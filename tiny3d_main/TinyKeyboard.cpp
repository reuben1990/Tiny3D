//
//  TinyKeyboard.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyKeyboard.h"

namespace Tiny
{
    TinyKeyListener::TinyKeyListener() : mIsMarkForRemove(false) {}
    TinyKeyListener::~TinyKeyListener() {}
    
    void TinyKeyListener::markForRemove(bool isRemove)
    {
        mIsMarkForRemove = isRemove;
    }
    
    TinyKeyboard::TinyKeyboard() {}
    
    TinyKeyboard::~TinyKeyboard() {}
    
    TinyKeyboard *TinyKeyboard::create()
    {
        auto ret = new TinyKeyboard();
        ret->initialize();
        return ret;
    }
    
    void TinyKeyboard::addEventCallBack(TinyKeyListener* listener)
    {
        auto listenerIter = mListeners.find(listener);
        listener->markForRemove(false);
        if (listenerIter == mListeners.end())
        {
            mListeners.insert(listener);
        }
    }
    
    void TinyKeyboard::removeEventCallBack(TinyKeyListener* listener)
    {
        listener->markForRemove(true);
    }
    
    void TinyKeyboard::keyPressed(Tiny::TinyKeyEvent *event)
    {
        std::set<TinyKeyListener *>::iterator listenerIter;
        for (listenerIter = mListeners.begin(); listenerIter != mListeners.end(); listenerIter ++)
        {
            (*listenerIter)->keyPressed(event);
        }
    }
    
    void TinyKeyboard::keyReleased(Tiny::TinyKeyEvent *event)
    {
        std::set<TinyKeyListener *>::iterator listenerIter;
        for (listenerIter = mListeners.begin(); listenerIter != mListeners.end(); listenerIter ++)
        {
            (*listenerIter)->keyReleased(event);
        }
    }
}