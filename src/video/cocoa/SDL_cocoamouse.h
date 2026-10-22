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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_cocoamouse_h_
#define SDL_cocoamouse_h_

#ଅନ୍ତର୍ଭାଵ "SDL_cocoavideo.h"

ବାହ୍ୟ bool Cocoa_InitMouse(SDL_VideoDevice *_this);
ବାହ୍ୟ NSWindow *Cocoa_GetMouseFocus(ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_HandleMouseEvent(SDL_VideoDevice *_this, NSEvent *event);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_HandleMouseWheel(SDL_Window *window, NSEvent *event);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_HandleMouseWarp(CGFloat x, CGFloat y);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_QuitMouse(SDL_VideoDevice *_this);

ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_InitGCMouse(ଶୂନ୍ୟ);
ବାହ୍ୟ bool Cocoa_GCMouseRelativeMode(ଶୂନ୍ୟ);
ବାହ୍ୟ bool Cocoa_HasGCMouse(ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_QuitGCMouse(ଶୂନ୍ୟ);

ସଂରଚନା SDL_CursorData
{
    NSTimer *frameTimer;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା current_frame;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_cursors;
    ସଂରଚନା
    {
        ଶୂନ୍ୟ *cursor;
        Uint32 duration;
    } frames[];
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
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
