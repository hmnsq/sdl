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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ଅନ୍ତର୍ଭାଵ "../../dialog/unix/SDL_zenitymessagebox.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11messagebox.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11toolkit.h"

#ifndef SDL_FORK_MESSAGEBOX
#define SDL_FORK_MESSAGEBOX 0
#endif

#ଯଦି SDL_FORK_MESSAGEBOX
#ଅନ୍ତର୍ଭାଵ <sys/types.h>
#ଅନ୍ତର୍ଭାଵ <sys/wait.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#ଅନ୍ତର୍ଭାଵ <errno.h>
#endif

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_MessageBoxX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *message;
    SDL_ToolkitControlX11 **buttons;
    ଅଚଳ SDL_MessageBoxData *messageboxdata;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା *buttonID;
} SDL_MessageBoxX11;

ସ୍ଥିର ଶୂନ୍ୟ X11_MessageBoxButtonCallback(SDL_ToolkitControlX11 *control, ଶୂନ୍ୟ *data)
{
    SDL_MessageBoxX11 *cbdata;

    cbdata = data;
    *cbdata->buttonID = X11Toolkit_GetButtonControlData(control)->buttonID;
    X11Toolkit_SignalWindowClose(cbdata->window);
}

ସ୍ଥିର ଶୂନ୍ୟ X11_PositionMessageBox(SDL_MessageBoxX11 *controls, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *wp, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *hp) {
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା first_ଧାଡ଼ି_width;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା first_ଧାଡ଼ି_height;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା second_ଧାଡ଼ି_width;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା second_ଧାଡ଼ି_height;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_button_width;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_button_height;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା window_width;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା window_height;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    bool rtl;
    
    /* window size */
    window_width = 1;
    window_height = 1;
    
    /* rtl */
    ଯଦି (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ଡାହାଣ_TO_ବାମ) {
        rtl = true;
    } ଅନ୍ୟଥା ଯଦି (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ବାମ_TO_ଡାହାଣ) {
        rtl = false;
    } ଅନ୍ୟଥା {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_ଧାଡ଼ି_width = first_ଧାଡ଼ି_height = 0;
    ଯଦି (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_ଧାଡ଼ି_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        ଯଦି (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } ଅନ୍ୟଥା {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        ଯଦି (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_ଧାଡ଼ି_Height(controls->message))/2;
            first_ଧାଡ଼ି_height = controls->message->rect.y + controls->message->rect.h;
        } ଅନ୍ୟଥା {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_ଧାଡ଼ି_height = controls->icon->rect.h;
        }        
    } ଅନ୍ୟଥା ଯଦି (!controls->icon && controls->message) {
        first_ଧାଡ଼ି_width = controls->message->rect.w;  
        first_ଧାଡ଼ି_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } ଅନ୍ୟଥା ଯଦି (controls->icon && !controls->message) {
        first_ଧାଡ଼ି_width = controls->icon->rect.w;  
        first_ଧାଡ଼ି_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_ଧାଡ଼ି_width = second_ଧାଡ଼ି_height = 0;
    
    ପାଇଁ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    ଯଦି (rtl) {
        ପାଇଁ (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            ଯଦି (first_ଧାଡ଼ି_height) {
                controls->buttons[i]->rect.y = first_ଧାଡ଼ି_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_ଧାଡ଼ି_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } ଅନ୍ୟଥା {
                second_ଧାଡ଼ି_height = max_button_height;
            }
            
            ଯଦି ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } ଅନ୍ୟଥା {
        ପାଇଁ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            ଯଦି (first_ଧାଡ଼ି_height) {
                controls->buttons[i]->rect.y = first_ଧାଡ଼ି_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_ଧାଡ଼ି_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } ଅନ୍ୟଥା {
                second_ଧାଡ଼ି_height = max_button_height;
            }
            
            ଯଦି (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    ଯଦି (controls->messageboxdata->numbuttons) {
        ଯଦି (rtl) {
            second_ଧାଡ଼ି_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } ଅନ୍ୟଥା {
            second_ଧାଡ଼ି_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    ଯଦି (second_ଧାଡ଼ି_width > first_ଧାଡ଼ି_width) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା pad;
        
        pad = (second_ଧାଡ଼ି_width - first_ଧାଡ଼ି_width)/2;
        ଯଦି (controls->message) {
            controls->message->rect.x += pad;
        }
        ଯଦି (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } ଅନ୍ୟଥା {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା pad;
        
        pad = (first_ଧାଡ଼ି_width - second_ଧାଡ଼ି_width)/2;
        ପାଇଁ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_ଧାଡ଼ି_width, second_ଧାଡ଼ି_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_ଧାଡ଼ି_height + second_ଧାଡ଼ି_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    ଯଦି (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    ଯଦି (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    ପାଇଁ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ X11_OnMessageBoxScaleChange(SDL_ToolkitWindowX11 *window, ଶୂନ୍ୟ *data) {
    SDL_MessageBoxX11 *controls;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h;

    controls = data;
    X11_PositionMessageBox(controls, &w, &h);
    X11Toolkit_ResizeWindow(window, w, h);
}

ସ୍ଥିର bool X11_ShowMessageBoxImpl(ଅଚଳ SDL_MessageBoxData *messageboxdata, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = ଖାଲି;
    SDL_MessageBoxX11 controls;
    ଅଚଳ SDL_MessageBoxColor *colorhints;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    ଯଦି (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } ଅନ୍ୟଥା {
        colorhints = ଖାଲି;
    }

    /* Create window */
    ଯଦି (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#ଯଦି SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, ଖାଲି, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#ଅନ୍ୟଥା 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, ଖାଲି, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#endif
    ଯଦି (!controls.window) {
        ଫେରନ୍ତୁ false;
    }
    controls.window->cb_data = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, ଆକାର(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (ଅକ୍ଷର *)messageboxdata->message);
    ପାଇଁ (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.window, &messageboxdata->buttons[i]);
        X11Toolkit_RegisterCallbackForButtonControl(controls.buttons[i], &controls, X11_MessageBoxButtonCallback);
    }

    /* Positioning */
    X11_PositionMessageBox(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11Toolkit_CreateWindowRes(controls.window, w, h, 0, 0, (ଅକ୍ଷର *)messageboxdata->title);
    X11Toolkit_DoWindowEventLoop(controls.window);
    X11Toolkit_DestroyWindow(controls.window);
    SDL_free(controls.buttons);
    ଫେରନ୍ତୁ true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(ଅଚଳ SDL_MessageBoxData *messageboxdata, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *buttonID)
{
    ଯଦି (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        ଫେରନ୍ତୁ true;
    }

#ଯଦି SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା fds[2];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା status = 0;
    bool result = true;

    ଯଦି (pipe(fds) == -1) {
        ଫେରନ୍ତୁ X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    ଯଦି (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        ଫେରନ୍ତୁ X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } ଅନ୍ୟଥା ଯଦି (pid == 0) {                                       // we're the child
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା exitcode = 0;
        close(fds[0]);
        result = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        ଯଦି (ଲିଖ(fds[1], &result, ଆକାର(result)) != ଆକାର(result)) {
            exitcode = 1;
        } ଅନ୍ୟଥା ଯଦି (ଲିଖ(fds[1], buttonID, ଆକାର(*buttonID)) != ଆକାର(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } ଅନ୍ୟଥା {             // we're the parent
        pid_t rc;
        close(fds[1]);
        କର {
            rc = waitpid(pid, &status, 0);
        } ଯେତେବେଳେ ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        ଯଦି ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            result = SDL_SetError("msgbox child process failed");
        } ଅନ୍ୟଥା ଯଦି ((ପଠ(fds[0], &result, ଆକାର(result)) != ଆକାର(result)) ||
                   (ପଠ(fds[0], buttonID, ଆକାର(*buttonID)) != ଆକାର(*buttonID))) {
            result = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        ଫେରନ୍ତୁ result;
    }
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#endif
}
#endif // SDL_VIDEO_DRIVER_X11
