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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_cocoamouse_h_
#घोषणा SDL_cocoamouse_h_

#समावेश "SDL_cocoavideo.h"

बाह्य bool Cocoa_InitMouse(SDL_VideoDevice *_this);
बाह्य NSWindow *Cocoa_GetMouseFocus(व्योम);
बाह्य व्योम Cocoa_HandleMouseEvent(SDL_VideoDevice *_this, NSEvent *event);
बाह्य व्योम Cocoa_HandleMouseWheel(SDL_Window *window, NSEvent *event);
बाह्य व्योम Cocoa_HandleMouseWarp(CGFloat x, CGFloat y);
बाह्य व्योम Cocoa_QuitMouse(SDL_VideoDevice *_this);

बाह्य व्योम Cocoa_InitGCMouse(व्योम);
बाह्य bool Cocoa_GCMouseRelativeMode(व्योम);
बाह्य bool Cocoa_HasGCMouse(व्योम);
बाह्य व्योम Cocoa_QuitGCMouse(व्योम);

काष्ठा SDL_Cursor_तथ्य
{
    NSTimer *frameTimer;
    पूर्णांक current_frame;

    पूर्णांक अंक_cursors;
    काष्ठा
    {
        व्योम *cursor;
        Uint32 duration;
    } frames[];
};

प्रकार काष्ठा
{
    // Whether we've seen a cursor warp since the last move event.
    bool seenWarp;
    // What location our last cursor warp was to.
    CGFloat lastWarpX;
    CGFloat lastWarpY;
    // What location we last saw the cursor move to.
    CGFloat lastMoveX;
    CGFloat lastMoveY;
} SDL_Mouse_तथ्य;

@interface NSCursor (InvisibleCursor)
+ (NSCursor *)invisibleCursor;
@end

#पूर्ण_अगर // SDL_cocoamouse_h_
