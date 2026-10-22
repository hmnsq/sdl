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
बाह्य "C" {
#endif

#अन्तर्भाव "SDL_internal.h"
#अन्तर्भाव "SDL_bframebuffer.h"

#ifdef __cplusplus
}
#endif

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <AppKit.h>
#अन्तर्भाव <Cursor.h>
#अन्तर्भाव <InterfaceKit.h>
#ifdef SDL_VIDEO_OPENGL
#अन्तर्भाव <opengl/GLView.h>
#endif
#अन्तर्भाव "../../core/haiku/SDL_BApp.h"

गणना WinCommands
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
class SDL_BView : सार्वजनिक BView
{
  सार्वजनिक:
    SDL_BView(BRect frame, स्थिरांक अक्षर *name, uint32 resizingMode)
        : BView(frame, name, resizingMode, B_WILL_DRAW),
          fBitmap(रिक्त)
    {
    }

    शून्य Draw(BRect dirty)
    {
        जर (fBitmap != रिक्त)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    शून्य SetBitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  खाजगी:
    BBitmap *fBitmap;
};

class SDL_BWin : सार्वजनिक BWindow
{
  सार्वजनिक:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, window_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_NORMAL_WINDOW_FEEL, flags)
    {
        _last_buttons = 0;

        _cur_view = रिक्त;
        _SDL_View = रिक्त;

#ifdef SDL_VIDEO_OPENGL
        _SDL_GLView = रिक्त;
        _gl_type = 0;
#endif
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        _prev_frame = रिक्त;
        _fullscreen = रिक्त;

        // Handle framebuffer stuff
        _buffer_locker = new BLocker();
        _bitmap = रिक्त;
    }

    आभासी ~SDL_BWin()
    {
        Lock();

        जर (_SDL_View != रिक्त && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = रिक्त;
        }

#ifdef SDL_VIDEO_OPENGL
        जर (_SDL_GLView) {
            जर (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(रिक्त);
            जर (_SDL_GLView == _cur_view)
                RemoveChild(_SDL_GLView);
            _SDL_GLView = रिक्त;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#endif
        Unlock();

        delete _prev_frame;

        // Clean up framebuffer stuff
        _buffer_locker->Lock();
        delete _buffer_locker;
    }

    शून्य SetCurrentView(BView *view)
    {
        जर (_cur_view != view) {
            जर (_cur_view != रिक्त)
                RemoveChild(_cur_view);
            _cur_view = view;
            जर (_cur_view != रिक्त)
                AddChild(_cur_view);
        }
    }

    शून्य UpdateCurrentView()
    {
#ifdef SDL_VIDEO_OPENGL
        जर (_SDL_GLView != रिक्त) {
            SetCurrentView(_SDL_GLView);
        } अन्यथा
#endif
        जर (_SDL_View != रिक्त) {
            SetCurrentView(_SDL_View);
        } अन्यथा {
            SetCurrentView(रिक्त);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        जर (_SDL_View == रिक्त) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        परत _SDL_View;
    }

    शून्य RemoveView()
    {
        Lock();
        जर (_SDL_View != रिक्त) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = रिक्त;
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
        जर (_SDL_GLView == रिक्त) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        परत _SDL_GLView;
    }

    शून्य RemoveGLView()
    {
        Lock();
        जर (_SDL_GLView != रिक्त) {
            जर (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(रिक्त);
            _SDL_GLView = रिक्त;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    शून्य SwapBuffers(शून्य)
    {
        _SDL_GLView->SwapBuffers();
    }
#endif

    /* * * * * Event sending * * * * */
    // Hook functions
    आभासी शून्य FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage संदेश(BAPP_WINDOW_MOVED);
        संदेश.AddInt32("window-x", (पूर्णांक)origin.x);
        संदेश.AddInt32("window-y", (पूर्णांक)origin.y);
        _PostWindowEvent(संदेश);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    शून्य FrameResized(दशांश width, दशांश height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage संदेश(BAPP_WINDOW_RESIZED);

        संदेश.AddInt32("window-w", (पूर्णांक)width + 1);
        संदेश.AddInt32("window-h", (पूर्णांक)height + 1);
        _PostWindowEvent(संदेश);

        // Perform normal hook operations
        BWindow::FrameResized(width, height);
    }

    bool QuitRequested()
    {
        BMessage संदेश(BAPP_WINDOW_CLOSE_REQUESTED);
        _PostWindowEvent(संदेश);

        // We won't allow a quit unless asked by DestroyWindow()
        परत false;
    }

    शून्य WindowActivated(bool active)
    {
        BMessage संदेश(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        संदेश.AddBool("focusGained", active);
        _PostWindowEvent(संदेश);
    }

    शून्य Zoom(BPoint origin,
              दशांश width,
              दशांश height)
    {
        BMessage संदेश(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(संदेश);

        // Before the window zooms, record its size
        जर (!_prev_frame)
            _prev_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    शून्य Show()
    {
        पर्यंत (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage संदेश(BAPP_SHOW);
        _PostWindowEvent(संदेश);
    }

    शून्य Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage संदेश(BAPP_HIDE);
        _PostWindowEvent(संदेश);
    }

    शून्य Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage संदेश(minState);
        _PostWindowEvent(संदेश);
    }

    शून्य ScreenChanged(BRect screenFrame, color_space depth)
    {
        जर (_fullscreen) {
            MoveTo(screenFrame.डावा, screenFrame.शीर्ष);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    शून्य DispatchMessage(BMessage *संदेश, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 किल्ली;     // Used for key events

        निवड (संदेश->what) {
        स्थिती B_MOUSE_MOVED:
            int32 transit;
            जर (संदेश->FindPoint("where", &where) == B_OK && संदेश->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            थांबा;

        स्थिती B_MOUSE_DOWN:
            जर (संदेश->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            थांबा;

        स्थिती B_MOUSE_UP:
            जर (संदेश->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            थांबा;

        स्थिती B_MOUSE_WHEEL_CHANGED:
            दशांश x, y;
            जर (संदेश->FindFloat("be:wheel_delta_x", &x) == B_OK && संदेश->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((पूर्णांक)x, (पूर्णांक)y);
            }
            थांबा;

        स्थिती B_किल्ली_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            पर्यंत (i < 4 && संदेश->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            जर (संदेश->FindInt32("key", &किल्ली) == B_OK) {
                किल्ली_Event_2((SDL_Scancode)किल्ली, &bytes[0], i, true);
            }
        } थांबा;

        स्थिती B_UNMAPPED_किल्ली_DOWN: // modifier keys are unmapped
            जर (संदेश->FindInt32("key", &किल्ली) == B_OK) {
                किल्ली_Event_2((SDL_Scancode)किल्ली, रिक्त, 0, true);
            }
            थांबा;

        स्थिती B_किल्ली_UP:
        स्थिती B_UNMAPPED_किल्ली_UP: // modifier keys are unmapped
            जर (संदेश->FindInt32("key", &किल्ली) == B_OK) {
                किल्ली_Event_2(किल्ली, रिक्त, 0, false);
            }
            थांबा;

        पूर्वनिर्धारित:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            थांबा;
        }

        BWindow::DispatchMessage(संदेश, target);
    }

    // Handle command messages
    शून्य MessageReceived(BMessage *message)
    {
        निवड (message->what) {
        // Handle commands from SDL
        स्थिती BWIN_SET_TITLE:
            _SetTitle(message);
            थांबा;
        स्थिती BWIN_MOVE_WINDOW:
            _MoveTo(message);
            थांबा;
        स्थिती BWIN_RESIZE_WINDOW:
            _ResizeTo(message);
            थांबा;
        स्थिती BWIN_SET_BORDERED:
        {
            bool bEnabled;
            जर (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            थांबा;
        }
        स्थिती BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            जर (message->FindBool("window-resizable", &bEnabled) == B_OK)
                _SetResizable(bEnabled);
            थांबा;
        }
        स्थिती BWIN_SHOW_WINDOW:
            Show();
            थांबा;
        स्थिती BWIN_HIDE_WINDOW:
            Hide();
            थांबा;
        स्थिती BWIN_MAXIMIZE_WINDOW:
            BWindow::Zoom();
            थांबा;
        स्थिती BWIN_MINIMIZE_WINDOW:
            Minimize(true);
            थांबा;
        स्थिती BWIN_RESTORE_WINDOW:
            _Restore();
            थांबा;
        स्थिती BWIN_FULLSCREEN:
        {
            bool fullscreen;
            जर (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            थांबा;
        }
        स्थिती BWIN_MINIMUM_SIZE_WINDOW:
            _SetMinimumSize(message);
            थांबा;
        स्थिती BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            पर्यंत ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            जर (_bitmap != रिक्त) {
#ifdef SDL_VIDEO_OPENGL
                जर (_SDL_GLView != रिक्त && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } अन्यथा
#endif
                जर (_SDL_View != रिक्त && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            थांबा;
        }
        पूर्वनिर्धारित:
            // Perform normal message handling
            BWindow::MessageReceived(message);
            थांबा;
        }
    }

    // Accessor methods
    bool IsShown() { परत _shown; }
    int32 GetID() { परत _id; }
    BBitmap *GetBitmap() { परत _bitmap; }
    BView *GetCurView() { परत _cur_view; }
    SDL_BView *GetView() { परत _SDL_View; }
#ifdef SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        परत _SDL_GLView;
    }
    Uint32 GetGLType() { परत _gl_type; }
#endif

    // Setter methods
    शून्य SetID(int32 id) { _id = id; }
    शून्य LockBuffer() { _buffer_locker->Lock(); }
    शून्य UnlockBuffer() { _buffer_locker->Unlock(); }
    शून्य SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        जर (_SDL_View != रिक्त)
            _SDL_View->SetBitmap(bitmap);
    }

  खाजगी:
    // Event redirection
    शून्य _MouseMotionEvent(BPoint &where, int32 transit)
    {
        जर (transit == B_EXITED_VIEW) {
            // Change mouse focus
            जर (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } अन्यथा {
            // Change mouse focus
            जर (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage संदेश(BAPP_MOUSE_MOVED);
            संदेश.AddInt32("x", (पूर्णांक)where.x);
            संदेश.AddInt32("y", (पूर्णांक)where.y);

            _PostWindowEvent(संदेश);
        }
    }

    शून्य _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage संदेश(BAPP_MOUSE_FOCUS);
        संदेश.AddBool("focusGained", focusGained);
        _PostWindowEvent(संदेश);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    शून्य _MouseButtonEvent(int32 buttons, bool down)
    {
        int32 buttonStateChange = buttons ^ _last_buttons;

        जर (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_डावा, down);
        }
        जर (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_उजवा, down);
        }
        जर (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_मधला, down);
        }

        _last_buttons = buttons;
    }

    शून्य _SendMouseButton(int32 button, bool down)
    {
        BMessage संदेश(BAPP_MOUSE_BUTTON);
        संदेश.AddInt32("button-id", button);
        संदेश.AddBool("button-down", down);
        _PostWindowEvent(संदेश);
    }

    शून्य _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage संदेश(BAPP_MOUSE_WHEEL);
        संदेश.AddInt32("xticks", x);
        संदेश.AddInt32("yticks", y);
        _PostWindowEvent(संदेश);
    }

    शून्य किल्ली_Event_2(int32 किल्ली_Code, स्थिरांक int8 *किल्ली_Utf8, स्थिरांक ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage संदेश(BAPP_किल्ली);
        संदेश.AddInt32("key-scancode", किल्ली_Code);
        जर (किल्ली_Utf8 != रिक्त) {
            संदेश.AddData("key-utf8", B_INT8_TYPE, (स्थिरांक शून्य *)किल्ली_Utf8, len);
        }
        संदेश.AddBool("key-down", down);
        SDL_Looper->PostMessage(&संदेश);
    }

    शून्य _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage संदेश(BAPP_REPAINT);
        _PostWindowEvent(संदेश);
    }
    शून्य _PostWindowEvent(BMessage &संदेश)
    {
        संदेश.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&संदेश);
    }

    // Command methods (functions called upon by SDL)
    शून्य _SetTitle(BMessage *संदेश)
    {
        स्थिरांक अक्षर *title;
        जर (
            संदेश->FindString("window-title", &title) != B_OK) {
            परत;
        }
        SetTitle(title);
    }

    शून्य _MoveTo(BMessage *संदेश)
    {
        int32 x, y;
        जर (
            संदेश->FindInt32("window-x", &x) != B_OK ||
            संदेश->FindInt32("window-y", &y) != B_OK) {
            परत;
        }
        जर (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        अन्यथा
            MoveTo(x, y);
    }

    शून्य _ResizeTo(BMessage *संदेश)
    {
        int32 w, h;
        जर (
            संदेश->FindInt32("window-w", &w) != B_OK ||
            संदेश->FindInt32("window-h", &h) != B_OK) {
            परत;
        }
        जर (_fullscreen) {
            _non_fullscreen_frame.उजवा = _non_fullscreen_frame.डावा + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.शीर्ष + h;
        } अन्यथा
            ResizeTo(w, h);
    }

    शून्य _SetBordered(bool bEnabled)
    {
        जर (_fullscreen)
            _bordered = bEnabled;
        अन्यथा
            SetLook(bEnabled ? B_TITLED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
    }

    शून्य _SetResizable(bool bEnabled)
    {
        जर (_fullscreen)
            _resizable = bEnabled;
        अन्यथा {
            जर (bEnabled) {
                SetFlags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } अन्यथा {
                SetFlags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    शून्य _SetMinimumSize(BMessage *संदेश)
    {
        दशांश maxHeight;
        दशांश maxWidth;
        दशांश _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        GetSizeLimits(&_, &maxWidth, &_, &maxHeight);
        जर (संदेश->FindInt32("window-w", &minWidth) != B_OK)
            परत;
        जर (संदेश->FindInt32("window-h", &minHeight) != B_OK)
            परत;
        SetSizeLimits((दशांश)minWidth, maxWidth, (दशांश)minHeight, maxHeight);
        UpdateSizeLimits();
    }

    शून्य _Restore()
    {
        जर (IsMinimized()) {
            Minimize(false);
        } अन्यथा जर (IsHidden()) {
            Show();
        } अन्यथा जर (_fullscreen) {

        } अन्यथा जर (_prev_frame != रिक्त) { // Zoomed
            MoveTo(_prev_frame->डावा, _prev_frame->शीर्ष);
            ResizeTo(_prev_frame->Width(), _prev_frame->Height());
        }
    }

    शून्य _SetFullScreen(bool fullscreen)
    {
        जर (fullscreen != _fullscreen) {
            जर (fullscreen) {
                BScreen screen(this);
                BRect screenFrame = screen.Frame();
                _bordered = Look() != B_NO_BORDER_WINDOW_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                _non_fullscreen_frame = Frame();
                _SetBordered(false);
                _SetResizable(false);
                MoveTo(screenFrame.डावा, screenFrame.शीर्ष);
                ResizeTo(screenFrame.Width(), screenFrame.Height());
                _fullscreen = fullscreen;
            } अन्यथा {
                _fullscreen = fullscreen;
                MoveTo(_non_fullscreen_frame.डावा, _non_fullscreen_frame.शीर्ष);
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
