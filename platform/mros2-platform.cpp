/* target dependent procedure for mros2-mbed
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

/* NOTE: 
 *   this file has not been implemented and used yet
 */

#include "mros2.h"
#include "mros2-platform.h"

#include "cmsis_os.h"
#include "wifi.h"


namespace mros2_platform
{

/*
 *  Setup network I/F
 */
esp_err_t network_connect(void)
{
  init_wifi();
  osKernelStart();
  osDelay(10000);

  /*
  SocketAddress socketAddress;
  network.get_ip_address(&socketAddress);
  const char* ip_address = socketAddress.get_ip_address();
  printf("  IP Address: %s\r\n", ip_address);
  */

  /* convert IP address to be used in rtps/config.h */
  //std::array<uint8_t, 4> ipaddr;
  //sscanf(ip_address, "%d.%d.%d.%d", &ipaddr[0], &ipaddr[1], &ipaddr[2], &ipaddr[3]);
  //std::array<uint8_t, 4> ipaddr = { 192, 168, 11, 104 };

  //mros2::setIPAddrRTPS(ipaddr);

  //return result;
}

}  /* namespace mros2_platform */
