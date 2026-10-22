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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#અન્તર્ભાવ "SDL_vitavideo.h"
#અન્તર્ભાવ "SDL_vitamessagebox.h"
#અન્તર્ભાવ <psp2/message_dialog.h>

#ifdef SDL_VIDEO_RENDER_VITA_GXM
#અન્તર્ભાવ "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#endif // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_ShowMessageBox(અચલ SDL_MessageBoxData *messageboxdata, પૂર્ણાંક *buttonID)
{
#ifdef SDL_VIDEO_RENDER_VITA_GXM
    Sce_સંદેશ_Dialog_Param param;
    Sce_સંદેશ_Dialog_User_Message_Param સંદેશ_Param;
    Sce_સંદેશ_Dialog_Buttons_Param buttonParam;
    SceDisplayFrameBuf dispparam;
    અક્ષર message[512];

    Sce_સંદેશ_Dialog_Result dialog_result;
    SceCommonDialogErrorCode init_result;
    bool setup_minimal_gxm = false;

    જો (messageboxdata->numbuttons > 3) {
        પાછા false;
    }

    SDL_zero(param);
    sce_સંદેશ_Dialog_Param_Init(&param);
    param.mode = SCE_સંદેશ_DIALOG_MODE_USER_સંદેશ;

    SDL_zero(સંદેશ_Param);
    SDL_snprintf(message, કદ(message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

    સંદેશ_Param.સંદેશ = (અચલ SceChar8 *)message;
    SDL_zero(buttonParam);

    જો (messageboxdata->numbuttons == 3) {
        સંદેશ_Param.buttonType = SCE_સંદેશ_DIALOG_BUTTON_TYPE_3_BUTTONS;
        સંદેશ_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].text;
        buttonParam.msg2 = messageboxdata->buttons[1].text;
        buttonParam.msg3 = messageboxdata->buttons[2].text;
    } નહીંતર જો (messageboxdata->numbuttons == 2) {
        સંદેશ_Param.buttonType = SCE_સંદેશ_DIALOG_BUTTON_TYPE_YESNO;
    } નહીંતર જો (messageboxdata->numbuttons == 1) {
        સંદેશ_Param.buttonType = SCE_સંદેશ_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_સંદેશ_Param = &સંદેશ_Param;

    dispparam.size = કદ(dispparam);

    init_result = sce_સંદેશ_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    જો (init_result == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_minimal_init_for_common_dialog();
        init_result = sce_સંદેશ_Dialog_Init(&param);
        setup_minimal_gxm = true;
    }

    gxm_init_for_common_dialog();

    જો (init_result >= 0) {
        જ્યારે (sce_સંદેશ_Dialog_Get_Status() == SCE_COMMON_DIALOG_STATUS_RUNNING) {
            gxm_swap_for_common_dialog();
        }
        SDL_zero(dialog_result);
        sce_સંદેશ_Dialog_Get_Result(&dialog_result);

        જો (dialog_result.buttonId == SCE_સંદેશ_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } નહીંતર જો (dialog_result.buttonId == SCE_સંદેશ_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } નહીંતર જો (dialog_result.buttonId == SCE_સંદેશ_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } નહીંતર જો (dialog_result.buttonId == SCE_સંદેશ_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } નહીંતર જો (dialog_result.buttonId == SCE_સંદેશ_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } નહીંતર જો (dialog_result.buttonId == SCE_સંદેશ_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_સંદેશ_Dialog_Term();
    } નહીંતર {
        પાછા false;
    }

    gxm_term_for_common_dialog();

    જો (setup_minimal_gxm) {
        gxm_minimal_term_for_common_dialog();
    }

    પાછા true;
#નહીંતર
    (શૂન્ય)messageboxdata;
    (શૂન્ય)buttonID;
    પાછા SDL_Unsupported();
#endif // SDL_VIDEO_RENDER_VITA_GXM
}

#endif // SDL_VIDEO_DRIVER_VITA
