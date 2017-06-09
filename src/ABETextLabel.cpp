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

#include "ABETextLabel.h"

using abege::ABETextLabel;

ABETextLabel::ABETextLabel(std::string name, const char *texturePath) : ABEObject(name) {
    // Initialize texture.
    mTexture = new ABETexture();
    mTexture->loadDDS(texturePath);

    // Initialize VBO.
    glGenBuffers(1, &mVertexBufferID);
    glGenBuffers(1, &mUVBufferID);

    // Initialize Shader.
    mShader = new ABEShader("shaders/DefaultTextVertexShader.vs", "shaders/DefaultTextVertexShader.fs");

    // Initialize uniforms' IDs.
    mUniformID = glGetUniformLocation(mShader->ID, "DefaultTextureSampler");
}

void ABETextLabel::render() {
    size_t length = mText.length();

    // Fill buffers.
    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> UVs;
    for (unsigned int i = 0; i < length; i++) {
        float x = getX();
        float y = getY();
        glm::vec2 vertex_up_left = glm::vec2(x + i * mSize, y + mSize);
        glm::vec2 vertex_up_right = glm::vec2(x + i * mSize + mSize, y + mSize);
        glm::vec2 vertex_down_right = glm::vec2(x + i * mSize + mSize, y);
        glm::vec2 vertex_down_left = glm::vec2(x + i * mSize, y);

        vertices.push_back(vertex_up_left);
        vertices.push_back(vertex_down_left);
        vertices.push_back(vertex_up_right);

        vertices.push_back(vertex_down_right);
        vertices.push_back(vertex_up_right);
        vertices.push_back(vertex_down_left);

        char character = mText[i];
        float uv_x = (character % 16) / 16.0f;
        float uv_y = (character / 16) / 16.0f;

        glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
        glm::vec2 uv_up_right = glm::vec2(uv_x + 1.0f / 16.0f, uv_y);
        glm::vec2 uv_down_right = glm::vec2(uv_x + 1.0f / 16.0f, (uv_y + 1.0f / 16.0f));
        glm::vec2 uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / 16.0f));
        UVs.push_back(uv_up_left);
        UVs.push_back(uv_down_left);
        UVs.push_back(uv_up_right);

        UVs.push_back(uv_down_right);
        UVs.push_back(uv_up_right);
        UVs.push_back(uv_down_left);
    }
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mUVBufferID);
    glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

    // Bind shader.
    glUseProgram(mShader->ID);

    // Bind texture.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture->ID);
    glUniform1i(mUniformID, 0);

    // 1rst attribute buffer : vertices.
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    // 2nd attribute buffer : UVs.
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, mUVBufferID);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw call.
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));

    glDisable(GL_BLEND);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

ABETextLabel::~ABETextLabel() {
    // Delete buffers.
    glDeleteBuffers(1, &mVertexBufferID);
    glDeleteBuffers(1, &mUVBufferID);

    // Delete texture.
    glDeleteTextures(1, &mTexture->ID);

    // Delete shader.
    glDeleteProgram(mShader->ID);
}