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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ "SDL_x11video.h"

#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_scancode_tables_c.h"

#అన్తర్భావ <X11/keysym.h>

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#అన్తర్భావ <X11/XKBlib.h>
#అయితే_ముగింపు

#అన్తర్భావ "../../events/imKStoUCS.h"
#అన్తర్భావ "../../events/SDL_keysym_to_scancode_c.h"
#అన్తర్భావ "../../events/SDL_keysym_to_keycode_c.h"

#నిర్వచితమైతే X_HAVE_UTF8_STRING
#అన్తర్భావ <locale.h>
#అయితే_ముగింపు

స్థిర SDL_Scancode_పట్టిక scancode_సమితి[] = {
    SDL_SCANCODE_పట్టిక_DARWIN,
    SDL_SCANCODE_పట్టిక_XFREE86_1,
    SDL_SCANCODE_పట్టిక_XFREE86_2,
    SDL_SCANCODE_పట్టిక_XVNC,
};

స్థిర bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    ఎంపిక (scancode) {
    స్థితి SDL_SCANCODE_ESCAPE:
    స్థితి SDL_SCANCODE_CAPSLOCK:
    స్థితి SDL_SCANCODE_NUMLOCKCLEAR:
    స్థితి SDL_SCANCODE_LSHIFT:
    స్థితి SDL_SCANCODE_RSHIFT:
    స్థితి SDL_SCANCODE_LCTRL:
    స్థితి SDL_SCANCODE_RCTRL:
    స్థితి SDL_SCANCODE_LALT:
    స్థితి SDL_SCANCODE_RALT:
    స్థితి SDL_SCANCODE_LGUI:
    స్థితి SDL_SCANCODE_RGUI:
        తిరిగి false;
    అప్రమేయ:
        తిరిగి true;
    }
}

స్థిర కీలకం_Sym X11_కీలకం_సంకేతం_గమ్యం_Sym(SDL_VideoDevice *_this, కీలకం_సంకేతం_2 keycode, గుర్తులేని పూర్ణాంకం సమూహం, గుర్తులేని పూర్ణాంకం level)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    కీలకం_Sym keysym;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ఒకవేళ (దత్తాంశం->keyboard.xkb_enabled) {
        keysym = X11_Xkb_Keycode_గమ్యం_Keysym(దత్తాంశం->display, keycode, సమూహం, level);
    } లేకపోతే
#అయితే_ముగింపు
    {
        // TODO: Handle groups on the legacy path.
        ఒకవేళ (keycode >= దత్తాంశం->keyboard.core.min_keycode && keycode <= దత్తాంశం->keyboard.core.max_keycode) {
            keysym = దత్తాంశం->keyboard.core.keysym_map[(keycode - దత్తాంశం->keyboard.core.min_keycode) * దత్తాంశం->keyboard.core.keysyms_చొప్పున_కీలకం];
        } లేకపోతే {
            keysym = No_చిహ్నం;
        }
    }

    తిరిగి keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
స్థిర SDL_Scancode X11_కీలకం_సంకేతం_గమ్యం_SDLScancode(SDL_VideoDevice *_this, కీలకం_సంకేతం_2 keycode)
{
    స్థిరరాశి కీలకం_Sym keysym = X11_కీలకం_సంకేతం_గమ్యం_Sym(_this, keycode, 0, 0);

    ఒకవేళ (keysym == No_చిహ్నం) {
        తిరిగి SDL_SCANCODE_UNKNOWN;
    }

    తిరిగి SDL_Get_Scancode_From_కీలకం_Sym(keysym, keycode);
}

#నిర్వచితమైతే X_HAVE_UTF8_STRING
స్థిర bool X11_InitIM(SDL_Video_దత్తాంశం *videodata);

స్థిర శూన్య im_instantiate_handler(Display *display, XPointer client_దత్తాంశం, XPointer call_దత్తాంశం)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)client_దత్తాంశం;

    ఒకవేళ (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, ఖాళీ, ఖాళీ, ఖాళీ, im_instantiate_handler, client_దత్తాంశం);
    }
}

స్థిర శూన్య im_destroyed_handler(XIM im, XPointer client_దత్తాంశం, XPointer call_దత్తాంశం)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)client_దత్తాంశం;

    videodata->im = ఖాళీ;
    X11_XRegisterIMInstantiateCallback(videodata->display, ఖాళీ, ఖాళీ, ఖాళీ, im_instantiate_handler, client_దత్తాంశం);
}

స్థిర bool X11_InitIM(SDL_Video_దత్తాంశం *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    అక్షరం *prev_locale = setlocale(LC_ALL, ఖాళీ);
    అక్షరం *prev_xmods = X11_XSetLocaleModifiers(ఖాళీ);

    ఒకవేళ (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    ఒకవేళ (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (శూన్య)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, ఖాళీ, ఖాళీ, ఖాళీ);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (శూన్య)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    ఒకవేళ (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_దత్తాంశం_2 = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (అక్షరం *)ఖాళీ);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        కొరకు (పూర్ణాంకం i = 0; i < videodata->numwindows; ++i) {
            SDL_కిటికీ_దత్తాంశం *w = videodata->windowlist[i];
            ఒకవేళ (!w->ic) {
                X11_Create_ఆదానం_Context(w);
            }
        }

        తిరిగి true;
    }

    తిరిగి false;
}
#అయితే_ముగింపు // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    పూర్ణాంకం i = 0;
    పూర్ణాంకం j = 0;
    పూర్ణాంకం min_keycode, max_keycode;
    నిర్మాణం
    {
        SDL_Scancode scancode;
        కీలకం_Sym keysym;
        పూర్ణాంకం విలువ;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_పూర్వ, 0 },
        { SDL_SCANCODE_పైకి, XK_పైకి, 0 },
        { SDL_SCANCODE_ఎడమ, XK_ఎడమ, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    పూర్ణాంకం ఉత్తమ_దూరం;
    పూర్ణాంకం ఉత్తమ_సూచీ;
    పూర్ణాంకం దూరం;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    పూర్ణాంకం xkb_major = Xkb_Major_సంస్కరణ;
    పూర్ణాంకం xkb_minor = Xkb_Minor_సంస్కరణ;

    ఒకవేళ (X11_XkbQueryExtension(దత్తాంశం->display, ఖాళీ, &దత్తాంశం->keyboard.xkb.event, ఖాళీ, &xkb_major, &xkb_minor)) {
        Bool xkb_repeat = 0;
        దత్తాంశం->keyboard.xkb_enabled = true;
        దత్తాంశం->keyboard.xkb.desc_ptr = X11_XkbGetMap(దత్తాంశం->display, Xkb_All_Client_Info_ముసుగు, XkbUseCoreKbd);

        // This will remove KeyRelease events for held keys.
        X11_Xkb_సమితి_Detectable_Auto_Repeat(దత్తాంశం->display, True, &xkb_repeat);

        // Enable the key mapping and state events.
        X11_XkbSelectEvents(దత్తాంశం->display, XkbUseCoreKbd,
                            Xkb_New_Keyboard_Notify_ముసుగు | Xkb_Map_Notify_ముసుగు | Xkb_State_Notify_ముసుగు,
                            Xkb_New_Keyboard_Notify_ముసుగు | Xkb_Map_Notify_ముసుగు | Xkb_State_Notify_ముసుగు);
        X11_XkbSelectEventDetails(దత్తాంశం->display, XkbUseCoreKbd, XkbStateNotify, Xkb_సమూహం_State_ముసుగు | Xkb_Modifier_State_ముసుగు, Xkb_సమూహం_State_ముసుగు | Xkb_Modifier_State_ముసుగు);
    } లేకపోతే
#అయితే_ముగింపు
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(దత్తాంశం->display, &దత్తాంశం->keyboard.core.min_keycode, &దత్తాంశం->keyboard.core.max_keycode);
        దత్తాంశం->keyboard.core.keysym_map = X11_XGetKeyboardMapping(దత్తాంశం->display, దత్తాంశం->keyboard.core.min_keycode,
                                                              దత్తాంశం->keyboard.core.max_keycode - దత్తాంశం->keyboard.core.min_keycode,
                                                              &దత్తాంశం->keyboard.core.keysyms_చొప్పున_కీలకం);
    }

    // Open a connection to the X input manager
#నిర్వచితమైతే X_HAVE_UTF8_STRING
    ఒకవేళ (SDL_X11_HAVE_UTF8) {
        ఒకవేళ (!X11_InitIM(దత్తాంశం)) {
            X11_XRegisterIMInstantiateCallback(దత్తాంశం->display, ఖాళీ, ఖాళీ, ఖాళీ, im_instantiate_handler, (XPointer)దత్తాంశం);
        }
    }
#అయితే_ముగింపు
    // Try to determine which scancodes are being used based on fingerprint
    ఉత్తమ_దూరం = SDL_arraysize(fingerprint) + 1;
    ఉత్తమ_సూచీ = -1;
    X11_XDisplayKeycodes(దత్తాంశం->display, &min_keycode, &max_keycode);
    కొరకు (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].విలువ = X11_XKeysym_గమ్యం_Keycode(దత్తాంశం->display, fingerprint[i].keysym) - min_keycode;
    }
    కొరకు (i = 0; i < SDL_arraysize(scancode_సమితి); ++i) {
        పూర్ణాంకం పట్టిక_కొలత;
        స్థిరరాశి SDL_Scancode *పట్టిక = SDL_Get_Scancode_పట్టిక(scancode_సమితి[i], &పట్టిక_కొలత);

        దూరం = 0;
        కొరకు (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            ఒకవేళ (fingerprint[j].విలువ < 0 || fingerprint[j].విలువ >= పట్టిక_కొలత) {
                దూరం += 1;
            } లేకపోతే ఒకవేళ (పట్టిక[fingerprint[j].విలువ] != fingerprint[j].scancode) {
                దూరం += 1;
            }
        }
        ఒకవేళ (దూరం < ఉత్తమ_దూరం) {
            ఉత్తమ_దూరం = దూరం;
            ఉత్తమ_సూచీ = i;
        }
    }
    ఒకవేళ (ఉత్తమ_సూచీ < 0 || ఉత్తమ_దూరం > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        పూర్ణాంకం fingerprint_విలువ = X11_XKeysym_గమ్యం_Keycode(దత్తాంశం->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        ఒకవేళ (fingerprint_విలువ == 235) {
            కొరకు (i = 0; i < SDL_arraysize(scancode_సమితి); ++i) {
                ఒకవేళ (scancode_సమితి[i] == SDL_SCANCODE_పట్టిక_XFREE86_2) {
                    ఉత్తమ_సూచీ = i;
                    ఉత్తమ_దూరం = 0;
                    ఆపు;
                }
            }
        }
    }
    ఒకవేళ (ఉత్తమ_సూచీ >= 0 && ఉత్తమ_దూరం <= 2) {
        పూర్ణాంకం పట్టిక_కొలత;
        స్థిరరాశి SDL_Scancode *పట్టిక = SDL_Get_Scancode_పట్టిక(scancode_సమితి[ఉత్తమ_సూచీ], &పట్టిక_కొలత);

#నిర్వచితమైతే DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", ఉత్తమ_సూచీ, min_keycode, max_keycode, పట్టిక_కొలత);
#అయితే_ముగింపు
        // This should never happen, but just in case...
        ఒకవేళ (పట్టిక_కొలత > (SDL_arraysize(దత్తాంశం->keyboard.కీలకం_layout) - min_keycode)) {
            పట్టిక_కొలత = (SDL_arraysize(దత్తాంశం->keyboard.కీలకం_layout) - min_keycode);
        }
        SDL_memcpy(&దత్తాంశం->keyboard.కీలకం_layout[min_keycode], పట్టిక, పరిమాణం(SDL_Scancode) * పట్టిక_కొలత);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        కొరకు (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_కీలకం_సంకేతం_గమ్యం_SDLScancode(_this, i);
#నిర్వచితమైతే DEBUG_KEYBOARD
            {
                కీలకం_Sym sym;
                sym = X11_కీలకం_సంకేతం_గమ్యం_Sym(_this, (కీలకం_సంకేతం_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (గుర్తులేని పూర్ణాంకం)sym, sym == No_చిహ్నం ? "NoSymbol" : X11_XKeysym_గమ్యం_String(sym));
            }
#అయితే_ముగింపు
            ఒకవేళ (scancode == దత్తాంశం->keyboard.కీలకం_layout[i]) {
                కొనసాగు;
            }
            ఒకవేళ ((SDL_GetKeymapKeycode(ఖాళీ, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_ముసుగు | SDLK_EXTENDED_ముసుగు)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#నిర్వచితమైతే DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", దత్తాంశం->కీలకం_layout[i], SDL_GetScancodeName(దత్తాంశం->కీలకం_layout[i]), scancode, SDL_GetScancodeName(scancode));
#అయితే_ముగింపు
                దత్తాంశం->keyboard.కీలకం_layout[i] = scancode;
            }
        }
    } లేకపోతే {
#నిర్వచితమైతే DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#అయితే_ముగింపు

        // Determine key_layout - only works on US QWERTY layout
        కొరకు (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_కీలకం_సంకేతం_గమ్యం_SDLScancode(_this, i);
#నిర్వచితమైతే DEBUG_SCANCODES
            {
                కీలకం_Sym sym;
                sym = X11_కీలకం_సంకేతం_గమ్యం_Sym(_this, (కీలకం_సంకేతం_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (గుర్తులేని పూర్ణాంకం)sym, sym == No_చిహ్నం ? "NoSymbol" : X11_XKeysym_గమ్యం_String(sym));
            }
            ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } లేకపోతే {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#అయితే_ముగింపు
            దత్తాంశం->keyboard.కీలకం_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_సమితి_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    తిరిగి true;
}

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
స్థిర గుర్తులేని పూర్ణాంకం X11_Get_Xkb_Virtual_Modifier_ముసుగు(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *vmod_name)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    గుర్తులేని పూర్ణాంకం mod_ముసుగు = 0;

    స్థిరరాశి Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    ఒకవేళ (vmod != None) {
        కొరకు (పూర్ణాంకం i = 0; i < Xkb_అంకె_Virtual_Mods; ++i) {
            ఒకవేళ (vmod == videodata->keyboard.xkb.desc_ptr->పేర్లు->vmods[i]) {
                mod_ముసుగు = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                ఆపు;
            }
        }
    }

    తిరిగి mod_ముసుగు;
}
#అయితే_ముగింపు

స్థిర గుర్తులేని X11_Get_XModifier_ముసుగు(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    Display *display = videodata->display;
    గుర్తులేని పూర్ణాంకం mod_ముసుగు = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    గుర్తులేని పూర్ణాంకం n = xmods->max_keypermod;
    కొరకు (పూర్ణాంకం i = 3; i < 8; i++) {
        కొరకు (పూర్ణాంకం j = 0; j < n; j++) {
            స్థిరరాశి కీలకం_సంకేతం_2 kc = xmods->modifiermap[i * n + j];
            ఒకవేళ (videodata->keyboard.కీలకం_layout[kc] == scancode) {
                mod_ముసుగు = 1 << i;
                ఆపు;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    తిరిగి mod_ముసుగు;
}

స్థిర శూన్య X11_కూడు_Keymap_నమోదు(SDL_Keymap *keymap, Uint32 xkeycode, కీలకం_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_ముసుగు)
{
    SDL_Keycode keycode = SDL_Get_కీలకం_సంకేతం_From_కీలకం_Sym(xkeysym, xkeycode, sdl_mod_ముసుగు);

    ఒకవేళ (!keycode) {
        ఎంపిక (sdl_scancode) {
        స్థితి SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            ఆపు;
        స్థితి SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            ఆపు;
        స్థితి SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            ఆపు;
        స్థితి SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            ఆపు;
        అప్రమేయ:
            keycode = SDL_SCANCODE_గమ్యం_KEYCODE(sdl_scancode);
            ఆపు;
        }
    }

    SDL_సమితి_Keymap_నమోదు(keymap, sdl_scancode, sdl_mod_ముసుగు, keycode);
}

శూన్య X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ఒకవేళ (దత్తాంశం->keyboard.xkb_enabled) {
        XkbStateRec state;

        కొరకు (గుర్తులేని పూర్ణాంకం i = 0; i < Xkb_అంకె_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(దత్తాంశం->keyboard.xkb.keymaps[i]);
            దత్తాంశం->keyboard.xkb.keymaps[i] = ఖాళీ;
        }

        X11_Xkb_Get_పేర్లు(దత్తాంశం->display, Xkb_Virtual_Mod_పేర్లు_ముసుగు, దత్తాంశం->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(దత్తాంశం->display, Xkb_All_Client_Info_ముసుగు | Xkb_Virtual_Mods_ముసుగు, దత్తాంశం->keyboard.xkb.desc_ptr);

        ఒకవేళ (X11_XkbGetState(దత్తాంశం->display, XkbUseCoreKbd, &state) == Success) {
            దత్తాంశం->keyboard.xkb.current_సమూహం = state.సమూహం;
        }

        దత్తాంశం->keyboard.alt_ముసుగు = X11_Get_Xkb_Virtual_Modifier_ముసుగు(_this, "Alt");
        ఒకవేళ (!దత్తాంశం->keyboard.alt_ముసుగు) {
            దత్తాంశం->keyboard.alt_ముసుగు = X11_Get_Xkb_Virtual_Modifier_ముసుగు(_this, "Meta");
        }
        దత్తాంశం->keyboard.gui_ముసుగు = X11_Get_Xkb_Virtual_Modifier_ముసుగు(_this, "Super");
        దత్తాంశం->keyboard.level3_ముసుగు = X11_Get_Xkb_Virtual_Modifier_ముసుగు(_this, "LevelThree");
        దత్తాంశం->keyboard.level5_ముసుగు = X11_Get_Xkb_Virtual_Modifier_ముసుగు(_this, "LevelFive");
        దత్తాంశం->keyboard.numlock_ముసుగు = X11_Get_Xkb_Virtual_Modifier_ముసుగు(_this, "NumLock");
        దత్తాంశం->keyboard.scrolllock_ముసుగు = X11_Get_Xkb_Virtual_Modifier_ముసుగు(_this, "ScrollLock");

        కొరకు (గుర్తులేని పూర్ణాంకం i = 0; i < Xkb_అంకె_Kbd_Groups; ++i) {
            దత్తాంశం->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            ఒకవేళ (!దత్తాంశం->keyboard.xkb.keymaps[i]) {
                కొరకు (గుర్తులేని పూర్ణాంకం j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(దత్తాంశం->keyboard.xkb.keymaps[i]);
                    దత్తాంశం->keyboard.xkb.keymaps[j] = ఖాళీ;
                }

                తిరిగి;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        స్థిరరాశి Uint32 valid_mod_ముసుగు = జరుపు_ముసుగు_2 | తాళం_ముసుగు | దత్తాంశం->keyboard.alt_ముసుగు | దత్తాంశం->keyboard.level3_ముసుగు | దత్తాంశం->keyboard.level5_ముసుగు;

        కొరకు (Uint32 xkeycode = దత్తాంశం->keyboard.xkb.desc_ptr->min_కీలకం_సంకేతం; xkeycode < దత్తాంశం->keyboard.xkb.desc_ptr->max_కీలకం_సంకేతం; ++xkeycode) {
            స్థిరరాశి SDL_Scancode scancode = దత్తాంశం->keyboard.కీలకం_layout[xkeycode];
            ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN) {
                కొనసాగు;
            }

            కొరకు (Uint32 సమూహం = 0; సమూహం < Xkb_అంకె_Kbd_Groups; ++సమూహం) {
                SDL_Keymap *keymap = దత్తాంశం->keyboard.xkb.keymaps[సమూహం];

                Uint32 effective_సమూహం = సమూహం;
                స్థిరరాశి గుర్తులేని అక్షరం max_కీలకం_సమూహం = Xkb_కీలకం_అంకె_Groups(దత్తాంశం->keyboard.xkb.desc_ptr, xkeycode);
                స్థిరరాశి గుర్తులేని అక్షరం కీలకం_సమూహం_info = Xkb_కీలకం_సమూహం_Info(దత్తాంశం->keyboard.xkb.desc_ptr, xkeycode);

                ఒకవేళ (max_కీలకం_సమూహం && effective_సమూహం >= max_కీలకం_సమూహం) {
                    స్థిరరాశి గుర్తులేని అక్షరం action = Xkb_బహిర్గతం_యొక్క_Range_సమూహం_Action(కీలకం_సమూహం_info);

                    ఎంపిక (action) {
                    అప్రమేయ:
                        effective_సమూహం %= max_కీలకం_సమూహం;
                        ఆపు;
                    స్థితి XkbClampIntoRange:
                        effective_సమూహం = max_కీలకం_సమూహం - 1;
                        ఆపు;
                    స్థితి XkbRedirectIntoRange:
                        effective_సమూహం = Xkb_బహిర్గతం_యొక్క_Range_సమూహం_సంఖ్య(కీలకం_సమూహం_info);
                        ఒకవేళ (effective_సమూహం >= max_కీలకం_సమూహం) {
                            effective_సమూహం = 0;
                        }
                        ఆపు;
                    }
                }

                Xkb_కీలకం_Type_Ptr కీలకం_type = Xkb_కీలకం_కీలకం_Type(దత్తాంశం->keyboard.xkb.desc_ptr, xkeycode, effective_సమూహం);

                కొరకు (Uint32 level = 0; level < కీలకం_type->అంకె_స్థాయిలు; ++level) {
                    స్థిరరాశి కీలకం_Sym keysym = X11_కీలకం_సంకేతం_గమ్యం_Sym(_this, xkeycode, effective_సమూహం, level);

                    ఒకవేళ (keysym != No_చిహ్నం) {
                        bool కీలకం_added = false;

                        కొరకు (పూర్ణాంకం map_idx = 0; map_idx < కీలకం_type->map_లెక్క; ++map_idx) {
                            ఒకవేళ (కీలకం_type->map[map_idx].చురుకైన && కీలకం_type->map[map_idx].level == level) {
                                స్థిరరాశి గుర్తులేని పూర్ణాంకం xkb_mod_ముసుగు = కీలకం_type->map[map_idx].mods.ముసుగు;
                                ఒకవేళ ((xkb_mod_ముసుగు | valid_mod_ముసుగు) == valid_mod_ముసుగు) {
                                    స్థిరరాశి SDL_Keymod sdl_mod_ముసుగు = (xkb_mod_ముసుగు & జరుపు_ముసుగు_2 ? SDL_KMOD_జరుపు : 0) |
                                                                    (xkb_mod_ముసుగు & తాళం_ముసుగు ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_ముసుగు & దత్తాంశం->keyboard.alt_ముసుగు ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_ముసుగు & దత్తాంశం->keyboard.level3_ముసుగు ? SDL_KMOD_బహుళకం : 0) |
                                                                    (xkb_mod_ముసుగు & దత్తాంశం->keyboard.level5_ముసుగు ? SDL_KMOD_LEVEL5 : 0);

                                    X11_కూడు_Keymap_నమోదు(keymap, xkeycode, keysym, scancode, sdl_mod_ముసుగు);
                                    కీలకం_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        ఒకవేళ (!level && !కీలకం_added) {
                            X11_కూడు_Keymap_నమోదు(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_సమితి_Keymap(దత్తాంశం->keyboard.xkb.keymaps[దత్తాంశం->keyboard.xkb.current_సమూహం], send_event);
    } లేకపోతే
#అయితే_ముగింపు
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        ఒకవేళ (!keymap) {
            తిరిగి;
        }

        ఒకవేళ (send_event) {
            ఒకవేళ (దత్తాంశం->keyboard.core.keysym_map) {
                X11_XFree(దత్తాంశం->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(దత్తాంశం->display, &దత్తాంశం->keyboard.core.min_keycode, &దత్తాంశం->keyboard.core.max_keycode);
            దత్తాంశం->keyboard.core.keysym_map = X11_XGetKeyboardMapping(దత్తాంశం->display, దత్తాంశం->keyboard.core.min_keycode,
                                                                     దత్తాంశం->keyboard.core.max_keycode - దత్తాంశం->keyboard.core.min_keycode,
                                                                     &దత్తాంశం->keyboard.core.keysyms_చొప్పున_కీలకం);
        }

        కొరకు (Uint32 xkeycode = దత్తాంశం->keyboard.core.min_keycode; xkeycode <= దత్తాంశం->keyboard.core.max_keycode; ++xkeycode) {
            స్థిరరాశి SDL_Scancode scancode = దత్తాంశం->keyboard.కీలకం_layout[xkeycode];
            ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN) {
                కొనసాగు;
            }

            స్థిరరాశి కీలకం_Sym keysym = X11_కీలకం_సంకేతం_గమ్యం_Sym(_this, xkeycode, 0, 0);
            ఒకవేళ (keysym != No_చిహ్నం) {
                X11_కూడు_Keymap_నమోదు(keymap, xkeycode, keysym, scancode, 0);
            }
        }

        దత్తాంశం->keyboard.alt_ముసుగు = Mod1_ముసుగు; // Alt or Meta
        దత్తాంశం->keyboard.gui_ముసుగు = Mod4_ముసుగు; // Super
        దత్తాంశం->keyboard.level3_ముసుగు = Mod5_ముసుగు; // Note: Not a typo, Mod5 = level 3 shift, and Mod3 = level 5 shift.
        దత్తాంశం->keyboard.level5_ముసుగు = Mod3_ముసుగు;
        దత్తాంశం->keyboard.numlock_ముసుగు = X11_Get_XModifier_ముసుగు(_this, SDL_SCANCODE_NUMLOCKCLEAR);
        దత్తాంశం->keyboard.scrolllock_ముసుగు = X11_Get_XModifier_ముసుగు(_this, SDL_SCANCODE_SCROLLLOCK);

        SDL_సమితి_Keymap(keymap, send_event);
    }
}

శూన్య X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

#నిర్వచితమైతే X_HAVE_UTF8_STRING
    ఒకవేళ (దత్తాంశం->im) {
        X11_XCloseIM(దత్తాంశం->im);
        దత్తాంశం->im = ఖాళీ;
    } లేకపోతే {
        X11_XUnregisterIMInstantiateCallback(దత్తాంశం->display, ఖాళీ, ఖాళీ, ఖాళీ, im_instantiate_handler, (XPointer)దత్తాంశం);
    }
#అయితే_ముగింపు // X_HAVE_UTF8_STRING

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ఒకవేళ (దత్తాంశం->keyboard.xkb_enabled) {
        కొరకు (పూర్ణాంకం i = 0; i < Xkb_అంకె_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(దత్తాంశం->keyboard.xkb.keymaps[i]);
            దత్తాంశం->keyboard.xkb.keymaps[i] = ఖాళీ;
        }

        ఒకవేళ (దత్తాంశం->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(దత్తాంశం->keyboard.xkb.desc_ptr, 0, True);
            దత్తాంశం->keyboard.xkb.desc_ptr = ఖాళీ;
        }
    } లేకపోతే
#అయితే_ముగింపు
        ఒకవేళ (దత్తాంశం->keyboard.core.keysym_map) {
        X11_XFree(దత్తాంశం->keyboard.core.keysym_map);
        దత్తాంశం->keyboard.core.keysym_map = ఖాళీ;
    }
}

శూన్య X11_ClearComposition(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    ఒకవేళ (దత్తాంశం->preedit_నిడివి > 0) {
        దత్తాంశం->preedit_పాఠ్యం[0] = '\0';
        దత్తాంశం->preedit_నిడివి = 0;
    }

    ఒకవేళ (దత్తాంశం->ime_needs_clear_composition) {
        SDL_Send_Editing_పాఠ్యం("", 0, 0);
        దత్తాంశం->ime_needs_clear_composition = false;
    }
}

స్థిర శూన్య X11_SendEditingEvent(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    ఒకవేళ (దత్తాంశం->preedit_నిడివి == 0) {
        X11_ClearComposition(దత్తాంశం);
        తిరిగి;
    }

    bool లోపల_highlight = false;
    పూర్ణాంకం ప్రారంభం = -1, నిడివి = 0, i;
    కొరకు (i = 0; i < దత్తాంశం->preedit_నిడివి; ++i) {
        ఒకవేళ (దత్తాంశం->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            ఒకవేళ (ప్రారంభం < 0) {
                ప్రారంభం = i;
                లోపల_highlight = true;
            }
        } లేకపోతే ఒకవేళ (లోపల_highlight) {
            // Found the end of the highlight
            ఆపు;
        }
    }
    ఒకవేళ (లోపల_highlight) {
        నిడివి = (i - ప్రారంభం);
    } లేకపోతే {
        ప్రారంభం = SDL_clamp(దత్తాంశం->preedit_cursor, 0, దత్తాంశం->preedit_నిడివి);
    }
    SDL_Send_Editing_పాఠ్యం(దత్తాంశం->preedit_పాఠ్యం, ప్రారంభం, నిడివి);

    దత్తాంశం->ime_needs_clear_composition = true;
}

#నిర్వచితమైతే X_HAVE_UTF8_STRING
స్థిర పూర్ణాంకం preedit_ప్రారంభం_callback(XIC xic, XPointer client_దత్తాంశం_2, XPointer call_దత్తాంశం_2)
{
    // No limit on preedit text length
    తిరిగి -1;
}

స్థిర శూన్య preedit_పూర్తి_callback(XIC xic, XPointer client_దత్తాంశం_2, XPointer call_దత్తాంశం_2)
{
}

స్థిర శూన్య preedit_draw_callback(XIC xic, XPointer client_దత్తాంశం_2, XIMPreeditDrawCallbackStruct *call_దత్తాంశం_2)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = (SDL_కిటికీ_దత్తాంశం *)client_దత్తాంశం_2;
    పూర్ణాంకం chg_మొదటి = SDL_clamp(call_దత్తాంశం_2->chg_మొదటి, 0, దత్తాంశం->preedit_నిడివి);
    పూర్ణాంకం chg_నిడివి = SDL_clamp(call_దత్తాంశం_2->chg_నిడివి, 0, దత్తాంశం->preedit_నిడివి - chg_మొదటి);

    స్థిరరాశి అక్షరం *ప్రారంభం = దత్తాంశం->preedit_పాఠ్యం;
    ఒకవేళ (chg_నిడివి > 0) {
        // Delete text in range
        కొరకు (పూర్ణాంకం i = 0; ప్రారంభం && *ప్రారంభం && i < chg_మొదటి; ++i) {
            SDL_అడుగు_UTF8(&ప్రారంభం, ఖాళీ);
        }

        స్థిరరాశి అక్షరం *చివర = ప్రారంభం;
        కొరకు (పూర్ణాంకం i = 0; చివర && *చివర && i < chg_నిడివి; ++i) {
            SDL_అడుగు_UTF8(&చివర, ఖాళీ);
        }

        ఒకవేళ (చివర > ప్రారంభం) {
            SDL_memmove((అక్షరం *)ప్రారంభం, చివర, SDL_strlen(చివర) + 1);
            ఒకవేళ ((chg_మొదటి + chg_నిడివి) > దత్తాంశం->preedit_నిడివి) {
                SDL_memmove(&దత్తాంశం->preedit_feedback[chg_మొదటి], &దత్తాంశం->preedit_feedback[chg_మొదటి + chg_నిడివి], (దత్తాంశం->preedit_నిడివి - chg_మొదటి - chg_నిడివి) * పరిమాణం(*దత్తాంశం->preedit_feedback));
            }
        }
        దత్తాంశం->preedit_నిడివి -= chg_నిడివి;
    }

    XIMText *పాఠ్యం = call_దత్తాంశం_2->పాఠ్యం;
    ఒకవేళ (పాఠ్యం) {
        // Insert text in range
        SDL_assert(!పాఠ్యం->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        ఒకవేళ (పాఠ్యం->string.multi_byte) {
            పాఠ్యం->నిడివి = SDL_utf8strlen(పాఠ్యం->string.multi_byte);
        }

        size_t string_కొలత = SDL_strlen(పాఠ్యం->string.multi_byte);
        size_t కొలత = string_కొలత + 1;
        ఒకవేళ (దత్తాంశం->preedit_పాఠ్యం) {
            కొలత += SDL_strlen(దత్తాంశం->preedit_పాఠ్యం);
        }
        అక్షరం *preedit_పాఠ్యం = (అక్షరం *)SDL_malloc(కొలత * పరిమాణం(*preedit_పాఠ్యం));
        ఒకవేళ (preedit_పాఠ్యం) {
            size_t pre_కొలత = (ప్రారంభం - దత్తాంశం->preedit_పాఠ్యం);
            size_t post_కొలత = ప్రారంభం ? SDL_strlen(ప్రారంభం) : 0;
            ఒకవేళ (pre_కొలత > 0) {
                SDL_memcpy(&preedit_పాఠ్యం[0], దత్తాంశం->preedit_పాఠ్యం, pre_కొలత);
            }
            SDL_memcpy(&preedit_పాఠ్యం[pre_కొలత], పాఠ్యం->string.multi_byte, string_కొలత);
            ఒకవేళ (post_కొలత > 0) {
                SDL_memcpy(&preedit_పాఠ్యం[pre_కొలత + string_కొలత], ప్రారంభం, post_కొలత);
            }
            preedit_పాఠ్యం[కొలత - 1] = '\0';
        }

        size_t feedback_కొలత = దత్తాంశం->preedit_నిడివి + పాఠ్యం->నిడివి;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_కొలత * పరిమాణం(*feedback));
        ఒకవేళ (feedback) {
            size_t pre_కొలత = (size_t)chg_మొదటి;
            size_t post_కొలత = (size_t)దత్తాంశం->preedit_నిడివి - pre_కొలత;
            ఒకవేళ (pre_కొలత > 0) {
                SDL_memcpy(&feedback[0], దత్తాంశం->preedit_feedback, pre_కొలత * పరిమాణం(*feedback));
            }
            SDL_memcpy(&feedback[pre_కొలత], పాఠ్యం->feedback, పాఠ్యం->నిడివి * పరిమాణం(*feedback));
            ఒకవేళ (post_కొలత > 0) {
                SDL_memcpy(&feedback[pre_కొలత + పాఠ్యం->నిడివి], &దత్తాంశం->preedit_feedback[pre_కొలత], post_కొలత * పరిమాణం(*feedback));
            }
        }

        ఒకవేళ (preedit_పాఠ్యం && feedback) {
            SDL_free(దత్తాంశం->preedit_పాఠ్యం);
            దత్తాంశం->preedit_పాఠ్యం = preedit_పాఠ్యం;

            SDL_free(దత్తాంశం->preedit_feedback);
            దత్తాంశం->preedit_feedback = feedback;

            దత్తాంశం->preedit_నిడివి += పాఠ్యం->నిడివి;
        } లేకపోతే {
            SDL_free(preedit_పాఠ్యం);
            SDL_free(feedback);
        }
    }

    దత్తాంశం->preedit_cursor = call_దత్తాంశం_2->caret;

#నిర్వచితమైతే DEBUG_XIM
    ఒకవేళ (call_దత్తాంశం_2->chg_నిడివి > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_దత్తాంశం_2->chg_నిడివి, call_దత్తాంశం_2->chg_మొదటి);
    }
    ఒకవేళ (పాఠ్యం) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", పాఠ్యం->string.multi_byte, call_దత్తాంశం_2->chg_మొదటి, call_దత్తాంశం_2->caret);
    }
    SDL_Log("Pre-edit text: %s", దత్తాంశం->preedit_పాఠ్యం);
#అయితే_ముగింపు

    X11_SendEditingEvent(దత్తాంశం);
}

స్థిర శూన్య preedit_caret_callback(XIC xic, XPointer client_దత్తాంశం_2, XIMPreeditCaretCallbackStruct *call_దత్తాంశం_2)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = (SDL_కిటికీ_దత్తాంశం *)client_దత్తాంశం_2;

    ఎంపిక (call_దత్తాంశం_2->direction) {
    స్థితి XIMAbsolutePosition:
        ఒకవేళ (call_దత్తాంశం_2->position != దత్తాంశం->preedit_cursor) {
            దత్తాంశం->preedit_cursor = call_దత్తాంశం_2->position;
            X11_SendEditingEvent(దత్తాంశం);
        }
        ఆపు;
    స్థితి XIMDontChange:
        ఆపు;
    అప్రమేయ:
        // Not currently supported
        ఆపు;
    }
}

స్థిర శూన్య ic_destroyed_handler(XIC ic, XPointer client_దత్తాంశం, XPointer call_దత్తాంశం)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = (SDL_కిటికీ_దత్తాంశం *)client_దత్తాంశం;
    దత్తాంశం->ic = ఖాళీ;
    X11_Destroy_ఆదానం_Context(దత్తాంశం);

    // If the IM was already recreated, create a new IC.
    ఒకవేళ (దత్తాంశం->videodata->im) {
        X11_Create_ఆదానం_Context(దత్తాంశం);
    }
}
#అయితే_ముగింపు // X_HAVE_UTF8_STRING

శూన్య X11_Create_ఆదానం_Context(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
#నిర్వచితమైతే X_HAVE_UTF8_STRING
    SDL_Video_దత్తాంశం *videodata = దత్తాంశం->videodata;

    ఒకవేళ (SDL_X11_HAVE_UTF8 && videodata->im) {
        స్థిరరాశి అక్షరం *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_దత్తాంశం_2 = (XPointer)దత్తాంశం;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        ఒకవేళ (hint && SDL_strstr(hint, "composition")) {
            XIMCallback draw_callback;
            draw_callback.client_దత్తాంశం_2 = (XPointer)దత్తాంశం;
            draw_callback.callback = (XIMProc)preedit_draw_callback;

            XIMCallback ప్రారంభం_callback;
            ప్రారంభం_callback.client_దత్తాంశం_2 = (XPointer)దత్తాంశం;
            ప్రారంభం_callback.callback = (XIMProc)preedit_ప్రారంభం_callback;

            XIMCallback పూర్తి_callback;
            పూర్తి_callback.client_దత్తాంశం_2 = (XPointer)దత్తాంశం;
            పూర్తి_callback.callback = (XIMProc)preedit_పూర్తి_callback;

            XIMCallback caret_callback;
            caret_callback.client_దత్తాంశం_2 = (XPointer)దత్తాంశం;
            caret_callback.callback = (XIMProc)preedit_caret_callback;

            XVaNestedList attr = X11_XVaCreateNestedList(0,
                                                         XNPreedit_ప్రారంభం_Callback, &ప్రారంభం_callback,
                                                         XNPreedit_పూర్తి_Callback, &పూర్తి_callback,
                                                         XNPreeditDrawCallback, &draw_callback,
                                                         XNPreeditCaretCallback, &caret_callback,
                                                         ఖాళీ);
            ఒకవేళ (attr) {
                దత్తాంశం->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreedit_లక్షణాలు, attr,
                                         XNClient_కిటికీ, దత్తాంశం->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         ఖాళీ);
                X11_XFree(attr);
            }
        }
        ఒకవేళ (!దత్తాంశం->ic) {
            దత్తాంశం->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClient_కిటికీ, దత్తాంశం->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     ఖాళీ);
        }
        దత్తాంశం->xim_spot.x = -1;
        దత్తాంశం->xim_spot.y = -1;
    }
#అయితే_ముగింపు // X_HAVE_UTF8_STRING
}


శూన్య X11_Destroy_ఆదానం_Context(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
#నిర్వచితమైతే X_HAVE_UTF8_STRING
    ఒకవేళ (దత్తాంశం->ic) {
        X11_XDestroyIC(దత్తాంశం->ic);
        దత్తాంశం->ic = ఖాళీ;
    }
    SDL_free(దత్తాంశం->preedit_పాఠ్యం);
    SDL_free(దత్తాంశం->preedit_feedback);
    దత్తాంశం->preedit_పాఠ్యం = ఖాళీ;
    దత్తాంశం->preedit_feedback = ఖాళీ;
#అయితే_ముగింపు
}

స్థిర శూన్య X11_ResetXIM(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#నిర్వచితమైతే X_HAVE_UTF8_STRING
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    ఒకవేళ (దత్తాంశం && దత్తాంశం->ic) {
        // Clear any partially entered dead keys
        అక్షరం *contents = X11_Xutf8ResetIC(దత్తాంశం->ic);
        ఒకవేళ (contents) {
            X11_XFree(contents);
        }
    }
#అయితే_ముగింపు // X_HAVE_UTF8_STRING
}

bool X11_ప్రారంభం_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, కిటికీ);

    తిరిగి X11_Update_పాఠ్యం_ఆదానం_Area(_this, కిటికీ);
}

bool X11_Stop_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    X11_ResetXIM(_this, కిటికీ);
    తిరిగి true;
}

bool X11_Update_పాఠ్యం_ఆదానం_Area(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#నిర్వచితమైతే X_HAVE_UTF8_STRING
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    ఒకవేళ (దత్తాంశం && దత్తాంశం->ic) {
        XPoint spot;
        spot.x = కిటికీ->పాఠ్యం_ఆదానం_rect.x + కిటికీ->పాఠ్యం_ఆదానం_cursor;
        spot.y = కిటికీ->పాఠ్యం_ఆదానం_rect.y + కిటికీ->పాఠ్యం_ఆదానం_rect.h;
        ఒకవేళ (spot.x != దత్తాంశం->xim_spot.x || spot.y != దత్తాంశం->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, ఖాళీ);
            ఒకవేళ (attr) {
                X11_XSetICValues(దత్తాంశం->ic, XNPreedit_లక్షణాలు, attr, ఖాళీ);
                X11_XFree(attr);
            }
            SDL_copyp(&దత్తాంశం->xim_spot, &spot);
        }
    }
#అయితే_ముగింపు
    తిరిగి true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    తిరిగి videodata->use_steam_screen_keyboard;
}

శూన్య X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;

    ఒకవేళ (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        స్థిరరాశి పూర్ణాంకం k_EFloating_Gamepad_పాఠ్యం_ఆదానం_బహుళకం_బహుళకం_Single_పంక్తి = 0;    // Enter dismisses the keyboard
        స్థిరరాశి పూర్ణాంకం k_EFloating_Gamepad_పాఠ్యం_ఆదానం_బహుళకం_బహుళకం_గుణిజం_పంక్తులు = 1; // User needs to explicitly dismiss the keyboard
        స్థిరరాశి పూర్ణాంకం k_EFloating_Gamepad_పాఠ్యం_ఆదానం_బహుళకం_బహుళకం_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        స్థిరరాశి పూర్ణాంకం k_EFloating_Gamepad_పాఠ్యం_ఆదానం_బహుళకం_బహుళకం_Numeric = 3;       // Numeric keypad is shown
        అక్షరం deeplink[128];
        పూర్ణాంకం బహుళకం;

        ఎంపిక (SDL_Get_పాఠ్యం_ఆదానం_Type(props)) {
        స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_EMAIL:
            బహుళకం = k_EFloating_Gamepad_పాఠ్యం_ఆదానం_బహుళకం_బహుళకం_Email;
            ఆపు;
        స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య:
        స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య_PASSWORD_HIDDEN:
        స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య_PASSWORD_VISIBLE:
            బహుళకం = k_EFloating_Gamepad_పాఠ్యం_ఆదానం_బహుళకం_బహుళకం_Numeric;
            ఆపు;
        అప్రమేయ:
            ఒకవేళ (SDL_Get_పాఠ్యం_ఆదానం_Multiline(props)) {
                బహుళకం = k_EFloating_Gamepad_పాఠ్యం_ఆదానం_బహుళకం_బహుళకం_గుణిజం_పంక్తులు;
            } లేకపోతే {
                బహుళకం = k_EFloating_Gamepad_పాఠ్యం_ఆదానం_బహుళకం_బహుళకం_Single_పంక్తి;
            }
            ఆపు;
        }
        (శూన్య)SDL_snprintf(deeplink, పరిమాణం(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           కిటికీ->పాఠ్యం_ఆదానం_rect.x, కిటికీ->పాఠ్యం_ఆదానం_rect.y,
                           కిటికీ->పాఠ్యం_ఆదానం_rect.w, కిటికీ->పాఠ్యం_ఆదానం_rect.h,
                           బహుళకం);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

శూన్య X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;

    ఒకవేళ (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
