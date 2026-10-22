#جيڪڏهن_وصف_نه_ٿيل _SDL_OPENVRVIDEO_H
#وصف_ڪريو _SDL_OPENVRVIDEO_H

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS
#جيڪڏهن_وصف_ٿيل EXTERN_C
#وصف_رد EXTERN_C
#جيڪڏهن_پورو
#جيڪڏهن_پورو

// OpenVR has a LOT of unused variables that GCC will freak out on.
#جيڪڏهن_وصف_ٿيل __GNUC__
#هدايت GCC diagnostic ڌڪو
#هدايت GCC diagnostic ignored "-Wunused-variable"
#جيڪڏهن_پورو

#وصف_ڪريو USE_SDL
#ضمن "openvr_capi.h"

#جيڪڏهن_وصف_ٿيل __GNUC__
#هدايت GCC diagnostic ڪڍو
#جيڪڏهن_پورو

#ضمن <stdint.h>

#جيڪڏهن_وصف_نه_ٿيل SDL_VIDEO_DRIVER_WINDOWS

#ضمن <GLES3/gl3.h>
#ضمن <GLES3/gl32.h>
#ضمن <EGL/egl.h>
#ضمن <GLES2/gl2.h>
#ضمن <GLES2/gl2ext.h>
#ضمن <GLES2/gl2ext.h>

#جيڪڏهن_پورو


بنية SDL_دري_معلومات
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS
    SDL_دري *دري;
    HWND hwnd;
    HWND والد;
    HDC hdc;
    HDC mdc;
#وإلا
    صحيح dummy;
#جيڪڏهن_پورو
};

بنية SDL_Video_معلومات {
    فراغ * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_Init_اندروني)( EVRInitError *peError, EVRApplicationType eType );
    ثابت حرف *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ثابت حرف *pch_Interface_نسخو, EVRInitError *peError );

    صحيح is_بفر_rendering;

    بنانشان صحيح overlaytexture;

    بنانشان صحيح fbo, rbo;

    صحيح saved_texture_state;

    بنية VR_IVRSystem_Fn_جدول *oSystem;
    بنية VR_IVROverlay_Fn_جدول *oOverlay;
	بنية VR_IVRInput_Fn_جدول * o_داخلا;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	حرف * sOverlayName;

	VRAction_سيٽ_Handle_t داخلا_action_سيٽ;
	VRActionHandle_t * داخلا_action_handles_buttons;
	صحيح داخلا_action_handles_buttons_ڳڻپ;
	VRActionHandle_t * داخلا_action_handles_axes;
	صحيح داخلا_action_handles_axes_ڳڻپ;
	VRActionHandle_t داخلا_action_handles_haptics[2];

    bool bHasShownOverlay;
    صحيح targw, targh;
    صحيح آخري_targw, آخري_targh;
    صحيح مٽا_سٽا_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_چوکٺو_پڇاڙي;
	bool bIconOverridden;
	
	SDL_دري * دري;
	
	SDL_Joystick *virtual_joystick;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#وإلا
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#جيڪڏهن_پورو
};

بنية SDL_Display_معلومات
{
    صحيح dummy;
};

#جيڪڏهن_پورو
