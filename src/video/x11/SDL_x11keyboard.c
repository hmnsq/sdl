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

#ifdef SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "SDL_x11video.h"

#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_scancode_tables_c.h"

#अन्तर्भाव <X11/keysym.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#अन्तर्भाव <X11/XKBlib.h>
#endif

#अन्तर्भाव "../../events/imKStoUCS.h"
#अन्तर्भाव "../../events/SDL_keysym_to_scancode_c.h"
#अन्तर्भाव "../../events/SDL_keysym_to_keycode_c.h"

#ifdef X_HAVE_UTF8_STRING
#अन्तर्भाव <locale.h>
#endif

स्थिर SDL_ScancodeTable scancode_set[] = {
    SDL_SCANCODE_TABLE_DARWIN,
    SDL_SCANCODE_TABLE_XFREE86_1,
    SDL_SCANCODE_TABLE_XFREE86_2,
    SDL_SCANCODE_TABLE_XVNC,
};

स्थिर bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    विकल्प (scancode) {
    पक्ष SDL_SCANCODE_ESCAPE:
    पक्ष SDL_SCANCODE_CAPSLOCK:
    पक्ष SDL_SCANCODE_NUMLOCKCLEAR:
    पक्ष SDL_SCANCODE_LSHIFT:
    पक्ष SDL_SCANCODE_RSHIFT:
    पक्ष SDL_SCANCODE_LCTRL:
    पक्ष SDL_SCANCODE_RCTRL:
    पक्ष SDL_SCANCODE_LALT:
    पक्ष SDL_SCANCODE_RALT:
    पक्ष SDL_SCANCODE_LGUI:
    पक्ष SDL_SCANCODE_RGUI:
        प्रत्यागम false;
    स्वभाव:
        प्रत्यागम true;
    }
}

स्थिर कुञ्चिका_Sym X11_कुञ्चिका_Code_To_Sym(SDL_VideoDevice *_this, कुञ्चिका_Code_2 keycode, unsigned पूर्णाङ्क group, unsigned पूर्णाङ्क level)
{
    SDL_VideoData *data = _this->internal;
    कुञ्चिका_Sym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    जइ (data->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(data->display, keycode, group, level);
    } अण्णहा
#endif
    {
        // TODO: Handle groups on the legacy path.
        जइ (keycode >= data->keyboard.core.min_keycode && keycode <= data->keyboard.core.max_keycode) {
            keysym = data->keyboard.core.keysym_map[(keycode - data->keyboard.core.min_keycode) * data->keyboard.core.keysyms_per_कुञ्चिका];
        } अण्णहा {
            keysym = No_चिह्नम्;
        }
    }

    प्रत्यागम keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
स्थिर SDL_Scancode X11_कुञ्चिका_Code_To_SDLScancode(SDL_VideoDevice *_this, कुञ्चिका_Code_2 keycode)
{
    ध्रुव कुञ्चिका_Sym keysym = X11_कुञ्चिका_Code_To_Sym(_this, keycode, 0, 0);

    जइ (keysym == No_चिह्नम्) {
        प्रत्यागम SDL_SCANCODE_UNKNOWN;
    }

    प्रत्यागम SDL_Get_Scancode_From_कुञ्चिका_Sym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
स्थिर bool X11_InitIM(SDL_VideoData *videodata);

स्थिर शून्य im_instantiate_handler(Display *display, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    जइ (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, रिक्त, रिक्त, रिक्त, im_instantiate_handler, clientData);
    }
}

स्थिर शून्य im_destroyed_handler(XIM im, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    videodata->im = रिक्त;
    X11_XRegisterIMInstantiateCallback(videodata->display, रिक्त, रिक्त, रिक्त, im_instantiate_handler, clientData);
}

स्थिर bool X11_InitIM(SDL_VideoData *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    वर्ण *prev_locale = setlocale(LC_ALL, रिक्त);
    वर्ण *prev_xmods = X11_XSetLocaleModifiers(रिक्त);

    जइ (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    जइ (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (शून्य)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, रिक्त, रिक्त, रिक्त);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (शून्य)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    जइ (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (वर्ण *)रिक्त);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        प्रति (पूर्णाङ्क i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *w = videodata->windowlist[i];
            जइ (!w->ic) {
                X11_Create_निवेशः_Context(w);
            }
        }

        प्रत्यागम true;
    }

    प्रत्यागम false;
}
#endif // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    पूर्णाङ्क i = 0;
    पूर्णाङ्क j = 0;
    पूर्णाङ्क min_keycode, max_keycode;
    संरचना
    {
        SDL_Scancode scancode;
        कुञ्चिका_Sym keysym;
        पूर्णाङ्क मानम्;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_वामः, XK_वामः, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    पूर्णाङ्क best_distance;
    पूर्णाङ्क best_index;
    पूर्णाङ्क distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    पूर्णाङ्क xkb_major = XkbMajorVersion;
    पूर्णाङ्क xkb_minor = XkbMinorVersion;

    जइ (X11_XkbQueryExtension(data->display, रिक्त, &data->keyboard.xkb.event, रिक्त, &xkb_major, &xkb_minor)) {
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
    } अण्णहा
#endif
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
        data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                              data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                              &data->keyboard.core.keysyms_per_कुञ्चिका);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    जइ (SDL_X11_HAVE_UTF8) {
        जइ (!X11_InitIM(data)) {
            X11_XRegisterIMInstantiateCallback(data->display, रिक्त, रिक्त, रिक्त, im_instantiate_handler, (XPointer)data);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_index = -1;
    X11_XDisplayKeycodes(data->display, &min_keycode, &max_keycode);
    प्रति (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].मानम् = X11_XKeysymToKeycode(data->display, fingerprint[i].keysym) - min_keycode;
    }
    प्रति (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        पूर्णाङ्क table_size;
        ध्रुव SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_size);

        distance = 0;
        प्रति (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            जइ (fingerprint[j].मानम् < 0 || fingerprint[j].मानम् >= table_size) {
                distance += 1;
            } अण्णहा जइ (table[fingerprint[j].मानम्] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        जइ (distance < best_distance) {
            best_distance = distance;
            best_index = i;
        }
    }
    जइ (best_index < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        पूर्णाङ्क fingerprint_मानम् = X11_XKeysymToKeycode(data->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        जइ (fingerprint_मानम् == 235) {
            प्रति (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                जइ (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_index = i;
                    best_distance = 0;
                    भङ्ग;
                }
            }
        }
    }
    जइ (best_index >= 0 && best_distance <= 2) {
        पूर्णाङ्क table_size;
        ध्रुव SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_index], &table_size);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_index, min_keycode, max_keycode, table_size);
#endif
        // This should never happen, but just in case...
        जइ (table_size > (SDL_arraysize(data->keyboard.कुञ्चिका_layout) - min_keycode)) {
            table_size = (SDL_arraysize(data->keyboard.कुञ्चिका_layout) - min_keycode);
        }
        SDL_memcpy(&data->keyboard.कुञ्चिका_layout[min_keycode], table, परिमाण(SDL_Scancode) * table_size);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        प्रति (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_कुञ्चिका_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                कुञ्चिका_Sym sym;
                sym = X11_कुञ्चिका_Code_To_Sym(_this, (कुञ्चिका_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned पूर्णाङ्क)sym, sym == No_चिह्नम् ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            जइ (scancode == data->keyboard.कुञ्चिका_layout[i]) {
                अनुवर्त;
            }
            जइ ((SDL_GetKeymapKeycode(रिक्त, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", data->कुञ्चिका_layout[i], SDL_GetScancodeName(data->कुञ्चिका_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                data->keyboard.कुञ्चिका_layout[i] = scancode;
            }
        }
    } अण्णहा {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        प्रति (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_कुञ्चिका_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                कुञ्चिका_Sym sym;
                sym = X11_कुञ्चिका_Code_To_Sym(_this, (कुञ्चिका_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned पूर्णाङ्क)sym, sym == No_चिह्नम् ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            जइ (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } अण्णहा {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            data->keyboard.कुञ्चिका_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    प्रत्यागम true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
स्थिर unsigned पूर्णाङ्क X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, ध्रुव वर्ण *vmod_name)
{
    SDL_VideoData *videodata = _this->internal;
    unsigned पूर्णाङ्क mod_mask = 0;

    ध्रुव Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    जइ (vmod != None) {
        प्रति (पूर्णाङ्क i = 0; i < Xkb_अङ्कः_Virtual_Mods; ++i) {
            जइ (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                भङ्ग;
            }
        }
    }

    प्रत्यागम mod_mask;
}
#endif

स्थिर unsigned X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    unsigned पूर्णाङ्क mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    unsigned पूर्णाङ्क n = xmods->max_keypermod;
    प्रति (पूर्णाङ्क i = 3; i < 8; i++) {
        प्रति (पूर्णाङ्क j = 0; j < n; j++) {
            ध्रुव कुञ्चिका_Code_2 kc = xmods->modifiermap[i * n + j];
            जइ (videodata->keyboard.कुञ्चिका_layout[kc] == scancode) {
                mod_mask = 1 << i;
                भङ्ग;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    प्रत्यागम mod_mask;
}

स्थिर शून्य X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, कुञ्चिका_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_कुञ्चिका_Code_From_कुञ्चिका_Sym(xkeysym, xkeycode, sdl_mod_mask);

    जइ (!keycode) {
        विकल्प (sdl_scancode) {
        पक्ष SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            भङ्ग;
        पक्ष SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            भङ्ग;
        पक्ष SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            भङ्ग;
        पक्ष SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            भङ्ग;
        स्वभाव:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            भङ्ग;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

शून्य X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    जइ (data->keyboard.xkb_enabled) {
        XkbStateRec state;

        प्रति (unsigned पूर्णाङ्क i = 0; i < Xkb_अङ्कः_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = रिक्त;
        }

        X11_XkbGetNames(data->display, XkbVirtualModNamesMask, data->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(data->display, XkbAllClientInfoMask | XkbVirtualModsMask, data->keyboard.xkb.desc_ptr);

        जइ (X11_XkbGetState(data->display, XkbUseCoreKbd, &state) == Success) {
            data->keyboard.xkb.current_group = state.group;
        }

        data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        जइ (!data->keyboard.alt_mask) {
            data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        data->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        data->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        data->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        data->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        data->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        प्रति (unsigned पूर्णाङ्क i = 0; i < Xkb_अङ्कः_Kbd_Groups; ++i) {
            data->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            जइ (!data->keyboard.xkb.keymaps[i]) {
                प्रति (unsigned पूर्णाङ्क j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
                    data->keyboard.xkb.keymaps[j] = रिक्त;
                }

                प्रत्यागम;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ध्रुव Uint32 valid_mod_mask = ShiftMask | LockMask | data->keyboard.alt_mask | data->keyboard.level3_mask | data->keyboard.level5_mask;

        प्रति (Uint32 xkeycode = data->keyboard.xkb.desc_ptr->min_कुञ्चिका_code; xkeycode < data->keyboard.xkb.desc_ptr->max_कुञ्चिका_code; ++xkeycode) {
            ध्रुव SDL_Scancode scancode = data->keyboard.कुञ्चिका_layout[xkeycode];
            जइ (scancode == SDL_SCANCODE_UNKNOWN) {
                अनुवर्त;
            }

            प्रति (Uint32 group = 0; group < Xkb_अङ्कः_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = data->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                ध्रुव unsigned वर्ण max_कुञ्चिका_group = Xkb_कुञ्चिका_अङ्कः_Groups(data->keyboard.xkb.desc_ptr, xkeycode);
                ध्रुव unsigned वर्ण कुञ्चिका_group_info = Xkb_कुञ्चिका_Group_Info(data->keyboard.xkb.desc_ptr, xkeycode);

                जइ (max_कुञ्चिका_group && effective_group >= max_कुञ्चिका_group) {
                    ध्रुव unsigned वर्ण action = XkbOutOfRangeGroupAction(कुञ्चिका_group_info);

                    विकल्प (action) {
                    स्वभाव:
                        effective_group %= max_कुञ्चिका_group;
                        भङ्ग;
                    पक्ष XkbClampIntoRange:
                        effective_group = max_कुञ्चिका_group - 1;
                        भङ्ग;
                    पक्ष XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_सङ्ख्या(कुञ्चिका_group_info);
                        जइ (effective_group >= max_कुञ्चिका_group) {
                            effective_group = 0;
                        }
                        भङ्ग;
                    }
                }

                Xkb_कुञ्चिका_Type_Ptr कुञ्चिका_type = Xkb_कुञ्चिका_कुञ्चिका_Type(data->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                प्रति (Uint32 level = 0; level < कुञ्चिका_type->अङ्कः_levels; ++level) {
                    ध्रुव कुञ्चिका_Sym keysym = X11_कुञ्चिका_Code_To_Sym(_this, xkeycode, effective_group, level);

                    जइ (keysym != No_चिह्नम्) {
                        bool कुञ्चिका_added = false;

                        प्रति (पूर्णाङ्क map_idx = 0; map_idx < कुञ्चिका_type->map_गणनम्; ++map_idx) {
                            जइ (कुञ्चिका_type->map[map_idx].active && कुञ्चिका_type->map[map_idx].level == level) {
                                ध्रुव unsigned पूर्णाङ्क xkb_mod_mask = कुञ्चिका_type->map[map_idx].mods.mask;
                                जइ ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    ध्रुव SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & data->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    कुञ्चिका_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        जइ (!level && !कुञ्चिका_added) {
                            X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_SetKeymap(data->keyboard.xkb.keymaps[data->keyboard.xkb.current_group], send_event);
    } अण्णहा
#endif
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        जइ (!keymap) {
            प्रत्यागम;
        }

        जइ (send_event) {
            जइ (data->keyboard.core.keysym_map) {
                X11_XFree(data->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
            data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                                     data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                                     &data->keyboard.core.keysyms_per_कुञ्चिका);
        }

        प्रति (Uint32 xkeycode = data->keyboard.core.min_keycode; xkeycode <= data->keyboard.core.max_keycode; ++xkeycode) {
            ध्रुव SDL_Scancode scancode = data->keyboard.कुञ्चिका_layout[xkeycode];
            जइ (scancode == SDL_SCANCODE_UNKNOWN) {
                अनुवर्त;
            }

            ध्रुव कुञ्चिका_Sym keysym = X11_कुञ्चिका_Code_To_Sym(_this, xkeycode, 0, 0);
            जइ (keysym != No_चिह्नम्) {
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

शून्य X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

#ifdef X_HAVE_UTF8_STRING
    जइ (data->im) {
        X11_XCloseIM(data->im);
        data->im = रिक्त;
    } अण्णहा {
        X11_XUnregisterIMInstantiateCallback(data->display, रिक्त, रिक्त, रिक्त, im_instantiate_handler, (XPointer)data);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    जइ (data->keyboard.xkb_enabled) {
        प्रति (पूर्णाङ्क i = 0; i < Xkb_अङ्कः_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = रिक्त;
        }

        जइ (data->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(data->keyboard.xkb.desc_ptr, 0, True);
            data->keyboard.xkb.desc_ptr = रिक्त;
        }
    } अण्णहा
#endif
        जइ (data->keyboard.core.keysym_map) {
        X11_XFree(data->keyboard.core.keysym_map);
        data->keyboard.core.keysym_map = रिक्त;
    }
}

शून्य X11_ClearComposition(SDL_WindowData *data)
{
    जइ (data->preedit_length > 0) {
        data->preedit_text[0] = '\0';
        data->preedit_length = 0;
    }

    जइ (data->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        data->ime_needs_clear_composition = false;
    }
}

स्थिर शून्य X11_SendEditingEvent(SDL_WindowData *data)
{
    जइ (data->preedit_length == 0) {
        X11_ClearComposition(data);
        प्रत्यागम;
    }

    bool in_highlight = false;
    पूर्णाङ्क start = -1, length = 0, i;
    प्रति (i = 0; i < data->preedit_length; ++i) {
        जइ (data->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            जइ (start < 0) {
                start = i;
                in_highlight = true;
            }
        } अण्णहा जइ (in_highlight) {
            // Found the end of the highlight
            भङ्ग;
        }
    }
    जइ (in_highlight) {
        length = (i - start);
    } अण्णहा {
        start = SDL_clamp(data->preedit_cursor, 0, data->preedit_length);
    }
    SDL_SendEditingText(data->preedit_text, start, length);

    data->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
स्थिर पूर्णाङ्क preedit_start_callback(XIC xic, XPointer client_data, XPointer call_data)
{
    // No limit on preedit text length
    प्रत्यागम -1;
}

स्थिर शून्य preedit_done_callback(XIC xic, XPointer client_data, XPointer call_data)
{
}

स्थिर शून्य preedit_draw_callback(XIC xic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;
    पूर्णाङ्क chg_first = SDL_clamp(call_data->chg_first, 0, data->preedit_length);
    पूर्णाङ्क chg_length = SDL_clamp(call_data->chg_length, 0, data->preedit_length - chg_first);

    ध्रुव वर्ण *start = data->preedit_text;
    जइ (chg_length > 0) {
        // Delete text in range
        प्रति (पूर्णाङ्क i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, रिक्त);
        }

        ध्रुव वर्ण *end = start;
        प्रति (पूर्णाङ्क i = 0; end && *end && i < chg_length; ++i) {
            SDL_StepUTF8(&end, रिक्त);
        }

        जइ (end > start) {
            SDL_memmove((वर्ण *)start, end, SDL_strlen(end) + 1);
            जइ ((chg_first + chg_length) > data->preedit_length) {
                SDL_memmove(&data->preedit_feedback[chg_first], &data->preedit_feedback[chg_first + chg_length], (data->preedit_length - chg_first - chg_length) * परिमाण(*data->preedit_feedback));
            }
        }
        data->preedit_length -= chg_length;
    }

    XIMText *text = call_data->text;
    जइ (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        जइ (text->string.multi_byte) {
            text->length = SDL_utf8strlen(text->string.multi_byte);
        }

        size_t string_size = SDL_strlen(text->string.multi_byte);
        size_t size = string_size + 1;
        जइ (data->preedit_text) {
            size += SDL_strlen(data->preedit_text);
        }
        वर्ण *preedit_text = (वर्ण *)SDL_malloc(size * परिमाण(*preedit_text));
        जइ (preedit_text) {
            size_t pre_size = (start - data->preedit_text);
            size_t post_size = start ? SDL_strlen(start) : 0;
            जइ (pre_size > 0) {
                SDL_memcpy(&preedit_text[0], data->preedit_text, pre_size);
            }
            SDL_memcpy(&preedit_text[pre_size], text->string.multi_byte, string_size);
            जइ (post_size > 0) {
                SDL_memcpy(&preedit_text[pre_size + string_size], start, post_size);
            }
            preedit_text[size - 1] = '\0';
        }

        size_t feedback_size = data->preedit_length + text->length;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_size * परिमाण(*feedback));
        जइ (feedback) {
            size_t pre_size = (size_t)chg_first;
            size_t post_size = (size_t)data->preedit_length - pre_size;
            जइ (pre_size > 0) {
                SDL_memcpy(&feedback[0], data->preedit_feedback, pre_size * परिमाण(*feedback));
            }
            SDL_memcpy(&feedback[pre_size], text->feedback, text->length * परिमाण(*feedback));
            जइ (post_size > 0) {
                SDL_memcpy(&feedback[pre_size + text->length], &data->preedit_feedback[pre_size], post_size * परिमाण(*feedback));
            }
        }

        जइ (preedit_text && feedback) {
            SDL_free(data->preedit_text);
            data->preedit_text = preedit_text;

            SDL_free(data->preedit_feedback);
            data->preedit_feedback = feedback;

            data->preedit_length += text->length;
        } अण्णहा {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    data->preedit_cursor = call_data->caret;

#ifdef DEBUG_XIM
    जइ (call_data->chg_length > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_data->chg_length, call_data->chg_first);
    }
    जइ (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_data->chg_first, call_data->caret);
    }
    SDL_Log("Pre-edit text: %s", data->preedit_text);
#endif

    X11_SendEditingEvent(data);
}

स्थिर शून्य preedit_caret_callback(XIC xic, XPointer client_data, XIMPreeditCaretCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;

    विकल्प (call_data->direction) {
    पक्ष XIMAbsolutePosition:
        जइ (call_data->position != data->preedit_cursor) {
            data->preedit_cursor = call_data->position;
            X11_SendEditingEvent(data);
        }
        भङ्ग;
    पक्ष XIMDontChange:
        भङ्ग;
    स्वभाव:
        // Not currently supported
        भङ्ग;
    }
}

स्थिर शून्य ic_destroyed_handler(XIC ic, XPointer clientData, XPointer callData)
{
    SDL_WindowData *data = (SDL_WindowData *)clientData;
    data->ic = रिक्त;
    X11_Destroy_निवेशः_Context(data);

    // If the IM was already recreated, create a new IC.
    जइ (data->videodata->im) {
        X11_Create_निवेशः_Context(data);
    }
}
#endif // X_HAVE_UTF8_STRING

शून्य X11_Create_निवेशः_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_VideoData *videodata = data->videodata;

    जइ (SDL_X11_HAVE_UTF8 && videodata->im) {
        ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)data;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        जइ (hint && SDL_strstr(hint, "composition")) {
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
                                                         रिक्त);
            जइ (attr) {
                data->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, data->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         रिक्त);
                X11_XFree(attr);
            }
        }
        जइ (!data->ic) {
            data->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClientWindow, data->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     रिक्त);
        }
        data->xim_spot.x = -1;
        data->xim_spot.y = -1;
    }
#endif // X_HAVE_UTF8_STRING
}


शून्य X11_Destroy_निवेशः_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    जइ (data->ic) {
        X11_XDestroyIC(data->ic);
        data->ic = रिक्त;
    }
    SDL_free(data->preedit_text);
    SDL_free(data->preedit_feedback);
    data->preedit_text = रिक्त;
    data->preedit_feedback = रिक्त;
#endif
}

स्थिर शून्य X11_ResetXIM(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    जइ (data && data->ic) {
        // Clear any partially entered dead keys
        वर्ण *contents = X11_Xutf8ResetIC(data->ic);
        जइ (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_निवेशः(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    प्रत्यागम X11_Update_Text_निवेशः_Area(_this, window);
}

bool X11_Stop_Text_निवेशः(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    प्रत्यागम true;
}

bool X11_Update_Text_निवेशः_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    जइ (data && data->ic) {
        XPoint spot;
        spot.x = window->text_निवेशः_rect.x + window->text_निवेशः_cursor;
        spot.y = window->text_निवेशः_rect.y + window->text_निवेशः_rect.h;
        जइ (spot.x != data->xim_spot.x || spot.y != data->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, रिक्त);
            जइ (attr) {
                X11_XSetICValues(data->ic, XNPreeditAttributes, attr, रिक्त);
                X11_XFree(attr);
            }
            SDL_copyp(&data->xim_spot, &spot);
        }
    }
#endif
    प्रत्यागम true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    प्रत्यागम videodata->use_steam_screen_keyboard;
}

शून्य X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;

    जइ (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ध्रुव पूर्णाङ्क k_EFloating_Gamepad_Text_निवेशः_Mode_Mode_Single_पङ्क्तिः = 0;    // Enter dismisses the keyboard
        ध्रुव पूर्णाङ्क k_EFloating_Gamepad_Text_निवेशः_Mode_Mode_Multiple_पङ्क्तयः = 1; // User needs to explicitly dismiss the keyboard
        ध्रुव पूर्णाङ्क k_EFloating_Gamepad_Text_निवेशः_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ध्रुव पूर्णाङ्क k_EFloating_Gamepad_Text_निवेशः_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        वर्ण deeplink[128];
        पूर्णाङ्क mode;

        विकल्प (SDL_Get_Text_निवेशः_Type(props)) {
        पक्ष SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_निवेशः_Mode_Mode_Email;
            भङ्ग;
        पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या:
        पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_HIDDEN:
        पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_निवेशः_Mode_Mode_Numeric;
            भङ्ग;
        स्वभाव:
            जइ (SDL_Get_Text_निवेशः_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_निवेशः_Mode_Mode_Multiple_पङ्क्तयः;
            } अण्णहा {
                mode = k_EFloating_Gamepad_Text_निवेशः_Mode_Mode_Single_पङ्क्तिः;
            }
            भङ्ग;
        }
        (शून्य)SDL_snprintf(deeplink, परिमाण(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_निवेशः_rect.x, window->text_निवेशः_rect.y,
                           window->text_निवेशः_rect.w, window->text_निवेशः_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

शून्य X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;

    जइ (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
