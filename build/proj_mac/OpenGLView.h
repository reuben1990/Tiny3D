//
//  TinyOpenGLView.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyOpenGLView_h
#define proj_mac_TinyOpenGLView_h

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#include "TinyMouse.h"
#include "TinyKeyboard.h"
#include "TinyPlatform.h"

@interface OpenGLView : NSOpenGLView
{
    Tiny::TinyMouse *mMouse;
    Tiny::TinyKeyboard *mKeyBoard;
    NSTimer *mTimer;
}

- (void)visit:(NSTimer*)timer;

@end

#endif