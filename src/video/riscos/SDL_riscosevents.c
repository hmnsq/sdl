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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_RISCOS

#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_riscosvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscosevents_c.h"
#ಅನ್ತರ್ಭಾವ "scancodes_riscos.h"

#ಅನ್ತರ್ಭಾವ <kernel.h>
#ಅನ್ತರ್ಭಾವ <swis.h>

ಸ್ಥಿರ SDL_Scancode SDL_RISCOS_translate_keycode(ಪೂರ್ಣಾಂಕ keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    ಆದರೆ (keycode < SDL_arraysize(riscos_scancode_ಕೋಷ್ಟಕ)) {
        scancode = riscos_scancode_ಕೋಷ್ಟಕ[keycode];

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_SCANCODES
        ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#ಆದರೆ_ಅಂತ್ಯ
    }

    ಹಿಂತಿರುಗಿ scancode;
}

ಶೂನ್ಯ RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ಆಂತರಿಕ = _this->ಆಂತರಿಕ;
    Uint8 ಕೀಲಿ = 2;
    ಪೂರ್ಣಾಂಕ i;

    // Check for key releases
    ಗಾಗಿ (i = 0; i < RISCOS_MAX_ಕೀಲಿಗಳು_PRESSED; i++) {
        ಆದರೆ (ಆಂತರಿಕ->ಕೀಲಿ_pressed[i] != 255) {
            ಆದರೆ ((_kernel_osbyte(129, ಆಂತರಿಕ->ಕೀಲಿ_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_ಕೀಲಿ(0, SDL_DEFAULT_KEYBOARD_ID, ಆಂತರಿಕ->ಕೀಲಿ_pressed[i], SDL_RISCOS_translate_keycode(ಆಂತರಿಕ->ಕೀಲಿ_pressed[i]), false);
                ಆಂತರಿಕ->ಕೀಲಿ_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    ಆಗ (ಕೀಲಿ < 0xff) {
        ಕೀಲಿ = _kernel_osbyte(121, ಕೀಲಿ + 1, 0) & 0xff;
        ಆಯ್ಕೆ (ಕೀಲಿ) {
        ಸ್ಥಿತಿ 255:
        // Ignore mouse keys
        ಸ್ಥಿತಿ 9:
        ಸ್ಥಿತಿ 10:
        ಸ್ಥಿತಿ 11:
        // Ignore keys with multiple INKEY codes
        ಸ್ಥಿತಿ 24:
        ಸ್ಥಿತಿ 40:
        ಸ್ಥಿತಿ 71:
        ಸ್ಥಿತಿ 87:
            ನಿಲ್ಲಿಸು;

        ಪೂರ್ವನಿಯೋಜಿತ:
            SDL_Send_Keyboard_ಕೀಲಿ(0, SDL_DEFAULT_KEYBOARD_ID, ಕೀಲಿ, SDL_RISCOS_translate_keycode(ಕೀಲಿ), true);

            // Record the press so we can detect release later.
            ಗಾಗಿ (i = 0; i < RISCOS_MAX_ಕೀಲಿಗಳು_PRESSED; i++) {
                ಆದರೆ (ಆಂತರಿಕ->ಕೀಲಿ_pressed[i] == ಕೀಲಿ) {
                    ನಿಲ್ಲಿಸು;
                }
                ಆದರೆ (ಆಂತರಿಕ->ಕೀಲಿ_pressed[i] == 255) {
                    ಆಂತರಿಕ->ಕೀಲಿ_pressed[i] = ಕೀಲಿ;
                    ನಿಲ್ಲಿಸು;
                }
            }
        }
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Uint8 mouse_button_map[] = {
    SDL_BUTTON_ಬಲ,
    SDL_BUTTON_ಮಧ್ಯ,
    SDL_BUTTON_ಎಡ,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

ಶೂನ್ಯ RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ಆಂತರಿಕ = _this->ಆಂತರಿಕ;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    ಪೂರ್ಣಾಂಕ i, x, y, buttons;

    ಆದರೆ (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        ಹಿಂತಿರುಗಿ;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    ಆದರೆ (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (ದಶಮಾಂಶ)x, (ದಶಮಾಂಶ)y);
    }

    ಆದರೆ (ಆಂತರಿಕ->ಕೊನೆಯ_mouse_buttons != buttons) {
        ಗಾಗಿ (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
            bool ಕೆಳಕ್ಕೆ = ((buttons & (1 << i)) != 0);
            SDL_SendMouseButton(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, mouse_button_map[i], ಕೆಳಕ್ಕೆ);
        }
        ಆಂತರಿಕ->ಕೊನೆಯ_mouse_buttons = buttons;
    }
}

bool RISCOS_InitEvents(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ಆಂತರಿಕ = _this->ಆಂತರಿಕ;
    _kernel_swi_regs regs;
    ಪೂರ್ಣಾಂಕ i, ಸ್ಥಿತಿ_2;

    ಗಾಗಿ (i = 0; i < RISCOS_MAX_ಕೀಲಿಗಳು_PRESSED; i++) {
        ಆಂತರಿಕ->ಕೀಲಿ_pressed[i] = 255;
    }

    ಸ್ಥಿತಿ_2 = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_ಅಂಕೆ, (ಸ್ಥಿತಿ_2 & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (ಸ್ಥಿತಿ_2 & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (ಸ್ಥಿತಿ_2 & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    ಆಂತರಿಕ->ಕೊನೆಯ_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ RISCOS_PumpEvents(SDL_VideoDevice *_this)
{
    RISCOS_PollMouse(_this);
    RISCOS_PollKeyboard(_this);
}

ಶೂನ್ಯ RISCOS_QuitEvents(SDL_VideoDevice *_this)
{
    // Re-enable escape.
    _kernel_osbyte(229, 0, 0);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_RISCOS
