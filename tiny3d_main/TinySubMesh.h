//
//  TinySubMesh.h
//  proj_mac
//
//  Created by reuben chao on 2/9/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinySubMesh__
#define __proj_mac__TinySubMesh__

#include <stdio.h>
#include "TinyObject.h"
#include "TinyPlatform.h"
#include "TinyVertexIndexData.h"

namespace Tiny
{
    class TinySubMesh : public TinyObject
    {
    public:
        TinySubMesh();
        ~TinySubMesh();
        uint32 load(uint8* data, uint32 offset);
        TinyVertexObject* mVertexObject;
    };
}

#endif /* defined(__proj_mac__TinySubMesh__) */
