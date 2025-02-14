#include "renderer.h"
#include "network.h"
#include "physics.h"
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

extern b2Body* playerBody;
GLFWwindow* window;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        std::string command;
        if (key == GLFW_KEY_LEFT) {
            command = "left";
        } else if (key == GLFW_KEY_RIGHT) {
            command = "right";
        }
        if (!command.empty()) {
            sendInput(command);
        }
    }
}

void initGraphics() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return;
    }
    window = glfwCreateWindow(800, 600, "ENet + Box2D Game", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window!" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glOrtho(-10, 10, -10, 10, -1, 1);
    glfwSetKeyCallback(window, keyCallback);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    b2Vec2 pos = playerBody->GetPosition();
    glPushMatrix();
    glTranslatef(pos.x, pos.y, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
    glEnd();
    glPopMatrix();
    glfwSwapBuffers(window);
}
