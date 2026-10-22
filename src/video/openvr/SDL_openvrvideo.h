#నిర్వచితం_కాకపోతే _SDL_OPENVRVIDEO_H
#నిర్వచించు _SDL_OPENVRVIDEO_H

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS
#నిర్వచితమైతే EXTERN_C
#నిర్వచనం_రద్దు EXTERN_C
#అయితే_ముగింపు
#అయితే_ముగింపు

// OpenVR has a LOT of unused variables that GCC will freak out on.
#నిర్వచితమైతే __GNUC__
#సూచన GCC diagnostic నెట్టు
#సూచన GCC diagnostic ignored "-Wunused-variable"
#అయితే_ముగింపు

#నిర్వచించు USE_SDL
#అన్తర్భావ "openvr_capi.h"

#నిర్వచితమైతే __GNUC__
#సూచన GCC diagnostic తీయి
#అయితే_ముగింపు

#అన్తర్భావ <stdint.h>

#నిర్వచితం_కాకపోతే SDL_VIDEO_DRIVER_WINDOWS

#అన్తర్భావ <GLES3/gl3.h>
#అన్తర్భావ <GLES3/gl32.h>
#అన్తర్భావ <EGL/egl.h>
#అన్తర్భావ <GLES2/gl2.h>
#అన్తర్భావ <GLES2/gl2ext.h>
#అన్తర్భావ <GLES2/gl2ext.h>

#అయితే_ముగింపు


నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS
    SDL_కిటికీ *కిటికీ;
    HWND hwnd;
    HWND మాతృ;
    HDC hdc;
    HDC mdc;
#లేకపోతే
    పూర్ణాంకం dummy;
#అయితే_ముగింపు
};

నిర్మాణం SDL_Video_దత్తాంశం {
    శూన్య * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_Init_అంతర్గత)( EVRInitError *peError, EVRApplicationType eType );
    స్థిరరాశి అక్షరం *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( స్థిరరాశి అక్షరం *pch_Interface_సంస్కరణ, EVRInitError *peError );

    పూర్ణాంకం is_బఫరు_rendering;

    గుర్తులేని పూర్ణాంకం overlaytexture;

    గుర్తులేని పూర్ణాంకం fbo, rbo;

    పూర్ణాంకం saved_texture_state;

    నిర్మాణం VR_IVRSystem_Fn_పట్టిక *oSystem;
    నిర్మాణం VR_IVROverlay_Fn_పట్టిక *oOverlay;
	నిర్మాణం VR_IVRInput_Fn_పట్టిక * o_ఆదానం;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	అక్షరం * sOverlayName;

	VRAction_సమితి_Handle_t ఆదానం_action_సమితి;
	VRActionHandle_t * ఆదానం_action_handles_buttons;
	పూర్ణాంకం ఆదానం_action_handles_buttons_లెక్క;
	VRActionHandle_t * ఆదానం_action_handles_axes;
	పూర్ణాంకం ఆదానం_action_handles_axes_లెక్క;
	VRActionHandle_t ఆదానం_action_handles_haptics[2];

    bool bHasShownOverlay;
    పూర్ణాంకం targw, targh;
    పూర్ణాంకం చివరి_targw, చివరి_targh;
    పూర్ణాంకం మార్పిడి_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_చట్రం_చివర;
	bool bIconOverridden;
	
	SDL_కిటికీ * కిటికీ;
	
	SDL_Joystick *virtual_joystick;
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#లేకపోతే
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#అయితే_ముగింపు
};

నిర్మాణం SDL_Display_దత్తాంశం
{
    పూర్ణాంకం dummy;
};

#అయితే_ముగింపు
