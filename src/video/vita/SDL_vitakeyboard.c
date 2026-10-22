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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VITA

#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/kernel/processmgr.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/ctrl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/hid.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitavideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitakeyboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
ਪੂਰਨ keyboard_hid_handle = 0;
Uint8 prev_ਕੁੰਜੀਆਂ[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 ਤਾਲਾ_ਕੁੰਜੀ_ਥੱਲੇ = 0;

ਖਾਲੀ VITA_InitKeyboard(ਖਾਲੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR
    sce_Sysmodule_ਲੱਦੋ_Module(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#ਜੇ_ਅੰਤ
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    ਜੇ (keyboard_hid_handle > 0) {
        SDL_ਜੋੜੋ_Keyboard((SDL_KeyboardID)keyboard_hid_handle, ਨਿਰਾ);
    }
}

ਖਾਲੀ VITA_PollKeyboard(ਖਾਲੀ)
{
    // We skip polling keyboard if no window is created
    ਜੇ (!Vita_ਖਿੜਕੀ) {
        ਵਾਪਸ;
    }

    ਜੇ (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        ਪੂਰਨ ਅੰਕ_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        ਜੇ (ਅੰਕ_Reports < 0) {
            keyboard_hid_handle = 0;
        } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕ_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            ਜੇ (k_reports[ਅੰਕ_Reports - 1].modifiers[1] & 0x1) {
                ਜੇ (!(locks & 0x1)) {
                    SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } ਨਹੀਂਤਾਂ {
                ਜੇ (locks & 0x1) {
                    SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            ਜੇ (k_reports[ਅੰਕ_Reports - 1].modifiers[1] & 0x2) {
                ਜੇ (!(locks & 0x2)) {
                    SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } ਨਹੀਂਤਾਂ {
                ਜੇ (locks & 0x2) {
                    SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            ਜੇ (k_reports[ਅੰਕ_Reports - 1].modifiers[1] & 0x4) {
                ਜੇ (!(locks & 0x4)) {
                    SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } ਨਹੀਂਤਾਂ {
                ਜੇ (locks & 0x4) {
                    SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 ਬਦਲਿਆ_modifiers = k_reports[ਅੰਕ_Reports - 1].modifiers[0] ^ prev_modifiers;

                ਜੇ (ਬਦਲਿਆ_modifiers & 0x01) {
                    ਜੇ (prev_modifiers & 0x01) {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } ਨਹੀਂਤਾਂ {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                ਜੇ (ਬਦਲਿਆ_modifiers & 0x02) {
                    ਜੇ (prev_modifiers & 0x02) {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } ਨਹੀਂਤਾਂ {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                ਜੇ (ਬਦਲਿਆ_modifiers & 0x04) {
                    ਜੇ (prev_modifiers & 0x04) {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } ਨਹੀਂਤਾਂ {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                ਜੇ (ਬਦਲਿਆ_modifiers & 0x08) {
                    ਜੇ (prev_modifiers & 0x08) {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } ਨਹੀਂਤਾਂ {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                ਜੇ (ਬਦਲਿਆ_modifiers & 0x10) {
                    ਜੇ (prev_modifiers & 0x10) {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } ਨਹੀਂਤਾਂ {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                ਜੇ (ਬਦਲਿਆ_modifiers & 0x20) {
                    ਜੇ (prev_modifiers & 0x20) {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } ਨਹੀਂਤਾਂ {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                ਜੇ (ਬਦਲਿਆ_modifiers & 0x40) {
                    ਜੇ (prev_modifiers & 0x40) {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } ਨਹੀਂਤਾਂ {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                ਜੇ (ਬਦਲਿਆ_modifiers & 0x80) {
                    ਜੇ (prev_modifiers & 0x80) {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } ਨਹੀਂਤਾਂ {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[ਅੰਕ_Reports - 1].modifiers[0];

            ਲਈ (ਪੂਰਨ i = 0; i < 6; i++) {

                ਪੂਰਨ ਕੁੰਜੀ_ਕੋਡ = k_reports[ਅੰਕ_Reports - 1].keycodes[i];

                ਜੇ (ਕੁੰਜੀ_ਕੋਡ != prev_ਕੁੰਜੀਆਂ[i]) {

                    ਜੇ (prev_ਕੁੰਜੀਆਂ[i]) {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, prev_ਕੁੰਜੀਆਂ[i], false);
                    }
                    ਜੇ (ਕੁੰਜੀ_ਕੋਡ) {
                        SDL_Send_Keyboard_ਕੁੰਜੀ(0, keyboardID, 0, ਕੁੰਜੀ_ਕੋਡ, true);
                    }
                    prev_ਕੁੰਜੀਆਂ[i] = ਕੁੰਜੀ_ਕੋਡ;
                }
            }
        }
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_VITA
