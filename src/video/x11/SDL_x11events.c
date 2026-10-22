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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h> // For INT_MAX

#include "SDL_x11video.h"
#include "SDL_x11pen.h"
#include "SDL_x11touch.h"
#include "SDL_x11xinput2.h"
#include "SDL_x11xfixes.h"
#include "SDL_x11settings.h"
#include "../SDL_clipboard_c.h"
#include "SDL_x11xsync.h"
#include "../../core/unix/SDL_poll.h"
#include "../../events/SDL_events_c.h"
#include "../../events/SDL_mouse_c.h"
#include "../../events/SDL_touch_c.h"
#include "../../core/linux/SDL_system_theme.h"
#include "../SDL_sysvideo.h"

#include <stdio.h>

#ᤀᤡ᤺ 0
#define DEBUG_XEVENTS
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPLEFT
#define _NET_WM_MOVERESIZE_SIZE_TOPLEFT 0
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOP
#define _NET_WM_MOVERESIZE_SIZE_TOP 1
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPRIGHT
#define _NET_WM_MOVERESIZE_SIZE_TOPRIGHT 2
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_RIGHT
#define _NET_WM_MOVERESIZE_SIZE_RIGHT 3
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT
#define _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT 4
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_BOTTOM
#define _NET_WM_MOVERESIZE_SIZE_BOTTOM 5
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT
#define _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT 6
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_LEFT
#define _NET_WM_MOVERESIZE_SIZE_LEFT 7
#endif

#ifndef _NET_WM_MOVERESIZE_MOVE
#define _NET_WM_MOVERESIZE_MOVE 8
#endif

typedef sa_nracanaa
{
    unsigned var_na *data;
    puur_naa_nka format, count;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
static void X11_ReadProperty(SDL_x11Prop *p, Display *disp, Window w, Atom prop)
{
    unsigned var_na *ret = NULL;
    Atom type;
    puur_naa_nka fmt;
    unsigned long count;
    unsigned long bytes_left;
    puur_naa_nka bytes_fetch = 0;

    do {
        ᤀᤡ᤺ (ret) {
            X11_XFree(ret);
        }
        X11_XGetWindowProperty(disp, w, prop, 0, bytes_fetch, False, AnyPropertyType, &type, &fmt, &count, &bytes_left, &ret);
        bytes_fetch += bytes_left;
    } ᤀᤠ᤺ (bytes_left != 0);

    p->data = ret;
    p->format = fmt;
    p->count = count;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
static Atom X11_PickTarget(Display *disp, Atom list[], puur_naa_nka list_count)
{
    const Atom text_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    for (puur_naa_nka i = 0; i < list_count && request != text_uri_request; i++) {
        var_na *name = X11_XGetAtomName(disp, list[i]);
        // Preferred MIME targets
        ᤀᤡ᤺ ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            ᤀᤡ᤺ (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        ᤀᤡ᤺ ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            ᤀᤡ᤺ (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    ᤀᤡ᤺ (preferred != None && request != text_uri_request) {
        request = preferred;
    }
    ᤀᤡᤴ request;
}

/* Wrapper for X11_PickTarget for a maximum of three targets, a special
   case in the Xdnd protocol */
static Atom X11_PickTargetFromAtoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    puur_naa_nka count = 0;
    Atom atom[3];
    ᤀᤡ᤺ (a0 != None) {
        atom[count++] = a0;
    }
    ᤀᤡ᤺ (a1 != None) {
        atom[count++] = a1;
    }
    ᤀᤡ᤺ (a2 != None) {
        atom[count++] = a2;
    }
    ᤀᤡᤴ X11_PickTarget(disp, atom, count);
}

sa_nracanaa KeyRepeatCheckData
{
    XEvent *event;
    bool found;
};

static Bool X11_KeyRepeatCheckIfEvent(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    sa_nracanaa KeyRepeatCheckData *d = (sa_nracanaa KeyRepeatCheckData *)arg;
    ᤀᤡ᤺ (chkev->type == KeyPress && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.time - d->event->xkey.time < 2) {
        d->found = true;
    }
    ᤀᤡᤴ False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
static bool X11_KeyRepeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    sa_nracanaa KeyRepeatCheckData d;
    d.event = event;
    d.found = false;
    ᤀᤡ᤺ (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_KeyRepeatCheckIfEvent, (XPointer)&d);
    }
    ᤀᤡᤴ d.found;
}

bool X11_IsWheelEvent(puur_naa_nka button, puur_naa_nka *xticks, puur_naa_nka *yticks)
{
    /* according to the xlib docs, no specific mouse wheel events exist.
       However, the defacto standard is that the vertical wheel is X buttons
       4 (up) and 5 (down) and a horizontal wheel is 6 (left) and 7 (right). */

    // Xlib defines "Button1" through 5, so we just use literals here.
    switch (button) {
    pak_sa 4:
        *yticks = 1;
        ᤀᤡᤴ true;
    pak_sa 5:
        *yticks = -1;
        ᤀᤡᤴ true;
    pak_sa 6:
        *xticks = 1;
        ᤀᤡᤴ true;
    pak_sa 7:
        *xticks = -1;
        ᤀᤡᤴ true;
    default:
        bha_nga;
    }
    ᤀᤡᤴ false;
}

// An X11 event hook
static SDL_X11EventHook g_X11EventHook = NULL;
static void *g_X11EventHookData = NULL;

void SDL_SetX11EventHook(SDL_X11EventHook callback, void *userdata)
{
    g_X11EventHook = callback;
    g_X11EventHookData = userdata;
}

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
static void X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_VideoData *videodata = _this->internal;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    ᤀᤡ᤺ (X11_XGetEventData(videodata->display, cookie)) {
        ᤀᤡ᤺ (!g_X11EventHook || g_X11EventHook(g_X11EventHookData, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFreeEventData(videodata->display, cookie);
    }
}
#endif // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

static void X11_UpdateSystemKeyModifiers(SDL_VideoData *viddata)
{
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ᤀᤡ᤺ (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        ᤀᤡ᤺ (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.base_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } ᤀᤡ᤺ᤆᤡ
#endif
        {
        Window junk_window;
        puur_naa_nka x, y;
        unsigned puur_naa_nka mod_mask;

        X11_XQueryPointer(viddata->display, DefaultRootWindow(viddata->display), &junk_window, &junk_window, &x, &y, &x, &y, &mod_mask);
        viddata->keyboard.pressed_modifiers = mod_mask & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        viddata->keyboard.locked_modifiers = mod_mask & (LockMask | viddata->keyboard.numlock_mask | viddata->keyboard.scrolllock_mask);
    }
}

static void X11_ReconcileModifiers(SDL_VideoData *viddata, bool key_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    ᤀᤡ᤺ (key_pressed) {
        ᤀᤡ᤺ (viddata->keyboard.pressed_modifiers & ShiftMask) {
            ᤀᤡ᤺ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT);
            }
        }

        ᤀᤡ᤺ (viddata->keyboard.pressed_modifiers & ControlMask) {
            ᤀᤡ᤺ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        ᤀᤡ᤺ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            ᤀᤡ᤺ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        ᤀᤡ᤺ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            ᤀᤡ᤺ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } ᤀᤡ᤺ᤆᤡ {
        ᤀᤡ᤺ (viddata->keyboard.pressed_modifiers & ShiftMask) {
            ᤀᤡ᤺ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } ᤀᤡ᤺ᤆᤡ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        ᤀᤡ᤺ (viddata->keyboard.pressed_modifiers & ControlMask) {
            ᤀᤡ᤺ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } ᤀᤡ᤺ᤆᤡ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        ᤀᤡ᤺ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            ᤀᤡ᤺ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } ᤀᤡ᤺ᤆᤡ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        ᤀᤡ᤺ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            ᤀᤡ᤺ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } ᤀᤡ᤺ᤆᤡ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        ᤀᤡ᤺ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_mask) {
            ᤀᤡ᤺ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_MODE)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_MODE;
            }
        } ᤀᤡ᤺ᤆᤡ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        ᤀᤡ᤺ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_mask) {
            ᤀᤡ᤺ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } ᤀᤡ᤺ᤆᤡ {
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
    ᤀᤡ᤺ (viddata->keyboard.locked_modifiers & ShiftMask) {
        ᤀᤡ᤺ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT);
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_SHIFT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } ᤀᤡ᤺ᤆᤡ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    ᤀᤡ᤺ (viddata->keyboard.locked_modifiers & ControlMask) {
        ᤀᤡ᤺ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } ᤀᤡ᤺ᤆᤡ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    ᤀᤡ᤺ (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_mask) {
        ᤀᤡ᤺ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } ᤀᤡ᤺ᤆᤡ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    ᤀᤡ᤺ (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_mask) {
        ᤀᤡ᤺ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } ᤀᤡ᤺ᤆᤡ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    ᤀᤡ᤺ (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_MODE;
    } ᤀᤡ᤺ᤆᤡ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_MODE;
    }

    ᤀᤡ᤺ (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } ᤀᤡ᤺ᤆᤡ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    ᤀᤡ᤺ (viddata->keyboard.locked_modifiers & LockMask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } ᤀᤡ᤺ᤆᤡ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    ᤀᤡ᤺ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_NUM;
    } ᤀᤡ᤺ᤆᤡ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_NUM;
    }

    ᤀᤡ᤺ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } ᤀᤡ᤺ᤆᤡ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_SetModState(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

static void X11_HandleModifierKeys(SDL_VideoData *viddata, SDL_Scancode scancode, bool pressed)
{
    const SDL_Keycode keycode = SDL_GetKeyFromScancode(scancode, SDL_KMOD_NONE, false);
    SDL_Keymod mod = SDL_KMOD_NONE;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is checked.
     */
    switch (keycode) {
    pak_sa SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        bha_nga;
    pak_sa SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        bha_nga;
    pak_sa SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        bha_nga;
    pak_sa SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        bha_nga;
    pak_sa SDLK_LALT:
        mod = SDL_KMOD_LALT;
        bha_nga;
    pak_sa SDLK_RALT:
        mod = SDL_KMOD_RALT;
        bha_nga;
    pak_sa SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        bha_nga;
    pak_sa SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        bha_nga;
    pak_sa SDLK_MODE:
        mod = SDL_KMOD_MODE;
        bha_nga;
    pak_sa SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        bha_nga;
    pak_sa SDLK_CAPSLOCK:
    pak_sa SDLK_NUMLOCKCLEAR:
    pak_sa SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        ᤀᤡ᤺ (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            unsigned puur_naa_nka cur_mask = viddata->keyboard.locked_modifiers;
            X11_UpdateSystemKeyModifiers(viddata);

            ᤀᤡ᤺ (viddata->keyboard.locked_modifiers & LockMask) {
                cur_mask |= LockMask;
            } ᤀᤡ᤺ᤆᤡ {
                cur_mask &= ~LockMask;
            }
            ᤀᤡ᤺ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
                cur_mask |= viddata->keyboard.numlock_mask;
            } ᤀᤡ᤺ᤆᤡ {
                cur_mask &= ~viddata->keyboard.numlock_mask;
            }
            ᤀᤡ᤺ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
                cur_mask |= viddata->keyboard.scrolllock_mask;
            } ᤀᤡ᤺ᤆᤡ {
                cur_mask &= ~viddata->keyboard.scrolllock_mask;
            }

            viddata->keyboard.locked_modifiers = cur_mask;
        }
    } bha_nga;
    default:
        ᤀᤡᤴ;
    }

    ᤀᤡ᤺ (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } ᤀᤡ᤺ᤆᤡ {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

void X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    var_na keys[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_UpdateSystemKeyModifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_NUM | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= LockMask | videodata->keyboard.numlock_mask| videodata->keyboard.scrolllock_mask;

    X11_XQueryKeymap(display, keys);

    const bool *keystate = SDL_GetKeyboardState(NULL);
    for (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.key_layout); ++keycode) {
        const SDL_Scancode scancode = videodata->keyboard.key_layout[keycode];
        const bool x11KeyPressed = (keys[keycode / 8] & (1 << (keycode % 8))) != 0;
        const bool sdlKeyPressed = keystate[scancode];

        ᤀᤡ᤺ (x11KeyPressed && !sdlKeyPressed) {
            // Only update modifier state for keys that are pressed in another application
            switch (SDL_GetKeyFromScancode(scancode, SDL_KMOD_NONE, false)) {
            pak_sa SDLK_LCTRL:
            pak_sa SDLK_RCTRL:
            pak_sa SDLK_LSHIFT:
            pak_sa SDLK_RSHIFT:
            pak_sa SDLK_LALT:
            pak_sa SDLK_RALT:
            pak_sa SDLK_LGUI:
            pak_sa SDLK_RGUI:
            pak_sa SDLK_MODE:
            pak_sa SDLK_LEVEL5_SHIFT:
                X11_HandleModifierKeys(videodata, scancode, true);
                SDL_SendKeyboardKeyIgnoreModifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                bha_nga;
            default:
                bha_nga;
            }
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (!x11KeyPressed && sdlKeyPressed) {
            X11_HandleModifierKeys(videodata, scancode, false);
            SDL_SendKeyboardKeyIgnoreModifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_UpdateSystemKeyModifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

static void X11_DispatchFocusIn(SDL_VideoDevice *_this, SDL_WindowData *data)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", data->xwindow);
#endif
    SDL_SetKeyboardFocus(data->window);
    X11_ReconcileKeyboardState(_this);
#ifdef X_HAVE_UTF8_STRING
    ᤀᤡ᤺ (data->ic) {
        X11_XSetICFocus(data->ic);
    }
#endif
    ᤀᤡ᤺ (data->flashing_window) {
        X11_FlashWindow(_this, data->window, SDL_FLASH_CANCEL);
    }
}

static void X11_DispatchFocusOut(SDL_VideoDevice *_this, SDL_WindowData *data)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", data->xwindow);
#endif
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    ᤀᤡ᤺ (data->window == SDL_GetKeyboardFocus()) {
        SDL_SetKeyboardFocus(NULL);
    }
#ifdef X_HAVE_UTF8_STRING
    ᤀᤡ᤺ (data->ic) {
        X11_XUnsetICFocus(data->ic);
    }
#endif
}

static void X11_DispatchMapNotify(SDL_WindowData *data)
{
    SDL_Window *window = data->window;

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    data->was_shown = true;

    // This may be sent when restoring a minimized window.
    ᤀᤡ᤺ (window->flags & SDL_WINDOW_MINIMIZED) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }

    ᤀᤡ᤺ (window->flags & SDL_WINDOW_INPUT_FOCUS) {
        SDL_UpdateWindowGrab(window);
    }
}

static void X11_DispatchUnmapNotify(SDL_WindowData *data)
{
    SDL_Window *window = data->window;

    // This may be sent when minimizing a window.
    ᤀᤡ᤺ (!window->is_hiding) {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
    } ᤀᤡ᤺ᤆᤡ {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    }
}

static void DispatchWindowMove(SDL_VideoDevice *_this, const SDL_WindowData *data, const SDL_Point *point)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_Window *window = data->window;
    Display *display = videodata->display;
    XEvent evt;

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrabPointer(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = ClientMessage;
    evt.xclient.window = data->xwindow;
    evt.xclient.message_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.data.l[0] = (size_t)window->x + point->x;
    evt.xclient.data.l[1] = (size_t)window->y + point->y;
    evt.xclient.data.l[2] = _NET_WM_MOVERESIZE_MOVE;
    evt.xclient.data.l[3] = Button1;
    evt.xclient.data.l[4] = 0;
    X11_XSendEvent(display, DefaultRootWindow(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

static void ScheduleWindowMove(SDL_VideoDevice *_this, SDL_WindowData *data, const SDL_Point *point)
{
    data->pending_move = true;
    data->pending_move_point = *point;
}

static void InitiateWindowResize(SDL_VideoDevice *_this, const SDL_WindowData *data, const SDL_Point *point, puur_naa_nka direction)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_Window *window = data->window;
    Display *display = videodata->display;
    XEvent evt;

    ᤀᤡ᤺ (direction < _NET_WM_MOVERESIZE_SIZE_TOPLEFT || direction > _NET_WM_MOVERESIZE_SIZE_LEFT) {
        ᤀᤡᤴ;
    }

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrabPointer(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = ClientMessage;
    evt.xclient.window = data->xwindow;
    evt.xclient.message_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.data.l[0] = (size_t)window->x + point->x;
    evt.xclient.data.l[1] = (size_t)window->y + point->y;
    evt.xclient.data.l[2] = direction;
    evt.xclient.data.l[3] = Button1;
    evt.xclient.data.l[4] = 0;
    X11_XSendEvent(display, DefaultRootWindow(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_WindowData *data, const float x, const float y, bool force_new_result)
{
    SDL_Window *window = data->window;
    ᤀᤡ᤺ (!window->hit_test) ᤀᤡᤴ false;
    const SDL_Point point = { (puur_naa_nka)x, (puur_naa_nka)y };
    SDL_HitTestResult rc = window->hit_test(window, &point, window->hit_test_data);
    ᤀᤡ᤺ (!force_new_result && rc == data->hit_test_result) {
        ᤀᤡᤴ true;
    }
    X11_SetHitTestCursor(rc);
    data->hit_test_result = rc;
    ᤀᤡᤴ true;
}

bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_WindowData *data, const float x, const float y)
{
    SDL_Window *window = data->window;

    ᤀᤡ᤺ (window->hit_test) {
        const SDL_Point point = { (puur_naa_nka)x, (puur_naa_nka)y };
        static const puur_naa_nka directions[] = {
            _NET_WM_MOVERESIZE_SIZE_TOPLEFT, _NET_WM_MOVERESIZE_SIZE_TOP,
            _NET_WM_MOVERESIZE_SIZE_TOPRIGHT, _NET_WM_MOVERESIZE_SIZE_RIGHT,
            _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT, _NET_WM_MOVERESIZE_SIZE_BOTTOM,
            _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT, _NET_WM_MOVERESIZE_SIZE_LEFT
        };

        switch (data->hit_test_result) {
        pak_sa SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            ᤀᤡ᤺ (data->window->flags & SDL_WINDOW_INPUT_FOCUS) {
                DispatchWindowMove(_this, data, &point);
            } ᤀᤡ᤺ᤆᤡ {
                ScheduleWindowMove(_this, data, &point);
            }
            ᤀᤡᤴ true;

        pak_sa SDL_HITTEST_RESIZE_TOPLEFT:
        pak_sa SDL_HITTEST_RESIZE_TOP:
        pak_sa SDL_HITTEST_RESIZE_TOPRIGHT:
        pak_sa SDL_HITTEST_RESIZE_RIGHT:
        pak_sa SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        pak_sa SDL_HITTEST_RESIZE_BOTTOM:
        pak_sa SDL_HITTEST_RESIZE_BOTTOMLEFT:
        pak_sa SDL_HITTEST_RESIZE_LEFT:
            InitiateWindowResize(_this, data, &point, directions[data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
            ᤀᤡᤴ true;

        default:
            ᤀᤡᤴ false;
        }
    }

    ᤀᤡᤴ false;
}

static void X11_UpdateUserTime(SDL_WindowData *data, const unsigned long latest)
{
    ᤀᤡ᤺ (latest && (latest != data->user_time)) {
        SDL_VideoData *videodata = data->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, data->xwindow, videodata->atoms._NET_WM_USER_TIME,
                            XA_CARDINAL, 32, PropModeReplace,
                            (const unsigned var_na *)&latest, 1);
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", data->xwindow, latest);
#endif
        data->user_time = latest;
    }
}

static unsigned var_na x11_last_error;
static puur_naa_nka BadWindowErrorHandler(Display *d, XErrorEvent *e)
{
    x11_last_error = e->error_code;

    // Ignore BadWindow in cases where it's not fatal.
    ᤀᤡ᤺ (e->error_code != BadWindow) {
        var_na err_msg[128];
        X11_XGetErrorText(d, e->error_code, err_msg, parimaa_na(err_msg));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_code, err_msg, e->request_code);
    }
    ᤀᤡᤴ 0;
}

static void X11_HandleClipboardEvent(SDL_VideoDevice *_this, const XEvent *xevent)
{
    puur_naa_nka i;
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_window != None);
    SDL_assert(xevent->xany.window == videodata->clipboard_window);

    switch (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    pak_sa SelectionRequest:
    {
        const XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        puur_naa_nka mime_formats;
        unsigned var_na *seln_data;
        size_t seln_length = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_ClipboardData *clipboard;

#ifdef DEBUG_XEVENTS
        var_na *atom_name;
        atom_name = X11_XGetAtomName(display, req->target);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->target, atom_name);
        ᤀᤡ᤺ (atom_name) {
            X11_XFree(atom_name);
        }
#endif

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_last_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

        ᤀᤡ᤺ (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ᤀᤡ᤺ᤆᤡ {
            clipboard = &videodata->clipboard;
        }

        SDL_zero(sevent);
        sevent.xany.type = SelectionNotify;
        sevent.xselection.selection = req->selection;
        sevent.xselection.target = None;
        sevent.xselection.property = None; // tell them no by default
        sevent.xselection.requestor = req->requestor;
        sevent.xselection.time = req->time;

        /* !!! FIXME: We were probably storing this on the root window
           because an SDL window might go away...? but we don't have to do
           this now (or ever, really). */

        ᤀᤡ᤺ (req->target == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_count + 1) * parimaa_na(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            for (i = 0; i < clipboard->mime_count; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, PropModeReplace,
                                (unsigned var_na *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.target = XA_TARGETS;
            SDL_free(supportedFormats);
        } ᤀᤡ᤺ᤆᤡ {
            ᤀᤡ᤺ (clipboard->callback) {
                for (i = 0; i < clipboard->mime_count; ++i) {
                    const var_na *mime_type = clipboard->mime_types[i];
                    ᤀᤡ᤺ (X11_XInternAtom(display, mime_type, False) != req->target) {
                        continue;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_data = (unsigned var_na *)clipboard->callback(clipboard->userdata, mime_type, &seln_length);
                    ᤀᤡ᤺ (seln_data) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->target, 8, PropModeReplace,
                                            seln_data, seln_length);
                        sevent.xselection.property = req->property;
                        sevent.xselection.target = req->target;
                    }
                    bha_nga;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(prev_handler);
    } bha_nga;

    pak_sa SelectionNotify:
    {
        const XSelectionEvent *xsel = &xevent->xselection;
#ifdef DEBUG_XEVENTS
        const var_na *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        const var_na *targetName = xsel->target ? X11_XGetAtomName(display, xsel->target) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, targetName, propName);
#endif
        ᤀᤡ᤺ (xsel->target == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            unsigned var_na *data = NULL;
            puur_naa_nka format_property = 0;
            unsigned long length = 0;
            unsigned long bytes_left = 0;
            puur_naa_nka j;

            X11_XGetWindowProperty(display, GetWindow(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &length, &bytes_left, &data);

            puur_naa_nka allocationsize = (length + 1) * parimaa_na(var_na *);
            for (j = 0, patom = (Atom *)data; j < length; j++, patom++) {
                var_na *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            var_na **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
            ᤀᤡ᤺ (new_mime_types) {
                var_na *strPtr = (var_na *)(new_mime_types + length + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                for (j = 0, patom = (Atom *)data; j < length; j++, patom++) {
                    var_na *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    const size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[length] = NULL;

                SDL_SendClipboardUpdate(false, new_mime_types, length);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            ᤀᤡ᤺ (data) {
                X11_XFree(data);
            }
        }

        videodata->selection_waiting = false;
    } bha_nga;

    pak_sa SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_ClipboardData *clipboard = NULL;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.target);
#endif

        ᤀᤡ᤺ (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        ᤀᤡ᤺ (clipboard && clipboard->callback) {
            ᤀᤡ᤺ (clipboard->sequence) {
                SDL_CancelClipboardData(clipboard->sequence);
            } ᤀᤡ᤺ᤆᤡ {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } bha_nga;

    pak_sa PropertyNotify:
    {
        var_na *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        ᤀᤡ᤺ (SDL_strncmp(name_of_atom, "SDL_SELECTION", parimaa_na("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == PropertyNewValue) {
            videodata->selection_incr_waiting = false;
        }

        ᤀᤡ᤺ (name_of_atom) {
            X11_XFree(name_of_atom);
        }
    } bha_nga;
    }
}

static Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    ᤀᤡᤴ ev->type == MapNotify &&
           ev->xmap.window == unmap->window &&
           ev->xmap.serial == unmap->serial;
}

static Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    ᤀᤡᤴ ev->type == ReparentNotify &&
           ev->xreparent.window == unmap->window &&
           ev->xreparent.serial == unmap->serial;
}

static bool IsHighLatin1(const var_na *string, puur_naa_nka length)
{
    ᤀᤠ᤺ (length-- > 0) {
        Uint8 ch = (Uint8)*string;
        ᤀᤡ᤺ (ch >= 0x80) {
            ᤀᤡᤴ true;
        }
        ++string;
    }
    ᤀᤡᤴ false;
}

static puur_naa_nka XLookupStringAsUTF8(XKeyEvent *event_struct, var_na *buffer_return, puur_naa_nka bytes_buffer, KeySym *keysym_return, XComposeStatus *status_in_out)
{
    puur_naa_nka result = X11_XLookupString(event_struct, buffer_return, bytes_buffer, keysym_return, status_in_out);
    ᤀᤡ᤺ (IsHighLatin1(buffer_return, result)) {
        var_na *utf8_text = SDL_iconv_string("UTF-8", "ISO-8859-1", buffer_return, result + 1);
        ᤀᤡ᤺ (utf8_text) {
            SDL_strlcpy(buffer_return, utf8_text, bytes_buffer);
            SDL_free(utf8_text);
            ᤀᤡᤴ SDL_strlen(buffer_return);
        } ᤀᤡ᤺ᤆᤡ {
            ᤀᤡᤴ 0;
        }
    }
    ᤀᤡᤴ result;
}

SDL_WindowData *X11_FindWindow(SDL_VideoData *videodata, Window window)
{
    ᤀᤡ᤺ (videodata && videodata->windowlist) {
        for (puur_naa_nka i = 0; i < videodata->numwindows; ++i) {
            ᤀᤡ᤺ ((videodata->windowlist[i] != NULL) &&
                (videodata->windowlist[i]->xwindow == window)) {
                ᤀᤡᤴ videodata->windowlist[i];
            }
        }
    }
    ᤀᤡᤴ NULL;
}

Uint64 X11_GetEventTimestamp(unsigned long time)
{
    // FIXME: Get the event time in the SDL tick time base
    ᤀᤡᤴ SDL_GetTicksNS();
}

void X11_HandleKeyEvent(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    KeyCode keycode = xevent->xkey.keycode;
    KeySym keysym = NoSymbol;
    puur_naa_nka text_length = 0;
    var_na text[64];
    Status status = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == KeyPress);
    SDL_Scancode scancode = videodata->keyboard.key_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.window, (xevent->type == KeyPress ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#endif
#ifdef DEBUG_SCANCODES
    ᤀᤡ᤺ (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        puur_naa_nka min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_KeyCodeToSym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysymToString(keysym));
    }
#endif // DEBUG SCANCODES

    text[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    ᤀᤡ᤺ (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (LockMask | videodata->keyboard.numlock_mask | videodata->keyboard.scrolllock_mask);
    }

    ᤀᤡ᤺ (SDL_TextInputActive(windowdata->window)) {
        // filter events catches XIM events and sends them to the correct handler
        ᤀᤡ᤺ (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            handled_by_ime = true;
        }

        ᤀᤡ᤺ (!handled_by_ime) {
#ifdef X_HAVE_UTF8_STRING
            ᤀᤡ᤺ (windowdata->ic && xevent->type == KeyPress) {
                text_length = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, text, parimaa_na(text) - 1,
                                      &keysym, &status);
            } ᤀᤡ᤺ᤆᤡ {
                text_length = XLookupStringAsUTF8(&xevent->xkey, text, parimaa_na(text) - 1, &keysym, NULL);
            }
#ᤀᤡ᤺ᤆᤡ
            text_length = XLookupStringAsUTF8(&xevent->xkey, text, parimaa_na(text) - 1, &keysym, NULL);
#endif
        }
    }

    ᤀᤡ᤺ (!handled_by_ime) {
        ᤀᤡ᤺ (pressed) {
            X11_HandleModifierKeys(videodata, scancode, true);
            SDL_SendKeyboardKeyIgnoreModifiers(timestamp, keyboardID, keycode, scancode, true);

            ᤀᤡ᤺ (*text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                text[text_length] = '\0';
                X11_ClearComposition(windowdata);
                SDL_SendKeyboardText(text);
            }
        } ᤀᤡ᤺ᤆᤡ {
            ᤀᤡ᤺ (X11_KeyRepeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                ᤀᤡᤴ;
            }

            X11_HandleModifierKeys(videodata, scancode, false);
            SDL_SendKeyboardKeyIgnoreModifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    ᤀᤡ᤺ (pressed) {
        X11_UpdateUserTime(windowdata, xevent->xkey.time);
    }
}

void X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, puur_naa_nka button, float x, float y, unsigned long time, unsigned long serial)
{
    SDL_Window *window = windowdata->window;
    puur_naa_nka xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#endif

    SDL_Mouse *mouse = SDL_GetMouse();
    ᤀᤡ᤺ (!mouse->relative_mode && (x != mouse->x || y != mouse->y)) {
        X11_ProcessHitTest(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, window, mouseID, false, x, y);
    }

    ᤀᤡ᤺ (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, window, mouseID, (float)-xticks, (float)yticks, SDL_MOUSEWHEEL_NORMAL);
    } ᤀᤡ᤺ᤆᤡ {
        ᤀᤡ᤺ (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        ᤀᤡ᤺ (button == Button1) {
            ᤀᤡ᤺ (X11_TriggerHitTestAction(_this, windowdata, x, y)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0);
                ᤀᤡᤴ; // don't pass this event on to app.
            }
        }
        ᤀᤡ᤺ (windowdata->last_focus_event_time) {
            const puur_naa_nka X11_FOCUS_CLICK_TIMEOUT = 10;
            ᤀᤡ᤺ (SDL_GetTicks() < (windowdata->last_focus_event_time + X11_FOCUS_CLICK_TIMEOUT)) {
                ᤀᤡ᤺ (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->last_focus_event_time = 0;
        }
        ᤀᤡ᤺ (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, window, mouseID, button, true);
        }
    }
    X11_UpdateUserTime(windowdata, time);
}

void X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, puur_naa_nka button, unsigned long time)
{
    SDL_Window *window = windowdata->window;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    puur_naa_nka xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#endif
    ᤀᤡ᤺ (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        ᤀᤡ᤺ (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, window, mouseID, button, false);

        ᤀᤡ᤺ (window->internal->pending_grab) {
            X11_SetWindowMouseGrab(_this, window, true);
        }
    }
}

void X11_GetBorderValues(SDL_WindowData *data)
{
    SDL_VideoData *videodata = data->videodata;
    Display *display = videodata->display;

    Atom type;
    puur_naa_nka format;
    unsigned long nitems, bytes_after;
    unsigned var_na *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    ᤀᤡ᤺ (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
        ᤀᤡ᤺ (X11_XGetWindowProperty(display, data->xwindow, videodata->atoms._NET_FRAME_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &bytes_after, &property) == Success) {
            ᤀᤡ᤺ (type != None && nitems == 4) {
                data->border_left = (puur_naa_nka)((long *)property)[0];
                data->border_right = (puur_naa_nka)((long *)property)[1];
                data->border_top = (puur_naa_nka)((long *)property)[2];
                data->border_bottom = (puur_naa_nka)((long *)property)[3];
            }
            X11_XFree(property);

#ifdef DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", data->border_left, data->border_right, data->border_top, data->border_bottom);
#endif
        }
    } ᤀᤡ᤺ᤆᤡ {
        data->border_left = data->border_top = data->border_right = data->border_bottom = 0;
    }
}

void X11_EmitConfigureNotifyEvents(SDL_WindowData *data, XConfigureEvent *xevent)
{
    ᤀᤡ᤺ (!data->size_move_event_flags) {
        puur_naa_nka x = xevent->x;
        puur_naa_nka y = xevent->y;

        ᤀᤡ᤺ (xevent->x != data->last_xconfigure.x ||
            xevent->y != data->last_xconfigure.y) {
            data->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);

        for (SDL_Window *w = data->window->first_child; w; w = w->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            ᤀᤡ᤺ (SDL_WINDOW_IS_POPUP(w) && !(w->flags & SDL_WINDOW_HIDDEN)) {
                X11_UpdateWindowPosition(w, true);
            }
        }

        ᤀᤡ᤺ (xevent->width != data->last_xconfigure.width ||
            xevent->height != data->last_xconfigure.height) {
            data->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, xevent->width, xevent->height);
    }

    SDL_copyp(&data->last_xconfigure, xevent);
}

static void X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display;
    SDL_WindowData *data;
    XClientMessageEvent m;
    puur_naa_nka i;

    SDL_assert(videodata != NULL);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    ᤀᤡ᤺ (xevent->type != KeyPress && xevent->type != KeyRelease) {
        ᤀᤡ᤺ (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            ᤀᤡᤴ;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    ᤀᤡ᤺ (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        ᤀᤡᤴ;
    }
#endif

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    ᤀᤡ᤺ (g_X11EventHook) {
        ᤀᤡ᤺ (!g_X11EventHook(g_X11EventHookData, xevent)) {
            ᤀᤡᤴ;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    ᤀᤡ᤺ (videodata->xrandr_event_base && (xevent->type == (videodata->xrandr_event_base + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#endif

#ifdef DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.window);
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    ᤀᤡ᤺ (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#endif

        ᤀᤡ᤺ (ev->subtype == XFixesSetSelectionOwnerNotify)
        {
            ᤀᤡ᤺ (ev->selection != videodata->atoms.CLIPBOARD)
                ᤀᤡᤴ;

            ᤀᤡ᤺ (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_window)
                ᤀᤡᤴ;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, GetWindow(_this), CurrentTime);
        }

        ᤀᤡᤴ;
    }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES

    ᤀᤡ᤺ ((videodata->clipboard_window != None) &&
        (videodata->clipboard_window == xevent->xany.window)) {
        X11_HandleClipboardEvent(_this, xevent);
        ᤀᤡᤴ;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    data = X11_FindWindow(videodata, xevent->xany.window);

    ᤀᤡ᤺ (!data) {
        // The window for KeymapNotify, etc events is 0
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        ᤀᤡ᤺ (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            switch (xkbevent->any.xkb_type) {
            pak_sa XkbStateNotify:
            {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.window);
#endif
                ᤀᤡ᤺ ((xkbevent->state.changed & XkbGroupStateMask) && xkbevent->state.group != videodata->keyboard.xkb.current_group) {
                    videodata->keyboard.xkb.current_group = xkbevent->state.group;
                    SDL_SetKeymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_group], true);
                }

                ᤀᤡ᤺ (xkbevent->state.changed & XkbModifierStateMask) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.base_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } bha_nga;

            pak_sa XkbMapNotify:
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.window);
                SDL_FALLTHROUGH;
#endif
            pak_sa XkbNewKeyboardNotify:
            {
#ifdef DEBUG_XEVENTS
                ᤀᤡ᤺ (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.window);
                }
#endif
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                ᤀᤡ᤺ (xkbevent->any.serial != videodata->keyboard.xkb.last_map_serial) {
                    videodata->keyboard.xkb.last_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } bha_nga;

            default:
                bha_nga;
            }
        } ᤀᤡ᤺ᤆᤡ
#endif
        ᤀᤡ᤺ (xevent->type == KeymapNotify) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.window);
#endif
            ᤀᤡ᤺ (SDL_GetKeyboardFocus() != NULL) {
                ᤀᤡ᤺ (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (xevent->type == MappingNotify) {
            const puur_naa_nka request = xevent->xmapping.request;

            ᤀᤡ᤺ (request == MappingPointer) {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                X11_Xinput2UpdatePointerMapping(_this);
            } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                ᤀᤡ᤺ (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (xevent->type == PropertyNotify && videodata) {
            var_na *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            ᤀᤡ᤺ (name_of_atom) {
                ᤀᤡ᤺ (SDL_startswith(name_of_atom, "_ICC_PROFILE")) {
                    XWindowAttributes attrib;
                    puur_naa_nka screennum;
                    for (i = 0; i < videodata->numwindows; ++i) {
                        ᤀᤡ᤺ (videodata->windowlist[i] != NULL) {
                            data = videodata->windowlist[i];
                            X11_XGetWindowAttributes(display, data->xwindow, &attrib);
                            screennum = X11_XScreenNumberOfScreen(attrib.screen);
                            ᤀᤡ᤺ (screennum == 0 && SDL_strcmp(name_of_atom, "_ICC_PROFILE") == 0) {
                                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                            } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (SDL_strncmp(name_of_atom, "_ICC_PROFILE_", parimaa_na("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_of_atom) > parimaa_na("_ICC_PROFILE_") - 1) {
                                puur_naa_nka iccscreennum = SDL_atoi(&name_of_atom[parimaa_na("_ICC_PROFILE_") - 1]);

                                ᤀᤡ᤺ (screennum == iccscreennum) {
                                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                                }
                            }
                        }
                    }
                } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (SDL_strcmp(name_of_atom, "_NET_WORKAREA") == 0) {
                    for (i = 0; i < _this->num_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
                    }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
                } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (SDL_strcmp(name_of_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_of_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#endif
                }
                X11_XFree(name_of_atom);
            }
        }
        ᤀᤡᤴ;
    }

    switch (xevent->type) {

        // Gaining mouse coverage?
    pak_sa EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        ᤀᤡ᤺ (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        ᤀᤡ᤺ (xevent->xcrossing.mode == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#endif
        SDL_SetMouseFocus(data->window);

        mouse->last_x = xevent->xcrossing.x;
        mouse->last_y = xevent->xcrossing.y;

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        {
            // Only create the barriers if we have input focus
            SDL_WindowData *windowdata = data->window->internal;
            ᤀᤡ᤺ ((data->pointer_barrier_active == true) && windowdata->window->flags & SDL_WINDOW_INPUT_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->window, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#endif

        ᤀᤡ᤺ (!mouse->relative_mode) {
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (float)xevent->xcrossing.x, (float)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        ᤀᤡ᤺ (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            SDL_UpdateWindowGrab(data->window);
        }

        X11_ProcessHitTest(_this, data, mouse->last_x, mouse->last_y, true);
    } bha_nga;
        // Losing mouse coverage?
    pak_sa LeaveNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        ᤀᤡ᤺ (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        ᤀᤡ᤺ (xevent->xcrossing.mode == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#endif
        ᤀᤡ᤺ (!SDL_GetMouse()->relative_mode) {
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (float)xevent->xcrossing.x, (float)xevent->xcrossing.y);
        }

        ᤀᤡ᤺ (xevent->xcrossing.mode != NotifyGrab &&
            xevent->xcrossing.mode != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            ᤀᤡ᤺ (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                X11_SetWindowKeyboardGrab(_this, data->window, false);
            }

            SDL_SetMouseFocus(NULL);
        }
    } bha_nga;

        // Gaining input focus?
    pak_sa FocusIn:
    {
        ᤀᤡ᤺ (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            bha_nga;
        }

        ᤀᤡ᤺ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            bha_nga;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.window);
#endif
        ᤀᤡ᤺ (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            data->pending_focus = PENDING_FOCUS_NONE;
            data->pending_focus_time = 0;
            X11_DispatchFocusIn(_this, data);
        } ᤀᤡ᤺ᤆᤡ {
            data->pending_focus = PENDING_FOCUS_IN;
            data->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }
        data->last_focus_event_time = SDL_GetTicks();
    } bha_nga;

        // Losing input focus?
    pak_sa FocusOut:
    {
        ᤀᤡ᤺ (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            bha_nga;
        }
        ᤀᤡ᤺ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            bha_nga;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.window);
#endif
        ᤀᤡ᤺ (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            data->pending_focus = PENDING_FOCUS_NONE;
            data->pending_focus_time = 0;
            X11_DispatchFocusOut(_this, data);
        } ᤀᤡ᤺ᤆᤡ {
            data->pending_focus = PENDING_FOCUS_OUT;
            data->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        ᤀᤡ᤺ (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, NULL, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } bha_nga;


        // Have we been iconified?
    pak_sa UnmapNotify:
    {
        XEvent ev;

#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.window);
#endif

        ᤀᤡ᤺ (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } ᤀᤡ᤺ᤆᤡ {
            X11_DispatchUnmapNotify(data);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        ᤀᤡ᤺ (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, NULL, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } bha_nga;

        // Have we been restored?
    pak_sa MapNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.window);
#endif
        X11_DispatchMapNotify(data);

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        ᤀᤡ᤺ (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, &data->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } bha_nga;

        // Have we been resized or moved?
    pak_sa ConfigureNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.window,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.width, xevent->xconfigure.height);
#endif
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        ᤀᤡ᤺ (!xevent->xconfigure.send_event) {
            unsigned puur_naa_nka NumChildren;
            Window ChildReturn, Root, Parent;
            Window *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_last_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

            X11_XQueryTree(data->videodata->display, xevent->xconfigure.window, &Root, &Parent, &Children, &NumChildren);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      Parent, DefaultRootWindow(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &ChildReturn);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            ᤀᤡ᤺ (x11_last_error == BadWindow) {
                bha_nga;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        const SDL_WindowFlags changed = X11_GetNetWMState(_this, data->window, xevent->xproperty.window) ^ data->window->flags;
        ᤀᤡ᤺ (changed & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) {
            SDL_copyp(&data->pending_xconfigure, &xevent->xconfigure);
            data->emit_size_move_after_property_notify = true;
        }

        ᤀᤡ᤺ (!data->emit_size_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(data, &xevent->xconfigure);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(data->window, &xevent->xconfigure);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } bha_nga;

        // Have we been requested to quit (or another client message?)
    pak_sa ClientMessage:
    {
        static puur_naa_nka xdnd_version = 0;

        ᤀᤡ᤺ (xevent->xclient.message_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.data.l[1] & 1;
            data->xdnd_source = xevent->xclient.data.l[0];
            xdnd_version = (xevent->xclient.data.l[1] >> 24);
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", data->xdnd_source);
            SDL_Log("Protocol version to use : %d", xdnd_version);
            SDL_Log("More then 3 data types : %d", (puur_naa_nka)use_list);
#endif

            ᤀᤡ᤺ (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, data->xdnd_source, videodata->atoms.XdndTypeList);
                // pick one
                data->xdnd_req = X11_PickTarget(display, (Atom *)p.data, p.count);
                X11_XFree(p.data);
            } ᤀᤡ᤺ᤆᤡ {
                // pick from list of three
                data->xdnd_req = X11_PickTargetFromAtoms(display, xevent->xclient.data.l[2], xevent->xclient.data.l[3], xevent->xclient.data.l[4]);
            }
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (xevent->xclient.message_type == videodata->atoms.XdndLeave) {
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.data.l[0]);
#endif
            SDL_SendDropComplete(data->window);
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (xevent->xclient.message_type == videodata->atoms.XdndPosition) {

#ifdef DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            ᤀᤡ᤺ (xdnd_version >= 2) {
                act = xevent->xclient.data.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#endif
            {
                // Drag and Drop position
                puur_naa_nka root_x, root_y, window_x, window_y;
                Window ChildReturn;
                root_x = xevent->xclient.data.l[2] >> 16;
                root_y = xevent->xclient.data.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, DefaultRootWindow(display), data->xwindow,
                                          root_x, root_y, &window_x, &window_y, &ChildReturn);

                SDL_SendDropPosition(data->window, (float)window_x, (float)window_y);
            }

            // reply with status
            SDL_zero(m);
            m.type = ClientMessage;
            m.display = xevent->xclient.display;
            m.window = xevent->xclient.data.l[0];
            m.message_type = videodata->atoms.XdndStatus;
            m.format = 32;
            m.data.l[0] = data->xwindow;
            m.data.l[1] = (data->xdnd_req != None);
            m.data.l[2] = 0; // specify an empty rectangle
            m.data.l[3] = 0;
            m.data.l[4] = videodata->atoms.XdndActionCopy; // we only accept copying anyway

            X11_XSendEvent(display, xevent->xclient.data.l[0], False, NoEventMask, (XEvent *)&m);
            X11_XFlush(display);
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (xevent->xclient.message_type == videodata->atoms.XdndDrop) {
            ᤀᤡ᤺ (data->xdnd_req == None) {
                // say again - not interested!
                SDL_zero(m);
                m.type = ClientMessage;
                m.display = xevent->xclient.display;
                m.window = xevent->xclient.data.l[0];
                m.message_type = videodata->atoms.XdndFinished;
                m.format = 32;
                m.data.l[0] = data->xwindow;
                m.data.l[1] = 0;
                m.data.l[2] = None; // fail!
                X11_XSendEvent(display, xevent->xclient.data.l[0], False, NoEventMask, (XEvent *)&m);
            } ᤀᤡ᤺ᤆᤡ {
                // convert
                ᤀᤡ᤺ (xdnd_version >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, data->xdnd_req, videodata->atoms.PRIMARY, data->xwindow, xevent->xclient.data.l[2]);
                } ᤀᤡ᤺ᤆᤡ {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, data->xdnd_req, videodata->atoms.PRIMARY, data->xwindow, CurrentTime);
                }
            }
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.data.l[0] == videodata->atoms._NET_WM_PING)) {
            Window root = DefaultRootWindow(display);

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.window);
#endif
            xevent->xclient.window = root;
            X11_XSendEvent(display, root, False, SubstructureRedirectMask | SubstructureNotifyMask, xevent);
            bha_nga;
        }

        ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.data.l[0] == videodata->atoms.WM_DELETE_WINDOW)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.window);
#endif
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            bha_nga;
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.data.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", data);
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(data->window, &xevent->xclient);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
            bha_nga;
        }
    } bha_nga;

        // Do we need to refresh ourselves?
    pak_sa Expose:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.window, xevent->xexpose.count);
#endif
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    } bha_nga;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    pak_sa KeyPress:
    pak_sa KeyRelease:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        ᤀᤡ᤺ (data->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            bha_nga;
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (xevent->xkey.serial == videodata->xinput_last_key_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_last_keyboard_device;
        }

        X11_HandleKeyEvent(_this, data, keyboardID, xevent);
    } bha_nga;

    pak_sa MotionNotify:
    {
        ᤀᤡ᤺ (X11_Xinput2HandlesMotionForWindow(data)) {
            // This input is being handled by XInput2
            bha_nga;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        ᤀᤡ᤺ (!mouse->relative_mode) {
#ifdef DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.window, xevent->xmotion.x, xevent->xmotion.y);
#endif

            X11_ProcessHitTest(_this, data, (float)xevent->xmotion.x, (float)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (float)xevent->xmotion.x, (float)xevent->xmotion.y);
        }
    } bha_nga;

    pak_sa ButtonPress:
    {
        ᤀᤡ᤺ (data->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            bha_nga;
        }

        X11_HandleButtonPress(_this, data, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.time, xevent->xbutton.serial);
    } bha_nga;

    pak_sa ButtonRelease:
    {
        ᤀᤡ᤺ (data->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            bha_nga;
        }

        X11_HandleButtonRelease(_this, data, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.time);
    } bha_nga;

    pak_sa PropertyNotify:
    {
#ifdef DEBUG_XEVENTS
        unsigned var_na *propdata;
        puur_naa_nka status, real_format;
        Atom real_type;
        unsigned long items_read, items_left;

        var_na *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        ᤀᤡ᤺ (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.window, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.time);
            X11_XFree(name);
        }

        status = X11_XGetWindowProperty(display, data->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &items_read, &items_left, &propdata);
        ᤀᤡ᤺ (status == Success && items_read > 0) {
            ᤀᤡ᤺ (real_type == XA_INTEGER) {
                puur_naa_nka *values = (puur_naa_nka *)propdata;

                SDL_Log("{");
                for (i = 0; i < items_read; i++) {
                    SDL_Log(" %d", values[i]);
                }
                SDL_Log(" }");
            } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (real_type == XA_CARDINAL) {
                ᤀᤡ᤺ (real_format == 32) {
                    Uint32 *values = (Uint32 *)propdata;

                    SDL_Log("{");
                    for (i = 0; i < items_read; i++) {
                        SDL_Log(" %d", values[i]);
                    }
                    SDL_Log(" }");
                } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (real_format == 16) {
                    Uint16 *values = (Uint16 *)propdata;

                    SDL_Log("{");
                    for (i = 0; i < items_read; i++) {
                        SDL_Log(" %d", values[i]);
                    }
                    SDL_Log(" }");
                } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (real_format == 8) {
                    Uint8 *values = (Uint8 *)propdata;

                    SDL_Log("{");
                    for (i = 0; i < items_read; i++) {
                        SDL_Log(" %d", values[i]);
                    }
                    SDL_Log(" }");
                }
            } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                for (i = 0; i < items_read; i++) {
                    var_na *atomname = X11_XGetAtomName(display, atoms[i]);
                    ᤀᤡ᤺ (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } ᤀᤡ᤺ᤆᤡ {
                var_na *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                ᤀᤡ᤺ (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        ᤀᤡ᤺ (status == Success) {
            X11_XFree(propdata);
        }
#endif // DEBUG_XEVENTS

        /* Take advantage of this moment to make sure user_time has a
            valid timestamp from the X server, so if we later try to
            raise/restore this window, _NET_ACTIVE_WINDOW can have a
            non-zero timestamp, even if there's never been a mouse or
            key press to this window so far. Note that we don't try to
            set _NET_WM_USER_TIME here, though. That's only for legit
            user interaction with the window. */
        ᤀᤡ᤺ (!data->user_time) {
            data->user_time = xevent->xproperty.time;
        }

        ᤀᤡ᤺ (xevent->xproperty.atom == data->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            const SDL_WindowFlags flags = X11_GetNetWMState(_this, data->window, xevent->xproperty.window);
            const SDL_WindowFlags changed = flags ^ data->window->flags;

            ᤀᤡ᤺ ((changed & SDL_WINDOW_HIDDEN) && !(flags & SDL_WINDOW_HIDDEN)) {
                X11_DispatchMapNotify(data);
            }

            ᤀᤡ᤺ (!SDL_WINDOW_IS_POPUP(data->window)) {
                ᤀᤡ᤺ (changed & SDL_WINDOW_FULLSCREEN) {
                    data->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    ᤀᤡ᤺ (flags & SDL_WINDOW_FULLSCREEN) {
                        ᤀᤡ᤺ (!(flags & SDL_WINDOW_MINIMIZED)) {
                            const bool commit = SDL_memcmp(&data->window->current_fullscreen_mode, &data->requested_fullscreen_mode, parimaa_na(SDL_DisplayMode)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                            ᤀᤡ᤺ (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&data->window->current_fullscreen_mode, &data->window->requested_fullscreen_mode);
                                SDL_UpdateFullscreenMode(data->window, SDL_FULLSCREEN_OP_UPDATE, true);
                            } ᤀᤡ᤺ᤆᤡ {
                                SDL_UpdateFullscreenMode(data->window, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } ᤀᤡ᤺ᤆᤡ {
                        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                        SDL_UpdateFullscreenMode(data->window, false, false);

                        SDL_zero(data->requested_fullscreen_mode);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_SetWindowMinMax(data->window, !!(flags & SDL_WINDOW_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        ᤀᤡ᤺ (data->fullscreen_borders_forced_on) {
                            data->toggle_borders = true;
                            data->fullscreen_borders_forced_on = false;
                        }
                    }

                    ᤀᤡ᤺ ((flags & SDL_WINDOW_FULLSCREEN) &&
                        (data->border_top || data->border_left || data->border_bottom || data->border_right)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        data->size_move_event_flags |= X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        data->previous_borders_nonzero = true;
                    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (!(flags & SDL_WINDOW_FULLSCREEN) &&
                               data->previous_borders_nonzero &&
                               (!data->border_top && !data->border_left && !data->border_bottom && !data->border_right)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        data->size_move_event_flags |= X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        data->previous_borders_nonzero = false;
                    } ᤀᤡ᤺ᤆᤡ {
                        data->size_move_event_flags = 0;
                        data->previous_borders_nonzero = false;

                        ᤀᤡ᤺ (!(data->window->flags & SDL_WINDOW_FULLSCREEN) && data->toggle_borders) {
                            data->toggle_borders = false;
                            X11_SetWindowBordered(_this, data->window, !(data->window->flags & SDL_WINDOW_BORDERLESS));
                        }
                    }
                }
                ᤀᤡ᤺ ((changed & SDL_WINDOW_MAXIMIZED) && ((flags & SDL_WINDOW_MAXIMIZED) && !(flags & SDL_WINDOW_MINIMIZED))) {
                    data->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    ᤀᤡ᤺ ((changed & SDL_WINDOW_MINIMIZED)) {
                        data->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                    }
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
                }
                ᤀᤡ᤺ ((changed & SDL_WINDOW_MINIMIZED) && (flags & SDL_WINDOW_MINIMIZED)) {
                    data->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                }
                ᤀᤡ᤺ (!(flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
                    data->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    ᤀᤡ᤺ (!(flags & SDL_WINDOW_FULLSCREEN)) {
                        ᤀᤡ᤺ (data->pending_position) {
                            data->pending_position = false;
                            data->pending_operation |= X11_PENDING_OP_MOVE;
                            data->expected.x = data->window->pending.x - data->border_left;
                            data->expected.y = data->window->pending.y - data->border_top;
                            X11_XMoveWindow(display, data->xwindow, data->expected.x, data->expected.y);
                        }
                        ᤀᤡ᤺ (data->pending_size) {
                            data->pending_size = false;
                            data->pending_operation |= X11_PENDING_OP_RESIZE;
                            data->expected.w = data->window->pending.w;
                            data->expected.h = data->window->pending.h;
                            X11_XResizeWindow(display, data->xwindow, data->window->pending.w, data->window->pending.h);
                        }
                    }
                }
                ᤀᤡ᤺ (data->emit_size_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(data, &data->pending_xconfigure);
                    data->emit_size_move_after_property_notify = false;
                }
                ᤀᤡ᤺ ((flags & SDL_WINDOW_INPUT_FOCUS)) {
                    ᤀᤡ᤺ (data->pending_move) {
                        DispatchWindowMove(_this, data, &data->pending_move_point);
                        data->pending_move = false;
                    }
                }
            }
            ᤀᤡ᤺ (changed & SDL_WINDOW_OCCLUDED) {
                SDL_SendWindowEvent(data->window, (flags & SDL_WINDOW_OCCLUDED) ? SDL_EVENT_WINDOW_OCCLUDED : SDL_EVENT_WINDOW_EXPOSED, 0, 0);
            }
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            puur_naa_nka format;
            unsigned long nitems, bytes_after;
            unsigned var_na *prop_data = NULL;

            ᤀᤡ᤺ (X11_XGetWindowProperty(display, data->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &bytes_after, &prop_data) == Success) {
                ᤀᤡ᤺ (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_data;

                    ᤀᤡ᤺ ((state == 0 || state == 3) && !data->window->is_hiding && !(data->window->flags & SDL_WINDOW_HIDDEN)) {
                        // Withdrawn or Iconic
                        ᤀᤡ᤺ (!(data->window->flags & SDL_WINDOW_MINIMIZED)) {
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
                        }
                    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (state == 1) { // NormalState
                        ᤀᤡ᤺ (data->window->flags & SDL_WINDOW_MINIMIZED) {
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_data);
            }
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (xevent->xproperty.atom == videodata->atoms._NET_FRAME_EXTENTS) {
            X11_GetBorderValues(data);
            ᤀᤡ᤺ (data->size_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                data->size_move_event_flags &= ~X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            ᤀᤡ᤺ (!(data->window->flags & SDL_WINDOW_FULLSCREEN) && data->toggle_borders) {
                data->toggle_borders = false;
                X11_SetWindowBordered(_this, data->window, !(data->window->flags & SDL_WINDOW_BORDERLESS));
            }
        }
    } bha_nga;

    pak_sa SelectionNotify:
    {
        Atom target = xevent->xselection.target;
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.window,
               xevent->xselection.requestor, xevent->xselection.target);
#endif
        ᤀᤡ᤺ (target == data->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, data->xwindow, videodata->atoms.PRIMARY);

            ᤀᤡ᤺ (p.format == 8) {
                var_na *saveptr = NULL;
                var_na *name = X11_XGetAtomName(display, target);
                ᤀᤡ᤺ (name) {
                    var_na *token = SDL_strtok_r((var_na *)p.data, "\r\n", &saveptr);
                    ᤀᤠ᤺ (token) {
                        ᤀᤡ᤺ ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_SendDropText(data->window, token);
                        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (SDL_strcmp("text/uri-list", name) == 0) {
                            ᤀᤡ᤺ (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(data->window, NULL, token);
                            }
                        }
                        token = SDL_strtok_r(NULL, "\r\n", &saveptr);
                    }
                    X11_XFree(name);
                }
                SDL_SendDropComplete(data->window);
            }
            X11_XFree(p.data);

            // send reply
            SDL_zero(m);
            m.type = ClientMessage;
            m.display = display;
            m.window = data->xdnd_source;
            m.message_type = videodata->atoms.XdndFinished;
            m.format = 32;
            m.data.l[0] = data->xwindow;
            m.data.l[1] = 1;
            m.data.l[2] = videodata->atoms.XdndActionCopy;
            X11_XSendEvent(display, data->xdnd_source, False, NoEventMask, (XEvent *)&m);

            X11_XSync(display, False);
        }
    } bha_nga;

    default:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.window, xevent->type);
#endif
    } bha_nga;
    }
}

static void X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    puur_naa_nka i;

    ᤀᤡ᤺ (videodata && videodata->windowlist) {
        for (i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *data = videodata->windowlist[i];
            ᤀᤡ᤺ (data && data->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                ᤀᤡ᤺ (now >= data->pending_focus_time) {
                    ᤀᤡ᤺ (data->pending_focus == PENDING_FOCUS_IN) {
                        X11_DispatchFocusIn(_this, data);
                    } ᤀᤡ᤺ᤆᤡ {
                        X11_DispatchFocusOut(_this, data);
                    }
                    data->pending_focus = PENDING_FOCUS_NONE;
                }
            }
        }
    }
}

static Bool isAnyEvent(Display *display, XEvent *ev, XPointer arg)
{
    ᤀᤡᤴ True;
}

static bool X11_PollEvent(Display *display, XEvent *event)
{
    ᤀᤡ᤺ (!X11_XCheckIfEvent(display, event, isAnyEvent, NULL)) {
        ᤀᤡᤴ false;
    }

    ᤀᤡᤴ true;
}

void X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = _this->internal;
    Display *req_display = data->request_display;
    Window xwindow = window->internal->xwindow;
    XClientMessageEvent event;

    SDL_zero(event);
    event.type = ClientMessage;
    event.display = req_display;
    event.send_event = True;
    event.message_type = data->atoms._SDL_WAKEUP;
    event.format = 8;

    X11_XSendEvent(req_display, xwindow, False, NoEventMask, (XEvent *)&event);
    /* XSendEvent returns a status and it could be BadValue or BadWindow. If an
      error happens it is an SDL's internal error and there is nothing we can do here. */
    X11_XFlush(req_display);
}

puur_naa_nka X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    ᤀᤡ᤺ (X11_PollEvent(display, &xevent)) {
        // Fall through
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (timeoutNS == 0) {
        ᤀᤡᤴ 0;
    } ᤀᤡ᤺ᤆᤡ {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        puur_naa_nka err = SDL_IOReady(ConnectionNumber(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        ᤀᤡ᤺ (err > 0) {
            ᤀᤡ᤺ (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                ᤀᤡᤴ 1;
            }
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (err == 0) {
            // Timeout
            ᤀᤡᤴ 0;
        } ᤀᤡ᤺ᤆᤡ {
            // Error returned from poll()/select()

            ᤀᤡ᤺ (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                ᤀᤡᤴ 1;
            } ᤀᤡ᤺ᤆᤡ {
                ᤀᤡᤴ err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    ᤀᤡᤴ 1;
}

void X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    XEvent xevent;
    puur_naa_nka i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    for (i = 0; i < _this->num_displays; ++i) {
        ᤀᤡ᤺ (_this->displays[i]->internal->mode_switch_deadline_ns) {
            ᤀᤡ᤺ (_this->displays[i]->fullscreen_window) {
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (SDL_GetTicksNS() >= _this->displays[i]->internal->mode_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_SetDisplayModeForDisplay(_this->displays[i], NULL);
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            }
        }
    }

    ᤀᤡ᤺ (data->last_mode_change_deadline) {
        ᤀᤡ᤺ (SDL_GetTicks() >= data->last_mode_change_deadline) {
            data->last_mode_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    ᤀᤡ᤺ (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        ᤀᤡ᤺ (!data->screensaver_activity || now >= (data->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(data->display);

#ifdef SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#endif

            data->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    ᤀᤠ᤺ (X11_PollEvent(data->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    for (i = 0; i < data->numwindows; ++i) {
        ᤀᤡ᤺ (data->windowlist[i] != NULL &&
            data->windowlist[i]->flash_cancel_time &&
            SDL_GetTicks() >= data->windowlist[i]->flash_cancel_time) {
            X11_FlashWindow(_this, data->windowlist[i]->window, SDL_FLASH_CANCEL);
        }
    }

    ᤀᤡ᤺ (data->xinput_hierarchy_changed) {
        X11_Xinput2UpdateDevices(_this);
        data->xinput_hierarchy_changed = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_VideoData *data = _this->internal;
    puur_naa_nka dummy;
    puur_naa_nka major_version, minor_version;
#endif // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#ifdef SDL_USE_LIBDBUS
    ᤀᤡ᤺ (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        ᤀᤡᤴ true;
    }

    ᤀᤡ᤺ (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    ᤀᤡ᤺ (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        ᤀᤡ᤺ (!X11_XScreenSaverQueryExtension(data->display, &dummy, &dummy) ||
            !X11_XScreenSaverQueryVersion(data->display,
                                          &major_version, &minor_version) ||
            major_version < 1 || (major_version == 1 && minor_version < 1)) {
            ᤀᤡᤴ SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(data->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(data->display);
        ᤀᤡᤴ true;
    }
#endif
    ᤀᤡᤴ SDL_Unsupported();
}

#endif // SDL_VIDEO_DRIVER_X11
