//
//  TinySubEntity.h
//  proj_mac
//
//  Created by reuben chao on 2/9/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinySubEntity__
#define __proj_mac__TinySubEntity__

#include <stdio.h>
#include "TinyRenderable.h"
#include "TinySubMesh.h"

namespace Tiny
{
    class TinyEntity;
    class TinySubEntity : public TinyRenderable
    {
    public:
        TinySubEntity(TinyEntity* parent, TinySubMesh* subMesh);
        virtual ~TinySubEntity();
        virtual void getRenderOperation(TinyRenderOperation* ro);
        virtual void getModelMatrix(kmMat4& mat);
    protected:
        TinySubMesh* mSubMesh;
        TinyEntity* mParentEntity;
    };
}

#endif /* defined(__proj_mac__TinySubEntity__) */
