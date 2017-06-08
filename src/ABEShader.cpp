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

#include "ABEShader.h"

#include <fstream>
#include <sstream>

#include "ABELogger.h"

#define ABE_PROGRAM_COMPILE "PROGRAM"
#define ABE_SHADER_COMPILE "SHADER"

using std::string;

using abege::ABEShader;

ABEShader::ABEShader(const char* vertexPath,
                     const char* fragmentPath) {
    compile(readFromFile(vertexPath), readFromFile(fragmentPath));
}

void ABEShader::compile(std::string vertexCode, std::string fragmentCode) {
    compile(vertexCode.c_str(), fragmentCode.c_str());
}

void ABEShader::compile(const char *vertexCode, const char *fragmentCode) {
    unsigned int vertex, fragment;

    // Compile vertex shader.
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, ABE_SHADER_COMPILE);

    // Compile fragment Shader.
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, ABE_SHADER_COMPILE);

    // Compile and link shader Program.
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);

    glLinkProgram(ID);
    checkCompileErrors(ID, ABE_PROGRAM_COMPILE);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void ABEShader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type == ABE_PROGRAM_COMPILE) {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            LOGE(TAG, "Program compile Error! ", infoLog);
        }
    }
    else if (type == ABE_SHADER_COMPILE){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            LOGE(TAG, "Shader compile Error! ", infoLog);
        }
    }
}

string ABEShader::readFromFile(string path) {
    std::ifstream fileReadStream(path);

    std::stringstream buffer;
    buffer << fileReadStream.rdbuf();

    fileReadStream.close();

    return buffer.str();
}
