 //
//  OpenGLView.m
//  proj_mac
//
//  Created by reuben chao on 2/2/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#import <OpenGL/gl3.h>
#import "OpenGLView.h"
#import "TinyInputManager.h"
#include "TinyMouse.h"
#include "TinyKeyboard.h"
#include "TinyRoot.h"
#include <vector>
#include <string>
#include "kazmath/kazmath.h"
#include "TinyMath.h"
#include "TinyDelegate.h"


@implementation OpenGLView

- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat*)format
{
    self = [super initWithFrame:frameRect pixelFormat:format];
    if (self)
    {
        NSTrackingArea *trackingArea = [[NSTrackingArea alloc] initWithRect:[self bounds]
            options: (NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveInKeyWindow )
            owner:self
            userInfo:nil];
        [self addTrackingArea:trackingArea];
    }
    
    //create mouse and keyboard delegate
    Tiny::TinyInputObject *inputObject_mouse = Tiny::TinyInputManager::getSingleton()->getInputObject(Tiny::InputDevice::Mouse);
    mMouse = (Tiny::TinyMouse *)inputObject_mouse;
    Tiny::TinyInputObject *inputObject_keyboard = Tiny::TinyInputManager::getSingleton()->getInputObject(Tiny::InputDevice::Keyboard);
    mKeyBoard = (Tiny::TinyKeyboard *)inputObject_keyboard;
    
    
    
    return self;
}

- (void)update  // moved or resized
{
    [super update];
    
    [[self openGLContext] makeCurrentContext];
    [[self openGLContext] update];
}

- (void)reshape
{
    [super reshape];
    
    [[self openGLContext] makeCurrentContext];
    [[self openGLContext] update];
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

#pragma mark - keyboard and mouse event

- (void)keyDown:(NSEvent *)theEvent
{
    //[super keyDown:theEvent];
    NSString *characters = [theEvent characters];
    std::string keys;
    for (NSUInteger i = 0; i < [characters length]; ++i)
    {
        unichar character = [characters characterAtIndex:i];
        Tiny::TinyKeyEvent event;
        event.mKeyCode = character;
        mKeyBoard->keyPressed(&event);
    }
    //NSLog(@"keyDown: %@", characters);
}

- (void)keyUp:(NSEvent *)theEvent
{
    //[super keyUp:theEvent];
    NSString *characters = [theEvent characters];
    std::string keys;
    for (NSUInteger i = 0; i < [characters length]; ++i)
    {
        unichar character = [characters characterAtIndex:i];
        Tiny::TinyKeyEvent event;
        event.mKeyCode = character;
        mKeyBoard->keyReleased(&event);
    }
    //NSLog(@"keyUp: %@", characters);
}

- (void)mouseMoved:(NSEvent *)theEvent
{
    //[super mouseMoved:theEvent];
    
    Tiny::TinyMouseEvent event;
    event.state.deltaX = [theEvent deltaX];
    event.state.deltaY = [theEvent deltaY];
    
    NSPoint location = [theEvent locationInWindow];;
    kmVec2 vec2 = Tiny::kmVec2Make(location.x, location.y);
    
    mMouse->setLocation(&vec2);
    mMouse->mouseMoved(&event);
    //NSLog(@"mouseMoved: x:%f y:%f", x, y);
}

- (void)mouseDown:(NSEvent *)theEvent
{
    //[super mouseDown:theEvent];
    NSPoint location = [theEvent locationInWindow];
    Tiny::TinyMouseEvent event;
    kmVec2 vec2 = Tiny::kmVec2Make(location.x, location.y);
    mMouse->setLocation(&vec2);
    mMouse->mousePressed(&event, Tiny::TinyMouseButtonID::MB_Left);
    //NSLog(@"mouseDown: location:%f %f", location.x, location.y);
}

- (void)mouseUp:(NSEvent *)theEvent
{
    //[super mouseUp:theEvent];
    NSPoint location = [theEvent locationInWindow];
    Tiny::TinyMouseEvent event;
    kmVec2 vec2 = Tiny::kmVec2Make(location.x, location.y);
    mMouse->setLocation(&vec2);
    mMouse->mouseReleased(&event, Tiny::TinyMouseButtonID::MB_Left);
    //NSLog(@"mouseUp: location:%f %f", location.x, location.y);
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
    //[super rightMouseDown:theEvent];
//    NSPoint location = [theEvent locationInWindow];
//    [[TinyInputManager sharedInputController] mouseRightDown:location];
    //NSLog(@"rightMouseDown: location:%f %f", location.x, location.y);
}

- (void)rightMouseUp:(NSEvent *)theEvent
{
    //[super rightMouseUp:theEvent];
//    NSPoint location = [theEvent locationInWindow];
//    [[TinyInputManager sharedInputController] mouseRightUp:location];
    //NSLog(@"rightMouseUp: location:%f %f", location.x, location.y);
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    //[super mouseDragged:theEvent];
//    CGFloat x = [theEvent deltaX];
//    CGFloat y = [theEvent deltaY];
//    [[TinyInputManager sharedInputController] mouseLeftDragWithX:x andY:y];
    //NSLog(@"mouseDragged: x:%f y:%f", x, y);
}

- (void)rightMouseDragged:(NSEvent *)theEvent
{
    //[super rightMouseDragged:theEvent];
//    CGFloat x = [theEvent deltaX];
//    CGFloat y = [theEvent deltaY];
//    [[TinyInputManager sharedInputController] mouseRightDragWithX:x andY:y];
    //NSLog(@"rightMouseDragged: x:%f y:%f", x, y);
}

- (void)scrollWheel:(NSEvent *)theEvent
{
    //[super scrollWheel:theEvent];
//    CGFloat x = [theEvent scrollingDeltaX];
//    CGFloat y = [theEvent scrollingDeltaY];
//    [[TinyInputManager sharedInputController] mouseScrollWithX:x andY:y];
    //NSLog(@"scrollWheel: x:%f y:%f", x, y);
}

- (void)mouseEntered:(NSEvent *)theEvent
{
    //[super mouseEntered:theEvent];
    //NSLog(@"mouseEntered");
}

- (void)mouseExited:(NSEvent *)theEvent
{
    //[super mouseExited:theEvent];
    //NSLog(@"mouseExited");
}

- (void)cursorUpdate:(NSEvent *)theEvent
{
    //[super cursorUpdate:theEvent];
    //NSLog(@"cursorUpdate");
}

@end
