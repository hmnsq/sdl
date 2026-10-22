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
#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_HAIKU) && defined(SDL_VIDEO_OPENGL)

#అన్తర్భావ "SDL_bopengl.h"

#అన్తర్భావ <unistd.h>
#అన్తర్భావ <KernelKit.h>
#అన్తర్భావ <OpenGLKit.h>
#అన్తర్భావ "SDL_BWin.h"
#అన్తర్భావ "../../core/haiku/SDL_BApp.h"

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు


స్థిర SDL_INLINE SDL_BWin *గమ్యం_Be_Win(SDL_కిటికీ *కిటికీ)
{
    తిరిగి (SDL_BWin *)(కిటికీ->అంతర్గత);
}

స్థిర SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    తిరిగి SDL_Looper;
}

// Passing a NULL path means load pointers from the application
తార్కిక HAIKU_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
// FIXME: Is this working correctly?
    image_info info;
            int32 cookie = 0;
    అయితే (get_తదుపరి_image_info(0, &cookie, &info) == B_OK) {
        శూన్య *location = ఖాళీ;
        ఒకవేళ ( get_image_చిహ్నం(info.id, "glBegin", B_చిహ్నం_TYPE_ANY,
                &location) == B_OK) {

            _this->gl_config.dll_handle = (SDL_SharedObject *) (addr_t) info.id;
            _this->gl_config.driver_loaded = 1;
            SDL_strlcpy(_this->gl_config.driver_మార్గం, "libGL.so",
                    SDL_arraysize(_this->gl_config.driver_మార్గం));
        }
    }
    తిరిగి నిజం;
}

SDL_Function_సూచిక HAIKU_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc)
{
    ఒకవేళ (_this->gl_config.dll_handle) {
        శూన్య *location = ఖాళీ;
        స్థితి_t err;
        ఒకవేళ ((err =
            get_image_చిహ్నం((image_id) (addr_t) _this->gl_config.dll_handle,
                              proc, B_చిహ్నం_TYPE_ANY,
                              &location)) == B_OK) {
            తిరిగి (SDL_Function_సూచిక)location;
        } లేకపోతే {
                SDL_సమితి_Error("Couldn't find OpenGL symbol");
                తిరిగి ఖాళీ;
        }
    } లేకపోతే {
        SDL_సమితి_Error("OpenGL library not loaded");
        తిరిగి ఖాళీ;
    }
}


తార్కిక HAIKU_GL_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    గమ్యం_Be_Win(కిటికీ)->మార్పిడి_Buffers();
    తిరిగి నిజం;
}

తార్కిక HAIKU_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ, SDL_GLContext context)
{
    BGLView *glView = (BGLView *)context;
    // printf("HAIKU_GL_MakeCurrent(%llx), win = %llx, thread = %d\n", (uint64)context, (uint64)window, find_thread(NULL));
    ఒకవేళ (glView) {
        ఒకవేళ ((glView->కిటికీ_2() == ఖాళీ) || (!కిటికీ) || (గమ్యం_Be_Win(కిటికీ)->GetGLView() != glView)) {
            తిరిగి SDL_సమితి_Error("MakeCurrent failed");
        }
    }
    _GetBeLooper()->సమితి_Current_Context(glView);
    తిరిగి నిజం;
}


SDL_GLContext HAIKU_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    /* FIXME: Not sure what flags should be included here; may want to have
       most of them */
    SDL_BWin *bwin = గమ్యం_Be_Win(కిటికీ);
    // printf("HAIKU_GL_CreateContext, win = %llx, thread = %d\n", (uint64)window, find_thread(NULL));
    ఒకవేళ (bwin->GetGLView() != ఖాళీ) {
        SDL_సమితి_Error("Context already creaded");
        తిరిగి ఖాళీ;
    }
    Uint32 gl_flags = BGL_RGB;
    ఒకవేళ (_this->gl_config.alpha_కొలత) {
        gl_flags |= BGL_ALPHA;
    }
    ఒకవేళ (_this->gl_config.లోతు_కొలత) {
        gl_flags |= BGL_లోతు;
    }
    ఒకవేళ (_this->gl_config.stencil_కొలత) {
        gl_flags |= BGL_STENCIL;
    }
    ఒకవేళ (_this->gl_config.double_బఫరు) {
        gl_flags |= BGL_DOUBLE;
    } లేకపోతే {
        gl_flags |= BGL_SINGLE;
    }
    ఒకవేళ (_this->gl_config.accum_red_కొలత ||
            _this->gl_config.accum_green_కొలత ||
            _this->gl_config.accum_blue_కొలత ||
            _this->gl_config.accum_alpha_కొలత) {
        gl_flags |= BGL_ACCUM;
    }
#ఒకవేళ __GNUC__ > 3
    ఒకవేళ (_this->gl_config.share_with_current_context) {
        gl_flags |= BGL_SHARE_CONTEXT;
    }
#అయితే_ముగింపు
    bwin->CreateGLView(gl_flags);
    _GetBeLooper()->సమితి_Current_Context(bwin->GetGLView());
    తిరిగి (SDL_GLContext)(bwin->GetGLView());
}

తార్కిక HAIKU_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    // printf("HAIKU_GL_DestroyContext(%llx), thread = %d\n", (uint64)context, find_thread(NULL));
    BGLView *glView = (BGLView *)context;
    SDL_BWin *bwin = (SDL_BWin *)glView->కిటికీ_2();
    ఒకవేళ (!bwin) {
        తొలగించు glView;
    } లేకపోతే {
        bwin->RemoveGLView();
    }
    తిరిగి నిజం;
}


తార్కిక HAIKU_GL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval)
{
    // TODO: Implement this, if necessary?
    తిరిగి SDL_Unsupported();
}

తార్కిక HAIKU_GL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval)
{
    తిరిగి SDL_Unsupported();
}


శూన్య HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    // TODO: Implement this, if necessary?
}


/* FIXME: This function is meant to clear the OpenGL context when the video
   mode changes (see SDL_bmodes.cc), but it doesn't seem to help, and is not
   currently in use. */
శూన్య HAIKU_GL_RebootContexts(SDL_VideoDevice *_this)
{
    SDL_కిటికీ *కిటికీ = _this->windows;
    అయితే (కిటికీ) {
        SDL_BWin *bwin = గమ్యం_Be_Win(కిటికీ);
        ఒకవేళ (bwin->GetGLView()) {
            bwin->తాళం_Looper();
            bwin->RemoveGLView();
            bwin->CreateGLView(bwin->GetGLType());
            bwin->UnlockLooper();
        }
        కిటికీ = కిటికీ->తదుపరి;
    }
}


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_HAIKU && SDL_VIDEO_OPENGL
