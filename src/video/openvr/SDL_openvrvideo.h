#اگر_تعریف_نشده _SDL_OPENVRVIDEO_H
#تعریف_کن _SDL_OPENVRVIDEO_H

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS
#اگر_تعریف_شده EXTERN_C
#لغو_تعریف EXTERN_C
#پایان_اگر
#پایان_اگر

// OpenVR has a LOT of unused variables that GCC will freak out on.
#اگر_تعریف_شده __GNUC__
#رهنمود GCC diagnostic افزودن
#رهنمود GCC diagnostic ignored "-Wunused-variable"
#پایان_اگر

#تعریف_کن USE_SDL
#ضمن "openvr_capi.h"

#اگر_تعریف_شده __GNUC__
#رهنمود GCC diagnostic برداشت
#پایان_اگر

#ضمن <stdint.h>

#اگر_تعریف_نشده SDL_VIDEO_DRIVER_WINDOWS

#ضمن <GLES3/gl3.h>
#ضمن <GLES3/gl32.h>
#ضمن <EGL/egl.h>
#ضمن <GLES2/gl2.h>
#ضمن <GLES2/gl2ext.h>
#ضمن <GLES2/gl2ext.h>

#پایان_اگر


بنية SDL_پنجره_داده
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS
    SDL_پنجره *پنجره;
    HWND hwnd;
    HWND والد;
    HDC hdc;
    HDC mdc;
#وإلا
    صحيح dummy;
#پایان_اگر
};

بنية SDL_Video_داده {
    فراغ * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_Init_داخلی)( EVRInitError *peError, EVRApplicationType eType );
    ثابت حرف *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ثابت حرف *pch_Interface_نسخه, EVRInitError *peError );

    صحيح is_میانگیر_rendering;

    بیعلامت صحيح overlaytexture;

    بیعلامت صحيح fbo, rbo;

    صحيح saved_texture_state;

    بنية VR_IVRSystem_Fn_جدول *oSystem;
    بنية VR_IVROverlay_Fn_جدول *oOverlay;
	بنية VR_IVRInput_Fn_جدول * o_درون_داد;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	حرف * sOverlayName;

	VRAction_مجموعه_Handle_t درون_داد_action_مجموعه;
	VRActionHandle_t * درون_داد_action_handles_buttons;
	صحيح درون_داد_action_handles_buttons_شمار;
	VRActionHandle_t * درون_داد_action_handles_axes;
	صحيح درون_داد_action_handles_axes_شمار;
	VRActionHandle_t درون_داد_action_handles_haptics[2];

    bool bHasShownOverlay;
    صحيح targw, targh;
    صحيح آخرین_targw, آخرین_targh;
    صحيح جابجا_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_قاب_انتها;
	bool bIconOverridden;
	
	SDL_پنجره * پنجره;
	
	SDL_Joystick *virtual_joystick;
#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#وإلا
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#پایان_اگر
};

بنية SDL_Display_داده
{
    صحيح dummy;
};

#پایان_اگر
