#include "lwip.h"
#include "lwipopts.h"
#include "cmsis_os.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <stdio.h>

static SemaphoreHandle_t xMutex = NULL;

void MX_LWIP_Init(void)
{
  xMutex = xSemaphoreCreateMutex();
  return;
}

void sys_lock_tcpip_core(void)
{
  xSemaphoreTake(xMutex, portMAX_DELAY);
  return;
}

void sys_unlock_tcpip_core(void)
{
  xSemaphoreGive(xMutex);
  return;
}
