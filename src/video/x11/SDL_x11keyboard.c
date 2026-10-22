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
    निवड (scancode) {
    स्थिती SDL_SCANCODE_ESCAPE:
    स्थिती SDL_SCANCODE_CAPSLOCK:
    स्थिती SDL_SCANCODE_NUMLOCKCLEAR:
    स्थिती SDL_SCANCODE_LSHIFT:
    स्थिती SDL_SCANCODE_RSHIFT:
    स्थिती SDL_SCANCODE_LCTRL:
    स्थिती SDL_SCANCODE_RCTRL:
    स्थिती SDL_SCANCODE_LALT:
    स्थिती SDL_SCANCODE_RALT:
    स्थिती SDL_SCANCODE_LGUI:
    स्थिती SDL_SCANCODE_RGUI:
        परत false;
    पूर्वनिर्धारित:
        परत true;
    }
}

स्थिर किल्ली_Sym X11_किल्ली_Code_To_Sym(SDL_VideoDevice *_this, किल्ली_Code_2 keycode, अचिन्हित पूर्णांक group, अचिन्हित पूर्णांक level)
{
    SDL_VideoData *data = _this->internal;
    किल्ली_Sym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    जर (data->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(data->display, keycode, group, level);
    } अन्यथा
#endif
    {
        // TODO: Handle groups on the legacy path.
        जर (keycode >= data->keyboard.core.min_keycode && keycode <= data->keyboard.core.max_keycode) {
            keysym = data->keyboard.core.keysym_map[(keycode - data->keyboard.core.min_keycode) * data->keyboard.core.keysyms_per_किल्ली];
        } अन्यथा {
            keysym = No_चिन्ह;
        }
    }

    परत keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
स्थिर SDL_Scancode X11_किल्ली_Code_To_SDLScancode(SDL_VideoDevice *_this, किल्ली_Code_2 keycode)
{
    स्थिरांक किल्ली_Sym keysym = X11_किल्ली_Code_To_Sym(_this, keycode, 0, 0);

    जर (keysym == No_चिन्ह) {
        परत SDL_SCANCODE_UNKNOWN;
    }

    परत SDL_Get_Scancode_From_किल्ली_Sym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
स्थिर bool X11_InitIM(SDL_VideoData *videodata);

स्थिर शून्य im_instantiate_handler(Display *display, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    जर (X11_InitIM(videodata)) {
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
    अक्षर *prev_locale = रखो_क्षेत्र(LC_ALL, रिक्त);
    अक्षर *prev_xmods = X11_XSetLocaleModifiers(रिक्त);

    जर (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    जर (prev_xmods) {
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

    जर (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (अक्षर *)रिक्त);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        साठी (पूर्णांक i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *w = videodata->windowlist[i];
            जर (!w->ic) {
                X11_Create_आदान_Context(w);
            }
        }

        परत true;
    }

    परत false;
}
#endif // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    पूर्णांक i = 0;
    पूर्णांक j = 0;
    पूर्णांक min_keycode, max_keycode;
    संरचना
    {
        SDL_Scancode scancode;
        किल्ली_Sym keysym;
        पूर्णांक मूल्य;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_डावा, XK_डावा, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    पूर्णांक best_distance;
    पूर्णांक best_index;
    पूर्णांक distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    पूर्णांक xkb_major = XkbMajorVersion;
    पूर्णांक xkb_minor = XkbMinorVersion;

    जर (X11_XkbQueryExtension(data->display, रिक्त, &data->keyboard.xkb.event, रिक्त, &xkb_major, &xkb_minor)) {
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
                                                              &data->keyboard.core.keysyms_per_किल्ली);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    जर (SDL_X11_HAVE_UTF8) {
        जर (!X11_InitIM(data)) {
            X11_XRegisterIMInstantiateCallback(data->display, रिक्त, रिक्त, रिक्त, im_instantiate_handler, (XPointer)data);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_index = -1;
    X11_XDisplayKeycodes(data->display, &min_keycode, &max_keycode);
    साठी (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].मूल्य = X11_XKeysymToKeycode(data->display, fingerprint[i].keysym) - min_keycode;
    }
    साठी (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        पूर्णांक table_size;
        स्थिरांक SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_size);

        distance = 0;
        साठी (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            जर (fingerprint[j].मूल्य < 0 || fingerprint[j].मूल्य >= table_size) {
                distance += 1;
            } अन्यथा जर (table[fingerprint[j].मूल्य] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        जर (distance < best_distance) {
            best_distance = distance;
            best_index = i;
        }
    }
    जर (best_index < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        पूर्णांक fingerprint_मूल्य = X11_XKeysymToKeycode(data->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        जर (fingerprint_मूल्य == 235) {
            साठी (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                जर (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_index = i;
                    best_distance = 0;
                    थांबा;
                }
            }
        }
    }
    जर (best_index >= 0 && best_distance <= 2) {
        पूर्णांक table_size;
        स्थिरांक SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_index], &table_size);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_index, min_keycode, max_keycode, table_size);
#endif
        // This should never happen, but just in case...
        जर (table_size > (SDL_arraysize(data->keyboard.किल्ली_layout) - min_keycode)) {
            table_size = (SDL_arraysize(data->keyboard.किल्ली_layout) - min_keycode);
        }
        SDL_memcpy(&data->keyboard.किल्ली_layout[min_keycode], table, आकार(SDL_Scancode) * table_size);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        साठी (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_किल्ली_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                किल्ली_Sym sym;
                sym = X11_किल्ली_Code_To_Sym(_this, (किल्ली_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (अचिन्हित पूर्णांक)sym, sym == No_चिन्ह ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            जर (scancode == data->keyboard.किल्ली_layout[i]) {
                सुरूठेवा;
            }
            जर ((SDL_GetKeymapKeycode(रिक्त, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", data->किल्ली_layout[i], SDL_GetScancodeName(data->किल्ली_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                data->keyboard.किल्ली_layout[i] = scancode;
            }
        }
    } अन्यथा {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        साठी (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_किल्ली_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                किल्ली_Sym sym;
                sym = X11_किल्ली_Code_To_Sym(_this, (किल्ली_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (अचिन्हित पूर्णांक)sym, sym == No_चिन्ह ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            जर (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } अन्यथा {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            data->keyboard.किल्ली_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    परत true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
स्थिर अचिन्हित पूर्णांक X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, स्थिरांक अक्षर *vmod_name)
{
    SDL_VideoData *videodata = _this->internal;
    अचिन्हित पूर्णांक mod_mask = 0;

    स्थिरांक Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    जर (vmod != None) {
        साठी (पूर्णांक i = 0; i < Xkb_अंक_Virtual_Mods; ++i) {
            जर (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                थांबा;
            }
        }
    }

    परत mod_mask;
}
#endif

स्थिर अचिन्हित X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    अचिन्हित पूर्णांक mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    अचिन्हित पूर्णांक n = xmods->max_keypermod;
    साठी (पूर्णांक i = 3; i < 8; i++) {
        साठी (पूर्णांक j = 0; j < n; j++) {
            स्थिरांक किल्ली_Code_2 kc = xmods->modifiermap[i * n + j];
            जर (videodata->keyboard.किल्ली_layout[kc] == scancode) {
                mod_mask = 1 << i;
                थांबा;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    परत mod_mask;
}

स्थिर शून्य X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, किल्ली_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_किल्ली_Code_From_किल्ली_Sym(xkeysym, xkeycode, sdl_mod_mask);

    जर (!keycode) {
        निवड (sdl_scancode) {
        स्थिती SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            थांबा;
        स्थिती SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            थांबा;
        स्थिती SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            थांबा;
        स्थिती SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            थांबा;
        पूर्वनिर्धारित:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            थांबा;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

शून्य X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    जर (data->keyboard.xkb_enabled) {
        XkbStateRec state;

        साठी (अचिन्हित पूर्णांक i = 0; i < Xkb_अंक_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = रिक्त;
        }

        X11_XkbGetNames(data->display, XkbVirtualModNamesMask, data->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(data->display, XkbAllClientInfoMask | XkbVirtualModsMask, data->keyboard.xkb.desc_ptr);

        जर (X11_XkbGetState(data->display, XkbUseCoreKbd, &state) == Success) {
            data->keyboard.xkb.current_group = state.group;
        }

        data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        जर (!data->keyboard.alt_mask) {
            data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        data->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        data->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        data->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        data->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        data->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        साठी (अचिन्हित पूर्णांक i = 0; i < Xkb_अंक_Kbd_Groups; ++i) {
            data->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            जर (!data->keyboard.xkb.keymaps[i]) {
                साठी (अचिन्हित पूर्णांक j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
                    data->keyboard.xkb.keymaps[j] = रिक्त;
                }

                परत;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        स्थिरांक Uint32 valid_mod_mask = ShiftMask | LockMask | data->keyboard.alt_mask | data->keyboard.level3_mask | data->keyboard.level5_mask;

        साठी (Uint32 xkeycode = data->keyboard.xkb.desc_ptr->min_किल्ली_code; xkeycode < data->keyboard.xkb.desc_ptr->max_किल्ली_code; ++xkeycode) {
            स्थिरांक SDL_Scancode scancode = data->keyboard.किल्ली_layout[xkeycode];
            जर (scancode == SDL_SCANCODE_UNKNOWN) {
                सुरूठेवा;
            }

            साठी (Uint32 group = 0; group < Xkb_अंक_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = data->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                स्थिरांक अचिन्हित अक्षर max_किल्ली_group = Xkb_किल्ली_अंक_Groups(data->keyboard.xkb.desc_ptr, xkeycode);
                स्थिरांक अचिन्हित अक्षर किल्ली_group_info = Xkb_किल्ली_Group_Info(data->keyboard.xkb.desc_ptr, xkeycode);

                जर (max_किल्ली_group && effective_group >= max_किल्ली_group) {
                    स्थिरांक अचिन्हित अक्षर action = XkbOutOfRangeGroupAction(किल्ली_group_info);

                    निवड (action) {
                    पूर्वनिर्धारित:
                        effective_group %= max_किल्ली_group;
                        थांबा;
                    स्थिती XkbClampIntoRange:
                        effective_group = max_किल्ली_group - 1;
                        थांबा;
                    स्थिती XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_संख्या(किल्ली_group_info);
                        जर (effective_group >= max_किल्ली_group) {
                            effective_group = 0;
                        }
                        थांबा;
                    }
                }

                Xkb_किल्ली_Type_Ptr किल्ली_type = Xkb_किल्ली_किल्ली_Type(data->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                साठी (Uint32 level = 0; level < किल्ली_type->अंक_levels; ++level) {
                    स्थिरांक किल्ली_Sym keysym = X11_किल्ली_Code_To_Sym(_this, xkeycode, effective_group, level);

                    जर (keysym != No_चिन्ह) {
                        bool किल्ली_added = false;

                        साठी (पूर्णांक map_idx = 0; map_idx < किल्ली_type->map_मोजणी; ++map_idx) {
                            जर (किल्ली_type->map[map_idx].active && किल्ली_type->map[map_idx].level == level) {
                                स्थिरांक अचिन्हित पूर्णांक xkb_mod_mask = किल्ली_type->map[map_idx].mods.mask;
                                जर ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    स्थिरांक SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & data->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    किल्ली_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        जर (!level && !किल्ली_added) {
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
        जर (!keymap) {
            परत;
        }

        जर (send_event) {
            जर (data->keyboard.core.keysym_map) {
                X11_XFree(data->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
            data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                                     data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                                     &data->keyboard.core.keysyms_per_किल्ली);
        }

        साठी (Uint32 xkeycode = data->keyboard.core.min_keycode; xkeycode <= data->keyboard.core.max_keycode; ++xkeycode) {
            स्थिरांक SDL_Scancode scancode = data->keyboard.किल्ली_layout[xkeycode];
            जर (scancode == SDL_SCANCODE_UNKNOWN) {
                सुरूठेवा;
            }

            स्थिरांक किल्ली_Sym keysym = X11_किल्ली_Code_To_Sym(_this, xkeycode, 0, 0);
            जर (keysym != No_चिन्ह) {
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
    जर (data->im) {
        X11_XCloseIM(data->im);
        data->im = रिक्त;
    } अन्यथा {
        X11_XUnregisterIMInstantiateCallback(data->display, रिक्त, रिक्त, रिक्त, im_instantiate_handler, (XPointer)data);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    जर (data->keyboard.xkb_enabled) {
        साठी (पूर्णांक i = 0; i < Xkb_अंक_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = रिक्त;
        }

        जर (data->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(data->keyboard.xkb.desc_ptr, 0, True);
            data->keyboard.xkb.desc_ptr = रिक्त;
        }
    } अन्यथा
#endif
        जर (data->keyboard.core.keysym_map) {
        X11_XFree(data->keyboard.core.keysym_map);
        data->keyboard.core.keysym_map = रिक्त;
    }
}

शून्य X11_ClearComposition(SDL_WindowData *data)
{
    जर (data->preedit_length > 0) {
        data->preedit_text[0] = '\0';
        data->preedit_length = 0;
    }

    जर (data->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        data->ime_needs_clear_composition = false;
    }
}

स्थिर शून्य X11_SendEditingEvent(SDL_WindowData *data)
{
    जर (data->preedit_length == 0) {
        X11_ClearComposition(data);
        परत;
    }

    bool in_highlight = false;
    पूर्णांक start = -1, length = 0, i;
    साठी (i = 0; i < data->preedit_length; ++i) {
        जर (data->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            जर (start < 0) {
                start = i;
                in_highlight = true;
            }
        } अन्यथा जर (in_highlight) {
            // Found the end of the highlight
            थांबा;
        }
    }
    जर (in_highlight) {
        length = (i - start);
    } अन्यथा {
        start = SDL_clamp(data->preedit_cursor, 0, data->preedit_length);
    }
    SDL_SendEditingText(data->preedit_text, start, length);

    data->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
स्थिर पूर्णांक preedit_start_callback(XIC xic, XPointer client_data, XPointer call_data)
{
    // No limit on preedit text length
    परत -1;
}

स्थिर शून्य preedit_done_callback(XIC xic, XPointer client_data, XPointer call_data)
{
}

स्थिर शून्य preedit_draw_callback(XIC xic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;
    पूर्णांक chg_first = SDL_clamp(call_data->chg_first, 0, data->preedit_length);
    पूर्णांक chg_length = SDL_clamp(call_data->chg_length, 0, data->preedit_length - chg_first);

    स्थिरांक अक्षर *start = data->preedit_text;
    जर (chg_length > 0) {
        // Delete text in range
        साठी (पूर्णांक i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, रिक्त);
        }

        स्थिरांक अक्षर *end = start;
        साठी (पूर्णांक i = 0; end && *end && i < chg_length; ++i) {
            SDL_StepUTF8(&end, रिक्त);
        }

        जर (end > start) {
            SDL_memmove((अक्षर *)start, end, SDL_strlen(end) + 1);
            जर ((chg_first + chg_length) > data->preedit_length) {
                SDL_memmove(&data->preedit_feedback[chg_first], &data->preedit_feedback[chg_first + chg_length], (data->preedit_length - chg_first - chg_length) * आकार(*data->preedit_feedback));
            }
        }
        data->preedit_length -= chg_length;
    }

    XIMText *text = call_data->text;
    जर (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        जर (text->string.multi_byte) {
            text->length = SDL_utf8strlen(text->string.multi_byte);
        }

        माप_प्रकार string_size = SDL_strlen(text->string.multi_byte);
        माप_प्रकार size = string_size + 1;
        जर (data->preedit_text) {
            size += SDL_strlen(data->preedit_text);
        }
        अक्षर *preedit_text = (अक्षर *)SDL_malloc(size * आकार(*preedit_text));
        जर (preedit_text) {
            माप_प्रकार pre_size = (start - data->preedit_text);
            माप_प्रकार post_size = start ? SDL_strlen(start) : 0;
            जर (pre_size > 0) {
                SDL_memcpy(&preedit_text[0], data->preedit_text, pre_size);
            }
            SDL_memcpy(&preedit_text[pre_size], text->string.multi_byte, string_size);
            जर (post_size > 0) {
                SDL_memcpy(&preedit_text[pre_size + string_size], start, post_size);
            }
            preedit_text[size - 1] = '\0';
        }

        माप_प्रकार feedback_size = data->preedit_length + text->length;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_size * आकार(*feedback));
        जर (feedback) {
            माप_प्रकार pre_size = (माप_प्रकार)chg_first;
            माप_प्रकार post_size = (माप_प्रकार)data->preedit_length - pre_size;
            जर (pre_size > 0) {
                SDL_memcpy(&feedback[0], data->preedit_feedback, pre_size * आकार(*feedback));
            }
            SDL_memcpy(&feedback[pre_size], text->feedback, text->length * आकार(*feedback));
            जर (post_size > 0) {
                SDL_memcpy(&feedback[pre_size + text->length], &data->preedit_feedback[pre_size], post_size * आकार(*feedback));
            }
        }

        जर (preedit_text && feedback) {
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
    जर (call_data->chg_length > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_data->chg_length, call_data->chg_first);
    }
    जर (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_data->chg_first, call_data->caret);
    }
    SDL_Log("Pre-edit text: %s", data->preedit_text);
#endif

    X11_SendEditingEvent(data);
}

स्थिर शून्य preedit_caret_callback(XIC xic, XPointer client_data, XIMPreeditCaretCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;

    निवड (call_data->direction) {
    स्थिती XIMAbsolutePosition:
        जर (call_data->position != data->preedit_cursor) {
            data->preedit_cursor = call_data->position;
            X11_SendEditingEvent(data);
        }
        थांबा;
    स्थिती XIMDontChange:
        थांबा;
    पूर्वनिर्धारित:
        // Not currently supported
        थांबा;
    }
}

स्थिर शून्य ic_destroyed_handler(XIC ic, XPointer clientData, XPointer callData)
{
    SDL_WindowData *data = (SDL_WindowData *)clientData;
    data->ic = रिक्त;
    X11_Destroy_आदान_Context(data);

    // If the IM was already recreated, create a new IC.
    जर (data->videodata->im) {
        X11_Create_आदान_Context(data);
    }
}
#endif // X_HAVE_UTF8_STRING

शून्य X11_Create_आदान_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_VideoData *videodata = data->videodata;

    जर (SDL_X11_HAVE_UTF8 && videodata->im) {
        स्थिरांक अक्षर *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)data;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        जर (hint && SDL_strstr(hint, "composition")) {
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
            जर (attr) {
                data->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, data->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         रिक्त);
                X11_XFree(attr);
            }
        }
        जर (!data->ic) {
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


शून्य X11_Destroy_आदान_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    जर (data->ic) {
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

    जर (data && data->ic) {
        // Clear any partially entered dead keys
        अक्षर *contents = X11_Xutf8ResetIC(data->ic);
        जर (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_आदान(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    परत X11_Update_Text_आदान_Area(_this, window);
}

bool X11_Stop_Text_आदान(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    परत true;
}

bool X11_Update_Text_आदान_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    जर (data && data->ic) {
        XPoint spot;
        spot.x = window->text_आदान_rect.x + window->text_आदान_cursor;
        spot.y = window->text_आदान_rect.y + window->text_आदान_rect.h;
        जर (spot.x != data->xim_spot.x || spot.y != data->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, रिक्त);
            जर (attr) {
                X11_XSetICValues(data->ic, XNPreeditAttributes, attr, रिक्त);
                X11_XFree(attr);
            }
            SDL_copyp(&data->xim_spot, &spot);
        }
    }
#endif
    परत true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    परत videodata->use_steam_screen_keyboard;
}

शून्य X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;

    जर (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        स्थिरांक पूर्णांक k_EFloating_Gamepad_Text_आदान_Mode_Mode_Single_ओळ = 0;    // Enter dismisses the keyboard
        स्थिरांक पूर्णांक k_EFloating_Gamepad_Text_आदान_Mode_Mode_Multiple_ओळी = 1; // User needs to explicitly dismiss the keyboard
        स्थिरांक पूर्णांक k_EFloating_Gamepad_Text_आदान_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        स्थिरांक पूर्णांक k_EFloating_Gamepad_Text_आदान_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        अक्षर deeplink[128];
        पूर्णांक mode;

        निवड (SDL_Get_Text_आदान_Type(props)) {
        स्थिती SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_आदान_Mode_Mode_Email;
            थांबा;
        स्थिती SDL_TEXTINPUT_TYPE_संख्या:
        स्थिती SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_HIDDEN:
        स्थिती SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_आदान_Mode_Mode_Numeric;
            थांबा;
        पूर्वनिर्धारित:
            जर (SDL_Get_Text_आदान_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_आदान_Mode_Mode_Multiple_ओळी;
            } अन्यथा {
                mode = k_EFloating_Gamepad_Text_आदान_Mode_Mode_Single_ओळ;
            }
            थांबा;
        }
        (शून्य)SDL_snprintf(deeplink, आकार(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_आदान_rect.x, window->text_आदान_rect.y,
                           window->text_आदान_rect.w, window->text_आदान_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

शून्य X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;

    जर (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
