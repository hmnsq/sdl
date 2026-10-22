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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_vitavideo_h
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_vitavideo_h

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/types.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/display.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/ime_dialog.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/sysmodule.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PIB
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/gxm.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/display.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <pib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <EGL/egl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <EGL/eglext.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <GLES2/gl2.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <GLES2/gl2ext.h>
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_GLDriver_ਅੰਕੜੇ
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriver_ਅੰਕੜੇ;
#ਜੇ_ਅੰਤ

ਬਣਤਰ SDL_Video_ਅੰਕੜੇ
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_ਬਫਰ[SCE_IME_DIALOG_MAX_ਪਾਠ_ਲੰਮਾਈ];
    bool ime_ਸਰਗਰਮ;
};

ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
    bool ਵਰਤਦਾ_gles;
    SceUID ਬਫਰ_uid;
    ਖਾਲੀ *ਬਫਰ_2;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#ਜੇ_ਅੰਤ
};

ਬਾਹਰੀ SDL_ਖਿੜਕੀ *Vita_ਖਿੜਕੀ;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
ਬਾਹਰੀ bool VITA_VideoInit(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ VITA_VideoQuit(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool VITA_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
ਬਾਹਰੀ ਖਾਲੀ VITA_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool VITA_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ VITA_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ VITA_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ VITA_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ VITA_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ VITA_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ VITA_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ VITA_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool VITA_ਸੈੱਟ_ਖਿੜਕੀ_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed);
ਬਾਹਰੀ ਖਾਲੀ VITA_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VITA
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
ਬਾਹਰੀ bool VITA_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
ਬਾਹਰੀ SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ SDL_Function_ਸੂਚਕ VITA_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc);
#ਜੇ_ਅੰਤ

// OpenGLES functions
ਬਾਹਰੀ bool VITA_GLES_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
ਬਾਹਰੀ SDL_Function_ਸੂਚਕ VITA_GLES_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc);
ਬਾਹਰੀ ਖਾਲੀ VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
ਬਾਹਰੀ SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context);
ਬਾਹਰੀ bool VITA_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval);
ਬਾਹਰੀ bool VITA_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval);
ਬਾਹਰੀ bool VITA_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#ਜੇ_ਅੰਤ

// VITA on screen keyboard
ਬਾਹਰੀ bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props);
ਬਾਹਰੀ ਖਾਲੀ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

ਬਾਹਰੀ ਖਾਲੀ VITA_PumpEvents(SDL_VideoDevice *_this);

#ਜੇ_ਅੰਤ // SDL_vitavideo_h
