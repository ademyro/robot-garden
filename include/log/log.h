#ifndef RG_LOG_H
#define RG_LOG_H

/**
 * Formats the given arguments into a string and writes it to STDERR,
 * if this is a debug build.
 *
 * See `common.h` for the DEBUG flag.
 */
void debugLog(const char *msg, ...);

#endif
