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

#ifndef SDL_BWin_h_
#define SDL_BWin_h_

#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
#endif

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"
#ಅನ್ತರ್ಭಾವ "SDL_bframebuffer.h"

#ifdef __cplusplus
}
#endif

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <AppKit.h>
#ಅನ್ತರ್ಭಾವ <Cursor.h>
#ಅನ್ತರ್ಭಾವ <InterfaceKit.h>
#ifdef SDL_VIDEO_OPENGL
#ಅನ್ತರ್ಭಾವ <opengl/GLView.h>
#endif
#ಅನ್ತರ್ಭಾವ "../../core/haiku/SDL_BApp.h"

ಗಣನಾ WinCommands
{
    BWIN_MOVE_WINDOW,
    BWIN_RESIZE_WINDOW,
    BWIN_SHOW_WINDOW,
    BWIN_HIDE_WINDOW,
    BWIN_MAXIMIZE_WINDOW,
    BWIN_MINIMIZE_WINDOW,
    BWIN_RESTORE_WINDOW,
    BWIN_SET_TITLE,
    BWIN_SET_BORDERED,
    BWIN_SET_RESIZABLE,
    BWIN_FULLSCREEN,
    BWIN_UPDATE_FRAMEBUFFER,
    BWIN_MINIMUM_SIZE_WINDOW
};

// non-OpenGL framebuffer view
class SDL_BView : ಸಾರ್ವಜನಿಕ BView
{
  ಸಾರ್ವಜನಿಕ:
    SDL_BView(BRect frame, ಧ್ರುವ ವರ್ಣ *name, uint32 resizingMode)
        : BView(frame, name, resizingMode, B_WILL_DRAW),
          fBitmap(ರಿಕ್ತ)
    {
    }

    ಶೂನ್ಯ Draw(BRect dirty)
    {
        ಯದಿ (fBitmap != ರಿಕ್ತ)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    ಶೂನ್ಯ SetBitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  ಗುಪ್ತ:
    BBitmap *fBitmap;
};

class SDL_BWin : ಸಾರ್ವಜನಿಕ BWindow
{
  ಸಾರ್ವಜನಿಕ:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, window_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_NORMAL_WINDOW_FEEL, flags)
    {
        _last_buttons = 0;

        _cur_view = ರಿಕ್ತ;
        _SDL_View = ರಿಕ್ತ;

#ifdef SDL_VIDEO_OPENGL
        _SDL_GLView = ರಿಕ್ತ;
        _gl_type = 0;
#endif
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        _prev_frame = ರಿಕ್ತ;
        _fullscreen = ರಿಕ್ತ;

        // Handle framebuffer stuff
        _buffer_locker = new BLocker();
        _bitmap = ರಿಕ್ತ;
    }

    ಆಭಾಸ ~SDL_BWin()
    {
        Lock();

        ಯದಿ (_SDL_View != ರಿಕ್ತ && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = ರಿಕ್ತ;
        }

#ifdef SDL_VIDEO_OPENGL
        ಯದಿ (_SDL_GLView) {
            ಯದಿ (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(ರಿಕ್ತ);
            ಯದಿ (_SDL_GLView == _cur_view)
                RemoveChild(_SDL_GLView);
            _SDL_GLView = ರಿಕ್ತ;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#endif
        Unlock();

        delete _prev_frame;

        // Clean up framebuffer stuff
        _buffer_locker->Lock();
        delete _buffer_locker;
    }

    ಶೂನ್ಯ SetCurrentView(BView *view)
    {
        ಯದಿ (_cur_view != view) {
            ಯದಿ (_cur_view != ರಿಕ್ತ)
                RemoveChild(_cur_view);
            _cur_view = view;
            ಯದಿ (_cur_view != ರಿಕ್ತ)
                AddChild(_cur_view);
        }
    }

    ಶೂನ್ಯ UpdateCurrentView()
    {
#ifdef SDL_VIDEO_OPENGL
        ಯದಿ (_SDL_GLView != ರಿಕ್ತ) {
            SetCurrentView(_SDL_GLView);
        } ಅನ್ಯಥಾ
#endif
        ಯದಿ (_SDL_View != ರಿಕ್ತ) {
            SetCurrentView(_SDL_View);
        } ಅನ್ಯಥಾ {
            SetCurrentView(ರಿಕ್ತ);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        ಯದಿ (_SDL_View == ರಿಕ್ತ) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        ಪ್ರತ್ಯಾಗಮ _SDL_View;
    }

    ಶೂನ್ಯ RemoveView()
    {
        Lock();
        ಯದಿ (_SDL_View != ರಿಕ್ತ) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = ರಿಕ್ತ;
            UpdateCurrentView();
            delete oldView;
        }
        Unlock();
    }

    /* * * * * OpenGL functionality * * * * */
#ifdef SDL_VIDEO_OPENGL
    BGLView *CreateGLView(Uint32 gl_flags)
    {
        Lock();
        ಯದಿ (_SDL_GLView == ರಿಕ್ತ) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        ಪ್ರತ್ಯಾಗಮ _SDL_GLView;
    }

    ಶೂನ್ಯ RemoveGLView()
    {
        Lock();
        ಯದಿ (_SDL_GLView != ರಿಕ್ತ) {
            ಯದಿ (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(ರಿಕ್ತ);
            _SDL_GLView = ರಿಕ್ತ;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    ಶೂನ್ಯ SwapBuffers(ಶೂನ್ಯ)
    {
        _SDL_GLView->SwapBuffers();
    }
#endif

    /* * * * * Event sending * * * * */
    // Hook functions
    ಆಭಾಸ ಶೂನ್ಯ FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage ಸಂದೇಶ(BAPP_WINDOW_MOVED);
        ಸಂದೇಶ.AddInt32("window-x", (ಪೂರ್ಣಾಙ್ಕ)origin.x);
        ಸಂದೇಶ.AddInt32("window-y", (ಪೂರ್ಣಾಙ್ಕ)origin.y);
        _PostWindowEvent(ಸಂದೇಶ);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    ಶೂನ್ಯ FrameResized(ಭಿನ್ನ width, ಭಿನ್ನ height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage ಸಂದೇಶ(BAPP_WINDOW_RESIZED);

        ಸಂದೇಶ.AddInt32("window-w", (ಪೂರ್ಣಾಙ್ಕ)width + 1);
        ಸಂದೇಶ.AddInt32("window-h", (ಪೂರ್ಣಾಙ್ಕ)height + 1);
        _PostWindowEvent(ಸಂದೇಶ);

        // Perform normal hook operations
        BWindow::FrameResized(width, height);
    }

    bool QuitRequested()
    {
        BMessage ಸಂದೇಶ(BAPP_WINDOW_CLOSE_REQUESTED);
        _PostWindowEvent(ಸಂದೇಶ);

        // We won't allow a quit unless asked by DestroyWindow()
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಶೂನ್ಯ WindowActivated(bool active)
    {
        BMessage ಸಂದೇಶ(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        ಸಂದೇಶ.AddBool("focusGained", active);
        _PostWindowEvent(ಸಂದೇಶ);
    }

    ಶೂನ್ಯ Zoom(BPoint origin,
              ಭಿನ್ನ width,
              ಭಿನ್ನ height)
    {
        BMessage ಸಂದೇಶ(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(ಸಂದೇಶ);

        // Before the window zooms, record its size
        ಯದಿ (!_prev_frame)
            _prev_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    ಶೂನ್ಯ Show()
    {
        ಯಾವತ್ (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage ಸಂದೇಶ(BAPP_SHOW);
        _PostWindowEvent(ಸಂದೇಶ);
    }

    ಶೂನ್ಯ Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage ಸಂದೇಶ(BAPP_HIDE);
        _PostWindowEvent(ಸಂದೇಶ);
    }

    ಶೂನ್ಯ Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage ಸಂದೇಶ(minState);
        _PostWindowEvent(ಸಂದೇಶ);
    }

    ಶೂನ್ಯ ScreenChanged(BRect screenFrame, color_space depth)
    {
        ಯದಿ (_fullscreen) {
            MoveTo(screenFrame.ಎಡ, screenFrame.ತುದಿ);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    ಶೂನ್ಯ DispatchMessage(BMessage *ಸಂದೇಶ, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 ಕೀಲಿ;     // Used for key events

        ವಿಕಲ್ಪ (ಸಂದೇಶ->what) {
        ಪಕ್ಷ B_MOUSE_MOVED:
            int32 transit;
            ಯದಿ (ಸಂದೇಶ->FindPoint("where", &where) == B_OK && ಸಂದೇಶ->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            ಭಙ್ಗ;

        ಪಕ್ಷ B_MOUSE_DOWN:
            ಯದಿ (ಸಂದೇಶ->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            ಭಙ್ಗ;

        ಪಕ್ಷ B_MOUSE_UP:
            ಯದಿ (ಸಂದೇಶ->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            ಭಙ್ಗ;

        ಪಕ್ಷ B_MOUSE_WHEEL_CHANGED:
            ಭಿನ್ನ x, y;
            ಯದಿ (ಸಂದೇಶ->FindFloat("be:wheel_delta_x", &x) == B_OK && ಸಂದೇಶ->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((ಪೂರ್ಣಾಙ್ಕ)x, (ಪೂರ್ಣಾಙ್ಕ)y);
            }
            ಭಙ್ಗ;

        ಪಕ್ಷ B_ಕೀಲಿ_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            ಯಾವತ್ (i < 4 && ಸಂದೇಶ->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            ಯದಿ (ಸಂದೇಶ->FindInt32("key", &ಕೀಲಿ) == B_OK) {
                ಕೀಲಿ_Event_2((SDL_Scancode)ಕೀಲಿ, &bytes[0], i, true);
            }
        } ಭಙ್ಗ;

        ಪಕ್ಷ B_UNMAPPED_ಕೀಲಿ_DOWN: // modifier keys are unmapped
            ಯದಿ (ಸಂದೇಶ->FindInt32("key", &ಕೀಲಿ) == B_OK) {
                ಕೀಲಿ_Event_2((SDL_Scancode)ಕೀಲಿ, ರಿಕ್ತ, 0, true);
            }
            ಭಙ್ಗ;

        ಪಕ್ಷ B_ಕೀಲಿ_UP:
        ಪಕ್ಷ B_UNMAPPED_ಕೀಲಿ_UP: // modifier keys are unmapped
            ಯದಿ (ಸಂದೇಶ->FindInt32("key", &ಕೀಲಿ) == B_OK) {
                ಕೀಲಿ_Event_2(ಕೀಲಿ, ರಿಕ್ತ, 0, false);
            }
            ಭಙ್ಗ;

        ಸ್ವಭಾವ:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            ಭಙ್ಗ;
        }

        BWindow::DispatchMessage(ಸಂದೇಶ, target);
    }

    // Handle command messages
    ಶೂನ್ಯ MessageReceived(BMessage *message)
    {
        ವಿಕಲ್ಪ (message->what) {
        // Handle commands from SDL
        ಪಕ್ಷ BWIN_SET_TITLE:
            _SetTitle(message);
            ಭಙ್ಗ;
        ಪಕ್ಷ BWIN_MOVE_WINDOW:
            _MoveTo(message);
            ಭಙ್ಗ;
        ಪಕ್ಷ BWIN_RESIZE_WINDOW:
            _ResizeTo(message);
            ಭಙ್ಗ;
        ಪಕ್ಷ BWIN_SET_BORDERED:
        {
            bool bEnabled;
            ಯದಿ (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            ಭಙ್ಗ;
        }
        ಪಕ್ಷ BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            ಯದಿ (message->FindBool("window-resizable", &bEnabled) == B_OK)
                _SetResizable(bEnabled);
            ಭಙ್ಗ;
        }
        ಪಕ್ಷ BWIN_SHOW_WINDOW:
            Show();
            ಭಙ್ಗ;
        ಪಕ್ಷ BWIN_HIDE_WINDOW:
            Hide();
            ಭಙ್ಗ;
        ಪಕ್ಷ BWIN_MAXIMIZE_WINDOW:
            BWindow::Zoom();
            ಭಙ್ಗ;
        ಪಕ್ಷ BWIN_MINIMIZE_WINDOW:
            Minimize(true);
            ಭಙ್ಗ;
        ಪಕ್ಷ BWIN_RESTORE_WINDOW:
            _Restore();
            ಭಙ್ಗ;
        ಪಕ್ಷ BWIN_FULLSCREEN:
        {
            bool fullscreen;
            ಯದಿ (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            ಭಙ್ಗ;
        }
        ಪಕ್ಷ BWIN_MINIMUM_SIZE_WINDOW:
            _SetMinimumSize(message);
            ಭಙ್ಗ;
        ಪಕ್ಷ BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            ಯಾವತ್ ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            ಯದಿ (_bitmap != ರಿಕ್ತ) {
#ifdef SDL_VIDEO_OPENGL
                ಯದಿ (_SDL_GLView != ರಿಕ್ತ && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } ಅನ್ಯಥಾ
#endif
                ಯದಿ (_SDL_View != ರಿಕ್ತ && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            ಭಙ್ಗ;
        }
        ಸ್ವಭಾವ:
            // Perform normal message handling
            BWindow::MessageReceived(message);
            ಭಙ್ಗ;
        }
    }

    // Accessor methods
    bool IsShown() { ಪ್ರತ್ಯಾಗಮ _shown; }
    int32 GetID() { ಪ್ರತ್ಯಾಗಮ _id; }
    BBitmap *GetBitmap() { ಪ್ರತ್ಯಾಗಮ _bitmap; }
    BView *GetCurView() { ಪ್ರತ್ಯಾಗಮ _cur_view; }
    SDL_BView *GetView() { ಪ್ರತ್ಯಾಗಮ _SDL_View; }
#ifdef SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        ಪ್ರತ್ಯಾಗಮ _SDL_GLView;
    }
    Uint32 GetGLType() { ಪ್ರತ್ಯಾಗಮ _gl_type; }
#endif

    // Setter methods
    ಶೂನ್ಯ SetID(int32 id) { _id = id; }
    ಶೂನ್ಯ LockBuffer() { _buffer_locker->Lock(); }
    ಶೂನ್ಯ UnlockBuffer() { _buffer_locker->Unlock(); }
    ಶೂನ್ಯ SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        ಯದಿ (_SDL_View != ರಿಕ್ತ)
            _SDL_View->SetBitmap(bitmap);
    }

  ಗುಪ್ತ:
    // Event redirection
    ಶೂನ್ಯ _MouseMotionEvent(BPoint &where, int32 transit)
    {
        ಯದಿ (transit == B_EXITED_VIEW) {
            // Change mouse focus
            ಯದಿ (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } ಅನ್ಯಥಾ {
            // Change mouse focus
            ಯದಿ (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage ಸಂದೇಶ(BAPP_MOUSE_MOVED);
            ಸಂದೇಶ.AddInt32("x", (ಪೂರ್ಣಾಙ್ಕ)where.x);
            ಸಂದೇಶ.AddInt32("y", (ಪೂರ್ಣಾಙ್ಕ)where.y);

            _PostWindowEvent(ಸಂದೇಶ);
        }
    }

    ಶೂನ್ಯ _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage ಸಂದೇಶ(BAPP_MOUSE_FOCUS);
        ಸಂದೇಶ.AddBool("focusGained", focusGained);
        _PostWindowEvent(ಸಂದೇಶ);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    ಶೂನ್ಯ _MouseButtonEvent(int32 buttons, bool down)
    {
        int32 buttonStateChange = buttons ^ _last_buttons;

        ಯದಿ (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ಎಡ, down);
        }
        ಯದಿ (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ಬಲ, down);
        }
        ಯದಿ (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ಮಧ್ಯ, down);
        }

        _last_buttons = buttons;
    }

    ಶೂನ್ಯ _SendMouseButton(int32 button, bool down)
    {
        BMessage ಸಂದೇಶ(BAPP_MOUSE_BUTTON);
        ಸಂದೇಶ.AddInt32("button-id", button);
        ಸಂದೇಶ.AddBool("button-down", down);
        _PostWindowEvent(ಸಂದೇಶ);
    }

    ಶೂನ್ಯ _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage ಸಂದೇಶ(BAPP_MOUSE_WHEEL);
        ಸಂದೇಶ.AddInt32("xticks", x);
        ಸಂದೇಶ.AddInt32("yticks", y);
        _PostWindowEvent(ಸಂದೇಶ);
    }

    ಶೂನ್ಯ ಕೀಲಿ_Event_2(int32 ಕೀಲಿ_Code, ಧ್ರುವ int8 *ಕೀಲಿ_Utf8, ಧ್ರುವ ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage ಸಂದೇಶ(BAPP_ಕೀಲಿ);
        ಸಂದೇಶ.AddInt32("key-scancode", ಕೀಲಿ_Code);
        ಯದಿ (ಕೀಲಿ_Utf8 != ರಿಕ್ತ) {
            ಸಂದೇಶ.AddData("key-utf8", B_INT8_TYPE, (ಧ್ರುವ ಶೂನ್ಯ *)ಕೀಲಿ_Utf8, len);
        }
        ಸಂದೇಶ.AddBool("key-down", down);
        SDL_Looper->PostMessage(&ಸಂದೇಶ);
    }

    ಶೂನ್ಯ _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage ಸಂದೇಶ(BAPP_REPAINT);
        _PostWindowEvent(ಸಂದೇಶ);
    }
    ಶೂನ್ಯ _PostWindowEvent(BMessage &ಸಂದೇಶ)
    {
        ಸಂದೇಶ.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&ಸಂದೇಶ);
    }

    // Command methods (functions called upon by SDL)
    ಶೂನ್ಯ _SetTitle(BMessage *ಸಂದೇಶ)
    {
        ಧ್ರುವ ವರ್ಣ *title;
        ಯದಿ (
            ಸಂದೇಶ->FindString("window-title", &title) != B_OK) {
            ಪ್ರತ್ಯಾಗಮ;
        }
        SetTitle(title);
    }

    ಶೂನ್ಯ _MoveTo(BMessage *ಸಂದೇಶ)
    {
        int32 x, y;
        ಯದಿ (
            ಸಂದೇಶ->FindInt32("window-x", &x) != B_OK ||
            ಸಂದೇಶ->FindInt32("window-y", &y) != B_OK) {
            ಪ್ರತ್ಯಾಗಮ;
        }
        ಯದಿ (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        ಅನ್ಯಥಾ
            MoveTo(x, y);
    }

    ಶೂನ್ಯ _ResizeTo(BMessage *ಸಂದೇಶ)
    {
        int32 w, h;
        ಯದಿ (
            ಸಂದೇಶ->FindInt32("window-w", &w) != B_OK ||
            ಸಂದೇಶ->FindInt32("window-h", &h) != B_OK) {
            ಪ್ರತ್ಯಾಗಮ;
        }
        ಯದಿ (_fullscreen) {
            _non_fullscreen_frame.ಬಲ = _non_fullscreen_frame.ಎಡ + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.ತುದಿ + h;
        } ಅನ್ಯಥಾ
            ResizeTo(w, h);
    }

    ಶೂನ್ಯ _SetBordered(bool bEnabled)
    {
        ಯದಿ (_fullscreen)
            _bordered = bEnabled;
        ಅನ್ಯಥಾ
            SetLook(bEnabled ? B_TITLED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
    }

    ಶೂನ್ಯ _SetResizable(bool bEnabled)
    {
        ಯದಿ (_fullscreen)
            _resizable = bEnabled;
        ಅನ್ಯಥಾ {
            ಯದಿ (bEnabled) {
                SetFlags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } ಅನ್ಯಥಾ {
                SetFlags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    ಶೂನ್ಯ _SetMinimumSize(BMessage *ಸಂದೇಶ)
    {
        ಭಿನ್ನ maxHeight;
        ಭಿನ್ನ maxWidth;
        ಭಿನ್ನ _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        GetSizeLimits(&_, &maxWidth, &_, &maxHeight);
        ಯದಿ (ಸಂದೇಶ->FindInt32("window-w", &minWidth) != B_OK)
            ಪ್ರತ್ಯಾಗಮ;
        ಯದಿ (ಸಂದೇಶ->FindInt32("window-h", &minHeight) != B_OK)
            ಪ್ರತ್ಯಾಗಮ;
        SetSizeLimits((ಭಿನ್ನ)minWidth, maxWidth, (ಭಿನ್ನ)minHeight, maxHeight);
        UpdateSizeLimits();
    }

    ಶೂನ್ಯ _Restore()
    {
        ಯದಿ (IsMinimized()) {
            Minimize(false);
        } ಅನ್ಯಥಾ ಯದಿ (IsHidden()) {
            Show();
        } ಅನ್ಯಥಾ ಯದಿ (_fullscreen) {

        } ಅನ್ಯಥಾ ಯದಿ (_prev_frame != ರಿಕ್ತ) { // Zoomed
            MoveTo(_prev_frame->ಎಡ, _prev_frame->ತುದಿ);
            ResizeTo(_prev_frame->Width(), _prev_frame->Height());
        }
    }

    ಶೂನ್ಯ _SetFullScreen(bool fullscreen)
    {
        ಯದಿ (fullscreen != _fullscreen) {
            ಯದಿ (fullscreen) {
                BScreen screen(this);
                BRect screenFrame = screen.Frame();
                _bordered = Look() != B_NO_BORDER_WINDOW_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                _non_fullscreen_frame = Frame();
                _SetBordered(false);
                _SetResizable(false);
                MoveTo(screenFrame.ಎಡ, screenFrame.ತುದಿ);
                ResizeTo(screenFrame.Width(), screenFrame.Height());
                _fullscreen = fullscreen;
            } ಅನ್ಯಥಾ {
                _fullscreen = fullscreen;
                MoveTo(_non_fullscreen_frame.ಎಡ, _non_fullscreen_frame.ತುದಿ);
                ResizeTo(_non_fullscreen_frame.Width(), _non_fullscreen_frame.Height());
                _SetBordered(_bordered);
                _SetResizable(_resizable);
            }
        }
    }

    // Members

    BView *_cur_view;
    SDL_BView *_SDL_View;
#ifdef SDL_VIDEO_OPENGL
    BGLView *_SDL_GLView;
    Uint32 _gl_type;
#endif

    int32 _last_buttons;
    int32 _id;           // Window id used by SDL_BApp
    bool _mouse_focused; // Does this window have mouse focus?
    bool _shown;
    bool _inhibit_resize;

    BRect *_prev_frame; // Previous position and size of the window
    bool _fullscreen;
    // valid only if fullscreen
    BRect _non_fullscreen_frame;
    bool _bordered;
    bool _resizable;

    // Framebuffer members
    BLocker *_buffer_locker;
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
#endif // SDL_BWin_h_
