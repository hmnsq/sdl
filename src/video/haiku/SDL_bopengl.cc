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
#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#അന്തര്ഭാവ "SDL_bopengl.h"

#അന്തര്ഭാവ <unistd.h>
#അന്തര്ഭാവ <KernelKit.h>
#അന്തര്ഭാവ <OpenGLKit.h>
#അന്തര്ഭാവ "SDL_BWin.h"
#അന്തര്ഭാവ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
ബാഹ്യ "C" {
#endif


സ്ഥിതം SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    തിരികെ (SDL_BWin *)(window->internal);
}

സ്ഥിതം SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    തിരികെ SDL_Looper;
}

// Passing a NULL path means load pointers from the application
തർക്കം HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    ആകുമ്പോൾ (get_next_image_info(0, &cookie, &info) == B_OK) {
        ശൂന്യം *location = ശൂന്യ;
        എങ്കിൽ ( get_image_ചിഹ്നം(info.id, "glBegin", B_ചിഹ്നം_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_path, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_path));
        }
    }
    തിരികെ സത്യം;
}

SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc)
{
    എങ്കിൽ (_this->gl_config.dll_handle) {
        ശൂന്യം *location = ശൂന്യ;
        status_t err;
        എങ്കിൽ ((err =
            get_image_ചിഹ്നം((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_ചിഹ്നം_TYPE_ANY,
                              &location)) == B_OK) {
            തിരികെ (SDL_FunctionPointer)location;
        } അല്ലെങ്കിൽ {
                SDL_SetError("Couldn't find OpenGL symbol");
                തിരികെ ശൂന്യ;
        }
    } അല്ലെങ്കിൽ {
        SDL_SetError("OpenGL library not loaded");
        തിരികെ ശൂന്യ;
    }
}


തർക്കം HAIKU_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->SwapBuffers();
    തിരികെ സത്യം;
}

തർക്കം HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    എങ്കിൽ (glView) {
        എങ്കിൽ ((glView->Window() == ശൂന്യ) || (!window) || (_ToBeWin(window)->GetGLView() != glView)) {
            തിരികെ SDL_SetError("MakeCurrent failed");
        }
    }
    _GetBeLooper()->SetCurrentContext(glView);
    തിരികെ സത്യം;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = _ToBeWin(window);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    എങ്കിൽ (bwin->GetGLView() != ശൂന്യ) {
        SDL_SetError("Context already creaded");
        തിരികെ ശൂന്യ;
    }
    Uint32 gl_flags = BGL_RGB;
    എങ്കിൽ (_this->gl_config.alpha_size) {
        gl_flags |= BGL_ALPHA;
    }
    എങ്കിൽ (_this->gl_config.depth_size) {
        gl_flags |= BGL_DEPTH;
    }
    എങ്കിൽ (_this->gl_config.stencil_size) {
        gl_flags |= BGL_STENCIL;
    }
    എങ്കിൽ (_this->gl_config.double_buffer) {
        gl_flags |= BGL_DOUBLE;
    } അല്ലെങ്കിൽ {
        gl_flags |= BGL_SINGLE;
    }
    എങ്കിൽ (_this->gl_config.accum_red_size ||
            _this->gl_config.accum_green_size ||
            _this->gl_config.accum_blue_size ||
            _this->gl_config.accum_alpha_size) {
        gl_flags |= BGL_ACCUM;
    }
#എങ്കിൽ __GNUC__ > 3
    എങ്കിൽ (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#endif
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->SetCurrentContext(bwin->GetGLView());
    തിരികെ (SDL_GLContext)(bwin->GetGLView());
}

തർക്കം HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->Window();
    എങ്കിൽ (!bwin) {
        delete glView;
    } അല്ലെങ്കിൽ {
        bwin->RemoveGLView();
    }
    തിരികെ സത്യം;
}


തർക്കം HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval)
{
    // TODO: Implement this, if necessary?
    തിരികെ SDL_Unsupported();
}

തർക്കം HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ *interval)
{
    തിരികെ SDL_Unsupported();
}


ശൂന്യം HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
ശൂന്യം HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_Window *window = _this->windows;
    ആകുമ്പോൾ (window) {
        SDL_BWin *bwin = _ToBeWin(window);
        എങ്കിൽ (bwin->GetGLView()) {
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
