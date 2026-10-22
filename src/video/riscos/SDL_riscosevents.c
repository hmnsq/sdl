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
#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#شامل "../../events/SDL_events_c.h"

#شامل "SDL_riscosvideo.h"
#شامل "SDL_riscosevents_c.h"
#شامل "scancodes_riscos.h"

#شامل <kernel.h>
#شامل <swis.h>

ایستا SDL_Scancode SDL_RISCOS_translate_keycode(صحیح keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    اگر (keycode < SDL_arraysize(riscos_scancode_table)) {
        scancode = riscos_scancode_table[keycode];

#ifdef DEBUG_SCANCODES
        اگر (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#endif
    }

    بازگشت scancode;
}

تهی RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    Uint8 کلید = 2;
    صحیح i;

    // Check for key releases
    برای (i = 0; i < RISCOS_MAX_کلیدها_PRESSED; i++) {
        اگر (internal->کلید_pressed[i] != 255) {
            اگر ((_kernel_osbyte(129, internal->کلید_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_کلید(0, SDL_DEFAULT_KEYBOARD_ID, internal->کلید_pressed[i], SDL_RISCOS_translate_keycode(internal->کلید_pressed[i]), false);
                internal->کلید_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    وقتی (کلید < 0xff) {
        کلید = _kernel_osbyte(121, کلید + 1, 0) & 0xff;
        انتخاب (کلید) {
        حالت 255:
        // Ignore mouse keys
        حالت 9:
        حالت 10:
        حالت 11:
        // Ignore keys with multiple INKEY codes
        حالت 24:
        حالت 40:
        حالت 71:
        حالت 87:
            بشکن;

        پیشفرض:
            SDL_Send_Keyboard_کلید(0, SDL_DEFAULT_KEYBOARD_ID, کلید, SDL_RISCOS_translate_keycode(کلید), true);

            // Record the press so we can detect release later.
            برای (i = 0; i < RISCOS_MAX_کلیدها_PRESSED; i++) {
                اگر (internal->کلید_pressed[i] == کلید) {
                    بشکن;
                }
                اگر (internal->کلید_pressed[i] == 255) {
                    internal->کلید_pressed[i] = کلید;
                    بشکن;
                }
            }
        }
    }
}

ایستا ثابت Uint8 mouse_button_map[] = {
    SDL_BUTTON_راست,
    SDL_BUTTON_میانه,
    SDL_BUTTON_چپ,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

تهی RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    صحیح i, x, y, buttons;

    اگر (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        بازگشت;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    اگر (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (اعشاری)x, (اعشاری)y);
    }

    اگر (internal->last_mouse_buttons != buttons) {
        برای (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
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
    صحیح i, status;

    برای (i = 0; i < RISCOS_MAX_کلیدها_PRESSED; i++) {
        internal->کلید_pressed[i] = 255;
    }

    status = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_رقم, (status & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (status & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (status & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    internal->last_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    بازگشت true;
}

تهی RISCOS_PumpEvents(SDL_VideoDevice *_this)
{
    RISCOS_PollMouse(_this);
    RISCOS_PollKeyboard(_this);
}

تهی RISCOS_QuitEvents(SDL_VideoDevice *_this)
{
    // Re-enable escape.
    _kernel_osbyte(229, 0, 0);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
