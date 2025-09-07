#include "render/render.h"

#include "log/log.h"

Maybe(Renderer) newRenderer(const ShaderLib *lib) {
  Renderer renderer;

  renderer.shader = *lib->basic;

  Maybe(Texture) maybeTexture = loadTexture("silly-robot.png");
  if (!maybeTexture.isSome) {
    debugLog("Failed to load texture; abandoning renderer creation.");
    return None(Renderer);
  }

  renderer.texture = maybeTexture.value;

  float quadVertices[] = {
    -0.5f, -0.5f, 0.0f, 0.0f,  // bottom left
    0.5f, -0.5f, 1.0f, 0.0f,  // bottom right
    0.5f, 0.5f, 1.0f, 1.0f,  // top right
    -0.5f, 0.5f, 0.0f, 1.0f   // top left
  };

  uint32_t indices[] = {
    0, 1, 2,
    0, 2, 3
  };

  glGenVertexArrays(1, &renderer.vao);

  glGenBuffers(1, &renderer.vbo);
  glGenBuffers(1, &renderer.ebo);

  glBindVertexArray(renderer.vao);

  glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return Some(Renderer, renderer);
}

void renderQuad(Renderer *renderer) {
  useShader(renderer->shader);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, renderer->texture.id);

  glBindVertexArray(renderer->vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void deleteRenderer(Renderer *renderer) {
  deleteShader(renderer->shader);
  glDeleteVertexArrays(1, &renderer->vao);
  glDeleteBuffers(1, &renderer->vbo);
}
