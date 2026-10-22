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

#که_نه_تعریف_شوی SDL_vitavideo_h
#تعریف_کړه SDL_vitavideo_h

#ضمن "SDL_internal.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_egl_c.h"

#ضمن <psp2/types.h>
#ضمن <psp2/display.h>
#ضمن <psp2/ime_dialog.h>
#ضمن <psp2/sysmodule.h>

#که_تعریف_شوی SDL_VIDEO_VITA_PIB
#ضمن <psp2/gxm.h>
#ضمن <psp2/display.h>
#ضمن <pib.h>
#ضمن <EGL/egl.h>
#ضمن <EGL/eglext.h>
#ضمن <GLES2/gl2.h>
#ضمن <GLES2/gl2ext.h>
تعريفنوع بنية SDL_GLDriver_معلومات
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriver_معلومات;
#د_که_پای

بنية SDL_Video_معلومات
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_بفر[SCE_IME_DIALOG_MAX_متن_اوږدتیا];
    bool ime_فعال;
};

بنية SDL_کړکۍ_معلومات
{
    bool کاروي_gles;
    SceUID بفر_uid;
    فراغ *بفر_2;
#که_تعریف_شوی SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#د_که_پای
};

خارجي SDL_کړکۍ *Vita_کړکۍ;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجي bool VITA_VideoInit(SDL_VideoDevice *_this);
خارجي فراغ VITA_VideoQuit(SDL_VideoDevice *_this);
خارجي bool VITA_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props);
خارجي فراغ VITA_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool VITA_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ VITA_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ VITA_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ VITA_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ VITA_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ VITA_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ VITA_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ VITA_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool VITA_سېټ_کړکۍ_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed);
خارجي فراغ VITA_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

#که_تعریف_شوی SDL_VIDEO_DRIVER_VITA
#که_تعریف_شوی SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
خارجي bool VITA_GL_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار);
خارجي SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي SDL_Function_اشاره_ګر VITA_GL_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc);
#د_که_پای

// OpenGLES functions
خارجي bool VITA_GLES_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار);
خارجي SDL_Function_اشاره_ګر VITA_GLES_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_GLContext context);
خارجي bool VITA_GLES_سېټ_بدلون_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool VITA_GLES_Get_بدلون_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool VITA_GLES_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#د_که_پای

// VITA on screen keyboard
خارجي bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
خارجي فراغ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props);
خارجي فراغ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

خارجي فراغ VITA_PumpEvents(SDL_VideoDevice *_this);

#د_که_پای // SDL_vitavideo_h
