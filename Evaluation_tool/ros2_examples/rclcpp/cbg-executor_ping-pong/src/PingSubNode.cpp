// Copyright
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

#include "PingSubNode.hpp"
#include <iostream>
#include "fstream"
#include "ostream"
#include <cassert>


using namespace std::chrono_literals;
using namespace std::chrono;
using std::placeholders::_1;

PingSubNode::PingSubNode(
  rclcpp::Node::SharedPtr node, rclcpp::RealTimeClass cbg_class,
  const std::string & topics_prefix, const std::chrono::microseconds send_period)
: topics_prefix_(topics_prefix)
{
  assert(node != nullptr);
  assert(!topics_prefix.empty());

  callback_group_ = node->create_callback_group(
    rclcpp::CallbackGroupType::MutuallyExclusive, cbg_class);

  ping_sent_timestamps_.reserve(1000000); // TODO(Ralph): Adjust size to experiment duration and send period.
  pong_received_timestamps_.resize(1000000);

  rclcpp::SubscriptionOptionsWithAllocator<std::allocator<void>> options;
  options.callback_group = callback_group_;

  ping_timer_ = node->create_wall_timer(send_period, std::bind(&PingSubNode::ping_timer_callback,
      this), callback_group_);
  ping_publisher_ = node->create_publisher<std_msgs::msg::Int32>(topics_prefix_ + "_ping", rclcpp::SystemDefaultsQoS());
  pong_subscription_ = node->create_subscription<std_msgs::msg::Int32>(topics_prefix_ + "_pong", rclcpp::SystemDefaultsQoS(),
      std::bind(&PingSubNode::pong_subscription_callback, this,
      _1), options);
}



void PingSubNode::ping_timer_callback()
{
  std_msgs::msg::Int32 message;
  

  message.data = ping_sent_count_;
  ping_sent_timestamps_.push_back(std::chrono::system_clock::now());
  ping_publisher_->publish(message);
  std::cout << "timercallback" << std::endl;
  ++ping_sent_count_;
}


void PingSubNode::pong_subscription_callback(const std_msgs::msg::Int32::SharedPtr msg)
{
  pong_received_timestamps_[msg->data] = std::chrono::system_clock::now();
  std::cout << "subscriptioncallback" << std::endl;
  ++pong_received_count_;
}
void PingSubNode::outputjitter(std::vector<int64_t> jitters)
{
  std::ofstream jitteroutput("jitter.txt");
  for (size_t x = 1; x < jitters.size(); ++x) {
        jitteroutput<<jitters[x];
        jitteroutput <<std::endl;
       
        }
 
   jitteroutput.close();

}

void PingSubNode::print_jitter()
{
 
  //std::ofstream outputfile("test.txt");
  
  std::chrono::system_clock::duration latencyMax = 0us;
  std::chrono::system_clock::duration latencyMin = 100000000s;
  std::chrono::system_clock::duration latencySum = 0us;

  for (size_t i = 0; i < ping_sent_timestamps_.size(); ++i) {
   
    if (pong_received_timestamps_[i] >= ping_sent_timestamps_[i]) {
      std::chrono::system_clock::duration latency = pong_received_timestamps_[i] -
        ping_sent_timestamps_[i];
        auto latency_us=std::chrono::duration_cast<std::chrono::microseconds>(latency);
       latencys.push_back(latency);
      
       
     }
    
     }
     for (size_t j = 0; j < latencys.size(); ++j) {
       auto jitter=latencys[j+1]-latencys[j];
       jitters.push_back(jitter);
        
        }
        for (size_t x = 1; x < jitters.size(); ++x) {
        //outputfile<<std::chrono::duration_cast<std::chrono::microseconds>(jitters[x]).count();
        //outputfile <<std::endl;
        std::cout << "jitter"<< x<<"______"<<std::chrono::duration_cast<std::chrono::microseconds>(jitters[x]).count()<< std::endl;
        }
       //outputfile.close();


}

void PingSubNode::print_statistics()
{
  std::cout << "Sent " << ping_sent_count_ << " pings on " << topics_prefix_ << "_ping topic" <<
    std::endl;
  std::cout << "Received " << pong_received_count_ << " pongs on " << topics_prefix_ <<
    "_pong topic" << std::endl;

  std::chrono::system_clock::duration latencyMax = 0us;
  std::chrono::system_clock::duration latencyMin = 100000000s;
  std::chrono::system_clock::duration latencySum = 0us;

  for (size_t i = 0; i < ping_sent_timestamps_.size(); ++i) {
    if (pong_received_timestamps_[i] >= ping_sent_timestamps_[i]) {
      std::chrono::system_clock::duration latency = pong_received_timestamps_[i] -
        ping_sent_timestamps_[i];
      latencyMax = std::max(latencyMax, latency);
      latencyMin = std::min(latencyMin, latency);
      latencySum += latency;
    }
  }
  if (pong_received_count_ > 0) {
    std::chrono::system_clock::duration latencyAvg = latencySum / pong_received_count_;

    std::cout << "latency on " << topics_prefix_ << " path: min=" <<
      std::chrono::duration_cast<std::chrono::microseconds>(latencyMin).count() <<
      "us max=" << std::chrono::duration_cast<std::chrono::microseconds>(latencyMax).count() <<
      "us avg=" << std::chrono::duration_cast<std::chrono::microseconds>(latencyAvg).count() <<
      "us " << std::endl;
  }

}

void PingSubNode::save_statistics(std::ofstream *fs)
{
  *fs << "Sent " << ping_sent_count_ << " pings on " << topics_prefix_ << "_ping topic" <<std::endl;
  *fs << "Received " << pong_received_count_ << " pongs on " << topics_prefix_ <<"_pong topic" << std::endl;

  std::chrono::system_clock::duration latencyMax = 0us;
  std::chrono::system_clock::duration latencyMin = 100000000s;
  std::chrono::system_clock::duration latencySum = 0us;

  for (size_t i = 0; i < ping_sent_timestamps_.size(); ++i) {
    if (pong_received_timestamps_[i] >= ping_sent_timestamps_[i]) {
      std::chrono::system_clock::duration latency = pong_received_timestamps_[i] -
        ping_sent_timestamps_[i];
      latencyMax = std::max(latencyMax, latency);
      latencyMin = std::min(latencyMin, latency);
      latencySum += latency;
    }
  }
  std::chrono::system_clock::duration latencyAvg = latencySum / pong_received_count_;

  *fs << "latency on " << topics_prefix_ <<
  " path: min=" << std::chrono::duration_cast<std::chrono::microseconds>(latencyMin).count() <<
  "us max=" << std::chrono::duration_cast<std::chrono::microseconds>(latencyMax).count() <<
  "us avg=" << std::chrono::duration_cast<std::chrono::microseconds>(latencyAvg).count() <<
  "us " << std::endl;
}

void PingSubNode::save_statistics2(std::ofstream *fs)
{
  *fs << ping_sent_count_ <<std::endl;
  *fs << pong_received_count_ <<std::endl;

  std::chrono::system_clock::duration latencyMax = 0us;
  std::chrono::system_clock::duration latencyMin = 100000000s;
  std::chrono::system_clock::duration latencySum = 0us;

  for (size_t i = 0; i < ping_sent_timestamps_.size(); ++i) {
    if (pong_received_timestamps_[i] >= ping_sent_timestamps_[i]) {
      std::chrono::system_clock::duration latency = pong_received_timestamps_[i] -
        ping_sent_timestamps_[i];
      latencyMax = std::max(latencyMax, latency);
      latencyMin = std::min(latencyMin, latency);
      latencySum += latency;
    }
  }
  std::chrono::system_clock::duration latencyAvg = latencySum / pong_received_count_;

  *fs  << std::chrono::duration_cast<std::chrono::microseconds>(latencyMin).count() <<
  "\n" << std::chrono::duration_cast<std::chrono::microseconds>(latencyMax).count() <<
  "\n" << std::chrono::duration_cast<std::chrono::microseconds>(latencyAvg).count() << std::endl;
}

