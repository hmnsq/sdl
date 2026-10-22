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
#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#समावेश "SDL_bopengl.h"

#समावेश <unistd.h>
#समावेश <KernelKit.h>
#समावेश <OpenGLKit.h>
#समावेश "SDL_BWin.h"
#समावेश "../../core/haiku/SDL_BApp.h"

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर


अटल SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    वापस (SDL_BWin *)(window->internal);
}

अटल SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    वापस SDL_Looper;
}

// Passing a NULL path means load pointers from the application
bool HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    जबतक (get_अग्र_image_info(0, &cookie, &info) == B_OK) {
        व्योम *location = शून्य;
        अगर ( get_image_प्रतीक(info.id, "glBegin", B_प्रतीक_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_path, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_path));
        }
    }
    वापस true;
}

SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc)
{
    अगर (_this->gl_config.dll_handle) {
        व्योम *location = शून्य;
        status_t err;
        अगर ((err =
            get_image_प्रतीक((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_प्रतीक_TYPE_ANY,
                              &location)) == B_OK) {
            वापस (SDL_FunctionPointer)location;
        } अन्यथा {
                SDL_SetError("Couldn't find OpenGL symbol");
                वापस शून्य;
        }
    } अन्यथा {
        SDL_SetError("OpenGL library not loaded");
        वापस शून्य;
    }
}


bool HAIKU_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->SwapBuffers();
    वापस true;
}

bool HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * window, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    अगर (glView) {
        अगर ((glView->Window() == शून्य) || (!window) || (_ToBeWin(window)->GetGLView() != glView)) {
            वापस SDL_SetError("MakeCurrent failed");
        }
    }
    _GetBeLooper()->SetCurrentContext(glView);
    वापस true;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = _ToBeWin(window);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    अगर (bwin->GetGLView() != शून्य) {
        SDL_SetError("Context already creaded");
        वापस शून्य;
    }
    Uint32 gl_flags = BGL_RGB;
    अगर (_this->gl_config.alpha_आकार) {
        gl_flags |= BGL_ALPHA;
    }
    अगर (_this->gl_config.depth_आकार) {
        gl_flags |= BGL_DEPTH;
    }
    अगर (_this->gl_config.stencil_आकार) {
        gl_flags |= BGL_STENCIL;
    }
    अगर (_this->gl_config.double_बफर) {
        gl_flags |= BGL_DOUBLE;
    } अन्यथा {
        gl_flags |= BGL_SINGLE;
    }
    अगर (_this->gl_config.accum_red_आकार ||
            _this->gl_config.accum_green_आकार ||
            _this->gl_config.accum_blue_आकार ||
            _this->gl_config.accum_alpha_आकार) {
        gl_flags |= BGL_ACCUM;
    }
#अगर __GNUC__ > 3
    अगर (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#पूर्ण_अगर
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->SetCurrentContext(bwin->GetGLView());
    वापस (SDL_GLContext)(bwin->GetGLView());
}

bool HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->Window();
    अगर (!bwin) {
        मिटाओ glView;
    } अन्यथा {
        bwin->RemoveGLView();
    }
    वापस true;
}


bool HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval)
{
    // TODO: Implement this, if necessary?
    वापस SDL_Unsupported();
}

bool HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval)
{
    वापस SDL_Unsupported();
}


व्योम HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
व्योम HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_Window *window = _this->windows;
    जबतक (window) {
        SDL_BWin *bwin = _ToBeWin(window);
        अगर (bwin->GetGLView()) {
            bwin->LockLooper();
            bwin->RemoveGLView();
            bwin->CreateGLView(bwin->GetGLType());
            bwin->UnlockLooper();
        }
        window = window->अग्र;
    }
}


#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL
