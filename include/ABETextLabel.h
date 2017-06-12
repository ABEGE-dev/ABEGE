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

#include <map>
#include <string>

namespace abege {

struct Character {
    GLuint textureID;   // ID handle of the glyph texture.
    glm::ivec2 size;    // Size of glyph.
    glm::ivec2 bearing;  // Offset from baseline to left/top of glyph.
    GLuint advance;    // Horizontal offset to advance to next glyph.
};

class ABETextLabel : public ABEObject {
 public:
    ABETextLabel(std::string name, const char *texturePath);
    ~ABETextLabel();

    void render();

    void setText(std::string text) { mText = text; }
    void setSize(uint16_t size) { mSize = size; }
    void setColour(float red, float green, float blue) { mTextColour = glm::vec3(red, green, blue); }

 private:
    const std::string TAG = "ABETextLabel";

    std::string mText;
    uint16_t mSize;
    glm::vec3 mTextColour = glm::vec3(0.5f, 0.8f, 0.2f);

    std::map<GLchar, Character> mCharacters; // TODO: Put this into a "FontLoader" and initialise in game system.
};

}

#endif // ABEGE_ABETEXTLABEL_H
