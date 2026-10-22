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
        𐤀𐤌 (fBitmap != عدم)
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

        𐤀𐤌 (_SDL_View != عدم && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = عدم;
        }

#ifdef SDL_VIDEO_OPENGL
        𐤀𐤌 (_SDL_GLView) {
            𐤀𐤌 (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(عدم);
            𐤀𐤌 (_SDL_GLView == _cur_view)
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
        𐤀𐤌 (_cur_view != view) {
            𐤀𐤌 (_cur_view != عدم)
                RemoveChild(_cur_view);
            _cur_view = view;
            𐤀𐤌 (_cur_view != عدم)
                AddChild(_cur_view);
        }
    }

    فراغ UpdateCurrentView()
    {
#ifdef SDL_VIDEO_OPENGL
        𐤀𐤌 (_SDL_GLView != عدم) {
            SetCurrentView(_SDL_GLView);
        } وإلا
#endif
        𐤀𐤌 (_SDL_View != عدم) {
            SetCurrentView(_SDL_View);
        } وإلا {
            SetCurrentView(عدم);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        𐤀𐤌 (_SDL_View == عدم) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        أرجع _SDL_View;
    }

    فراغ RemoveView()
    {
        Lock();
        𐤀𐤌 (_SDL_View != عدم) {
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
        𐤀𐤌 (_SDL_GLView == عدم) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        أرجع _SDL_GLView;
    }

    فراغ RemoveGLView()
    {
        Lock();
        𐤀𐤌 (_SDL_GLView != عدم) {
            𐤀𐤌 (SDL_Looper->GetCurrentContext() == _SDL_GLView)
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
        BMessage msg(BAPP_WINDOW_MOVED);
        msg.AddInt32("window-x", (صحيح)origin.x);
        msg.AddInt32("window-y", (صحيح)origin.y);
        _PostWindowEvent(msg);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    فراغ FrameResized(عائم width, عائم height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage msg(BAPP_WINDOW_RESIZED);

        msg.AddInt32("window-w", (صحيح)width + 1);
        msg.AddInt32("window-h", (صحيح)height + 1);
        _PostWindowEvent(msg);

        // Perform normal hook operations
        BWindow::FrameResized(width, height);
    }

    bool QuitRequested()
    {
        BMessage msg(BAPP_WINDOW_CLOSE_REQUESTED);
        _PostWindowEvent(msg);

        // We won't allow a quit unless asked by DestroyWindow()
        أرجع false;
    }

    فراغ WindowActivated(bool active)
    {
        BMessage msg(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        msg.AddBool("focusGained", active);
        _PostWindowEvent(msg);
    }

    فراغ Zoom(BPoint origin,
              عائم width,
              عائم height)
    {
        BMessage msg(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(msg);

        // Before the window zooms, record its size
        𐤀𐤌 (!_prev_frame)
            _prev_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    فراغ Show()
    {
        طالما (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage msg(BAPP_SHOW);
        _PostWindowEvent(msg);
    }

    فراغ Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage msg(BAPP_HIDE);
        _PostWindowEvent(msg);
    }

    فراغ Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage msg(minState);
        _PostWindowEvent(msg);
    }

    فراغ ScreenChanged(BRect screenFrame, color_space depth)
    {
        𐤀𐤌 (_fullscreen) {
            MoveTo(screenFrame.left, screenFrame.top);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    فراغ DispatchMessage(BMessage *msg, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 key;     // Used for key events

        بدل (msg->what) {
        حالة B_MOUSE_MOVED:
            int32 transit;
            𐤀𐤌 (msg->FindPoint("where", &where) == B_OK && msg->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            اكسر;

        حالة B_MOUSE_DOWN:
            𐤀𐤌 (msg->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            اكسر;

        حالة B_MOUSE_UP:
            𐤀𐤌 (msg->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            اكسر;

        حالة B_MOUSE_WHEEL_CHANGED:
            عائم x, y;
            𐤀𐤌 (msg->FindFloat("be:wheel_delta_x", &x) == B_OK && msg->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((صحيح)x, (صحيح)y);
            }
            اكسر;

        حالة B_KEY_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            طالما (i < 4 && msg->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            𐤀𐤌 (msg->FindInt32("key", &key) == B_OK) {
                _KeyEvent((SDL_Scancode)key, &bytes[0], i, true);
            }
        } اكسر;

        حالة B_UNMAPPED_KEY_DOWN: // modifier keys are unmapped
            𐤀𐤌 (msg->FindInt32("key", &key) == B_OK) {
                _KeyEvent((SDL_Scancode)key, عدم, 0, true);
            }
            اكسر;

        حالة B_KEY_UP:
        حالة B_UNMAPPED_KEY_UP: // modifier keys are unmapped
            𐤀𐤌 (msg->FindInt32("key", &key) == B_OK) {
                _KeyEvent(key, عدم, 0, false);
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

        BWindow::DispatchMessage(msg, target);
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
            𐤀𐤌 (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            اكسر;
        }
        حالة BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            𐤀𐤌 (message->FindBool("window-resizable", &bEnabled) == B_OK)
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
            𐤀𐤌 (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            اكسر;
        }
        حالة BWIN_MINIMUM_SIZE_WINDOW:
            _SetMinimumSize(message);
            اكسر;
        حالة BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            طالما ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            𐤀𐤌 (_bitmap != عدم) {
#ifdef SDL_VIDEO_OPENGL
                𐤀𐤌 (_SDL_GLView != عدم && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } وإلا
#endif
                𐤀𐤌 (_SDL_View != عدم && _cur_view == _SDL_View) {
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
    bool IsShown() { أرجع _shown; }
    int32 GetID() { أرجع _id; }
    BBitmap *GetBitmap() { أرجع _bitmap; }
    BView *GetCurView() { أرجع _cur_view; }
    SDL_BView *GetView() { أرجع _SDL_View; }
#ifdef SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        أرجع _SDL_GLView;
    }
    Uint32 GetGLType() { أرجع _gl_type; }
#endif

    // Setter methods
    فراغ SetID(int32 id) { _id = id; }
    فراغ LockBuffer() { _buffer_locker->Lock(); }
    فراغ UnlockBuffer() { _buffer_locker->Unlock(); }
    فراغ SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        𐤀𐤌 (_SDL_View != عدم)
            _SDL_View->SetBitmap(bitmap);
    }

  خاص:
    // Event redirection
    فراغ _MouseMotionEvent(BPoint &where, int32 transit)
    {
        𐤀𐤌 (transit == B_EXITED_VIEW) {
            // Change mouse focus
            𐤀𐤌 (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } وإلا {
            // Change mouse focus
            𐤀𐤌 (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage msg(BAPP_MOUSE_MOVED);
            msg.AddInt32("x", (صحيح)where.x);
            msg.AddInt32("y", (صحيح)where.y);

            _PostWindowEvent(msg);
        }
    }

    فراغ _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage msg(BAPP_MOUSE_FOCUS);
        msg.AddBool("focusGained", focusGained);
        _PostWindowEvent(msg);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    فراغ _MouseButtonEvent(int32 buttons, bool down)
    {
        int32 buttonStateChange = buttons ^ _last_buttons;

        𐤀𐤌 (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_LEFT, down);
        }
        𐤀𐤌 (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_RIGHT, down);
        }
        𐤀𐤌 (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_MIDDLE, down);
        }

        _last_buttons = buttons;
    }

    فراغ _SendMouseButton(int32 button, bool down)
    {
        BMessage msg(BAPP_MOUSE_BUTTON);
        msg.AddInt32("button-id", button);
        msg.AddBool("button-down", down);
        _PostWindowEvent(msg);
    }

    فراغ _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage msg(BAPP_MOUSE_WHEEL);
        msg.AddInt32("xticks", x);
        msg.AddInt32("yticks", y);
        _PostWindowEvent(msg);
    }

    فراغ _KeyEvent(int32 keyCode, ثابت int8 *keyUtf8, ثابت ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage msg(BAPP_KEY);
        msg.AddInt32("key-scancode", keyCode);
        𐤀𐤌 (keyUtf8 != عدم) {
            msg.AddData("key-utf8", B_INT8_TYPE, (ثابت فراغ *)keyUtf8, len);
        }
        msg.AddBool("key-down", down);
        SDL_Looper->PostMessage(&msg);
    }

    فراغ _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage msg(BAPP_REPAINT);
        _PostWindowEvent(msg);
    }
    فراغ _PostWindowEvent(BMessage &msg)
    {
        msg.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&msg);
    }

    // Command methods (functions called upon by SDL)
    فراغ _SetTitle(BMessage *msg)
    {
        ثابت حرف *title;
        𐤀𐤌 (
            msg->FindString("window-title", &title) != B_OK) {
            أرجع;
        }
        SetTitle(title);
    }

    فراغ _MoveTo(BMessage *msg)
    {
        int32 x, y;
        𐤀𐤌 (
            msg->FindInt32("window-x", &x) != B_OK ||
            msg->FindInt32("window-y", &y) != B_OK) {
            أرجع;
        }
        𐤀𐤌 (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        وإلا
            MoveTo(x, y);
    }

    فراغ _ResizeTo(BMessage *msg)
    {
        int32 w, h;
        𐤀𐤌 (
            msg->FindInt32("window-w", &w) != B_OK ||
            msg->FindInt32("window-h", &h) != B_OK) {
            أرجع;
        }
        𐤀𐤌 (_fullscreen) {
            _non_fullscreen_frame.right = _non_fullscreen_frame.left + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.top + h;
        } وإلا
            ResizeTo(w, h);
    }

    فراغ _SetBordered(bool bEnabled)
    {
        𐤀𐤌 (_fullscreen)
            _bordered = bEnabled;
        وإلا
            SetLook(bEnabled ? B_TITLED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
    }

    فراغ _SetResizable(bool bEnabled)
    {
        𐤀𐤌 (_fullscreen)
            _resizable = bEnabled;
        وإلا {
            𐤀𐤌 (bEnabled) {
                SetFlags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } وإلا {
                SetFlags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    فراغ _SetMinimumSize(BMessage *msg)
    {
        عائم maxHeight;
        عائم maxWidth;
        عائم _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        GetSizeLimits(&_, &maxWidth, &_, &maxHeight);
        𐤀𐤌 (msg->FindInt32("window-w", &minWidth) != B_OK)
            أرجع;
        𐤀𐤌 (msg->FindInt32("window-h", &minHeight) != B_OK)
            أرجع;
        SetSizeLimits((عائم)minWidth, maxWidth, (عائم)minHeight, maxHeight);
        UpdateSizeLimits();
    }

    فراغ _Restore()
    {
        𐤀𐤌 (IsMinimized()) {
            Minimize(false);
        } وإلا 𐤀𐤌 (IsHidden()) {
            Show();
        } وإلا 𐤀𐤌 (_fullscreen) {

        } وإلا 𐤀𐤌 (_prev_frame != عدم) { // Zoomed
            MoveTo(_prev_frame->left, _prev_frame->top);
            ResizeTo(_prev_frame->Width(), _prev_frame->Height());
        }
    }

    فراغ _SetFullScreen(bool fullscreen)
    {
        𐤀𐤌 (fullscreen != _fullscreen) {
            𐤀𐤌 (fullscreen) {
                BScreen screen(this);
                BRect screenFrame = screen.Frame();
                _bordered = Look() != B_NO_BORDER_WINDOW_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                _non_fullscreen_frame = Frame();
                _SetBordered(false);
                _SetResizable(false);
                MoveTo(screenFrame.left, screenFrame.top);
                ResizeTo(screenFrame.Width(), screenFrame.Height());
                _fullscreen = fullscreen;
            } وإلا {
                _fullscreen = fullscreen;
                MoveTo(_non_fullscreen_frame.left, _non_fullscreen_frame.top);
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
