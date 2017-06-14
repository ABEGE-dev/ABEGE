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

#include "ABEResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL.h>

using abege::ABEResourceManager;
using abege::ABEShader;
using abege::ABETexture2D;

std::map<std::string, ABETexture2D> ABEResourceManager::Textures;
std::map<std::string, ABEShader> ABEResourceManager::Shaders;


ABEShader ABEResourceManager::LoadShader(const GLchar *vShaderFile,
    const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name) {
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

ABEShader ABEResourceManager::GetShader(std::string name) {
    return Shaders[name];
}

ABETexture2D ABEResourceManager::LoadTexture(const GLchar *file,
    GLboolean alpha, std::string name) {
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

ABETexture2D ABEResourceManager::GetTexture(std::string name) {
    return Textures[name];
}

void ABEResourceManager::Clear() {
    for (auto iter : Shaders) {
        glDeleteProgram(iter.second.ID);
    }
    for (auto iter : Textures) {
        glDeleteTextures(1, &iter.second.ID);
    }
}

ABEShader ABEResourceManager::loadShaderFromFile(const GLchar *vShaderFile,
    const GLchar *fShaderFile, const GLchar *gShaderFile) {
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try {
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        if (gShaderFile != nullptr) {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e) {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();

    ABEShader shader;
    shader.Compile(vShaderCode, fShaderCode,
        gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

ABETexture2D ABEResourceManager::loadTextureFromFile(const GLchar *file,
    GLboolean alpha) {
    ABETexture2D texture;
    if (alpha) {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    int width, height, nrChannels;
    unsigned char* image = SOIL_load_image(file, &width, &height, 0,
        texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    texture.Generate(width, height, image);
    SOIL_free_image_data(image);
    return texture;
}
