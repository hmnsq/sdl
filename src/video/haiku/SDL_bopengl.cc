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
#include "SDL_internal.h"

#만약 defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#include "SDL_bopengl.h"

#include <unistd.h>
#include <KernelKit.h>
#include <OpenGLKit.h>
#include "SDL_BWin.h"
#include "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
extern "C" {
#endif


static SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    반환 (SDL_BWin *)(window->internal);
}

static SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    반환 SDL_Looper;
}

// Passing a NULL path means load pointers from the application
bool HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, const char *path)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    동안 (get_next_image_info(0, &cookie, &info) == B_OK) {
        void *location = NULL;
        만약 ( get_image_symbol(info.id, "glBegin", B_SYMBOL_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_path, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_path));
        }
    }
    반환 true;
}

SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, const char *proc)
{
    만약 (_this->gl_config.dll_handle) {
        void *location = NULL;
        status_t err;
        만약 ((err =
            get_image_symbol((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_SYMBOL_TYPE_ANY,
                              &location)) == B_OK) {
            반환 (SDL_FunctionPointer)location;
        } 아니면 {
                SDL_SetError("Couldn't find OpenGL symbol");
                반환 NULL;
        }
    } 아니면 {
        SDL_SetError("OpenGL library not loaded");
        반환 NULL;
    }
}


bool HAIKU_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->SwapBuffers();
    반환 true;
}

bool HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    만약 (glView) {
        만약 ((glView->Window() == NULL) || (!window) || (_ToBeWin(window)->GetGLView() != glView)) {
            반환 SDL_SetError("MakeCurrent failed");
        }
    }
    _GetBeLooper()->SetCurrentContext(glView);
    반환 true;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = _ToBeWin(window);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    만약 (bwin->GetGLView() != NULL) {
        SDL_SetError("Context already creaded");
        반환 NULL;
    }
    Uint32 gl_flags = BGL_RGB;
    만약 (_this->gl_config.alpha_size) {
        gl_flags |= BGL_ALPHA;
    }
    만약 (_this->gl_config.depth_size) {
        gl_flags |= BGL_DEPTH;
    }
    만약 (_this->gl_config.stencil_size) {
        gl_flags |= BGL_STENCIL;
    }
    만약 (_this->gl_config.double_buffer) {
        gl_flags |= BGL_DOUBLE;
    } 아니면 {
        gl_flags |= BGL_SINGLE;
    }
    만약 (_this->gl_config.accum_red_size ||
            _this->gl_config.accum_green_size ||
            _this->gl_config.accum_blue_size ||
            _this->gl_config.accum_alpha_size) {
        gl_flags |= BGL_ACCUM;
    }
#만약 __GNUC__ > 3
    만약 (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#endif
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->SetCurrentContext(bwin->GetGLView());
    반환 (SDL_GLContext)(bwin->GetGLView());
}

bool HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->Window();
    만약 (!bwin) {
        delete glView;
    } 아니면 {
        bwin->RemoveGLView();
    }
    반환 true;
}


bool HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, 정수 interval)
{
    // TODO: Implement this, if necessary?
    반환 SDL_Unsupported();
}

bool HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, 정수 *interval)
{
    반환 SDL_Unsupported();
}


void HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
void HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_Window *window = _this->windows;
    동안 (window) {
        SDL_BWin *bwin = _ToBeWin(window);
        만약 (bwin->GetGLView()) {
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
