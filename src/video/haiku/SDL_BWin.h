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

#अगर_अघोषित SDL_BWin_h_
#घोषणा SDL_BWin_h_

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

#समावेश "SDL_internal.h"
#समावेश "SDL_bframebuffer.h"

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#समावेश <stdio.h>
#समावेश <AppKit.h>
#समावेश <Cursor.h>
#समावेश <InterfaceKit.h>
#अगर_घोषित SDL_VIDEO_OPENGL
#समावेश <opengl/GLView.h>
#पूर्ण_अगर
#समावेश "../../core/haiku/SDL_BApp.h"

क्रमागत WinCommands
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
    BWIN_MINIMUM_आकार_WINDOW
};

// non-OpenGL framebuffer view
class SDL_BView : खुला BView
{
  खुला:
    SDL_BView(BRect frame, स्थिर अक्षर *name, uint32 resizingMode)
        : BView(frame, name, resizingMode, B_WILL_DRAW),
          fBitmap(शून्य)
    {
    }

    व्योम Draw(BRect dirty)
    {
        अगर (fBitmap != शून्य)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    व्योम SetBitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  निजी:
    BBitmap *fBitmap;
};

class SDL_BWin : खुला BWindow
{
  खुला:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, window_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_NORMAL_WINDOW_FEEL, flags)
    {
        _last_buttons = 0;

        _cur_view = शून्य;
        _SDL_View = शून्य;

#अगर_घोषित SDL_VIDEO_OPENGL
        _SDL_GLView = शून्य;
        _gl_type = 0;
#पूर्ण_अगर
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        पूर्व_frame = शून्य;
        _fullscreen = शून्य;

        // Handle framebuffer stuff
        बफर_locker = new BLocker();
        _bitmap = शून्य;
    }

    भव ~SDL_BWin()
    {
        Lock();

        अगर (_SDL_View != शून्य && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = शून्य;
        }

#अगर_घोषित SDL_VIDEO_OPENGL
        अगर (_SDL_GLView) {
            अगर (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(शून्य);
            अगर (_SDL_GLView == _cur_view)
                RemoveChild(_SDL_GLView);
            _SDL_GLView = शून्य;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#पूर्ण_अगर
        Unlock();

        delete पूर्व_frame;

        // Clean up framebuffer stuff
        बफर_locker->Lock();
        delete बफर_locker;
    }

    व्योम SetCurrentView(BView *view)
    {
        अगर (_cur_view != view) {
            अगर (_cur_view != शून्य)
                RemoveChild(_cur_view);
            _cur_view = view;
            अगर (_cur_view != शून्य)
                AddChild(_cur_view);
        }
    }

    व्योम UpdateCurrentView()
    {
#अगर_घोषित SDL_VIDEO_OPENGL
        अगर (_SDL_GLView != शून्य) {
            SetCurrentView(_SDL_GLView);
        } अन्यथा
#पूर्ण_अगर
        अगर (_SDL_View != शून्य) {
            SetCurrentView(_SDL_View);
        } अन्यथा {
            SetCurrentView(शून्य);
        }
    }

    SDL_BView *CreateView()
    {
        Lock();
        अगर (_SDL_View == शून्य) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        वापस _SDL_View;
    }

    व्योम RemoveView()
    {
        Lock();
        अगर (_SDL_View != शून्य) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = शून्य;
            UpdateCurrentView();
            delete oldView;
        }
        Unlock();
    }

    /* * * * * OpenGL functionality * * * * */
#अगर_घोषित SDL_VIDEO_OPENGL
    BGLView *CreateGLView(Uint32 gl_flags)
    {
        Lock();
        अगर (_SDL_GLView == शून्य) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_FRAME_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        वापस _SDL_GLView;
    }

    व्योम RemoveGLView()
    {
        Lock();
        अगर (_SDL_GLView != शून्य) {
            अगर (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->SetCurrentContext(शून्य);
            _SDL_GLView = शून्य;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    व्योम SwapBuffers(व्योम)
    {
        _SDL_GLView->SwapBuffers();
    }
#पूर्ण_अगर

    /* * * * * Event sending * * * * */
    // Hook functions
    भव व्योम FrameMoved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage संदेश(BAPP_WINDOW_MOVED);
        संदेश.AddInt32("window-x", (पूर्णांक)origin.x);
        संदेश.AddInt32("window-y", (पूर्णांक)origin.y);
        _PostWindowEvent(संदेश);

        // Perform normal hook operations
        BWindow::FrameMoved(origin);
    }

    व्योम FrameResized(भग्न width, भग्न height)
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
        वापस false;
    }

    व्योम WindowActivated(bool active)
    {
        BMessage संदेश(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        संदेश.AddBool("focusGained", active);
        _PostWindowEvent(संदेश);
    }

    व्योम Zoom(BPoint origin,
              भग्न width,
              भग्न height)
    {
        BMessage संदेश(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        _PostWindowEvent(संदेश);

        // Before the window zooms, record its size
        अगर (!पूर्व_frame)
            पूर्व_frame = new BRect(Frame());

        // Perform normal hook operations
        BWindow::Zoom(origin, width, height);
    }

    // Member functions
    व्योम Show()
    {
        जबतक (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage संदेश(BAPP_SHOW);
        _PostWindowEvent(संदेश);
    }

    व्योम Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage संदेश(BAPP_HIDE);
        _PostWindowEvent(संदेश);
    }

    व्योम Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage संदेश(minState);
        _PostWindowEvent(संदेश);
    }

    व्योम ScreenChanged(BRect screenFrame, color_space depth)
    {
        अगर (_fullscreen) {
            MoveTo(screenFrame.बायाँ, screenFrame.शीर्ष);
            ResizeTo(screenFrame.Width(), screenFrame.Height());
        }
    }

    // BView message interruption
    व्योम DispatchMessage(BMessage *संदेश, BHandler *target)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 कुंजी;     // Used for key events

        चयन (संदेश->what) {
        हाल B_MOUSE_MOVED:
            int32 transit;
            अगर (संदेश->FindPoint("where", &where) == B_OK && संदेश->FindInt32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            अवरोध;

        हाल B_MOUSE_DOWN:
            अगर (संदेश->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            अवरोध;

        हाल B_MOUSE_UP:
            अगर (संदेश->FindInt32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            अवरोध;

        हाल B_MOUSE_WHEEL_CHANGED:
            भग्न x, y;
            अगर (संदेश->FindFloat("be:wheel_delta_x", &x) == B_OK && संदेश->FindFloat("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((पूर्णांक)x, (पूर्णांक)y);
            }
            अवरोध;

        हाल B_कुंजी_DOWN:
        {
            int32 i = 0;
            int8 byte;
            int8 bytes[4] = { 0, 0, 0, 0 };
            जबतक (i < 4 && संदेश->FindInt8("byte", i, &byte) == B_OK) {
                bytes[i] = byte;
                i++;
            }
            अगर (संदेश->FindInt32("key", &कुंजी) == B_OK) {
                कुंजी_Event_2((SDL_Scancode)कुंजी, &bytes[0], i, true);
            }
        } अवरोध;

        हाल B_UNMAPPED_कुंजी_DOWN: // modifier keys are unmapped
            अगर (संदेश->FindInt32("key", &कुंजी) == B_OK) {
                कुंजी_Event_2((SDL_Scancode)कुंजी, शून्य, 0, true);
            }
            अवरोध;

        हाल B_कुंजी_UP:
        हाल B_UNMAPPED_कुंजी_UP: // modifier keys are unmapped
            अगर (संदेश->FindInt32("key", &कुंजी) == B_OK) {
                कुंजी_Event_2(कुंजी, शून्य, 0, false);
            }
            अवरोध;

        शेष:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            अवरोध;
        }

        BWindow::DispatchMessage(संदेश, target);
    }

    // Handle command messages
    व्योम MessageReceived(BMessage *message)
    {
        चयन (message->what) {
        // Handle commands from SDL
        हाल BWIN_SET_TITLE:
            _SetTitle(message);
            अवरोध;
        हाल BWIN_MOVE_WINDOW:
            _MoveTo(message);
            अवरोध;
        हाल BWIN_RESIZE_WINDOW:
            _ResizeTo(message);
            अवरोध;
        हाल BWIN_SET_BORDERED:
        {
            bool bEnabled;
            अगर (message->FindBool("window-border", &bEnabled) == B_OK)
                _SetBordered(bEnabled);
            अवरोध;
        }
        हाल BWIN_SET_RESIZABLE:
        {
            bool bEnabled;
            अगर (message->FindBool("window-resizable", &bEnabled) == B_OK)
                _SetResizable(bEnabled);
            अवरोध;
        }
        हाल BWIN_SHOW_WINDOW:
            Show();
            अवरोध;
        हाल BWIN_HIDE_WINDOW:
            Hide();
            अवरोध;
        हाल BWIN_MAXIMIZE_WINDOW:
            BWindow::Zoom();
            अवरोध;
        हाल BWIN_MINIMIZE_WINDOW:
            Minimize(true);
            अवरोध;
        हाल BWIN_RESTORE_WINDOW:
            _Restore();
            अवरोध;
        हाल BWIN_FULLSCREEN:
        {
            bool fullscreen;
            अगर (message->FindBool("fullscreen", &fullscreen) == B_OK)
                _SetFullScreen(fullscreen);
            अवरोध;
        }
        हाल BWIN_MINIMUM_आकार_WINDOW:
            Set_Minimum_आकार(message);
            अवरोध;
        हाल BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pendingMessage;
            जबतक ((pendingMessage = MessageQueue()->FindMessage(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                MessageQueue()->RemoveMessage(pendingMessage);
                delete pendingMessage;
            }
            अगर (_bitmap != शून्य) {
#अगर_घोषित SDL_VIDEO_OPENGL
                अगर (_SDL_GLView != शून्य && _cur_view == _SDL_GLView) {
                    _SDL_GLView->CopyPixelsIn(_bitmap, B_ORIGIN);
                } अन्यथा
#पूर्ण_अगर
                अगर (_SDL_View != शून्य && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            अवरोध;
        }
        शेष:
            // Perform normal message handling
            BWindow::MessageReceived(message);
            अवरोध;
        }
    }

    // Accessor methods
    bool IsShown() { वापस _shown; }
    int32 GetID() { वापस _id; }
    BBitmap *GetBitmap() { वापस _bitmap; }
    BView *GetCurView() { वापस _cur_view; }
    SDL_BView *GetView() { वापस _SDL_View; }
#अगर_घोषित SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        वापस _SDL_GLView;
    }
    Uint32 GetGLType() { वापस _gl_type; }
#पूर्ण_अगर

    // Setter methods
    व्योम SetID(int32 id) { _id = id; }
    व्योम Lock_बफर() { बफर_locker->Lock(); }
    व्योम Unlock_बफर() { बफर_locker->Unlock(); }
    व्योम SetBitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        अगर (_SDL_View != शून्य)
            _SDL_View->SetBitmap(bitmap);
    }

  निजी:
    // Event redirection
    व्योम _MouseMotionEvent(BPoint &where, int32 transit)
    {
        अगर (transit == B_EXITED_VIEW) {
            // Change mouse focus
            अगर (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } अन्यथा {
            // Change mouse focus
            अगर (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage संदेश(BAPP_MOUSE_MOVED);
            संदेश.AddInt32("x", (पूर्णांक)where.x);
            संदेश.AddInt32("y", (पूर्णांक)where.y);

            _PostWindowEvent(संदेश);
        }
    }

    व्योम _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage संदेश(BAPP_MOUSE_FOCUS);
        संदेश.AddBool("focusGained", focusGained);
        _PostWindowEvent(संदेश);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    व्योम _MouseButtonEvent(int32 buttons, bool down)
    {
        int32 buttonStateChange = buttons ^ _last_buttons;

        अगर (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_बायाँ, down);
        }
        अगर (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_दायाँ, down);
        }
        अगर (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_मध्य, down);
        }

        _last_buttons = buttons;
    }

    व्योम _SendMouseButton(int32 button, bool down)
    {
        BMessage संदेश(BAPP_MOUSE_BUTTON);
        संदेश.AddInt32("button-id", button);
        संदेश.AddBool("button-down", down);
        _PostWindowEvent(संदेश);
    }

    व्योम _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage संदेश(BAPP_MOUSE_WHEEL);
        संदेश.AddInt32("xticks", x);
        संदेश.AddInt32("yticks", y);
        _PostWindowEvent(संदेश);
    }

    व्योम कुंजी_Event_2(int32 कुंजी_Code, स्थिर int8 *कुंजी_Utf8, स्थिर ssize_t &len, bool down)
    {
        // Create a message to pass along to the BeApp thread
        BMessage संदेश(BAPP_कुंजी);
        संदेश.AddInt32("key-scancode", कुंजी_Code);
        अगर (कुंजी_Utf8 != शून्य) {
            संदेश.Add_तथ्य("key-utf8", B_INT8_TYPE, (स्थिर व्योम *)कुंजी_Utf8, len);
        }
        संदेश.AddBool("key-down", down);
        SDL_Looper->PostMessage(&संदेश);
    }

    व्योम _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage संदेश(BAPP_REPAINT);
        _PostWindowEvent(संदेश);
    }
    व्योम _PostWindowEvent(BMessage &संदेश)
    {
        संदेश.AddInt32("window-id", _id);
        SDL_Looper->PostMessage(&संदेश);
    }

    // Command methods (functions called upon by SDL)
    व्योम _SetTitle(BMessage *संदेश)
    {
        स्थिर अक्षर *title;
        अगर (
            संदेश->FindString("window-title", &title) != B_OK) {
            वापस;
        }
        SetTitle(title);
    }

    व्योम _MoveTo(BMessage *संदेश)
    {
        int32 x, y;
        अगर (
            संदेश->FindInt32("window-x", &x) != B_OK ||
            संदेश->FindInt32("window-y", &y) != B_OK) {
            वापस;
        }
        अगर (_fullscreen)
            _non_fullscreen_frame.OffsetTo(x, y);
        अन्यथा
            MoveTo(x, y);
    }

    व्योम _ResizeTo(BMessage *संदेश)
    {
        int32 w, h;
        अगर (
            संदेश->FindInt32("window-w", &w) != B_OK ||
            संदेश->FindInt32("window-h", &h) != B_OK) {
            वापस;
        }
        अगर (_fullscreen) {
            _non_fullscreen_frame.दायाँ = _non_fullscreen_frame.बायाँ + w;
            _non_fullscreen_frame.bottom = _non_fullscreen_frame.शीर्ष + h;
        } अन्यथा
            ResizeTo(w, h);
    }

    व्योम _SetBordered(bool bEnabled)
    {
        अगर (_fullscreen)
            _bordered = bEnabled;
        अन्यथा
            SetLook(bEnabled ? B_TITLED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
    }

    व्योम _SetResizable(bool bEnabled)
    {
        अगर (_fullscreen)
            _resizable = bEnabled;
        अन्यथा {
            अगर (bEnabled) {
                SetFlags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } अन्यथा {
                SetFlags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    व्योम Set_Minimum_आकार(BMessage *संदेश)
    {
        भग्न maxHeight;
        भग्न maxWidth;
        भग्न _;
        int32 minHeight;
        int32 minWidth;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        Get_आकार_Limits(&_, &maxWidth, &_, &maxHeight);
        अगर (संदेश->FindInt32("window-w", &minWidth) != B_OK)
            वापस;
        अगर (संदेश->FindInt32("window-h", &minHeight) != B_OK)
            वापस;
        Set_आकार_Limits((भग्न)minWidth, maxWidth, (भग्न)minHeight, maxHeight);
        Update_आकार_Limits();
    }

    व्योम _Restore()
    {
        अगर (IsMinimized()) {
            Minimize(false);
        } अन्यथा अगर (IsHidden()) {
            Show();
        } अन्यथा अगर (_fullscreen) {

        } अन्यथा अगर (पूर्व_frame != शून्य) { // Zoomed
            MoveTo(पूर्व_frame->बायाँ, पूर्व_frame->शीर्ष);
            ResizeTo(पूर्व_frame->Width(), पूर्व_frame->Height());
        }
    }

    व्योम _SetFullScreen(bool fullscreen)
    {
        अगर (fullscreen != _fullscreen) {
            अगर (fullscreen) {
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
#अगर_घोषित SDL_VIDEO_OPENGL
    BGLView *_SDL_GLView;
    Uint32 _gl_type;
#पूर्ण_अगर

    int32 _last_buttons;
    int32 _id;           // Window id used by SDL_BApp
    bool _mouse_focused; // Does this window have mouse focus?
    bool _shown;
    bool _inhibit_resize;

    BRect *पूर्व_frame; // Previous position and size of the window
    bool _fullscreen;
    // valid only if fullscreen
    BRect _non_fullscreen_frame;
    bool _bordered;
    bool _resizable;

    // Framebuffer members
    BLocker *बफर_locker;
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
#पूर्ण_अगर // SDL_BWin_h_
