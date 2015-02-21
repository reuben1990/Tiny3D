//
//  TinyCommon.h
//  proj_mac
//
//  Created by reuben chao on 2/12/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinyCommon_h
#define proj_mac_TinyCommon_h

#include <map>
#include <iostream>
#include <string>
#include <sstream>

namespace Tiny
{
    typedef std::map<std::string, const void*> TinyNameValuePairList;
    
    class TinyNameGenerator
    {
    protected:
        std::string mPrefix;
        unsigned long long int mNext;
    public:
//        TinyNameGenerator(const TinyNameGenerator& rhs)
//        : mPrefix(rhs.mPrefix), mNext(rhs.mNext) {}
        
        TinyNameGenerator(const std::string prefix) : mPrefix(prefix), mNext(1) {}
        
        /// Generate a new name
        std::string generate()
        {
            std::ostringstream s;
            s << mPrefix << mNext++;
            return s.str();
        }
        
        /// Reset the internal counter
        void reset()
        {
            mNext = 1ULL;
        }
        
        /// Manually set the internal counter (use caution)
        void setNext(unsigned long long int val)
        {
            mNext = val;
        }
        
        /// Get the internal counter
        unsigned long long int getNext() const
        {
            // lock even on get because 64-bit may not be atomic read
            return mNext;
        }
    };
}

#endif
