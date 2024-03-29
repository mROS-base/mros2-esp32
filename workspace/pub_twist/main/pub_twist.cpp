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
#include "geometry_msgs/msg/vector3.hpp"
#include "geometry_msgs/msg/twist.hpp"


extern "C" void app_main(void)
{
  /* connect to the network */
  if (mros2_platform_network_connect())
  {
    MROS2_INFO("successfully connect and setup network\r\n---");
  }
  else
  {
    MROS2_ERROR("failed to connect and setup network! aborting,,,");
    return;
  }

  MROS2_INFO("mbed mros2 start!");
  MROS2_INFO("app name: pub_twist");

  mros2::init(0, NULL);
  MROS2_DEBUG("mROS 2 initialization is completed");

  mros2::Node node = mros2::Node::create_node("mros2_node");
  mros2::Publisher pub = node.create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  osDelay(100);
  MROS2_INFO("ready to pub/sub message\r\n---");

  geometry_msgs::msg::Vector3 linear;
  geometry_msgs::msg::Vector3 angular;
  geometry_msgs::msg::Twist twist;

  auto publish_count = 0;
  while (1)
  {
    linear.x = publish_count/1.0;
    linear.y = publish_count/1.0;
    linear.z = publish_count/1.0;  
    angular.x = publish_count/1.0;
    angular.y = publish_count/1.0;
    angular.z = publish_count/1.0;
    twist.linear = linear;
    twist.angular = angular;
    MROS2_INFO("publishing Twist msg!!");
    pub.publish(twist);
    publish_count++;
    osDelay(1000);
  }

  mros2::spin();
  return;
}