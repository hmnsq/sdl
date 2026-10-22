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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ <sys/types.h>
#అన్తర్భావ <sys/time.h>
#అన్తర్భావ <signal.h>
#అన్తర్భావ <unistd.h>
#అన్తర్భావ <limits.h> // For INT_MAX

#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11pen.h"
#అన్తర్భావ "SDL_x11touch.h"
#అన్తర్భావ "SDL_x11xinput2.h"
#అన్తర్భావ "SDL_x11xfixes.h"
#అన్తర్భావ "SDL_x11settings.h"
#అన్తర్భావ "../SDL_clipboard_c.h"
#అన్తర్భావ "SDL_x11xsync.h"
#అన్తర్భావ "../../core/unix/SDL_poll.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_touch_c.h"
#అన్తర్భావ "../../core/linux/SDL_system_theme.h"
#అన్తర్భావ "../SDL_sysvideo.h"

#అన్తర్భావ <stdio.h>

#ఒకవేళ 0
#నిర్వచించు DEBUG_XEVENTS
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే NET_WM_MOVERESIZE_కొలత_TOPLEFT
#నిర్వచించు NET_WM_MOVERESIZE_కొలత_TOPLEFT 0
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే NET_WM_MOVERESIZE_కొలత_శిఖరం
#నిర్వచించు NET_WM_MOVERESIZE_కొలత_శిఖరం 1
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే NET_WM_MOVERESIZE_కొలత_TOPRIGHT
#నిర్వచించు NET_WM_MOVERESIZE_కొలత_TOPRIGHT 2
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే NET_WM_MOVERESIZE_కొలత_కుడి
#నిర్వచించు NET_WM_MOVERESIZE_కొలత_కుడి 3
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే NET_WM_MOVERESIZE_కొలత_BOTTOMRIGHT
#నిర్వచించు NET_WM_MOVERESIZE_కొలత_BOTTOMRIGHT 4
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే NET_WM_MOVERESIZE_కొలత_BOTTOM
#నిర్వచించు NET_WM_MOVERESIZE_కొలత_BOTTOM 5
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే NET_WM_MOVERESIZE_కొలత_BOTTOMLEFT
#నిర్వచించు NET_WM_MOVERESIZE_కొలత_BOTTOMLEFT 6
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే NET_WM_MOVERESIZE_కొలత_ఎడమ
#నిర్వచించు NET_WM_MOVERESIZE_కొలత_ఎడమ 7
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే _NET_WM_MOVERESIZE_MOVE
#నిర్వచించు _NET_WM_MOVERESIZE_MOVE 8
#అయితే_ముగింపు

రకనిర్వచనం నిర్మాణం
{
    గుర్తులేని అక్షరం *దత్తాంశం;
    పూర్ణాంకం format, లెక్క;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
స్థిర శూన్య X11_ReadProperty(SDL_x11Prop *p, Display *disp, కిటికీ_2 w, Atom prop)
{
    గుర్తులేని అక్షరం *ret = ఖాళీ;
    Atom type;
    పూర్ణాంకం fmt;
    గుర్తులేని దీర్ఘ లెక్క;
    గుర్తులేని దీర్ఘ బైట్లు_ఎడమ;
    పూర్ణాంకం బైట్లు_fetch = 0;

    చేయి {
        ఒకవేళ (ret) {
            X11_XFree(ret);
        }
        X11_XGet_కిటికీ_Property(disp, w, prop, 0, బైట్లు_fetch, False, AnyPropertyType, &type, &fmt, &లెక్క, &బైట్లు_ఎడమ, &ret);
        బైట్లు_fetch += బైట్లు_ఎడమ;
    } అయితే (బైట్లు_ఎడమ != 0);

    p->దత్తాంశం = ret;
    p->format = fmt;
    p->లెక్క = లెక్క;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
స్థిర Atom X11_Pick_లక్ష్యం(Display *disp, Atom list[], పూర్ణాంకం list_లెక్క)
{
    స్థిరరాశి Atom పాఠ్యం_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    కొరకు (పూర్ణాంకం i = 0; i < list_లెక్క && request != పాఠ్యం_uri_request; i++) {
        అక్షరం *name = X11_XGetAtomName(disp, list[i]);
        // Preferred MIME targets
        ఒకవేళ ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            ఒకవేళ (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        ఒకవేళ ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            ఒకవేళ (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    ఒకవేళ (preferred != None && request != పాఠ్యం_uri_request) {
        request = preferred;
    }
    తిరిగి request;
}

/* Wrapper for X11_PickTarget for a maximum of three targets, a special
   case in the Xdnd protocol */
స్థిర Atom X11_Pick_లక్ష్యం_From_Atoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    పూర్ణాంకం లెక్క = 0;
    Atom atom[3];
    ఒకవేళ (a0 != None) {
        atom[లెక్క++] = a0;
    }
    ఒకవేళ (a1 != None) {
        atom[లెక్క++] = a1;
    }
    ఒకవేళ (a2 != None) {
        atom[లెక్క++] = a2;
    }
    తిరిగి X11_Pick_లక్ష్యం(disp, atom, లెక్క);
}

నిర్మాణం కీలకం_Repeat_Check_దత్తాంశం
{
    XEvent *event;
    bool దొరికింది;
};

స్థిర Bool X11_కీలకం_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    నిర్మాణం కీలకం_Repeat_Check_దత్తాంశం *d = (నిర్మాణం కీలకం_Repeat_Check_దత్తాంశం *)arg;
    ఒకవేళ (chkev->type == కీలకం_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.సమయం - d->event->xkey.సమయం < 2) {
        d->దొరికింది = true;
    }
    తిరిగి False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
స్థిర bool X11_కీలకం_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    నిర్మాణం కీలకం_Repeat_Check_దత్తాంశం d;
    d.event = event;
    d.దొరికింది = false;
    ఒకవేళ (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_కీలకం_Repeat_Check_If_Event, (XPointer)&d);
    }
    తిరిగి d.దొరికింది;
}

bool X11_IsWheelEvent(పూర్ణాంకం button, పూర్ణాంకం *xticks, పూర్ణాంకం *yticks)
{
    /* according to the xlib docs, no specific mouse wheel events exist.
       However, the defacto standard is that the vertical wheel is X buttons
       4 (up) and 5 (down) and a horizontal wheel is 6 (left) and 7 (right). */

    // Xlib defines "Button1" through 5, so we just use literals here.
    ఎంపిక (button) {
    స్థితి 4:
        *yticks = 1;
        తిరిగి true;
    స్థితి 5:
        *yticks = -1;
        తిరిగి true;
    స్థితి 6:
        *xticks = 1;
        తిరిగి true;
    స్థితి 7:
        *xticks = -1;
        తిరిగి true;
    అప్రమేయ:
        ఆపు;
    }
    తిరిగి false;
}

// An X11 event hook
స్థిర SDL_X11EventHook g_X11EventHook = ఖాళీ;
స్థిర శూన్య *g_X11_Event_Hook_దత్తాంశం = ఖాళీ;

శూన్య SDL_సమితి_X11_Event_Hook(SDL_X11EventHook callback, శూన్య *userdata)
{
    g_X11EventHook = callback;
    g_X11_Event_Hook_దత్తాంశం = userdata;
}

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
స్థిర శూన్య X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    ఒకవేళ (X11_XGet_Event_దత్తాంశం(videodata->display, cookie)) {
        ఒకవేళ (!g_X11EventHook || g_X11EventHook(g_X11_Event_Hook_దత్తాంశం, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFree_Event_దత్తాంశం(videodata->display, cookie);
    }
}
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

స్థిర శూన్య X11_Update_System_కీలకం_Modifiers(SDL_Video_దత్తాంశం *viddata)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ఒకవేళ (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        ఒకవేళ (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.పునాది_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } లేకపోతే
#అయితే_ముగింపు
        {
        కిటికీ_2 junk_కిటికీ;
        పూర్ణాంకం x, y;
        గుర్తులేని పూర్ణాంకం mod_ముసుగు;

        X11_XQuery_సూచిక(viddata->display, Default_మూలం_కిటికీ(viddata->display), &junk_కిటికీ, &junk_కిటికీ, &x, &y, &x, &y, &mod_ముసుగు);
        viddata->keyboard.pressed_modifiers = mod_ముసుగు & (జరుపు_ముసుగు_2 | Control_ముసుగు | Mod1_ముసుగు | Mod3_ముసుగు | Mod4_ముసుగు | Mod5_ముసుగు);
        viddata->keyboard.locked_modifiers = mod_ముసుగు & (తాళం_ముసుగు | viddata->keyboard.numlock_ముసుగు | viddata->keyboard.scrolllock_ముసుగు);
    }
}

స్థిర శూన్య X11_ReconcileModifiers(SDL_Video_దత్తాంశం *viddata, bool కీలకం_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    ఒకవేళ (కీలకం_pressed) {
        ఒకవేళ (viddata->keyboard.pressed_modifiers & జరుపు_ముసుగు_2) {
            ఒకవేళ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_జరుపు) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_జరుపు;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_జరుపు);
            }
        }

        ఒకవేళ (viddata->keyboard.pressed_modifiers & Control_ముసుగు) {
            ఒకవేళ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        ఒకవేళ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_ముసుగు) {
            ఒకవేళ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        ఒకవేళ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_ముసుగు) {
            ఒకవేళ (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } లేకపోతే {
        ఒకవేళ (viddata->keyboard.pressed_modifiers & జరుపు_ముసుగు_2) {
            ఒకవేళ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_జరుపు)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_జరుపు;
            }
        } లేకపోతే {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_జరుపు;
        }

        ఒకవేళ (viddata->keyboard.pressed_modifiers & Control_ముసుగు) {
            ఒకవేళ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } లేకపోతే {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        ఒకవేళ (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_ముసుగు) {
            ఒకవేళ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } లేకపోతే {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        ఒకవేళ (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_ముసుగు) {
            ఒకవేళ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } లేకపోతే {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        ఒకవేళ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_ముసుగు) {
            ఒకవేళ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_బహుళకం)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_బహుళకం;
            }
        } లేకపోతే {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_బహుళకం;
        }

        ఒకవేళ (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_ముసుగు) {
            ఒకవేళ (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } లేకపోతే {
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
    ఒకవేళ (viddata->keyboard.locked_modifiers & జరుపు_ముసుగు_2) {
        ఒకవేళ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_జరుపు) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_జరుపు;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_జరుపు);
        } లేకపోతే ఒకవేళ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_జరుపు)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_జరుపు;
        }
    } లేకపోతే {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_జరుపు;
    }

    ఒకవేళ (viddata->keyboard.locked_modifiers & Control_ముసుగు) {
        ఒకవేళ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } లేకపోతే ఒకవేళ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } లేకపోతే {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    ఒకవేళ (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_ముసుగు) {
        ఒకవేళ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } లేకపోతే ఒకవేళ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } లేకపోతే {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    ఒకవేళ (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_ముసుగు) {
        ఒకవేళ (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } లేకపోతే ఒకవేళ (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } లేకపోతే {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    ఒకవేళ (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_ముసుగు) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_బహుళకం;
    } లేకపోతే {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_బహుళకం;
    }

    ఒకవేళ (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_ముసుగు) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } లేకపోతే {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    ఒకవేళ (viddata->keyboard.locked_modifiers & తాళం_ముసుగు) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } లేకపోతే {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    ఒకవేళ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_ముసుగు) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_అంకె;
    } లేకపోతే {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_అంకె;
    }

    ఒకవేళ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_ముసుగు) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } లేకపోతే {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_సమితి_Mod_State(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

స్థిర శూన్య X11_Handle_Modifier_కీలకాలు(SDL_Video_దత్తాంశం *viddata, SDL_Scancode scancode, bool pressed)
{
    స్థిరరాశి SDL_Keycode keycode = SDL_Get_కీలకం_From_Scancode(scancode, SDL_KMOD_NONE, false);
    SDL_Keymod mod = SDL_KMOD_NONE;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is checked.
     */
    ఎంపిక (keycode) {
    స్థితి SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        ఆపు;
    స్థితి SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        ఆపు;
    స్థితి SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        ఆపు;
    స్థితి SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        ఆపు;
    స్థితి SDLK_LALT:
        mod = SDL_KMOD_LALT;
        ఆపు;
    స్థితి SDLK_RALT:
        mod = SDL_KMOD_RALT;
        ఆపు;
    స్థితి SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        ఆపు;
    స్థితి SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        ఆపు;
    స్థితి SDLK_బహుళకం:
        mod = SDL_KMOD_బహుళకం;
        ఆపు;
    స్థితి SDLK_LEVEL5_జరుపు:
        mod = SDL_KMOD_LEVEL5;
        ఆపు;
    స్థితి SDLK_CAPSLOCK:
    స్థితి SDLK_NUMLOCKCLEAR:
    స్థితి SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        ఒకవేళ (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            గుర్తులేని పూర్ణాంకం cur_ముసుగు = viddata->keyboard.locked_modifiers;
            X11_Update_System_కీలకం_Modifiers(viddata);

            ఒకవేళ (viddata->keyboard.locked_modifiers & తాళం_ముసుగు) {
                cur_ముసుగు |= తాళం_ముసుగు;
            } లేకపోతే {
                cur_ముసుగు &= ~తాళం_ముసుగు;
            }
            ఒకవేళ (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_ముసుగు) {
                cur_ముసుగు |= viddata->keyboard.numlock_ముసుగు;
            } లేకపోతే {
                cur_ముసుగు &= ~viddata->keyboard.numlock_ముసుగు;
            }
            ఒకవేళ (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_ముసుగు) {
                cur_ముసుగు |= viddata->keyboard.scrolllock_ముసుగు;
            } లేకపోతే {
                cur_ముసుగు &= ~viddata->keyboard.scrolllock_ముసుగు;
            }

            viddata->keyboard.locked_modifiers = cur_ముసుగు;
        }
    } ఆపు;
    అప్రమేయ:
        తిరిగి;
    }

    ఒకవేళ (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } లేకపోతే {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

శూన్య X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    Display *display = videodata->display;
    అక్షరం కీలకాలు[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_కీలకం_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_అంకె | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= తాళం_ముసుగు | videodata->keyboard.numlock_ముసుగు| videodata->keyboard.scrolllock_ముసుగు;

    X11_XQueryKeymap(display, కీలకాలు);

    స్థిరరాశి bool *keystate = SDL_GetKeyboardState(ఖాళీ);
    కొరకు (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.కీలకం_layout); ++keycode) {
        స్థిరరాశి SDL_Scancode scancode = videodata->keyboard.కీలకం_layout[keycode];
        స్థిరరాశి bool x11_కీలకం_Pressed = (కీలకాలు[keycode / 8] & (1 << (keycode % 8))) != 0;
        స్థిరరాశి bool sdl_కీలకం_Pressed = keystate[scancode];

        ఒకవేళ (x11_కీలకం_Pressed && !sdl_కీలకం_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            ఎంపిక (SDL_Get_కీలకం_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            స్థితి SDLK_LCTRL:
            స్థితి SDLK_RCTRL:
            స్థితి SDLK_LSHIFT:
            స్థితి SDLK_RSHIFT:
            స్థితి SDLK_LALT:
            స్థితి SDLK_RALT:
            స్థితి SDLK_LGUI:
            స్థితి SDLK_RGUI:
            స్థితి SDLK_బహుళకం:
            స్థితి SDLK_LEVEL5_జరుపు:
                X11_Handle_Modifier_కీలకాలు(videodata, scancode, true);
                SDL_Send_Keyboard_కీలకం_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                ఆపు;
            అప్రమేయ:
                ఆపు;
            }
        } లేకపోతే ఒకవేళ (!x11_కీలకం_Pressed && sdl_కీలకం_Pressed) {
            X11_Handle_Modifier_కీలకాలు(videodata, scancode, false);
            SDL_Send_Keyboard_కీలకం_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_కీలకం_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

స్థిర శూన్య X11_Dispatch_Focus_లోపల(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
#నిర్వచితమైతే DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", దత్తాంశం->xwindow);
#అయితే_ముగింపు
    SDL_సమితి_Keyboard_Focus(దత్తాంశం->కిటికీ);
    X11_ReconcileKeyboardState(_this);
#నిర్వచితమైతే X_HAVE_UTF8_STRING
    ఒకవేళ (దత్తాంశం->ic) {
        X11_XSetICFocus(దత్తాంశం->ic);
    }
#అయితే_ముగింపు
    ఒకవేళ (దత్తాంశం->flashing_కిటికీ) {
        X11_Flash_కిటికీ(_this, దత్తాంశం->కిటికీ, SDL_FLASH_CANCEL);
    }
}

స్థిర శూన్య X11_Dispatch_Focus_బహిర్గతం(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
#నిర్వచితమైతే DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", దత్తాంశం->xwindow);
#అయితే_ముగింపు
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    ఒకవేళ (దత్తాంశం->కిటికీ == SDL_GetKeyboardFocus()) {
        SDL_సమితి_Keyboard_Focus(ఖాళీ);
    }
#నిర్వచితమైతే X_HAVE_UTF8_STRING
    ఒకవేళ (దత్తాంశం->ic) {
        X11_XUnsetICFocus(దత్తాంశం->ic);
    }
#అయితే_ముగింపు
}

స్థిర శూన్య X11_DispatchMapNotify(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    SDL_కిటికీ *కిటికీ = దత్తాంశం->కిటికీ;

    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_SHOWN, 0, 0);
    దత్తాంశం->was_shown = true;

    // This may be sent when restoring a minimized window.
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MINIMIZED) {
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESTORED, 0, 0);
        SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_EXPOSED, 0, 0);
    }

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS) {
        SDL_Update_కిటికీ_Grab(కిటికీ);
    }
}

స్థిర శూన్య X11_DispatchUnmapNotify(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    SDL_కిటికీ *కిటికీ = దత్తాంశం->కిటికీ;

    // This may be sent when minimizing a window.
    ఒకవేళ (!కిటికీ->is_hiding) {
        SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_MINIMIZED, 0, 0);
        SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_OCCLUDED, 0, 0);
    } లేకపోతే {
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_HIDDEN, 0, 0);
    }
}

స్థిర శూన్య Dispatch_కిటికీ_Move(SDL_VideoDevice *_this, స్థిరరాశి SDL_కిటికీ_దత్తాంశం *దత్తాంశం, స్థిరరాశి SDL_బిందువు *బిందువు)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    SDL_కిటికీ *కిటికీ = దత్తాంశం->కిటికీ;
    Display *display = videodata->display;
    XEvent evt;

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_సూచిక(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_సందేశం;
    evt.xclient.కిటికీ = దత్తాంశం->xwindow;
    evt.xclient.సందేశం_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.దత్తాంశం.l[0] = (size_t)కిటికీ->x + బిందువు->x;
    evt.xclient.దత్తాంశం.l[1] = (size_t)కిటికీ->y + బిందువు->y;
    evt.xclient.దత్తాంశం.l[2] = _NET_WM_MOVERESIZE_MOVE;
    evt.xclient.దత్తాంశం.l[3] = Button1;
    evt.xclient.దత్తాంశం.l[4] = 0;
    X11_XSendEvent(display, Default_మూలం_కిటికీ(display), False, Substructure_Redirect_ముసుగు | Substructure_Notify_ముసుగు, &evt);

    X11_XSync(display, 0);
}

స్థిర శూన్య కాలపట్టిక_కిటికీ_Move(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *దత్తాంశం, స్థిరరాశి SDL_బిందువు *బిందువు)
{
    దత్తాంశం->pending_move = true;
    దత్తాంశం->pending_move_బిందువు = *బిందువు;
}

స్థిర శూన్య Initiate_కిటికీ_Resize(SDL_VideoDevice *_this, స్థిరరాశి SDL_కిటికీ_దత్తాంశం *దత్తాంశం, స్థిరరాశి SDL_బిందువు *బిందువు, పూర్ణాంకం direction)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    SDL_కిటికీ *కిటికీ = దత్తాంశం->కిటికీ;
    Display *display = videodata->display;
    XEvent evt;

    ఒకవేళ (direction < NET_WM_MOVERESIZE_కొలత_TOPLEFT || direction > NET_WM_MOVERESIZE_కొలత_ఎడమ) {
        తిరిగి;
    }

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_సూచిక(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_సందేశం;
    evt.xclient.కిటికీ = దత్తాంశం->xwindow;
    evt.xclient.సందేశం_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.దత్తాంశం.l[0] = (size_t)కిటికీ->x + బిందువు->x;
    evt.xclient.దత్తాంశం.l[1] = (size_t)కిటికీ->y + బిందువు->y;
    evt.xclient.దత్తాంశం.l[2] = direction;
    evt.xclient.దత్తాంశం.l[3] = Button1;
    evt.xclient.దత్తాంశం.l[4] = 0;
    X11_XSendEvent(display, Default_మూలం_కిటికీ(display), False, Substructure_Redirect_ముసుగు | Substructure_Notify_ముసుగు, &evt);

    X11_XSync(display, 0);
}

bool X11_Process_తగిలింది_Test(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *దత్తాంశం, స్థిరరాశి దశాంశం x, స్థిరరాశి దశాంశం y, bool force_new_ఫలితం)
{
    SDL_కిటికీ *కిటికీ = దత్తాంశం->కిటికీ;
    ఒకవేళ (!కిటికీ->తగిలింది_test) తిరిగి false;
    స్థిరరాశి SDL_బిందువు బిందువు = { (పూర్ణాంకం)x, (పూర్ణాంకం)y };
    SDL_తగిలింది_Test_ఫలితం rc = కిటికీ->తగిలింది_test(కిటికీ, &బిందువు, కిటికీ->తగిలింది_test_దత్తాంశం);
    ఒకవేళ (!force_new_ఫలితం && rc == దత్తాంశం->తగిలింది_test_ఫలితం) {
        తిరిగి true;
    }
    X11_సమితి_తగిలింది_Test_Cursor(rc);
    దత్తాంశం->తగిలింది_test_ఫలితం = rc;
    తిరిగి true;
}

bool X11_Trigger_తగిలింది_Test_Action(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *దత్తాంశం, స్థిరరాశి దశాంశం x, స్థిరరాశి దశాంశం y)
{
    SDL_కిటికీ *కిటికీ = దత్తాంశం->కిటికీ;

    ఒకవేళ (కిటికీ->తగిలింది_test) {
        స్థిరరాశి SDL_బిందువు బిందువు = { (పూర్ణాంకం)x, (పూర్ణాంకం)y };
        స్థిర స్థిరరాశి పూర్ణాంకం directions[] = {
            NET_WM_MOVERESIZE_కొలత_TOPLEFT, NET_WM_MOVERESIZE_కొలత_శిఖరం,
            NET_WM_MOVERESIZE_కొలత_TOPRIGHT, NET_WM_MOVERESIZE_కొలత_కుడి,
            NET_WM_MOVERESIZE_కొలత_BOTTOMRIGHT, NET_WM_MOVERESIZE_కొలత_BOTTOM,
            NET_WM_MOVERESIZE_కొలత_BOTTOMLEFT, NET_WM_MOVERESIZE_కొలత_ఎడమ
        };

        ఎంపిక (దత్తాంశం->తగిలింది_test_ఫలితం) {
        స్థితి SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            ఒకవేళ (దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS) {
                Dispatch_కిటికీ_Move(_this, దత్తాంశం, &బిందువు);
            } లేకపోతే {
                కాలపట్టిక_కిటికీ_Move(_this, దత్తాంశం, &బిందువు);
            }
            తిరిగి true;

        స్థితి SDL_HITTEST_RESIZE_TOPLEFT:
        స్థితి SDL_HITTEST_RESIZE_శిఖరం:
        స్థితి SDL_HITTEST_RESIZE_TOPRIGHT:
        స్థితి SDL_HITTEST_RESIZE_కుడి:
        స్థితి SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        స్థితి SDL_HITTEST_RESIZE_BOTTOM:
        స్థితి SDL_HITTEST_RESIZE_BOTTOMLEFT:
        స్థితి SDL_HITTEST_RESIZE_ఎడమ:
            Initiate_కిటికీ_Resize(_this, దత్తాంశం, &బిందువు, directions[దత్తాంశం->తగిలింది_test_ఫలితం - SDL_HITTEST_RESIZE_TOPLEFT]);
            తిరిగి true;

        అప్రమేయ:
            తిరిగి false;
        }
    }

    తిరిగి false;
}

స్థిర శూన్య X11_Update_User_సమయం(SDL_కిటికీ_దత్తాంశం *దత్తాంశం, స్థిరరాశి గుర్తులేని దీర్ఘ latest)
{
    ఒకవేళ (latest && (latest != దత్తాంశం->user_సమయం)) {
        SDL_Video_దత్తాంశం *videodata = దత్తాంశం->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, దత్తాంశం->xwindow, videodata->atoms.NET_WM_USER_సమయం,
                            XA_CARDINAL, 32, Prop_బహుళకం_Replace,
                            (స్థిరరాశి గుర్తులేని అక్షరం *)&latest, 1);
#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", దత్తాంశం->xwindow, latest);
#అయితే_ముగింపు
        దత్తాంశం->user_సమయం = latest;
    }
}

స్థిర గుర్తులేని అక్షరం x11_చివరి_error;
స్థిర పూర్ణాంకం Bad_కిటికీ_Error_Handler(Display *d, XErrorEvent *e)
{
    x11_చివరి_error = e->error_సంకేతం;

    // Ignore BadWindow in cases where it's not fatal.
    ఒకవేళ (e->error_సంకేతం != Bad_కిటికీ) {
        అక్షరం err_సందేశం[128];
        X11_XGet_Error_పాఠ్యం(d, e->error_సంకేతం, err_సందేశం, పరిమాణం(err_సందేశం));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_సంకేతం, err_సందేశం, e->request_సంకేతం);
    }
    తిరిగి 0;
}

స్థిర శూన్య X11_HandleClipboardEvent(SDL_VideoDevice *_this, స్థిరరాశి XEvent *xevent)
{
    పూర్ణాంకం i;
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_కిటికీ != None);
    SDL_assert(xevent->xany.కిటికీ == videodata->clipboard_కిటికీ);

    ఎంపిక (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    స్థితి SelectionRequest:
    {
        స్థిరరాశి XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        పూర్ణాంకం mime_formats;
        గుర్తులేని అక్షరం *seln_దత్తాంశం;
        size_t seln_నిడివి = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_Clipboard_దత్తాంశం *clipboard;

#నిర్వచితమైతే DEBUG_XEVENTS
        అక్షరం *atom_name;
        atom_name = X11_XGetAtomName(display, req->లక్ష్యం);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->లక్ష్యం, atom_name);
        ఒకవేళ (atom_name) {
            X11_XFree(atom_name);
        }
#అయితే_ముగింపు

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_చివరి_error = 0;
        XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_కిటికీ_Error_Handler);

        ఒకవేళ (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } లేకపోతే {
            clipboard = &videodata->clipboard;
        }

        SDL_zero(sevent);
        sevent.xany.type = SelectionNotify;
        sevent.xselection.selection = req->selection;
        sevent.xselection.లక్ష్యం = None;
        sevent.xselection.property = None; // tell them no by default
        sevent.xselection.requestor = req->requestor;
        sevent.xselection.సమయం = req->సమయం;

        /* !!! FIXME: We were probably storing this on the root window
           because an SDL window might go away...? but we don't have to do
           this now (or ever, really). */

        ఒకవేళ (req->లక్ష్యం == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_లెక్క + 1) * పరిమాణం(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            కొరకు (i = 0; i < clipboard->mime_లెక్క; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, Prop_బహుళకం_Replace,
                                (గుర్తులేని అక్షరం *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.లక్ష్యం = XA_TARGETS;
            SDL_free(supportedFormats);
        } లేకపోతే {
            ఒకవేళ (clipboard->callback) {
                కొరకు (i = 0; i < clipboard->mime_లెక్క; ++i) {
                    స్థిరరాశి అక్షరం *mime_type = clipboard->mime_types[i];
                    ఒకవేళ (X11_XInternAtom(display, mime_type, False) != req->లక్ష్యం) {
                        కొనసాగు;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_దత్తాంశం = (గుర్తులేని అక్షరం *)clipboard->callback(clipboard->userdata, mime_type, &seln_నిడివి);
                    ఒకవేళ (seln_దత్తాంశం) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->లక్ష్యం, 8, Prop_బహుళకం_Replace,
                                            seln_దత్తాంశం, seln_నిడివి);
                        sevent.xselection.property = req->property;
                        sevent.xselection.లక్ష్యం = req->లక్ష్యం;
                    }
                    ఆపు;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(prev_handler);
    } ఆపు;

    స్థితి SelectionNotify:
    {
        స్థిరరాశి XSelectionEvent *xsel = &xevent->xselection;
#నిర్వచితమైతే DEBUG_XEVENTS
        స్థిరరాశి అక్షరం *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        స్థిరరాశి అక్షరం *లక్ష్యం_Name = xsel->లక్ష్యం ? X11_XGetAtomName(display, xsel->లక్ష్యం) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, లక్ష్యం_Name, propName);
#అయితే_ముగింపు
        ఒకవేళ (xsel->లక్ష్యం == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            గుర్తులేని అక్షరం *దత్తాంశం = ఖాళీ;
            పూర్ణాంకం format_property = 0;
            గుర్తులేని దీర్ఘ నిడివి = 0;
            గుర్తులేని దీర్ఘ బైట్లు_ఎడమ = 0;
            పూర్ణాంకం j;

            X11_XGet_కిటికీ_Property(display, Get_కిటికీ(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &నిడివి, &బైట్లు_ఎడమ, &దత్తాంశం);

            పూర్ణాంకం allocationsize = (నిడివి + 1) * పరిమాణం(అక్షరం *);
            కొరకు (j = 0, patom = (Atom *)దత్తాంశం; j < నిడివి; j++, patom++) {
                అక్షరం *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            అక్షరం **new_mime_types = SDL_Allocate_Temporary_జ్ఞాపకం(allocationsize);
            ఒకవేళ (new_mime_types) {
                అక్షరం *strPtr = (అక్షరం *)(new_mime_types + నిడివి + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                కొరకు (j = 0, patom = (Atom *)దత్తాంశం; j < నిడివి; j++, patom++) {
                    అక్షరం *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    స్థిరరాశి size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[నిడివి] = ఖాళీ;

                SDL_SendClipboardUpdate(false, new_mime_types, నిడివి);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            ఒకవేళ (దత్తాంశం) {
                X11_XFree(దత్తాంశం);
            }
        }

        videodata->selection_నిరీక్షణ = false;
    } ఆపు;

    స్థితి SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_Clipboard_దత్తాంశం *clipboard = ఖాళీ;

#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.లక్ష్యం);
#అయితే_ముగింపు

        ఒకవేళ (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } లేకపోతే ఒకవేళ (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        ఒకవేళ (clipboard && clipboard->callback) {
            ఒకవేళ (clipboard->sequence) {
                SDL_Cancel_Clipboard_దత్తాంశం(clipboard->sequence);
            } లేకపోతే {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } ఆపు;

    స్థితి PropertyNotify:
    {
        అక్షరం *name_యొక్క_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        ఒకవేళ (SDL_strncmp(name_యొక్క_atom, "SDL_SELECTION", పరిమాణం("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_విలువ) {
            videodata->selection_incr_నిరీక్షణ = false;
        }

        ఒకవేళ (name_యొక్క_atom) {
            X11_XFree(name_యొక్క_atom);
        }
    } ఆపు;
    }
}

స్థిర Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    తిరిగి ev->type == MapNotify &&
           ev->xmap.కిటికీ == unmap->కిటికీ &&
           ev->xmap.serial == unmap->serial;
}

స్థిర Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    తిరిగి ev->type == ReparentNotify &&
           ev->xreparent.కిటికీ == unmap->కిటికీ &&
           ev->xreparent.serial == unmap->serial;
}

స్థిర bool Is_ఎగువ_Latin1(స్థిరరాశి అక్షరం *string, పూర్ణాంకం నిడివి)
{
    అయితే (నిడివి-- > 0) {
        Uint8 ch = (Uint8)*string;
        ఒకవేళ (ch >= 0x80) {
            తిరిగి true;
        }
        ++string;
    }
    తిరిగి false;
}

స్థిర పూర్ణాంకం XLookupStringAsUTF8(XKeyEvent *event_struct, అక్షరం *బఫరు_return, పూర్ణాంకం బైట్లు_బఫరు, కీలకం_Sym *keysym_return, XCompose_స్థితి *స్థితి_లోపల_బహిర్గతం)
{
    పూర్ణాంకం ఫలితం = X11_XLookupString(event_struct, బఫరు_return, బైట్లు_బఫరు, keysym_return, స్థితి_లోపల_బహిర్గతం);
    ఒకవేళ (Is_ఎగువ_Latin1(బఫరు_return, ఫలితం)) {
        అక్షరం *utf8_పాఠ్యం = SDL_iconv_string("UTF-8", "ISO-8859-1", బఫరు_return, ఫలితం + 1);
        ఒకవేళ (utf8_పాఠ్యం) {
            SDL_strlcpy(బఫరు_return, utf8_పాఠ్యం, బైట్లు_బఫరు);
            SDL_free(utf8_పాఠ్యం);
            తిరిగి SDL_strlen(బఫరు_return);
        } లేకపోతే {
            తిరిగి 0;
        }
    }
    తిరిగి ఫలితం;
}

SDL_కిటికీ_దత్తాంశం *X11_కనుగొను_కిటికీ(SDL_Video_దత్తాంశం *videodata, కిటికీ_2 కిటికీ)
{
    ఒకవేళ (videodata && videodata->windowlist) {
        కొరకు (పూర్ణాంకం i = 0; i < videodata->numwindows; ++i) {
            ఒకవేళ ((videodata->windowlist[i] != ఖాళీ) &&
                (videodata->windowlist[i]->xwindow == కిటికీ)) {
                తిరిగి videodata->windowlist[i];
            }
        }
    }
    తిరిగి ఖాళీ;
}

Uint64 X11_GetEventTimestamp(గుర్తులేని దీర్ఘ సమయం)
{
    // FIXME: Get the event time in the SDL tick time base
    తిరిగి SDL_GetTicksNS();
}

శూన్య X11_Handle_కీలకం_Event(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    Display *display = videodata->display;
    కీలకం_సంకేతం_2 keycode = xevent->xkey.keycode;
    కీలకం_Sym keysym = No_చిహ్నం;
    పూర్ణాంకం పాఠ్యం_నిడివి = 0;
    అక్షరం పాఠ్యం[64];
    స్థితి_3 స్థితి_2 = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == కీలకం_Press);
    SDL_Scancode scancode = videodata->keyboard.కీలకం_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.సమయం);

#నిర్వచితమైతే DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.కిటికీ, (xevent->type == కీలకం_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#అయితే_ముగింపు
#నిర్వచితమైతే DEBUG_SCANCODES
    ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        పూర్ణాంకం min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_కీలకం_సంకేతం_గమ్యం_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysym_గమ్యం_String(keysym));
    }
#అయితే_ముగింపు // DEBUG SCANCODES

    పాఠ్యం[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    ఒకవేళ (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (జరుపు_ముసుగు_2 | Control_ముసుగు | Mod1_ముసుగు | Mod3_ముసుగు | Mod4_ముసుగు | Mod5_ముసుగు);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (తాళం_ముసుగు | videodata->keyboard.numlock_ముసుగు | videodata->keyboard.scrolllock_ముసుగు);
    }

    ఒకవేళ (SDL_పాఠ్యం_ఆదానం_చురుకైన(windowdata->కిటికీ)) {
        // filter events catches XIM events and sends them to the correct handler
        ఒకవేళ (X11_XFilterEvent(xevent, None)) {
#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.కిటికీ);
#అయితే_ముగింపు
            handled_by_ime = true;
        }

        ఒకవేళ (!handled_by_ime) {
#నిర్వచితమైతే X_HAVE_UTF8_STRING
            ఒకవేళ (windowdata->ic && xevent->type == కీలకం_Press) {
                పాఠ్యం_నిడివి = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, పాఠ్యం, పరిమాణం(పాఠ్యం) - 1,
                                      &keysym, &స్థితి_2);
            } లేకపోతే {
                పాఠ్యం_నిడివి = XLookupStringAsUTF8(&xevent->xkey, పాఠ్యం, పరిమాణం(పాఠ్యం) - 1, &keysym, ఖాళీ);
            }
#లేకపోతే
            పాఠ్యం_నిడివి = XLookupStringAsUTF8(&xevent->xkey, పాఠ్యం, పరిమాణం(పాఠ్యం) - 1, &keysym, ఖాళీ);
#అయితే_ముగింపు
        }
    }

    ఒకవేళ (!handled_by_ime) {
        ఒకవేళ (pressed) {
            X11_Handle_Modifier_కీలకాలు(videodata, scancode, true);
            SDL_Send_Keyboard_కీలకం_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            ఒకవేళ (*పాఠ్యం && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                పాఠ్యం[పాఠ్యం_నిడివి] = '\0';
                X11_ClearComposition(windowdata);
                SDL_Send_Keyboard_పాఠ్యం(పాఠ్యం);
            }
        } లేకపోతే {
            ఒకవేళ (X11_కీలకం_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                తిరిగి;
            }

            X11_Handle_Modifier_కీలకాలు(videodata, scancode, false);
            SDL_Send_Keyboard_కీలకం_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    ఒకవేళ (pressed) {
        X11_Update_User_సమయం(windowdata, xevent->xkey.సమయం);
    }
}

శూన్య X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *windowdata, SDL_MouseID mouseID, పూర్ణాంకం button, దశాంశం x, దశాంశం y, గుర్తులేని దీర్ఘ సమయం, గుర్తులేని దీర్ఘ serial)
{
    SDL_కిటికీ *కిటికీ = windowdata->కిటికీ;
    పూర్ణాంకం xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(సమయం);

#నిర్వచితమైతే DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#అయితే_ముగింపు

    SDL_Mouse *mouse = SDL_GetMouse();
    ఒకవేళ (!mouse->relative_బహుళకం && (x != mouse->x || y != mouse->y)) {
        X11_Process_తగిలింది_Test(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, కిటికీ, mouseID, false, x, y);
    }

    ఒకవేళ (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, కిటికీ, mouseID, (దశాంశం)-xticks, (దశాంశం)yticks, SDL_MOUSEWHEEL_సాధారణ);
    } లేకపోతే {
        ఒకవేళ (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        ఒకవేళ (button == Button1) {
            ఒకవేళ (X11_Trigger_తగిలింది_Test_Action(_this, windowdata, x, y)) {
                SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_తగిలింది_TEST, 0, 0);
                తిరిగి; // don't pass this event on to app.
            }
        }
        ఒకవేళ (windowdata->చివరి_focus_event_సమయం) {
            స్థిరరాశి పూర్ణాంకం X11_FOCUS_CLICK_TIMEOUT = 10;
            ఒకవేళ (SDL_GetTicks() < (windowdata->చివరి_focus_event_సమయం + X11_FOCUS_CLICK_TIMEOUT)) {
                ఒకవేళ (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->చివరి_focus_event_సమయం = 0;
        }
        ఒకవేళ (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, కిటికీ, mouseID, button, true);
        }
    }
    X11_Update_User_సమయం(windowdata, సమయం);
}

శూన్య X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *windowdata, SDL_MouseID mouseID, పూర్ణాంకం button, గుర్తులేని దీర్ఘ సమయం)
{
    SDL_కిటికీ *కిటికీ = windowdata->కిటికీ;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    పూర్ణాంకం xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(సమయం);

#నిర్వచితమైతే DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#అయితే_ముగింపు
    ఒకవేళ (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        ఒకవేళ (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, కిటికీ, mouseID, button, false);

        ఒకవేళ (కిటికీ->అంతర్గత->pending_grab) {
            X11_సమితి_కిటికీ_Mouse_Grab(_this, కిటికీ, true);
        }
    }
}

శూన్య X11_Get_Border_విలువలు(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    SDL_Video_దత్తాంశం *videodata = దత్తాంశం->videodata;
    Display *display = videodata->display;

    Atom type;
    పూర్ణాంకం format;
    గుర్తులేని దీర్ఘ nitems, బైట్లు_after;
    గుర్తులేని అక్షరం *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    ఒకవేళ (!(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_BORDERLESS)) {
        ఒకవేళ (X11_XGet_కిటికీ_Property(display, దత్తాంశం->xwindow, videodata->atoms.NET_చట్రం_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &బైట్లు_after, &property) == Success) {
            ఒకవేళ (type != None && nitems == 4) {
                దత్తాంశం->border_ఎడమ = (పూర్ణాంకం)((దీర్ఘ *)property)[0];
                దత్తాంశం->border_కుడి = (పూర్ణాంకం)((దీర్ఘ *)property)[1];
                దత్తాంశం->border_శిఖరం = (పూర్ణాంకం)((దీర్ఘ *)property)[2];
                దత్తాంశం->border_bottom = (పూర్ణాంకం)((దీర్ఘ *)property)[3];
            }
            X11_XFree(property);

#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", దత్తాంశం->border_ఎడమ, దత్తాంశం->border_కుడి, దత్తాంశం->border_శిఖరం, దత్తాంశం->border_bottom);
#అయితే_ముగింపు
        }
    } లేకపోతే {
        దత్తాంశం->border_ఎడమ = దత్తాంశం->border_శిఖరం = దత్తాంశం->border_కుడి = దత్తాంశం->border_bottom = 0;
    }
}

శూన్య X11_EmitConfigureNotifyEvents(SDL_కిటికీ_దత్తాంశం *దత్తాంశం, XConfigureEvent *xevent)
{
    ఒకవేళ (!దత్తాంశం->కొలత_move_event_flags) {
        పూర్ణాంకం x = xevent->x;
        పూర్ణాంకం y = xevent->y;

        ఒకవేళ (xevent->x != దత్తాంశం->చివరి_xconfigure.x ||
            xevent->y != దత్తాంశం->చివరి_xconfigure.y) {
            దత్తాంశం->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_Global_గమ్యం_Relative_For_కిటికీ(దత్తాంశం->కిటికీ, x, y, &x, &y);
        SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_MOVED, x, y);

        కొరకు (SDL_కిటికీ *w = దత్తాంశం->కిటికీ->మొదటి_బిడ్డ; w; w = w->తదుపరి_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            ఒకవేళ (SDL_కిటికీ_IS_POPUP(w) && !(w->flags & SDL_కిటికీ_HIDDEN)) {
                X11_Update_కిటికీ_Position(w, true);
            }
        }

        ఒకవేళ (xevent->వెడల్పు != దత్తాంశం->చివరి_xconfigure.వెడల్పు ||
            xevent->ఎత్తు != దత్తాంశం->చివరి_xconfigure.ఎత్తు) {
            దత్తాంశం->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_RESIZED, xevent->వెడల్పు, xevent->ఎత్తు);
    }

    SDL_copyp(&దత్తాంశం->చివరి_xconfigure, xevent);
}

స్థిర శూన్య X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    Display *display;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;
    XClient_సందేశం_Event m;
    పూర్ణాంకం i;

    SDL_assert(videodata != ఖాళీ);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    ఒకవేళ (xevent->type != కీలకం_Press && xevent->type != కీలకం_Release) {
        ఒకవేళ (X11_XFilterEvent(xevent, None)) {
#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.కిటికీ);
#అయితే_ముగింపు
            తిరిగి;
        }
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    ఒకవేళ (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        తిరిగి;
    }
#అయితే_ముగింపు

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    ఒకవేళ (g_X11EventHook) {
        ఒకవేళ (!g_X11EventHook(g_X11_Event_Hook_దత్తాంశం, xevent)) {
            తిరిగి;
        }
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
    ఒకవేళ (videodata->xrandr_event_పునాది && (xevent->type == (videodata->xrandr_event_పునాది + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#అయితే_ముగింపు

#నిర్వచితమైతే DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.కిటికీ);
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
    ఒకవేళ (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#అయితే_ముగింపు

        ఒకవేళ (ev->subtype == XFixes_సమితి_Selection_Owner_Notify)
        {
            ఒకవేళ (ev->selection != videodata->atoms.CLIPBOARD)
                తిరిగి;

            ఒకవేళ (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_కిటికీ)
                తిరిగి;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, Get_కిటికీ(_this), Current_సమయం);
        }

        తిరిగి;
    }
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XFIXES

    ఒకవేళ ((videodata->clipboard_కిటికీ != None) &&
        (videodata->clipboard_కిటికీ == xevent->xany.కిటికీ)) {
        X11_HandleClipboardEvent(_this, xevent);
        తిరిగి;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    దత్తాంశం = X11_కనుగొను_కిటికీ(videodata, xevent->xany.కిటికీ);

    ఒకవేళ (!దత్తాంశం) {
        // The window for KeymapNotify, etc events is 0
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        ఒకవేళ (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            ఎంపిక (xkbevent->any.xkb_type) {
            స్థితి XkbStateNotify:
            {
#నిర్వచితమైతే DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.కిటికీ);
#అయితే_ముగింపు
                ఒకవేళ ((xkbevent->state.మారింది & Xkb_సమూహం_State_ముసుగు) && xkbevent->state.సమూహం != videodata->keyboard.xkb.current_సమూహం) {
                    videodata->keyboard.xkb.current_సమూహం = xkbevent->state.సమూహం;
                    SDL_సమితి_Keymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_సమూహం], true);
                }

                ఒకవేళ (xkbevent->state.మారింది & Xkb_Modifier_State_ముసుగు) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.పునాది_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } ఆపు;

            స్థితి XkbMapNotify:
#నిర్వచితమైతే DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.కిటికీ);
                SDL_FALLTHROUGH;
#అయితే_ముగింపు
            స్థితి XkbNewKeyboardNotify:
            {
#నిర్వచితమైతే DEBUG_XEVENTS
                ఒకవేళ (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.కిటికీ);
                }
#అయితే_ముగింపు
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                ఒకవేళ (xkbevent->any.serial != videodata->keyboard.xkb.చివరి_map_serial) {
                    videodata->keyboard.xkb.చివరి_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } ఆపు;

            అప్రమేయ:
                ఆపు;
            }
        } లేకపోతే
#అయితే_ముగింపు
        ఒకవేళ (xevent->type == KeymapNotify) {
#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.కిటికీ);
#అయితే_ముగింపు
            ఒకవేళ (SDL_GetKeyboardFocus() != ఖాళీ) {
                ఒకవేళ (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } లేకపోతే ఒకవేళ (xevent->type == MappingNotify) {
            స్థిరరాశి పూర్ణాంకం request = xevent->xmapping.request;

            ఒకవేళ (request == Mapping_సూచిక) {
#నిర్వచితమైతే DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.కిటికీ);
#అయితే_ముగింపు
                X11_Xinput2_Update_సూచిక_Mapping(_this);
            } లేకపోతే ఒకవేళ (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#నిర్వచితమైతే DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.కిటికీ);
#అయితే_ముగింపు
                ఒకవేళ (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } లేకపోతే ఒకవేళ (xevent->type == PropertyNotify && videodata) {
            అక్షరం *name_యొక్క_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            ఒకవేళ (name_యొక్క_atom) {
                ఒకవేళ (SDL_startswith(name_యొక్క_atom, "_ICC_PROFILE")) {
                    XWindow_లక్షణాలు attrib;
                    పూర్ణాంకం screennum;
                    కొరకు (i = 0; i < videodata->numwindows; ++i) {
                        ఒకవేళ (videodata->windowlist[i] != ఖాళీ) {
                            దత్తాంశం = videodata->windowlist[i];
                            X11_XGet_కిటికీ_లక్షణాలు(display, దత్తాంశం->xwindow, &attrib);
                            screennum = X11_XScreen_సంఖ్య_యొక్క_Screen(attrib.screen);
                            ఒకవేళ (screennum == 0 && SDL_strcmp(name_యొక్క_atom, "_ICC_PROFILE") == 0) {
                                SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_ICCPROF_మారింది, 0, 0);
                            } లేకపోతే ఒకవేళ (SDL_strncmp(name_యొక్క_atom, "_ICC_PROFILE_", పరిమాణం("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_యొక్క_atom) > పరిమాణం("_ICC_PROFILE_") - 1) {
                                పూర్ణాంకం iccscreennum = SDL_atoi(&name_యొక్క_atom[పరిమాణం("_ICC_PROFILE_") - 1]);

                                ఒకవేళ (screennum == iccscreennum) {
                                    SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_ICCPROF_మారింది, 0, 0);
                                }
                            }
                        }
                    }
                } లేకపోతే ఒకవేళ (SDL_strcmp(name_యొక్క_atom, "_NET_WORKAREA") == 0) {
                    కొరకు (i = 0; i < _this->అంకె_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_మారింది, 0, 0);
                    }
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
                } లేకపోతే ఒకవేళ (SDL_strcmp(name_యొక్క_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_యొక్క_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#అయితే_ముగింపు
                }
                X11_XFree(name_యొక్క_atom);
            }
        }
        తిరిగి;
    }

    ఎంపిక (xevent->type) {

        // Gaining mouse coverage?
    స్థితి EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.కిటికీ,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.బహుళకం);
        ఒకవేళ (xevent->xcrossing.బహుళకం == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        ఒకవేళ (xevent->xcrossing.బహుళకం == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#అయితే_ముగింపు
        SDL_సమితి_Mouse_Focus(దత్తాంశం->కిటికీ);

        mouse->చివరి_x = xevent->xcrossing.x;
        mouse->చివరి_y = xevent->xcrossing.y;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
        {
            // Only create the barriers if we have input focus
            SDL_కిటికీ_దత్తాంశం *windowdata = దత్తాంశం->కిటికీ->అంతర్గత;
            ఒకవేళ ((దత్తాంశం->సూచిక_barrier_చురుకైన == true) && windowdata->కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->కిటికీ, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#అయితే_ముగింపు

        ఒకవేళ (!mouse->relative_బహుళకం) {
            SDL_SendMouseMotion(0, దత్తాంశం->కిటికీ, SDL_GLOBAL_MOUSE_ID, false, (దశాంశం)xevent->xcrossing.x, (దశాంశం)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        ఒకవేళ (!(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_MOUSE_CAPTURE)) {
            SDL_Update_కిటికీ_Grab(దత్తాంశం->కిటికీ);
        }

        X11_Process_తగిలింది_Test(_this, దత్తాంశం, mouse->చివరి_x, mouse->చివరి_y, true);
    } ఆపు;
        // Losing mouse coverage?
    స్థితి LeaveNotify:
    {
#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.కిటికీ,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.బహుళకం);
        ఒకవేళ (xevent->xcrossing.బహుళకం == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        ఒకవేళ (xevent->xcrossing.బహుళకం == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#అయితే_ముగింపు
        ఒకవేళ (!SDL_GetMouse()->relative_బహుళకం) {
            SDL_SendMouseMotion(0, దత్తాంశం->కిటికీ, SDL_GLOBAL_MOUSE_ID, false, (దశాంశం)xevent->xcrossing.x, (దశాంశం)xevent->xcrossing.y);
        }

        ఒకవేళ (xevent->xcrossing.బహుళకం != NotifyGrab &&
            xevent->xcrossing.బహుళకం != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            ఒకవేళ (!(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
                X11_సమితి_కిటికీ_Keyboard_Grab(_this, దత్తాంశం->కిటికీ, false);
            }

            SDL_సమితి_Mouse_Focus(ఖాళీ);
        }
    } ఆపు;

        // Gaining input focus?
    స్థితి Focus_లోపల:
    {
        ఒకవేళ (xevent->xfocus.బహుళకం == NotifyGrab || xevent->xfocus.బహుళకం == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.కిటికీ);
#అయితే_ముగింపు
            ఆపు;
        }

        ఒకవేళ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_సూచిక) {
#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.కిటికీ);
#అయితే_ముగింపు
            ఆపు;
        }
#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.కిటికీ);
#అయితే_ముగింపు
        ఒకవేళ (!videodata->చివరి_బహుళకం_change_deadline) /* no recent mode changes */ {
            దత్తాంశం->pending_focus = PENDING_FOCUS_NONE;
            దత్తాంశం->pending_focus_సమయం = 0;
            X11_Dispatch_Focus_లోపల(_this, దత్తాంశం);
        } లేకపోతే {
            దత్తాంశం->pending_focus = PENDING_FOCUS_లోపల;
            దత్తాంశం->pending_focus_సమయం = SDL_GetTicks() + PENDING_FOCUS_సమయం;
        }
        దత్తాంశం->చివరి_focus_event_సమయం = SDL_GetTicks();
    } ఆపు;

        // Losing input focus?
    స్థితి Focus_బహిర్గతం:
    {
        ఒకవేళ (xevent->xfocus.బహుళకం == NotifyGrab || xevent->xfocus.బహుళకం == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.కిటికీ);
#అయితే_ముగింపు
            ఆపు;
        }
        ఒకవేళ (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_సూచిక) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.కిటికీ);
#అయితే_ముగింపు
            ఆపు;
        }
#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.కిటికీ);
#అయితే_ముగింపు
        ఒకవేళ (!videodata->చివరి_బహుళకం_change_deadline) /* no recent mode changes */ {
            దత్తాంశం->pending_focus = PENDING_FOCUS_NONE;
            దత్తాంశం->pending_focus_సమయం = 0;
            X11_Dispatch_Focus_బహిర్గతం(_this, దత్తాంశం);
        } లేకపోతే {
            దత్తాంశం->pending_focus = PENDING_FOCUS_బహిర్గతం;
            దత్తాంశం->pending_focus_సమయం = SDL_GetTicks() + PENDING_FOCUS_సమయం;
        }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        ఒకవేళ (దత్తాంశం->సూచిక_barrier_చురుకైన == true) {
            X11_ConfineCursorWithFlags(_this, దత్తాంశం->కిటికీ, ఖాళీ, X11_BARRIER_HANDLED_BY_EVENT);
        }
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XFIXES
    } ఆపు;


        // Have we been iconified?
    స్థితి UnmapNotify:
    {
        XEvent ev;

#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.కిటికీ);
#అయితే_ముగింపు

        ఒకవేళ (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } లేకపోతే {
            X11_DispatchUnmapNotify(దత్తాంశం);
        }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        ఒకవేళ (దత్తాంశం->సూచిక_barrier_చురుకైన == true) {
            X11_ConfineCursorWithFlags(_this, దత్తాంశం->కిటికీ, ఖాళీ, X11_BARRIER_HANDLED_BY_EVENT);
        }
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XFIXES
    } ఆపు;

        // Have we been restored?
    స్థితి MapNotify:
    {
#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.కిటికీ);
#అయితే_ముగింపు
        X11_DispatchMapNotify(దత్తాంశం);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        ఒకవేళ (దత్తాంశం->సూచిక_barrier_చురుకైన == true) {
            X11_ConfineCursorWithFlags(_this, దత్తాంశం->కిటికీ, &దత్తాంశం->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XFIXES
    } ఆపు;

        // Have we been resized or moved?
    స్థితి ConfigureNotify:
    {
#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.కిటికీ,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.వెడల్పు, xevent->xconfigure.ఎత్తు);
#అయితే_ముగింపు
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        ఒకవేళ (!xevent->xconfigure.send_event) {
            గుర్తులేని పూర్ణాంకం అంకె_Children;
            కిటికీ_2 బిడ్డ_Return, మూలం_2, మాతృ_2;
            కిటికీ_2 *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_చివరి_error = 0;
            XErrorHandler prev_handler = X11_XSetErrorHandler(Bad_కిటికీ_Error_Handler);

            X11_XQuery_వృక్షం(దత్తాంశం->videodata->display, xevent->xconfigure.కిటికీ, &మూలం_2, &మాతృ_2, &Children, &అంకె_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      మాతృ_2, Default_మూలం_కిటికీ(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &బిడ్డ_Return);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(prev_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            ఒకవేళ (x11_చివరి_error == Bad_కిటికీ) {
                ఆపు;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        స్థిరరాశి SDL_కిటికీ_Flags మారింది = X11_GetNetWMState(_this, దత్తాంశం->కిటికీ, xevent->xproperty.కిటికీ) ^ దత్తాంశం->కిటికీ->flags;
        ఒకవేళ (మారింది & (SDL_కిటికీ_FULLSCREEN | SDL_కిటికీ_MAXIMIZED)) {
            SDL_copyp(&దత్తాంశం->pending_xconfigure, &xevent->xconfigure);
            దత్తాంశం->emit_కొలత_move_after_property_notify = true;
        }

        ఒకవేళ (!దత్తాంశం->emit_కొలత_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(దత్తాంశం, &xevent->xconfigure);
        }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(దత్తాంశం->కిటికీ, &xevent->xconfigure);
#అయితే_ముగింపు /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } ఆపు;

        // Have we been requested to quit (or another client message?)
    స్థితి Client_సందేశం:
    {
        స్థిర పూర్ణాంకం xdnd_సంస్కరణ = 0;

        ఒకవేళ (xevent->xclient.సందేశం_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.దత్తాంశం.l[1] & 1;
            దత్తాంశం->xdnd_ఆధారం = xevent->xclient.దత్తాంశం.l[0];
            xdnd_సంస్కరణ = (xevent->xclient.దత్తాంశం.l[1] >> 24);
#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", దత్తాంశం->xdnd_ఆధారం);
            SDL_Log("Protocol version to use : %d", xdnd_సంస్కరణ);
            SDL_Log("More then 3 data types : %d", (పూర్ణాంకం)use_list);
#అయితే_ముగింపు

            ఒకవేళ (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, దత్తాంశం->xdnd_ఆధారం, videodata->atoms.XdndTypeList);
                // pick one
                దత్తాంశం->xdnd_req = X11_Pick_లక్ష్యం(display, (Atom *)p.దత్తాంశం, p.లెక్క);
                X11_XFree(p.దత్తాంశం);
            } లేకపోతే {
                // pick from list of three
                దత్తాంశం->xdnd_req = X11_Pick_లక్ష్యం_From_Atoms(display, xevent->xclient.దత్తాంశం.l[2], xevent->xclient.దత్తాంశం.l[3], xevent->xclient.దత్తాంశం.l[4]);
            }
        } లేకపోతే ఒకవేళ (xevent->xclient.సందేశం_type == videodata->atoms.XdndLeave) {
#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.దత్తాంశం.l[0]);
#అయితే_ముగింపు
            SDL_SendDropComplete(దత్తాంశం->కిటికీ);
        } లేకపోతే ఒకవేళ (xevent->xclient.సందేశం_type == videodata->atoms.XdndPosition) {

#నిర్వచితమైతే DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            ఒకవేళ (xdnd_సంస్కరణ >= 2) {
                act = xevent->xclient.దత్తాంశం.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#అయితే_ముగింపు
            {
                // Drag and Drop position
                పూర్ణాంకం మూలం_x, మూలం_y, కిటికీ_x, కిటికీ_y;
                కిటికీ_2 బిడ్డ_Return;
                మూలం_x = xevent->xclient.దత్తాంశం.l[2] >> 16;
                మూలం_y = xevent->xclient.దత్తాంశం.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_మూలం_కిటికీ(display), దత్తాంశం->xwindow,
                                          మూలం_x, మూలం_y, &కిటికీ_x, &కిటికీ_y, &బిడ్డ_Return);

                SDL_SendDropPosition(దత్తాంశం->కిటికీ, (దశాంశం)కిటికీ_x, (దశాంశం)కిటికీ_y);
            }

            // reply with status
            SDL_zero(m);
            m.type = Client_సందేశం;
            m.display = xevent->xclient.display;
            m.కిటికీ = xevent->xclient.దత్తాంశం.l[0];
            m.సందేశం_type = videodata->atoms.Xdnd_స్థితి;
            m.format = 32;
            m.దత్తాంశం.l[0] = దత్తాంశం->xwindow;
            m.దత్తాంశం.l[1] = (దత్తాంశం->xdnd_req != None);
            m.దత్తాంశం.l[2] = 0; // specify an empty rectangle
            m.దత్తాంశం.l[3] = 0;
            m.దత్తాంశం.l[4] = videodata->atoms.XdndActionCopy; // we only accept copying anyway

            X11_XSendEvent(display, xevent->xclient.దత్తాంశం.l[0], False, No_Event_ముసుగు, (XEvent *)&m);
            X11_XFlush(display);
        } లేకపోతే ఒకవేళ (xevent->xclient.సందేశం_type == videodata->atoms.XdndDrop) {
            ఒకవేళ (దత్తాంశం->xdnd_req == None) {
                // say again - not interested!
                SDL_zero(m);
                m.type = Client_సందేశం;
                m.display = xevent->xclient.display;
                m.కిటికీ = xevent->xclient.దత్తాంశం.l[0];
                m.సందేశం_type = videodata->atoms.Xdnd_ముగిసిన;
                m.format = 32;
                m.దత్తాంశం.l[0] = దత్తాంశం->xwindow;
                m.దత్తాంశం.l[1] = 0;
                m.దత్తాంశం.l[2] = None; // fail!
                X11_XSendEvent(display, xevent->xclient.దత్తాంశం.l[0], False, No_Event_ముసుగు, (XEvent *)&m);
            } లేకపోతే {
                // convert
                ఒకవేళ (xdnd_సంస్కరణ >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, దత్తాంశం->xdnd_req, videodata->atoms.PRIMARY, దత్తాంశం->xwindow, xevent->xclient.దత్తాంశం.l[2]);
                } లేకపోతే {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, దత్తాంశం->xdnd_req, videodata->atoms.PRIMARY, దత్తాంశం->xwindow, Current_సమయం);
                }
            }
        } లేకపోతే ఒకవేళ ((xevent->xclient.సందేశం_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.దత్తాంశం.l[0] == videodata->atoms._NET_WM_PING)) {
            కిటికీ_2 మూలం = Default_మూలం_కిటికీ(display);

#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.కిటికీ);
#అయితే_ముగింపు
            xevent->xclient.కిటికీ = మూలం;
            X11_XSendEvent(display, మూలం, False, Substructure_Redirect_ముసుగు | Substructure_Notify_ముసుగు, xevent);
            ఆపు;
        }

        లేకపోతే ఒకవేళ ((xevent->xclient.సందేశం_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.దత్తాంశం.l[0] == videodata->atoms.WM_DELETE_కిటికీ)) {

#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.కిటికీ);
#అయితే_ముగింపు
            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_CLOSE_REQUESTED, 0, 0);
            ఆపు;
        } లేకపోతే ఒకవేళ ((xevent->xclient.సందేశం_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.దత్తాంశం.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#నిర్వచితమైతే DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", దత్తాంశం);
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(దత్తాంశం->కిటికీ, &xevent->xclient);
#అయితే_ముగింపు /* SDL_VIDEO_DRIVER_X11_XSYNC */
            ఆపు;
        }
    } ఆపు;

        // Do we need to refresh ourselves?
    స్థితి Expose:
    {
#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.కిటికీ, xevent->xexpose.లెక్క);
#అయితే_ముగింపు
        SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_EXPOSED, 0, 0);
    } ఆపు;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    స్థితి కీలకం_Press:
    స్థితి కీలకం_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        ఒకవేళ (దత్తాంశం->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            ఆపు;
        } లేకపోతే ఒకవేళ (xevent->xkey.serial == videodata->xinput_చివరి_కీలకం_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_చివరి_keyboard_device;
        }

        X11_Handle_కీలకం_Event(_this, దత్తాంశం, keyboardID, xevent);
    } ఆపు;

    స్థితి MotionNotify:
    {
        ఒకవేళ (X11_Xinput2_Handles_Motion_For_కిటికీ(దత్తాంశం)) {
            // This input is being handled by XInput2
            ఆపు;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        ఒకవేళ (!mouse->relative_బహుళకం) {
#నిర్వచితమైతే DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.కిటికీ, xevent->xmotion.x, xevent->xmotion.y);
#అయితే_ముగింపు

            X11_Process_తగిలింది_Test(_this, దత్తాంశం, (దశాంశం)xevent->xmotion.x, (దశాంశం)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, దత్తాంశం->కిటికీ, SDL_GLOBAL_MOUSE_ID, false, (దశాంశం)xevent->xmotion.x, (దశాంశం)xevent->xmotion.y);
        }
    } ఆపు;

    స్థితి ButtonPress:
    {
        ఒకవేళ (దత్తాంశం->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_చివరి_button_serial) {
            // This input event was handled by XInput2.
            ఆపు;
        }

        X11_HandleButtonPress(_this, దత్తాంశం, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.సమయం, xevent->xbutton.serial);
    } ఆపు;

    స్థితి ButtonRelease:
    {
        ఒకవేళ (దత్తాంశం->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_చివరి_button_serial) {
            // This input event was handled by XInput2.
            ఆపు;
        }

        X11_HandleButtonRelease(_this, దత్తాంశం, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.సమయం);
    } ఆపు;

    స్థితి PropertyNotify:
    {
#నిర్వచితమైతే DEBUG_XEVENTS
        గుర్తులేని అక్షరం *propdata;
        పూర్ణాంకం స్థితి_2, real_format;
        Atom real_type;
        గుర్తులేని దీర్ఘ వస్తువులు_read, వస్తువులు_ఎడమ;

        అక్షరం *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        ఒకవేళ (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.కిటికీ, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.సమయం);
            X11_XFree(name);
        }

        స్థితి_2 = X11_XGet_కిటికీ_Property(display, దత్తాంశం->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &వస్తువులు_read, &వస్తువులు_ఎడమ, &propdata);
        ఒకవేళ (స్థితి_2 == Success && వస్తువులు_read > 0) {
            ఒకవేళ (real_type == XA_INTEGER) {
                పూర్ణాంకం *విలువలు = (పూర్ణాంకం *)propdata;

                SDL_Log("{");
                కొరకు (i = 0; i < వస్తువులు_read; i++) {
                    SDL_Log(" %d", విలువలు[i]);
                }
                SDL_Log(" }");
            } లేకపోతే ఒకవేళ (real_type == XA_CARDINAL) {
                ఒకవేళ (real_format == 32) {
                    Uint32 *విలువలు = (Uint32 *)propdata;

                    SDL_Log("{");
                    కొరకు (i = 0; i < వస్తువులు_read; i++) {
                        SDL_Log(" %d", విలువలు[i]);
                    }
                    SDL_Log(" }");
                } లేకపోతే ఒకవేళ (real_format == 16) {
                    Uint16 *విలువలు = (Uint16 *)propdata;

                    SDL_Log("{");
                    కొరకు (i = 0; i < వస్తువులు_read; i++) {
                        SDL_Log(" %d", విలువలు[i]);
                    }
                    SDL_Log(" }");
                } లేకపోతే ఒకవేళ (real_format == 8) {
                    Uint8 *విలువలు = (Uint8 *)propdata;

                    SDL_Log("{");
                    కొరకు (i = 0; i < వస్తువులు_read; i++) {
                        SDL_Log(" %d", విలువలు[i]);
                    }
                    SDL_Log(" }");
                }
            } లేకపోతే ఒకవేళ (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } లేకపోతే ఒకవేళ (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                కొరకు (i = 0; i < వస్తువులు_read; i++) {
                    అక్షరం *atomname = X11_XGetAtomName(display, atoms[i]);
                    ఒకవేళ (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } లేకపోతే {
                అక్షరం *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                ఒకవేళ (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        ఒకవేళ (స్థితి_2 == Success) {
            X11_XFree(propdata);
        }
#అయితే_ముగింపు // DEBUG_XEVENTS

        /* Take advantage of this moment to make sure user_time has a
            valid timestamp from the X server, so if we later try to
            raise/restore this window, _NET_ACTIVE_WINDOW can have a
            non-zero timestamp, even if there's never been a mouse or
            key press to this window so far. Note that we don't try to
            set _NET_WM_USER_TIME here, though. That's only for legit
            user interaction with the window. */
        ఒకవేళ (!దత్తాంశం->user_సమయం) {
            దత్తాంశం->user_సమయం = xevent->xproperty.సమయం;
        }

        ఒకవేళ (xevent->xproperty.atom == దత్తాంశం->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            స్థిరరాశి SDL_కిటికీ_Flags flags = X11_GetNetWMState(_this, దత్తాంశం->కిటికీ, xevent->xproperty.కిటికీ);
            స్థిరరాశి SDL_కిటికీ_Flags మారింది = flags ^ దత్తాంశం->కిటికీ->flags;

            ఒకవేళ ((మారింది & SDL_కిటికీ_HIDDEN) && !(flags & SDL_కిటికీ_HIDDEN)) {
                X11_DispatchMapNotify(దత్తాంశం);
            }

            ఒకవేళ (!SDL_కిటికీ_IS_POPUP(దత్తాంశం->కిటికీ)) {
                ఒకవేళ (మారింది & SDL_కిటికీ_FULLSCREEN) {
                    దత్తాంశం->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    ఒకవేళ (flags & SDL_కిటికీ_FULLSCREEN) {
                        ఒకవేళ (!(flags & SDL_కిటికీ_MINIMIZED)) {
                            స్థిరరాశి bool commit = SDL_memcmp(&దత్తాంశం->కిటికీ->current_fullscreen_బహుళకం, &దత్తాంశం->requested_fullscreen_బహుళకం, పరిమాణం(SDL_Display_బహుళకం)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_RESTORED, 0, 0);
                            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_ENTER_FULLSCREEN, 0, 0);
                            ఒకవేళ (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&దత్తాంశం->కిటికీ->current_fullscreen_బహుళకం, &దత్తాంశం->కిటికీ->requested_fullscreen_బహుళకం);
                                SDL_Update_Fullscreen_బహుళకం(దత్తాంశం->కిటికీ, SDL_FULLSCREEN_OP_UPDATE, true);
                            } లేకపోతే {
                                SDL_Update_Fullscreen_బహుళకం(దత్తాంశం->కిటికీ, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } లేకపోతే {
                        SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_LEAVE_FULLSCREEN, 0, 0);
                        SDL_Update_Fullscreen_బహుళకం(దత్తాంశం->కిటికీ, false, false);

                        SDL_zero(దత్తాంశం->requested_fullscreen_బహుళకం);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_సమితి_కిటికీ_Min_Max(దత్తాంశం->కిటికీ, !!(flags & SDL_కిటికీ_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        ఒకవేళ (దత్తాంశం->fullscreen_borders_forced_on) {
                            దత్తాంశం->toggle_borders = true;
                            దత్తాంశం->fullscreen_borders_forced_on = false;
                        }
                    }

                    ఒకవేళ ((flags & SDL_కిటికీ_FULLSCREEN) &&
                        (దత్తాంశం->border_శిఖరం || దత్తాంశం->border_ఎడమ || దత్తాంశం->border_bottom || దత్తాంశం->border_కుడి)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        దత్తాంశం->కొలత_move_event_flags |= X11_కొలత_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        దత్తాంశం->మునుపటి_borders_nonzero = true;
                    } లేకపోతే ఒకవేళ (!(flags & SDL_కిటికీ_FULLSCREEN) &&
                               దత్తాంశం->మునుపటి_borders_nonzero &&
                               (!దత్తాంశం->border_శిఖరం && !దత్తాంశం->border_ఎడమ && !దత్తాంశం->border_bottom && !దత్తాంశం->border_కుడి)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        దత్తాంశం->కొలత_move_event_flags |= X11_కొలత_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        దత్తాంశం->మునుపటి_borders_nonzero = false;
                    } లేకపోతే {
                        దత్తాంశం->కొలత_move_event_flags = 0;
                        దత్తాంశం->మునుపటి_borders_nonzero = false;

                        ఒకవేళ (!(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) && దత్తాంశం->toggle_borders) {
                            దత్తాంశం->toggle_borders = false;
                            X11_సమితి_కిటికీ_Bordered(_this, దత్తాంశం->కిటికీ, !(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_BORDERLESS));
                        }
                    }
                }
                ఒకవేళ ((మారింది & SDL_కిటికీ_MAXIMIZED) && ((flags & SDL_కిటికీ_MAXIMIZED) && !(flags & SDL_కిటికీ_MINIMIZED))) {
                    దత్తాంశం->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    ఒకవేళ ((మారింది & SDL_కిటికీ_MINIMIZED)) {
                        దత్తాంశం->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_RESTORED, 0, 0);
                    }
                    SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_MAXIMIZED, 0, 0);
                }
                ఒకవేళ ((మారింది & SDL_కిటికీ_MINIMIZED) && (flags & SDL_కిటికీ_MINIMIZED)) {
                    దత్తాంశం->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_MINIMIZED, 0, 0);
                }
                ఒకవేళ (!(flags & (SDL_కిటికీ_MAXIMIZED | SDL_కిటికీ_MINIMIZED))) {
                    దత్తాంశం->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    ఒకవేళ (!(flags & SDL_కిటికీ_FULLSCREEN)) {
                        ఒకవేళ (దత్తాంశం->pending_position) {
                            దత్తాంశం->pending_position = false;
                            దత్తాంశం->pending_operation |= X11_PENDING_OP_MOVE;
                            దత్తాంశం->expected.x = దత్తాంశం->కిటికీ->pending.x - దత్తాంశం->border_ఎడమ;
                            దత్తాంశం->expected.y = దత్తాంశం->కిటికీ->pending.y - దత్తాంశం->border_శిఖరం;
                            X11_XMove_కిటికీ(display, దత్తాంశం->xwindow, దత్తాంశం->expected.x, దత్తాంశం->expected.y);
                        }
                        ఒకవేళ (దత్తాంశం->pending_కొలత) {
                            దత్తాంశం->pending_కొలత = false;
                            దత్తాంశం->pending_operation |= X11_PENDING_OP_RESIZE;
                            దత్తాంశం->expected.w = దత్తాంశం->కిటికీ->pending.w;
                            దత్తాంశం->expected.h = దత్తాంశం->కిటికీ->pending.h;
                            X11_XResize_కిటికీ(display, దత్తాంశం->xwindow, దత్తాంశం->కిటికీ->pending.w, దత్తాంశం->కిటికీ->pending.h);
                        }
                    }
                }
                ఒకవేళ (దత్తాంశం->emit_కొలత_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(దత్తాంశం, &దత్తాంశం->pending_xconfigure);
                    దత్తాంశం->emit_కొలత_move_after_property_notify = false;
                }
                ఒకవేళ ((flags & SDL_కిటికీ_ఆదానం_FOCUS)) {
                    ఒకవేళ (దత్తాంశం->pending_move) {
                        Dispatch_కిటికీ_Move(_this, దత్తాంశం, &దత్తాంశం->pending_move_బిందువు);
                        దత్తాంశం->pending_move = false;
                    }
                }
            }
            ఒకవేళ (మారింది & SDL_కిటికీ_OCCLUDED) {
                SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, (flags & SDL_కిటికీ_OCCLUDED) ? SDL_EVENT_కిటికీ_OCCLUDED : SDL_EVENT_కిటికీ_EXPOSED, 0, 0);
            }
        } లేకపోతే ఒకవేళ (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            పూర్ణాంకం format;
            గుర్తులేని దీర్ఘ nitems, బైట్లు_after;
            గుర్తులేని అక్షరం *prop_దత్తాంశం = ఖాళీ;

            ఒకవేళ (X11_XGet_కిటికీ_Property(display, దత్తాంశం->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &బైట్లు_after, &prop_దత్తాంశం) == Success) {
                ఒకవేళ (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_దత్తాంశం;

                    ఒకవేళ ((state == 0 || state == 3) && !దత్తాంశం->కిటికీ->is_hiding && !(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_HIDDEN)) {
                        // Withdrawn or Iconic
                        ఒకవేళ (!(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_MINIMIZED)) {
                            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_MINIMIZED, 0, 0);
                            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_OCCLUDED, 0, 0);
                        }
                    } లేకపోతే ఒకవేళ (state == 1) { // NormalState
                        ఒకవేళ (దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_MINIMIZED) {
                            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_RESTORED, 0, 0);
                            SDL_Send_కిటికీ_Event(దత్తాంశం->కిటికీ, SDL_EVENT_కిటికీ_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_దత్తాంశం);
            }
        } లేకపోతే ఒకవేళ (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } లేకపోతే ఒకవేళ (xevent->xproperty.atom == videodata->atoms.NET_చట్రం_EXTENTS) {
            X11_Get_Border_విలువలు(దత్తాంశం);
            ఒకవేళ (దత్తాంశం->కొలత_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                దత్తాంశం->కొలత_move_event_flags &= ~X11_కొలత_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            ఒకవేళ (!(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) && దత్తాంశం->toggle_borders) {
                దత్తాంశం->toggle_borders = false;
                X11_సమితి_కిటికీ_Bordered(_this, దత్తాంశం->కిటికీ, !(దత్తాంశం->కిటికీ->flags & SDL_కిటికీ_BORDERLESS));
            }
        }
    } ఆపు;

    స్థితి SelectionNotify:
    {
        Atom లక్ష్యం = xevent->xselection.లక్ష్యం;
#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.కిటికీ,
               xevent->xselection.requestor, xevent->xselection.లక్ష్యం);
#అయితే_ముగింపు
        ఒకవేళ (లక్ష్యం == దత్తాంశం->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, దత్తాంశం->xwindow, videodata->atoms.PRIMARY);

            ఒకవేళ (p.format == 8) {
                అక్షరం *saveptr = ఖాళీ;
                అక్షరం *name = X11_XGetAtomName(display, లక్ష్యం);
                ఒకవేళ (name) {
                    అక్షరం *token = SDL_strtok_r((అక్షరం *)p.దత్తాంశం, "\r\n", &saveptr);
                    అయితే (token) {
                        ఒకవేళ ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_Send_Drop_పాఠ్యం(దత్తాంశం->కిటికీ, token);
                        } లేకపోతే ఒకవేళ (SDL_strcmp("text/uri-list", name) == 0) {
                            ఒకవేళ (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(దత్తాంశం->కిటికీ, ఖాళీ, token);
                            }
                        }
                        token = SDL_strtok_r(ఖాళీ, "\r\n", &saveptr);
                    }
                    X11_XFree(name);
                }
                SDL_SendDropComplete(దత్తాంశం->కిటికీ);
            }
            X11_XFree(p.దత్తాంశం);

            // send reply
            SDL_zero(m);
            m.type = Client_సందేశం;
            m.display = display;
            m.కిటికీ = దత్తాంశం->xdnd_ఆధారం;
            m.సందేశం_type = videodata->atoms.Xdnd_ముగిసిన;
            m.format = 32;
            m.దత్తాంశం.l[0] = దత్తాంశం->xwindow;
            m.దత్తాంశం.l[1] = 1;
            m.దత్తాంశం.l[2] = videodata->atoms.XdndActionCopy;
            X11_XSendEvent(display, దత్తాంశం->xdnd_ఆధారం, False, No_Event_ముసుగు, (XEvent *)&m);

            X11_XSync(display, False);
        }
    } ఆపు;

    అప్రమేయ:
    {
#నిర్వచితమైతే DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.కిటికీ, xevent->type);
#అయితే_ముగింపు
    } ఆపు;
    }
}

స్థిర శూన్య X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    పూర్ణాంకం i;

    ఒకవేళ (videodata && videodata->windowlist) {
        కొరకు (i = 0; i < videodata->numwindows; ++i) {
            SDL_కిటికీ_దత్తాంశం *దత్తాంశం = videodata->windowlist[i];
            ఒకవేళ (దత్తాంశం && దత్తాంశం->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                ఒకవేళ (now >= దత్తాంశం->pending_focus_సమయం) {
                    ఒకవేళ (దత్తాంశం->pending_focus == PENDING_FOCUS_లోపల) {
                        X11_Dispatch_Focus_లోపల(_this, దత్తాంశం);
                    } లేకపోతే {
                        X11_Dispatch_Focus_బహిర్గతం(_this, దత్తాంశం);
                    }
                    దత్తాంశం->pending_focus = PENDING_FOCUS_NONE;
                }
            }
        }
    }
}

స్థిర Bool isAnyEvent(Display *display, XEvent *ev, XPointer arg)
{
    తిరిగి True;
}

స్థిర bool X11_PollEvent(Display *display, XEvent *event)
{
    ఒకవేళ (!X11_XCheckIfEvent(display, event, isAnyEvent, ఖాళీ)) {
        తిరిగి false;
    }

    తిరిగి true;
}

శూన్య X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    Display *req_display = దత్తాంశం->request_display;
    కిటికీ_2 xwindow = కిటికీ->అంతర్గత->xwindow;
    XClient_సందేశం_Event event;

    SDL_zero(event);
    event.type = Client_సందేశం;
    event.display = req_display;
    event.send_event = True;
    event.సందేశం_type = దత్తాంశం->atoms._SDL_WAKEUP;
    event.format = 8;

    X11_XSendEvent(req_display, xwindow, False, No_Event_ముసుగు, (XEvent *)&event);
    /* XSendEvent returns a status and it could be BadValue or BadWindow. If an
      error happens it is an SDL's internal error and there is nothing we can do here. */
    X11_XFlush(req_display);
}

పూర్ణాంకం X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    ఒకవేళ (X11_PollEvent(display, &xevent)) {
        // Fall through
    } లేకపోతే ఒకవేళ (timeoutNS == 0) {
        తిరిగి 0;
    } లేకపోతే {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        పూర్ణాంకం err = SDL_IOReady(Connection_సంఖ్య(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        ఒకవేళ (err > 0) {
            ఒకవేళ (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                తిరిగి 1;
            }
        } లేకపోతే ఒకవేళ (err == 0) {
            // Timeout
            తిరిగి 0;
        } లేకపోతే {
            // Error returned from poll()/select()

            ఒకవేళ (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                తిరిగి 1;
            } లేకపోతే {
                తిరిగి err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    తిరిగి 1;
}

శూన్య X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    XEvent xevent;
    పూర్ణాంకం i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    కొరకు (i = 0; i < _this->అంకె_displays; ++i) {
        ఒకవేళ (_this->displays[i]->అంతర్గత->బహుళకం_switch_deadline_ns) {
            ఒకవేళ (_this->displays[i]->fullscreen_కిటికీ) {
                _this->displays[i]->అంతర్గత->బహుళకం_switch_deadline_ns = 0;
            } లేకపోతే ఒకవేళ (SDL_GetTicksNS() >= _this->displays[i]->అంతర్గత->బహుళకం_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_సమితి_Display_బహుళకం_For_Display(_this->displays[i], ఖాళీ);
                _this->displays[i]->అంతర్గత->బహుళకం_switch_deadline_ns = 0;
            }
        }
    }

    ఒకవేళ (దత్తాంశం->చివరి_బహుళకం_change_deadline) {
        ఒకవేళ (SDL_GetTicks() >= దత్తాంశం->చివరి_బహుళకం_change_deadline) {
            దత్తాంశం->చివరి_బహుళకం_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    ఒకవేళ (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        ఒకవేళ (!దత్తాంశం->screensaver_activity || now >= (దత్తాంశం->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(దత్తాంశం->display);

#నిర్వచితమైతే SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#అయితే_ముగింపు

            దత్తాంశం->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    అయితే (X11_PollEvent(దత్తాంశం->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    కొరకు (i = 0; i < దత్తాంశం->numwindows; ++i) {
        ఒకవేళ (దత్తాంశం->windowlist[i] != ఖాళీ &&
            దత్తాంశం->windowlist[i]->flash_cancel_సమయం &&
            SDL_GetTicks() >= దత్తాంశం->windowlist[i]->flash_cancel_సమయం) {
            X11_Flash_కిటికీ(_this, దత్తాంశం->windowlist[i]->కిటికీ, SDL_FLASH_CANCEL);
        }
    }

    ఒకవేళ (దత్తాంశం->xinput_hierarchy_మారింది) {
        X11_Xinput2UpdateDevices(_this);
        దత్తాంశం->xinput_hierarchy_మారింది = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    పూర్ణాంకం dummy;
    పూర్ణాంకం major_సంస్కరణ, minor_సంస్కరణ;
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#నిర్వచితమైతే SDL_USE_LIBDBUS
    ఒకవేళ (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        తిరిగి true;
    }

    ఒకవేళ (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    ఒకవేళ (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        ఒకవేళ (!X11_XScreenSaverQueryExtension(దత్తాంశం->display, &dummy, &dummy) ||
            !X11_XScreen_Saver_Query_సంస్కరణ(దత్తాంశం->display,
                                          &major_సంస్కరణ, &minor_సంస్కరణ) ||
            major_సంస్కరణ < 1 || (major_సంస్కరణ == 1 && minor_సంస్కరణ < 1)) {
            తిరిగి SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(దత్తాంశం->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(దత్తాంశం->display);
        తిరిగి true;
    }
#అయితే_ముగింపు
    తిరిగి SDL_Unsupported();
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
