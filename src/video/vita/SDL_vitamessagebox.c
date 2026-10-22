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
#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#شامل "SDL_vitavideo.h"
#شامل "SDL_vitamessagebox.h"
#شامل <psp2/message_dialog.h>

#ifdef SDL_VIDEO_RENDER_VITA_GXM
#شامل "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#endif // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_ShowMessageBox(ثابت SDL_MessageBoxData *messageboxdata, صحیح *buttonID)
{
#ifdef SDL_VIDEO_RENDER_VITA_GXM
    Sce_پیام_Dialog_Param param;
    Sce_پیام_Dialog_User_Message_Param پیام_Param;
    Sce_پیام_Dialog_Buttons_Param buttonParam;
    SceDisplayFrameBuf dispparam;
    نویسه message[512];

    Sce_پیام_Dialog_Result dialog_result;
    SceCommonDialogErrorCode init_result;
    bool setup_minimal_gxm = false;

    اگر (messageboxdata->numbuttons > 3) {
        بازگشت false;
    }

    SDL_zero(param);
    sce_پیام_Dialog_Param_Init(&param);
    param.mode = SCE_پیام_DIALOG_MODE_USER_پیام;

    SDL_zero(پیام_Param);
    SDL_snprintf(message, اندازه(message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

    پیام_Param.پیام = (ثابت SceChar8 *)message;
    SDL_zero(buttonParam);

    اگر (messageboxdata->numbuttons == 3) {
        پیام_Param.buttonType = SCE_پیام_DIALOG_BUTTON_TYPE_3_BUTTONS;
        پیام_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].text;
        buttonParam.msg2 = messageboxdata->buttons[1].text;
        buttonParam.msg3 = messageboxdata->buttons[2].text;
    } وگرنه اگر (messageboxdata->numbuttons == 2) {
        پیام_Param.buttonType = SCE_پیام_DIALOG_BUTTON_TYPE_YESNO;
    } وگرنه اگر (messageboxdata->numbuttons == 1) {
        پیام_Param.buttonType = SCE_پیام_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_پیام_Param = &پیام_Param;

    dispparam.size = اندازه(dispparam);

    init_result = sce_پیام_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    اگر (init_result == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_minimal_init_for_common_dialog();
        init_result = sce_پیام_Dialog_Init(&param);
        setup_minimal_gxm = true;
    }

    gxm_init_for_common_dialog();

    اگر (init_result >= 0) {
        وقتی (sce_پیام_Dialog_Get_Status() == SCE_COMMON_DIALOG_STATUS_RUNNING) {
            gxm_swap_for_common_dialog();
        }
        SDL_zero(dialog_result);
        sce_پیام_Dialog_Get_Result(&dialog_result);

        اگر (dialog_result.buttonId == SCE_پیام_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } وگرنه اگر (dialog_result.buttonId == SCE_پیام_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } وگرنه اگر (dialog_result.buttonId == SCE_پیام_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } وگرنه اگر (dialog_result.buttonId == SCE_پیام_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } وگرنه اگر (dialog_result.buttonId == SCE_پیام_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } وگرنه اگر (dialog_result.buttonId == SCE_پیام_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_پیام_Dialog_Term();
    } وگرنه {
        بازگشت false;
    }

    gxm_term_for_common_dialog();

    اگر (setup_minimal_gxm) {
        gxm_minimal_term_for_common_dialog();
    }

    بازگشت true;
#وگرنه
    (تهی)messageboxdata;
    (تهی)buttonID;
    بازگشت SDL_Unsupported();
#endif // SDL_VIDEO_RENDER_VITA_GXM
}

#endif // SDL_VIDEO_DRIVER_VITA
