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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#include "SDL_vitavideo.h"
#include "SDL_vitamessagebox.h"
#include <psp2/message_dialog.h>

#ifdef SDL_VIDEO_RENDER_VITA_GXM
#include "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#endif // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_ShowMessageBox(const SDL_MessageBoxData *messageboxdata, int *buttonID)
{
#ifdef SDL_VIDEO_RENDER_VITA_GXM
    Sce_मेनसाहे_Dialog_Param param;
    Sce_मेनसाहे_Dialog_User_Message_Param मेनसाहे_Param;
    Sce_मेनसाहे_Dialog_Buttons_Param buttonParam;
    SceDisplayFrameBuf dispparam;
    char message[512];

    Sce_मेनसाहे_Dialog_Result dialog_result;
    SceCommonDialogErrorCode init_result;
    bool setup_minimal_gxm = false;

    if (messageboxdata->numbuttons > 3) {
        return false;
    }

    SDL_zero(param);
    sce_मेनसाहे_Dialog_Param_Init(&param);
    param.mode = SCE_मेनसाहे_DIALOG_MODE_USER_मेनसाहे;

    SDL_zero(मेनसाहे_Param);
    SDL_snprintf(message, sizeof(message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

    मेनसाहे_Param.मेनसाहे = (const SceChar8 *)message;
    SDL_zero(buttonParam);

    if (messageboxdata->numbuttons == 3) {
        मेनसाहे_Param.buttonType = SCE_मेनसाहे_DIALOG_BUTTON_TYPE_3_BUTTONS;
        मेनसाहे_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].text;
        buttonParam.msg2 = messageboxdata->buttons[1].text;
        buttonParam.msg3 = messageboxdata->buttons[2].text;
    } else if (messageboxdata->numbuttons == 2) {
        मेनसाहे_Param.buttonType = SCE_मेनसाहे_DIALOG_BUTTON_TYPE_YESNO;
    } else if (messageboxdata->numbuttons == 1) {
        मेनसाहे_Param.buttonType = SCE_मेनसाहे_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_मेनसाहे_Param = &मेनसाहे_Param;

    dispparam.size = sizeof(dispparam);

    init_result = sce_मेनसाहे_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    if (init_result == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_minimal_init_for_common_dialog();
        init_result = sce_मेनसाहे_Dialog_Init(&param);
        setup_minimal_gxm = true;
    }

    gxm_init_for_common_dialog();

    if (init_result >= 0) {
        while (sce_मेनसाहे_Dialog_Get_Status() == SCE_COMMON_DIALOG_STATUS_RUNNING) {
            gxm_swap_for_common_dialog();
        }
        SDL_zero(dialog_result);
        sce_मेनसाहे_Dialog_Get_Result(&dialog_result);

        if (dialog_result.buttonId == SCE_मेनसाहे_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } else if (dialog_result.buttonId == SCE_मेनसाहे_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } else if (dialog_result.buttonId == SCE_मेनसाहे_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } else if (dialog_result.buttonId == SCE_मेनसाहे_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } else if (dialog_result.buttonId == SCE_मेनसाहे_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } else if (dialog_result.buttonId == SCE_मेनसाहे_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_मेनसाहे_Dialog_Term();
    } else {
        return false;
    }

    gxm_term_for_common_dialog();

    if (setup_minimal_gxm) {
        gxm_minimal_term_for_common_dialog();
    }

    return true;
#else
    (void)messageboxdata;
    (void)buttonID;
    return SDL_Unsupported();
#endif // SDL_VIDEO_RENDER_VITA_GXM
}

#endif // SDL_VIDEO_DRIVER_VITA
