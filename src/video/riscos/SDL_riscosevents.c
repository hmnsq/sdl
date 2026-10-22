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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_RISCOS

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "scancodes_riscos.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <kernel.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <swis.h>

ਸਥਿਰ SDL_Scancode SDL_RISCOS_translate_keycode(ਪੂਰਨ keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    ਜੇ (keycode < SDL_arraysize(riscos_scancode_ਸਾਰਣੀ)) {
        scancode = riscos_scancode_ਸਾਰਣੀ[keycode];

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_SCANCODES
        ਜੇ (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#ਜੇ_ਅੰਤ
    }

    ਵਾਪਸ scancode;
}

ਖਾਲੀ RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = _this->ਅੰਦਰੂਨੀ;
    Uint8 ਕੁੰਜੀ = 2;
    ਪੂਰਨ i;

    // Check for key releases
    ਲਈ (i = 0; i < RISCOS_MAX_ਕੁੰਜੀਆਂ_PRESSED; i++) {
        ਜੇ (ਅੰਦਰੂਨੀ->ਕੁੰਜੀ_pressed[i] != 255) {
            ਜੇ ((_kernel_osbyte(129, ਅੰਦਰੂਨੀ->ਕੁੰਜੀ_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_ਕੁੰਜੀ(0, SDL_DEFAULT_KEYBOARD_ID, ਅੰਦਰੂਨੀ->ਕੁੰਜੀ_pressed[i], SDL_RISCOS_translate_keycode(ਅੰਦਰੂਨੀ->ਕੁੰਜੀ_pressed[i]), false);
                ਅੰਦਰੂਨੀ->ਕੁੰਜੀ_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    ਜਦੋਂ (ਕੁੰਜੀ < 0xff) {
        ਕੁੰਜੀ = _kernel_osbyte(121, ਕੁੰਜੀ + 1, 0) & 0xff;
        ਚੋਣ (ਕੁੰਜੀ) {
        ਹਾਲਤ 255:
        // Ignore mouse keys
        ਹਾਲਤ 9:
        ਹਾਲਤ 10:
        ਹਾਲਤ 11:
        // Ignore keys with multiple INKEY codes
        ਹਾਲਤ 24:
        ਹਾਲਤ 40:
        ਹਾਲਤ 71:
        ਹਾਲਤ 87:
            ਰੋਕੋ;

        ਮੂਲ:
            SDL_Send_Keyboard_ਕੁੰਜੀ(0, SDL_DEFAULT_KEYBOARD_ID, ਕੁੰਜੀ, SDL_RISCOS_translate_keycode(ਕੁੰਜੀ), true);

            // Record the press so we can detect release later.
            ਲਈ (i = 0; i < RISCOS_MAX_ਕੁੰਜੀਆਂ_PRESSED; i++) {
                ਜੇ (ਅੰਦਰੂਨੀ->ਕੁੰਜੀ_pressed[i] == ਕੁੰਜੀ) {
                    ਰੋਕੋ;
                }
                ਜੇ (ਅੰਦਰੂਨੀ->ਕੁੰਜੀ_pressed[i] == 255) {
                    ਅੰਦਰੂਨੀ->ਕੁੰਜੀ_pressed[i] = ਕੁੰਜੀ;
                    ਰੋਕੋ;
                }
            }
        }
    }
}

ਸਥਿਰ ਅਚਲ Uint8 mouse_button_map[] = {
    SDL_BUTTON_ਸੱਜਾ,
    SDL_BUTTON_ਵਿਚਕਾਰ,
    SDL_BUTTON_ਖੱਬਾ,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

ਖਾਲੀ RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = _this->ਅੰਦਰੂਨੀ;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    ਪੂਰਨ i, x, y, buttons;

    ਜੇ (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        ਵਾਪਸ;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    ਜੇ (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (ਦਸ਼ਮਲਵ)x, (ਦਸ਼ਮਲਵ)y);
    }

    ਜੇ (ਅੰਦਰੂਨੀ->ਆਖਰੀ_mouse_buttons != buttons) {
        ਲਈ (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
            bool ਥੱਲੇ = ((buttons & (1 << i)) != 0);
            SDL_SendMouseButton(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, mouse_button_map[i], ਥੱਲੇ);
        }
        ਅੰਦਰੂਨੀ->ਆਖਰੀ_mouse_buttons = buttons;
    }
}

bool RISCOS_InitEvents(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = _this->ਅੰਦਰੂਨੀ;
    _kernel_swi_regs regs;
    ਪੂਰਨ i, ਸਥਿਤੀ;

    ਲਈ (i = 0; i < RISCOS_MAX_ਕੁੰਜੀਆਂ_PRESSED; i++) {
        ਅੰਦਰੂਨੀ->ਕੁੰਜੀ_pressed[i] = 255;
    }

    ਸਥਿਤੀ = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_ਅੰਕ, (ਸਥਿਤੀ & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (ਸਥਿਤੀ & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (ਸਥਿਤੀ & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    ਅੰਦਰੂਨੀ->ਆਖਰੀ_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    ਵਾਪਸ true;
}

ਖਾਲੀ RISCOS_PumpEvents(SDL_VideoDevice *_this)
{
    RISCOS_PollMouse(_this);
    RISCOS_PollKeyboard(_this);
}

ਖਾਲੀ RISCOS_QuitEvents(SDL_VideoDevice *_this)
{
    // Re-enable escape.
    _kernel_osbyte(229, 0, 0);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_RISCOS
