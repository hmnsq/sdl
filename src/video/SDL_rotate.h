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

#నిర్వచితం_కాకపోతే SDL_rotate_h_
#నిర్వచించు SDL_rotate_h_

బాహ్య SDL_Surface *SDLgfx_rotateSurface(SDL_Surface *src, ద్విగుణ angle, పూర్ణాంకం smooth, పూర్ణాంకం flipx, పూర్ణాంకం flipy,
                                         స్థిరరాశి SDL_Rect *rect_dest, ద్విగుణ cangle, ద్విగుణ sangle, స్థిరరాశి SDL_FPoint *center);
బాహ్య శూన్య SDLgfx_rotozoom_Surface_కొలత_Trig(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, ద్విగుణ angle, స్థిరరాశి SDL_FPoint *center,
                                           SDL_Rect *rect_dest, ద్విగుణ *cangle, ద్విగుణ *sangle);

#అయితే_ముగింపు // SDL_rotate_h_
