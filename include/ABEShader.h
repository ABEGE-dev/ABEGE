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

#ifndef INCLUDE_ABESHADER_H_
#define INCLUDE_ABESHADER_H_

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace abege {

class ABEShader {
 public:
    GLuint ID;
    ABEShader() {}
    ABEShader &Use();
    void Compile(const GLchar *vertexSource, const GLchar *fragmentSource,
        const GLchar *geometrySource = nullptr);

    void    SetFloat(const GLchar *name, GLfloat value,
        GLboolean useShader = false);
    void    SetInteger(const GLchar *name, GLint value,
        GLboolean useShader = false);
    void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y,
        GLboolean useShader = false);
    void    SetVector2f(const GLchar *name, const glm::vec2 &value,
        GLboolean useShader = false);
    void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z,
        GLboolean useShader = false);
    void    SetVector3f(const GLchar *name, const glm::vec3 &value,
        GLboolean useShader = false);
    void    SetVector4f(const GLchar *name, GLfloat x,
        GLfloat y, GLfloat z, GLfloat w,
        GLboolean useShader = false);
    void    SetVector4f(const GLchar *name, const glm::vec4 &value,
        GLboolean useShader = false);
    void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix,
        GLboolean useShader = false);

 private:
    void checkCompileErrors(GLuint object, std::string type);
};
}  // namespace abege
#endif  // INCLUDE_ABESHADER_H_
