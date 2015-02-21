//
//  TinyMath.cpp
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyMath.h"

namespace Tiny
{
    kmVec4 kmVec4Make(float x, float y, float z, float w)
    {
        kmVec4 ret;
        ret.x = x;
        ret.y = y;
        ret.z = z;
        ret.w = w;
        return ret;
    }
    
    kmVec3 kmVec3Make(float x, float y, float z)
    {
        kmVec3 ret;
        ret.x = x;
        ret.y = y;
        ret.z = z;
        return ret;
    }
    
    kmVec2 kmVec2Make(float x, float y)
    {
        kmVec2 ret;
        ret.x = x;
        ret.y = y;
        return ret;
    }
    
    kmQuaternion kmQuaternionMake(float x, float y, float z, float w)
    {
        kmQuaternion ret;
        ret.x = x;
        ret.y = y;
        ret.z = z;
        ret.w = w;
        return ret;
    }
}