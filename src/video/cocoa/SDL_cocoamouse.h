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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_cocoamouse_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_cocoamouse_h_

#ಅನ್ತರ್ಭಾವ "SDL_cocoavideo.h"

ಬಾಹ್ಯ bool Cocoa_InitMouse(SDL_VideoDevice *_this);
ಬಾಹ್ಯ NSWindow *Cocoa_GetMouseFocus(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_HandleMouseEvent(SDL_VideoDevice *_this, NSEvent *event);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_HandleMouseWheel(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, NSEvent *event);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_HandleMouseWarp(CGFloat x, CGFloat y);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_QuitMouse(SDL_VideoDevice *_this);

ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_InitGCMouse(ಶೂನ್ಯ);
ಬಾಹ್ಯ bool Cocoa_GCMouse_Relative_ಬಹುಲಕ(ಶೂನ್ಯ);
ಬಾಹ್ಯ bool Cocoa_HasGCMouse(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_QuitGCMouse(ಶೂನ್ಯ);

ರಚನೆ SDL_Cursor_ದತ್ತಾಂಶ
{
    NSTimer *ಚೌಕಟ್ಟು_Timer;
    ಪೂರ್ಣಾಂಕ current_ಚೌಕಟ್ಟು;

    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_cursors;
    ರಚನೆ
    {
        ಶೂನ್ಯ *cursor;
        Uint32 duration;
    } ಚೌಕಟ್ಟುಗಳು[];
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    // Whether we've seen a cursor warp since the last move event.
    bool ನೋಡಿದ_Warp;
    // What location our last cursor warp was to.
    CGFloat ಕೊನೆಯ_Warp_X;
    CGFloat ಕೊನೆಯ_Warp_Y;
    // What location we last saw the cursor move to.
    CGFloat ಕೊನೆಯ_Move_X;
    CGFloat ಕೊನೆಯ_Move_Y;
} SDL_Mouse_ದತ್ತಾಂಶ;

@interface NSCursor (InvisibleCursor)
+ (NSCursor *)invisibleCursor;
@ಕೊನೆ

#ಆದರೆ_ಅಂತ್ಯ // SDL_cocoamouse_h_
