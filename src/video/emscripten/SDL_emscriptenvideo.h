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
#ضمن "SDL_internal.h"

#اگر_تعریف_نشده SDL_emscriptenvideo_h_
#تعریف_کن SDL_emscriptenvideo_h_

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_touch_c.h"
#ضمن <emscripten/emscripten.h>
#ضمن <emscripten/html5.h>

بنية SDL_پنجره_داده
{
    SDL_پنجره *پنجره;
    SDL_Surface *surface;

    SDL_GLContext gl_context;

    صحيح non_fill_document_عرض;
    صحيح non_fill_document_ارتفاع;

    حرف *canvas_id;
    حرف *keyboard_element;

    عائم pixel_نسبت;

    bool external_اندازه;

    Uint32 fullscreen_نما_flags;
    bool fullscreen_resize;
    bool fullscreen_change_درون_پیشرفت;

    bool has_اشاره_گر_قفل;

    bool mouse_focus_loss_pending;
};

خارجي SDL_پنجره *Emscripten_fill_document_پنجره;

bool Emscripten_Should_مجموعه_جابجا_Interval(صحيح interval);
صحيح Emscripten_Get_Pending_جابجا_Interval(فراغ);

#پایان_اگر // SDL_emscriptenvideo_h_
