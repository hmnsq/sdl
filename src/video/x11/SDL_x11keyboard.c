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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#അന്തര്ഭാവ "SDL_x11video.h"

#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"
#അന്തര്ഭാവ "../../events/SDL_scancode_tables_c.h"

#അന്തര്ഭാവ <X11/keysym.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#അന്തര്ഭാവ <X11/XKBlib.h>
#endif

#അന്തര്ഭാവ "../../events/imKStoUCS.h"
#അന്തര്ഭാവ "../../events/SDL_keysym_to_scancode_c.h"
#അന്തര്ഭാവ "../../events/SDL_keysym_to_keycode_c.h"

#ifdef X_HAVE_UTF8_STRING
#അന്തര്ഭാവ <locale.h>
#endif

സ്ഥിതം SDL_ScancodeTable scancode_set[] = {
    SDL_SCANCODE_TABLE_DARWIN,
    SDL_SCANCODE_TABLE_XFREE86_1,
    SDL_SCANCODE_TABLE_XFREE86_2,
    SDL_SCANCODE_TABLE_XVNC,
};

സ്ഥിതം bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    തിരഞ്ഞെടുപ്പ് (scancode) {
    അവസ്ഥ SDL_SCANCODE_ESCAPE:
    അവസ്ഥ SDL_SCANCODE_CAPSLOCK:
    അവസ്ഥ SDL_SCANCODE_NUMLOCKCLEAR:
    അവസ്ഥ SDL_SCANCODE_LSHIFT:
    അവസ്ഥ SDL_SCANCODE_RSHIFT:
    അവസ്ഥ SDL_SCANCODE_LCTRL:
    അവസ്ഥ SDL_SCANCODE_RCTRL:
    അവസ്ഥ SDL_SCANCODE_LALT:
    അവസ്ഥ SDL_SCANCODE_RALT:
    അവസ്ഥ SDL_SCANCODE_LGUI:
    അവസ്ഥ SDL_SCANCODE_RGUI:
        തിരികെ false;
    സ്ഥിരസ്ഥിതി:
        തിരികെ true;
    }
}

സ്ഥിതം താക്കോൽ_Sym X11_താക്കോൽ_Code_To_Sym(SDL_VideoDevice *_this, താക്കോൽ_Code_2 keycode, unsigned പൂർണ്ണസംഖ്യ group, unsigned പൂർണ്ണസംഖ്യ level)
{
    SDL_VideoData *data = _this->internal;
    താക്കോൽ_Sym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    എങ്കിൽ (data->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(data->display, keycode, group, level);
    } അല്ലെങ്കിൽ
#endif
    {
        // TODO: Handle groups on the legacy path.
        എങ്കിൽ (keycode >= data->keyboard.core.min_keycode && keycode <= data->keyboard.core.max_keycode) {
            keysym = data->keyboard.core.keysym_map[(keycode - data->keyboard.core.min_keycode) * data->keyboard.core.keysyms_per_താക്കോൽ];
        } അല്ലെങ്കിൽ {
            keysym = No_ചിഹ്നം;
        }
    }

    തിരികെ keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
സ്ഥിതം SDL_Scancode X11_താക്കോൽ_Code_To_SDLScancode(SDL_VideoDevice *_this, താക്കോൽ_Code_2 keycode)
{
    സ്ഥിരം താക്കോൽ_Sym keysym = X11_താക്കോൽ_Code_To_Sym(_this, keycode, 0, 0);

    എങ്കിൽ (keysym == No_ചിഹ്നം) {
        തിരികെ SDL_SCANCODE_UNKNOWN;
    }

    തിരികെ SDL_Get_Scancode_From_താക്കോൽ_Sym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
സ്ഥിതം bool X11_InitIM(SDL_VideoData *videodata);

സ്ഥിതം ശൂന്യം im_instantiate_handler(Display *display, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    എങ്കിൽ (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, ശൂന്യ, ശൂന്യ, ശൂന്യ, im_instantiate_handler, clientData);
    }
}

സ്ഥിതം ശൂന്യം im_destroyed_handler(XIM im, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    videodata->im = ശൂന്യ;
    X11_XRegisterIMInstantiateCallback(videodata->display, ശൂന്യ, ശൂന്യ, ശൂന്യ, im_instantiate_handler, clientData);
}

സ്ഥിതം bool X11_InitIM(SDL_VideoData *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    അക്ഷരം *prev_locale = setlocale(LC_ALL, ശൂന്യ);
    അക്ഷരം *prev_xmods = X11_XSetLocaleModifiers(ശൂന്യ);

    എങ്കിൽ (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    എങ്കിൽ (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (ശൂന്യം)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, ശൂന്യ, ശൂന്യ, ശൂന്യ);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (ശൂന്യം)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    എങ്കിൽ (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (അക്ഷരം *)ശൂന്യ);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *w = videodata->windowlist[i];
            എങ്കിൽ (!w->ic) {
                X11_Create_നിവേശം_Context(w);
            }
        }

        തിരികെ true;
    }

    തിരികെ false;
}
#endif // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    പൂർണ്ണസംഖ്യ i = 0;
    പൂർണ്ണസംഖ്യ j = 0;
    പൂർണ്ണസംഖ്യ min_keycode, max_keycode;
    ഘടന
    {
        SDL_Scancode scancode;
        താക്കോൽ_Sym keysym;
        പൂർണ്ണസംഖ്യ മൂല്യം;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_ഇടത്, XK_ഇടത്, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    പൂർണ്ണസംഖ്യ best_distance;
    പൂർണ്ണസംഖ്യ best_index;
    പൂർണ്ണസംഖ്യ distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    പൂർണ്ണസംഖ്യ xkb_major = XkbMajorVersion;
    പൂർണ്ണസംഖ്യ xkb_minor = XkbMinorVersion;

    എങ്കിൽ (X11_XkbQueryExtension(data->display, ശൂന്യ, &data->keyboard.xkb.event, ശൂന്യ, &xkb_major, &xkb_minor)) {
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
    } അല്ലെങ്കിൽ
#endif
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
        data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                              data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                              &data->keyboard.core.keysyms_per_താക്കോൽ);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    എങ്കിൽ (SDL_X11_HAVE_UTF8) {
        എങ്കിൽ (!X11_InitIM(data)) {
            X11_XRegisterIMInstantiateCallback(data->display, ശൂന്യ, ശൂന്യ, ശൂന്യ, im_instantiate_handler, (XPointer)data);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_index = -1;
    X11_XDisplayKeycodes(data->display, &min_keycode, &max_keycode);
    വേണ്ടി (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].മൂല്യം = X11_XKeysymToKeycode(data->display, fingerprint[i].keysym) - min_keycode;
    }
    വേണ്ടി (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        പൂർണ്ണസംഖ്യ table_size;
        സ്ഥിരം SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_size);

        distance = 0;
        വേണ്ടി (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            എങ്കിൽ (fingerprint[j].മൂല്യം < 0 || fingerprint[j].മൂല്യം >= table_size) {
                distance += 1;
            } അല്ലെങ്കിൽ എങ്കിൽ (table[fingerprint[j].മൂല്യം] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        എങ്കിൽ (distance < best_distance) {
            best_distance = distance;
            best_index = i;
        }
    }
    എങ്കിൽ (best_index < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        പൂർണ്ണസംഖ്യ fingerprint_മൂല്യം = X11_XKeysymToKeycode(data->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        എങ്കിൽ (fingerprint_മൂല്യം == 235) {
            വേണ്ടി (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                എങ്കിൽ (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_index = i;
                    best_distance = 0;
                    നിർത്തുക;
                }
            }
        }
    }
    എങ്കിൽ (best_index >= 0 && best_distance <= 2) {
        പൂർണ്ണസംഖ്യ table_size;
        സ്ഥിരം SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_index], &table_size);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_index, min_keycode, max_keycode, table_size);
#endif
        // This should never happen, but just in case...
        എങ്കിൽ (table_size > (SDL_arraysize(data->keyboard.താക്കോൽ_layout) - min_keycode)) {
            table_size = (SDL_arraysize(data->keyboard.താക്കോൽ_layout) - min_keycode);
        }
        SDL_memcpy(&data->keyboard.താക്കോൽ_layout[min_keycode], table, വലുപ്പം(SDL_Scancode) * table_size);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        വേണ്ടി (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_താക്കോൽ_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                താക്കോൽ_Sym sym;
                sym = X11_താക്കോൽ_Code_To_Sym(_this, (താക്കോൽ_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned പൂർണ്ണസംഖ്യ)sym, sym == No_ചിഹ്നം ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            എങ്കിൽ (scancode == data->keyboard.താക്കോൽ_layout[i]) {
                തുടരുക;
            }
            എങ്കിൽ ((SDL_GetKeymapKeycode(ശൂന്യ, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", data->താക്കോൽ_layout[i], SDL_GetScancodeName(data->താക്കോൽ_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                data->keyboard.താക്കോൽ_layout[i] = scancode;
            }
        }
    } അല്ലെങ്കിൽ {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        വേണ്ടി (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_താക്കോൽ_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                താക്കോൽ_Sym sym;
                sym = X11_താക്കോൽ_Code_To_Sym(_this, (താക്കോൽ_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned പൂർണ്ണസംഖ്യ)sym, sym == No_ചിഹ്നം ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            എങ്കിൽ (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } അല്ലെങ്കിൽ {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            data->keyboard.താക്കോൽ_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    തിരികെ true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
സ്ഥിതം unsigned പൂർണ്ണസംഖ്യ X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *vmod_name)
{
    SDL_VideoData *videodata = _this->internal;
    unsigned പൂർണ്ണസംഖ്യ mod_mask = 0;

    സ്ഥിരം Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    എങ്കിൽ (vmod != None) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < Xkb_അക്കം_Virtual_Mods; ++i) {
            എങ്കിൽ (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                നിർത്തുക;
            }
        }
    }

    തിരികെ mod_mask;
}
#endif

സ്ഥിതം unsigned X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    unsigned പൂർണ്ണസംഖ്യ mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    unsigned പൂർണ്ണസംഖ്യ n = xmods->max_keypermod;
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 3; i < 8; i++) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < n; j++) {
            സ്ഥിരം താക്കോൽ_Code_2 kc = xmods->modifiermap[i * n + j];
            എങ്കിൽ (videodata->keyboard.താക്കോൽ_layout[kc] == scancode) {
                mod_mask = 1 << i;
                നിർത്തുക;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    തിരികെ mod_mask;
}

സ്ഥിതം ശൂന്യം X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, താക്കോൽ_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_താക്കോൽ_Code_From_താക്കോൽ_Sym(xkeysym, xkeycode, sdl_mod_mask);

    എങ്കിൽ (!keycode) {
        തിരഞ്ഞെടുപ്പ് (sdl_scancode) {
        അവസ്ഥ SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            നിർത്തുക;
        അവസ്ഥ SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            നിർത്തുക;
        അവസ്ഥ SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            നിർത്തുക;
        അവസ്ഥ SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            നിർത്തുക;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

ശൂന്യം X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    എങ്കിൽ (data->keyboard.xkb_enabled) {
        XkbStateRec state;

        വേണ്ടി (unsigned പൂർണ്ണസംഖ്യ i = 0; i < Xkb_അക്കം_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = ശൂന്യ;
        }

        X11_XkbGetNames(data->display, XkbVirtualModNamesMask, data->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(data->display, XkbAllClientInfoMask | XkbVirtualModsMask, data->keyboard.xkb.desc_ptr);

        എങ്കിൽ (X11_XkbGetState(data->display, XkbUseCoreKbd, &state) == Success) {
            data->keyboard.xkb.current_group = state.group;
        }

        data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        എങ്കിൽ (!data->keyboard.alt_mask) {
            data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        data->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        data->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        data->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        data->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        data->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        വേണ്ടി (unsigned പൂർണ്ണസംഖ്യ i = 0; i < Xkb_അക്കം_Kbd_Groups; ++i) {
            data->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            എങ്കിൽ (!data->keyboard.xkb.keymaps[i]) {
                വേണ്ടി (unsigned പൂർണ്ണസംഖ്യ j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
                    data->keyboard.xkb.keymaps[j] = ശൂന്യ;
                }

                തിരികെ;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        സ്ഥിരം Uint32 valid_mod_mask = ShiftMask | LockMask | data->keyboard.alt_mask | data->keyboard.level3_mask | data->keyboard.level5_mask;

        വേണ്ടി (Uint32 xkeycode = data->keyboard.xkb.desc_ptr->min_താക്കോൽ_code; xkeycode < data->keyboard.xkb.desc_ptr->max_താക്കോൽ_code; ++xkeycode) {
            സ്ഥിരം SDL_Scancode scancode = data->keyboard.താക്കോൽ_layout[xkeycode];
            എങ്കിൽ (scancode == SDL_SCANCODE_UNKNOWN) {
                തുടരുക;
            }

            വേണ്ടി (Uint32 group = 0; group < Xkb_അക്കം_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = data->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                സ്ഥിരം unsigned അക്ഷരം max_താക്കോൽ_group = Xkb_താക്കോൽ_അക്കം_Groups(data->keyboard.xkb.desc_ptr, xkeycode);
                സ്ഥിരം unsigned അക്ഷരം താക്കോൽ_group_info = Xkb_താക്കോൽ_Group_Info(data->keyboard.xkb.desc_ptr, xkeycode);

                എങ്കിൽ (max_താക്കോൽ_group && effective_group >= max_താക്കോൽ_group) {
                    സ്ഥിരം unsigned അക്ഷരം action = XkbOutOfRangeGroupAction(താക്കോൽ_group_info);

                    തിരഞ്ഞെടുപ്പ് (action) {
                    സ്ഥിരസ്ഥിതി:
                        effective_group %= max_താക്കോൽ_group;
                        നിർത്തുക;
                    അവസ്ഥ XkbClampIntoRange:
                        effective_group = max_താക്കോൽ_group - 1;
                        നിർത്തുക;
                    അവസ്ഥ XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_സംഖ്യ(താക്കോൽ_group_info);
                        എങ്കിൽ (effective_group >= max_താക്കോൽ_group) {
                            effective_group = 0;
                        }
                        നിർത്തുക;
                    }
                }

                Xkb_താക്കോൽ_Type_Ptr താക്കോൽ_type = Xkb_താക്കോൽ_താക്കോൽ_Type(data->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                വേണ്ടി (Uint32 level = 0; level < താക്കോൽ_type->അക്കം_levels; ++level) {
                    സ്ഥിരം താക്കോൽ_Sym keysym = X11_താക്കോൽ_Code_To_Sym(_this, xkeycode, effective_group, level);

                    എങ്കിൽ (keysym != No_ചിഹ്നം) {
                        bool താക്കോൽ_added = false;

                        വേണ്ടി (പൂർണ്ണസംഖ്യ map_idx = 0; map_idx < താക്കോൽ_type->map_എണ്ണം; ++map_idx) {
                            എങ്കിൽ (താക്കോൽ_type->map[map_idx].active && താക്കോൽ_type->map[map_idx].level == level) {
                                സ്ഥിരം unsigned പൂർണ്ണസംഖ്യ xkb_mod_mask = താക്കോൽ_type->map[map_idx].mods.mask;
                                എങ്കിൽ ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    സ്ഥിരം SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & data->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    താക്കോൽ_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        എങ്കിൽ (!level && !താക്കോൽ_added) {
                            X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_SetKeymap(data->keyboard.xkb.keymaps[data->keyboard.xkb.current_group], send_event);
    } അല്ലെങ്കിൽ
#endif
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        എങ്കിൽ (!keymap) {
            തിരികെ;
        }

        എങ്കിൽ (send_event) {
            എങ്കിൽ (data->keyboard.core.keysym_map) {
                X11_XFree(data->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
            data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                                     data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                                     &data->keyboard.core.keysyms_per_താക്കോൽ);
        }

        വേണ്ടി (Uint32 xkeycode = data->keyboard.core.min_keycode; xkeycode <= data->keyboard.core.max_keycode; ++xkeycode) {
            സ്ഥിരം SDL_Scancode scancode = data->keyboard.താക്കോൽ_layout[xkeycode];
            എങ്കിൽ (scancode == SDL_SCANCODE_UNKNOWN) {
                തുടരുക;
            }

            സ്ഥിരം താക്കോൽ_Sym keysym = X11_താക്കോൽ_Code_To_Sym(_this, xkeycode, 0, 0);
            എങ്കിൽ (keysym != No_ചിഹ്നം) {
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

ശൂന്യം X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

#ifdef X_HAVE_UTF8_STRING
    എങ്കിൽ (data->im) {
        X11_XCloseIM(data->im);
        data->im = ശൂന്യ;
    } അല്ലെങ്കിൽ {
        X11_XUnregisterIMInstantiateCallback(data->display, ശൂന്യ, ശൂന്യ, ശൂന്യ, im_instantiate_handler, (XPointer)data);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    എങ്കിൽ (data->keyboard.xkb_enabled) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < Xkb_അക്കം_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = ശൂന്യ;
        }

        എങ്കിൽ (data->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(data->keyboard.xkb.desc_ptr, 0, True);
            data->keyboard.xkb.desc_ptr = ശൂന്യ;
        }
    } അല്ലെങ്കിൽ
#endif
        എങ്കിൽ (data->keyboard.core.keysym_map) {
        X11_XFree(data->keyboard.core.keysym_map);
        data->keyboard.core.keysym_map = ശൂന്യ;
    }
}

ശൂന്യം X11_ClearComposition(SDL_WindowData *data)
{
    എങ്കിൽ (data->preedit_length > 0) {
        data->preedit_text[0] = '\0';
        data->preedit_length = 0;
    }

    എങ്കിൽ (data->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        data->ime_needs_clear_composition = false;
    }
}

സ്ഥിതം ശൂന്യം X11_SendEditingEvent(SDL_WindowData *data)
{
    എങ്കിൽ (data->preedit_length == 0) {
        X11_ClearComposition(data);
        തിരികെ;
    }

    bool in_highlight = false;
    പൂർണ്ണസംഖ്യ start = -1, length = 0, i;
    വേണ്ടി (i = 0; i < data->preedit_length; ++i) {
        എങ്കിൽ (data->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            എങ്കിൽ (start < 0) {
                start = i;
                in_highlight = true;
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (in_highlight) {
            // Found the end of the highlight
            നിർത്തുക;
        }
    }
    എങ്കിൽ (in_highlight) {
        length = (i - start);
    } അല്ലെങ്കിൽ {
        start = SDL_clamp(data->preedit_cursor, 0, data->preedit_length);
    }
    SDL_SendEditingText(data->preedit_text, start, length);

    data->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
സ്ഥിതം പൂർണ്ണസംഖ്യ preedit_start_callback(XIC xic, XPointer client_data, XPointer call_data)
{
    // No limit on preedit text length
    തിരികെ -1;
}

സ്ഥിതം ശൂന്യം preedit_done_callback(XIC xic, XPointer client_data, XPointer call_data)
{
}

സ്ഥിതം ശൂന്യം preedit_draw_callback(XIC xic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;
    പൂർണ്ണസംഖ്യ chg_first = SDL_clamp(call_data->chg_first, 0, data->preedit_length);
    പൂർണ്ണസംഖ്യ chg_length = SDL_clamp(call_data->chg_length, 0, data->preedit_length - chg_first);

    സ്ഥിരം അക്ഷരം *start = data->preedit_text;
    എങ്കിൽ (chg_length > 0) {
        // Delete text in range
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, ശൂന്യ);
        }

        സ്ഥിരം അക്ഷരം *end = start;
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; end && *end && i < chg_length; ++i) {
            SDL_StepUTF8(&end, ശൂന്യ);
        }

        എങ്കിൽ (end > start) {
            SDL_memmove((അക്ഷരം *)start, end, SDL_strlen(end) + 1);
            എങ്കിൽ ((chg_first + chg_length) > data->preedit_length) {
                SDL_memmove(&data->preedit_feedback[chg_first], &data->preedit_feedback[chg_first + chg_length], (data->preedit_length - chg_first - chg_length) * വലുപ്പം(*data->preedit_feedback));
            }
        }
        data->preedit_length -= chg_length;
    }

    XIMText *text = call_data->text;
    എങ്കിൽ (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        എങ്കിൽ (text->string.multi_byte) {
            text->length = SDL_utf8strlen(text->string.multi_byte);
        }

        size_t string_size = SDL_strlen(text->string.multi_byte);
        size_t size = string_size + 1;
        എങ്കിൽ (data->preedit_text) {
            size += SDL_strlen(data->preedit_text);
        }
        അക്ഷരം *preedit_text = (അക്ഷരം *)SDL_malloc(size * വലുപ്പം(*preedit_text));
        എങ്കിൽ (preedit_text) {
            size_t pre_size = (start - data->preedit_text);
            size_t post_size = start ? SDL_strlen(start) : 0;
            എങ്കിൽ (pre_size > 0) {
                SDL_memcpy(&preedit_text[0], data->preedit_text, pre_size);
            }
            SDL_memcpy(&preedit_text[pre_size], text->string.multi_byte, string_size);
            എങ്കിൽ (post_size > 0) {
                SDL_memcpy(&preedit_text[pre_size + string_size], start, post_size);
            }
            preedit_text[size - 1] = '\0';
        }

        size_t feedback_size = data->preedit_length + text->length;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_size * വലുപ്പം(*feedback));
        എങ്കിൽ (feedback) {
            size_t pre_size = (size_t)chg_first;
            size_t post_size = (size_t)data->preedit_length - pre_size;
            എങ്കിൽ (pre_size > 0) {
                SDL_memcpy(&feedback[0], data->preedit_feedback, pre_size * വലുപ്പം(*feedback));
            }
            SDL_memcpy(&feedback[pre_size], text->feedback, text->length * വലുപ്പം(*feedback));
            എങ്കിൽ (post_size > 0) {
                SDL_memcpy(&feedback[pre_size + text->length], &data->preedit_feedback[pre_size], post_size * വലുപ്പം(*feedback));
            }
        }

        എങ്കിൽ (preedit_text && feedback) {
            SDL_free(data->preedit_text);
            data->preedit_text = preedit_text;

            SDL_free(data->preedit_feedback);
            data->preedit_feedback = feedback;

            data->preedit_length += text->length;
        } അല്ലെങ്കിൽ {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    data->preedit_cursor = call_data->caret;

#ifdef DEBUG_XIM
    എങ്കിൽ (call_data->chg_length > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_data->chg_length, call_data->chg_first);
    }
    എങ്കിൽ (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_data->chg_first, call_data->caret);
    }
    SDL_Log("Pre-edit text: %s", data->preedit_text);
#endif

    X11_SendEditingEvent(data);
}

സ്ഥിതം ശൂന്യം preedit_caret_callback(XIC xic, XPointer client_data, XIMPreeditCaretCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;

    തിരഞ്ഞെടുപ്പ് (call_data->direction) {
    അവസ്ഥ XIMAbsolutePosition:
        എങ്കിൽ (call_data->position != data->preedit_cursor) {
            data->preedit_cursor = call_data->position;
            X11_SendEditingEvent(data);
        }
        നിർത്തുക;
    അവസ്ഥ XIMDontChange:
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        // Not currently supported
        നിർത്തുക;
    }
}

സ്ഥിതം ശൂന്യം ic_destroyed_handler(XIC ic, XPointer clientData, XPointer callData)
{
    SDL_WindowData *data = (SDL_WindowData *)clientData;
    data->ic = ശൂന്യ;
    X11_Destroy_നിവേശം_Context(data);

    // If the IM was already recreated, create a new IC.
    എങ്കിൽ (data->videodata->im) {
        X11_Create_നിവേശം_Context(data);
    }
}
#endif // X_HAVE_UTF8_STRING

ശൂന്യം X11_Create_നിവേശം_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_VideoData *videodata = data->videodata;

    എങ്കിൽ (SDL_X11_HAVE_UTF8 && videodata->im) {
        സ്ഥിരം അക്ഷരം *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)data;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        എങ്കിൽ (hint && SDL_strstr(hint, "composition")) {
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
                                                         ശൂന്യ);
            എങ്കിൽ (attr) {
                data->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, data->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         ശൂന്യ);
                X11_XFree(attr);
            }
        }
        എങ്കിൽ (!data->ic) {
            data->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClientWindow, data->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     ശൂന്യ);
        }
        data->xim_spot.x = -1;
        data->xim_spot.y = -1;
    }
#endif // X_HAVE_UTF8_STRING
}


ശൂന്യം X11_Destroy_നിവേശം_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    എങ്കിൽ (data->ic) {
        X11_XDestroyIC(data->ic);
        data->ic = ശൂന്യ;
    }
    SDL_free(data->preedit_text);
    SDL_free(data->preedit_feedback);
    data->preedit_text = ശൂന്യ;
    data->preedit_feedback = ശൂന്യ;
#endif
}

സ്ഥിതം ശൂന്യം X11_ResetXIM(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    എങ്കിൽ (data && data->ic) {
        // Clear any partially entered dead keys
        അക്ഷരം *contents = X11_Xutf8ResetIC(data->ic);
        എങ്കിൽ (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    തിരികെ X11_Update_Text_നിവേശം_Area(_this, window);
}

bool X11_Stop_Text_നിവേശം(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    തിരികെ true;
}

bool X11_Update_Text_നിവേശം_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    എങ്കിൽ (data && data->ic) {
        XPoint spot;
        spot.x = window->text_നിവേശം_rect.x + window->text_നിവേശം_cursor;
        spot.y = window->text_നിവേശം_rect.y + window->text_നിവേശം_rect.h;
        എങ്കിൽ (spot.x != data->xim_spot.x || spot.y != data->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, ശൂന്യ);
            എങ്കിൽ (attr) {
                X11_XSetICValues(data->ic, XNPreeditAttributes, attr, ശൂന്യ);
                X11_XFree(attr);
            }
            SDL_copyp(&data->xim_spot, &spot);
        }
    }
#endif
    തിരികെ true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    തിരികെ videodata->use_steam_screen_keyboard;
}

ശൂന്യം X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;

    എങ്കിൽ (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        സ്ഥിരം പൂർണ്ണസംഖ്യ k_EFloating_Gamepad_Text_നിവേശം_Mode_Mode_Single_വരി = 0;    // Enter dismisses the keyboard
        സ്ഥിരം പൂർണ്ണസംഖ്യ k_EFloating_Gamepad_Text_നിവേശം_Mode_Mode_Multiple_വരികൾ = 1; // User needs to explicitly dismiss the keyboard
        സ്ഥിരം പൂർണ്ണസംഖ്യ k_EFloating_Gamepad_Text_നിവേശം_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        സ്ഥിരം പൂർണ്ണസംഖ്യ k_EFloating_Gamepad_Text_നിവേശം_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        അക്ഷരം deeplink[128];
        പൂർണ്ണസംഖ്യ mode;

        തിരഞ്ഞെടുപ്പ് (SDL_Get_Text_നിവേശം_Type(props)) {
        അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_നിവേശം_Mode_Mode_Email;
            നിർത്തുക;
        അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ:
        അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ_PASSWORD_HIDDEN:
        അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_നിവേശം_Mode_Mode_Numeric;
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            എങ്കിൽ (SDL_Get_Text_നിവേശം_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_നിവേശം_Mode_Mode_Multiple_വരികൾ;
            } അല്ലെങ്കിൽ {
                mode = k_EFloating_Gamepad_Text_നിവേശം_Mode_Mode_Single_വരി;
            }
            നിർത്തുക;
        }
        (ശൂന്യം)SDL_snprintf(deeplink, വലുപ്പം(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_നിവേശം_rect.x, window->text_നിവേശം_rect.y,
                           window->text_നിവേശം_rect.w, window->text_നിവേശം_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

ശൂന്യം X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;

    എങ്കിൽ (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
