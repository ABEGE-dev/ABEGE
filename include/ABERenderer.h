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

#ifndef INCLUDE_ABERENDERER_H_
#define INCLUDE_ABERENDERER_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ABETexture.h"
#include "ABEShader.h"

namespace abege {
class ABERenderer {
 public:
     ABERenderer(ABEShader &shader);
     ~ABERenderer();
     void Drawing(ABETexture2D &texture, glm::vec2 position,
         glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
         glm::vec3 color = glm::vec3(1.0f));
 private:
     ABEShader shader;
     GLuint quadVAO;
     void initRenderData();
};
}  // namespace abege

#endif  // INCLUDE_ABERENDERER_H_
