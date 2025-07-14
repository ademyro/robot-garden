#ifndef RG_LOADER_H
#define RG_LOADER_H

#include "shader.h"

/**
 * Works as a "shader manager" for the game by storing hardcoded pointers to each shader.
 */
typedef struct {
    /**
     * Represents the game's “basic shader.”
     *
     * At the time of writing, it is used solely for rendering solid and triangles.
     */
    const Shader *basic;
} ShaderLib;

DEF_MAYBE_TYPE_FOR(ShaderLib);

/**
 * Loads all the game’s shaders into a single `ShaderLib`.  The `Shader`s are owned
 * by the `ShaderLib` itself.
 *
 * @return A `Some(ShaderLib)` in the case of success, `None(ShaderLib)` if any shaders fail to load or compile.
 */
Maybe(ShaderLib) loadShaders();

/**
 * Frees the `ShaderLib` and its associated `Shader`s.
 */
void freeShaders(const ShaderLib *lib);

#endif
