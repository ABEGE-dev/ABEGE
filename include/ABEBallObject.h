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

#ifndef INCLUDE_ABEBALLOBJECT_H_
#define INCLUDE_ABEBALLOBJECT_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "ABETexture.h"
#include "ABERenderer.h"
#include "ABEObject.h"

namespace abege {
class ABEBallObject : public ABEObject {
 public:
    GLfloat   Radius;
    GLboolean Stuck;

    ABEBallObject();
    ABEBallObject(glm::vec2 pos, GLfloat radius,
        glm::vec2 velocity, ABETexture2D sprite);

    glm::vec2 Move(GLfloat dt, GLuint window_width);

    void Reset(glm::vec2 position, glm::vec2 velocity);
};
}  // namespace abege

#endif  // INCLUDE_ABEBALLOBJECT_H_
