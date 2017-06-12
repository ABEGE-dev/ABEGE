
cmake_minimum_required(VERSION 2.6)

include_directories(
        glfw-3.2.1/include/GLFW/
        glew-2.0.0/include/
        freetype-2.8/include/
)

# Build for GLFW.

add_subdirectory (glfw-3.2.1)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            -lGL -lGLU -lXrandr -lXext -lX11 -lrt
            ${CMAKE_DL_LIBS}
            ${GLFW_LIBRARIES}
            )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            ${CMAKE_DL_LIBS}
            ${GLFW_LIBRARIES}
            )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Build for GLEW.

set(GLEW_SOURCE glew-2.0.0/src/glew.c)

set(GLEW_HEADERS)

add_library(GLEW_200 STATIC
        ${GLEW_SOURCE}
        ${GLEW_INCLUDE})

target_link_libraries(GLEW_200
        ${OPENGL_LIBRARY}
        ${EXTRA_LIBS})

# Build for Freetype.

add_subdirectory(freetype-2.8)
