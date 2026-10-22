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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

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

#ಆದರೆ 0
#ವ್ಯಾಖ್ಯಾನಿಸು DEBUG_XEVENTS
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NET_WM_MOVERESIZE_ಗಾತ್ರ_TOPLEFT
#ವ್ಯಾಖ್ಯಾನಿಸು NET_WM_MOVERESIZE_ಗಾತ್ರ_TOPLEFT 0
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NET_WM_MOVERESIZE_ಗಾತ್ರ_ತುದಿ
#ವ್ಯಾಖ್ಯಾನಿಸು NET_WM_MOVERESIZE_ಗಾತ್ರ_ತುದಿ 1
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NET_WM_MOVERESIZE_ಗಾತ್ರ_TOPRIGHT
#ವ್ಯಾಖ್ಯಾನಿಸು NET_WM_MOVERESIZE_ಗಾತ್ರ_TOPRIGHT 2
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NET_WM_MOVERESIZE_ಗಾತ್ರ_ಬಲ
#ವ್ಯಾಖ್ಯಾನಿಸು NET_WM_MOVERESIZE_ಗಾತ್ರ_ಬಲ 3
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NET_WM_MOVERESIZE_ಗಾತ್ರ_BOTTOMRIGHT
#ವ್ಯಾಖ್ಯಾನಿಸು NET_WM_MOVERESIZE_ಗಾತ್ರ_BOTTOMRIGHT 4
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NET_WM_MOVERESIZE_ಗಾತ್ರ_BOTTOM
#ವ್ಯಾಖ್ಯಾನಿಸು NET_WM_MOVERESIZE_ಗಾತ್ರ_BOTTOM 5
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NET_WM_MOVERESIZE_ಗಾತ್ರ_BOTTOMLEFT
#ವ್ಯಾಖ್ಯಾನಿಸು NET_WM_MOVERESIZE_ಗಾತ್ರ_BOTTOMLEFT 6
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NET_WM_MOVERESIZE_ಗಾತ್ರ_ಎಡ
#ವ್ಯಾಖ್ಯಾನಿಸು NET_WM_MOVERESIZE_ಗಾತ್ರ_ಎಡ 7
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _NET_WM_MOVERESIZE_MOVE
#ವ್ಯಾಖ್ಯಾನಿಸು _NET_WM_MOVERESIZE_MOVE 8
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ format, ಎಣಿಕೆ_2;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ಸ್ಥಿರ ಶೂನ್ಯ X11_ReadProperty(SDL_x11Prop *p, Display *disp, ಕಿಟಕಿ_2 w, Atom prop)
{
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ret = ಖಾಲಿ;
    Atom type;
    ಪೂರ್ಣಾಂಕ fmt;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಎಣಿಕೆ_2;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಬೈಟುಗಳು_ಎಡ;
    ಪೂರ್ಣಾಂಕ ಬೈಟುಗಳು_fetch = 0;

    ಮಾಡು {
        ಆದರೆ (ret) {
            X11_XFree(ret);
        }
        X11_XGet_ಕಿಟಕಿ_Property(disp, w, prop, 0, ಬೈಟುಗಳು_fetch, False, AnyPropertyType, &type, &fmt, &ಎಣಿಕೆ_2, &ಬೈಟುಗಳು_ಎಡ, &ret);
        ಬೈಟುಗಳು_fetch += ಬೈಟುಗಳು_ಎಡ;
    } ಆಗ (ಬೈಟುಗಳು_ಎಡ != 0);

    p->ದತ್ತಾಂಶ = ret;
    p->format = fmt;
    p->ಎಣಿಕೆ_2 = ಎಣಿಕೆ_2;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
ಸ್ಥಿರ Atom X11_Pick_ಗುರಿ(Display *disp, Atom list[], ಪೂರ್ಣಾಂಕ list_ಎಣಿಕೆ)
{
    ಸ್ಥಿರಾಂಕ Atom ಪಠ್ಯ_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < list_ಎಣಿಕೆ && request != ಪಠ್ಯ_uri_request; i++) {
        ಅಕ್ಷರ *name = X11_XGetAtomName(disp, list[i]);
        // Preferred MIME targets
        ಆದರೆ ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            ಆದರೆ (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        ಆದರೆ ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            ಆದರೆ (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    ಆದರೆ (preferred != None && request != ಪಠ್ಯ_uri_request) {
        request = preferred;
    }
    ಹಿಂತಿರುಗಿ request;
}

/* Wrapper for X11_PickTarget for a maximum of three targets, a special
   case in the Xdnd protocol */
ಸ್ಥಿರ Atom X11_Pick_ಗುರಿ_From_Atoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2 = 0;
    Atom atom[3];
    ಆದರೆ (a0 != None) {
        atom[ಎಣಿಕೆ_2++] = a0;
    }
    ಆದರೆ (a1 != None) {
        atom[ಎಣಿಕೆ_2++] = a1;
    }
    ಆದರೆ (a2 != None) {
        atom[ಎಣಿಕೆ_2++] = a2;
    }
    ಹಿಂತಿರುಗಿ X11_Pick_ಗುರಿ(disp, atom, ಎಣಿಕೆ_2);
}

ರಚನೆ ಕೀಲಿ_Repeat_Check_ದತ್ತಾಂಶ
{
    XEvent *event;
    bool ಸಿಕ್ಕಿತು;
};

ಸ್ಥಿರ Bool X11_ಕೀಲಿ_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    ರಚನೆ ಕೀಲಿ_Repeat_Check_ದತ್ತಾಂಶ *d = (ರಚನೆ ಕೀಲಿ_Repeat_Check_ದತ್ತಾಂಶ *)arg;
    ಆದರೆ (chkev->type == ಕೀಲಿ_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.ಸಮಯ - d->event->xkey.ಸಮಯ < 2) {
        d->ಸಿಕ್ಕಿತು = true;
    }
    ಹಿಂತಿರುಗಿ False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
ಸ್ಥಿರ bool X11_ಕೀಲಿ_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    ರಚನೆ ಕೀಲಿ_Repeat_Check_ದತ್ತಾಂಶ d;
    d.event = event;
    d.ಸಿಕ್ಕಿತು = false;
    ಆದರೆ (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_ಕೀಲಿ_Repeat_Check_If_Event, (XPointer)&d);
    }
    ಹಿಂತಿರುಗಿ d.ಸಿಕ್ಕಿತು;
}

bool X11_IsWheelEvent(ಪೂರ್ಣಾಂಕ button, ಪೂರ್ಣಾಂಕ *xticks, ಪೂರ್ಣಾಂಕ *yticks)
{
    /* according to the xlib docs, no specific mouse wheel events exist.
       However, the defacto standard is that the vertical wheel is X buttons
       4 (up) and 5 (down) and a horizontal wheel is 6 (left) and 7 (right). */

    // Xlib defines "Button1" through 5, so we just use literals here.
    ಆಯ್ಕೆ (button) {
    ಸ್ಥಿತಿ 4:
        *yticks = 1;
        ಹಿಂತಿರುಗಿ true;
    ಸ್ಥಿತಿ 5:
        *yticks = -1;
        ಹಿಂತಿರುಗಿ true;
    ಸ್ಥಿತಿ 6:
        *xticks = 1;
        ಹಿಂತಿರುಗಿ true;
    ಸ್ಥಿತಿ 7:
        *xticks = -1;
        ಹಿಂತಿರುಗಿ true;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ false;
}

// An X11 event hook
ಸ್ಥಿರ SDL_X11EventHook g_X11EventHook = ಖಾಲಿ;
ಸ್ಥಿರ ಶೂನ್ಯ *g_X11_Event_Hook_ದತ್ತಾಂಶ = ಖಾಲಿ;

ಶೂನ್ಯ SDL_ಗಣ_X11_Event_Hook(SDL_X11EventHook callback, ಶೂನ್ಯ *userdata)
{
    g_X11EventHook = callback;
    g_X11_Event_Hook_ದತ್ತಾಂಶ = userdata;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
ಸ್ಥಿರ ಶೂನ್ಯ X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    ಆದರೆ (X11_XGet_Event_ದತ್ತಾಂಶ(videodata->display, cookie)) {
        ಆದರೆ (!g_X11EventHook || g_X11EventHook(g_X11_Event_Hook_ದತ್ತಾಂಶ, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFree_Event_ದತ್ತಾಂಶ(videodata->display, cookie);
    }
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

ಸ್ಥಿರ ಶೂನ್ಯ X11_Update_System_ಕೀಲಿ_Modifiers(SDL_Video_ದತ್ತಾಂಶ *viddata)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ಆದರೆ (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        ಆದರೆ (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.ತಳ_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        {
        ಕಿಟಕಿ_2 junk_ಕಿಟಕಿ;
        ಪೂರ್ಣಾಂಕ x, y;
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ mod_ಮುಖವಾಡ;

        X11_XQuery_ಸೂಚಕ(viddata->display, Default_ಬೇರು_ಕಿಟಕಿ(viddata->display), &junk_ಕಿಟಕಿ, &junk_ಕಿಟಕಿ, &x, &y, &x, &y, &mod_ಮುಖವಾಡ);
        viddata->keyboard.pressed_modifiers = mod_ಮುಖವಾಡ & (ಸರಿಸು_ಮುಖವಾಡ_2 | Control_ಮುಖವಾಡ | Mod1_ಮುಖವಾಡ | Mod3_ಮುಖವಾಡ | Mod4_ಮುಖವಾಡ | Mod5_ಮುಖವಾಡ);
        viddata->keyboard.locked_modifiers = mod_ಮುಖವಾಡ & (ಬೀಗ_ಮುಖವಾಡ | viddata->keyboard.numlock_ಮುಖವಾಡ | viddata->keyboard.scrolllock_ಮುಖವಾಡ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_ReconcileModifiers(SDL_Video_ದತ್ತಾಂಶ *viddata, bool ಕೀಲಿ_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    ಆದರೆ (ಕೀಲಿ_pressed) {
        ಆದರೆ (viddata->keyboard.pressed_modifiers & ಸರಿಸು_ಮುಖವಾಡ_2) {
            ಆದರೆ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ಸರಿಸು) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ಸರಿಸು;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ಸರಿಸು);
            }
        }

        ಆದರೆ (viddata->keyboard.pressed_modifiers & Control_ಮುಖವಾಡ) {
            ಆದರೆ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        ಆದರೆ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_ಮುಖವಾಡ) {
            ಆದರೆ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        ಆದರೆ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_ಮುಖವಾಡ) {
            ಆದರೆ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (viddata->keyboard.pressed_modifiers & ಸರಿಸು_ಮುಖವಾಡ_2) {
            ಆದರೆ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ಸರಿಸು)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ಸರಿಸು;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ಸರಿಸು;
        }

        ಆದರೆ (viddata->keyboard.pressed_modifiers & Control_ಮುಖವಾಡ) {
            ಆದರೆ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        ಆದರೆ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_ಮುಖವಾಡ) {
            ಆದರೆ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        ಆದರೆ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_ಮುಖವಾಡ) {
            ಆದರೆ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        ಆದರೆ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_ಮುಖವಾಡ) {
            ಆದರೆ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ಬಹುಲಕ)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ಬಹುಲಕ;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ಬಹುಲಕ;
        }

        ಆದರೆ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_ಮುಖವಾಡ) {
            ಆದರೆ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
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
    ಆದರೆ (viddata->keyboard.locked_modifiers & ಸರಿಸು_ಮುಖವಾಡ_2) {
        ಆದರೆ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ಸರಿಸು) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ಸರಿಸು;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ಸರಿಸು);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ಸರಿಸು)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ಸರಿಸು;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ಸರಿಸು;
    }

    ಆದರೆ (viddata->keyboard.locked_modifiers & Control_ಮುಖವಾಡ) {
        ಆದರೆ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    ಆದರೆ (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_ಮುಖವಾಡ) {
        ಆದರೆ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    ಆದರೆ (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_ಮುಖವಾಡ) {
        ಆದರೆ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    ಆದರೆ (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_ಮುಖವಾಡ) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ಬಹುಲಕ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ಬಹುಲಕ;
    }

    ಆದರೆ (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_ಮುಖವಾಡ) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } ಇಲ್ಲದಿದ್ದರೆ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    ಆದರೆ (viddata->keyboard.locked_modifiers & ಬೀಗ_ಮುಖವಾಡ) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } ಇಲ್ಲದಿದ್ದರೆ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    ಆದರೆ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_ಮುಖವಾಡ) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ಅಂಕೆ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ಅಂಕೆ;
    }

    ಆದರೆ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_ಮುಖವಾಡ) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } ಇಲ್ಲದಿದ್ದರೆ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_ಗಣ_Mod_State(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Handle_Modifier_ಕೀಲಿಗಳು(SDL_Video_ದತ್ತಾಂಶ *viddata, SDL_Scancode scancode, bool pressed)
{
    ಸ್ಥಿರಾಂಕ SDL_Keycode keycode = SDL_Get_ಕೀಲಿ_From_Scancode(scancode, SDL_KMOD_NONE, false);
    SDL_Keymod mod = SDL_KMOD_NONE;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is checked.
     */
    ಆಯ್ಕೆ (keycode) {
    ಸ್ಥಿತಿ SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_LALT:
        mod = SDL_KMOD_LALT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_RALT:
        mod = SDL_KMOD_RALT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_ಬಹುಲಕ:
        mod = SDL_KMOD_ಬಹುಲಕ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_LEVEL5_ಸರಿಸು:
        mod = SDL_KMOD_LEVEL5;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_CAPSLOCK:
    ಸ್ಥಿತಿ SDLK_NUMLOCKCLEAR:
    ಸ್ಥಿತಿ SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        ಆದರೆ (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ cur_ಮುಖವಾಡ = viddata->keyboard.locked_modifiers;
            X11_Update_System_ಕೀಲಿ_Modifiers(viddata);

            ಆದರೆ (viddata->keyboard.locked_modifiers & ಬೀಗ_ಮುಖವಾಡ) {
                cur_ಮುಖವಾಡ |= ಬೀಗ_ಮುಖವಾಡ;
            } ಇಲ್ಲದಿದ್ದರೆ {
                cur_ಮುಖವಾಡ &= ~ಬೀಗ_ಮುಖವಾಡ;
            }
            ಆದರೆ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_ಮುಖವಾಡ) {
                cur_ಮುಖವಾಡ |= viddata->keyboard.numlock_ಮುಖವಾಡ;
            } ಇಲ್ಲದಿದ್ದರೆ {
                cur_ಮುಖವಾಡ &= ~viddata->keyboard.numlock_ಮುಖವಾಡ;
            }
            ಆದರೆ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_ಮುಖವಾಡ) {
                cur_ಮುಖವಾಡ |= viddata->keyboard.scrolllock_ಮುಖವಾಡ;
            } ಇಲ್ಲದಿದ್ದರೆ {
                cur_ಮುಖವಾಡ &= ~viddata->keyboard.scrolllock_ಮುಖವಾಡ;
            }

            viddata->keyboard.locked_modifiers = cur_ಮುಖವಾಡ;
        }
    } ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } ಇಲ್ಲದಿದ್ದರೆ {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

ಶೂನ್ಯ X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    Display *display = videodata->display;
    ಅಕ್ಷರ ಕೀಲಿಗಳು[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_ಕೀಲಿ_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_ಅಂಕೆ | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= ಬೀಗ_ಮುಖವಾಡ | videodata->keyboard.numlock_ಮುಖವಾಡ| videodata->keyboard.scrolllock_ಮುಖವಾಡ;

    X11_XQueryKeymap(display, ಕೀಲಿಗಳು);

    ಸ್ಥಿರಾಂಕ bool *keystate = SDL_GetKeyboardState(ಖಾಲಿ);
    ಗಾಗಿ (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.ಕೀಲಿ_layout); ++keycode) {
        ಸ್ಥಿರಾಂಕ SDL_Scancode scancode = videodata->keyboard.ಕೀಲಿ_layout[keycode];
        ಸ್ಥಿರಾಂಕ bool x11_ಕೀಲಿ_Pressed = (ಕೀಲಿಗಳು[keycode / 8] & (1 << (keycode % 8))) != 0;
        ಸ್ಥಿರಾಂಕ bool sdl_ಕೀಲಿ_Pressed = keystate[scancode];

        ಆದರೆ (x11_ಕೀಲಿ_Pressed && !sdl_ಕೀಲಿ_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            ಆಯ್ಕೆ (SDL_Get_ಕೀಲಿ_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            ಸ್ಥಿತಿ SDLK_LCTRL:
            ಸ್ಥಿತಿ SDLK_RCTRL:
            ಸ್ಥಿತಿ SDLK_LSHIFT:
            ಸ್ಥಿತಿ SDLK_RSHIFT:
            ಸ್ಥಿತಿ SDLK_LALT:
            ಸ್ಥಿತಿ SDLK_RALT:
            ಸ್ಥಿತಿ SDLK_LGUI:
            ಸ್ಥಿತಿ SDLK_RGUI:
            ಸ್ಥಿತಿ SDLK_ಬಹುಲಕ:
            ಸ್ಥಿತಿ SDLK_LEVEL5_ಸರಿಸು:
                X11_Handle_Modifier_ಕೀಲಿಗಳು(videodata, scancode, true);
                SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                ನಿಲ್ಲಿಸು;
            ಪೂರ್ವನಿಯೋಜಿತ:
                ನಿಲ್ಲಿಸು;
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!x11_ಕೀಲಿ_Pressed && sdl_ಕೀಲಿ_Pressed) {
            X11_Handle_Modifier_ಕೀಲಿಗಳು(videodata, scancode, false);
            SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_ಕೀಲಿ_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Dispatch_Focus_ಒಳ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", ದತ್ತಾಂಶ->xwindow);
#ಆದರೆ_ಅಂತ್ಯ
    SDL_ಗಣ_Keyboard_Focus(ದತ್ತಾಂಶ->ಕಿಟಕಿ);
    X11_ReconcileKeyboardState(_this);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    ಆದರೆ (ದತ್ತಾಂಶ->ic) {
        X11_XSetICFocus(ದತ್ತಾಂಶ->ic);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (ದತ್ತಾಂಶ->flashing_ಕಿಟಕಿ) {
        X11_Flash_ಕಿಟಕಿ(_this, ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_FLASH_CANCEL);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Dispatch_Focus_ಹೊರಹೋಗು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", ದತ್ತಾಂಶ->xwindow);
#ಆದರೆ_ಅಂತ್ಯ
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ == SDL_GetKeyboardFocus()) {
        SDL_ಗಣ_Keyboard_Focus(ಖಾಲಿ);
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    ಆದರೆ (ದತ್ತಾಂಶ->ic) {
        X11_XUnsetICFocus(ದತ್ತಾಂಶ->ic);
    }
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_DispatchMapNotify(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ದತ್ತಾಂಶ->ಕಿಟಕಿ;

    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_SHOWN, 0, 0);
    ದತ್ತಾಂಶ->was_shown = true;

    // This may be sent when restoring a minimized window.
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED) {
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESTORED, 0, 0);
        SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_EXPOSED, 0, 0);
    }

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS) {
        SDL_Update_ಕಿಟಕಿ_Grab(ಕಿಟಕಿ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_DispatchUnmapNotify(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ದತ್ತಾಂಶ->ಕಿಟಕಿ;

    // This may be sent when minimizing a window.
    ಆದರೆ (!ಕಿಟಕಿ->is_hiding) {
        SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MINIMIZED, 0, 0);
        SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_OCCLUDED, 0, 0);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_HIDDEN, 0, 0);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Dispatch_ಕಿಟಕಿ_Move(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, ಸ್ಥಿರಾಂಕ SDL_ಬಿಂದು *ಬಿಂದು)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ದತ್ತಾಂಶ->ಕಿಟಕಿ;
    Display *display = videodata->display;
    XEvent evt;

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_ಸೂಚಕ(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_ಸಂದೇಶ;
    evt.xclient.ಕಿಟಕಿ = ದತ್ತಾಂಶ->xwindow;
    evt.xclient.ಸಂದೇಶ_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.ದತ್ತಾಂಶ.l[0] = (size_t)ಕಿಟಕಿ->x + ಬಿಂದು->x;
    evt.xclient.ದತ್ತಾಂಶ.l[1] = (size_t)ಕಿಟಕಿ->y + ಬಿಂದು->y;
    evt.xclient.ದತ್ತಾಂಶ.l[2] = _NET_WM_MOVERESIZE_MOVE;
    evt.xclient.ದತ್ತಾಂಶ.l[3] = Button1;
    evt.xclient.ದತ್ತಾಂಶ.l[4] = 0;
    X11_XSendEvent(display, Default_ಬೇರು_ಕಿಟಕಿ(display), False, Substructure_Redirect_ಮುಖವಾಡ | Substructure_Notify_ಮುಖವಾಡ, &evt);

    X11_XSync(display, 0);
}

ಸ್ಥಿರ ಶೂನ್ಯ ವೇಳಾಪಟ್ಟಿ_ಕಿಟಕಿ_Move(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, ಸ್ಥಿರಾಂಕ SDL_ಬಿಂದು *ಬಿಂದು)
{
    ದತ್ತಾಂಶ->pending_move = true;
    ದತ್ತಾಂಶ->pending_move_ಬಿಂದು = *ಬಿಂದು;
}

ಸ್ಥಿರ ಶೂನ್ಯ Initiate_ಕಿಟಕಿ_Resize(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, ಸ್ಥಿರಾಂಕ SDL_ಬಿಂದು *ಬಿಂದು, ಪೂರ್ಣಾಂಕ direction)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ದತ್ತಾಂಶ->ಕಿಟಕಿ;
    Display *display = videodata->display;
    XEvent evt;

    ಆದರೆ (direction < NET_WM_MOVERESIZE_ಗಾತ್ರ_TOPLEFT || direction > NET_WM_MOVERESIZE_ಗಾತ್ರ_ಎಡ) {
        ಹಿಂತಿರುಗಿ;
    }

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_ಸೂಚಕ(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_ಸಂದೇಶ;
    evt.xclient.ಕಿಟಕಿ = ದತ್ತಾಂಶ->xwindow;
    evt.xclient.ಸಂದೇಶ_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.ದತ್ತಾಂಶ.l[0] = (size_t)ಕಿಟಕಿ->x + ಬಿಂದು->x;
    evt.xclient.ದತ್ತಾಂಶ.l[1] = (size_t)ಕಿಟಕಿ->y + ಬಿಂದು->y;
    evt.xclient.ದತ್ತಾಂಶ.l[2] = direction;
    evt.xclient.ದತ್ತಾಂಶ.l[3] = Button1;
    evt.xclient.ದತ್ತಾಂಶ.l[4] = 0;
    X11_XSendEvent(display, Default_ಬೇರು_ಕಿಟಕಿ(display), False, Substructure_Redirect_ಮುಖವಾಡ | Substructure_Notify_ಮುಖವಾಡ, &evt);

    X11_XSync(display, 0);
}

bool X11_Process_ದೊರಕಿತು_Test(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ x, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ y, bool force_new_ಫಲಿತಾಂಶ)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ದತ್ತಾಂಶ->ಕಿಟಕಿ;
    ಆದರೆ (!ಕಿಟಕಿ->ದೊರಕಿತು_test) ಹಿಂತಿರುಗಿ false;
    ಸ್ಥಿರಾಂಕ SDL_ಬಿಂದು ಬಿಂದು = { (ಪೂರ್ಣಾಂಕ)x, (ಪೂರ್ಣಾಂಕ)y };
    SDL_ದೊರಕಿತು_Test_ಫಲಿತಾಂಶ rc = ಕಿಟಕಿ->ದೊರಕಿತು_test(ಕಿಟಕಿ, &ಬಿಂದು, ಕಿಟಕಿ->ದೊರಕಿತು_test_ದತ್ತಾಂಶ);
    ಆದರೆ (!force_new_ಫಲಿತಾಂಶ && rc == ದತ್ತಾಂಶ->ದೊರಕಿತು_test_ಫಲಿತಾಂಶ) {
        ಹಿಂತಿರುಗಿ true;
    }
    X11_ಗಣ_ದೊರಕಿತು_Test_Cursor(rc);
    ದತ್ತಾಂಶ->ದೊರಕಿತು_test_ಫಲಿತಾಂಶ = rc;
    ಹಿಂತಿರುಗಿ true;
}

bool X11_Trigger_ದೊರಕಿತು_Test_Action(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ x, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ y)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ದತ್ತಾಂಶ->ಕಿಟಕಿ;

    ಆದರೆ (ಕಿಟಕಿ->ದೊರಕಿತು_test) {
        ಸ್ಥಿರಾಂಕ SDL_ಬಿಂದು ಬಿಂದು = { (ಪೂರ್ಣಾಂಕ)x, (ಪೂರ್ಣಾಂಕ)y };
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ directions[] = {
            NET_WM_MOVERESIZE_ಗಾತ್ರ_TOPLEFT, NET_WM_MOVERESIZE_ಗಾತ್ರ_ತುದಿ,
            NET_WM_MOVERESIZE_ಗಾತ್ರ_TOPRIGHT, NET_WM_MOVERESIZE_ಗಾತ್ರ_ಬಲ,
            NET_WM_MOVERESIZE_ಗಾತ್ರ_BOTTOMRIGHT, NET_WM_MOVERESIZE_ಗಾತ್ರ_BOTTOM,
            NET_WM_MOVERESIZE_ಗಾತ್ರ_BOTTOMLEFT, NET_WM_MOVERESIZE_ಗಾತ್ರ_ಎಡ
        };

        ಆಯ್ಕೆ (ದತ್ತಾಂಶ->ದೊರಕಿತು_test_ಫಲಿತಾಂಶ) {
        ಸ್ಥಿತಿ SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS) {
                Dispatch_ಕಿಟಕಿ_Move(_this, ದತ್ತಾಂಶ, &ಬಿಂದು);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ವೇಳಾಪಟ್ಟಿ_ಕಿಟಕಿ_Move(_this, ದತ್ತಾಂಶ, &ಬಿಂದು);
            }
            ಹಿಂತಿರುಗಿ true;

        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_TOPLEFT:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ತುದಿ:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_TOPRIGHT:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ಬಲ:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOM:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOMLEFT:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ಎಡ:
            Initiate_ಕಿಟಕಿ_Resize(_this, ದತ್ತಾಂಶ, &ಬಿಂದು, directions[ದತ್ತಾಂಶ->ದೊರಕಿತು_test_ಫಲಿತಾಂಶ - SDL_HITTEST_RESIZE_TOPLEFT]);
            ಹಿಂತಿರುಗಿ true;

        ಪೂರ್ವನಿಯೋಜಿತ:
            ಹಿಂತಿರುಗಿ false;
        }
    }

    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Update_User_ಸಮಯ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ latest)
{
    ಆದರೆ (latest && (latest != ದತ್ತಾಂಶ->user_ಸಮಯ)) {
        SDL_Video_ದತ್ತಾಂಶ *videodata = ದತ್ತಾಂಶ->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, ದತ್ತಾಂಶ->xwindow, videodata->atoms.NET_WM_USER_ಸಮಯ,
                            XA_CARDINAL, 32, Prop_ಬಹುಲಕ_Replace,
                            (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)&latest, 1);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", ದತ್ತಾಂಶ->xwindow, latest);
#ಆದರೆ_ಅಂತ್ಯ
        ದತ್ತಾಂಶ->user_ಸಮಯ = latest;
    }
}

ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ x11_ಕೊನೆಯ_error;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Bad_ಕಿಟಕಿ_Error_Handler(Display *d, XErrorEvent *e)
{
    x11_ಕೊನೆಯ_error = e->error_ಸಂಕೇತ;

    // Ignore BadWindow in cases where it's not fatal.
    ಆದರೆ (e->error_ಸಂಕೇತ != Bad_ಕಿಟಕಿ) {
        ಅಕ್ಷರ err_ಸಂದೇಶ[128];
        X11_XGet_Error_ಪಠ್ಯ(d, e->error_ಸಂಕೇತ, err_ಸಂದೇಶ, ಗಾತ್ರ(err_ಸಂದೇಶ));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_ಸಂಕೇತ, err_ಸಂದೇಶ, e->request_ಸಂಕೇತ);
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_HandleClipboardEvent(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ XEvent *xevent)
{
    ಪೂರ್ಣಾಂಕ i;
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_ಕಿಟಕಿ != None);
    SDL_assert(xevent->xany.ಕಿಟಕಿ == videodata->clipboard_ಕಿಟಕಿ);

    ಆಯ್ಕೆ (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    ಸ್ಥಿತಿ SelectionRequest:
    {
        ಸ್ಥಿರಾಂಕ XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        ಪೂರ್ಣಾಂಕ mime_formats;
        ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *seln_ದತ್ತಾಂಶ;
        size_t seln_ಉದ್ದಳತೆ = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_Clipboard_ದತ್ತಾಂಶ *clipboard;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        ಅಕ್ಷರ *atom_name;
        atom_name = X11_XGetAtomName(display, req->ಗುರಿ);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->ಗುರಿ, atom_name);
        ಆದರೆ (atom_name) {
            X11_XFree(atom_name);
        }
#ಆದರೆ_ಅಂತ್ಯ

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_ಕೊನೆಯ_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_ಕಿಟಕಿ_Error_Handler);

        ಆದರೆ (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ಇಲ್ಲದಿದ್ದರೆ {
            clipboard = &videodata->clipboard;
        }

        SDL_zero(sevent);
        sevent.xany.type = SelectionNotify;
        sevent.xselection.selection = req->selection;
        sevent.xselection.ಗುರಿ = None;
        sevent.xselection.property = None; // tell them no by default
        sevent.xselection.requestor = req->requestor;
        sevent.xselection.ಸಮಯ = req->ಸಮಯ;

        /* !!! FIXME: We were probably storing this on the root window
           because an SDL window might go away...? but we don't have to do
           this now (or ever, really). */

        ಆದರೆ (req->ಗುರಿ == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_ಎಣಿಕೆ + 1) * ಗಾತ್ರ(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            ಗಾಗಿ (i = 0; i < clipboard->mime_ಎಣಿಕೆ; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, Prop_ಬಹುಲಕ_Replace,
                                (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.ಗುರಿ = XA_TARGETS;
            SDL_free(supportedFormats);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (clipboard->callback) {
                ಗಾಗಿ (i = 0; i < clipboard->mime_ಎಣಿಕೆ; ++i) {
                    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type = clipboard->mime_types[i];
                    ಆದರೆ (X11_XInternAtom(display, mime_type, False) != req->ಗುರಿ) {
                        ಮುಂದುವರಿ;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_ದತ್ತಾಂಶ = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)clipboard->callback(clipboard->userdata, mime_type, &seln_ಉದ್ದಳತೆ);
                    ಆದರೆ (seln_ದತ್ತಾಂಶ) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->ಗುರಿ, 8, Prop_ಬಹುಲಕ_Replace,
                                            seln_ದತ್ತಾಂಶ, seln_ಉದ್ದಳತೆ);
                        sevent.xselection.property = req->property;
                        sevent.xselection.ಗುರಿ = req->ಗುರಿ;
                    }
                    ನಿಲ್ಲಿಸು;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(prev_handler);
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SelectionNotify:
    {
        ಸ್ಥಿರಾಂಕ XSelectionEvent *xsel = &xevent->xselection;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಗುರಿ_Name = xsel->ಗುರಿ ? X11_XGetAtomName(display, xsel->ಗುರಿ) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, ಗುರಿ_Name, propName);
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (xsel->ಗುರಿ == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ದತ್ತಾಂಶ = ಖಾಲಿ;
            ಪೂರ್ಣಾಂಕ format_property = 0;
            ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಉದ್ದಳತೆ = 0;
            ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಬೈಟುಗಳು_ಎಡ = 0;
            ಪೂರ್ಣಾಂಕ j;

            X11_XGet_ಕಿಟಕಿ_Property(display, Get_ಕಿಟಕಿ(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &ಉದ್ದಳತೆ, &ಬೈಟುಗಳು_ಎಡ, &ದತ್ತಾಂಶ);

            ಪೂರ್ಣಾಂಕ allocationsize = (ಉದ್ದಳತೆ + 1) * ಗಾತ್ರ(ಅಕ್ಷರ *);
            ಗಾಗಿ (j = 0, patom = (Atom *)ದತ್ತಾಂಶ; j < ಉದ್ದಳತೆ; j++, patom++) {
                ಅಕ್ಷರ *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            ಅಕ್ಷರ **new_mime_types = SDL_Allocate_Temporary_ಸ್ಮರಣೆ(allocationsize);
            ಆದರೆ (new_mime_types) {
                ಅಕ್ಷರ *strPtr = (ಅಕ್ಷರ *)(new_mime_types + ಉದ್ದಳತೆ + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                ಗಾಗಿ (j = 0, patom = (Atom *)ದತ್ತಾಂಶ; j < ಉದ್ದಳತೆ; j++, patom++) {
                    ಅಕ್ಷರ *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    ಸ್ಥಿರಾಂಕ size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[ಉದ್ದಳತೆ] = ಖಾಲಿ;

                SDL_SendClipboardUpdate(false, new_mime_types, ಉದ್ದಳತೆ);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            ಆದರೆ (ದತ್ತಾಂಶ) {
                X11_XFree(ದತ್ತಾಂಶ);
            }
        }

        videodata->selection_ಕಾಯುವಿಕೆ = false;
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_Clipboard_ದತ್ತಾಂಶ *clipboard = ಖಾಲಿ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.ಗುರಿ);
#ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        ಆದರೆ (clipboard && clipboard->callback) {
            ಆದರೆ (clipboard->sequence) {
                SDL_Cancel_Clipboard_ದತ್ತಾಂಶ(clipboard->sequence);
            } ಇಲ್ಲದಿದ್ದರೆ {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ PropertyNotify:
    {
        ಅಕ್ಷರ *name_ದ_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        ಆದರೆ (SDL_strncmp(name_ದ_atom, "SDL_SELECTION", ಗಾತ್ರ("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_ಮೌಲ್ಯ) {
            videodata->selection_incr_ಕಾಯುವಿಕೆ = false;
        }

        ಆದರೆ (name_ದ_atom) {
            X11_XFree(name_ದ_atom);
        }
    } ನಿಲ್ಲಿಸು;
    }
}

ಸ್ಥಿರ Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    ಹಿಂತಿರುಗಿ ev->type == MapNotify &&
           ev->xmap.ಕಿಟಕಿ == unmap->ಕಿಟಕಿ &&
           ev->xmap.serial == unmap->serial;
}

ಸ್ಥಿರ Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    ಹಿಂತಿರುಗಿ ev->type == ReparentNotify &&
           ev->xreparent.ಕಿಟಕಿ == unmap->ಕಿಟಕಿ &&
           ev->xreparent.serial == unmap->serial;
}

ಸ್ಥಿರ bool Is_ಮೇಲಿನ_Latin1(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *string, ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ)
{
    ಆಗ (ಉದ್ದಳತೆ-- > 0) {
        Uint8 ch = (Uint8)*string;
        ಆದರೆ (ch >= 0x80) {
            ಹಿಂತಿರುಗಿ true;
        }
        ++string;
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ XLookupStringAsUTF8(XKeyEvent *event_struct, ಅಕ್ಷರ *ಬಫರ್_return, ಪೂರ್ಣಾಂಕ ಬೈಟುಗಳು_ಬಫರ್, ಕೀಲಿ_Sym *keysym_return, XCompose_ಸ್ಥಿತಿ *ಸ್ಥಿತಿ_ಒಳ_ಹೊರಹೋಗು)
{
    ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = X11_XLookupString(event_struct, ಬಫರ್_return, ಬೈಟುಗಳು_ಬಫರ್, keysym_return, ಸ್ಥಿತಿ_ಒಳ_ಹೊರಹೋಗು);
    ಆದರೆ (Is_ಮೇಲಿನ_Latin1(ಬಫರ್_return, ಫಲಿತಾಂಶ)) {
        ಅಕ್ಷರ *utf8_ಪಠ್ಯ = SDL_iconv_string("UTF-8", "ISO-8859-1", ಬಫರ್_return, ಫಲಿತಾಂಶ + 1);
        ಆದರೆ (utf8_ಪಠ್ಯ) {
            SDL_strlcpy(ಬಫರ್_return, utf8_ಪಠ್ಯ, ಬೈಟುಗಳು_ಬಫರ್);
            SDL_free(utf8_ಪಠ್ಯ);
            ಹಿಂತಿರುಗಿ SDL_strlen(ಬಫರ್_return);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ 0;
        }
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *X11_ಕಂಡುಹಿಡಿ_ಕಿಟಕಿ(SDL_Video_ದತ್ತಾಂಶ *videodata, ಕಿಟಕಿ_2 ಕಿಟಕಿ)
{
    ಆದರೆ (videodata && videodata->windowlist) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < videodata->numwindows; ++i) {
            ಆದರೆ ((videodata->windowlist[i] != ಖಾಲಿ) &&
                (videodata->windowlist[i]->xwindow == ಕಿಟಕಿ)) {
                ಹಿಂತಿರುಗಿ videodata->windowlist[i];
            }
        }
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

Uint64 X11_GetEventTimestamp(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಸಮಯ)
{
    // FIXME: Get the event time in the SDL tick time base
    ಹಿಂತಿರುಗಿ SDL_GetTicksNS();
}

ಶೂನ್ಯ X11_Handle_ಕೀಲಿ_Event(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    Display *display = videodata->display;
    ಕೀಲಿ_ಸಂಕೇತ_2 keycode = xevent->xkey.keycode;
    ಕೀಲಿ_Sym keysym = No_ಚಿಹ್ನೆ;
    ಪೂರ್ಣಾಂಕ ಪಠ್ಯ_ಉದ್ದಳತೆ = 0;
    ಅಕ್ಷರ ಪಠ್ಯ[64];
    ಸ್ಥಿತಿ_3 ಸ್ಥಿತಿ_2 = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == ಕೀಲಿ_Press);
    SDL_Scancode scancode = videodata->keyboard.ಕೀಲಿ_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.ಸಮಯ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.ಕಿಟಕಿ, (xevent->type == ಕೀಲಿ_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_SCANCODES
    ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        ಪೂರ್ಣಾಂಕ min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_ಕೀಲಿ_ಸಂಕೇತ_ಗಮ್ಯ_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysym_ಗಮ್ಯ_String(keysym));
    }
#ಆದರೆ_ಅಂತ್ಯ // DEBUG SCANCODES

    ಪಠ್ಯ[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    ಆದರೆ (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (ಸರಿಸು_ಮುಖವಾಡ_2 | Control_ಮುಖವಾಡ | Mod1_ಮುಖವಾಡ | Mod3_ಮುಖವಾಡ | Mod4_ಮುಖವಾಡ | Mod5_ಮುಖವಾಡ);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (ಬೀಗ_ಮುಖವಾಡ | videodata->keyboard.numlock_ಮುಖವಾಡ | videodata->keyboard.scrolllock_ಮುಖವಾಡ);
    }

    ಆದರೆ (SDL_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ(windowdata->ಕಿಟಕಿ)) {
        // filter events catches XIM events and sends them to the correct handler
        ಆದರೆ (X11_XFilterEvent(xevent, None)) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
            handled_by_ime = true;
        }

        ಆದರೆ (!handled_by_ime) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
            ಆದರೆ (windowdata->ic && xevent->type == ಕೀಲಿ_Press) {
                ಪಠ್ಯ_ಉದ್ದಳತೆ = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, ಪಠ್ಯ, ಗಾತ್ರ(ಪಠ್ಯ) - 1,
                                      &keysym, &ಸ್ಥಿತಿ_2);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಪಠ್ಯ_ಉದ್ದಳತೆ = XLookupStringAsUTF8(&xevent->xkey, ಪಠ್ಯ, ಗಾತ್ರ(ಪಠ್ಯ) - 1, &keysym, ಖಾಲಿ);
            }
#ಇಲ್ಲದಿದ್ದರೆ
            ಪಠ್ಯ_ಉದ್ದಳತೆ = XLookupStringAsUTF8(&xevent->xkey, ಪಠ್ಯ, ಗಾತ್ರ(ಪಠ್ಯ) - 1, &keysym, ಖಾಲಿ);
#ಆದರೆ_ಅಂತ್ಯ
        }
    }

    ಆದರೆ (!handled_by_ime) {
        ಆದರೆ (pressed) {
            X11_Handle_Modifier_ಕೀಲಿಗಳು(videodata, scancode, true);
            SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            ಆದರೆ (*ಪಠ್ಯ && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                ಪಠ್ಯ[ಪಠ್ಯ_ಉದ್ದಳತೆ] = '\0';
                X11_ClearComposition(windowdata);
                SDL_Send_Keyboard_ಪಠ್ಯ(ಪಠ್ಯ);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (X11_ಕೀಲಿ_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                ಹಿಂತಿರುಗಿ;
            }

            X11_Handle_Modifier_ಕೀಲಿಗಳು(videodata, scancode, false);
            SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    ಆದರೆ (pressed) {
        X11_Update_User_ಸಮಯ(windowdata, xevent->xkey.ಸಮಯ);
    }
}

ಶೂನ್ಯ X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata, SDL_MouseID mouseID, ಪೂರ್ಣಾಂಕ button, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಸಮಯ, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ serial)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = windowdata->ಕಿಟಕಿ;
    ಪೂರ್ಣಾಂಕ xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(ಸಮಯ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#ಆದರೆ_ಅಂತ್ಯ

    SDL_Mouse *mouse = SDL_GetMouse();
    ಆದರೆ (!mouse->relative_ಬಹುಲಕ && (x != mouse->x || y != mouse->y)) {
        X11_Process_ದೊರಕಿತು_Test(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, ಕಿಟಕಿ, mouseID, false, x, y);
    }

    ಆದರೆ (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, ಕಿಟಕಿ, mouseID, (ದಶಮಾಂಶ)-xticks, (ದಶಮಾಂಶ)yticks, SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        ಆದರೆ (button == Button1) {
            ಆದರೆ (X11_Trigger_ದೊರಕಿತು_Test_Action(_this, windowdata, x, y)) {
                SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_ದೊರಕಿತು_TEST, 0, 0);
                ಹಿಂತಿರುಗಿ; // don't pass this event on to app.
            }
        }
        ಆದರೆ (windowdata->ಕೊನೆಯ_focus_event_ಸಮಯ) {
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ X11_FOCUS_CLICK_TIMEOUT = 10;
            ಆದರೆ (SDL_GetTicks() < (windowdata->ಕೊನೆಯ_focus_event_ಸಮಯ + X11_FOCUS_CLICK_TIMEOUT)) {
                ಆದರೆ (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->ಕೊನೆಯ_focus_event_ಸಮಯ = 0;
        }
        ಆದರೆ (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, ಕಿಟಕಿ, mouseID, button, true);
        }
    }
    X11_Update_User_ಸಮಯ(windowdata, ಸಮಯ);
}

ಶೂನ್ಯ X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata, SDL_MouseID mouseID, ಪೂರ್ಣಾಂಕ button, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಸಮಯ)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = windowdata->ಕಿಟಕಿ;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    ಪೂರ್ಣಾಂಕ xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(ಸಮಯ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        ಆದರೆ (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, ಕಿಟಕಿ, mouseID, button, false);

        ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ->pending_grab) {
            X11_ಗಣ_ಕಿಟಕಿ_Mouse_Grab(_this, ಕಿಟಕಿ, true);
        }
    }
}

ಶೂನ್ಯ X11_Get_Border_ಮೌಲ್ಯಗಳು(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = ದತ್ತಾಂಶ->videodata;
    Display *display = videodata->display;

    Atom type;
    ಪೂರ್ಣಾಂಕ format;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ nitems, ಬೈಟುಗಳು_after;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    ಆದರೆ (!(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS)) {
        ಆದರೆ (X11_XGet_ಕಿಟಕಿ_Property(display, ದತ್ತಾಂಶ->xwindow, videodata->atoms.NET_ಚೌಕಟ್ಟು_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &ಬೈಟುಗಳು_after, &property) == Success) {
            ಆದರೆ (type != None && nitems == 4) {
                ದತ್ತಾಂಶ->border_ಎಡ = (ಪೂರ್ಣಾಂಕ)((ದೀರ್ಘ *)property)[0];
                ದತ್ತಾಂಶ->border_ಬಲ = (ಪೂರ್ಣಾಂಕ)((ದೀರ್ಘ *)property)[1];
                ದತ್ತಾಂಶ->border_ತುದಿ = (ಪೂರ್ಣಾಂಕ)((ದೀರ್ಘ *)property)[2];
                ದತ್ತಾಂಶ->border_bottom = (ಪೂರ್ಣಾಂಕ)((ದೀರ್ಘ *)property)[3];
            }
            X11_XFree(property);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", ದತ್ತಾಂಶ->border_ಎಡ, ದತ್ತಾಂಶ->border_ಬಲ, ದತ್ತಾಂಶ->border_ತುದಿ, ದತ್ತಾಂಶ->border_bottom);
#ಆದರೆ_ಅಂತ್ಯ
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->border_ಎಡ = ದತ್ತಾಂಶ->border_ತುದಿ = ದತ್ತಾಂಶ->border_ಬಲ = ದತ್ತಾಂಶ->border_bottom = 0;
    }
}

ಶೂನ್ಯ X11_EmitConfigureNotifyEvents(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, XConfigureEvent *xevent)
{
    ಆದರೆ (!ದತ್ತಾಂಶ->ಗಾತ್ರ_move_event_flags) {
        ಪೂರ್ಣಾಂಕ x = xevent->x;
        ಪೂರ್ಣಾಂಕ y = xevent->y;

        ಆದರೆ (xevent->x != ದತ್ತಾಂಶ->ಕೊನೆಯ_xconfigure.x ||
            xevent->y != ದತ್ತಾಂಶ->ಕೊನೆಯ_xconfigure.y) {
            ದತ್ತಾಂಶ->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_Global_ಗಮ್ಯ_Relative_For_ಕಿಟಕಿ(ದತ್ತಾಂಶ->ಕಿಟಕಿ, x, y, &x, &y);
        SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MOVED, x, y);

        ಗಾಗಿ (SDL_ಕಿಟಕಿ *w = ದತ್ತಾಂಶ->ಕಿಟಕಿ->ಮೊದಲ_ಮಗು; w; w = w->ಮುಂದಿನ_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(w) && !(w->flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
                X11_Update_ಕಿಟಕಿ_Position(w, true);
            }
        }

        ಆದರೆ (xevent->ಅಗಲ != ದತ್ತಾಂಶ->ಕೊನೆಯ_xconfigure.ಅಗಲ ||
            xevent->ಎತ್ತರ != ದತ್ತಾಂಶ->ಕೊನೆಯ_xconfigure.ಎತ್ತರ) {
            ದತ್ತಾಂಶ->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, xevent->ಅಗಲ, xevent->ಎತ್ತರ);
    }

    SDL_copyp(&ದತ್ತಾಂಶ->ಕೊನೆಯ_xconfigure, xevent);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    Display *display;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    XClient_ಸಂದೇಶ_Event m;
    ಪೂರ್ಣಾಂಕ i;

    SDL_assert(videodata != ಖಾಲಿ);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    ಆದರೆ (xevent->type != ಕೀಲಿ_Press && xevent->type != ಕೀಲಿ_Release) {
        ಆದರೆ (X11_XFilterEvent(xevent, None)) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
            ಹಿಂತಿರುಗಿ;
        }
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    ಆದರೆ (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        ಹಿಂತಿರುಗಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    ಆದರೆ (g_X11EventHook) {
        ಆದರೆ (!g_X11EventHook(g_X11_Event_Hook_ದತ್ತಾಂಶ, xevent)) {
            ಹಿಂತಿರುಗಿ;
        }
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
    ಆದರೆ (videodata->xrandr_event_ತಳ && (xevent->type == (videodata->xrandr_event_ತಳ + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
    ಆದರೆ (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ (ev->subtype == XFixes_ಗಣ_Selection_Owner_Notify)
        {
            ಆದರೆ (ev->selection != videodata->atoms.CLIPBOARD)
                ಹಿಂತಿರುಗಿ;

            ಆದರೆ (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_ಕಿಟಕಿ)
                ಹಿಂತಿರುಗಿ;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, Get_ಕಿಟಕಿ(_this), Current_ಸಮಯ);
        }

        ಹಿಂತಿರುಗಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XFIXES

    ಆದರೆ ((videodata->clipboard_ಕಿಟಕಿ != None) &&
        (videodata->clipboard_ಕಿಟಕಿ == xevent->xany.ಕಿಟಕಿ)) {
        X11_HandleClipboardEvent(_this, xevent);
        ಹಿಂತಿರುಗಿ;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    ದತ್ತಾಂಶ = X11_ಕಂಡುಹಿಡಿ_ಕಿಟಕಿ(videodata, xevent->xany.ಕಿಟಕಿ);

    ಆದರೆ (!ದತ್ತಾಂಶ) {
        // The window for KeymapNotify, etc events is 0
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        ಆದರೆ (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            ಆಯ್ಕೆ (xkbevent->any.xkb_type) {
            ಸ್ಥಿತಿ XkbStateNotify:
            {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
                ಆದರೆ ((xkbevent->state.ಬದಲಾಯಿತು & Xkb_ಗುಂಪು_State_ಮುಖವಾಡ) && xkbevent->state.ಗುಂಪು != videodata->keyboard.xkb.current_ಗುಂಪು) {
                    videodata->keyboard.xkb.current_ಗುಂಪು = xkbevent->state.ಗುಂಪು;
                    SDL_ಗಣ_Keymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_ಗುಂಪು], true);
                }

                ಆದರೆ (xkbevent->state.ಬದಲಾಯಿತು & Xkb_Modifier_State_ಮುಖವಾಡ) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.ತಳ_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } ನಿಲ್ಲಿಸು;

            ಸ್ಥಿತಿ XkbMapNotify:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.ಕಿಟಕಿ);
                SDL_FALLTHROUGH;
#ಆದರೆ_ಅಂತ್ಯ
            ಸ್ಥಿತಿ XkbNewKeyboardNotify:
            {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
                ಆದರೆ (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.ಕಿಟಕಿ);
                }
#ಆದರೆ_ಅಂತ್ಯ
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                ಆದರೆ (xkbevent->any.serial != videodata->keyboard.xkb.ಕೊನೆಯ_map_serial) {
                    videodata->keyboard.xkb.ಕೊನೆಯ_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } ನಿಲ್ಲಿಸು;

            ಪೂರ್ವನಿಯೋಜಿತ:
                ನಿಲ್ಲಿಸು;
            }
        } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (xevent->type == KeymapNotify) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
            ಆದರೆ (SDL_GetKeyboardFocus() != ಖಾಲಿ) {
                ಆದರೆ (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (xevent->type == MappingNotify) {
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ request = xevent->xmapping.request;

            ಆದರೆ (request == Mapping_ಸೂಚಕ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
                X11_Xinput2_Update_ಸೂಚಕ_Mapping(_this);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
                ಆದರೆ (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (xevent->type == PropertyNotify && videodata) {
            ಅಕ್ಷರ *name_ದ_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            ಆದರೆ (name_ದ_atom) {
                ಆದರೆ (SDL_startswith(name_ದ_atom, "_ICC_PROFILE")) {
                    XWindow_ಗುಣಲಕ್ಷಣಗಳು attrib;
                    ಪೂರ್ಣಾಂಕ screennum;
                    ಗಾಗಿ (i = 0; i < videodata->numwindows; ++i) {
                        ಆದರೆ (videodata->windowlist[i] != ಖಾಲಿ) {
                            ದತ್ತಾಂಶ = videodata->windowlist[i];
                            X11_XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು(display, ದತ್ತಾಂಶ->xwindow, &attrib);
                            screennum = X11_XScreen_ಸಂಖ್ಯೆ_ದ_Screen(attrib.screen);
                            ಆದರೆ (screennum == 0 && SDL_strcmp(name_ದ_atom, "_ICC_PROFILE") == 0) {
                                SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_ICCPROF_ಬದಲಾಯಿತು, 0, 0);
                            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strncmp(name_ದ_atom, "_ICC_PROFILE_", ಗಾತ್ರ("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_ದ_atom) > ಗಾತ್ರ("_ICC_PROFILE_") - 1) {
                                ಪೂರ್ಣಾಂಕ iccscreennum = SDL_atoi(&name_ದ_atom[ಗಾತ್ರ("_ICC_PROFILE_") - 1]);

                                ಆದರೆ (screennum == iccscreennum) {
                                    SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_ICCPROF_ಬದಲಾಯಿತು, 0, 0);
                                }
                            }
                        }
                    }
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(name_ದ_atom, "_NET_WORKAREA") == 0) {
                    ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_ಬದಲಾಯಿತು, 0, 0);
                    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(name_ದ_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_ದ_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#ಆದರೆ_ಅಂತ್ಯ
                }
                X11_XFree(name_ದ_atom);
            }
        }
        ಹಿಂತಿರುಗಿ;
    }

    ಆಯ್ಕೆ (xevent->type) {

        // Gaining mouse coverage?
    ಸ್ಥಿತಿ EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.ಕಿಟಕಿ,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.ಬಹುಲಕ);
        ಆದರೆ (xevent->xcrossing.ಬಹುಲಕ == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        ಆದರೆ (xevent->xcrossing.ಬಹುಲಕ == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#ಆದರೆ_ಅಂತ್ಯ
        SDL_ಗಣ_Mouse_Focus(ದತ್ತಾಂಶ->ಕಿಟಕಿ);

        mouse->ಕೊನೆಯ_x = xevent->xcrossing.x;
        mouse->ಕೊನೆಯ_y = xevent->xcrossing.y;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
        {
            // Only create the barriers if we have input focus
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = ದತ್ತಾಂಶ->ಕಿಟಕಿ->ಆಂತರಿಕ;
            ಆದರೆ ((ದತ್ತಾಂಶ->ಸೂಚಕ_barrier_ಸಕ್ರಿಯ == true) && windowdata->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->ಕಿಟಕಿ, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ (!mouse->relative_ಬಹುಲಕ) {
            SDL_SendMouseMotion(0, ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_GLOBAL_MOUSE_ID, false, (ದಶಮಾಂಶ)xevent->xcrossing.x, (ದಶಮಾಂಶ)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        ಆದರೆ (!(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_CAPTURE)) {
            SDL_Update_ಕಿಟಕಿ_Grab(ದತ್ತಾಂಶ->ಕಿಟಕಿ);
        }

        X11_Process_ದೊರಕಿತು_Test(_this, ದತ್ತಾಂಶ, mouse->ಕೊನೆಯ_x, mouse->ಕೊನೆಯ_y, true);
    } ನಿಲ್ಲಿಸು;
        // Losing mouse coverage?
    ಸ್ಥಿತಿ LeaveNotify:
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.ಕಿಟಕಿ,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.ಬಹುಲಕ);
        ಆದರೆ (xevent->xcrossing.ಬಹುಲಕ == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        ಆದರೆ (xevent->xcrossing.ಬಹುಲಕ == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (!SDL_GetMouse()->relative_ಬಹುಲಕ) {
            SDL_SendMouseMotion(0, ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_GLOBAL_MOUSE_ID, false, (ದಶಮಾಂಶ)xevent->xcrossing.x, (ದಶಮಾಂಶ)xevent->xcrossing.y);
        }

        ಆದರೆ (xevent->xcrossing.ಬಹುಲಕ != NotifyGrab &&
            xevent->xcrossing.ಬಹುಲಕ != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            ಆದರೆ (!(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
                X11_ಗಣ_ಕಿಟಕಿ_Keyboard_Grab(_this, ದತ್ತಾಂಶ->ಕಿಟಕಿ, false);
            }

            SDL_ಗಣ_Mouse_Focus(ಖಾಲಿ);
        }
    } ನಿಲ್ಲಿಸು;

        // Gaining input focus?
    ಸ್ಥಿತಿ Focus_ಒಳ:
    {
        ಆದರೆ (xevent->xfocus.ಬಹುಲಕ == NotifyGrab || xevent->xfocus.ಬಹುಲಕ == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
            ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_ಸೂಚಕ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
            ನಿಲ್ಲಿಸು;
        }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (!videodata->ಕೊನೆಯ_ಬಹುಲಕ_change_deadline) /* no recent mode changes */ {
            ದತ್ತಾಂಶ->pending_focus = PENDING_FOCUS_NONE;
            ದತ್ತಾಂಶ->pending_focus_ಸಮಯ = 0;
            X11_Dispatch_Focus_ಒಳ(_this, ದತ್ತಾಂಶ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ದತ್ತಾಂಶ->pending_focus = PENDING_FOCUS_ಒಳ;
            ದತ್ತಾಂಶ->pending_focus_ಸಮಯ = SDL_GetTicks() + PENDING_FOCUS_ಸಮಯ;
        }
        ದತ್ತಾಂಶ->ಕೊನೆಯ_focus_event_ಸಮಯ = SDL_GetTicks();
    } ನಿಲ್ಲಿಸು;

        // Losing input focus?
    ಸ್ಥಿತಿ Focus_ಹೊರಹೋಗು:
    {
        ಆದರೆ (xevent->xfocus.ಬಹುಲಕ == NotifyGrab || xevent->xfocus.ಬಹುಲಕ == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
            ನಿಲ್ಲಿಸು;
        }
        ಆದರೆ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_ಸೂಚಕ) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
            ನಿಲ್ಲಿಸು;
        }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (!videodata->ಕೊನೆಯ_ಬಹುಲಕ_change_deadline) /* no recent mode changes */ {
            ದತ್ತಾಂಶ->pending_focus = PENDING_FOCUS_NONE;
            ದತ್ತಾಂಶ->pending_focus_ಸಮಯ = 0;
            X11_Dispatch_Focus_ಹೊರಹೋಗು(_this, ದತ್ತಾಂಶ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ದತ್ತಾಂಶ->pending_focus = PENDING_FOCUS_ಹೊರಹೋಗು;
            ದತ್ತಾಂಶ->pending_focus_ಸಮಯ = SDL_GetTicks() + PENDING_FOCUS_ಸಮಯ;
        }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        ಆದರೆ (ದತ್ತಾಂಶ->ಸೂಚಕ_barrier_ಸಕ್ರಿಯ == true) {
            X11_ConfineCursorWithFlags(_this, ದತ್ತಾಂಶ->ಕಿಟಕಿ, ಖಾಲಿ, X11_BARRIER_HANDLED_BY_EVENT);
        }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XFIXES
    } ನಿಲ್ಲಿಸು;


        // Have we been iconified?
    ಸ್ಥಿತಿ UnmapNotify:
    {
        XEvent ev;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } ಇಲ್ಲದಿದ್ದರೆ {
            X11_DispatchUnmapNotify(ದತ್ತಾಂಶ);
        }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        ಆದರೆ (ದತ್ತಾಂಶ->ಸೂಚಕ_barrier_ಸಕ್ರಿಯ == true) {
            X11_ConfineCursorWithFlags(_this, ದತ್ತಾಂಶ->ಕಿಟಕಿ, ಖಾಲಿ, X11_BARRIER_HANDLED_BY_EVENT);
        }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XFIXES
    } ನಿಲ್ಲಿಸು;

        // Have we been restored?
    ಸ್ಥಿತಿ MapNotify:
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
        X11_DispatchMapNotify(ದತ್ತಾಂಶ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        ಆದರೆ (ದತ್ತಾಂಶ->ಸೂಚಕ_barrier_ಸಕ್ರಿಯ == true) {
            X11_ConfineCursorWithFlags(_this, ದತ್ತಾಂಶ->ಕಿಟಕಿ, &ದತ್ತಾಂಶ->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XFIXES
    } ನಿಲ್ಲಿಸು;

        // Have we been resized or moved?
    ಸ್ಥಿತಿ ConfigureNotify:
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.ಕಿಟಕಿ,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.ಅಗಲ, xevent->xconfigure.ಎತ್ತರ);
#ಆದರೆ_ಅಂತ್ಯ
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        ಆದರೆ (!xevent->xconfigure.send_event) {
            ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಅಂಕೆ_Children;
            ಕಿಟಕಿ_2 ಮಗು_Return, ಬೇರು_2, ಪೋಷಕ_2;
            ಕಿಟಕಿ_2 *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_ಕೊನೆಯ_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_ಕಿಟಕಿ_Error_Handler);

            X11_XQuery_ವೃಕ್ಷ(ದತ್ತಾಂಶ->videodata->display, xevent->xconfigure.ಕಿಟಕಿ, &ಬೇರು_2, &ಪೋಷಕ_2, &Children, &ಅಂಕೆ_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      ಪೋಷಕ_2, Default_ಬೇರು_ಕಿಟಕಿ(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &ಮಗು_Return);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            ಆದರೆ (x11_ಕೊನೆಯ_error == Bad_ಕಿಟಕಿ) {
                ನಿಲ್ಲಿಸು;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_Flags ಬದಲಾಯಿತು = X11_GetNetWMState(_this, ದತ್ತಾಂಶ->ಕಿಟಕಿ, xevent->xproperty.ಕಿಟಕಿ) ^ ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags;
        ಆದರೆ (ಬದಲಾಯಿತು & (SDL_ಕಿಟಕಿ_FULLSCREEN | SDL_ಕಿಟಕಿ_MAXIMIZED)) {
            SDL_copyp(&ದತ್ತಾಂಶ->pending_xconfigure, &xevent->xconfigure);
            ದತ್ತಾಂಶ->emit_ಗಾತ್ರ_move_after_property_notify = true;
        }

        ಆದರೆ (!ದತ್ತಾಂಶ->emit_ಗಾತ್ರ_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(ದತ್ತಾಂಶ, &xevent->xconfigure);
        }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(ದತ್ತಾಂಶ->ಕಿಟಕಿ, &xevent->xconfigure);
#ಆದರೆ_ಅಂತ್ಯ /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } ನಿಲ್ಲಿಸು;

        // Have we been requested to quit (or another client message?)
    ಸ್ಥಿತಿ Client_ಸಂದೇಶ:
    {
        ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ xdnd_ಆವೃತ್ತಿ = 0;

        ಆದರೆ (xevent->xclient.ಸಂದೇಶ_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.ದತ್ತಾಂಶ.l[1] & 1;
            ದತ್ತಾಂಶ->xdnd_ಮೂಲ = xevent->xclient.ದತ್ತಾಂಶ.l[0];
            xdnd_ಆವೃತ್ತಿ = (xevent->xclient.ದತ್ತಾಂಶ.l[1] >> 24);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", ದತ್ತಾಂಶ->xdnd_ಮೂಲ);
            SDL_Log("Protocol version to use : %d", xdnd_ಆವೃತ್ತಿ);
            SDL_Log("More then 3 data types : %d", (ಪೂರ್ಣಾಂಕ)use_list);
#ಆದರೆ_ಅಂತ್ಯ

            ಆದರೆ (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, ದತ್ತಾಂಶ->xdnd_ಮೂಲ, videodata->atoms.XdndTypeList);
                // pick one
                ದತ್ತಾಂಶ->xdnd_req = X11_Pick_ಗುರಿ(display, (Atom *)p.ದತ್ತಾಂಶ, p.ಎಣಿಕೆ_2);
                X11_XFree(p.ದತ್ತಾಂಶ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                // pick from list of three
                ದತ್ತಾಂಶ->xdnd_req = X11_Pick_ಗುರಿ_From_Atoms(display, xevent->xclient.ದತ್ತಾಂಶ.l[2], xevent->xclient.ದತ್ತಾಂಶ.l[3], xevent->xclient.ದತ್ತಾಂಶ.l[4]);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (xevent->xclient.ಸಂದೇಶ_type == videodata->atoms.XdndLeave) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.ದತ್ತಾಂಶ.l[0]);
#ಆದರೆ_ಅಂತ್ಯ
            SDL_SendDropComplete(ದತ್ತಾಂಶ->ಕಿಟಕಿ);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (xevent->xclient.ಸಂದೇಶ_type == videodata->atoms.XdndPosition) {

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            ಆದರೆ (xdnd_ಆವೃತ್ತಿ >= 2) {
                act = xevent->xclient.ದತ್ತಾಂಶ.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#ಆದರೆ_ಅಂತ್ಯ
            {
                // Drag and Drop position
                ಪೂರ್ಣಾಂಕ ಬೇರು_x, ಬೇರು_y, ಕಿಟಕಿ_x, ಕಿಟಕಿ_y;
                ಕಿಟಕಿ_2 ಮಗು_Return;
                ಬೇರು_x = xevent->xclient.ದತ್ತಾಂಶ.l[2] >> 16;
                ಬೇರು_y = xevent->xclient.ದತ್ತಾಂಶ.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_ಬೇರು_ಕಿಟಕಿ(display), ದತ್ತಾಂಶ->xwindow,
                                          ಬೇರು_x, ಬೇರು_y, &ಕಿಟಕಿ_x, &ಕಿಟಕಿ_y, &ಮಗು_Return);

                SDL_SendDropPosition(ದತ್ತಾಂಶ->ಕಿಟಕಿ, (ದಶಮಾಂಶ)ಕಿಟಕಿ_x, (ದಶಮಾಂಶ)ಕಿಟಕಿ_y);
            }

            // reply with status
            SDL_zero(m);
            m.type = Client_ಸಂದೇಶ;
            m.display = xevent->xclient.display;
            m.ಕಿಟಕಿ = xevent->xclient.ದತ್ತಾಂಶ.l[0];
            m.ಸಂದೇಶ_type = videodata->atoms.Xdnd_ಸ್ಥಿತಿ;
            m.format = 32;
            m.ದತ್ತಾಂಶ.l[0] = ದತ್ತಾಂಶ->xwindow;
            m.ದತ್ತಾಂಶ.l[1] = (ದತ್ತಾಂಶ->xdnd_req != None);
            m.ದತ್ತಾಂಶ.l[2] = 0; // specify an empty rectangle
            m.ದತ್ತಾಂಶ.l[3] = 0;
            m.ದತ್ತಾಂಶ.l[4] = videodata->atoms.XdndActionCopy; // we only accept copying anyway

            X11_XSendEvent(display, xevent->xclient.ದತ್ತಾಂಶ.l[0], False, No_Event_ಮುಖವಾಡ, (XEvent *)&m);
            X11_XFlush(display);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (xevent->xclient.ಸಂದೇಶ_type == videodata->atoms.XdndDrop) {
            ಆದರೆ (ದತ್ತಾಂಶ->xdnd_req == None) {
                // say again - not interested!
                SDL_zero(m);
                m.type = Client_ಸಂದೇಶ;
                m.display = xevent->xclient.display;
                m.ಕಿಟಕಿ = xevent->xclient.ದತ್ತಾಂಶ.l[0];
                m.ಸಂದೇಶ_type = videodata->atoms.Xdnd_ಪೂರ್ಣಗೊಂಡ;
                m.format = 32;
                m.ದತ್ತಾಂಶ.l[0] = ದತ್ತಾಂಶ->xwindow;
                m.ದತ್ತಾಂಶ.l[1] = 0;
                m.ದತ್ತಾಂಶ.l[2] = None; // fail!
                X11_XSendEvent(display, xevent->xclient.ದತ್ತಾಂಶ.l[0], False, No_Event_ಮುಖವಾಡ, (XEvent *)&m);
            } ಇಲ್ಲದಿದ್ದರೆ {
                // convert
                ಆದರೆ (xdnd_ಆವೃತ್ತಿ >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, ದತ್ತಾಂಶ->xdnd_req, videodata->atoms.PRIMARY, ದತ್ತಾಂಶ->xwindow, xevent->xclient.ದತ್ತಾಂಶ.l[2]);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, ದತ್ತಾಂಶ->xdnd_req, videodata->atoms.PRIMARY, ದತ್ತಾಂಶ->xwindow, Current_ಸಮಯ);
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((xevent->xclient.ಸಂದೇಶ_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.ದತ್ತಾಂಶ.l[0] == videodata->atoms._NET_WM_PING)) {
            ಕಿಟಕಿ_2 ಬೇರು = Default_ಬೇರು_ಕಿಟಕಿ(display);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
            xevent->xclient.ಕಿಟಕಿ = ಬೇರು;
            X11_XSendEvent(display, ಬೇರು, False, Substructure_Redirect_ಮುಖವಾಡ | Substructure_Notify_ಮುಖವಾಡ, xevent);
            ನಿಲ್ಲಿಸು;
        }

        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((xevent->xclient.ಸಂದೇಶ_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.ದತ್ತಾಂಶ.l[0] == videodata->atoms.WM_DELETE_ಕಿಟಕಿ)) {

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_CLOSE_REQUESTED, 0, 0);
            ನಿಲ್ಲಿಸು;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((xevent->xclient.ಸಂದೇಶ_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.ದತ್ತಾಂಶ.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", ದತ್ತಾಂಶ);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(ದತ್ತಾಂಶ->ಕಿಟಕಿ, &xevent->xclient);
#ಆದರೆ_ಅಂತ್ಯ /* SDL_VIDEO_DRIVER_X11_XSYNC */
            ನಿಲ್ಲಿಸು;
        }
    } ನಿಲ್ಲಿಸು;

        // Do we need to refresh ourselves?
    ಸ್ಥಿತಿ Expose:
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.ಕಿಟಕಿ, xevent->xexpose.ಎಣಿಕೆ_2);
#ಆದರೆ_ಅಂತ್ಯ
        SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_EXPOSED, 0, 0);
    } ನಿಲ್ಲಿಸು;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    ಸ್ಥಿತಿ ಕೀಲಿ_Press:
    ಸ್ಥಿತಿ ಕೀಲಿ_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        ಆದರೆ (ದತ್ತಾಂಶ->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            ನಿಲ್ಲಿಸು;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (xevent->xkey.serial == videodata->xinput_ಕೊನೆಯ_ಕೀಲಿ_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_ಕೊನೆಯ_keyboard_device;
        }

        X11_Handle_ಕೀಲಿ_Event(_this, ದತ್ತಾಂಶ, keyboardID, xevent);
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ MotionNotify:
    {
        ಆದರೆ (X11_Xinput2_Handles_Motion_For_ಕಿಟಕಿ(ದತ್ತಾಂಶ)) {
            // This input is being handled by XInput2
            ನಿಲ್ಲಿಸು;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        ಆದರೆ (!mouse->relative_ಬಹುಲಕ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.ಕಿಟಕಿ, xevent->xmotion.x, xevent->xmotion.y);
#ಆದರೆ_ಅಂತ್ಯ

            X11_Process_ದೊರಕಿತು_Test(_this, ದತ್ತಾಂಶ, (ದಶಮಾಂಶ)xevent->xmotion.x, (ದಶಮಾಂಶ)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_GLOBAL_MOUSE_ID, false, (ದಶಮಾಂಶ)xevent->xmotion.x, (ದಶಮಾಂಶ)xevent->xmotion.y);
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ButtonPress:
    {
        ಆದರೆ (ದತ್ತಾಂಶ->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_ಕೊನೆಯ_button_serial) {
            // This input event was handled by XInput2.
            ನಿಲ್ಲಿಸು;
        }

        X11_HandleButtonPress(_this, ದತ್ತಾಂಶ, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.ಸಮಯ, xevent->xbutton.serial);
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ButtonRelease:
    {
        ಆದರೆ (ದತ್ತಾಂಶ->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_ಕೊನೆಯ_button_serial) {
            // This input event was handled by XInput2.
            ನಿಲ್ಲಿಸು;
        }

        X11_HandleButtonRelease(_this, ದತ್ತಾಂಶ, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.ಸಮಯ);
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ PropertyNotify:
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *propdata;
        ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2, real_format;
        Atom real_type;
        ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ವಸ್ತುಗಳು_read, ವಸ್ತುಗಳು_ಎಡ;

        ಅಕ್ಷರ *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        ಆದರೆ (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.ಕಿಟಕಿ, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.ಸಮಯ);
            X11_XFree(name);
        }

        ಸ್ಥಿತಿ_2 = X11_XGet_ಕಿಟಕಿ_Property(display, ದತ್ತಾಂಶ->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ, &propdata);
        ಆದರೆ (ಸ್ಥಿತಿ_2 == Success && ವಸ್ತುಗಳು_read > 0) {
            ಆದರೆ (real_type == XA_INTEGER) {
                ಪೂರ್ಣಾಂಕ *ಮೌಲ್ಯಗಳು = (ಪೂರ್ಣಾಂಕ *)propdata;

                SDL_Log("{");
                ಗಾಗಿ (i = 0; i < ವಸ್ತುಗಳು_read; i++) {
                    SDL_Log(" %d", ಮೌಲ್ಯಗಳು[i]);
                }
                SDL_Log(" }");
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (real_type == XA_CARDINAL) {
                ಆದರೆ (real_format == 32) {
                    Uint32 *ಮೌಲ್ಯಗಳು = (Uint32 *)propdata;

                    SDL_Log("{");
                    ಗಾಗಿ (i = 0; i < ವಸ್ತುಗಳು_read; i++) {
                        SDL_Log(" %d", ಮೌಲ್ಯಗಳು[i]);
                    }
                    SDL_Log(" }");
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (real_format == 16) {
                    Uint16 *ಮೌಲ್ಯಗಳು = (Uint16 *)propdata;

                    SDL_Log("{");
                    ಗಾಗಿ (i = 0; i < ವಸ್ತುಗಳು_read; i++) {
                        SDL_Log(" %d", ಮೌಲ್ಯಗಳು[i]);
                    }
                    SDL_Log(" }");
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (real_format == 8) {
                    Uint8 *ಮೌಲ್ಯಗಳು = (Uint8 *)propdata;

                    SDL_Log("{");
                    ಗಾಗಿ (i = 0; i < ವಸ್ತುಗಳು_read; i++) {
                        SDL_Log(" %d", ಮೌಲ್ಯಗಳು[i]);
                    }
                    SDL_Log(" }");
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                ಗಾಗಿ (i = 0; i < ವಸ್ತುಗಳು_read; i++) {
                    ಅಕ್ಷರ *atomname = X11_XGetAtomName(display, atoms[i]);
                    ಆದರೆ (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಅಕ್ಷರ *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                ಆದರೆ (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        ಆದರೆ (ಸ್ಥಿತಿ_2 == Success) {
            X11_XFree(propdata);
        }
#ಆದರೆ_ಅಂತ್ಯ // DEBUG_XEVENTS

        /* Take advantage of this moment to make sure user_time has a
            valid timestamp from the X server, so if we later try to
            raise/restore this window, _NET_ACTIVE_WINDOW can have a
            non-zero timestamp, even if there's never been a mouse or
            key press to this window so far. Note that we don't try to
            set _NET_WM_USER_TIME here, though. That's only for legit
            user interaction with the window. */
        ಆದರೆ (!ದತ್ತಾಂಶ->user_ಸಮಯ) {
            ದತ್ತಾಂಶ->user_ಸಮಯ = xevent->xproperty.ಸಮಯ;
        }

        ಆದರೆ (xevent->xproperty.atom == ದತ್ತಾಂಶ->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_Flags flags = X11_GetNetWMState(_this, ದತ್ತಾಂಶ->ಕಿಟಕಿ, xevent->xproperty.ಕಿಟಕಿ);
            ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_Flags ಬದಲಾಯಿತು = flags ^ ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags;

            ಆದರೆ ((ಬದಲಾಯಿತು & SDL_ಕಿಟಕಿ_HIDDEN) && !(flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
                X11_DispatchMapNotify(ದತ್ತಾಂಶ);
            }

            ಆದರೆ (!SDL_ಕಿಟಕಿ_IS_POPUP(ದತ್ತಾಂಶ->ಕಿಟಕಿ)) {
                ಆದರೆ (ಬದಲಾಯಿತು & SDL_ಕಿಟಕಿ_FULLSCREEN) {
                    ದತ್ತಾಂಶ->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
                        ಆದರೆ (!(flags & SDL_ಕಿಟಕಿ_MINIMIZED)) {
                            ಸ್ಥಿರಾಂಕ bool commit = SDL_memcmp(&ದತ್ತಾಂಶ->ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ, &ದತ್ತಾಂಶ->requested_fullscreen_ಬಹುಲಕ, ಗಾತ್ರ(SDL_Display_ಬಹುಲಕ)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESTORED, 0, 0);
                            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_ENTER_FULLSCREEN, 0, 0);
                            ಆದರೆ (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&ದತ್ತಾಂಶ->ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ, &ದತ್ತಾಂಶ->ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ);
                                SDL_Update_Fullscreen_ಬಹುಲಕ(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_FULLSCREEN_OP_UPDATE, true);
                            } ಇಲ್ಲದಿದ್ದರೆ {
                                SDL_Update_Fullscreen_ಬಹುಲಕ(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_LEAVE_FULLSCREEN, 0, 0);
                        SDL_Update_Fullscreen_ಬಹುಲಕ(ದತ್ತಾಂಶ->ಕಿಟಕಿ, false, false);

                        SDL_zero(ದತ್ತಾಂಶ->requested_fullscreen_ಬಹುಲಕ);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_ಗಣ_ಕಿಟಕಿ_Min_Max(ದತ್ತಾಂಶ->ಕಿಟಕಿ, !!(flags & SDL_ಕಿಟಕಿ_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        ಆದರೆ (ದತ್ತಾಂಶ->fullscreen_borders_forced_on) {
                            ದತ್ತಾಂಶ->toggle_borders = true;
                            ದತ್ತಾಂಶ->fullscreen_borders_forced_on = false;
                        }
                    }

                    ಆದರೆ ((flags & SDL_ಕಿಟಕಿ_FULLSCREEN) &&
                        (ದತ್ತಾಂಶ->border_ತುದಿ || ದತ್ತಾಂಶ->border_ಎಡ || ದತ್ತಾಂಶ->border_bottom || ದತ್ತಾಂಶ->border_ಬಲ)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        ದತ್ತಾಂಶ->ಗಾತ್ರ_move_event_flags |= X11_ಗಾತ್ರ_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        ದತ್ತಾಂಶ->ಹಿಂದಿನ_borders_nonzero = true;
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(flags & SDL_ಕಿಟಕಿ_FULLSCREEN) &&
                               ದತ್ತಾಂಶ->ಹಿಂದಿನ_borders_nonzero &&
                               (!ದತ್ತಾಂಶ->border_ತುದಿ && !ದತ್ತಾಂಶ->border_ಎಡ && !ದತ್ತಾಂಶ->border_bottom && !ದತ್ತಾಂಶ->border_ಬಲ)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        ದತ್ತಾಂಶ->ಗಾತ್ರ_move_event_flags |= X11_ಗಾತ್ರ_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        ದತ್ತಾಂಶ->ಹಿಂದಿನ_borders_nonzero = false;
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        ದತ್ತಾಂಶ->ಗಾತ್ರ_move_event_flags = 0;
                        ದತ್ತಾಂಶ->ಹಿಂದಿನ_borders_nonzero = false;

                        ಆದರೆ (!(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) && ದತ್ತಾಂಶ->toggle_borders) {
                            ದತ್ತಾಂಶ->toggle_borders = false;
                            X11_ಗಣ_ಕಿಟಕಿ_Bordered(_this, ದತ್ತಾಂಶ->ಕಿಟಕಿ, !(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS));
                        }
                    }
                }
                ಆದರೆ ((ಬದಲಾಯಿತು & SDL_ಕಿಟಕಿ_MAXIMIZED) && ((flags & SDL_ಕಿಟಕಿ_MAXIMIZED) && !(flags & SDL_ಕಿಟಕಿ_MINIMIZED))) {
                    ದತ್ತಾಂಶ->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    ಆದರೆ ((ಬದಲಾಯಿತು & SDL_ಕಿಟಕಿ_MINIMIZED)) {
                        ದತ್ತಾಂಶ->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESTORED, 0, 0);
                    }
                    SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MAXIMIZED, 0, 0);
                }
                ಆದರೆ ((ಬದಲಾಯಿತು & SDL_ಕಿಟಕಿ_MINIMIZED) && (flags & SDL_ಕಿಟಕಿ_MINIMIZED)) {
                    ದತ್ತಾಂಶ->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MINIMIZED, 0, 0);
                }
                ಆದರೆ (!(flags & (SDL_ಕಿಟಕಿ_MAXIMIZED | SDL_ಕಿಟಕಿ_MINIMIZED))) {
                    ದತ್ತಾಂಶ->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    ಆದರೆ (!(flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
                        ಆದರೆ (ದತ್ತಾಂಶ->pending_position) {
                            ದತ್ತಾಂಶ->pending_position = false;
                            ದತ್ತಾಂಶ->pending_operation |= X11_PENDING_OP_MOVE;
                            ದತ್ತಾಂಶ->expected.x = ದತ್ತಾಂಶ->ಕಿಟಕಿ->pending.x - ದತ್ತಾಂಶ->border_ಎಡ;
                            ದತ್ತಾಂಶ->expected.y = ದತ್ತಾಂಶ->ಕಿಟಕಿ->pending.y - ದತ್ತಾಂಶ->border_ತುದಿ;
                            X11_XMove_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, ದತ್ತಾಂಶ->expected.x, ದತ್ತಾಂಶ->expected.y);
                        }
                        ಆದರೆ (ದತ್ತಾಂಶ->pending_ಗಾತ್ರ) {
                            ದತ್ತಾಂಶ->pending_ಗಾತ್ರ = false;
                            ದತ್ತಾಂಶ->pending_operation |= X11_PENDING_OP_RESIZE;
                            ದತ್ತಾಂಶ->expected.w = ದತ್ತಾಂಶ->ಕಿಟಕಿ->pending.w;
                            ದತ್ತಾಂಶ->expected.h = ದತ್ತಾಂಶ->ಕಿಟಕಿ->pending.h;
                            X11_XResize_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->xwindow, ದತ್ತಾಂಶ->ಕಿಟಕಿ->pending.w, ದತ್ತಾಂಶ->ಕಿಟಕಿ->pending.h);
                        }
                    }
                }
                ಆದರೆ (ದತ್ತಾಂಶ->emit_ಗಾತ್ರ_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(ದತ್ತಾಂಶ, &ದತ್ತಾಂಶ->pending_xconfigure);
                    ದತ್ತಾಂಶ->emit_ಗಾತ್ರ_move_after_property_notify = false;
                }
                ಆದರೆ ((flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS)) {
                    ಆದರೆ (ದತ್ತಾಂಶ->pending_move) {
                        Dispatch_ಕಿಟಕಿ_Move(_this, ದತ್ತಾಂಶ, &ದತ್ತಾಂಶ->pending_move_ಬಿಂದು);
                        ದತ್ತಾಂಶ->pending_move = false;
                    }
                }
            }
            ಆದರೆ (ಬದಲಾಯಿತು & SDL_ಕಿಟಕಿ_OCCLUDED) {
                SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, (flags & SDL_ಕಿಟಕಿ_OCCLUDED) ? SDL_EVENT_ಕಿಟಕಿ_OCCLUDED : SDL_EVENT_ಕಿಟಕಿ_EXPOSED, 0, 0);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            ಪೂರ್ಣಾಂಕ format;
            ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ nitems, ಬೈಟುಗಳು_after;
            ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *prop_ದತ್ತಾಂಶ = ಖಾಲಿ;

            ಆದರೆ (X11_XGet_ಕಿಟಕಿ_Property(display, ದತ್ತಾಂಶ->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &ಬೈಟುಗಳು_after, &prop_ದತ್ತಾಂಶ) == Success) {
                ಆದರೆ (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_ದತ್ತಾಂಶ;

                    ಆದರೆ ((state == 0 || state == 3) && !ದತ್ತಾಂಶ->ಕಿಟಕಿ->is_hiding && !(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
                        // Withdrawn or Iconic
                        ಆದರೆ (!(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED)) {
                            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MINIMIZED, 0, 0);
                            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_OCCLUDED, 0, 0);
                        }
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (state == 1) { // NormalState
                        ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED) {
                            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESTORED, 0, 0);
                            SDL_Send_ಕಿಟಕಿ_Event(ದತ್ತಾಂಶ->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_ದತ್ತಾಂಶ);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (xevent->xproperty.atom == videodata->atoms.NET_ಚೌಕಟ್ಟು_EXTENTS) {
            X11_Get_Border_ಮೌಲ್ಯಗಳು(ದತ್ತಾಂಶ);
            ಆದರೆ (ದತ್ತಾಂಶ->ಗಾತ್ರ_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                ದತ್ತಾಂಶ->ಗಾತ್ರ_move_event_flags &= ~X11_ಗಾತ್ರ_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            ಆದರೆ (!(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) && ದತ್ತಾಂಶ->toggle_borders) {
                ದತ್ತಾಂಶ->toggle_borders = false;
                X11_ಗಣ_ಕಿಟಕಿ_Bordered(_this, ದತ್ತಾಂಶ->ಕಿಟಕಿ, !(ದತ್ತಾಂಶ->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS));
            }
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ SelectionNotify:
    {
        Atom ಗುರಿ = xevent->xselection.ಗುರಿ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.ಕಿಟಕಿ,
               xevent->xselection.requestor, xevent->xselection.ಗುರಿ);
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (ಗುರಿ == ದತ್ತಾಂಶ->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, ದತ್ತಾಂಶ->xwindow, videodata->atoms.PRIMARY);

            ಆದರೆ (p.format == 8) {
                ಅಕ್ಷರ *saveptr = ಖಾಲಿ;
                ಅಕ್ಷರ *name = X11_XGetAtomName(display, ಗುರಿ);
                ಆದರೆ (name) {
                    ಅಕ್ಷರ *token = SDL_strtok_r((ಅಕ್ಷರ *)p.ದತ್ತಾಂಶ, "\r\n", &saveptr);
                    ಆಗ (token) {
                        ಆದರೆ ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_Send_Drop_ಪಠ್ಯ(ದತ್ತಾಂಶ->ಕಿಟಕಿ, token);
                        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp("text/uri-list", name) == 0) {
                            ಆದರೆ (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(ದತ್ತಾಂಶ->ಕಿಟಕಿ, ಖಾಲಿ, token);
                            }
                        }
                        token = SDL_strtok_r(ಖಾಲಿ, "\r\n", &saveptr);
                    }
                    X11_XFree(name);
                }
                SDL_SendDropComplete(ದತ್ತಾಂಶ->ಕಿಟಕಿ);
            }
            X11_XFree(p.ದತ್ತಾಂಶ);

            // send reply
            SDL_zero(m);
            m.type = Client_ಸಂದೇಶ;
            m.display = display;
            m.ಕಿಟಕಿ = ದತ್ತಾಂಶ->xdnd_ಮೂಲ;
            m.ಸಂದೇಶ_type = videodata->atoms.Xdnd_ಪೂರ್ಣಗೊಂಡ;
            m.format = 32;
            m.ದತ್ತಾಂಶ.l[0] = ದತ್ತಾಂಶ->xwindow;
            m.ದತ್ತಾಂಶ.l[1] = 1;
            m.ದತ್ತಾಂಶ.l[2] = videodata->atoms.XdndActionCopy;
            X11_XSendEvent(display, ದತ್ತಾಂಶ->xdnd_ಮೂಲ, False, No_Event_ಮುಖವಾಡ, (XEvent *)&m);

            X11_XSync(display, False);
        }
    } ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.ಕಿಟಕಿ, xevent->type);
#ಆದರೆ_ಅಂತ್ಯ
    } ನಿಲ್ಲಿಸು;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (videodata && videodata->windowlist) {
        ಗಾಗಿ (i = 0; i < videodata->numwindows; ++i) {
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = videodata->windowlist[i];
            ಆದರೆ (ದತ್ತಾಂಶ && ದತ್ತಾಂಶ->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                ಆದರೆ (now >= ದತ್ತಾಂಶ->pending_focus_ಸಮಯ) {
                    ಆದರೆ (ದತ್ತಾಂಶ->pending_focus == PENDING_FOCUS_ಒಳ) {
                        X11_Dispatch_Focus_ಒಳ(_this, ದತ್ತಾಂಶ);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        X11_Dispatch_Focus_ಹೊರಹೋಗು(_this, ದತ್ತಾಂಶ);
                    }
                    ದತ್ತಾಂಶ->pending_focus = PENDING_FOCUS_NONE;
                }
            }
        }
    }
}

ಸ್ಥಿರ Bool isAnyEvent(Display *display, XEvent *ev, XPointer arg)
{
    ಹಿಂತಿರುಗಿ True;
}

ಸ್ಥಿರ bool X11_PollEvent(Display *display, XEvent *event)
{
    ಆದರೆ (!X11_XCheckIfEvent(display, event, isAnyEvent, ಖಾಲಿ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    Display *req_display = ದತ್ತಾಂಶ->request_display;
    ಕಿಟಕಿ_2 xwindow = ಕಿಟಕಿ->ಆಂತರಿಕ->xwindow;
    XClient_ಸಂದೇಶ_Event event;

    SDL_zero(event);
    event.type = Client_ಸಂದೇಶ;
    event.display = req_display;
    event.send_event = True;
    event.ಸಂದೇಶ_type = ದತ್ತಾಂಶ->atoms._SDL_WAKEUP;
    event.format = 8;

    X11_XSendEvent(req_display, xwindow, False, No_Event_ಮುಖವಾಡ, (XEvent *)&event);
    /* XSendEvent returns a status and it could be BadValue or BadWindow. If an
      error happens it is an SDL's internal error and there is nothing we can do here. */
    X11_XFlush(req_display);
}

ಪೂರ್ಣಾಂಕ X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    ಆದರೆ (X11_PollEvent(display, &xevent)) {
        // Fall through
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (timeoutNS == 0) {
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        ಪೂರ್ಣಾಂಕ err = SDL_IOReady(Connection_ಸಂಖ್ಯೆ(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        ಆದರೆ (err > 0) {
            ಆದರೆ (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                ಹಿಂತಿರುಗಿ 1;
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (err == 0) {
            // Timeout
            ಹಿಂತಿರುಗಿ 0;
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Error returned from poll()/select()

            ಆದರೆ (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                ಹಿಂತಿರುಗಿ 1;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಹಿಂತಿರುಗಿ err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    ಹಿಂತಿರುಗಿ 1;
}

ಶೂನ್ಯ X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    XEvent xevent;
    ಪೂರ್ಣಾಂಕ i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        ಆದರೆ (_this->displays[i]->ಆಂತರಿಕ->ಬಹುಲಕ_switch_deadline_ns) {
            ಆದರೆ (_this->displays[i]->fullscreen_ಕಿಟಕಿ) {
                _this->displays[i]->ಆಂತರಿಕ->ಬಹುಲಕ_switch_deadline_ns = 0;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_GetTicksNS() >= _this->displays[i]->ಆಂತರಿಕ->ಬಹುಲಕ_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_ಗಣ_Display_ಬಹುಲಕ_For_Display(_this->displays[i], ಖಾಲಿ);
                _this->displays[i]->ಆಂತರಿಕ->ಬಹುಲಕ_switch_deadline_ns = 0;
            }
        }
    }

    ಆದರೆ (ದತ್ತಾಂಶ->ಕೊನೆಯ_ಬಹುಲಕ_change_deadline) {
        ಆದರೆ (SDL_GetTicks() >= ದತ್ತಾಂಶ->ಕೊನೆಯ_ಬಹುಲಕ_change_deadline) {
            ದತ್ತಾಂಶ->ಕೊನೆಯ_ಬಹುಲಕ_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    ಆದರೆ (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        ಆದರೆ (!ದತ್ತಾಂಶ->screensaver_activity || now >= (ದತ್ತಾಂಶ->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(ದತ್ತಾಂಶ->display);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#ಆದರೆ_ಅಂತ್ಯ

            ದತ್ತಾಂಶ->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    ಆಗ (X11_PollEvent(ದತ್ತಾಂಶ->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    ಗಾಗಿ (i = 0; i < ದತ್ತಾಂಶ->numwindows; ++i) {
        ಆದರೆ (ದತ್ತಾಂಶ->windowlist[i] != ಖಾಲಿ &&
            ದತ್ತಾಂಶ->windowlist[i]->flash_cancel_ಸಮಯ &&
            SDL_GetTicks() >= ದತ್ತಾಂಶ->windowlist[i]->flash_cancel_ಸಮಯ) {
            X11_Flash_ಕಿಟಕಿ(_this, ದತ್ತಾಂಶ->windowlist[i]->ಕಿಟಕಿ, SDL_FLASH_CANCEL);
        }
    }

    ಆದರೆ (ದತ್ತಾಂಶ->xinput_hierarchy_ಬದಲಾಯಿತು) {
        X11_Xinput2UpdateDevices(_this);
        ದತ್ತಾಂಶ->xinput_hierarchy_ಬದಲಾಯಿತು = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ dummy;
    ಪೂರ್ಣಾಂಕ major_ಆವೃತ್ತಿ, minor_ಆವೃತ್ತಿ;
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
    ಆದರೆ (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    ಆದರೆ (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        ಆದರೆ (!X11_XScreenSaverQueryExtension(ದತ್ತಾಂಶ->display, &dummy, &dummy) ||
            !X11_XScreen_Saver_Query_ಆವೃತ್ತಿ(ದತ್ತಾಂಶ->display,
                                          &major_ಆವೃತ್ತಿ, &minor_ಆವೃತ್ತಿ) ||
            major_ಆವೃತ್ತಿ < 1 || (major_ಆವೃತ್ತಿ == 1 && minor_ಆವೃತ್ತಿ < 1)) {
            ಹಿಂತಿರುಗಿ SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(ದತ್ತಾಂಶ->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(ದತ್ತಾಂಶ->display);
        ಹಿಂತಿರುಗಿ true;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
