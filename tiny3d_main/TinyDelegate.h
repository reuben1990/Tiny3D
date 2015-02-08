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
#include "TinySingleton.h"

namespace Tiny
{
    class TinyDelegate : public TinyObject, public TinySingleton<TinyDelegate>
    {
    public:
        TinyDelegate();
        virtual ~TinyDelegate();
        virtual void initialize();
    private:
    };
}


#endif /* defined(__proj_mac__TinyDelegate__) */
