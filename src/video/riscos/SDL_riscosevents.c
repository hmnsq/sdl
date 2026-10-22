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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_RISCOS

#अन्तर्भाव "../../events/SDL_events_c.h"

#अन्तर्भाव "SDL_riscosvideo.h"
#अन्तर्भाव "SDL_riscosevents_c.h"
#अन्तर्भाव "scancodes_riscos.h"

#अन्तर्भाव <kernel.h>
#अन्तर्भाव <swis.h>

स्थिर SDL_Scancode SDL_RISCOS_translate_keycode(पूर्णाङ्क keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    यदि (keycode < SDL_arraysize(riscos_scancode_सारणी)) {
        scancode = riscos_scancode_सारणी[keycode];

#यदि_परिभाषितम् DEBUG_SCANCODES
        यदि (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#यदि_अन्तः
    }

    प्रत्यागम scancode;
}

शून्य RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *आन्तरिकम् = _this->आन्तरिकम्;
    Uint8 कुञ्चिका = 2;
    पूर्णाङ्क i;

    // Check for key releases
    प्रति (i = 0; i < RISCOS_MAX_कुञ्चिकाः_PRESSED; i++) {
        यदि (आन्तरिकम्->कुञ्चिका_pressed[i] != 255) {
            यदि ((_kernel_osbyte(129, आन्तरिकम्->कुञ्चिका_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_कुञ्चिका(0, SDL_DEFAULT_KEYBOARD_ID, आन्तरिकम्->कुञ्चिका_pressed[i], SDL_RISCOS_translate_keycode(आन्तरिकम्->कुञ्चिका_pressed[i]), false);
                आन्तरिकम्->कुञ्चिका_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    यावत् (कुञ्चिका < 0xff) {
        कुञ्चिका = _kernel_osbyte(121, कुञ्चिका + 1, 0) & 0xff;
        विकल्प (कुञ्चिका) {
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
            SDL_Send_Keyboard_कुञ्चिका(0, SDL_DEFAULT_KEYBOARD_ID, कुञ्चिका, SDL_RISCOS_translate_keycode(कुञ्चिका), true);

            // Record the press so we can detect release later.
            प्रति (i = 0; i < RISCOS_MAX_कुञ्चिकाः_PRESSED; i++) {
                यदि (आन्तरिकम्->कुञ्चिका_pressed[i] == कुञ्चिका) {
                    भङ्ग;
                }
                यदि (आन्तरिकम्->कुञ्चिका_pressed[i] == 255) {
                    आन्तरिकम्->कुञ्चिका_pressed[i] = कुञ्चिका;
                    भङ्ग;
                }
            }
        }
    }
}

स्थिर ध्रुव Uint8 mouse_button_map[] = {
    SDL_BUTTON_दक्षिणः,
    SDL_BUTTON_मध्यः,
    SDL_BUTTON_वामः,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

शून्य RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *आन्तरिकम् = _this->आन्तरिकम्;
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

    यदि (आन्तरिकम्->चरमः_mouse_buttons != buttons) {
        प्रति (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
            bool अधस्तात् = ((buttons & (1 << i)) != 0);
            SDL_SendMouseButton(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, mouse_button_map[i], अधस्तात्);
        }
        आन्तरिकम्->चरमः_mouse_buttons = buttons;
    }
}

bool RISCOS_InitEvents(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *आन्तरिकम् = _this->आन्तरिकम्;
    _kernel_swi_regs regs;
    पूर्णाङ्क i, स्थितिः;

    प्रति (i = 0; i < RISCOS_MAX_कुञ्चिकाः_PRESSED; i++) {
        आन्तरिकम्->कुञ्चिका_pressed[i] = 255;
    }

    स्थितिः = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_अङ्कः, (स्थितिः & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (स्थितिः & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (स्थितिः & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    आन्तरिकम्->चरमः_mouse_buttons = regs.r[2];

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

#यदि_अन्तः // SDL_VIDEO_DRIVER_RISCOS
