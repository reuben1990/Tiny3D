//
//  TinyNode.h
//  proj_mac
//
//  Created by reuben chao on 2/8/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyNode__
#define __proj_mac__TinyNode__

#include <stdio.h>
#include "TinyObject.h"
#include <set>
#include <map>
#include <string>

namespace Tiny
{

    class TinyNode : public TinyObject
    {
    public:
        TinyNode(std::string &name);
        ~TinyNode();
        TinyNode* createChild();
        void addChild(TinyNode* node);
        void removeChild(TinyNode* node);
        void getChild(std::string& name);
        void update();
        void setPosition(kmVec3 &pos);
        void setScale(kmVec3 &scale);
        void setOrientation(kmVec3 &orientation);
        void updateFromParent();
        kmVec3& getPosition();
        kmVec3& getScale();
        kmVec3& getOrientation();
        kmVec3& getDerivedPosition();
        kmVec3& getDerivedScale();
        kmQuaternion& getDerivedOrientation();
        std::string& getName();
        TinyNode* getParent();
        void setParent(TinyNode* parent);
    protected:
        kmVec3 mPosition;
        kmVec3 mDerivedPosition;
        kmQuaternion mOrientation;
        kmQuaternion mDerivedOrientation;
        kmVec3 mScale;
        kmVec3 mDerivedScale;
        TinyNode* parent;
        std::map<std::string, TinyNode*> mChildren;
        std::string mName;
    };
}
#endif /* defined(__proj_mac__TinyNode__) */
