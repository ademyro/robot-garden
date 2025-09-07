#include "common/common.h"
#include "texture/texture.h"
#include "log/log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/image.h"

/**
 * The folder where the game textures are stored.
 */
#define TEXTURE_FOLDER "../texture/"

/**
  * Prepends `../texture/` to the given string.
  *
  * This function does not guarantee that the path given exists.
  *
  * Ownership of the allocations done by this function goes to the caller.
  *
  * @param fileName The given string.
  */
const char *texturePath(const char *fileName) {
  const char *path = malloc(DEFAULT_PATH_LENGTH);

  snprintf(
    (char *)path,
    DEFAULT_PATH_LENGTH,
    TEXTURE_FOLDER "%s",
    fileName
  );

  return path;
}

Maybe(Texture) loadTexture(const char *fileName) {
  const char *path = texturePath(fileName);

  GLuint id;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
  stbi_set_flip_vertically_on_load(true);

  int width, height, channelCount;
  unsigned char *data = stbi_load(path, &width, &height, &channelCount, 0);

  if (!data) {
    debugLog("Failed to load texture: %s", fileName);
    return None(Texture);
  }

  GLenum format = (channelCount == 4) ? GL_RGBA : GL_RGB;

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    format,
    width,
    height,
    0,
    format,
    GL_UNSIGNED_BYTE,
    data
  );

  stbi_image_free(data);

  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

  Texture texture = {.width = width, .height = height, .id = id};
  return Some(Texture, texture);
}
