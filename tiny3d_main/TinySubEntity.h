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
    class TinySubEntity : public TinyRenderable
    {
    public:
        TinySubEntity(TinySubMesh* subMesh);
        virtual ~TinySubEntity();
        virtual void getRenderOperation(TinyRenderOperation* ro);
    protected:
        TinySubMesh* mSubMesh;
    };
}

#endif /* defined(__proj_mac__TinySubEntity__) */
