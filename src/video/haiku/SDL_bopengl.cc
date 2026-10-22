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

#ifdef __cplusplus
خارجي "C" {
#endif


ساكن SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    إرجاع (SDL_BWin *)(window->internal);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    إرجاع SDL_Looper;
}

// Passing a NULL path means load pointers from the application
منطقي HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, ثابت حرف *path)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    بينما (get_next_image_info(0, &cookie, &info) == B_OK) {
        فراغ *location = عدم;
        إذا ( get_image_رمز(info.id, "glBegin", B_رمز_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_path, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_path));
        }
    }
    إرجاع true;
}

SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    إذا (_this->gl_config.dll_handle) {
        فراغ *location = عدم;
        status_t err;
        إذا ((err =
            get_image_رمز((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_رمز_TYPE_ANY,
                              &location)) == B_OK) {
            إرجاع (SDL_FunctionPointer)location;
        } وإلا {
                SDL_SetError("Couldn't find OpenGL symbol");
                إرجاع عدم;
        }
    } وإلا {
        SDL_SetError("OpenGL library not loaded");
        إرجاع عدم;
    }
}


منطقي HAIKU_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->SwapBuffers();
    إرجاع true;
}

منطقي HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    إذا (glView) {
        إذا ((glView->Window() == عدم) || (!window) || (_ToBeWin(window)->GetGLView() != glView)) {
            إرجاع SDL_SetError("MakeCurrent failed");
        }
    }
    _GetBeLooper()->SetCurrentContext(glView);
    إرجاع true;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = _ToBeWin(window);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    إذا (bwin->GetGLView() != عدم) {
        SDL_SetError("Context already creaded");
        إرجاع عدم;
    }
    Uint32 gl_flags = BGL_RGB;
    إذا (_this->gl_config.alpha_size) {
        gl_flags |= BGL_ALPHA;
    }
    إذا (_this->gl_config.depth_size) {
        gl_flags |= BGL_DEPTH;
    }
    إذا (_this->gl_config.stencil_size) {
        gl_flags |= BGL_STENCIL;
    }
    إذا (_this->gl_config.double_buffer) {
        gl_flags |= BGL_DOUBLE;
    } وإلا {
        gl_flags |= BGL_SINGLE;
    }
    إذا (_this->gl_config.accum_red_size ||
            _this->gl_config.accum_green_size ||
            _this->gl_config.accum_blue_size ||
            _this->gl_config.accum_alpha_size) {
        gl_flags |= BGL_ACCUM;
    }
#إذا __GNUC__ > 3
    إذا (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#endif
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->SetCurrentContext(bwin->GetGLView());
    إرجاع (SDL_GLContext)(bwin->GetGLView());
}

منطقي HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->Window();
    إذا (!bwin) {
        delete glView;
    } وإلا {
        bwin->RemoveGLView();
    }
    إرجاع true;
}


منطقي HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, صحيح interval)
{
    // TODO: Implement this, if necessary?
    إرجاع SDL_Unsupported();
}

منطقي HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, صحيح *interval)
{
    إرجاع SDL_Unsupported();
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
    SDL_Window *window = _this->windows;
    بينما (window) {
        SDL_BWin *bwin = _ToBeWin(window);
        إذا (bwin->GetGLView()) {
            bwin->LockLooper();
            bwin->RemoveGLView();
            bwin->CreateGLView(bwin->GetGLType());
            bwin->UnlockLooper();
        }
        window = window->next;
    }
}


#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL
