#include "render/render.h"

Maybe(Renderer) newRenderer(const ShaderLib *lib) {
    Renderer renderer;

    renderer.shader = *lib->basic;

    float quadVertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };

    glGenVertexArrays(1, &renderer.vao);
    glBindVertexArray(renderer.vao);

    glGenBuffers(1, &renderer.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return Some(Renderer, renderer);
}

void renderQuad(Renderer *renderer) {
    useShader(renderer->shader);
    glBindVertexArray(renderer->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void deleteRenderer(Renderer *renderer) {
    deleteShader(renderer->shader);
    glDeleteVertexArrays(1, &renderer->vao);
    glDeleteBuffers(1, &renderer->vbo);
}