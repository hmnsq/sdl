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

#که_نه_تعریف_شوی SDL_pspvideo_h_
#تعریف_کړه SDL_pspvideo_h_

#ضمن <GLES/egl.h>

#ضمن "SDL_internal.h"
#ضمن "../SDL_sysvideo.h"

بنية SDL_Video_معلومات
{
    bool egl_initialized; // OpenGL ES device initialization status
    uint32_t egl_refcount;    // OpenGL ES reference count

};

بنية SDL_کړکۍ_معلومات
{
    bool کاروي_gles; // if true window must support OpenGL ES

};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجي bool PSP_VideoInit(SDL_VideoDevice *_this);
خارجي فراغ PSP_VideoQuit(SDL_VideoDevice *_this);
خارجي bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool PSP_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ);
خارجي bool PSP_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props);
خارجي فراغ PSP_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool PSP_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ PSP_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ PSP_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ PSP_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ PSP_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ PSP_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ PSP_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ PSP_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ PSP_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

// OpenGL/OpenGL ES functions
خارجي bool PSP_GL_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار);
خارجي SDL_Function_اشاره_ګر PSP_GL_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_GLContext context);
خارجي bool PSP_GL_سېټ_بدلون_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool PSP_GL_Get_بدلون_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool PSP_GL_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

// PSP on screen keyboard
خارجي bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
خارجي فراغ PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props);
خارجي فراغ PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

#د_که_پای // SDL_pspvideo_h_
