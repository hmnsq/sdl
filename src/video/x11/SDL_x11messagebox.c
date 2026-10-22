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

#ifdef SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "../../dialog/unix/SDL_zenitymessagebox.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11messagebox.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11toolkit.h"

#ifndef SDL_FORK_MESSAGEBOX
#define SDL_FORK_MESSAGEBOX 0
#endif

#ಯದಿ SDL_FORK_MESSAGEBOX
#ಅನ್ತರ್ಭಾವ <sys/types.h>
#ಅನ್ತರ್ಭಾವ <sys/wait.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <errno.h>
#endif

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_MessageBoxX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *message;
    SDL_ToolkitControlX11 **buttons;
    ಧ್ರುವ SDL_MessageBoxData *messageboxdata;
    ಪೂರ್ಣಾಙ್ಕ *buttonID;
} SDL_MessageBoxX11;

ಸ್ಥಿರ ಶೂನ್ಯ X11_MessageBoxButtonCallback(SDL_ToolkitControlX11 *control, ಶೂನ್ಯ *data)
{
    SDL_MessageBoxX11 *cbdata;

    cbdata = data;
    *cbdata->buttonID = X11Toolkit_GetButtonControlData(control)->buttonID;
    X11Toolkit_SignalWindowClose(cbdata->window);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_PositionMessageBox(SDL_MessageBoxX11 *controls, ಪೂರ್ಣಾಙ್ಕ *wp, ಪೂರ್ಣಾಙ್ಕ *hp) {
    ಪೂರ್ಣಾಙ್ಕ first_ಸಾಲು_width;
    ಪೂರ್ಣಾಙ್ಕ first_ಸಾಲು_height;
    ಪೂರ್ಣಾಙ್ಕ second_ಸಾಲು_width;
    ಪೂರ್ಣಾಙ್ಕ second_ಸಾಲು_height;
    ಪೂರ್ಣಾಙ್ಕ max_button_width;
    ಪೂರ್ಣಾಙ್ಕ max_button_height;
    ಪೂರ್ಣಾಙ್ಕ window_width;
    ಪೂರ್ಣಾಙ್ಕ window_height;
    ಪೂರ್ಣಾಙ್ಕ i;
    bool rtl;
    
    /* window size */
    window_width = 1;
    window_height = 1;
    
    /* rtl */
    ಯದಿ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ಬಲ_TO_ಎಡ) {
        rtl = true;
    } ಅನ್ಯಥಾ ಯದಿ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ಎಡ_TO_ಬಲ) {
        rtl = false;
    } ಅನ್ಯಥಾ {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_ಸಾಲು_width = first_ಸಾಲು_height = 0;
    ಯದಿ (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_ಸಾಲು_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        ಯದಿ (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } ಅನ್ಯಥಾ {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        ಯದಿ (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_ಸಾಲು_Height(controls->message))/2;
            first_ಸಾಲು_height = controls->message->rect.y + controls->message->rect.h;
        } ಅನ್ಯಥಾ {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_ಸಾಲು_height = controls->icon->rect.h;
        }        
    } ಅನ್ಯಥಾ ಯದಿ (!controls->icon && controls->message) {
        first_ಸಾಲು_width = controls->message->rect.w;  
        first_ಸಾಲು_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } ಅನ್ಯಥಾ ಯದಿ (controls->icon && !controls->message) {
        first_ಸಾಲು_width = controls->icon->rect.w;  
        first_ಸಾಲು_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_ಸಾಲು_width = second_ಸಾಲು_height = 0;
    
    ಪ್ರತಿ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    ಯದಿ (rtl) {
        ಪ್ರತಿ (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            ಯದಿ (first_ಸಾಲು_height) {
                controls->buttons[i]->rect.y = first_ಸಾಲು_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_ಸಾಲು_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } ಅನ್ಯಥಾ {
                second_ಸಾಲು_height = max_button_height;
            }
            
            ಯದಿ ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } ಅನ್ಯಥಾ {
        ಪ್ರತಿ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            ಯದಿ (first_ಸಾಲು_height) {
                controls->buttons[i]->rect.y = first_ಸಾಲು_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_ಸಾಲು_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } ಅನ್ಯಥಾ {
                second_ಸಾಲು_height = max_button_height;
            }
            
            ಯದಿ (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    ಯದಿ (controls->messageboxdata->numbuttons) {
        ಯದಿ (rtl) {
            second_ಸಾಲು_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } ಅನ್ಯಥಾ {
            second_ಸಾಲು_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    ಯದಿ (second_ಸಾಲು_width > first_ಸಾಲು_width) {
        ಪೂರ್ಣಾಙ್ಕ pad;
        
        pad = (second_ಸಾಲು_width - first_ಸಾಲು_width)/2;
        ಯದಿ (controls->message) {
            controls->message->rect.x += pad;
        }
        ಯದಿ (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } ಅನ್ಯಥಾ {
        ಪೂರ್ಣಾಙ್ಕ pad;
        
        pad = (first_ಸಾಲು_width - second_ಸಾಲು_width)/2;
        ಪ್ರತಿ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_ಸಾಲು_width, second_ಸಾಲು_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_ಸಾಲು_height + second_ಸಾಲು_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    ಯದಿ (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    ಯದಿ (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    ಪ್ರತಿ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_OnMessageBoxScaleChange(SDL_ToolkitWindowX11 *window, ಶೂನ್ಯ *data) {
    SDL_MessageBoxX11 *controls;
    ಪೂರ್ಣಾಙ್ಕ w;
    ಪೂರ್ಣಾಙ್ಕ h;

    controls = data;
    X11_PositionMessageBox(controls, &w, &h);
    X11Toolkit_ResizeWindow(window, w, h);
}

ಸ್ಥಿರ bool X11_ShowMessageBoxImpl(ಧ್ರುವ SDL_MessageBoxData *messageboxdata, ಪೂರ್ಣಾಙ್ಕ *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = ರಿಕ್ತ;
    SDL_MessageBoxX11 controls;
    ಧ್ರುವ SDL_MessageBoxColor *colorhints;
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪೂರ್ಣಾಙ್ಕ w;
    ಪೂರ್ಣಾಙ್ಕ h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    ಯದಿ (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } ಅನ್ಯಥಾ {
        colorhints = ರಿಕ್ತ;
    }

    /* Create window */
    ಯದಿ (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#ಯದಿ SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, ರಿಕ್ತ, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#ಅನ್ಯಥಾ 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, ರಿಕ್ತ, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#endif
    ಯದಿ (!controls.window) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    controls.window->cb_data = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, ಪರಿಮಾಣ(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (ವರ್ಣ *)messageboxdata->message);
    ಪ್ರತಿ (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.window, &messageboxdata->buttons[i]);
        X11Toolkit_RegisterCallbackForButtonControl(controls.buttons[i], &controls, X11_MessageBoxButtonCallback);
    }

    /* Positioning */
    X11_PositionMessageBox(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11Toolkit_CreateWindowRes(controls.window, w, h, 0, 0, (ವರ್ಣ *)messageboxdata->title);
    X11Toolkit_DoWindowEventLoop(controls.window);
    X11Toolkit_DestroyWindow(controls.window);
    SDL_free(controls.buttons);
    ಪ್ರತ್ಯಾಗಮ true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(ಧ್ರುವ SDL_MessageBoxData *messageboxdata, ಪೂರ್ಣಾಙ್ಕ *buttonID)
{
    ಯದಿ (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

#ಯದಿ SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    ಪೂರ್ಣಾಙ್ಕ fds[2];
    ಪೂರ್ಣಾಙ್ಕ status = 0;
    bool result = true;

    ಯದಿ (pipe(fds) == -1) {
        ಪ್ರತ್ಯಾಗಮ X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    ಯದಿ (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        ಪ್ರತ್ಯಾಗಮ X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } ಅನ್ಯಥಾ ಯದಿ (pid == 0) {                                       // we're the child
        ಪೂರ್ಣಾಙ್ಕ exitcode = 0;
        close(fds[0]);
        result = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        ಯದಿ (ಲಿಖ(fds[1], &result, ಪರಿಮಾಣ(result)) != ಪರಿಮಾಣ(result)) {
            exitcode = 1;
        } ಅನ್ಯಥಾ ಯದಿ (ಲಿಖ(fds[1], buttonID, ಪರಿಮಾಣ(*buttonID)) != ಪರಿಮಾಣ(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } ಅನ್ಯಥಾ {             // we're the parent
        pid_t rc;
        close(fds[1]);
        ಕುರು {
            rc = waitpid(pid, &status, 0);
        } ಯಾವತ್ ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        ಯದಿ ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            result = SDL_SetError("msgbox child process failed");
        } ಅನ್ಯಥಾ ಯದಿ ((ಪಠ(fds[0], &result, ಪರಿಮಾಣ(result)) != ಪರಿಮಾಣ(result)) ||
                   (ಪಠ(fds[0], buttonID, ಪರಿಮಾಣ(*buttonID)) != ಪರಿಮಾಣ(*buttonID))) {
            result = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        ಪ್ರತ್ಯಾಗಮ result;
    }
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#endif
}
#endif // SDL_VIDEO_DRIVER_X11
