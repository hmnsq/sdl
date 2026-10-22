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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_emscriptenvideo_h_
#परिभाषय SDL_emscriptenvideo_h_

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"
#अन्तर्भाव <emscripten/emscripten.h>
#अन्तर्भाव <emscripten/html5.h>

संरचना SDL_गवाक्षः_दत्त
{
    SDL_गवाक्षः *गवाक्षः;
    SDL_Surface *surface;

    SDL_GLContext gl_context;

    पूर्णाङ्क non_fill_document_विस्तारः;
    पूर्णाङ्क non_fill_document_height;

    वर्ण *canvas_id;
    वर्ण *keyboard_element;

    भिन्न pixel_अनुपातः;

    bool external_आकार;

    Uint32 fullscreen_बहुलकम्_flags;
    bool fullscreen_resize;
    bool fullscreen_change_अन्तर्_प्रगतिः;

    bool has_pointer_तालकम्;

    bool mouse_focus_loss_pending;
};

बाह्य SDL_गवाक्षः *Emscripten_fill_document_गवाक्षः;

bool Emscripten_Should_समुच्चयः_Swap_Interval(पूर्णाङ्क interval);
पूर्णाङ्क Emscripten_GetPendingSwapInterval(शून्य);

#यदि_अन्तः // SDL_emscriptenvideo_h_
