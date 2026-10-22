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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_emscriptenvideo_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_emscriptenvideo_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_touch_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <emscripten/emscripten.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <emscripten/html5.h>

ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    SDL_Surface *surface;

    SDL_GLContext gl_context;

    ਪੂਰਨ non_fill_document_ਚੌੜਾਈ;
    ਪੂਰਨ non_fill_document_ਉਚਾਈ;

    ਅੱਖਰ *canvas_id;
    ਅੱਖਰ *keyboard_element;

    ਦਸ਼ਮਲਵ pixel_ਅਨੁਪਾਤ;

    bool external_ਮਾਪ;

    Uint32 fullscreen_ਬਹੁਲਕ_flags;
    bool fullscreen_resize;
    bool fullscreen_change_ਵਿੱਚ_ਤਰੱਕੀ;

    bool has_ਸੂਚਕ_ਤਾਲਾ;

    bool mouse_focus_loss_pending;
};

ਬਾਹਰੀ SDL_ਖਿੜਕੀ *Emscripten_fill_document_ਖਿੜਕੀ;

bool Emscripten_Should_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(ਪੂਰਨ interval);
ਪੂਰਨ Emscripten_Get_Pending_ਅਦਲਾ_ਬਦਲੀ_Interval(ਖਾਲੀ);

#ਜੇ_ਅੰਤ // SDL_emscriptenvideo_h_
