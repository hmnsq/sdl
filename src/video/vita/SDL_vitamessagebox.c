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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VITA

#ضمن "SDL_vitavideo.h"
#ضمن "SDL_vitamessagebox.h"
#ضمن <psp2/message_dialog.h>

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_RENDER_VITA_GXM
#ضمن "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#جيڪڏهن_پورو // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_Show_پيغام_Box(ثابت SDL_پيغام_Box_معلومات *messageboxdata, صحيح *buttonID)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_RENDER_VITA_GXM
    Sce_نياپو_Dialog_Param param;
    Sce_نياپو_Dialog_User_پيغام_Param نياپو_Param;
    Sce_نياپو_Dialog_Buttons_Param buttonParam;
    Sce_Display_چوکٺو_Buf dispparam;
    حرف پيغام[512];

    Sce_نياپو_Dialog_نتيجو dialog_نتيجو;
    Sce_Common_Dialog_Error_ڪوڊ init_نتيجو;
    bool تياري_گهٽتر_gxm = false;

    إذا (messageboxdata->numbuttons > 3) {
        أرجع false;
    }

    SDL_zero(param);
    sce_نياپو_Dialog_Param_Init(&param);
    param.گهڻائي = SCE_نياپو_DIALOG_گهڻائي_USER_نياپو;

    SDL_zero(نياپو_Param);
    SDL_snprintf(پيغام, حجم(پيغام), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->پيغام);

    نياپو_Param.نياپو = (ثابت SceChar8 *)پيغام;
    SDL_zero(buttonParam);

    إذا (messageboxdata->numbuttons == 3) {
        نياپو_Param.buttonType = SCE_نياپو_DIALOG_BUTTON_TYPE_3_BUTTONS;
        نياپو_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].متن;
        buttonParam.msg2 = messageboxdata->buttons[1].متن;
        buttonParam.msg3 = messageboxdata->buttons[2].متن;
    } وإلا إذا (messageboxdata->numbuttons == 2) {
        نياپو_Param.buttonType = SCE_نياپو_DIALOG_BUTTON_TYPE_YESNO;
    } وإلا إذا (messageboxdata->numbuttons == 1) {
        نياپو_Param.buttonType = SCE_نياپو_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_نياپو_Param = &نياپو_Param;

    dispparam.سائيز = حجم(dispparam);

    init_نتيجو = sce_نياپو_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    إذا (init_نتيجو == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_گهٽتر_init_for_common_dialog();
        init_نتيجو = sce_نياپو_Dialog_Init(&param);
        تياري_گهٽتر_gxm = true;
    }

    gxm_init_for_common_dialog();

    إذا (init_نتيجو >= 0) {
        طالما (sce_نياپو_Dialog_Get_حالت() == SCE_COMMON_DIALOG_حالت_RUNNING) {
            gxm_مٽا_سٽا_for_common_dialog();
        }
        SDL_zero(dialog_نتيجو);
        sce_نياپو_Dialog_Get_نتيجو(&dialog_نتيجو);

        إذا (dialog_نتيجو.buttonId == SCE_نياپو_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } وإلا إذا (dialog_نتيجو.buttonId == SCE_نياپو_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } وإلا إذا (dialog_نتيجو.buttonId == SCE_نياپو_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } وإلا إذا (dialog_نتيجو.buttonId == SCE_نياپو_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } وإلا إذا (dialog_نتيجو.buttonId == SCE_نياپو_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } وإلا إذا (dialog_نتيجو.buttonId == SCE_نياپو_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_نياپو_Dialog_رڪن();
    } وإلا {
        أرجع false;
    }

    gxm_رڪن_for_common_dialog();

    إذا (تياري_گهٽتر_gxm) {
        gxm_گهٽتر_رڪن_for_common_dialog();
    }

    أرجع true;
#وإلا
    (فراغ)messageboxdata;
    (فراغ)buttonID;
    أرجع SDL_Unsupported();
#جيڪڏهن_پورو // SDL_VIDEO_RENDER_VITA_GXM
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_VITA
