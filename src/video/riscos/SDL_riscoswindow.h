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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_riscoswindow_h_
#परिभाषय SDL_riscoswindow_h_

#अन्तर्भाव "SDL_riscosdefs.h"

संरचना SDL_गवाक्षः_दत्त
{
    SDL_गवाक्षः *गवाक्षः;
    sprite_area *fb_area;
    sprite_शीर्षकम् *fb_sprite;
};

बाह्य bool RISCOS_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
बाह्य शून्य RISCOS_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);

#यदि_अन्तः // SDL_riscoswindow_h_
