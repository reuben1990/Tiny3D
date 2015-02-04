//
//  TinyRoot.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyRoot_h
#define proj_mac_TinyRoot_h

namespace Tiny {
    class TinyRoot
    {
    public:
        static TinyRoot *getSingleton();
        TinyRoot();
        ~TinyRoot();
        void renderOneFrame(float timeInterval);
        void updateAllRenderTargets();
        void onWindowUpdate(float width, float height);
    private:
        static TinyRoot *sSingleton;
        
    };
}

#endif
