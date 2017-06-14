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

#ifndef ABEGE_LOGO_H
#define ABEGE_LOGO_H

#include "ABEObject.h"

using abege::ABEAttribute;
using abege::ABELocation;
using abege::ABEObject;
using abege::ABEShape;
using abege::ABEShader;
using abege::ABETexture;

class Logo : public ABEObject {
 public:
    Logo(std::string name) : ABEObject(name) {
        mShape = setShape();
        mShader = setShader();

        compile();

        mTexture = setTexture();
    }

    ABEShape *setShape() override {
        ABEShape *shape = new ABEShape({ABELocation(0.5, 0.5),
                                        ABELocation(0.5, -0.5),
                                        ABELocation(-0.5, -0.5),
                                        ABELocation(-0.5, 0.5)});
        // Colours.
        shape->addAttribute(ABEAttribute({1.0f, 0.0f, 0.0f,
                                          0.0f, 1.0f, 0.0f,
                                          0.0f, 0.0f, 1.0f,
                                          1.0f, 1.0f, 0.0f}, 3));
        // Texture Coordinates.
        shape->addAttribute(ABEAttribute({1.0f, 1.0f,
                                          1.0f, 0.0f,
                                          0.0f, 0.0f,
                                          0.0f, 1.0f}, 2));
        return shape;
    }

    ABEShader *setShader() override {
        return new ABEShader("shaders/TextureVertexShader.vs",
                             "shaders/TextureFragmentShader.fs");
    }

    ABETexture *setTexture() override {
        ABETexture *texture = new ABETexture();
        texture->loadTexture("images/Logo.png");
        return texture;
    }
};

#endif //ABEGE_LOGO_H
