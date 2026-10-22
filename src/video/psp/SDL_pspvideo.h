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

#اگر_غیر_تعریف_شدہ SDL_pspvideo_h_
#تعریف_کرو SDL_pspvideo_h_

#شامل <GLES/egl.h>

#شامل "SDL_internal.h"
#شامل "../SDL_sysvideo.h"

ساخت SDL_Video_ڈیٹا
{
    bool egl_initialized; // OpenGL ES device initialization status
    uint32_t egl_refcount;    // OpenGL ES reference count

};

ساخت SDL_کھڑکی_ڈیٹا
{
    bool استعمال_کرتا_gles; // if true window must support OpenGL ES

};

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجی bool PSP_VideoInit(SDL_VideoDevice *_this);
خارجی خالی PSP_VideoQuit(SDL_VideoDevice *_this);
خارجی bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجی bool PSP_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
خارجی bool PSP_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجی خالی PSP_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool PSP_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی PSP_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی PSP_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی PSP_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی PSP_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی PSP_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی PSP_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی PSP_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی PSP_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

// OpenGL/OpenGL ES functions
خارجی bool PSP_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ);
خارجی SDL_Function_اشارہ_گر PSP_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجی خالی PSP_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجی SDL_GLContext PSP_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool PSP_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context);
خارجی bool PSP_GL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval);
خارجی bool PSP_GL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval);
خارجی bool PSP_GL_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool PSP_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

// PSP on screen keyboard
خارجی bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
خارجی خالی PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);
خارجی خالی PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

#اگر_ختم // SDL_pspvideo_h_
