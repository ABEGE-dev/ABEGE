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

#define DEFAULT_ANTI_ALIASING_RATE 4 // x4
#define DEFAULT_GL_VERSION_MAJOR 3
#define DEFAULT_GL_VERSION_MINOR 3

using std::invalid_argument;

using abege::ABESceneController;
using abege::ABEWindow;
using abege::ABEVideoOptions;

void ABEWindow::init(std::string title) throw(std::invalid_argument) {
    int screenWidth = mVideoOptions->getScreenResolutionWidth();
    int screenHeight = mVideoOptions->getScreenResolutionHeight();

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
    mGLFWwindow = glfwCreateWindow(screenWidth, screenHeight,
                               title.c_str(),
                               mVideoOptions->getFullscreen() ? glfwGetPrimaryMonitor() : nullptr,
                               nullptr);
    if (mGLFWwindow == NULL) {
        throw invalid_argument("Failed to open GLFW window!\n");
    }

    glfwMakeContextCurrent(mGLFWwindow);
    // Initialize GLEW.
    if (glewInit() != GLEW_OK) {
        throw invalid_argument("Failed to initialize GLEW!\n");
    }

    glViewport(0, 0, screenWidth, screenHeight);

    glfwSetFramebufferSizeCallback(mGLFWwindow, framebufferSizeChangedCallback);
}

ABEWindow::ABEWindow(std::string title) throw(invalid_argument) {
    init(title);
}

ABEWindow::ABEWindow(std::string title, int width, int height, bool fullscreen) throw(std::invalid_argument) {
    mVideoOptions->setScreenResolution(width, height);
    mVideoOptions->setFullscreen(fullscreen);
    init(title);
}

ABEWindow::~ABEWindow() {
    glfwTerminate();
    for (auto it = mSceneStack.begin(); it < mSceneStack.end(); ++it) {
        delete *it;
    }
}

void ABEWindow::start(ABESceneController *initialSceneController) {
    pushSceneController(initialSceneController);

    // Dark background.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

#ifndef NDEBUG
    // FPS calculation variables.
    double previousTime = glfwGetTime();
    int currentFPS = 0;
    int frameCount = 0;

    mFPSTextLabel = new ABETextLabel("FPSLabel", "images/Holstein.DDS");
    mFPSTextLabel->setPosition(0, 580);
    mFPSTextLabel->setSize(16);
#endif

    while(mQuitSignal == 0 && glfwWindowShouldClose(mGLFWwindow) == 0) {
        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT);

#ifndef NDEBUG
        // FPS calculation.
        double currentTime = glfwGetTime();
        frameCount++;
        if (currentTime - previousTime >= 0.2/*second*/) {
            previousTime = currentTime;

            currentFPS = frameCount * 5;

            frameCount = 0;
        }
        displayFPS(currentFPS);
#endif

        doRendering();

        glfwSwapBuffers(mGLFWwindow);
        glfwPollEvents();
    }
}

void ABEWindow::doRendering() {
    mSceneStack.back()->renderAll();
}

// Scene Controller manipulations.

void ABEWindow::pushSceneController(ABESceneController *sceneController) {
    mSceneStack.push_back(sceneController);
}

void ABEWindow::setSceneController(ABESceneController *sceneController) {
    mSceneStack.back() = sceneController;
}

void ABEWindow::popSceneController() {
    mSceneStack.pop_back();
}

// Tool functions.
void ABEWindow::displayFPS(int fps) {
    mFPSTextLabel->setText(std::to_string(fps));
    mFPSTextLabel->render();
}

// Callbacks.

void ABEWindow::framebufferSizeChangedCallback(GLFWwindow */*GLFWwindow*/,
                                               const int width, const int height) {
    glViewport(0, 0, width, height);
}
