/* mros2 example
 * Copyright (c) 2023 mROS-base
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mros2.h"
#include "mros2-platform.h"
#include "std_msgs/msg/string.hpp"

#include "cmsis_os.h"
#include "wifi.h"


void userCallback(std_msgs::msg::String *msg)
{
  printf("subscribed msg: '%s'\r\n", msg->data.c_str());
}

extern "C" void app_main(void)
{
  printf("mbed mros2 start!\r\n");
  printf("app name: echoback_string\r\n");

  /* connect to the network, but not be used yet */
  //mros2_platform::network_connect();

  init_wifi();
  osKernelStart();

  /* get mros2 IP address and set it to RTPS */
  std::array<uint8_t, 4> ipaddr;
  uint8_t mros2_ip_addr_octet[4];
  get_mros2_ip_addr(mros2_ip_addr_octet);
  for (int i = 0; i < 4; i++)
    ipaddr[i] = mros2_ip_addr_octet[i];
  
  MROS2_INFO("set mros2 IP address to RTPS: %d.%d.%d.%d\r\n", ipaddr[0], ipaddr[1], ipaddr[2], ipaddr[3]);
  mros2::setIPAddrRTPS(ipaddr);

  mros2::init(0, NULL);
  MROS2_DEBUG("mROS 2 initialization is completed\r\n");

  mros2::Node node = mros2::Node::create_node("mros2_node");
  mros2::Publisher pub = node.create_publisher<std_msgs::msg::String>("to_linux", 10);
  mros2::Subscriber sub = node.create_subscription<std_msgs::msg::String>("to_stm", 10, userCallback);

  osDelay(100);
  MROS2_INFO("ready to pub/sub message\r\n");

  auto count = 0;
  while (1)
  {
    auto msg = std_msgs::msg::String();
    msg.data = "Hello from " + std::string(MROS2_PLATFORM_NAME) + " onto " + quote(TARGET_NAME) + ": " + std::to_string(count++);
    printf("publishing msg: '%s'\r\n", msg.data.c_str());
    pub.publish(msg);
    osDelay(1000);
  }

  mros2::spin();
  return;
}