//
//  TinyMacRenderWindow.h
//  proj_mac
//
//  Created by reuben chao on 2/19/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyMacRenderWindow__
#define __proj_mac__TinyMacRenderWindow__

#include <stdio.h>
#include "TinyRenderWindow.h"
#include "OpenGLView.h"
#import <Cocoa/Cocoa.h>

namespace Tiny
{
    class TinyMacRenderWindow : public TinyRenderWindow
    {
    public:
        TinyMacRenderWindow(OpenGLView* glView);
        ~TinyMacRenderWindow();
        virtual void preRender();
        virtual void swapBuffers();
    protected:
        OpenGLView* mGLView;
    };
}

#endif /* defined(__proj_mac__TinyMacRenderWindow__) */
