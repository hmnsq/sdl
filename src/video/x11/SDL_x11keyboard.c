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
#ضمن "SDL_internal.h"

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"

#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_scancode_tables_c.h"

#ضمن <X11/keysym.h>

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#ضمن <X11/XKBlib.h>
#د_که_پای

#ضمن "../../events/imKStoUCS.h"
#ضمن "../../events/SDL_keysym_to_scancode_c.h"
#ضمن "../../events/SDL_keysym_to_keycode_c.h"

#که_تعریف_شوی X_HAVE_UTF8_STRING
#ضمن <locale.h>
#د_که_پای

ساكن SDL_Scancode_جدول scancode_سېټ[] = {
    SDL_SCANCODE_جدول_DARWIN,
    SDL_SCANCODE_جدول_XFREE86_1,
    SDL_SCANCODE_جدول_XFREE86_2,
    SDL_SCANCODE_جدول_XVNC,
};

ساكن bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    بدل (scancode) {
    حالة SDL_SCANCODE_ESCAPE:
    حالة SDL_SCANCODE_CAPSLOCK:
    حالة SDL_SCANCODE_NUMLOCKCLEAR:
    حالة SDL_SCANCODE_LSHIFT:
    حالة SDL_SCANCODE_RSHIFT:
    حالة SDL_SCANCODE_LCTRL:
    حالة SDL_SCANCODE_RCTRL:
    حالة SDL_SCANCODE_LALT:
    حالة SDL_SCANCODE_RALT:
    حالة SDL_SCANCODE_LGUI:
    حالة SDL_SCANCODE_RGUI:
        أرجع false;
    افتراضي:
        أرجع true;
    }
}

ساكن کلی_Sym X11_کلی_کوډ_منزل_Sym(SDL_VideoDevice *_this, کلی_کوډ_2 keycode, بینښه صحيح ډله, بینښه صحيح level)
{
    SDL_Video_معلومات *معلومات = _this->دننی;
    کلی_Sym keysym;

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (معلومات->keyboard.xkb_enabled) {
        keysym = X11_Xkb_Keycode_منزل_Keysym(معلومات->display, keycode, ډله, level);
    } وإلا
#د_که_پای
    {
        // TODO: Handle groups on the legacy path.
        إذا (keycode >= معلومات->keyboard.core.min_keycode && keycode <= معلومات->keyboard.core.max_keycode) {
            keysym = معلومات->keyboard.core.keysym_map[(keycode - معلومات->keyboard.core.min_keycode) * معلومات->keyboard.core.keysyms_فی_کلی];
        } وإلا {
            keysym = No_نښه;
        }
    }

    أرجع keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
ساكن SDL_Scancode X11_کلی_کوډ_منزل_SDLScancode(SDL_VideoDevice *_this, کلی_کوډ_2 keycode)
{
    ثابت کلی_Sym keysym = X11_کلی_کوډ_منزل_Sym(_this, keycode, 0, 0);

    إذا (keysym == No_نښه) {
        أرجع SDL_SCANCODE_UNKNOWN;
    }

    أرجع SDL_Get_Scancode_From_کلی_Sym(keysym, keycode);
}

#که_تعریف_شوی X_HAVE_UTF8_STRING
ساكن bool X11_InitIM(SDL_Video_معلومات *videodata);

ساكن فراغ im_instantiate_handler(Display *display, XPointer client_معلومات, XPointer call_معلومات)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)client_معلومات;

    إذا (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, عدم, عدم, عدم, im_instantiate_handler, client_معلومات);
    }
}

ساكن فراغ im_destroyed_handler(XIM im, XPointer client_معلومات, XPointer call_معلومات)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)client_معلومات;

    videodata->im = عدم;
    X11_XRegisterIMInstantiateCallback(videodata->display, عدم, عدم, عدم, im_instantiate_handler, client_معلومات);
}

ساكن bool X11_InitIM(SDL_Video_معلومات *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    حرف *prev_locale = setlocale(LC_ALL, عدم);
    حرف *prev_xmods = X11_XSetLocaleModifiers(عدم);

    إذا (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    إذا (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (فراغ)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, عدم, عدم, عدم);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (فراغ)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    إذا (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_معلومات_2 = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (حرف *)عدم);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        لكل (صحيح i = 0; i < videodata->numwindows; ++i) {
            SDL_کړکۍ_معلومات *w = videodata->windowlist[i];
            إذا (!w->ic) {
                X11_Create_ننوت_Context(w);
            }
        }

        أرجع true;
    }

    أرجع false;
}
#د_که_پای // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->دننی;
    صحيح i = 0;
    صحيح j = 0;
    صحيح min_keycode, max_keycode;
    بنية
    {
        SDL_Scancode scancode;
        کلی_Sym keysym;
        صحيح ارزښت;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_مخکینی, 0 },
        { SDL_SCANCODE_پورته, XK_پورته, 0 },
        { SDL_SCANCODE_کیڼ, XK_کیڼ, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    صحيح غوره_واټن;
    صحيح غوره_شاخص;
    صحيح واټن;

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    صحيح xkb_major = Xkb_Major_نسخه;
    صحيح xkb_minor = Xkb_Minor_نسخه;

    إذا (X11_XkbQueryExtension(معلومات->display, عدم, &معلومات->keyboard.xkb.event, عدم, &xkb_major, &xkb_minor)) {
        Bool xkb_repeat = 0;
        معلومات->keyboard.xkb_enabled = true;
        معلومات->keyboard.xkb.desc_ptr = X11_XkbGetMap(معلومات->display, Xkb_All_Client_Info_ماسک, XkbUseCoreKbd);

        // This will remove KeyRelease events for held keys.
        X11_Xkb_سېټ_Detectable_Auto_Repeat(معلومات->display, True, &xkb_repeat);

        // Enable the key mapping and state events.
        X11_XkbSelectEvents(معلومات->display, XkbUseCoreKbd,
                            Xkb_New_Keyboard_Notify_ماسک | Xkb_Map_Notify_ماسک | Xkb_State_Notify_ماسک,
                            Xkb_New_Keyboard_Notify_ماسک | Xkb_Map_Notify_ماسک | Xkb_State_Notify_ماسک);
        X11_XkbSelectEventDetails(معلومات->display, XkbUseCoreKbd, XkbStateNotify, Xkb_ډله_State_ماسک | Xkb_Modifier_State_ماسک, Xkb_ډله_State_ماسک | Xkb_Modifier_State_ماسک);
    } وإلا
#د_که_پای
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(معلومات->display, &معلومات->keyboard.core.min_keycode, &معلومات->keyboard.core.max_keycode);
        معلومات->keyboard.core.keysym_map = X11_XGetKeyboardMapping(معلومات->display, معلومات->keyboard.core.min_keycode,
                                                              معلومات->keyboard.core.max_keycode - معلومات->keyboard.core.min_keycode,
                                                              &معلومات->keyboard.core.keysyms_فی_کلی);
    }

    // Open a connection to the X input manager
#که_تعریف_شوی X_HAVE_UTF8_STRING
    إذا (SDL_X11_HAVE_UTF8) {
        إذا (!X11_InitIM(معلومات)) {
            X11_XRegisterIMInstantiateCallback(معلومات->display, عدم, عدم, عدم, im_instantiate_handler, (XPointer)معلومات);
        }
    }
#د_که_پای
    // Try to determine which scancodes are being used based on fingerprint
    غوره_واټن = SDL_arraysize(fingerprint) + 1;
    غوره_شاخص = -1;
    X11_XDisplayKeycodes(معلومات->display, &min_keycode, &max_keycode);
    لكل (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].ارزښت = X11_XKeysym_منزل_Keycode(معلومات->display, fingerprint[i].keysym) - min_keycode;
    }
    لكل (i = 0; i < SDL_arraysize(scancode_سېټ); ++i) {
        صحيح جدول_اندازه;
        ثابت SDL_Scancode *جدول = SDL_Get_Scancode_جدول(scancode_سېټ[i], &جدول_اندازه);

        واټن = 0;
        لكل (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            إذا (fingerprint[j].ارزښت < 0 || fingerprint[j].ارزښت >= جدول_اندازه) {
                واټن += 1;
            } وإلا إذا (جدول[fingerprint[j].ارزښت] != fingerprint[j].scancode) {
                واټن += 1;
            }
        }
        إذا (واټن < غوره_واټن) {
            غوره_واټن = واټن;
            غوره_شاخص = i;
        }
    }
    إذا (غوره_شاخص < 0 || غوره_واټن > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        صحيح fingerprint_ارزښت = X11_XKeysym_منزل_Keycode(معلومات->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        إذا (fingerprint_ارزښت == 235) {
            لكل (i = 0; i < SDL_arraysize(scancode_سېټ); ++i) {
                إذا (scancode_سېټ[i] == SDL_SCANCODE_جدول_XFREE86_2) {
                    غوره_شاخص = i;
                    غوره_واټن = 0;
                    اكسر;
                }
            }
        }
    }
    إذا (غوره_شاخص >= 0 && غوره_واټن <= 2) {
        صحيح جدول_اندازه;
        ثابت SDL_Scancode *جدول = SDL_Get_Scancode_جدول(scancode_سېټ[غوره_شاخص], &جدول_اندازه);

#که_تعریف_شوی DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", غوره_شاخص, min_keycode, max_keycode, جدول_اندازه);
#د_که_پای
        // This should never happen, but just in case...
        إذا (جدول_اندازه > (SDL_arraysize(معلومات->keyboard.کلی_layout) - min_keycode)) {
            جدول_اندازه = (SDL_arraysize(معلومات->keyboard.کلی_layout) - min_keycode);
        }
        SDL_memcpy(&معلومات->keyboard.کلی_layout[min_keycode], جدول, حجم(SDL_Scancode) * جدول_اندازه);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        لكل (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_کلی_کوډ_منزل_SDLScancode(_this, i);
#که_تعریف_شوی DEBUG_KEYBOARD
            {
                کلی_Sym sym;
                sym = X11_کلی_کوډ_منزل_Sym(_this, (کلی_کوډ_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (بینښه صحيح)sym, sym == No_نښه ? "NoSymbol" : X11_XKeysym_منزل_String(sym));
            }
#د_که_پای
            إذا (scancode == معلومات->keyboard.کلی_layout[i]) {
                استمر;
            }
            إذا ((SDL_GetKeymapKeycode(عدم, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_ماسک | SDLK_EXTENDED_ماسک)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#که_تعریف_شوی DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", معلومات->کلی_layout[i], SDL_GetScancodeName(معلومات->کلی_layout[i]), scancode, SDL_GetScancodeName(scancode));
#د_که_پای
                معلومات->keyboard.کلی_layout[i] = scancode;
            }
        }
    } وإلا {
#که_تعریف_شوی DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#د_که_پای

        // Determine key_layout - only works on US QWERTY layout
        لكل (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_کلی_کوډ_منزل_SDLScancode(_this, i);
#که_تعریف_شوی DEBUG_SCANCODES
            {
                کلی_Sym sym;
                sym = X11_کلی_کوډ_منزل_Sym(_this, (کلی_کوډ_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (بینښه صحيح)sym, sym == No_نښه ? "NoSymbol" : X11_XKeysym_منزل_String(sym));
            }
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } وإلا {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#د_که_پای
            معلومات->keyboard.کلی_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_سېټ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    أرجع true;
}

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
ساكن بینښه صحيح X11_Get_Xkb_Virtual_Modifier_ماسک(SDL_VideoDevice *_this, ثابت حرف *vmod_name)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    بینښه صحيح mod_ماسک = 0;

    ثابت Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    إذا (vmod != None) {
        لكل (صحيح i = 0; i < Xkb_عدد_Virtual_Mods; ++i) {
            إذا (vmod == videodata->keyboard.xkb.desc_ptr->نومونه->vmods[i]) {
                mod_ماسک = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                اكسر;
            }
        }
    }

    أرجع mod_ماسک;
}
#د_که_پای

ساكن بینښه X11_Get_XModifier_ماسک(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    Display *display = videodata->display;
    بینښه صحيح mod_ماسک = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    بینښه صحيح n = xmods->max_keypermod;
    لكل (صحيح i = 3; i < 8; i++) {
        لكل (صحيح j = 0; j < n; j++) {
            ثابت کلی_کوډ_2 kc = xmods->modifiermap[i * n + j];
            إذا (videodata->keyboard.کلی_layout[kc] == scancode) {
                mod_ماسک = 1 << i;
                اكسر;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    أرجع mod_ماسک;
}

ساكن فراغ X11_جمع_کړه_Keymap_ثبت(SDL_Keymap *keymap, Uint32 xkeycode, کلی_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_ماسک)
{
    SDL_Keycode keycode = SDL_Get_کلی_کوډ_From_کلی_Sym(xkeysym, xkeycode, sdl_mod_ماسک);

    إذا (!keycode) {
        بدل (sdl_scancode) {
        حالة SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            اكسر;
        حالة SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            اكسر;
        حالة SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            اكسر;
        حالة SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            اكسر;
        افتراضي:
            keycode = SDL_SCANCODE_منزل_KEYCODE(sdl_scancode);
            اكسر;
        }
    }

    SDL_سېټ_Keymap_ثبت(keymap, sdl_scancode, sdl_mod_ماسک, keycode);
}

فراغ X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_Video_معلومات *معلومات = _this->دننی;

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (معلومات->keyboard.xkb_enabled) {
        XkbStateRec state;

        لكل (بینښه صحيح i = 0; i < Xkb_عدد_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(معلومات->keyboard.xkb.keymaps[i]);
            معلومات->keyboard.xkb.keymaps[i] = عدم;
        }

        X11_Xkb_Get_نومونه(معلومات->display, Xkb_Virtual_Mod_نومونه_ماسک, معلومات->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(معلومات->display, Xkb_All_Client_Info_ماسک | Xkb_Virtual_Mods_ماسک, معلومات->keyboard.xkb.desc_ptr);

        إذا (X11_XkbGetState(معلومات->display, XkbUseCoreKbd, &state) == Success) {
            معلومات->keyboard.xkb.current_ډله = state.ډله;
        }

        معلومات->keyboard.alt_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "Alt");
        إذا (!معلومات->keyboard.alt_ماسک) {
            معلومات->keyboard.alt_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "Meta");
        }
        معلومات->keyboard.gui_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "Super");
        معلومات->keyboard.level3_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "LevelThree");
        معلومات->keyboard.level5_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "LevelFive");
        معلومات->keyboard.numlock_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "NumLock");
        معلومات->keyboard.scrolllock_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "ScrollLock");

        لكل (بینښه صحيح i = 0; i < Xkb_عدد_Kbd_Groups; ++i) {
            معلومات->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            إذا (!معلومات->keyboard.xkb.keymaps[i]) {
                لكل (بینښه صحيح j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(معلومات->keyboard.xkb.keymaps[i]);
                    معلومات->keyboard.xkb.keymaps[j] = عدم;
                }

                أرجع;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ثابت Uint32 valid_mod_ماسک = ښويدنه_ماسک_2 | قلف_ماسک | معلومات->keyboard.alt_ماسک | معلومات->keyboard.level3_ماسک | معلومات->keyboard.level5_ماسک;

        لكل (Uint32 xkeycode = معلومات->keyboard.xkb.desc_ptr->min_کلی_کوډ; xkeycode < معلومات->keyboard.xkb.desc_ptr->max_کلی_کوډ; ++xkeycode) {
            ثابت SDL_Scancode scancode = معلومات->keyboard.کلی_layout[xkeycode];
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                استمر;
            }

            لكل (Uint32 ډله = 0; ډله < Xkb_عدد_Kbd_Groups; ++ډله) {
                SDL_Keymap *keymap = معلومات->keyboard.xkb.keymaps[ډله];

                Uint32 effective_ډله = ډله;
                ثابت بینښه حرف max_کلی_ډله = Xkb_کلی_عدد_Groups(معلومات->keyboard.xkb.desc_ptr, xkeycode);
                ثابت بینښه حرف کلی_ډله_info = Xkb_کلی_ډله_Info(معلومات->keyboard.xkb.desc_ptr, xkeycode);

                إذا (max_کلی_ډله && effective_ډله >= max_کلی_ډله) {
                    ثابت بینښه حرف action = Xkb_بهر_د_Range_ډله_Action(کلی_ډله_info);

                    بدل (action) {
                    افتراضي:
                        effective_ډله %= max_کلی_ډله;
                        اكسر;
                    حالة XkbClampIntoRange:
                        effective_ډله = max_کلی_ډله - 1;
                        اكسر;
                    حالة XkbRedirectIntoRange:
                        effective_ډله = Xkb_بهر_د_Range_ډله_شمېره(کلی_ډله_info);
                        إذا (effective_ډله >= max_کلی_ډله) {
                            effective_ډله = 0;
                        }
                        اكسر;
                    }
                }

                Xkb_کلی_Type_Ptr کلی_type = Xkb_کلی_کلی_Type(معلومات->keyboard.xkb.desc_ptr, xkeycode, effective_ډله);

                لكل (Uint32 level = 0; level < کلی_type->عدد_پوړونه; ++level) {
                    ثابت کلی_Sym keysym = X11_کلی_کوډ_منزل_Sym(_this, xkeycode, effective_ډله, level);

                    إذا (keysym != No_نښه) {
                        bool کلی_added = false;

                        لكل (صحيح map_idx = 0; map_idx < کلی_type->map_شمېر; ++map_idx) {
                            إذا (کلی_type->map[map_idx].فعال && کلی_type->map[map_idx].level == level) {
                                ثابت بینښه صحيح xkb_mod_ماسک = کلی_type->map[map_idx].mods.ماسک;
                                إذا ((xkb_mod_ماسک | valid_mod_ماسک) == valid_mod_ماسک) {
                                    ثابت SDL_Keymod sdl_mod_ماسک = (xkb_mod_ماسک & ښويدنه_ماسک_2 ? SDL_KMOD_ښويدنه : 0) |
                                                                    (xkb_mod_ماسک & قلف_ماسک ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_ماسک & معلومات->keyboard.alt_ماسک ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_ماسک & معلومات->keyboard.level3_ماسک ? SDL_KMOD_ډېرپېښ : 0) |
                                                                    (xkb_mod_ماسک & معلومات->keyboard.level5_ماسک ? SDL_KMOD_LEVEL5 : 0);

                                    X11_جمع_کړه_Keymap_ثبت(keymap, xkeycode, keysym, scancode, sdl_mod_ماسک);
                                    کلی_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        إذا (!level && !کلی_added) {
                            X11_جمع_کړه_Keymap_ثبت(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_سېټ_Keymap(معلومات->keyboard.xkb.keymaps[معلومات->keyboard.xkb.current_ډله], send_event);
    } وإلا
#د_که_پای
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        إذا (!keymap) {
            أرجع;
        }

        إذا (send_event) {
            إذا (معلومات->keyboard.core.keysym_map) {
                X11_XFree(معلومات->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(معلومات->display, &معلومات->keyboard.core.min_keycode, &معلومات->keyboard.core.max_keycode);
            معلومات->keyboard.core.keysym_map = X11_XGetKeyboardMapping(معلومات->display, معلومات->keyboard.core.min_keycode,
                                                                     معلومات->keyboard.core.max_keycode - معلومات->keyboard.core.min_keycode,
                                                                     &معلومات->keyboard.core.keysyms_فی_کلی);
        }

        لكل (Uint32 xkeycode = معلومات->keyboard.core.min_keycode; xkeycode <= معلومات->keyboard.core.max_keycode; ++xkeycode) {
            ثابت SDL_Scancode scancode = معلومات->keyboard.کلی_layout[xkeycode];
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                استمر;
            }

            ثابت کلی_Sym keysym = X11_کلی_کوډ_منزل_Sym(_this, xkeycode, 0, 0);
            إذا (keysym != No_نښه) {
                X11_جمع_کړه_Keymap_ثبت(keymap, xkeycode, keysym, scancode, 0);
            }
        }

        معلومات->keyboard.alt_ماسک = Mod1_ماسک; // Alt or Meta
        معلومات->keyboard.gui_ماسک = Mod4_ماسک; // Super
        معلومات->keyboard.level3_ماسک = Mod5_ماسک; // Note: Not a typo, Mod5 = level 3 shift, and Mod3 = level 5 shift.
        معلومات->keyboard.level5_ماسک = Mod3_ماسک;
        معلومات->keyboard.numlock_ماسک = X11_Get_XModifier_ماسک(_this, SDL_SCANCODE_NUMLOCKCLEAR);
        معلومات->keyboard.scrolllock_ماسک = X11_Get_XModifier_ماسک(_this, SDL_SCANCODE_SCROLLLOCK);

        SDL_سېټ_Keymap(keymap, send_event);
    }
}

فراغ X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->دننی;

#که_تعریف_شوی X_HAVE_UTF8_STRING
    إذا (معلومات->im) {
        X11_XCloseIM(معلومات->im);
        معلومات->im = عدم;
    } وإلا {
        X11_XUnregisterIMInstantiateCallback(معلومات->display, عدم, عدم, عدم, im_instantiate_handler, (XPointer)معلومات);
    }
#د_که_پای // X_HAVE_UTF8_STRING

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (معلومات->keyboard.xkb_enabled) {
        لكل (صحيح i = 0; i < Xkb_عدد_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(معلومات->keyboard.xkb.keymaps[i]);
            معلومات->keyboard.xkb.keymaps[i] = عدم;
        }

        إذا (معلومات->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(معلومات->keyboard.xkb.desc_ptr, 0, True);
            معلومات->keyboard.xkb.desc_ptr = عدم;
        }
    } وإلا
#د_که_پای
        إذا (معلومات->keyboard.core.keysym_map) {
        X11_XFree(معلومات->keyboard.core.keysym_map);
        معلومات->keyboard.core.keysym_map = عدم;
    }
}

فراغ X11_ClearComposition(SDL_کړکۍ_معلومات *معلومات)
{
    إذا (معلومات->preedit_اوږدتیا > 0) {
        معلومات->preedit_متن[0] = '\0';
        معلومات->preedit_اوږدتیا = 0;
    }

    إذا (معلومات->ime_needs_clear_composition) {
        SDL_Send_Editing_متن("", 0, 0);
        معلومات->ime_needs_clear_composition = false;
    }
}

ساكن فراغ X11_SendEditingEvent(SDL_کړکۍ_معلومات *معلومات)
{
    إذا (معلومات->preedit_اوږدتیا == 0) {
        X11_ClearComposition(معلومات);
        أرجع;
    }

    bool دننه_highlight = false;
    صحيح پیل = -1, اوږدتیا = 0, i;
    لكل (i = 0; i < معلومات->preedit_اوږدتیا; ++i) {
        إذا (معلومات->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            إذا (پیل < 0) {
                پیل = i;
                دننه_highlight = true;
            }
        } وإلا إذا (دننه_highlight) {
            // Found the end of the highlight
            اكسر;
        }
    }
    إذا (دننه_highlight) {
        اوږدتیا = (i - پیل);
    } وإلا {
        پیل = SDL_clamp(معلومات->preedit_cursor, 0, معلومات->preedit_اوږدتیا);
    }
    SDL_Send_Editing_متن(معلومات->preedit_متن, پیل, اوږدتیا);

    معلومات->ime_needs_clear_composition = true;
}

#که_تعریف_شوی X_HAVE_UTF8_STRING
ساكن صحيح preedit_پیل_callback(XIC xic, XPointer client_معلومات_2, XPointer call_معلومات_2)
{
    // No limit on preedit text length
    أرجع -1;
}

ساكن فراغ preedit_بشپړ_callback(XIC xic, XPointer client_معلومات_2, XPointer call_معلومات_2)
{
}

ساكن فراغ preedit_draw_callback(XIC xic, XPointer client_معلومات_2, XIMPreeditDrawCallbackStruct *call_معلومات_2)
{
    SDL_کړکۍ_معلومات *معلومات = (SDL_کړکۍ_معلومات *)client_معلومات_2;
    صحيح chg_لومړی = SDL_clamp(call_معلومات_2->chg_لومړی, 0, معلومات->preedit_اوږدتیا);
    صحيح chg_اوږدتیا = SDL_clamp(call_معلومات_2->chg_اوږدتیا, 0, معلومات->preedit_اوږدتیا - chg_لومړی);

    ثابت حرف *پیل = معلومات->preedit_متن;
    إذا (chg_اوږدتیا > 0) {
        // Delete text in range
        لكل (صحيح i = 0; پیل && *پیل && i < chg_لومړی; ++i) {
            SDL_ګام_UTF8(&پیل, عدم);
        }

        ثابت حرف *پای_ټکی = پیل;
        لكل (صحيح i = 0; پای_ټکی && *پای_ټکی && i < chg_اوږدتیا; ++i) {
            SDL_ګام_UTF8(&پای_ټکی, عدم);
        }

        إذا (پای_ټکی > پیل) {
            SDL_memmove((حرف *)پیل, پای_ټکی, SDL_strlen(پای_ټکی) + 1);
            إذا ((chg_لومړی + chg_اوږدتیا) > معلومات->preedit_اوږدتیا) {
                SDL_memmove(&معلومات->preedit_feedback[chg_لومړی], &معلومات->preedit_feedback[chg_لومړی + chg_اوږدتیا], (معلومات->preedit_اوږدتیا - chg_لومړی - chg_اوږدتیا) * حجم(*معلومات->preedit_feedback));
            }
        }
        معلومات->preedit_اوږدتیا -= chg_اوږدتیا;
    }

    XIMText *متن = call_معلومات_2->متن;
    إذا (متن) {
        // Insert text in range
        SDL_assert(!متن->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        إذا (متن->string.multi_byte) {
            متن->اوږدتیا = SDL_utf8strlen(متن->string.multi_byte);
        }

        size_t string_اندازه = SDL_strlen(متن->string.multi_byte);
        size_t اندازه = string_اندازه + 1;
        إذا (معلومات->preedit_متن) {
            اندازه += SDL_strlen(معلومات->preedit_متن);
        }
        حرف *preedit_متن = (حرف *)SDL_malloc(اندازه * حجم(*preedit_متن));
        إذا (preedit_متن) {
            size_t pre_اندازه = (پیل - معلومات->preedit_متن);
            size_t post_اندازه = پیل ? SDL_strlen(پیل) : 0;
            إذا (pre_اندازه > 0) {
                SDL_memcpy(&preedit_متن[0], معلومات->preedit_متن, pre_اندازه);
            }
            SDL_memcpy(&preedit_متن[pre_اندازه], متن->string.multi_byte, string_اندازه);
            إذا (post_اندازه > 0) {
                SDL_memcpy(&preedit_متن[pre_اندازه + string_اندازه], پیل, post_اندازه);
            }
            preedit_متن[اندازه - 1] = '\0';
        }

        size_t feedback_اندازه = معلومات->preedit_اوږدتیا + متن->اوږدتیا;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_اندازه * حجم(*feedback));
        إذا (feedback) {
            size_t pre_اندازه = (size_t)chg_لومړی;
            size_t post_اندازه = (size_t)معلومات->preedit_اوږدتیا - pre_اندازه;
            إذا (pre_اندازه > 0) {
                SDL_memcpy(&feedback[0], معلومات->preedit_feedback, pre_اندازه * حجم(*feedback));
            }
            SDL_memcpy(&feedback[pre_اندازه], متن->feedback, متن->اوږدتیا * حجم(*feedback));
            إذا (post_اندازه > 0) {
                SDL_memcpy(&feedback[pre_اندازه + متن->اوږدتیا], &معلومات->preedit_feedback[pre_اندازه], post_اندازه * حجم(*feedback));
            }
        }

        إذا (preedit_متن && feedback) {
            SDL_free(معلومات->preedit_متن);
            معلومات->preedit_متن = preedit_متن;

            SDL_free(معلومات->preedit_feedback);
            معلومات->preedit_feedback = feedback;

            معلومات->preedit_اوږدتیا += متن->اوږدتیا;
        } وإلا {
            SDL_free(preedit_متن);
            SDL_free(feedback);
        }
    }

    معلومات->preedit_cursor = call_معلومات_2->caret;

#که_تعریف_شوی DEBUG_XIM
    إذا (call_معلومات_2->chg_اوږدتیا > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_معلومات_2->chg_اوږدتیا, call_معلومات_2->chg_لومړی);
    }
    إذا (متن) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", متن->string.multi_byte, call_معلومات_2->chg_لومړی, call_معلومات_2->caret);
    }
    SDL_Log("Pre-edit text: %s", معلومات->preedit_متن);
#د_که_پای

    X11_SendEditingEvent(معلومات);
}

ساكن فراغ preedit_caret_callback(XIC xic, XPointer client_معلومات_2, XIMPreeditCaretCallbackStruct *call_معلومات_2)
{
    SDL_کړکۍ_معلومات *معلومات = (SDL_کړکۍ_معلومات *)client_معلومات_2;

    بدل (call_معلومات_2->direction) {
    حالة XIMAbsolutePosition:
        إذا (call_معلومات_2->position != معلومات->preedit_cursor) {
            معلومات->preedit_cursor = call_معلومات_2->position;
            X11_SendEditingEvent(معلومات);
        }
        اكسر;
    حالة XIMDontChange:
        اكسر;
    افتراضي:
        // Not currently supported
        اكسر;
    }
}

ساكن فراغ ic_destroyed_handler(XIC ic, XPointer client_معلومات, XPointer call_معلومات)
{
    SDL_کړکۍ_معلومات *معلومات = (SDL_کړکۍ_معلومات *)client_معلومات;
    معلومات->ic = عدم;
    X11_Destroy_ننوت_Context(معلومات);

    // If the IM was already recreated, create a new IC.
    إذا (معلومات->videodata->im) {
        X11_Create_ننوت_Context(معلومات);
    }
}
#د_که_پای // X_HAVE_UTF8_STRING

فراغ X11_Create_ننوت_Context(SDL_کړکۍ_معلومات *معلومات)
{
#که_تعریف_شوی X_HAVE_UTF8_STRING
    SDL_Video_معلومات *videodata = معلومات->videodata;

    إذا (SDL_X11_HAVE_UTF8 && videodata->im) {
        ثابت حرف *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_معلومات_2 = (XPointer)معلومات;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        إذا (hint && SDL_strstr(hint, "composition")) {
            XIMCallback draw_callback;
            draw_callback.client_معلومات_2 = (XPointer)معلومات;
            draw_callback.callback = (XIMProc)preedit_draw_callback;

            XIMCallback پیل_callback;
            پیل_callback.client_معلومات_2 = (XPointer)معلومات;
            پیل_callback.callback = (XIMProc)preedit_پیل_callback;

            XIMCallback بشپړ_callback;
            بشپړ_callback.client_معلومات_2 = (XPointer)معلومات;
            بشپړ_callback.callback = (XIMProc)preedit_بشپړ_callback;

            XIMCallback caret_callback;
            caret_callback.client_معلومات_2 = (XPointer)معلومات;
            caret_callback.callback = (XIMProc)preedit_caret_callback;

            XVaNestedList attr = X11_XVaCreateNestedList(0,
                                                         XNPreedit_پیل_Callback, &پیل_callback,
                                                         XNPreedit_بشپړ_Callback, &بشپړ_callback,
                                                         XNPreeditDrawCallback, &draw_callback,
                                                         XNPreeditCaretCallback, &caret_callback,
                                                         عدم);
            إذا (attr) {
                معلومات->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreedit_ځانګړتیاوې, attr,
                                         XNClient_کړکۍ, معلومات->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         عدم);
                X11_XFree(attr);
            }
        }
        إذا (!معلومات->ic) {
            معلومات->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClient_کړکۍ, معلومات->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     عدم);
        }
        معلومات->xim_spot.x = -1;
        معلومات->xim_spot.y = -1;
    }
#د_که_پای // X_HAVE_UTF8_STRING
}


فراغ X11_Destroy_ننوت_Context(SDL_کړکۍ_معلومات *معلومات)
{
#که_تعریف_شوی X_HAVE_UTF8_STRING
    إذا (معلومات->ic) {
        X11_XDestroyIC(معلومات->ic);
        معلومات->ic = عدم;
    }
    SDL_free(معلومات->preedit_متن);
    SDL_free(معلومات->preedit_feedback);
    معلومات->preedit_متن = عدم;
    معلومات->preedit_feedback = عدم;
#د_که_پای
}

ساكن فراغ X11_ResetXIM(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#که_تعریف_شوی X_HAVE_UTF8_STRING
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

    إذا (معلومات && معلومات->ic) {
        // Clear any partially entered dead keys
        حرف *contents = X11_Xutf8ResetIC(معلومات->ic);
        إذا (contents) {
            X11_XFree(contents);
        }
    }
#د_که_پای // X_HAVE_UTF8_STRING
}

bool X11_پیل_متن_ننوت(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, کړکۍ);

    أرجع X11_Update_متن_ننوت_Area(_this, کړکۍ);
}

bool X11_Stop_متن_ننوت(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    X11_ResetXIM(_this, کړکۍ);
    أرجع true;
}

bool X11_Update_متن_ننوت_Area(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#که_تعریف_شوی X_HAVE_UTF8_STRING
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

    إذا (معلومات && معلومات->ic) {
        XPoint spot;
        spot.x = کړکۍ->متن_ننوت_rect.x + کړکۍ->متن_ننوت_cursor;
        spot.y = کړکۍ->متن_ننوت_rect.y + کړکۍ->متن_ننوت_rect.h;
        إذا (spot.x != معلومات->xim_spot.x || spot.y != معلومات->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, عدم);
            إذا (attr) {
                X11_XSetICValues(معلومات->ic, XNPreedit_ځانګړتیاوې, attr, عدم);
                X11_XFree(attr);
            }
            SDL_copyp(&معلومات->xim_spot, &spot);
        }
    }
#د_که_پای
    أرجع true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    أرجع videodata->use_steam_screen_keyboard;
}

فراغ X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props)
{
    SDL_Video_معلومات *videodata = _this->دننی;

    إذا (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ثابت صحيح k_EFloating_Gamepad_متن_ننوت_ډېرپېښ_ډېرپېښ_Single_کرښه = 0;    // Enter dismisses the keyboard
        ثابت صحيح k_EFloating_Gamepad_متن_ننوت_ډېرپېښ_ډېرپېښ_مضرب_کرښې = 1; // User needs to explicitly dismiss the keyboard
        ثابت صحيح k_EFloating_Gamepad_متن_ننوت_ډېرپېښ_ډېرپېښ_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ثابت صحيح k_EFloating_Gamepad_متن_ننوت_ډېرپېښ_ډېرپېښ_Numeric = 3;       // Numeric keypad is shown
        حرف deeplink[128];
        صحيح ډېرپېښ;

        بدل (SDL_Get_متن_ننوت_Type(props)) {
        حالة SDL_TEXTINPUT_TYPE_متن_EMAIL:
            ډېرپېښ = k_EFloating_Gamepad_متن_ننوت_ډېرپېښ_ډېرپېښ_Email;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_شمېره:
        حالة SDL_TEXTINPUT_TYPE_شمېره_PASSWORD_HIDDEN:
        حالة SDL_TEXTINPUT_TYPE_شمېره_PASSWORD_VISIBLE:
            ډېرپېښ = k_EFloating_Gamepad_متن_ننوت_ډېرپېښ_ډېرپېښ_Numeric;
            اكسر;
        افتراضي:
            إذا (SDL_Get_متن_ننوت_Multiline(props)) {
                ډېرپېښ = k_EFloating_Gamepad_متن_ننوت_ډېرپېښ_ډېرپېښ_مضرب_کرښې;
            } وإلا {
                ډېرپېښ = k_EFloating_Gamepad_متن_ننوت_ډېرپېښ_ډېرپېښ_Single_کرښه;
            }
            اكسر;
        }
        (فراغ)SDL_snprintf(deeplink, حجم(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           کړکۍ->متن_ننوت_rect.x, کړکۍ->متن_ننوت_rect.y,
                           کړکۍ->متن_ننوت_rect.w, کړکۍ->متن_ننوت_rect.h,
                           ډېرپېښ);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

فراغ X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *videodata = _this->دننی;

    إذا (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#د_که_پای // SDL_VIDEO_DRIVER_X11
