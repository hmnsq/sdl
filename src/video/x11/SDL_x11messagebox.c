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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#അന്തര്ഭാവ "../../dialog/unix/SDL_zenitymessagebox.h"
#അന്തര്ഭാവ "SDL_x11messagebox.h"
#അന്തര്ഭാവ "SDL_x11toolkit.h"

#ifndef SDL_FORK_MESSAGEBOX
#define SDL_FORK_MESSAGEBOX 0
#endif

#എങ്കിൽ SDL_FORK_MESSAGEBOX
#അന്തര്ഭാവ <sys/types.h>
#അന്തര്ഭാവ <sys/wait.h>
#അന്തര്ഭാവ <unistd.h>
#അന്തര്ഭാവ <errno.h>
#endif

തരനിർവചനം ഘടന SDL_MessageBoxX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *message;
    SDL_ToolkitControlX11 **buttons;
    സ്ഥിരം SDL_MessageBoxData *messageboxdata;
    പൂർണ്ണസംഖ്യ *buttonID;
} SDL_MessageBoxX11;

സ്ഥിതം ശൂന്യം X11_MessageBoxButtonCallback(SDL_ToolkitControlX11 *control, ശൂന്യം *data)
{
    SDL_MessageBoxX11 *cbdata;

    cbdata = data;
    *cbdata->buttonID = X11Toolkit_GetButtonControlData(control)->buttonID;
    X11Toolkit_SignalWindowClose(cbdata->window);
}

സ്ഥിതം ശൂന്യം X11_PositionMessageBox(SDL_MessageBoxX11 *controls, പൂർണ്ണസംഖ്യ *wp, പൂർണ്ണസംഖ്യ *hp) {
    പൂർണ്ണസംഖ്യ first_വരി_width;
    പൂർണ്ണസംഖ്യ first_വരി_height;
    പൂർണ്ണസംഖ്യ second_വരി_width;
    പൂർണ്ണസംഖ്യ second_വരി_height;
    പൂർണ്ണസംഖ്യ max_button_width;
    പൂർണ്ണസംഖ്യ max_button_height;
    പൂർണ്ണസംഖ്യ window_width;
    പൂർണ്ണസംഖ്യ window_height;
    പൂർണ്ണസംഖ്യ i;
    bool rtl;
    
    /* window size */
    window_width = 1;
    window_height = 1;
    
    /* rtl */
    എങ്കിൽ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_വലത്_TO_ഇടത്) {
        rtl = true;
    } അല്ലെങ്കിൽ എങ്കിൽ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ഇടത്_TO_വലത്) {
        rtl = false;
    } അല്ലെങ്കിൽ {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_വരി_width = first_വരി_height = 0;
    എങ്കിൽ (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_വരി_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        എങ്കിൽ (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } അല്ലെങ്കിൽ {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        എങ്കിൽ (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_വരി_Height(controls->message))/2;
            first_വരി_height = controls->message->rect.y + controls->message->rect.h;
        } അല്ലെങ്കിൽ {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_വരി_height = controls->icon->rect.h;
        }        
    } അല്ലെങ്കിൽ എങ്കിൽ (!controls->icon && controls->message) {
        first_വരി_width = controls->message->rect.w;  
        first_വരി_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } അല്ലെങ്കിൽ എങ്കിൽ (controls->icon && !controls->message) {
        first_വരി_width = controls->icon->rect.w;  
        first_വരി_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_വരി_width = second_വരി_height = 0;
    
    വേണ്ടി (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    എങ്കിൽ (rtl) {
        വേണ്ടി (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            എങ്കിൽ (first_വരി_height) {
                controls->buttons[i]->rect.y = first_വരി_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_വരി_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } അല്ലെങ്കിൽ {
                second_വരി_height = max_button_height;
            }
            
            എങ്കിൽ ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } അല്ലെങ്കിൽ {
        വേണ്ടി (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            എങ്കിൽ (first_വരി_height) {
                controls->buttons[i]->rect.y = first_വരി_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_വരി_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } അല്ലെങ്കിൽ {
                second_വരി_height = max_button_height;
            }
            
            എങ്കിൽ (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    എങ്കിൽ (controls->messageboxdata->numbuttons) {
        എങ്കിൽ (rtl) {
            second_വരി_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } അല്ലെങ്കിൽ {
            second_വരി_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    എങ്കിൽ (second_വരി_width > first_വരി_width) {
        പൂർണ്ണസംഖ്യ pad;
        
        pad = (second_വരി_width - first_വരി_width)/2;
        എങ്കിൽ (controls->message) {
            controls->message->rect.x += pad;
        }
        എങ്കിൽ (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } അല്ലെങ്കിൽ {
        പൂർണ്ണസംഖ്യ pad;
        
        pad = (first_വരി_width - second_വരി_width)/2;
        വേണ്ടി (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_വരി_width, second_വരി_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_വരി_height + second_വരി_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    എങ്കിൽ (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    എങ്കിൽ (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    വേണ്ടി (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
}

സ്ഥിതം ശൂന്യം X11_OnMessageBoxScaleChange(SDL_ToolkitWindowX11 *window, ശൂന്യം *data) {
    SDL_MessageBoxX11 *controls;
    പൂർണ്ണസംഖ്യ w;
    പൂർണ്ണസംഖ്യ h;

    controls = data;
    X11_PositionMessageBox(controls, &w, &h);
    X11Toolkit_ResizeWindow(window, w, h);
}

സ്ഥിതം bool X11_ShowMessageBoxImpl(സ്ഥിരം SDL_MessageBoxData *messageboxdata, പൂർണ്ണസംഖ്യ *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = ശൂന്യ;
    SDL_MessageBoxX11 controls;
    സ്ഥിരം SDL_MessageBoxColor *colorhints;
    പൂർണ്ണസംഖ്യ i;
    പൂർണ്ണസംഖ്യ w;
    പൂർണ്ണസംഖ്യ h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    എങ്കിൽ (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } അല്ലെങ്കിൽ {
        colorhints = ശൂന്യ;
    }

    /* Create window */
    എങ്കിൽ (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#എങ്കിൽ SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, ശൂന്യ, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#അല്ലെങ്കിൽ 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, ശൂന്യ, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#endif
    എങ്കിൽ (!controls.window) {
        തിരികെ false;
    }
    controls.window->cb_data = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, വലുപ്പം(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (അക്ഷരം *)messageboxdata->message);
    വേണ്ടി (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.window, &messageboxdata->buttons[i]);
        X11Toolkit_RegisterCallbackForButtonControl(controls.buttons[i], &controls, X11_MessageBoxButtonCallback);
    }

    /* Positioning */
    X11_PositionMessageBox(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11Toolkit_CreateWindowRes(controls.window, w, h, 0, 0, (അക്ഷരം *)messageboxdata->title);
    X11Toolkit_DoWindowEventLoop(controls.window);
    X11Toolkit_DestroyWindow(controls.window);
    SDL_free(controls.buttons);
    തിരികെ true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(സ്ഥിരം SDL_MessageBoxData *messageboxdata, പൂർണ്ണസംഖ്യ *buttonID)
{
    എങ്കിൽ (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        തിരികെ true;
    }

#എങ്കിൽ SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    പൂർണ്ണസംഖ്യ fds[2];
    പൂർണ്ണസംഖ്യ status = 0;
    bool result = true;

    എങ്കിൽ (pipe(fds) == -1) {
        തിരികെ X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    എങ്കിൽ (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        തിരികെ X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } അല്ലെങ്കിൽ എങ്കിൽ (pid == 0) {                                       // we're the child
        പൂർണ്ണസംഖ്യ exitcode = 0;
        close(fds[0]);
        result = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        എങ്കിൽ (ലിഖ(fds[1], &result, വലുപ്പം(result)) != വലുപ്പം(result)) {
            exitcode = 1;
        } അല്ലെങ്കിൽ എങ്കിൽ (ലിഖ(fds[1], buttonID, വലുപ്പം(*buttonID)) != വലുപ്പം(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } അല്ലെങ്കിൽ {             // we're the parent
        pid_t rc;
        close(fds[1]);
        ചെയ്യുക {
            rc = waitpid(pid, &status, 0);
        } ആകുമ്പോൾ ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        എങ്കിൽ ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            result = SDL_SetError("msgbox child process failed");
        } അല്ലെങ്കിൽ എങ്കിൽ ((പഠ(fds[0], &result, വലുപ്പം(result)) != വലുപ്പം(result)) ||
                   (പഠ(fds[0], buttonID, വലുപ്പം(*buttonID)) != വലുപ്പം(*buttonID))) {
            result = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        തിരികെ result;
    }
#അല്ലെങ്കിൽ
    തിരികെ X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#endif
}
#endif // SDL_VIDEO_DRIVER_X11
