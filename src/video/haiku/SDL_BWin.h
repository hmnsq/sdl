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
வெளி "C" {
#endif

#அந்தர்பாவ "SDL_internal.h"
#அந்தர்பாவ "SDL_bframebuffer.h"

#ifdef __cplusplus
}
#endif

#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <AppKit.h>
#அந்தர்பாவ <Cursor.h>
#அந்தர்பாவ <InterfaceKit.h>
#ifdef SDL_VIDEO_OPENGL
#அந்தர்பாவ <opengl/GLView.h>
#endif
#அந்தர்பாவ "../../core/haiku/SDL_BApp.h"

எண்ணிக்கை WinCommands
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
class SDL_BView : பொது BView
{
  பொது:
    SDL_BView(BRect frame, மாறிலி எழுத்து *name, uint32 resizingMode)
        : BView(frame, name, resizingMode, B_WILL_DRAW),
          fBitmap(வெற்று)
    {
    }

    வெறுமை Draw(BRect dirty)
    {
        எனில் (fBitmap != வெற்று)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    வெறுமை SetBitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  தனிப்பட்ட:
    BBitmap *fBitmap;
};

class SDL_BWin : பொது BWindow
{
  பொது:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, window_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_NORMAL_WINDOW_FEEL, flags)
    {
        _last_buttons = 0;

        _cur_view = வெற்று;
        _SDL_View = வெற்று;

#ifdef SDL_VIDEO_OPENGL
        _SDL_GLView = வெற்று;
        _gl_type = 0;
#endif
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        _prev_frame = வெற்று;
        _fullscreen = வெற்று;

        // Handle framebuffer stuff
        _buffer_locker = new BLocker();
        _bitmap = வெற்று;
    }

    மெய்நிகர் ~SDL_BWin()
    {
        Lock();

        எனில் (_SDL_View != வெற்று && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = வெற்று;
        }

#ifdef SDL_VIDEO_OPENGL
        எனில் (_SDL_GLView) {
            எனில் (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(வெற்று);
            எனில் (_SDL_GLView == _cur_view)
                RemoveChild(_SDL_GLView);
            _SDL_GLView = வெற்று;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#endif
        Unlock();

        delete _prev_frame;

        // Clean up framebuffer stuff
        _buffer_locker->Lock();
        delete _buffer_locker;
    }

    வெறுமை SetCurrentView(BView *view)
    {
        எனில் (_cur_view != view) {
            எனில் (_cur_view != வெற்று)
                RemoveChild(_cur_view);
            _cur_view = view;
            எனில் (_cur_view != வெற்று)
                AddChild(_cur_view);
        }
    }

    வெறுமை UpdateCurrentView()
    {
#ifdef SDL_VIDEO_OPENGL
        எனில் (_SDL_GLView != வெற்று) {
            SetCurrentView(_SDL_GLView);
        } இல்லையெனில்
#endif
        எனில் (_SDL_View != வெற்று) {
            SetCurrentView(_SDL_View);
        } இல்லையெனில் {
            SetCurrentView(வெற்று);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        எனில் (_SDL_View == வெற்று) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        திரும்பு _SDL_View;
    }

    வெறுமை RemoveView()
    {
        Lock();
        எனில் (_SDL_View != வெற்று) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = வெற்று;
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
        எனில் (_SDL_GLView == வெற்று) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        திரும்பு _SDL_GLView;
    }

    வெறுமை RemoveGLView()
    {
        Lock();
        எனில் (_SDL_GLView != வெற்று) {
            எனில் (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(வெற்று);
            _SDL_GLView = வெற்று;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    வெறுமை SwapBuffers(வெறுமை)
    {
        _SDL_GLView->SwapBuffers();
    }
#endif

    /* * * * * Event sending * * * * */
    // Hook functions
    மெய்நிகர் வெறுமை FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage செய்தி(BAPP_WINDOW_MOVED);
        செய்தி.AddInt32("window-x", (முழு)origin.x);
        செய்தி.AddInt32("window-y", (முழு)origin.y);
        _PostWindowEvent(செய்தி);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    வெறுமை FrameResized(தசம width, தசம height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage செய்தி(BAPP_WINDOW_RESIZED);

        செய்தி.AddInt32("window-w", (முழு)width + 1);
        செய்தி.AddInt32("window-h", (முழு)height + 1);
        _PostWindowEvent(செய்தி);

        // Perform normal hook operations
        BWindow::FrameResized(width, height);
    }

    bool QuitRequested()
    {
        BMessage செய்தி(BAPP_WINDOW_CLOSE_REQUESTED);
        _PostWindowEvent(செய்தி);

        // We won't allow a quit unless asked by DestroyWindow()
        திரும்பு false;
    }

    வெறுமை WindowActivated(bool active)
    {
        BMessage செய்தி(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        செய்தி.AddBool("focusGained", active);
        _PostWindowEvent(செய்தி);
    }

    வெறுமை Zoom(BPoint origin,
              தசம width,
              தசம height)
    {
        BMessage செய்தி(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(செய்தி);

        // Before the window zooms, record its size
        எனில் (!_prev_frame)
            _prev_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    வெறுமை Show()
    {
        போது (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage செய்தி(BAPP_SHOW);
        _PostWindowEvent(செய்தி);
    }

    வெறுமை Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage செய்தி(BAPP_HIDE);
        _PostWindowEvent(செய்தி);
    }

    வெறுமை Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage செய்தி(minState);
        _PostWindowEvent(செய்தி);
    }

    வெறுமை ScreenChanged(BRect screenFrame, color_space depth)
    {
        எனில் (_fullscreen) {
            MoveTo(screenFrame.இடது, screenFrame.உச்சி);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    வெறுமை DispatchMessage(BMessage *செய்தி, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 சாவி;     // Used for key events

        தேர்வு (செய்தி->what) {
        நிலை B_MOUSE_MOVED:
            int32 transit;
            எனில் (செய்தி->FindPoint("where", &where) == B_OK && செய்தி->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            நிறுத்து;

        நிலை B_MOUSE_DOWN:
            எனில் (செய்தி->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            நிறுத்து;

        நிலை B_MOUSE_UP:
            எனில் (செய்தி->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            நிறுத்து;

        நிலை B_MOUSE_WHEEL_CHANGED:
            தசம x, y;
            எனில் (செய்தி->FindFloat("be:wheel_delta_x", &x) == B_OK && செய்தி->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((முழு)x, (முழு)y);
            }
            நிறுத்து;

        நிலை B_சாவி_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            போது (i < 4 && செய்தி->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            எனில் (செய்தி->FindInt32("key", &சாவி) == B_OK) {
                சாவி_Event_2((SDL_Scancode)சாவி, &bytes[0], i, true);
            }
        } நிறுத்து;

        நிலை B_UNMAPPED_சாவி_DOWN: // modifier keys are unmapped
            எனில் (செய்தி->FindInt32("key", &சாவி) == B_OK) {
                சாவி_Event_2((SDL_Scancode)சாவி, வெற்று, 0, true);
            }
            நிறுத்து;

        நிலை B_சாவி_UP:
        நிலை B_UNMAPPED_சாவி_UP: // modifier keys are unmapped
            எனில் (செய்தி->FindInt32("key", &சாவி) == B_OK) {
                சாவி_Event_2(சாவி, வெற்று, 0, false);
            }
            நிறுத்து;

        இயல்பு:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            நிறுத்து;
        }

        BWindow::DispatchMessage(செய்தி, target);
    }

    // Handle command messages
    வெறுமை MessageReceived(BMessage *message)
    {
        தேர்வு (message->what) {
        // Handle commands from SDL
        நிலை BWIN_SET_TITLE:
            _SetTitle(message);
            நிறுத்து;
        நிலை BWIN_MOVE_WINDOW:
            _MoveTo(message);
            நிறுத்து;
        நிலை BWIN_RESIZE_WINDOW:
            _ResizeTo(message);
            நிறுத்து;
        நிலை BWIN_SET_BORDERED:
        {
            bool bEnabled;
            எனில் (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            நிறுத்து;
        }
        நிலை BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            எனில் (message->FindBool("window-resizable", &bEnabled) == B_OK)
                _SetResizable(bEnabled);
            நிறுத்து;
        }
        நிலை BWIN_SHOW_WINDOW:
            Show();
            நிறுத்து;
        நிலை BWIN_HIDE_WINDOW:
            Hide();
            நிறுத்து;
        நிலை BWIN_MAXIMIZE_WINDOW:
            BWindow::Zoom();
            நிறுத்து;
        நிலை BWIN_MINIMIZE_WINDOW:
            Minimize(true);
            நிறுத்து;
        நிலை BWIN_RESTORE_WINDOW:
            _Restore();
            நிறுத்து;
        நிலை BWIN_FULLSCREEN:
        {
            bool fullscreen;
            எனில் (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            நிறுத்து;
        }
        நிலை BWIN_MINIMUM_SIZE_WINDOW:
            _SetMinimumSize(message);
            நிறுத்து;
        நிலை BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            போது ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            எனில் (_bitmap != வெற்று) {
#ifdef SDL_VIDEO_OPENGL
                எனில் (_SDL_GLView != வெற்று && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } இல்லையெனில்
#endif
                எனில் (_SDL_View != வெற்று && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            நிறுத்து;
        }
        இயல்பு:
            // Perform normal message handling
            BWindow::MessageReceived(message);
            நிறுத்து;
        }
    }

    // Accessor methods
    bool IsShown() { திரும்பு _shown; }
    int32 GetID() { திரும்பு _id; }
    BBitmap *GetBitmap() { திரும்பு _bitmap; }
    BView *GetCurView() { திரும்பு _cur_view; }
    SDL_BView *GetView() { திரும்பு _SDL_View; }
#ifdef SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        திரும்பு _SDL_GLView;
    }
    Uint32 GetGLType() { திரும்பு _gl_type; }
#endif

    // Setter methods
    வெறுமை SetID(int32 id) { _id = id; }
    வெறுமை LockBuffer() { _buffer_locker->Lock(); }
    வெறுமை UnlockBuffer() { _buffer_locker->Unlock(); }
    வெறுமை SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        எனில் (_SDL_View != வெற்று)
            _SDL_View->SetBitmap(bitmap);
    }

  தனிப்பட்ட:
    // Event redirection
    வெறுமை _MouseMotionEvent(BPoint &where, int32 transit)
    {
        எனில் (transit == B_EXITED_VIEW) {
            // Change mouse focus
            எனில் (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } இல்லையெனில் {
            // Change mouse focus
            எனில் (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage செய்தி(BAPP_MOUSE_MOVED);
            செய்தி.AddInt32("x", (முழு)where.x);
            செய்தி.AddInt32("y", (முழு)where.y);

            _PostWindowEvent(செய்தி);
        }
    }

    வெறுமை _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage செய்தி(BAPP_MOUSE_FOCUS);
        செய்தி.AddBool("focusGained", focusGained);
        _PostWindowEvent(செய்தி);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    வெறுமை _MouseButtonEvent(int32 buttons, bool down)
    {
        int32 buttonStateChange = buttons ^ _last_buttons;

        எனில் (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_இடது, down);
        }
        எனில் (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_வலது, down);
        }
        எனில் (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_நடு, down);
        }

        _last_buttons = buttons;
    }

    வெறுமை _SendMouseButton(int32 button, bool down)
    {
        BMessage செய்தி(BAPP_MOUSE_BUTTON);
        செய்தி.AddInt32("button-id", button);
        செய்தி.AddBool("button-down", down);
        _PostWindowEvent(செய்தி);
    }

    வெறுமை _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage செய்தி(BAPP_MOUSE_WHEEL);
        செய்தி.AddInt32("xticks", x);
        செய்தி.AddInt32("yticks", y);
        _PostWindowEvent(செய்தி);
    }

    வெறுமை சாவி_Event_2(int32 சாவி_Code, மாறிலி int8 *சாவி_Utf8, மாறிலி ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage செய்தி(BAPP_சாவி);
        செய்தி.AddInt32("key-scancode", சாவி_Code);
        எனில் (சாவி_Utf8 != வெற்று) {
            செய்தி.AddData("key-utf8", B_INT8_TYPE, (மாறிலி வெறுமை *)சாவி_Utf8, len);
        }
        செய்தி.AddBool("key-down", down);
        SDL_Looper->PostMessage(&செய்தி);
    }

    வெறுமை _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage செய்தி(BAPP_REPAINT);
        _PostWindowEvent(செய்தி);
    }
    வெறுமை _PostWindowEvent(BMessage &செய்தி)
    {
        செய்தி.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&செய்தி);
    }

    // Command methods (functions called upon by SDL)
    வெறுமை _SetTitle(BMessage *செய்தி)
    {
        மாறிலி எழுத்து *title;
        எனில் (
            செய்தி->FindString("window-title", &title) != B_OK) {
            திரும்பு;
        }
        SetTitle(title);
    }

    வெறுமை _MoveTo(BMessage *செய்தி)
    {
        int32 x, y;
        எனில் (
            செய்தி->FindInt32("window-x", &x) != B_OK ||
            செய்தி->FindInt32("window-y", &y) != B_OK) {
            திரும்பு;
        }
        எனில் (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        இல்லையெனில்
            MoveTo(x, y);
    }

    வெறுமை _ResizeTo(BMessage *செய்தி)
    {
        int32 w, h;
        எனில் (
            செய்தி->FindInt32("window-w", &w) != B_OK ||
            செய்தி->FindInt32("window-h", &h) != B_OK) {
            திரும்பு;
        }
        எனில் (_fullscreen) {
            _non_fullscreen_frame.வலது = _non_fullscreen_frame.இடது + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.உச்சி + h;
        } இல்லையெனில்
            ResizeTo(w, h);
    }

    வெறுமை _SetBordered(bool bEnabled)
    {
        எனில் (_fullscreen)
            _bordered = bEnabled;
        இல்லையெனில்
            SetLook(bEnabled ? B_TITLED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
    }

    வெறுமை _SetResizable(bool bEnabled)
    {
        எனில் (_fullscreen)
            _resizable = bEnabled;
        இல்லையெனில் {
            எனில் (bEnabled) {
                SetFlags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } இல்லையெனில் {
                SetFlags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    வெறுமை _SetMinimumSize(BMessage *செய்தி)
    {
        தசம maxHeight;
        தசம maxWidth;
        தசம _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        GetSizeLimits(&_, &maxWidth, &_, &maxHeight);
        எனில் (செய்தி->FindInt32("window-w", &minWidth) != B_OK)
            திரும்பு;
        எனில் (செய்தி->FindInt32("window-h", &minHeight) != B_OK)
            திரும்பு;
        SetSizeLimits((தசம)minWidth, maxWidth, (தசம)minHeight, maxHeight);
        UpdateSizeLimits();
    }

    வெறுமை _Restore()
    {
        எனில் (IsMinimized()) {
            Minimize(false);
        } இல்லையெனில் எனில் (IsHidden()) {
            Show();
        } இல்லையெனில் எனில் (_fullscreen) {

        } இல்லையெனில் எனில் (_prev_frame != வெற்று) { // Zoomed
            MoveTo(_prev_frame->இடது, _prev_frame->உச்சி);
            ResizeTo(_prev_frame->Width(), _prev_frame->Height());
        }
    }

    வெறுமை _SetFullScreen(bool fullscreen)
    {
        எனில் (fullscreen != _fullscreen) {
            எனில் (fullscreen) {
                BScreen screen(this);
                BRect screenFrame = screen.Frame();
                _bordered = Look() != B_NO_BORDER_WINDOW_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                _non_fullscreen_frame = Frame();
                _SetBordered(false);
                _SetResizable(false);
                MoveTo(screenFrame.இடது, screenFrame.உச்சி);
                ResizeTo(screenFrame.Width(), screenFrame.Height());
                _fullscreen = fullscreen;
            } இல்லையெனில் {
                _fullscreen = fullscreen;
                MoveTo(_non_fullscreen_frame.இடது, _non_fullscreen_frame.உச்சி);
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
