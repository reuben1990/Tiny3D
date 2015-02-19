//
//  TinyInputManager.cpp
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyInputManager.h"
#include "TinyMouse.h"
#include "TinyKeyboard.h"

namespace Tiny
{
    TinyInputManager::TinyInputManager()
    {
    }
    
    TinyInputManager::~TinyInputManager()
    {
    }

    void TinyInputManager::initialize()
    {
    }
    
    std::vector<TinyInputObject *> * TinyInputManager::checkInputObjectList(InputDevice inputDevice)
    {
        auto deviceIter = mInputDevices.find(inputDevice);
        std::vector<TinyInputObject *> *inputObjList;
        if (deviceIter == mInputDevices.end())
        {
            inputObjList = new std::vector<TinyInputObject *>();
            mInputDevices[inputDevice] = inputObjList;
        }
        else
        {
            inputObjList = deviceIter->second;
        }
        return inputObjList;
    }
    
    void TinyInputManager::createInputObject(InputDevice inputDevice)
    {
        TinyInputObject* inputObject = nullptr;
        switch (inputDevice) {
            case InputDevice::Mouse:
            {
                inputObject = Tiny::TinyMouse::create();
                break;
            }
            case InputDevice::Keyboard:
            {
                inputObject = Tiny::TinyKeyboard::create();
                break;
            }
            default:
            {
                break;
            }
        }
        if (inputObject != nullptr)
        {
            auto inputObjList = checkInputObjectList(inputDevice);
            inputObjList->push_back(inputObject);
        }
    }
    
    TinyInputObject* TinyInputManager::getInputObject(InputDevice inputDevice, int index)
    {
        auto deviceIter = mInputDevices.find(inputDevice);
        TinyInputObject* ret = nullptr;
        if (deviceIter != mInputDevices.end())
        {
            std::vector<TinyInputObject *> *inputObjects = deviceIter->second;
            if (inputObjects->size() > index)
            {
                ret = (*inputObjects)[index];
            }
        }
        return ret;
    }
}