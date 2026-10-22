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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#समावेश "SDL_x11video.h"

#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/SDL_scancode_tables_c.h"

#समावेश <X11/keysym.h>

#अगर_घोषित SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#समावेश <X11/XKBlib.h>
#पूर्ण_अगर

#समावेश "../../events/imKStoUCS.h"
#समावेश "../../events/SDL_keysym_to_scancode_c.h"
#समावेश "../../events/SDL_keysym_to_keycode_c.h"

#अगर_घोषित X_HAVE_UTF8_STRING
#समावेश <locale.h>
#पूर्ण_अगर

अटल SDL_ScancodeTable scancode_set[] = {
    SDL_SCANCODE_TABLE_DARWIN,
    SDL_SCANCODE_TABLE_XFREE86_1,
    SDL_SCANCODE_TABLE_XFREE86_2,
    SDL_SCANCODE_TABLE_XVNC,
};

अटल bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    चयन (scancode) {
    हाल SDL_SCANCODE_ESCAPE:
    हाल SDL_SCANCODE_CAPSLOCK:
    हाल SDL_SCANCODE_NUMLOCKCLEAR:
    हाल SDL_SCANCODE_LSHIFT:
    हाल SDL_SCANCODE_RSHIFT:
    हाल SDL_SCANCODE_LCTRL:
    हाल SDL_SCANCODE_RCTRL:
    हाल SDL_SCANCODE_LALT:
    हाल SDL_SCANCODE_RALT:
    हाल SDL_SCANCODE_LGUI:
    हाल SDL_SCANCODE_RGUI:
        वापस false;
    शेष:
        वापस true;
    }
}

अटल कुंजी_Sym X11_कुंजी_Code_To_Sym(SDL_VideoDevice *_this, कुंजी_Code_2 keycode, अचिन्हित पूर्णांक group, अचिन्हित पूर्णांक level)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    कुंजी_Sym keysym;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    अगर (तथ्य->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(तथ्य->display, keycode, group, level);
    } अन्यथा
#पूर्ण_अगर
    {
        // TODO: Handle groups on the legacy path.
        अगर (keycode >= तथ्य->keyboard.core.min_keycode && keycode <= तथ्य->keyboard.core.max_keycode) {
            keysym = तथ्य->keyboard.core.keysym_map[(keycode - तथ्य->keyboard.core.min_keycode) * तथ्य->keyboard.core.keysyms_per_कुंजी];
        } अन्यथा {
            keysym = No_प्रतीक;
        }
    }

    वापस keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
अटल SDL_Scancode X11_कुंजी_Code_To_SDLScancode(SDL_VideoDevice *_this, कुंजी_Code_2 keycode)
{
    स्थिर कुंजी_Sym keysym = X11_कुंजी_Code_To_Sym(_this, keycode, 0, 0);

    अगर (keysym == No_प्रतीक) {
        वापस SDL_SCANCODE_UNKNOWN;
    }

    वापस SDL_Get_Scancode_From_कुंजी_Sym(keysym, keycode);
}

#अगर_घोषित X_HAVE_UTF8_STRING
अटल bool X11_InitIM(SDL_Video_तथ्य *videodata);

अटल व्योम im_instantiate_handler(Display *display, XPointer client_तथ्य, XPointer call_तथ्य)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)client_तथ्य;

    अगर (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, शून्य, शून्य, शून्य, im_instantiate_handler, client_तथ्य);
    }
}

अटल व्योम im_destroyed_handler(XIM im, XPointer client_तथ्य, XPointer call_तथ्य)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)client_तथ्य;

    videodata->im = शून्य;
    X11_XRegisterIMInstantiateCallback(videodata->display, शून्य, शून्य, शून्य, im_instantiate_handler, client_तथ्य);
}

अटल bool X11_InitIM(SDL_Video_तथ्य *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    अक्षर *पूर्व_locale = रखो_क्षेत्र(LC_ALL, शून्य);
    अक्षर *पूर्व_xmods = X11_XSetLocaleModifiers(शून्य);

    अगर (पूर्व_locale) {
        पूर्व_locale = SDL_strdup(पूर्व_locale);
    }

    अगर (पूर्व_xmods) {
        पूर्व_xmods = SDL_strdup(पूर्व_xmods);
    }

    (व्योम)रखो_क्षेत्र(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, शून्य, शून्य, शून्य);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (व्योम)रखो_क्षेत्र(LC_ALL, पूर्व_locale);
    X11_XSetLocaleModifiers(पूर्व_xmods);

    SDL_free(पूर्व_locale);
    SDL_free(पूर्व_xmods);

    अगर (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_तथ्य_2 = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (अक्षर *)शून्य);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        क्रम (पूर्णांक i = 0; i < videodata->numwindows; ++i) {
            SDL_Window_तथ्य *w = videodata->windowlist[i];
            अगर (!w->ic) {
                X11_Create_निवेश_Context(w);
            }
        }

        वापस true;
    }

    वापस false;
}
#पूर्ण_अगर // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    पूर्णांक i = 0;
    पूर्णांक j = 0;
    पूर्णांक min_keycode, max_keycode;
    काष्ठा
    {
        SDL_Scancode scancode;
        कुंजी_Sym keysym;
        पूर्णांक मूल्य;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_बायाँ, XK_बायाँ, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    पूर्णांक best_distance;
    पूर्णांक best_सूचकांक;
    पूर्णांक distance;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    पूर्णांक xkb_major = XkbMajorVersion;
    पूर्णांक xkb_minor = XkbMinorVersion;

    अगर (X11_XkbQueryExtension(तथ्य->display, शून्य, &तथ्य->keyboard.xkb.event, शून्य, &xkb_major, &xkb_minor)) {
        Bool xkb_repeat = 0;
        तथ्य->keyboard.xkb_enabled = true;
        तथ्य->keyboard.xkb.desc_ptr = X11_XkbGetMap(तथ्य->display, XkbAllClientInfoMask, XkbUseCoreKbd);

        // This will remove KeyRelease events for held keys.
        X11_XkbSetDetectableAutoRepeat(तथ्य->display, True, &xkb_repeat);

        // Enable the key mapping and state events.
        X11_XkbSelectEvents(तथ्य->display, XkbUseCoreKbd,
                            XkbNewKeyboardNotifyMask | XkbMapNotifyMask | XkbStateNotifyMask,
                            XkbNewKeyboardNotifyMask | XkbMapNotifyMask | XkbStateNotifyMask);
        X11_XkbSelectEventDetails(तथ्य->display, XkbUseCoreKbd, XkbStateNotify, XkbGroupStateMask | XkbModifierStateMask, XkbGroupStateMask | XkbModifierStateMask);
    } अन्यथा
#पूर्ण_अगर
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(तथ्य->display, &तथ्य->keyboard.core.min_keycode, &तथ्य->keyboard.core.max_keycode);
        तथ्य->keyboard.core.keysym_map = X11_XGetKeyboardMapping(तथ्य->display, तथ्य->keyboard.core.min_keycode,
                                                              तथ्य->keyboard.core.max_keycode - तथ्य->keyboard.core.min_keycode,
                                                              &तथ्य->keyboard.core.keysyms_per_कुंजी);
    }

    // Open a connection to the X input manager
#अगर_घोषित X_HAVE_UTF8_STRING
    अगर (SDL_X11_HAVE_UTF8) {
        अगर (!X11_InitIM(तथ्य)) {
            X11_XRegisterIMInstantiateCallback(तथ्य->display, शून्य, शून्य, शून्य, im_instantiate_handler, (XPointer)तथ्य);
        }
    }
#पूर्ण_अगर
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_सूचकांक = -1;
    X11_XDisplayKeycodes(तथ्य->display, &min_keycode, &max_keycode);
    क्रम (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].मूल्य = X11_XKeysymToKeycode(तथ्य->display, fingerprint[i].keysym) - min_keycode;
    }
    क्रम (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        पूर्णांक table_आकार;
        स्थिर SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_आकार);

        distance = 0;
        क्रम (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            अगर (fingerprint[j].मूल्य < 0 || fingerprint[j].मूल्य >= table_आकार) {
                distance += 1;
            } अन्यथा अगर (table[fingerprint[j].मूल्य] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        अगर (distance < best_distance) {
            best_distance = distance;
            best_सूचकांक = i;
        }
    }
    अगर (best_सूचकांक < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        पूर्णांक fingerprint_मूल्य = X11_XKeysymToKeycode(तथ्य->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        अगर (fingerprint_मूल्य == 235) {
            क्रम (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                अगर (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_सूचकांक = i;
                    best_distance = 0;
                    अवरोध;
                }
            }
        }
    }
    अगर (best_सूचकांक >= 0 && best_distance <= 2) {
        पूर्णांक table_आकार;
        स्थिर SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_सूचकांक], &table_आकार);

#अगर_घोषित DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_सूचकांक, min_keycode, max_keycode, table_आकार);
#पूर्ण_अगर
        // This should never happen, but just in case...
        अगर (table_आकार > (SDL_arraysize(तथ्य->keyboard.कुंजी_layout) - min_keycode)) {
            table_आकार = (SDL_arraysize(तथ्य->keyboard.कुंजी_layout) - min_keycode);
        }
        SDL_memcpy(&तथ्य->keyboard.कुंजी_layout[min_keycode], table, माप(SDL_Scancode) * table_आकार);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        क्रम (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_कुंजी_Code_To_SDLScancode(_this, i);
#अगर_घोषित DEBUG_KEYBOARD
            {
                कुंजी_Sym sym;
                sym = X11_कुंजी_Code_To_Sym(_this, (कुंजी_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (अचिन्हित पूर्णांक)sym, sym == No_प्रतीक ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#पूर्ण_अगर
            अगर (scancode == तथ्य->keyboard.कुंजी_layout[i]) {
                जारी;
            }
            अगर ((SDL_GetKeymapKeycode(शून्य, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#अगर_घोषित DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", तथ्य->कुंजी_layout[i], SDL_GetScancodeName(तथ्य->कुंजी_layout[i]), scancode, SDL_GetScancodeName(scancode));
#पूर्ण_अगर
                तथ्य->keyboard.कुंजी_layout[i] = scancode;
            }
        }
    } अन्यथा {
#अगर_घोषित DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#पूर्ण_अगर

        // Determine key_layout - only works on US QWERTY layout
        क्रम (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_कुंजी_Code_To_SDLScancode(_this, i);
#अगर_घोषित DEBUG_SCANCODES
            {
                कुंजी_Sym sym;
                sym = X11_कुंजी_Code_To_Sym(_this, (कुंजी_Code_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (अचिन्हित पूर्णांक)sym, sym == No_प्रतीक ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            अगर (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } अन्यथा {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#पूर्ण_अगर
            तथ्य->keyboard.कुंजी_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    वापस true;
}

#अगर_घोषित SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
अटल अचिन्हित पूर्णांक X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, स्थिर अक्षर *vmod_name)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    अचिन्हित पूर्णांक mod_mask = 0;

    स्थिर Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    अगर (vmod != None) {
        क्रम (पूर्णांक i = 0; i < Xkb_अंक_Virtual_Mods; ++i) {
            अगर (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                अवरोध;
            }
        }
    }

    वापस mod_mask;
}
#पूर्ण_अगर

अटल अचिन्हित X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    Display *display = videodata->display;
    अचिन्हित पूर्णांक mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    अचिन्हित पूर्णांक n = xmods->max_keypermod;
    क्रम (पूर्णांक i = 3; i < 8; i++) {
        क्रम (पूर्णांक j = 0; j < n; j++) {
            स्थिर कुंजी_Code_2 kc = xmods->modifiermap[i * n + j];
            अगर (videodata->keyboard.कुंजी_layout[kc] == scancode) {
                mod_mask = 1 << i;
                अवरोध;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    वापस mod_mask;
}

अटल व्योम X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, कुंजी_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_Get_कुंजी_Code_From_कुंजी_Sym(xkeysym, xkeycode, sdl_mod_mask);

    अगर (!keycode) {
        चयन (sdl_scancode) {
        हाल SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            अवरोध;
        हाल SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            अवरोध;
        हाल SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            अवरोध;
        हाल SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            अवरोध;
        शेष:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            अवरोध;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

व्योम X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    अगर (तथ्य->keyboard.xkb_enabled) {
        XkbStateRec state;

        क्रम (अचिन्हित पूर्णांक i = 0; i < Xkb_अंक_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(तथ्य->keyboard.xkb.keymaps[i]);
            तथ्य->keyboard.xkb.keymaps[i] = शून्य;
        }

        X11_XkbGetNames(तथ्य->display, XkbVirtualModNamesMask, तथ्य->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(तथ्य->display, XkbAllClientInfoMask | XkbVirtualModsMask, तथ्य->keyboard.xkb.desc_ptr);

        अगर (X11_XkbGetState(तथ्य->display, XkbUseCoreKbd, &state) == Success) {
            तथ्य->keyboard.xkb.current_group = state.group;
        }

        तथ्य->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        अगर (!तथ्य->keyboard.alt_mask) {
            तथ्य->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        तथ्य->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        तथ्य->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        तथ्य->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        तथ्य->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        तथ्य->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        क्रम (अचिन्हित पूर्णांक i = 0; i < Xkb_अंक_Kbd_Groups; ++i) {
            तथ्य->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            अगर (!तथ्य->keyboard.xkb.keymaps[i]) {
                क्रम (अचिन्हित पूर्णांक j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(तथ्य->keyboard.xkb.keymaps[i]);
                    तथ्य->keyboard.xkb.keymaps[j] = शून्य;
                }

                वापस;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        स्थिर Uint32 valid_mod_mask = ShiftMask | LockMask | तथ्य->keyboard.alt_mask | तथ्य->keyboard.level3_mask | तथ्य->keyboard.level5_mask;

        क्रम (Uint32 xkeycode = तथ्य->keyboard.xkb.desc_ptr->min_कुंजी_code; xkeycode < तथ्य->keyboard.xkb.desc_ptr->max_कुंजी_code; ++xkeycode) {
            स्थिर SDL_Scancode scancode = तथ्य->keyboard.कुंजी_layout[xkeycode];
            अगर (scancode == SDL_SCANCODE_UNKNOWN) {
                जारी;
            }

            क्रम (Uint32 group = 0; group < Xkb_अंक_Kbd_Groups; ++group) {
                SDL_Keymap *keymap = तथ्य->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                स्थिर अचिन्हित अक्षर max_कुंजी_group = Xkb_कुंजी_अंक_Groups(तथ्य->keyboard.xkb.desc_ptr, xkeycode);
                स्थिर अचिन्हित अक्षर कुंजी_group_info = Xkb_कुंजी_Group_Info(तथ्य->keyboard.xkb.desc_ptr, xkeycode);

                अगर (max_कुंजी_group && effective_group >= max_कुंजी_group) {
                    स्थिर अचिन्हित अक्षर action = XkbOutOfRangeGroupAction(कुंजी_group_info);

                    चयन (action) {
                    शेष:
                        effective_group %= max_कुंजी_group;
                        अवरोध;
                    हाल XkbClampIntoRange:
                        effective_group = max_कुंजी_group - 1;
                        अवरोध;
                    हाल XkbRedirectIntoRange:
                        effective_group = Xkb_Out_Of_Range_Group_संख्या(कुंजी_group_info);
                        अगर (effective_group >= max_कुंजी_group) {
                            effective_group = 0;
                        }
                        अवरोध;
                    }
                }

                Xkb_कुंजी_Type_Ptr कुंजी_type = Xkb_कुंजी_कुंजी_Type(तथ्य->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                क्रम (Uint32 level = 0; level < कुंजी_type->अंक_levels; ++level) {
                    स्थिर कुंजी_Sym keysym = X11_कुंजी_Code_To_Sym(_this, xkeycode, effective_group, level);

                    अगर (keysym != No_प्रतीक) {
                        bool कुंजी_added = false;

                        क्रम (पूर्णांक map_idx = 0; map_idx < कुंजी_type->map_गिनती; ++map_idx) {
                            अगर (कुंजी_type->map[map_idx].active && कुंजी_type->map[map_idx].level == level) {
                                स्थिर अचिन्हित पूर्णांक xkb_mod_mask = कुंजी_type->map[map_idx].mods.mask;
                                अगर ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    स्थिर SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & तथ्य->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & तथ्य->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & तथ्य->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    कुंजी_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        अगर (!level && !कुंजी_added) {
                            X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_SetKeymap(तथ्य->keyboard.xkb.keymaps[तथ्य->keyboard.xkb.current_group], send_event);
    } अन्यथा
#पूर्ण_अगर
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        अगर (!keymap) {
            वापस;
        }

        अगर (send_event) {
            अगर (तथ्य->keyboard.core.keysym_map) {
                X11_XFree(तथ्य->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(तथ्य->display, &तथ्य->keyboard.core.min_keycode, &तथ्य->keyboard.core.max_keycode);
            तथ्य->keyboard.core.keysym_map = X11_XGetKeyboardMapping(तथ्य->display, तथ्य->keyboard.core.min_keycode,
                                                                     तथ्य->keyboard.core.max_keycode - तथ्य->keyboard.core.min_keycode,
                                                                     &तथ्य->keyboard.core.keysyms_per_कुंजी);
        }

        क्रम (Uint32 xkeycode = तथ्य->keyboard.core.min_keycode; xkeycode <= तथ्य->keyboard.core.max_keycode; ++xkeycode) {
            स्थिर SDL_Scancode scancode = तथ्य->keyboard.कुंजी_layout[xkeycode];
            अगर (scancode == SDL_SCANCODE_UNKNOWN) {
                जारी;
            }

            स्थिर कुंजी_Sym keysym = X11_कुंजी_Code_To_Sym(_this, xkeycode, 0, 0);
            अगर (keysym != No_प्रतीक) {
                X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
            }
        }

        तथ्य->keyboard.alt_mask = Mod1Mask; // Alt or Meta
        तथ्य->keyboard.gui_mask = Mod4Mask; // Super
        तथ्य->keyboard.level3_mask = Mod5Mask; // Note: Not a typo, Mod5 = level 3 shift, and Mod3 = level 5 shift.
        तथ्य->keyboard.level5_mask = Mod3Mask;
        तथ्य->keyboard.numlock_mask = X11_GetXModifierMask(_this, SDL_SCANCODE_NUMLOCKCLEAR);
        तथ्य->keyboard.scrolllock_mask = X11_GetXModifierMask(_this, SDL_SCANCODE_SCROLLLOCK);

        SDL_SetKeymap(keymap, send_event);
    }
}

व्योम X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

#अगर_घोषित X_HAVE_UTF8_STRING
    अगर (तथ्य->im) {
        X11_XCloseIM(तथ्य->im);
        तथ्य->im = शून्य;
    } अन्यथा {
        X11_XUnregisterIMInstantiateCallback(तथ्य->display, शून्य, शून्य, शून्य, im_instantiate_handler, (XPointer)तथ्य);
    }
#पूर्ण_अगर // X_HAVE_UTF8_STRING

#अगर_घोषित SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    अगर (तथ्य->keyboard.xkb_enabled) {
        क्रम (पूर्णांक i = 0; i < Xkb_अंक_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(तथ्य->keyboard.xkb.keymaps[i]);
            तथ्य->keyboard.xkb.keymaps[i] = शून्य;
        }

        अगर (तथ्य->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(तथ्य->keyboard.xkb.desc_ptr, 0, True);
            तथ्य->keyboard.xkb.desc_ptr = शून्य;
        }
    } अन्यथा
#पूर्ण_अगर
        अगर (तथ्य->keyboard.core.keysym_map) {
        X11_XFree(तथ्य->keyboard.core.keysym_map);
        तथ्य->keyboard.core.keysym_map = शून्य;
    }
}

व्योम X11_ClearComposition(SDL_Window_तथ्य *तथ्य)
{
    अगर (तथ्य->preedit_लंबाई > 0) {
        तथ्य->preedit_text[0] = '\0';
        तथ्य->preedit_लंबाई = 0;
    }

    अगर (तथ्य->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        तथ्य->ime_needs_clear_composition = false;
    }
}

अटल व्योम X11_SendEditingEvent(SDL_Window_तथ्य *तथ्य)
{
    अगर (तथ्य->preedit_लंबाई == 0) {
        X11_ClearComposition(तथ्य);
        वापस;
    }

    bool in_highlight = false;
    पूर्णांक start = -1, लंबाई = 0, i;
    क्रम (i = 0; i < तथ्य->preedit_लंबाई; ++i) {
        अगर (तथ्य->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            अगर (start < 0) {
                start = i;
                in_highlight = true;
            }
        } अन्यथा अगर (in_highlight) {
            // Found the end of the highlight
            अवरोध;
        }
    }
    अगर (in_highlight) {
        लंबाई = (i - start);
    } अन्यथा {
        start = SDL_clamp(तथ्य->preedit_cursor, 0, तथ्य->preedit_लंबाई);
    }
    SDL_SendEditingText(तथ्य->preedit_text, start, लंबाई);

    तथ्य->ime_needs_clear_composition = true;
}

#अगर_घोषित X_HAVE_UTF8_STRING
अटल पूर्णांक preedit_start_callback(XIC xic, XPointer client_तथ्य_2, XPointer call_तथ्य_2)
{
    // No limit on preedit text length
    वापस -1;
}

अटल व्योम preedit_done_callback(XIC xic, XPointer client_तथ्य_2, XPointer call_तथ्य_2)
{
}

अटल व्योम preedit_draw_callback(XIC xic, XPointer client_तथ्य_2, XIMPreeditDrawCallbackStruct *call_तथ्य_2)
{
    SDL_Window_तथ्य *तथ्य = (SDL_Window_तथ्य *)client_तथ्य_2;
    पूर्णांक chg_first = SDL_clamp(call_तथ्य_2->chg_first, 0, तथ्य->preedit_लंबाई);
    पूर्णांक chg_लंबाई = SDL_clamp(call_तथ्य_2->chg_लंबाई, 0, तथ्य->preedit_लंबाई - chg_first);

    स्थिर अक्षर *start = तथ्य->preedit_text;
    अगर (chg_लंबाई > 0) {
        // Delete text in range
        क्रम (पूर्णांक i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, शून्य);
        }

        स्थिर अक्षर *end = start;
        क्रम (पूर्णांक i = 0; end && *end && i < chg_लंबाई; ++i) {
            SDL_StepUTF8(&end, शून्य);
        }

        अगर (end > start) {
            SDL_memmove((अक्षर *)start, end, SDL_strlen(end) + 1);
            अगर ((chg_first + chg_लंबाई) > तथ्य->preedit_लंबाई) {
                SDL_memmove(&तथ्य->preedit_feedback[chg_first], &तथ्य->preedit_feedback[chg_first + chg_लंबाई], (तथ्य->preedit_लंबाई - chg_first - chg_लंबाई) * माप(*तथ्य->preedit_feedback));
            }
        }
        तथ्य->preedit_लंबाई -= chg_लंबाई;
    }

    XIMText *text = call_तथ्य_2->text;
    अगर (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        अगर (text->string.multi_byte) {
            text->लंबाई = SDL_utf8strlen(text->string.multi_byte);
        }

        माप_प्रकार string_आकार = SDL_strlen(text->string.multi_byte);
        माप_प्रकार आकार = string_आकार + 1;
        अगर (तथ्य->preedit_text) {
            आकार += SDL_strlen(तथ्य->preedit_text);
        }
        अक्षर *preedit_text = (अक्षर *)SDL_malloc(आकार * माप(*preedit_text));
        अगर (preedit_text) {
            माप_प्रकार pre_आकार = (start - तथ्य->preedit_text);
            माप_प्रकार post_आकार = start ? SDL_strlen(start) : 0;
            अगर (pre_आकार > 0) {
                SDL_memcpy(&preedit_text[0], तथ्य->preedit_text, pre_आकार);
            }
            SDL_memcpy(&preedit_text[pre_आकार], text->string.multi_byte, string_आकार);
            अगर (post_आकार > 0) {
                SDL_memcpy(&preedit_text[pre_आकार + string_आकार], start, post_आकार);
            }
            preedit_text[आकार - 1] = '\0';
        }

        माप_प्रकार feedback_आकार = तथ्य->preedit_लंबाई + text->लंबाई;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_आकार * माप(*feedback));
        अगर (feedback) {
            माप_प्रकार pre_आकार = (माप_प्रकार)chg_first;
            माप_प्रकार post_आकार = (माप_प्रकार)तथ्य->preedit_लंबाई - pre_आकार;
            अगर (pre_आकार > 0) {
                SDL_memcpy(&feedback[0], तथ्य->preedit_feedback, pre_आकार * माप(*feedback));
            }
            SDL_memcpy(&feedback[pre_आकार], text->feedback, text->लंबाई * माप(*feedback));
            अगर (post_आकार > 0) {
                SDL_memcpy(&feedback[pre_आकार + text->लंबाई], &तथ्य->preedit_feedback[pre_आकार], post_आकार * माप(*feedback));
            }
        }

        अगर (preedit_text && feedback) {
            SDL_free(तथ्य->preedit_text);
            तथ्य->preedit_text = preedit_text;

            SDL_free(तथ्य->preedit_feedback);
            तथ्य->preedit_feedback = feedback;

            तथ्य->preedit_लंबाई += text->लंबाई;
        } अन्यथा {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    तथ्य->preedit_cursor = call_तथ्य_2->caret;

#अगर_घोषित DEBUG_XIM
    अगर (call_तथ्य_2->chg_लंबाई > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_तथ्य_2->chg_लंबाई, call_तथ्य_2->chg_first);
    }
    अगर (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_तथ्य_2->chg_first, call_तथ्य_2->caret);
    }
    SDL_Log("Pre-edit text: %s", तथ्य->preedit_text);
#पूर्ण_अगर

    X11_SendEditingEvent(तथ्य);
}

अटल व्योम preedit_caret_callback(XIC xic, XPointer client_तथ्य_2, XIMPreeditCaretCallbackStruct *call_तथ्य_2)
{
    SDL_Window_तथ्य *तथ्य = (SDL_Window_तथ्य *)client_तथ्य_2;

    चयन (call_तथ्य_2->direction) {
    हाल XIMAbsolutePosition:
        अगर (call_तथ्य_2->position != तथ्य->preedit_cursor) {
            तथ्य->preedit_cursor = call_तथ्य_2->position;
            X11_SendEditingEvent(तथ्य);
        }
        अवरोध;
    हाल XIMDontChange:
        अवरोध;
    शेष:
        // Not currently supported
        अवरोध;
    }
}

अटल व्योम ic_destroyed_handler(XIC ic, XPointer client_तथ्य, XPointer call_तथ्य)
{
    SDL_Window_तथ्य *तथ्य = (SDL_Window_तथ्य *)client_तथ्य;
    तथ्य->ic = शून्य;
    X11_Destroy_निवेश_Context(तथ्य);

    // If the IM was already recreated, create a new IC.
    अगर (तथ्य->videodata->im) {
        X11_Create_निवेश_Context(तथ्य);
    }
}
#पूर्ण_अगर // X_HAVE_UTF8_STRING

व्योम X11_Create_निवेश_Context(SDL_Window_तथ्य *तथ्य)
{
#अगर_घोषित X_HAVE_UTF8_STRING
    SDL_Video_तथ्य *videodata = तथ्य->videodata;

    अगर (SDL_X11_HAVE_UTF8 && videodata->im) {
        स्थिर अक्षर *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_तथ्य_2 = (XPointer)तथ्य;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        अगर (hint && SDL_strstr(hint, "composition")) {
            XIMCallback draw_callback;
            draw_callback.client_तथ्य_2 = (XPointer)तथ्य;
            draw_callback.callback = (XIMProc)preedit_draw_callback;

            XIMCallback start_callback;
            start_callback.client_तथ्य_2 = (XPointer)तथ्य;
            start_callback.callback = (XIMProc)preedit_start_callback;

            XIMCallback done_callback;
            done_callback.client_तथ्य_2 = (XPointer)तथ्य;
            done_callback.callback = (XIMProc)preedit_done_callback;

            XIMCallback caret_callback;
            caret_callback.client_तथ्य_2 = (XPointer)तथ्य;
            caret_callback.callback = (XIMProc)preedit_caret_callback;

            XVaNestedList attr = X11_XVaCreateNestedList(0,
                                                         XNPreeditStartCallback, &start_callback,
                                                         XNPreeditDoneCallback, &done_callback,
                                                         XNPreeditDrawCallback, &draw_callback,
                                                         XNPreeditCaretCallback, &caret_callback,
                                                         शून्य);
            अगर (attr) {
                तथ्य->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, तथ्य->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         शून्य);
                X11_XFree(attr);
            }
        }
        अगर (!तथ्य->ic) {
            तथ्य->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClientWindow, तथ्य->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     शून्य);
        }
        तथ्य->xim_spot.x = -1;
        तथ्य->xim_spot.y = -1;
    }
#पूर्ण_अगर // X_HAVE_UTF8_STRING
}


व्योम X11_Destroy_निवेश_Context(SDL_Window_तथ्य *तथ्य)
{
#अगर_घोषित X_HAVE_UTF8_STRING
    अगर (तथ्य->ic) {
        X11_XDestroyIC(तथ्य->ic);
        तथ्य->ic = शून्य;
    }
    SDL_free(तथ्य->preedit_text);
    SDL_free(तथ्य->preedit_feedback);
    तथ्य->preedit_text = शून्य;
    तथ्य->preedit_feedback = शून्य;
#पूर्ण_अगर
}

अटल व्योम X11_ResetXIM(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर_घोषित X_HAVE_UTF8_STRING
    SDL_Window_तथ्य *तथ्य = window->internal;

    अगर (तथ्य && तथ्य->ic) {
        // Clear any partially entered dead keys
        अक्षर *contents = X11_Xutf8ResetIC(तथ्य->ic);
        अगर (contents) {
            X11_XFree(contents);
        }
    }
#पूर्ण_अगर // X_HAVE_UTF8_STRING
}

bool X11_Start_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    वापस X11_Update_Text_निवेश_Area(_this, window);
}

bool X11_Stop_Text_निवेश(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    वापस true;
}

bool X11_Update_Text_निवेश_Area(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर_घोषित X_HAVE_UTF8_STRING
    SDL_Window_तथ्य *तथ्य = window->internal;

    अगर (तथ्य && तथ्य->ic) {
        XPoint spot;
        spot.x = window->text_निवेश_rect.x + window->text_निवेश_cursor;
        spot.y = window->text_निवेश_rect.y + window->text_निवेश_rect.h;
        अगर (spot.x != तथ्य->xim_spot.x || spot.y != तथ्य->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, शून्य);
            अगर (attr) {
                X11_XSetICValues(तथ्य->ic, XNPreeditAttributes, attr, शून्य);
                X11_XFree(attr);
            }
            SDL_copyp(&तथ्य->xim_spot, &spot);
        }
    }
#पूर्ण_अगर
    वापस true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    वापस videodata->use_steam_screen_keyboard;
}

व्योम X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_Video_तथ्य *videodata = _this->internal;

    अगर (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        स्थिर पूर्णांक k_EFloating_Gamepad_Text_निवेश_Mode_Mode_Single_पंक्ति = 0;    // Enter dismisses the keyboard
        स्थिर पूर्णांक k_EFloating_Gamepad_Text_निवेश_Mode_Mode_Multiple_पंक्तियाँ = 1; // User needs to explicitly dismiss the keyboard
        स्थिर पूर्णांक k_EFloating_Gamepad_Text_निवेश_Mode_Mode_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        स्थिर पूर्णांक k_EFloating_Gamepad_Text_निवेश_Mode_Mode_Numeric = 3;       // Numeric keypad is shown
        अक्षर deeplink[128];
        पूर्णांक mode;

        चयन (SDL_Get_Text_निवेश_Type(props)) {
        हाल SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloating_Gamepad_Text_निवेश_Mode_Mode_Email;
            अवरोध;
        हाल SDL_TEXTINPUT_TYPE_संख्या:
        हाल SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_HIDDEN:
        हाल SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_VISIBLE:
            mode = k_EFloating_Gamepad_Text_निवेश_Mode_Mode_Numeric;
            अवरोध;
        शेष:
            अगर (SDL_Get_Text_निवेश_Multiline(props)) {
                mode = k_EFloating_Gamepad_Text_निवेश_Mode_Mode_Multiple_पंक्तियाँ;
            } अन्यथा {
                mode = k_EFloating_Gamepad_Text_निवेश_Mode_Mode_Single_पंक्ति;
            }
            अवरोध;
        }
        (व्योम)SDL_snprintf(deeplink, माप(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_निवेश_rect.x, window->text_निवेश_rect.y,
                           window->text_निवेश_rect.w, window->text_निवेश_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

व्योम X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *videodata = _this->internal;

    अगर (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11
