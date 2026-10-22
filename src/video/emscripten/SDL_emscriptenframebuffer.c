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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_EMSCRIPTEN

#అన్తర్భావ "SDL_emscriptenvideo.h"
#అన్తర్భావ "SDL_emscriptenframebuffer.h"

#అన్తర్భావ <emscripten/threading.h>

bool Emscripten_Create_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PixelFormat *format, శూన్య **pixels, పూర్ణాంకం *pitch)
{
    SDL_Surface *surface;
    స్థిరరాశి SDL_PixelFormat surface_format = SDL_PIXELFORMAT_RGBA32;
    పూర్ణాంకం w, h;

    // Free the old framebuffer surface
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    surface = దత్తాంశం->surface;
    SDL_DestroySurface(surface);

    // Create a new one
    SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &w, &h);

    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    ఒకవేళ (!surface) {
        తిరిగి false;
    }

    // Save the info and return!
    దత్తాంశం->surface = surface;
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    తిరిగి true;
}

bool Emscripten_Update_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rects, పూర్ణాంకం numrects)
{
    SDL_Surface *surface;

    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    surface = దత్తాంశం->surface;
    ఒకవేళ (!surface) {
        తిరిగి SDL_సమితి_Error("Couldn't find framebuffer surface for window");
    }

    // Send the data to the display

    /* *INDENT-OFF* */ // clang-format off
    పూర్ణాంకం updated = MAIN_THREAD_EM_ASM_INT({
        var w = $0;
        var h = $1;
        var pixels = $2;
        var canvasId = UTF8_గమ్యం_String($3);
        var canvas = document.querySelector(canvasId);

        //TODO: this should store a context per canvas
        var SDL3 = Module['SDL3'];
        ఒకవేళ (SDL3.ctxCanvas !== canvas) {
            SDL3.ctx = Browser.createContext(canvas, false, true);
            ఒకవేళ (!SDL3.ctx) {
                తిరిగి false;
            }
            SDL3.ctxCanvas = canvas;
        }
        ఒకవేళ (SDL3.w !== w || SDL3.h !== h || SDL3.imageCtx !== SDL3.ctx) {
            SDL3.image = SDL3.ctx.create_Image_దత్తాంశం(w, h);
            SDL3.w = w;
            SDL3.h = h;
            SDL3.imageCtx = SDL3.ctx;
        }
        var దత్తాంశం = SDL3.image.దత్తాంశం;
        var src = pixels / 4;

        ఒకవేళ (SDL3.data32_దత్తాంశం !== దత్తాంశం) {
            SDL3.data32 = new Int32Array(దత్తాంశం.బఫరు_2);
            SDL3.data32_దత్తాంశం = దత్తాంశం;
        }
        var data32 = SDL3.data32;
        data32.సమితి(HEAP32.subarray(src, src + data32.నిడివి));

        SDL3.ctx.put_Image_దత్తాంశం(SDL3.image, 0, 0);
        తిరిగి true;
    }, surface->w, surface->h, surface->pixels, దత్తాంశం->canvas_id);
    /* *INDENT-ON* */ // clang-format on

    ఒకవేళ (!updated) {
        తిరిగి SDL_సమితి_Error("Couldn't create context for canvas update");
    }

    ఒకవేళ (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }

    తిరిగి true;
}

శూన్య Emscripten_Destroy_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    SDL_DestroySurface(దత్తాంశం->surface);
    దత్తాంశం->surface = ఖాళీ;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_EMSCRIPTEN
