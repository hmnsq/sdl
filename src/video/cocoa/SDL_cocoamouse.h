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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_cocoamouse_h_
#परिभाषय SDL_cocoamouse_h_

#अन्तर्भाव "SDL_cocoavideo.h"

बाह्य bool Cocoa_InitMouse(SDL_VideoDevice *_this);
बाह्य NSWindow *Cocoa_GetMouseFocus(शून्य);
बाह्य शून्य Cocoa_HandleMouseEvent(SDL_VideoDevice *_this, NSEvent *event);
बाह्य शून्य Cocoa_HandleMouseWheel(SDL_गवाक्षः *गवाक्षः, NSEvent *event);
बाह्य शून्य Cocoa_HandleMouseWarp(CGFloat x, CGFloat y);
बाह्य शून्य Cocoa_QuitMouse(SDL_VideoDevice *_this);

बाह्य शून्य Cocoa_InitGCMouse(शून्य);
बाह्य bool Cocoa_GCMouse_Relative_बहुलकम्(शून्य);
बाह्य bool Cocoa_HasGCMouse(शून्य);
बाह्य शून्य Cocoa_QuitGCMouse(शून्य);

संरचना SDL_Cursor_दत्त
{
    NSTimer *frameTimer;
    पूर्णाङ्क current_frame;

    पूर्णाङ्क अङ्कः_cursors;
    संरचना
    {
        शून्य *cursor;
        Uint32 duration;
    } चौकटाः[];
};

प्रकारनिर्देश संरचना
{
    // Whether we've seen a cursor warp since the last move event.
    bool आलोकितम्_Warp;
    // What location our last cursor warp was to.
    CGFloat चरमः_Warp_X;
    CGFloat चरमः_Warp_Y;
    // What location we last saw the cursor move to.
    CGFloat चरमः_Move_X;
    CGFloat चरमः_Move_Y;
} SDL_Mouse_दत्त;

@interface NSCursor (InvisibleCursor)
+ (NSCursor *)invisibleCursor;
@अन्तः

#यदि_अन्तः // SDL_cocoamouse_h_
