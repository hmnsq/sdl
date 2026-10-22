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
#અન્તર્ભાવ "SDL_internal.h"

#જો defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#અન્તર્ભાવ "SDL_bopengl.h"

#અન્તર્ભાવ <unistd.h>
#અન્તર્ભાવ <KernelKit.h>
#અન્તર્ભાવ <OpenGLKit.h>
#અન્તર્ભાવ "SDL_BWin.h"
#અન્તર્ભાવ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
બાહ્ય "C" {
#endif


સ્થિર SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    પાછા (SDL_BWin *)(window->internal);
}

સ્થિર SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    પાછા SDL_Looper;
}

// Passing a NULL path means load pointers from the application
તાર્કિક HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, અચલ અક્ષર *path)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    જ્યારે (get_next_image_info(0, &cookie, &info) == B_OK) {
        શૂન્ય *location = ખાલી;
        જો ( get_image_પ્રતીક(info.id, "glBegin", B_પ્રતીક_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_path, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_path));
        }
    }
    પાછા સાચું;
}

SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, અચલ અક્ષર *proc)
{
    જો (_this->gl_config.dll_handle) {
        શૂન્ય *location = ખાલી;
        status_t err;
        જો ((err =
            get_image_પ્રતીક((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_પ્રતીક_TYPE_ANY,
                              &location)) == B_OK) {
            પાછા (SDL_FunctionPointer)location;
        } નહીંતર {
                SDL_SetError("Couldn't find OpenGL symbol");
                પાછા ખાલી;
        }
    } નહીંતર {
        SDL_SetError("OpenGL library not loaded");
        પાછા ખાલી;
    }
}


તાર્કિક HAIKU_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->SwapBuffers();
    પાછા સાચું;
}

તાર્કિક HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    જો (glView) {
        જો ((glView->Window() == ખાલી) || (!window) || (_ToBeWin(window)->GetGLView() != glView)) {
            પાછા SDL_SetError("MakeCurrent failed");
        }
    }
    _GetBeLooper()->SetCurrentContext(glView);
    પાછા સાચું;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = _ToBeWin(window);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    જો (bwin->GetGLView() != ખાલી) {
        SDL_SetError("Context already creaded");
        પાછા ખાલી;
    }
    Uint32 gl_flags = BGL_RGB;
    જો (_this->gl_config.alpha_size) {
        gl_flags |= BGL_ALPHA;
    }
    જો (_this->gl_config.depth_size) {
        gl_flags |= BGL_DEPTH;
    }
    જો (_this->gl_config.stencil_size) {
        gl_flags |= BGL_STENCIL;
    }
    જો (_this->gl_config.double_buffer) {
        gl_flags |= BGL_DOUBLE;
    } નહીંતર {
        gl_flags |= BGL_SINGLE;
    }
    જો (_this->gl_config.accum_red_size ||
            _this->gl_config.accum_green_size ||
            _this->gl_config.accum_blue_size ||
            _this->gl_config.accum_alpha_size) {
        gl_flags |= BGL_ACCUM;
    }
#જો __GNUC__ > 3
    જો (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#endif
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->SetCurrentContext(bwin->GetGLView());
    પાછા (SDL_GLContext)(bwin->GetGLView());
}

તાર્કિક HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->Window();
    જો (!bwin) {
        delete glView;
    } નહીંતર {
        bwin->RemoveGLView();
    }
    પાછા સાચું;
}


તાર્કિક HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, પૂર્ણાંક interval)
{
    // TODO: Implement this, if necessary?
    પાછા SDL_Unsupported();
}

તાર્કિક HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, પૂર્ણાંક *interval)
{
    પાછા SDL_Unsupported();
}


શૂન્ય HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
શૂન્ય HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_Window *window = _this->windows;
    જ્યારે (window) {
        SDL_BWin *bwin = _ToBeWin(window);
        જો (bwin->GetGLView()) {
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
