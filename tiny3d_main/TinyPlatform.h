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

namespace Tiny
{
    typedef unsigned int uint32;
    typedef unsigned short uint16;
    typedef unsigned char uint8;
    typedef int int32;
    typedef short int16;
    typedef char int8;
    
    static const int kMaxLogLen = 16*1024;
    
    void TinyLog(const char * pszFormat, ...)
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
    
#define TINYLOG TinyLog
}

#endif
