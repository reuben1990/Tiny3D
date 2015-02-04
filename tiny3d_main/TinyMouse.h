//
//  TinyMouse.h
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyMouse__
#define __proj_mac__TinyMouse__

#include <stdio.h>
#include "TinyObject.h"
#include "TinyInputObject.h"
#include <set>
#include "kazmath/kazmath.h"

namespace Tiny
{
    enum TinyMouseButtonID
    {
        MB_Left = 0,
        MB_Right,
        MB_Middle
    };
    
    class TinyMouseState : public TinyObject
    {
    public:
        //position diff
        int deltaX;
        int deltaY;
    };
    
    class TinyMouseEvent : public TinyObject
    {
    public:
        TinyMouseState state;
    };
    
    class TinyMouseListener : public TinyObject
    {
    public:
        TinyMouseListener();
        virtual ~TinyMouseListener();
        virtual void mouseMoved(TinyMouseEvent* event) = 0;
        virtual void mousePressed(TinyMouseEvent* event, TinyMouseButtonID id) = 0;
        virtual void mouseReleased(TinyMouseEvent* event, TinyMouseButtonID id) = 0;
        void markForRemove(bool isRemove);
    private:
        bool mIsMarkForRemove;
    };
    
    class TinyMouse : public TinyInputObject
    {
    public:
        TinyMouse();
        virtual ~TinyMouse();
        static TinyMouse *create();
        void initialize();
        void addEventCallBack(TinyMouseListener* listener);
        void removeEventCallBack(TinyMouseListener* listener);
        void mouseMoved(TinyMouseEvent* event);
        void mousePressed(TinyMouseEvent* event, TinyMouseButtonID id);
        void mouseReleased(TinyMouseEvent* event, TinyMouseButtonID id);
        void setLocation(kmVec2 *location);
    private:
        std::set<TinyMouseListener *> mListeners;
        kmVec2 mLocation;
    };
}

#endif /* defined(__proj_mac__TinyMouse__) */
