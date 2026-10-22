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

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#ଅନ୍ତର୍ଭାଵ "SDL_emscriptenvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_emscriptenframebuffer.h"

#ଅନ୍ତର୍ଭାଵ <emscripten/threading.h>

bool Emscripten_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ଶୂନ୍ୟ **pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pitch)
{
    SDL_Surface *surface;
    ଅଚଳ SDL_PixelFormat surface_format = SDL_PIXELFORMAT_RGBA32;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;

    // Free the old framebuffer surface
    SDL_WindowData *data = window->internal;
    surface = data->surface;
    SDL_DestroySurface(surface);

    // Create a new one
    SDL_GetWindowSizeInPixels(window, &w, &h);

    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    ଯଦି (!surface) {
        ଫେରନ୍ତୁ false;
    }

    // Save the info and return!
    data->surface = surface;
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    ଫେରନ୍ତୁ true;
}

bool Emscripten_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ଅଚଳ SDL_Rect *rects, ପୂର୍ଣ୍ଣସଂଖ୍ୟା numrects)
{
    SDL_Surface *surface;

    SDL_WindowData *data = window->internal;
    surface = data->surface;
    ଯଦି (!surface) {
        ଫେରନ୍ତୁ SDL_SetError("Couldn't find framebuffer surface for window");
    }

    // Send the data to the display

    /* *INDENT-OFF* */ // clang-format off
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା updated = MAIN_THREAD_EM_ASM_INT({
        var w = $0;
        var h = $1;
        var pixels = $2;
        var canvasId = UTF8ToString($3);
        var canvas = document.querySelector(canvasId);

        //TODO: this should store a context per canvas
        var SDL3 = Module['SDL3'];
        ଯଦି (SDL3.ctxCanvas !== canvas) {
            SDL3.ctx = Browser.createContext(canvas, false, true);
            ଯଦି (!SDL3.ctx) {
                ଫେରନ୍ତୁ false;
            }
            SDL3.ctxCanvas = canvas;
        }
        ଯଦି (SDL3.w !== w || SDL3.h !== h || SDL3.imageCtx !== SDL3.ctx) {
            SDL3.image = SDL3.ctx.createImageData(w, h);
            SDL3.w = w;
            SDL3.h = h;
            SDL3.imageCtx = SDL3.ctx;
        }
        var data = SDL3.image.data;
        var src = pixels / 4;

        ଯଦି (SDL3.data32Data !== data) {
            SDL3.data32 = new Int32Array(data.buffer);
            SDL3.data32Data = data;
        }
        var data32 = SDL3.data32;
        data32.set(HEAP32.subarray(src, src + data32.length));

        SDL3.ctx.putImageData(SDL3.image, 0, 0);
        ଫେରନ୍ତୁ true;
    }, surface->w, surface->h, surface->pixels, data->canvas_id);
    /* *INDENT-ON* */ // clang-format on

    ଯଦି (!updated) {
        ଫେରନ୍ତୁ SDL_SetError("Couldn't create context for canvas update");
    }

    ଯଦି (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ Emscripten_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    SDL_DestroySurface(data->surface);
    data->surface = ଖାଲି;
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
