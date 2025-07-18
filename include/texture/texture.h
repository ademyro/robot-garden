#ifndef RG_TEXTURE_H
#define RG_TEXTURE_H

#include "glad/gl.h"

#include "util/maybe.h"

/**
 * Represents a game texture image, carrying an ID.
 */
typedef struct {
    /**
     * The unique ID of the texture.
     */
    GLuint id;

    /**
     * The texture’s width.
     */
    int width;

    /**
     * The texture’s height.
     */
    int height;
} Texture;

DEF_MAYBE_TYPE_FOR(Texture);

/**
 * Tries to load a texture from the given `fileName`.
 *
 * Resolution is done by prefixing the fileName with `../texture/`.  If the texture is not found, a
 * `None(Texture)` is returned.
 *
 * @param fileName The texture file’s *name* (not the full path).
 */
Maybe(Texture) loadTexture(const char *fileName);

// (still not sure what this doess :scream:)
void bindTexture(Texture texture);

/**
 * Deletes the given texture.
 */
void deleteTexture(Texture texture);

#endif
