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

#समावेश "SDL_internal.h"
#समावेश "SDL_qnx.h"
#समावेश "SDL3/SDL_mouse.h"
#समावेश "SDL3/SDL_events.h"
#समावेश "SDL3/SDL_video.h"
#समावेश "../../events/SDL_mouse_c.h"


अटल Uint8 screenToMouseButton(पूर्णांक x)
{
    //Screen only supports 3 mouse buttons.
    चयन(x){
        हाल SCREEN_बायाँ_MOUSE_BUTTON: // 1 << 0
        वापस SDL_BUTTON_बायाँ;
        हाल SCREEN_दायाँ_MOUSE_BUTTON: //1 << 1
        वापस SDL_BUTTON_दायाँ;
        हाल SCREEN_मध्य_MOUSE_BUTTON: //1 << 2
        वापस SDL_BUTTON_मध्य;
    }
    वापस 0;
}

व्योम handlePointerEvent(screen_event_t event)
{
    पूर्णांक              buttons = 0;
    पूर्णांक              mouse_wheel = 0;
    पूर्णांक              mouse_h_wheel = 0;
    पूर्णांक              pos[2] = {0,0};

    Uint64           timestamp = SDL_GetTicksNS();
    SDL_Mouse        *mouse;
    SDL_Mouse_तथ्य    *mouse_तथ्य;
    SDL_Window       *window;

    screen_get_event_property_iv(event, SCREEN_PROPERTY_BUTTONS, &buttons);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_MOUSE_WHEEL, &mouse_wheel);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_MOUSE_HORIZONTAL_WHEEL, &mouse_h_wheel);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_POSITION, pos);

    mouse = SDL_GetMouse();

    window = mouse->focus;
    mouse_तथ्य = mouse->internal;
    SDL_assert(mouse_तथ्य != शून्य);

    अगर (mouse->relative_mode) {
        // The mouse is hidden. We don't have control over its actual position
        // with SCREEN_PROPERTY_POSITION, just the position of the icon.
        SDL_SendMouseMotion(timestamp, window, SDL_DEFAULT_MOUSE_ID, true, pos[0] - mouse_तथ्य->x_पूर्व, pos[1] - mouse_तथ्य->y_पूर्व);
    } अन्यथा {
        SDL_SendMouseMotion(timestamp, window, SDL_DEFAULT_MOUSE_ID, false, pos[0], pos[1]);
    }

    mouse_तथ्य->x_पूर्व = pos[0];
    mouse_तथ्य->y_पूर्व = pos[1];

    // Capture button presses
    क्रम (पूर्णांक i = 0; i < 3; ++i)
    {
        Uint8 ret = screenToMouseButton(1 << i);
        SDL_SendMouseButton(timestamp, window, SDL_DEFAULT_MOUSE_ID, ret, (bool) ((buttons & (1 << i)) == (1 << i)));
    }

    // Capture mouse wheel
    // TODO: Verify this. I can at least confirm that this behaves the same
    //       way as x11.
    SDL_SendMouseWheel(timestamp, window, 0, (भग्न) mouse_wheel, (भग्न) mouse_h_wheel, SDL_MOUSEWHEEL_NORMAL);
}
