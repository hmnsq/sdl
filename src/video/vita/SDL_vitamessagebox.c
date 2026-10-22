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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#ଅନ୍ତର୍ଭାଵ "SDL_vitavideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_vitamessagebox.h"
#ଅନ୍ତର୍ଭାଵ <psp2/message_dialog.h>

#ifdef SDL_VIDEO_RENDER_VITA_GXM
#ଅନ୍ତର୍ଭାଵ "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#endif // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_ShowMessageBox(ଅଚଳ SDL_MessageBoxData *messageboxdata, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *buttonID)
{
#ifdef SDL_VIDEO_RENDER_VITA_GXM
    Sce_ସନ୍ଦେଶ_Dialog_Param param;
    Sce_ସନ୍ଦେଶ_Dialog_User_Message_Param ସନ୍ଦେଶ_Param;
    Sce_ସନ୍ଦେଶ_Dialog_Buttons_Param buttonParam;
    SceDisplayFrameBuf dispparam;
    ଅକ୍ଷର message[512];

    Sce_ସନ୍ଦେଶ_Dialog_Result dialog_result;
    SceCommonDialogErrorCode init_result;
    bool setup_minimal_gxm = false;

    ଯଦି (messageboxdata->numbuttons > 3) {
        ଫେରନ୍ତୁ false;
    }

    SDL_zero(param);
    sce_ସନ୍ଦେଶ_Dialog_Param_Init(&param);
    param.mode = SCE_ସନ୍ଦେଶ_DIALOG_MODE_USER_ସନ୍ଦେଶ;

    SDL_zero(ସନ୍ଦେଶ_Param);
    SDL_snprintf(message, ଆକାର(message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

    ସନ୍ଦେଶ_Param.ସନ୍ଦେଶ = (ଅଚଳ SceChar8 *)message;
    SDL_zero(buttonParam);

    ଯଦି (messageboxdata->numbuttons == 3) {
        ସନ୍ଦେଶ_Param.buttonType = SCE_ସନ୍ଦେଶ_DIALOG_BUTTON_TYPE_3_BUTTONS;
        ସନ୍ଦେଶ_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].text;
        buttonParam.msg2 = messageboxdata->buttons[1].text;
        buttonParam.msg3 = messageboxdata->buttons[2].text;
    } ଅନ୍ୟଥା ଯଦି (messageboxdata->numbuttons == 2) {
        ସନ୍ଦେଶ_Param.buttonType = SCE_ସନ୍ଦେଶ_DIALOG_BUTTON_TYPE_YESNO;
    } ଅନ୍ୟଥା ଯଦି (messageboxdata->numbuttons == 1) {
        ସନ୍ଦେଶ_Param.buttonType = SCE_ସନ୍ଦେଶ_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_ସନ୍ଦେଶ_Param = &ସନ୍ଦେଶ_Param;

    dispparam.size = ଆକାର(dispparam);

    init_result = sce_ସନ୍ଦେଶ_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    ଯଦି (init_result == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_minimal_init_for_common_dialog();
        init_result = sce_ସନ୍ଦେଶ_Dialog_Init(&param);
        setup_minimal_gxm = true;
    }

    gxm_init_for_common_dialog();

    ଯଦି (init_result >= 0) {
        ଯେତେବେଳେ (sce_ସନ୍ଦେଶ_Dialog_Get_Status() == SCE_COMMON_DIALOG_STATUS_RUNNING) {
            gxm_swap_for_common_dialog();
        }
        SDL_zero(dialog_result);
        sce_ସନ୍ଦେଶ_Dialog_Get_Result(&dialog_result);

        ଯଦି (dialog_result.buttonId == SCE_ସନ୍ଦେଶ_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } ଅନ୍ୟଥା ଯଦି (dialog_result.buttonId == SCE_ସନ୍ଦେଶ_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } ଅନ୍ୟଥା ଯଦି (dialog_result.buttonId == SCE_ସନ୍ଦେଶ_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } ଅନ୍ୟଥା ଯଦି (dialog_result.buttonId == SCE_ସନ୍ଦେଶ_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } ଅନ୍ୟଥା ଯଦି (dialog_result.buttonId == SCE_ସନ୍ଦେଶ_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } ଅନ୍ୟଥା ଯଦି (dialog_result.buttonId == SCE_ସନ୍ଦେଶ_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_ସନ୍ଦେଶ_Dialog_Term();
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ false;
    }

    gxm_term_for_common_dialog();

    ଯଦି (setup_minimal_gxm) {
        gxm_minimal_term_for_common_dialog();
    }

    ଫେରନ୍ତୁ true;
#ଅନ୍ୟଥା
    (ଶୂନ୍ୟ)messageboxdata;
    (ଶୂନ୍ୟ)buttonID;
    ଫେରନ୍ତୁ SDL_Unsupported();
#endif // SDL_VIDEO_RENDER_VITA_GXM
}

#endif // SDL_VIDEO_DRIVER_VITA
