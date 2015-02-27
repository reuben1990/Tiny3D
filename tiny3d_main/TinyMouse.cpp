//
//  TinyMouse.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyMouse.h"

namespace Tiny
{
    TinyMouseListener::TinyMouseListener() : mIsMarkForRemove(false)
    {
    }
    
    TinyMouseListener::~TinyMouseListener() {}
    
    void TinyMouseListener::markForRemove(bool isRemove)
    {
        mIsMarkForRemove = isRemove;
    }
    
    TinyMouse::TinyMouse()
    {
        mLocation.x = 0;
        mLocation.y = 0;
    }
    
    TinyMouse::~TinyMouse() {}
    
    TinyMouse *TinyMouse::create()
    {
        auto ret = new TinyMouse();
        ret->initialize();
        return ret;
    }
    
    void TinyMouse::initialize()
    {
        //
    }
    
    void TinyMouse::setLocation(kmVec2 *location)
    {
        mLocation.x = location->x;
        mLocation.y = location->y;
    }
    
    void TinyMouse::addEventCallBack(TinyMouseListener* listener)
    {
        auto listenerIter = mListeners.find(listener);
        listener->markForRemove(false);
        if (listenerIter == mListeners.end())
        {
            mListeners.insert(listener);
        }
    }
    
    void TinyMouse::removeEventCallBack(TinyMouseListener* listener)
    {
        listener->markForRemove(true);
    }
    
    void TinyMouse::mouseMoved(TinyMouseEvent* event)
    {
        std::set<TinyMouseListener *>::iterator listenerIter;
        for (listenerIter = mListeners.begin(); listenerIter != mListeners.end(); listenerIter ++)
        {
            (*listenerIter)->mouseMoved(event);
        }
    }
    
    void TinyMouse::mouseDraged(TinyMouseEvent* event)
    {
        std::set<TinyMouseListener *>::iterator listenerIter;
        for (listenerIter = mListeners.begin(); listenerIter != mListeners.end(); listenerIter ++)
        {
            (*listenerIter)->mouseDraged(event);
        }
    }
    
    void TinyMouse::mousePressed(TinyMouseEvent* event, TinyMouseButtonID id)
    {
        std::set<TinyMouseListener *>::iterator listenerIter;
        for (listenerIter = mListeners.begin(); listenerIter != mListeners.end(); listenerIter ++)
        {
            (*listenerIter)->mousePressed(event, id);
        }
    }
    
    void TinyMouse::mouseReleased(TinyMouseEvent* event, TinyMouseButtonID id)
    {
        std::set<TinyMouseListener *>::iterator listenerIter;
        for (listenerIter = mListeners.begin(); listenerIter != mListeners.end(); listenerIter ++)
        {
            (*listenerIter)->mouseReleased(event, id);
        }
    }
}