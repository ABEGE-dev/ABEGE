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

#ifndef INCLUDE_ABERESOURCEMANAGER_H_
#define INCLUDE_ABERESOURCEMANAGER_H_

#include <GL/glew.h>

#include "ABETexture.h"
#include "ABEShader.h"

#include <map>
#include <string>

namespace abege {

class ABEResourceManager {
 public:
    static std::map<std::string, ABEShader> Shaders;
    static std::map<std::string, ABETexture2D> Textures;
    static ABEShader LoadShader(const GLchar *vShaderFile,
        const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
    static ABEShader GetShader(std::string name);
    static ABETexture2D LoadTexture(const GLchar *file,
        GLboolean alpha, std::string name);
    static ABETexture2D GetTexture(std::string name);
    static void Clear();
 private:
    ABEResourceManager() {}
    static ABEShader loadShaderFromFile(const GLchar *vShaderFile,
        const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
    static ABETexture2D loadTextureFromFile(const GLchar *file,
        GLboolean alpha);
};
}  // namespace abege

#endif  // INCLUDE_ABERESOURCEMANAGER_H_
