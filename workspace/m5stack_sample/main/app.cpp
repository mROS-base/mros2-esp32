/* mros2 example
 * Copyright (c) 2022 mROS-base
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
#include "std_msgs/msg/string.hpp"

#include "cmsis_os.h"
#include "wifi.h"

#include "M5Unified.h"
/* convert TARGET_NAME to put into message */
#define quote(x) std::string(q(x))
#define q(x) #x

void userCallback(std_msgs::msg::String *msg)
{
  printf("subscribed msg: '%s'\r\n", msg->data.c_str());
  M5.Lcd.printf("subscribed msg: '%s'\r\n", msg->data.c_str());
}

extern "C" void app_main(void)
{
  init_wifi();
  osKernelStart();

  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("mbed mros2 start!\r\n");
  M5.Lcd.printf("app name: m5stack_sample\r\n");

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
    msg.data = "Hello from mros2-mbed onto " + quote(TARGET_NAME) + ": " + std::to_string(count++);
    printf("publishing msg: '%s'\r\n", msg.data.c_str());
    pub.publish(msg);
    osDelay(1000);
  }

  mros2::spin();
  return;
}