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

#include <iostream>
#include "ABEObject.h"
#include "ABELogger.h"

using std::make_pair;
using std::pair;

using abege::ABEObject;
using abege::ABEShader;

ABEObject::ABEObject(std::string name) : mName(name) {
    // TODO: Remove these code.
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    mShader = new ABEShader("shaders/SimpleVertexShader.vs",
                            "shaders/SimpleFragmentShader.fs");

    static const GLfloat g_vertex_buffer_data[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    static const GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &mVertexArrayID);
    glGenBuffers(1, &mVertexBufferID);
    glGenBuffers(1, &mElementBufferID);

    glBindVertexArray(mVertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void ABEObject::render() {
    glUseProgram(mShader->ID);

    glEnableVertexAttribArray(0);
    glBindVertexArray(mVertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Draw the triangle.
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
}

void ABEObject::setPosition(float x, float y) {
    mPositionStack.back() = make_pair(x, y);
}

void ABEObject::pushPosition(float x, float y) {
    mPositionStack.push_back(make_pair(x, y));
}

pair<float, float> ABEObject::popPosition() {
    auto returnPair = mPositionStack.back();
    mPositionStack.pop_back();
    return returnPair;
}
