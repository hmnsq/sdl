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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_scancode_tables_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <X11/keysym.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/XKBlib.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/imKStoUCS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keysym_to_scancode_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keysym_to_keycode_c.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>
#ਜੇ_ਅੰਤ

ਸਥਿਰ SDL_Scancode_ਸਾਰਣੀ scancode_ਸੈੱਟ[] = {
    SDL_SCANCODE_ਸਾਰਣੀ_DARWIN,
    SDL_SCANCODE_ਸਾਰਣੀ_XFREE86_1,
    SDL_SCANCODE_ਸਾਰਣੀ_XFREE86_2,
    SDL_SCANCODE_ਸਾਰਣੀ_XVNC,
};

ਸਥਿਰ bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    ਚੋਣ (scancode) {
    ਹਾਲਤ SDL_SCANCODE_ESCAPE:
    ਹਾਲਤ SDL_SCANCODE_CAPSLOCK:
    ਹਾਲਤ SDL_SCANCODE_NUMLOCKCLEAR:
    ਹਾਲਤ SDL_SCANCODE_LSHIFT:
    ਹਾਲਤ SDL_SCANCODE_RSHIFT:
    ਹਾਲਤ SDL_SCANCODE_LCTRL:
    ਹਾਲਤ SDL_SCANCODE_RCTRL:
    ਹਾਲਤ SDL_SCANCODE_LALT:
    ਹਾਲਤ SDL_SCANCODE_RALT:
    ਹਾਲਤ SDL_SCANCODE_LGUI:
    ਹਾਲਤ SDL_SCANCODE_RGUI:
        ਵਾਪਸ false;
    ਮੂਲ:
        ਵਾਪਸ true;
    }
}

ਸਥਿਰ ਕੁੰਜੀ_Sym X11_ਕੁੰਜੀ_ਕੋਡ_ਮੰਜ਼ਿਲ_Sym(SDL_VideoDevice *_this, ਕੁੰਜੀ_ਕੋਡ_2 keycode, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਸਮੂਹ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ level)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    ਕੁੰਜੀ_Sym keysym;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ਜੇ (ਅੰਕੜੇ->keyboard.xkb_enabled) {
        keysym = X11_Xkb_Keycode_ਮੰਜ਼ਿਲ_Keysym(ਅੰਕੜੇ->display, keycode, ਸਮੂਹ, level);
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        // TODO: Handle groups on the legacy path.
        ਜੇ (keycode >= ਅੰਕੜੇ->keyboard.core.min_keycode && keycode <= ਅੰਕੜੇ->keyboard.core.max_keycode) {
            keysym = ਅੰਕੜੇ->keyboard.core.keysym_map[(keycode - ਅੰਕੜੇ->keyboard.core.min_keycode) * ਅੰਕੜੇ->keyboard.core.keysyms_ਪ੍ਰਤੀ_ਕੁੰਜੀ];
        } ਨਹੀਂਤਾਂ {
            keysym = No_ਚਿੰਨ੍ਹ;
        }
    }

    ਵਾਪਸ keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
ਸਥਿਰ SDL_Scancode X11_ਕੁੰਜੀ_ਕੋਡ_ਮੰਜ਼ਿਲ_SDLScancode(SDL_VideoDevice *_this, ਕੁੰਜੀ_ਕੋਡ_2 keycode)
{
    ਅਚਲ ਕੁੰਜੀ_Sym keysym = X11_ਕੁੰਜੀ_ਕੋਡ_ਮੰਜ਼ਿਲ_Sym(_this, keycode, 0, 0);

    ਜੇ (keysym == No_ਚਿੰਨ੍ਹ) {
        ਵਾਪਸ SDL_SCANCODE_UNKNOWN;
    }

    ਵਾਪਸ SDL_Get_Scancode_From_ਕੁੰਜੀ_Sym(keysym, keycode);
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
ਸਥਿਰ bool X11_InitIM(SDL_Video_ਅੰਕੜੇ *videodata);

ਸਥਿਰ ਖਾਲੀ im_instantiate_handler(Display *display, XPointer client_ਅੰਕੜੇ, XPointer call_ਅੰਕੜੇ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)client_ਅੰਕੜੇ;

    ਜੇ (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, im_instantiate_handler, client_ਅੰਕੜੇ);
    }
}

ਸਥਿਰ ਖਾਲੀ im_destroyed_handler(XIM im, XPointer client_ਅੰਕੜੇ, XPointer call_ਅੰਕੜੇ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)client_ਅੰਕੜੇ;

    videodata->im = ਨਿਰਾ;
    X11_XRegisterIMInstantiateCallback(videodata->display, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, im_instantiate_handler, client_ਅੰਕੜੇ);
}

ਸਥਿਰ bool X11_InitIM(SDL_Video_ਅੰਕੜੇ *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    ਅੱਖਰ *prev_locale = setlocale(LC_ALL, ਨਿਰਾ);
    ਅੱਖਰ *prev_xmods = X11_XSetLocaleModifiers(ਨਿਰਾ);

    ਜੇ (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    ਜੇ (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (ਖਾਲੀ)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (ਖਾਲੀ)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    ਜੇ (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_ਅੰਕੜੇ_2 = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (ਅੱਖਰ *)ਨਿਰਾ);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        ਲਈ (ਪੂਰਨ i = 0; i < videodata->numwindows; ++i) {
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *w = videodata->windowlist[i];
            ਜੇ (!w->ic) {
                X11_Create_ਨਿਵੇਸ਼_Context(w);
            }
        }

        ਵਾਪਸ true;
    }

    ਵਾਪਸ false;
}
#ਜੇ_ਅੰਤ // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    ਪੂਰਨ i = 0;
    ਪੂਰਨ j = 0;
    ਪੂਰਨ min_keycode, max_keycode;
    ਬਣਤਰ
    {
        SDL_Scancode scancode;
        ਕੁੰਜੀ_Sym keysym;
        ਪੂਰਨ ਮੁੱਲ;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_ਪੂਰਵ, 0 },
        { SDL_SCANCODE_ਉੱਪਰ, XK_ਉੱਪਰ, 0 },
        { SDL_SCANCODE_ਖੱਬਾ, XK_ਖੱਬਾ, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    ਪੂਰਨ ਉੱਤਮ_ਦੂਰੀ;
    ਪੂਰਨ ਉੱਤਮ_ਸੂਚਕਾਂਕ;
    ਪੂਰਨ ਦੂਰੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ਪੂਰਨ xkb_major = Xkb_Major_ਸੰਸਕਰਣ;
    ਪੂਰਨ xkb_minor = Xkb_Minor_ਸੰਸਕਰਣ;

    ਜੇ (X11_XkbQueryExtension(ਅੰਕੜੇ->display, ਨਿਰਾ, &ਅੰਕੜੇ->keyboard.xkb.event, ਨਿਰਾ, &xkb_major, &xkb_minor)) {
        Bool xkb_repeat = 0;
        ਅੰਕੜੇ->keyboard.xkb_enabled = true;
        ਅੰਕੜੇ->keyboard.xkb.desc_ptr = X11_XkbGetMap(ਅੰਕੜੇ->display, Xkb_All_Client_Info_ਨਕਾਬ, XkbUseCoreKbd);

        // This will remove KeyRelease events for held keys.
        X11_Xkb_ਸੈੱਟ_Detectable_Auto_Repeat(ਅੰਕੜੇ->display, True, &xkb_repeat);

        // Enable the key mapping and state events.
        X11_XkbSelectEvents(ਅੰਕੜੇ->display, XkbUseCoreKbd,
                            Xkb_New_Keyboard_Notify_ਨਕਾਬ | Xkb_Map_Notify_ਨਕਾਬ | Xkb_State_Notify_ਨਕਾਬ,
                            Xkb_New_Keyboard_Notify_ਨਕਾਬ | Xkb_Map_Notify_ਨਕਾਬ | Xkb_State_Notify_ਨਕਾਬ);
        X11_XkbSelectEventDetails(ਅੰਕੜੇ->display, XkbUseCoreKbd, XkbStateNotify, Xkb_ਸਮੂਹ_State_ਨਕਾਬ | Xkb_Modifier_State_ਨਕਾਬ, Xkb_ਸਮੂਹ_State_ਨਕਾਬ | Xkb_Modifier_State_ਨਕਾਬ);
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(ਅੰਕੜੇ->display, &ਅੰਕੜੇ->keyboard.core.min_keycode, &ਅੰਕੜੇ->keyboard.core.max_keycode);
        ਅੰਕੜੇ->keyboard.core.keysym_map = X11_XGetKeyboardMapping(ਅੰਕੜੇ->display, ਅੰਕੜੇ->keyboard.core.min_keycode,
                                                              ਅੰਕੜੇ->keyboard.core.max_keycode - ਅੰਕੜੇ->keyboard.core.min_keycode,
                                                              &ਅੰਕੜੇ->keyboard.core.keysyms_ਪ੍ਰਤੀ_ਕੁੰਜੀ);
    }

    // Open a connection to the X input manager
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    ਜੇ (SDL_X11_HAVE_UTF8) {
        ਜੇ (!X11_InitIM(ਅੰਕੜੇ)) {
            X11_XRegisterIMInstantiateCallback(ਅੰਕੜੇ->display, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, im_instantiate_handler, (XPointer)ਅੰਕੜੇ);
        }
    }
#ਜੇ_ਅੰਤ
    // Try to determine which scancodes are being used based on fingerprint
    ਉੱਤਮ_ਦੂਰੀ = SDL_arraysize(fingerprint) + 1;
    ਉੱਤਮ_ਸੂਚਕਾਂਕ = -1;
    X11_XDisplayKeycodes(ਅੰਕੜੇ->display, &min_keycode, &max_keycode);
    ਲਈ (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].ਮੁੱਲ = X11_XKeysym_ਮੰਜ਼ਿਲ_Keycode(ਅੰਕੜੇ->display, fingerprint[i].keysym) - min_keycode;
    }
    ਲਈ (i = 0; i < SDL_arraysize(scancode_ਸੈੱਟ); ++i) {
        ਪੂਰਨ ਸਾਰਣੀ_ਮਾਪ;
        ਅਚਲ SDL_Scancode *ਸਾਰਣੀ = SDL_Get_Scancode_ਸਾਰਣੀ(scancode_ਸੈੱਟ[i], &ਸਾਰਣੀ_ਮਾਪ);

        ਦੂਰੀ = 0;
        ਲਈ (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            ਜੇ (fingerprint[j].ਮੁੱਲ < 0 || fingerprint[j].ਮੁੱਲ >= ਸਾਰਣੀ_ਮਾਪ) {
                ਦੂਰੀ += 1;
            } ਨਹੀਂਤਾਂ ਜੇ (ਸਾਰਣੀ[fingerprint[j].ਮੁੱਲ] != fingerprint[j].scancode) {
                ਦੂਰੀ += 1;
            }
        }
        ਜੇ (ਦੂਰੀ < ਉੱਤਮ_ਦੂਰੀ) {
            ਉੱਤਮ_ਦੂਰੀ = ਦੂਰੀ;
            ਉੱਤਮ_ਸੂਚਕਾਂਕ = i;
        }
    }
    ਜੇ (ਉੱਤਮ_ਸੂਚਕਾਂਕ < 0 || ਉੱਤਮ_ਦੂਰੀ > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        ਪੂਰਨ fingerprint_ਮੁੱਲ = X11_XKeysym_ਮੰਜ਼ਿਲ_Keycode(ਅੰਕੜੇ->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        ਜੇ (fingerprint_ਮੁੱਲ == 235) {
            ਲਈ (i = 0; i < SDL_arraysize(scancode_ਸੈੱਟ); ++i) {
                ਜੇ (scancode_ਸੈੱਟ[i] == SDL_SCANCODE_ਸਾਰਣੀ_XFREE86_2) {
                    ਉੱਤਮ_ਸੂਚਕਾਂਕ = i;
                    ਉੱਤਮ_ਦੂਰੀ = 0;
                    ਰੋਕੋ;
                }
            }
        }
    }
    ਜੇ (ਉੱਤਮ_ਸੂਚਕਾਂਕ >= 0 && ਉੱਤਮ_ਦੂਰੀ <= 2) {
        ਪੂਰਨ ਸਾਰਣੀ_ਮਾਪ;
        ਅਚਲ SDL_Scancode *ਸਾਰਣੀ = SDL_Get_Scancode_ਸਾਰਣੀ(scancode_ਸੈੱਟ[ਉੱਤਮ_ਸੂਚਕਾਂਕ], &ਸਾਰਣੀ_ਮਾਪ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", ਉੱਤਮ_ਸੂਚਕਾਂਕ, min_keycode, max_keycode, ਸਾਰਣੀ_ਮਾਪ);
#ਜੇ_ਅੰਤ
        // This should never happen, but just in case...
        ਜੇ (ਸਾਰਣੀ_ਮਾਪ > (SDL_arraysize(ਅੰਕੜੇ->keyboard.ਕੁੰਜੀ_layout) - min_keycode)) {
            ਸਾਰਣੀ_ਮਾਪ = (SDL_arraysize(ਅੰਕੜੇ->keyboard.ਕੁੰਜੀ_layout) - min_keycode);
        }
        SDL_memcpy(&ਅੰਕੜੇ->keyboard.ਕੁੰਜੀ_layout[min_keycode], ਸਾਰਣੀ, ਆਕਾਰ(SDL_Scancode) * ਸਾਰਣੀ_ਮਾਪ);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        ਲਈ (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_ਕੁੰਜੀ_ਕੋਡ_ਮੰਜ਼ਿਲ_SDLScancode(_this, i);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_KEYBOARD
            {
                ਕੁੰਜੀ_Sym sym;
                sym = X11_ਕੁੰਜੀ_ਕੋਡ_ਮੰਜ਼ਿਲ_Sym(_this, (ਕੁੰਜੀ_ਕੋਡ_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)sym, sym == No_ਚਿੰਨ੍ਹ ? "NoSymbol" : X11_XKeysym_ਮੰਜ਼ਿਲ_String(sym));
            }
#ਜੇ_ਅੰਤ
            ਜੇ (scancode == ਅੰਕੜੇ->keyboard.ਕੁੰਜੀ_layout[i]) {
                ਜਾਰੀ;
            }
            ਜੇ ((SDL_GetKeymapKeycode(ਨਿਰਾ, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_ਨਕਾਬ | SDLK_EXTENDED_ਨਕਾਬ)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", ਅੰਕੜੇ->ਕੁੰਜੀ_layout[i], SDL_GetScancodeName(ਅੰਕੜੇ->ਕੁੰਜੀ_layout[i]), scancode, SDL_GetScancodeName(scancode));
#ਜੇ_ਅੰਤ
                ਅੰਕੜੇ->keyboard.ਕੁੰਜੀ_layout[i] = scancode;
            }
        }
    } ਨਹੀਂਤਾਂ {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#ਜੇ_ਅੰਤ

        // Determine key_layout - only works on US QWERTY layout
        ਲਈ (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_ਕੁੰਜੀ_ਕੋਡ_ਮੰਜ਼ਿਲ_SDLScancode(_this, i);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_SCANCODES
            {
                ਕੁੰਜੀ_Sym sym;
                sym = X11_ਕੁੰਜੀ_ਕੋਡ_ਮੰਜ਼ਿਲ_Sym(_this, (ਕੁੰਜੀ_ਕੋਡ_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)sym, sym == No_ਚਿੰਨ੍ਹ ? "NoSymbol" : X11_XKeysym_ਮੰਜ਼ਿਲ_String(sym));
            }
            ਜੇ (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } ਨਹੀਂਤਾਂ {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#ਜੇ_ਅੰਤ
            ਅੰਕੜੇ->keyboard.ਕੁੰਜੀ_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_ਸੈੱਟ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    ਵਾਪਸ true;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ X11_Get_Xkb_Virtual_Modifier_ਨਕਾਬ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *vmod_name)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ mod_ਨਕਾਬ = 0;

    ਅਚਲ Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    ਜੇ (vmod != None) {
        ਲਈ (ਪੂਰਨ i = 0; i < Xkb_ਅੰਕ_Virtual_Mods; ++i) {
            ਜੇ (vmod == videodata->keyboard.xkb.desc_ptr->ਨਾਂ->vmods[i]) {
                mod_ਨਕਾਬ = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                ਰੋਕੋ;
            }
        }
    }

    ਵਾਪਸ mod_ਨਕਾਬ;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ X11_Get_XModifier_ਨਕਾਬ(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    Display *display = videodata->display;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ mod_ਨਕਾਬ = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n = xmods->max_keypermod;
    ਲਈ (ਪੂਰਨ i = 3; i < 8; i++) {
        ਲਈ (ਪੂਰਨ j = 0; j < n; j++) {
            ਅਚਲ ਕੁੰਜੀ_ਕੋਡ_2 kc = xmods->modifiermap[i * n + j];
            ਜੇ (videodata->keyboard.ਕੁੰਜੀ_layout[kc] == scancode) {
                mod_ਨਕਾਬ = 1 << i;
                ਰੋਕੋ;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    ਵਾਪਸ mod_ਨਕਾਬ;
}

ਸਥਿਰ ਖਾਲੀ X11_ਜੋੜੋ_Keymap_ਇੰਦਰਾਜ(SDL_Keymap *keymap, Uint32 xkeycode, ਕੁੰਜੀ_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_ਨਕਾਬ)
{
    SDL_Keycode keycode = SDL_Get_ਕੁੰਜੀ_ਕੋਡ_From_ਕੁੰਜੀ_Sym(xkeysym, xkeycode, sdl_mod_ਨਕਾਬ);

    ਜੇ (!keycode) {
        ਚੋਣ (sdl_scancode) {
        ਹਾਲਤ SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            ਰੋਕੋ;
        ਮੂਲ:
            keycode = SDL_SCANCODE_ਮੰਜ਼ਿਲ_KEYCODE(sdl_scancode);
            ਰੋਕੋ;
        }
    }

    SDL_ਸੈੱਟ_Keymap_ਇੰਦਰਾਜ(keymap, sdl_scancode, sdl_mod_ਨਕਾਬ, keycode);
}

ਖਾਲੀ X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ਜੇ (ਅੰਕੜੇ->keyboard.xkb_enabled) {
        XkbStateRec state;

        ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i = 0; i < Xkb_ਅੰਕ_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(ਅੰਕੜੇ->keyboard.xkb.keymaps[i]);
            ਅੰਕੜੇ->keyboard.xkb.keymaps[i] = ਨਿਰਾ;
        }

        X11_Xkb_Get_ਨਾਂ(ਅੰਕੜੇ->display, Xkb_Virtual_Mod_ਨਾਂ_ਨਕਾਬ, ਅੰਕੜੇ->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(ਅੰਕੜੇ->display, Xkb_All_Client_Info_ਨਕਾਬ | Xkb_Virtual_Mods_ਨਕਾਬ, ਅੰਕੜੇ->keyboard.xkb.desc_ptr);

        ਜੇ (X11_XkbGetState(ਅੰਕੜੇ->display, XkbUseCoreKbd, &state) == Success) {
            ਅੰਕੜੇ->keyboard.xkb.current_ਸਮੂਹ = state.ਸਮੂਹ;
        }

        ਅੰਕੜੇ->keyboard.alt_ਨਕਾਬ = X11_Get_Xkb_Virtual_Modifier_ਨਕਾਬ(_this, "Alt");
        ਜੇ (!ਅੰਕੜੇ->keyboard.alt_ਨਕਾਬ) {
            ਅੰਕੜੇ->keyboard.alt_ਨਕਾਬ = X11_Get_Xkb_Virtual_Modifier_ਨਕਾਬ(_this, "Meta");
        }
        ਅੰਕੜੇ->keyboard.gui_ਨਕਾਬ = X11_Get_Xkb_Virtual_Modifier_ਨਕਾਬ(_this, "Super");
        ਅੰਕੜੇ->keyboard.level3_ਨਕਾਬ = X11_Get_Xkb_Virtual_Modifier_ਨਕਾਬ(_this, "LevelThree");
        ਅੰਕੜੇ->keyboard.level5_ਨਕਾਬ = X11_Get_Xkb_Virtual_Modifier_ਨਕਾਬ(_this, "LevelFive");
        ਅੰਕੜੇ->keyboard.numlock_ਨਕਾਬ = X11_Get_Xkb_Virtual_Modifier_ਨਕਾਬ(_this, "NumLock");
        ਅੰਕੜੇ->keyboard.scrolllock_ਨਕਾਬ = X11_Get_Xkb_Virtual_Modifier_ਨਕਾਬ(_this, "ScrollLock");

        ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i = 0; i < Xkb_ਅੰਕ_Kbd_Groups; ++i) {
            ਅੰਕੜੇ->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            ਜੇ (!ਅੰਕੜੇ->keyboard.xkb.keymaps[i]) {
                ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(ਅੰਕੜੇ->keyboard.xkb.keymaps[i]);
                    ਅੰਕੜੇ->keyboard.xkb.keymaps[j] = ਨਿਰਾ;
                }

                ਵਾਪਸ;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ਅਚਲ Uint32 valid_mod_ਨਕਾਬ = ਖਿਸਕਾਓ_ਨਕਾਬ_2 | ਤਾਲਾ_ਨਕਾਬ | ਅੰਕੜੇ->keyboard.alt_ਨਕਾਬ | ਅੰਕੜੇ->keyboard.level3_ਨਕਾਬ | ਅੰਕੜੇ->keyboard.level5_ਨਕਾਬ;

        ਲਈ (Uint32 xkeycode = ਅੰਕੜੇ->keyboard.xkb.desc_ptr->min_ਕੁੰਜੀ_ਕੋਡ; xkeycode < ਅੰਕੜੇ->keyboard.xkb.desc_ptr->max_ਕੁੰਜੀ_ਕੋਡ; ++xkeycode) {
            ਅਚਲ SDL_Scancode scancode = ਅੰਕੜੇ->keyboard.ਕੁੰਜੀ_layout[xkeycode];
            ਜੇ (scancode == SDL_SCANCODE_UNKNOWN) {
                ਜਾਰੀ;
            }

            ਲਈ (Uint32 ਸਮੂਹ = 0; ਸਮੂਹ < Xkb_ਅੰਕ_Kbd_Groups; ++ਸਮੂਹ) {
                SDL_Keymap *keymap = ਅੰਕੜੇ->keyboard.xkb.keymaps[ਸਮੂਹ];

                Uint32 effective_ਸਮੂਹ = ਸਮੂਹ;
                ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ max_ਕੁੰਜੀ_ਸਮੂਹ = Xkb_ਕੁੰਜੀ_ਅੰਕ_Groups(ਅੰਕੜੇ->keyboard.xkb.desc_ptr, xkeycode);
                ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਕੁੰਜੀ_ਸਮੂਹ_info = Xkb_ਕੁੰਜੀ_ਸਮੂਹ_Info(ਅੰਕੜੇ->keyboard.xkb.desc_ptr, xkeycode);

                ਜੇ (max_ਕੁੰਜੀ_ਸਮੂਹ && effective_ਸਮੂਹ >= max_ਕੁੰਜੀ_ਸਮੂਹ) {
                    ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ action = Xkb_ਬਾਹਰਲਾ_ਦਾ_Range_ਸਮੂਹ_Action(ਕੁੰਜੀ_ਸਮੂਹ_info);

                    ਚੋਣ (action) {
                    ਮੂਲ:
                        effective_ਸਮੂਹ %= max_ਕੁੰਜੀ_ਸਮੂਹ;
                        ਰੋਕੋ;
                    ਹਾਲਤ XkbClampIntoRange:
                        effective_ਸਮੂਹ = max_ਕੁੰਜੀ_ਸਮੂਹ - 1;
                        ਰੋਕੋ;
                    ਹਾਲਤ XkbRedirectIntoRange:
                        effective_ਸਮੂਹ = Xkb_ਬਾਹਰਲਾ_ਦਾ_Range_ਸਮੂਹ_ਸੰਖਿਆ(ਕੁੰਜੀ_ਸਮੂਹ_info);
                        ਜੇ (effective_ਸਮੂਹ >= max_ਕੁੰਜੀ_ਸਮੂਹ) {
                            effective_ਸਮੂਹ = 0;
                        }
                        ਰੋਕੋ;
                    }
                }

                Xkb_ਕੁੰਜੀ_Type_Ptr ਕੁੰਜੀ_type = Xkb_ਕੁੰਜੀ_ਕੁੰਜੀ_Type(ਅੰਕੜੇ->keyboard.xkb.desc_ptr, xkeycode, effective_ਸਮੂਹ);

                ਲਈ (Uint32 level = 0; level < ਕੁੰਜੀ_type->ਅੰਕ_ਪੱਧਰ; ++level) {
                    ਅਚਲ ਕੁੰਜੀ_Sym keysym = X11_ਕੁੰਜੀ_ਕੋਡ_ਮੰਜ਼ਿਲ_Sym(_this, xkeycode, effective_ਸਮੂਹ, level);

                    ਜੇ (keysym != No_ਚਿੰਨ੍ਹ) {
                        bool ਕੁੰਜੀ_added = false;

                        ਲਈ (ਪੂਰਨ map_idx = 0; map_idx < ਕੁੰਜੀ_type->map_ਗਿਣਤੀ; ++map_idx) {
                            ਜੇ (ਕੁੰਜੀ_type->map[map_idx].ਸਰਗਰਮ && ਕੁੰਜੀ_type->map[map_idx].level == level) {
                                ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ xkb_mod_ਨਕਾਬ = ਕੁੰਜੀ_type->map[map_idx].mods.ਨਕਾਬ;
                                ਜੇ ((xkb_mod_ਨਕਾਬ | valid_mod_ਨਕਾਬ) == valid_mod_ਨਕਾਬ) {
                                    ਅਚਲ SDL_Keymod sdl_mod_ਨਕਾਬ = (xkb_mod_ਨਕਾਬ & ਖਿਸਕਾਓ_ਨਕਾਬ_2 ? SDL_KMOD_ਖਿਸਕਾਓ : 0) |
                                                                    (xkb_mod_ਨਕਾਬ & ਤਾਲਾ_ਨਕਾਬ ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_ਨਕਾਬ & ਅੰਕੜੇ->keyboard.alt_ਨਕਾਬ ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_ਨਕਾਬ & ਅੰਕੜੇ->keyboard.level3_ਨਕਾਬ ? SDL_KMOD_ਬਹੁਲਕ : 0) |
                                                                    (xkb_mod_ਨਕਾਬ & ਅੰਕੜੇ->keyboard.level5_ਨਕਾਬ ? SDL_KMOD_LEVEL5 : 0);

                                    X11_ਜੋੜੋ_Keymap_ਇੰਦਰਾਜ(keymap, xkeycode, keysym, scancode, sdl_mod_ਨਕਾਬ);
                                    ਕੁੰਜੀ_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        ਜੇ (!level && !ਕੁੰਜੀ_added) {
                            X11_ਜੋੜੋ_Keymap_ਇੰਦਰਾਜ(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_ਸੈੱਟ_Keymap(ਅੰਕੜੇ->keyboard.xkb.keymaps[ਅੰਕੜੇ->keyboard.xkb.current_ਸਮੂਹ], send_event);
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        ਜੇ (!keymap) {
            ਵਾਪਸ;
        }

        ਜੇ (send_event) {
            ਜੇ (ਅੰਕੜੇ->keyboard.core.keysym_map) {
                X11_XFree(ਅੰਕੜੇ->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(ਅੰਕੜੇ->display, &ਅੰਕੜੇ->keyboard.core.min_keycode, &ਅੰਕੜੇ->keyboard.core.max_keycode);
            ਅੰਕੜੇ->keyboard.core.keysym_map = X11_XGetKeyboardMapping(ਅੰਕੜੇ->display, ਅੰਕੜੇ->keyboard.core.min_keycode,
                                                                     ਅੰਕੜੇ->keyboard.core.max_keycode - ਅੰਕੜੇ->keyboard.core.min_keycode,
                                                                     &ਅੰਕੜੇ->keyboard.core.keysyms_ਪ੍ਰਤੀ_ਕੁੰਜੀ);
        }

        ਲਈ (Uint32 xkeycode = ਅੰਕੜੇ->keyboard.core.min_keycode; xkeycode <= ਅੰਕੜੇ->keyboard.core.max_keycode; ++xkeycode) {
            ਅਚਲ SDL_Scancode scancode = ਅੰਕੜੇ->keyboard.ਕੁੰਜੀ_layout[xkeycode];
            ਜੇ (scancode == SDL_SCANCODE_UNKNOWN) {
                ਜਾਰੀ;
            }

            ਅਚਲ ਕੁੰਜੀ_Sym keysym = X11_ਕੁੰਜੀ_ਕੋਡ_ਮੰਜ਼ਿਲ_Sym(_this, xkeycode, 0, 0);
            ਜੇ (keysym != No_ਚਿੰਨ੍ਹ) {
                X11_ਜੋੜੋ_Keymap_ਇੰਦਰਾਜ(keymap, xkeycode, keysym, scancode, 0);
            }
        }

        ਅੰਕੜੇ->keyboard.alt_ਨਕਾਬ = Mod1_ਨਕਾਬ; // Alt or Meta
        ਅੰਕੜੇ->keyboard.gui_ਨਕਾਬ = Mod4_ਨਕਾਬ; // Super
        ਅੰਕੜੇ->keyboard.level3_ਨਕਾਬ = Mod5_ਨਕਾਬ; // Note: Not a typo, Mod5 = level 3 shift, and Mod3 = level 5 shift.
        ਅੰਕੜੇ->keyboard.level5_ਨਕਾਬ = Mod3_ਨਕਾਬ;
        ਅੰਕੜੇ->keyboard.numlock_ਨਕਾਬ = X11_Get_XModifier_ਨਕਾਬ(_this, SDL_SCANCODE_NUMLOCKCLEAR);
        ਅੰਕੜੇ->keyboard.scrolllock_ਨਕਾਬ = X11_Get_XModifier_ਨਕਾਬ(_this, SDL_SCANCODE_SCROLLLOCK);

        SDL_ਸੈੱਟ_Keymap(keymap, send_event);
    }
}

ਖਾਲੀ X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    ਜੇ (ਅੰਕੜੇ->im) {
        X11_XCloseIM(ਅੰਕੜੇ->im);
        ਅੰਕੜੇ->im = ਨਿਰਾ;
    } ਨਹੀਂਤਾਂ {
        X11_XUnregisterIMInstantiateCallback(ਅੰਕੜੇ->display, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, im_instantiate_handler, (XPointer)ਅੰਕੜੇ);
    }
#ਜੇ_ਅੰਤ // X_HAVE_UTF8_STRING

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ਜੇ (ਅੰਕੜੇ->keyboard.xkb_enabled) {
        ਲਈ (ਪੂਰਨ i = 0; i < Xkb_ਅੰਕ_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(ਅੰਕੜੇ->keyboard.xkb.keymaps[i]);
            ਅੰਕੜੇ->keyboard.xkb.keymaps[i] = ਨਿਰਾ;
        }

        ਜੇ (ਅੰਕੜੇ->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(ਅੰਕੜੇ->keyboard.xkb.desc_ptr, 0, True);
            ਅੰਕੜੇ->keyboard.xkb.desc_ptr = ਨਿਰਾ;
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        ਜੇ (ਅੰਕੜੇ->keyboard.core.keysym_map) {
        X11_XFree(ਅੰਕੜੇ->keyboard.core.keysym_map);
        ਅੰਕੜੇ->keyboard.core.keysym_map = ਨਿਰਾ;
    }
}

ਖਾਲੀ X11_ClearComposition(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    ਜੇ (ਅੰਕੜੇ->preedit_ਲੰਮਾਈ > 0) {
        ਅੰਕੜੇ->preedit_ਪਾਠ[0] = '\0';
        ਅੰਕੜੇ->preedit_ਲੰਮਾਈ = 0;
    }

    ਜੇ (ਅੰਕੜੇ->ime_needs_clear_composition) {
        SDL_Send_Editing_ਪਾਠ("", 0, 0);
        ਅੰਕੜੇ->ime_needs_clear_composition = false;
    }
}

ਸਥਿਰ ਖਾਲੀ X11_SendEditingEvent(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    ਜੇ (ਅੰਕੜੇ->preedit_ਲੰਮਾਈ == 0) {
        X11_ClearComposition(ਅੰਕੜੇ);
        ਵਾਪਸ;
    }

    bool ਵਿੱਚ_highlight = false;
    ਪੂਰਨ ਸ਼ੁਰੂ = -1, ਲੰਮਾਈ = 0, i;
    ਲਈ (i = 0; i < ਅੰਕੜੇ->preedit_ਲੰਮਾਈ; ++i) {
        ਜੇ (ਅੰਕੜੇ->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            ਜੇ (ਸ਼ੁਰੂ < 0) {
                ਸ਼ੁਰੂ = i;
                ਵਿੱਚ_highlight = true;
            }
        } ਨਹੀਂਤਾਂ ਜੇ (ਵਿੱਚ_highlight) {
            // Found the end of the highlight
            ਰੋਕੋ;
        }
    }
    ਜੇ (ਵਿੱਚ_highlight) {
        ਲੰਮਾਈ = (i - ਸ਼ੁਰੂ);
    } ਨਹੀਂਤਾਂ {
        ਸ਼ੁਰੂ = SDL_clamp(ਅੰਕੜੇ->preedit_cursor, 0, ਅੰਕੜੇ->preedit_ਲੰਮਾਈ);
    }
    SDL_Send_Editing_ਪਾਠ(ਅੰਕੜੇ->preedit_ਪਾਠ, ਸ਼ੁਰੂ, ਲੰਮਾਈ);

    ਅੰਕੜੇ->ime_needs_clear_composition = true;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
ਸਥਿਰ ਪੂਰਨ preedit_ਸ਼ੁਰੂ_callback(XIC xic, XPointer client_ਅੰਕੜੇ_2, XPointer call_ਅੰਕੜੇ_2)
{
    // No limit on preedit text length
    ਵਾਪਸ -1;
}

ਸਥਿਰ ਖਾਲੀ preedit_ਪੂਰਾ_callback(XIC xic, XPointer client_ਅੰਕੜੇ_2, XPointer call_ਅੰਕੜੇ_2)
{
}

ਸਥਿਰ ਖਾਲੀ preedit_draw_callback(XIC xic, XPointer client_ਅੰਕੜੇ_2, XIMPreeditDrawCallbackStruct *call_ਅੰਕੜੇ_2)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)client_ਅੰਕੜੇ_2;
    ਪੂਰਨ chg_ਪਹਿਲਾ = SDL_clamp(call_ਅੰਕੜੇ_2->chg_ਪਹਿਲਾ, 0, ਅੰਕੜੇ->preedit_ਲੰਮਾਈ);
    ਪੂਰਨ chg_ਲੰਮਾਈ = SDL_clamp(call_ਅੰਕੜੇ_2->chg_ਲੰਮਾਈ, 0, ਅੰਕੜੇ->preedit_ਲੰਮਾਈ - chg_ਪਹਿਲਾ);

    ਅਚਲ ਅੱਖਰ *ਸ਼ੁਰੂ = ਅੰਕੜੇ->preedit_ਪਾਠ;
    ਜੇ (chg_ਲੰਮਾਈ > 0) {
        // Delete text in range
        ਲਈ (ਪੂਰਨ i = 0; ਸ਼ੁਰੂ && *ਸ਼ੁਰੂ && i < chg_ਪਹਿਲਾ; ++i) {
            SDL_ਕਦਮ_UTF8(&ਸ਼ੁਰੂ, ਨਿਰਾ);
        }

        ਅਚਲ ਅੱਖਰ *ਸਿਰਾ = ਸ਼ੁਰੂ;
        ਲਈ (ਪੂਰਨ i = 0; ਸਿਰਾ && *ਸਿਰਾ && i < chg_ਲੰਮਾਈ; ++i) {
            SDL_ਕਦਮ_UTF8(&ਸਿਰਾ, ਨਿਰਾ);
        }

        ਜੇ (ਸਿਰਾ > ਸ਼ੁਰੂ) {
            SDL_memmove((ਅੱਖਰ *)ਸ਼ੁਰੂ, ਸਿਰਾ, SDL_strlen(ਸਿਰਾ) + 1);
            ਜੇ ((chg_ਪਹਿਲਾ + chg_ਲੰਮਾਈ) > ਅੰਕੜੇ->preedit_ਲੰਮਾਈ) {
                SDL_memmove(&ਅੰਕੜੇ->preedit_feedback[chg_ਪਹਿਲਾ], &ਅੰਕੜੇ->preedit_feedback[chg_ਪਹਿਲਾ + chg_ਲੰਮਾਈ], (ਅੰਕੜੇ->preedit_ਲੰਮਾਈ - chg_ਪਹਿਲਾ - chg_ਲੰਮਾਈ) * ਆਕਾਰ(*ਅੰਕੜੇ->preedit_feedback));
            }
        }
        ਅੰਕੜੇ->preedit_ਲੰਮਾਈ -= chg_ਲੰਮਾਈ;
    }

    XIMText *ਪਾਠ = call_ਅੰਕੜੇ_2->ਪਾਠ;
    ਜੇ (ਪਾਠ) {
        // Insert text in range
        SDL_assert(!ਪਾਠ->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        ਜੇ (ਪਾਠ->string.multi_byte) {
            ਪਾਠ->ਲੰਮਾਈ = SDL_utf8strlen(ਪਾਠ->string.multi_byte);
        }

        size_t string_ਮਾਪ = SDL_strlen(ਪਾਠ->string.multi_byte);
        size_t ਮਾਪ = string_ਮਾਪ + 1;
        ਜੇ (ਅੰਕੜੇ->preedit_ਪਾਠ) {
            ਮਾਪ += SDL_strlen(ਅੰਕੜੇ->preedit_ਪਾਠ);
        }
        ਅੱਖਰ *preedit_ਪਾਠ = (ਅੱਖਰ *)SDL_malloc(ਮਾਪ * ਆਕਾਰ(*preedit_ਪਾਠ));
        ਜੇ (preedit_ਪਾਠ) {
            size_t pre_ਮਾਪ = (ਸ਼ੁਰੂ - ਅੰਕੜੇ->preedit_ਪਾਠ);
            size_t post_ਮਾਪ = ਸ਼ੁਰੂ ? SDL_strlen(ਸ਼ੁਰੂ) : 0;
            ਜੇ (pre_ਮਾਪ > 0) {
                SDL_memcpy(&preedit_ਪਾਠ[0], ਅੰਕੜੇ->preedit_ਪਾਠ, pre_ਮਾਪ);
            }
            SDL_memcpy(&preedit_ਪਾਠ[pre_ਮਾਪ], ਪਾਠ->string.multi_byte, string_ਮਾਪ);
            ਜੇ (post_ਮਾਪ > 0) {
                SDL_memcpy(&preedit_ਪਾਠ[pre_ਮਾਪ + string_ਮਾਪ], ਸ਼ੁਰੂ, post_ਮਾਪ);
            }
            preedit_ਪਾਠ[ਮਾਪ - 1] = '\0';
        }

        size_t feedback_ਮਾਪ = ਅੰਕੜੇ->preedit_ਲੰਮਾਈ + ਪਾਠ->ਲੰਮਾਈ;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_ਮਾਪ * ਆਕਾਰ(*feedback));
        ਜੇ (feedback) {
            size_t pre_ਮਾਪ = (size_t)chg_ਪਹਿਲਾ;
            size_t post_ਮਾਪ = (size_t)ਅੰਕੜੇ->preedit_ਲੰਮਾਈ - pre_ਮਾਪ;
            ਜੇ (pre_ਮਾਪ > 0) {
                SDL_memcpy(&feedback[0], ਅੰਕੜੇ->preedit_feedback, pre_ਮਾਪ * ਆਕਾਰ(*feedback));
            }
            SDL_memcpy(&feedback[pre_ਮਾਪ], ਪਾਠ->feedback, ਪਾਠ->ਲੰਮਾਈ * ਆਕਾਰ(*feedback));
            ਜੇ (post_ਮਾਪ > 0) {
                SDL_memcpy(&feedback[pre_ਮਾਪ + ਪਾਠ->ਲੰਮਾਈ], &ਅੰਕੜੇ->preedit_feedback[pre_ਮਾਪ], post_ਮਾਪ * ਆਕਾਰ(*feedback));
            }
        }

        ਜੇ (preedit_ਪਾਠ && feedback) {
            SDL_free(ਅੰਕੜੇ->preedit_ਪਾਠ);
            ਅੰਕੜੇ->preedit_ਪਾਠ = preedit_ਪਾਠ;

            SDL_free(ਅੰਕੜੇ->preedit_feedback);
            ਅੰਕੜੇ->preedit_feedback = feedback;

            ਅੰਕੜੇ->preedit_ਲੰਮਾਈ += ਪਾਠ->ਲੰਮਾਈ;
        } ਨਹੀਂਤਾਂ {
            SDL_free(preedit_ਪਾਠ);
            SDL_free(feedback);
        }
    }

    ਅੰਕੜੇ->preedit_cursor = call_ਅੰਕੜੇ_2->caret;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_XIM
    ਜੇ (call_ਅੰਕੜੇ_2->chg_ਲੰਮਾਈ > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_ਅੰਕੜੇ_2->chg_ਲੰਮਾਈ, call_ਅੰਕੜੇ_2->chg_ਪਹਿਲਾ);
    }
    ਜੇ (ਪਾਠ) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", ਪਾਠ->string.multi_byte, call_ਅੰਕੜੇ_2->chg_ਪਹਿਲਾ, call_ਅੰਕੜੇ_2->caret);
    }
    SDL_Log("Pre-edit text: %s", ਅੰਕੜੇ->preedit_ਪਾਠ);
#ਜੇ_ਅੰਤ

    X11_SendEditingEvent(ਅੰਕੜੇ);
}

ਸਥਿਰ ਖਾਲੀ preedit_caret_callback(XIC xic, XPointer client_ਅੰਕੜੇ_2, XIMPreeditCaretCallbackStruct *call_ਅੰਕੜੇ_2)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)client_ਅੰਕੜੇ_2;

    ਚੋਣ (call_ਅੰਕੜੇ_2->direction) {
    ਹਾਲਤ XIMAbsolutePosition:
        ਜੇ (call_ਅੰਕੜੇ_2->position != ਅੰਕੜੇ->preedit_cursor) {
            ਅੰਕੜੇ->preedit_cursor = call_ਅੰਕੜੇ_2->position;
            X11_SendEditingEvent(ਅੰਕੜੇ);
        }
        ਰੋਕੋ;
    ਹਾਲਤ XIMDontChange:
        ਰੋਕੋ;
    ਮੂਲ:
        // Not currently supported
        ਰੋਕੋ;
    }
}

ਸਥਿਰ ਖਾਲੀ ic_destroyed_handler(XIC ic, XPointer client_ਅੰਕੜੇ, XPointer call_ਅੰਕੜੇ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)client_ਅੰਕੜੇ;
    ਅੰਕੜੇ->ic = ਨਿਰਾ;
    X11_Destroy_ਨਿਵੇਸ਼_Context(ਅੰਕੜੇ);

    // If the IM was already recreated, create a new IC.
    ਜੇ (ਅੰਕੜੇ->videodata->im) {
        X11_Create_ਨਿਵੇਸ਼_Context(ਅੰਕੜੇ);
    }
}
#ਜੇ_ਅੰਤ // X_HAVE_UTF8_STRING

ਖਾਲੀ X11_Create_ਨਿਵੇਸ਼_Context(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    SDL_Video_ਅੰਕੜੇ *videodata = ਅੰਕੜੇ->videodata;

    ਜੇ (SDL_X11_HAVE_UTF8 && videodata->im) {
        ਅਚਲ ਅੱਖਰ *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_ਅੰਕੜੇ_2 = (XPointer)ਅੰਕੜੇ;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        ਜੇ (hint && SDL_strstr(hint, "composition")) {
            XIMCallback draw_callback;
            draw_callback.client_ਅੰਕੜੇ_2 = (XPointer)ਅੰਕੜੇ;
            draw_callback.callback = (XIMProc)preedit_draw_callback;

            XIMCallback ਸ਼ੁਰੂ_callback;
            ਸ਼ੁਰੂ_callback.client_ਅੰਕੜੇ_2 = (XPointer)ਅੰਕੜੇ;
            ਸ਼ੁਰੂ_callback.callback = (XIMProc)preedit_ਸ਼ੁਰੂ_callback;

            XIMCallback ਪੂਰਾ_callback;
            ਪੂਰਾ_callback.client_ਅੰਕੜੇ_2 = (XPointer)ਅੰਕੜੇ;
            ਪੂਰਾ_callback.callback = (XIMProc)preedit_ਪੂਰਾ_callback;

            XIMCallback caret_callback;
            caret_callback.client_ਅੰਕੜੇ_2 = (XPointer)ਅੰਕੜੇ;
            caret_callback.callback = (XIMProc)preedit_caret_callback;

            XVaNestedList attr = X11_XVaCreateNestedList(0,
                                                         XNPreedit_ਸ਼ੁਰੂ_Callback, &ਸ਼ੁਰੂ_callback,
                                                         XNPreedit_ਪੂਰਾ_Callback, &ਪੂਰਾ_callback,
                                                         XNPreeditDrawCallback, &draw_callback,
                                                         XNPreeditCaretCallback, &caret_callback,
                                                         ਨਿਰਾ);
            ਜੇ (attr) {
                ਅੰਕੜੇ->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreedit_ਗੁਣ, attr,
                                         XNClient_ਖਿੜਕੀ, ਅੰਕੜੇ->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         ਨਿਰਾ);
                X11_XFree(attr);
            }
        }
        ਜੇ (!ਅੰਕੜੇ->ic) {
            ਅੰਕੜੇ->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClient_ਖਿੜਕੀ, ਅੰਕੜੇ->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     ਨਿਰਾ);
        }
        ਅੰਕੜੇ->xim_spot.x = -1;
        ਅੰਕੜੇ->xim_spot.y = -1;
    }
#ਜੇ_ਅੰਤ // X_HAVE_UTF8_STRING
}


ਖਾਲੀ X11_Destroy_ਨਿਵੇਸ਼_Context(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    ਜੇ (ਅੰਕੜੇ->ic) {
        X11_XDestroyIC(ਅੰਕੜੇ->ic);
        ਅੰਕੜੇ->ic = ਨਿਰਾ;
    }
    SDL_free(ਅੰਕੜੇ->preedit_ਪਾਠ);
    SDL_free(ਅੰਕੜੇ->preedit_feedback);
    ਅੰਕੜੇ->preedit_ਪਾਠ = ਨਿਰਾ;
    ਅੰਕੜੇ->preedit_feedback = ਨਿਰਾ;
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਖਾਲੀ X11_ResetXIM(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ && ਅੰਕੜੇ->ic) {
        // Clear any partially entered dead keys
        ਅੱਖਰ *contents = X11_Xutf8ResetIC(ਅੰਕੜੇ->ic);
        ਜੇ (contents) {
            X11_XFree(contents);
        }
    }
#ਜੇ_ਅੰਤ // X_HAVE_UTF8_STRING
}

bool X11_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, ਖਿੜਕੀ);

    ਵਾਪਸ X11_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area(_this, ਖਿੜਕੀ);
}

bool X11_Stop_ਪਾਠ_ਨਿਵੇਸ਼(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    X11_ResetXIM(_this, ਖਿੜਕੀ);
    ਵਾਪਸ true;
}

bool X11_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ && ਅੰਕੜੇ->ic) {
        XPoint spot;
        spot.x = ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.x + ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_cursor;
        spot.y = ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.y + ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.h;
        ਜੇ (spot.x != ਅੰਕੜੇ->xim_spot.x || spot.y != ਅੰਕੜੇ->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, ਨਿਰਾ);
            ਜੇ (attr) {
                X11_XSetICValues(ਅੰਕੜੇ->ic, XNPreedit_ਗੁਣ, attr, ਨਿਰਾ);
                X11_XFree(attr);
            }
            SDL_copyp(&ਅੰਕੜੇ->xim_spot, &spot);
        }
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    ਵਾਪਸ videodata->use_steam_screen_keyboard;
}

ਖਾਲੀ X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ਅਚਲ ਪੂਰਨ k_EFloating_Gamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_ਬਹੁਲਕ_Single_ਸਤਰ = 0;    // Enter dismisses the keyboard
        ਅਚਲ ਪੂਰਨ k_EFloating_Gamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_ਬਹੁਲਕ_ਗੁਣਜ_ਸਤਰਾਂ = 1; // User needs to explicitly dismiss the keyboard
        ਅਚਲ ਪੂਰਨ k_EFloating_Gamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_ਬਹੁਲਕ_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ਅਚਲ ਪੂਰਨ k_EFloating_Gamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_ਬਹੁਲਕ_Numeric = 3;       // Numeric keypad is shown
        ਅੱਖਰ deeplink[128];
        ਪੂਰਨ ਬਹੁਲਕ;

        ਚੋਣ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Type(props)) {
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_EMAIL:
            ਬਹੁਲਕ = k_EFloating_Gamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_ਬਹੁਲਕ_Email;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ:
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ_PASSWORD_HIDDEN:
        ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ_PASSWORD_VISIBLE:
            ਬਹੁਲਕ = k_EFloating_Gamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_ਬਹੁਲਕ_Numeric;
            ਰੋਕੋ;
        ਮੂਲ:
            ਜੇ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Multiline(props)) {
                ਬਹੁਲਕ = k_EFloating_Gamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_ਬਹੁਲਕ_ਗੁਣਜ_ਸਤਰਾਂ;
            } ਨਹੀਂਤਾਂ {
                ਬਹੁਲਕ = k_EFloating_Gamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_ਬਹੁਲਕ_Single_ਸਤਰ;
            }
            ਰੋਕੋ;
        }
        (ਖਾਲੀ)SDL_snprintf(deeplink, ਆਕਾਰ(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.x, ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.y,
                           ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.w, ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect.h,
                           ਬਹੁਲਕ);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

ਖਾਲੀ X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
