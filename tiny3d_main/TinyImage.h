//
//  TinyImage.h
//  proj_mac
//
//  Created by reuben chao on 2/19/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyImage__
#define __proj_mac__TinyImage__

#include <stdio.h>

#include "TinyObject.h"
#include <string>
#include "TinyPlatform.h"
#include <vector>
#include "kazmath/kazmath.h"

namespace Tiny
{
    class TinyImage : public TinyObject
    {
    public:
        typedef std::vector<uint8*> DataList;
        typedef std::vector<kmVec2> SizeList;
        TinyImage();
        ~TinyImage();
        void initWithData(uint8* data, uint32 length, bool isMipmap);
        bool mIsMipmap;
        DataList mDataList;
        SizeList mSizeList;
    };
}

#endif /* defined(__proj_mac__TinyImage__) */
