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

#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#અન્તર્ભાવ "../../dialog/unix/SDL_zenitymessagebox.h"
#અન્તર્ભાવ "SDL_x11messagebox.h"
#અન્તર્ભાવ "SDL_x11toolkit.h"

#ifndef SDL_FORK_MESSAGEBOX
#define SDL_FORK_MESSAGEBOX 0
#endif

#જો SDL_FORK_MESSAGEBOX
#અન્તર્ભાવ <sys/types.h>
#અન્તર્ભાવ <sys/wait.h>
#અન્તર્ભાવ <unistd.h>
#અન્તર્ભાવ <errno.h>
#endif

પ્રકારવ્યાખ્યા સંરચના SDL_MessageBoxX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *message;
    SDL_ToolkitControlX11 **buttons;
    અચલ SDL_MessageBoxData *messageboxdata;
    પૂર્ણાંક *buttonID;
} SDL_MessageBoxX11;

સ્થિર શૂન્ય X11_MessageBoxButtonCallback(SDL_ToolkitControlX11 *control, શૂન્ય *data)
{
    SDL_MessageBoxX11 *cbdata;

    cbdata = data;
    *cbdata->buttonID = X11Toolkit_GetButtonControlData(control)->buttonID;
    X11Toolkit_SignalWindowClose(cbdata->window);
}

સ્થિર શૂન્ય X11_PositionMessageBox(SDL_MessageBoxX11 *controls, પૂર્ણાંક *wp, પૂર્ણાંક *hp) {
    પૂર્ણાંક first_લીટી_width;
    પૂર્ણાંક first_લીટી_height;
    પૂર્ણાંક second_લીટી_width;
    પૂર્ણાંક second_લીટી_height;
    પૂર્ણાંક max_button_width;
    પૂર્ણાંક max_button_height;
    પૂર્ણાંક window_width;
    પૂર્ણાંક window_height;
    પૂર્ણાંક i;
    bool rtl;
    
    /* window size */
    window_width = 1;
    window_height = 1;
    
    /* rtl */
    જો (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_જમણું_TO_ડાબું) {
        rtl = true;
    } નહીંતર જો (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ડાબું_TO_જમણું) {
        rtl = false;
    } નહીંતર {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_લીટી_width = first_લીટી_height = 0;
    જો (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_લીટી_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        જો (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } નહીંતર {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        જો (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_લીટી_Height(controls->message))/2;
            first_લીટી_height = controls->message->rect.y + controls->message->rect.h;
        } નહીંતર {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_લીટી_height = controls->icon->rect.h;
        }        
    } નહીંતર જો (!controls->icon && controls->message) {
        first_લીટી_width = controls->message->rect.w;  
        first_લીટી_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } નહીંતર જો (controls->icon && !controls->message) {
        first_લીટી_width = controls->icon->rect.w;  
        first_લીટી_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_લીટી_width = second_લીટી_height = 0;
    
    માટે (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    જો (rtl) {
        માટે (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            જો (first_લીટી_height) {
                controls->buttons[i]->rect.y = first_લીટી_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_લીટી_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } નહીંતર {
                second_લીટી_height = max_button_height;
            }
            
            જો ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } નહીંતર {
        માટે (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            જો (first_લીટી_height) {
                controls->buttons[i]->rect.y = first_લીટી_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_લીટી_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } નહીંતર {
                second_લીટી_height = max_button_height;
            }
            
            જો (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    જો (controls->messageboxdata->numbuttons) {
        જો (rtl) {
            second_લીટી_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } નહીંતર {
            second_લીટી_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    જો (second_લીટી_width > first_લીટી_width) {
        પૂર્ણાંક pad;
        
        pad = (second_લીટી_width - first_લીટી_width)/2;
        જો (controls->message) {
            controls->message->rect.x += pad;
        }
        જો (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } નહીંતર {
        પૂર્ણાંક pad;
        
        pad = (first_લીટી_width - second_લીટી_width)/2;
        માટે (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_લીટી_width, second_લીટી_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_લીટી_height + second_લીટી_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    જો (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    જો (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    માટે (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
}

સ્થિર શૂન્ય X11_OnMessageBoxScaleChange(SDL_ToolkitWindowX11 *window, શૂન્ય *data) {
    SDL_MessageBoxX11 *controls;
    પૂર્ણાંક w;
    પૂર્ણાંક h;

    controls = data;
    X11_PositionMessageBox(controls, &w, &h);
    X11Toolkit_ResizeWindow(window, w, h);
}

સ્થિર bool X11_ShowMessageBoxImpl(અચલ SDL_MessageBoxData *messageboxdata, પૂર્ણાંક *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = ખાલી;
    SDL_MessageBoxX11 controls;
    અચલ SDL_MessageBoxColor *colorhints;
    પૂર્ણાંક i;
    પૂર્ણાંક w;
    પૂર્ણાંક h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    જો (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } નહીંતર {
        colorhints = ખાલી;
    }

    /* Create window */
    જો (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#જો SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, ખાલી, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#નહીંતર 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, ખાલી, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#endif
    જો (!controls.window) {
        પાછા false;
    }
    controls.window->cb_data = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, કદ(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (અક્ષર *)messageboxdata->message);
    માટે (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.window, &messageboxdata->buttons[i]);
        X11Toolkit_RegisterCallbackForButtonControl(controls.buttons[i], &controls, X11_MessageBoxButtonCallback);
    }

    /* Positioning */
    X11_PositionMessageBox(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11Toolkit_CreateWindowRes(controls.window, w, h, 0, 0, (અક્ષર *)messageboxdata->title);
    X11Toolkit_DoWindowEventLoop(controls.window);
    X11Toolkit_DestroyWindow(controls.window);
    SDL_free(controls.buttons);
    પાછા true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(અચલ SDL_MessageBoxData *messageboxdata, પૂર્ણાંક *buttonID)
{
    જો (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        પાછા true;
    }

#જો SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    પૂર્ણાંક fds[2];
    પૂર્ણાંક status = 0;
    bool result = true;

    જો (pipe(fds) == -1) {
        પાછા X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    જો (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        પાછા X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } નહીંતર જો (pid == 0) {                                       // we're the child
        પૂર્ણાંક exitcode = 0;
        close(fds[0]);
        result = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        જો (લિખ(fds[1], &result, કદ(result)) != કદ(result)) {
            exitcode = 1;
        } નહીંતર જો (લિખ(fds[1], buttonID, કદ(*buttonID)) != કદ(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } નહીંતર {             // we're the parent
        pid_t rc;
        close(fds[1]);
        કરો {
            rc = waitpid(pid, &status, 0);
        } જ્યારે ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        જો ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            result = SDL_SetError("msgbox child process failed");
        } નહીંતર જો ((પઠ(fds[0], &result, કદ(result)) != કદ(result)) ||
                   (પઠ(fds[0], buttonID, કદ(*buttonID)) != કદ(*buttonID))) {
            result = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        પાછા result;
    }
#નહીંતર
    પાછા X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#endif
}
#endif // SDL_VIDEO_DRIVER_X11
