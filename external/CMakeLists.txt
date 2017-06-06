
cmake_minimum_required(VERSION 2.6)

# Build for GLFW.

add_subdirectory (glfw-3.1.2)

include_directories(
        glfw-3.1.2/include/GLFW/
        glew-1.13.0/include/
)

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

set(GLEW_SOURCE glew-1.13.0/src/glew.c)

set(GLEW_HEADERS)


add_library(GLEW_1130 STATIC
        ${GLEW_SOURCE}
        ${GLEW_INCLUDE})

target_link_libraries(GLEW_1130
        ${OPENGL_LIBRARY}
        ${EXTRA_LIBS})
