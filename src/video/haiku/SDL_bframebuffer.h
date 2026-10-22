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

#यदि_अपरिभाषितम् SDL_BFRAMEBUFFER_H
#परिभाषय SDL_BFRAMEBUFFER_H
#अन्तर्भाव <SupportDefs.h>
#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

#परिभाषय DRAWTHREAD

#अन्तर्भाव "../SDL_sysvideo.h"

बाह्य bool HAIKU_Create_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः,
                                          SDL_PixelFormat *format,
                                          शून्य **pixels, पूर्णाङ्क *pitch);
बाह्य bool HAIKU_Update_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः,
                                          ध्रुव SDL_Rect *rects, पूर्णाङ्क numrects);
बाह्य शून्य HAIKU_Destroy_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य int32 HAIKU_DrawThread(शून्य *दत्त);

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
