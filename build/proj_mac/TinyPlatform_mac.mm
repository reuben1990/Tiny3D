//
//  TinyPlatform_mac.cpp
//  proj_mac
//
//  Created by reuben chao on 2/19/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include <stdio.h>
#include "TinyPlatform.h"
#include "AppDelegate.h"
#include "OpenGLView.h"
#include "TinyMacRenderWindow.h"
#include "TinyMemoryAlloc.h"

namespace Tiny
{
    void tinyLog(const char * pszFormat, ...)
    {
        printf("Tiny3d: ");
        char szBuf[kMaxLogLen + 1] = {0};
        va_list ap;
        va_start(ap, pszFormat);
        vsnprintf(szBuf, kMaxLogLen, pszFormat, ap);
        va_end(ap);
        printf("%s", szBuf);
        printf("\n");
    }
    
    TinyRenderWindow* tinyCreateRenderWindow(uint32 width, uint32 height)
    {
        OpenGLView* glView = [[AppDelegate sharedDelegate] createGLView:width height:height];
        return TINY_NEW TinyMacRenderWindow(glView);
    }
}