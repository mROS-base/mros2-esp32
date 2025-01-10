/*
 * NOTE:
 *   This file is copied from esp-idf examples as the below, and modified for usage of mros2-esp32.
 *   https://github.com/espressif/esp-idf/blob/master/examples/ethernet/basic/main/ethernet_example_main.c
 *   Therefore, mROS-base org inherits the Public Domain (or CC0) LICENCE for this file from the original file.
 */

#define ETHERNET_CONNECTED_BIT BIT0
#define ETHERNET_FAIL_BIT BIT1

/*
 * Caution:
 *   We have not tested the operation using STATIC_IP setting yet.
 *   So you may not un-comment the below line to use DHCP setting
 */

#ifdef __cplusplus
extern "C" {
#endif
extern void init_ethernet(void);
uint32_t get_mros2_ip_addr_eth(void);
#ifdef __cplusplus
}
#endif
