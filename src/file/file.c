#include "file/file.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * The default length for the string paths produced by this module.
 */
#define DEFAULT_PATH_LENGTH 512

/**
 * Helper that provides a path for the game’s directory as an allocated string.  No trailing `/` in included in the
 * returned string.
 *
 * The caller is responsible for freeing the resources created by this function.
 *
 * @return An allocated string for the game’s directory path.
 */
const char *gameDirPath() {
    const char *gameDirPath = malloc(DEFAULT_PATH_LENGTH);

    snprintf(
        (char *)gameDirPath,
        DEFAULT_PATH_LENGTH,
        "%s/" GAME_DIR_NAME,
        PARENT_DIR
    );

    return gameDirPath;
}

const char *asGameDirPath(const char *folderName) {
    const char *gameDir = gameDirPath();
    const char *path = malloc(DEFAULT_PATH_LENGTH);

    snprintf(
        (char *)path,
        DEFAULT_PATH_LENGTH,
        "%s/%s",
        gameDir,
        folderName
    );

    free((char *)gameDir);

    return path;
}