/*
  Simple DirectMedia Layer
  Copyright (C) 2026 BlackBerry Limited

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

#यदि_अपरिभाषितम् __SDL_QNX_H__
#परिभाषय __SDL_QNX_H__

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव <screen/screen.h>
#अन्तर्भाव <EGL/egl.h>

प्रकारनिर्देश संरचना SDL_Display_दत्त
{
    screen_display_t screen_display;
} SDL_Display_दत्त;

प्रकारनिर्देश संरचना SDL_Display_बहुलकम्_दत्त
{
    पूर्णाङ्क                   screen_format;
    screen_display_बहुलकम्_t screen_display_बहुलकम्;
} SDL_Display_बहुलकम्_दत्त;

प्रकारनिर्देश संरचना SDL_गवाक्षः_दत्त
{
    screen_गवाक्षः_t गवाक्षः;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_गवाक्षः_दत्त;

प्रकारनिर्देश संरचना SDL_Cursor_दत्त
{
    screen_session_t session;
    पूर्णाङ्क              realized_shape;
    bool             is_visible;
} SDL_Cursor_दत्त;

प्रकारनिर्देश संरचना SDL_Mouse_दत्त
{
    पूर्णाङ्क      x_पूर्व;
    पूर्णाङ्क      y_पूर्व;
} SDL_Mouse_दत्त;

बाह्य screen_context_t * getContext();
बाह्य screen_event_t * getEvent();

बाह्य शून्य handleKeyboardEvent(screen_event_t event);
बाह्य शून्य handlePointerEvent(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
बाह्य bool QNX_GLES_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *egl_मार्गः);
बाह्य SDL_FunctionPointer QNX_GLES_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc);
बाह्य SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool QNX_GLES_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval);
बाह्य bool QNX_GLES_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval);
बाह्य bool QNX_GLES_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः, SDL_GLContext context);
बाह्य bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
बाह्य शून्य QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

बाह्य SDL_PixelFormat screen_गन्तव्यम्_Pixel_Format(पूर्णाङ्क screen_format);
बाह्य bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
बाह्य bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool QNX_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्);

बाह्य शून्य initMouse(SDL_VideoDevice *_this);
बाह्य शून्य quitMouse(SDL_VideoDevice *_this);

बाह्य पूर्णाङ्क QNX_वृणु_Format(SDL_VideoDevice *_this, EGLConfig egl_conf);

#यदि_अन्तः
