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

#include "ABELocation.h"
#include "ABEShader.h"
#include "ABEShape.h"
#include "ABETexture.h"

#include <GL/glew.h>

#define ABEOBJECT_DRAW_FRAME

namespace abege {

class ABEObject {
 public:
    ABEObject() {}
    ABEObject(std::string name);

    void compile();

    virtual ABEShape *setShape() { return nullptr; }
    virtual ABEShader *setShader() { return nullptr; }
    virtual ABETexture *setTexture() { return nullptr; }

    void setShape(ABEShape *shape);
    void setShader(ABEShader *shader);
    void setTexture(ABETexture *texture);
    void setTexture(const char *imagePath);

    void render();

    void renderFrame();

    // Position manipulation.
    void setPosition(float x, float y) {
        mPosition = ABELocation(x, y);
    }

 protected:
    const std::string TAG = "ABEObject";
    std::string mName;
    // TODO(Wa): add shape(for collision detection).
    ABELocation mPosition = ABELocation(0.0f, 0.0f);

    ABEShape *mShape = nullptr;
    ABEShader *mShader = nullptr;
    ABETexture *mTexture = nullptr;

    GLuint mVertexArrayID, mVertexBufferID, mElementBufferID;
    GLuint mUVBufferID;
    GLint mUniformID;

#ifdef ABEOBJECT_DRAW_FRAME
    ABEShader *mFrameShader = nullptr;
    GLuint mFrameVertexArrayID, mFrameElementBufferID;
#endif
};

} // namespace abege.

#endif // ABEGE_ABEOBJECT_H
