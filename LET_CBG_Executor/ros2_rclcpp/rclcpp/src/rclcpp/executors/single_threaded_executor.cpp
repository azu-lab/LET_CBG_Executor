// Copyright 2015 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rclcpp/executors/single_threaded_executor.hpp"
#include "rclcpp/any_executable.hpp"
#include "rclcpp/scope_exit.hpp"
#include <iostream>
#include "fstream"
#include "ostream"

#define NSEC_PER_SEC 1000000000
#define _NOW (std::chrono::system_clock::now())

using rclcpp::executors::SingleThreadedExecutor;
std::vector<int64_t> jitters;
int j=0;
struct timespec start_time;
struct timespec spin_start_time;


SingleThreadedExecutor::SingleThreadedExecutor(const rclcpp::ExecutorOptions & options)
: rclcpp::Executor(options) {}

SingleThreadedExecutor::~SingleThreadedExecutor() {}

void
SingleThreadedExecutor::spin()
{
  if (spinning.exchange(true)) {
    throw std::runtime_error("spin() called while already spinning");
  }
  RCLCPP_SCOPE_EXIT(this->spinning.store(false); );
  while (rclcpp::ok(this->context_) && spinning.load()) {
    rclcpp::AnyExecutable any_executable;
    if (get_next_executable(any_executable)) {
       //std::cout << "execute is working" << std::endl;
      execute_any_executable(any_executable);
    }
  }
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
static inline void add_timespecs(
  const struct timespec * t1,
  const struct timespec * t2,
  struct timespec * dst)
{
  dst->tv_sec = t1->tv_sec + t2->tv_sec;
  dst->tv_nsec = t1->tv_nsec + t2->tv_nsec;
  normalize_timespec(dst);
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

int record_jitter(
  const struct timespec * deadline,
  const struct timespec * result_time)
{
  
  struct timespec jitter;
  int parity = 1;
  //std::cout << "jitter" << 1<< "ms" << std::endl;
  if (timespec_gt(result_time, deadline)) {
    // missed a deadline
   // std::cout << "jitter" << 2<< "ms" << std::endl;
    subtract_timespecs(result_time, deadline, &jitter);
    //std::cout << "jitter" << 3<< "ms" << std::endl;
  } else {
    //std::cout << "jitter" << 4<< "ms" << std::endl;
    subtract_timespecs(deadline, result_time, &jitter);
    parity = -1;
  }
  int64_t latency_samples;
  
  //std::cout << "jitter" << 10<< "ms" << std::endl;
   latency_samples= parity * timespec_to_uint64(&jitter);
   jitters.push_back(latency_samples);
   
  //std::cout << "jitter" << 5<< "ms" << std::endl;
   std::cout << "jitter__" << latency_samples<< "ns" << std::endl;
   
  return 0;
}
int sleep_time(
  const struct timespec * deadline,
  const struct timespec * result_time)
{
  struct timespec jitter;
  int parity = 1;
  //std::cout << "jitter" << 1<< "ms" << std::endl;
  if (timespec_gt(result_time, deadline)) {
    // missed a deadline
   // std::cout << "jitter" << 2<< "ms" << std::endl;
    subtract_timespecs(result_time, deadline, &jitter);
    //std::cout << "jitter" << 3<< "ms" << std::endl;
  } else {
    //std::cout << "jitter" << 4<< "ms" << std::endl;
    subtract_timespecs(deadline, result_time, &jitter);
    parity = -1;
  }
  int64_t latency_samples;
  
  //std::cout << "jitter" << 10<< "ms" << std::endl;
   latency_samples= parity * timespec_to_uint64(&jitter);
   
  return latency_samples;
}
bool max_duration_not_elapsed (std::chrono::nanoseconds max_duration,std::chrono::steady_clock::time_point start) {
 
      if (std::chrono::steady_clock::now() - start < max_duration) {
        
        return true;
      }
     
      // spun too long
      return false;
    }


void
SingleThreadedExecutor::spin_some(std::chrono::nanoseconds max_duration)
{
  auto start = std::chrono::steady_clock::now();
  /*
  auto max_duration_not_elapsed = [max_duration, start]() {
      if (std::chrono::nanoseconds(0) == max_duration) {
        // told to spin forever if need be
        return true;
      } else if (std::chrono::steady_clock::now() - start < max_duration) {
        // told to spin only for some maximum amount of time
        return true;
      }
      // spun too long
      return false;
    };*/
    

  RCLCPP_SCOPE_EXIT(this->spinning.store(false); );
  //&&!max_duration_not_elapsed()
  while (rclcpp::ok(this->context_)&&max_duration_not_elapsed(max_duration,start)) {
    //std::cout << "spin is working" << std::endl;
    rclcpp::AnyExecutable any_executable;
    if (get_next_executable(any_executable)) {
      execute_any_executable(any_executable);
      //std::cout << "let execute done" << std::endl;
    }
   
    else
    { return ;
    }
}
}

void
SingleThreadedExecutor::executor_spin_one_period(const uint64_t period,std::string thread_name1)
{
      struct timespec wakeup_time;
     struct timespec theoretical_time;
     struct timespec theoretical_end_time;
     struct timespec start_time_period;
     struct timespec end_time_period;
     struct timespec update_period;
     struct timespec end_spin_some;
     struct timespec sleep_start;
     
     int64_t sleep_time1;
     update_period.tv_sec = 0;
     update_period.tv_nsec = period;
     

       
  auto period_ns= std::chrono::duration<uint64_t,std::nano>(period);
  auto period_ms= std::chrono::duration<uint64_t,std::milli>(period);

      j++;
      
      multiply_timespec(&update_period, j, &theoretical_time);
      add_timespecs(&start_time, &theoretical_time, &theoretical_time);
       std::cout << "j" << j<< std::endl;
     std::cout <<thread_name1<< "--theoretical_time" << theoretical_time.tv_sec<< "s" << std::endl;
      std::cout <<thread_name1<< "--theoretical_time" << theoretical_time.tv_nsec<< "ns" << std::endl;

  
      clock_gettime(CLOCK_MONOTONIC, &start_time_period);
      std::cout <<thread_name1<< "--start_time_period" << start_time_period.tv_sec<< "s" << std::endl;
 
     std::cout <<thread_name1<< "--start_time_period" << start_time_period.tv_nsec<< "ns" << std::endl;
  spin_some(period_ns);
  clock_gettime(CLOCK_MONOTONIC, &end_spin_some);
 
  add_timespecs(&start_time_period,&update_period,&theoretical_end_time);
  sleep_time1=sleep_time(&end_spin_some,&theoretical_time);
  
  //auto end = std::chrono::steady_clock::now();
  std::cout << "sleep_time__" <<sleep_time1<< "ns" << std::endl;
  
  if ( sleep_time1> 0) {
    clock_gettime(CLOCK_MONOTONIC, &sleep_start);
   
       std::this_thread::sleep_for(std::chrono::nanoseconds(sleep_time1));
      clock_gettime(CLOCK_MONOTONIC, &end_time_period);
      std::cout <<thread_name1<< "--end_time_period" << end_time_period.tv_sec<< "s" << std::endl;
      std::cout <<thread_name1<< "--end_time_period" << end_time_period.tv_nsec<< "ns" << std::endl;
      wakeup_time=start_time_period;
      wakeup_time.tv_sec = wakeup_time.tv_sec;
      wakeup_time.tv_nsec = wakeup_time.tv_nsec+period;
      record_jitter(&wakeup_time, &end_time_period);
     
  }
  
}

void
SingleThreadedExecutor::executor_spin_period(const uint64_t period,std::string thread_name1)
{
   std::mutex mtx_;
  
  struct timespec current_time;
  struct timespec start_time_periodx;
  struct timespec end_time_periodx;
  
  j=0;
  
  if (spinning.exchange(true)) {
    throw std::runtime_error("spin() called while already spinning");
  }
  RCLCPP_SCOPE_EXIT(this->spinning.store(false); );
 
  
   clock_gettime(CLOCK_MONOTONIC, &start_time);
   current_time=start_time;
  // Set memory_strategy_ and exec_list_ based on weak_nodes_
  while (rclcpp::ok(this->context_)) {
    
   //std::cout << "current_time" << std::chrono::duration_cast<std::chrono::milliseconds>(start_let_period - start_let).count()<< "s" << std::endl;
  
   std::cout <<thread_name1<< "--start_time" << current_time.tv_sec<< "s" << std::endl;
 
   std::cout <<thread_name1<< "--start_time" << current_time.tv_nsec<< "ns" << std::endl;
   clock_gettime(CLOCK_MONOTONIC, &start_time_periodx);
   //std::cout <<thread_name1<< "---start_time_periodx" << start_time_periodx.tv_sec<< "s" << std::endl;
 
   //std::cout <<thread_name1<< "--start_time_periodx" << start_time_periodx.tv_nsec<< "ns" << std::endl;
    executor_spin_one_period(period,thread_name1);
   
    clock_gettime(CLOCK_MONOTONIC, &end_time_periodx);
   std::cout <<thread_name1<< "--end_time_periodx" << end_time_periodx.tv_sec<< "s" << std::endl;
 
   std::cout <<thread_name1<< "--end_time_periodx" << end_time_periodx.tv_nsec<< "ns" << std::endl;
   
  }
}

std::vector<int64_t>
SingleThreadedExecutor::spin(const uint64_t period)
{
 
  int i=0;
  if (spinning.exchange(true)) {
    throw std::runtime_error("spin() called while already spinning");
  }
  struct timespec theoretical_time;
  struct timespec wakeup_time;
   struct timespec start_time_period;
     struct timespec end_time_period;
     struct timespec update_period;
  update_period.tv_sec = 0;
  update_period.tv_nsec = period;
  jitters.reserve(10000000);
  RCLCPP_SCOPE_EXIT(this->spinning.store(false); );
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  while (rclcpp::ok(this->context_) && spinning.load()) {
    rclcpp::AnyExecutable any_executable;
    if (get_next_executable(any_executable)) {
      i++;
      multiply_timespec(&update_period, i, &theoretical_time);
      add_timespecs(&start_time, &theoretical_time, &theoretical_time);
      clock_gettime(CLOCK_MONOTONIC, &start_time_period);
       std::cout << "start_time_period" << start_time_period.tv_sec<< "s" << std::endl;
       std::cout << "start_time_period" << start_time_period.tv_nsec<< "ns" << std::endl;
      execute_any_executable(any_executable);
      clock_gettime(CLOCK_MONOTONIC, &end_time_period);
      std::cout << "theoretical_time" << theoretical_time.tv_sec<< "s" << std::endl;
      std::cout << "theoretical_time" << theoretical_time.tv_nsec<< "ns" << std::endl;
      std::cout << "end_time_period" << end_time_period.tv_sec<< "ns" << std::endl;
      std::cout << "end_time_period" << end_time_period.tv_nsec<< "ns" << std::endl;
      wakeup_time=start_time_period;
      wakeup_time.tv_sec = wakeup_time.tv_sec;
      wakeup_time.tv_nsec = wakeup_time.tv_nsec+period;
      record_jitter(&wakeup_time, &end_time_period);
    }
  }
  return jitters;
 
}