#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _SDL_OPENVRVIDEO_H
#ವ್ಯಾಖ್ಯಾನಿಸು _SDL_OPENVRVIDEO_H

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EXTERN_C
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು EXTERN_C
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

// OpenVR has a LOT of unused variables that GCC will freak out on.
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __GNUC__
#ಸೂಚನೆ GCC diagnostic ತಳ್ಳು
#ಸೂಚನೆ GCC diagnostic ignored "-Wunused-variable"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು USE_SDL
#ಅನ್ತರ್ಭಾವ "openvr_capi.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __GNUC__
#ಸೂಚನೆ GCC diagnostic ತೆಗೆ
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <stdint.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_VIDEO_DRIVER_WINDOWS

#ಅನ್ತರ್ಭಾವ <GLES3/gl3.h>
#ಅನ್ತರ್ಭಾವ <GLES3/gl32.h>
#ಅನ್ತರ್ಭಾವ <EGL/egl.h>
#ಅನ್ತರ್ಭಾವ <GLES2/gl2.h>
#ಅನ್ತರ್ಭಾವ <GLES2/gl2ext.h>
#ಅನ್ತರ್ಭಾವ <GLES2/gl2ext.h>

#ಆದರೆ_ಅಂತ್ಯ


ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    HWND hwnd;
    HWND ಪೋಷಕ;
    HDC hdc;
    HDC mdc;
#ಇಲ್ಲದಿದ್ದರೆ
    ಪೂರ್ಣಾಂಕ dummy;
#ಆದರೆ_ಅಂತ್ಯ
};

ರಚನೆ SDL_Video_ದತ್ತಾಂಶ {
    ಶೂನ್ಯ * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_Init_ಆಂತರಿಕ)( EVRInitError *peError, EVRApplicationType eType );
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pch_Interface_ಆವೃತ್ತಿ, EVRInitError *peError );

    ಪೂರ್ಣಾಂಕ is_ಬಫರ್_rendering;

    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ overlaytexture;

    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ fbo, rbo;

    ಪೂರ್ಣಾಂಕ saved_texture_state;

    ರಚನೆ VR_IVRSystem_Fn_ಕೋಷ್ಟಕ *oSystem;
    ರಚನೆ VR_IVROverlay_Fn_ಕೋಷ್ಟಕ *oOverlay;
	ರಚನೆ VR_IVRInput_Fn_ಕೋಷ್ಟಕ * o_ಒಳಹರಿವು;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	ಅಕ್ಷರ * sOverlayName;

	VRAction_ಗಣ_Handle_t ಒಳಹರಿವು_action_ಗಣ;
	VRActionHandle_t * ಒಳಹರಿವು_action_handles_buttons;
	ಪೂರ್ಣಾಂಕ ಒಳಹರಿವು_action_handles_buttons_ಎಣಿಕೆ;
	VRActionHandle_t * ಒಳಹರಿವು_action_handles_axes;
	ಪೂರ್ಣಾಂಕ ಒಳಹರಿವು_action_handles_axes_ಎಣಿಕೆ;
	VRActionHandle_t ಒಳಹರಿವು_action_handles_haptics[2];

    bool bHasShownOverlay;
    ಪೂರ್ಣಾಂಕ targw, targh;
    ಪೂರ್ಣಾಂಕ ಕೊನೆಯ_targw, ಕೊನೆಯ_targh;
    ಪೂರ್ಣಾಂಕ ಅದಲುಬದಲು_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_ಚೌಕಟ್ಟು_ಕೊನೆ;
	bool bIconOverridden;
	
	SDL_ಕಿಟಕಿ * ಕಿಟಕಿ;
	
	SDL_Joystick *virtual_joystick;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#ಇಲ್ಲದಿದ್ದರೆ
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#ಆದರೆ_ಅಂತ್ಯ
};

ರಚನೆ SDL_Display_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ dummy;
};

#ಆದರೆ_ಅಂತ್ಯ
