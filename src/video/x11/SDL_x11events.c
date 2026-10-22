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
#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11

#ضمن <sys/types.h>
#ضمن <sys/time.h>
#ضمن <signal.h>
#ضمن <unistd.h>
#ضمن <limits.h> // For INT_MAX

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11pen.h"
#ضمن "SDL_x11touch.h"
#ضمن "SDL_x11xinput2.h"
#ضمن "SDL_x11xfixes.h"
#ضمن "SDL_x11settings.h"
#ضمن "../SDL_clipboard_c.h"
#ضمن "SDL_x11xsync.h"
#ضمن "../../core/unix/SDL_poll.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_touch_c.h"
#ضمن "../../core/linux/SDL_system_theme.h"
#ضمن "../SDL_sysvideo.h"

#ضمن <stdio.h>

#إذا 0
#تعریف_کن DEBUG_XEVENTS
#پایان_اگر

#اگر_تعریف_نشده NET_WM_MOVERESIZE_اندازه_TOPLEFT
#تعریف_کن NET_WM_MOVERESIZE_اندازه_TOPLEFT 0
#پایان_اگر

#اگر_تعریف_نشده NET_WM_MOVERESIZE_اندازه_بالاترین
#تعریف_کن NET_WM_MOVERESIZE_اندازه_بالاترین 1
#پایان_اگر

#اگر_تعریف_نشده NET_WM_MOVERESIZE_اندازه_TOPRIGHT
#تعریف_کن NET_WM_MOVERESIZE_اندازه_TOPRIGHT 2
#پایان_اگر

#اگر_تعریف_نشده NET_WM_MOVERESIZE_اندازه_راست
#تعریف_کن NET_WM_MOVERESIZE_اندازه_راست 3
#پایان_اگر

#اگر_تعریف_نشده NET_WM_MOVERESIZE_اندازه_BOTTOMRIGHT
#تعریف_کن NET_WM_MOVERESIZE_اندازه_BOTTOMRIGHT 4
#پایان_اگر

#اگر_تعریف_نشده NET_WM_MOVERESIZE_اندازه_BOTTOM
#تعریف_کن NET_WM_MOVERESIZE_اندازه_BOTTOM 5
#پایان_اگر

#اگر_تعریف_نشده NET_WM_MOVERESIZE_اندازه_BOTTOMLEFT
#تعریف_کن NET_WM_MOVERESIZE_اندازه_BOTTOMLEFT 6
#پایان_اگر

#اگر_تعریف_نشده NET_WM_MOVERESIZE_اندازه_چپ
#تعریف_کن NET_WM_MOVERESIZE_اندازه_چپ 7
#پایان_اگر

#اگر_تعریف_نشده _NET_WM_MOVERESIZE_MOVE
#تعریف_کن _NET_WM_MOVERESIZE_MOVE 8
#پایان_اگر

تعريفنوع بنية
{
    بیعلامت حرف *داده;
    صحيح format, شمار;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ساكن فراغ X11_ReadProperty(SDL_x11Prop *p, Display *disp, پنجره_2 w, Atom prop)
{
    بیعلامت حرف *ret = عدم;
    Atom type;
    صحيح fmt;
    بیعلامت دراز شمار;
    بیعلامت دراز بایتها_چپ;
    صحيح بایتها_fetch = 0;

    افعل {
        إذا (ret) {
            X11_XFree(ret);
        }
        X11_XGet_پنجره_Property(disp, w, prop, 0, بایتها_fetch, False, AnyPropertyType, &type, &fmt, &شمار, &بایتها_چپ, &ret);
        بایتها_fetch += بایتها_چپ;
    } طالما (بایتها_چپ != 0);

    p->داده = ret;
    p->format = fmt;
    p->شمار = شمار;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
ساكن Atom X11_Pick_هدف(Display *disp, Atom list[], صحيح list_شمار)
{
    ثابت Atom متن_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    لكل (صحيح i = 0; i < list_شمار && request != متن_uri_request; i++) {
        حرف *name = X11_XGetAtomName(disp, list[i]);
        // Preferred MIME targets
        إذا ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            إذا (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        إذا ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            إذا (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    إذا (preferred != None && request != متن_uri_request) {
        request = preferred;
    }
    أرجع request;
}

/* Wrapper for X11_PickTarget for a maximum of three targets, a special
   case in the Xdnd protocol */
ساكن Atom X11_Pick_هدف_From_Atoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    صحيح شمار = 0;
    Atom atom[3];
    إذا (a0 != None) {
        atom[شمار++] = a0;
    }
    إذا (a1 != None) {
        atom[شمار++] = a1;
    }
    إذا (a2 != None) {
        atom[شمار++] = a2;
    }
    أرجع X11_Pick_هدف(disp, atom, شمار);
}

بنية کلید_Repeat_Check_داده
{
    XEvent *event;
    bool یافت;
};

ساكن Bool X11_کلید_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    بنية کلید_Repeat_Check_داده *d = (بنية کلید_Repeat_Check_داده *)arg;
    إذا (chkev->type == کلید_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.زمان - d->event->xkey.زمان < 2) {
        d->یافت = true;
    }
    أرجع False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
ساكن bool X11_کلید_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    بنية کلید_Repeat_Check_داده d;
    d.event = event;
    d.یافت = false;
    إذا (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_کلید_Repeat_Check_If_Event, (XPointer)&d);
    }
    أرجع d.یافت;
}

bool X11_IsWheelEvent(صحيح button, صحيح *xticks, صحيح *yticks)
{
    /* according to the xlib docs, no specific mouse wheel events exist.
       However, the defacto standard is that the vertical wheel is X buttons
       4 (up) and 5 (down) and a horizontal wheel is 6 (left) and 7 (right). */

    // Xlib defines "Button1" through 5, so we just use literals here.
    بدل (button) {
    حالة 4:
        *yticks = 1;
        أرجع true;
    حالة 5:
        *yticks = -1;
        أرجع true;
    حالة 6:
        *xticks = 1;
        أرجع true;
    حالة 7:
        *xticks = -1;
        أرجع true;
    افتراضي:
        اكسر;
    }
    أرجع false;
}

// An X11 event hook
ساكن SDL_X11EventHook g_X11EventHook = عدم;
ساكن فراغ *g_X11_Event_Hook_داده = عدم;

فراغ SDL_مجموعه_X11_Event_Hook(SDL_X11EventHook callback, فراغ *userdata)
{
    g_X11EventHook = callback;
    g_X11_Event_Hook_داده = userdata;
}

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
ساكن فراغ X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_Video_داده *videodata = _this->داخلی;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    إذا (X11_XGet_Event_داده(videodata->display, cookie)) {
        إذا (!g_X11EventHook || g_X11EventHook(g_X11_Event_Hook_داده, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFree_Event_داده(videodata->display, cookie);
    }
}
#پایان_اگر // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

ساكن فراغ X11_Update_System_کلید_Modifiers(SDL_Video_داده *viddata)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        إذا (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.پایه_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } وإلا
#پایان_اگر
        {
        پنجره_2 junk_پنجره;
        صحيح x, y;
        بیعلامت صحيح mod_ماسک;

        X11_XQuery_اشاره_گر(viddata->display, Default_ریشه_پنجره(viddata->display), &junk_پنجره, &junk_پنجره, &x, &y, &x, &y, &mod_ماسک);
        viddata->keyboard.pressed_modifiers = mod_ماسک & (لغزش_ماسک_2 | Control_ماسک | Mod1_ماسک | Mod3_ماسک | Mod4_ماسک | Mod5_ماسک);
        viddata->keyboard.locked_modifiers = mod_ماسک & (قفل_ماسک | viddata->keyboard.numlock_ماسک | viddata->keyboard.scrolllock_ماسک);
    }
}

ساكن فراغ X11_ReconcileModifiers(SDL_Video_داده *viddata, bool کلید_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    إذا (کلید_pressed) {
        إذا (viddata->keyboard.pressed_modifiers & لغزش_ماسک_2) {
            إذا (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_لغزش) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_لغزش;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_لغزش);
            }
        }

        إذا (viddata->keyboard.pressed_modifiers & Control_ماسک) {
            إذا (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        إذا (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_ماسک) {
            إذا (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        إذا (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_ماسک) {
            إذا (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } وإلا {
        إذا (viddata->keyboard.pressed_modifiers & لغزش_ماسک_2) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_لغزش)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_لغزش;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_لغزش;
        }

        إذا (viddata->keyboard.pressed_modifiers & Control_ماسک) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        إذا (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_ماسک) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        إذا (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_ماسک) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        إذا (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_ماسک) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_نما)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_نما;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_نما;
        }

        إذا (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_ماسک) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_LEVEL5;
        }
    }

    /* If a latch or lock was activated by a keypress, the latch/lock will
     * be tied to the specific left/right key that initiated it. Otherwise,
     * the ambiguous left/right combo is used.
     *
     * The modifier will remain active until the latch/lock is released by
     * the system.
     */
    إذا (viddata->keyboard.locked_modifiers & لغزش_ماسک_2) {
        إذا (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_لغزش) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_لغزش;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_لغزش);
        } وإلا إذا (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_لغزش)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_لغزش;
        }
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_لغزش;
    }

    إذا (viddata->keyboard.locked_modifiers & Control_ماسک) {
        إذا (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } وإلا إذا (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_ماسک) {
        إذا (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } وإلا إذا (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_ماسک) {
        إذا (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } وإلا إذا (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_ماسک) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_نما;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_نما;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_ماسک) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    إذا (viddata->keyboard.locked_modifiers & قفل_ماسک) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_ماسک) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_رقم;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_رقم;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_ماسک) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_مجموعه_Mod_State(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

ساكن فراغ X11_Handle_Modifier_کلیدها(SDL_Video_داده *viddata, SDL_Scancode scancode, bool pressed)
{
    ثابت SDL_Keycode keycode = SDL_Get_کلید_From_Scancode(scancode, SDL_KMOD_NONE, false);
    SDL_Keymod mod = SDL_KMOD_NONE;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is checked.
     */
    بدل (keycode) {
    حالة SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        اكسر;
    حالة SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        اكسر;
    حالة SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        اكسر;
    حالة SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        اكسر;
    حالة SDLK_LALT:
        mod = SDL_KMOD_LALT;
        اكسر;
    حالة SDLK_RALT:
        mod = SDL_KMOD_RALT;
        اكسر;
    حالة SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        اكسر;
    حالة SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        اكسر;
    حالة SDLK_نما:
        mod = SDL_KMOD_نما;
        اكسر;
    حالة SDLK_LEVEL5_لغزش:
        mod = SDL_KMOD_LEVEL5;
        اكسر;
    حالة SDLK_CAPSLOCK:
    حالة SDLK_NUMLOCKCLEAR:
    حالة SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        إذا (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            بیعلامت صحيح cur_ماسک = viddata->keyboard.locked_modifiers;
            X11_Update_System_کلید_Modifiers(viddata);

            إذا (viddata->keyboard.locked_modifiers & قفل_ماسک) {
                cur_ماسک |= قفل_ماسک;
            } وإلا {
                cur_ماسک &= ~قفل_ماسک;
            }
            إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_ماسک) {
                cur_ماسک |= viddata->keyboard.numlock_ماسک;
            } وإلا {
                cur_ماسک &= ~viddata->keyboard.numlock_ماسک;
            }
            إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_ماسک) {
                cur_ماسک |= viddata->keyboard.scrolllock_ماسک;
            } وإلا {
                cur_ماسک &= ~viddata->keyboard.scrolllock_ماسک;
            }

            viddata->keyboard.locked_modifiers = cur_ماسک;
        }
    } اكسر;
    افتراضي:
        أرجع;
    }

    إذا (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } وإلا {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

فراغ X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_Video_داده *videodata = _this->داخلی;
    Display *display = videodata->display;
    حرف کلیدها[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_کلید_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_رقم | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= قفل_ماسک | videodata->keyboard.numlock_ماسک| videodata->keyboard.scrolllock_ماسک;

    X11_XQueryKeymap(display, کلیدها);

    ثابت bool *keystate = SDL_GetKeyboardState(عدم);
    لكل (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.کلید_layout); ++keycode) {
        ثابت SDL_Scancode scancode = videodata->keyboard.کلید_layout[keycode];
        ثابت bool x11_کلید_Pressed = (کلیدها[keycode / 8] & (1 << (keycode % 8))) != 0;
        ثابت bool sdl_کلید_Pressed = keystate[scancode];

        إذا (x11_کلید_Pressed && !sdl_کلید_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            بدل (SDL_Get_کلید_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            حالة SDLK_LCTRL:
            حالة SDLK_RCTRL:
            حالة SDLK_LSHIFT:
            حالة SDLK_RSHIFT:
            حالة SDLK_LALT:
            حالة SDLK_RALT:
            حالة SDLK_LGUI:
            حالة SDLK_RGUI:
            حالة SDLK_نما:
            حالة SDLK_LEVEL5_لغزش:
                X11_Handle_Modifier_کلیدها(videodata, scancode, true);
                SDL_Send_Keyboard_کلید_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                اكسر;
            افتراضي:
                اكسر;
            }
        } وإلا إذا (!x11_کلید_Pressed && sdl_کلید_Pressed) {
            X11_Handle_Modifier_کلیدها(videodata, scancode, false);
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_کلید_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

ساكن فراغ X11_Dispatch_Focus_درون(SDL_VideoDevice *_this, SDL_پنجره_داده *داده)
{
#اگر_تعریف_شده DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", داده->xwindow);
#پایان_اگر
    SDL_مجموعه_Keyboard_Focus(داده->پنجره);
    X11_ReconcileKeyboardState(_this);
#اگر_تعریف_شده X_HAVE_UTF8_STRING
    إذا (داده->ic) {
        X11_XSetICFocus(داده->ic);
    }
#پایان_اگر
    إذا (داده->flashing_پنجره) {
        X11_Flash_پنجره(_this, داده->پنجره, SDL_FLASH_CANCEL);
    }
}

ساكن فراغ X11_Dispatch_Focus_بیرون(SDL_VideoDevice *_this, SDL_پنجره_داده *داده)
{
#اگر_تعریف_شده DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", داده->xwindow);
#پایان_اگر
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    إذا (داده->پنجره == SDL_GetKeyboardFocus()) {
        SDL_مجموعه_Keyboard_Focus(عدم);
    }
#اگر_تعریف_شده X_HAVE_UTF8_STRING
    إذا (داده->ic) {
        X11_XUnsetICFocus(داده->ic);
    }
#پایان_اگر
}

ساكن فراغ X11_DispatchMapNotify(SDL_پنجره_داده *داده)
{
    SDL_پنجره *پنجره = داده->پنجره;

    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_SHOWN, 0, 0);
    داده->was_shown = true;

    // This may be sent when restoring a minimized window.
    إذا (پنجره->flags & SDL_پنجره_MINIMIZED) {
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESTORED, 0, 0);
        SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_EXPOSED, 0, 0);
    }

    إذا (پنجره->flags & SDL_پنجره_درون_داد_FOCUS) {
        SDL_Update_پنجره_Grab(پنجره);
    }
}

ساكن فراغ X11_DispatchUnmapNotify(SDL_پنجره_داده *داده)
{
    SDL_پنجره *پنجره = داده->پنجره;

    // This may be sent when minimizing a window.
    إذا (!پنجره->is_hiding) {
        SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_MINIMIZED, 0, 0);
        SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_OCCLUDED, 0, 0);
    } وإلا {
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_HIDDEN, 0, 0);
    }
}

ساكن فراغ Dispatch_پنجره_Move(SDL_VideoDevice *_this, ثابت SDL_پنجره_داده *داده, ثابت SDL_نقطه *نقطه)
{
    SDL_Video_داده *videodata = _this->داخلی;
    SDL_پنجره *پنجره = داده->پنجره;
    Display *display = videodata->display;
    XEvent evt;

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_اشاره_گر(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_پیام;
    evt.xclient.پنجره = داده->xwindow;
    evt.xclient.پیام_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.داده.l[0] = (size_t)پنجره->x + نقطه->x;
    evt.xclient.داده.l[1] = (size_t)پنجره->y + نقطه->y;
    evt.xclient.داده.l[2] = _NET_WM_MOVERESIZE_MOVE;
    evt.xclient.داده.l[3] = Button1;
    evt.xclient.داده.l[4] = 0;
    X11_XSendEvent(display, Default_ریشه_پنجره(display), False, Substructure_Redirect_ماسک | Substructure_Notify_ماسک, &evt);

    X11_XSync(display, 0);
}

ساكن فراغ زمانبندی_پنجره_Move(SDL_VideoDevice *_this, SDL_پنجره_داده *داده, ثابت SDL_نقطه *نقطه)
{
    داده->pending_move = true;
    داده->pending_move_نقطه = *نقطه;
}

ساكن فراغ Initiate_پنجره_Resize(SDL_VideoDevice *_this, ثابت SDL_پنجره_داده *داده, ثابت SDL_نقطه *نقطه, صحيح direction)
{
    SDL_Video_داده *videodata = _this->داخلی;
    SDL_پنجره *پنجره = داده->پنجره;
    Display *display = videodata->display;
    XEvent evt;

    إذا (direction < NET_WM_MOVERESIZE_اندازه_TOPLEFT || direction > NET_WM_MOVERESIZE_اندازه_چپ) {
        أرجع;
    }

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_اشاره_گر(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_پیام;
    evt.xclient.پنجره = داده->xwindow;
    evt.xclient.پیام_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.داده.l[0] = (size_t)پنجره->x + نقطه->x;
    evt.xclient.داده.l[1] = (size_t)پنجره->y + نقطه->y;
    evt.xclient.داده.l[2] = direction;
    evt.xclient.داده.l[3] = Button1;
    evt.xclient.داده.l[4] = 0;
    X11_XSendEvent(display, Default_ریشه_پنجره(display), False, Substructure_Redirect_ماسک | Substructure_Notify_ماسک, &evt);

    X11_XSync(display, 0);
}

bool X11_Process_اصابت_Test(SDL_VideoDevice *_this, SDL_پنجره_داده *داده, ثابت عائم x, ثابت عائم y, bool force_new_نتیجه)
{
    SDL_پنجره *پنجره = داده->پنجره;
    إذا (!پنجره->اصابت_test) أرجع false;
    ثابت SDL_نقطه نقطه = { (صحيح)x, (صحيح)y };
    SDL_اصابت_Test_نتیجه rc = پنجره->اصابت_test(پنجره, &نقطه, پنجره->اصابت_test_داده);
    إذا (!force_new_نتیجه && rc == داده->اصابت_test_نتیجه) {
        أرجع true;
    }
    X11_مجموعه_اصابت_Test_Cursor(rc);
    داده->اصابت_test_نتیجه = rc;
    أرجع true;
}

bool X11_Trigger_اصابت_Test_Action(SDL_VideoDevice *_this, SDL_پنجره_داده *داده, ثابت عائم x, ثابت عائم y)
{
    SDL_پنجره *پنجره = داده->پنجره;

    إذا (پنجره->اصابت_test) {
        ثابت SDL_نقطه نقطه = { (صحيح)x, (صحيح)y };
        ساكن ثابت صحيح directions[] = {
            NET_WM_MOVERESIZE_اندازه_TOPLEFT, NET_WM_MOVERESIZE_اندازه_بالاترین,
            NET_WM_MOVERESIZE_اندازه_TOPRIGHT, NET_WM_MOVERESIZE_اندازه_راست,
            NET_WM_MOVERESIZE_اندازه_BOTTOMRIGHT, NET_WM_MOVERESIZE_اندازه_BOTTOM,
            NET_WM_MOVERESIZE_اندازه_BOTTOMLEFT, NET_WM_MOVERESIZE_اندازه_چپ
        };

        بدل (داده->اصابت_test_نتیجه) {
        حالة SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            إذا (داده->پنجره->flags & SDL_پنجره_درون_داد_FOCUS) {
                Dispatch_پنجره_Move(_this, داده, &نقطه);
            } وإلا {
                زمانبندی_پنجره_Move(_this, داده, &نقطه);
            }
            أرجع true;

        حالة SDL_HITTEST_RESIZE_TOPLEFT:
        حالة SDL_HITTEST_RESIZE_بالاترین:
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
        حالة SDL_HITTEST_RESIZE_راست:
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        حالة SDL_HITTEST_RESIZE_BOTTOM:
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
        حالة SDL_HITTEST_RESIZE_چپ:
            Initiate_پنجره_Resize(_this, داده, &نقطه, directions[داده->اصابت_test_نتیجه - SDL_HITTEST_RESIZE_TOPLEFT]);
            أرجع true;

        افتراضي:
            أرجع false;
        }
    }

    أرجع false;
}

ساكن فراغ X11_Update_User_زمان(SDL_پنجره_داده *داده, ثابت بیعلامت دراز latest)
{
    إذا (latest && (latest != داده->user_زمان)) {
        SDL_Video_داده *videodata = داده->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, داده->xwindow, videodata->atoms.NET_WM_USER_زمان,
                            XA_CARDINAL, 32, Prop_نما_Replace,
                            (ثابت بیعلامت حرف *)&latest, 1);
#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", داده->xwindow, latest);
#پایان_اگر
        داده->user_زمان = latest;
    }
}

ساكن بیعلامت حرف x11_آخرین_error;
ساكن صحيح Bad_پنجره_Error_Handler(Display *d, XErrorEvent *e)
{
    x11_آخرین_error = e->error_کد;

    // Ignore BadWindow in cases where it's not fatal.
    إذا (e->error_کد != Bad_پنجره) {
        حرف err_پیام[128];
        X11_XGet_Error_متن(d, e->error_کد, err_پیام, حجم(err_پیام));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_کد, err_پیام, e->request_کد);
    }
    أرجع 0;
}

ساكن فراغ X11_HandleClipboardEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    صحيح i;
    SDL_Video_داده *videodata = _this->داخلی;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_پنجره != None);
    SDL_assert(xevent->xany.پنجره == videodata->clipboard_پنجره);

    بدل (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    حالة SelectionRequest:
    {
        ثابت XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        صحيح mime_formats;
        بیعلامت حرف *seln_داده;
        size_t seln_درازی = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_Clipboard_داده *clipboard;

#اگر_تعریف_شده DEBUG_XEVENTS
        حرف *atom_name;
        atom_name = X11_XGetAtomName(display, req->هدف);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->هدف, atom_name);
        إذا (atom_name) {
            X11_XFree(atom_name);
        }
#پایان_اگر

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_آخرین_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_پنجره_Error_Handler);

        إذا (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } وإلا {
            clipboard = &videodata->clipboard;
        }

        SDL_zero(sevent);
        sevent.xany.type = SelectionNotify;
        sevent.xselection.selection = req->selection;
        sevent.xselection.هدف = None;
        sevent.xselection.property = None; // tell them no by default
        sevent.xselection.requestor = req->requestor;
        sevent.xselection.زمان = req->زمان;

        /* !!! FIXME: We were probably storing this on the root window
           because an SDL window might go away...? but we don't have to do
           this now (or ever, really). */

        إذا (req->هدف == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_شمار + 1) * حجم(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            لكل (i = 0; i < clipboard->mime_شمار; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, Prop_نما_Replace,
                                (بیعلامت حرف *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.هدف = XA_TARGETS;
            SDL_free(supportedFormats);
        } وإلا {
            إذا (clipboard->callback) {
                لكل (i = 0; i < clipboard->mime_شمار; ++i) {
                    ثابت حرف *mime_type = clipboard->mime_types[i];
                    إذا (X11_XInternAtom(display, mime_type, False) != req->هدف) {
                        استمر;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_داده = (بیعلامت حرف *)clipboard->callback(clipboard->userdata, mime_type, &seln_درازی);
                    إذا (seln_داده) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->هدف, 8, Prop_نما_Replace,
                                            seln_داده, seln_درازی);
                        sevent.xselection.property = req->property;
                        sevent.xselection.هدف = req->هدف;
                    }
                    اكسر;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(prev_handler);
    } اكسر;

    حالة SelectionNotify:
    {
        ثابت XSelectionEvent *xsel = &xevent->xselection;
#اگر_تعریف_شده DEBUG_XEVENTS
        ثابت حرف *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        ثابت حرف *هدف_Name = xsel->هدف ? X11_XGetAtomName(display, xsel->هدف) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, هدف_Name, propName);
#پایان_اگر
        إذا (xsel->هدف == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            بیعلامت حرف *داده = عدم;
            صحيح format_property = 0;
            بیعلامت دراز درازی = 0;
            بیعلامت دراز بایتها_چپ = 0;
            صحيح j;

            X11_XGet_پنجره_Property(display, Get_پنجره(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &درازی, &بایتها_چپ, &داده);

            صحيح allocationsize = (درازی + 1) * حجم(حرف *);
            لكل (j = 0, patom = (Atom *)داده; j < درازی; j++, patom++) {
                حرف *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            حرف **new_mime_types = SDL_Allocate_Temporary_حافظه(allocationsize);
            إذا (new_mime_types) {
                حرف *strPtr = (حرف *)(new_mime_types + درازی + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                لكل (j = 0, patom = (Atom *)داده; j < درازی; j++, patom++) {
                    حرف *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    ثابت size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[درازی] = عدم;

                SDL_SendClipboardUpdate(false, new_mime_types, درازی);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            إذا (داده) {
                X11_XFree(داده);
            }
        }

        videodata->selection_انتظار = false;
    } اكسر;

    حالة SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_Clipboard_داده *clipboard = عدم;

#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.هدف);
#پایان_اگر

        إذا (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } وإلا إذا (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        إذا (clipboard && clipboard->callback) {
            إذا (clipboard->sequence) {
                SDL_Cancel_Clipboard_داده(clipboard->sequence);
            } وإلا {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } اكسر;

    حالة PropertyNotify:
    {
        حرف *name_از_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        إذا (SDL_strncmp(name_از_atom, "SDL_SELECTION", حجم("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_مقدار) {
            videodata->selection_incr_انتظار = false;
        }

        إذا (name_از_atom) {
            X11_XFree(name_از_atom);
        }
    } اكسر;
    }
}

ساكن Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    أرجع ev->type == MapNotify &&
           ev->xmap.پنجره == unmap->پنجره &&
           ev->xmap.serial == unmap->serial;
}

ساكن Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    أرجع ev->type == ReparentNotify &&
           ev->xreparent.پنجره == unmap->پنجره &&
           ev->xreparent.serial == unmap->serial;
}

ساكن bool Is_بالا_Latin1(ثابت حرف *string, صحيح درازی)
{
    طالما (درازی-- > 0) {
        Uint8 ch = (Uint8)*string;
        إذا (ch >= 0x80) {
            أرجع true;
        }
        ++string;
    }
    أرجع false;
}

ساكن صحيح XLookupStringAsUTF8(XKeyEvent *event_struct, حرف *میانگیر_return, صحيح بایتها_میانگیر, کلید_Sym *keysym_return, XCompose_وضعیت *وضعیت_درون_بیرون)
{
    صحيح نتیجه = X11_XLookupString(event_struct, میانگیر_return, بایتها_میانگیر, keysym_return, وضعیت_درون_بیرون);
    إذا (Is_بالا_Latin1(میانگیر_return, نتیجه)) {
        حرف *utf8_متن = SDL_iconv_string("UTF-8", "ISO-8859-1", میانگیر_return, نتیجه + 1);
        إذا (utf8_متن) {
            SDL_strlcpy(میانگیر_return, utf8_متن, بایتها_میانگیر);
            SDL_free(utf8_متن);
            أرجع SDL_strlen(میانگیر_return);
        } وإلا {
            أرجع 0;
        }
    }
    أرجع نتیجه;
}

SDL_پنجره_داده *X11_پیدا_کن_پنجره(SDL_Video_داده *videodata, پنجره_2 پنجره)
{
    إذا (videodata && videodata->windowlist) {
        لكل (صحيح i = 0; i < videodata->numwindows; ++i) {
            إذا ((videodata->windowlist[i] != عدم) &&
                (videodata->windowlist[i]->xwindow == پنجره)) {
                أرجع videodata->windowlist[i];
            }
        }
    }
    أرجع عدم;
}

Uint64 X11_GetEventTimestamp(بیعلامت دراز زمان)
{
    // FIXME: Get the event time in the SDL tick time base
    أرجع SDL_GetTicksNS();
}

فراغ X11_Handle_کلید_Event(SDL_VideoDevice *_this, SDL_پنجره_داده *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_Video_داده *videodata = _this->داخلی;
    Display *display = videodata->display;
    کلید_کد_2 keycode = xevent->xkey.keycode;
    کلید_Sym keysym = No_نماد;
    صحيح متن_درازی = 0;
    حرف متن[64];
    وضعیت_2 وضعیت = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == کلید_Press);
    SDL_Scancode scancode = videodata->keyboard.کلید_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.زمان);

#اگر_تعریف_شده DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.پنجره, (xevent->type == کلید_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#پایان_اگر
#اگر_تعریف_شده DEBUG_SCANCODES
    إذا (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        صحيح min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_کلید_کد_مقصد_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysym_مقصد_String(keysym));
    }
#پایان_اگر // DEBUG SCANCODES

    متن[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    إذا (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (لغزش_ماسک_2 | Control_ماسک | Mod1_ماسک | Mod3_ماسک | Mod4_ماسک | Mod5_ماسک);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (قفل_ماسک | videodata->keyboard.numlock_ماسک | videodata->keyboard.scrolllock_ماسک);
    }

    إذا (SDL_متن_درون_داد_فعال(windowdata->پنجره)) {
        // filter events catches XIM events and sends them to the correct handler
        إذا (X11_XFilterEvent(xevent, None)) {
#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.پنجره);
#پایان_اگر
            handled_by_ime = true;
        }

        إذا (!handled_by_ime) {
#اگر_تعریف_شده X_HAVE_UTF8_STRING
            إذا (windowdata->ic && xevent->type == کلید_Press) {
                متن_درازی = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, متن, حجم(متن) - 1,
                                      &keysym, &وضعیت);
            } وإلا {
                متن_درازی = XLookupStringAsUTF8(&xevent->xkey, متن, حجم(متن) - 1, &keysym, عدم);
            }
#وإلا
            متن_درازی = XLookupStringAsUTF8(&xevent->xkey, متن, حجم(متن) - 1, &keysym, عدم);
#پایان_اگر
        }
    }

    إذا (!handled_by_ime) {
        إذا (pressed) {
            X11_Handle_Modifier_کلیدها(videodata, scancode, true);
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            إذا (*متن && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                متن[متن_درازی] = '\0';
                X11_ClearComposition(windowdata);
                SDL_Send_Keyboard_متن(متن);
            }
        } وإلا {
            إذا (X11_کلید_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                أرجع;
            }

            X11_Handle_Modifier_کلیدها(videodata, scancode, false);
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    إذا (pressed) {
        X11_Update_User_زمان(windowdata, xevent->xkey.زمان);
    }
}

فراغ X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_پنجره_داده *windowdata, SDL_MouseID mouseID, صحيح button, عائم x, عائم y, بیعلامت دراز زمان, بیعلامت دراز serial)
{
    SDL_پنجره *پنجره = windowdata->پنجره;
    صحيح xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(زمان);

#اگر_تعریف_شده DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#پایان_اگر

    SDL_Mouse *mouse = SDL_GetMouse();
    إذا (!mouse->relative_نما && (x != mouse->x || y != mouse->y)) {
        X11_Process_اصابت_Test(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, پنجره, mouseID, false, x, y);
    }

    إذا (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, پنجره, mouseID, (عائم)-xticks, (عائم)yticks, SDL_MOUSEWHEEL_نرمال);
    } وإلا {
        إذا (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        إذا (button == Button1) {
            إذا (X11_Trigger_اصابت_Test_Action(_this, windowdata, x, y)) {
                SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_اصابت_TEST, 0, 0);
                أرجع; // don't pass this event on to app.
            }
        }
        إذا (windowdata->آخرین_focus_event_زمان) {
            ثابت صحيح X11_FOCUS_CLICK_TIMEOUT = 10;
            إذا (SDL_GetTicks() < (windowdata->آخرین_focus_event_زمان + X11_FOCUS_CLICK_TIMEOUT)) {
                إذا (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->آخرین_focus_event_زمان = 0;
        }
        إذا (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, پنجره, mouseID, button, true);
        }
    }
    X11_Update_User_زمان(windowdata, زمان);
}

فراغ X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_پنجره_داده *windowdata, SDL_MouseID mouseID, صحيح button, بیعلامت دراز زمان)
{
    SDL_پنجره *پنجره = windowdata->پنجره;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    صحيح xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(زمان);

#اگر_تعریف_شده DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#پایان_اگر
    إذا (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        إذا (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, پنجره, mouseID, button, false);

        إذا (پنجره->داخلی->pending_grab) {
            X11_مجموعه_پنجره_Mouse_Grab(_this, پنجره, true);
        }
    }
}

فراغ X11_Get_Border_مقادیر(SDL_پنجره_داده *داده)
{
    SDL_Video_داده *videodata = داده->videodata;
    Display *display = videodata->display;

    Atom type;
    صحيح format;
    بیعلامت دراز nitems, بایتها_after;
    بیعلامت حرف *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    إذا (!(داده->پنجره->flags & SDL_پنجره_BORDERLESS)) {
        إذا (X11_XGet_پنجره_Property(display, داده->xwindow, videodata->atoms.NET_قاب_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &بایتها_after, &property) == Success) {
            إذا (type != None && nitems == 4) {
                داده->border_چپ = (صحيح)((دراز *)property)[0];
                داده->border_راست = (صحيح)((دراز *)property)[1];
                داده->border_بالاترین = (صحيح)((دراز *)property)[2];
                داده->border_bottom = (صحيح)((دراز *)property)[3];
            }
            X11_XFree(property);

#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", داده->border_چپ, داده->border_راست, داده->border_بالاترین, داده->border_bottom);
#پایان_اگر
        }
    } وإلا {
        داده->border_چپ = داده->border_بالاترین = داده->border_راست = داده->border_bottom = 0;
    }
}

فراغ X11_EmitConfigureNotifyEvents(SDL_پنجره_داده *داده, XConfigureEvent *xevent)
{
    إذا (!داده->اندازه_move_event_flags) {
        صحيح x = xevent->x;
        صحيح y = xevent->y;

        إذا (xevent->x != داده->آخرین_xconfigure.x ||
            xevent->y != داده->آخرین_xconfigure.y) {
            داده->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_Global_مقصد_Relative_For_پنجره(داده->پنجره, x, y, &x, &y);
        SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_MOVED, x, y);

        لكل (SDL_پنجره *w = داده->پنجره->اولی_فرزند; w; w = w->بعدی_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            إذا (SDL_پنجره_IS_POPUP(w) && !(w->flags & SDL_پنجره_HIDDEN)) {
                X11_Update_پنجره_Position(w, true);
            }
        }

        إذا (xevent->عرض != داده->آخرین_xconfigure.عرض ||
            xevent->ارتفاع != داده->آخرین_xconfigure.ارتفاع) {
            داده->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_RESIZED, xevent->عرض, xevent->ارتفاع);
    }

    SDL_copyp(&داده->آخرین_xconfigure, xevent);
}

ساكن فراغ X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_Video_داده *videodata = _this->داخلی;
    Display *display;
    SDL_پنجره_داده *داده;
    XClient_پیام_Event m;
    صحيح i;

    SDL_assert(videodata != عدم);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    إذا (xevent->type != کلید_Press && xevent->type != کلید_Release) {
        إذا (X11_XFilterEvent(xevent, None)) {
#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.پنجره);
#پایان_اگر
            أرجع;
        }
    }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    إذا (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        أرجع;
    }
#پایان_اگر

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    إذا (g_X11EventHook) {
        إذا (!g_X11EventHook(g_X11_Event_Hook_داده, xevent)) {
            أرجع;
        }
    }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
    إذا (videodata->xrandr_event_پایه && (xevent->type == (videodata->xrandr_event_پایه + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#پایان_اگر

#اگر_تعریف_شده DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.پنجره);
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XFIXES
    إذا (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#پایان_اگر

        إذا (ev->subtype == XFixes_مجموعه_Selection_Owner_Notify)
        {
            إذا (ev->selection != videodata->atoms.CLIPBOARD)
                أرجع;

            إذا (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_پنجره)
                أرجع;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, Get_پنجره(_this), Current_زمان);
        }

        أرجع;
    }
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XFIXES

    إذا ((videodata->clipboard_پنجره != None) &&
        (videodata->clipboard_پنجره == xevent->xany.پنجره)) {
        X11_HandleClipboardEvent(_this, xevent);
        أرجع;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    داده = X11_پیدا_کن_پنجره(videodata, xevent->xany.پنجره);

    إذا (!داده) {
        // The window for KeymapNotify, etc events is 0
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        إذا (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            بدل (xkbevent->any.xkb_type) {
            حالة XkbStateNotify:
            {
#اگر_تعریف_شده DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.پنجره);
#پایان_اگر
                إذا ((xkbevent->state.تغییریافته & Xkb_گروه_State_ماسک) && xkbevent->state.گروه != videodata->keyboard.xkb.current_گروه) {
                    videodata->keyboard.xkb.current_گروه = xkbevent->state.گروه;
                    SDL_مجموعه_Keymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_گروه], true);
                }

                إذا (xkbevent->state.تغییریافته & Xkb_Modifier_State_ماسک) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.پایه_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } اكسر;

            حالة XkbMapNotify:
#اگر_تعریف_شده DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.پنجره);
                SDL_FALLTHROUGH;
#پایان_اگر
            حالة XkbNewKeyboardNotify:
            {
#اگر_تعریف_شده DEBUG_XEVENTS
                إذا (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.پنجره);
                }
#پایان_اگر
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                إذا (xkbevent->any.serial != videodata->keyboard.xkb.آخرین_map_serial) {
                    videodata->keyboard.xkb.آخرین_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } اكسر;

            افتراضي:
                اكسر;
            }
        } وإلا
#پایان_اگر
        إذا (xevent->type == KeymapNotify) {
#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.پنجره);
#پایان_اگر
            إذا (SDL_GetKeyboardFocus() != عدم) {
                إذا (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } وإلا إذا (xevent->type == MappingNotify) {
            ثابت صحيح request = xevent->xmapping.request;

            إذا (request == Mapping_اشاره_گر) {
#اگر_تعریف_شده DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.پنجره);
#پایان_اگر
                X11_Xinput2_Update_اشاره_گر_Mapping(_this);
            } وإلا إذا (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#اگر_تعریف_شده DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.پنجره);
#پایان_اگر
                إذا (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } وإلا إذا (xevent->type == PropertyNotify && videodata) {
            حرف *name_از_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            إذا (name_از_atom) {
                إذا (SDL_startswith(name_از_atom, "_ICC_PROFILE")) {
                    XWindow_صفات attrib;
                    صحيح screennum;
                    لكل (i = 0; i < videodata->numwindows; ++i) {
                        إذا (videodata->windowlist[i] != عدم) {
                            داده = videodata->windowlist[i];
                            X11_XGet_پنجره_صفات(display, داده->xwindow, &attrib);
                            screennum = X11_XScreen_عدد_از_Screen(attrib.screen);
                            إذا (screennum == 0 && SDL_strcmp(name_از_atom, "_ICC_PROFILE") == 0) {
                                SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_ICCPROF_تغییریافته, 0, 0);
                            } وإلا إذا (SDL_strncmp(name_از_atom, "_ICC_PROFILE_", حجم("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_از_atom) > حجم("_ICC_PROFILE_") - 1) {
                                صحيح iccscreennum = SDL_atoi(&name_از_atom[حجم("_ICC_PROFILE_") - 1]);

                                إذا (screennum == iccscreennum) {
                                    SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_ICCPROF_تغییریافته, 0, 0);
                                }
                            }
                        }
                    }
                } وإلا إذا (SDL_strcmp(name_از_atom, "_NET_WORKAREA") == 0) {
                    لكل (i = 0; i < _this->رقم_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_تغییریافته, 0, 0);
                    }
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
                } وإلا إذا (SDL_strcmp(name_از_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_از_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#پایان_اگر
                }
                X11_XFree(name_از_atom);
            }
        }
        أرجع;
    }

    بدل (xevent->type) {

        // Gaining mouse coverage?
    حالة EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.پنجره,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.نما);
        إذا (xevent->xcrossing.نما == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        إذا (xevent->xcrossing.نما == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#پایان_اگر
        SDL_مجموعه_Mouse_Focus(داده->پنجره);

        mouse->آخرین_x = xevent->xcrossing.x;
        mouse->آخرین_y = xevent->xcrossing.y;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XFIXES
        {
            // Only create the barriers if we have input focus
            SDL_پنجره_داده *windowdata = داده->پنجره->داخلی;
            إذا ((داده->اشاره_گر_barrier_فعال == true) && windowdata->پنجره->flags & SDL_پنجره_درون_داد_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->پنجره, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#پایان_اگر

        إذا (!mouse->relative_نما) {
            SDL_SendMouseMotion(0, داده->پنجره, SDL_GLOBAL_MOUSE_ID, false, (عائم)xevent->xcrossing.x, (عائم)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        إذا (!(داده->پنجره->flags & SDL_پنجره_MOUSE_CAPTURE)) {
            SDL_Update_پنجره_Grab(داده->پنجره);
        }

        X11_Process_اصابت_Test(_this, داده, mouse->آخرین_x, mouse->آخرین_y, true);
    } اكسر;
        // Losing mouse coverage?
    حالة LeaveNotify:
    {
#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.پنجره,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.نما);
        إذا (xevent->xcrossing.نما == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        إذا (xevent->xcrossing.نما == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#پایان_اگر
        إذا (!SDL_GetMouse()->relative_نما) {
            SDL_SendMouseMotion(0, داده->پنجره, SDL_GLOBAL_MOUSE_ID, false, (عائم)xevent->xcrossing.x, (عائم)xevent->xcrossing.y);
        }

        إذا (xevent->xcrossing.نما != NotifyGrab &&
            xevent->xcrossing.نما != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            إذا (!(داده->پنجره->flags & SDL_پنجره_FULLSCREEN)) {
                X11_مجموعه_پنجره_Keyboard_Grab(_this, داده->پنجره, false);
            }

            SDL_مجموعه_Mouse_Focus(عدم);
        }
    } اكسر;

        // Gaining input focus?
    حالة Focus_درون:
    {
        إذا (xevent->xfocus.نما == NotifyGrab || xevent->xfocus.نما == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.پنجره);
#پایان_اگر
            اكسر;
        }

        إذا (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_اشاره_گر) {
#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.پنجره);
#پایان_اگر
            اكسر;
        }
#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.پنجره);
#پایان_اگر
        إذا (!videodata->آخرین_نما_change_deadline) /* no recent mode changes */ {
            داده->pending_focus = PENDING_FOCUS_NONE;
            داده->pending_focus_زمان = 0;
            X11_Dispatch_Focus_درون(_this, داده);
        } وإلا {
            داده->pending_focus = PENDING_FOCUS_درون;
            داده->pending_focus_زمان = SDL_GetTicks() + PENDING_FOCUS_زمان;
        }
        داده->آخرین_focus_event_زمان = SDL_GetTicks();
    } اكسر;

        // Losing input focus?
    حالة Focus_بیرون:
    {
        إذا (xevent->xfocus.نما == NotifyGrab || xevent->xfocus.نما == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.پنجره);
#پایان_اگر
            اكسر;
        }
        إذا (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_اشاره_گر) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.پنجره);
#پایان_اگر
            اكسر;
        }
#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.پنجره);
#پایان_اگر
        إذا (!videodata->آخرین_نما_change_deadline) /* no recent mode changes */ {
            داده->pending_focus = PENDING_FOCUS_NONE;
            داده->pending_focus_زمان = 0;
            X11_Dispatch_Focus_بیرون(_this, داده);
        } وإلا {
            داده->pending_focus = PENDING_FOCUS_بیرون;
            داده->pending_focus_زمان = SDL_GetTicks() + PENDING_FOCUS_زمان;
        }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        إذا (داده->اشاره_گر_barrier_فعال == true) {
            X11_ConfineCursorWithFlags(_this, داده->پنجره, عدم, X11_BARRIER_HANDLED_BY_EVENT);
        }
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XFIXES
    } اكسر;


        // Have we been iconified?
    حالة UnmapNotify:
    {
        XEvent ev;

#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.پنجره);
#پایان_اگر

        إذا (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } وإلا {
            X11_DispatchUnmapNotify(داده);
        }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        إذا (داده->اشاره_گر_barrier_فعال == true) {
            X11_ConfineCursorWithFlags(_this, داده->پنجره, عدم, X11_BARRIER_HANDLED_BY_EVENT);
        }
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XFIXES
    } اكسر;

        // Have we been restored?
    حالة MapNotify:
    {
#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.پنجره);
#پایان_اگر
        X11_DispatchMapNotify(داده);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        إذا (داده->اشاره_گر_barrier_فعال == true) {
            X11_ConfineCursorWithFlags(_this, داده->پنجره, &داده->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XFIXES
    } اكسر;

        // Have we been resized or moved?
    حالة ConfigureNotify:
    {
#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.پنجره,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.عرض, xevent->xconfigure.ارتفاع);
#پایان_اگر
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        إذا (!xevent->xconfigure.send_event) {
            بیعلامت صحيح رقم_Children;
            پنجره_2 فرزند_Return, ریشه_2, والد_2;
            پنجره_2 *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_آخرین_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_پنجره_Error_Handler);

            X11_XQuery_درخت(داده->videodata->display, xevent->xconfigure.پنجره, &ریشه_2, &والد_2, &Children, &رقم_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      والد_2, Default_ریشه_پنجره(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &فرزند_Return);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            إذا (x11_آخرین_error == Bad_پنجره) {
                اكسر;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        ثابت SDL_پنجره_Flags تغییریافته = X11_GetNetWMState(_this, داده->پنجره, xevent->xproperty.پنجره) ^ داده->پنجره->flags;
        إذا (تغییریافته & (SDL_پنجره_FULLSCREEN | SDL_پنجره_MAXIMIZED)) {
            SDL_copyp(&داده->pending_xconfigure, &xevent->xconfigure);
            داده->emit_اندازه_move_after_property_notify = true;
        }

        إذا (!داده->emit_اندازه_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(داده, &xevent->xconfigure);
        }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(داده->پنجره, &xevent->xconfigure);
#پایان_اگر /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } اكسر;

        // Have we been requested to quit (or another client message?)
    حالة Client_پیام:
    {
        ساكن صحيح xdnd_نسخه = 0;

        إذا (xevent->xclient.پیام_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.داده.l[1] & 1;
            داده->xdnd_منبع = xevent->xclient.داده.l[0];
            xdnd_نسخه = (xevent->xclient.داده.l[1] >> 24);
#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", داده->xdnd_منبع);
            SDL_Log("Protocol version to use : %d", xdnd_نسخه);
            SDL_Log("More then 3 data types : %d", (صحيح)use_list);
#پایان_اگر

            إذا (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, داده->xdnd_منبع, videodata->atoms.XdndTypeList);
                // pick one
                داده->xdnd_req = X11_Pick_هدف(display, (Atom *)p.داده, p.شمار);
                X11_XFree(p.داده);
            } وإلا {
                // pick from list of three
                داده->xdnd_req = X11_Pick_هدف_From_Atoms(display, xevent->xclient.داده.l[2], xevent->xclient.داده.l[3], xevent->xclient.داده.l[4]);
            }
        } وإلا إذا (xevent->xclient.پیام_type == videodata->atoms.XdndLeave) {
#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.داده.l[0]);
#پایان_اگر
            SDL_SendDropComplete(داده->پنجره);
        } وإلا إذا (xevent->xclient.پیام_type == videodata->atoms.XdndPosition) {

#اگر_تعریف_شده DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            إذا (xdnd_نسخه >= 2) {
                act = xevent->xclient.داده.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#پایان_اگر
            {
                // Drag and Drop position
                صحيح ریشه_x, ریشه_y, پنجره_x, پنجره_y;
                پنجره_2 فرزند_Return;
                ریشه_x = xevent->xclient.داده.l[2] >> 16;
                ریشه_y = xevent->xclient.داده.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_ریشه_پنجره(display), داده->xwindow,
                                          ریشه_x, ریشه_y, &پنجره_x, &پنجره_y, &فرزند_Return);

                SDL_SendDropPosition(داده->پنجره, (عائم)پنجره_x, (عائم)پنجره_y);
            }

            // reply with status
            SDL_zero(m);
            m.type = Client_پیام;
            m.display = xevent->xclient.display;
            m.پنجره = xevent->xclient.داده.l[0];
            m.پیام_type = videodata->atoms.Xdnd_وضعیت;
            m.format = 32;
            m.داده.l[0] = داده->xwindow;
            m.داده.l[1] = (داده->xdnd_req != None);
            m.داده.l[2] = 0; // specify an empty rectangle
            m.داده.l[3] = 0;
            m.داده.l[4] = videodata->atoms.XdndActionCopy; // we only accept copying anyway

            X11_XSendEvent(display, xevent->xclient.داده.l[0], False, No_Event_ماسک, (XEvent *)&m);
            X11_XFlush(display);
        } وإلا إذا (xevent->xclient.پیام_type == videodata->atoms.XdndDrop) {
            إذا (داده->xdnd_req == None) {
                // say again - not interested!
                SDL_zero(m);
                m.type = Client_پیام;
                m.display = xevent->xclient.display;
                m.پنجره = xevent->xclient.داده.l[0];
                m.پیام_type = videodata->atoms.Xdnd_پایانیافته;
                m.format = 32;
                m.داده.l[0] = داده->xwindow;
                m.داده.l[1] = 0;
                m.داده.l[2] = None; // fail!
                X11_XSendEvent(display, xevent->xclient.داده.l[0], False, No_Event_ماسک, (XEvent *)&m);
            } وإلا {
                // convert
                إذا (xdnd_نسخه >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, داده->xdnd_req, videodata->atoms.PRIMARY, داده->xwindow, xevent->xclient.داده.l[2]);
                } وإلا {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, داده->xdnd_req, videodata->atoms.PRIMARY, داده->xwindow, Current_زمان);
                }
            }
        } وإلا إذا ((xevent->xclient.پیام_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.داده.l[0] == videodata->atoms._NET_WM_PING)) {
            پنجره_2 ریشه = Default_ریشه_پنجره(display);

#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.پنجره);
#پایان_اگر
            xevent->xclient.پنجره = ریشه;
            X11_XSendEvent(display, ریشه, False, Substructure_Redirect_ماسک | Substructure_Notify_ماسک, xevent);
            اكسر;
        }

        وإلا إذا ((xevent->xclient.پیام_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.داده.l[0] == videodata->atoms.WM_DELETE_پنجره)) {

#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.پنجره);
#پایان_اگر
            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_CLOSE_REQUESTED, 0, 0);
            اكسر;
        } وإلا إذا ((xevent->xclient.پیام_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.داده.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#اگر_تعریف_شده DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", داده);
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(داده->پنجره, &xevent->xclient);
#پایان_اگر /* SDL_VIDEO_DRIVER_X11_XSYNC */
            اكسر;
        }
    } اكسر;

        // Do we need to refresh ourselves?
    حالة Expose:
    {
#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.پنجره, xevent->xexpose.شمار);
#پایان_اگر
        SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_EXPOSED, 0, 0);
    } اكسر;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    حالة کلید_Press:
    حالة کلید_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        إذا (داده->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            اكسر;
        } وإلا إذا (xevent->xkey.serial == videodata->xinput_آخرین_کلید_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_آخرین_keyboard_device;
        }

        X11_Handle_کلید_Event(_this, داده, keyboardID, xevent);
    } اكسر;

    حالة MotionNotify:
    {
        إذا (X11_Xinput2_Handles_Motion_For_پنجره(داده)) {
            // This input is being handled by XInput2
            اكسر;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        إذا (!mouse->relative_نما) {
#اگر_تعریف_شده DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.پنجره, xevent->xmotion.x, xevent->xmotion.y);
#پایان_اگر

            X11_Process_اصابت_Test(_this, داده, (عائم)xevent->xmotion.x, (عائم)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, داده->پنجره, SDL_GLOBAL_MOUSE_ID, false, (عائم)xevent->xmotion.x, (عائم)xevent->xmotion.y);
        }
    } اكسر;

    حالة ButtonPress:
    {
        إذا (داده->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_آخرین_button_serial) {
            // This input event was handled by XInput2.
            اكسر;
        }

        X11_HandleButtonPress(_this, داده, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.زمان, xevent->xbutton.serial);
    } اكسر;

    حالة ButtonRelease:
    {
        إذا (داده->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_آخرین_button_serial) {
            // This input event was handled by XInput2.
            اكسر;
        }

        X11_HandleButtonRelease(_this, داده, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.زمان);
    } اكسر;

    حالة PropertyNotify:
    {
#اگر_تعریف_شده DEBUG_XEVENTS
        بیعلامت حرف *propdata;
        صحيح وضعیت, real_format;
        Atom real_type;
        بیعلامت دراز اقلام_read, اقلام_چپ;

        حرف *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        إذا (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.پنجره, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.زمان);
            X11_XFree(name);
        }

        وضعیت = X11_XGet_پنجره_Property(display, داده->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &اقلام_read, &اقلام_چپ, &propdata);
        إذا (وضعیت == Success && اقلام_read > 0) {
            إذا (real_type == XA_INTEGER) {
                صحيح *مقادیر = (صحيح *)propdata;

                SDL_Log("{");
                لكل (i = 0; i < اقلام_read; i++) {
                    SDL_Log(" %d", مقادیر[i]);
                }
                SDL_Log(" }");
            } وإلا إذا (real_type == XA_CARDINAL) {
                إذا (real_format == 32) {
                    Uint32 *مقادیر = (Uint32 *)propdata;

                    SDL_Log("{");
                    لكل (i = 0; i < اقلام_read; i++) {
                        SDL_Log(" %d", مقادیر[i]);
                    }
                    SDL_Log(" }");
                } وإلا إذا (real_format == 16) {
                    Uint16 *مقادیر = (Uint16 *)propdata;

                    SDL_Log("{");
                    لكل (i = 0; i < اقلام_read; i++) {
                        SDL_Log(" %d", مقادیر[i]);
                    }
                    SDL_Log(" }");
                } وإلا إذا (real_format == 8) {
                    Uint8 *مقادیر = (Uint8 *)propdata;

                    SDL_Log("{");
                    لكل (i = 0; i < اقلام_read; i++) {
                        SDL_Log(" %d", مقادیر[i]);
                    }
                    SDL_Log(" }");
                }
            } وإلا إذا (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } وإلا إذا (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                لكل (i = 0; i < اقلام_read; i++) {
                    حرف *atomname = X11_XGetAtomName(display, atoms[i]);
                    إذا (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } وإلا {
                حرف *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                إذا (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        إذا (وضعیت == Success) {
            X11_XFree(propdata);
        }
#پایان_اگر // DEBUG_XEVENTS

        /* Take advantage of this moment to make sure user_time has a
            valid timestamp from the X server, so if we later try to
            raise/restore this window, _NET_ACTIVE_WINDOW can have a
            non-zero timestamp, even if there's never been a mouse or
            key press to this window so far. Note that we don't try to
            set _NET_WM_USER_TIME here, though. That's only for legit
            user interaction with the window. */
        إذا (!داده->user_زمان) {
            داده->user_زمان = xevent->xproperty.زمان;
        }

        إذا (xevent->xproperty.atom == داده->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            ثابت SDL_پنجره_Flags flags = X11_GetNetWMState(_this, داده->پنجره, xevent->xproperty.پنجره);
            ثابت SDL_پنجره_Flags تغییریافته = flags ^ داده->پنجره->flags;

            إذا ((تغییریافته & SDL_پنجره_HIDDEN) && !(flags & SDL_پنجره_HIDDEN)) {
                X11_DispatchMapNotify(داده);
            }

            إذا (!SDL_پنجره_IS_POPUP(داده->پنجره)) {
                إذا (تغییریافته & SDL_پنجره_FULLSCREEN) {
                    داده->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    إذا (flags & SDL_پنجره_FULLSCREEN) {
                        إذا (!(flags & SDL_پنجره_MINIMIZED)) {
                            ثابت bool commit = SDL_memcmp(&داده->پنجره->current_fullscreen_نما, &داده->requested_fullscreen_نما, حجم(SDL_Display_نما)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_RESTORED, 0, 0);
                            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_ENTER_FULLSCREEN, 0, 0);
                            إذا (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&داده->پنجره->current_fullscreen_نما, &داده->پنجره->requested_fullscreen_نما);
                                SDL_Update_Fullscreen_نما(داده->پنجره, SDL_FULLSCREEN_OP_UPDATE, true);
                            } وإلا {
                                SDL_Update_Fullscreen_نما(داده->پنجره, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } وإلا {
                        SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_LEAVE_FULLSCREEN, 0, 0);
                        SDL_Update_Fullscreen_نما(داده->پنجره, false, false);

                        SDL_zero(داده->requested_fullscreen_نما);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_مجموعه_پنجره_Min_Max(داده->پنجره, !!(flags & SDL_پنجره_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        إذا (داده->fullscreen_borders_forced_on) {
                            داده->toggle_borders = true;
                            داده->fullscreen_borders_forced_on = false;
                        }
                    }

                    إذا ((flags & SDL_پنجره_FULLSCREEN) &&
                        (داده->border_بالاترین || داده->border_چپ || داده->border_bottom || داده->border_راست)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        داده->اندازه_move_event_flags |= X11_اندازه_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        داده->قبلی_borders_nonzero = true;
                    } وإلا إذا (!(flags & SDL_پنجره_FULLSCREEN) &&
                               داده->قبلی_borders_nonzero &&
                               (!داده->border_بالاترین && !داده->border_چپ && !داده->border_bottom && !داده->border_راست)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        داده->اندازه_move_event_flags |= X11_اندازه_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        داده->قبلی_borders_nonzero = false;
                    } وإلا {
                        داده->اندازه_move_event_flags = 0;
                        داده->قبلی_borders_nonzero = false;

                        إذا (!(داده->پنجره->flags & SDL_پنجره_FULLSCREEN) && داده->toggle_borders) {
                            داده->toggle_borders = false;
                            X11_مجموعه_پنجره_Bordered(_this, داده->پنجره, !(داده->پنجره->flags & SDL_پنجره_BORDERLESS));
                        }
                    }
                }
                إذا ((تغییریافته & SDL_پنجره_MAXIMIZED) && ((flags & SDL_پنجره_MAXIMIZED) && !(flags & SDL_پنجره_MINIMIZED))) {
                    داده->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    إذا ((تغییریافته & SDL_پنجره_MINIMIZED)) {
                        داده->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_RESTORED, 0, 0);
                    }
                    SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_MAXIMIZED, 0, 0);
                }
                إذا ((تغییریافته & SDL_پنجره_MINIMIZED) && (flags & SDL_پنجره_MINIMIZED)) {
                    داده->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_MINIMIZED, 0, 0);
                }
                إذا (!(flags & (SDL_پنجره_MAXIMIZED | SDL_پنجره_MINIMIZED))) {
                    داده->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    إذا (!(flags & SDL_پنجره_FULLSCREEN)) {
                        إذا (داده->pending_position) {
                            داده->pending_position = false;
                            داده->pending_operation |= X11_PENDING_OP_MOVE;
                            داده->expected.x = داده->پنجره->pending.x - داده->border_چپ;
                            داده->expected.y = داده->پنجره->pending.y - داده->border_بالاترین;
                            X11_XMove_پنجره(display, داده->xwindow, داده->expected.x, داده->expected.y);
                        }
                        إذا (داده->pending_اندازه) {
                            داده->pending_اندازه = false;
                            داده->pending_operation |= X11_PENDING_OP_RESIZE;
                            داده->expected.w = داده->پنجره->pending.w;
                            داده->expected.h = داده->پنجره->pending.h;
                            X11_XResize_پنجره(display, داده->xwindow, داده->پنجره->pending.w, داده->پنجره->pending.h);
                        }
                    }
                }
                إذا (داده->emit_اندازه_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(داده, &داده->pending_xconfigure);
                    داده->emit_اندازه_move_after_property_notify = false;
                }
                إذا ((flags & SDL_پنجره_درون_داد_FOCUS)) {
                    إذا (داده->pending_move) {
                        Dispatch_پنجره_Move(_this, داده, &داده->pending_move_نقطه);
                        داده->pending_move = false;
                    }
                }
            }
            إذا (تغییریافته & SDL_پنجره_OCCLUDED) {
                SDL_Send_پنجره_Event(داده->پنجره, (flags & SDL_پنجره_OCCLUDED) ? SDL_EVENT_پنجره_OCCLUDED : SDL_EVENT_پنجره_EXPOSED, 0, 0);
            }
        } وإلا إذا (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            صحيح format;
            بیعلامت دراز nitems, بایتها_after;
            بیعلامت حرف *prop_داده = عدم;

            إذا (X11_XGet_پنجره_Property(display, داده->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &بایتها_after, &prop_داده) == Success) {
                إذا (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_داده;

                    إذا ((state == 0 || state == 3) && !داده->پنجره->is_hiding && !(داده->پنجره->flags & SDL_پنجره_HIDDEN)) {
                        // Withdrawn or Iconic
                        إذا (!(داده->پنجره->flags & SDL_پنجره_MINIMIZED)) {
                            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_MINIMIZED, 0, 0);
                            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_OCCLUDED, 0, 0);
                        }
                    } وإلا إذا (state == 1) { // NormalState
                        إذا (داده->پنجره->flags & SDL_پنجره_MINIMIZED) {
                            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_RESTORED, 0, 0);
                            SDL_Send_پنجره_Event(داده->پنجره, SDL_EVENT_پنجره_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_داده);
            }
        } وإلا إذا (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } وإلا إذا (xevent->xproperty.atom == videodata->atoms.NET_قاب_EXTENTS) {
            X11_Get_Border_مقادیر(داده);
            إذا (داده->اندازه_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                داده->اندازه_move_event_flags &= ~X11_اندازه_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            إذا (!(داده->پنجره->flags & SDL_پنجره_FULLSCREEN) && داده->toggle_borders) {
                داده->toggle_borders = false;
                X11_مجموعه_پنجره_Bordered(_this, داده->پنجره, !(داده->پنجره->flags & SDL_پنجره_BORDERLESS));
            }
        }
    } اكسر;

    حالة SelectionNotify:
    {
        Atom هدف = xevent->xselection.هدف;
#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.پنجره,
               xevent->xselection.requestor, xevent->xselection.هدف);
#پایان_اگر
        إذا (هدف == داده->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, داده->xwindow, videodata->atoms.PRIMARY);

            إذا (p.format == 8) {
                حرف *saveptr = عدم;
                حرف *name = X11_XGetAtomName(display, هدف);
                إذا (name) {
                    حرف *token = SDL_strtok_r((حرف *)p.داده, "\r\n", &saveptr);
                    طالما (token) {
                        إذا ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_Send_Drop_متن(داده->پنجره, token);
                        } وإلا إذا (SDL_strcmp("text/uri-list", name) == 0) {
                            إذا (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(داده->پنجره, عدم, token);
                            }
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    X11_XFree(name);
                }
                SDL_SendDropComplete(داده->پنجره);
            }
            X11_XFree(p.داده);

            // send reply
            SDL_zero(m);
            m.type = Client_پیام;
            m.display = display;
            m.پنجره = داده->xdnd_منبع;
            m.پیام_type = videodata->atoms.Xdnd_پایانیافته;
            m.format = 32;
            m.داده.l[0] = داده->xwindow;
            m.داده.l[1] = 1;
            m.داده.l[2] = videodata->atoms.XdndActionCopy;
            X11_XSendEvent(display, داده->xdnd_منبع, False, No_Event_ماسک, (XEvent *)&m);

            X11_XSync(display, False);
        }
    } اكسر;

    افتراضي:
    {
#اگر_تعریف_شده DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.پنجره, xevent->type);
#پایان_اگر
    } اكسر;
    }
}

ساكن فراغ X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_Video_داده *videodata = _this->داخلی;
    صحيح i;

    إذا (videodata && videodata->windowlist) {
        لكل (i = 0; i < videodata->numwindows; ++i) {
            SDL_پنجره_داده *داده = videodata->windowlist[i];
            إذا (داده && داده->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                إذا (now >= داده->pending_focus_زمان) {
                    إذا (داده->pending_focus == PENDING_FOCUS_درون) {
                        X11_Dispatch_Focus_درون(_this, داده);
                    } وإلا {
                        X11_Dispatch_Focus_بیرون(_this, داده);
                    }
                    داده->pending_focus = PENDING_FOCUS_NONE;
                }
            }
        }
    }
}

ساكن Bool isAnyEvent(Display *display, XEvent *ev, XPointer arg)
{
    أرجع True;
}

ساكن bool X11_PollEvent(Display *display, XEvent *event)
{
    إذا (!X11_XCheckIfEvent(display, event, isAnyEvent, عدم)) {
        أرجع false;
    }

    أرجع true;
}

فراغ X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *داده = _this->داخلی;
    Display *req_display = داده->request_display;
    پنجره_2 xwindow = پنجره->داخلی->xwindow;
    XClient_پیام_Event event;

    SDL_zero(event);
    event.type = Client_پیام;
    event.display = req_display;
    event.send_event = True;
    event.پیام_type = داده->atoms._SDL_WAKEUP;
    event.format = 8;

    X11_XSendEvent(req_display, xwindow, False, No_Event_ماسک, (XEvent *)&event);
    /* XSendEvent returns a status and it could be BadValue or BadWindow. If an
      error happens it is an SDL's internal error and there is nothing we can do here. */
    X11_XFlush(req_display);
}

صحيح X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_داده *videodata = _this->داخلی;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    إذا (X11_PollEvent(display, &xevent)) {
        // Fall through
    } وإلا إذا (timeoutNS == 0) {
        أرجع 0;
    } وإلا {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        صحيح err = SDL_IOReady(Connection_عدد(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        إذا (err > 0) {
            إذا (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                أرجع 1;
            }
        } وإلا إذا (err == 0) {
            // Timeout
            أرجع 0;
        } وإلا {
            // Error returned from poll()/select()

            إذا (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                أرجع 1;
            } وإلا {
                أرجع err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    أرجع 1;
}

فراغ X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;
    XEvent xevent;
    صحيح i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    لكل (i = 0; i < _this->رقم_displays; ++i) {
        إذا (_this->displays[i]->داخلی->نما_switch_deadline_ns) {
            إذا (_this->displays[i]->fullscreen_پنجره) {
                _this->displays[i]->داخلی->نما_switch_deadline_ns = 0;
            } وإلا إذا (SDL_GetTicksNS() >= _this->displays[i]->داخلی->نما_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_مجموعه_Display_نما_For_Display(_this->displays[i], عدم);
                _this->displays[i]->داخلی->نما_switch_deadline_ns = 0;
            }
        }
    }

    إذا (داده->آخرین_نما_change_deadline) {
        إذا (SDL_GetTicks() >= داده->آخرین_نما_change_deadline) {
            داده->آخرین_نما_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    إذا (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        إذا (!داده->screensaver_activity || now >= (داده->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(داده->display);

#اگر_تعریف_شده SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#پایان_اگر

            داده->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    طالما (X11_PollEvent(داده->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    لكل (i = 0; i < داده->numwindows; ++i) {
        إذا (داده->windowlist[i] != عدم &&
            داده->windowlist[i]->flash_cancel_زمان &&
            SDL_GetTicks() >= داده->windowlist[i]->flash_cancel_زمان) {
            X11_Flash_پنجره(_this, داده->windowlist[i]->پنجره, SDL_FLASH_CANCEL);
        }
    }

    إذا (داده->xinput_hierarchy_تغییریافته) {
        X11_Xinput2UpdateDevices(_this);
        داده->xinput_hierarchy_تغییریافته = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_Video_داده *داده = _this->داخلی;
    صحيح dummy;
    صحيح major_نسخه, minor_نسخه;
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#اگر_تعریف_شده SDL_USE_LIBDBUS
    إذا (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        أرجع true;
    }

    إذا (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    إذا (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        إذا (!X11_XScreenSaverQueryExtension(داده->display, &dummy, &dummy) ||
            !X11_XScreen_Saver_Query_نسخه(داده->display,
                                          &major_نسخه, &minor_نسخه) ||
            major_نسخه < 1 || (major_نسخه == 1 && minor_نسخه < 1)) {
            أرجع SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(داده->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(داده->display);
        أرجع true;
    }
#پایان_اگر
    أرجع SDL_Unsupported();
}

#پایان_اگر // SDL_VIDEO_DRIVER_X11
