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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_qnx.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL3/SDL_mouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL3/SDL_events.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL3/SDL_video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"


ਸਥਿਰ Uint8 screen_ਮੰਜ਼ਿਲ_Mouse_Button(ਪੂਰਨ x)
{
    //Screen only supports 3 mouse buttons.
    ਚੋਣ(x){
        ਹਾਲਤ SCREEN_ਖੱਬਾ_MOUSE_BUTTON: // 1 << 0
        ਵਾਪਸ SDL_BUTTON_ਖੱਬਾ;
        ਹਾਲਤ SCREEN_ਸੱਜਾ_MOUSE_BUTTON: //1 << 1
        ਵਾਪਸ SDL_BUTTON_ਸੱਜਾ;
        ਹਾਲਤ SCREEN_ਵਿਚਕਾਰ_MOUSE_BUTTON: //1 << 2
        ਵਾਪਸ SDL_BUTTON_ਵਿਚਕਾਰ;
    }
    ਵਾਪਸ 0;
}

ਖਾਲੀ handle_ਸੂਚਕ_Event(screen_event_t event)
{
    ਪੂਰਨ              buttons = 0;
    ਪੂਰਨ              mouse_wheel = 0;
    ਪੂਰਨ              mouse_h_wheel = 0;
    ਪੂਰਨ              pos[2] = {0,0};

    Uint64           timestamp = SDL_GetTicksNS();
    SDL_Mouse        *mouse;
    SDL_Mouse_ਅੰਕੜੇ    *mouse_ਅੰਕੜੇ;
    SDL_ਖਿੜਕੀ       *ਖਿੜਕੀ;

    screen_get_event_property_iv(event, SCREEN_PROPERTY_BUTTONS, &buttons);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_MOUSE_WHEEL, &mouse_wheel);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_MOUSE_HORIZONTAL_WHEEL, &mouse_h_wheel);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_POSITION, pos);

    mouse = SDL_GetMouse();

    ਖਿੜਕੀ = mouse->focus;
    mouse_ਅੰਕੜੇ = mouse->ਅੰਦਰੂਨੀ;
    SDL_assert(mouse_ਅੰਕੜੇ != ਨਿਰਾ);

    ਜੇ (mouse->relative_ਬਹੁਲਕ) {
        // The mouse is hidden. We don't have control over its actual position
        // with SCREEN_PROPERTY_POSITION, just the position of the icon.
        SDL_SendMouseMotion(timestamp, ਖਿੜਕੀ, SDL_DEFAULT_MOUSE_ID, true, pos[0] - mouse_ਅੰਕੜੇ->x_prev, pos[1] - mouse_ਅੰਕੜੇ->y_prev);
    } ਨਹੀਂਤਾਂ {
        SDL_SendMouseMotion(timestamp, ਖਿੜਕੀ, SDL_DEFAULT_MOUSE_ID, false, pos[0], pos[1]);
    }

    mouse_ਅੰਕੜੇ->x_prev = pos[0];
    mouse_ਅੰਕੜੇ->y_prev = pos[1];

    // Capture button presses
    ਲਈ (ਪੂਰਨ i = 0; i < 3; ++i)
    {
        Uint8 ret = screen_ਮੰਜ਼ਿਲ_Mouse_Button(1 << i);
        SDL_SendMouseButton(timestamp, ਖਿੜਕੀ, SDL_DEFAULT_MOUSE_ID, ret, (bool) ((buttons & (1 << i)) == (1 << i)));
    }

    // Capture mouse wheel
    // TODO: Verify this. I can at least confirm that this behaves the same
    //       way as x11.
    SDL_SendMouseWheel(timestamp, ਖਿੜਕੀ, 0, (ਦਸ਼ਮਲਵ) mouse_wheel, (ਦਸ਼ਮਲਵ) mouse_h_wheel, SDL_MOUSEWHEEL_ਸਾਧਾਰਨ);
}
