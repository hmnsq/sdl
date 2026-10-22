#ifndef _SDL_OPENVRVIDEO_H
#define _SDL_OPENVRVIDEO_H

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ifdef EXTERN_C
#undef EXTERN_C
#endif
#endif

// OpenVR has a LOT of unused variables that GCC will freak out on.
#ifdef __GNUC__
#pragma GCC diagnostic ढकला
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#define USE_SDL
#अन्तर्भाव "openvr_capi.h"

#ifdef __GNUC__
#pragma GCC diagnostic काढा
#endif

#अन्तर्भाव <stdint.h>

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#अन्तर्भाव <GLES3/gl3.h>
#अन्तर्भाव <GLES3/gl32.h>
#अन्तर्भाव <EGL/egl.h>
#अन्तर्भाव <GLES2/gl2.h>
#अन्तर्भाव <GLES2/gl2ext.h>
#अन्तर्भाव <GLES2/gl2ext.h>

#endif


संरचना SDL_WindowData
{
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#अन्यथा
    पूर्णाङ्क dummy;
#endif
};

संरचना SDL_VideoData {
    शून्य * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    ध्रुव वर्ण *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ध्रुव वर्ण *pchInterfaceVersion, EVRInitError *peError );

    पूर्णाङ्क is_buffer_rendering;

    unsigned पूर्णाङ्क overlaytexture;

    unsigned पूर्णाङ्क fbo, rbo;

    पूर्णाङ्क saved_texture_state;

    संरचना VR_IVRSystem_FnTable *oSystem;
    संरचना VR_IVROverlay_FnTable *oOverlay;
	संरचना VR_IVRInput_FnTable * o_आदान;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	वर्ण * sOverlayName;

	VRActionSetHandle_t आदान_action_set;
	VRActionHandle_t * आदान_action_handles_buttons;
	पूर्णाङ्क आदान_action_handles_buttons_मोजणी;
	VRActionHandle_t * आदान_action_handles_axes;
	पूर्णाङ्क आदान_action_handles_axes_मोजणी;
	VRActionHandle_t आदान_action_handles_haptics[2];

    bool bHasShownOverlay;
    पूर्णाङ्क targw, targh;
    पूर्णाङ्क last_targw, last_targh;
    पूर्णाङ्क swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_end;
	bool bIconOverridden;
	
	SDL_Window * window;
	
	SDL_Joystick *virtual_joystick;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#अन्यथा
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#endif
};

संरचना SDL_DisplayData
{
    पूर्णाङ्क dummy;
};

#endif
