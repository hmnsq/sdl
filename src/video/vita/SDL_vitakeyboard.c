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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#അന്തര്ഭാവ <psp2/kernel/processmgr.h>
#അന്തര്ഭാവ <psp2/ctrl.h>
#അന്തര്ഭാവ <psp2/hid.h>

#അന്തര്ഭാവ "SDL_vitavideo.h"
#അന്തര്ഭാവ "SDL_vitakeyboard.h"
#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
പൂർണ്ണസംഖ്യ keyboard_hid_handle = 0;
Uint8 prev_താക്കോലുകൾ[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 lock_താക്കോൽ_down = 0;

ശൂന്യം VITA_InitKeyboard(ശൂന്യം)
{
#ifdef SDL_VIDEO_VITA_PVR
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#endif
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    എങ്കിൽ (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, ശൂന്യ);
    }
}

ശൂന്യം VITA_PollKeyboard(ശൂന്യം)
{
    // We skip polling keyboard if no window is created
    എങ്കിൽ (!Vita_Window) {
        തിരികെ;
    }

    എങ്കിൽ (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        പൂർണ്ണസംഖ്യ അക്കം_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        എങ്കിൽ (അക്കം_Reports < 0) {
            keyboard_hid_handle = 0;
        } അല്ലെങ്കിൽ എങ്കിൽ (അക്കം_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            എങ്കിൽ (k_reports[അക്കം_Reports - 1].modifiers[1] & 0x1) {
                എങ്കിൽ (!(locks & 0x1)) {
                    SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } അല്ലെങ്കിൽ {
                എങ്കിൽ (locks & 0x1) {
                    SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            എങ്കിൽ (k_reports[അക്കം_Reports - 1].modifiers[1] & 0x2) {
                എങ്കിൽ (!(locks & 0x2)) {
                    SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } അല്ലെങ്കിൽ {
                എങ്കിൽ (locks & 0x2) {
                    SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            എങ്കിൽ (k_reports[അക്കം_Reports - 1].modifiers[1] & 0x4) {
                എങ്കിൽ (!(locks & 0x4)) {
                    SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } അല്ലെങ്കിൽ {
                എങ്കിൽ (locks & 0x4) {
                    SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[അക്കം_Reports - 1].modifiers[0] ^ prev_modifiers;

                എങ്കിൽ (changed_modifiers & 0x01) {
                    എങ്കിൽ (prev_modifiers & 0x01) {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } അല്ലെങ്കിൽ {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                എങ്കിൽ (changed_modifiers & 0x02) {
                    എങ്കിൽ (prev_modifiers & 0x02) {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } അല്ലെങ്കിൽ {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                എങ്കിൽ (changed_modifiers & 0x04) {
                    എങ്കിൽ (prev_modifiers & 0x04) {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } അല്ലെങ്കിൽ {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                എങ്കിൽ (changed_modifiers & 0x08) {
                    എങ്കിൽ (prev_modifiers & 0x08) {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } അല്ലെങ്കിൽ {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                എങ്കിൽ (changed_modifiers & 0x10) {
                    എങ്കിൽ (prev_modifiers & 0x10) {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } അല്ലെങ്കിൽ {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                എങ്കിൽ (changed_modifiers & 0x20) {
                    എങ്കിൽ (prev_modifiers & 0x20) {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } അല്ലെങ്കിൽ {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                എങ്കിൽ (changed_modifiers & 0x40) {
                    എങ്കിൽ (prev_modifiers & 0x40) {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } അല്ലെങ്കിൽ {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                എങ്കിൽ (changed_modifiers & 0x80) {
                    എങ്കിൽ (prev_modifiers & 0x80) {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } അല്ലെങ്കിൽ {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[അക്കം_Reports - 1].modifiers[0];

            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 6; i++) {

                പൂർണ്ണസംഖ്യ താക്കോൽ_Code = k_reports[അക്കം_Reports - 1].keycodes[i];

                എങ്കിൽ (താക്കോൽ_Code != prev_താക്കോലുകൾ[i]) {

                    എങ്കിൽ (prev_താക്കോലുകൾ[i]) {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, prev_താക്കോലുകൾ[i], false);
                    }
                    എങ്കിൽ (താക്കോൽ_Code) {
                        SDL_Send_Keyboard_താക്കോൽ(0, keyboardID, 0, താക്കോൽ_Code, true);
                    }
                    prev_താക്കോലുകൾ[i] = താക്കോൽ_Code;
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA
