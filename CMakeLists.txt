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
        external/glfw-3.2.1/include/GLFW/
        external/glew-2.0.0/include/
        include/
)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        GLEW_200)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
if(COMPILER_SUPPORTS_CXX1Z)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_definitions(
	-DGLEW_STATIC
)

# Build for ABEGE Lib.
add_library(abege
        src/ABEWindow.cpp src/ABEObject.cpp src/ABESceneController.cpp)
target_link_libraries(abege
        ${ALL_LIBS})

# Build Simple Example.
add_executable(SimpleExample
        example/SimpleExample/SimpleExample.cpp)
add_dependencies(SimpleExample abege)
target_link_libraries(SimpleExample
        abege
        ${ALL_LIBS})
