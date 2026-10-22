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
#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#அந்தர்பாவ "SDL_bopengl.h"

#அந்தர்பாவ <unistd.h>
#அந்தர்பாவ <KernelKit.h>
#அந்தர்பாவ <OpenGLKit.h>
#அந்தர்பாவ "SDL_BWin.h"
#அந்தர்பாவ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
வெளி "C" {
#endif


நிலையான SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    திரும்பு (SDL_BWin *)(window->internal);
}

நிலையான SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    திரும்பு SDL_Looper;
}

// Passing a NULL path means load pointers from the application
தருக்க HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    போது (get_next_image_info(0, &cookie, &info) == B_OK) {
        வெறுமை *location = வெற்று;
        எனில் ( get_image_குறியீடு(info.id, "glBegin", B_குறியீடு_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_path, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_path));
        }
    }
    திரும்பு உண்மை;
}

SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, மாறிலி எழுத்து *proc)
{
    எனில் (_this->gl_config.dll_handle) {
        வெறுமை *location = வெற்று;
        status_t err;
        எனில் ((err =
            get_image_குறியீடு((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_குறியீடு_TYPE_ANY,
                              &location)) == B_OK) {
            திரும்பு (SDL_FunctionPointer)location;
        } இல்லையெனில் {
                SDL_SetError("Couldn't find OpenGL symbol");
                திரும்பு வெற்று;
        }
    } இல்லையெனில் {
        SDL_SetError("OpenGL library not loaded");
        திரும்பு வெற்று;
    }
}


தருக்க HAIKU_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->SwapBuffers();
    திரும்பு உண்மை;
}

தருக்க HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    எனில் (glView) {
        எனில் ((glView->Window() == வெற்று) || (!window) || (_ToBeWin(window)->GetGLView() != glView)) {
            திரும்பு SDL_SetError("MakeCurrent failed");
        }
    }
    _GetBeLooper()->SetCurrentContext(glView);
    திரும்பு உண்மை;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = _ToBeWin(window);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    எனில் (bwin->GetGLView() != வெற்று) {
        SDL_SetError("Context already creaded");
        திரும்பு வெற்று;
    }
    Uint32 gl_flags = BGL_RGB;
    எனில் (_this->gl_config.alpha_size) {
        gl_flags |= BGL_ALPHA;
    }
    எனில் (_this->gl_config.depth_size) {
        gl_flags |= BGL_DEPTH;
    }
    எனில் (_this->gl_config.stencil_size) {
        gl_flags |= BGL_STENCIL;
    }
    எனில் (_this->gl_config.double_buffer) {
        gl_flags |= BGL_DOUBLE;
    } இல்லையெனில் {
        gl_flags |= BGL_SINGLE;
    }
    எனில் (_this->gl_config.accum_red_size ||
            _this->gl_config.accum_green_size ||
            _this->gl_config.accum_blue_size ||
            _this->gl_config.accum_alpha_size) {
        gl_flags |= BGL_ACCUM;
    }
#எனில் __GNUC__ > 3
    எனில் (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#endif
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->SetCurrentContext(bwin->GetGLView());
    திரும்பு (SDL_GLContext)(bwin->GetGLView());
}

தருக்க HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->Window();
    எனில் (!bwin) {
        delete glView;
    } இல்லையெனில் {
        bwin->RemoveGLView();
    }
    திரும்பு உண்மை;
}


தருக்க HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, முழு interval)
{
    // TODO: Implement this, if necessary?
    திரும்பு SDL_Unsupported();
}

தருக்க HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, முழு *interval)
{
    திரும்பு SDL_Unsupported();
}


வெறுமை HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
வெறுமை HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_Window *window = _this->windows;
    போது (window) {
        SDL_BWin *bwin = _ToBeWin(window);
        எனில் (bwin->GetGLView()) {
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
