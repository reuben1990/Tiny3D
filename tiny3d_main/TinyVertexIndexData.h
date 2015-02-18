//
//  TinyVertexIndexData.h
//  proj_mac
//
//  Created by reuben chao on 2/13/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyVertexIndexData__
#define __proj_mac__TinyVertexIndexData__

#include <stdio.h>
#include "TinyObject.h"
#include "TinyHardwareBuffer.h"

namespace Tiny
{
    class TinyVertexData : public TinyObject
    {
    public:
        TinyVertexData();
        virtual ~TinyVertexData();
        void load(uint8* data, uint32 length);
    protected:
        TinyHardwareBuffer* mBuffer;
    };
    
    class TinyIndexData : public TinyObject
    {
    public:
        TinyIndexData();
        virtual ~TinyIndexData();
        void load(uint8* data, uint32 length);
    protected:
        TinyHardwareBuffer* mBuffer;
    };
}

#endif /* defined(__proj_mac__TinyVertexIndexData__) */
