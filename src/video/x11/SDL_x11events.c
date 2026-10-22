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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#அந்தர்பாவ <sys/types.h>
#அந்தர்பாவ <sys/time.h>
#அந்தர்பாவ <signal.h>
#அந்தர்பாவ <unistd.h>
#அந்தர்பாவ <limits.h> // For INT_MAX

#அந்தர்பாவ "SDL_x11video.h"
#அந்தர்பாவ "SDL_x11pen.h"
#அந்தர்பாவ "SDL_x11touch.h"
#அந்தர்பாவ "SDL_x11xinput2.h"
#அந்தர்பாவ "SDL_x11xfixes.h"
#அந்தர்பாவ "SDL_x11settings.h"
#அந்தர்பாவ "../SDL_clipboard_c.h"
#அந்தர்பாவ "SDL_x11xsync.h"
#அந்தர்பாவ "../../core/unix/SDL_poll.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"
#அந்தர்பாவ "../../events/SDL_touch_c.h"
#அந்தர்பாவ "../../core/linux/SDL_system_theme.h"
#அந்தர்பாவ "../SDL_sysvideo.h"

#அந்தர்பாவ <stdio.h>

#எனில் 0
#define DEBUG_XEVENTS
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPLEFT
#define _NET_WM_MOVERESIZE_SIZE_TOPLEFT 0
#endif

#ifndef NET_WM_MOVERESIZE_SIZE_உச்சி
#define NET_WM_MOVERESIZE_SIZE_உச்சி 1
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPRIGHT
#define _NET_WM_MOVERESIZE_SIZE_TOPRIGHT 2
#endif

#ifndef NET_WM_MOVERESIZE_SIZE_வலது
#define NET_WM_MOVERESIZE_SIZE_வலது 3
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

#ifndef NET_WM_MOVERESIZE_SIZE_இடது
#define NET_WM_MOVERESIZE_SIZE_இடது 7
#endif

#ifndef _NET_WM_MOVERESIZE_MOVE
#define _NET_WM_MOVERESIZE_MOVE 8
#endif

வகைவரை கட்டமைப்பு
{
    unsigned எழுத்து *data;
    முழு format, மொத்தம்;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
நிலையான வெறுமை X11_ReadProperty(SDL_x11Prop *p, Display *disp, Window w, Atom prop)
{
    unsigned எழுத்து *ret = வெற்று;
    Atom type;
    முழு fmt;
    unsigned long மொத்தம்;
    unsigned long bytes_இடது;
    முழு bytes_fetch = 0;

    செய் {
        எனில் (ret) {
            X11_XFree(ret);
        }
        X11_XGetWindowProperty(disp, w, prop, 0, bytes_fetch, False, AnyPropertyType, &type, &fmt, &மொத்தம், &bytes_இடது, &ret);
        bytes_fetch += bytes_இடது;
    } போது (bytes_இடது != 0);

    p->data = ret;
    p->format = fmt;
    p->மொத்தம் = மொத்தம்;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
நிலையான Atom X11_PickTarget(Display *disp, Atom list[], முழு list_மொத்தம்)
{
    மாறிலி Atom text_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    க்கு (முழு i = 0; i < list_மொத்தம் && request != text_uri_request; i++) {
        எழுத்து *name = X11_XGetAtomName(disp, list[i]);
        // Preferred MIME targets
        எனில் ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            எனில் (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        எனில் ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            எனில் (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    எனில் (preferred != None && request != text_uri_request) {
        request = preferred;
    }
    திரும்பு request;
}

/* Wrapper for X11_PickTarget for a maximum of three targets, a special
   case in the Xdnd protocol */
நிலையான Atom X11_PickTargetFromAtoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    முழு மொத்தம் = 0;
    Atom atom[3];
    எனில் (a0 != None) {
        atom[மொத்தம்++] = a0;
    }
    எனில் (a1 != None) {
        atom[மொத்தம்++] = a1;
    }
    எனில் (a2 != None) {
        atom[மொத்தம்++] = a2;
    }
    திரும்பு X11_PickTarget(disp, atom, மொத்தம்);
}

கட்டமைப்பு சாவி_Repeat_Check_Data
{
    XEvent *event;
    bool found;
};

நிலையான Bool X11_சாவி_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    கட்டமைப்பு சாவி_Repeat_Check_Data *d = (கட்டமைப்பு சாவி_Repeat_Check_Data *)arg;
    எனில் (chkev->type == சாவி_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.time - d->event->xkey.time < 2) {
        d->found = true;
    }
    திரும்பு False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
நிலையான bool X11_சாவி_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    கட்டமைப்பு சாவி_Repeat_Check_Data d;
    d.event = event;
    d.found = false;
    எனில் (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_சாவி_Repeat_Check_If_Event, (XPointer)&d);
    }
    திரும்பு d.found;
}

bool X11_IsWheelEvent(முழு button, முழு *xticks, முழு *yticks)
{
    /* according to the xlib docs, no specific mouse wheel events exist.
       However, the defacto standard is that the vertical wheel is X buttons
       4 (up) and 5 (down) and a horizontal wheel is 6 (left) and 7 (right). */

    // Xlib defines "Button1" through 5, so we just use literals here.
    தேர்வு (button) {
    நிலை 4:
        *yticks = 1;
        திரும்பு true;
    நிலை 5:
        *yticks = -1;
        திரும்பு true;
    நிலை 6:
        *xticks = 1;
        திரும்பு true;
    நிலை 7:
        *xticks = -1;
        திரும்பு true;
    இயல்பு:
        நிறுத்து;
    }
    திரும்பு false;
}

// An X11 event hook
நிலையான SDL_X11EventHook g_X11EventHook = வெற்று;
நிலையான வெறுமை *g_X11EventHookData = வெற்று;

வெறுமை SDL_SetX11EventHook(SDL_X11EventHook callback, வெறுமை *userdata)
{
    g_X11EventHook = callback;
    g_X11EventHookData = userdata;
}

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
நிலையான வெறுமை X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_VideoData *videodata = _this->internal;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    எனில் (X11_XGetEventData(videodata->display, cookie)) {
        எனில் (!g_X11EventHook || g_X11EventHook(g_X11EventHookData, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFreeEventData(videodata->display, cookie);
    }
}
#endif // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

நிலையான வெறுமை X11_Update_System_சாவி_Modifiers(SDL_VideoData *viddata)
{
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    எனில் (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        எனில் (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.base_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } இல்லையெனில்
#endif
        {
        Window junk_window;
        முழு x, y;
        unsigned முழு mod_mask;

        X11_XQueryPointer(viddata->display, Default_வேர்_Window(viddata->display), &junk_window, &junk_window, &x, &y, &x, &y, &mod_mask);
        viddata->keyboard.pressed_modifiers = mod_mask & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        viddata->keyboard.locked_modifiers = mod_mask & (LockMask | viddata->keyboard.numlock_mask | viddata->keyboard.scrolllock_mask);
    }
}

நிலையான வெறுமை X11_ReconcileModifiers(SDL_VideoData *viddata, bool சாவி_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    எனில் (சாவி_pressed) {
        எனில் (viddata->keyboard.pressed_modifiers & ShiftMask) {
            எனில் (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT);
            }
        }

        எனில் (viddata->keyboard.pressed_modifiers & ControlMask) {
            எனில் (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        எனில் (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            எனில் (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        எனில் (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            எனில் (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } இல்லையெனில் {
        எனில் (viddata->keyboard.pressed_modifiers & ShiftMask) {
            எனில் (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } இல்லையெனில் {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        எனில் (viddata->keyboard.pressed_modifiers & ControlMask) {
            எனில் (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } இல்லையெனில் {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        எனில் (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            எனில் (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } இல்லையெனில் {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        எனில் (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            எனில் (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } இல்லையெனில் {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        எனில் (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_mask) {
            எனில் (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_MODE)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_MODE;
            }
        } இல்லையெனில் {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        எனில் (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_mask) {
            எனில் (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } இல்லையெனில் {
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
    எனில் (viddata->keyboard.locked_modifiers & ShiftMask) {
        எனில் (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT);
        } இல்லையெனில் எனில் (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_SHIFT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } இல்லையெனில் {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    எனில் (viddata->keyboard.locked_modifiers & ControlMask) {
        எனில் (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } இல்லையெனில் எனில் (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } இல்லையெனில் {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    எனில் (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_mask) {
        எனில் (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } இல்லையெனில் எனில் (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } இல்லையெனில் {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    எனில் (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_mask) {
        எனில் (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } இல்லையெனில் எனில் (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } இல்லையெனில் {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    எனில் (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_MODE;
    } இல்லையெனில் {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_MODE;
    }

    எனில் (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } இல்லையெனில் {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    எனில் (viddata->keyboard.locked_modifiers & LockMask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } இல்லையெனில் {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    எனில் (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_இலக்கம்;
    } இல்லையெனில் {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_இலக்கம்;
    }

    எனில் (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } இல்லையெனில் {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_SetModState(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

நிலையான வெறுமை X11_Handle_Modifier_சாவிகள்(SDL_VideoData *viddata, SDL_Scancode scancode, bool pressed)
{
    மாறிலி SDL_Keycode keycode = SDL_Get_சாவி_From_Scancode(scancode, SDL_KMOD_NONE, false);
    SDL_Keymod mod = SDL_KMOD_NONE;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is checked.
     */
    தேர்வு (keycode) {
    நிலை SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        நிறுத்து;
    நிலை SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        நிறுத்து;
    நிலை SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        நிறுத்து;
    நிலை SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        நிறுத்து;
    நிலை SDLK_LALT:
        mod = SDL_KMOD_LALT;
        நிறுத்து;
    நிலை SDLK_RALT:
        mod = SDL_KMOD_RALT;
        நிறுத்து;
    நிலை SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        நிறுத்து;
    நிலை SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        நிறுத்து;
    நிலை SDLK_MODE:
        mod = SDL_KMOD_MODE;
        நிறுத்து;
    நிலை SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        நிறுத்து;
    நிலை SDLK_CAPSLOCK:
    நிலை SDLK_NUMLOCKCLEAR:
    நிலை SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        எனில் (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            unsigned முழு cur_mask = viddata->keyboard.locked_modifiers;
            X11_Update_System_சாவி_Modifiers(viddata);

            எனில் (viddata->keyboard.locked_modifiers & LockMask) {
                cur_mask |= LockMask;
            } இல்லையெனில் {
                cur_mask &= ~LockMask;
            }
            எனில் (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
                cur_mask |= viddata->keyboard.numlock_mask;
            } இல்லையெனில் {
                cur_mask &= ~viddata->keyboard.numlock_mask;
            }
            எனில் (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
                cur_mask |= viddata->keyboard.scrolllock_mask;
            } இல்லையெனில் {
                cur_mask &= ~viddata->keyboard.scrolllock_mask;
            }

            viddata->keyboard.locked_modifiers = cur_mask;
        }
    } நிறுத்து;
    இயல்பு:
        திரும்பு;
    }

    எனில் (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } இல்லையெனில் {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

வெறுமை X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    எழுத்து சாவிகள்[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_சாவி_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_இலக்கம் | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= LockMask | videodata->keyboard.numlock_mask| videodata->keyboard.scrolllock_mask;

    X11_XQueryKeymap(display, சாவிகள்);

    மாறிலி bool *keystate = SDL_GetKeyboardState(வெற்று);
    க்கு (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.சாவி_layout); ++keycode) {
        மாறிலி SDL_Scancode scancode = videodata->keyboard.சாவி_layout[keycode];
        மாறிலி bool x11_சாவி_Pressed = (சாவிகள்[keycode / 8] & (1 << (keycode % 8))) != 0;
        மாறிலி bool sdl_சாவி_Pressed = keystate[scancode];

        எனில் (x11_சாவி_Pressed && !sdl_சாவி_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            தேர்வு (SDL_Get_சாவி_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            நிலை SDLK_LCTRL:
            நிலை SDLK_RCTRL:
            நிலை SDLK_LSHIFT:
            நிலை SDLK_RSHIFT:
            நிலை SDLK_LALT:
            நிலை SDLK_RALT:
            நிலை SDLK_LGUI:
            நிலை SDLK_RGUI:
            நிலை SDLK_MODE:
            நிலை SDLK_LEVEL5_SHIFT:
                X11_Handle_Modifier_சாவிகள்(videodata, scancode, true);
                SDL_Send_Keyboard_சாவி_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                நிறுத்து;
            இயல்பு:
                நிறுத்து;
            }
        } இல்லையெனில் எனில் (!x11_சாவி_Pressed && sdl_சாவி_Pressed) {
            X11_Handle_Modifier_சாவிகள்(videodata, scancode, false);
            SDL_Send_Keyboard_சாவி_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_சாவி_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

நிலையான வெறுமை X11_DispatchFocusIn(SDL_VideoDevice *_this, SDL_WindowData *data)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", data->xwindow);
#endif
    SDL_SetKeyboardFocus(data->window);
    X11_ReconcileKeyboardState(_this);
#ifdef X_HAVE_UTF8_STRING
    எனில் (data->ic) {
        X11_XSetICFocus(data->ic);
    }
#endif
    எனில் (data->flashing_window) {
        X11_FlashWindow(_this, data->window, SDL_FLASH_CANCEL);
    }
}

நிலையான வெறுமை X11_DispatchFocusOut(SDL_VideoDevice *_this, SDL_WindowData *data)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", data->xwindow);
#endif
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    எனில் (data->window == SDL_GetKeyboardFocus()) {
        SDL_SetKeyboardFocus(வெற்று);
    }
#ifdef X_HAVE_UTF8_STRING
    எனில் (data->ic) {
        X11_XUnsetICFocus(data->ic);
    }
#endif
}

நிலையான வெறுமை X11_DispatchMapNotify(SDL_WindowData *data)
{
    SDL_Window *window = data->window;

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    data->was_shown = true;

    // This may be sent when restoring a minimized window.
    எனில் (window->flags & SDL_WINDOW_MINIMIZED) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }

    எனில் (window->flags & SDL_WINDOW_உள்ளீடு_FOCUS) {
        SDL_UpdateWindowGrab(window);
    }
}

நிலையான வெறுமை X11_DispatchUnmapNotify(SDL_WindowData *data)
{
    SDL_Window *window = data->window;

    // This may be sent when minimizing a window.
    எனில் (!window->is_hiding) {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
    } இல்லையெனில் {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    }
}

நிலையான வெறுமை DispatchWindowMove(SDL_VideoDevice *_this, மாறிலி SDL_WindowData *data, மாறிலி SDL_Point *point)
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
    X11_XSendEvent(display, Default_வேர்_Window(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

நிலையான வெறுமை ScheduleWindowMove(SDL_VideoDevice *_this, SDL_WindowData *data, மாறிலி SDL_Point *point)
{
    data->pending_move = true;
    data->pending_move_point = *point;
}

நிலையான வெறுமை InitiateWindowResize(SDL_VideoDevice *_this, மாறிலி SDL_WindowData *data, மாறிலி SDL_Point *point, முழு direction)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_Window *window = data->window;
    Display *display = videodata->display;
    XEvent evt;

    எனில் (direction < _NET_WM_MOVERESIZE_SIZE_TOPLEFT || direction > NET_WM_MOVERESIZE_SIZE_இடது) {
        திரும்பு;
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
    X11_XSendEvent(display, Default_வேர்_Window(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_WindowData *data, மாறிலி தசம x, மாறிலி தசம y, bool force_new_result)
{
    SDL_Window *window = data->window;
    எனில் (!window->hit_test) திரும்பு false;
    மாறிலி SDL_Point point = { (முழு)x, (முழு)y };
    SDL_HitTestResult rc = window->hit_test(window, &point, window->hit_test_data);
    எனில் (!force_new_result && rc == data->hit_test_result) {
        திரும்பு true;
    }
    X11_SetHitTestCursor(rc);
    data->hit_test_result = rc;
    திரும்பு true;
}

bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_WindowData *data, மாறிலி தசம x, மாறிலி தசம y)
{
    SDL_Window *window = data->window;

    எனில் (window->hit_test) {
        மாறிலி SDL_Point point = { (முழு)x, (முழு)y };
        நிலையான மாறிலி முழு directions[] = {
            _NET_WM_MOVERESIZE_SIZE_TOPLEFT, NET_WM_MOVERESIZE_SIZE_உச்சி,
            _NET_WM_MOVERESIZE_SIZE_TOPRIGHT, NET_WM_MOVERESIZE_SIZE_வலது,
            _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT, _NET_WM_MOVERESIZE_SIZE_BOTTOM,
            _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT, NET_WM_MOVERESIZE_SIZE_இடது
        };

        தேர்வு (data->hit_test_result) {
        நிலை SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            எனில் (data->window->flags & SDL_WINDOW_உள்ளீடு_FOCUS) {
                DispatchWindowMove(_this, data, &point);
            } இல்லையெனில் {
                ScheduleWindowMove(_this, data, &point);
            }
            திரும்பு true;

        நிலை SDL_HITTEST_RESIZE_TOPLEFT:
        நிலை SDL_HITTEST_RESIZE_உச்சி:
        நிலை SDL_HITTEST_RESIZE_TOPRIGHT:
        நிலை SDL_HITTEST_RESIZE_வலது:
        நிலை SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        நிலை SDL_HITTEST_RESIZE_BOTTOM:
        நிலை SDL_HITTEST_RESIZE_BOTTOMLEFT:
        நிலை SDL_HITTEST_RESIZE_இடது:
            InitiateWindowResize(_this, data, &point, directions[data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
            திரும்பு true;

        இயல்பு:
            திரும்பு false;
        }
    }

    திரும்பு false;
}

நிலையான வெறுமை X11_UpdateUserTime(SDL_WindowData *data, மாறிலி unsigned long latest)
{
    எனில் (latest && (latest != data->user_time)) {
        SDL_VideoData *videodata = data->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, data->xwindow, videodata->atoms._NET_WM_USER_TIME,
                            XA_CARDINAL, 32, PropModeReplace,
                            (மாறிலி unsigned எழுத்து *)&latest, 1);
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", data->xwindow, latest);
#endif
        data->user_time = latest;
    }
}

நிலையான unsigned எழுத்து x11_last_error;
நிலையான முழு BadWindowErrorHandler(Display *d, XErrorEvent *e)
{
    x11_last_error = e->error_code;

    // Ignore BadWindow in cases where it's not fatal.
    எனில் (e->error_code != BadWindow) {
        எழுத்து err_செய்தி[128];
        X11_XGetErrorText(d, e->error_code, err_செய்தி, அளவு(err_செய்தி));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_code, err_செய்தி, e->request_code);
    }
    திரும்பு 0;
}

நிலையான வெறுமை X11_HandleClipboardEvent(SDL_VideoDevice *_this, மாறிலி XEvent *xevent)
{
    முழு i;
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_window != None);
    SDL_assert(xevent->xany.window == videodata->clipboard_window);

    தேர்வு (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    நிலை SelectionRequest:
    {
        மாறிலி XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        முழு mime_formats;
        unsigned எழுத்து *seln_data;
        size_t seln_length = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_ClipboardData *clipboard;

#ifdef DEBUG_XEVENTS
        எழுத்து *atom_name;
        atom_name = X11_XGetAtomName(display, req->target);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->target, atom_name);
        எனில் (atom_name) {
            X11_XFree(atom_name);
        }
#endif

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_last_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

        எனில் (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } இல்லையெனில் {
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

        எனில் (req->target == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_மொத்தம் + 1) * அளவு(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            க்கு (i = 0; i < clipboard->mime_மொத்தம்; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, PropModeReplace,
                                (unsigned எழுத்து *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.target = XA_TARGETS;
            SDL_free(supportedFormats);
        } இல்லையெனில் {
            எனில் (clipboard->callback) {
                க்கு (i = 0; i < clipboard->mime_மொத்தம்; ++i) {
                    மாறிலி எழுத்து *mime_type = clipboard->mime_types[i];
                    எனில் (X11_XInternAtom(display, mime_type, False) != req->target) {
                        தொடர்;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_data = (unsigned எழுத்து *)clipboard->callback(clipboard->userdata, mime_type, &seln_length);
                    எனில் (seln_data) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->target, 8, PropModeReplace,
                                            seln_data, seln_length);
                        sevent.xselection.property = req->property;
                        sevent.xselection.target = req->target;
                    }
                    நிறுத்து;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(prev_handler);
    } நிறுத்து;

    நிலை SelectionNotify:
    {
        மாறிலி XSelectionEvent *xsel = &xevent->xselection;
#ifdef DEBUG_XEVENTS
        மாறிலி எழுத்து *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        மாறிலி எழுத்து *targetName = xsel->target ? X11_XGetAtomName(display, xsel->target) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, targetName, propName);
#endif
        எனில் (xsel->target == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            unsigned எழுத்து *data = வெற்று;
            முழு format_property = 0;
            unsigned long length = 0;
            unsigned long bytes_இடது = 0;
            முழு j;

            X11_XGetWindowProperty(display, GetWindow(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &length, &bytes_இடது, &data);

            முழு allocationsize = (length + 1) * அளவு(எழுத்து *);
            க்கு (j = 0, patom = (Atom *)data; j < length; j++, patom++) {
                எழுத்து *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            எழுத்து **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
            எனில் (new_mime_types) {
                எழுத்து *strPtr = (எழுத்து *)(new_mime_types + length + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                க்கு (j = 0, patom = (Atom *)data; j < length; j++, patom++) {
                    எழுத்து *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    மாறிலி size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[length] = வெற்று;

                SDL_SendClipboardUpdate(false, new_mime_types, length);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            எனில் (data) {
                X11_XFree(data);
            }
        }

        videodata->selection_waiting = false;
    } நிறுத்து;

    நிலை SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_ClipboardData *clipboard = வெற்று;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.target);
#endif

        எனில் (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } இல்லையெனில் எனில் (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        எனில் (clipboard && clipboard->callback) {
            எனில் (clipboard->sequence) {
                SDL_CancelClipboardData(clipboard->sequence);
            } இல்லையெனில் {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } நிறுத்து;

    நிலை PropertyNotify:
    {
        எழுத்து *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        எனில் (SDL_strncmp(name_of_atom, "SDL_SELECTION", அளவு("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_மதிப்பு) {
            videodata->selection_incr_waiting = false;
        }

        எனில் (name_of_atom) {
            X11_XFree(name_of_atom);
        }
    } நிறுத்து;
    }
}

நிலையான Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    திரும்பு ev->type == MapNotify &&
           ev->xmap.window == unmap->window &&
           ev->xmap.serial == unmap->serial;
}

நிலையான Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    திரும்பு ev->type == ReparentNotify &&
           ev->xreparent.window == unmap->window &&
           ev->xreparent.serial == unmap->serial;
}

நிலையான bool Is_உயர்வு_Latin1(மாறிலி எழுத்து *string, முழு length)
{
    போது (length-- > 0) {
        Uint8 ch = (Uint8)*string;
        எனில் (ch >= 0x80) {
            திரும்பு true;
        }
        ++string;
    }
    திரும்பு false;
}

நிலையான முழு XLookupStringAsUTF8(XKeyEvent *event_struct, எழுத்து *buffer_return, முழு bytes_buffer, சாவி_Sym *keysym_return, XComposeStatus *status_in_out)
{
    முழு result = X11_XLookupString(event_struct, buffer_return, bytes_buffer, keysym_return, status_in_out);
    எனில் (Is_உயர்வு_Latin1(buffer_return, result)) {
        எழுத்து *utf8_text = SDL_iconv_string("UTF-8", "ISO-8859-1", buffer_return, result + 1);
        எனில் (utf8_text) {
            SDL_strlcpy(buffer_return, utf8_text, bytes_buffer);
            SDL_free(utf8_text);
            திரும்பு SDL_strlen(buffer_return);
        } இல்லையெனில் {
            திரும்பு 0;
        }
    }
    திரும்பு result;
}

SDL_WindowData *X11_FindWindow(SDL_VideoData *videodata, Window window)
{
    எனில் (videodata && videodata->windowlist) {
        க்கு (முழு i = 0; i < videodata->numwindows; ++i) {
            எனில் ((videodata->windowlist[i] != வெற்று) &&
                (videodata->windowlist[i]->xwindow == window)) {
                திரும்பு videodata->windowlist[i];
            }
        }
    }
    திரும்பு வெற்று;
}

Uint64 X11_GetEventTimestamp(unsigned long time)
{
    // FIXME: Get the event time in the SDL tick time base
    திரும்பு SDL_GetTicksNS();
}

வெறுமை X11_Handle_சாவி_Event(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    சாவி_Code_2 keycode = xevent->xkey.keycode;
    சாவி_Sym keysym = No_குறியீடு;
    முழு text_length = 0;
    எழுத்து text[64];
    Status status = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == சாவி_Press);
    SDL_Scancode scancode = videodata->keyboard.சாவி_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.window, (xevent->type == சாவி_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#endif
#ifdef DEBUG_SCANCODES
    எனில் (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        முழு min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_சாவி_Code_To_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysymToString(keysym));
    }
#endif // DEBUG SCANCODES

    text[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    எனில் (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (LockMask | videodata->keyboard.numlock_mask | videodata->keyboard.scrolllock_mask);
    }

    எனில் (SDL_Text_உள்ளீடு_Active(windowdata->window)) {
        // filter events catches XIM events and sends them to the correct handler
        எனில் (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            handled_by_ime = true;
        }

        எனில் (!handled_by_ime) {
#ifdef X_HAVE_UTF8_STRING
            எனில் (windowdata->ic && xevent->type == சாவி_Press) {
                text_length = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, text, அளவு(text) - 1,
                                      &keysym, &status);
            } இல்லையெனில் {
                text_length = XLookupStringAsUTF8(&xevent->xkey, text, அளவு(text) - 1, &keysym, வெற்று);
            }
#இல்லையெனில்
            text_length = XLookupStringAsUTF8(&xevent->xkey, text, அளவு(text) - 1, &keysym, வெற்று);
#endif
        }
    }

    எனில் (!handled_by_ime) {
        எனில் (pressed) {
            X11_Handle_Modifier_சாவிகள்(videodata, scancode, true);
            SDL_Send_Keyboard_சாவி_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            எனில் (*text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                text[text_length] = '\0';
                X11_ClearComposition(windowdata);
                SDL_SendKeyboardText(text);
            }
        } இல்லையெனில் {
            எனில் (X11_சாவி_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                திரும்பு;
            }

            X11_Handle_Modifier_சாவிகள்(videodata, scancode, false);
            SDL_Send_Keyboard_சாவி_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    எனில் (pressed) {
        X11_UpdateUserTime(windowdata, xevent->xkey.time);
    }
}

வெறுமை X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, முழு button, தசம x, தசம y, unsigned long time, unsigned long serial)
{
    SDL_Window *window = windowdata->window;
    முழு xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#endif

    SDL_Mouse *mouse = SDL_GetMouse();
    எனில் (!mouse->relative_mode && (x != mouse->x || y != mouse->y)) {
        X11_ProcessHitTest(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, window, mouseID, false, x, y);
    }

    எனில் (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, window, mouseID, (தசம)-xticks, (தசம)yticks, SDL_MOUSEWHEEL_NORMAL);
    } இல்லையெனில் {
        எனில் (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        எனில் (button == Button1) {
            எனில் (X11_TriggerHitTestAction(_this, windowdata, x, y)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0);
                திரும்பு; // don't pass this event on to app.
            }
        }
        எனில் (windowdata->last_focus_event_time) {
            மாறிலி முழு X11_FOCUS_CLICK_TIMEOUT = 10;
            எனில் (SDL_GetTicks() < (windowdata->last_focus_event_time + X11_FOCUS_CLICK_TIMEOUT)) {
                எனில் (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->last_focus_event_time = 0;
        }
        எனில் (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, window, mouseID, button, true);
        }
    }
    X11_UpdateUserTime(windowdata, time);
}

வெறுமை X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, முழு button, unsigned long time)
{
    SDL_Window *window = windowdata->window;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    முழு xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#endif
    எனில் (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        எனில் (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, window, mouseID, button, false);

        எனில் (window->internal->pending_grab) {
            X11_SetWindowMouseGrab(_this, window, true);
        }
    }
}

வெறுமை X11_Get_Border_மதிப்புகள்(SDL_WindowData *data)
{
    SDL_VideoData *videodata = data->videodata;
    Display *display = videodata->display;

    Atom type;
    முழு format;
    unsigned long nitems, bytes_after;
    unsigned எழுத்து *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    எனில் (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
        எனில் (X11_XGetWindowProperty(display, data->xwindow, videodata->atoms._NET_FRAME_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &bytes_after, &property) == Success) {
            எனில் (type != None && nitems == 4) {
                data->border_இடது = (முழு)((long *)property)[0];
                data->border_வலது = (முழு)((long *)property)[1];
                data->border_உச்சி = (முழு)((long *)property)[2];
                data->border_bottom = (முழு)((long *)property)[3];
            }
            X11_XFree(property);

#ifdef DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", data->border_இடது, data->border_வலது, data->border_உச்சி, data->border_bottom);
#endif
        }
    } இல்லையெனில் {
        data->border_இடது = data->border_உச்சி = data->border_வலது = data->border_bottom = 0;
    }
}

வெறுமை X11_EmitConfigureNotifyEvents(SDL_WindowData *data, XConfigureEvent *xevent)
{
    எனில் (!data->size_move_event_flags) {
        முழு x = xevent->x;
        முழு y = xevent->y;

        எனில் (xevent->x != data->last_xconfigure.x ||
            xevent->y != data->last_xconfigure.y) {
            data->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);

        க்கு (SDL_Window *w = data->window->first_child; w; w = w->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            எனில் (SDL_WINDOW_IS_POPUP(w) && !(w->flags & SDL_WINDOW_HIDDEN)) {
                X11_UpdateWindowPosition(w, true);
            }
        }

        எனில் (xevent->width != data->last_xconfigure.width ||
            xevent->height != data->last_xconfigure.height) {
            data->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, xevent->width, xevent->height);
    }

    SDL_copyp(&data->last_xconfigure, xevent);
}

நிலையான வெறுமை X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display;
    SDL_WindowData *data;
    XClientMessageEvent m;
    முழு i;

    SDL_assert(videodata != வெற்று);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    எனில் (xevent->type != சாவி_Press && xevent->type != சாவி_Release) {
        எனில் (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            திரும்பு;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    எனில் (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        திரும்பு;
    }
#endif

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    எனில் (g_X11EventHook) {
        எனில் (!g_X11EventHook(g_X11EventHookData, xevent)) {
            திரும்பு;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    எனில் (videodata->xrandr_event_base && (xevent->type == (videodata->xrandr_event_base + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#endif

#ifdef DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.window);
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    எனில் (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#endif

        எனில் (ev->subtype == XFixesSetSelectionOwnerNotify)
        {
            எனில் (ev->selection != videodata->atoms.CLIPBOARD)
                திரும்பு;

            எனில் (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_window)
                திரும்பு;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, GetWindow(_this), CurrentTime);
        }

        திரும்பு;
    }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES

    எனில் ((videodata->clipboard_window != None) &&
        (videodata->clipboard_window == xevent->xany.window)) {
        X11_HandleClipboardEvent(_this, xevent);
        திரும்பு;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    data = X11_FindWindow(videodata, xevent->xany.window);

    எனில் (!data) {
        // The window for KeymapNotify, etc events is 0
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        எனில் (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            தேர்வு (xkbevent->any.xkb_type) {
            நிலை XkbStateNotify:
            {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.window);
#endif
                எனில் ((xkbevent->state.changed & XkbGroupStateMask) && xkbevent->state.group != videodata->keyboard.xkb.current_group) {
                    videodata->keyboard.xkb.current_group = xkbevent->state.group;
                    SDL_SetKeymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_group], true);
                }

                எனில் (xkbevent->state.changed & XkbModifierStateMask) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.base_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } நிறுத்து;

            நிலை XkbMapNotify:
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.window);
                SDL_FALLTHROUGH;
#endif
            நிலை XkbNewKeyboardNotify:
            {
#ifdef DEBUG_XEVENTS
                எனில் (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.window);
                }
#endif
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                எனில் (xkbevent->any.serial != videodata->keyboard.xkb.last_map_serial) {
                    videodata->keyboard.xkb.last_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } நிறுத்து;

            இயல்பு:
                நிறுத்து;
            }
        } இல்லையெனில்
#endif
        எனில் (xevent->type == KeymapNotify) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.window);
#endif
            எனில் (SDL_GetKeyboardFocus() != வெற்று) {
                எனில் (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } இல்லையெனில் எனில் (xevent->type == MappingNotify) {
            மாறிலி முழு request = xevent->xmapping.request;

            எனில் (request == MappingPointer) {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                X11_Xinput2UpdatePointerMapping(_this);
            } இல்லையெனில் எனில் (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                எனில் (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } இல்லையெனில் எனில் (xevent->type == PropertyNotify && videodata) {
            எழுத்து *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            எனில் (name_of_atom) {
                எனில் (SDL_startswith(name_of_atom, "_ICC_PROFILE")) {
                    XWindowAttributes attrib;
                    முழு screennum;
                    க்கு (i = 0; i < videodata->numwindows; ++i) {
                        எனில் (videodata->windowlist[i] != வெற்று) {
                            data = videodata->windowlist[i];
                            X11_XGetWindowAttributes(display, data->xwindow, &attrib);
                            screennum = X11_XScreen_எண்_Of_Screen(attrib.screen);
                            எனில் (screennum == 0 && SDL_strcmp(name_of_atom, "_ICC_PROFILE") == 0) {
                                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                            } இல்லையெனில் எனில் (SDL_strncmp(name_of_atom, "_ICC_PROFILE_", அளவு("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_of_atom) > அளவு("_ICC_PROFILE_") - 1) {
                                முழு iccscreennum = SDL_atoi(&name_of_atom[அளவு("_ICC_PROFILE_") - 1]);

                                எனில் (screennum == iccscreennum) {
                                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                                }
                            }
                        }
                    }
                } இல்லையெனில் எனில் (SDL_strcmp(name_of_atom, "_NET_WORKAREA") == 0) {
                    க்கு (i = 0; i < _this->இலக்கம்_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
                    }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
                } இல்லையெனில் எனில் (SDL_strcmp(name_of_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_of_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#endif
                }
                X11_XFree(name_of_atom);
            }
        }
        திரும்பு;
    }

    தேர்வு (xevent->type) {

        // Gaining mouse coverage?
    நிலை EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        எனில் (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        எனில் (xevent->xcrossing.mode == NotifyUngrab) {
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
            எனில் ((data->pointer_barrier_active == true) && windowdata->window->flags & SDL_WINDOW_உள்ளீடு_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->window, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#endif

        எனில் (!mouse->relative_mode) {
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (தசம)xevent->xcrossing.x, (தசம)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        எனில் (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            SDL_UpdateWindowGrab(data->window);
        }

        X11_ProcessHitTest(_this, data, mouse->last_x, mouse->last_y, true);
    } நிறுத்து;
        // Losing mouse coverage?
    நிலை LeaveNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        எனில் (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        எனில் (xevent->xcrossing.mode == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#endif
        எனில் (!SDL_GetMouse()->relative_mode) {
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (தசம)xevent->xcrossing.x, (தசம)xevent->xcrossing.y);
        }

        எனில் (xevent->xcrossing.mode != NotifyGrab &&
            xevent->xcrossing.mode != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            எனில் (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                X11_SetWindowKeyboardGrab(_this, data->window, false);
            }

            SDL_SetMouseFocus(வெற்று);
        }
    } நிறுத்து;

        // Gaining input focus?
    நிலை FocusIn:
    {
        எனில் (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            நிறுத்து;
        }

        எனில் (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            நிறுத்து;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.window);
#endif
        எனில் (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            data->pending_focus = PENDING_FOCUS_NONE;
            data->pending_focus_time = 0;
            X11_DispatchFocusIn(_this, data);
        } இல்லையெனில் {
            data->pending_focus = PENDING_FOCUS_IN;
            data->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }
        data->last_focus_event_time = SDL_GetTicks();
    } நிறுத்து;

        // Losing input focus?
    நிலை FocusOut:
    {
        எனில் (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            நிறுத்து;
        }
        எனில் (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            நிறுத்து;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.window);
#endif
        எனில் (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            data->pending_focus = PENDING_FOCUS_NONE;
            data->pending_focus_time = 0;
            X11_DispatchFocusOut(_this, data);
        } இல்லையெனில் {
            data->pending_focus = PENDING_FOCUS_OUT;
            data->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        எனில் (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, வெற்று, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } நிறுத்து;


        // Have we been iconified?
    நிலை UnmapNotify:
    {
        XEvent ev;

#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.window);
#endif

        எனில் (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } இல்லையெனில் {
            X11_DispatchUnmapNotify(data);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        எனில் (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, வெற்று, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } நிறுத்து;

        // Have we been restored?
    நிலை MapNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.window);
#endif
        X11_DispatchMapNotify(data);

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        எனில் (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, &data->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } நிறுத்து;

        // Have we been resized or moved?
    நிலை ConfigureNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.window,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.width, xevent->xconfigure.height);
#endif
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        எனில் (!xevent->xconfigure.send_event) {
            unsigned முழு இலக்கம்_Children;
            Window ChildReturn, வேர்_2, Parent;
            Window *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_last_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

            X11_XQuery_மரம்(data->videodata->display, xevent->xconfigure.window, &வேர்_2, &Parent, &Children, &இலக்கம்_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      Parent, Default_வேர்_Window(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &ChildReturn);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            எனில் (x11_last_error == BadWindow) {
                நிறுத்து;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        மாறிலி SDL_WindowFlags changed = X11_GetNetWMState(_this, data->window, xevent->xproperty.window) ^ data->window->flags;
        எனில் (changed & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) {
            SDL_copyp(&data->pending_xconfigure, &xevent->xconfigure);
            data->emit_size_move_after_property_notify = true;
        }

        எனில் (!data->emit_size_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(data, &xevent->xconfigure);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(data->window, &xevent->xconfigure);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } நிறுத்து;

        // Have we been requested to quit (or another client message?)
    நிலை ClientMessage:
    {
        நிலையான முழு xdnd_version = 0;

        எனில் (xevent->xclient.message_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.data.l[1] & 1;
            data->xdnd_source = xevent->xclient.data.l[0];
            xdnd_version = (xevent->xclient.data.l[1] >> 24);
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", data->xdnd_source);
            SDL_Log("Protocol version to use : %d", xdnd_version);
            SDL_Log("More then 3 data types : %d", (முழு)use_list);
#endif

            எனில் (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, data->xdnd_source, videodata->atoms.XdndTypeList);
                // pick one
                data->xdnd_req = X11_PickTarget(display, (Atom *)p.data, p.மொத்தம்);
                X11_XFree(p.data);
            } இல்லையெனில் {
                // pick from list of three
                data->xdnd_req = X11_PickTargetFromAtoms(display, xevent->xclient.data.l[2], xevent->xclient.data.l[3], xevent->xclient.data.l[4]);
            }
        } இல்லையெனில் எனில் (xevent->xclient.message_type == videodata->atoms.XdndLeave) {
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.data.l[0]);
#endif
            SDL_SendDropComplete(data->window);
        } இல்லையெனில் எனில் (xevent->xclient.message_type == videodata->atoms.XdndPosition) {

#ifdef DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            எனில் (xdnd_version >= 2) {
                act = xevent->xclient.data.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#endif
            {
                // Drag and Drop position
                முழு வேர்_x, வேர்_y, window_x, window_y;
                Window ChildReturn;
                வேர்_x = xevent->xclient.data.l[2] >> 16;
                வேர்_y = xevent->xclient.data.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_வேர்_Window(display), data->xwindow,
                                          வேர்_x, வேர்_y, &window_x, &window_y, &ChildReturn);

                SDL_SendDropPosition(data->window, (தசம)window_x, (தசம)window_y);
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
        } இல்லையெனில் எனில் (xevent->xclient.message_type == videodata->atoms.XdndDrop) {
            எனில் (data->xdnd_req == None) {
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
            } இல்லையெனில் {
                // convert
                எனில் (xdnd_version >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, data->xdnd_req, videodata->atoms.PRIMARY, data->xwindow, xevent->xclient.data.l[2]);
                } இல்லையெனில் {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, data->xdnd_req, videodata->atoms.PRIMARY, data->xwindow, CurrentTime);
                }
            }
        } இல்லையெனில் எனில் ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.data.l[0] == videodata->atoms._NET_WM_PING)) {
            Window வேர் = Default_வேர்_Window(display);

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.window);
#endif
            xevent->xclient.window = வேர்;
            X11_XSendEvent(display, வேர், False, SubstructureRedirectMask | SubstructureNotifyMask, xevent);
            நிறுத்து;
        }

        இல்லையெனில் எனில் ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.data.l[0] == videodata->atoms.WM_DELETE_WINDOW)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.window);
#endif
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            நிறுத்து;
        } இல்லையெனில் எனில் ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.data.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", data);
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(data->window, &xevent->xclient);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
            நிறுத்து;
        }
    } நிறுத்து;

        // Do we need to refresh ourselves?
    நிலை Expose:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.window, xevent->xexpose.மொத்தம்);
#endif
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    } நிறுத்து;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    நிலை சாவி_Press:
    நிலை சாவி_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        எனில் (data->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            நிறுத்து;
        } இல்லையெனில் எனில் (xevent->xkey.serial == videodata->xinput_last_சாவி_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_last_keyboard_device;
        }

        X11_Handle_சாவி_Event(_this, data, keyboardID, xevent);
    } நிறுத்து;

    நிலை MotionNotify:
    {
        எனில் (X11_Xinput2HandlesMotionForWindow(data)) {
            // This input is being handled by XInput2
            நிறுத்து;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        எனில் (!mouse->relative_mode) {
#ifdef DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.window, xevent->xmotion.x, xevent->xmotion.y);
#endif

            X11_ProcessHitTest(_this, data, (தசம)xevent->xmotion.x, (தசம)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (தசம)xevent->xmotion.x, (தசம)xevent->xmotion.y);
        }
    } நிறுத்து;

    நிலை ButtonPress:
    {
        எனில் (data->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            நிறுத்து;
        }

        X11_HandleButtonPress(_this, data, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.time, xevent->xbutton.serial);
    } நிறுத்து;

    நிலை ButtonRelease:
    {
        எனில் (data->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            நிறுத்து;
        }

        X11_HandleButtonRelease(_this, data, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.time);
    } நிறுத்து;

    நிலை PropertyNotify:
    {
#ifdef DEBUG_XEVENTS
        unsigned எழுத்து *propdata;
        முழு status, real_format;
        Atom real_type;
        unsigned long பொருட்கள்_read, பொருட்கள்_இடது;

        எழுத்து *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        எனில் (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.window, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.time);
            X11_XFree(name);
        }

        status = X11_XGetWindowProperty(display, data->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &பொருட்கள்_read, &பொருட்கள்_இடது, &propdata);
        எனில் (status == Success && பொருட்கள்_read > 0) {
            எனில் (real_type == XA_INTEGER) {
                முழு *மதிப்புகள் = (முழு *)propdata;

                SDL_Log("{");
                க்கு (i = 0; i < பொருட்கள்_read; i++) {
                    SDL_Log(" %d", மதிப்புகள்[i]);
                }
                SDL_Log(" }");
            } இல்லையெனில் எனில் (real_type == XA_CARDINAL) {
                எனில் (real_format == 32) {
                    Uint32 *மதிப்புகள் = (Uint32 *)propdata;

                    SDL_Log("{");
                    க்கு (i = 0; i < பொருட்கள்_read; i++) {
                        SDL_Log(" %d", மதிப்புகள்[i]);
                    }
                    SDL_Log(" }");
                } இல்லையெனில் எனில் (real_format == 16) {
                    Uint16 *மதிப்புகள் = (Uint16 *)propdata;

                    SDL_Log("{");
                    க்கு (i = 0; i < பொருட்கள்_read; i++) {
                        SDL_Log(" %d", மதிப்புகள்[i]);
                    }
                    SDL_Log(" }");
                } இல்லையெனில் எனில் (real_format == 8) {
                    Uint8 *மதிப்புகள் = (Uint8 *)propdata;

                    SDL_Log("{");
                    க்கு (i = 0; i < பொருட்கள்_read; i++) {
                        SDL_Log(" %d", மதிப்புகள்[i]);
                    }
                    SDL_Log(" }");
                }
            } இல்லையெனில் எனில் (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } இல்லையெனில் எனில் (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                க்கு (i = 0; i < பொருட்கள்_read; i++) {
                    எழுத்து *atomname = X11_XGetAtomName(display, atoms[i]);
                    எனில் (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } இல்லையெனில் {
                எழுத்து *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                எனில் (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        எனில் (status == Success) {
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
        எனில் (!data->user_time) {
            data->user_time = xevent->xproperty.time;
        }

        எனில் (xevent->xproperty.atom == data->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            மாறிலி SDL_WindowFlags flags = X11_GetNetWMState(_this, data->window, xevent->xproperty.window);
            மாறிலி SDL_WindowFlags changed = flags ^ data->window->flags;

            எனில் ((changed & SDL_WINDOW_HIDDEN) && !(flags & SDL_WINDOW_HIDDEN)) {
                X11_DispatchMapNotify(data);
            }

            எனில் (!SDL_WINDOW_IS_POPUP(data->window)) {
                எனில் (changed & SDL_WINDOW_FULLSCREEN) {
                    data->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    எனில் (flags & SDL_WINDOW_FULLSCREEN) {
                        எனில் (!(flags & SDL_WINDOW_MINIMIZED)) {
                            மாறிலி bool commit = SDL_memcmp(&data->window->current_fullscreen_mode, &data->requested_fullscreen_mode, அளவு(SDL_DisplayMode)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                            எனில் (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&data->window->current_fullscreen_mode, &data->window->requested_fullscreen_mode);
                                SDL_UpdateFullscreenMode(data->window, SDL_FULLSCREEN_OP_UPDATE, true);
                            } இல்லையெனில் {
                                SDL_UpdateFullscreenMode(data->window, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } இல்லையெனில் {
                        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                        SDL_UpdateFullscreenMode(data->window, false, false);

                        SDL_zero(data->requested_fullscreen_mode);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_SetWindowMinMax(data->window, !!(flags & SDL_WINDOW_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        எனில் (data->fullscreen_borders_forced_on) {
                            data->toggle_borders = true;
                            data->fullscreen_borders_forced_on = false;
                        }
                    }

                    எனில் ((flags & SDL_WINDOW_FULLSCREEN) &&
                        (data->border_உச்சி || data->border_இடது || data->border_bottom || data->border_வலது)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        data->size_move_event_flags |= X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        data->previous_borders_nonzero = true;
                    } இல்லையெனில் எனில் (!(flags & SDL_WINDOW_FULLSCREEN) &&
                               data->previous_borders_nonzero &&
                               (!data->border_உச்சி && !data->border_இடது && !data->border_bottom && !data->border_வலது)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        data->size_move_event_flags |= X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        data->previous_borders_nonzero = false;
                    } இல்லையெனில் {
                        data->size_move_event_flags = 0;
                        data->previous_borders_nonzero = false;

                        எனில் (!(data->window->flags & SDL_WINDOW_FULLSCREEN) && data->toggle_borders) {
                            data->toggle_borders = false;
                            X11_SetWindowBordered(_this, data->window, !(data->window->flags & SDL_WINDOW_BORDERLESS));
                        }
                    }
                }
                எனில் ((changed & SDL_WINDOW_MAXIMIZED) && ((flags & SDL_WINDOW_MAXIMIZED) && !(flags & SDL_WINDOW_MINIMIZED))) {
                    data->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    எனில் ((changed & SDL_WINDOW_MINIMIZED)) {
                        data->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                    }
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
                }
                எனில் ((changed & SDL_WINDOW_MINIMIZED) && (flags & SDL_WINDOW_MINIMIZED)) {
                    data->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                }
                எனில் (!(flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
                    data->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    எனில் (!(flags & SDL_WINDOW_FULLSCREEN)) {
                        எனில் (data->pending_position) {
                            data->pending_position = false;
                            data->pending_operation |= X11_PENDING_OP_MOVE;
                            data->expected.x = data->window->pending.x - data->border_இடது;
                            data->expected.y = data->window->pending.y - data->border_உச்சி;
                            X11_XMoveWindow(display, data->xwindow, data->expected.x, data->expected.y);
                        }
                        எனில் (data->pending_size) {
                            data->pending_size = false;
                            data->pending_operation |= X11_PENDING_OP_RESIZE;
                            data->expected.w = data->window->pending.w;
                            data->expected.h = data->window->pending.h;
                            X11_XResizeWindow(display, data->xwindow, data->window->pending.w, data->window->pending.h);
                        }
                    }
                }
                எனில் (data->emit_size_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(data, &data->pending_xconfigure);
                    data->emit_size_move_after_property_notify = false;
                }
                எனில் ((flags & SDL_WINDOW_உள்ளீடு_FOCUS)) {
                    எனில் (data->pending_move) {
                        DispatchWindowMove(_this, data, &data->pending_move_point);
                        data->pending_move = false;
                    }
                }
            }
            எனில் (changed & SDL_WINDOW_OCCLUDED) {
                SDL_SendWindowEvent(data->window, (flags & SDL_WINDOW_OCCLUDED) ? SDL_EVENT_WINDOW_OCCLUDED : SDL_EVENT_WINDOW_EXPOSED, 0, 0);
            }
        } இல்லையெனில் எனில் (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            முழு format;
            unsigned long nitems, bytes_after;
            unsigned எழுத்து *prop_data = வெற்று;

            எனில் (X11_XGetWindowProperty(display, data->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &bytes_after, &prop_data) == Success) {
                எனில் (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_data;

                    எனில் ((state == 0 || state == 3) && !data->window->is_hiding && !(data->window->flags & SDL_WINDOW_HIDDEN)) {
                        // Withdrawn or Iconic
                        எனில் (!(data->window->flags & SDL_WINDOW_MINIMIZED)) {
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
                        }
                    } இல்லையெனில் எனில் (state == 1) { // NormalState
                        எனில் (data->window->flags & SDL_WINDOW_MINIMIZED) {
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_data);
            }
        } இல்லையெனில் எனில் (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } இல்லையெனில் எனில் (xevent->xproperty.atom == videodata->atoms._NET_FRAME_EXTENTS) {
            X11_Get_Border_மதிப்புகள்(data);
            எனில் (data->size_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                data->size_move_event_flags &= ~X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            எனில் (!(data->window->flags & SDL_WINDOW_FULLSCREEN) && data->toggle_borders) {
                data->toggle_borders = false;
                X11_SetWindowBordered(_this, data->window, !(data->window->flags & SDL_WINDOW_BORDERLESS));
            }
        }
    } நிறுத்து;

    நிலை SelectionNotify:
    {
        Atom target = xevent->xselection.target;
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.window,
               xevent->xselection.requestor, xevent->xselection.target);
#endif
        எனில் (target == data->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, data->xwindow, videodata->atoms.PRIMARY);

            எனில் (p.format == 8) {
                எழுத்து *saveptr = வெற்று;
                எழுத்து *name = X11_XGetAtomName(display, target);
                எனில் (name) {
                    எழுத்து *token = SDL_strtok_r((எழுத்து *)p.data, "\r\n", &saveptr);
                    போது (token) {
                        எனில் ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_SendDropText(data->window, token);
                        } இல்லையெனில் எனில் (SDL_strcmp("text/uri-list", name) == 0) {
                            எனில் (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(data->window, வெற்று, token);
                            }
                        }
                        token = SDL_strtok_r(வெற்று, "\r\n", &saveptr);
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
    } நிறுத்து;

    இயல்பு:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.window, xevent->type);
#endif
    } நிறுத்து;
    }
}

நிலையான வெறுமை X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    முழு i;

    எனில் (videodata && videodata->windowlist) {
        க்கு (i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *data = videodata->windowlist[i];
            எனில் (data && data->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                எனில் (now >= data->pending_focus_time) {
                    எனில் (data->pending_focus == PENDING_FOCUS_IN) {
                        X11_DispatchFocusIn(_this, data);
                    } இல்லையெனில் {
                        X11_DispatchFocusOut(_this, data);
                    }
                    data->pending_focus = PENDING_FOCUS_NONE;
                }
            }
        }
    }
}

நிலையான Bool isAnyEvent(Display *display, XEvent *ev, XPointer arg)
{
    திரும்பு True;
}

நிலையான bool X11_PollEvent(Display *display, XEvent *event)
{
    எனில் (!X11_XCheckIfEvent(display, event, isAnyEvent, வெற்று)) {
        திரும்பு false;
    }

    திரும்பு true;
}

வெறுமை X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
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

முழு X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    எனில் (X11_PollEvent(display, &xevent)) {
        // Fall through
    } இல்லையெனில் எனில் (timeoutNS == 0) {
        திரும்பு 0;
    } இல்லையெனில் {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        முழு err = SDL_IOReady(Connection_எண்(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        எனில் (err > 0) {
            எனில் (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                திரும்பு 1;
            }
        } இல்லையெனில் எனில் (err == 0) {
            // Timeout
            திரும்பு 0;
        } இல்லையெனில் {
            // Error returned from poll()/select()

            எனில் (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                திரும்பு 1;
            } இல்லையெனில் {
                திரும்பு err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    திரும்பு 1;
}

வெறுமை X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    XEvent xevent;
    முழு i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    க்கு (i = 0; i < _this->இலக்கம்_displays; ++i) {
        எனில் (_this->displays[i]->internal->mode_switch_deadline_ns) {
            எனில் (_this->displays[i]->fullscreen_window) {
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            } இல்லையெனில் எனில் (SDL_GetTicksNS() >= _this->displays[i]->internal->mode_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_SetDisplayModeForDisplay(_this->displays[i], வெற்று);
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            }
        }
    }

    எனில் (data->last_mode_change_deadline) {
        எனில் (SDL_GetTicks() >= data->last_mode_change_deadline) {
            data->last_mode_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    எனில் (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        எனில் (!data->screensaver_activity || now >= (data->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(data->display);

#ifdef SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#endif

            data->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    போது (X11_PollEvent(data->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    க்கு (i = 0; i < data->numwindows; ++i) {
        எனில் (data->windowlist[i] != வெற்று &&
            data->windowlist[i]->flash_cancel_time &&
            SDL_GetTicks() >= data->windowlist[i]->flash_cancel_time) {
            X11_FlashWindow(_this, data->windowlist[i]->window, SDL_FLASH_CANCEL);
        }
    }

    எனில் (data->xinput_hierarchy_changed) {
        X11_Xinput2UpdateDevices(_this);
        data->xinput_hierarchy_changed = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_VideoData *data = _this->internal;
    முழு dummy;
    முழு major_version, minor_version;
#endif // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#ifdef SDL_USE_LIBDBUS
    எனில் (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        திரும்பு true;
    }

    எனில் (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    எனில் (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        எனில் (!X11_XScreenSaverQueryExtension(data->display, &dummy, &dummy) ||
            !X11_XScreenSaverQueryVersion(data->display,
                                          &major_version, &minor_version) ||
            major_version < 1 || (major_version == 1 && minor_version < 1)) {
            திரும்பு SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(data->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(data->display);
        திரும்பு true;
    }
#endif
    திரும்பு SDL_Unsupported();
}

#endif // SDL_VIDEO_DRIVER_X11
