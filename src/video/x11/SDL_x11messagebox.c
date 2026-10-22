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

#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#شامل "../../dialog/unix/SDL_zenitymessagebox.h"
#شامل "SDL_x11messagebox.h"
#شامل "SDL_x11toolkit.h"

#ifndef SDL_FORK_MESSAGEBOX
#define SDL_FORK_MESSAGEBOX 0
#endif

#اگر SDL_FORK_MESSAGEBOX
#شامل <sys/types.h>
#شامل <sys/wait.h>
#شامل <unistd.h>
#شامل <errno.h>
#endif

تعریفنوع ساختار SDL_MessageBoxX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *message;
    SDL_ToolkitControlX11 **buttons;
    ثابت SDL_MessageBoxData *messageboxdata;
    صحیح *buttonID;
} SDL_MessageBoxX11;

ایستا تهی X11_MessageBoxButtonCallback(SDL_ToolkitControlX11 *control, تهی *data)
{
    SDL_MessageBoxX11 *cbdata;

    cbdata = data;
    *cbdata->buttonID = X11Toolkit_GetButtonControlData(control)->buttonID;
    X11Toolkit_SignalWindowClose(cbdata->window);
}

ایستا تهی X11_PositionMessageBox(SDL_MessageBoxX11 *controls, صحیح *wp, صحیح *hp) {
    صحیح first_سطر_width;
    صحیح first_سطر_height;
    صحیح second_سطر_width;
    صحیح second_سطر_height;
    صحیح max_button_width;
    صحیح max_button_height;
    صحیح window_width;
    صحیح window_height;
    صحیح i;
    bool rtl;
    
    /* window size */
    window_width = 1;
    window_height = 1;
    
    /* rtl */
    اگر (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_راست_TO_چپ) {
        rtl = true;
    } وگرنه اگر (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_چپ_TO_راست) {
        rtl = false;
    } وگرنه {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_سطر_width = first_سطر_height = 0;
    اگر (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_سطر_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        اگر (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } وگرنه {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        اگر (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_سطر_Height(controls->message))/2;
            first_سطر_height = controls->message->rect.y + controls->message->rect.h;
        } وگرنه {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_سطر_height = controls->icon->rect.h;
        }        
    } وگرنه اگر (!controls->icon && controls->message) {
        first_سطر_width = controls->message->rect.w;  
        first_سطر_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } وگرنه اگر (controls->icon && !controls->message) {
        first_سطر_width = controls->icon->rect.w;  
        first_سطر_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_سطر_width = second_سطر_height = 0;
    
    برای (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    اگر (rtl) {
        برای (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            اگر (first_سطر_height) {
                controls->buttons[i]->rect.y = first_سطر_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_سطر_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } وگرنه {
                second_سطر_height = max_button_height;
            }
            
            اگر ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } وگرنه {
        برای (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            اگر (first_سطر_height) {
                controls->buttons[i]->rect.y = first_سطر_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_سطر_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } وگرنه {
                second_سطر_height = max_button_height;
            }
            
            اگر (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    اگر (controls->messageboxdata->numbuttons) {
        اگر (rtl) {
            second_سطر_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } وگرنه {
            second_سطر_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    اگر (second_سطر_width > first_سطر_width) {
        صحیح pad;
        
        pad = (second_سطر_width - first_سطر_width)/2;
        اگر (controls->message) {
            controls->message->rect.x += pad;
        }
        اگر (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } وگرنه {
        صحیح pad;
        
        pad = (first_سطر_width - second_سطر_width)/2;
        برای (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_سطر_width, second_سطر_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_سطر_height + second_سطر_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    اگر (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    اگر (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    برای (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
}

ایستا تهی X11_OnMessageBoxScaleChange(SDL_ToolkitWindowX11 *window, تهی *data) {
    SDL_MessageBoxX11 *controls;
    صحیح w;
    صحیح h;

    controls = data;
    X11_PositionMessageBox(controls, &w, &h);
    X11Toolkit_ResizeWindow(window, w, h);
}

ایستا bool X11_ShowMessageBoxImpl(ثابت SDL_MessageBoxData *messageboxdata, صحیح *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = پوچ;
    SDL_MessageBoxX11 controls;
    ثابت SDL_MessageBoxColor *colorhints;
    صحیح i;
    صحیح w;
    صحیح h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    اگر (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } وگرنه {
        colorhints = پوچ;
    }

    /* Create window */
    اگر (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#اگر SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, پوچ, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#وگرنه 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, پوچ, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#endif
    اگر (!controls.window) {
        بازگشت false;
    }
    controls.window->cb_data = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, اندازه(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (نویسه *)messageboxdata->message);
    برای (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.window, &messageboxdata->buttons[i]);
        X11Toolkit_RegisterCallbackForButtonControl(controls.buttons[i], &controls, X11_MessageBoxButtonCallback);
    }

    /* Positioning */
    X11_PositionMessageBox(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11Toolkit_CreateWindowRes(controls.window, w, h, 0, 0, (نویسه *)messageboxdata->title);
    X11Toolkit_DoWindowEventLoop(controls.window);
    X11Toolkit_DestroyWindow(controls.window);
    SDL_free(controls.buttons);
    بازگشت true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(ثابت SDL_MessageBoxData *messageboxdata, صحیح *buttonID)
{
    اگر (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        بازگشت true;
    }

#اگر SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    صحیح fds[2];
    صحیح status = 0;
    bool result = true;

    اگر (pipe(fds) == -1) {
        بازگشت X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    اگر (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        بازگشت X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } وگرنه اگر (pid == 0) {                                       // we're the child
        صحیح exitcode = 0;
        close(fds[0]);
        result = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        اگر (اكتب(fds[1], &result, اندازه(result)) != اندازه(result)) {
            exitcode = 1;
        } وگرنه اگر (اكتب(fds[1], buttonID, اندازه(*buttonID)) != اندازه(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } وگرنه {             // we're the parent
        pid_t rc;
        close(fds[1]);
        انجامبده {
            rc = waitpid(pid, &status, 0);
        } وقتی ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        اگر ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            result = SDL_SetError("msgbox child process failed");
        } وگرنه اگر ((اقرأ(fds[0], &result, اندازه(result)) != اندازه(result)) ||
                   (اقرأ(fds[0], buttonID, اندازه(*buttonID)) != اندازه(*buttonID))) {
            result = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        بازگشت result;
    }
#وگرنه
    بازگشت X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#endif
}
#endif // SDL_VIDEO_DRIVER_X11
