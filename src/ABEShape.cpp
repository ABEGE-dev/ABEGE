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

using std::accumulate;
using std::advance;
using std::for_each;
using std::list;

using abege::ABEAttribute;
using abege::ABELocation;
using abege::ABEShape;

void ABEAttribute::append(ABEAttribute target) {
    if (Values.size() == 0) {
        Values = target.Values;
        Stride = target.Stride;
    } else {
        auto itInsert = Values.begin();
        advance(itInsert, Stride);
        auto targetInsertStart = target.Values.begin();
        auto targetInsertEnd = target.Values.begin();
        advance(targetInsertEnd, target.Stride);

        for (int i = 0; i < Values.size() / Stride; ++i) {
            Values.insert(itInsert, targetInsertStart, targetInsertEnd);
            advance(itInsert, Stride);
            advance(targetInsertStart, target.Stride);
            advance(targetInsertEnd, target.Stride);
        }
        Stride += target.Stride;
    }
}

ABEShape::ABEShape(int verticesCount, std::vector<ABELocation> vertices) {
    list<GLfloat> values;
    for_each(vertices.begin(), vertices.end(), [&values](const auto &location) {
        values.push_back(location.X);
        values.push_back(location.Y);
        values.push_back(location.Z);
    });
    addAttribute(ABEAttribute(values, 3));
}

void ABEShape::addAttribute(ABEAttribute attribute) {
    mAttributes.push_back(attribute);
}
