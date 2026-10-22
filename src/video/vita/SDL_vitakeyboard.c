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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#ଅନ୍ତର୍ଭାଵ <psp2/kernel/processmgr.h>
#ଅନ୍ତର୍ଭାଵ <psp2/ctrl.h>
#ଅନ୍ତର୍ଭାଵ <psp2/hid.h>

#ଅନ୍ତର୍ଭାଵ "SDL_vitavideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_vitakeyboard.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
ପୂର୍ଣ୍ଣସଂଖ୍ୟା keyboard_hid_handle = 0;
Uint8 prev_ଚାବିଗୁଡ଼ିକ[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 lock_ଚାବି_down = 0;

ଶୂନ୍ୟ VITA_InitKeyboard(ଶୂନ୍ୟ)
{
#ifdef SDL_VIDEO_VITA_PVR
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#endif
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    ଯଦି (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, ଖାଲି);
    }
}

ଶୂନ୍ୟ VITA_PollKeyboard(ଶୂନ୍ୟ)
{
    // We skip polling keyboard if no window is created
    ଯଦି (!Vita_Window) {
        ଫେରନ୍ତୁ;
    }

    ଯଦି (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        ଯଦି (ଅଙ୍କ_Reports < 0) {
            keyboard_hid_handle = 0;
        } ଅନ୍ୟଥା ଯଦି (ଅଙ୍କ_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            ଯଦି (k_reports[ଅଙ୍କ_Reports - 1].modifiers[1] & 0x1) {
                ଯଦି (!(locks & 0x1)) {
                    SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } ଅନ୍ୟଥା {
                ଯଦି (locks & 0x1) {
                    SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            ଯଦି (k_reports[ଅଙ୍କ_Reports - 1].modifiers[1] & 0x2) {
                ଯଦି (!(locks & 0x2)) {
                    SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } ଅନ୍ୟଥା {
                ଯଦି (locks & 0x2) {
                    SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            ଯଦି (k_reports[ଅଙ୍କ_Reports - 1].modifiers[1] & 0x4) {
                ଯଦି (!(locks & 0x4)) {
                    SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } ଅନ୍ୟଥା {
                ଯଦି (locks & 0x4) {
                    SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[ଅଙ୍କ_Reports - 1].modifiers[0] ^ prev_modifiers;

                ଯଦି (changed_modifiers & 0x01) {
                    ଯଦି (prev_modifiers & 0x01) {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } ଅନ୍ୟଥା {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                ଯଦି (changed_modifiers & 0x02) {
                    ଯଦି (prev_modifiers & 0x02) {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } ଅନ୍ୟଥା {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                ଯଦି (changed_modifiers & 0x04) {
                    ଯଦି (prev_modifiers & 0x04) {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } ଅନ୍ୟଥା {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                ଯଦି (changed_modifiers & 0x08) {
                    ଯଦି (prev_modifiers & 0x08) {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } ଅନ୍ୟଥା {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                ଯଦି (changed_modifiers & 0x10) {
                    ଯଦି (prev_modifiers & 0x10) {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } ଅନ୍ୟଥା {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                ଯଦି (changed_modifiers & 0x20) {
                    ଯଦି (prev_modifiers & 0x20) {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } ଅନ୍ୟଥା {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                ଯଦି (changed_modifiers & 0x40) {
                    ଯଦି (prev_modifiers & 0x40) {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } ଅନ୍ୟଥା {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                ଯଦି (changed_modifiers & 0x80) {
                    ଯଦି (prev_modifiers & 0x80) {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } ଅନ୍ୟଥା {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[ଅଙ୍କ_Reports - 1].modifiers[0];

            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 6; i++) {

                ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଚାବି_Code = k_reports[ଅଙ୍କ_Reports - 1].keycodes[i];

                ଯଦି (ଚାବି_Code != prev_ଚାବିଗୁଡ଼ିକ[i]) {

                    ଯଦି (prev_ଚାବିଗୁଡ଼ିକ[i]) {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, prev_ଚାବିଗୁଡ଼ିକ[i], false);
                    }
                    ଯଦି (ଚାବି_Code) {
                        SDL_Send_Keyboard_ଚାବି(0, keyboardID, 0, ଚାବି_Code, true);
                    }
                    prev_ଚାବିଗୁଡ଼ିକ[i] = ଚାବି_Code;
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA
