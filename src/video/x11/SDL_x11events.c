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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ <sys/types.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/time.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <signal.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h> // For INT_MAX

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11pen.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11touch.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xinput2.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xfixes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11settings.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_clipboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xsync.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/unix/SDL_poll.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_touch_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_system_theme.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਜੇ 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEBUG_XEVENTS
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NET_WM_MOVERESIZE_ਮਾਪ_TOPLEFT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NET_WM_MOVERESIZE_ਮਾਪ_TOPLEFT 0
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NET_WM_MOVERESIZE_ਮਾਪ_ਸਿਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NET_WM_MOVERESIZE_ਮਾਪ_ਸਿਖਰ 1
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NET_WM_MOVERESIZE_ਮਾਪ_TOPRIGHT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NET_WM_MOVERESIZE_ਮਾਪ_TOPRIGHT 2
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NET_WM_MOVERESIZE_ਮਾਪ_ਸੱਜਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NET_WM_MOVERESIZE_ਮਾਪ_ਸੱਜਾ 3
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NET_WM_MOVERESIZE_ਮਾਪ_BOTTOMRIGHT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NET_WM_MOVERESIZE_ਮਾਪ_BOTTOMRIGHT 4
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NET_WM_MOVERESIZE_ਮਾਪ_BOTTOM
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NET_WM_MOVERESIZE_ਮਾਪ_BOTTOM 5
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NET_WM_MOVERESIZE_ਮਾਪ_BOTTOMLEFT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NET_WM_MOVERESIZE_ਮਾਪ_BOTTOMLEFT 6
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NET_WM_MOVERESIZE_ਮਾਪ_ਖੱਬਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NET_WM_MOVERESIZE_ਮਾਪ_ਖੱਬਾ 7
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ _NET_WM_MOVERESIZE_MOVE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ _NET_WM_MOVERESIZE_MOVE 8
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਅੰਕੜੇ;
    ਪੂਰਨ format, ਗਿਣਤੀ_2;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ਸਥਿਰ ਖਾਲੀ X11_ReadProperty(SDL_x11Prop *p, Display *disp, ਖਿੜਕੀ_2 w, Atom prop)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ret = ਨਿਰਾ;
    Atom type;
    ਪੂਰਨ fmt;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਗਿਣਤੀ_2;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਬਾਈਟਾਂ_ਖੱਬਾ;
    ਪੂਰਨ ਬਾਈਟਾਂ_fetch = 0;

    ਕਰੋ {
        ਜੇ (ret) {
            X11_XFree(ret);
        }
        X11_XGet_ਖਿੜਕੀ_Property(disp, w, prop, 0, ਬਾਈਟਾਂ_fetch, False, AnyPropertyType, &type, &fmt, &ਗਿਣਤੀ_2, &ਬਾਈਟਾਂ_ਖੱਬਾ, &ret);
        ਬਾਈਟਾਂ_fetch += ਬਾਈਟਾਂ_ਖੱਬਾ;
    } ਜਦੋਂ (ਬਾਈਟਾਂ_ਖੱਬਾ != 0);

    p->ਅੰਕੜੇ = ret;
    p->format = fmt;
    p->ਗਿਣਤੀ_2 = ਗਿਣਤੀ_2;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
ਸਥਿਰ Atom X11_Pick_ਨਿਸ਼ਾਨਾ(Display *disp, Atom list[], ਪੂਰਨ list_ਗਿਣਤੀ)
{
    ਅਚਲ Atom ਪਾਠ_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    ਲਈ (ਪੂਰਨ i = 0; i < list_ਗਿਣਤੀ && request != ਪਾਠ_uri_request; i++) {
        ਅੱਖਰ *name = X11_XGetAtomName(disp, list[i]);
        // Preferred MIME targets
        ਜੇ ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            ਜੇ (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        ਜੇ ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            ਜੇ (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    ਜੇ (preferred != None && request != ਪਾਠ_uri_request) {
        request = preferred;
    }
    ਵਾਪਸ request;
}

/* Wrapper for X11_PickTarget for a maximum of three targets, a special
   case in the Xdnd protocol */
ਸਥਿਰ Atom X11_Pick_ਨਿਸ਼ਾਨਾ_From_Atoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    ਪੂਰਨ ਗਿਣਤੀ_2 = 0;
    Atom atom[3];
    ਜੇ (a0 != None) {
        atom[ਗਿਣਤੀ_2++] = a0;
    }
    ਜੇ (a1 != None) {
        atom[ਗਿਣਤੀ_2++] = a1;
    }
    ਜੇ (a2 != None) {
        atom[ਗਿਣਤੀ_2++] = a2;
    }
    ਵਾਪਸ X11_Pick_ਨਿਸ਼ਾਨਾ(disp, atom, ਗਿਣਤੀ_2);
}

ਬਣਤਰ ਕੁੰਜੀ_Repeat_Check_ਅੰਕੜੇ
{
    XEvent *event;
    bool ਮਿਲਿਆ;
};

ਸਥਿਰ Bool X11_ਕੁੰਜੀ_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    ਬਣਤਰ ਕੁੰਜੀ_Repeat_Check_ਅੰਕੜੇ *d = (ਬਣਤਰ ਕੁੰਜੀ_Repeat_Check_ਅੰਕੜੇ *)arg;
    ਜੇ (chkev->type == ਕੁੰਜੀ_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.ਸਮਾਂ - d->event->xkey.ਸਮਾਂ < 2) {
        d->ਮਿਲਿਆ = true;
    }
    ਵਾਪਸ False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
ਸਥਿਰ bool X11_ਕੁੰਜੀ_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    ਬਣਤਰ ਕੁੰਜੀ_Repeat_Check_ਅੰਕੜੇ d;
    d.event = event;
    d.ਮਿਲਿਆ = false;
    ਜੇ (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_ਕੁੰਜੀ_Repeat_Check_If_Event, (XPointer)&d);
    }
    ਵਾਪਸ d.ਮਿਲਿਆ;
}

bool X11_IsWheelEvent(ਪੂਰਨ button, ਪੂਰਨ *xticks, ਪੂਰਨ *yticks)
{
    /* according to the xlib docs, no specific mouse wheel events exist.
       However, the defacto standard is that the vertical wheel is X buttons
       4 (up) and 5 (down) and a horizontal wheel is 6 (left) and 7 (right). */

    // Xlib defines "Button1" through 5, so we just use literals here.
    ਚੋਣ (button) {
    ਹਾਲਤ 4:
        *yticks = 1;
        ਵਾਪਸ true;
    ਹਾਲਤ 5:
        *yticks = -1;
        ਵਾਪਸ true;
    ਹਾਲਤ 6:
        *xticks = 1;
        ਵਾਪਸ true;
    ਹਾਲਤ 7:
        *xticks = -1;
        ਵਾਪਸ true;
    ਮੂਲ:
        ਰੋਕੋ;
    }
    ਵਾਪਸ false;
}

// An X11 event hook
ਸਥਿਰ SDL_X11EventHook g_X11EventHook = ਨਿਰਾ;
ਸਥਿਰ ਖਾਲੀ *g_X11_Event_Hook_ਅੰਕੜੇ = ਨਿਰਾ;

ਖਾਲੀ SDL_ਸੈੱਟ_X11_Event_Hook(SDL_X11EventHook callback, ਖਾਲੀ *userdata)
{
    g_X11EventHook = callback;
    g_X11_Event_Hook_ਅੰਕੜੇ = userdata;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
ਸਥਿਰ ਖਾਲੀ X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    ਜੇ (X11_XGet_Event_ਅੰਕੜੇ(videodata->display, cookie)) {
        ਜੇ (!g_X11EventHook || g_X11EventHook(g_X11_Event_Hook_ਅੰਕੜੇ, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFree_Event_ਅੰਕੜੇ(videodata->display, cookie);
    }
}
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

ਸਥਿਰ ਖਾਲੀ X11_Update_System_ਕੁੰਜੀ_Modifiers(SDL_Video_ਅੰਕੜੇ *viddata)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ਜੇ (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        ਜੇ (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.ਅਧਾਰ_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        {
        ਖਿੜਕੀ_2 junk_ਖਿੜਕੀ;
        ਪੂਰਨ x, y;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ mod_ਨਕਾਬ;

        X11_XQuery_ਸੂਚਕ(viddata->display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(viddata->display), &junk_ਖਿੜਕੀ, &junk_ਖਿੜਕੀ, &x, &y, &x, &y, &mod_ਨਕਾਬ);
        viddata->keyboard.pressed_modifiers = mod_ਨਕਾਬ & (ਖਿਸਕਾਓ_ਨਕਾਬ_2 | Control_ਨਕਾਬ | Mod1_ਨਕਾਬ | Mod3_ਨਕਾਬ | Mod4_ਨਕਾਬ | Mod5_ਨਕਾਬ);
        viddata->keyboard.locked_modifiers = mod_ਨਕਾਬ & (ਤਾਲਾ_ਨਕਾਬ | viddata->keyboard.numlock_ਨਕਾਬ | viddata->keyboard.scrolllock_ਨਕਾਬ);
    }
}

ਸਥਿਰ ਖਾਲੀ X11_ReconcileModifiers(SDL_Video_ਅੰਕੜੇ *viddata, bool ਕੁੰਜੀ_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    ਜੇ (ਕੁੰਜੀ_pressed) {
        ਜੇ (viddata->keyboard.pressed_modifiers & ਖਿਸਕਾਓ_ਨਕਾਬ_2) {
            ਜੇ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ਖਿਸਕਾਓ) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ਖਿਸਕਾਓ;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ਖਿਸਕਾਓ);
            }
        }

        ਜੇ (viddata->keyboard.pressed_modifiers & Control_ਨਕਾਬ) {
            ਜੇ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        ਜੇ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_ਨਕਾਬ) {
            ਜੇ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        ਜੇ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_ਨਕਾਬ) {
            ਜੇ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (viddata->keyboard.pressed_modifiers & ਖਿਸਕਾਓ_ਨਕਾਬ_2) {
            ਜੇ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ਖਿਸਕਾਓ)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ਖਿਸਕਾਓ;
            }
        } ਨਹੀਂਤਾਂ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ਖਿਸਕਾਓ;
        }

        ਜੇ (viddata->keyboard.pressed_modifiers & Control_ਨਕਾਬ) {
            ਜੇ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } ਨਹੀਂਤਾਂ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        ਜੇ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_ਨਕਾਬ) {
            ਜੇ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } ਨਹੀਂਤਾਂ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        ਜੇ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_ਨਕਾਬ) {
            ਜੇ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } ਨਹੀਂਤਾਂ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        ਜੇ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_ਨਕਾਬ) {
            ਜੇ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ਬਹੁਲਕ)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ਬਹੁਲਕ;
            }
        } ਨਹੀਂਤਾਂ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ਬਹੁਲਕ;
        }

        ਜੇ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_ਨਕਾਬ) {
            ਜੇ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } ਨਹੀਂਤਾਂ {
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
    ਜੇ (viddata->keyboard.locked_modifiers & ਖਿਸਕਾਓ_ਨਕਾਬ_2) {
        ਜੇ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ਖਿਸਕਾਓ) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ਖਿਸਕਾਓ;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ਖਿਸਕਾਓ);
        } ਨਹੀਂਤਾਂ ਜੇ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ਖਿਸਕਾਓ)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ਖਿਸਕਾਓ;
        }
    } ਨਹੀਂਤਾਂ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ਖਿਸਕਾਓ;
    }

    ਜੇ (viddata->keyboard.locked_modifiers & Control_ਨਕਾਬ) {
        ਜੇ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } ਨਹੀਂਤਾਂ ਜੇ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } ਨਹੀਂਤਾਂ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    ਜੇ (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_ਨਕਾਬ) {
        ਜੇ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } ਨਹੀਂਤਾਂ ਜੇ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } ਨਹੀਂਤਾਂ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    ਜੇ (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_ਨਕਾਬ) {
        ਜੇ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } ਨਹੀਂਤਾਂ ਜੇ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } ਨਹੀਂਤਾਂ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    ਜੇ (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_ਨਕਾਬ) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ਬਹੁਲਕ;
    } ਨਹੀਂਤਾਂ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ਬਹੁਲਕ;
    }

    ਜੇ (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_ਨਕਾਬ) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } ਨਹੀਂਤਾਂ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    ਜੇ (viddata->keyboard.locked_modifiers & ਤਾਲਾ_ਨਕਾਬ) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } ਨਹੀਂਤਾਂ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    ਜੇ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_ਨਕਾਬ) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ਅੰਕ;
    } ਨਹੀਂਤਾਂ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ਅੰਕ;
    }

    ਜੇ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_ਨਕਾਬ) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } ਨਹੀਂਤਾਂ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_ਸੈੱਟ_Mod_State(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

ਸਥਿਰ ਖਾਲੀ X11_Handle_Modifier_ਕੁੰਜੀਆਂ(SDL_Video_ਅੰਕੜੇ *viddata, SDL_Scancode scancode, bool pressed)
{
    ਅਚਲ SDL_Keycode keycode = SDL_Get_ਕੁੰਜੀ_From_Scancode(scancode, SDL_KMOD_NONE, false);
    SDL_Keymod mod = SDL_KMOD_NONE;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is checked.
     */
    ਚੋਣ (keycode) {
    ਹਾਲਤ SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_LALT:
        mod = SDL_KMOD_LALT;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_RALT:
        mod = SDL_KMOD_RALT;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_ਬਹੁਲਕ:
        mod = SDL_KMOD_ਬਹੁਲਕ;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_LEVEL5_ਖਿਸਕਾਓ:
        mod = SDL_KMOD_LEVEL5;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_CAPSLOCK:
    ਹਾਲਤ SDLK_NUMLOCKCLEAR:
    ਹਾਲਤ SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        ਜੇ (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ cur_ਨਕਾਬ = viddata->keyboard.locked_modifiers;
            X11_Update_System_ਕੁੰਜੀ_Modifiers(viddata);

            ਜੇ (viddata->keyboard.locked_modifiers & ਤਾਲਾ_ਨਕਾਬ) {
                cur_ਨਕਾਬ |= ਤਾਲਾ_ਨਕਾਬ;
            } ਨਹੀਂਤਾਂ {
                cur_ਨਕਾਬ &= ~ਤਾਲਾ_ਨਕਾਬ;
            }
            ਜੇ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_ਨਕਾਬ) {
                cur_ਨਕਾਬ |= viddata->keyboard.numlock_ਨਕਾਬ;
            } ਨਹੀਂਤਾਂ {
                cur_ਨਕਾਬ &= ~viddata->keyboard.numlock_ਨਕਾਬ;
            }
            ਜੇ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_ਨਕਾਬ) {
                cur_ਨਕਾਬ |= viddata->keyboard.scrolllock_ਨਕਾਬ;
            } ਨਹੀਂਤਾਂ {
                cur_ਨਕਾਬ &= ~viddata->keyboard.scrolllock_ਨਕਾਬ;
            }

            viddata->keyboard.locked_modifiers = cur_ਨਕਾਬ;
        }
    } ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ;
    }

    ਜੇ (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } ਨਹੀਂਤਾਂ {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

ਖਾਲੀ X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    Display *display = videodata->display;
    ਅੱਖਰ ਕੁੰਜੀਆਂ[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_ਕੁੰਜੀ_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_ਅੰਕ | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= ਤਾਲਾ_ਨਕਾਬ | videodata->keyboard.numlock_ਨਕਾਬ| videodata->keyboard.scrolllock_ਨਕਾਬ;

    X11_XQueryKeymap(display, ਕੁੰਜੀਆਂ);

    ਅਚਲ bool *keystate = SDL_GetKeyboardState(ਨਿਰਾ);
    ਲਈ (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.ਕੁੰਜੀ_layout); ++keycode) {
        ਅਚਲ SDL_Scancode scancode = videodata->keyboard.ਕੁੰਜੀ_layout[keycode];
        ਅਚਲ bool x11_ਕੁੰਜੀ_Pressed = (ਕੁੰਜੀਆਂ[keycode / 8] & (1 << (keycode % 8))) != 0;
        ਅਚਲ bool sdl_ਕੁੰਜੀ_Pressed = keystate[scancode];

        ਜੇ (x11_ਕੁੰਜੀ_Pressed && !sdl_ਕੁੰਜੀ_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            ਚੋਣ (SDL_Get_ਕੁੰਜੀ_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            ਹਾਲਤ SDLK_LCTRL:
            ਹਾਲਤ SDLK_RCTRL:
            ਹਾਲਤ SDLK_LSHIFT:
            ਹਾਲਤ SDLK_RSHIFT:
            ਹਾਲਤ SDLK_LALT:
            ਹਾਲਤ SDLK_RALT:
            ਹਾਲਤ SDLK_LGUI:
            ਹਾਲਤ SDLK_RGUI:
            ਹਾਲਤ SDLK_ਬਹੁਲਕ:
            ਹਾਲਤ SDLK_LEVEL5_ਖਿਸਕਾਓ:
                X11_Handle_Modifier_ਕੁੰਜੀਆਂ(videodata, scancode, true);
                SDL_Send_Keyboard_ਕੁੰਜੀ_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                ਰੋਕੋ;
            ਮੂਲ:
                ਰੋਕੋ;
            }
        } ਨਹੀਂਤਾਂ ਜੇ (!x11_ਕੁੰਜੀ_Pressed && sdl_ਕੁੰਜੀ_Pressed) {
            X11_Handle_Modifier_ਕੁੰਜੀਆਂ(videodata, scancode, false);
            SDL_Send_Keyboard_ਕੁੰਜੀ_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_ਕੁੰਜੀ_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

ਸਥਿਰ ਖਾਲੀ X11_Dispatch_Focus_ਵਿੱਚ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", ਅੰਕੜੇ->xwindow);
#ਜੇ_ਅੰਤ
    SDL_ਸੈੱਟ_Keyboard_Focus(ਅੰਕੜੇ->ਖਿੜਕੀ);
    X11_ReconcileKeyboardState(_this);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    ਜੇ (ਅੰਕੜੇ->ic) {
        X11_XSetICFocus(ਅੰਕੜੇ->ic);
    }
#ਜੇ_ਅੰਤ
    ਜੇ (ਅੰਕੜੇ->flashing_ਖਿੜਕੀ) {
        X11_Flash_ਖਿੜਕੀ(_this, ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_FLASH_CANCEL);
    }
}

ਸਥਿਰ ਖਾਲੀ X11_Dispatch_Focus_ਬਾਹਰਲਾ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", ਅੰਕੜੇ->xwindow);
#ਜੇ_ਅੰਤ
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ == SDL_GetKeyboardFocus()) {
        SDL_ਸੈੱਟ_Keyboard_Focus(ਨਿਰਾ);
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    ਜੇ (ਅੰਕੜੇ->ic) {
        X11_XUnsetICFocus(ਅੰਕੜੇ->ic);
    }
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਖਾਲੀ X11_DispatchMapNotify(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਅੰਕੜੇ->ਖਿੜਕੀ;

    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_SHOWN, 0, 0);
    ਅੰਕੜੇ->was_shown = true;

    // This may be sent when restoring a minimized window.
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED) {
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESTORED, 0, 0);
        SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_EXPOSED, 0, 0);
    }

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS) {
        SDL_Update_ਖਿੜਕੀ_Grab(ਖਿੜਕੀ);
    }
}

ਸਥਿਰ ਖਾਲੀ X11_DispatchUnmapNotify(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਅੰਕੜੇ->ਖਿੜਕੀ;

    // This may be sent when minimizing a window.
    ਜੇ (!ਖਿੜਕੀ->is_hiding) {
        SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MINIMIZED, 0, 0);
        SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_OCCLUDED, 0, 0);
    } ਨਹੀਂਤਾਂ {
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_HIDDEN, 0, 0);
    }
}

ਸਥਿਰ ਖਾਲੀ Dispatch_ਖਿੜਕੀ_Move(SDL_VideoDevice *_this, ਅਚਲ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ, ਅਚਲ SDL_ਬਿੰਦੂ *ਬਿੰਦੂ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਅੰਕੜੇ->ਖਿੜਕੀ;
    Display *display = videodata->display;
    XEvent evt;

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_ਸੂਚਕ(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_ਸੁਨੇਹਾ;
    evt.xclient.ਖਿੜਕੀ = ਅੰਕੜੇ->xwindow;
    evt.xclient.ਸੁਨੇਹਾ_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.ਅੰਕੜੇ.l[0] = (size_t)ਖਿੜਕੀ->x + ਬਿੰਦੂ->x;
    evt.xclient.ਅੰਕੜੇ.l[1] = (size_t)ਖਿੜਕੀ->y + ਬਿੰਦੂ->y;
    evt.xclient.ਅੰਕੜੇ.l[2] = _NET_WM_MOVERESIZE_MOVE;
    evt.xclient.ਅੰਕੜੇ.l[3] = Button1;
    evt.xclient.ਅੰਕੜੇ.l[4] = 0;
    X11_XSendEvent(display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(display), False, Substructure_Redirect_ਨਕਾਬ | Substructure_Notify_ਨਕਾਬ, &evt);

    X11_XSync(display, 0);
}

ਸਥਿਰ ਖਾਲੀ ਸਮਾਂ_ਸਾਰਣੀ_ਖਿੜਕੀ_Move(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ, ਅਚਲ SDL_ਬਿੰਦੂ *ਬਿੰਦੂ)
{
    ਅੰਕੜੇ->pending_move = true;
    ਅੰਕੜੇ->pending_move_ਬਿੰਦੂ = *ਬਿੰਦੂ;
}

ਸਥਿਰ ਖਾਲੀ Initiate_ਖਿੜਕੀ_Resize(SDL_VideoDevice *_this, ਅਚਲ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ, ਅਚਲ SDL_ਬਿੰਦੂ *ਬਿੰਦੂ, ਪੂਰਨ direction)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਅੰਕੜੇ->ਖਿੜਕੀ;
    Display *display = videodata->display;
    XEvent evt;

    ਜੇ (direction < NET_WM_MOVERESIZE_ਮਾਪ_TOPLEFT || direction > NET_WM_MOVERESIZE_ਮਾਪ_ਖੱਬਾ) {
        ਵਾਪਸ;
    }

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_ਸੂਚਕ(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_ਸੁਨੇਹਾ;
    evt.xclient.ਖਿੜਕੀ = ਅੰਕੜੇ->xwindow;
    evt.xclient.ਸੁਨੇਹਾ_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.ਅੰਕੜੇ.l[0] = (size_t)ਖਿੜਕੀ->x + ਬਿੰਦੂ->x;
    evt.xclient.ਅੰਕੜੇ.l[1] = (size_t)ਖਿੜਕੀ->y + ਬਿੰਦੂ->y;
    evt.xclient.ਅੰਕੜੇ.l[2] = direction;
    evt.xclient.ਅੰਕੜੇ.l[3] = Button1;
    evt.xclient.ਅੰਕੜੇ.l[4] = 0;
    X11_XSendEvent(display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(display), False, Substructure_Redirect_ਨਕਾਬ | Substructure_Notify_ਨਕਾਬ, &evt);

    X11_XSync(display, 0);
}

bool X11_Process_ਪ੍ਰਾਪਤੀ_Test(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ, ਅਚਲ ਦਸ਼ਮਲਵ x, ਅਚਲ ਦਸ਼ਮਲਵ y, bool force_new_ਨਤੀਜਾ)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਅੰਕੜੇ->ਖਿੜਕੀ;
    ਜੇ (!ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test) ਵਾਪਸ false;
    ਅਚਲ SDL_ਬਿੰਦੂ ਬਿੰਦੂ = { (ਪੂਰਨ)x, (ਪੂਰਨ)y };
    SDL_ਪ੍ਰਾਪਤੀ_Test_ਨਤੀਜਾ rc = ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test(ਖਿੜਕੀ, &ਬਿੰਦੂ, ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test_ਅੰਕੜੇ);
    ਜੇ (!force_new_ਨਤੀਜਾ && rc == ਅੰਕੜੇ->ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ) {
        ਵਾਪਸ true;
    }
    X11_ਸੈੱਟ_ਪ੍ਰਾਪਤੀ_Test_Cursor(rc);
    ਅੰਕੜੇ->ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ = rc;
    ਵਾਪਸ true;
}

bool X11_Trigger_ਪ੍ਰਾਪਤੀ_Test_Action(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ, ਅਚਲ ਦਸ਼ਮਲਵ x, ਅਚਲ ਦਸ਼ਮਲਵ y)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਅੰਕੜੇ->ਖਿੜਕੀ;

    ਜੇ (ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test) {
        ਅਚਲ SDL_ਬਿੰਦੂ ਬਿੰਦੂ = { (ਪੂਰਨ)x, (ਪੂਰਨ)y };
        ਸਥਿਰ ਅਚਲ ਪੂਰਨ directions[] = {
            NET_WM_MOVERESIZE_ਮਾਪ_TOPLEFT, NET_WM_MOVERESIZE_ਮਾਪ_ਸਿਖਰ,
            NET_WM_MOVERESIZE_ਮਾਪ_TOPRIGHT, NET_WM_MOVERESIZE_ਮਾਪ_ਸੱਜਾ,
            NET_WM_MOVERESIZE_ਮਾਪ_BOTTOMRIGHT, NET_WM_MOVERESIZE_ਮਾਪ_BOTTOM,
            NET_WM_MOVERESIZE_ਮਾਪ_BOTTOMLEFT, NET_WM_MOVERESIZE_ਮਾਪ_ਖੱਬਾ
        };

        ਚੋਣ (ਅੰਕੜੇ->ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ) {
        ਹਾਲਤ SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS) {
                Dispatch_ਖਿੜਕੀ_Move(_this, ਅੰਕੜੇ, &ਬਿੰਦੂ);
            } ਨਹੀਂਤਾਂ {
                ਸਮਾਂ_ਸਾਰਣੀ_ਖਿੜਕੀ_Move(_this, ਅੰਕੜੇ, &ਬਿੰਦੂ);
            }
            ਵਾਪਸ true;

        ਹਾਲਤ SDL_HITTEST_RESIZE_TOPLEFT:
        ਹਾਲਤ SDL_HITTEST_RESIZE_ਸਿਖਰ:
        ਹਾਲਤ SDL_HITTEST_RESIZE_TOPRIGHT:
        ਹਾਲਤ SDL_HITTEST_RESIZE_ਸੱਜਾ:
        ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOM:
        ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOMLEFT:
        ਹਾਲਤ SDL_HITTEST_RESIZE_ਖੱਬਾ:
            Initiate_ਖਿੜਕੀ_Resize(_this, ਅੰਕੜੇ, &ਬਿੰਦੂ, directions[ਅੰਕੜੇ->ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ - SDL_HITTEST_RESIZE_TOPLEFT]);
            ਵਾਪਸ true;

        ਮੂਲ:
            ਵਾਪਸ false;
        }
    }

    ਵਾਪਸ false;
}

ਸਥਿਰ ਖਾਲੀ X11_Update_User_ਸਮਾਂ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ latest)
{
    ਜੇ (latest && (latest != ਅੰਕੜੇ->user_ਸਮਾਂ)) {
        SDL_Video_ਅੰਕੜੇ *videodata = ਅੰਕੜੇ->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, ਅੰਕੜੇ->xwindow, videodata->atoms.NET_WM_USER_ਸਮਾਂ,
                            XA_CARDINAL, 32, Prop_ਬਹੁਲਕ_Replace,
                            (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)&latest, 1);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", ਅੰਕੜੇ->xwindow, latest);
#ਜੇ_ਅੰਤ
        ਅੰਕੜੇ->user_ਸਮਾਂ = latest;
    }
}

ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ x11_ਆਖਰੀ_error;
ਸਥਿਰ ਪੂਰਨ Bad_ਖਿੜਕੀ_Error_Handler(Display *d, XErrorEvent *e)
{
    x11_ਆਖਰੀ_error = e->error_ਕੋਡ;

    // Ignore BadWindow in cases where it's not fatal.
    ਜੇ (e->error_ਕੋਡ != Bad_ਖਿੜਕੀ) {
        ਅੱਖਰ err_ਸੁਨੇਹਾ[128];
        X11_XGet_Error_ਪਾਠ(d, e->error_ਕੋਡ, err_ਸੁਨੇਹਾ, ਆਕਾਰ(err_ਸੁਨੇਹਾ));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_ਕੋਡ, err_ਸੁਨੇਹਾ, e->request_ਕੋਡ);
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ X11_HandleClipboardEvent(SDL_VideoDevice *_this, ਅਚਲ XEvent *xevent)
{
    ਪੂਰਨ i;
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_ਖਿੜਕੀ != None);
    SDL_assert(xevent->xany.ਖਿੜਕੀ == videodata->clipboard_ਖਿੜਕੀ);

    ਚੋਣ (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    ਹਾਲਤ SelectionRequest:
    {
        ਅਚਲ XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        ਪੂਰਨ mime_formats;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *seln_ਅੰਕੜੇ;
        size_t seln_ਲੰਮਾਈ = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_Clipboard_ਅੰਕੜੇ *clipboard;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        ਅੱਖਰ *atom_name;
        atom_name = X11_XGetAtomName(display, req->ਨਿਸ਼ਾਨਾ);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->ਨਿਸ਼ਾਨਾ, atom_name);
        ਜੇ (atom_name) {
            X11_XFree(atom_name);
        }
#ਜੇ_ਅੰਤ

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_ਆਖਰੀ_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_ਖਿੜਕੀ_Error_Handler);

        ਜੇ (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ਨਹੀਂਤਾਂ {
            clipboard = &videodata->clipboard;
        }

        SDL_zero(sevent);
        sevent.xany.type = SelectionNotify;
        sevent.xselection.selection = req->selection;
        sevent.xselection.ਨਿਸ਼ਾਨਾ = None;
        sevent.xselection.property = None; // tell them no by default
        sevent.xselection.requestor = req->requestor;
        sevent.xselection.ਸਮਾਂ = req->ਸਮਾਂ;

        /* !!! FIXME: We were probably storing this on the root window
           because an SDL window might go away...? but we don't have to do
           this now (or ever, really). */

        ਜੇ (req->ਨਿਸ਼ਾਨਾ == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_ਗਿਣਤੀ + 1) * ਆਕਾਰ(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            ਲਈ (i = 0; i < clipboard->mime_ਗਿਣਤੀ; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, Prop_ਬਹੁਲਕ_Replace,
                                (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.ਨਿਸ਼ਾਨਾ = XA_TARGETS;
            SDL_free(supportedFormats);
        } ਨਹੀਂਤਾਂ {
            ਜੇ (clipboard->callback) {
                ਲਈ (i = 0; i < clipboard->mime_ਗਿਣਤੀ; ++i) {
                    ਅਚਲ ਅੱਖਰ *mime_type = clipboard->mime_types[i];
                    ਜੇ (X11_XInternAtom(display, mime_type, False) != req->ਨਿਸ਼ਾਨਾ) {
                        ਜਾਰੀ;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_ਅੰਕੜੇ = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)clipboard->callback(clipboard->userdata, mime_type, &seln_ਲੰਮਾਈ);
                    ਜੇ (seln_ਅੰਕੜੇ) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->ਨਿਸ਼ਾਨਾ, 8, Prop_ਬਹੁਲਕ_Replace,
                                            seln_ਅੰਕੜੇ, seln_ਲੰਮਾਈ);
                        sevent.xselection.property = req->property;
                        sevent.xselection.ਨਿਸ਼ਾਨਾ = req->ਨਿਸ਼ਾਨਾ;
                    }
                    ਰੋਕੋ;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(prev_handler);
    } ਰੋਕੋ;

    ਹਾਲਤ SelectionNotify:
    {
        ਅਚਲ XSelectionEvent *xsel = &xevent->xselection;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        ਅਚਲ ਅੱਖਰ *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        ਅਚਲ ਅੱਖਰ *ਨਿਸ਼ਾਨਾ_Name = xsel->ਨਿਸ਼ਾਨਾ ? X11_XGetAtomName(display, xsel->ਨਿਸ਼ਾਨਾ) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, ਨਿਸ਼ਾਨਾ_Name, propName);
#ਜੇ_ਅੰਤ
        ਜੇ (xsel->ਨਿਸ਼ਾਨਾ == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਅੰਕੜੇ = ਨਿਰਾ;
            ਪੂਰਨ format_property = 0;
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾਈ = 0;
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਬਾਈਟਾਂ_ਖੱਬਾ = 0;
            ਪੂਰਨ j;

            X11_XGet_ਖਿੜਕੀ_Property(display, Get_ਖਿੜਕੀ(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &ਲੰਮਾਈ, &ਬਾਈਟਾਂ_ਖੱਬਾ, &ਅੰਕੜੇ);

            ਪੂਰਨ allocationsize = (ਲੰਮਾਈ + 1) * ਆਕਾਰ(ਅੱਖਰ *);
            ਲਈ (j = 0, patom = (Atom *)ਅੰਕੜੇ; j < ਲੰਮਾਈ; j++, patom++) {
                ਅੱਖਰ *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            ਅੱਖਰ **new_mime_types = SDL_Allocate_Temporary_ਸਮ੍ਰਿਤੀ(allocationsize);
            ਜੇ (new_mime_types) {
                ਅੱਖਰ *strPtr = (ਅੱਖਰ *)(new_mime_types + ਲੰਮਾਈ + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                ਲਈ (j = 0, patom = (Atom *)ਅੰਕੜੇ; j < ਲੰਮਾਈ; j++, patom++) {
                    ਅੱਖਰ *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    ਅਚਲ size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[ਲੰਮਾਈ] = ਨਿਰਾ;

                SDL_SendClipboardUpdate(false, new_mime_types, ਲੰਮਾਈ);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            ਜੇ (ਅੰਕੜੇ) {
                X11_XFree(ਅੰਕੜੇ);
            }
        }

        videodata->selection_ਉਡੀਕ = false;
    } ਰੋਕੋ;

    ਹਾਲਤ SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_Clipboard_ਅੰਕੜੇ *clipboard = ਨਿਰਾ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.ਨਿਸ਼ਾਨਾ);
#ਜੇ_ਅੰਤ

        ਜੇ (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ਨਹੀਂਤਾਂ ਜੇ (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        ਜੇ (clipboard && clipboard->callback) {
            ਜੇ (clipboard->sequence) {
                SDL_Cancel_Clipboard_ਅੰਕੜੇ(clipboard->sequence);
            } ਨਹੀਂਤਾਂ {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } ਰੋਕੋ;

    ਹਾਲਤ PropertyNotify:
    {
        ਅੱਖਰ *name_ਦਾ_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        ਜੇ (SDL_strncmp(name_ਦਾ_atom, "SDL_SELECTION", ਆਕਾਰ("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_ਮੁੱਲ) {
            videodata->selection_incr_ਉਡੀਕ = false;
        }

        ਜੇ (name_ਦਾ_atom) {
            X11_XFree(name_ਦਾ_atom);
        }
    } ਰੋਕੋ;
    }
}

ਸਥਿਰ Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    ਵਾਪਸ ev->type == MapNotify &&
           ev->xmap.ਖਿੜਕੀ == unmap->ਖਿੜਕੀ &&
           ev->xmap.serial == unmap->serial;
}

ਸਥਿਰ Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    ਵਾਪਸ ev->type == ReparentNotify &&
           ev->xreparent.ਖਿੜਕੀ == unmap->ਖਿੜਕੀ &&
           ev->xreparent.serial == unmap->serial;
}

ਸਥਿਰ bool Is_ਉੱਚਾ_Latin1(ਅਚਲ ਅੱਖਰ *string, ਪੂਰਨ ਲੰਮਾਈ)
{
    ਜਦੋਂ (ਲੰਮਾਈ-- > 0) {
        Uint8 ch = (Uint8)*string;
        ਜੇ (ch >= 0x80) {
            ਵਾਪਸ true;
        }
        ++string;
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ ਪੂਰਨ XLookupStringAsUTF8(XKeyEvent *event_struct, ਅੱਖਰ *ਬਫਰ_return, ਪੂਰਨ ਬਾਈਟਾਂ_ਬਫਰ, ਕੁੰਜੀ_Sym *keysym_return, XCompose_ਸਥਿਤੀ *ਸਥਿਤੀ_ਵਿੱਚ_ਬਾਹਰਲਾ)
{
    ਪੂਰਨ ਨਤੀਜਾ = X11_XLookupString(event_struct, ਬਫਰ_return, ਬਾਈਟਾਂ_ਬਫਰ, keysym_return, ਸਥਿਤੀ_ਵਿੱਚ_ਬਾਹਰਲਾ);
    ਜੇ (Is_ਉੱਚਾ_Latin1(ਬਫਰ_return, ਨਤੀਜਾ)) {
        ਅੱਖਰ *utf8_ਪਾਠ = SDL_iconv_string("UTF-8", "ISO-8859-1", ਬਫਰ_return, ਨਤੀਜਾ + 1);
        ਜੇ (utf8_ਪਾਠ) {
            SDL_strlcpy(ਬਫਰ_return, utf8_ਪਾਠ, ਬਾਈਟਾਂ_ਬਫਰ);
            SDL_free(utf8_ਪਾਠ);
            ਵਾਪਸ SDL_strlen(ਬਫਰ_return);
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ 0;
        }
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *X11_ਲੱਭੋ_ਖਿੜਕੀ(SDL_Video_ਅੰਕੜੇ *videodata, ਖਿੜਕੀ_2 ਖਿੜਕੀ)
{
    ਜੇ (videodata && videodata->windowlist) {
        ਲਈ (ਪੂਰਨ i = 0; i < videodata->numwindows; ++i) {
            ਜੇ ((videodata->windowlist[i] != ਨਿਰਾ) &&
                (videodata->windowlist[i]->xwindow == ਖਿੜਕੀ)) {
                ਵਾਪਸ videodata->windowlist[i];
            }
        }
    }
    ਵਾਪਸ ਨਿਰਾ;
}

Uint64 X11_GetEventTimestamp(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਸਮਾਂ)
{
    // FIXME: Get the event time in the SDL tick time base
    ਵਾਪਸ SDL_GetTicksNS();
}

ਖਾਲੀ X11_Handle_ਕੁੰਜੀ_Event(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    Display *display = videodata->display;
    ਕੁੰਜੀ_ਕੋਡ_2 keycode = xevent->xkey.keycode;
    ਕੁੰਜੀ_Sym keysym = No_ਚਿੰਨ੍ਹ;
    ਪੂਰਨ ਪਾਠ_ਲੰਮਾਈ = 0;
    ਅੱਖਰ ਪਾਠ[64];
    ਸਥਿਤੀ_2 ਸਥਿਤੀ = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == ਕੁੰਜੀ_Press);
    SDL_Scancode scancode = videodata->keyboard.ਕੁੰਜੀ_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.ਸਮਾਂ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.ਖਿੜਕੀ, (xevent->type == ਕੁੰਜੀ_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_SCANCODES
    ਜੇ (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        ਪੂਰਨ min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_ਕੁੰਜੀ_ਕੋਡ_ਮੰਜ਼ਿਲ_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysym_ਮੰਜ਼ਿਲ_String(keysym));
    }
#ਜੇ_ਅੰਤ // DEBUG SCANCODES

    ਪਾਠ[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    ਜੇ (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (ਖਿਸਕਾਓ_ਨਕਾਬ_2 | Control_ਨਕਾਬ | Mod1_ਨਕਾਬ | Mod3_ਨਕਾਬ | Mod4_ਨਕਾਬ | Mod5_ਨਕਾਬ);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (ਤਾਲਾ_ਨਕਾਬ | videodata->keyboard.numlock_ਨਕਾਬ | videodata->keyboard.scrolllock_ਨਕਾਬ);
    }

    ਜੇ (SDL_ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ(windowdata->ਖਿੜਕੀ)) {
        // filter events catches XIM events and sends them to the correct handler
        ਜੇ (X11_XFilterEvent(xevent, None)) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
            handled_by_ime = true;
        }

        ਜੇ (!handled_by_ime) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
            ਜੇ (windowdata->ic && xevent->type == ਕੁੰਜੀ_Press) {
                ਪਾਠ_ਲੰਮਾਈ = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, ਪਾਠ, ਆਕਾਰ(ਪਾਠ) - 1,
                                      &keysym, &ਸਥਿਤੀ);
            } ਨਹੀਂਤਾਂ {
                ਪਾਠ_ਲੰਮਾਈ = XLookupStringAsUTF8(&xevent->xkey, ਪਾਠ, ਆਕਾਰ(ਪਾਠ) - 1, &keysym, ਨਿਰਾ);
            }
#ਨਹੀਂਤਾਂ
            ਪਾਠ_ਲੰਮਾਈ = XLookupStringAsUTF8(&xevent->xkey, ਪਾਠ, ਆਕਾਰ(ਪਾਠ) - 1, &keysym, ਨਿਰਾ);
#ਜੇ_ਅੰਤ
        }
    }

    ਜੇ (!handled_by_ime) {
        ਜੇ (pressed) {
            X11_Handle_Modifier_ਕੁੰਜੀਆਂ(videodata, scancode, true);
            SDL_Send_Keyboard_ਕੁੰਜੀ_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            ਜੇ (*ਪਾਠ && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                ਪਾਠ[ਪਾਠ_ਲੰਮਾਈ] = '\0';
                X11_ClearComposition(windowdata);
                SDL_Send_Keyboard_ਪਾਠ(ਪਾਠ);
            }
        } ਨਹੀਂਤਾਂ {
            ਜੇ (X11_ਕੁੰਜੀ_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                ਵਾਪਸ;
            }

            X11_Handle_Modifier_ਕੁੰਜੀਆਂ(videodata, scancode, false);
            SDL_Send_Keyboard_ਕੁੰਜੀ_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    ਜੇ (pressed) {
        X11_Update_User_ਸਮਾਂ(windowdata, xevent->xkey.ਸਮਾਂ);
    }
}

ਖਾਲੀ X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata, SDL_MouseID mouseID, ਪੂਰਨ button, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਸਮਾਂ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ serial)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = windowdata->ਖਿੜਕੀ;
    ਪੂਰਨ xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(ਸਮਾਂ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#ਜੇ_ਅੰਤ

    SDL_Mouse *mouse = SDL_GetMouse();
    ਜੇ (!mouse->relative_ਬਹੁਲਕ && (x != mouse->x || y != mouse->y)) {
        X11_Process_ਪ੍ਰਾਪਤੀ_Test(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, ਖਿੜਕੀ, mouseID, false, x, y);
    }

    ਜੇ (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, ਖਿੜਕੀ, mouseID, (ਦਸ਼ਮਲਵ)-xticks, (ਦਸ਼ਮਲਵ)yticks, SDL_MOUSEWHEEL_ਸਾਧਾਰਨ);
    } ਨਹੀਂਤਾਂ {
        ਜੇ (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        ਜੇ (button == Button1) {
            ਜੇ (X11_Trigger_ਪ੍ਰਾਪਤੀ_Test_Action(_this, windowdata, x, y)) {
                SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_TEST, 0, 0);
                ਵਾਪਸ; // don't pass this event on to app.
            }
        }
        ਜੇ (windowdata->ਆਖਰੀ_focus_event_ਸਮਾਂ) {
            ਅਚਲ ਪੂਰਨ X11_FOCUS_CLICK_TIMEOUT = 10;
            ਜੇ (SDL_GetTicks() < (windowdata->ਆਖਰੀ_focus_event_ਸਮਾਂ + X11_FOCUS_CLICK_TIMEOUT)) {
                ਜੇ (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->ਆਖਰੀ_focus_event_ਸਮਾਂ = 0;
        }
        ਜੇ (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, ਖਿੜਕੀ, mouseID, button, true);
        }
    }
    X11_Update_User_ਸਮਾਂ(windowdata, ਸਮਾਂ);
}

ਖਾਲੀ X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata, SDL_MouseID mouseID, ਪੂਰਨ button, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਸਮਾਂ)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = windowdata->ਖਿੜਕੀ;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    ਪੂਰਨ xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(ਸਮਾਂ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#ਜੇ_ਅੰਤ
    ਜੇ (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        ਜੇ (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, ਖਿੜਕੀ, mouseID, button, false);

        ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_grab) {
            X11_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(_this, ਖਿੜਕੀ, true);
        }
    }
}

ਖਾਲੀ X11_Get_Border_ਮੁੱਲਾਂ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = ਅੰਕੜੇ->videodata;
    Display *display = videodata->display;

    Atom type;
    ਪੂਰਨ format;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ nitems, ਬਾਈਟਾਂ_after;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    ਜੇ (!(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS)) {
        ਜੇ (X11_XGet_ਖਿੜਕੀ_Property(display, ਅੰਕੜੇ->xwindow, videodata->atoms.NET_ਚੌਖਟਾ_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &ਬਾਈਟਾਂ_after, &property) == Success) {
            ਜੇ (type != None && nitems == 4) {
                ਅੰਕੜੇ->border_ਖੱਬਾ = (ਪੂਰਨ)((ਲੰਮਾ *)property)[0];
                ਅੰਕੜੇ->border_ਸੱਜਾ = (ਪੂਰਨ)((ਲੰਮਾ *)property)[1];
                ਅੰਕੜੇ->border_ਸਿਖਰ = (ਪੂਰਨ)((ਲੰਮਾ *)property)[2];
                ਅੰਕੜੇ->border_bottom = (ਪੂਰਨ)((ਲੰਮਾ *)property)[3];
            }
            X11_XFree(property);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", ਅੰਕੜੇ->border_ਖੱਬਾ, ਅੰਕੜੇ->border_ਸੱਜਾ, ਅੰਕੜੇ->border_ਸਿਖਰ, ਅੰਕੜੇ->border_bottom);
#ਜੇ_ਅੰਤ
        }
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->border_ਖੱਬਾ = ਅੰਕੜੇ->border_ਸਿਖਰ = ਅੰਕੜੇ->border_ਸੱਜਾ = ਅੰਕੜੇ->border_bottom = 0;
    }
}

ਖਾਲੀ X11_EmitConfigureNotifyEvents(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ, XConfigureEvent *xevent)
{
    ਜੇ (!ਅੰਕੜੇ->ਮਾਪ_move_event_flags) {
        ਪੂਰਨ x = xevent->x;
        ਪੂਰਨ y = xevent->y;

        ਜੇ (xevent->x != ਅੰਕੜੇ->ਆਖਰੀ_xconfigure.x ||
            xevent->y != ਅੰਕੜੇ->ਆਖਰੀ_xconfigure.y) {
            ਅੰਕੜੇ->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_Global_ਮੰਜ਼ਿਲ_Relative_For_ਖਿੜਕੀ(ਅੰਕੜੇ->ਖਿੜਕੀ, x, y, &x, &y);
        SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MOVED, x, y);

        ਲਈ (SDL_ਖਿੜਕੀ *w = ਅੰਕੜੇ->ਖਿੜਕੀ->ਪਹਿਲਾ_ਬੱਚਾ; w; w = w->ਅਗਲਾ_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(w) && !(w->flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
                X11_Update_ਖਿੜਕੀ_Position(w, true);
            }
        }

        ਜੇ (xevent->ਚੌੜਾਈ != ਅੰਕੜੇ->ਆਖਰੀ_xconfigure.ਚੌੜਾਈ ||
            xevent->ਉਚਾਈ != ਅੰਕੜੇ->ਆਖਰੀ_xconfigure.ਉਚਾਈ) {
            ਅੰਕੜੇ->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, xevent->ਚੌੜਾਈ, xevent->ਉਚਾਈ);
    }

    SDL_copyp(&ਅੰਕੜੇ->ਆਖਰੀ_xconfigure, xevent);
}

ਸਥਿਰ ਖਾਲੀ X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    Display *display;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;
    XClient_ਸੁਨੇਹਾ_Event m;
    ਪੂਰਨ i;

    SDL_assert(videodata != ਨਿਰਾ);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    ਜੇ (xevent->type != ਕੁੰਜੀ_Press && xevent->type != ਕੁੰਜੀ_Release) {
        ਜੇ (X11_XFilterEvent(xevent, None)) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
            ਵਾਪਸ;
        }
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    ਜੇ (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        ਵਾਪਸ;
    }
#ਜੇ_ਅੰਤ

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    ਜੇ (g_X11EventHook) {
        ਜੇ (!g_X11EventHook(g_X11_Event_Hook_ਅੰਕੜੇ, xevent)) {
            ਵਾਪਸ;
        }
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
    ਜੇ (videodata->xrandr_event_ਅਧਾਰ && (xevent->type == (videodata->xrandr_event_ਅਧਾਰ + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
    ਜੇ (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#ਜੇ_ਅੰਤ

        ਜੇ (ev->subtype == XFixes_ਸੈੱਟ_Selection_Owner_Notify)
        {
            ਜੇ (ev->selection != videodata->atoms.CLIPBOARD)
                ਵਾਪਸ;

            ਜੇ (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_ਖਿੜਕੀ)
                ਵਾਪਸ;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, Get_ਖਿੜਕੀ(_this), Current_ਸਮਾਂ);
        }

        ਵਾਪਸ;
    }
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XFIXES

    ਜੇ ((videodata->clipboard_ਖਿੜਕੀ != None) &&
        (videodata->clipboard_ਖਿੜਕੀ == xevent->xany.ਖਿੜਕੀ)) {
        X11_HandleClipboardEvent(_this, xevent);
        ਵਾਪਸ;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    ਅੰਕੜੇ = X11_ਲੱਭੋ_ਖਿੜਕੀ(videodata, xevent->xany.ਖਿੜਕੀ);

    ਜੇ (!ਅੰਕੜੇ) {
        // The window for KeymapNotify, etc events is 0
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        ਜੇ (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            ਚੋਣ (xkbevent->any.xkb_type) {
            ਹਾਲਤ XkbStateNotify:
            {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
                ਜੇ ((xkbevent->state.ਬਦਲਿਆ & Xkb_ਸਮੂਹ_State_ਨਕਾਬ) && xkbevent->state.ਸਮੂਹ != videodata->keyboard.xkb.current_ਸਮੂਹ) {
                    videodata->keyboard.xkb.current_ਸਮੂਹ = xkbevent->state.ਸਮੂਹ;
                    SDL_ਸੈੱਟ_Keymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_ਸਮੂਹ], true);
                }

                ਜੇ (xkbevent->state.ਬਦਲਿਆ & Xkb_Modifier_State_ਨਕਾਬ) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.ਅਧਾਰ_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } ਰੋਕੋ;

            ਹਾਲਤ XkbMapNotify:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.ਖਿੜਕੀ);
                SDL_FALLTHROUGH;
#ਜੇ_ਅੰਤ
            ਹਾਲਤ XkbNewKeyboardNotify:
            {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
                ਜੇ (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.ਖਿੜਕੀ);
                }
#ਜੇ_ਅੰਤ
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                ਜੇ (xkbevent->any.serial != videodata->keyboard.xkb.ਆਖਰੀ_map_serial) {
                    videodata->keyboard.xkb.ਆਖਰੀ_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } ਰੋਕੋ;

            ਮੂਲ:
                ਰੋਕੋ;
            }
        } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        ਜੇ (xevent->type == KeymapNotify) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
            ਜੇ (SDL_GetKeyboardFocus() != ਨਿਰਾ) {
                ਜੇ (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (xevent->type == MappingNotify) {
            ਅਚਲ ਪੂਰਨ request = xevent->xmapping.request;

            ਜੇ (request == Mapping_ਸੂਚਕ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
                X11_Xinput2_Update_ਸੂਚਕ_Mapping(_this);
            } ਨਹੀਂਤਾਂ ਜੇ (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
                ਜੇ (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (xevent->type == PropertyNotify && videodata) {
            ਅੱਖਰ *name_ਦਾ_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            ਜੇ (name_ਦਾ_atom) {
                ਜੇ (SDL_startswith(name_ਦਾ_atom, "_ICC_PROFILE")) {
                    XWindow_ਗੁਣ attrib;
                    ਪੂਰਨ screennum;
                    ਲਈ (i = 0; i < videodata->numwindows; ++i) {
                        ਜੇ (videodata->windowlist[i] != ਨਿਰਾ) {
                            ਅੰਕੜੇ = videodata->windowlist[i];
                            X11_XGet_ਖਿੜਕੀ_ਗੁਣ(display, ਅੰਕੜੇ->xwindow, &attrib);
                            screennum = X11_XScreen_ਸੰਖਿਆ_ਦਾ_Screen(attrib.screen);
                            ਜੇ (screennum == 0 && SDL_strcmp(name_ਦਾ_atom, "_ICC_PROFILE") == 0) {
                                SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_ICCPROF_ਬਦਲਿਆ, 0, 0);
                            } ਨਹੀਂਤਾਂ ਜੇ (SDL_strncmp(name_ਦਾ_atom, "_ICC_PROFILE_", ਆਕਾਰ("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_ਦਾ_atom) > ਆਕਾਰ("_ICC_PROFILE_") - 1) {
                                ਪੂਰਨ iccscreennum = SDL_atoi(&name_ਦਾ_atom[ਆਕਾਰ("_ICC_PROFILE_") - 1]);

                                ਜੇ (screennum == iccscreennum) {
                                    SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_ICCPROF_ਬਦਲਿਆ, 0, 0);
                                }
                            }
                        }
                    }
                } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(name_ਦਾ_atom, "_NET_WORKAREA") == 0) {
                    ਲਈ (i = 0; i < _this->ਅੰਕ_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_ਬਦਲਿਆ, 0, 0);
                    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
                } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(name_ਦਾ_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_ਦਾ_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#ਜੇ_ਅੰਤ
                }
                X11_XFree(name_ਦਾ_atom);
            }
        }
        ਵਾਪਸ;
    }

    ਚੋਣ (xevent->type) {

        // Gaining mouse coverage?
    ਹਾਲਤ EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.ਖਿੜਕੀ,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.ਬਹੁਲਕ);
        ਜੇ (xevent->xcrossing.ਬਹੁਲਕ == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        ਜੇ (xevent->xcrossing.ਬਹੁਲਕ == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#ਜੇ_ਅੰਤ
        SDL_ਸੈੱਟ_Mouse_Focus(ਅੰਕੜੇ->ਖਿੜਕੀ);

        mouse->ਆਖਰੀ_x = xevent->xcrossing.x;
        mouse->ਆਖਰੀ_y = xevent->xcrossing.y;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
        {
            // Only create the barriers if we have input focus
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = ਅੰਕੜੇ->ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
            ਜੇ ((ਅੰਕੜੇ->ਸੂਚਕ_barrier_ਸਰਗਰਮ == true) && windowdata->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->ਖਿੜਕੀ, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#ਜੇ_ਅੰਤ

        ਜੇ (!mouse->relative_ਬਹੁਲਕ) {
            SDL_SendMouseMotion(0, ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_GLOBAL_MOUSE_ID, false, (ਦਸ਼ਮਲਵ)xevent->xcrossing.x, (ਦਸ਼ਮਲਵ)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        ਜੇ (!(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_CAPTURE)) {
            SDL_Update_ਖਿੜਕੀ_Grab(ਅੰਕੜੇ->ਖਿੜਕੀ);
        }

        X11_Process_ਪ੍ਰਾਪਤੀ_Test(_this, ਅੰਕੜੇ, mouse->ਆਖਰੀ_x, mouse->ਆਖਰੀ_y, true);
    } ਰੋਕੋ;
        // Losing mouse coverage?
    ਹਾਲਤ LeaveNotify:
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.ਖਿੜਕੀ,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.ਬਹੁਲਕ);
        ਜੇ (xevent->xcrossing.ਬਹੁਲਕ == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        ਜੇ (xevent->xcrossing.ਬਹੁਲਕ == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#ਜੇ_ਅੰਤ
        ਜੇ (!SDL_GetMouse()->relative_ਬਹੁਲਕ) {
            SDL_SendMouseMotion(0, ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_GLOBAL_MOUSE_ID, false, (ਦਸ਼ਮਲਵ)xevent->xcrossing.x, (ਦਸ਼ਮਲਵ)xevent->xcrossing.y);
        }

        ਜੇ (xevent->xcrossing.ਬਹੁਲਕ != NotifyGrab &&
            xevent->xcrossing.ਬਹੁਲਕ != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            ਜੇ (!(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
                X11_ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab(_this, ਅੰਕੜੇ->ਖਿੜਕੀ, false);
            }

            SDL_ਸੈੱਟ_Mouse_Focus(ਨਿਰਾ);
        }
    } ਰੋਕੋ;

        // Gaining input focus?
    ਹਾਲਤ Focus_ਵਿੱਚ:
    {
        ਜੇ (xevent->xfocus.ਬਹੁਲਕ == NotifyGrab || xevent->xfocus.ਬਹੁਲਕ == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
            ਰੋਕੋ;
        }

        ਜੇ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_ਸੂਚਕ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
            ਰੋਕੋ;
        }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
        ਜੇ (!videodata->ਆਖਰੀ_ਬਹੁਲਕ_change_deadline) /* no recent mode changes */ {
            ਅੰਕੜੇ->pending_focus = PENDING_FOCUS_NONE;
            ਅੰਕੜੇ->pending_focus_ਸਮਾਂ = 0;
            X11_Dispatch_Focus_ਵਿੱਚ(_this, ਅੰਕੜੇ);
        } ਨਹੀਂਤਾਂ {
            ਅੰਕੜੇ->pending_focus = PENDING_FOCUS_ਵਿੱਚ;
            ਅੰਕੜੇ->pending_focus_ਸਮਾਂ = SDL_GetTicks() + PENDING_FOCUS_ਸਮਾਂ;
        }
        ਅੰਕੜੇ->ਆਖਰੀ_focus_event_ਸਮਾਂ = SDL_GetTicks();
    } ਰੋਕੋ;

        // Losing input focus?
    ਹਾਲਤ Focus_ਬਾਹਰਲਾ:
    {
        ਜੇ (xevent->xfocus.ਬਹੁਲਕ == NotifyGrab || xevent->xfocus.ਬਹੁਲਕ == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
            ਰੋਕੋ;
        }
        ਜੇ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_ਸੂਚਕ) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
            ਰੋਕੋ;
        }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
        ਜੇ (!videodata->ਆਖਰੀ_ਬਹੁਲਕ_change_deadline) /* no recent mode changes */ {
            ਅੰਕੜੇ->pending_focus = PENDING_FOCUS_NONE;
            ਅੰਕੜੇ->pending_focus_ਸਮਾਂ = 0;
            X11_Dispatch_Focus_ਬਾਹਰਲਾ(_this, ਅੰਕੜੇ);
        } ਨਹੀਂਤਾਂ {
            ਅੰਕੜੇ->pending_focus = PENDING_FOCUS_ਬਾਹਰਲਾ;
            ਅੰਕੜੇ->pending_focus_ਸਮਾਂ = SDL_GetTicks() + PENDING_FOCUS_ਸਮਾਂ;
        }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        ਜੇ (ਅੰਕੜੇ->ਸੂਚਕ_barrier_ਸਰਗਰਮ == true) {
            X11_ConfineCursorWithFlags(_this, ਅੰਕੜੇ->ਖਿੜਕੀ, ਨਿਰਾ, X11_BARRIER_HANDLED_BY_EVENT);
        }
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XFIXES
    } ਰੋਕੋ;


        // Have we been iconified?
    ਹਾਲਤ UnmapNotify:
    {
        XEvent ev;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ

        ਜੇ (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } ਨਹੀਂਤਾਂ {
            X11_DispatchUnmapNotify(ਅੰਕੜੇ);
        }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        ਜੇ (ਅੰਕੜੇ->ਸੂਚਕ_barrier_ਸਰਗਰਮ == true) {
            X11_ConfineCursorWithFlags(_this, ਅੰਕੜੇ->ਖਿੜਕੀ, ਨਿਰਾ, X11_BARRIER_HANDLED_BY_EVENT);
        }
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XFIXES
    } ਰੋਕੋ;

        // Have we been restored?
    ਹਾਲਤ MapNotify:
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
        X11_DispatchMapNotify(ਅੰਕੜੇ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        ਜੇ (ਅੰਕੜੇ->ਸੂਚਕ_barrier_ਸਰਗਰਮ == true) {
            X11_ConfineCursorWithFlags(_this, ਅੰਕੜੇ->ਖਿੜਕੀ, &ਅੰਕੜੇ->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XFIXES
    } ਰੋਕੋ;

        // Have we been resized or moved?
    ਹਾਲਤ ConfigureNotify:
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.ਖਿੜਕੀ,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.ਚੌੜਾਈ, xevent->xconfigure.ਉਚਾਈ);
#ਜੇ_ਅੰਤ
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        ਜੇ (!xevent->xconfigure.send_event) {
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਅੰਕ_Children;
            ਖਿੜਕੀ_2 ਬੱਚਾ_Return, ਜੜ੍ਹ_2, ਮਾਪਾ_2;
            ਖਿੜਕੀ_2 *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_ਆਖਰੀ_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_ਖਿੜਕੀ_Error_Handler);

            X11_XQuery_ਰੁੱਖ(ਅੰਕੜੇ->videodata->display, xevent->xconfigure.ਖਿੜਕੀ, &ਜੜ੍ਹ_2, &ਮਾਪਾ_2, &Children, &ਅੰਕ_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      ਮਾਪਾ_2, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &ਬੱਚਾ_Return);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            ਜੇ (x11_ਆਖਰੀ_error == Bad_ਖਿੜਕੀ) {
                ਰੋਕੋ;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        ਅਚਲ SDL_ਖਿੜਕੀ_Flags ਬਦਲਿਆ = X11_GetNetWMState(_this, ਅੰਕੜੇ->ਖਿੜਕੀ, xevent->xproperty.ਖਿੜਕੀ) ^ ਅੰਕੜੇ->ਖਿੜਕੀ->flags;
        ਜੇ (ਬਦਲਿਆ & (SDL_ਖਿੜਕੀ_FULLSCREEN | SDL_ਖਿੜਕੀ_MAXIMIZED)) {
            SDL_copyp(&ਅੰਕੜੇ->pending_xconfigure, &xevent->xconfigure);
            ਅੰਕੜੇ->emit_ਮਾਪ_move_after_property_notify = true;
        }

        ਜੇ (!ਅੰਕੜੇ->emit_ਮਾਪ_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(ਅੰਕੜੇ, &xevent->xconfigure);
        }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(ਅੰਕੜੇ->ਖਿੜਕੀ, &xevent->xconfigure);
#ਜੇ_ਅੰਤ /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } ਰੋਕੋ;

        // Have we been requested to quit (or another client message?)
    ਹਾਲਤ Client_ਸੁਨੇਹਾ:
    {
        ਸਥਿਰ ਪੂਰਨ xdnd_ਸੰਸਕਰਣ = 0;

        ਜੇ (xevent->xclient.ਸੁਨੇਹਾ_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.ਅੰਕੜੇ.l[1] & 1;
            ਅੰਕੜੇ->xdnd_ਸਰੋਤ = xevent->xclient.ਅੰਕੜੇ.l[0];
            xdnd_ਸੰਸਕਰਣ = (xevent->xclient.ਅੰਕੜੇ.l[1] >> 24);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", ਅੰਕੜੇ->xdnd_ਸਰੋਤ);
            SDL_Log("Protocol version to use : %d", xdnd_ਸੰਸਕਰਣ);
            SDL_Log("More then 3 data types : %d", (ਪੂਰਨ)use_list);
#ਜੇ_ਅੰਤ

            ਜੇ (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, ਅੰਕੜੇ->xdnd_ਸਰੋਤ, videodata->atoms.XdndTypeList);
                // pick one
                ਅੰਕੜੇ->xdnd_req = X11_Pick_ਨਿਸ਼ਾਨਾ(display, (Atom *)p.ਅੰਕੜੇ, p.ਗਿਣਤੀ_2);
                X11_XFree(p.ਅੰਕੜੇ);
            } ਨਹੀਂਤਾਂ {
                // pick from list of three
                ਅੰਕੜੇ->xdnd_req = X11_Pick_ਨਿਸ਼ਾਨਾ_From_Atoms(display, xevent->xclient.ਅੰਕੜੇ.l[2], xevent->xclient.ਅੰਕੜੇ.l[3], xevent->xclient.ਅੰਕੜੇ.l[4]);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (xevent->xclient.ਸੁਨੇਹਾ_type == videodata->atoms.XdndLeave) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.ਅੰਕੜੇ.l[0]);
#ਜੇ_ਅੰਤ
            SDL_SendDropComplete(ਅੰਕੜੇ->ਖਿੜਕੀ);
        } ਨਹੀਂਤਾਂ ਜੇ (xevent->xclient.ਸੁਨੇਹਾ_type == videodata->atoms.XdndPosition) {

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            ਜੇ (xdnd_ਸੰਸਕਰਣ >= 2) {
                act = xevent->xclient.ਅੰਕੜੇ.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#ਜੇ_ਅੰਤ
            {
                // Drag and Drop position
                ਪੂਰਨ ਜੜ੍ਹ_x, ਜੜ੍ਹ_y, ਖਿੜਕੀ_x, ਖਿੜਕੀ_y;
                ਖਿੜਕੀ_2 ਬੱਚਾ_Return;
                ਜੜ੍ਹ_x = xevent->xclient.ਅੰਕੜੇ.l[2] >> 16;
                ਜੜ੍ਹ_y = xevent->xclient.ਅੰਕੜੇ.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(display), ਅੰਕੜੇ->xwindow,
                                          ਜੜ੍ਹ_x, ਜੜ੍ਹ_y, &ਖਿੜਕੀ_x, &ਖਿੜਕੀ_y, &ਬੱਚਾ_Return);

                SDL_SendDropPosition(ਅੰਕੜੇ->ਖਿੜਕੀ, (ਦਸ਼ਮਲਵ)ਖਿੜਕੀ_x, (ਦਸ਼ਮਲਵ)ਖਿੜਕੀ_y);
            }

            // reply with status
            SDL_zero(m);
            m.type = Client_ਸੁਨੇਹਾ;
            m.display = xevent->xclient.display;
            m.ਖਿੜਕੀ = xevent->xclient.ਅੰਕੜੇ.l[0];
            m.ਸੁਨੇਹਾ_type = videodata->atoms.Xdnd_ਸਥਿਤੀ;
            m.format = 32;
            m.ਅੰਕੜੇ.l[0] = ਅੰਕੜੇ->xwindow;
            m.ਅੰਕੜੇ.l[1] = (ਅੰਕੜੇ->xdnd_req != None);
            m.ਅੰਕੜੇ.l[2] = 0; // specify an empty rectangle
            m.ਅੰਕੜੇ.l[3] = 0;
            m.ਅੰਕੜੇ.l[4] = videodata->atoms.XdndActionCopy; // we only accept copying anyway

            X11_XSendEvent(display, xevent->xclient.ਅੰਕੜੇ.l[0], False, No_Event_ਨਕਾਬ, (XEvent *)&m);
            X11_XFlush(display);
        } ਨਹੀਂਤਾਂ ਜੇ (xevent->xclient.ਸੁਨੇਹਾ_type == videodata->atoms.XdndDrop) {
            ਜੇ (ਅੰਕੜੇ->xdnd_req == None) {
                // say again - not interested!
                SDL_zero(m);
                m.type = Client_ਸੁਨੇਹਾ;
                m.display = xevent->xclient.display;
                m.ਖਿੜਕੀ = xevent->xclient.ਅੰਕੜੇ.l[0];
                m.ਸੁਨੇਹਾ_type = videodata->atoms.Xdnd_ਮੁਕੰਮਲ;
                m.format = 32;
                m.ਅੰਕੜੇ.l[0] = ਅੰਕੜੇ->xwindow;
                m.ਅੰਕੜੇ.l[1] = 0;
                m.ਅੰਕੜੇ.l[2] = None; // fail!
                X11_XSendEvent(display, xevent->xclient.ਅੰਕੜੇ.l[0], False, No_Event_ਨਕਾਬ, (XEvent *)&m);
            } ਨਹੀਂਤਾਂ {
                // convert
                ਜੇ (xdnd_ਸੰਸਕਰਣ >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, ਅੰਕੜੇ->xdnd_req, videodata->atoms.PRIMARY, ਅੰਕੜੇ->xwindow, xevent->xclient.ਅੰਕੜੇ.l[2]);
                } ਨਹੀਂਤਾਂ {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, ਅੰਕੜੇ->xdnd_req, videodata->atoms.PRIMARY, ਅੰਕੜੇ->xwindow, Current_ਸਮਾਂ);
                }
            }
        } ਨਹੀਂਤਾਂ ਜੇ ((xevent->xclient.ਸੁਨੇਹਾ_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.ਅੰਕੜੇ.l[0] == videodata->atoms._NET_WM_PING)) {
            ਖਿੜਕੀ_2 ਜੜ੍ਹ = Default_ਜੜ੍ਹ_ਖਿੜਕੀ(display);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
            xevent->xclient.ਖਿੜਕੀ = ਜੜ੍ਹ;
            X11_XSendEvent(display, ਜੜ੍ਹ, False, Substructure_Redirect_ਨਕਾਬ | Substructure_Notify_ਨਕਾਬ, xevent);
            ਰੋਕੋ;
        }

        ਨਹੀਂਤਾਂ ਜੇ ((xevent->xclient.ਸੁਨੇਹਾ_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.ਅੰਕੜੇ.l[0] == videodata->atoms.WM_DELETE_ਖਿੜਕੀ)) {

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_CLOSE_REQUESTED, 0, 0);
            ਰੋਕੋ;
        } ਨਹੀਂਤਾਂ ਜੇ ((xevent->xclient.ਸੁਨੇਹਾ_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.ਅੰਕੜੇ.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", ਅੰਕੜੇ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(ਅੰਕੜੇ->ਖਿੜਕੀ, &xevent->xclient);
#ਜੇ_ਅੰਤ /* SDL_VIDEO_DRIVER_X11_XSYNC */
            ਰੋਕੋ;
        }
    } ਰੋਕੋ;

        // Do we need to refresh ourselves?
    ਹਾਲਤ Expose:
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.ਖਿੜਕੀ, xevent->xexpose.ਗਿਣਤੀ_2);
#ਜੇ_ਅੰਤ
        SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_EXPOSED, 0, 0);
    } ਰੋਕੋ;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    ਹਾਲਤ ਕੁੰਜੀ_Press:
    ਹਾਲਤ ਕੁੰਜੀ_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        ਜੇ (ਅੰਕੜੇ->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            ਰੋਕੋ;
        } ਨਹੀਂਤਾਂ ਜੇ (xevent->xkey.serial == videodata->xinput_ਆਖਰੀ_ਕੁੰਜੀ_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_ਆਖਰੀ_keyboard_device;
        }

        X11_Handle_ਕੁੰਜੀ_Event(_this, ਅੰਕੜੇ, keyboardID, xevent);
    } ਰੋਕੋ;

    ਹਾਲਤ MotionNotify:
    {
        ਜੇ (X11_Xinput2_Handles_Motion_For_ਖਿੜਕੀ(ਅੰਕੜੇ)) {
            // This input is being handled by XInput2
            ਰੋਕੋ;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        ਜੇ (!mouse->relative_ਬਹੁਲਕ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.ਖਿੜਕੀ, xevent->xmotion.x, xevent->xmotion.y);
#ਜੇ_ਅੰਤ

            X11_Process_ਪ੍ਰਾਪਤੀ_Test(_this, ਅੰਕੜੇ, (ਦਸ਼ਮਲਵ)xevent->xmotion.x, (ਦਸ਼ਮਲਵ)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_GLOBAL_MOUSE_ID, false, (ਦਸ਼ਮਲਵ)xevent->xmotion.x, (ਦਸ਼ਮਲਵ)xevent->xmotion.y);
        }
    } ਰੋਕੋ;

    ਹਾਲਤ ButtonPress:
    {
        ਜੇ (ਅੰਕੜੇ->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_ਆਖਰੀ_button_serial) {
            // This input event was handled by XInput2.
            ਰੋਕੋ;
        }

        X11_HandleButtonPress(_this, ਅੰਕੜੇ, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.ਸਮਾਂ, xevent->xbutton.serial);
    } ਰੋਕੋ;

    ਹਾਲਤ ButtonRelease:
    {
        ਜੇ (ਅੰਕੜੇ->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_ਆਖਰੀ_button_serial) {
            // This input event was handled by XInput2.
            ਰੋਕੋ;
        }

        X11_HandleButtonRelease(_this, ਅੰਕੜੇ, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.ਸਮਾਂ);
    } ਰੋਕੋ;

    ਹਾਲਤ PropertyNotify:
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *propdata;
        ਪੂਰਨ ਸਥਿਤੀ, real_format;
        Atom real_type;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਚੀਜ਼ਾਂ_read, ਚੀਜ਼ਾਂ_ਖੱਬਾ;

        ਅੱਖਰ *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        ਜੇ (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.ਖਿੜਕੀ, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.ਸਮਾਂ);
            X11_XFree(name);
        }

        ਸਥਿਤੀ = X11_XGet_ਖਿੜਕੀ_Property(display, ਅੰਕੜੇ->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &ਚੀਜ਼ਾਂ_read, &ਚੀਜ਼ਾਂ_ਖੱਬਾ, &propdata);
        ਜੇ (ਸਥਿਤੀ == Success && ਚੀਜ਼ਾਂ_read > 0) {
            ਜੇ (real_type == XA_INTEGER) {
                ਪੂਰਨ *ਮੁੱਲਾਂ = (ਪੂਰਨ *)propdata;

                SDL_Log("{");
                ਲਈ (i = 0; i < ਚੀਜ਼ਾਂ_read; i++) {
                    SDL_Log(" %d", ਮੁੱਲਾਂ[i]);
                }
                SDL_Log(" }");
            } ਨਹੀਂਤਾਂ ਜੇ (real_type == XA_CARDINAL) {
                ਜੇ (real_format == 32) {
                    Uint32 *ਮੁੱਲਾਂ = (Uint32 *)propdata;

                    SDL_Log("{");
                    ਲਈ (i = 0; i < ਚੀਜ਼ਾਂ_read; i++) {
                        SDL_Log(" %d", ਮੁੱਲਾਂ[i]);
                    }
                    SDL_Log(" }");
                } ਨਹੀਂਤਾਂ ਜੇ (real_format == 16) {
                    Uint16 *ਮੁੱਲਾਂ = (Uint16 *)propdata;

                    SDL_Log("{");
                    ਲਈ (i = 0; i < ਚੀਜ਼ਾਂ_read; i++) {
                        SDL_Log(" %d", ਮੁੱਲਾਂ[i]);
                    }
                    SDL_Log(" }");
                } ਨਹੀਂਤਾਂ ਜੇ (real_format == 8) {
                    Uint8 *ਮੁੱਲਾਂ = (Uint8 *)propdata;

                    SDL_Log("{");
                    ਲਈ (i = 0; i < ਚੀਜ਼ਾਂ_read; i++) {
                        SDL_Log(" %d", ਮੁੱਲਾਂ[i]);
                    }
                    SDL_Log(" }");
                }
            } ਨਹੀਂਤਾਂ ਜੇ (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } ਨਹੀਂਤਾਂ ਜੇ (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                ਲਈ (i = 0; i < ਚੀਜ਼ਾਂ_read; i++) {
                    ਅੱਖਰ *atomname = X11_XGetAtomName(display, atoms[i]);
                    ਜੇ (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } ਨਹੀਂਤਾਂ {
                ਅੱਖਰ *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                ਜੇ (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        ਜੇ (ਸਥਿਤੀ == Success) {
            X11_XFree(propdata);
        }
#ਜੇ_ਅੰਤ // DEBUG_XEVENTS

        /* Take advantage of this moment to make sure user_time has a
            valid timestamp from the X server, so if we later try to
            raise/restore this window, _NET_ACTIVE_WINDOW can have a
            non-zero timestamp, even if there's never been a mouse or
            key press to this window so far. Note that we don't try to
            set _NET_WM_USER_TIME here, though. That's only for legit
            user interaction with the window. */
        ਜੇ (!ਅੰਕੜੇ->user_ਸਮਾਂ) {
            ਅੰਕੜੇ->user_ਸਮਾਂ = xevent->xproperty.ਸਮਾਂ;
        }

        ਜੇ (xevent->xproperty.atom == ਅੰਕੜੇ->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            ਅਚਲ SDL_ਖਿੜਕੀ_Flags flags = X11_GetNetWMState(_this, ਅੰਕੜੇ->ਖਿੜਕੀ, xevent->xproperty.ਖਿੜਕੀ);
            ਅਚਲ SDL_ਖਿੜਕੀ_Flags ਬਦਲਿਆ = flags ^ ਅੰਕੜੇ->ਖਿੜਕੀ->flags;

            ਜੇ ((ਬਦਲਿਆ & SDL_ਖਿੜਕੀ_HIDDEN) && !(flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
                X11_DispatchMapNotify(ਅੰਕੜੇ);
            }

            ਜੇ (!SDL_ਖਿੜਕੀ_IS_POPUP(ਅੰਕੜੇ->ਖਿੜਕੀ)) {
                ਜੇ (ਬਦਲਿਆ & SDL_ਖਿੜਕੀ_FULLSCREEN) {
                    ਅੰਕੜੇ->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    ਜੇ (flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
                        ਜੇ (!(flags & SDL_ਖਿੜਕੀ_MINIMIZED)) {
                            ਅਚਲ bool commit = SDL_memcmp(&ਅੰਕੜੇ->ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ, &ਅੰਕੜੇ->requested_fullscreen_ਬਹੁਲਕ, ਆਕਾਰ(SDL_Display_ਬਹੁਲਕ)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESTORED, 0, 0);
                            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_ENTER_FULLSCREEN, 0, 0);
                            ਜੇ (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&ਅੰਕੜੇ->ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ, &ਅੰਕੜੇ->ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ);
                                SDL_Update_Fullscreen_ਬਹੁਲਕ(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_FULLSCREEN_OP_UPDATE, true);
                            } ਨਹੀਂਤਾਂ {
                                SDL_Update_Fullscreen_ਬਹੁਲਕ(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } ਨਹੀਂਤਾਂ {
                        SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_LEAVE_FULLSCREEN, 0, 0);
                        SDL_Update_Fullscreen_ਬਹੁਲਕ(ਅੰਕੜੇ->ਖਿੜਕੀ, false, false);

                        SDL_zero(ਅੰਕੜੇ->requested_fullscreen_ਬਹੁਲਕ);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_ਸੈੱਟ_ਖਿੜਕੀ_Min_Max(ਅੰਕੜੇ->ਖਿੜਕੀ, !!(flags & SDL_ਖਿੜਕੀ_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        ਜੇ (ਅੰਕੜੇ->fullscreen_borders_forced_on) {
                            ਅੰਕੜੇ->toggle_borders = true;
                            ਅੰਕੜੇ->fullscreen_borders_forced_on = false;
                        }
                    }

                    ਜੇ ((flags & SDL_ਖਿੜਕੀ_FULLSCREEN) &&
                        (ਅੰਕੜੇ->border_ਸਿਖਰ || ਅੰਕੜੇ->border_ਖੱਬਾ || ਅੰਕੜੇ->border_bottom || ਅੰਕੜੇ->border_ਸੱਜਾ)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        ਅੰਕੜੇ->ਮਾਪ_move_event_flags |= X11_ਮਾਪ_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        ਅੰਕੜੇ->ਪਿਛਲਾ_borders_nonzero = true;
                    } ਨਹੀਂਤਾਂ ਜੇ (!(flags & SDL_ਖਿੜਕੀ_FULLSCREEN) &&
                               ਅੰਕੜੇ->ਪਿਛਲਾ_borders_nonzero &&
                               (!ਅੰਕੜੇ->border_ਸਿਖਰ && !ਅੰਕੜੇ->border_ਖੱਬਾ && !ਅੰਕੜੇ->border_bottom && !ਅੰਕੜੇ->border_ਸੱਜਾ)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        ਅੰਕੜੇ->ਮਾਪ_move_event_flags |= X11_ਮਾਪ_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        ਅੰਕੜੇ->ਪਿਛਲਾ_borders_nonzero = false;
                    } ਨਹੀਂਤਾਂ {
                        ਅੰਕੜੇ->ਮਾਪ_move_event_flags = 0;
                        ਅੰਕੜੇ->ਪਿਛਲਾ_borders_nonzero = false;

                        ਜੇ (!(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) && ਅੰਕੜੇ->toggle_borders) {
                            ਅੰਕੜੇ->toggle_borders = false;
                            X11_ਸੈੱਟ_ਖਿੜਕੀ_Bordered(_this, ਅੰਕੜੇ->ਖਿੜਕੀ, !(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS));
                        }
                    }
                }
                ਜੇ ((ਬਦਲਿਆ & SDL_ਖਿੜਕੀ_MAXIMIZED) && ((flags & SDL_ਖਿੜਕੀ_MAXIMIZED) && !(flags & SDL_ਖਿੜਕੀ_MINIMIZED))) {
                    ਅੰਕੜੇ->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    ਜੇ ((ਬਦਲਿਆ & SDL_ਖਿੜਕੀ_MINIMIZED)) {
                        ਅੰਕੜੇ->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESTORED, 0, 0);
                    }
                    SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MAXIMIZED, 0, 0);
                }
                ਜੇ ((ਬਦਲਿਆ & SDL_ਖਿੜਕੀ_MINIMIZED) && (flags & SDL_ਖਿੜਕੀ_MINIMIZED)) {
                    ਅੰਕੜੇ->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MINIMIZED, 0, 0);
                }
                ਜੇ (!(flags & (SDL_ਖਿੜਕੀ_MAXIMIZED | SDL_ਖਿੜਕੀ_MINIMIZED))) {
                    ਅੰਕੜੇ->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    ਜੇ (!(flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
                        ਜੇ (ਅੰਕੜੇ->pending_position) {
                            ਅੰਕੜੇ->pending_position = false;
                            ਅੰਕੜੇ->pending_operation |= X11_PENDING_OP_MOVE;
                            ਅੰਕੜੇ->expected.x = ਅੰਕੜੇ->ਖਿੜਕੀ->pending.x - ਅੰਕੜੇ->border_ਖੱਬਾ;
                            ਅੰਕੜੇ->expected.y = ਅੰਕੜੇ->ਖਿੜਕੀ->pending.y - ਅੰਕੜੇ->border_ਸਿਖਰ;
                            X11_XMove_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, ਅੰਕੜੇ->expected.x, ਅੰਕੜੇ->expected.y);
                        }
                        ਜੇ (ਅੰਕੜੇ->pending_ਮਾਪ) {
                            ਅੰਕੜੇ->pending_ਮਾਪ = false;
                            ਅੰਕੜੇ->pending_operation |= X11_PENDING_OP_RESIZE;
                            ਅੰਕੜੇ->expected.w = ਅੰਕੜੇ->ਖਿੜਕੀ->pending.w;
                            ਅੰਕੜੇ->expected.h = ਅੰਕੜੇ->ਖਿੜਕੀ->pending.h;
                            X11_XResize_ਖਿੜਕੀ(display, ਅੰਕੜੇ->xwindow, ਅੰਕੜੇ->ਖਿੜਕੀ->pending.w, ਅੰਕੜੇ->ਖਿੜਕੀ->pending.h);
                        }
                    }
                }
                ਜੇ (ਅੰਕੜੇ->emit_ਮਾਪ_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(ਅੰਕੜੇ, &ਅੰਕੜੇ->pending_xconfigure);
                    ਅੰਕੜੇ->emit_ਮਾਪ_move_after_property_notify = false;
                }
                ਜੇ ((flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS)) {
                    ਜੇ (ਅੰਕੜੇ->pending_move) {
                        Dispatch_ਖਿੜਕੀ_Move(_this, ਅੰਕੜੇ, &ਅੰਕੜੇ->pending_move_ਬਿੰਦੂ);
                        ਅੰਕੜੇ->pending_move = false;
                    }
                }
            }
            ਜੇ (ਬਦਲਿਆ & SDL_ਖਿੜਕੀ_OCCLUDED) {
                SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, (flags & SDL_ਖਿੜਕੀ_OCCLUDED) ? SDL_EVENT_ਖਿੜਕੀ_OCCLUDED : SDL_EVENT_ਖਿੜਕੀ_EXPOSED, 0, 0);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            ਪੂਰਨ format;
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ nitems, ਬਾਈਟਾਂ_after;
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *prop_ਅੰਕੜੇ = ਨਿਰਾ;

            ਜੇ (X11_XGet_ਖਿੜਕੀ_Property(display, ਅੰਕੜੇ->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &ਬਾਈਟਾਂ_after, &prop_ਅੰਕੜੇ) == Success) {
                ਜੇ (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_ਅੰਕੜੇ;

                    ਜੇ ((state == 0 || state == 3) && !ਅੰਕੜੇ->ਖਿੜਕੀ->is_hiding && !(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
                        // Withdrawn or Iconic
                        ਜੇ (!(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED)) {
                            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MINIMIZED, 0, 0);
                            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_OCCLUDED, 0, 0);
                        }
                    } ਨਹੀਂਤਾਂ ਜੇ (state == 1) { // NormalState
                        ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED) {
                            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESTORED, 0, 0);
                            SDL_Send_ਖਿੜਕੀ_Event(ਅੰਕੜੇ->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_ਅੰਕੜੇ);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } ਨਹੀਂਤਾਂ ਜੇ (xevent->xproperty.atom == videodata->atoms.NET_ਚੌਖਟਾ_EXTENTS) {
            X11_Get_Border_ਮੁੱਲਾਂ(ਅੰਕੜੇ);
            ਜੇ (ਅੰਕੜੇ->ਮਾਪ_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                ਅੰਕੜੇ->ਮਾਪ_move_event_flags &= ~X11_ਮਾਪ_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            ਜੇ (!(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) && ਅੰਕੜੇ->toggle_borders) {
                ਅੰਕੜੇ->toggle_borders = false;
                X11_ਸੈੱਟ_ਖਿੜਕੀ_Bordered(_this, ਅੰਕੜੇ->ਖਿੜਕੀ, !(ਅੰਕੜੇ->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS));
            }
        }
    } ਰੋਕੋ;

    ਹਾਲਤ SelectionNotify:
    {
        Atom ਨਿਸ਼ਾਨਾ = xevent->xselection.ਨਿਸ਼ਾਨਾ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.ਖਿੜਕੀ,
               xevent->xselection.requestor, xevent->xselection.ਨਿਸ਼ਾਨਾ);
#ਜੇ_ਅੰਤ
        ਜੇ (ਨਿਸ਼ਾਨਾ == ਅੰਕੜੇ->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, ਅੰਕੜੇ->xwindow, videodata->atoms.PRIMARY);

            ਜੇ (p.format == 8) {
                ਅੱਖਰ *saveptr = ਨਿਰਾ;
                ਅੱਖਰ *name = X11_XGetAtomName(display, ਨਿਸ਼ਾਨਾ);
                ਜੇ (name) {
                    ਅੱਖਰ *token = SDL_strtok_r((ਅੱਖਰ *)p.ਅੰਕੜੇ, "\r\n", &saveptr);
                    ਜਦੋਂ (token) {
                        ਜੇ ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_Send_Drop_ਪਾਠ(ਅੰਕੜੇ->ਖਿੜਕੀ, token);
                        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp("text/uri-list", name) == 0) {
                            ਜੇ (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(ਅੰਕੜੇ->ਖਿੜਕੀ, ਨਿਰਾ, token);
                            }
                        }
                        token = SDL_strtok_r(ਨਿਰਾ, "\r\n", &saveptr);
                    }
                    X11_XFree(name);
                }
                SDL_SendDropComplete(ਅੰਕੜੇ->ਖਿੜਕੀ);
            }
            X11_XFree(p.ਅੰਕੜੇ);

            // send reply
            SDL_zero(m);
            m.type = Client_ਸੁਨੇਹਾ;
            m.display = display;
            m.ਖਿੜਕੀ = ਅੰਕੜੇ->xdnd_ਸਰੋਤ;
            m.ਸੁਨੇਹਾ_type = videodata->atoms.Xdnd_ਮੁਕੰਮਲ;
            m.format = 32;
            m.ਅੰਕੜੇ.l[0] = ਅੰਕੜੇ->xwindow;
            m.ਅੰਕੜੇ.l[1] = 1;
            m.ਅੰਕੜੇ.l[2] = videodata->atoms.XdndActionCopy;
            X11_XSendEvent(display, ਅੰਕੜੇ->xdnd_ਸਰੋਤ, False, No_Event_ਨਕਾਬ, (XEvent *)&m);

            X11_XSync(display, False);
        }
    } ਰੋਕੋ;

    ਮੂਲ:
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.ਖਿੜਕੀ, xevent->type);
#ਜੇ_ਅੰਤ
    } ਰੋਕੋ;
    }
}

ਸਥਿਰ ਖਾਲੀ X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    ਪੂਰਨ i;

    ਜੇ (videodata && videodata->windowlist) {
        ਲਈ (i = 0; i < videodata->numwindows; ++i) {
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = videodata->windowlist[i];
            ਜੇ (ਅੰਕੜੇ && ਅੰਕੜੇ->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                ਜੇ (now >= ਅੰਕੜੇ->pending_focus_ਸਮਾਂ) {
                    ਜੇ (ਅੰਕੜੇ->pending_focus == PENDING_FOCUS_ਵਿੱਚ) {
                        X11_Dispatch_Focus_ਵਿੱਚ(_this, ਅੰਕੜੇ);
                    } ਨਹੀਂਤਾਂ {
                        X11_Dispatch_Focus_ਬਾਹਰਲਾ(_this, ਅੰਕੜੇ);
                    }
                    ਅੰਕੜੇ->pending_focus = PENDING_FOCUS_NONE;
                }
            }
        }
    }
}

ਸਥਿਰ Bool isAnyEvent(Display *display, XEvent *ev, XPointer arg)
{
    ਵਾਪਸ True;
}

ਸਥਿਰ bool X11_PollEvent(Display *display, XEvent *event)
{
    ਜੇ (!X11_XCheckIfEvent(display, event, isAnyEvent, ਨਿਰਾ)) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

ਖਾਲੀ X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    Display *req_display = ਅੰਕੜੇ->request_display;
    ਖਿੜਕੀ_2 xwindow = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->xwindow;
    XClient_ਸੁਨੇਹਾ_Event event;

    SDL_zero(event);
    event.type = Client_ਸੁਨੇਹਾ;
    event.display = req_display;
    event.send_event = True;
    event.ਸੁਨੇਹਾ_type = ਅੰਕੜੇ->atoms._SDL_WAKEUP;
    event.format = 8;

    X11_XSendEvent(req_display, xwindow, False, No_Event_ਨਕਾਬ, (XEvent *)&event);
    /* XSendEvent returns a status and it could be BadValue or BadWindow. If an
      error happens it is an SDL's internal error and there is nothing we can do here. */
    X11_XFlush(req_display);
}

ਪੂਰਨ X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    ਜੇ (X11_PollEvent(display, &xevent)) {
        // Fall through
    } ਨਹੀਂਤਾਂ ਜੇ (timeoutNS == 0) {
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        ਪੂਰਨ err = SDL_IOReady(Connection_ਸੰਖਿਆ(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        ਜੇ (err > 0) {
            ਜੇ (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                ਵਾਪਸ 1;
            }
        } ਨਹੀਂਤਾਂ ਜੇ (err == 0) {
            // Timeout
            ਵਾਪਸ 0;
        } ਨਹੀਂਤਾਂ {
            // Error returned from poll()/select()

            ਜੇ (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                ਵਾਪਸ 1;
            } ਨਹੀਂਤਾਂ {
                ਵਾਪਸ err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    ਵਾਪਸ 1;
}

ਖਾਲੀ X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    XEvent xevent;
    ਪੂਰਨ i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    ਲਈ (i = 0; i < _this->ਅੰਕ_displays; ++i) {
        ਜੇ (_this->displays[i]->ਅੰਦਰੂਨੀ->ਬਹੁਲਕ_switch_deadline_ns) {
            ਜੇ (_this->displays[i]->fullscreen_ਖਿੜਕੀ) {
                _this->displays[i]->ਅੰਦਰੂਨੀ->ਬਹੁਲਕ_switch_deadline_ns = 0;
            } ਨਹੀਂਤਾਂ ਜੇ (SDL_GetTicksNS() >= _this->displays[i]->ਅੰਦਰੂਨੀ->ਬਹੁਲਕ_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_ਸੈੱਟ_Display_ਬਹੁਲਕ_For_Display(_this->displays[i], ਨਿਰਾ);
                _this->displays[i]->ਅੰਦਰੂਨੀ->ਬਹੁਲਕ_switch_deadline_ns = 0;
            }
        }
    }

    ਜੇ (ਅੰਕੜੇ->ਆਖਰੀ_ਬਹੁਲਕ_change_deadline) {
        ਜੇ (SDL_GetTicks() >= ਅੰਕੜੇ->ਆਖਰੀ_ਬਹੁਲਕ_change_deadline) {
            ਅੰਕੜੇ->ਆਖਰੀ_ਬਹੁਲਕ_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    ਜੇ (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        ਜੇ (!ਅੰਕੜੇ->screensaver_activity || now >= (ਅੰਕੜੇ->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(ਅੰਕੜੇ->display);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#ਜੇ_ਅੰਤ

            ਅੰਕੜੇ->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    ਜਦੋਂ (X11_PollEvent(ਅੰਕੜੇ->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    ਲਈ (i = 0; i < ਅੰਕੜੇ->numwindows; ++i) {
        ਜੇ (ਅੰਕੜੇ->windowlist[i] != ਨਿਰਾ &&
            ਅੰਕੜੇ->windowlist[i]->flash_cancel_ਸਮਾਂ &&
            SDL_GetTicks() >= ਅੰਕੜੇ->windowlist[i]->flash_cancel_ਸਮਾਂ) {
            X11_Flash_ਖਿੜਕੀ(_this, ਅੰਕੜੇ->windowlist[i]->ਖਿੜਕੀ, SDL_FLASH_CANCEL);
        }
    }

    ਜੇ (ਅੰਕੜੇ->xinput_hierarchy_ਬਦਲਿਆ) {
        X11_Xinput2UpdateDevices(_this);
        ਅੰਕੜੇ->xinput_hierarchy_ਬਦਲਿਆ = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    ਪੂਰਨ dummy;
    ਪੂਰਨ major_ਸੰਸਕਰਣ, minor_ਸੰਸਕਰਣ;
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
    ਜੇ (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        ਵਾਪਸ true;
    }

    ਜੇ (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    ਜੇ (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        ਜੇ (!X11_XScreenSaverQueryExtension(ਅੰਕੜੇ->display, &dummy, &dummy) ||
            !X11_XScreen_Saver_Query_ਸੰਸਕਰਣ(ਅੰਕੜੇ->display,
                                          &major_ਸੰਸਕਰਣ, &minor_ਸੰਸਕਰਣ) ||
            major_ਸੰਸਕਰਣ < 1 || (major_ਸੰਸਕਰਣ == 1 && minor_ਸੰਸਕਰਣ < 1)) {
            ਵਾਪਸ SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(ਅੰਕੜੇ->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(ਅੰਕੜੇ->display);
        ਵਾਪਸ true;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ SDL_Unsupported();
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
