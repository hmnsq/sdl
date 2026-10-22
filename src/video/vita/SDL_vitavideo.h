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

#اگر_غیر_تعریف_شدہ SDL_vitavideo_h
#تعریف_کرو SDL_vitavideo_h

#شامل "SDL_internal.h"
#شامل "../SDL_sysvideo.h"
#شامل "../SDL_egl_c.h"

#شامل <psp2/types.h>
#شامل <psp2/display.h>
#شامل <psp2/ime_dialog.h>
#شامل <psp2/sysmodule.h>

#اگر_تعریف_شدہ SDL_VIDEO_VITA_PIB
#شامل <psp2/gxm.h>
#شامل <psp2/display.h>
#شامل <pib.h>
#شامل <EGL/egl.h>
#شامل <EGL/eglext.h>
#شامل <GLES2/gl2.h>
#شامل <GLES2/gl2ext.h>
قسمتعریف ساخت SDL_GLDriver_ڈیٹا
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriver_ڈیٹا;
#اگر_ختم

ساخت SDL_Video_ڈیٹا
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_بفر[SCE_IME_DIALOG_MAX_متن_لمبائی];
    bool ime_فعال;
};

ساخت SDL_کھڑکی_ڈیٹا
{
    bool استعمال_کرتا_gles;
    SceUID بفر_uid;
    خالی *بفر_2;
#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#اگر_ختم
};

خارجی SDL_کھڑکی *Vita_کھڑکی;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجی bool VITA_VideoInit(SDL_VideoDevice *_this);
خارجی خالی VITA_VideoQuit(SDL_VideoDevice *_this);
خارجی bool VITA_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجی خالی VITA_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool VITA_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی VITA_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی VITA_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی VITA_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی VITA_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی VITA_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی VITA_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی VITA_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool VITA_سیٹ_کھڑکی_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجی خالی VITA_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VITA
#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
خارجی bool VITA_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ);
خارجی SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی SDL_Function_اشارہ_گر VITA_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
#اگر_ختم

// OpenGLES functions
خارجی bool VITA_GLES_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ);
خارجی SDL_Function_اشارہ_گر VITA_GLES_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجی خالی VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
خارجی SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context);
خارجی bool VITA_GLES_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval);
خارجی bool VITA_GLES_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval);
خارجی bool VITA_GLES_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#اگر_ختم

// VITA on screen keyboard
خارجی bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
خارجی خالی VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);
خارجی خالی VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

خارجی خالی VITA_PumpEvents(SDL_VideoDevice *_this);

#اگر_ختم // SDL_vitavideo_h
