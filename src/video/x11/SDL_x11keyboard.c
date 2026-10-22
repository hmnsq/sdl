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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"

#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_scancode_tables_c.h"

#ضمن <X11/keysym.h>

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#ضمن <X11/XKBlib.h>
#پایان_اگر

#ضمن "../../events/imKStoUCS.h"
#ضمن "../../events/SDL_keysym_to_scancode_c.h"
#ضمن "../../events/SDL_keysym_to_keycode_c.h"

#اگر_تعریف_شده X_HAVE_UTF8_STRING
#ضمن <locale.h>
#پایان_اگر

ساكن SDL_Scancode_جدول scancode_مجموعه[] = {
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

ساكن کلید_Sym X11_کلید_کد_مقصد_Sym(SDL_VideoDevice *_this, کلید_کد_2 keycode, بیعلامت صحيح گروه, بیعلامت صحيح level)
{
    SDL_Video_داده *داده = _this->داخلی;
    کلید_Sym keysym;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (داده->keyboard.xkb_enabled) {
        keysym = X11_Xkb_Keycode_مقصد_Keysym(داده->display, keycode, گروه, level);
    } وإلا
#پایان_اگر
    {
        // TODO: Handle groups on the legacy path.
        إذا (keycode >= داده->keyboard.core.min_keycode && keycode <= داده->keyboard.core.max_keycode) {
            keysym = داده->keyboard.core.keysym_map[(keycode - داده->keyboard.core.min_keycode) * داده->keyboard.core.keysyms_در_هر_کلید];
        } وإلا {
            keysym = No_نماد;
        }
    }

    أرجع keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
ساكن SDL_Scancode X11_کلید_کد_مقصد_SDLScancode(SDL_VideoDevice *_this, کلید_کد_2 keycode)
{
    ثابت کلید_Sym keysym = X11_کلید_کد_مقصد_Sym(_this, keycode, 0, 0);

    إذا (keysym == No_نماد) {
        أرجع SDL_SCANCODE_UNKNOWN;
    }

    أرجع SDL_Get_Scancode_From_کلید_Sym(keysym, keycode);
}

#اگر_تعریف_شده X_HAVE_UTF8_STRING
ساكن bool X11_InitIM(SDL_Video_داده *videodata);

ساكن فراغ im_instantiate_handler(Display *display, XPointer client_داده, XPointer call_داده)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)client_داده;

    إذا (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, عدم, عدم, عدم, im_instantiate_handler, client_داده);
    }
}

ساكن فراغ im_destroyed_handler(XIM im, XPointer client_داده, XPointer call_داده)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)client_داده;

    videodata->im = عدم;
    X11_XRegisterIMInstantiateCallback(videodata->display, عدم, عدم, عدم, im_instantiate_handler, client_داده);
}

ساكن bool X11_InitIM(SDL_Video_داده *videodata)
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
        destroyed_callback.client_داده_2 = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (حرف *)عدم);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        لكل (صحيح i = 0; i < videodata->numwindows; ++i) {
            SDL_پنجره_داده *w = videodata->windowlist[i];
            إذا (!w->ic) {
                X11_Create_درون_داد_Context(w);
            }
        }

        أرجع true;
    }

    أرجع false;
}
#پایان_اگر // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;
    صحيح i = 0;
    صحيح j = 0;
    صحيح min_keycode, max_keycode;
    بنية
    {
        SDL_Scancode scancode;
        کلید_Sym keysym;
        صحيح مقدار;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_پیشین, 0 },
        { SDL_SCANCODE_به_بالا, XK_به_بالا, 0 },
        { SDL_SCANCODE_چپ, XK_چپ, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    صحيح بهترین_فاصله;
    صحيح بهترین_شاخص;
    صحيح فاصله;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    صحيح xkb_major = Xkb_Major_نسخه;
    صحيح xkb_minor = Xkb_Minor_نسخه;

    إذا (X11_XkbQueryExtension(داده->display, عدم, &داده->keyboard.xkb.event, عدم, &xkb_major, &xkb_minor)) {
        Bool xkb_repeat = 0;
        داده->keyboard.xkb_enabled = true;
        داده->keyboard.xkb.desc_ptr = X11_XkbGetMap(داده->display, Xkb_All_Client_Info_ماسک, XkbUseCoreKbd);

        // This will remove KeyRelease events for held keys.
        X11_Xkb_مجموعه_Detectable_Auto_Repeat(داده->display, True, &xkb_repeat);

        // Enable the key mapping and state events.
        X11_XkbSelectEvents(داده->display, XkbUseCoreKbd,
                            Xkb_New_Keyboard_Notify_ماسک | Xkb_Map_Notify_ماسک | Xkb_State_Notify_ماسک,
                            Xkb_New_Keyboard_Notify_ماسک | Xkb_Map_Notify_ماسک | Xkb_State_Notify_ماسک);
        X11_XkbSelectEventDetails(داده->display, XkbUseCoreKbd, XkbStateNotify, Xkb_گروه_State_ماسک | Xkb_Modifier_State_ماسک, Xkb_گروه_State_ماسک | Xkb_Modifier_State_ماسک);
    } وإلا
#پایان_اگر
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(داده->display, &داده->keyboard.core.min_keycode, &داده->keyboard.core.max_keycode);
        داده->keyboard.core.keysym_map = X11_XGetKeyboardMapping(داده->display, داده->keyboard.core.min_keycode,
                                                              داده->keyboard.core.max_keycode - داده->keyboard.core.min_keycode,
                                                              &داده->keyboard.core.keysyms_در_هر_کلید);
    }

    // Open a connection to the X input manager
#اگر_تعریف_شده X_HAVE_UTF8_STRING
    إذا (SDL_X11_HAVE_UTF8) {
        إذا (!X11_InitIM(داده)) {
            X11_XRegisterIMInstantiateCallback(داده->display, عدم, عدم, عدم, im_instantiate_handler, (XPointer)داده);
        }
    }
#پایان_اگر
    // Try to determine which scancodes are being used based on fingerprint
    بهترین_فاصله = SDL_arraysize(fingerprint) + 1;
    بهترین_شاخص = -1;
    X11_XDisplayKeycodes(داده->display, &min_keycode, &max_keycode);
    لكل (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].مقدار = X11_XKeysym_مقصد_Keycode(داده->display, fingerprint[i].keysym) - min_keycode;
    }
    لكل (i = 0; i < SDL_arraysize(scancode_مجموعه); ++i) {
        صحيح جدول_اندازه;
        ثابت SDL_Scancode *جدول = SDL_Get_Scancode_جدول(scancode_مجموعه[i], &جدول_اندازه);

        فاصله = 0;
        لكل (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            إذا (fingerprint[j].مقدار < 0 || fingerprint[j].مقدار >= جدول_اندازه) {
                فاصله += 1;
            } وإلا إذا (جدول[fingerprint[j].مقدار] != fingerprint[j].scancode) {
                فاصله += 1;
            }
        }
        إذا (فاصله < بهترین_فاصله) {
            بهترین_فاصله = فاصله;
            بهترین_شاخص = i;
        }
    }
    إذا (بهترین_شاخص < 0 || بهترین_فاصله > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        صحيح fingerprint_مقدار = X11_XKeysym_مقصد_Keycode(داده->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        إذا (fingerprint_مقدار == 235) {
            لكل (i = 0; i < SDL_arraysize(scancode_مجموعه); ++i) {
                إذا (scancode_مجموعه[i] == SDL_SCANCODE_جدول_XFREE86_2) {
                    بهترین_شاخص = i;
                    بهترین_فاصله = 0;
                    اكسر;
                }
            }
        }
    }
    إذا (بهترین_شاخص >= 0 && بهترین_فاصله <= 2) {
        صحيح جدول_اندازه;
        ثابت SDL_Scancode *جدول = SDL_Get_Scancode_جدول(scancode_مجموعه[بهترین_شاخص], &جدول_اندازه);

#اگر_تعریف_شده DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", بهترین_شاخص, min_keycode, max_keycode, جدول_اندازه);
#پایان_اگر
        // This should never happen, but just in case...
        إذا (جدول_اندازه > (SDL_arraysize(داده->keyboard.کلید_layout) - min_keycode)) {
            جدول_اندازه = (SDL_arraysize(داده->keyboard.کلید_layout) - min_keycode);
        }
        SDL_memcpy(&داده->keyboard.کلید_layout[min_keycode], جدول, حجم(SDL_Scancode) * جدول_اندازه);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        لكل (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_کلید_کد_مقصد_SDLScancode(_this, i);
#اگر_تعریف_شده DEBUG_KEYBOARD
            {
                کلید_Sym sym;
                sym = X11_کلید_کد_مقصد_Sym(_this, (کلید_کد_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (بیعلامت صحيح)sym, sym == No_نماد ? "NoSymbol" : X11_XKeysym_مقصد_String(sym));
            }
#پایان_اگر
            إذا (scancode == داده->keyboard.کلید_layout[i]) {
                استمر;
            }
            إذا ((SDL_GetKeymapKeycode(عدم, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_ماسک | SDLK_EXTENDED_ماسک)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#اگر_تعریف_شده DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", داده->کلید_layout[i], SDL_GetScancodeName(داده->کلید_layout[i]), scancode, SDL_GetScancodeName(scancode));
#پایان_اگر
                داده->keyboard.کلید_layout[i] = scancode;
            }
        }
    } وإلا {
#اگر_تعریف_شده DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#پایان_اگر

        // Determine key_layout - only works on US QWERTY layout
        لكل (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_کلید_کد_مقصد_SDLScancode(_this, i);
#اگر_تعریف_شده DEBUG_SCANCODES
            {
                کلید_Sym sym;
                sym = X11_کلید_کد_مقصد_Sym(_this, (کلید_کد_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (بیعلامت صحيح)sym, sym == No_نماد ? "NoSymbol" : X11_XKeysym_مقصد_String(sym));
            }
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } وإلا {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#پایان_اگر
            داده->keyboard.کلید_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_مجموعه_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    أرجع true;
}

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
ساكن بیعلامت صحيح X11_Get_Xkb_Virtual_Modifier_ماسک(SDL_VideoDevice *_this, ثابت حرف *vmod_name)
{
    SDL_Video_داده *videodata = _this->داخلی;
    بیعلامت صحيح mod_ماسک = 0;

    ثابت Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    إذا (vmod != None) {
        لكل (صحيح i = 0; i < Xkb_رقم_Virtual_Mods; ++i) {
            إذا (vmod == videodata->keyboard.xkb.desc_ptr->نامها->vmods[i]) {
                mod_ماسک = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                اكسر;
            }
        }
    }

    أرجع mod_ماسک;
}
#پایان_اگر

ساكن بیعلامت X11_Get_XModifier_ماسک(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_Video_داده *videodata = _this->داخلی;
    Display *display = videodata->display;
    بیعلامت صحيح mod_ماسک = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    بیعلامت صحيح n = xmods->max_keypermod;
    لكل (صحيح i = 3; i < 8; i++) {
        لكل (صحيح j = 0; j < n; j++) {
            ثابت کلید_کد_2 kc = xmods->modifiermap[i * n + j];
            إذا (videodata->keyboard.کلید_layout[kc] == scancode) {
                mod_ماسک = 1 << i;
                اكسر;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    أرجع mod_ماسک;
}

ساكن فراغ X11_جمع_کن_Keymap_مدخل(SDL_Keymap *keymap, Uint32 xkeycode, کلید_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_ماسک)
{
    SDL_Keycode keycode = SDL_Get_کلید_کد_From_کلید_Sym(xkeysym, xkeycode, sdl_mod_ماسک);

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
            keycode = SDL_SCANCODE_مقصد_KEYCODE(sdl_scancode);
            اكسر;
        }
    }

    SDL_مجموعه_Keymap_مدخل(keymap, sdl_scancode, sdl_mod_ماسک, keycode);
}

فراغ X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_Video_داده *داده = _this->داخلی;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (داده->keyboard.xkb_enabled) {
        XkbStateRec state;

        لكل (بیعلامت صحيح i = 0; i < Xkb_رقم_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(داده->keyboard.xkb.keymaps[i]);
            داده->keyboard.xkb.keymaps[i] = عدم;
        }

        X11_Xkb_Get_نامها(داده->display, Xkb_Virtual_Mod_نامها_ماسک, داده->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(داده->display, Xkb_All_Client_Info_ماسک | Xkb_Virtual_Mods_ماسک, داده->keyboard.xkb.desc_ptr);

        إذا (X11_XkbGetState(داده->display, XkbUseCoreKbd, &state) == Success) {
            داده->keyboard.xkb.current_گروه = state.گروه;
        }

        داده->keyboard.alt_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "Alt");
        إذا (!داده->keyboard.alt_ماسک) {
            داده->keyboard.alt_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "Meta");
        }
        داده->keyboard.gui_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "Super");
        داده->keyboard.level3_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "LevelThree");
        داده->keyboard.level5_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "LevelFive");
        داده->keyboard.numlock_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "NumLock");
        داده->keyboard.scrolllock_ماسک = X11_Get_Xkb_Virtual_Modifier_ماسک(_this, "ScrollLock");

        لكل (بیعلامت صحيح i = 0; i < Xkb_رقم_Kbd_Groups; ++i) {
            داده->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            إذا (!داده->keyboard.xkb.keymaps[i]) {
                لكل (بیعلامت صحيح j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(داده->keyboard.xkb.keymaps[i]);
                    داده->keyboard.xkb.keymaps[j] = عدم;
                }

                أرجع;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ثابت Uint32 valid_mod_ماسک = لغزش_ماسک_2 | قفل_ماسک | داده->keyboard.alt_ماسک | داده->keyboard.level3_ماسک | داده->keyboard.level5_ماسک;

        لكل (Uint32 xkeycode = داده->keyboard.xkb.desc_ptr->min_کلید_کد; xkeycode < داده->keyboard.xkb.desc_ptr->max_کلید_کد; ++xkeycode) {
            ثابت SDL_Scancode scancode = داده->keyboard.کلید_layout[xkeycode];
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                استمر;
            }

            لكل (Uint32 گروه = 0; گروه < Xkb_رقم_Kbd_Groups; ++گروه) {
                SDL_Keymap *keymap = داده->keyboard.xkb.keymaps[گروه];

                Uint32 effective_گروه = گروه;
                ثابت بیعلامت حرف max_کلید_گروه = Xkb_کلید_رقم_Groups(داده->keyboard.xkb.desc_ptr, xkeycode);
                ثابت بیعلامت حرف کلید_گروه_info = Xkb_کلید_گروه_Info(داده->keyboard.xkb.desc_ptr, xkeycode);

                إذا (max_کلید_گروه && effective_گروه >= max_کلید_گروه) {
                    ثابت بیعلامت حرف action = Xkb_بیرون_از_Range_گروه_Action(کلید_گروه_info);

                    بدل (action) {
                    افتراضي:
                        effective_گروه %= max_کلید_گروه;
                        اكسر;
                    حالة XkbClampIntoRange:
                        effective_گروه = max_کلید_گروه - 1;
                        اكسر;
                    حالة XkbRedirectIntoRange:
                        effective_گروه = Xkb_بیرون_از_Range_گروه_عدد(کلید_گروه_info);
                        إذا (effective_گروه >= max_کلید_گروه) {
                            effective_گروه = 0;
                        }
                        اكسر;
                    }
                }

                Xkb_کلید_Type_Ptr کلید_type = Xkb_کلید_کلید_Type(داده->keyboard.xkb.desc_ptr, xkeycode, effective_گروه);

                لكل (Uint32 level = 0; level < کلید_type->رقم_سطوح; ++level) {
                    ثابت کلید_Sym keysym = X11_کلید_کد_مقصد_Sym(_this, xkeycode, effective_گروه, level);

                    إذا (keysym != No_نماد) {
                        bool کلید_added = false;

                        لكل (صحيح map_idx = 0; map_idx < کلید_type->map_شمار; ++map_idx) {
                            إذا (کلید_type->map[map_idx].فعال && کلید_type->map[map_idx].level == level) {
                                ثابت بیعلامت صحيح xkb_mod_ماسک = کلید_type->map[map_idx].mods.ماسک;
                                إذا ((xkb_mod_ماسک | valid_mod_ماسک) == valid_mod_ماسک) {
                                    ثابت SDL_Keymod sdl_mod_ماسک = (xkb_mod_ماسک & لغزش_ماسک_2 ? SDL_KMOD_لغزش : 0) |
                                                                    (xkb_mod_ماسک & قفل_ماسک ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_ماسک & داده->keyboard.alt_ماسک ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_ماسک & داده->keyboard.level3_ماسک ? SDL_KMOD_نما : 0) |
                                                                    (xkb_mod_ماسک & داده->keyboard.level5_ماسک ? SDL_KMOD_LEVEL5 : 0);

                                    X11_جمع_کن_Keymap_مدخل(keymap, xkeycode, keysym, scancode, sdl_mod_ماسک);
                                    کلید_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        إذا (!level && !کلید_added) {
                            X11_جمع_کن_Keymap_مدخل(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_مجموعه_Keymap(داده->keyboard.xkb.keymaps[داده->keyboard.xkb.current_گروه], send_event);
    } وإلا
#پایان_اگر
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        إذا (!keymap) {
            أرجع;
        }

        إذا (send_event) {
            إذا (داده->keyboard.core.keysym_map) {
                X11_XFree(داده->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(داده->display, &داده->keyboard.core.min_keycode, &داده->keyboard.core.max_keycode);
            داده->keyboard.core.keysym_map = X11_XGetKeyboardMapping(داده->display, داده->keyboard.core.min_keycode,
                                                                     داده->keyboard.core.max_keycode - داده->keyboard.core.min_keycode,
                                                                     &داده->keyboard.core.keysyms_در_هر_کلید);
        }

        لكل (Uint32 xkeycode = داده->keyboard.core.min_keycode; xkeycode <= داده->keyboard.core.max_keycode; ++xkeycode) {
            ثابت SDL_Scancode scancode = داده->keyboard.کلید_layout[xkeycode];
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                استمر;
            }

            ثابت کلید_Sym keysym = X11_کلید_کد_مقصد_Sym(_this, xkeycode, 0, 0);
            إذا (keysym != No_نماد) {
                X11_جمع_کن_Keymap_مدخل(keymap, xkeycode, keysym, scancode, 0);
            }
        }

        داده->keyboard.alt_ماسک = Mod1_ماسک; // Alt or Meta
        داده->keyboard.gui_ماسک = Mod4_ماسک; // Super
        داده->keyboard.level3_ماسک = Mod5_ماسک; // Note: Not a typo, Mod5 = level 3 shift, and Mod3 = level 5 shift.
        داده->keyboard.level5_ماسک = Mod3_ماسک;
        داده->keyboard.numlock_ماسک = X11_Get_XModifier_ماسک(_this, SDL_SCANCODE_NUMLOCKCLEAR);
        داده->keyboard.scrolllock_ماسک = X11_Get_XModifier_ماسک(_this, SDL_SCANCODE_SCROLLLOCK);

        SDL_مجموعه_Keymap(keymap, send_event);
    }
}

فراغ X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;

#اگر_تعریف_شده X_HAVE_UTF8_STRING
    إذا (داده->im) {
        X11_XCloseIM(داده->im);
        داده->im = عدم;
    } وإلا {
        X11_XUnregisterIMInstantiateCallback(داده->display, عدم, عدم, عدم, im_instantiate_handler, (XPointer)داده);
    }
#پایان_اگر // X_HAVE_UTF8_STRING

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (داده->keyboard.xkb_enabled) {
        لكل (صحيح i = 0; i < Xkb_رقم_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(داده->keyboard.xkb.keymaps[i]);
            داده->keyboard.xkb.keymaps[i] = عدم;
        }

        إذا (داده->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(داده->keyboard.xkb.desc_ptr, 0, True);
            داده->keyboard.xkb.desc_ptr = عدم;
        }
    } وإلا
#پایان_اگر
        إذا (داده->keyboard.core.keysym_map) {
        X11_XFree(داده->keyboard.core.keysym_map);
        داده->keyboard.core.keysym_map = عدم;
    }
}

فراغ X11_ClearComposition(SDL_پنجره_داده *داده)
{
    إذا (داده->preedit_درازی > 0) {
        داده->preedit_متن[0] = '\0';
        داده->preedit_درازی = 0;
    }

    إذا (داده->ime_needs_clear_composition) {
        SDL_Send_Editing_متن("", 0, 0);
        داده->ime_needs_clear_composition = false;
    }
}

ساكن فراغ X11_SendEditingEvent(SDL_پنجره_داده *داده)
{
    إذا (داده->preedit_درازی == 0) {
        X11_ClearComposition(داده);
        أرجع;
    }

    bool درون_highlight = false;
    صحيح شروع = -1, درازی = 0, i;
    لكل (i = 0; i < داده->preedit_درازی; ++i) {
        إذا (داده->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            إذا (شروع < 0) {
                شروع = i;
                درون_highlight = true;
            }
        } وإلا إذا (درون_highlight) {
            // Found the end of the highlight
            اكسر;
        }
    }
    إذا (درون_highlight) {
        درازی = (i - شروع);
    } وإلا {
        شروع = SDL_clamp(داده->preedit_cursor, 0, داده->preedit_درازی);
    }
    SDL_Send_Editing_متن(داده->preedit_متن, شروع, درازی);

    داده->ime_needs_clear_composition = true;
}

#اگر_تعریف_شده X_HAVE_UTF8_STRING
ساكن صحيح preedit_شروع_callback(XIC xic, XPointer client_داده_2, XPointer call_داده_2)
{
    // No limit on preedit text length
    أرجع -1;
}

ساكن فراغ preedit_انجامشده_callback(XIC xic, XPointer client_داده_2, XPointer call_داده_2)
{
}

ساكن فراغ preedit_draw_callback(XIC xic, XPointer client_داده_2, XIMPreeditDrawCallbackStruct *call_داده_2)
{
    SDL_پنجره_داده *داده = (SDL_پنجره_داده *)client_داده_2;
    صحيح chg_اولی = SDL_clamp(call_داده_2->chg_اولی, 0, داده->preedit_درازی);
    صحيح chg_درازی = SDL_clamp(call_داده_2->chg_درازی, 0, داده->preedit_درازی - chg_اولی);

    ثابت حرف *شروع = داده->preedit_متن;
    إذا (chg_درازی > 0) {
        // Delete text in range
        لكل (صحيح i = 0; شروع && *شروع && i < chg_اولی; ++i) {
            SDL_گام_UTF8(&شروع, عدم);
        }

        ثابت حرف *انتها = شروع;
        لكل (صحيح i = 0; انتها && *انتها && i < chg_درازی; ++i) {
            SDL_گام_UTF8(&انتها, عدم);
        }

        إذا (انتها > شروع) {
            SDL_memmove((حرف *)شروع, انتها, SDL_strlen(انتها) + 1);
            إذا ((chg_اولی + chg_درازی) > داده->preedit_درازی) {
                SDL_memmove(&داده->preedit_feedback[chg_اولی], &داده->preedit_feedback[chg_اولی + chg_درازی], (داده->preedit_درازی - chg_اولی - chg_درازی) * حجم(*داده->preedit_feedback));
            }
        }
        داده->preedit_درازی -= chg_درازی;
    }

    XIMText *متن = call_داده_2->متن;
    إذا (متن) {
        // Insert text in range
        SDL_assert(!متن->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        إذا (متن->string.multi_byte) {
            متن->درازی = SDL_utf8strlen(متن->string.multi_byte);
        }

        size_t string_اندازه = SDL_strlen(متن->string.multi_byte);
        size_t اندازه = string_اندازه + 1;
        إذا (داده->preedit_متن) {
            اندازه += SDL_strlen(داده->preedit_متن);
        }
        حرف *preedit_متن = (حرف *)SDL_malloc(اندازه * حجم(*preedit_متن));
        إذا (preedit_متن) {
            size_t pre_اندازه = (شروع - داده->preedit_متن);
            size_t post_اندازه = شروع ? SDL_strlen(شروع) : 0;
            إذا (pre_اندازه > 0) {
                SDL_memcpy(&preedit_متن[0], داده->preedit_متن, pre_اندازه);
            }
            SDL_memcpy(&preedit_متن[pre_اندازه], متن->string.multi_byte, string_اندازه);
            إذا (post_اندازه > 0) {
                SDL_memcpy(&preedit_متن[pre_اندازه + string_اندازه], شروع, post_اندازه);
            }
            preedit_متن[اندازه - 1] = '\0';
        }

        size_t feedback_اندازه = داده->preedit_درازی + متن->درازی;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_اندازه * حجم(*feedback));
        إذا (feedback) {
            size_t pre_اندازه = (size_t)chg_اولی;
            size_t post_اندازه = (size_t)داده->preedit_درازی - pre_اندازه;
            إذا (pre_اندازه > 0) {
                SDL_memcpy(&feedback[0], داده->preedit_feedback, pre_اندازه * حجم(*feedback));
            }
            SDL_memcpy(&feedback[pre_اندازه], متن->feedback, متن->درازی * حجم(*feedback));
            إذا (post_اندازه > 0) {
                SDL_memcpy(&feedback[pre_اندازه + متن->درازی], &داده->preedit_feedback[pre_اندازه], post_اندازه * حجم(*feedback));
            }
        }

        إذا (preedit_متن && feedback) {
            SDL_free(داده->preedit_متن);
            داده->preedit_متن = preedit_متن;

            SDL_free(داده->preedit_feedback);
            داده->preedit_feedback = feedback;

            داده->preedit_درازی += متن->درازی;
        } وإلا {
            SDL_free(preedit_متن);
            SDL_free(feedback);
        }
    }

    داده->preedit_cursor = call_داده_2->caret;

#اگر_تعریف_شده DEBUG_XIM
    إذا (call_داده_2->chg_درازی > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_داده_2->chg_درازی, call_داده_2->chg_اولی);
    }
    إذا (متن) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", متن->string.multi_byte, call_داده_2->chg_اولی, call_داده_2->caret);
    }
    SDL_Log("Pre-edit text: %s", داده->preedit_متن);
#پایان_اگر

    X11_SendEditingEvent(داده);
}

ساكن فراغ preedit_caret_callback(XIC xic, XPointer client_داده_2, XIMPreeditCaretCallbackStruct *call_داده_2)
{
    SDL_پنجره_داده *داده = (SDL_پنجره_داده *)client_داده_2;

    بدل (call_داده_2->direction) {
    حالة XIMAbsolutePosition:
        إذا (call_داده_2->position != داده->preedit_cursor) {
            داده->preedit_cursor = call_داده_2->position;
            X11_SendEditingEvent(داده);
        }
        اكسر;
    حالة XIMDontChange:
        اكسر;
    افتراضي:
        // Not currently supported
        اكسر;
    }
}

ساكن فراغ ic_destroyed_handler(XIC ic, XPointer client_داده, XPointer call_داده)
{
    SDL_پنجره_داده *داده = (SDL_پنجره_داده *)client_داده;
    داده->ic = عدم;
    X11_Destroy_درون_داد_Context(داده);

    // If the IM was already recreated, create a new IC.
    إذا (داده->videodata->im) {
        X11_Create_درون_داد_Context(داده);
    }
}
#پایان_اگر // X_HAVE_UTF8_STRING

فراغ X11_Create_درون_داد_Context(SDL_پنجره_داده *داده)
{
#اگر_تعریف_شده X_HAVE_UTF8_STRING
    SDL_Video_داده *videodata = داده->videodata;

    إذا (SDL_X11_HAVE_UTF8 && videodata->im) {
        ثابت حرف *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_داده_2 = (XPointer)داده;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        إذا (hint && SDL_strstr(hint, "composition")) {
            XIMCallback draw_callback;
            draw_callback.client_داده_2 = (XPointer)داده;
            draw_callback.callback = (XIMProc)preedit_draw_callback;

            XIMCallback شروع_callback;
            شروع_callback.client_داده_2 = (XPointer)داده;
            شروع_callback.callback = (XIMProc)preedit_شروع_callback;

            XIMCallback انجامشده_callback;
            انجامشده_callback.client_داده_2 = (XPointer)داده;
            انجامشده_callback.callback = (XIMProc)preedit_انجامشده_callback;

            XIMCallback caret_callback;
            caret_callback.client_داده_2 = (XPointer)داده;
            caret_callback.callback = (XIMProc)preedit_caret_callback;

            XVaNestedList attr = X11_XVaCreateNestedList(0,
                                                         XNPreedit_شروع_Callback, &شروع_callback,
                                                         XNPreedit_انجامشده_Callback, &انجامشده_callback,
                                                         XNPreeditDrawCallback, &draw_callback,
                                                         XNPreeditCaretCallback, &caret_callback,
                                                         عدم);
            إذا (attr) {
                داده->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreedit_صفات, attr,
                                         XNClient_پنجره, داده->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         عدم);
                X11_XFree(attr);
            }
        }
        إذا (!داده->ic) {
            داده->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClient_پنجره, داده->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     عدم);
        }
        داده->xim_spot.x = -1;
        داده->xim_spot.y = -1;
    }
#پایان_اگر // X_HAVE_UTF8_STRING
}


فراغ X11_Destroy_درون_داد_Context(SDL_پنجره_داده *داده)
{
#اگر_تعریف_شده X_HAVE_UTF8_STRING
    إذا (داده->ic) {
        X11_XDestroyIC(داده->ic);
        داده->ic = عدم;
    }
    SDL_free(داده->preedit_متن);
    SDL_free(داده->preedit_feedback);
    داده->preedit_متن = عدم;
    داده->preedit_feedback = عدم;
#پایان_اگر
}

ساكن فراغ X11_ResetXIM(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#اگر_تعریف_شده X_HAVE_UTF8_STRING
    SDL_پنجره_داده *داده = پنجره->داخلی;

    إذا (داده && داده->ic) {
        // Clear any partially entered dead keys
        حرف *contents = X11_Xutf8ResetIC(داده->ic);
        إذا (contents) {
            X11_XFree(contents);
        }
    }
#پایان_اگر // X_HAVE_UTF8_STRING
}

bool X11_شروع_متن_درون_داد(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, پنجره);

    أرجع X11_Update_متن_درون_داد_Area(_this, پنجره);
}

bool X11_Stop_متن_درون_داد(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    X11_ResetXIM(_this, پنجره);
    أرجع true;
}

bool X11_Update_متن_درون_داد_Area(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#اگر_تعریف_شده X_HAVE_UTF8_STRING
    SDL_پنجره_داده *داده = پنجره->داخلی;

    إذا (داده && داده->ic) {
        XPoint spot;
        spot.x = پنجره->متن_درون_داد_rect.x + پنجره->متن_درون_داد_cursor;
        spot.y = پنجره->متن_درون_داد_rect.y + پنجره->متن_درون_داد_rect.h;
        إذا (spot.x != داده->xim_spot.x || spot.y != داده->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, عدم);
            إذا (attr) {
                X11_XSetICValues(داده->ic, XNPreedit_صفات, attr, عدم);
                X11_XFree(attr);
            }
            SDL_copyp(&داده->xim_spot, &spot);
        }
    }
#پایان_اگر
    أرجع true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_Video_داده *videodata = _this->داخلی;
    أرجع videodata->use_steam_screen_keyboard;
}

فراغ X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props)
{
    SDL_Video_داده *videodata = _this->داخلی;

    إذا (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ثابت صحيح k_EFloating_Gamepad_متن_درون_داد_نما_نما_Single_سطر = 0;    // Enter dismisses the keyboard
        ثابت صحيح k_EFloating_Gamepad_متن_درون_داد_نما_نما_مضرب_سطرها = 1; // User needs to explicitly dismiss the keyboard
        ثابت صحيح k_EFloating_Gamepad_متن_درون_داد_نما_نما_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ثابت صحيح k_EFloating_Gamepad_متن_درون_داد_نما_نما_Numeric = 3;       // Numeric keypad is shown
        حرف deeplink[128];
        صحيح نما;

        بدل (SDL_Get_متن_درون_داد_Type(props)) {
        حالة SDL_TEXTINPUT_TYPE_متن_EMAIL:
            نما = k_EFloating_Gamepad_متن_درون_داد_نما_نما_Email;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_عدد:
        حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
        حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_VISIBLE:
            نما = k_EFloating_Gamepad_متن_درون_داد_نما_نما_Numeric;
            اكسر;
        افتراضي:
            إذا (SDL_Get_متن_درون_داد_Multiline(props)) {
                نما = k_EFloating_Gamepad_متن_درون_داد_نما_نما_مضرب_سطرها;
            } وإلا {
                نما = k_EFloating_Gamepad_متن_درون_داد_نما_نما_Single_سطر;
            }
            اكسر;
        }
        (فراغ)SDL_snprintf(deeplink, حجم(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           پنجره->متن_درون_داد_rect.x, پنجره->متن_درون_داد_rect.y,
                           پنجره->متن_درون_داد_rect.w, پنجره->متن_درون_داد_rect.h,
                           نما);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

فراغ X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *videodata = _this->داخلی;

    إذا (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#پایان_اگر // SDL_VIDEO_DRIVER_X11
