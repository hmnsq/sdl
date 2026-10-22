#अगर_अघोषित _SDL_OPENVRVIDEO_H
#घोषणा _SDL_OPENVRVIDEO_H

#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS
#अगर_घोषित EXTERN_C
#अघोषित EXTERN_C
#पूर्ण_अगर
#पूर्ण_अगर

// OpenVR has a LOT of unused variables that GCC will freak out on.
#अगर_घोषित __GNUC__
#आशय GCC diagnostic धकेलो
#आशय GCC diagnostic ignored "-Wunused-variable"
#पूर्ण_अगर

#घोषणा USE_SDL
#समावेश "openvr_capi.h"

#अगर_घोषित __GNUC__
#आशय GCC diagnostic निकालो
#पूर्ण_अगर

#समावेश <stdint.h>

#अगर_अघोषित SDL_VIDEO_DRIVER_WINDOWS

#समावेश <GLES3/gl3.h>
#समावेश <GLES3/gl32.h>
#समावेश <EGL/egl.h>
#समावेश <GLES2/gl2.h>
#समावेश <GLES2/gl2ext.h>
#समावेश <GLES2/gl2ext.h>

#पूर्ण_अगर


काष्ठा SDL_Window_तथ्य
{
#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
#अन्यथा
    पूर्णांक dummy;
#पूर्ण_अगर
};

काष्ठा SDL_Video_तथ्य {
    व्योम * openVRLIB;
    intptr_t vrtoken;
    intptr_t (*FN_VR_InitInternal)( EVRInitError *peError, EVRApplicationType eType );
    स्थिर अक्षर *(*FN_VR_GetVRInitErrorAsEnglishDescription)( EVRInitError error );
    intptr_t (*FN_VR_GetGenericInterface)( स्थिर अक्षर *pchInterfaceVersion, EVRInitError *peError );

    पूर्णांक is_बफर_rendering;

    अचिन्हित पूर्णांक overlaytexture;

    अचिन्हित पूर्णांक fbo, rbo;

    पूर्णांक saved_texture_state;

    काष्ठा VR_IVRSystem_FnTable *oSystem;
    काष्ठा VR_IVROverlay_FnTable *oOverlay;
	काष्ठा VR_IVRInput_FnTable * o_निवेश;
	VROverlayHandle_t overlayID, thumbID, cursorID;
	
	अक्षर * sOverlayName;

	VRActionSetHandle_t निवेश_action_set;
	VRActionHandle_t * निवेश_action_handles_buttons;
	पूर्णांक निवेश_action_handles_buttons_गिनती;
	VRActionHandle_t * निवेश_action_handles_axes;
	पूर्णांक निवेश_action_handles_axes_गिनती;
	VRActionHandle_t निवेश_action_handles_haptics[2];

    bool bHasShownOverlay;
    पूर्णांक targw, targh;
    पूर्णांक last_targw, last_targh;
    पूर्णांक swap_interval;

    bool bDidCreateOverlay;
	bool renderdoc_debugmarker_frame_end;
	bool bIconOverridden;
	
	SDL_Window * window;
	
	SDL_Joystick *virtual_joystick;
#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS
    HDC hdc;
    HGLRC hglrc;
#अन्यथा
    EGLDisplay eglDpy;
    EGLContext eglCtx;
#पूर्ण_अगर
};

काष्ठा SDL_Display_तथ्य
{
    पूर्णांक dummy;
};

#पूर्ण_अगर
