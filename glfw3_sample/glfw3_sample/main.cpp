//
//  main.cpp
//  glfw_sample
//
//  Created by dandelion on 2014/01/04.
//  Copyright (c) 2014年 dandelion. All rights reserved.
//

#include <GLFW/glfw3.h>
#include <iostream>

static void error_callback(int error, const char* description)
{
    std::cerr << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        std::cout << "[ESC] key is pressed."  << std::endl;
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(void)
{
    GLFWwindow* window = NULL;

    // set the error callback
    glfwSetErrorCallback(error_callback);

    // initialize the GLFW library
    if(!glfwInit())
    {
        std::cerr << "[Error] glfwInit() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    // creates a window and its associated context
    window = glfwCreateWindow(640, 480, "glfw3 sample", NULL, NULL);

    if(!window)
    {
        std::cerr << "[Error] glfwCreateWindow() failed." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // make the context of the specified window current on the calling thread
    glfwMakeContextCurrent(window);

    // set the key callback of the specific window
    glfwSetKeyCallback(window, key_callback);

    while(!glfwWindowShouldClose(window))
    {
        float ratio = 0.0f;
        int width, height = 0;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 200.f, 0.f, 0.f, -1.f);

        glBegin(GL_QUADS);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.5f, -0.5f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.5f, -0.5f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.5f, 0.5f, 0.f);
        glColor3f(1.f, 0.f, 1.f);
        glVertex3f(-0.5f, 0.5f, 0.f);
        glEnd();

        // swap the front and back buffers of the specified window
        glfwSwapBuffers(window);

        // processes only those events that have already been received
        // and then returns immediately
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
