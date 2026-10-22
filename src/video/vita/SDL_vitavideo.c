/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VITA

// SDL internals
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"

// VITA declarations
#అన్తర్భావ <psp2/kernel/processmgr.h>
#అన్తర్భావ "SDL_vitavideo.h"
#అన్తర్భావ "SDL_vitatouch.h"
#అన్తర్భావ "SDL_vitakeyboard.h"
#అన్తర్భావ "SDL_vitamouse_c.h"
#అన్తర్భావ "SDL_vitaframebuffer.h"
#అన్తర్భావ "SDL_vitamessagebox.h"

#ఒకవేళ defined(SDL_VIDEO_VITA_PVR)
#నిర్వచించు VITA_GLES_Get_Proc_చిరునామా  SDL_EGL_Get_Proc_చిరునామా_అంతర్గత
#నిర్వచించు VITA_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#నిర్వచించు VITA_GLES_సమితి_మార్పిడి_Interval SDL_EGL_సమితి_మార్పిడి_Interval
#నిర్వచించు VITA_GLES_Get_మార్పిడి_Interval SDL_EGL_Get_మార్పిడి_Interval
#నిర్వచించు VITA_GLES_DestroyContext   SDL_EGL_DestroyContext
#అయితే_ముగింపు

SDL_కిటికీ *Vita_కిటికీ;

స్థిర శూన్య VITA_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->అంతర్గత);
    SDL_free(device);
}

స్థిర SDL_VideoDevice *VITA_Create(శూన్య)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *phdata;
#నిర్వచితమైతే SDL_VIDEO_VITA_PIB
    SDL_GLDriver_దత్తాంశం *gldata;
#అయితే_ముగింపు
    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    // Initialize internal VITA specific data
    phdata = (SDL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Video_దత్తాంశం));
    ఒకవేళ (!phdata) {
        SDL_free(device);
        తిరిగి ఖాళీ;
    }
#నిర్వచితమైతే SDL_VIDEO_VITA_PIB

    gldata = (SDL_GLDriver_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_GLDriver_దత్తాంశం));
    ఒకవేళ (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        తిరిగి ఖాళీ;
    }
    device->gl_దత్తాంశం = gldata;
    phdata->egl_initialized = true;
#అయితే_ముగింపు
    phdata->ime_చురుకైన = false;

    device->అంతర్గత = phdata;

    // Setup amount of available displays and current display
    device->అంకె_displays = 0;

    // Set device free function
    device->విడుదల = VITA_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VITA_VideoInit;
    device->VideoQuit = VITA_VideoQuit;
    device->CreateSDLWindow = VITA_Create_కిటికీ;
    device->సమితి_కిటికీ_Title = VITA_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_Position = VITA_సమితి_కిటికీ_Position;
    device->సమితి_కిటికీ_కొలత = VITA_సమితి_కిటికీ_కొలత;
    device->Show_కిటికీ = VITA_Show_కిటికీ;
    device->Hide_కిటికీ = VITA_Hide_కిటికీ;
    device->Raise_కిటికీ = VITA_Raise_కిటికీ;
    device->Maximize_కిటికీ = VITA_Maximize_కిటికీ;
    device->Minimize_కిటికీ = VITA_Minimize_కిటికీ;
    device->Restore_కిటికీ = VITA_Restore_కిటికీ;
    device->సమితి_కిటికీ_Mouse_Grab = VITA_సమితి_కిటికీ_Grab;
    device->సమితి_కిటికీ_Keyboard_Grab = VITA_సమితి_కిటికీ_Grab;
    device->Destroy_కిటికీ = VITA_Destroy_కిటికీ;

    /*
        // Disabled, causes issues on high-framerate updates. SDL still emulates this.
        // TODO: Is VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER needed?
        device->CreateWindowFramebuffer = VITA_CreateWindowFramebuffer;
        device->UpdateWindowFramebuffer = VITA_UpdateWindowFramebuffer;
        device->DestroyWindowFramebuffer = VITA_DestroyWindowFramebuffer;
    */

#ఒకవేళ defined(SDL_VIDEO_VITA_PIB) || defined(SDL_VIDEO_VITA_PVR)
#నిర్వచితమైతే SDL_VIDEO_VITA_PVR_OGL
    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false)) {
        device->GL_ఎక్కించు_Library = VITA_GL_ఎక్కించు_Library;
        device->GL_CreateContext = VITA_GL_CreateContext;
        device->GL_Get_Proc_చిరునామా = VITA_GL_Get_Proc_చిరునామా;
    } లేకపోతే {
#అయితే_ముగింపు
        device->GL_ఎక్కించు_Library = VITA_GLES_ఎక్కించు_Library;
        device->GL_CreateContext = VITA_GLES_CreateContext;
        device->GL_Get_Proc_చిరునామా = VITA_GLES_Get_Proc_చిరునామా;
#నిర్వచితమైతే SDL_VIDEO_VITA_PVR_OGL
    }
#అయితే_ముగింపు

    device->GL_UnloadLibrary = VITA_GLES_UnloadLibrary;
    device->GL_MakeCurrent = VITA_GLES_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = VITA_GLES_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = VITA_GLES_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = VITA_GLES_మార్పిడి_కిటికీ;
    device->GL_DestroyContext = VITA_GLES_DestroyContext;
#అయితే_ముగింపు

    device->HasScreenKeyboardSupport = VITA_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = VITA_ShowScreenKeyboard;
    device->HideScreenKeyboard = VITA_HideScreenKeyboard;

    device->PumpEvents = VITA_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    తిరిగి device;
}

VideoBootStrap VITA_bootstrap = {
    "vita",
    "VITA Video Driver",
    VITA_Create,
    VITA_Show_సందేశం_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool VITA_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_బహుళకం బహుళకం;
#నిర్వచితమైతే SDL_VIDEO_VITA_PVR
    స్థిరరాశి అక్షరం *res = SDL_GetHint(SDL_HINT_VITA_RESOLUTION);
#అయితే_ముగింపు
    SDL_zero(బహుళకం);

#నిర్వచితమైతే SDL_VIDEO_VITA_PVR
    ఒకవేళ (res) {
        // 1088i for PSTV (Or Sharpscale)
        ఒకవేళ (SDL_strncmp(res, "1080", 4) == 0) {
            బహుళకం.w = 1920;
            బహుళకం.h = 1088;
        }
        // 725p for PSTV (Or Sharpscale)
        లేకపోతే ఒకవేళ (SDL_strncmp(res, "720", 3) == 0) {
            బహుళకం.w = 1280;
            బహుళకం.h = 725;
        }
    }
    // 544p
    లేకపోతే {
#అయితే_ముగింపు
        బహుళకం.w = 960;
        బహుళకం.h = 544;
#నిర్వచితమైతే SDL_VIDEO_VITA_PVR
    }
#అయితే_ముగింపు

    బహుళకం.refresh_రేటు = 60.0f;

    // 32 bpp for default
    బహుళకం.format = SDL_PIXELFORMAT_ABGR8888;

    ఒకవేళ (SDL_కూడు_Basic_Video_Display(&బహుళకం) == 0) {
        తిరిగి false;
    }

    VITA_InitTouch();
    VITA_InitKeyboard();
    VITA_InitMouse();

    తిరిగి true;
}

శూన్య VITA_VideoQuit(SDL_VideoDevice *_this)
{
    VITA_QuitTouch();
}

bool VITA_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_కిటికీ_దత్తాంశం *wdata;
#నిర్వచితమైతే SDL_VIDEO_VITA_PVR
    Psp2_Native_కిటికీ win;
    పూర్ణాంకం తాత్కాలిక_major = 2;
    పూర్ణాంకం తాత్కాలిక_minor = 1;
    పూర్ణాంకం తాత్కాలిక_profile = 0;
#అయితే_ముగింపు

    // Allocate window internal data
    wdata = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_కిటికీ_దత్తాంశం));
    ఒకవేళ (!wdata) {
        తిరిగి false;
    }

    // Setup driver data for this window
    కిటికీ->అంతర్గత = wdata;

    // Vita can only have one window
    ఒకవేళ (Vita_కిటికీ) {
        తిరిగి SDL_సమితి_Error("Only one window supported");
    }

    Vita_కిటికీ = కిటికీ;

#నిర్వచితమైతే SDL_VIDEO_VITA_PVR
    win.type = PSP2_DRAWABLE_TYPE_కిటికీ;
    win.అంకె_Flip_Buffers = 2;
    win.flipChainThrdAffinity = 0x20000;

    // 1088i for PSTV (Or Sharpscale)
    ఒకవేళ (కిటికీ->w == 1920) {
        win.కిటికీ_కొలత = PSP2_కిటికీ_1920_X1088;
    }
    // 725p for PSTV (Or Sharpscale)
    లేకపోతే ఒకవేళ (కిటికీ->w == 1280) {
        win.కిటికీ_కొలత = PSP2_కిటికీ_1280_X725;
    }
    // 544p
    లేకపోతే {
        win.కిటికీ_కొలత = PSP2_కిటికీ_960_X544;
    }
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
        bool use_opengl = SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false);
        ఒకవేళ (use_opengl) {
            // Set version to 2.1 and PROFILE to ES
            తాత్కాలిక_major = _this->gl_config.major_సంస్కరణ;
            తాత్కాలిక_minor = _this->gl_config.minor_సంస్కరణ;
            తాత్కాలిక_profile = _this->gl_config.profile_ముసుగు;

            _this->gl_config.major_సంస్కరణ = 2;
            _this->gl_config.minor_సంస్కరణ = 1;
            _this->gl_config.profile_ముసుగు = SDL_GL_CONTEXT_PROFILE_ES;
        }
        wdata->egl_surface = SDL_EGL_CreateSurface(_this, కిటికీ, &win);
        ఒకవేళ (wdata->egl_surface == EGL_NO_SURFACE) {
            తిరిగి SDL_సమితి_Error("Could not create GLES window surface");
        }
        ఒకవేళ (use_opengl) {
            // Revert
            _this->gl_config.major_సంస్కరణ = తాత్కాలిక_major;
            _this->gl_config.minor_సంస్కరణ = తాత్కాలిక_minor;
            _this->gl_config.profile_ముసుగు = తాత్కాలిక_profile;
        }
    }
#అయితే_ముగింపు

    // fix input, we need to find a better way
    SDL_సమితి_Keyboard_Focus(కిటికీ);

    // Window has been successfully created
    తిరిగి true;
}

శూన్య VITA_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
bool VITA_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    తిరిగి SDL_Unsupported();
}
శూన్య VITA_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య VITA_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య VITA_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య VITA_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య VITA_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య VITA_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య VITA_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
bool VITA_సమితి_కిటికీ_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed)
{
    తిరిగి true;
}

శూన్య VITA_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;

    దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_free(దత్తాంశం);

    కిటికీ->అంతర్గత = ఖాళీ;
    Vita_కిటికీ = ఖాళీ;
}

bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    తిరిగి true;
}

#నిర్వచితం_కాకపోతే SCE_IME_LANGUAGE_ENGLISH_US
#నిర్వచించు SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#అయితే_ముగింపు

స్థిర శూన్య utf16_గమ్యం_utf8(స్థిరరాశి uint16_t *src, uint8_t *dst)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; src[i]; i++) {
        ఒకవేళ (!(src[i] & 0xFF80)) {
            *(dst++) = src[i] & 0xFF;
        } లేకపోతే ఒకవేళ (!(src[i] & 0xF800)) {
            *(dst++) = ((src[i] >> 6) & 0xFF) | 0xC0;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        } లేకపోతే ఒకవేళ ((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
            *(dst++) = (((src[i] + 64) >> 8) & 0x3) | 0xF0;
            *(dst++) = (((src[i] >> 2) + 16) & 0x3F) | 0x80;
            *(dst++) = ((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF);
            *(dst++) = (src[i + 1] & 0x3F) | 0x80;
            i += 1;
        } లేకపోతే {
            *(dst++) = ((src[i] >> 12) & 0xF) | 0xE0;
            *(dst++) = ((src[i] >> 6) & 0x3F) | 0x80;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        }
    }

    *dst = '\0';
}

#నిర్వచితమైతే SDL_VIDEO_VITA_PVR
SceWChar16 libime_బహిర్గతం[SCE_IME_MAX_PREEDIT_నిడివి + SCE_IME_MAX_పాఠ్యం_నిడివి + 1];
అక్షరం libime_initval[8] = { 1 };
SceImeCaret caret_rev;

శూన్య VITA_ImeEventHandler(శూన్య *arg, స్థిరరాశి Sce_Ime_Event_దత్తాంశం *e)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)arg;
    uint8_t utf8_బఫరు[SCE_IME_MAX_పాఠ్యం_నిడివి];
    ఎంపిక (e->id) {
    స్థితి SCE_IME_EVENT_UPDATE_పాఠ్యం:
        ఒకవేళ (e->param.పాఠ్యం.caret_సూచీ == 0) {
            SDL_Send_Keyboard_కీలకం_Auto_Release(0, SDL_SCANCODE_BACKSPACE);
            sce_Ime_సమితి_పాఠ్యం((SceWChar16 *)libime_initval, 4);
        } లేకపోతే {
            utf16_గమ్యం_utf8((SceWChar16 *)&libime_బహిర్గతం[1], utf8_బఫరు);
            ఒకవేళ (utf8_బఫరు[0] == ' ') {
                SDL_Send_Keyboard_కీలకం_Auto_Release(0, SDL_SCANCODE_SPACE);
            } లేకపోతే {
                SDL_Send_Keyboard_పాఠ్యం((స్థిరరాశి అక్షరం *)utf8_బఫరు);
            }
            SDL_zero(caret_rev);
            SDL_memset(libime_బహిర్గతం, 0, ((SCE_IME_MAX_PREEDIT_నిడివి + SCE_IME_MAX_పాఠ్యం_నిడివి + 1) * పరిమాణం(SceWChar16)));
            caret_rev.సూచీ = 1;
            sce_Ime_సమితి_Caret(&caret_rev);
            sce_Ime_సమితి_పాఠ్యం((SceWChar16 *)libime_initval, 4);
        }
        ఆపు;
    స్థితి SCE_IME_EVENT_PRESS_ENTER:
        SDL_Send_Keyboard_కీలకం_Auto_Release(0, SDL_SCANCODE_RETURN);
        ఆపు;
    స్థితి SCE_IME_EVENT_PRESS_CLOSE:
        sceImeClose();
        videodata->ime_చురుకైన = false;
        SDL_SendScreenKeyboardHidden();
        ఆపు;
    }
}
#అయితే_ముగింపు // SDL_VIDEO_VITA_PVR

శూన్య VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    SceInt32 res;

#నిర్వచితమైతే SDL_VIDEO_VITA_PVR

    SceUInt32 libime_work[SCE_IME_WORK_బఫరు_కొలత / పరిమాణం(SceInt32)];
    SceImeParam param;

    sceImeParamInit(&param);

    SDL_memset(libime_బహిర్గతం, 0, ((SCE_IME_MAX_PREEDIT_నిడివి + SCE_IME_MAX_పాఠ్యం_నిడివి + 1) * పరిమాణం(SceWChar16)));

    param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
    param.languagesForced = SCE_FALSE;
    ఎంపిక (SDL_Get_పాఠ్యం_ఆదానం_Type(props)) {
    అప్రమేయ:
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం:
        param.type = SCE_IME_TYPE_DEFAULT;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_NAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_EMAIL:
        param.type = SCE_IME_TYPE_MAIL;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_USERNAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_DEFAULT;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_DEFAULT;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య:
        param.type = SCE_IME_TYPE_సంఖ్య;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_సంఖ్య;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_సంఖ్య;
        ఆపు;
    }
    param.option = 0;
    ఒకవేళ (SDL_Get_పాఠ్యం_ఆదానం_Capitalization(props) != SDL_CAPITALIZE_SENTENCES) {
        param.option |= SCE_IME_OPTION_NO_AUTO_CAPITALIZATION;
    }
    ఒకవేళ (!SDL_Get_పాఠ్యం_ఆదానం_Autocorrect(props)) {
        param.option |= SCE_IME_OPTION_NO_ASSISTANCE;
    }
    ఒకవేళ (SDL_Get_పాఠ్యం_ఆదానం_Multiline(props)) {
        param.option |= SCE_IME_OPTION_MULTILINE;
    }
    param.ఆదానం_పాఠ్యం_బఫరు = libime_బహిర్గతం;
    param.max_పాఠ్యం_నిడివి = SCE_IME_MAX_పాఠ్యం_నిడివి;
    param.handler = VITA_ImeEventHandler;
    param.filter = ఖాళీ;
    param.initial_పాఠ్యం = (SceWChar16 *)libime_initval;
    param.arg = videodata;
    param.work = libime_work;

    res = sceImeOpen(&param);
    ఒకవేళ (res < 0) {
        SDL_సమితి_Error("Failed to init IME");
        తిరిగి;
    }

#లేకపోతే
    SceWChar16 *title = u"";
    SceWChar16 *పాఠ్యం = u"";

    SceImeDialogParam param;
    sceImeDialogParamInit(&param);

    param.supportedLanguages = 0;
    param.languagesForced = SCE_FALSE;
    param.type = SCE_IME_TYPE_DEFAULT;
    param.option = 0;
    param.పాఠ్యం_Box_బహుళకం = SCE_IME_DIALOG_TEXTBOX_బహుళకం_WITH_CLEAR;
    param.max_పాఠ్యం_నిడివి = SCE_IME_DIALOG_MAX_పాఠ్యం_నిడివి;

    param.title = title;
    param.initial_పాఠ్యం = పాఠ్యం;
    param.ఆదానం_పాఠ్యం_బఫరు = videodata->ime_బఫరు;

    res = sceImeDialogInit(&param);
    ఒకవేళ (res < 0) {
        SDL_సమితి_Error("Failed to init IME dialog");
        తిరిగి;
    }

#అయితే_ముగింపు

    videodata->ime_చురుకైన = true;

    SDL_SendScreenKeyboardShown();
}

శూన్య VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#నిర్వచితం_కాకపోతే SDL_VIDEO_VITA_PVR
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;

    Sce_Common_Dialog_స్థితి dialog_స్థితి = sce_Ime_Dialog_Get_స్థితి();

    ఎంపిక (dialog_స్థితి) {
    అప్రమేయ:
    స్థితి SCE_COMMON_DIALOG_స్థితి_NONE:
    స్థితి SCE_COMMON_DIALOG_స్థితి_RUNNING:
        ఆపు;
    స్థితి SCE_COMMON_DIALOG_స్థితి_ముగిసిన:
        sce_Ime_Dialog_పదం();
        ఆపు;
    }

    videodata->ime_చురుకైన = false;

    SDL_SendScreenKeyboardHidden();
#అయితే_ముగింపు
}

శూన్య VITA_PumpEvents(SDL_VideoDevice *_this)
{
#నిర్వచితం_కాకపోతే SDL_VIDEO_VITA_PVR
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
#అయితే_ముగింపు

    ఒకవేళ (_this->suspend_screensaver) {
        // cancel all idle timers to prevent vita going to sleep
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
    }

    VITA_PollTouch();
    VITA_PollKeyboard();
    VITA_PollMouse();

#నిర్వచితం_కాకపోతే SDL_VIDEO_VITA_PVR
    ఒకవేళ (videodata->ime_చురుకైన == true) {
        // update IME status. Terminate, if finished
        Sce_Common_Dialog_స్థితి dialog_స్థితి = sce_Ime_Dialog_Get_స్థితి();
        ఒకవేళ (dialog_స్థితి == SCE_COMMON_DIALOG_స్థితి_ముగిసిన) {
            uint8_t utf8_బఫరు[SCE_IME_DIALOG_MAX_పాఠ్యం_నిడివి];

            Sce_Ime_Dialog_ఫలితం ఫలితం;
            SDL_zero(ఫలితం);
            sce_Ime_Dialog_Get_ఫలితం(&ఫలితం);

            // Convert UTF16 to UTF8
            utf16_గమ్యం_utf8(videodata->ime_బఫరు, utf8_బఫరు);

            // Send SDL event
            SDL_Send_Keyboard_పాఠ్యం((స్థిరరాశి అక్షరం *)utf8_బఫరు);

            // Send enter key only on enter
            ఒకవేళ (ఫలితం.button == SCE_IME_DIALOG_BUTTON_ENTER) {
                SDL_Send_Keyboard_కీలకం_Auto_Release(0, SDL_SCANCODE_RETURN);
            }

            sce_Ime_Dialog_పదం();

            videodata->ime_చురుకైన = false;

            SDL_SendScreenKeyboardHidden();
        }
    }
#అయితే_ముగింపు
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VITA
