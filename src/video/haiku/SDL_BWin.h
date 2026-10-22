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
ബാഹ്യ "C" {
#endif

#അന്തര്ഭാവ "SDL_internal.h"
#അന്തര്ഭാവ "SDL_bframebuffer.h"

#ifdef __cplusplus
}
#endif

#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <AppKit.h>
#അന്തര്ഭാവ <Cursor.h>
#അന്തര്ഭാവ <InterfaceKit.h>
#ifdef SDL_VIDEO_OPENGL
#അന്തര്ഭാവ <opengl/GLView.h>
#endif
#അന്തര്ഭാവ "../../core/haiku/SDL_BApp.h"

എണ്ണൽ WinCommands
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
class SDL_BView : പൊതു BView
{
  പൊതു:
    SDL_BView(BRect frame, സ്ഥിരം അക്ഷരം *name, uint32 resizingMode)
        : BView(frame, name, resizingMode, B_WILL_DRAW),
          fBitmap(ശൂന്യ)
    {
    }

    ശൂന്യം Draw(BRect dirty)
    {
        എങ്കിൽ (fBitmap != ശൂന്യ)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    ശൂന്യം SetBitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  സ്വകാര്യ:
    BBitmap *fBitmap;
};

class SDL_BWin : പൊതു BWindow
{
  പൊതു:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, window_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_NORMAL_WINDOW_FEEL, flags)
    {
        _last_buttons = 0;

        _cur_view = ശൂന്യ;
        _SDL_View = ശൂന്യ;

#ifdef SDL_VIDEO_OPENGL
        _SDL_GLView = ശൂന്യ;
        _gl_type = 0;
#endif
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        _prev_frame = ശൂന്യ;
        _fullscreen = ശൂന്യ;

        // Handle framebuffer stuff
        _buffer_locker = new BLocker();
        _bitmap = ശൂന്യ;
    }

    മായാ ~SDL_BWin()
    {
        Lock();

        എങ്കിൽ (_SDL_View != ശൂന്യ && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = ശൂന്യ;
        }

#ifdef SDL_VIDEO_OPENGL
        എങ്കിൽ (_SDL_GLView) {
            എങ്കിൽ (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(ശൂന്യ);
            എങ്കിൽ (_SDL_GLView == _cur_view)
                RemoveChild(_SDL_GLView);
            _SDL_GLView = ശൂന്യ;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#endif
        Unlock();

        delete _prev_frame;

        // Clean up framebuffer stuff
        _buffer_locker->Lock();
        delete _buffer_locker;
    }

    ശൂന്യം SetCurrentView(BView *view)
    {
        എങ്കിൽ (_cur_view != view) {
            എങ്കിൽ (_cur_view != ശൂന്യ)
                RemoveChild(_cur_view);
            _cur_view = view;
            എങ്കിൽ (_cur_view != ശൂന്യ)
                AddChild(_cur_view);
        }
    }

    ശൂന്യം UpdateCurrentView()
    {
#ifdef SDL_VIDEO_OPENGL
        എങ്കിൽ (_SDL_GLView != ശൂന്യ) {
            SetCurrentView(_SDL_GLView);
        } അല്ലെങ്കിൽ
#endif
        എങ്കിൽ (_SDL_View != ശൂന്യ) {
            SetCurrentView(_SDL_View);
        } അല്ലെങ്കിൽ {
            SetCurrentView(ശൂന്യ);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        എങ്കിൽ (_SDL_View == ശൂന്യ) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        തിരികെ _SDL_View;
    }

    ശൂന്യം RemoveView()
    {
        Lock();
        എങ്കിൽ (_SDL_View != ശൂന്യ) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = ശൂന്യ;
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
        എങ്കിൽ (_SDL_GLView == ശൂന്യ) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        തിരികെ _SDL_GLView;
    }

    ശൂന്യം RemoveGLView()
    {
        Lock();
        എങ്കിൽ (_SDL_GLView != ശൂന്യ) {
            എങ്കിൽ (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(ശൂന്യ);
            _SDL_GLView = ശൂന്യ;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    ശൂന്യം SwapBuffers(ശൂന്യം)
    {
        _SDL_GLView->SwapBuffers();
    }
#endif

    /* * * * * Event sending * * * * */
    // Hook functions
    മായാ ശൂന്യം FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage സന്ദേശം(BAPP_WINDOW_MOVED);
        സന്ദേശം.AddInt32("window-x", (പൂർണ്ണസംഖ്യ)origin.x);
        സന്ദേശം.AddInt32("window-y", (പൂർണ്ണസംഖ്യ)origin.y);
        _PostWindowEvent(സന്ദേശം);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    ശൂന്യം FrameResized(ദശാംശം width, ദശാംശം height)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage സന്ദേശം(BAPP_WINDOW_RESIZED);

        സന്ദേശം.AddInt32("window-w", (പൂർണ്ണസംഖ്യ)width + 1);
        സന്ദേശം.AddInt32("window-h", (പൂർണ്ണസംഖ്യ)height + 1);
        _PostWindowEvent(സന്ദേശം);

        // Perform normal hook operations
        BWindow::FrameResized(width, height);
    }

    bool QuitRequested()
    {
        BMessage സന്ദേശം(BAPP_WINDOW_CLOSE_REQUESTED);
        _PostWindowEvent(സന്ദേശം);

        // We won't allow a quit unless asked by DestroyWindow()
        തിരികെ false;
    }

    ശൂന്യം WindowActivated(bool active)
    {
        BMessage സന്ദേശം(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        സന്ദേശം.AddBool("focusGained", active);
        _PostWindowEvent(സന്ദേശം);
    }

    ശൂന്യം Zoom(BPoint origin,
              ദശാംശം width,
              ദശാംശം height)
    {
        BMessage സന്ദേശം(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(സന്ദേശം);

        // Before the window zooms, record its size
        എങ്കിൽ (!_prev_frame)
            _prev_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    ശൂന്യം Show()
    {
        ആകുമ്പോൾ (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage സന്ദേശം(BAPP_SHOW);
        _PostWindowEvent(സന്ദേശം);
    }

    ശൂന്യം Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage സന്ദേശം(BAPP_HIDE);
        _PostWindowEvent(സന്ദേശം);
    }

    ശൂന്യം Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage സന്ദേശം(minState);
        _PostWindowEvent(സന്ദേശം);
    }

    ശൂന്യം ScreenChanged(BRect screenFrame, color_space depth)
    {
        എങ്കിൽ (_fullscreen) {
            MoveTo(screenFrame.ഇടത്, screenFrame.മുകൾ);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    ശൂന്യം DispatchMessage(BMessage *സന്ദേശം, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 താക്കോൽ;     // Used for key events

        തിരഞ്ഞെടുപ്പ് (സന്ദേശം->what) {
        അവസ്ഥ B_MOUSE_MOVED:
            int32 transit;
            എങ്കിൽ (സന്ദേശം->FindPoint("where", &where) == B_OK && സന്ദേശം->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            നിർത്തുക;

        അവസ്ഥ B_MOUSE_DOWN:
            എങ്കിൽ (സന്ദേശം->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            നിർത്തുക;

        അവസ്ഥ B_MOUSE_UP:
            എങ്കിൽ (സന്ദേശം->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            നിർത്തുക;

        അവസ്ഥ B_MOUSE_WHEEL_CHANGED:
            ദശാംശം x, y;
            എങ്കിൽ (സന്ദേശം->FindFloat("be:wheel_delta_x", &x) == B_OK && സന്ദേശം->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((പൂർണ്ണസംഖ്യ)x, (പൂർണ്ണസംഖ്യ)y);
            }
            നിർത്തുക;

        അവസ്ഥ B_താക്കോൽ_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            ആകുമ്പോൾ (i < 4 && സന്ദേശം->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            എങ്കിൽ (സന്ദേശം->FindInt32("key", &താക്കോൽ) == B_OK) {
                താക്കോൽ_Event_2((SDL_Scancode)താക്കോൽ, &bytes[0], i, true);
            }
        } നിർത്തുക;

        അവസ്ഥ B_UNMAPPED_താക്കോൽ_DOWN: // modifier keys are unmapped
            എങ്കിൽ (സന്ദേശം->FindInt32("key", &താക്കോൽ) == B_OK) {
                താക്കോൽ_Event_2((SDL_Scancode)താക്കോൽ, ശൂന്യ, 0, true);
            }
            നിർത്തുക;

        അവസ്ഥ B_താക്കോൽ_UP:
        അവസ്ഥ B_UNMAPPED_താക്കോൽ_UP: // modifier keys are unmapped
            എങ്കിൽ (സന്ദേശം->FindInt32("key", &താക്കോൽ) == B_OK) {
                താക്കോൽ_Event_2(താക്കോൽ, ശൂന്യ, 0, false);
            }
            നിർത്തുക;

        സ്ഥിരസ്ഥിതി:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            നിർത്തുക;
        }

        BWindow::DispatchMessage(സന്ദേശം, target);
    }

    // Handle command messages
    ശൂന്യം MessageReceived(BMessage *message)
    {
        തിരഞ്ഞെടുപ്പ് (message->what) {
        // Handle commands from SDL
        അവസ്ഥ BWIN_SET_TITLE:
            _SetTitle(message);
            നിർത്തുക;
        അവസ്ഥ BWIN_MOVE_WINDOW:
            _MoveTo(message);
            നിർത്തുക;
        അവസ്ഥ BWIN_RESIZE_WINDOW:
            _ResizeTo(message);
            നിർത്തുക;
        അവസ്ഥ BWIN_SET_BORDERED:
        {
            bool bEnabled;
            എങ്കിൽ (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            നിർത്തുക;
        }
        അവസ്ഥ BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            എങ്കിൽ (message->FindBool("window-resizable", &bEnabled) == B_OK)
                _SetResizable(bEnabled);
            നിർത്തുക;
        }
        അവസ്ഥ BWIN_SHOW_WINDOW:
            Show();
            നിർത്തുക;
        അവസ്ഥ BWIN_HIDE_WINDOW:
            Hide();
            നിർത്തുക;
        അവസ്ഥ BWIN_MAXIMIZE_WINDOW:
            BWindow::Zoom();
            നിർത്തുക;
        അവസ്ഥ BWIN_MINIMIZE_WINDOW:
            Minimize(true);
            നിർത്തുക;
        അവസ്ഥ BWIN_RESTORE_WINDOW:
            _Restore();
            നിർത്തുക;
        അവസ്ഥ BWIN_FULLSCREEN:
        {
            bool fullscreen;
            എങ്കിൽ (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            നിർത്തുക;
        }
        അവസ്ഥ BWIN_MINIMUM_SIZE_WINDOW:
            _SetMinimumSize(message);
            നിർത്തുക;
        അവസ്ഥ BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            ആകുമ്പോൾ ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            എങ്കിൽ (_bitmap != ശൂന്യ) {
#ifdef SDL_VIDEO_OPENGL
                എങ്കിൽ (_SDL_GLView != ശൂന്യ && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } അല്ലെങ്കിൽ
#endif
                എങ്കിൽ (_SDL_View != ശൂന്യ && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            നിർത്തുക;
        }
        സ്ഥിരസ്ഥിതി:
            // Perform normal message handling
            BWindow::MessageReceived(message);
            നിർത്തുക;
        }
    }

    // Accessor methods
    bool IsShown() { തിരികെ _shown; }
    int32 GetID() { തിരികെ _id; }
    BBitmap *GetBitmap() { തിരികെ _bitmap; }
    BView *GetCurView() { തിരികെ _cur_view; }
    SDL_BView *GetView() { തിരികെ _SDL_View; }
#ifdef SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        തിരികെ _SDL_GLView;
    }
    Uint32 GetGLType() { തിരികെ _gl_type; }
#endif

    // Setter methods
    ശൂന്യം SetID(int32 id) { _id = id; }
    ശൂന്യം LockBuffer() { _buffer_locker->Lock(); }
    ശൂന്യം UnlockBuffer() { _buffer_locker->Unlock(); }
    ശൂന്യം SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        എങ്കിൽ (_SDL_View != ശൂന്യ)
            _SDL_View->SetBitmap(bitmap);
    }

  സ്വകാര്യ:
    // Event redirection
    ശൂന്യം _MouseMotionEvent(BPoint &where, int32 transit)
    {
        എങ്കിൽ (transit == B_EXITED_VIEW) {
            // Change mouse focus
            എങ്കിൽ (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } അല്ലെങ്കിൽ {
            // Change mouse focus
            എങ്കിൽ (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage സന്ദേശം(BAPP_MOUSE_MOVED);
            സന്ദേശം.AddInt32("x", (പൂർണ്ണസംഖ്യ)where.x);
            സന്ദേശം.AddInt32("y", (പൂർണ്ണസംഖ്യ)where.y);

            _PostWindowEvent(സന്ദേശം);
        }
    }

    ശൂന്യം _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage സന്ദേശം(BAPP_MOUSE_FOCUS);
        സന്ദേശം.AddBool("focusGained", focusGained);
        _PostWindowEvent(സന്ദേശം);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    ശൂന്യം _MouseButtonEvent(int32 buttons, bool down)
    {
        int32 buttonStateChange = buttons ^ _last_buttons;

        എങ്കിൽ (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ഇടത്, down);
        }
        എങ്കിൽ (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_വലത്, down);
        }
        എങ്കിൽ (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_നടുവ്, down);
        }

        _last_buttons = buttons;
    }

    ശൂന്യം _SendMouseButton(int32 button, bool down)
    {
        BMessage സന്ദേശം(BAPP_MOUSE_BUTTON);
        സന്ദേശം.AddInt32("button-id", button);
        സന്ദേശം.AddBool("button-down", down);
        _PostWindowEvent(സന്ദേശം);
    }

    ശൂന്യം _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage സന്ദേശം(BAPP_MOUSE_WHEEL);
        സന്ദേശം.AddInt32("xticks", x);
        സന്ദേശം.AddInt32("yticks", y);
        _PostWindowEvent(സന്ദേശം);
    }

    ശൂന്യം താക്കോൽ_Event_2(int32 താക്കോൽ_Code, സ്ഥിരം int8 *താക്കോൽ_Utf8, സ്ഥിരം ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage സന്ദേശം(BAPP_താക്കോൽ);
        സന്ദേശം.AddInt32("key-scancode", താക്കോൽ_Code);
        എങ്കിൽ (താക്കോൽ_Utf8 != ശൂന്യ) {
            സന്ദേശം.AddData("key-utf8", B_INT8_TYPE, (സ്ഥിരം ശൂന്യം *)താക്കോൽ_Utf8, len);
        }
        സന്ദേശം.AddBool("key-down", down);
        SDL_Looper->PostMessage(&സന്ദേശം);
    }

    ശൂന്യം _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage സന്ദേശം(BAPP_REPAINT);
        _PostWindowEvent(സന്ദേശം);
    }
    ശൂന്യം _PostWindowEvent(BMessage &സന്ദേശം)
    {
        സന്ദേശം.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&സന്ദേശം);
    }

    // Command methods (functions called upon by SDL)
    ശൂന്യം _SetTitle(BMessage *സന്ദേശം)
    {
        സ്ഥിരം അക്ഷരം *title;
        എങ്കിൽ (
            സന്ദേശം->FindString("window-title", &title) != B_OK) {
            തിരികെ;
        }
        SetTitle(title);
    }

    ശൂന്യം _MoveTo(BMessage *സന്ദേശം)
    {
        int32 x, y;
        എങ്കിൽ (
            സന്ദേശം->FindInt32("window-x", &x) != B_OK ||
            സന്ദേശം->FindInt32("window-y", &y) != B_OK) {
            തിരികെ;
        }
        എങ്കിൽ (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        അല്ലെങ്കിൽ
            MoveTo(x, y);
    }

    ശൂന്യം _ResizeTo(BMessage *സന്ദേശം)
    {
        int32 w, h;
        എങ്കിൽ (
            സന്ദേശം->FindInt32("window-w", &w) != B_OK ||
            സന്ദേശം->FindInt32("window-h", &h) != B_OK) {
            തിരികെ;
        }
        എങ്കിൽ (_fullscreen) {
            _non_fullscreen_frame.വലത് = _non_fullscreen_frame.ഇടത് + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.മുകൾ + h;
        } അല്ലെങ്കിൽ
            ResizeTo(w, h);
    }

    ശൂന്യം _SetBordered(bool bEnabled)
    {
        എങ്കിൽ (_fullscreen)
            _bordered = bEnabled;
        അല്ലെങ്കിൽ
            SetLook(bEnabled ? B_TITLED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
    }

    ശൂന്യം _SetResizable(bool bEnabled)
    {
        എങ്കിൽ (_fullscreen)
            _resizable = bEnabled;
        അല്ലെങ്കിൽ {
            എങ്കിൽ (bEnabled) {
                SetFlags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } അല്ലെങ്കിൽ {
                SetFlags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    ശൂന്യം _SetMinimumSize(BMessage *സന്ദേശം)
    {
        ദശാംശം maxHeight;
        ദശാംശം maxWidth;
        ദശാംശം _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        GetSizeLimits(&_, &maxWidth, &_, &maxHeight);
        എങ്കിൽ (സന്ദേശം->FindInt32("window-w", &minWidth) != B_OK)
            തിരികെ;
        എങ്കിൽ (സന്ദേശം->FindInt32("window-h", &minHeight) != B_OK)
            തിരികെ;
        SetSizeLimits((ദശാംശം)minWidth, maxWidth, (ദശാംശം)minHeight, maxHeight);
        UpdateSizeLimits();
    }

    ശൂന്യം _Restore()
    {
        എങ്കിൽ (IsMinimized()) {
            Minimize(false);
        } അല്ലെങ്കിൽ എങ്കിൽ (IsHidden()) {
            Show();
        } അല്ലെങ്കിൽ എങ്കിൽ (_fullscreen) {

        } അല്ലെങ്കിൽ എങ്കിൽ (_prev_frame != ശൂന്യ) { // Zoomed
            MoveTo(_prev_frame->ഇടത്, _prev_frame->മുകൾ);
            ResizeTo(_prev_frame->Width(), _prev_frame->Height());
        }
    }

    ശൂന്യം _SetFullScreen(bool fullscreen)
    {
        എങ്കിൽ (fullscreen != _fullscreen) {
            എങ്കിൽ (fullscreen) {
                BScreen screen(this);
                BRect screenFrame = screen.Frame();
                _bordered = Look() != B_NO_BORDER_WINDOW_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                _non_fullscreen_frame = Frame();
                _SetBordered(false);
                _SetResizable(false);
                MoveTo(screenFrame.ഇടത്, screenFrame.മുകൾ);
                ResizeTo(screenFrame.Width(), screenFrame.Height());
                _fullscreen = fullscreen;
            } അല്ലെങ്കിൽ {
                _fullscreen = fullscreen;
                MoveTo(_non_fullscreen_frame.ഇടത്, _non_fullscreen_frame.മുകൾ);
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
