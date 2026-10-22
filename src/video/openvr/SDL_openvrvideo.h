#ifndef _SDL_OPENVRVIDEO_H
#define _SDL_OPENVRVIDEO_H

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ifdef EXTERN_C
#undef EXTERN_C
#endif
#endif

// OpenVR has a LOT of unused variables that GCC will freak out on.
#ifdef __GNUC__
#pragma GCC diagnostic தள்ளு
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#define USE_SDL
#அந்தர்பாவ "openvr_capi.h"

#ifdef __GNUC__
#pragma GCC diagnostic எடு
#endif

#அந்தர்பாவ <stdint.h>

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#அந்தர்பாவ <GLES3/gl3.h>
#அந்தர்பாவ <GLES3/gl32.h>
#அந்தர்பாவ <EGL/egl.h>
#அந்தர்பாவ <GLES2/gl2.h>
#அந்தர்பாவ <GLES2/gl2ext.h>
#அந்தர்பாவ <GLES2/gl2ext.h>

#endif


கட்டமைப்பு SDL_WindowData
{
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#இல்லையெனில்
    முழு dummy;
#endif
};

கட்டமைப்பு SDL_VideoData {
    வெறுமை * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    மாறிலி எழுத்து *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( மாறிலி எழுத்து *pchInterfaceVersion, EVRInitError *peError );

    முழு is_buffer_rendering;

    unsigned முழு overlaytexture;

    unsigned முழு fbo, rbo;

    முழு saved_texture_state;

    கட்டமைப்பு VR_IVRSystem_FnTable *oSystem;
    கட்டமைப்பு VR_IVROverlay_FnTable *oOverlay;
	கட்டமைப்பு VR_IVRInput_FnTable * o_உள்ளீடு;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	எழுத்து * sOverlayName;

	VRActionSetHandle_t உள்ளீடு_action_set;
	VRActionHandle_t * உள்ளீடு_action_handles_buttons;
	முழு உள்ளீடு_action_handles_buttons_மொத்தம்;
	VRActionHandle_t * உள்ளீடு_action_handles_axes;
	முழு உள்ளீடு_action_handles_axes_மொத்தம்;
	VRActionHandle_t உள்ளீடு_action_handles_haptics[2];

    bool bHasShownOverlay;
    முழு targw, targh;
    முழு last_targw, last_targh;
    முழு swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_end;
	bool bIconOverridden;
	
	SDL_Window * window;
	
	SDL_Joystick *virtual_joystick;
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#இல்லையெனில்
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#endif
};

கட்டமைப்பு SDL_DisplayData
{
    முழு dummy;
};

#endif
