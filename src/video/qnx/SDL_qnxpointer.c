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

#అన్తర్భావ "SDL_internal.h"
#అన్తర్భావ "SDL_qnx.h"
#అన్తర్భావ "SDL3/SDL_mouse.h"
#అన్తర్భావ "SDL3/SDL_events.h"
#అన్తర్భావ "SDL3/SDL_video.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"


స్థిర Uint8 screen_గమ్యం_Mouse_Button(పూర్ణాంకం x)
{
    //Screen only supports 3 mouse buttons.
    ఎంపిక(x){
        స్థితి SCREEN_ఎడమ_MOUSE_BUTTON: // 1 << 0
        తిరిగి SDL_BUTTON_ఎడమ;
        స్థితి SCREEN_కుడి_MOUSE_BUTTON: //1 << 1
        తిరిగి SDL_BUTTON_కుడి;
        స్థితి SCREEN_మధ్య_MOUSE_BUTTON: //1 << 2
        తిరిగి SDL_BUTTON_మధ్య;
    }
    తిరిగి 0;
}

శూన్య handle_సూచిక_Event(screen_event_t event)
{
    పూర్ణాంకం              buttons = 0;
    పూర్ణాంకం              mouse_wheel = 0;
    పూర్ణాంకం              mouse_h_wheel = 0;
    పూర్ణాంకం              pos[2] = {0,0};

    Uint64           timestamp = SDL_GetTicksNS();
    SDL_Mouse        *mouse;
    SDL_Mouse_దత్తాంశం    *mouse_దత్తాంశం;
    SDL_కిటికీ       *కిటికీ;

    screen_get_event_property_iv(event, SCREEN_PROPERTY_BUTTONS, &buttons);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_MOUSE_WHEEL, &mouse_wheel);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_MOUSE_HORIZONTAL_WHEEL, &mouse_h_wheel);
    screen_get_event_property_iv(event, SCREEN_PROPERTY_POSITION, pos);

    mouse = SDL_GetMouse();

    కిటికీ = mouse->focus;
    mouse_దత్తాంశం = mouse->అంతర్గత;
    SDL_assert(mouse_దత్తాంశం != ఖాళీ);

    ఒకవేళ (mouse->relative_బహుళకం) {
        // The mouse is hidden. We don't have control over its actual position
        // with SCREEN_PROPERTY_POSITION, just the position of the icon.
        SDL_SendMouseMotion(timestamp, కిటికీ, SDL_DEFAULT_MOUSE_ID, true, pos[0] - mouse_దత్తాంశం->x_prev, pos[1] - mouse_దత్తాంశం->y_prev);
    } లేకపోతే {
        SDL_SendMouseMotion(timestamp, కిటికీ, SDL_DEFAULT_MOUSE_ID, false, pos[0], pos[1]);
    }

    mouse_దత్తాంశం->x_prev = pos[0];
    mouse_దత్తాంశం->y_prev = pos[1];

    // Capture button presses
    కొరకు (పూర్ణాంకం i = 0; i < 3; ++i)
    {
        Uint8 ret = screen_గమ్యం_Mouse_Button(1 << i);
        SDL_SendMouseButton(timestamp, కిటికీ, SDL_DEFAULT_MOUSE_ID, ret, (bool) ((buttons & (1 << i)) == (1 << i)));
    }

    // Capture mouse wheel
    // TODO: Verify this. I can at least confirm that this behaves the same
    //       way as x11.
    SDL_SendMouseWheel(timestamp, కిటికీ, 0, (దశాంశం) mouse_wheel, (దశాంశం) mouse_h_wheel, SDL_MOUSEWHEEL_సాధారణ);
}
