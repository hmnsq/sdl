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

#که_نه_تعریف_شوی SDL_BWin_h_
#تعریف_کړه SDL_BWin_h_

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

#ضمن "SDL_internal.h"
#ضمن "SDL_bframebuffer.h"

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#ضمن <stdio.h>
#ضمن <AppKit.h>
#ضمن <Cursor.h>
#ضمن <InterfaceKit.h>
#که_تعریف_شوی SDL_VIDEO_OPENGL
#ضمن <opengl/GLView.h>
#د_که_پای
#ضمن "../../core/haiku/SDL_BApp.h"

تعداد WinCommands
{
    BWIN_MOVE_کړکۍ,
    BWIN_RESIZE_کړکۍ,
    BWIN_SHOW_کړکۍ,
    BWIN_HIDE_کړکۍ,
    BWIN_MAXIMIZE_کړکۍ,
    BWIN_MINIMIZE_کړکۍ,
    BWIN_RESTORE_کړکۍ,
    BWIN_سېټ_TITLE,
    BWIN_سېټ_BORDERED,
    BWIN_سېټ_RESIZABLE,
    BWIN_FULLSCREEN,
    BWIN_UPDATE_FRAMEBUFFER,
    BWIN_MINIMUM_اندازه_کړکۍ
};

// non-OpenGL framebuffer view
class SDL_BView : عام BView
{
  عام:
    SDL_BView(BRect چوکاټ, ثابت حرف *name, uint32 resizing_ډېرپېښ)
        : BView(چوکاټ, name, resizing_ډېرپېښ, B_WILL_DRAW),
          fBitmap(عدم)
    {
    }

    فراغ Draw(BRect dirty)
    {
        إذا (fBitmap != عدم)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    فراغ سېټ_Bitmap(BBitmap *bitmap)
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
    SDL_BWin(BRect bounds, کړکۍ_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_نورمال_کړکۍ_FEEL, flags)
    {
        وروستی_buttons = 0;

        _cur_view = عدم;
        _SDL_View = عدم;

#که_تعریف_شوی SDL_VIDEO_OPENGL
        _SDL_GLView = عدم;
        _gl_type = 0;
#د_که_پای
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        prev_چوکاټ = عدم;
        _fullscreen = عدم;

        // Handle framebuffer stuff
        بفر_locker = new BLocker();
        _bitmap = عدم;
    }

    مجازي ~SDL_BWin()
    {
        قلف();

        إذا (_SDL_View != عدم && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = عدم;
        }

#که_تعریف_شوی SDL_VIDEO_OPENGL
        إذا (_SDL_GLView) {
            إذا (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->سېټ_Current_Context(عدم);
            إذا (_SDL_GLView == _cur_view)
                Remove_ماشوم(_SDL_GLView);
            _SDL_GLView = عدم;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#د_که_پای
        Unlock();

        delete prev_چوکاټ;

        // Clean up framebuffer stuff
        بفر_locker->قلف();
        delete بفر_locker;
    }

    فراغ سېټ_Current_View(BView *view)
    {
        إذا (_cur_view != view) {
            إذا (_cur_view != عدم)
                Remove_ماشوم(_cur_view);
            _cur_view = view;
            إذا (_cur_view != عدم)
                جمع_کړه_ماشوم(_cur_view);
        }
    }

    فراغ UpdateCurrentView()
    {
#که_تعریف_شوی SDL_VIDEO_OPENGL
        إذا (_SDL_GLView != عدم) {
            سېټ_Current_View(_SDL_GLView);
        } وإلا
#د_که_پای
        إذا (_SDL_View != عدم) {
            سېټ_Current_View(_SDL_View);
        } وإلا {
            سېټ_Current_View(عدم);
        }
    }

    SDL_BView *CreateView()
    {
        قلف();
        إذا (_SDL_View == عدم) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        أرجع _SDL_View;
    }

    فراغ RemoveView()
    {
        قلف();
        إذا (_SDL_View != عدم) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = عدم;
            UpdateCurrentView();
            delete oldView;
        }
        Unlock();
    }

    /* * * * * OpenGL functionality * * * * */
#که_تعریف_شوی SDL_VIDEO_OPENGL
    BGLView *CreateGLView(Uint32 gl_flags)
    {
        قلف();
        إذا (_SDL_GLView == عدم) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_چوکاټ_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        أرجع _SDL_GLView;
    }

    فراغ RemoveGLView()
    {
        قلف();
        إذا (_SDL_GLView != عدم) {
            إذا (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->سېټ_Current_Context(عدم);
            _SDL_GLView = عدم;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    فراغ بدلون_Buffers(فراغ)
    {
        _SDL_GLView->بدلون_Buffers();
    }
#د_که_پای

    /* * * * * Event sending * * * * */
    // Hook functions
    مجازي فراغ چوکاټ_Moved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage پیغام_2(BAPP_کړکۍ_MOVED);
        پیغام_2.جمع_کړه_Int32("window-x", (صحيح)origin.x);
        پیغام_2.جمع_کړه_Int32("window-y", (صحيح)origin.y);
        Post_کړکۍ_Event(پیغام_2);

        // Perform normal hook operations
        BWindow::چوکاټ_Moved(origin);
    }

    فراغ چوکاټ_Resized(عائم پلنوالی, عائم لوړوالی)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage پیغام_2(BAPP_کړکۍ_RESIZED);

        پیغام_2.جمع_کړه_Int32("window-w", (صحيح)پلنوالی + 1);
        پیغام_2.جمع_کړه_Int32("window-h", (صحيح)لوړوالی + 1);
        Post_کړکۍ_Event(پیغام_2);

        // Perform normal hook operations
        BWindow::چوکاټ_Resized(پلنوالی, لوړوالی);
    }

    bool QuitRequested()
    {
        BMessage پیغام_2(BAPP_کړکۍ_CLOSE_REQUESTED);
        Post_کړکۍ_Event(پیغام_2);

        // We won't allow a quit unless asked by DestroyWindow()
        أرجع false;
    }

    فراغ کړکۍ_Activated(bool فعال)
    {
        BMessage پیغام_2(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        پیغام_2.جمع_کړه_Bool("focusGained", فعال);
        Post_کړکۍ_Event(پیغام_2);
    }

    فراغ Zoom(BPoint origin,
              عائم پلنوالی,
              عائم لوړوالی)
    {
        BMessage پیغام_2(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        Post_کړکۍ_Event(پیغام_2);

        // Before the window zooms, record its size
        إذا (!prev_چوکاټ)
            prev_چوکاټ = new BRect(چوکاټ_2());

        // Perform normal hook operations
        BWindow::Zoom(origin, پلنوالی, لوړوالی);
    }

    // Member functions
    فراغ Show()
    {
        طالما (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage پیغام_2(BAPP_SHOW);
        Post_کړکۍ_Event(پیغام_2);
    }

    فراغ Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage پیغام_2(BAPP_HIDE);
        Post_کړکۍ_Event(پیغام_2);
    }

    فراغ Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage پیغام_2(minState);
        Post_کړکۍ_Event(پیغام_2);
    }

    فراغ Screen_بدل_شوی(BRect screen_چوکاټ, color_space ژوروالی_2)
    {
        إذا (_fullscreen) {
            Move_منزل(screen_چوکاټ.کیڼ, screen_چوکاټ.سر);
            Resize_منزل(screen_چوکاټ.پلنوالی_2(), screen_چوکاټ.لوړوالی_2());
        }
    }

    // BView message interruption
    فراغ Dispatch_پیغام(BMessage *پیغام_2, BHandler *موخه)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 کلی;     // Used for key events

        بدل (پیغام_2->what) {
        حالة B_MOUSE_MOVED:
            int32 transit;
            إذا (پیغام_2->پیدا_کړه_ټکی("where", &where) == B_OK && پیغام_2->پیدا_کړه_Int32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            اكسر;

        حالة B_MOUSE_ښکته:
            إذا (پیغام_2->پیدا_کړه_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            اكسر;

        حالة B_MOUSE_پورته:
            إذا (پیغام_2->پیدا_کړه_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            اكسر;

        حالة B_MOUSE_WHEEL_بدل_شوی:
            عائم x, y;
            إذا (پیغام_2->پیدا_کړه_Float("be:wheel_delta_x", &x) == B_OK && پیغام_2->پیدا_کړه_Float("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((صحيح)x, (صحيح)y);
            }
            اكسر;

        حالة B_کلی_ښکته:
        {
            int32 i = 0;
            int8 byte;
            int8 بایټونه[4] = { 0, 0, 0, 0 };
            طالما (i < 4 && پیغام_2->پیدا_کړه_Int8("byte", i, &byte) == B_OK) {
                بایټونه[i] = byte;
                i++;
            }
            إذا (پیغام_2->پیدا_کړه_Int32("key", &کلی) == B_OK) {
                کلی_Event_2((SDL_Scancode)کلی, &بایټونه[0], i, true);
            }
        } اكسر;

        حالة B_UNMAPPED_کلی_ښکته: // modifier keys are unmapped
            إذا (پیغام_2->پیدا_کړه_Int32("key", &کلی) == B_OK) {
                کلی_Event_2((SDL_Scancode)کلی, عدم, 0, true);
            }
            اكسر;

        حالة B_کلی_پورته:
        حالة B_UNMAPPED_کلی_پورته: // modifier keys are unmapped
            إذا (پیغام_2->پیدا_کړه_Int32("key", &کلی) == B_OK) {
                کلی_Event_2(کلی, عدم, 0, false);
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

        BWindow::Dispatch_پیغام(پیغام_2, موخه);
    }

    // Handle command messages
    فراغ پیغام_Received(BMessage *پیغام)
    {
        بدل (پیغام->what) {
        // Handle commands from SDL
        حالة BWIN_سېټ_TITLE:
            سېټ_Title(پیغام);
            اكسر;
        حالة BWIN_MOVE_کړکۍ:
            Move_منزل_2(پیغام);
            اكسر;
        حالة BWIN_RESIZE_کړکۍ:
            Resize_منزل_2(پیغام);
            اكسر;
        حالة BWIN_سېټ_BORDERED:
        {
            bool bEnabled;
            إذا (پیغام->پیدا_کړه_Bool("window-border", &bEnabled) == B_OK)
                سېټ_Bordered(bEnabled);
            اكسر;
        }
        حالة BWIN_سېټ_RESIZABLE:
        {
            bool bEnabled;
            إذا (پیغام->پیدا_کړه_Bool("window-resizable", &bEnabled) == B_OK)
                سېټ_Resizable(bEnabled);
            اكسر;
        }
        حالة BWIN_SHOW_کړکۍ:
            Show();
            اكسر;
        حالة BWIN_HIDE_کړکۍ:
            Hide();
            اكسر;
        حالة BWIN_MAXIMIZE_کړکۍ:
            BWindow::Zoom();
            اكسر;
        حالة BWIN_MINIMIZE_کړکۍ:
            Minimize(true);
            اكسر;
        حالة BWIN_RESTORE_کړکۍ:
            _Restore();
            اكسر;
        حالة BWIN_FULLSCREEN:
        {
            bool fullscreen;
            إذا (پیغام->پیدا_کړه_Bool("fullscreen", &fullscreen) == B_OK)
                سېټ_ډک_Screen(fullscreen);
            اكسر;
        }
        حالة BWIN_MINIMUM_اندازه_کړکۍ:
            سېټ_Minimum_اندازه(پیغام);
            اكسر;
        حالة BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pending_پیغام;
            طالما ((pending_پیغام = پیغام_کتار()->پیدا_کړه_پیغام(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                پیغام_کتار()->Remove_پیغام(pending_پیغام);
                delete pending_پیغام;
            }
            إذا (_bitmap != عدم) {
#که_تعریف_شوی SDL_VIDEO_OPENGL
                إذا (_SDL_GLView != عدم && _cur_view == _SDL_GLView) {
                    _SDL_GLView->Copy_Pixels_دننه(_bitmap, B_ORIGIN);
                } وإلا
#د_که_پای
                إذا (_SDL_View != عدم && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            اكسر;
        }
        افتراضي:
            // Perform normal message handling
            BWindow::پیغام_Received(پیغام);
            اكسر;
        }
    }

    // Accessor methods
    bool IsShown() { أرجع _shown; }
    int32 GetID() { أرجع _id; }
    BBitmap *GetBitmap() { أرجع _bitmap; }
    BView *GetCurView() { أرجع _cur_view; }
    SDL_BView *GetView() { أرجع _SDL_View; }
#که_تعریف_شوی SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        أرجع _SDL_GLView;
    }
    Uint32 GetGLType() { أرجع _gl_type; }
#د_که_پای

    // Setter methods
    فراغ سېټ_ID(int32 id) { _id = id; }
    فراغ قلف_بفر() { بفر_locker->قلف(); }
    فراغ Unlock_بفر() { بفر_locker->Unlock(); }
    فراغ سېټ_Bitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        إذا (_SDL_View != عدم)
            _SDL_View->سېټ_Bitmap(bitmap);
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
            BMessage پیغام_2(BAPP_MOUSE_MOVED);
            پیغام_2.جمع_کړه_Int32("x", (صحيح)where.x);
            پیغام_2.جمع_کړه_Int32("y", (صحيح)where.y);

            Post_کړکۍ_Event(پیغام_2);
        }
    }

    فراغ _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage پیغام_2(BAPP_MOUSE_FOCUS);
        پیغام_2.جمع_کړه_Bool("focusGained", focusGained);
        Post_کړکۍ_Event(پیغام_2);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    فراغ _MouseButtonEvent(int32 buttons, bool ښکته)
    {
        int32 buttonStateChange = buttons ^ وروستی_buttons;

        إذا (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_کیڼ, ښکته);
        }
        إذا (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ښی, ښکته);
        }
        إذا (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_منځ, ښکته);
        }

        وروستی_buttons = buttons;
    }

    فراغ _SendMouseButton(int32 button, bool ښکته)
    {
        BMessage پیغام_2(BAPP_MOUSE_BUTTON);
        پیغام_2.جمع_کړه_Int32("button-id", button);
        پیغام_2.جمع_کړه_Bool("button-down", ښکته);
        Post_کړکۍ_Event(پیغام_2);
    }

    فراغ _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage پیغام_2(BAPP_MOUSE_WHEEL);
        پیغام_2.جمع_کړه_Int32("xticks", x);
        پیغام_2.جمع_کړه_Int32("yticks", y);
        Post_کړکۍ_Event(پیغام_2);
    }

    فراغ کلی_Event_2(int32 کلی_کوډ, ثابت int8 *کلی_Utf8, ثابت ssize_t &len, bool ښکته)
    {
        // Create a message to pass along to the BeApp thread
        BMessage پیغام_2(BAPP_کلی);
        پیغام_2.جمع_کړه_Int32("key-scancode", کلی_کوډ);
        إذا (کلی_Utf8 != عدم) {
            پیغام_2.جمع_کړه_معلومات("key-utf8", B_INT8_TYPE, (ثابت فراغ *)کلی_Utf8, len);
        }
        پیغام_2.جمع_کړه_Bool("key-down", ښکته);
        SDL_Looper->Post_پیغام(&پیغام_2);
    }

    فراغ _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage پیغام_2(BAPP_REPAINT);
        Post_کړکۍ_Event(پیغام_2);
    }
    فراغ Post_کړکۍ_Event(BMessage &پیغام_2)
    {
        پیغام_2.جمع_کړه_Int32("window-id", _id);
        SDL_Looper->Post_پیغام(&پیغام_2);
    }

    // Command methods (functions called upon by SDL)
    فراغ سېټ_Title(BMessage *پیغام_2)
    {
        ثابت حرف *title;
        إذا (
            پیغام_2->پیدا_کړه_String("window-title", &title) != B_OK) {
            أرجع;
        }
        سېټ_Title_2(title);
    }

    فراغ Move_منزل_2(BMessage *پیغام_2)
    {
        int32 x, y;
        إذا (
            پیغام_2->پیدا_کړه_Int32("window-x", &x) != B_OK ||
            پیغام_2->پیدا_کړه_Int32("window-y", &y) != B_OK) {
            أرجع;
        }
        إذا (_fullscreen)
            non_fullscreen_چوکاټ.دننه_واټن_منزل(x, y);
        وإلا
            Move_منزل(x, y);
    }

    فراغ Resize_منزل_2(BMessage *پیغام_2)
    {
        int32 w, h;
        إذا (
            پیغام_2->پیدا_کړه_Int32("window-w", &w) != B_OK ||
            پیغام_2->پیدا_کړه_Int32("window-h", &h) != B_OK) {
            أرجع;
        }
        إذا (_fullscreen) {
            non_fullscreen_چوکاټ.ښی = non_fullscreen_چوکاټ.کیڼ + w;
            non_fullscreen_چوکاټ.bottom = non_fullscreen_چوکاټ.سر + h;
        } وإلا
            Resize_منزل(w, h);
    }

    فراغ سېټ_Bordered(bool bEnabled)
    {
        إذا (_fullscreen)
            _bordered = bEnabled;
        وإلا
            سېټ_Look(bEnabled ? B_TITLED_کړکۍ_LOOK : B_NO_BORDER_کړکۍ_LOOK);
    }

    فراغ سېټ_Resizable(bool bEnabled)
    {
        إذا (_fullscreen)
            _resizable = bEnabled;
        وإلا {
            إذا (bEnabled) {
                سېټ_Flags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } وإلا {
                سېټ_Flags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    فراغ سېټ_Minimum_اندازه(BMessage *پیغام_2)
    {
        عائم max_لوړوالی;
        عائم max_پلنوالی;
        عائم _;
        int32 min_لوړوالی;
        int32 min_پلنوالی;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        Get_اندازه_Limits(&_, &max_پلنوالی, &_, &max_لوړوالی);
        إذا (پیغام_2->پیدا_کړه_Int32("window-w", &min_پلنوالی) != B_OK)
            أرجع;
        إذا (پیغام_2->پیدا_کړه_Int32("window-h", &min_لوړوالی) != B_OK)
            أرجع;
        سېټ_اندازه_Limits((عائم)min_پلنوالی, max_پلنوالی, (عائم)min_لوړوالی, max_لوړوالی);
        Update_اندازه_Limits();
    }

    فراغ _Restore()
    {
        إذا (IsMinimized()) {
            Minimize(false);
        } وإلا إذا (IsHidden()) {
            Show();
        } وإلا إذا (_fullscreen) {

        } وإلا إذا (prev_چوکاټ != عدم) { // Zoomed
            Move_منزل(prev_چوکاټ->کیڼ, prev_چوکاټ->سر);
            Resize_منزل(prev_چوکاټ->پلنوالی_2(), prev_چوکاټ->لوړوالی_2());
        }
    }

    فراغ سېټ_ډک_Screen(bool fullscreen)
    {
        إذا (fullscreen != _fullscreen) {
            إذا (fullscreen) {
                BScreen screen(this);
                BRect screen_چوکاټ = screen.چوکاټ_2();
                _bordered = Look() != B_NO_BORDER_کړکۍ_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                non_fullscreen_چوکاټ = چوکاټ_2();
                سېټ_Bordered(false);
                سېټ_Resizable(false);
                Move_منزل(screen_چوکاټ.کیڼ, screen_چوکاټ.سر);
                Resize_منزل(screen_چوکاټ.پلنوالی_2(), screen_چوکاټ.لوړوالی_2());
                _fullscreen = fullscreen;
            } وإلا {
                _fullscreen = fullscreen;
                Move_منزل(non_fullscreen_چوکاټ.کیڼ, non_fullscreen_چوکاټ.سر);
                Resize_منزل(non_fullscreen_چوکاټ.پلنوالی_2(), non_fullscreen_چوکاټ.لوړوالی_2());
                سېټ_Bordered(_bordered);
                سېټ_Resizable(_resizable);
            }
        }
    }

    // Members

    BView *_cur_view;
    SDL_BView *_SDL_View;
#که_تعریف_شوی SDL_VIDEO_OPENGL
    BGLView *_SDL_GLView;
    Uint32 _gl_type;
#د_که_پای

    int32 وروستی_buttons;
    int32 _id;           // Window id used by SDL_BApp
    bool _mouse_focused; // Does this window have mouse focus?
    bool _shown;
    bool _inhibit_resize;

    BRect *prev_چوکاټ; // Previous position and size of the window
    bool _fullscreen;
    // valid only if fullscreen
    BRect non_fullscreen_چوکاټ;
    bool _bordered;
    bool _resizable;

    // Framebuffer members
    BLocker *بفر_locker;
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
#د_که_پای // SDL_BWin_h_
