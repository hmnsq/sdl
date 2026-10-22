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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#અન્તર્ભાવ <sys/types.h>
#અન્તર્ભાવ <sys/time.h>
#અન્તર્ભાવ <signal.h>
#અન્તર્ભાવ <unistd.h>
#અન્તર્ભાવ <limits.h> // For INT_MAX

#અન્તર્ભાવ "SDL_x11video.h"
#અન્તર્ભાવ "SDL_x11pen.h"
#અન્તર્ભાવ "SDL_x11touch.h"
#અન્તર્ભાવ "SDL_x11xinput2.h"
#અન્તર્ભાવ "SDL_x11xfixes.h"
#અન્તર્ભાવ "SDL_x11settings.h"
#અન્તર્ભાવ "../SDL_clipboard_c.h"
#અન્તર્ભાવ "SDL_x11xsync.h"
#અન્તર્ભાવ "../../core/unix/SDL_poll.h"
#અન્તર્ભાવ "../../events/SDL_events_c.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"
#અન્તર્ભાવ "../../events/SDL_touch_c.h"
#અન્તર્ભાવ "../../core/linux/SDL_system_theme.h"
#અન્તર્ભાવ "../SDL_sysvideo.h"

#અન્તર્ભાવ <stdio.h>

#જો 0
#define DEBUG_XEVENTS
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPLEFT
#define _NET_WM_MOVERESIZE_SIZE_TOPLEFT 0
#endif

#ifndef NET_WM_MOVERESIZE_SIZE_ટોચ
#define NET_WM_MOVERESIZE_SIZE_ટોચ 1
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPRIGHT
#define _NET_WM_MOVERESIZE_SIZE_TOPRIGHT 2
#endif

#ifndef NET_WM_MOVERESIZE_SIZE_જમણું
#define NET_WM_MOVERESIZE_SIZE_જમણું 3
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

#ifndef NET_WM_MOVERESIZE_SIZE_ડાબું
#define NET_WM_MOVERESIZE_SIZE_ડાબું 7
#endif

#ifndef _NET_WM_MOVERESIZE_MOVE
#define _NET_WM_MOVERESIZE_MOVE 8
#endif

પ્રકારવ્યાખ્યા સંરચના
{
    unsigned અક્ષર *data;
    પૂર્ણાંક format, ગણતરી;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
સ્થિર શૂન્ય X11_ReadProperty(SDL_x11Prop *p, Display *disp, Window w, Atom prop)
{
    unsigned અક્ષર *ret = ખાલી;
    Atom type;
    પૂર્ણાંક fmt;
    unsigned long ગણતરી;
    unsigned long bytes_ડાબું;
    પૂર્ણાંક bytes_fetch = 0;

    કરો {
        જો (ret) {
            X11_XFree(ret);
        }
        X11_XGetWindowProperty(disp, w, prop, 0, bytes_fetch, False, AnyPropertyType, &type, &fmt, &ગણતરી, &bytes_ડાબું, &ret);
        bytes_fetch += bytes_ડાબું;
    } જ્યારે (bytes_ડાબું != 0);

    p->data = ret;
    p->format = fmt;
    p->ગણતરી = ગણતરી;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
સ્થિર Atom X11_PickTarget(Display *disp, Atom list[], પૂર્ણાંક list_ગણતરી)
{
    અચલ Atom text_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    માટે (પૂર્ણાંક i = 0; i < list_ગણતરી && request != text_uri_request; i++) {
        અક્ષર *name = X11_XGetAtomName(disp, list[i]);
        // Preferred MIME targets
        જો ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            જો (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        જો ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            જો (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    જો (preferred != None && request != text_uri_request) {
        request = preferred;
    }
    પાછા request;
}

/* Wrapper for X11_PickTarget for a maximum of three targets, a special
   case in the Xdnd protocol */
સ્થિર Atom X11_PickTargetFromAtoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    પૂર્ણાંક ગણતરી = 0;
    Atom atom[3];
    જો (a0 != None) {
        atom[ગણતરી++] = a0;
    }
    જો (a1 != None) {
        atom[ગણતરી++] = a1;
    }
    જો (a2 != None) {
        atom[ગણતરી++] = a2;
    }
    પાછા X11_PickTarget(disp, atom, ગણતરી);
}

સંરચના ચાવી_Repeat_Check_Data
{
    XEvent *event;
    bool found;
};

સ્થિર Bool X11_ચાવી_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    સંરચના ચાવી_Repeat_Check_Data *d = (સંરચના ચાવી_Repeat_Check_Data *)arg;
    જો (chkev->type == ચાવી_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.time - d->event->xkey.time < 2) {
        d->found = true;
    }
    પાછા False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
સ્થિર bool X11_ચાવી_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    સંરચના ચાવી_Repeat_Check_Data d;
    d.event = event;
    d.found = false;
    જો (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_ચાવી_Repeat_Check_If_Event, (XPointer)&d);
    }
    પાછા d.found;
}

bool X11_IsWheelEvent(પૂર્ણાંક button, પૂર્ણાંક *xticks, પૂર્ણાંક *yticks)
{
    /* according to the xlib docs, no specific mouse wheel events exist.
       However, the defacto standard is that the vertical wheel is X buttons
       4 (up) and 5 (down) and a horizontal wheel is 6 (left) and 7 (right). */

    // Xlib defines "Button1" through 5, so we just use literals here.
    પસંદગી (button) {
    સ્થિતિ 4:
        *yticks = 1;
        પાછા true;
    સ્થિતિ 5:
        *yticks = -1;
        પાછા true;
    સ્થિતિ 6:
        *xticks = 1;
        પાછા true;
    સ્થિતિ 7:
        *xticks = -1;
        પાછા true;
    મૂળભૂત:
        તોડો;
    }
    પાછા false;
}

// An X11 event hook
સ્થિર SDL_X11EventHook g_X11EventHook = ખાલી;
સ્થિર શૂન્ય *g_X11EventHookData = ખાલી;

શૂન્ય SDL_SetX11EventHook(SDL_X11EventHook callback, શૂન્ય *userdata)
{
    g_X11EventHook = callback;
    g_X11EventHookData = userdata;
}

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
સ્થિર શૂન્ય X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_VideoData *videodata = _this->internal;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    જો (X11_XGetEventData(videodata->display, cookie)) {
        જો (!g_X11EventHook || g_X11EventHook(g_X11EventHookData, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFreeEventData(videodata->display, cookie);
    }
}
#endif // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

સ્થિર શૂન્ય X11_Update_System_ચાવી_Modifiers(SDL_VideoData *viddata)
{
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    જો (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        જો (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.base_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } નહીંતર
#endif
        {
        Window junk_window;
        પૂર્ણાંક x, y;
        unsigned પૂર્ણાંક mod_mask;

        X11_XQueryPointer(viddata->display, Default_મૂળ_Window(viddata->display), &junk_window, &junk_window, &x, &y, &x, &y, &mod_mask);
        viddata->keyboard.pressed_modifiers = mod_mask & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        viddata->keyboard.locked_modifiers = mod_mask & (LockMask | viddata->keyboard.numlock_mask | viddata->keyboard.scrolllock_mask);
    }
}

સ્થિર શૂન્ય X11_ReconcileModifiers(SDL_VideoData *viddata, bool ચાવી_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    જો (ચાવી_pressed) {
        જો (viddata->keyboard.pressed_modifiers & ShiftMask) {
            જો (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT);
            }
        }

        જો (viddata->keyboard.pressed_modifiers & ControlMask) {
            જો (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        જો (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            જો (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        જો (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            જો (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } નહીંતર {
        જો (viddata->keyboard.pressed_modifiers & ShiftMask) {
            જો (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } નહીંતર {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        જો (viddata->keyboard.pressed_modifiers & ControlMask) {
            જો (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } નહીંતર {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        જો (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            જો (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } નહીંતર {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        જો (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            જો (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } નહીંતર {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        જો (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_mask) {
            જો (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_MODE)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_MODE;
            }
        } નહીંતર {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        જો (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_mask) {
            જો (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } નહીંતર {
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
    જો (viddata->keyboard.locked_modifiers & ShiftMask) {
        જો (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT);
        } નહીંતર જો (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_SHIFT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } નહીંતર {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    જો (viddata->keyboard.locked_modifiers & ControlMask) {
        જો (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } નહીંતર જો (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } નહીંતર {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    જો (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_mask) {
        જો (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } નહીંતર જો (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } નહીંતર {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    જો (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_mask) {
        જો (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } નહીંતર જો (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } નહીંતર {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    જો (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_MODE;
    } નહીંતર {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_MODE;
    }

    જો (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } નહીંતર {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    જો (viddata->keyboard.locked_modifiers & LockMask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } નહીંતર {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    જો (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_અંક;
    } નહીંતર {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_અંક;
    }

    જો (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } નહીંતર {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_SetModState(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

સ્થિર શૂન્ય X11_Handle_Modifier_ચાવીઓ(SDL_VideoData *viddata, SDL_Scancode scancode, bool pressed)
{
    અચલ SDL_Keycode keycode = SDL_Get_ચાવી_From_Scancode(scancode, SDL_KMOD_NONE, false);
    SDL_Keymod mod = SDL_KMOD_NONE;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is checked.
     */
    પસંદગી (keycode) {
    સ્થિતિ SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        તોડો;
    સ્થિતિ SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        તોડો;
    સ્થિતિ SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        તોડો;
    સ્થિતિ SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        તોડો;
    સ્થિતિ SDLK_LALT:
        mod = SDL_KMOD_LALT;
        તોડો;
    સ્થિતિ SDLK_RALT:
        mod = SDL_KMOD_RALT;
        તોડો;
    સ્થિતિ SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        તોડો;
    સ્થિતિ SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        તોડો;
    સ્થિતિ SDLK_MODE:
        mod = SDL_KMOD_MODE;
        તોડો;
    સ્થિતિ SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        તોડો;
    સ્થિતિ SDLK_CAPSLOCK:
    સ્થિતિ SDLK_NUMLOCKCLEAR:
    સ્થિતિ SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        જો (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            unsigned પૂર્ણાંક cur_mask = viddata->keyboard.locked_modifiers;
            X11_Update_System_ચાવી_Modifiers(viddata);

            જો (viddata->keyboard.locked_modifiers & LockMask) {
                cur_mask |= LockMask;
            } નહીંતર {
                cur_mask &= ~LockMask;
            }
            જો (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
                cur_mask |= viddata->keyboard.numlock_mask;
            } નહીંતર {
                cur_mask &= ~viddata->keyboard.numlock_mask;
            }
            જો (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
                cur_mask |= viddata->keyboard.scrolllock_mask;
            } નહીંતર {
                cur_mask &= ~viddata->keyboard.scrolllock_mask;
            }

            viddata->keyboard.locked_modifiers = cur_mask;
        }
    } તોડો;
    મૂળભૂત:
        પાછા;
    }

    જો (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } નહીંતર {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

શૂન્ય X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    અક્ષર ચાવીઓ[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_ચાવી_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_અંક | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= LockMask | videodata->keyboard.numlock_mask| videodata->keyboard.scrolllock_mask;

    X11_XQueryKeymap(display, ચાવીઓ);

    અચલ bool *keystate = SDL_GetKeyboardState(ખાલી);
    માટે (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.ચાવી_layout); ++keycode) {
        અચલ SDL_Scancode scancode = videodata->keyboard.ચાવી_layout[keycode];
        અચલ bool x11_ચાવી_Pressed = (ચાવીઓ[keycode / 8] & (1 << (keycode % 8))) != 0;
        અચલ bool sdl_ચાવી_Pressed = keystate[scancode];

        જો (x11_ચાવી_Pressed && !sdl_ચાવી_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            પસંદગી (SDL_Get_ચાવી_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            સ્થિતિ SDLK_LCTRL:
            સ્થિતિ SDLK_RCTRL:
            સ્થિતિ SDLK_LSHIFT:
            સ્થિતિ SDLK_RSHIFT:
            સ્થિતિ SDLK_LALT:
            સ્થિતિ SDLK_RALT:
            સ્થિતિ SDLK_LGUI:
            સ્થિતિ SDLK_RGUI:
            સ્થિતિ SDLK_MODE:
            સ્થિતિ SDLK_LEVEL5_SHIFT:
                X11_Handle_Modifier_ચાવીઓ(videodata, scancode, true);
                SDL_Send_Keyboard_ચાવી_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                તોડો;
            મૂળભૂત:
                તોડો;
            }
        } નહીંતર જો (!x11_ચાવી_Pressed && sdl_ચાવી_Pressed) {
            X11_Handle_Modifier_ચાવીઓ(videodata, scancode, false);
            SDL_Send_Keyboard_ચાવી_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_ચાવી_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

સ્થિર શૂન્ય X11_DispatchFocusIn(SDL_VideoDevice *_this, SDL_WindowData *data)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", data->xwindow);
#endif
    SDL_SetKeyboardFocus(data->window);
    X11_ReconcileKeyboardState(_this);
#ifdef X_HAVE_UTF8_STRING
    જો (data->ic) {
        X11_XSetICFocus(data->ic);
    }
#endif
    જો (data->flashing_window) {
        X11_FlashWindow(_this, data->window, SDL_FLASH_CANCEL);
    }
}

સ્થિર શૂન્ય X11_DispatchFocusOut(SDL_VideoDevice *_this, SDL_WindowData *data)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", data->xwindow);
#endif
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    જો (data->window == SDL_GetKeyboardFocus()) {
        SDL_SetKeyboardFocus(ખાલી);
    }
#ifdef X_HAVE_UTF8_STRING
    જો (data->ic) {
        X11_XUnsetICFocus(data->ic);
    }
#endif
}

સ્થિર શૂન્ય X11_DispatchMapNotify(SDL_WindowData *data)
{
    SDL_Window *window = data->window;

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    data->was_shown = true;

    // This may be sent when restoring a minimized window.
    જો (window->flags & SDL_WINDOW_MINIMIZED) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }

    જો (window->flags & SDL_WINDOW_આગત_FOCUS) {
        SDL_UpdateWindowGrab(window);
    }
}

સ્થિર શૂન્ય X11_DispatchUnmapNotify(SDL_WindowData *data)
{
    SDL_Window *window = data->window;

    // This may be sent when minimizing a window.
    જો (!window->is_hiding) {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
    } નહીંતર {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    }
}

સ્થિર શૂન્ય DispatchWindowMove(SDL_VideoDevice *_this, અચલ SDL_WindowData *data, અચલ SDL_Point *point)
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
    X11_XSendEvent(display, Default_મૂળ_Window(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

સ્થિર શૂન્ય ScheduleWindowMove(SDL_VideoDevice *_this, SDL_WindowData *data, અચલ SDL_Point *point)
{
    data->pending_move = true;
    data->pending_move_point = *point;
}

સ્થિર શૂન્ય InitiateWindowResize(SDL_VideoDevice *_this, અચલ SDL_WindowData *data, અચલ SDL_Point *point, પૂર્ણાંક direction)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_Window *window = data->window;
    Display *display = videodata->display;
    XEvent evt;

    જો (direction < _NET_WM_MOVERESIZE_SIZE_TOPLEFT || direction > NET_WM_MOVERESIZE_SIZE_ડાબું) {
        પાછા;
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
    X11_XSendEvent(display, Default_મૂળ_Window(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_WindowData *data, અચલ દશાંશ x, અચલ દશાંશ y, bool force_new_result)
{
    SDL_Window *window = data->window;
    જો (!window->hit_test) પાછા false;
    અચલ SDL_Point point = { (પૂર્ણાંક)x, (પૂર્ણાંક)y };
    SDL_HitTestResult rc = window->hit_test(window, &point, window->hit_test_data);
    જો (!force_new_result && rc == data->hit_test_result) {
        પાછા true;
    }
    X11_SetHitTestCursor(rc);
    data->hit_test_result = rc;
    પાછા true;
}

bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_WindowData *data, અચલ દશાંશ x, અચલ દશાંશ y)
{
    SDL_Window *window = data->window;

    જો (window->hit_test) {
        અચલ SDL_Point point = { (પૂર્ણાંક)x, (પૂર્ણાંક)y };
        સ્થિર અચલ પૂર્ણાંક directions[] = {
            _NET_WM_MOVERESIZE_SIZE_TOPLEFT, NET_WM_MOVERESIZE_SIZE_ટોચ,
            _NET_WM_MOVERESIZE_SIZE_TOPRIGHT, NET_WM_MOVERESIZE_SIZE_જમણું,
            _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT, _NET_WM_MOVERESIZE_SIZE_BOTTOM,
            _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT, NET_WM_MOVERESIZE_SIZE_ડાબું
        };

        પસંદગી (data->hit_test_result) {
        સ્થિતિ SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            જો (data->window->flags & SDL_WINDOW_આગત_FOCUS) {
                DispatchWindowMove(_this, data, &point);
            } નહીંતર {
                ScheduleWindowMove(_this, data, &point);
            }
            પાછા true;

        સ્થિતિ SDL_HITTEST_RESIZE_TOPLEFT:
        સ્થિતિ SDL_HITTEST_RESIZE_ટોચ:
        સ્થિતિ SDL_HITTEST_RESIZE_TOPRIGHT:
        સ્થિતિ SDL_HITTEST_RESIZE_જમણું:
        સ્થિતિ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        સ્થિતિ SDL_HITTEST_RESIZE_BOTTOM:
        સ્થિતિ SDL_HITTEST_RESIZE_BOTTOMLEFT:
        સ્થિતિ SDL_HITTEST_RESIZE_ડાબું:
            InitiateWindowResize(_this, data, &point, directions[data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
            પાછા true;

        મૂળભૂત:
            પાછા false;
        }
    }

    પાછા false;
}

સ્થિર શૂન્ય X11_UpdateUserTime(SDL_WindowData *data, અચલ unsigned long latest)
{
    જો (latest && (latest != data->user_time)) {
        SDL_VideoData *videodata = data->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, data->xwindow, videodata->atoms._NET_WM_USER_TIME,
                            XA_CARDINAL, 32, PropModeReplace,
                            (અચલ unsigned અક્ષર *)&latest, 1);
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", data->xwindow, latest);
#endif
        data->user_time = latest;
    }
}

સ્થિર unsigned અક્ષર x11_last_error;
સ્થિર પૂર્ણાંક BadWindowErrorHandler(Display *d, XErrorEvent *e)
{
    x11_last_error = e->error_code;

    // Ignore BadWindow in cases where it's not fatal.
    જો (e->error_code != BadWindow) {
        અક્ષર err_સંદેશ[128];
        X11_XGetErrorText(d, e->error_code, err_સંદેશ, કદ(err_સંદેશ));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_code, err_સંદેશ, e->request_code);
    }
    પાછા 0;
}

સ્થિર શૂન્ય X11_HandleClipboardEvent(SDL_VideoDevice *_this, અચલ XEvent *xevent)
{
    પૂર્ણાંક i;
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_window != None);
    SDL_assert(xevent->xany.window == videodata->clipboard_window);

    પસંદગી (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    સ્થિતિ SelectionRequest:
    {
        અચલ XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        પૂર્ણાંક mime_formats;
        unsigned અક્ષર *seln_data;
        size_t seln_length = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_ClipboardData *clipboard;

#ifdef DEBUG_XEVENTS
        અક્ષર *atom_name;
        atom_name = X11_XGetAtomName(display, req->target);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->target, atom_name);
        જો (atom_name) {
            X11_XFree(atom_name);
        }
#endif

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_last_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

        જો (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } નહીંતર {
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

        જો (req->target == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_ગણતરી + 1) * કદ(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            માટે (i = 0; i < clipboard->mime_ગણતરી; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, PropModeReplace,
                                (unsigned અક્ષર *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.target = XA_TARGETS;
            SDL_free(supportedFormats);
        } નહીંતર {
            જો (clipboard->callback) {
                માટે (i = 0; i < clipboard->mime_ગણતરી; ++i) {
                    અચલ અક્ષર *mime_type = clipboard->mime_types[i];
                    જો (X11_XInternAtom(display, mime_type, False) != req->target) {
                        ચાલુ;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_data = (unsigned અક્ષર *)clipboard->callback(clipboard->userdata, mime_type, &seln_length);
                    જો (seln_data) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->target, 8, PropModeReplace,
                                            seln_data, seln_length);
                        sevent.xselection.property = req->property;
                        sevent.xselection.target = req->target;
                    }
                    તોડો;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(prev_handler);
    } તોડો;

    સ્થિતિ SelectionNotify:
    {
        અચલ XSelectionEvent *xsel = &xevent->xselection;
#ifdef DEBUG_XEVENTS
        અચલ અક્ષર *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        અચલ અક્ષર *targetName = xsel->target ? X11_XGetAtomName(display, xsel->target) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, targetName, propName);
#endif
        જો (xsel->target == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            unsigned અક્ષર *data = ખાલી;
            પૂર્ણાંક format_property = 0;
            unsigned long length = 0;
            unsigned long bytes_ડાબું = 0;
            પૂર્ણાંક j;

            X11_XGetWindowProperty(display, GetWindow(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &length, &bytes_ડાબું, &data);

            પૂર્ણાંક allocationsize = (length + 1) * કદ(અક્ષર *);
            માટે (j = 0, patom = (Atom *)data; j < length; j++, patom++) {
                અક્ષર *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            અક્ષર **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
            જો (new_mime_types) {
                અક્ષર *strPtr = (અક્ષર *)(new_mime_types + length + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                માટે (j = 0, patom = (Atom *)data; j < length; j++, patom++) {
                    અક્ષર *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    અચલ size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[length] = ખાલી;

                SDL_SendClipboardUpdate(false, new_mime_types, length);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            જો (data) {
                X11_XFree(data);
            }
        }

        videodata->selection_waiting = false;
    } તોડો;

    સ્થિતિ SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_ClipboardData *clipboard = ખાલી;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.target);
#endif

        જો (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } નહીંતર જો (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        જો (clipboard && clipboard->callback) {
            જો (clipboard->sequence) {
                SDL_CancelClipboardData(clipboard->sequence);
            } નહીંતર {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } તોડો;

    સ્થિતિ PropertyNotify:
    {
        અક્ષર *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        જો (SDL_strncmp(name_of_atom, "SDL_SELECTION", કદ("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_કિંમત) {
            videodata->selection_incr_waiting = false;
        }

        જો (name_of_atom) {
            X11_XFree(name_of_atom);
        }
    } તોડો;
    }
}

સ્થિર Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    પાછા ev->type == MapNotify &&
           ev->xmap.window == unmap->window &&
           ev->xmap.serial == unmap->serial;
}

સ્થિર Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    પાછા ev->type == ReparentNotify &&
           ev->xreparent.window == unmap->window &&
           ev->xreparent.serial == unmap->serial;
}

સ્થિર bool Is_ઉપલું_Latin1(અચલ અક્ષર *string, પૂર્ણાંક length)
{
    જ્યારે (length-- > 0) {
        Uint8 ch = (Uint8)*string;
        જો (ch >= 0x80) {
            પાછા true;
        }
        ++string;
    }
    પાછા false;
}

સ્થિર પૂર્ણાંક XLookupStringAsUTF8(XKeyEvent *event_struct, અક્ષર *buffer_return, પૂર્ણાંક bytes_buffer, ચાવી_Sym *keysym_return, XComposeStatus *status_in_out)
{
    પૂર્ણાંક result = X11_XLookupString(event_struct, buffer_return, bytes_buffer, keysym_return, status_in_out);
    જો (Is_ઉપલું_Latin1(buffer_return, result)) {
        અક્ષર *utf8_text = SDL_iconv_string("UTF-8", "ISO-8859-1", buffer_return, result + 1);
        જો (utf8_text) {
            SDL_strlcpy(buffer_return, utf8_text, bytes_buffer);
            SDL_free(utf8_text);
            પાછા SDL_strlen(buffer_return);
        } નહીંતર {
            પાછા 0;
        }
    }
    પાછા result;
}

SDL_WindowData *X11_FindWindow(SDL_VideoData *videodata, Window window)
{
    જો (videodata && videodata->windowlist) {
        માટે (પૂર્ણાંક i = 0; i < videodata->numwindows; ++i) {
            જો ((videodata->windowlist[i] != ખાલી) &&
                (videodata->windowlist[i]->xwindow == window)) {
                પાછા videodata->windowlist[i];
            }
        }
    }
    પાછા ખાલી;
}

Uint64 X11_GetEventTimestamp(unsigned long time)
{
    // FIXME: Get the event time in the SDL tick time base
    પાછા SDL_GetTicksNS();
}

શૂન્ય X11_Handle_ચાવી_Event(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    ચાવી_Code_2 keycode = xevent->xkey.keycode;
    ચાવી_Sym keysym = No_પ્રતીક;
    પૂર્ણાંક text_length = 0;
    અક્ષર text[64];
    Status status = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == ચાવી_Press);
    SDL_Scancode scancode = videodata->keyboard.ચાવી_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.window, (xevent->type == ચાવી_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#endif
#ifdef DEBUG_SCANCODES
    જો (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        પૂર્ણાંક min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_ચાવી_Code_To_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysymToString(keysym));
    }
#endif // DEBUG SCANCODES

    text[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    જો (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (LockMask | videodata->keyboard.numlock_mask | videodata->keyboard.scrolllock_mask);
    }

    જો (SDL_Text_આગત_Active(windowdata->window)) {
        // filter events catches XIM events and sends them to the correct handler
        જો (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            handled_by_ime = true;
        }

        જો (!handled_by_ime) {
#ifdef X_HAVE_UTF8_STRING
            જો (windowdata->ic && xevent->type == ચાવી_Press) {
                text_length = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, text, કદ(text) - 1,
                                      &keysym, &status);
            } નહીંતર {
                text_length = XLookupStringAsUTF8(&xevent->xkey, text, કદ(text) - 1, &keysym, ખાલી);
            }
#નહીંતર
            text_length = XLookupStringAsUTF8(&xevent->xkey, text, કદ(text) - 1, &keysym, ખાલી);
#endif
        }
    }

    જો (!handled_by_ime) {
        જો (pressed) {
            X11_Handle_Modifier_ચાવીઓ(videodata, scancode, true);
            SDL_Send_Keyboard_ચાવી_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            જો (*text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                text[text_length] = '\0';
                X11_ClearComposition(windowdata);
                SDL_SendKeyboardText(text);
            }
        } નહીંતર {
            જો (X11_ચાવી_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                પાછા;
            }

            X11_Handle_Modifier_ચાવીઓ(videodata, scancode, false);
            SDL_Send_Keyboard_ચાવી_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    જો (pressed) {
        X11_UpdateUserTime(windowdata, xevent->xkey.time);
    }
}

શૂન્ય X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, પૂર્ણાંક button, દશાંશ x, દશાંશ y, unsigned long time, unsigned long serial)
{
    SDL_Window *window = windowdata->window;
    પૂર્ણાંક xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#endif

    SDL_Mouse *mouse = SDL_GetMouse();
    જો (!mouse->relative_mode && (x != mouse->x || y != mouse->y)) {
        X11_ProcessHitTest(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, window, mouseID, false, x, y);
    }

    જો (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, window, mouseID, (દશાંશ)-xticks, (દશાંશ)yticks, SDL_MOUSEWHEEL_NORMAL);
    } નહીંતર {
        જો (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        જો (button == Button1) {
            જો (X11_TriggerHitTestAction(_this, windowdata, x, y)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0);
                પાછા; // don't pass this event on to app.
            }
        }
        જો (windowdata->last_focus_event_time) {
            અચલ પૂર્ણાંક X11_FOCUS_CLICK_TIMEOUT = 10;
            જો (SDL_GetTicks() < (windowdata->last_focus_event_time + X11_FOCUS_CLICK_TIMEOUT)) {
                જો (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->last_focus_event_time = 0;
        }
        જો (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, window, mouseID, button, true);
        }
    }
    X11_UpdateUserTime(windowdata, time);
}

શૂન્ય X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, પૂર્ણાંક button, unsigned long time)
{
    SDL_Window *window = windowdata->window;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    પૂર્ણાંક xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#endif
    જો (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        જો (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, window, mouseID, button, false);

        જો (window->internal->pending_grab) {
            X11_SetWindowMouseGrab(_this, window, true);
        }
    }
}

શૂન્ય X11_Get_Border_કિંમતો(SDL_WindowData *data)
{
    SDL_VideoData *videodata = data->videodata;
    Display *display = videodata->display;

    Atom type;
    પૂર્ણાંક format;
    unsigned long nitems, bytes_after;
    unsigned અક્ષર *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    જો (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
        જો (X11_XGetWindowProperty(display, data->xwindow, videodata->atoms._NET_FRAME_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &bytes_after, &property) == Success) {
            જો (type != None && nitems == 4) {
                data->border_ડાબું = (પૂર્ણાંક)((long *)property)[0];
                data->border_જમણું = (પૂર્ણાંક)((long *)property)[1];
                data->border_ટોચ = (પૂર્ણાંક)((long *)property)[2];
                data->border_bottom = (પૂર્ણાંક)((long *)property)[3];
            }
            X11_XFree(property);

#ifdef DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", data->border_ડાબું, data->border_જમણું, data->border_ટોચ, data->border_bottom);
#endif
        }
    } નહીંતર {
        data->border_ડાબું = data->border_ટોચ = data->border_જમણું = data->border_bottom = 0;
    }
}

શૂન્ય X11_EmitConfigureNotifyEvents(SDL_WindowData *data, XConfigureEvent *xevent)
{
    જો (!data->size_move_event_flags) {
        પૂર્ણાંક x = xevent->x;
        પૂર્ણાંક y = xevent->y;

        જો (xevent->x != data->last_xconfigure.x ||
            xevent->y != data->last_xconfigure.y) {
            data->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);

        માટે (SDL_Window *w = data->window->first_child; w; w = w->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            જો (SDL_WINDOW_IS_POPUP(w) && !(w->flags & SDL_WINDOW_HIDDEN)) {
                X11_UpdateWindowPosition(w, true);
            }
        }

        જો (xevent->width != data->last_xconfigure.width ||
            xevent->height != data->last_xconfigure.height) {
            data->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, xevent->width, xevent->height);
    }

    SDL_copyp(&data->last_xconfigure, xevent);
}

સ્થિર શૂન્ય X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display;
    SDL_WindowData *data;
    XClientMessageEvent m;
    પૂર્ણાંક i;

    SDL_assert(videodata != ખાલી);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    જો (xevent->type != ચાવી_Press && xevent->type != ચાવી_Release) {
        જો (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            પાછા;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    જો (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        પાછા;
    }
#endif

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    જો (g_X11EventHook) {
        જો (!g_X11EventHook(g_X11EventHookData, xevent)) {
            પાછા;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    જો (videodata->xrandr_event_base && (xevent->type == (videodata->xrandr_event_base + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#endif

#ifdef DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.window);
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    જો (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#endif

        જો (ev->subtype == XFixesSetSelectionOwnerNotify)
        {
            જો (ev->selection != videodata->atoms.CLIPBOARD)
                પાછા;

            જો (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_window)
                પાછા;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, GetWindow(_this), CurrentTime);
        }

        પાછા;
    }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES

    જો ((videodata->clipboard_window != None) &&
        (videodata->clipboard_window == xevent->xany.window)) {
        X11_HandleClipboardEvent(_this, xevent);
        પાછા;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    data = X11_FindWindow(videodata, xevent->xany.window);

    જો (!data) {
        // The window for KeymapNotify, etc events is 0
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        જો (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            પસંદગી (xkbevent->any.xkb_type) {
            સ્થિતિ XkbStateNotify:
            {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.window);
#endif
                જો ((xkbevent->state.changed & XkbGroupStateMask) && xkbevent->state.group != videodata->keyboard.xkb.current_group) {
                    videodata->keyboard.xkb.current_group = xkbevent->state.group;
                    SDL_SetKeymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_group], true);
                }

                જો (xkbevent->state.changed & XkbModifierStateMask) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.base_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } તોડો;

            સ્થિતિ XkbMapNotify:
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.window);
                SDL_FALLTHROUGH;
#endif
            સ્થિતિ XkbNewKeyboardNotify:
            {
#ifdef DEBUG_XEVENTS
                જો (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.window);
                }
#endif
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                જો (xkbevent->any.serial != videodata->keyboard.xkb.last_map_serial) {
                    videodata->keyboard.xkb.last_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } તોડો;

            મૂળભૂત:
                તોડો;
            }
        } નહીંતર
#endif
        જો (xevent->type == KeymapNotify) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.window);
#endif
            જો (SDL_GetKeyboardFocus() != ખાલી) {
                જો (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } નહીંતર જો (xevent->type == MappingNotify) {
            અચલ પૂર્ણાંક request = xevent->xmapping.request;

            જો (request == MappingPointer) {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                X11_Xinput2UpdatePointerMapping(_this);
            } નહીંતર જો (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                જો (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } નહીંતર જો (xevent->type == PropertyNotify && videodata) {
            અક્ષર *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            જો (name_of_atom) {
                જો (SDL_startswith(name_of_atom, "_ICC_PROFILE")) {
                    XWindowAttributes attrib;
                    પૂર્ણાંક screennum;
                    માટે (i = 0; i < videodata->numwindows; ++i) {
                        જો (videodata->windowlist[i] != ખાલી) {
                            data = videodata->windowlist[i];
                            X11_XGetWindowAttributes(display, data->xwindow, &attrib);
                            screennum = X11_XScreen_સંખ્યા_Of_Screen(attrib.screen);
                            જો (screennum == 0 && SDL_strcmp(name_of_atom, "_ICC_PROFILE") == 0) {
                                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                            } નહીંતર જો (SDL_strncmp(name_of_atom, "_ICC_PROFILE_", કદ("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_of_atom) > કદ("_ICC_PROFILE_") - 1) {
                                પૂર્ણાંક iccscreennum = SDL_atoi(&name_of_atom[કદ("_ICC_PROFILE_") - 1]);

                                જો (screennum == iccscreennum) {
                                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                                }
                            }
                        }
                    }
                } નહીંતર જો (SDL_strcmp(name_of_atom, "_NET_WORKAREA") == 0) {
                    માટે (i = 0; i < _this->અંક_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
                    }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
                } નહીંતર જો (SDL_strcmp(name_of_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_of_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#endif
                }
                X11_XFree(name_of_atom);
            }
        }
        પાછા;
    }

    પસંદગી (xevent->type) {

        // Gaining mouse coverage?
    સ્થિતિ EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        જો (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        જો (xevent->xcrossing.mode == NotifyUngrab) {
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
            જો ((data->pointer_barrier_active == true) && windowdata->window->flags & SDL_WINDOW_આગત_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->window, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#endif

        જો (!mouse->relative_mode) {
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (દશાંશ)xevent->xcrossing.x, (દશાંશ)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        જો (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            SDL_UpdateWindowGrab(data->window);
        }

        X11_ProcessHitTest(_this, data, mouse->last_x, mouse->last_y, true);
    } તોડો;
        // Losing mouse coverage?
    સ્થિતિ LeaveNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        જો (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        જો (xevent->xcrossing.mode == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#endif
        જો (!SDL_GetMouse()->relative_mode) {
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (દશાંશ)xevent->xcrossing.x, (દશાંશ)xevent->xcrossing.y);
        }

        જો (xevent->xcrossing.mode != NotifyGrab &&
            xevent->xcrossing.mode != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            જો (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                X11_SetWindowKeyboardGrab(_this, data->window, false);
            }

            SDL_SetMouseFocus(ખાલી);
        }
    } તોડો;

        // Gaining input focus?
    સ્થિતિ FocusIn:
    {
        જો (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            તોડો;
        }

        જો (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            તોડો;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.window);
#endif
        જો (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            data->pending_focus = PENDING_FOCUS_NONE;
            data->pending_focus_time = 0;
            X11_DispatchFocusIn(_this, data);
        } નહીંતર {
            data->pending_focus = PENDING_FOCUS_IN;
            data->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }
        data->last_focus_event_time = SDL_GetTicks();
    } તોડો;

        // Losing input focus?
    સ્થિતિ FocusOut:
    {
        જો (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            તોડો;
        }
        જો (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            તોડો;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.window);
#endif
        જો (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            data->pending_focus = PENDING_FOCUS_NONE;
            data->pending_focus_time = 0;
            X11_DispatchFocusOut(_this, data);
        } નહીંતર {
            data->pending_focus = PENDING_FOCUS_OUT;
            data->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        જો (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, ખાલી, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } તોડો;


        // Have we been iconified?
    સ્થિતિ UnmapNotify:
    {
        XEvent ev;

#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.window);
#endif

        જો (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } નહીંતર {
            X11_DispatchUnmapNotify(data);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        જો (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, ખાલી, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } તોડો;

        // Have we been restored?
    સ્થિતિ MapNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.window);
#endif
        X11_DispatchMapNotify(data);

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        જો (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, &data->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } તોડો;

        // Have we been resized or moved?
    સ્થિતિ ConfigureNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.window,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.width, xevent->xconfigure.height);
#endif
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        જો (!xevent->xconfigure.send_event) {
            unsigned પૂર્ણાંક અંક_Children;
            Window ChildReturn, મૂળ_2, Parent;
            Window *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_last_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

            X11_XQuery_વૃક્ષ(data->videodata->display, xevent->xconfigure.window, &મૂળ_2, &Parent, &Children, &અંક_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      Parent, Default_મૂળ_Window(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &ChildReturn);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            જો (x11_last_error == BadWindow) {
                તોડો;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        અચલ SDL_WindowFlags changed = X11_GetNetWMState(_this, data->window, xevent->xproperty.window) ^ data->window->flags;
        જો (changed & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) {
            SDL_copyp(&data->pending_xconfigure, &xevent->xconfigure);
            data->emit_size_move_after_property_notify = true;
        }

        જો (!data->emit_size_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(data, &xevent->xconfigure);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(data->window, &xevent->xconfigure);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } તોડો;

        // Have we been requested to quit (or another client message?)
    સ્થિતિ ClientMessage:
    {
        સ્થિર પૂર્ણાંક xdnd_version = 0;

        જો (xevent->xclient.message_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.data.l[1] & 1;
            data->xdnd_source = xevent->xclient.data.l[0];
            xdnd_version = (xevent->xclient.data.l[1] >> 24);
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", data->xdnd_source);
            SDL_Log("Protocol version to use : %d", xdnd_version);
            SDL_Log("More then 3 data types : %d", (પૂર્ણાંક)use_list);
#endif

            જો (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, data->xdnd_source, videodata->atoms.XdndTypeList);
                // pick one
                data->xdnd_req = X11_PickTarget(display, (Atom *)p.data, p.ગણતરી);
                X11_XFree(p.data);
            } નહીંતર {
                // pick from list of three
                data->xdnd_req = X11_PickTargetFromAtoms(display, xevent->xclient.data.l[2], xevent->xclient.data.l[3], xevent->xclient.data.l[4]);
            }
        } નહીંતર જો (xevent->xclient.message_type == videodata->atoms.XdndLeave) {
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.data.l[0]);
#endif
            SDL_SendDropComplete(data->window);
        } નહીંતર જો (xevent->xclient.message_type == videodata->atoms.XdndPosition) {

#ifdef DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            જો (xdnd_version >= 2) {
                act = xevent->xclient.data.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#endif
            {
                // Drag and Drop position
                પૂર્ણાંક મૂળ_x, મૂળ_y, window_x, window_y;
                Window ChildReturn;
                મૂળ_x = xevent->xclient.data.l[2] >> 16;
                મૂળ_y = xevent->xclient.data.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_મૂળ_Window(display), data->xwindow,
                                          મૂળ_x, મૂળ_y, &window_x, &window_y, &ChildReturn);

                SDL_SendDropPosition(data->window, (દશાંશ)window_x, (દશાંશ)window_y);
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
        } નહીંતર જો (xevent->xclient.message_type == videodata->atoms.XdndDrop) {
            જો (data->xdnd_req == None) {
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
            } નહીંતર {
                // convert
                જો (xdnd_version >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, data->xdnd_req, videodata->atoms.PRIMARY, data->xwindow, xevent->xclient.data.l[2]);
                } નહીંતર {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, data->xdnd_req, videodata->atoms.PRIMARY, data->xwindow, CurrentTime);
                }
            }
        } નહીંતર જો ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.data.l[0] == videodata->atoms._NET_WM_PING)) {
            Window મૂળ = Default_મૂળ_Window(display);

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.window);
#endif
            xevent->xclient.window = મૂળ;
            X11_XSendEvent(display, મૂળ, False, SubstructureRedirectMask | SubstructureNotifyMask, xevent);
            તોડો;
        }

        નહીંતર જો ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.data.l[0] == videodata->atoms.WM_DELETE_WINDOW)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.window);
#endif
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            તોડો;
        } નહીંતર જો ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.data.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", data);
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(data->window, &xevent->xclient);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
            તોડો;
        }
    } તોડો;

        // Do we need to refresh ourselves?
    સ્થિતિ Expose:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.window, xevent->xexpose.ગણતરી);
#endif
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    } તોડો;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    સ્થિતિ ચાવી_Press:
    સ્થિતિ ચાવી_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        જો (data->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            તોડો;
        } નહીંતર જો (xevent->xkey.serial == videodata->xinput_last_ચાવી_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_last_keyboard_device;
        }

        X11_Handle_ચાવી_Event(_this, data, keyboardID, xevent);
    } તોડો;

    સ્થિતિ MotionNotify:
    {
        જો (X11_Xinput2HandlesMotionForWindow(data)) {
            // This input is being handled by XInput2
            તોડો;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        જો (!mouse->relative_mode) {
#ifdef DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.window, xevent->xmotion.x, xevent->xmotion.y);
#endif

            X11_ProcessHitTest(_this, data, (દશાંશ)xevent->xmotion.x, (દશાંશ)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (દશાંશ)xevent->xmotion.x, (દશાંશ)xevent->xmotion.y);
        }
    } તોડો;

    સ્થિતિ ButtonPress:
    {
        જો (data->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            તોડો;
        }

        X11_HandleButtonPress(_this, data, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.time, xevent->xbutton.serial);
    } તોડો;

    સ્થિતિ ButtonRelease:
    {
        જો (data->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            તોડો;
        }

        X11_HandleButtonRelease(_this, data, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.time);
    } તોડો;

    સ્થિતિ PropertyNotify:
    {
#ifdef DEBUG_XEVENTS
        unsigned અક્ષર *propdata;
        પૂર્ણાંક status, real_format;
        Atom real_type;
        unsigned long વસ્તુઓ_read, વસ્તુઓ_ડાબું;

        અક્ષર *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        જો (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.window, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.time);
            X11_XFree(name);
        }

        status = X11_XGetWindowProperty(display, data->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &વસ્તુઓ_read, &વસ્તુઓ_ડાબું, &propdata);
        જો (status == Success && વસ્તુઓ_read > 0) {
            જો (real_type == XA_INTEGER) {
                પૂર્ણાંક *કિંમતો = (પૂર્ણાંક *)propdata;

                SDL_Log("{");
                માટે (i = 0; i < વસ્તુઓ_read; i++) {
                    SDL_Log(" %d", કિંમતો[i]);
                }
                SDL_Log(" }");
            } નહીંતર જો (real_type == XA_CARDINAL) {
                જો (real_format == 32) {
                    Uint32 *કિંમતો = (Uint32 *)propdata;

                    SDL_Log("{");
                    માટે (i = 0; i < વસ્તુઓ_read; i++) {
                        SDL_Log(" %d", કિંમતો[i]);
                    }
                    SDL_Log(" }");
                } નહીંતર જો (real_format == 16) {
                    Uint16 *કિંમતો = (Uint16 *)propdata;

                    SDL_Log("{");
                    માટે (i = 0; i < વસ્તુઓ_read; i++) {
                        SDL_Log(" %d", કિંમતો[i]);
                    }
                    SDL_Log(" }");
                } નહીંતર જો (real_format == 8) {
                    Uint8 *કિંમતો = (Uint8 *)propdata;

                    SDL_Log("{");
                    માટે (i = 0; i < વસ્તુઓ_read; i++) {
                        SDL_Log(" %d", કિંમતો[i]);
                    }
                    SDL_Log(" }");
                }
            } નહીંતર જો (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } નહીંતર જો (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                માટે (i = 0; i < વસ્તુઓ_read; i++) {
                    અક્ષર *atomname = X11_XGetAtomName(display, atoms[i]);
                    જો (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } નહીંતર {
                અક્ષર *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                જો (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        જો (status == Success) {
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
        જો (!data->user_time) {
            data->user_time = xevent->xproperty.time;
        }

        જો (xevent->xproperty.atom == data->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            અચલ SDL_WindowFlags flags = X11_GetNetWMState(_this, data->window, xevent->xproperty.window);
            અચલ SDL_WindowFlags changed = flags ^ data->window->flags;

            જો ((changed & SDL_WINDOW_HIDDEN) && !(flags & SDL_WINDOW_HIDDEN)) {
                X11_DispatchMapNotify(data);
            }

            જો (!SDL_WINDOW_IS_POPUP(data->window)) {
                જો (changed & SDL_WINDOW_FULLSCREEN) {
                    data->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    જો (flags & SDL_WINDOW_FULLSCREEN) {
                        જો (!(flags & SDL_WINDOW_MINIMIZED)) {
                            અચલ bool commit = SDL_memcmp(&data->window->current_fullscreen_mode, &data->requested_fullscreen_mode, કદ(SDL_DisplayMode)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                            જો (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&data->window->current_fullscreen_mode, &data->window->requested_fullscreen_mode);
                                SDL_UpdateFullscreenMode(data->window, SDL_FULLSCREEN_OP_UPDATE, true);
                            } નહીંતર {
                                SDL_UpdateFullscreenMode(data->window, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } નહીંતર {
                        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                        SDL_UpdateFullscreenMode(data->window, false, false);

                        SDL_zero(data->requested_fullscreen_mode);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_SetWindowMinMax(data->window, !!(flags & SDL_WINDOW_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        જો (data->fullscreen_borders_forced_on) {
                            data->toggle_borders = true;
                            data->fullscreen_borders_forced_on = false;
                        }
                    }

                    જો ((flags & SDL_WINDOW_FULLSCREEN) &&
                        (data->border_ટોચ || data->border_ડાબું || data->border_bottom || data->border_જમણું)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        data->size_move_event_flags |= X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        data->previous_borders_nonzero = true;
                    } નહીંતર જો (!(flags & SDL_WINDOW_FULLSCREEN) &&
                               data->previous_borders_nonzero &&
                               (!data->border_ટોચ && !data->border_ડાબું && !data->border_bottom && !data->border_જમણું)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        data->size_move_event_flags |= X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        data->previous_borders_nonzero = false;
                    } નહીંતર {
                        data->size_move_event_flags = 0;
                        data->previous_borders_nonzero = false;

                        જો (!(data->window->flags & SDL_WINDOW_FULLSCREEN) && data->toggle_borders) {
                            data->toggle_borders = false;
                            X11_SetWindowBordered(_this, data->window, !(data->window->flags & SDL_WINDOW_BORDERLESS));
                        }
                    }
                }
                જો ((changed & SDL_WINDOW_MAXIMIZED) && ((flags & SDL_WINDOW_MAXIMIZED) && !(flags & SDL_WINDOW_MINIMIZED))) {
                    data->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    જો ((changed & SDL_WINDOW_MINIMIZED)) {
                        data->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                    }
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
                }
                જો ((changed & SDL_WINDOW_MINIMIZED) && (flags & SDL_WINDOW_MINIMIZED)) {
                    data->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                }
                જો (!(flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
                    data->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    જો (!(flags & SDL_WINDOW_FULLSCREEN)) {
                        જો (data->pending_position) {
                            data->pending_position = false;
                            data->pending_operation |= X11_PENDING_OP_MOVE;
                            data->expected.x = data->window->pending.x - data->border_ડાબું;
                            data->expected.y = data->window->pending.y - data->border_ટોચ;
                            X11_XMoveWindow(display, data->xwindow, data->expected.x, data->expected.y);
                        }
                        જો (data->pending_size) {
                            data->pending_size = false;
                            data->pending_operation |= X11_PENDING_OP_RESIZE;
                            data->expected.w = data->window->pending.w;
                            data->expected.h = data->window->pending.h;
                            X11_XResizeWindow(display, data->xwindow, data->window->pending.w, data->window->pending.h);
                        }
                    }
                }
                જો (data->emit_size_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(data, &data->pending_xconfigure);
                    data->emit_size_move_after_property_notify = false;
                }
                જો ((flags & SDL_WINDOW_આગત_FOCUS)) {
                    જો (data->pending_move) {
                        DispatchWindowMove(_this, data, &data->pending_move_point);
                        data->pending_move = false;
                    }
                }
            }
            જો (changed & SDL_WINDOW_OCCLUDED) {
                SDL_SendWindowEvent(data->window, (flags & SDL_WINDOW_OCCLUDED) ? SDL_EVENT_WINDOW_OCCLUDED : SDL_EVENT_WINDOW_EXPOSED, 0, 0);
            }
        } નહીંતર જો (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            પૂર્ણાંક format;
            unsigned long nitems, bytes_after;
            unsigned અક્ષર *prop_data = ખાલી;

            જો (X11_XGetWindowProperty(display, data->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &bytes_after, &prop_data) == Success) {
                જો (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_data;

                    જો ((state == 0 || state == 3) && !data->window->is_hiding && !(data->window->flags & SDL_WINDOW_HIDDEN)) {
                        // Withdrawn or Iconic
                        જો (!(data->window->flags & SDL_WINDOW_MINIMIZED)) {
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
                        }
                    } નહીંતર જો (state == 1) { // NormalState
                        જો (data->window->flags & SDL_WINDOW_MINIMIZED) {
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_data);
            }
        } નહીંતર જો (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } નહીંતર જો (xevent->xproperty.atom == videodata->atoms._NET_FRAME_EXTENTS) {
            X11_Get_Border_કિંમતો(data);
            જો (data->size_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                data->size_move_event_flags &= ~X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            જો (!(data->window->flags & SDL_WINDOW_FULLSCREEN) && data->toggle_borders) {
                data->toggle_borders = false;
                X11_SetWindowBordered(_this, data->window, !(data->window->flags & SDL_WINDOW_BORDERLESS));
            }
        }
    } તોડો;

    સ્થિતિ SelectionNotify:
    {
        Atom target = xevent->xselection.target;
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.window,
               xevent->xselection.requestor, xevent->xselection.target);
#endif
        જો (target == data->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, data->xwindow, videodata->atoms.PRIMARY);

            જો (p.format == 8) {
                અક્ષર *saveptr = ખાલી;
                અક્ષર *name = X11_XGetAtomName(display, target);
                જો (name) {
                    અક્ષર *token = SDL_strtok_r((અક્ષર *)p.data, "\r\n", &saveptr);
                    જ્યારે (token) {
                        જો ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_SendDropText(data->window, token);
                        } નહીંતર જો (SDL_strcmp("text/uri-list", name) == 0) {
                            જો (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(data->window, ખાલી, token);
                            }
                        }
                        token = SDL_strtok_r(ખાલી, "\r\n", &saveptr);
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
    } તોડો;

    મૂળભૂત:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.window, xevent->type);
#endif
    } તોડો;
    }
}

સ્થિર શૂન્ય X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    પૂર્ણાંક i;

    જો (videodata && videodata->windowlist) {
        માટે (i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *data = videodata->windowlist[i];
            જો (data && data->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                જો (now >= data->pending_focus_time) {
                    જો (data->pending_focus == PENDING_FOCUS_IN) {
                        X11_DispatchFocusIn(_this, data);
                    } નહીંતર {
                        X11_DispatchFocusOut(_this, data);
                    }
                    data->pending_focus = PENDING_FOCUS_NONE;
                }
            }
        }
    }
}

સ્થિર Bool isAnyEvent(Display *display, XEvent *ev, XPointer arg)
{
    પાછા True;
}

સ્થિર bool X11_PollEvent(Display *display, XEvent *event)
{
    જો (!X11_XCheckIfEvent(display, event, isAnyEvent, ખાલી)) {
        પાછા false;
    }

    પાછા true;
}

શૂન્ય X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
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

પૂર્ણાંક X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    જો (X11_PollEvent(display, &xevent)) {
        // Fall through
    } નહીંતર જો (timeoutNS == 0) {
        પાછા 0;
    } નહીંતર {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        પૂર્ણાંક err = SDL_IOReady(Connection_સંખ્યા(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        જો (err > 0) {
            જો (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                પાછા 1;
            }
        } નહીંતર જો (err == 0) {
            // Timeout
            પાછા 0;
        } નહીંતર {
            // Error returned from poll()/select()

            જો (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                પાછા 1;
            } નહીંતર {
                પાછા err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    પાછા 1;
}

શૂન્ય X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    XEvent xevent;
    પૂર્ણાંક i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    માટે (i = 0; i < _this->અંક_displays; ++i) {
        જો (_this->displays[i]->internal->mode_switch_deadline_ns) {
            જો (_this->displays[i]->fullscreen_window) {
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            } નહીંતર જો (SDL_GetTicksNS() >= _this->displays[i]->internal->mode_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_SetDisplayModeForDisplay(_this->displays[i], ખાલી);
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            }
        }
    }

    જો (data->last_mode_change_deadline) {
        જો (SDL_GetTicks() >= data->last_mode_change_deadline) {
            data->last_mode_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    જો (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        જો (!data->screensaver_activity || now >= (data->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(data->display);

#ifdef SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#endif

            data->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    જ્યારે (X11_PollEvent(data->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    માટે (i = 0; i < data->numwindows; ++i) {
        જો (data->windowlist[i] != ખાલી &&
            data->windowlist[i]->flash_cancel_time &&
            SDL_GetTicks() >= data->windowlist[i]->flash_cancel_time) {
            X11_FlashWindow(_this, data->windowlist[i]->window, SDL_FLASH_CANCEL);
        }
    }

    જો (data->xinput_hierarchy_changed) {
        X11_Xinput2UpdateDevices(_this);
        data->xinput_hierarchy_changed = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_VideoData *data = _this->internal;
    પૂર્ણાંક dummy;
    પૂર્ણાંક major_version, minor_version;
#endif // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#ifdef SDL_USE_LIBDBUS
    જો (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        પાછા true;
    }

    જો (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    જો (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        જો (!X11_XScreenSaverQueryExtension(data->display, &dummy, &dummy) ||
            !X11_XScreenSaverQueryVersion(data->display,
                                          &major_version, &minor_version) ||
            major_version < 1 || (major_version == 1 && minor_version < 1)) {
            પાછા SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(data->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(data->display);
        પાછા true;
    }
#endif
    પાછા SDL_Unsupported();
}

#endif // SDL_VIDEO_DRIVER_X11
