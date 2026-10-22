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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#અન્તર્ભાવ <psp2/kernel/processmgr.h>
#અન્તર્ભાવ <psp2/ctrl.h>
#અન્તર્ભાવ <psp2/hid.h>

#અન્તર્ભાવ "SDL_vitavideo.h"
#અન્તર્ભાવ "SDL_vitakeyboard.h"
#અન્તર્ભાવ "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
પૂર્ણાંક keyboard_hid_handle = 0;
Uint8 prev_ચાવીઓ[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 lock_ચાવી_down = 0;

શૂન્ય VITA_InitKeyboard(શૂન્ય)
{
#ifdef SDL_VIDEO_VITA_PVR
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#endif
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    જો (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, ખાલી);
    }
}

શૂન્ય VITA_PollKeyboard(શૂન્ય)
{
    // We skip polling keyboard if no window is created
    જો (!Vita_Window) {
        પાછા;
    }

    જો (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        પૂર્ણાંક અંક_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        જો (અંક_Reports < 0) {
            keyboard_hid_handle = 0;
        } નહીંતર જો (અંક_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            જો (k_reports[અંક_Reports - 1].modifiers[1] & 0x1) {
                જો (!(locks & 0x1)) {
                    SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } નહીંતર {
                જો (locks & 0x1) {
                    SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            જો (k_reports[અંક_Reports - 1].modifiers[1] & 0x2) {
                જો (!(locks & 0x2)) {
                    SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } નહીંતર {
                જો (locks & 0x2) {
                    SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            જો (k_reports[અંક_Reports - 1].modifiers[1] & 0x4) {
                જો (!(locks & 0x4)) {
                    SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } નહીંતર {
                જો (locks & 0x4) {
                    SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[અંક_Reports - 1].modifiers[0] ^ prev_modifiers;

                જો (changed_modifiers & 0x01) {
                    જો (prev_modifiers & 0x01) {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } નહીંતર {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                જો (changed_modifiers & 0x02) {
                    જો (prev_modifiers & 0x02) {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } નહીંતર {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                જો (changed_modifiers & 0x04) {
                    જો (prev_modifiers & 0x04) {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } નહીંતર {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                જો (changed_modifiers & 0x08) {
                    જો (prev_modifiers & 0x08) {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } નહીંતર {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                જો (changed_modifiers & 0x10) {
                    જો (prev_modifiers & 0x10) {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } નહીંતર {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                જો (changed_modifiers & 0x20) {
                    જો (prev_modifiers & 0x20) {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } નહીંતર {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                જો (changed_modifiers & 0x40) {
                    જો (prev_modifiers & 0x40) {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } નહીંતર {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                જો (changed_modifiers & 0x80) {
                    જો (prev_modifiers & 0x80) {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } નહીંતર {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[અંક_Reports - 1].modifiers[0];

            માટે (પૂર્ણાંક i = 0; i < 6; i++) {

                પૂર્ણાંક ચાવી_Code = k_reports[અંક_Reports - 1].keycodes[i];

                જો (ચાવી_Code != prev_ચાવીઓ[i]) {

                    જો (prev_ચાવીઓ[i]) {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, prev_ચાવીઓ[i], false);
                    }
                    જો (ચાવી_Code) {
                        SDL_Send_Keyboard_ચાવી(0, keyboardID, 0, ચાવી_Code, true);
                    }
                    prev_ચાવીઓ[i] = ચાવી_Code;
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA
