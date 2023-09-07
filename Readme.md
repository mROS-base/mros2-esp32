# mros2-esp32
mROS 2 (formally `mros2`) realizes a agent-less and lightweight runtime environment compatible with ROS 2 for embedded devices.
mROS 2 mainly offers pub/sub APIs compatible with [rclcpp](https://docs.ros.org/en/rolling/p/rclcpp/index.html) for embedded devices.

mROS 2 consists of communication library for pub/sub APIs, RTPS protocol, UDP/IP stack, and real-time kernel.
This repository provides the reference implementation of mROS 2 that can be operated on the Mbed enabled board.
Please also check [mros2 repository](https://github.com/mROS-base/mros2) for more details and another implementations.

## Supported environment
- ESP32-S3-DevKitC-1
- M5Stack Basic
- M5Stack Core2
- M5Stack CoreS3
- XIAO ESP32C3 (see [#7](https://github.com/mROS-base/mros2-esp32/issues/7))

# Quickstart by this repository itself

## install esp-idf
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html


After install esp-idf, you need to install jinja2 library in esp-idf environment.

## git clone and settings
```
git clone --recursive https://github.com/mROS-base/mros2-esp32.git
cd mros2-esp32
```
### Change WiFi SSID/Pass
Change ESP_WIFI_SSID and ESP_WIFI_PASS in ```/workspace/common/wifi/wifi.h```.

### Change IP address
Change IP address in ```/include/rtps/config.h```.

When using DHCP, it is also necessary to specify the IP address.
Flash the app and check the IP address from startup log.
After that chenge the IP address in ```config.h``` and rebuild it.

## Examples
This repository contains some example applications in [workspace/](workspace/) to communicate with ROS 2 nodes on the host.
Of course you can also create a new program file and specify it as your own application.

Please also check [mROS-base/mros2-host-examples](https://github.com/mROS-base/mros2-host-examples) repository for more detail about the host examples.

Currently, the following examples are available.
- echoback_string
- echoreply_string
- pub_float32
- pub_twist
- sub_pose
- sub_uint16
- m5stack_sample

M5Stack_sample project needs [M5Unified](https://github.com/m5stack/M5Unified) and [M5GFX](https://github.com/m5stack/M5GFX) libraries.  
Git clone these libraries to ```common/``` directory.


The following examples are under development. untested.
- pub_image
- pub_long_string_sub_crc


## build Examples
```
cd workspace/[Example]/

/* M5Stack Basic / M5Stack Core2 */
idf.py set-target esp32

/* ESP32S3Dev / M5Stack CoreS3 */
idf.py set-target esp32s3

idf.py menuconfig  

 /* in menuconfig */  
  Component config -> LWIP -> IPv6 ->   

  /*Disable IPv6*/
  - [ ] IPv6 support (Disable)  
 /* Save and Quit menuconfig */

idf.py build

/* If an error occurs, try the following*/
  python -m pip install jinja2
/* --- */

idf.py -p [PORT] flash

idf.py -p [PORT] monitor
/* To exit monitor, press Ctrl + ] */
```
# Usage into your ESP-IDF project
If you needs to use mros2 into your ESP-IDF project, 
clone this repository to ```components``` directory in your project.

mros2 needs network connection and setting of IP address.
Please see [Wifi connection example](workspace/common/wifi).
IP address setting find in upper section [Change IP address](#change-ip-address).
