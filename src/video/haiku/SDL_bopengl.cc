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

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت


ساكن SDL_INLINE SDL_BWin *منزل_Be_Win(SDL_کھڑکی *کھڑکی)
{
    أرجع (SDL_BWin *)(کھڑکی->اندرونی);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    أرجع SDL_Looper;
}

// Passing a NULL path means load pointers from the application
منطقي HAIKU_GL_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    طالما (get_اگلا_image_info(0, &cookie, &info) == B_OK) {
        فراغ *location = عدم;
        إذا ( get_image_علامت(info.id, "glBegin", B_علامت_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_رستہ, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_رستہ));
        }
    }
    أرجع سچ;
}

SDL_Function_اشارہ_گر HAIKU_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    إذا (_this->gl_config.dll_handle) {
        فراغ *location = عدم;
        حالت_t err;
        إذا ((err =
            get_image_علامت((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_علامت_TYPE_ANY,
                              &location)) == B_OK) {
            أرجع (SDL_Function_اشارہ_گر)location;
        } وإلا {
                SDL_سیٹ_Error("Couldn't find OpenGL symbol");
                أرجع عدم;
        }
    } وإلا {
        SDL_سیٹ_Error("OpenGL library not loaded");
        أرجع عدم;
    }
}


منطقي HAIKU_GL_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    منزل_Be_Win(کھڑکی)->وٹاندرا_Buffers();
    أرجع سچ;
}

منطقي HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    إذا (glView) {
        إذا ((glView->کھڑکی_2() == عدم) || (!کھڑکی) || (منزل_Be_Win(کھڑکی)->GetGLView() != glView)) {
            أرجع SDL_سیٹ_Error("MakeCurrent failed");
        }
    }
    _GetBeLooper()->سیٹ_Current_Context(glView);
    أرجع سچ;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = منزل_Be_Win(کھڑکی);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    إذا (bwin->GetGLView() != عدم) {
        SDL_سیٹ_Error("Context already creaded");
        أرجع عدم;
    }
    Uint32 gl_flags = BGL_RGB;
    إذا (_this->gl_config.alpha_ناپ) {
        gl_flags |= BGL_ALPHA;
    }
    إذا (_this->gl_config.ڈونگھائی_ناپ) {
        gl_flags |= BGL_ڈونگھائی;
    }
    إذا (_this->gl_config.stencil_ناپ) {
        gl_flags |= BGL_STENCIL;
    }
    إذا (_this->gl_config.double_بفر) {
        gl_flags |= BGL_DOUBLE;
    } وإلا {
        gl_flags |= BGL_SINGLE;
    }
    إذا (_this->gl_config.accum_red_ناپ ||
            _this->gl_config.accum_green_ناپ ||
            _this->gl_config.accum_blue_ناپ ||
            _this->gl_config.accum_alpha_ناپ) {
        gl_flags |= BGL_ACCUM;
    }
#إذا __GNUC__ > 3
    إذا (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#جے_انت
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->سیٹ_Current_Context(bwin->GetGLView());
    أرجع (SDL_GLContext)(bwin->GetGLView());
}

منطقي HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->کھڑکی_2();
    إذا (!bwin) {
        مٹاؤ glView;
    } وإلا {
        bwin->RemoveGLView();
    }
    أرجع سچ;
}


منطقي HAIKU_GL_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    // TODO: Implement this, if necessary?
    أرجع SDL_Unsupported();
}

منطقي HAIKU_GL_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *interval)
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
    SDL_کھڑکی *کھڑکی = _this->windows;
    طالما (کھڑکی) {
        SDL_BWin *bwin = منزل_Be_Win(کھڑکی);
        إذا (bwin->GetGLView()) {
            bwin->جندرا_Looper();
            bwin->RemoveGLView();
            bwin->CreateGLView(bwin->GetGLType());
            bwin->UnlockLooper();
        }
        کھڑکی = کھڑکی->اگلا;
    }
}


#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL
