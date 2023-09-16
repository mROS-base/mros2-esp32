#ifndef MROS2_PLATFORM_H
#define MROS2_PLATFORM_H

#define MROS2_PLATFORM_NAME "mros2-esp32"
#define TARGET_NAME "ESP32"

/* convert TARGET_NAME to put into message */
#define quote(x) std::string(q(x))
#define q(x) #x


/* NOTE: this function has not been implemented and used yet */
namespace mros2_platform
{

esp_err_t network_connect(void);

}  /* namespace mros2_platform */

#endif /* MROS2_PLATFORM_H */