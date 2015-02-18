//
//  TinyMeshManager.h
//  proj_mac
//
//  Created by reuben chao on 2/13/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyMeshManager__
#define __proj_mac__TinyMeshManager__

#include <stdio.h>
#include "TinyResourceManager.h"
#include "TinyMesh.h"
#include "TinySingleton.h"

namespace Tiny
{
    class TinyMeshManager : public TinyResourceManager, public TinySingleton<TinyMeshManager>
    {
        virtual TinyMesh* load(std::string& fileName);
    };
}


#endif /* defined(__proj_mac__TinyMeshManager__) */
