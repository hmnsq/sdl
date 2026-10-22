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

#ifdef SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"

#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_scancode_tables_c.h"

#ضمن <X11/keysym.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#ضمن <X11/XKBlib.h>
#endif

#ضمن "../../events/imKStoUCS.h"
#ضمن "../../events/SDL_keysym_to_scancode_c.h"
#ضمن "../../events/SDL_keysym_to_keycode_c.h"

#ifdef X_HAVE_UTF8_STRING
#ضمن <locale.h>
#endif

ساكن SDL_ScancodeTable scancode_set[] = {
    SDL_SCANCODE_TABLE_DARWIN,
    SDL_SCANCODE_TABLE_XFREE86_1,
    SDL_SCANCODE_TABLE_XFREE86_2,
    SDL_SCANCODE_TABLE_XVNC,
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

ساكن کونچي_Sym X11_کونچي_Code_To_Sym(SDL_VideoDevice *_this, کونچي_Code_2 keycode, unsigned صحيح group, unsigned صحيح level)
{
    SDL_VideoData *data = _this->internal;
    کونچي_Sym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (data->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(data->display, keycode, group, level);
    } وإلا
#endif
    {
        // TODO: Handle groups on the legacy path.
        إذا (keycode >= data->keyboard.core.min_keycode && keycode <= data->keyboard.core.max_keycode) {
            keysym = data->keyboard.core.keysym_map[(keycode - data->keyboard.core.min_keycode) * data->keyboard.core.keysyms_per_کونچي];
        } وإلا {
            keysym = No_سيمبول;
        }
    }

    أرجع keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
ساكن SDL_Scancode X11_کونچي_Code_To_SDLScancode(SDL_VideoDevice *_this, کونچي_Code_2 keycode)
{
    ثابت کونچي_Sym keysym = X11_کونچي_Code_To_Sym(_this, keycode, 0, 0);

    إذا (keysym == No_سيمبول) {
        أرجع SDL_SCANCODE_UNKNOWN;
    }

    أرجع SDL_Get_Scancode_From_کونچي_Sym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
ساكن bool X11_InitIM(SDL_VideoData *videodata);

ساكن فراغ im_instantiate_handler(Display *display, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    إذا (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, عدم, عدم, عدم, im_instantiate_handler, clientData);
    }
}

ساكن فراغ im_destroyed_handler(XIM im, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    videodata->im = عدم;
    X11_XRegisterIMInstantiateCallback(videodata->display, عدم, عدم, عدم, im_instantiate_handler, clientData);
}

ساكن bool X11_InitIM(SDL_VideoData *videodata)
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
        destroyed_callback.client_data = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (حرف *)عدم);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        لكل (صحيح i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *w = videodata->windowlist[i];
            إذا (!w->ic) {
                X11_Create_ماسوقن_Context(w);
            }
        }

        أرجع true;
    }

    أرجع false;
}
#endif // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    صحيح i = 0;
    صحيح j = 0;
    صحيح min_keycode, max_keycode;
    بنية
    {
        SDL_Scancode scancode;
        کونچي_Sym keysym;
        صحيح نيلاي;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_کيري, XK_کيري, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    صحيح best_distance;
    صحيح best_index;
    صحيح distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    صحيح xkb_major = XkbMajorVersion;
    صحيح xkb_minor = XkbMinorVersion;

    إذا (X11_XkbQueryExtension(data->display, عدم, &data->keyboard.xkb.event, عدم, &xkb_major, &xkb_minor)) {
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
    } وإلا
#endif
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
        data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                              data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                              &data->keyboard.core.keysyms_per_کونچي);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    إذا (SDL_X11_HAVE_UTF8) {
        إذا (!X11_InitIM(data)) {
            X11_XRegisterIMInstantiateCallback(data->display, عدم, عدم, عدم, im_instantiate_handler, (XPointer)data);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_index = -1;
    X11_XDisplayKeycodes(data->display, &min_keycode, &max_keycode);
    لكل (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].نيلاي = X11_XKeysymToKeycode(data->display, fingerprint[i].keysym) - min_keycode;
    }
    لكل (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        صحيح table_size;
        ثابت SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_size);

        distance = 0;
        لكل (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            إذا (fingerprint[j].نيلاي < 0 || fingerprint[j].نيلاي >= table_size) {
                distance += 1;
            } وإلا إذا (table[fingerprint[j].نيلاي] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        إذا (distance < best_distance) {
            best_distance = distance;
            best_index = i;
        }
    }
    إذا (best_index < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        صحيح fingerprint_نيلاي = X11_XKeysymToKeycode(data->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        إذا (fingerprint_نيلاي == 235) {
            لكل (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                إذا (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_index = i;
                    best_distance = 0;
                    اكسر;
                }
            }
        }
    }
    إذا (best_index >= 0 && best_distance <= 2) {
        صحيح table_size;
        ثابت SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_index], &table_size);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_index, min_keycode, max_keycode, table_size);
#endif
        // This should never happen, but just in case...
        إذا (table_size > (SDL_arraysize(data->keyboard.کونچي_layout) - min_keycode)) {
            table_size = (SDL_arraysize(data->keyboard.کونچي_layout) - min_keycode);
        }
        SDL_memcpy(&data->keyboard.کونچي_layout[min_keycode], table, حجم(SDL_Scancode) * table_size);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        لكل (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_کونچي_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                کونچي_Sym sym;
                sym = X11_کونچي_Code_To_Sym(_this, (کونچي_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned صحيح)sym, sym == No_سيمبول ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            إذا (scancode == data->keyboard.کونچي_layout[i]) {
                استمر;
            }
            إذا ((SDL_GetKeymapKeycode(عدم, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", data->کونچي_layout[i], SDL_GetScancodeName(data->کونچي_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                data->keyboard.کونچي_layout[i] = scancode;
            }
        }
    } وإلا {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        لكل (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_کونچي_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                کونچي_Sym sym;
                sym = X11_کونچي_Code_To_Sym(_this, (کونچي_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned صحيح)sym, sym == No_سيمبول ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } وإلا {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            data->keyboard.کونچي_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    أرجع true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
ساكن unsigned صحيح X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, ثابت حرف *vmod_name)
{
    SDL_VideoData *videodata = _this->internal;
    unsigned صحيح mod_mask = 0;

    ثابت Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    إذا (vmod != None) {
        لكل (صحيح i = 0; i < Xkb_اڠک_Virtual_Mods; ++i) {
            إذا (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                اكسر;
            }
        }
    }

    أرجع mod_mask;
}
#endif

ساكن unsigned X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    unsigned صحيح mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    unsigned صحيح n = xmods->max_keypermod;
    لكل (صحيح i = 3; i < 8; i++) {
        لكل (صحيح j = 0; j < n; j++) {
            ثابت کونچي_Code_2 kc = xmods->modifiermap[i * n + j];
            إذا (videodata->keyboard.کونچي_layout[kc] == scancode) {
                mod_mask = 1 << i;
                اكسر;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    أرجع mod_mask;
}

ساكن فراغ X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, کونچي_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_کونچي_Code_From_کونچي_Sym(xkeysym, xkeycode, sdl_mod_mask);

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
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            اكسر;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

فراغ X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (data->keyboard.xkb_enabled) {
        XkbStateRec state;

        لكل (unsigned صحيح i = 0; i < Xkb_اڠک_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = عدم;
        }

        X11_XkbGetNames(data->display, XkbVirtualModNamesMask, data->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(data->display, XkbAllClientInfoMask | XkbVirtualModsMask, data->keyboard.xkb.desc_ptr);

        إذا (X11_XkbGetState(data->display, XkbUseCoreKbd, &state) == Success) {
            data->keyboard.xkb.current_group = state.group;
        }

        data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        إذا (!data->keyboard.alt_mask) {
            data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        data->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        data->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        data->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        data->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        data->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        لكل (unsigned صحيح i = 0; i < Xkb_اڠک_Kbd_Groups; ++i) {
            data->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            إذا (!data->keyboard.xkb.keymaps[i]) {
                لكل (unsigned صحيح j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
                    data->keyboard.xkb.keymaps[j] = عدم;
                }

                أرجع;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ثابت Uint32 valid_mod_mask = ShiftMask | LockMask | data->keyboard.alt_mask | data->keyboard.level3_mask | data->keyboard.level5_mask;

        لكل (Uint32 xkeycode = data->keyboard.xkb.desc_ptr->min_کونچي_code; xkeycode < data->keyboard.xkb.desc_ptr->max_کونچي_code; ++xkeycode) {
            ثابت SDL_Scancode scancode = data->keyboard.کونچي_layout[xkeycode];
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                استمر;
            }

            لكل (Uint32 group = 0; group < Xkb_اڠک_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = data->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                ثابت unsigned حرف max_کونچي_group = Xkb_کونچي_اڠک_Groups(data->keyboard.xkb.desc_ptr, xkeycode);
                ثابت unsigned حرف کونچي_group_info = Xkb_کونچي_Group_Info(data->keyboard.xkb.desc_ptr, xkeycode);

                إذا (max_کونچي_group && effective_group >= max_کونچي_group) {
                    ثابت unsigned حرف action = XkbOutOfRangeGroupAction(کونچي_group_info);

                    بدل (action) {
                    افتراضي:
                        effective_group %= max_کونچي_group;
                        اكسر;
                    حالة XkbClampIntoRange:
                        effective_group = max_کونچي_group - 1;
                        اكسر;
                    حالة XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_نومبور(کونچي_group_info);
                        إذا (effective_group >= max_کونچي_group) {
                            effective_group = 0;
                        }
                        اكسر;
                    }
                }

                Xkb_کونچي_Type_Ptr کونچي_type = Xkb_کونچي_کونچي_Type(data->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                لكل (Uint32 level = 0; level < کونچي_type->اڠک_levels; ++level) {
                    ثابت کونچي_Sym keysym = X11_کونچي_Code_To_Sym(_this, xkeycode, effective_group, level);

                    إذا (keysym != No_سيمبول) {
                        bool کونچي_added = false;

                        لكل (صحيح map_idx = 0; map_idx < کونچي_type->map_کيراءن; ++map_idx) {
                            إذا (کونچي_type->map[map_idx].active && کونچي_type->map[map_idx].level == level) {
                                ثابت unsigned صحيح xkb_mod_mask = کونچي_type->map[map_idx].mods.mask;
                                إذا ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    ثابت SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & data->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    کونچي_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        إذا (!level && !کونچي_added) {
                            X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_SetKeymap(data->keyboard.xkb.keymaps[data->keyboard.xkb.current_group], send_event);
    } وإلا
#endif
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        إذا (!keymap) {
            أرجع;
        }

        إذا (send_event) {
            إذا (data->keyboard.core.keysym_map) {
                X11_XFree(data->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
            data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                                     data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                                     &data->keyboard.core.keysyms_per_کونچي);
        }

        لكل (Uint32 xkeycode = data->keyboard.core.min_keycode; xkeycode <= data->keyboard.core.max_keycode; ++xkeycode) {
            ثابت SDL_Scancode scancode = data->keyboard.کونچي_layout[xkeycode];
            إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                استمر;
            }

            ثابت کونچي_Sym keysym = X11_کونچي_Code_To_Sym(_this, xkeycode, 0, 0);
            إذا (keysym != No_سيمبول) {
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

فراغ X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

#ifdef X_HAVE_UTF8_STRING
    إذا (data->im) {
        X11_XCloseIM(data->im);
        data->im = عدم;
    } وإلا {
        X11_XUnregisterIMInstantiateCallback(data->display, عدم, عدم, عدم, im_instantiate_handler, (XPointer)data);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    إذا (data->keyboard.xkb_enabled) {
        لكل (صحيح i = 0; i < Xkb_اڠک_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = عدم;
        }

        إذا (data->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(data->keyboard.xkb.desc_ptr, 0, True);
            data->keyboard.xkb.desc_ptr = عدم;
        }
    } وإلا
#endif
        إذا (data->keyboard.core.keysym_map) {
        X11_XFree(data->keyboard.core.keysym_map);
        data->keyboard.core.keysym_map = عدم;
    }
}

فراغ X11_ClearComposition(SDL_WindowData *data)
{
    إذا (data->preedit_length > 0) {
        data->preedit_text[0] = '\0';
        data->preedit_length = 0;
    }

    إذا (data->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        data->ime_needs_clear_composition = false;
    }
}

ساكن فراغ X11_SendEditingEvent(SDL_WindowData *data)
{
    إذا (data->preedit_length == 0) {
        X11_ClearComposition(data);
        أرجع;
    }

    bool in_highlight = false;
    صحيح start = -1, length = 0, i;
    لكل (i = 0; i < data->preedit_length; ++i) {
        إذا (data->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            إذا (start < 0) {
                start = i;
                in_highlight = true;
            }
        } وإلا إذا (in_highlight) {
            // Found the end of the highlight
            اكسر;
        }
    }
    إذا (in_highlight) {
        length = (i - start);
    } وإلا {
        start = SDL_clamp(data->preedit_cursor, 0, data->preedit_length);
    }
    SDL_SendEditingText(data->preedit_text, start, length);

    data->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
ساكن صحيح preedit_start_callback(XIC xic, XPointer client_data, XPointer call_data)
{
    // No limit on preedit text length
    أرجع -1;
}

ساكن فراغ preedit_done_callback(XIC xic, XPointer client_data, XPointer call_data)
{
}

ساكن فراغ preedit_draw_callback(XIC xic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;
    صحيح chg_first = SDL_clamp(call_data->chg_first, 0, data->preedit_length);
    صحيح chg_length = SDL_clamp(call_data->chg_length, 0, data->preedit_length - chg_first);

    ثابت حرف *start = data->preedit_text;
    إذا (chg_length > 0) {
        // Delete text in range
        لكل (صحيح i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, عدم);
        }

        ثابت حرف *end = start;
        لكل (صحيح i = 0; end && *end && i < chg_length; ++i) {
            SDL_StepUTF8(&end, عدم);
        }

        إذا (end > start) {
            SDL_memmove((حرف *)start, end, SDL_strlen(end) + 1);
            إذا ((chg_first + chg_length) > data->preedit_length) {
                SDL_memmove(&data->preedit_feedback[chg_first], &data->preedit_feedback[chg_first + chg_length], (data->preedit_length - chg_first - chg_length) * حجم(*data->preedit_feedback));
            }
        }
        data->preedit_length -= chg_length;
    }

    XIMText *text = call_data->text;
    إذا (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        إذا (text->string.multi_byte) {
            text->length = SDL_utf8strlen(text->string.multi_byte);
        }

        size_t string_size = SDL_strlen(text->string.multi_byte);
        size_t size = string_size + 1;
        إذا (data->preedit_text) {
            size += SDL_strlen(data->preedit_text);
        }
        حرف *preedit_text = (حرف *)SDL_malloc(size * حجم(*preedit_text));
        إذا (preedit_text) {
            size_t pre_size = (start - data->preedit_text);
            size_t post_size = start ? SDL_strlen(start) : 0;
            إذا (pre_size > 0) {
                SDL_memcpy(&preedit_text[0], data->preedit_text, pre_size);
            }
            SDL_memcpy(&preedit_text[pre_size], text->string.multi_byte, string_size);
            إذا (post_size > 0) {
                SDL_memcpy(&preedit_text[pre_size + string_size], start, post_size);
            }
            preedit_text[size - 1] = '\0';
        }

        size_t feedback_size = data->preedit_length + text->length;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_size * حجم(*feedback));
        إذا (feedback) {
            size_t pre_size = (size_t)chg_first;
            size_t post_size = (size_t)data->preedit_length - pre_size;
            إذا (pre_size > 0) {
                SDL_memcpy(&feedback[0], data->preedit_feedback, pre_size * حجم(*feedback));
            }
            SDL_memcpy(&feedback[pre_size], text->feedback, text->length * حجم(*feedback));
            إذا (post_size > 0) {
                SDL_memcpy(&feedback[pre_size + text->length], &data->preedit_feedback[pre_size], post_size * حجم(*feedback));
            }
        }

        إذا (preedit_text && feedback) {
            SDL_free(data->preedit_text);
            data->preedit_text = preedit_text;

            SDL_free(data->preedit_feedback);
            data->preedit_feedback = feedback;

            data->preedit_length += text->length;
        } وإلا {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    data->preedit_cursor = call_data->caret;

#ifdef DEBUG_XIM
    إذا (call_data->chg_length > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_data->chg_length, call_data->chg_first);
    }
    إذا (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_data->chg_first, call_data->caret);
    }
    SDL_Log("Pre-edit text: %s", data->preedit_text);
#endif

    X11_SendEditingEvent(data);
}

ساكن فراغ preedit_caret_callback(XIC xic, XPointer client_data, XIMPreeditCaretCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;

    بدل (call_data->direction) {
    حالة XIMAbsolutePosition:
        إذا (call_data->position != data->preedit_cursor) {
            data->preedit_cursor = call_data->position;
            X11_SendEditingEvent(data);
        }
        اكسر;
    حالة XIMDontChange:
        اكسر;
    افتراضي:
        // Not currently supported
        اكسر;
    }
}

ساكن فراغ ic_destroyed_handler(XIC ic, XPointer clientData, XPointer callData)
{
    SDL_WindowData *data = (SDL_WindowData *)clientData;
    data->ic = عدم;
    X11_Destroy_ماسوقن_Context(data);

    // If the IM was already recreated, create a new IC.
    إذا (data->videodata->im) {
        X11_Create_ماسوقن_Context(data);
    }
}
#endif // X_HAVE_UTF8_STRING

فراغ X11_Create_ماسوقن_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_VideoData *videodata = data->videodata;

    إذا (SDL_X11_HAVE_UTF8 && videodata->im) {
        ثابت حرف *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)data;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        إذا (hint && SDL_strstr(hint, "composition")) {
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
                                                         عدم);
            إذا (attr) {
                data->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, data->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         عدم);
                X11_XFree(attr);
            }
        }
        إذا (!data->ic) {
            data->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClientWindow, data->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     عدم);
        }
        data->xim_spot.x = -1;
        data->xim_spot.y = -1;
    }
#endif // X_HAVE_UTF8_STRING
}


فراغ X11_Destroy_ماسوقن_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    إذا (data->ic) {
        X11_XDestroyIC(data->ic);
        data->ic = عدم;
    }
    SDL_free(data->preedit_text);
    SDL_free(data->preedit_feedback);
    data->preedit_text = عدم;
    data->preedit_feedback = عدم;
#endif
}

ساكن فراغ X11_ResetXIM(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    إذا (data && data->ic) {
        // Clear any partially entered dead keys
        حرف *contents = X11_Xutf8ResetIC(data->ic);
        إذا (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_ماسوقن(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    أرجع X11_Update_Text_ماسوقن_Area(_this, window);
}

bool X11_Stop_Text_ماسوقن(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    أرجع true;
}

bool X11_Update_Text_ماسوقن_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    إذا (data && data->ic) {
        XPoint spot;
        spot.x = window->text_ماسوقن_rect.x + window->text_ماسوقن_cursor;
        spot.y = window->text_ماسوقن_rect.y + window->text_ماسوقن_rect.h;
        إذا (spot.x != data->xim_spot.x || spot.y != data->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, عدم);
            إذا (attr) {
                X11_XSetICValues(data->ic, XNPreeditAttributes, attr, عدم);
                X11_XFree(attr);
            }
            SDL_copyp(&data->xim_spot, &spot);
        }
    }
#endif
    أرجع true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    أرجع videodata->use_steam_screen_keyboard;
}

فراغ X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;

    إذا (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ثابت صحيح k_EFloating_Gamepad_Text_ماسوقن_Mode_Mode_Single_باريس = 0;    // Enter dismisses the keyboard
        ثابت صحيح k_EFloating_Gamepad_Text_ماسوقن_Mode_Mode_Multiple_باريس_سموا = 1; // User needs to explicitly dismiss the keyboard
        ثابت صحيح k_EFloating_Gamepad_Text_ماسوقن_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ثابت صحيح k_EFloating_Gamepad_Text_ماسوقن_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        حرف deeplink[128];
        صحيح mode;

        بدل (SDL_Get_Text_ماسوقن_Type(props)) {
        حالة SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_ماسوقن_Mode_Mode_Email;
            اكسر;
        حالة SDL_TEXTINPUT_TYPE_نومبور:
        حالة SDL_TEXTINPUT_TYPE_نومبور_PASSWORD_HIDDEN:
        حالة SDL_TEXTINPUT_TYPE_نومبور_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_ماسوقن_Mode_Mode_Numeric;
            اكسر;
        افتراضي:
            إذا (SDL_Get_Text_ماسوقن_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_ماسوقن_Mode_Mode_Multiple_باريس_سموا;
            } وإلا {
                mode = k_EFloating_Gamepad_Text_ماسوقن_Mode_Mode_Single_باريس;
            }
            اكسر;
        }
        (فراغ)SDL_snprintf(deeplink, حجم(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_ماسوقن_rect.x, window->text_ماسوقن_rect.y,
                           window->text_ماسوقن_rect.w, window->text_ماسوقن_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

فراغ X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;

    إذا (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
