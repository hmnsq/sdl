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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#अन्तर्भाव "../../events/SDL_events_c.h"

#अन्तर्भाव "SDL_riscosvideo.h"
#अन्तर्भाव "SDL_riscosevents_c.h"
#अन्तर्भाव "scancodes_riscos.h"

#अन्तर्भाव <kernel.h>
#अन्तर्भाव <swis.h>

स्थिर SDL_Scancode SDL_RISCOS_translate_keycode(पूर्णांक keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    जर (keycode < SDL_arraysize(riscos_scancode_table)) {
        scancode = riscos_scancode_table[keycode];

#ifdef DEBUG_SCANCODES
        जर (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#endif
    }

    परत scancode;
}

शून्य RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    Uint8 किल्ली = 2;
    पूर्णांक i;

    // Check for key releases
    साठी (i = 0; i < RISCOS_MAX_किल्ल्या_PRESSED; i++) {
        जर (internal->किल्ली_pressed[i] != 255) {
            जर ((_kernel_osbyte(129, internal->किल्ली_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_किल्ली(0, SDL_DEFAULT_KEYBOARD_ID, internal->किल्ली_pressed[i], SDL_RISCOS_translate_keycode(internal->किल्ली_pressed[i]), false);
                internal->किल्ली_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    पर्यंत (किल्ली < 0xff) {
        किल्ली = _kernel_osbyte(121, किल्ली + 1, 0) & 0xff;
        निवड (किल्ली) {
        स्थिती 255:
        // Ignore mouse keys
        स्थिती 9:
        स्थिती 10:
        स्थिती 11:
        // Ignore keys with multiple INKEY codes
        स्थिती 24:
        स्थिती 40:
        स्थिती 71:
        स्थिती 87:
            थांबा;

        पूर्वनिर्धारित:
            SDL_Send_Keyboard_किल्ली(0, SDL_DEFAULT_KEYBOARD_ID, किल्ली, SDL_RISCOS_translate_keycode(किल्ली), true);

            // Record the press so we can detect release later.
            साठी (i = 0; i < RISCOS_MAX_किल्ल्या_PRESSED; i++) {
                जर (internal->किल्ली_pressed[i] == किल्ली) {
                    थांबा;
                }
                जर (internal->किल्ली_pressed[i] == 255) {
                    internal->किल्ली_pressed[i] = किल्ली;
                    थांबा;
                }
            }
        }
    }
}

स्थिर स्थिरांक Uint8 mouse_button_map[] = {
    SDL_BUTTON_उजवा,
    SDL_BUTTON_मधला,
    SDL_BUTTON_डावा,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

शून्य RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    पूर्णांक i, x, y, buttons;

    जर (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        परत;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    जर (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (दशांश)x, (दशांश)y);
    }

    जर (internal->last_mouse_buttons != buttons) {
        साठी (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
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
    पूर्णांक i, status;

    साठी (i = 0; i < RISCOS_MAX_किल्ल्या_PRESSED; i++) {
        internal->किल्ली_pressed[i] = 255;
    }

    status = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_अंक, (status & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (status & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (status & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    internal->last_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    परत true;
}

शून्य RISCOS_PumpEvents(SDL_VideoDevice *_this)
{
    RISCOS_PollMouse(_this);
    RISCOS_PollKeyboard(_this);
}

शून्य RISCOS_QuitEvents(SDL_VideoDevice *_this)
{
    // Re-enable escape.
    _kernel_osbyte(229, 0, 0);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
