#ifndef _SDL_OPENVRVIDEO_H
#define _SDL_OPENVRVIDEO_H

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ifdef EXTERN_C
#undef EXTERN_C
#endif
#endif

// OpenVR has a LOT of unused variables that GCC will freak out on.
#ifdef __GNUC__
#pragma GCC diagnostic ધકેલો
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#define USE_SDL
#અન્તર્ભાવ "openvr_capi.h"

#ifdef __GNUC__
#pragma GCC diagnostic કાઢો
#endif

#અન્તર્ભાવ <stdint.h>

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#અન્તર્ભાવ <GLES3/gl3.h>
#અન્તર્ભાવ <GLES3/gl32.h>
#અન્તર્ભાવ <EGL/egl.h>
#અન્તર્ભાવ <GLES2/gl2.h>
#અન્તર્ભાવ <GLES2/gl2ext.h>
#અન્તર્ભાવ <GLES2/gl2ext.h>

#endif


સંરચના SDL_WindowData
{
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#નહીંતર
    પૂર્ણાંક dummy;
#endif
};

સંરચના SDL_VideoData {
    શૂન્ય * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    અચલ અક્ષર *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( અચલ અક્ષર *pchInterfaceVersion, EVRInitError *peError );

    પૂર્ણાંક is_buffer_rendering;

    unsigned પૂર્ણાંક overlaytexture;

    unsigned પૂર્ણાંક fbo, rbo;

    પૂર્ણાંક saved_texture_state;

    સંરચના VR_IVRSystem_FnTable *oSystem;
    સંરચના VR_IVROverlay_FnTable *oOverlay;
	સંરચના VR_IVRInput_FnTable * o_આગત;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	અક્ષર * sOverlayName;

	VRActionSetHandle_t આગત_action_set;
	VRActionHandle_t * આગત_action_handles_buttons;
	પૂર્ણાંક આગત_action_handles_buttons_ગણતરી;
	VRActionHandle_t * આગત_action_handles_axes;
	પૂર્ણાંક આગત_action_handles_axes_ગણતરી;
	VRActionHandle_t આગત_action_handles_haptics[2];

    bool bHasShownOverlay;
    પૂર્ણાંક targw, targh;
    પૂર્ણાંક last_targw, last_targh;
    પૂર્ણાંક swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_end;
	bool bIconOverridden;
	
	SDL_Window * window;
	
	SDL_Joystick *virtual_joystick;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#નહીંતર
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#endif
};

સંરચના SDL_DisplayData
{
    પૂર્ણાંક dummy;
};

#endif
