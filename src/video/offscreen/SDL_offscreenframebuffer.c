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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_OFFSCREEN

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../SDL_properties_c.h"
#అన్తర్భావ "SDL_offscreenframebuffer_c.h"

#నిర్వచించు OFFSCREEN_SURFACE "SDL.internal.window.surface"


bool SDL_OFFSCREEN_Create_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PixelFormat *format, శూన్య **pixels, పూర్ణాంకం *pitch)
{
    SDL_Surface *surface;
    స్థిరరాశి SDL_PixelFormat surface_format = SDL_PIXELFORMAT_XRGB8888;
    పూర్ణాంకం w, h;

    // Create a new framebuffer
    SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &w, &h);
    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    ఒకవేళ (!surface) {
        తిరిగి false;
    }

    // Save the info and return!
    SDL_సమితి_Surface_Property(SDL_Get_కిటికీ_Properties(కిటికీ), OFFSCREEN_SURFACE, surface);
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;

    తిరిగి true;
}

bool SDL_OFFSCREEN_Update_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rects, పూర్ణాంకం numrects)
{
    స్థిర పూర్ణాంకం చట్రం_సంఖ్య;
    SDL_Surface *surface;

    surface = (SDL_Surface *)SDL_Get_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), OFFSCREEN_SURFACE, ఖాళీ);
    ఒకవేళ (!surface) {
        తిరిగి SDL_సమితి_Error("Couldn't find offscreen surface for window");
    }

    // Send the data to the display
    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_OFFSCREEN_SAVE_చట్రాలు, false)) {
        అక్షరం file[128];
        (శూన్య)SDL_snprintf(file, పరిమాణం(file), "SDL_window%" SDL_PRIu32 "-%8.8d.bmp",
                           SDL_Get_కిటికీ_ID(కిటికీ), ++చట్రం_సంఖ్య);
        SDL_SaveBMP(surface, file);
    }
    తిరిగి true;
}

శూన్య SDL_OFFSCREEN_Destroy_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_ClearProperty(SDL_Get_కిటికీ_Properties(కిటికీ), OFFSCREEN_SURFACE);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_OFFSCREEN
