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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#ضمن "SDL_bopengl.h"

#ضمن <unistd.h>
#ضمن <KernelKit.h>
#ضمن <OpenGLKit.h>
#ضمن "SDL_BWin.h"
#ضمن "../../core/haiku/SDL_BApp.h"

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای


ساكن SDL_INLINE SDL_BWin *منزل_Be_Win(SDL_کړکۍ *کړکۍ)
{
    أرجع (SDL_BWin *)(کړکۍ->دننی);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    أرجع SDL_Looper;
}

// Passing a NULL path means load pointers from the application
منطقي HAIKU_GL_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    طالما (get_بل_image_info(0, &cookie, &info) == B_OK) {
        فراغ *location = عدم;
        إذا ( get_image_نښه(info.id, "glBegin", B_نښه_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_لار, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_لار));
        }
    }
    أرجع ریښتیا;
}

SDL_Function_اشاره_ګر HAIKU_GL_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    إذا (_this->gl_config.dll_handle) {
        فراغ *location = عدم;
        حالت_t err;
        إذا ((err =
            get_image_نښه((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_نښه_TYPE_ANY,
                              &location)) == B_OK) {
            أرجع (SDL_Function_اشاره_ګر)location;
        } وإلا {
                SDL_سېټ_Error("Couldn't find OpenGL symbol");
                أرجع عدم;
        }
    } وإلا {
        SDL_سېټ_Error("OpenGL library not loaded");
        أرجع عدم;
    }
}


منطقي HAIKU_GL_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    منزل_Be_Win(کړکۍ)->بدلون_Buffers();
    أرجع ریښتیا;
}

منطقي HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    إذا (glView) {
        إذا ((glView->کړکۍ_2() == عدم) || (!کړکۍ) || (منزل_Be_Win(کړکۍ)->GetGLView() != glView)) {
            أرجع SDL_سېټ_Error("MakeCurrent failed");
        }
    }
    _GetBeLooper()->سېټ_Current_Context(glView);
    أرجع ریښتیا;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = منزل_Be_Win(کړکۍ);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    إذا (bwin->GetGLView() != عدم) {
        SDL_سېټ_Error("Context already creaded");
        أرجع عدم;
    }
    Uint32 gl_flags = BGL_RGB;
    إذا (_this->gl_config.alpha_اندازه) {
        gl_flags |= BGL_ALPHA;
    }
    إذا (_this->gl_config.ژوروالی_اندازه) {
        gl_flags |= BGL_ژوروالی;
    }
    إذا (_this->gl_config.stencil_اندازه) {
        gl_flags |= BGL_STENCIL;
    }
    إذا (_this->gl_config.double_بفر) {
        gl_flags |= BGL_DOUBLE;
    } وإلا {
        gl_flags |= BGL_SINGLE;
    }
    إذا (_this->gl_config.accum_red_اندازه ||
            _this->gl_config.accum_green_اندازه ||
            _this->gl_config.accum_blue_اندازه ||
            _this->gl_config.accum_alpha_اندازه) {
        gl_flags |= BGL_ACCUM;
    }
#إذا __GNUC__ > 3
    إذا (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#د_که_پای
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->سېټ_Current_Context(bwin->GetGLView());
    أرجع (SDL_GLContext)(bwin->GetGLView());
}

منطقي HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->کړکۍ_2();
    إذا (!bwin) {
        ړنګول glView;
    } وإلا {
        bwin->RemoveGLView();
    }
    أرجع ریښتیا;
}


منطقي HAIKU_GL_سېټ_بدلون_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    // TODO: Implement this, if necessary?
    أرجع SDL_Unsupported();
}

منطقي HAIKU_GL_Get_بدلون_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    أرجع SDL_Unsupported();
}


فراغ HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
فراغ HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_کړکۍ *کړکۍ = _this->windows;
    طالما (کړکۍ) {
        SDL_BWin *bwin = منزل_Be_Win(کړکۍ);
        إذا (bwin->GetGLView()) {
            bwin->قلف_Looper();
            bwin->RemoveGLView();
            bwin->CreateGLView(bwin->GetGLType());
            bwin->UnlockLooper();
        }
        کړکۍ = کړکۍ->بل;
    }
}


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL
