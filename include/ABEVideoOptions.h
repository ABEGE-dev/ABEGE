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

#ifndef ABEGE_ABEVIDEOOPTIONS_H
#define ABEGE_ABEVIDEOOPTIONS_H

#define DEFAULT_WINDOW_SIZE_WIDTH 1024
#define DEFAULT_WINDOW_SIZE_HEIGHT 768
#define DEFAULT_FULLSCREEN false

namespace abege {

class ABEVideoOptions {
 public:
    ABEVideoOptions() {}

    void setScreenResolution(int width, int height) {
        mScreenResolutionWidth = width;
        mScreenResolutionHeight = height;
    }
    void setFullscreen(bool fullscreen) {
        mFullscreen = fullscreen;
    }

    int getScreenResolutionWidth() { return mScreenResolutionWidth; }
    int getScreenResolutionHeight() { return mScreenResolutionHeight; }
    bool getFullscreen() { return mFullscreen; }

 private:
    int mScreenResolutionWidth = DEFAULT_WINDOW_SIZE_WIDTH;
    int mScreenResolutionHeight = DEFAULT_WINDOW_SIZE_HEIGHT;
    bool mFullscreen = DEFAULT_FULLSCREEN;
};

} // namespace abege.

#endif //ABEGE_ABEVIDEOOPTIONS_H
