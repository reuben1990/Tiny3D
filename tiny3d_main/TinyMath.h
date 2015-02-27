//
//  TinyMath.h
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyMath__
#define __proj_mac__TinyMath__

#include <stdio.h>

#include "kazmath/kazmath.h"

namespace Tiny
{
    kmQuaternion kmQuaternionMake(float x, float y, float z, float w);
    kmVec4 kmVec4Make(float x, float y, float z, float w);
    kmVec3 kmVec3Make(float x, float y, float z);
    kmVec2 kmVec2Make(float x, float y);
    const float kTinyPI = 4 * atan(1);
    float degreeToRadian(float degree);
    float radianToDegree(float radian);
}

#endif /* defined(__proj_mac__TinyMath__) */
