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
#include "TinyFrameListener.h"
#include "TinyEntity.h"

using namespace Tiny;

class OceanApplication : public TinyKeyListener, public TinyMouseListener, public TinyFrameListener
{
public:
    void initialize();
    virtual void keyPressed(TinyKeyEvent* event);
    virtual void keyReleased(TinyKeyEvent* event);
    virtual void mouseMoved(TinyMouseEvent* event);
    virtual void mouseDraged(TinyMouseEvent* event);
    virtual void mousePressed(TinyMouseEvent* event, TinyMouseButtonID id);
    virtual void mouseReleased(TinyMouseEvent* event, TinyMouseButtonID id);
    virtual void onFrameStarted();
protected:
    TinyMouse* mMouse;
    TinyKeyboard* mKeyBoard;
    Tiny::TinyCamera* mCamera;
    TinyEntity* mEntity;
    
    kmVec3 light_direction;
    kmVec3 light_color;
    float light_ambient_power;
    float light_diffuse_power;
    float light_specular_power;
    float material_shininess;
};

#endif /* defined(__proj_mac__OceanApplication__) */
