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
#شامل "SDL_internal.h"

#ifndef SDL_cocoamouse_h_
#define SDL_cocoamouse_h_

#شامل "SDL_cocoavideo.h"

بیرونی bool Cocoa_InitMouse(SDL_VideoDevice *_this);
بیرونی NSWindow *Cocoa_GetMouseFocus(تهی);
بیرونی تهی Cocoa_HandleMouseEvent(SDL_VideoDevice *_this, NSEvent *event);
بیرونی تهی Cocoa_HandleMouseWheel(SDL_Window *window, NSEvent *event);
بیرونی تهی Cocoa_HandleMouseWarp(CGFloat x, CGFloat y);
بیرونی تهی Cocoa_QuitMouse(SDL_VideoDevice *_this);

بیرونی تهی Cocoa_InitGCMouse(تهی);
بیرونی bool Cocoa_GCMouseRelativeMode(تهی);
بیرونی bool Cocoa_HasGCMouse(تهی);
بیرونی تهی Cocoa_QuitGCMouse(تهی);

ساختار SDL_CursorData
{
    NSTimer *frameTimer;
    صحیح current_frame;

    صحیح رقم_cursors;
    ساختار
    {
        تهی *cursor;
        Uint32 duration;
    } frames[];
};

تعریفنوع ساختار
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
