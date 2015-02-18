//
//  TinyRenderOperation.h
//  proj_mac
//
//  Created by reuben chao on 2/13/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyRenderOperation__
#define __proj_mac__TinyRenderOperation__

#include <stdio.h>
#include "TinyVertexIndexData.h"

namespace Tiny
{
    class TinyRenderOperation
    {
    public:
        TinyRenderOperation();
        virtual ~TinyRenderOperation();
        TinyVertexData* mVertexData;
        TinyIndexData* mIndexData;
    };
}

#endif /* defined(__proj_mac__TinyRenderOperation__) */
