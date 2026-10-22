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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#অন্তর্ভাব <sys/types.h>
#অন্তর্ভাব <sys/time.h>
#অন্তর্ভাব <signal.h>
#অন্তর্ভাব <unistd.h>
#অন্তর্ভাব <limits.h> // For INT_MAX

#অন্তর্ভাব "SDL_x11video.h"
#অন্তর্ভাব "SDL_x11pen.h"
#অন্তর্ভাব "SDL_x11touch.h"
#অন্তর্ভাব "SDL_x11xinput2.h"
#অন্তর্ভাব "SDL_x11xfixes.h"
#অন্তর্ভাব "SDL_x11settings.h"
#অন্তর্ভাব "../SDL_clipboard_c.h"
#অন্তর্ভাব "SDL_x11xsync.h"
#অন্তর্ভাব "../../core/unix/SDL_poll.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"
#অন্তর্ভাব "../../events/SDL_touch_c.h"
#অন্তর্ভাব "../../core/linux/SDL_system_theme.h"
#অন্তর্ভাব "../SDL_sysvideo.h"

#অন্তর্ভাব <stdio.h>

#যদি 0
#define DEBUG_XEVENTS
#endif

#ifndef NET_WM_MOVERESIZE_আকার_TOPLEFT
#define NET_WM_MOVERESIZE_আকার_TOPLEFT 0
#endif

#ifndef NET_WM_MOVERESIZE_আকার_শীর্ষ
#define NET_WM_MOVERESIZE_আকার_শীর্ষ 1
#endif

#ifndef NET_WM_MOVERESIZE_আকার_TOPRIGHT
#define NET_WM_MOVERESIZE_আকার_TOPRIGHT 2
#endif

#ifndef NET_WM_MOVERESIZE_আকার_ডান
#define NET_WM_MOVERESIZE_আকার_ডান 3
#endif

#ifndef NET_WM_MOVERESIZE_আকার_BOTTOMRIGHT
#define NET_WM_MOVERESIZE_আকার_BOTTOMRIGHT 4
#endif

#ifndef NET_WM_MOVERESIZE_আকার_BOTTOM
#define NET_WM_MOVERESIZE_আকার_BOTTOM 5
#endif

#ifndef NET_WM_MOVERESIZE_আকার_BOTTOMLEFT
#define NET_WM_MOVERESIZE_আকার_BOTTOMLEFT 6
#endif

#ifndef NET_WM_MOVERESIZE_আকার_বাম
#define NET_WM_MOVERESIZE_আকার_বাম 7
#endif

#ifndef _NET_WM_MOVERESIZE_MOVE
#define _NET_WM_MOVERESIZE_MOVE 8
#endif

প্রকারলেখ কাঠামো
{
    unsigned অক্ষর *তথ্য;
    পূর্ণসংখ্যা format, গুনতি;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
স্থির শূন্য X11_ReadProperty(SDL_x11Prop *p, Display *disp, Window w, Atom prop)
{
    unsigned অক্ষর *ret = ফাঁকা;
    Atom type;
    পূর্ণসংখ্যা fmt;
    unsigned long গুনতি;
    unsigned long bytes_বাম;
    পূর্ণসংখ্যা bytes_fetch = 0;

    করো {
        যদি (ret) {
            X11_XFree(ret);
        }
        X11_XGetWindowProperty(disp, w, prop, 0, bytes_fetch, False, AnyPropertyType, &type, &fmt, &গুনতি, &bytes_বাম, &ret);
        bytes_fetch += bytes_বাম;
    } যখন (bytes_বাম != 0);

    p->তথ্য = ret;
    p->format = fmt;
    p->গুনতি = গুনতি;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
স্থির Atom X11_PickTarget(Display *disp, Atom list[], পূর্ণসংখ্যা list_গুনতি)
{
    ধ্রুবক Atom text_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    জন্য (পূর্ণসংখ্যা i = 0; i < list_গুনতি && request != text_uri_request; i++) {
        অক্ষর *name = X11_XGetAtomName(disp, list[i]);
        // Preferred MIME targets
        যদি ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            যদি (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        যদি ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            যদি (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    যদি (preferred != None && request != text_uri_request) {
        request = preferred;
    }
    ফেরত request;
}

/* Wrapper for X11_PickTarget for a maximum of three targets, a special
   case in the Xdnd protocol */
স্থির Atom X11_PickTargetFromAtoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    পূর্ণসংখ্যা গুনতি = 0;
    Atom atom[3];
    যদি (a0 != None) {
        atom[গুনতি++] = a0;
    }
    যদি (a1 != None) {
        atom[গুনতি++] = a1;
    }
    যদি (a2 != None) {
        atom[গুনতি++] = a2;
    }
    ফেরত X11_PickTarget(disp, atom, গুনতি);
}

কাঠামো চাবি_Repeat_Check_তথ্য
{
    XEvent *event;
    bool found;
};

স্থির Bool X11_চাবি_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    কাঠামো চাবি_Repeat_Check_তথ্য *d = (কাঠামো চাবি_Repeat_Check_তথ্য *)arg;
    যদি (chkev->type == চাবি_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.time - d->event->xkey.time < 2) {
        d->found = true;
    }
    ফেরত False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
স্থির bool X11_চাবি_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    কাঠামো চাবি_Repeat_Check_তথ্য d;
    d.event = event;
    d.found = false;
    যদি (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_চাবি_Repeat_Check_If_Event, (XPointer)&d);
    }
    ফেরত d.found;
}

bool X11_IsWheelEvent(পূর্ণসংখ্যা button, পূর্ণসংখ্যা *xticks, পূর্ণসংখ্যা *yticks)
{
    /* according to the xlib docs, no specific mouse wheel events exist.
       However, the defacto standard is that the vertical wheel is X buttons
       4 (up) and 5 (down) and a horizontal wheel is 6 (left) and 7 (right). */

    // Xlib defines "Button1" through 5, so we just use literals here.
    নির্বাচন (button) {
    ক্ষেত্র 4:
        *yticks = 1;
        ফেরত true;
    ক্ষেত্র 5:
        *yticks = -1;
        ফেরত true;
    ক্ষেত্র 6:
        *xticks = 1;
        ফেরত true;
    ক্ষেত্র 7:
        *xticks = -1;
        ফেরত true;
    পূর্বনির্ধারিত:
        বিরতি;
    }
    ফেরত false;
}

// An X11 event hook
স্থির SDL_X11EventHook g_X11EventHook = ফাঁকা;
স্থির শূন্য *g_X11_Event_Hook_তথ্য = ফাঁকা;

শূন্য SDL_SetX11EventHook(SDL_X11EventHook callback, শূন্য *userdata)
{
    g_X11EventHook = callback;
    g_X11_Event_Hook_তথ্য = userdata;
}

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
স্থির শূন্য X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_Video_তথ্য *videodata = _this->internal;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    যদি (X11_XGet_Event_তথ্য(videodata->display, cookie)) {
        যদি (!g_X11EventHook || g_X11EventHook(g_X11_Event_Hook_তথ্য, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFree_Event_তথ্য(videodata->display, cookie);
    }
}
#endif // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

স্থির শূন্য X11_Update_System_চাবি_Modifiers(SDL_Video_তথ্য *viddata)
{
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    যদি (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        যদি (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.base_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } অন্যথা
#endif
        {
        Window junk_window;
        পূর্ণসংখ্যা x, y;
        unsigned পূর্ণসংখ্যা mod_mask;

        X11_XQueryPointer(viddata->display, Default_মূল_Window(viddata->display), &junk_window, &junk_window, &x, &y, &x, &y, &mod_mask);
        viddata->keyboard.pressed_modifiers = mod_mask & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        viddata->keyboard.locked_modifiers = mod_mask & (LockMask | viddata->keyboard.numlock_mask | viddata->keyboard.scrolllock_mask);
    }
}

স্থির শূন্য X11_ReconcileModifiers(SDL_Video_তথ্য *viddata, bool চাবি_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    যদি (চাবি_pressed) {
        যদি (viddata->keyboard.pressed_modifiers & ShiftMask) {
            যদি (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_SHIFT);
            }
        }

        যদি (viddata->keyboard.pressed_modifiers & ControlMask) {
            যদি (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        যদি (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            যদি (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        যদি (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            যদি (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } অন্যথা {
        যদি (viddata->keyboard.pressed_modifiers & ShiftMask) {
            যদি (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } অন্যথা {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        যদি (viddata->keyboard.pressed_modifiers & ControlMask) {
            যদি (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } অন্যথা {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        যদি (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_mask) {
            যদি (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } অন্যথা {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        যদি (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_mask) {
            যদি (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } অন্যথা {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        যদি (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_mask) {
            যদি (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_MODE)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_MODE;
            }
        } অন্যথা {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        যদি (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_mask) {
            যদি (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } অন্যথা {
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
    যদি (viddata->keyboard.locked_modifiers & ShiftMask) {
        যদি (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_SHIFT);
        } অন্যথা যদি (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_SHIFT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } অন্যথা {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    যদি (viddata->keyboard.locked_modifiers & ControlMask) {
        যদি (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } অন্যথা যদি (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } অন্যথা {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    যদি (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_mask) {
        যদি (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } অন্যথা যদি (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } অন্যথা {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    যদি (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_mask) {
        যদি (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } অন্যথা যদি (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } অন্যথা {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    যদি (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_MODE;
    } অন্যথা {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_MODE;
    }

    যদি (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } অন্যথা {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    যদি (viddata->keyboard.locked_modifiers & LockMask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } অন্যথা {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    যদি (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_অঙ্ক;
    } অন্যথা {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_অঙ্ক;
    }

    যদি (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } অন্যথা {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_SetModState(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

স্থির শূন্য X11_Handle_Modifier_চাবিগুলি(SDL_Video_তথ্য *viddata, SDL_Scancode scancode, bool pressed)
{
    ধ্রুবক SDL_Keycode keycode = SDL_Get_চাবি_From_Scancode(scancode, SDL_KMOD_NONE, false);
    SDL_Keymod mod = SDL_KMOD_NONE;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is checked.
     */
    নির্বাচন (keycode) {
    ক্ষেত্র SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        বিরতি;
    ক্ষেত্র SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        বিরতি;
    ক্ষেত্র SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        বিরতি;
    ক্ষেত্র SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        বিরতি;
    ক্ষেত্র SDLK_LALT:
        mod = SDL_KMOD_LALT;
        বিরতি;
    ক্ষেত্র SDLK_RALT:
        mod = SDL_KMOD_RALT;
        বিরতি;
    ক্ষেত্র SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        বিরতি;
    ক্ষেত্র SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        বিরতি;
    ক্ষেত্র SDLK_MODE:
        mod = SDL_KMOD_MODE;
        বিরতি;
    ক্ষেত্র SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        বিরতি;
    ক্ষেত্র SDLK_CAPSLOCK:
    ক্ষেত্র SDLK_NUMLOCKCLEAR:
    ক্ষেত্র SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        যদি (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            unsigned পূর্ণসংখ্যা cur_mask = viddata->keyboard.locked_modifiers;
            X11_Update_System_চাবি_Modifiers(viddata);

            যদি (viddata->keyboard.locked_modifiers & LockMask) {
                cur_mask |= LockMask;
            } অন্যথা {
                cur_mask &= ~LockMask;
            }
            যদি (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_mask) {
                cur_mask |= viddata->keyboard.numlock_mask;
            } অন্যথা {
                cur_mask &= ~viddata->keyboard.numlock_mask;
            }
            যদি (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_mask) {
                cur_mask |= viddata->keyboard.scrolllock_mask;
            } অন্যথা {
                cur_mask &= ~viddata->keyboard.scrolllock_mask;
            }

            viddata->keyboard.locked_modifiers = cur_mask;
        }
    } বিরতি;
    পূর্বনির্ধারিত:
        ফেরত;
    }

    যদি (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } অন্যথা {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

শূন্য X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    Display *display = videodata->display;
    অক্ষর চাবিগুলি[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_চাবি_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_অঙ্ক | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= LockMask | videodata->keyboard.numlock_mask| videodata->keyboard.scrolllock_mask;

    X11_XQueryKeymap(display, চাবিগুলি);

    ধ্রুবক bool *keystate = SDL_GetKeyboardState(ফাঁকা);
    জন্য (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.চাবি_layout); ++keycode) {
        ধ্রুবক SDL_Scancode scancode = videodata->keyboard.চাবি_layout[keycode];
        ধ্রুবক bool x11_চাবি_Pressed = (চাবিগুলি[keycode / 8] & (1 << (keycode % 8))) != 0;
        ধ্রুবক bool sdl_চাবি_Pressed = keystate[scancode];

        যদি (x11_চাবি_Pressed && !sdl_চাবি_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            নির্বাচন (SDL_Get_চাবি_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            ক্ষেত্র SDLK_LCTRL:
            ক্ষেত্র SDLK_RCTRL:
            ক্ষেত্র SDLK_LSHIFT:
            ক্ষেত্র SDLK_RSHIFT:
            ক্ষেত্র SDLK_LALT:
            ক্ষেত্র SDLK_RALT:
            ক্ষেত্র SDLK_LGUI:
            ক্ষেত্র SDLK_RGUI:
            ক্ষেত্র SDLK_MODE:
            ক্ষেত্র SDLK_LEVEL5_SHIFT:
                X11_Handle_Modifier_চাবিগুলি(videodata, scancode, true);
                SDL_Send_Keyboard_চাবি_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                বিরতি;
            পূর্বনির্ধারিত:
                বিরতি;
            }
        } অন্যথা যদি (!x11_চাবি_Pressed && sdl_চাবি_Pressed) {
            X11_Handle_Modifier_চাবিগুলি(videodata, scancode, false);
            SDL_Send_Keyboard_চাবি_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_চাবি_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

স্থির শূন্য X11_DispatchFocusIn(SDL_VideoDevice *_this, SDL_Window_তথ্য *তথ্য)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", তথ্য->xwindow);
#endif
    SDL_SetKeyboardFocus(তথ্য->window);
    X11_ReconcileKeyboardState(_this);
#ifdef X_HAVE_UTF8_STRING
    যদি (তথ্য->ic) {
        X11_XSetICFocus(তথ্য->ic);
    }
#endif
    যদি (তথ্য->flashing_window) {
        X11_FlashWindow(_this, তথ্য->window, SDL_FLASH_CANCEL);
    }
}

স্থির শূন্য X11_DispatchFocusOut(SDL_VideoDevice *_this, SDL_Window_তথ্য *তথ্য)
{
#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", তথ্য->xwindow);
#endif
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    যদি (তথ্য->window == SDL_GetKeyboardFocus()) {
        SDL_SetKeyboardFocus(ফাঁকা);
    }
#ifdef X_HAVE_UTF8_STRING
    যদি (তথ্য->ic) {
        X11_XUnsetICFocus(তথ্য->ic);
    }
#endif
}

স্থির শূন্য X11_DispatchMapNotify(SDL_Window_তথ্য *তথ্য)
{
    SDL_Window *window = তথ্য->window;

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    তথ্য->was_shown = true;

    // This may be sent when restoring a minimized window.
    যদি (window->flags & SDL_WINDOW_MINIMIZED) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }

    যদি (window->flags & SDL_WINDOW_প্রবেশ_FOCUS) {
        SDL_UpdateWindowGrab(window);
    }
}

স্থির শূন্য X11_DispatchUnmapNotify(SDL_Window_তথ্য *তথ্য)
{
    SDL_Window *window = তথ্য->window;

    // This may be sent when minimizing a window.
    যদি (!window->is_hiding) {
        SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
    } অন্যথা {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    }
}

স্থির শূন্য DispatchWindowMove(SDL_VideoDevice *_this, ধ্রুবক SDL_Window_তথ্য *তথ্য, ধ্রুবক SDL_Point *point)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    SDL_Window *window = তথ্য->window;
    Display *display = videodata->display;
    XEvent evt;

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrabPointer(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = ClientMessage;
    evt.xclient.window = তথ্য->xwindow;
    evt.xclient.message_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.তথ্য.l[0] = (size_t)window->x + point->x;
    evt.xclient.তথ্য.l[1] = (size_t)window->y + point->y;
    evt.xclient.তথ্য.l[2] = _NET_WM_MOVERESIZE_MOVE;
    evt.xclient.তথ্য.l[3] = Button1;
    evt.xclient.তথ্য.l[4] = 0;
    X11_XSendEvent(display, Default_মূল_Window(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

স্থির শূন্য ScheduleWindowMove(SDL_VideoDevice *_this, SDL_Window_তথ্য *তথ্য, ধ্রুবক SDL_Point *point)
{
    তথ্য->pending_move = true;
    তথ্য->pending_move_point = *point;
}

স্থির শূন্য InitiateWindowResize(SDL_VideoDevice *_this, ধ্রুবক SDL_Window_তথ্য *তথ্য, ধ্রুবক SDL_Point *point, পূর্ণসংখ্যা direction)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    SDL_Window *window = তথ্য->window;
    Display *display = videodata->display;
    XEvent evt;

    যদি (direction < NET_WM_MOVERESIZE_আকার_TOPLEFT || direction > NET_WM_MOVERESIZE_আকার_বাম) {
        ফেরত;
    }

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrabPointer(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = ClientMessage;
    evt.xclient.window = তথ্য->xwindow;
    evt.xclient.message_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.তথ্য.l[0] = (size_t)window->x + point->x;
    evt.xclient.তথ্য.l[1] = (size_t)window->y + point->y;
    evt.xclient.তথ্য.l[2] = direction;
    evt.xclient.তথ্য.l[3] = Button1;
    evt.xclient.তথ্য.l[4] = 0;
    X11_XSendEvent(display, Default_মূল_Window(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &evt);

    X11_XSync(display, 0);
}

bool X11_ProcessHitTest(SDL_VideoDevice *_this, SDL_Window_তথ্য *তথ্য, ধ্রুবক দশমিক x, ধ্রুবক দশমিক y, bool force_new_ফলাফল)
{
    SDL_Window *window = তথ্য->window;
    যদি (!window->hit_test) ফেরত false;
    ধ্রুবক SDL_Point point = { (পূর্ণসংখ্যা)x, (পূর্ণসংখ্যা)y };
    SDL_Hit_Test_ফলাফল rc = window->hit_test(window, &point, window->hit_test_তথ্য);
    যদি (!force_new_ফলাফল && rc == তথ্য->hit_test_ফলাফল) {
        ফেরত true;
    }
    X11_SetHitTestCursor(rc);
    তথ্য->hit_test_ফলাফল = rc;
    ফেরত true;
}

bool X11_TriggerHitTestAction(SDL_VideoDevice *_this, SDL_Window_তথ্য *তথ্য, ধ্রুবক দশমিক x, ধ্রুবক দশমিক y)
{
    SDL_Window *window = তথ্য->window;

    যদি (window->hit_test) {
        ধ্রুবক SDL_Point point = { (পূর্ণসংখ্যা)x, (পূর্ণসংখ্যা)y };
        স্থির ধ্রুবক পূর্ণসংখ্যা directions[] = {
            NET_WM_MOVERESIZE_আকার_TOPLEFT, NET_WM_MOVERESIZE_আকার_শীর্ষ,
            NET_WM_MOVERESIZE_আকার_TOPRIGHT, NET_WM_MOVERESIZE_আকার_ডান,
            NET_WM_MOVERESIZE_আকার_BOTTOMRIGHT, NET_WM_MOVERESIZE_আকার_BOTTOM,
            NET_WM_MOVERESIZE_আকার_BOTTOMLEFT, NET_WM_MOVERESIZE_আকার_বাম
        };

        নির্বাচন (তথ্য->hit_test_ফলাফল) {
        ক্ষেত্র SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            যদি (তথ্য->window->flags & SDL_WINDOW_প্রবেশ_FOCUS) {
                DispatchWindowMove(_this, তথ্য, &point);
            } অন্যথা {
                ScheduleWindowMove(_this, তথ্য, &point);
            }
            ফেরত true;

        ক্ষেত্র SDL_HITTEST_RESIZE_TOPLEFT:
        ক্ষেত্র SDL_HITTEST_RESIZE_শীর্ষ:
        ক্ষেত্র SDL_HITTEST_RESIZE_TOPRIGHT:
        ক্ষেত্র SDL_HITTEST_RESIZE_ডান:
        ক্ষেত্র SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        ক্ষেত্র SDL_HITTEST_RESIZE_BOTTOM:
        ক্ষেত্র SDL_HITTEST_RESIZE_BOTTOMLEFT:
        ক্ষেত্র SDL_HITTEST_RESIZE_বাম:
            InitiateWindowResize(_this, তথ্য, &point, directions[তথ্য->hit_test_ফলাফল - SDL_HITTEST_RESIZE_TOPLEFT]);
            ফেরত true;

        পূর্বনির্ধারিত:
            ফেরত false;
        }
    }

    ফেরত false;
}

স্থির শূন্য X11_UpdateUserTime(SDL_Window_তথ্য *তথ্য, ধ্রুবক unsigned long latest)
{
    যদি (latest && (latest != তথ্য->user_time)) {
        SDL_Video_তথ্য *videodata = তথ্য->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, তথ্য->xwindow, videodata->atoms._NET_WM_USER_TIME,
                            XA_CARDINAL, 32, PropModeReplace,
                            (ধ্রুবক unsigned অক্ষর *)&latest, 1);
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", তথ্য->xwindow, latest);
#endif
        তথ্য->user_time = latest;
    }
}

স্থির unsigned অক্ষর x11_last_error;
স্থির পূর্ণসংখ্যা BadWindowErrorHandler(Display *d, XErrorEvent *e)
{
    x11_last_error = e->error_code;

    // Ignore BadWindow in cases where it's not fatal.
    যদি (e->error_code != BadWindow) {
        অক্ষর err_বার্তা[128];
        X11_XGetErrorText(d, e->error_code, err_বার্তা, আকার(err_বার্তা));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_code, err_বার্তা, e->request_code);
    }
    ফেরত 0;
}

স্থির শূন্য X11_HandleClipboardEvent(SDL_VideoDevice *_this, ধ্রুবক XEvent *xevent)
{
    পূর্ণসংখ্যা i;
    SDL_Video_তথ্য *videodata = _this->internal;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_window != None);
    SDL_assert(xevent->xany.window == videodata->clipboard_window);

    নির্বাচন (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    ক্ষেত্র SelectionRequest:
    {
        ধ্রুবক XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        পূর্ণসংখ্যা mime_formats;
        unsigned অক্ষর *seln_তথ্য;
        size_t seln_দৈর্ঘ্য = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_Clipboard_তথ্য *clipboard;

#ifdef DEBUG_XEVENTS
        অক্ষর *atom_name;
        atom_name = X11_XGetAtomName(display, req->target);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->target, atom_name);
        যদি (atom_name) {
            X11_XFree(atom_name);
        }
#endif

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_last_error = 0;
        XErrorHandler পূর্ব_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

        যদি (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } অন্যথা {
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

        যদি (req->target == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_গুনতি + 1) * আকার(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            জন্য (i = 0; i < clipboard->mime_গুনতি; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, PropModeReplace,
                                (unsigned অক্ষর *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.target = XA_TARGETS;
            SDL_free(supportedFormats);
        } অন্যথা {
            যদি (clipboard->callback) {
                জন্য (i = 0; i < clipboard->mime_গুনতি; ++i) {
                    ধ্রুবক অক্ষর *mime_type = clipboard->mime_types[i];
                    যদি (X11_XInternAtom(display, mime_type, False) != req->target) {
                        চালু;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_তথ্য = (unsigned অক্ষর *)clipboard->callback(clipboard->userdata, mime_type, &seln_দৈর্ঘ্য);
                    যদি (seln_তথ্য) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->target, 8, PropModeReplace,
                                            seln_তথ্য, seln_দৈর্ঘ্য);
                        sevent.xselection.property = req->property;
                        sevent.xselection.target = req->target;
                    }
                    বিরতি;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(পূর্ব_handler);
    } বিরতি;

    ক্ষেত্র SelectionNotify:
    {
        ধ্রুবক XSelectionEvent *xsel = &xevent->xselection;
#ifdef DEBUG_XEVENTS
        ধ্রুবক অক্ষর *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        ধ্রুবক অক্ষর *targetName = xsel->target ? X11_XGetAtomName(display, xsel->target) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, targetName, propName);
#endif
        যদি (xsel->target == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            unsigned অক্ষর *তথ্য = ফাঁকা;
            পূর্ণসংখ্যা format_property = 0;
            unsigned long দৈর্ঘ্য = 0;
            unsigned long bytes_বাম = 0;
            পূর্ণসংখ্যা j;

            X11_XGetWindowProperty(display, GetWindow(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &দৈর্ঘ্য, &bytes_বাম, &তথ্য);

            পূর্ণসংখ্যা allocationsize = (দৈর্ঘ্য + 1) * আকার(অক্ষর *);
            জন্য (j = 0, patom = (Atom *)তথ্য; j < দৈর্ঘ্য; j++, patom++) {
                অক্ষর *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            অক্ষর **new_mime_types = SDL_AllocateTemporaryMemory(allocationsize);
            যদি (new_mime_types) {
                অক্ষর *strPtr = (অক্ষর *)(new_mime_types + দৈর্ঘ্য + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                জন্য (j = 0, patom = (Atom *)তথ্য; j < দৈর্ঘ্য; j++, patom++) {
                    অক্ষর *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    ধ্রুবক size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[দৈর্ঘ্য] = ফাঁকা;

                SDL_SendClipboardUpdate(false, new_mime_types, দৈর্ঘ্য);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            যদি (তথ্য) {
                X11_XFree(তথ্য);
            }
        }

        videodata->selection_waiting = false;
    } বিরতি;

    ক্ষেত্র SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_Clipboard_তথ্য *clipboard = ফাঁকা;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.target);
#endif

        যদি (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } অন্যথা যদি (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        যদি (clipboard && clipboard->callback) {
            যদি (clipboard->sequence) {
                SDL_Cancel_Clipboard_তথ্য(clipboard->sequence);
            } অন্যথা {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } বিরতি;

    ক্ষেত্র PropertyNotify:
    {
        অক্ষর *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        যদি (SDL_strncmp(name_of_atom, "SDL_SELECTION", আকার("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_মান) {
            videodata->selection_incr_waiting = false;
        }

        যদি (name_of_atom) {
            X11_XFree(name_of_atom);
        }
    } বিরতি;
    }
}

স্থির Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    ফেরত ev->type == MapNotify &&
           ev->xmap.window == unmap->window &&
           ev->xmap.serial == unmap->serial;
}

স্থির Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    ফেরত ev->type == ReparentNotify &&
           ev->xreparent.window == unmap->window &&
           ev->xreparent.serial == unmap->serial;
}

স্থির bool Is_উপরের_Latin1(ধ্রুবক অক্ষর *string, পূর্ণসংখ্যা দৈর্ঘ্য)
{
    যখন (দৈর্ঘ্য-- > 0) {
        Uint8 ch = (Uint8)*string;
        যদি (ch >= 0x80) {
            ফেরত true;
        }
        ++string;
    }
    ফেরত false;
}

স্থির পূর্ণসংখ্যা XLookupStringAsUTF8(XKeyEvent *event_struct, অক্ষর *বাফার_return, পূর্ণসংখ্যা bytes_বাফার, চাবি_Sym *keysym_return, XComposeStatus *status_in_out)
{
    পূর্ণসংখ্যা ফলাফল = X11_XLookupString(event_struct, বাফার_return, bytes_বাফার, keysym_return, status_in_out);
    যদি (Is_উপরের_Latin1(বাফার_return, ফলাফল)) {
        অক্ষর *utf8_text = SDL_iconv_string("UTF-8", "ISO-8859-1", বাফার_return, ফলাফল + 1);
        যদি (utf8_text) {
            SDL_strlcpy(বাফার_return, utf8_text, bytes_বাফার);
            SDL_free(utf8_text);
            ফেরত SDL_strlen(বাফার_return);
        } অন্যথা {
            ফেরত 0;
        }
    }
    ফেরত ফলাফল;
}

SDL_Window_তথ্য *X11_FindWindow(SDL_Video_তথ্য *videodata, Window window)
{
    যদি (videodata && videodata->windowlist) {
        জন্য (পূর্ণসংখ্যা i = 0; i < videodata->numwindows; ++i) {
            যদি ((videodata->windowlist[i] != ফাঁকা) &&
                (videodata->windowlist[i]->xwindow == window)) {
                ফেরত videodata->windowlist[i];
            }
        }
    }
    ফেরত ফাঁকা;
}

Uint64 X11_GetEventTimestamp(unsigned long time)
{
    // FIXME: Get the event time in the SDL tick time base
    ফেরত SDL_GetTicksNS();
}

শূন্য X11_Handle_চাবি_Event(SDL_VideoDevice *_this, SDL_Window_তথ্য *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    Display *display = videodata->display;
    চাবি_Code_2 keycode = xevent->xkey.keycode;
    চাবি_Sym keysym = No_প্রতীক;
    পূর্ণসংখ্যা text_দৈর্ঘ্য = 0;
    অক্ষর text[64];
    Status status = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == চাবি_Press);
    SDL_Scancode scancode = videodata->keyboard.চাবি_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.window, (xevent->type == চাবি_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#endif
#ifdef DEBUG_SCANCODES
    যদি (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        পূর্ণসংখ্যা min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_চাবি_Code_To_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysymToString(keysym));
    }
#endif // DEBUG SCANCODES

    text[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    যদি (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (ShiftMask | ControlMask | Mod1Mask | Mod3Mask | Mod4Mask | Mod5Mask);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (LockMask | videodata->keyboard.numlock_mask | videodata->keyboard.scrolllock_mask);
    }

    যদি (SDL_Text_প্রবেশ_Active(windowdata->window)) {
        // filter events catches XIM events and sends them to the correct handler
        যদি (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            handled_by_ime = true;
        }

        যদি (!handled_by_ime) {
#ifdef X_HAVE_UTF8_STRING
            যদি (windowdata->ic && xevent->type == চাবি_Press) {
                text_দৈর্ঘ্য = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, text, আকার(text) - 1,
                                      &keysym, &status);
            } অন্যথা {
                text_দৈর্ঘ্য = XLookupStringAsUTF8(&xevent->xkey, text, আকার(text) - 1, &keysym, ফাঁকা);
            }
#অন্যথা
            text_দৈর্ঘ্য = XLookupStringAsUTF8(&xevent->xkey, text, আকার(text) - 1, &keysym, ফাঁকা);
#endif
        }
    }

    যদি (!handled_by_ime) {
        যদি (pressed) {
            X11_Handle_Modifier_চাবিগুলি(videodata, scancode, true);
            SDL_Send_Keyboard_চাবি_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            যদি (*text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                text[text_দৈর্ঘ্য] = '\0';
                X11_ClearComposition(windowdata);
                SDL_SendKeyboardText(text);
            }
        } অন্যথা {
            যদি (X11_চাবি_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                ফেরত;
            }

            X11_Handle_Modifier_চাবিগুলি(videodata, scancode, false);
            SDL_Send_Keyboard_চাবি_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    যদি (pressed) {
        X11_UpdateUserTime(windowdata, xevent->xkey.time);
    }
}

শূন্য X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_Window_তথ্য *windowdata, SDL_MouseID mouseID, পূর্ণসংখ্যা button, দশমিক x, দশমিক y, unsigned long time, unsigned long serial)
{
    SDL_Window *window = windowdata->window;
    পূর্ণসংখ্যা xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#endif

    SDL_Mouse *mouse = SDL_GetMouse();
    যদি (!mouse->relative_mode && (x != mouse->x || y != mouse->y)) {
        X11_ProcessHitTest(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, window, mouseID, false, x, y);
    }

    যদি (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, window, mouseID, (দশমিক)-xticks, (দশমিক)yticks, SDL_MOUSEWHEEL_NORMAL);
    } অন্যথা {
        যদি (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        যদি (button == Button1) {
            যদি (X11_TriggerHitTestAction(_this, windowdata, x, y)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIT_TEST, 0, 0);
                ফেরত; // don't pass this event on to app.
            }
        }
        যদি (windowdata->last_focus_event_time) {
            ধ্রুবক পূর্ণসংখ্যা X11_FOCUS_CLICK_TIMEOUT = 10;
            যদি (SDL_GetTicks() < (windowdata->last_focus_event_time + X11_FOCUS_CLICK_TIMEOUT)) {
                যদি (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->last_focus_event_time = 0;
        }
        যদি (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, window, mouseID, button, true);
        }
    }
    X11_UpdateUserTime(windowdata, time);
}

শূন্য X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_Window_তথ্য *windowdata, SDL_MouseID mouseID, পূর্ণসংখ্যা button, unsigned long time)
{
    SDL_Window *window = windowdata->window;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    পূর্ণসংখ্যা xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#ifdef DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#endif
    যদি (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        যদি (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, window, mouseID, button, false);

        যদি (window->internal->pending_grab) {
            X11_SetWindowMouseGrab(_this, window, true);
        }
    }
}

শূন্য X11_Get_Border_মানসমূহ(SDL_Window_তথ্য *তথ্য)
{
    SDL_Video_তথ্য *videodata = তথ্য->videodata;
    Display *display = videodata->display;

    Atom type;
    পূর্ণসংখ্যা format;
    unsigned long nitems, bytes_after;
    unsigned অক্ষর *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    যদি (!(তথ্য->window->flags & SDL_WINDOW_BORDERLESS)) {
        যদি (X11_XGetWindowProperty(display, তথ্য->xwindow, videodata->atoms._NET_FRAME_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &bytes_after, &property) == Success) {
            যদি (type != None && nitems == 4) {
                তথ্য->border_বাম = (পূর্ণসংখ্যা)((long *)property)[0];
                তথ্য->border_ডান = (পূর্ণসংখ্যা)((long *)property)[1];
                তথ্য->border_শীর্ষ = (পূর্ণসংখ্যা)((long *)property)[2];
                তথ্য->border_bottom = (পূর্ণসংখ্যা)((long *)property)[3];
            }
            X11_XFree(property);

#ifdef DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", তথ্য->border_বাম, তথ্য->border_ডান, তথ্য->border_শীর্ষ, তথ্য->border_bottom);
#endif
        }
    } অন্যথা {
        তথ্য->border_বাম = তথ্য->border_শীর্ষ = তথ্য->border_ডান = তথ্য->border_bottom = 0;
    }
}

শূন্য X11_EmitConfigureNotifyEvents(SDL_Window_তথ্য *তথ্য, XConfigureEvent *xevent)
{
    যদি (!তথ্য->আকার_move_event_flags) {
        পূর্ণসংখ্যা x = xevent->x;
        পূর্ণসংখ্যা y = xevent->y;

        যদি (xevent->x != তথ্য->last_xconfigure.x ||
            xevent->y != তথ্য->last_xconfigure.y) {
            তথ্য->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_GlobalToRelativeForWindow(তথ্য->window, x, y, &x, &y);
        SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_MOVED, x, y);

        জন্য (SDL_Window *w = তথ্য->window->first_child; w; w = w->পরবর্তী_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            যদি (SDL_WINDOW_IS_POPUP(w) && !(w->flags & SDL_WINDOW_HIDDEN)) {
                X11_UpdateWindowPosition(w, true);
            }
        }

        যদি (xevent->width != তথ্য->last_xconfigure.width ||
            xevent->height != তথ্য->last_xconfigure.height) {
            তথ্য->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_RESIZED, xevent->width, xevent->height);
    }

    SDL_copyp(&তথ্য->last_xconfigure, xevent);
}

স্থির শূন্য X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    Display *display;
    SDL_Window_তথ্য *তথ্য;
    XClientMessageEvent m;
    পূর্ণসংখ্যা i;

    SDL_assert(videodata != ফাঁকা);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    যদি (xevent->type != চাবি_Press && xevent->type != চাবি_Release) {
        যদি (X11_XFilterEvent(xevent, None)) {
#ifdef DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.window);
#endif
            ফেরত;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    যদি (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        ফেরত;
    }
#endif

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    যদি (g_X11EventHook) {
        যদি (!g_X11EventHook(g_X11_Event_Hook_তথ্য, xevent)) {
            ফেরত;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    যদি (videodata->xrandr_event_base && (xevent->type == (videodata->xrandr_event_base + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#endif

#ifdef DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.window);
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    যদি (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#ifdef DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#endif

        যদি (ev->subtype == XFixesSetSelectionOwnerNotify)
        {
            যদি (ev->selection != videodata->atoms.CLIPBOARD)
                ফেরত;

            যদি (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_window)
                ফেরত;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, GetWindow(_this), CurrentTime);
        }

        ফেরত;
    }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES

    যদি ((videodata->clipboard_window != None) &&
        (videodata->clipboard_window == xevent->xany.window)) {
        X11_HandleClipboardEvent(_this, xevent);
        ফেরত;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    তথ্য = X11_FindWindow(videodata, xevent->xany.window);

    যদি (!তথ্য) {
        // The window for KeymapNotify, etc events is 0
#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        যদি (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            নির্বাচন (xkbevent->any.xkb_type) {
            ক্ষেত্র XkbStateNotify:
            {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.window);
#endif
                যদি ((xkbevent->state.changed & XkbGroupStateMask) && xkbevent->state.group != videodata->keyboard.xkb.current_group) {
                    videodata->keyboard.xkb.current_group = xkbevent->state.group;
                    SDL_SetKeymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_group], true);
                }

                যদি (xkbevent->state.changed & XkbModifierStateMask) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.base_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } বিরতি;

            ক্ষেত্র XkbMapNotify:
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.window);
                SDL_FALLTHROUGH;
#endif
            ক্ষেত্র XkbNewKeyboardNotify:
            {
#ifdef DEBUG_XEVENTS
                যদি (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.window);
                }
#endif
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                যদি (xkbevent->any.serial != videodata->keyboard.xkb.last_map_serial) {
                    videodata->keyboard.xkb.last_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } বিরতি;

            পূর্বনির্ধারিত:
                বিরতি;
            }
        } অন্যথা
#endif
        যদি (xevent->type == KeymapNotify) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.window);
#endif
            যদি (SDL_GetKeyboardFocus() != ফাঁকা) {
                যদি (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } অন্যথা যদি (xevent->type == MappingNotify) {
            ধ্রুবক পূর্ণসংখ্যা request = xevent->xmapping.request;

            যদি (request == MappingPointer) {
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                X11_Xinput2UpdatePointerMapping(_this);
            } অন্যথা যদি (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#ifdef DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.window);
#endif
                যদি (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } অন্যথা যদি (xevent->type == PropertyNotify && videodata) {
            অক্ষর *name_of_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            যদি (name_of_atom) {
                যদি (SDL_startswith(name_of_atom, "_ICC_PROFILE")) {
                    XWindowAttributes attrib;
                    পূর্ণসংখ্যা screennum;
                    জন্য (i = 0; i < videodata->numwindows; ++i) {
                        যদি (videodata->windowlist[i] != ফাঁকা) {
                            তথ্য = videodata->windowlist[i];
                            X11_XGetWindowAttributes(display, তথ্য->xwindow, &attrib);
                            screennum = X11_XScreen_সংখ্যা_Of_Screen(attrib.screen);
                            যদি (screennum == 0 && SDL_strcmp(name_of_atom, "_ICC_PROFILE") == 0) {
                                SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                            } অন্যথা যদি (SDL_strncmp(name_of_atom, "_ICC_PROFILE_", আকার("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_of_atom) > আকার("_ICC_PROFILE_") - 1) {
                                পূর্ণসংখ্যা iccscreennum = SDL_atoi(&name_of_atom[আকার("_ICC_PROFILE_") - 1]);

                                যদি (screennum == iccscreennum) {
                                    SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_ICCPROF_CHANGED, 0, 0);
                                }
                            }
                        }
                    }
                } অন্যথা যদি (SDL_strcmp(name_of_atom, "_NET_WORKAREA") == 0) {
                    জন্য (i = 0; i < _this->অঙ্ক_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED, 0, 0);
                    }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
                } অন্যথা যদি (SDL_strcmp(name_of_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_of_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#endif
                }
                X11_XFree(name_of_atom);
            }
        }
        ফেরত;
    }

    নির্বাচন (xevent->type) {

        // Gaining mouse coverage?
    ক্ষেত্র EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        যদি (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        যদি (xevent->xcrossing.mode == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#endif
        SDL_SetMouseFocus(তথ্য->window);

        mouse->last_x = xevent->xcrossing.x;
        mouse->last_y = xevent->xcrossing.y;

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        {
            // Only create the barriers if we have input focus
            SDL_Window_তথ্য *windowdata = তথ্য->window->internal;
            যদি ((তথ্য->pointer_barrier_active == true) && windowdata->window->flags & SDL_WINDOW_প্রবেশ_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->window, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#endif

        যদি (!mouse->relative_mode) {
            SDL_SendMouseMotion(0, তথ্য->window, SDL_GLOBAL_MOUSE_ID, false, (দশমিক)xevent->xcrossing.x, (দশমিক)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        যদি (!(তথ্য->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
            SDL_UpdateWindowGrab(তথ্য->window);
        }

        X11_ProcessHitTest(_this, তথ্য, mouse->last_x, mouse->last_y, true);
    } বিরতি;
        // Losing mouse coverage?
    ক্ষেত্র LeaveNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.window,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.mode);
        যদি (xevent->xcrossing.mode == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        যদি (xevent->xcrossing.mode == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#endif
        যদি (!SDL_GetMouse()->relative_mode) {
            SDL_SendMouseMotion(0, তথ্য->window, SDL_GLOBAL_MOUSE_ID, false, (দশমিক)xevent->xcrossing.x, (দশমিক)xevent->xcrossing.y);
        }

        যদি (xevent->xcrossing.mode != NotifyGrab &&
            xevent->xcrossing.mode != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            যদি (!(তথ্য->window->flags & SDL_WINDOW_FULLSCREEN)) {
                X11_SetWindowKeyboardGrab(_this, তথ্য->window, false);
            }

            SDL_SetMouseFocus(ফাঁকা);
        }
    } বিরতি;

        // Gaining input focus?
    ক্ষেত্র FocusIn:
    {
        যদি (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            বিরতি;
        }

        যদি (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            বিরতি;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.window);
#endif
        যদি (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            তথ্য->pending_focus = PENDING_FOCUS_NONE;
            তথ্য->pending_focus_time = 0;
            X11_DispatchFocusIn(_this, তথ্য);
        } অন্যথা {
            তথ্য->pending_focus = PENDING_FOCUS_IN;
            তথ্য->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }
        তথ্য->last_focus_event_time = SDL_GetTicks();
    } বিরতি;

        // Losing input focus?
    ক্ষেত্র FocusOut:
    {
        যদি (xevent->xfocus.mode == NotifyGrab || xevent->xfocus.mode == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.window);
#endif
            বিরতি;
        }
        যদি (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.window);
#endif
            বিরতি;
        }
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.window);
#endif
        যদি (!videodata->last_mode_change_deadline) /* no recent mode changes */ {
            তথ্য->pending_focus = PENDING_FOCUS_NONE;
            তথ্য->pending_focus_time = 0;
            X11_DispatchFocusOut(_this, তথ্য);
        } অন্যথা {
            তথ্য->pending_focus = PENDING_FOCUS_OUT;
            তথ্য->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        যদি (তথ্য->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, তথ্য->window, ফাঁকা, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } বিরতি;


        // Have we been iconified?
    ক্ষেত্র UnmapNotify:
    {
        XEvent ev;

#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.window);
#endif

        যদি (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } অন্যথা {
            X11_DispatchUnmapNotify(তথ্য);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        যদি (তথ্য->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, তথ্য->window, ফাঁকা, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } বিরতি;

        // Have we been restored?
    ক্ষেত্র MapNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.window);
#endif
        X11_DispatchMapNotify(তথ্য);

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        যদি (তথ্য->pointer_barrier_active == true) {
            X11_ConfineCursorWithFlags(_this, তথ্য->window, &তথ্য->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
    } বিরতি;

        // Have we been resized or moved?
    ক্ষেত্র ConfigureNotify:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.window,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.width, xevent->xconfigure.height);
#endif
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        যদি (!xevent->xconfigure.send_event) {
            unsigned পূর্ণসংখ্যা অঙ্ক_Children;
            Window ChildReturn, মূল_2, Parent;
            Window *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_last_error = 0;
            XErrorHandler পূর্ব_handler = X11_XSetErrorHandler(BadWindowErrorHandler);

            X11_XQuery_বৃক্ষ(তথ্য->videodata->display, xevent->xconfigure.window, &মূল_2, &Parent, &Children, &অঙ্ক_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      Parent, Default_মূল_Window(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &ChildReturn);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(পূর্ব_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            যদি (x11_last_error == BadWindow) {
                বিরতি;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        ধ্রুবক SDL_WindowFlags changed = X11_GetNetWMState(_this, তথ্য->window, xevent->xproperty.window) ^ তথ্য->window->flags;
        যদি (changed & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) {
            SDL_copyp(&তথ্য->pending_xconfigure, &xevent->xconfigure);
            তথ্য->emit_আকার_move_after_property_notify = true;
        }

        যদি (!তথ্য->emit_আকার_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(তথ্য, &xevent->xconfigure);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(তথ্য->window, &xevent->xconfigure);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } বিরতি;

        // Have we been requested to quit (or another client message?)
    ক্ষেত্র ClientMessage:
    {
        স্থির পূর্ণসংখ্যা xdnd_version = 0;

        যদি (xevent->xclient.message_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.তথ্য.l[1] & 1;
            তথ্য->xdnd_source = xevent->xclient.তথ্য.l[0];
            xdnd_version = (xevent->xclient.তথ্য.l[1] >> 24);
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", তথ্য->xdnd_source);
            SDL_Log("Protocol version to use : %d", xdnd_version);
            SDL_Log("More then 3 data types : %d", (পূর্ণসংখ্যা)use_list);
#endif

            যদি (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, তথ্য->xdnd_source, videodata->atoms.XdndTypeList);
                // pick one
                তথ্য->xdnd_req = X11_PickTarget(display, (Atom *)p.তথ্য, p.গুনতি);
                X11_XFree(p.তথ্য);
            } অন্যথা {
                // pick from list of three
                তথ্য->xdnd_req = X11_PickTargetFromAtoms(display, xevent->xclient.তথ্য.l[2], xevent->xclient.তথ্য.l[3], xevent->xclient.তথ্য.l[4]);
            }
        } অন্যথা যদি (xevent->xclient.message_type == videodata->atoms.XdndLeave) {
#ifdef DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.তথ্য.l[0]);
#endif
            SDL_SendDropComplete(তথ্য->window);
        } অন্যথা যদি (xevent->xclient.message_type == videodata->atoms.XdndPosition) {

#ifdef DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            যদি (xdnd_version >= 2) {
                act = xevent->xclient.তথ্য.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#endif
            {
                // Drag and Drop position
                পূর্ণসংখ্যা মূল_x, মূল_y, window_x, window_y;
                Window ChildReturn;
                মূল_x = xevent->xclient.তথ্য.l[2] >> 16;
                মূল_y = xevent->xclient.তথ্য.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_মূল_Window(display), তথ্য->xwindow,
                                          মূল_x, মূল_y, &window_x, &window_y, &ChildReturn);

                SDL_SendDropPosition(তথ্য->window, (দশমিক)window_x, (দশমিক)window_y);
            }

            // reply with status
            SDL_zero(m);
            m.type = ClientMessage;
            m.display = xevent->xclient.display;
            m.window = xevent->xclient.তথ্য.l[0];
            m.message_type = videodata->atoms.XdndStatus;
            m.format = 32;
            m.তথ্য.l[0] = তথ্য->xwindow;
            m.তথ্য.l[1] = (তথ্য->xdnd_req != None);
            m.তথ্য.l[2] = 0; // specify an empty rectangle
            m.তথ্য.l[3] = 0;
            m.তথ্য.l[4] = videodata->atoms.XdndActionCopy; // we only accept copying anyway

            X11_XSendEvent(display, xevent->xclient.তথ্য.l[0], False, NoEventMask, (XEvent *)&m);
            X11_XFlush(display);
        } অন্যথা যদি (xevent->xclient.message_type == videodata->atoms.XdndDrop) {
            যদি (তথ্য->xdnd_req == None) {
                // say again - not interested!
                SDL_zero(m);
                m.type = ClientMessage;
                m.display = xevent->xclient.display;
                m.window = xevent->xclient.তথ্য.l[0];
                m.message_type = videodata->atoms.XdndFinished;
                m.format = 32;
                m.তথ্য.l[0] = তথ্য->xwindow;
                m.তথ্য.l[1] = 0;
                m.তথ্য.l[2] = None; // fail!
                X11_XSendEvent(display, xevent->xclient.তথ্য.l[0], False, NoEventMask, (XEvent *)&m);
            } অন্যথা {
                // convert
                যদি (xdnd_version >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, তথ্য->xdnd_req, videodata->atoms.PRIMARY, তথ্য->xwindow, xevent->xclient.তথ্য.l[2]);
                } অন্যথা {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, তথ্য->xdnd_req, videodata->atoms.PRIMARY, তথ্য->xwindow, CurrentTime);
                }
            }
        } অন্যথা যদি ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.তথ্য.l[0] == videodata->atoms._NET_WM_PING)) {
            Window মূল = Default_মূল_Window(display);

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.window);
#endif
            xevent->xclient.window = মূল;
            X11_XSendEvent(display, মূল, False, SubstructureRedirectMask | SubstructureNotifyMask, xevent);
            বিরতি;
        }

        অন্যথা যদি ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.তথ্য.l[0] == videodata->atoms.WM_DELETE_WINDOW)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.window);
#endif
            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
            বিরতি;
        } অন্যথা যদি ((xevent->xclient.message_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.তথ্য.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#ifdef DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", তথ্য);
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(তথ্য->window, &xevent->xclient);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */
            বিরতি;
        }
    } বিরতি;

        // Do we need to refresh ourselves?
    ক্ষেত্র Expose:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.window, xevent->xexpose.গুনতি);
#endif
        SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    } বিরতি;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    ক্ষেত্র চাবি_Press:
    ক্ষেত্র চাবি_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        যদি (তথ্য->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            বিরতি;
        } অন্যথা যদি (xevent->xkey.serial == videodata->xinput_last_চাবি_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_last_keyboard_device;
        }

        X11_Handle_চাবি_Event(_this, তথ্য, keyboardID, xevent);
    } বিরতি;

    ক্ষেত্র MotionNotify:
    {
        যদি (X11_Xinput2HandlesMotionForWindow(তথ্য)) {
            // This input is being handled by XInput2
            বিরতি;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        যদি (!mouse->relative_mode) {
#ifdef DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.window, xevent->xmotion.x, xevent->xmotion.y);
#endif

            X11_ProcessHitTest(_this, তথ্য, (দশমিক)xevent->xmotion.x, (দশমিক)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, তথ্য->window, SDL_GLOBAL_MOUSE_ID, false, (দশমিক)xevent->xmotion.x, (দশমিক)xevent->xmotion.y);
        }
    } বিরতি;

    ক্ষেত্র ButtonPress:
    {
        যদি (তথ্য->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            বিরতি;
        }

        X11_HandleButtonPress(_this, তথ্য, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.time, xevent->xbutton.serial);
    } বিরতি;

    ক্ষেত্র ButtonRelease:
    {
        যদি (তথ্য->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_last_button_serial) {
            // This input event was handled by XInput2.
            বিরতি;
        }

        X11_HandleButtonRelease(_this, তথ্য, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.time);
    } বিরতি;

    ক্ষেত্র PropertyNotify:
    {
#ifdef DEBUG_XEVENTS
        unsigned অক্ষর *propdata;
        পূর্ণসংখ্যা status, real_format;
        Atom real_type;
        unsigned long বস্তুসমূহ_read, বস্তুসমূহ_বাম;

        অক্ষর *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        যদি (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.window, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.time);
            X11_XFree(name);
        }

        status = X11_XGetWindowProperty(display, তথ্য->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &বস্তুসমূহ_read, &বস্তুসমূহ_বাম, &propdata);
        যদি (status == Success && বস্তুসমূহ_read > 0) {
            যদি (real_type == XA_INTEGER) {
                পূর্ণসংখ্যা *মানসমূহ = (পূর্ণসংখ্যা *)propdata;

                SDL_Log("{");
                জন্য (i = 0; i < বস্তুসমূহ_read; i++) {
                    SDL_Log(" %d", মানসমূহ[i]);
                }
                SDL_Log(" }");
            } অন্যথা যদি (real_type == XA_CARDINAL) {
                যদি (real_format == 32) {
                    Uint32 *মানসমূহ = (Uint32 *)propdata;

                    SDL_Log("{");
                    জন্য (i = 0; i < বস্তুসমূহ_read; i++) {
                        SDL_Log(" %d", মানসমূহ[i]);
                    }
                    SDL_Log(" }");
                } অন্যথা যদি (real_format == 16) {
                    Uint16 *মানসমূহ = (Uint16 *)propdata;

                    SDL_Log("{");
                    জন্য (i = 0; i < বস্তুসমূহ_read; i++) {
                        SDL_Log(" %d", মানসমূহ[i]);
                    }
                    SDL_Log(" }");
                } অন্যথা যদি (real_format == 8) {
                    Uint8 *মানসমূহ = (Uint8 *)propdata;

                    SDL_Log("{");
                    জন্য (i = 0; i < বস্তুসমূহ_read; i++) {
                        SDL_Log(" %d", মানসমূহ[i]);
                    }
                    SDL_Log(" }");
                }
            } অন্যথা যদি (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } অন্যথা যদি (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                জন্য (i = 0; i < বস্তুসমূহ_read; i++) {
                    অক্ষর *atomname = X11_XGetAtomName(display, atoms[i]);
                    যদি (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } অন্যথা {
                অক্ষর *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                যদি (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        যদি (status == Success) {
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
        যদি (!তথ্য->user_time) {
            তথ্য->user_time = xevent->xproperty.time;
        }

        যদি (xevent->xproperty.atom == তথ্য->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            ধ্রুবক SDL_WindowFlags flags = X11_GetNetWMState(_this, তথ্য->window, xevent->xproperty.window);
            ধ্রুবক SDL_WindowFlags changed = flags ^ তথ্য->window->flags;

            যদি ((changed & SDL_WINDOW_HIDDEN) && !(flags & SDL_WINDOW_HIDDEN)) {
                X11_DispatchMapNotify(তথ্য);
            }

            যদি (!SDL_WINDOW_IS_POPUP(তথ্য->window)) {
                যদি (changed & SDL_WINDOW_FULLSCREEN) {
                    তথ্য->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    যদি (flags & SDL_WINDOW_FULLSCREEN) {
                        যদি (!(flags & SDL_WINDOW_MINIMIZED)) {
                            ধ্রুবক bool commit = SDL_memcmp(&তথ্য->window->current_fullscreen_mode, &তথ্য->requested_fullscreen_mode, আকার(SDL_DisplayMode)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                            যদি (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&তথ্য->window->current_fullscreen_mode, &তথ্য->window->requested_fullscreen_mode);
                                SDL_UpdateFullscreenMode(তথ্য->window, SDL_FULLSCREEN_OP_UPDATE, true);
                            } অন্যথা {
                                SDL_UpdateFullscreenMode(তথ্য->window, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } অন্যথা {
                        SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                        SDL_UpdateFullscreenMode(তথ্য->window, false, false);

                        SDL_zero(তথ্য->requested_fullscreen_mode);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_SetWindowMinMax(তথ্য->window, !!(flags & SDL_WINDOW_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        যদি (তথ্য->fullscreen_borders_forced_on) {
                            তথ্য->toggle_borders = true;
                            তথ্য->fullscreen_borders_forced_on = false;
                        }
                    }

                    যদি ((flags & SDL_WINDOW_FULLSCREEN) &&
                        (তথ্য->border_শীর্ষ || তথ্য->border_বাম || তথ্য->border_bottom || তথ্য->border_ডান)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        তথ্য->আকার_move_event_flags |= X11_আকার_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        তথ্য->previous_borders_nonzero = true;
                    } অন্যথা যদি (!(flags & SDL_WINDOW_FULLSCREEN) &&
                               তথ্য->previous_borders_nonzero &&
                               (!তথ্য->border_শীর্ষ && !তথ্য->border_বাম && !তথ্য->border_bottom && !তথ্য->border_ডান)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        তথ্য->আকার_move_event_flags |= X11_আকার_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        তথ্য->previous_borders_nonzero = false;
                    } অন্যথা {
                        তথ্য->আকার_move_event_flags = 0;
                        তথ্য->previous_borders_nonzero = false;

                        যদি (!(তথ্য->window->flags & SDL_WINDOW_FULLSCREEN) && তথ্য->toggle_borders) {
                            তথ্য->toggle_borders = false;
                            X11_SetWindowBordered(_this, তথ্য->window, !(তথ্য->window->flags & SDL_WINDOW_BORDERLESS));
                        }
                    }
                }
                যদি ((changed & SDL_WINDOW_MAXIMIZED) && ((flags & SDL_WINDOW_MAXIMIZED) && !(flags & SDL_WINDOW_MINIMIZED))) {
                    তথ্য->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    যদি ((changed & SDL_WINDOW_MINIMIZED)) {
                        তথ্য->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                    }
                    SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_MAXIMIZED, 0, 0);
                }
                যদি ((changed & SDL_WINDOW_MINIMIZED) && (flags & SDL_WINDOW_MINIMIZED)) {
                    তথ্য->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                }
                যদি (!(flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED))) {
                    তথ্য->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    যদি (!(flags & SDL_WINDOW_FULLSCREEN)) {
                        যদি (তথ্য->pending_position) {
                            তথ্য->pending_position = false;
                            তথ্য->pending_operation |= X11_PENDING_OP_MOVE;
                            তথ্য->expected.x = তথ্য->window->pending.x - তথ্য->border_বাম;
                            তথ্য->expected.y = তথ্য->window->pending.y - তথ্য->border_শীর্ষ;
                            X11_XMoveWindow(display, তথ্য->xwindow, তথ্য->expected.x, তথ্য->expected.y);
                        }
                        যদি (তথ্য->pending_আকার) {
                            তথ্য->pending_আকার = false;
                            তথ্য->pending_operation |= X11_PENDING_OP_RESIZE;
                            তথ্য->expected.w = তথ্য->window->pending.w;
                            তথ্য->expected.h = তথ্য->window->pending.h;
                            X11_XResizeWindow(display, তথ্য->xwindow, তথ্য->window->pending.w, তথ্য->window->pending.h);
                        }
                    }
                }
                যদি (তথ্য->emit_আকার_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(তথ্য, &তথ্য->pending_xconfigure);
                    তথ্য->emit_আকার_move_after_property_notify = false;
                }
                যদি ((flags & SDL_WINDOW_প্রবেশ_FOCUS)) {
                    যদি (তথ্য->pending_move) {
                        DispatchWindowMove(_this, তথ্য, &তথ্য->pending_move_point);
                        তথ্য->pending_move = false;
                    }
                }
            }
            যদি (changed & SDL_WINDOW_OCCLUDED) {
                SDL_SendWindowEvent(তথ্য->window, (flags & SDL_WINDOW_OCCLUDED) ? SDL_EVENT_WINDOW_OCCLUDED : SDL_EVENT_WINDOW_EXPOSED, 0, 0);
            }
        } অন্যথা যদি (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            পূর্ণসংখ্যা format;
            unsigned long nitems, bytes_after;
            unsigned অক্ষর *prop_তথ্য = ফাঁকা;

            যদি (X11_XGetWindowProperty(display, তথ্য->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &bytes_after, &prop_তথ্য) == Success) {
                যদি (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_তথ্য;

                    যদি ((state == 0 || state == 3) && !তথ্য->window->is_hiding && !(তথ্য->window->flags & SDL_WINDOW_HIDDEN)) {
                        // Withdrawn or Iconic
                        যদি (!(তথ্য->window->flags & SDL_WINDOW_MINIMIZED)) {
                            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
                        }
                    } অন্যথা যদি (state == 1) { // NormalState
                        যদি (তথ্য->window->flags & SDL_WINDOW_MINIMIZED) {
                            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                            SDL_SendWindowEvent(তথ্য->window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_তথ্য);
            }
        } অন্যথা যদি (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } অন্যথা যদি (xevent->xproperty.atom == videodata->atoms._NET_FRAME_EXTENTS) {
            X11_Get_Border_মানসমূহ(তথ্য);
            যদি (তথ্য->আকার_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                তথ্য->আকার_move_event_flags &= ~X11_আকার_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            যদি (!(তথ্য->window->flags & SDL_WINDOW_FULLSCREEN) && তথ্য->toggle_borders) {
                তথ্য->toggle_borders = false;
                X11_SetWindowBordered(_this, তথ্য->window, !(তথ্য->window->flags & SDL_WINDOW_BORDERLESS));
            }
        }
    } বিরতি;

    ক্ষেত্র SelectionNotify:
    {
        Atom target = xevent->xselection.target;
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.window,
               xevent->xselection.requestor, xevent->xselection.target);
#endif
        যদি (target == তথ্য->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, তথ্য->xwindow, videodata->atoms.PRIMARY);

            যদি (p.format == 8) {
                অক্ষর *saveptr = ফাঁকা;
                অক্ষর *name = X11_XGetAtomName(display, target);
                যদি (name) {
                    অক্ষর *token = SDL_strtok_r((অক্ষর *)p.তথ্য, "\r\n", &saveptr);
                    যখন (token) {
                        যদি ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_SendDropText(তথ্য->window, token);
                        } অন্যথা যদি (SDL_strcmp("text/uri-list", name) == 0) {
                            যদি (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(তথ্য->window, ফাঁকা, token);
                            }
                        }
                        token = SDL_strtok_r(ফাঁকা, "\r\n", &saveptr);
                    }
                    X11_XFree(name);
                }
                SDL_SendDropComplete(তথ্য->window);
            }
            X11_XFree(p.তথ্য);

            // send reply
            SDL_zero(m);
            m.type = ClientMessage;
            m.display = display;
            m.window = তথ্য->xdnd_source;
            m.message_type = videodata->atoms.XdndFinished;
            m.format = 32;
            m.তথ্য.l[0] = তথ্য->xwindow;
            m.তথ্য.l[1] = 1;
            m.তথ্য.l[2] = videodata->atoms.XdndActionCopy;
            X11_XSendEvent(display, তথ্য->xdnd_source, False, NoEventMask, (XEvent *)&m);

            X11_XSync(display, False);
        }
    } বিরতি;

    পূর্বনির্ধারিত:
    {
#ifdef DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.window, xevent->type);
#endif
    } বিরতি;
    }
}

স্থির শূন্য X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    পূর্ণসংখ্যা i;

    যদি (videodata && videodata->windowlist) {
        জন্য (i = 0; i < videodata->numwindows; ++i) {
            SDL_Window_তথ্য *তথ্য = videodata->windowlist[i];
            যদি (তথ্য && তথ্য->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                যদি (now >= তথ্য->pending_focus_time) {
                    যদি (তথ্য->pending_focus == PENDING_FOCUS_IN) {
                        X11_DispatchFocusIn(_this, তথ্য);
                    } অন্যথা {
                        X11_DispatchFocusOut(_this, তথ্য);
                    }
                    তথ্য->pending_focus = PENDING_FOCUS_NONE;
                }
            }
        }
    }
}

স্থির Bool isAnyEvent(Display *display, XEvent *ev, XPointer arg)
{
    ফেরত True;
}

স্থির bool X11_PollEvent(Display *display, XEvent *event)
{
    যদি (!X11_XCheckIfEvent(display, event, isAnyEvent, ফাঁকা)) {
        ফেরত false;
    }

    ফেরত true;
}

শূন্য X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    Display *req_display = তথ্য->request_display;
    Window xwindow = window->internal->xwindow;
    XClientMessageEvent event;

    SDL_zero(event);
    event.type = ClientMessage;
    event.display = req_display;
    event.send_event = True;
    event.message_type = তথ্য->atoms._SDL_WAKEUP;
    event.format = 8;

    X11_XSendEvent(req_display, xwindow, False, NoEventMask, (XEvent *)&event);
    /* XSendEvent returns a status and it could be BadValue or BadWindow. If an
      error happens it is an SDL's internal error and there is nothing we can do here. */
    X11_XFlush(req_display);
}

পূর্ণসংখ্যা X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    যদি (X11_PollEvent(display, &xevent)) {
        // Fall through
    } অন্যথা যদি (timeoutNS == 0) {
        ফেরত 0;
    } অন্যথা {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        পূর্ণসংখ্যা err = SDL_IOReady(Connection_সংখ্যা(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        যদি (err > 0) {
            যদি (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                ফেরত 1;
            }
        } অন্যথা যদি (err == 0) {
            // Timeout
            ফেরত 0;
        } অন্যথা {
            // Error returned from poll()/select()

            যদি (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                ফেরত 1;
            } অন্যথা {
                ফেরত err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    ফেরত 1;
}

শূন্য X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    XEvent xevent;
    পূর্ণসংখ্যা i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    জন্য (i = 0; i < _this->অঙ্ক_displays; ++i) {
        যদি (_this->displays[i]->internal->mode_switch_deadline_ns) {
            যদি (_this->displays[i]->fullscreen_window) {
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            } অন্যথা যদি (SDL_GetTicksNS() >= _this->displays[i]->internal->mode_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_SetDisplayModeForDisplay(_this->displays[i], ফাঁকা);
                _this->displays[i]->internal->mode_switch_deadline_ns = 0;
            }
        }
    }

    যদি (তথ্য->last_mode_change_deadline) {
        যদি (SDL_GetTicks() >= তথ্য->last_mode_change_deadline) {
            তথ্য->last_mode_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    যদি (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        যদি (!তথ্য->screensaver_activity || now >= (তথ্য->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(তথ্য->display);

#ifdef SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#endif

            তথ্য->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    যখন (X11_PollEvent(তথ্য->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    জন্য (i = 0; i < তথ্য->numwindows; ++i) {
        যদি (তথ্য->windowlist[i] != ফাঁকা &&
            তথ্য->windowlist[i]->flash_cancel_time &&
            SDL_GetTicks() >= তথ্য->windowlist[i]->flash_cancel_time) {
            X11_FlashWindow(_this, তথ্য->windowlist[i]->window, SDL_FLASH_CANCEL);
        }
    }

    যদি (তথ্য->xinput_hierarchy_changed) {
        X11_Xinput2UpdateDevices(_this);
        তথ্য->xinput_hierarchy_changed = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_Video_তথ্য *তথ্য = _this->internal;
    পূর্ণসংখ্যা dummy;
    পূর্ণসংখ্যা major_version, minor_version;
#endif // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#ifdef SDL_USE_LIBDBUS
    যদি (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        ফেরত true;
    }

    যদি (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    যদি (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        যদি (!X11_XScreenSaverQueryExtension(তথ্য->display, &dummy, &dummy) ||
            !X11_XScreenSaverQueryVersion(তথ্য->display,
                                          &major_version, &minor_version) ||
            major_version < 1 || (major_version == 1 && minor_version < 1)) {
            ফেরত SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(তথ্য->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(তথ্য->display);
        ফেরত true;
    }
#endif
    ফেরত SDL_Unsupported();
}

#endif // SDL_VIDEO_DRIVER_X11
