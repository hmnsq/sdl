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

#నిర్వచితం_కాకపోతే __SDL_QNX_H__
#నిర్వచించు __SDL_QNX_H__

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ <screen/screen.h>
#అన్తర్భావ <EGL/egl.h>

రకనిర్వచనం నిర్మాణం SDL_Display_దత్తాంశం
{
    screen_display_t screen_display;
} SDL_Display_దత్తాంశం;

రకనిర్వచనం నిర్మాణం SDL_Display_బహుళకం_దత్తాంశం
{
    పూర్ణాంకం                   screen_format;
    screen_display_బహుళకం_t screen_display_బహుళకం;
} SDL_Display_బహుళకం_దత్తాంశం;

రకనిర్వచనం నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
    screen_కిటికీ_t కిటికీ;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_కిటికీ_దత్తాంశం;

రకనిర్వచనం నిర్మాణం SDL_Cursor_దత్తాంశం
{
    screen_session_t session;
    పూర్ణాంకం              realized_shape;
    bool             is_visible;
} SDL_Cursor_దత్తాంశం;

రకనిర్వచనం నిర్మాణం SDL_Mouse_దత్తాంశం
{
    పూర్ణాంకం      x_prev;
    పూర్ణాంకం      y_prev;
} SDL_Mouse_దత్తాంశం;

బాహ్య screen_context_t * getContext();
బాహ్య screen_event_t * getEvent();

బాహ్య శూన్య handleKeyboardEvent(screen_event_t event);
బాహ్య శూన్య handle_సూచిక_Event(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
బాహ్య bool QNX_GLES_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *egl_మార్గం);
బాహ్య SDL_Function_సూచిక QNX_GLES_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc);
బాహ్య SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool QNX_GLES_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval);
బాహ్య bool QNX_GLES_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval);
బాహ్య bool QNX_GLES_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ, SDL_GLContext context);
బాహ్య bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
బాహ్య శూన్య QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

బాహ్య SDL_PixelFormat screen_గమ్యం_Pixel_Format(పూర్ణాంకం screen_format);
బాహ్య bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
బాహ్య bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
బాహ్య bool QNX_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);

బాహ్య శూన్య initMouse(SDL_VideoDevice *_this);
బాహ్య శూన్య quitMouse(SDL_VideoDevice *_this);

బాహ్య పూర్ణాంకం QNX_ఎంచుకో_Format(SDL_VideoDevice *_this, EGLConfig egl_conf);

#అయితే_ముగింపు
