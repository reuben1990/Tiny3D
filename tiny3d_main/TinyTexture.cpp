//
//  TinyTexture.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyTexture.h"
#include "TinyMemoryAlloc.h"

namespace Tiny
{
    TinyTexture::TinyTexture()
        : mHandler(0)
    {
        
    }
    
    TinyTexture::~TinyTexture()
    {
        
    }
    
    void TinyTexture::load(uint8* data, uint32 length)
    {
        TinyImage* image = TINY_NEW TinyImage();
        image->initWithData(data, length, true);
        initWithImage(image);
        TINY_DELETE image;
    }
    
    void TinyTexture::load(vector<uint8*>& datas, vector<uint32>& lengths)
    {
        uint32 length = datas.size();
        std::vector<TinyImage*> images
        for (int i = 0; i < length; i ++)
        {
            TinyImage* image = TINY_NEW TinyImage();
            image->initWithData(datas[i], lengths[i], true);
            images.push_back(image)
        }
        initWithImages(images);
        for (int i = 0; i < length; i ++)
        {
            TINY_DELETE images[i];
        }
    }
    
    void TinyTexture::initWithImage(TinyImage* image)
    {
        if (mHandler == 0)
        {
            DataList& dataList = image->mDataList;
            SizeList& sizeList = image->mSizeList;
            //glPixelStorei(GL_UNPACK_ALIGNMENT,4);
            glGenTextures(1, &mHandler);
            
            glActiveTexture(GL_TEXTURE0);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, mHandler);
            
            int mipMapCount = image->mDataList.size();
            for (int i = 0; i < mipMapCount; i ++)
            {
                uint32 width = sizeList[i].x;
                uint32 height = sizeList[i].y;
                glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataList[i]);
            }
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            if (image.mIsMapmap == false)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            }
            else
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            glDisable(GL_TEXTURE_2D);
        }
    }
    
    void TinyTexture::initWithImages(std::vector<TinyImage*> images)
    {
        if (mHandler == 0)
        {
            glActiveTexture(GL_TEXTURE0);
            glEnable(GL_TEXTURE_CUBE_MAP);
            glGenTextures(1, &mHandler);
            glBindTexture(GL_TEXTURE_CUBE_MAP, mHandler);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            bool isMapmap = images[0].mIsMapmap;
            if (isMapmap == false)
            {
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            }
            else
            {
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
                glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
            }
            
            for (int cubeIdx = 0; cubeIdx < 6; cubeIdx ++)
            {
                DataList& dataList = images[i]->mDataList;
                SizeList& sizeList = images[i]->mSizeList;
                
                int mipMapCount = dataList.size();
                for (int i = 0; i < mipMapCount; i ++)
                {
                    uint32 width = sizeList[i].x;
                    uint32 height = sizeList[i].y;
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + cubeIdx, i, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataList[i]);
                }
            }
            glDisable(GL_TEXTURE_CUBE_MAP);
        }
    }
    
    GLuint TinyTexture::getHandler()
    {
        return mHandler;
    }
    
    GLuint* getHandlerPtr()
    {
        return &mHandler;
    }
}