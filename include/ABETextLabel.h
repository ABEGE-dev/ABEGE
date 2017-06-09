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

#ifndef ABEGE_ABETEXTLABEL_H
#define ABEGE_ABETEXTLABEL_H

#include "ABEObject.h"

#include <string>

namespace abege {

class ABETextLabel : public ABEObject {
 public:
    ABETextLabel(std::string name, const char *texturePath);
    ~ABETextLabel();

    void render();

    void setText(std::string text) { mText = text; }
    void setSize(uint16_t size) { mSize = size; }

 private:
    std::string mText;
    uint16_t mSize;
};

}

#endif // ABEGE_ABETEXTLABEL_H
