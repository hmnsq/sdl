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

#جيڪڏهن_وصف_نه_ٿيل SDL_BWin_h_
#وصف_ڪريو SDL_BWin_h_

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

#ضمن "SDL_internal.h"
#ضمن "SDL_bframebuffer.h"

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#ضمن <stdio.h>
#ضمن <AppKit.h>
#ضمن <Cursor.h>
#ضمن <InterfaceKit.h>
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
#ضمن <opengl/GLView.h>
#جيڪڏهن_پورو
#ضمن "../../core/haiku/SDL_BApp.h"

تعداد WinCommands
{
    BWIN_MOVE_دري,
    BWIN_RESIZE_دري,
    BWIN_SHOW_دري,
    BWIN_HIDE_دري,
    BWIN_MAXIMIZE_دري,
    BWIN_MINIMIZE_دري,
    BWIN_RESTORE_دري,
    BWIN_سيٽ_TITLE,
    BWIN_سيٽ_BORDERED,
    BWIN_سيٽ_RESIZABLE,
    BWIN_FULLSCREEN,
    BWIN_UPDATE_FRAMEBUFFER,
    BWIN_MINIMUM_سائيز_دري
};

// non-OpenGL framebuffer view
class SDL_BView : عام BView
{
  عام:
    SDL_BView(BRect چوکٺو, ثابت حرف *name, uint32 resizing_گهڻائي)
        : BView(چوکٺو, name, resizing_گهڻائي, B_WILL_DRAW),
          fBitmap(عدم)
    {
    }

    فراغ Draw(BRect dirty)
    {
        إذا (fBitmap != عدم)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    فراغ سيٽ_Bitmap(BBitmap *bitmap)
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
    SDL_BWin(BRect bounds, دري_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_عام_دري_FEEL, flags)
    {
        آخري_buttons = 0;

        _cur_view = عدم;
        _SDL_View = عدم;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
        _SDL_GLView = عدم;
        _gl_type = 0;
#جيڪڏهن_پورو
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        prev_چوکٺو = عدم;
        _fullscreen = عدم;

        // Handle framebuffer stuff
        بفر_locker = new BLocker();
        _bitmap = عدم;
    }

    مجازي ~SDL_BWin()
    {
        تالو();

        إذا (_SDL_View != عدم && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = عدم;
        }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
        إذا (_SDL_GLView) {
            إذا (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->سيٽ_Current_Context(عدم);
            إذا (_SDL_GLView == _cur_view)
                Remove_ٻار(_SDL_GLView);
            _SDL_GLView = عدم;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#جيڪڏهن_پورو
        Unlock();

        delete prev_چوکٺو;

        // Clean up framebuffer stuff
        بفر_locker->تالو();
        delete بفر_locker;
    }

    فراغ سيٽ_Current_View(BView *view)
    {
        إذا (_cur_view != view) {
            إذا (_cur_view != عدم)
                Remove_ٻار(_cur_view);
            _cur_view = view;
            إذا (_cur_view != عدم)
                جوڙيو_ٻار(_cur_view);
        }
    }

    فراغ UpdateCurrentView()
    {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
        إذا (_SDL_GLView != عدم) {
            سيٽ_Current_View(_SDL_GLView);
        } وإلا
#جيڪڏهن_پورو
        إذا (_SDL_View != عدم) {
            سيٽ_Current_View(_SDL_View);
        } وإلا {
            سيٽ_Current_View(عدم);
        }
    }

    SDL_BView *CreateView()
    {
        تالو();
        إذا (_SDL_View == عدم) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        أرجع _SDL_View;
    }

    فراغ RemoveView()
    {
        تالو();
        إذا (_SDL_View != عدم) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = عدم;
            UpdateCurrentView();
            delete oldView;
        }
        Unlock();
    }

    /* * * * * OpenGL functionality * * * * */
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
    BGLView *CreateGLView(Uint32 gl_flags)
    {
        تالو();
        إذا (_SDL_GLView == عدم) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_چوکٺو_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        أرجع _SDL_GLView;
    }

    فراغ RemoveGLView()
    {
        تالو();
        إذا (_SDL_GLView != عدم) {
            إذا (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->سيٽ_Current_Context(عدم);
            _SDL_GLView = عدم;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    فراغ مٽا_سٽا_Buffers(فراغ)
    {
        _SDL_GLView->مٽا_سٽا_Buffers();
    }
#جيڪڏهن_پورو

    /* * * * * Event sending * * * * */
    // Hook functions
    مجازي فراغ چوکٺو_Moved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage نياپو(BAPP_دري_MOVED);
        نياپو.جوڙيو_Int32("window-x", (صحيح)origin.x);
        نياپو.جوڙيو_Int32("window-y", (صحيح)origin.y);
        Post_دري_Event(نياپو);

        // Perform normal hook operations
        BWindow::چوکٺو_Moved(origin);
    }

    فراغ چوکٺو_Resized(عائم ويڪر, عائم اوچائي)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage نياپو(BAPP_دري_RESIZED);

        نياپو.جوڙيو_Int32("window-w", (صحيح)ويڪر + 1);
        نياپو.جوڙيو_Int32("window-h", (صحيح)اوچائي + 1);
        Post_دري_Event(نياپو);

        // Perform normal hook operations
        BWindow::چوکٺو_Resized(ويڪر, اوچائي);
    }

    bool QuitRequested()
    {
        BMessage نياپو(BAPP_دري_CLOSE_REQUESTED);
        Post_دري_Event(نياپو);

        // We won't allow a quit unless asked by DestroyWindow()
        أرجع false;
    }

    فراغ دري_Activated(bool سرگرم)
    {
        BMessage نياپو(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        نياپو.جوڙيو_Bool("focusGained", سرگرم);
        Post_دري_Event(نياپو);
    }

    فراغ Zoom(BPoint origin,
              عائم ويڪر,
              عائم اوچائي)
    {
        BMessage نياپو(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        Post_دري_Event(نياپو);

        // Before the window zooms, record its size
        إذا (!prev_چوکٺو)
            prev_چوکٺو = new BRect(چوکٺو_2());

        // Perform normal hook operations
        BWindow::Zoom(origin, ويڪر, اوچائي);
    }

    // Member functions
    فراغ Show()
    {
        طالما (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage نياپو(BAPP_SHOW);
        Post_دري_Event(نياپو);
    }

    فراغ Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage نياپو(BAPP_HIDE);
        Post_دري_Event(نياپو);
    }

    فراغ Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage نياپو(minState);
        Post_دري_Event(نياپو);
    }

    فراغ Screen_بدليو(BRect screen_چوکٺو, color_space اونهائي_2)
    {
        إذا (_fullscreen) {
            Move_منزل(screen_چوکٺو.کاٻو, screen_چوکٺو.چوٽي);
            Resize_منزل(screen_چوکٺو.ويڪر_2(), screen_چوکٺو.اوچائي_2());
        }
    }

    // BView message interruption
    فراغ Dispatch_پيغام(BMessage *نياپو, BHandler *هدف)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 ڪنجي;     // Used for key events

        بدل (نياپو->what) {
        حالة B_MOUSE_MOVED:
            int32 transit;
            إذا (نياپو->ڳوليو_نقطو("where", &where) == B_OK && نياپو->ڳوليو_Int32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            اكسر;

        حالة B_MOUSE_هيٺ_ڏانهن:
            إذا (نياپو->ڳوليو_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            اكسر;

        حالة B_MOUSE_مٿي:
            إذا (نياپو->ڳوليو_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            اكسر;

        حالة B_MOUSE_WHEEL_بدليو:
            عائم x, y;
            إذا (نياپو->ڳوليو_Float("be:wheel_delta_x", &x) == B_OK && نياپو->ڳوليو_Float("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((صحيح)x, (صحيح)y);
            }
            اكسر;

        حالة B_ڪنجي_هيٺ_ڏانهن:
        {
            int32 i = 0;
            int8 byte;
            int8 بائيٽون[4] = { 0, 0, 0, 0 };
            طالما (i < 4 && نياپو->ڳوليو_Int8("byte", i, &byte) == B_OK) {
                بائيٽون[i] = byte;
                i++;
            }
            إذا (نياپو->ڳوليو_Int32("key", &ڪنجي) == B_OK) {
                ڪنجي_Event_2((SDL_Scancode)ڪنجي, &بائيٽون[0], i, true);
            }
        } اكسر;

        حالة B_UNMAPPED_ڪنجي_هيٺ_ڏانهن: // modifier keys are unmapped
            إذا (نياپو->ڳوليو_Int32("key", &ڪنجي) == B_OK) {
                ڪنجي_Event_2((SDL_Scancode)ڪنجي, عدم, 0, true);
            }
            اكسر;

        حالة B_ڪنجي_مٿي:
        حالة B_UNMAPPED_ڪنجي_مٿي: // modifier keys are unmapped
            إذا (نياپو->ڳوليو_Int32("key", &ڪنجي) == B_OK) {
                ڪنجي_Event_2(ڪنجي, عدم, 0, false);
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

        BWindow::Dispatch_پيغام(نياپو, هدف);
    }

    // Handle command messages
    فراغ پيغام_Received(BMessage *پيغام)
    {
        بدل (پيغام->what) {
        // Handle commands from SDL
        حالة BWIN_سيٽ_TITLE:
            سيٽ_Title(پيغام);
            اكسر;
        حالة BWIN_MOVE_دري:
            Move_منزل_2(پيغام);
            اكسر;
        حالة BWIN_RESIZE_دري:
            Resize_منزل_2(پيغام);
            اكسر;
        حالة BWIN_سيٽ_BORDERED:
        {
            bool bEnabled;
            إذا (پيغام->ڳوليو_Bool("window-border", &bEnabled) == B_OK)
                سيٽ_Bordered(bEnabled);
            اكسر;
        }
        حالة BWIN_سيٽ_RESIZABLE:
        {
            bool bEnabled;
            إذا (پيغام->ڳوليو_Bool("window-resizable", &bEnabled) == B_OK)
                سيٽ_Resizable(bEnabled);
            اكسر;
        }
        حالة BWIN_SHOW_دري:
            Show();
            اكسر;
        حالة BWIN_HIDE_دري:
            Hide();
            اكسر;
        حالة BWIN_MAXIMIZE_دري:
            BWindow::Zoom();
            اكسر;
        حالة BWIN_MINIMIZE_دري:
            Minimize(true);
            اكسر;
        حالة BWIN_RESTORE_دري:
            _Restore();
            اكسر;
        حالة BWIN_FULLSCREEN:
        {
            bool fullscreen;
            إذا (پيغام->ڳوليو_Bool("fullscreen", &fullscreen) == B_OK)
                سيٽ_ڀريل_Screen(fullscreen);
            اكسر;
        }
        حالة BWIN_MINIMUM_سائيز_دري:
            سيٽ_Minimum_سائيز(پيغام);
            اكسر;
        حالة BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pending_پيغام;
            طالما ((pending_پيغام = پيغام_قطار()->ڳوليو_پيغام(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                پيغام_قطار()->Remove_پيغام(pending_پيغام);
                delete pending_پيغام;
            }
            إذا (_bitmap != عدم) {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
                إذا (_SDL_GLView != عدم && _cur_view == _SDL_GLView) {
                    _SDL_GLView->Copy_Pixels_اندريون(_bitmap, B_ORIGIN);
                } وإلا
#جيڪڏهن_پورو
                إذا (_SDL_View != عدم && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            اكسر;
        }
        افتراضي:
            // Perform normal message handling
            BWindow::پيغام_Received(پيغام);
            اكسر;
        }
    }

    // Accessor methods
    bool IsShown() { أرجع _shown; }
    int32 GetID() { أرجع _id; }
    BBitmap *GetBitmap() { أرجع _bitmap; }
    BView *GetCurView() { أرجع _cur_view; }
    SDL_BView *GetView() { أرجع _SDL_View; }
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        أرجع _SDL_GLView;
    }
    Uint32 GetGLType() { أرجع _gl_type; }
#جيڪڏهن_پورو

    // Setter methods
    فراغ سيٽ_ID(int32 id) { _id = id; }
    فراغ تالو_بفر() { بفر_locker->تالو(); }
    فراغ Unlock_بفر() { بفر_locker->Unlock(); }
    فراغ سيٽ_Bitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        إذا (_SDL_View != عدم)
            _SDL_View->سيٽ_Bitmap(bitmap);
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
            BMessage نياپو(BAPP_MOUSE_MOVED);
            نياپو.جوڙيو_Int32("x", (صحيح)where.x);
            نياپو.جوڙيو_Int32("y", (صحيح)where.y);

            Post_دري_Event(نياپو);
        }
    }

    فراغ _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage نياپو(BAPP_MOUSE_FOCUS);
        نياپو.جوڙيو_Bool("focusGained", focusGained);
        Post_دري_Event(نياپو);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    فراغ _MouseButtonEvent(int32 buttons, bool هيٺ_ڏانهن)
    {
        int32 buttonStateChange = buttons ^ آخري_buttons;

        إذا (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_کاٻو, هيٺ_ڏانهن);
        }
        إذا (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_ساڄو, هيٺ_ڏانهن);
        }
        إذا (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_وچ, هيٺ_ڏانهن);
        }

        آخري_buttons = buttons;
    }

    فراغ _SendMouseButton(int32 button, bool هيٺ_ڏانهن)
    {
        BMessage نياپو(BAPP_MOUSE_BUTTON);
        نياپو.جوڙيو_Int32("button-id", button);
        نياپو.جوڙيو_Bool("button-down", هيٺ_ڏانهن);
        Post_دري_Event(نياپو);
    }

    فراغ _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage نياپو(BAPP_MOUSE_WHEEL);
        نياپو.جوڙيو_Int32("xticks", x);
        نياپو.جوڙيو_Int32("yticks", y);
        Post_دري_Event(نياپو);
    }

    فراغ ڪنجي_Event_2(int32 ڪنجي_ڪوڊ, ثابت int8 *ڪنجي_Utf8, ثابت ssize_t &len, bool هيٺ_ڏانهن)
    {
        // Create a message to pass along to the BeApp thread
        BMessage نياپو(BAPP_ڪنجي);
        نياپو.جوڙيو_Int32("key-scancode", ڪنجي_ڪوڊ);
        إذا (ڪنجي_Utf8 != عدم) {
            نياپو.جوڙيو_معلومات("key-utf8", B_INT8_TYPE, (ثابت فراغ *)ڪنجي_Utf8, len);
        }
        نياپو.جوڙيو_Bool("key-down", هيٺ_ڏانهن);
        SDL_Looper->Post_پيغام(&نياپو);
    }

    فراغ _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage نياپو(BAPP_REPAINT);
        Post_دري_Event(نياپو);
    }
    فراغ Post_دري_Event(BMessage &نياپو)
    {
        نياپو.جوڙيو_Int32("window-id", _id);
        SDL_Looper->Post_پيغام(&نياپو);
    }

    // Command methods (functions called upon by SDL)
    فراغ سيٽ_Title(BMessage *نياپو)
    {
        ثابت حرف *title;
        إذا (
            نياپو->ڳوليو_String("window-title", &title) != B_OK) {
            أرجع;
        }
        سيٽ_Title_2(title);
    }

    فراغ Move_منزل_2(BMessage *نياپو)
    {
        int32 x, y;
        إذا (
            نياپو->ڳوليو_Int32("window-x", &x) != B_OK ||
            نياپو->ڳوليو_Int32("window-y", &y) != B_OK) {
            أرجع;
        }
        إذا (_fullscreen)
            non_fullscreen_چوکٺو.وٿي_منزل(x, y);
        وإلا
            Move_منزل(x, y);
    }

    فراغ Resize_منزل_2(BMessage *نياپو)
    {
        int32 w, h;
        إذا (
            نياپو->ڳوليو_Int32("window-w", &w) != B_OK ||
            نياپو->ڳوليو_Int32("window-h", &h) != B_OK) {
            أرجع;
        }
        إذا (_fullscreen) {
            non_fullscreen_چوکٺو.ساڄو = non_fullscreen_چوکٺو.کاٻو + w;
            non_fullscreen_چوکٺو.bottom = non_fullscreen_چوکٺو.چوٽي + h;
        } وإلا
            Resize_منزل(w, h);
    }

    فراغ سيٽ_Bordered(bool bEnabled)
    {
        إذا (_fullscreen)
            _bordered = bEnabled;
        وإلا
            سيٽ_Look(bEnabled ? B_TITLED_دري_LOOK : B_NO_BORDER_دري_LOOK);
    }

    فراغ سيٽ_Resizable(bool bEnabled)
    {
        إذا (_fullscreen)
            _resizable = bEnabled;
        وإلا {
            إذا (bEnabled) {
                سيٽ_Flags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } وإلا {
                سيٽ_Flags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    فراغ سيٽ_Minimum_سائيز(BMessage *نياپو)
    {
        عائم max_اوچائي;
        عائم max_ويڪر;
        عائم _;
        int32 min_اوچائي;
        int32 min_ويڪر;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        Get_سائيز_Limits(&_, &max_ويڪر, &_, &max_اوچائي);
        إذا (نياپو->ڳوليو_Int32("window-w", &min_ويڪر) != B_OK)
            أرجع;
        إذا (نياپو->ڳوليو_Int32("window-h", &min_اوچائي) != B_OK)
            أرجع;
        سيٽ_سائيز_Limits((عائم)min_ويڪر, max_ويڪر, (عائم)min_اوچائي, max_اوچائي);
        Update_سائيز_Limits();
    }

    فراغ _Restore()
    {
        إذا (IsMinimized()) {
            Minimize(false);
        } وإلا إذا (IsHidden()) {
            Show();
        } وإلا إذا (_fullscreen) {

        } وإلا إذا (prev_چوکٺو != عدم) { // Zoomed
            Move_منزل(prev_چوکٺو->کاٻو, prev_چوکٺو->چوٽي);
            Resize_منزل(prev_چوکٺو->ويڪر_2(), prev_چوکٺو->اوچائي_2());
        }
    }

    فراغ سيٽ_ڀريل_Screen(bool fullscreen)
    {
        إذا (fullscreen != _fullscreen) {
            إذا (fullscreen) {
                BScreen screen(this);
                BRect screen_چوکٺو = screen.چوکٺو_2();
                _bordered = Look() != B_NO_BORDER_دري_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                non_fullscreen_چوکٺو = چوکٺو_2();
                سيٽ_Bordered(false);
                سيٽ_Resizable(false);
                Move_منزل(screen_چوکٺو.کاٻو, screen_چوکٺو.چوٽي);
                Resize_منزل(screen_چوکٺو.ويڪر_2(), screen_چوکٺو.اوچائي_2());
                _fullscreen = fullscreen;
            } وإلا {
                _fullscreen = fullscreen;
                Move_منزل(non_fullscreen_چوکٺو.کاٻو, non_fullscreen_چوکٺو.چوٽي);
                Resize_منزل(non_fullscreen_چوکٺو.ويڪر_2(), non_fullscreen_چوکٺو.اوچائي_2());
                سيٽ_Bordered(_bordered);
                سيٽ_Resizable(_resizable);
            }
        }
    }

    // Members

    BView *_cur_view;
    SDL_BView *_SDL_View;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
    BGLView *_SDL_GLView;
    Uint32 _gl_type;
#جيڪڏهن_پورو

    int32 آخري_buttons;
    int32 _id;           // Window id used by SDL_BApp
    bool _mouse_focused; // Does this window have mouse focus?
    bool _shown;
    bool _inhibit_resize;

    BRect *prev_چوکٺو; // Previous position and size of the window
    bool _fullscreen;
    // valid only if fullscreen
    BRect non_fullscreen_چوکٺو;
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
#جيڪڏهن_پورو // SDL_BWin_h_
