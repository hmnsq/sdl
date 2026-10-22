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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#அந்தர்பாவ "SDL_vitavideo.h"
#அந்தர்பாவ "SDL_vitamessagebox.h"
#அந்தர்பாவ <psp2/message_dialog.h>

#ifdef SDL_VIDEO_RENDER_VITA_GXM
#அந்தர்பாவ "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#endif // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_ShowMessageBox(மாறிலி SDL_MessageBoxData *messageboxdata, முழு *buttonID)
{
#ifdef SDL_VIDEO_RENDER_VITA_GXM
    Sce_செய்தி_Dialog_Param param;
    Sce_செய்தி_Dialog_User_Message_Param செய்தி_Param;
    Sce_செய்தி_Dialog_Buttons_Param buttonParam;
    SceDisplayFrameBuf dispparam;
    எழுத்து message[512];

    Sce_செய்தி_Dialog_Result dialog_result;
    SceCommonDialogErrorCode init_result;
    bool setup_minimal_gxm = false;

    எனில் (messageboxdata->numbuttons > 3) {
        திரும்பு false;
    }

    SDL_zero(param);
    sce_செய்தி_Dialog_Param_Init(&param);
    param.mode = SCE_செய்தி_DIALOG_MODE_USER_செய்தி;

    SDL_zero(செய்தி_Param);
    SDL_snprintf(message, அளவு(message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

    செய்தி_Param.செய்தி = (மாறிலி SceChar8 *)message;
    SDL_zero(buttonParam);

    எனில் (messageboxdata->numbuttons == 3) {
        செய்தி_Param.buttonType = SCE_செய்தி_DIALOG_BUTTON_TYPE_3_BUTTONS;
        செய்தி_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].text;
        buttonParam.msg2 = messageboxdata->buttons[1].text;
        buttonParam.msg3 = messageboxdata->buttons[2].text;
    } இல்லையெனில் எனில் (messageboxdata->numbuttons == 2) {
        செய்தி_Param.buttonType = SCE_செய்தி_DIALOG_BUTTON_TYPE_YESNO;
    } இல்லையெனில் எனில் (messageboxdata->numbuttons == 1) {
        செய்தி_Param.buttonType = SCE_செய்தி_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_செய்தி_Param = &செய்தி_Param;

    dispparam.size = அளவு(dispparam);

    init_result = sce_செய்தி_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    எனில் (init_result == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_minimal_init_for_common_dialog();
        init_result = sce_செய்தி_Dialog_Init(&param);
        setup_minimal_gxm = true;
    }

    gxm_init_for_common_dialog();

    எனில் (init_result >= 0) {
        போது (sce_செய்தி_Dialog_Get_Status() == SCE_COMMON_DIALOG_STATUS_RUNNING) {
            gxm_swap_for_common_dialog();
        }
        SDL_zero(dialog_result);
        sce_செய்தி_Dialog_Get_Result(&dialog_result);

        எனில் (dialog_result.buttonId == SCE_செய்தி_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } இல்லையெனில் எனில் (dialog_result.buttonId == SCE_செய்தி_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } இல்லையெனில் எனில் (dialog_result.buttonId == SCE_செய்தி_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } இல்லையெனில் எனில் (dialog_result.buttonId == SCE_செய்தி_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } இல்லையெனில் எனில் (dialog_result.buttonId == SCE_செய்தி_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } இல்லையெனில் எனில் (dialog_result.buttonId == SCE_செய்தி_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_செய்தி_Dialog_Term();
    } இல்லையெனில் {
        திரும்பு false;
    }

    gxm_term_for_common_dialog();

    எனில் (setup_minimal_gxm) {
        gxm_minimal_term_for_common_dialog();
    }

    திரும்பு true;
#இல்லையெனில்
    (வெறுமை)messageboxdata;
    (வெறுமை)buttonID;
    திரும்பு SDL_Unsupported();
#endif // SDL_VIDEO_RENDER_VITA_GXM
}

#endif // SDL_VIDEO_DRIVER_VITA
