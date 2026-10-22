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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಯದಿ defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#ಅನ್ತರ್ಭಾವ "SDL_bopengl.h"

#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <KernelKit.h>
#ಅನ್ತರ್ಭಾವ <OpenGLKit.h>
#ಅನ್ತರ್ಭಾವ "SDL_BWin.h"
#ಅನ್ತರ್ಭಾವ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
#endif


ಸ್ಥಿರ SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    ಪ್ರತ್ಯಾಗಮ (SDL_BWin *)(window->internal);
}

ಸ್ಥಿರ SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ಪ್ರತ್ಯಾಗಮ SDL_Looper;
}

// Passing a NULL path means load pointers from the application
ತಾರ್ಕಿಕ HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    ಯಾವತ್ (get_next_image_info(0, &cookie, &info) == B_OK) {
        ಶೂನ್ಯ *location = ರಿಕ್ತ;
        ಯದಿ ( get_image_ಚಿಹ್ನೆ(info.id, "glBegin", B_ಚಿಹ್ನೆ_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_path, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_path));
        }
    }
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *proc)
{
    ಯದಿ (_this->gl_config.dll_handle) {
        ಶೂನ್ಯ *location = ರಿಕ್ತ;
        status_t err;
        ಯದಿ ((err =
            get_image_ಚಿಹ್ನೆ((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_ಚಿಹ್ನೆ_TYPE_ANY,
                              &location)) == B_OK) {
            ಪ್ರತ್ಯಾಗಮ (SDL_FunctionPointer)location;
        } ಅನ್ಯಥಾ {
                SDL_SetError("Couldn't find OpenGL symbol");
                ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    } ಅನ್ಯಥಾ {
        SDL_SetError("OpenGL library not loaded");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
}


ತಾರ್ಕಿಕ HAIKU_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->SwapBuffers();
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ತಾರ್ಕಿಕ HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    ಯದಿ (glView) {
        ಯದಿ ((glView->Window() == ರಿಕ್ತ) || (!window) || (_ToBeWin(window)->GetGLView() != glView)) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("MakeCurrent failed");
        }
    }
    _GetBeLooper()->SetCurrentContext(glView);
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = _ToBeWin(window);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    ಯದಿ (bwin->GetGLView() != ರಿಕ್ತ) {
        SDL_SetError("Context already creaded");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    Uint32 gl_flags = BGL_RGB;
    ಯದಿ (_this->gl_config.alpha_size) {
        gl_flags |= BGL_ALPHA;
    }
    ಯದಿ (_this->gl_config.depth_size) {
        gl_flags |= BGL_DEPTH;
    }
    ಯದಿ (_this->gl_config.stencil_size) {
        gl_flags |= BGL_STENCIL;
    }
    ಯದಿ (_this->gl_config.double_buffer) {
        gl_flags |= BGL_DOUBLE;
    } ಅನ್ಯಥಾ {
        gl_flags |= BGL_SINGLE;
    }
    ಯದಿ (_this->gl_config.accum_red_size ||
            _this->gl_config.accum_green_size ||
            _this->gl_config.accum_blue_size ||
            _this->gl_config.accum_alpha_size) {
        gl_flags |= BGL_ACCUM;
    }
#ಯದಿ __GNUC__ > 3
    ಯದಿ (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#endif
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->SetCurrentContext(bwin->GetGLView());
    ಪ್ರತ್ಯಾಗಮ (SDL_GLContext)(bwin->GetGLView());
}

ತಾರ್ಕಿಕ HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->Window();
    ಯದಿ (!bwin) {
        delete glView;
    } ಅನ್ಯಥಾ {
        bwin->RemoveGLView();
    }
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}


ತಾರ್ಕಿಕ HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ interval)
{
    // TODO: Implement this, if necessary?
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

ತಾರ್ಕಿಕ HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ *interval)
{
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}


ಶೂನ್ಯ HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
ಶೂನ್ಯ HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_Window *window = _this->windows;
    ಯಾವತ್ (window) {
        SDL_BWin *bwin = _ToBeWin(window);
        ಯದಿ (bwin->GetGLView()) {
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
