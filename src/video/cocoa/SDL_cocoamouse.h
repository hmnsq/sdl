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
#ضمن "SDL_internal.h"

#که_نه_تعریف_شوی SDL_cocoamouse_h_
#تعریف_کړه SDL_cocoamouse_h_

#ضمن "SDL_cocoavideo.h"

خارجي bool Cocoa_InitMouse(SDL_VideoDevice *_this);
خارجي NSWindow *Cocoa_GetMouseFocus(فراغ);
خارجي فراغ Cocoa_HandleMouseEvent(SDL_VideoDevice *_this, NSEvent *event);
خارجي فراغ Cocoa_HandleMouseWheel(SDL_کړکۍ *کړکۍ, NSEvent *event);
خارجي فراغ Cocoa_HandleMouseWarp(CGFloat x, CGFloat y);
خارجي فراغ Cocoa_QuitMouse(SDL_VideoDevice *_this);

خارجي فراغ Cocoa_InitGCMouse(فراغ);
خارجي bool Cocoa_GCMouse_Relative_ډېرپېښ(فراغ);
خارجي bool Cocoa_HasGCMouse(فراغ);
خارجي فراغ Cocoa_QuitGCMouse(فراغ);

بنية SDL_Cursor_معلومات
{
    NSTimer *چوکاټ_Timer;
    صحيح current_چوکاټ;

    صحيح عدد_cursors;
    بنية
    {
        فراغ *cursor;
        Uint32 duration;
    } چوکاټونه[];
};

تعريفنوع بنية
{
    // Whether we've seen a cursor warp since the last move event.
    bool کتل_شوی_Warp;
    // What location our last cursor warp was to.
    CGFloat وروستی_Warp_X;
    CGFloat وروستی_Warp_Y;
    // What location we last saw the cursor move to.
    CGFloat وروستی_Move_X;
    CGFloat وروستی_Move_Y;
} SDL_Mouse_معلومات;

@interface NSCursor (InvisibleCursor)
+ (NSCursor *)invisibleCursor;
@پای_ټکی

#د_که_پای // SDL_cocoamouse_h_
