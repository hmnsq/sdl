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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#અન્તર્ભાવ "SDL_x11video.h"

#અન્તર્ભાવ "../../events/SDL_keyboard_c.h"
#અન્તર્ભાવ "../../events/SDL_scancode_tables_c.h"

#અન્તર્ભાવ <X11/keysym.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#અન્તર્ભાવ <X11/XKBlib.h>
#endif

#અન્તર્ભાવ "../../events/imKStoUCS.h"
#અન્તર્ભાવ "../../events/SDL_keysym_to_scancode_c.h"
#અન્તર્ભાવ "../../events/SDL_keysym_to_keycode_c.h"

#ifdef X_HAVE_UTF8_STRING
#અન્તર્ભાવ <locale.h>
#endif

સ્થિર SDL_ScancodeTable scancode_set[] = {
    SDL_SCANCODE_TABLE_DARWIN,
    SDL_SCANCODE_TABLE_XFREE86_1,
    SDL_SCANCODE_TABLE_XFREE86_2,
    SDL_SCANCODE_TABLE_XVNC,
};

સ્થિર bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    પસંદગી (scancode) {
    સ્થિતિ SDL_SCANCODE_ESCAPE:
    સ્થિતિ SDL_SCANCODE_CAPSLOCK:
    સ્થિતિ SDL_SCANCODE_NUMLOCKCLEAR:
    સ્થિતિ SDL_SCANCODE_LSHIFT:
    સ્થિતિ SDL_SCANCODE_RSHIFT:
    સ્થિતિ SDL_SCANCODE_LCTRL:
    સ્થિતિ SDL_SCANCODE_RCTRL:
    સ્થિતિ SDL_SCANCODE_LALT:
    સ્થિતિ SDL_SCANCODE_RALT:
    સ્થિતિ SDL_SCANCODE_LGUI:
    સ્થિતિ SDL_SCANCODE_RGUI:
        પાછા false;
    મૂળભૂત:
        પાછા true;
    }
}

સ્થિર ચાવી_Sym X11_ચાવી_Code_To_Sym(SDL_VideoDevice *_this, ચાવી_Code_2 keycode, unsigned પૂર્ણાંક group, unsigned પૂર્ણાંક level)
{
    SDL_VideoData *data = _this->internal;
    ચાવી_Sym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    જો (data->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(data->display, keycode, group, level);
    } નહીંતર
#endif
    {
        // TODO: Handle groups on the legacy path.
        જો (keycode >= data->keyboard.core.min_keycode && keycode <= data->keyboard.core.max_keycode) {
            keysym = data->keyboard.core.keysym_map[(keycode - data->keyboard.core.min_keycode) * data->keyboard.core.keysyms_per_ચાવી];
        } નહીંતર {
            keysym = No_પ્રતીક;
        }
    }

    પાછા keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
સ્થિર SDL_Scancode X11_ચાવી_Code_To_SDLScancode(SDL_VideoDevice *_this, ચાવી_Code_2 keycode)
{
    અચલ ચાવી_Sym keysym = X11_ચાવી_Code_To_Sym(_this, keycode, 0, 0);

    જો (keysym == No_પ્રતીક) {
        પાછા SDL_SCANCODE_UNKNOWN;
    }

    પાછા SDL_Get_Scancode_From_ચાવી_Sym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
સ્થિર bool X11_InitIM(SDL_VideoData *videodata);

સ્થિર શૂન્ય im_instantiate_handler(Display *display, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    જો (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, ખાલી, ખાલી, ખાલી, im_instantiate_handler, clientData);
    }
}

સ્થિર શૂન્ય im_destroyed_handler(XIM im, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    videodata->im = ખાલી;
    X11_XRegisterIMInstantiateCallback(videodata->display, ખાલી, ખાલી, ખાલી, im_instantiate_handler, clientData);
}

સ્થિર bool X11_InitIM(SDL_VideoData *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    અક્ષર *prev_locale = setlocale(LC_ALL, ખાલી);
    અક્ષર *prev_xmods = X11_XSetLocaleModifiers(ખાલી);

    જો (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    જો (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (શૂન્ય)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, ખાલી, ખાલી, ખાલી);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (શૂન્ય)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    જો (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (અક્ષર *)ખાલી);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        માટે (પૂર્ણાંક i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *w = videodata->windowlist[i];
            જો (!w->ic) {
                X11_Create_આગત_Context(w);
            }
        }

        પાછા true;
    }

    પાછા false;
}
#endif // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    પૂર્ણાંક i = 0;
    પૂર્ણાંક j = 0;
    પૂર્ણાંક min_keycode, max_keycode;
    સંરચના
    {
        SDL_Scancode scancode;
        ચાવી_Sym keysym;
        પૂર્ણાંક કિંમત;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_ડાબું, XK_ડાબું, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    પૂર્ણાંક best_distance;
    પૂર્ણાંક best_index;
    પૂર્ણાંક distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    પૂર્ણાંક xkb_major = XkbMajorVersion;
    પૂર્ણાંક xkb_minor = XkbMinorVersion;

    જો (X11_XkbQueryExtension(data->display, ખાલી, &data->keyboard.xkb.event, ખાલી, &xkb_major, &xkb_minor)) {
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
    } નહીંતર
#endif
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
        data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                              data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                              &data->keyboard.core.keysyms_per_ચાવી);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    જો (SDL_X11_HAVE_UTF8) {
        જો (!X11_InitIM(data)) {
            X11_XRegisterIMInstantiateCallback(data->display, ખાલી, ખાલી, ખાલી, im_instantiate_handler, (XPointer)data);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_index = -1;
    X11_XDisplayKeycodes(data->display, &min_keycode, &max_keycode);
    માટે (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].કિંમત = X11_XKeysymToKeycode(data->display, fingerprint[i].keysym) - min_keycode;
    }
    માટે (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        પૂર્ણાંક table_size;
        અચલ SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_size);

        distance = 0;
        માટે (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            જો (fingerprint[j].કિંમત < 0 || fingerprint[j].કિંમત >= table_size) {
                distance += 1;
            } નહીંતર જો (table[fingerprint[j].કિંમત] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        જો (distance < best_distance) {
            best_distance = distance;
            best_index = i;
        }
    }
    જો (best_index < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        પૂર્ણાંક fingerprint_કિંમત = X11_XKeysymToKeycode(data->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        જો (fingerprint_કિંમત == 235) {
            માટે (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                જો (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_index = i;
                    best_distance = 0;
                    તોડો;
                }
            }
        }
    }
    જો (best_index >= 0 && best_distance <= 2) {
        પૂર્ણાંક table_size;
        અચલ SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_index], &table_size);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_index, min_keycode, max_keycode, table_size);
#endif
        // This should never happen, but just in case...
        જો (table_size > (SDL_arraysize(data->keyboard.ચાવી_layout) - min_keycode)) {
            table_size = (SDL_arraysize(data->keyboard.ચાવી_layout) - min_keycode);
        }
        SDL_memcpy(&data->keyboard.ચાવી_layout[min_keycode], table, કદ(SDL_Scancode) * table_size);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        માટે (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_ચાવી_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                ચાવી_Sym sym;
                sym = X11_ચાવી_Code_To_Sym(_this, (ચાવી_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned પૂર્ણાંક)sym, sym == No_પ્રતીક ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            જો (scancode == data->keyboard.ચાવી_layout[i]) {
                ચાલુ;
            }
            જો ((SDL_GetKeymapKeycode(ખાલી, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", data->ચાવી_layout[i], SDL_GetScancodeName(data->ચાવી_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                data->keyboard.ચાવી_layout[i] = scancode;
            }
        }
    } નહીંતર {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        માટે (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_ચાવી_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                ચાવી_Sym sym;
                sym = X11_ચાવી_Code_To_Sym(_this, (ચાવી_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned પૂર્ણાંક)sym, sym == No_પ્રતીક ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            જો (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } નહીંતર {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            data->keyboard.ચાવી_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    પાછા true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
સ્થિર unsigned પૂર્ણાંક X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, અચલ અક્ષર *vmod_name)
{
    SDL_VideoData *videodata = _this->internal;
    unsigned પૂર્ણાંક mod_mask = 0;

    અચલ Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    જો (vmod != None) {
        માટે (પૂર્ણાંક i = 0; i < Xkb_અંક_Virtual_Mods; ++i) {
            જો (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                તોડો;
            }
        }
    }

    પાછા mod_mask;
}
#endif

સ્થિર unsigned X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    unsigned પૂર્ણાંક mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    unsigned પૂર્ણાંક n = xmods->max_keypermod;
    માટે (પૂર્ણાંક i = 3; i < 8; i++) {
        માટે (પૂર્ણાંક j = 0; j < n; j++) {
            અચલ ચાવી_Code_2 kc = xmods->modifiermap[i * n + j];
            જો (videodata->keyboard.ચાવી_layout[kc] == scancode) {
                mod_mask = 1 << i;
                તોડો;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    પાછા mod_mask;
}

સ્થિર શૂન્ય X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, ચાવી_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_ચાવી_Code_From_ચાવી_Sym(xkeysym, xkeycode, sdl_mod_mask);

    જો (!keycode) {
        પસંદગી (sdl_scancode) {
        સ્થિતિ SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            તોડો;
        સ્થિતિ SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            તોડો;
        સ્થિતિ SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            તોડો;
        સ્થિતિ SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            તોડો;
        મૂળભૂત:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            તોડો;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

શૂન્ય X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    જો (data->keyboard.xkb_enabled) {
        XkbStateRec state;

        માટે (unsigned પૂર્ણાંક i = 0; i < Xkb_અંક_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = ખાલી;
        }

        X11_XkbGetNames(data->display, XkbVirtualModNamesMask, data->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(data->display, XkbAllClientInfoMask | XkbVirtualModsMask, data->keyboard.xkb.desc_ptr);

        જો (X11_XkbGetState(data->display, XkbUseCoreKbd, &state) == Success) {
            data->keyboard.xkb.current_group = state.group;
        }

        data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        જો (!data->keyboard.alt_mask) {
            data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        data->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        data->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        data->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        data->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        data->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        માટે (unsigned પૂર્ણાંક i = 0; i < Xkb_અંક_Kbd_Groups; ++i) {
            data->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            જો (!data->keyboard.xkb.keymaps[i]) {
                માટે (unsigned પૂર્ણાંક j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
                    data->keyboard.xkb.keymaps[j] = ખાલી;
                }

                પાછા;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        અચલ Uint32 valid_mod_mask = ShiftMask | LockMask | data->keyboard.alt_mask | data->keyboard.level3_mask | data->keyboard.level5_mask;

        માટે (Uint32 xkeycode = data->keyboard.xkb.desc_ptr->min_ચાવી_code; xkeycode < data->keyboard.xkb.desc_ptr->max_ચાવી_code; ++xkeycode) {
            અચલ SDL_Scancode scancode = data->keyboard.ચાવી_layout[xkeycode];
            જો (scancode == SDL_SCANCODE_UNKNOWN) {
                ચાલુ;
            }

            માટે (Uint32 group = 0; group < Xkb_અંક_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = data->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                અચલ unsigned અક્ષર max_ચાવી_group = Xkb_ચાવી_અંક_Groups(data->keyboard.xkb.desc_ptr, xkeycode);
                અચલ unsigned અક્ષર ચાવી_group_info = Xkb_ચાવી_Group_Info(data->keyboard.xkb.desc_ptr, xkeycode);

                જો (max_ચાવી_group && effective_group >= max_ચાવી_group) {
                    અચલ unsigned અક્ષર action = XkbOutOfRangeGroupAction(ચાવી_group_info);

                    પસંદગી (action) {
                    મૂળભૂત:
                        effective_group %= max_ચાવી_group;
                        તોડો;
                    સ્થિતિ XkbClampIntoRange:
                        effective_group = max_ચાવી_group - 1;
                        તોડો;
                    સ્થિતિ XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_સંખ્યા(ચાવી_group_info);
                        જો (effective_group >= max_ચાવી_group) {
                            effective_group = 0;
                        }
                        તોડો;
                    }
                }

                Xkb_ચાવી_Type_Ptr ચાવી_type = Xkb_ચાવી_ચાવી_Type(data->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                માટે (Uint32 level = 0; level < ચાવી_type->અંક_levels; ++level) {
                    અચલ ચાવી_Sym keysym = X11_ચાવી_Code_To_Sym(_this, xkeycode, effective_group, level);

                    જો (keysym != No_પ્રતીક) {
                        bool ચાવી_added = false;

                        માટે (પૂર્ણાંક map_idx = 0; map_idx < ચાવી_type->map_ગણતરી; ++map_idx) {
                            જો (ચાવી_type->map[map_idx].active && ચાવી_type->map[map_idx].level == level) {
                                અચલ unsigned પૂર્ણાંક xkb_mod_mask = ચાવી_type->map[map_idx].mods.mask;
                                જો ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    અચલ SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & data->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    ચાવી_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        જો (!level && !ચાવી_added) {
                            X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_SetKeymap(data->keyboard.xkb.keymaps[data->keyboard.xkb.current_group], send_event);
    } નહીંતર
#endif
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        જો (!keymap) {
            પાછા;
        }

        જો (send_event) {
            જો (data->keyboard.core.keysym_map) {
                X11_XFree(data->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
            data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                                     data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                                     &data->keyboard.core.keysyms_per_ચાવી);
        }

        માટે (Uint32 xkeycode = data->keyboard.core.min_keycode; xkeycode <= data->keyboard.core.max_keycode; ++xkeycode) {
            અચલ SDL_Scancode scancode = data->keyboard.ચાવી_layout[xkeycode];
            જો (scancode == SDL_SCANCODE_UNKNOWN) {
                ચાલુ;
            }

            અચલ ચાવી_Sym keysym = X11_ચાવી_Code_To_Sym(_this, xkeycode, 0, 0);
            જો (keysym != No_પ્રતીક) {
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

શૂન્ય X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

#ifdef X_HAVE_UTF8_STRING
    જો (data->im) {
        X11_XCloseIM(data->im);
        data->im = ખાલી;
    } નહીંતર {
        X11_XUnregisterIMInstantiateCallback(data->display, ખાલી, ખાલી, ખાલી, im_instantiate_handler, (XPointer)data);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    જો (data->keyboard.xkb_enabled) {
        માટે (પૂર્ણાંક i = 0; i < Xkb_અંક_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = ખાલી;
        }

        જો (data->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(data->keyboard.xkb.desc_ptr, 0, True);
            data->keyboard.xkb.desc_ptr = ખાલી;
        }
    } નહીંતર
#endif
        જો (data->keyboard.core.keysym_map) {
        X11_XFree(data->keyboard.core.keysym_map);
        data->keyboard.core.keysym_map = ખાલી;
    }
}

શૂન્ય X11_ClearComposition(SDL_WindowData *data)
{
    જો (data->preedit_length > 0) {
        data->preedit_text[0] = '\0';
        data->preedit_length = 0;
    }

    જો (data->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        data->ime_needs_clear_composition = false;
    }
}

સ્થિર શૂન્ય X11_SendEditingEvent(SDL_WindowData *data)
{
    જો (data->preedit_length == 0) {
        X11_ClearComposition(data);
        પાછા;
    }

    bool in_highlight = false;
    પૂર્ણાંક start = -1, length = 0, i;
    માટે (i = 0; i < data->preedit_length; ++i) {
        જો (data->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            જો (start < 0) {
                start = i;
                in_highlight = true;
            }
        } નહીંતર જો (in_highlight) {
            // Found the end of the highlight
            તોડો;
        }
    }
    જો (in_highlight) {
        length = (i - start);
    } નહીંતર {
        start = SDL_clamp(data->preedit_cursor, 0, data->preedit_length);
    }
    SDL_SendEditingText(data->preedit_text, start, length);

    data->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
સ્થિર પૂર્ણાંક preedit_start_callback(XIC xic, XPointer client_data, XPointer call_data)
{
    // No limit on preedit text length
    પાછા -1;
}

સ્થિર શૂન્ય preedit_done_callback(XIC xic, XPointer client_data, XPointer call_data)
{
}

સ્થિર શૂન્ય preedit_draw_callback(XIC xic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;
    પૂર્ણાંક chg_first = SDL_clamp(call_data->chg_first, 0, data->preedit_length);
    પૂર્ણાંક chg_length = SDL_clamp(call_data->chg_length, 0, data->preedit_length - chg_first);

    અચલ અક્ષર *start = data->preedit_text;
    જો (chg_length > 0) {
        // Delete text in range
        માટે (પૂર્ણાંક i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, ખાલી);
        }

        અચલ અક્ષર *end = start;
        માટે (પૂર્ણાંક i = 0; end && *end && i < chg_length; ++i) {
            SDL_StepUTF8(&end, ખાલી);
        }

        જો (end > start) {
            SDL_memmove((અક્ષર *)start, end, SDL_strlen(end) + 1);
            જો ((chg_first + chg_length) > data->preedit_length) {
                SDL_memmove(&data->preedit_feedback[chg_first], &data->preedit_feedback[chg_first + chg_length], (data->preedit_length - chg_first - chg_length) * કદ(*data->preedit_feedback));
            }
        }
        data->preedit_length -= chg_length;
    }

    XIMText *text = call_data->text;
    જો (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        જો (text->string.multi_byte) {
            text->length = SDL_utf8strlen(text->string.multi_byte);
        }

        size_t string_size = SDL_strlen(text->string.multi_byte);
        size_t size = string_size + 1;
        જો (data->preedit_text) {
            size += SDL_strlen(data->preedit_text);
        }
        અક્ષર *preedit_text = (અક્ષર *)SDL_malloc(size * કદ(*preedit_text));
        જો (preedit_text) {
            size_t pre_size = (start - data->preedit_text);
            size_t post_size = start ? SDL_strlen(start) : 0;
            જો (pre_size > 0) {
                SDL_memcpy(&preedit_text[0], data->preedit_text, pre_size);
            }
            SDL_memcpy(&preedit_text[pre_size], text->string.multi_byte, string_size);
            જો (post_size > 0) {
                SDL_memcpy(&preedit_text[pre_size + string_size], start, post_size);
            }
            preedit_text[size - 1] = '\0';
        }

        size_t feedback_size = data->preedit_length + text->length;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_size * કદ(*feedback));
        જો (feedback) {
            size_t pre_size = (size_t)chg_first;
            size_t post_size = (size_t)data->preedit_length - pre_size;
            જો (pre_size > 0) {
                SDL_memcpy(&feedback[0], data->preedit_feedback, pre_size * કદ(*feedback));
            }
            SDL_memcpy(&feedback[pre_size], text->feedback, text->length * કદ(*feedback));
            જો (post_size > 0) {
                SDL_memcpy(&feedback[pre_size + text->length], &data->preedit_feedback[pre_size], post_size * કદ(*feedback));
            }
        }

        જો (preedit_text && feedback) {
            SDL_free(data->preedit_text);
            data->preedit_text = preedit_text;

            SDL_free(data->preedit_feedback);
            data->preedit_feedback = feedback;

            data->preedit_length += text->length;
        } નહીંતર {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    data->preedit_cursor = call_data->caret;

#ifdef DEBUG_XIM
    જો (call_data->chg_length > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_data->chg_length, call_data->chg_first);
    }
    જો (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_data->chg_first, call_data->caret);
    }
    SDL_Log("Pre-edit text: %s", data->preedit_text);
#endif

    X11_SendEditingEvent(data);
}

સ્થિર શૂન્ય preedit_caret_callback(XIC xic, XPointer client_data, XIMPreeditCaretCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;

    પસંદગી (call_data->direction) {
    સ્થિતિ XIMAbsolutePosition:
        જો (call_data->position != data->preedit_cursor) {
            data->preedit_cursor = call_data->position;
            X11_SendEditingEvent(data);
        }
        તોડો;
    સ્થિતિ XIMDontChange:
        તોડો;
    મૂળભૂત:
        // Not currently supported
        તોડો;
    }
}

સ્થિર શૂન્ય ic_destroyed_handler(XIC ic, XPointer clientData, XPointer callData)
{
    SDL_WindowData *data = (SDL_WindowData *)clientData;
    data->ic = ખાલી;
    X11_Destroy_આગત_Context(data);

    // If the IM was already recreated, create a new IC.
    જો (data->videodata->im) {
        X11_Create_આગત_Context(data);
    }
}
#endif // X_HAVE_UTF8_STRING

શૂન્ય X11_Create_આગત_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_VideoData *videodata = data->videodata;

    જો (SDL_X11_HAVE_UTF8 && videodata->im) {
        અચલ અક્ષર *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)data;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        જો (hint && SDL_strstr(hint, "composition")) {
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
                                                         ખાલી);
            જો (attr) {
                data->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, data->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         ખાલી);
                X11_XFree(attr);
            }
        }
        જો (!data->ic) {
            data->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClientWindow, data->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     ખાલી);
        }
        data->xim_spot.x = -1;
        data->xim_spot.y = -1;
    }
#endif // X_HAVE_UTF8_STRING
}


શૂન્ય X11_Destroy_આગત_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    જો (data->ic) {
        X11_XDestroyIC(data->ic);
        data->ic = ખાલી;
    }
    SDL_free(data->preedit_text);
    SDL_free(data->preedit_feedback);
    data->preedit_text = ખાલી;
    data->preedit_feedback = ખાલી;
#endif
}

સ્થિર શૂન્ય X11_ResetXIM(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    જો (data && data->ic) {
        // Clear any partially entered dead keys
        અક્ષર *contents = X11_Xutf8ResetIC(data->ic);
        જો (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_આગત(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    પાછા X11_Update_Text_આગત_Area(_this, window);
}

bool X11_Stop_Text_આગત(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    પાછા true;
}

bool X11_Update_Text_આગત_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    જો (data && data->ic) {
        XPoint spot;
        spot.x = window->text_આગત_rect.x + window->text_આગત_cursor;
        spot.y = window->text_આગત_rect.y + window->text_આગત_rect.h;
        જો (spot.x != data->xim_spot.x || spot.y != data->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, ખાલી);
            જો (attr) {
                X11_XSetICValues(data->ic, XNPreeditAttributes, attr, ખાલી);
                X11_XFree(attr);
            }
            SDL_copyp(&data->xim_spot, &spot);
        }
    }
#endif
    પાછા true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    પાછા videodata->use_steam_screen_keyboard;
}

શૂન્ય X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;

    જો (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        અચલ પૂર્ણાંક k_EFloating_Gamepad_Text_આગત_Mode_Mode_Single_લીટી = 0;    // Enter dismisses the keyboard
        અચલ પૂર્ણાંક k_EFloating_Gamepad_Text_આગત_Mode_Mode_Multiple_લીટીઓ = 1; // User needs to explicitly dismiss the keyboard
        અચલ પૂર્ણાંક k_EFloating_Gamepad_Text_આગત_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        અચલ પૂર્ણાંક k_EFloating_Gamepad_Text_આગત_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        અક્ષર deeplink[128];
        પૂર્ણાંક mode;

        પસંદગી (SDL_Get_Text_આગત_Type(props)) {
        સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_આગત_Mode_Mode_Email;
            તોડો;
        સ્થિતિ SDL_TEXTINPUT_TYPE_સંખ્યા:
        સ્થિતિ SDL_TEXTINPUT_TYPE_સંખ્યા_PASSWORD_HIDDEN:
        સ્થિતિ SDL_TEXTINPUT_TYPE_સંખ્યા_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_આગત_Mode_Mode_Numeric;
            તોડો;
        મૂળભૂત:
            જો (SDL_Get_Text_આગત_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_આગત_Mode_Mode_Multiple_લીટીઓ;
            } નહીંતર {
                mode = k_EFloating_Gamepad_Text_આગત_Mode_Mode_Single_લીટી;
            }
            તોડો;
        }
        (શૂન્ય)SDL_snprintf(deeplink, કદ(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_આગત_rect.x, window->text_આગત_rect.y,
                           window->text_આગત_rect.w, window->text_આગત_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

શૂન્ય X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;

    જો (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
