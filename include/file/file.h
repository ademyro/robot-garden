#ifndef RB_FILE_H
#define RB_FILE_H

#ifdef _WIN32
#include <direct.h>
#define mkdir(dir, mode) _mkdir(dir)
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

#ifdef _WIN32
#define PARENT_DIR getenv("APPDATA")
#else
#define PARENT_DIR getenv("HOME")
#endif

/**
 * Defines the name that should be given to the game’s directory, where save files and logs will be stored.
 */
#define GAME_DIR_NAME ".robot_garden"

/**
 * @param folderName The name of the folder that should be in the game’s dedicated directory.
 * @return An allocated string containing the given `folderName` prefixed with the game directory’s path.
 *
 * No guarantees about the existence of such a folder are provided.
 *
 * The caller is responsible for managing the memory returned by this function.
 */
const char *asGameDirPath(const char *folderName);

#endif