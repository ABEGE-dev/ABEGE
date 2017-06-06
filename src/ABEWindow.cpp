/*
 * Copyright 2017 Hao Sun <sun.me.0207@gmail.com>
 * Copyright 2017 Zongyu Yin <alexyin1012@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include "ABEWindow.h"

#include <iostream>
#include <stdexcept>

#define DEFAULT_ANTI_ALIASING_RATE 4 // x4
#define DEFAULT_GL_VERSION_MAJOR 3
#define DEFAULT_GL_VERSION_MINOR 3

using std::invalid_argument;

using abege::ABEWindow;

ABEWindow::ABEWindow(int width, int height,
                     std::string title,
                     GLFWmonitor *monitor,
                     GLFWwindow *share) {
    mQuitSignal = false;

    // Initialise GLFW.
    if (glfwInit() == 0) {
        throw invalid_argument("Failed to initialise GLFW!\n");
    }

    glfwWindowHint(GLFW_SAMPLES, DEFAULT_ANTI_ALIASING_RATE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, DEFAULT_GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, DEFAULT_GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context.
    mWindow = glfwCreateWindow(width, height, title.c_str(), monitor, share);
    if (mWindow == NULL) {
        throw invalid_argument("Failed to open GLFW window!\n");
    }

    glfwMakeContextCurrent(mWindow);

    // Initialize GLEW.
    if (glewInit() != GLEW_OK) {
        throw invalid_argument("Failed to initialize GLEW!\n");
    }

    // Dark background.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    while(!mQuitSignal && glfwWindowShouldClose(mWindow) == 0) {
        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT);

        doRendering();

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
}

ABEWindow::ABEWindow(int width, int height, std::string title) {
    ABEWindow(width, height, title, nullptr, nullptr);
}

ABEWindow::ABEWindow() {
    ABEWindow(DEFAULT_WINDOW_SIZE_WIDTH, DEFAULT_WINDOW_SIZE_HEIGHT, "", glfwGetPrimaryMonitor(), nullptr);
}

ABEWindow::~ABEWindow() {
    glfwTerminate();
}

void ABEWindow::start() {

}

void ABEWindow::doRendering() {

}
