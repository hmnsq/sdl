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
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#ضمن <psp2/kernel/processmgr.h>
#ضمن <psp2/ctrl.h>
#ضمن <psp2/hid.h>

#ضمن "SDL_vitavideo.h"
#ضمن "SDL_vitakeyboard.h"
#ضمن "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
صحيح keyboard_hid_handle = 0;
Uint8 prev_کلیلەکان[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 lock_کلیل_down = 0;

فراغ VITA_InitKeyboard(فراغ)
{
#ifdef SDL_VIDEO_VITA_PVR
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#endif
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    إذا (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, عدم);
    }
}

فراغ VITA_PollKeyboard(فراغ)
{
    // We skip polling keyboard if no window is created
    إذا (!Vita_Window) {
        أرجع;
    }

    إذا (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        صحيح ژمارە_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        إذا (ژمارە_Reports < 0) {
            keyboard_hid_handle = 0;
        } وإلا إذا (ژمارە_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            إذا (k_reports[ژمارە_Reports - 1].modifiers[1] & 0x1) {
                إذا (!(locks & 0x1)) {
                    SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } وإلا {
                إذا (locks & 0x1) {
                    SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            إذا (k_reports[ژمارە_Reports - 1].modifiers[1] & 0x2) {
                إذا (!(locks & 0x2)) {
                    SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } وإلا {
                إذا (locks & 0x2) {
                    SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            إذا (k_reports[ژمارە_Reports - 1].modifiers[1] & 0x4) {
                إذا (!(locks & 0x4)) {
                    SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } وإلا {
                إذا (locks & 0x4) {
                    SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[ژمارە_Reports - 1].modifiers[0] ^ prev_modifiers;

                إذا (changed_modifiers & 0x01) {
                    إذا (prev_modifiers & 0x01) {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } وإلا {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                إذا (changed_modifiers & 0x02) {
                    إذا (prev_modifiers & 0x02) {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } وإلا {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                إذا (changed_modifiers & 0x04) {
                    إذا (prev_modifiers & 0x04) {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } وإلا {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                إذا (changed_modifiers & 0x08) {
                    إذا (prev_modifiers & 0x08) {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } وإلا {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                إذا (changed_modifiers & 0x10) {
                    إذا (prev_modifiers & 0x10) {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } وإلا {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                إذا (changed_modifiers & 0x20) {
                    إذا (prev_modifiers & 0x20) {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } وإلا {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                إذا (changed_modifiers & 0x40) {
                    إذا (prev_modifiers & 0x40) {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } وإلا {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                إذا (changed_modifiers & 0x80) {
                    إذا (prev_modifiers & 0x80) {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } وإلا {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[ژمارە_Reports - 1].modifiers[0];

            لكل (صحيح i = 0; i < 6; i++) {

                صحيح کلیل_Code = k_reports[ژمارە_Reports - 1].keycodes[i];

                إذا (کلیل_Code != prev_کلیلەکان[i]) {

                    إذا (prev_کلیلەکان[i]) {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, prev_کلیلەکان[i], false);
                    }
                    إذا (کلیل_Code) {
                        SDL_Send_Keyboard_کلیل(0, keyboardID, 0, کلیل_Code, true);
                    }
                    prev_کلیلەکان[i] = کلیل_Code;
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA
