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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"

#ଅନ୍ତର୍ଭାଵ "SDL_riscosvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_riscosevents_c.h"
#ଅନ୍ତର୍ଭାଵ "scancodes_riscos.h"

#ଅନ୍ତର୍ଭାଵ <kernel.h>
#ଅନ୍ତର୍ଭାଵ <swis.h>

ସ୍ଥିର SDL_Scancode SDL_RISCOS_translate_keycode(ପୂର୍ଣ୍ଣସଂଖ୍ୟା keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    ଯଦି (keycode < SDL_arraysize(riscos_scancode_table)) {
        scancode = riscos_scancode_table[keycode];

#ifdef DEBUG_SCANCODES
        ଯଦି (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#endif
    }

    ଫେରନ୍ତୁ scancode;
}

ଶୂନ୍ୟ RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    Uint8 ଚାବି = 2;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    // Check for key releases
    ପାଇଁ (i = 0; i < RISCOS_MAX_ଚାବିଗୁଡ଼ିକ_PRESSED; i++) {
        ଯଦି (internal->ଚାବି_pressed[i] != 255) {
            ଯଦି ((_kernel_osbyte(129, internal->ଚାବି_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_ଚାବି(0, SDL_DEFAULT_KEYBOARD_ID, internal->ଚାବି_pressed[i], SDL_RISCOS_translate_keycode(internal->ଚାବି_pressed[i]), false);
                internal->ଚାବି_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    ଯେତେବେଳେ (ଚାବି < 0xff) {
        ଚାବି = _kernel_osbyte(121, ଚାବି + 1, 0) & 0xff;
        ବାଛ (ଚାବି) {
        ସ୍ଥିତି 255:
        // Ignore mouse keys
        ସ୍ଥିତି 9:
        ସ୍ଥିତି 10:
        ସ୍ଥିତି 11:
        // Ignore keys with multiple INKEY codes
        ସ୍ଥିତି 24:
        ସ୍ଥିତି 40:
        ସ୍ଥିତି 71:
        ସ୍ଥିତି 87:
            ଭାଙ୍ଗ;

        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            SDL_Send_Keyboard_ଚାବି(0, SDL_DEFAULT_KEYBOARD_ID, ଚାବି, SDL_RISCOS_translate_keycode(ଚାବି), true);

            // Record the press so we can detect release later.
            ପାଇଁ (i = 0; i < RISCOS_MAX_ଚାବିଗୁଡ଼ିକ_PRESSED; i++) {
                ଯଦି (internal->ଚାବି_pressed[i] == ଚାବି) {
                    ଭାଙ୍ଗ;
                }
                ଯଦି (internal->ଚାବି_pressed[i] == 255) {
                    internal->ଚାବି_pressed[i] = ଚାବି;
                    ଭାଙ୍ଗ;
                }
            }
        }
    }
}

ସ୍ଥିର ଅଚଳ Uint8 mouse_button_map[] = {
    SDL_BUTTON_ଡାହାଣ,
    SDL_BUTTON_ମଧ୍ୟ,
    SDL_BUTTON_ବାମ,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

ଶୂନ୍ୟ RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, x, y, buttons;

    ଯଦି (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        ଫେରନ୍ତୁ;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    ଯଦି (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (ଦଶମିକ)x, (ଦଶମିକ)y);
    }

    ଯଦି (internal->last_mouse_buttons != buttons) {
        ପାଇଁ (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
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
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, status;

    ପାଇଁ (i = 0; i < RISCOS_MAX_ଚାବିଗୁଡ଼ିକ_PRESSED; i++) {
        internal->ଚାବି_pressed[i] = 255;
    }

    status = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_ଅଙ୍କ, (status & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (status & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (status & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    internal->last_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ RISCOS_PumpEvents(SDL_VideoDevice *_this)
{
    RISCOS_PollMouse(_this);
    RISCOS_PollKeyboard(_this);
}

ଶୂନ୍ୟ RISCOS_QuitEvents(SDL_VideoDevice *_this)
{
    // Re-enable escape.
    _kernel_osbyte(229, 0, 0);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
