/*
  Simple DirectMedia Layer
  Copyright (C) 2026 BlackBerry Limited

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
#അന്തര്ഭാവ "SDL_qnx.h"
#അന്തര്ഭാവ "SDL3/SDL_mouse.h"
#അന്തര്ഭാവ "SDL3/SDL_events.h"
#അന്തര്ഭാവ "SDL3/SDL_video.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"


സ്ഥിതം Uint8 screenToMouseButton(പൂർണ്ണസംഖ്യ x)
{
    //Screen only supports 3 mouse buttons.
    തിരഞ്ഞെടുപ്പ്(x){
        അവസ്ഥ SCREEN_ഇടത്_MOUSE_BUTTON: // 1 << 0
        തിരികെ SDL_BUTTON_ഇടത്;
        അവസ്ഥ SCREEN_വലത്_MOUSE_BUTTON: //1 << 1
        തിരികെ SDL_BUTTON_വലത്;
        അവസ്ഥ SCREEN_നടുവ്_MOUSE_BUTTON: //1 << 2
        തിരികെ SDL_BUTTON_നടുവ്;
    }
    തിരികെ 0;
}

ശൂന്യം handlePointerEvent(screen_event_t event)
{
    പൂർണ്ണസംഖ്യ              buttons = 0;
    പൂർണ്ണസംഖ്യ              mouse_wheel = 0;
    പൂർണ്ണസംഖ്യ              mouse_h_wheel = 0;
    പൂർണ്ണസംഖ്യ              pos[2] = {0,0};

    Uint64           timestamp = SDL_GetTicksNS();
    SDL_Mouse        *mouse;
    SDL_MouseData    *mouse_data;
    SDL_Window       *window;

    screen_get_event_property_iv(event, SCREEN_PROPERTY_BUTTONS, &buttons);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_MOUSE_WHEEL, &mouse_wheel);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_MOUSE_HORIZONTAL_WHEEL, &mouse_h_wheel);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_POSITION, pos);

    mouse = SDL_GetMouse();

    window = mouse->focus;
    mouse_data = mouse->internal;
    SDL_assert(mouse_data != ശൂന്യ);

    എങ്കിൽ (mouse->relative_mode) {
        // The mouse is hidden. We don't have control over its actual position
        // with SCREEN_PROPERTY_POSITION, just the position of the icon.
        SDL_SendMouseMotion(timestamp, window, SDL_DEFAULT_MOUSE_ID, true, pos[0] - mouse_data->x_prev, pos[1] - mouse_data->y_prev);
    } അല്ലെങ്കിൽ {
        SDL_SendMouseMotion(timestamp, window, SDL_DEFAULT_MOUSE_ID, false, pos[0], pos[1]);
    }

    mouse_data->x_prev = pos[0];
    mouse_data->y_prev = pos[1];

    // Capture button presses
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 3; ++i)
    {
        Uint8 ret = screenToMouseButton(1 << i);
        SDL_SendMouseButton(timestamp, window, SDL_DEFAULT_MOUSE_ID, ret, (bool) ((buttons & (1 << i)) == (1 << i)));
    }

    // Capture mouse wheel
    // TODO: Verify this. I can at least confirm that this behaves the same
    //       way as x11.
    SDL_SendMouseWheel(timestamp, window, 0, (ദശാംശം) mouse_wheel, (ദശാംശം) mouse_h_wheel, SDL_MOUSEWHEEL_NORMAL);
}
