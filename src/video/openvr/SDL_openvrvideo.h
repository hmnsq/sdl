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


sa_nracanaa SDL_WindowData
{
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#မဟုတ်ပါက
    ကိန်းပြည့် dummy;
#endif
};

sa_nracanaa SDL_VideoData {
    void * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    const var_na *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( const var_na *pchInterfaceVersion, EVRInitError *peError );

    ကိန်းပြည့် is_buffer_rendering;

    unsigned ကိန်းပြည့် overlaytexture;

    unsigned ကိန်းပြည့် fbo, rbo;

    ကိန်းပြည့် saved_texture_state;

    sa_nracanaa VR_IVRSystem_FnTable *oSystem;
    sa_nracanaa VR_IVROverlay_FnTable *oOverlay;
	sa_nracanaa VR_IVRInput_FnTable * oInput;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	var_na * sOverlayName;

	VRActionSetHandle_t input_action_set;
	VRActionHandle_t * input_action_handles_buttons;
	ကိန်းပြည့် input_action_handles_buttons_count;
	VRActionHandle_t * input_action_handles_axes;
	ကိန်းပြည့် input_action_handles_axes_count;
	VRActionHandle_t input_action_handles_haptics[2];

    bool bHasShownOverlay;
    ကိန်းပြည့် targw, targh;
    ကိန်းပြည့် last_targw, last_targh;
    ကိန်းပြည့် swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_end;
	bool bIconOverridden;
	
	SDL_Window * window;
	
	SDL_Joystick *virtual_joystick;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#မဟုတ်ပါက
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#endif
};

sa_nracanaa SDL_DisplayData
{
    ကိန်းပြည့် dummy;
};

#endif
