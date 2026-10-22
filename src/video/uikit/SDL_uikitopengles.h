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
#यदि_अपरिभाषितम् SDL_uikitopengles_
#परिभाषय SDL_uikitopengles_

#यदि defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)

#अन्तर्भाव "../SDL_sysvideo.h"

बाह्य bool UIKit_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः,
                                SDL_GLContext context);
बाह्य bool UIKit_GL_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य SDL_GLContext UIKit_GL_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool UIKit_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
बाह्य SDL_FunctionPointer UIKit_GL_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc);
बाह्य bool UIKit_GL_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);

बाह्य शून्य UIKit_GL_RestoreCurrentContext(शून्य);

#यदि_अन्तः // SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

#यदि_अन्तः // SDL_uikitopengles_
