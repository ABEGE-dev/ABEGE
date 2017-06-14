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

#include "ABEGameLevel.h"

#include <fstream>
#include <sstream>

using abege::ABEGameLevel;
using abege::ABEObject;
using abege::ABERenderer;


void ABEGameLevel::Load(const GLchar *file,
    GLuint levelWidth, GLuint levelHeight) {
    this->Bricks.clear();
    GLuint tileCode;
    ABEGameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<GLuint>> tileData;
    if (fstream) {
        while (std::getline(fstream, line)) {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while (sstream >> tileCode) {
                row.push_back(tileCode);
            }
            tileData.push_back(row);
        }
        if (tileData.size() > 0) {
            this->init(tileData, levelWidth, levelHeight);
        }
    }
}

void ABEGameLevel::Draw(ABERenderer &renderer) {
    for (ABEObject &tile : this->Bricks) {
        if (!tile.Destroyed) {
            tile.Draw(renderer);
        }
    }
}

GLboolean ABEGameLevel::IsCompleted() {
    for (ABEObject &tile : this->Bricks) {
        if (!tile.IsSolid && !tile.Destroyed) {
            return GL_FALSE;
        }
    }
    return GL_TRUE;
}

void ABEGameLevel::init(std::vector<std::vector<GLuint>> tileData,
    GLuint levelWidth, GLuint levelHeight) {
    GLuint height = tileData.size();
    GLuint width = tileData[0].size();
    GLfloat unit_width = levelWidth / static_cast<GLfloat>(width),
        unit_height = levelHeight / height;
    for (GLuint y = 0; y < height; ++y) {
        for (GLuint x = 0; x < width; ++x) {
            if (tileData[y][x] == 1) {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                ABEObject obj(pos, size,
                    ABEResourceManager::GetTexture("block_solid"),
                    glm::vec3(0.8f, 0.8f, 0.7f));
                obj.IsSolid = GL_TRUE;
                this->Bricks.push_back(obj);
            } else if (tileData[y][x] > 1) {
                glm::vec3 color = glm::vec3(1.0f);
                if (tileData[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                this->Bricks.push_back(ABEObject(pos, size,
                    ABEResourceManager::GetTexture("block"), color));
            }
        }
    }
}
