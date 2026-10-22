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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11

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
#وصف_ڪريو DEBUG_XEVENTS
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل NET_WM_MOVERESIZE_سائيز_TOPLEFT
#وصف_ڪريو NET_WM_MOVERESIZE_سائيز_TOPLEFT 0
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل NET_WM_MOVERESIZE_سائيز_چوٽي
#وصف_ڪريو NET_WM_MOVERESIZE_سائيز_چوٽي 1
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل NET_WM_MOVERESIZE_سائيز_TOPRIGHT
#وصف_ڪريو NET_WM_MOVERESIZE_سائيز_TOPRIGHT 2
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل NET_WM_MOVERESIZE_سائيز_ساڄو
#وصف_ڪريو NET_WM_MOVERESIZE_سائيز_ساڄو 3
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل NET_WM_MOVERESIZE_سائيز_BOTTOMRIGHT
#وصف_ڪريو NET_WM_MOVERESIZE_سائيز_BOTTOMRIGHT 4
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل NET_WM_MOVERESIZE_سائيز_BOTTOM
#وصف_ڪريو NET_WM_MOVERESIZE_سائيز_BOTTOM 5
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل NET_WM_MOVERESIZE_سائيز_BOTTOMLEFT
#وصف_ڪريو NET_WM_MOVERESIZE_سائيز_BOTTOMLEFT 6
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل NET_WM_MOVERESIZE_سائيز_کاٻو
#وصف_ڪريو NET_WM_MOVERESIZE_سائيز_کاٻو 7
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل _NET_WM_MOVERESIZE_MOVE
#وصف_ڪريو _NET_WM_MOVERESIZE_MOVE 8
#جيڪڏهن_پورو

تعريفنوع بنية
{
    بنانشان حرف *معلومات;
    صحيح format, ڳڻپ;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ساكن فراغ X11_ReadProperty(SDL_x11Prop *p, Display *disp, دري_2 w, Atom prop)
{
    بنانشان حرف *ret = عدم;
    Atom type;
    صحيح fmt;
    بنانشان ڊگهو ڳڻپ;
    بنانشان ڊگهو بائيٽون_کاٻو;
    صحيح بائيٽون_fetch = 0;

    افعل {
        إذا (ret) {
            X11_XFree(ret);
        }
        X11_XGet_دري_Property(disp, w, prop, 0, بائيٽون_fetch, False, AnyPropertyType, &type, &fmt, &ڳڻپ, &بائيٽون_کاٻو, &ret);
        بائيٽون_fetch += بائيٽون_کاٻو;
    } طالما (بائيٽون_کاٻو != 0);

    p->معلومات = ret;
    p->format = fmt;
    p->ڳڻپ = ڳڻپ;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
ساكن Atom X11_Pick_هدف(Display *disp, Atom list[], صحيح list_ڳڻپ)
{
    ثابت Atom متن_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    لكل (صحيح i = 0; i < list_ڳڻپ && request != متن_uri_request; i++) {
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
    صحيح ڳڻپ = 0;
    Atom atom[3];
    إذا (a0 != None) {
        atom[ڳڻپ++] = a0;
    }
    إذا (a1 != None) {
        atom[ڳڻپ++] = a1;
    }
    إذا (a2 != None) {
        atom[ڳڻپ++] = a2;
    }
    أرجع X11_Pick_هدف(disp, atom, ڳڻپ);
}

بنية ڪنجي_Repeat_Check_معلومات
{
    XEvent *event;
    bool مليو;
};

ساكن Bool X11_ڪنجي_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    بنية ڪنجي_Repeat_Check_معلومات *d = (بنية ڪنجي_Repeat_Check_معلومات *)arg;
    إذا (chkev->type == ڪنجي_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.وقت - d->event->xkey.وقت < 2) {
        d->مليو = true;
    }
    أرجع False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
ساكن bool X11_ڪنجي_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    بنية ڪنجي_Repeat_Check_معلومات d;
    d.event = event;
    d.مليو = false;
    إذا (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_ڪنجي_Repeat_Check_If_Event, (XPointer)&d);
    }
    أرجع d.مليو;
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
ساكن فراغ *g_X11_Event_Hook_معلومات = عدم;

فراغ SDL_سيٽ_X11_Event_Hook(SDL_X11EventHook callback, فراغ *userdata)
{
    g_X11EventHook = callback;
    g_X11_Event_Hook_معلومات = userdata;
}

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
ساكن فراغ X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_Video_معلومات *videodata = _this->اندروني;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    إذا (X11_XGet_Event_معلومات(videodata->display, cookie)) {
        إذا (!g_X11EventHook || g_X11EventHook(g_X11_Event_Hook_معلومات, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFree_Event_معلومات(videodata->display, cookie);
    }
}
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

ساكن فراغ X11_Update_System_ڪنجي_Modifiers(SDL_Video_معلومات *viddata)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        إذا (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.بنياد_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } وإلا
#جيڪڏهن_پورو
        {
        دري_2 junk_دري;
        صحيح x, y;
        بنانشان صحيح mod_نقاب;

        X11_XQuery_اشارو(viddata->display, Default_پاڙ_دري(viddata->display), &junk_دري, &junk_دري, &x, &y, &x, &y, &mod_نقاب);
        viddata->keyboard.pressed_modifiers = mod_نقاب & (سرڪايو_نقاب_2 | Control_نقاب | Mod1_نقاب | Mod3_نقاب | Mod4_نقاب | Mod5_نقاب);
        viddata->keyboard.locked_modifiers = mod_نقاب & (تالو_نقاب | viddata->keyboard.numlock_نقاب | viddata->keyboard.scrolllock_نقاب);
    }
}

ساكن فراغ X11_ReconcileModifiers(SDL_Video_معلومات *viddata, bool ڪنجي_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    إذا (ڪنجي_pressed) {
        إذا (viddata->keyboard.pressed_modifiers & سرڪايو_نقاب_2) {
            إذا (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_سرڪايو) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_سرڪايو;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_سرڪايو);
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
        إذا (viddata->keyboard.pressed_modifiers & سرڪايو_نقاب_2) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_سرڪايو)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_سرڪايو;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_سرڪايو;
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
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_گهڻائي)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_گهڻائي;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_گهڻائي;
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
    إذا (viddata->keyboard.locked_modifiers & سرڪايو_نقاب_2) {
        إذا (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_سرڪايو) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_سرڪايو;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_سرڪايو);
        } وإلا إذا (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_سرڪايو)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_سرڪايو;
        }
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_سرڪايو;
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
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_گهڻائي;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_گهڻائي;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    إذا (viddata->keyboard.locked_modifiers & تالو_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_انگ;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_انگ;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_سيٽ_Mod_State(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

ساكن فراغ X11_Handle_Modifier_ڪنجيون(SDL_Video_معلومات *viddata, SDL_Scancode scancode, bool pressed)
{
    ثابت SDL_Keycode keycode = SDL_Get_ڪنجي_From_Scancode(scancode, SDL_KMOD_NONE, false);
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
    حالة SDLK_گهڻائي:
        mod = SDL_KMOD_گهڻائي;
        اكسر;
    حالة SDLK_LEVEL5_سرڪايو:
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
            بنانشان صحيح cur_نقاب = viddata->keyboard.locked_modifiers;
            X11_Update_System_ڪنجي_Modifiers(viddata);

            إذا (viddata->keyboard.locked_modifiers & تالو_نقاب) {
                cur_نقاب |= تالو_نقاب;
            } وإلا {
                cur_نقاب &= ~تالو_نقاب;
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
    SDL_Video_معلومات *videodata = _this->اندروني;
    Display *display = videodata->display;
    حرف ڪنجيون[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_ڪنجي_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_انگ | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= تالو_نقاب | videodata->keyboard.numlock_نقاب| videodata->keyboard.scrolllock_نقاب;

    X11_XQueryKeymap(display, ڪنجيون);

    ثابت bool *keystate = SDL_GetKeyboardState(عدم);
    لكل (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.ڪنجي_layout); ++keycode) {
        ثابت SDL_Scancode scancode = videodata->keyboard.ڪنجي_layout[keycode];
        ثابت bool x11_ڪنجي_Pressed = (ڪنجيون[keycode / 8] & (1 << (keycode % 8))) != 0;
        ثابت bool sdl_ڪنجي_Pressed = keystate[scancode];

        إذا (x11_ڪنجي_Pressed && !sdl_ڪنجي_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            بدل (SDL_Get_ڪنجي_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            حالة SDLK_LCTRL:
            حالة SDLK_RCTRL:
            حالة SDLK_LSHIFT:
            حالة SDLK_RSHIFT:
            حالة SDLK_LALT:
            حالة SDLK_RALT:
            حالة SDLK_LGUI:
            حالة SDLK_RGUI:
            حالة SDLK_گهڻائي:
            حالة SDLK_LEVEL5_سرڪايو:
                X11_Handle_Modifier_ڪنجيون(videodata, scancode, true);
                SDL_Send_Keyboard_ڪنجي_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                اكسر;
            افتراضي:
                اكسر;
            }
        } وإلا إذا (!x11_ڪنجي_Pressed && sdl_ڪنجي_Pressed) {
            X11_Handle_Modifier_ڪنجيون(videodata, scancode, false);
            SDL_Send_Keyboard_ڪنجي_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_ڪنجي_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

ساكن فراغ X11_Dispatch_Focus_اندريون(SDL_VideoDevice *_this, SDL_دري_معلومات *معلومات)
{
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", معلومات->xwindow);
#جيڪڏهن_پورو
    SDL_سيٽ_Keyboard_Focus(معلومات->دري);
    X11_ReconcileKeyboardState(_this);
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
    إذا (معلومات->ic) {
        X11_XSetICFocus(معلومات->ic);
    }
#جيڪڏهن_پورو
    إذا (معلومات->flashing_دري) {
        X11_Flash_دري(_this, معلومات->دري, SDL_FLASH_CANCEL);
    }
}

ساكن فراغ X11_Dispatch_Focus_ٻاهريون(SDL_VideoDevice *_this, SDL_دري_معلومات *معلومات)
{
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", معلومات->xwindow);
#جيڪڏهن_پورو
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    إذا (معلومات->دري == SDL_GetKeyboardFocus()) {
        SDL_سيٽ_Keyboard_Focus(عدم);
    }
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
    إذا (معلومات->ic) {
        X11_XUnsetICFocus(معلومات->ic);
    }
#جيڪڏهن_پورو
}

ساكن فراغ X11_DispatchMapNotify(SDL_دري_معلومات *معلومات)
{
    SDL_دري *دري = معلومات->دري;

    SDL_Send_دري_Event(دري, SDL_EVENT_دري_SHOWN, 0, 0);
    معلومات->was_shown = true;

    // This may be sent when restoring a minimized window.
    إذا (دري->flags & SDL_دري_MINIMIZED) {
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESTORED, 0, 0);
        SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_EXPOSED, 0, 0);
    }

    إذا (دري->flags & SDL_دري_داخلا_FOCUS) {
        SDL_Update_دري_Grab(دري);
    }
}

ساكن فراغ X11_DispatchUnmapNotify(SDL_دري_معلومات *معلومات)
{
    SDL_دري *دري = معلومات->دري;

    // This may be sent when minimizing a window.
    إذا (!دري->is_hiding) {
        SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_MINIMIZED, 0, 0);
        SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_OCCLUDED, 0, 0);
    } وإلا {
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_HIDDEN, 0, 0);
    }
}

ساكن فراغ Dispatch_دري_Move(SDL_VideoDevice *_this, ثابت SDL_دري_معلومات *معلومات, ثابت SDL_نقطو *نقطو)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    SDL_دري *دري = معلومات->دري;
    Display *display = videodata->display;
    XEvent evt;

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_اشارو(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_پيغام;
    evt.xclient.دري = معلومات->xwindow;
    evt.xclient.پيغام_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.معلومات.l[0] = (size_t)دري->x + نقطو->x;
    evt.xclient.معلومات.l[1] = (size_t)دري->y + نقطو->y;
    evt.xclient.معلومات.l[2] = _NET_WM_MOVERESIZE_MOVE;
    evt.xclient.معلومات.l[3] = Button1;
    evt.xclient.معلومات.l[4] = 0;
    X11_XSendEvent(display, Default_پاڙ_دري(display), False, Substructure_Redirect_نقاب | Substructure_Notify_نقاب, &evt);

    X11_XSync(display, 0);
}

ساكن فراغ وقت_جدول_دري_Move(SDL_VideoDevice *_this, SDL_دري_معلومات *معلومات, ثابت SDL_نقطو *نقطو)
{
    معلومات->pending_move = true;
    معلومات->pending_move_نقطو = *نقطو;
}

ساكن فراغ Initiate_دري_Resize(SDL_VideoDevice *_this, ثابت SDL_دري_معلومات *معلومات, ثابت SDL_نقطو *نقطو, صحيح direction)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    SDL_دري *دري = معلومات->دري;
    Display *display = videodata->display;
    XEvent evt;

    إذا (direction < NET_WM_MOVERESIZE_سائيز_TOPLEFT || direction > NET_WM_MOVERESIZE_سائيز_کاٻو) {
        أرجع;
    }

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_اشارو(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_پيغام;
    evt.xclient.دري = معلومات->xwindow;
    evt.xclient.پيغام_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.معلومات.l[0] = (size_t)دري->x + نقطو->x;
    evt.xclient.معلومات.l[1] = (size_t)دري->y + نقطو->y;
    evt.xclient.معلومات.l[2] = direction;
    evt.xclient.معلومات.l[3] = Button1;
    evt.xclient.معلومات.l[4] = 0;
    X11_XSendEvent(display, Default_پاڙ_دري(display), False, Substructure_Redirect_نقاب | Substructure_Notify_نقاب, &evt);

    X11_XSync(display, 0);
}

bool X11_Process_ڪاميابي_Test(SDL_VideoDevice *_this, SDL_دري_معلومات *معلومات, ثابت عائم x, ثابت عائم y, bool force_new_نتيجو)
{
    SDL_دري *دري = معلومات->دري;
    إذا (!دري->ڪاميابي_test) أرجع false;
    ثابت SDL_نقطو نقطو = { (صحيح)x, (صحيح)y };
    SDL_ڪاميابي_Test_نتيجو rc = دري->ڪاميابي_test(دري, &نقطو, دري->ڪاميابي_test_معلومات);
    إذا (!force_new_نتيجو && rc == معلومات->ڪاميابي_test_نتيجو) {
        أرجع true;
    }
    X11_سيٽ_ڪاميابي_Test_Cursor(rc);
    معلومات->ڪاميابي_test_نتيجو = rc;
    أرجع true;
}

bool X11_Trigger_ڪاميابي_Test_Action(SDL_VideoDevice *_this, SDL_دري_معلومات *معلومات, ثابت عائم x, ثابت عائم y)
{
    SDL_دري *دري = معلومات->دري;

    إذا (دري->ڪاميابي_test) {
        ثابت SDL_نقطو نقطو = { (صحيح)x, (صحيح)y };
        ساكن ثابت صحيح directions[] = {
            NET_WM_MOVERESIZE_سائيز_TOPLEFT, NET_WM_MOVERESIZE_سائيز_چوٽي,
            NET_WM_MOVERESIZE_سائيز_TOPRIGHT, NET_WM_MOVERESIZE_سائيز_ساڄو,
            NET_WM_MOVERESIZE_سائيز_BOTTOMRIGHT, NET_WM_MOVERESIZE_سائيز_BOTTOM,
            NET_WM_MOVERESIZE_سائيز_BOTTOMLEFT, NET_WM_MOVERESIZE_سائيز_کاٻو
        };

        بدل (معلومات->ڪاميابي_test_نتيجو) {
        حالة SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            إذا (معلومات->دري->flags & SDL_دري_داخلا_FOCUS) {
                Dispatch_دري_Move(_this, معلومات, &نقطو);
            } وإلا {
                وقت_جدول_دري_Move(_this, معلومات, &نقطو);
            }
            أرجع true;

        حالة SDL_HITTEST_RESIZE_TOPLEFT:
        حالة SDL_HITTEST_RESIZE_چوٽي:
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
        حالة SDL_HITTEST_RESIZE_ساڄو:
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        حالة SDL_HITTEST_RESIZE_BOTTOM:
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
        حالة SDL_HITTEST_RESIZE_کاٻو:
            Initiate_دري_Resize(_this, معلومات, &نقطو, directions[معلومات->ڪاميابي_test_نتيجو - SDL_HITTEST_RESIZE_TOPLEFT]);
            أرجع true;

        افتراضي:
            أرجع false;
        }
    }

    أرجع false;
}

ساكن فراغ X11_Update_User_وقت(SDL_دري_معلومات *معلومات, ثابت بنانشان ڊگهو latest)
{
    إذا (latest && (latest != معلومات->user_وقت)) {
        SDL_Video_معلومات *videodata = معلومات->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, معلومات->xwindow, videodata->atoms.NET_WM_USER_وقت,
                            XA_CARDINAL, 32, Prop_گهڻائي_Replace,
                            (ثابت بنانشان حرف *)&latest, 1);
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", معلومات->xwindow, latest);
#جيڪڏهن_پورو
        معلومات->user_وقت = latest;
    }
}

ساكن بنانشان حرف x11_آخري_error;
ساكن صحيح Bad_دري_Error_Handler(Display *d, XErrorEvent *e)
{
    x11_آخري_error = e->error_ڪوڊ;

    // Ignore BadWindow in cases where it's not fatal.
    إذا (e->error_ڪوڊ != Bad_دري) {
        حرف err_نياپو[128];
        X11_XGet_Error_متن(d, e->error_ڪوڊ, err_نياپو, حجم(err_نياپو));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_ڪوڊ, err_نياپو, e->request_ڪوڊ);
    }
    أرجع 0;
}

ساكن فراغ X11_HandleClipboardEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    صحيح i;
    SDL_Video_معلومات *videodata = _this->اندروني;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_دري != None);
    SDL_assert(xevent->xany.دري == videodata->clipboard_دري);

    بدل (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    حالة SelectionRequest:
    {
        ثابت XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        صحيح mime_formats;
        بنانشان حرف *seln_معلومات;
        size_t seln_ڊيگهائي = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_Clipboard_معلومات *clipboard;

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        حرف *atom_name;
        atom_name = X11_XGetAtomName(display, req->هدف);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->هدف, atom_name);
        إذا (atom_name) {
            X11_XFree(atom_name);
        }
#جيڪڏهن_پورو

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_آخري_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_دري_Error_Handler);

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
        sevent.xselection.وقت = req->وقت;

        /* !!! FIXME: We were probably storing this on the root window
           because an SDL window might go away...? but we don't have to do
           this now (or ever, really). */

        إذا (req->هدف == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_ڳڻپ + 1) * حجم(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            لكل (i = 0; i < clipboard->mime_ڳڻپ; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, Prop_گهڻائي_Replace,
                                (بنانشان حرف *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.هدف = XA_TARGETS;
            SDL_free(supportedFormats);
        } وإلا {
            إذا (clipboard->callback) {
                لكل (i = 0; i < clipboard->mime_ڳڻپ; ++i) {
                    ثابت حرف *mime_type = clipboard->mime_types[i];
                    إذا (X11_XInternAtom(display, mime_type, False) != req->هدف) {
                        استمر;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_معلومات = (بنانشان حرف *)clipboard->callback(clipboard->userdata, mime_type, &seln_ڊيگهائي);
                    إذا (seln_معلومات) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->هدف, 8, Prop_گهڻائي_Replace,
                                            seln_معلومات, seln_ڊيگهائي);
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
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        ثابت حرف *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        ثابت حرف *هدف_Name = xsel->هدف ? X11_XGetAtomName(display, xsel->هدف) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, هدف_Name, propName);
#جيڪڏهن_پورو
        إذا (xsel->هدف == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            بنانشان حرف *معلومات = عدم;
            صحيح format_property = 0;
            بنانشان ڊگهو ڊيگهائي = 0;
            بنانشان ڊگهو بائيٽون_کاٻو = 0;
            صحيح j;

            X11_XGet_دري_Property(display, Get_دري(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &ڊيگهائي, &بائيٽون_کاٻو, &معلومات);

            صحيح allocationsize = (ڊيگهائي + 1) * حجم(حرف *);
            لكل (j = 0, patom = (Atom *)معلومات; j < ڊيگهائي; j++, patom++) {
                حرف *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            حرف **new_mime_types = SDL_Allocate_Temporary_يادگيري(allocationsize);
            إذا (new_mime_types) {
                حرف *strPtr = (حرف *)(new_mime_types + ڊيگهائي + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                لكل (j = 0, patom = (Atom *)معلومات; j < ڊيگهائي; j++, patom++) {
                    حرف *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    ثابت size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[ڊيگهائي] = عدم;

                SDL_SendClipboardUpdate(false, new_mime_types, ڊيگهائي);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            إذا (معلومات) {
                X11_XFree(معلومات);
            }
        }

        videodata->selection_انتظار = false;
    } اكسر;

    حالة SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_Clipboard_معلومات *clipboard = عدم;

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.هدف);
#جيڪڏهن_پورو

        إذا (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } وإلا إذا (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        إذا (clipboard && clipboard->callback) {
            إذا (clipboard->sequence) {
                SDL_Cancel_Clipboard_معلومات(clipboard->sequence);
            } وإلا {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } اكسر;

    حالة PropertyNotify:
    {
        حرف *name_جو_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        إذا (SDL_strncmp(name_جو_atom, "SDL_SELECTION", حجم("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_قدر) {
            videodata->selection_incr_انتظار = false;
        }

        إذا (name_جو_atom) {
            X11_XFree(name_جو_atom);
        }
    } اكسر;
    }
}

ساكن Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    أرجع ev->type == MapNotify &&
           ev->xmap.دري == unmap->دري &&
           ev->xmap.serial == unmap->serial;
}

ساكن Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    أرجع ev->type == ReparentNotify &&
           ev->xreparent.دري == unmap->دري &&
           ev->xreparent.serial == unmap->serial;
}

ساكن bool Is_مٿاهون_Latin1(ثابت حرف *string, صحيح ڊيگهائي)
{
    طالما (ڊيگهائي-- > 0) {
        Uint8 ch = (Uint8)*string;
        إذا (ch >= 0x80) {
            أرجع true;
        }
        ++string;
    }
    أرجع false;
}

ساكن صحيح XLookupStringAsUTF8(XKeyEvent *event_struct, حرف *بفر_return, صحيح بائيٽون_بفر, ڪنجي_Sym *keysym_return, XCompose_حالت *حالت_اندريون_ٻاهريون)
{
    صحيح نتيجو = X11_XLookupString(event_struct, بفر_return, بائيٽون_بفر, keysym_return, حالت_اندريون_ٻاهريون);
    إذا (Is_مٿاهون_Latin1(بفر_return, نتيجو)) {
        حرف *utf8_متن = SDL_iconv_string("UTF-8", "ISO-8859-1", بفر_return, نتيجو + 1);
        إذا (utf8_متن) {
            SDL_strlcpy(بفر_return, utf8_متن, بائيٽون_بفر);
            SDL_free(utf8_متن);
            أرجع SDL_strlen(بفر_return);
        } وإلا {
            أرجع 0;
        }
    }
    أرجع نتيجو;
}

SDL_دري_معلومات *X11_ڳوليو_دري(SDL_Video_معلومات *videodata, دري_2 دري)
{
    إذا (videodata && videodata->windowlist) {
        لكل (صحيح i = 0; i < videodata->numwindows; ++i) {
            إذا ((videodata->windowlist[i] != عدم) &&
                (videodata->windowlist[i]->xwindow == دري)) {
                أرجع videodata->windowlist[i];
            }
        }
    }
    أرجع عدم;
}

Uint64 X11_GetEventTimestamp(بنانشان ڊگهو وقت)
{
    // FIXME: Get the event time in the SDL tick time base
    أرجع SDL_GetTicksNS();
}

فراغ X11_Handle_ڪنجي_Event(SDL_VideoDevice *_this, SDL_دري_معلومات *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    Display *display = videodata->display;
    ڪنجي_ڪوڊ_2 keycode = xevent->xkey.keycode;
    ڪنجي_Sym keysym = No_نشان;
    صحيح متن_ڊيگهائي = 0;
    حرف متن[64];
    حالت_2 حالت = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == ڪنجي_Press);
    SDL_Scancode scancode = videodata->keyboard.ڪنجي_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.وقت);

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.دري, (xevent->type == ڪنجي_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل DEBUG_SCANCODES
    إذا (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        صحيح min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_ڪنجي_ڪوڊ_منزل_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysym_منزل_String(keysym));
    }
#جيڪڏهن_پورو // DEBUG SCANCODES

    متن[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    إذا (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (سرڪايو_نقاب_2 | Control_نقاب | Mod1_نقاب | Mod3_نقاب | Mod4_نقاب | Mod5_نقاب);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (تالو_نقاب | videodata->keyboard.numlock_نقاب | videodata->keyboard.scrolllock_نقاب);
    }

    إذا (SDL_متن_داخلا_سرگرم(windowdata->دري)) {
        // filter events catches XIM events and sends them to the correct handler
        إذا (X11_XFilterEvent(xevent, None)) {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.دري);
#جيڪڏهن_پورو
            handled_by_ime = true;
        }

        إذا (!handled_by_ime) {
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
            إذا (windowdata->ic && xevent->type == ڪنجي_Press) {
                متن_ڊيگهائي = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, متن, حجم(متن) - 1,
                                      &keysym, &حالت);
            } وإلا {
                متن_ڊيگهائي = XLookupStringAsUTF8(&xevent->xkey, متن, حجم(متن) - 1, &keysym, عدم);
            }
#وإلا
            متن_ڊيگهائي = XLookupStringAsUTF8(&xevent->xkey, متن, حجم(متن) - 1, &keysym, عدم);
#جيڪڏهن_پورو
        }
    }

    إذا (!handled_by_ime) {
        إذا (pressed) {
            X11_Handle_Modifier_ڪنجيون(videodata, scancode, true);
            SDL_Send_Keyboard_ڪنجي_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            إذا (*متن && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                متن[متن_ڊيگهائي] = '\0';
                X11_ClearComposition(windowdata);
                SDL_Send_Keyboard_متن(متن);
            }
        } وإلا {
            إذا (X11_ڪنجي_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                أرجع;
            }

            X11_Handle_Modifier_ڪنجيون(videodata, scancode, false);
            SDL_Send_Keyboard_ڪنجي_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    إذا (pressed) {
        X11_Update_User_وقت(windowdata, xevent->xkey.وقت);
    }
}

فراغ X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_دري_معلومات *windowdata, SDL_MouseID mouseID, صحيح button, عائم x, عائم y, بنانشان ڊگهو وقت, بنانشان ڊگهو serial)
{
    SDL_دري *دري = windowdata->دري;
    صحيح xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(وقت);

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#جيڪڏهن_پورو

    SDL_Mouse *mouse = SDL_GetMouse();
    إذا (!mouse->relative_گهڻائي && (x != mouse->x || y != mouse->y)) {
        X11_Process_ڪاميابي_Test(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, دري, mouseID, false, x, y);
    }

    إذا (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, دري, mouseID, (عائم)-xticks, (عائم)yticks, SDL_MOUSEWHEEL_عام);
    } وإلا {
        إذا (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        إذا (button == Button1) {
            إذا (X11_Trigger_ڪاميابي_Test_Action(_this, windowdata, x, y)) {
                SDL_Send_دري_Event(دري, SDL_EVENT_دري_ڪاميابي_TEST, 0, 0);
                أرجع; // don't pass this event on to app.
            }
        }
        إذا (windowdata->آخري_focus_event_وقت) {
            ثابت صحيح X11_FOCUS_CLICK_TIMEOUT = 10;
            إذا (SDL_GetTicks() < (windowdata->آخري_focus_event_وقت + X11_FOCUS_CLICK_TIMEOUT)) {
                إذا (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->آخري_focus_event_وقت = 0;
        }
        إذا (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, دري, mouseID, button, true);
        }
    }
    X11_Update_User_وقت(windowdata, وقت);
}

فراغ X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_دري_معلومات *windowdata, SDL_MouseID mouseID, صحيح button, بنانشان ڊگهو وقت)
{
    SDL_دري *دري = windowdata->دري;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    صحيح xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(وقت);

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#جيڪڏهن_پورو
    إذا (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        إذا (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, دري, mouseID, button, false);

        إذا (دري->اندروني->pending_grab) {
            X11_سيٽ_دري_Mouse_Grab(_this, دري, true);
        }
    }
}

فراغ X11_Get_Border_قدرون(SDL_دري_معلومات *معلومات)
{
    SDL_Video_معلومات *videodata = معلومات->videodata;
    Display *display = videodata->display;

    Atom type;
    صحيح format;
    بنانشان ڊگهو nitems, بائيٽون_after;
    بنانشان حرف *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    إذا (!(معلومات->دري->flags & SDL_دري_BORDERLESS)) {
        إذا (X11_XGet_دري_Property(display, معلومات->xwindow, videodata->atoms.NET_چوکٺو_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &بائيٽون_after, &property) == Success) {
            إذا (type != None && nitems == 4) {
                معلومات->border_کاٻو = (صحيح)((ڊگهو *)property)[0];
                معلومات->border_ساڄو = (صحيح)((ڊگهو *)property)[1];
                معلومات->border_چوٽي = (صحيح)((ڊگهو *)property)[2];
                معلومات->border_bottom = (صحيح)((ڊگهو *)property)[3];
            }
            X11_XFree(property);

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", معلومات->border_کاٻو, معلومات->border_ساڄو, معلومات->border_چوٽي, معلومات->border_bottom);
#جيڪڏهن_پورو
        }
    } وإلا {
        معلومات->border_کاٻو = معلومات->border_چوٽي = معلومات->border_ساڄو = معلومات->border_bottom = 0;
    }
}

فراغ X11_EmitConfigureNotifyEvents(SDL_دري_معلومات *معلومات, XConfigureEvent *xevent)
{
    إذا (!معلومات->سائيز_move_event_flags) {
        صحيح x = xevent->x;
        صحيح y = xevent->y;

        إذا (xevent->x != معلومات->آخري_xconfigure.x ||
            xevent->y != معلومات->آخري_xconfigure.y) {
            معلومات->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_Global_منزل_Relative_For_دري(معلومات->دري, x, y, &x, &y);
        SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_MOVED, x, y);

        لكل (SDL_دري *w = معلومات->دري->پهريون_ٻار; w; w = w->ايندڙ_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            إذا (SDL_دري_IS_POPUP(w) && !(w->flags & SDL_دري_HIDDEN)) {
                X11_Update_دري_Position(w, true);
            }
        }

        إذا (xevent->ويڪر != معلومات->آخري_xconfigure.ويڪر ||
            xevent->اوچائي != معلومات->آخري_xconfigure.اوچائي) {
            معلومات->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_RESIZED, xevent->ويڪر, xevent->اوچائي);
    }

    SDL_copyp(&معلومات->آخري_xconfigure, xevent);
}

ساكن فراغ X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    Display *display;
    SDL_دري_معلومات *معلومات;
    XClient_پيغام_Event m;
    صحيح i;

    SDL_assert(videodata != عدم);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    إذا (xevent->type != ڪنجي_Press && xevent->type != ڪنجي_Release) {
        إذا (X11_XFilterEvent(xevent, None)) {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.دري);
#جيڪڏهن_پورو
            أرجع;
        }
    }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    إذا (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        أرجع;
    }
#جيڪڏهن_پورو

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    إذا (g_X11EventHook) {
        إذا (!g_X11EventHook(g_X11_Event_Hook_معلومات, xevent)) {
            أرجع;
        }
    }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XRANDR
    إذا (videodata->xrandr_event_بنياد && (xevent->type == (videodata->xrandr_event_بنياد + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.دري);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES
    إذا (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#جيڪڏهن_پورو

        إذا (ev->subtype == XFixes_سيٽ_Selection_Owner_Notify)
        {
            إذا (ev->selection != videodata->atoms.CLIPBOARD)
                أرجع;

            إذا (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_دري)
                أرجع;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, Get_دري(_this), Current_وقت);
        }

        أرجع;
    }
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11_XFIXES

    إذا ((videodata->clipboard_دري != None) &&
        (videodata->clipboard_دري == xevent->xany.دري)) {
        X11_HandleClipboardEvent(_this, xevent);
        أرجع;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    معلومات = X11_ڳوليو_دري(videodata, xevent->xany.دري);

    إذا (!معلومات) {
        // The window for KeymapNotify, etc events is 0
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        إذا (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            بدل (xkbevent->any.xkb_type) {
            حالة XkbStateNotify:
            {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.دري);
#جيڪڏهن_پورو
                إذا ((xkbevent->state.بدليو & Xkb_گروهه_State_نقاب) && xkbevent->state.گروهه != videodata->keyboard.xkb.current_گروهه) {
                    videodata->keyboard.xkb.current_گروهه = xkbevent->state.گروهه;
                    SDL_سيٽ_Keymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_گروهه], true);
                }

                إذا (xkbevent->state.بدليو & Xkb_Modifier_State_نقاب) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.بنياد_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } اكسر;

            حالة XkbMapNotify:
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.دري);
                SDL_FALLTHROUGH;
#جيڪڏهن_پورو
            حالة XkbNewKeyboardNotify:
            {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
                إذا (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.دري);
                }
#جيڪڏهن_پورو
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                إذا (xkbevent->any.serial != videodata->keyboard.xkb.آخري_map_serial) {
                    videodata->keyboard.xkb.آخري_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } اكسر;

            افتراضي:
                اكسر;
            }
        } وإلا
#جيڪڏهن_پورو
        إذا (xevent->type == KeymapNotify) {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.دري);
#جيڪڏهن_پورو
            إذا (SDL_GetKeyboardFocus() != عدم) {
                إذا (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } وإلا إذا (xevent->type == MappingNotify) {
            ثابت صحيح request = xevent->xmapping.request;

            إذا (request == Mapping_اشارو) {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.دري);
#جيڪڏهن_پورو
                X11_Xinput2_Update_اشارو_Mapping(_this);
            } وإلا إذا (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.دري);
#جيڪڏهن_پورو
                إذا (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } وإلا إذا (xevent->type == PropertyNotify && videodata) {
            حرف *name_جو_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            إذا (name_جو_atom) {
                إذا (SDL_startswith(name_جو_atom, "_ICC_PROFILE")) {
                    XWindow_خاصيتون attrib;
                    صحيح screennum;
                    لكل (i = 0; i < videodata->numwindows; ++i) {
                        إذا (videodata->windowlist[i] != عدم) {
                            معلومات = videodata->windowlist[i];
                            X11_XGet_دري_خاصيتون(display, معلومات->xwindow, &attrib);
                            screennum = X11_XScreen_عدد_جو_Screen(attrib.screen);
                            إذا (screennum == 0 && SDL_strcmp(name_جو_atom, "_ICC_PROFILE") == 0) {
                                SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_ICCPROF_بدليو, 0, 0);
                            } وإلا إذا (SDL_strncmp(name_جو_atom, "_ICC_PROFILE_", حجم("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_جو_atom) > حجم("_ICC_PROFILE_") - 1) {
                                صحيح iccscreennum = SDL_atoi(&name_جو_atom[حجم("_ICC_PROFILE_") - 1]);

                                إذا (screennum == iccscreennum) {
                                    SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_ICCPROF_بدليو, 0, 0);
                                }
                            }
                        }
                    }
                } وإلا إذا (SDL_strcmp(name_جو_atom, "_NET_WORKAREA") == 0) {
                    لكل (i = 0; i < _this->انگ_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_بدليو, 0, 0);
                    }
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XRANDR
                } وإلا إذا (SDL_strcmp(name_جو_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_جو_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#جيڪڏهن_پورو
                }
                X11_XFree(name_جو_atom);
            }
        }
        أرجع;
    }

    بدل (xevent->type) {

        // Gaining mouse coverage?
    حالة EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.دري,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.گهڻائي);
        إذا (xevent->xcrossing.گهڻائي == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        إذا (xevent->xcrossing.گهڻائي == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#جيڪڏهن_پورو
        SDL_سيٽ_Mouse_Focus(معلومات->دري);

        mouse->آخري_x = xevent->xcrossing.x;
        mouse->آخري_y = xevent->xcrossing.y;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES
        {
            // Only create the barriers if we have input focus
            SDL_دري_معلومات *windowdata = معلومات->دري->اندروني;
            إذا ((معلومات->اشارو_barrier_سرگرم == true) && windowdata->دري->flags & SDL_دري_داخلا_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->دري, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#جيڪڏهن_پورو

        إذا (!mouse->relative_گهڻائي) {
            SDL_SendMouseMotion(0, معلومات->دري, SDL_GLOBAL_MOUSE_ID, false, (عائم)xevent->xcrossing.x, (عائم)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        إذا (!(معلومات->دري->flags & SDL_دري_MOUSE_CAPTURE)) {
            SDL_Update_دري_Grab(معلومات->دري);
        }

        X11_Process_ڪاميابي_Test(_this, معلومات, mouse->آخري_x, mouse->آخري_y, true);
    } اكسر;
        // Losing mouse coverage?
    حالة LeaveNotify:
    {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.دري,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.گهڻائي);
        إذا (xevent->xcrossing.گهڻائي == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        إذا (xevent->xcrossing.گهڻائي == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#جيڪڏهن_پورو
        إذا (!SDL_GetMouse()->relative_گهڻائي) {
            SDL_SendMouseMotion(0, معلومات->دري, SDL_GLOBAL_MOUSE_ID, false, (عائم)xevent->xcrossing.x, (عائم)xevent->xcrossing.y);
        }

        إذا (xevent->xcrossing.گهڻائي != NotifyGrab &&
            xevent->xcrossing.گهڻائي != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            إذا (!(معلومات->دري->flags & SDL_دري_FULLSCREEN)) {
                X11_سيٽ_دري_Keyboard_Grab(_this, معلومات->دري, false);
            }

            SDL_سيٽ_Mouse_Focus(عدم);
        }
    } اكسر;

        // Gaining input focus?
    حالة Focus_اندريون:
    {
        إذا (xevent->xfocus.گهڻائي == NotifyGrab || xevent->xfocus.گهڻائي == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.دري);
#جيڪڏهن_پورو
            اكسر;
        }

        إذا (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_اشارو) {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.دري);
#جيڪڏهن_پورو
            اكسر;
        }
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.دري);
#جيڪڏهن_پورو
        إذا (!videodata->آخري_گهڻائي_change_deadline) /* no recent mode changes */ {
            معلومات->pending_focus = PENDING_FOCUS_NONE;
            معلومات->pending_focus_وقت = 0;
            X11_Dispatch_Focus_اندريون(_this, معلومات);
        } وإلا {
            معلومات->pending_focus = PENDING_FOCUS_اندريون;
            معلومات->pending_focus_وقت = SDL_GetTicks() + PENDING_FOCUS_وقت;
        }
        معلومات->آخري_focus_event_وقت = SDL_GetTicks();
    } اكسر;

        // Losing input focus?
    حالة Focus_ٻاهريون:
    {
        إذا (xevent->xfocus.گهڻائي == NotifyGrab || xevent->xfocus.گهڻائي == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.دري);
#جيڪڏهن_پورو
            اكسر;
        }
        إذا (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_اشارو) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.دري);
#جيڪڏهن_پورو
            اكسر;
        }
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.دري);
#جيڪڏهن_پورو
        إذا (!videodata->آخري_گهڻائي_change_deadline) /* no recent mode changes */ {
            معلومات->pending_focus = PENDING_FOCUS_NONE;
            معلومات->pending_focus_وقت = 0;
            X11_Dispatch_Focus_ٻاهريون(_this, معلومات);
        } وإلا {
            معلومات->pending_focus = PENDING_FOCUS_ٻاهريون;
            معلومات->pending_focus_وقت = SDL_GetTicks() + PENDING_FOCUS_وقت;
        }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        إذا (معلومات->اشارو_barrier_سرگرم == true) {
            X11_ConfineCursorWithFlags(_this, معلومات->دري, عدم, X11_BARRIER_HANDLED_BY_EVENT);
        }
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11_XFIXES
    } اكسر;


        // Have we been iconified?
    حالة UnmapNotify:
    {
        XEvent ev;

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.دري);
#جيڪڏهن_پورو

        إذا (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } وإلا {
            X11_DispatchUnmapNotify(معلومات);
        }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        إذا (معلومات->اشارو_barrier_سرگرم == true) {
            X11_ConfineCursorWithFlags(_this, معلومات->دري, عدم, X11_BARRIER_HANDLED_BY_EVENT);
        }
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11_XFIXES
    } اكسر;

        // Have we been restored?
    حالة MapNotify:
    {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.دري);
#جيڪڏهن_پورو
        X11_DispatchMapNotify(معلومات);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        إذا (معلومات->اشارو_barrier_سرگرم == true) {
            X11_ConfineCursorWithFlags(_this, معلومات->دري, &معلومات->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11_XFIXES
    } اكسر;

        // Have we been resized or moved?
    حالة ConfigureNotify:
    {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.دري,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.ويڪر, xevent->xconfigure.اوچائي);
#جيڪڏهن_پورو
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        إذا (!xevent->xconfigure.send_event) {
            بنانشان صحيح انگ_Children;
            دري_2 ٻار_Return, پاڙ_2, والد_2;
            دري_2 *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_آخري_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_دري_Error_Handler);

            X11_XQuery_وڻ(معلومات->videodata->display, xevent->xconfigure.دري, &پاڙ_2, &والد_2, &Children, &انگ_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      والد_2, Default_پاڙ_دري(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &ٻار_Return);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            إذا (x11_آخري_error == Bad_دري) {
                اكسر;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        ثابت SDL_دري_Flags بدليو = X11_GetNetWMState(_this, معلومات->دري, xevent->xproperty.دري) ^ معلومات->دري->flags;
        إذا (بدليو & (SDL_دري_FULLSCREEN | SDL_دري_MAXIMIZED)) {
            SDL_copyp(&معلومات->pending_xconfigure, &xevent->xconfigure);
            معلومات->emit_سائيز_move_after_property_notify = true;
        }

        إذا (!معلومات->emit_سائيز_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(معلومات, &xevent->xconfigure);
        }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(معلومات->دري, &xevent->xconfigure);
#جيڪڏهن_پورو /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } اكسر;

        // Have we been requested to quit (or another client message?)
    حالة Client_پيغام:
    {
        ساكن صحيح xdnd_نسخو = 0;

        إذا (xevent->xclient.پيغام_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.معلومات.l[1] & 1;
            معلومات->xdnd_ذريعو = xevent->xclient.معلومات.l[0];
            xdnd_نسخو = (xevent->xclient.معلومات.l[1] >> 24);
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", معلومات->xdnd_ذريعو);
            SDL_Log("Protocol version to use : %d", xdnd_نسخو);
            SDL_Log("More then 3 data types : %d", (صحيح)use_list);
#جيڪڏهن_پورو

            إذا (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, معلومات->xdnd_ذريعو, videodata->atoms.XdndTypeList);
                // pick one
                معلومات->xdnd_req = X11_Pick_هدف(display, (Atom *)p.معلومات, p.ڳڻپ);
                X11_XFree(p.معلومات);
            } وإلا {
                // pick from list of three
                معلومات->xdnd_req = X11_Pick_هدف_From_Atoms(display, xevent->xclient.معلومات.l[2], xevent->xclient.معلومات.l[3], xevent->xclient.معلومات.l[4]);
            }
        } وإلا إذا (xevent->xclient.پيغام_type == videodata->atoms.XdndLeave) {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.معلومات.l[0]);
#جيڪڏهن_پورو
            SDL_SendDropComplete(معلومات->دري);
        } وإلا إذا (xevent->xclient.پيغام_type == videodata->atoms.XdndPosition) {

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            إذا (xdnd_نسخو >= 2) {
                act = xevent->xclient.معلومات.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#جيڪڏهن_پورو
            {
                // Drag and Drop position
                صحيح پاڙ_x, پاڙ_y, دري_x, دري_y;
                دري_2 ٻار_Return;
                پاڙ_x = xevent->xclient.معلومات.l[2] >> 16;
                پاڙ_y = xevent->xclient.معلومات.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_پاڙ_دري(display), معلومات->xwindow,
                                          پاڙ_x, پاڙ_y, &دري_x, &دري_y, &ٻار_Return);

                SDL_SendDropPosition(معلومات->دري, (عائم)دري_x, (عائم)دري_y);
            }

            // reply with status
            SDL_zero(m);
            m.type = Client_پيغام;
            m.display = xevent->xclient.display;
            m.دري = xevent->xclient.معلومات.l[0];
            m.پيغام_type = videodata->atoms.Xdnd_حالت;
            m.format = 32;
            m.معلومات.l[0] = معلومات->xwindow;
            m.معلومات.l[1] = (معلومات->xdnd_req != None);
            m.معلومات.l[2] = 0; // specify an empty rectangle
            m.معلومات.l[3] = 0;
            m.معلومات.l[4] = videodata->atoms.XdndActionCopy; // we only accept copying anyway

            X11_XSendEvent(display, xevent->xclient.معلومات.l[0], False, No_Event_نقاب, (XEvent *)&m);
            X11_XFlush(display);
        } وإلا إذا (xevent->xclient.پيغام_type == videodata->atoms.XdndDrop) {
            إذا (معلومات->xdnd_req == None) {
                // say again - not interested!
                SDL_zero(m);
                m.type = Client_پيغام;
                m.display = xevent->xclient.display;
                m.دري = xevent->xclient.معلومات.l[0];
                m.پيغام_type = videodata->atoms.Xdnd_ختم;
                m.format = 32;
                m.معلومات.l[0] = معلومات->xwindow;
                m.معلومات.l[1] = 0;
                m.معلومات.l[2] = None; // fail!
                X11_XSendEvent(display, xevent->xclient.معلومات.l[0], False, No_Event_نقاب, (XEvent *)&m);
            } وإلا {
                // convert
                إذا (xdnd_نسخو >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, معلومات->xdnd_req, videodata->atoms.PRIMARY, معلومات->xwindow, xevent->xclient.معلومات.l[2]);
                } وإلا {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, معلومات->xdnd_req, videodata->atoms.PRIMARY, معلومات->xwindow, Current_وقت);
                }
            }
        } وإلا إذا ((xevent->xclient.پيغام_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.معلومات.l[0] == videodata->atoms._NET_WM_PING)) {
            دري_2 پاڙ = Default_پاڙ_دري(display);

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.دري);
#جيڪڏهن_پورو
            xevent->xclient.دري = پاڙ;
            X11_XSendEvent(display, پاڙ, False, Substructure_Redirect_نقاب | Substructure_Notify_نقاب, xevent);
            اكسر;
        }

        وإلا إذا ((xevent->xclient.پيغام_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.معلومات.l[0] == videodata->atoms.WM_DELETE_دري)) {

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.دري);
#جيڪڏهن_پورو
            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_CLOSE_REQUESTED, 0, 0);
            اكسر;
        } وإلا إذا ((xevent->xclient.پيغام_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.معلومات.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", معلومات);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(معلومات->دري, &xevent->xclient);
#جيڪڏهن_پورو /* SDL_VIDEO_DRIVER_X11_XSYNC */
            اكسر;
        }
    } اكسر;

        // Do we need to refresh ourselves?
    حالة Expose:
    {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.دري, xevent->xexpose.ڳڻپ);
#جيڪڏهن_پورو
        SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_EXPOSED, 0, 0);
    } اكسر;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    حالة ڪنجي_Press:
    حالة ڪنجي_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        إذا (معلومات->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            اكسر;
        } وإلا إذا (xevent->xkey.serial == videodata->xinput_آخري_ڪنجي_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_آخري_keyboard_device;
        }

        X11_Handle_ڪنجي_Event(_this, معلومات, keyboardID, xevent);
    } اكسر;

    حالة MotionNotify:
    {
        إذا (X11_Xinput2_Handles_Motion_For_دري(معلومات)) {
            // This input is being handled by XInput2
            اكسر;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        إذا (!mouse->relative_گهڻائي) {
#جيڪڏهن_وصف_ٿيل DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.دري, xevent->xmotion.x, xevent->xmotion.y);
#جيڪڏهن_پورو

            X11_Process_ڪاميابي_Test(_this, معلومات, (عائم)xevent->xmotion.x, (عائم)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, معلومات->دري, SDL_GLOBAL_MOUSE_ID, false, (عائم)xevent->xmotion.x, (عائم)xevent->xmotion.y);
        }
    } اكسر;

    حالة ButtonPress:
    {
        إذا (معلومات->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_آخري_button_serial) {
            // This input event was handled by XInput2.
            اكسر;
        }

        X11_HandleButtonPress(_this, معلومات, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.وقت, xevent->xbutton.serial);
    } اكسر;

    حالة ButtonRelease:
    {
        إذا (معلومات->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_آخري_button_serial) {
            // This input event was handled by XInput2.
            اكسر;
        }

        X11_HandleButtonRelease(_this, معلومات, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.وقت);
    } اكسر;

    حالة PropertyNotify:
    {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        بنانشان حرف *propdata;
        صحيح حالت, real_format;
        Atom real_type;
        بنانشان ڊگهو شيون_read, شيون_کاٻو;

        حرف *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        إذا (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.دري, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.وقت);
            X11_XFree(name);
        }

        حالت = X11_XGet_دري_Property(display, معلومات->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &شيون_read, &شيون_کاٻو, &propdata);
        إذا (حالت == Success && شيون_read > 0) {
            إذا (real_type == XA_INTEGER) {
                صحيح *قدرون = (صحيح *)propdata;

                SDL_Log("{");
                لكل (i = 0; i < شيون_read; i++) {
                    SDL_Log(" %d", قدرون[i]);
                }
                SDL_Log(" }");
            } وإلا إذا (real_type == XA_CARDINAL) {
                إذا (real_format == 32) {
                    Uint32 *قدرون = (Uint32 *)propdata;

                    SDL_Log("{");
                    لكل (i = 0; i < شيون_read; i++) {
                        SDL_Log(" %d", قدرون[i]);
                    }
                    SDL_Log(" }");
                } وإلا إذا (real_format == 16) {
                    Uint16 *قدرون = (Uint16 *)propdata;

                    SDL_Log("{");
                    لكل (i = 0; i < شيون_read; i++) {
                        SDL_Log(" %d", قدرون[i]);
                    }
                    SDL_Log(" }");
                } وإلا إذا (real_format == 8) {
                    Uint8 *قدرون = (Uint8 *)propdata;

                    SDL_Log("{");
                    لكل (i = 0; i < شيون_read; i++) {
                        SDL_Log(" %d", قدرون[i]);
                    }
                    SDL_Log(" }");
                }
            } وإلا إذا (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } وإلا إذا (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                لكل (i = 0; i < شيون_read; i++) {
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
#جيڪڏهن_پورو // DEBUG_XEVENTS

        /* Take advantage of this moment to make sure user_time has a
            valid timestamp from the X server, so if we later try to
            raise/restore this window, _NET_ACTIVE_WINDOW can have a
            non-zero timestamp, even if there's never been a mouse or
            key press to this window so far. Note that we don't try to
            set _NET_WM_USER_TIME here, though. That's only for legit
            user interaction with the window. */
        إذا (!معلومات->user_وقت) {
            معلومات->user_وقت = xevent->xproperty.وقت;
        }

        إذا (xevent->xproperty.atom == معلومات->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            ثابت SDL_دري_Flags flags = X11_GetNetWMState(_this, معلومات->دري, xevent->xproperty.دري);
            ثابت SDL_دري_Flags بدليو = flags ^ معلومات->دري->flags;

            إذا ((بدليو & SDL_دري_HIDDEN) && !(flags & SDL_دري_HIDDEN)) {
                X11_DispatchMapNotify(معلومات);
            }

            إذا (!SDL_دري_IS_POPUP(معلومات->دري)) {
                إذا (بدليو & SDL_دري_FULLSCREEN) {
                    معلومات->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    إذا (flags & SDL_دري_FULLSCREEN) {
                        إذا (!(flags & SDL_دري_MINIMIZED)) {
                            ثابت bool commit = SDL_memcmp(&معلومات->دري->current_fullscreen_گهڻائي, &معلومات->requested_fullscreen_گهڻائي, حجم(SDL_Display_گهڻائي)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_RESTORED, 0, 0);
                            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_ENTER_FULLSCREEN, 0, 0);
                            إذا (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&معلومات->دري->current_fullscreen_گهڻائي, &معلومات->دري->requested_fullscreen_گهڻائي);
                                SDL_Update_Fullscreen_گهڻائي(معلومات->دري, SDL_FULLSCREEN_OP_UPDATE, true);
                            } وإلا {
                                SDL_Update_Fullscreen_گهڻائي(معلومات->دري, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } وإلا {
                        SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_LEAVE_FULLSCREEN, 0, 0);
                        SDL_Update_Fullscreen_گهڻائي(معلومات->دري, false, false);

                        SDL_zero(معلومات->requested_fullscreen_گهڻائي);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_سيٽ_دري_Min_Max(معلومات->دري, !!(flags & SDL_دري_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        إذا (معلومات->fullscreen_borders_forced_on) {
                            معلومات->toggle_borders = true;
                            معلومات->fullscreen_borders_forced_on = false;
                        }
                    }

                    إذا ((flags & SDL_دري_FULLSCREEN) &&
                        (معلومات->border_چوٽي || معلومات->border_کاٻو || معلومات->border_bottom || معلومات->border_ساڄو)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        معلومات->سائيز_move_event_flags |= X11_سائيز_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        معلومات->اڳيون_borders_nonzero = true;
                    } وإلا إذا (!(flags & SDL_دري_FULLSCREEN) &&
                               معلومات->اڳيون_borders_nonzero &&
                               (!معلومات->border_چوٽي && !معلومات->border_کاٻو && !معلومات->border_bottom && !معلومات->border_ساڄو)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        معلومات->سائيز_move_event_flags |= X11_سائيز_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        معلومات->اڳيون_borders_nonzero = false;
                    } وإلا {
                        معلومات->سائيز_move_event_flags = 0;
                        معلومات->اڳيون_borders_nonzero = false;

                        إذا (!(معلومات->دري->flags & SDL_دري_FULLSCREEN) && معلومات->toggle_borders) {
                            معلومات->toggle_borders = false;
                            X11_سيٽ_دري_Bordered(_this, معلومات->دري, !(معلومات->دري->flags & SDL_دري_BORDERLESS));
                        }
                    }
                }
                إذا ((بدليو & SDL_دري_MAXIMIZED) && ((flags & SDL_دري_MAXIMIZED) && !(flags & SDL_دري_MINIMIZED))) {
                    معلومات->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    إذا ((بدليو & SDL_دري_MINIMIZED)) {
                        معلومات->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_RESTORED, 0, 0);
                    }
                    SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_MAXIMIZED, 0, 0);
                }
                إذا ((بدليو & SDL_دري_MINIMIZED) && (flags & SDL_دري_MINIMIZED)) {
                    معلومات->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_MINIMIZED, 0, 0);
                }
                إذا (!(flags & (SDL_دري_MAXIMIZED | SDL_دري_MINIMIZED))) {
                    معلومات->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    إذا (!(flags & SDL_دري_FULLSCREEN)) {
                        إذا (معلومات->pending_position) {
                            معلومات->pending_position = false;
                            معلومات->pending_operation |= X11_PENDING_OP_MOVE;
                            معلومات->expected.x = معلومات->دري->pending.x - معلومات->border_کاٻو;
                            معلومات->expected.y = معلومات->دري->pending.y - معلومات->border_چوٽي;
                            X11_XMove_دري(display, معلومات->xwindow, معلومات->expected.x, معلومات->expected.y);
                        }
                        إذا (معلومات->pending_سائيز) {
                            معلومات->pending_سائيز = false;
                            معلومات->pending_operation |= X11_PENDING_OP_RESIZE;
                            معلومات->expected.w = معلومات->دري->pending.w;
                            معلومات->expected.h = معلومات->دري->pending.h;
                            X11_XResize_دري(display, معلومات->xwindow, معلومات->دري->pending.w, معلومات->دري->pending.h);
                        }
                    }
                }
                إذا (معلومات->emit_سائيز_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(معلومات, &معلومات->pending_xconfigure);
                    معلومات->emit_سائيز_move_after_property_notify = false;
                }
                إذا ((flags & SDL_دري_داخلا_FOCUS)) {
                    إذا (معلومات->pending_move) {
                        Dispatch_دري_Move(_this, معلومات, &معلومات->pending_move_نقطو);
                        معلومات->pending_move = false;
                    }
                }
            }
            إذا (بدليو & SDL_دري_OCCLUDED) {
                SDL_Send_دري_Event(معلومات->دري, (flags & SDL_دري_OCCLUDED) ? SDL_EVENT_دري_OCCLUDED : SDL_EVENT_دري_EXPOSED, 0, 0);
            }
        } وإلا إذا (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            صحيح format;
            بنانشان ڊگهو nitems, بائيٽون_after;
            بنانشان حرف *prop_معلومات = عدم;

            إذا (X11_XGet_دري_Property(display, معلومات->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &بائيٽون_after, &prop_معلومات) == Success) {
                إذا (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_معلومات;

                    إذا ((state == 0 || state == 3) && !معلومات->دري->is_hiding && !(معلومات->دري->flags & SDL_دري_HIDDEN)) {
                        // Withdrawn or Iconic
                        إذا (!(معلومات->دري->flags & SDL_دري_MINIMIZED)) {
                            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_MINIMIZED, 0, 0);
                            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_OCCLUDED, 0, 0);
                        }
                    } وإلا إذا (state == 1) { // NormalState
                        إذا (معلومات->دري->flags & SDL_دري_MINIMIZED) {
                            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_RESTORED, 0, 0);
                            SDL_Send_دري_Event(معلومات->دري, SDL_EVENT_دري_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_معلومات);
            }
        } وإلا إذا (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } وإلا إذا (xevent->xproperty.atom == videodata->atoms.NET_چوکٺو_EXTENTS) {
            X11_Get_Border_قدرون(معلومات);
            إذا (معلومات->سائيز_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                معلومات->سائيز_move_event_flags &= ~X11_سائيز_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            إذا (!(معلومات->دري->flags & SDL_دري_FULLSCREEN) && معلومات->toggle_borders) {
                معلومات->toggle_borders = false;
                X11_سيٽ_دري_Bordered(_this, معلومات->دري, !(معلومات->دري->flags & SDL_دري_BORDERLESS));
            }
        }
    } اكسر;

    حالة SelectionNotify:
    {
        Atom هدف = xevent->xselection.هدف;
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.دري,
               xevent->xselection.requestor, xevent->xselection.هدف);
#جيڪڏهن_پورو
        إذا (هدف == معلومات->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, معلومات->xwindow, videodata->atoms.PRIMARY);

            إذا (p.format == 8) {
                حرف *saveptr = عدم;
                حرف *name = X11_XGetAtomName(display, هدف);
                إذا (name) {
                    حرف *token = SDL_strtok_r((حرف *)p.معلومات, "\r\n", &saveptr);
                    طالما (token) {
                        إذا ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_Send_Drop_متن(معلومات->دري, token);
                        } وإلا إذا (SDL_strcmp("text/uri-list", name) == 0) {
                            إذا (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(معلومات->دري, عدم, token);
                            }
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    X11_XFree(name);
                }
                SDL_SendDropComplete(معلومات->دري);
            }
            X11_XFree(p.معلومات);

            // send reply
            SDL_zero(m);
            m.type = Client_پيغام;
            m.display = display;
            m.دري = معلومات->xdnd_ذريعو;
            m.پيغام_type = videodata->atoms.Xdnd_ختم;
            m.format = 32;
            m.معلومات.l[0] = معلومات->xwindow;
            m.معلومات.l[1] = 1;
            m.معلومات.l[2] = videodata->atoms.XdndActionCopy;
            X11_XSendEvent(display, معلومات->xdnd_ذريعو, False, No_Event_نقاب, (XEvent *)&m);

            X11_XSync(display, False);
        }
    } اكسر;

    افتراضي:
    {
#جيڪڏهن_وصف_ٿيل DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.دري, xevent->type);
#جيڪڏهن_پورو
    } اكسر;
    }
}

ساكن فراغ X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    صحيح i;

    إذا (videodata && videodata->windowlist) {
        لكل (i = 0; i < videodata->numwindows; ++i) {
            SDL_دري_معلومات *معلومات = videodata->windowlist[i];
            إذا (معلومات && معلومات->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                إذا (now >= معلومات->pending_focus_وقت) {
                    إذا (معلومات->pending_focus == PENDING_FOCUS_اندريون) {
                        X11_Dispatch_Focus_اندريون(_this, معلومات);
                    } وإلا {
                        X11_Dispatch_Focus_ٻاهريون(_this, معلومات);
                    }
                    معلومات->pending_focus = PENDING_FOCUS_NONE;
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

فراغ X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    Display *req_display = معلومات->request_display;
    دري_2 xwindow = دري->اندروني->xwindow;
    XClient_پيغام_Event event;

    SDL_zero(event);
    event.type = Client_پيغام;
    event.display = req_display;
    event.send_event = True;
    event.پيغام_type = معلومات->atoms._SDL_WAKEUP;
    event.format = 8;

    X11_XSendEvent(req_display, xwindow, False, No_Event_نقاب, (XEvent *)&event);
    /* XSendEvent returns a status and it could be BadValue or BadWindow. If an
      error happens it is an SDL's internal error and there is nothing we can do here. */
    X11_XFlush(req_display);
}

صحيح X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
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
    SDL_Video_معلومات *معلومات = _this->اندروني;
    XEvent xevent;
    صحيح i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    لكل (i = 0; i < _this->انگ_displays; ++i) {
        إذا (_this->displays[i]->اندروني->گهڻائي_switch_deadline_ns) {
            إذا (_this->displays[i]->fullscreen_دري) {
                _this->displays[i]->اندروني->گهڻائي_switch_deadline_ns = 0;
            } وإلا إذا (SDL_GetTicksNS() >= _this->displays[i]->اندروني->گهڻائي_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_سيٽ_Display_گهڻائي_For_Display(_this->displays[i], عدم);
                _this->displays[i]->اندروني->گهڻائي_switch_deadline_ns = 0;
            }
        }
    }

    إذا (معلومات->آخري_گهڻائي_change_deadline) {
        إذا (SDL_GetTicks() >= معلومات->آخري_گهڻائي_change_deadline) {
            معلومات->آخري_گهڻائي_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    إذا (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        إذا (!معلومات->screensaver_activity || now >= (معلومات->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(معلومات->display);

#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#جيڪڏهن_پورو

            معلومات->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    طالما (X11_PollEvent(معلومات->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    لكل (i = 0; i < معلومات->numwindows; ++i) {
        إذا (معلومات->windowlist[i] != عدم &&
            معلومات->windowlist[i]->flash_cancel_وقت &&
            SDL_GetTicks() >= معلومات->windowlist[i]->flash_cancel_وقت) {
            X11_Flash_دري(_this, معلومات->windowlist[i]->دري, SDL_FLASH_CANCEL);
        }
    }

    إذا (معلومات->xinput_hierarchy_بدليو) {
        X11_Xinput2UpdateDevices(_this);
        معلومات->xinput_hierarchy_بدليو = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_Video_معلومات *معلومات = _this->اندروني;
    صحيح dummy;
    صحيح major_نسخو, minor_نسخو;
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
    إذا (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        أرجع true;
    }

    إذا (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    إذا (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        إذا (!X11_XScreenSaverQueryExtension(معلومات->display, &dummy, &dummy) ||
            !X11_XScreen_Saver_Query_نسخو(معلومات->display,
                                          &major_نسخو, &minor_نسخو) ||
            major_نسخو < 1 || (major_نسخو == 1 && minor_نسخو < 1)) {
            أرجع SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(معلومات->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(معلومات->display);
        أرجع true;
    }
#جيڪڏهن_پورو
    أرجع SDL_Unsupported();
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11
