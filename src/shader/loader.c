#include "shader/loader.h"

#include <stdlib.h>

#include "shader/shader.h"
#include "log/log.h"

/**
 * Helper function that loads an individual shader and attempts to allocate it on the heap.
 *
 * @param folderName The name of the folder containing the vertex and fragment shaders.
 * @return An allocated `Shader` in the case of success, a `NULL` pointer otherwise.
 */
const Shader *loadIndividualShader(const char *folderName) {
    const Maybe(Shader) maybe = newShader(folderName);
    if (!maybe.isSome) {
        debugLog("Shader creation failed: folder %s", folderName);
        return NULL;
    }

    Shader *allocatedShader = malloc(sizeof(*allocatedShader));
    if (allocatedShader == NULL) {
        return NULL;
    }

    *allocatedShader = maybe.value;
    return allocatedShader;
}

Maybe(ShaderLib) loadShaders() {
    const Shader *basic = loadIndividualShader("basic");

    if (basic == NULL) {
        free((Shader *)basic);
        return None(ShaderLib);
    }

    return Some(ShaderLib, {
        .basic = basic
    });
}

void freeShaders(const ShaderLib *lib) {
    free((Shader *)lib->basic);
}
