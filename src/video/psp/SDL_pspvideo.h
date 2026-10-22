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

#جيڪڏهن_وصف_نه_ٿيل SDL_pspvideo_h_
#وصف_ڪريو SDL_pspvideo_h_

#ضمن <GLES/egl.h>

#ضمن "SDL_internal.h"
#ضمن "../SDL_sysvideo.h"

بنية SDL_Video_معلومات
{
    bool egl_initialized; // OpenGL ES device initialization status
    uint32_t egl_refcount;    // OpenGL ES reference count

};

بنية SDL_دري_معلومات
{
    bool استعمال_ڪري_gles; // if true window must support OpenGL ES

};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجي bool PSP_VideoInit(SDL_VideoDevice *_this);
خارجي فراغ PSP_VideoQuit(SDL_VideoDevice *_this);
خارجي bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool PSP_سيٽ_Display_گهڻائي(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي);
خارجي bool PSP_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props);
خارجي فراغ PSP_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool PSP_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ PSP_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ PSP_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ PSP_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ PSP_Raise_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ PSP_Maximize_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ PSP_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ PSP_Restore_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ PSP_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري);

// OpenGL/OpenGL ES functions
خارجي bool PSP_GL_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو);
خارجي SDL_Function_اشارو PSP_GL_Get_Proc_پتو(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_دري *دري, SDL_GLContext context);
خارجي bool PSP_GL_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool PSP_GL_Get_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool PSP_GL_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

// PSP on screen keyboard
خارجي bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
خارجي فراغ PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props);
خارجي فراغ PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري);

#جيڪڏهن_پورو // SDL_pspvideo_h_
