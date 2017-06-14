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

#include "iostream"

#include "ABETexture.h"

using abege::ABETexture2D;

ABETexture2D::ABETexture2D() :
    Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB),
    Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT),
    Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR) {
    glGenTextures(1, &this->ID);
}

void ABETexture2D::Generate(GLuint width, GLuint height, unsigned char *data) {
    this->Width = width;
    this->Height = height;
    //  Create Texture.
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0,
        this->Image_Format, GL_UNSIGNED_BYTE, data);
    //  Set Texture wrap and Filter mode.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    //  Unbind Texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void ABETexture2D::Bind() const {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
