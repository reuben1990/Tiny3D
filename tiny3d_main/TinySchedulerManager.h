//
//  TinySchedulerManager.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinySchedulerManager_h
#define proj_mac_TinySchedulerManager_h

#include "TinyObject.h"

namespace Tiny
{
    class TinyScheduleManager : public TinyObject
    {
    public:
        TinyScheduleManager();
        virtual ~TinyScheduleManager();
        static TinyScheduleManager *getSingleton();
        void initialize();
        void timeStep(float timeInterval);
    private:
        static TinyScheduleManager *sSingleton;
        
    };
}

#endif
