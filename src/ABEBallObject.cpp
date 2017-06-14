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

#include "ABEBallObject.h"

using abege::ABEBallObject;
using abege::ABETexture2D;

ABEBallObject::ABEBallObject() :
    ABEObject(), Radius(12.5f), Stuck(true) {}

ABEBallObject::ABEBallObject(glm::vec2 pos, GLfloat radius,
    glm::vec2 velocity, ABETexture2D texture) :
    ABEObject(pos, glm::vec2(radius * 2, radius * 2), texture,
    glm::vec3(1.0f), velocity),
    Radius(radius), Stuck(true) {}

glm::vec2 ABEBallObject::Move(GLfloat dt, GLuint window_width) {
    if (!this->Stuck) {
        this->Position += this->Velocity * dt;

        if (this->Position.x <= 0.0f) {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = 0.0f;
        } else if (this->Position.x + this->Size.x >= window_width) {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = window_width - this->Size.x;
        }
        if (this->Position.y <= 0.0f) {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }
    }
    return this->Position;
}

void ABEBallObject::Reset(glm::vec2 position, glm::vec2 velocity) {
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
}
