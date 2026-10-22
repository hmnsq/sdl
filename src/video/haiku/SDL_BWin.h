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

#جے_بنا_تعریف SDL_BWin_h_
#تعریف_کرو SDL_BWin_h_

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

#ضمن "SDL_internal.h"
#ضمن "SDL_bframebuffer.h"

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#ضمن <stdio.h>
#ضمن <AppKit.h>
#ضمن <Cursor.h>
#ضمن <InterfaceKit.h>
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
#ضمن <opengl/GLView.h>
#جے_انت
#ضمن "../../core/haiku/SDL_BApp.h"

تعداد WinCommands
{
    BWIN_MOVE_کھڑکی,
    BWIN_RESIZE_کھڑکی,
    BWIN_SHOW_کھڑکی,
    BWIN_HIDE_کھڑکی,
    BWIN_MAXIMIZE_کھڑکی,
    BWIN_MINIMIZE_کھڑکی,
    BWIN_RESTORE_کھڑکی,
    BWIN_سیٹ_TITLE,
    BWIN_سیٹ_BORDERED,
    BWIN_سیٹ_RESIZABLE,
    BWIN_FULLSCREEN,
    BWIN_UPDATE_FRAMEBUFFER,
    BWIN_MINIMUM_ناپ_کھڑکی
};

// non-OpenGL framebuffer view
class SDL_BView : عام BView
{
  عام:
    SDL_BView(BRect چوکھٹا, ثابت حرف *name, uint32 resizing_منوال)
        : BView(چوکھٹا, name, resizing_منوال, B_WILL_DRAW),
          fBitmap(عدم)
    {
    }

    فراغ Draw(BRect dirty)
    {
        إذا (fBitmap != عدم)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    فراغ سیٹ_Bitmap(BBitmap *bitmap)
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
    SDL_BWin(BRect bounds, کھڑکی_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_عام_کھڑکی_FEEL, flags)
    {
        آخری_buttons = 0;

        _cur_view = عدم;
        _SDL_View = عدم;

#جے_تعریف_شدہ SDL_VIDEO_OPENGL
        _SDL_GLView = عدم;
        _gl_type = 0;
#جے_انت
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        prev_چوکھٹا = عدم;
        _fullscreen = عدم;

        // Handle framebuffer stuff
        بفر_locker = new BLocker();
        _bitmap = عدم;
    }

    مجازی ~SDL_BWin()
    {
        جندرا();

        إذا (_SDL_View != عدم && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = عدم;
        }

#جے_تعریف_شدہ SDL_VIDEO_OPENGL
        إذا (_SDL_GLView) {
            إذا (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->سیٹ_Current_Context(عدم);
            إذا (_SDL_GLView == _cur_view)
                Remove_بچہ(_SDL_GLView);
            _SDL_GLView = عدم;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#جے_انت
        Unlock();

        delete prev_چوکھٹا;

        // Clean up framebuffer stuff
        بفر_locker->جندرا();
        delete بفر_locker;
    }

    فراغ سیٹ_Current_View(BView *view)
    {
        إذا (_cur_view != view) {
            إذا (_cur_view != عدم)
                Remove_بچہ(_cur_view);
            _cur_view = view;
            إذا (_cur_view != عدم)
                جوڑو_بچہ(_cur_view);
        }
    }

    فراغ UpdateCurrentView()
    {
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
        إذا (_SDL_GLView != عدم) {
            سیٹ_Current_View(_SDL_GLView);
        } وإلا
#جے_انت
        إذا (_SDL_View != عدم) {
            سیٹ_Current_View(_SDL_View);
        } وإلا {
            سیٹ_Current_View(عدم);
        }
    }

    SDL_BView *CreateView()
    {
        جندرا();
        إذا (_SDL_View == عدم) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        أرجع _SDL_View;
    }

    فراغ RemoveView()
    {
        جندرا();
        إذا (_SDL_View != عدم) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = عدم;
            UpdateCurrentView();
            delete oldView;
        }
        Unlock();
    }

    /* * * * * OpenGL functionality * * * * */
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
    BGLView *CreateGLView(Uint32 gl_flags)
    {
        جندرا();
        إذا (_SDL_GLView == عدم) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_چوکھٹا_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        أرجع _SDL_GLView;
    }

    فراغ RemoveGLView()
    {
        جندرا();
        إذا (_SDL_GLView != عدم) {
            إذا (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->سیٹ_Current_Context(عدم);
            _SDL_GLView = عدم;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    فراغ وٹاندرا_Buffers(فراغ)
    {
        _SDL_GLView->وٹاندرا_Buffers();
    }
#جے_انت

    /* * * * * Event sending * * * * */
    // Hook functions
    مجازی فراغ چوکھٹا_Moved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage پیغام(BAPP_کھڑکی_MOVED);
        پیغام.جوڑو_Int32("window-x", (صحيح)origin.x);
        پیغام.جوڑو_Int32("window-y", (صحيح)origin.y);
        Post_کھڑکی_Event(پیغام);

        // Perform normal hook operations
        BWindow::چوکھٹا_Moved(origin);
    }

    فراغ چوکھٹا_Resized(عائم چوڑائی, عائم اچائی)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage پیغام(BAPP_کھڑکی_RESIZED);

        پیغام.جوڑو_Int32("window-w", (صحيح)چوڑائی + 1);
        پیغام.جوڑو_Int32("window-h", (صحيح)اچائی + 1);
        Post_کھڑکی_Event(پیغام);

        // Perform normal hook operations
        BWindow::چوکھٹا_Resized(چوڑائی, اچائی);
    }

    bool QuitRequested()
    {
        BMessage پیغام(BAPP_کھڑکی_CLOSE_REQUESTED);
        Post_کھڑکی_Event(پیغام);

        // We won't allow a quit unless asked by DestroyWindow()
        أرجع false;
    }

    فراغ کھڑکی_Activated(bool سرگرم)
    {
        BMessage پیغام(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        پیغام.جوڑو_Bool("focusGained", سرگرم);
        Post_کھڑکی_Event(پیغام);
    }

    فراغ Zoom(BPoint origin,
              عائم چوڑائی,
              عائم اچائی)
    {
        BMessage پیغام(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        Post_کھڑکی_Event(پیغام);

        // Before the window zooms, record its size
        إذا (!prev_چوکھٹا)
            prev_چوکھٹا = new BRect(چوکھٹا_2());

        // Perform normal hook operations
        BWindow::Zoom(origin, چوڑائی, اچائی);
    }

    // Member functions
    فراغ Show()
    {
        طالما (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage پیغام(BAPP_SHOW);
        Post_کھڑکی_Event(پیغام);
    }

    فراغ Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage پیغام(BAPP_HIDE);
        Post_کھڑکی_Event(پیغام);
    }

    فراغ Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage پیغام(minState);
        Post_کھڑکی_Event(پیغام);
    }

    فراغ Screen_بدلیا(BRect screen_چوکھٹا, color_space ڈونگھائی_2)
    {
        إذا (_fullscreen) {
            Move_منزل(screen_چوکھٹا.بایاں, screen_چوکھٹا.چوٹی);
            Resize_منزل(screen_چوکھٹا.چوڑائی_2(), screen_چوکھٹا.اچائی_2());
        }
    }

    // BView message interruption
    فراغ Dispatch_سنیہا(BMessage *پیغام, BHandler *نشانہ)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 کلید;     // Used for key events

        بدل (پیغام->what) {
        حالة B_MOUSE_MOVED:
            int32 transit;
            إذا (پیغام->لبھو_نقطہ("where", &where) == B_OK && پیغام->لبھو_Int32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            اكسر;

        حالة B_MOUSE_تھلے:
            إذا (پیغام->لبھو_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            اكسر;

        حالة B_MOUSE_اتے:
            إذا (پیغام->لبھو_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            اكسر;

        حالة B_MOUSE_WHEEL_بدلیا:
            عائم x, y;
            إذا (پیغام->لبھو_Float("be:wheel_delta_x", &x) == B_OK && پیغام->لبھو_Float("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((صحيح)x, (صحيح)y);
            }
            اكسر;

        حالة B_کلید_تھلے:
        {
            int32 i = 0;
            int8 byte;
            int8 بائٹاں[4] = { 0, 0, 0, 0 };
            طالما (i < 4 && پیغام->لبھو_Int8("byte", i, &byte) == B_OK) {
                بائٹاں[i] = byte;
                i++;
            }
            إذا (پیغام->لبھو_Int32("key", &کلید) == B_OK) {
                کلید_Event_2((SDL_Scancode)کلید, &بائٹاں[0], i, true);
            }
        } اكسر;

        حالة B_UNMAPPED_کلید_تھلے: // modifier keys are unmapped
            إذا (پیغام->لبھو_Int32("key", &کلید) == B_OK) {
                کلید_Event_2((SDL_Scancode)کلید, عدم, 0, true);
            }
            اكسر;

        حالة B_کلید_اتے:
        حالة B_UNMAPPED_کلید_اتے: // modifier keys are unmapped
            إذا (پیغام->لبھو_Int32("key", &کلید) == B_OK) {
                کلید_Event_2(کلید, عدم, 0, false);
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

        BWindow::Dispatch_سنیہا(پیغام, نشانہ);
    }

    // Handle command messages
    فراغ سنیہا_Received(BMessage *سنیہا)
    {
        بدل (سنیہا->what) {
        // Handle commands from SDL
        حالة BWIN_سیٹ_TITLE:
            سیٹ_Title(سنیہا);
            اكسر;
        حالة BWIN_MOVE_کھڑکی:
            Move_منزل_2(سنیہا);
            اكسر;
        حالة BWIN_RESIZE_کھڑکی:
            Resize_منزل_2(سنیہا);
            اكسر;
        حالة BWIN_سیٹ_BORDERED:
        {
            bool bEnabled;
            إذا (سنیہا->لبھو_Bool("window-border", &bEnabled) == B_OK)
                سیٹ_Bordered(bEnabled);
            اكسر;
        }
        حالة BWIN_سیٹ_RESIZABLE:
        {
            bool bEnabled;
            إذا (سنیہا->لبھو_Bool("window-resizable", &bEnabled) == B_OK)
                سیٹ_Resizable(bEnabled);
            اكسر;
        }
        حالة BWIN_SHOW_کھڑکی:
            Show();
            اكسر;
        حالة BWIN_HIDE_کھڑکی:
            Hide();
            اكسر;
        حالة BWIN_MAXIMIZE_کھڑکی:
            BWindow::Zoom();
            اكسر;
        حالة BWIN_MINIMIZE_کھڑکی:
            Minimize(true);
            اكسر;
        حالة BWIN_RESTORE_کھڑکی:
            _Restore();
            اكسر;
        حالة BWIN_FULLSCREEN:
        {
            bool fullscreen;
            إذا (سنیہا->لبھو_Bool("fullscreen", &fullscreen) == B_OK)
                سیٹ_بھریا_Screen(fullscreen);
            اكسر;
        }
        حالة BWIN_MINIMUM_ناپ_کھڑکی:
            سیٹ_Minimum_ناپ(سنیہا);
            اكسر;
        حالة BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pending_سنیہا;
            طالما ((pending_سنیہا = سنیہا_قطار()->لبھو_سنیہا(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                سنیہا_قطار()->Remove_سنیہا(pending_سنیہا);
                delete pending_سنیہا;
            }
            إذا (_bitmap != عدم) {
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
                إذا (_SDL_GLView != عدم && _cur_view == _SDL_GLView) {
                    _SDL_GLView->Copy_Pixels_وچ(_bitmap, B_ORIGIN);
                } وإلا
#جے_انت
                إذا (_SDL_View != عدم && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            اكسر;
        }
        افتراضي:
            // Perform normal message handling
            BWindow::سنیہا_Received(سنیہا);
            اكسر;
        }
    }

    // Accessor methods
    bool IsShown() { أرجع _shown; }
    int32 GetID() { أرجع _id; }
    BBitmap *GetBitmap() { أرجع _bitmap; }
    BView *GetCurView() { أرجع _cur_view; }
    SDL_BView *GetView() { أرجع _SDL_View; }
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        أرجع _SDL_GLView;
    }
    Uint32 GetGLType() { أرجع _gl_type; }
#جے_انت

    // Setter methods
    فراغ سیٹ_ID(int32 id) { _id = id; }
    فراغ جندرا_بفر() { بفر_locker->جندرا(); }
    فراغ Unlock_بفر() { بفر_locker->Unlock(); }
    فراغ سیٹ_Bitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        إذا (_SDL_View != عدم)
            _SDL_View->سیٹ_Bitmap(bitmap);
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
            BMessage پیغام(BAPP_MOUSE_MOVED);
            پیغام.جوڑو_Int32("x", (صحيح)where.x);
            پیغام.جوڑو_Int32("y", (صحيح)where.y);

            Post_کھڑکی_Event(پیغام);
        }
    }

    فراغ _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage پیغام(BAPP_MOUSE_FOCUS);
        پیغام.جوڑو_Bool("focusGained", focusGained);
        Post_کھڑکی_Event(پیغام);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    فراغ _MouseButtonEvent(int32 buttons, bool تھلے)
    {
        int32 buttonStateChange = buttons ^ آخری_buttons;

        إذا (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_بایاں, تھلے);
        }
        إذا (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_دایاں, تھلے);
        }
        إذا (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_درمیان, تھلے);
        }

        آخری_buttons = buttons;
    }

    فراغ _SendMouseButton(int32 button, bool تھلے)
    {
        BMessage پیغام(BAPP_MOUSE_BUTTON);
        پیغام.جوڑو_Int32("button-id", button);
        پیغام.جوڑو_Bool("button-down", تھلے);
        Post_کھڑکی_Event(پیغام);
    }

    فراغ _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage پیغام(BAPP_MOUSE_WHEEL);
        پیغام.جوڑو_Int32("xticks", x);
        پیغام.جوڑو_Int32("yticks", y);
        Post_کھڑکی_Event(پیغام);
    }

    فراغ کلید_Event_2(int32 کلید_کوڈ, ثابت int8 *کلید_Utf8, ثابت ssize_t &len, bool تھلے)
    {
        // Create a message to pass along to the BeApp thread
        BMessage پیغام(BAPP_کلید);
        پیغام.جوڑو_Int32("key-scancode", کلید_کوڈ);
        إذا (کلید_Utf8 != عدم) {
            پیغام.جوڑو_انکڑے("key-utf8", B_INT8_TYPE, (ثابت فراغ *)کلید_Utf8, len);
        }
        پیغام.جوڑو_Bool("key-down", تھلے);
        SDL_Looper->Post_سنیہا(&پیغام);
    }

    فراغ _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage پیغام(BAPP_REPAINT);
        Post_کھڑکی_Event(پیغام);
    }
    فراغ Post_کھڑکی_Event(BMessage &پیغام)
    {
        پیغام.جوڑو_Int32("window-id", _id);
        SDL_Looper->Post_سنیہا(&پیغام);
    }

    // Command methods (functions called upon by SDL)
    فراغ سیٹ_Title(BMessage *پیغام)
    {
        ثابت حرف *title;
        إذا (
            پیغام->لبھو_String("window-title", &title) != B_OK) {
            أرجع;
        }
        سیٹ_Title_2(title);
    }

    فراغ Move_منزل_2(BMessage *پیغام)
    {
        int32 x, y;
        إذا (
            پیغام->لبھو_Int32("window-x", &x) != B_OK ||
            پیغام->لبھو_Int32("window-y", &y) != B_OK) {
            أرجع;
        }
        إذا (_fullscreen)
            non_fullscreen_چوکھٹا.وتھ_منزل(x, y);
        وإلا
            Move_منزل(x, y);
    }

    فراغ Resize_منزل_2(BMessage *پیغام)
    {
        int32 w, h;
        إذا (
            پیغام->لبھو_Int32("window-w", &w) != B_OK ||
            پیغام->لبھو_Int32("window-h", &h) != B_OK) {
            أرجع;
        }
        إذا (_fullscreen) {
            non_fullscreen_چوکھٹا.دایاں = non_fullscreen_چوکھٹا.بایاں + w;
            non_fullscreen_چوکھٹا.bottom = non_fullscreen_چوکھٹا.چوٹی + h;
        } وإلا
            Resize_منزل(w, h);
    }

    فراغ سیٹ_Bordered(bool bEnabled)
    {
        إذا (_fullscreen)
            _bordered = bEnabled;
        وإلا
            سیٹ_Look(bEnabled ? B_TITLED_کھڑکی_LOOK : B_NO_BORDER_کھڑکی_LOOK);
    }

    فراغ سیٹ_Resizable(bool bEnabled)
    {
        إذا (_fullscreen)
            _resizable = bEnabled;
        وإلا {
            إذا (bEnabled) {
                سیٹ_Flags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } وإلا {
                سیٹ_Flags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    فراغ سیٹ_Minimum_ناپ(BMessage *پیغام)
    {
        عائم max_اچائی;
        عائم max_چوڑائی;
        عائم _;
        int32 min_اچائی;
        int32 min_چوڑائی;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        Get_ناپ_Limits(&_, &max_چوڑائی, &_, &max_اچائی);
        إذا (پیغام->لبھو_Int32("window-w", &min_چوڑائی) != B_OK)
            أرجع;
        إذا (پیغام->لبھو_Int32("window-h", &min_اچائی) != B_OK)
            أرجع;
        سیٹ_ناپ_Limits((عائم)min_چوڑائی, max_چوڑائی, (عائم)min_اچائی, max_اچائی);
        Update_ناپ_Limits();
    }

    فراغ _Restore()
    {
        إذا (IsMinimized()) {
            Minimize(false);
        } وإلا إذا (IsHidden()) {
            Show();
        } وإلا إذا (_fullscreen) {

        } وإلا إذا (prev_چوکھٹا != عدم) { // Zoomed
            Move_منزل(prev_چوکھٹا->بایاں, prev_چوکھٹا->چوٹی);
            Resize_منزل(prev_چوکھٹا->چوڑائی_2(), prev_چوکھٹا->اچائی_2());
        }
    }

    فراغ سیٹ_بھریا_Screen(bool fullscreen)
    {
        إذا (fullscreen != _fullscreen) {
            إذا (fullscreen) {
                BScreen screen(this);
                BRect screen_چوکھٹا = screen.چوکھٹا_2();
                _bordered = Look() != B_NO_BORDER_کھڑکی_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                non_fullscreen_چوکھٹا = چوکھٹا_2();
                سیٹ_Bordered(false);
                سیٹ_Resizable(false);
                Move_منزل(screen_چوکھٹا.بایاں, screen_چوکھٹا.چوٹی);
                Resize_منزل(screen_چوکھٹا.چوڑائی_2(), screen_چوکھٹا.اچائی_2());
                _fullscreen = fullscreen;
            } وإلا {
                _fullscreen = fullscreen;
                Move_منزل(non_fullscreen_چوکھٹا.بایاں, non_fullscreen_چوکھٹا.چوٹی);
                Resize_منزل(non_fullscreen_چوکھٹا.چوڑائی_2(), non_fullscreen_چوکھٹا.اچائی_2());
                سیٹ_Bordered(_bordered);
                سیٹ_Resizable(_resizable);
            }
        }
    }

    // Members

    BView *_cur_view;
    SDL_BView *_SDL_View;
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
    BGLView *_SDL_GLView;
    Uint32 _gl_type;
#جے_انت

    int32 آخری_buttons;
    int32 _id;           // Window id used by SDL_BApp
    bool _mouse_focused; // Does this window have mouse focus?
    bool _shown;
    bool _inhibit_resize;

    BRect *prev_چوکھٹا; // Previous position and size of the window
    bool _fullscreen;
    // valid only if fullscreen
    BRect non_fullscreen_چوکھٹا;
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
#جے_انت // SDL_BWin_h_
