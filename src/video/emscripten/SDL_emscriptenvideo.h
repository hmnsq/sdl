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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_emscriptenvideo_h_
#నిర్వచించు SDL_emscriptenvideo_h_

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_touch_c.h"
#అన్తర్భావ <emscripten/emscripten.h>
#అన్తర్భావ <emscripten/html5.h>

నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
    SDL_కిటికీ *కిటికీ;
    SDL_Surface *surface;

    SDL_GLContext gl_context;

    పూర్ణాంకం non_fill_document_వెడల్పు;
    పూర్ణాంకం non_fill_document_ఎత్తు;

    అక్షరం *canvas_id;
    అక్షరం *keyboard_element;

    దశాంశం pixel_నిష్పత్తి;

    bool external_కొలత;

    Uint32 fullscreen_బహుళకం_flags;
    bool fullscreen_resize;
    bool fullscreen_change_లోపల_పురోగతి;

    bool has_సూచిక_తాళం;

    bool mouse_focus_loss_pending;
};

బాహ్య SDL_కిటికీ *Emscripten_fill_document_కిటికీ;

bool Emscripten_Should_సమితి_మార్పిడి_Interval(పూర్ణాంకం interval);
పూర్ణాంకం Emscripten_Get_Pending_మార్పిడి_Interval(శూన్య);

#అయితే_ముగింపు // SDL_emscriptenvideo_h_
