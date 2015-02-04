//
//  TinySchedulerManager.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinySchedulerManager.h"

namespace Tiny
{
    TinyScheduleManager *TinyScheduleManager::sSingleton = nullptr;
    
    TinyScheduleManager::TinyScheduleManager()
    {
        
    }
    
    TinyScheduleManager::~TinyScheduleManager()
    {
        
    }
    
    TinyScheduleManager *TinyScheduleManager::getSingleton()
    {
        if (sSingleton == nullptr)
        {
            sSingleton = new TinyScheduleManager();
            sSingleton->initialize();
        }
        return sSingleton;
    }
    
    void TinyScheduleManager::initialize()
    {
        
    }
    
    void TinyScheduleManager::timeStep(float timeInterval)
    {
        
    }
}