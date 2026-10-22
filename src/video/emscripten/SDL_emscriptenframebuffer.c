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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#અન્તર્ભાવ "SDL_emscriptenvideo.h"
#અન્તર્ભાવ "SDL_emscriptenframebuffer.h"

#અન્તર્ભાવ <emscripten/threading.h>

bool Emscripten_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, શૂન્ય **pixels, પૂર્ણાંક *pitch)
{
    SDL_Surface *surface;
    અચલ SDL_PixelFormat surface_format = SDL_PIXELFORMAT_RGBA32;
    પૂર્ણાંક w, h;

    // Free the old framebuffer surface
    SDL_WindowData *data = window->internal;
    surface = data->surface;
    SDL_DestroySurface(surface);

    // Create a new one
    SDL_GetWindowSizeInPixels(window, &w, &h);

    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    જો (!surface) {
        પાછા false;
    }

    // Save the info and return!
    data->surface = surface;
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    પાછા true;
}

bool Emscripten_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, અચલ SDL_Rect *rects, પૂર્ણાંક numrects)
{
    SDL_Surface *surface;

    SDL_WindowData *data = window->internal;
    surface = data->surface;
    જો (!surface) {
        પાછા SDL_SetError("Couldn't find framebuffer surface for window");
    }

    // Send the data to the display

    /* *INDENT-OFF* */ // clang-format off
    પૂર્ણાંક updated = MAIN_THREAD_EM_ASM_INT({
        var w = $0;
        var h = $1;
        var pixels = $2;
        var canvasId = UTF8ToString($3);
        var canvas = document.querySelector(canvasId);

        //TODO: this should store a context per canvas
        var SDL3 = Module['SDL3'];
        જો (SDL3.ctxCanvas !== canvas) {
            SDL3.ctx = Browser.createContext(canvas, false, true);
            જો (!SDL3.ctx) {
                પાછા false;
            }
            SDL3.ctxCanvas = canvas;
        }
        જો (SDL3.w !== w || SDL3.h !== h || SDL3.imageCtx !== SDL3.ctx) {
            SDL3.image = SDL3.ctx.createImageData(w, h);
            SDL3.w = w;
            SDL3.h = h;
            SDL3.imageCtx = SDL3.ctx;
        }
        var data = SDL3.image.data;
        var src = pixels / 4;

        જો (SDL3.data32Data !== data) {
            SDL3.data32 = new Int32Array(data.buffer);
            SDL3.data32Data = data;
        }
        var data32 = SDL3.data32;
        data32.set(HEAP32.subarray(src, src + data32.length));

        SDL3.ctx.putImageData(SDL3.image, 0, 0);
        પાછા true;
    }, surface->w, surface->h, surface->pixels, data->canvas_id);
    /* *INDENT-ON* */ // clang-format on

    જો (!updated) {
        પાછા SDL_SetError("Couldn't create context for canvas update");
    }

    જો (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }

    પાછા true;
}

શૂન્ય Emscripten_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    SDL_DestroySurface(data->surface);
    data->surface = ખાલી;
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
