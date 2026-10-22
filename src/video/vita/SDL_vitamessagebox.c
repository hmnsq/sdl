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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VITA

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_vitamessagebox.h"
#ಅನ್ತರ್ಭಾವ <psp2/message_dialog.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_RENDER_VITA_GXM
#ಅನ್ತರ್ಭಾವ "../../render/vitagxm/SDL_render_vita_gxm_tools.h"
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_RENDER_VITA_GXM

bool VITA_Show_ಸಂದೇಶ_Box(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonID)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_RENDER_VITA_GXM
    Sce_ಸಂದೇಶ_Dialog_Param param;
    Sce_ಸಂದೇಶ_Dialog_User_ಸಂದೇಶ_Param ಸಂದೇಶ_Param;
    Sce_ಸಂದೇಶ_Dialog_Buttons_Param buttonParam;
    Sce_Display_ಚೌಕಟ್ಟು_Buf dispparam;
    ಅಕ್ಷರ ಸಂದೇಶ[512];

    Sce_ಸಂದೇಶ_Dialog_ಫಲಿತಾಂಶ dialog_ಫಲಿತಾಂಶ;
    Sce_Common_Dialog_Error_ಸಂಕೇತ init_ಫಲಿತಾಂಶ;
    bool ಸಿದ್ಧತೆ_ಕನಿಷ್ಠತಮ_gxm = false;

    ಆದರೆ (messageboxdata->numbuttons > 3) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_zero(param);
    sce_ಸಂದೇಶ_Dialog_Param_Init(&param);
    param.ಬಹುಲಕ = SCE_ಸಂದೇಶ_DIALOG_ಬಹುಲಕ_USER_ಸಂದೇಶ;

    SDL_zero(ಸಂದೇಶ_Param);
    SDL_snprintf(ಸಂದೇಶ, ಗಾತ್ರ(ಸಂದೇಶ), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->ಸಂದೇಶ);

    ಸಂದೇಶ_Param.ಸಂದೇಶ_2 = (ಸ್ಥಿರಾಂಕ SceChar8 *)ಸಂದೇಶ;
    SDL_zero(buttonParam);

    ಆದರೆ (messageboxdata->numbuttons == 3) {
        ಸಂದೇಶ_Param.buttonType = SCE_ಸಂದೇಶ_DIALOG_BUTTON_TYPE_3_BUTTONS;
        ಸಂದೇಶ_Param.buttonParam = &buttonParam;
        buttonParam.msg1 = messageboxdata->buttons[0].ಪಠ್ಯ;
        buttonParam.msg2 = messageboxdata->buttons[1].ಪಠ್ಯ;
        buttonParam.msg3 = messageboxdata->buttons[2].ಪಠ್ಯ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (messageboxdata->numbuttons == 2) {
        ಸಂದೇಶ_Param.buttonType = SCE_ಸಂದೇಶ_DIALOG_BUTTON_TYPE_YESNO;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (messageboxdata->numbuttons == 1) {
        ಸಂದೇಶ_Param.buttonType = SCE_ಸಂದೇಶ_DIALOG_BUTTON_TYPE_OK;
    }
    param.user_ಸಂದೇಶ_Param = &ಸಂದೇಶ_Param;

    dispparam.ಗಾತ್ರ_2 = ಗಾತ್ರ(dispparam);

    init_ಫಲಿತಾಂಶ = sce_ಸಂದೇಶ_Dialog_Init(&param);

    // Setup display if it hasn't been initialized before
    ಆದರೆ (init_ಫಲಿತಾಂಶ == SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED) {
        gxm_ಕನಿಷ್ಠತಮ_init_for_common_dialog();
        init_ಫಲಿತಾಂಶ = sce_ಸಂದೇಶ_Dialog_Init(&param);
        ಸಿದ್ಧತೆ_ಕನಿಷ್ಠತಮ_gxm = true;
    }

    gxm_init_for_common_dialog();

    ಆದರೆ (init_ಫಲಿತಾಂಶ >= 0) {
        ಆಗ (sce_ಸಂದೇಶ_Dialog_Get_ಸ್ಥಿತಿ() == SCE_COMMON_DIALOG_ಸ್ಥಿತಿ_RUNNING) {
            gxm_ಅದಲುಬದಲು_for_common_dialog();
        }
        SDL_zero(dialog_ಫಲಿತಾಂಶ);
        sce_ಸಂದೇಶ_Dialog_Get_ಫಲಿತಾಂಶ(&dialog_ಫಲಿತಾಂಶ);

        ಆದರೆ (dialog_ಫಲಿತಾಂಶ.buttonId == SCE_ಸಂದೇಶ_DIALOG_BUTTON_ID_BUTTON1) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dialog_ಫಲಿತಾಂಶ.buttonId == SCE_ಸಂದೇಶ_DIALOG_BUTTON_ID_BUTTON2) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dialog_ಫಲಿತಾಂಶ.buttonId == SCE_ಸಂದೇಶ_DIALOG_BUTTON_ID_BUTTON3) {
            *buttonID = messageboxdata->buttons[2].buttonID;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dialog_ಫಲಿತಾಂಶ.buttonId == SCE_ಸಂದೇಶ_DIALOG_BUTTON_ID_YES) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dialog_ಫಲಿತಾಂಶ.buttonId == SCE_ಸಂದೇಶ_DIALOG_BUTTON_ID_NO) {
            *buttonID = messageboxdata->buttons[1].buttonID;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dialog_ಫಲಿತಾಂಶ.buttonId == SCE_ಸಂದೇಶ_DIALOG_BUTTON_ID_OK) {
            *buttonID = messageboxdata->buttons[0].buttonID;
        }
        sce_ಸಂದೇಶ_Dialog_ಪದ();
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ false;
    }

    gxm_ಪದ_for_common_dialog();

    ಆದರೆ (ಸಿದ್ಧತೆ_ಕನಿಷ್ಠತಮ_gxm) {
        gxm_ಕನಿಷ್ಠತಮ_ಪದ_for_common_dialog();
    }

    ಹಿಂತಿರುಗಿ true;
#ಇಲ್ಲದಿದ್ದರೆ
    (ಶೂನ್ಯ)messageboxdata;
    (ಶೂನ್ಯ)buttonID;
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_RENDER_VITA_GXM
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_VITA
