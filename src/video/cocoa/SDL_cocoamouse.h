/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#অন্তর্ভাৱ "SDL_internal.h"

#ifndef SDL_cocoamouse_h_
#define SDL_cocoamouse_h_

#অন্তর্ভাৱ "SDL_cocoavideo.h"

বাহ্য bool Cocoa_InitMouse(SDL_VideoDevice *_this);
বাহ্য NSWindow *Cocoa_GetMouseFocus(শূন্য);
বাহ্য শূন্য Cocoa_HandleMouseEvent(SDL_VideoDevice *_this, NSEvent *event);
বাহ্য শূন্য Cocoa_HandleMouseWheel(SDL_Window *window, NSEvent *event);
বাহ্য শূন্য Cocoa_HandleMouseWarp(CGFloat x, CGFloat y);
বাহ্য শূন্য Cocoa_QuitMouse(SDL_VideoDevice *_this);

বাহ্য শূন্য Cocoa_InitGCMouse(শূন্য);
বাহ্য bool Cocoa_GCMouseRelativeMode(শূন্য);
বাহ্য bool Cocoa_HasGCMouse(শূন্য);
বাহ্য শূন্য Cocoa_QuitGCMouse(শূন্য);

সংরচনা SDL_CursorData
{
    NSTimer *frameTimer;
    পূর্ণাঙ্ক current_frame;

    পূর্ণাঙ্ক অঙ্ক_cursors;
    সংরচনা
    {
        শূন্য *cursor;
        Uint32 duration;
    } frames[];
};

প্রকারনির্দেশ সংরচনা
{
    // Whether we've seen a cursor warp since the last move event.
    bool seenWarp;
    // What location our last cursor warp was to.
    CGFloat lastWarpX;
    CGFloat lastWarpY;
    // What location we last saw the cursor move to.
    CGFloat lastMoveX;
    CGFloat lastMoveY;
} SDL_MouseData;

@interface NSCursor (InvisibleCursor)
+ (NSCursor *)invisibleCursor;
@end

#endif // SDL_cocoamouse_h_
