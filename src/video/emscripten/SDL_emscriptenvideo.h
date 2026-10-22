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

#ifndef SDL_emscriptenvideo_h_
#define SDL_emscriptenvideo_h_

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"
#अन्तर्भाव <emscripten/emscripten.h>
#अन्तर्भाव <emscripten/html5.h>

संरचना SDL_WindowData
{
    SDL_Window *window;
    SDL_Surface *surface;

    SDL_GLContext gl_context;

    पूर्णांक non_fill_document_width;
    पूर्णांक non_fill_document_height;

    अक्षर *canvas_id;
    अक्षर *keyboard_element;

    दशांश pixel_ratio;

    bool external_size;

    Uint32 fullscreen_mode_flags;
    bool fullscreen_resize;
    bool fullscreen_change_in_progress;

    bool has_pointer_lock;

    bool mouse_focus_loss_pending;
};

बाह्य SDL_Window *Emscripten_fill_document_window;

bool Emscripten_ShouldSetSwapInterval(पूर्णांक interval);
पूर्णांक Emscripten_GetPendingSwapInterval(शून्य);

#endif // SDL_emscriptenvideo_h_
