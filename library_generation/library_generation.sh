#!/bin/bash

PROJECT=$(pwd)

ros2 run micro_ros_setup create_firmware_ws.sh generate_lib

######## Adding extra packages ########
pushd firmware/mcu_ws > /dev/null

    # Import user defined packages
    mkdir extra_packages
    pushd extra_packages > /dev/null
        cp -R $PROJECT/library_generation/extra_packages/* .
        vcs import --input extra_packages.repos

        # Only lucy_msgs is needed from lucy_ros_packages; ignore everything else
        for pkg in lucy_ros_packages/*/; do
            [ "$(basename "$pkg")" = "lucy_msgs" ] && continue
            touch "$pkg/COLCON_IGNORE"
        done
    popd > /dev/null

popd > /dev/null

######## Build for Raspberry Pi Pico SDK  ########
rm -rf firmware/build

ros2 run micro_ros_setup build_firmware.sh $PROJECT/library_generation/toolchain.cmake $PROJECT/library_generation/colcon.meta

find firmware/build/include/ -name "*.c"  -delete
mkdir -p $PROJECT/libmicroros/include
cp -R firmware/build/include/* $PROJECT/libmicroros/include

cp -R firmware/build/libmicroros.a $PROJECT/libmicroros/libmicroros.a

######## Generate extra files ########
find firmware/mcu_ws/ros2 \( -name "*.srv" -o -name "*.msg" -o -name "*.action" \) | awk -F"/" '{print $(NF-2)"/"$NF}' > $PROJECT/available_ros2_types
find firmware/mcu_ws/extra_packages \( -name "*.srv" -o -name "*.msg" -o -name "*.action" \) | awk -F"/" '{print $(NF-2)"/"$NF}' >> $PROJECT/available_ros2_types
# sort it so that the result order is reproducible
sort -o $PROJECT/available_ros2_types $PROJECT/available_ros2_types

cd firmware
echo "" > $PROJECT/built_packages
for f in $(find $(pwd) -name .git -type d); do pushd $f > /dev/null; echo $(git config --get remote.origin.url) $(git rev-parse HEAD) >> $PROJECT/built_packages; popd > /dev/null; done;
# sort it so that the result order is reproducible
sort -o $PROJECT/built_packages $PROJECT/built_packages

######## Fix permissions ########
#sudo chmod -R 777 $PROJECT/microros_static_library
#sudo chmod -R -x+X $PROJECT/microros_static_library
