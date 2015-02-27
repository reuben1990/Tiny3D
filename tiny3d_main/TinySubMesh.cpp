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
        float scaler = 1;
        kmVec3 vData[] =
        {
            {0, scaler, 0},
            {0, 0, 0},
            {scaler, 0, 0}
        };
        kmVec2 uvData[] =
        {
            {0, 0},
            {0, 1},
            {1, 1}
        };
        GLushort iData[] = {0, 1, 2};
        mVertexObject->loadVertexElement((uint8*)vData, sizeof(vData), 3, VERTEX_LOCATION_POSITION);
        mVertexObject->loadVertexElement((uint8*)uvData, sizeof(uvData), 2, VERTEX_LOCATION_UV);
        mVertexObject->loadIndexElement((uint8*)iData, sizeof(iData), 3);
        return 0;
    }
}