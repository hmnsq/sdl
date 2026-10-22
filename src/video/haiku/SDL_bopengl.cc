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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#شامل "SDL_bopengl.h"

#شامل <unistd.h>
#شامل <KernelKit.h>
#شامل <OpenGLKit.h>
#شامل "SDL_BWin.h"
#شامل "../../core/haiku/SDL_BApp.h"

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم


ساکن SDL_INLINE SDL_BWin *مقصد_Be_Win(SDL_کھڑکی *کھڑکی)
{
    واپس (SDL_BWin *)(کھڑکی->اندرونی_2);
}

ساکن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    واپس SDL_Looper;
}

// Passing a NULL path means load pointers from the application
منطقی HAIKU_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    جب (get_اگلا_image_info(0, &cookie, &info) == B_OK) {
        خالی *location = تہی;
        اگر ( get_image_علامت(info.id, "glBegin", B_علامت_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_راستہ, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_راستہ));
        }
    }
    واپس سچ;
}

SDL_Function_اشارہ_گر HAIKU_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    اگر (_this->gl_config.dll_handle) {
        خالی *location = تہی;
        حالت_t err;
        اگر ((err =
            get_image_علامت((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_علامت_TYPE_ANY,
                              &location)) == B_OK) {
            واپس (SDL_Function_اشارہ_گر)location;
        } ورنہ {
                SDL_سیٹ_Error("Couldn't find OpenGL symbol");
                واپس تہی;
        }
    } ورنہ {
        SDL_سیٹ_Error("OpenGL library not loaded");
        واپس تہی;
    }
}


منطقی HAIKU_GL_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    مقصد_Be_Win(کھڑکی)->تبادلہ_Buffers();
    واپس سچ;
}

منطقی HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    اگر (glView) {
        اگر ((glView->کھڑکی_2() == تہی) || (!کھڑکی) || (مقصد_Be_Win(کھڑکی)->GetGLView() != glView)) {
            واپس SDL_سیٹ_Error("MakeCurrent failed");
        }
    }
    _GetBeLooper()->سیٹ_Current_Context(glView);
    واپس سچ;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = مقصد_Be_Win(کھڑکی);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    اگر (bwin->GetGLView() != تہی) {
        SDL_سیٹ_Error("Context already creaded");
        واپس تہی;
    }
    Uint32 gl_flags = BGL_RGB;
    اگر (_this->gl_config.alpha_سائز) {
        gl_flags |= BGL_ALPHA;
    }
    اگر (_this->gl_config.گہرائی_سائز) {
        gl_flags |= BGL_گہرائی;
    }
    اگر (_this->gl_config.stencil_سائز) {
        gl_flags |= BGL_STENCIL;
    }
    اگر (_this->gl_config.double_بفر) {
        gl_flags |= BGL_DOUBLE;
    } ورنہ {
        gl_flags |= BGL_SINGLE;
    }
    اگر (_this->gl_config.accum_red_سائز ||
            _this->gl_config.accum_green_سائز ||
            _this->gl_config.accum_blue_سائز ||
            _this->gl_config.accum_alpha_سائز) {
        gl_flags |= BGL_ACCUM;
    }
#اگر __GNUC__ > 3
    اگر (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#اگر_ختم
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->سیٹ_Current_Context(bwin->GetGLView());
    واپس (SDL_GLContext)(bwin->GetGLView());
}

منطقی HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->کھڑکی_2();
    اگر (!bwin) {
        حذف glView;
    } ورنہ {
        bwin->RemoveGLView();
    }
    واپس سچ;
}


منطقی HAIKU_GL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval)
{
    // TODO: Implement this, if necessary?
    واپس SDL_Unsupported();
}

منطقی HAIKU_GL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval)
{
    واپس SDL_Unsupported();
}


خالی HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
خالی HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_کھڑکی *کھڑکی = _this->windows;
    جب (کھڑکی) {
        SDL_BWin *bwin = مقصد_Be_Win(کھڑکی);
        اگر (bwin->GetGLView()) {
            bwin->تالا_Looper();
            bwin->RemoveGLView();
            bwin->CreateGLView(bwin->GetGLType());
            bwin->UnlockLooper();
        }
        کھڑکی = کھڑکی->اگلا;
    }
}


#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL
