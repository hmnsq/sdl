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
#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_VITA

#ضمن "SDL_vitavideo.h"
#ضمن "SDL_vitamessagebox.h"
#ضمن <psp2/message_dialog.h>

#اگر_تعریف_شده SDL_VIDEO_RENDER_VITA_GXM
#ضمن "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#پایان_اگر // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_Show_پیام_Box(ثابت SDL_پیام_Box_داده *messageboxdata, صحيح *buttonID)
{
#اگر_تعریف_شده SDL_VIDEO_RENDER_VITA_GXM
    Sce_پیام_Dialog_Param param;
    Sce_پیام_Dialog_User_پیام_Param پیام_Param;
    Sce_پیام_Dialog_Buttons_Param buttonParam;
    Sce_Display_قاب_Buf dispparam;
    حرف پیام[512];

    Sce_پیام_Dialog_نتیجه dialog_نتیجه;
    Sce_Common_Dialog_Error_کد init_نتیجه;
    bool راهاندازی_کمینه_gxm = false;

    إذا (messageboxdata->numbuttons > 3) {
        أرجع false;
    }

    SDL_zero(param);
    sce_پیام_Dialog_Param_Init(&param);
    param.نما = SCE_پیام_DIALOG_نما_USER_پیام;

    SDL_zero(پیام_Param);
    SDL_snprintf(پیام, حجم(پیام), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->پیام);

    پیام_Param.پیام_2 = (ثابت SceChar8 *)پیام;
    SDL_zero(buttonParam);

    إذا (messageboxdata->numbuttons == 3) {
        پیام_Param.buttonType = SCE_پیام_DIALOG_BUTTON_TYPE_3_BUTTONS;
        پیام_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].متن;
        buttonParam.msg2 = messageboxdata->buttons[1].متن;
        buttonParam.msg3 = messageboxdata->buttons[2].متن;
    } وإلا إذا (messageboxdata->numbuttons == 2) {
        پیام_Param.buttonType = SCE_پیام_DIALOG_BUTTON_TYPE_YESNO;
    } وإلا إذا (messageboxdata->numbuttons == 1) {
        پیام_Param.buttonType = SCE_پیام_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_پیام_Param = &پیام_Param;

    dispparam.اندازه = حجم(dispparam);

    init_نتیجه = sce_پیام_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    إذا (init_نتیجه == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_کمینه_init_for_common_dialog();
        init_نتیجه = sce_پیام_Dialog_Init(&param);
        راهاندازی_کمینه_gxm = true;
    }

    gxm_init_for_common_dialog();

    إذا (init_نتیجه >= 0) {
        طالما (sce_پیام_Dialog_Get_وضعیت() == SCE_COMMON_DIALOG_وضعیت_RUNNING) {
            gxm_جابجا_for_common_dialog();
        }
        SDL_zero(dialog_نتیجه);
        sce_پیام_Dialog_Get_نتیجه(&dialog_نتیجه);

        إذا (dialog_نتیجه.buttonId == SCE_پیام_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } وإلا إذا (dialog_نتیجه.buttonId == SCE_پیام_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } وإلا إذا (dialog_نتیجه.buttonId == SCE_پیام_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } وإلا إذا (dialog_نتیجه.buttonId == SCE_پیام_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } وإلا إذا (dialog_نتیجه.buttonId == SCE_پیام_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } وإلا إذا (dialog_نتیجه.buttonId == SCE_پیام_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_پیام_Dialog_جمله();
    } وإلا {
        أرجع false;
    }

    gxm_جمله_for_common_dialog();

    إذا (راهاندازی_کمینه_gxm) {
        gxm_کمینه_جمله_for_common_dialog();
    }

    أرجع true;
#وإلا
    (فراغ)messageboxdata;
    (فراغ)buttonID;
    أرجع SDL_Unsupported();
#پایان_اگر // SDL_VIDEO_RENDER_VITA_GXM
}

#پایان_اگر // SDL_VIDEO_DRIVER_VITA
