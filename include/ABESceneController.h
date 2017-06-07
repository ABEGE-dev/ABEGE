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

#ifndef ABEGE_ABESCENECONTROLLER_H
#define ABEGE_ABESCENECONTROLLER_H

#include <vector>

#include "ABEObject.h"

namespace abege {

class ABEWindow;

class ABESceneController {
 public:
    ABESceneController(ABEWindow *window, std::string name);
    ~ABESceneController() {}

    void addObject(ABEObject *obj);

    void renderAll();

 private:
    ABEWindow *mWindow;
    std::string mName;
    std::vector<ABEObject *> mObjectContainer = {};
};

} // namespace abege.

#endif //ABEGE_ABESCENECONTROLLER_H
