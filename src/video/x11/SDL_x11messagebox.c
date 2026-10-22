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

#जर SDL_FORK_MESSAGEBOX
#अन्तर्भाव <sys/types.h>
#अन्तर्भाव <sys/wait.h>
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <errno.h>
#endif

प्रकारव्याख्या संरचना SDL_MessageBoxX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *message;
    SDL_ToolkitControlX11 **buttons;
    स्थिरांक SDL_MessageBoxData *messageboxdata;
    पूर्णांक *buttonID;
} SDL_MessageBoxX11;

स्थिर शून्य X11_MessageBoxButtonCallback(SDL_ToolkitControlX11 *control, शून्य *data)
{
    SDL_MessageBoxX11 *cbdata;

    cbdata = data;
    *cbdata->buttonID = X11Toolkit_GetButtonControlData(control)->buttonID;
    X11Toolkit_SignalWindowClose(cbdata->window);
}

स्थिर शून्य X11_PositionMessageBox(SDL_MessageBoxX11 *controls, पूर्णांक *wp, पूर्णांक *hp) {
    पूर्णांक first_ओळ_width;
    पूर्णांक first_ओळ_height;
    पूर्णांक second_ओळ_width;
    पूर्णांक second_ओळ_height;
    पूर्णांक max_button_width;
    पूर्णांक max_button_height;
    पूर्णांक window_width;
    पूर्णांक window_height;
    पूर्णांक i;
    bool rtl;
    
    /* window size */
    window_width = 1;
    window_height = 1;
    
    /* rtl */
    जर (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_उजवा_TO_डावा) {
        rtl = true;
    } अन्यथा जर (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_डावा_TO_उजवा) {
        rtl = false;
    } अन्यथा {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_ओळ_width = first_ओळ_height = 0;
    जर (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_ओळ_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        जर (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } अन्यथा {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        जर (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_ओळ_Height(controls->message))/2;
            first_ओळ_height = controls->message->rect.y + controls->message->rect.h;
        } अन्यथा {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_ओळ_height = controls->icon->rect.h;
        }        
    } अन्यथा जर (!controls->icon && controls->message) {
        first_ओळ_width = controls->message->rect.w;  
        first_ओळ_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } अन्यथा जर (controls->icon && !controls->message) {
        first_ओळ_width = controls->icon->rect.w;  
        first_ओळ_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_ओळ_width = second_ओळ_height = 0;
    
    साठी (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    जर (rtl) {
        साठी (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            जर (first_ओळ_height) {
                controls->buttons[i]->rect.y = first_ओळ_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_ओळ_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } अन्यथा {
                second_ओळ_height = max_button_height;
            }
            
            जर ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } अन्यथा {
        साठी (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            जर (first_ओळ_height) {
                controls->buttons[i]->rect.y = first_ओळ_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_ओळ_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } अन्यथा {
                second_ओळ_height = max_button_height;
            }
            
            जर (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    जर (controls->messageboxdata->numbuttons) {
        जर (rtl) {
            second_ओळ_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } अन्यथा {
            second_ओळ_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    जर (second_ओळ_width > first_ओळ_width) {
        पूर्णांक pad;
        
        pad = (second_ओळ_width - first_ओळ_width)/2;
        जर (controls->message) {
            controls->message->rect.x += pad;
        }
        जर (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } अन्यथा {
        पूर्णांक pad;
        
        pad = (first_ओळ_width - second_ओळ_width)/2;
        साठी (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_ओळ_width, second_ओळ_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_ओळ_height + second_ओळ_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    जर (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    जर (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    साठी (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
}

स्थिर शून्य X11_OnMessageBoxScaleChange(SDL_ToolkitWindowX11 *window, शून्य *data) {
    SDL_MessageBoxX11 *controls;
    पूर्णांक w;
    पूर्णांक h;

    controls = data;
    X11_PositionMessageBox(controls, &w, &h);
    X11Toolkit_ResizeWindow(window, w, h);
}

स्थिर bool X11_ShowMessageBoxImpl(स्थिरांक SDL_MessageBoxData *messageboxdata, पूर्णांक *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = रिक्त;
    SDL_MessageBoxX11 controls;
    स्थिरांक SDL_MessageBoxColor *colorhints;
    पूर्णांक i;
    पूर्णांक w;
    पूर्णांक h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    जर (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } अन्यथा {
        colorhints = रिक्त;
    }

    /* Create window */
    जर (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#जर SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, रिक्त, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#अन्यथा 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, रिक्त, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#endif
    जर (!controls.window) {
        परत false;
    }
    controls.window->cb_data = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, आकार(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (अक्षर *)messageboxdata->message);
    साठी (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.window, &messageboxdata->buttons[i]);
        X11Toolkit_RegisterCallbackForButtonControl(controls.buttons[i], &controls, X11_MessageBoxButtonCallback);
    }

    /* Positioning */
    X11_PositionMessageBox(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11Toolkit_CreateWindowRes(controls.window, w, h, 0, 0, (अक्षर *)messageboxdata->title);
    X11Toolkit_DoWindowEventLoop(controls.window);
    X11Toolkit_DestroyWindow(controls.window);
    SDL_free(controls.buttons);
    परत true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(स्थिरांक SDL_MessageBoxData *messageboxdata, पूर्णांक *buttonID)
{
    जर (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        परत true;
    }

#जर SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    पूर्णांक fds[2];
    पूर्णांक status = 0;
    bool result = true;

    जर (pipe(fds) == -1) {
        परत X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = विभाजन();
    जर (pid == -1) { // failed
        बंद(fds[0]);
        बंद(fds[1]);
        परत X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } अन्यथा जर (pid == 0) {                                       // we're the child
        पूर्णांक exitcode = 0;
        बंद(fds[0]);
        result = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        जर (लिख(fds[1], &result, आकार(result)) != आकार(result)) {
            exitcode = 1;
        } अन्यथा जर (लिख(fds[1], buttonID, आकार(*buttonID)) != आकार(*buttonID)) {
            exitcode = 1;
        }
        बंद(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } अन्यथा {             // we're the parent
        pid_t rc;
        बंद(fds[1]);
        करा {
            rc = waitpid(pid, &status, 0);
        } पर्यंत ((rc == -1) && (त्रुटि_सं == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        जर ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            result = SDL_SetError("msgbox child process failed");
        } अन्यथा जर ((पठ(fds[0], &result, आकार(result)) != आकार(result)) ||
                   (पठ(fds[0], buttonID, आकार(*buttonID)) != आकार(*buttonID))) {
            result = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        बंद(fds[0]);

        परत result;
    }
#अन्यथा
    परत X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#endif
}
#endif // SDL_VIDEO_DRIVER_X11
