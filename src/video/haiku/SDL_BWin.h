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
বাহ্যিক "C" {
#endif

#অন্তর্ভাব "SDL_internal.h"
#অন্তর্ভাব "SDL_bframebuffer.h"

#ifdef __cplusplus
}
#endif

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <AppKit.h>
#অন্তর্ভাব <Cursor.h>
#অন্তর্ভাব <InterfaceKit.h>
#ifdef SDL_VIDEO_OPENGL
#অন্তর্ভাব <opengl/GLView.h>
#endif
#অন্তর্ভাব "../../core/haiku/SDL_BApp.h"

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
    BWIN_MINIMUM_আকার_WINDOW
};

// non-OpenGL framebuffer view
class SDL_BView : সর্বজনীন BView
{
  সর্বজনীন:
    SDL_BView(BRect frame, ধ্রুবক অক্ষর *name, uint32 resizingMode)
        : BView(frame, name, resizingMode, B_WILL_DRAW),
          fBitmap(ফাঁকা)
    {
    }

    শূন্য Draw(BRect dirty)
    {
        যদি (fBitmap != ফাঁকা)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    শূন্য SetBitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  ব্যক্তিগত:
    BBitmap *fBitmap;
};

class SDL_BWin : সর্বজনীন BWindow
{
  সর্বজনীন:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, window_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_NORMAL_WINDOW_FEEL, flags)
    {
        _last_buttons = 0;

        _cur_view = ফাঁকা;
        _SDL_View = ফাঁকা;

#ifdef SDL_VIDEO_OPENGL
        _SDL_GLView = ফাঁকা;
        _gl_type = 0;
#endif
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        পূর্ব_frame = ফাঁকা;
        _fullscreen = ফাঁকা;

        // Handle framebuffer stuff
        বাফার_locker = new BLocker();
        _bitmap = ফাঁকা;
    }

    আভাসী ~SDL_BWin()
    {
        Lock();

        যদি (_SDL_View != ফাঁকা && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = ফাঁকা;
        }

#ifdef SDL_VIDEO_OPENGL
        যদি (_SDL_GLView) {
            যদি (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(ফাঁকা);
            যদি (_SDL_GLView == _cur_view)
                RemoveChild(_SDL_GLView);
            _SDL_GLView = ফাঁকা;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#endif
        Unlock();

        delete পূর্ব_frame;

        // Clean up framebuffer stuff
        বাফার_locker->Lock();
        delete বাফার_locker;
    }

    শূন্য SetCurrentView(BView *view)
    {
        যদি (_cur_view != view) {
            যদি (_cur_view != ফাঁকা)
                RemoveChild(_cur_view);
            _cur_view = view;
            যদি (_cur_view != ফাঁকা)
                AddChild(_cur_view);
        }
    }

    শূন্য UpdateCurrentView()
    {
#ifdef SDL_VIDEO_OPENGL
        যদি (_SDL_GLView != ফাঁকা) {
            SetCurrentView(_SDL_GLView);
        } অন্যথা
#endif
        যদি (_SDL_View != ফাঁকা) {
            SetCurrentView(_SDL_View);
        } অন্যথা {
            SetCurrentView(ফাঁকা);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        যদি (_SDL_View == ফাঁকা) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        ফেরত _SDL_View;
    }

    শূন্য RemoveView()
    {
        Lock();
        যদি (_SDL_View != ফাঁকা) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = ফাঁকা;
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
        যদি (_SDL_GLView == ফাঁকা) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        ফেরত _SDL_GLView;
    }

    শূন্য RemoveGLView()
    {
        Lock();
        যদি (_SDL_GLView != ফাঁকা) {
            যদি (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(ফাঁকা);
            _SDL_GLView = ফাঁকা;
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
    আভাসী শূন্য FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage বার্তা(BAPP_WINDOW_MOVED);
        বার্তা.AddInt32("window-x", (পূর্ণসংখ্যা)origin.x);
        বার্তা.AddInt32("window-y", (পূর্ণসংখ্যা)origin.y);
        _PostWindowEvent(বার্তা);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    শূন্য FrameResized(দশমিক width, দশমিক height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage বার্তা(BAPP_WINDOW_RESIZED);

        বার্তা.AddInt32("window-w", (পূর্ণসংখ্যা)width + 1);
        বার্তা.AddInt32("window-h", (পূর্ণসংখ্যা)height + 1);
        _PostWindowEvent(বার্তা);

        // Perform normal hook operations
        BWindow::FrameResized(width, height);
    }

    bool QuitRequested()
    {
        BMessage বার্তা(BAPP_WINDOW_CLOSE_REQUESTED);
        _PostWindowEvent(বার্তা);

        // We won't allow a quit unless asked by DestroyWindow()
        ফেরত false;
    }

    শূন্য WindowActivated(bool active)
    {
        BMessage বার্তা(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        বার্তা.AddBool("focusGained", active);
        _PostWindowEvent(বার্তা);
    }

    শূন্য Zoom(BPoint origin,
              দশমিক width,
              দশমিক height)
    {
        BMessage বার্তা(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(বার্তা);

        // Before the window zooms, record its size
        যদি (!পূর্ব_frame)
            পূর্ব_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    শূন্য Show()
    {
        যখন (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage বার্তা(BAPP_SHOW);
        _PostWindowEvent(বার্তা);
    }

    শূন্য Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage বার্তা(BAPP_HIDE);
        _PostWindowEvent(বার্তা);
    }

    শূন্য Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage বার্তা(minState);
        _PostWindowEvent(বার্তা);
    }

    শূন্য ScreenChanged(BRect screenFrame, color_space depth)
    {
        যদি (_fullscreen) {
            MoveTo(screenFrame.বাম, screenFrame.শীর্ষ);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    শূন্য DispatchMessage(BMessage *বার্তা, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 চাবি;     // Used for key events

        নির্বাচন (বার্তা->what) {
        ক্ষেত্র B_MOUSE_MOVED:
            int32 transit;
            যদি (বার্তা->FindPoint("where", &where) == B_OK && বার্তা->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            বিরতি;

        ক্ষেত্র B_MOUSE_DOWN:
            যদি (বার্তা->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            বিরতি;

        ক্ষেত্র B_MOUSE_UP:
            যদি (বার্তা->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            বিরতি;

        ক্ষেত্র B_MOUSE_WHEEL_CHANGED:
            দশমিক x, y;
            যদি (বার্তা->FindFloat("be:wheel_delta_x", &x) == B_OK && বার্তা->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((পূর্ণসংখ্যা)x, (পূর্ণসংখ্যা)y);
            }
            বিরতি;

        ক্ষেত্র B_চাবি_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            যখন (i < 4 && বার্তা->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            যদি (বার্তা->FindInt32("key", &চাবি) == B_OK) {
                চাবি_Event_2((SDL_Scancode)চাবি, &bytes[0], i, true);
            }
        } বিরতি;

        ক্ষেত্র B_UNMAPPED_চাবি_DOWN: // modifier keys are unmapped
            যদি (বার্তা->FindInt32("key", &চাবি) == B_OK) {
                চাবি_Event_2((SDL_Scancode)চাবি, ফাঁকা, 0, true);
            }
            বিরতি;

        ক্ষেত্র B_চাবি_UP:
        ক্ষেত্র B_UNMAPPED_চাবি_UP: // modifier keys are unmapped
            যদি (বার্তা->FindInt32("key", &চাবি) == B_OK) {
                চাবি_Event_2(চাবি, ফাঁকা, 0, false);
            }
            বিরতি;

        পূর্বনির্ধারিত:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            বিরতি;
        }

        BWindow::DispatchMessage(বার্তা, target);
    }

    // Handle command messages
    শূন্য MessageReceived(BMessage *message)
    {
        নির্বাচন (message->what) {
        // Handle commands from SDL
        ক্ষেত্র BWIN_SET_TITLE:
            _SetTitle(message);
            বিরতি;
        ক্ষেত্র BWIN_MOVE_WINDOW:
            _MoveTo(message);
            বিরতি;
        ক্ষেত্র BWIN_RESIZE_WINDOW:
            _ResizeTo(message);
            বিরতি;
        ক্ষেত্র BWIN_SET_BORDERED:
        {
            bool bEnabled;
            যদি (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            বিরতি;
        }
        ক্ষেত্র BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            যদি (message->FindBool("window-resizable", &bEnabled) == B_OK)
                _SetResizable(bEnabled);
            বিরতি;
        }
        ক্ষেত্র BWIN_SHOW_WINDOW:
            Show();
            বিরতি;
        ক্ষেত্র BWIN_HIDE_WINDOW:
            Hide();
            বিরতি;
        ক্ষেত্র BWIN_MAXIMIZE_WINDOW:
            BWindow::Zoom();
            বিরতি;
        ক্ষেত্র BWIN_MINIMIZE_WINDOW:
            Minimize(true);
            বিরতি;
        ক্ষেত্র BWIN_RESTORE_WINDOW:
            _Restore();
            বিরতি;
        ক্ষেত্র BWIN_FULLSCREEN:
        {
            bool fullscreen;
            যদি (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            বিরতি;
        }
        ক্ষেত্র BWIN_MINIMUM_আকার_WINDOW:
            Set_Minimum_আকার(message);
            বিরতি;
        ক্ষেত্র BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            যখন ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            যদি (_bitmap != ফাঁকা) {
#ifdef SDL_VIDEO_OPENGL
                যদি (_SDL_GLView != ফাঁকা && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } অন্যথা
#endif
                যদি (_SDL_View != ফাঁকা && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            বিরতি;
        }
        পূর্বনির্ধারিত:
            // Perform normal message handling
            BWindow::MessageReceived(message);
            বিরতি;
        }
    }

    // Accessor methods
    bool IsShown() { ফেরত _shown; }
    int32 GetID() { ফেরত _id; }
    BBitmap *GetBitmap() { ফেরত _bitmap; }
    BView *GetCurView() { ফেরত _cur_view; }
    SDL_BView *GetView() { ফেরত _SDL_View; }
#ifdef SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        ফেরত _SDL_GLView;
    }
    Uint32 GetGLType() { ফেরত _gl_type; }
#endif

    // Setter methods
    শূন্য SetID(int32 id) { _id = id; }
    শূন্য Lock_বাফার() { বাফার_locker->Lock(); }
    শূন্য Unlock_বাফার() { বাফার_locker->Unlock(); }
    শূন্য SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        যদি (_SDL_View != ফাঁকা)
            _SDL_View->SetBitmap(bitmap);
    }

  ব্যক্তিগত:
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
            BMessage বার্তা(BAPP_MOUSE_MOVED);
            বার্তা.AddInt32("x", (পূর্ণসংখ্যা)where.x);
            বার্তা.AddInt32("y", (পূর্ণসংখ্যা)where.y);

            _PostWindowEvent(বার্তা);
        }
    }

    শূন্য _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage বার্তা(BAPP_MOUSE_FOCUS);
        বার্তা.AddBool("focusGained", focusGained);
        _PostWindowEvent(বার্তা);

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
        BMessage বার্তা(BAPP_MOUSE_BUTTON);
        বার্তা.AddInt32("button-id", button);
        বার্তা.AddBool("button-down", down);
        _PostWindowEvent(বার্তা);
    }

    শূন্য _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage বার্তা(BAPP_MOUSE_WHEEL);
        বার্তা.AddInt32("xticks", x);
        বার্তা.AddInt32("yticks", y);
        _PostWindowEvent(বার্তা);
    }

    শূন্য চাবি_Event_2(int32 চাবি_Code, ধ্রুবক int8 *চাবি_Utf8, ধ্রুবক ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage বার্তা(BAPP_চাবি);
        বার্তা.AddInt32("key-scancode", চাবি_Code);
        যদি (চাবি_Utf8 != ফাঁকা) {
            বার্তা.Add_তথ্য("key-utf8", B_INT8_TYPE, (ধ্রুবক শূন্য *)চাবি_Utf8, len);
        }
        বার্তা.AddBool("key-down", down);
        SDL_Looper->PostMessage(&বার্তা);
    }

    শূন্য _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage বার্তা(BAPP_REPAINT);
        _PostWindowEvent(বার্তা);
    }
    শূন্য _PostWindowEvent(BMessage &বার্তা)
    {
        বার্তা.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&বার্তা);
    }

    // Command methods (functions called upon by SDL)
    শূন্য _SetTitle(BMessage *বার্তা)
    {
        ধ্রুবক অক্ষর *title;
        যদি (
            বার্তা->FindString("window-title", &title) != B_OK) {
            ফেরত;
        }
        SetTitle(title);
    }

    শূন্য _MoveTo(BMessage *বার্তা)
    {
        int32 x, y;
        যদি (
            বার্তা->FindInt32("window-x", &x) != B_OK ||
            বার্তা->FindInt32("window-y", &y) != B_OK) {
            ফেরত;
        }
        যদি (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        অন্যথা
            MoveTo(x, y);
    }

    শূন্য _ResizeTo(BMessage *বার্তা)
    {
        int32 w, h;
        যদি (
            বার্তা->FindInt32("window-w", &w) != B_OK ||
            বার্তা->FindInt32("window-h", &h) != B_OK) {
            ফেরত;
        }
        যদি (_fullscreen) {
            _non_fullscreen_frame.ডান = _non_fullscreen_frame.বাম + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.শীর্ষ + h;
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

    শূন্য Set_Minimum_আকার(BMessage *বার্তা)
    {
        দশমিক maxHeight;
        দশমিক maxWidth;
        দশমিক _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        Get_আকার_Limits(&_, &maxWidth, &_, &maxHeight);
        যদি (বার্তা->FindInt32("window-w", &minWidth) != B_OK)
            ফেরত;
        যদি (বার্তা->FindInt32("window-h", &minHeight) != B_OK)
            ফেরত;
        Set_আকার_Limits((দশমিক)minWidth, maxWidth, (দশমিক)minHeight, maxHeight);
        Update_আকার_Limits();
    }

    শূন্য _Restore()
    {
        যদি (IsMinimized()) {
            Minimize(false);
        } অন্যথা যদি (IsHidden()) {
            Show();
        } অন্যথা যদি (_fullscreen) {

        } অন্যথা যদি (পূর্ব_frame != ফাঁকা) { // Zoomed
            MoveTo(পূর্ব_frame->বাম, পূর্ব_frame->শীর্ষ);
            ResizeTo(পূর্ব_frame->Width(), পূর্ব_frame->Height());
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
                MoveTo(screenFrame.বাম, screenFrame.শীর্ষ);
                ResizeTo(screenFrame.Width(), screenFrame.Height());
                _fullscreen = fullscreen;
            } অন্যথা {
                _fullscreen = fullscreen;
                MoveTo(_non_fullscreen_frame.বাম, _non_fullscreen_frame.শীর্ষ);
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

    BRect *পূর্ব_frame; // Previous position and size of the window
    bool _fullscreen;
    // valid only if fullscreen
    BRect _non_fullscreen_frame;
    bool _bordered;
    bool _resizable;

    // Framebuffer members
    BLocker *বাফার_locker;
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
