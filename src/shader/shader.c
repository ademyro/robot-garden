#include "shader/shader.h"
#include "util/maybe.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * The default length for a variety of strings, such as:
 *
 * - “info” strings returned by OpenGL in the event of an error,
 * - The default size of the shader file paths.
 */
#define DEFAULT_STR_LENGTH 512

/**
 * Utility for reading a file.
 *
 * @param path The path of the file in question.
 * @return If an error occurred, `NULL`.  Otherwise, A heap allocated `char *`.
 * The user is responsible for freeing the memory.
 */
static char *readFile(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    const size_t size = ftell(file);
    rewind(file);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "Could not allocate memory for: %s\n", path);
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    fclose(file);

    return buffer;
}

/**
 * This function does not guarantee that the returned path is valid.
 *
 * The user is responsible for freeing the allocated memory.
 *
 * @param folderName The name of the folder that contains the shaders to be compiled in `shader/`.
 * @param fileEnding The shader file’s extension, *including the `.` prefix*.
 *
 * ## Example usage:
 *
 * ```c
 * const char *vertPath = fullRelativePathFor(folderName, ".vert");
 * ```
 *
 * @return A full relative path for the shader source file in `folderName` with the given `fileEnding`.
 */
static const char *relativeShaderPathFor(const char *folderName, const char *fileEnding) {
    const char *relativePath = malloc(DEFAULT_STR_LENGTH + 1);
    snprintf(
        (char *)relativePath,
        DEFAULT_STR_LENGTH,
        "../shader/%s/%s%s",
        folderName,
        folderName,
        fileEnding
    );

    return relativePath;
}

/**
 * @param type The kind of shader we’re compiling.
 * @param source The source of the shader itself.
 * @return A GLint indicating the shader’s ID.  `-1` is returned in the event of a compilation failure.
 */
static GLint compileShader(const GLenum type, const char *source) {
    const GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[DEFAULT_STR_LENGTH];

        glGetShaderInfoLog(shader, DEFAULT_STR_LENGTH, NULL, info);
        fprintf(stderr, "Error compiling shader: \n%s\n", info);

        return -1;
    }

    return (GLint)shader;
}

static Maybe(Shader) newShaderFromExplicitFiles(const char *vertPath, const char *fragPath) {
    const char *vertSrc = readFile(vertPath);
    const char *fragSrc = readFile(fragPath);

    if (!vertSrc || !fragSrc) {
        fprintf(stderr, "Could not load shaders.\n");
        return None(Shader);
    }

    const GLint vertShader = compileShader(GL_VERTEX_SHADER, vertSrc);
    const GLint fragShader = compileShader(GL_FRAGMENT_SHADER, fragSrc);

    free((char *)vertSrc);
    free((char *)fragSrc);

    if (vertShader == -1 || fragShader == -1) {
        fprintf(stderr, "Failed to compile shaders.\n");
        return None(Shader);
    }

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char info[DEFAULT_STR_LENGTH];
        glGetProgramInfoLog(program, DEFAULT_STR_LENGTH, NULL, info);
        fprintf(stderr, "Shader linking error: \n%s\n", info);
    }

    return Some(Shader, { .id = program });
}

Maybe(Shader) newShader(const char *folderName) {
    const char *vertPath = relativeShaderPathFor(folderName, ".vert");
    const char *fragPath = relativeShaderPathFor(folderName, ".frag");

    const Maybe(Shader) shader = newShaderFromExplicitFiles(vertPath, fragPath);

    free((char *)vertPath);
    free((char *)fragPath);

    return shader;
}

void useShader(const Shader shader) {
    glUseProgram(shader.id);
}

void deleteShader(const Shader shader) {
    glDeleteProgram(shader.id);
}