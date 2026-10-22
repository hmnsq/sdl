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

#اگر_تعریف_نشده SDL_BWin_h_
#تعریف_کن SDL_BWin_h_

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

#ضمن "SDL_internal.h"
#ضمن "SDL_bframebuffer.h"

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#ضمن <stdio.h>
#ضمن <AppKit.h>
#ضمن <Cursor.h>
#ضمن <InterfaceKit.h>
#اگر_تعریف_شده SDL_VIDEO_OPENGL
#ضمن <opengl/GLView.h>
#پایان_اگر
#ضمن "../../core/haiku/SDL_BApp.h"

تعداد WinCommands
{
    BWIN_MOVE_پنجره,
    BWIN_RESIZE_پنجره,
    BWIN_SHOW_پنجره,
    BWIN_HIDE_پنجره,
    BWIN_MAXIMIZE_پنجره,
    BWIN_MINIMIZE_پنجره,
    BWIN_RESTORE_پنجره,
    BWIN_مجموعه_TITLE,
    BWIN_مجموعه_BORDERED,
    BWIN_مجموعه_RESIZABLE,
    BWIN_FULLSCREEN,
    BWIN_UPDATE_FRAMEBUFFER,
    BWIN_MINIMUM_اندازه_پنجره
};

// non-OpenGL framebuffer view
class SDL_BView : عام BView
{
  عام:
    SDL_BView(BRect قاب, ثابت حرف *name, uint32 resizing_نما)
        : BView(قاب, name, resizing_نما, B_WILL_DRAW),
          fBitmap(عدم)
    {
    }

    فراغ Draw(BRect dirty)
    {
        إذا (fBitmap != عدم)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    فراغ مجموعه_Bitmap(BBitmap *bitmap)
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
    SDL_BWin(BRect bounds, پنجره_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_نرمال_پنجره_FEEL, flags)
    {
        آخرین_buttons = 0;

        _cur_view = عدم;
        _SDL_View = عدم;

#اگر_تعریف_شده SDL_VIDEO_OPENGL
        _SDL_GLView = عدم;
        _gl_type = 0;
#پایان_اگر
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        prev_قاب = عدم;
        _fullscreen = عدم;

        // Handle framebuffer stuff
        میانگیر_locker = new BLocker();
        _bitmap = عدم;
    }

    مجازی ~SDL_BWin()
    {
        قفل();

        إذا (_SDL_View != عدم && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = عدم;
        }

#اگر_تعریف_شده SDL_VIDEO_OPENGL
        إذا (_SDL_GLView) {
            إذا (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->مجموعه_Current_Context(عدم);
            إذا (_SDL_GLView == _cur_view)
                Remove_فرزند(_SDL_GLView);
            _SDL_GLView = عدم;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#پایان_اگر
        Unlock();

        delete prev_قاب;

        // Clean up framebuffer stuff
        میانگیر_locker->قفل();
        delete میانگیر_locker;
    }

    فراغ مجموعه_Current_View(BView *view)
    {
        إذا (_cur_view != view) {
            إذا (_cur_view != عدم)
                Remove_فرزند(_cur_view);
            _cur_view = view;
            إذا (_cur_view != عدم)
                جمع_کن_فرزند(_cur_view);
        }
    }

    فراغ UpdateCurrentView()
    {
#اگر_تعریف_شده SDL_VIDEO_OPENGL
        إذا (_SDL_GLView != عدم) {
            مجموعه_Current_View(_SDL_GLView);
        } وإلا
#پایان_اگر
        إذا (_SDL_View != عدم) {
            مجموعه_Current_View(_SDL_View);
        } وإلا {
            مجموعه_Current_View(عدم);
        }
    }

    SDL_BView *CreateView()
    {
        قفل();
        إذا (_SDL_View == عدم) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        أرجع _SDL_View;
    }

    فراغ RemoveView()
    {
        قفل();
        إذا (_SDL_View != عدم) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = عدم;
            UpdateCurrentView();
            delete oldView;
        }
        Unlock();
    }

    /* * * * * OpenGL functionality * * * * */
#اگر_تعریف_شده SDL_VIDEO_OPENGL
    BGLView *CreateGLView(Uint32 gl_flags)
    {
        قفل();
        إذا (_SDL_GLView == عدم) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_قاب_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        أرجع _SDL_GLView;
    }

    فراغ RemoveGLView()
    {
        قفل();
        إذا (_SDL_GLView != عدم) {
            إذا (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->مجموعه_Current_Context(عدم);
            _SDL_GLView = عدم;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    فراغ جابجا_Buffers(فراغ)
    {
        _SDL_GLView->جابجا_Buffers();
    }
#پایان_اگر

    /* * * * * Event sending * * * * */
    // Hook functions
    مجازی فراغ قاب_Moved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage پیام_2(BAPP_پنجره_MOVED);
        پیام_2.جمع_کن_Int32("window-x", (صحيح)origin.x);
        پیام_2.جمع_کن_Int32("window-y", (صحيح)origin.y);
        Post_پنجره_Event(پیام_2);

        // Perform normal hook operations
        BWindow::قاب_Moved(origin);
    }

    فراغ قاب_Resized(عائم عرض, عائم ارتفاع)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage پیام_2(BAPP_پنجره_RESIZED);

        پیام_2.جمع_کن_Int32("window-w", (صحيح)عرض + 1);
        پیام_2.جمع_کن_Int32("window-h", (صحيح)ارتفاع + 1);
        Post_پنجره_Event(پیام_2);

        // Perform normal hook operations
        BWindow::قاب_Resized(عرض, ارتفاع);
    }

    bool QuitRequested()
    {
        BMessage پیام_2(BAPP_پنجره_CLOSE_REQUESTED);
        Post_پنجره_Event(پیام_2);

        // We won't allow a quit unless asked by DestroyWindow()
        أرجع false;
    }

    فراغ پنجره_Activated(bool فعال)
    {
        BMessage پیام_2(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        پیام_2.جمع_کن_Bool("focusGained", فعال);
        Post_پنجره_Event(پیام_2);
    }

    فراغ Zoom(BPoint origin,
              عائم عرض,
              عائم ارتفاع)
    {
        BMessage پیام_2(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        Post_پنجره_Event(پیام_2);

        // Before the window zooms, record its size
        إذا (!prev_قاب)
            prev_قاب = new BRect(قاب_2());

        // Perform normal hook operations
        BWindow::Zoom(origin, عرض, ارتفاع);
    }

    // Member functions
    فراغ Show()
    {
        طالما (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage پیام_2(BAPP_SHOW);
        Post_پنجره_Event(پیام_2);
    }

    فراغ Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage پیام_2(BAPP_HIDE);
        Post_پنجره_Event(پیام_2);
    }

    فراغ Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage پیام_2(minState);
        Post_پنجره_Event(پیام_2);
    }

    فراغ Screen_تغییریافته(BRect screen_قاب, color_space عمق_2)
    {
        إذا (_fullscreen) {
            Move_مقصد(screen_قاب.چپ, screen_قاب.بالاترین);
            Resize_مقصد(screen_قاب.عرض_2(), screen_قاب.ارتفاع_2());
        }
    }

    // BView message interruption
    فراغ Dispatch_پیام(BMessage *پیام_2, BHandler *هدف)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 کلید;     // Used for key events

        بدل (پیام_2->what) {
        حالة B_MOUSE_MOVED:
            int32 transit;
            إذا (پیام_2->پیدا_کن_نقطه("where", &where) == B_OK && پیام_2->پیدا_کن_Int32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            اكسر;

        حالة B_MOUSE_پایین:
            إذا (پیام_2->پیدا_کن_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            اكسر;

        حالة B_MOUSE_به_بالا:
            إذا (پیام_2->پیدا_کن_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            اكسر;

        حالة B_MOUSE_WHEEL_تغییریافته:
            عائم x, y;
            إذا (پیام_2->پیدا_کن_Float("be:wheel_delta_x", &x) == B_OK && پیام_2->پیدا_کن_Float("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((صحيح)x, (صحيح)y);
            }
            اكسر;

        حالة B_کلید_پایین:
        {
            int32 i = 0;
            int8 byte;
            int8 بایتها[4] = { 0, 0, 0, 0 };
            طالما (i < 4 && پیام_2->پیدا_کن_Int8("byte", i, &byte) == B_OK) {
                بایتها[i] = byte;
                i++;
            }
            إذا (پیام_2->پیدا_کن_Int32("key", &کلید) == B_OK) {
                کلید_Event_2((SDL_Scancode)کلید, &بایتها[0], i, true);
            }
        } اكسر;

        حالة B_UNMAPPED_کلید_پایین: // modifier keys are unmapped
            إذا (پیام_2->پیدا_کن_Int32("key", &کلید) == B_OK) {
                کلید_Event_2((SDL_Scancode)کلید, عدم, 0, true);
            }
            اكسر;

        حالة B_کلید_به_بالا:
        حالة B_UNMAPPED_کلید_به_بالا: // modifier keys are unmapped
            إذا (پیام_2->پیدا_کن_Int32("key", &کلید) == B_OK) {
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

        BWindow::Dispatch_پیام(پیام_2, هدف);
    }

    // Handle command messages
    فراغ پیام_Received(BMessage *پیام)
    {
        بدل (پیام->what) {
        // Handle commands from SDL
        حالة BWIN_مجموعه_TITLE:
            مجموعه_Title(پیام);
            اكسر;
        حالة BWIN_MOVE_پنجره:
            Move_مقصد_2(پیام);
            اكسر;
        حالة BWIN_RESIZE_پنجره:
            Resize_مقصد_2(پیام);
            اكسر;
        حالة BWIN_مجموعه_BORDERED:
        {
            bool bEnabled;
            إذا (پیام->پیدا_کن_Bool("window-border", &bEnabled) == B_OK)
                مجموعه_Bordered(bEnabled);
            اكسر;
        }
        حالة BWIN_مجموعه_RESIZABLE:
        {
            bool bEnabled;
            إذا (پیام->پیدا_کن_Bool("window-resizable", &bEnabled) == B_OK)
                مجموعه_Resizable(bEnabled);
            اكسر;
        }
        حالة BWIN_SHOW_پنجره:
            Show();
            اكسر;
        حالة BWIN_HIDE_پنجره:
            Hide();
            اكسر;
        حالة BWIN_MAXIMIZE_پنجره:
            BWindow::Zoom();
            اكسر;
        حالة BWIN_MINIMIZE_پنجره:
            Minimize(true);
            اكسر;
        حالة BWIN_RESTORE_پنجره:
            _Restore();
            اكسر;
        حالة BWIN_FULLSCREEN:
        {
            bool fullscreen;
            إذا (پیام->پیدا_کن_Bool("fullscreen", &fullscreen) == B_OK)
                مجموعه_پر_Screen(fullscreen);
            اكسر;
        }
        حالة BWIN_MINIMUM_اندازه_پنجره:
            مجموعه_Minimum_اندازه(پیام);
            اكسر;
        حالة BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pending_پیام;
            طالما ((pending_پیام = پیام_صف()->پیدا_کن_پیام(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                پیام_صف()->Remove_پیام(pending_پیام);
                delete pending_پیام;
            }
            إذا (_bitmap != عدم) {
#اگر_تعریف_شده SDL_VIDEO_OPENGL
                إذا (_SDL_GLView != عدم && _cur_view == _SDL_GLView) {
                    _SDL_GLView->Copy_Pixels_درون(_bitmap, B_ORIGIN);
                } وإلا
#پایان_اگر
                إذا (_SDL_View != عدم && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            اكسر;
        }
        افتراضي:
            // Perform normal message handling
            BWindow::پیام_Received(پیام);
            اكسر;
        }
    }

    // Accessor methods
    bool IsShown() { أرجع _shown; }
    int32 GetID() { أرجع _id; }
    BBitmap *GetBitmap() { أرجع _bitmap; }
    BView *GetCurView() { أرجع _cur_view; }
    SDL_BView *GetView() { أرجع _SDL_View; }
#اگر_تعریف_شده SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        أرجع _SDL_GLView;
    }
    Uint32 GetGLType() { أرجع _gl_type; }
#پایان_اگر

    // Setter methods
    فراغ مجموعه_ID(int32 id) { _id = id; }
    فراغ قفل_میانگیر() { میانگیر_locker->قفل(); }
    فراغ Unlock_میانگیر() { میانگیر_locker->Unlock(); }
    فراغ مجموعه_Bitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        إذا (_SDL_View != عدم)
            _SDL_View->مجموعه_Bitmap(bitmap);
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
            BMessage پیام_2(BAPP_MOUSE_MOVED);
            پیام_2.جمع_کن_Int32("x", (صحيح)where.x);
            پیام_2.جمع_کن_Int32("y", (صحيح)where.y);

            Post_پنجره_Event(پیام_2);
        }
    }

    فراغ _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage پیام_2(BAPP_MOUSE_FOCUS);
        پیام_2.جمع_کن_Bool("focusGained", focusGained);
        Post_پنجره_Event(پیام_2);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    فراغ _MouseButtonEvent(int32 buttons, bool پایین)
    {
        int32 buttonStateChange = buttons ^ آخرین_buttons;

        إذا (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_چپ, پایین);
        }
        إذا (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_راست, پایین);
        }
        إذا (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_میانه, پایین);
        }

        آخرین_buttons = buttons;
    }

    فراغ _SendMouseButton(int32 button, bool پایین)
    {
        BMessage پیام_2(BAPP_MOUSE_BUTTON);
        پیام_2.جمع_کن_Int32("button-id", button);
        پیام_2.جمع_کن_Bool("button-down", پایین);
        Post_پنجره_Event(پیام_2);
    }

    فراغ _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage پیام_2(BAPP_MOUSE_WHEEL);
        پیام_2.جمع_کن_Int32("xticks", x);
        پیام_2.جمع_کن_Int32("yticks", y);
        Post_پنجره_Event(پیام_2);
    }

    فراغ کلید_Event_2(int32 کلید_کد, ثابت int8 *کلید_Utf8, ثابت ssize_t &len, bool پایین)
    {
        // Create a message to pass along to the BeApp thread
        BMessage پیام_2(BAPP_کلید);
        پیام_2.جمع_کن_Int32("key-scancode", کلید_کد);
        إذا (کلید_Utf8 != عدم) {
            پیام_2.جمع_کن_داده("key-utf8", B_INT8_TYPE, (ثابت فراغ *)کلید_Utf8, len);
        }
        پیام_2.جمع_کن_Bool("key-down", پایین);
        SDL_Looper->Post_پیام(&پیام_2);
    }

    فراغ _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage پیام_2(BAPP_REPAINT);
        Post_پنجره_Event(پیام_2);
    }
    فراغ Post_پنجره_Event(BMessage &پیام_2)
    {
        پیام_2.جمع_کن_Int32("window-id", _id);
        SDL_Looper->Post_پیام(&پیام_2);
    }

    // Command methods (functions called upon by SDL)
    فراغ مجموعه_Title(BMessage *پیام_2)
    {
        ثابت حرف *title;
        إذا (
            پیام_2->پیدا_کن_String("window-title", &title) != B_OK) {
            أرجع;
        }
        مجموعه_Title_2(title);
    }

    فراغ Move_مقصد_2(BMessage *پیام_2)
    {
        int32 x, y;
        إذا (
            پیام_2->پیدا_کن_Int32("window-x", &x) != B_OK ||
            پیام_2->پیدا_کن_Int32("window-y", &y) != B_OK) {
            أرجع;
        }
        إذا (_fullscreen)
            non_fullscreen_قاب.جابه_جایی_مقصد(x, y);
        وإلا
            Move_مقصد(x, y);
    }

    فراغ Resize_مقصد_2(BMessage *پیام_2)
    {
        int32 w, h;
        إذا (
            پیام_2->پیدا_کن_Int32("window-w", &w) != B_OK ||
            پیام_2->پیدا_کن_Int32("window-h", &h) != B_OK) {
            أرجع;
        }
        إذا (_fullscreen) {
            non_fullscreen_قاب.راست = non_fullscreen_قاب.چپ + w;
            non_fullscreen_قاب.bottom = non_fullscreen_قاب.بالاترین + h;
        } وإلا
            Resize_مقصد(w, h);
    }

    فراغ مجموعه_Bordered(bool bEnabled)
    {
        إذا (_fullscreen)
            _bordered = bEnabled;
        وإلا
            مجموعه_Look(bEnabled ? B_TITLED_پنجره_LOOK : B_NO_BORDER_پنجره_LOOK);
    }

    فراغ مجموعه_Resizable(bool bEnabled)
    {
        إذا (_fullscreen)
            _resizable = bEnabled;
        وإلا {
            إذا (bEnabled) {
                مجموعه_Flags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } وإلا {
                مجموعه_Flags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    فراغ مجموعه_Minimum_اندازه(BMessage *پیام_2)
    {
        عائم max_ارتفاع;
        عائم max_عرض;
        عائم _;
        int32 min_ارتفاع;
        int32 min_عرض;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        Get_اندازه_Limits(&_, &max_عرض, &_, &max_ارتفاع);
        إذا (پیام_2->پیدا_کن_Int32("window-w", &min_عرض) != B_OK)
            أرجع;
        إذا (پیام_2->پیدا_کن_Int32("window-h", &min_ارتفاع) != B_OK)
            أرجع;
        مجموعه_اندازه_Limits((عائم)min_عرض, max_عرض, (عائم)min_ارتفاع, max_ارتفاع);
        Update_اندازه_Limits();
    }

    فراغ _Restore()
    {
        إذا (IsMinimized()) {
            Minimize(false);
        } وإلا إذا (IsHidden()) {
            Show();
        } وإلا إذا (_fullscreen) {

        } وإلا إذا (prev_قاب != عدم) { // Zoomed
            Move_مقصد(prev_قاب->چپ, prev_قاب->بالاترین);
            Resize_مقصد(prev_قاب->عرض_2(), prev_قاب->ارتفاع_2());
        }
    }

    فراغ مجموعه_پر_Screen(bool fullscreen)
    {
        إذا (fullscreen != _fullscreen) {
            إذا (fullscreen) {
                BScreen screen(this);
                BRect screen_قاب = screen.قاب_2();
                _bordered = Look() != B_NO_BORDER_پنجره_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                non_fullscreen_قاب = قاب_2();
                مجموعه_Bordered(false);
                مجموعه_Resizable(false);
                Move_مقصد(screen_قاب.چپ, screen_قاب.بالاترین);
                Resize_مقصد(screen_قاب.عرض_2(), screen_قاب.ارتفاع_2());
                _fullscreen = fullscreen;
            } وإلا {
                _fullscreen = fullscreen;
                Move_مقصد(non_fullscreen_قاب.چپ, non_fullscreen_قاب.بالاترین);
                Resize_مقصد(non_fullscreen_قاب.عرض_2(), non_fullscreen_قاب.ارتفاع_2());
                مجموعه_Bordered(_bordered);
                مجموعه_Resizable(_resizable);
            }
        }
    }

    // Members

    BView *_cur_view;
    SDL_BView *_SDL_View;
#اگر_تعریف_شده SDL_VIDEO_OPENGL
    BGLView *_SDL_GLView;
    Uint32 _gl_type;
#پایان_اگر

    int32 آخرین_buttons;
    int32 _id;           // Window id used by SDL_BApp
    bool _mouse_focused; // Does this window have mouse focus?
    bool _shown;
    bool _inhibit_resize;

    BRect *prev_قاب; // Previous position and size of the window
    bool _fullscreen;
    // valid only if fullscreen
    BRect non_fullscreen_قاب;
    bool _bordered;
    bool _resizable;

    // Framebuffer members
    BLocker *میانگیر_locker;
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
#پایان_اگر // SDL_BWin_h_
