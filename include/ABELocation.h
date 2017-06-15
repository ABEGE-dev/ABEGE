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

#ifndef ABEGE_ABELOCATION_H
#define ABEGE_ABELOCATION_H

#include <GL/glew.h>

#define ABEGE_Z_NO_3D 0.0f

namespace abege {

class ABELocation {
 public:
    // TODO: Currently use GL coordinate.
    GLfloat X;
    GLfloat Y;
    GLfloat Z = ABEGE_Z_NO_3D;
    ABELocation(GLfloat x, GLfloat y) : X(x), Y(y) {}
};

}

#endif //ABEGE_ABELOCATION_H
