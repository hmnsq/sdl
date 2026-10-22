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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "SDL_x11video.h"

#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_scancode_tables_c.h"

#अन्तर्भाव <X11/keysym.h>

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#अन्तर्भाव <X11/XKBlib.h>
#यदि_अन्तः

#अन्तर्भाव "../../events/imKStoUCS.h"
#अन्तर्भाव "../../events/SDL_keysym_to_scancode_c.h"
#अन्तर्भाव "../../events/SDL_keysym_to_keycode_c.h"

#यदि_परिभाषितम् X_HAVE_UTF8_STRING
#अन्तर्भाव <locale.h>
#यदि_अन्तः

स्थिर SDL_Scancode_सारणी scancode_समुच्चयः[] = {
    SDL_SCANCODE_सारणी_DARWIN,
    SDL_SCANCODE_सारणी_XFREE86_1,
    SDL_SCANCODE_सारणी_XFREE86_2,
    SDL_SCANCODE_सारणी_XVNC,
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

स्थिर कुञ्चिका_Sym X11_कुञ्चिका_संहिता_गन्तव्यम्_Sym(SDL_VideoDevice *_this, कुञ्चिका_संहिता_2 keycode, अचिह्नित पूर्णाङ्क गणः, अचिह्नित पूर्णाङ्क level)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    कुञ्चिका_Sym keysym;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    यदि (दत्त->keyboard.xkb_enabled) {
        keysym = X11_Xkb_Keycode_गन्तव्यम्_Keysym(दत्त->display, keycode, गणः, level);
    } अन्यथा
#यदि_अन्तः
    {
        // TODO: Handle groups on the legacy path.
        यदि (keycode >= दत्त->keyboard.core.min_keycode && keycode <= दत्त->keyboard.core.max_keycode) {
            keysym = दत्त->keyboard.core.keysym_map[(keycode - दत्त->keyboard.core.min_keycode) * दत्त->keyboard.core.keysyms_प्रत्येकम्_कुञ्चिका];
        } अन्यथा {
            keysym = No_चिह्नम्;
        }
    }

    प्रत्यागम keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
स्थिर SDL_Scancode X11_कुञ्चिका_संहिता_गन्तव्यम्_SDLScancode(SDL_VideoDevice *_this, कुञ्चिका_संहिता_2 keycode)
{
    ध्रुव कुञ्चिका_Sym keysym = X11_कुञ्चिका_संहिता_गन्तव्यम्_Sym(_this, keycode, 0, 0);

    यदि (keysym == No_चिह्नम्) {
        प्रत्यागम SDL_SCANCODE_UNKNOWN;
    }

    प्रत्यागम SDL_Get_Scancode_From_कुञ्चिका_Sym(keysym, keycode);
}

#यदि_परिभाषितम् X_HAVE_UTF8_STRING
स्थिर bool X11_InitIM(SDL_Video_दत्त *videodata);

स्थिर शून्य im_instantiate_handler(Display *display, XPointer client_दत्त, XPointer call_दत्त)
{
    SDL_Video_दत्त *videodata = (SDL_Video_दत्त *)client_दत्त;

    यदि (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, रिक्त, रिक्त, रिक्त, im_instantiate_handler, client_दत्त);
    }
}

स्थिर शून्य im_destroyed_handler(XIM im, XPointer client_दत्त, XPointer call_दत्त)
{
    SDL_Video_दत्त *videodata = (SDL_Video_दत्त *)client_दत्त;

    videodata->im = रिक्त;
    X11_XRegisterIMInstantiateCallback(videodata->display, रिक्त, रिक्त, रिक्त, im_instantiate_handler, client_दत्त);
}

स्थिर bool X11_InitIM(SDL_Video_दत्त *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    वर्ण *पूर्व_locale = setlocale(LC_ALL, रिक्त);
    वर्ण *पूर्व_xmods = X11_XSetLocaleModifiers(रिक्त);

    यदि (पूर्व_locale) {
        पूर्व_locale = SDL_strdup(पूर्व_locale);
    }

    यदि (पूर्व_xmods) {
        पूर्व_xmods = SDL_strdup(पूर्व_xmods);
    }

    (शून्य)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, रिक्त, रिक्त, रिक्त);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (शून्य)setlocale(LC_ALL, पूर्व_locale);
    X11_XSetLocaleModifiers(पूर्व_xmods);

    SDL_free(पूर्व_locale);
    SDL_free(पूर्व_xmods);

    यदि (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_दत्त_2 = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (वर्ण *)रिक्त);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        प्रति (पूर्णाङ्क i = 0; i < videodata->numwindows; ++i) {
            SDL_गवाक्षः_दत्त *w = videodata->windowlist[i];
            यदि (!w->ic) {
                X11_Create_निवेशः_Context(w);
            }
        }

        प्रत्यागम true;
    }

    प्रत्यागम false;
}
#यदि_अन्तः // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
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
        { SDL_SCANCODE_PAGEUP, XK_प्राक्, 0 },
        { SDL_SCANCODE_ऊर्ध्वम्, XK_ऊर्ध्वम्, 0 },
        { SDL_SCANCODE_वामः, XK_वामः, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    पूर्णाङ्क best_distance;
    पूर्णाङ्क best_सूचकांक;
    पूर्णाङ्क distance;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    पूर्णाङ्क xkb_major = Xkb_Major_संस्करणम्;
    पूर्णाङ्क xkb_minor = Xkb_Minor_संस्करणम्;

    यदि (X11_XkbQueryExtension(दत्त->display, रिक्त, &दत्त->keyboard.xkb.event, रिक्त, &xkb_major, &xkb_minor)) {
        Bool xkb_repeat = 0;
        दत्त->keyboard.xkb_enabled = true;
        दत्त->keyboard.xkb.desc_ptr = X11_XkbGetMap(दत्त->display, Xkb_All_Client_Info_आवरणम्, XkbUseCoreKbd);

        // This will remove KeyRelease events for held keys.
        X11_Xkb_समुच्चयः_Detectable_Auto_Repeat(दत्त->display, True, &xkb_repeat);

        // Enable the key mapping and state events.
        X11_XkbSelectEvents(दत्त->display, XkbUseCoreKbd,
                            Xkb_New_Keyboard_Notify_आवरणम् | Xkb_Map_Notify_आवरणम् | Xkb_State_Notify_आवरणम्,
                            Xkb_New_Keyboard_Notify_आवरणम् | Xkb_Map_Notify_आवरणम् | Xkb_State_Notify_आवरणम्);
        X11_XkbSelectEventDetails(दत्त->display, XkbUseCoreKbd, XkbStateNotify, Xkb_गणः_State_आवरणम् | Xkb_Modifier_State_आवरणम्, Xkb_गणः_State_आवरणम् | Xkb_Modifier_State_आवरणम्);
    } अन्यथा
#यदि_अन्तः
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(दत्त->display, &दत्त->keyboard.core.min_keycode, &दत्त->keyboard.core.max_keycode);
        दत्त->keyboard.core.keysym_map = X11_XGetKeyboardMapping(दत्त->display, दत्त->keyboard.core.min_keycode,
                                                              दत्त->keyboard.core.max_keycode - दत्त->keyboard.core.min_keycode,
                                                              &दत्त->keyboard.core.keysyms_प्रत्येकम्_कुञ्चिका);
    }

    // Open a connection to the X input manager
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    यदि (SDL_X11_HAVE_UTF8) {
        यदि (!X11_InitIM(दत्त)) {
            X11_XRegisterIMInstantiateCallback(दत्त->display, रिक्त, रिक्त, रिक्त, im_instantiate_handler, (XPointer)दत्त);
        }
    }
#यदि_अन्तः
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_सूचकांक = -1;
    X11_XDisplayKeycodes(दत्त->display, &min_keycode, &max_keycode);
    प्रति (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].मानम् = X11_XKeysym_गन्तव्यम्_Keycode(दत्त->display, fingerprint[i].keysym) - min_keycode;
    }
    प्रति (i = 0; i < SDL_arraysize(scancode_समुच्चयः); ++i) {
        पूर्णाङ्क सारणी_आकार;
        ध्रुव SDL_Scancode *सारणी = SDL_Get_Scancode_सारणी(scancode_समुच्चयः[i], &सारणी_आकार);

        distance = 0;
        प्रति (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            यदि (fingerprint[j].मानम् < 0 || fingerprint[j].मानम् >= सारणी_आकार) {
                distance += 1;
            } अन्यथा यदि (सारणी[fingerprint[j].मानम्] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        यदि (distance < best_distance) {
            best_distance = distance;
            best_सूचकांक = i;
        }
    }
    यदि (best_सूचकांक < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        पूर्णाङ्क fingerprint_मानम् = X11_XKeysym_गन्तव्यम्_Keycode(दत्त->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        यदि (fingerprint_मानम् == 235) {
            प्रति (i = 0; i < SDL_arraysize(scancode_समुच्चयः); ++i) {
                यदि (scancode_समुच्चयः[i] == SDL_SCANCODE_सारणी_XFREE86_2) {
                    best_सूचकांक = i;
                    best_distance = 0;
                    भङ्ग;
                }
            }
        }
    }
    यदि (best_सूचकांक >= 0 && best_distance <= 2) {
        पूर्णाङ्क सारणी_आकार;
        ध्रुव SDL_Scancode *सारणी = SDL_Get_Scancode_सारणी(scancode_समुच्चयः[best_सूचकांक], &सारणी_आकार);

#यदि_परिभाषितम् DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_सूचकांक, min_keycode, max_keycode, सारणी_आकार);
#यदि_अन्तः
        // This should never happen, but just in case...
        यदि (सारणी_आकार > (SDL_arraysize(दत्त->keyboard.कुञ्चिका_layout) - min_keycode)) {
            सारणी_आकार = (SDL_arraysize(दत्त->keyboard.कुञ्चिका_layout) - min_keycode);
        }
        SDL_memcpy(&दत्त->keyboard.कुञ्चिका_layout[min_keycode], सारणी, परिमाण(SDL_Scancode) * सारणी_आकार);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        प्रति (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_कुञ्चिका_संहिता_गन्तव्यम्_SDLScancode(_this, i);
#यदि_परिभाषितम् DEBUG_KEYBOARD
            {
                कुञ्चिका_Sym sym;
                sym = X11_कुञ्चिका_संहिता_गन्तव्यम्_Sym(_this, (कुञ्चिका_संहिता_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (अचिह्नित पूर्णाङ्क)sym, sym == No_चिह्नम् ? "NoSymbol" : X11_XKeysym_गन्तव्यम्_String(sym));
            }
#यदि_अन्तः
            यदि (scancode == दत्त->keyboard.कुञ्चिका_layout[i]) {
                अनुवर्त;
            }
            यदि ((SDL_GetKeymapKeycode(रिक्त, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_आवरणम् | SDLK_EXTENDED_आवरणम्)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#यदि_परिभाषितम् DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", दत्त->कुञ्चिका_layout[i], SDL_GetScancodeName(दत्त->कुञ्चिका_layout[i]), scancode, SDL_GetScancodeName(scancode));
#यदि_अन्तः
                दत्त->keyboard.कुञ्चिका_layout[i] = scancode;
            }
        }
    } अन्यथा {
#यदि_परिभाषितम् DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#यदि_अन्तः

        // Determine key_layout - only works on US QWERTY layout
        प्रति (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_कुञ्चिका_संहिता_गन्तव्यम्_SDLScancode(_this, i);
#यदि_परिभाषितम् DEBUG_SCANCODES
            {
                कुञ्चिका_Sym sym;
                sym = X11_कुञ्चिका_संहिता_गन्तव्यम्_Sym(_this, (कुञ्चिका_संहिता_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (अचिह्नित पूर्णाङ्क)sym, sym == No_चिह्नम् ? "NoSymbol" : X11_XKeysym_गन्तव्यम्_String(sym));
            }
            यदि (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } अन्यथा {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#यदि_अन्तः
            दत्त->keyboard.कुञ्चिका_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_समुच्चयः_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    प्रत्यागम true;
}

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
स्थिर अचिह्नित पूर्णाङ्क X11_Get_Xkb_Virtual_Modifier_आवरणम्(SDL_VideoDevice *_this, ध्रुव वर्ण *vmod_name)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    अचिह्नित पूर्णाङ्क mod_आवरणम् = 0;

    ध्रुव Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    यदि (vmod != None) {
        प्रति (पूर्णाङ्क i = 0; i < Xkb_अङ्कः_Virtual_Mods; ++i) {
            यदि (vmod == videodata->keyboard.xkb.desc_ptr->नामानि->vmods[i]) {
                mod_आवरणम् = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                भङ्ग;
            }
        }
    }

    प्रत्यागम mod_आवरणम्;
}
#यदि_अन्तः

स्थिर अचिह्नित X11_Get_XModifier_आवरणम्(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    Display *display = videodata->display;
    अचिह्नित पूर्णाङ्क mod_आवरणम् = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    अचिह्नित पूर्णाङ्क n = xmods->max_keypermod;
    प्रति (पूर्णाङ्क i = 3; i < 8; i++) {
        प्रति (पूर्णाङ्क j = 0; j < n; j++) {
            ध्रुव कुञ्चिका_संहिता_2 kc = xmods->modifiermap[i * n + j];
            यदि (videodata->keyboard.कुञ्चिका_layout[kc] == scancode) {
                mod_आवरणम् = 1 << i;
                भङ्ग;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    प्रत्यागम mod_आवरणम्;
}

स्थिर शून्य X11_सङ्कलय_Keymap_प्रविष्टिः(SDL_Keymap *keymap, Uint32 xkeycode, कुञ्चिका_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_आवरणम्)
{
    SDL_Keycode keycode = SDL_Get_कुञ्चिका_संहिता_From_कुञ्चिका_Sym(xkeysym, xkeycode, sdl_mod_आवरणम्);

    यदि (!keycode) {
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
            keycode = SDL_SCANCODE_गन्तव्यम्_KEYCODE(sdl_scancode);
            भङ्ग;
        }
    }

    SDL_समुच्चयः_Keymap_प्रविष्टिः(keymap, sdl_scancode, sdl_mod_आवरणम्, keycode);
}

शून्य X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    यदि (दत्त->keyboard.xkb_enabled) {
        XkbStateRec state;

        प्रति (अचिह्नित पूर्णाङ्क i = 0; i < Xkb_अङ्कः_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(दत्त->keyboard.xkb.keymaps[i]);
            दत्त->keyboard.xkb.keymaps[i] = रिक्त;
        }

        X11_Xkb_Get_नामानि(दत्त->display, Xkb_Virtual_Mod_नामानि_आवरणम्, दत्त->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(दत्त->display, Xkb_All_Client_Info_आवरणम् | Xkb_Virtual_Mods_आवरणम्, दत्त->keyboard.xkb.desc_ptr);

        यदि (X11_XkbGetState(दत्त->display, XkbUseCoreKbd, &state) == Success) {
            दत्त->keyboard.xkb.current_गणः = state.गणः;
        }

        दत्त->keyboard.alt_आवरणम् = X11_Get_Xkb_Virtual_Modifier_आवरणम्(_this, "Alt");
        यदि (!दत्त->keyboard.alt_आवरणम्) {
            दत्त->keyboard.alt_आवरणम् = X11_Get_Xkb_Virtual_Modifier_आवरणम्(_this, "Meta");
        }
        दत्त->keyboard.gui_आवरणम् = X11_Get_Xkb_Virtual_Modifier_आवरणम्(_this, "Super");
        दत्त->keyboard.level3_आवरणम् = X11_Get_Xkb_Virtual_Modifier_आवरणम्(_this, "LevelThree");
        दत्त->keyboard.level5_आवरणम् = X11_Get_Xkb_Virtual_Modifier_आवरणम्(_this, "LevelFive");
        दत्त->keyboard.numlock_आवरणम् = X11_Get_Xkb_Virtual_Modifier_आवरणम्(_this, "NumLock");
        दत्त->keyboard.scrolllock_आवरणम् = X11_Get_Xkb_Virtual_Modifier_आवरणम्(_this, "ScrollLock");

        प्रति (अचिह्नित पूर्णाङ्क i = 0; i < Xkb_अङ्कः_Kbd_Groups; ++i) {
            दत्त->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            यदि (!दत्त->keyboard.xkb.keymaps[i]) {
                प्रति (अचिह्नित पूर्णाङ्क j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(दत्त->keyboard.xkb.keymaps[i]);
                    दत्त->keyboard.xkb.keymaps[j] = रिक्त;
                }

                प्रत्यागम;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ध्रुव Uint32 valid_mod_आवरणम् = सरणम्_आवरणम्_2 | तालकम्_आवरणम् | दत्त->keyboard.alt_आवरणम् | दत्त->keyboard.level3_आवरणम् | दत्त->keyboard.level5_आवरणम्;

        प्रति (Uint32 xkeycode = दत्त->keyboard.xkb.desc_ptr->min_कुञ्चिका_संहिता; xkeycode < दत्त->keyboard.xkb.desc_ptr->max_कुञ्चिका_संहिता; ++xkeycode) {
            ध्रुव SDL_Scancode scancode = दत्त->keyboard.कुञ्चिका_layout[xkeycode];
            यदि (scancode == SDL_SCANCODE_UNKNOWN) {
                अनुवर्त;
            }

            प्रति (Uint32 गणः = 0; गणः < Xkb_अङ्कः_Kbd_Groups; ++गणः) {
                SDL_Keymap *keymap = दत्त->keyboard.xkb.keymaps[गणः];

                Uint32 effective_गणः = गणः;
                ध्रुव अचिह्नित वर्ण max_कुञ्चिका_गणः = Xkb_कुञ्चिका_अङ्कः_Groups(दत्त->keyboard.xkb.desc_ptr, xkeycode);
                ध्रुव अचिह्नित वर्ण कुञ्चिका_गणः_info = Xkb_कुञ्चिका_गणः_Info(दत्त->keyboard.xkb.desc_ptr, xkeycode);

                यदि (max_कुञ्चिका_गणः && effective_गणः >= max_कुञ्चिका_गणः) {
                    ध्रुव अचिह्नित वर्ण action = Xkb_बहिर्गमनम्_सम्बन्धि_Range_गणः_Action(कुञ्चिका_गणः_info);

                    विकल्प (action) {
                    स्वभाव:
                        effective_गणः %= max_कुञ्चिका_गणः;
                        भङ्ग;
                    पक्ष XkbClampIntoRange:
                        effective_गणः = max_कुञ्चिका_गणः - 1;
                        भङ्ग;
                    पक्ष XkbRedirectIntoRange:
                        effective_गणः = Xkb_बहिर्गमनम्_सम्बन्धि_Range_गणः_सङ्ख्या(कुञ्चिका_गणः_info);
                        यदि (effective_गणः >= max_कुञ्चिका_गणः) {
                            effective_गणः = 0;
                        }
                        भङ्ग;
                    }
                }

                Xkb_कुञ्चिका_Type_Ptr कुञ्चिका_type = Xkb_कुञ्चिका_कुञ्चिका_Type(दत्त->keyboard.xkb.desc_ptr, xkeycode, effective_गणः);

                प्रति (Uint32 level = 0; level < कुञ्चिका_type->अङ्कः_स्तराः; ++level) {
                    ध्रुव कुञ्चिका_Sym keysym = X11_कुञ्चिका_संहिता_गन्तव्यम्_Sym(_this, xkeycode, effective_गणः, level);

                    यदि (keysym != No_चिह्नम्) {
                        bool कुञ्चिका_added = false;

                        प्रति (पूर्णाङ्क map_idx = 0; map_idx < कुञ्चिका_type->map_गणनम्; ++map_idx) {
                            यदि (कुञ्चिका_type->map[map_idx].सक्रिय && कुञ्चिका_type->map[map_idx].level == level) {
                                ध्रुव अचिह्नित पूर्णाङ्क xkb_mod_आवरणम् = कुञ्चिका_type->map[map_idx].mods.आवरणम्;
                                यदि ((xkb_mod_आवरणम् | valid_mod_आवरणम्) == valid_mod_आवरणम्) {
                                    ध्रुव SDL_Keymod sdl_mod_आवरणम् = (xkb_mod_आवरणम् & सरणम्_आवरणम्_2 ? SDL_KMOD_सरणम् : 0) |
                                                                    (xkb_mod_आवरणम् & तालकम्_आवरणम् ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_आवरणम् & दत्त->keyboard.alt_आवरणम् ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_आवरणम् & दत्त->keyboard.level3_आवरणम् ? SDL_KMOD_बहुलकम् : 0) |
                                                                    (xkb_mod_आवरणम् & दत्त->keyboard.level5_आवरणम् ? SDL_KMOD_LEVEL5 : 0);

                                    X11_सङ्कलय_Keymap_प्रविष्टिः(keymap, xkeycode, keysym, scancode, sdl_mod_आवरणम्);
                                    कुञ्चिका_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        यदि (!level && !कुञ्चिका_added) {
                            X11_सङ्कलय_Keymap_प्रविष्टिः(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_समुच्चयः_Keymap(दत्त->keyboard.xkb.keymaps[दत्त->keyboard.xkb.current_गणः], send_event);
    } अन्यथा
#यदि_अन्तः
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        यदि (!keymap) {
            प्रत्यागम;
        }

        यदि (send_event) {
            यदि (दत्त->keyboard.core.keysym_map) {
                X11_XFree(दत्त->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(दत्त->display, &दत्त->keyboard.core.min_keycode, &दत्त->keyboard.core.max_keycode);
            दत्त->keyboard.core.keysym_map = X11_XGetKeyboardMapping(दत्त->display, दत्त->keyboard.core.min_keycode,
                                                                     दत्त->keyboard.core.max_keycode - दत्त->keyboard.core.min_keycode,
                                                                     &दत्त->keyboard.core.keysyms_प्रत्येकम्_कुञ्चिका);
        }

        प्रति (Uint32 xkeycode = दत्त->keyboard.core.min_keycode; xkeycode <= दत्त->keyboard.core.max_keycode; ++xkeycode) {
            ध्रुव SDL_Scancode scancode = दत्त->keyboard.कुञ्चिका_layout[xkeycode];
            यदि (scancode == SDL_SCANCODE_UNKNOWN) {
                अनुवर्त;
            }

            ध्रुव कुञ्चिका_Sym keysym = X11_कुञ्चिका_संहिता_गन्तव्यम्_Sym(_this, xkeycode, 0, 0);
            यदि (keysym != No_चिह्नम्) {
                X11_सङ्कलय_Keymap_प्रविष्टिः(keymap, xkeycode, keysym, scancode, 0);
            }
        }

        दत्त->keyboard.alt_आवरणम् = Mod1_आवरणम्; // Alt or Meta
        दत्त->keyboard.gui_आवरणम् = Mod4_आवरणम्; // Super
        दत्त->keyboard.level3_आवरणम् = Mod5_आवरणम्; // Note: Not a typo, Mod5 = level 3 shift, and Mod3 = level 5 shift.
        दत्त->keyboard.level5_आवरणम् = Mod3_आवरणम्;
        दत्त->keyboard.numlock_आवरणम् = X11_Get_XModifier_आवरणम्(_this, SDL_SCANCODE_NUMLOCKCLEAR);
        दत्त->keyboard.scrolllock_आवरणम् = X11_Get_XModifier_आवरणम्(_this, SDL_SCANCODE_SCROLLLOCK);

        SDL_समुच्चयः_Keymap(keymap, send_event);
    }
}

शून्य X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    यदि (दत्त->im) {
        X11_XCloseIM(दत्त->im);
        दत्त->im = रिक्त;
    } अन्यथा {
        X11_XUnregisterIMInstantiateCallback(दत्त->display, रिक्त, रिक्त, रिक्त, im_instantiate_handler, (XPointer)दत्त);
    }
#यदि_अन्तः // X_HAVE_UTF8_STRING

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    यदि (दत्त->keyboard.xkb_enabled) {
        प्रति (पूर्णाङ्क i = 0; i < Xkb_अङ्कः_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(दत्त->keyboard.xkb.keymaps[i]);
            दत्त->keyboard.xkb.keymaps[i] = रिक्त;
        }

        यदि (दत्त->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(दत्त->keyboard.xkb.desc_ptr, 0, True);
            दत्त->keyboard.xkb.desc_ptr = रिक्त;
        }
    } अन्यथा
#यदि_अन्तः
        यदि (दत्त->keyboard.core.keysym_map) {
        X11_XFree(दत्त->keyboard.core.keysym_map);
        दत्त->keyboard.core.keysym_map = रिक्त;
    }
}

शून्य X11_ClearComposition(SDL_गवाक्षः_दत्त *दत्त)
{
    यदि (दत्त->preedit_दीर्घता > 0) {
        दत्त->preedit_text[0] = '\0';
        दत्त->preedit_दीर्घता = 0;
    }

    यदि (दत्त->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        दत्त->ime_needs_clear_composition = false;
    }
}

स्थिर शून्य X11_SendEditingEvent(SDL_गवाक्षः_दत्त *दत्त)
{
    यदि (दत्त->preedit_दीर्घता == 0) {
        X11_ClearComposition(दत्त);
        प्रत्यागम;
    }

    bool अन्तर्_highlight = false;
    पूर्णाङ्क start = -1, दीर्घता = 0, i;
    प्रति (i = 0; i < दत्त->preedit_दीर्घता; ++i) {
        यदि (दत्त->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            यदि (start < 0) {
                start = i;
                अन्तर्_highlight = true;
            }
        } अन्यथा यदि (अन्तर्_highlight) {
            // Found the end of the highlight
            भङ्ग;
        }
    }
    यदि (अन्तर्_highlight) {
        दीर्घता = (i - start);
    } अन्यथा {
        start = SDL_clamp(दत्त->preedit_cursor, 0, दत्त->preedit_दीर्घता);
    }
    SDL_SendEditingText(दत्त->preedit_text, start, दीर्घता);

    दत्त->ime_needs_clear_composition = true;
}

#यदि_परिभाषितम् X_HAVE_UTF8_STRING
स्थिर पूर्णाङ्क preedit_start_callback(XIC xic, XPointer client_दत्त_2, XPointer call_दत्त_2)
{
    // No limit on preedit text length
    प्रत्यागम -1;
}

स्थिर शून्य preedit_समाप्तम्_callback(XIC xic, XPointer client_दत्त_2, XPointer call_दत्त_2)
{
}

स्थिर शून्य preedit_draw_callback(XIC xic, XPointer client_दत्त_2, XIMPreeditDrawCallbackStruct *call_दत्त_2)
{
    SDL_गवाक्षः_दत्त *दत्त = (SDL_गवाक्षः_दत्त *)client_दत्त_2;
    पूर्णाङ्क chg_first = SDL_clamp(call_दत्त_2->chg_first, 0, दत्त->preedit_दीर्घता);
    पूर्णाङ्क chg_दीर्घता = SDL_clamp(call_दत्त_2->chg_दीर्घता, 0, दत्त->preedit_दीर्घता - chg_first);

    ध्रुव वर्ण *start = दत्त->preedit_text;
    यदि (chg_दीर्घता > 0) {
        // Delete text in range
        प्रति (पूर्णाङ्क i = 0; start && *start && i < chg_first; ++i) {
            SDL_चरणः_UTF8(&start, रिक्त);
        }

        ध्रुव वर्ण *अन्तः = start;
        प्रति (पूर्णाङ्क i = 0; अन्तः && *अन्तः && i < chg_दीर्घता; ++i) {
            SDL_चरणः_UTF8(&अन्तः, रिक्त);
        }

        यदि (अन्तः > start) {
            SDL_memmove((वर्ण *)start, अन्तः, SDL_strlen(अन्तः) + 1);
            यदि ((chg_first + chg_दीर्घता) > दत्त->preedit_दीर्घता) {
                SDL_memmove(&दत्त->preedit_feedback[chg_first], &दत्त->preedit_feedback[chg_first + chg_दीर्घता], (दत्त->preedit_दीर्घता - chg_first - chg_दीर्घता) * परिमाण(*दत्त->preedit_feedback));
            }
        }
        दत्त->preedit_दीर्घता -= chg_दीर्घता;
    }

    XIMText *text = call_दत्त_2->text;
    यदि (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        यदि (text->string.multi_byte) {
            text->दीर्घता = SDL_utf8strlen(text->string.multi_byte);
        }

        size_t string_आकार = SDL_strlen(text->string.multi_byte);
        size_t आकार = string_आकार + 1;
        यदि (दत्त->preedit_text) {
            आकार += SDL_strlen(दत्त->preedit_text);
        }
        वर्ण *preedit_text = (वर्ण *)SDL_malloc(आकार * परिमाण(*preedit_text));
        यदि (preedit_text) {
            size_t pre_आकार = (start - दत्त->preedit_text);
            size_t post_आकार = start ? SDL_strlen(start) : 0;
            यदि (pre_आकार > 0) {
                SDL_memcpy(&preedit_text[0], दत्त->preedit_text, pre_आकार);
            }
            SDL_memcpy(&preedit_text[pre_आकार], text->string.multi_byte, string_आकार);
            यदि (post_आकार > 0) {
                SDL_memcpy(&preedit_text[pre_आकार + string_आकार], start, post_आकार);
            }
            preedit_text[आकार - 1] = '\0';
        }

        size_t feedback_आकार = दत्त->preedit_दीर्घता + text->दीर्घता;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_आकार * परिमाण(*feedback));
        यदि (feedback) {
            size_t pre_आकार = (size_t)chg_first;
            size_t post_आकार = (size_t)दत्त->preedit_दीर्घता - pre_आकार;
            यदि (pre_आकार > 0) {
                SDL_memcpy(&feedback[0], दत्त->preedit_feedback, pre_आकार * परिमाण(*feedback));
            }
            SDL_memcpy(&feedback[pre_आकार], text->feedback, text->दीर्घता * परिमाण(*feedback));
            यदि (post_आकार > 0) {
                SDL_memcpy(&feedback[pre_आकार + text->दीर्घता], &दत्त->preedit_feedback[pre_आकार], post_आकार * परिमाण(*feedback));
            }
        }

        यदि (preedit_text && feedback) {
            SDL_free(दत्त->preedit_text);
            दत्त->preedit_text = preedit_text;

            SDL_free(दत्त->preedit_feedback);
            दत्त->preedit_feedback = feedback;

            दत्त->preedit_दीर्घता += text->दीर्घता;
        } अन्यथा {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    दत्त->preedit_cursor = call_दत्त_2->caret;

#यदि_परिभाषितम् DEBUG_XIM
    यदि (call_दत्त_2->chg_दीर्घता > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_दत्त_2->chg_दीर्घता, call_दत्त_2->chg_first);
    }
    यदि (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_दत्त_2->chg_first, call_दत्त_2->caret);
    }
    SDL_Log("Pre-edit text: %s", दत्त->preedit_text);
#यदि_अन्तः

    X11_SendEditingEvent(दत्त);
}

स्थिर शून्य preedit_caret_callback(XIC xic, XPointer client_दत्त_2, XIMPreeditCaretCallbackStruct *call_दत्त_2)
{
    SDL_गवाक्षः_दत्त *दत्त = (SDL_गवाक्षः_दत्त *)client_दत्त_2;

    विकल्प (call_दत्त_2->direction) {
    पक्ष XIMAbsolutePosition:
        यदि (call_दत्त_2->position != दत्त->preedit_cursor) {
            दत्त->preedit_cursor = call_दत्त_2->position;
            X11_SendEditingEvent(दत्त);
        }
        भङ्ग;
    पक्ष XIMDontChange:
        भङ्ग;
    स्वभाव:
        // Not currently supported
        भङ्ग;
    }
}

स्थिर शून्य ic_destroyed_handler(XIC ic, XPointer client_दत्त, XPointer call_दत्त)
{
    SDL_गवाक्षः_दत्त *दत्त = (SDL_गवाक्षः_दत्त *)client_दत्त;
    दत्त->ic = रिक्त;
    X11_Destroy_निवेशः_Context(दत्त);

    // If the IM was already recreated, create a new IC.
    यदि (दत्त->videodata->im) {
        X11_Create_निवेशः_Context(दत्त);
    }
}
#यदि_अन्तः // X_HAVE_UTF8_STRING

शून्य X11_Create_निवेशः_Context(SDL_गवाक्षः_दत्त *दत्त)
{
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    SDL_Video_दत्त *videodata = दत्त->videodata;

    यदि (SDL_X11_HAVE_UTF8 && videodata->im) {
        ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_दत्त_2 = (XPointer)दत्त;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        यदि (hint && SDL_strstr(hint, "composition")) {
            XIMCallback draw_callback;
            draw_callback.client_दत्त_2 = (XPointer)दत्त;
            draw_callback.callback = (XIMProc)preedit_draw_callback;

            XIMCallback start_callback;
            start_callback.client_दत्त_2 = (XPointer)दत्त;
            start_callback.callback = (XIMProc)preedit_start_callback;

            XIMCallback समाप्तम्_callback;
            समाप्तम्_callback.client_दत्त_2 = (XPointer)दत्त;
            समाप्तम्_callback.callback = (XIMProc)preedit_समाप्तम्_callback;

            XIMCallback caret_callback;
            caret_callback.client_दत्त_2 = (XPointer)दत्त;
            caret_callback.callback = (XIMProc)preedit_caret_callback;

            XVaNestedList attr = X11_XVaCreateNestedList(0,
                                                         XNPreeditStartCallback, &start_callback,
                                                         XNPreedit_समाप्तम्_Callback, &समाप्तम्_callback,
                                                         XNPreeditDrawCallback, &draw_callback,
                                                         XNPreeditCaretCallback, &caret_callback,
                                                         रिक्त);
            यदि (attr) {
                दत्त->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreedit_गुणाः, attr,
                                         XNClient_गवाक्षः, दत्त->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         रिक्त);
                X11_XFree(attr);
            }
        }
        यदि (!दत्त->ic) {
            दत्त->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClient_गवाक्षः, दत्त->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     रिक्त);
        }
        दत्त->xim_spot.x = -1;
        दत्त->xim_spot.y = -1;
    }
#यदि_अन्तः // X_HAVE_UTF8_STRING
}


शून्य X11_Destroy_निवेशः_Context(SDL_गवाक्षः_दत्त *दत्त)
{
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    यदि (दत्त->ic) {
        X11_XDestroyIC(दत्त->ic);
        दत्त->ic = रिक्त;
    }
    SDL_free(दत्त->preedit_text);
    SDL_free(दत्त->preedit_feedback);
    दत्त->preedit_text = रिक्त;
    दत्त->preedit_feedback = रिक्त;
#यदि_अन्तः
}

स्थिर शून्य X11_ResetXIM(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    यदि (दत्त && दत्त->ic) {
        // Clear any partially entered dead keys
        वर्ण *contents = X11_Xutf8ResetIC(दत्त->ic);
        यदि (contents) {
            X11_XFree(contents);
        }
    }
#यदि_अन्तः // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_निवेशः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, गवाक्षः);

    प्रत्यागम X11_Update_Text_निवेशः_Area(_this, गवाक्षः);
}

bool X11_Stop_Text_निवेशः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    X11_ResetXIM(_this, गवाक्षः);
    प्रत्यागम true;
}

bool X11_Update_Text_निवेशः_Area(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    यदि (दत्त && दत्त->ic) {
        XPoint spot;
        spot.x = गवाक्षः->text_निवेशः_rect.x + गवाक्षः->text_निवेशः_cursor;
        spot.y = गवाक्षः->text_निवेशः_rect.y + गवाक्षः->text_निवेशः_rect.h;
        यदि (spot.x != दत्त->xim_spot.x || spot.y != दत्त->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, रिक्त);
            यदि (attr) {
                X11_XSetICValues(दत्त->ic, XNPreedit_गुणाः, attr, रिक्त);
                X11_XFree(attr);
            }
            SDL_copyp(&दत्त->xim_spot, &spot);
        }
    }
#यदि_अन्तः
    प्रत्यागम true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    प्रत्यागम videodata->use_steam_screen_keyboard;
}

शून्य X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;

    यदि (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ध्रुव पूर्णाङ्क k_EFloating_Gamepad_Text_निवेशः_बहुलकम्_बहुलकम्_Single_पङ्क्तिः = 0;    // Enter dismisses the keyboard
        ध्रुव पूर्णाङ्क k_EFloating_Gamepad_Text_निवेशः_बहुलकम्_बहुलकम्_गुणजः_पङ्क्तयः = 1; // User needs to explicitly dismiss the keyboard
        ध्रुव पूर्णाङ्क k_EFloating_Gamepad_Text_निवेशः_बहुलकम्_बहुलकम्_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ध्रुव पूर्णाङ्क k_EFloating_Gamepad_Text_निवेशः_बहुलकम्_बहुलकम्_Numeric = 3;       // Numeric keypad is shown
        वर्ण deeplink[128];
        पूर्णाङ्क बहुलकम्;

        विकल्प (SDL_Get_Text_निवेशः_Type(props)) {
        पक्ष SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            बहुलकम् = k_EFloating_Gamepad_Text_निवेशः_बहुलकम्_बहुलकम्_Email;
            भङ्ग;
        पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या:
        पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_HIDDEN:
        पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_VISIBLE:
            बहुलकम् = k_EFloating_Gamepad_Text_निवेशः_बहुलकम्_बहुलकम्_Numeric;
            भङ्ग;
        स्वभाव:
            यदि (SDL_Get_Text_निवेशः_Multiline(props)) {
                बहुलकम् = k_EFloating_Gamepad_Text_निवेशः_बहुलकम्_बहुलकम्_गुणजः_पङ्क्तयः;
            } अन्यथा {
                बहुलकम् = k_EFloating_Gamepad_Text_निवेशः_बहुलकम्_बहुलकम्_Single_पङ्क्तिः;
            }
            भङ्ग;
        }
        (शून्य)SDL_snprintf(deeplink, परिमाण(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           गवाक्षः->text_निवेशः_rect.x, गवाक्षः->text_निवेशः_rect.y,
                           गवाक्षः->text_निवेशः_rect.w, गवाक्षः->text_निवेशः_rect.h,
                           बहुलकम्);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

शून्य X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;

    यदि (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
