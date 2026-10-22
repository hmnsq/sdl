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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VITA

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitavideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitamessagebox.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/message_dialog.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_RENDER_VITA_GXM
#ਅਨ੍ਤਰ੍ਭਾਵ "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#ਜੇ_ਅੰਤ // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_Show_ਸੁਨੇਹਾ_Box(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_RENDER_VITA_GXM
    Sce_ਸੁਨੇਹਾ_Dialog_Param param;
    Sce_ਸੁਨੇਹਾ_Dialog_User_ਸੁਨੇਹਾ_Param ਸੁਨੇਹਾ_Param;
    Sce_ਸੁਨੇਹਾ_Dialog_Buttons_Param buttonParam;
    Sce_Display_ਚੌਖਟਾ_Buf dispparam;
    ਅੱਖਰ ਸੁਨੇਹਾ[512];

    Sce_ਸੁਨੇਹਾ_Dialog_ਨਤੀਜਾ dialog_ਨਤੀਜਾ;
    Sce_Common_Dialog_Error_ਕੋਡ init_ਨਤੀਜਾ;
    bool ਤਿਆਰੀ_ਨਿਊਨਤਮ_gxm = false;

    ਜੇ (messageboxdata->numbuttons > 3) {
        ਵਾਪਸ false;
    }

    SDL_zero(param);
    sce_ਸੁਨੇਹਾ_Dialog_Param_Init(&param);
    param.ਬਹੁਲਕ = SCE_ਸੁਨੇਹਾ_DIALOG_ਬਹੁਲਕ_USER_ਸੁਨੇਹਾ;

    SDL_zero(ਸੁਨੇਹਾ_Param);
    SDL_snprintf(ਸੁਨੇਹਾ, ਆਕਾਰ(ਸੁਨੇਹਾ), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->ਸੁਨੇਹਾ);

    ਸੁਨੇਹਾ_Param.ਸੁਨੇਹਾ_2 = (ਅਚਲ SceChar8 *)ਸੁਨੇਹਾ;
    SDL_zero(buttonParam);

    ਜੇ (messageboxdata->numbuttons == 3) {
        ਸੁਨੇਹਾ_Param.buttonType = SCE_ਸੁਨੇਹਾ_DIALOG_BUTTON_TYPE_3_BUTTONS;
        ਸੁਨੇਹਾ_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].ਪਾਠ;
        buttonParam.msg2 = messageboxdata->buttons[1].ਪਾਠ;
        buttonParam.msg3 = messageboxdata->buttons[2].ਪਾਠ;
    } ਨਹੀਂਤਾਂ ਜੇ (messageboxdata->numbuttons == 2) {
        ਸੁਨੇਹਾ_Param.buttonType = SCE_ਸੁਨੇਹਾ_DIALOG_BUTTON_TYPE_YESNO;
    } ਨਹੀਂਤਾਂ ਜੇ (messageboxdata->numbuttons == 1) {
        ਸੁਨੇਹਾ_Param.buttonType = SCE_ਸੁਨੇਹਾ_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_ਸੁਨੇਹਾ_Param = &ਸੁਨੇਹਾ_Param;

    dispparam.ਮਾਪ = ਆਕਾਰ(dispparam);

    init_ਨਤੀਜਾ = sce_ਸੁਨੇਹਾ_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    ਜੇ (init_ਨਤੀਜਾ == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_ਨਿਊਨਤਮ_init_for_common_dialog();
        init_ਨਤੀਜਾ = sce_ਸੁਨੇਹਾ_Dialog_Init(&param);
        ਤਿਆਰੀ_ਨਿਊਨਤਮ_gxm = true;
    }

    gxm_init_for_common_dialog();

    ਜੇ (init_ਨਤੀਜਾ >= 0) {
        ਜਦੋਂ (sce_ਸੁਨੇਹਾ_Dialog_Get_ਸਥਿਤੀ() == SCE_COMMON_DIALOG_ਸਥਿਤੀ_RUNNING) {
            gxm_ਅਦਲਾ_ਬਦਲੀ_for_common_dialog();
        }
        SDL_zero(dialog_ਨਤੀਜਾ);
        sce_ਸੁਨੇਹਾ_Dialog_Get_ਨਤੀਜਾ(&dialog_ਨਤੀਜਾ);

        ਜੇ (dialog_ਨਤੀਜਾ.buttonId == SCE_ਸੁਨੇਹਾ_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } ਨਹੀਂਤਾਂ ਜੇ (dialog_ਨਤੀਜਾ.buttonId == SCE_ਸੁਨੇਹਾ_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } ਨਹੀਂਤਾਂ ਜੇ (dialog_ਨਤੀਜਾ.buttonId == SCE_ਸੁਨੇਹਾ_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } ਨਹੀਂਤਾਂ ਜੇ (dialog_ਨਤੀਜਾ.buttonId == SCE_ਸੁਨੇਹਾ_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } ਨਹੀਂਤਾਂ ਜੇ (dialog_ਨਤੀਜਾ.buttonId == SCE_ਸੁਨੇਹਾ_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } ਨਹੀਂਤਾਂ ਜੇ (dialog_ਨਤੀਜਾ.buttonId == SCE_ਸੁਨੇਹਾ_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_ਸੁਨੇਹਾ_Dialog_ਪਦ();
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ false;
    }

    gxm_ਪਦ_for_common_dialog();

    ਜੇ (ਤਿਆਰੀ_ਨਿਊਨਤਮ_gxm) {
        gxm_ਨਿਊਨਤਮ_ਪਦ_for_common_dialog();
    }

    ਵਾਪਸ true;
#ਨਹੀਂਤਾਂ
    (ਖਾਲੀ)messageboxdata;
    (ਖਾਲੀ)buttonID;
    ਵਾਪਸ SDL_Unsupported();
#ਜੇ_ਅੰਤ // SDL_VIDEO_RENDER_VITA_GXM
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_VITA
