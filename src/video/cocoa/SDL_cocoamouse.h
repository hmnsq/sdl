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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_cocoamouse_h_
#నిర్వచించు SDL_cocoamouse_h_

#అన్తర్భావ "SDL_cocoavideo.h"

బాహ్య bool Cocoa_InitMouse(SDL_VideoDevice *_this);
బాహ్య NSWindow *Cocoa_GetMouseFocus(శూన్య);
బాహ్య శూన్య Cocoa_HandleMouseEvent(SDL_VideoDevice *_this, NSEvent *event);
బాహ్య శూన్య Cocoa_HandleMouseWheel(SDL_కిటికీ *కిటికీ, NSEvent *event);
బాహ్య శూన్య Cocoa_HandleMouseWarp(CGFloat x, CGFloat y);
బాహ్య శూన్య Cocoa_QuitMouse(SDL_VideoDevice *_this);

బాహ్య శూన్య Cocoa_InitGCMouse(శూన్య);
బాహ్య bool Cocoa_GCMouse_Relative_బహుళకం(శూన్య);
బాహ్య bool Cocoa_HasGCMouse(శూన్య);
బాహ్య శూన్య Cocoa_QuitGCMouse(శూన్య);

నిర్మాణం SDL_Cursor_దత్తాంశం
{
    NSTimer *చట్రం_Timer;
    పూర్ణాంకం current_చట్రం;

    పూర్ణాంకం అంకె_cursors;
    నిర్మాణం
    {
        శూన్య *cursor;
        Uint32 duration;
    } చట్రాలు[];
};

రకనిర్వచనం నిర్మాణం
{
    // Whether we've seen a cursor warp since the last move event.
    bool చూసిన_Warp;
    // What location our last cursor warp was to.
    CGFloat చివరి_Warp_X;
    CGFloat చివరి_Warp_Y;
    // What location we last saw the cursor move to.
    CGFloat చివరి_Move_X;
    CGFloat చివరి_Move_Y;
} SDL_Mouse_దత్తాంశం;

@interface NSCursor (InvisibleCursor)
+ (NSCursor *)invisibleCursor;
@చివర

#అయితే_ముగింపు // SDL_cocoamouse_h_
