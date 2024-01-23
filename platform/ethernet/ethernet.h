
#include <stdint.h>
#include "sdkconfig.h"

#ifdef CONFIG_M_ROS_ESP_NETIF_ENET

/*
 * NOTE:
 *   This file is copied from esp-idf examples as the below, and modified for usage of mros2-esp32.
 *   https://github.com/espressif/esp-idf/blob/master/examples/wifi/getting_started/station/main/station_example_main.c
 *   Therefore, mROS-base org inherits the Public Domain (or CC0) LICENCE for this file from the original file.
 */

#define ETHERNET_CONNECTED_BIT BIT0
#define ETHERNET_FAIL_BIT BIT1

/*
 * Caution:
 *   We have not tested the operation using STATIC_IP setting yet.
 *   So you may not un-comment the below line to use DHCP setting
 */
// #define STATIC_IP
#ifdef STATIC_IP
#define NETIF_IPADDR "192.168.11.107"
#define NETIF_NETMASK "255.255.255.0"
#define NETIF_GW "192.168.11.1"
#endif
#ifdef __cplusplus
extern "C"
{
#endif
    extern void init_network(void);
    uint32_t get_mros2_ip_addr(void);
#ifdef __cplusplus
}
#endif

#endif // CONFIG_M_ROS_ESP_NETIF_ENET
