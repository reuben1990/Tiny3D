//
//  TinyPlatform.h
//  proj_mac
//
//  Created by reuben chao on 2/10/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyPlatform_h
#define proj_mac_TinyPlatform_h

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <OpenGL/gl.h>

#include <stdarg.h>
#include <stdio.h>

#define TINYLOG tinyLog

class TinyRenderWindow;

namespace Tiny
{
    typedef unsigned int uint32;
    typedef unsigned short uint16;
    typedef unsigned char uint8;
    typedef int int32;
    typedef short int16;
    typedef char int8;
    
    static const int kMaxLogLen = 16*1024;
    
    void tinyLog(const char * pszFormat, ...);
    TinyRenderWindow* tinyCreateRenderWindow(uint32 width, uint32 height);
}

#endif
