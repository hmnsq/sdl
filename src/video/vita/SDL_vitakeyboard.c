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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VITA

#అన్తర్భావ <psp2/kernel/processmgr.h>
#అన్తర్భావ <psp2/ctrl.h>
#అన్తర్భావ <psp2/hid.h>

#అన్తర్భావ "SDL_vitavideo.h"
#అన్తర్భావ "SDL_vitakeyboard.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
పూర్ణాంకం keyboard_hid_handle = 0;
Uint8 prev_కీలకాలు[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 తాళం_కీలకం_కిందికి = 0;

శూన్య VITA_InitKeyboard(శూన్య)
{
#నిర్వచితమైతే SDL_VIDEO_VITA_PVR
    sce_Sysmodule_ఎక్కించు_Module(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#అయితే_ముగింపు
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    ఒకవేళ (keyboard_hid_handle > 0) {
        SDL_కూడు_Keyboard((SDL_KeyboardID)keyboard_hid_handle, ఖాళీ);
    }
}

శూన్య VITA_PollKeyboard(శూన్య)
{
    // We skip polling keyboard if no window is created
    ఒకవేళ (!Vita_కిటికీ) {
        తిరిగి;
    }

    ఒకవేళ (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        పూర్ణాంకం అంకె_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        ఒకవేళ (అంకె_Reports < 0) {
            keyboard_hid_handle = 0;
        } లేకపోతే ఒకవేళ (అంకె_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            ఒకవేళ (k_reports[అంకె_Reports - 1].modifiers[1] & 0x1) {
                ఒకవేళ (!(locks & 0x1)) {
                    SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } లేకపోతే {
                ఒకవేళ (locks & 0x1) {
                    SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            ఒకవేళ (k_reports[అంకె_Reports - 1].modifiers[1] & 0x2) {
                ఒకవేళ (!(locks & 0x2)) {
                    SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } లేకపోతే {
                ఒకవేళ (locks & 0x2) {
                    SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            ఒకవేళ (k_reports[అంకె_Reports - 1].modifiers[1] & 0x4) {
                ఒకవేళ (!(locks & 0x4)) {
                    SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } లేకపోతే {
                ఒకవేళ (locks & 0x4) {
                    SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 మారింది_modifiers = k_reports[అంకె_Reports - 1].modifiers[0] ^ prev_modifiers;

                ఒకవేళ (మారింది_modifiers & 0x01) {
                    ఒకవేళ (prev_modifiers & 0x01) {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } లేకపోతే {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                ఒకవేళ (మారింది_modifiers & 0x02) {
                    ఒకవేళ (prev_modifiers & 0x02) {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } లేకపోతే {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                ఒకవేళ (మారింది_modifiers & 0x04) {
                    ఒకవేళ (prev_modifiers & 0x04) {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } లేకపోతే {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                ఒకవేళ (మారింది_modifiers & 0x08) {
                    ఒకవేళ (prev_modifiers & 0x08) {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } లేకపోతే {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                ఒకవేళ (మారింది_modifiers & 0x10) {
                    ఒకవేళ (prev_modifiers & 0x10) {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } లేకపోతే {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                ఒకవేళ (మారింది_modifiers & 0x20) {
                    ఒకవేళ (prev_modifiers & 0x20) {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } లేకపోతే {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                ఒకవేళ (మారింది_modifiers & 0x40) {
                    ఒకవేళ (prev_modifiers & 0x40) {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } లేకపోతే {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                ఒకవేళ (మారింది_modifiers & 0x80) {
                    ఒకవేళ (prev_modifiers & 0x80) {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } లేకపోతే {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[అంకె_Reports - 1].modifiers[0];

            కొరకు (పూర్ణాంకం i = 0; i < 6; i++) {

                పూర్ణాంకం కీలకం_సంకేతం = k_reports[అంకె_Reports - 1].keycodes[i];

                ఒకవేళ (కీలకం_సంకేతం != prev_కీలకాలు[i]) {

                    ఒకవేళ (prev_కీలకాలు[i]) {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, prev_కీలకాలు[i], false);
                    }
                    ఒకవేళ (కీలకం_సంకేతం) {
                        SDL_Send_Keyboard_కీలకం(0, keyboardID, 0, కీలకం_సంకేతం, true);
                    }
                    prev_కీలకాలు[i] = కీలకం_సంకేతం;
                }
            }
        }
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VITA
