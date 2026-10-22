#ifndef _SDL_OPENVRVIDEO_H
#define _SDL_OPENVRVIDEO_H

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ifdef EXTERN_C
#undef EXTERN_C
#endif
#endif

// OpenVR has a LOT of unused variables that GCC will freak out on.
#ifdef __GNUC__
#pragma GCC diagnostic ଠେଲ
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#define USE_SDL
#ଅନ୍ତର୍ଭାଵ "openvr_capi.h"

#ifdef __GNUC__
#pragma GCC diagnostic କାଢ଼
#endif

#ଅନ୍ତର୍ଭାଵ <stdint.h>

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#ଅନ୍ତର୍ଭାଵ <GLES3/gl3.h>
#ଅନ୍ତର୍ଭାଵ <GLES3/gl32.h>
#ଅନ୍ତର୍ଭାଵ <EGL/egl.h>
#ଅନ୍ତର୍ଭାଵ <GLES2/gl2.h>
#ଅନ୍ତର୍ଭାଵ <GLES2/gl2ext.h>
#ଅନ୍ତର୍ଭାଵ <GLES2/gl2ext.h>

#endif


ସଂରଚନା SDL_WindowData
{
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#ଅନ୍ୟଥା
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dummy;
#endif
};

ସଂରଚନା SDL_VideoData {
    ଶୂନ୍ୟ * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    ଅଚଳ ଅକ୍ଷର *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ଅଚଳ ଅକ୍ଷର *pchInterfaceVersion, EVRInitError *peError );

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_buffer_rendering;

    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା overlaytexture;

    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା fbo, rbo;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା saved_texture_state;

    ସଂରଚନା VR_IVRSystem_FnTable *oSystem;
    ସଂରଚନା VR_IVROverlay_FnTable *oOverlay;
	ସଂରଚନା VR_IVRInput_FnTable * o_ନିବେଶ;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	ଅକ୍ଷର * sOverlayName;

	VRActionSetHandle_t ନିବେଶ_action_set;
	VRActionHandle_t * ନିବେଶ_action_handles_buttons;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ନିବେଶ_action_handles_buttons_ଗଣନା;
	VRActionHandle_t * ନିବେଶ_action_handles_axes;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ନିବେଶ_action_handles_axes_ଗଣନା;
	VRActionHandle_t ନିବେଶ_action_handles_haptics[2];

    bool bHasShownOverlay;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା targw, targh;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା last_targw, last_targh;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_end;
	bool bIconOverridden;
	
	SDL_Window * window;
	
	SDL_Joystick *virtual_joystick;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#ଅନ୍ୟଥା
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#endif
};

ସଂରଚନା SDL_DisplayData
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dummy;
};

#endif
