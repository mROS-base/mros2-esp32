// #include <stdio.h>
// #include "mros2.h"

// extern "C" void app_main(void)
// {
//   mros2::init(0, NULL);
// }

#include "mros2.h"
#include "std_msgs/msg/string.hpp"

#include "cmsis_os.h"
#include "netif.h"
#include "wifi.h"

#include <stdio.h>
#include <string.h>

mros2::Subscriber sub;
mros2::Publisher pub;

void userCallback(std_msgs::msg::String *msg)
{
  printf("subscribed msg: '%s'\r\n", msg->data.c_str());
  printf("publishing msg: '%s'\r\n", msg->data.c_str());
  pub.publish(*msg);
}

extern "C" void app_main(void)
{
  // maybe need to initialize wifi
  // netif_posix_add(NETIF_IPADDR, NETIF_NETMASK);
  init_wifi();

  osKernelStart();

  printf("mros2-posix start!\r\n");
  printf("app name: echoreply_string\r\n");
  mros2::init(0, NULL);
  MROS2_DEBUG("mROS 2 initialization is completed\r\n");

  mros2::Node node = mros2::Node::create_node("mros2_node");
  pub = node.create_publisher<std_msgs::msg::String>("to_linux", 10);
  sub = node.create_subscription<std_msgs::msg::String>("to_stm", 10, userCallback);
  vTaskDelay(100);
  MROS2_INFO("ready to pub/sub message\r\n");

  mros2::spin();
}

