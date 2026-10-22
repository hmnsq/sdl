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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#அந்தர்பாவ <psp2/kernel/processmgr.h>
#அந்தர்பாவ <psp2/ctrl.h>
#அந்தர்பாவ <psp2/hid.h>

#அந்தர்பாவ "SDL_vitavideo.h"
#அந்தர்பாவ "SDL_vitakeyboard.h"
#அந்தர்பாவ "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
முழு keyboard_hid_handle = 0;
Uint8 prev_சாவிகள்[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 lock_சாவி_down = 0;

வெறுமை VITA_InitKeyboard(வெறுமை)
{
#ifdef SDL_VIDEO_VITA_PVR
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#endif
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    எனில் (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, வெற்று);
    }
}

வெறுமை VITA_PollKeyboard(வெறுமை)
{
    // We skip polling keyboard if no window is created
    எனில் (!Vita_Window) {
        திரும்பு;
    }

    எனில் (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        முழு இலக்கம்_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        எனில் (இலக்கம்_Reports < 0) {
            keyboard_hid_handle = 0;
        } இல்லையெனில் எனில் (இலக்கம்_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            எனில் (k_reports[இலக்கம்_Reports - 1].modifiers[1] & 0x1) {
                எனில் (!(locks & 0x1)) {
                    SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } இல்லையெனில் {
                எனில் (locks & 0x1) {
                    SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            எனில் (k_reports[இலக்கம்_Reports - 1].modifiers[1] & 0x2) {
                எனில் (!(locks & 0x2)) {
                    SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } இல்லையெனில் {
                எனில் (locks & 0x2) {
                    SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            எனில் (k_reports[இலக்கம்_Reports - 1].modifiers[1] & 0x4) {
                எனில் (!(locks & 0x4)) {
                    SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } இல்லையெனில் {
                எனில் (locks & 0x4) {
                    SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[இலக்கம்_Reports - 1].modifiers[0] ^ prev_modifiers;

                எனில் (changed_modifiers & 0x01) {
                    எனில் (prev_modifiers & 0x01) {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } இல்லையெனில் {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                எனில் (changed_modifiers & 0x02) {
                    எனில் (prev_modifiers & 0x02) {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } இல்லையெனில் {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                எனில் (changed_modifiers & 0x04) {
                    எனில் (prev_modifiers & 0x04) {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } இல்லையெனில் {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                எனில் (changed_modifiers & 0x08) {
                    எனில் (prev_modifiers & 0x08) {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } இல்லையெனில் {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                எனில் (changed_modifiers & 0x10) {
                    எனில் (prev_modifiers & 0x10) {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } இல்லையெனில் {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                எனில் (changed_modifiers & 0x20) {
                    எனில் (prev_modifiers & 0x20) {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } இல்லையெனில் {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                எனில் (changed_modifiers & 0x40) {
                    எனில் (prev_modifiers & 0x40) {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } இல்லையெனில் {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                எனில் (changed_modifiers & 0x80) {
                    எனில் (prev_modifiers & 0x80) {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } இல்லையெனில் {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[இலக்கம்_Reports - 1].modifiers[0];

            க்கு (முழு i = 0; i < 6; i++) {

                முழு சாவி_Code = k_reports[இலக்கம்_Reports - 1].keycodes[i];

                எனில் (சாவி_Code != prev_சாவிகள்[i]) {

                    எனில் (prev_சாவிகள்[i]) {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, prev_சாவிகள்[i], false);
                    }
                    எனில் (சாவி_Code) {
                        SDL_Send_Keyboard_சாவி(0, keyboardID, 0, சாவி_Code, true);
                    }
                    prev_சாவிகள்[i] = சாவி_Code;
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA
