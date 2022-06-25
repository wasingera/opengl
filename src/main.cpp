#include "glad/glad.h"
#include "shader.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress) ) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    Shader s {"../shaders/learn.vert", "../shaders/learn.frag"};

    float vertices[] = {
        -.5, -.5, 0, 1, 0, 0,
        .5, -.5, 0,  0, 1, 0,
        0, .5, 0,    0, 0, 1,
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VAO{}, VBO{}, EBO{};
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    /* glGenBuffers(1, &EBO); */

    // Setup triangle 0
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), NULL);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*) (3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); */
    /* glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); */


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        s.use();

        // Draw triangle 0
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* glBindVertexArray(VAO); */
        /* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); */
        /* glDrawArrays(GL_TRIANGLES, 0, 6); */
        /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    /* glDeleteBuffers(1, &EBO); */

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}