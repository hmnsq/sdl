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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11

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
#تعریف_کرو DEBUG_XEVENTS
#جے_انت

#جے_بنا_تعریف NET_WM_MOVERESIZE_ناپ_TOPLEFT
#تعریف_کرو NET_WM_MOVERESIZE_ناپ_TOPLEFT 0
#جے_انت

#جے_بنا_تعریف NET_WM_MOVERESIZE_ناپ_چوٹی
#تعریف_کرو NET_WM_MOVERESIZE_ناپ_چوٹی 1
#جے_انت

#جے_بنا_تعریف NET_WM_MOVERESIZE_ناپ_TOPRIGHT
#تعریف_کرو NET_WM_MOVERESIZE_ناپ_TOPRIGHT 2
#جے_انت

#جے_بنا_تعریف NET_WM_MOVERESIZE_ناپ_دایاں
#تعریف_کرو NET_WM_MOVERESIZE_ناپ_دایاں 3
#جے_انت

#جے_بنا_تعریف NET_WM_MOVERESIZE_ناپ_BOTTOMRIGHT
#تعریف_کرو NET_WM_MOVERESIZE_ناپ_BOTTOMRIGHT 4
#جے_انت

#جے_بنا_تعریف NET_WM_MOVERESIZE_ناپ_BOTTOM
#تعریف_کرو NET_WM_MOVERESIZE_ناپ_BOTTOM 5
#جے_انت

#جے_بنا_تعریف NET_WM_MOVERESIZE_ناپ_BOTTOMLEFT
#تعریف_کرو NET_WM_MOVERESIZE_ناپ_BOTTOMLEFT 6
#جے_انت

#جے_بنا_تعریف NET_WM_MOVERESIZE_ناپ_بایاں
#تعریف_کرو NET_WM_MOVERESIZE_ناپ_بایاں 7
#جے_انت

#جے_بنا_تعریف _NET_WM_MOVERESIZE_MOVE
#تعریف_کرو _NET_WM_MOVERESIZE_MOVE 8
#جے_انت

تعريفنوع بنية
{
    بنانشانی حرف *انکڑے;
    صحيح format, گنتی;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ساكن فراغ X11_ReadProperty(SDL_x11Prop *p, Display *disp, کھڑکی_2 w, Atom prop)
{
    بنانشانی حرف *ret = عدم;
    Atom type;
    صحيح fmt;
    بنانشانی لما گنتی;
    بنانشانی لما بائٹاں_بایاں;
    صحيح بائٹاں_fetch = 0;

    افعل {
        إذا (ret) {
            X11_XFree(ret);
        }
        X11_XGet_کھڑکی_Property(disp, w, prop, 0, بائٹاں_fetch, False, AnyPropertyType, &type, &fmt, &گنتی, &بائٹاں_بایاں, &ret);
        بائٹاں_fetch += بائٹاں_بایاں;
    } طالما (بائٹاں_بایاں != 0);

    p->انکڑے = ret;
    p->format = fmt;
    p->گنتی = گنتی;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
ساكن Atom X11_Pick_نشانہ(Display *disp, Atom list[], صحيح list_گنتی)
{
    ثابت Atom متن_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    لكل (صحيح i = 0; i < list_گنتی && request != متن_uri_request; i++) {
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
ساكن Atom X11_Pick_نشانہ_From_Atoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    صحيح گنتی = 0;
    Atom atom[3];
    إذا (a0 != None) {
        atom[گنتی++] = a0;
    }
    إذا (a1 != None) {
        atom[گنتی++] = a1;
    }
    إذا (a2 != None) {
        atom[گنتی++] = a2;
    }
    أرجع X11_Pick_نشانہ(disp, atom, گنتی);
}

بنية کلید_Repeat_Check_انکڑے
{
    XEvent *event;
    bool لبھیا;
};

ساكن Bool X11_کلید_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    بنية کلید_Repeat_Check_انکڑے *d = (بنية کلید_Repeat_Check_انکڑے *)arg;
    إذا (chkev->type == کلید_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.ویلا - d->event->xkey.ویلا < 2) {
        d->لبھیا = true;
    }
    أرجع False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
ساكن bool X11_کلید_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    بنية کلید_Repeat_Check_انکڑے d;
    d.event = event;
    d.لبھیا = false;
    إذا (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_کلید_Repeat_Check_If_Event, (XPointer)&d);
    }
    أرجع d.لبھیا;
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
ساكن فراغ *g_X11_Event_Hook_انکڑے = عدم;

فراغ SDL_سیٹ_X11_Event_Hook(SDL_X11EventHook callback, فراغ *userdata)
{
    g_X11EventHook = callback;
    g_X11_Event_Hook_انکڑے = userdata;
}

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
ساكن فراغ X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    إذا (X11_XGet_Event_انکڑے(videodata->display, cookie)) {
        إذا (!g_X11EventHook || g_X11EventHook(g_X11_Event_Hook_انکڑے, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFree_Event_انکڑے(videodata->display, cookie);
    }
}
#جے_انت // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

ساكن فراغ X11_Update_System_کلید_Modifiers(SDL_Video_انکڑے *viddata)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        إذا (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.ادھار_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } وإلا
#جے_انت
        {
        کھڑکی_2 junk_کھڑکی;
        صحيح x, y;
        بنانشانی صحيح mod_نقاب;

        X11_XQuery_اشارہ_گر(viddata->display, Default_جڑ_کھڑکی(viddata->display), &junk_کھڑکی, &junk_کھڑکی, &x, &y, &x, &y, &mod_نقاب);
        viddata->keyboard.pressed_modifiers = mod_نقاب & (کھسکاؤ_نقاب_2 | Control_نقاب | Mod1_نقاب | Mod3_نقاب | Mod4_نقاب | Mod5_نقاب);
        viddata->keyboard.locked_modifiers = mod_نقاب & (جندرا_نقاب | viddata->keyboard.numlock_نقاب | viddata->keyboard.scrolllock_نقاب);
    }
}

ساكن فراغ X11_ReconcileModifiers(SDL_Video_انکڑے *viddata, bool کلید_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    إذا (کلید_pressed) {
        إذا (viddata->keyboard.pressed_modifiers & کھسکاؤ_نقاب_2) {
            إذا (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_کھسکاؤ) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_کھسکاؤ;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_کھسکاؤ);
            }
        }

        إذا (viddata->keyboard.pressed_modifiers & Control_نقاب) {
            إذا (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        إذا (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_نقاب) {
            إذا (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        إذا (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_نقاب) {
            إذا (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } وإلا {
        إذا (viddata->keyboard.pressed_modifiers & کھسکاؤ_نقاب_2) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_کھسکاؤ)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_کھسکاؤ;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_کھسکاؤ;
        }

        إذا (viddata->keyboard.pressed_modifiers & Control_نقاب) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        إذا (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_نقاب) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        إذا (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_نقاب) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        إذا (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_نقاب) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_منوال)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_منوال;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_منوال;
        }

        إذا (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_نقاب) {
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
    إذا (viddata->keyboard.locked_modifiers & کھسکاؤ_نقاب_2) {
        إذا (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_کھسکاؤ) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_کھسکاؤ;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_کھسکاؤ);
        } وإلا إذا (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_کھسکاؤ)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_کھسکاؤ;
        }
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_کھسکاؤ;
    }

    إذا (viddata->keyboard.locked_modifiers & Control_نقاب) {
        إذا (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } وإلا إذا (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_نقاب) {
        إذا (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } وإلا إذا (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_نقاب) {
        إذا (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } وإلا إذا (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_منوال;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_منوال;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    إذا (viddata->keyboard.locked_modifiers & جندرا_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_عدد;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_عدد;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_سیٹ_Mod_State(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

ساكن فراغ X11_Handle_Modifier_کلیدیں(SDL_Video_انکڑے *viddata, SDL_Scancode scancode, bool pressed)
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
    حالة SDLK_منوال:
        mod = SDL_KMOD_منوال;
        اكسر;
    حالة SDLK_LEVEL5_کھسکاؤ:
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
            بنانشانی صحيح cur_نقاب = viddata->keyboard.locked_modifiers;
            X11_Update_System_کلید_Modifiers(viddata);

            إذا (viddata->keyboard.locked_modifiers & جندرا_نقاب) {
                cur_نقاب |= جندرا_نقاب;
            } وإلا {
                cur_نقاب &= ~جندرا_نقاب;
            }
            إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_نقاب) {
                cur_نقاب |= viddata->keyboard.numlock_نقاب;
            } وإلا {
                cur_نقاب &= ~viddata->keyboard.numlock_نقاب;
            }
            إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_نقاب) {
                cur_نقاب |= viddata->keyboard.scrolllock_نقاب;
            } وإلا {
                cur_نقاب &= ~viddata->keyboard.scrolllock_نقاب;
            }

            viddata->keyboard.locked_modifiers = cur_نقاب;
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
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    Display *display = videodata->display;
    حرف کلیدیں[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_کلید_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_عدد | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= جندرا_نقاب | videodata->keyboard.numlock_نقاب| videodata->keyboard.scrolllock_نقاب;

    X11_XQueryKeymap(display, کلیدیں);

    ثابت bool *keystate = SDL_GetKeyboardState(عدم);
    لكل (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.کلید_layout); ++keycode) {
        ثابت SDL_Scancode scancode = videodata->keyboard.کلید_layout[keycode];
        ثابت bool x11_کلید_Pressed = (کلیدیں[keycode / 8] & (1 << (keycode % 8))) != 0;
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
            حالة SDLK_منوال:
            حالة SDLK_LEVEL5_کھسکاؤ:
                X11_Handle_Modifier_کلیدیں(videodata, scancode, true);
                SDL_Send_Keyboard_کلید_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                اكسر;
            افتراضي:
                اكسر;
            }
        } وإلا إذا (!x11_کلید_Pressed && sdl_کلید_Pressed) {
            X11_Handle_Modifier_کلیدیں(videodata, scancode, false);
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_کلید_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

ساكن فراغ X11_Dispatch_Focus_وچ(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *انکڑے)
{
#جے_تعریف_شدہ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", انکڑے->xwindow);
#جے_انت
    SDL_سیٹ_Keyboard_Focus(انکڑے->کھڑکی);
    X11_ReconcileKeyboardState(_this);
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    إذا (انکڑے->ic) {
        X11_XSetICFocus(انکڑے->ic);
    }
#جے_انت
    إذا (انکڑے->flashing_کھڑکی) {
        X11_Flash_کھڑکی(_this, انکڑے->کھڑکی, SDL_FLASH_CANCEL);
    }
}

ساكن فراغ X11_Dispatch_Focus_باہرلا(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *انکڑے)
{
#جے_تعریف_شدہ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", انکڑے->xwindow);
#جے_انت
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    إذا (انکڑے->کھڑکی == SDL_GetKeyboardFocus()) {
        SDL_سیٹ_Keyboard_Focus(عدم);
    }
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    إذا (انکڑے->ic) {
        X11_XUnsetICFocus(انکڑے->ic);
    }
#جے_انت
}

ساكن فراغ X11_DispatchMapNotify(SDL_کھڑکی_انکڑے *انکڑے)
{
    SDL_کھڑکی *کھڑکی = انکڑے->کھڑکی;

    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);
    انکڑے->was_shown = true;

    // This may be sent when restoring a minimized window.
    إذا (کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
        SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
    }

    إذا (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
        SDL_Update_کھڑکی_Grab(کھڑکی);
    }
}

ساكن فراغ X11_DispatchUnmapNotify(SDL_کھڑکی_انکڑے *انکڑے)
{
    SDL_کھڑکی *کھڑکی = انکڑے->کھڑکی;

    // This may be sent when minimizing a window.
    إذا (!کھڑکی->is_hiding) {
        SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
        SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_OCCLUDED, 0, 0);
    } وإلا {
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_HIDDEN, 0, 0);
    }
}

ساكن فراغ Dispatch_کھڑکی_Move(SDL_VideoDevice *_this, ثابت SDL_کھڑکی_انکڑے *انکڑے, ثابت SDL_نقطہ *نقطہ)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    SDL_کھڑکی *کھڑکی = انکڑے->کھڑکی;
    Display *display = videodata->display;
    XEvent evt;

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_اشارہ_گر(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_سنیہا;
    evt.xclient.کھڑکی = انکڑے->xwindow;
    evt.xclient.سنیہا_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.انکڑے.l[0] = (size_t)کھڑکی->x + نقطہ->x;
    evt.xclient.انکڑے.l[1] = (size_t)کھڑکی->y + نقطہ->y;
    evt.xclient.انکڑے.l[2] = _NET_WM_MOVERESIZE_MOVE;
    evt.xclient.انکڑے.l[3] = Button1;
    evt.xclient.انکڑے.l[4] = 0;
    X11_XSendEvent(display, Default_جڑ_کھڑکی(display), False, Substructure_Redirect_نقاب | Substructure_Notify_نقاب, &evt);

    X11_XSync(display, 0);
}

ساكن فراغ ویلا_سارنی_کھڑکی_Move(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *انکڑے, ثابت SDL_نقطہ *نقطہ)
{
    انکڑے->pending_move = true;
    انکڑے->pending_move_نقطہ = *نقطہ;
}

ساكن فراغ Initiate_کھڑکی_Resize(SDL_VideoDevice *_this, ثابت SDL_کھڑکی_انکڑے *انکڑے, ثابت SDL_نقطہ *نقطہ, صحيح direction)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    SDL_کھڑکی *کھڑکی = انکڑے->کھڑکی;
    Display *display = videodata->display;
    XEvent evt;

    إذا (direction < NET_WM_MOVERESIZE_ناپ_TOPLEFT || direction > NET_WM_MOVERESIZE_ناپ_بایاں) {
        أرجع;
    }

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_اشارہ_گر(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_سنیہا;
    evt.xclient.کھڑکی = انکڑے->xwindow;
    evt.xclient.سنیہا_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.انکڑے.l[0] = (size_t)کھڑکی->x + نقطہ->x;
    evt.xclient.انکڑے.l[1] = (size_t)کھڑکی->y + نقطہ->y;
    evt.xclient.انکڑے.l[2] = direction;
    evt.xclient.انکڑے.l[3] = Button1;
    evt.xclient.انکڑے.l[4] = 0;
    X11_XSendEvent(display, Default_جڑ_کھڑکی(display), False, Substructure_Redirect_نقاب | Substructure_Notify_نقاب, &evt);

    X11_XSync(display, 0);
}

bool X11_Process_کامیابی_Test(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *انکڑے, ثابت عائم x, ثابت عائم y, bool force_new_نتیجہ)
{
    SDL_کھڑکی *کھڑکی = انکڑے->کھڑکی;
    إذا (!کھڑکی->کامیابی_test) أرجع false;
    ثابت SDL_نقطہ نقطہ = { (صحيح)x, (صحيح)y };
    SDL_کامیابی_Test_نتیجہ rc = کھڑکی->کامیابی_test(کھڑکی, &نقطہ, کھڑکی->کامیابی_test_انکڑے);
    إذا (!force_new_نتیجہ && rc == انکڑے->کامیابی_test_نتیجہ) {
        أرجع true;
    }
    X11_سیٹ_کامیابی_Test_Cursor(rc);
    انکڑے->کامیابی_test_نتیجہ = rc;
    أرجع true;
}

bool X11_Trigger_کامیابی_Test_Action(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *انکڑے, ثابت عائم x, ثابت عائم y)
{
    SDL_کھڑکی *کھڑکی = انکڑے->کھڑکی;

    إذا (کھڑکی->کامیابی_test) {
        ثابت SDL_نقطہ نقطہ = { (صحيح)x, (صحيح)y };
        ساكن ثابت صحيح directions[] = {
            NET_WM_MOVERESIZE_ناپ_TOPLEFT, NET_WM_MOVERESIZE_ناپ_چوٹی,
            NET_WM_MOVERESIZE_ناپ_TOPRIGHT, NET_WM_MOVERESIZE_ناپ_دایاں,
            NET_WM_MOVERESIZE_ناپ_BOTTOMRIGHT, NET_WM_MOVERESIZE_ناپ_BOTTOM,
            NET_WM_MOVERESIZE_ناپ_BOTTOMLEFT, NET_WM_MOVERESIZE_ناپ_بایاں
        };

        بدل (انکڑے->کامیابی_test_نتیجہ) {
        حالة SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            إذا (انکڑے->کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
                Dispatch_کھڑکی_Move(_this, انکڑے, &نقطہ);
            } وإلا {
                ویلا_سارنی_کھڑکی_Move(_this, انکڑے, &نقطہ);
            }
            أرجع true;

        حالة SDL_HITTEST_RESIZE_TOPLEFT:
        حالة SDL_HITTEST_RESIZE_چوٹی:
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
        حالة SDL_HITTEST_RESIZE_دایاں:
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        حالة SDL_HITTEST_RESIZE_BOTTOM:
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
        حالة SDL_HITTEST_RESIZE_بایاں:
            Initiate_کھڑکی_Resize(_this, انکڑے, &نقطہ, directions[انکڑے->کامیابی_test_نتیجہ - SDL_HITTEST_RESIZE_TOPLEFT]);
            أرجع true;

        افتراضي:
            أرجع false;
        }
    }

    أرجع false;
}

ساكن فراغ X11_Update_User_ویلا(SDL_کھڑکی_انکڑے *انکڑے, ثابت بنانشانی لما latest)
{
    إذا (latest && (latest != انکڑے->user_ویلا)) {
        SDL_Video_انکڑے *videodata = انکڑے->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, انکڑے->xwindow, videodata->atoms.NET_WM_USER_ویلا,
                            XA_CARDINAL, 32, Prop_منوال_Replace,
                            (ثابت بنانشانی حرف *)&latest, 1);
#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", انکڑے->xwindow, latest);
#جے_انت
        انکڑے->user_ویلا = latest;
    }
}

ساكن بنانشانی حرف x11_آخری_error;
ساكن صحيح Bad_کھڑکی_Error_Handler(Display *d, XErrorEvent *e)
{
    x11_آخری_error = e->error_کوڈ;

    // Ignore BadWindow in cases where it's not fatal.
    إذا (e->error_کوڈ != Bad_کھڑکی) {
        حرف err_پیغام[128];
        X11_XGet_Error_متن(d, e->error_کوڈ, err_پیغام, حجم(err_پیغام));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_کوڈ, err_پیغام, e->request_کوڈ);
    }
    أرجع 0;
}

ساكن فراغ X11_HandleClipboardEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    صحيح i;
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_کھڑکی != None);
    SDL_assert(xevent->xany.کھڑکی == videodata->clipboard_کھڑکی);

    بدل (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    حالة SelectionRequest:
    {
        ثابت XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        صحيح mime_formats;
        بنانشانی حرف *seln_انکڑے;
        size_t seln_لمائی = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_Clipboard_انکڑے *clipboard;

#جے_تعریف_شدہ DEBUG_XEVENTS
        حرف *atom_name;
        atom_name = X11_XGetAtomName(display, req->نشانہ);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->نشانہ, atom_name);
        إذا (atom_name) {
            X11_XFree(atom_name);
        }
#جے_انت

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_آخری_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_کھڑکی_Error_Handler);

        إذا (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } وإلا {
            clipboard = &videodata->clipboard;
        }

        SDL_zero(sevent);
        sevent.xany.type = SelectionNotify;
        sevent.xselection.selection = req->selection;
        sevent.xselection.نشانہ = None;
        sevent.xselection.property = None; // tell them no by default
        sevent.xselection.requestor = req->requestor;
        sevent.xselection.ویلا = req->ویلا;

        /* !!! FIXME: We were probably storing this on the root window
           because an SDL window might go away...? but we don't have to do
           this now (or ever, really). */

        إذا (req->نشانہ == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_گنتی + 1) * حجم(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            لكل (i = 0; i < clipboard->mime_گنتی; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, Prop_منوال_Replace,
                                (بنانشانی حرف *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.نشانہ = XA_TARGETS;
            SDL_free(supportedFormats);
        } وإلا {
            إذا (clipboard->callback) {
                لكل (i = 0; i < clipboard->mime_گنتی; ++i) {
                    ثابت حرف *mime_type = clipboard->mime_types[i];
                    إذا (X11_XInternAtom(display, mime_type, False) != req->نشانہ) {
                        استمر;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_انکڑے = (بنانشانی حرف *)clipboard->callback(clipboard->userdata, mime_type, &seln_لمائی);
                    إذا (seln_انکڑے) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->نشانہ, 8, Prop_منوال_Replace,
                                            seln_انکڑے, seln_لمائی);
                        sevent.xselection.property = req->property;
                        sevent.xselection.نشانہ = req->نشانہ;
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
#جے_تعریف_شدہ DEBUG_XEVENTS
        ثابت حرف *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        ثابت حرف *نشانہ_Name = xsel->نشانہ ? X11_XGetAtomName(display, xsel->نشانہ) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, نشانہ_Name, propName);
#جے_انت
        إذا (xsel->نشانہ == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            بنانشانی حرف *انکڑے = عدم;
            صحيح format_property = 0;
            بنانشانی لما لمائی = 0;
            بنانشانی لما بائٹاں_بایاں = 0;
            صحيح j;

            X11_XGet_کھڑکی_Property(display, Get_کھڑکی(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &لمائی, &بائٹاں_بایاں, &انکڑے);

            صحيح allocationsize = (لمائی + 1) * حجم(حرف *);
            لكل (j = 0, patom = (Atom *)انکڑے; j < لمائی; j++, patom++) {
                حرف *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            حرف **new_mime_types = SDL_Allocate_Temporary_حافظہ(allocationsize);
            إذا (new_mime_types) {
                حرف *strPtr = (حرف *)(new_mime_types + لمائی + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                لكل (j = 0, patom = (Atom *)انکڑے; j < لمائی; j++, patom++) {
                    حرف *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    ثابت size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[لمائی] = عدم;

                SDL_SendClipboardUpdate(false, new_mime_types, لمائی);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            إذا (انکڑے) {
                X11_XFree(انکڑے);
            }
        }

        videodata->selection_اڈیک = false;
    } اكسر;

    حالة SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_Clipboard_انکڑے *clipboard = عدم;

#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.نشانہ);
#جے_انت

        إذا (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } وإلا إذا (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        إذا (clipboard && clipboard->callback) {
            إذا (clipboard->sequence) {
                SDL_Cancel_Clipboard_انکڑے(clipboard->sequence);
            } وإلا {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } اكسر;

    حالة PropertyNotify:
    {
        حرف *name_دا_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        إذا (SDL_strncmp(name_دا_atom, "SDL_SELECTION", حجم("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_قدر) {
            videodata->selection_incr_اڈیک = false;
        }

        إذا (name_دا_atom) {
            X11_XFree(name_دا_atom);
        }
    } اكسر;
    }
}

ساكن Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    أرجع ev->type == MapNotify &&
           ev->xmap.کھڑکی == unmap->کھڑکی &&
           ev->xmap.serial == unmap->serial;
}

ساكن Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    أرجع ev->type == ReparentNotify &&
           ev->xreparent.کھڑکی == unmap->کھڑکی &&
           ev->xreparent.serial == unmap->serial;
}

ساكن bool Is_بلند_Latin1(ثابت حرف *string, صحيح لمائی)
{
    طالما (لمائی-- > 0) {
        Uint8 ch = (Uint8)*string;
        إذا (ch >= 0x80) {
            أرجع true;
        }
        ++string;
    }
    أرجع false;
}

ساكن صحيح XLookupStringAsUTF8(XKeyEvent *event_struct, حرف *بفر_return, صحيح بائٹاں_بفر, کلید_Sym *keysym_return, XCompose_حالت *حالت_وچ_باہرلا)
{
    صحيح نتیجہ = X11_XLookupString(event_struct, بفر_return, بائٹاں_بفر, keysym_return, حالت_وچ_باہرلا);
    إذا (Is_بلند_Latin1(بفر_return, نتیجہ)) {
        حرف *utf8_متن = SDL_iconv_string("UTF-8", "ISO-8859-1", بفر_return, نتیجہ + 1);
        إذا (utf8_متن) {
            SDL_strlcpy(بفر_return, utf8_متن, بائٹاں_بفر);
            SDL_free(utf8_متن);
            أرجع SDL_strlen(بفر_return);
        } وإلا {
            أرجع 0;
        }
    }
    أرجع نتیجہ;
}

SDL_کھڑکی_انکڑے *X11_لبھو_کھڑکی(SDL_Video_انکڑے *videodata, کھڑکی_2 کھڑکی)
{
    إذا (videodata && videodata->windowlist) {
        لكل (صحيح i = 0; i < videodata->numwindows; ++i) {
            إذا ((videodata->windowlist[i] != عدم) &&
                (videodata->windowlist[i]->xwindow == کھڑکی)) {
                أرجع videodata->windowlist[i];
            }
        }
    }
    أرجع عدم;
}

Uint64 X11_GetEventTimestamp(بنانشانی لما ویلا)
{
    // FIXME: Get the event time in the SDL tick time base
    أرجع SDL_GetTicksNS();
}

فراغ X11_Handle_کلید_Event(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    Display *display = videodata->display;
    کلید_کوڈ_2 keycode = xevent->xkey.keycode;
    کلید_Sym keysym = No_علامت;
    صحيح متن_لمائی = 0;
    حرف متن[64];
    حالت_2 حالت = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == کلید_Press);
    SDL_Scancode scancode = videodata->keyboard.کلید_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.ویلا);

#جے_تعریف_شدہ DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.کھڑکی, (xevent->type == کلید_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#جے_انت
#جے_تعریف_شدہ DEBUG_SCANCODES
    إذا (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        صحيح min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_کلید_کوڈ_منزل_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysym_منزل_String(keysym));
    }
#جے_انت // DEBUG SCANCODES

    متن[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    إذا (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (کھسکاؤ_نقاب_2 | Control_نقاب | Mod1_نقاب | Mod3_نقاب | Mod4_نقاب | Mod5_نقاب);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (جندرا_نقاب | videodata->keyboard.numlock_نقاب | videodata->keyboard.scrolllock_نقاب);
    }

    إذا (SDL_متن_داخلہ_سرگرم(windowdata->کھڑکی)) {
        // filter events catches XIM events and sends them to the correct handler
        إذا (X11_XFilterEvent(xevent, None)) {
#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.کھڑکی);
#جے_انت
            handled_by_ime = true;
        }

        إذا (!handled_by_ime) {
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
            إذا (windowdata->ic && xevent->type == کلید_Press) {
                متن_لمائی = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, متن, حجم(متن) - 1,
                                      &keysym, &حالت);
            } وإلا {
                متن_لمائی = XLookupStringAsUTF8(&xevent->xkey, متن, حجم(متن) - 1, &keysym, عدم);
            }
#وإلا
            متن_لمائی = XLookupStringAsUTF8(&xevent->xkey, متن, حجم(متن) - 1, &keysym, عدم);
#جے_انت
        }
    }

    إذا (!handled_by_ime) {
        إذا (pressed) {
            X11_Handle_Modifier_کلیدیں(videodata, scancode, true);
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            إذا (*متن && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                متن[متن_لمائی] = '\0';
                X11_ClearComposition(windowdata);
                SDL_Send_Keyboard_متن(متن);
            }
        } وإلا {
            إذا (X11_کلید_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                أرجع;
            }

            X11_Handle_Modifier_کلیدیں(videodata, scancode, false);
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    إذا (pressed) {
        X11_Update_User_ویلا(windowdata, xevent->xkey.ویلا);
    }
}

فراغ X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *windowdata, SDL_MouseID mouseID, صحيح button, عائم x, عائم y, بنانشانی لما ویلا, بنانشانی لما serial)
{
    SDL_کھڑکی *کھڑکی = windowdata->کھڑکی;
    صحيح xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(ویلا);

#جے_تعریف_شدہ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#جے_انت

    SDL_Mouse *mouse = SDL_GetMouse();
    إذا (!mouse->relative_منوال && (x != mouse->x || y != mouse->y)) {
        X11_Process_کامیابی_Test(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, کھڑکی, mouseID, false, x, y);
    }

    إذا (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, کھڑکی, mouseID, (عائم)-xticks, (عائم)yticks, SDL_MOUSEWHEEL_عام);
    } وإلا {
        إذا (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        إذا (button == Button1) {
            إذا (X11_Trigger_کامیابی_Test_Action(_this, windowdata, x, y)) {
                SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_کامیابی_TEST, 0, 0);
                أرجع; // don't pass this event on to app.
            }
        }
        إذا (windowdata->آخری_focus_event_ویلا) {
            ثابت صحيح X11_FOCUS_CLICK_TIMEOUT = 10;
            إذا (SDL_GetTicks() < (windowdata->آخری_focus_event_ویلا + X11_FOCUS_CLICK_TIMEOUT)) {
                إذا (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->آخری_focus_event_ویلا = 0;
        }
        إذا (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, کھڑکی, mouseID, button, true);
        }
    }
    X11_Update_User_ویلا(windowdata, ویلا);
}

فراغ X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *windowdata, SDL_MouseID mouseID, صحيح button, بنانشانی لما ویلا)
{
    SDL_کھڑکی *کھڑکی = windowdata->کھڑکی;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    صحيح xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(ویلا);

#جے_تعریف_شدہ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#جے_انت
    إذا (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        إذا (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, کھڑکی, mouseID, button, false);

        إذا (کھڑکی->اندرونی->pending_grab) {
            X11_سیٹ_کھڑکی_Mouse_Grab(_this, کھڑکی, true);
        }
    }
}

فراغ X11_Get_Border_اقدار(SDL_کھڑکی_انکڑے *انکڑے)
{
    SDL_Video_انکڑے *videodata = انکڑے->videodata;
    Display *display = videodata->display;

    Atom type;
    صحيح format;
    بنانشانی لما nitems, بائٹاں_after;
    بنانشانی حرف *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    إذا (!(انکڑے->کھڑکی->flags & SDL_کھڑکی_BORDERLESS)) {
        إذا (X11_XGet_کھڑکی_Property(display, انکڑے->xwindow, videodata->atoms.NET_چوکھٹا_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &بائٹاں_after, &property) == Success) {
            إذا (type != None && nitems == 4) {
                انکڑے->border_بایاں = (صحيح)((لما *)property)[0];
                انکڑے->border_دایاں = (صحيح)((لما *)property)[1];
                انکڑے->border_چوٹی = (صحيح)((لما *)property)[2];
                انکڑے->border_bottom = (صحيح)((لما *)property)[3];
            }
            X11_XFree(property);

#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", انکڑے->border_بایاں, انکڑے->border_دایاں, انکڑے->border_چوٹی, انکڑے->border_bottom);
#جے_انت
        }
    } وإلا {
        انکڑے->border_بایاں = انکڑے->border_چوٹی = انکڑے->border_دایاں = انکڑے->border_bottom = 0;
    }
}

فراغ X11_EmitConfigureNotifyEvents(SDL_کھڑکی_انکڑے *انکڑے, XConfigureEvent *xevent)
{
    إذا (!انکڑے->ناپ_move_event_flags) {
        صحيح x = xevent->x;
        صحيح y = xevent->y;

        إذا (xevent->x != انکڑے->آخری_xconfigure.x ||
            xevent->y != انکڑے->آخری_xconfigure.y) {
            انکڑے->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_Global_منزل_Relative_For_کھڑکی(انکڑے->کھڑکی, x, y, &x, &y);
        SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_MOVED, x, y);

        لكل (SDL_کھڑکی *w = انکڑے->کھڑکی->پہلا_بچہ; w; w = w->اگلا_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            إذا (SDL_کھڑکی_IS_POPUP(w) && !(w->flags & SDL_کھڑکی_HIDDEN)) {
                X11_Update_کھڑکی_Position(w, true);
            }
        }

        إذا (xevent->چوڑائی != انکڑے->آخری_xconfigure.چوڑائی ||
            xevent->اچائی != انکڑے->آخری_xconfigure.اچائی) {
            انکڑے->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_RESIZED, xevent->چوڑائی, xevent->اچائی);
    }

    SDL_copyp(&انکڑے->آخری_xconfigure, xevent);
}

ساكن فراغ X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    Display *display;
    SDL_کھڑکی_انکڑے *انکڑے;
    XClient_سنیہا_Event m;
    صحيح i;

    SDL_assert(videodata != عدم);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    إذا (xevent->type != کلید_Press && xevent->type != کلید_Release) {
        إذا (X11_XFilterEvent(xevent, None)) {
#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.کھڑکی);
#جے_انت
            أرجع;
        }
    }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    إذا (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        أرجع;
    }
#جے_انت

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    إذا (g_X11EventHook) {
        إذا (!g_X11EventHook(g_X11_Event_Hook_انکڑے, xevent)) {
            أرجع;
        }
    }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
    إذا (videodata->xrandr_event_ادھار && (xevent->type == (videodata->xrandr_event_ادھار + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#جے_انت

#جے_تعریف_شدہ DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.کھڑکی);
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    إذا (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#جے_انت

        إذا (ev->subtype == XFixes_سیٹ_Selection_Owner_Notify)
        {
            إذا (ev->selection != videodata->atoms.CLIPBOARD)
                أرجع;

            إذا (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_کھڑکی)
                أرجع;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, Get_کھڑکی(_this), Current_ویلا);
        }

        أرجع;
    }
#جے_انت // SDL_VIDEO_DRIVER_X11_XFIXES

    إذا ((videodata->clipboard_کھڑکی != None) &&
        (videodata->clipboard_کھڑکی == xevent->xany.کھڑکی)) {
        X11_HandleClipboardEvent(_this, xevent);
        أرجع;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    انکڑے = X11_لبھو_کھڑکی(videodata, xevent->xany.کھڑکی);

    إذا (!انکڑے) {
        // The window for KeymapNotify, etc events is 0
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        إذا (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            بدل (xkbevent->any.xkb_type) {
            حالة XkbStateNotify:
            {
#جے_تعریف_شدہ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.کھڑکی);
#جے_انت
                إذا ((xkbevent->state.بدلیا & Xkb_گروہ_State_نقاب) && xkbevent->state.گروہ != videodata->keyboard.xkb.current_گروہ) {
                    videodata->keyboard.xkb.current_گروہ = xkbevent->state.گروہ;
                    SDL_سیٹ_Keymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_گروہ], true);
                }

                إذا (xkbevent->state.بدلیا & Xkb_Modifier_State_نقاب) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.ادھار_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } اكسر;

            حالة XkbMapNotify:
#جے_تعریف_شدہ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.کھڑکی);
                SDL_FALLTHROUGH;
#جے_انت
            حالة XkbNewKeyboardNotify:
            {
#جے_تعریف_شدہ DEBUG_XEVENTS
                إذا (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.کھڑکی);
                }
#جے_انت
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                إذا (xkbevent->any.serial != videodata->keyboard.xkb.آخری_map_serial) {
                    videodata->keyboard.xkb.آخری_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } اكسر;

            افتراضي:
                اكسر;
            }
        } وإلا
#جے_انت
        إذا (xevent->type == KeymapNotify) {
#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.کھڑکی);
#جے_انت
            إذا (SDL_GetKeyboardFocus() != عدم) {
                إذا (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } وإلا إذا (xevent->type == MappingNotify) {
            ثابت صحيح request = xevent->xmapping.request;

            إذا (request == Mapping_اشارہ_گر) {
#جے_تعریف_شدہ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.کھڑکی);
#جے_انت
                X11_Xinput2_Update_اشارہ_گر_Mapping(_this);
            } وإلا إذا (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#جے_تعریف_شدہ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.کھڑکی);
#جے_انت
                إذا (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } وإلا إذا (xevent->type == PropertyNotify && videodata) {
            حرف *name_دا_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            إذا (name_دا_atom) {
                إذا (SDL_startswith(name_دا_atom, "_ICC_PROFILE")) {
                    XWindow_گن attrib;
                    صحيح screennum;
                    لكل (i = 0; i < videodata->numwindows; ++i) {
                        إذا (videodata->windowlist[i] != عدم) {
                            انکڑے = videodata->windowlist[i];
                            X11_XGet_کھڑکی_گن(display, انکڑے->xwindow, &attrib);
                            screennum = X11_XScreen_نمبر_دا_Screen(attrib.screen);
                            إذا (screennum == 0 && SDL_strcmp(name_دا_atom, "_ICC_PROFILE") == 0) {
                                SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_ICCPROF_بدلیا, 0, 0);
                            } وإلا إذا (SDL_strncmp(name_دا_atom, "_ICC_PROFILE_", حجم("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_دا_atom) > حجم("_ICC_PROFILE_") - 1) {
                                صحيح iccscreennum = SDL_atoi(&name_دا_atom[حجم("_ICC_PROFILE_") - 1]);

                                إذا (screennum == iccscreennum) {
                                    SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_ICCPROF_بدلیا, 0, 0);
                                }
                            }
                        }
                    }
                } وإلا إذا (SDL_strcmp(name_دا_atom, "_NET_WORKAREA") == 0) {
                    لكل (i = 0; i < _this->عدد_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_بدلیا, 0, 0);
                    }
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
                } وإلا إذا (SDL_strcmp(name_دا_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_دا_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#جے_انت
                }
                X11_XFree(name_دا_atom);
            }
        }
        أرجع;
    }

    بدل (xevent->type) {

        // Gaining mouse coverage?
    حالة EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.کھڑکی,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.منوال);
        إذا (xevent->xcrossing.منوال == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        إذا (xevent->xcrossing.منوال == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#جے_انت
        SDL_سیٹ_Mouse_Focus(انکڑے->کھڑکی);

        mouse->آخری_x = xevent->xcrossing.x;
        mouse->آخری_y = xevent->xcrossing.y;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
        {
            // Only create the barriers if we have input focus
            SDL_کھڑکی_انکڑے *windowdata = انکڑے->کھڑکی->اندرونی;
            إذا ((انکڑے->اشارہ_گر_barrier_سرگرم == true) && windowdata->کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->کھڑکی, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#جے_انت

        إذا (!mouse->relative_منوال) {
            SDL_SendMouseMotion(0, انکڑے->کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (عائم)xevent->xcrossing.x, (عائم)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        إذا (!(انکڑے->کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE)) {
            SDL_Update_کھڑکی_Grab(انکڑے->کھڑکی);
        }

        X11_Process_کامیابی_Test(_this, انکڑے, mouse->آخری_x, mouse->آخری_y, true);
    } اكسر;
        // Losing mouse coverage?
    حالة LeaveNotify:
    {
#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.کھڑکی,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.منوال);
        إذا (xevent->xcrossing.منوال == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        إذا (xevent->xcrossing.منوال == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#جے_انت
        إذا (!SDL_GetMouse()->relative_منوال) {
            SDL_SendMouseMotion(0, انکڑے->کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (عائم)xevent->xcrossing.x, (عائم)xevent->xcrossing.y);
        }

        إذا (xevent->xcrossing.منوال != NotifyGrab &&
            xevent->xcrossing.منوال != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            إذا (!(انکڑے->کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
                X11_سیٹ_کھڑکی_Keyboard_Grab(_this, انکڑے->کھڑکی, false);
            }

            SDL_سیٹ_Mouse_Focus(عدم);
        }
    } اكسر;

        // Gaining input focus?
    حالة Focus_وچ:
    {
        إذا (xevent->xfocus.منوال == NotifyGrab || xevent->xfocus.منوال == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.کھڑکی);
#جے_انت
            اكسر;
        }

        إذا (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_اشارہ_گر) {
#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.کھڑکی);
#جے_انت
            اكسر;
        }
#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.کھڑکی);
#جے_انت
        إذا (!videodata->آخری_منوال_change_deadline) /* no recent mode changes */ {
            انکڑے->pending_focus = PENDING_FOCUS_NONE;
            انکڑے->pending_focus_ویلا = 0;
            X11_Dispatch_Focus_وچ(_this, انکڑے);
        } وإلا {
            انکڑے->pending_focus = PENDING_FOCUS_وچ;
            انکڑے->pending_focus_ویلا = SDL_GetTicks() + PENDING_FOCUS_ویلا;
        }
        انکڑے->آخری_focus_event_ویلا = SDL_GetTicks();
    } اكسر;

        // Losing input focus?
    حالة Focus_باہرلا:
    {
        إذا (xevent->xfocus.منوال == NotifyGrab || xevent->xfocus.منوال == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.کھڑکی);
#جے_انت
            اكسر;
        }
        إذا (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_اشارہ_گر) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.کھڑکی);
#جے_انت
            اكسر;
        }
#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.کھڑکی);
#جے_انت
        إذا (!videodata->آخری_منوال_change_deadline) /* no recent mode changes */ {
            انکڑے->pending_focus = PENDING_FOCUS_NONE;
            انکڑے->pending_focus_ویلا = 0;
            X11_Dispatch_Focus_باہرلا(_this, انکڑے);
        } وإلا {
            انکڑے->pending_focus = PENDING_FOCUS_باہرلا;
            انکڑے->pending_focus_ویلا = SDL_GetTicks() + PENDING_FOCUS_ویلا;
        }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        إذا (انکڑے->اشارہ_گر_barrier_سرگرم == true) {
            X11_ConfineCursorWithFlags(_this, انکڑے->کھڑکی, عدم, X11_BARRIER_HANDLED_BY_EVENT);
        }
#جے_انت // SDL_VIDEO_DRIVER_X11_XFIXES
    } اكسر;


        // Have we been iconified?
    حالة UnmapNotify:
    {
        XEvent ev;

#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.کھڑکی);
#جے_انت

        إذا (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } وإلا {
            X11_DispatchUnmapNotify(انکڑے);
        }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        إذا (انکڑے->اشارہ_گر_barrier_سرگرم == true) {
            X11_ConfineCursorWithFlags(_this, انکڑے->کھڑکی, عدم, X11_BARRIER_HANDLED_BY_EVENT);
        }
#جے_انت // SDL_VIDEO_DRIVER_X11_XFIXES
    } اكسر;

        // Have we been restored?
    حالة MapNotify:
    {
#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.کھڑکی);
#جے_انت
        X11_DispatchMapNotify(انکڑے);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        إذا (انکڑے->اشارہ_گر_barrier_سرگرم == true) {
            X11_ConfineCursorWithFlags(_this, انکڑے->کھڑکی, &انکڑے->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#جے_انت // SDL_VIDEO_DRIVER_X11_XFIXES
    } اكسر;

        // Have we been resized or moved?
    حالة ConfigureNotify:
    {
#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.کھڑکی,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.چوڑائی, xevent->xconfigure.اچائی);
#جے_انت
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        إذا (!xevent->xconfigure.send_event) {
            بنانشانی صحيح عدد_Children;
            کھڑکی_2 بچہ_Return, جڑ_2, ماپا_2;
            کھڑکی_2 *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_آخری_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_کھڑکی_Error_Handler);

            X11_XQuery_درخت(انکڑے->videodata->display, xevent->xconfigure.کھڑکی, &جڑ_2, &ماپا_2, &Children, &عدد_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      ماپا_2, Default_جڑ_کھڑکی(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &بچہ_Return);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            إذا (x11_آخری_error == Bad_کھڑکی) {
                اكسر;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        ثابت SDL_کھڑکی_Flags بدلیا = X11_GetNetWMState(_this, انکڑے->کھڑکی, xevent->xproperty.کھڑکی) ^ انکڑے->کھڑکی->flags;
        إذا (بدلیا & (SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_MAXIMIZED)) {
            SDL_copyp(&انکڑے->pending_xconfigure, &xevent->xconfigure);
            انکڑے->emit_ناپ_move_after_property_notify = true;
        }

        إذا (!انکڑے->emit_ناپ_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(انکڑے, &xevent->xconfigure);
        }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(انکڑے->کھڑکی, &xevent->xconfigure);
#جے_انت /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } اكسر;

        // Have we been requested to quit (or another client message?)
    حالة Client_سنیہا:
    {
        ساكن صحيح xdnd_نسخہ = 0;

        إذا (xevent->xclient.سنیہا_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.انکڑے.l[1] & 1;
            انکڑے->xdnd_سروت = xevent->xclient.انکڑے.l[0];
            xdnd_نسخہ = (xevent->xclient.انکڑے.l[1] >> 24);
#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", انکڑے->xdnd_سروت);
            SDL_Log("Protocol version to use : %d", xdnd_نسخہ);
            SDL_Log("More then 3 data types : %d", (صحيح)use_list);
#جے_انت

            إذا (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, انکڑے->xdnd_سروت, videodata->atoms.XdndTypeList);
                // pick one
                انکڑے->xdnd_req = X11_Pick_نشانہ(display, (Atom *)p.انکڑے, p.گنتی);
                X11_XFree(p.انکڑے);
            } وإلا {
                // pick from list of three
                انکڑے->xdnd_req = X11_Pick_نشانہ_From_Atoms(display, xevent->xclient.انکڑے.l[2], xevent->xclient.انکڑے.l[3], xevent->xclient.انکڑے.l[4]);
            }
        } وإلا إذا (xevent->xclient.سنیہا_type == videodata->atoms.XdndLeave) {
#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.انکڑے.l[0]);
#جے_انت
            SDL_SendDropComplete(انکڑے->کھڑکی);
        } وإلا إذا (xevent->xclient.سنیہا_type == videodata->atoms.XdndPosition) {

#جے_تعریف_شدہ DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            إذا (xdnd_نسخہ >= 2) {
                act = xevent->xclient.انکڑے.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#جے_انت
            {
                // Drag and Drop position
                صحيح جڑ_x, جڑ_y, کھڑکی_x, کھڑکی_y;
                کھڑکی_2 بچہ_Return;
                جڑ_x = xevent->xclient.انکڑے.l[2] >> 16;
                جڑ_y = xevent->xclient.انکڑے.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_جڑ_کھڑکی(display), انکڑے->xwindow,
                                          جڑ_x, جڑ_y, &کھڑکی_x, &کھڑکی_y, &بچہ_Return);

                SDL_SendDropPosition(انکڑے->کھڑکی, (عائم)کھڑکی_x, (عائم)کھڑکی_y);
            }

            // reply with status
            SDL_zero(m);
            m.type = Client_سنیہا;
            m.display = xevent->xclient.display;
            m.کھڑکی = xevent->xclient.انکڑے.l[0];
            m.سنیہا_type = videodata->atoms.Xdnd_حالت;
            m.format = 32;
            m.انکڑے.l[0] = انکڑے->xwindow;
            m.انکڑے.l[1] = (انکڑے->xdnd_req != None);
            m.انکڑے.l[2] = 0; // specify an empty rectangle
            m.انکڑے.l[3] = 0;
            m.انکڑے.l[4] = videodata->atoms.XdndActionCopy; // we only accept copying anyway

            X11_XSendEvent(display, xevent->xclient.انکڑے.l[0], False, No_Event_نقاب, (XEvent *)&m);
            X11_XFlush(display);
        } وإلا إذا (xevent->xclient.سنیہا_type == videodata->atoms.XdndDrop) {
            إذا (انکڑے->xdnd_req == None) {
                // say again - not interested!
                SDL_zero(m);
                m.type = Client_سنیہا;
                m.display = xevent->xclient.display;
                m.کھڑکی = xevent->xclient.انکڑے.l[0];
                m.سنیہا_type = videodata->atoms.Xdnd_مکمل;
                m.format = 32;
                m.انکڑے.l[0] = انکڑے->xwindow;
                m.انکڑے.l[1] = 0;
                m.انکڑے.l[2] = None; // fail!
                X11_XSendEvent(display, xevent->xclient.انکڑے.l[0], False, No_Event_نقاب, (XEvent *)&m);
            } وإلا {
                // convert
                إذا (xdnd_نسخہ >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, انکڑے->xdnd_req, videodata->atoms.PRIMARY, انکڑے->xwindow, xevent->xclient.انکڑے.l[2]);
                } وإلا {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, انکڑے->xdnd_req, videodata->atoms.PRIMARY, انکڑے->xwindow, Current_ویلا);
                }
            }
        } وإلا إذا ((xevent->xclient.سنیہا_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.انکڑے.l[0] == videodata->atoms._NET_WM_PING)) {
            کھڑکی_2 جڑ = Default_جڑ_کھڑکی(display);

#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.کھڑکی);
#جے_انت
            xevent->xclient.کھڑکی = جڑ;
            X11_XSendEvent(display, جڑ, False, Substructure_Redirect_نقاب | Substructure_Notify_نقاب, xevent);
            اكسر;
        }

        وإلا إذا ((xevent->xclient.سنیہا_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.انکڑے.l[0] == videodata->atoms.WM_DELETE_کھڑکی)) {

#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.کھڑکی);
#جے_انت
            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_CLOSE_REQUESTED, 0, 0);
            اكسر;
        } وإلا إذا ((xevent->xclient.سنیہا_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.انکڑے.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#جے_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", انکڑے);
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(انکڑے->کھڑکی, &xevent->xclient);
#جے_انت /* SDL_VIDEO_DRIVER_X11_XSYNC */
            اكسر;
        }
    } اكسر;

        // Do we need to refresh ourselves?
    حالة Expose:
    {
#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.کھڑکی, xevent->xexpose.گنتی);
#جے_انت
        SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
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
        إذا (انکڑے->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            اكسر;
        } وإلا إذا (xevent->xkey.serial == videodata->xinput_آخری_کلید_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_آخری_keyboard_device;
        }

        X11_Handle_کلید_Event(_this, انکڑے, keyboardID, xevent);
    } اكسر;

    حالة MotionNotify:
    {
        إذا (X11_Xinput2_Handles_Motion_For_کھڑکی(انکڑے)) {
            // This input is being handled by XInput2
            اكسر;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        إذا (!mouse->relative_منوال) {
#جے_تعریف_شدہ DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.کھڑکی, xevent->xmotion.x, xevent->xmotion.y);
#جے_انت

            X11_Process_کامیابی_Test(_this, انکڑے, (عائم)xevent->xmotion.x, (عائم)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, انکڑے->کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (عائم)xevent->xmotion.x, (عائم)xevent->xmotion.y);
        }
    } اكسر;

    حالة ButtonPress:
    {
        إذا (انکڑے->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_آخری_button_serial) {
            // This input event was handled by XInput2.
            اكسر;
        }

        X11_HandleButtonPress(_this, انکڑے, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.ویلا, xevent->xbutton.serial);
    } اكسر;

    حالة ButtonRelease:
    {
        إذا (انکڑے->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_آخری_button_serial) {
            // This input event was handled by XInput2.
            اكسر;
        }

        X11_HandleButtonRelease(_this, انکڑے, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.ویلا);
    } اكسر;

    حالة PropertyNotify:
    {
#جے_تعریف_شدہ DEBUG_XEVENTS
        بنانشانی حرف *propdata;
        صحيح حالت, real_format;
        Atom real_type;
        بنانشانی لما اشیاء_read, اشیاء_بایاں;

        حرف *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        إذا (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.کھڑکی, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.ویلا);
            X11_XFree(name);
        }

        حالت = X11_XGet_کھڑکی_Property(display, انکڑے->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &اشیاء_read, &اشیاء_بایاں, &propdata);
        إذا (حالت == Success && اشیاء_read > 0) {
            إذا (real_type == XA_INTEGER) {
                صحيح *اقدار = (صحيح *)propdata;

                SDL_Log("{");
                لكل (i = 0; i < اشیاء_read; i++) {
                    SDL_Log(" %d", اقدار[i]);
                }
                SDL_Log(" }");
            } وإلا إذا (real_type == XA_CARDINAL) {
                إذا (real_format == 32) {
                    Uint32 *اقدار = (Uint32 *)propdata;

                    SDL_Log("{");
                    لكل (i = 0; i < اشیاء_read; i++) {
                        SDL_Log(" %d", اقدار[i]);
                    }
                    SDL_Log(" }");
                } وإلا إذا (real_format == 16) {
                    Uint16 *اقدار = (Uint16 *)propdata;

                    SDL_Log("{");
                    لكل (i = 0; i < اشیاء_read; i++) {
                        SDL_Log(" %d", اقدار[i]);
                    }
                    SDL_Log(" }");
                } وإلا إذا (real_format == 8) {
                    Uint8 *اقدار = (Uint8 *)propdata;

                    SDL_Log("{");
                    لكل (i = 0; i < اشیاء_read; i++) {
                        SDL_Log(" %d", اقدار[i]);
                    }
                    SDL_Log(" }");
                }
            } وإلا إذا (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } وإلا إذا (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                لكل (i = 0; i < اشیاء_read; i++) {
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
        إذا (حالت == Success) {
            X11_XFree(propdata);
        }
#جے_انت // DEBUG_XEVENTS

        /* Take advantage of this moment to make sure user_time has a
            valid timestamp from the X server, so if we later try to
            raise/restore this window, _NET_ACTIVE_WINDOW can have a
            non-zero timestamp, even if there's never been a mouse or
            key press to this window so far. Note that we don't try to
            set _NET_WM_USER_TIME here, though. That's only for legit
            user interaction with the window. */
        إذا (!انکڑے->user_ویلا) {
            انکڑے->user_ویلا = xevent->xproperty.ویلا;
        }

        إذا (xevent->xproperty.atom == انکڑے->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            ثابت SDL_کھڑکی_Flags flags = X11_GetNetWMState(_this, انکڑے->کھڑکی, xevent->xproperty.کھڑکی);
            ثابت SDL_کھڑکی_Flags بدلیا = flags ^ انکڑے->کھڑکی->flags;

            إذا ((بدلیا & SDL_کھڑکی_HIDDEN) && !(flags & SDL_کھڑکی_HIDDEN)) {
                X11_DispatchMapNotify(انکڑے);
            }

            إذا (!SDL_کھڑکی_IS_POPUP(انکڑے->کھڑکی)) {
                إذا (بدلیا & SDL_کھڑکی_FULLSCREEN) {
                    انکڑے->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    إذا (flags & SDL_کھڑکی_FULLSCREEN) {
                        إذا (!(flags & SDL_کھڑکی_MINIMIZED)) {
                            ثابت bool commit = SDL_memcmp(&انکڑے->کھڑکی->current_fullscreen_منوال, &انکڑے->requested_fullscreen_منوال, حجم(SDL_Display_منوال)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
                            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_ENTER_FULLSCREEN, 0, 0);
                            إذا (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&انکڑے->کھڑکی->current_fullscreen_منوال, &انکڑے->کھڑکی->requested_fullscreen_منوال);
                                SDL_Update_Fullscreen_منوال(انکڑے->کھڑکی, SDL_FULLSCREEN_OP_UPDATE, true);
                            } وإلا {
                                SDL_Update_Fullscreen_منوال(انکڑے->کھڑکی, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } وإلا {
                        SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_LEAVE_FULLSCREEN, 0, 0);
                        SDL_Update_Fullscreen_منوال(انکڑے->کھڑکی, false, false);

                        SDL_zero(انکڑے->requested_fullscreen_منوال);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_سیٹ_کھڑکی_Min_Max(انکڑے->کھڑکی, !!(flags & SDL_کھڑکی_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        إذا (انکڑے->fullscreen_borders_forced_on) {
                            انکڑے->toggle_borders = true;
                            انکڑے->fullscreen_borders_forced_on = false;
                        }
                    }

                    إذا ((flags & SDL_کھڑکی_FULLSCREEN) &&
                        (انکڑے->border_چوٹی || انکڑے->border_بایاں || انکڑے->border_bottom || انکڑے->border_دایاں)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        انکڑے->ناپ_move_event_flags |= X11_ناپ_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        انکڑے->پچھلا_borders_nonzero = true;
                    } وإلا إذا (!(flags & SDL_کھڑکی_FULLSCREEN) &&
                               انکڑے->پچھلا_borders_nonzero &&
                               (!انکڑے->border_چوٹی && !انکڑے->border_بایاں && !انکڑے->border_bottom && !انکڑے->border_دایاں)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        انکڑے->ناپ_move_event_flags |= X11_ناپ_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        انکڑے->پچھلا_borders_nonzero = false;
                    } وإلا {
                        انکڑے->ناپ_move_event_flags = 0;
                        انکڑے->پچھلا_borders_nonzero = false;

                        إذا (!(انکڑے->کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && انکڑے->toggle_borders) {
                            انکڑے->toggle_borders = false;
                            X11_سیٹ_کھڑکی_Bordered(_this, انکڑے->کھڑکی, !(انکڑے->کھڑکی->flags & SDL_کھڑکی_BORDERLESS));
                        }
                    }
                }
                إذا ((بدلیا & SDL_کھڑکی_MAXIMIZED) && ((flags & SDL_کھڑکی_MAXIMIZED) && !(flags & SDL_کھڑکی_MINIMIZED))) {
                    انکڑے->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    إذا ((بدلیا & SDL_کھڑکی_MINIMIZED)) {
                        انکڑے->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
                    }
                    SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_MAXIMIZED, 0, 0);
                }
                إذا ((بدلیا & SDL_کھڑکی_MINIMIZED) && (flags & SDL_کھڑکی_MINIMIZED)) {
                    انکڑے->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
                }
                إذا (!(flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_MINIMIZED))) {
                    انکڑے->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    إذا (!(flags & SDL_کھڑکی_FULLSCREEN)) {
                        إذا (انکڑے->pending_position) {
                            انکڑے->pending_position = false;
                            انکڑے->pending_operation |= X11_PENDING_OP_MOVE;
                            انکڑے->expected.x = انکڑے->کھڑکی->pending.x - انکڑے->border_بایاں;
                            انکڑے->expected.y = انکڑے->کھڑکی->pending.y - انکڑے->border_چوٹی;
                            X11_XMove_کھڑکی(display, انکڑے->xwindow, انکڑے->expected.x, انکڑے->expected.y);
                        }
                        إذا (انکڑے->pending_ناپ) {
                            انکڑے->pending_ناپ = false;
                            انکڑے->pending_operation |= X11_PENDING_OP_RESIZE;
                            انکڑے->expected.w = انکڑے->کھڑکی->pending.w;
                            انکڑے->expected.h = انکڑے->کھڑکی->pending.h;
                            X11_XResize_کھڑکی(display, انکڑے->xwindow, انکڑے->کھڑکی->pending.w, انکڑے->کھڑکی->pending.h);
                        }
                    }
                }
                إذا (انکڑے->emit_ناپ_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(انکڑے, &انکڑے->pending_xconfigure);
                    انکڑے->emit_ناپ_move_after_property_notify = false;
                }
                إذا ((flags & SDL_کھڑکی_داخلہ_FOCUS)) {
                    إذا (انکڑے->pending_move) {
                        Dispatch_کھڑکی_Move(_this, انکڑے, &انکڑے->pending_move_نقطہ);
                        انکڑے->pending_move = false;
                    }
                }
            }
            إذا (بدلیا & SDL_کھڑکی_OCCLUDED) {
                SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, (flags & SDL_کھڑکی_OCCLUDED) ? SDL_EVENT_کھڑکی_OCCLUDED : SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
            }
        } وإلا إذا (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            صحيح format;
            بنانشانی لما nitems, بائٹاں_after;
            بنانشانی حرف *prop_انکڑے = عدم;

            إذا (X11_XGet_کھڑکی_Property(display, انکڑے->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &بائٹاں_after, &prop_انکڑے) == Success) {
                إذا (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_انکڑے;

                    إذا ((state == 0 || state == 3) && !انکڑے->کھڑکی->is_hiding && !(انکڑے->کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
                        // Withdrawn or Iconic
                        إذا (!(انکڑے->کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
                            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
                            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_OCCLUDED, 0, 0);
                        }
                    } وإلا إذا (state == 1) { // NormalState
                        إذا (انکڑے->کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
                            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
                            SDL_Send_کھڑکی_Event(انکڑے->کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_انکڑے);
            }
        } وإلا إذا (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } وإلا إذا (xevent->xproperty.atom == videodata->atoms.NET_چوکھٹا_EXTENTS) {
            X11_Get_Border_اقدار(انکڑے);
            إذا (انکڑے->ناپ_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                انکڑے->ناپ_move_event_flags &= ~X11_ناپ_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            إذا (!(انکڑے->کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && انکڑے->toggle_borders) {
                انکڑے->toggle_borders = false;
                X11_سیٹ_کھڑکی_Bordered(_this, انکڑے->کھڑکی, !(انکڑے->کھڑکی->flags & SDL_کھڑکی_BORDERLESS));
            }
        }
    } اكسر;

    حالة SelectionNotify:
    {
        Atom نشانہ = xevent->xselection.نشانہ;
#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.کھڑکی,
               xevent->xselection.requestor, xevent->xselection.نشانہ);
#جے_انت
        إذا (نشانہ == انکڑے->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, انکڑے->xwindow, videodata->atoms.PRIMARY);

            إذا (p.format == 8) {
                حرف *saveptr = عدم;
                حرف *name = X11_XGetAtomName(display, نشانہ);
                إذا (name) {
                    حرف *token = SDL_strtok_r((حرف *)p.انکڑے, "\r\n", &saveptr);
                    طالما (token) {
                        إذا ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_Send_Drop_متن(انکڑے->کھڑکی, token);
                        } وإلا إذا (SDL_strcmp("text/uri-list", name) == 0) {
                            إذا (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(انکڑے->کھڑکی, عدم, token);
                            }
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    X11_XFree(name);
                }
                SDL_SendDropComplete(انکڑے->کھڑکی);
            }
            X11_XFree(p.انکڑے);

            // send reply
            SDL_zero(m);
            m.type = Client_سنیہا;
            m.display = display;
            m.کھڑکی = انکڑے->xdnd_سروت;
            m.سنیہا_type = videodata->atoms.Xdnd_مکمل;
            m.format = 32;
            m.انکڑے.l[0] = انکڑے->xwindow;
            m.انکڑے.l[1] = 1;
            m.انکڑے.l[2] = videodata->atoms.XdndActionCopy;
            X11_XSendEvent(display, انکڑے->xdnd_سروت, False, No_Event_نقاب, (XEvent *)&m);

            X11_XSync(display, False);
        }
    } اكسر;

    افتراضي:
    {
#جے_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.کھڑکی, xevent->type);
#جے_انت
    } اكسر;
    }
}

ساكن فراغ X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    صحيح i;

    إذا (videodata && videodata->windowlist) {
        لكل (i = 0; i < videodata->numwindows; ++i) {
            SDL_کھڑکی_انکڑے *انکڑے = videodata->windowlist[i];
            إذا (انکڑے && انکڑے->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                إذا (now >= انکڑے->pending_focus_ویلا) {
                    إذا (انکڑے->pending_focus == PENDING_FOCUS_وچ) {
                        X11_Dispatch_Focus_وچ(_this, انکڑے);
                    } وإلا {
                        X11_Dispatch_Focus_باہرلا(_this, انکڑے);
                    }
                    انکڑے->pending_focus = PENDING_FOCUS_NONE;
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

فراغ X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    Display *req_display = انکڑے->request_display;
    کھڑکی_2 xwindow = کھڑکی->اندرونی->xwindow;
    XClient_سنیہا_Event event;

    SDL_zero(event);
    event.type = Client_سنیہا;
    event.display = req_display;
    event.send_event = True;
    event.سنیہا_type = انکڑے->atoms._SDL_WAKEUP;
    event.format = 8;

    X11_XSendEvent(req_display, xwindow, False, No_Event_نقاب, (XEvent *)&event);
    /* XSendEvent returns a status and it could be BadValue or BadWindow. If an
      error happens it is an SDL's internal error and there is nothing we can do here. */
    X11_XFlush(req_display);
}

صحيح X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
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
        صحيح err = SDL_IOReady(Connection_نمبر(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
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
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    XEvent xevent;
    صحيح i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    لكل (i = 0; i < _this->عدد_displays; ++i) {
        إذا (_this->displays[i]->اندرونی->منوال_switch_deadline_ns) {
            إذا (_this->displays[i]->fullscreen_کھڑکی) {
                _this->displays[i]->اندرونی->منوال_switch_deadline_ns = 0;
            } وإلا إذا (SDL_GetTicksNS() >= _this->displays[i]->اندرونی->منوال_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_سیٹ_Display_منوال_For_Display(_this->displays[i], عدم);
                _this->displays[i]->اندرونی->منوال_switch_deadline_ns = 0;
            }
        }
    }

    إذا (انکڑے->آخری_منوال_change_deadline) {
        إذا (SDL_GetTicks() >= انکڑے->آخری_منوال_change_deadline) {
            انکڑے->آخری_منوال_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    إذا (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        إذا (!انکڑے->screensaver_activity || now >= (انکڑے->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(انکڑے->display);

#جے_تعریف_شدہ SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#جے_انت

            انکڑے->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    طالما (X11_PollEvent(انکڑے->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    لكل (i = 0; i < انکڑے->numwindows; ++i) {
        إذا (انکڑے->windowlist[i] != عدم &&
            انکڑے->windowlist[i]->flash_cancel_ویلا &&
            SDL_GetTicks() >= انکڑے->windowlist[i]->flash_cancel_ویلا) {
            X11_Flash_کھڑکی(_this, انکڑے->windowlist[i]->کھڑکی, SDL_FLASH_CANCEL);
        }
    }

    إذا (انکڑے->xinput_hierarchy_بدلیا) {
        X11_Xinput2UpdateDevices(_this);
        انکڑے->xinput_hierarchy_بدلیا = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    صحيح dummy;
    صحيح major_نسخہ, minor_نسخہ;
#جے_انت // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#جے_تعریف_شدہ SDL_USE_LIBDBUS
    إذا (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        أرجع true;
    }

    إذا (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    إذا (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        إذا (!X11_XScreenSaverQueryExtension(انکڑے->display, &dummy, &dummy) ||
            !X11_XScreen_Saver_Query_نسخہ(انکڑے->display,
                                          &major_نسخہ, &minor_نسخہ) ||
            major_نسخہ < 1 || (major_نسخہ == 1 && minor_نسخہ < 1)) {
            أرجع SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(انکڑے->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(انکڑے->display);
        أرجع true;
    }
#جے_انت
    أرجع SDL_Unsupported();
}

#جے_انت // SDL_VIDEO_DRIVER_X11
