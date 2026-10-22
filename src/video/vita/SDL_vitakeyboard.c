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
Uint8 prev_कुंजियाँ[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 lock_कुंजी_down = 0;

शून्य VITA_InitKeyboard(शून्य)
{
#ifdef SDL_VIDEO_VITA_PVR
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#endif
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    यदि (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, रिक्त);
    }
}

शून्य VITA_PollKeyboard(शून्य)
{
    // We skip polling keyboard if no window is created
    यदि (!Vita_Window) {
        प्रत्यागम;
    }

    यदि (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        पूर्णाङ्क अंक_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        यदि (अंक_Reports < 0) {
            keyboard_hid_handle = 0;
        } अन्यथा यदि (अंक_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            यदि (k_reports[अंक_Reports - 1].modifiers[1] & 0x1) {
                यदि (!(locks & 0x1)) {
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } अन्यथा {
                यदि (locks & 0x1) {
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            यदि (k_reports[अंक_Reports - 1].modifiers[1] & 0x2) {
                यदि (!(locks & 0x2)) {
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } अन्यथा {
                यदि (locks & 0x2) {
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            यदि (k_reports[अंक_Reports - 1].modifiers[1] & 0x4) {
                यदि (!(locks & 0x4)) {
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } अन्यथा {
                यदि (locks & 0x4) {
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[अंक_Reports - 1].modifiers[0] ^ prev_modifiers;

                यदि (changed_modifiers & 0x01) {
                    यदि (prev_modifiers & 0x01) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                यदि (changed_modifiers & 0x02) {
                    यदि (prev_modifiers & 0x02) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                यदि (changed_modifiers & 0x04) {
                    यदि (prev_modifiers & 0x04) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                यदि (changed_modifiers & 0x08) {
                    यदि (prev_modifiers & 0x08) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                यदि (changed_modifiers & 0x10) {
                    यदि (prev_modifiers & 0x10) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                यदि (changed_modifiers & 0x20) {
                    यदि (prev_modifiers & 0x20) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                यदि (changed_modifiers & 0x40) {
                    यदि (prev_modifiers & 0x40) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                यदि (changed_modifiers & 0x80) {
                    यदि (prev_modifiers & 0x80) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[अंक_Reports - 1].modifiers[0];

            प्रति (पूर्णाङ्क i = 0; i < 6; i++) {

                पूर्णाङ्क कुंजी_Code = k_reports[अंक_Reports - 1].keycodes[i];

                यदि (कुंजी_Code != prev_कुंजियाँ[i]) {

                    यदि (prev_कुंजियाँ[i]) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, prev_कुंजियाँ[i], false);
                    }
                    यदि (कुंजी_Code) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, कुंजी_Code, true);
                    }
                    prev_कुंजियाँ[i] = कुंजी_Code;
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA
