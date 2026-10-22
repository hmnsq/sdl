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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_EMSCRIPTEN

#ضمن "SDL_emscriptenvideo.h"
#ضمن "SDL_emscriptenframebuffer.h"

#ضمن <emscripten/threading.h>

bool Emscripten_Create_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_Surface *surface;
    ثابت SDL_PixelFormat surface_format = SDL_PIXELFORMAT_RGBA32;
    صحيح w, h;

    // Free the old framebuffer surface
    SDL_پنجره_داده *داده = پنجره->داخلی;
    surface = داده->surface;
    SDL_DestroySurface(surface);

    // Create a new one
    SDL_Get_پنجره_اندازه_درون_Pixels(پنجره, &w, &h);

    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    إذا (!surface) {
        أرجع false;
    }

    // Save the info and return!
    داده->surface = surface;
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    أرجع true;
}

bool Emscripten_Update_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_Surface *surface;

    SDL_پنجره_داده *داده = پنجره->داخلی;
    surface = داده->surface;
    إذا (!surface) {
        أرجع SDL_مجموعه_Error("Couldn't find framebuffer surface for window");
    }

    // Send the data to the display

    /* *INDENT-OFF* */ // clang-format off
    صحيح updated = MAIN_THREAD_EM_ASM_INT({
        var w = $0;
        var h = $1;
        var pixels = $2;
        var canvasId = UTF8_مقصد_String($3);
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
            SDL3.image = SDL3.ctx.create_Image_داده(w, h);
            SDL3.w = w;
            SDL3.h = h;
            SDL3.imageCtx = SDL3.ctx;
        }
        var داده = SDL3.image.داده;
        var src = pixels / 4;

        إذا (SDL3.data32_داده !== داده) {
            SDL3.data32 = new Int32Array(داده.میانگیر_2);
            SDL3.data32_داده = داده;
        }
        var data32 = SDL3.data32;
        data32.مجموعه(HEAP32.subarray(src, src + data32.درازی));

        SDL3.ctx.put_Image_داده(SDL3.image, 0, 0);
        أرجع true;
    }, surface->w, surface->h, surface->pixels, داده->canvas_id);
    /* *INDENT-ON* */ // clang-format on

    إذا (!updated) {
        أرجع SDL_مجموعه_Error("Couldn't create context for canvas update");
    }

    إذا (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }

    أرجع true;
}

فراغ Emscripten_Destroy_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    SDL_DestroySurface(داده->surface);
    داده->surface = عدم;
}

#پایان_اگر // SDL_VIDEO_DRIVER_EMSCRIPTEN
