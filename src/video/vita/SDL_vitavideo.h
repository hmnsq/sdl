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

#جے_بنا_تعریف SDL_vitavideo_h
#تعریف_کرو SDL_vitavideo_h

#ضمن "SDL_internal.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_egl_c.h"

#ضمن <psp2/types.h>
#ضمن <psp2/display.h>
#ضمن <psp2/ime_dialog.h>
#ضمن <psp2/sysmodule.h>

#جے_تعریف_شدہ SDL_VIDEO_VITA_PIB
#ضمن <psp2/gxm.h>
#ضمن <psp2/display.h>
#ضمن <pib.h>
#ضمن <EGL/egl.h>
#ضمن <EGL/eglext.h>
#ضمن <GLES2/gl2.h>
#ضمن <GLES2/gl2ext.h>
تعريفنوع بنية SDL_GLDriver_انکڑے
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriver_انکڑے;
#جے_انت

بنية SDL_Video_انکڑے
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_بفر[SCE_IME_DIALOG_MAX_متن_لمائی];
    bool ime_سرگرم;
};

بنية SDL_کھڑکی_انکڑے
{
    bool ورتدا_gles;
    SceUID بفر_uid;
    فراغ *بفر_2;
#جے_تعریف_شدہ SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#جے_انت
};

خارجي SDL_کھڑکی *Vita_کھڑکی;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجي bool VITA_VideoInit(SDL_VideoDevice *_this);
خارجي فراغ VITA_VideoQuit(SDL_VideoDevice *_this);
خارجي bool VITA_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجي فراغ VITA_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool VITA_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ VITA_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ VITA_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ VITA_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ VITA_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ VITA_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ VITA_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ VITA_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool VITA_سیٹ_کھڑکی_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجي فراغ VITA_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VITA
#جے_تعریف_شدہ SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
خارجي bool VITA_GL_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ);
خارجي SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي SDL_Function_اشارہ_گر VITA_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
#جے_انت

// OpenGLES functions
خارجي bool VITA_GLES_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ);
خارجي SDL_Function_اشارہ_گر VITA_GLES_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context);
خارجي bool VITA_GLES_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool VITA_GLES_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool VITA_GLES_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#جے_انت

// VITA on screen keyboard
خارجي bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
خارجي فراغ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);
خارجي فراغ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

خارجي فراغ VITA_PumpEvents(SDL_VideoDevice *_this);

#جے_انت // SDL_vitavideo_h
