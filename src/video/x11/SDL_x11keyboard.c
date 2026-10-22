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

#شامل "SDL_x11video.h"

#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_scancode_tables_c.h"

#شامل <X11/keysym.h>

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#شامل <X11/XKBlib.h>
#اگر_ختم

#شامل "../../events/imKStoUCS.h"
#شامل "../../events/SDL_keysym_to_scancode_c.h"
#شامل "../../events/SDL_keysym_to_keycode_c.h"

#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
#شامل <locale.h>
#اگر_ختم

ساکن SDL_Scancode_جدول scancode_سیٹ[] = {
    SDL_SCANCODE_جدول_DARWIN,
    SDL_SCANCODE_جدول_XFREE86_1,
    SDL_SCANCODE_جدول_XFREE86_2,
    SDL_SCANCODE_جدول_XVNC,
};

ساکن bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    انتخاب (scancode) {
    حالت SDL_SCANCODE_ESCAPE:
    حالت SDL_SCANCODE_CAPSLOCK:
    حالت SDL_SCANCODE_NUMLOCKCLEAR:
    حالت SDL_SCANCODE_LSHIFT:
    حالت SDL_SCANCODE_RSHIFT:
    حالت SDL_SCANCODE_LCTRL:
    حالت SDL_SCANCODE_RCTRL:
    حالت SDL_SCANCODE_LALT:
    حالت SDL_SCANCODE_RALT:
    حالت SDL_SCANCODE_LGUI:
    حالت SDL_SCANCODE_RGUI:
        واپس false;
    طےشدہ:
        واپس true;
    }
}

ساکن کلید_Sym X11_کلید_رمز_مقصد_Sym(SDL_VideoDevice *_this, کلید_رمز_2 keycode, غیرعلامتی صحیح گروہ, غیرعلامتی صحیح level)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    کلید_Sym keysym;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    اگر (ڈیٹا->keyboard.xkb_enabled) {
        keysym = X11_Xkb_Keycode_مقصد_Keysym(ڈیٹا->display, keycode, گروہ, level);
    } ورنہ
#اگر_ختم
    {
        // TODO: Handle groups on the legacy path.
        اگر (keycode >= ڈیٹا->keyboard.core.min_keycode && keycode <= ڈیٹا->keyboard.core.max_keycode) {
            keysym = ڈیٹا->keyboard.core.keysym_map[(keycode - ڈیٹا->keyboard.core.min_keycode) * ڈیٹا->keyboard.core.keysyms_فی_کلید];
        } ورنہ {
            keysym = No_علامت;
        }
    }

    واپس keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
ساکن SDL_Scancode X11_کلید_رمز_مقصد_SDLScancode(SDL_VideoDevice *_this, کلید_رمز_2 keycode)
{
    ثابت کلید_Sym keysym = X11_کلید_رمز_مقصد_Sym(_this, keycode, 0, 0);

    اگر (keysym == No_علامت) {
        واپس SDL_SCANCODE_UNKNOWN;
    }

    واپس SDL_Get_Scancode_From_کلید_Sym(keysym, keycode);
}

#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
ساکن bool X11_InitIM(SDL_Video_ڈیٹا *videodata);

ساکن خالی im_instantiate_handler(Display *display, XPointer client_ڈیٹا, XPointer call_ڈیٹا)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)client_ڈیٹا;

    اگر (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, تہی, تہی, تہی, im_instantiate_handler, client_ڈیٹا);
    }
}

ساکن خالی im_destroyed_handler(XIM im, XPointer client_ڈیٹا, XPointer call_ڈیٹا)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)client_ڈیٹا;

    videodata->im = تہی;
    X11_XRegisterIMInstantiateCallback(videodata->display, تہی, تہی, تہی, im_instantiate_handler, client_ڈیٹا);
}

ساکن bool X11_InitIM(SDL_Video_ڈیٹا *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    حرف *پچھلا_locale = setlocale(LC_ALL, تہی);
    حرف *پچھلا_xmods = X11_XSetLocaleModifiers(تہی);

    اگر (پچھلا_locale) {
        پچھلا_locale = SDL_strdup(پچھلا_locale);
    }

    اگر (پچھلا_xmods) {
        پچھلا_xmods = SDL_strdup(پچھلا_xmods);
    }

    (خالی)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, تہی, تہی, تہی);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (خالی)setlocale(LC_ALL, پچھلا_locale);
    X11_XSetLocaleModifiers(پچھلا_xmods);

    SDL_free(پچھلا_locale);
    SDL_free(پچھلا_xmods);

    اگر (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_ڈیٹا_2 = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (حرف *)تہی);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        برائے (صحیح i = 0; i < videodata->numwindows; ++i) {
            SDL_کھڑکی_ڈیٹا *w = videodata->windowlist[i];
            اگر (!w->ic) {
                X11_Create_داخلہ_Context(w);
            }
        }

        واپس true;
    }

    واپس false;
}
#اگر_ختم // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    صحیح i = 0;
    صحیح j = 0;
    صحیح min_keycode, max_keycode;
    ساخت
    {
        SDL_Scancode scancode;
        کلید_Sym keysym;
        صحیح قدر;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_پیشگی, 0 },
        { SDL_SCANCODE_اوپر, XK_اوپر, 0 },
        { SDL_SCANCODE_بایاں, XK_بایاں, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    صحیح بہترین_فاصلہ;
    صحیح بہترین_اشاریہ;
    صحیح فاصلہ;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    صحیح xkb_major = Xkb_Major_نسخہ;
    صحیح xkb_minor = Xkb_Minor_نسخہ;

    اگر (X11_XkbQueryExtension(ڈیٹا->display, تہی, &ڈیٹا->keyboard.xkb.event, تہی, &xkb_major, &xkb_minor)) {
        Bool xkb_repeat = 0;
        ڈیٹا->keyboard.xkb_enabled = true;
        ڈیٹا->keyboard.xkb.desc_ptr = X11_XkbGetMap(ڈیٹا->display, Xkb_All_Client_Info_نقاب, XkbUseCoreKbd);

        // This will remove KeyRelease events for held keys.
        X11_Xkb_سیٹ_Detectable_Auto_Repeat(ڈیٹا->display, True, &xkb_repeat);

        // Enable the key mapping and state events.
        X11_XkbSelectEvents(ڈیٹا->display, XkbUseCoreKbd,
                            Xkb_New_Keyboard_Notify_نقاب | Xkb_Map_Notify_نقاب | Xkb_State_Notify_نقاب,
                            Xkb_New_Keyboard_Notify_نقاب | Xkb_Map_Notify_نقاب | Xkb_State_Notify_نقاب);
        X11_XkbSelectEventDetails(ڈیٹا->display, XkbUseCoreKbd, XkbStateNotify, Xkb_گروہ_State_نقاب | Xkb_Modifier_State_نقاب, Xkb_گروہ_State_نقاب | Xkb_Modifier_State_نقاب);
    } ورنہ
#اگر_ختم
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(ڈیٹا->display, &ڈیٹا->keyboard.core.min_keycode, &ڈیٹا->keyboard.core.max_keycode);
        ڈیٹا->keyboard.core.keysym_map = X11_XGetKeyboardMapping(ڈیٹا->display, ڈیٹا->keyboard.core.min_keycode,
                                                              ڈیٹا->keyboard.core.max_keycode - ڈیٹا->keyboard.core.min_keycode,
                                                              &ڈیٹا->keyboard.core.keysyms_فی_کلید);
    }

    // Open a connection to the X input manager
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    اگر (SDL_X11_HAVE_UTF8) {
        اگر (!X11_InitIM(ڈیٹا)) {
            X11_XRegisterIMInstantiateCallback(ڈیٹا->display, تہی, تہی, تہی, im_instantiate_handler, (XPointer)ڈیٹا);
        }
    }
#اگر_ختم
    // Try to determine which scancodes are being used based on fingerprint
    بہترین_فاصلہ = SDL_arraysize(fingerprint) + 1;
    بہترین_اشاریہ = -1;
    X11_XDisplayKeycodes(ڈیٹا->display, &min_keycode, &max_keycode);
    برائے (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].قدر = X11_XKeysym_مقصد_Keycode(ڈیٹا->display, fingerprint[i].keysym) - min_keycode;
    }
    برائے (i = 0; i < SDL_arraysize(scancode_سیٹ); ++i) {
        صحیح جدول_سائز;
        ثابت SDL_Scancode *جدول = SDL_Get_Scancode_جدول(scancode_سیٹ[i], &جدول_سائز);

        فاصلہ = 0;
        برائے (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            اگر (fingerprint[j].قدر < 0 || fingerprint[j].قدر >= جدول_سائز) {
                فاصلہ += 1;
            } ورنہ اگر (جدول[fingerprint[j].قدر] != fingerprint[j].scancode) {
                فاصلہ += 1;
            }
        }
        اگر (فاصلہ < بہترین_فاصلہ) {
            بہترین_فاصلہ = فاصلہ;
            بہترین_اشاریہ = i;
        }
    }
    اگر (بہترین_اشاریہ < 0 || بہترین_فاصلہ > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        صحیح fingerprint_قدر = X11_XKeysym_مقصد_Keycode(ڈیٹا->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        اگر (fingerprint_قدر == 235) {
            برائے (i = 0; i < SDL_arraysize(scancode_سیٹ); ++i) {
                اگر (scancode_سیٹ[i] == SDL_SCANCODE_جدول_XFREE86_2) {
                    بہترین_اشاریہ = i;
                    بہترین_فاصلہ = 0;
                    توڑو;
                }
            }
        }
    }
    اگر (بہترین_اشاریہ >= 0 && بہترین_فاصلہ <= 2) {
        صحیح جدول_سائز;
        ثابت SDL_Scancode *جدول = SDL_Get_Scancode_جدول(scancode_سیٹ[بہترین_اشاریہ], &جدول_سائز);

#اگر_تعریف_شدہ DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", بہترین_اشاریہ, min_keycode, max_keycode, جدول_سائز);
#اگر_ختم
        // This should never happen, but just in case...
        اگر (جدول_سائز > (SDL_arraysize(ڈیٹا->keyboard.کلید_layout) - min_keycode)) {
            جدول_سائز = (SDL_arraysize(ڈیٹا->keyboard.کلید_layout) - min_keycode);
        }
        SDL_memcpy(&ڈیٹا->keyboard.کلید_layout[min_keycode], جدول, حجم(SDL_Scancode) * جدول_سائز);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        برائے (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_کلید_رمز_مقصد_SDLScancode(_this, i);
#اگر_تعریف_شدہ DEBUG_KEYBOARD
            {
                کلید_Sym sym;
                sym = X11_کلید_رمز_مقصد_Sym(_this, (کلید_رمز_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (غیرعلامتی صحیح)sym, sym == No_علامت ? "NoSymbol" : X11_XKeysym_مقصد_String(sym));
            }
#اگر_ختم
            اگر (scancode == ڈیٹا->keyboard.کلید_layout[i]) {
                جاری;
            }
            اگر ((SDL_GetKeymapKeycode(تہی, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_نقاب | SDLK_EXTENDED_نقاب)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#اگر_تعریف_شدہ DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", ڈیٹا->کلید_layout[i], SDL_GetScancodeName(ڈیٹا->کلید_layout[i]), scancode, SDL_GetScancodeName(scancode));
#اگر_ختم
                ڈیٹا->keyboard.کلید_layout[i] = scancode;
            }
        }
    } ورنہ {
#اگر_تعریف_شدہ DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#اگر_ختم

        // Determine key_layout - only works on US QWERTY layout
        برائے (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_کلید_رمز_مقصد_SDLScancode(_this, i);
#اگر_تعریف_شدہ DEBUG_SCANCODES
            {
                کلید_Sym sym;
                sym = X11_کلید_رمز_مقصد_Sym(_this, (کلید_رمز_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (غیرعلامتی صحیح)sym, sym == No_علامت ? "NoSymbol" : X11_XKeysym_مقصد_String(sym));
            }
            اگر (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } ورنہ {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#اگر_ختم
            ڈیٹا->keyboard.کلید_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_سیٹ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    واپس true;
}

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
ساکن غیرعلامتی صحیح X11_Get_Xkb_Virtual_Modifier_نقاب(SDL_VideoDevice *_this, ثابت حرف *vmod_name)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    غیرعلامتی صحیح mod_نقاب = 0;

    ثابت Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    اگر (vmod != None) {
        برائے (صحیح i = 0; i < Xkb_عدد_Virtual_Mods; ++i) {
            اگر (vmod == videodata->keyboard.xkb.desc_ptr->نام->vmods[i]) {
                mod_نقاب = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                توڑو;
            }
        }
    }

    واپس mod_نقاب;
}
#اگر_ختم

ساکن غیرعلامتی X11_Get_XModifier_نقاب(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    Display *display = videodata->display;
    غیرعلامتی صحیح mod_نقاب = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    غیرعلامتی صحیح n = xmods->max_keypermod;
    برائے (صحیح i = 3; i < 8; i++) {
        برائے (صحیح j = 0; j < n; j++) {
            ثابت کلید_رمز_2 kc = xmods->modifiermap[i * n + j];
            اگر (videodata->keyboard.کلید_layout[kc] == scancode) {
                mod_نقاب = 1 << i;
                توڑو;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    واپس mod_نقاب;
}

ساکن خالی X11_جوڑو_Keymap_اندراج(SDL_Keymap *keymap, Uint32 xkeycode, کلید_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_نقاب)
{
    SDL_Keycode keycode = SDL_Get_کلید_رمز_From_کلید_Sym(xkeysym, xkeycode, sdl_mod_نقاب);

    اگر (!keycode) {
        انتخاب (sdl_scancode) {
        حالت SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            توڑو;
        حالت SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            توڑو;
        حالت SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            توڑو;
        حالت SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            توڑو;
        طےشدہ:
            keycode = SDL_SCANCODE_مقصد_KEYCODE(sdl_scancode);
            توڑو;
        }
    }

    SDL_سیٹ_Keymap_اندراج(keymap, sdl_scancode, sdl_mod_نقاب, keycode);
}

خالی X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    اگر (ڈیٹا->keyboard.xkb_enabled) {
        XkbStateRec state;

        برائے (غیرعلامتی صحیح i = 0; i < Xkb_عدد_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(ڈیٹا->keyboard.xkb.keymaps[i]);
            ڈیٹا->keyboard.xkb.keymaps[i] = تہی;
        }

        X11_Xkb_Get_نام(ڈیٹا->display, Xkb_Virtual_Mod_نام_نقاب, ڈیٹا->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(ڈیٹا->display, Xkb_All_Client_Info_نقاب | Xkb_Virtual_Mods_نقاب, ڈیٹا->keyboard.xkb.desc_ptr);

        اگر (X11_XkbGetState(ڈیٹا->display, XkbUseCoreKbd, &state) == Success) {
            ڈیٹا->keyboard.xkb.current_گروہ = state.گروہ;
        }

        ڈیٹا->keyboard.alt_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "Alt");
        اگر (!ڈیٹا->keyboard.alt_نقاب) {
            ڈیٹا->keyboard.alt_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "Meta");
        }
        ڈیٹا->keyboard.gui_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "Super");
        ڈیٹا->keyboard.level3_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "LevelThree");
        ڈیٹا->keyboard.level5_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "LevelFive");
        ڈیٹا->keyboard.numlock_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "NumLock");
        ڈیٹا->keyboard.scrolllock_نقاب = X11_Get_Xkb_Virtual_Modifier_نقاب(_this, "ScrollLock");

        برائے (غیرعلامتی صحیح i = 0; i < Xkb_عدد_Kbd_Groups; ++i) {
            ڈیٹا->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            اگر (!ڈیٹا->keyboard.xkb.keymaps[i]) {
                برائے (غیرعلامتی صحیح j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(ڈیٹا->keyboard.xkb.keymaps[i]);
                    ڈیٹا->keyboard.xkb.keymaps[j] = تہی;
                }

                واپس;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ثابت Uint32 valid_mod_نقاب = سرکاؤ_نقاب_2 | تالا_نقاب | ڈیٹا->keyboard.alt_نقاب | ڈیٹا->keyboard.level3_نقاب | ڈیٹا->keyboard.level5_نقاب;

        برائے (Uint32 xkeycode = ڈیٹا->keyboard.xkb.desc_ptr->min_کلید_رمز; xkeycode < ڈیٹا->keyboard.xkb.desc_ptr->max_کلید_رمز; ++xkeycode) {
            ثابت SDL_Scancode scancode = ڈیٹا->keyboard.کلید_layout[xkeycode];
            اگر (scancode == SDL_SCANCODE_UNKNOWN) {
                جاری;
            }

            برائے (Uint32 گروہ = 0; گروہ < Xkb_عدد_Kbd_Groups; ++گروہ) {
                SDL_Keymap *keymap = ڈیٹا->keyboard.xkb.keymaps[گروہ];

                Uint32 effective_گروہ = گروہ;
                ثابت غیرعلامتی حرف max_کلید_گروہ = Xkb_کلید_عدد_Groups(ڈیٹا->keyboard.xkb.desc_ptr, xkeycode);
                ثابت غیرعلامتی حرف کلید_گروہ_info = Xkb_کلید_گروہ_Info(ڈیٹا->keyboard.xkb.desc_ptr, xkeycode);

                اگر (max_کلید_گروہ && effective_گروہ >= max_کلید_گروہ) {
                    ثابت غیرعلامتی حرف action = Xkb_برآمد_کا_Range_گروہ_Action(کلید_گروہ_info);

                    انتخاب (action) {
                    طےشدہ:
                        effective_گروہ %= max_کلید_گروہ;
                        توڑو;
                    حالت XkbClampIntoRange:
                        effective_گروہ = max_کلید_گروہ - 1;
                        توڑو;
                    حالت XkbRedirectIntoRange:
                        effective_گروہ = Xkb_برآمد_کا_Range_گروہ_نمبر(کلید_گروہ_info);
                        اگر (effective_گروہ >= max_کلید_گروہ) {
                            effective_گروہ = 0;
                        }
                        توڑو;
                    }
                }

                Xkb_کلید_Type_Ptr کلید_type = Xkb_کلید_کلید_Type(ڈیٹا->keyboard.xkb.desc_ptr, xkeycode, effective_گروہ);

                برائے (Uint32 level = 0; level < کلید_type->عدد_سطحیں; ++level) {
                    ثابت کلید_Sym keysym = X11_کلید_رمز_مقصد_Sym(_this, xkeycode, effective_گروہ, level);

                    اگر (keysym != No_علامت) {
                        bool کلید_added = false;

                        برائے (صحیح map_idx = 0; map_idx < کلید_type->map_گنتی; ++map_idx) {
                            اگر (کلید_type->map[map_idx].فعال && کلید_type->map[map_idx].level == level) {
                                ثابت غیرعلامتی صحیح xkb_mod_نقاب = کلید_type->map[map_idx].mods.نقاب;
                                اگر ((xkb_mod_نقاب | valid_mod_نقاب) == valid_mod_نقاب) {
                                    ثابت SDL_Keymod sdl_mod_نقاب = (xkb_mod_نقاب & سرکاؤ_نقاب_2 ? SDL_KMOD_سرکاؤ : 0) |
                                                                    (xkb_mod_نقاب & تالا_نقاب ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_نقاب & ڈیٹا->keyboard.alt_نقاب ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_نقاب & ڈیٹا->keyboard.level3_نقاب ? SDL_KMOD_منوال : 0) |
                                                                    (xkb_mod_نقاب & ڈیٹا->keyboard.level5_نقاب ? SDL_KMOD_LEVEL5 : 0);

                                    X11_جوڑو_Keymap_اندراج(keymap, xkeycode, keysym, scancode, sdl_mod_نقاب);
                                    کلید_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        اگر (!level && !کلید_added) {
                            X11_جوڑو_Keymap_اندراج(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_سیٹ_Keymap(ڈیٹا->keyboard.xkb.keymaps[ڈیٹا->keyboard.xkb.current_گروہ], send_event);
    } ورنہ
#اگر_ختم
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        اگر (!keymap) {
            واپس;
        }

        اگر (send_event) {
            اگر (ڈیٹا->keyboard.core.keysym_map) {
                X11_XFree(ڈیٹا->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(ڈیٹا->display, &ڈیٹا->keyboard.core.min_keycode, &ڈیٹا->keyboard.core.max_keycode);
            ڈیٹا->keyboard.core.keysym_map = X11_XGetKeyboardMapping(ڈیٹا->display, ڈیٹا->keyboard.core.min_keycode,
                                                                     ڈیٹا->keyboard.core.max_keycode - ڈیٹا->keyboard.core.min_keycode,
                                                                     &ڈیٹا->keyboard.core.keysyms_فی_کلید);
        }

        برائے (Uint32 xkeycode = ڈیٹا->keyboard.core.min_keycode; xkeycode <= ڈیٹا->keyboard.core.max_keycode; ++xkeycode) {
            ثابت SDL_Scancode scancode = ڈیٹا->keyboard.کلید_layout[xkeycode];
            اگر (scancode == SDL_SCANCODE_UNKNOWN) {
                جاری;
            }

            ثابت کلید_Sym keysym = X11_کلید_رمز_مقصد_Sym(_this, xkeycode, 0, 0);
            اگر (keysym != No_علامت) {
                X11_جوڑو_Keymap_اندراج(keymap, xkeycode, keysym, scancode, 0);
            }
        }

        ڈیٹا->keyboard.alt_نقاب = Mod1_نقاب; // Alt or Meta
        ڈیٹا->keyboard.gui_نقاب = Mod4_نقاب; // Super
        ڈیٹا->keyboard.level3_نقاب = Mod5_نقاب; // Note: Not a typo, Mod5 = level 3 shift, and Mod3 = level 5 shift.
        ڈیٹا->keyboard.level5_نقاب = Mod3_نقاب;
        ڈیٹا->keyboard.numlock_نقاب = X11_Get_XModifier_نقاب(_this, SDL_SCANCODE_NUMLOCKCLEAR);
        ڈیٹا->keyboard.scrolllock_نقاب = X11_Get_XModifier_نقاب(_this, SDL_SCANCODE_SCROLLLOCK);

        SDL_سیٹ_Keymap(keymap, send_event);
    }
}

خالی X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    اگر (ڈیٹا->im) {
        X11_XCloseIM(ڈیٹا->im);
        ڈیٹا->im = تہی;
    } ورنہ {
        X11_XUnregisterIMInstantiateCallback(ڈیٹا->display, تہی, تہی, تہی, im_instantiate_handler, (XPointer)ڈیٹا);
    }
#اگر_ختم // X_HAVE_UTF8_STRING

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    اگر (ڈیٹا->keyboard.xkb_enabled) {
        برائے (صحیح i = 0; i < Xkb_عدد_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(ڈیٹا->keyboard.xkb.keymaps[i]);
            ڈیٹا->keyboard.xkb.keymaps[i] = تہی;
        }

        اگر (ڈیٹا->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(ڈیٹا->keyboard.xkb.desc_ptr, 0, True);
            ڈیٹا->keyboard.xkb.desc_ptr = تہی;
        }
    } ورنہ
#اگر_ختم
        اگر (ڈیٹا->keyboard.core.keysym_map) {
        X11_XFree(ڈیٹا->keyboard.core.keysym_map);
        ڈیٹا->keyboard.core.keysym_map = تہی;
    }
}

خالی X11_ClearComposition(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    اگر (ڈیٹا->preedit_لمبائی > 0) {
        ڈیٹا->preedit_متن[0] = '\0';
        ڈیٹا->preedit_لمبائی = 0;
    }

    اگر (ڈیٹا->ime_needs_clear_composition) {
        SDL_Send_Editing_متن("", 0, 0);
        ڈیٹا->ime_needs_clear_composition = false;
    }
}

ساکن خالی X11_SendEditingEvent(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    اگر (ڈیٹا->preedit_لمبائی == 0) {
        X11_ClearComposition(ڈیٹا);
        واپس;
    }

    bool اندر_highlight = false;
    صحیح آغاز = -1, لمبائی = 0, i;
    برائے (i = 0; i < ڈیٹا->preedit_لمبائی; ++i) {
        اگر (ڈیٹا->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            اگر (آغاز < 0) {
                آغاز = i;
                اندر_highlight = true;
            }
        } ورنہ اگر (اندر_highlight) {
            // Found the end of the highlight
            توڑو;
        }
    }
    اگر (اندر_highlight) {
        لمبائی = (i - آغاز);
    } ورنہ {
        آغاز = SDL_clamp(ڈیٹا->preedit_cursor, 0, ڈیٹا->preedit_لمبائی);
    }
    SDL_Send_Editing_متن(ڈیٹا->preedit_متن, آغاز, لمبائی);

    ڈیٹا->ime_needs_clear_composition = true;
}

#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
ساکن صحیح preedit_آغاز_callback(XIC xic, XPointer client_ڈیٹا_2, XPointer call_ڈیٹا_2)
{
    // No limit on preedit text length
    واپس -1;
}

ساکن خالی preedit_مکمل_callback(XIC xic, XPointer client_ڈیٹا_2, XPointer call_ڈیٹا_2)
{
}

ساکن خالی preedit_draw_callback(XIC xic, XPointer client_ڈیٹا_2, XIMPreeditDrawCallbackStruct *call_ڈیٹا_2)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = (SDL_کھڑکی_ڈیٹا *)client_ڈیٹا_2;
    صحیح chg_پہلا = SDL_clamp(call_ڈیٹا_2->chg_پہلا, 0, ڈیٹا->preedit_لمبائی);
    صحیح chg_لمبائی = SDL_clamp(call_ڈیٹا_2->chg_لمبائی, 0, ڈیٹا->preedit_لمبائی - chg_پہلا);

    ثابت حرف *آغاز = ڈیٹا->preedit_متن;
    اگر (chg_لمبائی > 0) {
        // Delete text in range
        برائے (صحیح i = 0; آغاز && *آغاز && i < chg_پہلا; ++i) {
            SDL_قدم_UTF8(&آغاز, تہی);
        }

        ثابت حرف *انتہا = آغاز;
        برائے (صحیح i = 0; انتہا && *انتہا && i < chg_لمبائی; ++i) {
            SDL_قدم_UTF8(&انتہا, تہی);
        }

        اگر (انتہا > آغاز) {
            SDL_memmove((حرف *)آغاز, انتہا, SDL_strlen(انتہا) + 1);
            اگر ((chg_پہلا + chg_لمبائی) > ڈیٹا->preedit_لمبائی) {
                SDL_memmove(&ڈیٹا->preedit_feedback[chg_پہلا], &ڈیٹا->preedit_feedback[chg_پہلا + chg_لمبائی], (ڈیٹا->preedit_لمبائی - chg_پہلا - chg_لمبائی) * حجم(*ڈیٹا->preedit_feedback));
            }
        }
        ڈیٹا->preedit_لمبائی -= chg_لمبائی;
    }

    XIMText *متن = call_ڈیٹا_2->متن;
    اگر (متن) {
        // Insert text in range
        SDL_assert(!متن->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        اگر (متن->string.multi_byte) {
            متن->لمبائی = SDL_utf8strlen(متن->string.multi_byte);
        }

        size_t string_سائز = SDL_strlen(متن->string.multi_byte);
        size_t سائز = string_سائز + 1;
        اگر (ڈیٹا->preedit_متن) {
            سائز += SDL_strlen(ڈیٹا->preedit_متن);
        }
        حرف *preedit_متن = (حرف *)SDL_malloc(سائز * حجم(*preedit_متن));
        اگر (preedit_متن) {
            size_t pre_سائز = (آغاز - ڈیٹا->preedit_متن);
            size_t post_سائز = آغاز ? SDL_strlen(آغاز) : 0;
            اگر (pre_سائز > 0) {
                SDL_memcpy(&preedit_متن[0], ڈیٹا->preedit_متن, pre_سائز);
            }
            SDL_memcpy(&preedit_متن[pre_سائز], متن->string.multi_byte, string_سائز);
            اگر (post_سائز > 0) {
                SDL_memcpy(&preedit_متن[pre_سائز + string_سائز], آغاز, post_سائز);
            }
            preedit_متن[سائز - 1] = '\0';
        }

        size_t feedback_سائز = ڈیٹا->preedit_لمبائی + متن->لمبائی;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_سائز * حجم(*feedback));
        اگر (feedback) {
            size_t pre_سائز = (size_t)chg_پہلا;
            size_t post_سائز = (size_t)ڈیٹا->preedit_لمبائی - pre_سائز;
            اگر (pre_سائز > 0) {
                SDL_memcpy(&feedback[0], ڈیٹا->preedit_feedback, pre_سائز * حجم(*feedback));
            }
            SDL_memcpy(&feedback[pre_سائز], متن->feedback, متن->لمبائی * حجم(*feedback));
            اگر (post_سائز > 0) {
                SDL_memcpy(&feedback[pre_سائز + متن->لمبائی], &ڈیٹا->preedit_feedback[pre_سائز], post_سائز * حجم(*feedback));
            }
        }

        اگر (preedit_متن && feedback) {
            SDL_free(ڈیٹا->preedit_متن);
            ڈیٹا->preedit_متن = preedit_متن;

            SDL_free(ڈیٹا->preedit_feedback);
            ڈیٹا->preedit_feedback = feedback;

            ڈیٹا->preedit_لمبائی += متن->لمبائی;
        } ورنہ {
            SDL_free(preedit_متن);
            SDL_free(feedback);
        }
    }

    ڈیٹا->preedit_cursor = call_ڈیٹا_2->caret;

#اگر_تعریف_شدہ DEBUG_XIM
    اگر (call_ڈیٹا_2->chg_لمبائی > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_ڈیٹا_2->chg_لمبائی, call_ڈیٹا_2->chg_پہلا);
    }
    اگر (متن) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", متن->string.multi_byte, call_ڈیٹا_2->chg_پہلا, call_ڈیٹا_2->caret);
    }
    SDL_Log("Pre-edit text: %s", ڈیٹا->preedit_متن);
#اگر_ختم

    X11_SendEditingEvent(ڈیٹا);
}

ساکن خالی preedit_caret_callback(XIC xic, XPointer client_ڈیٹا_2, XIMPreeditCaretCallbackStruct *call_ڈیٹا_2)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = (SDL_کھڑکی_ڈیٹا *)client_ڈیٹا_2;

    انتخاب (call_ڈیٹا_2->direction) {
    حالت XIMAbsolutePosition:
        اگر (call_ڈیٹا_2->position != ڈیٹا->preedit_cursor) {
            ڈیٹا->preedit_cursor = call_ڈیٹا_2->position;
            X11_SendEditingEvent(ڈیٹا);
        }
        توڑو;
    حالت XIMDontChange:
        توڑو;
    طےشدہ:
        // Not currently supported
        توڑو;
    }
}

ساکن خالی ic_destroyed_handler(XIC ic, XPointer client_ڈیٹا, XPointer call_ڈیٹا)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = (SDL_کھڑکی_ڈیٹا *)client_ڈیٹا;
    ڈیٹا->ic = تہی;
    X11_Destroy_داخلہ_Context(ڈیٹا);

    // If the IM was already recreated, create a new IC.
    اگر (ڈیٹا->videodata->im) {
        X11_Create_داخلہ_Context(ڈیٹا);
    }
}
#اگر_ختم // X_HAVE_UTF8_STRING

خالی X11_Create_داخلہ_Context(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    SDL_Video_ڈیٹا *videodata = ڈیٹا->videodata;

    اگر (SDL_X11_HAVE_UTF8 && videodata->im) {
        ثابت حرف *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_ڈیٹا_2 = (XPointer)ڈیٹا;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        اگر (hint && SDL_strstr(hint, "composition")) {
            XIMCallback draw_callback;
            draw_callback.client_ڈیٹا_2 = (XPointer)ڈیٹا;
            draw_callback.callback = (XIMProc)preedit_draw_callback;

            XIMCallback آغاز_callback;
            آغاز_callback.client_ڈیٹا_2 = (XPointer)ڈیٹا;
            آغاز_callback.callback = (XIMProc)preedit_آغاز_callback;

            XIMCallback مکمل_callback;
            مکمل_callback.client_ڈیٹا_2 = (XPointer)ڈیٹا;
            مکمل_callback.callback = (XIMProc)preedit_مکمل_callback;

            XIMCallback caret_callback;
            caret_callback.client_ڈیٹا_2 = (XPointer)ڈیٹا;
            caret_callback.callback = (XIMProc)preedit_caret_callback;

            XVaNestedList attr = X11_XVaCreateNestedList(0,
                                                         XNPreedit_آغاز_Callback, &آغاز_callback,
                                                         XNPreedit_مکمل_Callback, &مکمل_callback,
                                                         XNPreeditDrawCallback, &draw_callback,
                                                         XNPreeditCaretCallback, &caret_callback,
                                                         تہی);
            اگر (attr) {
                ڈیٹا->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreedit_اوصاف, attr,
                                         XNClient_کھڑکی, ڈیٹا->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         تہی);
                X11_XFree(attr);
            }
        }
        اگر (!ڈیٹا->ic) {
            ڈیٹا->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClient_کھڑکی, ڈیٹا->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     تہی);
        }
        ڈیٹا->xim_spot.x = -1;
        ڈیٹا->xim_spot.y = -1;
    }
#اگر_ختم // X_HAVE_UTF8_STRING
}


خالی X11_Destroy_داخلہ_Context(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    اگر (ڈیٹا->ic) {
        X11_XDestroyIC(ڈیٹا->ic);
        ڈیٹا->ic = تہی;
    }
    SDL_free(ڈیٹا->preedit_متن);
    SDL_free(ڈیٹا->preedit_feedback);
    ڈیٹا->preedit_متن = تہی;
    ڈیٹا->preedit_feedback = تہی;
#اگر_ختم
}

ساکن خالی X11_ResetXIM(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    اگر (ڈیٹا && ڈیٹا->ic) {
        // Clear any partially entered dead keys
        حرف *contents = X11_Xutf8ResetIC(ڈیٹا->ic);
        اگر (contents) {
            X11_XFree(contents);
        }
    }
#اگر_ختم // X_HAVE_UTF8_STRING
}

bool X11_آغاز_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, کھڑکی);

    واپس X11_Update_متن_داخلہ_Area(_this, کھڑکی);
}

bool X11_Stop_متن_داخلہ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    X11_ResetXIM(_this, کھڑکی);
    واپس true;
}

bool X11_Update_متن_داخلہ_Area(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    اگر (ڈیٹا && ڈیٹا->ic) {
        XPoint spot;
        spot.x = کھڑکی->متن_داخلہ_rect.x + کھڑکی->متن_داخلہ_cursor;
        spot.y = کھڑکی->متن_داخلہ_rect.y + کھڑکی->متن_داخلہ_rect.h;
        اگر (spot.x != ڈیٹا->xim_spot.x || spot.y != ڈیٹا->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, تہی);
            اگر (attr) {
                X11_XSetICValues(ڈیٹا->ic, XNPreedit_اوصاف, attr, تہی);
                X11_XFree(attr);
            }
            SDL_copyp(&ڈیٹا->xim_spot, &spot);
        }
    }
#اگر_ختم
    واپس true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    واپس videodata->use_steam_screen_keyboard;
}

خالی X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;

    اگر (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ثابت صحیح k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_Single_سطر = 0;    // Enter dismisses the keyboard
        ثابت صحیح k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_مضرب_سطریں = 1; // User needs to explicitly dismiss the keyboard
        ثابت صحیح k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ثابت صحیح k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_Numeric = 3;       // Numeric keypad is shown
        حرف deeplink[128];
        صحیح منوال;

        انتخاب (SDL_Get_متن_داخلہ_Type(props)) {
        حالت SDL_TEXTINPUT_TYPE_متن_EMAIL:
            منوال = k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_Email;
            توڑو;
        حالت SDL_TEXTINPUT_TYPE_نمبر:
        حالت SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_HIDDEN:
        حالت SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_VISIBLE:
            منوال = k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_Numeric;
            توڑو;
        طےشدہ:
            اگر (SDL_Get_متن_داخلہ_Multiline(props)) {
                منوال = k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_مضرب_سطریں;
            } ورنہ {
                منوال = k_EFloating_Gamepad_متن_داخلہ_منوال_منوال_Single_سطر;
            }
            توڑو;
        }
        (خالی)SDL_snprintf(deeplink, حجم(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           کھڑکی->متن_داخلہ_rect.x, کھڑکی->متن_داخلہ_rect.y,
                           کھڑکی->متن_داخلہ_rect.w, کھڑکی->متن_داخلہ_rect.h,
                           منوال);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

خالی X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;

    اگر (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11
