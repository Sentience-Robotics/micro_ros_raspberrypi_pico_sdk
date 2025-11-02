```bash
docker run --rm -d -v /dev:/dev --privileged --net=host microros/micro-ros-agent:humble serial --dev /dev/ttyACM0 -b 115200

cd ~/lucy_ws/src/micro_ros_raspberrypi_pico_sdk/build
cmake ..
make
sudo picotool load pico_micro_ros_right_arm.uf2 -f --ser E6617C93E37A6629
sudo picotool reboot -f --ser E6617C93E37A6629

# OR
pico-flash-right-arm
pico-flash-left-arm

# DEBUG
ros2 topic echo /joints/right_arm
ros2 topic echo /trace_publisher

# ???
cd /home/dev/lucy_ws/lucy_ros2/install
source setup.zsh

ros2 topic echo rp2040_topic
```

left arm : E6617C93E3858429
right arm : E6617C93E37A6629
