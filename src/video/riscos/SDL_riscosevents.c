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

    ܐܢ (keycode < SDL_arraysize(riscos_scancode_table)) {
        scancode = riscos_scancode_table[keycode];

#ifdef DEBUG_SCANCODES
        ܐܢ (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#endif
    }

    ܦܢܐ scancode;
}

فراغ RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    Uint8 key = 2;
    صحيح i;

    // Check for key releases
    لكل (i = 0; i < RISCOS_MAX_KEYS_PRESSED; i++) {
        ܐܢ (internal->key_pressed[i] != 255) {
            ܐܢ ((_kernel_osbyte(129, internal->key_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_SendKeyboardKey(0, SDL_DEFAULT_KEYBOARD_ID, internal->key_pressed[i], SDL_RISCOS_translate_keycode(internal->key_pressed[i]), false);
                internal->key_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    ܟܡܐ (key < 0xff) {
        key = _kernel_osbyte(121, key + 1, 0) & 0xff;
        بدل (key) {
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
            SDL_SendKeyboardKey(0, SDL_DEFAULT_KEYBOARD_ID, key, SDL_RISCOS_translate_keycode(key), true);

            // Record the press so we can detect release later.
            لكل (i = 0; i < RISCOS_MAX_KEYS_PRESSED; i++) {
                ܐܢ (internal->key_pressed[i] == key) {
                    اكسر;
                }
                ܐܢ (internal->key_pressed[i] == 255) {
                    internal->key_pressed[i] = key;
                    اكسر;
                }
            }
        }
    }
}

ساكن ثابت Uint8 mouse_button_map[] = {
    SDL_BUTTON_RIGHT,
    SDL_BUTTON_MIDDLE,
    SDL_BUTTON_LEFT,
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

    ܐܢ (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        ܦܢܐ;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    ܐܢ (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (عائم)x, (عائم)y);
    }

    ܐܢ (internal->last_mouse_buttons != buttons) {
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

    لكل (i = 0; i < RISCOS_MAX_KEYS_PRESSED; i++) {
        internal->key_pressed[i] = 255;
    }

    status = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_NUM, (status & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (status & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (status & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    internal->last_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    ܦܢܐ true;
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
