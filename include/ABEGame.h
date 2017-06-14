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

#ifndef INCLUDE_ABEGAME_H_
#define INCLUDE_ABEGAME_H_

#include <GL/glew.h>
#include <glfw3.h>

#include <vector>

#include "ABEGameLevel.h"

enum GameState {GAME_ACTIVE, GAME_MENU, GAME_WIN};

const glm::vec2 PLAYER_SIZE(100, 20);
const GLfloat PLAYER_VELOCITY(500.0f);

namespace abege {

class ABEGame {
 public:
    GameState State;
    GLboolean Keys[1024];
    GLuint Width, Height;
    std::vector<ABEGameLevel> Levels;
    GLuint Level;

    ABEGame(GLuint width, GLuint height);
    ~ABEGame();

    void Init();

    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
};
}  // namespace abege

#endif  // INCLUDE_ABEGAME_H_
