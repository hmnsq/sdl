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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#അന്തര്ഭാവ "SDL_vitavideo.h"
#അന്തര്ഭാവ "SDL_vitamessagebox.h"
#അന്തര്ഭാവ <psp2/message_dialog.h>

#ifdef SDL_VIDEO_RENDER_VITA_GXM
#അന്തര്ഭാവ "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#endif // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_ShowMessageBox(സ്ഥിരം SDL_MessageBoxData *messageboxdata, പൂർണ്ണസംഖ്യ *buttonID)
{
#ifdef SDL_VIDEO_RENDER_VITA_GXM
    Sce_സന്ദേശം_Dialog_Param param;
    Sce_സന്ദേശം_Dialog_User_Message_Param സന്ദേശം_Param;
    Sce_സന്ദേശം_Dialog_Buttons_Param buttonParam;
    SceDisplayFrameBuf dispparam;
    അക്ഷരം message[512];

    Sce_സന്ദേശം_Dialog_Result dialog_result;
    SceCommonDialogErrorCode init_result;
    bool setup_minimal_gxm = false;

    എങ്കിൽ (messageboxdata->numbuttons > 3) {
        തിരികെ false;
    }

    SDL_zero(param);
    sce_സന്ദേശം_Dialog_Param_Init(&param);
    param.mode = SCE_സന്ദേശം_DIALOG_MODE_USER_സന്ദേശം;

    SDL_zero(സന്ദേശം_Param);
    SDL_snprintf(message, വലുപ്പം(message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

    സന്ദേശം_Param.സന്ദേശം = (സ്ഥിരം SceChar8 *)message;
    SDL_zero(buttonParam);

    എങ്കിൽ (messageboxdata->numbuttons == 3) {
        സന്ദേശം_Param.buttonType = SCE_സന്ദേശം_DIALOG_BUTTON_TYPE_3_BUTTONS;
        സന്ദേശം_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].text;
        buttonParam.msg2 = messageboxdata->buttons[1].text;
        buttonParam.msg3 = messageboxdata->buttons[2].text;
    } അല്ലെങ്കിൽ എങ്കിൽ (messageboxdata->numbuttons == 2) {
        സന്ദേശം_Param.buttonType = SCE_സന്ദേശം_DIALOG_BUTTON_TYPE_YESNO;
    } അല്ലെങ്കിൽ എങ്കിൽ (messageboxdata->numbuttons == 1) {
        സന്ദേശം_Param.buttonType = SCE_സന്ദേശം_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_സന്ദേശം_Param = &സന്ദേശം_Param;

    dispparam.size = വലുപ്പം(dispparam);

    init_result = sce_സന്ദേശം_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    എങ്കിൽ (init_result == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_minimal_init_for_common_dialog();
        init_result = sce_സന്ദേശം_Dialog_Init(&param);
        setup_minimal_gxm = true;
    }

    gxm_init_for_common_dialog();

    എങ്കിൽ (init_result >= 0) {
        ആകുമ്പോൾ (sce_സന്ദേശം_Dialog_Get_Status() == SCE_COMMON_DIALOG_STATUS_RUNNING) {
            gxm_swap_for_common_dialog();
        }
        SDL_zero(dialog_result);
        sce_സന്ദേശം_Dialog_Get_Result(&dialog_result);

        എങ്കിൽ (dialog_result.buttonId == SCE_സന്ദേശം_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } അല്ലെങ്കിൽ എങ്കിൽ (dialog_result.buttonId == SCE_സന്ദേശം_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } അല്ലെങ്കിൽ എങ്കിൽ (dialog_result.buttonId == SCE_സന്ദേശം_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } അല്ലെങ്കിൽ എങ്കിൽ (dialog_result.buttonId == SCE_സന്ദേശം_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } അല്ലെങ്കിൽ എങ്കിൽ (dialog_result.buttonId == SCE_സന്ദേശം_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } അല്ലെങ്കിൽ എങ്കിൽ (dialog_result.buttonId == SCE_സന്ദേശം_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_സന്ദേശം_Dialog_Term();
    } അല്ലെങ്കിൽ {
        തിരികെ false;
    }

    gxm_term_for_common_dialog();

    എങ്കിൽ (setup_minimal_gxm) {
        gxm_minimal_term_for_common_dialog();
    }

    തിരികെ true;
#അല്ലെങ്കിൽ
    (ശൂന്യം)messageboxdata;
    (ശൂന്യം)buttonID;
    തിരികെ SDL_Unsupported();
#endif // SDL_VIDEO_RENDER_VITA_GXM
}

#endif // SDL_VIDEO_DRIVER_VITA
