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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VITA

#ಅನ್ತರ್ಭಾವ <psp2/kernel/processmgr.h>
#ಅನ್ತರ್ಭಾವ <psp2/ctrl.h>
#ಅನ್ತರ್ಭಾವ <psp2/hid.h>

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_vitakeyboard.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
ಪೂರ್ಣಾಂಕ keyboard_hid_handle = 0;
Uint8 prev_ಕೀಲಿಗಳು[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 ಬೀಗ_ಕೀಲಿ_ಕೆಳಕ್ಕೆ = 0;

ಶೂನ್ಯ VITA_InitKeyboard(ಶೂನ್ಯ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR
    sce_Sysmodule_ತುಂಬು_Module(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#ಆದರೆ_ಅಂತ್ಯ
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    ಆದರೆ (keyboard_hid_handle > 0) {
        SDL_ಕೂಡಿಸು_Keyboard((SDL_KeyboardID)keyboard_hid_handle, ಖಾಲಿ);
    }
}

ಶೂನ್ಯ VITA_PollKeyboard(ಶೂನ್ಯ)
{
    // We skip polling keyboard if no window is created
    ಆದರೆ (!Vita_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        ಪೂರ್ಣಾಂಕ ಅಂಕೆ_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        ಆದರೆ (ಅಂಕೆ_Reports < 0) {
            keyboard_hid_handle = 0;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಅಂಕೆ_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            ಆದರೆ (k_reports[ಅಂಕೆ_Reports - 1].modifiers[1] & 0x1) {
                ಆದರೆ (!(locks & 0x1)) {
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಆದರೆ (locks & 0x1) {
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            ಆದರೆ (k_reports[ಅಂಕೆ_Reports - 1].modifiers[1] & 0x2) {
                ಆದರೆ (!(locks & 0x2)) {
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಆದರೆ (locks & 0x2) {
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            ಆದರೆ (k_reports[ಅಂಕೆ_Reports - 1].modifiers[1] & 0x4) {
                ಆದರೆ (!(locks & 0x4)) {
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಆದರೆ (locks & 0x4) {
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 ಬದಲಾಯಿತು_modifiers = k_reports[ಅಂಕೆ_Reports - 1].modifiers[0] ^ prev_modifiers;

                ಆದರೆ (ಬದಲಾಯಿತು_modifiers & 0x01) {
                    ಆದರೆ (prev_modifiers & 0x01) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                ಆದರೆ (ಬದಲಾಯಿತು_modifiers & 0x02) {
                    ಆದರೆ (prev_modifiers & 0x02) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                ಆದರೆ (ಬದಲಾಯಿತು_modifiers & 0x04) {
                    ಆದರೆ (prev_modifiers & 0x04) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                ಆದರೆ (ಬದಲಾಯಿತು_modifiers & 0x08) {
                    ಆದರೆ (prev_modifiers & 0x08) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                ಆದರೆ (ಬದಲಾಯಿತು_modifiers & 0x10) {
                    ಆದರೆ (prev_modifiers & 0x10) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                ಆದರೆ (ಬದಲಾಯಿತು_modifiers & 0x20) {
                    ಆದರೆ (prev_modifiers & 0x20) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                ಆದರೆ (ಬದಲಾಯಿತು_modifiers & 0x40) {
                    ಆದರೆ (prev_modifiers & 0x40) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                ಆದರೆ (ಬದಲಾಯಿತು_modifiers & 0x80) {
                    ಆದರೆ (prev_modifiers & 0x80) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[ಅಂಕೆ_Reports - 1].modifiers[0];

            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 6; i++) {

                ಪೂರ್ಣಾಂಕ ಕೀಲಿ_ಸಂಕೇತ = k_reports[ಅಂಕೆ_Reports - 1].keycodes[i];

                ಆದರೆ (ಕೀಲಿ_ಸಂಕೇತ != prev_ಕೀಲಿಗಳು[i]) {

                    ಆದರೆ (prev_ಕೀಲಿಗಳು[i]) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, prev_ಕೀಲಿಗಳು[i], false);
                    }
                    ಆದರೆ (ಕೀಲಿ_ಸಂಕೇತ) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, ಕೀಲಿ_ಸಂಕೇತ, true);
                    }
                    prev_ಕೀಲಿಗಳು[i] = ಕೀಲಿ_ಸಂಕೇತ;
                }
            }
        }
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_VITA
