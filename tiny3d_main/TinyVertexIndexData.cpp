//
//  TinyVertexIndexData.cpp
//  proj_mac
//
//  Created by reuben chao on 2/13/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyVertexIndexData.h"
#include "TinyMemoryAlloc.h"
#include "TinyPlatform.h"

namespace Tiny
{
    TinyIndexData::TinyIndexData()
        : mBuffer(TINY_NEW TinyHardwareBuffer())
    {
    }
    
    TinyIndexData::~TinyIndexData()
    {
        TINY_DELETE mBuffer;
    }
    
    void TinyIndexData::load(uint8* data, uint32 length, uint32 vertexNum)
    {
        mVertexNum = vertexNum;
        mBuffer->readData(data, length, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    }
    
    uint32 TinyIndexData::getVertexNum()
    {
        return mVertexNum;
    }
    
    TinyHardwareBuffer* TinyIndexData::getBuffer()
    {
        return mBuffer;
    }
    
    TinyVertexData::TinyVertexData()
    {
        
    }
    
    TinyVertexData::~TinyVertexData()
    {
        auto iter = mVertexElements.begin();
        for (; iter != mVertexElements.end(); iter ++)
        {
            TINY_DELETE iter->second;
        }
    }
 
    void TinyVertexData::load(uint8* data, uint32 length, uint32 vectorSizePerElement, TinyVertexAttrLocation location)
    {
        auto iter = mVertexElements.find(location);
        TinyVertexElement* element;
        if (iter == mVertexElements.end())
        {
            element = TINY_NEW TinyVertexElement();
            mVertexElements.insert(std::pair<TinyVertexAttrLocation, TinyVertexElement*>(location, element));
        }
        else
        {
            element = iter->second;
        }
        element->load(data, length, vectorSizePerElement);
    }
    
    MapIterator<TinyVertexElementMap > TinyVertexData::getBufferIterator()
    {
        return MapIterator<TinyVertexElementMap >(mVertexElements.begin(), mVertexElements.end());
    }
    
    TinyVertexElement::TinyVertexElement()
        : mBuffer(TINY_NEW TinyHardwareBuffer())
        , mVectorSizePerElement(0)
    {
        
    }
    
    TinyVertexElement::~TinyVertexElement()
    {
        TINY_DELETE mBuffer;
    }
    
    void TinyVertexElement::load(uint8* data, uint32 length, uint32 vectorSizePerElement)
    {
        mBuffer->readData(data, length, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
        mVectorSizePerElement = vectorSizePerElement;
    }
    
    TinyVertexObject::TinyVertexObject()
        : mVertexData(TINY_NEW TinyVertexData())
        , mIndexData(TINY_NEW TinyIndexData())
        , mHandler(0)
    {
        
    }
    
    TinyVertexObject::~TinyVertexObject()
    {
        TINY_DELETE mVertexData;
        TINY_DELETE mIndexData;
    }
    
    TinyVertexData* TinyVertexObject::getVertexData()
    {
        return mVertexData;
    }
    
    TinyIndexData* TinyVertexObject::getIndexData()
    {
        return mIndexData;
    }
    
    void TinyVertexObject::loadVertexElement(uint8* data, uint32 length, uint32 vectorSizePerElement, TinyVertexAttrLocation location)
    {
        mVertexData->load(data, length, vectorSizePerElement, location);
    }
    
    void TinyVertexObject::loadIndexElement(uint8* data, uint32 length, uint32 vertexNum)
    {
        mIndexData->load(data, length, vertexNum);
    }
    
    graphicInt TinyVertexObject::getHandler()
    {
        return mHandler;
    }
    
    void TinyVertexObject::setHandler(graphicInt handler)
    {
        mHandler = handler;
    }
    
    bool TinyVertexObject::isGeneratedObject()
    {
        return mHandler;
    }
}




