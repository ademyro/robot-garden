#include <stdio.h>
#include <stdarg.h>

#include "log/log.h"

void debugLog(const char *msg, ...) {
  va_list args;
  va_start(args, msg);

  vfprintf(stderr, msg, args);

  va_end(args);
  fputc('\n', stderr);
}
