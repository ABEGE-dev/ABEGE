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

#ifndef INCLUDE_ABETEXTURE_H_
#define INCLUDE_ABETEXTURE_H_

#include <GL/glew.h>

namespace abege {
class ABETexture2D {
 public:
    GLuint ID;
    GLuint Width, Height;
    GLuint Internal_Format, Image_Format;
    GLuint Wrap_S, Wrap_T;
    GLuint Filter_Min, Filter_Max;

    ABETexture2D();
    void Generate(GLuint Width, GLuint Height, unsigned char *data);
    void Bind() const;
};
}  // namespace abege

#endif  // INCLUDE_ABETEXTURE_H_
