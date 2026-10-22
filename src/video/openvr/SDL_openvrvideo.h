#که_نه_تعریف_شوی _SDL_OPENVRVIDEO_H
#تعریف_کړه _SDL_OPENVRVIDEO_H

#که_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS
#که_تعریف_شوی EXTERN_C
#تعریف_لغوه EXTERN_C
#د_که_پای
#د_که_پای

// OpenVR has a LOT of unused variables that GCC will freak out on.
#که_تعریف_شوی __GNUC__
#لارښوونه GCC diagnostic ټېل
#لارښوونه GCC diagnostic ignored "-Wunused-variable"
#د_که_پای

#تعریف_کړه USE_SDL
#ضمن "openvr_capi.h"

#که_تعریف_شوی __GNUC__
#لارښوونه GCC diagnostic راوباسه
#د_که_پای

#ضمن <stdint.h>

#که_نه_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS

#ضمن <GLES3/gl3.h>
#ضمن <GLES3/gl32.h>
#ضمن <EGL/egl.h>
#ضمن <GLES2/gl2.h>
#ضمن <GLES2/gl2ext.h>
#ضمن <GLES2/gl2ext.h>

#د_که_پای


بنية SDL_کړکۍ_معلومات
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS
    SDL_کړکۍ *کړکۍ;
    HWND hwnd;
    HWND پلار;
    HDC hdc;
    HDC mdc;
#وإلا
    صحيح dummy;
#د_که_پای
};

بنية SDL_Video_معلومات {
    فراغ * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_Init_دننی)( EVRInitError *peError, EVRApplicationType eType );
    ثابت حرف *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ثابت حرف *pch_Interface_نسخه, EVRInitError *peError );

    صحيح is_بفر_rendering;

    بینښه صحيح overlaytexture;

    بینښه صحيح fbo, rbo;

    صحيح saved_texture_state;

    بنية VR_IVRSystem_Fn_جدول *oSystem;
    بنية VR_IVROverlay_Fn_جدول *oOverlay;
	بنية VR_IVRInput_Fn_جدول * o_ننوت;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	حرف * sOverlayName;

	VRAction_سېټ_Handle_t ننوت_action_سېټ;
	VRActionHandle_t * ننوت_action_handles_buttons;
	صحيح ننوت_action_handles_buttons_شمېر;
	VRActionHandle_t * ننوت_action_handles_axes;
	صحيح ننوت_action_handles_axes_شمېر;
	VRActionHandle_t ننوت_action_handles_haptics[2];

    bool bHasShownOverlay;
    صحيح targw, targh;
    صحيح وروستی_targw, وروستی_targh;
    صحيح بدلون_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_چوکاټ_پای_ټکی;
	bool bIconOverridden;
	
	SDL_کړکۍ * کړکۍ;
	
	SDL_Joystick *virtual_joystick;
#که_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#وإلا
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#د_که_پای
};

بنية SDL_Display_معلومات
{
    صحيح dummy;
};

#د_که_پای
