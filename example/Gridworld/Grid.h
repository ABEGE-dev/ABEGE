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

#ifndef ABEGE_GRID_H
#define ABEGE_GRID_H

#include "ABEObject.h"

#define GRID_UPPER_BOUND 0.95
#define GRID_LOWER_BOUND -0.95
#define GRID_LEFT_BOUND -0.95
#define GRID_RIGHT_BOUND 0.95

using std::vector;

using abege::ABEObject;
using abege::ABELocation;
using abege::ABEShape;
using abege::ABEShader;

class Grid : public ABEObject {
 public:
    Grid(std::string name, int width, int height) : ABEObject(name) {
        float gridWidth = (GRID_RIGHT_BOUND - GRID_LEFT_BOUND) / width;
        float gridHeight = (GRID_UPPER_BOUND - GRID_LOWER_BOUND) / height;
        vector<ABELocation> gridVertices;
        // Set vertical lines.
        for (int i = 0; i < width + 1; ++i) {
            gridVertices.push_back(ABELocation(GRID_UPPER_BOUND, GRID_LEFT_BOUND + i * gridWidth));
            gridVertices.push_back(ABELocation(GRID_LOWER_BOUND, GRID_LEFT_BOUND + i * gridWidth));
        }
        // Set horizontal lines.
        for (int i = 0; i < height + 1; ++i) {
            gridVertices.push_back(ABELocation(GRID_LOWER_BOUND + i * gridHeight, GRID_LEFT_BOUND));
            gridVertices.push_back(ABELocation(GRID_LOWER_BOUND + i * gridHeight, GRID_RIGHT_BOUND));
        }
        vector<GLuint> indices = {};
        for (int j = 0; j < width * height * 2; ++j) {
            indices.push_back(j);
        }
        mShape = new ABEShape(gridVertices, indices);
        mShader = new ABEShader("shaders/FrameVertexShader.vs",
                                "shaders/FrameFragmentShader.fs");

        compile();

        setPolygonMode(GL_LINE);
    }
};

#endif //ABEGE_GRID_H
