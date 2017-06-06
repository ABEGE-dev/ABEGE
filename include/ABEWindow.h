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

#define DEFAULT_WINDOW_SIZE_WIDTH  1024
#define DEFAULT_WINDOW_SIZE_HEIGHT 768


#include <string>

#include <GL/glew.h>
#include <glfw3.h>

namespace abege {

class ABEWindow {
 public:
    ABEWindow(int width, int height, std::string title); // Create a windowed window.
    ABEWindow(); // Create a full screen window.

    ABEWindow(int width, int height,
              std::string title,
              GLFWmonitor *monitor,
              GLFWwindow *share); // Base constructor.

    ~ABEWindow();

    void start();
    void setQuit(bool quit = true);
 private:
    GLFWwindow* mWindow;
    // TODO(Hao): BG Queue.
    bool mQuitSignal;

    void doRendering();
};

} // Namespace abege.

#endif // ABEGE_ABEWINDOW_H
