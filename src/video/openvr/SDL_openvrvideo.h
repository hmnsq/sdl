#ifndef _SDL_OPENVRVIDEO_H
#define _SDL_OPENVRVIDEO_H

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ifdef EXTERN_C
#undef EXTERN_C
#endif
#endif

// OpenVR has a LOT of unused variables that GCC will freak out on.
#ifdef __GNUC__
#pragma GCC diagnostic ತಳ್ಳು
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#define USE_SDL
#ಅನ್ತರ್ಭಾವ "openvr_capi.h"

#ifdef __GNUC__
#pragma GCC diagnostic ತೆಗೆ
#endif

#ಅನ್ತರ್ಭಾವ <stdint.h>

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#ಅನ್ತರ್ಭಾವ <GLES3/gl3.h>
#ಅನ್ತರ್ಭಾವ <GLES3/gl32.h>
#ಅನ್ತರ್ಭಾವ <EGL/egl.h>
#ಅನ್ತರ್ಭಾವ <GLES2/gl2.h>
#ಅನ್ತರ್ಭಾವ <GLES2/gl2ext.h>
#ಅನ್ತರ್ಭಾವ <GLES2/gl2ext.h>

#endif


ಸಂರಚನಾ SDL_WindowData
{
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#ಅನ್ಯಥಾ
    ಪೂರ್ಣಾಙ್ಕ dummy;
#endif
};

ಸಂರಚನಾ SDL_VideoData {
    ಶೂನ್ಯ * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    ಧ್ರುವ ವರ್ಣ *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ಧ್ರುವ ವರ್ಣ *pchInterfaceVersion, EVRInitError *peError );

    ಪೂರ್ಣಾಙ್ಕ is_buffer_rendering;

    unsigned ಪೂರ್ಣಾಙ್ಕ overlaytexture;

    unsigned ಪೂರ್ಣಾಙ್ಕ fbo, rbo;

    ಪೂರ್ಣಾಙ್ಕ saved_texture_state;

    ಸಂರಚನಾ VR_IVRSystem_FnTable *oSystem;
    ಸಂರಚನಾ VR_IVROverlay_FnTable *oOverlay;
	ಸಂರಚನಾ VR_IVRInput_FnTable * o_ಒಳಹರಿವು;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	ವರ್ಣ * sOverlayName;

	VRActionSetHandle_t ಒಳಹರಿವು_action_set;
	VRActionHandle_t * ಒಳಹರಿವು_action_handles_buttons;
	ಪೂರ್ಣಾಙ್ಕ ಒಳಹರಿವು_action_handles_buttons_ಎಣಿಕೆ;
	VRActionHandle_t * ಒಳಹರಿವು_action_handles_axes;
	ಪೂರ್ಣಾಙ್ಕ ಒಳಹರಿವು_action_handles_axes_ಎಣಿಕೆ;
	VRActionHandle_t ಒಳಹರಿವು_action_handles_haptics[2];

    bool bHasShownOverlay;
    ಪೂರ್ಣಾಙ್ಕ targw, targh;
    ಪೂರ್ಣಾಙ್ಕ last_targw, last_targh;
    ಪೂರ್ಣಾಙ್ಕ swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_end;
	bool bIconOverridden;
	
	SDL_Window * window;
	
	SDL_Joystick *virtual_joystick;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#ಅನ್ಯಥಾ
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#endif
};

ಸಂರಚನಾ SDL_DisplayData
{
    ಪೂರ್ಣಾಙ್ಕ dummy;
};

#endif
