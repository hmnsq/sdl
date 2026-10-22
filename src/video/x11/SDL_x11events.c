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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#अन्तर्भाव <sys/types.h>
#अन्तर्भाव <sys/time.h>
#अन्तर्भाव <signal.h>
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <limits.h> // For INT_MAX

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11pen.h"
#अन्तर्भाव "SDL_x11touch.h"
#अन्तर्भाव "SDL_x11xinput2.h"
#अन्तर्भाव "SDL_x11xfixes.h"
#अन्तर्भाव "SDL_x11settings.h"
#अन्तर्भाव "../SDL_clipboard_c.h"
#अन्तर्भाव "SDL_x11xsync.h"
#अन्तर्भाव "../../core/unix/SDL_poll.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"
#अन्तर्भाव "../../core/linux/SDL_system_theme.h"
#अन्तर्भाव "../SDL_sysvideo.h"

#अन्तर्भाव <stdio.h>

#जइ 0
#define DEBUG_XEVENTS
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPLEFT
#define _NET_WM_MOVERESIZE_SIZE_TOPLEFT 0
#endif

#ifndef NET_WM_MOVERESIZE_SIZE_शिखरम्
#define NET_WM_MOVERESIZE_SIZE_शिखरम् 1
#endif

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPRIGHT
#define _NET_WM_MOVERESIZE_SIZE_TOPRIGHT 2
#endif

#ifndef NET_WM_MOVERESIZE_SIZE_दक्षिणः
#define NET_WM_MOVERESIZE_SIZE_दक्षिणः 3
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

#ifndef NET_WM_MOVERESIZE_SIZE_वामः
#define NET_WM_MOVERESIZE_SIZE_वामः 7
#endif

#ifndef _NET_WM_MOVERESIZE_MOVE
#define _NET_WM_MOVERESIZE_MOVE 8
#endif

प्रकारनिर्देश संरचना
{
    unsigned वर्ण *data;
    पूर्णाङ्क format, गणनम्;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
स्थिर शून्य X11_ReadProperty(SDL_x11Prop *p, Display *disp, Window w, Atom prop)
{
    unsigned वर्ण *ret = रिक्त;
    Atom type;
    पूर्णाङ्क fmt;
    unsigned long गणनम्;
    unsigned long bytes_वामः;
    पूर्णाङ्क bytes_fetch = 0;

    करेहि {
        जइ (ret) {
            X11_XFree(ret);
        }
        X11_XGetWindowProperty(disp, w, prop, 0, bytes_fetch, False, AnyPropertyType, &type, &fmt, &गणनम्, &bytes_वामः, &ret);
        bytes_fetch += bytes_वामः;
    } जाव (bytes_वामः != 0);

    p->data = ret;
    p->format = fmt;
    p->गणनम् = गणनम्;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
स्थिर Atom X11_PickTarget(Display *disp, Atom list[], पूर्णाङ्क list_गणनम्)
{
    ध्रुव Atom text_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    प्रति (पूर्णाङ्क i = 0; i < list_गणनम् && request != text_uri_request; i++) {
        वर्ण *name = X11_XGetAtomName(disp, list[i]);
        // Preferred MIME targets
        जइ ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            जइ (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        जइ ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            जइ (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    जइ (preferred != None && request != text_uri_request) {
        request = preferred;
    }
    प्रत्यागम request;
}

/* Wrapper for X11_PickTarget for a maximum of three targets, a special
   case in the Xdnd protocol */
स्थिर Atom X11_PickTargetFromAtoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    पूर्णाङ्क गणनम् = 0;
    Atom atom[3];
    जइ (a0 != None) {
        atom[गणनम्++] = a0;
    }
    जइ (a1 != None) {
        atom[गणनम्++] = a1;
    }
    जइ (a2 != None) {
        atom[गणनम्++] = a2;
    }
    प्रत्यागम X11_PickTarget(disp, atom, गणनम्);
}

संरचना कुञ्चिका_Repeat_Check_Data
{
    XEvent *event;
    bool found;
};

स्थिर Bool X11_कुञ्चिका_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    संरचना कुञ्चिका_Repeat_Check_Data *d = (संरचना कुञ्चिका_Repeat_Check_Data *)arg;
    जइ (chkev->type == कुञ्चिका_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.time - d->event->xkey.time < 2) {
        d->found = true;
    }
    प्रत्यागम False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
स्थिर bool X11_कुञ्चिका_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    संरचना कुञ्चिका_Repeat_Check_Data d;
    d.event = event;
    d.found = false;
    जइ (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_कुञ्चिका_Repeat_Check_If_Event, (XPointer)&d);
    }
    प्रत्यागम d.found;
}

bool X11_IsWheelEvent(पूर्णाङ्क button, पूर्णाङ्क *xticks, पूर्णाङ्क *yticks)
{
    /* according to the xlib docs, no specific mouse wheel events exist.
       However, the defacto standard is that the vertical wheel is X buttons
       4 (up) and 5 (down) and a horizontal wheel is 6 (left) and 7 (right). */

    // Xlib defines "Button1" through 5, so we just use literals here.
    विकल्प (button) {
    पक्ष 4:
        *yticks = 1;
        प्रत्यागम true;
    पक्ष 5:
        *yticks = -1;
        प्रत्यागम true;
    पक्ष 6:
        *xticks = 1;
        प्रत्यागम true;
    पक्ष 7:
        *xticks = -1;
        प्रत्यागम true;
    स्वभाव:
        भङ्ग;
    }
    प्रत्यागम false;
}

// An X11 event hook
स्थिर SDL_X11EventHook g_X11EventHook = रिक्त;
स्थिर शून्य *g_X11EventHookData = रिक्त;

शून्य SDL_SetX11EventHook(SDL_X11EventHook callback, शून्य *userdata)
{
    g_X11EventHook = callback;
    g_X11EventHookData = userdata;
}

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
स्थिर शून्य X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_VideoData *videodata = _this->internal;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    जइ (X11_XGetEventData(videodata->display, cookie)) {
        जइ (!g_X11EventHook || g_X11EventHook(g_X11EventHookData, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFreeEventData(videodata->display, cookie);
    }
}
#endif // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

स्थिर शून्य X11_Update_System_कुञ्चिका_Modifiers(SDL_VideoData *viddata)
{
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    जइ (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        जइ (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.base_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } अण्णहा
#endif
        {
        Window junk_window;
        पूर्णाङ्क x, y;
        unsigned पूर्णाङ्क mod_mask;

        X11_XQueryPointer(viddata->display, Default_मूलम्_Window(viddata->display), &junk_window, &junk_window, &x, &y, &x, &y, &mod_mask);
        viddata->keyboard.pressed_modifiers = mod_mask & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        viddata->keyboard.locked_modifiers = mod_mask & (LockMask | viddata->keyboard.numlock_mask | viddata->keyboard.scrolllock_mask);
    }
}

स्थिर शून्य X11_ReconcileModifiers(SDL_VideoData *viddata, bool कुञ्चिका_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    जइ (कुञ्चिका_pressed) {
        जइ (viddata->keyboard.pressed_modifiers & ShiftMask) {
            जइ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT);
            }
        }

        जइ (viddata->keyboard.pressed_modifiers & ControlMask) {
            जइ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        जइ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            जइ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        जइ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            जइ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } अण्णहा {
        जइ (viddata->keyboard.pressed_modifiers & ShiftMask) {
            जइ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } अण्णहा {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        जइ (viddata->keyboard.pressed_modifiers & ControlMask) {
            जइ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } अण्णहा {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        जइ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            जइ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } अण्णहा {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        जइ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            जइ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } अण्णहा {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        जइ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_mask) {
            जइ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_MODE)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_MODE;
            }
        } अण्णहा {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        जइ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_mask) {
            जइ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } अण्णहा {
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
    जइ (viddata->keyboard.locked_modifiers & ShiftMask) {
        जइ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT);
        } अण्णहा जइ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_SHIFT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } अण्णहा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    जइ (viddata->keyboard.locked_modifiers & ControlMask) {
        जइ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } अण्णहा जइ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } अण्णहा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    जइ (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_mask) {
        जइ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } अण्णहा जइ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } अण्णहा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    जइ (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_mask) {
        जइ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } अण्णहा जइ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } अण्णहा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    जइ (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_MODE;
    } अण्णहा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_MODE;
    }

    जइ (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } अण्णहा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    जइ (viddata->keyboard.locked_modifiers & LockMask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } अण्णहा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    जइ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_अङ्कः;
    } अण्णहा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_अङ्कः;
    }

    जइ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } अण्णहा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_SetModState(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

स्थिर शून्य X11_Handle_Modifier_कुञ्चिकाः(SDL_VideoData *viddata, SDL_Scancode scancode, bool pressed)
{
    ध्रुव SDL_Keycode keycode = SDL_Get_कुञ्चिका_From_Scancode(scancode, SDL_KMOD_NONE, false);
    SDL_Keymod mod = SDL_KMOD_NONE;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is checked.
     */
    विकल्प (keycode) {
    पक्ष SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        भङ्ग;
    पक्ष SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        भङ्ग;
    पक्ष SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        भङ्ग;
    पक्ष SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        भङ्ग;
    पक्ष SDLK_LALT:
        mod = SDL_KMOD_LALT;
        भङ्ग;
    पक्ष SDLK_RALT:
        mod = SDL_KMOD_RALT;
        भङ्ग;
    पक्ष SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        भङ्ग;
    पक्ष SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        भङ्ग;
    पक्ष SDLK_MODE:
        mod = SDL_KMOD_MODE;
        भङ्ग;
    पक्ष SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        भङ्ग;
    पक्ष SDLK_CAPSLOCK:
    पक्ष SDLK_NUMLOCKCLEAR:
    पक्ष SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        जइ (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            unsigned पूर्णाङ्क cur_mask = viddata->keyboard.locked_modifiers;
            X11_Update_System_कुञ्चिका_Modifiers(viddata);

            जइ (viddata->keyboard.locked_modifiers & LockMask) {
                cur_mask |= LockMask;
            } अण्णहा {
                cur_mask &= ~LockMask;
            }
            जइ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
                cur_mask |= viddata->keyboard.numlock_mask;
            } अण्णहा {
                cur_mask &= ~viddata->keyboard.numlock_mask;
            }
            जइ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
                cur_mask |= viddata->keyboard.scrolllock_mask;
            } अण्णहा {
                cur_mask &= ~viddata->keyboard.scrolllock_mask;
            }

            viddata->keyboard.locked_modifiers = cur_mask;
        }
    } भङ्ग;
    स्वभाव:
        प्रत्यागम;
    }

    जइ (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } अण्णहा {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

शून्य X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    वर्ण कुञ्चिकाः[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_कुञ्चिका_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_अङ्कः | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= LockMask | videodata->keyboard.numlock_mask| videodata->keyboard.scrolllock_mask;

    X11_XQueryKeymap(display, कुञ्चिकाः);

    ध्रुव bool *keystate = SDL_GetKeyboardState(रिक्त);
    प्रति (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.कुञ्चिका_layout); ++keycode) {
        ध्रुव SDL_Scancode scancode = videodata->keyboard.कुञ्चिका_layout[keycode];
        ध्रुव bool x11_कुञ्चिका_Pressed = (कुञ्चिकाः[keycode / 8] & (1 << (keycode % 8))) != 0;
        ध्रुव bool sdl_कुञ्चिका_Pressed = keystate[scancode];

        जइ (x11_कुञ्चिका_Pressed && !sdl_कुञ्चिका_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            विकल्प (SDL_Get_कुञ्चिका_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            पक्ष SDLK_LCTRL:
            पक्ष SDLK_RCTRL:
            पक्ष SDLK_LSHIFT:
            पक्ष SDLK_RSHIFT:
            पक्ष SDLK_LALT:
            पक्ष SDLK_RALT:
            पक्ष SDLK_LGUI:
            पक्ष SDLK_RGUI:
            पक्ष SDLK_MODE:
            पक्ष SDLK_LEVEL5_SHIFT:
                X11_Handle_Modifier_कुञ्चिकाः(videodata, scancode, true);
                SDL_Send_Keyboard_कुञ्चिका_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                भङ्ग;
            स्वभाव:
                भङ्ग;
            }
        } अण्णहा जइ (!x11_कुञ्चिका_Pressed && sdl_कुञ्चिका_Pressed) {
            X11_Handle_Modifier_कुञ्चिकाः(videodata, scancode, false);
            SDL_Send_Keyboard_कुञ्चिका_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_कुञ्चिका_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

स्थिर शून्य X11_DispatchFocusIn(SDL_VideoDevice *_this, SDL_WindowData *data)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", data->xwindow);
#endif
    SDL_SetKeyboardFocus(data->window);
    X11_ReconcileKeyboardState(_this);
#ifdef X_HAVE_UTF8_STRING
    जइ (data->ic) {
        X11_XSetICFocus(data->ic);
    }
#endif
    जइ (data->flashing_window) {
        X11_FlashWindow(_this, data->window, SDL_FLASH_CANCEL);
    }
}

स्थिर शून्य X11_DispatchFocusOut(SDL_VideoDevice *_this, SDL_WindowData *data)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", data->xwindow);
#endif
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    जइ (data->window == SDL_GetKeyboardFocus()) {
        SDL_SetKeyboardFocus(रिक्त);
    }
#ifdef X_HAVE_UTF8_STRING
    जइ (data->ic) {
        X11_XUnsetICFocus(data->ic);
    }
#endif
}

स्थिर शून्य X11_DispatchMapNotify(SDL_WindowData *data)
{
    SDL_Window *window = data->window;

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    data->was_shown = true;

    // This may be sent when restoring a minimized window.
    जइ (window->flags & SDL_WINDOW_MINIMIZED) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }

    जइ (window->flags & SDL_WINDOW_निवेशः_FOCUS) {
        SDL_UpdateWindowGrab(window);
    }
}

स्थिर शून्य X11_DispatchUnmapNotify(SDL_WindowData *data)
{
    SDL_Window *window = data->window;

    // This may be sent when minimizing a window.
    जइ (!window->is_hiding) {
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
    } अण्णहा {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    }
}

स्थिर शून्य DispatchWindowMove(SDL_VideoDevice *_this, ध्रुव SDL_WindowData *data, ध्रुव SDL_Point *point)
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
    X11_XSendEvent(display, Default_मूलम्_Window(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

स्थिर शून्य ScheduleWindowMove(SDL_VideoDevice *_this, SDL_WindowData *data, ध्रुव SDL_Point *point)
{
    data->pending_move = true;
    data->pending_move_point = *point;
}

स्थिर शून्य InitiateWindowResize(SDL_VideoDevice *_this, ध्रुव SDL_WindowData *data, ध्रुव SDL_Point *point, पूर्णाङ्क direction)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_Window *window = data->window;
    Display *display = videodata->display;
    XEvent evt;

    जइ (direction < _NET_WM_MOVERESIZE_SIZE_TOPLEFT || direction > NET_WM_MOVERESIZE_SIZE_वामः) {
        प्रत्यागम;
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
    X11_XSendEvent(display, Default_मूलम्_Window(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_WindowData *data, ध्रुव भिन्न x, ध्रुव भिन्न y, bool force_new_result)
{
    SDL_Window *window = data->window;
    जइ (!window->hit_test) प्रत्यागम false;
    ध्रुव SDL_Point point = { (पूर्णाङ्क)x, (पूर्णाङ्क)y };
    SDL_HitTestResult rc = window->hit_test(window, &point, window->hit_test_data);
    जइ (!force_new_result && rc == data->hit_test_result) {
        प्रत्यागम true;
    }
    X11_SetHitTestCursor(rc);
    data->hit_test_result = rc;
    प्रत्यागम true;
}

bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_WindowData *data, ध्रुव भिन्न x, ध्रुव भिन्न y)
{
    SDL_Window *window = data->window;

    जइ (window->hit_test) {
        ध्रुव SDL_Point point = { (पूर्णाङ्क)x, (पूर्णाङ्क)y };
        स्थिर ध्रुव पूर्णाङ्क directions[] = {
            _NET_WM_MOVERESIZE_SIZE_TOPLEFT, NET_WM_MOVERESIZE_SIZE_शिखरम्,
            _NET_WM_MOVERESIZE_SIZE_TOPRIGHT, NET_WM_MOVERESIZE_SIZE_दक्षिणः,
            _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT, _NET_WM_MOVERESIZE_SIZE_BOTTOM,
            _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT, NET_WM_MOVERESIZE_SIZE_वामः
        };

        विकल्प (data->hit_test_result) {
        पक्ष SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            जइ (data->window->flags & SDL_WINDOW_निवेशः_FOCUS) {
                DispatchWindowMove(_this, data, &point);
            } अण्णहा {
                ScheduleWindowMove(_this, data, &point);
            }
            प्रत्यागम true;

        पक्ष SDL_HITTEST_RESIZE_TOPLEFT:
        पक्ष SDL_HITTEST_RESIZE_शिखरम्:
        पक्ष SDL_HITTEST_RESIZE_TOPRIGHT:
        पक्ष SDL_HITTEST_RESIZE_दक्षिणः:
        पक्ष SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        पक्ष SDL_HITTEST_RESIZE_BOTTOM:
        पक्ष SDL_HITTEST_RESIZE_BOTTOMLEFT:
        पक्ष SDL_HITTEST_RESIZE_वामः:
            InitiateWindowResize(_this, data, &point, directions[data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
            प्रत्यागम true;

        स्वभाव:
            प्रत्यागम false;
        }
    }

    प्रत्यागम false;
}

स्थिर शून्य X11_UpdateUserTime(SDL_WindowData *data, ध्रुव unsigned long latest)
{
    जइ (latest && (latest != data->user_time)) {
        SDL_VideoData *videodata = data->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, data->xwindow, videodata->atoms._NET_WM_USER_TIME,
                            XA_CARDINAL, 32, PropModeReplace,
                            (ध्रुव unsigned वर्ण *)&latest, 1);
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", data->xwindow, latest);
#endif
        data->user_time = latest;
    }
}

स्थिर unsigned वर्ण x11_last_error;
स्थिर पूर्णाङ्क BadWindowErrorHandler(Display *d, XErrorEvent *e)
{
    x11_last_error = e->error_code;

    // Ignore BadWindow in cases where it's not fatal.
    जइ (e->error_code != BadWindow) {
        वर्ण err_सन्देशः[128];
        X11_XGetErrorText(d, e->error_code, err_सन्देशः, परिमाण(err_सन्देशः));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_code, err_सन्देशः, e->request_code);
    }
    प्रत्यागम 0;
}

स्थिर शून्य X11_HandleClipboardEvent(SDL_VideoDevice *_this, ध्रुव XEvent *xevent)
{
    पूर्णाङ्क i;
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_window != None);
    SDL_assert(xevent->xany.window == videodata->clipboard_window);

    विकल्प (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    पक्ष SelectionRequest:
    {
        ध्रुव XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        पूर्णाङ्क mime_formats;
        unsigned वर्ण *seln_data;
        size_t seln_length = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_ClipboardData *clipboard;

#ifdef DEBUG_XEVENTS
        वर्ण *atom_name;
        atom_name = X11_XGetAtomName(display, req->target);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->target, atom_name);
        जइ (atom_name) {
            X11_XFree(atom_name);
        }
#endif

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_last_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

        जइ (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } अण्णहा {
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

        जइ (req->target == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_गणनम् + 1) * परिमाण(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            प्रति (i = 0; i < clipboard->mime_गणनम्; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, PropModeReplace,
                                (unsigned वर्ण *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.target = XA_TARGETS;
            SDL_free(supportedFormats);
        } अण्णहा {
            जइ (clipboard->callback) {
                प्रति (i = 0; i < clipboard->mime_गणनम्; ++i) {
                    ध्रुव वर्ण *mime_type = clipboard->mime_types[i];
                    जइ (X11_XInternAtom(display, mime_type, False) != req->target) {
                        अनुवर्त;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_data = (unsigned वर्ण *)clipboard->callback(clipboard->userdata, mime_type, &seln_length);
                    जइ (seln_data) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->target, 8, PropModeReplace,
                                            seln_data, seln_length);
                        sevent.xselection.property = req->property;
                        sevent.xselection.target = req->target;
                    }
                    भङ्ग;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(prev_handler);
    } भङ्ग;

    पक्ष SelectionNotify:
    {
        ध्रुव XSelectionEvent *xsel = &xevent->xselection;
#ifdef DEBUG_XEVENTS
        ध्रुव वर्ण *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        ध्रुव वर्ण *targetName = xsel->target ? X11_XGetAtomName(display, xsel->target) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, targetName, propName);
#endif
        जइ (xsel->target == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            unsigned वर्ण *data = रिक्त;
            पूर्णाङ्क format_property = 0;
            unsigned long length = 0;
            unsigned long bytes_वामः = 0;
            पूर्णाङ्क j;

            X11_XGetWindowProperty(display, GetWindow(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &length, &bytes_वामः, &data);

            पूर्णाङ्क allocationsize = (length + 1) * परिमाण(वर्ण *);
            प्रति (j = 0, patom = (Atom *)data; j < length; j++, patom++) {
                वर्ण *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            वर्ण **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
            जइ (new_mime_types) {
                वर्ण *strPtr = (वर्ण *)(new_mime_types + length + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                प्रति (j = 0, patom = (Atom *)data; j < length; j++, patom++) {
                    वर्ण *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    ध्रुव size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[length] = रिक्त;

                SDL_SendClipboardUpdate(false, new_mime_types, length);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            जइ (data) {
                X11_XFree(data);
            }
        }

        videodata->selection_waiting = false;
    } भङ्ग;

    पक्ष SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_ClipboardData *clipboard = रिक्त;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.target);
#endif

        जइ (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } अण्णहा जइ (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        जइ (clipboard && clipboard->callback) {
            जइ (clipboard->sequence) {
                SDL_CancelClipboardData(clipboard->sequence);
            } अण्णहा {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } भङ्ग;

    पक्ष PropertyNotify:
    {
        वर्ण *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        जइ (SDL_strncmp(name_of_atom, "SDL_SELECTION", परिमाण("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_मानम्) {
            videodata->selection_incr_waiting = false;
        }

        जइ (name_of_atom) {
            X11_XFree(name_of_atom);
        }
    } भङ्ग;
    }
}

स्थिर Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    प्रत्यागम ev->type == MapNotify &&
           ev->xmap.window == unmap->window &&
           ev->xmap.serial == unmap->serial;
}

स्थिर Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    प्रत्यागम ev->type == ReparentNotify &&
           ev->xreparent.window == unmap->window &&
           ev->xreparent.serial == unmap->serial;
}

स्थिर bool Is_उच्चः_Latin1(ध्रुव वर्ण *string, पूर्णाङ्क length)
{
    जाव (length-- > 0) {
        Uint8 ch = (Uint8)*string;
        जइ (ch >= 0x80) {
            प्रत्यागम true;
        }
        ++string;
    }
    प्रत्यागम false;
}

स्थिर पूर्णाङ्क XLookupStringAsUTF8(XKeyEvent *event_struct, वर्ण *buffer_return, पूर्णाङ्क bytes_buffer, कुञ्चिका_Sym *keysym_return, XComposeStatus *status_in_out)
{
    पूर्णाङ्क result = X11_XLookupString(event_struct, buffer_return, bytes_buffer, keysym_return, status_in_out);
    जइ (Is_उच्चः_Latin1(buffer_return, result)) {
        वर्ण *utf8_text = SDL_iconv_string("UTF-8", "ISO-8859-1", buffer_return, result + 1);
        जइ (utf8_text) {
            SDL_strlcpy(buffer_return, utf8_text, bytes_buffer);
            SDL_free(utf8_text);
            प्रत्यागम SDL_strlen(buffer_return);
        } अण्णहा {
            प्रत्यागम 0;
        }
    }
    प्रत्यागम result;
}

SDL_WindowData *X11_FindWindow(SDL_VideoData *videodata, Window window)
{
    जइ (videodata && videodata->windowlist) {
        प्रति (पूर्णाङ्क i = 0; i < videodata->numwindows; ++i) {
            जइ ((videodata->windowlist[i] != रिक्त) &&
                (videodata->windowlist[i]->xwindow == window)) {
                प्रत्यागम videodata->windowlist[i];
            }
        }
    }
    प्रत्यागम रिक्त;
}

Uint64 X11_GetEventTimestamp(unsigned long time)
{
    // FIXME: Get the event time in the SDL tick time base
    प्रत्यागम SDL_GetTicksNS();
}

शून्य X11_Handle_कुञ्चिका_Event(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    कुञ्चिका_Code_2 keycode = xevent->xkey.keycode;
    कुञ्चिका_Sym keysym = No_चिह्नम्;
    पूर्णाङ्क text_length = 0;
    वर्ण text[64];
    Status status = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == कुञ्चिका_Press);
    SDL_Scancode scancode = videodata->keyboard.कुञ्चिका_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.window, (xevent->type == कुञ्चिका_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#endif
#ifdef DEBUG_SCANCODES
    जइ (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        पूर्णाङ्क min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_कुञ्चिका_Code_To_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysymToString(keysym));
    }
#endif // DEBUG SCANCODES

    text[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    जइ (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (LockMask | videodata->keyboard.numlock_mask | videodata->keyboard.scrolllock_mask);
    }

    जइ (SDL_Text_निवेशः_Active(windowdata->window)) {
        // filter events catches XIM events and sends them to the correct handler
        जइ (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            handled_by_ime = true;
        }

        जइ (!handled_by_ime) {
#ifdef X_HAVE_UTF8_STRING
            जइ (windowdata->ic && xevent->type == कुञ्चिका_Press) {
                text_length = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, text, परिमाण(text) - 1,
                                      &keysym, &status);
            } अण्णहा {
                text_length = XLookupStringAsUTF8(&xevent->xkey, text, परिमाण(text) - 1, &keysym, रिक्त);
            }
#अण्णहा
            text_length = XLookupStringAsUTF8(&xevent->xkey, text, परिमाण(text) - 1, &keysym, रिक्त);
#endif
        }
    }

    जइ (!handled_by_ime) {
        जइ (pressed) {
            X11_Handle_Modifier_कुञ्चिकाः(videodata, scancode, true);
            SDL_Send_Keyboard_कुञ्चिका_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            जइ (*text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                text[text_length] = '\0';
                X11_ClearComposition(windowdata);
                SDL_SendKeyboardText(text);
            }
        } अण्णहा {
            जइ (X11_कुञ्चिका_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                प्रत्यागम;
            }

            X11_Handle_Modifier_कुञ्चिकाः(videodata, scancode, false);
            SDL_Send_Keyboard_कुञ्चिका_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    जइ (pressed) {
        X11_UpdateUserTime(windowdata, xevent->xkey.time);
    }
}

शून्य X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, पूर्णाङ्क button, भिन्न x, भिन्न y, unsigned long time, unsigned long serial)
{
    SDL_Window *window = windowdata->window;
    पूर्णाङ्क xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#endif

    SDL_Mouse *mouse = SDL_GetMouse();
    जइ (!mouse->relative_mode && (x != mouse->x || y != mouse->y)) {
        X11_ProcessHitTest(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, window, mouseID, false, x, y);
    }

    जइ (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, window, mouseID, (भिन्न)-xticks, (भिन्न)yticks, SDL_MOUSEWHEEL_NORMAL);
    } अण्णहा {
        जइ (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        जइ (button == Button1) {
            जइ (X11_TriggerHitTestAction(_this, windowdata, x, y)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0);
                प्रत्यागम; // don't pass this event on to app.
            }
        }
        जइ (windowdata->last_focus_event_time) {
            ध्रुव पूर्णाङ्क X11_FOCUS_CLICK_TIMEOUT = 10;
            जइ (SDL_GetTicks() < (windowdata->last_focus_event_time + X11_FOCUS_CLICK_TIMEOUT)) {
                जइ (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->last_focus_event_time = 0;
        }
        जइ (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, window, mouseID, button, true);
        }
    }
    X11_UpdateUserTime(windowdata, time);
}

शून्य X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_WindowData *windowdata, SDL_MouseID mouseID, पूर्णाङ्क button, unsigned long time)
{
    SDL_Window *window = windowdata->window;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    पूर्णाङ्क xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#endif
    जइ (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        जइ (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, window, mouseID, button, false);

        जइ (window->internal->pending_grab) {
            X11_SetWindowMouseGrab(_this, window, true);
        }
    }
}

शून्य X11_Get_Border_मानानि(SDL_WindowData *data)
{
    SDL_VideoData *videodata = data->videodata;
    Display *display = videodata->display;

    Atom type;
    पूर्णाङ्क format;
    unsigned long nitems, bytes_after;
    unsigned वर्ण *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    जइ (!(data->window->flags & SDL_WINDOW_BORDERLESS)) {
        जइ (X11_XGetWindowProperty(display, data->xwindow, videodata->atoms._NET_FRAME_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &bytes_after, &property) == Success) {
            जइ (type != None && nitems == 4) {
                data->border_वामः = (पूर्णाङ्क)((long *)property)[0];
                data->border_दक्षिणः = (पूर्णाङ्क)((long *)property)[1];
                data->border_शिखरम् = (पूर्णाङ्क)((long *)property)[2];
                data->border_bottom = (पूर्णाङ्क)((long *)property)[3];
            }
            X11_XFree(property);

#ifdef DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", data->border_वामः, data->border_दक्षिणः, data->border_शिखरम्, data->border_bottom);
#endif
        }
    } अण्णहा {
        data->border_वामः = data->border_शिखरम् = data->border_दक्षिणः = data->border_bottom = 0;
    }
}

शून्य X11_EmitConfigureNotifyEvents(SDL_WindowData *data, XConfigureEvent *xevent)
{
    जइ (!data->size_move_event_flags) {
        पूर्णाङ्क x = xevent->x;
        पूर्णाङ्क y = xevent->y;

        जइ (xevent->x != data->last_xconfigure.x ||
            xevent->y != data->last_xconfigure.y) {
            data->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_GlobalToRelativeForWindow(data->window, x, y, &x, &y);
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MOVED, x, y);

        प्रति (SDL_Window *w = data->window->first_child; w; w = w->next_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            जइ (SDL_WINDOW_IS_POPUP(w) && !(w->flags & SDL_WINDOW_HIDDEN)) {
                X11_UpdateWindowPosition(w, true);
            }
        }

        जइ (xevent->width != data->last_xconfigure.width ||
            xevent->height != data->last_xconfigure.height) {
            data->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESIZED, xevent->width, xevent->height);
    }

    SDL_copyp(&data->last_xconfigure, xevent);
}

स्थिर शून्य X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display;
    SDL_WindowData *data;
    XClientMessageEvent m;
    पूर्णाङ्क i;

    SDL_assert(videodata != रिक्त);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    जइ (xevent->type != कुञ्चिका_Press && xevent->type != कुञ्चिका_Release) {
        जइ (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            प्रत्यागम;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    जइ (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        प्रत्यागम;
    }
#endif

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    जइ (g_X11EventHook) {
        जइ (!g_X11EventHook(g_X11EventHookData, xevent)) {
            प्रत्यागम;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    जइ (videodata->xrandr_event_base && (xevent->type == (videodata->xrandr_event_base + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#endif

#ifdef DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.window);
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    जइ (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#endif

        जइ (ev->subtype == XFixesSetSelectionOwnerNotify)
        {
            जइ (ev->selection != videodata->atoms.CLIPBOARD)
                प्रत्यागम;

            जइ (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_window)
                प्रत्यागम;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, GetWindow(_this), CurrentTime);
        }

        प्रत्यागम;
    }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES

    जइ ((videodata->clipboard_window != None) &&
        (videodata->clipboard_window == xevent->xany.window)) {
        X11_HandleClipboardEvent(_this, xevent);
        प्रत्यागम;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    data = X11_FindWindow(videodata, xevent->xany.window);

    जइ (!data) {
        // The window for KeymapNotify, etc events is 0
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        जइ (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            विकल्प (xkbevent->any.xkb_type) {
            पक्ष XkbStateNotify:
            {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.window);
#endif
                जइ ((xkbevent->state.changed & XkbGroupStateMask) && xkbevent->state.group != videodata->keyboard.xkb.current_group) {
                    videodata->keyboard.xkb.current_group = xkbevent->state.group;
                    SDL_SetKeymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_group], true);
                }

                जइ (xkbevent->state.changed & XkbModifierStateMask) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.base_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } भङ्ग;

            पक्ष XkbMapNotify:
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.window);
                SDL_FALLTHROUGH;
#endif
            पक्ष XkbNewKeyboardNotify:
            {
#ifdef DEBUG_XEVENTS
                जइ (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.window);
                }
#endif
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                जइ (xkbevent->any.serial != videodata->keyboard.xkb.last_map_serial) {
                    videodata->keyboard.xkb.last_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } भङ्ग;

            स्वभाव:
                भङ्ग;
            }
        } अण्णहा
#endif
        जइ (xevent->type == KeymapNotify) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.window);
#endif
            जइ (SDL_GetKeyboardFocus() != रिक्त) {
                जइ (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } अण्णहा जइ (xevent->type == MappingNotify) {
            ध्रुव पूर्णाङ्क request = xevent->xmapping.request;

            जइ (request == MappingPointer) {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                X11_Xinput2UpdatePointerMapping(_this);
            } अण्णहा जइ (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                जइ (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } अण्णहा जइ (xevent->type == PropertyNotify && videodata) {
            वर्ण *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            जइ (name_of_atom) {
                जइ (SDL_startswith(name_of_atom, "_ICC_PROFILE")) {
                    XWindowAttributes attrib;
                    पूर्णाङ्क screennum;
                    प्रति (i = 0; i < videodata->numwindows; ++i) {
                        जइ (videodata->windowlist[i] != रिक्त) {
                            data = videodata->windowlist[i];
                            X11_XGetWindowAttributes(display, data->xwindow, &attrib);
                            screennum = X11_XScreen_सङ्ख्या_Of_Screen(attrib.screen);
                            जइ (screennum == 0 && SDL_strcmp(name_of_atom, "_ICC_PROFILE") == 0) {
                                SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                            } अण्णहा जइ (SDL_strncmp(name_of_atom, "_ICC_PROFILE_", परिमाण("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_of_atom) > परिमाण("_ICC_PROFILE_") - 1) {
                                पूर्णाङ्क iccscreennum = SDL_atoi(&name_of_atom[परिमाण("_ICC_PROFILE_") - 1]);

                                जइ (screennum == iccscreennum) {
                                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                                }
                            }
                        }
                    }
                } अण्णहा जइ (SDL_strcmp(name_of_atom, "_NET_WORKAREA") == 0) {
                    प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
                    }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
                } अण्णहा जइ (SDL_strcmp(name_of_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_of_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#endif
                }
                X11_XFree(name_of_atom);
            }
        }
        प्रत्यागम;
    }

    विकल्प (xevent->type) {

        // Gaining mouse coverage?
    पक्ष EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        जइ (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        जइ (xevent->xcrossing.mode == NotifyUngrab) {
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
            जइ ((data->pointer_barrier_active == true) && windowdata->window->flags & SDL_WINDOW_निवेशः_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->window, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#endif

        जइ (!mouse->relative_mode) {
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (भिन्न)xevent->xcrossing.x, (भिन्न)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        जइ (!(data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            SDL_UpdateWindowGrab(data->window);
        }

        X11_ProcessHitTest(_this, data, mouse->last_x, mouse->last_y, true);
    } भङ्ग;
        // Losing mouse coverage?
    पक्ष LeaveNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        जइ (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        जइ (xevent->xcrossing.mode == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#endif
        जइ (!SDL_GetMouse()->relative_mode) {
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (भिन्न)xevent->xcrossing.x, (भिन्न)xevent->xcrossing.y);
        }

        जइ (xevent->xcrossing.mode != NotifyGrab &&
            xevent->xcrossing.mode != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            जइ (!(data->window->flags & SDL_WINDOW_FULLSCREEN)) {
                X11_SetWindowKeyboardGrab(_this, data->window, false);
            }

            SDL_SetMouseFocus(रिक्त);
        }
    } भङ्ग;

        // Gaining input focus?
    पक्ष FocusIn:
    {
        जइ (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            भङ्ग;
        }

        जइ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            भङ्ग;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.window);
#endif
        जइ (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            data->pending_focus = PENDING_FOCUS_NONE;
            data->pending_focus_time = 0;
            X11_DispatchFocusIn(_this, data);
        } अण्णहा {
            data->pending_focus = PENDING_FOCUS_IN;
            data->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }
        data->last_focus_event_time = SDL_GetTicks();
    } भङ्ग;

        // Losing input focus?
    पक्ष FocusOut:
    {
        जइ (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            भङ्ग;
        }
        जइ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            भङ्ग;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.window);
#endif
        जइ (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            data->pending_focus = PENDING_FOCUS_NONE;
            data->pending_focus_time = 0;
            X11_DispatchFocusOut(_this, data);
        } अण्णहा {
            data->pending_focus = PENDING_FOCUS_OUT;
            data->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        जइ (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, रिक्त, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } भङ्ग;


        // Have we been iconified?
    पक्ष UnmapNotify:
    {
        XEvent ev;

#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.window);
#endif

        जइ (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } अण्णहा {
            X11_DispatchUnmapNotify(data);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        जइ (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, रिक्त, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } भङ्ग;

        // Have we been restored?
    पक्ष MapNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.window);
#endif
        X11_DispatchMapNotify(data);

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        जइ (data->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, data->window, &data->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } भङ्ग;

        // Have we been resized or moved?
    पक्ष ConfigureNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.window,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.width, xevent->xconfigure.height);
#endif
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        जइ (!xevent->xconfigure.send_event) {
            unsigned पूर्णाङ्क अङ्कः_Children;
            Window ChildReturn, मूलम्_2, Parent;
            Window *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_last_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

            X11_XQuery_वृक्षः(data->videodata->display, xevent->xconfigure.window, &मूलम्_2, &Parent, &Children, &अङ्कः_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      Parent, Default_मूलम्_Window(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &ChildReturn);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            जइ (x11_last_error == BadWindow) {
                भङ्ग;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        ध्रुव SDL_WindowFlags changed = X11_GetNetWMState(_this, data->window, xevent->xproperty.window) ^ data->window->flags;
        जइ (changed & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) {
            SDL_copyp(&data->pending_xconfigure, &xevent->xconfigure);
            data->emit_size_move_after_property_notify = true;
        }

        जइ (!data->emit_size_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(data, &xevent->xconfigure);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(data->window, &xevent->xconfigure);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } भङ्ग;

        // Have we been requested to quit (or another client message?)
    पक्ष ClientMessage:
    {
        स्थिर पूर्णाङ्क xdnd_version = 0;

        जइ (xevent->xclient.message_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.data.l[1] & 1;
            data->xdnd_source = xevent->xclient.data.l[0];
            xdnd_version = (xevent->xclient.data.l[1] >> 24);
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", data->xdnd_source);
            SDL_Log("Protocol version to use : %d", xdnd_version);
            SDL_Log("More then 3 data types : %d", (पूर्णाङ्क)use_list);
#endif

            जइ (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, data->xdnd_source, videodata->atoms.XdndTypeList);
                // pick one
                data->xdnd_req = X11_PickTarget(display, (Atom *)p.data, p.गणनम्);
                X11_XFree(p.data);
            } अण्णहा {
                // pick from list of three
                data->xdnd_req = X11_PickTargetFromAtoms(display, xevent->xclient.data.l[2], xevent->xclient.data.l[3], xevent->xclient.data.l[4]);
            }
        } अण्णहा जइ (xevent->xclient.message_type == videodata->atoms.XdndLeave) {
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.data.l[0]);
#endif
            SDL_SendDropComplete(data->window);
        } अण्णहा जइ (xevent->xclient.message_type == videodata->atoms.XdndPosition) {

#ifdef DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            जइ (xdnd_version >= 2) {
                act = xevent->xclient.data.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#endif
            {
                // Drag and Drop position
                पूर्णाङ्क मूलम्_x, मूलम्_y, window_x, window_y;
                Window ChildReturn;
                मूलम्_x = xevent->xclient.data.l[2] >> 16;
                मूलम्_y = xevent->xclient.data.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_मूलम्_Window(display), data->xwindow,
                                          मूलम्_x, मूलम्_y, &window_x, &window_y, &ChildReturn);

                SDL_SendDropPosition(data->window, (भिन्न)window_x, (भिन्न)window_y);
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
        } अण्णहा जइ (xevent->xclient.message_type == videodata->atoms.XdndDrop) {
            जइ (data->xdnd_req == None) {
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
            } अण्णहा {
                // convert
                जइ (xdnd_version >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, data->xdnd_req, videodata->atoms.PRIMARY, data->xwindow, xevent->xclient.data.l[2]);
                } अण्णहा {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, data->xdnd_req, videodata->atoms.PRIMARY, data->xwindow, CurrentTime);
                }
            }
        } अण्णहा जइ ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.data.l[0] == videodata->atoms._NET_WM_PING)) {
            Window मूलम् = Default_मूलम्_Window(display);

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.window);
#endif
            xevent->xclient.window = मूलम्;
            X11_XSendEvent(display, मूलम्, False, SubstructureRedirectMask | SubstructureNotifyMask, xevent);
            भङ्ग;
        }

        अण्णहा जइ ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.data.l[0] == videodata->atoms.WM_DELETE_WINDOW)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.window);
#endif
            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            भङ्ग;
        } अण्णहा जइ ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.data.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", data);
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(data->window, &xevent->xclient);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
            भङ्ग;
        }
    } भङ्ग;

        // Do we need to refresh ourselves?
    पक्ष Expose:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.window, xevent->xexpose.गणनम्);
#endif
        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    } भङ्ग;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    पक्ष कुञ्चिका_Press:
    पक्ष कुञ्चिका_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        जइ (data->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            भङ्ग;
        } अण्णहा जइ (xevent->xkey.serial == videodata->xinput_last_कुञ्चिका_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_last_keyboard_device;
        }

        X11_Handle_कुञ्चिका_Event(_this, data, keyboardID, xevent);
    } भङ्ग;

    पक्ष MotionNotify:
    {
        जइ (X11_Xinput2HandlesMotionForWindow(data)) {
            // This input is being handled by XInput2
            भङ्ग;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        जइ (!mouse->relative_mode) {
#ifdef DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.window, xevent->xmotion.x, xevent->xmotion.y);
#endif

            X11_ProcessHitTest(_this, data, (भिन्न)xevent->xmotion.x, (भिन्न)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, data->window, SDL_GLOBAL_MOUSE_ID, false, (भिन्न)xevent->xmotion.x, (भिन्न)xevent->xmotion.y);
        }
    } भङ्ग;

    पक्ष ButtonPress:
    {
        जइ (data->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            भङ्ग;
        }

        X11_HandleButtonPress(_this, data, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.time, xevent->xbutton.serial);
    } भङ्ग;

    पक्ष ButtonRelease:
    {
        जइ (data->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            भङ्ग;
        }

        X11_HandleButtonRelease(_this, data, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.time);
    } भङ्ग;

    पक्ष PropertyNotify:
    {
#ifdef DEBUG_XEVENTS
        unsigned वर्ण *propdata;
        पूर्णाङ्क status, real_format;
        Atom real_type;
        unsigned long वस्तूनि_read, वस्तूनि_वामः;

        वर्ण *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        जइ (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.window, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.time);
            X11_XFree(name);
        }

        status = X11_XGetWindowProperty(display, data->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
        जइ (status == Success && वस्तूनि_read > 0) {
            जइ (real_type == XA_INTEGER) {
                पूर्णाङ्क *मानानि = (पूर्णाङ्क *)propdata;

                SDL_Log("{");
                प्रति (i = 0; i < वस्तूनि_read; i++) {
                    SDL_Log(" %d", मानानि[i]);
                }
                SDL_Log(" }");
            } अण्णहा जइ (real_type == XA_CARDINAL) {
                जइ (real_format == 32) {
                    Uint32 *मानानि = (Uint32 *)propdata;

                    SDL_Log("{");
                    प्रति (i = 0; i < वस्तूनि_read; i++) {
                        SDL_Log(" %d", मानानि[i]);
                    }
                    SDL_Log(" }");
                } अण्णहा जइ (real_format == 16) {
                    Uint16 *मानानि = (Uint16 *)propdata;

                    SDL_Log("{");
                    प्रति (i = 0; i < वस्तूनि_read; i++) {
                        SDL_Log(" %d", मानानि[i]);
                    }
                    SDL_Log(" }");
                } अण्णहा जइ (real_format == 8) {
                    Uint8 *मानानि = (Uint8 *)propdata;

                    SDL_Log("{");
                    प्रति (i = 0; i < वस्तूनि_read; i++) {
                        SDL_Log(" %d", मानानि[i]);
                    }
                    SDL_Log(" }");
                }
            } अण्णहा जइ (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } अण्णहा जइ (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                प्रति (i = 0; i < वस्तूनि_read; i++) {
                    वर्ण *atomname = X11_XGetAtomName(display, atoms[i]);
                    जइ (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } अण्णहा {
                वर्ण *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                जइ (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        जइ (status == Success) {
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
        जइ (!data->user_time) {
            data->user_time = xevent->xproperty.time;
        }

        जइ (xevent->xproperty.atom == data->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            ध्रुव SDL_WindowFlags flags = X11_GetNetWMState(_this, data->window, xevent->xproperty.window);
            ध्रुव SDL_WindowFlags changed = flags ^ data->window->flags;

            जइ ((changed & SDL_WINDOW_HIDDEN) && !(flags & SDL_WINDOW_HIDDEN)) {
                X11_DispatchMapNotify(data);
            }

            जइ (!SDL_WINDOW_IS_POPUP(data->window)) {
                जइ (changed & SDL_WINDOW_FULLSCREEN) {
                    data->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    जइ (flags & SDL_WINDOW_FULLSCREEN) {
                        जइ (!(flags & SDL_WINDOW_MINIMIZED)) {
                            ध्रुव bool commit = SDL_memcmp(&data->window->current_fullscreen_mode, &data->requested_fullscreen_mode, परिमाण(SDL_DisplayMode)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                            जइ (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&data->window->current_fullscreen_mode, &data->window->requested_fullscreen_mode);
                                SDL_UpdateFullscreenMode(data->window, SDL_FULLSCREEN_OP_UPDATE, true);
                            } अण्णहा {
                                SDL_UpdateFullscreenMode(data->window, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } अण्णहा {
                        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                        SDL_UpdateFullscreenMode(data->window, false, false);

                        SDL_zero(data->requested_fullscreen_mode);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_SetWindowMinMax(data->window, !!(flags & SDL_WINDOW_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        जइ (data->fullscreen_borders_forced_on) {
                            data->toggle_borders = true;
                            data->fullscreen_borders_forced_on = false;
                        }
                    }

                    जइ ((flags & SDL_WINDOW_FULLSCREEN) &&
                        (data->border_शिखरम् || data->border_वामः || data->border_bottom || data->border_दक्षिणः)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        data->size_move_event_flags |= X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        data->previous_borders_nonzero = true;
                    } अण्णहा जइ (!(flags & SDL_WINDOW_FULLSCREEN) &&
                               data->previous_borders_nonzero &&
                               (!data->border_शिखरम् && !data->border_वामः && !data->border_bottom && !data->border_दक्षिणः)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        data->size_move_event_flags |= X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        data->previous_borders_nonzero = false;
                    } अण्णहा {
                        data->size_move_event_flags = 0;
                        data->previous_borders_nonzero = false;

                        जइ (!(data->window->flags & SDL_WINDOW_FULLSCREEN) && data->toggle_borders) {
                            data->toggle_borders = false;
                            X11_SetWindowBordered(_this, data->window, !(data->window->flags & SDL_WINDOW_BORDERLESS));
                        }
                    }
                }
                जइ ((changed & SDL_WINDOW_MAXIMIZED) && ((flags & SDL_WINDOW_MAXIMIZED) && !(flags & SDL_WINDOW_MINIMIZED))) {
                    data->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    जइ ((changed & SDL_WINDOW_MINIMIZED)) {
                        data->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                    }
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
                }
                जइ ((changed & SDL_WINDOW_MINIMIZED) && (flags & SDL_WINDOW_MINIMIZED)) {
                    data->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                }
                जइ (!(flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
                    data->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    जइ (!(flags & SDL_WINDOW_FULLSCREEN)) {
                        जइ (data->pending_position) {
                            data->pending_position = false;
                            data->pending_operation |= X11_PENDING_OP_MOVE;
                            data->expected.x = data->window->pending.x - data->border_वामः;
                            data->expected.y = data->window->pending.y - data->border_शिखरम्;
                            X11_XMoveWindow(display, data->xwindow, data->expected.x, data->expected.y);
                        }
                        जइ (data->pending_size) {
                            data->pending_size = false;
                            data->pending_operation |= X11_PENDING_OP_RESIZE;
                            data->expected.w = data->window->pending.w;
                            data->expected.h = data->window->pending.h;
                            X11_XResizeWindow(display, data->xwindow, data->window->pending.w, data->window->pending.h);
                        }
                    }
                }
                जइ (data->emit_size_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(data, &data->pending_xconfigure);
                    data->emit_size_move_after_property_notify = false;
                }
                जइ ((flags & SDL_WINDOW_निवेशः_FOCUS)) {
                    जइ (data->pending_move) {
                        DispatchWindowMove(_this, data, &data->pending_move_point);
                        data->pending_move = false;
                    }
                }
            }
            जइ (changed & SDL_WINDOW_OCCLUDED) {
                SDL_SendWindowEvent(data->window, (flags & SDL_WINDOW_OCCLUDED) ? SDL_EVENT_WINDOW_OCCLUDED : SDL_EVENT_WINDOW_EXPOSED, 0, 0);
            }
        } अण्णहा जइ (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            पूर्णाङ्क format;
            unsigned long nitems, bytes_after;
            unsigned वर्ण *prop_data = रिक्त;

            जइ (X11_XGetWindowProperty(display, data->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &bytes_after, &prop_data) == Success) {
                जइ (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_data;

                    जइ ((state == 0 || state == 3) && !data->window->is_hiding && !(data->window->flags & SDL_WINDOW_HIDDEN)) {
                        // Withdrawn or Iconic
                        जइ (!(data->window->flags & SDL_WINDOW_MINIMIZED)) {
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
                        }
                    } अण्णहा जइ (state == 1) { // NormalState
                        जइ (data->window->flags & SDL_WINDOW_MINIMIZED) {
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(data->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_data);
            }
        } अण्णहा जइ (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } अण्णहा जइ (xevent->xproperty.atom == videodata->atoms._NET_FRAME_EXTENTS) {
            X11_Get_Border_मानानि(data);
            जइ (data->size_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                data->size_move_event_flags &= ~X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            जइ (!(data->window->flags & SDL_WINDOW_FULLSCREEN) && data->toggle_borders) {
                data->toggle_borders = false;
                X11_SetWindowBordered(_this, data->window, !(data->window->flags & SDL_WINDOW_BORDERLESS));
            }
        }
    } भङ्ग;

    पक्ष SelectionNotify:
    {
        Atom target = xevent->xselection.target;
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.window,
               xevent->xselection.requestor, xevent->xselection.target);
#endif
        जइ (target == data->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, data->xwindow, videodata->atoms.PRIMARY);

            जइ (p.format == 8) {
                वर्ण *saveptr = रिक्त;
                वर्ण *name = X11_XGetAtomName(display, target);
                जइ (name) {
                    वर्ण *token = SDL_strtok_r((वर्ण *)p.data, "\r\n", &saveptr);
                    जाव (token) {
                        जइ ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_SendDropText(data->window, token);
                        } अण्णहा जइ (SDL_strcmp("text/uri-list", name) == 0) {
                            जइ (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(data->window, रिक्त, token);
                            }
                        }
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
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
    } भङ्ग;

    स्वभाव:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.window, xevent->type);
#endif
    } भङ्ग;
    }
}

स्थिर शून्य X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    पूर्णाङ्क i;

    जइ (videodata && videodata->windowlist) {
        प्रति (i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *data = videodata->windowlist[i];
            जइ (data && data->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                जइ (now >= data->pending_focus_time) {
                    जइ (data->pending_focus == PENDING_FOCUS_IN) {
                        X11_DispatchFocusIn(_this, data);
                    } अण्णहा {
                        X11_DispatchFocusOut(_this, data);
                    }
                    data->pending_focus = PENDING_FOCUS_NONE;
                }
            }
        }
    }
}

स्थिर Bool isAnyEvent(Display *display, XEvent *ev, XPointer arg)
{
    प्रत्यागम True;
}

स्थिर bool X11_PollEvent(Display *display, XEvent *event)
{
    जइ (!X11_XCheckIfEvent(display, event, isAnyEvent, रिक्त)) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

शून्य X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
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

पूर्णाङ्क X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    जइ (X11_PollEvent(display, &xevent)) {
        // Fall through
    } अण्णहा जइ (timeoutNS == 0) {
        प्रत्यागम 0;
    } अण्णहा {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        पूर्णाङ्क err = SDL_IOReady(Connection_सङ्ख्या(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        जइ (err > 0) {
            जइ (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                प्रत्यागम 1;
            }
        } अण्णहा जइ (err == 0) {
            // Timeout
            प्रत्यागम 0;
        } अण्णहा {
            // Error returned from poll()/select()

            जइ (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                प्रत्यागम 1;
            } अण्णहा {
                प्रत्यागम err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    प्रत्यागम 1;
}

शून्य X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    XEvent xevent;
    पूर्णाङ्क i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
        जइ (_this->displays[i]->internal->mode_switch_deadline_ns) {
            जइ (_this->displays[i]->fullscreen_window) {
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            } अण्णहा जइ (SDL_GetTicksNS() >= _this->displays[i]->internal->mode_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_SetDisplayModeForDisplay(_this->displays[i], रिक्त);
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            }
        }
    }

    जइ (data->last_mode_change_deadline) {
        जइ (SDL_GetTicks() >= data->last_mode_change_deadline) {
            data->last_mode_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    जइ (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        जइ (!data->screensaver_activity || now >= (data->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(data->display);

#ifdef SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#endif

            data->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    जाव (X11_PollEvent(data->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    प्रति (i = 0; i < data->numwindows; ++i) {
        जइ (data->windowlist[i] != रिक्त &&
            data->windowlist[i]->flash_cancel_time &&
            SDL_GetTicks() >= data->windowlist[i]->flash_cancel_time) {
            X11_FlashWindow(_this, data->windowlist[i]->window, SDL_FLASH_CANCEL);
        }
    }

    जइ (data->xinput_hierarchy_changed) {
        X11_Xinput2UpdateDevices(_this);
        data->xinput_hierarchy_changed = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_VideoData *data = _this->internal;
    पूर्णाङ्क dummy;
    पूर्णाङ्क major_version, minor_version;
#endif // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#ifdef SDL_USE_LIBDBUS
    जइ (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        प्रत्यागम true;
    }

    जइ (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    जइ (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        जइ (!X11_XScreenSaverQueryExtension(data->display, &dummy, &dummy) ||
            !X11_XScreenSaverQueryVersion(data->display,
                                          &major_version, &minor_version) ||
            major_version < 1 || (major_version == 1 && minor_version < 1)) {
            प्रत्यागम SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(data->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(data->display);
        प्रत्यागम true;
    }
#endif
    प्रत्यागम SDL_Unsupported();
}

#endif // SDL_VIDEO_DRIVER_X11
