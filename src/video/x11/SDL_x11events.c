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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

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

#यदि 0
#परिभाषय DEBUG_XEVENTS
#यदि_अन्तः

#यदि_अपरिभाषितम् NET_WM_MOVERESIZE_आकार_TOPLEFT
#परिभाषय NET_WM_MOVERESIZE_आकार_TOPLEFT 0
#यदि_अन्तः

#यदि_अपरिभाषितम् NET_WM_MOVERESIZE_आकार_शिखरम्
#परिभाषय NET_WM_MOVERESIZE_आकार_शिखरम् 1
#यदि_अन्तः

#यदि_अपरिभाषितम् NET_WM_MOVERESIZE_आकार_TOPRIGHT
#परिभाषय NET_WM_MOVERESIZE_आकार_TOPRIGHT 2
#यदि_अन्तः

#यदि_अपरिभाषितम् NET_WM_MOVERESIZE_आकार_दक्षिणः
#परिभाषय NET_WM_MOVERESIZE_आकार_दक्षिणः 3
#यदि_अन्तः

#यदि_अपरिभाषितम् NET_WM_MOVERESIZE_आकार_BOTTOMRIGHT
#परिभाषय NET_WM_MOVERESIZE_आकार_BOTTOMRIGHT 4
#यदि_अन्तः

#यदि_अपरिभाषितम् NET_WM_MOVERESIZE_आकार_BOTTOM
#परिभाषय NET_WM_MOVERESIZE_आकार_BOTTOM 5
#यदि_अन्तः

#यदि_अपरिभाषितम् NET_WM_MOVERESIZE_आकार_BOTTOMLEFT
#परिभाषय NET_WM_MOVERESIZE_आकार_BOTTOMLEFT 6
#यदि_अन्तः

#यदि_अपरिभाषितम् NET_WM_MOVERESIZE_आकार_वामः
#परिभाषय NET_WM_MOVERESIZE_आकार_वामः 7
#यदि_अन्तः

#यदि_अपरिभाषितम् _NET_WM_MOVERESIZE_MOVE
#परिभाषय _NET_WM_MOVERESIZE_MOVE 8
#यदि_अन्तः

प्रकारनिर्देश संरचना
{
    अचिह्नित वर्ण *दत्त;
    पूर्णाङ्क format, गणनम्;
    Atom type;
} SDL_x11Prop;

/* Reads property
   Must call X11_XFree on results
 */
स्थिर शून्य X11_ReadProperty(SDL_x11Prop *p, Display *disp, गवाक्षः_2 w, Atom prop)
{
    अचिह्नित वर्ण *ret = रिक्त;
    Atom type;
    पूर्णाङ्क fmt;
    अचिह्नित दीर्घ गणनम्;
    अचिह्नित दीर्घ अष्टकानि_वामः;
    पूर्णाङ्क अष्टकानि_fetch = 0;

    कुरु {
        यदि (ret) {
            X11_XFree(ret);
        }
        X11_XGet_गवाक्षः_Property(disp, w, prop, 0, अष्टकानि_fetch, False, AnyPropertyType, &type, &fmt, &गणनम्, &अष्टकानि_वामः, &ret);
        अष्टकानि_fetch += अष्टकानि_वामः;
    } यावत् (अष्टकानि_वामः != 0);

    p->दत्त = ret;
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
        यदि ((SDL_strcmp("text/uri-list", name) == 0) ||
            (SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
            (SDL_strcmp("UTF8_STRING", name) == 0)) {
            यदि (preferred == None) {
                preferred = list[i];
            }
            request = list[i];
        }
        // Fallback MIME targets
        यदि ((SDL_strcmp("text/plain", name) == 0) ||
            (SDL_strcmp("TEXT", name) == 0)) {
            यदि (request == None) {
                request = list[i];
            }
        }
        X11_XFree(name);
    }

    // The type 'text/uri-list' is preferred over all others.
    यदि (preferred != None && request != text_uri_request) {
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
    यदि (a0 != None) {
        atom[गणनम्++] = a0;
    }
    यदि (a1 != None) {
        atom[गणनम्++] = a1;
    }
    यदि (a2 != None) {
        atom[गणनम्++] = a2;
    }
    प्रत्यागम X11_PickTarget(disp, atom, गणनम्);
}

संरचना कुञ्चिका_Repeat_Check_दत्त
{
    XEvent *event;
    bool प्राप्तम्;
};

स्थिर Bool X11_कुञ्चिका_Repeat_Check_If_Event(Display *display, XEvent *chkev,
                                      XPointer arg)
{
    संरचना कुञ्चिका_Repeat_Check_दत्त *d = (संरचना कुञ्चिका_Repeat_Check_दत्त *)arg;
    यदि (chkev->type == कुञ्चिका_Press && chkev->xkey.keycode == d->event->xkey.keycode && chkev->xkey.time - d->event->xkey.time < 2) {
        d->प्राप्तम् = true;
    }
    प्रत्यागम False;
}

/* Check to see if this is a repeated key.
   (idea shamelessly lifted from GII -- thanks guys! :)
 */
स्थिर bool X11_कुञ्चिका_Repeat(Display *display, XEvent *event)
{
    XEvent dummyev;
    संरचना कुञ्चिका_Repeat_Check_दत्त d;
    d.event = event;
    d.प्राप्तम् = false;
    यदि (X11_XPending(display)) {
        X11_XCheckIfEvent(display, &dummyev, X11_कुञ्चिका_Repeat_Check_If_Event, (XPointer)&d);
    }
    प्रत्यागम d.प्राप्तम्;
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
स्थिर शून्य *g_X11_Event_Hook_दत्त = रिक्त;

शून्य SDL_समुच्चयः_X11_Event_Hook(SDL_X11EventHook callback, शून्य *userdata)
{
    g_X11EventHook = callback;
    g_X11_Event_Hook_दत्त = userdata;
}

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
स्थिर शून्य X11_HandleGenericEvent(SDL_VideoDevice *_this, XEvent *xev)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;

    // event is a union, so cookie == &event, but this is type safe.
    XGenericEventCookie *cookie = &xev->xcookie;
    यदि (X11_XGet_Event_दत्त(videodata->display, cookie)) {
        यदि (!g_X11EventHook || g_X11EventHook(g_X11_Event_Hook_दत्त, xev)) {
            X11_HandleXinput2Event(_this, cookie);
        }
        X11_XFree_Event_दत्त(videodata->display, cookie);
    }
}
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS

स्थिर शून्य X11_Update_System_कुञ्चिका_Modifiers(SDL_Video_दत्त *viddata)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    यदि (viddata->keyboard.xkb_enabled) {
        XkbStateRec xkb_state;
        यदि (X11_XkbGetState(viddata->display, XkbUseCoreKbd, &xkb_state) == Success) {
            viddata->keyboard.pressed_modifiers = xkb_state.आधारः_mods;
            viddata->keyboard.locked_modifiers = xkb_state.latched_mods | xkb_state.locked_mods;
        }
    } अन्यथा
#यदि_अन्तः
        {
        गवाक्षः_2 junk_गवाक्षः;
        पूर्णाङ्क x, y;
        अचिह्नित पूर्णाङ्क mod_आवरणम्;

        X11_XQueryPointer(viddata->display, Default_मूलम्_गवाक्षः(viddata->display), &junk_गवाक्षः, &junk_गवाक्षः, &x, &y, &x, &y, &mod_आवरणम्);
        viddata->keyboard.pressed_modifiers = mod_आवरणम् & (सरणम्_आवरणम्_2 | Control_आवरणम् | Mod1_आवरणम् | Mod3_आवरणम् | Mod4_आवरणम् | Mod5_आवरणम्);
        viddata->keyboard.locked_modifiers = mod_आवरणम् & (तालकम्_आवरणम् | viddata->keyboard.numlock_आवरणम् | viddata->keyboard.scrolllock_आवरणम्);
    }
}

स्थिर शून्य X11_ReconcileModifiers(SDL_Video_दत्त *viddata, bool कुञ्चिका_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, if the modifier was set to the
     * pressed state via means other than pressing the physical key, or if the
     * modifier state was set by a keypress before the corresponding key event
     * was received.
     */
    यदि (कुञ्चिका_pressed) {
        यदि (viddata->keyboard.pressed_modifiers & सरणम्_आवरणम्_2) {
            यदि (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_सरणम्) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_सरणम्;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_सरणम्);
            }
        }

        यदि (viddata->keyboard.pressed_modifiers & Control_आवरणम्) {
            यदि (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_CTRL);
            }
        }

        यदि (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_आवरणम्) {
            यदि (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_ALT);
            }
        }

        यदि (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_आवरणम्) {
            यदि (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI) {
                viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
                viddata->keyboard.sdl_pressed_modifiers |= (viddata->keyboard.sdl_physically_pressed_modifiers & SDL_KMOD_GUI);
            }
        }
    } अन्यथा {
        यदि (viddata->keyboard.pressed_modifiers & सरणम्_आवरणम्_2) {
            यदि (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_सरणम्)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_सरणम्;
            }
        } अन्यथा {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_सरणम्;
        }

        यदि (viddata->keyboard.pressed_modifiers & Control_आवरणम्) {
            यदि (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } अन्यथा {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        यदि (viddata->keyboard.pressed_modifiers & viddata->keyboard.alt_आवरणम्) {
            यदि (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_ALT;
            }
        } अन्यथा {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        यदि (viddata->keyboard.pressed_modifiers & viddata->keyboard.gui_आवरणम्) {
            यदि (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_GUI;
            }
        } अन्यथा {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        यदि (viddata->keyboard.pressed_modifiers & viddata->keyboard.level3_आवरणम्) {
            यदि (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_बहुलकम्)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_बहुलकम्;
            }
        } अन्यथा {
            viddata->keyboard.sdl_pressed_modifiers &= ~SDL_KMOD_बहुलकम्;
        }

        यदि (viddata->keyboard.pressed_modifiers & viddata->keyboard.level5_आवरणम्) {
            यदि (!(viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_LEVEL5)) {
                viddata->keyboard.sdl_pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } अन्यथा {
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
    यदि (viddata->keyboard.locked_modifiers & सरणम्_आवरणम्_2) {
        यदि (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_सरणम्) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_सरणम्;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_सरणम्);
        } अन्यथा यदि (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_सरणम्)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_सरणम्;
        }
    } अन्यथा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_सरणम्;
    }

    यदि (viddata->keyboard.locked_modifiers & Control_आवरणम्) {
        यदि (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_CTRL);
        } अन्यथा यदि (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_CTRL)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CTRL;
        }
    } अन्यथा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    यदि (viddata->keyboard.locked_modifiers & viddata->keyboard.alt_आवरणम्) {
        यदि (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_ALT);
        } अन्यथा यदि (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_ALT)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_ALT;
        }
    } अन्यथा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_ALT;
    }

    यदि (viddata->keyboard.locked_modifiers & viddata->keyboard.gui_आवरणम्) {
        यदि (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI) {
            viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
            viddata->keyboard.sdl_locked_modifiers |= (viddata->keyboard.sdl_pressed_modifiers & SDL_KMOD_GUI);
        } अन्यथा यदि (!(viddata->keyboard.sdl_locked_modifiers & SDL_KMOD_GUI)) {
            viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_GUI;
        }
    } अन्यथा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_GUI;
    }

    यदि (viddata->keyboard.locked_modifiers & viddata->keyboard.level3_आवरणम्) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_बहुलकम्;
    } अन्यथा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_बहुलकम्;
    }

    यदि (viddata->keyboard.locked_modifiers & viddata->keyboard.level5_आवरणम्) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_LEVEL5;
    } अन्यथा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock, Numlock, and Scrolllock can only be locked, not pressed.
    यदि (viddata->keyboard.locked_modifiers & तालकम्_आवरणम्) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_CAPS;
    } अन्यथा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    यदि (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_आवरणम्) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_अङ्कः;
    } अन्यथा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_अङ्कः;
    }

    यदि (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_आवरणम्) {
        viddata->keyboard.sdl_locked_modifiers |= SDL_KMOD_SCROLL;
    } अन्यथा {
        viddata->keyboard.sdl_locked_modifiers &= ~SDL_KMOD_SCROLL;
    }

    SDL_समुच्चयः_Mod_State(viddata->keyboard.sdl_pressed_modifiers | viddata->keyboard.sdl_locked_modifiers);
}

स्थिर शून्य X11_Handle_Modifier_कुञ्चिकाः(SDL_Video_दत्त *viddata, SDL_Scancode scancode, bool pressed)
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
    पक्ष SDLK_बहुलकम्:
        mod = SDL_KMOD_बहुलकम्;
        भङ्ग;
    पक्ष SDLK_LEVEL5_सरणम्:
        mod = SDL_KMOD_LEVEL5;
        भङ्ग;
    पक्ष SDLK_CAPSLOCK:
    पक्ष SDLK_NUMLOCKCLEAR:
    पक्ष SDLK_SCROLLLOCK:
    {
        // XKB provides the latched/locked state explicitly.
        यदि (viddata->keyboard.xkb_enabled) {
            /* For locking modifier keys, query the lock state directly, or we may have to wait until the next
             * key press event to know if a lock was actually activated from the key event.
             */
            अचिह्नित पूर्णाङ्क cur_आवरणम् = viddata->keyboard.locked_modifiers;
            X11_Update_System_कुञ्चिका_Modifiers(viddata);

            यदि (viddata->keyboard.locked_modifiers & तालकम्_आवरणम्) {
                cur_आवरणम् |= तालकम्_आवरणम्;
            } अन्यथा {
                cur_आवरणम् &= ~तालकम्_आवरणम्;
            }
            यदि (viddata->keyboard.locked_modifiers & viddata->keyboard.numlock_आवरणम्) {
                cur_आवरणम् |= viddata->keyboard.numlock_आवरणम्;
            } अन्यथा {
                cur_आवरणम् &= ~viddata->keyboard.numlock_आवरणम्;
            }
            यदि (viddata->keyboard.locked_modifiers & viddata->keyboard.scrolllock_आवरणम्) {
                cur_आवरणम् |= viddata->keyboard.scrolllock_आवरणम्;
            } अन्यथा {
                cur_आवरणम् &= ~viddata->keyboard.scrolllock_आवरणम्;
            }

            viddata->keyboard.locked_modifiers = cur_आवरणम्;
        }
    } भङ्ग;
    स्वभाव:
        प्रत्यागम;
    }

    यदि (pressed) {
        viddata->keyboard.sdl_pressed_modifiers |= mod;
        viddata->keyboard.sdl_physically_pressed_modifiers |= mod;
    } अन्यथा {
        viddata->keyboard.sdl_pressed_modifiers &= ~mod;
        viddata->keyboard.sdl_physically_pressed_modifiers &= ~mod;
    }

    X11_ReconcileModifiers(viddata, true);
}

शून्य X11_ReconcileKeyboardState(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
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
    videodata->keyboard.locked_modifiers &= तालकम्_आवरणम् | videodata->keyboard.numlock_आवरणम्| videodata->keyboard.scrolllock_आवरणम्;

    X11_XQueryKeymap(display, कुञ्चिकाः);

    ध्रुव bool *keystate = SDL_GetKeyboardState(रिक्त);
    प्रति (Uint32 keycode = 0; keycode < SDL_arraysize(videodata->keyboard.कुञ्चिका_layout); ++keycode) {
        ध्रुव SDL_Scancode scancode = videodata->keyboard.कुञ्चिका_layout[keycode];
        ध्रुव bool x11_कुञ्चिका_Pressed = (कुञ्चिकाः[keycode / 8] & (1 << (keycode % 8))) != 0;
        ध्रुव bool sdl_कुञ्चिका_Pressed = keystate[scancode];

        यदि (x11_कुञ्चिका_Pressed && !sdl_कुञ्चिका_Pressed) {
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
            पक्ष SDLK_बहुलकम्:
            पक्ष SDLK_LEVEL5_सरणम्:
                X11_Handle_Modifier_कुञ्चिकाः(videodata, scancode, true);
                SDL_Send_Keyboard_कुञ्चिका_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, true);
                भङ्ग;
            स्वभाव:
                भङ्ग;
            }
        } अन्यथा यदि (!x11_कुञ्चिका_Pressed && sdl_कुञ्चिका_Pressed) {
            X11_Handle_Modifier_कुञ्चिकाः(videodata, scancode, false);
            SDL_Send_Keyboard_कुञ्चिका_Ignore_Modifiers(0, SDL_GLOBAL_KEYBOARD_ID, keycode, scancode, false);
        }
    }

    // Update the latched/locked state for modifiers other than Caps, Num, and Scroll lock.
    X11_Update_System_कुञ्चिका_Modifiers(videodata);
    X11_ReconcileModifiers(videodata, true);
}

स्थिर शून्य X11_Dispatch_Focus_अन्तर्(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *दत्त)
{
#यदि_परिभाषितम् DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusIn", दत्त->xwindow);
#यदि_अन्तः
    SDL_समुच्चयः_Keyboard_Focus(दत्त->गवाक्षः);
    X11_ReconcileKeyboardState(_this);
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    यदि (दत्त->ic) {
        X11_XSetICFocus(दत्त->ic);
    }
#यदि_अन्तः
    यदि (दत्त->flashing_गवाक्षः) {
        X11_Flash_गवाक्षः(_this, दत्त->गवाक्षः, SDL_FLASH_CANCEL);
    }
}

स्थिर शून्य X11_Dispatch_Focus_बहिर्गमनम्(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *दत्त)
{
#यदि_परिभाषितम् DEBUG_XEVENTS
    SDL_Log("window 0x%lx: Dispatching FocusOut", दत्त->xwindow);
#यदि_अन्तः
    /* If another window has already processed a focus in, then don't try to
     * remove focus here.  Doing so will incorrectly remove focus from that
     * window, and the focus lost event for this window will have already
     * been dispatched anyway. */
    यदि (दत्त->गवाक्षः == SDL_GetKeyboardFocus()) {
        SDL_समुच्चयः_Keyboard_Focus(रिक्त);
    }
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    यदि (दत्त->ic) {
        X11_XUnsetICFocus(दत्त->ic);
    }
#यदि_अन्तः
}

स्थिर शून्य X11_DispatchMapNotify(SDL_गवाक्षः_दत्त *दत्त)
{
    SDL_गवाक्षः *गवाक्षः = दत्त->गवाक्षः;

    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_SHOWN, 0, 0);
    दत्त->was_shown = true;

    // This may be sent when restoring a minimized window.
    यदि (गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED) {
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESTORED, 0, 0);
        SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_EXPOSED, 0, 0);
    }

    यदि (गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS) {
        SDL_Update_गवाक्षः_Grab(गवाक्षः);
    }
}

स्थिर शून्य X11_DispatchUnmapNotify(SDL_गवाक्षः_दत्त *दत्त)
{
    SDL_गवाक्षः *गवाक्षः = दत्त->गवाक्षः;

    // This may be sent when minimizing a window.
    यदि (!गवाक्षः->is_hiding) {
        SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_MINIMIZED, 0, 0);
        SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_OCCLUDED, 0, 0);
    } अन्यथा {
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_HIDDEN, 0, 0);
    }
}

स्थिर शून्य Dispatch_गवाक्षः_Move(SDL_VideoDevice *_this, ध्रुव SDL_गवाक्षः_दत्त *दत्त, ध्रुव SDL_Point *point)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    SDL_गवाक्षः *गवाक्षः = दत्त->गवाक्षः;
    Display *display = videodata->display;
    XEvent evt;

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrabPointer(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_सन्देशः;
    evt.xclient.गवाक्षः = दत्त->xwindow;
    evt.xclient.सन्देशः_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.दत्त.l[0] = (size_t)गवाक्षः->x + point->x;
    evt.xclient.दत्त.l[1] = (size_t)गवाक्षः->y + point->y;
    evt.xclient.दत्त.l[2] = _NET_WM_MOVERESIZE_MOVE;
    evt.xclient.दत्त.l[3] = Button1;
    evt.xclient.दत्त.l[4] = 0;
    X11_XSendEvent(display, Default_मूलम्_गवाक्षः(display), False, Substructure_Redirect_आवरणम् | Substructure_Notify_आवरणम्, &evt);

    X11_XSync(display, 0);
}

स्थिर शून्य कालसारणी_गवाक्षः_Move(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *दत्त, ध्रुव SDL_Point *point)
{
    दत्त->pending_move = true;
    दत्त->pending_move_point = *point;
}

स्थिर शून्य Initiate_गवाक्षः_Resize(SDL_VideoDevice *_this, ध्रुव SDL_गवाक्षः_दत्त *दत्त, ध्रुव SDL_Point *point, पूर्णाङ्क direction)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    SDL_गवाक्षः *गवाक्षः = दत्त->गवाक्षः;
    Display *display = videodata->display;
    XEvent evt;

    यदि (direction < NET_WM_MOVERESIZE_आकार_TOPLEFT || direction > NET_WM_MOVERESIZE_आकार_वामः) {
        प्रत्यागम;
    }

    // !!! FIXME: we need to regrab this if necessary when the drag is done.
    X11_XUngrabPointer(display, 0L);
    X11_XFlush(display);

    evt.xclient.type = Client_सन्देशः;
    evt.xclient.गवाक्षः = दत्त->xwindow;
    evt.xclient.सन्देशः_type = videodata->atoms._NET_WM_MOVERESIZE;
    evt.xclient.format = 32;
    evt.xclient.दत्त.l[0] = (size_t)गवाक्षः->x + point->x;
    evt.xclient.दत्त.l[1] = (size_t)गवाक्षः->y + point->y;
    evt.xclient.दत्त.l[2] = direction;
    evt.xclient.दत्त.l[3] = Button1;
    evt.xclient.दत्त.l[4] = 0;
    X11_XSendEvent(display, Default_मूलम्_गवाक्षः(display), False, Substructure_Redirect_आवरणम् | Substructure_Notify_आवरणम्, &evt);

    X11_XSync(display, 0);
}

bool X11_Process_लब्धम्_Test(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *दत्त, ध्रुव भिन्न x, ध्रुव भिन्न y, bool force_new_परिणाम)
{
    SDL_गवाक्षः *गवाक्षः = दत्त->गवाक्षः;
    यदि (!गवाक्षः->लब्धम्_test) प्रत्यागम false;
    ध्रुव SDL_Point point = { (पूर्णाङ्क)x, (पूर्णाङ्क)y };
    SDL_लब्धम्_Test_परिणाम rc = गवाक्षः->लब्धम्_test(गवाक्षः, &point, गवाक्षः->लब्धम्_test_दत्त);
    यदि (!force_new_परिणाम && rc == दत्त->लब्धम्_test_परिणाम) {
        प्रत्यागम true;
    }
    X11_समुच्चयः_लब्धम्_Test_Cursor(rc);
    दत्त->लब्धम्_test_परिणाम = rc;
    प्रत्यागम true;
}

bool X11_Trigger_लब्धम्_Test_Action(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *दत्त, ध्रुव भिन्न x, ध्रुव भिन्न y)
{
    SDL_गवाक्षः *गवाक्षः = दत्त->गवाक्षः;

    यदि (गवाक्षः->लब्धम्_test) {
        ध्रुव SDL_Point point = { (पूर्णाङ्क)x, (पूर्णाङ्क)y };
        स्थिर ध्रुव पूर्णाङ्क directions[] = {
            NET_WM_MOVERESIZE_आकार_TOPLEFT, NET_WM_MOVERESIZE_आकार_शिखरम्,
            NET_WM_MOVERESIZE_आकार_TOPRIGHT, NET_WM_MOVERESIZE_आकार_दक्षिणः,
            NET_WM_MOVERESIZE_आकार_BOTTOMRIGHT, NET_WM_MOVERESIZE_आकार_BOTTOM,
            NET_WM_MOVERESIZE_आकार_BOTTOMLEFT, NET_WM_MOVERESIZE_आकार_वामः
        };

        विकल्प (दत्त->लब्धम्_test_परिणाम) {
        पक्ष SDL_HITTEST_DRAGGABLE:
            /* Some window managers get in a bad state when a move event starts while input is transitioning
               to the SDL window. This can happen when clicking on a drag region of an unfocused window
               where the same mouse down event will trigger a drag event and a window activate. */
            यदि (दत्त->गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS) {
                Dispatch_गवाक्षः_Move(_this, दत्त, &point);
            } अन्यथा {
                कालसारणी_गवाक्षः_Move(_this, दत्त, &point);
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
            Initiate_गवाक्षः_Resize(_this, दत्त, &point, directions[दत्त->लब्धम्_test_परिणाम - SDL_HITTEST_RESIZE_TOPLEFT]);
            प्रत्यागम true;

        स्वभाव:
            प्रत्यागम false;
        }
    }

    प्रत्यागम false;
}

स्थिर शून्य X11_UpdateUserTime(SDL_गवाक्षः_दत्त *दत्त, ध्रुव अचिह्नित दीर्घ latest)
{
    यदि (latest && (latest != दत्त->user_time)) {
        SDL_Video_दत्त *videodata = दत्त->videodata;
        Display *display = videodata->display;
        X11_XChangeProperty(display, दत्त->xwindow, videodata->atoms._NET_WM_USER_TIME,
                            XA_CARDINAL, 32, Prop_बहुलकम्_Replace,
                            (ध्रुव अचिह्नित वर्ण *)&latest, 1);
#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window 0x%lx: updating _NET_WM_USER_TIME to %lu", दत्त->xwindow, latest);
#यदि_अन्तः
        दत्त->user_time = latest;
    }
}

स्थिर अचिह्नित वर्ण x11_चरमः_error;
स्थिर पूर्णाङ्क Bad_गवाक्षः_Error_Handler(Display *d, XErrorEvent *e)
{
    x11_चरमः_error = e->error_संहिता;

    // Ignore BadWindow in cases where it's not fatal.
    यदि (e->error_संहिता != Bad_गवाक्षः) {
        वर्ण err_सन्देशः[128];
        X11_XGetErrorText(d, e->error_संहिता, err_सन्देशः, परिमाण(err_सन्देशः));
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "X failed request: %hhu (%s), major opcode: %hhu", e->error_संहिता, err_सन्देशः, e->request_संहिता);
    }
    प्रत्यागम 0;
}

स्थिर शून्य X11_HandleClipboardEvent(SDL_VideoDevice *_this, ध्रुव XEvent *xevent)
{
    पूर्णाङ्क i;
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    Display *display = videodata->display;

    SDL_assert(videodata->clipboard_गवाक्षः != None);
    SDL_assert(xevent->xany.गवाक्षः == videodata->clipboard_गवाक्षः);

    विकल्प (xevent->type) {
        // Copy the selection from our own CUTBUFFER to the requested property
    पक्ष SelectionRequest:
    {
        ध्रुव XSelectionRequestEvent *req = &xevent->xselectionrequest;
        XEvent sevent;
        पूर्णाङ्क mime_formats;
        अचिह्नित वर्ण *seln_दत्त;
        size_t seln_दीर्घता = 0;
        Atom XA_TARGETS = videodata->atoms.TARGETS;
        SDLX11_Clipboard_दत्त *clipboard;

#यदि_परिभाषितम् DEBUG_XEVENTS
        वर्ण *atom_name;
        atom_name = X11_XGetAtomName(display, req->target);
        SDL_Log("window CLIPBOARD: SelectionRequest (requestor = 0x%lx, target = 0x%lx, mime_type = %s)",
               req->requestor, req->target, atom_name);
        यदि (atom_name) {
            X11_XFree(atom_name);
        }
#यदि_अन्तः

        /* If the requesting window was already destroyed, XChangeProperty can generate a BadWindow
         * error. Register an error handler to catch this, and prevent it from being fatal.
         */
        x11_चरमः_error = 0;
        XErrorHandler पूर्व_handler = X11_XSetErrorHandler(Bad_गवाक्षः_Error_Handler);

        यदि (req->selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } अन्यथा {
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

        यदि (req->target == XA_TARGETS) {
            Atom *supportedFormats;
            supportedFormats = SDL_malloc((clipboard->mime_गणनम् + 1) * परिमाण(Atom));
            supportedFormats[0] = XA_TARGETS;
            mime_formats = 1;
            प्रति (i = 0; i < clipboard->mime_गणनम्; ++i) {
                supportedFormats[mime_formats++] = X11_XInternAtom(display, clipboard->mime_types[i], False);
            }
            X11_XChangeProperty(display, req->requestor, req->property,
                                XA_ATOM, 32, Prop_बहुलकम्_Replace,
                                (अचिह्नित वर्ण *)supportedFormats,
                                mime_formats);
            sevent.xselection.property = req->property;
            sevent.xselection.target = XA_TARGETS;
            SDL_free(supportedFormats);
        } अन्यथा {
            यदि (clipboard->callback) {
                प्रति (i = 0; i < clipboard->mime_गणनम्; ++i) {
                    ध्रुव वर्ण *mime_type = clipboard->mime_types[i];
                    यदि (X11_XInternAtom(display, mime_type, False) != req->target) {
                        अनुवर्त;
                    }

                    // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do.
                    // This is a safe cast, XChangeProperty() doesn't take a const value, but it doesn't modify the data
                    seln_दत्त = (अचिह्नित वर्ण *)clipboard->callback(clipboard->userdata, mime_type, &seln_दीर्घता);
                    यदि (seln_दत्त) {
                        X11_XChangeProperty(display, req->requestor, req->property,
                                            req->target, 8, Prop_बहुलकम्_Replace,
                                            seln_दत्त, seln_दीर्घता);
                        sevent.xselection.property = req->property;
                        sevent.xselection.target = req->target;
                    }
                    भङ्ग;
                }
            }
        }
        X11_XSendEvent(display, req->requestor, False, 0, &sevent);
        X11_XSync(display, False);

        X11_XSetErrorHandler(पूर्व_handler);
    } भङ्ग;

    पक्ष SelectionNotify:
    {
        ध्रुव XSelectionEvent *xsel = &xevent->xselection;
#यदि_परिभाषितम् DEBUG_XEVENTS
        ध्रुव वर्ण *propName = xsel->property ? X11_XGetAtomName(display, xsel->property) : "None";
        ध्रुव वर्ण *targetName = xsel->target ? X11_XGetAtomName(display, xsel->target) : "None";

        SDL_Log("window CLIPBOARD: SelectionNotify (requestor = 0x%lx, target = %s, property = %s)",
               xsel->requestor, targetName, propName);
#यदि_अन्तः
        यदि (xsel->target == videodata->atoms.TARGETS && xsel->property == videodata->atoms.SDL_FORMATS) {
            /* the new mime formats are the SDL_FORMATS property as an array of Atoms */
            Atom atom = None;
            Atom *patom;
            अचिह्नित वर्ण *दत्त = रिक्त;
            पूर्णाङ्क format_property = 0;
            अचिह्नित दीर्घ दीर्घता = 0;
            अचिह्नित दीर्घ अष्टकानि_वामः = 0;
            पूर्णाङ्क j;

            X11_XGet_गवाक्षः_Property(display, Get_गवाक्षः(_this), videodata->atoms.SDL_FORMATS, 0, 200,
                                            0, XA_ATOM, &atom, &format_property, &दीर्घता, &अष्टकानि_वामः, &दत्त);

            पूर्णाङ्क allocationsize = (दीर्घता + 1) * परिमाण(वर्ण *);
            प्रति (j = 0, patom = (Atom *)दत्त; j < दीर्घता; j++, patom++) {
                वर्ण *atomStr = X11_XGetAtomName(display, *patom);
                allocationsize += SDL_strlen(atomStr) + 1;
                X11_XFree(atomStr);
            }

            वर्ण **new_mime_types = SDL_Allocate_Temporary_स्मृतिः(allocationsize);
            यदि (new_mime_types) {
                वर्ण *strPtr = (वर्ण *)(new_mime_types + दीर्घता + 1);
                allocationsize -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

                प्रति (j = 0, patom = (Atom *)दत्त; j < दीर्घता; j++, patom++) {
                    वर्ण *atomStr = X11_XGetAtomName(display, *patom);
                    new_mime_types[j] = strPtr;
                    ध्रुव size_t len = SDL_strlcpy(strPtr, atomStr, allocationsize) + 1;
                    strPtr += len;
                    allocationsize -= len;
                    X11_XFree(atomStr);
                }
                new_mime_types[दीर्घता] = रिक्त;

                SDL_SendClipboardUpdate(false, new_mime_types, दीर्घता);

                // Clear the internal selection source data, as it was invalided after updating the clipboard.
                SDL_zero(videodata->clipboard);
            }

            यदि (दत्त) {
                X11_XFree(दत्त);
            }
        }

        videodata->selection_प्रतीक्षा = false;
    } भङ्ग;

    पक्ष SelectionClear:
    {
        Atom XA_CLIPBOARD = videodata->atoms.CLIPBOARD;
        SDLX11_Clipboard_दत्त *clipboard = रिक्त;

#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: SelectionClear (requestor = 0x%lx, target = 0x%lx)",
               xevent->xselection.requestor, xevent->xselection.target);
#यदि_अन्तः

        यदि (xevent->xselectionclear.selection == XA_PRIMARY) {
            clipboard = &videodata->primary_selection;
        } अन्यथा यदि (XA_CLIPBOARD != None && xevent->xselectionclear.selection == XA_CLIPBOARD) {
            clipboard = &videodata->clipboard;
        }
        यदि (clipboard && clipboard->callback) {
            यदि (clipboard->sequence) {
                SDL_Cancel_Clipboard_दत्त(clipboard->sequence);
            } अन्यथा {
                SDL_free(clipboard->userdata);
            }
            SDL_zerop(clipboard);
        }
    } भङ्ग;

    पक्ष PropertyNotify:
    {
        वर्ण *name_सम्बन्धि_atom = X11_XGetAtomName(display, xevent->xproperty.atom);

        यदि (SDL_strncmp(name_सम्बन्धि_atom, "SDL_SELECTION", परिमाण("SDL_SELECTION") - 1) == 0 && xevent->xproperty.state == Property_New_मानम्) {
            videodata->selection_incr_प्रतीक्षा = false;
        }

        यदि (name_सम्बन्धि_atom) {
            X11_XFree(name_सम्बन्धि_atom);
        }
    } भङ्ग;
    }
}

स्थिर Bool isMapNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    प्रत्यागम ev->type == MapNotify &&
           ev->xmap.गवाक्षः == unmap->गवाक्षः &&
           ev->xmap.serial == unmap->serial;
}

स्थिर Bool isReparentNotify(Display *display, XEvent *ev, XPointer arg)
{
    XUnmapEvent *unmap;

    unmap = (XUnmapEvent *)arg;

    प्रत्यागम ev->type == ReparentNotify &&
           ev->xreparent.गवाक्षः == unmap->गवाक्षः &&
           ev->xreparent.serial == unmap->serial;
}

स्थिर bool Is_उच्चः_Latin1(ध्रुव वर्ण *string, पूर्णाङ्क दीर्घता)
{
    यावत् (दीर्घता-- > 0) {
        Uint8 ch = (Uint8)*string;
        यदि (ch >= 0x80) {
            प्रत्यागम true;
        }
        ++string;
    }
    प्रत्यागम false;
}

स्थिर पूर्णाङ्क XLookupStringAsUTF8(XKeyEvent *event_struct, वर्ण *बफर_return, पूर्णाङ्क अष्टकानि_बफर, कुञ्चिका_Sym *keysym_return, XCompose_स्थितिः *स्थितिः_अन्तर्_बहिर्गमनम्)
{
    पूर्णाङ्क परिणाम = X11_XLookupString(event_struct, बफर_return, अष्टकानि_बफर, keysym_return, स्थितिः_अन्तर्_बहिर्गमनम्);
    यदि (Is_उच्चः_Latin1(बफर_return, परिणाम)) {
        वर्ण *utf8_text = SDL_iconv_string("UTF-8", "ISO-8859-1", बफर_return, परिणाम + 1);
        यदि (utf8_text) {
            SDL_strlcpy(बफर_return, utf8_text, अष्टकानि_बफर);
            SDL_free(utf8_text);
            प्रत्यागम SDL_strlen(बफर_return);
        } अन्यथा {
            प्रत्यागम 0;
        }
    }
    प्रत्यागम परिणाम;
}

SDL_गवाक्षः_दत्त *X11_Find_गवाक्षः(SDL_Video_दत्त *videodata, गवाक्षः_2 गवाक्षः)
{
    यदि (videodata && videodata->windowlist) {
        प्रति (पूर्णाङ्क i = 0; i < videodata->numwindows; ++i) {
            यदि ((videodata->windowlist[i] != रिक्त) &&
                (videodata->windowlist[i]->xwindow == गवाक्षः)) {
                प्रत्यागम videodata->windowlist[i];
            }
        }
    }
    प्रत्यागम रिक्त;
}

Uint64 X11_GetEventTimestamp(अचिह्नित दीर्घ time)
{
    // FIXME: Get the event time in the SDL tick time base
    प्रत्यागम SDL_GetTicksNS();
}

शून्य X11_Handle_कुञ्चिका_Event(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    Display *display = videodata->display;
    कुञ्चिका_संहिता_2 keycode = xevent->xkey.keycode;
    कुञ्चिका_Sym keysym = No_चिह्नम्;
    पूर्णाङ्क text_दीर्घता = 0;
    वर्ण text[64];
    स्थितिः_2 स्थितिः = 0;
    bool handled_by_ime = false;
    bool pressed = (xevent->type == कुञ्चिका_Press);
    SDL_Scancode scancode = videodata->keyboard.कुञ्चिका_layout[keycode];
    Uint64 timestamp = X11_GetEventTimestamp(xevent->xkey.time);

#यदि_परिभाषितम् DEBUG_XEVENTS
    SDL_Log("window 0x%lx %s (X11 keycode = 0x%X)", xevent->xany.गवाक्षः, (xevent->type == कुञ्चिका_Press ? "KeyPress" : "KeyRelease"), xevent->xkey.keycode);
#यदि_अन्तः
#यदि_परिभाषितम् DEBUG_SCANCODES
    यदि (scancode == SDL_SCANCODE_UNKNOWN && keycode) {
        पूर्णाङ्क min_keycode, max_keycode;
        X11_XDisplayKeycodes(display, &min_keycode, &max_keycode);
        keysym = X11_कुञ्चिका_संहिता_गन्तव्यम्_Sym(_this, keycode, xevent->xkey.state >> 13);
        SDL_Log("The key you just pressed is not recognized by SDL. To help get this fixed, please report this to the SDL forums/mailing list <https://discourse.libsdl.org/> X11 KeyCode %d (%d), X11 KeySym 0x%lX (%s).",
                keycode, keycode - min_keycode, keysym,
                X11_XKeysym_गन्तव्यम्_String(keysym));
    }
#यदि_अन्तः // DEBUG SCANCODES

    text[0] = '\0';

    // XKB updates the modifiers explicitly via a state event.
    यदि (!videodata->keyboard.xkb_enabled) {
        videodata->keyboard.pressed_modifiers = xevent->xkey.state & (सरणम्_आवरणम्_2 | Control_आवरणम् | Mod1_आवरणम् | Mod3_आवरणम् | Mod4_आवरणम् | Mod5_आवरणम्);
        videodata->keyboard.locked_modifiers = xevent->xkey.state & (तालकम्_आवरणम् | videodata->keyboard.numlock_आवरणम् | videodata->keyboard.scrolllock_आवरणम्);
    }

    यदि (SDL_Text_निवेशः_सक्रिय(windowdata->गवाक्षः)) {
        // filter events catches XIM events and sends them to the correct handler
        यदि (X11_XFilterEvent(xevent, None)) {
#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.गवाक्षः);
#यदि_अन्तः
            handled_by_ime = true;
        }

        यदि (!handled_by_ime) {
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
            यदि (windowdata->ic && xevent->type == कुञ्चिका_Press) {
                text_दीर्घता = X11_Xutf8LookupString(windowdata->ic, &xevent->xkey, text, परिमाण(text) - 1,
                                      &keysym, &स्थितिः);
            } अन्यथा {
                text_दीर्घता = XLookupStringAsUTF8(&xevent->xkey, text, परिमाण(text) - 1, &keysym, रिक्त);
            }
#अन्यथा
            text_दीर्घता = XLookupStringAsUTF8(&xevent->xkey, text, परिमाण(text) - 1, &keysym, रिक्त);
#यदि_अन्तः
        }
    }

    यदि (!handled_by_ime) {
        यदि (pressed) {
            X11_Handle_Modifier_कुञ्चिकाः(videodata, scancode, true);
            SDL_Send_Keyboard_कुञ्चिका_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, true);

            यदि (*text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                text[text_दीर्घता] = '\0';
                X11_ClearComposition(windowdata);
                SDL_SendKeyboardText(text);
            }
        } अन्यथा {
            यदि (X11_कुञ्चिका_Repeat(display, xevent)) {
                // We're about to get a repeated key down, ignore the key up
                प्रत्यागम;
            }

            X11_Handle_Modifier_कुञ्चिकाः(videodata, scancode, false);
            SDL_Send_Keyboard_कुञ्चिका_Ignore_Modifiers(timestamp, keyboardID, keycode, scancode, false);
        }
    }

    यदि (pressed) {
        X11_UpdateUserTime(windowdata, xevent->xkey.time);
    }
}

शून्य X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *windowdata, SDL_MouseID mouseID, पूर्णाङ्क button, भिन्न x, भिन्न y, अचिह्नित दीर्घ time, अचिह्नित दीर्घ serial)
{
    SDL_गवाक्षः *गवाक्षः = windowdata->गवाक्षः;
    पूर्णाङ्क xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#यदि_परिभाषितम् DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonPress (X11 button = %d)", windowdata->xwindow, button);
#यदि_अन्तः

    SDL_Mouse *mouse = SDL_GetMouse();
    यदि (!mouse->relative_बहुलकम् && (x != mouse->x || y != mouse->y)) {
        X11_Process_लब्धम्_Test(_this, windowdata, x, y, false);
        SDL_SendMouseMotion(timestamp, गवाक्षः, mouseID, false, x, y);
    }

    यदि (X11_IsWheelEvent(button, &xticks, &yticks)) {
        SDL_SendMouseWheel(timestamp, गवाक्षः, mouseID, (भिन्न)-xticks, (भिन्न)yticks, SDL_MOUSEWHEEL_प्रसामान्यम्);
    } अन्यथा {
        यदि (button > 7) {
            /* X button values 4-7 are used for scrolling, so X1 is 8, X2 is 9, ...
               => subtract (8-SDL_BUTTON_X1) to get value SDL expects */
            button -= (8 - SDL_BUTTON_X1);
        }
        यदि (button == Button1) {
            यदि (X11_Trigger_लब्धम्_Test_Action(_this, windowdata, x, y)) {
                SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_लब्धम्_TEST, 0, 0);
                प्रत्यागम; // don't pass this event on to app.
            }
        }
        यदि (windowdata->चरमः_focus_event_time) {
            ध्रुव पूर्णाङ्क X11_FOCUS_CLICK_TIMEOUT = 10;
            यदि (SDL_GetTicks() < (windowdata->चरमः_focus_event_time + X11_FOCUS_CLICK_TIMEOUT)) {
                यदि (!SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false)) {
                    // Ignore all press events with this serial.
                    windowdata->ignore_button_press_serial = serial;
                }
            }
            windowdata->चरमः_focus_event_time = 0;
        }
        यदि (serial != windowdata->ignore_button_press_serial) {
            SDL_SendMouseButton(timestamp, गवाक्षः, mouseID, button, true);
        }
    }
    X11_UpdateUserTime(windowdata, time);
}

शून्य X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *windowdata, SDL_MouseID mouseID, पूर्णाङ्क button, अचिह्नित दीर्घ time)
{
    SDL_गवाक्षः *गवाक्षः = windowdata->गवाक्षः;
    // The X server sends a Release event for each Press for wheels. Ignore them.
    पूर्णाङ्क xticks = 0, yticks = 0;
    Uint64 timestamp = X11_GetEventTimestamp(time);

#यदि_परिभाषितम् DEBUG_XEVENTS
    SDL_Log("window 0x%lx: ButtonRelease (X11 button = %d)", windowdata->xwindow, button);
#यदि_अन्तः
    यदि (!X11_IsWheelEvent(button, &xticks, &yticks)) {
        यदि (button > 7) {
            // see explanation at case ButtonPress
            button -= (8 - SDL_BUTTON_X1);
        }
        SDL_SendMouseButton(timestamp, गवाक्षः, mouseID, button, false);

        यदि (गवाक्षः->आन्तरिकम्->pending_grab) {
            X11_समुच्चयः_गवाक्षः_Mouse_Grab(_this, गवाक्षः, true);
        }
    }
}

शून्य X11_Get_Border_मानानि(SDL_गवाक्षः_दत्त *दत्त)
{
    SDL_Video_दत्त *videodata = दत्त->videodata;
    Display *display = videodata->display;

    Atom type;
    पूर्णाङ्क format;
    अचिह्नित दीर्घ nitems, अष्टकानि_after;
    अचिह्नित वर्ण *property;

    // Some compositors will send extents even when the border hint is turned off. Ignore them in this case.
    यदि (!(दत्त->गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS)) {
        यदि (X11_XGet_गवाक्षः_Property(display, दत्त->xwindow, videodata->atoms._NET_FRAME_EXTENTS, 0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &अष्टकानि_after, &property) == Success) {
            यदि (type != None && nitems == 4) {
                दत्त->border_वामः = (पूर्णाङ्क)((दीर्घ *)property)[0];
                दत्त->border_दक्षिणः = (पूर्णाङ्क)((दीर्घ *)property)[1];
                दत्त->border_शिखरम् = (पूर्णाङ्क)((दीर्घ *)property)[2];
                दत्त->border_bottom = (पूर्णाङ्क)((दीर्घ *)property)[3];
            }
            X11_XFree(property);

#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("New _NET_FRAME_EXTENTS: left=%d right=%d, top=%d, bottom=%d", दत्त->border_वामः, दत्त->border_दक्षिणः, दत्त->border_शिखरम्, दत्त->border_bottom);
#यदि_अन्तः
        }
    } अन्यथा {
        दत्त->border_वामः = दत्त->border_शिखरम् = दत्त->border_दक्षिणः = दत्त->border_bottom = 0;
    }
}

शून्य X11_EmitConfigureNotifyEvents(SDL_गवाक्षः_दत्त *दत्त, XConfigureEvent *xevent)
{
    यदि (!दत्त->आकार_move_event_flags) {
        पूर्णाङ्क x = xevent->x;
        पूर्णाङ्क y = xevent->y;

        यदि (xevent->x != दत्त->चरमः_xconfigure.x ||
            xevent->y != दत्त->चरमः_xconfigure.y) {
            दत्त->pending_operation &= ~X11_PENDING_OP_MOVE;
        }
        SDL_Global_गन्तव्यम्_Relative_For_गवाक्षः(दत्त->गवाक्षः, x, y, &x, &y);
        SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_MOVED, x, y);

        प्रति (SDL_गवाक्षः *w = दत्त->गवाक्षः->first_child; w; w = w->अग्र_sibling) {
            // Don't update hidden child popup windows, their relative position doesn't change
            यदि (SDL_गवाक्षः_IS_POPUP(w) && !(w->flags & SDL_गवाक्षः_HIDDEN)) {
                X11_Update_गवाक्षः_Position(w, true);
            }
        }

        यदि (xevent->विस्तारः != दत्त->चरमः_xconfigure.विस्तारः ||
            xevent->height != दत्त->चरमः_xconfigure.height) {
            दत्त->pending_operation &= ~X11_PENDING_OP_RESIZE;
        }
        SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, xevent->विस्तारः, xevent->height);
    }

    SDL_copyp(&दत्त->चरमः_xconfigure, xevent);
}

स्थिर शून्य X11_DispatchEvent(SDL_VideoDevice *_this, XEvent *xevent)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    Display *display;
    SDL_गवाक्षः_दत्त *दत्त;
    XClient_सन्देशः_Event m;
    पूर्णाङ्क i;

    SDL_assert(videodata != रिक्त);
    display = videodata->display;

    // filter events catches XIM events and sends them to the correct handler
    // Key press/release events are filtered in X11_HandleKeyEvent()
    यदि (xevent->type != कुञ्चिका_Press && xevent->type != कुञ्चिका_Release) {
        यदि (X11_XFilterEvent(xevent, None)) {
#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("Filtered event type = %d display = %p window = 0x%lx",
                   xevent->type, xevent->xany.display, xevent->xany.गवाक्षः);
#यदि_अन्तः
            प्रत्यागम;
        }
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
    यदि (xevent->type == GenericEvent) {
        X11_HandleGenericEvent(_this, xevent);
        प्रत्यागम;
    }
#यदि_अन्तः

    // Calling the event hook for generic events happens in X11_HandleGenericEvent(), where the event data is available
    यदि (g_X11EventHook) {
        यदि (!g_X11EventHook(g_X11_Event_Hook_दत्त, xevent)) {
            प्रत्यागम;
        }
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
    यदि (videodata->xrandr_event_आधारः && (xevent->type == (videodata->xrandr_event_आधारः + RRNotify))) {
        X11_HandleXRandREvent(_this, xevent);
    }
#यदि_अन्तः

#यदि_परिभाषितम् DEBUG_XEVENTS
    SDL_Log("X11 event type = %d display = %p window = 0x%lx",
           xevent->type, xevent->xany.display, xevent->xany.गवाक्षः);
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
    यदि (SDL_X11_HAVE_XFIXES &&
        xevent->type == X11_GetXFixesSelectionNotifyEvent()) {
        XFixesSelectionNotifyEvent *ev = (XFixesSelectionNotifyEvent *)xevent;

#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window CLIPBOARD: XFixesSelectionNotify (selection = %s)",
               X11_XGetAtomName(display, ev->selection));
#यदि_अन्तः

        यदि (ev->subtype == XFixes_समुच्चयः_Selection_Owner_Notify)
        {
            यदि (ev->selection != videodata->atoms.CLIPBOARD)
                प्रत्यागम;

            यदि (X11_XGetSelectionOwner(display, ev->selection) == videodata->clipboard_गवाक्षः)
                प्रत्यागम;

            /* when here we're notified that the clipboard had an external change, we request the
             * available mime types by asking for a conversion to the TARGETS format. We should get a
             * SelectionNotify event later, and when treating these results, we will push a ClipboardUpdated
             * event
             */

            X11_XConvertSelection(display, videodata->atoms.CLIPBOARD, videodata->atoms.TARGETS,
                    videodata->atoms.SDL_FORMATS, Get_गवाक्षः(_this), CurrentTime);
        }

        प्रत्यागम;
    }
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XFIXES

    यदि ((videodata->clipboard_गवाक्षः != None) &&
        (videodata->clipboard_गवाक्षः == xevent->xany.गवाक्षः)) {
        X11_HandleClipboardEvent(_this, xevent);
        प्रत्यागम;
    }

    // xsettings internally filters events for the windows it watches
    X11_HandleXsettingsEvent(_this, xevent);

    दत्त = X11_Find_गवाक्षः(videodata, xevent->xany.गवाक्षः);

    यदि (!दत्त) {
        // The window for KeymapNotify, etc events is 0
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
        यदि (videodata->keyboard.xkb_enabled && xevent->type == videodata->keyboard.xkb.event) {
            XkbEvent *xkbevent = (XkbEvent *)xevent;
            विकल्प (xkbevent->any.xkb_type) {
            पक्ष XkbStateNotify:
            {
#यदि_परिभाषितम् DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbStateNotify!", xevent->xany.गवाक्षः);
#यदि_अन्तः
                यदि ((xkbevent->state.परिवर्तितम् & Xkb_गणः_State_आवरणम्) && xkbevent->state.गणः != videodata->keyboard.xkb.current_गणः) {
                    videodata->keyboard.xkb.current_गणः = xkbevent->state.गणः;
                    SDL_समुच्चयः_Keymap(videodata->keyboard.xkb.keymaps[videodata->keyboard.xkb.current_गणः], true);
                }

                यदि (xkbevent->state.परिवर्तितम् & Xkb_Modifier_State_आवरणम्) {
                    videodata->keyboard.pressed_modifiers = xkbevent->state.आधारः_mods;
                    videodata->keyboard.locked_modifiers = xkbevent->state.latched_mods | xkbevent->state.locked_mods;
                    X11_ReconcileModifiers(videodata, false);
                }
            } भङ्ग;

            पक्ष XkbMapNotify:
#यदि_परिभाषितम् DEBUG_XEVENTS
                SDL_Log("window 0x%lx: XkbMapNotify!", xevent->xany.गवाक्षः);
                SDL_FALLTHROUGH;
#यदि_अन्तः
            पक्ष XkbNewKeyboardNotify:
            {
#यदि_परिभाषितम् DEBUG_XEVENTS
                यदि (xkbevent->any.xkb_type == XkbNewKeyboardNotify) {
                    SDL_Log("window 0x%lx: XkbNewKeyboardNotify!", xevent->xany.गवाक्षः);
                }
#यदि_अन्तः
                X11_XkbRefreshKeyboardMapping(&xkbevent->map);

                // Don't redundantly rebuild the keymap if this is a duplicate event.
                यदि (xkbevent->any.serial != videodata->keyboard.xkb.चरमः_map_serial) {
                    videodata->keyboard.xkb.चरमः_map_serial = xkbevent->any.serial;
                    X11_UpdateKeymap(_this, true);
                }
            } भङ्ग;

            स्वभाव:
                भङ्ग;
            }
        } अन्यथा
#यदि_अन्तः
        यदि (xevent->type == KeymapNotify) {
#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("window 0x%lx: KeymapNotify!", xevent->xany.गवाक्षः);
#यदि_अन्तः
            यदि (SDL_GetKeyboardFocus() != रिक्त) {
                यदि (!videodata->keyboard.xkb_enabled) {
                    X11_UpdateKeymap(_this, true);
                }
                X11_ReconcileKeyboardState(_this);
            }
        } अन्यथा यदि (xevent->type == MappingNotify) {
            ध्रुव पूर्णाङ्क request = xevent->xmapping.request;

            यदि (request == MappingPointer) {
#यदि_परिभाषितम् DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.गवाक्षः);
#यदि_अन्तः
                X11_Xinput2UpdatePointerMapping(_this);
            } अन्यथा यदि (!videodata->keyboard.xkb_enabled) {
                // Has the keyboard layout changed?
#यदि_परिभाषितम् DEBUG_XEVENTS
                SDL_Log("window 0x%lx: MappingNotify!", xevent->xany.गवाक्षः);
#यदि_अन्तः
                यदि (request == MappingKeyboard || request == MappingModifier) {
                    X11_XRefreshKeyboardMapping(&xevent->xmapping);
                }

                X11_UpdateKeymap(_this, true);
            }
        } अन्यथा यदि (xevent->type == PropertyNotify && videodata) {
            वर्ण *name_सम्बन्धि_atom = X11_XGetAtomName(display, xevent->xproperty.atom);
            यदि (name_सम्बन्धि_atom) {
                यदि (SDL_startswith(name_सम्बन्धि_atom, "_ICC_PROFILE")) {
                    XWindow_गुणाः attrib;
                    पूर्णाङ्क screennum;
                    प्रति (i = 0; i < videodata->numwindows; ++i) {
                        यदि (videodata->windowlist[i] != रिक्त) {
                            दत्त = videodata->windowlist[i];
                            X11_XGet_गवाक्षः_गुणाः(display, दत्त->xwindow, &attrib);
                            screennum = X11_XScreen_सङ्ख्या_सम्बन्धि_Screen(attrib.screen);
                            यदि (screennum == 0 && SDL_strcmp(name_सम्बन्धि_atom, "_ICC_PROFILE") == 0) {
                                SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_ICCPROF_परिवर्तितम्, 0, 0);
                            } अन्यथा यदि (SDL_strncmp(name_सम्बन्धि_atom, "_ICC_PROFILE_", परिमाण("_ICC_PROFILE_") - 1) == 0 && SDL_strlen(name_सम्बन्धि_atom) > परिमाण("_ICC_PROFILE_") - 1) {
                                पूर्णाङ्क iccscreennum = SDL_atoi(&name_सम्बन्धि_atom[परिमाण("_ICC_PROFILE_") - 1]);

                                यदि (screennum == iccscreennum) {
                                    SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_ICCPROF_परिवर्तितम्, 0, 0);
                                }
                            }
                        }
                    }
                } अन्यथा यदि (SDL_strcmp(name_सम्बन्धि_atom, "_NET_WORKAREA") == 0) {
                    प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
                        SDL_SendDisplayEvent(_this->displays[i], SDL_EVENT_DISPLAY_USABLE_BOUNDS_परिवर्तितम्, 0, 0);
                    }
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
                } अन्यथा यदि (SDL_strcmp(name_सम्बन्धि_atom, "GAMESCOPE_DISPLAY_IS_EXTERNAL") == 0 ||
                           SDL_strcmp(name_सम्बन्धि_atom, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS") == 0) {
                    X11_CheckDisplaysMoved(_this, display);
#यदि_अन्तः
                }
                X11_XFree(name_सम्बन्धि_atom);
            }
        }
        प्रत्यागम;
    }

    विकल्प (xevent->type) {

        // Gaining mouse coverage?
    पक्ष EnterNotify:
    {
        SDL_Mouse *mouse = SDL_GetMouse();
#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window 0x%lx: EnterNotify! (%d,%d,%d)", xevent->xany.गवाक्षः,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.बहुलकम्);
        यदि (xevent->xcrossing.बहुलकम् == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        यदि (xevent->xcrossing.बहुलकम् == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#यदि_अन्तः
        SDL_समुच्चयः_Mouse_Focus(दत्त->गवाक्षः);

        mouse->चरमः_x = xevent->xcrossing.x;
        mouse->चरमः_y = xevent->xcrossing.y;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
        {
            // Only create the barriers if we have input focus
            SDL_गवाक्षः_दत्त *windowdata = दत्त->गवाक्षः->आन्तरिकम्;
            यदि ((दत्त->pointer_barrier_सक्रिय == true) && windowdata->गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS) {
                X11_ConfineCursorWithFlags(_this, windowdata->गवाक्षः, &windowdata->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
            }
        }
#यदि_अन्तः

        यदि (!mouse->relative_बहुलकम्) {
            SDL_SendMouseMotion(0, दत्त->गवाक्षः, SDL_GLOBAL_MOUSE_ID, false, (भिन्न)xevent->xcrossing.x, (भिन्न)xevent->xcrossing.y);
        }

        // We ungrab in LeaveNotify, so we may need to grab again here, but not if captured, as the capture can be lost.
        यदि (!(दत्त->गवाक्षः->flags & SDL_गवाक्षः_MOUSE_CAPTURE)) {
            SDL_Update_गवाक्षः_Grab(दत्त->गवाक्षः);
        }

        X11_Process_लब्धम्_Test(_this, दत्त, mouse->चरमः_x, mouse->चरमः_y, true);
    } भङ्ग;
        // Losing mouse coverage?
    पक्ष LeaveNotify:
    {
#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window 0x%lx: LeaveNotify! (%d,%d,%d)", xevent->xany.गवाक्षः,
               xevent->xcrossing.x,
               xevent->xcrossing.y,
               xevent->xcrossing.बहुलकम्);
        यदि (xevent->xcrossing.बहुलकम् == NotifyGrab) {
            SDL_Log("Mode: NotifyGrab");
        }
        यदि (xevent->xcrossing.बहुलकम् == NotifyUngrab) {
            SDL_Log("Mode: NotifyUngrab");
        }
#यदि_अन्तः
        यदि (!SDL_GetMouse()->relative_बहुलकम्) {
            SDL_SendMouseMotion(0, दत्त->गवाक्षः, SDL_GLOBAL_MOUSE_ID, false, (भिन्न)xevent->xcrossing.x, (भिन्न)xevent->xcrossing.y);
        }

        यदि (xevent->xcrossing.बहुलकम् != NotifyGrab &&
            xevent->xcrossing.बहुलकम् != NotifyUngrab &&
            xevent->xcrossing.detail != NotifyInferior) {

            /* In order for interaction with the window decorations and menu to work properly
               on Mutter, we need to ungrab the keyboard when the mouse leaves. */
            यदि (!(दत्त->गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
                X11_समुच्चयः_गवाक्षः_Keyboard_Grab(_this, दत्त->गवाक्षः, false);
            }

            SDL_समुच्चयः_Mouse_Focus(रिक्त);
        }
    } भङ्ग;

        // Gaining input focus?
    पक्ष Focus_अन्तर्:
    {
        यदि (xevent->xfocus.बहुलकम् == NotifyGrab || xevent->xfocus.बहुलकम् == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.गवाक्षः);
#यदि_अन्तः
            भङ्ग;
        }

        यदि (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusIn (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.गवाक्षः);
#यदि_अन्तः
            भङ्ग;
        }
#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusIn!", xevent->xany.गवाक्षः);
#यदि_अन्तः
        यदि (!videodata->चरमः_बहुलकम्_change_deadline) /* no recent mode changes */ {
            दत्त->pending_focus = PENDING_FOCUS_NONE;
            दत्त->pending_focus_time = 0;
            X11_Dispatch_Focus_अन्तर्(_this, दत्त);
        } अन्यथा {
            दत्त->pending_focus = PENDING_FOCUS_अन्तर्;
            दत्त->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }
        दत्त->चरमः_focus_event_time = SDL_GetTicks();
    } भङ्ग;

        // Losing input focus?
    पक्ष Focus_बहिर्गमनम्:
    {
        यदि (xevent->xfocus.बहुलकम् == NotifyGrab || xevent->xfocus.बहुलकम् == NotifyUngrab) {
            // Someone is handling a global hotkey, ignore it
#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyGrab/NotifyUngrab, ignoring)", xevent->xany.गवाक्षः);
#यदि_अन्तः
            भङ्ग;
        }
        यदि (xevent->xfocus.detail == NotifyInferior || xevent->xfocus.detail == NotifyPointer) {
            /* We still have focus if a child gets focus. We also don't
               care about the position of the pointer when the keyboard
               focus changed. */
#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("window 0x%lx: FocusOut (NotifyInferior/NotifyPointer, ignoring)", xevent->xany.गवाक्षः);
#यदि_अन्तः
            भङ्ग;
        }
#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window 0x%lx: FocusOut!", xevent->xany.गवाक्षः);
#यदि_अन्तः
        यदि (!videodata->चरमः_बहुलकम्_change_deadline) /* no recent mode changes */ {
            दत्त->pending_focus = PENDING_FOCUS_NONE;
            दत्त->pending_focus_time = 0;
            X11_Dispatch_Focus_बहिर्गमनम्(_this, दत्त);
        } अन्यथा {
            दत्त->pending_focus = PENDING_FOCUS_बहिर्गमनम्;
            दत्त->pending_focus_time = SDL_GetTicks() + PENDING_FOCUS_TIME;
        }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if it is activated.
        यदि (दत्त->pointer_barrier_सक्रिय == true) {
            X11_ConfineCursorWithFlags(_this, दत्त->गवाक्षः, रिक्त, X11_BARRIER_HANDLED_BY_EVENT);
        }
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XFIXES
    } भङ्ग;


        // Have we been iconified?
    पक्ष UnmapNotify:
    {
        XEvent ev;

#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window 0x%lx: UnmapNotify!", xevent->xany.गवाक्षः);
#यदि_अन्तः

        यदि (X11_XCheckIfEvent(display, &ev, &isReparentNotify, (XPointer)&xevent->xunmap)) {
            X11_XCheckIfEvent(display, &ev, &isMapNotify, (XPointer)&xevent->xunmap);
        } अन्यथा {
            X11_DispatchUnmapNotify(दत्त);
        }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
        // Disable confinement if the window gets hidden.
        यदि (दत्त->pointer_barrier_सक्रिय == true) {
            X11_ConfineCursorWithFlags(_this, दत्त->गवाक्षः, रिक्त, X11_BARRIER_HANDLED_BY_EVENT);
        }
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XFIXES
    } भङ्ग;

        // Have we been restored?
    पक्ष MapNotify:
    {
#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window 0x%lx: MapNotify!", xevent->xany.गवाक्षः);
#यदि_अन्तः
        X11_DispatchMapNotify(दत्त);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
        // Enable confinement if it was activated.
        यदि (दत्त->pointer_barrier_सक्रिय == true) {
            X11_ConfineCursorWithFlags(_this, दत्त->गवाक्षः, &दत्त->barrier_rect, X11_BARRIER_HANDLED_BY_EVENT);
        }
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XFIXES
    } भङ्ग;

        // Have we been resized or moved?
    पक्ष ConfigureNotify:
    {
#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window 0x%lx: ConfigureNotify! (position: %d,%d, size: %dx%d)", xevent->xany.गवाक्षः,
               xevent->xconfigure.x, xevent->xconfigure.y,
               xevent->xconfigure.विस्तारः, xevent->xconfigure.height);
#यदि_अन्तः
        // Real configure notify events are relative to the parent, synthetic events are absolute.
        यदि (!xevent->xconfigure.send_event) {
            अचिह्नित पूर्णाङ्क अङ्कः_Children;
            गवाक्षः_2 ChildReturn, मूलम्_2, Parent;
            गवाक्षः_2 *Children;
            /* Translate these coordinates back to relative to root.
             *
             * XTranslateCoordinates can generate a BadWindow error if called during a racy
             * reparenting operation, so a non-fatal error handler is required.
             */
            x11_चरमः_error = 0;
            XErrorHandler पूर्व_handler = X11_XSetErrorHandler(Bad_गवाक्षः_Error_Handler);

            X11_XQuery_वृक्षः(दत्त->videodata->display, xevent->xconfigure.गवाक्षः, &मूलम्_2, &Parent, &Children, &अङ्कः_Children);
            X11_XTranslateCoordinates(xevent->xconfigure.display,
                                      Parent, Default_मूलम्_गवाक्षः(xevent->xconfigure.display),
                                      xevent->xconfigure.x, xevent->xconfigure.y,
                                      &xevent->xconfigure.x, &xevent->xconfigure.y,
                                      &ChildReturn);

            // Make sure the error callback was called if XTranslateCoordinates() failed.
            X11_XSync(display, False);
            X11_XSetErrorHandler(पूर्व_handler);

            // If XTranslateCoordinates failed due to a BadWindow error, nothing more to do here.
            यदि (x11_चरमः_error == Bad_गवाक्षः) {
                भङ्ग;
            }
        }

        /* Some window managers send ConfigureNotify before PropertyNotify when changing state (Xfce and
         * fvwm are known to do this), which is backwards from other window managers, as well as what is
         * expected by SDL and its clients. Defer emitting the size/move events until the corresponding
         * PropertyNotify arrives for consistency.
         */
        ध्रुव SDL_गवाक्षः_Flags परिवर्तितम् = X11_GetNetWMState(_this, दत्त->गवाक्षः, xevent->xproperty.गवाक्षः) ^ दत्त->गवाक्षः->flags;
        यदि (परिवर्तितम् & (SDL_गवाक्षः_FULLSCREEN | SDL_गवाक्षः_MAXIMIZED)) {
            SDL_copyp(&दत्त->pending_xconfigure, &xevent->xconfigure);
            दत्त->emit_आकार_move_after_property_notify = true;
        }

        यदि (!दत्त->emit_आकार_move_after_property_notify) {
            X11_EmitConfigureNotifyEvents(दत्त, &xevent->xconfigure);
        }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC
        X11_HandleConfigure(दत्त->गवाक्षः, &xevent->xconfigure);
#यदि_अन्तः /* SDL_VIDEO_DRIVER_X11_XSYNC */
    } भङ्ग;

        // Have we been requested to quit (or another client message?)
    पक्ष Client_सन्देशः:
    {
        स्थिर पूर्णाङ्क xdnd_संस्करणम् = 0;

        यदि (xevent->xclient.सन्देशः_type == videodata->atoms.XdndEnter) {

            bool use_list = xevent->xclient.दत्त.l[1] & 1;
            दत्त->xdnd_source = xevent->xclient.दत्त.l[0];
            xdnd_संस्करणम् = (xevent->xclient.दत्त.l[1] >> 24);
#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", दत्त->xdnd_source);
            SDL_Log("Protocol version to use : %d", xdnd_संस्करणम्);
            SDL_Log("More then 3 data types : %d", (पूर्णाङ्क)use_list);
#यदि_अन्तः

            यदि (use_list) {
                // fetch conversion targets
                SDL_x11Prop p;
                X11_ReadProperty(&p, display, दत्त->xdnd_source, videodata->atoms.XdndTypeList);
                // pick one
                दत्त->xdnd_req = X11_PickTarget(display, (Atom *)p.दत्त, p.गणनम्);
                X11_XFree(p.दत्त);
            } अन्यथा {
                // pick from list of three
                दत्त->xdnd_req = X11_PickTargetFromAtoms(display, xevent->xclient.दत्त.l[2], xevent->xclient.दत्त.l[3], xevent->xclient.दत्त.l[4]);
            }
        } अन्यथा यदि (xevent->xclient.सन्देशः_type == videodata->atoms.XdndLeave) {
#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("XID of source window : 0x%lx", xevent->xclient.दत्त.l[0]);
#यदि_अन्तः
            SDL_SendDropComplete(दत्त->गवाक्षः);
        } अन्यथा यदि (xevent->xclient.सन्देशः_type == videodata->atoms.XdndPosition) {

#यदि_परिभाषितम् DEBUG_XEVENTS
            Atom act = videodata->atoms.XdndActionCopy;
            यदि (xdnd_संस्करणम् >= 2) {
                act = xevent->xclient.दत्त.l[4];
            }
            SDL_Log("Action requested by user is : %s", X11_XGetAtomName(display, act));
#यदि_अन्तः
            {
                // Drag and Drop position
                पूर्णाङ्क मूलम्_x, मूलम्_y, गवाक्षः_x, गवाक्षः_y;
                गवाक्षः_2 ChildReturn;
                मूलम्_x = xevent->xclient.दत्त.l[2] >> 16;
                मूलम्_y = xevent->xclient.दत्त.l[2] & 0xffff;
                // Translate from root to current window position
                X11_XTranslateCoordinates(display, Default_मूलम्_गवाक्षः(display), दत्त->xwindow,
                                          मूलम्_x, मूलम्_y, &गवाक्षः_x, &गवाक्षः_y, &ChildReturn);

                SDL_SendDropPosition(दत्त->गवाक्षः, (भिन्न)गवाक्षः_x, (भिन्न)गवाक्षः_y);
            }

            // reply with status
            SDL_zero(m);
            m.type = Client_सन्देशः;
            m.display = xevent->xclient.display;
            m.गवाक्षः = xevent->xclient.दत्त.l[0];
            m.सन्देशः_type = videodata->atoms.Xdnd_स्थितिः;
            m.format = 32;
            m.दत्त.l[0] = दत्त->xwindow;
            m.दत्त.l[1] = (दत्त->xdnd_req != None);
            m.दत्त.l[2] = 0; // specify an empty rectangle
            m.दत्त.l[3] = 0;
            m.दत्त.l[4] = videodata->atoms.XdndActionCopy; // we only accept copying anyway

            X11_XSendEvent(display, xevent->xclient.दत्त.l[0], False, No_Event_आवरणम्, (XEvent *)&m);
            X11_XFlush(display);
        } अन्यथा यदि (xevent->xclient.सन्देशः_type == videodata->atoms.XdndDrop) {
            यदि (दत्त->xdnd_req == None) {
                // say again - not interested!
                SDL_zero(m);
                m.type = Client_सन्देशः;
                m.display = xevent->xclient.display;
                m.गवाक्षः = xevent->xclient.दत्त.l[0];
                m.सन्देशः_type = videodata->atoms.Xdnd_परिसमाप्तम्;
                m.format = 32;
                m.दत्त.l[0] = दत्त->xwindow;
                m.दत्त.l[1] = 0;
                m.दत्त.l[2] = None; // fail!
                X11_XSendEvent(display, xevent->xclient.दत्त.l[0], False, No_Event_आवरणम्, (XEvent *)&m);
            } अन्यथा {
                // convert
                यदि (xdnd_संस्करणम् >= 1) {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, दत्त->xdnd_req, videodata->atoms.PRIMARY, दत्त->xwindow, xevent->xclient.दत्त.l[2]);
                } अन्यथा {
                    X11_XConvertSelection(display, videodata->atoms.XdndSelection, दत्त->xdnd_req, videodata->atoms.PRIMARY, दत्त->xwindow, CurrentTime);
                }
            }
        } अन्यथा यदि ((xevent->xclient.सन्देशः_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.दत्त.l[0] == videodata->atoms._NET_WM_PING)) {
            गवाक्षः_2 मूलम् = Default_मूलम्_गवाक्षः(display);

#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("window 0x%lx: _NET_WM_PING", xevent->xany.गवाक्षः);
#यदि_अन्तः
            xevent->xclient.गवाक्षः = मूलम्;
            X11_XSendEvent(display, मूलम्, False, Substructure_Redirect_आवरणम् | Substructure_Notify_आवरणम्, xevent);
            भङ्ग;
        }

        अन्यथा यदि ((xevent->xclient.सन्देशः_type == videodata->atoms.WM_PROTOCOLS) &&
                 (xevent->xclient.format == 32) &&
                 (xevent->xclient.दत्त.l[0] == videodata->atoms.WM_DELETE_गवाक्षः)) {

#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("window 0x%lx: WM_DELETE_WINDOW", xevent->xany.गवाक्षः);
#यदि_अन्तः
            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_CLOSE_REQUESTED, 0, 0);
            भङ्ग;
        } अन्यथा यदि ((xevent->xclient.सन्देशः_type == videodata->atoms.WM_PROTOCOLS) &&
                   (xevent->xclient.format == 32) &&
                   (xevent->xclient.दत्त.l[0] == videodata->atoms._NET_WM_SYNC_REQUEST)) {

#यदि_परिभाषितम् DEBUG_XEVENTS
            SDL_Log("window %p: _NET_WM_SYNC_REQUEST", दत्त);
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC
            X11_HandleSyncRequest(दत्त->गवाक्षः, &xevent->xclient);
#यदि_अन्तः /* SDL_VIDEO_DRIVER_X11_XSYNC */
            भङ्ग;
        }
    } भङ्ग;

        // Do we need to refresh ourselves?
    पक्ष Expose:
    {
#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Expose (count = %d)", xevent->xany.गवाक्षः, xevent->xexpose.गणनम्);
#यदि_अन्तः
        SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_EXPOSED, 0, 0);
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
        यदि (दत्त->xinput2_keyboard_enabled) {
            // This input is being handled by XInput2.
            भङ्ग;
        } अन्यथा यदि (xevent->xkey.serial == videodata->xinput_चरमः_कुञ्चिका_serial) {
            // Use the device ID from the XInput2 event if the serials match.
            keyboardID = videodata->xinput_चरमः_keyboard_device;
        }

        X11_Handle_कुञ्चिका_Event(_this, दत्त, keyboardID, xevent);
    } भङ्ग;

    पक्ष MotionNotify:
    {
        यदि (X11_Xinput2_Handles_Motion_For_गवाक्षः(दत्त)) {
            // This input is being handled by XInput2
            भङ्ग;
        }

        SDL_Mouse *mouse = SDL_GetMouse();
        यदि (!mouse->relative_बहुलकम्) {
#यदि_परिभाषितम् DEBUG_MOTION
            SDL_Log("window 0x%lx: X11 motion: %d,%d", xevent->xany.गवाक्षः, xevent->xmotion.x, xevent->xmotion.y);
#यदि_अन्तः

            X11_Process_लब्धम्_Test(_this, दत्त, (भिन्न)xevent->xmotion.x, (भिन्न)xevent->xmotion.y, false);
            SDL_SendMouseMotion(0, दत्त->गवाक्षः, SDL_GLOBAL_MOUSE_ID, false, (भिन्न)xevent->xmotion.x, (भिन्न)xevent->xmotion.y);
        }
    } भङ्ग;

    पक्ष ButtonPress:
    {
        यदि (दत्त->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_चरमः_button_serial) {
            // This input event was handled by XInput2.
            भङ्ग;
        }

        X11_HandleButtonPress(_this, दत्त, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button,
                              xevent->xbutton.x, xevent->xbutton.y, xevent->xbutton.time, xevent->xbutton.serial);
    } भङ्ग;

    पक्ष ButtonRelease:
    {
        यदि (दत्त->xinput2_mouse_enabled && xevent->xbutton.serial == videodata->xinput_चरमः_button_serial) {
            // This input event was handled by XInput2.
            भङ्ग;
        }

        X11_HandleButtonRelease(_this, दत्त, SDL_GLOBAL_MOUSE_ID, xevent->xbutton.button, xevent->xbutton.time);
    } भङ्ग;

    पक्ष PropertyNotify:
    {
#यदि_परिभाषितम् DEBUG_XEVENTS
        अचिह्नित वर्ण *propdata;
        पूर्णाङ्क स्थितिः, real_format;
        Atom real_type;
        अचिह्नित दीर्घ वस्तूनि_read, वस्तूनि_वामः;

        वर्ण *name = X11_XGetAtomName(display, xevent->xproperty.atom);
        यदि (name) {
            SDL_Log("window 0x%lx: PropertyNotify: %s %s time=%lu", xevent->xany.गवाक्षः, name, (xevent->xproperty.state == PropertyDelete) ? "deleted" : "changed", xevent->xproperty.time);
            X11_XFree(name);
        }

        स्थितिः = X11_XGet_गवाक्षः_Property(display, दत्त->xwindow, xevent->xproperty.atom, 0L, 8192L, False, AnyPropertyType, &real_type, &real_format, &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
        यदि (स्थितिः == Success && वस्तूनि_read > 0) {
            यदि (real_type == XA_INTEGER) {
                पूर्णाङ्क *मानानि = (पूर्णाङ्क *)propdata;

                SDL_Log("{");
                प्रति (i = 0; i < वस्तूनि_read; i++) {
                    SDL_Log(" %d", मानानि[i]);
                }
                SDL_Log(" }");
            } अन्यथा यदि (real_type == XA_CARDINAL) {
                यदि (real_format == 32) {
                    Uint32 *मानानि = (Uint32 *)propdata;

                    SDL_Log("{");
                    प्रति (i = 0; i < वस्तूनि_read; i++) {
                        SDL_Log(" %d", मानानि[i]);
                    }
                    SDL_Log(" }");
                } अन्यथा यदि (real_format == 16) {
                    Uint16 *मानानि = (Uint16 *)propdata;

                    SDL_Log("{");
                    प्रति (i = 0; i < वस्तूनि_read; i++) {
                        SDL_Log(" %d", मानानि[i]);
                    }
                    SDL_Log(" }");
                } अन्यथा यदि (real_format == 8) {
                    Uint8 *मानानि = (Uint8 *)propdata;

                    SDL_Log("{");
                    प्रति (i = 0; i < वस्तूनि_read; i++) {
                        SDL_Log(" %d", मानानि[i]);
                    }
                    SDL_Log(" }");
                }
            } अन्यथा यदि (real_type == XA_STRING ||
                       real_type == videodata->atoms.UTF8_STRING) {
                SDL_Log("{ \"%s\" }", propdata);
            } अन्यथा यदि (real_type == XA_ATOM) {
                Atom *atoms = (Atom *)propdata;

                SDL_Log("{");
                प्रति (i = 0; i < वस्तूनि_read; i++) {
                    वर्ण *atomname = X11_XGetAtomName(display, atoms[i]);
                    यदि (atomname) {
                        SDL_Log(" %s", atomname);
                        X11_XFree(atomname);
                    }
                }
                SDL_Log(" }");
            } अन्यथा {
                वर्ण *atomname = X11_XGetAtomName(display, real_type);
                SDL_Log("Unknown type: 0x%lx (%s)", real_type, atomname ? atomname : "UNKNOWN");
                यदि (atomname) {
                    X11_XFree(atomname);
                }
            }
        }
        यदि (स्थितिः == Success) {
            X11_XFree(propdata);
        }
#यदि_अन्तः // DEBUG_XEVENTS

        /* Take advantage of this moment to make sure user_time has a
            valid timestamp from the X server, so if we later try to
            raise/restore this window, _NET_ACTIVE_WINDOW can have a
            non-zero timestamp, even if there's never been a mouse or
            key press to this window so far. Note that we don't try to
            set _NET_WM_USER_TIME here, though. That's only for legit
            user interaction with the window. */
        यदि (!दत्त->user_time) {
            दत्त->user_time = xevent->xproperty.time;
        }

        यदि (xevent->xproperty.atom == दत्त->videodata->atoms._NET_WM_STATE) {
            /* Get the new state from the window manager.
             * Compositing window managers can alter visibility of windows
             * without ever mapping / unmapping them, so we handle that here,
             * because they use the NETWM protocol to notify us of changes.
             */
            ध्रुव SDL_गवाक्षः_Flags flags = X11_GetNetWMState(_this, दत्त->गवाक्षः, xevent->xproperty.गवाक्षः);
            ध्रुव SDL_गवाक्षः_Flags परिवर्तितम् = flags ^ दत्त->गवाक्षः->flags;

            यदि ((परिवर्तितम् & SDL_गवाक्षः_HIDDEN) && !(flags & SDL_गवाक्षः_HIDDEN)) {
                X11_DispatchMapNotify(दत्त);
            }

            यदि (!SDL_गवाक्षः_IS_POPUP(दत्त->गवाक्षः)) {
                यदि (परिवर्तितम् & SDL_गवाक्षः_FULLSCREEN) {
                    दत्त->pending_operation &= ~X11_PENDING_OP_FULLSCREEN;

                    यदि (flags & SDL_गवाक्षः_FULLSCREEN) {
                        यदि (!(flags & SDL_गवाक्षः_MINIMIZED)) {
                            ध्रुव bool commit = SDL_memcmp(&दत्त->गवाक्षः->current_fullscreen_बहुलकम्, &दत्त->requested_fullscreen_बहुलकम्, परिमाण(SDL_Display_बहुलकम्)) != 0;

                            // Ensure the maximized flag is cleared before entering fullscreen.
                            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_RESTORED, 0, 0);
                            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_ENTER_FULLSCREEN, 0, 0);
                            यदि (commit) {
                                /* This was initiated by the compositor, or the mode was changed between the request and the window
                                 * becoming fullscreen. Switch to the application requested mode if necessary.
                                 */
                                SDL_copyp(&दत्त->गवाक्षः->current_fullscreen_बहुलकम्, &दत्त->गवाक्षः->requested_fullscreen_बहुलकम्);
                                SDL_Update_Fullscreen_बहुलकम्(दत्त->गवाक्षः, SDL_FULLSCREEN_OP_UPDATE, true);
                            } अन्यथा {
                                SDL_Update_Fullscreen_बहुलकम्(दत्त->गवाक्षः, SDL_FULLSCREEN_OP_ENTER, false);
                            }
                        }
                    } अन्यथा {
                        SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_LEAVE_FULLSCREEN, 0, 0);
                        SDL_Update_Fullscreen_बहुलकम्(दत्त->गवाक्षः, false, false);

                        SDL_zero(दत्त->requested_fullscreen_बहुलकम्);

                        // Need to restore or update any limits changed while the window was fullscreen.
                        X11_समुच्चयः_गवाक्षः_Min_Max(दत्त->गवाक्षः, !!(flags & SDL_गवाक्षः_MAXIMIZED));

                        // Toggle the borders if they were forced on while creating a borderless fullscreen window.
                        यदि (दत्त->fullscreen_borders_forced_on) {
                            दत्त->toggle_borders = true;
                            दत्त->fullscreen_borders_forced_on = false;
                        }
                    }

                    यदि ((flags & SDL_गवाक्षः_FULLSCREEN) &&
                        (दत्त->border_शिखरम् || दत्त->border_वामः || दत्त->border_bottom || दत्त->border_दक्षिणः)) {
                        /* If the window is entering fullscreen and the borders are
                         * non-zero sized, turn off size events until the borders are
                         * shut off to avoid bogus window sizes and positions, and
                         * note that the old borders were non-zero for restoration.
                         */
                        दत्त->आकार_move_event_flags |= X11_आकार_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        दत्त->previous_borders_nonzero = true;
                    } अन्यथा यदि (!(flags & SDL_गवाक्षः_FULLSCREEN) &&
                               दत्त->previous_borders_nonzero &&
                               (!दत्त->border_शिखरम् && !दत्त->border_वामः && !दत्त->border_bottom && !दत्त->border_दक्षिणः)) {
                        /* If the window is leaving fullscreen and the current borders
                         * are zero sized, but weren't when entering fullscreen, turn
                         * off size events until the borders come back to avoid bogus
                         * window sizes and positions.
                         */
                        दत्त->आकार_move_event_flags |= X11_आकार_MOVE_EVENTS_WAIT_FOR_BORDERS;
                        दत्त->previous_borders_nonzero = false;
                    } अन्यथा {
                        दत्त->आकार_move_event_flags = 0;
                        दत्त->previous_borders_nonzero = false;

                        यदि (!(दत्त->गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) && दत्त->toggle_borders) {
                            दत्त->toggle_borders = false;
                            X11_समुच्चयः_गवाक्षः_Bordered(_this, दत्त->गवाक्षः, !(दत्त->गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS));
                        }
                    }
                }
                यदि ((परिवर्तितम् & SDL_गवाक्षः_MAXIMIZED) && ((flags & SDL_गवाक्षः_MAXIMIZED) && !(flags & SDL_गवाक्षः_MINIMIZED))) {
                    दत्त->pending_operation &= ~X11_PENDING_OP_MAXIMIZE;
                    यदि ((परिवर्तितम् & SDL_गवाक्षः_MINIMIZED)) {
                        दत्त->pending_operation &= ~X11_PENDING_OP_RESTORE;
                        // If coming out of minimized, send a restore event before sending maximized.
                        SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_RESTORED, 0, 0);
                    }
                    SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_MAXIMIZED, 0, 0);
                }
                यदि ((परिवर्तितम् & SDL_गवाक्षः_MINIMIZED) && (flags & SDL_गवाक्षः_MINIMIZED)) {
                    दत्त->pending_operation &= ~X11_PENDING_OP_MINIMIZE;
                    SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_MINIMIZED, 0, 0);
                }
                यदि (!(flags & (SDL_गवाक्षः_MAXIMIZED | SDL_गवाक्षः_MINIMIZED))) {
                    दत्त->pending_operation &= ~X11_PENDING_OP_RESTORE;
                    SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_RESTORED, 0, 0);

                    // Apply any pending state if restored.
                    यदि (!(flags & SDL_गवाक्षः_FULLSCREEN)) {
                        यदि (दत्त->pending_position) {
                            दत्त->pending_position = false;
                            दत्त->pending_operation |= X11_PENDING_OP_MOVE;
                            दत्त->expected.x = दत्त->गवाक्षः->pending.x - दत्त->border_वामः;
                            दत्त->expected.y = दत्त->गवाक्षः->pending.y - दत्त->border_शिखरम्;
                            X11_XMove_गवाक्षः(display, दत्त->xwindow, दत्त->expected.x, दत्त->expected.y);
                        }
                        यदि (दत्त->pending_आकार) {
                            दत्त->pending_आकार = false;
                            दत्त->pending_operation |= X11_PENDING_OP_RESIZE;
                            दत्त->expected.w = दत्त->गवाक्षः->pending.w;
                            दत्त->expected.h = दत्त->गवाक्षः->pending.h;
                            X11_XResize_गवाक्षः(display, दत्त->xwindow, दत्त->गवाक्षः->pending.w, दत्त->गवाक्षः->pending.h);
                        }
                    }
                }
                यदि (दत्त->emit_आकार_move_after_property_notify) {
                    X11_EmitConfigureNotifyEvents(दत्त, &दत्त->pending_xconfigure);
                    दत्त->emit_आकार_move_after_property_notify = false;
                }
                यदि ((flags & SDL_गवाक्षः_निवेशः_FOCUS)) {
                    यदि (दत्त->pending_move) {
                        Dispatch_गवाक्षः_Move(_this, दत्त, &दत्त->pending_move_point);
                        दत्त->pending_move = false;
                    }
                }
            }
            यदि (परिवर्तितम् & SDL_गवाक्षः_OCCLUDED) {
                SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, (flags & SDL_गवाक्षः_OCCLUDED) ? SDL_EVENT_गवाक्षः_OCCLUDED : SDL_EVENT_गवाक्षः_EXPOSED, 0, 0);
            }
        } अन्यथा यदि (xevent->xproperty.atom == videodata->atoms.WM_STATE) {
            /* Support for ICCCM-compliant window managers (like i3) that change
               WM_STATE to WithdrawnState without sending UnmapNotify or updating
               _NET_WM_STATE when moving windows to invisible workspaces. */
            Atom type;
            पूर्णाङ्क format;
            अचिह्नित दीर्घ nitems, अष्टकानि_after;
            अचिह्नित वर्ण *prop_दत्त = रिक्त;

            यदि (X11_XGet_गवाक्षः_Property(display, दत्त->xwindow, videodata->atoms.WM_STATE,
                                       0L, 2L, False, videodata->atoms.WM_STATE,
                                       &type, &format, &nitems, &अष्टकानि_after, &prop_दत्त) == Success) {
                यदि (nitems > 0) {
                    // WM_STATE: 0=Withdrawn, 1=Normal, 3=Iconic
                    Uint32 state = *(Uint32 *)prop_दत्त;

                    यदि ((state == 0 || state == 3) && !दत्त->गवाक्षः->is_hiding && !(दत्त->गवाक्षः->flags & SDL_गवाक्षः_HIDDEN)) {
                        // Withdrawn or Iconic
                        यदि (!(दत्त->गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED)) {
                            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_MINIMIZED, 0, 0);
                            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_OCCLUDED, 0, 0);
                        }
                    } अन्यथा यदि (state == 1) { // NormalState
                        यदि (दत्त->गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED) {
                            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_RESTORED, 0, 0);
                            SDL_Send_गवाक्षः_Event(दत्त->गवाक्षः, SDL_EVENT_गवाक्षः_EXPOSED, 0, 0);
                        }
                    }
                }
                X11_XFree(prop_दत्त);
            }
        } अन्यथा यदि (xevent->xproperty.atom == videodata->atoms.XKLAVIER_STATE) {
            /* Hack for Ubuntu 12.04 (etc) that doesn't send MappingNotify
               events when the keyboard layout changes (for example,
               changing from English to French on the menubar's keyboard
               icon). Since it changes the XKLAVIER_STATE property, we
               notice and reinit our keymap here. This might not be the
               right approach, but it seems to work. */
            X11_UpdateKeymap(_this, true);
        } अन्यथा यदि (xevent->xproperty.atom == videodata->atoms._NET_FRAME_EXTENTS) {
            X11_Get_Border_मानानि(दत्त);
            यदि (दत्त->आकार_move_event_flags) {
                /* Events are disabled when leaving fullscreen until the borders appear to avoid
                 * incorrect size/position events on compositing window managers.
                 */
                दत्त->आकार_move_event_flags &= ~X11_आकार_MOVE_EVENTS_WAIT_FOR_BORDERS;
            }
            यदि (!(दत्त->गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) && दत्त->toggle_borders) {
                दत्त->toggle_borders = false;
                X11_समुच्चयः_गवाक्षः_Bordered(_this, दत्त->गवाक्षः, !(दत्त->गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS));
            }
        }
    } भङ्ग;

    पक्ष SelectionNotify:
    {
        Atom target = xevent->xselection.target;
#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window 0x%lx: SelectionNotify (requestor = 0x%lx, target = 0x%lx)", xevent->xany.गवाक्षः,
               xevent->xselection.requestor, xevent->xselection.target);
#यदि_अन्तः
        यदि (target == दत्त->xdnd_req) {
            // read data
            SDL_x11Prop p;
            X11_ReadProperty(&p, display, दत्त->xwindow, videodata->atoms.PRIMARY);

            यदि (p.format == 8) {
                वर्ण *saveptr = रिक्त;
                वर्ण *name = X11_XGetAtomName(display, target);
                यदि (name) {
                    वर्ण *token = SDL_strtok_r((वर्ण *)p.दत्त, "\r\n", &saveptr);
                    यावत् (token) {
                        यदि ((SDL_strcmp("text/plain;charset=utf-8", name) == 0) ||
                            (SDL_strcmp("UTF8_STRING", name) == 0) ||
                            (SDL_strcmp("text/plain", name) == 0) ||
                            (SDL_strcmp("TEXT", name) == 0)) {
                            SDL_SendDropText(दत्त->गवाक्षः, token);
                        } अन्यथा यदि (SDL_strcmp("text/uri-list", name) == 0) {
                            यदि (SDL_URIToLocal(token, token) >= 0) {
                                SDL_SendDropFile(दत्त->गवाक्षः, रिक्त, token);
                            }
                        }
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    X11_XFree(name);
                }
                SDL_SendDropComplete(दत्त->गवाक्षः);
            }
            X11_XFree(p.दत्त);

            // send reply
            SDL_zero(m);
            m.type = Client_सन्देशः;
            m.display = display;
            m.गवाक्षः = दत्त->xdnd_source;
            m.सन्देशः_type = videodata->atoms.Xdnd_परिसमाप्तम्;
            m.format = 32;
            m.दत्त.l[0] = दत्त->xwindow;
            m.दत्त.l[1] = 1;
            m.दत्त.l[2] = videodata->atoms.XdndActionCopy;
            X11_XSendEvent(display, दत्त->xdnd_source, False, No_Event_आवरणम्, (XEvent *)&m);

            X11_XSync(display, False);
        }
    } भङ्ग;

    स्वभाव:
    {
#यदि_परिभाषितम् DEBUG_XEVENTS
        SDL_Log("window 0x%lx: Unhandled event %d", xevent->xany.गवाक्षः, xevent->type);
#यदि_अन्तः
    } भङ्ग;
    }
}

स्थिर शून्य X11_HandleFocusChanges(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    पूर्णाङ्क i;

    यदि (videodata && videodata->windowlist) {
        प्रति (i = 0; i < videodata->numwindows; ++i) {
            SDL_गवाक्षः_दत्त *दत्त = videodata->windowlist[i];
            यदि (दत्त && दत्त->pending_focus != PENDING_FOCUS_NONE) {
                Uint64 now = SDL_GetTicks();
                यदि (now >= दत्त->pending_focus_time) {
                    यदि (दत्त->pending_focus == PENDING_FOCUS_अन्तर्) {
                        X11_Dispatch_Focus_अन्तर्(_this, दत्त);
                    } अन्यथा {
                        X11_Dispatch_Focus_बहिर्गमनम्(_this, दत्त);
                    }
                    दत्त->pending_focus = PENDING_FOCUS_NONE;
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
    यदि (!X11_XCheckIfEvent(display, event, isAnyEvent, रिक्त)) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

शून्य X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    Display *req_display = दत्त->request_display;
    गवाक्षः_2 xwindow = गवाक्षः->आन्तरिकम्->xwindow;
    XClient_सन्देशः_Event event;

    SDL_zero(event);
    event.type = Client_सन्देशः;
    event.display = req_display;
    event.send_event = True;
    event.सन्देशः_type = दत्त->atoms._SDL_WAKEUP;
    event.format = 8;

    X11_XSendEvent(req_display, xwindow, False, No_Event_आवरणम्, (XEvent *)&event);
    /* XSendEvent returns a status and it could be BadValue or BadWindow. If an
      error happens it is an SDL's internal error and there is nothing we can do here. */
    X11_XFlush(req_display);
}

पूर्णाङ्क X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    Display *display;
    XEvent xevent;
    display = videodata->display;

    SDL_zero(xevent);

    // Flush and poll to grab any events already read and queued
    X11_XFlush(display);
    यदि (X11_PollEvent(display, &xevent)) {
        // Fall through
    } अन्यथा यदि (timeoutNS == 0) {
        प्रत्यागम 0;
    } अन्यथा {
        // Use SDL_IOR_NO_RETRY to ensure SIGINT will break us out of our wait
        पूर्णाङ्क err = SDL_IOReady(Connection_सङ्ख्या(display), SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        यदि (err > 0) {
            यदि (!X11_PollEvent(display, &xevent)) {
                /* Someone may have beat us to reading the fd. Return 1 here to
                 * trigger the normal spurious wakeup logic in the event core. */
                प्रत्यागम 1;
            }
        } अन्यथा यदि (err == 0) {
            // Timeout
            प्रत्यागम 0;
        } अन्यथा {
            // Error returned from poll()/select()

            यदि (errno == EINTR) {
                /* If the wait was interrupted by a signal, we may have generated a
                 * SDL_EVENT_QUIT event. Let the caller know to call SDL_PumpEvents(). */
                प्रत्यागम 1;
            } अन्यथा {
                प्रत्यागम err;
            }
        }
    }

    X11_DispatchEvent(_this, &xevent);
    प्रत्यागम 1;
}

शून्य X11_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    XEvent xevent;
    पूर्णाङ्क i;

    /* Check if a display had the mode changed and is waiting for a window to asynchronously become
     * fullscreen. If there is no fullscreen window past the elapsed timeout, revert the mode switch.
     */
    प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
        यदि (_this->displays[i]->आन्तरिकम्->बहुलकम्_switch_deadline_ns) {
            यदि (_this->displays[i]->fullscreen_गवाक्षः) {
                _this->displays[i]->आन्तरिकम्->बहुलकम्_switch_deadline_ns = 0;
            } अन्यथा यदि (SDL_GetTicksNS() >= _this->displays[i]->आन्तरिकम्->बहुलकम्_switch_deadline_ns) {
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                             "Time out elapsed after mode switch on display %" SDL_PRIu32 " with no window becoming fullscreen; reverting", _this->displays[i]->id);
                SDL_समुच्चयः_Display_बहुलकम्_For_Display(_this->displays[i], रिक्त);
                _this->displays[i]->आन्तरिकम्->बहुलकम्_switch_deadline_ns = 0;
            }
        }
    }

    यदि (दत्त->चरमः_बहुलकम्_change_deadline) {
        यदि (SDL_GetTicks() >= दत्त->चरमः_बहुलकम्_change_deadline) {
            दत्त->चरमः_बहुलकम्_change_deadline = 0; // assume we're done.
        }
    }

    // Update activity every 30 seconds to prevent screensaver
    यदि (_this->suspend_screensaver) {
        Uint64 now = SDL_GetTicks();
        यदि (!दत्त->screensaver_activity || now >= (दत्त->screensaver_activity + 30000)) {
            X11_XResetScreenSaver(दत्त->display);

#यदि_परिभाषितम् SDL_USE_LIBDBUS
            SDL_DBus_ScreensaverTickle();
#यदि_अन्तः

            दत्त->screensaver_activity = now;
        }
    }

    SDL_zero(xevent);

    // Keep processing pending events
    यावत् (X11_PollEvent(दत्त->display, &xevent)) {
        X11_DispatchEvent(_this, &xevent);
    }

    // FIXME: Only need to do this when there are pending focus changes
    X11_HandleFocusChanges(_this);

    // FIXME: Only need to do this when there are flashing windows
    प्रति (i = 0; i < दत्त->numwindows; ++i) {
        यदि (दत्त->windowlist[i] != रिक्त &&
            दत्त->windowlist[i]->flash_cancel_time &&
            SDL_GetTicks() >= दत्त->windowlist[i]->flash_cancel_time) {
            X11_Flash_गवाक्षः(_this, दत्त->windowlist[i]->गवाक्षः, SDL_FLASH_CANCEL);
        }
    }

    यदि (दत्त->xinput_hierarchy_परिवर्तितम्) {
        X11_Xinput2UpdateDevices(_this);
        दत्त->xinput_hierarchy_परिवर्तितम् = false;
    }
}

bool X11_SuspendScreenSaver(SDL_VideoDevice *_this)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    पूर्णाङ्क dummy;
    पूर्णाङ्क major_संस्करणम्, minor_संस्करणम्;
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XSCRNSAVER

#यदि_परिभाषितम् SDL_USE_LIBDBUS
    यदि (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        प्रत्यागम true;
    }

    यदि (_this->suspend_screensaver) {
        SDL_DBus_ScreensaverTickle();
    }
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSCRNSAVER
    यदि (SDL_X11_HAVE_XSS) {
        // X11_XScreenSaverSuspend was introduced in MIT-SCREEN-SAVER 1.1
        यदि (!X11_XScreenSaverQueryExtension(दत्त->display, &dummy, &dummy) ||
            !X11_XScreen_Saver_Query_संस्करणम्(दत्त->display,
                                          &major_संस्करणम्, &minor_संस्करणम्) ||
            major_संस्करणम् < 1 || (major_संस्करणम् == 1 && minor_संस्करणम् < 1)) {
            प्रत्यागम SDL_Unsupported();
        }

        X11_XScreenSaverSuspend(दत्त->display, _this->suspend_screensaver);
        X11_XResetScreenSaver(दत्त->display);
        प्रत्यागम true;
    }
#यदि_अन्तः
    प्रत्यागम SDL_Unsupported();
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
