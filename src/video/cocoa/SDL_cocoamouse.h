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

#جيڪڏهن_وصف_نه_ٿيل SDL_cocoamouse_h_
#وصف_ڪريو SDL_cocoamouse_h_

#ضمن "SDL_cocoavideo.h"

خارجي bool Cocoa_InitMouse(SDL_VideoDevice *_this);
خارجي NSWindow *Cocoa_GetMouseFocus(فراغ);
خارجي فراغ Cocoa_HandleMouseEvent(SDL_VideoDevice *_this, NSEvent *event);
خارجي فراغ Cocoa_HandleMouseWheel(SDL_دري *دري, NSEvent *event);
خارجي فراغ Cocoa_HandleMouseWarp(CGFloat x, CGFloat y);
خارجي فراغ Cocoa_QuitMouse(SDL_VideoDevice *_this);

خارجي فراغ Cocoa_InitGCMouse(فراغ);
خارجي bool Cocoa_GCMouse_Relative_گهڻائي(فراغ);
خارجي bool Cocoa_HasGCMouse(فراغ);
خارجي فراغ Cocoa_QuitGCMouse(فراغ);

بنية SDL_Cursor_معلومات
{
    NSTimer *چوکٺو_Timer;
    صحيح current_چوکٺو;

    صحيح انگ_cursors;
    بنية
    {
        فراغ *cursor;
        Uint32 duration;
    } چوکٺا[];
};

تعريفنوع بنية
{
    // Whether we've seen a cursor warp since the last move event.
    bool ڏٺل_Warp;
    // What location our last cursor warp was to.
    CGFloat آخري_Warp_X;
    CGFloat آخري_Warp_Y;
    // What location we last saw the cursor move to.
    CGFloat آخري_Move_X;
    CGFloat آخري_Move_Y;
} SDL_Mouse_معلومات;

@interface NSCursor (InvisibleCursor)
+ (NSCursor *)invisibleCursor;
@پڇاڙي

#جيڪڏهن_پورو // SDL_cocoamouse_h_
