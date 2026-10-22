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
ବାହ୍ୟ "C" {
#endif

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"
#ଅନ୍ତର୍ଭାଵ "SDL_bframebuffer.h"

#ifdef __cplusplus
}
#endif

#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <AppKit.h>
#ଅନ୍ତର୍ଭାଵ <Cursor.h>
#ଅନ୍ତର୍ଭାଵ <InterfaceKit.h>
#ifdef SDL_VIDEO_OPENGL
#ଅନ୍ତର୍ଭାଵ <opengl/GLView.h>
#endif
#ଅନ୍ତର୍ଭାଵ "../../core/haiku/SDL_BApp.h"

ଗଣନା WinCommands
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
class SDL_BView : ସର୍ବସାଧାରଣ BView
{
  ସର୍ବସାଧାରଣ:
    SDL_BView(BRect frame, ଅଚଳ ଅକ୍ଷର *name, uint32 resizingMode)
        : BView(frame, name, resizingMode, B_WILL_DRAW),
          fBitmap(ଖାଲି)
    {
    }

    ଶୂନ୍ୟ Draw(BRect dirty)
    {
        ଯଦି (fBitmap != ଖାଲି)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    ଶୂନ୍ୟ SetBitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  ବ୍ୟକ୍ତିଗତ:
    BBitmap *fBitmap;
};

class SDL_BWin : ସର୍ବସାଧାରଣ BWindow
{
  ସର୍ବସାଧାରଣ:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, window_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_NORMAL_WINDOW_FEEL, flags)
    {
        _last_buttons = 0;

        _cur_view = ଖାଲି;
        _SDL_View = ଖାଲି;

#ifdef SDL_VIDEO_OPENGL
        _SDL_GLView = ଖାଲି;
        _gl_type = 0;
#endif
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        _prev_frame = ଖାଲି;
        _fullscreen = ଖାଲି;

        // Handle framebuffer stuff
        _buffer_locker = new BLocker();
        _bitmap = ଖାଲି;
    }

    ଆଭାସୀ ~SDL_BWin()
    {
        Lock();

        ଯଦି (_SDL_View != ଖାଲି && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = ଖାଲି;
        }

#ifdef SDL_VIDEO_OPENGL
        ଯଦି (_SDL_GLView) {
            ଯଦି (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(ଖାଲି);
            ଯଦି (_SDL_GLView == _cur_view)
                RemoveChild(_SDL_GLView);
            _SDL_GLView = ଖାଲି;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#endif
        Unlock();

        delete _prev_frame;

        // Clean up framebuffer stuff
        _buffer_locker->Lock();
        delete _buffer_locker;
    }

    ଶୂନ୍ୟ SetCurrentView(BView *view)
    {
        ଯଦି (_cur_view != view) {
            ଯଦି (_cur_view != ଖାଲି)
                RemoveChild(_cur_view);
            _cur_view = view;
            ଯଦି (_cur_view != ଖାଲି)
                AddChild(_cur_view);
        }
    }

    ଶୂନ୍ୟ UpdateCurrentView()
    {
#ifdef SDL_VIDEO_OPENGL
        ଯଦି (_SDL_GLView != ଖାଲି) {
            SetCurrentView(_SDL_GLView);
        } ଅନ୍ୟଥା
#endif
        ଯଦି (_SDL_View != ଖାଲି) {
            SetCurrentView(_SDL_View);
        } ଅନ୍ୟଥା {
            SetCurrentView(ଖାଲି);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        ଯଦି (_SDL_View == ଖାଲି) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        ଫେରନ୍ତୁ _SDL_View;
    }

    ଶୂନ୍ୟ RemoveView()
    {
        Lock();
        ଯଦି (_SDL_View != ଖାଲି) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = ଖାଲି;
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
        ଯଦି (_SDL_GLView == ଖାଲି) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        ଫେରନ୍ତୁ _SDL_GLView;
    }

    ଶୂନ୍ୟ RemoveGLView()
    {
        Lock();
        ଯଦି (_SDL_GLView != ଖାଲି) {
            ଯଦି (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(ଖାଲି);
            _SDL_GLView = ଖାଲି;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    ଶୂନ୍ୟ SwapBuffers(ଶୂନ୍ୟ)
    {
        _SDL_GLView->SwapBuffers();
    }
#endif

    /* * * * * Event sending * * * * */
    // Hook functions
    ଆଭାସୀ ଶୂନ୍ୟ FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage ସନ୍ଦେଶ(BAPP_WINDOW_MOVED);
        ସନ୍ଦେଶ.AddInt32("window-x", (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)origin.x);
        ସନ୍ଦେଶ.AddInt32("window-y", (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)origin.y);
        _PostWindowEvent(ସନ୍ଦେଶ);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    ଶୂନ୍ୟ FrameResized(ଦଶମିକ width, ଦଶମିକ height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage ସନ୍ଦେଶ(BAPP_WINDOW_RESIZED);

        ସନ୍ଦେଶ.AddInt32("window-w", (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)width + 1);
        ସନ୍ଦେଶ.AddInt32("window-h", (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)height + 1);
        _PostWindowEvent(ସନ୍ଦେଶ);

        // Perform normal hook operations
        BWindow::FrameResized(width, height);
    }

    bool QuitRequested()
    {
        BMessage ସନ୍ଦେଶ(BAPP_WINDOW_CLOSE_REQUESTED);
        _PostWindowEvent(ସନ୍ଦେଶ);

        // We won't allow a quit unless asked by DestroyWindow()
        ଫେରନ୍ତୁ false;
    }

    ଶୂନ୍ୟ WindowActivated(bool active)
    {
        BMessage ସନ୍ଦେଶ(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        ସନ୍ଦେଶ.AddBool("focusGained", active);
        _PostWindowEvent(ସନ୍ଦେଶ);
    }

    ଶୂନ୍ୟ Zoom(BPoint origin,
              ଦଶମିକ width,
              ଦଶମିକ height)
    {
        BMessage ସନ୍ଦେଶ(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(ସନ୍ଦେଶ);

        // Before the window zooms, record its size
        ଯଦି (!_prev_frame)
            _prev_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    ଶୂନ୍ୟ Show()
    {
        ଯେତେବେଳେ (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage ସନ୍ଦେଶ(BAPP_SHOW);
        _PostWindowEvent(ସନ୍ଦେଶ);
    }

    ଶୂନ୍ୟ Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage ସନ୍ଦେଶ(BAPP_HIDE);
        _PostWindowEvent(ସନ୍ଦେଶ);
    }

    ଶୂନ୍ୟ Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage ସନ୍ଦେଶ(minState);
        _PostWindowEvent(ସନ୍ଦେଶ);
    }

    ଶୂନ୍ୟ ScreenChanged(BRect screenFrame, color_space depth)
    {
        ଯଦି (_fullscreen) {
            MoveTo(screenFrame.ବାମ, screenFrame.ଶୀର୍ଷ);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    ଶୂନ୍ୟ DispatchMessage(BMessage *ସନ୍ଦେଶ, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 ଚାବି;     // Used for key events

        ବାଛ (ସନ୍ଦେଶ->what) {
        ସ୍ଥିତି B_MOUSE_MOVED:
            int32 transit;
            ଯଦି (ସନ୍ଦେଶ->FindPoint("where", &where) == B_OK && ସନ୍ଦେଶ->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            ଭାଙ୍ଗ;

        ସ୍ଥିତି B_MOUSE_DOWN:
            ଯଦି (ସନ୍ଦେଶ->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            ଭାଙ୍ଗ;

        ସ୍ଥିତି B_MOUSE_UP:
            ଯଦି (ସନ୍ଦେଶ->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            ଭାଙ୍ଗ;

        ସ୍ଥିତି B_MOUSE_WHEEL_CHANGED:
            ଦଶମିକ x, y;
            ଯଦି (ସନ୍ଦେଶ->FindFloat("be:wheel_delta_x", &x) == B_OK && ସନ୍ଦେଶ->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((ପୂର୍ଣ୍ଣସଂଖ୍ୟା)x, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)y);
            }
            ଭାଙ୍ଗ;

        ସ୍ଥିତି B_ଚାବି_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            ଯେତେବେଳେ (i < 4 && ସନ୍ଦେଶ->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            ଯଦି (ସନ୍ଦେଶ->FindInt32("key", &ଚାବି) == B_OK) {
                ଚାବି_Event_2((SDL_Scancode)ଚାବି, &bytes[0], i, true);
            }
        } ଭାଙ୍ଗ;

        ସ୍ଥିତି B_UNMAPPED_ଚାବି_DOWN: // modifier keys are unmapped
            ଯଦି (ସନ୍ଦେଶ->FindInt32("key", &ଚାବି) == B_OK) {
                ଚାବି_Event_2((SDL_Scancode)ଚାବି, ଖାଲି, 0, true);
            }
            ଭାଙ୍ଗ;

        ସ୍ଥିତି B_ଚାବି_UP:
        ସ୍ଥିତି B_UNMAPPED_ଚାବି_UP: // modifier keys are unmapped
            ଯଦି (ସନ୍ଦେଶ->FindInt32("key", &ଚାବି) == B_OK) {
                ଚାବି_Event_2(ଚାବି, ଖାଲି, 0, false);
            }
            ଭାଙ୍ଗ;

        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            ଭାଙ୍ଗ;
        }

        BWindow::DispatchMessage(ସନ୍ଦେଶ, target);
    }

    // Handle command messages
    ଶୂନ୍ୟ MessageReceived(BMessage *message)
    {
        ବାଛ (message->what) {
        // Handle commands from SDL
        ସ୍ଥିତି BWIN_SET_TITLE:
            _SetTitle(message);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି BWIN_MOVE_WINDOW:
            _MoveTo(message);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି BWIN_RESIZE_WINDOW:
            _ResizeTo(message);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି BWIN_SET_BORDERED:
        {
            bool bEnabled;
            ଯଦି (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            ଭାଙ୍ଗ;
        }
        ସ୍ଥିତି BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            ଯଦି (message->FindBool("window-resizable", &bEnabled) == B_OK)
                _SetResizable(bEnabled);
            ଭାଙ୍ଗ;
        }
        ସ୍ଥିତି BWIN_SHOW_WINDOW:
            Show();
            ଭାଙ୍ଗ;
        ସ୍ଥିତି BWIN_HIDE_WINDOW:
            Hide();
            ଭାଙ୍ଗ;
        ସ୍ଥିତି BWIN_MAXIMIZE_WINDOW:
            BWindow::Zoom();
            ଭାଙ୍ଗ;
        ସ୍ଥିତି BWIN_MINIMIZE_WINDOW:
            Minimize(true);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି BWIN_RESTORE_WINDOW:
            _Restore();
            ଭାଙ୍ଗ;
        ସ୍ଥିତି BWIN_FULLSCREEN:
        {
            bool fullscreen;
            ଯଦି (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            ଭାଙ୍ଗ;
        }
        ସ୍ଥିତି BWIN_MINIMUM_SIZE_WINDOW:
            _SetMinimumSize(message);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            ଯେତେବେଳେ ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            ଯଦି (_bitmap != ଖାଲି) {
#ifdef SDL_VIDEO_OPENGL
                ଯଦି (_SDL_GLView != ଖାଲି && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } ଅନ୍ୟଥା
#endif
                ଯଦି (_SDL_View != ଖାଲି && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            ଭାଙ୍ଗ;
        }
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            // Perform normal message handling
            BWindow::MessageReceived(message);
            ଭାଙ୍ଗ;
        }
    }

    // Accessor methods
    bool IsShown() { ଫେରନ୍ତୁ _shown; }
    int32 GetID() { ଫେରନ୍ତୁ _id; }
    BBitmap *GetBitmap() { ଫେରନ୍ତୁ _bitmap; }
    BView *GetCurView() { ଫେରନ୍ତୁ _cur_view; }
    SDL_BView *GetView() { ଫେରନ୍ତୁ _SDL_View; }
#ifdef SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        ଫେରନ୍ତୁ _SDL_GLView;
    }
    Uint32 GetGLType() { ଫେରନ୍ତୁ _gl_type; }
#endif

    // Setter methods
    ଶୂନ୍ୟ SetID(int32 id) { _id = id; }
    ଶୂନ୍ୟ LockBuffer() { _buffer_locker->Lock(); }
    ଶୂନ୍ୟ UnlockBuffer() { _buffer_locker->Unlock(); }
    ଶୂନ୍ୟ SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        ଯଦି (_SDL_View != ଖାଲି)
            _SDL_View->SetBitmap(bitmap);
    }

  ବ୍ୟକ୍ତିଗତ:
    // Event redirection
    ଶୂନ୍ୟ _MouseMotionEvent(BPoint &where, int32 transit)
    {
        ଯଦି (transit == B_EXITED_VIEW) {
            // Change mouse focus
            ଯଦି (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } ଅନ୍ୟଥା {
            // Change mouse focus
            ଯଦି (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage ସନ୍ଦେଶ(BAPP_MOUSE_MOVED);
            ସନ୍ଦେଶ.AddInt32("x", (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)where.x);
            ସନ୍ଦେଶ.AddInt32("y", (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)where.y);

            _PostWindowEvent(ସନ୍ଦେଶ);
        }
    }

    ଶୂନ୍ୟ _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage ସନ୍ଦେଶ(BAPP_MOUSE_FOCUS);
        ସନ୍ଦେଶ.AddBool("focusGained", focusGained);
        _PostWindowEvent(ସନ୍ଦେଶ);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    ଶୂନ୍ୟ _MouseButtonEvent(int32 buttons, bool down)
    {
        int32 buttonStateChange = buttons ^ _last_buttons;

        ଯଦି (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ବାମ, down);
        }
        ଯଦି (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ଡାହାଣ, down);
        }
        ଯଦି (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ମଧ୍ୟ, down);
        }

        _last_buttons = buttons;
    }

    ଶୂନ୍ୟ _SendMouseButton(int32 button, bool down)
    {
        BMessage ସନ୍ଦେଶ(BAPP_MOUSE_BUTTON);
        ସନ୍ଦେଶ.AddInt32("button-id", button);
        ସନ୍ଦେଶ.AddBool("button-down", down);
        _PostWindowEvent(ସନ୍ଦେଶ);
    }

    ଶୂନ୍ୟ _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage ସନ୍ଦେଶ(BAPP_MOUSE_WHEEL);
        ସନ୍ଦେଶ.AddInt32("xticks", x);
        ସନ୍ଦେଶ.AddInt32("yticks", y);
        _PostWindowEvent(ସନ୍ଦେଶ);
    }

    ଶୂନ୍ୟ ଚାବି_Event_2(int32 ଚାବି_Code, ଅଚଳ int8 *ଚାବି_Utf8, ଅଚଳ ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage ସନ୍ଦେଶ(BAPP_ଚାବି);
        ସନ୍ଦେଶ.AddInt32("key-scancode", ଚାବି_Code);
        ଯଦି (ଚାବି_Utf8 != ଖାଲି) {
            ସନ୍ଦେଶ.AddData("key-utf8", B_INT8_TYPE, (ଅଚଳ ଶୂନ୍ୟ *)ଚାବି_Utf8, len);
        }
        ସନ୍ଦେଶ.AddBool("key-down", down);
        SDL_Looper->PostMessage(&ସନ୍ଦେଶ);
    }

    ଶୂନ୍ୟ _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage ସନ୍ଦେଶ(BAPP_REPAINT);
        _PostWindowEvent(ସନ୍ଦେଶ);
    }
    ଶୂନ୍ୟ _PostWindowEvent(BMessage &ସନ୍ଦେଶ)
    {
        ସନ୍ଦେଶ.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&ସନ୍ଦେଶ);
    }

    // Command methods (functions called upon by SDL)
    ଶୂନ୍ୟ _SetTitle(BMessage *ସନ୍ଦେଶ)
    {
        ଅଚଳ ଅକ୍ଷର *title;
        ଯଦି (
            ସନ୍ଦେଶ->FindString("window-title", &title) != B_OK) {
            ଫେରନ୍ତୁ;
        }
        SetTitle(title);
    }

    ଶୂନ୍ୟ _MoveTo(BMessage *ସନ୍ଦେଶ)
    {
        int32 x, y;
        ଯଦି (
            ସନ୍ଦେଶ->FindInt32("window-x", &x) != B_OK ||
            ସନ୍ଦେଶ->FindInt32("window-y", &y) != B_OK) {
            ଫେରନ୍ତୁ;
        }
        ଯଦି (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        ଅନ୍ୟଥା
            MoveTo(x, y);
    }

    ଶୂନ୍ୟ _ResizeTo(BMessage *ସନ୍ଦେଶ)
    {
        int32 w, h;
        ଯଦି (
            ସନ୍ଦେଶ->FindInt32("window-w", &w) != B_OK ||
            ସନ୍ଦେଶ->FindInt32("window-h", &h) != B_OK) {
            ଫେରନ୍ତୁ;
        }
        ଯଦି (_fullscreen) {
            _non_fullscreen_frame.ଡାହାଣ = _non_fullscreen_frame.ବାମ + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.ଶୀର୍ଷ + h;
        } ଅନ୍ୟଥା
            ResizeTo(w, h);
    }

    ଶୂନ୍ୟ _SetBordered(bool bEnabled)
    {
        ଯଦି (_fullscreen)
            _bordered = bEnabled;
        ଅନ୍ୟଥା
            SetLook(bEnabled ? B_TITLED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
    }

    ଶୂନ୍ୟ _SetResizable(bool bEnabled)
    {
        ଯଦି (_fullscreen)
            _resizable = bEnabled;
        ଅନ୍ୟଥା {
            ଯଦି (bEnabled) {
                SetFlags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } ଅନ୍ୟଥା {
                SetFlags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    ଶୂନ୍ୟ _SetMinimumSize(BMessage *ସନ୍ଦେଶ)
    {
        ଦଶମିକ maxHeight;
        ଦଶମିକ maxWidth;
        ଦଶମିକ _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        GetSizeLimits(&_, &maxWidth, &_, &maxHeight);
        ଯଦି (ସନ୍ଦେଶ->FindInt32("window-w", &minWidth) != B_OK)
            ଫେରନ୍ତୁ;
        ଯଦି (ସନ୍ଦେଶ->FindInt32("window-h", &minHeight) != B_OK)
            ଫେରନ୍ତୁ;
        SetSizeLimits((ଦଶମିକ)minWidth, maxWidth, (ଦଶମିକ)minHeight, maxHeight);
        UpdateSizeLimits();
    }

    ଶୂନ୍ୟ _Restore()
    {
        ଯଦି (IsMinimized()) {
            Minimize(false);
        } ଅନ୍ୟଥା ଯଦି (IsHidden()) {
            Show();
        } ଅନ୍ୟଥା ଯଦି (_fullscreen) {

        } ଅନ୍ୟଥା ଯଦି (_prev_frame != ଖାଲି) { // Zoomed
            MoveTo(_prev_frame->ବାମ, _prev_frame->ଶୀର୍ଷ);
            ResizeTo(_prev_frame->Width(), _prev_frame->Height());
        }
    }

    ଶୂନ୍ୟ _SetFullScreen(bool fullscreen)
    {
        ଯଦି (fullscreen != _fullscreen) {
            ଯଦି (fullscreen) {
                BScreen screen(this);
                BRect screenFrame = screen.Frame();
                _bordered = Look() != B_NO_BORDER_WINDOW_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                _non_fullscreen_frame = Frame();
                _SetBordered(false);
                _SetResizable(false);
                MoveTo(screenFrame.ବାମ, screenFrame.ଶୀର୍ଷ);
                ResizeTo(screenFrame.Width(), screenFrame.Height());
                _fullscreen = fullscreen;
            } ଅନ୍ୟଥା {
                _fullscreen = fullscreen;
                MoveTo(_non_fullscreen_frame.ବାମ, _non_fullscreen_frame.ଶୀର୍ଷ);
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
