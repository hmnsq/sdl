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

#ifdef SDL_VIDEO_DRIVER_X11

#شامل "SDL_x11video.h"

#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_scancode_tables_c.h"

#شامل <X11/keysym.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#شامل <X11/XKBlib.h>
#endif

#شامل "../../events/imKStoUCS.h"
#شامل "../../events/SDL_keysym_to_scancode_c.h"
#شامل "../../events/SDL_keysym_to_keycode_c.h"

#ifdef X_HAVE_UTF8_STRING
#شامل <locale.h>
#endif

ایستا SDL_ScancodeTable scancode_set[] = {
    SDL_SCANCODE_TABLE_DARWIN,
    SDL_SCANCODE_TABLE_XFREE86_1,
    SDL_SCANCODE_TABLE_XFREE86_2,
    SDL_SCANCODE_TABLE_XVNC,
};

ایستا bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
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
        بازگشت false;
    پیشفرض:
        بازگشت true;
    }
}

ایستا کلید_Sym X11_کلید_Code_To_Sym(SDL_VideoDevice *_this, کلید_Code_2 keycode, unsigned صحیح group, unsigned صحیح level)
{
    SDL_VideoData *data = _this->internal;
    کلید_Sym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    اگر (data->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(data->display, keycode, group, level);
    } وگرنه
#endif
    {
        // TODO: Handle groups on the legacy path.
        اگر (keycode >= data->keyboard.core.min_keycode && keycode <= data->keyboard.core.max_keycode) {
            keysym = data->keyboard.core.keysym_map[(keycode - data->keyboard.core.min_keycode) * data->keyboard.core.keysyms_per_کلید];
        } وگرنه {
            keysym = No_نماد;
        }
    }

    بازگشت keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
ایستا SDL_Scancode X11_کلید_Code_To_SDLScancode(SDL_VideoDevice *_this, کلید_Code_2 keycode)
{
    ثابت کلید_Sym keysym = X11_کلید_Code_To_Sym(_this, keycode, 0, 0);

    اگر (keysym == No_نماد) {
        بازگشت SDL_SCANCODE_UNKNOWN;
    }

    بازگشت SDL_Get_Scancode_From_کلید_Sym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
ایستا bool X11_InitIM(SDL_VideoData *videodata);

ایستا تهی im_instantiate_handler(Display *display, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    اگر (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, پوچ, پوچ, پوچ, im_instantiate_handler, clientData);
    }
}

ایستا تهی im_destroyed_handler(XIM im, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    videodata->im = پوچ;
    X11_XRegisterIMInstantiateCallback(videodata->display, پوچ, پوچ, پوچ, im_instantiate_handler, clientData);
}

ایستا bool X11_InitIM(SDL_VideoData *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    نویسه *prev_locale = setlocale(LC_ALL, پوچ);
    نویسه *prev_xmods = X11_XSetLocaleModifiers(پوچ);

    اگر (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    اگر (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (تهی)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, پوچ, پوچ, پوچ);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (تهی)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    اگر (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (نویسه *)پوچ);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        برای (صحیح i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *w = videodata->windowlist[i];
            اگر (!w->ic) {
                X11_Create_درون_داد_Context(w);
            }
        }

        بازگشت true;
    }

    بازگشت false;
}
#endif // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    صحیح i = 0;
    صحیح j = 0;
    صحیح min_keycode, max_keycode;
    ساختار
    {
        SDL_Scancode scancode;
        کلید_Sym keysym;
        صحیح مقدار;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_چپ, XK_چپ, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    صحیح best_distance;
    صحیح best_index;
    صحیح distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    صحیح xkb_major = XkbMajorVersion;
    صحیح xkb_minor = XkbMinorVersion;

    اگر (X11_XkbQueryExtension(data->display, پوچ, &data->keyboard.xkb.event, پوچ, &xkb_major, &xkb_minor)) {
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
    } وگرنه
#endif
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
        data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                              data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                              &data->keyboard.core.keysyms_per_کلید);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    اگر (SDL_X11_HAVE_UTF8) {
        اگر (!X11_InitIM(data)) {
            X11_XRegisterIMInstantiateCallback(data->display, پوچ, پوچ, پوچ, im_instantiate_handler, (XPointer)data);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_index = -1;
    X11_XDisplayKeycodes(data->display, &min_keycode, &max_keycode);
    برای (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].مقدار = X11_XKeysymToKeycode(data->display, fingerprint[i].keysym) - min_keycode;
    }
    برای (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        صحیح table_size;
        ثابت SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_size);

        distance = 0;
        برای (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            اگر (fingerprint[j].مقدار < 0 || fingerprint[j].مقدار >= table_size) {
                distance += 1;
            } وگرنه اگر (table[fingerprint[j].مقدار] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        اگر (distance < best_distance) {
            best_distance = distance;
            best_index = i;
        }
    }
    اگر (best_index < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        صحیح fingerprint_مقدار = X11_XKeysymToKeycode(data->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        اگر (fingerprint_مقدار == 235) {
            برای (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                اگر (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_index = i;
                    best_distance = 0;
                    بشکن;
                }
            }
        }
    }
    اگر (best_index >= 0 && best_distance <= 2) {
        صحیح table_size;
        ثابت SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_index], &table_size);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_index, min_keycode, max_keycode, table_size);
#endif
        // This should never happen, but just in case...
        اگر (table_size > (SDL_arraysize(data->keyboard.کلید_layout) - min_keycode)) {
            table_size = (SDL_arraysize(data->keyboard.کلید_layout) - min_keycode);
        }
        SDL_memcpy(&data->keyboard.کلید_layout[min_keycode], table, اندازه(SDL_Scancode) * table_size);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        برای (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_کلید_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                کلید_Sym sym;
                sym = X11_کلید_Code_To_Sym(_this, (کلید_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned صحیح)sym, sym == No_نماد ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            اگر (scancode == data->keyboard.کلید_layout[i]) {
                ادامه;
            }
            اگر ((SDL_GetKeymapKeycode(پوچ, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", data->کلید_layout[i], SDL_GetScancodeName(data->کلید_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                data->keyboard.کلید_layout[i] = scancode;
            }
        }
    } وگرنه {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        برای (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_کلید_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                کلید_Sym sym;
                sym = X11_کلید_Code_To_Sym(_this, (کلید_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned صحیح)sym, sym == No_نماد ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            اگر (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } وگرنه {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            data->keyboard.کلید_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    بازگشت true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
ایستا unsigned صحیح X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, ثابت نویسه *vmod_name)
{
    SDL_VideoData *videodata = _this->internal;
    unsigned صحیح mod_mask = 0;

    ثابت Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    اگر (vmod != None) {
        برای (صحیح i = 0; i < Xkb_رقم_Virtual_Mods; ++i) {
            اگر (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                بشکن;
            }
        }
    }

    بازگشت mod_mask;
}
#endif

ایستا unsigned X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    unsigned صحیح mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    unsigned صحیح n = xmods->max_keypermod;
    برای (صحیح i = 3; i < 8; i++) {
        برای (صحیح j = 0; j < n; j++) {
            ثابت کلید_Code_2 kc = xmods->modifiermap[i * n + j];
            اگر (videodata->keyboard.کلید_layout[kc] == scancode) {
                mod_mask = 1 << i;
                بشکن;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    بازگشت mod_mask;
}

ایستا تهی X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, کلید_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_کلید_Code_From_کلید_Sym(xkeysym, xkeycode, sdl_mod_mask);

    اگر (!keycode) {
        انتخاب (sdl_scancode) {
        حالت SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            بشکن;
        حالت SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            بشکن;
        حالت SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            بشکن;
        حالت SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            بشکن;
        پیشفرض:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            بشکن;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

تهی X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    اگر (data->keyboard.xkb_enabled) {
        XkbStateRec state;

        برای (unsigned صحیح i = 0; i < Xkb_رقم_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = پوچ;
        }

        X11_XkbGetNames(data->display, XkbVirtualModNamesMask, data->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(data->display, XkbAllClientInfoMask | XkbVirtualModsMask, data->keyboard.xkb.desc_ptr);

        اگر (X11_XkbGetState(data->display, XkbUseCoreKbd, &state) == Success) {
            data->keyboard.xkb.current_group = state.group;
        }

        data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        اگر (!data->keyboard.alt_mask) {
            data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        data->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        data->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        data->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        data->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        data->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        برای (unsigned صحیح i = 0; i < Xkb_رقم_Kbd_Groups; ++i) {
            data->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            اگر (!data->keyboard.xkb.keymaps[i]) {
                برای (unsigned صحیح j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
                    data->keyboard.xkb.keymaps[j] = پوچ;
                }

                بازگشت;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ثابت Uint32 valid_mod_mask = ShiftMask | LockMask | data->keyboard.alt_mask | data->keyboard.level3_mask | data->keyboard.level5_mask;

        برای (Uint32 xkeycode = data->keyboard.xkb.desc_ptr->min_کلید_code; xkeycode < data->keyboard.xkb.desc_ptr->max_کلید_code; ++xkeycode) {
            ثابت SDL_Scancode scancode = data->keyboard.کلید_layout[xkeycode];
            اگر (scancode == SDL_SCANCODE_UNKNOWN) {
                ادامه;
            }

            برای (Uint32 group = 0; group < Xkb_رقم_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = data->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                ثابت unsigned نویسه max_کلید_group = Xkb_کلید_رقم_Groups(data->keyboard.xkb.desc_ptr, xkeycode);
                ثابت unsigned نویسه کلید_group_info = Xkb_کلید_Group_Info(data->keyboard.xkb.desc_ptr, xkeycode);

                اگر (max_کلید_group && effective_group >= max_کلید_group) {
                    ثابت unsigned نویسه action = XkbOutOfRangeGroupAction(کلید_group_info);

                    انتخاب (action) {
                    پیشفرض:
                        effective_group %= max_کلید_group;
                        بشکن;
                    حالت XkbClampIntoRange:
                        effective_group = max_کلید_group - 1;
                        بشکن;
                    حالت XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_عدد(کلید_group_info);
                        اگر (effective_group >= max_کلید_group) {
                            effective_group = 0;
                        }
                        بشکن;
                    }
                }

                Xkb_کلید_Type_Ptr کلید_type = Xkb_کلید_کلید_Type(data->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                برای (Uint32 level = 0; level < کلید_type->رقم_levels; ++level) {
                    ثابت کلید_Sym keysym = X11_کلید_Code_To_Sym(_this, xkeycode, effective_group, level);

                    اگر (keysym != No_نماد) {
                        bool کلید_added = false;

                        برای (صحیح map_idx = 0; map_idx < کلید_type->map_شمار; ++map_idx) {
                            اگر (کلید_type->map[map_idx].active && کلید_type->map[map_idx].level == level) {
                                ثابت unsigned صحیح xkb_mod_mask = کلید_type->map[map_idx].mods.mask;
                                اگر ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    ثابت SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & data->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    کلید_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        اگر (!level && !کلید_added) {
                            X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_SetKeymap(data->keyboard.xkb.keymaps[data->keyboard.xkb.current_group], send_event);
    } وگرنه
#endif
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        اگر (!keymap) {
            بازگشت;
        }

        اگر (send_event) {
            اگر (data->keyboard.core.keysym_map) {
                X11_XFree(data->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
            data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                                     data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                                     &data->keyboard.core.keysyms_per_کلید);
        }

        برای (Uint32 xkeycode = data->keyboard.core.min_keycode; xkeycode <= data->keyboard.core.max_keycode; ++xkeycode) {
            ثابت SDL_Scancode scancode = data->keyboard.کلید_layout[xkeycode];
            اگر (scancode == SDL_SCANCODE_UNKNOWN) {
                ادامه;
            }

            ثابت کلید_Sym keysym = X11_کلید_Code_To_Sym(_this, xkeycode, 0, 0);
            اگر (keysym != No_نماد) {
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

تهی X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

#ifdef X_HAVE_UTF8_STRING
    اگر (data->im) {
        X11_XCloseIM(data->im);
        data->im = پوچ;
    } وگرنه {
        X11_XUnregisterIMInstantiateCallback(data->display, پوچ, پوچ, پوچ, im_instantiate_handler, (XPointer)data);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    اگر (data->keyboard.xkb_enabled) {
        برای (صحیح i = 0; i < Xkb_رقم_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = پوچ;
        }

        اگر (data->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(data->keyboard.xkb.desc_ptr, 0, True);
            data->keyboard.xkb.desc_ptr = پوچ;
        }
    } وگرنه
#endif
        اگر (data->keyboard.core.keysym_map) {
        X11_XFree(data->keyboard.core.keysym_map);
        data->keyboard.core.keysym_map = پوچ;
    }
}

تهی X11_ClearComposition(SDL_WindowData *data)
{
    اگر (data->preedit_length > 0) {
        data->preedit_text[0] = '\0';
        data->preedit_length = 0;
    }

    اگر (data->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        data->ime_needs_clear_composition = false;
    }
}

ایستا تهی X11_SendEditingEvent(SDL_WindowData *data)
{
    اگر (data->preedit_length == 0) {
        X11_ClearComposition(data);
        بازگشت;
    }

    bool in_highlight = false;
    صحیح start = -1, length = 0, i;
    برای (i = 0; i < data->preedit_length; ++i) {
        اگر (data->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            اگر (start < 0) {
                start = i;
                in_highlight = true;
            }
        } وگرنه اگر (in_highlight) {
            // Found the end of the highlight
            بشکن;
        }
    }
    اگر (in_highlight) {
        length = (i - start);
    } وگرنه {
        start = SDL_clamp(data->preedit_cursor, 0, data->preedit_length);
    }
    SDL_SendEditingText(data->preedit_text, start, length);

    data->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
ایستا صحیح preedit_start_callback(XIC xic, XPointer client_data, XPointer call_data)
{
    // No limit on preedit text length
    بازگشت -1;
}

ایستا تهی preedit_done_callback(XIC xic, XPointer client_data, XPointer call_data)
{
}

ایستا تهی preedit_draw_callback(XIC xic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;
    صحیح chg_first = SDL_clamp(call_data->chg_first, 0, data->preedit_length);
    صحیح chg_length = SDL_clamp(call_data->chg_length, 0, data->preedit_length - chg_first);

    ثابت نویسه *start = data->preedit_text;
    اگر (chg_length > 0) {
        // Delete text in range
        برای (صحیح i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, پوچ);
        }

        ثابت نویسه *end = start;
        برای (صحیح i = 0; end && *end && i < chg_length; ++i) {
            SDL_StepUTF8(&end, پوچ);
        }

        اگر (end > start) {
            SDL_memmove((نویسه *)start, end, SDL_strlen(end) + 1);
            اگر ((chg_first + chg_length) > data->preedit_length) {
                SDL_memmove(&data->preedit_feedback[chg_first], &data->preedit_feedback[chg_first + chg_length], (data->preedit_length - chg_first - chg_length) * اندازه(*data->preedit_feedback));
            }
        }
        data->preedit_length -= chg_length;
    }

    XIMText *text = call_data->text;
    اگر (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        اگر (text->string.multi_byte) {
            text->length = SDL_utf8strlen(text->string.multi_byte);
        }

        size_t string_size = SDL_strlen(text->string.multi_byte);
        size_t size = string_size + 1;
        اگر (data->preedit_text) {
            size += SDL_strlen(data->preedit_text);
        }
        نویسه *preedit_text = (نویسه *)SDL_malloc(size * اندازه(*preedit_text));
        اگر (preedit_text) {
            size_t pre_size = (start - data->preedit_text);
            size_t post_size = start ? SDL_strlen(start) : 0;
            اگر (pre_size > 0) {
                SDL_memcpy(&preedit_text[0], data->preedit_text, pre_size);
            }
            SDL_memcpy(&preedit_text[pre_size], text->string.multi_byte, string_size);
            اگر (post_size > 0) {
                SDL_memcpy(&preedit_text[pre_size + string_size], start, post_size);
            }
            preedit_text[size - 1] = '\0';
        }

        size_t feedback_size = data->preedit_length + text->length;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_size * اندازه(*feedback));
        اگر (feedback) {
            size_t pre_size = (size_t)chg_first;
            size_t post_size = (size_t)data->preedit_length - pre_size;
            اگر (pre_size > 0) {
                SDL_memcpy(&feedback[0], data->preedit_feedback, pre_size * اندازه(*feedback));
            }
            SDL_memcpy(&feedback[pre_size], text->feedback, text->length * اندازه(*feedback));
            اگر (post_size > 0) {
                SDL_memcpy(&feedback[pre_size + text->length], &data->preedit_feedback[pre_size], post_size * اندازه(*feedback));
            }
        }

        اگر (preedit_text && feedback) {
            SDL_free(data->preedit_text);
            data->preedit_text = preedit_text;

            SDL_free(data->preedit_feedback);
            data->preedit_feedback = feedback;

            data->preedit_length += text->length;
        } وگرنه {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    data->preedit_cursor = call_data->caret;

#ifdef DEBUG_XIM
    اگر (call_data->chg_length > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_data->chg_length, call_data->chg_first);
    }
    اگر (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_data->chg_first, call_data->caret);
    }
    SDL_Log("Pre-edit text: %s", data->preedit_text);
#endif

    X11_SendEditingEvent(data);
}

ایستا تهی preedit_caret_callback(XIC xic, XPointer client_data, XIMPreeditCaretCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;

    انتخاب (call_data->direction) {
    حالت XIMAbsolutePosition:
        اگر (call_data->position != data->preedit_cursor) {
            data->preedit_cursor = call_data->position;
            X11_SendEditingEvent(data);
        }
        بشکن;
    حالت XIMDontChange:
        بشکن;
    پیشفرض:
        // Not currently supported
        بشکن;
    }
}

ایستا تهی ic_destroyed_handler(XIC ic, XPointer clientData, XPointer callData)
{
    SDL_WindowData *data = (SDL_WindowData *)clientData;
    data->ic = پوچ;
    X11_Destroy_درون_داد_Context(data);

    // If the IM was already recreated, create a new IC.
    اگر (data->videodata->im) {
        X11_Create_درون_داد_Context(data);
    }
}
#endif // X_HAVE_UTF8_STRING

تهی X11_Create_درون_داد_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_VideoData *videodata = data->videodata;

    اگر (SDL_X11_HAVE_UTF8 && videodata->im) {
        ثابت نویسه *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)data;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        اگر (hint && SDL_strstr(hint, "composition")) {
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
                                                         پوچ);
            اگر (attr) {
                data->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, data->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         پوچ);
                X11_XFree(attr);
            }
        }
        اگر (!data->ic) {
            data->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClientWindow, data->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     پوچ);
        }
        data->xim_spot.x = -1;
        data->xim_spot.y = -1;
    }
#endif // X_HAVE_UTF8_STRING
}


تهی X11_Destroy_درون_داد_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    اگر (data->ic) {
        X11_XDestroyIC(data->ic);
        data->ic = پوچ;
    }
    SDL_free(data->preedit_text);
    SDL_free(data->preedit_feedback);
    data->preedit_text = پوچ;
    data->preedit_feedback = پوچ;
#endif
}

ایستا تهی X11_ResetXIM(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    اگر (data && data->ic) {
        // Clear any partially entered dead keys
        نویسه *contents = X11_Xutf8ResetIC(data->ic);
        اگر (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_درون_داد(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    بازگشت X11_Update_Text_درون_داد_Area(_this, window);
}

bool X11_Stop_Text_درون_داد(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    بازگشت true;
}

bool X11_Update_Text_درون_داد_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    اگر (data && data->ic) {
        XPoint spot;
        spot.x = window->text_درون_داد_rect.x + window->text_درون_داد_cursor;
        spot.y = window->text_درون_داد_rect.y + window->text_درون_داد_rect.h;
        اگر (spot.x != data->xim_spot.x || spot.y != data->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, پوچ);
            اگر (attr) {
                X11_XSetICValues(data->ic, XNPreeditAttributes, attr, پوچ);
                X11_XFree(attr);
            }
            SDL_copyp(&data->xim_spot, &spot);
        }
    }
#endif
    بازگشت true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    بازگشت videodata->use_steam_screen_keyboard;
}

تهی X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;

    اگر (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ثابت صحیح k_EFloating_Gamepad_Text_درون_داد_Mode_Mode_Single_سطر = 0;    // Enter dismisses the keyboard
        ثابت صحیح k_EFloating_Gamepad_Text_درون_داد_Mode_Mode_Multiple_سطرها = 1; // User needs to explicitly dismiss the keyboard
        ثابت صحیح k_EFloating_Gamepad_Text_درون_داد_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ثابت صحیح k_EFloating_Gamepad_Text_درون_داد_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        نویسه deeplink[128];
        صحیح mode;

        انتخاب (SDL_Get_Text_درون_داد_Type(props)) {
        حالت SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_درون_داد_Mode_Mode_Email;
            بشکن;
        حالت SDL_TEXTINPUT_TYPE_عدد:
        حالت SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
        حالت SDL_TEXTINPUT_TYPE_عدد_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_درون_داد_Mode_Mode_Numeric;
            بشکن;
        پیشفرض:
            اگر (SDL_Get_Text_درون_داد_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_درون_داد_Mode_Mode_Multiple_سطرها;
            } وگرنه {
                mode = k_EFloating_Gamepad_Text_درون_داد_Mode_Mode_Single_سطر;
            }
            بشکن;
        }
        (تهی)SDL_snprintf(deeplink, اندازه(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_درون_داد_rect.x, window->text_درون_داد_rect.y,
                           window->text_درون_داد_rect.w, window->text_درون_داد_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

تهی X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;

    اگر (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
