# mros2-esp32

mROS 2 (`mros2` as casually codename) realizes a agent-less and lightweight runtime environment compatible with ROS 2 for embedded devices.
mROS 2 mainly offers pub/sub APIs compatible with [rclcpp](https://docs.ros.org/en/rolling/p/rclcpp/index.html) for embedded devices.

mROS 2 consists of communication library for pub/sub APIs, RTPS protocol, UDP/IP stack, and real-time kernel.
This repository provides the reference implementation of mROS 2 that can be operated on the [Espressif Systems ESP32](https://www.espressif.com/en/products/socs/esp32) boards.
Please also check [mros2 repository](https://github.com/mROS-base/mros2) for more details and another implementations.

## Supported environment

- Target device: ESP32 family
  - Boards
    - For now, these boards below are confirmed to run the example on them.
      - [ESP32-S3-DevKitC-1](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/hw-reference/esp32s3/user-guide-devkitc-1.html)
    - These boards below are also confirmed by the development team, but not always supported in the latest version (due to our development resources,,,).
      - [M5Stack Basic](http://docs.m5stack.com/en/core/basic)
      - [M5Stack Core2](http://docs.m5stack.com/en/core/core2)
      - [M5Stack CoreS3](http://docs.m5stack.com/en/core/CoreS3)
    - These boards were confirmed to operate by our friendly users (any PRs are welcome to add this list based on your experience!!)
      - [Seeed Studio XIAO ESP32C3](https://www.seeedstudio.com/Seeed-XIAO-ESP32C3-p-5431.html) (see [#7](https://github.com/mROS-base/mros2-esp32/issues/7))
      - [ESP32-C6-DevKitC-1](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c6/esp32-c6-devkitc-1/user_guide.html) (see [#21](https://github.com/mROS-base/mros2-esp32/issues/21))
      - [Seeed Studio XIAO ESP32C6](https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C6-p-5884.html) (see [#23](https://github.com/mROS-base/mros2-esp32/issues/23))
      - [Seeed Studio XIAO ESP32S3](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html) (see [#24](https://github.com/mROS-base/mros2-esp32/issues/24))
      - [M5StickC Plus2](https://docs.m5stack.com/en/core/M5StickC%20PLUS2) (see [#31](https://github.com/mROS-base/mros2-esp32/issues/31))
  - SDK: [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/index.html)
  - Kernel: [ESP-IDF FreeRTOS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos_idf.html)
- Host environment
  - [ROS 2 Humble Hawksbill](https://docs.ros.org/en/humble/index.html) on Ubuntu 22.04 LTS
- Network setting
  - Make sure both the device and the host are connected to the same network.
  - IP address needs to be assigned to the device by DHCP. We have not confirmed the operation using static IP setting yet. So you may not un-comment the `#define STATIC_IP` line in `platform/wifi/wifi.h`.
  - Please prepare the Wi-Fi router that provides 2.4 GHz band.
    - Most of ESP32 only support 2.4 GHz.
    - Note that you need to set up a dedicated SSID at 2.4 GHz. If the SSID has a band steering setting (that shares 2.4 GHz and 5 GHz), the communication of ESP32 may be disconnected during the operation.
  - The firewall on the host (Ubuntu) needs to be disabled for ROS 2 (DDS) communication (e.g. `$ sudo ufw disable`).
  - If the host is connected to the Internet with other network adapters, communication with mros2 may not work properly. In that case, please turn off them.

## Setup for development environment

First, please install ESP-IDF as the toolchain for ESP32 family.
We recommend to install it followed "Maunal Installation".  
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#manual-installation

Currently, we checked the operation of basic sapmles with [esp-idf v5.1.1](https://github.com/espressif/esp-idf/releases/tag/v5.1.1).

Building mros2 library requires [Jinja2](https://pypi.org/project/Jinja2/) (to generate `platform/templates.hpp` automatically). So please install this as the below.

```
$ pip install -U Jinja2
```

## Quickstart only with this repository

This repository contains mros2 libarary with its related implementations for ESP32, and some examples in [`workspace/`](workspace/).
IOW, this repository is all you need to try it out about the power of mros2-esp32 right away!!  
This sections describes the quickstart with `workspace/echoback_string` as the examples.

You can also use this repositoy as a component in your own ESP-IDF project.
If you want to do so, please refer to [Usage into your own ESP-IDF project](#usage-into-your-own-esp-idf-project) in the next section.

### git clone

Please `git clone` this repository with `--recursive` (mandatory).

```
git clone --recursive https://github.com/mROS-base/mros2-esp32.git
cd mros2-esp32
```

Note that you cannot change the directory name from `mros2-esp32` since it is used as the component name in `CMakeLists.txt`.

### Setup your SSID and PASS

Please setup SSID and PASS for your Wi-Fi AP in `platform/wifi/wifi.h` (be careful that we should not commit and push your network environment to the world :D)

```platform/wifi/wifi.h
#define ESP_WIFI_SSID "SSID"
#define ESP_WIFI_PASS "PASS"
```

Again, make sure that its SSID assigns IP by DHCP and is dedicated to 2.4 GHz band.

### Set target

Go to `workspace/echoback_string/` and do the below to setup the target device.
You need to adjust `<target>` arg for your device (e.g., M5Stack Basic and Core2 for `esp32`, ESP32S3Dev and M5Stack CoreS3 for `esp32s3`)

```
cd workspace/echoback_string
idf.py set-target esp32
```

Next, you need to disable IPv6 connection for lwIP, since RTPS communication cannot work well when it is enabled.
Please do `idf.py menuconfig`, move to "Component config" -> "LWIP" -> "Enable IPv6" and  --->" and type Space to disable it.

The below image is from [@tasada038](https://github.com/tasada038)'s article: 「[mros2-esp32とM5Stackでサンプルプログラムを試す](https://zenn.dev/tasada038/articles/fdbf3e5ff7cd01)」

[![](https://storage.googleapis.com/zenn-user-upload/667047c679bb-20230606.png)](https://zenn.dev/tasada038/articles/fdbf3e5ff7cd01#mros2-esp32%E3%81%AE%E3%82%B5%E3%83%B3%E3%83%97%E3%83%AB%E5%AE%9F%E8%A1%8C)

If you are afraid to fiddle with this screen, you can skip this step because disabling IPv6 will be disabled automatically during the build process.
However, you need to run the build twice in a row for proper configuration in this case.

### build, flash, and run!

Please build the project as the below command.

```
idf.py build
```

When the build completed successfully, a binary is generated in `build/echoback_string.bin`.

Connect the device to the host via USB cable, and flash the binary to it.
The port `/tty/ttyUSB0` may be adjusted according to your target board and development environment.

```
idf.py -p /tty/ttyUSB0 flash
```

Finally, ron-yori-Run!  
You can observe the serial terminal by [IDF Monitor](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/tools/idf-monitor.html) 
(quit is `Ctrl + ]`).

```
$ idf.py -p /tty/ttyUSB0 monitor
Executing action: monitor
Running idf_monitor in directory /home/hogehoge/mros2-esp32/workspace/echoback_string
...(SNIPPED)...
I (2208) esp_netif_handlers: sta ip: 192.168.11.102, mask: 255.255.255.0, gw: 192.168.11.1
I (2208) wifi station: got ip:192.168.11.102
I (2208) wifi station: connected to ap SSID:SSID password:PASS
LOG_DEBUG : 00000000.182 : [MROS2LIB] set "192.168.11.102" for RTPS communication
LOG_NOTICE : 00000000.182 : successfully connect and setup network
---
LOG_NOTICE : 00000000.183 : mros2-esp32 start!
LOG_NOTICE : 00000000.183 : app name: echoback_string
LOG_DEBUG : 00000000.184 : [MROS2LIB] mros2_init task start
LOG_DEBUG : 00000000.184 : [MROS2LIB] Initilizing lwIP complete
LOG_DEBUG : 00000000.185 : mROS 2 initialization is completed
LOG_DEBUG : 00000000.186 : [MROS2LIB] create_node
LOG_DEBUG : 00000000.186 : [MROS2LIB] start creating participant
LOG_DEBUG : 00000000.187 : [MROS2LIB] successfully created participant
LOG_DEBUG : 00000000.187 : [MROS2LIB] create_publisher complete.
LOG_DEBUG : 00000000.188 : [MROS2LIB] create_subscription complete.
LOG_DEBUG : 00000000.195 : [MROS2LIB] Initilizing Domain complete
LOG_NOTICE : 00000000.198 : ready to pub/sub message
---
LOG_NOTICE : 00000000.198 : publishing msg: 'Hello from mros2-esp32 onto "ESP32": 0'
LOG_NOTICE : 00000000.298 : publishing msg: 'Hello from mros2-esp32 onto "ESP32": 1'
LOG_NOTICE : 00000000.398 : publishing msg: 'Hello from mros2-esp32 onto "ESP32": 2'
LOG_NOTICE : 00000000.498 : publishing msg: 'Hello from mros2-esp32 onto "ESP32": 3'
...(SNIPPED)...
```

You can confirm proper connection with your AP (SSID and PASS), and gotten IP address that will also be set for RTPS communication.

To confirm the operation of this echoback_string example, please operate [mros2-host-examples/mros2_echoreply_string](https://github.com/mROS-base/mros2-host-examples#mros2_echoreply_string) node on the ROS 2 host as the below.

```
$ ros2 run mros2_echoreply_string echoreply_node
[INFO] [1695193182.117751738] [mros2_echoreply_node]: 
Subscribed msg: 'Hello from mros2-esp32 onto "ESP32": 11'
[INFO] [1695193182.117877196] [mros2_echoreply_node]: 
Publishing msg: 'Hello from mros2-esp32 onto "ESP32": 11'
[INFO] [1695193183.115781171] [mros2_echoreply_node]: 
Subscribed msg: 'Hello from mros2-esp32 onto "ESP32": 12'
[INFO] [1695193183.115852751] [mros2_echoreply_node]: 
Publishing msg: 'Hello from mros2-esp32 onto "ESP32": 12'
[INFO] [1695193184.160837237] [mros2_echoreply_node]: 
Subscribed msg: 'Hello from mros2-esp32 onto "ESP32": 13'
[INFO] [1695193184.160930132] [mros2_echoreply_node]: 
Publishing msg: 'Hello from mros2-esp32 onto "ESP32": 13'
[INFO] [1695193185.185828052] [mros2_echoreply_node]: 
Subscribed msg: 'Hello from mros2-esp32 onto "ESP32": 14'
[INFO] [1695193185.185916568] [mros2_echoreply_node]: 
Publishing msg: 'Hello from mros2-esp32 onto "ESP32": 14'
...(SNIPPED)...
```

After that, mros2-esp32 and ROS 2 host can be connected directly via RTPS!

```
...(SNIPPED)...
LOG_NOTICE : 00000001.245 : publishing msg: 'Hello from mros2-esp32 onto "ESP32": 9'
LOG_NOTICE : 00000001.345 : publishing msg: 'Hello from mros2-esp32 onto "ESP32": 10'
LOG_DEBUG : 00000001.397 : [MROS2LIB] publisher matched with remote subscriber
LOG_NOTICE : 00000001.445 : publishing msg: 'Hello from mros2-esp32 onto "ESP32": 11'
LOG_NOTICE : 00000001.446 : subscribed msg: 'Hello from mros2-esp32 onto "ESP32": 11'
LOG_NOTICE : 00000001.545 : publishing msg: 'Hello from mros2-esp32 onto "ESP32": 12'
LOG_NOTICE : 00000001.545 : subscribed msg: 'Hello from mros2-esp32 onto "ESP32": 12'
LOG_DEBUG : 00000001.611 : [MROS2LIB] subscriber matched with remote publisher
LOG_NOTICE : 00000001.645 : publishing msg: 'Hello from mros2-esp32 onto "ESP32": 13'
LOG_NOTICE : 00000001.650 : subscribed msg: 'Hello from mros2-esp32 onto "ESP32": 13'
LOG_NOTICE : 00000001.745 : publishing msg: 'Hello from mros2-esp32 onto "ESP32": 14'
LOG_NOTICE : 00000001.755 : subscribed msg: 'Hello from mros2-esp32 onto "ESP32": 14'
...(SNIPPED)...
```

### Examples

This repository contains some example applications in [workspace/](workspace/) to communicate with ROS 2 nodes on the host.

The followings are the basic communication examples to the host.
The description and host operation of them are almost the same with [mros2-mbed#Examples](https://github.com/mROS-base/mros2-mbed#examples) (link is to mros2-mbed ripository).
Please also check [mROS-base/mros2-host-examples](https://github.com/mROS-base/mros2-host-examples) repository for more detail about the host examples.

- [echoback_string](https://github.com/mROS-base/mros2-mbed#echoback_string-default)
- [echoreply_string](https://github.com/mROS-base/mros2-mbed#echoreply_string)
- [pub_float32](https://github.com/mROS-base/mros2-mbed#pub_float32)
- [pub_twist](https://github.com/mROS-base/mros2-mbed#pub_twist)
- [sub_pose](https://github.com/mROS-base/mros2-mbed#sub_pose)
- [sub_uint16](https://github.com/mROS-base/mros2-mbed#sub_uint16)

The followings are under development and not confirmed the proper operation yet (also see [Issue#14](https://github.com/mROS-base/mros2-esp32/issues/14))

- [pub_image](https://github.com/mROS-base/mros2-mbed#pub_image)
- [pub_long_string_sub_crc](https://github.com/mROS-base/mros2-mbed#pub_long_string_sub_crc)

The followings is for M5Stack device.
You need to do `git clone` [M5Unified](https://github.com/m5stack/M5Unified) and [M5GFX](https://github.com/m5stack/M5GFX) in `components/`, and use ESP-IDF v4.4.4 to try this sample due to the compatibility of these libraries.

- m5stack_sample

## Usage into your own ESP-IDF project

We are sure that you definiately want to use mros2-esp32 into your onw ESP-IDF project!

This section introduce how to realize it, assuming the project name is "hello_mros2" and the location is `~/esp/`.

### Create your own project

Go to your own location and create the `hello_mros2` project.

```
cd ~/esp
idf.py create-project hello_mros2
cd hello_mros2
```

### Clone mros2-esp32

First, create `./components` and do `git clone` into it (`--recursive` is mandatory).

```
mkdir components
cd components/
git clone --recursive https://github.com/mROS-base/mros2-esp32
```

### Change file type of source code

You need to change filename (.ext) from `main/hello_mros2.c` to `main/hello_mros2.cpp` because you will use mros2 C++ APIs.

```
mv main/hello_mros2.c main/hello_mros2.cpp
```

### Edit CMakeLists.txt

You need to edit `./CMakeLists.txt` and `./main/CMakeLists.txt` as the below.

- `./CMakeLists.txt`  
  ```
  cmake_minimum_required(VERSION 3.16)
  
  add_compile_options(-w)  # add
  
  include($ENV{IDF_PATH}/tools/cmake/project.cmake)
  project(hello_mros2)
  ```
  - This is due to avoid build error about `-Werror=format` in mros2-esp32 logging functions. See [#Issue16](https://github.com/mROS-base/mros2-esp32/issues/16) for details.
- `./main/CMakeLists.txt`
  ```
  idf_component_register(SRCS "hello_mros2.cpp"  # edit
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES "mros2-esp32")  # add
  ```

### Write your mros2 application

The fastest way is to copy from [./workspace/echoback_string/main/echoback_string.cpp](https://github.com/mROS-base/mros2-esp32/blob/main/workspace/echoback_string/main/echoback_string.cpp) :D

```
cd ~/esp/hello_mros2
cp components/mros2-esp32/workspace/echoback_string/main/echoback_string.cpp main/hello_mros2.cpp 
```

### Setup your SSID and PASS in mros2 lib

You need to SSID and PASS for your Wi-Fi AP in `components/mros2-esp32/platform/wifi/wifi.h` (be careful that we should not commit and push your network environment to the world :D)

```platform/wifi/wifi.h
#define ESP_WIFI_SSID "SSID"
#define ESP_WIFI_PASS "PASS"
```

### Then, set target, build, flash, and Run!!

The rest of operations follow from [this subsection on Quickstart](#set-target).

If you want to use your own customized message type followed by the ROS 2 manner, please refer to [mros2#generating-header-files-for-custom-msgtypes](https://github.com/mROS-base/mros2#generating-header-files-for-custom-msgtypes) section.

Enjoy your mros2-esp32 development life!! :tada:  

## Submodules and Licenses

The source code of this repository itself is published under [Apache License 2.0](https://github.com/mROS-base/mros2/blob/main/LICENSE).  
Please note that this repository requires the following stacks as the submodules, and also check their Licenses.

- [mros2](https://github.com/mROS-base/mros2): the pub/sub APIs compatible with ROS 2 Rclcpp
  - [embeddedRTPS](https://github.com/mROS-base/embeddedRTPS): RTPS communication layer (including lwIP and Micro-CDR)
- [ESP-IDF and FreeRTOS](https://github.com/espressif/esp-idf): Espressif IoT Development Framework. Official development framework for Espressif SoCs.

## Awesome resources!

The following are trial reports written by third-party users. We deeply appreciate your contributions! Of course, PR for adding your reports/articles, example of works are very welcome!!

- [@tasada038](https://github.com/tasada038): 「[mros2-esp32とM5Stackでサンプルプログラムを試す](https://zenn.dev/tasada038/articles/fdbf3e5ff7cd01)」
- [@Ar-Ray-code](https://github.com/Ar-Ray-code): 「[mros2-esp32をDocker内でビルドする](https://ar-ray.hatenablog.com/entry/2023/06/10/235333)」
