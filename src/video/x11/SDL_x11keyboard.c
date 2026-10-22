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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#அந்தர்பாவ "SDL_x11video.h"

#அந்தர்பாவ "../../events/SDL_keyboard_c.h"
#அந்தர்பாவ "../../events/SDL_scancode_tables_c.h"

#அந்தர்பாவ <X11/keysym.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#அந்தர்பாவ <X11/XKBlib.h>
#endif

#அந்தர்பாவ "../../events/imKStoUCS.h"
#அந்தர்பாவ "../../events/SDL_keysym_to_scancode_c.h"
#அந்தர்பாவ "../../events/SDL_keysym_to_keycode_c.h"

#ifdef X_HAVE_UTF8_STRING
#அந்தர்பாவ <locale.h>
#endif

நிலையான SDL_ScancodeTable scancode_set[] = {
    SDL_SCANCODE_TABLE_DARWIN,
    SDL_SCANCODE_TABLE_XFREE86_1,
    SDL_SCANCODE_TABLE_XFREE86_2,
    SDL_SCANCODE_TABLE_XVNC,
};

நிலையான bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    தேர்வு (scancode) {
    நிலை SDL_SCANCODE_ESCAPE:
    நிலை SDL_SCANCODE_CAPSLOCK:
    நிலை SDL_SCANCODE_NUMLOCKCLEAR:
    நிலை SDL_SCANCODE_LSHIFT:
    நிலை SDL_SCANCODE_RSHIFT:
    நிலை SDL_SCANCODE_LCTRL:
    நிலை SDL_SCANCODE_RCTRL:
    நிலை SDL_SCANCODE_LALT:
    நிலை SDL_SCANCODE_RALT:
    நிலை SDL_SCANCODE_LGUI:
    நிலை SDL_SCANCODE_RGUI:
        திரும்பு false;
    இயல்பு:
        திரும்பு true;
    }
}

நிலையான சாவி_Sym X11_சாவி_Code_To_Sym(SDL_VideoDevice *_this, சாவி_Code_2 keycode, unsigned முழு group, unsigned முழு level)
{
    SDL_VideoData *data = _this->internal;
    சாவி_Sym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    எனில் (data->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(data->display, keycode, group, level);
    } இல்லையெனில்
#endif
    {
        // TODO: Handle groups on the legacy path.
        எனில் (keycode >= data->keyboard.core.min_keycode && keycode <= data->keyboard.core.max_keycode) {
            keysym = data->keyboard.core.keysym_map[(keycode - data->keyboard.core.min_keycode) * data->keyboard.core.keysyms_per_சாவி];
        } இல்லையெனில் {
            keysym = No_குறியீடு;
        }
    }

    திரும்பு keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
நிலையான SDL_Scancode X11_சாவி_Code_To_SDLScancode(SDL_VideoDevice *_this, சாவி_Code_2 keycode)
{
    மாறிலி சாவி_Sym keysym = X11_சாவி_Code_To_Sym(_this, keycode, 0, 0);

    எனில் (keysym == No_குறியீடு) {
        திரும்பு SDL_SCANCODE_UNKNOWN;
    }

    திரும்பு SDL_Get_Scancode_From_சாவி_Sym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
நிலையான bool X11_InitIM(SDL_VideoData *videodata);

நிலையான வெறுமை im_instantiate_handler(Display *display, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    எனில் (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, வெற்று, வெற்று, வெற்று, im_instantiate_handler, clientData);
    }
}

நிலையான வெறுமை im_destroyed_handler(XIM im, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    videodata->im = வெற்று;
    X11_XRegisterIMInstantiateCallback(videodata->display, வெற்று, வெற்று, வெற்று, im_instantiate_handler, clientData);
}

நிலையான bool X11_InitIM(SDL_VideoData *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    எழுத்து *prev_locale = setlocale(LC_ALL, வெற்று);
    எழுத்து *prev_xmods = X11_XSetLocaleModifiers(வெற்று);

    எனில் (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    எனில் (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (வெறுமை)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, வெற்று, வெற்று, வெற்று);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (வெறுமை)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    எனில் (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (எழுத்து *)வெற்று);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        க்கு (முழு i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *w = videodata->windowlist[i];
            எனில் (!w->ic) {
                X11_Create_உள்ளீடு_Context(w);
            }
        }

        திரும்பு true;
    }

    திரும்பு false;
}
#endif // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    முழு i = 0;
    முழு j = 0;
    முழு min_keycode, max_keycode;
    கட்டமைப்பு
    {
        SDL_Scancode scancode;
        சாவி_Sym keysym;
        முழு மதிப்பு;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_இடது, XK_இடது, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    முழு best_distance;
    முழு best_index;
    முழு distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    முழு xkb_major = XkbMajorVersion;
    முழு xkb_minor = XkbMinorVersion;

    எனில் (X11_XkbQueryExtension(data->display, வெற்று, &data->keyboard.xkb.event, வெற்று, &xkb_major, &xkb_minor)) {
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
    } இல்லையெனில்
#endif
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
        data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                              data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                              &data->keyboard.core.keysyms_per_சாவி);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    எனில் (SDL_X11_HAVE_UTF8) {
        எனில் (!X11_InitIM(data)) {
            X11_XRegisterIMInstantiateCallback(data->display, வெற்று, வெற்று, வெற்று, im_instantiate_handler, (XPointer)data);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_index = -1;
    X11_XDisplayKeycodes(data->display, &min_keycode, &max_keycode);
    க்கு (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].மதிப்பு = X11_XKeysymToKeycode(data->display, fingerprint[i].keysym) - min_keycode;
    }
    க்கு (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        முழு table_size;
        மாறிலி SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_size);

        distance = 0;
        க்கு (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            எனில் (fingerprint[j].மதிப்பு < 0 || fingerprint[j].மதிப்பு >= table_size) {
                distance += 1;
            } இல்லையெனில் எனில் (table[fingerprint[j].மதிப்பு] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        எனில் (distance < best_distance) {
            best_distance = distance;
            best_index = i;
        }
    }
    எனில் (best_index < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        முழு fingerprint_மதிப்பு = X11_XKeysymToKeycode(data->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        எனில் (fingerprint_மதிப்பு == 235) {
            க்கு (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                எனில் (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_index = i;
                    best_distance = 0;
                    நிறுத்து;
                }
            }
        }
    }
    எனில் (best_index >= 0 && best_distance <= 2) {
        முழு table_size;
        மாறிலி SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_index], &table_size);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_index, min_keycode, max_keycode, table_size);
#endif
        // This should never happen, but just in case...
        எனில் (table_size > (SDL_arraysize(data->keyboard.சாவி_layout) - min_keycode)) {
            table_size = (SDL_arraysize(data->keyboard.சாவி_layout) - min_keycode);
        }
        SDL_memcpy(&data->keyboard.சாவி_layout[min_keycode], table, அளவு(SDL_Scancode) * table_size);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        க்கு (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_சாவி_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                சாவி_Sym sym;
                sym = X11_சாவி_Code_To_Sym(_this, (சாவி_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned முழு)sym, sym == No_குறியீடு ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            எனில் (scancode == data->keyboard.சாவி_layout[i]) {
                தொடர்;
            }
            எனில் ((SDL_GetKeymapKeycode(வெற்று, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", data->சாவி_layout[i], SDL_GetScancodeName(data->சாவி_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                data->keyboard.சாவி_layout[i] = scancode;
            }
        }
    } இல்லையெனில் {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        க்கு (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_சாவி_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                சாவி_Sym sym;
                sym = X11_சாவி_Code_To_Sym(_this, (சாவி_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned முழு)sym, sym == No_குறியீடு ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            எனில் (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } இல்லையெனில் {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            data->keyboard.சாவி_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    திரும்பு true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
நிலையான unsigned முழு X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, மாறிலி எழுத்து *vmod_name)
{
    SDL_VideoData *videodata = _this->internal;
    unsigned முழு mod_mask = 0;

    மாறிலி Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    எனில் (vmod != None) {
        க்கு (முழு i = 0; i < Xkb_இலக்கம்_Virtual_Mods; ++i) {
            எனில் (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                நிறுத்து;
            }
        }
    }

    திரும்பு mod_mask;
}
#endif

நிலையான unsigned X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    unsigned முழு mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    unsigned முழு n = xmods->max_keypermod;
    க்கு (முழு i = 3; i < 8; i++) {
        க்கு (முழு j = 0; j < n; j++) {
            மாறிலி சாவி_Code_2 kc = xmods->modifiermap[i * n + j];
            எனில் (videodata->keyboard.சாவி_layout[kc] == scancode) {
                mod_mask = 1 << i;
                நிறுத்து;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    திரும்பு mod_mask;
}

நிலையான வெறுமை X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, சாவி_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_சாவி_Code_From_சாவி_Sym(xkeysym, xkeycode, sdl_mod_mask);

    எனில் (!keycode) {
        தேர்வு (sdl_scancode) {
        நிலை SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            நிறுத்து;
        நிலை SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            நிறுத்து;
        நிலை SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            நிறுத்து;
        நிலை SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            நிறுத்து;
        இயல்பு:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            நிறுத்து;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

வெறுமை X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    எனில் (data->keyboard.xkb_enabled) {
        XkbStateRec state;

        க்கு (unsigned முழு i = 0; i < Xkb_இலக்கம்_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = வெற்று;
        }

        X11_XkbGetNames(data->display, XkbVirtualModNamesMask, data->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(data->display, XkbAllClientInfoMask | XkbVirtualModsMask, data->keyboard.xkb.desc_ptr);

        எனில் (X11_XkbGetState(data->display, XkbUseCoreKbd, &state) == Success) {
            data->keyboard.xkb.current_group = state.group;
        }

        data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        எனில் (!data->keyboard.alt_mask) {
            data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        data->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        data->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        data->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        data->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        data->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        க்கு (unsigned முழு i = 0; i < Xkb_இலக்கம்_Kbd_Groups; ++i) {
            data->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            எனில் (!data->keyboard.xkb.keymaps[i]) {
                க்கு (unsigned முழு j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
                    data->keyboard.xkb.keymaps[j] = வெற்று;
                }

                திரும்பு;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        மாறிலி Uint32 valid_mod_mask = ShiftMask | LockMask | data->keyboard.alt_mask | data->keyboard.level3_mask | data->keyboard.level5_mask;

        க்கு (Uint32 xkeycode = data->keyboard.xkb.desc_ptr->min_சாவி_code; xkeycode < data->keyboard.xkb.desc_ptr->max_சாவி_code; ++xkeycode) {
            மாறிலி SDL_Scancode scancode = data->keyboard.சாவி_layout[xkeycode];
            எனில் (scancode == SDL_SCANCODE_UNKNOWN) {
                தொடர்;
            }

            க்கு (Uint32 group = 0; group < Xkb_இலக்கம்_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = data->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                மாறிலி unsigned எழுத்து max_சாவி_group = Xkb_சாவி_இலக்கம்_Groups(data->keyboard.xkb.desc_ptr, xkeycode);
                மாறிலி unsigned எழுத்து சாவி_group_info = Xkb_சாவி_Group_Info(data->keyboard.xkb.desc_ptr, xkeycode);

                எனில் (max_சாவி_group && effective_group >= max_சாவி_group) {
                    மாறிலி unsigned எழுத்து action = XkbOutOfRangeGroupAction(சாவி_group_info);

                    தேர்வு (action) {
                    இயல்பு:
                        effective_group %= max_சாவி_group;
                        நிறுத்து;
                    நிலை XkbClampIntoRange:
                        effective_group = max_சாவி_group - 1;
                        நிறுத்து;
                    நிலை XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_எண்(சாவி_group_info);
                        எனில் (effective_group >= max_சாவி_group) {
                            effective_group = 0;
                        }
                        நிறுத்து;
                    }
                }

                Xkb_சாவி_Type_Ptr சாவி_type = Xkb_சாவி_சாவி_Type(data->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                க்கு (Uint32 level = 0; level < சாவி_type->இலக்கம்_levels; ++level) {
                    மாறிலி சாவி_Sym keysym = X11_சாவி_Code_To_Sym(_this, xkeycode, effective_group, level);

                    எனில் (keysym != No_குறியீடு) {
                        bool சாவி_added = false;

                        க்கு (முழு map_idx = 0; map_idx < சாவி_type->map_மொத்தம்; ++map_idx) {
                            எனில் (சாவி_type->map[map_idx].active && சாவி_type->map[map_idx].level == level) {
                                மாறிலி unsigned முழு xkb_mod_mask = சாவி_type->map[map_idx].mods.mask;
                                எனில் ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    மாறிலி SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & data->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    சாவி_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        எனில் (!level && !சாவி_added) {
                            X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_SetKeymap(data->keyboard.xkb.keymaps[data->keyboard.xkb.current_group], send_event);
    } இல்லையெனில்
#endif
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        எனில் (!keymap) {
            திரும்பு;
        }

        எனில் (send_event) {
            எனில் (data->keyboard.core.keysym_map) {
                X11_XFree(data->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
            data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                                     data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                                     &data->keyboard.core.keysyms_per_சாவி);
        }

        க்கு (Uint32 xkeycode = data->keyboard.core.min_keycode; xkeycode <= data->keyboard.core.max_keycode; ++xkeycode) {
            மாறிலி SDL_Scancode scancode = data->keyboard.சாவி_layout[xkeycode];
            எனில் (scancode == SDL_SCANCODE_UNKNOWN) {
                தொடர்;
            }

            மாறிலி சாவி_Sym keysym = X11_சாவி_Code_To_Sym(_this, xkeycode, 0, 0);
            எனில் (keysym != No_குறியீடு) {
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

வெறுமை X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

#ifdef X_HAVE_UTF8_STRING
    எனில் (data->im) {
        X11_XCloseIM(data->im);
        data->im = வெற்று;
    } இல்லையெனில் {
        X11_XUnregisterIMInstantiateCallback(data->display, வெற்று, வெற்று, வெற்று, im_instantiate_handler, (XPointer)data);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    எனில் (data->keyboard.xkb_enabled) {
        க்கு (முழு i = 0; i < Xkb_இலக்கம்_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = வெற்று;
        }

        எனில் (data->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(data->keyboard.xkb.desc_ptr, 0, True);
            data->keyboard.xkb.desc_ptr = வெற்று;
        }
    } இல்லையெனில்
#endif
        எனில் (data->keyboard.core.keysym_map) {
        X11_XFree(data->keyboard.core.keysym_map);
        data->keyboard.core.keysym_map = வெற்று;
    }
}

வெறுமை X11_ClearComposition(SDL_WindowData *data)
{
    எனில் (data->preedit_length > 0) {
        data->preedit_text[0] = '\0';
        data->preedit_length = 0;
    }

    எனில் (data->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        data->ime_needs_clear_composition = false;
    }
}

நிலையான வெறுமை X11_SendEditingEvent(SDL_WindowData *data)
{
    எனில் (data->preedit_length == 0) {
        X11_ClearComposition(data);
        திரும்பு;
    }

    bool in_highlight = false;
    முழு start = -1, length = 0, i;
    க்கு (i = 0; i < data->preedit_length; ++i) {
        எனில் (data->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            எனில் (start < 0) {
                start = i;
                in_highlight = true;
            }
        } இல்லையெனில் எனில் (in_highlight) {
            // Found the end of the highlight
            நிறுத்து;
        }
    }
    எனில் (in_highlight) {
        length = (i - start);
    } இல்லையெனில் {
        start = SDL_clamp(data->preedit_cursor, 0, data->preedit_length);
    }
    SDL_SendEditingText(data->preedit_text, start, length);

    data->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
நிலையான முழு preedit_start_callback(XIC xic, XPointer client_data, XPointer call_data)
{
    // No limit on preedit text length
    திரும்பு -1;
}

நிலையான வெறுமை preedit_done_callback(XIC xic, XPointer client_data, XPointer call_data)
{
}

நிலையான வெறுமை preedit_draw_callback(XIC xic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;
    முழு chg_first = SDL_clamp(call_data->chg_first, 0, data->preedit_length);
    முழு chg_length = SDL_clamp(call_data->chg_length, 0, data->preedit_length - chg_first);

    மாறிலி எழுத்து *start = data->preedit_text;
    எனில் (chg_length > 0) {
        // Delete text in range
        க்கு (முழு i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, வெற்று);
        }

        மாறிலி எழுத்து *end = start;
        க்கு (முழு i = 0; end && *end && i < chg_length; ++i) {
            SDL_StepUTF8(&end, வெற்று);
        }

        எனில் (end > start) {
            SDL_memmove((எழுத்து *)start, end, SDL_strlen(end) + 1);
            எனில் ((chg_first + chg_length) > data->preedit_length) {
                SDL_memmove(&data->preedit_feedback[chg_first], &data->preedit_feedback[chg_first + chg_length], (data->preedit_length - chg_first - chg_length) * அளவு(*data->preedit_feedback));
            }
        }
        data->preedit_length -= chg_length;
    }

    XIMText *text = call_data->text;
    எனில் (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        எனில் (text->string.multi_byte) {
            text->length = SDL_utf8strlen(text->string.multi_byte);
        }

        size_t string_size = SDL_strlen(text->string.multi_byte);
        size_t size = string_size + 1;
        எனில் (data->preedit_text) {
            size += SDL_strlen(data->preedit_text);
        }
        எழுத்து *preedit_text = (எழுத்து *)SDL_malloc(size * அளவு(*preedit_text));
        எனில் (preedit_text) {
            size_t pre_size = (start - data->preedit_text);
            size_t post_size = start ? SDL_strlen(start) : 0;
            எனில் (pre_size > 0) {
                SDL_memcpy(&preedit_text[0], data->preedit_text, pre_size);
            }
            SDL_memcpy(&preedit_text[pre_size], text->string.multi_byte, string_size);
            எனில் (post_size > 0) {
                SDL_memcpy(&preedit_text[pre_size + string_size], start, post_size);
            }
            preedit_text[size - 1] = '\0';
        }

        size_t feedback_size = data->preedit_length + text->length;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_size * அளவு(*feedback));
        எனில் (feedback) {
            size_t pre_size = (size_t)chg_first;
            size_t post_size = (size_t)data->preedit_length - pre_size;
            எனில் (pre_size > 0) {
                SDL_memcpy(&feedback[0], data->preedit_feedback, pre_size * அளவு(*feedback));
            }
            SDL_memcpy(&feedback[pre_size], text->feedback, text->length * அளவு(*feedback));
            எனில் (post_size > 0) {
                SDL_memcpy(&feedback[pre_size + text->length], &data->preedit_feedback[pre_size], post_size * அளவு(*feedback));
            }
        }

        எனில் (preedit_text && feedback) {
            SDL_free(data->preedit_text);
            data->preedit_text = preedit_text;

            SDL_free(data->preedit_feedback);
            data->preedit_feedback = feedback;

            data->preedit_length += text->length;
        } இல்லையெனில் {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    data->preedit_cursor = call_data->caret;

#ifdef DEBUG_XIM
    எனில் (call_data->chg_length > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_data->chg_length, call_data->chg_first);
    }
    எனில் (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_data->chg_first, call_data->caret);
    }
    SDL_Log("Pre-edit text: %s", data->preedit_text);
#endif

    X11_SendEditingEvent(data);
}

நிலையான வெறுமை preedit_caret_callback(XIC xic, XPointer client_data, XIMPreeditCaretCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;

    தேர்வு (call_data->direction) {
    நிலை XIMAbsolutePosition:
        எனில் (call_data->position != data->preedit_cursor) {
            data->preedit_cursor = call_data->position;
            X11_SendEditingEvent(data);
        }
        நிறுத்து;
    நிலை XIMDontChange:
        நிறுத்து;
    இயல்பு:
        // Not currently supported
        நிறுத்து;
    }
}

நிலையான வெறுமை ic_destroyed_handler(XIC ic, XPointer clientData, XPointer callData)
{
    SDL_WindowData *data = (SDL_WindowData *)clientData;
    data->ic = வெற்று;
    X11_Destroy_உள்ளீடு_Context(data);

    // If the IM was already recreated, create a new IC.
    எனில் (data->videodata->im) {
        X11_Create_உள்ளீடு_Context(data);
    }
}
#endif // X_HAVE_UTF8_STRING

வெறுமை X11_Create_உள்ளீடு_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_VideoData *videodata = data->videodata;

    எனில் (SDL_X11_HAVE_UTF8 && videodata->im) {
        மாறிலி எழுத்து *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)data;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        எனில் (hint && SDL_strstr(hint, "composition")) {
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
                                                         வெற்று);
            எனில் (attr) {
                data->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, data->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         வெற்று);
                X11_XFree(attr);
            }
        }
        எனில் (!data->ic) {
            data->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClientWindow, data->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     வெற்று);
        }
        data->xim_spot.x = -1;
        data->xim_spot.y = -1;
    }
#endif // X_HAVE_UTF8_STRING
}


வெறுமை X11_Destroy_உள்ளீடு_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    எனில் (data->ic) {
        X11_XDestroyIC(data->ic);
        data->ic = வெற்று;
    }
    SDL_free(data->preedit_text);
    SDL_free(data->preedit_feedback);
    data->preedit_text = வெற்று;
    data->preedit_feedback = வெற்று;
#endif
}

நிலையான வெறுமை X11_ResetXIM(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    எனில் (data && data->ic) {
        // Clear any partially entered dead keys
        எழுத்து *contents = X11_Xutf8ResetIC(data->ic);
        எனில் (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_உள்ளீடு(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    திரும்பு X11_Update_Text_உள்ளீடு_Area(_this, window);
}

bool X11_Stop_Text_உள்ளீடு(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    திரும்பு true;
}

bool X11_Update_Text_உள்ளீடு_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    எனில் (data && data->ic) {
        XPoint spot;
        spot.x = window->text_உள்ளீடு_rect.x + window->text_உள்ளீடு_cursor;
        spot.y = window->text_உள்ளீடு_rect.y + window->text_உள்ளீடு_rect.h;
        எனில் (spot.x != data->xim_spot.x || spot.y != data->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, வெற்று);
            எனில் (attr) {
                X11_XSetICValues(data->ic, XNPreeditAttributes, attr, வெற்று);
                X11_XFree(attr);
            }
            SDL_copyp(&data->xim_spot, &spot);
        }
    }
#endif
    திரும்பு true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    திரும்பு videodata->use_steam_screen_keyboard;
}

வெறுமை X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;

    எனில் (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        மாறிலி முழு k_EFloating_Gamepad_Text_உள்ளீடு_Mode_Mode_Single_வரி = 0;    // Enter dismisses the keyboard
        மாறிலி முழு k_EFloating_Gamepad_Text_உள்ளீடு_Mode_Mode_Multiple_வரிகள் = 1; // User needs to explicitly dismiss the keyboard
        மாறிலி முழு k_EFloating_Gamepad_Text_உள்ளீடு_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        மாறிலி முழு k_EFloating_Gamepad_Text_உள்ளீடு_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        எழுத்து deeplink[128];
        முழு mode;

        தேர்வு (SDL_Get_Text_உள்ளீடு_Type(props)) {
        நிலை SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_உள்ளீடு_Mode_Mode_Email;
            நிறுத்து;
        நிலை SDL_TEXTINPUT_TYPE_எண்:
        நிலை SDL_TEXTINPUT_TYPE_எண்_PASSWORD_HIDDEN:
        நிலை SDL_TEXTINPUT_TYPE_எண்_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_உள்ளீடு_Mode_Mode_Numeric;
            நிறுத்து;
        இயல்பு:
            எனில் (SDL_Get_Text_உள்ளீடு_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_உள்ளீடு_Mode_Mode_Multiple_வரிகள்;
            } இல்லையெனில் {
                mode = k_EFloating_Gamepad_Text_உள்ளீடு_Mode_Mode_Single_வரி;
            }
            நிறுத்து;
        }
        (வெறுமை)SDL_snprintf(deeplink, அளவு(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_உள்ளீடு_rect.x, window->text_உள்ளீடு_rect.y,
                           window->text_உள்ளீடு_rect.w, window->text_உள்ளீடு_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

வெறுமை X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;

    எனில் (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
