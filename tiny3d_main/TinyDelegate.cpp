//
//  TinyDelegate.cpp
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyDelegate.h"
#include "TinyInputManager.h"
#include "TinyRoot.h"

namespace Tiny
{
    TinyDelegate *TinyDelegate::sSingleTon = NULL;

    TinyDelegate::TinyDelegate()
    {
        
    }

    TinyDelegate::~TinyDelegate()
    {
        
    }

    void TinyDelegate::initialize()
    {
        
    }
    
    TinyDelegate *TinyDelegate::getSingleton()
    {
        if (sSingleTon == NULL)
        {
            sSingleTon = new TinyDelegate();
            sSingleTon->initialize();
        }
        return sSingleTon;
    }
}