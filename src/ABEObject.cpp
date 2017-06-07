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

#include "ABEObject.h"

using std::make_pair;
using std::pair;

using abege::ABEObject;

void ABEObject::render() {
    // TODO(Wa): Add render function here.
}

void ABEObject::setPosition(float x, float y) {
    mPositionStack.back() = make_pair(x, y);
}

void ABEObject::pushPosition(float x, float y) {
    mPositionStack.push_back(make_pair(x, y));
}

pair<float, float> ABEObject::popPosition() {
    auto returnPair = mPositionStack.back();
    mPositionStack.pop_back();
    return returnPair;
}
