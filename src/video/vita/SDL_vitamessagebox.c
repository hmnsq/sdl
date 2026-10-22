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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#अन्तर्भाव "SDL_vitavideo.h"
#अन्तर्भाव "SDL_vitamessagebox.h"
#अन्तर्भाव <psp2/message_dialog.h>

#ifdef SDL_VIDEO_RENDER_VITA_GXM
#अन्तर्भाव "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#endif // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_ShowMessageBox(ध्रुव SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID)
{
#ifdef SDL_VIDEO_RENDER_VITA_GXM
    Sce_सन्देशः_Dialog_Param param;
    Sce_सन्देशः_Dialog_User_Message_Param सन्देशः_Param;
    Sce_सन्देशः_Dialog_Buttons_Param buttonParam;
    SceDisplayFrameBuf dispparam;
    वर्ण message[512];

    Sce_सन्देशः_Dialog_Result dialog_result;
    SceCommonDialogErrorCode init_result;
    bool setup_minimal_gxm = false;

    सचे (messageboxdata->numbuttons > 3) {
        पटिनिवत्त false;
    }

    SDL_zero(param);
    sce_सन्देशः_Dialog_Param_Init(&param);
    param.mode = SCE_सन्देशः_DIALOG_MODE_USER_सन्देशः;

    SDL_zero(सन्देशः_Param);
    SDL_snprintf(message, परिमाण(message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

    सन्देशः_Param.सन्देशः = (ध्रुव SceChar8 *)message;
    SDL_zero(buttonParam);

    सचे (messageboxdata->numbuttons == 3) {
        सन्देशः_Param.buttonType = SCE_सन्देशः_DIALOG_BUTTON_TYPE_3_BUTTONS;
        सन्देशः_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].text;
        buttonParam.msg2 = messageboxdata->buttons[1].text;
        buttonParam.msg3 = messageboxdata->buttons[2].text;
    } अञ्ञथा सचे (messageboxdata->numbuttons == 2) {
        सन्देशः_Param.buttonType = SCE_सन्देशः_DIALOG_BUTTON_TYPE_YESNO;
    } अञ्ञथा सचे (messageboxdata->numbuttons == 1) {
        सन्देशः_Param.buttonType = SCE_सन्देशः_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_सन्देशः_Param = &सन्देशः_Param;

    dispparam.size = परिमाण(dispparam);

    init_result = sce_सन्देशः_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    सचे (init_result == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_minimal_init_for_common_dialog();
        init_result = sce_सन्देशः_Dialog_Init(&param);
        setup_minimal_gxm = true;
    }

    gxm_init_for_common_dialog();

    सचे (init_result >= 0) {
        याव (sce_सन्देशः_Dialog_Get_Status() == SCE_COMMON_DIALOG_STATUS_RUNNING) {
            gxm_swap_for_common_dialog();
        }
        SDL_zero(dialog_result);
        sce_सन्देशः_Dialog_Get_Result(&dialog_result);

        सचे (dialog_result.buttonId == SCE_सन्देशः_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } अञ्ञथा सचे (dialog_result.buttonId == SCE_सन्देशः_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } अञ्ञथा सचे (dialog_result.buttonId == SCE_सन्देशः_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } अञ्ञथा सचे (dialog_result.buttonId == SCE_सन्देशः_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } अञ्ञथा सचे (dialog_result.buttonId == SCE_सन्देशः_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } अञ्ञथा सचे (dialog_result.buttonId == SCE_सन्देशः_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_सन्देशः_Dialog_Term();
    } अञ्ञथा {
        पटिनिवत्त false;
    }

    gxm_term_for_common_dialog();

    सचे (setup_minimal_gxm) {
        gxm_minimal_term_for_common_dialog();
    }

    पटिनिवत्त true;
#अञ्ञथा
    (शून्य)messageboxdata;
    (शून्य)buttonID;
    पटिनिवत्त SDL_Unsupported();
#endif // SDL_VIDEO_RENDER_VITA_GXM
}

#endif // SDL_VIDEO_DRIVER_VITA
