#اگر_غیر_تعریف_شدہ _SDL_OPENVRVIDEO_H
#تعریف_کرو _SDL_OPENVRVIDEO_H

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
#اگر_تعریف_شدہ EXTERN_C
#تعریف_منسوخ EXTERN_C
#اگر_ختم
#اگر_ختم

// OpenVR has a LOT of unused variables that GCC will freak out on.
#اگر_تعریف_شدہ __GNUC__
#ہدایت GCC diagnostic ڈالو
#ہدایت GCC diagnostic ignored "-Wunused-variable"
#اگر_ختم

#تعریف_کرو USE_SDL
#شامل "openvr_capi.h"

#اگر_تعریف_شدہ __GNUC__
#ہدایت GCC diagnostic نکالو
#اگر_ختم

#شامل <stdint.h>

#اگر_غیر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS

#شامل <GLES3/gl3.h>
#شامل <GLES3/gl32.h>
#شامل <EGL/egl.h>
#شامل <GLES2/gl2.h>
#شامل <GLES2/gl2ext.h>
#شامل <GLES2/gl2ext.h>

#اگر_ختم


ساخت SDL_کھڑکی_ڈیٹا
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
    SDL_کھڑکی *کھڑکی;
    HWND hwnd;
    HWND والد;
    HDC hdc;
    HDC mdc;
#ورنہ
    صحیح dummy;
#اگر_ختم
};

ساخت SDL_Video_ڈیٹا {
    خالی * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_Init_اندرونی)( EVRInitError *peError, EVRApplicationType eType );
    ثابت حرف *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ثابت حرف *pch_Interface_نسخہ, EVRInitError *peError );

    صحیح is_بفر_rendering;

    غیرعلامتی صحیح overlaytexture;

    غیرعلامتی صحیح fbo, rbo;

    صحیح saved_texture_state;

    ساخت VR_IVRSystem_Fn_جدول *oSystem;
    ساخت VR_IVROverlay_Fn_جدول *oOverlay;
	ساخت VR_IVRInput_Fn_جدول * o_داخلہ;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	حرف * sOverlayName;

	VRAction_سیٹ_Handle_t داخلہ_action_سیٹ;
	VRActionHandle_t * داخلہ_action_handles_buttons;
	صحیح داخلہ_action_handles_buttons_گنتی;
	VRActionHandle_t * داخلہ_action_handles_axes;
	صحیح داخلہ_action_handles_axes_گنتی;
	VRActionHandle_t داخلہ_action_handles_haptics[2];

    bool bHasShownOverlay;
    صحیح targw, targh;
    صحیح آخری_targw, آخری_targh;
    صحیح تبادلہ_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_چوکھٹا_انتہا;
	bool bIconOverridden;
	
	SDL_کھڑکی * کھڑکی;
	
	SDL_Joystick *virtual_joystick;
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#ورنہ
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#اگر_ختم
};

ساخت SDL_Display_ڈیٹا
{
    صحیح dummy;
};

#اگر_ختم
