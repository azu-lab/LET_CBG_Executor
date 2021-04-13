#include <functional>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <pthread.h>

#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/executor.hpp>

#include "PingSubNode.hpp"
#include "PongSubNode.hpp"

using namespace std::chrono_literals;
using namespace std::chrono;
using std::placeholders::_1;

using rclcpp::executor::Executor;
using rclcpp::executors::SingleThreadedExecutor;
using rclcpp::callback_group::RealTimeClass;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;
const std::chrono::seconds EXPERIMENT_DURATION = 1s;

#define EXPERIENC_NUM 20
/// This function prints details on the arguments of this executable.
void print_help()
{
  std::cout << "Call with arguments [type] [rt_ping_period_us] [so_ping_period_us][be_ping_period_us] " <<
    " [cpu_id]." << std::endl;
  std::cout << "  type: determines the nodes included in this process:" << std::endl;
  std::cout << "    i: ping node only" << std::endl;
  std::cout << "    o: pong node only" << std::endl;
  std::cout << "    io: ping node and pong node" << std::endl;
  std::cout << "  rt_ping_period_us: microseconds between publishing of ping messages " << "by real-time thread in ping node" << std::endl;
//  std::cout << "  so_ping_period_us: microseconds between publishing of ping messages " << "by soft-real thread in ping node" << std::endl;
  std::cout << "  be_ping_period_us: microseconds between publishing of ping messages " << "by best-effort thread in ping node" << std::endl;
  //std::cout << "  rt_busyloop_us: microseconds of computation by real-time thread in " << "pong node before answering with pong" << std::endl;
  //std::cout << "  so_busyloop_us: microseconds of computation by soft-real thread in " << "pong node before answering with pong" << std::endl;
  //std::cout << "  be_busyloop_us: microseconds of computation by best-effort thread in " << "pong node before answering with pong" << std::endl;
  //std::cout << "  cpu_id (optional): pins both, real-time thread and soft-real thread ,best-effort thread, to " << "the given cpu" << std::endl;
  std::cout << " publish data size: "<< std::endl;
  std::cout << "    10: 10byte data "<< std::endl;
  std::cout << "    100: 100byte data "<< std::endl;
  std::cout << "    1000: 1000byte data "<< std::endl;
}


/// Sets the priority of the given thread to max or min priority (in the SCHED_FIFO real-time
/// policy) and pins the thread to the given cpu (if cpu_id != 0).

//void configure_thread(std::thread & t, bool set_real_time, int cpu_id)
void configure_thread(std::thread & t, int set_real_time, int cpu_id)
{

  sched_param params;
  int policy;
  pthread_getschedparam(t.native_handle(), &policy, &params);
  if (set_real_time == 1) {
    params.sched_priority = sched_get_priority_max(SCHED_FIFO);
  }
  else if(set_real_time == 2) {
//        params.sched_priority = sched_get_priority_max(SCHED_FIFO);
    params.sched_priority = (sched_get_priority_max(SCHED_FIFO) + sched_get_priority_min(SCHED_FIFO))/2;
  }
  else
  {
   params.sched_priority = sched_get_priority_min(SCHED_FIFO);
  }

  int error = pthread_setschedparam(t.native_handle(), SCHED_FIFO, &params);
  if (error!=0) {
    throw std::runtime_error("Failed to set scheduler parameters of thread!");
  }

//  std::string no;
//  no = std::to_string(set_real_time);

//std::cout << " busy_loop " << set_real_time << " us " << std::endl;
int pri = params.sched_priority;
  std::cout << " thread No " << set_real_time;
  std::cout << " priority " << pri << std::endl;


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

//one experiment
void expe_onece(int i,int argc,char * argv[],std::ofstream *fs,std::ofstream *fs2){
  rclcpp::init(argc, argv);


  int cpuId = 0;


  std::string processType(argv[1]);
  microseconds rt_ping_period_us(atol(argv[2]));
  //microseconds so_ping_period_us(atol(argv[3]));
  microseconds be_ping_period_us(atol(argv[3]));
  long busy_loop = atol(argv[2])/EXPERIENC_NUM;

  //busy_loop = busy_loop + ((i*(busy_loop/2)));
  busy_loop = busy_loop*(i+1);

  std::cout << " busy_loop " << busy_loop << " us " << std::endl;

  //microseconds rt_busyloop_us(atol(argv[5]));
  //microseconds so_busyloop_us(atol(argv[6]));
  //microseconds be_busyloop_us(atol(argv[7]));
  microseconds rt_busyloop_us(busy_loop);
//  microseconds so_busyloop_us(busy_loop);
  microseconds be_busyloop_us(busy_loop);


  // Create  executors within this process.
  rclcpp::executors::SingleThreadedExecutor executor_rt;
//  rclcpp::executors::SingleThreadedExecutor executor_so;
  rclcpp::executors::SingleThreadedExecutor executor_be;

  // If requested by the process-type argument, compose the Ping node from two PingSubNode
  // instances.
  rclcpp::Node::SharedPtr ping_node = nullptr;
  PingSubNode::SharedPtr ping_rt = nullptr;
//  PingSubNode::SharedPtr ping_so = nullptr;
  PingSubNode::SharedPtr ping_be = nullptr;
  if (processType.find("i") != std::string::npos) {
    std::cout << "Creating ping node." << std::endl;
    ping_node = std::make_shared<rclcpp::Node>("ping");
    ping_rt = std::make_shared<PingSubNode>(ping_node, RealTimeClass::RealTimeCritical, "RT", rt_ping_period_us);
//    ping_so = std::make_shared<PingSubNode>(ping_node, RealTimeClass::SoftRealTime, "SO", so_ping_period_us);
    ping_be = std::make_shared<PingSubNode>(ping_node, RealTimeClass::BestEffort, "BE", be_ping_period_us);
    executor_rt.add_callback_group(ping_rt->get_callback_group(), ping_node->get_node_base_interface());
//    executor_so.add_callback_group(ping_so->get_callback_group(), ping_node->get_node_base_interface());
    executor_be.add_callback_group(ping_be->get_callback_group(), ping_node->get_node_base_interface());
  }


  // If requested by the process-type argument, compose the Pong node from two PongSubNode
  // instances.
  rclcpp::Node::SharedPtr pong_node = nullptr;
  PongSubNode::SharedPtr pong_rt = nullptr;
//  PongSubNode::SharedPtr pong_so = nullptr;
  PongSubNode::SharedPtr pong_be = nullptr;
  if (processType.find("o") != std::string::npos) {
    std::cout << "Creating pong node." << std::endl;
    pong_node = std::make_shared<rclcpp::Node>("pong");
    pong_rt = std::make_shared<PongSubNode>(pong_node, RealTimeClass::RealTimeCritical, "RT", rt_busyloop_us);
//    pong_so = std::make_shared<PongSubNode>(pong_node, RealTimeClass::SoftRealTime, "SO", so_busyloop_us);
    pong_be = std::make_shared<PongSubNode>(pong_node, RealTimeClass::BestEffort, "BE", be_busyloop_us);
    executor_rt.add_callback_group(pong_rt->get_callback_group(), pong_node->get_node_base_interface());
//    executor_so.add_callback_group(pong_so->get_callback_group(), pong_node->get_node_base_interface());
    executor_be.add_callback_group(pong_be->get_callback_group(), pong_node->get_node_base_interface());
  }

  // Create and configure thread for the real-time executor, i.e. the high-priority executor.
  std::thread thread_rt([&]() {
      executor_rt.spin();
    });

  configure_thread(thread_rt, 1, cpuId);

  // Create and configure thread for the soft-real executor, i.e. the middle-priority executor.
/*  std::thread thread_so([&]() {
      executor_so.spin();
    });

  configure_thread(thread_so, 2, cpuId);
*/
  // Create and configure thread for the best-effort executor, i.e. the low-priority executor.
  std::thread thread_be([&]() {
      executor_be.spin();
    });

  configure_thread(thread_be, 3, cpuId);

  // Creating the threads immediately started them. Therefore, get start CPU time of each
  /// thread now.
  clockid_t thread_rt_clock_id, /*thread_so_clock_id,*/thread_be_clock_id;
  pthread_getcpuclockid(thread_rt.native_handle(), &thread_rt_clock_id);
//  pthread_getcpuclockid(thread_so.native_handle(), &thread_so_clock_id);
  pthread_getcpuclockid(thread_be.native_handle(), &thread_be_clock_id);
  nanoseconds rt_thread_begin = get_current_thread_clock_time(thread_rt_clock_id);
//  nanoseconds so_thread_begin = get_current_thread_clock_time(thread_so_clock_id);
  nanoseconds be_thread_begin = get_current_thread_clock_time(thread_be_clock_id);

  std::this_thread::sleep_for(EXPERIMENT_DURATION);

  // Get end CPU time of each thread ...
  nanoseconds rt_thread_end = get_current_thread_clock_time(thread_rt_clock_id);
//  nanoseconds so_thread_end = get_current_thread_clock_time(thread_so_clock_id);
  nanoseconds be_thread_end = get_current_thread_clock_time(thread_be_clock_id);
  std::cout << "stop the experiment." << std::endl;
  // ... and stop the experiment.
  rclcpp::shutdown();
  thread_rt.join();
//  thread_so.join();
  thread_be.join();

  // Print CPU times.
  long be_thread_duration_ms = std::chrono::duration_cast<milliseconds>(be_thread_end - be_thread_begin).count();
//  long so_thread_duration_ms = std::chrono::duration_cast<milliseconds>(so_thread_end - so_thread_begin).count();
  long rt_thread_duration_ms = std::chrono::duration_cast<milliseconds>(rt_thread_end - rt_thread_begin).count();
  std::cout << "RT thread ran for " << rt_thread_duration_ms << " ms " << std::endl;
//  std::cout << "SO thread ran for " << so_thread_duration_ms << " ms " << std::endl;
  std::cout << "BE thread ran for " << be_thread_duration_ms << " ms " << std::endl;

  *fs <<"RT thread ran for :";
  *fs << rt_thread_duration_ms<< " ms "<< std::endl;
  *fs2 << rt_thread_duration_ms<< std::endl;
/*
  *fs <<"SO thread ran for :";
  *fs << so_thread_duration_ms<< " ms"<< std::endl;
  *fs2 << so_thread_duration_ms<< std::endl;
*/
  *fs <<"BE thread ran for :";
  *fs << be_thread_duration_ms<< " ms "<< std::endl;
  *fs2 << be_thread_duration_ms<< std::endl;

  std::cout << "TxPeriod: " << rt_ping_period_us.count() << " us " << be_ping_period_us.count() << "us";/*<< so_ping_period_us.count() << " us "*/ 
  std::cout << "CTime: " << rt_busyloop_us.count() <<  " us " /*<< so_busyloop_us.count() <<" us "*/ << be_busyloop_us.count() << "us";
  std::cout << "ThdRunTime: " << rt_thread_duration_ms << " ms "/*<< so_thread_duration_ms << " ms "*/ << be_thread_duration_ms << "ms" << std::endl;
  std::cout << "Save Result" << std::endl;

  *fs << "TxPeriod: " << rt_ping_period_us.count() << " us " /*<< so_ping_period_us.count() << " us "*/ << be_ping_period_us.count() << "us\n";
  *fs << "CTime: " << rt_busyloop_us.count() <<  " us " /*<< so_busyloop_us.count() <<" us "*/ << be_busyloop_us.count() << "us\n";
  *fs << "ThdRunTime: " << rt_thread_duration_ms << " ms "/*<< so_thread_duration_ms << " ms "*/ << be_thread_duration_ms << "ms" << std::endl;
  *fs << "Save Result" << std::endl;


  *fs2 << rt_ping_period_us.count() << std::endl;
//  *fs2 << so_ping_period_us.count() << std::endl;
  *fs2 << be_ping_period_us.count() << std::endl;
  *fs2 << rt_busyloop_us.count() << std::endl;
//  *fs2 << so_busyloop_us.count() << std::endl;
  *fs2 << be_busyloop_us.count() << std::endl;
  *fs2 << rt_thread_duration_ms << std::endl;
//  *fs2 << so_thread_duration_ms << std::endl;
  *fs2 << be_thread_duration_ms << std::endl;
  ping_rt->save_statistics2(fs2);
//  ping_so->save_statistics2(fs2);
  ping_be->save_statistics2(fs2);

  ping_rt->save_statistics(fs);
//  ping_so->save_statistics(fs);
  ping_be->save_statistics(fs);

  // Print out throughput and latency statistics measured in the PingSubNode instances.
  if (ping_node) {
    ping_rt->print_statistics();
//    ping_so->print_statistics();
    ping_be->print_statistics();
  }
}

/// The main function composes the Ping and Pong node (depending on the arguments)
/// and runs the experiment. See README.md for a simple architecture diagram.
/// Here: rt = real-time = high scheduler priority and be = best-effort = low scheduler priority.
int main(int argc, char * argv[])
{
  std::cout << "start exp" << std::endl;
  //Open file for saveing result data
  std::ofstream fs;//write cout text and result
  std::ofstream fs2;//write only result
  fs.open("exp0Result.txt");
  fs2.open("exp0Result2.txt");


  PingSubNode::SharedPtr ps = nullptr;
  ps = std::make_shared<PingSubNode>();

/*  ps->data_set(argv[3]); */

  if (!fs)
  {
   std::cout << "can't open file" << std::endl;
   std::cin.get();
    return 0;
  }
  if (!fs2)
  {
   std::cout << "can't open file2" << std::endl;
   std::cin.get();
    return 0;
  }

  //Do experinece for EXPERIENC_NUM
  for(int i = 0; i < EXPERIENC_NUM; i++){
    //std::cout << "roop i:" << i << "/" <<EXPERIENC_NUM<< std::endl;
    std::cout << "exp:" << i+1 << "/" <<EXPERIENC_NUM<< std::endl;
    expe_onece(i,argc, argv, &fs,&fs2);
  }
  std::cout << "roop :" << EXPERIENC_NUM << std::endl;
  fs.close();
  fs2.close();

  return 0;
}
