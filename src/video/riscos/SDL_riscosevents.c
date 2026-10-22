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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_RISCOS

#అన్తర్భావ "../../events/SDL_events_c.h"

#అన్తర్భావ "SDL_riscosvideo.h"
#అన్తర్భావ "SDL_riscosevents_c.h"
#అన్తర్భావ "scancodes_riscos.h"

#అన్తర్భావ <kernel.h>
#అన్తర్భావ <swis.h>

స్థిర SDL_Scancode SDL_RISCOS_translate_keycode(పూర్ణాంకం keycode)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    ఒకవేళ (keycode < SDL_arraysize(riscos_scancode_పట్టిక)) {
        scancode = riscos_scancode_పట్టిక[keycode];

#నిర్వచితమైతే DEBUG_SCANCODES
        ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN) {
            SDL_Log("The key you just pressed is not recognized by SDL: %d", keycode);
        }
#అయితే_ముగింపు
    }

    తిరిగి scancode;
}

శూన్య RISCOS_PollKeyboard(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *అంతర్గత = _this->అంతర్గత;
    Uint8 కీలకం = 2;
    పూర్ణాంకం i;

    // Check for key releases
    కొరకు (i = 0; i < RISCOS_MAX_కీలకాలు_PRESSED; i++) {
        ఒకవేళ (అంతర్గత->కీలకం_pressed[i] != 255) {
            ఒకవేళ ((_kernel_osbyte(129, అంతర్గత->కీలకం_pressed[i] ^ 0xff, 0xff) & 0xff) != 255) {
                SDL_Send_Keyboard_కీలకం(0, SDL_DEFAULT_KEYBOARD_ID, అంతర్గత->కీలకం_pressed[i], SDL_RISCOS_translate_keycode(అంతర్గత->కీలకం_pressed[i]), false);
                అంతర్గత->కీలకం_pressed[i] = 255;
            }
        }
    }

    // Check for key presses
    అయితే (కీలకం < 0xff) {
        కీలకం = _kernel_osbyte(121, కీలకం + 1, 0) & 0xff;
        ఎంపిక (కీలకం) {
        స్థితి 255:
        // Ignore mouse keys
        స్థితి 9:
        స్థితి 10:
        స్థితి 11:
        // Ignore keys with multiple INKEY codes
        స్థితి 24:
        స్థితి 40:
        స్థితి 71:
        స్థితి 87:
            ఆపు;

        అప్రమేయ:
            SDL_Send_Keyboard_కీలకం(0, SDL_DEFAULT_KEYBOARD_ID, కీలకం, SDL_RISCOS_translate_keycode(కీలకం), true);

            // Record the press so we can detect release later.
            కొరకు (i = 0; i < RISCOS_MAX_కీలకాలు_PRESSED; i++) {
                ఒకవేళ (అంతర్గత->కీలకం_pressed[i] == కీలకం) {
                    ఆపు;
                }
                ఒకవేళ (అంతర్గత->కీలకం_pressed[i] == 255) {
                    అంతర్గత->కీలకం_pressed[i] = కీలకం;
                    ఆపు;
                }
            }
        }
    }
}

స్థిర స్థిరరాశి Uint8 mouse_button_map[] = {
    SDL_BUTTON_కుడి,
    SDL_BUTTON_మధ్య,
    SDL_BUTTON_ఎడమ,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2,
    SDL_BUTTON_X2 + 1,
    SDL_BUTTON_X2 + 2,
    SDL_BUTTON_X2 + 3
};

శూన్య RISCOS_PollMouse(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *అంతర్గత = _this->అంతర్గత;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Rect rect;
    _kernel_swi_regs regs;
    పూర్ణాంకం i, x, y, buttons;

    ఒకవేళ (!SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &rect)) {
        తిరిగి;
    }

    _kernel_swi(OS_Mouse, &regs, &regs);
    x = (regs.r[0] >> 1);
    y = rect.h - (regs.r[1] >> 1);
    buttons = regs.r[2];

    ఒకవేళ (mouse->x != x || mouse->y != y) {
        SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, (దశాంశం)x, (దశాంశం)y);
    }

    ఒకవేళ (అంతర్గత->చివరి_mouse_buttons != buttons) {
        కొరకు (i = 0; i < SDL_arraysize(mouse_button_map); i++) {
            bool కిందికి = ((buttons & (1 << i)) != 0);
            SDL_SendMouseButton(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, mouse_button_map[i], కిందికి);
        }
        అంతర్గత->చివరి_mouse_buttons = buttons;
    }
}

bool RISCOS_InitEvents(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *అంతర్గత = _this->అంతర్గత;
    _kernel_swi_regs regs;
    పూర్ణాంకం i, స్థితి_2;

    కొరకు (i = 0; i < RISCOS_MAX_కీలకాలు_PRESSED; i++) {
        అంతర్గత->కీలకం_pressed[i] = 255;
    }

    స్థితి_2 = (_kernel_osbyte(202, 0, 255) & 0xFF);
    SDL_ToggleModState(SDL_KMOD_అంకె, (స్థితి_2 & (1 << 2)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_CAPS, (స్థితి_2 & (1 << 4)) ? false : true);
    SDL_ToggleModState(SDL_KMOD_SCROLL, (స్థితి_2 & (1 << 1)) ? true : false);

    _kernel_swi(OS_Mouse, &regs, &regs);
    అంతర్గత->చివరి_mouse_buttons = regs.r[2];

    // Disable escape.
    _kernel_osbyte(229, 1, 0);

    తిరిగి true;
}

శూన్య RISCOS_PumpEvents(SDL_VideoDevice *_this)
{
    RISCOS_PollMouse(_this);
    RISCOS_PollKeyboard(_this);
}

శూన్య RISCOS_QuitEvents(SDL_VideoDevice *_this)
{
    // Re-enable escape.
    _kernel_osbyte(229, 0, 0);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_RISCOS
