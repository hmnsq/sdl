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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <psp2/hid.h>

#include "SDL_vitavideo.h"
#include "SDL_vitakeyboard.h"
#include "../../events/SDL_keyboard_c.h"

SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
จำนวนเต็ม keyboard_hid_handle = 0;
Uint8 prev_keys[6] = { 0 };
Uint8 prev_modifiers = 0;
Uint8 locks = 0;
Uint8 lock_key_down = 0;

void VITA_InitKeyboard(void)
{
#ifdef SDL_VIDEO_VITA_PVR
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME); /** For PVR OSK Support **/
#endif
    sceHidKeyboardEnumerate(&keyboard_hid_handle, 1);

    ถ้า (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, NULL);
    }
}

void VITA_PollKeyboard(void)
{
    // We skip polling keyboard if no window is created
    ถ้า (!Vita_Window) {
        คืน;
    }

    ถ้า (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        จำนวนเต็ม numReports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        ถ้า (numReports < 0) {
            keyboard_hid_handle = 0;
        } มิฉะนั้น ถ้า (numReports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            ถ้า (k_reports[numReports - 1].modifiers[1] & 0x1) {
                ถ้า (!(locks & 0x1)) {
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } มิฉะนั้น {
                ถ้า (locks & 0x1) {
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            ถ้า (k_reports[numReports - 1].modifiers[1] & 0x2) {
                ถ้า (!(locks & 0x2)) {
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } มิฉะนั้น {
                ถ้า (locks & 0x2) {
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            ถ้า (k_reports[numReports - 1].modifiers[1] & 0x4) {
                ถ้า (!(locks & 0x4)) {
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } มิฉะนั้น {
                ถ้า (locks & 0x4) {
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[numReports - 1].modifiers[0] ^ prev_modifiers;

                ถ้า (changed_modifiers & 0x01) {
                    ถ้า (prev_modifiers & 0x01) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } มิฉะนั้น {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                ถ้า (changed_modifiers & 0x02) {
                    ถ้า (prev_modifiers & 0x02) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } มิฉะนั้น {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                ถ้า (changed_modifiers & 0x04) {
                    ถ้า (prev_modifiers & 0x04) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } มิฉะนั้น {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                ถ้า (changed_modifiers & 0x08) {
                    ถ้า (prev_modifiers & 0x08) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } มิฉะนั้น {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                ถ้า (changed_modifiers & 0x10) {
                    ถ้า (prev_modifiers & 0x10) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } มิฉะนั้น {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                ถ้า (changed_modifiers & 0x20) {
                    ถ้า (prev_modifiers & 0x20) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } มิฉะนั้น {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                ถ้า (changed_modifiers & 0x40) {
                    ถ้า (prev_modifiers & 0x40) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } มิฉะนั้น {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                ถ้า (changed_modifiers & 0x80) {
                    ถ้า (prev_modifiers & 0x80) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } มิฉะนั้น {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[numReports - 1].modifiers[0];

            สำหรับ (จำนวนเต็ม i = 0; i < 6; i++) {

                จำนวนเต็ม keyCode = k_reports[numReports - 1].keycodes[i];

                ถ้า (keyCode != prev_keys[i]) {

                    ถ้า (prev_keys[i]) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, prev_keys[i], false);
                    }
                    ถ้า (keyCode) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, keyCode, true);
                    }
                    prev_keys[i] = keyCode;
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA
