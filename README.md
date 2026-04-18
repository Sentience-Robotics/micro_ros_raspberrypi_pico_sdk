![banner](.images/banner-dark-theme.png#gh-dark-mode-only)
![banner](.images/banner-light-theme.png#gh-light-mode-only)

# micro-ROS module for Raspberry Pi Pico SDK

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

## Getting Started

Here is a quick way to compile the example given in this repository.

### Dependencies

micro-ROS precompiled library is compiled using `arm-none-eabi-gcc` [9.3.1](https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2), a compatible version is expected when building the micro-ROS project.
You can specify a compiler path with the following command:

```bash
# Configure environment
echo "export PICO_TOOLCHAIN_PATH=..." >> ~/.bashrc
source ~/.bashrc
```

### 1. Install Pico SDK
First, make sure the Pico SDK is properly installed and configured:

```bash
# Install dependencies
sudo apt install cmake g++ gcc-arm-none-eabi doxygen libnewlib-arm-none-eabi git python3
git clone --recurse-submodules https://github.com/raspberrypi/pico-sdk.git $HOME/pico-sdk

# Configure environment
echo "export PICO_SDK_PATH=$HOME/pico-sdk" >> ~/.bashrc
source ~/.bashrc
```

### 2. Compile Example

Once the Pico SDK is ready, clone this repository and compile the example:

```bash
git clone -b humble https://github.com/micro-ROS/micro_ros_raspberrypi_pico_sdk
cd micro_ros_raspberrypi_pico_sdk
mkdir build
cd build
cmake ..
make
```

To flash, hold the boot button, plug the USB and run:
```
cp pico_micro_ros_right_arm.uf2 /media/$USER/RPI-RP2
```

### 3. Start Micro-ROS Agent
Micro-ROS follows the client-server architecture, so you need to start the Micro-ROS Agent.
You can do so using the [micro-ros-agent Docker](https://hub.docker.com/r/microros/micro-ros-agent):
```bash
docker run -it --rm -v /dev:/dev --privileged --net=host microros/micro-ros-agent:humble serial --dev /dev/ttyACM0 -b 115200
```

### Using UART serial communication

To use the UART serial protocol instead of USB (for example, to use micro-ROS in combination with a Raspberry Pi Debug Probe), it is enough to update the `# Configure Pico` section in the `CMakeLists.txt` file as follows:

```
# Configure Pico
pico_enable_stdio_usb(pico_micro_ros_example 0)
pico_enable_stdio_uart(pico_micro_ros_example 1)
```

## What files are relevant?
- `pico_uart_transport.c`: Contains the board specific implementation of the serial transport (no change needed).
- `CMakeLists.txt`: CMake file.
- `src/main.c`: The actual ROS 2 publisher.

## How to build the precompiled library

Micro-ROS is precompiled for Raspberry Pi Pico in [`libmicroros`](libmicroros) (this directory is gitignored; generate it locally when needed).

Extra interfaces are picked up from `library_generation/extra_packages/` and `library_generation/extra_packages/extra_packages.repos`.

**Note:** The `lucy_msgs` package lives in [`lucy_ros_packages`](https://github.com/Sentience-Robotics/lucy_ros_packages) and is imported during the library build. Rebuild `libmicroros` after changing those definitions.

### Native build (no Docker)

Requires a ROS 2 Humble environment with `micro_ros_setup`, `PICO_SDK_PATH` pointing at the Pico SDK, the `arm-none-eabi-*` toolchain, and `vcs` (from ROS dev tools). From the repository root:

```bash
source /opt/ros/humble/setup.bash
cd micro_ros_raspberrypi_pico_sdk
rm -rf firmware   # optional: force a clean micro-ROS workspace
bash library_generation/library_generation.sh
```

Outputs are written under `libmicroros/` (`libmicroros.a` and `libmicroros/include/`).

### Docker build

The upstream image expects a `microros_static_library/` prefix; this repository keeps scripts under `library_generation/` at the top level, so set `MICROROS_LIBRARY_FOLDER` to `.`:

```bash
docker pull microros/micro_ros_static_library_builder:humble
docker run -it --rm -v "$(pwd)":/project -e MICROROS_LIBRARY_FOLDER=. microros/micro_ros_static_library_builder:humble
```

## How to use Pico SDK?

Here is a Raspberry Pi Pico C/C++ SDK documentation:
https://datasheets.raspberrypi.org/pico/raspberry-pi-pico-c-sdk.pdf
## Purpose of the Project

This software is not ready for production use. It has neither been developed nor
tested for a specific use case. However, the license conditions of the
applicable Open Source licenses allow you to adapt the software to your needs.
Before using it in a safety relevant setting, make sure that the software
fulfills your requirements and adjust it according to any applicable safety
standards, e.g., ISO 26262.

## License

This repository is open-sourced under the Apache-2.0 license. See the [LICENSE](LICENSE) file for details.

For a list of other open-source components included in this repository,
see the file [3rd-party-licenses.txt](3rd-party-licenses.txt).

## Known Issues/Limitations

There are no known limitations.
