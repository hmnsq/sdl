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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#ಅನ್ತರ್ಭಾವ "SDL_bopengl.h"

#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <KernelKit.h>
#ಅನ್ತರ್ಭಾವ <OpenGLKit.h>
#ಅನ್ತರ್ಭಾವ "SDL_BWin.h"
#ಅನ್ತರ್ಭಾವ "../../core/haiku/SDL_BApp.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ


ಸ್ಥಿರ SDL_INLINE SDL_BWin *ಗಮ್ಯ_Be_Win(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ (SDL_BWin *)(ಕಿಟಕಿ->ಆಂತರಿಕ);
}

ಸ್ಥಿರ SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ಹಿಂತಿರುಗಿ SDL_Looper;
}

// Passing a NULL path means load pointers from the application
ತಾರ್ಕಿಕ HAIKU_GL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    ಆಗ (get_ಮುಂದಿನ_image_info(0, &cookie, &info) == B_OK) {
        ಶೂನ್ಯ *location = ಖಾಲಿ;
        ಆದರೆ ( get_image_ಚಿಹ್ನೆ(info.id, "glBegin", B_ಚಿಹ್ನೆ_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_ಮಾರ್ಗ, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_ಮಾರ್ಗ));
        }
    }
    ಹಿಂತಿರುಗಿ ನಿಜ;
}

SDL_Function_ಸೂಚಕ HAIKU_GL_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc)
{
    ಆದರೆ (_this->gl_config.dll_handle) {
        ಶೂನ್ಯ *location = ಖಾಲಿ;
        ಸ್ಥಿತಿ_t err;
        ಆದರೆ ((err =
            get_image_ಚಿಹ್ನೆ((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_ಚಿಹ್ನೆ_TYPE_ANY,
                              &location)) == B_OK) {
            ಹಿಂತಿರುಗಿ (SDL_Function_ಸೂಚಕ)location;
        } ಇಲ್ಲದಿದ್ದರೆ {
                SDL_ಗಣ_Error("Couldn't find OpenGL symbol");
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Error("OpenGL library not loaded");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
}


ತಾರ್ಕಿಕ HAIKU_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->ಅದಲುಬದಲು_Buffers();
    ಹಿಂತಿರುಗಿ ನಿಜ;
}

ತಾರ್ಕಿಕ HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    ಆದರೆ (glView) {
        ಆದರೆ ((glView->ಕಿಟಕಿ_2() == ಖಾಲಿ) || (!ಕಿಟಕಿ) || (ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->GetGLView() != glView)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("MakeCurrent failed");
        }
    }
    _GetBeLooper()->ಗಣ_Current_Context(glView);
    ಹಿಂತಿರುಗಿ ನಿಜ;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    ಆದರೆ (bwin->GetGLView() != ಖಾಲಿ) {
        SDL_ಗಣ_Error("Context already creaded");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    Uint32 gl_flags = BGL_RGB;
    ಆದರೆ (_this->gl_config.alpha_ಗಾತ್ರ) {
        gl_flags |= BGL_ALPHA;
    }
    ಆದರೆ (_this->gl_config.ಆಳ_ಗಾತ್ರ) {
        gl_flags |= BGL_ಆಳ;
    }
    ಆದರೆ (_this->gl_config.stencil_ಗಾತ್ರ) {
        gl_flags |= BGL_STENCIL;
    }
    ಆದರೆ (_this->gl_config.double_ಬಫರ್) {
        gl_flags |= BGL_DOUBLE;
    } ಇಲ್ಲದಿದ್ದರೆ {
        gl_flags |= BGL_SINGLE;
    }
    ಆದರೆ (_this->gl_config.accum_red_ಗಾತ್ರ ||
            _this->gl_config.accum_green_ಗಾತ್ರ ||
            _this->gl_config.accum_blue_ಗಾತ್ರ ||
            _this->gl_config.accum_alpha_ಗಾತ್ರ) {
        gl_flags |= BGL_ACCUM;
    }
#ಆದರೆ __GNUC__ > 3
    ಆದರೆ (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#ಆದರೆ_ಅಂತ್ಯ
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->ಗಣ_Current_Context(bwin->GetGLView());
    ಹಿಂತಿರುಗಿ (SDL_GLContext)(bwin->GetGLView());
}

ತಾರ್ಕಿಕ HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->ಕಿಟಕಿ_2();
    ಆದರೆ (!bwin) {
        ಅಳಿಸು glView;
    } ಇಲ್ಲದಿದ್ದರೆ {
        bwin->RemoveGLView();
    }
    ಹಿಂತಿರುಗಿ ನಿಜ;
}


ತಾರ್ಕಿಕ HAIKU_GL_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval)
{
    // TODO: Implement this, if necessary?
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

ತಾರ್ಕಿಕ HAIKU_GL_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval)
{
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
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
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = _this->windows;
    ಆಗ (ಕಿಟಕಿ) {
        SDL_BWin *bwin = ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ);
        ಆದರೆ (bwin->GetGLView()) {
            bwin->ಬೀಗ_Looper();
            bwin->RemoveGLView();
            bwin->CreateGLView(bwin->GetGLType());
            bwin->UnlockLooper();
        }
        ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ;
    }
}


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL
