

## Requirements
- ROS 2 foxy (Ubuntu 20.04)

## Build
1.Clone the repository
$git clone https://github.com/azu-lab/LET_CBG_Executor.git
2.Set environment variables
$cd LET_CBG_Executor
$source /ros2_foxy/install/setup.bash
3.Build
$colcon build --symlink-install
## Evaluation
1．Set environment variables
Open a new terminal
$sudo su
$cd Evaluation_tool/ros2_examples/rclcpp/cbg-executor_ping-pong
$source /ros2_foxy/install/setup.bash
$source /LET_CBG_Executor/install/setup.bash
2.Build
$colcon build --symlink-install
3.RUN
$source /install/setup.bash
Start the executable by
$ros2 run cbg-executor_ping-pong_cpp ping-pong args...
where args... are five or six arguments as follows:
[type] [rt_ping_period_us] [be_ping_period_us] [rt_busyloop_us] [be_busyloop_us] [cpu_id]

type: determines the nodes included in this process:
  i: ping node only
  o: pong node only
  io: ping node and pong node

rt_ping_period_us: microseconds between publishing of ping messages by real-time thread
                   in ping node
be_ping_period_us: microseconds between publishing of ping messages by best-effort
                   thread in ping node
rt_busyloop_us:    microseconds of computation by real-time thread in pong node before
                   answering with pong
be_busyloop_us:    microseconds of computation by best-effort thread in pong node before
mode:               default/let
rt_letperiod_ns:    let period
be_letperiod_ns:    let period
cpu_id (optional): pins both, real-time thread and best-effort thread, to the given cpu
When using type i, a second process with type o has to be started simultaneously.