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

#ifndef ABEGE_ABELOGGER_H
#define ABEGE_ABELOGGER_H

#include <chrono>
#include <ctime>
#include <iostream>
#include <typeinfo>
#include <utility>

// Uncomment/Comment the following line to Enable/Disable debug output.
#define DEBUG_BUILD

namespace abege {

class ABESceneController;
class ABEWindow;

/**
 * Logger.
 */
inline void LOG() {}

template<typename First, typename ...Rest>
void LOG(First &&first, Rest &&...rest) {
    std::cout << std::forward<First>(first);

    if (sizeof...(Rest) != 0) {
        LOG(std::forward<Rest>(rest)...);
    }
}

inline std::string getCurrentTime() {
    time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string current_time_string = std::ctime(&current_time);
    current_time_string.pop_back();
    current_time_string += "  ";
    return current_time_string;
}

// This logging is for Linux only.
// TODO(Wa): support Windows. (Unsupported part is the colour.)
#ifdef DEBUG_BUILD
#define LOGI(TAG, ...) LOG(getCurrentTime(), TAG, ":\t", __VA_ARGS__, '\n');
#define LOGE(TAG, ...) LOG("\033[1;31m", getCurrentTime(), TAG, ":\t", __VA_ARGS__, "\033[0m\n");
#else
#define LOGI(TAG, ...)
#define LOGE(TAG, ...)
#endif // DEBUG_BUILD

} // namespace abege.

#endif // ABEGE_ABELOGGER_H
