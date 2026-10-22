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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VITA

#अन्तर्भाव <psp2/kernel/processmgr.h>
#अन्तर्भाव <psp2/ctrl.h>
#अन्तर्भाव <psp2/hid.h>

#अन्तर्भाव "SDL_vitavideo.h"
#अन्तर्भाव "SDL_vitakeyboard.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
पूर्णाङ्क keyboard_hid_handle = 0;
Uint8 पूर्व_कुञ्चिकाः[6] = { 0 };
Uint8 पूर्व_modifiers = 0;
Uint8 locks = 0;
Uint8 तालकम्_कुञ्चिका_अधस्तात् = 0;

शून्य VITA_InitKeyboard(शून्य)
{
#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR
    sce_Sysmodule_आरोपय_Module(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#यदि_अन्तः
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    यदि (keyboard_hid_handle > 0) {
        SDL_सङ्कलय_Keyboard((SDL_KeyboardID)keyboard_hid_handle, रिक्त);
    }
}

शून्य VITA_PollKeyboard(शून्य)
{
    // We skip polling keyboard if no window is created
    यदि (!Vita_गवाक्षः) {
        प्रत्यागम;
    }

    यदि (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        पूर्णाङ्क अङ्कः_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        यदि (अङ्कः_Reports < 0) {
            keyboard_hid_handle = 0;
        } अन्यथा यदि (अङ्कः_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            यदि (k_reports[अङ्कः_Reports - 1].modifiers[1] & 0x1) {
                यदि (!(locks & 0x1)) {
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } अन्यथा {
                यदि (locks & 0x1) {
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            यदि (k_reports[अङ्कः_Reports - 1].modifiers[1] & 0x2) {
                यदि (!(locks & 0x2)) {
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } अन्यथा {
                यदि (locks & 0x2) {
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            यदि (k_reports[अङ्कः_Reports - 1].modifiers[1] & 0x4) {
                यदि (!(locks & 0x4)) {
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } अन्यथा {
                यदि (locks & 0x4) {
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 परिवर्तितम्_modifiers = k_reports[अङ्कः_Reports - 1].modifiers[0] ^ पूर्व_modifiers;

                यदि (परिवर्तितम्_modifiers & 0x01) {
                    यदि (पूर्व_modifiers & 0x01) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                यदि (परिवर्तितम्_modifiers & 0x02) {
                    यदि (पूर्व_modifiers & 0x02) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                यदि (परिवर्तितम्_modifiers & 0x04) {
                    यदि (पूर्व_modifiers & 0x04) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                यदि (परिवर्तितम्_modifiers & 0x08) {
                    यदि (पूर्व_modifiers & 0x08) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                यदि (परिवर्तितम्_modifiers & 0x10) {
                    यदि (पूर्व_modifiers & 0x10) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                यदि (परिवर्तितम्_modifiers & 0x20) {
                    यदि (पूर्व_modifiers & 0x20) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                यदि (परिवर्तितम्_modifiers & 0x40) {
                    यदि (पूर्व_modifiers & 0x40) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                यदि (परिवर्तितम्_modifiers & 0x80) {
                    यदि (पूर्व_modifiers & 0x80) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            पूर्व_modifiers = k_reports[अङ्कः_Reports - 1].modifiers[0];

            प्रति (पूर्णाङ्क i = 0; i < 6; i++) {

                पूर्णाङ्क कुञ्चिका_संहिता = k_reports[अङ्कः_Reports - 1].keycodes[i];

                यदि (कुञ्चिका_संहिता != पूर्व_कुञ्चिकाः[i]) {

                    यदि (पूर्व_कुञ्चिकाः[i]) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, पूर्व_कुञ्चिकाः[i], false);
                    }
                    यदि (कुञ्चिका_संहिता) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, कुञ्चिका_संहिता, true);
                    }
                    पूर्व_कुञ्चिकाः[i] = कुञ्चिका_संहिता;
                }
            }
        }
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_VITA
