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
#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#अन्तर्भाव "SDL_bopengl.h"

#अन्तर्भाव <unistd.h>
#अन्तर्भाव <KernelKit.h>
#अन्तर्भाव <OpenGLKit.h>
#अन्तर्भाव "SDL_BWin.h"
#अन्तर्भाव "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
बाह्य "C" {
#endif


स्थिर SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    फर्काऊ (SDL_BWin *)(window->internal);
}

स्थिर SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    फर्काऊ SDL_Looper;
}

// Passing a NULL path means load pointers from the application
तार्किक HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, अचर वर्ण *path)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    जबसम्म (get_next_image_info(0, &cookie, &info) == B_OK) {
        शून्य *location = रिक्त;
        यदि ( get_image_चिह्न(info.id, "glBegin", B_चिह्न_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_path, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_path));
        }
    }
    फर्काऊ सत्य;
}

SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, अचर वर्ण *proc)
{
    यदि (_this->gl_config.dll_handle) {
        शून्य *location = रिक्त;
        status_t err;
        यदि ((err =
            get_image_चिह्न((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_चिह्न_TYPE_ANY,
                              &location)) == B_OK) {
            फर्काऊ (SDL_FunctionPointer)location;
        } अन्यथा {
                SDL_SetError("Couldn't find OpenGL symbol");
                फर्काऊ रिक्त;
        }
    } अन्यथा {
        SDL_SetError("OpenGL library not loaded");
        फर्काऊ रिक्त;
    }
}


तार्किक HAIKU_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->SwapBuffers();
    फर्काऊ सत्य;
}

तार्किक HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    यदि (glView) {
        यदि ((glView->Window() == रिक्त) || (!window) || (_ToBeWin(window)->GetGLView() != glView)) {
            फर्काऊ SDL_SetError("MakeCurrent failed");
        }
    }
    _GetBeLooper()->SetCurrentContext(glView);
    फर्काऊ सत्य;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = _ToBeWin(window);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    यदि (bwin->GetGLView() != रिक्त) {
        SDL_SetError("Context already creaded");
        फर्काऊ रिक्त;
    }
    Uint32 gl_flags = BGL_RGB;
    यदि (_this->gl_config.alpha_size) {
        gl_flags |= BGL_ALPHA;
    }
    यदि (_this->gl_config.depth_size) {
        gl_flags |= BGL_DEPTH;
    }
    यदि (_this->gl_config.stencil_size) {
        gl_flags |= BGL_STENCIL;
    }
    यदि (_this->gl_config.double_buffer) {
        gl_flags |= BGL_DOUBLE;
    } अन्यथा {
        gl_flags |= BGL_SINGLE;
    }
    यदि (_this->gl_config.accum_red_size ||
            _this->gl_config.accum_green_size ||
            _this->gl_config.accum_blue_size ||
            _this->gl_config.accum_alpha_size) {
        gl_flags |= BGL_ACCUM;
    }
#यदि __GNUC__ > 3
    यदि (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#endif
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->SetCurrentContext(bwin->GetGLView());
    फर्काऊ (SDL_GLContext)(bwin->GetGLView());
}

तार्किक HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->Window();
    यदि (!bwin) {
        delete glView;
    } अन्यथा {
        bwin->RemoveGLView();
    }
    फर्काऊ सत्य;
}


तार्किक HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क interval)
{
    // TODO: Implement this, if necessary?
    फर्काऊ SDL_Unsupported();
}

तार्किक HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval)
{
    फर्काऊ SDL_Unsupported();
}


शून्य HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
शून्य HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_Window *window = _this->windows;
    जबसम्म (window) {
        SDL_BWin *bwin = _ToBeWin(window);
        यदि (bwin->GetGLView()) {
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
