#include <time.h>

#include "log/log.h"
#include "file/file.h"

/**
 * The global logger state, silently managed by `log.c`.
 */
static Logger logger;

/**
 * Helper function that provides a file name for the current log file based on the date.
 *
 * If one already exists in the game’s log directory, it is iteratively given an integer suffix to differentiate it.
 */
static const char *logFileName() {

}

void initLogger() {
    logger.bufferSize = 0;

    pthread_mutex_init(&logger.mutex, NULL);
}