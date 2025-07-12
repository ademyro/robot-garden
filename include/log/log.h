#ifndef RG_LOG_H
#define RG_LOG_H

#include <stdio.h>

#include "glfw/src/posix_thread.h"

/**
 * Defines the name of the folder that contains the log files, within the game directory (`.robot_garden`).
 *
 * No trailing `/` is included.
 */
#define LOG_FOLDER_NAME "logs"

/**
 * Defines the maximum size a log buffer can have before it must be flushed.  This limit does not apply when a
 * log flush is forced, i.e. upon an autosave.
 */
#define MAX_LOG_BUFFER_SIZE 1024

/**
 * Stores the current logging state, such as the file the logs must be output to, and the current log buffer.
 *
 * Storing a `Logger` struct is unnecessary, as `log.c` stores a static `Logger` that manages the global logging state.
 *
 * Thread safety is handled by `log.c` as well using mutexes.
 */
typedef struct {
    /**
     * The current log buffer.
     *
     * Buffering is used to avoid many consecutive I/O operations, which can often be expensive.
     *
     * In debug builds, logging to STDERR is also performed, and this action is not buffered.
     */
    char buffer[MAX_LOG_BUFFER_SIZE];

    /**
     * Stores the current size of the log buffer.
     *
     * If this size exceeds `MAX_LOG_BUFFER_SIZE`, a flush is triggered.
     */
    int bufferSize;

    /**
     * The file the log buffer is output to when flushing.
     *
     * This file remains open for the duration of the program.
     */
    FILE *logFile;

    /**
     * The Logger’s mutex, ensuring no data races occur when logging.
     */
    pthread_mutex_t mutex;
} Logger;

/**
 * Initializes the global logger state in `log.c`.
 */
void initLogger();

/**
 * Writes the given string to the global `Logger`, flushing the buffer if necessary.
 */
void log(const char *msg);

/**
 * Flushes the log buffer, writing its contents to the Logger’s `logFile`.
 */
void flushLogs();

#endif
