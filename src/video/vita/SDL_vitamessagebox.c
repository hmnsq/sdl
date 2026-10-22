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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VITA

#अन्तर्भाव "SDL_vitavideo.h"
#अन्तर्भाव "SDL_vitamessagebox.h"
#अन्तर्भाव <psp2/message_dialog.h>

#यदि_परिभाषितम् SDL_VIDEO_RENDER_VITA_GXM
#अन्तर्भाव "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#यदि_अन्तः // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_Show_सन्देशः_Box(ध्रुव SDL_सन्देशः_Box_दत्त *messageboxdata, पूर्णाङ्क *buttonID)
{
#यदि_परिभाषितम् SDL_VIDEO_RENDER_VITA_GXM
    Sce_सन्देशः_Dialog_Param param;
    Sce_सन्देशः_Dialog_User_सन्देशः_Param सन्देशः_Param;
    Sce_सन्देशः_Dialog_Buttons_Param buttonParam;
    SceDisplayFrameBuf dispparam;
    वर्ण सन्देशः[512];

    Sce_सन्देशः_Dialog_परिणाम dialog_परिणाम;
    Sce_Common_Dialog_Error_संहिता init_परिणाम;
    bool सज्जता_अल्पिष्ठम्_gxm = false;

    यदि (messageboxdata->numbuttons > 3) {
        प्रत्यागम false;
    }

    SDL_zero(param);
    sce_सन्देशः_Dialog_Param_Init(&param);
    param.बहुलकम् = SCE_सन्देशः_DIALOG_बहुलकम्_USER_सन्देशः;

    SDL_zero(सन्देशः_Param);
    SDL_snprintf(सन्देशः, परिमाण(सन्देशः), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->सन्देशः);

    सन्देशः_Param.सन्देशः_2 = (ध्रुव SceChar8 *)सन्देशः;
    SDL_zero(buttonParam);

    यदि (messageboxdata->numbuttons == 3) {
        सन्देशः_Param.buttonType = SCE_सन्देशः_DIALOG_BUTTON_TYPE_3_BUTTONS;
        सन्देशः_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].text;
        buttonParam.msg2 = messageboxdata->buttons[1].text;
        buttonParam.msg3 = messageboxdata->buttons[2].text;
    } अन्यथा यदि (messageboxdata->numbuttons == 2) {
        सन्देशः_Param.buttonType = SCE_सन्देशः_DIALOG_BUTTON_TYPE_YESNO;
    } अन्यथा यदि (messageboxdata->numbuttons == 1) {
        सन्देशः_Param.buttonType = SCE_सन्देशः_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_सन्देशः_Param = &सन्देशः_Param;

    dispparam.आकार = परिमाण(dispparam);

    init_परिणाम = sce_सन्देशः_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    यदि (init_परिणाम == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_अल्पिष्ठम्_init_for_common_dialog();
        init_परिणाम = sce_सन्देशः_Dialog_Init(&param);
        सज्जता_अल्पिष्ठम्_gxm = true;
    }

    gxm_init_for_common_dialog();

    यदि (init_परिणाम >= 0) {
        यावत् (sce_सन्देशः_Dialog_Get_स्थितिः() == SCE_COMMON_DIALOG_स्थितिः_RUNNING) {
            gxm_swap_for_common_dialog();
        }
        SDL_zero(dialog_परिणाम);
        sce_सन्देशः_Dialog_Get_परिणाम(&dialog_परिणाम);

        यदि (dialog_परिणाम.buttonId == SCE_सन्देशः_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } अन्यथा यदि (dialog_परिणाम.buttonId == SCE_सन्देशः_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } अन्यथा यदि (dialog_परिणाम.buttonId == SCE_सन्देशः_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } अन्यथा यदि (dialog_परिणाम.buttonId == SCE_सन्देशः_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } अन्यथा यदि (dialog_परिणाम.buttonId == SCE_सन्देशः_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } अन्यथा यदि (dialog_परिणाम.buttonId == SCE_सन्देशः_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_सन्देशः_Dialog_पदांशः();
    } अन्यथा {
        प्रत्यागम false;
    }

    gxm_पदांशः_for_common_dialog();

    यदि (सज्जता_अल्पिष्ठम्_gxm) {
        gxm_अल्पिष्ठम्_पदांशः_for_common_dialog();
    }

    प्रत्यागम true;
#अन्यथा
    (शून्य)messageboxdata;
    (शून्य)buttonID;
    प्रत्यागम SDL_Unsupported();
#यदि_अन्तः // SDL_VIDEO_RENDER_VITA_GXM
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_VITA
