#ifndef RG_RENDER_H
#define RG_RENDER_H

#include "glad/gl.h"

#include "shader/shader.h"
#include "shader/loader.h"

#include "texture/texture.h"

#include "util/maybe.h"

// temporary: add docstring later
typedef struct {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    Shader shader;
    Texture texture;
} Renderer;

DEF_MAYBE_TYPE_FOR(Renderer);

// temporary: quad hardcoded—add docstring later
Maybe(Renderer) newRenderer(const ShaderLib *lib);

// temporary: delete later
void renderQuad(Renderer *renderer);

// temporary: add docstring later
void deleteRenderer(Renderer *renderer);

#endif
