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

#অন্তর্ভাব "SDL_internal.h"
#অন্তর্ভাব "SDL_qnx.h"
#অন্তর্ভাব "SDL3/SDL_mouse.h"
#অন্তর্ভাব "SDL3/SDL_events.h"
#অন্তর্ভাব "SDL3/SDL_video.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"


স্থির Uint8 screenToMouseButton(পূর্ণসংখ্যা x)
{
    //Screen only supports 3 mouse buttons.
    নির্বাচন(x){
        ক্ষেত্র SCREEN_বাম_MOUSE_BUTTON: // 1 << 0
        ফেরত SDL_BUTTON_বাম;
        ক্ষেত্র SCREEN_ডান_MOUSE_BUTTON: //1 << 1
        ফেরত SDL_BUTTON_ডান;
        ক্ষেত্র SCREEN_মধ্য_MOUSE_BUTTON: //1 << 2
        ফেরত SDL_BUTTON_মধ্য;
    }
    ফেরত 0;
}

শূন্য handlePointerEvent(screen_event_t event)
{
    পূর্ণসংখ্যা              buttons = 0;
    পূর্ণসংখ্যা              mouse_wheel = 0;
    পূর্ণসংখ্যা              mouse_h_wheel = 0;
    পূর্ণসংখ্যা              pos[2] = {0,0};

    Uint64           timestamp = SDL_GetTicksNS();
    SDL_Mouse        *mouse;
    SDL_Mouse_তথ্য    *mouse_তথ্য;
    SDL_Window       *window;

    screen_get_event_property_iv(event, SCREEN_PROPERTY_BUTTONS, &buttons);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_MOUSE_WHEEL, &mouse_wheel);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_MOUSE_HORIZONTAL_WHEEL, &mouse_h_wheel);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_POSITION, pos);

    mouse = SDL_GetMouse();

    window = mouse->focus;
    mouse_তথ্য = mouse->internal;
    SDL_assert(mouse_তথ্য != ফাঁকা);

    যদি (mouse->relative_mode) {
        // The mouse is hidden. We don't have control over its actual position
        // with SCREEN_PROPERTY_POSITION, just the position of the icon.
        SDL_SendMouseMotion(timestamp, window, SDL_DEFAULT_MOUSE_ID, true, pos[0] - mouse_তথ্য->x_পূর্ব, pos[1] - mouse_তথ্য->y_পূর্ব);
    } অন্যথা {
        SDL_SendMouseMotion(timestamp, window, SDL_DEFAULT_MOUSE_ID, false, pos[0], pos[1]);
    }

    mouse_তথ্য->x_পূর্ব = pos[0];
    mouse_তথ্য->y_পূর্ব = pos[1];

    // Capture button presses
    জন্য (পূর্ণসংখ্যা i = 0; i < 3; ++i)
    {
        Uint8 ret = screenToMouseButton(1 << i);
        SDL_SendMouseButton(timestamp, window, SDL_DEFAULT_MOUSE_ID, ret, (bool) ((buttons & (1 << i)) == (1 << i)));
    }

    // Capture mouse wheel
    // TODO: Verify this. I can at least confirm that this behaves the same
    //       way as x11.
    SDL_SendMouseWheel(timestamp, window, 0, (দশমিক) mouse_wheel, (দশমিক) mouse_h_wheel, SDL_MOUSEWHEEL_NORMAL);
}
