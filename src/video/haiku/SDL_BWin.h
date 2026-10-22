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
بیرونی "C" {
#endif

#شامل "SDL_internal.h"
#شامل "SDL_bframebuffer.h"

#ifdef __cplusplus
}
#endif

#شامل <stdio.h>
#شامل <AppKit.h>
#شامل <Cursor.h>
#شامل <InterfaceKit.h>
#ifdef SDL_VIDEO_OPENGL
#شامل <opengl/GLView.h>
#endif
#شامل "../../core/haiku/SDL_BApp.h"

شمارش WinCommands
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
class SDL_BView : عمومی BView
{
  عمومی:
    SDL_BView(BRect frame, ثابت نویسه *name, uint32 resizingMode)
        : BView(frame, name, resizingMode, B_WILL_DRAW),
          fBitmap(پوچ)
    {
    }

    تهی Draw(BRect dirty)
    {
        اگر (fBitmap != پوچ)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    تهی SetBitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  خصوصی:
    BBitmap *fBitmap;
};

class SDL_BWin : عمومی BWindow
{
  عمومی:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, window_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_NORMAL_WINDOW_FEEL, flags)
    {
        _last_buttons = 0;

        _cur_view = پوچ;
        _SDL_View = پوچ;

#ifdef SDL_VIDEO_OPENGL
        _SDL_GLView = پوچ;
        _gl_type = 0;
#endif
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        _prev_frame = پوچ;
        _fullscreen = پوچ;

        // Handle framebuffer stuff
        _buffer_locker = new BLocker();
        _bitmap = پوچ;
    }

    مجازی ~SDL_BWin()
    {
        Lock();

        اگر (_SDL_View != پوچ && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = پوچ;
        }

#ifdef SDL_VIDEO_OPENGL
        اگر (_SDL_GLView) {
            اگر (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(پوچ);
            اگر (_SDL_GLView == _cur_view)
                RemoveChild(_SDL_GLView);
            _SDL_GLView = پوچ;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#endif
        Unlock();

        delete _prev_frame;

        // Clean up framebuffer stuff
        _buffer_locker->Lock();
        delete _buffer_locker;
    }

    تهی SetCurrentView(BView *view)
    {
        اگر (_cur_view != view) {
            اگر (_cur_view != پوچ)
                RemoveChild(_cur_view);
            _cur_view = view;
            اگر (_cur_view != پوچ)
                AddChild(_cur_view);
        }
    }

    تهی UpdateCurrentView()
    {
#ifdef SDL_VIDEO_OPENGL
        اگر (_SDL_GLView != پوچ) {
            SetCurrentView(_SDL_GLView);
        } وگرنه
#endif
        اگر (_SDL_View != پوچ) {
            SetCurrentView(_SDL_View);
        } وگرنه {
            SetCurrentView(پوچ);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        اگر (_SDL_View == پوچ) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        بازگشت _SDL_View;
    }

    تهی RemoveView()
    {
        Lock();
        اگر (_SDL_View != پوچ) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = پوچ;
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
        اگر (_SDL_GLView == پوچ) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        بازگشت _SDL_GLView;
    }

    تهی RemoveGLView()
    {
        Lock();
        اگر (_SDL_GLView != پوچ) {
            اگر (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(پوچ);
            _SDL_GLView = پوچ;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    تهی SwapBuffers(تهی)
    {
        _SDL_GLView->SwapBuffers();
    }
#endif

    /* * * * * Event sending * * * * */
    // Hook functions
    مجازی تهی FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage پیام(BAPP_WINDOW_MOVED);
        پیام.AddInt32("window-x", (صحیح)origin.x);
        پیام.AddInt32("window-y", (صحیح)origin.y);
        _PostWindowEvent(پیام);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    تهی FrameResized(اعشاری width, اعشاری height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage پیام(BAPP_WINDOW_RESIZED);

        پیام.AddInt32("window-w", (صحیح)width + 1);
        پیام.AddInt32("window-h", (صحیح)height + 1);
        _PostWindowEvent(پیام);

        // Perform normal hook operations
        BWindow::FrameResized(width, height);
    }

    bool QuitRequested()
    {
        BMessage پیام(BAPP_WINDOW_CLOSE_REQUESTED);
        _PostWindowEvent(پیام);

        // We won't allow a quit unless asked by DestroyWindow()
        بازگشت false;
    }

    تهی WindowActivated(bool active)
    {
        BMessage پیام(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        پیام.AddBool("focusGained", active);
        _PostWindowEvent(پیام);
    }

    تهی Zoom(BPoint origin,
              اعشاری width,
              اعشاری height)
    {
        BMessage پیام(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(پیام);

        // Before the window zooms, record its size
        اگر (!_prev_frame)
            _prev_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    تهی Show()
    {
        وقتی (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage پیام(BAPP_SHOW);
        _PostWindowEvent(پیام);
    }

    تهی Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage پیام(BAPP_HIDE);
        _PostWindowEvent(پیام);
    }

    تهی Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage پیام(minState);
        _PostWindowEvent(پیام);
    }

    تهی ScreenChanged(BRect screenFrame, color_space depth)
    {
        اگر (_fullscreen) {
            MoveTo(screenFrame.چپ, screenFrame.بالاترین);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    تهی DispatchMessage(BMessage *پیام, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 کلید;     // Used for key events

        انتخاب (پیام->what) {
        حالت B_MOUSE_MOVED:
            int32 transit;
            اگر (پیام->FindPoint("where", &where) == B_OK && پیام->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            بشکن;

        حالت B_MOUSE_DOWN:
            اگر (پیام->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            بشکن;

        حالت B_MOUSE_UP:
            اگر (پیام->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            بشکن;

        حالت B_MOUSE_WHEEL_CHANGED:
            اعشاری x, y;
            اگر (پیام->FindFloat("be:wheel_delta_x", &x) == B_OK && پیام->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((صحیح)x, (صحیح)y);
            }
            بشکن;

        حالت B_کلید_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            وقتی (i < 4 && پیام->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            اگر (پیام->FindInt32("key", &کلید) == B_OK) {
                کلید_Event_2((SDL_Scancode)کلید, &bytes[0], i, true);
            }
        } بشکن;

        حالت B_UNMAPPED_کلید_DOWN: // modifier keys are unmapped
            اگر (پیام->FindInt32("key", &کلید) == B_OK) {
                کلید_Event_2((SDL_Scancode)کلید, پوچ, 0, true);
            }
            بشکن;

        حالت B_کلید_UP:
        حالت B_UNMAPPED_کلید_UP: // modifier keys are unmapped
            اگر (پیام->FindInt32("key", &کلید) == B_OK) {
                کلید_Event_2(کلید, پوچ, 0, false);
            }
            بشکن;

        پیشفرض:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            بشکن;
        }

        BWindow::DispatchMessage(پیام, target);
    }

    // Handle command messages
    تهی MessageReceived(BMessage *message)
    {
        انتخاب (message->what) {
        // Handle commands from SDL
        حالت BWIN_SET_TITLE:
            _SetTitle(message);
            بشکن;
        حالت BWIN_MOVE_WINDOW:
            _MoveTo(message);
            بشکن;
        حالت BWIN_RESIZE_WINDOW:
            _ResizeTo(message);
            بشکن;
        حالت BWIN_SET_BORDERED:
        {
            bool bEnabled;
            اگر (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            بشکن;
        }
        حالت BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            اگر (message->FindBool("window-resizable", &bEnabled) == B_OK)
                _SetResizable(bEnabled);
            بشکن;
        }
        حالت BWIN_SHOW_WINDOW:
            Show();
            بشکن;
        حالت BWIN_HIDE_WINDOW:
            Hide();
            بشکن;
        حالت BWIN_MAXIMIZE_WINDOW:
            BWindow::Zoom();
            بشکن;
        حالت BWIN_MINIMIZE_WINDOW:
            Minimize(true);
            بشکن;
        حالت BWIN_RESTORE_WINDOW:
            _Restore();
            بشکن;
        حالت BWIN_FULLSCREEN:
        {
            bool fullscreen;
            اگر (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            بشکن;
        }
        حالت BWIN_MINIMUM_SIZE_WINDOW:
            _SetMinimumSize(message);
            بشکن;
        حالت BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            وقتی ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            اگر (_bitmap != پوچ) {
#ifdef SDL_VIDEO_OPENGL
                اگر (_SDL_GLView != پوچ && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } وگرنه
#endif
                اگر (_SDL_View != پوچ && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            بشکن;
        }
        پیشفرض:
            // Perform normal message handling
            BWindow::MessageReceived(message);
            بشکن;
        }
    }

    // Accessor methods
    bool IsShown() { بازگشت _shown; }
    int32 GetID() { بازگشت _id; }
    BBitmap *GetBitmap() { بازگشت _bitmap; }
    BView *GetCurView() { بازگشت _cur_view; }
    SDL_BView *GetView() { بازگشت _SDL_View; }
#ifdef SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        بازگشت _SDL_GLView;
    }
    Uint32 GetGLType() { بازگشت _gl_type; }
#endif

    // Setter methods
    تهی SetID(int32 id) { _id = id; }
    تهی LockBuffer() { _buffer_locker->Lock(); }
    تهی UnlockBuffer() { _buffer_locker->Unlock(); }
    تهی SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        اگر (_SDL_View != پوچ)
            _SDL_View->SetBitmap(bitmap);
    }

  خصوصی:
    // Event redirection
    تهی _MouseMotionEvent(BPoint &where, int32 transit)
    {
        اگر (transit == B_EXITED_VIEW) {
            // Change mouse focus
            اگر (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } وگرنه {
            // Change mouse focus
            اگر (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage پیام(BAPP_MOUSE_MOVED);
            پیام.AddInt32("x", (صحیح)where.x);
            پیام.AddInt32("y", (صحیح)where.y);

            _PostWindowEvent(پیام);
        }
    }

    تهی _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage پیام(BAPP_MOUSE_FOCUS);
        پیام.AddBool("focusGained", focusGained);
        _PostWindowEvent(پیام);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    تهی _MouseButtonEvent(int32 buttons, bool down)
    {
        int32 buttonStateChange = buttons ^ _last_buttons;

        اگر (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_چپ, down);
        }
        اگر (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_راست, down);
        }
        اگر (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_میانه, down);
        }

        _last_buttons = buttons;
    }

    تهی _SendMouseButton(int32 button, bool down)
    {
        BMessage پیام(BAPP_MOUSE_BUTTON);
        پیام.AddInt32("button-id", button);
        پیام.AddBool("button-down", down);
        _PostWindowEvent(پیام);
    }

    تهی _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage پیام(BAPP_MOUSE_WHEEL);
        پیام.AddInt32("xticks", x);
        پیام.AddInt32("yticks", y);
        _PostWindowEvent(پیام);
    }

    تهی کلید_Event_2(int32 کلید_Code, ثابت int8 *کلید_Utf8, ثابت ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage پیام(BAPP_کلید);
        پیام.AddInt32("key-scancode", کلید_Code);
        اگر (کلید_Utf8 != پوچ) {
            پیام.AddData("key-utf8", B_INT8_TYPE, (ثابت تهی *)کلید_Utf8, len);
        }
        پیام.AddBool("key-down", down);
        SDL_Looper->PostMessage(&پیام);
    }

    تهی _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage پیام(BAPP_REPAINT);
        _PostWindowEvent(پیام);
    }
    تهی _PostWindowEvent(BMessage &پیام)
    {
        پیام.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&پیام);
    }

    // Command methods (functions called upon by SDL)
    تهی _SetTitle(BMessage *پیام)
    {
        ثابت نویسه *title;
        اگر (
            پیام->FindString("window-title", &title) != B_OK) {
            بازگشت;
        }
        SetTitle(title);
    }

    تهی _MoveTo(BMessage *پیام)
    {
        int32 x, y;
        اگر (
            پیام->FindInt32("window-x", &x) != B_OK ||
            پیام->FindInt32("window-y", &y) != B_OK) {
            بازگشت;
        }
        اگر (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        وگرنه
            MoveTo(x, y);
    }

    تهی _ResizeTo(BMessage *پیام)
    {
        int32 w, h;
        اگر (
            پیام->FindInt32("window-w", &w) != B_OK ||
            پیام->FindInt32("window-h", &h) != B_OK) {
            بازگشت;
        }
        اگر (_fullscreen) {
            _non_fullscreen_frame.راست = _non_fullscreen_frame.چپ + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.بالاترین + h;
        } وگرنه
            ResizeTo(w, h);
    }

    تهی _SetBordered(bool bEnabled)
    {
        اگر (_fullscreen)
            _bordered = bEnabled;
        وگرنه
            SetLook(bEnabled ? B_TITLED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
    }

    تهی _SetResizable(bool bEnabled)
    {
        اگر (_fullscreen)
            _resizable = bEnabled;
        وگرنه {
            اگر (bEnabled) {
                SetFlags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } وگرنه {
                SetFlags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    تهی _SetMinimumSize(BMessage *پیام)
    {
        اعشاری maxHeight;
        اعشاری maxWidth;
        اعشاری _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        GetSizeLimits(&_, &maxWidth, &_, &maxHeight);
        اگر (پیام->FindInt32("window-w", &minWidth) != B_OK)
            بازگشت;
        اگر (پیام->FindInt32("window-h", &minHeight) != B_OK)
            بازگشت;
        SetSizeLimits((اعشاری)minWidth, maxWidth, (اعشاری)minHeight, maxHeight);
        UpdateSizeLimits();
    }

    تهی _Restore()
    {
        اگر (IsMinimized()) {
            Minimize(false);
        } وگرنه اگر (IsHidden()) {
            Show();
        } وگرنه اگر (_fullscreen) {

        } وگرنه اگر (_prev_frame != پوچ) { // Zoomed
            MoveTo(_prev_frame->چپ, _prev_frame->بالاترین);
            ResizeTo(_prev_frame->Width(), _prev_frame->Height());
        }
    }

    تهی _SetFullScreen(bool fullscreen)
    {
        اگر (fullscreen != _fullscreen) {
            اگر (fullscreen) {
                BScreen screen(this);
                BRect screenFrame = screen.Frame();
                _bordered = Look() != B_NO_BORDER_WINDOW_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                _non_fullscreen_frame = Frame();
                _SetBordered(false);
                _SetResizable(false);
                MoveTo(screenFrame.چپ, screenFrame.بالاترین);
                ResizeTo(screenFrame.Width(), screenFrame.Height());
                _fullscreen = fullscreen;
            } وگرنه {
                _fullscreen = fullscreen;
                MoveTo(_non_fullscreen_frame.چپ, _non_fullscreen_frame.بالاترین);
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
