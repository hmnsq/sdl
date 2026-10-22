#جے_بنا_تعریف _SDL_OPENVRVIDEO_H
#تعریف_کرو _SDL_OPENVRVIDEO_H

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
#جے_تعریف_شدہ EXTERN_C
#تعریف_رد EXTERN_C
#جے_انت
#جے_انت

// OpenVR has a LOT of unused variables that GCC will freak out on.
#جے_تعریف_شدہ __GNUC__
#ہدایت GCC diagnostic ڈالو
#ہدایت GCC diagnostic ignored "-Wunused-variable"
#جے_انت

#تعریف_کرو USE_SDL
#ضمن "openvr_capi.h"

#جے_تعریف_شدہ __GNUC__
#ہدایت GCC diagnostic نکالو
#جے_انت

#ضمن <stdint.h>

#جے_بنا_تعریف SDL_VIDEO_DRIVER_WINDOWS

#ضمن <GLES3/gl3.h>
#ضمن <GLES3/gl32.h>
#ضمن <EGL/egl.h>
#ضمن <GLES2/gl2.h>
#ضمن <GLES2/gl2ext.h>
#ضمن <GLES2/gl2ext.h>

#جے_انت


بنية SDL_کھڑکی_انکڑے
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
    SDL_کھڑکی *کھڑکی;
    HWND hwnd;
    HWND ماپا;
    HDC hdc;
    HDC mdc;
#وإلا
    صحيح dummy;
#جے_انت
};

بنية SDL_Video_انکڑے {
    فراغ * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_Init_اندرونی)( EVRInitError *peError, EVRApplicationType eType );
    ثابت حرف *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ثابت حرف *pch_Interface_نسخہ, EVRInitError *peError );

    صحيح is_بفر_rendering;

    بنانشانی صحيح overlaytexture;

    بنانشانی صحيح fbo, rbo;

    صحيح saved_texture_state;

    بنية VR_IVRSystem_Fn_جدول *oSystem;
    بنية VR_IVROverlay_Fn_جدول *oOverlay;
	بنية VR_IVRInput_Fn_جدول * o_داخلہ;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	حرف * sOverlayName;

	VRAction_سیٹ_Handle_t داخلہ_action_سیٹ;
	VRActionHandle_t * داخلہ_action_handles_buttons;
	صحيح داخلہ_action_handles_buttons_گنتی;
	VRActionHandle_t * داخلہ_action_handles_axes;
	صحيح داخلہ_action_handles_axes_گنتی;
	VRActionHandle_t داخلہ_action_handles_haptics[2];

    bool bHasShownOverlay;
    صحيح targw, targh;
    صحيح آخری_targw, آخری_targh;
    صحيح وٹاندرا_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_چوکھٹا_سرا;
	bool bIconOverridden;
	
	SDL_کھڑکی * کھڑکی;
	
	SDL_Joystick *virtual_joystick;
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#وإلا
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#جے_انت
};

بنية SDL_Display_انکڑے
{
    صحيح dummy;
};

#جے_انت
