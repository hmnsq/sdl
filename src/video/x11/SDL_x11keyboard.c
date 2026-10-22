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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"

#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_scancode_tables_c.h"

#ಅನ್ತರ್ಭಾವ <X11/keysym.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#ಅನ್ತರ್ಭಾವ <X11/XKBlib.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "../../events/imKStoUCS.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keysym_to_scancode_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keysym_to_keycode_c.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
#ಅನ್ತರ್ಭಾವ <locale.h>
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ SDL_Scancode_ಕೋಷ್ಟಕ scancode_ಗಣ[] = {
    SDL_SCANCODE_ಕೋಷ್ಟಕ_DARWIN,
    SDL_SCANCODE_ಕೋಷ್ಟಕ_XFREE86_1,
    SDL_SCANCODE_ಕೋಷ್ಟಕ_XFREE86_2,
    SDL_SCANCODE_ಕೋಷ್ಟಕ_XVNC,
};

ಸ್ಥಿರ bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    ಆಯ್ಕೆ (scancode) {
    ಸ್ಥಿತಿ SDL_SCANCODE_ESCAPE:
    ಸ್ಥಿತಿ SDL_SCANCODE_CAPSLOCK:
    ಸ್ಥಿತಿ SDL_SCANCODE_NUMLOCKCLEAR:
    ಸ್ಥಿತಿ SDL_SCANCODE_LSHIFT:
    ಸ್ಥಿತಿ SDL_SCANCODE_RSHIFT:
    ಸ್ಥಿತಿ SDL_SCANCODE_LCTRL:
    ಸ್ಥಿತಿ SDL_SCANCODE_RCTRL:
    ಸ್ಥಿತಿ SDL_SCANCODE_LALT:
    ಸ್ಥಿತಿ SDL_SCANCODE_RALT:
    ಸ್ಥಿತಿ SDL_SCANCODE_LGUI:
    ಸ್ಥಿತಿ SDL_SCANCODE_RGUI:
        ಹಿಂತಿರುಗಿ false;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ true;
    }
}

ಸ್ಥಿರ ಕೀಲಿ_Sym X11_ಕೀಲಿ_ಸಂಕೇತ_ಗಮ್ಯ_Sym(SDL_VideoDevice *_this, ಕೀಲಿ_ಸಂಕೇತ_2 keycode, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಗುಂಪು, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ level)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    ಕೀಲಿ_Sym keysym;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ಆದರೆ (ದತ್ತಾಂಶ->keyboard.xkb_enabled) {
        keysym = X11_Xkb_Keycode_ಗಮ್ಯ_Keysym(ದತ್ತಾಂಶ->display, keycode, ಗುಂಪು, level);
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        // TODO: Handle groups on the legacy path.
        ಆದರೆ (keycode >= ದತ್ತಾಂಶ->keyboard.core.min_keycode && keycode <= ದತ್ತಾಂಶ->keyboard.core.max_keycode) {
            keysym = ದತ್ತಾಂಶ->keyboard.core.keysym_map[(keycode - ದತ್ತಾಂಶ->keyboard.core.min_keycode) * ದತ್ತಾಂಶ->keyboard.core.keysyms_ಪ್ರತಿ_ಕೀಲಿ];
        } ಇಲ್ಲದಿದ್ದರೆ {
            keysym = No_ಚಿಹ್ನೆ;
        }
    }

    ಹಿಂತಿರುಗಿ keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
ಸ್ಥಿರ SDL_Scancode X11_ಕೀಲಿ_ಸಂಕೇತ_ಗಮ್ಯ_SDLScancode(SDL_VideoDevice *_this, ಕೀಲಿ_ಸಂಕೇತ_2 keycode)
{
    ಸ್ಥಿರಾಂಕ ಕೀಲಿ_Sym keysym = X11_ಕೀಲಿ_ಸಂಕೇತ_ಗಮ್ಯ_Sym(_this, keycode, 0, 0);

    ಆದರೆ (keysym == No_ಚಿಹ್ನೆ) {
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ SDL_Get_Scancode_From_ಕೀಲಿ_Sym(keysym, keycode);
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
ಸ್ಥಿರ bool X11_InitIM(SDL_Video_ದತ್ತಾಂಶ *videodata);

ಸ್ಥಿರ ಶೂನ್ಯ im_instantiate_handler(Display *display, XPointer client_ದತ್ತಾಂಶ, XPointer call_ದತ್ತಾಂಶ)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)client_ದತ್ತಾಂಶ;

    ಆದರೆ (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, im_instantiate_handler, client_ದತ್ತಾಂಶ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ im_destroyed_handler(XIM im, XPointer client_ದತ್ತಾಂಶ, XPointer call_ದತ್ತಾಂಶ)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)client_ದತ್ತಾಂಶ;

    videodata->im = ಖಾಲಿ;
    X11_XRegisterIMInstantiateCallback(videodata->display, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, im_instantiate_handler, client_ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ bool X11_InitIM(SDL_Video_ದತ್ತಾಂಶ *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    ಅಕ್ಷರ *prev_locale = setlocale(LC_ALL, ಖಾಲಿ);
    ಅಕ್ಷರ *prev_xmods = X11_XSetLocaleModifiers(ಖಾಲಿ);

    ಆದರೆ (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    ಆದರೆ (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (ಶೂನ್ಯ)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (ಶೂನ್ಯ)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    ಆದರೆ (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_ದತ್ತಾಂಶ_2 = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (ಅಕ್ಷರ *)ಖಾಲಿ);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < videodata->numwindows; ++i) {
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *w = videodata->windowlist[i];
            ಆದರೆ (!w->ic) {
                X11_Create_ಒಳಹರಿವು_Context(w);
            }
        }

        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ false;
}
#ಆದರೆ_ಅಂತ್ಯ // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ i = 0;
    ಪೂರ್ಣಾಂಕ j = 0;
    ಪೂರ್ಣಾಂಕ min_keycode, max_keycode;
    ರಚನೆ
    {
        SDL_Scancode scancode;
        ಕೀಲಿ_Sym keysym;
        ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_ಪೂರ್ವ, 0 },
        { SDL_SCANCODE_ಮೇಲೆ, XK_ಮೇಲೆ, 0 },
        { SDL_SCANCODE_ಎಡ, XK_ಎಡ, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    ಪೂರ್ಣಾಂಕ ಉತ್ತಮ_ದೂರ;
    ಪೂರ್ಣಾಂಕ ಉತ್ತಮ_ಸೂಚ್ಯಂಕ;
    ಪೂರ್ಣಾಂಕ ದೂರ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ಪೂರ್ಣಾಂಕ xkb_major = Xkb_Major_ಆವೃತ್ತಿ;
    ಪೂರ್ಣಾಂಕ xkb_minor = Xkb_Minor_ಆವೃತ್ತಿ;

    ಆದರೆ (X11_XkbQueryExtension(ದತ್ತಾಂಶ->display, ಖಾಲಿ, &ದತ್ತಾಂಶ->keyboard.xkb.event, ಖಾಲಿ, &xkb_major, &xkb_minor)) {
        Bool xkb_repeat = 0;
        ದತ್ತಾಂಶ->keyboard.xkb_enabled = true;
        ದತ್ತಾಂಶ->keyboard.xkb.desc_ptr = X11_XkbGetMap(ದತ್ತಾಂಶ->display, Xkb_All_Client_Info_ಮುಖವಾಡ, XkbUseCoreKbd);

        // This will remove KeyRelease events for held keys.
        X11_Xkb_ಗಣ_Detectable_Auto_Repeat(ದತ್ತಾಂಶ->display, True, &xkb_repeat);

        // Enable the key mapping and state events.
        X11_XkbSelectEvents(ದತ್ತಾಂಶ->display, XkbUseCoreKbd,
                            Xkb_New_Keyboard_Notify_ಮುಖವಾಡ | Xkb_Map_Notify_ಮುಖವಾಡ | Xkb_State_Notify_ಮುಖವಾಡ,
                            Xkb_New_Keyboard_Notify_ಮುಖವಾಡ | Xkb_Map_Notify_ಮುಖವಾಡ | Xkb_State_Notify_ಮುಖವಾಡ);
        X11_XkbSelectEventDetails(ದತ್ತಾಂಶ->display, XkbUseCoreKbd, XkbStateNotify, Xkb_ಗುಂಪು_State_ಮುಖವಾಡ | Xkb_Modifier_State_ಮುಖವಾಡ, Xkb_ಗುಂಪು_State_ಮುಖವಾಡ | Xkb_Modifier_State_ಮುಖವಾಡ);
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(ದತ್ತಾಂಶ->display, &ದತ್ತಾಂಶ->keyboard.core.min_keycode, &ದತ್ತಾಂಶ->keyboard.core.max_keycode);
        ದತ್ತಾಂಶ->keyboard.core.keysym_map = X11_XGetKeyboardMapping(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->keyboard.core.min_keycode,
                                                              ದತ್ತಾಂಶ->keyboard.core.max_keycode - ದತ್ತಾಂಶ->keyboard.core.min_keycode,
                                                              &ದತ್ತಾಂಶ->keyboard.core.keysyms_ಪ್ರತಿ_ಕೀಲಿ);
    }

    // Open a connection to the X input manager
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    ಆದರೆ (SDL_X11_HAVE_UTF8) {
        ಆದರೆ (!X11_InitIM(ದತ್ತಾಂಶ)) {
            X11_XRegisterIMInstantiateCallback(ದತ್ತಾಂಶ->display, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, im_instantiate_handler, (XPointer)ದತ್ತಾಂಶ);
        }
    }
#ಆದರೆ_ಅಂತ್ಯ
    // Try to determine which scancodes are being used based on fingerprint
    ಉತ್ತಮ_ದೂರ = SDL_arraysize(fingerprint) + 1;
    ಉತ್ತಮ_ಸೂಚ್ಯಂಕ = -1;
    X11_XDisplayKeycodes(ದತ್ತಾಂಶ->display, &min_keycode, &max_keycode);
    ಗಾಗಿ (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].ಮೌಲ್ಯ = X11_XKeysym_ಗಮ್ಯ_Keycode(ದತ್ತಾಂಶ->display, fingerprint[i].keysym) - min_keycode;
    }
    ಗಾಗಿ (i = 0; i < SDL_arraysize(scancode_ಗಣ); ++i) {
        ಪೂರ್ಣಾಂಕ ಕೋಷ್ಟಕ_ಗಾತ್ರ;
        ಸ್ಥಿರಾಂಕ SDL_Scancode *ಕೋಷ್ಟಕ = SDL_Get_Scancode_ಕೋಷ್ಟಕ(scancode_ಗಣ[i], &ಕೋಷ್ಟಕ_ಗಾತ್ರ);

        ದೂರ = 0;
        ಗಾಗಿ (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            ಆದರೆ (fingerprint[j].ಮೌಲ್ಯ < 0 || fingerprint[j].ಮೌಲ್ಯ >= ಕೋಷ್ಟಕ_ಗಾತ್ರ) {
                ದೂರ += 1;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕೋಷ್ಟಕ[fingerprint[j].ಮೌಲ್ಯ] != fingerprint[j].scancode) {
                ದೂರ += 1;
            }
        }
        ಆದರೆ (ದೂರ < ಉತ್ತಮ_ದೂರ) {
            ಉತ್ತಮ_ದೂರ = ದೂರ;
            ಉತ್ತಮ_ಸೂಚ್ಯಂಕ = i;
        }
    }
    ಆದರೆ (ಉತ್ತಮ_ಸೂಚ್ಯಂಕ < 0 || ಉತ್ತಮ_ದೂರ > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        ಪೂರ್ಣಾಂಕ fingerprint_ಮೌಲ್ಯ = X11_XKeysym_ಗಮ್ಯ_Keycode(ದತ್ತಾಂಶ->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        ಆದರೆ (fingerprint_ಮೌಲ್ಯ == 235) {
            ಗಾಗಿ (i = 0; i < SDL_arraysize(scancode_ಗಣ); ++i) {
                ಆದರೆ (scancode_ಗಣ[i] == SDL_SCANCODE_ಕೋಷ್ಟಕ_XFREE86_2) {
                    ಉತ್ತಮ_ಸೂಚ್ಯಂಕ = i;
                    ಉತ್ತಮ_ದೂರ = 0;
                    ನಿಲ್ಲಿಸು;
                }
            }
        }
    }
    ಆದರೆ (ಉತ್ತಮ_ಸೂಚ್ಯಂಕ >= 0 && ಉತ್ತಮ_ದೂರ <= 2) {
        ಪೂರ್ಣಾಂಕ ಕೋಷ್ಟಕ_ಗಾತ್ರ;
        ಸ್ಥಿರಾಂಕ SDL_Scancode *ಕೋಷ್ಟಕ = SDL_Get_Scancode_ಕೋಷ್ಟಕ(scancode_ಗಣ[ಉತ್ತಮ_ಸೂಚ್ಯಂಕ], &ಕೋಷ್ಟಕ_ಗಾತ್ರ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", ಉತ್ತಮ_ಸೂಚ್ಯಂಕ, min_keycode, max_keycode, ಕೋಷ್ಟಕ_ಗಾತ್ರ);
#ಆದರೆ_ಅಂತ್ಯ
        // This should never happen, but just in case...
        ಆದರೆ (ಕೋಷ್ಟಕ_ಗಾತ್ರ > (SDL_arraysize(ದತ್ತಾಂಶ->keyboard.ಕೀಲಿ_layout) - min_keycode)) {
            ಕೋಷ್ಟಕ_ಗಾತ್ರ = (SDL_arraysize(ದತ್ತಾಂಶ->keyboard.ಕೀಲಿ_layout) - min_keycode);
        }
        SDL_memcpy(&ದತ್ತಾಂಶ->keyboard.ಕೀಲಿ_layout[min_keycode], ಕೋಷ್ಟಕ, ಗಾತ್ರ(SDL_Scancode) * ಕೋಷ್ಟಕ_ಗಾತ್ರ);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        ಗಾಗಿ (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_ಕೀಲಿ_ಸಂಕೇತ_ಗಮ್ಯ_SDLScancode(_this, i);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_KEYBOARD
            {
                ಕೀಲಿ_Sym sym;
                sym = X11_ಕೀಲಿ_ಸಂಕೇತ_ಗಮ್ಯ_Sym(_this, (ಕೀಲಿ_ಸಂಕೇತ_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)sym, sym == No_ಚಿಹ್ನೆ ? "NoSymbol" : X11_XKeysym_ಗಮ್ಯ_String(sym));
            }
#ಆದರೆ_ಅಂತ್ಯ
            ಆದರೆ (scancode == ದತ್ತಾಂಶ->keyboard.ಕೀಲಿ_layout[i]) {
                ಮುಂದುವರಿ;
            }
            ಆದರೆ ((SDL_GetKeymapKeycode(ಖಾಲಿ, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_ಮುಖವಾಡ | SDLK_EXTENDED_ಮುಖವಾಡ)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", ದತ್ತಾಂಶ->ಕೀಲಿ_layout[i], SDL_GetScancodeName(ದತ್ತಾಂಶ->ಕೀಲಿ_layout[i]), scancode, SDL_GetScancodeName(scancode));
#ಆದರೆ_ಅಂತ್ಯ
                ದತ್ತಾಂಶ->keyboard.ಕೀಲಿ_layout[i] = scancode;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#ಆದರೆ_ಅಂತ್ಯ

        // Determine key_layout - only works on US QWERTY layout
        ಗಾಗಿ (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_ಕೀಲಿ_ಸಂಕೇತ_ಗಮ್ಯ_SDLScancode(_this, i);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_SCANCODES
            {
                ಕೀಲಿ_Sym sym;
                sym = X11_ಕೀಲಿ_ಸಂಕೇತ_ಗಮ್ಯ_Sym(_this, (ಕೀಲಿ_ಸಂಕೇತ_2)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)sym, sym == No_ಚಿಹ್ನೆ ? "NoSymbol" : X11_XKeysym_ಗಮ್ಯ_String(sym));
            }
            ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } ಇಲ್ಲದಿದ್ದರೆ {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#ಆದರೆ_ಅಂತ್ಯ
            ದತ್ತಾಂಶ->keyboard.ಕೀಲಿ_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_ಗಣ_Scancode_Name(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ X11_Get_Xkb_Virtual_Modifier_ಮುಖವಾಡ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *vmod_name)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ mod_ಮುಖವಾಡ = 0;

    ಸ್ಥಿರಾಂಕ Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    ಆದರೆ (vmod != None) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < Xkb_ಅಂಕೆ_Virtual_Mods; ++i) {
            ಆದರೆ (vmod == videodata->keyboard.xkb.desc_ptr->ಹೆಸರುಗಳು->vmods[i]) {
                mod_ಮುಖವಾಡ = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                ನಿಲ್ಲಿಸು;
            }
        }
    }

    ಹಿಂತಿರುಗಿ mod_ಮುಖವಾಡ;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ X11_Get_XModifier_ಮುಖವಾಡ(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    Display *display = videodata->display;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ mod_ಮುಖವಾಡ = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ n = xmods->max_keypermod;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 3; i < 8; i++) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < n; j++) {
            ಸ್ಥಿರಾಂಕ ಕೀಲಿ_ಸಂಕೇತ_2 kc = xmods->modifiermap[i * n + j];
            ಆದರೆ (videodata->keyboard.ಕೀಲಿ_layout[kc] == scancode) {
                mod_ಮುಖವಾಡ = 1 << i;
                ನಿಲ್ಲಿಸು;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    ಹಿಂತಿರುಗಿ mod_ಮುಖವಾಡ;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_ಕೂಡಿಸು_Keymap_ನಮೂದು(SDL_Keymap *keymap, Uint32 xkeycode, ಕೀಲಿ_Sym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_ಮುಖವಾಡ)
{
    SDL_Keycode keycode = SDL_Get_ಕೀಲಿ_ಸಂಕೇತ_From_ಕೀಲಿ_Sym(xkeysym, xkeycode, sdl_mod_ಮುಖವಾಡ);

    ಆದರೆ (!keycode) {
        ಆಯ್ಕೆ (sdl_scancode) {
        ಸ್ಥಿತಿ SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            keycode = SDL_SCANCODE_ಗಮ್ಯ_KEYCODE(sdl_scancode);
            ನಿಲ್ಲಿಸು;
        }
    }

    SDL_ಗಣ_Keymap_ನಮೂದು(keymap, sdl_scancode, sdl_mod_ಮುಖವಾಡ, keycode);
}

ಶೂನ್ಯ X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ಆದರೆ (ದತ್ತಾಂಶ->keyboard.xkb_enabled) {
        XkbStateRec state;

        ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i = 0; i < Xkb_ಅಂಕೆ_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(ದತ್ತಾಂಶ->keyboard.xkb.keymaps[i]);
            ದತ್ತಾಂಶ->keyboard.xkb.keymaps[i] = ಖಾಲಿ;
        }

        X11_Xkb_Get_ಹೆಸರುಗಳು(ದತ್ತಾಂಶ->display, Xkb_Virtual_Mod_ಹೆಸರುಗಳು_ಮುಖವಾಡ, ದತ್ತಾಂಶ->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(ದತ್ತಾಂಶ->display, Xkb_All_Client_Info_ಮುಖವಾಡ | Xkb_Virtual_Mods_ಮುಖವಾಡ, ದತ್ತಾಂಶ->keyboard.xkb.desc_ptr);

        ಆದರೆ (X11_XkbGetState(ದತ್ತಾಂಶ->display, XkbUseCoreKbd, &state) == Success) {
            ದತ್ತಾಂಶ->keyboard.xkb.current_ಗುಂಪು = state.ಗುಂಪು;
        }

        ದತ್ತಾಂಶ->keyboard.alt_ಮುಖವಾಡ = X11_Get_Xkb_Virtual_Modifier_ಮುಖವಾಡ(_this, "Alt");
        ಆದರೆ (!ದತ್ತಾಂಶ->keyboard.alt_ಮುಖವಾಡ) {
            ದತ್ತಾಂಶ->keyboard.alt_ಮುಖವಾಡ = X11_Get_Xkb_Virtual_Modifier_ಮುಖವಾಡ(_this, "Meta");
        }
        ದತ್ತಾಂಶ->keyboard.gui_ಮುಖವಾಡ = X11_Get_Xkb_Virtual_Modifier_ಮುಖವಾಡ(_this, "Super");
        ದತ್ತಾಂಶ->keyboard.level3_ಮುಖವಾಡ = X11_Get_Xkb_Virtual_Modifier_ಮುಖವಾಡ(_this, "LevelThree");
        ದತ್ತಾಂಶ->keyboard.level5_ಮುಖವಾಡ = X11_Get_Xkb_Virtual_Modifier_ಮುಖವಾಡ(_this, "LevelFive");
        ದತ್ತಾಂಶ->keyboard.numlock_ಮುಖವಾಡ = X11_Get_Xkb_Virtual_Modifier_ಮುಖವಾಡ(_this, "NumLock");
        ದತ್ತಾಂಶ->keyboard.scrolllock_ಮುಖವಾಡ = X11_Get_Xkb_Virtual_Modifier_ಮುಖವಾಡ(_this, "ScrollLock");

        ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i = 0; i < Xkb_ಅಂಕೆ_Kbd_Groups; ++i) {
            ದತ್ತಾಂಶ->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            ಆದರೆ (!ದತ್ತಾಂಶ->keyboard.xkb.keymaps[i]) {
                ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(ದತ್ತಾಂಶ->keyboard.xkb.keymaps[i]);
                    ದತ್ತಾಂಶ->keyboard.xkb.keymaps[j] = ಖಾಲಿ;
                }

                ಹಿಂತಿರುಗಿ;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        ಸ್ಥಿರಾಂಕ Uint32 valid_mod_ಮುಖವಾಡ = ಸರಿಸು_ಮುಖವಾಡ_2 | ಬೀಗ_ಮುಖವಾಡ | ದತ್ತಾಂಶ->keyboard.alt_ಮುಖವಾಡ | ದತ್ತಾಂಶ->keyboard.level3_ಮುಖವಾಡ | ದತ್ತಾಂಶ->keyboard.level5_ಮುಖವಾಡ;

        ಗಾಗಿ (Uint32 xkeycode = ದತ್ತಾಂಶ->keyboard.xkb.desc_ptr->min_ಕೀಲಿ_ಸಂಕೇತ; xkeycode < ದತ್ತಾಂಶ->keyboard.xkb.desc_ptr->max_ಕೀಲಿ_ಸಂಕೇತ; ++xkeycode) {
            ಸ್ಥಿರಾಂಕ SDL_Scancode scancode = ದತ್ತಾಂಶ->keyboard.ಕೀಲಿ_layout[xkeycode];
            ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN) {
                ಮುಂದುವರಿ;
            }

            ಗಾಗಿ (Uint32 ಗುಂಪು = 0; ಗುಂಪು < Xkb_ಅಂಕೆ_Kbd_Groups; ++ಗುಂಪು) {
                SDL_Keymap *keymap = ದತ್ತಾಂಶ->keyboard.xkb.keymaps[ಗುಂಪು];

                Uint32 effective_ಗುಂಪು = ಗುಂಪು;
                ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ max_ಕೀಲಿ_ಗುಂಪು = Xkb_ಕೀಲಿ_ಅಂಕೆ_Groups(ದತ್ತಾಂಶ->keyboard.xkb.desc_ptr, xkeycode);
                ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಕೀಲಿ_ಗುಂಪು_info = Xkb_ಕೀಲಿ_ಗುಂಪು_Info(ದತ್ತಾಂಶ->keyboard.xkb.desc_ptr, xkeycode);

                ಆದರೆ (max_ಕೀಲಿ_ಗುಂಪು && effective_ಗುಂಪು >= max_ಕೀಲಿ_ಗುಂಪು) {
                    ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ action = Xkb_ಹೊರಹೋಗು_ದ_Range_ಗುಂಪು_Action(ಕೀಲಿ_ಗುಂಪು_info);

                    ಆಯ್ಕೆ (action) {
                    ಪೂರ್ವನಿಯೋಜಿತ:
                        effective_ಗುಂಪು %= max_ಕೀಲಿ_ಗುಂಪು;
                        ನಿಲ್ಲಿಸು;
                    ಸ್ಥಿತಿ XkbClampIntoRange:
                        effective_ಗುಂಪು = max_ಕೀಲಿ_ಗುಂಪು - 1;
                        ನಿಲ್ಲಿಸು;
                    ಸ್ಥಿತಿ XkbRedirectIntoRange:
                        effective_ಗುಂಪು = Xkb_ಹೊರಹೋಗು_ದ_Range_ಗುಂಪು_ಸಂಖ್ಯೆ(ಕೀಲಿ_ಗುಂಪು_info);
                        ಆದರೆ (effective_ಗುಂಪು >= max_ಕೀಲಿ_ಗುಂಪು) {
                            effective_ಗುಂಪು = 0;
                        }
                        ನಿಲ್ಲಿಸು;
                    }
                }

                Xkb_ಕೀಲಿ_Type_Ptr ಕೀಲಿ_type = Xkb_ಕೀಲಿ_ಕೀಲಿ_Type(ದತ್ತಾಂಶ->keyboard.xkb.desc_ptr, xkeycode, effective_ಗುಂಪು);

                ಗಾಗಿ (Uint32 level = 0; level < ಕೀಲಿ_type->ಅಂಕೆ_ಮಟ್ಟಗಳು; ++level) {
                    ಸ್ಥಿರಾಂಕ ಕೀಲಿ_Sym keysym = X11_ಕೀಲಿ_ಸಂಕೇತ_ಗಮ್ಯ_Sym(_this, xkeycode, effective_ಗುಂಪು, level);

                    ಆದರೆ (keysym != No_ಚಿಹ್ನೆ) {
                        bool ಕೀಲಿ_added = false;

                        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ map_idx = 0; map_idx < ಕೀಲಿ_type->map_ಎಣಿಕೆ; ++map_idx) {
                            ಆದರೆ (ಕೀಲಿ_type->map[map_idx].ಸಕ್ರಿಯ && ಕೀಲಿ_type->map[map_idx].level == level) {
                                ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ xkb_mod_ಮುಖವಾಡ = ಕೀಲಿ_type->map[map_idx].mods.ಮುಖವಾಡ;
                                ಆದರೆ ((xkb_mod_ಮುಖವಾಡ | valid_mod_ಮುಖವಾಡ) == valid_mod_ಮುಖವಾಡ) {
                                    ಸ್ಥಿರಾಂಕ SDL_Keymod sdl_mod_ಮುಖವಾಡ = (xkb_mod_ಮುಖವಾಡ & ಸರಿಸು_ಮುಖವಾಡ_2 ? SDL_KMOD_ಸರಿಸು : 0) |
                                                                    (xkb_mod_ಮುಖವಾಡ & ಬೀಗ_ಮುಖವಾಡ ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_ಮುಖವಾಡ & ದತ್ತಾಂಶ->keyboard.alt_ಮುಖವಾಡ ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_ಮುಖವಾಡ & ದತ್ತಾಂಶ->keyboard.level3_ಮುಖವಾಡ ? SDL_KMOD_ಬಹುಲಕ : 0) |
                                                                    (xkb_mod_ಮುಖವಾಡ & ದತ್ತಾಂಶ->keyboard.level5_ಮುಖವಾಡ ? SDL_KMOD_LEVEL5 : 0);

                                    X11_ಕೂಡಿಸು_Keymap_ನಮೂದು(keymap, xkeycode, keysym, scancode, sdl_mod_ಮುಖವಾಡ);
                                    ಕೀಲಿ_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        ಆದರೆ (!level && !ಕೀಲಿ_added) {
                            X11_ಕೂಡಿಸು_Keymap_ನಮೂದು(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_ಗಣ_Keymap(ದತ್ತಾಂಶ->keyboard.xkb.keymaps[ದತ್ತಾಂಶ->keyboard.xkb.current_ಗುಂಪು], send_event);
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        ಆದರೆ (!keymap) {
            ಹಿಂತಿರುಗಿ;
        }

        ಆದರೆ (send_event) {
            ಆದರೆ (ದತ್ತಾಂಶ->keyboard.core.keysym_map) {
                X11_XFree(ದತ್ತಾಂಶ->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(ದತ್ತಾಂಶ->display, &ದತ್ತಾಂಶ->keyboard.core.min_keycode, &ದತ್ತಾಂಶ->keyboard.core.max_keycode);
            ದತ್ತಾಂಶ->keyboard.core.keysym_map = X11_XGetKeyboardMapping(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->keyboard.core.min_keycode,
                                                                     ದತ್ತಾಂಶ->keyboard.core.max_keycode - ದತ್ತಾಂಶ->keyboard.core.min_keycode,
                                                                     &ದತ್ತಾಂಶ->keyboard.core.keysyms_ಪ್ರತಿ_ಕೀಲಿ);
        }

        ಗಾಗಿ (Uint32 xkeycode = ದತ್ತಾಂಶ->keyboard.core.min_keycode; xkeycode <= ದತ್ತಾಂಶ->keyboard.core.max_keycode; ++xkeycode) {
            ಸ್ಥಿರಾಂಕ SDL_Scancode scancode = ದತ್ತಾಂಶ->keyboard.ಕೀಲಿ_layout[xkeycode];
            ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN) {
                ಮುಂದುವರಿ;
            }

            ಸ್ಥಿರಾಂಕ ಕೀಲಿ_Sym keysym = X11_ಕೀಲಿ_ಸಂಕೇತ_ಗಮ್ಯ_Sym(_this, xkeycode, 0, 0);
            ಆದರೆ (keysym != No_ಚಿಹ್ನೆ) {
                X11_ಕೂಡಿಸು_Keymap_ನಮೂದು(keymap, xkeycode, keysym, scancode, 0);
            }
        }

        ದತ್ತಾಂಶ->keyboard.alt_ಮುಖವಾಡ = Mod1_ಮುಖವಾಡ; // Alt or Meta
        ದತ್ತಾಂಶ->keyboard.gui_ಮುಖವಾಡ = Mod4_ಮುಖವಾಡ; // Super
        ದತ್ತಾಂಶ->keyboard.level3_ಮುಖವಾಡ = Mod5_ಮುಖವಾಡ; // Note: Not a typo, Mod5 = level 3 shift, and Mod3 = level 5 shift.
        ದತ್ತಾಂಶ->keyboard.level5_ಮುಖವಾಡ = Mod3_ಮುಖವಾಡ;
        ದತ್ತಾಂಶ->keyboard.numlock_ಮುಖವಾಡ = X11_Get_XModifier_ಮುಖವಾಡ(_this, SDL_SCANCODE_NUMLOCKCLEAR);
        ದತ್ತಾಂಶ->keyboard.scrolllock_ಮುಖವಾಡ = X11_Get_XModifier_ಮುಖವಾಡ(_this, SDL_SCANCODE_SCROLLLOCK);

        SDL_ಗಣ_Keymap(keymap, send_event);
    }
}

ಶೂನ್ಯ X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    ಆದರೆ (ದತ್ತಾಂಶ->im) {
        X11_XCloseIM(ದತ್ತಾಂಶ->im);
        ದತ್ತಾಂಶ->im = ಖಾಲಿ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_XUnregisterIMInstantiateCallback(ದತ್ತಾಂಶ->display, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, im_instantiate_handler, (XPointer)ದತ್ತಾಂಶ);
    }
#ಆದರೆ_ಅಂತ್ಯ // X_HAVE_UTF8_STRING

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    ಆದರೆ (ದತ್ತಾಂಶ->keyboard.xkb_enabled) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < Xkb_ಅಂಕೆ_Kbd_Groups; ++i) {
            SDL_DestroyKeymap(ದತ್ತಾಂಶ->keyboard.xkb.keymaps[i]);
            ದತ್ತಾಂಶ->keyboard.xkb.keymaps[i] = ಖಾಲಿ;
        }

        ಆದರೆ (ದತ್ತಾಂಶ->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(ದತ್ತಾಂಶ->keyboard.xkb.desc_ptr, 0, True);
            ದತ್ತಾಂಶ->keyboard.xkb.desc_ptr = ಖಾಲಿ;
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (ದತ್ತಾಂಶ->keyboard.core.keysym_map) {
        X11_XFree(ದತ್ತಾಂಶ->keyboard.core.keysym_map);
        ದತ್ತಾಂಶ->keyboard.core.keysym_map = ಖಾಲಿ;
    }
}

ಶೂನ್ಯ X11_ClearComposition(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    ಆದರೆ (ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ > 0) {
        ದತ್ತಾಂಶ->preedit_ಪಠ್ಯ[0] = '\0';
        ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ = 0;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->ime_needs_clear_composition) {
        SDL_Send_Editing_ಪಠ್ಯ("", 0, 0);
        ದತ್ತಾಂಶ->ime_needs_clear_composition = false;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_SendEditingEvent(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    ಆದರೆ (ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ == 0) {
        X11_ClearComposition(ದತ್ತಾಂಶ);
        ಹಿಂತಿರುಗಿ;
    }

    bool ಒಳ_highlight = false;
    ಪೂರ್ಣಾಂಕ ಆರಂಭ = -1, ಉದ್ದಳತೆ = 0, i;
    ಗಾಗಿ (i = 0; i < ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ; ++i) {
        ಆದರೆ (ದತ್ತಾಂಶ->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            ಆದರೆ (ಆರಂಭ < 0) {
                ಆರಂಭ = i;
                ಒಳ_highlight = true;
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಒಳ_highlight) {
            // Found the end of the highlight
            ನಿಲ್ಲಿಸು;
        }
    }
    ಆದರೆ (ಒಳ_highlight) {
        ಉದ್ದಳತೆ = (i - ಆರಂಭ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆರಂಭ = SDL_clamp(ದತ್ತಾಂಶ->preedit_cursor, 0, ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ);
    }
    SDL_Send_Editing_ಪಠ್ಯ(ದತ್ತಾಂಶ->preedit_ಪಠ್ಯ, ಆರಂಭ, ಉದ್ದಳತೆ);

    ದತ್ತಾಂಶ->ime_needs_clear_composition = true;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ preedit_ಆರಂಭ_callback(XIC xic, XPointer client_ದತ್ತಾಂಶ_2, XPointer call_ದತ್ತಾಂಶ_2)
{
    // No limit on preedit text length
    ಹಿಂತಿರುಗಿ -1;
}

ಸ್ಥಿರ ಶೂನ್ಯ preedit_ಮುಗಿದ_callback(XIC xic, XPointer client_ದತ್ತಾಂಶ_2, XPointer call_ದತ್ತಾಂಶ_2)
{
}

ಸ್ಥಿರ ಶೂನ್ಯ preedit_draw_callback(XIC xic, XPointer client_ದತ್ತಾಂಶ_2, XIMPreeditDrawCallbackStruct *call_ದತ್ತಾಂಶ_2)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)client_ದತ್ತಾಂಶ_2;
    ಪೂರ್ಣಾಂಕ chg_ಮೊದಲ = SDL_clamp(call_ದತ್ತಾಂಶ_2->chg_ಮೊದಲ, 0, ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ);
    ಪೂರ್ಣಾಂಕ chg_ಉದ್ದಳತೆ = SDL_clamp(call_ದತ್ತಾಂಶ_2->chg_ಉದ್ದಳತೆ, 0, ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ - chg_ಮೊದಲ);

    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಆರಂಭ = ದತ್ತಾಂಶ->preedit_ಪಠ್ಯ;
    ಆದರೆ (chg_ಉದ್ದಳತೆ > 0) {
        // Delete text in range
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; ಆರಂಭ && *ಆರಂಭ && i < chg_ಮೊದಲ; ++i) {
            SDL_ಹೆಜ್ಜೆ_UTF8(&ಆರಂಭ, ಖಾಲಿ);
        }

        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೊನೆ = ಆರಂಭ;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; ಕೊನೆ && *ಕೊನೆ && i < chg_ಉದ್ದಳತೆ; ++i) {
            SDL_ಹೆಜ್ಜೆ_UTF8(&ಕೊನೆ, ಖಾಲಿ);
        }

        ಆದರೆ (ಕೊನೆ > ಆರಂಭ) {
            SDL_memmove((ಅಕ್ಷರ *)ಆರಂಭ, ಕೊನೆ, SDL_strlen(ಕೊನೆ) + 1);
            ಆದರೆ ((chg_ಮೊದಲ + chg_ಉದ್ದಳತೆ) > ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ) {
                SDL_memmove(&ದತ್ತಾಂಶ->preedit_feedback[chg_ಮೊದಲ], &ದತ್ತಾಂಶ->preedit_feedback[chg_ಮೊದಲ + chg_ಉದ್ದಳತೆ], (ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ - chg_ಮೊದಲ - chg_ಉದ್ದಳತೆ) * ಗಾತ್ರ(*ದತ್ತಾಂಶ->preedit_feedback));
            }
        }
        ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ -= chg_ಉದ್ದಳತೆ;
    }

    XIMText *ಪಠ್ಯ = call_ದತ್ತಾಂಶ_2->ಪಠ್ಯ;
    ಆದರೆ (ಪಠ್ಯ) {
        // Insert text in range
        SDL_assert(!ಪಠ್ಯ->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        ಆದರೆ (ಪಠ್ಯ->string.multi_byte) {
            ಪಠ್ಯ->ಉದ್ದಳತೆ = SDL_utf8strlen(ಪಠ್ಯ->string.multi_byte);
        }

        size_t string_ಗಾತ್ರ = SDL_strlen(ಪಠ್ಯ->string.multi_byte);
        size_t ಗಾತ್ರ_2 = string_ಗಾತ್ರ + 1;
        ಆದರೆ (ದತ್ತಾಂಶ->preedit_ಪಠ್ಯ) {
            ಗಾತ್ರ_2 += SDL_strlen(ದತ್ತಾಂಶ->preedit_ಪಠ್ಯ);
        }
        ಅಕ್ಷರ *preedit_ಪಠ್ಯ = (ಅಕ್ಷರ *)SDL_malloc(ಗಾತ್ರ_2 * ಗಾತ್ರ(*preedit_ಪಠ್ಯ));
        ಆದರೆ (preedit_ಪಠ್ಯ) {
            size_t pre_ಗಾತ್ರ = (ಆರಂಭ - ದತ್ತಾಂಶ->preedit_ಪಠ್ಯ);
            size_t post_ಗಾತ್ರ = ಆರಂಭ ? SDL_strlen(ಆರಂಭ) : 0;
            ಆದರೆ (pre_ಗಾತ್ರ > 0) {
                SDL_memcpy(&preedit_ಪಠ್ಯ[0], ದತ್ತಾಂಶ->preedit_ಪಠ್ಯ, pre_ಗಾತ್ರ);
            }
            SDL_memcpy(&preedit_ಪಠ್ಯ[pre_ಗಾತ್ರ], ಪಠ್ಯ->string.multi_byte, string_ಗಾತ್ರ);
            ಆದರೆ (post_ಗಾತ್ರ > 0) {
                SDL_memcpy(&preedit_ಪಠ್ಯ[pre_ಗಾತ್ರ + string_ಗಾತ್ರ], ಆರಂಭ, post_ಗಾತ್ರ);
            }
            preedit_ಪಠ್ಯ[ಗಾತ್ರ_2 - 1] = '\0';
        }

        size_t feedback_ಗಾತ್ರ = ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ + ಪಠ್ಯ->ಉದ್ದಳತೆ;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_ಗಾತ್ರ * ಗಾತ್ರ(*feedback));
        ಆದರೆ (feedback) {
            size_t pre_ಗಾತ್ರ = (size_t)chg_ಮೊದಲ;
            size_t post_ಗಾತ್ರ = (size_t)ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ - pre_ಗಾತ್ರ;
            ಆದರೆ (pre_ಗಾತ್ರ > 0) {
                SDL_memcpy(&feedback[0], ದತ್ತಾಂಶ->preedit_feedback, pre_ಗಾತ್ರ * ಗಾತ್ರ(*feedback));
            }
            SDL_memcpy(&feedback[pre_ಗಾತ್ರ], ಪಠ್ಯ->feedback, ಪಠ್ಯ->ಉದ್ದಳತೆ * ಗಾತ್ರ(*feedback));
            ಆದರೆ (post_ಗಾತ್ರ > 0) {
                SDL_memcpy(&feedback[pre_ಗಾತ್ರ + ಪಠ್ಯ->ಉದ್ದಳತೆ], &ದತ್ತಾಂಶ->preedit_feedback[pre_ಗಾತ್ರ], post_ಗಾತ್ರ * ಗಾತ್ರ(*feedback));
            }
        }

        ಆದರೆ (preedit_ಪಠ್ಯ && feedback) {
            SDL_free(ದತ್ತಾಂಶ->preedit_ಪಠ್ಯ);
            ದತ್ತಾಂಶ->preedit_ಪಠ್ಯ = preedit_ಪಠ್ಯ;

            SDL_free(ದತ್ತಾಂಶ->preedit_feedback);
            ದತ್ತಾಂಶ->preedit_feedback = feedback;

            ದತ್ತಾಂಶ->preedit_ಉದ್ದಳತೆ += ಪಠ್ಯ->ಉದ್ದಳತೆ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_free(preedit_ಪಠ್ಯ);
            SDL_free(feedback);
        }
    }

    ದತ್ತಾಂಶ->preedit_cursor = call_ದತ್ತಾಂಶ_2->caret;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_XIM
    ಆದರೆ (call_ದತ್ತಾಂಶ_2->chg_ಉದ್ದಳತೆ > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_ದತ್ತಾಂಶ_2->chg_ಉದ್ದಳತೆ, call_ದತ್ತಾಂಶ_2->chg_ಮೊದಲ);
    }
    ಆದರೆ (ಪಠ್ಯ) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", ಪಠ್ಯ->string.multi_byte, call_ದತ್ತಾಂಶ_2->chg_ಮೊದಲ, call_ದತ್ತಾಂಶ_2->caret);
    }
    SDL_Log("Pre-edit text: %s", ದತ್ತಾಂಶ->preedit_ಪಠ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ

    X11_SendEditingEvent(ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ ಶೂನ್ಯ preedit_caret_callback(XIC xic, XPointer client_ದತ್ತಾಂಶ_2, XIMPreeditCaretCallbackStruct *call_ದತ್ತಾಂಶ_2)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)client_ದತ್ತಾಂಶ_2;

    ಆಯ್ಕೆ (call_ದತ್ತಾಂಶ_2->direction) {
    ಸ್ಥಿತಿ XIMAbsolutePosition:
        ಆದರೆ (call_ದತ್ತಾಂಶ_2->position != ದತ್ತಾಂಶ->preedit_cursor) {
            ದತ್ತಾಂಶ->preedit_cursor = call_ದತ್ತಾಂಶ_2->position;
            X11_SendEditingEvent(ದತ್ತಾಂಶ);
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ XIMDontChange:
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        // Not currently supported
        ನಿಲ್ಲಿಸು;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ic_destroyed_handler(XIC ic, XPointer client_ದತ್ತಾಂಶ, XPointer call_ದತ್ತಾಂಶ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)client_ದತ್ತಾಂಶ;
    ದತ್ತಾಂಶ->ic = ಖಾಲಿ;
    X11_Destroy_ಒಳಹರಿವು_Context(ದತ್ತಾಂಶ);

    // If the IM was already recreated, create a new IC.
    ಆದರೆ (ದತ್ತಾಂಶ->videodata->im) {
        X11_Create_ಒಳಹರಿವು_Context(ದತ್ತಾಂಶ);
    }
}
#ಆದರೆ_ಅಂತ್ಯ // X_HAVE_UTF8_STRING

ಶೂನ್ಯ X11_Create_ಒಳಹರಿವು_Context(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    SDL_Video_ದತ್ತಾಂಶ *videodata = ದತ್ತಾಂಶ->videodata;

    ಆದರೆ (SDL_X11_HAVE_UTF8 && videodata->im) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_ದತ್ತಾಂಶ_2 = (XPointer)ದತ್ತಾಂಶ;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        ಆದರೆ (hint && SDL_strstr(hint, "composition")) {
            XIMCallback draw_callback;
            draw_callback.client_ದತ್ತಾಂಶ_2 = (XPointer)ದತ್ತಾಂಶ;
            draw_callback.callback = (XIMProc)preedit_draw_callback;

            XIMCallback ಆರಂಭ_callback;
            ಆರಂಭ_callback.client_ದತ್ತಾಂಶ_2 = (XPointer)ದತ್ತಾಂಶ;
            ಆರಂಭ_callback.callback = (XIMProc)preedit_ಆರಂಭ_callback;

            XIMCallback ಮುಗಿದ_callback;
            ಮುಗಿದ_callback.client_ದತ್ತಾಂಶ_2 = (XPointer)ದತ್ತಾಂಶ;
            ಮುಗಿದ_callback.callback = (XIMProc)preedit_ಮುಗಿದ_callback;

            XIMCallback caret_callback;
            caret_callback.client_ದತ್ತಾಂಶ_2 = (XPointer)ದತ್ತಾಂಶ;
            caret_callback.callback = (XIMProc)preedit_caret_callback;

            XVaNestedList attr = X11_XVaCreateNestedList(0,
                                                         XNPreedit_ಆರಂಭ_Callback, &ಆರಂಭ_callback,
                                                         XNPreedit_ಮುಗಿದ_Callback, &ಮುಗಿದ_callback,
                                                         XNPreeditDrawCallback, &draw_callback,
                                                         XNPreeditCaretCallback, &caret_callback,
                                                         ಖಾಲಿ);
            ಆದರೆ (attr) {
                ದತ್ತಾಂಶ->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreedit_ಗುಣಲಕ್ಷಣಗಳು, attr,
                                         XNClient_ಕಿಟಕಿ, ದತ್ತಾಂಶ->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         ಖಾಲಿ);
                X11_XFree(attr);
            }
        }
        ಆದರೆ (!ದತ್ತಾಂಶ->ic) {
            ದತ್ತಾಂಶ->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClient_ಕಿಟಕಿ, ದತ್ತಾಂಶ->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     ಖಾಲಿ);
        }
        ದತ್ತಾಂಶ->xim_spot.x = -1;
        ದತ್ತಾಂಶ->xim_spot.y = -1;
    }
#ಆದರೆ_ಅಂತ್ಯ // X_HAVE_UTF8_STRING
}


ಶೂನ್ಯ X11_Destroy_ಒಳಹರಿವು_Context(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    ಆದರೆ (ದತ್ತಾಂಶ->ic) {
        X11_XDestroyIC(ದತ್ತಾಂಶ->ic);
        ದತ್ತಾಂಶ->ic = ಖಾಲಿ;
    }
    SDL_free(ದತ್ತಾಂಶ->preedit_ಪಠ್ಯ);
    SDL_free(ದತ್ತಾಂಶ->preedit_feedback);
    ದತ್ತಾಂಶ->preedit_ಪಠ್ಯ = ಖಾಲಿ;
    ದತ್ತಾಂಶ->preedit_feedback = ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_ResetXIM(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ && ದತ್ತಾಂಶ->ic) {
        // Clear any partially entered dead keys
        ಅಕ್ಷರ *contents = X11_Xutf8ResetIC(ದತ್ತಾಂಶ->ic);
        ಆದರೆ (contents) {
            X11_XFree(contents);
        }
    }
#ಆದರೆ_ಅಂತ್ಯ // X_HAVE_UTF8_STRING
}

bool X11_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, ಕಿಟಕಿ);

    ಹಿಂತಿರುಗಿ X11_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area(_this, ಕಿಟಕಿ);
}

bool X11_Stop_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    X11_ResetXIM(_this, ಕಿಟಕಿ);
    ಹಿಂತಿರುಗಿ true;
}

bool X11_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ && ದತ್ತಾಂಶ->ic) {
        XPoint spot;
        spot.x = ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.x + ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_cursor;
        spot.y = ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.y + ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.h;
        ಆದರೆ (spot.x != ದತ್ತಾಂಶ->xim_spot.x || spot.y != ದತ್ತಾಂಶ->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, ಖಾಲಿ);
            ಆದರೆ (attr) {
                X11_XSetICValues(ದತ್ತಾಂಶ->ic, XNPreedit_ಗುಣಲಕ್ಷಣಗಳು, attr, ಖಾಲಿ);
                X11_XFree(attr);
            }
            SDL_copyp(&ದತ್ತಾಂಶ->xim_spot, &spot);
        }
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    ಹಿಂತಿರುಗಿ videodata->use_steam_screen_keyboard;
}

ಶೂನ್ಯ X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;

    ಆದರೆ (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ k_EFloating_Gamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_ಬಹುಲಕ_Single_ಸಾಲು = 0;    // Enter dismisses the keyboard
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ k_EFloating_Gamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_ಬಹುಲಕ_ಅಪವರ್ತ್ಯ_ಸಾಲುಗಳು = 1; // User needs to explicitly dismiss the keyboard
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ k_EFloating_Gamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_ಬಹುಲಕ_Email = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ k_EFloating_Gamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_ಬಹುಲಕ_Numeric = 3;       // Numeric keypad is shown
        ಅಕ್ಷರ deeplink[128];
        ಪೂರ್ಣಾಂಕ ಬಹುಲಕ;

        ಆಯ್ಕೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Type(props)) {
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_EMAIL:
            ಬಹುಲಕ = k_EFloating_Gamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_ಬಹುಲಕ_Email;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ:
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_HIDDEN:
        ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_VISIBLE:
            ಬಹುಲಕ = k_EFloating_Gamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_ಬಹುಲಕ_Numeric;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಆದರೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Multiline(props)) {
                ಬಹುಲಕ = k_EFloating_Gamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_ಬಹುಲಕ_ಅಪವರ್ತ್ಯ_ಸಾಲುಗಳು;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಬಹುಲಕ = k_EFloating_Gamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_ಬಹುಲಕ_Single_ಸಾಲು;
            }
            ನಿಲ್ಲಿಸು;
        }
        (ಶೂನ್ಯ)SDL_snprintf(deeplink, ಗಾತ್ರ(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.x, ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.y,
                           ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.w, ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect.h,
                           ಬಹುಲಕ);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

ಶೂನ್ಯ X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;

    ಆದರೆ (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
