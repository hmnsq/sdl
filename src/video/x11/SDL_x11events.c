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

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11

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
#تعریف_کړه DEBUG_XEVENTS
#د_که_پای

#که_نه_تعریف_شوی NET_WM_MOVERESIZE_اندازه_TOPLEFT
#تعریف_کړه NET_WM_MOVERESIZE_اندازه_TOPLEFT 0
#د_که_پای

#که_نه_تعریف_شوی NET_WM_MOVERESIZE_اندازه_سر
#تعریف_کړه NET_WM_MOVERESIZE_اندازه_سر 1
#د_که_پای

#که_نه_تعریف_شوی NET_WM_MOVERESIZE_اندازه_TOPRIGHT
#تعریف_کړه NET_WM_MOVERESIZE_اندازه_TOPRIGHT 2
#د_که_پای

#که_نه_تعریف_شوی NET_WM_MOVERESIZE_اندازه_ښی
#تعریف_کړه NET_WM_MOVERESIZE_اندازه_ښی 3
#د_که_پای

#که_نه_تعریف_شوی NET_WM_MOVERESIZE_اندازه_BOTTOMRIGHT
#تعریف_کړه NET_WM_MOVERESIZE_اندازه_BOTTOMRIGHT 4
#د_که_پای

#که_نه_تعریف_شوی NET_WM_MOVERESIZE_اندازه_BOTTOM
#تعریف_کړه NET_WM_MOVERESIZE_اندازه_BOTTOM 5
#د_که_پای

#که_نه_تعریف_شوی NET_WM_MOVERESIZE_اندازه_BOTTOMLEFT
#تعریف_کړه NET_WM_MOVERESIZE_اندازه_BOTTOMLEFT 6
#د_که_پای

#که_نه_تعریف_شوی NET_WM_MOVERESIZE_اندازه_کیڼ
#تعریف_کړه NET_WM_MOVERESIZE_اندازه_کیڼ 7
#د_که_پای

#که_نه_تعریف_شوی _NET_WM_MOVERESIZE_MOVE
#تعریف_کړه _NET_WM_MOVERESIZE_MOVE 8
#د_که_پای

تعريفنوع بنية
{
    بینښه حرف *معلومات;
    صحيح format, شمېر;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ساكن فراغ X11_ReadProperty(SDL_x11Prop *p, Display *disp, کړکۍ_2 w, Atom prop)
{
    بینښه حرف *ret = عدم;
    Atom type;
    صحيح fmt;
    بینښه اوږد شمېر;
    بینښه اوږد بایټونه_کیڼ;
    صحيح بایټونه_fetch = 0;

    افعل {
        إذا (ret) {
            X11_XFree(ret);
        }
        X11_XGet_کړکۍ_Property(disp, w, prop, 0, بایټونه_fetch, False, AnyPropertyType, &type, &fmt, &شمېر, &بایټونه_کیڼ, &ret);
        بایټونه_fetch += بایټونه_کیڼ;
    } طالما (بایټونه_کیڼ != 0);

    p->معلومات = ret;
    p->format = fmt;
    p->شمېر = شمېر;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
ساكن Atom X11_Pick_موخه(Display *disp, Atom list[], صحيح list_شمېر)
{
    ثابت Atom متن_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    لكل (صحيح i = 0; i < list_شمېر && request != متن_uri_request; i++) {
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
ساكن Atom X11_Pick_موخه_From_Atoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    صحيح شمېر = 0;
    Atom atom[3];
    إذا (a0 != None) {
        atom[شمېر++] = a0;
    }
    إذا (a1 != None) {
        atom[شمېر++] = a1;
    }
    إذا (a2 != None) {
        atom[شمېر++] = a2;
    }
    أرجع X11_Pick_موخه(disp, atom, شمېر);
}

بنية کلی_Repeat_Check_معلومات
{
    XEvent *event;
    bool وموندل;
};

ساكن Bool X11_کلی_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    بنية کلی_Repeat_Check_معلومات *d = (بنية کلی_Repeat_Check_معلومات *)arg;
    إذا (chkev->type == کلی_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.وخت - d->event->xkey.وخت < 2) {
        d->وموندل = true;
    }
    أرجع False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
ساكن bool X11_کلی_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    بنية کلی_Repeat_Check_معلومات d;
    d.event = event;
    d.وموندل = false;
    إذا (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_کلی_Repeat_Check_If_Event, (XPointer)&d);
    }
    أرجع d.وموندل;
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

فراغ SDL_سېټ_X11_Event_Hook(SDL_X11EventHook callback, فراغ *userdata)
{
    g_X11EventHook = callback;
    g_X11_Event_Hook_معلومات = userdata;
}

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
ساكن فراغ X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_Video_معلومات *videodata = _this->دننی;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    إذا (X11_XGet_Event_معلومات(videodata->display, cookie)) {
        إذا (!g_X11EventHook || g_X11EventHook(g_X11_Event_Hook_معلومات, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFree_Event_معلومات(videodata->display, cookie);
    }
}
#د_که_پای // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

ساكن فراغ X11_Update_System_کلی_Modifiers(SDL_Video_معلومات *viddata)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        إذا (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.بنسټ_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } وإلا
#د_که_پای
        {
        کړکۍ_2 junk_کړکۍ;
        صحيح x, y;
        بینښه صحيح mod_ماسک;

        X11_XQuery_اشاره_ګر(viddata->display, Default_ریښه_کړکۍ(viddata->display), &junk_کړکۍ, &junk_کړکۍ, &x, &y, &x, &y, &mod_ماسک);
        viddata->keyboard.pressed_modifiers = mod_ماسک & (ښويدنه_ماسک_2 | Control_ماسک | Mod1_ماسک | Mod3_ماسک | Mod4_ماسک | Mod5_ماسک);
        viddata->keyboard.locked_modifiers = mod_ماسک & (قلف_ماسک | viddata->keyboard.numlock_ماسک | viddata->keyboard.scrolllock_ماسک);
    }
}

ساكن فراغ X11_ReconcileModifiers(SDL_Video_معلومات *viddata, bool کلی_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    إذا (کلی_pressed) {
        إذا (viddata->keyboard.pressed_modifiers & ښويدنه_ماسک_2) {
            إذا (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ښويدنه) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ښويدنه;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ښويدنه);
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
        إذا (viddata->keyboard.pressed_modifiers & ښويدنه_ماسک_2) {
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ښويدنه)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ښويدنه;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ښويدنه;
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
            إذا (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ډېرپېښ)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ډېرپېښ;
            }
        } وإلا {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ډېرپېښ;
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
    إذا (viddata->keyboard.locked_modifiers & ښويدنه_ماسک_2) {
        إذا (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ښويدنه) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ښويدنه;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ښويدنه);
        } وإلا إذا (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ښويدنه)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ښويدنه;
        }
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ښويدنه;
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
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ډېرپېښ;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ډېرپېښ;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_ماسک) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    إذا (viddata->keyboard.locked_modifiers & قلف_ماسک) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_ماسک) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_عدد;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_عدد;
    }

    إذا (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_ماسک) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } وإلا {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_سېټ_Mod_State(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

ساكن فراغ X11_Handle_Modifier_کلیګانې(SDL_Video_معلومات *viddata, SDL_Scancode scancode, bool pressed)
{
    ثابت SDL_Keycode keycode = SDL_Get_کلی_From_Scancode(scancode, SDL_KMOD_NONE, false);
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
    حالة SDLK_ډېرپېښ:
        mod = SDL_KMOD_ډېرپېښ;
        اكسر;
    حالة SDLK_LEVEL5_ښويدنه:
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
            بینښه صحيح cur_ماسک = viddata->keyboard.locked_modifiers;
            X11_Update_System_کلی_Modifiers(viddata);

            إذا (viddata->keyboard.locked_modifiers & قلف_ماسک) {
                cur_ماسک |= قلف_ماسک;
            } وإلا {
                cur_ماسک &= ~قلف_ماسک;
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
    SDL_Video_معلومات *videodata = _this->دننی;
    Display *display = videodata->display;
    حرف کلیګانې[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_کلی_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_عدد | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= قلف_ماسک | videodata->keyboard.numlock_ماسک| videodata->keyboard.scrolllock_ماسک;

    X11_XQueryKeymap(display, کلیګانې);

    ثابت bool *keystate = SDL_GetKeyboardState(عدم);
    لكل (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.کلی_layout); ++keycode) {
        ثابت SDL_Scancode scancode = videodata->keyboard.کلی_layout[keycode];
        ثابت bool x11_کلی_Pressed = (کلیګانې[keycode / 8] & (1 << (keycode % 8))) != 0;
        ثابت bool sdl_کلی_Pressed = keystate[scancode];

        إذا (x11_کلی_Pressed && !sdl_کلی_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            بدل (SDL_Get_کلی_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            حالة SDLK_LCTRL:
            حالة SDLK_RCTRL:
            حالة SDLK_LSHIFT:
            حالة SDLK_RSHIFT:
            حالة SDLK_LALT:
            حالة SDLK_RALT:
            حالة SDLK_LGUI:
            حالة SDLK_RGUI:
            حالة SDLK_ډېرپېښ:
            حالة SDLK_LEVEL5_ښويدنه:
                X11_Handle_Modifier_کلیګانې(videodata, scancode, true);
                SDL_Send_Keyboard_کلی_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                اكسر;
            افتراضي:
                اكسر;
            }
        } وإلا إذا (!x11_کلی_Pressed && sdl_کلی_Pressed) {
            X11_Handle_Modifier_کلیګانې(videodata, scancode, false);
            SDL_Send_Keyboard_کلی_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_کلی_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

ساكن فراغ X11_Dispatch_Focus_دننه(SDL_VideoDevice *_this, SDL_کړکۍ_معلومات *معلومات)
{
#که_تعریف_شوی DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", معلومات->xwindow);
#د_که_پای
    SDL_سېټ_Keyboard_Focus(معلومات->کړکۍ);
    X11_ReconcileKeyboardState(_this);
#که_تعریف_شوی X_HAVE_UTF8_STRING
    إذا (معلومات->ic) {
        X11_XSetICFocus(معلومات->ic);
    }
#د_که_پای
    إذا (معلومات->flashing_کړکۍ) {
        X11_Flash_کړکۍ(_this, معلومات->کړکۍ, SDL_FLASH_CANCEL);
    }
}

ساكن فراغ X11_Dispatch_Focus_بهر(SDL_VideoDevice *_this, SDL_کړکۍ_معلومات *معلومات)
{
#که_تعریف_شوی DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", معلومات->xwindow);
#د_که_پای
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    إذا (معلومات->کړکۍ == SDL_GetKeyboardFocus()) {
        SDL_سېټ_Keyboard_Focus(عدم);
    }
#که_تعریف_شوی X_HAVE_UTF8_STRING
    إذا (معلومات->ic) {
        X11_XUnsetICFocus(معلومات->ic);
    }
#د_که_پای
}

ساكن فراغ X11_DispatchMapNotify(SDL_کړکۍ_معلومات *معلومات)
{
    SDL_کړکۍ *کړکۍ = معلومات->کړکۍ;

    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_SHOWN, 0, 0);
    معلومات->was_shown = true;

    // This may be sent when restoring a minimized window.
    إذا (کړکۍ->flags & SDL_کړکۍ_MINIMIZED) {
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESTORED, 0, 0);
        SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_EXPOSED, 0, 0);
    }

    إذا (کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS) {
        SDL_Update_کړکۍ_Grab(کړکۍ);
    }
}

ساكن فراغ X11_DispatchUnmapNotify(SDL_کړکۍ_معلومات *معلومات)
{
    SDL_کړکۍ *کړکۍ = معلومات->کړکۍ;

    // This may be sent when minimizing a window.
    إذا (!کړکۍ->is_hiding) {
        SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_MINIMIZED, 0, 0);
        SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_OCCLUDED, 0, 0);
    } وإلا {
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_HIDDEN, 0, 0);
    }
}

ساكن فراغ Dispatch_کړکۍ_Move(SDL_VideoDevice *_this, ثابت SDL_کړکۍ_معلومات *معلومات, ثابت SDL_ټکی *ټکی)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    SDL_کړکۍ *کړکۍ = معلومات->کړکۍ;
    Display *display = videodata->display;
    XEvent evt;

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_اشاره_ګر(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_پیغام;
    evt.xclient.کړکۍ = معلومات->xwindow;
    evt.xclient.پیغام_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.معلومات.l[0] = (size_t)کړکۍ->x + ټکی->x;
    evt.xclient.معلومات.l[1] = (size_t)کړکۍ->y + ټکی->y;
    evt.xclient.معلومات.l[2] = _NET_WM_MOVERESIZE_MOVE;
    evt.xclient.معلومات.l[3] = Button1;
    evt.xclient.معلومات.l[4] = 0;
    X11_XSendEvent(display, Default_ریښه_کړکۍ(display), False, Substructure_Redirect_ماسک | Substructure_Notify_ماسک, &evt);

    X11_XSync(display, 0);
}

ساكن فراغ مهالوېش_کړکۍ_Move(SDL_VideoDevice *_this, SDL_کړکۍ_معلومات *معلومات, ثابت SDL_ټکی *ټکی)
{
    معلومات->pending_move = true;
    معلومات->pending_move_ټکی = *ټکی;
}

ساكن فراغ Initiate_کړکۍ_Resize(SDL_VideoDevice *_this, ثابت SDL_کړکۍ_معلومات *معلومات, ثابت SDL_ټکی *ټکی, صحيح direction)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    SDL_کړکۍ *کړکۍ = معلومات->کړکۍ;
    Display *display = videodata->display;
    XEvent evt;

    إذا (direction < NET_WM_MOVERESIZE_اندازه_TOPLEFT || direction > NET_WM_MOVERESIZE_اندازه_کیڼ) {
        أرجع;
    }

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_اشاره_ګر(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_پیغام;
    evt.xclient.کړکۍ = معلومات->xwindow;
    evt.xclient.پیغام_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.معلومات.l[0] = (size_t)کړکۍ->x + ټکی->x;
    evt.xclient.معلومات.l[1] = (size_t)کړکۍ->y + ټکی->y;
    evt.xclient.معلومات.l[2] = direction;
    evt.xclient.معلومات.l[3] = Button1;
    evt.xclient.معلومات.l[4] = 0;
    X11_XSendEvent(display, Default_ریښه_کړکۍ(display), False, Substructure_Redirect_ماسک | Substructure_Notify_ماسک, &evt);

    X11_XSync(display, 0);
}

bool X11_Process_موندنه_Test(SDL_VideoDevice *_this, SDL_کړکۍ_معلومات *معلومات, ثابت عائم x, ثابت عائم y, bool force_new_پایله)
{
    SDL_کړکۍ *کړکۍ = معلومات->کړکۍ;
    إذا (!کړکۍ->موندنه_test) أرجع false;
    ثابت SDL_ټکی ټکی = { (صحيح)x, (صحيح)y };
    SDL_موندنه_Test_پایله rc = کړکۍ->موندنه_test(کړکۍ, &ټکی, کړکۍ->موندنه_test_معلومات);
    إذا (!force_new_پایله && rc == معلومات->موندنه_test_پایله) {
        أرجع true;
    }
    X11_سېټ_موندنه_Test_Cursor(rc);
    معلومات->موندنه_test_پایله = rc;
    أرجع true;
}

bool X11_Trigger_موندنه_Test_Action(SDL_VideoDevice *_this, SDL_کړکۍ_معلومات *معلومات, ثابت عائم x, ثابت عائم y)
{
    SDL_کړکۍ *کړکۍ = معلومات->کړکۍ;

    إذا (کړکۍ->موندنه_test) {
        ثابت SDL_ټکی ټکی = { (صحيح)x, (صحيح)y };
        ساكن ثابت صحيح directions[] = {
            NET_WM_MOVERESIZE_اندازه_TOPLEFT, NET_WM_MOVERESIZE_اندازه_سر,
            NET_WM_MOVERESIZE_اندازه_TOPRIGHT, NET_WM_MOVERESIZE_اندازه_ښی,
            NET_WM_MOVERESIZE_اندازه_BOTTOMRIGHT, NET_WM_MOVERESIZE_اندازه_BOTTOM,
            NET_WM_MOVERESIZE_اندازه_BOTTOMLEFT, NET_WM_MOVERESIZE_اندازه_کیڼ
        };

        بدل (معلومات->موندنه_test_پایله) {
        حالة SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            إذا (معلومات->کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS) {
                Dispatch_کړکۍ_Move(_this, معلومات, &ټکی);
            } وإلا {
                مهالوېش_کړکۍ_Move(_this, معلومات, &ټکی);
            }
            أرجع true;

        حالة SDL_HITTEST_RESIZE_TOPLEFT:
        حالة SDL_HITTEST_RESIZE_سر:
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
        حالة SDL_HITTEST_RESIZE_ښی:
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        حالة SDL_HITTEST_RESIZE_BOTTOM:
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
        حالة SDL_HITTEST_RESIZE_کیڼ:
            Initiate_کړکۍ_Resize(_this, معلومات, &ټکی, directions[معلومات->موندنه_test_پایله - SDL_HITTEST_RESIZE_TOPLEFT]);
            أرجع true;

        افتراضي:
            أرجع false;
        }
    }

    أرجع false;
}

ساكن فراغ X11_Update_User_وخت(SDL_کړکۍ_معلومات *معلومات, ثابت بینښه اوږد latest)
{
    إذا (latest && (latest != معلومات->user_وخت)) {
        SDL_Video_معلومات *videodata = معلومات->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, معلومات->xwindow, videodata->atoms.NET_WM_USER_وخت,
                            XA_CARDINAL, 32, Prop_ډېرپېښ_Replace,
                            (ثابت بینښه حرف *)&latest, 1);
#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", معلومات->xwindow, latest);
#د_که_پای
        معلومات->user_وخت = latest;
    }
}

ساكن بینښه حرف x11_وروستی_error;
ساكن صحيح Bad_کړکۍ_Error_Handler(Display *d, XErrorEvent *e)
{
    x11_وروستی_error = e->error_کوډ;

    // Ignore BadWindow in cases where it's not fatal.
    إذا (e->error_کوډ != Bad_کړکۍ) {
        حرف err_پیغام[128];
        X11_XGet_Error_متن(d, e->error_کوډ, err_پیغام, حجم(err_پیغام));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_کوډ, err_پیغام, e->request_کوډ);
    }
    أرجع 0;
}

ساكن فراغ X11_HandleClipboardEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    صحيح i;
    SDL_Video_معلومات *videodata = _this->دننی;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_کړکۍ != None);
    SDL_assert(xevent->xany.کړکۍ == videodata->clipboard_کړکۍ);

    بدل (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    حالة SelectionRequest:
    {
        ثابت XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        صحيح mime_formats;
        بینښه حرف *seln_معلومات;
        size_t seln_اوږدتیا = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_Clipboard_معلومات *clipboard;

#که_تعریف_شوی DEBUG_XEVENTS
        حرف *atom_name;
        atom_name = X11_XGetAtomName(display, req->موخه);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->موخه, atom_name);
        إذا (atom_name) {
            X11_XFree(atom_name);
        }
#د_که_پای

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_وروستی_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_کړکۍ_Error_Handler);

        إذا (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } وإلا {
            clipboard = &videodata->clipboard;
        }

        SDL_zero(sevent);
        sevent.xany.type = SelectionNotify;
        sevent.xselection.selection = req->selection;
        sevent.xselection.موخه = None;
        sevent.xselection.property = None; // tell them no by default
        sevent.xselection.requestor = req->requestor;
        sevent.xselection.وخت = req->وخت;

        /* !!! FIXME: We were probably storing this on the root window
           because an SDL window might go away...? but we don't have to do
           this now (or ever, really). */

        إذا (req->موخه == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_شمېر + 1) * حجم(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            لكل (i = 0; i < clipboard->mime_شمېر; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, Prop_ډېرپېښ_Replace,
                                (بینښه حرف *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.موخه = XA_TARGETS;
            SDL_free(supportedFormats);
        } وإلا {
            إذا (clipboard->callback) {
                لكل (i = 0; i < clipboard->mime_شمېر; ++i) {
                    ثابت حرف *mime_type = clipboard->mime_types[i];
                    إذا (X11_XInternAtom(display, mime_type, False) != req->موخه) {
                        استمر;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_معلومات = (بینښه حرف *)clipboard->callback(clipboard->userdata, mime_type, &seln_اوږدتیا);
                    إذا (seln_معلومات) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->موخه, 8, Prop_ډېرپېښ_Replace,
                                            seln_معلومات, seln_اوږدتیا);
                        sevent.xselection.property = req->property;
                        sevent.xselection.موخه = req->موخه;
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
#که_تعریف_شوی DEBUG_XEVENTS
        ثابت حرف *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        ثابت حرف *موخه_Name = xsel->موخه ? X11_XGetAtomName(display, xsel->موخه) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, موخه_Name, propName);
#د_که_پای
        إذا (xsel->موخه == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            بینښه حرف *معلومات = عدم;
            صحيح format_property = 0;
            بینښه اوږد اوږدتیا = 0;
            بینښه اوږد بایټونه_کیڼ = 0;
            صحيح j;

            X11_XGet_کړکۍ_Property(display, Get_کړکۍ(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &اوږدتیا, &بایټونه_کیڼ, &معلومات);

            صحيح allocationsize = (اوږدتیا + 1) * حجم(حرف *);
            لكل (j = 0, patom = (Atom *)معلومات; j < اوږدتیا; j++, patom++) {
                حرف *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            حرف **new_mime_types = SDL_Allocate_Temporary_حافظه(allocationsize);
            إذا (new_mime_types) {
                حرف *strPtr = (حرف *)(new_mime_types + اوږدتیا + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                لكل (j = 0, patom = (Atom *)معلومات; j < اوږدتیا; j++, patom++) {
                    حرف *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    ثابت size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[اوږدتیا] = عدم;

                SDL_SendClipboardUpdate(false, new_mime_types, اوږدتیا);

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

#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.موخه);
#د_که_پای

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
        حرف *name_د_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        إذا (SDL_strncmp(name_د_atom, "SDL_SELECTION", حجم("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_ارزښت) {
            videodata->selection_incr_انتظار = false;
        }

        إذا (name_د_atom) {
            X11_XFree(name_د_atom);
        }
    } اكسر;
    }
}

ساكن Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    أرجع ev->type == MapNotify &&
           ev->xmap.کړکۍ == unmap->کړکۍ &&
           ev->xmap.serial == unmap->serial;
}

ساكن Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    أرجع ev->type == ReparentNotify &&
           ev->xreparent.کړکۍ == unmap->کړکۍ &&
           ev->xreparent.serial == unmap->serial;
}

ساكن bool Is_لوړ_Latin1(ثابت حرف *string, صحيح اوږدتیا)
{
    طالما (اوږدتیا-- > 0) {
        Uint8 ch = (Uint8)*string;
        إذا (ch >= 0x80) {
            أرجع true;
        }
        ++string;
    }
    أرجع false;
}

ساكن صحيح XLookupStringAsUTF8(XKeyEvent *event_struct, حرف *بفر_return, صحيح بایټونه_بفر, کلی_Sym *keysym_return, XCompose_حالت *حالت_دننه_بهر)
{
    صحيح پایله = X11_XLookupString(event_struct, بفر_return, بایټونه_بفر, keysym_return, حالت_دننه_بهر);
    إذا (Is_لوړ_Latin1(بفر_return, پایله)) {
        حرف *utf8_متن = SDL_iconv_string("UTF-8", "ISO-8859-1", بفر_return, پایله + 1);
        إذا (utf8_متن) {
            SDL_strlcpy(بفر_return, utf8_متن, بایټونه_بفر);
            SDL_free(utf8_متن);
            أرجع SDL_strlen(بفر_return);
        } وإلا {
            أرجع 0;
        }
    }
    أرجع پایله;
}

SDL_کړکۍ_معلومات *X11_پیدا_کړه_کړکۍ(SDL_Video_معلومات *videodata, کړکۍ_2 کړکۍ)
{
    إذا (videodata && videodata->windowlist) {
        لكل (صحيح i = 0; i < videodata->numwindows; ++i) {
            إذا ((videodata->windowlist[i] != عدم) &&
                (videodata->windowlist[i]->xwindow == کړکۍ)) {
                أرجع videodata->windowlist[i];
            }
        }
    }
    أرجع عدم;
}

Uint64 X11_GetEventTimestamp(بینښه اوږد وخت)
{
    // FIXME: Get the event time in the SDL tick time base
    أرجع SDL_GetTicksNS();
}

فراغ X11_Handle_کلی_Event(SDL_VideoDevice *_this, SDL_کړکۍ_معلومات *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    Display *display = videodata->display;
    کلی_کوډ_2 keycode = xevent->xkey.keycode;
    کلی_Sym keysym = No_نښه;
    صحيح متن_اوږدتیا = 0;
    حرف متن[64];
    حالت_2 حالت = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == کلی_Press);
    SDL_Scancode scancode = videodata->keyboard.کلی_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.وخت);

#که_تعریف_شوی DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.کړکۍ, (xevent->type == کلی_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#د_که_پای
#که_تعریف_شوی DEBUG_SCANCODES
    إذا (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        صحيح min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_کلی_کوډ_منزل_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysym_منزل_String(keysym));
    }
#د_که_پای // DEBUG SCANCODES

    متن[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    إذا (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (ښويدنه_ماسک_2 | Control_ماسک | Mod1_ماسک | Mod3_ماسک | Mod4_ماسک | Mod5_ماسک);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (قلف_ماسک | videodata->keyboard.numlock_ماسک | videodata->keyboard.scrolllock_ماسک);
    }

    إذا (SDL_متن_ننوت_فعال(windowdata->کړکۍ)) {
        // filter events catches XIM events and sends them to the correct handler
        إذا (X11_XFilterEvent(xevent, None)) {
#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.کړکۍ);
#د_که_پای
            handled_by_ime = true;
        }

        إذا (!handled_by_ime) {
#که_تعریف_شوی X_HAVE_UTF8_STRING
            إذا (windowdata->ic && xevent->type == کلی_Press) {
                متن_اوږدتیا = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, متن, حجم(متن) - 1,
                                      &keysym, &حالت);
            } وإلا {
                متن_اوږدتیا = XLookupStringAsUTF8(&xevent->xkey, متن, حجم(متن) - 1, &keysym, عدم);
            }
#وإلا
            متن_اوږدتیا = XLookupStringAsUTF8(&xevent->xkey, متن, حجم(متن) - 1, &keysym, عدم);
#د_که_پای
        }
    }

    إذا (!handled_by_ime) {
        إذا (pressed) {
            X11_Handle_Modifier_کلیګانې(videodata, scancode, true);
            SDL_Send_Keyboard_کلی_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            إذا (*متن && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                متن[متن_اوږدتیا] = '\0';
                X11_ClearComposition(windowdata);
                SDL_Send_Keyboard_متن(متن);
            }
        } وإلا {
            إذا (X11_کلی_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                أرجع;
            }

            X11_Handle_Modifier_کلیګانې(videodata, scancode, false);
            SDL_Send_Keyboard_کلی_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    إذا (pressed) {
        X11_Update_User_وخت(windowdata, xevent->xkey.وخت);
    }
}

فراغ X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_کړکۍ_معلومات *windowdata, SDL_MouseID mouseID, صحيح button, عائم x, عائم y, بینښه اوږد وخت, بینښه اوږد serial)
{
    SDL_کړکۍ *کړکۍ = windowdata->کړکۍ;
    صحيح xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(وخت);

#که_تعریف_شوی DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#د_که_پای

    SDL_Mouse *mouse = SDL_GetMouse();
    إذا (!mouse->relative_ډېرپېښ && (x != mouse->x || y != mouse->y)) {
        X11_Process_موندنه_Test(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, کړکۍ, mouseID, false, x, y);
    }

    إذا (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, کړکۍ, mouseID, (عائم)-xticks, (عائم)yticks, SDL_MOUSEWHEEL_نورمال);
    } وإلا {
        إذا (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        إذا (button == Button1) {
            إذا (X11_Trigger_موندنه_Test_Action(_this, windowdata, x, y)) {
                SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_موندنه_TEST, 0, 0);
                أرجع; // don't pass this event on to app.
            }
        }
        إذا (windowdata->وروستی_focus_event_وخت) {
            ثابت صحيح X11_FOCUS_CLICK_TIMEOUT = 10;
            إذا (SDL_GetTicks() < (windowdata->وروستی_focus_event_وخت + X11_FOCUS_CLICK_TIMEOUT)) {
                إذا (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->وروستی_focus_event_وخت = 0;
        }
        إذا (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, کړکۍ, mouseID, button, true);
        }
    }
    X11_Update_User_وخت(windowdata, وخت);
}

فراغ X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_کړکۍ_معلومات *windowdata, SDL_MouseID mouseID, صحيح button, بینښه اوږد وخت)
{
    SDL_کړکۍ *کړکۍ = windowdata->کړکۍ;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    صحيح xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(وخت);

#که_تعریف_شوی DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#د_که_پای
    إذا (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        إذا (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, کړکۍ, mouseID, button, false);

        إذا (کړکۍ->دننی->pending_grab) {
            X11_سېټ_کړکۍ_Mouse_Grab(_this, کړکۍ, true);
        }
    }
}

فراغ X11_Get_Border_ارزښتونه(SDL_کړکۍ_معلومات *معلومات)
{
    SDL_Video_معلومات *videodata = معلومات->videodata;
    Display *display = videodata->display;

    Atom type;
    صحيح format;
    بینښه اوږد nitems, بایټونه_after;
    بینښه حرف *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    إذا (!(معلومات->کړکۍ->flags & SDL_کړکۍ_BORDERLESS)) {
        إذا (X11_XGet_کړکۍ_Property(display, معلومات->xwindow, videodata->atoms.NET_چوکاټ_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &بایټونه_after, &property) == Success) {
            إذا (type != None && nitems == 4) {
                معلومات->border_کیڼ = (صحيح)((اوږد *)property)[0];
                معلومات->border_ښی = (صحيح)((اوږد *)property)[1];
                معلومات->border_سر = (صحيح)((اوږد *)property)[2];
                معلومات->border_bottom = (صحيح)((اوږد *)property)[3];
            }
            X11_XFree(property);

#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", معلومات->border_کیڼ, معلومات->border_ښی, معلومات->border_سر, معلومات->border_bottom);
#د_که_پای
        }
    } وإلا {
        معلومات->border_کیڼ = معلومات->border_سر = معلومات->border_ښی = معلومات->border_bottom = 0;
    }
}

فراغ X11_EmitConfigureNotifyEvents(SDL_کړکۍ_معلومات *معلومات, XConfigureEvent *xevent)
{
    إذا (!معلومات->اندازه_move_event_flags) {
        صحيح x = xevent->x;
        صحيح y = xevent->y;

        إذا (xevent->x != معلومات->وروستی_xconfigure.x ||
            xevent->y != معلومات->وروستی_xconfigure.y) {
            معلومات->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_Global_منزل_Relative_For_کړکۍ(معلومات->کړکۍ, x, y, &x, &y);
        SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_MOVED, x, y);

        لكل (SDL_کړکۍ *w = معلومات->کړکۍ->لومړی_ماشوم; w; w = w->بل_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            إذا (SDL_کړکۍ_IS_POPUP(w) && !(w->flags & SDL_کړکۍ_HIDDEN)) {
                X11_Update_کړکۍ_Position(w, true);
            }
        }

        إذا (xevent->پلنوالی != معلومات->وروستی_xconfigure.پلنوالی ||
            xevent->لوړوالی != معلومات->وروستی_xconfigure.لوړوالی) {
            معلومات->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_RESIZED, xevent->پلنوالی, xevent->لوړوالی);
    }

    SDL_copyp(&معلومات->وروستی_xconfigure, xevent);
}

ساكن فراغ X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    Display *display;
    SDL_کړکۍ_معلومات *معلومات;
    XClient_پیغام_Event m;
    صحيح i;

    SDL_assert(videodata != عدم);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    إذا (xevent->type != کلی_Press && xevent->type != کلی_Release) {
        إذا (X11_XFilterEvent(xevent, None)) {
#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.کړکۍ);
#د_که_پای
            أرجع;
        }
    }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    إذا (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        أرجع;
    }
#د_که_پای

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    إذا (g_X11EventHook) {
        إذا (!g_X11EventHook(g_X11_Event_Hook_معلومات, xevent)) {
            أرجع;
        }
    }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XRANDR
    إذا (videodata->xrandr_event_بنسټ && (xevent->type == (videodata->xrandr_event_بنسټ + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#د_که_پای

#که_تعریف_شوی DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.کړکۍ);
#د_که_پای

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XFIXES
    إذا (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#د_که_پای

        إذا (ev->subtype == XFixes_سېټ_Selection_Owner_Notify)
        {
            إذا (ev->selection != videodata->atoms.CLIPBOARD)
                أرجع;

            إذا (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_کړکۍ)
                أرجع;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, Get_کړکۍ(_this), Current_وخت);
        }

        أرجع;
    }
#د_که_پای // SDL_VIDEO_DRIVER_X11_XFIXES

    إذا ((videodata->clipboard_کړکۍ != None) &&
        (videodata->clipboard_کړکۍ == xevent->xany.کړکۍ)) {
        X11_HandleClipboardEvent(_this, xevent);
        أرجع;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    معلومات = X11_پیدا_کړه_کړکۍ(videodata, xevent->xany.کړکۍ);

    إذا (!معلومات) {
        // The window for KeymapNotify, etc events is 0
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        إذا (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            بدل (xkbevent->any.xkb_type) {
            حالة XkbStateNotify:
            {
#که_تعریف_شوی DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.کړکۍ);
#د_که_پای
                إذا ((xkbevent->state.بدل_شوی & Xkb_ډله_State_ماسک) && xkbevent->state.ډله != videodata->keyboard.xkb.current_ډله) {
                    videodata->keyboard.xkb.current_ډله = xkbevent->state.ډله;
                    SDL_سېټ_Keymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_ډله], true);
                }

                إذا (xkbevent->state.بدل_شوی & Xkb_Modifier_State_ماسک) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.بنسټ_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } اكسر;

            حالة XkbMapNotify:
#که_تعریف_شوی DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.کړکۍ);
                SDL_FALLTHROUGH;
#د_که_پای
            حالة XkbNewKeyboardNotify:
            {
#که_تعریف_شوی DEBUG_XEVENTS
                إذا (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.کړکۍ);
                }
#د_که_پای
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                إذا (xkbevent->any.serial != videodata->keyboard.xkb.وروستی_map_serial) {
                    videodata->keyboard.xkb.وروستی_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } اكسر;

            افتراضي:
                اكسر;
            }
        } وإلا
#د_که_پای
        إذا (xevent->type == KeymapNotify) {
#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.کړکۍ);
#د_که_پای
            إذا (SDL_GetKeyboardFocus() != عدم) {
                إذا (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } وإلا إذا (xevent->type == MappingNotify) {
            ثابت صحيح request = xevent->xmapping.request;

            إذا (request == Mapping_اشاره_ګر) {
#که_تعریف_شوی DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.کړکۍ);
#د_که_پای
                X11_Xinput2_Update_اشاره_ګر_Mapping(_this);
            } وإلا إذا (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#که_تعریف_شوی DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.کړکۍ);
#د_که_پای
                إذا (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } وإلا إذا (xevent->type == PropertyNotify && videodata) {
            حرف *name_د_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            إذا (name_د_atom) {
                إذا (SDL_startswith(name_د_atom, "_ICC_PROFILE")) {
                    XWindow_ځانګړتیاوې attrib;
                    صحيح screennum;
                    لكل (i = 0; i < videodata->numwindows; ++i) {
                        إذا (videodata->windowlist[i] != عدم) {
                            معلومات = videodata->windowlist[i];
                            X11_XGet_کړکۍ_ځانګړتیاوې(display, معلومات->xwindow, &attrib);
                            screennum = X11_XScreen_شمېره_د_Screen(attrib.screen);
                            إذا (screennum == 0 && SDL_strcmp(name_د_atom, "_ICC_PROFILE") == 0) {
                                SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_ICCPROF_بدل_شوی, 0, 0);
                            } وإلا إذا (SDL_strncmp(name_د_atom, "_ICC_PROFILE_", حجم("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_د_atom) > حجم("_ICC_PROFILE_") - 1) {
                                صحيح iccscreennum = SDL_atoi(&name_د_atom[حجم("_ICC_PROFILE_") - 1]);

                                إذا (screennum == iccscreennum) {
                                    SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_ICCPROF_بدل_شوی, 0, 0);
                                }
                            }
                        }
                    }
                } وإلا إذا (SDL_strcmp(name_د_atom, "_NET_WORKAREA") == 0) {
                    لكل (i = 0; i < _this->عدد_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_بدل_شوی, 0, 0);
                    }
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XRANDR
                } وإلا إذا (SDL_strcmp(name_د_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_د_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#د_که_پای
                }
                X11_XFree(name_د_atom);
            }
        }
        أرجع;
    }

    بدل (xevent->type) {

        // Gaining mouse coverage?
    حالة EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.کړکۍ,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.ډېرپېښ);
        إذا (xevent->xcrossing.ډېرپېښ == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        إذا (xevent->xcrossing.ډېرپېښ == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#د_که_پای
        SDL_سېټ_Mouse_Focus(معلومات->کړکۍ);

        mouse->وروستی_x = xevent->xcrossing.x;
        mouse->وروستی_y = xevent->xcrossing.y;

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XFIXES
        {
            // Only create the barriers if we have input focus
            SDL_کړکۍ_معلومات *windowdata = معلومات->کړکۍ->دننی;
            إذا ((معلومات->اشاره_ګر_barrier_فعال == true) && windowdata->کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->کړکۍ, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#د_که_پای

        إذا (!mouse->relative_ډېرپېښ) {
            SDL_SendMouseMotion(0, معلومات->کړکۍ, SDL_GLOBAL_MOUSE_ID, false, (عائم)xevent->xcrossing.x, (عائم)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        إذا (!(معلومات->کړکۍ->flags & SDL_کړکۍ_MOUSE_CAPTURE)) {
            SDL_Update_کړکۍ_Grab(معلومات->کړکۍ);
        }

        X11_Process_موندنه_Test(_this, معلومات, mouse->وروستی_x, mouse->وروستی_y, true);
    } اكسر;
        // Losing mouse coverage?
    حالة LeaveNotify:
    {
#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.کړکۍ,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.ډېرپېښ);
        إذا (xevent->xcrossing.ډېرپېښ == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        إذا (xevent->xcrossing.ډېرپېښ == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#د_که_پای
        إذا (!SDL_GetMouse()->relative_ډېرپېښ) {
            SDL_SendMouseMotion(0, معلومات->کړکۍ, SDL_GLOBAL_MOUSE_ID, false, (عائم)xevent->xcrossing.x, (عائم)xevent->xcrossing.y);
        }

        إذا (xevent->xcrossing.ډېرپېښ != NotifyGrab &&
            xevent->xcrossing.ډېرپېښ != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            إذا (!(معلومات->کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
                X11_سېټ_کړکۍ_Keyboard_Grab(_this, معلومات->کړکۍ, false);
            }

            SDL_سېټ_Mouse_Focus(عدم);
        }
    } اكسر;

        // Gaining input focus?
    حالة Focus_دننه:
    {
        إذا (xevent->xfocus.ډېرپېښ == NotifyGrab || xevent->xfocus.ډېرپېښ == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.کړکۍ);
#د_که_پای
            اكسر;
        }

        إذا (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_اشاره_ګر) {
#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.کړکۍ);
#د_که_پای
            اكسر;
        }
#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.کړکۍ);
#د_که_پای
        إذا (!videodata->وروستی_ډېرپېښ_change_deadline) /* no recent mode changes */ {
            معلومات->pending_focus = PENDING_FOCUS_NONE;
            معلومات->pending_focus_وخت = 0;
            X11_Dispatch_Focus_دننه(_this, معلومات);
        } وإلا {
            معلومات->pending_focus = PENDING_FOCUS_دننه;
            معلومات->pending_focus_وخت = SDL_GetTicks() + PENDING_FOCUS_وخت;
        }
        معلومات->وروستی_focus_event_وخت = SDL_GetTicks();
    } اكسر;

        // Losing input focus?
    حالة Focus_بهر:
    {
        إذا (xevent->xfocus.ډېرپېښ == NotifyGrab || xevent->xfocus.ډېرپېښ == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.کړکۍ);
#د_که_پای
            اكسر;
        }
        إذا (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_اشاره_ګر) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.کړکۍ);
#د_که_پای
            اكسر;
        }
#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.کړکۍ);
#د_که_پای
        إذا (!videodata->وروستی_ډېرپېښ_change_deadline) /* no recent mode changes */ {
            معلومات->pending_focus = PENDING_FOCUS_NONE;
            معلومات->pending_focus_وخت = 0;
            X11_Dispatch_Focus_بهر(_this, معلومات);
        } وإلا {
            معلومات->pending_focus = PENDING_FOCUS_بهر;
            معلومات->pending_focus_وخت = SDL_GetTicks() + PENDING_FOCUS_وخت;
        }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        إذا (معلومات->اشاره_ګر_barrier_فعال == true) {
            X11_ConfineCursorWithFlags(_this, معلومات->کړکۍ, عدم, X11_BARRIER_HANDLED_BY_EVENT);
        }
#د_که_پای // SDL_VIDEO_DRIVER_X11_XFIXES
    } اكسر;


        // Have we been iconified?
    حالة UnmapNotify:
    {
        XEvent ev;

#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.کړکۍ);
#د_که_پای

        إذا (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } وإلا {
            X11_DispatchUnmapNotify(معلومات);
        }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        إذا (معلومات->اشاره_ګر_barrier_فعال == true) {
            X11_ConfineCursorWithFlags(_this, معلومات->کړکۍ, عدم, X11_BARRIER_HANDLED_BY_EVENT);
        }
#د_که_پای // SDL_VIDEO_DRIVER_X11_XFIXES
    } اكسر;

        // Have we been restored?
    حالة MapNotify:
    {
#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.کړکۍ);
#د_که_پای
        X11_DispatchMapNotify(معلومات);

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        إذا (معلومات->اشاره_ګر_barrier_فعال == true) {
            X11_ConfineCursorWithFlags(_this, معلومات->کړکۍ, &معلومات->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#د_که_پای // SDL_VIDEO_DRIVER_X11_XFIXES
    } اكسر;

        // Have we been resized or moved?
    حالة ConfigureNotify:
    {
#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.کړکۍ,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.پلنوالی, xevent->xconfigure.لوړوالی);
#د_که_پای
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        إذا (!xevent->xconfigure.send_event) {
            بینښه صحيح عدد_Children;
            کړکۍ_2 ماشوم_Return, ریښه_2, پلار_2;
            کړکۍ_2 *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_وروستی_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_کړکۍ_Error_Handler);

            X11_XQuery_ونه(معلومات->videodata->display, xevent->xconfigure.کړکۍ, &ریښه_2, &پلار_2, &Children, &عدد_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      پلار_2, Default_ریښه_کړکۍ(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &ماشوم_Return);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            إذا (x11_وروستی_error == Bad_کړکۍ) {
                اكسر;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        ثابت SDL_کړکۍ_Flags بدل_شوی = X11_GetNetWMState(_this, معلومات->کړکۍ, xevent->xproperty.کړکۍ) ^ معلومات->کړکۍ->flags;
        إذا (بدل_شوی & (SDL_کړکۍ_FULLSCREEN | SDL_کړکۍ_MAXIMIZED)) {
            SDL_copyp(&معلومات->pending_xconfigure, &xevent->xconfigure);
            معلومات->emit_اندازه_move_after_property_notify = true;
        }

        إذا (!معلومات->emit_اندازه_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(معلومات, &xevent->xconfigure);
        }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(معلومات->کړکۍ, &xevent->xconfigure);
#د_که_پای /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } اكسر;

        // Have we been requested to quit (or another client message?)
    حالة Client_پیغام:
    {
        ساكن صحيح xdnd_نسخه = 0;

        إذا (xevent->xclient.پیغام_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.معلومات.l[1] & 1;
            معلومات->xdnd_سرچینه = xevent->xclient.معلومات.l[0];
            xdnd_نسخه = (xevent->xclient.معلومات.l[1] >> 24);
#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", معلومات->xdnd_سرچینه);
            SDL_Log("Protocol version to use : %d", xdnd_نسخه);
            SDL_Log("More then 3 data types : %d", (صحيح)use_list);
#د_که_پای

            إذا (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, معلومات->xdnd_سرچینه, videodata->atoms.XdndTypeList);
                // pick one
                معلومات->xdnd_req = X11_Pick_موخه(display, (Atom *)p.معلومات, p.شمېر);
                X11_XFree(p.معلومات);
            } وإلا {
                // pick from list of three
                معلومات->xdnd_req = X11_Pick_موخه_From_Atoms(display, xevent->xclient.معلومات.l[2], xevent->xclient.معلومات.l[3], xevent->xclient.معلومات.l[4]);
            }
        } وإلا إذا (xevent->xclient.پیغام_type == videodata->atoms.XdndLeave) {
#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.معلومات.l[0]);
#د_که_پای
            SDL_SendDropComplete(معلومات->کړکۍ);
        } وإلا إذا (xevent->xclient.پیغام_type == videodata->atoms.XdndPosition) {

#که_تعریف_شوی DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            إذا (xdnd_نسخه >= 2) {
                act = xevent->xclient.معلومات.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#د_که_پای
            {
                // Drag and Drop position
                صحيح ریښه_x, ریښه_y, کړکۍ_x, کړکۍ_y;
                کړکۍ_2 ماشوم_Return;
                ریښه_x = xevent->xclient.معلومات.l[2] >> 16;
                ریښه_y = xevent->xclient.معلومات.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_ریښه_کړکۍ(display), معلومات->xwindow,
                                          ریښه_x, ریښه_y, &کړکۍ_x, &کړکۍ_y, &ماشوم_Return);

                SDL_SendDropPosition(معلومات->کړکۍ, (عائم)کړکۍ_x, (عائم)کړکۍ_y);
            }

            // reply with status
            SDL_zero(m);
            m.type = Client_پیغام;
            m.display = xevent->xclient.display;
            m.کړکۍ = xevent->xclient.معلومات.l[0];
            m.پیغام_type = videodata->atoms.Xdnd_حالت;
            m.format = 32;
            m.معلومات.l[0] = معلومات->xwindow;
            m.معلومات.l[1] = (معلومات->xdnd_req != None);
            m.معلومات.l[2] = 0; // specify an empty rectangle
            m.معلومات.l[3] = 0;
            m.معلومات.l[4] = videodata->atoms.XdndActionCopy; // we only accept copying anyway

            X11_XSendEvent(display, xevent->xclient.معلومات.l[0], False, No_Event_ماسک, (XEvent *)&m);
            X11_XFlush(display);
        } وإلا إذا (xevent->xclient.پیغام_type == videodata->atoms.XdndDrop) {
            إذا (معلومات->xdnd_req == None) {
                // say again - not interested!
                SDL_zero(m);
                m.type = Client_پیغام;
                m.display = xevent->xclient.display;
                m.کړکۍ = xevent->xclient.معلومات.l[0];
                m.پیغام_type = videodata->atoms.Xdnd_پای_ته_رسېدلی;
                m.format = 32;
                m.معلومات.l[0] = معلومات->xwindow;
                m.معلومات.l[1] = 0;
                m.معلومات.l[2] = None; // fail!
                X11_XSendEvent(display, xevent->xclient.معلومات.l[0], False, No_Event_ماسک, (XEvent *)&m);
            } وإلا {
                // convert
                إذا (xdnd_نسخه >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, معلومات->xdnd_req, videodata->atoms.PRIMARY, معلومات->xwindow, xevent->xclient.معلومات.l[2]);
                } وإلا {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, معلومات->xdnd_req, videodata->atoms.PRIMARY, معلومات->xwindow, Current_وخت);
                }
            }
        } وإلا إذا ((xevent->xclient.پیغام_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.معلومات.l[0] == videodata->atoms._NET_WM_PING)) {
            کړکۍ_2 ریښه = Default_ریښه_کړکۍ(display);

#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.کړکۍ);
#د_که_پای
            xevent->xclient.کړکۍ = ریښه;
            X11_XSendEvent(display, ریښه, False, Substructure_Redirect_ماسک | Substructure_Notify_ماسک, xevent);
            اكسر;
        }

        وإلا إذا ((xevent->xclient.پیغام_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.معلومات.l[0] == videodata->atoms.WM_DELETE_کړکۍ)) {

#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.کړکۍ);
#د_که_پای
            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_CLOSE_REQUESTED, 0, 0);
            اكسر;
        } وإلا إذا ((xevent->xclient.پیغام_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.معلومات.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#که_تعریف_شوی DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", معلومات);
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(معلومات->کړکۍ, &xevent->xclient);
#د_که_پای /* SDL_VIDEO_DRIVER_X11_XSYNC */
            اكسر;
        }
    } اكسر;

        // Do we need to refresh ourselves?
    حالة Expose:
    {
#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.کړکۍ, xevent->xexpose.شمېر);
#د_که_پای
        SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_EXPOSED, 0, 0);
    } اكسر;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    حالة کلی_Press:
    حالة کلی_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        إذا (معلومات->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            اكسر;
        } وإلا إذا (xevent->xkey.serial == videodata->xinput_وروستی_کلی_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_وروستی_keyboard_device;
        }

        X11_Handle_کلی_Event(_this, معلومات, keyboardID, xevent);
    } اكسر;

    حالة MotionNotify:
    {
        إذا (X11_Xinput2_Handles_Motion_For_کړکۍ(معلومات)) {
            // This input is being handled by XInput2
            اكسر;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        إذا (!mouse->relative_ډېرپېښ) {
#که_تعریف_شوی DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.کړکۍ, xevent->xmotion.x, xevent->xmotion.y);
#د_که_پای

            X11_Process_موندنه_Test(_this, معلومات, (عائم)xevent->xmotion.x, (عائم)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, معلومات->کړکۍ, SDL_GLOBAL_MOUSE_ID, false, (عائم)xevent->xmotion.x, (عائم)xevent->xmotion.y);
        }
    } اكسر;

    حالة ButtonPress:
    {
        إذا (معلومات->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_وروستی_button_serial) {
            // This input event was handled by XInput2.
            اكسر;
        }

        X11_HandleButtonPress(_this, معلومات, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.وخت, xevent->xbutton.serial);
    } اكسر;

    حالة ButtonRelease:
    {
        إذا (معلومات->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_وروستی_button_serial) {
            // This input event was handled by XInput2.
            اكسر;
        }

        X11_HandleButtonRelease(_this, معلومات, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.وخت);
    } اكسر;

    حالة PropertyNotify:
    {
#که_تعریف_شوی DEBUG_XEVENTS
        بینښه حرف *propdata;
        صحيح حالت, real_format;
        Atom real_type;
        بینښه اوږد توکي_read, توکي_کیڼ;

        حرف *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        إذا (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.کړکۍ, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.وخت);
            X11_XFree(name);
        }

        حالت = X11_XGet_کړکۍ_Property(display, معلومات->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &توکي_read, &توکي_کیڼ, &propdata);
        إذا (حالت == Success && توکي_read > 0) {
            إذا (real_type == XA_INTEGER) {
                صحيح *ارزښتونه = (صحيح *)propdata;

                SDL_Log("{");
                لكل (i = 0; i < توکي_read; i++) {
                    SDL_Log(" %d", ارزښتونه[i]);
                }
                SDL_Log(" }");
            } وإلا إذا (real_type == XA_CARDINAL) {
                إذا (real_format == 32) {
                    Uint32 *ارزښتونه = (Uint32 *)propdata;

                    SDL_Log("{");
                    لكل (i = 0; i < توکي_read; i++) {
                        SDL_Log(" %d", ارزښتونه[i]);
                    }
                    SDL_Log(" }");
                } وإلا إذا (real_format == 16) {
                    Uint16 *ارزښتونه = (Uint16 *)propdata;

                    SDL_Log("{");
                    لكل (i = 0; i < توکي_read; i++) {
                        SDL_Log(" %d", ارزښتونه[i]);
                    }
                    SDL_Log(" }");
                } وإلا إذا (real_format == 8) {
                    Uint8 *ارزښتونه = (Uint8 *)propdata;

                    SDL_Log("{");
                    لكل (i = 0; i < توکي_read; i++) {
                        SDL_Log(" %d", ارزښتونه[i]);
                    }
                    SDL_Log(" }");
                }
            } وإلا إذا (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } وإلا إذا (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                لكل (i = 0; i < توکي_read; i++) {
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
#د_که_پای // DEBUG_XEVENTS

        /* Take advantage of this moment to make sure user_time has a
            valid timestamp from the X server, so if we later try to
            raise/restore this window, _NET_ACTIVE_WINDOW can have a
            non-zero timestamp, even if there's never been a mouse or
            key press to this window so far. Note that we don't try to
            set _NET_WM_USER_TIME here, though. That's only for legit
            user interaction with the window. */
        إذا (!معلومات->user_وخت) {
            معلومات->user_وخت = xevent->xproperty.وخت;
        }

        إذا (xevent->xproperty.atom == معلومات->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            ثابت SDL_کړکۍ_Flags flags = X11_GetNetWMState(_this, معلومات->کړکۍ, xevent->xproperty.کړکۍ);
            ثابت SDL_کړکۍ_Flags بدل_شوی = flags ^ معلومات->کړکۍ->flags;

            إذا ((بدل_شوی & SDL_کړکۍ_HIDDEN) && !(flags & SDL_کړکۍ_HIDDEN)) {
                X11_DispatchMapNotify(معلومات);
            }

            إذا (!SDL_کړکۍ_IS_POPUP(معلومات->کړکۍ)) {
                إذا (بدل_شوی & SDL_کړکۍ_FULLSCREEN) {
                    معلومات->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    إذا (flags & SDL_کړکۍ_FULLSCREEN) {
                        إذا (!(flags & SDL_کړکۍ_MINIMIZED)) {
                            ثابت bool commit = SDL_memcmp(&معلومات->کړکۍ->current_fullscreen_ډېرپېښ, &معلومات->requested_fullscreen_ډېرپېښ, حجم(SDL_Display_ډېرپېښ)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_RESTORED, 0, 0);
                            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_ENTER_FULLSCREEN, 0, 0);
                            إذا (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&معلومات->کړکۍ->current_fullscreen_ډېرپېښ, &معلومات->کړکۍ->requested_fullscreen_ډېرپېښ);
                                SDL_Update_Fullscreen_ډېرپېښ(معلومات->کړکۍ, SDL_FULLSCREEN_OP_UPDATE, true);
                            } وإلا {
                                SDL_Update_Fullscreen_ډېرپېښ(معلومات->کړکۍ, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } وإلا {
                        SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_LEAVE_FULLSCREEN, 0, 0);
                        SDL_Update_Fullscreen_ډېرپېښ(معلومات->کړکۍ, false, false);

                        SDL_zero(معلومات->requested_fullscreen_ډېرپېښ);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_سېټ_کړکۍ_Min_Max(معلومات->کړکۍ, !!(flags & SDL_کړکۍ_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        إذا (معلومات->fullscreen_borders_forced_on) {
                            معلومات->toggle_borders = true;
                            معلومات->fullscreen_borders_forced_on = false;
                        }
                    }

                    إذا ((flags & SDL_کړکۍ_FULLSCREEN) &&
                        (معلومات->border_سر || معلومات->border_کیڼ || معلومات->border_bottom || معلومات->border_ښی)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        معلومات->اندازه_move_event_flags |= X11_اندازه_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        معلومات->پخوانی_borders_nonzero = true;
                    } وإلا إذا (!(flags & SDL_کړکۍ_FULLSCREEN) &&
                               معلومات->پخوانی_borders_nonzero &&
                               (!معلومات->border_سر && !معلومات->border_کیڼ && !معلومات->border_bottom && !معلومات->border_ښی)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        معلومات->اندازه_move_event_flags |= X11_اندازه_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        معلومات->پخوانی_borders_nonzero = false;
                    } وإلا {
                        معلومات->اندازه_move_event_flags = 0;
                        معلومات->پخوانی_borders_nonzero = false;

                        إذا (!(معلومات->کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) && معلومات->toggle_borders) {
                            معلومات->toggle_borders = false;
                            X11_سېټ_کړکۍ_Bordered(_this, معلومات->کړکۍ, !(معلومات->کړکۍ->flags & SDL_کړکۍ_BORDERLESS));
                        }
                    }
                }
                إذا ((بدل_شوی & SDL_کړکۍ_MAXIMIZED) && ((flags & SDL_کړکۍ_MAXIMIZED) && !(flags & SDL_کړکۍ_MINIMIZED))) {
                    معلومات->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    إذا ((بدل_شوی & SDL_کړکۍ_MINIMIZED)) {
                        معلومات->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_RESTORED, 0, 0);
                    }
                    SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_MAXIMIZED, 0, 0);
                }
                إذا ((بدل_شوی & SDL_کړکۍ_MINIMIZED) && (flags & SDL_کړکۍ_MINIMIZED)) {
                    معلومات->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_MINIMIZED, 0, 0);
                }
                إذا (!(flags & (SDL_کړکۍ_MAXIMIZED | SDL_کړکۍ_MINIMIZED))) {
                    معلومات->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    إذا (!(flags & SDL_کړکۍ_FULLSCREEN)) {
                        إذا (معلومات->pending_position) {
                            معلومات->pending_position = false;
                            معلومات->pending_operation |= X11_PENDING_OP_MOVE;
                            معلومات->expected.x = معلومات->کړکۍ->pending.x - معلومات->border_کیڼ;
                            معلومات->expected.y = معلومات->کړکۍ->pending.y - معلومات->border_سر;
                            X11_XMove_کړکۍ(display, معلومات->xwindow, معلومات->expected.x, معلومات->expected.y);
                        }
                        إذا (معلومات->pending_اندازه) {
                            معلومات->pending_اندازه = false;
                            معلومات->pending_operation |= X11_PENDING_OP_RESIZE;
                            معلومات->expected.w = معلومات->کړکۍ->pending.w;
                            معلومات->expected.h = معلومات->کړکۍ->pending.h;
                            X11_XResize_کړکۍ(display, معلومات->xwindow, معلومات->کړکۍ->pending.w, معلومات->کړکۍ->pending.h);
                        }
                    }
                }
                إذا (معلومات->emit_اندازه_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(معلومات, &معلومات->pending_xconfigure);
                    معلومات->emit_اندازه_move_after_property_notify = false;
                }
                إذا ((flags & SDL_کړکۍ_ننوت_FOCUS)) {
                    إذا (معلومات->pending_move) {
                        Dispatch_کړکۍ_Move(_this, معلومات, &معلومات->pending_move_ټکی);
                        معلومات->pending_move = false;
                    }
                }
            }
            إذا (بدل_شوی & SDL_کړکۍ_OCCLUDED) {
                SDL_Send_کړکۍ_Event(معلومات->کړکۍ, (flags & SDL_کړکۍ_OCCLUDED) ? SDL_EVENT_کړکۍ_OCCLUDED : SDL_EVENT_کړکۍ_EXPOSED, 0, 0);
            }
        } وإلا إذا (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            صحيح format;
            بینښه اوږد nitems, بایټونه_after;
            بینښه حرف *prop_معلومات = عدم;

            إذا (X11_XGet_کړکۍ_Property(display, معلومات->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &بایټونه_after, &prop_معلومات) == Success) {
                إذا (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_معلومات;

                    إذا ((state == 0 || state == 3) && !معلومات->کړکۍ->is_hiding && !(معلومات->کړکۍ->flags & SDL_کړکۍ_HIDDEN)) {
                        // Withdrawn or Iconic
                        إذا (!(معلومات->کړکۍ->flags & SDL_کړکۍ_MINIMIZED)) {
                            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_MINIMIZED, 0, 0);
                            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_OCCLUDED, 0, 0);
                        }
                    } وإلا إذا (state == 1) { // NormalState
                        إذا (معلومات->کړکۍ->flags & SDL_کړکۍ_MINIMIZED) {
                            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_RESTORED, 0, 0);
                            SDL_Send_کړکۍ_Event(معلومات->کړکۍ, SDL_EVENT_کړکۍ_EXPOSED, 0, 0);
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
        } وإلا إذا (xevent->xproperty.atom == videodata->atoms.NET_چوکاټ_EXTENTS) {
            X11_Get_Border_ارزښتونه(معلومات);
            إذا (معلومات->اندازه_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                معلومات->اندازه_move_event_flags &= ~X11_اندازه_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            إذا (!(معلومات->کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) && معلومات->toggle_borders) {
                معلومات->toggle_borders = false;
                X11_سېټ_کړکۍ_Bordered(_this, معلومات->کړکۍ, !(معلومات->کړکۍ->flags & SDL_کړکۍ_BORDERLESS));
            }
        }
    } اكسر;

    حالة SelectionNotify:
    {
        Atom موخه = xevent->xselection.موخه;
#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.کړکۍ,
               xevent->xselection.requestor, xevent->xselection.موخه);
#د_که_پای
        إذا (موخه == معلومات->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, معلومات->xwindow, videodata->atoms.PRIMARY);

            إذا (p.format == 8) {
                حرف *saveptr = عدم;
                حرف *name = X11_XGetAtomName(display, موخه);
                إذا (name) {
                    حرف *token = SDL_strtok_r((حرف *)p.معلومات, "\r\n", &saveptr);
                    طالما (token) {
                        إذا ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_Send_Drop_متن(معلومات->کړکۍ, token);
                        } وإلا إذا (SDL_strcmp("text/uri-list", name) == 0) {
                            إذا (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(معلومات->کړکۍ, عدم, token);
                            }
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    X11_XFree(name);
                }
                SDL_SendDropComplete(معلومات->کړکۍ);
            }
            X11_XFree(p.معلومات);

            // send reply
            SDL_zero(m);
            m.type = Client_پیغام;
            m.display = display;
            m.کړکۍ = معلومات->xdnd_سرچینه;
            m.پیغام_type = videodata->atoms.Xdnd_پای_ته_رسېدلی;
            m.format = 32;
            m.معلومات.l[0] = معلومات->xwindow;
            m.معلومات.l[1] = 1;
            m.معلومات.l[2] = videodata->atoms.XdndActionCopy;
            X11_XSendEvent(display, معلومات->xdnd_سرچینه, False, No_Event_ماسک, (XEvent *)&m);

            X11_XSync(display, False);
        }
    } اكسر;

    افتراضي:
    {
#که_تعریف_شوی DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.کړکۍ, xevent->type);
#د_که_پای
    } اكسر;
    }
}

ساكن فراغ X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    صحيح i;

    إذا (videodata && videodata->windowlist) {
        لكل (i = 0; i < videodata->numwindows; ++i) {
            SDL_کړکۍ_معلومات *معلومات = videodata->windowlist[i];
            إذا (معلومات && معلومات->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                إذا (now >= معلومات->pending_focus_وخت) {
                    إذا (معلومات->pending_focus == PENDING_FOCUS_دننه) {
                        X11_Dispatch_Focus_دننه(_this, معلومات);
                    } وإلا {
                        X11_Dispatch_Focus_بهر(_this, معلومات);
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

فراغ X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *معلومات = _this->دننی;
    Display *req_display = معلومات->request_display;
    کړکۍ_2 xwindow = کړکۍ->دننی->xwindow;
    XClient_پیغام_Event event;

    SDL_zero(event);
    event.type = Client_پیغام;
    event.display = req_display;
    event.send_event = True;
    event.پیغام_type = معلومات->atoms._SDL_WAKEUP;
    event.format = 8;

    X11_XSendEvent(req_display, xwindow, False, No_Event_ماسک, (XEvent *)&event);
    /* XSendEvent returns a status and it could be BadValue or BadWindow. If an
      error happens it is an SDL's internal error and there is nothing we can do here. */
    X11_XFlush(req_display);
}

صحيح X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_معلومات *videodata = _this->دننی;
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
        صحيح err = SDL_IOReady(Connection_شمېره(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
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
    SDL_Video_معلومات *معلومات = _this->دننی;
    XEvent xevent;
    صحيح i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    لكل (i = 0; i < _this->عدد_displays; ++i) {
        إذا (_this->displays[i]->دننی->ډېرپېښ_switch_deadline_ns) {
            إذا (_this->displays[i]->fullscreen_کړکۍ) {
                _this->displays[i]->دننی->ډېرپېښ_switch_deadline_ns = 0;
            } وإلا إذا (SDL_GetTicksNS() >= _this->displays[i]->دننی->ډېرپېښ_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_سېټ_Display_ډېرپېښ_For_Display(_this->displays[i], عدم);
                _this->displays[i]->دننی->ډېرپېښ_switch_deadline_ns = 0;
            }
        }
    }

    إذا (معلومات->وروستی_ډېرپېښ_change_deadline) {
        إذا (SDL_GetTicks() >= معلومات->وروستی_ډېرپېښ_change_deadline) {
            معلومات->وروستی_ډېرپېښ_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    إذا (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        إذا (!معلومات->screensaver_activity || now >= (معلومات->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(معلومات->display);

#که_تعریف_شوی SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#د_که_پای

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
            معلومات->windowlist[i]->flash_cancel_وخت &&
            SDL_GetTicks() >= معلومات->windowlist[i]->flash_cancel_وخت) {
            X11_Flash_کړکۍ(_this, معلومات->windowlist[i]->کړکۍ, SDL_FLASH_CANCEL);
        }
    }

    إذا (معلومات->xinput_hierarchy_بدل_شوی) {
        X11_Xinput2UpdateDevices(_this);
        معلومات->xinput_hierarchy_بدل_شوی = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_Video_معلومات *معلومات = _this->دننی;
    صحيح dummy;
    صحيح major_نسخه, minor_نسخه;
#د_که_پای // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#که_تعریف_شوی SDL_USE_LIBDBUS
    إذا (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        أرجع true;
    }

    إذا (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#د_که_پای

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    إذا (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        إذا (!X11_XScreenSaverQueryExtension(معلومات->display, &dummy, &dummy) ||
            !X11_XScreen_Saver_Query_نسخه(معلومات->display,
                                          &major_نسخه, &minor_نسخه) ||
            major_نسخه < 1 || (major_نسخه == 1 && minor_نسخه < 1)) {
            أرجع SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(معلومات->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(معلومات->display);
        أرجع true;
    }
#د_که_پای
    أرجع SDL_Unsupported();
}

#د_که_پای // SDL_VIDEO_DRIVER_X11
