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

#ifndef SDL_rotate_h_
#define SDL_rotate_h_

ಬಾಹ್ಯ SDL_Surface *SDLgfx_rotateSurface(SDL_Surface *src, ದ್ವಿಗುಣ angle, ಪೂರ್ಣಾಙ್ಕ smooth, ಪೂರ್ಣಾಙ್ಕ flipx, ಪೂರ್ಣಾಙ್ಕ flipy,
                                         ಧ್ರುವ SDL_Rect *rect_dest, ದ್ವಿಗುಣ cangle, ದ್ವಿಗುಣ sangle, ಧ್ರುವ SDL_FPoint *center);
ಬಾಹ್ಯ ಶೂನ್ಯ SDLgfx_rotozoomSurfaceSizeTrig(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ದ್ವಿಗುಣ angle, ಧ್ರುವ SDL_FPoint *center,
                                           SDL_Rect *rect_dest, ದ್ವಿಗುಣ *cangle, ದ್ವಿಗುಣ *sangle);

#endif // SDL_rotate_h_
