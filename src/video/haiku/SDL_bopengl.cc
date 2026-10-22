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

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः


स्थिर SDL_INLINE SDL_BWin *गन्तव्यम्_Be_Win(SDL_गवाक्षः *गवाक्षः)
{
    प्रत्यागम (SDL_BWin *)(गवाक्षः->आन्तरिकम्);
}

स्थिर SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    प्रत्यागम SDL_Looper;
}

// Passing a NULL path means load pointers from the application
तार्किक HAIKU_GL_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    यावत् (get_अग्र_image_info(0, &cookie, &info) == B_OK) {
        शून्य *location = रिक्त;
        यदि ( get_image_चिह्नम्(info.id, "glBegin", B_चिह्नम्_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_मार्गः, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_मार्गः));
        }
    }
    प्रत्यागम सत्य;
}

SDL_FunctionPointer HAIKU_GL_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc)
{
    यदि (_this->gl_config.dll_handle) {
        शून्य *location = रिक्त;
        स्थितिः_t err;
        यदि ((err =
            get_image_चिह्नम्((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_चिह्नम्_TYPE_ANY,
                              &location)) == B_OK) {
            प्रत्यागम (SDL_FunctionPointer)location;
        } अन्यथा {
                SDL_समुच्चयः_Error("Couldn't find OpenGL symbol");
                प्रत्यागम रिक्त;
        }
    } अन्यथा {
        SDL_समुच्चयः_Error("OpenGL library not loaded");
        प्रत्यागम रिक्त;
    }
}


तार्किक HAIKU_GL_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    गन्तव्यम्_Be_Win(गवाक्षः)->SwapBuffers();
    प्रत्यागम सत्य;
}

तार्किक HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    यदि (glView) {
        यदि ((glView->गवाक्षः_2() == रिक्त) || (!गवाक्षः) || (गन्तव्यम्_Be_Win(गवाक्षः)->GetGLView() != glView)) {
            प्रत्यागम SDL_समुच्चयः_Error("MakeCurrent failed");
        }
    }
    _GetBeLooper()->समुच्चयः_Current_Context(glView);
    प्रत्यागम सत्य;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = गन्तव्यम्_Be_Win(गवाक्षः);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    यदि (bwin->GetGLView() != रिक्त) {
        SDL_समुच्चयः_Error("Context already creaded");
        प्रत्यागम रिक्त;
    }
    Uint32 gl_flags = BGL_RGB;
    यदि (_this->gl_config.alpha_आकार) {
        gl_flags |= BGL_ALPHA;
    }
    यदि (_this->gl_config.गभीरता_आकार) {
        gl_flags |= BGL_गभीरता;
    }
    यदि (_this->gl_config.stencil_आकार) {
        gl_flags |= BGL_STENCIL;
    }
    यदि (_this->gl_config.double_बफर) {
        gl_flags |= BGL_DOUBLE;
    } अन्यथा {
        gl_flags |= BGL_SINGLE;
    }
    यदि (_this->gl_config.accum_red_आकार ||
            _this->gl_config.accum_green_आकार ||
            _this->gl_config.accum_blue_आकार ||
            _this->gl_config.accum_alpha_आकार) {
        gl_flags |= BGL_ACCUM;
    }
#यदि __GNUC__ > 3
    यदि (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#यदि_अन्तः
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->समुच्चयः_Current_Context(bwin->GetGLView());
    प्रत्यागम (SDL_GLContext)(bwin->GetGLView());
}

तार्किक HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->गवाक्षः_2();
    यदि (!bwin) {
        विलोपय glView;
    } अन्यथा {
        bwin->RemoveGLView();
    }
    प्रत्यागम सत्य;
}


तार्किक HAIKU_GL_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval)
{
    // TODO: Implement this, if necessary?
    प्रत्यागम SDL_Unsupported();
}

तार्किक HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval)
{
    प्रत्यागम SDL_Unsupported();
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
    SDL_गवाक्षः *गवाक्षः = _this->windows;
    यावत् (गवाक्षः) {
        SDL_BWin *bwin = गन्तव्यम्_Be_Win(गवाक्षः);
        यदि (bwin->GetGLView()) {
            bwin->तालकम्_Looper();
            bwin->RemoveGLView();
            bwin->CreateGLView(bwin->GetGLType());
            bwin->UnlockLooper();
        }
        गवाक्षः = गवाक्षः->अग्र;
    }
}


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL
