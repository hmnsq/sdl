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
#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_cocoamouse_h_
#define SDL_cocoamouse_h_

#அந்தர்பாவ "SDL_cocoavideo.h"

வெளி bool Cocoa_InitMouse(SDL_VideoDevice *_this);
வெளி NSWindow *Cocoa_GetMouseFocus(வெறுமை);
வெளி வெறுமை Cocoa_HandleMouseEvent(SDL_VideoDevice *_this, NSEvent *event);
வெளி வெறுமை Cocoa_HandleMouseWheel(SDL_Window *window, NSEvent *event);
வெளி வெறுமை Cocoa_HandleMouseWarp(CGFloat x, CGFloat y);
வெளி வெறுமை Cocoa_QuitMouse(SDL_VideoDevice *_this);

வெளி வெறுமை Cocoa_InitGCMouse(வெறுமை);
வெளி bool Cocoa_GCMouseRelativeMode(வெறுமை);
வெளி bool Cocoa_HasGCMouse(வெறுமை);
வெளி வெறுமை Cocoa_QuitGCMouse(வெறுமை);

கட்டமைப்பு SDL_CursorData
{
    NSTimer *frameTimer;
    முழு current_frame;

    முழு இலக்கம்_cursors;
    கட்டமைப்பு
    {
        வெறுமை *cursor;
        Uint32 duration;
    } frames[];
};

வகைவரை கட்டமைப்பு
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
