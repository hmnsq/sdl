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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#அந்தர்பாவ "../../dialog/unix/SDL_zenitymessagebox.h"
#அந்தர்பாவ "SDL_x11messagebox.h"
#அந்தர்பாவ "SDL_x11toolkit.h"

#ifndef SDL_FORK_MESSAGEBOX
#define SDL_FORK_MESSAGEBOX 0
#endif

#எனில் SDL_FORK_MESSAGEBOX
#அந்தர்பாவ <sys/types.h>
#அந்தர்பாவ <sys/wait.h>
#அந்தர்பாவ <unistd.h>
#அந்தர்பாவ <errno.h>
#endif

வகைவரை கட்டமைப்பு SDL_MessageBoxX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *message;
    SDL_ToolkitControlX11 **buttons;
    மாறிலி SDL_MessageBoxData *messageboxdata;
    முழு *buttonID;
} SDL_MessageBoxX11;

நிலையான வெறுமை X11_MessageBoxButtonCallback(SDL_ToolkitControlX11 *control, வெறுமை *data)
{
    SDL_MessageBoxX11 *cbdata;

    cbdata = data;
    *cbdata->buttonID = X11Toolkit_GetButtonControlData(control)->buttonID;
    X11Toolkit_SignalWindowClose(cbdata->window);
}

நிலையான வெறுமை X11_PositionMessageBox(SDL_MessageBoxX11 *controls, முழு *wp, முழு *hp) {
    முழு first_வரி_width;
    முழு first_வரி_height;
    முழு second_வரி_width;
    முழு second_வரி_height;
    முழு max_button_width;
    முழு max_button_height;
    முழு window_width;
    முழு window_height;
    முழு i;
    bool rtl;
    
    /* window size */
    window_width = 1;
    window_height = 1;
    
    /* rtl */
    எனில் (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_வலது_TO_இடது) {
        rtl = true;
    } இல்லையெனில் எனில் (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_இடது_TO_வலது) {
        rtl = false;
    } இல்லையெனில் {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_வரி_width = first_வரி_height = 0;
    எனில் (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_வரி_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        எனில் (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } இல்லையெனில் {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        எனில் (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_வரி_Height(controls->message))/2;
            first_வரி_height = controls->message->rect.y + controls->message->rect.h;
        } இல்லையெனில் {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_வரி_height = controls->icon->rect.h;
        }        
    } இல்லையெனில் எனில் (!controls->icon && controls->message) {
        first_வரி_width = controls->message->rect.w;  
        first_வரி_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } இல்லையெனில் எனில் (controls->icon && !controls->message) {
        first_வரி_width = controls->icon->rect.w;  
        first_வரி_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_வரி_width = second_வரி_height = 0;
    
    க்கு (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    எனில் (rtl) {
        க்கு (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            எனில் (first_வரி_height) {
                controls->buttons[i]->rect.y = first_வரி_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_வரி_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } இல்லையெனில் {
                second_வரி_height = max_button_height;
            }
            
            எனில் ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } இல்லையெனில் {
        க்கு (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            எனில் (first_வரி_height) {
                controls->buttons[i]->rect.y = first_வரி_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_வரி_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } இல்லையெனில் {
                second_வரி_height = max_button_height;
            }
            
            எனில் (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    எனில் (controls->messageboxdata->numbuttons) {
        எனில் (rtl) {
            second_வரி_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } இல்லையெனில் {
            second_வரி_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    எனில் (second_வரி_width > first_வரி_width) {
        முழு pad;
        
        pad = (second_வரி_width - first_வரி_width)/2;
        எனில் (controls->message) {
            controls->message->rect.x += pad;
        }
        எனில் (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } இல்லையெனில் {
        முழு pad;
        
        pad = (first_வரி_width - second_வரி_width)/2;
        க்கு (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_வரி_width, second_வரி_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_வரி_height + second_வரி_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    எனில் (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    எனில் (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    க்கு (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
}

நிலையான வெறுமை X11_OnMessageBoxScaleChange(SDL_ToolkitWindowX11 *window, வெறுமை *data) {
    SDL_MessageBoxX11 *controls;
    முழு w;
    முழு h;

    controls = data;
    X11_PositionMessageBox(controls, &w, &h);
    X11Toolkit_ResizeWindow(window, w, h);
}

நிலையான bool X11_ShowMessageBoxImpl(மாறிலி SDL_MessageBoxData *messageboxdata, முழு *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = வெற்று;
    SDL_MessageBoxX11 controls;
    மாறிலி SDL_MessageBoxColor *colorhints;
    முழு i;
    முழு w;
    முழு h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    எனில் (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } இல்லையெனில் {
        colorhints = வெற்று;
    }

    /* Create window */
    எனில் (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#எனில் SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, வெற்று, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#இல்லையெனில் 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, வெற்று, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#endif
    எனில் (!controls.window) {
        திரும்பு false;
    }
    controls.window->cb_data = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, அளவு(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (எழுத்து *)messageboxdata->message);
    க்கு (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.window, &messageboxdata->buttons[i]);
        X11Toolkit_RegisterCallbackForButtonControl(controls.buttons[i], &controls, X11_MessageBoxButtonCallback);
    }

    /* Positioning */
    X11_PositionMessageBox(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11Toolkit_CreateWindowRes(controls.window, w, h, 0, 0, (எழுத்து *)messageboxdata->title);
    X11Toolkit_DoWindowEventLoop(controls.window);
    X11Toolkit_DestroyWindow(controls.window);
    SDL_free(controls.buttons);
    திரும்பு true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(மாறிலி SDL_MessageBoxData *messageboxdata, முழு *buttonID)
{
    எனில் (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        திரும்பு true;
    }

#எனில் SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    முழு fds[2];
    முழு status = 0;
    bool result = true;

    எனில் (pipe(fds) == -1) {
        திரும்பு X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    எனில் (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        திரும்பு X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } இல்லையெனில் எனில் (pid == 0) {                                       // we're the child
        முழு exitcode = 0;
        close(fds[0]);
        result = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        எனில் (லிக(fds[1], &result, அளவு(result)) != அளவு(result)) {
            exitcode = 1;
        } இல்லையெனில் எனில் (லிக(fds[1], buttonID, அளவு(*buttonID)) != அளவு(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } இல்லையெனில் {             // we're the parent
        pid_t rc;
        close(fds[1]);
        செய் {
            rc = waitpid(pid, &status, 0);
        } போது ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        எனில் ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            result = SDL_SetError("msgbox child process failed");
        } இல்லையெனில் எனில் ((பட(fds[0], &result, அளவு(result)) != அளவு(result)) ||
                   (பட(fds[0], buttonID, அளவு(*buttonID)) != அளவு(*buttonID))) {
            result = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        திரும்பு result;
    }
#இல்லையெனில்
    திரும்பு X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#endif
}
#endif // SDL_VIDEO_DRIVER_X11
