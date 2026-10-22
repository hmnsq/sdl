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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#include "SDL_x11video.h"

#include "../../events/SDL_keyboard_c.h"
#include "../../events/SDL_scancode_tables_c.h"

#include <X11/keysym.h>

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
#include <X11/XKBlib.h>
#endif

#include "../../events/imKStoUCS.h"
#include "../../events/SDL_keysym_to_scancode_c.h"
#include "../../events/SDL_keysym_to_keycode_c.h"

#ifdef X_HAVE_UTF8_STRING
#include <locale.h>
#endif

static SDL_ScancodeTable scancode_set[] = {
    SDL_SCANCODE_TABLE_DARWIN,
    SDL_SCANCODE_TABLE_XFREE86_1,
    SDL_SCANCODE_TABLE_XFREE86_2,
    SDL_SCANCODE_TABLE_XVNC,
};

static bool X11_ScancodeIsRemappable(SDL_Scancode scancode)
{
    /*
     * XKB remappings can assign different keysyms for these scancodes, but
     * as these keys are in fixed positions, the scancodes themselves shouldn't
     * be switched. Mark them as not being remappable.
     */
    switch (scancode) {
    case SDL_SCANCODE_ESCAPE:
    case SDL_SCANCODE_CAPSLOCK:
    case SDL_SCANCODE_NUMLOCKCLEAR:
    case SDL_SCANCODE_LSHIFT:
    case SDL_SCANCODE_RSHIFT:
    case SDL_SCANCODE_LCTRL:
    case SDL_SCANCODE_RCTRL:
    case SDL_SCANCODE_LALT:
    case SDL_SCANCODE_RALT:
    case SDL_SCANCODE_LGUI:
    case SDL_SCANCODE_RGUI:
        trả_về false;
    default:
        trả_về true;
    }
}

static KeySym X11_KeyCodeToSym(SDL_VideoDevice *_this, KeyCode keycode, unsigned số_nguyên group, unsigned số_nguyên level)
{
    SDL_VideoData *data = _this->internal;
    KeySym keysym;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    nếu (data->keyboard.xkb_enabled) {
        keysym = X11_XkbKeycodeToKeysym(data->display, keycode, group, level);
    } không_thì
#endif
    {
        // TODO: Handle groups on the legacy path.
        nếu (keycode >= data->keyboard.core.min_keycode && keycode <= data->keyboard.core.max_keycode) {
            keysym = data->keyboard.core.keysym_map[(keycode - data->keyboard.core.min_keycode) * data->keyboard.core.keysyms_per_key];
        } không_thì {
            keysym = NoSymbol;
        }
    }

    trả_về keysym;
}

// This function only correctly maps letters and numbers for keyboards in US QWERTY layout
static SDL_Scancode X11_KeyCodeToSDLScancode(SDL_VideoDevice *_this, KeyCode keycode)
{
    const KeySym keysym = X11_KeyCodeToSym(_this, keycode, 0, 0);

    nếu (keysym == NoSymbol) {
        trả_về SDL_SCANCODE_UNKNOWN;
    }

    trả_về SDL_GetScancodeFromKeySym(keysym, keycode);
}

#ifdef X_HAVE_UTF8_STRING
static bool X11_InitIM(SDL_VideoData *videodata);

static void im_instantiate_handler(Display *display, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    nếu (X11_InitIM(videodata)) {
        X11_XUnregisterIMInstantiateCallback(videodata->display, NULL, NULL, NULL, im_instantiate_handler, clientData);
    }
}

static void im_destroyed_handler(XIM im, XPointer clientData, XPointer callData)
{
    SDL_VideoData *videodata = (SDL_VideoData *)clientData;

    videodata->im = NULL;
    X11_XRegisterIMInstantiateCallback(videodata->display, NULL, NULL, NULL, im_instantiate_handler, clientData);
}

static bool X11_InitIM(SDL_VideoData *videodata)
{
    /* Set the locale, and call XSetLocaleModifiers before XOpenIM so that
     * Compose keys will work correctly.
     */
    char *prev_locale = setlocale(LC_ALL, NULL);
    char *prev_xmods = X11_XSetLocaleModifiers(NULL);

    nếu (prev_locale) {
        prev_locale = SDL_strdup(prev_locale);
    }

    nếu (prev_xmods) {
        prev_xmods = SDL_strdup(prev_xmods);
    }

    (void)setlocale(LC_ALL, "");
    X11_XSetLocaleModifiers("");

    XIM im = X11_XOpenIM(videodata->display, NULL, NULL, NULL);

    /* Reset the locale + X locale modifiers back to how they were,
     * locale first because the X locale modifiers depend on it.
     */
    (void)setlocale(LC_ALL, prev_locale);
    X11_XSetLocaleModifiers(prev_xmods);

    SDL_free(prev_locale);
    SDL_free(prev_xmods);

    nếu (im) {
        videodata->im = im;

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)videodata;
        destroyed_callback.callback = (XIMProc)im_destroyed_handler;

        X11_XSetIMValues(im, XNDestroyCallback, &destroyed_callback, (char *)NULL);

        /* Attach the new IC to any existing windows.
         *
         * If we wound up here before any old input contexts were destroyed,
         * they will be recreated in the IC destroyed callback.
         */
        cho (số_nguyên i = 0; i < videodata->numwindows; ++i) {
            SDL_WindowData *w = videodata->windowlist[i];
            nếu (!w->ic) {
                X11_CreateInputContext(w);
            }
        }

        trả_về true;
    }

    trả_về false;
}
#endif // X_HAVE_UTF8_STRING

bool X11_InitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    số_nguyên i = 0;
    số_nguyên j = 0;
    số_nguyên min_keycode, max_keycode;
    struct
    {
        SDL_Scancode scancode;
        KeySym keysym;
        số_nguyên value;
    } fingerprint[] = {
        { SDL_SCANCODE_HOME, XK_Home, 0 },
        { SDL_SCANCODE_PAGEUP, XK_Prior, 0 },
        { SDL_SCANCODE_UP, XK_Up, 0 },
        { SDL_SCANCODE_LEFT, XK_Left, 0 },
        { SDL_SCANCODE_DELETE, XK_Delete, 0 },
        { SDL_SCANCODE_KP_ENTER, XK_KP_Enter, 0 },
    };
    số_nguyên best_distance;
    số_nguyên best_index;
    số_nguyên distance;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    số_nguyên xkb_major = XkbMajorVersion;
    số_nguyên xkb_minor = XkbMinorVersion;

    nếu (X11_XkbQueryExtension(data->display, NULL, &data->keyboard.xkb.event, NULL, &xkb_major, &xkb_minor)) {
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
    } không_thì
#endif
    {
        // If XKB isn't available, initialize the legacy path.
        X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
        data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                              data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                              &data->keyboard.core.keysyms_per_key);
    }

    // Open a connection to the X input manager
#ifdef X_HAVE_UTF8_STRING
    nếu (SDL_X11_HAVE_UTF8) {
        nếu (!X11_InitIM(data)) {
            X11_XRegisterIMInstantiateCallback(data->display, NULL, NULL, NULL, im_instantiate_handler, (XPointer)data);
        }
    }
#endif
    // Try to determine which scancodes are being used based on fingerprint
    best_distance = SDL_arraysize(fingerprint) + 1;
    best_index = -1;
    X11_XDisplayKeycodes(data->display, &min_keycode, &max_keycode);
    cho (i = 0; i < SDL_arraysize(fingerprint); ++i) {
        fingerprint[i].value = X11_XKeysymToKeycode(data->display, fingerprint[i].keysym) - min_keycode;
    }
    cho (i = 0; i < SDL_arraysize(scancode_set); ++i) {
        số_nguyên table_size;
        const SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[i], &table_size);

        distance = 0;
        cho (j = 0; j < SDL_arraysize(fingerprint); ++j) {
            nếu (fingerprint[j].value < 0 || fingerprint[j].value >= table_size) {
                distance += 1;
            } không_thì nếu (table[fingerprint[j].value] != fingerprint[j].scancode) {
                distance += 1;
            }
        }
        nếu (distance < best_distance) {
            best_distance = distance;
            best_index = i;
        }
    }
    nếu (best_index < 0 || best_distance > 2) {
        // This is likely to be SDL_SCANCODE_TABLE_XFREE86_2 with remapped keys, double check a rarely remapped value
        số_nguyên fingerprint_value = X11_XKeysymToKeycode(data->display, 0x1008FF5B /* XF86Documents */) - min_keycode;
        nếu (fingerprint_value == 235) {
            cho (i = 0; i < SDL_arraysize(scancode_set); ++i) {
                nếu (scancode_set[i] == SDL_SCANCODE_TABLE_XFREE86_2) {
                    best_index = i;
                    best_distance = 0;
                    break;
                }
            }
        }
    }
    nếu (best_index >= 0 && best_distance <= 2) {
        số_nguyên table_size;
        const SDL_Scancode *table = SDL_GetScancodeTable(scancode_set[best_index], &table_size);

#ifdef DEBUG_KEYBOARD
        SDL_Log("Using scancode set %d, min_keycode = %d, max_keycode = %d, table_size = %d", best_index, min_keycode, max_keycode, table_size);
#endif
        // This should never happen, but just in case...
        nếu (table_size > (SDL_arraysize(data->keyboard.key_layout) - min_keycode)) {
            table_size = (SDL_arraysize(data->keyboard.key_layout) - min_keycode);
        }
        SDL_memcpy(&data->keyboard.key_layout[min_keycode], table, sizeof(SDL_Scancode) * table_size);

        /* Scancodes represent physical locations on the keyboard, unaffected by keyboard mapping.
           However, there are a number of extended scancodes that have no standard location, so use
           the X11 mapping for all non-character keys.
         */
        cho (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_KeyCodeToSDLScancode(_this, i);
#ifdef DEBUG_KEYBOARD
            {
                KeySym sym;
                sym = X11_KeyCodeToSym(_this, (KeyCode)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned số_nguyên)sym, sym == NoSymbol ? "NoSymbol" : X11_XKeysymToString(sym));
            }
#endif
            nếu (scancode == data->keyboard.key_layout[i]) {
                continue;
            }
            nếu ((SDL_GetKeymapKeycode(NULL, scancode, SDL_KMOD_NONE) & (SDLK_SCANCODE_MASK | SDLK_EXTENDED_MASK)) && X11_ScancodeIsRemappable(scancode)) {
                // Not a character key and the scancode is safe to remap
#ifdef DEBUG_KEYBOARD
                SDL_Log("Changing scancode, was %d (%s), now %d (%s)", data->key_layout[i], SDL_GetScancodeName(data->key_layout[i]), scancode, SDL_GetScancodeName(scancode));
#endif
                data->keyboard.key_layout[i] = scancode;
            }
        }
    } không_thì {
#ifdef DEBUG_SCANCODES
        SDL_Log("Keyboard layout unknown, please report the following to the SDL forums/mailing list (https://discourse.libsdl.org/):");
#endif

        // Determine key_layout - only works on US QWERTY layout
        cho (i = min_keycode; i <= max_keycode; ++i) {
            SDL_Scancode scancode = X11_KeyCodeToSDLScancode(_this, i);
#ifdef DEBUG_SCANCODES
            {
                KeySym sym;
                sym = X11_KeyCodeToSym(_this, (KeyCode)i, 0);
                SDL_Log("code = %d, sym = 0x%X (%s) ", i - min_keycode,
                        (unsigned số_nguyên)sym, sym == NoSymbol ? "NoSymbol" : X11_XKeysymToString(sym));
            }
            nếu (scancode == SDL_SCANCODE_UNKNOWN) {
                SDL_Log("scancode not found");
            } không_thì {
                SDL_Log("scancode = %d (%s)", scancode, SDL_GetScancodeName(scancode));
            }
#endif
            data->keyboard.key_layout[i] = scancode;
        }
    }

    X11_UpdateKeymap(_this, false);

    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");

    X11_ReconcileKeyboardState(_this);

    trả_về true;
}

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
static unsigned số_nguyên X11_GetXkbVirtualModifierMask(SDL_VideoDevice *_this, const char *vmod_name)
{
    SDL_VideoData *videodata = _this->internal;
    unsigned số_nguyên mod_mask = 0;

    const Atom vmod = X11_XInternAtom(videodata->display, vmod_name, True);
    nếu (vmod != None) {
        cho (số_nguyên i = 0; i < XkbNumVirtualMods; ++i) {
            nếu (vmod == videodata->keyboard.xkb.desc_ptr->names->vmods[i]) {
                mod_mask = videodata->keyboard.xkb.desc_ptr->server->vmods[i];
                break;
            }
        }
    }

    trả_về mod_mask;
}
#endif

static unsigned X11_GetXModifierMask(SDL_VideoDevice *_this, SDL_Scancode scancode)
{
    SDL_VideoData *videodata = _this->internal;
    Display *display = videodata->display;
    unsigned số_nguyên mod_mask = 0;

    XModifierKeymap *xmods = X11_XGetModifierMapping(display);
    unsigned số_nguyên n = xmods->max_keypermod;
    cho (số_nguyên i = 3; i < 8; i++) {
        cho (số_nguyên j = 0; j < n; j++) {
            const KeyCode kc = xmods->modifiermap[i * n + j];
            nếu (videodata->keyboard.key_layout[kc] == scancode) {
                mod_mask = 1 << i;
                break;
            }
        }
    }
    X11_XFreeModifiermap(xmods);

    trả_về mod_mask;
}

static void X11_AddKeymapEntry(SDL_Keymap *keymap, Uint32 xkeycode, KeySym xkeysym, SDL_Scancode sdl_scancode, SDL_Keymod sdl_mod_mask)
{
    SDL_Keycode keycode = SDL_GetKeyCodeFromKeySym(xkeysym, xkeycode, sdl_mod_mask);

    nếu (!keycode) {
        switch (sdl_scancode) {
        case SDL_SCANCODE_RETURN:
            keycode = SDLK_RETURN;
            break;
        case SDL_SCANCODE_ESCAPE:
            keycode = SDLK_ESCAPE;
            break;
        case SDL_SCANCODE_BACKSPACE:
            keycode = SDLK_BACKSPACE;
            break;
        case SDL_SCANCODE_DELETE:
            keycode = SDLK_DELETE;
            break;
        default:
            keycode = SDL_SCANCODE_TO_KEYCODE(sdl_scancode);
            break;
        }
    }

    SDL_SetKeymapEntry(keymap, sdl_scancode, sdl_mod_mask, keycode);
}

void X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    nếu (data->keyboard.xkb_enabled) {
        XkbStateRec state;

        cho (unsigned số_nguyên i = 0; i < XkbNumKbdGroups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = NULL;
        }

        X11_XkbGetNames(data->display, XkbVirtualModNamesMask, data->keyboard.xkb.desc_ptr);
        X11_XkbGetUpdatedMap(data->display, XkbAllClientInfoMask | XkbVirtualModsMask, data->keyboard.xkb.desc_ptr);

        nếu (X11_XkbGetState(data->display, XkbUseCoreKbd, &state) == Success) {
            data->keyboard.xkb.current_group = state.group;
        }

        data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Alt");
        nếu (!data->keyboard.alt_mask) {
            data->keyboard.alt_mask = X11_GetXkbVirtualModifierMask(_this, "Meta");
        }
        data->keyboard.gui_mask = X11_GetXkbVirtualModifierMask(_this, "Super");
        data->keyboard.level3_mask = X11_GetXkbVirtualModifierMask(_this, "LevelThree");
        data->keyboard.level5_mask = X11_GetXkbVirtualModifierMask(_this, "LevelFive");
        data->keyboard.numlock_mask = X11_GetXkbVirtualModifierMask(_this, "NumLock");
        data->keyboard.scrolllock_mask = X11_GetXkbVirtualModifierMask(_this, "ScrollLock");

        cho (unsigned số_nguyên i = 0; i < XkbNumKbdGroups; ++i) {
            data->keyboard.xkb.keymaps[i] = SDL_CreateKeymap(false);
            nếu (!data->keyboard.xkb.keymaps[i]) {
                cho (unsigned số_nguyên j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
                    data->keyboard.xkb.keymaps[j] = NULL;
                }

                trả_về;
            }
        }

        // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
        const Uint32 valid_mod_mask = ShiftMask | LockMask | data->keyboard.alt_mask | data->keyboard.level3_mask | data->keyboard.level5_mask;

        cho (Uint32 xkeycode = data->keyboard.xkb.desc_ptr->min_key_code; xkeycode < data->keyboard.xkb.desc_ptr->max_key_code; ++xkeycode) {
            const SDL_Scancode scancode = data->keyboard.key_layout[xkeycode];
            nếu (scancode == SDL_SCANCODE_UNKNOWN) {
                continue;
            }

            cho (Uint32 group = 0; group < XkbNumKbdGroups; ++group) {
                SDL_Keymap *keymap = data->keyboard.xkb.keymaps[group];

                Uint32 effective_group = group;
                const unsigned char max_key_group = XkbKeyNumGroups(data->keyboard.xkb.desc_ptr, xkeycode);
                const unsigned char key_group_info = XkbKeyGroupInfo(data->keyboard.xkb.desc_ptr, xkeycode);

                nếu (max_key_group && effective_group >= max_key_group) {
                    const unsigned char action = XkbOutOfRangeGroupAction(key_group_info);

                    switch (action) {
                    default:
                        effective_group %= max_key_group;
                        break;
                    case XkbClampIntoRange:
                        effective_group = max_key_group - 1;
                        break;
                    case XkbRedirectIntoRange:
                        effective_group = XkbOutOfRangeGroupNumber(key_group_info);
                        nếu (effective_group >= max_key_group) {
                            effective_group = 0;
                        }
                        break;
                    }
                }

                XkbKeyTypePtr key_type = XkbKeyKeyType(data->keyboard.xkb.desc_ptr, xkeycode, effective_group);

                cho (Uint32 level = 0; level < key_type->num_levels; ++level) {
                    const KeySym keysym = X11_KeyCodeToSym(_this, xkeycode, effective_group, level);

                    nếu (keysym != NoSymbol) {
                        bool key_added = false;

                        cho (số_nguyên map_idx = 0; map_idx < key_type->map_count; ++map_idx) {
                            nếu (key_type->map[map_idx].active && key_type->map[map_idx].level == level) {
                                const unsigned số_nguyên xkb_mod_mask = key_type->map[map_idx].mods.mask;
                                nếu ((xkb_mod_mask | valid_mod_mask) == valid_mod_mask) {
                                    const SDL_Keymod sdl_mod_mask = (xkb_mod_mask & ShiftMask ? SDL_KMOD_SHIFT : 0) |
                                                                    (xkb_mod_mask & LockMask ? SDL_KMOD_CAPS : 0) |
                                                                    (xkb_mod_mask & data->keyboard.alt_mask ? SDL_KMOD_ALT : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level3_mask ? SDL_KMOD_MODE : 0) |
                                                                    (xkb_mod_mask & data->keyboard.level5_mask ? SDL_KMOD_LEVEL5 : 0);

                                    X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, sdl_mod_mask);
                                    key_added = true;
                                }
                            }
                        }

                        // Add the unmodified key for level 0.
                        nếu (!level && !key_added) {
                            X11_AddKeymapEntry(keymap, xkeycode, keysym, scancode, 0);
                        }
                    }
                }
            }
        }

        SDL_SetKeymap(data->keyboard.xkb.keymaps[data->keyboard.xkb.current_group], send_event);
    } không_thì
#endif
    {
        SDL_Keymap *keymap = SDL_CreateKeymap(true);
        nếu (!keymap) {
            trả_về;
        }

        nếu (send_event) {
            nếu (data->keyboard.core.keysym_map) {
                X11_XFree(data->keyboard.core.keysym_map);
            }
            X11_XDisplayKeycodes(data->display, &data->keyboard.core.min_keycode, &data->keyboard.core.max_keycode);
            data->keyboard.core.keysym_map = X11_XGetKeyboardMapping(data->display, data->keyboard.core.min_keycode,
                                                                     data->keyboard.core.max_keycode - data->keyboard.core.min_keycode,
                                                                     &data->keyboard.core.keysyms_per_key);
        }

        cho (Uint32 xkeycode = data->keyboard.core.min_keycode; xkeycode <= data->keyboard.core.max_keycode; ++xkeycode) {
            const SDL_Scancode scancode = data->keyboard.key_layout[xkeycode];
            nếu (scancode == SDL_SCANCODE_UNKNOWN) {
                continue;
            }

            const KeySym keysym = X11_KeyCodeToSym(_this, xkeycode, 0, 0);
            nếu (keysym != NoSymbol) {
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

void X11_QuitKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

#ifdef X_HAVE_UTF8_STRING
    nếu (data->im) {
        X11_XCloseIM(data->im);
        data->im = NULL;
    } không_thì {
        X11_XUnregisterIMInstantiateCallback(data->display, NULL, NULL, NULL, im_instantiate_handler, (XPointer)data);
    }
#endif // X_HAVE_UTF8_STRING

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
    nếu (data->keyboard.xkb_enabled) {
        cho (số_nguyên i = 0; i < XkbNumKbdGroups; ++i) {
            SDL_DestroyKeymap(data->keyboard.xkb.keymaps[i]);
            data->keyboard.xkb.keymaps[i] = NULL;
        }

        nếu (data->keyboard.xkb_enabled) {
            X11_XkbFreeKeyboard(data->keyboard.xkb.desc_ptr, 0, True);
            data->keyboard.xkb.desc_ptr = NULL;
        }
    } không_thì
#endif
        nếu (data->keyboard.core.keysym_map) {
        X11_XFree(data->keyboard.core.keysym_map);
        data->keyboard.core.keysym_map = NULL;
    }
}

void X11_ClearComposition(SDL_WindowData *data)
{
    nếu (data->preedit_length > 0) {
        data->preedit_text[0] = '\0';
        data->preedit_length = 0;
    }

    nếu (data->ime_needs_clear_composition) {
        SDL_SendEditingText("", 0, 0);
        data->ime_needs_clear_composition = false;
    }
}

static void X11_SendEditingEvent(SDL_WindowData *data)
{
    nếu (data->preedit_length == 0) {
        X11_ClearComposition(data);
        trả_về;
    }

    bool in_highlight = false;
    số_nguyên start = -1, length = 0, i;
    cho (i = 0; i < data->preedit_length; ++i) {
        nếu (data->preedit_feedback[i] & (XIMReverse | XIMHighlight)) {
            nếu (start < 0) {
                start = i;
                in_highlight = true;
            }
        } không_thì nếu (in_highlight) {
            // Found the end of the highlight
            break;
        }
    }
    nếu (in_highlight) {
        length = (i - start);
    } không_thì {
        start = SDL_clamp(data->preedit_cursor, 0, data->preedit_length);
    }
    SDL_SendEditingText(data->preedit_text, start, length);

    data->ime_needs_clear_composition = true;
}

#ifdef X_HAVE_UTF8_STRING
static số_nguyên preedit_start_callback(XIC xic, XPointer client_data, XPointer call_data)
{
    // No limit on preedit text length
    trả_về -1;
}

static void preedit_done_callback(XIC xic, XPointer client_data, XPointer call_data)
{
}

static void preedit_draw_callback(XIC xic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;
    số_nguyên chg_first = SDL_clamp(call_data->chg_first, 0, data->preedit_length);
    số_nguyên chg_length = SDL_clamp(call_data->chg_length, 0, data->preedit_length - chg_first);

    const char *start = data->preedit_text;
    nếu (chg_length > 0) {
        // Delete text in range
        cho (số_nguyên i = 0; start && *start && i < chg_first; ++i) {
            SDL_StepUTF8(&start, NULL);
        }

        const char *end = start;
        cho (số_nguyên i = 0; end && *end && i < chg_length; ++i) {
            SDL_StepUTF8(&end, NULL);
        }

        nếu (end > start) {
            SDL_memmove((char *)start, end, SDL_strlen(end) + 1);
            nếu ((chg_first + chg_length) > data->preedit_length) {
                SDL_memmove(&data->preedit_feedback[chg_first], &data->preedit_feedback[chg_first + chg_length], (data->preedit_length - chg_first - chg_length) * sizeof(*data->preedit_feedback));
            }
        }
        data->preedit_length -= chg_length;
    }

    XIMText *text = call_data->text;
    nếu (text) {
        // Insert text in range
        SDL_assert(!text->encoding_is_wchar);

        // The text length isn't calculated as directed by the spec, recalculate it now
        nếu (text->string.multi_byte) {
            text->length = SDL_utf8strlen(text->string.multi_byte);
        }

        size_t string_size = SDL_strlen(text->string.multi_byte);
        size_t size = string_size + 1;
        nếu (data->preedit_text) {
            size += SDL_strlen(data->preedit_text);
        }
        char *preedit_text = (char *)SDL_malloc(size * sizeof(*preedit_text));
        nếu (preedit_text) {
            size_t pre_size = (start - data->preedit_text);
            size_t post_size = start ? SDL_strlen(start) : 0;
            nếu (pre_size > 0) {
                SDL_memcpy(&preedit_text[0], data->preedit_text, pre_size);
            }
            SDL_memcpy(&preedit_text[pre_size], text->string.multi_byte, string_size);
            nếu (post_size > 0) {
                SDL_memcpy(&preedit_text[pre_size + string_size], start, post_size);
            }
            preedit_text[size - 1] = '\0';
        }

        size_t feedback_size = data->preedit_length + text->length;
        XIMFeedback *feedback = (XIMFeedback *)SDL_malloc(feedback_size * sizeof(*feedback));
        nếu (feedback) {
            size_t pre_size = (size_t)chg_first;
            size_t post_size = (size_t)data->preedit_length - pre_size;
            nếu (pre_size > 0) {
                SDL_memcpy(&feedback[0], data->preedit_feedback, pre_size * sizeof(*feedback));
            }
            SDL_memcpy(&feedback[pre_size], text->feedback, text->length * sizeof(*feedback));
            nếu (post_size > 0) {
                SDL_memcpy(&feedback[pre_size + text->length], &data->preedit_feedback[pre_size], post_size * sizeof(*feedback));
            }
        }

        nếu (preedit_text && feedback) {
            SDL_free(data->preedit_text);
            data->preedit_text = preedit_text;

            SDL_free(data->preedit_feedback);
            data->preedit_feedback = feedback;

            data->preedit_length += text->length;
        } không_thì {
            SDL_free(preedit_text);
            SDL_free(feedback);
        }
    }

    data->preedit_cursor = call_data->caret;

#ifdef DEBUG_XIM
    nếu (call_data->chg_length > 0) {
        SDL_Log("Draw callback deleted %d characters at %d", call_data->chg_length, call_data->chg_first);
    }
    nếu (text) {
        SDL_Log("Draw callback inserted %s at %d, caret: %d", text->string.multi_byte, call_data->chg_first, call_data->caret);
    }
    SDL_Log("Pre-edit text: %s", data->preedit_text);
#endif

    X11_SendEditingEvent(data);
}

static void preedit_caret_callback(XIC xic, XPointer client_data, XIMPreeditCaretCallbackStruct *call_data)
{
    SDL_WindowData *data = (SDL_WindowData *)client_data;

    switch (call_data->direction) {
    case XIMAbsolutePosition:
        nếu (call_data->position != data->preedit_cursor) {
            data->preedit_cursor = call_data->position;
            X11_SendEditingEvent(data);
        }
        break;
    case XIMDontChange:
        break;
    default:
        // Not currently supported
        break;
    }
}

static void ic_destroyed_handler(XIC ic, XPointer clientData, XPointer callData)
{
    SDL_WindowData *data = (SDL_WindowData *)clientData;
    data->ic = NULL;
    X11_DestroyInputContext(data);

    // If the IM was already recreated, create a new IC.
    nếu (data->videodata->im) {
        X11_CreateInputContext(data);
    }
}
#endif // X_HAVE_UTF8_STRING

void X11_CreateInputContext(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_VideoData *videodata = data->videodata;

    nếu (SDL_X11_HAVE_UTF8 && videodata->im) {
        const char *hint = SDL_GetHint(SDL_HINT_IME_IMPLEMENTED_UI);

        XIMCallback destroyed_callback;
        destroyed_callback.client_data = (XPointer)data;
        destroyed_callback.callback = (XIMProc)ic_destroyed_handler;

        nếu (hint && SDL_strstr(hint, "composition")) {
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
                                                         NULL);
            nếu (attr) {
                data->ic = X11_XCreateIC(videodata->im,
                                         XNInputStyle, XIMPreeditCallbacks | XIMStatusCallbacks,
                                         XNPreeditAttributes, attr,
                                         XNClientWindow, data->xwindow,
                                         XNDestroyCallback, &destroyed_callback,
                                         NULL);
                X11_XFree(attr);
            }
        }
        nếu (!data->ic) {
            data->ic = X11_XCreateIC(videodata->im,
                                     XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                                     XNClientWindow, data->xwindow,
                                     XNDestroyCallback, &destroyed_callback,
                                     NULL);
        }
        data->xim_spot.x = -1;
        data->xim_spot.y = -1;
    }
#endif // X_HAVE_UTF8_STRING
}


void X11_DestroyInputContext(SDL_WindowData *data)
{
#ifdef X_HAVE_UTF8_STRING
    nếu (data->ic) {
        X11_XDestroyIC(data->ic);
        data->ic = NULL;
    }
    SDL_free(data->preedit_text);
    SDL_free(data->preedit_feedback);
    data->preedit_text = NULL;
    data->preedit_feedback = NULL;
#endif
}

static void X11_ResetXIM(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    nếu (data && data->ic) {
        // Clear any partially entered dead keys
        char *contents = X11_Xutf8ResetIC(data->ic);
        nếu (contents) {
            X11_XFree(contents);
        }
    }
#endif // X_HAVE_UTF8_STRING
}

bool X11_StartTextInput(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    X11_ResetXIM(_this, window);

    trả_về X11_UpdateTextInputArea(_this, window);
}

bool X11_StopTextInput(SDL_VideoDevice *_this, SDL_Window *window)
{
    X11_ResetXIM(_this, window);
    trả_về true;
}

bool X11_UpdateTextInputArea(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef X_HAVE_UTF8_STRING
    SDL_WindowData *data = window->internal;

    nếu (data && data->ic) {
        XPoint spot;
        spot.x = window->text_input_rect.x + window->text_input_cursor;
        spot.y = window->text_input_rect.y + window->text_input_rect.h;
        nếu (spot.x != data->xim_spot.x || spot.y != data->xim_spot.y) {
            XVaNestedList attr = X11_XVaCreateNestedList(0, XNSpotLocation, &spot, NULL);
            nếu (attr) {
                X11_XSetICValues(data->ic, XNPreeditAttributes, attr, NULL);
                X11_XFree(attr);
            }
            SDL_copyp(&data->xim_spot, &spot);
        }
    }
#endif
    trả_về true;
}

bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    trả_về videodata->use_steam_screen_keyboard;
}

void X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;

    nếu (videodata->use_steam_screen_keyboard) {
        /* For more documentation of the URL parameters, see:
         * https://partner.steamgames.com/doc/api/ISteamUtils#ShowFloatingGamepadTextInput
         */
        const số_nguyên k_EFloatingGamepadTextInputModeModeSingleLine = 0;    // Enter dismisses the keyboard
        const số_nguyên k_EFloatingGamepadTextInputModeModeMultipleLines = 1; // User needs to explicitly dismiss the keyboard
        const số_nguyên k_EFloatingGamepadTextInputModeModeEmail = 2;         // Keyboard is displayed in a special mode that makes it easier to enter emails
        const số_nguyên k_EFloatingGamepadTextInputModeModeNumeric = 3;       // Numeric keypad is shown
        char deeplink[128];
        số_nguyên mode;

        switch (SDL_GetTextInputType(props)) {
        case SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
            mode = k_EFloatingGamepadTextInputModeModeEmail;
            break;
        case SDL_TEXTINPUT_TYPE_NUMBER:
        case SDL_TEXTINPUT_TYPE_NUMBER_PASSWORD_HIDDEN:
        case SDL_TEXTINPUT_TYPE_NUMBER_PASSWORD_VISIBLE:
            mode = k_EFloatingGamepadTextInputModeModeNumeric;
            break;
        default:
            nếu (SDL_GetTextInputMultiline(props)) {
                mode = k_EFloatingGamepadTextInputModeModeMultipleLines;
            } không_thì {
                mode = k_EFloatingGamepadTextInputModeModeSingleLine;
            }
            break;
        }
        (void)SDL_snprintf(deeplink, sizeof(deeplink),
                           "steam://open/keyboard?XPosition=%i&YPosition=%i&Width=%i&Height=%i&Mode=%d",
                           window->text_input_rect.x, window->text_input_rect.y,
                           window->text_input_rect.w, window->text_input_rect.h,
                           mode);
        SDL_OpenURL(deeplink);
        SDL_SendScreenKeyboardShown();
    }
}

void X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;

    nếu (videodata->use_steam_screen_keyboard) {
        SDL_OpenURL("steam://close/keyboard");
        SDL_SendScreenKeyboardHidden();
    }
}

#endif // SDL_VIDEO_DRIVER_X11
