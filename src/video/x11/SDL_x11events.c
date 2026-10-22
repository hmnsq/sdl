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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#شامل <sys/types.h>
#شامل <sys/time.h>
#شامل <signal.h>
#شامل <unistd.h>
#شامل <limits.h> // For INT_MAX

#شامل "SDL_x11video.h"
#شامل "SDL_x11pen.h"
#شامل "SDL_x11touch.h"
#شامل "SDL_x11xinput2.h"
#شامل "SDL_x11xfixes.h"
#شامل "SDL_x11settings.h"
#شامل "../SDL_clipboard_c.h"
#شامل "SDL_x11xsync.h"
#شامل "../../core/unix/SDL_poll.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_touch_c.h"
#شامل "../../core/linux/SDL_system_theme.h"
#شامل "../SDL_sysvideo.h"

#شامل <stdio.h>

#اگر 0
#تعریف_کرو DEBUG_XEVENTS
#اگر_ختم

#اگر_غیر_تعریف_شدہ NET_WM_MOVERESIZE_سائز_TOPLEFT
#تعریف_کرو NET_WM_MOVERESIZE_سائز_TOPLEFT 0
#اگر_ختم

#اگر_غیر_تعریف_شدہ NET_WM_MOVERESIZE_سائز_چوٹی
#تعریف_کرو NET_WM_MOVERESIZE_سائز_چوٹی 1
#اگر_ختم

#اگر_غیر_تعریف_شدہ NET_WM_MOVERESIZE_سائز_TOPRIGHT
#تعریف_کرو NET_WM_MOVERESIZE_سائز_TOPRIGHT 2
#اگر_ختم

#اگر_غیر_تعریف_شدہ NET_WM_MOVERESIZE_سائز_دایاں
#تعریف_کرو NET_WM_MOVERESIZE_سائز_دایاں 3
#اگر_ختم

#اگر_غیر_تعریف_شدہ NET_WM_MOVERESIZE_سائز_BOTTOMRIGHT
#تعریف_کرو NET_WM_MOVERESIZE_سائز_BOTTOMRIGHT 4
#اگر_ختم

#اگر_غیر_تعریف_شدہ NET_WM_MOVERESIZE_سائز_BOTTOM
#تعریف_کرو NET_WM_MOVERESIZE_سائز_BOTTOM 5
#اگر_ختم

#اگر_غیر_تعریف_شدہ NET_WM_MOVERESIZE_سائز_BOTTOMLEFT
#تعریف_کرو NET_WM_MOVERESIZE_سائز_BOTTOMLEFT 6
#اگر_ختم

#اگر_غیر_تعریف_شدہ NET_WM_MOVERESIZE_سائز_بایاں
#تعریف_کرو NET_WM_MOVERESIZE_سائز_بایاں 7
#اگر_ختم

#اگر_غیر_تعریف_شدہ _NET_WM_MOVERESIZE_MOVE
#تعریف_کرو _NET_WM_MOVERESIZE_MOVE 8
#اگر_ختم

قسمتعریف ساخت
{
    غیرعلامتی حرف *ڈیٹا;
    صحیح format, گنتی;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
ساکن خالی X11_ReadProperty(SDL_x11Prop *p, Display *disp, کھڑکی_2 w, Atom prop)
{
    غیرعلامتی حرف *ret = تہی;
    Atom type;
    صحیح fmt;
    غیرعلامتی طویل گنتی;
    غیرعلامتی طویل بائٹیں_بایاں;
    صحیح بائٹیں_fetch = 0;

    کرو {
        اگر (ret) {
            X11_XFree(ret);
        }
        X11_XGet_کھڑکی_Property(disp, w, prop, 0, بائٹیں_fetch, False, AnyPropertyType, &type, &fmt, &گنتی, &بائٹیں_بایاں, &ret);
        بائٹیں_fetch += بائٹیں_بایاں;
    } جب (بائٹیں_بایاں != 0);

    p->ڈیٹا = ret;
    p->format = fmt;
    p->گنتی = گنتی;
    p->type = type;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
ساکن Atom X11_Pick_ہدف(Display *disp, Atom list[], صحیح list_گنتی)
{
    ثابت Atom متن_uri_request = X11_XInternAtom(disp, "text/uri-list", False);
    Atom request = None;
    Atom preferred = None;

    برائے (صحیح i = 0; i < list_گنتی && request != متن_uri_request; i++) {
        حرف *name = X11_XGetAtomName(disp, list[i]);
        // Preferred MIME targets
        اگر ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            اگر (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        اگر ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            اگر (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    اگر (preferred != None && request != متن_uri_request) {
        request = preferred;
    }
    واپس request;
}

/* Wrapper for X11_PickTarget for a maximum of three targets, a special
   case in the Xdnd protocol */
ساکن Atom X11_Pick_ہدف_From_Atoms(Display *disp, Atom a0, Atom a1, Atom a2)
{
    صحیح گنتی = 0;
    Atom atom[3];
    اگر (a0 != None) {
        atom[گنتی++] = a0;
    }
    اگر (a1 != None) {
        atom[گنتی++] = a1;
    }
    اگر (a2 != None) {
        atom[گنتی++] = a2;
    }
    واپس X11_Pick_ہدف(disp, atom, گنتی);
}

ساخت کلید_Repeat_Check_ڈیٹا
{
    XEvent *event;
    bool ملا;
};

ساکن Bool X11_کلید_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    ساخت کلید_Repeat_Check_ڈیٹا *d = (ساخت کلید_Repeat_Check_ڈیٹا *)arg;
    اگر (chkev->type == کلید_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.وقت - d->event->xkey.وقت < 2) {
        d->ملا = true;
    }
    واپس False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
ساکن bool X11_کلید_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    ساخت کلید_Repeat_Check_ڈیٹا d;
    d.event = event;
    d.ملا = false;
    اگر (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_کلید_Repeat_Check_If_Event, (XPointer)&d);
    }
    واپس d.ملا;
}

bool X11_IsWheelEvent(صحیح button, صحیح *xticks, صحیح *yticks)
{
    /* according to the xlib docs, no specific mouse wheel events exist.
       However, the defacto standard is that the vertical wheel is X buttons
       4 (up) and 5 (down) and a horizontal wheel is 6 (left) and 7 (right). */

    // Xlib defines "Button1" through 5, so we just use literals here.
    انتخاب (button) {
    حالت 4:
        *yticks = 1;
        واپس true;
    حالت 5:
        *yticks = -1;
        واپس true;
    حالت 6:
        *xticks = 1;
        واپس true;
    حالت 7:
        *xticks = -1;
        واپس true;
    طےشدہ:
        توڑو;
    }
    واپس false;
}

// An X11 event hook
ساکن SDL_X11EventHook g_X11EventHook = تہی;
ساکن خالی *g_X11_Event_Hook_ڈیٹا = تہی;

خالی SDL_سیٹ_X11_Event_Hook(SDL_X11EventHook callback, خالی *userdata)
{
    g_X11EventHook = callback;
    g_X11_Event_Hook_ڈیٹا = userdata;
}

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
ساکن خالی X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    اگر (X11_XGet_Event_ڈیٹا(videodata->display, cookie)) {
        اگر (!g_X11EventHook || g_X11EventHook(g_X11_Event_Hook_ڈیٹا, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFree_Event_ڈیٹا(videodata->display, cookie);
    }
}
#اگر_ختم // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

ساکن خالی X11_Update_System_کلید_Modifiers(SDL_Video_ڈیٹا *viddata)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    اگر (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        اگر (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.بنیاد_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } ورنہ
#اگر_ختم
        {
        کھڑکی_2 junk_کھڑکی;
        صحیح x, y;
        غیرعلامتی صحیح mod_نقاب;

        X11_XQuery_اشارہ_گر(viddata->display, Default_جڑ_کھڑکی(viddata->display), &junk_کھڑکی, &junk_کھڑکی, &x, &y, &x, &y, &mod_نقاب);
        viddata->keyboard.pressed_modifiers = mod_نقاب & (سرکاؤ_نقاب_2 | Control_نقاب | Mod1_نقاب | Mod3_نقاب | Mod4_نقاب | Mod5_نقاب);
        viddata->keyboard.locked_modifiers = mod_نقاب & (تالا_نقاب | viddata->keyboard.numlock_نقاب | viddata->keyboard.scrolllock_نقاب);
    }
}

ساکن خالی X11_ReconcileModifiers(SDL_Video_ڈیٹا *viddata, bool کلید_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    اگر (کلید_pressed) {
        اگر (viddata->keyboard.pressed_modifiers & سرکاؤ_نقاب_2) {
            اگر (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_سرکاؤ) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_سرکاؤ;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_سرکاؤ);
            }
        }

        اگر (viddata->keyboard.pressed_modifiers & Control_نقاب) {
            اگر (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        اگر (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_نقاب) {
            اگر (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        اگر (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_نقاب) {
            اگر (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } ورنہ {
        اگر (viddata->keyboard.pressed_modifiers & سرکاؤ_نقاب_2) {
            اگر (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_سرکاؤ)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_سرکاؤ;
            }
        } ورنہ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_سرکاؤ;
        }

        اگر (viddata->keyboard.pressed_modifiers & Control_نقاب) {
            اگر (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } ورنہ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        اگر (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_نقاب) {
            اگر (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } ورنہ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        اگر (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_نقاب) {
            اگر (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } ورنہ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        اگر (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_نقاب) {
            اگر (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_منوال)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_منوال;
            }
        } ورنہ {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_منوال;
        }

        اگر (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_نقاب) {
            اگر (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } ورنہ {
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
    اگر (viddata->keyboard.locked_modifiers & سرکاؤ_نقاب_2) {
        اگر (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_سرکاؤ) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_سرکاؤ;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_سرکاؤ);
        } ورنہ اگر (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_سرکاؤ)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_سرکاؤ;
        }
    } ورنہ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_سرکاؤ;
    }

    اگر (viddata->keyboard.locked_modifiers & Control_نقاب) {
        اگر (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } ورنہ اگر (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } ورنہ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    اگر (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_نقاب) {
        اگر (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } ورنہ اگر (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } ورنہ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    اگر (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_نقاب) {
        اگر (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } ورنہ اگر (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } ورنہ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    اگر (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_منوال;
    } ورنہ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_منوال;
    }

    اگر (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } ورنہ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    اگر (viddata->keyboard.locked_modifiers & تالا_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } ورنہ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    اگر (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_عدد;
    } ورنہ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_عدد;
    }

    اگر (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_نقاب) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } ورنہ {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_سیٹ_Mod_State(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

ساکن خالی X11_Handle_Modifier_کلیدیں(SDL_Video_ڈیٹا *viddata, SDL_Scancode scancode, bool pressed)
{
    ثابت SDL_Keycode keycode = SDL_Get_کلید_From_Scancode(scancode, SDL_KMOD_NONE, false);
    SDL_Keymod mod = SDL_KMOD_NONE;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is checked.
     */
    انتخاب (keycode) {
    حالت SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        توڑو;
    حالت SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        توڑو;
    حالت SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        توڑو;
    حالت SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        توڑو;
    حالت SDLK_LALT:
        mod = SDL_KMOD_LALT;
        توڑو;
    حالت SDLK_RALT:
        mod = SDL_KMOD_RALT;
        توڑو;
    حالت SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        توڑو;
    حالت SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        توڑو;
    حالت SDLK_منوال:
        mod = SDL_KMOD_منوال;
        توڑو;
    حالت SDLK_LEVEL5_سرکاؤ:
        mod = SDL_KMOD_LEVEL5;
        توڑو;
    حالت SDLK_CAPSLOCK:
    حالت SDLK_NUMLOCKCLEAR:
    حالت SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        اگر (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            غیرعلامتی صحیح cur_نقاب = viddata->keyboard.locked_modifiers;
            X11_Update_System_کلید_Modifiers(viddata);

            اگر (viddata->keyboard.locked_modifiers & تالا_نقاب) {
                cur_نقاب |= تالا_نقاب;
            } ورنہ {
                cur_نقاب &= ~تالا_نقاب;
            }
            اگر (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_نقاب) {
                cur_نقاب |= viddata->keyboard.numlock_نقاب;
            } ورنہ {
                cur_نقاب &= ~viddata->keyboard.numlock_نقاب;
            }
            اگر (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_نقاب) {
                cur_نقاب |= viddata->keyboard.scrolllock_نقاب;
            } ورنہ {
                cur_نقاب &= ~viddata->keyboard.scrolllock_نقاب;
            }

            viddata->keyboard.locked_modifiers = cur_نقاب;
        }
    } توڑو;
    طےشدہ:
        واپس;
    }

    اگر (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } ورنہ {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

خالی X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    Display *display = videodata->display;
    حرف کلیدیں[32];

    // Rebuild the modifier state in case it changed while focus was lost.
    X11_Update_System_کلید_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, false);

    // Keep caps, num, and scroll, but clear the others until we have updated key state.
    videodata->keyboard.sdl_pressed_modifiers = 0;
    videodata->keyboard.sdl_physically_pressed_modifiers = 0;
    videodata->keyboard.sdl_locked_modifiers &= SDL_KMOD_CAPS | SDL_KMOD_عدد | SDL_KMOD_SCROLL;
    videodata->keyboard.pressed_modifiers = 0;
    videodata->keyboard.locked_modifiers &= تالا_نقاب | videodata->keyboard.numlock_نقاب| videodata->keyboard.scrolllock_نقاب;

    X11_XQueryKeymap(display, کلیدیں);

    ثابت bool *keystate = SDL_GetKeyboardState(تہی);
    برائے (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.کلید_layout); ++keycode) {
        ثابت SDL_Scancode scancode = videodata->keyboard.کلید_layout[keycode];
        ثابت bool x11_کلید_Pressed = (کلیدیں[keycode / 8] & (1 << (keycode % 8))) != 0;
        ثابت bool sdl_کلید_Pressed = keystate[scancode];

        اگر (x11_کلید_Pressed && !sdl_کلید_Pressed) {
            // Only update modifier state for keys that are pressed in another application
            انتخاب (SDL_Get_کلید_From_Scancode(scancode, SDL_KMOD_NONE, false)) {
            حالت SDLK_LCTRL:
            حالت SDLK_RCTRL:
            حالت SDLK_LSHIFT:
            حالت SDLK_RSHIFT:
            حالت SDLK_LALT:
            حالت SDLK_RALT:
            حالت SDLK_LGUI:
            حالت SDLK_RGUI:
            حالت SDLK_منوال:
            حالت SDLK_LEVEL5_سرکاؤ:
                X11_Handle_Modifier_کلیدیں(videodata, scancode, true);
                SDL_Send_Keyboard_کلید_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                توڑو;
            طےشدہ:
                توڑو;
            }
        } ورنہ اگر (!x11_کلید_Pressed && sdl_کلید_Pressed) {
            X11_Handle_Modifier_کلیدیں(videodata, scancode, false);
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_کلید_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

ساکن خالی X11_Dispatch_Focus_اندر(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
#اگر_تعریف_شدہ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", ڈیٹا->xwindow);
#اگر_ختم
    SDL_سیٹ_Keyboard_Focus(ڈیٹا->کھڑکی);
    X11_ReconcileKeyboardState(_this);
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    اگر (ڈیٹا->ic) {
        X11_XSetICFocus(ڈیٹا->ic);
    }
#اگر_ختم
    اگر (ڈیٹا->flashing_کھڑکی) {
        X11_Flash_کھڑکی(_this, ڈیٹا->کھڑکی, SDL_FLASH_CANCEL);
    }
}

ساکن خالی X11_Dispatch_Focus_برآمد(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
#اگر_تعریف_شدہ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", ڈیٹا->xwindow);
#اگر_ختم
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    اگر (ڈیٹا->کھڑکی == SDL_GetKeyboardFocus()) {
        SDL_سیٹ_Keyboard_Focus(تہی);
    }
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    اگر (ڈیٹا->ic) {
        X11_XUnsetICFocus(ڈیٹا->ic);
    }
#اگر_ختم
}

ساکن خالی X11_DispatchMapNotify(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    SDL_کھڑکی *کھڑکی = ڈیٹا->کھڑکی;

    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);
    ڈیٹا->was_shown = true;

    // This may be sent when restoring a minimized window.
    اگر (کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
        SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
    }

    اگر (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
        SDL_Update_کھڑکی_Grab(کھڑکی);
    }
}

ساکن خالی X11_DispatchUnmapNotify(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    SDL_کھڑکی *کھڑکی = ڈیٹا->کھڑکی;

    // This may be sent when minimizing a window.
    اگر (!کھڑکی->is_hiding) {
        SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
        SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_OCCLUDED, 0, 0);
    } ورنہ {
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_HIDDEN, 0, 0);
    }
}

ساکن خالی Dispatch_کھڑکی_Move(SDL_VideoDevice *_this, ثابت SDL_کھڑکی_ڈیٹا *ڈیٹا, ثابت SDL_نقطہ *نقطہ)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    SDL_کھڑکی *کھڑکی = ڈیٹا->کھڑکی;
    Display *display = videodata->display;
    XEvent evt;

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_اشارہ_گر(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_پیغام;
    evt.xclient.کھڑکی = ڈیٹا->xwindow;
    evt.xclient.پیغام_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.ڈیٹا.l[0] = (size_t)کھڑکی->x + نقطہ->x;
    evt.xclient.ڈیٹا.l[1] = (size_t)کھڑکی->y + نقطہ->y;
    evt.xclient.ڈیٹا.l[2] = _NET_WM_MOVERESIZE_MOVE;
    evt.xclient.ڈیٹا.l[3] = Button1;
    evt.xclient.ڈیٹا.l[4] = 0;
    X11_XSendEvent(display, Default_جڑ_کھڑکی(display), False, Substructure_Redirect_نقاب | Substructure_Notify_نقاب, &evt);

    X11_XSync(display, 0);
}

ساکن خالی جدول_وقت_کھڑکی_Move(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *ڈیٹا, ثابت SDL_نقطہ *نقطہ)
{
    ڈیٹا->pending_move = true;
    ڈیٹا->pending_move_نقطہ = *نقطہ;
}

ساکن خالی Initiate_کھڑکی_Resize(SDL_VideoDevice *_this, ثابت SDL_کھڑکی_ڈیٹا *ڈیٹا, ثابت SDL_نقطہ *نقطہ, صحیح direction)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    SDL_کھڑکی *کھڑکی = ڈیٹا->کھڑکی;
    Display *display = videodata->display;
    XEvent evt;

    اگر (direction < NET_WM_MOVERESIZE_سائز_TOPLEFT || direction > NET_WM_MOVERESIZE_سائز_بایاں) {
        واپس;
    }

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrab_اشارہ_گر(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_پیغام;
    evt.xclient.کھڑکی = ڈیٹا->xwindow;
    evt.xclient.پیغام_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.ڈیٹا.l[0] = (size_t)کھڑکی->x + نقطہ->x;
    evt.xclient.ڈیٹا.l[1] = (size_t)کھڑکی->y + نقطہ->y;
    evt.xclient.ڈیٹا.l[2] = direction;
    evt.xclient.ڈیٹا.l[3] = Button1;
    evt.xclient.ڈیٹا.l[4] = 0;
    X11_XSendEvent(display, Default_جڑ_کھڑکی(display), False, Substructure_Redirect_نقاب | Substructure_Notify_نقاب, &evt);

    X11_XSync(display, 0);
}

bool X11_Process_کامیابی_Test(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *ڈیٹا, ثابت اعشاری x, ثابت اعشاری y, bool force_new_نتیجہ)
{
    SDL_کھڑکی *کھڑکی = ڈیٹا->کھڑکی;
    اگر (!کھڑکی->کامیابی_test) واپس false;
    ثابت SDL_نقطہ نقطہ = { (صحیح)x, (صحیح)y };
    SDL_کامیابی_Test_نتیجہ rc = کھڑکی->کامیابی_test(کھڑکی, &نقطہ, کھڑکی->کامیابی_test_ڈیٹا);
    اگر (!force_new_نتیجہ && rc == ڈیٹا->کامیابی_test_نتیجہ) {
        واپس true;
    }
    X11_سیٹ_کامیابی_Test_Cursor(rc);
    ڈیٹا->کامیابی_test_نتیجہ = rc;
    واپس true;
}

bool X11_Trigger_کامیابی_Test_Action(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *ڈیٹا, ثابت اعشاری x, ثابت اعشاری y)
{
    SDL_کھڑکی *کھڑکی = ڈیٹا->کھڑکی;

    اگر (کھڑکی->کامیابی_test) {
        ثابت SDL_نقطہ نقطہ = { (صحیح)x, (صحیح)y };
        ساکن ثابت صحیح directions[] = {
            NET_WM_MOVERESIZE_سائز_TOPLEFT, NET_WM_MOVERESIZE_سائز_چوٹی,
            NET_WM_MOVERESIZE_سائز_TOPRIGHT, NET_WM_MOVERESIZE_سائز_دایاں,
            NET_WM_MOVERESIZE_سائز_BOTTOMRIGHT, NET_WM_MOVERESIZE_سائز_BOTTOM,
            NET_WM_MOVERESIZE_سائز_BOTTOMLEFT, NET_WM_MOVERESIZE_سائز_بایاں
        };

        انتخاب (ڈیٹا->کامیابی_test_نتیجہ) {
        حالت SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            اگر (ڈیٹا->کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
                Dispatch_کھڑکی_Move(_this, ڈیٹا, &نقطہ);
            } ورنہ {
                جدول_وقت_کھڑکی_Move(_this, ڈیٹا, &نقطہ);
            }
            واپس true;

        حالت SDL_HITTEST_RESIZE_TOPLEFT:
        حالت SDL_HITTEST_RESIZE_چوٹی:
        حالت SDL_HITTEST_RESIZE_TOPRIGHT:
        حالت SDL_HITTEST_RESIZE_دایاں:
        حالت SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        حالت SDL_HITTEST_RESIZE_BOTTOM:
        حالت SDL_HITTEST_RESIZE_BOTTOMLEFT:
        حالت SDL_HITTEST_RESIZE_بایاں:
            Initiate_کھڑکی_Resize(_this, ڈیٹا, &نقطہ, directions[ڈیٹا->کامیابی_test_نتیجہ - SDL_HITTEST_RESIZE_TOPLEFT]);
            واپس true;

        طےشدہ:
            واپس false;
        }
    }

    واپس false;
}

ساکن خالی X11_Update_User_وقت(SDL_کھڑکی_ڈیٹا *ڈیٹا, ثابت غیرعلامتی طویل latest)
{
    اگر (latest && (latest != ڈیٹا->user_وقت)) {
        SDL_Video_ڈیٹا *videodata = ڈیٹا->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, ڈیٹا->xwindow, videodata->atoms.NET_WM_USER_وقت,
                            XA_CARDINAL, 32, Prop_منوال_Replace,
                            (ثابت غیرعلامتی حرف *)&latest, 1);
#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", ڈیٹا->xwindow, latest);
#اگر_ختم
        ڈیٹا->user_وقت = latest;
    }
}

ساکن غیرعلامتی حرف x11_آخری_error;
ساکن صحیح Bad_کھڑکی_Error_Handler(Display *d, XErrorEvent *e)
{
    x11_آخری_error = e->error_رمز;

    // Ignore BadWindow in cases where it's not fatal.
    اگر (e->error_رمز != Bad_کھڑکی) {
        حرف err_پیغام[128];
        X11_XGet_Error_متن(d, e->error_رمز, err_پیغام, حجم(err_پیغام));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_رمز, err_پیغام, e->request_رمز);
    }
    واپس 0;
}

ساکن خالی X11_HandleClipboardEvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    صحیح i;
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_کھڑکی != None);
    SDL_assert(xevent->xany.کھڑکی == videodata->clipboard_کھڑکی);

    انتخاب (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    حالت SelectionRequest:
    {
        ثابت XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        صحیح mime_formats;
        غیرعلامتی حرف *seln_ڈیٹا;
        size_t seln_لمبائی = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_Clipboard_ڈیٹا *clipboard;

#اگر_تعریف_شدہ DEBUG_XEVENTS
        حرف *atom_name;
        atom_name = X11_XGetAtomName(display, req->ہدف);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->ہدف, atom_name);
        اگر (atom_name) {
            X11_XFree(atom_name);
        }
#اگر_ختم

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_آخری_error = 0;
        XErrorHandler پچھلا_handler = X11_XSetErrorHandler(Bad_کھڑکی_Error_Handler);

        اگر (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ورنہ {
            clipboard = &videodata->clipboard;
        }

        SDL_zero(sevent);
        sevent.xany.type = SelectionNotify;
        sevent.xselection.selection = req->selection;
        sevent.xselection.ہدف = None;
        sevent.xselection.property = None; // tell them no by default
        sevent.xselection.requestor = req->requestor;
        sevent.xselection.وقت = req->وقت;

        /* !!! FIXME: We were probably storing this on the root window
           because an SDL window might go away...? but we don't have to do
           this now (or ever, really). */

        اگر (req->ہدف == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_گنتی + 1) * حجم(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            برائے (i = 0; i < clipboard->mime_گنتی; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, Prop_منوال_Replace,
                                (غیرعلامتی حرف *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.ہدف = XA_TARGETS;
            SDL_free(supportedFormats);
        } ورنہ {
            اگر (clipboard->callback) {
                برائے (i = 0; i < clipboard->mime_گنتی; ++i) {
                    ثابت حرف *mime_type = clipboard->mime_types[i];
                    اگر (X11_XInternAtom(display, mime_type, False) != req->ہدف) {
                        جاری;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_ڈیٹا = (غیرعلامتی حرف *)clipboard->callback(clipboard->userdata, mime_type, &seln_لمبائی);
                    اگر (seln_ڈیٹا) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->ہدف, 8, Prop_منوال_Replace,
                                            seln_ڈیٹا, seln_لمبائی);
                        sevent.xselection.property = req->property;
                        sevent.xselection.ہدف = req->ہدف;
                    }
                    توڑو;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(پچھلا_handler);
    } توڑو;

    حالت SelectionNotify:
    {
        ثابت XSelectionEvent *xsel = &xevent->xselection;
#اگر_تعریف_شدہ DEBUG_XEVENTS
        ثابت حرف *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        ثابت حرف *ہدف_Name = xsel->ہدف ? X11_XGetAtomName(display, xsel->ہدف) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, ہدف_Name, propName);
#اگر_ختم
        اگر (xsel->ہدف == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            غیرعلامتی حرف *ڈیٹا = تہی;
            صحیح format_property = 0;
            غیرعلامتی طویل لمبائی = 0;
            غیرعلامتی طویل بائٹیں_بایاں = 0;
            صحیح j;

            X11_XGet_کھڑکی_Property(display, Get_کھڑکی(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &لمبائی, &بائٹیں_بایاں, &ڈیٹا);

            صحیح allocationsize = (لمبائی + 1) * حجم(حرف *);
            برائے (j = 0, patom = (Atom *)ڈیٹا; j < لمبائی; j++, patom++) {
                حرف *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            حرف **new_mime_types = SDL_Allocate_Temporary_حافظہ(allocationsize);
            اگر (new_mime_types) {
                حرف *strPtr = (حرف *)(new_mime_types + لمبائی + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                برائے (j = 0, patom = (Atom *)ڈیٹا; j < لمبائی; j++, patom++) {
                    حرف *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    ثابت size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[لمبائی] = تہی;

                SDL_SendClipboardUpdate(false, new_mime_types, لمبائی);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            اگر (ڈیٹا) {
                X11_XFree(ڈیٹا);
            }
        }

        videodata->selection_انتظار = false;
    } توڑو;

    حالت SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_Clipboard_ڈیٹا *clipboard = تہی;

#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.ہدف);
#اگر_ختم

        اگر (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } ورنہ اگر (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        اگر (clipboard && clipboard->callback) {
            اگر (clipboard->sequence) {
                SDL_Cancel_Clipboard_ڈیٹا(clipboard->sequence);
            } ورنہ {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } توڑو;

    حالت PropertyNotify:
    {
        حرف *name_کا_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        اگر (SDL_strncmp(name_کا_atom, "SDL_SELECTION", حجم("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_قدر) {
            videodata->selection_incr_انتظار = false;
        }

        اگر (name_کا_atom) {
            X11_XFree(name_کا_atom);
        }
    } توڑو;
    }
}

ساکن Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    واپس ev->type == MapNotify &&
           ev->xmap.کھڑکی == unmap->کھڑکی &&
           ev->xmap.serial == unmap->serial;
}

ساکن Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    واپس ev->type == ReparentNotify &&
           ev->xreparent.کھڑکی == unmap->کھڑکی &&
           ev->xreparent.serial == unmap->serial;
}

ساکن bool Is_بلند_Latin1(ثابت حرف *string, صحیح لمبائی)
{
    جب (لمبائی-- > 0) {
        Uint8 ch = (Uint8)*string;
        اگر (ch >= 0x80) {
            واپس true;
        }
        ++string;
    }
    واپس false;
}

ساکن صحیح XLookupStringAsUTF8(XKeyEvent *event_struct, حرف *بفر_return, صحیح بائٹیں_بفر, کلید_Sym *keysym_return, XCompose_حالت *حالت_اندر_برآمد)
{
    صحیح نتیجہ = X11_XLookupString(event_struct, بفر_return, بائٹیں_بفر, keysym_return, حالت_اندر_برآمد);
    اگر (Is_بلند_Latin1(بفر_return, نتیجہ)) {
        حرف *utf8_متن = SDL_iconv_string("UTF-8", "ISO-8859-1", بفر_return, نتیجہ + 1);
        اگر (utf8_متن) {
            SDL_strlcpy(بفر_return, utf8_متن, بائٹیں_بفر);
            SDL_free(utf8_متن);
            واپس SDL_strlen(بفر_return);
        } ورنہ {
            واپس 0;
        }
    }
    واپس نتیجہ;
}

SDL_کھڑکی_ڈیٹا *X11_ڈھونڈو_کھڑکی(SDL_Video_ڈیٹا *videodata, کھڑکی_2 کھڑکی)
{
    اگر (videodata && videodata->windowlist) {
        برائے (صحیح i = 0; i < videodata->numwindows; ++i) {
            اگر ((videodata->windowlist[i] != تہی) &&
                (videodata->windowlist[i]->xwindow == کھڑکی)) {
                واپس videodata->windowlist[i];
            }
        }
    }
    واپس تہی;
}

Uint64 X11_GetEventTimestamp(غیرعلامتی طویل وقت)
{
    // FIXME: Get the event time in the SDL tick time base
    واپس SDL_GetTicksNS();
}

خالی X11_Handle_کلید_Event(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    Display *display = videodata->display;
    کلید_رمز_2 keycode = xevent->xkey.keycode;
    کلید_Sym keysym = No_علامت;
    صحیح متن_لمبائی = 0;
    حرف متن[64];
    حالت_3 حالت_2 = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == کلید_Press);
    SDL_Scancode scancode = videodata->keyboard.کلید_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.وقت);

#اگر_تعریف_شدہ DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.کھڑکی, (xevent->type == کلید_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#اگر_ختم
#اگر_تعریف_شدہ DEBUG_SCANCODES
    اگر (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        صحیح min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_کلید_رمز_مقصد_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysym_مقصد_String(keysym));
    }
#اگر_ختم // DEBUG SCANCODES

    متن[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    اگر (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (سرکاؤ_نقاب_2 | Control_نقاب | Mod1_نقاب | Mod3_نقاب | Mod4_نقاب | Mod5_نقاب);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (تالا_نقاب | videodata->keyboard.numlock_نقاب | videodata->keyboard.scrolllock_نقاب);
    }

    اگر (SDL_متن_داخلہ_فعال(windowdata->کھڑکی)) {
        // filter events catches XIM events and sends them to the correct handler
        اگر (X11_XFilterEvent(xevent, None)) {
#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.کھڑکی);
#اگر_ختم
            handled_by_ime = true;
        }

        اگر (!handled_by_ime) {
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
            اگر (windowdata->ic && xevent->type == کلید_Press) {
                متن_لمبائی = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, متن, حجم(متن) - 1,
                                      &keysym, &حالت_2);
            } ورنہ {
                متن_لمبائی = XLookupStringAsUTF8(&xevent->xkey, متن, حجم(متن) - 1, &keysym, تہی);
            }
#ورنہ
            متن_لمبائی = XLookupStringAsUTF8(&xevent->xkey, متن, حجم(متن) - 1, &keysym, تہی);
#اگر_ختم
        }
    }

    اگر (!handled_by_ime) {
        اگر (pressed) {
            X11_Handle_Modifier_کلیدیں(videodata, scancode, true);
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            اگر (*متن && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                متن[متن_لمبائی] = '\0';
                X11_ClearComposition(windowdata);
                SDL_Send_Keyboard_متن(متن);
            }
        } ورنہ {
            اگر (X11_کلید_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                واپس;
            }

            X11_Handle_Modifier_کلیدیں(videodata, scancode, false);
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    اگر (pressed) {
        X11_Update_User_وقت(windowdata, xevent->xkey.وقت);
    }
}

خالی X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *windowdata, SDL_MouseID mouseID, صحیح button, اعشاری x, اعشاری y, غیرعلامتی طویل وقت, غیرعلامتی طویل serial)
{
    SDL_کھڑکی *کھڑکی = windowdata->کھڑکی;
    صحیح xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(وقت);

#اگر_تعریف_شدہ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#اگر_ختم

    SDL_Mouse *mouse = SDL_GetMouse();
    اگر (!mouse->relative_منوال && (x != mouse->x || y != mouse->y)) {
        X11_Process_کامیابی_Test(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, کھڑکی, mouseID, false, x, y);
    }

    اگر (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, کھڑکی, mouseID, (اعشاری)-xticks, (اعشاری)yticks, SDL_MOUSEWHEEL_معمول);
    } ورنہ {
        اگر (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        اگر (button == Button1) {
            اگر (X11_Trigger_کامیابی_Test_Action(_this, windowdata, x, y)) {
                SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_کامیابی_TEST, 0, 0);
                واپس; // don't pass this event on to app.
            }
        }
        اگر (windowdata->آخری_focus_event_وقت) {
            ثابت صحیح X11_FOCUS_CLICK_TIMEOUT = 10;
            اگر (SDL_GetTicks() < (windowdata->آخری_focus_event_وقت + X11_FOCUS_CLICK_TIMEOUT)) {
                اگر (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->آخری_focus_event_وقت = 0;
        }
        اگر (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, کھڑکی, mouseID, button, true);
        }
    }
    X11_Update_User_وقت(windowdata, وقت);
}

خالی X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *windowdata, SDL_MouseID mouseID, صحیح button, غیرعلامتی طویل وقت)
{
    SDL_کھڑکی *کھڑکی = windowdata->کھڑکی;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    صحیح xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(وقت);

#اگر_تعریف_شدہ DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#اگر_ختم
    اگر (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        اگر (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, کھڑکی, mouseID, button, false);

        اگر (کھڑکی->اندرونی_2->pending_grab) {
            X11_سیٹ_کھڑکی_Mouse_Grab(_this, کھڑکی, true);
        }
    }
}

خالی X11_Get_Border_اقدار(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    SDL_Video_ڈیٹا *videodata = ڈیٹا->videodata;
    Display *display = videodata->display;

    Atom type;
    صحیح format;
    غیرعلامتی طویل nitems, بائٹیں_after;
    غیرعلامتی حرف *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    اگر (!(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_BORDERLESS)) {
        اگر (X11_XGet_کھڑکی_Property(display, ڈیٹا->xwindow, videodata->atoms.NET_چوکھٹا_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &بائٹیں_after, &property) == Success) {
            اگر (type != None && nitems == 4) {
                ڈیٹا->border_بایاں = (صحیح)((طویل *)property)[0];
                ڈیٹا->border_دایاں = (صحیح)((طویل *)property)[1];
                ڈیٹا->border_چوٹی = (صحیح)((طویل *)property)[2];
                ڈیٹا->border_bottom = (صحیح)((طویل *)property)[3];
            }
            X11_XFree(property);

#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", ڈیٹا->border_بایاں, ڈیٹا->border_دایاں, ڈیٹا->border_چوٹی, ڈیٹا->border_bottom);
#اگر_ختم
        }
    } ورنہ {
        ڈیٹا->border_بایاں = ڈیٹا->border_چوٹی = ڈیٹا->border_دایاں = ڈیٹا->border_bottom = 0;
    }
}

خالی X11_EmitConfigureNotifyEvents(SDL_کھڑکی_ڈیٹا *ڈیٹا, XConfigureEvent *xevent)
{
    اگر (!ڈیٹا->سائز_move_event_flags) {
        صحیح x = xevent->x;
        صحیح y = xevent->y;

        اگر (xevent->x != ڈیٹا->آخری_xconfigure.x ||
            xevent->y != ڈیٹا->آخری_xconfigure.y) {
            ڈیٹا->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_Global_مقصد_Relative_For_کھڑکی(ڈیٹا->کھڑکی, x, y, &x, &y);
        SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_MOVED, x, y);

        برائے (SDL_کھڑکی *w = ڈیٹا->کھڑکی->پہلا_بچہ; w; w = w->اگلا_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            اگر (SDL_کھڑکی_IS_POPUP(w) && !(w->flags & SDL_کھڑکی_HIDDEN)) {
                X11_Update_کھڑکی_Position(w, true);
            }
        }

        اگر (xevent->چوڑائی != ڈیٹا->آخری_xconfigure.چوڑائی ||
            xevent->اونچائی != ڈیٹا->آخری_xconfigure.اونچائی) {
            ڈیٹا->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_RESIZED, xevent->چوڑائی, xevent->اونچائی);
    }

    SDL_copyp(&ڈیٹا->آخری_xconfigure, xevent);
}

ساکن خالی X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    Display *display;
    SDL_کھڑکی_ڈیٹا *ڈیٹا;
    XClient_پیغام_Event m;
    صحیح i;

    SDL_assert(videodata != تہی);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    اگر (xevent->type != کلید_Press && xevent->type != کلید_Release) {
        اگر (X11_XFilterEvent(xevent, None)) {
#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.کھڑکی);
#اگر_ختم
            واپس;
        }
    }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    اگر (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        واپس;
    }
#اگر_ختم

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    اگر (g_X11EventHook) {
        اگر (!g_X11EventHook(g_X11_Event_Hook_ڈیٹا, xevent)) {
            واپس;
        }
    }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
    اگر (videodata->xrandr_event_بنیاد && (xevent->type == (videodata->xrandr_event_بنیاد + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#اگر_ختم

#اگر_تعریف_شدہ DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.کھڑکی);
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    اگر (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#اگر_ختم

        اگر (ev->subtype == XFixes_سیٹ_Selection_Owner_Notify)
        {
            اگر (ev->selection != videodata->atoms.CLIPBOARD)
                واپس;

            اگر (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_کھڑکی)
                واپس;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, Get_کھڑکی(_this), Current_وقت);
        }

        واپس;
    }
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XFIXES

    اگر ((videodata->clipboard_کھڑکی != None) &&
        (videodata->clipboard_کھڑکی == xevent->xany.کھڑکی)) {
        X11_HandleClipboardEvent(_this, xevent);
        واپس;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    ڈیٹا = X11_ڈھونڈو_کھڑکی(videodata, xevent->xany.کھڑکی);

    اگر (!ڈیٹا) {
        // The window for KeymapNotify, etc events is 0
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        اگر (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            انتخاب (xkbevent->any.xkb_type) {
            حالت XkbStateNotify:
            {
#اگر_تعریف_شدہ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.کھڑکی);
#اگر_ختم
                اگر ((xkbevent->state.بدلا & Xkb_گروہ_State_نقاب) && xkbevent->state.گروہ != videodata->keyboard.xkb.current_گروہ) {
                    videodata->keyboard.xkb.current_گروہ = xkbevent->state.گروہ;
                    SDL_سیٹ_Keymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_گروہ], true);
                }

                اگر (xkbevent->state.بدلا & Xkb_Modifier_State_نقاب) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.بنیاد_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } توڑو;

            حالت XkbMapNotify:
#اگر_تعریف_شدہ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.کھڑکی);
                SDL_FALLTHROUGH;
#اگر_ختم
            حالت XkbNewKeyboardNotify:
            {
#اگر_تعریف_شدہ DEBUG_XEVENTS
                اگر (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.کھڑکی);
                }
#اگر_ختم
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                اگر (xkbevent->any.serial != videodata->keyboard.xkb.آخری_map_serial) {
                    videodata->keyboard.xkb.آخری_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } توڑو;

            طےشدہ:
                توڑو;
            }
        } ورنہ
#اگر_ختم
        اگر (xevent->type == KeymapNotify) {
#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.کھڑکی);
#اگر_ختم
            اگر (SDL_GetKeyboardFocus() != تہی) {
                اگر (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } ورنہ اگر (xevent->type == MappingNotify) {
            ثابت صحیح request = xevent->xmapping.request;

            اگر (request == Mapping_اشارہ_گر) {
#اگر_تعریف_شدہ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.کھڑکی);
#اگر_ختم
                X11_Xinput2_Update_اشارہ_گر_Mapping(_this);
            } ورنہ اگر (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#اگر_تعریف_شدہ DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.کھڑکی);
#اگر_ختم
                اگر (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } ورنہ اگر (xevent->type == PropertyNotify && videodata) {
            حرف *name_کا_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            اگر (name_کا_atom) {
                اگر (SDL_startswith(name_کا_atom, "_ICC_PROFILE")) {
                    XWindow_اوصاف attrib;
                    صحیح screennum;
                    برائے (i = 0; i < videodata->numwindows; ++i) {
                        اگر (videodata->windowlist[i] != تہی) {
                            ڈیٹا = videodata->windowlist[i];
                            X11_XGet_کھڑکی_اوصاف(display, ڈیٹا->xwindow, &attrib);
                            screennum = X11_XScreen_نمبر_کا_Screen(attrib.screen);
                            اگر (screennum == 0 && SDL_strcmp(name_کا_atom, "_ICC_PROFILE") == 0) {
                                SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_ICCPROF_بدلا, 0, 0);
                            } ورنہ اگر (SDL_strncmp(name_کا_atom, "_ICC_PROFILE_", حجم("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_کا_atom) > حجم("_ICC_PROFILE_") - 1) {
                                صحیح iccscreennum = SDL_atoi(&name_کا_atom[حجم("_ICC_PROFILE_") - 1]);

                                اگر (screennum == iccscreennum) {
                                    SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_ICCPROF_بدلا, 0, 0);
                                }
                            }
                        }
                    }
                } ورنہ اگر (SDL_strcmp(name_کا_atom, "_NET_WORKAREA") == 0) {
                    برائے (i = 0; i < _this->عدد_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_بدلا, 0, 0);
                    }
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
                } ورنہ اگر (SDL_strcmp(name_کا_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_کا_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#اگر_ختم
                }
                X11_XFree(name_کا_atom);
            }
        }
        واپس;
    }

    انتخاب (xevent->type) {

        // Gaining mouse coverage?
    حالت EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.کھڑکی,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.منوال);
        اگر (xevent->xcrossing.منوال == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        اگر (xevent->xcrossing.منوال == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#اگر_ختم
        SDL_سیٹ_Mouse_Focus(ڈیٹا->کھڑکی);

        mouse->آخری_x = xevent->xcrossing.x;
        mouse->آخری_y = xevent->xcrossing.y;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
        {
            // Only create the barriers if we have input focus
            SDL_کھڑکی_ڈیٹا *windowdata = ڈیٹا->کھڑکی->اندرونی_2;
            اگر ((ڈیٹا->اشارہ_گر_barrier_فعال == true) && windowdata->کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->کھڑکی, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#اگر_ختم

        اگر (!mouse->relative_منوال) {
            SDL_SendMouseMotion(0, ڈیٹا->کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)xevent->xcrossing.x, (اعشاری)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        اگر (!(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE)) {
            SDL_Update_کھڑکی_Grab(ڈیٹا->کھڑکی);
        }

        X11_Process_کامیابی_Test(_this, ڈیٹا, mouse->آخری_x, mouse->آخری_y, true);
    } توڑو;
        // Losing mouse coverage?
    حالت LeaveNotify:
    {
#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.کھڑکی,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.منوال);
        اگر (xevent->xcrossing.منوال == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        اگر (xevent->xcrossing.منوال == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#اگر_ختم
        اگر (!SDL_GetMouse()->relative_منوال) {
            SDL_SendMouseMotion(0, ڈیٹا->کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)xevent->xcrossing.x, (اعشاری)xevent->xcrossing.y);
        }

        اگر (xevent->xcrossing.منوال != NotifyGrab &&
            xevent->xcrossing.منوال != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            اگر (!(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
                X11_سیٹ_کھڑکی_Keyboard_Grab(_this, ڈیٹا->کھڑکی, false);
            }

            SDL_سیٹ_Mouse_Focus(تہی);
        }
    } توڑو;

        // Gaining input focus?
    حالت Focus_اندر:
    {
        اگر (xevent->xfocus.منوال == NotifyGrab || xevent->xfocus.منوال == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.کھڑکی);
#اگر_ختم
            توڑو;
        }

        اگر (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_اشارہ_گر) {
#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.کھڑکی);
#اگر_ختم
            توڑو;
        }
#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.کھڑکی);
#اگر_ختم
        اگر (!videodata->آخری_منوال_change_deadline) /* no recent mode changes */ {
            ڈیٹا->pending_focus = PENDING_FOCUS_NONE;
            ڈیٹا->pending_focus_وقت = 0;
            X11_Dispatch_Focus_اندر(_this, ڈیٹا);
        } ورنہ {
            ڈیٹا->pending_focus = PENDING_FOCUS_اندر;
            ڈیٹا->pending_focus_وقت = SDL_GetTicks() + PENDING_FOCUS_وقت;
        }
        ڈیٹا->آخری_focus_event_وقت = SDL_GetTicks();
    } توڑو;

        // Losing input focus?
    حالت Focus_برآمد:
    {
        اگر (xevent->xfocus.منوال == NotifyGrab || xevent->xfocus.منوال == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.کھڑکی);
#اگر_ختم
            توڑو;
        }
        اگر (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == Notify_اشارہ_گر) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.کھڑکی);
#اگر_ختم
            توڑو;
        }
#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.کھڑکی);
#اگر_ختم
        اگر (!videodata->آخری_منوال_change_deadline) /* no recent mode changes */ {
            ڈیٹا->pending_focus = PENDING_FOCUS_NONE;
            ڈیٹا->pending_focus_وقت = 0;
            X11_Dispatch_Focus_برآمد(_this, ڈیٹا);
        } ورنہ {
            ڈیٹا->pending_focus = PENDING_FOCUS_برآمد;
            ڈیٹا->pending_focus_وقت = SDL_GetTicks() + PENDING_FOCUS_وقت;
        }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        اگر (ڈیٹا->اشارہ_گر_barrier_فعال == true) {
            X11_ConfineCursorWithFlags(_this, ڈیٹا->کھڑکی, تہی, X11_BARRIER_HANDLED_BY_EVENT);
        }
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XFIXES
    } توڑو;


        // Have we been iconified?
    حالت UnmapNotify:
    {
        XEvent ev;

#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.کھڑکی);
#اگر_ختم

        اگر (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } ورنہ {
            X11_DispatchUnmapNotify(ڈیٹا);
        }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        اگر (ڈیٹا->اشارہ_گر_barrier_فعال == true) {
            X11_ConfineCursorWithFlags(_this, ڈیٹا->کھڑکی, تہی, X11_BARRIER_HANDLED_BY_EVENT);
        }
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XFIXES
    } توڑو;

        // Have we been restored?
    حالت MapNotify:
    {
#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.کھڑکی);
#اگر_ختم
        X11_DispatchMapNotify(ڈیٹا);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        اگر (ڈیٹا->اشارہ_گر_barrier_فعال == true) {
            X11_ConfineCursorWithFlags(_this, ڈیٹا->کھڑکی, &ڈیٹا->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XFIXES
    } توڑو;

        // Have we been resized or moved?
    حالت ConfigureNotify:
    {
#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.کھڑکی,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.چوڑائی, xevent->xconfigure.اونچائی);
#اگر_ختم
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        اگر (!xevent->xconfigure.send_event) {
            غیرعلامتی صحیح عدد_Children;
            کھڑکی_2 بچہ_Return, جڑ_2, والد_2;
            کھڑکی_2 *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_آخری_error = 0;
            XErrorHandler پچھلا_handler = X11_XSetErrorHandler(Bad_کھڑکی_Error_Handler);

            X11_XQuery_درخت(ڈیٹا->videodata->display, xevent->xconfigure.کھڑکی, &جڑ_2, &والد_2, &Children, &عدد_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      والد_2, Default_جڑ_کھڑکی(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &بچہ_Return);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(پچھلا_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            اگر (x11_آخری_error == Bad_کھڑکی) {
                توڑو;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        ثابت SDL_کھڑکی_Flags بدلا = X11_GetNetWMState(_this, ڈیٹا->کھڑکی, xevent->xproperty.کھڑکی) ^ ڈیٹا->کھڑکی->flags;
        اگر (بدلا & (SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_MAXIMIZED)) {
            SDL_copyp(&ڈیٹا->pending_xconfigure, &xevent->xconfigure);
            ڈیٹا->emit_سائز_move_after_property_notify = true;
        }

        اگر (!ڈیٹا->emit_سائز_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(ڈیٹا, &xevent->xconfigure);
        }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(ڈیٹا->کھڑکی, &xevent->xconfigure);
#اگر_ختم /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } توڑو;

        // Have we been requested to quit (or another client message?)
    حالت Client_پیغام:
    {
        ساکن صحیح xdnd_نسخہ = 0;

        اگر (xevent->xclient.پیغام_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.ڈیٹا.l[1] & 1;
            ڈیٹا->xdnd_ماخذ = xevent->xclient.ڈیٹا.l[0];
            xdnd_نسخہ = (xevent->xclient.ڈیٹا.l[1] >> 24);
#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", ڈیٹا->xdnd_ماخذ);
            SDL_Log("Protocol version to use : %d", xdnd_نسخہ);
            SDL_Log("More then 3 data types : %d", (صحیح)use_list);
#اگر_ختم

            اگر (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, ڈیٹا->xdnd_ماخذ, videodata->atoms.XdndTypeList);
                // pick one
                ڈیٹا->xdnd_req = X11_Pick_ہدف(display, (Atom *)p.ڈیٹا, p.گنتی);
                X11_XFree(p.ڈیٹا);
            } ورنہ {
                // pick from list of three
                ڈیٹا->xdnd_req = X11_Pick_ہدف_From_Atoms(display, xevent->xclient.ڈیٹا.l[2], xevent->xclient.ڈیٹا.l[3], xevent->xclient.ڈیٹا.l[4]);
            }
        } ورنہ اگر (xevent->xclient.پیغام_type == videodata->atoms.XdndLeave) {
#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.ڈیٹا.l[0]);
#اگر_ختم
            SDL_SendDropComplete(ڈیٹا->کھڑکی);
        } ورنہ اگر (xevent->xclient.پیغام_type == videodata->atoms.XdndPosition) {

#اگر_تعریف_شدہ DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            اگر (xdnd_نسخہ >= 2) {
                act = xevent->xclient.ڈیٹا.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#اگر_ختم
            {
                // Drag and Drop position
                صحیح جڑ_x, جڑ_y, کھڑکی_x, کھڑکی_y;
                کھڑکی_2 بچہ_Return;
                جڑ_x = xevent->xclient.ڈیٹا.l[2] >> 16;
                جڑ_y = xevent->xclient.ڈیٹا.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_جڑ_کھڑکی(display), ڈیٹا->xwindow,
                                          جڑ_x, جڑ_y, &کھڑکی_x, &کھڑکی_y, &بچہ_Return);

                SDL_SendDropPosition(ڈیٹا->کھڑکی, (اعشاری)کھڑکی_x, (اعشاری)کھڑکی_y);
            }

            // reply with status
            SDL_zero(m);
            m.type = Client_پیغام;
            m.display = xevent->xclient.display;
            m.کھڑکی = xevent->xclient.ڈیٹا.l[0];
            m.پیغام_type = videodata->atoms.Xdnd_حالت;
            m.format = 32;
            m.ڈیٹا.l[0] = ڈیٹا->xwindow;
            m.ڈیٹا.l[1] = (ڈیٹا->xdnd_req != None);
            m.ڈیٹا.l[2] = 0; // specify an empty rectangle
            m.ڈیٹا.l[3] = 0;
            m.ڈیٹا.l[4] = videodata->atoms.XdndActionCopy; // we only accept copying anyway

            X11_XSendEvent(display, xevent->xclient.ڈیٹا.l[0], False, No_Event_نقاب, (XEvent *)&m);
            X11_XFlush(display);
        } ورنہ اگر (xevent->xclient.پیغام_type == videodata->atoms.XdndDrop) {
            اگر (ڈیٹا->xdnd_req == None) {
                // say again - not interested!
                SDL_zero(m);
                m.type = Client_پیغام;
                m.display = xevent->xclient.display;
                m.کھڑکی = xevent->xclient.ڈیٹا.l[0];
                m.پیغام_type = videodata->atoms.Xdnd_ختم_شدہ;
                m.format = 32;
                m.ڈیٹا.l[0] = ڈیٹا->xwindow;
                m.ڈیٹا.l[1] = 0;
                m.ڈیٹا.l[2] = None; // fail!
                X11_XSendEvent(display, xevent->xclient.ڈیٹا.l[0], False, No_Event_نقاب, (XEvent *)&m);
            } ورنہ {
                // convert
                اگر (xdnd_نسخہ >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, ڈیٹا->xdnd_req, videodata->atoms.PRIMARY, ڈیٹا->xwindow, xevent->xclient.ڈیٹا.l[2]);
                } ورنہ {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, ڈیٹا->xdnd_req, videodata->atoms.PRIMARY, ڈیٹا->xwindow, Current_وقت);
                }
            }
        } ورنہ اگر ((xevent->xclient.پیغام_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.ڈیٹا.l[0] == videodata->atoms._NET_WM_PING)) {
            کھڑکی_2 جڑ = Default_جڑ_کھڑکی(display);

#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.کھڑکی);
#اگر_ختم
            xevent->xclient.کھڑکی = جڑ;
            X11_XSendEvent(display, جڑ, False, Substructure_Redirect_نقاب | Substructure_Notify_نقاب, xevent);
            توڑو;
        }

        ورنہ اگر ((xevent->xclient.پیغام_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.ڈیٹا.l[0] == videodata->atoms.WM_DELETE_کھڑکی)) {

#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.کھڑکی);
#اگر_ختم
            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_CLOSE_REQUESTED, 0, 0);
            توڑو;
        } ورنہ اگر ((xevent->xclient.پیغام_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.ڈیٹا.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#اگر_تعریف_شدہ DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", ڈیٹا);
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(ڈیٹا->کھڑکی, &xevent->xclient);
#اگر_ختم /* SDL_VIDEO_DRIVER_X11_XSYNC */
            توڑو;
        }
    } توڑو;

        // Do we need to refresh ourselves?
    حالت Expose:
    {
#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.کھڑکی, xevent->xexpose.گنتی);
#اگر_ختم
        SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
    } توڑو;

    /* Use XInput2 instead of the xevents API if possible, for:
       - KeyPress
       - KeyRelease
       - MotionNotify
       - ButtonPress
       - ButtonRelease
       XInput2 has more precise information, e.g., to distinguish different input devices. */
    حالت کلید_Press:
    حالت کلید_Release:
    {
        SDL_KeyboardID keyboardID = SDL_GLOBAL_KEYBOARD_ID;
        اگر (ڈیٹا->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            توڑو;
        } ورنہ اگر (xevent->xkey.serial == videodata->xinput_آخری_کلید_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_آخری_keyboard_device;
        }

        X11_Handle_کلید_Event(_this, ڈیٹا, keyboardID, xevent);
    } توڑو;

    حالت MotionNotify:
    {
        اگر (X11_Xinput2_Handles_Motion_For_کھڑکی(ڈیٹا)) {
            // This input is being handled by XInput2
            توڑو;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        اگر (!mouse->relative_منوال) {
#اگر_تعریف_شدہ DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.کھڑکی, xevent->xmotion.x, xevent->xmotion.y);
#اگر_ختم

            X11_Process_کامیابی_Test(_this, ڈیٹا, (اعشاری)xevent->xmotion.x, (اعشاری)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, ڈیٹا->کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)xevent->xmotion.x, (اعشاری)xevent->xmotion.y);
        }
    } توڑو;

    حالت ButtonPress:
    {
        اگر (ڈیٹا->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_آخری_button_serial) {
            // This input event was handled by XInput2.
            توڑو;
        }

        X11_HandleButtonPress(_this, ڈیٹا, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.وقت, xevent->xbutton.serial);
    } توڑو;

    حالت ButtonRelease:
    {
        اگر (ڈیٹا->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_آخری_button_serial) {
            // This input event was handled by XInput2.
            توڑو;
        }

        X11_HandleButtonRelease(_this, ڈیٹا, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.وقت);
    } توڑو;

    حالت PropertyNotify:
    {
#اگر_تعریف_شدہ DEBUG_XEVENTS
        غیرعلامتی حرف *propdata;
        صحیح حالت_2, real_format;
        Atom real_type;
        غیرعلامتی طویل اشیاء_read, اشیاء_بایاں;

        حرف *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        اگر (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.کھڑکی, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.وقت);
            X11_XFree(name);
        }

        حالت_2 = X11_XGet_کھڑکی_Property(display, ڈیٹا->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &اشیاء_read, &اشیاء_بایاں, &propdata);
        اگر (حالت_2 == Success && اشیاء_read > 0) {
            اگر (real_type == XA_INTEGER) {
                صحیح *اقدار = (صحیح *)propdata;

                SDL_Log("{");
                برائے (i = 0; i < اشیاء_read; i++) {
                    SDL_Log(" %d", اقدار[i]);
                }
                SDL_Log(" }");
            } ورنہ اگر (real_type == XA_CARDINAL) {
                اگر (real_format == 32) {
                    Uint32 *اقدار = (Uint32 *)propdata;

                    SDL_Log("{");
                    برائے (i = 0; i < اشیاء_read; i++) {
                        SDL_Log(" %d", اقدار[i]);
                    }
                    SDL_Log(" }");
                } ورنہ اگر (real_format == 16) {
                    Uint16 *اقدار = (Uint16 *)propdata;

                    SDL_Log("{");
                    برائے (i = 0; i < اشیاء_read; i++) {
                        SDL_Log(" %d", اقدار[i]);
                    }
                    SDL_Log(" }");
                } ورنہ اگر (real_format == 8) {
                    Uint8 *اقدار = (Uint8 *)propdata;

                    SDL_Log("{");
                    برائے (i = 0; i < اشیاء_read; i++) {
                        SDL_Log(" %d", اقدار[i]);
                    }
                    SDL_Log(" }");
                }
            } ورنہ اگر (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } ورنہ اگر (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                برائے (i = 0; i < اشیاء_read; i++) {
                    حرف *atomname = X11_XGetAtomName(display, atoms[i]);
                    اگر (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } ورنہ {
                حرف *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                اگر (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        اگر (حالت_2 == Success) {
            X11_XFree(propdata);
        }
#اگر_ختم // DEBUG_XEVENTS

        /* Take advantage of this moment to make sure user_time has a
            valid timestamp from the X server, so if we later try to
            raise/restore this window, _NET_ACTIVE_WINDOW can have a
            non-zero timestamp, even if there's never been a mouse or
            key press to this window so far. Note that we don't try to
            set _NET_WM_USER_TIME here, though. That's only for legit
            user interaction with the window. */
        اگر (!ڈیٹا->user_وقت) {
            ڈیٹا->user_وقت = xevent->xproperty.وقت;
        }

        اگر (xevent->xproperty.atom == ڈیٹا->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            ثابت SDL_کھڑکی_Flags flags = X11_GetNetWMState(_this, ڈیٹا->کھڑکی, xevent->xproperty.کھڑکی);
            ثابت SDL_کھڑکی_Flags بدلا = flags ^ ڈیٹا->کھڑکی->flags;

            اگر ((بدلا & SDL_کھڑکی_HIDDEN) && !(flags & SDL_کھڑکی_HIDDEN)) {
                X11_DispatchMapNotify(ڈیٹا);
            }

            اگر (!SDL_کھڑکی_IS_POPUP(ڈیٹا->کھڑکی)) {
                اگر (بدلا & SDL_کھڑکی_FULLSCREEN) {
                    ڈیٹا->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    اگر (flags & SDL_کھڑکی_FULLSCREEN) {
                        اگر (!(flags & SDL_کھڑکی_MINIMIZED)) {
                            ثابت bool commit = SDL_memcmp(&ڈیٹا->کھڑکی->current_fullscreen_منوال, &ڈیٹا->requested_fullscreen_منوال, حجم(SDL_Display_منوال)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
                            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_ENTER_FULLSCREEN, 0, 0);
                            اگر (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&ڈیٹا->کھڑکی->current_fullscreen_منوال, &ڈیٹا->کھڑکی->requested_fullscreen_منوال);
                                SDL_Update_Fullscreen_منوال(ڈیٹا->کھڑکی, SDL_FULLSCREEN_OP_UPDATE, true);
                            } ورنہ {
                                SDL_Update_Fullscreen_منوال(ڈیٹا->کھڑکی, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } ورنہ {
                        SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_LEAVE_FULLSCREEN, 0, 0);
                        SDL_Update_Fullscreen_منوال(ڈیٹا->کھڑکی, false, false);

                        SDL_zero(ڈیٹا->requested_fullscreen_منوال);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_سیٹ_کھڑکی_Min_Max(ڈیٹا->کھڑکی, !!(flags & SDL_کھڑکی_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        اگر (ڈیٹا->fullscreen_borders_forced_on) {
                            ڈیٹا->toggle_borders = true;
                            ڈیٹا->fullscreen_borders_forced_on = false;
                        }
                    }

                    اگر ((flags & SDL_کھڑکی_FULLSCREEN) &&
                        (ڈیٹا->border_چوٹی || ڈیٹا->border_بایاں || ڈیٹا->border_bottom || ڈیٹا->border_دایاں)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        ڈیٹا->سائز_move_event_flags |= X11_سائز_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        ڈیٹا->پچھلا_borders_nonzero = true;
                    } ورنہ اگر (!(flags & SDL_کھڑکی_FULLSCREEN) &&
                               ڈیٹا->پچھلا_borders_nonzero &&
                               (!ڈیٹا->border_چوٹی && !ڈیٹا->border_بایاں && !ڈیٹا->border_bottom && !ڈیٹا->border_دایاں)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        ڈیٹا->سائز_move_event_flags |= X11_سائز_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        ڈیٹا->پچھلا_borders_nonzero = false;
                    } ورنہ {
                        ڈیٹا->سائز_move_event_flags = 0;
                        ڈیٹا->پچھلا_borders_nonzero = false;

                        اگر (!(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && ڈیٹا->toggle_borders) {
                            ڈیٹا->toggle_borders = false;
                            X11_سیٹ_کھڑکی_Bordered(_this, ڈیٹا->کھڑکی, !(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_BORDERLESS));
                        }
                    }
                }
                اگر ((بدلا & SDL_کھڑکی_MAXIMIZED) && ((flags & SDL_کھڑکی_MAXIMIZED) && !(flags & SDL_کھڑکی_MINIMIZED))) {
                    ڈیٹا->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    اگر ((بدلا & SDL_کھڑکی_MINIMIZED)) {
                        ڈیٹا->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
                    }
                    SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_MAXIMIZED, 0, 0);
                }
                اگر ((بدلا & SDL_کھڑکی_MINIMIZED) && (flags & SDL_کھڑکی_MINIMIZED)) {
                    ڈیٹا->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
                }
                اگر (!(flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_MINIMIZED))) {
                    ڈیٹا->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    اگر (!(flags & SDL_کھڑکی_FULLSCREEN)) {
                        اگر (ڈیٹا->pending_position) {
                            ڈیٹا->pending_position = false;
                            ڈیٹا->pending_operation |= X11_PENDING_OP_MOVE;
                            ڈیٹا->expected.x = ڈیٹا->کھڑکی->pending.x - ڈیٹا->border_بایاں;
                            ڈیٹا->expected.y = ڈیٹا->کھڑکی->pending.y - ڈیٹا->border_چوٹی;
                            X11_XMove_کھڑکی(display, ڈیٹا->xwindow, ڈیٹا->expected.x, ڈیٹا->expected.y);
                        }
                        اگر (ڈیٹا->pending_سائز) {
                            ڈیٹا->pending_سائز = false;
                            ڈیٹا->pending_operation |= X11_PENDING_OP_RESIZE;
                            ڈیٹا->expected.w = ڈیٹا->کھڑکی->pending.w;
                            ڈیٹا->expected.h = ڈیٹا->کھڑکی->pending.h;
                            X11_XResize_کھڑکی(display, ڈیٹا->xwindow, ڈیٹا->کھڑکی->pending.w, ڈیٹا->کھڑکی->pending.h);
                        }
                    }
                }
                اگر (ڈیٹا->emit_سائز_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(ڈیٹا, &ڈیٹا->pending_xconfigure);
                    ڈیٹا->emit_سائز_move_after_property_notify = false;
                }
                اگر ((flags & SDL_کھڑکی_داخلہ_FOCUS)) {
                    اگر (ڈیٹا->pending_move) {
                        Dispatch_کھڑکی_Move(_this, ڈیٹا, &ڈیٹا->pending_move_نقطہ);
                        ڈیٹا->pending_move = false;
                    }
                }
            }
            اگر (بدلا & SDL_کھڑکی_OCCLUDED) {
                SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, (flags & SDL_کھڑکی_OCCLUDED) ? SDL_EVENT_کھڑکی_OCCLUDED : SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
            }
        } ورنہ اگر (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            صحیح format;
            غیرعلامتی طویل nitems, بائٹیں_after;
            غیرعلامتی حرف *prop_ڈیٹا = تہی;

            اگر (X11_XGet_کھڑکی_Property(display, ڈیٹا->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &بائٹیں_after, &prop_ڈیٹا) == Success) {
                اگر (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_ڈیٹا;

                    اگر ((state == 0 || state == 3) && !ڈیٹا->کھڑکی->is_hiding && !(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
                        // Withdrawn or Iconic
                        اگر (!(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
                            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
                            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_OCCLUDED, 0, 0);
                        }
                    } ورنہ اگر (state == 1) { // NormalState
                        اگر (ڈیٹا->کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
                            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
                            SDL_Send_کھڑکی_Event(ڈیٹا->کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_ڈیٹا);
            }
        } ورنہ اگر (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } ورنہ اگر (xevent->xproperty.atom == videodata->atoms.NET_چوکھٹا_EXTENTS) {
            X11_Get_Border_اقدار(ڈیٹا);
            اگر (ڈیٹا->سائز_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                ڈیٹا->سائز_move_event_flags &= ~X11_سائز_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            اگر (!(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && ڈیٹا->toggle_borders) {
                ڈیٹا->toggle_borders = false;
                X11_سیٹ_کھڑکی_Bordered(_this, ڈیٹا->کھڑکی, !(ڈیٹا->کھڑکی->flags & SDL_کھڑکی_BORDERLESS));
            }
        }
    } توڑو;

    حالت SelectionNotify:
    {
        Atom ہدف = xevent->xselection.ہدف;
#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.کھڑکی,
               xevent->xselection.requestor, xevent->xselection.ہدف);
#اگر_ختم
        اگر (ہدف == ڈیٹا->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, ڈیٹا->xwindow, videodata->atoms.PRIMARY);

            اگر (p.format == 8) {
                حرف *saveptr = تہی;
                حرف *name = X11_XGetAtomName(display, ہدف);
                اگر (name) {
                    حرف *token = SDL_strtok_r((حرف *)p.ڈیٹا, "\r\n", &saveptr);
                    جب (token) {
                        اگر ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_Send_Drop_متن(ڈیٹا->کھڑکی, token);
                        } ورنہ اگر (SDL_strcmp("text/uri-list", name) == 0) {
                            اگر (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(ڈیٹا->کھڑکی, تہی, token);
                            }
                        }
                        token = SDL_strtok_r(تہی, "\r\n", &saveptr);
                    }
                    X11_XFree(name);
                }
                SDL_SendDropComplete(ڈیٹا->کھڑکی);
            }
            X11_XFree(p.ڈیٹا);

            // send reply
            SDL_zero(m);
            m.type = Client_پیغام;
            m.display = display;
            m.کھڑکی = ڈیٹا->xdnd_ماخذ;
            m.پیغام_type = videodata->atoms.Xdnd_ختم_شدہ;
            m.format = 32;
            m.ڈیٹا.l[0] = ڈیٹا->xwindow;
            m.ڈیٹا.l[1] = 1;
            m.ڈیٹا.l[2] = videodata->atoms.XdndActionCopy;
            X11_XSendEvent(display, ڈیٹا->xdnd_ماخذ, False, No_Event_نقاب, (XEvent *)&m);

            X11_XSync(display, False);
        }
    } توڑو;

    طےشدہ:
    {
#اگر_تعریف_شدہ DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.کھڑکی, xevent->type);
#اگر_ختم
    } توڑو;
    }
}

ساکن خالی X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    صحیح i;

    اگر (videodata && videodata->windowlist) {
        برائے (i = 0; i < videodata->numwindows; ++i) {
            SDL_کھڑکی_ڈیٹا *ڈیٹا = videodata->windowlist[i];
            اگر (ڈیٹا && ڈیٹا->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                اگر (now >= ڈیٹا->pending_focus_وقت) {
                    اگر (ڈیٹا->pending_focus == PENDING_FOCUS_اندر) {
                        X11_Dispatch_Focus_اندر(_this, ڈیٹا);
                    } ورنہ {
                        X11_Dispatch_Focus_برآمد(_this, ڈیٹا);
                    }
                    ڈیٹا->pending_focus = PENDING_FOCUS_NONE;
                }
            }
        }
    }
}

ساکن Bool isAnyEvent(Display *display, XEvent *ev, XPointer arg)
{
    واپس True;
}

ساکن bool X11_PollEvent(Display *display, XEvent *event)
{
    اگر (!X11_XCheckIfEvent(display, event, isAnyEvent, تہی)) {
        واپس false;
    }

    واپس true;
}

خالی X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    Display *req_display = ڈیٹا->request_display;
    کھڑکی_2 xwindow = کھڑکی->اندرونی_2->xwindow;
    XClient_پیغام_Event event;

    SDL_zero(event);
    event.type = Client_پیغام;
    event.display = req_display;
    event.send_event = True;
    event.پیغام_type = ڈیٹا->atoms._SDL_WAKEUP;
    event.format = 8;

    X11_XSendEvent(req_display, xwindow, False, No_Event_نقاب, (XEvent *)&event);
    /* XSendEvent returns a status and it could be BadValue or BadWindow. If an
      error happens it is an SDL's internal error and there is nothing we can do here. */
    X11_XFlush(req_display);
}

صحیح X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    اگر (X11_PollEvent(display, &xevent)) {
        // Fall through
    } ورنہ اگر (timeoutNS == 0) {
        واپس 0;
    } ورنہ {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        صحیح err = SDL_IOReady(Connection_نمبر(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        اگر (err > 0) {
            اگر (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                واپس 1;
            }
        } ورنہ اگر (err == 0) {
            // Timeout
            واپس 0;
        } ورنہ {
            // Error returned from poll()/select()

            اگر (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                واپس 1;
            } ورنہ {
                واپس err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    واپس 1;
}

خالی X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    XEvent xevent;
    صحیح i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    برائے (i = 0; i < _this->عدد_displays; ++i) {
        اگر (_this->displays[i]->اندرونی_2->منوال_switch_deadline_ns) {
            اگر (_this->displays[i]->fullscreen_کھڑکی) {
                _this->displays[i]->اندرونی_2->منوال_switch_deadline_ns = 0;
            } ورنہ اگر (SDL_GetTicksNS() >= _this->displays[i]->اندرونی_2->منوال_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_سیٹ_Display_منوال_For_Display(_this->displays[i], تہی);
                _this->displays[i]->اندرونی_2->منوال_switch_deadline_ns = 0;
            }
        }
    }

    اگر (ڈیٹا->آخری_منوال_change_deadline) {
        اگر (SDL_GetTicks() >= ڈیٹا->آخری_منوال_change_deadline) {
            ڈیٹا->آخری_منوال_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    اگر (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        اگر (!ڈیٹا->screensaver_activity || now >= (ڈیٹا->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(ڈیٹا->display);

#اگر_تعریف_شدہ SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#اگر_ختم

            ڈیٹا->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    جب (X11_PollEvent(ڈیٹا->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    برائے (i = 0; i < ڈیٹا->numwindows; ++i) {
        اگر (ڈیٹا->windowlist[i] != تہی &&
            ڈیٹا->windowlist[i]->flash_cancel_وقت &&
            SDL_GetTicks() >= ڈیٹا->windowlist[i]->flash_cancel_وقت) {
            X11_Flash_کھڑکی(_this, ڈیٹا->windowlist[i]->کھڑکی, SDL_FLASH_CANCEL);
        }
    }

    اگر (ڈیٹا->xinput_hierarchy_بدلا) {
        X11_Xinput2UpdateDevices(_this);
        ڈیٹا->xinput_hierarchy_بدلا = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    صحیح dummy;
    صحیح major_نسخہ, minor_نسخہ;
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#اگر_تعریف_شدہ SDL_USE_LIBDBUS
    اگر (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        واپس true;
    }

    اگر (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    اگر (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        اگر (!X11_XScreenSaverQueryExtension(ڈیٹا->display, &dummy, &dummy) ||
            !X11_XScreen_Saver_Query_نسخہ(ڈیٹا->display,
                                          &major_نسخہ, &minor_نسخہ) ||
            major_نسخہ < 1 || (major_نسخہ == 1 && minor_نسخہ < 1)) {
            واپس SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(ڈیٹا->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(ڈیٹا->display);
        واپس true;
    }
#اگر_ختم
    واپس SDL_Unsupported();
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11
