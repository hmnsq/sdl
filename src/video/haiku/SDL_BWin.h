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
خارجي "C" {
#endif

#ضمن "SDL_internal.h"
#ضمن "SDL_bframebuffer.h"

#ifdef __cplusplus
}
#endif

#ضمن <stdio.h>
#ضمن <AppKit.h>
#ضمن <Cursor.h>
#ضمن <InterfaceKit.h>
#ifdef SDL_VIDEO_OPENGL
#ضمن <opengl/GLView.h>
#endif
#ضمن "../../core/haiku/SDL_BApp.h"

تعداد WinCommands
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
class SDL_BView : عام BView
{
  عام:
    SDL_BView(BRect frame, ثابت حرف *name, uint32 resizingMode)
        : BView(frame, name, resizingMode, B_WILL_DRAW),
          fBitmap(عدم)
    {
    }

    فراغ Draw(BRect dirty)
    {
        إذا (fBitmap != عدم)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    فراغ SetBitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  خاص:
    BBitmap *fBitmap;
};

class SDL_BWin : عام BWindow
{
  عام:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, window_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_NORMAL_WINDOW_FEEL, flags)
    {
        _last_buttons = 0;

        _cur_view = عدم;
        _SDL_View = عدم;

#ifdef SDL_VIDEO_OPENGL
        _SDL_GLView = عدم;
        _gl_type = 0;
#endif
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        _prev_frame = عدم;
        _fullscreen = عدم;

        // Handle framebuffer stuff
        _buffer_locker = new BLocker();
        _bitmap = عدم;
    }

    virtual ~SDL_BWin()
    {
        Lock();

        إذا (_SDL_View != عدم && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = عدم;
        }

#ifdef SDL_VIDEO_OPENGL
        إذا (_SDL_GLView) {
            إذا (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(عدم);
            إذا (_SDL_GLView == _cur_view)
                RemoveChild(_SDL_GLView);
            _SDL_GLView = عدم;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#endif
        Unlock();

        delete _prev_frame;

        // Clean up framebuffer stuff
        _buffer_locker->Lock();
        delete _buffer_locker;
    }

    فراغ SetCurrentView(BView *view)
    {
        إذا (_cur_view != view) {
            إذا (_cur_view != عدم)
                RemoveChild(_cur_view);
            _cur_view = view;
            إذا (_cur_view != عدم)
                AddChild(_cur_view);
        }
    }

    فراغ UpdateCurrentView()
    {
#ifdef SDL_VIDEO_OPENGL
        إذا (_SDL_GLView != عدم) {
            SetCurrentView(_SDL_GLView);
        } وإلا
#endif
        إذا (_SDL_View != عدم) {
            SetCurrentView(_SDL_View);
        } وإلا {
            SetCurrentView(عدم);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        إذا (_SDL_View == عدم) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        إرجاع _SDL_View;
    }

    فراغ RemoveView()
    {
        Lock();
        إذا (_SDL_View != عدم) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = عدم;
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
        إذا (_SDL_GLView == عدم) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        إرجاع _SDL_GLView;
    }

    فراغ RemoveGLView()
    {
        Lock();
        إذا (_SDL_GLView != عدم) {
            إذا (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(عدم);
            _SDL_GLView = عدم;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    فراغ SwapBuffers(فراغ)
    {
        _SDL_GLView->SwapBuffers();
    }
#endif

    /* * * * * Event sending * * * * */
    // Hook functions
    virtual فراغ FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage رسالة(BAPP_WINDOW_MOVED);
        رسالة.AddInt32("window-x", (صحيح)origin.x);
        رسالة.AddInt32("window-y", (صحيح)origin.y);
        _PostWindowEvent(رسالة);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    فراغ FrameResized(عائم width, عائم height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage رسالة(BAPP_WINDOW_RESIZED);

        رسالة.AddInt32("window-w", (صحيح)width + 1);
        رسالة.AddInt32("window-h", (صحيح)height + 1);
        _PostWindowEvent(رسالة);

        // Perform normal hook operations
        BWindow::FrameResized(width, height);
    }

    bool QuitRequested()
    {
        BMessage رسالة(BAPP_WINDOW_CLOSE_REQUESTED);
        _PostWindowEvent(رسالة);

        // We won't allow a quit unless asked by DestroyWindow()
        إرجاع false;
    }

    فراغ WindowActivated(bool active)
    {
        BMessage رسالة(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        رسالة.AddBool("focusGained", active);
        _PostWindowEvent(رسالة);
    }

    فراغ Zoom(BPoint origin,
              عائم width,
              عائم height)
    {
        BMessage رسالة(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(رسالة);

        // Before the window zooms, record its size
        إذا (!_prev_frame)
            _prev_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    فراغ Show()
    {
        بينما (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage رسالة(BAPP_SHOW);
        _PostWindowEvent(رسالة);
    }

    فراغ Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage رسالة(BAPP_HIDE);
        _PostWindowEvent(رسالة);
    }

    فراغ Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage رسالة(minState);
        _PostWindowEvent(رسالة);
    }

    فراغ ScreenChanged(BRect screenFrame, color_space depth)
    {
        إذا (_fullscreen) {
            MoveTo(screenFrame.يسار, screenFrame.قمة);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    فراغ DispatchMessage(BMessage *رسالة, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 مفتاح;     // Used for key events

        بدل (رسالة->what) {
        حالة B_MOUSE_MOVED:
            int32 transit;
            إذا (رسالة->FindPoint("where", &where) == B_OK && رسالة->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            اكسر;

        حالة B_MOUSE_DOWN:
            إذا (رسالة->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            اكسر;

        حالة B_MOUSE_UP:
            إذا (رسالة->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            اكسر;

        حالة B_MOUSE_WHEEL_CHANGED:
            عائم x, y;
            إذا (رسالة->FindFloat("be:wheel_delta_x", &x) == B_OK && رسالة->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((صحيح)x, (صحيح)y);
            }
            اكسر;

        حالة B_مفتاح_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            بينما (i < 4 && رسالة->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            إذا (رسالة->FindInt32("key", &مفتاح) == B_OK) {
                مفتاح_Event_2((SDL_Scancode)مفتاح, &bytes[0], i, true);
            }
        } اكسر;

        حالة B_UNMAPPED_مفتاح_DOWN: // modifier keys are unmapped
            إذا (رسالة->FindInt32("key", &مفتاح) == B_OK) {
                مفتاح_Event_2((SDL_Scancode)مفتاح, عدم, 0, true);
            }
            اكسر;

        حالة B_مفتاح_UP:
        حالة B_UNMAPPED_مفتاح_UP: // modifier keys are unmapped
            إذا (رسالة->FindInt32("key", &مفتاح) == B_OK) {
                مفتاح_Event_2(مفتاح, عدم, 0, false);
            }
            اكسر;

        افتراضي:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            اكسر;
        }

        BWindow::DispatchMessage(رسالة, target);
    }

    // Handle command messages
    فراغ MessageReceived(BMessage *message)
    {
        بدل (message->what) {
        // Handle commands from SDL
        حالة BWIN_SET_TITLE:
            _SetTitle(message);
            اكسر;
        حالة BWIN_MOVE_WINDOW:
            _MoveTo(message);
            اكسر;
        حالة BWIN_RESIZE_WINDOW:
            _ResizeTo(message);
            اكسر;
        حالة BWIN_SET_BORDERED:
        {
            bool bEnabled;
            إذا (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            اكسر;
        }
        حالة BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            إذا (message->FindBool("window-resizable", &bEnabled) == B_OK)
                _SetResizable(bEnabled);
            اكسر;
        }
        حالة BWIN_SHOW_WINDOW:
            Show();
            اكسر;
        حالة BWIN_HIDE_WINDOW:
            Hide();
            اكسر;
        حالة BWIN_MAXIMIZE_WINDOW:
            BWindow::Zoom();
            اكسر;
        حالة BWIN_MINIMIZE_WINDOW:
            Minimize(true);
            اكسر;
        حالة BWIN_RESTORE_WINDOW:
            _Restore();
            اكسر;
        حالة BWIN_FULLSCREEN:
        {
            bool fullscreen;
            إذا (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            اكسر;
        }
        حالة BWIN_MINIMUM_SIZE_WINDOW:
            _SetMinimumSize(message);
            اكسر;
        حالة BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            بينما ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            إذا (_bitmap != عدم) {
#ifdef SDL_VIDEO_OPENGL
                إذا (_SDL_GLView != عدم && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } وإلا
#endif
                إذا (_SDL_View != عدم && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            اكسر;
        }
        افتراضي:
            // Perform normal message handling
            BWindow::MessageReceived(message);
            اكسر;
        }
    }

    // Accessor methods
    bool IsShown() { إرجاع _shown; }
    int32 GetID() { إرجاع _id; }
    BBitmap *GetBitmap() { إرجاع _bitmap; }
    BView *GetCurView() { إرجاع _cur_view; }
    SDL_BView *GetView() { إرجاع _SDL_View; }
#ifdef SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        إرجاع _SDL_GLView;
    }
    Uint32 GetGLType() { إرجاع _gl_type; }
#endif

    // Setter methods
    فراغ SetID(int32 id) { _id = id; }
    فراغ LockBuffer() { _buffer_locker->Lock(); }
    فراغ UnlockBuffer() { _buffer_locker->Unlock(); }
    فراغ SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        إذا (_SDL_View != عدم)
            _SDL_View->SetBitmap(bitmap);
    }

  خاص:
    // Event redirection
    فراغ _MouseMotionEvent(BPoint &where, int32 transit)
    {
        إذا (transit == B_EXITED_VIEW) {
            // Change mouse focus
            إذا (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } وإلا {
            // Change mouse focus
            إذا (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage رسالة(BAPP_MOUSE_MOVED);
            رسالة.AddInt32("x", (صحيح)where.x);
            رسالة.AddInt32("y", (صحيح)where.y);

            _PostWindowEvent(رسالة);
        }
    }

    فراغ _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage رسالة(BAPP_MOUSE_FOCUS);
        رسالة.AddBool("focusGained", focusGained);
        _PostWindowEvent(رسالة);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    فراغ _MouseButtonEvent(int32 buttons, bool down)
    {
        int32 buttonStateChange = buttons ^ _last_buttons;

        إذا (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_يسار, down);
        }
        إذا (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_يمين, down);
        }
        إذا (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_وسط, down);
        }

        _last_buttons = buttons;
    }

    فراغ _SendMouseButton(int32 button, bool down)
    {
        BMessage رسالة(BAPP_MOUSE_BUTTON);
        رسالة.AddInt32("button-id", button);
        رسالة.AddBool("button-down", down);
        _PostWindowEvent(رسالة);
    }

    فراغ _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage رسالة(BAPP_MOUSE_WHEEL);
        رسالة.AddInt32("xticks", x);
        رسالة.AddInt32("yticks", y);
        _PostWindowEvent(رسالة);
    }

    فراغ مفتاح_Event_2(int32 مفتاح_Code, ثابت int8 *مفتاح_Utf8, ثابت ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage رسالة(BAPP_مفتاح);
        رسالة.AddInt32("key-scancode", مفتاح_Code);
        إذا (مفتاح_Utf8 != عدم) {
            رسالة.AddData("key-utf8", B_INT8_TYPE, (ثابت فراغ *)مفتاح_Utf8, len);
        }
        رسالة.AddBool("key-down", down);
        SDL_Looper->PostMessage(&رسالة);
    }

    فراغ _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage رسالة(BAPP_REPAINT);
        _PostWindowEvent(رسالة);
    }
    فراغ _PostWindowEvent(BMessage &رسالة)
    {
        رسالة.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&رسالة);
    }

    // Command methods (functions called upon by SDL)
    فراغ _SetTitle(BMessage *رسالة)
    {
        ثابت حرف *title;
        إذا (
            رسالة->FindString("window-title", &title) != B_OK) {
            إرجاع;
        }
        SetTitle(title);
    }

    فراغ _MoveTo(BMessage *رسالة)
    {
        int32 x, y;
        إذا (
            رسالة->FindInt32("window-x", &x) != B_OK ||
            رسالة->FindInt32("window-y", &y) != B_OK) {
            إرجاع;
        }
        إذا (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        وإلا
            MoveTo(x, y);
    }

    فراغ _ResizeTo(BMessage *رسالة)
    {
        int32 w, h;
        إذا (
            رسالة->FindInt32("window-w", &w) != B_OK ||
            رسالة->FindInt32("window-h", &h) != B_OK) {
            إرجاع;
        }
        إذا (_fullscreen) {
            _non_fullscreen_frame.يمين = _non_fullscreen_frame.يسار + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.قمة + h;
        } وإلا
            ResizeTo(w, h);
    }

    فراغ _SetBordered(bool bEnabled)
    {
        إذا (_fullscreen)
            _bordered = bEnabled;
        وإلا
            SetLook(bEnabled ? B_TITLED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
    }

    فراغ _SetResizable(bool bEnabled)
    {
        إذا (_fullscreen)
            _resizable = bEnabled;
        وإلا {
            إذا (bEnabled) {
                SetFlags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } وإلا {
                SetFlags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    فراغ _SetMinimumSize(BMessage *رسالة)
    {
        عائم maxHeight;
        عائم maxWidth;
        عائم _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        GetSizeLimits(&_, &maxWidth, &_, &maxHeight);
        إذا (رسالة->FindInt32("window-w", &minWidth) != B_OK)
            إرجاع;
        إذا (رسالة->FindInt32("window-h", &minHeight) != B_OK)
            إرجاع;
        SetSizeLimits((عائم)minWidth, maxWidth, (عائم)minHeight, maxHeight);
        UpdateSizeLimits();
    }

    فراغ _Restore()
    {
        إذا (IsMinimized()) {
            Minimize(false);
        } وإلا إذا (IsHidden()) {
            Show();
        } وإلا إذا (_fullscreen) {

        } وإلا إذا (_prev_frame != عدم) { // Zoomed
            MoveTo(_prev_frame->يسار, _prev_frame->قمة);
            ResizeTo(_prev_frame->Width(), _prev_frame->Height());
        }
    }

    فراغ _SetFullScreen(bool fullscreen)
    {
        إذا (fullscreen != _fullscreen) {
            إذا (fullscreen) {
                BScreen screen(this);
                BRect screenFrame = screen.Frame();
                _bordered = Look() != B_NO_BORDER_WINDOW_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                _non_fullscreen_frame = Frame();
                _SetBordered(false);
                _SetResizable(false);
                MoveTo(screenFrame.يسار, screenFrame.قمة);
                ResizeTo(screenFrame.Width(), screenFrame.Height());
                _fullscreen = fullscreen;
            } وإلا {
                _fullscreen = fullscreen;
                MoveTo(_non_fullscreen_frame.يسار, _non_fullscreen_frame.قمة);
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
