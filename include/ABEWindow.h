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

#ifndef ABEGE_ABEWINDOW_H
#define ABEGE_ABEWINDOW_H

#include <stdexcept>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glfw3.h>

#include "ABESceneController.h"
#include "ABETextLabel.h"
#include "ABEVideoOptions.h"

namespace abege {

class ABEWindow {
 public:
    ABEWindow(std::string title) throw(std::invalid_argument);
    ABEWindow(std::string title, int width, int height, bool fullscreen) throw(std::invalid_argument);

    ~ABEWindow();

    void start(ABESceneController *initialSceneController);
    void setQuit(bool quit = true);

 private:
    GLFWwindow *mGLFWwindow = nullptr;
    std::vector<ABESceneController *> mSceneStack = {};
    bool mQuitSignal = false;
    ABEVideoOptions *mVideoOptions = new ABEVideoOptions();
    ABETextLabel *mFPSTextLabel;

    void init(std::string title) throw(std::invalid_argument); // Base constructor.
    void doRendering();

    // Scene Controller manipulations.
    void pushSceneController(ABESceneController *sceneController);
    void setSceneController(ABESceneController *sceneController);
    void popSceneController();

    // Tool Functions.
    void displayFPS(int fps);

    // Callbacks.
    static void framebufferSizeChangedCallback(GLFWwindow *window,
                                               int width, int height);
};

} // Namespace abege.

#endif // ABEGE_ABEWINDOW_H
