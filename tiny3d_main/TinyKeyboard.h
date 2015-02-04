//
//  TinyKeyboard.h
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyKeyboard__
#define __proj_mac__TinyKeyboard__

#include <stdio.h>
#include "TinyObject.h"
#include "TinyInputObject.h"
#include <set>

namespace Tiny
{

    class TinyKeyEvent : public TinyObject
    {
    public:
        unsigned short mKeyCode;
    };

    class TinyKeyListener : public TinyObject
    {
    public:
        TinyKeyListener();
        virtual ~TinyKeyListener();
        virtual void keyPressed(TinyKeyEvent* event) = 0;
        virtual void keyReleased(TinyKeyEvent* event) = 0;
        void markForRemove(bool isRemove);
    private:
        bool mIsMarkForRemove;
    };

    class TinyKeyboard : public TinyInputObject
    {
    public:
        TinyKeyboard();
        virtual ~TinyKeyboard();
        static TinyKeyboard *create();
        void initialize();
        void addEventCallBack(TinyKeyListener* listener);
        void removeEventCallBack(TinyKeyListener* listener);
        void keyPressed(TinyKeyEvent* event);
        void keyReleased(TinyKeyEvent* event);
        void isKeyDown(unsigned short keyCode);
    private:
        std::set<TinyKeyListener *> mListeners;
    };
}

#endif /* defined(__proj_mac__TinyKeyboard__) */
