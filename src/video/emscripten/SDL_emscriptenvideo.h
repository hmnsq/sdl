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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_emscriptenvideo_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_emscriptenvideo_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"
#ಅನ್ತರ್ಭಾವ <emscripten/emscripten.h>
#ಅನ್ತರ್ಭಾವ <emscripten/html5.h>

ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    SDL_Surface *surface;

    SDL_GLContext gl_context;

    ಪೂರ್ಣಾಂಕ non_fill_document_ಅಗಲ;
    ಪೂರ್ಣಾಂಕ non_fill_document_ಎತ್ತರ;

    ಅಕ್ಷರ *canvas_id;
    ಅಕ್ಷರ *keyboard_element;

    ದಶಮಾಂಶ pixel_ಅನುಪಾತ;

    bool external_ಗಾತ್ರ;

    Uint32 fullscreen_ಬಹುಲಕ_flags;
    bool fullscreen_resize;
    bool fullscreen_change_ಒಳ_ಪ್ರಗತಿ;

    bool has_ಸೂಚಕ_ಬೀಗ;

    bool mouse_focus_loss_pending;
};

ಬಾಹ್ಯ SDL_ಕಿಟಕಿ *Emscripten_fill_document_ಕಿಟಕಿ;

bool Emscripten_Should_ಗಣ_ಅದಲುಬದಲು_Interval(ಪೂರ್ಣಾಂಕ interval);
ಪೂರ್ಣಾಂಕ Emscripten_Get_Pending_ಅದಲುಬದಲು_Interval(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_emscriptenvideo_h_
