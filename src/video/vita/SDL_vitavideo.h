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

#यदि_अपरिभाषितम् SDL_vitavideo_h
#परिभाषय SDL_vitavideo_h

#अन्तर्भाव "SDL_internal.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_egl_c.h"

#अन्तर्भाव <psp2/types.h>
#अन्तर्भाव <psp2/display.h>
#अन्तर्भाव <psp2/ime_dialog.h>
#अन्तर्भाव <psp2/sysmodule.h>

#यदि_परिभाषितम् SDL_VIDEO_VITA_PIB
#अन्तर्भाव <psp2/gxm.h>
#अन्तर्भाव <psp2/display.h>
#अन्तर्भाव <pib.h>
#अन्तर्भाव <EGL/egl.h>
#अन्तर्भाव <EGL/eglext.h>
#अन्तर्भाव <GLES2/gl2.h>
#अन्तर्भाव <GLES2/gl2ext.h>
प्रकारनिर्देश संरचना SDL_GLDriver_दत्त
{
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    uint32_t swapinterval;
} SDL_GLDriver_दत्त;
#यदि_अन्तः

संरचना SDL_Video_दत्त
{
    bool egl_initialized; // OpenGL device initialization status
    uint32_t egl_refcount;    // OpenGL reference count

    SceWChar16 ime_बफर[SCE_IME_DIALOG_MAX_TEXT_दीर्घता];
    bool ime_सक्रिय;
};

संरचना SDL_गवाक्षः_दत्त
{
    bool उपयुङ्क्ते_gles;
    SceUID बफर_uid;
    शून्य *बफर_2;
#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR
    EGLSurface egl_surface;
    EGLContext egl_context;
#यदि_अन्तः
};

बाह्य SDL_गवाक्षः *Vita_गवाक्षः;

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
बाह्य bool VITA_VideoInit(SDL_VideoDevice *_this);
बाह्य शून्य VITA_VideoQuit(SDL_VideoDevice *_this);
बाह्य bool VITA_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
बाह्य शून्य VITA_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool VITA_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य VITA_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य VITA_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य VITA_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य VITA_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य VITA_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य VITA_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य VITA_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool VITA_समुच्चयः_गवाक्षः_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed);
बाह्य शून्य VITA_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VITA
#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR_OGL
// OpenGL functions
बाह्य bool VITA_GL_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);
बाह्य SDL_GLContext VITA_GL_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य SDL_FunctionPointer VITA_GL_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc);
#यदि_अन्तः

// OpenGLES functions
बाह्य bool VITA_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);
बाह्य SDL_FunctionPointer VITA_GLES_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc);
बाह्य शून्य VITA_GLES_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य SDL_GLContext VITA_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool VITA_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context);
बाह्य bool VITA_GLES_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval);
बाह्य bool VITA_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval);
बाह्य bool VITA_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool VITA_GLES_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
#यदि_अन्तः

// VITA on screen keyboard
बाह्य bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
बाह्य शून्य VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props);
बाह्य शून्य VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);

बाह्य शून्य VITA_PumpEvents(SDL_VideoDevice *_this);

#यदि_अन्तः // SDL_vitavideo_h
