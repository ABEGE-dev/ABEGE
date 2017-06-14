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

#include "ABEGame.h"
#include "ABEResourceManager.h"
#include "ABERenderer.h"
#include "ABEObject.h"
#include "ABEBallObject.h"
#include "ABEGameLevel.h"

using abege::ABEGame;
using abege::ABERenderer;
using abege::ABEShader;
using abege::ABETexture2D;
using abege::ABEObject;
using abege::ABEBallObject;
using abege::ABEGameLevel;

const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const GLfloat BALL_RADIUS = 12.5f;

ABERenderer *renderer;
ABEObject *player;
ABEBallObject *ball;

ABEGame::ABEGame(GLuint width, GLuint height) :
    State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

ABEGame::~ABEGame() {
    delete renderer;
    delete player;
}

void ABEGame::Init() {
    ABEResourceManager::LoadShader("shaders/BreakoutVertexShader.vs",
        "shaders/BreakoutFragmentShader.fs", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
        static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ABEResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ABEResourceManager::GetShader("sprite").SetMatrix4("projection",
        projection);
    // Load Texture.
    ABEResourceManager::LoadTexture("textures/background.jpg",
        GL_FALSE, "background");
    ABEResourceManager::LoadTexture("textures/awesomeface.png",
        GL_TRUE, "face");
    ABEResourceManager::LoadTexture("textures/block.png",
        GL_FALSE, "block");
    ABEResourceManager::LoadTexture("textures/block_solid.png",
        GL_FALSE, "block_solid");
    ABEResourceManager::LoadTexture("textures/paddle.png", true, "paddle");

    renderer = new ABERenderer(ABEResourceManager::GetShader("sprite"));

    ABEGameLevel one;
    one.Load("levels/one.lvl", this->Width, this->Height * 0.5);
    ABEGameLevel two;
    two.Load("levels/two.lvl", this->Width, this->Height * 0.5);
    ABEGameLevel three;
    three.Load("levels/three.lvl", this->Width, this->Height * 0.5);
    ABEGameLevel four;
    four.Load("levels/four.lvl", this->Width, this->Height * 0.5);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;

    glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2,
        this->Height - PLAYER_SIZE.y);
    player = new ABEObject(playerPos, PLAYER_SIZE,
        ABEResourceManager::GetTexture("paddle"));

    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS,
        -BALL_RADIUS * 2);
    ball = new ABEBallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
        ABEResourceManager::GetTexture("face"));
}

void ABEGame::Update(GLfloat dt) {
    ball->Move(dt, this->Width);
}

void ABEGame::ProcessInput(GLfloat dt) {
    if (this->State == GAME_ACTIVE) {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move playerboard.
        if (this->Keys[GLFW_KEY_A]) {
            if (player->Position.x >= 0)
                player->Position.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_D]) {
            if (player->Position.x <= this->Width - player->Size.x) {
                player->Position.x += velocity;
            }
        }
        if (this->Keys[GLFW_KEY_SPACE]) {
            ball->Stuck = false;
        }
    }
}

void ABEGame::Render() {
    if (this->State == GAME_ACTIVE) {
        renderer->Drawing(ABEResourceManager::GetTexture("background"),
            glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
        this->Levels[this->Level].Draw(*renderer);
        player->Draw(*renderer);
        ball->Draw(*renderer);
    }
}
