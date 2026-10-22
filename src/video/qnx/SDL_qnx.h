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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __SDL_QNX_H__
#ವ್ಯಾಖ್ಯಾನಿಸು __SDL_QNX_H__

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ <screen/screen.h>
#ಅನ್ತರ್ಭಾವ <EGL/egl.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_Display_ದತ್ತಾಂಶ
{
    screen_display_t screen_display;
} SDL_Display_ದತ್ತಾಂಶ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ                   screen_format;
    screen_display_ಬಹುಲಕ_t screen_display_ಬಹುಲಕ;
} SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
    screen_ಕಿಟಕಿ_t ಕಿಟಕಿ;
    EGLSurface      egl_surface;
    SDL_GLContext   context;
    bool            resize;
    bool            has_focus;
} SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_Cursor_ದತ್ತಾಂಶ
{
    screen_session_t session;
    ಪೂರ್ಣಾಂಕ              realized_shape;
    bool             is_visible;
} SDL_Cursor_ದತ್ತಾಂಶ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_Mouse_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ      x_prev;
    ಪೂರ್ಣಾಂಕ      y_prev;
} SDL_Mouse_ದತ್ತಾಂಶ;

ಬಾಹ್ಯ screen_context_t * getContext();
ಬಾಹ್ಯ screen_event_t * getEvent();

ಬಾಹ್ಯ ಶೂನ್ಯ handleKeyboardEvent(screen_event_t event);
ಬಾಹ್ಯ ಶೂನ್ಯ handle_ಸೂಚಕ_Event(screen_event_t event);

// extern bool glInitConfig(SDL_WindowData *impl, int *pformat);
ಬಾಹ್ಯ bool QNX_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *egl_ಮಾರ್ಗ);
ಬಾಹ್ಯ SDL_Function_ಸೂಚಕ QNX_GLES_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc);
ಬಾಹ್ಯ SDL_GLContext QNX_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool QNX_GLES_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval);
ಬಾಹ್ಯ bool QNX_GLES_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval);
ಬಾಹ್ಯ bool QNX_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool QNX_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ, SDL_GLContext context);
ಬಾಹ್ಯ bool QNX_GLES_DeleteContext(SDL_VideoDevice *_this, SDL_GLContext context);
ಬಾಹ್ಯ ಶೂನ್ಯ QNX_GLES_UnloadLibrary(SDL_VideoDevice *_this);

ಬಾಹ್ಯ SDL_PixelFormat screen_ಗಮ್ಯ_Pixel_Format(ಪೂರ್ಣಾಂಕ screen_format);
ಬಾಹ್ಯ bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ಬಾಹ್ಯ bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ಬಾಹ್ಯ bool QNX_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);

ಬಾಹ್ಯ ಶೂನ್ಯ initMouse(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ quitMouse(SDL_VideoDevice *_this);

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ QNX_ಆರಿಸು_Format(SDL_VideoDevice *_this, EGLConfig egl_conf);

#ಆದರೆ_ಅಂತ್ಯ
