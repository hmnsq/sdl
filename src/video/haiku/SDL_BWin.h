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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_BWin_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_BWin_h_

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bframebuffer.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <AppKit.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <Cursor.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <InterfaceKit.h>
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
#ਅਨ੍ਤਰ੍ਭਾਵ <opengl/GLView.h>
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/haiku/SDL_BApp.h"

ਗਿਣਤੀ WinCommands
{
    BWIN_MOVE_ਖਿੜਕੀ,
    BWIN_RESIZE_ਖਿੜਕੀ,
    BWIN_SHOW_ਖਿੜਕੀ,
    BWIN_HIDE_ਖਿੜਕੀ,
    BWIN_MAXIMIZE_ਖਿੜਕੀ,
    BWIN_MINIMIZE_ਖਿੜਕੀ,
    BWIN_RESTORE_ਖਿੜਕੀ,
    BWIN_ਸੈੱਟ_TITLE,
    BWIN_ਸੈੱਟ_BORDERED,
    BWIN_ਸੈੱਟ_RESIZABLE,
    BWIN_FULLSCREEN,
    BWIN_UPDATE_FRAMEBUFFER,
    BWIN_MINIMUM_ਮਾਪ_ਖਿੜਕੀ
};

// non-OpenGL framebuffer view
class SDL_BView : ਜਨਤਕ BView
{
  ਜਨਤਕ:
    SDL_BView(BRect ਚੌਖਟਾ, ਅਚਲ ਅੱਖਰ *name, uint32 resizing_ਬਹੁਲਕ)
        : BView(ਚੌਖਟਾ, name, resizing_ਬਹੁਲਕ, B_WILL_DRAW),
          fBitmap(ਨਿਰਾ)
    {
    }

    ਖਾਲੀ Draw(BRect dirty)
    {
        ਜੇ (fBitmap != ਨਿਰਾ)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    ਖਾਲੀ ਸੈੱਟ_Bitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  ਨਿਜੀ:
    BBitmap *fBitmap;
};

class SDL_BWin : ਜਨਤਕ BWindow
{
  ਜਨਤਕ:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, ਖਿੜਕੀ_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_ਸਾਧਾਰਨ_ਖਿੜਕੀ_FEEL, flags)
    {
        ਆਖਰੀ_buttons = 0;

        _cur_view = ਨਿਰਾ;
        _SDL_View = ਨਿਰਾ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
        _SDL_GLView = ਨਿਰਾ;
        _gl_type = 0;
#ਜੇ_ਅੰਤ
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        prev_ਚੌਖਟਾ = ਨਿਰਾ;
        _fullscreen = ਨਿਰਾ;

        // Handle framebuffer stuff
        ਬਫਰ_locker = new BLocker();
        _bitmap = ਨਿਰਾ;
    }

    ਆਭਾਸੀ ~SDL_BWin()
    {
        ਤਾਲਾ();

        ਜੇ (_SDL_View != ਨਿਰਾ && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = ਨਿਰਾ;
        }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
        ਜੇ (_SDL_GLView) {
            ਜੇ (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->ਸੈੱਟ_Current_Context(ਨਿਰਾ);
            ਜੇ (_SDL_GLView == _cur_view)
                Remove_ਬੱਚਾ(_SDL_GLView);
            _SDL_GLView = ਨਿਰਾ;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#ਜੇ_ਅੰਤ
        Unlock();

        delete prev_ਚੌਖਟਾ;

        // Clean up framebuffer stuff
        ਬਫਰ_locker->ਤਾਲਾ();
        delete ਬਫਰ_locker;
    }

    ਖਾਲੀ ਸੈੱਟ_Current_View(BView *view)
    {
        ਜੇ (_cur_view != view) {
            ਜੇ (_cur_view != ਨਿਰਾ)
                Remove_ਬੱਚਾ(_cur_view);
            _cur_view = view;
            ਜੇ (_cur_view != ਨਿਰਾ)
                ਜੋੜੋ_ਬੱਚਾ(_cur_view);
        }
    }

    ਖਾਲੀ UpdateCurrentView()
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
        ਜੇ (_SDL_GLView != ਨਿਰਾ) {
            ਸੈੱਟ_Current_View(_SDL_GLView);
        } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        ਜੇ (_SDL_View != ਨਿਰਾ) {
            ਸੈੱਟ_Current_View(_SDL_View);
        } ਨਹੀਂਤਾਂ {
            ਸੈੱਟ_Current_View(ਨਿਰਾ);
        }
    }

    SDL_BView *CreateView()
    {
        ਤਾਲਾ();
        ਜੇ (_SDL_View == ਨਿਰਾ) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        ਵਾਪਸ _SDL_View;
    }

    ਖਾਲੀ RemoveView()
    {
        ਤਾਲਾ();
        ਜੇ (_SDL_View != ਨਿਰਾ) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = ਨਿਰਾ;
            UpdateCurrentView();
            delete oldView;
        }
        Unlock();
    }

    /* * * * * OpenGL functionality * * * * */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
    BGLView *CreateGLView(Uint32 gl_flags)
    {
        ਤਾਲਾ();
        ਜੇ (_SDL_GLView == ਨਿਰਾ) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_ਚੌਖਟਾ_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        ਵਾਪਸ _SDL_GLView;
    }

    ਖਾਲੀ RemoveGLView()
    {
        ਤਾਲਾ();
        ਜੇ (_SDL_GLView != ਨਿਰਾ) {
            ਜੇ (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->ਸੈੱਟ_Current_Context(ਨਿਰਾ);
            _SDL_GLView = ਨਿਰਾ;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    ਖਾਲੀ ਅਦਲਾ_ਬਦਲੀ_Buffers(ਖਾਲੀ)
    {
        _SDL_GLView->ਅਦਲਾ_ਬਦਲੀ_Buffers();
    }
#ਜੇ_ਅੰਤ

    /* * * * * Event sending * * * * */
    // Hook functions
    ਆਭਾਸੀ ਖਾਲੀ ਚੌਖਟਾ_Moved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage ਸੁਨੇਹਾ_2(BAPP_ਖਿੜਕੀ_MOVED);
        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("window-x", (ਪੂਰਨ)origin.x);
        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("window-y", (ਪੂਰਨ)origin.y);
        Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);

        // Perform normal hook operations
        BWindow::ਚੌਖਟਾ_Moved(origin);
    }

    ਖਾਲੀ ਚੌਖਟਾ_Resized(ਦਸ਼ਮਲਵ ਚੌੜਾਈ, ਦਸ਼ਮਲਵ ਉਚਾਈ)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage ਸੁਨੇਹਾ_2(BAPP_ਖਿੜਕੀ_RESIZED);

        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("window-w", (ਪੂਰਨ)ਚੌੜਾਈ + 1);
        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("window-h", (ਪੂਰਨ)ਉਚਾਈ + 1);
        Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);

        // Perform normal hook operations
        BWindow::ਚੌਖਟਾ_Resized(ਚੌੜਾਈ, ਉਚਾਈ);
    }

    bool QuitRequested()
    {
        BMessage ਸੁਨੇਹਾ_2(BAPP_ਖਿੜਕੀ_CLOSE_REQUESTED);
        Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);

        // We won't allow a quit unless asked by DestroyWindow()
        ਵਾਪਸ false;
    }

    ਖਾਲੀ ਖਿੜਕੀ_Activated(bool ਸਰਗਰਮ)
    {
        BMessage ਸੁਨੇਹਾ_2(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Bool("focusGained", ਸਰਗਰਮ);
        Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);
    }

    ਖਾਲੀ Zoom(BPoint origin,
              ਦਸ਼ਮਲਵ ਚੌੜਾਈ,
              ਦਸ਼ਮਲਵ ਉਚਾਈ)
    {
        BMessage ਸੁਨੇਹਾ_2(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);

        // Before the window zooms, record its size
        ਜੇ (!prev_ਚੌਖਟਾ)
            prev_ਚੌਖਟਾ = new BRect(ਚੌਖਟਾ_2());

        // Perform normal hook operations
        BWindow::Zoom(origin, ਚੌੜਾਈ, ਉਚਾਈ);
    }

    // Member functions
    ਖਾਲੀ Show()
    {
        ਜਦੋਂ (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage ਸੁਨੇਹਾ_2(BAPP_SHOW);
        Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);
    }

    ਖਾਲੀ Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage ਸੁਨੇਹਾ_2(BAPP_HIDE);
        Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);
    }

    ਖਾਲੀ Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage ਸੁਨੇਹਾ_2(minState);
        Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);
    }

    ਖਾਲੀ Screen_ਬਦਲਿਆ(BRect screen_ਚੌਖਟਾ, color_space ਡੂੰਘਾਈ_2)
    {
        ਜੇ (_fullscreen) {
            Move_ਮੰਜ਼ਿਲ(screen_ਚੌਖਟਾ.ਖੱਬਾ, screen_ਚੌਖਟਾ.ਸਿਖਰ);
            Resize_ਮੰਜ਼ਿਲ(screen_ਚੌਖਟਾ.ਚੌੜਾਈ_2(), screen_ਚੌਖਟਾ.ਉਚਾਈ_2());
        }
    }

    // BView message interruption
    ਖਾਲੀ Dispatch_ਸੁਨੇਹਾ(BMessage *ਸੁਨੇਹਾ_2, BHandler *ਨਿਸ਼ਾਨਾ)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 ਕੁੰਜੀ;     // Used for key events

        ਚੋਣ (ਸੁਨੇਹਾ_2->what) {
        ਹਾਲਤ B_MOUSE_MOVED:
            int32 transit;
            ਜੇ (ਸੁਨੇਹਾ_2->ਲੱਭੋ_ਬਿੰਦੂ("where", &where) == B_OK && ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            ਰੋਕੋ;

        ਹਾਲਤ B_MOUSE_ਥੱਲੇ:
            ਜੇ (ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            ਰੋਕੋ;

        ਹਾਲਤ B_MOUSE_ਉੱਪਰ:
            ਜੇ (ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            ਰੋਕੋ;

        ਹਾਲਤ B_MOUSE_WHEEL_ਬਦਲਿਆ:
            ਦਸ਼ਮਲਵ x, y;
            ਜੇ (ਸੁਨੇਹਾ_2->ਲੱਭੋ_Float("be:wheel_delta_x", &x) == B_OK && ਸੁਨੇਹਾ_2->ਲੱਭੋ_Float("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((ਪੂਰਨ)x, (ਪੂਰਨ)y);
            }
            ਰੋਕੋ;

        ਹਾਲਤ B_ਕੁੰਜੀ_ਥੱਲੇ:
        {
            int32 i = 0;
            int8 byte;
            int8 ਬਾਈਟਾਂ[4] = { 0, 0, 0, 0 };
            ਜਦੋਂ (i < 4 && ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int8("byte", i, &byte) == B_OK) {
                ਬਾਈਟਾਂ[i] = byte;
                i++;
            }
            ਜੇ (ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int32("key", &ਕੁੰਜੀ) == B_OK) {
                ਕੁੰਜੀ_Event_2((SDL_Scancode)ਕੁੰਜੀ, &ਬਾਈਟਾਂ[0], i, true);
            }
        } ਰੋਕੋ;

        ਹਾਲਤ B_UNMAPPED_ਕੁੰਜੀ_ਥੱਲੇ: // modifier keys are unmapped
            ਜੇ (ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int32("key", &ਕੁੰਜੀ) == B_OK) {
                ਕੁੰਜੀ_Event_2((SDL_Scancode)ਕੁੰਜੀ, ਨਿਰਾ, 0, true);
            }
            ਰੋਕੋ;

        ਹਾਲਤ B_ਕੁੰਜੀ_ਉੱਪਰ:
        ਹਾਲਤ B_UNMAPPED_ਕੁੰਜੀ_ਉੱਪਰ: // modifier keys are unmapped
            ਜੇ (ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int32("key", &ਕੁੰਜੀ) == B_OK) {
                ਕੁੰਜੀ_Event_2(ਕੁੰਜੀ, ਨਿਰਾ, 0, false);
            }
            ਰੋਕੋ;

        ਮੂਲ:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            ਰੋਕੋ;
        }

        BWindow::Dispatch_ਸੁਨੇਹਾ(ਸੁਨੇਹਾ_2, ਨਿਸ਼ਾਨਾ);
    }

    // Handle command messages
    ਖਾਲੀ ਸੁਨੇਹਾ_Received(BMessage *ਸੁਨੇਹਾ)
    {
        ਚੋਣ (ਸੁਨੇਹਾ->what) {
        // Handle commands from SDL
        ਹਾਲਤ BWIN_ਸੈੱਟ_TITLE:
            ਸੈੱਟ_Title(ਸੁਨੇਹਾ);
            ਰੋਕੋ;
        ਹਾਲਤ BWIN_MOVE_ਖਿੜਕੀ:
            Move_ਮੰਜ਼ਿਲ_2(ਸੁਨੇਹਾ);
            ਰੋਕੋ;
        ਹਾਲਤ BWIN_RESIZE_ਖਿੜਕੀ:
            Resize_ਮੰਜ਼ਿਲ_2(ਸੁਨੇਹਾ);
            ਰੋਕੋ;
        ਹਾਲਤ BWIN_ਸੈੱਟ_BORDERED:
        {
            bool bEnabled;
            ਜੇ (ਸੁਨੇਹਾ->ਲੱਭੋ_Bool("window-border", &bEnabled) == B_OK)
                ਸੈੱਟ_Bordered(bEnabled);
            ਰੋਕੋ;
        }
        ਹਾਲਤ BWIN_ਸੈੱਟ_RESIZABLE:
        {
            bool bEnabled;
            ਜੇ (ਸੁਨੇਹਾ->ਲੱਭੋ_Bool("window-resizable", &bEnabled) == B_OK)
                ਸੈੱਟ_Resizable(bEnabled);
            ਰੋਕੋ;
        }
        ਹਾਲਤ BWIN_SHOW_ਖਿੜਕੀ:
            Show();
            ਰੋਕੋ;
        ਹਾਲਤ BWIN_HIDE_ਖਿੜਕੀ:
            Hide();
            ਰੋਕੋ;
        ਹਾਲਤ BWIN_MAXIMIZE_ਖਿੜਕੀ:
            BWindow::Zoom();
            ਰੋਕੋ;
        ਹਾਲਤ BWIN_MINIMIZE_ਖਿੜਕੀ:
            Minimize(true);
            ਰੋਕੋ;
        ਹਾਲਤ BWIN_RESTORE_ਖਿੜਕੀ:
            _Restore();
            ਰੋਕੋ;
        ਹਾਲਤ BWIN_FULLSCREEN:
        {
            bool fullscreen;
            ਜੇ (ਸੁਨੇਹਾ->ਲੱਭੋ_Bool("fullscreen", &fullscreen) == B_OK)
                ਸੈੱਟ_ਭਰਿਆ_Screen(fullscreen);
            ਰੋਕੋ;
        }
        ਹਾਲਤ BWIN_MINIMUM_ਮਾਪ_ਖਿੜਕੀ:
            ਸੈੱਟ_Minimum_ਮਾਪ(ਸੁਨੇਹਾ);
            ਰੋਕੋ;
        ਹਾਲਤ BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pending_ਸੁਨੇਹਾ;
            ਜਦੋਂ ((pending_ਸੁਨੇਹਾ = ਸੁਨੇਹਾ_ਕਤਾਰ()->ਲੱਭੋ_ਸੁਨੇਹਾ(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                ਸੁਨੇਹਾ_ਕਤਾਰ()->Remove_ਸੁਨੇਹਾ(pending_ਸੁਨੇਹਾ);
                delete pending_ਸੁਨੇਹਾ;
            }
            ਜੇ (_bitmap != ਨਿਰਾ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
                ਜੇ (_SDL_GLView != ਨਿਰਾ && _cur_view == _SDL_GLView) {
                    _SDL_GLView->Copy_Pixels_ਵਿੱਚ(_bitmap, B_ORIGIN);
                } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
                ਜੇ (_SDL_View != ਨਿਰਾ && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            ਰੋਕੋ;
        }
        ਮੂਲ:
            // Perform normal message handling
            BWindow::ਸੁਨੇਹਾ_Received(ਸੁਨੇਹਾ);
            ਰੋਕੋ;
        }
    }

    // Accessor methods
    bool IsShown() { ਵਾਪਸ _shown; }
    int32 GetID() { ਵਾਪਸ _id; }
    BBitmap *GetBitmap() { ਵਾਪਸ _bitmap; }
    BView *GetCurView() { ਵਾਪਸ _cur_view; }
    SDL_BView *GetView() { ਵਾਪਸ _SDL_View; }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        ਵਾਪਸ _SDL_GLView;
    }
    Uint32 GetGLType() { ਵਾਪਸ _gl_type; }
#ਜੇ_ਅੰਤ

    // Setter methods
    ਖਾਲੀ ਸੈੱਟ_ID(int32 id) { _id = id; }
    ਖਾਲੀ ਤਾਲਾ_ਬਫਰ() { ਬਫਰ_locker->ਤਾਲਾ(); }
    ਖਾਲੀ Unlock_ਬਫਰ() { ਬਫਰ_locker->Unlock(); }
    ਖਾਲੀ ਸੈੱਟ_Bitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        ਜੇ (_SDL_View != ਨਿਰਾ)
            _SDL_View->ਸੈੱਟ_Bitmap(bitmap);
    }

  ਨਿਜੀ:
    // Event redirection
    ਖਾਲੀ _MouseMotionEvent(BPoint &where, int32 transit)
    {
        ਜੇ (transit == B_EXITED_VIEW) {
            // Change mouse focus
            ਜੇ (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } ਨਹੀਂਤਾਂ {
            // Change mouse focus
            ਜੇ (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage ਸੁਨੇਹਾ_2(BAPP_MOUSE_MOVED);
            ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("x", (ਪੂਰਨ)where.x);
            ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("y", (ਪੂਰਨ)where.y);

            Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);
        }
    }

    ਖਾਲੀ _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage ਸੁਨੇਹਾ_2(BAPP_MOUSE_FOCUS);
        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Bool("focusGained", focusGained);
        Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    ਖਾਲੀ _MouseButtonEvent(int32 buttons, bool ਥੱਲੇ)
    {
        int32 buttonStateChange = buttons ^ ਆਖਰੀ_buttons;

        ਜੇ (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ਖੱਬਾ, ਥੱਲੇ);
        }
        ਜੇ (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ਸੱਜਾ, ਥੱਲੇ);
        }
        ਜੇ (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ਵਿਚਕਾਰ, ਥੱਲੇ);
        }

        ਆਖਰੀ_buttons = buttons;
    }

    ਖਾਲੀ _SendMouseButton(int32 button, bool ਥੱਲੇ)
    {
        BMessage ਸੁਨੇਹਾ_2(BAPP_MOUSE_BUTTON);
        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("button-id", button);
        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Bool("button-down", ਥੱਲੇ);
        Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);
    }

    ਖਾਲੀ _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage ਸੁਨੇਹਾ_2(BAPP_MOUSE_WHEEL);
        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("xticks", x);
        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("yticks", y);
        Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);
    }

    ਖਾਲੀ ਕੁੰਜੀ_Event_2(int32 ਕੁੰਜੀ_ਕੋਡ, ਅਚਲ int8 *ਕੁੰਜੀ_Utf8, ਅਚਲ ssize_t &len, bool ਥੱਲੇ)
    {
        // Create a message to pass along to the BeApp thread
        BMessage ਸੁਨੇਹਾ_2(BAPP_ਕੁੰਜੀ);
        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("key-scancode", ਕੁੰਜੀ_ਕੋਡ);
        ਜੇ (ਕੁੰਜੀ_Utf8 != ਨਿਰਾ) {
            ਸੁਨੇਹਾ_2.ਜੋੜੋ_ਅੰਕੜੇ("key-utf8", B_INT8_TYPE, (ਅਚਲ ਖਾਲੀ *)ਕੁੰਜੀ_Utf8, len);
        }
        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Bool("key-down", ਥੱਲੇ);
        SDL_Looper->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
    }

    ਖਾਲੀ _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage ਸੁਨੇਹਾ_2(BAPP_REPAINT);
        Post_ਖਿੜਕੀ_Event(ਸੁਨੇਹਾ_2);
    }
    ਖਾਲੀ Post_ਖਿੜਕੀ_Event(BMessage &ਸੁਨੇਹਾ_2)
    {
        ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("window-id", _id);
        SDL_Looper->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
    }

    // Command methods (functions called upon by SDL)
    ਖਾਲੀ ਸੈੱਟ_Title(BMessage *ਸੁਨੇਹਾ_2)
    {
        ਅਚਲ ਅੱਖਰ *title;
        ਜੇ (
            ਸੁਨੇਹਾ_2->ਲੱਭੋ_String("window-title", &title) != B_OK) {
            ਵਾਪਸ;
        }
        ਸੈੱਟ_Title_2(title);
    }

    ਖਾਲੀ Move_ਮੰਜ਼ਿਲ_2(BMessage *ਸੁਨੇਹਾ_2)
    {
        int32 x, y;
        ਜੇ (
            ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int32("window-x", &x) != B_OK ||
            ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int32("window-y", &y) != B_OK) {
            ਵਾਪਸ;
        }
        ਜੇ (_fullscreen)
            non_fullscreen_ਚੌਖਟਾ.ਵਿੱਥ_ਮੰਜ਼ਿਲ(x, y);
        ਨਹੀਂਤਾਂ
            Move_ਮੰਜ਼ਿਲ(x, y);
    }

    ਖਾਲੀ Resize_ਮੰਜ਼ਿਲ_2(BMessage *ਸੁਨੇਹਾ_2)
    {
        int32 w, h;
        ਜੇ (
            ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int32("window-w", &w) != B_OK ||
            ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int32("window-h", &h) != B_OK) {
            ਵਾਪਸ;
        }
        ਜੇ (_fullscreen) {
            non_fullscreen_ਚੌਖਟਾ.ਸੱਜਾ = non_fullscreen_ਚੌਖਟਾ.ਖੱਬਾ + w;
            non_fullscreen_ਚੌਖਟਾ.bottom = non_fullscreen_ਚੌਖਟਾ.ਸਿਖਰ + h;
        } ਨਹੀਂਤਾਂ
            Resize_ਮੰਜ਼ਿਲ(w, h);
    }

    ਖਾਲੀ ਸੈੱਟ_Bordered(bool bEnabled)
    {
        ਜੇ (_fullscreen)
            _bordered = bEnabled;
        ਨਹੀਂਤਾਂ
            ਸੈੱਟ_Look(bEnabled ? B_TITLED_ਖਿੜਕੀ_LOOK : B_NO_BORDER_ਖਿੜਕੀ_LOOK);
    }

    ਖਾਲੀ ਸੈੱਟ_Resizable(bool bEnabled)
    {
        ਜੇ (_fullscreen)
            _resizable = bEnabled;
        ਨਹੀਂਤਾਂ {
            ਜੇ (bEnabled) {
                ਸੈੱਟ_Flags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } ਨਹੀਂਤਾਂ {
                ਸੈੱਟ_Flags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    ਖਾਲੀ ਸੈੱਟ_Minimum_ਮਾਪ(BMessage *ਸੁਨੇਹਾ_2)
    {
        ਦਸ਼ਮਲਵ max_ਉਚਾਈ;
        ਦਸ਼ਮਲਵ max_ਚੌੜਾਈ;
        ਦਸ਼ਮਲਵ _;
        int32 min_ਉਚਾਈ;
        int32 min_ਚੌੜਾਈ;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        Get_ਮਾਪ_Limits(&_, &max_ਚੌੜਾਈ, &_, &max_ਉਚਾਈ);
        ਜੇ (ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int32("window-w", &min_ਚੌੜਾਈ) != B_OK)
            ਵਾਪਸ;
        ਜੇ (ਸੁਨੇਹਾ_2->ਲੱਭੋ_Int32("window-h", &min_ਉਚਾਈ) != B_OK)
            ਵਾਪਸ;
        ਸੈੱਟ_ਮਾਪ_Limits((ਦਸ਼ਮਲਵ)min_ਚੌੜਾਈ, max_ਚੌੜਾਈ, (ਦਸ਼ਮਲਵ)min_ਉਚਾਈ, max_ਉਚਾਈ);
        Update_ਮਾਪ_Limits();
    }

    ਖਾਲੀ _Restore()
    {
        ਜੇ (IsMinimized()) {
            Minimize(false);
        } ਨਹੀਂਤਾਂ ਜੇ (IsHidden()) {
            Show();
        } ਨਹੀਂਤਾਂ ਜੇ (_fullscreen) {

        } ਨਹੀਂਤਾਂ ਜੇ (prev_ਚੌਖਟਾ != ਨਿਰਾ) { // Zoomed
            Move_ਮੰਜ਼ਿਲ(prev_ਚੌਖਟਾ->ਖੱਬਾ, prev_ਚੌਖਟਾ->ਸਿਖਰ);
            Resize_ਮੰਜ਼ਿਲ(prev_ਚੌਖਟਾ->ਚੌੜਾਈ_2(), prev_ਚੌਖਟਾ->ਉਚਾਈ_2());
        }
    }

    ਖਾਲੀ ਸੈੱਟ_ਭਰਿਆ_Screen(bool fullscreen)
    {
        ਜੇ (fullscreen != _fullscreen) {
            ਜੇ (fullscreen) {
                BScreen screen(this);
                BRect screen_ਚੌਖਟਾ = screen.ਚੌਖਟਾ_2();
                _bordered = Look() != B_NO_BORDER_ਖਿੜਕੀ_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                non_fullscreen_ਚੌਖਟਾ = ਚੌਖਟਾ_2();
                ਸੈੱਟ_Bordered(false);
                ਸੈੱਟ_Resizable(false);
                Move_ਮੰਜ਼ਿਲ(screen_ਚੌਖਟਾ.ਖੱਬਾ, screen_ਚੌਖਟਾ.ਸਿਖਰ);
                Resize_ਮੰਜ਼ਿਲ(screen_ਚੌਖਟਾ.ਚੌੜਾਈ_2(), screen_ਚੌਖਟਾ.ਉਚਾਈ_2());
                _fullscreen = fullscreen;
            } ਨਹੀਂਤਾਂ {
                _fullscreen = fullscreen;
                Move_ਮੰਜ਼ਿਲ(non_fullscreen_ਚੌਖਟਾ.ਖੱਬਾ, non_fullscreen_ਚੌਖਟਾ.ਸਿਖਰ);
                Resize_ਮੰਜ਼ਿਲ(non_fullscreen_ਚੌਖਟਾ.ਚੌੜਾਈ_2(), non_fullscreen_ਚੌਖਟਾ.ਉਚਾਈ_2());
                ਸੈੱਟ_Bordered(_bordered);
                ਸੈੱਟ_Resizable(_resizable);
            }
        }
    }

    // Members

    BView *_cur_view;
    SDL_BView *_SDL_View;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
    BGLView *_SDL_GLView;
    Uint32 _gl_type;
#ਜੇ_ਅੰਤ

    int32 ਆਖਰੀ_buttons;
    int32 _id;           // Window id used by SDL_BApp
    bool _mouse_focused; // Does this window have mouse focus?
    bool _shown;
    bool _inhibit_resize;

    BRect *prev_ਚੌਖਟਾ; // Previous position and size of the window
    bool _fullscreen;
    // valid only if fullscreen
    BRect non_fullscreen_ਚੌਖਟਾ;
    bool _bordered;
    bool _resizable;

    // Framebuffer members
    BLocker *ਬਫਰ_locker;
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
#ਜੇ_ਅੰਤ // SDL_BWin_h_
