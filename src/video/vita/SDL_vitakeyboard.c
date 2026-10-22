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
#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#شامل <psp2/kernel/processmgr.h>
#شامل <psp2/ctrl.h>
#شامل <psp2/hid.h>

#شامل "SDL_vitavideo.h"
#شامل "SDL_vitakeyboard.h"
#شامل "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
صحیح keyboard_hid_handle = 0;
Uint8 prev_کلیدها[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 lock_کلید_down = 0;

تهی VITA_InitKeyboard(تهی)
{
#ifdef SDL_VIDEO_VITA_PVR
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#endif
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    اگر (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, پوچ);
    }
}

تهی VITA_PollKeyboard(تهی)
{
    // We skip polling keyboard if no window is created
    اگر (!Vita_Window) {
        بازگشت;
    }

    اگر (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        صحیح رقم_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        اگر (رقم_Reports < 0) {
            keyboard_hid_handle = 0;
        } وگرنه اگر (رقم_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            اگر (k_reports[رقم_Reports - 1].modifiers[1] & 0x1) {
                اگر (!(locks & 0x1)) {
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } وگرنه {
                اگر (locks & 0x1) {
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            اگر (k_reports[رقم_Reports - 1].modifiers[1] & 0x2) {
                اگر (!(locks & 0x2)) {
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } وگرنه {
                اگر (locks & 0x2) {
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            اگر (k_reports[رقم_Reports - 1].modifiers[1] & 0x4) {
                اگر (!(locks & 0x4)) {
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } وگرنه {
                اگر (locks & 0x4) {
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[رقم_Reports - 1].modifiers[0] ^ prev_modifiers;

                اگر (changed_modifiers & 0x01) {
                    اگر (prev_modifiers & 0x01) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } وگرنه {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                اگر (changed_modifiers & 0x02) {
                    اگر (prev_modifiers & 0x02) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } وگرنه {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                اگر (changed_modifiers & 0x04) {
                    اگر (prev_modifiers & 0x04) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } وگرنه {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                اگر (changed_modifiers & 0x08) {
                    اگر (prev_modifiers & 0x08) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } وگرنه {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                اگر (changed_modifiers & 0x10) {
                    اگر (prev_modifiers & 0x10) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } وگرنه {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                اگر (changed_modifiers & 0x20) {
                    اگر (prev_modifiers & 0x20) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } وگرنه {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                اگر (changed_modifiers & 0x40) {
                    اگر (prev_modifiers & 0x40) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } وگرنه {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                اگر (changed_modifiers & 0x80) {
                    اگر (prev_modifiers & 0x80) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } وگرنه {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[رقم_Reports - 1].modifiers[0];

            برای (صحیح i = 0; i < 6; i++) {

                صحیح کلید_Code = k_reports[رقم_Reports - 1].keycodes[i];

                اگر (کلید_Code != prev_کلیدها[i]) {

                    اگر (prev_کلیدها[i]) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, prev_کلیدها[i], false);
                    }
                    اگر (کلید_Code) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, کلید_Code, true);
                    }
                    prev_کلیدها[i] = کلید_Code;
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA
