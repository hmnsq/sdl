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

#که_تعریف_شوی SDL_VIDEO_DRIVER_VITA

#ضمن "SDL_vitavideo.h"
#ضمن "SDL_vitamessagebox.h"
#ضمن <psp2/message_dialog.h>

#که_تعریف_شوی SDL_VIDEO_RENDER_VITA_GXM
#ضمن "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#د_که_پای // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_Show_پیغام_Box(ثابت SDL_پیغام_Box_معلومات *messageboxdata, صحيح *buttonID)
{
#که_تعریف_شوی SDL_VIDEO_RENDER_VITA_GXM
    Sce_پیغام_Dialog_Param param;
    Sce_پیغام_Dialog_User_پیغام_Param پیغام_Param;
    Sce_پیغام_Dialog_Buttons_Param buttonParam;
    Sce_Display_چوکاټ_Buf dispparam;
    حرف پیغام[512];

    Sce_پیغام_Dialog_پایله dialog_پایله;
    Sce_Common_Dialog_Error_کوډ init_پایله;
    bool تیاری_اصغري_gxm = false;

    إذا (messageboxdata->numbuttons > 3) {
        أرجع false;
    }

    SDL_zero(param);
    sce_پیغام_Dialog_Param_Init(&param);
    param.ډېرپېښ = SCE_پیغام_DIALOG_ډېرپېښ_USER_پیغام;

    SDL_zero(پیغام_Param);
    SDL_snprintf(پیغام, حجم(پیغام), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->پیغام);

    پیغام_Param.پیغام_2 = (ثابت SceChar8 *)پیغام;
    SDL_zero(buttonParam);

    إذا (messageboxdata->numbuttons == 3) {
        پیغام_Param.buttonType = SCE_پیغام_DIALOG_BUTTON_TYPE_3_BUTTONS;
        پیغام_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].متن;
        buttonParam.msg2 = messageboxdata->buttons[1].متن;
        buttonParam.msg3 = messageboxdata->buttons[2].متن;
    } وإلا إذا (messageboxdata->numbuttons == 2) {
        پیغام_Param.buttonType = SCE_پیغام_DIALOG_BUTTON_TYPE_YESNO;
    } وإلا إذا (messageboxdata->numbuttons == 1) {
        پیغام_Param.buttonType = SCE_پیغام_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_پیغام_Param = &پیغام_Param;

    dispparam.اندازه = حجم(dispparam);

    init_پایله = sce_پیغام_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    إذا (init_پایله == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_اصغري_init_for_common_dialog();
        init_پایله = sce_پیغام_Dialog_Init(&param);
        تیاری_اصغري_gxm = true;
    }

    gxm_init_for_common_dialog();

    إذا (init_پایله >= 0) {
        طالما (sce_پیغام_Dialog_Get_حالت() == SCE_COMMON_DIALOG_حالت_RUNNING) {
            gxm_بدلون_for_common_dialog();
        }
        SDL_zero(dialog_پایله);
        sce_پیغام_Dialog_Get_پایله(&dialog_پایله);

        إذا (dialog_پایله.buttonId == SCE_پیغام_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } وإلا إذا (dialog_پایله.buttonId == SCE_پیغام_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } وإلا إذا (dialog_پایله.buttonId == SCE_پیغام_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } وإلا إذا (dialog_پایله.buttonId == SCE_پیغام_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } وإلا إذا (dialog_پایله.buttonId == SCE_پیغام_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } وإلا إذا (dialog_پایله.buttonId == SCE_پیغام_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_پیغام_Dialog_غړی();
    } وإلا {
        أرجع false;
    }

    gxm_غړی_for_common_dialog();

    إذا (تیاری_اصغري_gxm) {
        gxm_اصغري_غړی_for_common_dialog();
    }

    أرجع true;
#وإلا
    (فراغ)messageboxdata;
    (فراغ)buttonID;
    أرجع SDL_Unsupported();
#د_که_پای // SDL_VIDEO_RENDER_VITA_GXM
}

#د_که_پای // SDL_VIDEO_DRIVER_VITA
