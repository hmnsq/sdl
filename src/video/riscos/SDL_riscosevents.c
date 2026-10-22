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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#অন্তর্ভাব "../../events/SDL_events_c.h"

#অন্তর্ভাব "SDL_riscosvideo.h"
#অন্তর্ভাব "SDL_riscosevents_c.h"
#অন্তর্ভাব "scancodes_riscos.h"

#অন্তর্ভাব <kernel.h>
#অন্তর্ভাব <swis.h>

স্থির SDL_Scancode SDL_RISCOS_translate_keycode(পূর্ণাঙ্ক keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    যদি (keycode < SDL_arraysize(riscos_scancode_table)) {
        scancode = riscos_scancode_table[keycode];

#ifdef DEBUG_SCANCODES
        যদি (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#endif
    }

    প্রত্যাগম scancode;
}

শূন্য RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    Uint8 চাবি = 2;
    পূর্ণাঙ্ক i;

    // Check for key releases
    প্রতি (i = 0; i < RISCOS_MAX_চাবিগুলি_PRESSED; i++) {
        যদি (internal->চাবি_pressed[i] != 255) {
            যদি ((_kernel_osbyte(129, internal->চাবি_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_চাবি(0, SDL_DEFAULT_KEYBOARD_ID, internal->চাবি_pressed[i], SDL_RISCOS_translate_keycode(internal->চাবি_pressed[i]), false);
                internal->চাবি_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    যাবত্ (চাবি < 0xff) {
        চাবি = _kernel_osbyte(121, চাবি + 1, 0) & 0xff;
        বিকল্প (চাবি) {
        পক্ষ 255:
        // Ignore mouse keys
        পক্ষ 9:
        পক্ষ 10:
        পক্ষ 11:
        // Ignore keys with multiple INKEY codes
        পক্ষ 24:
        পক্ষ 40:
        পক্ষ 71:
        পক্ষ 87:
            ভঙ্গ;

        স্বভাব:
            SDL_Send_Keyboard_চাবি(0, SDL_DEFAULT_KEYBOARD_ID, চাবি, SDL_RISCOS_translate_keycode(চাবি), true);

            // Record the press so we can detect release later.
            প্রতি (i = 0; i < RISCOS_MAX_চাবিগুলি_PRESSED; i++) {
                যদি (internal->চাবি_pressed[i] == চাবি) {
                    ভঙ্গ;
                }
                যদি (internal->চাবি_pressed[i] == 255) {
                    internal->চাবি_pressed[i] = চাবি;
                    ভঙ্গ;
                }
            }
        }
    }
}

স্থির ধ্রুব Uint8 mouse_button_map[] = {
    SDL_BUTTON_ডান,
    SDL_BUTTON_মধ্য,
    SDL_BUTTON_বাম,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

শূন্য RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    পূর্ণাঙ্ক i, x, y, buttons;

    যদি (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        প্রত্যাগম;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    যদি (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (ভিন্ন)x, (ভিন্ন)y);
    }

    যদি (internal->last_mouse_buttons != buttons) {
        প্রতি (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
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
    পূর্ণাঙ্ক i, status;

    প্রতি (i = 0; i < RISCOS_MAX_চাবিগুলি_PRESSED; i++) {
        internal->চাবি_pressed[i] = 255;
    }

    status = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_অঙ্ক, (status & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (status & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (status & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    internal->last_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    প্রত্যাগম true;
}

শূন্য RISCOS_PumpEvents(SDL_VideoDevice *_this)
{
    RISCOS_PollMouse(_this);
    RISCOS_PollKeyboard(_this);
}

শূন্য RISCOS_QuitEvents(SDL_VideoDevice *_this)
{
    // Re-enable escape.
    _kernel_osbyte(229, 0, 0);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
