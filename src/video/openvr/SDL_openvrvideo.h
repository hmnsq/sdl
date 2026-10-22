#ifndef _SDL_OPENVRVIDEO_H
#define _SDL_OPENVRVIDEO_H

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ifdef EXTERN_C
#undef EXTERN_C
#endif
#endif

// OpenVR has a LOT of unused variables that GCC will freak out on.
#ifdef __GNUC__
#pragma GCC diagnostic തള്ളുക
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#define USE_SDL
#അന്തര്ഭാവ "openvr_capi.h"

#ifdef __GNUC__
#pragma GCC diagnostic എടുക്കുക
#endif

#അന്തര്ഭാവ <stdint.h>

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#അന്തര്ഭാവ <GLES3/gl3.h>
#അന്തര്ഭാവ <GLES3/gl32.h>
#അന്തര്ഭാവ <EGL/egl.h>
#അന്തര്ഭാവ <GLES2/gl2.h>
#അന്തര്ഭാവ <GLES2/gl2ext.h>
#അന്തര്ഭാവ <GLES2/gl2ext.h>

#endif


ഘടന SDL_WindowData
{
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#അല്ലെങ്കിൽ
    പൂർണ്ണസംഖ്യ dummy;
#endif
};

ഘടന SDL_VideoData {
    ശൂന്യം * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    സ്ഥിരം അക്ഷരം *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( സ്ഥിരം അക്ഷരം *pchInterfaceVersion, EVRInitError *peError );

    പൂർണ്ണസംഖ്യ is_buffer_rendering;

    unsigned പൂർണ്ണസംഖ്യ overlaytexture;

    unsigned പൂർണ്ണസംഖ്യ fbo, rbo;

    പൂർണ്ണസംഖ്യ saved_texture_state;

    ഘടന VR_IVRSystem_FnTable *oSystem;
    ഘടന VR_IVROverlay_FnTable *oOverlay;
	ഘടന VR_IVRInput_FnTable * o_നിവേശം;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	അക്ഷരം * sOverlayName;

	VRActionSetHandle_t നിവേശം_action_set;
	VRActionHandle_t * നിവേശം_action_handles_buttons;
	പൂർണ്ണസംഖ്യ നിവേശം_action_handles_buttons_എണ്ണം;
	VRActionHandle_t * നിവേശം_action_handles_axes;
	പൂർണ്ണസംഖ്യ നിവേശം_action_handles_axes_എണ്ണം;
	VRActionHandle_t നിവേശം_action_handles_haptics[2];

    bool bHasShownOverlay;
    പൂർണ്ണസംഖ്യ targw, targh;
    പൂർണ്ണസംഖ്യ last_targw, last_targh;
    പൂർണ്ണസംഖ്യ swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_end;
	bool bIconOverridden;
	
	SDL_Window * window;
	
	SDL_Joystick *virtual_joystick;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#അല്ലെങ്കിൽ
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#endif
};

ഘടന SDL_DisplayData
{
    പൂർണ്ണസംഖ്യ dummy;
};

#endif
