#ifndef _SDL_OPENVRVIDEO_H
#define _SDL_OPENVRVIDEO_H

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ifdef EXTERN_C
#undef EXTERN_C
#endif
#endif

// OpenVR has a LOT of unused variables that GCC will freak out on.
#ifdef __GNUC__
#pragma GCC diagnostic ঠেলো
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#define USE_SDL
#অন্তর্ভাব "openvr_capi.h"

#ifdef __GNUC__
#pragma GCC diagnostic বের_করো
#endif

#অন্তর্ভাব <stdint.h>

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#অন্তর্ভাব <GLES3/gl3.h>
#অন্তর্ভাব <GLES3/gl32.h>
#অন্তর্ভাব <EGL/egl.h>
#অন্তর্ভাব <GLES2/gl2.h>
#অন্তর্ভাব <GLES2/gl2ext.h>
#অন্তর্ভাব <GLES2/gl2ext.h>

#endif


কাঠামো SDL_Window_তথ্য
{
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#অন্যথা
    পূর্ণসংখ্যা dummy;
#endif
};

কাঠামো SDL_Video_তথ্য {
    শূন্য * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    ধ্রুবক অক্ষর *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ধ্রুবক অক্ষর *pchInterfaceVersion, EVRInitError *peError );

    পূর্ণসংখ্যা is_বাফার_rendering;

    unsigned পূর্ণসংখ্যা overlaytexture;

    unsigned পূর্ণসংখ্যা fbo, rbo;

    পূর্ণসংখ্যা saved_texture_state;

    কাঠামো VR_IVRSystem_FnTable *oSystem;
    কাঠামো VR_IVROverlay_FnTable *oOverlay;
	কাঠামো VR_IVRInput_FnTable * o_প্রবেশ;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	অক্ষর * sOverlayName;

	VRActionSetHandle_t প্রবেশ_action_set;
	VRActionHandle_t * প্রবেশ_action_handles_buttons;
	পূর্ণসংখ্যা প্রবেশ_action_handles_buttons_গুনতি;
	VRActionHandle_t * প্রবেশ_action_handles_axes;
	পূর্ণসংখ্যা প্রবেশ_action_handles_axes_গুনতি;
	VRActionHandle_t প্রবেশ_action_handles_haptics[2];

    bool bHasShownOverlay;
    পূর্ণসংখ্যা targw, targh;
    পূর্ণসংখ্যা last_targw, last_targh;
    পূর্ণসংখ্যা swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_end;
	bool bIconOverridden;
	
	SDL_Window * window;
	
	SDL_Joystick *virtual_joystick;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#অন্যথা
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#endif
};

কাঠামো SDL_Display_তথ্য
{
    পূর্ণসংখ্যা dummy;
};

#endif
