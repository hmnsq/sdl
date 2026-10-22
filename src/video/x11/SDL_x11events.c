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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#അന്തര്ഭാവ <sys/types.h>
#അന്തര്ഭാവ <sys/time.h>
#അന്തര്ഭാവ <signal.h>
#അന്തര്ഭാവ <unistd.h>
#അന്തര്ഭാവ <limits.h> // For INT_MAX

#അന്തര്ഭാവ "SDL_x11video.h"
#അന്തര്ഭാവ "SDL_x11pen.h"
#അന്തര്ഭാവ "SDL_x11touch.h"
#അന്തര്ഭാവ "SDL_x11xinput2.h"
#അന്തര്ഭാവ "SDL_x11xfixes.h"
#അന്തര്ഭാവ "SDL_x11settings.h"
#അന്തര്ഭാവ "../SDL_clipboard_c.h"
#അന്തര്ഭാവ "SDL_x11xsync.h"
#അന്തര്ഭാവ "../../core/unix/SDL_poll.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../events/SDL_touch_c.h"
#അന്തര്ഭാവ "../../core/linux/SDL_system_theme.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"

#അന്തര്ഭാവ <stdio.h>

#എങ്കിൽ 0
#define DEBUG_XEVENTS
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPLEFT
#define _NET_WM_MOVERESIZE_SIZE_TOPLEFT 0
#endif

#ifndef NET_WM_MOVERESIZE_SIZE_മുകൾ
#define NET_WM_MOVERESIZE_SIZE_മുകൾ 1
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPRIGHT
#define _NET_WM_MOVERESIZE_SIZE_TOPRIGHT 2
#endif

#ifndef NET_WM_MOVERESIZE_SIZE_വലത്
#define NET_WM_MOVERESIZE_SIZE_വലത് 3
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

#ifndef NET_WM_MOVERESIZE_SIZE_ഇടത്
#define NET_WM_MOVERESIZE_SIZE_ഇടത് 7
#endif

#ifndef _NET_WM_MOVERESIZE_MOVE
#define _NET_WM_MOVERESIZE_MOVE 8
#endif

തരനിർവചനം ഘടന
{
    unsigned അക്ഷരം *data;
    പൂർണ്ണസംഖ്യ format, എണ്ണം;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
സ്ഥിതം ശൂന്യം X11_ReadProperty(SDL_x11Prop *p, Display *disp, Window w, Atom prop)
{
    unsigned അക്ഷരം *ret = ശൂന്യ;
    Atom type;
    പൂർണ്ണസംഖ്യ fmt;
    unsigned long എണ്ണം;
    unsigned long bytes_ഇടത്;
    പൂർണ്ണസംഖ്യ bytes_fetch = 0;

    ചെയ്യുക {
        എങ്കിൽ (ret) {
            X11_XFree(ret);
        }
        X11_XGetWindowProperty(disp, w, prop, 0, bytes_fetch, False, AnyPropertyType, &type, &fmt, &എണ്ണം, &bytes_ഇടത്, &ret);
        bytes_fetch += bytes_ഇടത്;
    } ആകുമ്പോൾ (bytes_ഇടത് != 0);

    p->data = ret;
    p->format = fmt;
    p->എണ്ണം = എണ്ണം;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
സ്ഥിതം Atom X11_PickTarget(Display *disp, Atom list[], പൂർണ്ണസംഖ്യ list_എണ്ണം)
{
    സ്ഥിരം Atom text_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < list_എണ്ണം && request != text_uri_request; i++) {
        അക്ഷരം *name = X11_XGetAtomName(disp, list[i]);
        // Preferred MIME targets
        എങ്കിൽ ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            എങ്കിൽ (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        എങ്കിൽ ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            എങ്കിൽ (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    എങ്കിൽ (preferred != None && request != text_uri_request) {
        request = preferred;
    }
    തിരികെ request;
}

/* Wrapper for X11_PickTarget for a maximum of three targets, a special
   case in the Xdnd protocol */
സ്ഥിതം Atom X11_PickTargetFromAtoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    പൂർണ്ണസംഖ്യ എണ്ണം = 0;
    Atom atom[3];
    എങ്കിൽ (a0 != None) {
        atom[എണ്ണം++] = a0;
    }
    എങ്കിൽ (a1 != None) {
        atom[എണ്ണം++] = a1;
    }
    എങ്കിൽ (a2 != None) {
        atom[എണ്ണം++] = a2;
    }
    തിരികെ X11_PickTarget(disp, atom, എണ്ണം);
}

ഘടന താക്കോൽ_Repeat_Check_Data
{
    XEvent *event;
    bool found;
};

സ്ഥിതം Bool X11_താക്കോൽ_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    ഘടന താക്കോൽ_Repeat_Check_Data *d = (ഘടന താക്കോൽ_Repeat_Check_Data *)arg;
    എങ്കിൽ (chkev->type == താക്കോൽ_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.time - d->event->xkey.time < 2) {
        d->found = true;
    }
    തിരികെ False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
സ്ഥിതം bool X11_താക്കോൽ_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    ഘടന താക്കോൽ_Repeat_Check_Data d;
    d.event = event;
    d.found = false;
    എങ്കിൽ (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_താക്കോൽ_Repeat_Check_If_Event, (XPointer)&d);
    }
    തിരികെ d.found;
}

bool X11_IsWheelEvent(പൂർണ്ണസംഖ്യ button, പൂർണ്ണസംഖ്യ *xticks, പൂർണ്ണസംഖ്യ *yticks)
{
    /* according to the xlib docs, no specific mouse wheel events exist.
       However, the defacto standard is that the vertical wheel is X buttons
       4 (up) and 5 (down) and a horizontal wheel is 6 (left) and 7 (right). */

    // Xlib defines "Button1" through 5, so we just use literals here.
    തിരഞ്ഞെടുപ്പ് (button) {
    അവസ്ഥ 4:
        *yticks = 1;
        തിരികെ true;
    അവസ്ഥ 5:
        *yticks = -1;
        തിരികെ true;
    അവസ്ഥ 6:
        *xticks = 1;
        തിരികെ true;
    അവസ്ഥ 7:
        *xticks = -1;
        തിരികെ true;
    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }
    തിരികെ false;
}

// An X11 event hook
സ്ഥിതം SDL_X11EventHook g_X11EventHook = ശൂന്യ;
സ്ഥിതം ശൂന്യം *g_X11EventHookData = ശൂന്യ;

ശൂന്യം SDL_SetX11EventHook(SDL_X11EventHook callback, ശൂന്യം *userdata)
{
    g_X11EventHook = callback;
    g_X11EventHookData = userdata;
}

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
സ്ഥിതം ശൂന്യം X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_VideoData *videodata = _this->internal;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    എങ്കിൽ (X11_XGetEventData(videodata->display, cookie)) {
        എങ്കിൽ (!g_X11EventHook || g_X11EventHook(g_X11EventHookData, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFreeEventData(videodata->display, cookie);
    }
}
#endif // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

സ്ഥിതം ശൂന്യം X11_Update_System_താക്കോൽ_Modifiers(SDL_VideoData *viddata)
{
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    എങ്കിൽ (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        എങ്കിൽ (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.base_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } അല്ലെങ്കിൽ
#endif
        {
        Window junk_window;
        പൂർണ്ണസംഖ്യ x, y;
        unsigned പൂർണ്ണസംഖ്യ mod_mask;

        X11_XQueryPointer(viddata->display, Default_വേര്_Window(viddata->display), &junk_window, &junk_window, &x, &y, &x, &y, &mod_mask);
        viddata->keyboard.pressed_modifiers = mod_mask & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        viddata->keyboard.locked_modifiers = mod_mask & (LockMask | viddata->keyboard.numlock_mask | viddata->keyboard.scrolllock_mask);
    }
}

സ്ഥിതം ശൂന്യം X11_ReconcileModifiers(SDL_VideoData *viddata, bool താക്കോൽ_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    എങ്കിൽ (താക്കോൽ_pressed) {
        എങ്കിൽ (viddata->keyboard.pressed_modifiers & ShiftMask) {
            എങ്കിൽ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT);
            }
        }

        എങ്കിൽ (viddata->keyboard.pressed_modifiers & ControlMask) {
            എങ്കിൽ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        എങ്കിൽ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            എങ്കിൽ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        എങ്കിൽ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            എങ്കിൽ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (viddata->keyboard.pressed_modifiers & ShiftMask) {
            എങ്കിൽ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } അല്ലെങ്കിൽ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        എങ്കിൽ (viddata->keyboard.pressed_modifiers & ControlMask) {
            എങ്കിൽ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } അല്ലെങ്കിൽ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        എങ്കിൽ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            എങ്കിൽ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } അല്ലെങ്കിൽ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        എങ്കിൽ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            എങ്കിൽ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } അല്ലെങ്കിൽ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        എങ്കിൽ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_mask) {
            എങ്കിൽ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_MODE)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_MODE;
            }
        } അല്ലെങ്കിൽ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        എങ്കിൽ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_mask) {
            എങ്കിൽ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } അല്ലെങ്കിൽ {
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
    എങ്കിൽ (viddata->keyboard.locked_modifiers & ShiftMask) {
        എങ്കിൽ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT);
        } അല്ലെങ്കിൽ എങ്കിൽ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_SHIFT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } അല്ലെങ്കിൽ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    എങ്കിൽ (viddata->keyboard.locked_modifiers & ControlMask) {
        എങ്കിൽ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } അല്ലെങ്കിൽ എങ്കിൽ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } അല്ലെങ്കിൽ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    എങ്കിൽ (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_mask) {
        എങ്കിൽ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } അല്ലെങ്കിൽ എങ്കിൽ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } അല്ലെങ്കിൽ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    എങ്കിൽ (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_mask) {
        എങ്കിൽ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } അല്ലെങ്കിൽ എങ്കിൽ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } അല്ലെങ്കിൽ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    എങ്കിൽ (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_MODE;
    } അല്ലെങ്കിൽ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_MODE;
    }

    എങ്കിൽ (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } അല്ലെങ്കിൽ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    എങ്കിൽ (viddata->keyboard.locked_modifiers & LockMask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } അല്ലെങ്കിൽ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    എങ്കിൽ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_അക്കം;
    } അല്ലെങ്കിൽ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_അക്കം;
    }

    എങ്കിൽ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } അല്ലെങ്കിൽ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_SetModState(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

സ്ഥിതം ശൂന്യം X11_Handle_Modifier_താക്കോലുകൾ(SDL_VideoData *viddata, SDL_Scancode scancode, bool pressed)
{
    സ്ഥിരം SDL_Keycode keycode = SDL_Get_താക്കോൽ_From_Scancode(scancode, SDL_KMOD_NONE, false);
    SDL_Keymod mod = SDL_KMOD_NONE;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is checked.
     */
    തിരഞ്ഞെടുപ്പ് (keycode) {
    അവസ്ഥ SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        നിർത്തുക;
    അവസ്ഥ SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        നിർത്തുക;
    അവസ്ഥ SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        നിർത്തുക;
    അവസ്ഥ SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        നിർത്തുക;
    അവസ്ഥ SDLK_LALT:
        mod = SDL_KMOD_LALT;
        നിർത്തുക;
    അവസ്ഥ SDLK_RALT:
        mod = SDL_KMOD_RALT;
        നിർത്തുക;
    അവസ്ഥ SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        നിർത്തുക;
    അവസ്ഥ SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        നിർത്തുക;
    അവസ്ഥ SDLK_MODE:
        mod = SDL_KMOD_MODE;
        നിർത്തുക;
    അവസ്ഥ SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        നിർത്തുക;
    അവസ്ഥ SDLK_CAPSLOCK:
    അവസ്ഥ SDLK_NUMLOCKCLEAR:
    അവസ്ഥ SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        എങ്കിൽ (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            unsigned പൂർണ്ണസംഖ്യ cur_mask = viddata->keyboard.locked_modifiers;
            X11_Update_System_താക്കോൽ_Modifiers(viddata);

            എങ്കിൽ (viddata->keyboard.locked_modifiers & LockMask) {
                cur_mask |= LockMask;
            } അല്ലെങ്കിൽ {
                cur_mask &= ~LockMask;
            }
            എങ്കിൽ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
                cur_mask |= viddata->keyboard.numlock_mask;
            } അല്ലെങ്കിൽ {
                cur_mask &= ~viddata->keyboard.numlock_mask;
            }
            എങ്കിൽ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
                cur_mask |= viddata->keyboard.scrolllock_mask;
            } അല്ലെങ്കിൽ {
                cur_mask &= ~viddata->keyboard.scrolllock_mask;
            }

            viddata->keyboard.locked_modifiers = cur_mask;
        }
    } നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        തിരികെ;
    }

    എങ്കിൽ (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } അല്ലെങ്കിൽ {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

ശൂന്യം X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    അക്ഷരം താക്കോലുകൾ[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_താക്കോൽ_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_അക്കം | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= LockMask | videodata->keyboard.numlock_mask| videodata->keyboard.scrolllock_mask;

    X11_XQueryKeymap(display, താക്കോലുകൾ);

    സ്ഥിരം bool *keystate = SDL_GetKeyboardState(ശൂന്യ);
    വേണ്ടി (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.താക്കോൽ_layout); ++keycode) {
        സ്ഥിരം SDL_Scancode scancode = videodata->keyboard.താക്കോൽ_layout[keycode];
        സ്ഥിരം bool x11_താക്കോൽ_Pressed = (താക്കോലുകൾ[keycode / 8] & (1 << (keycode % 8))) != 0;
        സ്ഥിരം bool sdl_താക്കോൽ_Pressed = keystate[scancode];

        എങ്കിൽ (x11_താക്കോൽ_Pressed && !sdl_താക്കോൽ_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            തിരഞ്ഞെടുപ്പ് (SDL_Get_താക്കോൽ_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            അവസ്ഥ SDLK_LCTRL:
            അവസ്ഥ SDLK_RCTRL:
            അവസ്ഥ SDLK_LSHIFT:
            അവസ്ഥ SDLK_RSHIFT:
            അവസ്ഥ SDLK_LALT:
            അവസ്ഥ SDLK_RALT:
            അവസ്ഥ SDLK_LGUI:
            അവസ്ഥ SDLK_RGUI:
            അവസ്ഥ SDLK_MODE:
            അവസ്ഥ SDLK_LEVEL5_SHIFT:
                X11_Handle_Modifier_താക്കോലുകൾ(videodata, scancode, true);
                SDL_Send_Keyboard_താക്കോൽ_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                നിർത്തുക;
            സ്ഥിരസ്ഥിതി:
                നിർത്തുക;
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (!x11_താക്കോൽ_Pressed && sdl_താക്കോൽ_Pressed) {
            X11_Handle_Modifier_താക്കോലുകൾ(videodata, scancode, false);
            SDL_Send_Keyboard_താക്കോൽ_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_താക്കോൽ_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

സ്ഥിതം ശൂന്യം X11_DispatchFocusIn(SDL_VideoDevice *_this, SDL_WindowData *data)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", data->xwindow);
#endif
    SDL_SetKeyboardFocus(data->window);
    X11_ReconcileKeyboardState(_this);
#ifdef X_HAVE_UTF8_STRING
    എങ്കിൽ (data->ic) {
        X11_XSetICFocus(data->ic);
    }
#endif
    എങ്കിൽ (data->flashing_window) {
        X11_FlashWindow(_this, data->window, SDL_FLASH_CANCEL);
    }
}

സ്ഥിതം ശൂന്യം X11_DispatchFocusOut(SDL_VideoDevice *_this, SDL_WindowData *data)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", data->xwindow);
#endif
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    എങ്കിൽ (data->window == SDL_GetKeyboardFocus()) {
        SDL_SetKeyboardFocus(ശൂന്യ);
    }
#ifdef X_HAVE_UTF8_STRING
    എങ്കിൽ (data->ic) {
        X11_XUnsetICFocus(data->ic);
    }
#endif
}

സ്ഥിതം ശൂന്യം X11_DispatchMapNotify(SDL_WindowData *data)
{
    SDL_Window *window = data->window;

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    data->was_shown = true;

    // This may be sent when restoring a minimized window.
    എങ്കിൽ (window->flags & SDL_WINDOW_MINIMIZED) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }

    എങ്കിൽ (window->flags & SDL_WINDOW_നിവേശം_FOCUS) {
        SDL_UpdateWindowGrab(window);
    }
}

സ്ഥിതം ശൂന്യം X11_DispatchUnmapNotify(SDL_WindowData *data)
{
    SDL_Window *window = data->window;

    // This may be sent when minimizing a window.
    എങ്കിൽ (!window->is_hiding) {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
    } അല്ലെങ്കിൽ {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    }
}

സ്ഥിതം ശൂന്യം DispatchWindowMove(SDL_VideoDevice *_this, സ്ഥിരം SDL_WindowData *data, സ്ഥിരം SDL_Point *point)
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
    X11_XSendEvent(display, Default_വേര്_Window(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

സ്ഥിതം ശൂന്യം ScheduleWindowMove(SDL_VideoDevice *_this, SDL_WindowData *data, സ്ഥിരം SDL_Point *point)
{
    data->pending_move = true;
    data->pending_move_point = *point;
}

സ്ഥിതം ശൂന്യം InitiateWindowResize(SDL_VideoDevice *_this, സ്ഥിരം SDL_WindowData *data, സ്ഥിരം SDL_Point *point, പൂർണ്ണസംഖ്യ direction)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_Window *window = data->window;
    Display *display = videodata->display;
    XEvent evt;

    എങ്കിൽ (direction < _NET_WM_MOVERESIZE_SIZE_TOPLEFT || direction > NET_WM_MOVERESIZE_SIZE_ഇടത്) {
        തിരികെ;
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
    X11_XSendEvent(display, Default_വേര്_Window(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_WindowData *data, സ്ഥിരം ദശാംശം x, സ്ഥിരം ദശാംശം y, bool force_new_result)
{
    SDL_Window *window = data->window;
    എങ്കിൽ (!window->hit_test) തിരികെ false;
    സ്ഥിരം SDL_Point point = { (പൂർണ്ണസംഖ്യ)x, (പൂർണ്ണസംഖ്യ)y };
    SDL_HitTestResult rc = window->hit_test(window, &point, window->hit_test_data);
    എങ്കിൽ (!force_new_result && rc == data->hit_test_result) {
        തിരികെ true;
    }
    X11_SetHitTestCursor(rc);
    data->hit_test_result = rc;
    തിരികെ true;
}

bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_WindowData *data, സ്ഥിരം ദശാംശം x, സ്ഥിരം ദശാംശം y)
{
    SDL_Window *window = data->window;

    എങ്കിൽ (window->hit_test) {
        സ്ഥിരം SDL_Point point = { (പൂർണ്ണസംഖ്യ)x, (പൂർണ്ണസംഖ്യ)y };
        സ്ഥിതം സ്ഥിരം പൂർണ്ണസംഖ്യ directions[] = {
            _NET_WM_MOVERESIZE_SIZE_TOPLEFT, NET_WM_MOVERESIZE_SIZE_മുകൾ,
            _NET_WM_MOVERESIZE_SIZE_TOPRIGHT, NET_WM_MOVERESIZE_SIZE_വലത്,
            _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT, _NET_WM_MOVERESIZE_SIZE_BOTTOM,
            _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT, NET_WM_MOVERESIZE_SIZE_ഇടത്
        };

        തിരഞ്ഞെടുപ്പ് (data->hit_test_result) {
        അവസ്ഥ SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            എങ്കിൽ (data->window->flags & SDL_WINDOW_നിവേശം_FOCUS) {
                DispatchWindowMove(_this, data, &point);
            } അല്ലെങ്കിൽ {
                ScheduleWindowMove(_this, data, &point);
            }
            തിരികെ true;

        അവസ്ഥ SDL_HITTEST_RESIZE_TOPLEFT:
        അവസ്ഥ SDL_HITTEST_RESIZE_മുകൾ:
        അവസ്ഥ SDL_HITTEST_RESIZE_TOPRIGHT:
        അവസ്ഥ SDL_HITTEST_RESIZE_വലത്:
        അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOM:
        അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOMLEFT:
        അവസ്ഥ SDL_HITTEST_RESIZE_ഇടത്:
            InitiateWindowResize(_this, data, &point, directions[data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
            തിരികെ true;

        സ്ഥിരസ്ഥിതി:
            തിരികെ false;
        }
    }

    തിരികെ false;
}

സ്ഥിതം ശൂന്യം X11_UpdateUserTime(SDL_WindowData *data, സ്ഥിരം unsigned long latest)
{
    എങ്കിൽ (latest && (latest != data->user_time)) {
        SDL_VideoData *videodata = data->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, data->xwindow, videodata->atoms._NET_WM_USER_TIME,
                            XA_CARDINAL, 32, PropModeReplace,
                            (സ്ഥിരം unsigned അക്ഷരം *)&latest, 1);
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", data->xwindow, latest);
#endif
        data->user_time = latest;
    }
}

സ്ഥിതം unsigned അക്ഷരം x11_last_error;
സ്ഥിതം പൂർണ്ണസംഖ്യ BadWindowErrorHandler(Display *d, XErrorEvent *e)
{
    x11_last_error = e->error_code;

    // Ignore BadWindow in cases where it's not fatal.
    എങ്കിൽ (e->error_code != BadWindow) {
        അക്ഷരം err_സന്ദേശം[128];
        X11_XGetErrorText(d, e->error_code, err_സന്ദേശം, വലുപ്പം(err_സന്ദേശം));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_code, err_സന്ദേശം, e->request_code);
    }
    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം X11_HandleClipboardEvent(SDL_VideoDevice *_this, സ്ഥിരം XEvent *xevent)
{
    പൂർണ്ണസംഖ്യ i;
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_window != None);
    SDL_assert(xevent->xany.window == videodata->clipboard_window);

    തിരഞ്ഞെടുപ്പ് (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    അവസ്ഥ SelectionRequest:
    {
        സ്ഥിരം XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        പൂർണ്ണസംഖ്യ mime_formats;
        unsigned അക്ഷരം *seln_data;
        size_t seln_length = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_ClipboardData *clipboard;

#ifdef DEBUG_XEVENTS
        അക്ഷരം *atom_name;
        atom_name = X11_XGetAtomName(display, req->target);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->target, atom_name);
        എങ്കിൽ (atom_name) {
            X11_XFree(atom_name);
        }
#endif

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_last_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

        എങ്കിൽ (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } അല്ലെങ്കിൽ {
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

        എങ്കിൽ (req->target == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_എണ്ണം + 1) * വലുപ്പം(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            വേണ്ടി (i = 0; i < clipboard->mime_എണ്ണം; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, PropModeReplace,
                                (unsigned അക്ഷരം *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.target = XA_TARGETS;
            SDL_free(supportedFormats);
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (clipboard->callback) {
                വേണ്ടി (i = 0; i < clipboard->mime_എണ്ണം; ++i) {
                    സ്ഥിരം അക്ഷരം *mime_type = clipboard->mime_types[i];
                    എങ്കിൽ (X11_XInternAtom(display, mime_type, False) != req->target) {
                        തുടരുക;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_data = (unsigned അക്ഷരം *)clipboard->callback(clipboard->userdata, mime_type, &seln_length);
                    എങ്കിൽ (seln_data) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->target, 8, PropModeReplace,
                                            seln_data, seln_length);
                        sevent.xselection.property = req->property;
                        sevent.xselection.target = req->target;
                    }
                    നിർത്തുക;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(prev_handler);
    } നിർത്തുക;

    അവസ്ഥ SelectionNotify:
    {
        സ്ഥിരം XSelectionEvent *xsel = &xevent->xselection;
#ifdef DEBUG_XEVENTS
        സ്ഥിരം അക്ഷരം *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        സ്ഥിരം അക്ഷരം *targetName = xsel->target ? X11_XGetAtomName(display, xsel->target) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, targetName, propName);
#endif
        എങ്കിൽ (xsel->target == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            unsigned അക്ഷരം *data = ശൂന്യ;
            പൂർണ്ണസംഖ്യ format_property = 0;
            unsigned long length = 0;
            unsigned long bytes_ഇടത് = 0;
            പൂർണ്ണസംഖ്യ j;

            X11_XGetWindowProperty(display, GetWindow(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &length, &bytes_ഇടത്, &data);

            പൂർണ്ണസംഖ്യ allocationsize = (length + 1) * വലുപ്പം(അക്ഷരം *);
            വേണ്ടി (j = 0, patom = (Atom *)data; j < length; j++, patom++) {
                അക്ഷരം *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            അക്ഷരം **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
            എങ്കിൽ (new_mime_types) {
                അക്ഷരം *strPtr = (അക്ഷരം *)(new_mime_types + length + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                വേണ്ടി (j = 0, patom = (Atom *)data; j < length; j++, patom++) {
                    അക്ഷരം *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    സ്ഥിരം size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[length] = ശൂന്യ;

                SDL_SendClipboardUpdate(false, new_mime_types, length);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            എങ്കിൽ (data) {
                X11_XFree(data);
            }
        }

        videodata->selection_waiting = false;
    } നിർത്തുക;

    അവസ്ഥ SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_ClipboardData *clipboard = ശൂന്യ;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.target);
#endif

        എങ്കിൽ (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } അല്ലെങ്കിൽ എങ്കിൽ (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        എങ്കിൽ (clipboard && clipboard->callback) {
            എങ്കിൽ (clipboard->sequence) {
                SDL_CancelClipboardData(clipboard->sequence);
            } അല്ലെങ്കിൽ {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } നിർത്തുക;

    അവസ്ഥ PropertyNotify:
    {
        അക്ഷരം *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        എങ്കിൽ (SDL_strncmp(name_of_atom, "SDL_SELECTION", വലുപ്പം("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_മൂല്യം) {
            videodata->selection_incr_waiting = false;
        }

        എങ്കിൽ (name_of_atom) {
            X11_XFree(name_of_atom);
        }
    } നിർത്തുക;
    }
}

സ്ഥിതം Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    തിരികെ ev->type == MapNotify &&
           ev->xmap.window == unmap->window &&
           ev->xmap.serial == unmap->serial;
}

സ്ഥിതം Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    തിരികെ ev->type == ReparentNotify &&
           ev->xreparent.window == unmap->window &&
           ev->xreparent.serial == unmap->serial;
}

സ്ഥിതം bool Is_മുകളിലെ_Latin1(സ്ഥിരം അക്ഷരം *string, പൂർണ്ണസംഖ്യ length)
{
    ആകുമ്പോൾ (length-- > 0) {
        Uint8 ch = (Uint8)*string;
        എങ്കിൽ (ch >= 0x80) {
            തിരികെ true;
        }
        ++string;
    }
    തിരികെ false;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ XLookupStringAsUTF8(XKeyEvent *event_struct, അക്ഷരം *buffer_return, പൂർണ്ണസംഖ്യ bytes_buffer, താക്കോൽ_Sym *keysym_return, XComposeStatus *status_in_out)
{
    പൂർണ്ണസംഖ്യ result = X11_XLookupString(event_struct, buffer_return, bytes_buffer, keysym_return, status_in_out);
    എങ്കിൽ (Is_മുകളിലെ_Latin1(buffer_return, result)) {
        അക്ഷരം *utf8_text = SDL_iconv_string("UTF-8", "ISO-8859-1", buffer_return, result + 1);
        എങ്കിൽ (utf8_text) {
            SDL_strlcpy(buffer_return, utf8_text, bytes_buffer);
            SDL_free(utf8_text);
            തിരികെ SDL_strlen(buffer_return);
        } അല്ലെങ്കിൽ {
            തിരികെ 0;
        }
    }
    തിരികെ result;
}

SDL_WindowData *X11_FindWindow(SDL_VideoData *videodata, Window window)
{
    എങ്കിൽ (videodata && videodata->windowlist) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < videodata->numwindows; ++i) {
            എങ്കിൽ ((videodata->windowlist[i] != ശൂന്യ) &&
                (videodata->windowlist[i]->xwindow == window)) {
                തിരികെ videodata->windowlist[i];
            }
        }
    }
    തിരികെ ശൂന്യ;
}

Uint64 X11_GetEventTimestamp(unsigned long time)
{
    // FIXME: Get the event time in the SDL tick time base
    തിരികെ SDL_GetTicksNS();
}

ശൂന്യം X11_Handle_താക്കോൽ_Event(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    താക്കോൽ_Code_2 keycode = xevent->xkey.keycode;
    താക്കോൽ_Sym keysym = No_ചിഹ്നം;
    പൂർണ്ണസംഖ്യ text_length = 0;
    അക്ഷരം text[64];
    Status status = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == താക്കോൽ_Press);
    SDL_Scancode scancode = videodata->keyboard.താക്കോൽ_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.window, (xevent->type == താക്കോൽ_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#endif
#ifdef DEBUG_SCANCODES
    എങ്കിൽ (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        പൂർണ്ണസംഖ്യ min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_താക്കോൽ_Code_To_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysymToString(keysym));
    }
#endif // DEBUG SCANCODES

    text[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    എങ്കിൽ (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (LockMask | videodata->keyboard.numlock_mask | videodata->keyboard.scrolllock_mask);
    }

    എങ്കിൽ (SDL_Text_നിവേശം_Active(windowdata->window)) {
        // filter events catches XIM events and sends them to the correct handler
        എങ്കിൽ (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            handled_by_ime = true;
        }

        എങ്കിൽ (!handled_by_ime) {
#ifdef X_HAVE_UTF8_STRING
            എങ്കിൽ (windowdata->ic && xevent->type == താക്കോൽ_Press) {
                text_length = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, text, വലുപ്പം(text) - 1,
                                      &keysym, &status);
            } അല്ലെങ്കിൽ {
                text_length = XLookupStringAsUTF8(&xevent->xkey, text, വലുപ്പം(text) - 1, &keysym, ശൂന്യ);
            }
#അല്ലെങ്കിൽ
            text_length = XLookupStringAsUTF8(&xevent->xkey, text, വലുപ്പം(text) - 1, &keysym, ശൂന്യ);
#endif
        }
    }

    എങ്കിൽ (!handled_by_ime) {
        എങ്കിൽ (pressed) {
            X11_Handle_Modifier_താക്കോലുകൾ(videodata, scancode, true);
            SDL_Send_Keyboard_താക്കോൽ_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            എങ്കിൽ (*text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                text[text_length] = '\0';
                X11_ClearComposition(windowdata);
                SDL_SendKeyboardText(text);
            }
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (X11_താക്കോൽ_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                തിരികെ;
            }

            X11_Handle_Modifier_താക്കോലുകൾ(videodata, scancode, false);
            SDL_Send_Keyboard_താക്കോൽ_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    എങ്കിൽ (pressed) {
        X11_UpdateUserTime(windowdata, xevent->xkey.time);
    }
}

ശൂന്യം X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, പൂർണ്ണസംഖ്യ button, ദശാംശം x, ദശാംശം y, unsigned long time, unsigned long serial)
{
    SDL_Window *window = windowdata->window;
    പൂർണ്ണസംഖ്യ xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#endif

    SDL_Mouse *mouse = SDL_GetMouse();
    എങ്കിൽ (!mouse->relative_mode && (x != mouse->x || y != mouse->y)) {
        X11_ProcessHitTest(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, window, mouseID, false, x, y);
    }

    എങ്കിൽ (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, window, mouseID, (ദശാംശം)-xticks, (ദശാംശം)yticks, SDL_MOUSEWHEEL_NORMAL);
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        എങ്കിൽ (button == Button1) {
            എങ്കിൽ (X11_TriggerHitTestAction(_this, windowdata, x, y)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0);
                തിരികെ; // don't pass this event on to app.
            }
        }
        എങ്കിൽ (windowdata->last_focus_event_time) {
            സ്ഥിരം പൂർണ്ണസംഖ്യ X11_FOCUS_CLICK_TIMEOUT = 10;
            എങ്കിൽ (SDL_GetTicks() < (windowdata->last_focus_event_time + X11_FOCUS_CLICK_TIMEOUT)) {
                എങ്കിൽ (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->last_focus_event_time = 0;
        }
        എങ്കിൽ (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, window, mouseID, button, true);
        }
    }
    X11_UpdateUserTime(windowdata, time);
}

ശൂന്യം X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, പൂർണ്ണസംഖ്യ button, unsigned long time)
{
    SDL_Window *window = windowdata->window;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    പൂർണ്ണസംഖ്യ xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#endif
    എങ്കിൽ (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        എങ്കിൽ (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, window, mouseID, button, false);

        എങ്കിൽ (window->internal->pending_grab) {
            X11_SetWindowMouseGrab(_this, window, true);
        }
    }
}

ശൂന്യം X11_Get_Border_മൂല്യങ്ങൾ(SDL_WindowData *data)
{
    SDL_VideoData *videodata = data->videodata;
    Display *display = videodata->display;

    Atom type;
    പൂർണ്ണസംഖ്യ format;
    unsigned long nitems, bytes_after;
    unsigned അക്ഷരം *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    എങ്കിൽ (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
        എങ്കിൽ (X11_XGetWindowProperty(display, data->xwindow, videodata->atoms._NET_FRAME_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &bytes_after, &property) == Success) {
            എങ്കിൽ (type != None && nitems == 4) {
                data->border_ഇടത് = (പൂർണ്ണസംഖ്യ)((long *)property)[0];
                data->border_വലത് = (പൂർണ്ണസംഖ്യ)((long *)property)[1];
                data->border_മുകൾ = (പൂർണ്ണസംഖ്യ)((long *)property)[2];
                data->border_bottom = (പൂർണ്ണസംഖ്യ)((long *)property)[3];
            }
            X11_XFree(property);

#ifdef DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", data->border_ഇടത്, data->border_വലത്, data->border_മുകൾ, data->border_bottom);
#endif
        }
    } അല്ലെങ്കിൽ {
        data->border_ഇടത് = data->border_മുകൾ = data->border_വലത് = data->border_bottom = 0;
    }
}

ശൂന്യം X11_EmitConfigureNotifyEvents(SDL_WindowData *data, XConfigureEvent *xevent)
{
    എങ്കിൽ (!data->size_move_event_flags) {
        പൂർണ്ണസംഖ്യ x = xevent->x;
        പൂർണ്ണസംഖ്യ y = xevent->y;

        എങ്കിൽ (xevent->x != data->last_xconfigure.x ||
            xevent->y != data->last_xconfigure.y) {
            data->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);

        വേണ്ടി (SDL_Window *w = data->window->first_child; w; w = w->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            എങ്കിൽ (SDL_WINDOW_IS_POPUP(w) && !(w->flags & SDL_WINDOW_HIDDEN)) {
                X11_UpdateWindowPosition(w, true);
            }
        }

        എങ്കിൽ (xevent->width != data->last_xconfigure.width ||
            xevent->height != data->last_xconfigure.height) {
            data->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, xevent->width, xevent->height);
    }

    SDL_copyp(&data->last_xconfigure, xevent);
}

സ്ഥിതം ശൂന്യം X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display;
    SDL_WindowData *data;
    XClientMessageEvent m;
    പൂർണ്ണസംഖ്യ i;

    SDL_assert(videodata != ശൂന്യ);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    എങ്കിൽ (xevent->type != താക്കോൽ_Press && xevent->type != താക്കോൽ_Release) {
        എങ്കിൽ (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            തിരികെ;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    എങ്കിൽ (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        തിരികെ;
    }
#endif

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    എങ്കിൽ (g_X11EventHook) {
        എങ്കിൽ (!g_X11EventHook(g_X11EventHookData, xevent)) {
            തിരികെ;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    എങ്കിൽ (videodata->xrandr_event_base && (xevent->type == (videodata->xrandr_event_base + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#endif

#ifdef DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.window);
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    എങ്കിൽ (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#endif

        എങ്കിൽ (ev->subtype == XFixesSetSelectionOwnerNotify)
        {
            എങ്കിൽ (ev->selection != videodata->atoms.CLIPBOARD)
                തിരികെ;

            എങ്കിൽ (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_window)
                തിരികെ;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, GetWindow(_this), CurrentTime);
        }

        തിരികെ;
    }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES

    എങ്കിൽ ((videodata->clipboard_window != None) &&
        (videodata->clipboard_window == xevent->xany.window)) {
        X11_HandleClipboardEvent(_this, xevent);
        തിരികെ;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    data = X11_FindWindow(videodata, xevent->xany.window);

    എങ്കിൽ (!data) {
        // The window for KeymapNotify, etc events is 0
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        എങ്കിൽ (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            തിരഞ്ഞെടുപ്പ് (xkbevent->any.xkb_type) {
            അവസ്ഥ XkbStateNotify:
            {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.window);
#endif
                എങ്കിൽ ((xkbevent->state.changed & XkbGroupStateMask) && xkbevent->state.group != videodata->keyboard.xkb.current_group) {
                    videodata->keyboard.xkb.current_group = xkbevent->state.group;
                    SDL_SetKeymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_group], true);
                }

                എങ്കിൽ (xkbevent->state.changed & XkbModifierStateMask) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.base_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } നിർത്തുക;

            അവസ്ഥ XkbMapNotify:
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.window);
                SDL_FALLTHROUGH;
#endif
            അവസ്ഥ XkbNewKeyboardNotify:
            {
#ifdef DEBUG_XEVENTS
                എങ്കിൽ (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.window);
                }
#endif
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                എങ്കിൽ (xkbevent->any.serial != videodata->keyboard.xkb.last_map_serial) {
                    videodata->keyboard.xkb.last_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } നിർത്തുക;

            സ്ഥിരസ്ഥിതി:
                നിർത്തുക;
            }
        } അല്ലെങ്കിൽ
#endif
        എങ്കിൽ (xevent->type == KeymapNotify) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.window);
#endif
            എങ്കിൽ (SDL_GetKeyboardFocus() != ശൂന്യ) {
                എങ്കിൽ (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (xevent->type == MappingNotify) {
            സ്ഥിരം പൂർണ്ണസംഖ്യ request = xevent->xmapping.request;

            എങ്കിൽ (request == MappingPointer) {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                X11_Xinput2UpdatePointerMapping(_this);
            } അല്ലെങ്കിൽ എങ്കിൽ (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                എങ്കിൽ (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (xevent->type == PropertyNotify && videodata) {
            അക്ഷരം *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            എങ്കിൽ (name_of_atom) {
                എങ്കിൽ (SDL_startswith(name_of_atom, "_ICC_PROFILE")) {
                    XWindowAttributes attrib;
                    പൂർണ്ണസംഖ്യ screennum;
                    വേണ്ടി (i = 0; i < videodata->numwindows; ++i) {
                        എങ്കിൽ (videodata->windowlist[i] != ശൂന്യ) {
                            data = videodata->windowlist[i];
                            X11_XGetWindowAttributes(display, data->xwindow, &attrib);
                            screennum = X11_XScreen_സംഖ്യ_Of_Screen(attrib.screen);
                            എങ്കിൽ (screennum == 0 && SDL_strcmp(name_of_atom, "_ICC_PROFILE") == 0) {
                                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                            } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strncmp(name_of_atom, "_ICC_PROFILE_", വലുപ്പം("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_of_atom) > വലുപ്പം("_ICC_PROFILE_") - 1) {
                                പൂർണ്ണസംഖ്യ iccscreennum = SDL_atoi(&name_of_atom[വലുപ്പം("_ICC_PROFILE_") - 1]);

                                എങ്കിൽ (screennum == iccscreennum) {
                                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                                }
                            }
                        }
                    }
                } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(name_of_atom, "_NET_WORKAREA") == 0) {
                    വേണ്ടി (i = 0; i < _this->അക്കം_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
                    }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
                } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(name_of_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_of_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#endif
                }
                X11_XFree(name_of_atom);
            }
        }
        തിരികെ;
    }

    തിരഞ്ഞെടുപ്പ് (xevent->type) {

        // Gaining mouse coverage?
    അവസ്ഥ EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        എങ്കിൽ (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        എങ്കിൽ (xevent->xcrossing.mode == NotifyUngrab) {
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
            എങ്കിൽ ((data->pointer_barrier_active == true) && windowdata->window->flags & SDL_WINDOW_നിവേശം_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->window, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#endif

        എങ്കിൽ (!mouse->relative_mode) {
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (ദശാംശം)xevent->xcrossing.x, (ദശാംശം)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        എങ്കിൽ (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            SDL_UpdateWindowGrab(data->window);
        }

        X11_ProcessHitTest(_this, data, mouse->last_x, mouse->last_y, true);
    } നിർത്തുക;
        // Losing mouse coverage?
    അവസ്ഥ LeaveNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        എങ്കിൽ (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        എങ്കിൽ (xevent->xcrossing.mode == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#endif
        എങ്കിൽ (!SDL_GetMouse()->relative_mode) {
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (ദശാംശം)xevent->xcrossing.x, (ദശാംശം)xevent->xcrossing.y);
        }

        എങ്കിൽ (xevent->xcrossing.mode != NotifyGrab &&
            xevent->xcrossing.mode != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            എങ്കിൽ (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                X11_SetWindowKeyboardGrab(_this, data->window, false);
            }

            SDL_SetMouseFocus(ശൂന്യ);
        }
    } നിർത്തുക;

        // Gaining input focus?
    അവസ്ഥ FocusIn:
    {
        എങ്കിൽ (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            നിർത്തുക;
        }

        എങ്കിൽ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            നിർത്തുക;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.window);
#endif
        എങ്കിൽ (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            data->pending_focus = PENDING_FOCUS_NONE;
            data->pending_focus_time = 0;
            X11_DispatchFocusIn(_this, data);
        } അല്ലെങ്കിൽ {
            data->pending_focus = PENDING_FOCUS_IN;
            data->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }
        data->last_focus_event_time = SDL_GetTicks();
    } നിർത്തുക;

        // Losing input focus?
    അവസ്ഥ FocusOut:
    {
        എങ്കിൽ (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            നിർത്തുക;
        }
        എങ്കിൽ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            നിർത്തുക;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.window);
#endif
        എങ്കിൽ (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            data->pending_focus = PENDING_FOCUS_NONE;
            data->pending_focus_time = 0;
            X11_DispatchFocusOut(_this, data);
        } അല്ലെങ്കിൽ {
            data->pending_focus = PENDING_FOCUS_OUT;
            data->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        എങ്കിൽ (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, ശൂന്യ, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } നിർത്തുക;


        // Have we been iconified?
    അവസ്ഥ UnmapNotify:
    {
        XEvent ev;

#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.window);
#endif

        എങ്കിൽ (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } അല്ലെങ്കിൽ {
            X11_DispatchUnmapNotify(data);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        എങ്കിൽ (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, ശൂന്യ, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } നിർത്തുക;

        // Have we been restored?
    അവസ്ഥ MapNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.window);
#endif
        X11_DispatchMapNotify(data);

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        എങ്കിൽ (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, &data->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } നിർത്തുക;

        // Have we been resized or moved?
    അവസ്ഥ ConfigureNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.window,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.width, xevent->xconfigure.height);
#endif
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        എങ്കിൽ (!xevent->xconfigure.send_event) {
            unsigned പൂർണ്ണസംഖ്യ അക്കം_Children;
            Window ChildReturn, വേര്_2, Parent;
            Window *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_last_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

            X11_XQuery_വൃക്ഷം(data->videodata->display, xevent->xconfigure.window, &വേര്_2, &Parent, &Children, &അക്കം_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      Parent, Default_വേര്_Window(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &ChildReturn);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            എങ്കിൽ (x11_last_error == BadWindow) {
                നിർത്തുക;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        സ്ഥിരം SDL_WindowFlags changed = X11_GetNetWMState(_this, data->window, xevent->xproperty.window) ^ data->window->flags;
        എങ്കിൽ (changed & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) {
            SDL_copyp(&data->pending_xconfigure, &xevent->xconfigure);
            data->emit_size_move_after_property_notify = true;
        }

        എങ്കിൽ (!data->emit_size_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(data, &xevent->xconfigure);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(data->window, &xevent->xconfigure);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } നിർത്തുക;

        // Have we been requested to quit (or another client message?)
    അവസ്ഥ ClientMessage:
    {
        സ്ഥിതം പൂർണ്ണസംഖ്യ xdnd_version = 0;

        എങ്കിൽ (xevent->xclient.message_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.data.l[1] & 1;
            data->xdnd_source = xevent->xclient.data.l[0];
            xdnd_version = (xevent->xclient.data.l[1] >> 24);
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", data->xdnd_source);
            SDL_Log("Protocol version to use : %d", xdnd_version);
            SDL_Log("More then 3 data types : %d", (പൂർണ്ണസംഖ്യ)use_list);
#endif

            എങ്കിൽ (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, data->xdnd_source, videodata->atoms.XdndTypeList);
                // pick one
                data->xdnd_req = X11_PickTarget(display, (Atom *)p.data, p.എണ്ണം);
                X11_XFree(p.data);
            } അല്ലെങ്കിൽ {
                // pick from list of three
                data->xdnd_req = X11_PickTargetFromAtoms(display, xevent->xclient.data.l[2], xevent->xclient.data.l[3], xevent->xclient.data.l[4]);
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (xevent->xclient.message_type == videodata->atoms.XdndLeave) {
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.data.l[0]);
#endif
            SDL_SendDropComplete(data->window);
        } അല്ലെങ്കിൽ എങ്കിൽ (xevent->xclient.message_type == videodata->atoms.XdndPosition) {

#ifdef DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            എങ്കിൽ (xdnd_version >= 2) {
                act = xevent->xclient.data.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#endif
            {
                // Drag and Drop position
                പൂർണ്ണസംഖ്യ വേര്_x, വേര്_y, window_x, window_y;
                Window ChildReturn;
                വേര്_x = xevent->xclient.data.l[2] >> 16;
                വേര്_y = xevent->xclient.data.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_വേര്_Window(display), data->xwindow,
                                          വേര്_x, വേര്_y, &window_x, &window_y, &ChildReturn);

                SDL_SendDropPosition(data->window, (ദശാംശം)window_x, (ദശാംശം)window_y);
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
        } അല്ലെങ്കിൽ എങ്കിൽ (xevent->xclient.message_type == videodata->atoms.XdndDrop) {
            എങ്കിൽ (data->xdnd_req == None) {
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
            } അല്ലെങ്കിൽ {
                // convert
                എങ്കിൽ (xdnd_version >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, data->xdnd_req, videodata->atoms.PRIMARY, data->xwindow, xevent->xclient.data.l[2]);
                } അല്ലെങ്കിൽ {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, data->xdnd_req, videodata->atoms.PRIMARY, data->xwindow, CurrentTime);
                }
            }
        } അല്ലെങ്കിൽ എങ്കിൽ ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.data.l[0] == videodata->atoms._NET_WM_PING)) {
            Window വേര് = Default_വേര്_Window(display);

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.window);
#endif
            xevent->xclient.window = വേര്;
            X11_XSendEvent(display, വേര്, False, SubstructureRedirectMask | SubstructureNotifyMask, xevent);
            നിർത്തുക;
        }

        അല്ലെങ്കിൽ എങ്കിൽ ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.data.l[0] == videodata->atoms.WM_DELETE_WINDOW)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.window);
#endif
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            നിർത്തുക;
        } അല്ലെങ്കിൽ എങ്കിൽ ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.data.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", data);
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(data->window, &xevent->xclient);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
            നിർത്തുക;
        }
    } നിർത്തുക;

        // Do we need to refresh ourselves?
    അവസ്ഥ Expose:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.window, xevent->xexpose.എണ്ണം);
#endif
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    } നിർത്തുക;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    അവസ്ഥ താക്കോൽ_Press:
    അവസ്ഥ താക്കോൽ_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        എങ്കിൽ (data->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            നിർത്തുക;
        } അല്ലെങ്കിൽ എങ്കിൽ (xevent->xkey.serial == videodata->xinput_last_താക്കോൽ_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_last_keyboard_device;
        }

        X11_Handle_താക്കോൽ_Event(_this, data, keyboardID, xevent);
    } നിർത്തുക;

    അവസ്ഥ MotionNotify:
    {
        എങ്കിൽ (X11_Xinput2HandlesMotionForWindow(data)) {
            // This input is being handled by XInput2
            നിർത്തുക;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        എങ്കിൽ (!mouse->relative_mode) {
#ifdef DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.window, xevent->xmotion.x, xevent->xmotion.y);
#endif

            X11_ProcessHitTest(_this, data, (ദശാംശം)xevent->xmotion.x, (ദശാംശം)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (ദശാംശം)xevent->xmotion.x, (ദശാംശം)xevent->xmotion.y);
        }
    } നിർത്തുക;

    അവസ്ഥ ButtonPress:
    {
        എങ്കിൽ (data->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            നിർത്തുക;
        }

        X11_HandleButtonPress(_this, data, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.time, xevent->xbutton.serial);
    } നിർത്തുക;

    അവസ്ഥ ButtonRelease:
    {
        എങ്കിൽ (data->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            നിർത്തുക;
        }

        X11_HandleButtonRelease(_this, data, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.time);
    } നിർത്തുക;

    അവസ്ഥ PropertyNotify:
    {
#ifdef DEBUG_XEVENTS
        unsigned അക്ഷരം *propdata;
        പൂർണ്ണസംഖ്യ status, real_format;
        Atom real_type;
        unsigned long ഇനങ്ങൾ_read, ഇനങ്ങൾ_ഇടത്;

        അക്ഷരം *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        എങ്കിൽ (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.window, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.time);
            X11_XFree(name);
        }

        status = X11_XGetWindowProperty(display, data->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &ഇനങ്ങൾ_read, &ഇനങ്ങൾ_ഇടത്, &propdata);
        എങ്കിൽ (status == Success && ഇനങ്ങൾ_read > 0) {
            എങ്കിൽ (real_type == XA_INTEGER) {
                പൂർണ്ണസംഖ്യ *മൂല്യങ്ങൾ = (പൂർണ്ണസംഖ്യ *)propdata;

                SDL_Log("{");
                വേണ്ടി (i = 0; i < ഇനങ്ങൾ_read; i++) {
                    SDL_Log(" %d", മൂല്യങ്ങൾ[i]);
                }
                SDL_Log(" }");
            } അല്ലെങ്കിൽ എങ്കിൽ (real_type == XA_CARDINAL) {
                എങ്കിൽ (real_format == 32) {
                    Uint32 *മൂല്യങ്ങൾ = (Uint32 *)propdata;

                    SDL_Log("{");
                    വേണ്ടി (i = 0; i < ഇനങ്ങൾ_read; i++) {
                        SDL_Log(" %d", മൂല്യങ്ങൾ[i]);
                    }
                    SDL_Log(" }");
                } അല്ലെങ്കിൽ എങ്കിൽ (real_format == 16) {
                    Uint16 *മൂല്യങ്ങൾ = (Uint16 *)propdata;

                    SDL_Log("{");
                    വേണ്ടി (i = 0; i < ഇനങ്ങൾ_read; i++) {
                        SDL_Log(" %d", മൂല്യങ്ങൾ[i]);
                    }
                    SDL_Log(" }");
                } അല്ലെങ്കിൽ എങ്കിൽ (real_format == 8) {
                    Uint8 *മൂല്യങ്ങൾ = (Uint8 *)propdata;

                    SDL_Log("{");
                    വേണ്ടി (i = 0; i < ഇനങ്ങൾ_read; i++) {
                        SDL_Log(" %d", മൂല്യങ്ങൾ[i]);
                    }
                    SDL_Log(" }");
                }
            } അല്ലെങ്കിൽ എങ്കിൽ (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } അല്ലെങ്കിൽ എങ്കിൽ (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                വേണ്ടി (i = 0; i < ഇനങ്ങൾ_read; i++) {
                    അക്ഷരം *atomname = X11_XGetAtomName(display, atoms[i]);
                    എങ്കിൽ (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } അല്ലെങ്കിൽ {
                അക്ഷരം *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                എങ്കിൽ (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        എങ്കിൽ (status == Success) {
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
        എങ്കിൽ (!data->user_time) {
            data->user_time = xevent->xproperty.time;
        }

        എങ്കിൽ (xevent->xproperty.atom == data->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            സ്ഥിരം SDL_WindowFlags flags = X11_GetNetWMState(_this, data->window, xevent->xproperty.window);
            സ്ഥിരം SDL_WindowFlags changed = flags ^ data->window->flags;

            എങ്കിൽ ((changed & SDL_WINDOW_HIDDEN) && !(flags & SDL_WINDOW_HIDDEN)) {
                X11_DispatchMapNotify(data);
            }

            എങ്കിൽ (!SDL_WINDOW_IS_POPUP(data->window)) {
                എങ്കിൽ (changed & SDL_WINDOW_FULLSCREEN) {
                    data->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    എങ്കിൽ (flags & SDL_WINDOW_FULLSCREEN) {
                        എങ്കിൽ (!(flags & SDL_WINDOW_MINIMIZED)) {
                            സ്ഥിരം bool commit = SDL_memcmp(&data->window->current_fullscreen_mode, &data->requested_fullscreen_mode, വലുപ്പം(SDL_DisplayMode)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                            എങ്കിൽ (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&data->window->current_fullscreen_mode, &data->window->requested_fullscreen_mode);
                                SDL_UpdateFullscreenMode(data->window, SDL_FULLSCREEN_OP_UPDATE, true);
                            } അല്ലെങ്കിൽ {
                                SDL_UpdateFullscreenMode(data->window, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } അല്ലെങ്കിൽ {
                        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                        SDL_UpdateFullscreenMode(data->window, false, false);

                        SDL_zero(data->requested_fullscreen_mode);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_SetWindowMinMax(data->window, !!(flags & SDL_WINDOW_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        എങ്കിൽ (data->fullscreen_borders_forced_on) {
                            data->toggle_borders = true;
                            data->fullscreen_borders_forced_on = false;
                        }
                    }

                    എങ്കിൽ ((flags & SDL_WINDOW_FULLSCREEN) &&
                        (data->border_മുകൾ || data->border_ഇടത് || data->border_bottom || data->border_വലത്)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        data->size_move_event_flags |= X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        data->previous_borders_nonzero = true;
                    } അല്ലെങ്കിൽ എങ്കിൽ (!(flags & SDL_WINDOW_FULLSCREEN) &&
                               data->previous_borders_nonzero &&
                               (!data->border_മുകൾ && !data->border_ഇടത് && !data->border_bottom && !data->border_വലത്)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        data->size_move_event_flags |= X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        data->previous_borders_nonzero = false;
                    } അല്ലെങ്കിൽ {
                        data->size_move_event_flags = 0;
                        data->previous_borders_nonzero = false;

                        എങ്കിൽ (!(data->window->flags & SDL_WINDOW_FULLSCREEN) && data->toggle_borders) {
                            data->toggle_borders = false;
                            X11_SetWindowBordered(_this, data->window, !(data->window->flags & SDL_WINDOW_BORDERLESS));
                        }
                    }
                }
                എങ്കിൽ ((changed & SDL_WINDOW_MAXIMIZED) && ((flags & SDL_WINDOW_MAXIMIZED) && !(flags & SDL_WINDOW_MINIMIZED))) {
                    data->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    എങ്കിൽ ((changed & SDL_WINDOW_MINIMIZED)) {
                        data->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                    }
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
                }
                എങ്കിൽ ((changed & SDL_WINDOW_MINIMIZED) && (flags & SDL_WINDOW_MINIMIZED)) {
                    data->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                }
                എങ്കിൽ (!(flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
                    data->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    എങ്കിൽ (!(flags & SDL_WINDOW_FULLSCREEN)) {
                        എങ്കിൽ (data->pending_position) {
                            data->pending_position = false;
                            data->pending_operation |= X11_PENDING_OP_MOVE;
                            data->expected.x = data->window->pending.x - data->border_ഇടത്;
                            data->expected.y = data->window->pending.y - data->border_മുകൾ;
                            X11_XMoveWindow(display, data->xwindow, data->expected.x, data->expected.y);
                        }
                        എങ്കിൽ (data->pending_size) {
                            data->pending_size = false;
                            data->pending_operation |= X11_PENDING_OP_RESIZE;
                            data->expected.w = data->window->pending.w;
                            data->expected.h = data->window->pending.h;
                            X11_XResizeWindow(display, data->xwindow, data->window->pending.w, data->window->pending.h);
                        }
                    }
                }
                എങ്കിൽ (data->emit_size_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(data, &data->pending_xconfigure);
                    data->emit_size_move_after_property_notify = false;
                }
                എങ്കിൽ ((flags & SDL_WINDOW_നിവേശം_FOCUS)) {
                    എങ്കിൽ (data->pending_move) {
                        DispatchWindowMove(_this, data, &data->pending_move_point);
                        data->pending_move = false;
                    }
                }
            }
            എങ്കിൽ (changed & SDL_WINDOW_OCCLUDED) {
                SDL_SendWindowEvent(data->window, (flags & SDL_WINDOW_OCCLUDED) ? SDL_EVENT_WINDOW_OCCLUDED : SDL_EVENT_WINDOW_EXPOSED, 0, 0);
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            പൂർണ്ണസംഖ്യ format;
            unsigned long nitems, bytes_after;
            unsigned അക്ഷരം *prop_data = ശൂന്യ;

            എങ്കിൽ (X11_XGetWindowProperty(display, data->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &bytes_after, &prop_data) == Success) {
                എങ്കിൽ (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_data;

                    എങ്കിൽ ((state == 0 || state == 3) && !data->window->is_hiding && !(data->window->flags & SDL_WINDOW_HIDDEN)) {
                        // Withdrawn or Iconic
                        എങ്കിൽ (!(data->window->flags & SDL_WINDOW_MINIMIZED)) {
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
                        }
                    } അല്ലെങ്കിൽ എങ്കിൽ (state == 1) { // NormalState
                        എങ്കിൽ (data->window->flags & SDL_WINDOW_MINIMIZED) {
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_data);
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } അല്ലെങ്കിൽ എങ്കിൽ (xevent->xproperty.atom == videodata->atoms._NET_FRAME_EXTENTS) {
            X11_Get_Border_മൂല്യങ്ങൾ(data);
            എങ്കിൽ (data->size_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                data->size_move_event_flags &= ~X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            എങ്കിൽ (!(data->window->flags & SDL_WINDOW_FULLSCREEN) && data->toggle_borders) {
                data->toggle_borders = false;
                X11_SetWindowBordered(_this, data->window, !(data->window->flags & SDL_WINDOW_BORDERLESS));
            }
        }
    } നിർത്തുക;

    അവസ്ഥ SelectionNotify:
    {
        Atom target = xevent->xselection.target;
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.window,
               xevent->xselection.requestor, xevent->xselection.target);
#endif
        എങ്കിൽ (target == data->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, data->xwindow, videodata->atoms.PRIMARY);

            എങ്കിൽ (p.format == 8) {
                അക്ഷരം *saveptr = ശൂന്യ;
                അക്ഷരം *name = X11_XGetAtomName(display, target);
                എങ്കിൽ (name) {
                    അക്ഷരം *token = SDL_strtok_r((അക്ഷരം *)p.data, "\r\n", &saveptr);
                    ആകുമ്പോൾ (token) {
                        എങ്കിൽ ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_SendDropText(data->window, token);
                        } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp("text/uri-list", name) == 0) {
                            എങ്കിൽ (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(data->window, ശൂന്യ, token);
                            }
                        }
                        token = SDL_strtok_r(ശൂന്യ, "\r\n", &saveptr);
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
    } നിർത്തുക;

    സ്ഥിരസ്ഥിതി:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.window, xevent->type);
#endif
    } നിർത്തുക;
    }
}

സ്ഥിതം ശൂന്യം X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    പൂർണ്ണസംഖ്യ i;

    എങ്കിൽ (videodata && videodata->windowlist) {
        വേണ്ടി (i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *data = videodata->windowlist[i];
            എങ്കിൽ (data && data->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                എങ്കിൽ (now >= data->pending_focus_time) {
                    എങ്കിൽ (data->pending_focus == PENDING_FOCUS_IN) {
                        X11_DispatchFocusIn(_this, data);
                    } അല്ലെങ്കിൽ {
                        X11_DispatchFocusOut(_this, data);
                    }
                    data->pending_focus = PENDING_FOCUS_NONE;
                }
            }
        }
    }
}

സ്ഥിതം Bool isAnyEvent(Display *display, XEvent *ev, XPointer arg)
{
    തിരികെ True;
}

സ്ഥിതം bool X11_PollEvent(Display *display, XEvent *event)
{
    എങ്കിൽ (!X11_XCheckIfEvent(display, event, isAnyEvent, ശൂന്യ)) {
        തിരികെ false;
    }

    തിരികെ true;
}

ശൂന്യം X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
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

പൂർണ്ണസംഖ്യ X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    എങ്കിൽ (X11_PollEvent(display, &xevent)) {
        // Fall through
    } അല്ലെങ്കിൽ എങ്കിൽ (timeoutNS == 0) {
        തിരികെ 0;
    } അല്ലെങ്കിൽ {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        പൂർണ്ണസംഖ്യ err = SDL_IOReady(Connection_സംഖ്യ(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        എങ്കിൽ (err > 0) {
            എങ്കിൽ (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                തിരികെ 1;
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (err == 0) {
            // Timeout
            തിരികെ 0;
        } അല്ലെങ്കിൽ {
            // Error returned from poll()/select()

            എങ്കിൽ (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                തിരികെ 1;
            } അല്ലെങ്കിൽ {
                തിരികെ err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    തിരികെ 1;
}

ശൂന്യം X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    XEvent xevent;
    പൂർണ്ണസംഖ്യ i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    വേണ്ടി (i = 0; i < _this->അക്കം_displays; ++i) {
        എങ്കിൽ (_this->displays[i]->internal->mode_switch_deadline_ns) {
            എങ്കിൽ (_this->displays[i]->fullscreen_window) {
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            } അല്ലെങ്കിൽ എങ്കിൽ (SDL_GetTicksNS() >= _this->displays[i]->internal->mode_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_SetDisplayModeForDisplay(_this->displays[i], ശൂന്യ);
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            }
        }
    }

    എങ്കിൽ (data->last_mode_change_deadline) {
        എങ്കിൽ (SDL_GetTicks() >= data->last_mode_change_deadline) {
            data->last_mode_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    എങ്കിൽ (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        എങ്കിൽ (!data->screensaver_activity || now >= (data->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(data->display);

#ifdef SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#endif

            data->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    ആകുമ്പോൾ (X11_PollEvent(data->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    വേണ്ടി (i = 0; i < data->numwindows; ++i) {
        എങ്കിൽ (data->windowlist[i] != ശൂന്യ &&
            data->windowlist[i]->flash_cancel_time &&
            SDL_GetTicks() >= data->windowlist[i]->flash_cancel_time) {
            X11_FlashWindow(_this, data->windowlist[i]->window, SDL_FLASH_CANCEL);
        }
    }

    എങ്കിൽ (data->xinput_hierarchy_changed) {
        X11_Xinput2UpdateDevices(_this);
        data->xinput_hierarchy_changed = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_VideoData *data = _this->internal;
    പൂർണ്ണസംഖ്യ dummy;
    പൂർണ്ണസംഖ്യ major_version, minor_version;
#endif // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#ifdef SDL_USE_LIBDBUS
    എങ്കിൽ (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        തിരികെ true;
    }

    എങ്കിൽ (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    എങ്കിൽ (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        എങ്കിൽ (!X11_XScreenSaverQueryExtension(data->display, &dummy, &dummy) ||
            !X11_XScreenSaverQueryVersion(data->display,
                                          &major_version, &minor_version) ||
            major_version < 1 || (major_version == 1 && minor_version < 1)) {
            തിരികെ SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(data->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(data->display);
        തിരികെ true;
    }
#endif
    തിരികെ SDL_Unsupported();
}

#endif // SDL_VIDEO_DRIVER_X11
