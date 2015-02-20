//
//  TinyVertexIndexData.h
//  proj_mac
//
//  Created by reuben chao on 2/13/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyVertexIndexData__
#define __proj_mac__TinyVertexIndexData__

#include <stdio.h>
#include "TinyObject.h"
#include "TinyHardwareBuffer.h"
#include "TinyIteratorWrapper.h"
#include <map>
#include "TinyPlatform.h"

namespace Tiny
{
    enum TinyVertexAttrLocation
    {
        VERTEX_LOCATION_POSITION = 0,
        VERTEX_LOCATION_UV,
        VERTEX_LOCATION_NORMAL,
        VERTEX_LOCATION_TANGENT
    };
    
    class TinyVertexElement : public TinyObject
    {
    public:
        TinyVertexElement();
        ~TinyVertexElement();
        void load(uint8* data, uint32 length, uint32 size);
        uint32 mSize;
        TinyHardwareBuffer* mBuffer;
    };
    
    typedef std::map<TinyVertexAttrLocation, TinyVertexElement*> TinyVertexElementMap;
    class TinyVertexData : public TinyObject
    {
    public:
        TinyVertexData();
        virtual ~TinyVertexData();
        void load(uint8* data, uint32 length, uint32 size, TinyVertexAttrLocation location);
        MapIterator<TinyVertexElementMap > getBufferIterator();
    protected:
        TinyVertexElementMap mVertexElements;
    };
    
    class TinyIndexData : public TinyObject
    {
    public:
        TinyIndexData();
        virtual ~TinyIndexData();
        void load(uint8* data, uint32 length, uint32 vertexSize);
        uint32 getVertexSize();
        TinyHardwareBuffer* getBuffer();
    protected:
        TinyHardwareBuffer* mBuffer;
        uint32 mVertexSize;
    };
}

#endif /* defined(__proj_mac__TinyVertexIndexData__) */
