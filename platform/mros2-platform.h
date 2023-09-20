#ifndef MROS2_PLATFORM_H
#define MROS2_PLATFORM_H

#define MROS2_PLATFORM_NAME "mros2-esp32"
#define TARGET_NAME "ESP32"

#include "cmsis_os.h"
#include "wifi.h"

/* convert TARGET_NAME to put into message */
#define quote(x) std::string(q(x))
#define q(x) #x


/* NOTE: this function has not been implemented and used yet */
extern "C" esp_err_t mros2_platform_network_connect(void);


#endif /* MROS2_PLATFORM_H */