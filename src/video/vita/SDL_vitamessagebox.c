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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_vitamessagebox.h"
#ಅನ್ತರ್ಭಾವ <psp2/message_dialog.h>

#ifdef SDL_VIDEO_RENDER_VITA_GXM
#ಅನ್ತರ್ಭಾವ "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#endif // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_ShowMessageBox(ಧ್ರುವ SDL_MessageBoxData *messageboxdata, ಪೂರ್ಣಾಙ್ಕ *buttonID)
{
#ifdef SDL_VIDEO_RENDER_VITA_GXM
    Sce_ಸಂದೇಶ_Dialog_Param param;
    Sce_ಸಂದೇಶ_Dialog_User_Message_Param ಸಂದೇಶ_Param;
    Sce_ಸಂದೇಶ_Dialog_Buttons_Param buttonParam;
    SceDisplayFrameBuf dispparam;
    ವರ್ಣ message[512];

    Sce_ಸಂದೇಶ_Dialog_Result dialog_result;
    SceCommonDialogErrorCode init_result;
    bool setup_minimal_gxm = false;

    ಯದಿ (messageboxdata->numbuttons > 3) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_zero(param);
    sce_ಸಂದೇಶ_Dialog_Param_Init(&param);
    param.mode = SCE_ಸಂದೇಶ_DIALOG_MODE_USER_ಸಂದೇಶ;

    SDL_zero(ಸಂದೇಶ_Param);
    SDL_snprintf(message, ಪರಿಮಾಣ(message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

    ಸಂದೇಶ_Param.ಸಂದೇಶ = (ಧ್ರುವ SceChar8 *)message;
    SDL_zero(buttonParam);

    ಯದಿ (messageboxdata->numbuttons == 3) {
        ಸಂದೇಶ_Param.buttonType = SCE_ಸಂದೇಶ_DIALOG_BUTTON_TYPE_3_BUTTONS;
        ಸಂದೇಶ_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].text;
        buttonParam.msg2 = messageboxdata->buttons[1].text;
        buttonParam.msg3 = messageboxdata->buttons[2].text;
    } ಅನ್ಯಥಾ ಯದಿ (messageboxdata->numbuttons == 2) {
        ಸಂದೇಶ_Param.buttonType = SCE_ಸಂದೇಶ_DIALOG_BUTTON_TYPE_YESNO;
    } ಅನ್ಯಥಾ ಯದಿ (messageboxdata->numbuttons == 1) {
        ಸಂದೇಶ_Param.buttonType = SCE_ಸಂದೇಶ_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_ಸಂದೇಶ_Param = &ಸಂದೇಶ_Param;

    dispparam.size = ಪರಿಮಾಣ(dispparam);

    init_result = sce_ಸಂದೇಶ_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    ಯದಿ (init_result == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_minimal_init_for_common_dialog();
        init_result = sce_ಸಂದೇಶ_Dialog_Init(&param);
        setup_minimal_gxm = true;
    }

    gxm_init_for_common_dialog();

    ಯದಿ (init_result >= 0) {
        ಯಾವತ್ (sce_ಸಂದೇಶ_Dialog_Get_Status() == SCE_COMMON_DIALOG_STATUS_RUNNING) {
            gxm_swap_for_common_dialog();
        }
        SDL_zero(dialog_result);
        sce_ಸಂದೇಶ_Dialog_Get_Result(&dialog_result);

        ಯದಿ (dialog_result.buttonId == SCE_ಸಂದೇಶ_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } ಅನ್ಯಥಾ ಯದಿ (dialog_result.buttonId == SCE_ಸಂದೇಶ_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } ಅನ್ಯಥಾ ಯದಿ (dialog_result.buttonId == SCE_ಸಂದೇಶ_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } ಅನ್ಯಥಾ ಯದಿ (dialog_result.buttonId == SCE_ಸಂದೇಶ_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } ಅನ್ಯಥಾ ಯದಿ (dialog_result.buttonId == SCE_ಸಂದೇಶ_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } ಅನ್ಯಥಾ ಯದಿ (dialog_result.buttonId == SCE_ಸಂದೇಶ_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_ಸಂದೇಶ_Dialog_Term();
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    gxm_term_for_common_dialog();

    ಯದಿ (setup_minimal_gxm) {
        gxm_minimal_term_for_common_dialog();
    }

    ಪ್ರತ್ಯಾಗಮ true;
#ಅನ್ಯಥಾ
    (ಶೂನ್ಯ)messageboxdata;
    (ಶೂನ್ಯ)buttonID;
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
#endif // SDL_VIDEO_RENDER_VITA_GXM
}

#endif // SDL_VIDEO_DRIVER_VITA
