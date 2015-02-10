//
//  TinyRenderable.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyRenderable_h
#define proj_mac_TinyRenderable_h

#include "TinyMaterial.h"

namespace Tiny
{
    class TinyRenderable : public TinyObject
    {
    public:
        TinyRenderable();
        virtual ~TinyRenderable();
    protected:
        TinyMaterial* mMaterial;
    };
}

#endif
