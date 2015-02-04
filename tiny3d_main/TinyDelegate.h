//
//  TinyDelegate.h
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef __proj_mac__TinyDelegate__
#define __proj_mac__TinyDelegate__

#include "TinyObject.h"

namespace Tiny
{
    class TinyDelegate : public TinyObject
    {
    public:
        TinyDelegate();
        virtual ~TinyDelegate();
        static TinyDelegate *getSingleton();
        virtual void initialize();
    private:
        bool mIsSchedule;
        static TinyDelegate *sSingleTon;
    };
}


#endif /* defined(__proj_mac__TinyDelegate__) */
