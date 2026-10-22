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

বাহ্য SDL_Surface *SDLgfx_rotateSurface(SDL_Surface *src, দ্ৱিগুণ angle, পূর্ণাঙ্ক smooth, পূর্ণাঙ্ক flipx, পূর্ণাঙ্ক flipy,
                                         ধ্রুৱ SDL_Rect *rect_dest, দ্ৱিগুণ cangle, দ্ৱিগুণ sangle, ধ্রুৱ SDL_FPoint *center);
বাহ্য শূন্য SDLgfx_rotozoomSurfaceSizeTrig(পূর্ণাঙ্ক width, পূর্ণাঙ্ক height, দ্ৱিগুণ angle, ধ্রুৱ SDL_FPoint *center,
                                           SDL_Rect *rect_dest, দ্ৱিগুণ *cangle, দ্ৱিগুণ *sangle);

#endif // SDL_rotate_h_
