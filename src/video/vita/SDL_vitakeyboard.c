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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VITA

#شامل <psp2/kernel/processmgr.h>
#شامل <psp2/ctrl.h>
#شامل <psp2/hid.h>

#شامل "SDL_vitavideo.h"
#شامل "SDL_vitakeyboard.h"
#شامل "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
صحیح keyboard_hid_handle = 0;
Uint8 پچھلا_کلیدیں[6] = { 0 };
Uint8 پچھلا_modifiers = 0;
Uint8 locks = 0;
Uint8 تالا_کلید_نیچے_کو = 0;

خالی VITA_InitKeyboard(خالی)
{
#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR
    sce_Sysmodule_بھرو_Module(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#اگر_ختم
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    اگر (keyboard_hid_handle > 0) {
        SDL_جوڑو_Keyboard((SDL_KeyboardID)keyboard_hid_handle, تہی);
    }
}

خالی VITA_PollKeyboard(خالی)
{
    // We skip polling keyboard if no window is created
    اگر (!Vita_کھڑکی) {
        واپس;
    }

    اگر (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        صحیح عدد_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        اگر (عدد_Reports < 0) {
            keyboard_hid_handle = 0;
        } ورنہ اگر (عدد_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            اگر (k_reports[عدد_Reports - 1].modifiers[1] & 0x1) {
                اگر (!(locks & 0x1)) {
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } ورنہ {
                اگر (locks & 0x1) {
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            اگر (k_reports[عدد_Reports - 1].modifiers[1] & 0x2) {
                اگر (!(locks & 0x2)) {
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } ورنہ {
                اگر (locks & 0x2) {
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            اگر (k_reports[عدد_Reports - 1].modifiers[1] & 0x4) {
                اگر (!(locks & 0x4)) {
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } ورنہ {
                اگر (locks & 0x4) {
                    SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 بدلا_modifiers = k_reports[عدد_Reports - 1].modifiers[0] ^ پچھلا_modifiers;

                اگر (بدلا_modifiers & 0x01) {
                    اگر (پچھلا_modifiers & 0x01) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } ورنہ {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                اگر (بدلا_modifiers & 0x02) {
                    اگر (پچھلا_modifiers & 0x02) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } ورنہ {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                اگر (بدلا_modifiers & 0x04) {
                    اگر (پچھلا_modifiers & 0x04) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } ورنہ {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                اگر (بدلا_modifiers & 0x08) {
                    اگر (پچھلا_modifiers & 0x08) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } ورنہ {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                اگر (بدلا_modifiers & 0x10) {
                    اگر (پچھلا_modifiers & 0x10) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } ورنہ {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                اگر (بدلا_modifiers & 0x20) {
                    اگر (پچھلا_modifiers & 0x20) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } ورنہ {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                اگر (بدلا_modifiers & 0x40) {
                    اگر (پچھلا_modifiers & 0x40) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } ورنہ {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                اگر (بدلا_modifiers & 0x80) {
                    اگر (پچھلا_modifiers & 0x80) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } ورنہ {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            پچھلا_modifiers = k_reports[عدد_Reports - 1].modifiers[0];

            برائے (صحیح i = 0; i < 6; i++) {

                صحیح کلید_رمز = k_reports[عدد_Reports - 1].keycodes[i];

                اگر (کلید_رمز != پچھلا_کلیدیں[i]) {

                    اگر (پچھلا_کلیدیں[i]) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, پچھلا_کلیدیں[i], false);
                    }
                    اگر (کلید_رمز) {
                        SDL_Send_Keyboard_کلید(0, keyboardID, 0, کلید_رمز, true);
                    }
                    پچھلا_کلیدیں[i] = کلید_رمز;
                }
            }
        }
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_VITA
