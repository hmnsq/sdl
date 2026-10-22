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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_RISCOS

#समावेश "../../events/SDL_events_c.h"

#समावेश "SDL_riscosvideo.h"
#समावेश "SDL_riscosevents_c.h"
#समावेश "scancodes_riscos.h"

#समावेश <kernel.h>
#समावेश <swis.h>

अटल SDL_Scancode SDL_RISCOS_translate_keycode(पूर्णांक keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    अगर (keycode < SDL_arraysize(riscos_scancode_table)) {
        scancode = riscos_scancode_table[keycode];

#अगर_घोषित DEBUG_SCANCODES
        अगर (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#पूर्ण_अगर
    }

    वापस scancode;
}

व्योम RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *internal = _this->internal;
    Uint8 कुंजी = 2;
    पूर्णांक i;

    // Check for key releases
    क्रम (i = 0; i < RISCOS_MAX_कुंजियाँ_PRESSED; i++) {
        अगर (internal->कुंजी_pressed[i] != 255) {
            अगर ((_kernel_osbyte(129, internal->कुंजी_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_कुंजी(0, SDL_DEFAULT_KEYBOARD_ID, internal->कुंजी_pressed[i], SDL_RISCOS_translate_keycode(internal->कुंजी_pressed[i]), false);
                internal->कुंजी_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    जबतक (कुंजी < 0xff) {
        कुंजी = _kernel_osbyte(121, कुंजी + 1, 0) & 0xff;
        चयन (कुंजी) {
        हाल 255:
        // Ignore mouse keys
        हाल 9:
        हाल 10:
        हाल 11:
        // Ignore keys with multiple INKEY codes
        हाल 24:
        हाल 40:
        हाल 71:
        हाल 87:
            अवरोध;

        शेष:
            SDL_Send_Keyboard_कुंजी(0, SDL_DEFAULT_KEYBOARD_ID, कुंजी, SDL_RISCOS_translate_keycode(कुंजी), true);

            // Record the press so we can detect release later.
            क्रम (i = 0; i < RISCOS_MAX_कुंजियाँ_PRESSED; i++) {
                अगर (internal->कुंजी_pressed[i] == कुंजी) {
                    अवरोध;
                }
                अगर (internal->कुंजी_pressed[i] == 255) {
                    internal->कुंजी_pressed[i] = कुंजी;
                    अवरोध;
                }
            }
        }
    }
}

अटल स्थिर Uint8 mouse_button_map[] = {
    SDL_BUTTON_दायाँ,
    SDL_BUTTON_मध्य,
    SDL_BUTTON_बायाँ,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

व्योम RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *internal = _this->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    पूर्णांक i, x, y, buttons;

    अगर (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        वापस;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    अगर (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (भग्न)x, (भग्न)y);
    }

    अगर (internal->last_mouse_buttons != buttons) {
        क्रम (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
            bool down = ((buttons & (1 << i)) != 0);
            SDL_SendMouseButton(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, mouse_button_map[i], down);
        }
        internal->last_mouse_buttons = buttons;
    }
}

bool RISCOS_InitEvents(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *internal = _this->internal;
    _kernel_swi_regs regs;
    पूर्णांक i, status;

    क्रम (i = 0; i < RISCOS_MAX_कुंजियाँ_PRESSED; i++) {
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

    वापस true;
}

व्योम RISCOS_PumpEvents(SDL_VideoDevice *_this)
{
    RISCOS_PollMouse(_this);
    RISCOS_PollKeyboard(_this);
}

व्योम RISCOS_QuitEvents(SDL_VideoDevice *_this)
{
    // Re-enable escape.
    _kernel_osbyte(229, 0, 0);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_RISCOS
