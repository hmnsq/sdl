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

#ifdef SDL_VIDEO_DRIVER_VITA

#ಅನ್ತರ್ಭಾವ <psp2/kernel/processmgr.h>
#ಅನ್ತರ್ಭಾವ <psp2/ctrl.h>
#ಅನ್ತರ್ಭಾವ <psp2/hid.h>

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_vitakeyboard.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
ಪೂರ್ಣಾಙ್ಕ keyboard_hid_handle = 0;
Uint8 prev_ಕೀಲಿಗಳು[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 lock_ಕೀಲಿ_down = 0;

ಶೂನ್ಯ VITA_InitKeyboard(ಶೂನ್ಯ)
{
#ifdef SDL_VIDEO_VITA_PVR
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#endif
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    ಯದಿ (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, ರಿಕ್ತ);
    }
}

ಶೂನ್ಯ VITA_PollKeyboard(ಶೂನ್ಯ)
{
    // We skip polling keyboard if no window is created
    ಯದಿ (!Vita_Window) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        ಯದಿ (ಅಂಕೆ_Reports < 0) {
            keyboard_hid_handle = 0;
        } ಅನ್ಯಥಾ ಯದಿ (ಅಂಕೆ_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            ಯದಿ (k_reports[ಅಂಕೆ_Reports - 1].modifiers[1] & 0x1) {
                ಯದಿ (!(locks & 0x1)) {
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } ಅನ್ಯಥಾ {
                ಯದಿ (locks & 0x1) {
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            ಯದಿ (k_reports[ಅಂಕೆ_Reports - 1].modifiers[1] & 0x2) {
                ಯದಿ (!(locks & 0x2)) {
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } ಅನ್ಯಥಾ {
                ಯದಿ (locks & 0x2) {
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            ಯದಿ (k_reports[ಅಂಕೆ_Reports - 1].modifiers[1] & 0x4) {
                ಯದಿ (!(locks & 0x4)) {
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } ಅನ್ಯಥಾ {
                ಯದಿ (locks & 0x4) {
                    SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[ಅಂಕೆ_Reports - 1].modifiers[0] ^ prev_modifiers;

                ಯದಿ (changed_modifiers & 0x01) {
                    ಯದಿ (prev_modifiers & 0x01) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } ಅನ್ಯಥಾ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                ಯದಿ (changed_modifiers & 0x02) {
                    ಯದಿ (prev_modifiers & 0x02) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } ಅನ್ಯಥಾ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                ಯದಿ (changed_modifiers & 0x04) {
                    ಯದಿ (prev_modifiers & 0x04) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } ಅನ್ಯಥಾ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                ಯದಿ (changed_modifiers & 0x08) {
                    ಯದಿ (prev_modifiers & 0x08) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } ಅನ್ಯಥಾ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                ಯದಿ (changed_modifiers & 0x10) {
                    ಯದಿ (prev_modifiers & 0x10) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } ಅನ್ಯಥಾ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                ಯದಿ (changed_modifiers & 0x20) {
                    ಯದಿ (prev_modifiers & 0x20) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } ಅನ್ಯಥಾ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                ಯದಿ (changed_modifiers & 0x40) {
                    ಯದಿ (prev_modifiers & 0x40) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } ಅನ್ಯಥಾ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                ಯದಿ (changed_modifiers & 0x80) {
                    ಯದಿ (prev_modifiers & 0x80) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } ಅನ್ಯಥಾ {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[ಅಂಕೆ_Reports - 1].modifiers[0];

            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 6; i++) {

                ಪೂರ್ಣಾಙ್ಕ ಕೀಲಿ_Code = k_reports[ಅಂಕೆ_Reports - 1].keycodes[i];

                ಯದಿ (ಕೀಲಿ_Code != prev_ಕೀಲಿಗಳು[i]) {

                    ಯದಿ (prev_ಕೀಲಿಗಳು[i]) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, prev_ಕೀಲಿಗಳು[i], false);
                    }
                    ಯದಿ (ಕೀಲಿ_Code) {
                        SDL_Send_Keyboard_ಕೀಲಿ(0, keyboardID, 0, ಕೀಲಿ_Code, true);
                    }
                    prev_ಕೀಲಿಗಳು[i] = ಕೀಲಿ_Code;
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA
