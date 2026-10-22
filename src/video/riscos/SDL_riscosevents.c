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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#അന്തര്ഭാവ "../../events/SDL_events_c.h"

#അന്തര്ഭാവ "SDL_riscosvideo.h"
#അന്തര്ഭാവ "SDL_riscosevents_c.h"
#അന്തര്ഭാവ "scancodes_riscos.h"

#അന്തര്ഭാവ <kernel.h>
#അന്തര്ഭാവ <swis.h>

സ്ഥിതം SDL_Scancode SDL_RISCOS_translate_keycode(പൂർണ്ണസംഖ്യ keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    എങ്കിൽ (keycode < SDL_arraysize(riscos_scancode_table)) {
        scancode = riscos_scancode_table[keycode];

#ifdef DEBUG_SCANCODES
        എങ്കിൽ (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#endif
    }

    തിരികെ scancode;
}

ശൂന്യം RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    Uint8 താക്കോൽ = 2;
    പൂർണ്ണസംഖ്യ i;

    // Check for key releases
    വേണ്ടി (i = 0; i < RISCOS_MAX_താക്കോലുകൾ_PRESSED; i++) {
        എങ്കിൽ (internal->താക്കോൽ_pressed[i] != 255) {
            എങ്കിൽ ((_kernel_osbyte(129, internal->താക്കോൽ_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_താക്കോൽ(0, SDL_DEFAULT_KEYBOARD_ID, internal->താക്കോൽ_pressed[i], SDL_RISCOS_translate_keycode(internal->താക്കോൽ_pressed[i]), false);
                internal->താക്കോൽ_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    ആകുമ്പോൾ (താക്കോൽ < 0xff) {
        താക്കോൽ = _kernel_osbyte(121, താക്കോൽ + 1, 0) & 0xff;
        തിരഞ്ഞെടുപ്പ് (താക്കോൽ) {
        അവസ്ഥ 255:
        // Ignore mouse keys
        അവസ്ഥ 9:
        അവസ്ഥ 10:
        അവസ്ഥ 11:
        // Ignore keys with multiple INKEY codes
        അവസ്ഥ 24:
        അവസ്ഥ 40:
        അവസ്ഥ 71:
        അവസ്ഥ 87:
            നിർത്തുക;

        സ്ഥിരസ്ഥിതി:
            SDL_Send_Keyboard_താക്കോൽ(0, SDL_DEFAULT_KEYBOARD_ID, താക്കോൽ, SDL_RISCOS_translate_keycode(താക്കോൽ), true);

            // Record the press so we can detect release later.
            വേണ്ടി (i = 0; i < RISCOS_MAX_താക്കോലുകൾ_PRESSED; i++) {
                എങ്കിൽ (internal->താക്കോൽ_pressed[i] == താക്കോൽ) {
                    നിർത്തുക;
                }
                എങ്കിൽ (internal->താക്കോൽ_pressed[i] == 255) {
                    internal->താക്കോൽ_pressed[i] = താക്കോൽ;
                    നിർത്തുക;
                }
            }
        }
    }
}

സ്ഥിതം സ്ഥിരം Uint8 mouse_button_map[] = {
    SDL_BUTTON_വലത്,
    SDL_BUTTON_നടുവ്,
    SDL_BUTTON_ഇടത്,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

ശൂന്യം RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = _this->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    പൂർണ്ണസംഖ്യ i, x, y, buttons;

    എങ്കിൽ (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        തിരികെ;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    എങ്കിൽ (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (ദശാംശം)x, (ദശാംശം)y);
    }

    എങ്കിൽ (internal->last_mouse_buttons != buttons) {
        വേണ്ടി (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
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
    പൂർണ്ണസംഖ്യ i, status;

    വേണ്ടി (i = 0; i < RISCOS_MAX_താക്കോലുകൾ_PRESSED; i++) {
        internal->താക്കോൽ_pressed[i] = 255;
    }

    status = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_അക്കം, (status & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (status & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (status & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    internal->last_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    തിരികെ true;
}

ശൂന്യം RISCOS_PumpEvents(SDL_VideoDevice *_this)
{
    RISCOS_PollMouse(_this);
    RISCOS_PollKeyboard(_this);
}

ശൂന്യം RISCOS_QuitEvents(SDL_VideoDevice *_this)
{
    // Re-enable escape.
    _kernel_osbyte(229, 0, 0);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
