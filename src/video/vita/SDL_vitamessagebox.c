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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VITA

#అన్తర్భావ "SDL_vitavideo.h"
#అన్తర్భావ "SDL_vitamessagebox.h"
#అన్తర్భావ <psp2/message_dialog.h>

#నిర్వచితమైతే SDL_VIDEO_RENDER_VITA_GXM
#అన్తర్భావ "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#అయితే_ముగింపు // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_Show_సందేశం_Box(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonID)
{
#నిర్వచితమైతే SDL_VIDEO_RENDER_VITA_GXM
    Sce_సందేశం_Dialog_Param param;
    Sce_సందేశం_Dialog_User_సందేశం_Param సందేశం_Param;
    Sce_సందేశం_Dialog_Buttons_Param buttonParam;
    Sce_Display_చట్రం_Buf dispparam;
    అక్షరం సందేశం[512];

    Sce_సందేశం_Dialog_ఫలితం dialog_ఫలితం;
    Sce_Common_Dialog_Error_సంకేతం init_ఫలితం;
    bool అమరిక_కనీస_gxm = false;

    ఒకవేళ (messageboxdata->numbuttons > 3) {
        తిరిగి false;
    }

    SDL_zero(param);
    sce_సందేశం_Dialog_Param_Init(&param);
    param.బహుళకం = SCE_సందేశం_DIALOG_బహుళకం_USER_సందేశం;

    SDL_zero(సందేశం_Param);
    SDL_snprintf(సందేశం, పరిమాణం(సందేశం), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->సందేశం);

    సందేశం_Param.సందేశం_2 = (స్థిరరాశి SceChar8 *)సందేశం;
    SDL_zero(buttonParam);

    ఒకవేళ (messageboxdata->numbuttons == 3) {
        సందేశం_Param.buttonType = SCE_సందేశం_DIALOG_BUTTON_TYPE_3_BUTTONS;
        సందేశం_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].పాఠ్యం;
        buttonParam.msg2 = messageboxdata->buttons[1].పాఠ్యం;
        buttonParam.msg3 = messageboxdata->buttons[2].పాఠ్యం;
    } లేకపోతే ఒకవేళ (messageboxdata->numbuttons == 2) {
        సందేశం_Param.buttonType = SCE_సందేశం_DIALOG_BUTTON_TYPE_YESNO;
    } లేకపోతే ఒకవేళ (messageboxdata->numbuttons == 1) {
        సందేశం_Param.buttonType = SCE_సందేశం_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_సందేశం_Param = &సందేశం_Param;

    dispparam.కొలత = పరిమాణం(dispparam);

    init_ఫలితం = sce_సందేశం_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    ఒకవేళ (init_ఫలితం == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_కనీస_init_for_common_dialog();
        init_ఫలితం = sce_సందేశం_Dialog_Init(&param);
        అమరిక_కనీస_gxm = true;
    }

    gxm_init_for_common_dialog();

    ఒకవేళ (init_ఫలితం >= 0) {
        అయితే (sce_సందేశం_Dialog_Get_స్థితి() == SCE_COMMON_DIALOG_స్థితి_RUNNING) {
            gxm_మార్పిడి_for_common_dialog();
        }
        SDL_zero(dialog_ఫలితం);
        sce_సందేశం_Dialog_Get_ఫలితం(&dialog_ఫలితం);

        ఒకవేళ (dialog_ఫలితం.buttonId == SCE_సందేశం_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } లేకపోతే ఒకవేళ (dialog_ఫలితం.buttonId == SCE_సందేశం_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } లేకపోతే ఒకవేళ (dialog_ఫలితం.buttonId == SCE_సందేశం_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } లేకపోతే ఒకవేళ (dialog_ఫలితం.buttonId == SCE_సందేశం_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } లేకపోతే ఒకవేళ (dialog_ఫలితం.buttonId == SCE_సందేశం_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } లేకపోతే ఒకవేళ (dialog_ఫలితం.buttonId == SCE_సందేశం_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_సందేశం_Dialog_పదం();
    } లేకపోతే {
        తిరిగి false;
    }

    gxm_పదం_for_common_dialog();

    ఒకవేళ (అమరిక_కనీస_gxm) {
        gxm_కనీస_పదం_for_common_dialog();
    }

    తిరిగి true;
#లేకపోతే
    (శూన్య)messageboxdata;
    (శూన్య)buttonID;
    తిరిగి SDL_Unsupported();
#అయితే_ముగింపు // SDL_VIDEO_RENDER_VITA_GXM
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VITA
