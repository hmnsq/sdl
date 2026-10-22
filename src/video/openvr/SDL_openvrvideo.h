#यदि_अपरिभाषितम् _SDL_OPENVRVIDEO_H
#परिभाषय _SDL_OPENVRVIDEO_H

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WINDOWS
#यदि_परिभाषितम् EXTERN_C
#अपरिभाषय EXTERN_C
#यदि_अन्तः
#यदि_अन्तः

// OpenVR has a LOT of unused variables that GCC will freak out on.
#यदि_परिभाषितम् __GNUC__
#निर्देशः GCC diagnostic प्रक्षिप
#निर्देशः GCC diagnostic ignored "-Wunused-variable"
#यदि_अन्तः

#परिभाषय USE_SDL
#अन्तर्भाव "openvr_capi.h"

#यदि_परिभाषितम् __GNUC__
#निर्देशः GCC diagnostic निष्कासय
#यदि_अन्तः

#अन्तर्भाव <stdint.h>

#यदि_अपरिभाषितम् SDL_VIDEO_DRIVER_WINDOWS

#अन्तर्भाव <GLES3/gl3.h>
#अन्तर्भाव <GLES3/gl32.h>
#अन्तर्भाव <EGL/egl.h>
#अन्तर्भाव <GLES2/gl2.h>
#अन्तर्भाव <GLES2/gl2ext.h>
#अन्तर्भाव <GLES2/gl2ext.h>

#यदि_अन्तः


संरचना SDL_गवाक्षः_दत्त
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WINDOWS
    SDL_गवाक्षः *गवाक्षः;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#अन्यथा
    पूर्णाङ्क dummy;
#यदि_अन्तः
};

संरचना SDL_Video_दत्त {
    शून्य * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_Init_आन्तरिकम्)( EVRInitError *peError, EVRApplicationType eType );
    ध्रुव वर्ण *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( ध्रुव वर्ण *pch_Interface_संस्करणम्, EVRInitError *peError );

    पूर्णाङ्क is_बफर_rendering;

    अचिह्नित पूर्णाङ्क overlaytexture;

    अचिह्नित पूर्णाङ्क fbo, rbo;

    पूर्णाङ्क saved_texture_state;

    संरचना VR_IVRSystem_Fn_सारणी *oSystem;
    संरचना VR_IVROverlay_Fn_सारणी *oOverlay;
	संरचना VR_IVRInput_Fn_सारणी * o_निवेशः;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	वर्ण * sOverlayName;

	VRAction_समुच्चयः_Handle_t निवेशः_action_समुच्चयः;
	VRActionHandle_t * निवेशः_action_handles_buttons;
	पूर्णाङ्क निवेशः_action_handles_buttons_गणनम्;
	VRActionHandle_t * निवेशः_action_handles_axes;
	पूर्णाङ्क निवेशः_action_handles_axes_गणनम्;
	VRActionHandle_t निवेशः_action_handles_haptics[2];

    bool bHasShownOverlay;
    पूर्णाङ्क targw, targh;
    पूर्णाङ्क चरमः_targw, चरमः_targh;
    पूर्णाङ्क swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_अन्तः;
	bool bIconOverridden;
	
	SDL_गवाक्षः * गवाक्षः;
	
	SDL_Joystick *virtual_joystick;
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#अन्यथा
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#यदि_अन्तः
};

संरचना SDL_Display_दत्त
{
    पूर्णाङ्क dummy;
};

#यदि_अन्तः
