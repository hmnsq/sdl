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

#ifdef SDL_VIDEO_DRIVER_RISCOS

#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_riscosvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscosevents_c.h"
#ಅನ್ತರ್ಭಾವ "scancodes_riscos.h"

#ಅನ್ತರ್ಭಾವ <kernel.h>
#ಅನ್ತರ್ಭಾವ <swis.h>

ಸ್ಥಿರ SDL_Scancode SDL_RISCOS_translate_keycode(ಪೂರ್ಣಾಙ್ಕ keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    ಯದಿ (keycode < SDL_arraysize(riscos_scancode_table)) {
        scancode = riscos_scancode_table[keycode];

#ifdef DEBUG_SCANCODES
        ಯದಿ (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#endif
    }

    ಪ್ರತ್ಯಾಗಮ scancode;
}

ಶೂನ್ಯ RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    Uint8 ಕೀಲಿ = 2;
    ಪೂರ್ಣಾಙ್ಕ i;

    // Check for key releases
    ಪ್ರತಿ (i = 0; i < RISCOS_MAX_ಕೀಲಿಗಳು_PRESSED; i++) {
        ಯದಿ (internal->ಕೀಲಿ_pressed[i] != 255) {
            ಯದಿ ((_kernel_osbyte(129, internal->ಕೀಲಿ_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_ಕೀಲಿ(0, SDL_DEFAULT_KEYBOARD_ID, internal->ಕೀಲಿ_pressed[i], SDL_RISCOS_translate_keycode(internal->ಕೀಲಿ_pressed[i]), false);
                internal->ಕೀಲಿ_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    ಯಾವತ್ (ಕೀಲಿ < 0xff) {
        ಕೀಲಿ = _kernel_osbyte(121, ಕೀಲಿ + 1, 0) & 0xff;
        ವಿಕಲ್ಪ (ಕೀಲಿ) {
        ಪಕ್ಷ 255:
        // Ignore mouse keys
        ಪಕ್ಷ 9:
        ಪಕ್ಷ 10:
        ಪಕ್ಷ 11:
        // Ignore keys with multiple INKEY codes
        ಪಕ್ಷ 24:
        ಪಕ್ಷ 40:
        ಪಕ್ಷ 71:
        ಪಕ್ಷ 87:
            ಭಙ್ಗ;

        ಸ್ವಭಾವ:
            SDL_Send_Keyboard_ಕೀಲಿ(0, SDL_DEFAULT_KEYBOARD_ID, ಕೀಲಿ, SDL_RISCOS_translate_keycode(ಕೀಲಿ), true);

            // Record the press so we can detect release later.
            ಪ್ರತಿ (i = 0; i < RISCOS_MAX_ಕೀಲಿಗಳು_PRESSED; i++) {
                ಯದಿ (internal->ಕೀಲಿ_pressed[i] == ಕೀಲಿ) {
                    ಭಙ್ಗ;
                }
                ಯದಿ (internal->ಕೀಲಿ_pressed[i] == 255) {
                    internal->ಕೀಲಿ_pressed[i] = ಕೀಲಿ;
                    ಭಙ್ಗ;
                }
            }
        }
    }
}

ಸ್ಥಿರ ಧ್ರುವ Uint8 mouse_button_map[] = {
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
    SDL_VideoData *internal = _this->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    ಪೂರ್ಣಾಙ್ಕ i, x, y, buttons;

    ಯದಿ (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    ಯದಿ (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (ಭಿನ್ನ)x, (ಭಿನ್ನ)y);
    }

    ಯದಿ (internal->last_mouse_buttons != buttons) {
        ಪ್ರತಿ (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
            bool down = ((buttons & (1 << i)) != 0);
            SDL_SendMouseButton(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, mouse_button_map[i], down);
        }
        internal->last_mouse_buttons = buttons;
    }
}

bool RISCOS_InitEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    _kernel_swi_regs regs;
    ಪೂರ್ಣಾಙ್ಕ i, status;

    ಪ್ರತಿ (i = 0; i < RISCOS_MAX_ಕೀಲಿಗಳು_PRESSED; i++) {
        internal->ಕೀಲಿ_pressed[i] = 255;
    }

    status = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_ಅಂಕೆ, (status & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (status & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (status & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    internal->last_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    ಪ್ರತ್ಯಾಗಮ true;
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

#endif // SDL_VIDEO_DRIVER_RISCOS
