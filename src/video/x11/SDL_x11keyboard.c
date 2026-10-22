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
        फर्काऊ false;
    स्वभाव:
        फर्काऊ true;
    }
}

स्थिर साँचो_Sym X11_साँचो_Code_To_Sym(SDL_VideoDevice *_this, साँचो_Code_2 keycode, अचिन्हित पूर्णाङ्क group, अचिन्हित पूर्णाङ्क level)
{
    SDL_VideoData *data = _this->internal;
    साँचो_Sym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    यदि (data->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(data->display, keycode, group, level);
    } अन्यथा
#endif
    {
        // TODO: Handle groups on the legacy path.
        यदि (keycode >= data->keyboard.core.min_keycode && keycode <= data->keyboard.core.max_keycode) {
            keysym = data->keyboard.core.keysym_map[(keycode - data->keyboard.core.min_keycode) * data->keyboard.core.keysyms_per_साँचो];
        } अन्यथा {
            keysym = No_चिह्न;
        }
    }

    फर्काऊ keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
स्थिर SDL_Scancode X11_साँचो_Code_To_SDLScancode(SDL_VideoDevice *_this, साँचो_Code_2 keycode)
{
    अचर साँचो_Sym keysym = X11_साँचो_Code_To_Sym(_this, keycode, 0, 0);

    यदि (keysym == No_चिह्न) {
        फर्काऊ SDL_SCANCODE_UNKNOWN;
    }

    फर्काऊ SDL_Get_Scancode_From_साँचो_Sym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
स्थिर bool X11_InitIM(SDL_VideoData *videodata);

स्थिर शून्य im_instantiate_handler(Display *display, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    यदि (X11_InitIM(videodata)) {
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
    वर्ण *prev_locale = रखो_क्षेत्र(LC_ALL, रिक्त);
    वर्ण *prev_xmods = X11_XSetLocaleModifiers(रिक्त);

    यदि (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    यदि (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (शून्य)रखो_क्षेत्र(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, रिक्त, रिक्त, रिक्त);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (शून्य)रखो_क्षेत्र(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    यदि (im) {
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
        लागि (पूर्णाङ्क i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *w = videodata->windowlist[i];
            यदि (!w->ic) {
                X11_Create_आगत_Context(w);
            }
        }

        फर्काऊ true;
    }

    फर्काऊ false;
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
        साँचो_Sym keysym;
        पूर्णाङ्क मान;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_बायाँ, XK_बायाँ, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    पूर्णाङ्क best_distance;
    पूर्णाङ्क best_index;
    पूर्णाङ्क distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    पूर्णाङ्क xkb_major = XkbMajorVersion;
    पूर्णाङ्क xkb_minor = XkbMinorVersion;

    यदि (X11_XkbQueryExtension(data->display, रिक्त, &data->keyboard.xkb.event, रिक्त, &xkb_major, &xkb_minor)) {
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
    } अन्यथा
#endif
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
        data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                              data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                              &data->keyboard.core.keysyms_per_साँचो);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    यदि (SDL_X11_HAVE_UTF8) {
        यदि (!X11_InitIM(data)) {
            X11_XRegisterIMInstantiateCallback(data->display, रिक्त, रिक्त, रिक्त, im_instantiate_handler, (XPointer)data);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_index = -1;
    X11_XDisplayKeycodes(data->display, &min_keycode, &max_keycode);
    लागि (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].मान = X11_XKeysymToKeycode(data->display, fingerprint[i].keysym) - min_keycode;
    }
    लागि (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        पूर्णाङ्क table_size;
        अचर SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_size);

        distance = 0;
        लागि (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            यदि (fingerprint[j].मान < 0 || fingerprint[j].मान >= table_size) {
                distance += 1;
            } अन्यथा यदि (table[fingerprint[j].मान] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        यदि (distance < best_distance) {
            best_distance = distance;
            best_index = i;
        }
    }
    यदि (best_index < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        पूर्णाङ्क fingerprint_मान = X11_XKeysymToKeycode(data->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        यदि (fingerprint_मान == 235) {
            लागि (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                यदि (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_index = i;
                    best_distance = 0;
                    रोक;
                }
            }
        }
    }
    यदि (best_index >= 0 && best_distance <= 2) {
        पूर्णाङ्क table_size;
        अचर SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_index], &table_size);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_index, min_keycode, max_keycode, table_size);
#endif
        // This should never happen, but just in case...
        यदि (table_size > (SDL_arraysize(data->keyboard.साँचो_layout) - min_keycode)) {
            table_size = (SDL_arraysize(data->keyboard.साँचो_layout) - min_keycode);
        }
        SDL_memcpy(&data->keyboard.साँचो_layout[min_keycode], table, परिमाण(SDL_Scancode) * table_size);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        लागि (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_साँचो_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                साँचो_Sym sym;
                sym = X11_साँचो_Code_To_Sym(_this, (साँचो_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (अचिन्हित पूर्णाङ्क)sym, sym == No_चिह्न ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            यदि (scancode == data->keyboard.साँचो_layout[i]) {
                जारी;
            }
            यदि ((SDL_GetKeymapKeycode(रिक्त, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", data->साँचो_layout[i], SDL_GetScancodeName(data->साँचो_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                data->keyboard.साँचो_layout[i] = scancode;
            }
        }
    } अन्यथा {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        लागि (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_साँचो_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                साँचो_Sym sym;
                sym = X11_साँचो_Code_To_Sym(_this, (साँचो_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (अचिन्हित पूर्णाङ्क)sym, sym == No_चिह्न ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            यदि (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } अन्यथा {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            data->keyboard.साँचो_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    फर्काऊ true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
स्थिर अचिन्हित पूर्णाङ्क X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, अचर वर्ण *vmod_name)
{
    SDL_VideoData *videodata = _this->internal;
    अचिन्हित पूर्णाङ्क mod_mask = 0;

    अचर Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    यदि (vmod != None) {
        लागि (पूर्णाङ्क i = 0; i < Xkb_अङ्क_Virtual_Mods; ++i) {
            यदि (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                रोक;
            }
        }
    }

    फर्काऊ mod_mask;
}
#endif

स्थिर अचिन्हित X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    अचिन्हित पूर्णाङ्क mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    अचिन्हित पूर्णाङ्क n = xmods->max_keypermod;
    लागि (पूर्णाङ्क i = 3; i < 8; i++) {
        लागि (पूर्णाङ्क j = 0; j < n; j++) {
            अचर साँचो_Code_2 kc = xmods->modifiermap[i * n + j];
            यदि (videodata->keyboard.साँचो_layout[kc] == scancode) {
                mod_mask = 1 << i;
                रोक;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    फर्काऊ mod_mask;
}

स्थिर शून्य X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, साँचो_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_साँचो_Code_From_साँचो_Sym(xkeysym, xkeycode, sdl_mod_mask);

    यदि (!keycode) {
        विकल्प (sdl_scancode) {
        पक्ष SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            रोक;
        पक्ष SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            रोक;
        पक्ष SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            रोक;
        पक्ष SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            रोक;
        स्वभाव:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            रोक;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

शून्य X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    यदि (data->keyboard.xkb_enabled) {
        XkbStateRec state;

        लागि (अचिन्हित पूर्णाङ्क i = 0; i < Xkb_अङ्क_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = रिक्त;
        }

        X11_XkbGetNames(data->display, XkbVirtualModNamesMask, data->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(data->display, XkbAllClientInfoMask | XkbVirtualModsMask, data->keyboard.xkb.desc_ptr);

        यदि (X11_XkbGetState(data->display, XkbUseCoreKbd, &state) == Success) {
            data->keyboard.xkb.current_group = state.group;
        }

        data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        यदि (!data->keyboard.alt_mask) {
            data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        data->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        data->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        data->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        data->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        data->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        लागि (अचिन्हित पूर्णाङ्क i = 0; i < Xkb_अङ्क_Kbd_Groups; ++i) {
            data->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            यदि (!data->keyboard.xkb.keymaps[i]) {
                लागि (अचिन्हित पूर्णाङ्क j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
                    data->keyboard.xkb.keymaps[j] = रिक्त;
                }

                फर्काऊ;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        अचर Uint32 valid_mod_mask = ShiftMask | LockMask | data->keyboard.alt_mask | data->keyboard.level3_mask | data->keyboard.level5_mask;

        लागि (Uint32 xkeycode = data->keyboard.xkb.desc_ptr->min_साँचो_code; xkeycode < data->keyboard.xkb.desc_ptr->max_साँचो_code; ++xkeycode) {
            अचर SDL_Scancode scancode = data->keyboard.साँचो_layout[xkeycode];
            यदि (scancode == SDL_SCANCODE_UNKNOWN) {
                जारी;
            }

            लागि (Uint32 group = 0; group < Xkb_अङ्क_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = data->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                अचर अचिन्हित वर्ण max_साँचो_group = Xkb_साँचो_अङ्क_Groups(data->keyboard.xkb.desc_ptr, xkeycode);
                अचर अचिन्हित वर्ण साँचो_group_info = Xkb_साँचो_Group_Info(data->keyboard.xkb.desc_ptr, xkeycode);

                यदि (max_साँचो_group && effective_group >= max_साँचो_group) {
                    अचर अचिन्हित वर्ण action = XkbOutOfRangeGroupAction(साँचो_group_info);

                    विकल्प (action) {
                    स्वभाव:
                        effective_group %= max_साँचो_group;
                        रोक;
                    पक्ष XkbClampIntoRange:
                        effective_group = max_साँचो_group - 1;
                        रोक;
                    पक्ष XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_सङ्ख्या(साँचो_group_info);
                        यदि (effective_group >= max_साँचो_group) {
                            effective_group = 0;
                        }
                        रोक;
                    }
                }

                Xkb_साँचो_Type_Ptr साँचो_type = Xkb_साँचो_साँचो_Type(data->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                लागि (Uint32 level = 0; level < साँचो_type->अङ्क_levels; ++level) {
                    अचर साँचो_Sym keysym = X11_साँचो_Code_To_Sym(_this, xkeycode, effective_group, level);

                    यदि (keysym != No_चिह्न) {
                        bool साँचो_added = false;

                        लागि (पूर्णाङ्क map_idx = 0; map_idx < साँचो_type->map_गन्ती; ++map_idx) {
                            यदि (साँचो_type->map[map_idx].active && साँचो_type->map[map_idx].level == level) {
                                अचर अचिन्हित पूर्णाङ्क xkb_mod_mask = साँचो_type->map[map_idx].mods.mask;
                                यदि ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    अचर SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & data->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    साँचो_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        यदि (!level && !साँचो_added) {
                            X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_SetKeymap(data->keyboard.xkb.keymaps[data->keyboard.xkb.current_group], send_event);
    } अन्यथा
#endif
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        यदि (!keymap) {
            फर्काऊ;
        }

        यदि (send_event) {
            यदि (data->keyboard.core.keysym_map) {
                X11_XFree(data->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
            data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                                     data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                                     &data->keyboard.core.keysyms_per_साँचो);
        }

        लागि (Uint32 xkeycode = data->keyboard.core.min_keycode; xkeycode <= data->keyboard.core.max_keycode; ++xkeycode) {
            अचर SDL_Scancode scancode = data->keyboard.साँचो_layout[xkeycode];
            यदि (scancode == SDL_SCANCODE_UNKNOWN) {
                जारी;
            }

            अचर साँचो_Sym keysym = X11_साँचो_Code_To_Sym(_this, xkeycode, 0, 0);
            यदि (keysym != No_चिह्न) {
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
    यदि (data->im) {
        X11_XCloseIM(data->im);
        data->im = रिक्त;
    } अन्यथा {
        X11_XUnregisterIMInstantiateCallback(data->display, रिक्त, रिक्त, रिक्त, im_instantiate_handler, (XPointer)data);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    यदि (data->keyboard.xkb_enabled) {
        लागि (पूर्णाङ्क i = 0; i < Xkb_अङ्क_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = रिक्त;
        }

        यदि (data->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(data->keyboard.xkb.desc_ptr, 0, True);
            data->keyboard.xkb.desc_ptr = रिक्त;
        }
    } अन्यथा
#endif
        यदि (data->keyboard.core.keysym_map) {
        X11_XFree(data->keyboard.core.keysym_map);
        data->keyboard.core.keysym_map = रिक्त;
    }
}

शून्य X11_ClearComposition(SDL_WindowData *data)
{
    यदि (data->preedit_length > 0) {
        data->preedit_text[0] = '\0';
        data->preedit_length = 0;
    }

    यदि (data->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        data->ime_needs_clear_composition = false;
    }
}

स्थिर शून्य X11_SendEditingEvent(SDL_WindowData *data)
{
    यदि (data->preedit_length == 0) {
        X11_ClearComposition(data);
        फर्काऊ;
    }

    bool in_highlight = false;
    पूर्णाङ्क start = -1, length = 0, i;
    लागि (i = 0; i < data->preedit_length; ++i) {
        यदि (data->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            यदि (start < 0) {
                start = i;
                in_highlight = true;
            }
        } अन्यथा यदि (in_highlight) {
            // Found the end of the highlight
            रोक;
        }
    }
    यदि (in_highlight) {
        length = (i - start);
    } अन्यथा {
        start = SDL_clamp(data->preedit_cursor, 0, data->preedit_length);
    }
    SDL_SendEditingText(data->preedit_text, start, length);

    data->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
स्थिर पूर्णाङ्क preedit_start_callback(XIC xic, XPointer client_data, XPointer call_data)
{
    // No limit on preedit text length
    फर्काऊ -1;
}

स्थिर शून्य preedit_done_callback(XIC xic, XPointer client_data, XPointer call_data)
{
}

स्थिर शून्य preedit_draw_callback(XIC xic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;
    पूर्णाङ्क chg_first = SDL_clamp(call_data->chg_first, 0, data->preedit_length);
    पूर्णाङ्क chg_length = SDL_clamp(call_data->chg_length, 0, data->preedit_length - chg_first);

    अचर वर्ण *start = data->preedit_text;
    यदि (chg_length > 0) {
        // Delete text in range
        लागि (पूर्णाङ्क i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, रिक्त);
        }

        अचर वर्ण *end = start;
        लागि (पूर्णाङ्क i = 0; end && *end && i < chg_length; ++i) {
            SDL_StepUTF8(&end, रिक्त);
        }

        यदि (end > start) {
            SDL_memmove((वर्ण *)start, end, SDL_strlen(end) + 1);
            यदि ((chg_first + chg_length) > data->preedit_length) {
                SDL_memmove(&data->preedit_feedback[chg_first], &data->preedit_feedback[chg_first + chg_length], (data->preedit_length - chg_first - chg_length) * परिमाण(*data->preedit_feedback));
            }
        }
        data->preedit_length -= chg_length;
    }

    XIMText *text = call_data->text;
    यदि (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        यदि (text->string.multi_byte) {
            text->length = SDL_utf8strlen(text->string.multi_byte);
        }

        माप_प्रकार string_size = SDL_strlen(text->string.multi_byte);
        माप_प्रकार size = string_size + 1;
        यदि (data->preedit_text) {
            size += SDL_strlen(data->preedit_text);
        }
        वर्ण *preedit_text = (वर्ण *)SDL_malloc(size * परिमाण(*preedit_text));
        यदि (preedit_text) {
            माप_प्रकार pre_size = (start - data->preedit_text);
            माप_प्रकार post_size = start ? SDL_strlen(start) : 0;
            यदि (pre_size > 0) {
                SDL_memcpy(&preedit_text[0], data->preedit_text, pre_size);
            }
            SDL_memcpy(&preedit_text[pre_size], text->string.multi_byte, string_size);
            यदि (post_size > 0) {
                SDL_memcpy(&preedit_text[pre_size + string_size], start, post_size);
            }
            preedit_text[size - 1] = '\0';
        }

        माप_प्रकार feedback_size = data->preedit_length + text->length;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_size * परिमाण(*feedback));
        यदि (feedback) {
            माप_प्रकार pre_size = (माप_प्रकार)chg_first;
            माप_प्रकार post_size = (माप_प्रकार)data->preedit_length - pre_size;
            यदि (pre_size > 0) {
                SDL_memcpy(&feedback[0], data->preedit_feedback, pre_size * परिमाण(*feedback));
            }
            SDL_memcpy(&feedback[pre_size], text->feedback, text->length * परिमाण(*feedback));
            यदि (post_size > 0) {
                SDL_memcpy(&feedback[pre_size + text->length], &data->preedit_feedback[pre_size], post_size * परिमाण(*feedback));
            }
        }

        यदि (preedit_text && feedback) {
            SDL_free(data->preedit_text);
            data->preedit_text = preedit_text;

            SDL_free(data->preedit_feedback);
            data->preedit_feedback = feedback;

            data->preedit_length += text->length;
        } अन्यथा {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    data->preedit_cursor = call_data->caret;

#ifdef DEBUG_XIM
    यदि (call_data->chg_length > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_data->chg_length, call_data->chg_first);
    }
    यदि (text) {
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
        यदि (call_data->position != data->preedit_cursor) {
            data->preedit_cursor = call_data->position;
            X11_SendEditingEvent(data);
        }
        रोक;
    पक्ष XIMDontChange:
        रोक;
    स्वभाव:
        // Not currently supported
        रोक;
    }
}

स्थिर शून्य ic_destroyed_handler(XIC ic, XPointer clientData, XPointer callData)
{
    SDL_WindowData *data = (SDL_WindowData *)clientData;
    data->ic = रिक्त;
    X11_Destroy_आगत_Context(data);

    // If the IM was already recreated, create a new IC.
    यदि (data->videodata->im) {
        X11_Create_आगत_Context(data);
    }
}
#endif // X_HAVE_UTF8_STRING

शून्य X11_Create_आगत_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_VideoData *videodata = data->videodata;

    यदि (SDL_X11_HAVE_UTF8 && videodata->im) {
        अचर वर्ण *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)data;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        यदि (hint && SDL_strstr(hint, "composition")) {
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
            यदि (attr) {
                data->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, data->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         रिक्त);
                X11_XFree(attr);
            }
        }
        यदि (!data->ic) {
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


शून्य X11_Destroy_आगत_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    यदि (data->ic) {
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

    यदि (data && data->ic) {
        // Clear any partially entered dead keys
        वर्ण *contents = X11_Xutf8ResetIC(data->ic);
        यदि (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_आगत(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    फर्काऊ X11_Update_Text_आगत_Area(_this, window);
}

bool X11_Stop_Text_आगत(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    फर्काऊ true;
}

bool X11_Update_Text_आगत_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    यदि (data && data->ic) {
        XPoint spot;
        spot.x = window->text_आगत_rect.x + window->text_आगत_cursor;
        spot.y = window->text_आगत_rect.y + window->text_आगत_rect.h;
        यदि (spot.x != data->xim_spot.x || spot.y != data->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, रिक्त);
            यदि (attr) {
                X11_XSetICValues(data->ic, XNPreeditAttributes, attr, रिक्त);
                X11_XFree(attr);
            }
            SDL_copyp(&data->xim_spot, &spot);
        }
    }
#endif
    फर्काऊ true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    फर्काऊ videodata->use_steam_screen_keyboard;
}

शून्य X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;

    यदि (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        अचर पूर्णाङ्क k_EFloating_Gamepad_Text_आगत_Mode_Mode_Single_पङ्क्ति = 0;    // Enter dismisses the keyboard
        अचर पूर्णाङ्क k_EFloating_Gamepad_Text_आगत_Mode_Mode_Multiple_पङ्क्तिहरू = 1; // User needs to explicitly dismiss the keyboard
        अचर पूर्णाङ्क k_EFloating_Gamepad_Text_आगत_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        अचर पूर्णाङ्क k_EFloating_Gamepad_Text_आगत_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        वर्ण deeplink[128];
        पूर्णाङ्क mode;

        विकल्प (SDL_Get_Text_आगत_Type(props)) {
        पक्ष SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_आगत_Mode_Mode_Email;
            रोक;
        पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या:
        पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_HIDDEN:
        पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_आगत_Mode_Mode_Numeric;
            रोक;
        स्वभाव:
            यदि (SDL_Get_Text_आगत_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_आगत_Mode_Mode_Multiple_पङ्क्तिहरू;
            } अन्यथा {
                mode = k_EFloating_Gamepad_Text_आगत_Mode_Mode_Single_पङ्क्ति;
            }
            रोक;
        }
        (शून्य)SDL_snprintf(deeplink, परिमाण(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_आगत_rect.x, window->text_आगत_rect.y,
                           window->text_आगत_rect.w, window->text_आगत_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

शून्य X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;

    यदि (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
