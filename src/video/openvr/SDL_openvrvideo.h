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
#include "openvr_capi.h"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#include <stdint.h>

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#include <GLES3/gl3.h>
#include <GLES3/gl32.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2ext.h>

#endif


struct SDL_WindowData
{
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#инако
    цео dummy;
#endif
};

struct SDL_VideoData {
    void * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    const char *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( const char *pchInterfaceVersion, EVRInitError *peError );

    цео is_buffer_rendering;

    unsigned цео overlaytexture;

    unsigned цео fbo, rbo;

    цео saved_texture_state;

    struct VR_IVRSystem_FnTable *oSystem;
    struct VR_IVROverlay_FnTable *oOverlay;
	struct VR_IVRInput_FnTable * oInput;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	char * sOverlayName;

	VRActionSetHandle_t input_action_set;
	VRActionHandle_t * input_action_handles_buttons;
	цео input_action_handles_buttons_count;
	VRActionHandle_t * input_action_handles_axes;
	цео input_action_handles_axes_count;
	VRActionHandle_t input_action_handles_haptics[2];

    bool bHasShownOverlay;
    цео targw, targh;
    цео last_targw, last_targh;
    цео swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_end;
	bool bIconOverridden;
	
	SDL_Window * window;
	
	SDL_Joystick *virtual_joystick;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#инако
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#endif
};

struct SDL_DisplayData
{
    цео dummy;
};

#endif
