#ifndef _CMSIS_IMPL_LOGGER_H_
#define _CMSIS_IMPL_LOGGER_H_

// #include "freertos_conversion.h"
#include "cmsis_impl_types.h"

#ifdef CMSIS_LOG_DISABLE_DEBUG
#else
#include <stdio.h>
#define syslog(flg, ...)                                               \
	do                                                                   \
	{                                                                    \
		uint32_t _tick = osKernelGetTickCount();                           \
		printf("%s : %08u.%03u : ", #flg, (_tick / 1000), (_tick % 1000)); \
		printf(__VA_ARGS__);                                               \
		printf("\n");                                                      \
	} while (0)
#endif

/*
 * CMSIS LOG API
 */
#ifdef CMSIS_LOG_DISABLE_DEBUG
#define CMSIS_IMPL_DEBUG(...)
#else
#define CMSIS_IMPL_DEBUG(...) syslog(LOG_DEBUG, __VA_ARGS__)
#endif

#ifdef CMSIS_LOG_DISABLE_INFO
#define CMSIS_IMPL_INFO(...)
#else
#define CMSIS_IMPL_INFO(...) syslog(LOG_NOTICE, __VA_ARGS__)
#endif

#ifdef CMSIS_LOG_DISABLE_WARN
#define CMSIS_IMPL_WARN(...)
#else
#define CMSIS_IMPL_WARN(...) syslog(LOG_WARNING, __VA_ARGS__)
#endif

#ifdef CMSIS_LOG_DISABLE_ERROR
#define CMSIS_IMPL_ERROR(...)
#else
#define CMSIS_IMPL_ERROR(...) syslog(LOG_ERROR, __VA_ARGS__)
#endif

#ifdef CMSIS_LOG_DISABLE_FATAL
#define CMSIS_IMPL_FATAL(...)
#else
#define CMSIS_IMPL_FATAL(...) syslog(LOG_EMERG, __VA_ARGS__)
#endif

#endif /* _CMSIS_IMPL_LOGGER_H_ */
