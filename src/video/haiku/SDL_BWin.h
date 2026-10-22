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

#اگر_غیر_تعریف_شدہ SDL_BWin_h_
#تعریف_کرو SDL_BWin_h_

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

#شامل "SDL_internal.h"
#شامل "SDL_bframebuffer.h"

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#شامل <stdio.h>
#شامل <AppKit.h>
#شامل <Cursor.h>
#شامل <InterfaceKit.h>
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
#شامل <opengl/GLView.h>
#اگر_ختم
#شامل "../../core/haiku/SDL_BApp.h"

شمار WinCommands
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
    BWIN_MINIMUM_سائز_کھڑکی
};

// non-OpenGL framebuffer view
class SDL_BView : عوامی BView
{
  عوامی:
    SDL_BView(BRect چوکھٹا, ثابت حرف *name, uint32 resizing_منوال)
        : BView(چوکھٹا, name, resizing_منوال, B_WILL_DRAW),
          fBitmap(تہی)
    {
    }

    خالی Draw(BRect dirty)
    {
        اگر (fBitmap != تہی)
            DrawBitmap(fBitmap, B_ORIGIN);
    }

    خالی سیٹ_Bitmap(BBitmap *bitmap)
    {
        fBitmap = bitmap;
    }

  نجی:
    BBitmap *fBitmap;
};

class SDL_BWin : عوامی BWindow
{
  عوامی:
    // Constructor/Destructor
    SDL_BWin(BRect bounds, کھڑکی_look look, uint32 flags)
        : BWindow(bounds, "Untitled", look, B_معمول_کھڑکی_FEEL, flags)
    {
        آخری_buttons = 0;

        _cur_view = تہی;
        _SDL_View = تہی;

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
        _SDL_GLView = تہی;
        _gl_type = 0;
#اگر_ختم
        _shown = false;
        _inhibit_resize = false;
        _mouse_focused = false;
        پچھلا_چوکھٹا = تہی;
        _fullscreen = تہی;

        // Handle framebuffer stuff
        بفر_locker = new BLocker();
        _bitmap = تہی;
    }

    مجازی ~SDL_BWin()
    {
        تالا();

        اگر (_SDL_View != تہی && _SDL_View != _cur_view) {
            delete _SDL_View;
            _SDL_View = تہی;
        }

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
        اگر (_SDL_GLView) {
            اگر (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->سیٹ_Current_Context(تہی);
            اگر (_SDL_GLView == _cur_view)
                Remove_بچہ(_SDL_GLView);
            _SDL_GLView = تہی;
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }

#اگر_ختم
        Unlock();

        delete پچھلا_چوکھٹا;

        // Clean up framebuffer stuff
        بفر_locker->تالا();
        delete بفر_locker;
    }

    خالی سیٹ_Current_View(BView *view)
    {
        اگر (_cur_view != view) {
            اگر (_cur_view != تہی)
                Remove_بچہ(_cur_view);
            _cur_view = view;
            اگر (_cur_view != تہی)
                جوڑو_بچہ(_cur_view);
        }
    }

    خالی UpdateCurrentView()
    {
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
        اگر (_SDL_GLView != تہی) {
            سیٹ_Current_View(_SDL_GLView);
        } ورنہ
#اگر_ختم
        اگر (_SDL_View != تہی) {
            سیٹ_Current_View(_SDL_View);
        } ورنہ {
            سیٹ_Current_View(تہی);
        }
    }

    SDL_BView *CreateView()
    {
        تالا();
        اگر (_SDL_View == تہی) {
            _SDL_View = new SDL_BView(Bounds(), "SDL View", B_FOLLOW_ALL_SIDES);
            UpdateCurrentView();
        }
        Unlock();
        واپس _SDL_View;
    }

    خالی RemoveView()
    {
        تالا();
        اگر (_SDL_View != تہی) {
            SDL_BView *oldView = _SDL_View;
            _SDL_View = تہی;
            UpdateCurrentView();
            delete oldView;
        }
        Unlock();
    }

    /* * * * * OpenGL functionality * * * * */
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
    BGLView *CreateGLView(Uint32 gl_flags)
    {
        تالا();
        اگر (_SDL_GLView == تہی) {
            _SDL_GLView = new BGLView(Bounds(), "SDL GLView",
                                      B_FOLLOW_ALL_SIDES,
                                      (B_WILL_DRAW | B_چوکھٹا_EVENTS),
                                      gl_flags);
            _gl_type = gl_flags;
            UpdateCurrentView();
        }
        Unlock();
        واپس _SDL_GLView;
    }

    خالی RemoveGLView()
    {
        تالا();
        اگر (_SDL_GLView != تہی) {
            اگر (SDL_Looper->GetCurrentContext() == _SDL_GLView)
                SDL_Looper->سیٹ_Current_Context(تہی);
            _SDL_GLView = تہی;
            UpdateCurrentView();
            // _SDL_GLView deleted by HAIKU_GL_DestroyContext
        }
        Unlock();
    }

    خالی تبادلہ_Buffers(خالی)
    {
        _SDL_GLView->تبادلہ_Buffers();
    }
#اگر_ختم

    /* * * * * Event sending * * * * */
    // Hook functions
    مجازی خالی چوکھٹا_Moved(BPoint origin)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage پیغام_2(BAPP_کھڑکی_MOVED);
        پیغام_2.جوڑو_Int32("window-x", (صحیح)origin.x);
        پیغام_2.جوڑو_Int32("window-y", (صحیح)origin.y);
        Post_کھڑکی_Event(پیغام_2);

        // Perform normal hook operations
        BWindow::چوکھٹا_Moved(origin);
    }

    خالی چوکھٹا_Resized(اعشاری چوڑائی, اعشاری اونچائی)
    {
        // Post a message to the BApp so that it can handle the window event
        BMessage پیغام_2(BAPP_کھڑکی_RESIZED);

        پیغام_2.جوڑو_Int32("window-w", (صحیح)چوڑائی + 1);
        پیغام_2.جوڑو_Int32("window-h", (صحیح)اونچائی + 1);
        Post_کھڑکی_Event(پیغام_2);

        // Perform normal hook operations
        BWindow::چوکھٹا_Resized(چوڑائی, اونچائی);
    }

    bool QuitRequested()
    {
        BMessage پیغام_2(BAPP_کھڑکی_CLOSE_REQUESTED);
        Post_کھڑکی_Event(پیغام_2);

        // We won't allow a quit unless asked by DestroyWindow()
        واپس false;
    }

    خالی کھڑکی_Activated(bool فعال)
    {
        BMessage پیغام_2(BAPP_KEYBOARD_FOCUS); // Mouse focus sold separately
        پیغام_2.جوڑو_Bool("focusGained", فعال);
        Post_کھڑکی_Event(پیغام_2);
    }

    خالی Zoom(BPoint origin,
              اعشاری چوڑائی,
              اعشاری اونچائی)
    {
        BMessage پیغام_2(BAPP_MAXIMIZE); // Closest thing to maximization Haiku has
        Post_کھڑکی_Event(پیغام_2);

        // Before the window zooms, record its size
        اگر (!پچھلا_چوکھٹا)
            پچھلا_چوکھٹا = new BRect(چوکھٹا_2());

        // Perform normal hook operations
        BWindow::Zoom(origin, چوڑائی, اونچائی);
    }

    // Member functions
    خالی Show()
    {
        جب (IsHidden()) {
            BWindow::Show();
        }
        _shown = true;

        BMessage پیغام_2(BAPP_SHOW);
        Post_کھڑکی_Event(پیغام_2);
    }

    خالی Hide()
    {
        BWindow::Hide();
        _shown = false;

        BMessage پیغام_2(BAPP_HIDE);
        Post_کھڑکی_Event(پیغام_2);
    }

    خالی Minimize(bool minimize)
    {
        BWindow::Minimize(minimize);
        int32 minState = (minimize ? BAPP_MINIMIZE : BAPP_RESTORE);

        BMessage پیغام_2(minState);
        Post_کھڑکی_Event(پیغام_2);
    }

    خالی Screen_بدلا(BRect screen_چوکھٹا, color_space گہرائی_2)
    {
        اگر (_fullscreen) {
            Move_مقصد(screen_چوکھٹا.بایاں, screen_چوکھٹا.چوٹی);
            Resize_مقصد(screen_چوکھٹا.چوڑائی_2(), screen_چوکھٹا.اونچائی_2());
        }
    }

    // BView message interruption
    خالی Dispatch_پیغام(BMessage *پیغام_2, BHandler *ہدف)
    {
        BPoint where;  // Used by mouse moved
        int32 buttons; // Used for mouse button events
        int32 کلید;     // Used for key events

        انتخاب (پیغام_2->what) {
        حالت B_MOUSE_MOVED:
            int32 transit;
            اگر (پیغام_2->ڈھونڈو_نقطہ("where", &where) == B_OK && پیغام_2->ڈھونڈو_Int32("be:transit", &transit) == B_OK) {
                _MouseMotionEvent(where, transit);
            }
            توڑو;

        حالت B_MOUSE_نیچے_کو:
            اگر (پیغام_2->ڈھونڈو_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, true);
            }
            توڑو;

        حالت B_MOUSE_اوپر:
            اگر (پیغام_2->ڈھونڈو_Int32("buttons", &buttons) == B_OK) {
                _MouseButtonEvent(buttons, false);
            }
            توڑو;

        حالت B_MOUSE_WHEEL_بدلا:
            اعشاری x, y;
            اگر (پیغام_2->ڈھونڈو_Float("be:wheel_delta_x", &x) == B_OK && پیغام_2->ڈھونڈو_Float("be:wheel_delta_y", &y) == B_OK) {
                _MouseWheelEvent((صحیح)x, (صحیح)y);
            }
            توڑو;

        حالت B_کلید_نیچے_کو:
        {
            int32 i = 0;
            int8 byte;
            int8 بائٹیں[4] = { 0, 0, 0, 0 };
            جب (i < 4 && پیغام_2->ڈھونڈو_Int8("byte", i, &byte) == B_OK) {
                بائٹیں[i] = byte;
                i++;
            }
            اگر (پیغام_2->ڈھونڈو_Int32("key", &کلید) == B_OK) {
                کلید_Event_2((SDL_Scancode)کلید, &بائٹیں[0], i, true);
            }
        } توڑو;

        حالت B_UNMAPPED_کلید_نیچے_کو: // modifier keys are unmapped
            اگر (پیغام_2->ڈھونڈو_Int32("key", &کلید) == B_OK) {
                کلید_Event_2((SDL_Scancode)کلید, تہی, 0, true);
            }
            توڑو;

        حالت B_کلید_اوپر:
        حالت B_UNMAPPED_کلید_اوپر: // modifier keys are unmapped
            اگر (پیغام_2->ڈھونڈو_Int32("key", &کلید) == B_OK) {
                کلید_Event_2(کلید, تہی, 0, false);
            }
            توڑو;

        طےشدہ:
            /* move it after switch{} so it's always handled
               that way we keep Haiku features like:
               - CTRL+Q to close window (and other shortcuts)
               - PrintScreen to make screenshot into /boot/home
               - etc.. */
            // BWindow::DispatchMessage(msg, target);
            توڑو;
        }

        BWindow::Dispatch_پیغام(پیغام_2, ہدف);
    }

    // Handle command messages
    خالی پیغام_Received(BMessage *پیغام)
    {
        انتخاب (پیغام->what) {
        // Handle commands from SDL
        حالت BWIN_سیٹ_TITLE:
            سیٹ_Title(پیغام);
            توڑو;
        حالت BWIN_MOVE_کھڑکی:
            Move_مقصد_2(پیغام);
            توڑو;
        حالت BWIN_RESIZE_کھڑکی:
            Resize_مقصد_2(پیغام);
            توڑو;
        حالت BWIN_سیٹ_BORDERED:
        {
            bool bEnabled;
            اگر (پیغام->ڈھونڈو_Bool("window-border", &bEnabled) == B_OK)
                سیٹ_Bordered(bEnabled);
            توڑو;
        }
        حالت BWIN_سیٹ_RESIZABLE:
        {
            bool bEnabled;
            اگر (پیغام->ڈھونڈو_Bool("window-resizable", &bEnabled) == B_OK)
                سیٹ_Resizable(bEnabled);
            توڑو;
        }
        حالت BWIN_SHOW_کھڑکی:
            Show();
            توڑو;
        حالت BWIN_HIDE_کھڑکی:
            Hide();
            توڑو;
        حالت BWIN_MAXIMIZE_کھڑکی:
            BWindow::Zoom();
            توڑو;
        حالت BWIN_MINIMIZE_کھڑکی:
            Minimize(true);
            توڑو;
        حالت BWIN_RESTORE_کھڑکی:
            _Restore();
            توڑو;
        حالت BWIN_FULLSCREEN:
        {
            bool fullscreen;
            اگر (پیغام->ڈھونڈو_Bool("fullscreen", &fullscreen) == B_OK)
                سیٹ_بھرا_Screen(fullscreen);
            توڑو;
        }
        حالت BWIN_MINIMUM_سائز_کھڑکی:
            سیٹ_Minimum_سائز(پیغام);
            توڑو;
        حالت BWIN_UPDATE_FRAMEBUFFER:
        {
            BMessage *pending_پیغام;
            جب ((pending_پیغام = پیغام_قطار()->ڈھونڈو_پیغام(BWIN_UPDATE_FRAMEBUFFER, 0))) {
                پیغام_قطار()->Remove_پیغام(pending_پیغام);
                delete pending_پیغام;
            }
            اگر (_bitmap != تہی) {
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
                اگر (_SDL_GLView != تہی && _cur_view == _SDL_GLView) {
                    _SDL_GLView->Copy_Pixels_اندر(_bitmap, B_ORIGIN);
                } ورنہ
#اگر_ختم
                اگر (_SDL_View != تہی && _cur_view == _SDL_View) {
                    _SDL_View->Draw(Bounds());
                }
            }
            توڑو;
        }
        طےشدہ:
            // Perform normal message handling
            BWindow::پیغام_Received(پیغام);
            توڑو;
        }
    }

    // Accessor methods
    bool IsShown() { واپس _shown; }
    int32 GetID() { واپس _id; }
    BBitmap *GetBitmap() { واپس _bitmap; }
    BView *GetCurView() { واپس _cur_view; }
    SDL_BView *GetView() { واپس _SDL_View; }
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
    BGLView *GetGLView()
    {
        واپس _SDL_GLView;
    }
    Uint32 GetGLType() { واپس _gl_type; }
#اگر_ختم

    // Setter methods
    خالی سیٹ_ID(int32 id) { _id = id; }
    خالی تالا_بفر() { بفر_locker->تالا(); }
    خالی Unlock_بفر() { بفر_locker->Unlock(); }
    خالی سیٹ_Bitmap(BBitmap *bitmap)
    {
        _bitmap = bitmap;
        اگر (_SDL_View != تہی)
            _SDL_View->سیٹ_Bitmap(bitmap);
    }

  نجی:
    // Event redirection
    خالی _MouseMotionEvent(BPoint &where, int32 transit)
    {
        اگر (transit == B_EXITED_VIEW) {
            // Change mouse focus
            اگر (_mouse_focused) {
                _MouseFocusEvent(false);
            }
        } ورنہ {
            // Change mouse focus
            اگر (!_mouse_focused) {
                _MouseFocusEvent(true);
            }
            BMessage پیغام_2(BAPP_MOUSE_MOVED);
            پیغام_2.جوڑو_Int32("x", (صحیح)where.x);
            پیغام_2.جوڑو_Int32("y", (صحیح)where.y);

            Post_کھڑکی_Event(پیغام_2);
        }
    }

    خالی _MouseFocusEvent(bool focusGained)
    {
        _mouse_focused = focusGained;
        BMessage پیغام_2(BAPP_MOUSE_FOCUS);
        پیغام_2.جوڑو_Bool("focusGained", focusGained);
        Post_کھڑکی_Event(پیغام_2);

        /* FIXME: Why were these here?
         if false: be_app->SetCursor(B_HAND_CURSOR);
         if true:  SDL_SetCursor(NULL); */
    }

    خالی _MouseButtonEvent(int32 buttons, bool نیچے_کو)
    {
        int32 buttonStateChange = buttons ^ آخری_buttons;

        اگر (buttonStateChange & B_PRIMARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_بایاں, نیچے_کو);
        }
        اگر (buttonStateChange & B_SECONDARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_دایاں, نیچے_کو);
        }
        اگر (buttonStateChange & B_TERTIARY_MOUSE_BUTTON) {
            _SendMouseButton(SDL_BUTTON_درمیان, نیچے_کو);
        }

        آخری_buttons = buttons;
    }

    خالی _SendMouseButton(int32 button, bool نیچے_کو)
    {
        BMessage پیغام_2(BAPP_MOUSE_BUTTON);
        پیغام_2.جوڑو_Int32("button-id", button);
        پیغام_2.جوڑو_Bool("button-down", نیچے_کو);
        Post_کھڑکی_Event(پیغام_2);
    }

    خالی _MouseWheelEvent(int32 x, int32 y)
    {
        // Create a message to pass along to the BeApp thread
        BMessage پیغام_2(BAPP_MOUSE_WHEEL);
        پیغام_2.جوڑو_Int32("xticks", x);
        پیغام_2.جوڑو_Int32("yticks", y);
        Post_کھڑکی_Event(پیغام_2);
    }

    خالی کلید_Event_2(int32 کلید_رمز, ثابت int8 *کلید_Utf8, ثابت ssize_t &len, bool نیچے_کو)
    {
        // Create a message to pass along to the BeApp thread
        BMessage پیغام_2(BAPP_کلید);
        پیغام_2.جوڑو_Int32("key-scancode", کلید_رمز);
        اگر (کلید_Utf8 != تہی) {
            پیغام_2.جوڑو_ڈیٹا("key-utf8", B_INT8_TYPE, (ثابت خالی *)کلید_Utf8, len);
        }
        پیغام_2.جوڑو_Bool("key-down", نیچے_کو);
        SDL_Looper->Post_پیغام(&پیغام_2);
    }

    خالی _RepaintEvent()
    {
        // Force a repaint: Call the SDL exposed event
        BMessage پیغام_2(BAPP_REPAINT);
        Post_کھڑکی_Event(پیغام_2);
    }
    خالی Post_کھڑکی_Event(BMessage &پیغام_2)
    {
        پیغام_2.جوڑو_Int32("window-id", _id);
        SDL_Looper->Post_پیغام(&پیغام_2);
    }

    // Command methods (functions called upon by SDL)
    خالی سیٹ_Title(BMessage *پیغام_2)
    {
        ثابت حرف *title;
        اگر (
            پیغام_2->ڈھونڈو_String("window-title", &title) != B_OK) {
            واپس;
        }
        سیٹ_Title_2(title);
    }

    خالی Move_مقصد_2(BMessage *پیغام_2)
    {
        int32 x, y;
        اگر (
            پیغام_2->ڈھونڈو_Int32("window-x", &x) != B_OK ||
            پیغام_2->ڈھونڈو_Int32("window-y", &y) != B_OK) {
            واپس;
        }
        اگر (_fullscreen)
            non_fullscreen_چوکھٹا.انحراف_مقصد(x, y);
        ورنہ
            Move_مقصد(x, y);
    }

    خالی Resize_مقصد_2(BMessage *پیغام_2)
    {
        int32 w, h;
        اگر (
            پیغام_2->ڈھونڈو_Int32("window-w", &w) != B_OK ||
            پیغام_2->ڈھونڈو_Int32("window-h", &h) != B_OK) {
            واپس;
        }
        اگر (_fullscreen) {
            non_fullscreen_چوکھٹا.دایاں = non_fullscreen_چوکھٹا.بایاں + w;
            non_fullscreen_چوکھٹا.bottom = non_fullscreen_چوکھٹا.چوٹی + h;
        } ورنہ
            Resize_مقصد(w, h);
    }

    خالی سیٹ_Bordered(bool bEnabled)
    {
        اگر (_fullscreen)
            _bordered = bEnabled;
        ورنہ
            سیٹ_Look(bEnabled ? B_TITLED_کھڑکی_LOOK : B_NO_BORDER_کھڑکی_LOOK);
    }

    خالی سیٹ_Resizable(bool bEnabled)
    {
        اگر (_fullscreen)
            _resizable = bEnabled;
        ورنہ {
            اگر (bEnabled) {
                سیٹ_Flags(Flags() & ~(B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            } ورنہ {
                سیٹ_Flags(Flags() | (B_NOT_RESIZABLE | B_NOT_ZOOMABLE));
            }
        }
    }

    خالی سیٹ_Minimum_سائز(BMessage *پیغام_2)
    {
        اعشاری max_اونچائی;
        اعشاری max_چوڑائی;
        اعشاری _;
        int32 min_اونچائی;
        int32 min_چوڑائی;

        // This is a bit convoluted, we only want to set the minimum not the maximum
        // But there is no direct call to do that, so store the maximum size beforehand
        Get_سائز_Limits(&_, &max_چوڑائی, &_, &max_اونچائی);
        اگر (پیغام_2->ڈھونڈو_Int32("window-w", &min_چوڑائی) != B_OK)
            واپس;
        اگر (پیغام_2->ڈھونڈو_Int32("window-h", &min_اونچائی) != B_OK)
            واپس;
        سیٹ_سائز_Limits((اعشاری)min_چوڑائی, max_چوڑائی, (اعشاری)min_اونچائی, max_اونچائی);
        Update_سائز_Limits();
    }

    خالی _Restore()
    {
        اگر (IsMinimized()) {
            Minimize(false);
        } ورنہ اگر (IsHidden()) {
            Show();
        } ورنہ اگر (_fullscreen) {

        } ورنہ اگر (پچھلا_چوکھٹا != تہی) { // Zoomed
            Move_مقصد(پچھلا_چوکھٹا->بایاں, پچھلا_چوکھٹا->چوٹی);
            Resize_مقصد(پچھلا_چوکھٹا->چوڑائی_2(), پچھلا_چوکھٹا->اونچائی_2());
        }
    }

    خالی سیٹ_بھرا_Screen(bool fullscreen)
    {
        اگر (fullscreen != _fullscreen) {
            اگر (fullscreen) {
                BScreen screen(this);
                BRect screen_چوکھٹا = screen.چوکھٹا_2();
                _bordered = Look() != B_NO_BORDER_کھڑکی_LOOK;
                _resizable = !(Flags() & B_NOT_RESIZABLE);
                non_fullscreen_چوکھٹا = چوکھٹا_2();
                سیٹ_Bordered(false);
                سیٹ_Resizable(false);
                Move_مقصد(screen_چوکھٹا.بایاں, screen_چوکھٹا.چوٹی);
                Resize_مقصد(screen_چوکھٹا.چوڑائی_2(), screen_چوکھٹا.اونچائی_2());
                _fullscreen = fullscreen;
            } ورنہ {
                _fullscreen = fullscreen;
                Move_مقصد(non_fullscreen_چوکھٹا.بایاں, non_fullscreen_چوکھٹا.چوٹی);
                Resize_مقصد(non_fullscreen_چوکھٹا.چوڑائی_2(), non_fullscreen_چوکھٹا.اونچائی_2());
                سیٹ_Bordered(_bordered);
                سیٹ_Resizable(_resizable);
            }
        }
    }

    // Members

    BView *_cur_view;
    SDL_BView *_SDL_View;
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
    BGLView *_SDL_GLView;
    Uint32 _gl_type;
#اگر_ختم

    int32 آخری_buttons;
    int32 _id;           // Window id used by SDL_BApp
    bool _mouse_focused; // Does this window have mouse focus?
    bool _shown;
    bool _inhibit_resize;

    BRect *پچھلا_چوکھٹا; // Previous position and size of the window
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
#اگر_ختم // SDL_BWin_h_
