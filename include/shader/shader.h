#ifndef RG_SHADER_H
#define RG_SHADER_H

#include "glad/gl.h"
#include "util/maybe.h"

/**
 * Abstraction layer for an OpenGL shader, encapsulating vertex and fragment shaders.
 *
 * @property id The ID of the Shader.
 */
typedef struct {
    GLuint id;
} Shader;

DEF_MAYBE_TYPE_FOR(Shader);

/**
 * Creates a new Shader from the name of the folder given.
 *
 * @param folderName The name of the folder in `shader/` that contains both the `.vert` and `.frag` files to be
 * compiled.
 * @return A Maybe(Shader) that is `None` in case of a compilation failure.
 */
Maybe(Shader) newShader(const char *folderName);

/**
 * Instructs OpenGL to use a specific shader.
 *
 * @param shader The shader in question.
 */
void useShader(Shader shader);

/**
 * Instructs OpenGL to delete a specific shader.
 *
 * @param shader The shader in question.
 */
void deleteShader(Shader shader);

#endif // RG_SHADER_H
