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
    mShader = new ABEShader("shaders/TextureVertexShader.vs",
                            "shaders/TextureFragmentShader.fs");

    static const GLfloat g_vertex_buffer_data[] = {
        // positions          // colors           // texture coordinates
        0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    static const GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glGenVertexArrays(1, &mVertexArrayID);
    glGenBuffers(1, &mVertexBufferID);
    glGenBuffers(1, &mElementBufferID);

    glBindVertexArray(mVertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<GLvoid *>(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<GLvoid *>(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<GLvoid *>((6 * sizeof(float))));

    glBindVertexArray(0);

#ifdef ABEOBJECT_DRAW_FRAME
    mFrameShader = new ABEShader("shaders/FrameVertexShader.vs",
                                 "shaders/FrameFragmentShader.fs");
#endif
}

void ABEObject::setTexture(const char *imagePath) {
    mTexture = new ABETexture();
    mTexture->loadTexture(imagePath);
}

void ABEObject::render() {

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
