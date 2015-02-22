//
//  TinySubMesh.cpp
//  proj_mac
//
//  Created by reuben chao on 2/9/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinySubMesh.h"
#include "TinyMesh.h"
#include "TinyMemoryAlloc.h"
#include "kazmath/kazmath.h"

namespace Tiny
{
    TinySubMesh::TinySubMesh()
        : mVertexObject(TINY_NEW TinyVertexObject())
    {

    }
    
    TinySubMesh::~TinySubMesh()
    {
        
        TINY_DELETE mVertexObject;
    }
    
    uint32 TinySubMesh::load(uint8* data, uint32 offset)
    {
        //TODO
        kmVec3 vdata[] =
        {
            {0, 1, -1},
            {0, 0, -1},
            {1, 0, -1}
        };
        GLushort idata[] = {0, 1, 2};
        mVertexObject->loadVertexElement((uint8*)vdata, sizeof(vdata), 3, VERTEX_LOCATION_POSITION);
        mVertexObject->loadIndexElement((uint8*)idata, sizeof(idata), 3);
        return 0;
    }
}