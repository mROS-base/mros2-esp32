#include "cmsis_os.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

osStatus_t osDelay(uint32_t ticks)
{
  vTaskDelay(ticks / portTICK_PERIOD_MS);
  return osOK;
}

uint32_t osKernelGetTickCount(void)
{
  return xTaskGetTickCount();
}

osStatus_t osKernelStart(void)
{
  return osOK;
}

osStatus_t osMessageQueueGet(osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout)
{
  xQueueReceive(mq_id, msg_ptr, timeout);
  return osOK;
}

osMessageQueueId_t osMessageQueueNew(uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr)
{
  return xQueueCreate(msg_count, msg_size);
}

osThreadId_t osThreadNew(osThreadFunc_t func, void *argument, const osThreadAttr_t *attr)
{
  TaskHandle_t xHandle;
  xTaskCreate(func, attr->name, attr->stack_size, argument, attr->priority, &xHandle);
  return xHandle;
}

osStatus_t osThreadTerminate(osThreadId_t thread_id)
{
  vTaskDelete(thread_id);
  return osOK;
}