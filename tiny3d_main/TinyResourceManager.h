//
//  TinyResourceManager.h
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyResourceManager__
#define __proj_mac__TinyResourceManager__

#include <stdio.h>
#include "TinyObject.h"
#include "TinyPlatform.h"
#include <string>

namespace Tiny
{

    class TinyResourceManager : public TinyObject
    {
    public:
        TinyResourceManager();
        ~TinyResourceManager();
        static void getFileData(const std::string& fileName, uint8** data, uint32& length);
    };
}

#endif /* defined(__proj_mac__TinyResourceManager__) */
