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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#অন্তর্ভাব "SDL_vitavideo.h"
#অন্তর্ভাব "SDL_vitamessagebox.h"
#অন্তর্ভাব <psp2/message_dialog.h>

#ifdef SDL_VIDEO_RENDER_VITA_GXM
#অন্তর্ভাব "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#endif // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_ShowMessageBox(ধ্রুবক SDL_Message_Box_তথ্য *messageboxdata, পূর্ণসংখ্যা *buttonID)
{
#ifdef SDL_VIDEO_RENDER_VITA_GXM
    Sce_বার্তা_Dialog_Param param;
    Sce_বার্তা_Dialog_User_Message_Param বার্তা_Param;
    Sce_বার্তা_Dialog_Buttons_Param buttonParam;
    SceDisplayFrameBuf dispparam;
    অক্ষর message[512];

    Sce_বার্তা_Dialog_ফলাফল dialog_ফলাফল;
    SceCommonDialogErrorCode init_ফলাফল;
    bool setup_minimal_gxm = false;

    যদি (messageboxdata->numbuttons > 3) {
        ফেরত false;
    }

    SDL_zero(param);
    sce_বার্তা_Dialog_Param_Init(&param);
    param.mode = SCE_বার্তা_DIALOG_MODE_USER_বার্তা;

    SDL_zero(বার্তা_Param);
    SDL_snprintf(message, আকার(message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

    বার্তা_Param.বার্তা = (ধ্রুবক SceChar8 *)message;
    SDL_zero(buttonParam);

    যদি (messageboxdata->numbuttons == 3) {
        বার্তা_Param.buttonType = SCE_বার্তা_DIALOG_BUTTON_TYPE_3_BUTTONS;
        বার্তা_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].text;
        buttonParam.msg2 = messageboxdata->buttons[1].text;
        buttonParam.msg3 = messageboxdata->buttons[2].text;
    } অন্যথা যদি (messageboxdata->numbuttons == 2) {
        বার্তা_Param.buttonType = SCE_বার্তা_DIALOG_BUTTON_TYPE_YESNO;
    } অন্যথা যদি (messageboxdata->numbuttons == 1) {
        বার্তা_Param.buttonType = SCE_বার্তা_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_বার্তা_Param = &বার্তা_Param;

    dispparam.আকার_2 = আকার(dispparam);

    init_ফলাফল = sce_বার্তা_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    যদি (init_ফলাফল == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_minimal_init_for_common_dialog();
        init_ফলাফল = sce_বার্তা_Dialog_Init(&param);
        setup_minimal_gxm = true;
    }

    gxm_init_for_common_dialog();

    যদি (init_ফলাফল >= 0) {
        যখন (sce_বার্তা_Dialog_Get_Status() == SCE_COMMON_DIALOG_STATUS_RUNNING) {
            gxm_swap_for_common_dialog();
        }
        SDL_zero(dialog_ফলাফল);
        sce_বার্তা_Dialog_Get_ফলাফল(&dialog_ফলাফল);

        যদি (dialog_ফলাফল.buttonId == SCE_বার্তা_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } অন্যথা যদি (dialog_ফলাফল.buttonId == SCE_বার্তা_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } অন্যথা যদি (dialog_ফলাফল.buttonId == SCE_বার্তা_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } অন্যথা যদি (dialog_ফলাফল.buttonId == SCE_বার্তা_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } অন্যথা যদি (dialog_ফলাফল.buttonId == SCE_বার্তা_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } অন্যথা যদি (dialog_ফলাফল.buttonId == SCE_বার্তা_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_বার্তা_Dialog_Term();
    } অন্যথা {
        ফেরত false;
    }

    gxm_term_for_common_dialog();

    যদি (setup_minimal_gxm) {
        gxm_minimal_term_for_common_dialog();
    }

    ফেরত true;
#অন্যথা
    (শূন্য)messageboxdata;
    (শূন্য)buttonID;
    ফেরত SDL_Unsupported();
#endif // SDL_VIDEO_RENDER_VITA_GXM
}

#endif // SDL_VIDEO_DRIVER_VITA
