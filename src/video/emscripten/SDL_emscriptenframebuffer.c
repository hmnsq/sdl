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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_EMSCRIPTEN

#ضمن "SDL_emscriptenvideo.h"
#ضمن "SDL_emscriptenframebuffer.h"

#ضمن <emscripten/threading.h>

bool Emscripten_Create_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_Surface *surface;
    ثابت SDL_PixelFormat surface_format = SDL_PIXELFORMAT_RGBA32;
    صحيح w, h;

    // Free the old framebuffer surface
    SDL_دري_معلومات *معلومات = دري->اندروني;
    surface = معلومات->surface;
    SDL_DestroySurface(surface);

    // Create a new one
    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &w, &h);

    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    إذا (!surface) {
        أرجع false;
    }

    // Save the info and return!
    معلومات->surface = surface;
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    أرجع true;
}

bool Emscripten_Update_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_Surface *surface;

    SDL_دري_معلومات *معلومات = دري->اندروني;
    surface = معلومات->surface;
    إذا (!surface) {
        أرجع SDL_سيٽ_Error("Couldn't find framebuffer surface for window");
    }

    // Send the data to the display

    /* *INDENT-OFF* */ // clang-format off
    صحيح updated = MAIN_THREAD_EM_ASM_INT({
        var w = $0;
        var h = $1;
        var pixels = $2;
        var canvasId = UTF8_منزل_String($3);
        var canvas = document.querySelector(canvasId);

        //TODO: this should store a context per canvas
        var SDL3 = Module['SDL3'];
        إذا (SDL3.ctxCanvas !== canvas) {
            SDL3.ctx = Browser.createContext(canvas, false, true);
            إذا (!SDL3.ctx) {
                أرجع false;
            }
            SDL3.ctxCanvas = canvas;
        }
        إذا (SDL3.w !== w || SDL3.h !== h || SDL3.imageCtx !== SDL3.ctx) {
            SDL3.image = SDL3.ctx.create_Image_معلومات(w, h);
            SDL3.w = w;
            SDL3.h = h;
            SDL3.imageCtx = SDL3.ctx;
        }
        var معلومات = SDL3.image.معلومات;
        var src = pixels / 4;

        إذا (SDL3.data32_معلومات !== معلومات) {
            SDL3.data32 = new Int32Array(معلومات.بفر_2);
            SDL3.data32_معلومات = معلومات;
        }
        var data32 = SDL3.data32;
        data32.سيٽ(HEAP32.subarray(src, src + data32.ڊيگهائي));

        SDL3.ctx.put_Image_معلومات(SDL3.image, 0, 0);
        أرجع true;
    }, surface->w, surface->h, surface->pixels, معلومات->canvas_id);
    /* *INDENT-ON* */ // clang-format on

    إذا (!updated) {
        أرجع SDL_سيٽ_Error("Couldn't create context for canvas update");
    }

    إذا (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }

    أرجع true;
}

فراغ Emscripten_Destroy_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    SDL_DestroySurface(معلومات->surface);
    معلومات->surface = عدم;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_EMSCRIPTEN
