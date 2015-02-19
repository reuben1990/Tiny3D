//
//  TinyInputManager.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyInputDelegate__
#define __proj_mac__TinyInputDelegate__

#include <vector>
#include <set>
#include <map>
#include <string>
#include "TinyObject.h"
#include "TinyInputObject.h"
#include "kazmath/kazmath.h"
#include "TinySingleton.h"

namespace Tiny
{
    enum InputDevice
    {
        Mouse = 0,
        Keyboard
    };

    class TinyInputManager : public TinyObject, public TinySingleton<TinyInputManager>
    {
    public:
        TinyInputManager();
        virtual ~TinyInputManager();
        TinyInputObject* getInputObject(InputDevice inputDevice, int index = 0);
        void createInputObject(InputDevice inputDevice);
        void initialize();
    private:
        std::vector<TinyInputObject *> * checkInputObjectList(InputDevice inputDevice);
        std::map<InputDevice, std::vector<TinyInputObject*> *> mInputDevices;
    };
}

#endif
