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

#अगर_घोषित SDL_VIDEO_DRIVER_DUMMY

#समावेश "../SDL_sysvideo.h"
#समावेश "../../SDL_properties_c.h"
#समावेश "SDL_nullframebuffer_c.h"

#घोषणा DUMMY_SURFACE "SDL.internal.window.surface"


bool SDL_DUMMY_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, व्योम **pixels, पूर्णांक *pitch)
{
    SDL_Surface *surface;
    स्थिर SDL_PixelFormat surface_format = SDL_PIXELFORMAT_XRGB8888;
    पूर्णांक w, h;

    // Create a new framebuffer
    SDL_Get_Window_आकार_In_Pixels(window, &w, &h);
    surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    अगर (!surface) {
        वापस false;
    }

    // Save the info and return!
    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), DUMMY_SURFACE, surface);
    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    वापस true;
}

bool SDL_DUMMY_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, स्थिर SDL_Rect *rects, पूर्णांक numrects)
{
    अटल पूर्णांक frame_संख्या;
    SDL_Surface *surface;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), DUMMY_SURFACE, शून्य);
    अगर (!surface) {
        वापस SDL_SetError("Couldn't find dummy surface for window");
    }

    // Send the data to the display
    अगर (SDL_GetHintBoolean(SDL_HINT_VIDEO_DUMMY_SAVE_FRAMES, false)) {
        अक्षर file[128];
        (व्योम)SDL_snprintf(file, माप(file), "SDL_window%" SDL_PRIu32 "-%8.8d.bmp",
                           SDL_GetWindowID(window), ++frame_संख्या);
        SDL_SaveBMP(surface, file);
    }
    वापस true;
}

व्योम SDL_DUMMY_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_ClearProperty(SDL_GetWindowProperties(window), DUMMY_SURFACE);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_DUMMY
