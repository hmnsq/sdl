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

#ifdef SDL_VIDEO_DRIVER_RISCOS

#અન્તર્ભાવ "../../events/SDL_events_c.h"

#અન્તર્ભાવ "SDL_riscosvideo.h"
#અન્તર્ભાવ "SDL_riscosevents_c.h"
#અન્તર્ભાવ "scancodes_riscos.h"

#અન્તર્ભાવ <kernel.h>
#અન્તર્ભાવ <swis.h>

સ્થિર SDL_Scancode SDL_RISCOS_translate_keycode(પૂર્ણાંક keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    જો (keycode < SDL_arraysize(riscos_scancode_table)) {
        scancode = riscos_scancode_table[keycode];

#ifdef DEBUG_SCANCODES
        જો (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#endif
    }

    પાછા scancode;
}

શૂન્ય RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    Uint8 ચાવી = 2;
    પૂર્ણાંક i;

    // Check for key releases
    માટે (i = 0; i < RISCOS_MAX_ચાવીઓ_PRESSED; i++) {
        જો (internal->ચાવી_pressed[i] != 255) {
            જો ((_kernel_osbyte(129, internal->ચાવી_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_ચાવી(0, SDL_DEFAULT_KEYBOARD_ID, internal->ચાવી_pressed[i], SDL_RISCOS_translate_keycode(internal->ચાવી_pressed[i]), false);
                internal->ચાવી_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    જ્યારે (ચાવી < 0xff) {
        ચાવી = _kernel_osbyte(121, ચાવી + 1, 0) & 0xff;
        પસંદગી (ચાવી) {
        સ્થિતિ 255:
        // Ignore mouse keys
        સ્થિતિ 9:
        સ્થિતિ 10:
        સ્થિતિ 11:
        // Ignore keys with multiple INKEY codes
        સ્થિતિ 24:
        સ્થિતિ 40:
        સ્થિતિ 71:
        સ્થિતિ 87:
            તોડો;

        મૂળભૂત:
            SDL_Send_Keyboard_ચાવી(0, SDL_DEFAULT_KEYBOARD_ID, ચાવી, SDL_RISCOS_translate_keycode(ચાવી), true);

            // Record the press so we can detect release later.
            માટે (i = 0; i < RISCOS_MAX_ચાવીઓ_PRESSED; i++) {
                જો (internal->ચાવી_pressed[i] == ચાવી) {
                    તોડો;
                }
                જો (internal->ચાવી_pressed[i] == 255) {
                    internal->ચાવી_pressed[i] = ચાવી;
                    તોડો;
                }
            }
        }
    }
}

સ્થિર અચલ Uint8 mouse_button_map[] = {
    SDL_BUTTON_જમણું,
    SDL_BUTTON_મધ્ય,
    SDL_BUTTON_ડાબું,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

શૂન્ય RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    પૂર્ણાંક i, x, y, buttons;

    જો (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        પાછા;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    જો (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (દશાંશ)x, (દશાંશ)y);
    }

    જો (internal->last_mouse_buttons != buttons) {
        માટે (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
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
    પૂર્ણાંક i, status;

    માટે (i = 0; i < RISCOS_MAX_ચાવીઓ_PRESSED; i++) {
        internal->ચાવી_pressed[i] = 255;
    }

    status = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_અંક, (status & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (status & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (status & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    internal->last_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    પાછા true;
}

શૂન્ય RISCOS_PumpEvents(SDL_VideoDevice *_this)
{
    RISCOS_PollMouse(_this);
    RISCOS_PollKeyboard(_this);
}

શૂન્ય RISCOS_QuitEvents(SDL_VideoDevice *_this)
{
    // Re-enable escape.
    _kernel_osbyte(229, 0, 0);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
