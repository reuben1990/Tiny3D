//
//  TinyMaterialManager.h
//  proj_mac
//
//  Created by reuben chao on 2/13/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyMaterialManager__
#define __proj_mac__TinyMaterialManager__

#include <stdio.h>
#include "TinyResourceManager.h"
#include "TinySingleton.h"
#include "TinyMaterial.h"
#include <string>

namespace Tiny
{
    class TinyMaterialManager : public TinyResourceManager, public TinySingleton<TinyMaterialManager>
    {
    public:
        TinyMaterial* load(std::string fileName);
    };
}

#endif /* defined(__proj_mac__TinyMaterialManager__) */
