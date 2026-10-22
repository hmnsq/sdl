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
ціле keyboard_hid_handle = 0;
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

    якщо (keyboard_hid_handle > 0) {
        SDL_AddKeyboard((SDL_KeyboardID)keyboard_hid_handle, NULL);
    }
}

void VITA_PollKeyboard(void)
{
    // We skip polling keyboard if no window is created
    якщо (!Vita_Window) {
        повернути;
    }

    якщо (keyboard_hid_handle > 0) {
        SDL_KeyboardID keyboardID = (SDL_KeyboardID)keyboard_hid_handle;
        ціле numReports = sceHidKeyboardRead(keyboard_hid_handle, (SceHidKeyboardReport **)&k_reports, SCE_HID_MAX_REPORT);

        якщо (numReports < 0) {
            keyboard_hid_handle = 0;
        } інакше якщо (numReports) {
            // Numlock and Capslock state changes only on a pressed event
            // The k_report only reports the state of the LED
            якщо (k_reports[numReports - 1].modifiers[1] & 0x1) {
                якщо (!(locks & 0x1)) {
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    locks |= 0x1;
                }
            } інакше {
                якщо (locks & 0x1) {
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, true);
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_NUMLOCKCLEAR, false);
                    locks &= ~0x1;
                }
            }

            якщо (k_reports[numReports - 1].modifiers[1] & 0x2) {
                якщо (!(locks & 0x2)) {
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    locks |= 0x2;
                }
            } інакше {
                якщо (locks & 0x2) {
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, true);
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_CAPSLOCK, false);
                    locks &= ~0x2;
                }
            }

            якщо (k_reports[numReports - 1].modifiers[1] & 0x4) {
                якщо (!(locks & 0x4)) {
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, true);
                    locks |= 0x4;
                }
            } інакше {
                якщо (locks & 0x4) {
                    SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_SCROLLLOCK, false);
                    locks &= ~0x4;
                }
            }

            {
                Uint8 changed_modifiers = k_reports[numReports - 1].modifiers[0] ^ prev_modifiers;

                якщо (changed_modifiers & 0x01) {
                    якщо (prev_modifiers & 0x01) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LCTRL, false);
                    } інакше {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LCTRL, true);
                    }
                }
                якщо (changed_modifiers & 0x02) {
                    якщо (prev_modifiers & 0x02) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, false);
                    } інакше {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LSHIFT, true);
                    }
                }
                якщо (changed_modifiers & 0x04) {
                    якщо (prev_modifiers & 0x04) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LALT, false);
                    } інакше {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LALT, true);
                    }
                }
                якщо (changed_modifiers & 0x08) {
                    якщо (prev_modifiers & 0x08) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LGUI, false);
                    } інакше {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_LGUI, true);
                    }
                }
                якщо (changed_modifiers & 0x10) {
                    якщо (prev_modifiers & 0x10) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RCTRL, false);
                    } інакше {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RCTRL, true);
                    }
                }
                якщо (changed_modifiers & 0x20) {
                    якщо (prev_modifiers & 0x20) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, false);
                    } інакше {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RSHIFT, true);
                    }
                }
                якщо (changed_modifiers & 0x40) {
                    якщо (prev_modifiers & 0x40) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RALT, false);
                    } інакше {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RALT, true);
                    }
                }
                якщо (changed_modifiers & 0x80) {
                    якщо (prev_modifiers & 0x80) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RGUI, false);
                    } інакше {
                        SDL_SendKeyboardKey(0, keyboardID, 0, SDL_SCANCODE_RGUI, true);
                    }
                }
            }

            prev_modifiers = k_reports[numReports - 1].modifiers[0];

            для (ціле i = 0; i < 6; i++) {

                ціле keyCode = k_reports[numReports - 1].keycodes[i];

                якщо (keyCode != prev_keys[i]) {

                    якщо (prev_keys[i]) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, prev_keys[i], false);
                    }
                    якщо (keyCode) {
                        SDL_SendKeyboardKey(0, keyboardID, 0, keyCode, true);
                    }
                    prev_keys[i] = keyCode;
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA
