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
બાહ્ય "C" {
#endif

#અન્તર્ભાવ "SDL_internal.h"
#અન્તર્ભાવ "SDL_bframebuffer.h"

#ifdef __cplusplus
}
#endif

#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <AppKit.h>
#અન્તર્ભાવ <Cursor.h>
#અન્તર્ભાવ <InterfaceKit.h>
#ifdef SDL_VIDEO_OPENGL
#અન્તર્ભાવ <opengl/GLView.h>
#endif
#અન્તર્ભાવ "../../core/haiku/SDL_BApp.h"

ગણના WinCommands
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
class SDL_BView : જાહેર BView
{
  જાહેર:
    SDL_BView(BRect frame, અચલ અક્ષર *name, uint32 resizingMode)
        : BView(frame, name, resizingMode, B_WILL_DRAW),
          fBitmap(ખાલી)
    {
    }

    શૂન્ય Draw(BRect dirty)
    {
        જો (fBitmap != ખાલી)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    શૂન્ય SetBitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  ખાનગી:
    BBitmap *fBitmap;
};

class SDL_BWin : જાહેર BWindow
{
  જાહેર:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, window_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_NORMAL_WINDOW_FEEL, flags)
    {
        _last_buttons = 0;

        _cur_view = ખાલી;
        _SDL_View = ખાલી;

#ifdef SDL_VIDEO_OPENGL
        _SDL_GLView = ખાલી;
        _gl_type = 0;
#endif
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        _prev_frame = ખાલી;
        _fullscreen = ખાલી;

        // Handle framebuffer stuff
        _buffer_locker = new BLocker();
        _bitmap = ખાલી;
    }

    આભાસી ~SDL_BWin()
    {
        Lock();

        જો (_SDL_View != ખાલી && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = ખાલી;
        }

#ifdef SDL_VIDEO_OPENGL
        જો (_SDL_GLView) {
            જો (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(ખાલી);
            જો (_SDL_GLView == _cur_view)
                RemoveChild(_SDL_GLView);
            _SDL_GLView = ખાલી;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#endif
        Unlock();

        delete _prev_frame;

        // Clean up framebuffer stuff
        _buffer_locker->Lock();
        delete _buffer_locker;
    }

    શૂન્ય SetCurrentView(BView *view)
    {
        જો (_cur_view != view) {
            જો (_cur_view != ખાલી)
                RemoveChild(_cur_view);
            _cur_view = view;
            જો (_cur_view != ખાલી)
                AddChild(_cur_view);
        }
    }

    શૂન્ય UpdateCurrentView()
    {
#ifdef SDL_VIDEO_OPENGL
        જો (_SDL_GLView != ખાલી) {
            SetCurrentView(_SDL_GLView);
        } નહીંતર
#endif
        જો (_SDL_View != ખાલી) {
            SetCurrentView(_SDL_View);
        } નહીંતર {
            SetCurrentView(ખાલી);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        જો (_SDL_View == ખાલી) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        પાછા _SDL_View;
    }

    શૂન્ય RemoveView()
    {
        Lock();
        જો (_SDL_View != ખાલી) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = ખાલી;
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
        જો (_SDL_GLView == ખાલી) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        પાછા _SDL_GLView;
    }

    શૂન્ય RemoveGLView()
    {
        Lock();
        જો (_SDL_GLView != ખાલી) {
            જો (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(ખાલી);
            _SDL_GLView = ખાલી;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    શૂન્ય SwapBuffers(શૂન્ય)
    {
        _SDL_GLView->SwapBuffers();
    }
#endif

    /* * * * * Event sending * * * * */
    // Hook functions
    આભાસી શૂન્ય FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage સંદેશ(BAPP_WINDOW_MOVED);
        સંદેશ.AddInt32("window-x", (પૂર્ણાંક)origin.x);
        સંદેશ.AddInt32("window-y", (પૂર્ણાંક)origin.y);
        _PostWindowEvent(સંદેશ);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    શૂન્ય FrameResized(દશાંશ width, દશાંશ height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage સંદેશ(BAPP_WINDOW_RESIZED);

        સંદેશ.AddInt32("window-w", (પૂર્ણાંક)width + 1);
        સંદેશ.AddInt32("window-h", (પૂર્ણાંક)height + 1);
        _PostWindowEvent(સંદેશ);

        // Perform normal hook operations
        BWindow::FrameResized(width, height);
    }

    bool QuitRequested()
    {
        BMessage સંદેશ(BAPP_WINDOW_CLOSE_REQUESTED);
        _PostWindowEvent(સંદેશ);

        // We won't allow a quit unless asked by DestroyWindow()
        પાછા false;
    }

    શૂન્ય WindowActivated(bool active)
    {
        BMessage સંદેશ(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        સંદેશ.AddBool("focusGained", active);
        _PostWindowEvent(સંદેશ);
    }

    શૂન્ય Zoom(BPoint origin,
              દશાંશ width,
              દશાંશ height)
    {
        BMessage સંદેશ(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(સંદેશ);

        // Before the window zooms, record its size
        જો (!_prev_frame)
            _prev_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    શૂન્ય Show()
    {
        જ્યારે (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage સંદેશ(BAPP_SHOW);
        _PostWindowEvent(સંદેશ);
    }

    શૂન્ય Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage સંદેશ(BAPP_HIDE);
        _PostWindowEvent(સંદેશ);
    }

    શૂન્ય Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage સંદેશ(minState);
        _PostWindowEvent(સંદેશ);
    }

    શૂન્ય ScreenChanged(BRect screenFrame, color_space depth)
    {
        જો (_fullscreen) {
            MoveTo(screenFrame.ડાબું, screenFrame.ટોચ);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    શૂન્ય DispatchMessage(BMessage *સંદેશ, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 ચાવી;     // Used for key events

        પસંદગી (સંદેશ->what) {
        સ્થિતિ B_MOUSE_MOVED:
            int32 transit;
            જો (સંદેશ->FindPoint("where", &where) == B_OK && સંદેશ->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            તોડો;

        સ્થિતિ B_MOUSE_DOWN:
            જો (સંદેશ->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            તોડો;

        સ્થિતિ B_MOUSE_UP:
            જો (સંદેશ->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            તોડો;

        સ્થિતિ B_MOUSE_WHEEL_CHANGED:
            દશાંશ x, y;
            જો (સંદેશ->FindFloat("be:wheel_delta_x", &x) == B_OK && સંદેશ->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((પૂર્ણાંક)x, (પૂર્ણાંક)y);
            }
            તોડો;

        સ્થિતિ B_ચાવી_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            જ્યારે (i < 4 && સંદેશ->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            જો (સંદેશ->FindInt32("key", &ચાવી) == B_OK) {
                ચાવી_Event_2((SDL_Scancode)ચાવી, &bytes[0], i, true);
            }
        } તોડો;

        સ્થિતિ B_UNMAPPED_ચાવી_DOWN: // modifier keys are unmapped
            જો (સંદેશ->FindInt32("key", &ચાવી) == B_OK) {
                ચાવી_Event_2((SDL_Scancode)ચાવી, ખાલી, 0, true);
            }
            તોડો;

        સ્થિતિ B_ચાવી_UP:
        સ્થિતિ B_UNMAPPED_ચાવી_UP: // modifier keys are unmapped
            જો (સંદેશ->FindInt32("key", &ચાવી) == B_OK) {
                ચાવી_Event_2(ચાવી, ખાલી, 0, false);
            }
            તોડો;

        મૂળભૂત:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            તોડો;
        }

        BWindow::DispatchMessage(સંદેશ, target);
    }

    // Handle command messages
    શૂન્ય MessageReceived(BMessage *message)
    {
        પસંદગી (message->what) {
        // Handle commands from SDL
        સ્થિતિ BWIN_SET_TITLE:
            _SetTitle(message);
            તોડો;
        સ્થિતિ BWIN_MOVE_WINDOW:
            _MoveTo(message);
            તોડો;
        સ્થિતિ BWIN_RESIZE_WINDOW:
            _ResizeTo(message);
            તોડો;
        સ્થિતિ BWIN_SET_BORDERED:
        {
            bool bEnabled;
            જો (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            તોડો;
        }
        સ્થિતિ BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            જો (message->FindBool("window-resizable", &bEnabled) == B_OK)
                _SetResizable(bEnabled);
            તોડો;
        }
        સ્થિતિ BWIN_SHOW_WINDOW:
            Show();
            તોડો;
        સ્થિતિ BWIN_HIDE_WINDOW:
            Hide();
            તોડો;
        સ્થિતિ BWIN_MAXIMIZE_WINDOW:
            BWindow::Zoom();
            તોડો;
        સ્થિતિ BWIN_MINIMIZE_WINDOW:
            Minimize(true);
            તોડો;
        સ્થિતિ BWIN_RESTORE_WINDOW:
            _Restore();
            તોડો;
        સ્થિતિ BWIN_FULLSCREEN:
        {
            bool fullscreen;
            જો (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            તોડો;
        }
        સ્થિતિ BWIN_MINIMUM_SIZE_WINDOW:
            _SetMinimumSize(message);
            તોડો;
        સ્થિતિ BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            જ્યારે ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            જો (_bitmap != ખાલી) {
#ifdef SDL_VIDEO_OPENGL
                જો (_SDL_GLView != ખાલી && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } નહીંતર
#endif
                જો (_SDL_View != ખાલી && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            તોડો;
        }
        મૂળભૂત:
            // Perform normal message handling
            BWindow::MessageReceived(message);
            તોડો;
        }
    }

    // Accessor methods
    bool IsShown() { પાછા _shown; }
    int32 GetID() { પાછા _id; }
    BBitmap *GetBitmap() { પાછા _bitmap; }
    BView *GetCurView() { પાછા _cur_view; }
    SDL_BView *GetView() { પાછા _SDL_View; }
#ifdef SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        પાછા _SDL_GLView;
    }
    Uint32 GetGLType() { પાછા _gl_type; }
#endif

    // Setter methods
    શૂન્ય SetID(int32 id) { _id = id; }
    શૂન્ય LockBuffer() { _buffer_locker->Lock(); }
    શૂન્ય UnlockBuffer() { _buffer_locker->Unlock(); }
    શૂન્ય SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        જો (_SDL_View != ખાલી)
            _SDL_View->SetBitmap(bitmap);
    }

  ખાનગી:
    // Event redirection
    શૂન્ય _MouseMotionEvent(BPoint &where, int32 transit)
    {
        જો (transit == B_EXITED_VIEW) {
            // Change mouse focus
            જો (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } નહીંતર {
            // Change mouse focus
            જો (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage સંદેશ(BAPP_MOUSE_MOVED);
            સંદેશ.AddInt32("x", (પૂર્ણાંક)where.x);
            સંદેશ.AddInt32("y", (પૂર્ણાંક)where.y);

            _PostWindowEvent(સંદેશ);
        }
    }

    શૂન્ય _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage સંદેશ(BAPP_MOUSE_FOCUS);
        સંદેશ.AddBool("focusGained", focusGained);
        _PostWindowEvent(સંદેશ);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    શૂન્ય _MouseButtonEvent(int32 buttons, bool down)
    {
        int32 buttonStateChange = buttons ^ _last_buttons;

        જો (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ડાબું, down);
        }
        જો (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_જમણું, down);
        }
        જો (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_મધ્ય, down);
        }

        _last_buttons = buttons;
    }

    શૂન્ય _SendMouseButton(int32 button, bool down)
    {
        BMessage સંદેશ(BAPP_MOUSE_BUTTON);
        સંદેશ.AddInt32("button-id", button);
        સંદેશ.AddBool("button-down", down);
        _PostWindowEvent(સંદેશ);
    }

    શૂન્ય _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage સંદેશ(BAPP_MOUSE_WHEEL);
        સંદેશ.AddInt32("xticks", x);
        સંદેશ.AddInt32("yticks", y);
        _PostWindowEvent(સંદેશ);
    }

    શૂન્ય ચાવી_Event_2(int32 ચાવી_Code, અચલ int8 *ચાવી_Utf8, અચલ ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage સંદેશ(BAPP_ચાવી);
        સંદેશ.AddInt32("key-scancode", ચાવી_Code);
        જો (ચાવી_Utf8 != ખાલી) {
            સંદેશ.AddData("key-utf8", B_INT8_TYPE, (અચલ શૂન્ય *)ચાવી_Utf8, len);
        }
        સંદેશ.AddBool("key-down", down);
        SDL_Looper->PostMessage(&સંદેશ);
    }

    શૂન્ય _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage સંદેશ(BAPP_REPAINT);
        _PostWindowEvent(સંદેશ);
    }
    શૂન્ય _PostWindowEvent(BMessage &સંદેશ)
    {
        સંદેશ.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&સંદેશ);
    }

    // Command methods (functions called upon by SDL)
    શૂન્ય _SetTitle(BMessage *સંદેશ)
    {
        અચલ અક્ષર *title;
        જો (
            સંદેશ->FindString("window-title", &title) != B_OK) {
            પાછા;
        }
        SetTitle(title);
    }

    શૂન્ય _MoveTo(BMessage *સંદેશ)
    {
        int32 x, y;
        જો (
            સંદેશ->FindInt32("window-x", &x) != B_OK ||
            સંદેશ->FindInt32("window-y", &y) != B_OK) {
            પાછા;
        }
        જો (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        નહીંતર
            MoveTo(x, y);
    }

    શૂન્ય _ResizeTo(BMessage *સંદેશ)
    {
        int32 w, h;
        જો (
            સંદેશ->FindInt32("window-w", &w) != B_OK ||
            સંદેશ->FindInt32("window-h", &h) != B_OK) {
            પાછા;
        }
        જો (_fullscreen) {
            _non_fullscreen_frame.જમણું = _non_fullscreen_frame.ડાબું + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.ટોચ + h;
        } નહીંતર
            ResizeTo(w, h);
    }

    શૂન્ય _SetBordered(bool bEnabled)
    {
        જો (_fullscreen)
            _bordered = bEnabled;
        નહીંતર
            SetLook(bEnabled ? B_TITLED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
    }

    શૂન્ય _SetResizable(bool bEnabled)
    {
        જો (_fullscreen)
            _resizable = bEnabled;
        નહીંતર {
            જો (bEnabled) {
                SetFlags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } નહીંતર {
                SetFlags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    શૂન્ય _SetMinimumSize(BMessage *સંદેશ)
    {
        દશાંશ maxHeight;
        દશાંશ maxWidth;
        દશાંશ _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        GetSizeLimits(&_, &maxWidth, &_, &maxHeight);
        જો (સંદેશ->FindInt32("window-w", &minWidth) != B_OK)
            પાછા;
        જો (સંદેશ->FindInt32("window-h", &minHeight) != B_OK)
            પાછા;
        SetSizeLimits((દશાંશ)minWidth, maxWidth, (દશાંશ)minHeight, maxHeight);
        UpdateSizeLimits();
    }

    શૂન્ય _Restore()
    {
        જો (IsMinimized()) {
            Minimize(false);
        } નહીંતર જો (IsHidden()) {
            Show();
        } નહીંતર જો (_fullscreen) {

        } નહીંતર જો (_prev_frame != ખાલી) { // Zoomed
            MoveTo(_prev_frame->ડાબું, _prev_frame->ટોચ);
            ResizeTo(_prev_frame->Width(), _prev_frame->Height());
        }
    }

    શૂન્ય _SetFullScreen(bool fullscreen)
    {
        જો (fullscreen != _fullscreen) {
            જો (fullscreen) {
                BScreen screen(this);
                BRect screenFrame = screen.Frame();
                _bordered = Look() != B_NO_BORDER_WINDOW_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                _non_fullscreen_frame = Frame();
                _SetBordered(false);
                _SetResizable(false);
                MoveTo(screenFrame.ડાબું, screenFrame.ટોચ);
                ResizeTo(screenFrame.Width(), screenFrame.Height());
                _fullscreen = fullscreen;
            } નહીંતર {
                _fullscreen = fullscreen;
                MoveTo(_non_fullscreen_frame.ડાબું, _non_fullscreen_frame.ટોચ);
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
