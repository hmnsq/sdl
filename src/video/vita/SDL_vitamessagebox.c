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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#অন্তর্ভাৱ "SDL_vitavideo.h"
#অন্তর্ভাৱ "SDL_vitamessagebox.h"
#অন্তর্ভাৱ <psp2/message_dialog.h>

#ifdef SDL_VIDEO_RENDER_VITA_GXM
#অন্তর্ভাৱ "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#endif // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_ShowMessageBox(ধ্রুৱ SDL_MessageBoxData *messageboxdata, পূর্ণাঙ্ক *buttonID)
{
#ifdef SDL_VIDEO_RENDER_VITA_GXM
    Sce_বাৰ্তা_Dialog_Param param;
    Sce_বাৰ্তা_Dialog_User_Message_Param বাৰ্তা_Param;
    Sce_বাৰ্তা_Dialog_Buttons_Param buttonParam;
    SceDisplayFrameBuf dispparam;
    ৱর্ণ message[512];

    Sce_বাৰ্তা_Dialog_Result dialog_result;
    SceCommonDialogErrorCode init_result;
    bool setup_minimal_gxm = false;

    যদি (messageboxdata->numbuttons > 3) {
        ঘূৰাই false;
    }

    SDL_zero(param);
    sce_বাৰ্তা_Dialog_Param_Init(&param);
    param.mode = SCE_বাৰ্তা_DIALOG_MODE_USER_বাৰ্তা;

    SDL_zero(বাৰ্তা_Param);
    SDL_snprintf(message, পরিমাণ(message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

    বাৰ্তা_Param.বাৰ্তা = (ধ্রুৱ SceChar8 *)message;
    SDL_zero(buttonParam);

    যদি (messageboxdata->numbuttons == 3) {
        বাৰ্তা_Param.buttonType = SCE_বাৰ্তা_DIALOG_BUTTON_TYPE_3_BUTTONS;
        বাৰ্তা_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].text;
        buttonParam.msg2 = messageboxdata->buttons[1].text;
        buttonParam.msg3 = messageboxdata->buttons[2].text;
    } অন্যথা যদি (messageboxdata->numbuttons == 2) {
        বাৰ্তা_Param.buttonType = SCE_বাৰ্তা_DIALOG_BUTTON_TYPE_YESNO;
    } অন্যথা যদি (messageboxdata->numbuttons == 1) {
        বাৰ্তা_Param.buttonType = SCE_বাৰ্তা_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_বাৰ্তা_Param = &বাৰ্তা_Param;

    dispparam.size = পরিমাণ(dispparam);

    init_result = sce_বাৰ্তা_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    যদি (init_result == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_minimal_init_for_common_dialog();
        init_result = sce_বাৰ্তা_Dialog_Init(&param);
        setup_minimal_gxm = true;
    }

    gxm_init_for_common_dialog();

    যদি (init_result >= 0) {
        যেতিয়ালৈ (sce_বাৰ্তা_Dialog_Get_Status() == SCE_COMMON_DIALOG_STATUS_RUNNING) {
            gxm_swap_for_common_dialog();
        }
        SDL_zero(dialog_result);
        sce_বাৰ্তা_Dialog_Get_Result(&dialog_result);

        যদি (dialog_result.buttonId == SCE_বাৰ্তা_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } অন্যথা যদি (dialog_result.buttonId == SCE_বাৰ্তা_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } অন্যথা যদি (dialog_result.buttonId == SCE_বাৰ্তা_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } অন্যথা যদি (dialog_result.buttonId == SCE_বাৰ্তা_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } অন্যথা যদি (dialog_result.buttonId == SCE_বাৰ্তা_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } অন্যথা যদি (dialog_result.buttonId == SCE_বাৰ্তা_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_বাৰ্তা_Dialog_Term();
    } অন্যথা {
        ঘূৰাই false;
    }

    gxm_term_for_common_dialog();

    যদি (setup_minimal_gxm) {
        gxm_minimal_term_for_common_dialog();
    }

    ঘূৰাই true;
#অন্যথা
    (শূন্য)messageboxdata;
    (শূন্য)buttonID;
    ঘূৰাই SDL_Unsupported();
#endif // SDL_VIDEO_RENDER_VITA_GXM
}

#endif // SDL_VIDEO_DRIVER_VITA
