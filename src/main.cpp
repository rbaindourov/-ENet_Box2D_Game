#include "network.h"
#include "client.h"
#include "physics.h"
#include "renderer.h"
#include <GLFW/glfw3.h>

int main() {
    initGraphics();
    initPhysics();
    initNetwork();
    initClient();

    while (!glfwWindowShouldClose(window)) {
        handleNetwork();
        stepPhysics();
        render();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
