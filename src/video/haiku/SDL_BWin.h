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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_BWin_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_BWin_h_

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"
#ಅನ್ತರ್ಭಾವ "SDL_bframebuffer.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <AppKit.h>
#ಅನ್ತರ್ಭಾವ <Cursor.h>
#ಅನ್ತರ್ಭಾವ <InterfaceKit.h>
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
#ಅನ್ತರ್ಭಾವ <opengl/GLView.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "../../core/haiku/SDL_BApp.h"

ಎಣಿಕೆ WinCommands
{
    BWIN_MOVE_ಕಿಟಕಿ,
    BWIN_RESIZE_ಕಿಟಕಿ,
    BWIN_SHOW_ಕಿಟಕಿ,
    BWIN_HIDE_ಕಿಟಕಿ,
    BWIN_MAXIMIZE_ಕಿಟಕಿ,
    BWIN_MINIMIZE_ಕಿಟಕಿ,
    BWIN_RESTORE_ಕಿಟಕಿ,
    BWIN_ಗಣ_TITLE,
    BWIN_ಗಣ_BORDERED,
    BWIN_ಗಣ_RESIZABLE,
    BWIN_FULLSCREEN,
    BWIN_UPDATE_FRAMEBUFFER,
    BWIN_MINIMUM_ಗಾತ್ರ_ಕಿಟಕಿ
};

// non-OpenGL framebuffer view
class SDL_BView : ಸಾರ್ವಜನಿಕ BView
{
  ಸಾರ್ವಜನಿಕ:
    SDL_BView(BRect ಚೌಕಟ್ಟು, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, uint32 resizing_ಬಹುಲಕ)
        : BView(ಚೌಕಟ್ಟು, name, resizing_ಬಹುಲಕ, B_WILL_DRAW),
          fBitmap(ಖಾಲಿ)
    {
    }

    ಶೂನ್ಯ Draw(BRect dirty)
    {
        ಆದರೆ (fBitmap != ಖಾಲಿ)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    ಶೂನ್ಯ ಗಣ_Bitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  ಖಾಸಗಿ:
    BBitmap *fBitmap;
};

class SDL_BWin : ಸಾರ್ವಜನಿಕ BWindow
{
  ಸಾರ್ವಜನಿಕ:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, ಕಿಟಕಿ_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_ಸಾಮಾನ್ಯ_ಕಿಟಕಿ_FEEL, flags)
    {
        ಕೊನೆಯ_buttons = 0;

        _cur_view = ಖಾಲಿ;
        _SDL_View = ಖಾಲಿ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
        _SDL_GLView = ಖಾಲಿ;
        _gl_type = 0;
#ಆದರೆ_ಅಂತ್ಯ
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        prev_ಚೌಕಟ್ಟು = ಖಾಲಿ;
        _fullscreen = ಖಾಲಿ;

        // Handle framebuffer stuff
        ಬಫರ್_locker = new BLocker();
        _bitmap = ಖಾಲಿ;
    }

    ವಾಸ್ತವಿಕ ~SDL_BWin()
    {
        ಬೀಗ();

        ಆದರೆ (_SDL_View != ಖಾಲಿ && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = ಖಾಲಿ;
        }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
        ಆದರೆ (_SDL_GLView) {
            ಆದರೆ (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->ಗಣ_Current_Context(ಖಾಲಿ);
            ಆದರೆ (_SDL_GLView == _cur_view)
                Remove_ಮಗು(_SDL_GLView);
            _SDL_GLView = ಖಾಲಿ;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#ಆದರೆ_ಅಂತ್ಯ
        Unlock();

        delete prev_ಚೌಕಟ್ಟು;

        // Clean up framebuffer stuff
        ಬಫರ್_locker->ಬೀಗ();
        delete ಬಫರ್_locker;
    }

    ಶೂನ್ಯ ಗಣ_Current_View(BView *view)
    {
        ಆದರೆ (_cur_view != view) {
            ಆದರೆ (_cur_view != ಖಾಲಿ)
                Remove_ಮಗು(_cur_view);
            _cur_view = view;
            ಆದರೆ (_cur_view != ಖಾಲಿ)
                ಕೂಡಿಸು_ಮಗು(_cur_view);
        }
    }

    ಶೂನ್ಯ UpdateCurrentView()
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
        ಆದರೆ (_SDL_GLView != ಖಾಲಿ) {
            ಗಣ_Current_View(_SDL_GLView);
        } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (_SDL_View != ಖಾಲಿ) {
            ಗಣ_Current_View(_SDL_View);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಗಣ_Current_View(ಖಾಲಿ);
        }
    }

    SDL_BView *CreateView()
    {
        ಬೀಗ();
        ಆದರೆ (_SDL_View == ಖಾಲಿ) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        ಹಿಂತಿರುಗಿ _SDL_View;
    }

    ಶೂನ್ಯ RemoveView()
    {
        ಬೀಗ();
        ಆದರೆ (_SDL_View != ಖಾಲಿ) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = ಖಾಲಿ;
            UpdateCurrentView();
            delete oldView;
        }
        Unlock();
    }

    /* * * * * OpenGL functionality * * * * */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
    BGLView *CreateGLView(Uint32 gl_flags)
    {
        ಬೀಗ();
        ಆದರೆ (_SDL_GLView == ಖಾಲಿ) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_ಚೌಕಟ್ಟು_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        ಹಿಂತಿರುಗಿ _SDL_GLView;
    }

    ಶೂನ್ಯ RemoveGLView()
    {
        ಬೀಗ();
        ಆದರೆ (_SDL_GLView != ಖಾಲಿ) {
            ಆದರೆ (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->ಗಣ_Current_Context(ಖಾಲಿ);
            _SDL_GLView = ಖಾಲಿ;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    ಶೂನ್ಯ ಅದಲುಬದಲು_Buffers(ಶೂನ್ಯ)
    {
        _SDL_GLView->ಅದಲುಬದಲು_Buffers();
    }
#ಆದರೆ_ಅಂತ್ಯ

    /* * * * * Event sending * * * * */
    // Hook functions
    ವಾಸ್ತವಿಕ ಶೂನ್ಯ ಚೌಕಟ್ಟು_Moved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage ಸಂದೇಶ_2(BAPP_ಕಿಟಕಿ_MOVED);
        ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("window-x", (ಪೂರ್ಣಾಂಕ)origin.x);
        ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("window-y", (ಪೂರ್ಣಾಂಕ)origin.y);
        Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);

        // Perform normal hook operations
        BWindow::ಚೌಕಟ್ಟು_Moved(origin);
    }

    ಶೂನ್ಯ ಚೌಕಟ್ಟು_Resized(ದಶಮಾಂಶ ಅಗಲ, ದಶಮಾಂಶ ಎತ್ತರ)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage ಸಂದೇಶ_2(BAPP_ಕಿಟಕಿ_RESIZED);

        ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("window-w", (ಪೂರ್ಣಾಂಕ)ಅಗಲ + 1);
        ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("window-h", (ಪೂರ್ಣಾಂಕ)ಎತ್ತರ + 1);
        Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);

        // Perform normal hook operations
        BWindow::ಚೌಕಟ್ಟು_Resized(ಅಗಲ, ಎತ್ತರ);
    }

    bool QuitRequested()
    {
        BMessage ಸಂದೇಶ_2(BAPP_ಕಿಟಕಿ_CLOSE_REQUESTED);
        Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);

        // We won't allow a quit unless asked by DestroyWindow()
        ಹಿಂತಿರುಗಿ false;
    }

    ಶೂನ್ಯ ಕಿಟಕಿ_Activated(bool ಸಕ್ರಿಯ)
    {
        BMessage ಸಂದೇಶ_2(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        ಸಂದೇಶ_2.ಕೂಡಿಸು_Bool("focusGained", ಸಕ್ರಿಯ);
        Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);
    }

    ಶೂನ್ಯ Zoom(BPoint origin,
              ದಶಮಾಂಶ ಅಗಲ,
              ದಶಮಾಂಶ ಎತ್ತರ)
    {
        BMessage ಸಂದೇಶ_2(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);

        // Before the window zooms, record its size
        ಆದರೆ (!prev_ಚೌಕಟ್ಟು)
            prev_ಚೌಕಟ್ಟು = new BRect(ಚೌಕಟ್ಟು_2());

        // Perform normal hook operations
        BWindow::Zoom(origin, ಅಗಲ, ಎತ್ತರ);
    }

    // Member functions
    ಶೂನ್ಯ Show()
    {
        ಆಗ (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage ಸಂದೇಶ_2(BAPP_SHOW);
        Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);
    }

    ಶೂನ್ಯ Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage ಸಂದೇಶ_2(BAPP_HIDE);
        Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);
    }

    ಶೂನ್ಯ Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage ಸಂದೇಶ_2(minState);
        Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);
    }

    ಶೂನ್ಯ Screen_ಬದಲಾಯಿತು(BRect screen_ಚೌಕಟ್ಟು, color_space ಆಳ_2)
    {
        ಆದರೆ (_fullscreen) {
            Move_ಗಮ್ಯ(screen_ಚೌಕಟ್ಟು.ಎಡ, screen_ಚೌಕಟ್ಟು.ತುದಿ);
            Resize_ಗಮ್ಯ(screen_ಚೌಕಟ್ಟು.ಅಗಲ_2(), screen_ಚೌಕಟ್ಟು.ಎತ್ತರ_2());
        }
    }

    // BView message interruption
    ಶೂನ್ಯ Dispatch_ಸಂದೇಶ(BMessage *ಸಂದೇಶ_2, BHandler *ಗುರಿ)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 ಕೀಲಿ;     // Used for key events

        ಆಯ್ಕೆ (ಸಂದೇಶ_2->what) {
        ಸ್ಥಿತಿ B_MOUSE_MOVED:
            int32 transit;
            ಆದರೆ (ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_ಬಿಂದು("where", &where) == B_OK && ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ B_MOUSE_ಕೆಳಕ್ಕೆ:
            ಆದರೆ (ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ B_MOUSE_ಮೇಲೆ:
            ಆದರೆ (ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ B_MOUSE_WHEEL_ಬದಲಾಯಿತು:
            ದಶಮಾಂಶ x, y;
            ಆದರೆ (ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Float("be:wheel_delta_x", &x) == B_OK && ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Float("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((ಪೂರ್ಣಾಂಕ)x, (ಪೂರ್ಣಾಂಕ)y);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ B_ಕೀಲಿ_ಕೆಳಕ್ಕೆ:
        {
            int32 i = 0;
            int8 byte;
            int8 ಬೈಟುಗಳು[4] = { 0, 0, 0, 0 };
            ಆಗ (i < 4 && ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int8("byte", i, &byte) == B_OK) {
                ಬೈಟುಗಳು[i] = byte;
                i++;
            }
            ಆದರೆ (ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int32("key", &ಕೀಲಿ) == B_OK) {
                ಕೀಲಿ_Event_2((SDL_Scancode)ಕೀಲಿ, &ಬೈಟುಗಳು[0], i, true);
            }
        } ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ B_UNMAPPED_ಕೀಲಿ_ಕೆಳಕ್ಕೆ: // modifier keys are unmapped
            ಆದರೆ (ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int32("key", &ಕೀಲಿ) == B_OK) {
                ಕೀಲಿ_Event_2((SDL_Scancode)ಕೀಲಿ, ಖಾಲಿ, 0, true);
            }
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ B_ಕೀಲಿ_ಮೇಲೆ:
        ಸ್ಥಿತಿ B_UNMAPPED_ಕೀಲಿ_ಮೇಲೆ: // modifier keys are unmapped
            ಆದರೆ (ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int32("key", &ಕೀಲಿ) == B_OK) {
                ಕೀಲಿ_Event_2(ಕೀಲಿ, ಖಾಲಿ, 0, false);
            }
            ನಿಲ್ಲಿಸು;

        ಪೂರ್ವನಿಯೋಜಿತ:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            ನಿಲ್ಲಿಸು;
        }

        BWindow::Dispatch_ಸಂದೇಶ(ಸಂದೇಶ_2, ಗುರಿ);
    }

    // Handle command messages
    ಶೂನ್ಯ ಸಂದೇಶ_Received(BMessage *ಸಂದೇಶ)
    {
        ಆಯ್ಕೆ (ಸಂದೇಶ->what) {
        // Handle commands from SDL
        ಸ್ಥಿತಿ BWIN_ಗಣ_TITLE:
            ಗಣ_Title(ಸಂದೇಶ);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ BWIN_MOVE_ಕಿಟಕಿ:
            Move_ಗಮ್ಯ_2(ಸಂದೇಶ);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ BWIN_RESIZE_ಕಿಟಕಿ:
            Resize_ಗಮ್ಯ_2(ಸಂದೇಶ);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ BWIN_ಗಣ_BORDERED:
        {
            bool bEnabled;
            ಆದರೆ (ಸಂದೇಶ->ಕಂಡುಹಿಡಿ_Bool("window-border", &bEnabled) == B_OK)
                ಗಣ_Bordered(bEnabled);
            ನಿಲ್ಲಿಸು;
        }
        ಸ್ಥಿತಿ BWIN_ಗಣ_RESIZABLE:
        {
            bool bEnabled;
            ಆದರೆ (ಸಂದೇಶ->ಕಂಡುಹಿಡಿ_Bool("window-resizable", &bEnabled) == B_OK)
                ಗಣ_Resizable(bEnabled);
            ನಿಲ್ಲಿಸು;
        }
        ಸ್ಥಿತಿ BWIN_SHOW_ಕಿಟಕಿ:
            Show();
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ BWIN_HIDE_ಕಿಟಕಿ:
            Hide();
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ BWIN_MAXIMIZE_ಕಿಟಕಿ:
            BWindow::Zoom();
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ BWIN_MINIMIZE_ಕಿಟಕಿ:
            Minimize(true);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ BWIN_RESTORE_ಕಿಟಕಿ:
            _Restore();
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ BWIN_FULLSCREEN:
        {
            bool fullscreen;
            ಆದರೆ (ಸಂದೇಶ->ಕಂಡುಹಿಡಿ_Bool("fullscreen", &fullscreen) == B_OK)
                ಗಣ_ತುಂಬಿದ_Screen(fullscreen);
            ನಿಲ್ಲಿಸು;
        }
        ಸ್ಥಿತಿ BWIN_MINIMUM_ಗಾತ್ರ_ಕಿಟಕಿ:
            ಗಣ_Minimum_ಗಾತ್ರ(ಸಂದೇಶ);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pending_ಸಂದೇಶ;
            ಆಗ ((pending_ಸಂದೇಶ = ಸಂದೇಶ_ಸರತಿ()->ಕಂಡುಹಿಡಿ_ಸಂದೇಶ(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                ಸಂದೇಶ_ಸರತಿ()->Remove_ಸಂದೇಶ(pending_ಸಂದೇಶ);
                delete pending_ಸಂದೇಶ;
            }
            ಆದರೆ (_bitmap != ಖಾಲಿ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
                ಆದರೆ (_SDL_GLView != ಖಾಲಿ && _cur_view == _SDL_GLView) {
                    _SDL_GLView->Copy_Pixels_ಒಳ(_bitmap, B_ORIGIN);
                } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
                ಆದರೆ (_SDL_View != ಖಾಲಿ && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            ನಿಲ್ಲಿಸು;
        }
        ಪೂರ್ವನಿಯೋಜಿತ:
            // Perform normal message handling
            BWindow::ಸಂದೇಶ_Received(ಸಂದೇಶ);
            ನಿಲ್ಲಿಸು;
        }
    }

    // Accessor methods
    bool IsShown() { ಹಿಂತಿರುಗಿ _shown; }
    int32 GetID() { ಹಿಂತಿರುಗಿ _id; }
    BBitmap *GetBitmap() { ಹಿಂತಿರುಗಿ _bitmap; }
    BView *GetCurView() { ಹಿಂತಿರುಗಿ _cur_view; }
    SDL_BView *GetView() { ಹಿಂತಿರುಗಿ _SDL_View; }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        ಹಿಂತಿರುಗಿ _SDL_GLView;
    }
    Uint32 GetGLType() { ಹಿಂತಿರುಗಿ _gl_type; }
#ಆದರೆ_ಅಂತ್ಯ

    // Setter methods
    ಶೂನ್ಯ ಗಣ_ID(int32 id) { _id = id; }
    ಶೂನ್ಯ ಬೀಗ_ಬಫರ್() { ಬಫರ್_locker->ಬೀಗ(); }
    ಶೂನ್ಯ Unlock_ಬಫರ್() { ಬಫರ್_locker->Unlock(); }
    ಶೂನ್ಯ ಗಣ_Bitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        ಆದರೆ (_SDL_View != ಖಾಲಿ)
            _SDL_View->ಗಣ_Bitmap(bitmap);
    }

  ಖಾಸಗಿ:
    // Event redirection
    ಶೂನ್ಯ _MouseMotionEvent(BPoint &where, int32 transit)
    {
        ಆದರೆ (transit == B_EXITED_VIEW) {
            // Change mouse focus
            ಆದರೆ (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Change mouse focus
            ಆದರೆ (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage ಸಂದೇಶ_2(BAPP_MOUSE_MOVED);
            ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("x", (ಪೂರ್ಣಾಂಕ)where.x);
            ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("y", (ಪೂರ್ಣಾಂಕ)where.y);

            Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);
        }
    }

    ಶೂನ್ಯ _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage ಸಂದೇಶ_2(BAPP_MOUSE_FOCUS);
        ಸಂದೇಶ_2.ಕೂಡಿಸು_Bool("focusGained", focusGained);
        Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    ಶೂನ್ಯ _MouseButtonEvent(int32 buttons, bool ಕೆಳಕ್ಕೆ)
    {
        int32 buttonStateChange = buttons ^ ಕೊನೆಯ_buttons;

        ಆದರೆ (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ಎಡ, ಕೆಳಕ್ಕೆ);
        }
        ಆದರೆ (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ಬಲ, ಕೆಳಕ್ಕೆ);
        }
        ಆದರೆ (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ಮಧ್ಯ, ಕೆಳಕ್ಕೆ);
        }

        ಕೊನೆಯ_buttons = buttons;
    }

    ಶೂನ್ಯ _SendMouseButton(int32 button, bool ಕೆಳಕ್ಕೆ)
    {
        BMessage ಸಂದೇಶ_2(BAPP_MOUSE_BUTTON);
        ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("button-id", button);
        ಸಂದೇಶ_2.ಕೂಡಿಸು_Bool("button-down", ಕೆಳಕ್ಕೆ);
        Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);
    }

    ಶೂನ್ಯ _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage ಸಂದೇಶ_2(BAPP_MOUSE_WHEEL);
        ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("xticks", x);
        ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("yticks", y);
        Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);
    }

    ಶೂನ್ಯ ಕೀಲಿ_Event_2(int32 ಕೀಲಿ_ಸಂಕೇತ, ಸ್ಥಿರಾಂಕ int8 *ಕೀಲಿ_Utf8, ಸ್ಥಿರಾಂಕ ssize_t &len, bool ಕೆಳಕ್ಕೆ)
    {
        // Create a message to pass along to the BeApp thread
        BMessage ಸಂದೇಶ_2(BAPP_ಕೀಲಿ);
        ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("key-scancode", ಕೀಲಿ_ಸಂಕೇತ);
        ಆದರೆ (ಕೀಲಿ_Utf8 != ಖಾಲಿ) {
            ಸಂದೇಶ_2.ಕೂಡಿಸು_ದತ್ತಾಂಶ("key-utf8", B_INT8_TYPE, (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *)ಕೀಲಿ_Utf8, len);
        }
        ಸಂದೇಶ_2.ಕೂಡಿಸು_Bool("key-down", ಕೆಳಕ್ಕೆ);
        SDL_Looper->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
    }

    ಶೂನ್ಯ _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage ಸಂದೇಶ_2(BAPP_REPAINT);
        Post_ಕಿಟಕಿ_Event(ಸಂದೇಶ_2);
    }
    ಶೂನ್ಯ Post_ಕಿಟಕಿ_Event(BMessage &ಸಂದೇಶ_2)
    {
        ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("window-id", _id);
        SDL_Looper->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
    }

    // Command methods (functions called upon by SDL)
    ಶೂನ್ಯ ಗಣ_Title(BMessage *ಸಂದೇಶ_2)
    {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *title;
        ಆದರೆ (
            ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_String("window-title", &title) != B_OK) {
            ಹಿಂತಿರುಗಿ;
        }
        ಗಣ_Title_2(title);
    }

    ಶೂನ್ಯ Move_ಗಮ್ಯ_2(BMessage *ಸಂದೇಶ_2)
    {
        int32 x, y;
        ಆದರೆ (
            ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int32("window-x", &x) != B_OK ||
            ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int32("window-y", &y) != B_OK) {
            ಹಿಂತಿರುಗಿ;
        }
        ಆದರೆ (_fullscreen)
            non_fullscreen_ಚೌಕಟ್ಟು.ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ(x, y);
        ಇಲ್ಲದಿದ್ದರೆ
            Move_ಗಮ್ಯ(x, y);
    }

    ಶೂನ್ಯ Resize_ಗಮ್ಯ_2(BMessage *ಸಂದೇಶ_2)
    {
        int32 w, h;
        ಆದರೆ (
            ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int32("window-w", &w) != B_OK ||
            ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int32("window-h", &h) != B_OK) {
            ಹಿಂತಿರುಗಿ;
        }
        ಆದರೆ (_fullscreen) {
            non_fullscreen_ಚೌಕಟ್ಟು.ಬಲ = non_fullscreen_ಚೌಕಟ್ಟು.ಎಡ + w;
            non_fullscreen_ಚೌಕಟ್ಟು.bottom = non_fullscreen_ಚೌಕಟ್ಟು.ತುದಿ + h;
        } ಇಲ್ಲದಿದ್ದರೆ
            Resize_ಗಮ್ಯ(w, h);
    }

    ಶೂನ್ಯ ಗಣ_Bordered(bool bEnabled)
    {
        ಆದರೆ (_fullscreen)
            _bordered = bEnabled;
        ಇಲ್ಲದಿದ್ದರೆ
            ಗಣ_Look(bEnabled ? B_TITLED_ಕಿಟಕಿ_LOOK : B_NO_BORDER_ಕಿಟಕಿ_LOOK);
    }

    ಶೂನ್ಯ ಗಣ_Resizable(bool bEnabled)
    {
        ಆದರೆ (_fullscreen)
            _resizable = bEnabled;
        ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (bEnabled) {
                ಗಣ_Flags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಗಣ_Flags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    ಶೂನ್ಯ ಗಣ_Minimum_ಗಾತ್ರ(BMessage *ಸಂದೇಶ_2)
    {
        ದಶಮಾಂಶ max_ಎತ್ತರ;
        ದಶಮಾಂಶ max_ಅಗಲ;
        ದಶಮಾಂಶ _;
        int32 min_ಎತ್ತರ;
        int32 min_ಅಗಲ;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        Get_ಗಾತ್ರ_Limits(&_, &max_ಅಗಲ, &_, &max_ಎತ್ತರ);
        ಆದರೆ (ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int32("window-w", &min_ಅಗಲ) != B_OK)
            ಹಿಂತಿರುಗಿ;
        ಆದರೆ (ಸಂದೇಶ_2->ಕಂಡುಹಿಡಿ_Int32("window-h", &min_ಎತ್ತರ) != B_OK)
            ಹಿಂತಿರುಗಿ;
        ಗಣ_ಗಾತ್ರ_Limits((ದಶಮಾಂಶ)min_ಅಗಲ, max_ಅಗಲ, (ದಶಮಾಂಶ)min_ಎತ್ತರ, max_ಎತ್ತರ);
        Update_ಗಾತ್ರ_Limits();
    }

    ಶೂನ್ಯ _Restore()
    {
        ಆದರೆ (IsMinimized()) {
            Minimize(false);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (IsHidden()) {
            Show();
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_fullscreen) {

        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (prev_ಚೌಕಟ್ಟು != ಖಾಲಿ) { // Zoomed
            Move_ಗಮ್ಯ(prev_ಚೌಕಟ್ಟು->ಎಡ, prev_ಚೌಕಟ್ಟು->ತುದಿ);
            Resize_ಗಮ್ಯ(prev_ಚೌಕಟ್ಟು->ಅಗಲ_2(), prev_ಚೌಕಟ್ಟು->ಎತ್ತರ_2());
        }
    }

    ಶೂನ್ಯ ಗಣ_ತುಂಬಿದ_Screen(bool fullscreen)
    {
        ಆದರೆ (fullscreen != _fullscreen) {
            ಆದರೆ (fullscreen) {
                BScreen screen(this);
                BRect screen_ಚೌಕಟ್ಟು = screen.ಚೌಕಟ್ಟು_2();
                _bordered = Look() != B_NO_BORDER_ಕಿಟಕಿ_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                non_fullscreen_ಚೌಕಟ್ಟು = ಚೌಕಟ್ಟು_2();
                ಗಣ_Bordered(false);
                ಗಣ_Resizable(false);
                Move_ಗಮ್ಯ(screen_ಚೌಕಟ್ಟು.ಎಡ, screen_ಚೌಕಟ್ಟು.ತುದಿ);
                Resize_ಗಮ್ಯ(screen_ಚೌಕಟ್ಟು.ಅಗಲ_2(), screen_ಚೌಕಟ್ಟು.ಎತ್ತರ_2());
                _fullscreen = fullscreen;
            } ಇಲ್ಲದಿದ್ದರೆ {
                _fullscreen = fullscreen;
                Move_ಗಮ್ಯ(non_fullscreen_ಚೌಕಟ್ಟು.ಎಡ, non_fullscreen_ಚೌಕಟ್ಟು.ತುದಿ);
                Resize_ಗಮ್ಯ(non_fullscreen_ಚೌಕಟ್ಟು.ಅಗಲ_2(), non_fullscreen_ಚೌಕಟ್ಟು.ಎತ್ತರ_2());
                ಗಣ_Bordered(_bordered);
                ಗಣ_Resizable(_resizable);
            }
        }
    }

    // Members

    BView *_cur_view;
    SDL_BView *_SDL_View;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
    BGLView *_SDL_GLView;
    Uint32 _gl_type;
#ಆದರೆ_ಅಂತ್ಯ

    int32 ಕೊನೆಯ_buttons;
    int32 _id;           // Window id used by SDL_BApp
    bool _mouse_focused; // Does this window have mouse focus?
    bool _shown;
    bool _inhibit_resize;

    BRect *prev_ಚೌಕಟ್ಟು; // Previous position and size of the window
    bool _fullscreen;
    // valid only if fullscreen
    BRect non_fullscreen_ಚೌಕಟ್ಟು;
    bool _bordered;
    bool _resizable;

    // Framebuffer members
    BLocker *ಬಫರ್_locker;
    BBitmap *_bitmap;
};

/* FIXME:
 * An explanation of framebuffer flags.
 *
 * _connected -           Original variable used to let the drawing thread know
 *                         when changes are being made to the other framebuffer
 *                         members.
 * _connection_disabled - Used to signal to the drawing thread that the window
 *                         is closing, and the thread should exit.
 * _buffer_created -      True if the current buffer is valid
 * _buffer_dirty -        True if the window should be redrawn.
 * _trash_window_buffer - True if the window buffer needs to be trashed partway
 *                         through a draw cycle.  Occurs when the previous
 *                         buffer provided by DirectConnected() is invalidated.
 */
#ಆದರೆ_ಅಂತ್ಯ // SDL_BWin_h_
