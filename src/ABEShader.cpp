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

#include <iostream>

using abege::ABEShader;

ABEShader &ABEShader::Use() {
    glUseProgram(this->ID);
    return *this;
}

void ABEShader::Compile(const GLchar *vertexSource,
    const GLchar *fragmentSource, const GLchar *geometrySource) {

    GLuint sVertex, sFragment, sGeometry;
    // Vertex Shader.
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    // Fragment Shader.
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    // Geometry Shader.
    if (geometrySource != nullptr) {
        sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(sGeometry, 1, &geometrySource, NULL);
        glCompileShader(sGeometry);
        checkCompileErrors(sGeometry, "GEOMETRY");
    }
    // Shader Program.
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->ID, sGeometry);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");
    // Delete Shader.
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr) {
        glDeleteShader(sGeometry);
    }
}

void ABEShader::SetFloat(const GLchar *name,
    GLfloat value, GLboolean useShader) {

    if (useShader) {
        this->Use();
    }
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void ABEShader::SetInteger(const GLchar *name,
    GLint value, GLboolean useShader) {

    if (useShader) {
        this->Use();
    }
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void ABEShader::SetVector2f(const GLchar *name,
    GLfloat x, GLfloat y, GLboolean useShader) {

    if (useShader) {
        this->Use();
    }
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void ABEShader::SetVector2f(const GLchar *name,
    const glm::vec2 &value, GLboolean useShader) {

    if (useShader) {
        this->Use();
    }
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void ABEShader::SetVector3f(const GLchar *name,
    GLfloat x, GLfloat y, GLfloat z, GLboolean useShader) {

    if (useShader) {
        this->Use();
    }
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void ABEShader::SetVector3f(const GLchar *name,
    const glm::vec3 &value, GLboolean useShader) {

    if (useShader) {
        this->Use();
    }
    glUniform3f(glGetUniformLocation(this->ID, name),
        value.x, value.y, value.z);
}
void ABEShader::SetVector4f(const GLchar *name, GLfloat x,
    GLfloat y, GLfloat z, GLfloat w, GLboolean useShader) {

    if (useShader) {
        this->Use();
    }
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void ABEShader::SetVector4f(const GLchar *name,
    const glm::vec4 &value, GLboolean useShader) {

    if (useShader) {
        this->Use();
    }
    glUniform4f(glGetUniformLocation(this->ID, name),
        value.x, value.y, value.z, value.w);
}
void ABEShader::SetMatrix4(const GLchar *name,
    const glm::mat4 &matrix, GLboolean useShader) {

    if (useShader) {
        this->Use();
    }
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name),
        1, GL_FALSE, glm::value_ptr(matrix));
}

void ABEShader::checkCompileErrors(GLuint object, std::string type) {
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: "
                << type << "\n"
                << infoLog << "\n -- ------------------------------- -- "
                << std::endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: "
                << type << "\n"
                << infoLog << "\n -- ------------------------------- -- "
                << std::endl;
        }
    }
}
