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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"
#ಅನ್ತರ್ಭಾವ "SDL_qnx.h"
#ಅನ್ತರ್ಭಾವ "SDL3/SDL_mouse.h"
#ಅನ್ತರ್ಭಾವ "SDL3/SDL_events.h"
#ಅನ್ತರ್ಭಾವ "SDL3/SDL_video.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"


ಸ್ಥಿರ Uint8 screen_ಗಮ್ಯ_Mouse_Button(ಪೂರ್ಣಾಂಕ x)
{
    //Screen only supports 3 mouse buttons.
    ಆಯ್ಕೆ(x){
        ಸ್ಥಿತಿ SCREEN_ಎಡ_MOUSE_BUTTON: // 1 << 0
        ಹಿಂತಿರುಗಿ SDL_BUTTON_ಎಡ;
        ಸ್ಥಿತಿ SCREEN_ಬಲ_MOUSE_BUTTON: //1 << 1
        ಹಿಂತಿರುಗಿ SDL_BUTTON_ಬಲ;
        ಸ್ಥಿತಿ SCREEN_ಮಧ್ಯ_MOUSE_BUTTON: //1 << 2
        ಹಿಂತಿರುಗಿ SDL_BUTTON_ಮಧ್ಯ;
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ handle_ಸೂಚಕ_Event(screen_event_t event)
{
    ಪೂರ್ಣಾಂಕ              buttons = 0;
    ಪೂರ್ಣಾಂಕ              mouse_wheel = 0;
    ಪೂರ್ಣಾಂಕ              mouse_h_wheel = 0;
    ಪೂರ್ಣಾಂಕ              pos[2] = {0,0};

    Uint64           timestamp = SDL_GetTicksNS();
    SDL_Mouse        *mouse;
    SDL_Mouse_ದತ್ತಾಂಶ    *mouse_ದತ್ತಾಂಶ;
    SDL_ಕಿಟಕಿ       *ಕಿಟಕಿ;

    screen_get_event_property_iv(event, SCREEN_PROPERTY_BUTTONS, &buttons);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_MOUSE_WHEEL, &mouse_wheel);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_MOUSE_HORIZONTAL_WHEEL, &mouse_h_wheel);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_POSITION, pos);

    mouse = SDL_GetMouse();

    ಕಿಟಕಿ = mouse->focus;
    mouse_ದತ್ತಾಂಶ = mouse->ಆಂತರಿಕ;
    SDL_assert(mouse_ದತ್ತಾಂಶ != ಖಾಲಿ);

    ಆದರೆ (mouse->relative_ಬಹುಲಕ) {
        // The mouse is hidden. We don't have control over its actual position
        // with SCREEN_PROPERTY_POSITION, just the position of the icon.
        SDL_SendMouseMotion(timestamp, ಕಿಟಕಿ, SDL_DEFAULT_MOUSE_ID, true, pos[0] - mouse_ದತ್ತಾಂಶ->x_prev, pos[1] - mouse_ದತ್ತಾಂಶ->y_prev);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_SendMouseMotion(timestamp, ಕಿಟಕಿ, SDL_DEFAULT_MOUSE_ID, false, pos[0], pos[1]);
    }

    mouse_ದತ್ತಾಂಶ->x_prev = pos[0];
    mouse_ದತ್ತಾಂಶ->y_prev = pos[1];

    // Capture button presses
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 3; ++i)
    {
        Uint8 ret = screen_ಗಮ್ಯ_Mouse_Button(1 << i);
        SDL_SendMouseButton(timestamp, ಕಿಟಕಿ, SDL_DEFAULT_MOUSE_ID, ret, (bool) ((buttons & (1 << i)) == (1 << i)));
    }

    // Capture mouse wheel
    // TODO: Verify this. I can at least confirm that this behaves the same
    //       way as x11.
    SDL_SendMouseWheel(timestamp, ಕಿಟಕಿ, 0, (ದಶಮಾಂಶ) mouse_wheel, (ದಶಮಾಂಶ) mouse_h_wheel, SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
}
