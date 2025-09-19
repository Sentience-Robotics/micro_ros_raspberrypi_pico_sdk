```bash
docker run --rm -d -v /dev:/dev --privileged --net=host microros/micro-ros-agent:humble serial --dev /dev/ttyACM0 -b 115200

cd ~/lucy_ws/src/micro_ros_raspberrypi_pico_sdk/build
cmake ..
make
sudo picotool load pico_micro_ros_example.uf2 -f
sudo picotool reboot -f

# DEBUG
ros2 topic echo /servo_subscriber
ros2 topic echo /trace_publisher

# ???
cd /home/dev/lucy_ws/lucy_ros2/install
source setup.zsh

ros2 topic echo rp2040_topic
```
