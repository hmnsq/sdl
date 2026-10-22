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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"

#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_scancode_tables_c.h"

#ಅನ್ತರ್ಭಾವ <X11/keysym.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#ಅನ್ತರ್ಭಾವ <X11/XKBlib.h>
#endif

#ಅನ್ತರ್ಭಾವ "../../events/imKStoUCS.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keysym_to_scancode_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keysym_to_keycode_c.h"

#ifdef X_HAVE_UTF8_STRING
#ಅನ್ತರ್ಭಾವ <locale.h>
#endif

ಸ್ಥಿರ SDL_ScancodeTable scancode_set[] = {
    SDL_SCANCODE_TABLE_DARWIN,
    SDL_SCANCODE_TABLE_XFREE86_1,
    SDL_SCANCODE_TABLE_XFREE86_2,
    SDL_SCANCODE_TABLE_XVNC,
};

ಸ್ಥಿರ bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    ವಿಕಲ್ಪ (scancode) {
    ಪಕ್ಷ SDL_SCANCODE_ESCAPE:
    ಪಕ್ಷ SDL_SCANCODE_CAPSLOCK:
    ಪಕ್ಷ SDL_SCANCODE_NUMLOCKCLEAR:
    ಪಕ್ಷ SDL_SCANCODE_LSHIFT:
    ಪಕ್ಷ SDL_SCANCODE_RSHIFT:
    ಪಕ್ಷ SDL_SCANCODE_LCTRL:
    ಪಕ್ಷ SDL_SCANCODE_RCTRL:
    ಪಕ್ಷ SDL_SCANCODE_LALT:
    ಪಕ್ಷ SDL_SCANCODE_RALT:
    ಪಕ್ಷ SDL_SCANCODE_LGUI:
    ಪಕ್ಷ SDL_SCANCODE_RGUI:
        ಪ್ರತ್ಯಾಗಮ false;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ true;
    }
}

ಸ್ಥಿರ ಕೀಲಿ_Sym X11_ಕೀಲಿ_Code_To_Sym(SDL_VideoDevice *_this, ಕೀಲಿ_Code_2 keycode, unsigned ಪೂರ್ಣಾಙ್ಕ group, unsigned ಪೂರ್ಣಾಙ್ಕ level)
{
    SDL_VideoData *data = _this->internal;
    ಕೀಲಿ_Sym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ಯದಿ (data->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(data->display, keycode, group, level);
    } ಅನ್ಯಥಾ
#endif
    {
        // TODO: Handle groups on the legacy path.
        ಯದಿ (keycode >= data->keyboard.core.min_keycode && keycode <= data->keyboard.core.max_keycode) {
            keysym = data->keyboard.core.keysym_map[(keycode - data->keyboard.core.min_keycode) * data->keyboard.core.keysyms_per_ಕೀಲಿ];
        } ಅನ್ಯಥಾ {
            keysym = No_ಚಿಹ್ನೆ;
        }
    }

    ಪ್ರತ್ಯಾಗಮ keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
ಸ್ಥಿರ SDL_Scancode X11_ಕೀಲಿ_Code_To_SDLScancode(SDL_VideoDevice *_this, ಕೀಲಿ_Code_2 keycode)
{
    ಧ್ರುವ ಕೀಲಿ_Sym keysym = X11_ಕೀಲಿ_Code_To_Sym(_this, keycode, 0, 0);

    ಯದಿ (keysym == No_ಚಿಹ್ನೆ) {
        ಪ್ರತ್ಯಾಗಮ SDL_SCANCODE_UNKNOWN;
    }

    ಪ್ರತ್ಯಾಗಮ SDL_Get_Scancode_From_ಕೀಲಿ_Sym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
ಸ್ಥಿರ bool X11_InitIM(SDL_VideoData *videodata);

ಸ್ಥಿರ ಶೂನ್ಯ im_instantiate_handler(Display *display, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    ಯದಿ (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, im_instantiate_handler, clientData);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ im_destroyed_handler(XIM im, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    videodata->im = ರಿಕ್ತ;
    X11_XRegisterIMInstantiateCallback(videodata->display, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, im_instantiate_handler, clientData);
}

ಸ್ಥಿರ bool X11_InitIM(SDL_VideoData *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    ವರ್ಣ *prev_locale = setlocale(LC_ALL, ರಿಕ್ತ);
    ವರ್ಣ *prev_xmods = X11_XSetLocaleModifiers(ರಿಕ್ತ);

    ಯದಿ (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    ಯದಿ (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (ಶೂನ್ಯ)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (ಶೂನ್ಯ)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    ಯದಿ (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (ವರ್ಣ *)ರಿಕ್ತ);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *w = videodata->windowlist[i];
            ಯದಿ (!w->ic) {
                X11_Create_ಒಳಹರಿವು_Context(w);
            }
        }

        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಪ್ರತ್ಯಾಗಮ false;
}
#endif // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    ಪೂರ್ಣಾಙ್ಕ i = 0;
    ಪೂರ್ಣಾಙ್ಕ j = 0;
    ಪೂರ್ಣಾಙ್ಕ min_keycode, max_keycode;
    ಸಂರಚನಾ
    {
        SDL_Scancode scancode;
        ಕೀಲಿ_Sym keysym;
        ಪೂರ್ಣಾಙ್ಕ ಮೌಲ್ಯ;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_ಎಡ, XK_ಎಡ, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    ಪೂರ್ಣಾಙ್ಕ best_distance;
    ಪೂರ್ಣಾಙ್ಕ best_index;
    ಪೂರ್ಣಾಙ್ಕ distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ಪೂರ್ಣಾಙ್ಕ xkb_major = XkbMajorVersion;
    ಪೂರ್ಣಾಙ್ಕ xkb_minor = XkbMinorVersion;

    ಯದಿ (X11_XkbQueryExtension(data->display, ರಿಕ್ತ, &data->keyboard.xkb.event, ರಿಕ್ತ, &xkb_major, &xkb_minor)) {
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
    } ಅನ್ಯಥಾ
#endif
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
        data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                              data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                              &data->keyboard.core.keysyms_per_ಕೀಲಿ);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    ಯದಿ (SDL_X11_HAVE_UTF8) {
        ಯದಿ (!X11_InitIM(data)) {
            X11_XRegisterIMInstantiateCallback(data->display, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, im_instantiate_handler, (XPointer)data);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_index = -1;
    X11_XDisplayKeycodes(data->display, &min_keycode, &max_keycode);
    ಪ್ರತಿ (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].ಮೌಲ್ಯ = X11_XKeysymToKeycode(data->display, fingerprint[i].keysym) - min_keycode;
    }
    ಪ್ರತಿ (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        ಪೂರ್ಣಾಙ್ಕ table_size;
        ಧ್ರುವ SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_size);

        distance = 0;
        ಪ್ರತಿ (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            ಯದಿ (fingerprint[j].ಮೌಲ್ಯ < 0 || fingerprint[j].ಮೌಲ್ಯ >= table_size) {
                distance += 1;
            } ಅನ್ಯಥಾ ಯದಿ (table[fingerprint[j].ಮೌಲ್ಯ] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        ಯದಿ (distance < best_distance) {
            best_distance = distance;
            best_index = i;
        }
    }
    ಯದಿ (best_index < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        ಪೂರ್ಣಾಙ್ಕ fingerprint_ಮೌಲ್ಯ = X11_XKeysymToKeycode(data->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        ಯದಿ (fingerprint_ಮೌಲ್ಯ == 235) {
            ಪ್ರತಿ (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                ಯದಿ (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_index = i;
                    best_distance = 0;
                    ಭಙ್ಗ;
                }
            }
        }
    }
    ಯದಿ (best_index >= 0 && best_distance <= 2) {
        ಪೂರ್ಣಾಙ್ಕ table_size;
        ಧ್ರುವ SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_index], &table_size);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_index, min_keycode, max_keycode, table_size);
#endif
        // This should never happen, but just in case...
        ಯದಿ (table_size > (SDL_arraysize(data->keyboard.ಕೀಲಿ_layout) - min_keycode)) {
            table_size = (SDL_arraysize(data->keyboard.ಕೀಲಿ_layout) - min_keycode);
        }
        SDL_memcpy(&data->keyboard.ಕೀಲಿ_layout[min_keycode], table, ಪರಿಮಾಣ(SDL_Scancode) * table_size);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        ಪ್ರತಿ (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_ಕೀಲಿ_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                ಕೀಲಿ_Sym sym;
                sym = X11_ಕೀಲಿ_Code_To_Sym(_this, (ಕೀಲಿ_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned ಪೂರ್ಣಾಙ್ಕ)sym, sym == No_ಚಿಹ್ನೆ ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            ಯದಿ (scancode == data->keyboard.ಕೀಲಿ_layout[i]) {
                ಅನುವರ್ತ;
            }
            ಯದಿ ((SDL_GetKeymapKeycode(ರಿಕ್ತ, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", data->ಕೀಲಿ_layout[i], SDL_GetScancodeName(data->ಕೀಲಿ_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                data->keyboard.ಕೀಲಿ_layout[i] = scancode;
            }
        }
    } ಅನ್ಯಥಾ {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        ಪ್ರತಿ (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_ಕೀಲಿ_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                ಕೀಲಿ_Sym sym;
                sym = X11_ಕೀಲಿ_Code_To_Sym(_this, (ಕೀಲಿ_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned ಪೂರ್ಣಾಙ್ಕ)sym, sym == No_ಚಿಹ್ನೆ ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            ಯದಿ (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } ಅನ್ಯಥಾ {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            data->keyboard.ಕೀಲಿ_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    ಪ್ರತ್ಯಾಗಮ true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
ಸ್ಥಿರ unsigned ಪೂರ್ಣಾಙ್ಕ X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *vmod_name)
{
    SDL_VideoData *videodata = _this->internal;
    unsigned ಪೂರ್ಣಾಙ್ಕ mod_mask = 0;

    ಧ್ರುವ Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    ಯದಿ (vmod != None) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < Xkb_ಅಂಕೆ_Virtual_Mods; ++i) {
            ಯದಿ (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                ಭಙ್ಗ;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ mod_mask;
}
#endif

ಸ್ಥಿರ unsigned X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    unsigned ಪೂರ್ಣಾಙ್ಕ mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    unsigned ಪೂರ್ಣಾಙ್ಕ n = xmods->max_keypermod;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 3; i < 8; i++) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < n; j++) {
            ಧ್ರುವ ಕೀಲಿ_Code_2 kc = xmods->modifiermap[i * n + j];
            ಯದಿ (videodata->keyboard.ಕೀಲಿ_layout[kc] == scancode) {
                mod_mask = 1 << i;
                ಭಙ್ಗ;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    ಪ್ರತ್ಯಾಗಮ mod_mask;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, ಕೀಲಿ_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_ಕೀಲಿ_Code_From_ಕೀಲಿ_Sym(xkeysym, xkeycode, sdl_mod_mask);

    ಯದಿ (!keycode) {
        ವಿಕಲ್ಪ (sdl_scancode) {
        ಪಕ್ಷ SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            ಭಙ್ಗ;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

ಶೂನ್ಯ X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ಯದಿ (data->keyboard.xkb_enabled) {
        XkbStateRec state;

        ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ i = 0; i < Xkb_ಅಂಕೆ_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = ರಿಕ್ತ;
        }

        X11_XkbGetNames(data->display, XkbVirtualModNamesMask, data->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(data->display, XkbAllClientInfoMask | XkbVirtualModsMask, data->keyboard.xkb.desc_ptr);

        ಯದಿ (X11_XkbGetState(data->display, XkbUseCoreKbd, &state) == Success) {
            data->keyboard.xkb.current_group = state.group;
        }

        data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        ಯದಿ (!data->keyboard.alt_mask) {
            data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        data->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        data->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        data->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        data->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        data->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ i = 0; i < Xkb_ಅಂಕೆ_Kbd_Groups; ++i) {
            data->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            ಯದಿ (!data->keyboard.xkb.keymaps[i]) {
                ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
                    data->keyboard.xkb.keymaps[j] = ರಿಕ್ತ;
                }

                ಪ್ರತ್ಯಾಗಮ;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ಧ್ರುವ Uint32 valid_mod_mask = ShiftMask | LockMask | data->keyboard.alt_mask | data->keyboard.level3_mask | data->keyboard.level5_mask;

        ಪ್ರತಿ (Uint32 xkeycode = data->keyboard.xkb.desc_ptr->min_ಕೀಲಿ_code; xkeycode < data->keyboard.xkb.desc_ptr->max_ಕೀಲಿ_code; ++xkeycode) {
            ಧ್ರುವ SDL_Scancode scancode = data->keyboard.ಕೀಲಿ_layout[xkeycode];
            ಯದಿ (scancode == SDL_SCANCODE_UNKNOWN) {
                ಅನುವರ್ತ;
            }

            ಪ್ರತಿ (Uint32 group = 0; group < Xkb_ಅಂಕೆ_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = data->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                ಧ್ರುವ unsigned ವರ್ಣ max_ಕೀಲಿ_group = Xkb_ಕೀಲಿ_ಅಂಕೆ_Groups(data->keyboard.xkb.desc_ptr, xkeycode);
                ಧ್ರುವ unsigned ವರ್ಣ ಕೀಲಿ_group_info = Xkb_ಕೀಲಿ_Group_Info(data->keyboard.xkb.desc_ptr, xkeycode);

                ಯದಿ (max_ಕೀಲಿ_group && effective_group >= max_ಕೀಲಿ_group) {
                    ಧ್ರುವ unsigned ವರ್ಣ action = XkbOutOfRangeGroupAction(ಕೀಲಿ_group_info);

                    ವಿಕಲ್ಪ (action) {
                    ಸ್ವಭಾವ:
                        effective_group %= max_ಕೀಲಿ_group;
                        ಭಙ್ಗ;
                    ಪಕ್ಷ XkbClampIntoRange:
                        effective_group = max_ಕೀಲಿ_group - 1;
                        ಭಙ್ಗ;
                    ಪಕ್ಷ XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_ಸಂಖ್ಯೆ(ಕೀಲಿ_group_info);
                        ಯದಿ (effective_group >= max_ಕೀಲಿ_group) {
                            effective_group = 0;
                        }
                        ಭಙ್ಗ;
                    }
                }

                Xkb_ಕೀಲಿ_Type_Ptr ಕೀಲಿ_type = Xkb_ಕೀಲಿ_ಕೀಲಿ_Type(data->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                ಪ್ರತಿ (Uint32 level = 0; level < ಕೀಲಿ_type->ಅಂಕೆ_levels; ++level) {
                    ಧ್ರುವ ಕೀಲಿ_Sym keysym = X11_ಕೀಲಿ_Code_To_Sym(_this, xkeycode, effective_group, level);

                    ಯದಿ (keysym != No_ಚಿಹ್ನೆ) {
                        bool ಕೀಲಿ_added = false;

                        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ map_idx = 0; map_idx < ಕೀಲಿ_type->map_ಎಣಿಕೆ; ++map_idx) {
                            ಯದಿ (ಕೀಲಿ_type->map[map_idx].active && ಕೀಲಿ_type->map[map_idx].level == level) {
                                ಧ್ರುವ unsigned ಪೂರ್ಣಾಙ್ಕ xkb_mod_mask = ಕೀಲಿ_type->map[map_idx].mods.mask;
                                ಯದಿ ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    ಧ್ರುವ SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & data->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    ಕೀಲಿ_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        ಯದಿ (!level && !ಕೀಲಿ_added) {
                            X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_SetKeymap(data->keyboard.xkb.keymaps[data->keyboard.xkb.current_group], send_event);
    } ಅನ್ಯಥಾ
#endif
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        ಯದಿ (!keymap) {
            ಪ್ರತ್ಯಾಗಮ;
        }

        ಯದಿ (send_event) {
            ಯದಿ (data->keyboard.core.keysym_map) {
                X11_XFree(data->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
            data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                                     data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                                     &data->keyboard.core.keysyms_per_ಕೀಲಿ);
        }

        ಪ್ರತಿ (Uint32 xkeycode = data->keyboard.core.min_keycode; xkeycode <= data->keyboard.core.max_keycode; ++xkeycode) {
            ಧ್ರುವ SDL_Scancode scancode = data->keyboard.ಕೀಲಿ_layout[xkeycode];
            ಯದಿ (scancode == SDL_SCANCODE_UNKNOWN) {
                ಅನುವರ್ತ;
            }

            ಧ್ರುವ ಕೀಲಿ_Sym keysym = X11_ಕೀಲಿ_Code_To_Sym(_this, xkeycode, 0, 0);
            ಯದಿ (keysym != No_ಚಿಹ್ನೆ) {
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

ಶೂನ್ಯ X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

#ifdef X_HAVE_UTF8_STRING
    ಯದಿ (data->im) {
        X11_XCloseIM(data->im);
        data->im = ರಿಕ್ತ;
    } ಅನ್ಯಥಾ {
        X11_XUnregisterIMInstantiateCallback(data->display, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, im_instantiate_handler, (XPointer)data);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ಯದಿ (data->keyboard.xkb_enabled) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < Xkb_ಅಂಕೆ_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = ರಿಕ್ತ;
        }

        ಯದಿ (data->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(data->keyboard.xkb.desc_ptr, 0, True);
            data->keyboard.xkb.desc_ptr = ರಿಕ್ತ;
        }
    } ಅನ್ಯಥಾ
#endif
        ಯದಿ (data->keyboard.core.keysym_map) {
        X11_XFree(data->keyboard.core.keysym_map);
        data->keyboard.core.keysym_map = ರಿಕ್ತ;
    }
}

ಶೂನ್ಯ X11_ClearComposition(SDL_WindowData *data)
{
    ಯದಿ (data->preedit_length > 0) {
        data->preedit_text[0] = '\0';
        data->preedit_length = 0;
    }

    ಯದಿ (data->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        data->ime_needs_clear_composition = false;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_SendEditingEvent(SDL_WindowData *data)
{
    ಯದಿ (data->preedit_length == 0) {
        X11_ClearComposition(data);
        ಪ್ರತ್ಯಾಗಮ;
    }

    bool in_highlight = false;
    ಪೂರ್ಣಾಙ್ಕ start = -1, length = 0, i;
    ಪ್ರತಿ (i = 0; i < data->preedit_length; ++i) {
        ಯದಿ (data->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            ಯದಿ (start < 0) {
                start = i;
                in_highlight = true;
            }
        } ಅನ್ಯಥಾ ಯದಿ (in_highlight) {
            // Found the end of the highlight
            ಭಙ್ಗ;
        }
    }
    ಯದಿ (in_highlight) {
        length = (i - start);
    } ಅನ್ಯಥಾ {
        start = SDL_clamp(data->preedit_cursor, 0, data->preedit_length);
    }
    SDL_SendEditingText(data->preedit_text, start, length);

    data->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ preedit_start_callback(XIC xic, XPointer client_data, XPointer call_data)
{
    // No limit on preedit text length
    ಪ್ರತ್ಯಾಗಮ -1;
}

ಸ್ಥಿರ ಶೂನ್ಯ preedit_done_callback(XIC xic, XPointer client_data, XPointer call_data)
{
}

ಸ್ಥಿರ ಶೂನ್ಯ preedit_draw_callback(XIC xic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;
    ಪೂರ್ಣಾಙ್ಕ chg_first = SDL_clamp(call_data->chg_first, 0, data->preedit_length);
    ಪೂರ್ಣಾಙ್ಕ chg_length = SDL_clamp(call_data->chg_length, 0, data->preedit_length - chg_first);

    ಧ್ರುವ ವರ್ಣ *start = data->preedit_text;
    ಯದಿ (chg_length > 0) {
        // Delete text in range
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, ರಿಕ್ತ);
        }

        ಧ್ರುವ ವರ್ಣ *end = start;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; end && *end && i < chg_length; ++i) {
            SDL_StepUTF8(&end, ರಿಕ್ತ);
        }

        ಯದಿ (end > start) {
            SDL_memmove((ವರ್ಣ *)start, end, SDL_strlen(end) + 1);
            ಯದಿ ((chg_first + chg_length) > data->preedit_length) {
                SDL_memmove(&data->preedit_feedback[chg_first], &data->preedit_feedback[chg_first + chg_length], (data->preedit_length - chg_first - chg_length) * ಪರಿಮಾಣ(*data->preedit_feedback));
            }
        }
        data->preedit_length -= chg_length;
    }

    XIMText *text = call_data->text;
    ಯದಿ (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        ಯದಿ (text->string.multi_byte) {
            text->length = SDL_utf8strlen(text->string.multi_byte);
        }

        size_t string_size = SDL_strlen(text->string.multi_byte);
        size_t size = string_size + 1;
        ಯದಿ (data->preedit_text) {
            size += SDL_strlen(data->preedit_text);
        }
        ವರ್ಣ *preedit_text = (ವರ್ಣ *)SDL_malloc(size * ಪರಿಮಾಣ(*preedit_text));
        ಯದಿ (preedit_text) {
            size_t pre_size = (start - data->preedit_text);
            size_t post_size = start ? SDL_strlen(start) : 0;
            ಯದಿ (pre_size > 0) {
                SDL_memcpy(&preedit_text[0], data->preedit_text, pre_size);
            }
            SDL_memcpy(&preedit_text[pre_size], text->string.multi_byte, string_size);
            ಯದಿ (post_size > 0) {
                SDL_memcpy(&preedit_text[pre_size + string_size], start, post_size);
            }
            preedit_text[size - 1] = '\0';
        }

        size_t feedback_size = data->preedit_length + text->length;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_size * ಪರಿಮಾಣ(*feedback));
        ಯದಿ (feedback) {
            size_t pre_size = (size_t)chg_first;
            size_t post_size = (size_t)data->preedit_length - pre_size;
            ಯದಿ (pre_size > 0) {
                SDL_memcpy(&feedback[0], data->preedit_feedback, pre_size * ಪರಿಮಾಣ(*feedback));
            }
            SDL_memcpy(&feedback[pre_size], text->feedback, text->length * ಪರಿಮಾಣ(*feedback));
            ಯದಿ (post_size > 0) {
                SDL_memcpy(&feedback[pre_size + text->length], &data->preedit_feedback[pre_size], post_size * ಪರಿಮಾಣ(*feedback));
            }
        }

        ಯದಿ (preedit_text && feedback) {
            SDL_free(data->preedit_text);
            data->preedit_text = preedit_text;

            SDL_free(data->preedit_feedback);
            data->preedit_feedback = feedback;

            data->preedit_length += text->length;
        } ಅನ್ಯಥಾ {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    data->preedit_cursor = call_data->caret;

#ifdef DEBUG_XIM
    ಯದಿ (call_data->chg_length > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_data->chg_length, call_data->chg_first);
    }
    ಯದಿ (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_data->chg_first, call_data->caret);
    }
    SDL_Log("Pre-edit text: %s", data->preedit_text);
#endif

    X11_SendEditingEvent(data);
}

ಸ್ಥಿರ ಶೂನ್ಯ preedit_caret_callback(XIC xic, XPointer client_data, XIMPreeditCaretCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;

    ವಿಕಲ್ಪ (call_data->direction) {
    ಪಕ್ಷ XIMAbsolutePosition:
        ಯದಿ (call_data->position != data->preedit_cursor) {
            data->preedit_cursor = call_data->position;
            X11_SendEditingEvent(data);
        }
        ಭಙ್ಗ;
    ಪಕ್ಷ XIMDontChange:
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        // Not currently supported
        ಭಙ್ಗ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ic_destroyed_handler(XIC ic, XPointer clientData, XPointer callData)
{
    SDL_WindowData *data = (SDL_WindowData *)clientData;
    data->ic = ರಿಕ್ತ;
    X11_Destroy_ಒಳಹರಿವು_Context(data);

    // If the IM was already recreated, create a new IC.
    ಯದಿ (data->videodata->im) {
        X11_Create_ಒಳಹರಿವು_Context(data);
    }
}
#endif // X_HAVE_UTF8_STRING

ಶೂನ್ಯ X11_Create_ಒಳಹರಿವು_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_VideoData *videodata = data->videodata;

    ಯದಿ (SDL_X11_HAVE_UTF8 && videodata->im) {
        ಧ್ರುವ ವರ್ಣ *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)data;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        ಯದಿ (hint && SDL_strstr(hint, "composition")) {
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
                                                         ರಿಕ್ತ);
            ಯದಿ (attr) {
                data->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, data->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         ರಿಕ್ತ);
                X11_XFree(attr);
            }
        }
        ಯದಿ (!data->ic) {
            data->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClientWindow, data->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     ರಿಕ್ತ);
        }
        data->xim_spot.x = -1;
        data->xim_spot.y = -1;
    }
#endif // X_HAVE_UTF8_STRING
}


ಶೂನ್ಯ X11_Destroy_ಒಳಹರಿವು_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    ಯದಿ (data->ic) {
        X11_XDestroyIC(data->ic);
        data->ic = ರಿಕ್ತ;
    }
    SDL_free(data->preedit_text);
    SDL_free(data->preedit_feedback);
    data->preedit_text = ರಿಕ್ತ;
    data->preedit_feedback = ರಿಕ್ತ;
#endif
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_ResetXIM(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    ಯದಿ (data && data->ic) {
        // Clear any partially entered dead keys
        ವರ್ಣ *contents = X11_Xutf8ResetIC(data->ic);
        ಯದಿ (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    ಪ್ರತ್ಯಾಗಮ X11_Update_Text_ಒಳಹರಿವು_Area(_this, window);
}

bool X11_Stop_Text_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    ಪ್ರತ್ಯಾಗಮ true;
}

bool X11_Update_Text_ಒಳಹರಿವು_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    ಯದಿ (data && data->ic) {
        XPoint spot;
        spot.x = window->text_ಒಳಹರಿವು_rect.x + window->text_ಒಳಹರಿವು_cursor;
        spot.y = window->text_ಒಳಹರಿವು_rect.y + window->text_ಒಳಹರಿವು_rect.h;
        ಯದಿ (spot.x != data->xim_spot.x || spot.y != data->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, ರಿಕ್ತ);
            ಯದಿ (attr) {
                X11_XSetICValues(data->ic, XNPreeditAttributes, attr, ರಿಕ್ತ);
                X11_XFree(attr);
            }
            SDL_copyp(&data->xim_spot, &spot);
        }
    }
#endif
    ಪ್ರತ್ಯಾಗಮ true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    ಪ್ರತ್ಯಾಗಮ videodata->use_steam_screen_keyboard;
}

ಶೂನ್ಯ X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;

    ಯದಿ (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ k_EFloating_Gamepad_Text_ಒಳಹರಿವು_Mode_Mode_Single_ಸಾಲು = 0;    // Enter dismisses the keyboard
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ k_EFloating_Gamepad_Text_ಒಳಹರಿವು_Mode_Mode_Multiple_ಸಾಲುಗಳು = 1; // User needs to explicitly dismiss the keyboard
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ k_EFloating_Gamepad_Text_ಒಳಹರಿವು_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ k_EFloating_Gamepad_Text_ಒಳಹರಿವು_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        ವರ್ಣ deeplink[128];
        ಪೂರ್ಣಾಙ್ಕ mode;

        ವಿಕಲ್ಪ (SDL_Get_Text_ಒಳಹರಿವು_Type(props)) {
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_ಒಳಹರಿವು_Mode_Mode_Email;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ:
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_HIDDEN:
        ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_ಒಳಹರಿವು_Mode_Mode_Numeric;
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            ಯದಿ (SDL_Get_Text_ಒಳಹರಿವು_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_ಒಳಹರಿವು_Mode_Mode_Multiple_ಸಾಲುಗಳು;
            } ಅನ್ಯಥಾ {
                mode = k_EFloating_Gamepad_Text_ಒಳಹರಿವು_Mode_Mode_Single_ಸಾಲು;
            }
            ಭಙ್ಗ;
        }
        (ಶೂನ್ಯ)SDL_snprintf(deeplink, ಪರಿಮಾಣ(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_ಒಳಹರಿವು_rect.x, window->text_ಒಳಹರಿವು_rect.y,
                           window->text_ಒಳಹರಿವು_rect.w, window->text_ಒಳಹರಿವು_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

ಶೂನ್ಯ X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;

    ಯದಿ (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
