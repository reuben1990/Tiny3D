//
//  AppDelegate.h
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import "OpenGLView.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (weak) IBOutlet NSWindow *window;
//- (OpenGLView*)createGLView:(NSInteger)width height:(NSInteger)height;
@end