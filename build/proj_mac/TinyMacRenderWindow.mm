//
//  TinyMacRenderWindow.cpp
//  proj_mac
//
//  Created by reuben chao on 2/19/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyMacRenderWindow.h"

namespace Tiny
{
    
    TinyMacRenderWindow::TinyMacRenderWindow(OpenGLView* glView) : TinyRenderWindow(glView.frame.size.width, glView.frame.size.height)
    {
        mGLView = glView;
    }
    
    TinyMacRenderWindow::~TinyMacRenderWindow()
    {
        
    }
    
    void TinyMacRenderWindow::swapBuffers()
    {
        [[mGLView openGLContext] flushBuffer];
    }
    
    void TinyMacRenderWindow::preRender()
    {
        [[mGLView openGLContext] makeCurrentContext];
    }
}