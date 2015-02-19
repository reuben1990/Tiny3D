//
//  TinyTextureController.h
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//
#ifndef proj_mac_TinyTextureManager_h
#define proj_mac_TinyTextureManager_h

#include "TinyResourceManager.h"
#include <string>
#include <vector>

namespace Tiny
{
    class TinyTextureManager : TinyResourceManager
    {
    public:
        TinyResourceManager();
        ~TinyResourceManager();
        TinyTexture* load(std::string& fileName);
        TinyTexture* load(std::vector<std::string>& fileNames)
    protected:
        
    };
}
#endif