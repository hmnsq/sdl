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
বাহ্য "C" {
#endif

#অন্তর্ভাৱ "SDL_internal.h"
#অন্তর্ভাৱ "SDL_bframebuffer.h"

#ifdef __cplusplus
}
#endif

#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <AppKit.h>
#অন্তর্ভাৱ <Cursor.h>
#অন্তর্ভাৱ <InterfaceKit.h>
#ifdef SDL_VIDEO_OPENGL
#অন্তর্ভাৱ <opengl/GLView.h>
#endif
#অন্তর্ভাৱ "../../core/haiku/SDL_BApp.h"

গণনা WinCommands
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
class SDL_BView : সার্ৱজনিক BView
{
  সার্ৱজনিক:
    SDL_BView(BRect frame, ধ্রুৱ ৱর্ণ *name, uint32 resizingMode)
        : BView(frame, name, resizingMode, B_WILL_DRAW),
          fBitmap(রিক্ত)
    {
    }

    শূন্য Draw(BRect dirty)
    {
        যদি (fBitmap != রিক্ত)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    শূন্য SetBitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  গুপ্ত:
    BBitmap *fBitmap;
};

class SDL_BWin : সার্ৱজনিক BWindow
{
  সার্ৱজনিক:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, window_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_NORMAL_WINDOW_FEEL, flags)
    {
        _last_buttons = 0;

        _cur_view = রিক্ত;
        _SDL_View = রিক্ত;

#ifdef SDL_VIDEO_OPENGL
        _SDL_GLView = রিক্ত;
        _gl_type = 0;
#endif
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        _prev_frame = রিক্ত;
        _fullscreen = রিক্ত;

        // Handle framebuffer stuff
        _buffer_locker = new BLocker();
        _bitmap = রিক্ত;
    }

    আভাস ~SDL_BWin()
    {
        Lock();

        যদি (_SDL_View != রিক্ত && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = রিক্ত;
        }

#ifdef SDL_VIDEO_OPENGL
        যদি (_SDL_GLView) {
            যদি (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(রিক্ত);
            যদি (_SDL_GLView == _cur_view)
                RemoveChild(_SDL_GLView);
            _SDL_GLView = রিক্ত;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#endif
        Unlock();

        delete _prev_frame;

        // Clean up framebuffer stuff
        _buffer_locker->Lock();
        delete _buffer_locker;
    }

    শূন্য SetCurrentView(BView *view)
    {
        যদি (_cur_view != view) {
            যদি (_cur_view != রিক্ত)
                RemoveChild(_cur_view);
            _cur_view = view;
            যদি (_cur_view != রিক্ত)
                AddChild(_cur_view);
        }
    }

    শূন্য UpdateCurrentView()
    {
#ifdef SDL_VIDEO_OPENGL
        যদি (_SDL_GLView != রিক্ত) {
            SetCurrentView(_SDL_GLView);
        } অন্যথা
#endif
        যদি (_SDL_View != রিক্ত) {
            SetCurrentView(_SDL_View);
        } অন্যথা {
            SetCurrentView(রিক্ত);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        যদি (_SDL_View == রিক্ত) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        ঘূৰাই _SDL_View;
    }

    শূন্য RemoveView()
    {
        Lock();
        যদি (_SDL_View != রিক্ত) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = রিক্ত;
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
        যদি (_SDL_GLView == রিক্ত) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        ঘূৰাই _SDL_GLView;
    }

    শূন্য RemoveGLView()
    {
        Lock();
        যদি (_SDL_GLView != রিক্ত) {
            যদি (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(রিক্ত);
            _SDL_GLView = রিক্ত;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    শূন্য SwapBuffers(শূন্য)
    {
        _SDL_GLView->SwapBuffers();
    }
#endif

    /* * * * * Event sending * * * * */
    // Hook functions
    আভাস শূন্য FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage বাৰ্তা(BAPP_WINDOW_MOVED);
        বাৰ্তা.AddInt32("window-x", (পূর্ণাঙ্ক)origin.x);
        বাৰ্তা.AddInt32("window-y", (পূর্ণাঙ্ক)origin.y);
        _PostWindowEvent(বাৰ্তা);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    শূন্য FrameResized(ভিন্ন width, ভিন্ন height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage বাৰ্তা(BAPP_WINDOW_RESIZED);

        বাৰ্তা.AddInt32("window-w", (পূর্ণাঙ্ক)width + 1);
        বাৰ্তা.AddInt32("window-h", (পূর্ণাঙ্ক)height + 1);
        _PostWindowEvent(বাৰ্তা);

        // Perform normal hook operations
        BWindow::FrameResized(width, height);
    }

    bool QuitRequested()
    {
        BMessage বাৰ্তা(BAPP_WINDOW_CLOSE_REQUESTED);
        _PostWindowEvent(বাৰ্তা);

        // We won't allow a quit unless asked by DestroyWindow()
        ঘূৰাই false;
    }

    শূন্য WindowActivated(bool active)
    {
        BMessage বাৰ্তা(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        বাৰ্তা.AddBool("focusGained", active);
        _PostWindowEvent(বাৰ্তা);
    }

    শূন্য Zoom(BPoint origin,
              ভিন্ন width,
              ভিন্ন height)
    {
        BMessage বাৰ্তা(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(বাৰ্তা);

        // Before the window zooms, record its size
        যদি (!_prev_frame)
            _prev_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    শূন্য Show()
    {
        যেতিয়ালৈ (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage বাৰ্তা(BAPP_SHOW);
        _PostWindowEvent(বাৰ্তা);
    }

    শূন্য Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage বাৰ্তা(BAPP_HIDE);
        _PostWindowEvent(বাৰ্তা);
    }

    শূন্য Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage বাৰ্তা(minState);
        _PostWindowEvent(বাৰ্তা);
    }

    শূন্য ScreenChanged(BRect screenFrame, color_space depth)
    {
        যদি (_fullscreen) {
            MoveTo(screenFrame.বাম, screenFrame.শীৰ্ষ);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    শূন্য DispatchMessage(BMessage *বাৰ্তা, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 চাবি;     // Used for key events

        ৱিকল্প (বাৰ্তা->what) {
        পক্ষ B_MOUSE_MOVED:
            int32 transit;
            যদি (বাৰ্তা->FindPoint("where", &where) == B_OK && বাৰ্তা->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            ভঙ্গ;

        পক্ষ B_MOUSE_DOWN:
            যদি (বাৰ্তা->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            ভঙ্গ;

        পক্ষ B_MOUSE_UP:
            যদি (বাৰ্তা->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            ভঙ্গ;

        পক্ষ B_MOUSE_WHEEL_CHANGED:
            ভিন্ন x, y;
            যদি (বাৰ্তা->FindFloat("be:wheel_delta_x", &x) == B_OK && বাৰ্তা->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((পূর্ণাঙ্ক)x, (পূর্ণাঙ্ক)y);
            }
            ভঙ্গ;

        পক্ষ B_চাবি_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            যেতিয়ালৈ (i < 4 && বাৰ্তা->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            যদি (বাৰ্তা->FindInt32("key", &চাবি) == B_OK) {
                চাবি_Event_2((SDL_Scancode)চাবি, &bytes[0], i, true);
            }
        } ভঙ্গ;

        পক্ষ B_UNMAPPED_চাবি_DOWN: // modifier keys are unmapped
            যদি (বাৰ্তা->FindInt32("key", &চাবি) == B_OK) {
                চাবি_Event_2((SDL_Scancode)চাবি, রিক্ত, 0, true);
            }
            ভঙ্গ;

        পক্ষ B_চাবি_UP:
        পক্ষ B_UNMAPPED_চাবি_UP: // modifier keys are unmapped
            যদি (বাৰ্তা->FindInt32("key", &চাবি) == B_OK) {
                চাবি_Event_2(চাবি, রিক্ত, 0, false);
            }
            ভঙ্গ;

        স্ৱভাৱ:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            ভঙ্গ;
        }

        BWindow::DispatchMessage(বাৰ্তা, target);
    }

    // Handle command messages
    শূন্য MessageReceived(BMessage *message)
    {
        ৱিকল্প (message->what) {
        // Handle commands from SDL
        পক্ষ BWIN_SET_TITLE:
            _SetTitle(message);
            ভঙ্গ;
        পক্ষ BWIN_MOVE_WINDOW:
            _MoveTo(message);
            ভঙ্গ;
        পক্ষ BWIN_RESIZE_WINDOW:
            _ResizeTo(message);
            ভঙ্গ;
        পক্ষ BWIN_SET_BORDERED:
        {
            bool bEnabled;
            যদি (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            ভঙ্গ;
        }
        পক্ষ BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            যদি (message->FindBool("window-resizable", &bEnabled) == B_OK)
                _SetResizable(bEnabled);
            ভঙ্গ;
        }
        পক্ষ BWIN_SHOW_WINDOW:
            Show();
            ভঙ্গ;
        পক্ষ BWIN_HIDE_WINDOW:
            Hide();
            ভঙ্গ;
        পক্ষ BWIN_MAXIMIZE_WINDOW:
            BWindow::Zoom();
            ভঙ্গ;
        পক্ষ BWIN_MINIMIZE_WINDOW:
            Minimize(true);
            ভঙ্গ;
        পক্ষ BWIN_RESTORE_WINDOW:
            _Restore();
            ভঙ্গ;
        পক্ষ BWIN_FULLSCREEN:
        {
            bool fullscreen;
            যদি (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            ভঙ্গ;
        }
        পক্ষ BWIN_MINIMUM_SIZE_WINDOW:
            _SetMinimumSize(message);
            ভঙ্গ;
        পক্ষ BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            যেতিয়ালৈ ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            যদি (_bitmap != রিক্ত) {
#ifdef SDL_VIDEO_OPENGL
                যদি (_SDL_GLView != রিক্ত && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } অন্যথা
#endif
                যদি (_SDL_View != রিক্ত && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            ভঙ্গ;
        }
        স্ৱভাৱ:
            // Perform normal message handling
            BWindow::MessageReceived(message);
            ভঙ্গ;
        }
    }

    // Accessor methods
    bool IsShown() { ঘূৰাই _shown; }
    int32 GetID() { ঘূৰাই _id; }
    BBitmap *GetBitmap() { ঘূৰাই _bitmap; }
    BView *GetCurView() { ঘূৰাই _cur_view; }
    SDL_BView *GetView() { ঘূৰাই _SDL_View; }
#ifdef SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        ঘূৰাই _SDL_GLView;
    }
    Uint32 GetGLType() { ঘূৰাই _gl_type; }
#endif

    // Setter methods
    শূন্য SetID(int32 id) { _id = id; }
    শূন্য LockBuffer() { _buffer_locker->Lock(); }
    শূন্য UnlockBuffer() { _buffer_locker->Unlock(); }
    শূন্য SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        যদি (_SDL_View != রিক্ত)
            _SDL_View->SetBitmap(bitmap);
    }

  গুপ্ত:
    // Event redirection
    শূন্য _MouseMotionEvent(BPoint &where, int32 transit)
    {
        যদি (transit == B_EXITED_VIEW) {
            // Change mouse focus
            যদি (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } অন্যথা {
            // Change mouse focus
            যদি (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage বাৰ্তা(BAPP_MOUSE_MOVED);
            বাৰ্তা.AddInt32("x", (পূর্ণাঙ্ক)where.x);
            বাৰ্তা.AddInt32("y", (পূর্ণাঙ্ক)where.y);

            _PostWindowEvent(বাৰ্তা);
        }
    }

    শূন্য _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage বাৰ্তা(BAPP_MOUSE_FOCUS);
        বাৰ্তা.AddBool("focusGained", focusGained);
        _PostWindowEvent(বাৰ্তা);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    শূন্য _MouseButtonEvent(int32 buttons, bool down)
    {
        int32 buttonStateChange = buttons ^ _last_buttons;

        যদি (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_বাম, down);
        }
        যদি (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ডান, down);
        }
        যদি (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_মধ্য, down);
        }

        _last_buttons = buttons;
    }

    শূন্য _SendMouseButton(int32 button, bool down)
    {
        BMessage বাৰ্তা(BAPP_MOUSE_BUTTON);
        বাৰ্তা.AddInt32("button-id", button);
        বাৰ্তা.AddBool("button-down", down);
        _PostWindowEvent(বাৰ্তা);
    }

    শূন্য _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage বাৰ্তা(BAPP_MOUSE_WHEEL);
        বাৰ্তা.AddInt32("xticks", x);
        বাৰ্তা.AddInt32("yticks", y);
        _PostWindowEvent(বাৰ্তা);
    }

    শূন্য চাবি_Event_2(int32 চাবি_Code, ধ্রুৱ int8 *চাবি_Utf8, ধ্রুৱ ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage বাৰ্তা(BAPP_চাবি);
        বাৰ্তা.AddInt32("key-scancode", চাবি_Code);
        যদি (চাবি_Utf8 != রিক্ত) {
            বাৰ্তা.AddData("key-utf8", B_INT8_TYPE, (ধ্রুৱ শূন্য *)চাবি_Utf8, len);
        }
        বাৰ্তা.AddBool("key-down", down);
        SDL_Looper->PostMessage(&বাৰ্তা);
    }

    শূন্য _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage বাৰ্তা(BAPP_REPAINT);
        _PostWindowEvent(বাৰ্তা);
    }
    শূন্য _PostWindowEvent(BMessage &বাৰ্তা)
    {
        বাৰ্তা.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&বাৰ্তা);
    }

    // Command methods (functions called upon by SDL)
    শূন্য _SetTitle(BMessage *বাৰ্তা)
    {
        ধ্রুৱ ৱর্ণ *title;
        যদি (
            বাৰ্তা->FindString("window-title", &title) != B_OK) {
            ঘূৰাই;
        }
        SetTitle(title);
    }

    শূন্য _MoveTo(BMessage *বাৰ্তা)
    {
        int32 x, y;
        যদি (
            বাৰ্তা->FindInt32("window-x", &x) != B_OK ||
            বাৰ্তা->FindInt32("window-y", &y) != B_OK) {
            ঘূৰাই;
        }
        যদি (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        অন্যথা
            MoveTo(x, y);
    }

    শূন্য _ResizeTo(BMessage *বাৰ্তা)
    {
        int32 w, h;
        যদি (
            বাৰ্তা->FindInt32("window-w", &w) != B_OK ||
            বাৰ্তা->FindInt32("window-h", &h) != B_OK) {
            ঘূৰাই;
        }
        যদি (_fullscreen) {
            _non_fullscreen_frame.ডান = _non_fullscreen_frame.বাম + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.শীৰ্ষ + h;
        } অন্যথা
            ResizeTo(w, h);
    }

    শূন্য _SetBordered(bool bEnabled)
    {
        যদি (_fullscreen)
            _bordered = bEnabled;
        অন্যথা
            SetLook(bEnabled ? B_TITLED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
    }

    শূন্য _SetResizable(bool bEnabled)
    {
        যদি (_fullscreen)
            _resizable = bEnabled;
        অন্যথা {
            যদি (bEnabled) {
                SetFlags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } অন্যথা {
                SetFlags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    শূন্য _SetMinimumSize(BMessage *বাৰ্তা)
    {
        ভিন্ন maxHeight;
        ভিন্ন maxWidth;
        ভিন্ন _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        GetSizeLimits(&_, &maxWidth, &_, &maxHeight);
        যদি (বাৰ্তা->FindInt32("window-w", &minWidth) != B_OK)
            ঘূৰাই;
        যদি (বাৰ্তা->FindInt32("window-h", &minHeight) != B_OK)
            ঘূৰাই;
        SetSizeLimits((ভিন্ন)minWidth, maxWidth, (ভিন্ন)minHeight, maxHeight);
        UpdateSizeLimits();
    }

    শূন্য _Restore()
    {
        যদি (IsMinimized()) {
            Minimize(false);
        } অন্যথা যদি (IsHidden()) {
            Show();
        } অন্যথা যদি (_fullscreen) {

        } অন্যথা যদি (_prev_frame != রিক্ত) { // Zoomed
            MoveTo(_prev_frame->বাম, _prev_frame->শীৰ্ষ);
            ResizeTo(_prev_frame->Width(), _prev_frame->Height());
        }
    }

    শূন্য _SetFullScreen(bool fullscreen)
    {
        যদি (fullscreen != _fullscreen) {
            যদি (fullscreen) {
                BScreen screen(this);
                BRect screenFrame = screen.Frame();
                _bordered = Look() != B_NO_BORDER_WINDOW_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                _non_fullscreen_frame = Frame();
                _SetBordered(false);
                _SetResizable(false);
                MoveTo(screenFrame.বাম, screenFrame.শীৰ্ষ);
                ResizeTo(screenFrame.Width(), screenFrame.Height());
                _fullscreen = fullscreen;
            } অন্যথা {
                _fullscreen = fullscreen;
                MoveTo(_non_fullscreen_frame.বাম, _non_fullscreen_frame.শীৰ্ষ);
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
