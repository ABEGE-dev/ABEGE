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
using abege::ABEShape;
using abege::ABETexture;

ABEObject::ABEObject(std::string name) : mName(name) {}

void ABEObject::compile() {
    if (mShape == nullptr) {
        LOGE(TAG, "No shape defined.");
        return;
    }

    int totalStride;
    auto array = mShape->getArray(&totalStride);

    auto indices = mShape->getIndices();

    glGenVertexArrays(1, &mVertexArrayID);
    glGenBuffers(1, &mVertexBufferID);
    glGenBuffers(1, &mElementBufferID);

    glBindVertexArray(mVertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, array.size() * sizeof(GLfloat), &array.front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

    GLuint baseStride = 0;
    for (GLuint i = 0; i < mShape->Attributes.size(); ++i) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, mShape->Attributes[i].Stride,
                              GL_FLOAT, GL_FALSE, totalStride * sizeof(GLfloat),
                              reinterpret_cast<GLvoid *>(baseStride * sizeof(float)));
        baseStride += mShape->Attributes[i].Stride;
//        glDisableVertexAttribArray(i);
    }

#ifdef ABEOBJECT_DRAW_FRAME
    mFrameShader = new ABEShader("shaders/FrameVertexShader.vs",
                                 "shaders/FrameFragmentShader.fs");

    auto frameIndices = mShape->getFrameIndices();

    glGenVertexArrays(1, &mFrameVertexArrayID);
    glGenBuffers(1, &mFrameElementBufferID);

    glBindVertexArray(mFrameVertexArrayID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mFrameElementBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, frameIndices.size() * sizeof(GLuint), &frameIndices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, totalStride * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));
#endif

    glBindVertexArray(0);
}

void ABEObject::setShader(ABEShader *shader) {
    mShader = shader;
}

void ABEObject::setShape(ABEShape *shape) {
    mShape = shape;
}

void ABEObject::setTexture(const char *imagePath) {
    mTexture = new ABETexture();
    mTexture->loadTexture(imagePath);
}

void ABEObject::setTexture(ABETexture *texture) {
    mTexture = texture;
}

void ABEObject::render() {
    mShader->use();

    if (mTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTexture->ID);
    }

    glBindVertexArray(mVertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);

    glDrawElements(GL_TRIANGLES, mShape->getIndicesCount(), GL_UNSIGNED_INT, 0);

    if (mTexture) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

#ifdef ABEOBJECT_DRAW_FRAME
    renderFrame();
#endif
}

void ABEObject::renderFrame() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    mFrameShader->use();

    glBindVertexArray(mFrameVertexArrayID);

    glDrawElements(GL_LINES, mShape->getFrameIndicesCount(), GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
