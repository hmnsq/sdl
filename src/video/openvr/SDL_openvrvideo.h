#ifndef _SDL_OPENVRVIDEO_H
#define _SDL_OPENVRVIDEO_H

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ifdef EXTERN_C
#undef EXTERN_C
#endif
#endif

// OpenVR has a LOT of unused variables that GCC will freak out on.
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#define USE_SDL
#ضمن "openvr_capi.h"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ضمن <stdint.h>

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#ضمن <GLES3/gl3.h>
#ضمن <GLES3/gl32.h>
#ضمن <EGL/egl.h>
#ضمن <GLES2/gl2.h>
#ضمن <GLES2/gl2ext.h>
#ضمن <GLES2/gl2ext.h>

#endif


بنية SDL_WindowData
{
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#وإلا
    صحيح dummy;
#endif
};

بنية SDL_VideoData {
    فراغ * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    ثابت حرف *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ثابت حرف *pchInterfaceVersion, EVRInitError *peError );

    صحيح is_buffer_rendering;

    unsigned صحيح overlaytexture;

    unsigned صحيح fbo, rbo;

    صحيح saved_texture_state;

    بنية VR_IVRSystem_FnTable *oSystem;
    بنية VR_IVROverlay_FnTable *oOverlay;
	بنية VR_IVRInput_FnTable * oInput;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	حرف * sOverlayName;

	VRActionSetHandle_t input_action_set;
	VRActionHandle_t * input_action_handles_buttons;
	صحيح input_action_handles_buttons_count;
	VRActionHandle_t * input_action_handles_axes;
	صحيح input_action_handles_axes_count;
	VRActionHandle_t input_action_handles_haptics[2];

    bool bHasShownOverlay;
    صحيح targw, targh;
    صحيح last_targw, last_targh;
    صحيح swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_end;
	bool bIconOverridden;
	
	SDL_Window * window;
	
	SDL_Joystick *virtual_joystick;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#وإلا
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#endif
};

بنية SDL_DisplayData
{
    صحيح dummy;
};

#endif
