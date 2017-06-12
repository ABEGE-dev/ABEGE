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

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ABELogger.h"

using abege::ABETextLabel;

ABETextLabel::ABETextLabel(std::string name, const char *fontPath) {
    // Initialize Shader.
    mShader = new ABEShader("shaders/DefaultTextVertexShader.vs", "shaders/DefaultTextVertexShader.fs");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(1024), 0.0f, static_cast<GLfloat>(768));
    mShader->use();
    glUniformMatrix4fv(glGetUniformLocation(mShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    FT_Library freeTypeLibrary;
    if (FT_Init_FreeType(&freeTypeLibrary)) {
        LOGE(TAG, "ERROR::FREETYPE: Could not init FreeType Library!");
        return;
    }

    FT_Face face;
    if (FT_New_Face(freeTypeLibrary, "fonts/DefaultFont.ttf", 0, &face)) {
        LOGE(TAG, "ERROR::FREETYPE: Failed to load font!");
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 16);

    // Disable byte-alignment restriction.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set.
    for (GLubyte c = 0; c < 128; c++) {
        // Load character glyph.
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            LOGE(TAG, "ERROR::FREETYPE: Failed to load Glyph!");
            continue;
        }
        // Generate texture.
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // Set texture options.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use.
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
        };
        mCharacters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType.
    FT_Done_Face(face);
    FT_Done_FreeType(freeTypeLibrary);

    // TODO: Put this initialisations into ABEObject in a more general way.
    glGenVertexArrays(1, &mVertexArrayID);
    glGenBuffers(1, &mVertexBufferID);

    glBindVertexArray(mVertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(4);
}

void ABETextLabel::render() {
    // Activate corresponding render state.
    mShader->use();
    glUniform3f(glGetUniformLocation(mShader->ID, "textColor"), mTextColour.x, mTextColour.y, mTextColour.z);
    glActiveTexture(GL_TEXTURE0);
//    glEnableVertexAttribArray(0);
    glBindVertexArray(mVertexArrayID);
//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    // Iterate through all characters.
    float x = getX();
    float y = getY();
    std::string::const_iterator c;
    for (c = mText.begin(); c != mText.end(); c++) {
        Character ch = mCharacters[*c];

        GLfloat xpos = x + ch.bearing.x;
        GLfloat ypos = y - (ch.size.y - ch.bearing.y);

        GLfloat w = ch.size.x;
        GLfloat h = ch.size.y;
        // Update vertex buffer object for each character.
        GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad.
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // Update content of VBO memory.
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // Render quad.
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels).
        // Bit shift by 6 to get value in pixels.
        //   2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels).
        x += (ch.advance >> 6);
    }
    //glBindVertexArray(0);
    //glBindTexture(GL_TEXTURE_2D, 0);
//    glDisableVertexAttribArray(0);
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
