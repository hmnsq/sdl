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

स्थिर SDL_Scancode SDL_RISCOS_translate_keycode(पूर्णाङ्क keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    यदि (keycode < SDL_arraysize(riscos_scancode_table)) {
        scancode = riscos_scancode_table[keycode];

#ifdef DEBUG_SCANCODES
        यदि (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#endif
    }

    प्रत्यागम scancode;
}

शून्य RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    Uint8 कुंजी = 2;
    पूर्णाङ्क i;

    // Check for key releases
    प्रति (i = 0; i < RISCOS_MAX_कुंजियाँ_PRESSED; i++) {
        यदि (internal->कुंजी_pressed[i] != 255) {
            यदि ((_kernel_osbyte(129, internal->कुंजी_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_कुंजी(0, SDL_DEFAULT_KEYBOARD_ID, internal->कुंजी_pressed[i], SDL_RISCOS_translate_keycode(internal->कुंजी_pressed[i]), false);
                internal->कुंजी_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    यावत् (कुंजी < 0xff) {
        कुंजी = _kernel_osbyte(121, कुंजी + 1, 0) & 0xff;
        विकल्प (कुंजी) {
        पक्ष 255:
        // Ignore mouse keys
        पक्ष 9:
        पक्ष 10:
        पक्ष 11:
        // Ignore keys with multiple INKEY codes
        पक्ष 24:
        पक्ष 40:
        पक्ष 71:
        पक्ष 87:
            भङ्ग;

        स्वभाव:
            SDL_Send_Keyboard_कुंजी(0, SDL_DEFAULT_KEYBOARD_ID, कुंजी, SDL_RISCOS_translate_keycode(कुंजी), true);

            // Record the press so we can detect release later.
            प्रति (i = 0; i < RISCOS_MAX_कुंजियाँ_PRESSED; i++) {
                यदि (internal->कुंजी_pressed[i] == कुंजी) {
                    भङ्ग;
                }
                यदि (internal->कुंजी_pressed[i] == 255) {
                    internal->कुंजी_pressed[i] = कुंजी;
                    भङ्ग;
                }
            }
        }
    }
}

स्थिर ध्रुव Uint8 mouse_button_map[] = {
    SDL_BUTTON_दायाँ,
    SDL_BUTTON_मध्य,
    SDL_BUTTON_बायाँ,
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
    पूर्णाङ्क i, x, y, buttons;

    यदि (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        प्रत्यागम;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    यदि (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (भिन्न)x, (भिन्न)y);
    }

    यदि (internal->last_mouse_buttons != buttons) {
        प्रति (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
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
    पूर्णाङ्क i, status;

    प्रति (i = 0; i < RISCOS_MAX_कुंजियाँ_PRESSED; i++) {
        internal->कुंजी_pressed[i] = 255;
    }

    status = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_अंक, (status & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (status & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (status & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    internal->last_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    प्रत्यागम true;
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
