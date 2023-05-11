// #include <stdio.h>
// #include "mros2.h"

// extern "C" void app_main(void)
// {
//   mros2::init(0, NULL);
// }

#include "mros2.h"
#include "std_msgs/msg/string.hpp"

#include "cmsis_os.h"
#include "wifi.h"

#include <stdio.h>
#include <string.h>
// #include "M5Unified.hpp"

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
  // auto cfg = M5.config();
  // M5.begin(cfg);
  // M5.Lcd.setTextSize(2);
  // M5.Lcd.println("Press BtnA");

  printf("mbed mros2 start!\r\n");
  printf("app name: echoback_string\r\n");
  mros2::init(0, NULL);
  MROS2_DEBUG("mROS 2 initialization is completed\r\n");

  mros2::Node node = mros2::Node::create_node("mros2_node");
  mros2::Publisher pub = node.create_publisher<std_msgs::msg::String>("to_linux", 10);
  // mros2::Subscriber sub = node.create_subscription<std_msgs::msg::String>("to_stm", 10, userCallback);

  osDelay(100);
  MROS2_INFO("ready to pub/sub message\r\n");

  auto count = 0;
  while (1)
  {
    auto msg = std_msgs::msg::String();
    msg.data = "Hello from mros2-mbed : " + std::to_string(count++);
    printf("publishing msg: '%s'\r\n", msg.data.c_str());
    pub.publish(msg);
    osDelay(1000);
  }

  mros2::spin();
  return;
}
