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

#ifdef SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "../../dialog/unix/SDL_zenitymessagebox.h"
#अन्तर्भाव "SDL_x11messagebox.h"
#अन्तर्भाव "SDL_x11toolkit.h"

#ifndef SDL_FORK_MESSAGEBOX
#define SDL_FORK_MESSAGEBOX 0
#endif

#जइ SDL_FORK_MESSAGEBOX
#अन्तर्भाव <sys/types.h>
#अन्तर्भाव <sys/wait.h>
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <errno.h>
#endif

प्रकारनिर्देश संरचना SDL_MessageBoxX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *message;
    SDL_ToolkitControlX11 **buttons;
    ध्रुव SDL_MessageBoxData *messageboxdata;
    पूर्णाङ्क *buttonID;
} SDL_MessageBoxX11;

स्थिर शून्य X11_MessageBoxButtonCallback(SDL_ToolkitControlX11 *control, शून्य *data)
{
    SDL_MessageBoxX11 *cbdata;

    cbdata = data;
    *cbdata->buttonID = X11Toolkit_GetButtonControlData(control)->buttonID;
    X11Toolkit_SignalWindowClose(cbdata->window);
}

स्थिर शून्य X11_PositionMessageBox(SDL_MessageBoxX11 *controls, पूर्णाङ्क *wp, पूर्णाङ्क *hp) {
    पूर्णाङ्क first_पङ्क्तिः_width;
    पूर्णाङ्क first_पङ्क्तिः_height;
    पूर्णाङ्क second_पङ्क्तिः_width;
    पूर्णाङ्क second_पङ्क्तिः_height;
    पूर्णाङ्क max_button_width;
    पूर्णाङ्क max_button_height;
    पूर्णाङ्क window_width;
    पूर्णाङ्क window_height;
    पूर्णाङ्क i;
    bool rtl;
    
    /* window size */
    window_width = 1;
    window_height = 1;
    
    /* rtl */
    जइ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_दक्षिणः_TO_वामः) {
        rtl = true;
    } अण्णहा जइ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_वामः_TO_दक्षिणः) {
        rtl = false;
    } अण्णहा {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_पङ्क्तिः_width = first_पङ्क्तिः_height = 0;
    जइ (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_पङ्क्तिः_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        जइ (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } अण्णहा {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        जइ (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_पङ्क्तिः_Height(controls->message))/2;
            first_पङ्क्तिः_height = controls->message->rect.y + controls->message->rect.h;
        } अण्णहा {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_पङ्क्तिः_height = controls->icon->rect.h;
        }        
    } अण्णहा जइ (!controls->icon && controls->message) {
        first_पङ्क्तिः_width = controls->message->rect.w;  
        first_पङ्क्तिः_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } अण्णहा जइ (controls->icon && !controls->message) {
        first_पङ्क्तिः_width = controls->icon->rect.w;  
        first_पङ्क्तिः_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_पङ्क्तिः_width = second_पङ्क्तिः_height = 0;
    
    प्रति (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    जइ (rtl) {
        प्रति (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            जइ (first_पङ्क्तिः_height) {
                controls->buttons[i]->rect.y = first_पङ्क्तिः_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_पङ्क्तिः_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } अण्णहा {
                second_पङ्क्तिः_height = max_button_height;
            }
            
            जइ ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } अण्णहा {
        प्रति (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            जइ (first_पङ्क्तिः_height) {
                controls->buttons[i]->rect.y = first_पङ्क्तिः_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_पङ्क्तिः_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } अण्णहा {
                second_पङ्क्तिः_height = max_button_height;
            }
            
            जइ (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    जइ (controls->messageboxdata->numbuttons) {
        जइ (rtl) {
            second_पङ्क्तिः_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } अण्णहा {
            second_पङ्क्तिः_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    जइ (second_पङ्क्तिः_width > first_पङ्क्तिः_width) {
        पूर्णाङ्क pad;
        
        pad = (second_पङ्क्तिः_width - first_पङ्क्तिः_width)/2;
        जइ (controls->message) {
            controls->message->rect.x += pad;
        }
        जइ (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } अण्णहा {
        पूर्णाङ्क pad;
        
        pad = (first_पङ्क्तिः_width - second_पङ्क्तिः_width)/2;
        प्रति (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_पङ्क्तिः_width, second_पङ्क्तिः_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_पङ्क्तिः_height + second_पङ्क्तिः_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    जइ (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    जइ (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    प्रति (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
}

स्थिर शून्य X11_OnMessageBoxScaleChange(SDL_ToolkitWindowX11 *window, शून्य *data) {
    SDL_MessageBoxX11 *controls;
    पूर्णाङ्क w;
    पूर्णाङ्क h;

    controls = data;
    X11_PositionMessageBox(controls, &w, &h);
    X11Toolkit_ResizeWindow(window, w, h);
}

स्थिर bool X11_ShowMessageBoxImpl(ध्रुव SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = रिक्त;
    SDL_MessageBoxX11 controls;
    ध्रुव SDL_MessageBoxColor *colorhints;
    पूर्णाङ्क i;
    पूर्णाङ्क w;
    पूर्णाङ्क h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    जइ (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } अण्णहा {
        colorhints = रिक्त;
    }

    /* Create window */
    जइ (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#जइ SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, रिक्त, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#अण्णहा 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, रिक्त, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#endif
    जइ (!controls.window) {
        प्रत्यागम false;
    }
    controls.window->cb_data = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, परिमाण(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (वर्ण *)messageboxdata->message);
    प्रति (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.window, &messageboxdata->buttons[i]);
        X11Toolkit_RegisterCallbackForButtonControl(controls.buttons[i], &controls, X11_MessageBoxButtonCallback);
    }

    /* Positioning */
    X11_PositionMessageBox(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11Toolkit_CreateWindowRes(controls.window, w, h, 0, 0, (वर्ण *)messageboxdata->title);
    X11Toolkit_DoWindowEventLoop(controls.window);
    X11Toolkit_DestroyWindow(controls.window);
    SDL_free(controls.buttons);
    प्रत्यागम true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(ध्रुव SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID)
{
    जइ (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        प्रत्यागम true;
    }

#जइ SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    पूर्णाङ्क fds[2];
    पूर्णाङ्क status = 0;
    bool result = true;

    जइ (pipe(fds) == -1) {
        प्रत्यागम X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    जइ (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        प्रत्यागम X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } अण्णहा जइ (pid == 0) {                                       // we're the child
        पूर्णाङ्क exitcode = 0;
        close(fds[0]);
        result = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        जइ (लिख(fds[1], &result, परिमाण(result)) != परिमाण(result)) {
            exitcode = 1;
        } अण्णहा जइ (लिख(fds[1], buttonID, परिमाण(*buttonID)) != परिमाण(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } अण्णहा {             // we're the parent
        pid_t rc;
        close(fds[1]);
        करेहि {
            rc = waitpid(pid, &status, 0);
        } जाव ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        जइ ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            result = SDL_SetError("msgbox child process failed");
        } अण्णहा जइ ((पठ(fds[0], &result, परिमाण(result)) != परिमाण(result)) ||
                   (पठ(fds[0], buttonID, परिमाण(*buttonID)) != परिमाण(*buttonID))) {
            result = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        प्रत्यागम result;
    }
#अण्णहा
    प्रत्यागम X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#endif
}
#endif // SDL_VIDEO_DRIVER_X11
