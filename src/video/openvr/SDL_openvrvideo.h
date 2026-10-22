#ifndef _SDL_OPENVRVIDEO_H
#define _SDL_OPENVRVIDEO_H

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ifdef EXTERN_C
#undef EXTERN_C
#endif
#endif

// OpenVR has a LOT of unused variables that GCC will freak out on.
#ifdef __GNUC__
#pragma GCC diagnostic افزودن
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#define USE_SDL
#شامل "openvr_capi.h"

#ifdef __GNUC__
#pragma GCC diagnostic برداشت
#endif

#شامل <stdint.h>

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#شامل <GLES3/gl3.h>
#شامل <GLES3/gl32.h>
#شامل <EGL/egl.h>
#شامل <GLES2/gl2.h>
#شامل <GLES2/gl2ext.h>
#شامل <GLES2/gl2ext.h>

#endif


ساختار SDL_WindowData
{
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#وگرنه
    صحیح dummy;
#endif
};

ساختار SDL_VideoData {
    تهی * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    ثابت نویسه *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ثابت نویسه *pchInterfaceVersion, EVRInitError *peError );

    صحیح is_buffer_rendering;

    unsigned صحیح overlaytexture;

    unsigned صحیح fbo, rbo;

    صحیح saved_texture_state;

    ساختار VR_IVRSystem_FnTable *oSystem;
    ساختار VR_IVROverlay_FnTable *oOverlay;
	ساختار VR_IVRInput_FnTable * o_درون_داد;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	نویسه * sOverlayName;

	VRActionSetHandle_t درون_داد_action_set;
	VRActionHandle_t * درون_داد_action_handles_buttons;
	صحیح درون_داد_action_handles_buttons_شمار;
	VRActionHandle_t * درون_داد_action_handles_axes;
	صحیح درون_داد_action_handles_axes_شمار;
	VRActionHandle_t درون_داد_action_handles_haptics[2];

    bool bHasShownOverlay;
    صحیح targw, targh;
    صحیح last_targw, last_targh;
    صحیح swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_end;
	bool bIconOverridden;
	
	SDL_Window * window;
	
	SDL_Joystick *virtual_joystick;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#وگرنه
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#endif
};

ساختار SDL_DisplayData
{
    صحیح dummy;
};

#endif
