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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_EMSCRIPTEN

#अन्तर्भाव "SDL_emscriptenvideo.h"
#अन्तर्भाव "SDL_emscriptenframebuffer.h"

#अन्तर्भाव <emscripten/threading.h>

bool Emscripten_Create_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PixelFormat *format, शून्य **pixels, पूर्णाङ्क *pitch)
{
    SDL_Surface *surface;
    ध्रुव SDL_PixelFormat surface_format = SDL_PIXELFORMAT_RGBA32;
    पूर्णाङ्क w, h;

    // Free the old framebuffer surface
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    surface = दत्त->surface;
    SDL_DestroySurface(surface);

    // Create a new one
    SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(गवाक्षः, &w, &h);

    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    यदि (!surface) {
        प्रत्यागम false;
    }

    // Save the info and return!
    दत्त->surface = surface;
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    प्रत्यागम true;
}

bool Emscripten_Update_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rects, पूर्णाङ्क numrects)
{
    SDL_Surface *surface;

    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    surface = दत्त->surface;
    यदि (!surface) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't find framebuffer surface for window");
    }

    // Send the data to the display

    /* *INDENT-OFF* */ // clang-format off
    पूर्णाङ्क updated = MAIN_THREAD_EM_ASM_INT({
        var w = $0;
        var h = $1;
        var pixels = $2;
        var canvasId = UTF8_गन्तव्यम्_String($3);
        var canvas = document.querySelector(canvasId);

        //TODO: this should store a context per canvas
        var SDL3 = Module['SDL3'];
        यदि (SDL3.ctxCanvas !== canvas) {
            SDL3.ctx = Browser.createContext(canvas, false, true);
            यदि (!SDL3.ctx) {
                प्रत्यागम false;
            }
            SDL3.ctxCanvas = canvas;
        }
        यदि (SDL3.w !== w || SDL3.h !== h || SDL3.imageCtx !== SDL3.ctx) {
            SDL3.image = SDL3.ctx.create_Image_दत्त(w, h);
            SDL3.w = w;
            SDL3.h = h;
            SDL3.imageCtx = SDL3.ctx;
        }
        var दत्त = SDL3.image.दत्त;
        var src = pixels / 4;

        यदि (SDL3.data32_दत्त !== दत्त) {
            SDL3.data32 = new Int32Array(दत्त.बफर_2);
            SDL3.data32_दत्त = दत्त;
        }
        var data32 = SDL3.data32;
        data32.समुच्चयः(HEAP32.subarray(src, src + data32.दीर्घता));

        SDL3.ctx.put_Image_दत्त(SDL3.image, 0, 0);
        प्रत्यागम true;
    }, surface->w, surface->h, surface->pixels, दत्त->canvas_id);
    /* *INDENT-ON* */ // clang-format on

    यदि (!updated) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't create context for canvas update");
    }

    यदि (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }

    प्रत्यागम true;
}

शून्य Emscripten_Destroy_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    SDL_DestroySurface(दत्त->surface);
    दत्त->surface = रिक्त;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_EMSCRIPTEN
