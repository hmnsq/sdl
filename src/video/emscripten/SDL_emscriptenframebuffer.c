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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_EMSCRIPTEN

#ಅನ್ತರ್ಭಾವ "SDL_emscriptenvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_emscriptenframebuffer.h"

#ಅನ್ತರ್ಭಾವ <emscripten/threading.h>

bool Emscripten_Create_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಂಕ *pitch)
{
    SDL_Surface *surface;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormat surface_format = SDL_PIXELFORMAT_RGBA32;
    ಪೂರ್ಣಾಂಕ w, h;

    // Free the old framebuffer surface
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    surface = ದತ್ತಾಂಶ->surface;
    SDL_DestroySurface(surface);

    // Create a new one
    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &w, &h);

    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    ಆದರೆ (!surface) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Save the info and return!
    ದತ್ತಾಂಶ->surface = surface;
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    ಹಿಂತಿರುಗಿ true;
}

bool Emscripten_Update_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects, ಪೂರ್ಣಾಂಕ numrects)
{
    SDL_Surface *surface;

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    surface = ದತ್ತಾಂಶ->surface;
    ಆದರೆ (!surface) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't find framebuffer surface for window");
    }

    // Send the data to the display

    /* *INDENT-OFF* */ // clang-format off
    ಪೂರ್ಣಾಂಕ updated = MAIN_THREAD_EM_ASM_INT({
        var w = $0;
        var h = $1;
        var pixels = $2;
        var canvasId = UTF8_ಗಮ್ಯ_String($3);
        var canvas = document.querySelector(canvasId);

        //TODO: this should store a context per canvas
        var SDL3 = Module['SDL3'];
        ಆದರೆ (SDL3.ctxCanvas !== canvas) {
            SDL3.ctx = Browser.createContext(canvas, false, true);
            ಆದರೆ (!SDL3.ctx) {
                ಹಿಂತಿರುಗಿ false;
            }
            SDL3.ctxCanvas = canvas;
        }
        ಆದರೆ (SDL3.w !== w || SDL3.h !== h || SDL3.imageCtx !== SDL3.ctx) {
            SDL3.image = SDL3.ctx.create_Image_ದತ್ತಾಂಶ(w, h);
            SDL3.w = w;
            SDL3.h = h;
            SDL3.imageCtx = SDL3.ctx;
        }
        var ದತ್ತಾಂಶ = SDL3.image.ದತ್ತಾಂಶ;
        var src = pixels / 4;

        ಆದರೆ (SDL3.data32_ದತ್ತಾಂಶ !== ದತ್ತಾಂಶ) {
            SDL3.data32 = new Int32Array(ದತ್ತಾಂಶ.ಬಫರ್_2);
            SDL3.data32_ದತ್ತಾಂಶ = ದತ್ತಾಂಶ;
        }
        var data32 = SDL3.data32;
        data32.ಗಣ(HEAP32.subarray(src, src + data32.ಉದ್ದಳತೆ));

        SDL3.ctx.put_Image_ದತ್ತಾಂಶ(SDL3.image, 0, 0);
        ಹಿಂತಿರುಗಿ true;
    }, surface->w, surface->h, surface->pixels, ದತ್ತಾಂಶ->canvas_id);
    /* *INDENT-ON* */ // clang-format on

    ಆದರೆ (!updated) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't create context for canvas update");
    }

    ಆದರೆ (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        // give back control to browser for screen refresh
        emscripten_sleep(0);
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Emscripten_Destroy_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    SDL_DestroySurface(ದತ್ತಾಂಶ->surface);
    ದತ್ತಾಂಶ->surface = ಖಾಲಿ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_EMSCRIPTEN
