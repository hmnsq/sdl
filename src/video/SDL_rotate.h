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

ബാഹ്യ SDL_Surface *SDLgfx_rotateSurface(SDL_Surface *src, ഇരട്ട angle, പൂർണ്ണസംഖ്യ smooth, പൂർണ്ണസംഖ്യ flipx, പൂർണ്ണസംഖ്യ flipy,
                                         സ്ഥിരം SDL_Rect *rect_dest, ഇരട്ട cangle, ഇരട്ട sangle, സ്ഥിരം SDL_FPoint *center);
ബാഹ്യ ശൂന്യം SDLgfx_rotozoomSurfaceSizeTrig(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, ഇരട്ട angle, സ്ഥിരം SDL_FPoint *center,
                                           SDL_Rect *rect_dest, ഇരട്ട *cangle, ഇരട്ട *sangle);

#endif // SDL_rotate_h_
