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

#include "ABEObject.h"

using abege::ABEObject;
using abege::ABERenderer;
using abege::ABETexture2D;

ABEObject::ABEObject()
    : Position(0, 0), Size(1, 1),
    Velocity(0.0f), Color(1.0f), Rotation(0.0f),
    Texture(), IsSolid(false), Destroyed(false) {}

ABEObject::ABEObject(glm::vec2 pos, glm::vec2 size,
    ABETexture2D texture, glm::vec3 color, glm::vec2 velocity)
    : Position(pos), Size(size), Velocity(velocity), Color(color),
    Rotation(0.0f), Texture(texture), IsSolid(false), Destroyed(false) {}

void ABEObject::Draw(ABERenderer &renderer) {
    renderer.Drawing(this->Texture, this->Position,
        this->Size, this->Rotation, this->Color);
}
