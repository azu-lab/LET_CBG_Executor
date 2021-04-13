#include <functional>
#include <iostream>
#include "fstream"
#include "ostream"
#include <thread>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>

#include <pthread.h>

#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/executor.hpp>

#include "PingSubNode.hpp"
#include "PongSubNode.hpp"

#define NSEC_PER_SEC 1000000000
#define EXPERIENC_NUM 20

using namespace std::chrono_literals;
using namespace std::chrono;
using std::placeholders::_1;

using rclcpp::Executor;
using rclcpp::executors::SingleThreadedExecutor;

const std::chrono::seconds EXPERIMENT_DURATION = 10s;
std::vector<int64_t> jitters;


/// This function prints details on the arguments of this executable.
void print_help()
{
  std::cout << "Call with arguments [type] [rt_ping_period_us] [be_ping_period_us] " <<
    "[rt_busyloop_us] [be_busyloop_us] [cpu_id]." << std::endl;
  std::cout << "  type: determines the nodes included in this process:" << std::endl;
  std::cout << "    i: ping node only" << std::endl;
  std::cout << "    o: pong node only" << std::endl;
  std::cout << "    io: ping node and pong node" << std::endl;
  std::cout << "  rt_ping_period_us: microseconds between publishing of ping messages " << "by real-time thread in ping node" << std::endl;
  std::cout << "  be_ping_period_us: microseconds between publishing of ping messages " << "by best-effort thread in ping node" << std::endl;
  std::cout << "  rt_busyloop_us: microseconds of computation by real-time thread in " << "pong node before answering with pong" << std::endl;
  std::cout << "  be_busyloop_us: microseconds of computation by best-effort thread in " << "pong node before answering with pong" << std::endl;
  std::cout << "  rt_let_period_ns: let period "  << std::endl;
  std::cout << "  be_let_period_ns: let period "  << std::endl;
  std::cout << "  scheduler (optional): let or default rclcpp "<< std::endl;
  std::cout << "  cpu_id (optional): pins both, real-time thread and best-effort thread, to " << "the given cpu" << std::endl;
}


static inline uint64_t timespec_to_uint64(const struct timespec * t)
{
  return static_cast<uint64_t>(t->tv_sec) * NSEC_PER_SEC + static_cast<uint64_t>(t->tv_nsec);
}

static inline void uint64_to_timespec(const uint64_t input, struct timespec * t)
{
  uint64_t nsecs = input % NSEC_PER_SEC;
  uint64_t secs = (input - nsecs) / NSEC_PER_SEC;
  t->tv_sec = static_cast<time_t>(secs);
  t->tv_nsec = static_cast<long>(nsecs); // NOLINT for C type long
}
static inline void multiply_timespec(
  const struct timespec * t, const uint32_t i,
  struct timespec * result)
{
  uint64_t result_nsec = i * timespec_to_uint64(t);
  uint64_to_timespec(result_nsec, result);
}
static inline void normalize_timespec(struct timespec * t)
{
  // TODO(jacquelinekay) improve
  while (t->tv_nsec >= NSEC_PER_SEC) {
    t->tv_nsec -= NSEC_PER_SEC;
    t->tv_sec++;
  }
}

static inline bool timespec_gt(
  const struct timespec * t1,
  const struct timespec * t2)
{
  if (t1->tv_sec > t2->tv_sec) {
    return true;
  }
  if (t1->tv_sec < t2->tv_sec) {
    return false;
  }
  return t1->tv_nsec > t2->tv_nsec;
}

static inline bool subtract_timespecs(
  const struct timespec * t1,
  const struct timespec * t2,
  struct timespec * dst)
{
  if (timespec_gt(t2, t1)) {
    return subtract_timespecs(t2, t1, dst);
  }

  dst->tv_sec = t1->tv_sec - t2->tv_sec;
  dst->tv_nsec = t1->tv_nsec - t2->tv_nsec;

  normalize_timespec(dst);
  return true;
}
/*
int record_jitter(
  const struct timespec * deadline,
  const struct timespec * result_time, const size_t iteration)
{
  size_t i = iteration;
  struct timespec jitter;
  int parity = 1;
  //std::cout << "jitter" << 1<< "ms" << std::endl;
  if (timespec_gt(result_time, deadline)) {
    // missed a deadline
    //std::cout << "jitter" << 2<< "ms" << std::endl;
    subtract_timespecs(result_time, deadline, &jitter);
    //std::cout << "jitter" << 3<< "ms" << std::endl;
  } else {
    //std::cout << "jitter" << 4<< "ms" << std::endl;
    subtract_timespecs(deadline, result_time, &jitter);
    parity = -1;
  }
  int64_t latency_samples;
 // std::cout << "jitter" << 10<< "ms" << std::endl;
   latency_samples= parity * timespec_to_uint64(&jitter);
  //std::cout << "jitter" << 5<< "ms" << std::endl;
   std::cout << "jitter" << latency_samples << "ns" << std::endl;
  return 0;
}
*/


/// Sets the priority of the given thread to max or min priority (in the SCHED_FIFO real-time
/// policy) and pins the thread to the given cpu (if cpu_id != 0).
void configure_thread(std::thread & t, bool set_real_time, int cpu_id)
{

  sched_param params;
  int policy;
  pthread_getschedparam(t.native_handle(), &policy, &params);
  if (set_real_time) {
    params.sched_priority = sched_get_priority_max(SCHED_FIFO);
  } else {
    params.sched_priority = sched_get_priority_min(SCHED_FIFO);
  }

  if (pthread_setschedparam(t.native_handle(), SCHED_FIFO, &params)) {
    throw std::runtime_error("Failed to set scheduler parameters of thread!");
  }

  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(cpu_id, &cpuset);
  pthread_setaffinity_np(t.native_handle(), sizeof(cpu_set_t), &cpuset);
}


/// Returns the time of the given clock as std::chrono timestamp. When used with a
/// thread's clock, this function may be used to measure the thread's CPU time.
std::chrono::nanoseconds get_current_thread_clock_time(clockid_t id)
{
  timespec spec;
  clock_gettime(id, &spec);
  return std::chrono::seconds{spec.tv_sec} + std::chrono::nanoseconds{spec.tv_nsec};
}


/// The main function composes the Ping and Pong node (depending on the arguments)
/// and runs the experiment. See README.md for a simple architecture diagram.
/// Here: rt = real-time = high scheduler priority and be = best-effort = low scheduler priority.
int main(int argc, char * argv[])
{
  using rclcpp::RealTimeClass;
  using std::chrono::milliseconds;
  using std::chrono::nanoseconds;

  rclcpp::init(argc, argv);

  if (argc < 8 || argc > 10) {
    print_help();
    return 0;
  }
  int64_t rt_let_period;
  int64_t be_let_period;
  std::string processType(argv[1]);

  microseconds rt_ping_period_us(atol(argv[2]));
  microseconds be_ping_period_us(atol(argv[3]));
  microseconds rt_busyloop_us(atol(argv[4]));
  microseconds be_busyloop_us(atol(argv[5]));
  rt_let_period=atol(argv[6]);
  be_let_period=atol(argv[7]);
  std::string scheduler;
   if(argc>=9)
  {
    scheduler=argv[8];

  }
  std::cout << scheduler << std::endl;
  int cpuId = 0;
  if (argc == 10) {
    cpuId = atoi(argv[9]);
  }
  

  // Create two executors within this process.
  rclcpp::executors::SingleThreadedExecutor executor_rt;
  rclcpp::executors::SingleThreadedExecutor executor_be;

  // If requested by the process-type argument, compose the Ping node from two PingSubNode
  // instances.
  rclcpp::Node::SharedPtr ping_node = nullptr;
  PingSubNode::SharedPtr ping_rt = nullptr;
  PingSubNode::SharedPtr ping_be = nullptr;
  if (processType.find("i") != std::string::npos) {
    std::cout << "Creating ping node." << std::endl;
    ping_node = std::make_shared<rclcpp::Node>("ping");
    ping_rt = std::make_shared<PingSubNode>(ping_node, RealTimeClass::RealTimeCritical, "RT", rt_ping_period_us);
    ping_be = std::make_shared<PingSubNode>(ping_node, RealTimeClass::BestEffort, "BE", be_ping_period_us);
    executor_rt.add_callback_group(ping_rt->get_callback_group(), ping_node->get_node_base_interface());
    executor_be.add_callback_group(ping_be->get_callback_group(), ping_node->get_node_base_interface());
  }

  // If requested by the process-type argument, compose the Pong node from two PongSubNode
  // instances.
  rclcpp::Node::SharedPtr pong_node = nullptr;
  PongSubNode::SharedPtr pong_rt = nullptr;
  PongSubNode::SharedPtr pong_be = nullptr;
  if (processType.find("o") != std::string::npos) {
    std::cout << "Creating pong node." << std::endl;
    pong_node = std::make_shared<rclcpp::Node>("pong");
    pong_rt = std::make_shared<PongSubNode>(pong_node, RealTimeClass::RealTimeCritical, "RT", rt_busyloop_us);
    pong_be = std::make_shared<PongSubNode>(pong_node, RealTimeClass::BestEffort, "BE", be_busyloop_us);
    executor_rt.add_callback_group(pong_rt->get_callback_group(), pong_node->get_node_base_interface());
    executor_be.add_callback_group(pong_be->get_callback_group(), pong_node->get_node_base_interface());
  }

  // Create and configure thread for the real-time executor, i.e. the high-priority executor.
  std::thread thread_rt([&]() {

      if(scheduler.compare("let")==0)
      {
      
       std::cout << "Thread with id=" << std::this_thread::get_id() << " is going to call executor_rt.executor_spin_period() ..." << std::endl;
       executor_rt.executor_spin_period(rt_let_period,"rt");//100000000
      }
      else
      {
        std::cout << "Thread with id=" << std::this_thread::get_id() << " is going to call executor_rt.spin() ..." << std::endl;
        std::cout << "rclcpp." << std::endl;
        executor_rt.spin();
      }
      
      
      

    });
  configure_thread(thread_rt, true, cpuId);

  // Create and configure thread for the best-effort executor, i.e. the low-priority executor.
  
  std::thread thread_be([&]() {
       if(scheduler.compare("let")==0)
      {
       
       std::cout << "Thread with id=" << std::this_thread::get_id() << " is going to call executor_rt.executor_spin_period() ..." << std::endl;
       executor_be.executor_spin_period(be_let_period,"be");//100000000
      }
      else
      {
        std::cout << "Thread with id=" << std::this_thread::get_id() << " is going to call executor_rt.spin() ..." << std::endl;
        std::cout << "rclcpp." << std::endl;
        executor_be.spin();
      }
    });
  configure_thread(thread_be, false, 2);

  // Creating the threads immediately started them. Therefore, get start CPU time of each
  /// thread now.
  clockid_t thread_rt_clock_id, thread_be_clock_id;
  pthread_getcpuclockid(thread_rt.native_handle(), &thread_rt_clock_id);
  pthread_getcpuclockid(thread_be.native_handle(), &thread_be_clock_id);
  nanoseconds rt_thread_begin = get_current_thread_clock_time(thread_rt_clock_id);
  nanoseconds be_thread_begin = get_current_thread_clock_time(thread_be_clock_id);

  std::this_thread::sleep_for(EXPERIMENT_DURATION);

  // Get end CPU time of each thread ...
  nanoseconds rt_thread_end = get_current_thread_clock_time(thread_rt_clock_id);
  nanoseconds be_thread_end = get_current_thread_clock_time(thread_be_clock_id);

  // ... and stop the experiment.
  rclcpp::shutdown();
  thread_rt.join();
  thread_be.join();

  // Print out throughput and latency statistics measured in the PingSubNode instances.
  if (ping_node) {
    ping_rt->outputjitter(jitters);
    ping_rt->print_jitter();
     ping_rt->print_statistics();
    ping_be->print_statistics();
  }

  // Print CPU times.
  long be_thread_duration_ms = std::chrono::duration_cast<milliseconds>(be_thread_end - be_thread_begin).count();
  long rt_thread_duration_ms = std::chrono::duration_cast<milliseconds>(rt_thread_end - rt_thread_begin).count();
  std::cout << "RT thread ran for " << rt_thread_duration_ms << "ms" << std::endl;
  std::cout << "BE thread ran for " << be_thread_duration_ms << "ms" << std::endl;

  std::cout << "TxPeriod: " << rt_ping_period_us.count() << "us " << be_ping_period_us.count() << "us";
  std::cout << " CTime: " << rt_busyloop_us.count() << "us " << be_busyloop_us.count() << "us";
  std::cout << " ThdRunTime: " << rt_thread_duration_ms << "ms " << be_thread_duration_ms << "ms" << std::endl;

  return 0;
}
