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
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#ضمن "../../events/SDL_events_c.h"

#ضمن "SDL_riscosvideo.h"
#ضمن "SDL_riscosevents_c.h"
#ضمن "scancodes_riscos.h"

#ضمن <kernel.h>
#ضمن <swis.h>

ساكن SDL_Scancode SDL_RISCOS_translate_keycode(صحيح keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    إذا (keycode < SDL_arraysize(riscos_scancode_table)) {
        scancode = riscos_scancode_table[keycode];

#ifdef DEBUG_SCANCODES
        إذا (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#endif
    }

    أرجع scancode;
}

فراغ RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    Uint8 کلید = 2;
    صحيح i;

    // Check for key releases
    لكل (i = 0; i < RISCOS_MAX_کلیدیں_PRESSED; i++) {
        إذا (internal->کلید_pressed[i] != 255) {
            إذا ((_kernel_osbyte(129, internal->کلید_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_کلید(0, SDL_DEFAULT_KEYBOARD_ID, internal->کلید_pressed[i], SDL_RISCOS_translate_keycode(internal->کلید_pressed[i]), false);
                internal->کلید_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    طالما (کلید < 0xff) {
        کلید = _kernel_osbyte(121, کلید + 1, 0) & 0xff;
        بدل (کلید) {
        حالة 255:
        // Ignore mouse keys
        حالة 9:
        حالة 10:
        حالة 11:
        // Ignore keys with multiple INKEY codes
        حالة 24:
        حالة 40:
        حالة 71:
        حالة 87:
            اكسر;

        افتراضي:
            SDL_Send_Keyboard_کلید(0, SDL_DEFAULT_KEYBOARD_ID, کلید, SDL_RISCOS_translate_keycode(کلید), true);

            // Record the press so we can detect release later.
            لكل (i = 0; i < RISCOS_MAX_کلیدیں_PRESSED; i++) {
                إذا (internal->کلید_pressed[i] == کلید) {
                    اكسر;
                }
                إذا (internal->کلید_pressed[i] == 255) {
                    internal->کلید_pressed[i] = کلید;
                    اكسر;
                }
            }
        }
    }
}

ساكن ثابت Uint8 mouse_button_map[] = {
    SDL_BUTTON_دایاں,
    SDL_BUTTON_درمیان,
    SDL_BUTTON_بایاں,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

فراغ RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    صحيح i, x, y, buttons;

    إذا (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        أرجع;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    إذا (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (عائم)x, (عائم)y);
    }

    إذا (internal->last_mouse_buttons != buttons) {
        لكل (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
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
    صحيح i, status;

    لكل (i = 0; i < RISCOS_MAX_کلیدیں_PRESSED; i++) {
        internal->کلید_pressed[i] = 255;
    }

    status = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_عدد, (status & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (status & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (status & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    internal->last_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    أرجع true;
}

فراغ RISCOS_PumpEvents(SDL_VideoDevice *_this)
{
    RISCOS_PollMouse(_this);
    RISCOS_PollKeyboard(_this);
}

فراغ RISCOS_QuitEvents(SDL_VideoDevice *_this)
{
    // Re-enable escape.
    _kernel_osbyte(229, 0, 0);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
