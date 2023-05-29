#include "esp_wifi_types.h"

#define ESP_WIFI_SSID "SSID"
#define ESP_WIFI_PASS "PASS"
#define ESP_MAXIMUM_RETRY 3
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1

// #define STATIC_IP
#ifdef STATIC_IP
#define NETIF_IPADDR "192.168.11.107"
#define NETIF_NETMASK "255.255.255.0"
#define NETIF_GW "192.168.11.1"
#endif
#ifdef __cplusplus
extern "C" {
#endif
extern void init_wifi(void);
#ifdef __cplusplus
}
#endif
