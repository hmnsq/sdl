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

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر


ساكن SDL_INLINE SDL_BWin *مقصد_Be_Win(SDL_پنجره *پنجره)
{
    أرجع (SDL_BWin *)(پنجره->داخلی);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    أرجع SDL_Looper;
}

// Passing a NULL path means load pointers from the application
منطقي HAIKU_GL_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    طالما (get_بعدی_image_info(0, &cookie, &info) == B_OK) {
        فراغ *location = عدم;
        إذا ( get_image_نماد(info.id, "glBegin", B_نماد_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_مسیر, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_مسیر));
        }
    }
    أرجع درست;
}

SDL_Function_اشاره_گر HAIKU_GL_Get_Proc_آدرس(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    إذا (_this->gl_config.dll_handle) {
        فراغ *location = عدم;
        وضعیت_t err;
        إذا ((err =
            get_image_نماد((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_نماد_TYPE_ANY,
                              &location)) == B_OK) {
            أرجع (SDL_Function_اشاره_گر)location;
        } وإلا {
                SDL_مجموعه_Error("Couldn't find OpenGL symbol");
                أرجع عدم;
        }
    } وإلا {
        SDL_مجموعه_Error("OpenGL library not loaded");
        أرجع عدم;
    }
}


منطقي HAIKU_GL_جابجا_پنجره(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    مقصد_Be_Win(پنجره)->جابجا_Buffers();
    أرجع درست;
}

منطقي HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره * پنجره, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    إذا (glView) {
        إذا ((glView->پنجره_2() == عدم) || (!پنجره) || (مقصد_Be_Win(پنجره)->GetGLView() != glView)) {
            أرجع SDL_مجموعه_Error("MakeCurrent failed");
        }
    }
    _GetBeLooper()->مجموعه_Current_Context(glView);
    أرجع درست;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = مقصد_Be_Win(پنجره);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    إذا (bwin->GetGLView() != عدم) {
        SDL_مجموعه_Error("Context already creaded");
        أرجع عدم;
    }
    Uint32 gl_flags = BGL_RGB;
    إذا (_this->gl_config.alpha_اندازه) {
        gl_flags |= BGL_ALPHA;
    }
    إذا (_this->gl_config.عمق_اندازه) {
        gl_flags |= BGL_عمق;
    }
    إذا (_this->gl_config.stencil_اندازه) {
        gl_flags |= BGL_STENCIL;
    }
    إذا (_this->gl_config.double_میانگیر) {
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
#پایان_اگر
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->مجموعه_Current_Context(bwin->GetGLView());
    أرجع (SDL_GLContext)(bwin->GetGLView());
}

منطقي HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->پنجره_2();
    إذا (!bwin) {
        حذف glView;
    } وإلا {
        bwin->RemoveGLView();
    }
    أرجع درست;
}


منطقي HAIKU_GL_مجموعه_جابجا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    // TODO: Implement this, if necessary?
    أرجع SDL_Unsupported();
}

منطقي HAIKU_GL_Get_جابجا_Interval(SDL_VideoDevice *_this, صحيح *interval)
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
    SDL_پنجره *پنجره = _this->windows;
    طالما (پنجره) {
        SDL_BWin *bwin = مقصد_Be_Win(پنجره);
        إذا (bwin->GetGLView()) {
            bwin->قفل_Looper();
            bwin->RemoveGLView();
            bwin->CreateGLView(bwin->GetGLType());
            bwin->UnlockLooper();
        }
        پنجره = پنجره->بعدی;
    }
}


#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL
