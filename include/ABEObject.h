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

#ifndef ABEGE_ABEOBJECT_H
#define ABEGE_ABEOBJECT_H

#include <string>
#include <utility>
#include <vector>

#include "ABEShader.h"
#include "ABETexture.h"

#include <GL/glew.h>

namespace abege {

class ABEObject {
 public:
    ABEObject() {}
    ABEObject(std::string name);

    // TODO: Add setVertexes.
    // TODO: Add addShader.
    void setTexture(const char *imagePath);

    virtual void render();

    // Position manipulation.
    void setPosition(float x, float y);
    void pushPosition(float x, float y);
    std::pair<float, float> popPosition();
    float getX() { return mPositionStack.back().first; }
    float getY() { return mPositionStack.back().second; }

 protected:
    std::string mName;
    // TODO(Wa): add shape(for collision detection).
    std::vector<std::pair<float, float>> mPositionStack = {std::make_pair(0.0, 0.0)};

    ABEShader *mShader = nullptr;
    ABETexture *mTexture = nullptr;

    GLuint mVertexBufferID, mVertexArrayID, mElementBufferID;
    GLuint mUVBufferID;
    GLint mUniformID;
};

} // namespace abege.

#endif // ABEGE_ABEOBJECT_H
