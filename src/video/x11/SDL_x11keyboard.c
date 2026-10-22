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
    বিকল্প (scancode) {
    পক্ষ SDL_SCANCODE_ESCAPE:
    পক্ষ SDL_SCANCODE_CAPSLOCK:
    পক্ষ SDL_SCANCODE_NUMLOCKCLEAR:
    পক্ষ SDL_SCANCODE_LSHIFT:
    পক্ষ SDL_SCANCODE_RSHIFT:
    পক্ষ SDL_SCANCODE_LCTRL:
    পক্ষ SDL_SCANCODE_RCTRL:
    পক্ষ SDL_SCANCODE_LALT:
    পক্ষ SDL_SCANCODE_RALT:
    পক্ষ SDL_SCANCODE_LGUI:
    পক্ষ SDL_SCANCODE_RGUI:
        প্রত্যাগম false;
    স্বভাব:
        প্রত্যাগম true;
    }
}

স্থির চাবি_Sym X11_চাবি_Code_To_Sym(SDL_VideoDevice *_this, চাবি_Code_2 keycode, unsigned পূর্ণাঙ্ক group, unsigned পূর্ণাঙ্ক level)
{
    SDL_VideoData *data = _this->internal;
    চাবি_Sym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    যদি (data->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(data->display, keycode, group, level);
    } অন্যথা
#endif
    {
        // TODO: Handle groups on the legacy path.
        যদি (keycode >= data->keyboard.core.min_keycode && keycode <= data->keyboard.core.max_keycode) {
            keysym = data->keyboard.core.keysym_map[(keycode - data->keyboard.core.min_keycode) * data->keyboard.core.keysyms_per_চাবি];
        } অন্যথা {
            keysym = No_প্রতীক;
        }
    }

    প্রত্যাগম keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
স্থির SDL_Scancode X11_চাবি_Code_To_SDLScancode(SDL_VideoDevice *_this, চাবি_Code_2 keycode)
{
    ধ্রুব চাবি_Sym keysym = X11_চাবি_Code_To_Sym(_this, keycode, 0, 0);

    যদি (keysym == No_প্রতীক) {
        প্রত্যাগম SDL_SCANCODE_UNKNOWN;
    }

    প্রত্যাগম SDL_Get_Scancode_From_চাবি_Sym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
স্থির bool X11_InitIM(SDL_VideoData *videodata);

স্থির শূন্য im_instantiate_handler(Display *display, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    যদি (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, রিক্ত, রিক্ত, রিক্ত, im_instantiate_handler, clientData);
    }
}

স্থির শূন্য im_destroyed_handler(XIM im, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    videodata->im = রিক্ত;
    X11_XRegisterIMInstantiateCallback(videodata->display, রিক্ত, রিক্ত, রিক্ত, im_instantiate_handler, clientData);
}

স্থির bool X11_InitIM(SDL_VideoData *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    বর্ণ *prev_locale = setlocale(LC_ALL, রিক্ত);
    বর্ণ *prev_xmods = X11_XSetLocaleModifiers(রিক্ত);

    যদি (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    যদি (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (শূন্য)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, রিক্ত, রিক্ত, রিক্ত);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (শূন্য)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    যদি (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (বর্ণ *)রিক্ত);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        প্রতি (পূর্ণাঙ্ক i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *w = videodata->windowlist[i];
            যদি (!w->ic) {
                X11_Create_প্রবেশ_Context(w);
            }
        }

        প্রত্যাগম true;
    }

    প্রত্যাগম false;
}
#endif // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    পূর্ণাঙ্ক i = 0;
    পূর্ণাঙ্ক j = 0;
    পূর্ণাঙ্ক min_keycode, max_keycode;
    সংরচনা
    {
        SDL_Scancode scancode;
        চাবি_Sym keysym;
        পূর্ণাঙ্ক মান;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_বাম, XK_বাম, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    পূর্ণাঙ্ক best_distance;
    পূর্ণাঙ্ক best_index;
    পূর্ণাঙ্ক distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    পূর্ণাঙ্ক xkb_major = XkbMajorVersion;
    পূর্ণাঙ্ক xkb_minor = XkbMinorVersion;

    যদি (X11_XkbQueryExtension(data->display, রিক্ত, &data->keyboard.xkb.event, রিক্ত, &xkb_major, &xkb_minor)) {
        Bool xkb_repeat = 0;
        data->keyboard.xkb_enabled = true;
        data->keyboard.xkb.desc_ptr = X11_XkbGetMap(data->display, XkbAllClientInfoMask, XkbUseCoreKbd);

        // This will remove KeyRelease events for held keys.
        X11_XkbSetDetectableAutoRepeat(data->display, True, &xkb_repeat);

        // Enable the key mapping and state events.
        X11_XkbSelectEvents(data->display, XkbUseCoreKbd,
                            XkbNewKeyboardNotifyMask | XkbMapNotifyMask | XkbStateNotifyMask,
                            XkbNewKeyboardNotifyMask | XkbMapNotifyMask | XkbStateNotifyMask);
        X11_XkbSelectEventDetails(data->display, XkbUseCoreKbd, XkbStateNotify, XkbGroupStateMask | XkbModifierStateMask, XkbGroupStateMask | XkbModifierStateMask);
    } অন্যথা
#endif
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
        data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                              data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                              &data->keyboard.core.keysyms_per_চাবি);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    যদি (SDL_X11_HAVE_UTF8) {
        যদি (!X11_InitIM(data)) {
            X11_XRegisterIMInstantiateCallback(data->display, রিক্ত, রিক্ত, রিক্ত, im_instantiate_handler, (XPointer)data);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_index = -1;
    X11_XDisplayKeycodes(data->display, &min_keycode, &max_keycode);
    প্রতি (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].মান = X11_XKeysymToKeycode(data->display, fingerprint[i].keysym) - min_keycode;
    }
    প্রতি (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        পূর্ণাঙ্ক table_size;
        ধ্রুব SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_size);

        distance = 0;
        প্রতি (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            যদি (fingerprint[j].মান < 0 || fingerprint[j].মান >= table_size) {
                distance += 1;
            } অন্যথা যদি (table[fingerprint[j].মান] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        যদি (distance < best_distance) {
            best_distance = distance;
            best_index = i;
        }
    }
    যদি (best_index < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        পূর্ণাঙ্ক fingerprint_মান = X11_XKeysymToKeycode(data->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        যদি (fingerprint_মান == 235) {
            প্রতি (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                যদি (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_index = i;
                    best_distance = 0;
                    ভঙ্গ;
                }
            }
        }
    }
    যদি (best_index >= 0 && best_distance <= 2) {
        পূর্ণাঙ্ক table_size;
        ধ্রুব SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_index], &table_size);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_index, min_keycode, max_keycode, table_size);
#endif
        // This should never happen, but just in case...
        যদি (table_size > (SDL_arraysize(data->keyboard.চাবি_layout) - min_keycode)) {
            table_size = (SDL_arraysize(data->keyboard.চাবি_layout) - min_keycode);
        }
        SDL_memcpy(&data->keyboard.চাবি_layout[min_keycode], table, পরিমাণ(SDL_Scancode) * table_size);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        প্রতি (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_চাবি_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                চাবি_Sym sym;
                sym = X11_চাবি_Code_To_Sym(_this, (চাবি_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned পূর্ণাঙ্ক)sym, sym == No_প্রতীক ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            যদি (scancode == data->keyboard.চাবি_layout[i]) {
                অনুবর্ত;
            }
            যদি ((SDL_GetKeymapKeycode(রিক্ত, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", data->চাবি_layout[i], SDL_GetScancodeName(data->চাবি_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                data->keyboard.চাবি_layout[i] = scancode;
            }
        }
    } অন্যথা {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        প্রতি (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_চাবি_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                চাবি_Sym sym;
                sym = X11_চাবি_Code_To_Sym(_this, (চাবি_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned পূর্ণাঙ্ক)sym, sym == No_প্রতীক ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            যদি (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } অন্যথা {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            data->keyboard.চাবি_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    প্রত্যাগম true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
স্থির unsigned পূর্ণাঙ্ক X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, ধ্রুব বর্ণ *vmod_name)
{
    SDL_VideoData *videodata = _this->internal;
    unsigned পূর্ণাঙ্ক mod_mask = 0;

    ধ্রুব Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    যদি (vmod != None) {
        প্রতি (পূর্ণাঙ্ক i = 0; i < Xkb_অঙ্ক_Virtual_Mods; ++i) {
            যদি (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                ভঙ্গ;
            }
        }
    }

    প্রত্যাগম mod_mask;
}
#endif

স্থির unsigned X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    unsigned পূর্ণাঙ্ক mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    unsigned পূর্ণাঙ্ক n = xmods->max_keypermod;
    প্রতি (পূর্ণাঙ্ক i = 3; i < 8; i++) {
        প্রতি (পূর্ণাঙ্ক j = 0; j < n; j++) {
            ধ্রুব চাবি_Code_2 kc = xmods->modifiermap[i * n + j];
            যদি (videodata->keyboard.চাবি_layout[kc] == scancode) {
                mod_mask = 1 << i;
                ভঙ্গ;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    প্রত্যাগম mod_mask;
}

স্থির শূন্য X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, চাবি_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_চাবি_Code_From_চাবি_Sym(xkeysym, xkeycode, sdl_mod_mask);

    যদি (!keycode) {
        বিকল্প (sdl_scancode) {
        পক্ষ SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            ভঙ্গ;
        পক্ষ SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            ভঙ্গ;
        পক্ষ SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            ভঙ্গ;
        পক্ষ SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            ভঙ্গ;
        স্বভাব:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            ভঙ্গ;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

শূন্য X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    যদি (data->keyboard.xkb_enabled) {
        XkbStateRec state;

        প্রতি (unsigned পূর্ণাঙ্ক i = 0; i < Xkb_অঙ্ক_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = রিক্ত;
        }

        X11_XkbGetNames(data->display, XkbVirtualModNamesMask, data->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(data->display, XkbAllClientInfoMask | XkbVirtualModsMask, data->keyboard.xkb.desc_ptr);

        যদি (X11_XkbGetState(data->display, XkbUseCoreKbd, &state) == Success) {
            data->keyboard.xkb.current_group = state.group;
        }

        data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        যদি (!data->keyboard.alt_mask) {
            data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        data->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        data->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        data->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        data->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        data->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        প্রতি (unsigned পূর্ণাঙ্ক i = 0; i < Xkb_অঙ্ক_Kbd_Groups; ++i) {
            data->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            যদি (!data->keyboard.xkb.keymaps[i]) {
                প্রতি (unsigned পূর্ণাঙ্ক j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
                    data->keyboard.xkb.keymaps[j] = রিক্ত;
                }

                প্রত্যাগম;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ধ্রুব Uint32 valid_mod_mask = ShiftMask | LockMask | data->keyboard.alt_mask | data->keyboard.level3_mask | data->keyboard.level5_mask;

        প্রতি (Uint32 xkeycode = data->keyboard.xkb.desc_ptr->min_চাবি_code; xkeycode < data->keyboard.xkb.desc_ptr->max_চাবি_code; ++xkeycode) {
            ধ্রুব SDL_Scancode scancode = data->keyboard.চাবি_layout[xkeycode];
            যদি (scancode == SDL_SCANCODE_UNKNOWN) {
                অনুবর্ত;
            }

            প্রতি (Uint32 group = 0; group < Xkb_অঙ্ক_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = data->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                ধ্রুব unsigned বর্ণ max_চাবি_group = Xkb_চাবি_অঙ্ক_Groups(data->keyboard.xkb.desc_ptr, xkeycode);
                ধ্রুব unsigned বর্ণ চাবি_group_info = Xkb_চাবি_Group_Info(data->keyboard.xkb.desc_ptr, xkeycode);

                যদি (max_চাবি_group && effective_group >= max_চাবি_group) {
                    ধ্রুব unsigned বর্ণ action = XkbOutOfRangeGroupAction(চাবি_group_info);

                    বিকল্প (action) {
                    স্বভাব:
                        effective_group %= max_চাবি_group;
                        ভঙ্গ;
                    পক্ষ XkbClampIntoRange:
                        effective_group = max_চাবি_group - 1;
                        ভঙ্গ;
                    পক্ষ XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_সংখ্যা(চাবি_group_info);
                        যদি (effective_group >= max_চাবি_group) {
                            effective_group = 0;
                        }
                        ভঙ্গ;
                    }
                }

                Xkb_চাবি_Type_Ptr চাবি_type = Xkb_চাবি_চাবি_Type(data->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                প্রতি (Uint32 level = 0; level < চাবি_type->অঙ্ক_levels; ++level) {
                    ধ্রুব চাবি_Sym keysym = X11_চাবি_Code_To_Sym(_this, xkeycode, effective_group, level);

                    যদি (keysym != No_প্রতীক) {
                        bool চাবি_added = false;

                        প্রতি (পূর্ণাঙ্ক map_idx = 0; map_idx < চাবি_type->map_গুনতি; ++map_idx) {
                            যদি (চাবি_type->map[map_idx].active && চাবি_type->map[map_idx].level == level) {
                                ধ্রুব unsigned পূর্ণাঙ্ক xkb_mod_mask = চাবি_type->map[map_idx].mods.mask;
                                যদি ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    ধ্রুব SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & data->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

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

        SDL_SetKeymap(data->keyboard.xkb.keymaps[data->keyboard.xkb.current_group], send_event);
    } অন্যথা
#endif
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        যদি (!keymap) {
            প্রত্যাগম;
        }

        যদি (send_event) {
            যদি (data->keyboard.core.keysym_map) {
                X11_XFree(data->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
            data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                                     data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                                     &data->keyboard.core.keysyms_per_চাবি);
        }

        প্রতি (Uint32 xkeycode = data->keyboard.core.min_keycode; xkeycode <= data->keyboard.core.max_keycode; ++xkeycode) {
            ধ্রুব SDL_Scancode scancode = data->keyboard.চাবি_layout[xkeycode];
            যদি (scancode == SDL_SCANCODE_UNKNOWN) {
                অনুবর্ত;
            }

            ধ্রুব চাবি_Sym keysym = X11_চাবি_Code_To_Sym(_this, xkeycode, 0, 0);
            যদি (keysym != No_প্রতীক) {
                X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
            }
        }

        data->keyboard.alt_mask = Mod1Mask; // Alt or Meta
        data->keyboard.gui_mask = Mod4Mask; // Super
        data->keyboard.level3_mask = Mod5Mask; // Note: Not a typo, Mod5 = level 3 shift, and Mod3 = level 5 shift.
        data->keyboard.level5_mask = Mod3Mask;
        data->keyboard.numlock_mask = X11_GetXModifierMask(_this, SDL_SCANCODE_NUMLOCKCLEAR);
        data->keyboard.scrolllock_mask = X11_GetXModifierMask(_this, SDL_SCANCODE_SCROLLLOCK);

        SDL_SetKeymap(keymap, send_event);
    }
}

শূন্য X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

#ifdef X_HAVE_UTF8_STRING
    যদি (data->im) {
        X11_XCloseIM(data->im);
        data->im = রিক্ত;
    } অন্যথা {
        X11_XUnregisterIMInstantiateCallback(data->display, রিক্ত, রিক্ত, রিক্ত, im_instantiate_handler, (XPointer)data);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    যদি (data->keyboard.xkb_enabled) {
        প্রতি (পূর্ণাঙ্ক i = 0; i < Xkb_অঙ্ক_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = রিক্ত;
        }

        যদি (data->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(data->keyboard.xkb.desc_ptr, 0, True);
            data->keyboard.xkb.desc_ptr = রিক্ত;
        }
    } অন্যথা
#endif
        যদি (data->keyboard.core.keysym_map) {
        X11_XFree(data->keyboard.core.keysym_map);
        data->keyboard.core.keysym_map = রিক্ত;
    }
}

শূন্য X11_ClearComposition(SDL_WindowData *data)
{
    যদি (data->preedit_length > 0) {
        data->preedit_text[0] = '\0';
        data->preedit_length = 0;
    }

    যদি (data->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        data->ime_needs_clear_composition = false;
    }
}

স্থির শূন্য X11_SendEditingEvent(SDL_WindowData *data)
{
    যদি (data->preedit_length == 0) {
        X11_ClearComposition(data);
        প্রত্যাগম;
    }

    bool in_highlight = false;
    পূর্ণাঙ্ক start = -1, length = 0, i;
    প্রতি (i = 0; i < data->preedit_length; ++i) {
        যদি (data->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            যদি (start < 0) {
                start = i;
                in_highlight = true;
            }
        } অন্যথা যদি (in_highlight) {
            // Found the end of the highlight
            ভঙ্গ;
        }
    }
    যদি (in_highlight) {
        length = (i - start);
    } অন্যথা {
        start = SDL_clamp(data->preedit_cursor, 0, data->preedit_length);
    }
    SDL_SendEditingText(data->preedit_text, start, length);

    data->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
স্থির পূর্ণাঙ্ক preedit_start_callback(XIC xic, XPointer client_data, XPointer call_data)
{
    // No limit on preedit text length
    প্রত্যাগম -1;
}

স্থির শূন্য preedit_done_callback(XIC xic, XPointer client_data, XPointer call_data)
{
}

স্থির শূন্য preedit_draw_callback(XIC xic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;
    পূর্ণাঙ্ক chg_first = SDL_clamp(call_data->chg_first, 0, data->preedit_length);
    পূর্ণাঙ্ক chg_length = SDL_clamp(call_data->chg_length, 0, data->preedit_length - chg_first);

    ধ্রুব বর্ণ *start = data->preedit_text;
    যদি (chg_length > 0) {
        // Delete text in range
        প্রতি (পূর্ণাঙ্ক i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, রিক্ত);
        }

        ধ্রুব বর্ণ *end = start;
        প্রতি (পূর্ণাঙ্ক i = 0; end && *end && i < chg_length; ++i) {
            SDL_StepUTF8(&end, রিক্ত);
        }

        যদি (end > start) {
            SDL_memmove((বর্ণ *)start, end, SDL_strlen(end) + 1);
            যদি ((chg_first + chg_length) > data->preedit_length) {
                SDL_memmove(&data->preedit_feedback[chg_first], &data->preedit_feedback[chg_first + chg_length], (data->preedit_length - chg_first - chg_length) * পরিমাণ(*data->preedit_feedback));
            }
        }
        data->preedit_length -= chg_length;
    }

    XIMText *text = call_data->text;
    যদি (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        যদি (text->string.multi_byte) {
            text->length = SDL_utf8strlen(text->string.multi_byte);
        }

        size_t string_size = SDL_strlen(text->string.multi_byte);
        size_t size = string_size + 1;
        যদি (data->preedit_text) {
            size += SDL_strlen(data->preedit_text);
        }
        বর্ণ *preedit_text = (বর্ণ *)SDL_malloc(size * পরিমাণ(*preedit_text));
        যদি (preedit_text) {
            size_t pre_size = (start - data->preedit_text);
            size_t post_size = start ? SDL_strlen(start) : 0;
            যদি (pre_size > 0) {
                SDL_memcpy(&preedit_text[0], data->preedit_text, pre_size);
            }
            SDL_memcpy(&preedit_text[pre_size], text->string.multi_byte, string_size);
            যদি (post_size > 0) {
                SDL_memcpy(&preedit_text[pre_size + string_size], start, post_size);
            }
            preedit_text[size - 1] = '\0';
        }

        size_t feedback_size = data->preedit_length + text->length;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_size * পরিমাণ(*feedback));
        যদি (feedback) {
            size_t pre_size = (size_t)chg_first;
            size_t post_size = (size_t)data->preedit_length - pre_size;
            যদি (pre_size > 0) {
                SDL_memcpy(&feedback[0], data->preedit_feedback, pre_size * পরিমাণ(*feedback));
            }
            SDL_memcpy(&feedback[pre_size], text->feedback, text->length * পরিমাণ(*feedback));
            যদি (post_size > 0) {
                SDL_memcpy(&feedback[pre_size + text->length], &data->preedit_feedback[pre_size], post_size * পরিমাণ(*feedback));
            }
        }

        যদি (preedit_text && feedback) {
            SDL_free(data->preedit_text);
            data->preedit_text = preedit_text;

            SDL_free(data->preedit_feedback);
            data->preedit_feedback = feedback;

            data->preedit_length += text->length;
        } অন্যথা {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    data->preedit_cursor = call_data->caret;

#ifdef DEBUG_XIM
    যদি (call_data->chg_length > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_data->chg_length, call_data->chg_first);
    }
    যদি (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_data->chg_first, call_data->caret);
    }
    SDL_Log("Pre-edit text: %s", data->preedit_text);
#endif

    X11_SendEditingEvent(data);
}

স্থির শূন্য preedit_caret_callback(XIC xic, XPointer client_data, XIMPreeditCaretCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;

    বিকল্প (call_data->direction) {
    পক্ষ XIMAbsolutePosition:
        যদি (call_data->position != data->preedit_cursor) {
            data->preedit_cursor = call_data->position;
            X11_SendEditingEvent(data);
        }
        ভঙ্গ;
    পক্ষ XIMDontChange:
        ভঙ্গ;
    স্বভাব:
        // Not currently supported
        ভঙ্গ;
    }
}

স্থির শূন্য ic_destroyed_handler(XIC ic, XPointer clientData, XPointer callData)
{
    SDL_WindowData *data = (SDL_WindowData *)clientData;
    data->ic = রিক্ত;
    X11_Destroy_প্রবেশ_Context(data);

    // If the IM was already recreated, create a new IC.
    যদি (data->videodata->im) {
        X11_Create_প্রবেশ_Context(data);
    }
}
#endif // X_HAVE_UTF8_STRING

শূন্য X11_Create_প্রবেশ_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_VideoData *videodata = data->videodata;

    যদি (SDL_X11_HAVE_UTF8 && videodata->im) {
        ধ্রুব বর্ণ *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)data;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        যদি (hint && SDL_strstr(hint, "composition")) {
            XIMCallback draw_callback;
            draw_callback.client_data = (XPointer)data;
            draw_callback.callback = (XIMProc)preedit_draw_callback;

            XIMCallback start_callback;
            start_callback.client_data = (XPointer)data;
            start_callback.callback = (XIMProc)preedit_start_callback;

            XIMCallback done_callback;
            done_callback.client_data = (XPointer)data;
            done_callback.callback = (XIMProc)preedit_done_callback;

            XIMCallback caret_callback;
            caret_callback.client_data = (XPointer)data;
            caret_callback.callback = (XIMProc)preedit_caret_callback;

            XVaNestedList attr = X11_XVaCreateNestedList(0,
                                                         XNPreeditStartCallback, &start_callback,
                                                         XNPreeditDoneCallback, &done_callback,
                                                         XNPreeditDrawCallback, &draw_callback,
                                                         XNPreeditCaretCallback, &caret_callback,
                                                         রিক্ত);
            যদি (attr) {
                data->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, data->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         রিক্ত);
                X11_XFree(attr);
            }
        }
        যদি (!data->ic) {
            data->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClientWindow, data->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     রিক্ত);
        }
        data->xim_spot.x = -1;
        data->xim_spot.y = -1;
    }
#endif // X_HAVE_UTF8_STRING
}


শূন্য X11_Destroy_প্রবেশ_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    যদি (data->ic) {
        X11_XDestroyIC(data->ic);
        data->ic = রিক্ত;
    }
    SDL_free(data->preedit_text);
    SDL_free(data->preedit_feedback);
    data->preedit_text = রিক্ত;
    data->preedit_feedback = রিক্ত;
#endif
}

স্থির শূন্য X11_ResetXIM(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    যদি (data && data->ic) {
        // Clear any partially entered dead keys
        বর্ণ *contents = X11_Xutf8ResetIC(data->ic);
        যদি (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    প্রত্যাগম X11_Update_Text_প্রবেশ_Area(_this, window);
}

bool X11_Stop_Text_প্রবেশ(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    প্রত্যাগম true;
}

bool X11_Update_Text_প্রবেশ_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    যদি (data && data->ic) {
        XPoint spot;
        spot.x = window->text_প্রবেশ_rect.x + window->text_প্রবেশ_cursor;
        spot.y = window->text_প্রবেশ_rect.y + window->text_প্রবেশ_rect.h;
        যদি (spot.x != data->xim_spot.x || spot.y != data->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, রিক্ত);
            যদি (attr) {
                X11_XSetICValues(data->ic, XNPreeditAttributes, attr, রিক্ত);
                X11_XFree(attr);
            }
            SDL_copyp(&data->xim_spot, &spot);
        }
    }
#endif
    প্রত্যাগম true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    প্রত্যাগম videodata->use_steam_screen_keyboard;
}

শূন্য X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;

    যদি (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ধ্রুব পূর্ণাঙ্ক k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Single_সারি = 0;    // Enter dismisses the keyboard
        ধ্রুব পূর্ণাঙ্ক k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Multiple_সারিগুলি = 1; // User needs to explicitly dismiss the keyboard
        ধ্রুব পূর্ণাঙ্ক k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ধ্রুব পূর্ণাঙ্ক k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        বর্ণ deeplink[128];
        পূর্ণাঙ্ক mode;

        বিকল্প (SDL_Get_Text_প্রবেশ_Type(props)) {
        পক্ষ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Email;
            ভঙ্গ;
        পক্ষ SDL_TEXTINPUT_TYPE_সংখ্যা:
        পক্ষ SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_HIDDEN:
        পক্ষ SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Numeric;
            ভঙ্গ;
        স্বভাব:
            যদি (SDL_Get_Text_প্রবেশ_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Multiple_সারিগুলি;
            } অন্যথা {
                mode = k_EFloating_Gamepad_Text_প্রবেশ_Mode_Mode_Single_সারি;
            }
            ভঙ্গ;
        }
        (শূন্য)SDL_snprintf(deeplink, পরিমাণ(deeplink),
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
    SDL_VideoData *videodata = _this->internal;

    যদি (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
