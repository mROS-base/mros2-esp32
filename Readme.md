# mros2-esp32
mROS 2 (formally `mros2`) realizes a agent-less and lightweight runtime environment compatible with ROS 2 for embedded devices.
mROS 2 mainly offers pub/sub APIs compatible with [rclcpp](https://docs.ros.org/en/rolling/p/rclcpp/index.html) for embedded devices.

mROS 2 consists of communication library for pub/sub APIs, RTPS protocol, UDP/IP stack, and real-time kernel.
This repository provides the reference implementation of mROS 2 that can be operated on the Mbed enabled board.
Please also check [mros2 repository](https://github.com/mROS-base/mros2) for more details and another implementations.

## Supported environment
- ESP32-S3-DevKitC-1
- M5Stack Basic

# Getting Started

## install esp-idf
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html

## clone and settings

```
git clone https://github.com/mROS-base/mros2-esp32.git
cd mros2-esp32
```
Change WiFi SSID/Pass and IP address
- /main/include/wifi.h

Change IP address
- /components/include/rtps/config.h
- /components/include/netif.h

## build sample application
```
cd workspace/[sample application]/
idf.py menuconfig  

 /* in menuconfig */  
  Component config -> LWIP -> IPv6 ->   

  /*Disable IPv6*/
  - [ ] IPv6 support (Disable)  
 /* Save and Quit menuconfig */

idf.py build
idf.py -p [PORT] flash
idf.py -p [PORT] monitor
```
