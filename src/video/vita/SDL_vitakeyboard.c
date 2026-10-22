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

#ifdef SDL_VIDEO_DRIVER_VITA

#अन्तर्भाव <psp2/kernel/processmgr.h>
#अन्तर्भाव <psp2/ctrl.h>
#अन्तर्भाव <psp2/hid.h>

#अन्तर्भाव "SDL_vitavideo.h"
#अन्तर्भाव "SDL_vitakeyboard.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
पूर्णाङ्क keyboard_hid_handle = 0;
Uint8 prev_कुञ्चिकाः[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 lock_कुञ्चिका_down = 0;

शून्य VITA_InitKeyboard(शून्य)
{
#ifdef SDL_VIDEO_VITA_PVR
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#endif
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    सचे (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, रिक्त);
    }
}

शून्य VITA_PollKeyboard(शून्य)
{
    // We skip polling keyboard if no window is created
    सचे (!Vita_Window) {
        पटिनिवत्त;
    }

    सचे (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        पूर्णाङ्क अङ्कः_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        सचे (अङ्कः_Reports < 0) {
            keyboard_hid_handle = 0;
        } अञ्ञथा सचे (अङ्कः_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            सचे (k_reports[अङ्कः_Reports - 1].modifiers[1] & 0x1) {
                सचे (!(locks & 0x1)) {
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } अञ्ञथा {
                सचे (locks & 0x1) {
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            सचे (k_reports[अङ्कः_Reports - 1].modifiers[1] & 0x2) {
                सचे (!(locks & 0x2)) {
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } अञ्ञथा {
                सचे (locks & 0x2) {
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            सचे (k_reports[अङ्कः_Reports - 1].modifiers[1] & 0x4) {
                सचे (!(locks & 0x4)) {
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } अञ्ञथा {
                सचे (locks & 0x4) {
                    SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[अङ्कः_Reports - 1].modifiers[0] ^ prev_modifiers;

                सचे (changed_modifiers & 0x01) {
                    सचे (prev_modifiers & 0x01) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } अञ्ञथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                सचे (changed_modifiers & 0x02) {
                    सचे (prev_modifiers & 0x02) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } अञ्ञथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                सचे (changed_modifiers & 0x04) {
                    सचे (prev_modifiers & 0x04) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } अञ्ञथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                सचे (changed_modifiers & 0x08) {
                    सचे (prev_modifiers & 0x08) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } अञ्ञथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                सचे (changed_modifiers & 0x10) {
                    सचे (prev_modifiers & 0x10) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } अञ्ञथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                सचे (changed_modifiers & 0x20) {
                    सचे (prev_modifiers & 0x20) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } अञ्ञथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                सचे (changed_modifiers & 0x40) {
                    सचे (prev_modifiers & 0x40) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } अञ्ञथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                सचे (changed_modifiers & 0x80) {
                    सचे (prev_modifiers & 0x80) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } अञ्ञथा {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[अङ्कः_Reports - 1].modifiers[0];

            अत्थाय (पूर्णाङ्क i = 0; i < 6; i++) {

                पूर्णाङ्क कुञ्चिका_Code = k_reports[अङ्कः_Reports - 1].keycodes[i];

                सचे (कुञ्चिका_Code != prev_कुञ्चिकाः[i]) {

                    सचे (prev_कुञ्चिकाः[i]) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, prev_कुञ्चिकाः[i], false);
                    }
                    सचे (कुञ्चिका_Code) {
                        SDL_Send_Keyboard_कुञ्चिका(0, keyboardID, 0, कुञ्चिका_Code, true);
                    }
                    prev_कुञ्चिकाः[i] = कुञ्चिका_Code;
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA
