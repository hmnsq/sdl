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

#অন্তর্ভাব "SDL_x11video.h"

#অন্তর্ভাব "../../events/SDL_keyboard_c.h"
#অন্তর্ভাব "../../events/SDL_scancode_tables_c.h"

#অন্তর্ভাব <X11/keysym.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#অন্তর্ভাব <X11/XKBlib.h>
#endif

#অন্তর্ভাব "../../events/imKStoUCS.h"
#অন্তর্ভাব "../../events/SDL_keysym_to_scancode_c.h"
#অন্তর্ভাব "../../events/SDL_keysym_to_keycode_c.h"

#ifdef X_HAVE_UTF8_STRING
#অন্তর্ভাব <locale.h>
#endif

স্থির SDL_ScancodeTable scancode_set[] = {
    SDL_SCANCODE_TABLE_DARWIN,
    SDL_SCANCODE_TABLE_XFREE86_1,
    SDL_SCANCODE_TABLE_XFREE86_2,
    SDL_SCANCODE_TABLE_XVNC,
};

স্থির bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    নির্বাচন (scancode) {
    ক্ষেত্র SDL_SCANCODE_ESCAPE:
    ক্ষেত্র SDL_SCANCODE_CAPSLOCK:
    ক্ষেত্র SDL_SCANCODE_NUMLOCKCLEAR:
    ক্ষেত্র SDL_SCANCODE_LSHIFT:
    ক্ষেত্র SDL_SCANCODE_RSHIFT:
    ক্ষেত্র SDL_SCANCODE_LCTRL:
    ক্ষেত্র SDL_SCANCODE_RCTRL:
    ক্ষেত্র SDL_SCANCODE_LALT:
    ক্ষেত্র SDL_SCANCODE_RALT:
    ক্ষেত্র SDL_SCANCODE_LGUI:
    ক্ষেত্র SDL_SCANCODE_RGUI:
        ফেরত false;
    পূর্বনির্ধারিত:
        ফেরত true;
    }
}

স্থির চাবি_Sym X11_চাবি_Code_To_Sym(SDL_VideoDevice *_this, চাবি_Code_2 keycode, unsigned পূর্ণসংখ্যা group, unsigned পূর্ণসংখ্যা level)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    চাবি_Sym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    যদি (তথ্য->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(তথ্য->display, keycode, group, level);
    } অন্যথা
#endif
    {
        // TODO: Handle groups on the legacy path.
        যদি (keycode >= তথ্য->keyboard.core.min_keycode && keycode <= তথ্য->keyboard.core.max_keycode) {
            keysym = তথ্য->keyboard.core.keysym_map[(keycode - তথ্য->keyboard.core.min_keycode) * তথ্য->keyboard.core.keysyms_per_চাবি];
        } অন্যথা {
            keysym = No_প্রতীক;
        }
    }

    ফেরত keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
স্থির SDL_Scancode X11_চাবি_Code_To_SDLScancode(SDL_VideoDevice *_this, চাবি_Code_2 keycode)
{
    ধ্রুবক চাবি_Sym keysym = X11_চাবি_Code_To_Sym(_this, keycode, 0, 0);

    যদি (keysym == No_প্রতীক) {
        ফেরত SDL_SCANCODE_UNKNOWN;
    }

    ফেরত SDL_Get_Scancode_From_চাবি_Sym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
স্থির bool X11_InitIM(SDL_Video_তথ্য *videodata);

স্থির শূন্য im_instantiate_handler(Display *display, XPointer client_তথ্য, XPointer call_তথ্য)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)client_তথ্য;

    যদি (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, ফাঁকা, ফাঁকা, ফাঁকা, im_instantiate_handler, client_তথ্য);
    }
}

স্থির শূন্য im_destroyed_handler(XIM im, XPointer client_তথ্য, XPointer call_তথ্য)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)client_তথ্য;

    videodata->im = ফাঁকা;
    X11_XRegisterIMInstantiateCallback(videodata->display, ফাঁকা, ফাঁকা, ফাঁকা, im_instantiate_handler, client_তথ্য);
}

স্থির bool X11_InitIM(SDL_Video_তথ্য *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    অক্ষর *পূর্ব_locale = setlocale(LC_ALL, ফাঁকা);
    অক্ষর *পূর্ব_xmods = X11_XSetLocaleModifiers(ফাঁকা);

    যদি (পূর্ব_locale) {
        পূর্ব_locale = SDL_strdup(পূর্ব_locale);
    }

    যদি (পূর্ব_xmods) {
        পূর্ব_xmods = SDL_strdup(পূর্ব_xmods);
    }

    (শূন্য)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, ফাঁকা, ফাঁকা, ফাঁকা);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (শূন্য)setlocale(LC_ALL, পূর্ব_locale);
    X11_XSetLocaleModifiers(পূর্ব_xmods);

    SDL_free(পূর্ব_locale);
    SDL_free(পূর্ব_xmods);

    যদি (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_তথ্য_2 = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (অক্ষর *)ফাঁকা);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        জন্য (পূর্ণসংখ্যা i = 0; i < videodata->numwindows; ++i) {
            SDL_Window_তথ্য *w = videodata->windowlist[i];
            যদি (!w->ic) {
                X11_Create_প্রবেশ_Context(w);
            }
        }

        ফেরত true;
    }

    ফেরত false;
}
#endif // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    পূর্ণসংখ্যা i = 0;
    পূর্ণসংখ্যা j = 0;
    পূর্ণসংখ্যা min_keycode, max_keycode;
    কাঠামো
    {
        SDL_Scancode scancode;
        চাবি_Sym keysym;
        পূর্ণসংখ্যা মান;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_বাম, XK_বাম, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    পূর্ণসংখ্যা best_distance;
    পূর্ণসংখ্যা best_সূচক;
    পূর্ণসংখ্যা distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    পূর্ণসংখ্যা xkb_major = XkbMajorVersion;
    পূর্ণসংখ্যা xkb_minor = XkbMinorVersion;

    যদি (X11_XkbQueryExtension(তথ্য->display, ফাঁকা, &তথ্য->keyboard.xkb.event, ফাঁকা, &xkb_major, &xkb_minor)) {
        Bool xkb_repeat = 0;
        তথ্য->keyboard.xkb_enabled = true;
        তথ্য->keyboard.xkb.desc_ptr = X11_XkbGetMap(তথ্য->display, XkbAllClientInfoMask, XkbUseCoreKbd);

        // This will remove KeyRelease events for held keys.
        X11_XkbSetDetectableAutoRepeat(তথ্য->display, True, &xkb_repeat);

        // Enable the key mapping and state events.
        X11_XkbSelectEvents(তথ্য->display, XkbUseCoreKbd,
                            XkbNewKeyboardNotifyMask | XkbMapNotifyMask | XkbStateNotifyMask,
                            XkbNewKeyboardNotifyMask | XkbMapNotifyMask | XkbStateNotifyMask);
        X11_XkbSelectEventDetails(তথ্য->display, XkbUseCoreKbd, XkbStateNotify, XkbGroupStateMask | XkbModifierStateMask, XkbGroupStateMask | XkbModifierStateMask);
    } অন্যথা
#endif
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(তথ্য->display, &তথ্য->keyboard.core.min_keycode, &তথ্য->keyboard.core.max_keycode);
        তথ্য->keyboard.core.keysym_map = X11_XGetKeyboardMapping(তথ্য->display, তথ্য->keyboard.core.min_keycode,
                                                              তথ্য->keyboard.core.max_keycode - তথ্য->keyboard.core.min_keycode,
                                                              &তথ্য->keyboard.core.keysyms_per_চাবি);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    যদি (SDL_X11_HAVE_UTF8) {
        যদি (!X11_InitIM(তথ্য)) {
            X11_XRegisterIMInstantiateCallback(তথ্য->display, ফাঁকা, ফাঁকা, ফাঁকা, im_instantiate_handler, (XPointer)তথ্য);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_সূচক = -1;
    X11_XDisplayKeycodes(তথ্য->display, &min_keycode, &max_keycode);
    জন্য (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].মান = X11_XKeysymToKeycode(তথ্য->display, fingerprint[i].keysym) - min_keycode;
    }
    জন্য (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        পূর্ণসংখ্যা table_আকার;
        ধ্রুবক SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_আকার);

        distance = 0;
        জন্য (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            যদি (fingerprint[j].মান < 0 || fingerprint[j].মান >= table_আকার) {
                distance += 1;
            } অন্যথা যদি (table[fingerprint[j].মান] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        যদি (distance < best_distance) {
            best_distance = distance;
            best_সূচক = i;
        }
    }
    যদি (best_সূচক < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        পূর্ণসংখ্যা fingerprint_মান = X11_XKeysymToKeycode(তথ্য->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        যদি (fingerprint_মান == 235) {
            জন্য (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                যদি (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_সূচক = i;
                    best_distance = 0;
                    বিরতি;
                }
            }
        }
    }
    যদি (best_সূচক >= 0 && best_distance <= 2) {
        পূর্ণসংখ্যা table_আকার;
        ধ্রুবক SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_সূচক], &table_আকার);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_সূচক, min_keycode, max_keycode, table_আকার);
#endif
        // This should never happen, but just in case...
        যদি (table_আকার > (SDL_arraysize(তথ্য->keyboard.চাবি_layout) - min_keycode)) {
            table_আকার = (SDL_arraysize(তথ্য->keyboard.চাবি_layout) - min_keycode);
        }
        SDL_memcpy(&তথ্য->keyboard.চাবি_layout[min_keycode], table, আকার(SDL_Scancode) * table_আকার);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        জন্য (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_চাবি_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                চাবি_Sym sym;
                sym = X11_চাবি_Code_To_Sym(_this, (চাবি_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned পূর্ণসংখ্যা)sym, sym == No_প্রতীক ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            যদি (scancode == তথ্য->keyboard.চাবি_layout[i]) {
                চালু;
            }
            যদি ((SDL_GetKeymapKeycode(ফাঁকা, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", তথ্য->চাবি_layout[i], SDL_GetScancodeName(তথ্য->চাবি_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                তথ্য->keyboard.চাবি_layout[i] = scancode;
            }
        }
    } অন্যথা {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        জন্য (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_চাবি_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                চাবি_Sym sym;
                sym = X11_চাবি_Code_To_Sym(_this, (চাবি_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned পূর্ণসংখ্যা)sym, sym == No_প্রতীক ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            যদি (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } অন্যথা {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            তথ্য->keyboard.চাবি_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    ফেরত true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
স্থির unsigned পূর্ণসংখ্যা X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *vmod_name)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    unsigned পূর্ণসংখ্যা mod_mask = 0;

    ধ্রুবক Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    যদি (vmod != None) {
        জন্য (পূর্ণসংখ্যা i = 0; i < Xkb_অঙ্ক_Virtual_Mods; ++i) {
            যদি (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                বিরতি;
            }
        }
    }

    ফেরত mod_mask;
}
#endif

স্থির unsigned X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    Display *display = videodata->display;
    unsigned পূর্ণসংখ্যা mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    unsigned পূর্ণসংখ্যা n = xmods->max_keypermod;
    জন্য (পূর্ণসংখ্যা i = 3; i < 8; i++) {
        জন্য (পূর্ণসংখ্যা j = 0; j < n; j++) {
            ধ্রুবক চাবি_Code_2 kc = xmods->modifiermap[i * n + j];
            যদি (videodata->keyboard.চাবি_layout[kc] == scancode) {
                mod_mask = 1 << i;
                বিরতি;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    ফেরত mod_mask;
}

স্থির শূন্য X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, চাবি_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_চাবি_Code_From_চাবি_Sym(xkeysym, xkeycode, sdl_mod_mask);

    যদি (!keycode) {
        নির্বাচন (sdl_scancode) {
        ক্ষেত্র SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            বিরতি;
        ক্ষেত্র SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            বিরতি;
        ক্ষেত্র SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            বিরতি;
        ক্ষেত্র SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            বিরতি;
        পূর্বনির্ধারিত:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            বিরতি;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

শূন্য X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    যদি (তথ্য->keyboard.xkb_enabled) {
        XkbStateRec state;

        জন্য (unsigned পূর্ণসংখ্যা i = 0; i < Xkb_অঙ্ক_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(তথ্য->keyboard.xkb.keymaps[i]);
            তথ্য->keyboard.xkb.keymaps[i] = ফাঁকা;
        }

        X11_XkbGetNames(তথ্য->display, XkbVirtualModNamesMask, তথ্য->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(তথ্য->display, XkbAllClientInfoMask | XkbVirtualModsMask, তথ্য->keyboard.xkb.desc_ptr);

        যদি (X11_XkbGetState(তথ্য->display, XkbUseCoreKbd, &state) == Success) {
            তথ্য->keyboard.xkb.current_group = state.group;
        }

        তথ্য->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        যদি (!তথ্য->keyboard.alt_mask) {
            তথ্য->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        তথ্য->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        তথ্য->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        তথ্য->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        তথ্য->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        তথ্য->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        জন্য (unsigned পূর্ণসংখ্যা i = 0; i < Xkb_অঙ্ক_Kbd_Groups; ++i) {
            তথ্য->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            যদি (!তথ্য->keyboard.xkb.keymaps[i]) {
                জন্য (unsigned পূর্ণসংখ্যা j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(তথ্য->keyboard.xkb.keymaps[i]);
                    তথ্য->keyboard.xkb.keymaps[j] = ফাঁকা;
                }

                ফেরত;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ধ্রুবক Uint32 valid_mod_mask = ShiftMask | LockMask | তথ্য->keyboard.alt_mask | তথ্য->keyboard.level3_mask | তথ্য->keyboard.level5_mask;

        জন্য (Uint32 xkeycode = তথ্য->keyboard.xkb.desc_ptr->min_চাবি_code; xkeycode < তথ্য->keyboard.xkb.desc_ptr->max_চাবি_code; ++xkeycode) {
            ধ্রুবক SDL_Scancode scancode = তথ্য->keyboard.চাবি_layout[xkeycode];
            যদি (scancode == SDL_SCANCODE_UNKNOWN) {
                চালু;
            }

            জন্য (Uint32 group = 0; group < Xkb_অঙ্ক_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = তথ্য->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                ধ্রুবক unsigned অক্ষর max_চাবি_group = Xkb_চাবি_অঙ্ক_Groups(তথ্য->keyboard.xkb.desc_ptr, xkeycode);
                ধ্রুবক unsigned অক্ষর চাবি_group_info = Xkb_চাবি_Group_Info(তথ্য->keyboard.xkb.desc_ptr, xkeycode);

                যদি (max_চাবি_group && effective_group >= max_চাবি_group) {
                    ধ্রুবক unsigned অক্ষর action = XkbOutOfRangeGroupAction(চাবি_group_info);

                    নির্বাচন (action) {
                    পূর্বনির্ধারিত:
                        effective_group %= max_চাবি_group;
                        বিরতি;
                    ক্ষেত্র XkbClampIntoRange:
                        effective_group = max_চাবি_group - 1;
                        বিরতি;
                    ক্ষেত্র XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_সংখ্যা(চাবি_group_info);
                        যদি (effective_group >= max_চাবি_group) {
                            effective_group = 0;
                        }
                        বিরতি;
                    }
                }

                Xkb_চাবি_Type_Ptr চাবি_type = Xkb_চাবি_চাবি_Type(তথ্য->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                জন্য (Uint32 level = 0; level < চাবি_type->অঙ্ক_levels; ++level) {
                    ধ্রুবক চাবি_Sym keysym = X11_চাবি_Code_To_Sym(_this, xkeycode, effective_group, level);

                    যদি (keysym != No_প্রতীক) {
                        bool চাবি_added = false;

                        জন্য (পূর্ণসংখ্যা map_idx = 0; map_idx < চাবি_type->map_গুনতি; ++map_idx) {
                            যদি (চাবি_type->map[map_idx].active && চাবি_type->map[map_idx].level == level) {
                                ধ্রুবক unsigned পূর্ণসংখ্যা xkb_mod_mask = চাবি_type->map[map_idx].mods.mask;
                                যদি ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    ধ্রুবক SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & তথ্য->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & তথ্য->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & তথ্য->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    চাবি_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        যদি (!level && !চাবি_added) {
                            X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_SetKeymap(তথ্য->keyboard.xkb.keymaps[তথ্য->keyboard.xkb.current_group], send_event);
    } অন্যথা
#endif
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        যদি (!keymap) {
            ফেরত;
        }

        যদি (send_event) {
            যদি (তথ্য->keyboard.core.keysym_map) {
                X11_XFree(তথ্য->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(তথ্য->display, &তথ্য->keyboard.core.min_keycode, &তথ্য->keyboard.core.max_keycode);
            তথ্য->keyboard.core.keysym_map = X11_XGetKeyboardMapping(তথ্য->display, তথ্য->keyboard.core.min_keycode,
                                                                     তথ্য->keyboard.core.max_keycode - তথ্য->keyboard.core.min_keycode,
                                                                     &তথ্য->keyboard.core.keysyms_per_চাবি);
        }

        জন্য (Uint32 xkeycode = তথ্য->keyboard.core.min_keycode; xkeycode <= তথ্য->keyboard.core.max_keycode; ++xkeycode) {
            ধ্রুবক SDL_Scancode scancode = তথ্য->keyboard.চাবি_layout[xkeycode];
            যদি (scancode == SDL_SCANCODE_UNKNOWN) {
                চালু;
            }

            ধ্রুবক চাবি_Sym keysym = X11_চাবি_Code_To_Sym(_this, xkeycode, 0, 0);
            যদি (keysym != No_প্রতীক) {
                X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
            }
        }

        তথ্য->keyboard.alt_mask = Mod1Mask; // Alt or Meta
        তথ্য->keyboard.gui_mask = Mod4Mask; // Super
        তথ্য->keyboard.level3_mask = Mod5Mask; // Note: Not a typo, Mod5 = level 3 shift, and Mod3 = level 5 shift.
        তথ্য->keyboard.level5_mask = Mod3Mask;
        তথ্য->keyboard.numlock_mask = X11_GetXModifierMask(_this, SDL_SCANCODE_NUMLOCKCLEAR);
        তথ্য->keyboard.scrolllock_mask = X11_GetXModifierMask(_this, SDL_SCANCODE_SCROLLLOCK);

        SDL_SetKeymap(keymap, send_event);
    }
}

শূন্য X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;

#ifdef X_HAVE_UTF8_STRING
    যদি (তথ্য->im) {
        X11_XCloseIM(তথ্য->im);
        তথ্য->im = ফাঁকা;
    } অন্যথা {
        X11_XUnregisterIMInstantiateCallback(তথ্য->display, ফাঁকা, ফাঁকা, ফাঁকা, im_instantiate_handler, (XPointer)তথ্য);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    যদি (তথ্য->keyboard.xkb_enabled) {
        জন্য (পূর্ণসংখ্যা i = 0; i < Xkb_অঙ্ক_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(তথ্য->keyboard.xkb.keymaps[i]);
            তথ্য->keyboard.xkb.keymaps[i] = ফাঁকা;
        }

        যদি (তথ্য->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(তথ্য->keyboard.xkb.desc_ptr, 0, True);
            তথ্য->keyboard.xkb.desc_ptr = ফাঁকা;
        }
    } অন্যথা
#endif
        যদি (তথ্য->keyboard.core.keysym_map) {
        X11_XFree(তথ্য->keyboard.core.keysym_map);
        তথ্য->keyboard.core.keysym_map = ফাঁকা;
    }
}

শূন্য X11_ClearComposition(SDL_Window_তথ্য *তথ্য)
{
    যদি (তথ্য->preedit_দৈর্ঘ্য > 0) {
        তথ্য->preedit_text[0] = '\0';
        তথ্য->preedit_দৈর্ঘ্য = 0;
    }

    যদি (তথ্য->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        তথ্য->ime_needs_clear_composition = false;
    }
}

স্থির শূন্য X11_SendEditingEvent(SDL_Window_তথ্য *তথ্য)
{
    যদি (তথ্য->preedit_দৈর্ঘ্য == 0) {
        X11_ClearComposition(তথ্য);
        ফেরত;
    }

    bool in_highlight = false;
    পূর্ণসংখ্যা start = -1, দৈর্ঘ্য = 0, i;
    জন্য (i = 0; i < তথ্য->preedit_দৈর্ঘ্য; ++i) {
        যদি (তথ্য->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            যদি (start < 0) {
                start = i;
                in_highlight = true;
            }
        } অন্যথা যদি (in_highlight) {
            // Found the end of the highlight
            বিরতি;
        }
    }
    যদি (in_highlight) {
        দৈর্ঘ্য = (i - start);
    } অন্যথা {
        start = SDL_clamp(তথ্য->preedit_cursor, 0, তথ্য->preedit_দৈর্ঘ্য);
    }
    SDL_SendEditingText(তথ্য->preedit_text, start, দৈর্ঘ্য);

    তথ্য->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
স্থির পূর্ণসংখ্যা preedit_start_callback(XIC xic, XPointer client_তথ্য_2, XPointer call_তথ্য_2)
{
    // No limit on preedit text length
    ফেরত -1;
}

স্থির শূন্য preedit_done_callback(XIC xic, XPointer client_তথ্য_2, XPointer call_তথ্য_2)
{
}

স্থির শূন্য preedit_draw_callback(XIC xic, XPointer client_তথ্য_2, XIMPreeditDrawCallbackStruct *call_তথ্য_2)
{
    SDL_Window_তথ্য *তথ্য = (SDL_Window_তথ্য *)client_তথ্য_2;
    পূর্ণসংখ্যা chg_first = SDL_clamp(call_তথ্য_2->chg_first, 0, তথ্য->preedit_দৈর্ঘ্য);
    পূর্ণসংখ্যা chg_দৈর্ঘ্য = SDL_clamp(call_তথ্য_2->chg_দৈর্ঘ্য, 0, তথ্য->preedit_দৈর্ঘ্য - chg_first);

    ধ্রুবক অক্ষর *start = তথ্য->preedit_text;
    যদি (chg_দৈর্ঘ্য > 0) {
        // Delete text in range
        জন্য (পূর্ণসংখ্যা i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, ফাঁকা);
        }

        ধ্রুবক অক্ষর *end = start;
        জন্য (পূর্ণসংখ্যা i = 0; end && *end && i < chg_দৈর্ঘ্য; ++i) {
            SDL_StepUTF8(&end, ফাঁকা);
        }

        যদি (end > start) {
            SDL_memmove((অক্ষর *)start, end, SDL_strlen(end) + 1);
            যদি ((chg_first + chg_দৈর্ঘ্য) > তথ্য->preedit_দৈর্ঘ্য) {
                SDL_memmove(&তথ্য->preedit_feedback[chg_first], &তথ্য->preedit_feedback[chg_first + chg_দৈর্ঘ্য], (তথ্য->preedit_দৈর্ঘ্য - chg_first - chg_দৈর্ঘ্য) * আকার(*তথ্য->preedit_feedback));
            }
        }
        তথ্য->preedit_দৈর্ঘ্য -= chg_দৈর্ঘ্য;
    }

    XIMText *text = call_তথ্য_2->text;
    যদি (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        যদি (text->string.multi_byte) {
            text->দৈর্ঘ্য = SDL_utf8strlen(text->string.multi_byte);
        }

        size_t string_আকার = SDL_strlen(text->string.multi_byte);
        size_t আকার_2 = string_আকার + 1;
        যদি (তথ্য->preedit_text) {
            আকার_2 += SDL_strlen(তথ্য->preedit_text);
        }
        অক্ষর *preedit_text = (অক্ষর *)SDL_malloc(আকার_2 * আকার(*preedit_text));
        যদি (preedit_text) {
            size_t pre_আকার = (start - তথ্য->preedit_text);
            size_t post_আকার = start ? SDL_strlen(start) : 0;
            যদি (pre_আকার > 0) {
                SDL_memcpy(&preedit_text[0], তথ্য->preedit_text, pre_আকার);
            }
            SDL_memcpy(&preedit_text[pre_আকার], text->string.multi_byte, string_আকার);
            যদি (post_আকার > 0) {
                SDL_memcpy(&preedit_text[pre_আকার + string_আকার], start, post_আকার);
            }
            preedit_text[আকার_2 - 1] = '\0';
        }

        size_t feedback_আকার = তথ্য->preedit_দৈর্ঘ্য + text->দৈর্ঘ্য;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_আকার * আকার(*feedback));
        যদি (feedback) {
            size_t pre_আকার = (size_t)chg_first;
            size_t post_আকার = (size_t)তথ্য->preedit_দৈর্ঘ্য - pre_আকার;
            যদি (pre_আকার > 0) {
                SDL_memcpy(&feedback[0], তথ্য->preedit_feedback, pre_আকার * আকার(*feedback));
            }
            SDL_memcpy(&feedback[pre_আকার], text->feedback, text->দৈর্ঘ্য * আকার(*feedback));
            যদি (post_আকার > 0) {
                SDL_memcpy(&feedback[pre_আকার + text->দৈর্ঘ্য], &তথ্য->preedit_feedback[pre_আকার], post_আকার * আকার(*feedback));
            }
        }

        যদি (preedit_text && feedback) {
            SDL_free(তথ্য->preedit_text);
            তথ্য->preedit_text = preedit_text;

            SDL_free(তথ্য->preedit_feedback);
            তথ্য->preedit_feedback = feedback;

            তথ্য->preedit_দৈর্ঘ্য += text->দৈর্ঘ্য;
        } অন্যথা {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    তথ্য->preedit_cursor = call_তথ্য_2->caret;

#ifdef DEBUG_XIM
    যদি (call_তথ্য_2->chg_দৈর্ঘ্য > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_তথ্য_2->chg_দৈর্ঘ্য, call_তথ্য_2->chg_first);
    }
    যদি (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_তথ্য_2->chg_first, call_তথ্য_2->caret);
    }
    SDL_Log("Pre-edit text: %s", তথ্য->preedit_text);
#endif

    X11_SendEditingEvent(তথ্য);
}

স্থির শূন্য preedit_caret_callback(XIC xic, XPointer client_তথ্য_2, XIMPreeditCaretCallbackStruct *call_তথ্য_2)
{
    SDL_Window_তথ্য *তথ্য = (SDL_Window_তথ্য *)client_তথ্য_2;

    নির্বাচন (call_তথ্য_2->direction) {
    ক্ষেত্র XIMAbsolutePosition:
        যদি (call_তথ্য_2->position != তথ্য->preedit_cursor) {
            তথ্য->preedit_cursor = call_তথ্য_2->position;
            X11_SendEditingEvent(তথ্য);
        }
        বিরতি;
    ক্ষেত্র XIMDontChange:
        বিরতি;
    পূর্বনির্ধারিত:
        // Not currently supported
        বিরতি;
    }
}

স্থির শূন্য ic_destroyed_handler(XIC ic, XPointer client_তথ্য, XPointer call_তথ্য)
{
    SDL_Window_তথ্য *তথ্য = (SDL_Window_তথ্য *)client_তথ্য;
    তথ্য->ic = ফাঁকা;
    X11_Destroy_প্রবেশ_Context(তথ্য);

    // If the IM was already recreated, create a new IC.
    যদি (তথ্য->videodata->im) {
        X11_Create_প্রবেশ_Context(তথ্য);
    }
}
#endif // X_HAVE_UTF8_STRING

শূন্য X11_Create_প্রবেশ_Context(SDL_Window_তথ্য *তথ্য)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_Video_তথ্য *videodata = তথ্য->videodata;

    যদি (SDL_X11_HAVE_UTF8 && videodata->im) {
        ধ্রুবক অক্ষর *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_তথ্য_2 = (XPointer)তথ্য;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        যদি (hint && SDL_strstr(hint, "composition")) {
            XIMCallback draw_callback;
            draw_callback.client_তথ্য_2 = (XPointer)তথ্য;
            draw_callback.callback = (XIMProc)preedit_draw_callback;

            XIMCallback start_callback;
            start_callback.client_তথ্য_2 = (XPointer)তথ্য;
            start_callback.callback = (XIMProc)preedit_start_callback;

            XIMCallback done_callback;
            done_callback.client_তথ্য_2 = (XPointer)তথ্য;
            done_callback.callback = (XIMProc)preedit_done_callback;

            XIMCallback caret_callback;
            caret_callback.client_তথ্য_2 = (XPointer)তথ্য;
            caret_callback.callback = (XIMProc)preedit_caret_callback;

            XVaNestedList attr = X11_XVaCreateNestedList(0,
                                                         XNPreeditStartCallback, &start_callback,
                                                         XNPreeditDoneCallback, &done_callback,
                                                         XNPreeditDrawCallback, &draw_callback,
                                                         XNPreeditCaretCallback, &caret_callback,
                                                         ফাঁকা);
            যদি (attr) {
                তথ্য->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, তথ্য->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         ফাঁকা);
                X11_XFree(attr);
            }
        }
        যদি (!তথ্য->ic) {
            তথ্য->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClientWindow, তথ্য->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     ফাঁকা);
        }
        তথ্য->xim_spot.x = -1;
        তথ্য->xim_spot.y = -1;
    }
#endif // X_HAVE_UTF8_STRING
}


শূন্য X11_Destroy_প্রবেশ_Context(SDL_Window_তথ্য *তথ্য)
{
#ifdef X_HAVE_UTF8_STRING
    যদি (তথ্য->ic) {
        X11_XDestroyIC(তথ্য->ic);
        তথ্য->ic = ফাঁকা;
    }
    SDL_free(তথ্য->preedit_text);
    SDL_free(তথ্য->preedit_feedback);
    তথ্য->preedit_text = ফাঁকা;
    তথ্য->preedit_feedback = ফাঁকা;
#endif
}

স্থির শূন্য X11_ResetXIM(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_Window_তথ্য *তথ্য = window->internal;

    যদি (তথ্য && তথ্য->ic) {
        // Clear any partially entered dead keys
        অক্ষর *contents = X11_Xutf8ResetIC(তথ্য->ic);
        যদি (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    ফেরত X11_Update_Text_প্রবেশ_Area(_this, window);
}

bool X11_Stop_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    ফেরত true;
}

bool X11_Update_Text_প্রবেশ_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_Window_তথ্য *তথ্য = window->internal;

    যদি (তথ্য && তথ্য->ic) {
        XPoint spot;
        spot.x = window->text_প্রবেশ_rect.x + window->text_প্রবেশ_cursor;
        spot.y = window->text_প্রবেশ_rect.y + window->text_প্রবেশ_rect.h;
        যদি (spot.x != তথ্য->xim_spot.x || spot.y != তথ্য->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, ফাঁকা);
            যদি (attr) {
                X11_XSetICValues(তথ্য->ic, XNPreeditAttributes, attr, ফাঁকা);
                X11_XFree(attr);
            }
            SDL_copyp(&তথ্য->xim_spot, &spot);
        }
    }
#endif
    ফেরত true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    ফেরত videodata->use_steam_screen_keyboard;
}

শূন্য X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_Video_তথ্য *videodata = _this->internal;

    যদি (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ধ্রুবক পূর্ণসংখ্যা k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Single_সারি = 0;    // Enter dismisses the keyboard
        ধ্রুবক পূর্ণসংখ্যা k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Multiple_সারিগুলি = 1; // User needs to explicitly dismiss the keyboard
        ধ্রুবক পূর্ণসংখ্যা k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ধ্রুবক পূর্ণসংখ্যা k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        অক্ষর deeplink[128];
        পূর্ণসংখ্যা mode;

        নির্বাচন (SDL_Get_Text_প্রবেশ_Type(props)) {
        ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Email;
            বিরতি;
        ক্ষেত্র SDL_TEXTINPUT_TYPE_সংখ্যা:
        ক্ষেত্র SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_HIDDEN:
        ক্ষেত্র SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Numeric;
            বিরতি;
        পূর্বনির্ধারিত:
            যদি (SDL_Get_Text_প্রবেশ_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Multiple_সারিগুলি;
            } অন্যথা {
                mode = k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Single_সারি;
            }
            বিরতি;
        }
        (শূন্য)SDL_snprintf(deeplink, আকার(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_প্রবেশ_rect.x, window->text_প্রবেশ_rect.y,
                           window->text_প্রবেশ_rect.w, window->text_প্রবেশ_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

শূন্য X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_তথ্য *videodata = _this->internal;

    যদি (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
