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

#ifndef ABEGE_ABESHAPE_H
#define ABEGE_ABESHAPE_H

#include <string>
#include <vector>

#include "ABELocation.h"

namespace abege {

class ABEAttribute {
 public:
    ABEAttribute() : Stride(0) {}
    ABEAttribute(std::vector<GLfloat> values, int stride) : Values(values), Stride(stride) {}

    int Stride;
    std::vector<GLfloat> Values;

    void append(ABEAttribute target);
};

class ABEShape {
 public:
    std::vector<ABEAttribute> Attributes;

    ABEShape(const std::vector<ABELocation> vertices);

    void addAttribute(ABEAttribute attribute);

    std::vector<GLfloat> getArray(size_t *size);

    GLsizei getIndicesCount() { return mIndices.size(); }
    std::vector<GLuint> getIndices() { return mIndices; }

    GLsizei getFrameIndicesCount() { return mFrameIndices.size(); }
    std::vector<GLuint> getFrameIndices() { return mFrameIndices; }

 private:
    const std::string TAG = "ABEShape";

    std::vector<GLuint> mIndices;
    std::vector<GLuint> mFrameIndices;
};

}

#endif //ABEGE_ABESHAPE_H
