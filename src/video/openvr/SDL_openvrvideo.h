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


সংরচনা SDL_WindowData
{
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#অন্যথা
    পূর্ণাঙ্ক dummy;
#endif
};

সংরচনা SDL_VideoData {
    শূন্য * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    ধ্রুব বর্ণ *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ধ্রুব বর্ণ *pchInterfaceVersion, EVRInitError *peError );

    পূর্ণাঙ্ক is_buffer_rendering;

    unsigned পূর্ণাঙ্ক overlaytexture;

    unsigned পূর্ণাঙ্ক fbo, rbo;

    পূর্ণাঙ্ক saved_texture_state;

    সংরচনা VR_IVRSystem_FnTable *oSystem;
    সংরচনা VR_IVROverlay_FnTable *oOverlay;
	সংরচনা VR_IVRInput_FnTable * o_প্রবেশ;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	বর্ণ * sOverlayName;

	VRActionSetHandle_t প্রবেশ_action_set;
	VRActionHandle_t * প্রবেশ_action_handles_buttons;
	পূর্ণাঙ্ক প্রবেশ_action_handles_buttons_গুনতি;
	VRActionHandle_t * প্রবেশ_action_handles_axes;
	পূর্ণাঙ্ক প্রবেশ_action_handles_axes_গুনতি;
	VRActionHandle_t প্রবেশ_action_handles_haptics[2];

    bool bHasShownOverlay;
    পূর্ণাঙ্ক targw, targh;
    পূর্ণাঙ্ক last_targw, last_targh;
    পূর্ণাঙ্ক swap_interval;

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

সংরচনা SDL_DisplayData
{
    পূর্ণাঙ্ক dummy;
};

#endif
