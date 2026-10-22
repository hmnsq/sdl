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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_VITA

#समावेश <psp2/kernel/processmgr.h>
#समावेश <psp2/ctrl.h>
#समावेश <psp2/hid.h>

#समावेश "SDL_vitavideo.h"
#समावेश "SDL_vitakeyboard.h"
#समावेश "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
पूर्णांक keyboard_hid_handle = 0;
Uint8 पूर्व_कुंजियाँ[6] = { 0 };
Uint8 पूर्व_modifiers = 0;
Uint8 locks = 0;
Uint8 lock_कुंजी_down = 0;

व्योम VITA_InitKeyboard(व्योम)
{
#अगर_घोषित SDL_VIDEO_VITA_PVR
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#पूर्ण_अगर
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    अगर (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, शून्य);
    }
}

व्योम VITA_PollKeyboard(व्योम)
{
    // We skip polling keyboard if no window is created
    अगर (!Vita_Window) {
        वापस;
    }

    अगर (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        पूर्णांक अंक_Reports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        अगर (अंक_Reports < 0) {
            keyboard_hid_handle = 0;
        } अन्यथा अगर (अंक_Reports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            अगर (k_reports[अंक_Reports - 1].modifiers[1] & 0x1) {
                अगर (!(locks & 0x1)) {
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } अन्यथा {
                अगर (locks & 0x1) {
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            अगर (k_reports[अंक_Reports - 1].modifiers[1] & 0x2) {
                अगर (!(locks & 0x2)) {
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } अन्यथा {
                अगर (locks & 0x2) {
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            अगर (k_reports[अंक_Reports - 1].modifiers[1] & 0x4) {
                अगर (!(locks & 0x4)) {
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } अन्यथा {
                अगर (locks & 0x4) {
                    SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[अंक_Reports - 1].modifiers[0] ^ पूर्व_modifiers;

                अगर (changed_modifiers & 0x01) {
                    अगर (पूर्व_modifiers & 0x01) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                अगर (changed_modifiers & 0x02) {
                    अगर (पूर्व_modifiers & 0x02) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                अगर (changed_modifiers & 0x04) {
                    अगर (पूर्व_modifiers & 0x04) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                अगर (changed_modifiers & 0x08) {
                    अगर (पूर्व_modifiers & 0x08) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                अगर (changed_modifiers & 0x10) {
                    अगर (पूर्व_modifiers & 0x10) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                अगर (changed_modifiers & 0x20) {
                    अगर (पूर्व_modifiers & 0x20) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                अगर (changed_modifiers & 0x40) {
                    अगर (पूर्व_modifiers & 0x40) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                अगर (changed_modifiers & 0x80) {
                    अगर (पूर्व_modifiers & 0x80) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } अन्यथा {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            पूर्व_modifiers = k_reports[अंक_Reports - 1].modifiers[0];

            क्रम (पूर्णांक i = 0; i < 6; i++) {

                पूर्णांक कुंजी_Code = k_reports[अंक_Reports - 1].keycodes[i];

                अगर (कुंजी_Code != पूर्व_कुंजियाँ[i]) {

                    अगर (पूर्व_कुंजियाँ[i]) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, पूर्व_कुंजियाँ[i], false);
                    }
                    अगर (कुंजी_Code) {
                        SDL_Send_Keyboard_कुंजी(0, keyboardID, 0, कुंजी_Code, true);
                    }
                    पूर्व_कुंजियाँ[i] = कुंजी_Code;
                }
            }
        }
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_VITA
