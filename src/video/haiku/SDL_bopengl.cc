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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଯଦି defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#ଅନ୍ତର୍ଭାଵ "SDL_bopengl.h"

#ଅନ୍ତର୍ଭାଵ <unistd.h>
#ଅନ୍ତର୍ଭାଵ <KernelKit.h>
#ଅନ୍ତର୍ଭାଵ <OpenGLKit.h>
#ଅନ୍ତର୍ଭାଵ "SDL_BWin.h"
#ଅନ୍ତର୍ଭାଵ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif


ସ୍ଥିର SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    ଫେରନ୍ତୁ (SDL_BWin *)(window->internal);
}

ସ୍ଥିର SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ଫେରନ୍ତୁ SDL_Looper;
}

// Passing a NULL path means load pointers from the application
ତାର୍କିକ HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    ଯେତେବେଳେ (get_next_image_info(0, &cookie, &info) == B_OK) {
        ଶୂନ୍ୟ *location = ଖାଲି;
        ଯଦି ( get_image_ପ୍ରତୀକ(info.id, "glBegin", B_ପ୍ରତୀକ_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_path, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_path));
        }
    }
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *proc)
{
    ଯଦି (_this->gl_config.dll_handle) {
        ଶୂନ୍ୟ *location = ଖାଲି;
        status_t err;
        ଯଦି ((err =
            get_image_ପ୍ରତୀକ((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_ପ୍ରତୀକ_TYPE_ANY,
                              &location)) == B_OK) {
            ଫେରନ୍ତୁ (SDL_FunctionPointer)location;
        } ଅନ୍ୟଥା {
                SDL_SetError("Couldn't find OpenGL symbol");
                ଫେରନ୍ତୁ ଖାଲି;
        }
    } ଅନ୍ୟଥା {
        SDL_SetError("OpenGL library not loaded");
        ଫେରନ୍ତୁ ଖାଲି;
    }
}


ତାର୍କିକ HAIKU_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->SwapBuffers();
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ତାର୍କିକ HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    ଯଦି (glView) {
        ଯଦି ((glView->Window() == ଖାଲି) || (!window) || (_ToBeWin(window)->GetGLView() != glView)) {
            ଫେରନ୍ତୁ SDL_SetError("MakeCurrent failed");
        }
    }
    _GetBeLooper()->SetCurrentContext(glView);
    ଫେରନ୍ତୁ ସତ୍ୟ;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = _ToBeWin(window);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    ଯଦି (bwin->GetGLView() != ଖାଲି) {
        SDL_SetError("Context already creaded");
        ଫେରନ୍ତୁ ଖାଲି;
    }
    Uint32 gl_flags = BGL_RGB;
    ଯଦି (_this->gl_config.alpha_size) {
        gl_flags |= BGL_ALPHA;
    }
    ଯଦି (_this->gl_config.depth_size) {
        gl_flags |= BGL_DEPTH;
    }
    ଯଦି (_this->gl_config.stencil_size) {
        gl_flags |= BGL_STENCIL;
    }
    ଯଦି (_this->gl_config.double_buffer) {
        gl_flags |= BGL_DOUBLE;
    } ଅନ୍ୟଥା {
        gl_flags |= BGL_SINGLE;
    }
    ଯଦି (_this->gl_config.accum_red_size ||
            _this->gl_config.accum_green_size ||
            _this->gl_config.accum_blue_size ||
            _this->gl_config.accum_alpha_size) {
        gl_flags |= BGL_ACCUM;
    }
#ଯଦି __GNUC__ > 3
    ଯଦି (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#endif
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->SetCurrentContext(bwin->GetGLView());
    ଫେରନ୍ତୁ (SDL_GLContext)(bwin->GetGLView());
}

ତାର୍କିକ HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->Window();
    ଯଦି (!bwin) {
        delete glView;
    } ଅନ୍ୟଥା {
        bwin->RemoveGLView();
    }
    ଫେରନ୍ତୁ ସତ୍ୟ;
}


ତାର୍କିକ HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval)
{
    // TODO: Implement this, if necessary?
    ଫେରନ୍ତୁ SDL_Unsupported();
}

ତାର୍କିକ HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *interval)
{
    ଫେରନ୍ତୁ SDL_Unsupported();
}


ଶୂନ୍ୟ HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
ଶୂନ୍ୟ HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_Window *window = _this->windows;
    ଯେତେବେଳେ (window) {
        SDL_BWin *bwin = _ToBeWin(window);
        ଯଦି (bwin->GetGLView()) {
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
