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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"

#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_scancode_tables_c.h"

#ضمن <X11/keysym.h>

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#ضمن <X11/XKBlib.h>
#جے_انت

#ضمن "../../events/imKStoUCS.h"
#ضمن "../../events/SDL_keysym_to_scancode_c.h"
#ضمن "../../events/SDL_keysym_to_keycode_c.h"

#جے_تعریف_شدہ X_HAVE_UTF8_STRING
#ضمن <locale.h>
#جے_انت

ساكن SDL_Scancode_جدول scancode_سیٹ[] = {
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

ساكن کلید_Sym X11_کلید_کوڈ_منزل_Sym(SDL_VideoDevice *_this, کلید_کوڈ_2 keycode, بنانشانی صحيح گروہ, بنانشانی صحيح level)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    کلید_Sym keysym;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (انکڑے->keyboard.xkb_enabled) {
        keysym = X11_Xkb_Keycode_منزل_Keysym(انکڑے->display, keycode, گروہ, level);
    } وإلا
#جے_انت
    {
        // TODO: Handle groups on the legacy path.
        إذا (keycode >= انکڑے->keyboard.core.min_keycode && keycode <= انکڑے->keyboard.core.max_keycode) {
            keysym = انکڑے->keyboard.core.keysym_map[(keycode - انکڑے->keyboard.core.min_keycode) * انکڑے->keyboard.core.keysyms_فی_کلید];
        } وإلا {
            keysym = No_علامت;
        }
    }

    أرجع keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
ساكن SDL_Scancode X11_کلید_کوڈ_منزل_SDLScancode(SDL_VideoDevice *_this, کلید_کوڈ_2 keycode)
{
    ثابت کلید_Sym keysym = X11_کلید_کوڈ_منزل_Sym(_this, keycode, 0, 0);

    إذا (keysym == No_علامت) {
        أرجع SDL_SCANCODE_UNKNOWN;
    }

    أرجع SDL_Get_Scancode_From_کلید_Sym(keysym, keycode);
}

#جے_تعریف_شدہ X_HAVE_UTF8_STRING
ساكن bool X11_InitIM(SDL_Video_انکڑے *videodata);

ساكن فراغ im_instantiate_handler(Display *display, XPointer client_انکڑے, XPointer call_انکڑے)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)client_انکڑے;

    إذا (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, عدم, عدم, عدم, im_instantiate_handler, client_انکڑے);
    }
}

ساكن فراغ im_destroyed_handler(XIM im, XPointer client_انکڑے, XPointer call_انکڑے)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)client_انکڑے;

    videodata->im = عدم;
    X11_XRegisterIMInstantiateCallback(videodata->display, عدم, عدم, عدم, im_instantiate_handler, client_انکڑے);
}

ساكن bool X11_InitIM(SDL_Video_انکڑے *videodata)
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
        destroyed_callback.client_انکڑے_2 = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (حرف *)عدم);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        لكل (صحيح i = 0; i < videodata->numwindows; ++i) {
            SDL_کھڑکی_انکڑے *w = videodata->windowlist[i];
            إذا (!w->ic) {
                X11_Create_داخلہ_Context(w);
            }
        }

        أرجع true;
    }

    أرجع false;
}
#جے_انت // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    صحيح i = 0;
    صحيح j = 0;
    صحيح min_keycode, max_keycode;
    بنية
    {
        SDL_Scancode scancode;
        کلید_Sym keysym;
        صحيح قدر;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_پہلوں, 0 },
        { SDL_SCANCODE_اتے, XK_اتے, 0 },
        { SDL_SCANCODE_بایاں, XK_بایاں, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    صحيح بہترین_فاصلہ;
    صحيح بہترین_اشاریہ;
    صحيح فاصلہ;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    صحيح xkb_major = Xkb_Major_نسخہ;
    صحيح xkb_minor = Xkb_Minor_نسخہ;

    إذا (X11_XkbQueryExtension(انکڑے->display, عدم, &انکڑے->keyboard.xkb.event, عدم, &xkb_major, &xkb_minor)) {
        Bool xkb_repeat = 0;
        انکڑے->keyboard.xkb_enabled = true;
        انکڑے->keyboard.xkb.desc_ptr = X11_XkbGetMap(انکڑے->display, Xkb_All_Client_Info_نقاب, XkbUseCoreKbd);

        // This will remove KeyRelease events for held keys.
        X11_Xkb_سیٹ_Detectable_Auto_Repeat(انکڑے->display, True, &xkb_repeat);

        // Enable the key mapping and state events.
        X11_XkbSelectEvents(انکڑے->display, XkbUseCoreKbd,
                            Xkb_New_Keyboard_Notify_نقاب | Xkb_Map_Notify_نقاب | Xkb_State_Notify_نقاب,
                            Xkb_New_Keyboard_Notify_نقاب | Xkb_Map_Notify_نقاب | Xkb_State_Notify_نقاب);
        X11_XkbSelectEventDetails(انکڑے->display, XkbUseCoreKbd, XkbStateNotify, Xkb_گروہ_State_نقاب | Xkb_Modifier_State_نقاب, Xkb_گروہ_State_نقاب | Xkb_Modifier_State_نقاب);
    } وإلا
#جے_انت
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(انکڑے->display, &انکڑے->keyboard.core.min_keycode, &انکڑے->keyboard.core.max_keycode);
        انکڑے->keyboard.core.keysym_map = X11_XGetKeyboardMapping(انکڑے->display, انکڑے->keyboard.core.min_keycode,
                                                              انکڑے->keyboard.core.max_keycode - انکڑے->keyboard.core.min_keycode,
                                                              &انکڑے->keyboard.core.keysyms_فی_کلید);
    }

    // Open a connection to the X input manager
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    إذا (SDL_X11_HAVE_UTF8) {
        إذا (!X11_InitIM(انکڑے)) {
            X11_XRegisterIMInstantiateCallback(انکڑے->display, عدم, عدم, عدم, im_instantiate_handler, (XPointer)انکڑے);
        }
    }
#جے_انت
    // Try to determine which scancodes are being used based on fingerprint
    بہترین_فاصلہ = SDL_arraysize(fingerprint) + 1;
    بہترین_اشاریہ = -1;
    X11_XDisplayKeycodes(انکڑے->display, &min_keycode, &max_keycode);
    لكل (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].قدر = X11_XKeysym_منزل_Keycode(انکڑے->display, fingerprint[i].keysym) - min_keycode;
    }
    لكل (i = 0; i < SDL_arraysize(scancode_سیٹ); ++i) {
        صحيح جدول_ناپ;
        ثابت SDL_Scancode *جدول = SDL_Get_Scancode_جدول(scancode_سیٹ[i], &جدول_ناپ);

        فاصلہ = 0;
        لكل (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            إذا (fingerprint[j].قدر < 0 || fingerprint[j].قدر >= جدول_ناپ) {
                فاصلہ += 1;
            } وإلا إذا (جدول[fingerprint[j].قدر] != fingerprint[j].scancode) {
                فاصلہ += 1;
            }
        }
        إذا (فاصلہ < بہترین_فاصلہ) {
            بہترین_فاصلہ = فاصلہ;
            بہترین_اشاریہ = i;
        }
    }
    إذا (بہترین_اشاریہ < 0 || بہترین_فاصلہ > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        صحيح fingerprint_قدر = X11_XKeysym_منزل_Keycode(انکڑے->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        إذا (fingerprint_قدر == 235) {
            لكل (i = 0; i < SDL_arraysize(scancode_سیٹ); ++i) {
                إذا (scancode_سیٹ[i] == SDL_SCANCODE_جدول_XFREE86_2) {
                    بہترین_اشاریہ = i;
                    بہترین_فاصلہ = 0;
                    اكسر;
                }
            }
        }
    }
    إذا (بہترین_اشاریہ >= 0 && بہترین_فاصلہ <= 2) {
        صحيح جدول_ناپ;
        ثابت SDL_Scancode *جدول = SDL_Get_Scancode_جدول(scancode_سیٹ[بہترین_اشاریہ], &جدول_ناپ);

#جے_تعریف_شدہ DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", بہترین_اشاریہ, min_keycode, max_keycode, جدول_ناپ);
#جے_انت
        // This should never happen, but just in case...
        إذا (جدول_ناپ > (SDL_arraysize(انکڑے->keyboard.کلید_layout) - min_keycode)) {
            جدول_ناپ = (SDL_arraysize(انکڑے->keyboard.کلید_layout) - min_keycode);
        }
        SDL_memcpy(&انکڑے->keyboard.کلید_layout[min_keycode], جدول, حجم(SDL_Scancode) * جدول_ناپ);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        لكل (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_کلید_کوڈ_منزل_SDLScancode(_this, i);
#جے_تعریف_شدہ DEBUG_KEYBOARD
            {
                کلید_Sym sym;
                sym = X11_کلید_کوڈ_منزل_Sym(_this, (کلید_کوڈ_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (بنانشانی صحيح)sym, sym == No_علامت ? "NoSymbol" : X11_XKeysym_منزل_String(sym));
            }
#جے_انت
            إذا (scancode == انکڑے->keyboard.کلید_layout[i]) {
                استمر;
            }
            إذا ((SDL_GetKeymapKeycode(عدم, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_نقاب | SDLK_EXTENDED_نقاب)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#جے_تعریف_شدہ DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", انکڑے->کلید_layout[i], SDL_GetScancodeName(انکڑے->کلید_layout[i]), scancode, SDL_GetScancodeName(scancode));
#جے_انت
                انکڑے->keyboard.کلید_layout[i] = scancode;
            }
        }
    } وإلا {
#جے_تعریف_شدہ DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#جے_انت

        // Determine key_layout - only works on US QWERTY layout
        لكل (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_کلید_کوڈ_منزل_SDLScancode(_this, i);
#جے_تعریف_شدہ DEBUG_SCANCODES
            {
                کلید_Sym sym;
                sym = X11_کلید_کوڈ_منزل_Sym(_this, (کلید_کوڈ_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (بنانشانی صحيح)sym, sym == No_علامت ? "NoSymbol" : X11_XKeysym_منزل_String(sym));
            }
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } وإلا {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#جے_انت
            انکڑے->keyboard.کلید_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_سیٹ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    أرجع true;
}

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
ساكن بنانشانی صحيح X11_Get_Xkb_Virtual_Modifier_نقاب(SDL_VideoDevice *_this, ثابت حرف *vmod_name)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    بنانشانی صحيح mod_نقاب = 0;

    ثابت Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    إذا (vmod != None) {
        لكل (صحيح i = 0; i < Xkb_عدد_Virtual_Mods; ++i) {
            إذا (vmod == videodata->keyboard.xkb.desc_ptr->ناں->vmods[i]) {
                mod_نقاب = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                اكسر;
            }
        }
    }

    أرجع mod_نقاب;
}
#جے_انت

ساكن بنانشانی X11_Get_XModifier_نقاب(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    Display *display = videodata->display;
    بنانشانی صحيح mod_نقاب = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    بنانشانی صحيح n = xmods->max_keypermod;
    لكل (صحيح i = 3; i < 8; i++) {
        لكل (صحيح j = 0; j < n; j++) {
            ثابت کلید_کوڈ_2 kc = xmods->modifiermap[i * n + j];
            إذا (videodata->keyboard.کلید_layout[kc] == scancode) {
                mod_نقاب = 1 << i;
                اكسر;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    أرجع mod_نقاب;
}

ساكن فراغ X11_جوڑو_Keymap_اندراج(SDL_Keymap *keymap, Uint32 xkeycode, کلید_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_نقاب)
{
    SDL_Keycode keycode = SDL_Get_کلید_کوڈ_From_کلید_Sym(xkeysym, xkeycode, sdl_mod_نقاب);

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

    SDL_سیٹ_Keymap_اندراج(keymap, sdl_scancode, sdl_mod_نقاب, keycode);
}

فراغ X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (انکڑے->keyboard.xkb_enabled) {
        XkbStateRec state;

        لكل (بنانشانی صحيح i = 0; i < Xkb_عدد_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(انکڑے->keyboard.xkb.keymaps[i]);
            انکڑے->keyboard.xkb.keymaps[i] = عدم;
        }

        X11_Xkb_Get_ناں(انکڑے->display, Xkb_Virtual_Mod_ناں_نقاب, انکڑے->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(انکڑے->display, Xkb_All_Client_Info_نقاب | Xkb_Virtual_Mods_نقاب, انکڑے->keyboard.xkb.desc_ptr);

        إذا (X11_XkbGetState(انکڑے->display, XkbUseCoreKbd, &state) == Success) {
            انکڑے->keyboard.xkb.current_گروہ = state.گروہ;
        }

        انکڑے->keyboard.alt_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "Alt");
        إذا (!انکڑے->keyboard.alt_نقاب) {
            انکڑے->keyboard.alt_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "Meta");
        }
        انکڑے->keyboard.gui_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "Super");
        انکڑے->keyboard.level3_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "LevelThree");
        انکڑے->keyboard.level5_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "LevelFive");
        انکڑے->keyboard.numlock_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "NumLock");
        انکڑے->keyboard.scrolllock_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "ScrollLock");

        لكل (بنانشانی صحيح i = 0; i < Xkb_عدد_Kbd_Groups; ++i) {
            انکڑے->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            إذا (!انکڑے->keyboard.xkb.keymaps[i]) {
                لكل (بنانشانی صحيح j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(انکڑے->keyboard.xkb.keymaps[i]);
                    انکڑے->keyboard.xkb.keymaps[j] = عدم;
                }

                أرجع;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ثابت Uint32 valid_mod_نقاب = کھسکاؤ_نقاب_2 | جندرا_نقاب | انکڑے->keyboard.alt_نقاب | انکڑے->keyboard.level3_نقاب | انکڑے->keyboard.level5_نقاب;

        لكل (Uint32 xkeycode = انکڑے->keyboard.xkb.desc_ptr->min_کلید_کوڈ; xkeycode < انکڑے->keyboard.xkb.desc_ptr->max_کلید_کوڈ; ++xkeycode) {
            ثابت SDL_Scancode scancode = انکڑے->keyboard.کلید_layout[xkeycode];
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                استمر;
            }

            لكل (Uint32 گروہ = 0; گروہ < Xkb_عدد_Kbd_Groups; ++گروہ) {
                SDL_Keymap *keymap = انکڑے->keyboard.xkb.keymaps[گروہ];

                Uint32 effective_گروہ = گروہ;
                ثابت بنانشانی حرف max_کلید_گروہ = Xkb_کلید_عدد_Groups(انکڑے->keyboard.xkb.desc_ptr, xkeycode);
                ثابت بنانشانی حرف کلید_گروہ_info = Xkb_کلید_گروہ_Info(انکڑے->keyboard.xkb.desc_ptr, xkeycode);

                إذا (max_کلید_گروہ && effective_گروہ >= max_کلید_گروہ) {
                    ثابت بنانشانی حرف action = Xkb_باہرلا_دا_Range_گروہ_Action(کلید_گروہ_info);

                    بدل (action) {
                    افتراضي:
                        effective_گروہ %= max_کلید_گروہ;
                        اكسر;
                    حالة XkbClampIntoRange:
                        effective_گروہ = max_کلید_گروہ - 1;
                        اكسر;
                    حالة XkbRedirectIntoRange:
                        effective_گروہ = Xkb_باہرلا_دا_Range_گروہ_نمبر(کلید_گروہ_info);
                        إذا (effective_گروہ >= max_کلید_گروہ) {
                            effective_گروہ = 0;
                        }
                        اكسر;
                    }
                }

                Xkb_کلید_Type_Ptr کلید_type = Xkb_کلید_کلید_Type(انکڑے->keyboard.xkb.desc_ptr, xkeycode, effective_گروہ);

                لكل (Uint32 level = 0; level < کلید_type->عدد_پدھراں; ++level) {
                    ثابت کلید_Sym keysym = X11_کلید_کوڈ_منزل_Sym(_this, xkeycode, effective_گروہ, level);

                    إذا (keysym != No_علامت) {
                        bool کلید_added = false;

                        لكل (صحيح map_idx = 0; map_idx < کلید_type->map_گنتی; ++map_idx) {
                            إذا (کلید_type->map[map_idx].سرگرم && کلید_type->map[map_idx].level == level) {
                                ثابت بنانشانی صحيح xkb_mod_نقاب = کلید_type->map[map_idx].mods.نقاب;
                                إذا ((xkb_mod_نقاب | valid_mod_نقاب) == valid_mod_نقاب) {
                                    ثابت SDL_Keymod sdl_mod_نقاب = (xkb_mod_نقاب & کھسکاؤ_نقاب_2 ? SDL_KMOD_کھسکاؤ : 0) |
                                                                    (xkb_mod_نقاب & جندرا_نقاب ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_نقاب & انکڑے->keyboard.alt_نقاب ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_نقاب & انکڑے->keyboard.level3_نقاب ? SDL_KMOD_منوال : 0) |
                                                                    (xkb_mod_نقاب & انکڑے->keyboard.level5_نقاب ? SDL_KMOD_LEVEL5 : 0);

                                    X11_جوڑو_Keymap_اندراج(keymap, xkeycode, keysym, scancode, sdl_mod_نقاب);
                                    کلید_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        إذا (!level && !کلید_added) {
                            X11_جوڑو_Keymap_اندراج(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_سیٹ_Keymap(انکڑے->keyboard.xkb.keymaps[انکڑے->keyboard.xkb.current_گروہ], send_event);
    } وإلا
#جے_انت
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        إذا (!keymap) {
            أرجع;
        }

        إذا (send_event) {
            إذا (انکڑے->keyboard.core.keysym_map) {
                X11_XFree(انکڑے->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(انکڑے->display, &انکڑے->keyboard.core.min_keycode, &انکڑے->keyboard.core.max_keycode);
            انکڑے->keyboard.core.keysym_map = X11_XGetKeyboardMapping(انکڑے->display, انکڑے->keyboard.core.min_keycode,
                                                                     انکڑے->keyboard.core.max_keycode - انکڑے->keyboard.core.min_keycode,
                                                                     &انکڑے->keyboard.core.keysyms_فی_کلید);
        }

        لكل (Uint32 xkeycode = انکڑے->keyboard.core.min_keycode; xkeycode <= انکڑے->keyboard.core.max_keycode; ++xkeycode) {
            ثابت SDL_Scancode scancode = انکڑے->keyboard.کلید_layout[xkeycode];
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                استمر;
            }

            ثابت کلید_Sym keysym = X11_کلید_کوڈ_منزل_Sym(_this, xkeycode, 0, 0);
            إذا (keysym != No_علامت) {
                X11_جوڑو_Keymap_اندراج(keymap, xkeycode, keysym, scancode, 0);
            }
        }

        انکڑے->keyboard.alt_نقاب = Mod1_نقاب; // Alt or Meta
        انکڑے->keyboard.gui_نقاب = Mod4_نقاب; // Super
        انکڑے->keyboard.level3_نقاب = Mod5_نقاب; // Note: Not a typo, Mod5 = level 3 shift, and Mod3 = level 5 shift.
        انکڑے->keyboard.level5_نقاب = Mod3_نقاب;
        انکڑے->keyboard.numlock_نقاب = X11_Get_XModifier_نقاب(_this, SDL_SCANCODE_NUMLOCKCLEAR);
        انکڑے->keyboard.scrolllock_نقاب = X11_Get_XModifier_نقاب(_this, SDL_SCANCODE_SCROLLLOCK);

        SDL_سیٹ_Keymap(keymap, send_event);
    }
}

فراغ X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    إذا (انکڑے->im) {
        X11_XCloseIM(انکڑے->im);
        انکڑے->im = عدم;
    } وإلا {
        X11_XUnregisterIMInstantiateCallback(انکڑے->display, عدم, عدم, عدم, im_instantiate_handler, (XPointer)انکڑے);
    }
#جے_انت // X_HAVE_UTF8_STRING

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (انکڑے->keyboard.xkb_enabled) {
        لكل (صحيح i = 0; i < Xkb_عدد_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(انکڑے->keyboard.xkb.keymaps[i]);
            انکڑے->keyboard.xkb.keymaps[i] = عدم;
        }

        إذا (انکڑے->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(انکڑے->keyboard.xkb.desc_ptr, 0, True);
            انکڑے->keyboard.xkb.desc_ptr = عدم;
        }
    } وإلا
#جے_انت
        إذا (انکڑے->keyboard.core.keysym_map) {
        X11_XFree(انکڑے->keyboard.core.keysym_map);
        انکڑے->keyboard.core.keysym_map = عدم;
    }
}

فراغ X11_ClearComposition(SDL_کھڑکی_انکڑے *انکڑے)
{
    إذا (انکڑے->preedit_لمائی > 0) {
        انکڑے->preedit_متن[0] = '\0';
        انکڑے->preedit_لمائی = 0;
    }

    إذا (انکڑے->ime_needs_clear_composition) {
        SDL_Send_Editing_متن("", 0, 0);
        انکڑے->ime_needs_clear_composition = false;
    }
}

ساكن فراغ X11_SendEditingEvent(SDL_کھڑکی_انکڑے *انکڑے)
{
    إذا (انکڑے->preedit_لمائی == 0) {
        X11_ClearComposition(انکڑے);
        أرجع;
    }

    bool وچ_highlight = false;
    صحيح شروع = -1, لمائی = 0, i;
    لكل (i = 0; i < انکڑے->preedit_لمائی; ++i) {
        إذا (انکڑے->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            إذا (شروع < 0) {
                شروع = i;
                وچ_highlight = true;
            }
        } وإلا إذا (وچ_highlight) {
            // Found the end of the highlight
            اكسر;
        }
    }
    إذا (وچ_highlight) {
        لمائی = (i - شروع);
    } وإلا {
        شروع = SDL_clamp(انکڑے->preedit_cursor, 0, انکڑے->preedit_لمائی);
    }
    SDL_Send_Editing_متن(انکڑے->preedit_متن, شروع, لمائی);

    انکڑے->ime_needs_clear_composition = true;
}

#جے_تعریف_شدہ X_HAVE_UTF8_STRING
ساكن صحيح preedit_شروع_callback(XIC xic, XPointer client_انکڑے_2, XPointer call_انکڑے_2)
{
    // No limit on preedit text length
    أرجع -1;
}

ساكن فراغ preedit_پورا_callback(XIC xic, XPointer client_انکڑے_2, XPointer call_انکڑے_2)
{
}

ساكن فراغ preedit_draw_callback(XIC xic, XPointer client_انکڑے_2, XIMPreeditDrawCallbackStruct *call_انکڑے_2)
{
    SDL_کھڑکی_انکڑے *انکڑے = (SDL_کھڑکی_انکڑے *)client_انکڑے_2;
    صحيح chg_پہلا = SDL_clamp(call_انکڑے_2->chg_پہلا, 0, انکڑے->preedit_لمائی);
    صحيح chg_لمائی = SDL_clamp(call_انکڑے_2->chg_لمائی, 0, انکڑے->preedit_لمائی - chg_پہلا);

    ثابت حرف *شروع = انکڑے->preedit_متن;
    إذا (chg_لمائی > 0) {
        // Delete text in range
        لكل (صحيح i = 0; شروع && *شروع && i < chg_پہلا; ++i) {
            SDL_قدم_UTF8(&شروع, عدم);
        }

        ثابت حرف *سرا = شروع;
        لكل (صحيح i = 0; سرا && *سرا && i < chg_لمائی; ++i) {
            SDL_قدم_UTF8(&سرا, عدم);
        }

        إذا (سرا > شروع) {
            SDL_memmove((حرف *)شروع, سرا, SDL_strlen(سرا) + 1);
            إذا ((chg_پہلا + chg_لمائی) > انکڑے->preedit_لمائی) {
                SDL_memmove(&انکڑے->preedit_feedback[chg_پہلا], &انکڑے->preedit_feedback[chg_پہلا + chg_لمائی], (انکڑے->preedit_لمائی - chg_پہلا - chg_لمائی) * حجم(*انکڑے->preedit_feedback));
            }
        }
        انکڑے->preedit_لمائی -= chg_لمائی;
    }

    XIMText *متن = call_انکڑے_2->متن;
    إذا (متن) {
        // Insert text in range
        SDL_assert(!متن->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        إذا (متن->string.multi_byte) {
            متن->لمائی = SDL_utf8strlen(متن->string.multi_byte);
        }

        size_t string_ناپ = SDL_strlen(متن->string.multi_byte);
        size_t ناپ = string_ناپ + 1;
        إذا (انکڑے->preedit_متن) {
            ناپ += SDL_strlen(انکڑے->preedit_متن);
        }
        حرف *preedit_متن = (حرف *)SDL_malloc(ناپ * حجم(*preedit_متن));
        إذا (preedit_متن) {
            size_t pre_ناپ = (شروع - انکڑے->preedit_متن);
            size_t post_ناپ = شروع ? SDL_strlen(شروع) : 0;
            إذا (pre_ناپ > 0) {
                SDL_memcpy(&preedit_متن[0], انکڑے->preedit_متن, pre_ناپ);
            }
            SDL_memcpy(&preedit_متن[pre_ناپ], متن->string.multi_byte, string_ناپ);
            إذا (post_ناپ > 0) {
                SDL_memcpy(&preedit_متن[pre_ناپ + string_ناپ], شروع, post_ناپ);
            }
            preedit_متن[ناپ - 1] = '\0';
        }

        size_t feedback_ناپ = انکڑے->preedit_لمائی + متن->لمائی;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_ناپ * حجم(*feedback));
        إذا (feedback) {
            size_t pre_ناپ = (size_t)chg_پہلا;
            size_t post_ناپ = (size_t)انکڑے->preedit_لمائی - pre_ناپ;
            إذا (pre_ناپ > 0) {
                SDL_memcpy(&feedback[0], انکڑے->preedit_feedback, pre_ناپ * حجم(*feedback));
            }
            SDL_memcpy(&feedback[pre_ناپ], متن->feedback, متن->لمائی * حجم(*feedback));
            إذا (post_ناپ > 0) {
                SDL_memcpy(&feedback[pre_ناپ + متن->لمائی], &انکڑے->preedit_feedback[pre_ناپ], post_ناپ * حجم(*feedback));
            }
        }

        إذا (preedit_متن && feedback) {
            SDL_free(انکڑے->preedit_متن);
            انکڑے->preedit_متن = preedit_متن;

            SDL_free(انکڑے->preedit_feedback);
            انکڑے->preedit_feedback = feedback;

            انکڑے->preedit_لمائی += متن->لمائی;
        } وإلا {
            SDL_free(preedit_متن);
            SDL_free(feedback);
        }
    }

    انکڑے->preedit_cursor = call_انکڑے_2->caret;

#جے_تعریف_شدہ DEBUG_XIM
    إذا (call_انکڑے_2->chg_لمائی > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_انکڑے_2->chg_لمائی, call_انکڑے_2->chg_پہلا);
    }
    إذا (متن) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", متن->string.multi_byte, call_انکڑے_2->chg_پہلا, call_انکڑے_2->caret);
    }
    SDL_Log("Pre-edit text: %s", انکڑے->preedit_متن);
#جے_انت

    X11_SendEditingEvent(انکڑے);
}

ساكن فراغ preedit_caret_callback(XIC xic, XPointer client_انکڑے_2, XIMPreeditCaretCallbackStruct *call_انکڑے_2)
{
    SDL_کھڑکی_انکڑے *انکڑے = (SDL_کھڑکی_انکڑے *)client_انکڑے_2;

    بدل (call_انکڑے_2->direction) {
    حالة XIMAbsolutePosition:
        إذا (call_انکڑے_2->position != انکڑے->preedit_cursor) {
            انکڑے->preedit_cursor = call_انکڑے_2->position;
            X11_SendEditingEvent(انکڑے);
        }
        اكسر;
    حالة XIMDontChange:
        اكسر;
    افتراضي:
        // Not currently supported
        اكسر;
    }
}

ساكن فراغ ic_destroyed_handler(XIC ic, XPointer client_انکڑے, XPointer call_انکڑے)
{
    SDL_کھڑکی_انکڑے *انکڑے = (SDL_کھڑکی_انکڑے *)client_انکڑے;
    انکڑے->ic = عدم;
    X11_Destroy_داخلہ_Context(انکڑے);

    // If the IM was already recreated, create a new IC.
    إذا (انکڑے->videodata->im) {
        X11_Create_داخلہ_Context(انکڑے);
    }
}
#جے_انت // X_HAVE_UTF8_STRING

فراغ X11_Create_داخلہ_Context(SDL_کھڑکی_انکڑے *انکڑے)
{
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    SDL_Video_انکڑے *videodata = انکڑے->videodata;

    إذا (SDL_X11_HAVE_UTF8 && videodata->im) {
        ثابت حرف *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_انکڑے_2 = (XPointer)انکڑے;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        إذا (hint && SDL_strstr(hint, "composition")) {
            XIMCallback draw_callback;
            draw_callback.client_انکڑے_2 = (XPointer)انکڑے;
            draw_callback.callback = (XIMProc)preedit_draw_callback;

            XIMCallback شروع_callback;
            شروع_callback.client_انکڑے_2 = (XPointer)انکڑے;
            شروع_callback.callback = (XIMProc)preedit_شروع_callback;

            XIMCallback پورا_callback;
            پورا_callback.client_انکڑے_2 = (XPointer)انکڑے;
            پورا_callback.callback = (XIMProc)preedit_پورا_callback;

            XIMCallback caret_callback;
            caret_callback.client_انکڑے_2 = (XPointer)انکڑے;
            caret_callback.callback = (XIMProc)preedit_caret_callback;

            XVaNestedList attr = X11_XVaCreateNestedList(0,
                                                         XNPreedit_شروع_Callback, &شروع_callback,
                                                         XNPreedit_پورا_Callback, &پورا_callback,
                                                         XNPreeditDrawCallback, &draw_callback,
                                                         XNPreeditCaretCallback, &caret_callback,
                                                         عدم);
            إذا (attr) {
                انکڑے->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreedit_گن, attr,
                                         XNClient_کھڑکی, انکڑے->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         عدم);
                X11_XFree(attr);
            }
        }
        إذا (!انکڑے->ic) {
            انکڑے->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClient_کھڑکی, انکڑے->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     عدم);
        }
        انکڑے->xim_spot.x = -1;
        انکڑے->xim_spot.y = -1;
    }
#جے_انت // X_HAVE_UTF8_STRING
}


فراغ X11_Destroy_داخلہ_Context(SDL_کھڑکی_انکڑے *انکڑے)
{
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    إذا (انکڑے->ic) {
        X11_XDestroyIC(انکڑے->ic);
        انکڑے->ic = عدم;
    }
    SDL_free(انکڑے->preedit_متن);
    SDL_free(انکڑے->preedit_feedback);
    انکڑے->preedit_متن = عدم;
    انکڑے->preedit_feedback = عدم;
#جے_انت
}

ساكن فراغ X11_ResetXIM(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    إذا (انکڑے && انکڑے->ic) {
        // Clear any partially entered dead keys
        حرف *contents = X11_Xutf8ResetIC(انکڑے->ic);
        إذا (contents) {
            X11_XFree(contents);
        }
    }
#جے_انت // X_HAVE_UTF8_STRING
}

bool X11_شروع_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, کھڑکی);

    أرجع X11_Update_متن_داخلہ_Area(_this, کھڑکی);
}

bool X11_Stop_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    X11_ResetXIM(_this, کھڑکی);
    أرجع true;
}

bool X11_Update_متن_داخلہ_Area(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    إذا (انکڑے && انکڑے->ic) {
        XPoint spot;
        spot.x = کھڑکی->متن_داخلہ_rect.x + کھڑکی->متن_داخلہ_cursor;
        spot.y = کھڑکی->متن_داخلہ_rect.y + کھڑکی->متن_داخلہ_rect.h;
        إذا (spot.x != انکڑے->xim_spot.x || spot.y != انکڑے->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, عدم);
            إذا (attr) {
                X11_XSetICValues(انکڑے->ic, XNPreedit_گن, attr, عدم);
                X11_XFree(attr);
            }
            SDL_copyp(&انکڑے->xim_spot, &spot);
        }
    }
#جے_انت
    أرجع true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    أرجع videodata->use_steam_screen_keyboard;
}

فراغ X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;

    إذا (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ثابت صحيح k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_Single_سطر = 0;    // Enter dismisses the keyboard
        ثابت صحيح k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_مضرب_سطریں = 1; // User needs to explicitly dismiss the keyboard
        ثابت صحيح k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ثابت صحيح k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_Numeric = 3;       // Numeric keypad is shown
        حرف deeplink[128];
        صحيح منوال;

        بدل (SDL_Get_متن_داخلہ_Type(props)) {
        حالة SDL_TEXTINPUT_TYPE_متن_EMAIL:
            منوال = k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_Email;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_نمبر:
        حالة SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_HIDDEN:
        حالة SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_VISIBLE:
            منوال = k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_Numeric;
            اكسر;
        افتراضي:
            إذا (SDL_Get_متن_داخلہ_Multiline(props)) {
                منوال = k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_مضرب_سطریں;
            } وإلا {
                منوال = k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_Single_سطر;
            }
            اكسر;
        }
        (فراغ)SDL_snprintf(deeplink, حجم(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           کھڑکی->متن_داخلہ_rect.x, کھڑکی->متن_داخلہ_rect.y,
                           کھڑکی->متن_داخلہ_rect.w, کھڑکی->متن_داخلہ_rect.h,
                           منوال);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

فراغ X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;

    إذا (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#جے_انت // SDL_VIDEO_DRIVER_X11
