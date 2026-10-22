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

#اگر_غیر_تعریف_شدہ SDL_cocoamouse_h_
#تعریف_کرو SDL_cocoamouse_h_

#شامل "SDL_cocoavideo.h"

خارجی bool Cocoa_InitMouse(SDL_VideoDevice *_this);
خارجی NSWindow *Cocoa_GetMouseFocus(خالی);
خارجی خالی Cocoa_HandleMouseEvent(SDL_VideoDevice *_this, NSEvent *event);
خارجی خالی Cocoa_HandleMouseWheel(SDL_کھڑکی *کھڑکی, NSEvent *event);
خارجی خالی Cocoa_HandleMouseWarp(CGFloat x, CGFloat y);
خارجی خالی Cocoa_QuitMouse(SDL_VideoDevice *_this);

خارجی خالی Cocoa_InitGCMouse(خالی);
خارجی bool Cocoa_GCMouse_Relative_منوال(خالی);
خارجی bool Cocoa_HasGCMouse(خالی);
خارجی خالی Cocoa_QuitGCMouse(خالی);

ساخت SDL_Cursor_ڈیٹا
{
    NSTimer *چوکھٹا_Timer;
    صحیح current_چوکھٹا;

    صحیح عدد_cursors;
    ساخت
    {
        خالی *cursor;
        Uint32 duration;
    } چوکھٹے[];
};

قسمتعریف ساخت
{
    // Whether we've seen a cursor warp since the last move event.
    bool نظر_آیا_Warp;
    // What location our last cursor warp was to.
    CGFloat آخری_Warp_X;
    CGFloat آخری_Warp_Y;
    // What location we last saw the cursor move to.
    CGFloat آخری_Move_X;
    CGFloat آخری_Move_Y;
} SDL_Mouse_ڈیٹا;

@interface NSCursor (InvisibleCursor)
+ (NSCursor *)invisibleCursor;
@انتہا

#اگر_ختم // SDL_cocoamouse_h_
