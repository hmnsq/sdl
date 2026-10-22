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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_emscriptenvideo_h_
#تعریف_کرو SDL_emscriptenvideo_h_

#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_touch_c.h"
#شامل <emscripten/emscripten.h>
#شامل <emscripten/html5.h>

ساخت SDL_کھڑکی_ڈیٹا
{
    SDL_کھڑکی *کھڑکی;
    SDL_Surface *surface;

    SDL_GLContext gl_context;

    صحیح non_fill_document_چوڑائی;
    صحیح non_fill_document_اونچائی;

    حرف *canvas_id;
    حرف *keyboard_element;

    اعشاری pixel_تناسب;

    bool external_سائز;

    Uint32 fullscreen_منوال_flags;
    bool fullscreen_resize;
    bool fullscreen_change_اندر_پیش_رفت;

    bool has_اشارہ_گر_تالا;

    bool mouse_focus_loss_pending;
};

خارجی SDL_کھڑکی *Emscripten_fill_document_کھڑکی;

bool Emscripten_Should_سیٹ_تبادلہ_Interval(صحیح interval);
صحیح Emscripten_Get_Pending_تبادلہ_Interval(خالی);

#اگر_ختم // SDL_emscriptenvideo_h_
