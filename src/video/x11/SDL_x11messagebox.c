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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "../../dialog/unix/SDL_zenitymessagebox.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11messagebox.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11toolkit.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_FORK_MESSAGEBOX
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_FORK_MESSAGEBOX 0
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ SDL_FORK_MESSAGEBOX
#ಅನ್ತರ್ಭಾವ <sys/types.h>
#ಅನ್ತರ್ಭಾವ <sys/wait.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_ಸಂದೇಶ_Box_X11
{
    SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *ಸಂದೇಶ;
    SDL_ToolkitControlX11 **buttons;
    ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata;
    ಪೂರ್ಣಾಂಕ *buttonID;
} SDL_ಸಂದೇಶ_Box_X11;

ಸ್ಥಿರ ಶೂನ್ಯ X11_ಸಂದೇಶ_Box_Button_Callback(SDL_ToolkitControlX11 *control, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    SDL_ಸಂದೇಶ_Box_X11 *cbdata;

    cbdata = ದತ್ತಾಂಶ;
    *cbdata->buttonID = X11_Toolkit_Get_Button_Control_ದತ್ತಾಂಶ(control)->buttonID;
    X11_Toolkit_Signal_ಕಿಟಕಿ_Close(cbdata->ಕಿಟಕಿ);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Position_ಸಂದೇಶ_Box(SDL_ಸಂದೇಶ_Box_X11 *controls, ಪೂರ್ಣಾಂಕ *wp, ಪೂರ್ಣಾಂಕ *hp) {
    ಪೂರ್ಣಾಂಕ ಮೊದಲ_ಸಾಲು_ಅಗಲ;
    ಪೂರ್ಣಾಂಕ ಮೊದಲ_ಸಾಲು_ಎತ್ತರ;
    ಪೂರ್ಣಾಂಕ ಎರಡನೇ_ಸಾಲು_ಅಗಲ;
    ಪೂರ್ಣಾಂಕ ಎರಡನೇ_ಸಾಲು_ಎತ್ತರ;
    ಪೂರ್ಣಾಂಕ max_button_ಅಗಲ;
    ಪೂರ್ಣಾಂಕ max_button_ಎತ್ತರ;
    ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_ಅಗಲ;
    ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_ಎತ್ತರ;
    ಪೂರ್ಣಾಂಕ i;
    bool rtl;
    
    /* window size */
    ಕಿಟಕಿ_ಅಗಲ = 1;
    ಕಿಟಕಿ_ಎತ್ತರ = 1;
    
    /* rtl */
    ಆದರೆ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ಬಲ_ಗಮ್ಯ_ಎಡ) {
        rtl = true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ಎಡ_ಗಮ್ಯ_ಬಲ) {
        rtl = false;
    } ಇಲ್ಲದಿದ್ದರೆ {
        rtl = controls->ಕಿಟಕಿ->flip_interface;
    }
    
    /* first line */
    ಮೊದಲ_ಸಾಲು_ಅಗಲ = ಮೊದಲ_ಸಾಲು_ಎತ್ತರ = 0;
    ಆದರೆ (controls->icon && controls->ಸಂದೇಶ) {
        controls->icon->rect.y = 0;
        
        ಮೊದಲ_ಸಾಲು_ಅಗಲ = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ಕಿಟಕಿ->iscale + controls->ಸಂದೇಶ->rect.w;  
        
        ಆದರೆ (!controls->ಕಿಟಕಿ->flip_interface) {
            controls->ಸಂದೇಶ->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->ಕಿಟಕಿ->iscale;
            controls->icon->rect.x = 0;
        } ಇಲ್ಲದಿದ್ದರೆ {
            controls->ಸಂದೇಶ->rect.x = 0;    
            controls->icon->rect.x = controls->ಸಂದೇಶ->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->ಕಿಟಕಿ->iscale;
        }
        
        ಆದರೆ (controls->ಸಂದೇಶ->rect.h > controls->icon->rect.h) {
            controls->ಸಂದೇಶ->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_ಮೊದಲ_ಸಾಲು_ಎತ್ತರ(controls->ಸಂದೇಶ))/2;
            ಮೊದಲ_ಸಾಲು_ಎತ್ತರ = controls->ಸಂದೇಶ->rect.y + controls->ಸಂದೇಶ->rect.h;
        } ಇಲ್ಲದಿದ್ದರೆ {
            controls->ಸಂದೇಶ->rect.y = (controls->icon->rect.h - controls->ಸಂದೇಶ->rect.h)/2;
            ಮೊದಲ_ಸಾಲು_ಎತ್ತರ = controls->icon->rect.h;
        }        
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!controls->icon && controls->ಸಂದೇಶ) {
        ಮೊದಲ_ಸಾಲು_ಅಗಲ = controls->ಸಂದೇಶ->rect.w;  
        ಮೊದಲ_ಸಾಲು_ಎತ್ತರ = controls->ಸಂದೇಶ->rect.h;
        controls->ಸಂದೇಶ->rect.x = 0;
        controls->ಸಂದೇಶ->rect.y = 0;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (controls->icon && !controls->ಸಂದೇಶ) {
        ಮೊದಲ_ಸಾಲು_ಅಗಲ = controls->icon->rect.w;  
        ಮೊದಲ_ಸಾಲು_ಎತ್ತರ = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_ಅಗಲ = 50;
    max_button_ಎತ್ತರ = 0;
    ಎರಡನೇ_ಸಾಲು_ಅಗಲ = ಎರಡನೇ_ಸಾಲು_ಎತ್ತರ = 0;
    
    ಗಾಗಿ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_ಅಗಲ = SDL_max(max_button_ಅಗಲ, controls->buttons[i]->rect.w);
        max_button_ಎತ್ತರ = SDL_max(max_button_ಎತ್ತರ, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    ಆದರೆ (rtl) {
        ಗಾಗಿ (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_ಅಗಲ;
            controls->buttons[i]->rect.h = max_button_ಎತ್ತರ;
            X11_Toolkit_Notify_Control_ದ_ಗಾತ್ರ_Change(controls->buttons[i]);

            ಆದರೆ (ಮೊದಲ_ಸಾಲು_ಎತ್ತರ) {
                controls->buttons[i]->rect.y = ಮೊದಲ_ಸಾಲು_ಎತ್ತರ + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->ಕಿಟಕಿ->iscale;
                ಎರಡನೇ_ಸಾಲು_ಎತ್ತರ = max_button_ಎತ್ತರ + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->ಕಿಟಕಿ->iscale;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಎರಡನೇ_ಸಾಲು_ಎತ್ತರ = max_button_ಎತ್ತರ;
            }
            
            ಆದರೆ ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->ಕಿಟಕಿ->iscale);
            }
        }    
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_ಅಗಲ;
            controls->buttons[i]->rect.h = max_button_ಎತ್ತರ;
            X11_Toolkit_Notify_Control_ದ_ಗಾತ್ರ_Change(controls->buttons[i]);

            ಆದರೆ (ಮೊದಲ_ಸಾಲು_ಎತ್ತರ) {
                controls->buttons[i]->rect.y = ಮೊದಲ_ಸಾಲು_ಎತ್ತರ + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->ಕಿಟಕಿ->iscale;
                ಎರಡನೇ_ಸಾಲು_ಎತ್ತರ = max_button_ಎತ್ತರ + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->ಕಿಟಕಿ->iscale;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಎರಡನೇ_ಸಾಲು_ಎತ್ತರ = max_button_ಎತ್ತರ;
            }
            
            ಆದರೆ (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->ಕಿಟಕಿ->iscale);
            }
        }
    }
    
    ಆದರೆ (controls->messageboxdata->numbuttons) {
        ಆದರೆ (rtl) {
            ಎರಡನೇ_ಸಾಲು_ಅಗಲ = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಎರಡನೇ_ಸಾಲು_ಅಗಲ = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    ಆದರೆ (ಎರಡನೇ_ಸಾಲು_ಅಗಲ > ಮೊದಲ_ಸಾಲು_ಅಗಲ) {
        ಪೂರ್ಣಾಂಕ pad;
        
        pad = (ಎರಡನೇ_ಸಾಲು_ಅಗಲ - ಮೊದಲ_ಸಾಲು_ಅಗಲ)/2;
        ಆದರೆ (controls->ಸಂದೇಶ) {
            controls->ಸಂದೇಶ->rect.x += pad;
        }
        ಆದರೆ (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಪೂರ್ಣಾಂಕ pad;
        
        pad = (ಮೊದಲ_ಸಾಲು_ಅಗಲ - ಎರಡನೇ_ಸಾಲು_ಅಗಲ)/2;
        ಗಾಗಿ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    ಕಿಟಕಿ_ಅಗಲ = SDL_max(ಮೊದಲ_ಸಾಲು_ಅಗಲ, ಎರಡನೇ_ಸಾಲು_ಅಗಲ) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->ಕಿಟಕಿ->iscale;
    ಕಿಟಕಿ_ಎತ್ತರ = ಮೊದಲ_ಸಾಲು_ಎತ್ತರ + ಎರಡನೇ_ಸಾಲು_ಎತ್ತರ + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->ಕಿಟಕಿ->iscale;
    *wp = ಕಿಟಕಿ_ಅಗಲ;
    *hp = ಕಿಟಕಿ_ಎತ್ತರ;
    ಆದರೆ (controls->ಸಂದೇಶ) {
        controls->ಸಂದೇಶ->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ಕಿಟಕಿ->iscale;
        controls->ಸಂದೇಶ->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ಕಿಟಕಿ->iscale;
    }
    ಆದರೆ (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ಕಿಟಕಿ->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ಕಿಟಕಿ->iscale;
    }
    ಗಾಗಿ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ಕಿಟಕಿ->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ಕಿಟಕಿ->iscale;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_On_ಸಂದೇಶ_Box_Scale_Change(SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ, ಶೂನ್ಯ *ದತ್ತಾಂಶ) {
    SDL_ಸಂದೇಶ_Box_X11 *controls;
    ಪೂರ್ಣಾಂಕ w;
    ಪೂರ್ಣಾಂಕ h;

    controls = ದತ್ತಾಂಶ;
    X11_Position_ಸಂದೇಶ_Box(controls, &w, &h);
    X11_Toolkit_Resize_ಕಿಟಕಿ(ಕಿಟಕಿ, w, h);
}

ಸ್ಥಿರ bool X11_Show_ಸಂದೇಶ_Box_Impl(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_ಕಿಟಕಿ *ಪೋಷಕ_ಕಿಟಕಿ = ಖಾಲಿ;
    SDL_ಸಂದೇಶ_Box_X11 controls;
    ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color *colorhints;
    ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ w;
    ಪೂರ್ಣಾಂಕ h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    ಆದರೆ (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } ಇಲ್ಲದಿದ್ದರೆ {
        colorhints = ಖಾಲಿ;
    }

    /* Create window */
    ಆದರೆ (messageboxdata->ಕಿಟಕಿ && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        ಪೋಷಕ_ಕಿಟಕಿ = messageboxdata->ಕಿಟಕಿ;
    }
#ಆದರೆ SDL_FORK_MESSAGEBOX
    controls.ಕಿಟಕಿ = X11_Toolkit_Create_ಕಿಟಕಿ_Struct(ಪೋಷಕ_ಕಿಟಕಿ, ಖಾಲಿ, SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_DIALOG, colorhints, true);
#ಇಲ್ಲದಿದ್ದರೆ 
    controls.ಕಿಟಕಿ = X11_Toolkit_Create_ಕಿಟಕಿ_Struct(ಪೋಷಕ_ಕಿಟಕಿ, ಖಾಲಿ, SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_DIALOG, colorhints, false);
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (!controls.ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ false;
    }
    controls.ಕಿಟಕಿ->cb_ದತ್ತಾಂಶ = &controls;
    controls.ಕಿಟಕಿ->cb_on_scale_change = X11_On_ಸಂದೇಶ_Box_Scale_Change;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, ಗಾತ್ರ(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.ಕಿಟಕಿ, messageboxdata->flags);
    controls.ಸಂದೇಶ = X11Toolkit_CreateLabelControl(controls.ಕಿಟಕಿ, (ಅಕ್ಷರ *)messageboxdata->ಸಂದೇಶ);
    ಗಾಗಿ (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.ಕಿಟಕಿ, &messageboxdata->buttons[i]);
        X11_Toolkit_ರಿಜಿಸ್ಟರ್_Callback_For_Button_Control(controls.buttons[i], &controls, X11_ಸಂದೇಶ_Box_Button_Callback);
    }

    /* Positioning */
    X11_Position_ಸಂದೇಶ_Box(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11_Toolkit_Create_ಕಿಟಕಿ_Res(controls.ಕಿಟಕಿ, w, h, 0, 0, (ಅಕ್ಷರ *)messageboxdata->title);
    X11_Toolkit_Do_ಕಿಟಕಿ_Event_Loop(controls.ಕಿಟಕಿ);
    X11_Toolkit_Destroy_ಕಿಟಕಿ(controls.ಕಿಟಕಿ);
    SDL_free(controls.buttons);
    ಹಿಂತಿರುಗಿ true;
}

// Display an x11 message box.
bool X11_Show_ಸಂದೇಶ_Box(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonID)
{
    ಆದರೆ (SDL_Zenity_Show_ಸಂದೇಶ_Box(messageboxdata, buttonID)) {
        ಹಿಂತಿರುಗಿ true;
    }

#ಆದರೆ SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    ಪೂರ್ಣಾಂಕ fds[2];
    ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2 = 0;
    bool ಫಲಿತಾಂಶ = true;

    ಆದರೆ (pipe(fds) == -1) {
        ಹಿಂತಿರುಗಿ X11_Show_ಸಂದೇಶ_Box_Impl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    ಆದರೆ (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        ಹಿಂತಿರುಗಿ X11_Show_ಸಂದೇಶ_Box_Impl(messageboxdata, buttonID); // oh well.
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (pid == 0) {                                       // we're the child
        ಪೂರ್ಣಾಂಕ exitcode = 0;
        close(fds[0]);
        ಫಲಿತಾಂಶ = X11_Show_ಸಂದೇಶ_Box_Impl(messageboxdata, buttonID);
        ಆದರೆ (ಲಿಖ(fds[1], &ಫಲಿತಾಂಶ, ಗಾತ್ರ(ಫಲಿತಾಂಶ)) != ಗಾತ್ರ(ಫಲಿತಾಂಶ)) {
            exitcode = 1;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಲಿಖ(fds[1], buttonID, ಗಾತ್ರ(*buttonID)) != ಗಾತ್ರ(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } ಇಲ್ಲದಿದ್ದರೆ {             // we're the parent
        pid_t rc;
        close(fds[1]);
        ಮಾಡು {
            rc = waitpid(pid, &ಸ್ಥಿತಿ_2, 0);
        } ಆಗ ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        ಆದರೆ ((rc == -1) || (!WIFEXITED(ಸ್ಥಿತಿ_2)) || (WEXITSTATUS(ಸ್ಥಿತಿ_2) != 0)) {
            ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("msgbox child process failed");
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಪಠ(fds[0], &ಫಲಿತಾಂಶ, ಗಾತ್ರ(ಫಲಿತಾಂಶ)) != ಗಾತ್ರ(ಫಲಿತಾಂಶ)) ||
                   (ಪಠ(fds[0], buttonID, ಗಾತ್ರ(*buttonID)) != ಗಾತ್ರ(*buttonID))) {
            ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ X11_Show_ಸಂದೇಶ_Box_Impl(messageboxdata, buttonID);
#ಆದರೆ_ಅಂತ್ಯ
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
