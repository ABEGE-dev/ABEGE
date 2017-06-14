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

#ifndef INCLUDE_ABEOBJECT_H_
#define INCLUDE_ABEOBJECT_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "ABETexture.h"
#include "ABERenderer.h"

namespace abege {
class ABEObject {
 public:
     glm::vec2 Position, Size, Velocity;
     glm::vec3 Color;
     GLfloat Rotation;
     GLboolean IsSolid;
     GLboolean Destroyed;
     ABETexture2D Texture;

     ABEObject();
     ABEObject(glm::vec2 pos, glm::vec2 size,
         ABETexture2D texure, glm::vec3 color = glm::vec3(1.0f),
         glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

     virtual void Draw(ABERenderer &renderer);
};
}  // namespace abege.

#endif  // INCLUDE_ABEOBJECT_H_
