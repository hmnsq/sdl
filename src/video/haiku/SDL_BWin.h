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
    SDL_BView(BRect frame, अचर वर्ण *name, uint32 resizingMode)
        : BView(frame, name, resizingMode, B_WILL_DRAW),
          fBitmap(रिक्त)
    {
    }

    शून्य Draw(BRect dirty)
    {
        यदि (fBitmap != रिक्त)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    शून्य SetBitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  गुप्त:
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

    आभास ~SDL_BWin()
    {
        Lock();

        यदि (_SDL_View != रिक्त && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = रिक्त;
        }

#ifdef SDL_VIDEO_OPENGL
        यदि (_SDL_GLView) {
            यदि (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(रिक्त);
            यदि (_SDL_GLView == _cur_view)
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
        यदि (_cur_view != view) {
            यदि (_cur_view != रिक्त)
                RemoveChild(_cur_view);
            _cur_view = view;
            यदि (_cur_view != रिक्त)
                AddChild(_cur_view);
        }
    }

    शून्य UpdateCurrentView()
    {
#ifdef SDL_VIDEO_OPENGL
        यदि (_SDL_GLView != रिक्त) {
            SetCurrentView(_SDL_GLView);
        } अन्यथा
#endif
        यदि (_SDL_View != रिक्त) {
            SetCurrentView(_SDL_View);
        } अन्यथा {
            SetCurrentView(रिक्त);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        यदि (_SDL_View == रिक्त) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        फर्काऊ _SDL_View;
    }

    शून्य RemoveView()
    {
        Lock();
        यदि (_SDL_View != रिक्त) {
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
        यदि (_SDL_GLView == रिक्त) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        फर्काऊ _SDL_GLView;
    }

    शून्य RemoveGLView()
    {
        Lock();
        यदि (_SDL_GLView != रिक्त) {
            यदि (SDL_Looper->GetCurrentContext() == _SDL_GLView)
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
    आभास शून्य FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage सन्देश(BAPP_WINDOW_MOVED);
        सन्देश.AddInt32("window-x", (पूर्णाङ्क)origin.x);
        सन्देश.AddInt32("window-y", (पूर्णाङ्क)origin.y);
        _PostWindowEvent(सन्देश);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    शून्य FrameResized(भिन्न width, भिन्न height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage सन्देश(BAPP_WINDOW_RESIZED);

        सन्देश.AddInt32("window-w", (पूर्णाङ्क)width + 1);
        सन्देश.AddInt32("window-h", (पूर्णाङ्क)height + 1);
        _PostWindowEvent(सन्देश);

        // Perform normal hook operations
        BWindow::FrameResized(width, height);
    }

    bool QuitRequested()
    {
        BMessage सन्देश(BAPP_WINDOW_CLOSE_REQUESTED);
        _PostWindowEvent(सन्देश);

        // We won't allow a quit unless asked by DestroyWindow()
        फर्काऊ false;
    }

    शून्य WindowActivated(bool active)
    {
        BMessage सन्देश(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        सन्देश.AddBool("focusGained", active);
        _PostWindowEvent(सन्देश);
    }

    शून्य Zoom(BPoint origin,
              भिन्न width,
              भिन्न height)
    {
        BMessage सन्देश(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(सन्देश);

        // Before the window zooms, record its size
        यदि (!_prev_frame)
            _prev_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    शून्य Show()
    {
        जबसम्म (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage सन्देश(BAPP_SHOW);
        _PostWindowEvent(सन्देश);
    }

    शून्य Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage सन्देश(BAPP_HIDE);
        _PostWindowEvent(सन्देश);
    }

    शून्य Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage सन्देश(minState);
        _PostWindowEvent(सन्देश);
    }

    शून्य ScreenChanged(BRect screenFrame, color_space depth)
    {
        यदि (_fullscreen) {
            MoveTo(screenFrame.बायाँ, screenFrame.शीर्ष);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    शून्य DispatchMessage(BMessage *सन्देश, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 साँचो;     // Used for key events

        विकल्प (सन्देश->what) {
        पक्ष B_MOUSE_MOVED:
            int32 transit;
            यदि (सन्देश->FindPoint("where", &where) == B_OK && सन्देश->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            रोक;

        पक्ष B_MOUSE_DOWN:
            यदि (सन्देश->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            रोक;

        पक्ष B_MOUSE_UP:
            यदि (सन्देश->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            रोक;

        पक्ष B_MOUSE_WHEEL_CHANGED:
            भिन्न x, y;
            यदि (सन्देश->FindFloat("be:wheel_delta_x", &x) == B_OK && सन्देश->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((पूर्णाङ्क)x, (पूर्णाङ्क)y);
            }
            रोक;

        पक्ष B_साँचो_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            जबसम्म (i < 4 && सन्देश->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            यदि (सन्देश->FindInt32("key", &साँचो) == B_OK) {
                साँचो_Event_2((SDL_Scancode)साँचो, &bytes[0], i, true);
            }
        } रोक;

        पक्ष B_UNMAPPED_साँचो_DOWN: // modifier keys are unmapped
            यदि (सन्देश->FindInt32("key", &साँचो) == B_OK) {
                साँचो_Event_2((SDL_Scancode)साँचो, रिक्त, 0, true);
            }
            रोक;

        पक्ष B_साँचो_UP:
        पक्ष B_UNMAPPED_साँचो_UP: // modifier keys are unmapped
            यदि (सन्देश->FindInt32("key", &साँचो) == B_OK) {
                साँचो_Event_2(साँचो, रिक्त, 0, false);
            }
            रोक;

        स्वभाव:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            रोक;
        }

        BWindow::DispatchMessage(सन्देश, target);
    }

    // Handle command messages
    शून्य MessageReceived(BMessage *message)
    {
        विकल्प (message->what) {
        // Handle commands from SDL
        पक्ष BWIN_SET_TITLE:
            _SetTitle(message);
            रोक;
        पक्ष BWIN_MOVE_WINDOW:
            _MoveTo(message);
            रोक;
        पक्ष BWIN_RESIZE_WINDOW:
            _ResizeTo(message);
            रोक;
        पक्ष BWIN_SET_BORDERED:
        {
            bool bEnabled;
            यदि (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            रोक;
        }
        पक्ष BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            यदि (message->FindBool("window-resizable", &bEnabled) == B_OK)
                _SetResizable(bEnabled);
            रोक;
        }
        पक्ष BWIN_SHOW_WINDOW:
            Show();
            रोक;
        पक्ष BWIN_HIDE_WINDOW:
            Hide();
            रोक;
        पक्ष BWIN_MAXIMIZE_WINDOW:
            BWindow::Zoom();
            रोक;
        पक्ष BWIN_MINIMIZE_WINDOW:
            Minimize(true);
            रोक;
        पक्ष BWIN_RESTORE_WINDOW:
            _Restore();
            रोक;
        पक्ष BWIN_FULLSCREEN:
        {
            bool fullscreen;
            यदि (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            रोक;
        }
        पक्ष BWIN_MINIMUM_SIZE_WINDOW:
            _SetMinimumSize(message);
            रोक;
        पक्ष BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            जबसम्म ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            यदि (_bitmap != रिक्त) {
#ifdef SDL_VIDEO_OPENGL
                यदि (_SDL_GLView != रिक्त && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } अन्यथा
#endif
                यदि (_SDL_View != रिक्त && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            रोक;
        }
        स्वभाव:
            // Perform normal message handling
            BWindow::MessageReceived(message);
            रोक;
        }
    }

    // Accessor methods
    bool IsShown() { फर्काऊ _shown; }
    int32 GetID() { फर्काऊ _id; }
    BBitmap *GetBitmap() { फर्काऊ _bitmap; }
    BView *GetCurView() { फर्काऊ _cur_view; }
    SDL_BView *GetView() { फर्काऊ _SDL_View; }
#ifdef SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        फर्काऊ _SDL_GLView;
    }
    Uint32 GetGLType() { फर्काऊ _gl_type; }
#endif

    // Setter methods
    शून्य SetID(int32 id) { _id = id; }
    शून्य LockBuffer() { _buffer_locker->Lock(); }
    शून्य UnlockBuffer() { _buffer_locker->Unlock(); }
    शून्य SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        यदि (_SDL_View != रिक्त)
            _SDL_View->SetBitmap(bitmap);
    }

  गुप्त:
    // Event redirection
    शून्य _MouseMotionEvent(BPoint &where, int32 transit)
    {
        यदि (transit == B_EXITED_VIEW) {
            // Change mouse focus
            यदि (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } अन्यथा {
            // Change mouse focus
            यदि (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage सन्देश(BAPP_MOUSE_MOVED);
            सन्देश.AddInt32("x", (पूर्णाङ्क)where.x);
            सन्देश.AddInt32("y", (पूर्णाङ्क)where.y);

            _PostWindowEvent(सन्देश);
        }
    }

    शून्य _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage सन्देश(BAPP_MOUSE_FOCUS);
        सन्देश.AddBool("focusGained", focusGained);
        _PostWindowEvent(सन्देश);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    शून्य _MouseButtonEvent(int32 buttons, bool down)
    {
        int32 buttonStateChange = buttons ^ _last_buttons;

        यदि (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_बायाँ, down);
        }
        यदि (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_दायाँ, down);
        }
        यदि (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_बीच, down);
        }

        _last_buttons = buttons;
    }

    शून्य _SendMouseButton(int32 button, bool down)
    {
        BMessage सन्देश(BAPP_MOUSE_BUTTON);
        सन्देश.AddInt32("button-id", button);
        सन्देश.AddBool("button-down", down);
        _PostWindowEvent(सन्देश);
    }

    शून्य _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage सन्देश(BAPP_MOUSE_WHEEL);
        सन्देश.AddInt32("xticks", x);
        सन्देश.AddInt32("yticks", y);
        _PostWindowEvent(सन्देश);
    }

    शून्य साँचो_Event_2(int32 साँचो_Code, अचर int8 *साँचो_Utf8, अचर ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage सन्देश(BAPP_साँचो);
        सन्देश.AddInt32("key-scancode", साँचो_Code);
        यदि (साँचो_Utf8 != रिक्त) {
            सन्देश.AddData("key-utf8", B_INT8_TYPE, (अचर शून्य *)साँचो_Utf8, len);
        }
        सन्देश.AddBool("key-down", down);
        SDL_Looper->PostMessage(&सन्देश);
    }

    शून्य _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage सन्देश(BAPP_REPAINT);
        _PostWindowEvent(सन्देश);
    }
    शून्य _PostWindowEvent(BMessage &सन्देश)
    {
        सन्देश.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&सन्देश);
    }

    // Command methods (functions called upon by SDL)
    शून्य _SetTitle(BMessage *सन्देश)
    {
        अचर वर्ण *title;
        यदि (
            सन्देश->FindString("window-title", &title) != B_OK) {
            फर्काऊ;
        }
        SetTitle(title);
    }

    शून्य _MoveTo(BMessage *सन्देश)
    {
        int32 x, y;
        यदि (
            सन्देश->FindInt32("window-x", &x) != B_OK ||
            सन्देश->FindInt32("window-y", &y) != B_OK) {
            फर्काऊ;
        }
        यदि (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        अन्यथा
            MoveTo(x, y);
    }

    शून्य _ResizeTo(BMessage *सन्देश)
    {
        int32 w, h;
        यदि (
            सन्देश->FindInt32("window-w", &w) != B_OK ||
            सन्देश->FindInt32("window-h", &h) != B_OK) {
            फर्काऊ;
        }
        यदि (_fullscreen) {
            _non_fullscreen_frame.दायाँ = _non_fullscreen_frame.बायाँ + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.शीर्ष + h;
        } अन्यथा
            ResizeTo(w, h);
    }

    शून्य _SetBordered(bool bEnabled)
    {
        यदि (_fullscreen)
            _bordered = bEnabled;
        अन्यथा
            SetLook(bEnabled ? B_TITLED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
    }

    शून्य _SetResizable(bool bEnabled)
    {
        यदि (_fullscreen)
            _resizable = bEnabled;
        अन्यथा {
            यदि (bEnabled) {
                SetFlags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } अन्यथा {
                SetFlags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    शून्य _SetMinimumSize(BMessage *सन्देश)
    {
        भिन्न maxHeight;
        भिन्न maxWidth;
        भिन्न _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        GetSizeLimits(&_, &maxWidth, &_, &maxHeight);
        यदि (सन्देश->FindInt32("window-w", &minWidth) != B_OK)
            फर्काऊ;
        यदि (सन्देश->FindInt32("window-h", &minHeight) != B_OK)
            फर्काऊ;
        SetSizeLimits((भिन्न)minWidth, maxWidth, (भिन्न)minHeight, maxHeight);
        UpdateSizeLimits();
    }

    शून्य _Restore()
    {
        यदि (IsMinimized()) {
            Minimize(false);
        } अन्यथा यदि (IsHidden()) {
            Show();
        } अन्यथा यदि (_fullscreen) {

        } अन्यथा यदि (_prev_frame != रिक्त) { // Zoomed
            MoveTo(_prev_frame->बायाँ, _prev_frame->शीर्ष);
            ResizeTo(_prev_frame->Width(), _prev_frame->Height());
        }
    }

    शून्य _SetFullScreen(bool fullscreen)
    {
        यदि (fullscreen != _fullscreen) {
            यदि (fullscreen) {
                BScreen screen(this);
                BRect screenFrame = screen.Frame();
                _bordered = Look() != B_NO_BORDER_WINDOW_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                _non_fullscreen_frame = Frame();
                _SetBordered(false);
                _SetResizable(false);
                MoveTo(screenFrame.बायाँ, screenFrame.शीर्ष);
                ResizeTo(screenFrame.Width(), screenFrame.Height());
                _fullscreen = fullscreen;
            } अन्यथा {
                _fullscreen = fullscreen;
                MoveTo(_non_fullscreen_frame.बायाँ, _non_fullscreen_frame.शीर्ष);
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
