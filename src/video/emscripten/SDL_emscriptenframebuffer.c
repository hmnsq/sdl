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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_EMSCRIPTEN

#समावेश "SDL_emscriptenvideo.h"
#समावेश "SDL_emscriptenframebuffer.h"

#समावेश <emscripten/threading.h>

bool Emscripten_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, व्योम **pixels, पूर्णांक *pitch)
{
    SDL_Surface *surface;
    स्थिर SDL_PixelFormat surface_format = SDL_PIXELFORMAT_RGBA32;
    पूर्णांक w, h;

    // Free the old framebuffer surface
    SDL_Window_तथ्य *तथ्य = window->internal;
    surface = तथ्य->surface;
    SDL_DestroySurface(surface);

    // Create a new one
    SDL_Get_Window_आकार_In_Pixels(window, &w, &h);

    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    अगर (!surface) {
        वापस false;
    }

    // Save the info and return!
    तथ्य->surface = surface;
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    वापस true;
}

bool Emscripten_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, स्थिर SDL_Rect *rects, पूर्णांक numrects)
{
    SDL_Surface *surface;

    SDL_Window_तथ्य *तथ्य = window->internal;
    surface = तथ्य->surface;
    अगर (!surface) {
        वापस SDL_SetError("Couldn't find framebuffer surface for window");
    }

    // Send the data to the display

    /* *INDENT-OFF* */ // clang-format off
    पूर्णांक updated = MAIN_THREAD_EM_ASM_INT({
        var w = $0;
        var h = $1;
        var pixels = $2;
        var canvasId = UTF8ToString($3);
        var canvas = document.querySelector(canvasId);

        //TODO: this should store a context per canvas
        var SDL3 = Module['SDL3'];
        अगर (SDL3.ctxCanvas !== canvas) {
            SDL3.ctx = Browser.createContext(canvas, false, true);
            अगर (!SDL3.ctx) {
                वापस false;
            }
            SDL3.ctxCanvas = canvas;
        }
        अगर (SDL3.w !== w || SDL3.h !== h || SDL3.imageCtx !== SDL3.ctx) {
            SDL3.image = SDL3.ctx.create_Image_तथ्य(w, h);
            SDL3.w = w;
            SDL3.h = h;
            SDL3.imageCtx = SDL3.ctx;
        }
        var तथ्य = SDL3.image.तथ्य;
        var src = pixels / 4;

        अगर (SDL3.data32_तथ्य !== तथ्य) {
            SDL3.data32 = new Int32Array(तथ्य.बफर_2);
            SDL3.data32_तथ्य = तथ्य;
        }
        var data32 = SDL3.data32;
        data32.set(HEAP32.subarray(src, src + data32.लंबाई));

        SDL3.ctx.put_Image_तथ्य(SDL3.image, 0, 0);
        वापस true;
    }, surface->w, surface->h, surface->pixels, तथ्य->canvas_id);
    /* *INDENT-ON* */ // clang-format on

    अगर (!updated) {
        वापस SDL_SetError("Couldn't create context for canvas update");
    }

    अगर (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }

    वापस true;
}

व्योम Emscripten_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    SDL_DestroySurface(तथ्य->surface);
    तथ्य->surface = शून्य;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_EMSCRIPTEN
