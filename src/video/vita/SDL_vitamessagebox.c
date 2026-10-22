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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VITA

#شامل "SDL_vitavideo.h"
#شامل "SDL_vitamessagebox.h"
#شامل <psp2/message_dialog.h>

#اگر_تعریف_شدہ SDL_VIDEO_RENDER_VITA_GXM
#شامل "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#اگر_ختم // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_Show_پیغام_Box(ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonID)
{
#اگر_تعریف_شدہ SDL_VIDEO_RENDER_VITA_GXM
    Sce_پیغام_Dialog_Param param;
    Sce_پیغام_Dialog_User_پیغام_Param پیغام_Param;
    Sce_پیغام_Dialog_Buttons_Param buttonParam;
    Sce_Display_چوکھٹا_Buf dispparam;
    حرف پیغام[512];

    Sce_پیغام_Dialog_نتیجہ dialog_نتیجہ;
    Sce_Common_Dialog_Error_رمز init_نتیجہ;
    bool تیاری_اقل_gxm = false;

    اگر (messageboxdata->numbuttons > 3) {
        واپس false;
    }

    SDL_zero(param);
    sce_پیغام_Dialog_Param_Init(&param);
    param.منوال = SCE_پیغام_DIALOG_منوال_USER_پیغام;

    SDL_zero(پیغام_Param);
    SDL_snprintf(پیغام, حجم(پیغام), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->پیغام);

    پیغام_Param.پیغام_2 = (ثابت SceChar8 *)پیغام;
    SDL_zero(buttonParam);

    اگر (messageboxdata->numbuttons == 3) {
        پیغام_Param.buttonType = SCE_پیغام_DIALOG_BUTTON_TYPE_3_BUTTONS;
        پیغام_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].متن;
        buttonParam.msg2 = messageboxdata->buttons[1].متن;
        buttonParam.msg3 = messageboxdata->buttons[2].متن;
    } ورنہ اگر (messageboxdata->numbuttons == 2) {
        پیغام_Param.buttonType = SCE_پیغام_DIALOG_BUTTON_TYPE_YESNO;
    } ورنہ اگر (messageboxdata->numbuttons == 1) {
        پیغام_Param.buttonType = SCE_پیغام_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_پیغام_Param = &پیغام_Param;

    dispparam.سائز = حجم(dispparam);

    init_نتیجہ = sce_پیغام_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    اگر (init_نتیجہ == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_اقل_init_for_common_dialog();
        init_نتیجہ = sce_پیغام_Dialog_Init(&param);
        تیاری_اقل_gxm = true;
    }

    gxm_init_for_common_dialog();

    اگر (init_نتیجہ >= 0) {
        جب (sce_پیغام_Dialog_Get_حالت() == SCE_COMMON_DIALOG_حالت_RUNNING) {
            gxm_تبادلہ_for_common_dialog();
        }
        SDL_zero(dialog_نتیجہ);
        sce_پیغام_Dialog_Get_نتیجہ(&dialog_نتیجہ);

        اگر (dialog_نتیجہ.buttonId == SCE_پیغام_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } ورنہ اگر (dialog_نتیجہ.buttonId == SCE_پیغام_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } ورنہ اگر (dialog_نتیجہ.buttonId == SCE_پیغام_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } ورنہ اگر (dialog_نتیجہ.buttonId == SCE_پیغام_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } ورنہ اگر (dialog_نتیجہ.buttonId == SCE_پیغام_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } ورنہ اگر (dialog_نتیجہ.buttonId == SCE_پیغام_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_پیغام_Dialog_رکن();
    } ورنہ {
        واپس false;
    }

    gxm_رکن_for_common_dialog();

    اگر (تیاری_اقل_gxm) {
        gxm_اقل_رکن_for_common_dialog();
    }

    واپس true;
#ورنہ
    (خالی)messageboxdata;
    (خالی)buttonID;
    واپس SDL_Unsupported();
#اگر_ختم // SDL_VIDEO_RENDER_VITA_GXM
}

#اگر_ختم // SDL_VIDEO_DRIVER_VITA
