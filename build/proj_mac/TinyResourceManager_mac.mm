//
//  TinyResourceManager_mac.cpp
//  proj_mac
//
//  Created by reuben chao on 2/19/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include <cstdio>
#import <Foundation/Foundation.h>
#include "TinyResourceManager.h"
#include "TinyPlatform.h"

namespace Tiny
{
    void TinyResourceManager::getFileData(const std::string& fileName, uint8** data, uint32& length)
    {
        NSString *nsFileName = [[NSString alloc] initWithUTF8String:fileName.c_str()];
        NSString *fullPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:nsFileName];
        
        NSFileManager *fileManager = [NSFileManager defaultManager];
        if ([fileManager fileExistsAtPath:fullPath] == NO)
        {
            NSLog(@"%@ not exist", fullPath);
        }
        else
        {
            NSData *fileData = [[NSData alloc] initWithContentsOfFile:fullPath];
            uint32 dataLength = (uint32)[fileData length];
            length = dataLength;
            *data = (uint8*)malloc(dataLength + 2);
            uint8* bytes = (uint8*)[fileData bytes];
            memcpy(*data, bytes, dataLength);
            const void* endChar = "\0";
            memcpy(*data + dataLength, endChar, 1);
        }
    }
}