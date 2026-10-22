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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_emscriptenvideo_h_
#define SDL_emscriptenvideo_h_

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_touch_c.h"
#ଅନ୍ତର୍ଭାଵ <emscripten/emscripten.h>
#ଅନ୍ତର୍ଭାଵ <emscripten/html5.h>

ସଂରଚନା SDL_WindowData
{
    SDL_Window *window;
    SDL_Surface *surface;

    SDL_GLContext gl_context;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା non_fill_document_width;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା non_fill_document_height;

    ଅକ୍ଷର *canvas_id;
    ଅକ୍ଷର *keyboard_element;

    ଦଶମିକ pixel_ratio;

    bool external_size;

    Uint32 fullscreen_mode_flags;
    bool fullscreen_resize;
    bool fullscreen_change_in_progress;

    bool has_pointer_lock;

    bool mouse_focus_loss_pending;
};

ବାହ୍ୟ SDL_Window *Emscripten_fill_document_window;

bool Emscripten_ShouldSetSwapInterval(ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା Emscripten_GetPendingSwapInterval(ଶୂନ୍ୟ);

#endif // SDL_emscriptenvideo_h_
