#
# Copyright 2017 Hao Sun <sun.me.0207@gmail.com>
# Copyright 2017 Zongyu Yin <alexyin1012@gmail.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 2.6)
project(ABEGE)

find_package(OpenGL REQUIRED)

# Compile external dependencies.
add_subdirectory(external)

include_directories(
        external/glfw-3.1.2/include/GLFW/
        external/glm-0.9.7.1/
        external/glew-1.13.0/include/
        ./include/
)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        GLEW_1130)

# Build for Test Window.
add_executable(test_window
        src/test_window.cpp
        )
target_link_libraries(test_window
        ${ALL_LIBS}
        )
