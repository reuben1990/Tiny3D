//
//  TinyTexture.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyTexture_h
#define proj_mac_TinyTexture_h

#include "TinyObject.h"
#include <string>
#include <vector>
#include "TinyPlatform.h"
#include "TinyImage.h"

namespace Tiny
{
    class TinyTexture
    {
    public:
        TinyTexture();
        ~TinyTexture();
        void load(uint8* data, uint32 length);
        void load(std::vector<uint8*>& datas, std::vector<uint32>& lengths);
        void initWithImage(TinyImage* image);
        void initWithImages(std::vector<TinyImage*>& images);
        GLuint getHandler();
        GLuint* getHandlerPtr();
    protected:
        GLuint mHandler;
    };
}

#endif
