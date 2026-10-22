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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ <sys/types.h>
#ಅನ್ತರ್ಭಾವ <sys/time.h>
#ಅನ್ತರ್ಭಾವ <signal.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <limits.h> // For INT_MAX

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11pen.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11touch.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xinput2.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xfixes.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11settings.h"
#ಅನ್ತರ್ಭಾವ "../SDL_clipboard_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xsync.h"
#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_poll.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_system_theme.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಯದಿ 0
#define DEBUG_XEVENTS
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPLEFT
#define _NET_WM_MOVERESIZE_SIZE_TOPLEFT 0
#endif

#ifndef NET_WM_MOVERESIZE_SIZE_ತುದಿ
#define NET_WM_MOVERESIZE_SIZE_ತುದಿ 1
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPRIGHT
#define _NET_WM_MOVERESIZE_SIZE_TOPRIGHT 2
#endif

#ifndef NET_WM_MOVERESIZE_SIZE_ಬಲ
#define NET_WM_MOVERESIZE_SIZE_ಬಲ 3
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

#ifndef NET_WM_MOVERESIZE_SIZE_ಎಡ
#define NET_WM_MOVERESIZE_SIZE_ಎಡ 7
#endif

#ifndef _NET_WM_MOVERESIZE_MOVE
#define _NET_WM_MOVERESIZE_MOVE 8
#endif

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    unsigned ವರ್ಣ *data;
    ಪೂರ್ಣಾಙ್ಕ format, ಎಣಿಕೆ;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ಸ್ಥಿರ ಶೂನ್ಯ X11_ReadProperty(SDL_x11Prop *p, Display *disp, Window w, Atom prop)
{
    unsigned ವರ್ಣ *ret = ರಿಕ್ತ;
    Atom type;
    ಪೂರ್ಣಾಙ್ಕ fmt;
    unsigned long ಎಣಿಕೆ;
    unsigned long bytes_ಎಡ;
    ಪೂರ್ಣಾಙ್ಕ bytes_fetch = 0;

    ಕುರು {
        ಯದಿ (ret) {
            X11_XFree(ret);
        }
        X11_XGetWindowProperty(disp, w, prop, 0, bytes_fetch, False, AnyPropertyType, &type, &fmt, &ಎಣಿಕೆ, &bytes_ಎಡ, &ret);
        bytes_fetch += bytes_ಎಡ;
    } ಯಾವತ್ (bytes_ಎಡ != 0);

    p->data = ret;
    p->format = fmt;
    p->ಎಣಿಕೆ = ಎಣಿಕೆ;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
ಸ್ಥಿರ Atom X11_PickTarget(Display *disp, Atom list[], ಪೂರ್ಣಾಙ್ಕ list_ಎಣಿಕೆ)
{
    ಧ್ರುವ Atom text_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < list_ಎಣಿಕೆ && request != text_uri_request; i++) {
        ವರ್ಣ *name = X11_XGetAtomName(disp, list[i]);
        // Preferred MIME targets
        ಯದಿ ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            ಯದಿ (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        ಯದಿ ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            ಯದಿ (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    ಯದಿ (preferred != None && request != text_uri_request) {
        request = preferred;
    }
    ಪ್ರತ್ಯಾಗಮ request;
}

/* Wrapper for X11_PickTarget for a maximum of three targets, a special
   case in the Xdnd protocol */
ಸ್ಥಿರ Atom X11_PickTargetFromAtoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ = 0;
    Atom atom[3];
    ಯದಿ (a0 != None) {
        atom[ಎಣಿಕೆ++] = a0;
    }
    ಯದಿ (a1 != None) {
        atom[ಎಣಿಕೆ++] = a1;
    }
    ಯದಿ (a2 != None) {
        atom[ಎಣಿಕೆ++] = a2;
    }
    ಪ್ರತ್ಯಾಗಮ X11_PickTarget(disp, atom, ಎಣಿಕೆ);
}

ಸಂರಚನಾ ಕೀಲಿ_Repeat_Check_Data
{
    XEvent *event;
    bool found;
};

ಸ್ಥಿರ Bool X11_ಕೀಲಿ_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    ಸಂರಚನಾ ಕೀಲಿ_Repeat_Check_Data *d = (ಸಂರಚನಾ ಕೀಲಿ_Repeat_Check_Data *)arg;
    ಯದಿ (chkev->type == ಕೀಲಿ_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.time - d->event->xkey.time < 2) {
        d->found = true;
    }
    ಪ್ರತ್ಯಾಗಮ False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
ಸ್ಥಿರ bool X11_ಕೀಲಿ_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    ಸಂರಚನಾ ಕೀಲಿ_Repeat_Check_Data d;
    d.event = event;
    d.found = false;
    ಯದಿ (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_ಕೀಲಿ_Repeat_Check_If_Event, (XPointer)&d);
    }
    ಪ್ರತ್ಯಾಗಮ d.found;
}

bool X11_IsWheelEvent(ಪೂರ್ಣಾಙ್ಕ button, ಪೂರ್ಣಾಙ್ಕ *xticks, ಪೂರ್ಣಾಙ್ಕ *yticks)
{
    /* according to the xlib docs, no specific mouse wheel events exist.
       However, the defacto standard is that the vertical wheel is X buttons
       4 (up) and 5 (down) and a horizontal wheel is 6 (left) and 7 (right). */

    // Xlib defines "Button1" through 5, so we just use literals here.
    ವಿಕಲ್ಪ (button) {
    ಪಕ್ಷ 4:
        *yticks = 1;
        ಪ್ರತ್ಯಾಗಮ true;
    ಪಕ್ಷ 5:
        *yticks = -1;
        ಪ್ರತ್ಯಾಗಮ true;
    ಪಕ್ಷ 6:
        *xticks = 1;
        ಪ್ರತ್ಯಾಗಮ true;
    ಪಕ್ಷ 7:
        *xticks = -1;
        ಪ್ರತ್ಯಾಗಮ true;
    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

// An X11 event hook
ಸ್ಥಿರ SDL_X11EventHook g_X11EventHook = ರಿಕ್ತ;
ಸ್ಥಿರ ಶೂನ್ಯ *g_X11EventHookData = ರಿಕ್ತ;

ಶೂನ್ಯ SDL_SetX11EventHook(SDL_X11EventHook callback, ಶೂನ್ಯ *userdata)
{
    g_X11EventHook = callback;
    g_X11EventHookData = userdata;
}

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
ಸ್ಥಿರ ಶೂನ್ಯ X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_VideoData *videodata = _this->internal;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    ಯದಿ (X11_XGetEventData(videodata->display, cookie)) {
        ಯದಿ (!g_X11EventHook || g_X11EventHook(g_X11EventHookData, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFreeEventData(videodata->display, cookie);
    }
}
#endif // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

ಸ್ಥಿರ ಶೂನ್ಯ X11_Update_System_ಕೀಲಿ_Modifiers(SDL_VideoData *viddata)
{
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ಯದಿ (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        ಯದಿ (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.base_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } ಅನ್ಯಥಾ
#endif
        {
        Window junk_window;
        ಪೂರ್ಣಾಙ್ಕ x, y;
        unsigned ಪೂರ್ಣಾಙ್ಕ mod_mask;

        X11_XQueryPointer(viddata->display, Default_ಬೇರು_Window(viddata->display), &junk_window, &junk_window, &x, &y, &x, &y, &mod_mask);
        viddata->keyboard.pressed_modifiers = mod_mask & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        viddata->keyboard.locked_modifiers = mod_mask & (LockMask | viddata->keyboard.numlock_mask | viddata->keyboard.scrolllock_mask);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_ReconcileModifiers(SDL_VideoData *viddata, bool ಕೀಲಿ_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    ಯದಿ (ಕೀಲಿ_pressed) {
        ಯದಿ (viddata->keyboard.pressed_modifiers & ShiftMask) {
            ಯದಿ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT);
            }
        }

        ಯದಿ (viddata->keyboard.pressed_modifiers & ControlMask) {
            ಯದಿ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        ಯದಿ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            ಯದಿ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        ಯದಿ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            ಯದಿ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (viddata->keyboard.pressed_modifiers & ShiftMask) {
            ಯದಿ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } ಅನ್ಯಥಾ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        ಯದಿ (viddata->keyboard.pressed_modifiers & ControlMask) {
            ಯದಿ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } ಅನ್ಯಥಾ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        ಯದಿ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            ಯದಿ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } ಅನ್ಯಥಾ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        ಯದಿ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            ಯದಿ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } ಅನ್ಯಥಾ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        ಯದಿ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_mask) {
            ಯದಿ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_MODE)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_MODE;
            }
        } ಅನ್ಯಥಾ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        ಯದಿ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_mask) {
            ಯದಿ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } ಅನ್ಯಥಾ {
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
    ಯದಿ (viddata->keyboard.locked_modifiers & ShiftMask) {
        ಯದಿ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT);
        } ಅನ್ಯಥಾ ಯದಿ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_SHIFT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } ಅನ್ಯಥಾ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    ಯದಿ (viddata->keyboard.locked_modifiers & ControlMask) {
        ಯದಿ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } ಅನ್ಯಥಾ ಯದಿ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } ಅನ್ಯಥಾ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    ಯದಿ (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_mask) {
        ಯದಿ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } ಅನ್ಯಥಾ ಯದಿ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } ಅನ್ಯಥಾ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    ಯದಿ (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_mask) {
        ಯದಿ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } ಅನ್ಯಥಾ ಯದಿ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } ಅನ್ಯಥಾ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    ಯದಿ (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_MODE;
    } ಅನ್ಯಥಾ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_MODE;
    }

    ಯದಿ (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } ಅನ್ಯಥಾ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    ಯದಿ (viddata->keyboard.locked_modifiers & LockMask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } ಅನ್ಯಥಾ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    ಯದಿ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ಅಂಕೆ;
    } ಅನ್ಯಥಾ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ಅಂಕೆ;
    }

    ಯದಿ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } ಅನ್ಯಥಾ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_SetModState(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Handle_Modifier_ಕೀಲಿಗಳು(SDL_VideoData *viddata, SDL_Scancode scancode, bool pressed)
{
    ಧ್ರುವ SDL_Keycode keycode = SDL_Get_ಕೀಲಿ_From_Scancode(scancode, SDL_KMOD_NONE, false);
    SDL_Keymod mod = SDL_KMOD_NONE;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is checked.
     */
    ವಿಕಲ್ಪ (keycode) {
    ಪಕ್ಷ SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_LALT:
        mod = SDL_KMOD_LALT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_RALT:
        mod = SDL_KMOD_RALT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_MODE:
        mod = SDL_KMOD_MODE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_CAPSLOCK:
    ಪಕ್ಷ SDLK_NUMLOCKCLEAR:
    ಪಕ್ಷ SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        ಯದಿ (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            unsigned ಪೂರ್ಣಾಙ್ಕ cur_mask = viddata->keyboard.locked_modifiers;
            X11_Update_System_ಕೀಲಿ_Modifiers(viddata);

            ಯದಿ (viddata->keyboard.locked_modifiers & LockMask) {
                cur_mask |= LockMask;
            } ಅನ್ಯಥಾ {
                cur_mask &= ~LockMask;
            }
            ಯದಿ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
                cur_mask |= viddata->keyboard.numlock_mask;
            } ಅನ್ಯಥಾ {
                cur_mask &= ~viddata->keyboard.numlock_mask;
            }
            ಯದಿ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
                cur_mask |= viddata->keyboard.scrolllock_mask;
            } ಅನ್ಯಥಾ {
                cur_mask &= ~viddata->keyboard.scrolllock_mask;
            }

            viddata->keyboard.locked_modifiers = cur_mask;
        }
    } ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } ಅನ್ಯಥಾ {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

ಶೂನ್ಯ X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    ವರ್ಣ ಕೀಲಿಗಳು[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_ಕೀಲಿ_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_ಅಂಕೆ | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= LockMask | videodata->keyboard.numlock_mask| videodata->keyboard.scrolllock_mask;

    X11_XQueryKeymap(display, ಕೀಲಿಗಳು);

    ಧ್ರುವ bool *keystate = SDL_GetKeyboardState(ರಿಕ್ತ);
    ಪ್ರತಿ (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.ಕೀಲಿ_layout); ++keycode) {
        ಧ್ರುವ SDL_Scancode scancode = videodata->keyboard.ಕೀಲಿ_layout[keycode];
        ಧ್ರುವ bool x11_ಕೀಲಿ_Pressed = (ಕೀಲಿಗಳು[keycode / 8] & (1 << (keycode % 8))) != 0;
        ಧ್ರುವ bool sdl_ಕೀಲಿ_Pressed = keystate[scancode];

        ಯದಿ (x11_ಕೀಲಿ_Pressed && !sdl_ಕೀಲಿ_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            ವಿಕಲ್ಪ (SDL_Get_ಕೀಲಿ_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            ಪಕ್ಷ SDLK_LCTRL:
            ಪಕ್ಷ SDLK_RCTRL:
            ಪಕ್ಷ SDLK_LSHIFT:
            ಪಕ್ಷ SDLK_RSHIFT:
            ಪಕ್ಷ SDLK_LALT:
            ಪಕ್ಷ SDLK_RALT:
            ಪಕ್ಷ SDLK_LGUI:
            ಪಕ್ಷ SDLK_RGUI:
            ಪಕ್ಷ SDLK_MODE:
            ಪಕ್ಷ SDLK_LEVEL5_SHIFT:
                X11_Handle_Modifier_ಕೀಲಿಗಳು(videodata, scancode, true);
                SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                ಭಙ್ಗ;
            ಸ್ವಭಾವ:
                ಭಙ್ಗ;
            }
        } ಅನ್ಯಥಾ ಯದಿ (!x11_ಕೀಲಿ_Pressed && sdl_ಕೀಲಿ_Pressed) {
            X11_Handle_Modifier_ಕೀಲಿಗಳು(videodata, scancode, false);
            SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_ಕೀಲಿ_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_DispatchFocusIn(SDL_VideoDevice *_this, SDL_WindowData *data)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", data->xwindow);
#endif
    SDL_SetKeyboardFocus(data->window);
    X11_ReconcileKeyboardState(_this);
#ifdef X_HAVE_UTF8_STRING
    ಯದಿ (data->ic) {
        X11_XSetICFocus(data->ic);
    }
#endif
    ಯದಿ (data->flashing_window) {
        X11_FlashWindow(_this, data->window, SDL_FLASH_CANCEL);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_DispatchFocusOut(SDL_VideoDevice *_this, SDL_WindowData *data)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", data->xwindow);
#endif
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    ಯದಿ (data->window == SDL_GetKeyboardFocus()) {
        SDL_SetKeyboardFocus(ರಿಕ್ತ);
    }
#ifdef X_HAVE_UTF8_STRING
    ಯದಿ (data->ic) {
        X11_XUnsetICFocus(data->ic);
    }
#endif
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_DispatchMapNotify(SDL_WindowData *data)
{
    SDL_Window *window = data->window;

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    data->was_shown = true;

    // This may be sent when restoring a minimized window.
    ಯದಿ (window->flags & SDL_WINDOW_MINIMIZED) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }

    ಯದಿ (window->flags & SDL_WINDOW_ಒಳಹರಿವು_FOCUS) {
        SDL_UpdateWindowGrab(window);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_DispatchUnmapNotify(SDL_WindowData *data)
{
    SDL_Window *window = data->window;

    // This may be sent when minimizing a window.
    ಯದಿ (!window->is_hiding) {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
    } ಅನ್ಯಥಾ {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ DispatchWindowMove(SDL_VideoDevice *_this, ಧ್ರುವ SDL_WindowData *data, ಧ್ರುವ SDL_Point *point)
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
    X11_XSendEvent(display, Default_ಬೇರು_Window(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

ಸ್ಥಿರ ಶೂನ್ಯ ScheduleWindowMove(SDL_VideoDevice *_this, SDL_WindowData *data, ಧ್ರುವ SDL_Point *point)
{
    data->pending_move = true;
    data->pending_move_point = *point;
}

ಸ್ಥಿರ ಶೂನ್ಯ InitiateWindowResize(SDL_VideoDevice *_this, ಧ್ರುವ SDL_WindowData *data, ಧ್ರುವ SDL_Point *point, ಪೂರ್ಣಾಙ್ಕ direction)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_Window *window = data->window;
    Display *display = videodata->display;
    XEvent evt;

    ಯದಿ (direction < _NET_WM_MOVERESIZE_SIZE_TOPLEFT || direction > NET_WM_MOVERESIZE_SIZE_ಎಡ) {
        ಪ್ರತ್ಯಾಗಮ;
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
    X11_XSendEvent(display, Default_ಬೇರು_Window(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_WindowData *data, ಧ್ರುವ ಭಿನ್ನ x, ಧ್ರುವ ಭಿನ್ನ y, bool force_new_result)
{
    SDL_Window *window = data->window;
    ಯದಿ (!window->hit_test) ಪ್ರತ್ಯಾಗಮ false;
    ಧ್ರುವ SDL_Point point = { (ಪೂರ್ಣಾಙ್ಕ)x, (ಪೂರ್ಣಾಙ್ಕ)y };
    SDL_HitTestResult rc = window->hit_test(window, &point, window->hit_test_data);
    ಯದಿ (!force_new_result && rc == data->hit_test_result) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    X11_SetHitTestCursor(rc);
    data->hit_test_result = rc;
    ಪ್ರತ್ಯಾಗಮ true;
}

bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_WindowData *data, ಧ್ರುವ ಭಿನ್ನ x, ಧ್ರುವ ಭಿನ್ನ y)
{
    SDL_Window *window = data->window;

    ಯದಿ (window->hit_test) {
        ಧ್ರುವ SDL_Point point = { (ಪೂರ್ಣಾಙ್ಕ)x, (ಪೂರ್ಣಾಙ್ಕ)y };
        ಸ್ಥಿರ ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ directions[] = {
            _NET_WM_MOVERESIZE_SIZE_TOPLEFT, NET_WM_MOVERESIZE_SIZE_ತುದಿ,
            _NET_WM_MOVERESIZE_SIZE_TOPRIGHT, NET_WM_MOVERESIZE_SIZE_ಬಲ,
            _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT, _NET_WM_MOVERESIZE_SIZE_BOTTOM,
            _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT, NET_WM_MOVERESIZE_SIZE_ಎಡ
        };

        ವಿಕಲ್ಪ (data->hit_test_result) {
        ಪಕ್ಷ SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            ಯದಿ (data->window->flags & SDL_WINDOW_ಒಳಹರಿವು_FOCUS) {
                DispatchWindowMove(_this, data, &point);
            } ಅನ್ಯಥಾ {
                ScheduleWindowMove(_this, data, &point);
            }
            ಪ್ರತ್ಯಾಗಮ true;

        ಪಕ್ಷ SDL_HITTEST_RESIZE_TOPLEFT:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_ತುದಿ:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_TOPRIGHT:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_ಬಲ:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOM:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOMLEFT:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_ಎಡ:
            InitiateWindowResize(_this, data, &point, directions[data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
            ಪ್ರತ್ಯಾಗಮ true;

        ಸ್ವಭಾವ:
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    ಪ್ರತ್ಯಾಗಮ false;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_UpdateUserTime(SDL_WindowData *data, ಧ್ರುವ unsigned long latest)
{
    ಯದಿ (latest && (latest != data->user_time)) {
        SDL_VideoData *videodata = data->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, data->xwindow, videodata->atoms._NET_WM_USER_TIME,
                            XA_CARDINAL, 32, PropModeReplace,
                            (ಧ್ರುವ unsigned ವರ್ಣ *)&latest, 1);
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", data->xwindow, latest);
#endif
        data->user_time = latest;
    }
}

ಸ್ಥಿರ unsigned ವರ್ಣ x11_last_error;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ BadWindowErrorHandler(Display *d, XErrorEvent *e)
{
    x11_last_error = e->error_code;

    // Ignore BadWindow in cases where it's not fatal.
    ಯದಿ (e->error_code != BadWindow) {
        ವರ್ಣ err_ಸಂದೇಶ[128];
        X11_XGetErrorText(d, e->error_code, err_ಸಂದೇಶ, ಪರಿಮಾಣ(err_ಸಂದೇಶ));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_code, err_ಸಂದೇಶ, e->request_code);
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_HandleClipboardEvent(SDL_VideoDevice *_this, ಧ್ರುವ XEvent *xevent)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_window != None);
    SDL_assert(xevent->xany.window == videodata->clipboard_window);

    ವಿಕಲ್ಪ (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    ಪಕ್ಷ SelectionRequest:
    {
        ಧ್ರುವ XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        ಪೂರ್ಣಾಙ್ಕ mime_formats;
        unsigned ವರ್ಣ *seln_data;
        size_t seln_length = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_ClipboardData *clipboard;

#ifdef DEBUG_XEVENTS
        ವರ್ಣ *atom_name;
        atom_name = X11_XGetAtomName(display, req->target);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->target, atom_name);
        ಯದಿ (atom_name) {
            X11_XFree(atom_name);
        }
#endif

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_last_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

        ಯದಿ (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ಅನ್ಯಥಾ {
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

        ಯದಿ (req->target == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_ಎಣಿಕೆ + 1) * ಪರಿಮಾಣ(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            ಪ್ರತಿ (i = 0; i < clipboard->mime_ಎಣಿಕೆ; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, PropModeReplace,
                                (unsigned ವರ್ಣ *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.target = XA_TARGETS;
            SDL_free(supportedFormats);
        } ಅನ್ಯಥಾ {
            ಯದಿ (clipboard->callback) {
                ಪ್ರತಿ (i = 0; i < clipboard->mime_ಎಣಿಕೆ; ++i) {
                    ಧ್ರುವ ವರ್ಣ *mime_type = clipboard->mime_types[i];
                    ಯದಿ (X11_XInternAtom(display, mime_type, False) != req->target) {
                        ಅನುವರ್ತ;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_data = (unsigned ವರ್ಣ *)clipboard->callback(clipboard->userdata, mime_type, &seln_length);
                    ಯದಿ (seln_data) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->target, 8, PropModeReplace,
                                            seln_data, seln_length);
                        sevent.xselection.property = req->property;
                        sevent.xselection.target = req->target;
                    }
                    ಭಙ್ಗ;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(prev_handler);
    } ಭಙ್ಗ;

    ಪಕ್ಷ SelectionNotify:
    {
        ಧ್ರುವ XSelectionEvent *xsel = &xevent->xselection;
#ifdef DEBUG_XEVENTS
        ಧ್ರುವ ವರ್ಣ *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        ಧ್ರುವ ವರ್ಣ *targetName = xsel->target ? X11_XGetAtomName(display, xsel->target) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, targetName, propName);
#endif
        ಯದಿ (xsel->target == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            unsigned ವರ್ಣ *data = ರಿಕ್ತ;
            ಪೂರ್ಣಾಙ್ಕ format_property = 0;
            unsigned long length = 0;
            unsigned long bytes_ಎಡ = 0;
            ಪೂರ್ಣಾಙ್ಕ j;

            X11_XGetWindowProperty(display, GetWindow(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &length, &bytes_ಎಡ, &data);

            ಪೂರ್ಣಾಙ್ಕ allocationsize = (length + 1) * ಪರಿಮಾಣ(ವರ್ಣ *);
            ಪ್ರತಿ (j = 0, patom = (Atom *)data; j < length; j++, patom++) {
                ವರ್ಣ *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            ವರ್ಣ **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
            ಯದಿ (new_mime_types) {
                ವರ್ಣ *strPtr = (ವರ್ಣ *)(new_mime_types + length + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                ಪ್ರತಿ (j = 0, patom = (Atom *)data; j < length; j++, patom++) {
                    ವರ್ಣ *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    ಧ್ರುವ size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[length] = ರಿಕ್ತ;

                SDL_SendClipboardUpdate(false, new_mime_types, length);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            ಯದಿ (data) {
                X11_XFree(data);
            }
        }

        videodata->selection_waiting = false;
    } ಭಙ್ಗ;

    ಪಕ್ಷ SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_ClipboardData *clipboard = ರಿಕ್ತ;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.target);
#endif

        ಯದಿ (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ಅನ್ಯಥಾ ಯದಿ (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        ಯದಿ (clipboard && clipboard->callback) {
            ಯದಿ (clipboard->sequence) {
                SDL_CancelClipboardData(clipboard->sequence);
            } ಅನ್ಯಥಾ {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } ಭಙ್ಗ;

    ಪಕ್ಷ PropertyNotify:
    {
        ವರ್ಣ *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        ಯದಿ (SDL_strncmp(name_of_atom, "SDL_SELECTION", ಪರಿಮಾಣ("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_ಮೌಲ್ಯ) {
            videodata->selection_incr_waiting = false;
        }

        ಯದಿ (name_of_atom) {
            X11_XFree(name_of_atom);
        }
    } ಭಙ್ಗ;
    }
}

ಸ್ಥಿರ Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    ಪ್ರತ್ಯಾಗಮ ev->type == MapNotify &&
           ev->xmap.window == unmap->window &&
           ev->xmap.serial == unmap->serial;
}

ಸ್ಥಿರ Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    ಪ್ರತ್ಯಾಗಮ ev->type == ReparentNotify &&
           ev->xreparent.window == unmap->window &&
           ev->xreparent.serial == unmap->serial;
}

ಸ್ಥಿರ bool Is_ಮೇಲಿನ_Latin1(ಧ್ರುವ ವರ್ಣ *string, ಪೂರ್ಣಾಙ್ಕ length)
{
    ಯಾವತ್ (length-- > 0) {
        Uint8 ch = (Uint8)*string;
        ಯದಿ (ch >= 0x80) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
        ++string;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ XLookupStringAsUTF8(XKeyEvent *event_struct, ವರ್ಣ *buffer_return, ಪೂರ್ಣಾಙ್ಕ bytes_buffer, ಕೀಲಿ_Sym *keysym_return, XComposeStatus *status_in_out)
{
    ಪೂರ್ಣಾಙ್ಕ result = X11_XLookupString(event_struct, buffer_return, bytes_buffer, keysym_return, status_in_out);
    ಯದಿ (Is_ಮೇಲಿನ_Latin1(buffer_return, result)) {
        ವರ್ಣ *utf8_text = SDL_iconv_string("UTF-8", "ISO-8859-1", buffer_return, result + 1);
        ಯದಿ (utf8_text) {
            SDL_strlcpy(buffer_return, utf8_text, bytes_buffer);
            SDL_free(utf8_text);
            ಪ್ರತ್ಯಾಗಮ SDL_strlen(buffer_return);
        } ಅನ್ಯಥಾ {
            ಪ್ರತ್ಯಾಗಮ 0;
        }
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

SDL_WindowData *X11_FindWindow(SDL_VideoData *videodata, Window window)
{
    ಯದಿ (videodata && videodata->windowlist) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < videodata->numwindows; ++i) {
            ಯದಿ ((videodata->windowlist[i] != ರಿಕ್ತ) &&
                (videodata->windowlist[i]->xwindow == window)) {
                ಪ್ರತ್ಯಾಗಮ videodata->windowlist[i];
            }
        }
    }
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

Uint64 X11_GetEventTimestamp(unsigned long time)
{
    // FIXME: Get the event time in the SDL tick time base
    ಪ್ರತ್ಯಾಗಮ SDL_GetTicksNS();
}

ಶೂನ್ಯ X11_Handle_ಕೀಲಿ_Event(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    ಕೀಲಿ_Code_2 keycode = xevent->xkey.keycode;
    ಕೀಲಿ_Sym keysym = No_ಚಿಹ್ನೆ;
    ಪೂರ್ಣಾಙ್ಕ text_length = 0;
    ವರ್ಣ text[64];
    Status status = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == ಕೀಲಿ_Press);
    SDL_Scancode scancode = videodata->keyboard.ಕೀಲಿ_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.window, (xevent->type == ಕೀಲಿ_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#endif
#ifdef DEBUG_SCANCODES
    ಯದಿ (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        ಪೂರ್ಣಾಙ್ಕ min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_ಕೀಲಿ_Code_To_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysymToString(keysym));
    }
#endif // DEBUG SCANCODES

    text[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    ಯದಿ (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (LockMask | videodata->keyboard.numlock_mask | videodata->keyboard.scrolllock_mask);
    }

    ಯದಿ (SDL_Text_ಒಳಹರಿವು_Active(windowdata->window)) {
        // filter events catches XIM events and sends them to the correct handler
        ಯದಿ (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            handled_by_ime = true;
        }

        ಯದಿ (!handled_by_ime) {
#ifdef X_HAVE_UTF8_STRING
            ಯದಿ (windowdata->ic && xevent->type == ಕೀಲಿ_Press) {
                text_length = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, text, ಪರಿಮಾಣ(text) - 1,
                                      &keysym, &status);
            } ಅನ್ಯಥಾ {
                text_length = XLookupStringAsUTF8(&xevent->xkey, text, ಪರಿಮಾಣ(text) - 1, &keysym, ರಿಕ್ತ);
            }
#ಅನ್ಯಥಾ
            text_length = XLookupStringAsUTF8(&xevent->xkey, text, ಪರಿಮಾಣ(text) - 1, &keysym, ರಿಕ್ತ);
#endif
        }
    }

    ಯದಿ (!handled_by_ime) {
        ಯದಿ (pressed) {
            X11_Handle_Modifier_ಕೀಲಿಗಳು(videodata, scancode, true);
            SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            ಯದಿ (*text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                text[text_length] = '\0';
                X11_ClearComposition(windowdata);
                SDL_SendKeyboardText(text);
            }
        } ಅನ್ಯಥಾ {
            ಯದಿ (X11_ಕೀಲಿ_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                ಪ್ರತ್ಯಾಗಮ;
            }

            X11_Handle_Modifier_ಕೀಲಿಗಳು(videodata, scancode, false);
            SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    ಯದಿ (pressed) {
        X11_UpdateUserTime(windowdata, xevent->xkey.time);
    }
}

ಶೂನ್ಯ X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, ಪೂರ್ಣಾಙ್ಕ button, ಭಿನ್ನ x, ಭಿನ್ನ y, unsigned long time, unsigned long serial)
{
    SDL_Window *window = windowdata->window;
    ಪೂರ್ಣಾಙ್ಕ xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#endif

    SDL_Mouse *mouse = SDL_GetMouse();
    ಯದಿ (!mouse->relative_mode && (x != mouse->x || y != mouse->y)) {
        X11_ProcessHitTest(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, window, mouseID, false, x, y);
    }

    ಯದಿ (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, window, mouseID, (ಭಿನ್ನ)-xticks, (ಭಿನ್ನ)yticks, SDL_MOUSEWHEEL_NORMAL);
    } ಅನ್ಯಥಾ {
        ಯದಿ (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        ಯದಿ (button == Button1) {
            ಯದಿ (X11_TriggerHitTestAction(_this, windowdata, x, y)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0);
                ಪ್ರತ್ಯಾಗಮ; // don't pass this event on to app.
            }
        }
        ಯದಿ (windowdata->last_focus_event_time) {
            ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ X11_FOCUS_CLICK_TIMEOUT = 10;
            ಯದಿ (SDL_GetTicks() < (windowdata->last_focus_event_time + X11_FOCUS_CLICK_TIMEOUT)) {
                ಯದಿ (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->last_focus_event_time = 0;
        }
        ಯದಿ (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, window, mouseID, button, true);
        }
    }
    X11_UpdateUserTime(windowdata, time);
}

ಶೂನ್ಯ X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, ಪೂರ್ಣಾಙ್ಕ button, unsigned long time)
{
    SDL_Window *window = windowdata->window;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    ಪೂರ್ಣಾಙ್ಕ xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#endif
    ಯದಿ (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        ಯದಿ (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, window, mouseID, button, false);

        ಯದಿ (window->internal->pending_grab) {
            X11_SetWindowMouseGrab(_this, window, true);
        }
    }
}

ಶೂನ್ಯ X11_Get_Border_ಮೌಲ್ಯಗಳು(SDL_WindowData *data)
{
    SDL_VideoData *videodata = data->videodata;
    Display *display = videodata->display;

    Atom type;
    ಪೂರ್ಣಾಙ್ಕ format;
    unsigned long nitems, bytes_after;
    unsigned ವರ್ಣ *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    ಯದಿ (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
        ಯದಿ (X11_XGetWindowProperty(display, data->xwindow, videodata->atoms._NET_FRAME_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &bytes_after, &property) == Success) {
            ಯದಿ (type != None && nitems == 4) {
                data->border_ಎಡ = (ಪೂರ್ಣಾಙ್ಕ)((long *)property)[0];
                data->border_ಬಲ = (ಪೂರ್ಣಾಙ್ಕ)((long *)property)[1];
                data->border_ತುದಿ = (ಪೂರ್ಣಾಙ್ಕ)((long *)property)[2];
                data->border_bottom = (ಪೂರ್ಣಾಙ್ಕ)((long *)property)[3];
            }
            X11_XFree(property);

#ifdef DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", data->border_ಎಡ, data->border_ಬಲ, data->border_ತುದಿ, data->border_bottom);
#endif
        }
    } ಅನ್ಯಥಾ {
        data->border_ಎಡ = data->border_ತುದಿ = data->border_ಬಲ = data->border_bottom = 0;
    }
}

ಶೂನ್ಯ X11_EmitConfigureNotifyEvents(SDL_WindowData *data, XConfigureEvent *xevent)
{
    ಯದಿ (!data->size_move_event_flags) {
        ಪೂರ್ಣಾಙ್ಕ x = xevent->x;
        ಪೂರ್ಣಾಙ್ಕ y = xevent->y;

        ಯದಿ (xevent->x != data->last_xconfigure.x ||
            xevent->y != data->last_xconfigure.y) {
            data->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);

        ಪ್ರತಿ (SDL_Window *w = data->window->first_child; w; w = w->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            ಯದಿ (SDL_WINDOW_IS_POPUP(w) && !(w->flags & SDL_WINDOW_HIDDEN)) {
                X11_UpdateWindowPosition(w, true);
            }
        }

        ಯದಿ (xevent->width != data->last_xconfigure.width ||
            xevent->height != data->last_xconfigure.height) {
            data->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, xevent->width, xevent->height);
    }

    SDL_copyp(&data->last_xconfigure, xevent);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display;
    SDL_WindowData *data;
    XClientMessageEvent m;
    ಪೂರ್ಣಾಙ್ಕ i;

    SDL_assert(videodata != ರಿಕ್ತ);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    ಯದಿ (xevent->type != ಕೀಲಿ_Press && xevent->type != ಕೀಲಿ_Release) {
        ಯದಿ (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            ಪ್ರತ್ಯಾಗಮ;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    ಯದಿ (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        ಪ್ರತ್ಯಾಗಮ;
    }
#endif

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    ಯದಿ (g_X11EventHook) {
        ಯದಿ (!g_X11EventHook(g_X11EventHookData, xevent)) {
            ಪ್ರತ್ಯಾಗಮ;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    ಯದಿ (videodata->xrandr_event_base && (xevent->type == (videodata->xrandr_event_base + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#endif

#ifdef DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.window);
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    ಯದಿ (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#endif

        ಯದಿ (ev->subtype == XFixesSetSelectionOwnerNotify)
        {
            ಯದಿ (ev->selection != videodata->atoms.CLIPBOARD)
                ಪ್ರತ್ಯಾಗಮ;

            ಯದಿ (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_window)
                ಪ್ರತ್ಯಾಗಮ;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, GetWindow(_this), CurrentTime);
        }

        ಪ್ರತ್ಯಾಗಮ;
    }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES

    ಯದಿ ((videodata->clipboard_window != None) &&
        (videodata->clipboard_window == xevent->xany.window)) {
        X11_HandleClipboardEvent(_this, xevent);
        ಪ್ರತ್ಯಾಗಮ;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    data = X11_FindWindow(videodata, xevent->xany.window);

    ಯದಿ (!data) {
        // The window for KeymapNotify, etc events is 0
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        ಯದಿ (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            ವಿಕಲ್ಪ (xkbevent->any.xkb_type) {
            ಪಕ್ಷ XkbStateNotify:
            {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.window);
#endif
                ಯದಿ ((xkbevent->state.changed & XkbGroupStateMask) && xkbevent->state.group != videodata->keyboard.xkb.current_group) {
                    videodata->keyboard.xkb.current_group = xkbevent->state.group;
                    SDL_SetKeymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_group], true);
                }

                ಯದಿ (xkbevent->state.changed & XkbModifierStateMask) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.base_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } ಭಙ್ಗ;

            ಪಕ್ಷ XkbMapNotify:
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.window);
                SDL_FALLTHROUGH;
#endif
            ಪಕ್ಷ XkbNewKeyboardNotify:
            {
#ifdef DEBUG_XEVENTS
                ಯದಿ (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.window);
                }
#endif
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                ಯದಿ (xkbevent->any.serial != videodata->keyboard.xkb.last_map_serial) {
                    videodata->keyboard.xkb.last_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } ಭಙ್ಗ;

            ಸ್ವಭಾವ:
                ಭಙ್ಗ;
            }
        } ಅನ್ಯಥಾ
#endif
        ಯದಿ (xevent->type == KeymapNotify) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.window);
#endif
            ಯದಿ (SDL_GetKeyboardFocus() != ರಿಕ್ತ) {
                ಯದಿ (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } ಅನ್ಯಥಾ ಯದಿ (xevent->type == MappingNotify) {
            ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ request = xevent->xmapping.request;

            ಯದಿ (request == MappingPointer) {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                X11_Xinput2UpdatePointerMapping(_this);
            } ಅನ್ಯಥಾ ಯದಿ (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                ಯದಿ (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } ಅನ್ಯಥಾ ಯದಿ (xevent->type == PropertyNotify && videodata) {
            ವರ್ಣ *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            ಯದಿ (name_of_atom) {
                ಯದಿ (SDL_startswith(name_of_atom, "_ICC_PROFILE")) {
                    XWindowAttributes attrib;
                    ಪೂರ್ಣಾಙ್ಕ screennum;
                    ಪ್ರತಿ (i = 0; i < videodata->numwindows; ++i) {
                        ಯದಿ (videodata->windowlist[i] != ರಿಕ್ತ) {
                            data = videodata->windowlist[i];
                            X11_XGetWindowAttributes(display, data->xwindow, &attrib);
                            screennum = X11_XScreen_ಸಂಖ್ಯೆ_Of_Screen(attrib.screen);
                            ಯದಿ (screennum == 0 && SDL_strcmp(name_of_atom, "_ICC_PROFILE") == 0) {
                                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                            } ಅನ್ಯಥಾ ಯದಿ (SDL_strncmp(name_of_atom, "_ICC_PROFILE_", ಪರಿಮಾಣ("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_of_atom) > ಪರಿಮಾಣ("_ICC_PROFILE_") - 1) {
                                ಪೂರ್ಣಾಙ್ಕ iccscreennum = SDL_atoi(&name_of_atom[ಪರಿಮಾಣ("_ICC_PROFILE_") - 1]);

                                ಯದಿ (screennum == iccscreennum) {
                                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                                }
                            }
                        }
                    }
                } ಅನ್ಯಥಾ ಯದಿ (SDL_strcmp(name_of_atom, "_NET_WORKAREA") == 0) {
                    ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
                    }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
                } ಅನ್ಯಥಾ ಯದಿ (SDL_strcmp(name_of_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_of_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#endif
                }
                X11_XFree(name_of_atom);
            }
        }
        ಪ್ರತ್ಯಾಗಮ;
    }

    ವಿಕಲ್ಪ (xevent->type) {

        // Gaining mouse coverage?
    ಪಕ್ಷ EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        ಯದಿ (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        ಯದಿ (xevent->xcrossing.mode == NotifyUngrab) {
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
            ಯದಿ ((data->pointer_barrier_active == true) && windowdata->window->flags & SDL_WINDOW_ಒಳಹರಿವು_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->window, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#endif

        ಯದಿ (!mouse->relative_mode) {
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (ಭಿನ್ನ)xevent->xcrossing.x, (ಭಿನ್ನ)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        ಯದಿ (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            SDL_UpdateWindowGrab(data->window);
        }

        X11_ProcessHitTest(_this, data, mouse->last_x, mouse->last_y, true);
    } ಭಙ್ಗ;
        // Losing mouse coverage?
    ಪಕ್ಷ LeaveNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        ಯದಿ (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        ಯದಿ (xevent->xcrossing.mode == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#endif
        ಯದಿ (!SDL_GetMouse()->relative_mode) {
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (ಭಿನ್ನ)xevent->xcrossing.x, (ಭಿನ್ನ)xevent->xcrossing.y);
        }

        ಯದಿ (xevent->xcrossing.mode != NotifyGrab &&
            xevent->xcrossing.mode != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            ಯದಿ (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                X11_SetWindowKeyboardGrab(_this, data->window, false);
            }

            SDL_SetMouseFocus(ರಿಕ್ತ);
        }
    } ಭಙ್ಗ;

        // Gaining input focus?
    ಪಕ್ಷ FocusIn:
    {
        ಯದಿ (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            ಭಙ್ಗ;
        }

        ಯದಿ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            ಭಙ್ಗ;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.window);
#endif
        ಯದಿ (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            data->pending_focus = PENDING_FOCUS_NONE;
            data->pending_focus_time = 0;
            X11_DispatchFocusIn(_this, data);
        } ಅನ್ಯಥಾ {
            data->pending_focus = PENDING_FOCUS_IN;
            data->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }
        data->last_focus_event_time = SDL_GetTicks();
    } ಭಙ್ಗ;

        // Losing input focus?
    ಪಕ್ಷ FocusOut:
    {
        ಯದಿ (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            ಭಙ್ಗ;
        }
        ಯದಿ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            ಭಙ್ಗ;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.window);
#endif
        ಯದಿ (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            data->pending_focus = PENDING_FOCUS_NONE;
            data->pending_focus_time = 0;
            X11_DispatchFocusOut(_this, data);
        } ಅನ್ಯಥಾ {
            data->pending_focus = PENDING_FOCUS_OUT;
            data->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        ಯದಿ (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, ರಿಕ್ತ, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } ಭಙ್ಗ;


        // Have we been iconified?
    ಪಕ್ಷ UnmapNotify:
    {
        XEvent ev;

#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.window);
#endif

        ಯದಿ (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } ಅನ್ಯಥಾ {
            X11_DispatchUnmapNotify(data);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        ಯದಿ (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, ರಿಕ್ತ, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } ಭಙ್ಗ;

        // Have we been restored?
    ಪಕ್ಷ MapNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.window);
#endif
        X11_DispatchMapNotify(data);

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        ಯದಿ (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, &data->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } ಭಙ್ಗ;

        // Have we been resized or moved?
    ಪಕ್ಷ ConfigureNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.window,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.width, xevent->xconfigure.height);
#endif
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        ಯದಿ (!xevent->xconfigure.send_event) {
            unsigned ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_Children;
            Window ChildReturn, ಬೇರು_2, Parent;
            Window *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_last_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

            X11_XQuery_ವೃಕ್ಷ(data->videodata->display, xevent->xconfigure.window, &ಬೇರು_2, &Parent, &Children, &ಅಂಕೆ_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      Parent, Default_ಬೇರು_Window(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &ChildReturn);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            ಯದಿ (x11_last_error == BadWindow) {
                ಭಙ್ಗ;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        ಧ್ರುವ SDL_WindowFlags changed = X11_GetNetWMState(_this, data->window, xevent->xproperty.window) ^ data->window->flags;
        ಯದಿ (changed & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) {
            SDL_copyp(&data->pending_xconfigure, &xevent->xconfigure);
            data->emit_size_move_after_property_notify = true;
        }

        ಯದಿ (!data->emit_size_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(data, &xevent->xconfigure);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(data->window, &xevent->xconfigure);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } ಭಙ್ಗ;

        // Have we been requested to quit (or another client message?)
    ಪಕ್ಷ ClientMessage:
    {
        ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ xdnd_version = 0;

        ಯದಿ (xevent->xclient.message_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.data.l[1] & 1;
            data->xdnd_source = xevent->xclient.data.l[0];
            xdnd_version = (xevent->xclient.data.l[1] >> 24);
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", data->xdnd_source);
            SDL_Log("Protocol version to use : %d", xdnd_version);
            SDL_Log("More then 3 data types : %d", (ಪೂರ್ಣಾಙ್ಕ)use_list);
#endif

            ಯದಿ (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, data->xdnd_source, videodata->atoms.XdndTypeList);
                // pick one
                data->xdnd_req = X11_PickTarget(display, (Atom *)p.data, p.ಎಣಿಕೆ);
                X11_XFree(p.data);
            } ಅನ್ಯಥಾ {
                // pick from list of three
                data->xdnd_req = X11_PickTargetFromAtoms(display, xevent->xclient.data.l[2], xevent->xclient.data.l[3], xevent->xclient.data.l[4]);
            }
        } ಅನ್ಯಥಾ ಯದಿ (xevent->xclient.message_type == videodata->atoms.XdndLeave) {
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.data.l[0]);
#endif
            SDL_SendDropComplete(data->window);
        } ಅನ್ಯಥಾ ಯದಿ (xevent->xclient.message_type == videodata->atoms.XdndPosition) {

#ifdef DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            ಯದಿ (xdnd_version >= 2) {
                act = xevent->xclient.data.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#endif
            {
                // Drag and Drop position
                ಪೂರ್ಣಾಙ್ಕ ಬೇರು_x, ಬೇರು_y, window_x, window_y;
                Window ChildReturn;
                ಬೇರು_x = xevent->xclient.data.l[2] >> 16;
                ಬೇರು_y = xevent->xclient.data.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_ಬೇರು_Window(display), data->xwindow,
                                          ಬೇರು_x, ಬೇರು_y, &window_x, &window_y, &ChildReturn);

                SDL_SendDropPosition(data->window, (ಭಿನ್ನ)window_x, (ಭಿನ್ನ)window_y);
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
        } ಅನ್ಯಥಾ ಯದಿ (xevent->xclient.message_type == videodata->atoms.XdndDrop) {
            ಯದಿ (data->xdnd_req == None) {
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
            } ಅನ್ಯಥಾ {
                // convert
                ಯದಿ (xdnd_version >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, data->xdnd_req, videodata->atoms.PRIMARY, data->xwindow, xevent->xclient.data.l[2]);
                } ಅನ್ಯಥಾ {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, data->xdnd_req, videodata->atoms.PRIMARY, data->xwindow, CurrentTime);
                }
            }
        } ಅನ್ಯಥಾ ಯದಿ ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.data.l[0] == videodata->atoms._NET_WM_PING)) {
            Window ಬೇರು = Default_ಬೇರು_Window(display);

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.window);
#endif
            xevent->xclient.window = ಬೇರು;
            X11_XSendEvent(display, ಬೇರು, False, SubstructureRedirectMask | SubstructureNotifyMask, xevent);
            ಭಙ್ಗ;
        }

        ಅನ್ಯಥಾ ಯದಿ ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.data.l[0] == videodata->atoms.WM_DELETE_WINDOW)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.window);
#endif
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            ಭಙ್ಗ;
        } ಅನ್ಯಥಾ ಯದಿ ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.data.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", data);
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(data->window, &xevent->xclient);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
            ಭಙ್ಗ;
        }
    } ಭಙ್ಗ;

        // Do we need to refresh ourselves?
    ಪಕ್ಷ Expose:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.window, xevent->xexpose.ಎಣಿಕೆ);
#endif
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    } ಭಙ್ಗ;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    ಪಕ್ಷ ಕೀಲಿ_Press:
    ಪಕ್ಷ ಕೀಲಿ_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        ಯದಿ (data->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            ಭಙ್ಗ;
        } ಅನ್ಯಥಾ ಯದಿ (xevent->xkey.serial == videodata->xinput_last_ಕೀಲಿ_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_last_keyboard_device;
        }

        X11_Handle_ಕೀಲಿ_Event(_this, data, keyboardID, xevent);
    } ಭಙ್ಗ;

    ಪಕ್ಷ MotionNotify:
    {
        ಯದಿ (X11_Xinput2HandlesMotionForWindow(data)) {
            // This input is being handled by XInput2
            ಭಙ್ಗ;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        ಯದಿ (!mouse->relative_mode) {
#ifdef DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.window, xevent->xmotion.x, xevent->xmotion.y);
#endif

            X11_ProcessHitTest(_this, data, (ಭಿನ್ನ)xevent->xmotion.x, (ಭಿನ್ನ)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (ಭಿನ್ನ)xevent->xmotion.x, (ಭಿನ್ನ)xevent->xmotion.y);
        }
    } ಭಙ್ಗ;

    ಪಕ್ಷ ButtonPress:
    {
        ಯದಿ (data->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            ಭಙ್ಗ;
        }

        X11_HandleButtonPress(_this, data, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.time, xevent->xbutton.serial);
    } ಭಙ್ಗ;

    ಪಕ್ಷ ButtonRelease:
    {
        ಯದಿ (data->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            ಭಙ್ಗ;
        }

        X11_HandleButtonRelease(_this, data, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.time);
    } ಭಙ್ಗ;

    ಪಕ್ಷ PropertyNotify:
    {
#ifdef DEBUG_XEVENTS
        unsigned ವರ್ಣ *propdata;
        ಪೂರ್ಣಾಙ್ಕ status, real_format;
        Atom real_type;
        unsigned long ವಸ್ತುಗಳು_read, ವಸ್ತುಗಳು_ಎಡ;

        ವರ್ಣ *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        ಯದಿ (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.window, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.time);
            X11_XFree(name);
        }

        status = X11_XGetWindowProperty(display, data->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ, &propdata);
        ಯದಿ (status == Success && ವಸ್ತುಗಳು_read > 0) {
            ಯದಿ (real_type == XA_INTEGER) {
                ಪೂರ್ಣಾಙ್ಕ *ಮೌಲ್ಯಗಳು = (ಪೂರ್ಣಾಙ್ಕ *)propdata;

                SDL_Log("{");
                ಪ್ರತಿ (i = 0; i < ವಸ್ತುಗಳು_read; i++) {
                    SDL_Log(" %d", ಮೌಲ್ಯಗಳು[i]);
                }
                SDL_Log(" }");
            } ಅನ್ಯಥಾ ಯದಿ (real_type == XA_CARDINAL) {
                ಯದಿ (real_format == 32) {
                    Uint32 *ಮೌಲ್ಯಗಳು = (Uint32 *)propdata;

                    SDL_Log("{");
                    ಪ್ರತಿ (i = 0; i < ವಸ್ತುಗಳು_read; i++) {
                        SDL_Log(" %d", ಮೌಲ್ಯಗಳು[i]);
                    }
                    SDL_Log(" }");
                } ಅನ್ಯಥಾ ಯದಿ (real_format == 16) {
                    Uint16 *ಮೌಲ್ಯಗಳು = (Uint16 *)propdata;

                    SDL_Log("{");
                    ಪ್ರತಿ (i = 0; i < ವಸ್ತುಗಳು_read; i++) {
                        SDL_Log(" %d", ಮೌಲ್ಯಗಳು[i]);
                    }
                    SDL_Log(" }");
                } ಅನ್ಯಥಾ ಯದಿ (real_format == 8) {
                    Uint8 *ಮೌಲ್ಯಗಳು = (Uint8 *)propdata;

                    SDL_Log("{");
                    ಪ್ರತಿ (i = 0; i < ವಸ್ತುಗಳು_read; i++) {
                        SDL_Log(" %d", ಮೌಲ್ಯಗಳು[i]);
                    }
                    SDL_Log(" }");
                }
            } ಅನ್ಯಥಾ ಯದಿ (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } ಅನ್ಯಥಾ ಯದಿ (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                ಪ್ರತಿ (i = 0; i < ವಸ್ತುಗಳು_read; i++) {
                    ವರ್ಣ *atomname = X11_XGetAtomName(display, atoms[i]);
                    ಯದಿ (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } ಅನ್ಯಥಾ {
                ವರ್ಣ *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                ಯದಿ (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        ಯದಿ (status == Success) {
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
        ಯದಿ (!data->user_time) {
            data->user_time = xevent->xproperty.time;
        }

        ಯದಿ (xevent->xproperty.atom == data->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            ಧ್ರುವ SDL_WindowFlags flags = X11_GetNetWMState(_this, data->window, xevent->xproperty.window);
            ಧ್ರುವ SDL_WindowFlags changed = flags ^ data->window->flags;

            ಯದಿ ((changed & SDL_WINDOW_HIDDEN) && !(flags & SDL_WINDOW_HIDDEN)) {
                X11_DispatchMapNotify(data);
            }

            ಯದಿ (!SDL_WINDOW_IS_POPUP(data->window)) {
                ಯದಿ (changed & SDL_WINDOW_FULLSCREEN) {
                    data->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    ಯದಿ (flags & SDL_WINDOW_FULLSCREEN) {
                        ಯದಿ (!(flags & SDL_WINDOW_MINIMIZED)) {
                            ಧ್ರುವ bool commit = SDL_memcmp(&data->window->current_fullscreen_mode, &data->requested_fullscreen_mode, ಪರಿಮಾಣ(SDL_DisplayMode)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                            ಯದಿ (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&data->window->current_fullscreen_mode, &data->window->requested_fullscreen_mode);
                                SDL_UpdateFullscreenMode(data->window, SDL_FULLSCREEN_OP_UPDATE, true);
                            } ಅನ್ಯಥಾ {
                                SDL_UpdateFullscreenMode(data->window, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } ಅನ್ಯಥಾ {
                        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                        SDL_UpdateFullscreenMode(data->window, false, false);

                        SDL_zero(data->requested_fullscreen_mode);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_SetWindowMinMax(data->window, !!(flags & SDL_WINDOW_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        ಯದಿ (data->fullscreen_borders_forced_on) {
                            data->toggle_borders = true;
                            data->fullscreen_borders_forced_on = false;
                        }
                    }

                    ಯದಿ ((flags & SDL_WINDOW_FULLSCREEN) &&
                        (data->border_ತುದಿ || data->border_ಎಡ || data->border_bottom || data->border_ಬಲ)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        data->size_move_event_flags |= X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        data->previous_borders_nonzero = true;
                    } ಅನ್ಯಥಾ ಯದಿ (!(flags & SDL_WINDOW_FULLSCREEN) &&
                               data->previous_borders_nonzero &&
                               (!data->border_ತುದಿ && !data->border_ಎಡ && !data->border_bottom && !data->border_ಬಲ)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        data->size_move_event_flags |= X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        data->previous_borders_nonzero = false;
                    } ಅನ್ಯಥಾ {
                        data->size_move_event_flags = 0;
                        data->previous_borders_nonzero = false;

                        ಯದಿ (!(data->window->flags & SDL_WINDOW_FULLSCREEN) && data->toggle_borders) {
                            data->toggle_borders = false;
                            X11_SetWindowBordered(_this, data->window, !(data->window->flags & SDL_WINDOW_BORDERLESS));
                        }
                    }
                }
                ಯದಿ ((changed & SDL_WINDOW_MAXIMIZED) && ((flags & SDL_WINDOW_MAXIMIZED) && !(flags & SDL_WINDOW_MINIMIZED))) {
                    data->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    ಯದಿ ((changed & SDL_WINDOW_MINIMIZED)) {
                        data->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                    }
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
                }
                ಯದಿ ((changed & SDL_WINDOW_MINIMIZED) && (flags & SDL_WINDOW_MINIMIZED)) {
                    data->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                }
                ಯದಿ (!(flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
                    data->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    ಯದಿ (!(flags & SDL_WINDOW_FULLSCREEN)) {
                        ಯದಿ (data->pending_position) {
                            data->pending_position = false;
                            data->pending_operation |= X11_PENDING_OP_MOVE;
                            data->expected.x = data->window->pending.x - data->border_ಎಡ;
                            data->expected.y = data->window->pending.y - data->border_ತುದಿ;
                            X11_XMoveWindow(display, data->xwindow, data->expected.x, data->expected.y);
                        }
                        ಯದಿ (data->pending_size) {
                            data->pending_size = false;
                            data->pending_operation |= X11_PENDING_OP_RESIZE;
                            data->expected.w = data->window->pending.w;
                            data->expected.h = data->window->pending.h;
                            X11_XResizeWindow(display, data->xwindow, data->window->pending.w, data->window->pending.h);
                        }
                    }
                }
                ಯದಿ (data->emit_size_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(data, &data->pending_xconfigure);
                    data->emit_size_move_after_property_notify = false;
                }
                ಯದಿ ((flags & SDL_WINDOW_ಒಳಹರಿವು_FOCUS)) {
                    ಯದಿ (data->pending_move) {
                        DispatchWindowMove(_this, data, &data->pending_move_point);
                        data->pending_move = false;
                    }
                }
            }
            ಯದಿ (changed & SDL_WINDOW_OCCLUDED) {
                SDL_SendWindowEvent(data->window, (flags & SDL_WINDOW_OCCLUDED) ? SDL_EVENT_WINDOW_OCCLUDED : SDL_EVENT_WINDOW_EXPOSED, 0, 0);
            }
        } ಅನ್ಯಥಾ ಯದಿ (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            ಪೂರ್ಣಾಙ್ಕ format;
            unsigned long nitems, bytes_after;
            unsigned ವರ್ಣ *prop_data = ರಿಕ್ತ;

            ಯದಿ (X11_XGetWindowProperty(display, data->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &bytes_after, &prop_data) == Success) {
                ಯದಿ (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_data;

                    ಯದಿ ((state == 0 || state == 3) && !data->window->is_hiding && !(data->window->flags & SDL_WINDOW_HIDDEN)) {
                        // Withdrawn or Iconic
                        ಯದಿ (!(data->window->flags & SDL_WINDOW_MINIMIZED)) {
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
                        }
                    } ಅನ್ಯಥಾ ಯದಿ (state == 1) { // NormalState
                        ಯದಿ (data->window->flags & SDL_WINDOW_MINIMIZED) {
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_data);
            }
        } ಅನ್ಯಥಾ ಯದಿ (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } ಅನ್ಯಥಾ ಯದಿ (xevent->xproperty.atom == videodata->atoms._NET_FRAME_EXTENTS) {
            X11_Get_Border_ಮೌಲ್ಯಗಳು(data);
            ಯದಿ (data->size_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                data->size_move_event_flags &= ~X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            ಯದಿ (!(data->window->flags & SDL_WINDOW_FULLSCREEN) && data->toggle_borders) {
                data->toggle_borders = false;
                X11_SetWindowBordered(_this, data->window, !(data->window->flags & SDL_WINDOW_BORDERLESS));
            }
        }
    } ಭಙ್ಗ;

    ಪಕ್ಷ SelectionNotify:
    {
        Atom target = xevent->xselection.target;
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.window,
               xevent->xselection.requestor, xevent->xselection.target);
#endif
        ಯದಿ (target == data->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, data->xwindow, videodata->atoms.PRIMARY);

            ಯದಿ (p.format == 8) {
                ವರ್ಣ *saveptr = ರಿಕ್ತ;
                ವರ್ಣ *name = X11_XGetAtomName(display, target);
                ಯದಿ (name) {
                    ವರ್ಣ *token = SDL_strtok_r((ವರ್ಣ *)p.data, "\r\n", &saveptr);
                    ಯಾವತ್ (token) {
                        ಯದಿ ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_SendDropText(data->window, token);
                        } ಅನ್ಯಥಾ ಯದಿ (SDL_strcmp("text/uri-list", name) == 0) {
                            ಯದಿ (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(data->window, ರಿಕ್ತ, token);
                            }
                        }
                        token = SDL_strtok_r(ರಿಕ್ತ, "\r\n", &saveptr);
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
    } ಭಙ್ಗ;

    ಸ್ವಭಾವ:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.window, xevent->type);
#endif
    } ಭಙ್ಗ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (videodata && videodata->windowlist) {
        ಪ್ರತಿ (i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *data = videodata->windowlist[i];
            ಯದಿ (data && data->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                ಯದಿ (now >= data->pending_focus_time) {
                    ಯದಿ (data->pending_focus == PENDING_FOCUS_IN) {
                        X11_DispatchFocusIn(_this, data);
                    } ಅನ್ಯಥಾ {
                        X11_DispatchFocusOut(_this, data);
                    }
                    data->pending_focus = PENDING_FOCUS_NONE;
                }
            }
        }
    }
}

ಸ್ಥಿರ Bool isAnyEvent(Display *display, XEvent *ev, XPointer arg)
{
    ಪ್ರತ್ಯಾಗಮ True;
}

ಸ್ಥಿರ bool X11_PollEvent(Display *display, XEvent *event)
{
    ಯದಿ (!X11_XCheckIfEvent(display, event, isAnyEvent, ರಿಕ್ತ)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
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

ಪೂರ್ಣಾಙ್ಕ X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    ಯದಿ (X11_PollEvent(display, &xevent)) {
        // Fall through
    } ಅನ್ಯಥಾ ಯದಿ (timeoutNS == 0) {
        ಪ್ರತ್ಯಾಗಮ 0;
    } ಅನ್ಯಥಾ {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        ಪೂರ್ಣಾಙ್ಕ err = SDL_IOReady(Connection_ಸಂಖ್ಯೆ(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        ಯದಿ (err > 0) {
            ಯದಿ (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                ಪ್ರತ್ಯಾಗಮ 1;
            }
        } ಅನ್ಯಥಾ ಯದಿ (err == 0) {
            // Timeout
            ಪ್ರತ್ಯಾಗಮ 0;
        } ಅನ್ಯಥಾ {
            // Error returned from poll()/select()

            ಯದಿ (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                ಪ್ರತ್ಯಾಗಮ 1;
            } ಅನ್ಯಥಾ {
                ಪ್ರತ್ಯಾಗಮ err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    ಪ್ರತ್ಯಾಗಮ 1;
}

ಶೂನ್ಯ X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    XEvent xevent;
    ಪೂರ್ಣಾಙ್ಕ i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        ಯದಿ (_this->displays[i]->internal->mode_switch_deadline_ns) {
            ಯದಿ (_this->displays[i]->fullscreen_window) {
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            } ಅನ್ಯಥಾ ಯದಿ (SDL_GetTicksNS() >= _this->displays[i]->internal->mode_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_SetDisplayModeForDisplay(_this->displays[i], ರಿಕ್ತ);
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            }
        }
    }

    ಯದಿ (data->last_mode_change_deadline) {
        ಯದಿ (SDL_GetTicks() >= data->last_mode_change_deadline) {
            data->last_mode_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    ಯದಿ (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        ಯದಿ (!data->screensaver_activity || now >= (data->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(data->display);

#ifdef SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#endif

            data->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    ಯಾವತ್ (X11_PollEvent(data->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    ಪ್ರತಿ (i = 0; i < data->numwindows; ++i) {
        ಯದಿ (data->windowlist[i] != ರಿಕ್ತ &&
            data->windowlist[i]->flash_cancel_time &&
            SDL_GetTicks() >= data->windowlist[i]->flash_cancel_time) {
            X11_FlashWindow(_this, data->windowlist[i]->window, SDL_FLASH_CANCEL);
        }
    }

    ಯದಿ (data->xinput_hierarchy_changed) {
        X11_Xinput2UpdateDevices(_this);
        data->xinput_hierarchy_changed = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_VideoData *data = _this->internal;
    ಪೂರ್ಣಾಙ್ಕ dummy;
    ಪೂರ್ಣಾಙ್ಕ major_version, minor_version;
#endif // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#ifdef SDL_USE_LIBDBUS
    ಯದಿ (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    ಯದಿ (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        ಯದಿ (!X11_XScreenSaverQueryExtension(data->display, &dummy, &dummy) ||
            !X11_XScreenSaverQueryVersion(data->display,
                                          &major_version, &minor_version) ||
            major_version < 1 || (major_version == 1 && minor_version < 1)) {
            ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(data->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(data->display);
        ಪ್ರತ್ಯಾಗಮ true;
    }
#endif
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

#endif // SDL_VIDEO_DRIVER_X11
