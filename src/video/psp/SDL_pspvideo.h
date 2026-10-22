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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_pspvideo_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_pspvideo_h_

#ਅਨ੍ਤਰ੍ਭਾਵ <GLES/egl.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

ਬਣਤਰ SDL_Video_ਅੰਕੜੇ
{
    bool egl_initialized; // OpenGL ES device initialization status
    uint32_t egl_refcount;    // OpenGL ES reference count

};

ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
    bool ਵਰਤਦਾ_gles; // if true window must support OpenGL ES

};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
ਬਾਹਰੀ bool PSP_VideoInit(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ PSP_VideoQuit(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ਬਾਹਰੀ bool PSP_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਬਾਹਰੀ bool PSP_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
ਬਾਹਰੀ ਖਾਲੀ PSP_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool PSP_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ PSP_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ PSP_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ PSP_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ PSP_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ PSP_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ PSP_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ PSP_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ PSP_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

// OpenGL/OpenGL ES functions
ਬਾਹਰੀ bool PSP_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
ਬਾਹਰੀ SDL_Function_ਸੂਚਕ PSP_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc);
ਬਾਹਰੀ ਖਾਲੀ PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
ਬਾਹਰੀ SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context);
ਬਾਹਰੀ bool PSP_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval);
ਬਾਹਰੀ bool PSP_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval);
ਬਾਹਰੀ bool PSP_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

// PSP on screen keyboard
ਬਾਹਰੀ bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props);
ਬਾਹਰੀ ਖਾਲੀ PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

#ਜੇ_ਅੰਤ // SDL_pspvideo_h_
