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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_cocoamouse_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_cocoamouse_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_cocoavideo.h"

ਬਾਹਰੀ bool Cocoa_InitMouse(SDL_VideoDevice *_this);
ਬਾਹਰੀ NSWindow *Cocoa_GetMouseFocus(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_HandleMouseEvent(SDL_VideoDevice *_this, NSEvent *event);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_HandleMouseWheel(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, NSEvent *event);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_HandleMouseWarp(CGFloat x, CGFloat y);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_QuitMouse(SDL_VideoDevice *_this);

ਬਾਹਰੀ ਖਾਲੀ Cocoa_InitGCMouse(ਖਾਲੀ);
ਬਾਹਰੀ bool Cocoa_GCMouse_Relative_ਬਹੁਲਕ(ਖਾਲੀ);
ਬਾਹਰੀ bool Cocoa_HasGCMouse(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_QuitGCMouse(ਖਾਲੀ);

ਬਣਤਰ SDL_Cursor_ਅੰਕੜੇ
{
    NSTimer *ਚੌਖਟਾ_Timer;
    ਪੂਰਨ current_ਚੌਖਟਾ;

    ਪੂਰਨ ਅੰਕ_cursors;
    ਬਣਤਰ
    {
        ਖਾਲੀ *cursor;
        Uint32 duration;
    } ਚੌਖਟੇ[];
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    // Whether we've seen a cursor warp since the last move event.
    bool ਵੇਖਿਆ_Warp;
    // What location our last cursor warp was to.
    CGFloat ਆਖਰੀ_Warp_X;
    CGFloat ਆਖਰੀ_Warp_Y;
    // What location we last saw the cursor move to.
    CGFloat ਆਖਰੀ_Move_X;
    CGFloat ਆਖਰੀ_Move_Y;
} SDL_Mouse_ਅੰਕੜੇ;

@interface NSCursor (InvisibleCursor)
+ (NSCursor *)invisibleCursor;
@ਸਿਰਾ

#ਜੇ_ਅੰਤ // SDL_cocoamouse_h_
