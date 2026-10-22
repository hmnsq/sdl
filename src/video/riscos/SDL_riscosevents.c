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

#ifdef SDL_VIDEO_DRIVER_RISCOS

#அந்தர்பாவ "../../events/SDL_events_c.h"

#அந்தர்பாவ "SDL_riscosvideo.h"
#அந்தர்பாவ "SDL_riscosevents_c.h"
#அந்தர்பாவ "scancodes_riscos.h"

#அந்தர்பாவ <kernel.h>
#அந்தர்பாவ <swis.h>

நிலையான SDL_Scancode SDL_RISCOS_translate_keycode(முழு keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    எனில் (keycode < SDL_arraysize(riscos_scancode_table)) {
        scancode = riscos_scancode_table[keycode];

#ifdef DEBUG_SCANCODES
        எனில் (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#endif
    }

    திரும்பு scancode;
}

வெறுமை RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    Uint8 சாவி = 2;
    முழு i;

    // Check for key releases
    க்கு (i = 0; i < RISCOS_MAX_சாவிகள்_PRESSED; i++) {
        எனில் (internal->சாவி_pressed[i] != 255) {
            எனில் ((_kernel_osbyte(129, internal->சாவி_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_சாவி(0, SDL_DEFAULT_KEYBOARD_ID, internal->சாவி_pressed[i], SDL_RISCOS_translate_keycode(internal->சாவி_pressed[i]), false);
                internal->சாவி_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    போது (சாவி < 0xff) {
        சாவி = _kernel_osbyte(121, சாவி + 1, 0) & 0xff;
        தேர்வு (சாவி) {
        நிலை 255:
        // Ignore mouse keys
        நிலை 9:
        நிலை 10:
        நிலை 11:
        // Ignore keys with multiple INKEY codes
        நிலை 24:
        நிலை 40:
        நிலை 71:
        நிலை 87:
            நிறுத்து;

        இயல்பு:
            SDL_Send_Keyboard_சாவி(0, SDL_DEFAULT_KEYBOARD_ID, சாவி, SDL_RISCOS_translate_keycode(சாவி), true);

            // Record the press so we can detect release later.
            க்கு (i = 0; i < RISCOS_MAX_சாவிகள்_PRESSED; i++) {
                எனில் (internal->சாவி_pressed[i] == சாவி) {
                    நிறுத்து;
                }
                எனில் (internal->சாவி_pressed[i] == 255) {
                    internal->சாவி_pressed[i] = சாவி;
                    நிறுத்து;
                }
            }
        }
    }
}

நிலையான மாறிலி Uint8 mouse_button_map[] = {
    SDL_BUTTON_வலது,
    SDL_BUTTON_நடு,
    SDL_BUTTON_இடது,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

வெறுமை RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    முழு i, x, y, buttons;

    எனில் (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        திரும்பு;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    எனில் (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (தசம)x, (தசம)y);
    }

    எனில் (internal->last_mouse_buttons != buttons) {
        க்கு (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
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
    முழு i, status;

    க்கு (i = 0; i < RISCOS_MAX_சாவிகள்_PRESSED; i++) {
        internal->சாவி_pressed[i] = 255;
    }

    status = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_இலக்கம், (status & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (status & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (status & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    internal->last_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    திரும்பு true;
}

வெறுமை RISCOS_PumpEvents(SDL_VideoDevice *_this)
{
    RISCOS_PollMouse(_this);
    RISCOS_PollKeyboard(_this);
}

வெறுமை RISCOS_QuitEvents(SDL_VideoDevice *_this)
{
    // Re-enable escape.
    _kernel_osbyte(229, 0, 0);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
