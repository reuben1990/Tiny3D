//
//  OceanApplication.h
//  proj_mac
//
//  Created by reuben chao on 2/23/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__OceanApplication__
#define __proj_mac__OceanApplication__

#include "TinyMouse.h"
#include "TinyKeyboard.h"
#include "TinyCamera.h"

using namespace Tiny;

class OceanApplication : public TinyKeyListener, public TinyMouseListener
{
public:
    void initialize();
    virtual void keyPressed(TinyKeyEvent* event);
    virtual void keyReleased(TinyKeyEvent* event);
    virtual void mouseMoved(TinyMouseEvent* event);
    virtual void mouseDraged(TinyMouseEvent* event);
    virtual void mousePressed(TinyMouseEvent* event, TinyMouseButtonID id);
    virtual void mouseReleased(TinyMouseEvent* event, TinyMouseButtonID id);
protected:
    TinyMouse* mMouse;
    TinyKeyboard* mKeyBoard;
    Tiny::TinyCamera* mCamera;
};

#endif /* defined(__proj_mac__OceanApplication__) */
