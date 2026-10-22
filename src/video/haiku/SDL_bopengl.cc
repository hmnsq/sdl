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
#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#অন্তর্ভাব "SDL_bopengl.h"

#অন্তর্ভাব <unistd.h>
#অন্তর্ভাব <KernelKit.h>
#অন্তর্ভাব <OpenGLKit.h>
#অন্তর্ভাব "SDL_BWin.h"
#অন্তর্ভাব "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
বাহ্য "C" {
#endif


স্থির SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    প্রত্যাগম (SDL_BWin *)(window->internal);
}

স্থির SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    প্রত্যাগম SDL_Looper;
}

// Passing a NULL path means load pointers from the application
তার্কিক HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুব বর্ণ *path)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    যাবত্ (get_next_image_info(0, &cookie, &info) == B_OK) {
        শূন্য *location = রিক্ত;
        যদি ( get_image_প্রতীক(info.id, "glBegin", B_প্রতীক_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_path, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_path));
        }
    }
    প্রত্যাগম সত্য;
}

SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, ধ্রুব বর্ণ *proc)
{
    যদি (_this->gl_config.dll_handle) {
        শূন্য *location = রিক্ত;
        status_t err;
        যদি ((err =
            get_image_প্রতীক((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_প্রতীক_TYPE_ANY,
                              &location)) == B_OK) {
            প্রত্যাগম (SDL_FunctionPointer)location;
        } অন্যথা {
                SDL_SetError("Couldn't find OpenGL symbol");
                প্রত্যাগম রিক্ত;
        }
    } অন্যথা {
        SDL_SetError("OpenGL library not loaded");
        প্রত্যাগম রিক্ত;
    }
}


তার্কিক HAIKU_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->SwapBuffers();
    প্রত্যাগম সত্য;
}

তার্কিক HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    যদি (glView) {
        যদি ((glView->Window() == রিক্ত) || (!window) || (_ToBeWin(window)->GetGLView() != glView)) {
            প্রত্যাগম SDL_SetError("MakeCurrent failed");
        }
    }
    _GetBeLooper()->SetCurrentContext(glView);
    প্রত্যাগম সত্য;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = _ToBeWin(window);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    যদি (bwin->GetGLView() != রিক্ত) {
        SDL_SetError("Context already creaded");
        প্রত্যাগম রিক্ত;
    }
    Uint32 gl_flags = BGL_RGB;
    যদি (_this->gl_config.alpha_size) {
        gl_flags |= BGL_ALPHA;
    }
    যদি (_this->gl_config.depth_size) {
        gl_flags |= BGL_DEPTH;
    }
    যদি (_this->gl_config.stencil_size) {
        gl_flags |= BGL_STENCIL;
    }
    যদি (_this->gl_config.double_buffer) {
        gl_flags |= BGL_DOUBLE;
    } অন্যথা {
        gl_flags |= BGL_SINGLE;
    }
    যদি (_this->gl_config.accum_red_size ||
            _this->gl_config.accum_green_size ||
            _this->gl_config.accum_blue_size ||
            _this->gl_config.accum_alpha_size) {
        gl_flags |= BGL_ACCUM;
    }
#যদি __GNUC__ > 3
    যদি (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#endif
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->SetCurrentContext(bwin->GetGLView());
    প্রত্যাগম (SDL_GLContext)(bwin->GetGLView());
}

তার্কিক HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->Window();
    যদি (!bwin) {
        delete glView;
    } অন্যথা {
        bwin->RemoveGLView();
    }
    প্রত্যাগম সত্য;
}


তার্কিক HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক interval)
{
    // TODO: Implement this, if necessary?
    প্রত্যাগম SDL_Unsupported();
}

তার্কিক HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক *interval)
{
    প্রত্যাগম SDL_Unsupported();
}


শূন্য HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
শূন্য HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_Window *window = _this->windows;
    যাবত্ (window) {
        SDL_BWin *bwin = _ToBeWin(window);
        যদি (bwin->GetGLView()) {
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
