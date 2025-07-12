#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <stdio.h>

#include "render/render.h"
#include "shader/shader.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

int main() {
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Robot Garden", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    const Maybe(ShaderLib) maybeLib = loadShaders();
    if (!maybeLib.isSome) {
        return -1;
    }

    const ShaderLib lib = maybeLib.value;

    const Maybe(Renderer) maybeRenderer = newRenderer(&lib);

    if (!maybeRenderer.isSome) {
        return -1;
    }

    Renderer renderer = maybeRenderer.value;

    while (!glfwWindowShouldClose(window)) {
        renderQuad(&renderer);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    deleteRenderer(&renderer);
    freeShaders(&lib);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}