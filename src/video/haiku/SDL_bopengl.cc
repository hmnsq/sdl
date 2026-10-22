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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bopengl.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <KernelKit.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <OpenGLKit.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_BWin.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/haiku/SDL_BApp.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ


ਸਥਿਰ SDL_INLINE SDL_BWin *ਮੰਜ਼ਿਲ_Be_Win(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਵਾਪਸ (SDL_BWin *)(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
}

ਸਥਿਰ SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ਵਾਪਸ SDL_Looper;
}

// Passing a NULL path means load pointers from the application
ਤਾਰਕਿਕ HAIKU_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    ਜਦੋਂ (get_ਅਗਲਾ_image_info(0, &cookie, &info) == B_OK) {
        ਖਾਲੀ *location = ਨਿਰਾ;
        ਜੇ ( get_image_ਚਿੰਨ੍ਹ(info.id, "glBegin", B_ਚਿੰਨ੍ਹ_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_ਰਸਤਾ, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_ਰਸਤਾ));
        }
    }
    ਵਾਪਸ ਸੱਚ;
}

SDL_Function_ਸੂਚਕ HAIKU_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc)
{
    ਜੇ (_this->gl_config.dll_handle) {
        ਖਾਲੀ *location = ਨਿਰਾ;
        ਸਥਿਤੀ_t err;
        ਜੇ ((err =
            get_image_ਚਿੰਨ੍ਹ((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_ਚਿੰਨ੍ਹ_TYPE_ANY,
                              &location)) == B_OK) {
            ਵਾਪਸ (SDL_Function_ਸੂਚਕ)location;
        } ਨਹੀਂਤਾਂ {
                SDL_ਸੈੱਟ_Error("Couldn't find OpenGL symbol");
                ਵਾਪਸ ਨਿਰਾ;
        }
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Error("OpenGL library not loaded");
        ਵਾਪਸ ਨਿਰਾ;
    }
}


ਤਾਰਕਿਕ HAIKU_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->ਅਦਲਾ_ਬਦਲੀ_Buffers();
    ਵਾਪਸ ਸੱਚ;
}

ਤਾਰਕਿਕ HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    ਜੇ (glView) {
        ਜੇ ((glView->ਖਿੜਕੀ_2() == ਨਿਰਾ) || (!ਖਿੜਕੀ) || (ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->GetGLView() != glView)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("MakeCurrent failed");
        }
    }
    _GetBeLooper()->ਸੈੱਟ_Current_Context(glView);
    ਵਾਪਸ ਸੱਚ;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    ਜੇ (bwin->GetGLView() != ਨਿਰਾ) {
        SDL_ਸੈੱਟ_Error("Context already creaded");
        ਵਾਪਸ ਨਿਰਾ;
    }
    Uint32 gl_flags = BGL_RGB;
    ਜੇ (_this->gl_config.alpha_ਮਾਪ) {
        gl_flags |= BGL_ALPHA;
    }
    ਜੇ (_this->gl_config.ਡੂੰਘਾਈ_ਮਾਪ) {
        gl_flags |= BGL_ਡੂੰਘਾਈ;
    }
    ਜੇ (_this->gl_config.stencil_ਮਾਪ) {
        gl_flags |= BGL_STENCIL;
    }
    ਜੇ (_this->gl_config.double_ਬਫਰ) {
        gl_flags |= BGL_DOUBLE;
    } ਨਹੀਂਤਾਂ {
        gl_flags |= BGL_SINGLE;
    }
    ਜੇ (_this->gl_config.accum_red_ਮਾਪ ||
            _this->gl_config.accum_green_ਮਾਪ ||
            _this->gl_config.accum_blue_ਮਾਪ ||
            _this->gl_config.accum_alpha_ਮਾਪ) {
        gl_flags |= BGL_ACCUM;
    }
#ਜੇ __GNUC__ > 3
    ਜੇ (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#ਜੇ_ਅੰਤ
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->ਸੈੱਟ_Current_Context(bwin->GetGLView());
    ਵਾਪਸ (SDL_GLContext)(bwin->GetGLView());
}

ਤਾਰਕਿਕ HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->ਖਿੜਕੀ_2();
    ਜੇ (!bwin) {
        ਮਿਟਾਓ glView;
    } ਨਹੀਂਤਾਂ {
        bwin->RemoveGLView();
    }
    ਵਾਪਸ ਸੱਚ;
}


ਤਾਰਕਿਕ HAIKU_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval)
{
    // TODO: Implement this, if necessary?
    ਵਾਪਸ SDL_Unsupported();
}

ਤਾਰਕਿਕ HAIKU_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval)
{
    ਵਾਪਸ SDL_Unsupported();
}


ਖਾਲੀ HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
ਖਾਲੀ HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = _this->windows;
    ਜਦੋਂ (ਖਿੜਕੀ) {
        SDL_BWin *bwin = ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ);
        ਜੇ (bwin->GetGLView()) {
            bwin->ਤਾਲਾ_Looper();
            bwin->RemoveGLView();
            bwin->CreateGLView(bwin->GetGLType());
            bwin->UnlockLooper();
        }
        ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ;
    }
}


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL
