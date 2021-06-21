#ifndef __MACROLOGGER_H__
#define __MACROLOGGER_H__

// #define LOG_LEVEL TRACE_LEVEL

#include <stdio.h>
#include <string.h>

#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

#define NO_LOG          0x00
#define ERROR_LEVEL     0x01
#define INFO_LEVEL      0x02
#define WARNING_LEVEL   0x03
#define DEBUG_LEVEL     0x04
#define TRACE_LEVEL     0x05

#ifndef LOG_LEVEL
#define LOG_LEVEL   TRACE_LEVEL
#endif

#define PRINTFUNCTION(format, ...)      fprintf(stderr, format, __VA_ARGS__ )

#define LOG_FMT             "%s | %-13s | %20s:%3d | "
#define LOG_ARGS(LOG_TAG)   LOG_TAG, _FILE, __func__, __LINE__

#define ERROR_TAG   "E"
#define INFO_TAG    "I"
#define WARNING_TAG "W"
#define DEBUG_TAG   "D"
#define TRACE_TAG   "T"

#define NEW_LINE "\n"

#if LOG_LEVEL >= TRACE_LEVEL
#define LOG_TRACE(message, ...) \
PRINTFUNCTION(LOG_FMT message NEW_LINE, LOG_ARGS(TRACE_TAG), __VA_ARGS__ )
#else
#define LOG_TRACE(message, ...)
#endif

#if LOG_LEVEL >= DEBUG_LEVEL
#define LOG_DEBUG(message, ...) \
PRINTFUNCTION(LOG_FMT message NEW_LINE, LOG_ARGS(DEBUG_TAG), __VA_ARGS__ )
#else
#define LOG_DEBUG(message, ...)
#endif

#if LOG_LEVEL >= WARNING_LEVEL
#define LOG_WARNING(message, ...) \
PRINTFUNCTION(LOG_FMT message NEW_LINE, LOG_ARGS(WARNING_TAG), __VA_ARGS__ )
#else
#define LOG_WARNING(message, ...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define LOG_INFO(message, ...) \
PRINTFUNCTION(LOG_FMT message NEW_LINE, LOG_ARGS(INFO_TAG), __VA_ARGS__ )
#else
#define LOG_INFO(message, ...)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
#define LOG_ERROR(message, ...) \
PRINTFUNCTION(LOG_FMT message NEW_LINE, LOG_ARGS(ERROR_TAG), __VA_ARGS__ )
#else
#define LOG_ERROR(message, ...)
#endif

#if LOG_LEVEL > NO_LOGS
#define LOG_IF_ERROR(condition, message, ...) \
if (condition) \
PRINTFUNCTION(LOG_FMT message NEW_LINE, LOG_ARGS(ERROR_TAG), __VA_ARGS__ )
#else
#define LOG_IF_ERROR(condition, message, ...)
#endif

#endif
