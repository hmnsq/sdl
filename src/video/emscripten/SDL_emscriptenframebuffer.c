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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_EMSCRIPTEN

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_emscriptenvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_emscriptenframebuffer.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <emscripten/threading.h>

bool Emscripten_Create_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PixelFormat *format, ਖਾਲੀ **pixels, ਪੂਰਨ *pitch)
{
    SDL_Surface *surface;
    ਅਚਲ SDL_PixelFormat surface_format = SDL_PIXELFORMAT_RGBA32;
    ਪੂਰਨ w, h;

    // Free the old framebuffer surface
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    surface = ਅੰਕੜੇ->surface;
    SDL_DestroySurface(surface);

    // Create a new one
    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &w, &h);

    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    ਜੇ (!surface) {
        ਵਾਪਸ false;
    }

    // Save the info and return!
    ਅੰਕੜੇ->surface = surface;
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    ਵਾਪਸ true;
}

bool Emscripten_Update_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rects, ਪੂਰਨ numrects)
{
    SDL_Surface *surface;

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    surface = ਅੰਕੜੇ->surface;
    ਜੇ (!surface) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't find framebuffer surface for window");
    }

    // Send the data to the display

    /* *INDENT-OFF* */ // clang-format off
    ਪੂਰਨ updated = MAIN_THREAD_EM_ASM_INT({
        var w = $0;
        var h = $1;
        var pixels = $2;
        var canvasId = UTF8_ਮੰਜ਼ਿਲ_String($3);
        var canvas = document.querySelector(canvasId);

        //TODO: this should store a context per canvas
        var SDL3 = Module['SDL3'];
        ਜੇ (SDL3.ctxCanvas !== canvas) {
            SDL3.ctx = Browser.createContext(canvas, false, true);
            ਜੇ (!SDL3.ctx) {
                ਵਾਪਸ false;
            }
            SDL3.ctxCanvas = canvas;
        }
        ਜੇ (SDL3.w !== w || SDL3.h !== h || SDL3.imageCtx !== SDL3.ctx) {
            SDL3.image = SDL3.ctx.create_Image_ਅੰਕੜੇ(w, h);
            SDL3.w = w;
            SDL3.h = h;
            SDL3.imageCtx = SDL3.ctx;
        }
        var ਅੰਕੜੇ = SDL3.image.ਅੰਕੜੇ;
        var src = pixels / 4;

        ਜੇ (SDL3.data32_ਅੰਕੜੇ !== ਅੰਕੜੇ) {
            SDL3.data32 = new Int32Array(ਅੰਕੜੇ.ਬਫਰ_2);
            SDL3.data32_ਅੰਕੜੇ = ਅੰਕੜੇ;
        }
        var data32 = SDL3.data32;
        data32.ਸੈੱਟ(HEAP32.subarray(src, src + data32.ਲੰਮਾਈ));

        SDL3.ctx.put_Image_ਅੰਕੜੇ(SDL3.image, 0, 0);
        ਵਾਪਸ true;
    }, surface->w, surface->h, surface->pixels, ਅੰਕੜੇ->canvas_id);
    /* *INDENT-ON* */ // clang-format on

    ਜੇ (!updated) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't create context for canvas update");
    }

    ਜੇ (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }

    ਵਾਪਸ true;
}

ਖਾਲੀ Emscripten_Destroy_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    SDL_DestroySurface(ਅੰਕੜੇ->surface);
    ਅੰਕੜੇ->surface = ਨਿਰਾ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_EMSCRIPTEN
