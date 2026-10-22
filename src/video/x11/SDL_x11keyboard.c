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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"

#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_scancode_tables_c.h"

#ضمن <X11/keysym.h>

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#ضمن <X11/XKBlib.h>
#جيڪڏهن_پورو

#ضمن "../../events/imKStoUCS.h"
#ضمن "../../events/SDL_keysym_to_scancode_c.h"
#ضمن "../../events/SDL_keysym_to_keycode_c.h"

#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
#ضمن <locale.h>
#جيڪڏهن_پورو

ساكن SDL_Scancode_جدول scancode_سيٽ[] = {
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

ساكن ڪنجي_Sym X11_ڪنجي_ڪوڊ_منزل_Sym(SDL_VideoDevice *_this, ڪنجي_ڪوڊ_2 keycode, بنانشان صحيح گروهه, بنانشان صحيح level)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    ڪنجي_Sym keysym;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (معلومات->keyboard.xkb_enabled) {
        keysym = X11_Xkb_Keycode_منزل_Keysym(معلومات->display, keycode, گروهه, level);
    } وإلا
#جيڪڏهن_پورو
    {
        // TODO: Handle groups on the legacy path.
        إذا (keycode >= معلومات->keyboard.core.min_keycode && keycode <= معلومات->keyboard.core.max_keycode) {
            keysym = معلومات->keyboard.core.keysym_map[(keycode - معلومات->keyboard.core.min_keycode) * معلومات->keyboard.core.keysyms_في_ڪنجي];
        } وإلا {
            keysym = No_نشان;
        }
    }

    أرجع keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
ساكن SDL_Scancode X11_ڪنجي_ڪوڊ_منزل_SDLScancode(SDL_VideoDevice *_this, ڪنجي_ڪوڊ_2 keycode)
{
    ثابت ڪنجي_Sym keysym = X11_ڪنجي_ڪوڊ_منزل_Sym(_this, keycode, 0, 0);

    إذا (keysym == No_نشان) {
        أرجع SDL_SCANCODE_UNKNOWN;
    }

    أرجع SDL_Get_Scancode_From_ڪنجي_Sym(keysym, keycode);
}

#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
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
            SDL_دري_معلومات *w = videodata->windowlist[i];
            إذا (!w->ic) {
                X11_Create_داخلا_Context(w);
            }
        }

        أرجع true;
    }

    أرجع false;
}
#جيڪڏهن_پورو // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    صحيح i = 0;
    صحيح j = 0;
    صحيح min_keycode, max_keycode;
    بنية
    {
        SDL_Scancode scancode;
        ڪنجي_Sym keysym;
        صحيح قدر;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_اڳواٽ, 0 },
        { SDL_SCANCODE_مٿي, XK_مٿي, 0 },
        { SDL_SCANCODE_کاٻو, XK_کاٻو, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    صحيح بهترين_مفاصلو;
    صحيح بهترين_اشاريو;
    صحيح مفاصلو;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    صحيح xkb_major = Xkb_Major_نسخو;
    صحيح xkb_minor = Xkb_Minor_نسخو;

    إذا (X11_XkbQueryExtension(معلومات->display, عدم, &معلومات->keyboard.xkb.event, عدم, &xkb_major, &xkb_minor)) {
        Bool xkb_repeat = 0;
        معلومات->keyboard.xkb_enabled = true;
        معلومات->keyboard.xkb.desc_ptr = X11_XkbGetMap(معلومات->display, Xkb_All_Client_Info_نقاب, XkbUseCoreKbd);

        // This will remove KeyRelease events for held keys.
        X11_Xkb_سيٽ_Detectable_Auto_Repeat(معلومات->display, True, &xkb_repeat);

        // Enable the key mapping and state events.
        X11_XkbSelectEvents(معلومات->display, XkbUseCoreKbd,
                            Xkb_New_Keyboard_Notify_نقاب | Xkb_Map_Notify_نقاب | Xkb_State_Notify_نقاب,
                            Xkb_New_Keyboard_Notify_نقاب | Xkb_Map_Notify_نقاب | Xkb_State_Notify_نقاب);
        X11_XkbSelectEventDetails(معلومات->display, XkbUseCoreKbd, XkbStateNotify, Xkb_گروهه_State_نقاب | Xkb_Modifier_State_نقاب, Xkb_گروهه_State_نقاب | Xkb_Modifier_State_نقاب);
    } وإلا
#جيڪڏهن_پورو
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(معلومات->display, &معلومات->keyboard.core.min_keycode, &معلومات->keyboard.core.max_keycode);
        معلومات->keyboard.core.keysym_map = X11_XGetKeyboardMapping(معلومات->display, معلومات->keyboard.core.min_keycode,
                                                              معلومات->keyboard.core.max_keycode - معلومات->keyboard.core.min_keycode,
                                                              &معلومات->keyboard.core.keysyms_في_ڪنجي);
    }

    // Open a connection to the X input manager
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
    إذا (SDL_X11_HAVE_UTF8) {
        إذا (!X11_InitIM(معلومات)) {
            X11_XRegisterIMInstantiateCallback(معلومات->display, عدم, عدم, عدم, im_instantiate_handler, (XPointer)معلومات);
        }
    }
#جيڪڏهن_پورو
    // Try to determine which scancodes are being used based on fingerprint
    بهترين_مفاصلو = SDL_arraysize(fingerprint) + 1;
    بهترين_اشاريو = -1;
    X11_XDisplayKeycodes(معلومات->display, &min_keycode, &max_keycode);
    لكل (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].قدر = X11_XKeysym_منزل_Keycode(معلومات->display, fingerprint[i].keysym) - min_keycode;
    }
    لكل (i = 0; i < SDL_arraysize(scancode_سيٽ); ++i) {
        صحيح جدول_سائيز;
        ثابت SDL_Scancode *جدول = SDL_Get_Scancode_جدول(scancode_سيٽ[i], &جدول_سائيز);

        مفاصلو = 0;
        لكل (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            إذا (fingerprint[j].قدر < 0 || fingerprint[j].قدر >= جدول_سائيز) {
                مفاصلو += 1;
            } وإلا إذا (جدول[fingerprint[j].قدر] != fingerprint[j].scancode) {
                مفاصلو += 1;
            }
        }
        إذا (مفاصلو < بهترين_مفاصلو) {
            بهترين_مفاصلو = مفاصلو;
            بهترين_اشاريو = i;
        }
    }
    إذا (بهترين_اشاريو < 0 || بهترين_مفاصلو > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        صحيح fingerprint_قدر = X11_XKeysym_منزل_Keycode(معلومات->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        إذا (fingerprint_قدر == 235) {
            لكل (i = 0; i < SDL_arraysize(scancode_سيٽ); ++i) {
                إذا (scancode_سيٽ[i] == SDL_SCANCODE_جدول_XFREE86_2) {
                    بهترين_اشاريو = i;
                    بهترين_مفاصلو = 0;
                    اكسر;
                }
            }
        }
    }
    إذا (بهترين_اشاريو >= 0 && بهترين_مفاصلو <= 2) {
        صحيح جدول_سائيز;
        ثابت SDL_Scancode *جدول = SDL_Get_Scancode_جدول(scancode_سيٽ[بهترين_اشاريو], &جدول_سائيز);

#جيڪڏهن_وصف_ٿيل DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", بهترين_اشاريو, min_keycode, max_keycode, جدول_سائيز);
#جيڪڏهن_پورو
        // This should never happen, but just in case...
        إذا (جدول_سائيز > (SDL_arraysize(معلومات->keyboard.ڪنجي_layout) - min_keycode)) {
            جدول_سائيز = (SDL_arraysize(معلومات->keyboard.ڪنجي_layout) - min_keycode);
        }
        SDL_memcpy(&معلومات->keyboard.ڪنجي_layout[min_keycode], جدول, حجم(SDL_Scancode) * جدول_سائيز);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        لكل (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_ڪنجي_ڪوڊ_منزل_SDLScancode(_this, i);
#جيڪڏهن_وصف_ٿيل DEBUG_KEYBOARD
            {
                ڪنجي_Sym sym;
                sym = X11_ڪنجي_ڪوڊ_منزل_Sym(_this, (ڪنجي_ڪوڊ_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (بنانشان صحيح)sym, sym == No_نشان ? "NoSymbol" : X11_XKeysym_منزل_String(sym));
            }
#جيڪڏهن_پورو
            إذا (scancode == معلومات->keyboard.ڪنجي_layout[i]) {
                استمر;
            }
            إذا ((SDL_GetKeymapKeycode(عدم, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_نقاب | SDLK_EXTENDED_نقاب)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#جيڪڏهن_وصف_ٿيل DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", معلومات->ڪنجي_layout[i], SDL_GetScancodeName(معلومات->ڪنجي_layout[i]), scancode, SDL_GetScancodeName(scancode));
#جيڪڏهن_پورو
                معلومات->keyboard.ڪنجي_layout[i] = scancode;
            }
        }
    } وإلا {
#جيڪڏهن_وصف_ٿيل DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#جيڪڏهن_پورو

        // Determine key_layout - only works on US QWERTY layout
        لكل (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_ڪنجي_ڪوڊ_منزل_SDLScancode(_this, i);
#جيڪڏهن_وصف_ٿيل DEBUG_SCANCODES
            {
                ڪنجي_Sym sym;
                sym = X11_ڪنجي_ڪوڊ_منزل_Sym(_this, (ڪنجي_ڪوڊ_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (بنانشان صحيح)sym, sym == No_نشان ? "NoSymbol" : X11_XKeysym_منزل_String(sym));
            }
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } وإلا {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#جيڪڏهن_پورو
            معلومات->keyboard.ڪنجي_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_سيٽ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    أرجع true;
}

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
ساكن بنانشان صحيح X11_Get_Xkb_Virtual_Modifier_نقاب(SDL_VideoDevice *_this, ثابت حرف *vmod_name)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    بنانشان صحيح mod_نقاب = 0;

    ثابت Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    إذا (vmod != None) {
        لكل (صحيح i = 0; i < Xkb_انگ_Virtual_Mods; ++i) {
            إذا (vmod == videodata->keyboard.xkb.desc_ptr->نالا->vmods[i]) {
                mod_نقاب = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                اكسر;
            }
        }
    }

    أرجع mod_نقاب;
}
#جيڪڏهن_پورو

ساكن بنانشان X11_Get_XModifier_نقاب(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    Display *display = videodata->display;
    بنانشان صحيح mod_نقاب = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    بنانشان صحيح n = xmods->max_keypermod;
    لكل (صحيح i = 3; i < 8; i++) {
        لكل (صحيح j = 0; j < n; j++) {
            ثابت ڪنجي_ڪوڊ_2 kc = xmods->modifiermap[i * n + j];
            إذا (videodata->keyboard.ڪنجي_layout[kc] == scancode) {
                mod_نقاب = 1 << i;
                اكسر;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    أرجع mod_نقاب;
}

ساكن فراغ X11_جوڙيو_Keymap_داخلا(SDL_Keymap *keymap, Uint32 xkeycode, ڪنجي_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_نقاب)
{
    SDL_Keycode keycode = SDL_Get_ڪنجي_ڪوڊ_From_ڪنجي_Sym(xkeysym, xkeycode, sdl_mod_نقاب);

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

    SDL_سيٽ_Keymap_داخلا(keymap, sdl_scancode, sdl_mod_نقاب, keycode);
}

فراغ X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (معلومات->keyboard.xkb_enabled) {
        XkbStateRec state;

        لكل (بنانشان صحيح i = 0; i < Xkb_انگ_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(معلومات->keyboard.xkb.keymaps[i]);
            معلومات->keyboard.xkb.keymaps[i] = عدم;
        }

        X11_Xkb_Get_نالا(معلومات->display, Xkb_Virtual_Mod_نالا_نقاب, معلومات->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(معلومات->display, Xkb_All_Client_Info_نقاب | Xkb_Virtual_Mods_نقاب, معلومات->keyboard.xkb.desc_ptr);

        إذا (X11_XkbGetState(معلومات->display, XkbUseCoreKbd, &state) == Success) {
            معلومات->keyboard.xkb.current_گروهه = state.گروهه;
        }

        معلومات->keyboard.alt_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "Alt");
        إذا (!معلومات->keyboard.alt_نقاب) {
            معلومات->keyboard.alt_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "Meta");
        }
        معلومات->keyboard.gui_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "Super");
        معلومات->keyboard.level3_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "LevelThree");
        معلومات->keyboard.level5_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "LevelFive");
        معلومات->keyboard.numlock_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "NumLock");
        معلومات->keyboard.scrolllock_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "ScrollLock");

        لكل (بنانشان صحيح i = 0; i < Xkb_انگ_Kbd_Groups; ++i) {
            معلومات->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            إذا (!معلومات->keyboard.xkb.keymaps[i]) {
                لكل (بنانشان صحيح j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(معلومات->keyboard.xkb.keymaps[i]);
                    معلومات->keyboard.xkb.keymaps[j] = عدم;
                }

                أرجع;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ثابت Uint32 valid_mod_نقاب = سرڪايو_نقاب_2 | تالو_نقاب | معلومات->keyboard.alt_نقاب | معلومات->keyboard.level3_نقاب | معلومات->keyboard.level5_نقاب;

        لكل (Uint32 xkeycode = معلومات->keyboard.xkb.desc_ptr->min_ڪنجي_ڪوڊ; xkeycode < معلومات->keyboard.xkb.desc_ptr->max_ڪنجي_ڪوڊ; ++xkeycode) {
            ثابت SDL_Scancode scancode = معلومات->keyboard.ڪنجي_layout[xkeycode];
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                استمر;
            }

            لكل (Uint32 گروهه = 0; گروهه < Xkb_انگ_Kbd_Groups; ++گروهه) {
                SDL_Keymap *keymap = معلومات->keyboard.xkb.keymaps[گروهه];

                Uint32 effective_گروهه = گروهه;
                ثابت بنانشان حرف max_ڪنجي_گروهه = Xkb_ڪنجي_انگ_Groups(معلومات->keyboard.xkb.desc_ptr, xkeycode);
                ثابت بنانشان حرف ڪنجي_گروهه_info = Xkb_ڪنجي_گروهه_Info(معلومات->keyboard.xkb.desc_ptr, xkeycode);

                إذا (max_ڪنجي_گروهه && effective_گروهه >= max_ڪنجي_گروهه) {
                    ثابت بنانشان حرف action = Xkb_ٻاهريون_جو_Range_گروهه_Action(ڪنجي_گروهه_info);

                    بدل (action) {
                    افتراضي:
                        effective_گروهه %= max_ڪنجي_گروهه;
                        اكسر;
                    حالة XkbClampIntoRange:
                        effective_گروهه = max_ڪنجي_گروهه - 1;
                        اكسر;
                    حالة XkbRedirectIntoRange:
                        effective_گروهه = Xkb_ٻاهريون_جو_Range_گروهه_عدد(ڪنجي_گروهه_info);
                        إذا (effective_گروهه >= max_ڪنجي_گروهه) {
                            effective_گروهه = 0;
                        }
                        اكسر;
                    }
                }

                Xkb_ڪنجي_Type_Ptr ڪنجي_type = Xkb_ڪنجي_ڪنجي_Type(معلومات->keyboard.xkb.desc_ptr, xkeycode, effective_گروهه);

                لكل (Uint32 level = 0; level < ڪنجي_type->انگ_سطحون; ++level) {
                    ثابت ڪنجي_Sym keysym = X11_ڪنجي_ڪوڊ_منزل_Sym(_this, xkeycode, effective_گروهه, level);

                    إذا (keysym != No_نشان) {
                        bool ڪنجي_added = false;

                        لكل (صحيح map_idx = 0; map_idx < ڪنجي_type->map_ڳڻپ; ++map_idx) {
                            إذا (ڪنجي_type->map[map_idx].سرگرم && ڪنجي_type->map[map_idx].level == level) {
                                ثابت بنانشان صحيح xkb_mod_نقاب = ڪنجي_type->map[map_idx].mods.نقاب;
                                إذا ((xkb_mod_نقاب | valid_mod_نقاب) == valid_mod_نقاب) {
                                    ثابت SDL_Keymod sdl_mod_نقاب = (xkb_mod_نقاب & سرڪايو_نقاب_2 ? SDL_KMOD_سرڪايو : 0) |
                                                                    (xkb_mod_نقاب & تالو_نقاب ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_نقاب & معلومات->keyboard.alt_نقاب ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_نقاب & معلومات->keyboard.level3_نقاب ? SDL_KMOD_گهڻائي : 0) |
                                                                    (xkb_mod_نقاب & معلومات->keyboard.level5_نقاب ? SDL_KMOD_LEVEL5 : 0);

                                    X11_جوڙيو_Keymap_داخلا(keymap, xkeycode, keysym, scancode, sdl_mod_نقاب);
                                    ڪنجي_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        إذا (!level && !ڪنجي_added) {
                            X11_جوڙيو_Keymap_داخلا(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_سيٽ_Keymap(معلومات->keyboard.xkb.keymaps[معلومات->keyboard.xkb.current_گروهه], send_event);
    } وإلا
#جيڪڏهن_پورو
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
                                                                     &معلومات->keyboard.core.keysyms_في_ڪنجي);
        }

        لكل (Uint32 xkeycode = معلومات->keyboard.core.min_keycode; xkeycode <= معلومات->keyboard.core.max_keycode; ++xkeycode) {
            ثابت SDL_Scancode scancode = معلومات->keyboard.ڪنجي_layout[xkeycode];
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                استمر;
            }

            ثابت ڪنجي_Sym keysym = X11_ڪنجي_ڪوڊ_منزل_Sym(_this, xkeycode, 0, 0);
            إذا (keysym != No_نشان) {
                X11_جوڙيو_Keymap_داخلا(keymap, xkeycode, keysym, scancode, 0);
            }
        }

        معلومات->keyboard.alt_نقاب = Mod1_نقاب; // Alt or Meta
        معلومات->keyboard.gui_نقاب = Mod4_نقاب; // Super
        معلومات->keyboard.level3_نقاب = Mod5_نقاب; // Note: Not a typo, Mod5 = level 3 shift, and Mod3 = level 5 shift.
        معلومات->keyboard.level5_نقاب = Mod3_نقاب;
        معلومات->keyboard.numlock_نقاب = X11_Get_XModifier_نقاب(_this, SDL_SCANCODE_NUMLOCKCLEAR);
        معلومات->keyboard.scrolllock_نقاب = X11_Get_XModifier_نقاب(_this, SDL_SCANCODE_SCROLLLOCK);

        SDL_سيٽ_Keymap(keymap, send_event);
    }
}

فراغ X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
    إذا (معلومات->im) {
        X11_XCloseIM(معلومات->im);
        معلومات->im = عدم;
    } وإلا {
        X11_XUnregisterIMInstantiateCallback(معلومات->display, عدم, عدم, عدم, im_instantiate_handler, (XPointer)معلومات);
    }
#جيڪڏهن_پورو // X_HAVE_UTF8_STRING

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (معلومات->keyboard.xkb_enabled) {
        لكل (صحيح i = 0; i < Xkb_انگ_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(معلومات->keyboard.xkb.keymaps[i]);
            معلومات->keyboard.xkb.keymaps[i] = عدم;
        }

        إذا (معلومات->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(معلومات->keyboard.xkb.desc_ptr, 0, True);
            معلومات->keyboard.xkb.desc_ptr = عدم;
        }
    } وإلا
#جيڪڏهن_پورو
        إذا (معلومات->keyboard.core.keysym_map) {
        X11_XFree(معلومات->keyboard.core.keysym_map);
        معلومات->keyboard.core.keysym_map = عدم;
    }
}

فراغ X11_ClearComposition(SDL_دري_معلومات *معلومات)
{
    إذا (معلومات->preedit_ڊيگهائي > 0) {
        معلومات->preedit_متن[0] = '\0';
        معلومات->preedit_ڊيگهائي = 0;
    }

    إذا (معلومات->ime_needs_clear_composition) {
        SDL_Send_Editing_متن("", 0, 0);
        معلومات->ime_needs_clear_composition = false;
    }
}

ساكن فراغ X11_SendEditingEvent(SDL_دري_معلومات *معلومات)
{
    إذا (معلومات->preedit_ڊيگهائي == 0) {
        X11_ClearComposition(معلومات);
        أرجع;
    }

    bool اندريون_highlight = false;
    صحيح شروعات = -1, ڊيگهائي = 0, i;
    لكل (i = 0; i < معلومات->preedit_ڊيگهائي; ++i) {
        إذا (معلومات->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            إذا (شروعات < 0) {
                شروعات = i;
                اندريون_highlight = true;
            }
        } وإلا إذا (اندريون_highlight) {
            // Found the end of the highlight
            اكسر;
        }
    }
    إذا (اندريون_highlight) {
        ڊيگهائي = (i - شروعات);
    } وإلا {
        شروعات = SDL_clamp(معلومات->preedit_cursor, 0, معلومات->preedit_ڊيگهائي);
    }
    SDL_Send_Editing_متن(معلومات->preedit_متن, شروعات, ڊيگهائي);

    معلومات->ime_needs_clear_composition = true;
}

#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
ساكن صحيح preedit_شروعات_callback(XIC xic, XPointer client_معلومات_2, XPointer call_معلومات_2)
{
    // No limit on preedit text length
    أرجع -1;
}

ساكن فراغ preedit_پورو_callback(XIC xic, XPointer client_معلومات_2, XPointer call_معلومات_2)
{
}

ساكن فراغ preedit_draw_callback(XIC xic, XPointer client_معلومات_2, XIMPreeditDrawCallbackStruct *call_معلومات_2)
{
    SDL_دري_معلومات *معلومات = (SDL_دري_معلومات *)client_معلومات_2;
    صحيح chg_پهريون = SDL_clamp(call_معلومات_2->chg_پهريون, 0, معلومات->preedit_ڊيگهائي);
    صحيح chg_ڊيگهائي = SDL_clamp(call_معلومات_2->chg_ڊيگهائي, 0, معلومات->preedit_ڊيگهائي - chg_پهريون);

    ثابت حرف *شروعات = معلومات->preedit_متن;
    إذا (chg_ڊيگهائي > 0) {
        // Delete text in range
        لكل (صحيح i = 0; شروعات && *شروعات && i < chg_پهريون; ++i) {
            SDL_قدم_UTF8(&شروعات, عدم);
        }

        ثابت حرف *پڇاڙي = شروعات;
        لكل (صحيح i = 0; پڇاڙي && *پڇاڙي && i < chg_ڊيگهائي; ++i) {
            SDL_قدم_UTF8(&پڇاڙي, عدم);
        }

        إذا (پڇاڙي > شروعات) {
            SDL_memmove((حرف *)شروعات, پڇاڙي, SDL_strlen(پڇاڙي) + 1);
            إذا ((chg_پهريون + chg_ڊيگهائي) > معلومات->preedit_ڊيگهائي) {
                SDL_memmove(&معلومات->preedit_feedback[chg_پهريون], &معلومات->preedit_feedback[chg_پهريون + chg_ڊيگهائي], (معلومات->preedit_ڊيگهائي - chg_پهريون - chg_ڊيگهائي) * حجم(*معلومات->preedit_feedback));
            }
        }
        معلومات->preedit_ڊيگهائي -= chg_ڊيگهائي;
    }

    XIMText *متن = call_معلومات_2->متن;
    إذا (متن) {
        // Insert text in range
        SDL_assert(!متن->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        إذا (متن->string.multi_byte) {
            متن->ڊيگهائي = SDL_utf8strlen(متن->string.multi_byte);
        }

        size_t string_سائيز = SDL_strlen(متن->string.multi_byte);
        size_t سائيز = string_سائيز + 1;
        إذا (معلومات->preedit_متن) {
            سائيز += SDL_strlen(معلومات->preedit_متن);
        }
        حرف *preedit_متن = (حرف *)SDL_malloc(سائيز * حجم(*preedit_متن));
        إذا (preedit_متن) {
            size_t pre_سائيز = (شروعات - معلومات->preedit_متن);
            size_t post_سائيز = شروعات ? SDL_strlen(شروعات) : 0;
            إذا (pre_سائيز > 0) {
                SDL_memcpy(&preedit_متن[0], معلومات->preedit_متن, pre_سائيز);
            }
            SDL_memcpy(&preedit_متن[pre_سائيز], متن->string.multi_byte, string_سائيز);
            إذا (post_سائيز > 0) {
                SDL_memcpy(&preedit_متن[pre_سائيز + string_سائيز], شروعات, post_سائيز);
            }
            preedit_متن[سائيز - 1] = '\0';
        }

        size_t feedback_سائيز = معلومات->preedit_ڊيگهائي + متن->ڊيگهائي;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_سائيز * حجم(*feedback));
        إذا (feedback) {
            size_t pre_سائيز = (size_t)chg_پهريون;
            size_t post_سائيز = (size_t)معلومات->preedit_ڊيگهائي - pre_سائيز;
            إذا (pre_سائيز > 0) {
                SDL_memcpy(&feedback[0], معلومات->preedit_feedback, pre_سائيز * حجم(*feedback));
            }
            SDL_memcpy(&feedback[pre_سائيز], متن->feedback, متن->ڊيگهائي * حجم(*feedback));
            إذا (post_سائيز > 0) {
                SDL_memcpy(&feedback[pre_سائيز + متن->ڊيگهائي], &معلومات->preedit_feedback[pre_سائيز], post_سائيز * حجم(*feedback));
            }
        }

        إذا (preedit_متن && feedback) {
            SDL_free(معلومات->preedit_متن);
            معلومات->preedit_متن = preedit_متن;

            SDL_free(معلومات->preedit_feedback);
            معلومات->preedit_feedback = feedback;

            معلومات->preedit_ڊيگهائي += متن->ڊيگهائي;
        } وإلا {
            SDL_free(preedit_متن);
            SDL_free(feedback);
        }
    }

    معلومات->preedit_cursor = call_معلومات_2->caret;

#جيڪڏهن_وصف_ٿيل DEBUG_XIM
    إذا (call_معلومات_2->chg_ڊيگهائي > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_معلومات_2->chg_ڊيگهائي, call_معلومات_2->chg_پهريون);
    }
    إذا (متن) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", متن->string.multi_byte, call_معلومات_2->chg_پهريون, call_معلومات_2->caret);
    }
    SDL_Log("Pre-edit text: %s", معلومات->preedit_متن);
#جيڪڏهن_پورو

    X11_SendEditingEvent(معلومات);
}

ساكن فراغ preedit_caret_callback(XIC xic, XPointer client_معلومات_2, XIMPreeditCaretCallbackStruct *call_معلومات_2)
{
    SDL_دري_معلومات *معلومات = (SDL_دري_معلومات *)client_معلومات_2;

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
    SDL_دري_معلومات *معلومات = (SDL_دري_معلومات *)client_معلومات;
    معلومات->ic = عدم;
    X11_Destroy_داخلا_Context(معلومات);

    // If the IM was already recreated, create a new IC.
    إذا (معلومات->videodata->im) {
        X11_Create_داخلا_Context(معلومات);
    }
}
#جيڪڏهن_پورو // X_HAVE_UTF8_STRING

فراغ X11_Create_داخلا_Context(SDL_دري_معلومات *معلومات)
{
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
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

            XIMCallback شروعات_callback;
            شروعات_callback.client_معلومات_2 = (XPointer)معلومات;
            شروعات_callback.callback = (XIMProc)preedit_شروعات_callback;

            XIMCallback پورو_callback;
            پورو_callback.client_معلومات_2 = (XPointer)معلومات;
            پورو_callback.callback = (XIMProc)preedit_پورو_callback;

            XIMCallback caret_callback;
            caret_callback.client_معلومات_2 = (XPointer)معلومات;
            caret_callback.callback = (XIMProc)preedit_caret_callback;

            XVaNestedList attr = X11_XVaCreateNestedList(0,
                                                         XNPreedit_شروعات_Callback, &شروعات_callback,
                                                         XNPreedit_پورو_Callback, &پورو_callback,
                                                         XNPreeditDrawCallback, &draw_callback,
                                                         XNPreeditCaretCallback, &caret_callback,
                                                         عدم);
            إذا (attr) {
                معلومات->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreedit_خاصيتون, attr,
                                         XNClient_دري, معلومات->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         عدم);
                X11_XFree(attr);
            }
        }
        إذا (!معلومات->ic) {
            معلومات->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClient_دري, معلومات->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     عدم);
        }
        معلومات->xim_spot.x = -1;
        معلومات->xim_spot.y = -1;
    }
#جيڪڏهن_پورو // X_HAVE_UTF8_STRING
}


فراغ X11_Destroy_داخلا_Context(SDL_دري_معلومات *معلومات)
{
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
    إذا (معلومات->ic) {
        X11_XDestroyIC(معلومات->ic);
        معلومات->ic = عدم;
    }
    SDL_free(معلومات->preedit_متن);
    SDL_free(معلومات->preedit_feedback);
    معلومات->preedit_متن = عدم;
    معلومات->preedit_feedback = عدم;
#جيڪڏهن_پورو
}

ساكن فراغ X11_ResetXIM(SDL_VideoDevice *_this, SDL_دري *دري)
{
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
    SDL_دري_معلومات *معلومات = دري->اندروني;

    إذا (معلومات && معلومات->ic) {
        // Clear any partially entered dead keys
        حرف *contents = X11_Xutf8ResetIC(معلومات->ic);
        إذا (contents) {
            X11_XFree(contents);
        }
    }
#جيڪڏهن_پورو // X_HAVE_UTF8_STRING
}

bool X11_شروعات_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, دري);

    أرجع X11_Update_متن_داخلا_Area(_this, دري);
}

bool X11_Stop_متن_داخلا(SDL_VideoDevice *_this, SDL_دري *دري)
{
    X11_ResetXIM(_this, دري);
    أرجع true;
}

bool X11_Update_متن_داخلا_Area(SDL_VideoDevice *_this, SDL_دري *دري)
{
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
    SDL_دري_معلومات *معلومات = دري->اندروني;

    إذا (معلومات && معلومات->ic) {
        XPoint spot;
        spot.x = دري->متن_داخلا_rect.x + دري->متن_داخلا_cursor;
        spot.y = دري->متن_داخلا_rect.y + دري->متن_داخلا_rect.h;
        إذا (spot.x != معلومات->xim_spot.x || spot.y != معلومات->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, عدم);
            إذا (attr) {
                X11_XSetICValues(معلومات->ic, XNPreedit_خاصيتون, attr, عدم);
                X11_XFree(attr);
            }
            SDL_copyp(&معلومات->xim_spot, &spot);
        }
    }
#جيڪڏهن_پورو
    أرجع true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    أرجع videodata->use_steam_screen_keyboard;
}

فراغ X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props)
{
    SDL_Video_معلومات *videodata = _this->اندروني;

    إذا (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ثابت صحيح k_EFloating_Gamepad_متن_داخلا_گهڻائي_گهڻائي_Single_سٽ = 0;    // Enter dismisses the keyboard
        ثابت صحيح k_EFloating_Gamepad_متن_داخلا_گهڻائي_گهڻائي_گڻو_سٽون = 1; // User needs to explicitly dismiss the keyboard
        ثابت صحيح k_EFloating_Gamepad_متن_داخلا_گهڻائي_گهڻائي_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ثابت صحيح k_EFloating_Gamepad_متن_داخلا_گهڻائي_گهڻائي_Numeric = 3;       // Numeric keypad is shown
        حرف deeplink[128];
        صحيح گهڻائي;

        بدل (SDL_Get_متن_داخلا_Type(props)) {
        حالة SDL_TEXTINPUT_TYPE_متن_EMAIL:
            گهڻائي = k_EFloating_Gamepad_متن_داخلا_گهڻائي_گهڻائي_Email;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_عدد:
        حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
        حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_VISIBLE:
            گهڻائي = k_EFloating_Gamepad_متن_داخلا_گهڻائي_گهڻائي_Numeric;
            اكسر;
        افتراضي:
            إذا (SDL_Get_متن_داخلا_Multiline(props)) {
                گهڻائي = k_EFloating_Gamepad_متن_داخلا_گهڻائي_گهڻائي_گڻو_سٽون;
            } وإلا {
                گهڻائي = k_EFloating_Gamepad_متن_داخلا_گهڻائي_گهڻائي_Single_سٽ;
            }
            اكسر;
        }
        (فراغ)SDL_snprintf(deeplink, حجم(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           دري->متن_داخلا_rect.x, دري->متن_داخلا_rect.y,
                           دري->متن_داخلا_rect.w, دري->متن_داخلا_rect.h,
                           گهڻائي);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

فراغ X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *videodata = _this->اندروني;

    إذا (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11
