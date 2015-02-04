//
//  TinyOpenGLView.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyOpenGLView_h
#define proj_mac_TinyOpenGLView_h

#import <OpenGL/gl.h>
#import <Cocoa/Cocoa.h>
#import "TinyDelegate.h"
#include "TinyMouse.h"
#include "TinyKeyboard.h"

@interface OpenGLView : NSOpenGLView {
    NSTimer *mTimer;
    Tiny::TinyMouse *mMouse;
    Tiny::TinyKeyboard *mKeyBoard;
};

- (void)visit:(NSTimer*)timer;

@end



#endif