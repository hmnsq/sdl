#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ _SDL_OPENVRVIDEO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ _SDL_OPENVRVIDEO_H

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EXTERN_C
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ EXTERN_C
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

// OpenVR has a LOT of unused variables that GCC will freak out on.
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __GNUC__
#ਹਦਾਇਤ GCC diagnostic ਧੱਕੋ
#ਹਦਾਇਤ GCC diagnostic ignored "-Wunused-variable"
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ USE_SDL
#ਅਨ੍ਤਰ੍ਭਾਵ "openvr_capi.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __GNUC__
#ਹਦਾਇਤ GCC diagnostic ਕੱਢੋ
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS

#ਅਨ੍ਤਰ੍ਭਾਵ <GLES3/gl3.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <GLES3/gl32.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <EGL/egl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <GLES2/gl2.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <GLES2/gl2ext.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <GLES2/gl2ext.h>

#ਜੇ_ਅੰਤ


ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    HWND hwnd;
    HWND ਮਾਪਾ;
    HDC hdc;
    HDC mdc;
#ਨਹੀਂਤਾਂ
    ਪੂਰਨ dummy;
#ਜੇ_ਅੰਤ
};

ਬਣਤਰ SDL_Video_ਅੰਕੜੇ {
    ਖਾਲੀ * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_Init_ਅੰਦਰੂਨੀ)( EVRInitError *peError, EVRApplicationType eType );
    ਅਚਲ ਅੱਖਰ *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ਅਚਲ ਅੱਖਰ *pch_Interface_ਸੰਸਕਰਣ, EVRInitError *peError );

    ਪੂਰਨ is_ਬਫਰ_rendering;

    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ overlaytexture;

    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ fbo, rbo;

    ਪੂਰਨ saved_texture_state;

    ਬਣਤਰ VR_IVRSystem_Fn_ਸਾਰਣੀ *oSystem;
    ਬਣਤਰ VR_IVROverlay_Fn_ਸਾਰਣੀ *oOverlay;
	ਬਣਤਰ VR_IVRInput_Fn_ਸਾਰਣੀ * o_ਨਿਵੇਸ਼;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	ਅੱਖਰ * sOverlayName;

	VRAction_ਸੈੱਟ_Handle_t ਨਿਵੇਸ਼_action_ਸੈੱਟ;
	VRActionHandle_t * ਨਿਵੇਸ਼_action_handles_buttons;
	ਪੂਰਨ ਨਿਵੇਸ਼_action_handles_buttons_ਗਿਣਤੀ;
	VRActionHandle_t * ਨਿਵੇਸ਼_action_handles_axes;
	ਪੂਰਨ ਨਿਵੇਸ਼_action_handles_axes_ਗਿਣਤੀ;
	VRActionHandle_t ਨਿਵੇਸ਼_action_handles_haptics[2];

    bool bHasShownOverlay;
    ਪੂਰਨ targw, targh;
    ਪੂਰਨ ਆਖਰੀ_targw, ਆਖਰੀ_targh;
    ਪੂਰਨ ਅਦਲਾ_ਬਦਲੀ_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_ਚੌਖਟਾ_ਸਿਰਾ;
	bool bIconOverridden;
	
	SDL_ਖਿੜਕੀ * ਖਿੜਕੀ;
	
	SDL_Joystick *virtual_joystick;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#ਨਹੀਂਤਾਂ
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#ਜੇ_ਅੰਤ
};

ਬਣਤਰ SDL_Display_ਅੰਕੜੇ
{
    ਪੂਰਨ dummy;
};

#ਜੇ_ਅੰਤ
