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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#অন্তর্ভাব <psp2/kernel/processmgr.h>
#অন্তর্ভাব <psp2/ctrl.h>
#অন্তর্ভাব <psp2/hid.h>

#অন্তর্ভাব "SDL_vitavideo.h"
#অন্তর্ভাব "SDL_vitakeyboard.h"
#অন্তর্ভাব "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
পূর্ণসংখ্যা keyboard_hid_handle = 0;
Uint8 পূর্ব_চাবিগুলি[6] = { 0 };
Uint8 পূর্ব_modifiers = 0;
Uint8 locks = 0;
Uint8 lock_চাবি_down = 0;

শূন্য VITA_InitKeyboard(শূন্য)
{
#ifdef SDL_VIDEO_VITA_PVR
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#endif
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    যদি (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, ফাঁকা);
    }
}

শূন্য VITA_PollKeyboard(শূন্য)
{
    // We skip polling keyboard if no window is created
    যদি (!Vita_Window) {
        ফেরত;
    }

    যদি (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        পূর্ণসংখ্যা অঙ্ক_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        যদি (অঙ্ক_Reports < 0) {
            keyboard_hid_handle = 0;
        } অন্যথা যদি (অঙ্ক_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            যদি (k_reports[অঙ্ক_Reports - 1].modifiers[1] & 0x1) {
                যদি (!(locks & 0x1)) {
                    SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } অন্যথা {
                যদি (locks & 0x1) {
                    SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            যদি (k_reports[অঙ্ক_Reports - 1].modifiers[1] & 0x2) {
                যদি (!(locks & 0x2)) {
                    SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } অন্যথা {
                যদি (locks & 0x2) {
                    SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            যদি (k_reports[অঙ্ক_Reports - 1].modifiers[1] & 0x4) {
                যদি (!(locks & 0x4)) {
                    SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } অন্যথা {
                যদি (locks & 0x4) {
                    SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[অঙ্ক_Reports - 1].modifiers[0] ^ পূর্ব_modifiers;

                যদি (changed_modifiers & 0x01) {
                    যদি (পূর্ব_modifiers & 0x01) {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } অন্যথা {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                যদি (changed_modifiers & 0x02) {
                    যদি (পূর্ব_modifiers & 0x02) {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } অন্যথা {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                যদি (changed_modifiers & 0x04) {
                    যদি (পূর্ব_modifiers & 0x04) {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } অন্যথা {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                যদি (changed_modifiers & 0x08) {
                    যদি (পূর্ব_modifiers & 0x08) {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } অন্যথা {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                যদি (changed_modifiers & 0x10) {
                    যদি (পূর্ব_modifiers & 0x10) {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } অন্যথা {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                যদি (changed_modifiers & 0x20) {
                    যদি (পূর্ব_modifiers & 0x20) {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } অন্যথা {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                যদি (changed_modifiers & 0x40) {
                    যদি (পূর্ব_modifiers & 0x40) {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } অন্যথা {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                যদি (changed_modifiers & 0x80) {
                    যদি (পূর্ব_modifiers & 0x80) {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } অন্যথা {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            পূর্ব_modifiers = k_reports[অঙ্ক_Reports - 1].modifiers[0];

            জন্য (পূর্ণসংখ্যা i = 0; i < 6; i++) {

                পূর্ণসংখ্যা চাবি_Code = k_reports[অঙ্ক_Reports - 1].keycodes[i];

                যদি (চাবি_Code != পূর্ব_চাবিগুলি[i]) {

                    যদি (পূর্ব_চাবিগুলি[i]) {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, পূর্ব_চাবিগুলি[i], false);
                    }
                    যদি (চাবি_Code) {
                        SDL_Send_Keyboard_চাবি(0, keyboardID, 0, চাবি_Code, true);
                    }
                    পূর্ব_চাবিগুলি[i] = চাবি_Code;
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA
