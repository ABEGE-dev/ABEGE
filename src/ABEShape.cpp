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

#include "ABEShape.h"

#include <algorithm>
#include <numeric>
#include <ABELogger.h>

using std::accumulate;
using std::advance;
using std::copy;
using std::for_each;
using std::vector;

using abege::ABEAttribute;
using abege::ABELocation;
using abege::ABEShape;

void ABEAttribute::append(ABEAttribute target) {
    if (Values.size() == 0) {
        Values = target.Values;
        Stride = target.Stride;
    } else {
        size_t valuesSize = Values.size();
        size_t totalInsertions = valuesSize / Stride;
        for (int i = 0; i < totalInsertions; ++i) {
            Values.insert(Values.begin() + (totalInsertions - i) * Stride,
				target.Values.begin() + (totalInsertions - i - 1) * target.Stride,
				target.Values.begin() + (totalInsertions - i) * target.Stride);
        }
        Stride += target.Stride;
    }
}

ABEShape::ABEShape(const std::vector<ABELocation> vertices, const std::vector<GLuint> indices) {
    vector<GLfloat> values;
    for_each(vertices.begin(), vertices.end(), [&values](const ABELocation &location) {
        values.push_back(location.X);
        values.push_back(location.Y);
        values.push_back(location.Z);
    });
    addAttribute(ABEAttribute(values, 3));

    if (indices.size() == 0) {
        for (GLuint i = 1; i < vertices.size() - 1; ++i) {
            mIndices.push_back(0);
            mIndices.push_back(i);
            mIndices.push_back(i + 1);
        }

        for (GLuint i = 0; i < vertices.size(); ++i) {
            mFrameIndices.push_back(i);
            mFrameIndices.push_back(i + 1);
        }
        mFrameIndices.pop_back();
        mFrameIndices.push_back(0);
    } else {
        mIndices = indices;
        mFrameIndices = indices;
    }
}

void ABEShape::addAttribute(ABEAttribute attribute) {
    Attributes.push_back(attribute);
}

vector<GLfloat> ABEShape::getArray(int *totalStride) {
    if (Attributes.size() == 0) {
        LOGE(TAG, "No Attributes defined.");
        return vector<GLfloat>();
    }
    ABEAttribute allAttributes = ABEAttribute();
    for_each(Attributes.begin(), Attributes.end(), [&allAttributes](const ABEAttribute &attribute) {
        allAttributes.append(attribute);
    });

    *totalStride = allAttributes.Stride;

    return allAttributes.Values;
}
