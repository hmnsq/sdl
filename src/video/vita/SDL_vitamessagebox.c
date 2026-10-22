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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_VITA

#समावेश "SDL_vitavideo.h"
#समावेश "SDL_vitamessagebox.h"
#समावेश <psp2/message_dialog.h>

#अगर_घोषित SDL_VIDEO_RENDER_VITA_GXM
#समावेश "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#पूर्ण_अगर // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_ShowMessageBox(स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonID)
{
#अगर_घोषित SDL_VIDEO_RENDER_VITA_GXM
    Sce_संदेश_Dialog_Param param;
    Sce_संदेश_Dialog_User_Message_Param संदेश_Param;
    Sce_संदेश_Dialog_Buttons_Param buttonParam;
    SceDisplayFrameBuf dispparam;
    अक्षर message[512];

    Sce_संदेश_Dialog_परिणाम dialog_परिणाम;
    SceCommonDialogErrorCode init_परिणाम;
    bool setup_minimal_gxm = false;

    अगर (messageboxdata->numbuttons > 3) {
        वापस false;
    }

    SDL_zero(param);
    sce_संदेश_Dialog_Param_Init(&param);
    param.mode = SCE_संदेश_DIALOG_MODE_USER_संदेश;

    SDL_zero(संदेश_Param);
    SDL_snprintf(message, माप(message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

    संदेश_Param.संदेश = (स्थिर SceChar8 *)message;
    SDL_zero(buttonParam);

    अगर (messageboxdata->numbuttons == 3) {
        संदेश_Param.buttonType = SCE_संदेश_DIALOG_BUTTON_TYPE_3_BUTTONS;
        संदेश_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].text;
        buttonParam.msg2 = messageboxdata->buttons[1].text;
        buttonParam.msg3 = messageboxdata->buttons[2].text;
    } अन्यथा अगर (messageboxdata->numbuttons == 2) {
        संदेश_Param.buttonType = SCE_संदेश_DIALOG_BUTTON_TYPE_YESNO;
    } अन्यथा अगर (messageboxdata->numbuttons == 1) {
        संदेश_Param.buttonType = SCE_संदेश_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_संदेश_Param = &संदेश_Param;

    dispparam.आकार = माप(dispparam);

    init_परिणाम = sce_संदेश_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    अगर (init_परिणाम == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_minimal_init_for_common_dialog();
        init_परिणाम = sce_संदेश_Dialog_Init(&param);
        setup_minimal_gxm = true;
    }

    gxm_init_for_common_dialog();

    अगर (init_परिणाम >= 0) {
        जबतक (sce_संदेश_Dialog_Get_Status() == SCE_COMMON_DIALOG_STATUS_RUNNING) {
            gxm_swap_for_common_dialog();
        }
        SDL_zero(dialog_परिणाम);
        sce_संदेश_Dialog_Get_परिणाम(&dialog_परिणाम);

        अगर (dialog_परिणाम.buttonId == SCE_संदेश_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } अन्यथा अगर (dialog_परिणाम.buttonId == SCE_संदेश_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } अन्यथा अगर (dialog_परिणाम.buttonId == SCE_संदेश_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } अन्यथा अगर (dialog_परिणाम.buttonId == SCE_संदेश_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } अन्यथा अगर (dialog_परिणाम.buttonId == SCE_संदेश_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } अन्यथा अगर (dialog_परिणाम.buttonId == SCE_संदेश_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_संदेश_Dialog_Term();
    } अन्यथा {
        वापस false;
    }

    gxm_term_for_common_dialog();

    अगर (setup_minimal_gxm) {
        gxm_minimal_term_for_common_dialog();
    }

    वापस true;
#अन्यथा
    (व्योम)messageboxdata;
    (व्योम)buttonID;
    वापस SDL_Unsupported();
#पूर्ण_अगर // SDL_VIDEO_RENDER_VITA_GXM
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_VITA
