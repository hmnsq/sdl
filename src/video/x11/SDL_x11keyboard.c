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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ଅନ୍ତର୍ଭାଵ "SDL_x11video.h"

#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keyboard_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_scancode_tables_c.h"

#ଅନ୍ତର୍ଭାଵ <X11/keysym.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#ଅନ୍ତର୍ଭାଵ <X11/XKBlib.h>
#endif

#ଅନ୍ତର୍ଭାଵ "../../events/imKStoUCS.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keysym_to_scancode_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keysym_to_keycode_c.h"

#ifdef X_HAVE_UTF8_STRING
#ଅନ୍ତର୍ଭାଵ <locale.h>
#endif

ସ୍ଥିର SDL_ScancodeTable scancode_set[] = {
    SDL_SCANCODE_TABLE_DARWIN,
    SDL_SCANCODE_TABLE_XFREE86_1,
    SDL_SCANCODE_TABLE_XFREE86_2,
    SDL_SCANCODE_TABLE_XVNC,
};

ସ୍ଥିର bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    ବାଛ (scancode) {
    ସ୍ଥିତି SDL_SCANCODE_ESCAPE:
    ସ୍ଥିତି SDL_SCANCODE_CAPSLOCK:
    ସ୍ଥିତି SDL_SCANCODE_NUMLOCKCLEAR:
    ସ୍ଥିତି SDL_SCANCODE_LSHIFT:
    ସ୍ଥିତି SDL_SCANCODE_RSHIFT:
    ସ୍ଥିତି SDL_SCANCODE_LCTRL:
    ସ୍ଥିତି SDL_SCANCODE_RCTRL:
    ସ୍ଥିତି SDL_SCANCODE_LALT:
    ସ୍ଥିତି SDL_SCANCODE_RALT:
    ସ୍ଥିତି SDL_SCANCODE_LGUI:
    ସ୍ଥିତି SDL_SCANCODE_RGUI:
        ଫେରନ୍ତୁ false;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ true;
    }
}

ସ୍ଥିର ଚାବି_Sym X11_ଚାବି_Code_To_Sym(SDL_VideoDevice *_this, ଚାବି_Code_2 keycode, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା group, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା level)
{
    SDL_VideoData *data = _this->internal;
    ଚାବି_Sym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ଯଦି (data->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(data->display, keycode, group, level);
    } ଅନ୍ୟଥା
#endif
    {
        // TODO: Handle groups on the legacy path.
        ଯଦି (keycode >= data->keyboard.core.min_keycode && keycode <= data->keyboard.core.max_keycode) {
            keysym = data->keyboard.core.keysym_map[(keycode - data->keyboard.core.min_keycode) * data->keyboard.core.keysyms_per_ଚାବି];
        } ଅନ୍ୟଥା {
            keysym = No_ପ୍ରତୀକ;
        }
    }

    ଫେରନ୍ତୁ keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
ସ୍ଥିର SDL_Scancode X11_ଚାବି_Code_To_SDLScancode(SDL_VideoDevice *_this, ଚାବି_Code_2 keycode)
{
    ଅଚଳ ଚାବି_Sym keysym = X11_ଚାବି_Code_To_Sym(_this, keycode, 0, 0);

    ଯଦି (keysym == No_ପ୍ରତୀକ) {
        ଫେରନ୍ତୁ SDL_SCANCODE_UNKNOWN;
    }

    ଫେରନ୍ତୁ SDL_Get_Scancode_From_ଚାବି_Sym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
ସ୍ଥିର bool X11_InitIM(SDL_VideoData *videodata);

ସ୍ଥିର ଶୂନ୍ୟ im_instantiate_handler(Display *display, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    ଯଦି (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, ଖାଲି, ଖାଲି, ଖାଲି, im_instantiate_handler, clientData);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ im_destroyed_handler(XIM im, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    videodata->im = ଖାଲି;
    X11_XRegisterIMInstantiateCallback(videodata->display, ଖାଲି, ଖାଲି, ଖାଲି, im_instantiate_handler, clientData);
}

ସ୍ଥିର bool X11_InitIM(SDL_VideoData *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    ଅକ୍ଷର *prev_locale = setlocale(LC_ALL, ଖାଲି);
    ଅକ୍ଷର *prev_xmods = X11_XSetLocaleModifiers(ଖାଲି);

    ଯଦି (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    ଯଦି (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (ଶୂନ୍ୟ)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, ଖାଲି, ଖାଲି, ଖାଲି);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (ଶୂନ୍ୟ)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    ଯଦି (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (ଅକ୍ଷର *)ଖାଲି);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *w = videodata->windowlist[i];
            ଯଦି (!w->ic) {
                X11_Create_ନିବେଶ_Context(w);
            }
        }

        ଫେରନ୍ତୁ true;
    }

    ଫେରନ୍ତୁ false;
}
#endif // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା min_keycode, max_keycode;
    ସଂରଚନା
    {
        SDL_Scancode scancode;
        ଚାବି_Sym keysym;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_ବାମ, XK_ବାମ, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା best_distance;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା best_index;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା xkb_major = XkbMajorVersion;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା xkb_minor = XkbMinorVersion;

    ଯଦି (X11_XkbQueryExtension(data->display, ଖାଲି, &data->keyboard.xkb.event, ଖାଲି, &xkb_major, &xkb_minor)) {
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
    } ଅନ୍ୟଥା
#endif
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
        data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                              data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                              &data->keyboard.core.keysyms_per_ଚାବି);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    ଯଦି (SDL_X11_HAVE_UTF8) {
        ଯଦି (!X11_InitIM(data)) {
            X11_XRegisterIMInstantiateCallback(data->display, ଖାଲି, ଖାଲି, ଖାଲି, im_instantiate_handler, (XPointer)data);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_index = -1;
    X11_XDisplayKeycodes(data->display, &min_keycode, &max_keycode);
    ପାଇଁ (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].ମୂଲ୍ୟ = X11_XKeysymToKeycode(data->display, fingerprint[i].keysym) - min_keycode;
    }
    ପାଇଁ (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା table_size;
        ଅଚଳ SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_size);

        distance = 0;
        ପାଇଁ (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            ଯଦି (fingerprint[j].ମୂଲ୍ୟ < 0 || fingerprint[j].ମୂଲ୍ୟ >= table_size) {
                distance += 1;
            } ଅନ୍ୟଥା ଯଦି (table[fingerprint[j].ମୂଲ୍ୟ] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        ଯଦି (distance < best_distance) {
            best_distance = distance;
            best_index = i;
        }
    }
    ଯଦି (best_index < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା fingerprint_ମୂଲ୍ୟ = X11_XKeysymToKeycode(data->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        ଯଦି (fingerprint_ମୂଲ୍ୟ == 235) {
            ପାଇଁ (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                ଯଦି (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_index = i;
                    best_distance = 0;
                    ଭାଙ୍ଗ;
                }
            }
        }
    }
    ଯଦି (best_index >= 0 && best_distance <= 2) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା table_size;
        ଅଚଳ SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_index], &table_size);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_index, min_keycode, max_keycode, table_size);
#endif
        // This should never happen, but just in case...
        ଯଦି (table_size > (SDL_arraysize(data->keyboard.ଚାବି_layout) - min_keycode)) {
            table_size = (SDL_arraysize(data->keyboard.ଚାବି_layout) - min_keycode);
        }
        SDL_memcpy(&data->keyboard.ଚାବି_layout[min_keycode], table, ଆକାର(SDL_Scancode) * table_size);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        ପାଇଁ (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_ଚାବି_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                ଚାବି_Sym sym;
                sym = X11_ଚାବି_Code_To_Sym(_this, (ଚାବି_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)sym, sym == No_ପ୍ରତୀକ ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            ଯଦି (scancode == data->keyboard.ଚାବି_layout[i]) {
                ଜାରି;
            }
            ଯଦି ((SDL_GetKeymapKeycode(ଖାଲି, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", data->ଚାବି_layout[i], SDL_GetScancodeName(data->ଚାବି_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                data->keyboard.ଚାବି_layout[i] = scancode;
            }
        }
    } ଅନ୍ୟଥା {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        ପାଇଁ (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_ଚାବି_Code_To_SDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                ଚାବି_Sym sym;
                sym = X11_ଚାବି_Code_To_Sym(_this, (ଚାବି_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)sym, sym == No_ପ୍ରତୀକ ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            ଯଦି (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } ଅନ୍ୟଥା {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            data->keyboard.ଚାବି_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    ଫେରନ୍ତୁ true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
ସ୍ଥିର unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *vmod_name)
{
    SDL_VideoData *videodata = _this->internal;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା mod_mask = 0;

    ଅଚଳ Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    ଯଦି (vmod != None) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < Xkb_ଅଙ୍କ_Virtual_Mods; ++i) {
            ଯଦି (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                ଭାଙ୍ଗ;
            }
        }
    }

    ଫେରନ୍ତୁ mod_mask;
}
#endif

ସ୍ଥିର unsigned X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = xmods->max_keypermod;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 3; i < 8; i++) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < n; j++) {
            ଅଚଳ ଚାବି_Code_2 kc = xmods->modifiermap[i * n + j];
            ଯଦି (videodata->keyboard.ଚାବି_layout[kc] == scancode) {
                mod_mask = 1 << i;
                ଭାଙ୍ଗ;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    ଫେରନ୍ତୁ mod_mask;
}

ସ୍ଥିର ଶୂନ୍ୟ X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, ଚାବି_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_ଚାବି_Code_From_ଚାବି_Sym(xkeysym, xkeycode, sdl_mod_mask);

    ଯଦି (!keycode) {
        ବାଛ (sdl_scancode) {
        ସ୍ଥିତି SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            ଭାଙ୍ଗ;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

ଶୂନ୍ୟ X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ଯଦି (data->keyboard.xkb_enabled) {
        XkbStateRec state;

        ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < Xkb_ଅଙ୍କ_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = ଖାଲି;
        }

        X11_XkbGetNames(data->display, XkbVirtualModNamesMask, data->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(data->display, XkbAllClientInfoMask | XkbVirtualModsMask, data->keyboard.xkb.desc_ptr);

        ଯଦି (X11_XkbGetState(data->display, XkbUseCoreKbd, &state) == Success) {
            data->keyboard.xkb.current_group = state.group;
        }

        data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        ଯଦି (!data->keyboard.alt_mask) {
            data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        data->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        data->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        data->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        data->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        data->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < Xkb_ଅଙ୍କ_Kbd_Groups; ++i) {
            data->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            ଯଦି (!data->keyboard.xkb.keymaps[i]) {
                ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
                    data->keyboard.xkb.keymaps[j] = ଖାଲି;
                }

                ଫେରନ୍ତୁ;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ଅଚଳ Uint32 valid_mod_mask = ShiftMask | LockMask | data->keyboard.alt_mask | data->keyboard.level3_mask | data->keyboard.level5_mask;

        ପାଇଁ (Uint32 xkeycode = data->keyboard.xkb.desc_ptr->min_ଚାବି_code; xkeycode < data->keyboard.xkb.desc_ptr->max_ଚାବି_code; ++xkeycode) {
            ଅଚଳ SDL_Scancode scancode = data->keyboard.ଚାବି_layout[xkeycode];
            ଯଦି (scancode == SDL_SCANCODE_UNKNOWN) {
                ଜାରି;
            }

            ପାଇଁ (Uint32 group = 0; group < Xkb_ଅଙ୍କ_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = data->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                ଅଚଳ unsigned ଅକ୍ଷର max_ଚାବି_group = Xkb_ଚାବି_ଅଙ୍କ_Groups(data->keyboard.xkb.desc_ptr, xkeycode);
                ଅଚଳ unsigned ଅକ୍ଷର ଚାବି_group_info = Xkb_ଚାବି_Group_Info(data->keyboard.xkb.desc_ptr, xkeycode);

                ଯଦି (max_ଚାବି_group && effective_group >= max_ଚାବି_group) {
                    ଅଚଳ unsigned ଅକ୍ଷର action = XkbOutOfRangeGroupAction(ଚାବି_group_info);

                    ବାଛ (action) {
                    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
                        effective_group %= max_ଚାବି_group;
                        ଭାଙ୍ଗ;
                    ସ୍ଥିତି XkbClampIntoRange:
                        effective_group = max_ଚାବି_group - 1;
                        ଭାଙ୍ଗ;
                    ସ୍ଥିତି XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_ସଂଖ୍ୟା(ଚାବି_group_info);
                        ଯଦି (effective_group >= max_ଚାବି_group) {
                            effective_group = 0;
                        }
                        ଭାଙ୍ଗ;
                    }
                }

                Xkb_ଚାବି_Type_Ptr ଚାବି_type = Xkb_ଚାବି_ଚାବି_Type(data->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                ପାଇଁ (Uint32 level = 0; level < ଚାବି_type->ଅଙ୍କ_levels; ++level) {
                    ଅଚଳ ଚାବି_Sym keysym = X11_ଚାବି_Code_To_Sym(_this, xkeycode, effective_group, level);

                    ଯଦି (keysym != No_ପ୍ରତୀକ) {
                        bool ଚାବି_added = false;

                        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା map_idx = 0; map_idx < ଚାବି_type->map_ଗଣନା; ++map_idx) {
                            ଯଦି (ଚାବି_type->map[map_idx].active && ଚାବି_type->map[map_idx].level == level) {
                                ଅଚଳ unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା xkb_mod_mask = ଚାବି_type->map[map_idx].mods.mask;
                                ଯଦି ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    ଅଚଳ SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & data->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    ଚାବି_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        ଯଦି (!level && !ଚାବି_added) {
                            X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_SetKeymap(data->keyboard.xkb.keymaps[data->keyboard.xkb.current_group], send_event);
    } ଅନ୍ୟଥା
#endif
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        ଯଦି (!keymap) {
            ଫେରନ୍ତୁ;
        }

        ଯଦି (send_event) {
            ଯଦି (data->keyboard.core.keysym_map) {
                X11_XFree(data->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
            data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                                     data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                                     &data->keyboard.core.keysyms_per_ଚାବି);
        }

        ପାଇଁ (Uint32 xkeycode = data->keyboard.core.min_keycode; xkeycode <= data->keyboard.core.max_keycode; ++xkeycode) {
            ଅଚଳ SDL_Scancode scancode = data->keyboard.ଚାବି_layout[xkeycode];
            ଯଦି (scancode == SDL_SCANCODE_UNKNOWN) {
                ଜାରି;
            }

            ଅଚଳ ଚାବି_Sym keysym = X11_ଚାବି_Code_To_Sym(_this, xkeycode, 0, 0);
            ଯଦି (keysym != No_ପ୍ରତୀକ) {
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

ଶୂନ୍ୟ X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

#ifdef X_HAVE_UTF8_STRING
    ଯଦି (data->im) {
        X11_XCloseIM(data->im);
        data->im = ଖାଲି;
    } ଅନ୍ୟଥା {
        X11_XUnregisterIMInstantiateCallback(data->display, ଖାଲି, ଖାଲି, ଖାଲି, im_instantiate_handler, (XPointer)data);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ଯଦି (data->keyboard.xkb_enabled) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < Xkb_ଅଙ୍କ_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = ଖାଲି;
        }

        ଯଦି (data->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(data->keyboard.xkb.desc_ptr, 0, True);
            data->keyboard.xkb.desc_ptr = ଖାଲି;
        }
    } ଅନ୍ୟଥା
#endif
        ଯଦି (data->keyboard.core.keysym_map) {
        X11_XFree(data->keyboard.core.keysym_map);
        data->keyboard.core.keysym_map = ଖାଲି;
    }
}

ଶୂନ୍ୟ X11_ClearComposition(SDL_WindowData *data)
{
    ଯଦି (data->preedit_length > 0) {
        data->preedit_text[0] = '\0';
        data->preedit_length = 0;
    }

    ଯଦି (data->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        data->ime_needs_clear_composition = false;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ X11_SendEditingEvent(SDL_WindowData *data)
{
    ଯଦି (data->preedit_length == 0) {
        X11_ClearComposition(data);
        ଫେରନ୍ତୁ;
    }

    bool in_highlight = false;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା start = -1, length = 0, i;
    ପାଇଁ (i = 0; i < data->preedit_length; ++i) {
        ଯଦି (data->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            ଯଦି (start < 0) {
                start = i;
                in_highlight = true;
            }
        } ଅନ୍ୟଥା ଯଦି (in_highlight) {
            // Found the end of the highlight
            ଭାଙ୍ଗ;
        }
    }
    ଯଦି (in_highlight) {
        length = (i - start);
    } ଅନ୍ୟଥା {
        start = SDL_clamp(data->preedit_cursor, 0, data->preedit_length);
    }
    SDL_SendEditingText(data->preedit_text, start, length);

    data->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା preedit_start_callback(XIC xic, XPointer client_data, XPointer call_data)
{
    // No limit on preedit text length
    ଫେରନ୍ତୁ -1;
}

ସ୍ଥିର ଶୂନ୍ୟ preedit_done_callback(XIC xic, XPointer client_data, XPointer call_data)
{
}

ସ୍ଥିର ଶୂନ୍ୟ preedit_draw_callback(XIC xic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା chg_first = SDL_clamp(call_data->chg_first, 0, data->preedit_length);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା chg_length = SDL_clamp(call_data->chg_length, 0, data->preedit_length - chg_first);

    ଅଚଳ ଅକ୍ଷର *start = data->preedit_text;
    ଯଦି (chg_length > 0) {
        // Delete text in range
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, ଖାଲି);
        }

        ଅଚଳ ଅକ୍ଷର *end = start;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; end && *end && i < chg_length; ++i) {
            SDL_StepUTF8(&end, ଖାଲି);
        }

        ଯଦି (end > start) {
            SDL_memmove((ଅକ୍ଷର *)start, end, SDL_strlen(end) + 1);
            ଯଦି ((chg_first + chg_length) > data->preedit_length) {
                SDL_memmove(&data->preedit_feedback[chg_first], &data->preedit_feedback[chg_first + chg_length], (data->preedit_length - chg_first - chg_length) * ଆକାର(*data->preedit_feedback));
            }
        }
        data->preedit_length -= chg_length;
    }

    XIMText *text = call_data->text;
    ଯଦି (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        ଯଦି (text->string.multi_byte) {
            text->length = SDL_utf8strlen(text->string.multi_byte);
        }

        size_t string_size = SDL_strlen(text->string.multi_byte);
        size_t size = string_size + 1;
        ଯଦି (data->preedit_text) {
            size += SDL_strlen(data->preedit_text);
        }
        ଅକ୍ଷର *preedit_text = (ଅକ୍ଷର *)SDL_malloc(size * ଆକାର(*preedit_text));
        ଯଦି (preedit_text) {
            size_t pre_size = (start - data->preedit_text);
            size_t post_size = start ? SDL_strlen(start) : 0;
            ଯଦି (pre_size > 0) {
                SDL_memcpy(&preedit_text[0], data->preedit_text, pre_size);
            }
            SDL_memcpy(&preedit_text[pre_size], text->string.multi_byte, string_size);
            ଯଦି (post_size > 0) {
                SDL_memcpy(&preedit_text[pre_size + string_size], start, post_size);
            }
            preedit_text[size - 1] = '\0';
        }

        size_t feedback_size = data->preedit_length + text->length;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_size * ଆକାର(*feedback));
        ଯଦି (feedback) {
            size_t pre_size = (size_t)chg_first;
            size_t post_size = (size_t)data->preedit_length - pre_size;
            ଯଦି (pre_size > 0) {
                SDL_memcpy(&feedback[0], data->preedit_feedback, pre_size * ଆକାର(*feedback));
            }
            SDL_memcpy(&feedback[pre_size], text->feedback, text->length * ଆକାର(*feedback));
            ଯଦି (post_size > 0) {
                SDL_memcpy(&feedback[pre_size + text->length], &data->preedit_feedback[pre_size], post_size * ଆକାର(*feedback));
            }
        }

        ଯଦି (preedit_text && feedback) {
            SDL_free(data->preedit_text);
            data->preedit_text = preedit_text;

            SDL_free(data->preedit_feedback);
            data->preedit_feedback = feedback;

            data->preedit_length += text->length;
        } ଅନ୍ୟଥା {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    data->preedit_cursor = call_data->caret;

#ifdef DEBUG_XIM
    ଯଦି (call_data->chg_length > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_data->chg_length, call_data->chg_first);
    }
    ଯଦି (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_data->chg_first, call_data->caret);
    }
    SDL_Log("Pre-edit text: %s", data->preedit_text);
#endif

    X11_SendEditingEvent(data);
}

ସ୍ଥିର ଶୂନ୍ୟ preedit_caret_callback(XIC xic, XPointer client_data, XIMPreeditCaretCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;

    ବାଛ (call_data->direction) {
    ସ୍ଥିତି XIMAbsolutePosition:
        ଯଦି (call_data->position != data->preedit_cursor) {
            data->preedit_cursor = call_data->position;
            X11_SendEditingEvent(data);
        }
        ଭାଙ୍ଗ;
    ସ୍ଥିତି XIMDontChange:
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        // Not currently supported
        ଭାଙ୍ଗ;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ ic_destroyed_handler(XIC ic, XPointer clientData, XPointer callData)
{
    SDL_WindowData *data = (SDL_WindowData *)clientData;
    data->ic = ଖାଲି;
    X11_Destroy_ନିବେଶ_Context(data);

    // If the IM was already recreated, create a new IC.
    ଯଦି (data->videodata->im) {
        X11_Create_ନିବେଶ_Context(data);
    }
}
#endif // X_HAVE_UTF8_STRING

ଶୂନ୍ୟ X11_Create_ନିବେଶ_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_VideoData *videodata = data->videodata;

    ଯଦି (SDL_X11_HAVE_UTF8 && videodata->im) {
        ଅଚଳ ଅକ୍ଷର *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)data;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        ଯଦି (hint && SDL_strstr(hint, "composition")) {
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
                                                         ଖାଲି);
            ଯଦି (attr) {
                data->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, data->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         ଖାଲି);
                X11_XFree(attr);
            }
        }
        ଯଦି (!data->ic) {
            data->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClientWindow, data->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     ଖାଲି);
        }
        data->xim_spot.x = -1;
        data->xim_spot.y = -1;
    }
#endif // X_HAVE_UTF8_STRING
}


ଶୂନ୍ୟ X11_Destroy_ନିବେଶ_Context(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    ଯଦି (data->ic) {
        X11_XDestroyIC(data->ic);
        data->ic = ଖାଲି;
    }
    SDL_free(data->preedit_text);
    SDL_free(data->preedit_feedback);
    data->preedit_text = ଖାଲି;
    data->preedit_feedback = ଖାଲି;
#endif
}

ସ୍ଥିର ଶୂନ୍ୟ X11_ResetXIM(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    ଯଦି (data && data->ic) {
        // Clear any partially entered dead keys
        ଅକ୍ଷର *contents = X11_Xutf8ResetIC(data->ic);
        ଯଦି (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_ନିବେଶ(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    ଫେରନ୍ତୁ X11_Update_Text_ନିବେଶ_Area(_this, window);
}

bool X11_Stop_Text_ନିବେଶ(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    ଫେରନ୍ତୁ true;
}

bool X11_Update_Text_ନିବେଶ_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    ଯଦି (data && data->ic) {
        XPoint spot;
        spot.x = window->text_ନିବେଶ_rect.x + window->text_ନିବେଶ_cursor;
        spot.y = window->text_ନିବେଶ_rect.y + window->text_ନିବେଶ_rect.h;
        ଯଦି (spot.x != data->xim_spot.x || spot.y != data->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, ଖାଲି);
            ଯଦି (attr) {
                X11_XSetICValues(data->ic, XNPreeditAttributes, attr, ଖାଲି);
                X11_XFree(attr);
            }
            SDL_copyp(&data->xim_spot, &spot);
        }
    }
#endif
    ଫେରନ୍ତୁ true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    ଫେରନ୍ତୁ videodata->use_steam_screen_keyboard;
}

ଶୂନ୍ୟ X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;

    ଯଦି (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା k_EFloating_Gamepad_Text_ନିବେଶ_Mode_Mode_Single_ଧାଡ଼ି = 0;    // Enter dismisses the keyboard
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା k_EFloating_Gamepad_Text_ନିବେଶ_Mode_Mode_Multiple_ଧାଡ଼ିଗୁଡ଼ିକ = 1; // User needs to explicitly dismiss the keyboard
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା k_EFloating_Gamepad_Text_ନିବେଶ_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା k_EFloating_Gamepad_Text_ନିବେଶ_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        ଅକ୍ଷର deeplink[128];
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା mode;

        ବାଛ (SDL_Get_Text_ନିବେଶ_Type(props)) {
        ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_ନିବେଶ_Mode_Mode_Email;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା:
        ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା_PASSWORD_HIDDEN:
        ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_ନିବେଶ_Mode_Mode_Numeric;
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଯଦି (SDL_Get_Text_ନିବେଶ_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_ନିବେଶ_Mode_Mode_Multiple_ଧାଡ଼ିଗୁଡ଼ିକ;
            } ଅନ୍ୟଥା {
                mode = k_EFloating_Gamepad_Text_ନିବେଶ_Mode_Mode_Single_ଧାଡ଼ି;
            }
            ଭାଙ୍ଗ;
        }
        (ଶୂନ୍ୟ)SDL_snprintf(deeplink, ଆକାର(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_ନିବେଶ_rect.x, window->text_ନିବେଶ_rect.y,
                           window->text_ନିବେଶ_rect.w, window->text_ନିବେଶ_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

ଶୂନ୍ୟ X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;

    ଯଦି (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
