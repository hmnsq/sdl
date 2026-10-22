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

#यदि SDL_FORK_MESSAGEBOX
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
    अचर SDL_MessageBoxData *messageboxdata;
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
    पूर्णाङ्क first_पङ्क्ति_width;
    पूर्णाङ्क first_पङ्क्ति_height;
    पूर्णाङ्क second_पङ्क्ति_width;
    पूर्णाङ्क second_पङ्क्ति_height;
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
    यदि (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_दायाँ_TO_बायाँ) {
        rtl = true;
    } अन्यथा यदि (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_बायाँ_TO_दायाँ) {
        rtl = false;
    } अन्यथा {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_पङ्क्ति_width = first_पङ्क्ति_height = 0;
    यदि (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_पङ्क्ति_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        यदि (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } अन्यथा {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        यदि (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_पङ्क्ति_Height(controls->message))/2;
            first_पङ्क्ति_height = controls->message->rect.y + controls->message->rect.h;
        } अन्यथा {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_पङ्क्ति_height = controls->icon->rect.h;
        }        
    } अन्यथा यदि (!controls->icon && controls->message) {
        first_पङ्क्ति_width = controls->message->rect.w;  
        first_पङ्क्ति_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } अन्यथा यदि (controls->icon && !controls->message) {
        first_पङ्क्ति_width = controls->icon->rect.w;  
        first_पङ्क्ति_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_पङ्क्ति_width = second_पङ्क्ति_height = 0;
    
    लागि (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    यदि (rtl) {
        लागि (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            यदि (first_पङ्क्ति_height) {
                controls->buttons[i]->rect.y = first_पङ्क्ति_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_पङ्क्ति_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } अन्यथा {
                second_पङ्क्ति_height = max_button_height;
            }
            
            यदि ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } अन्यथा {
        लागि (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            यदि (first_पङ्क्ति_height) {
                controls->buttons[i]->rect.y = first_पङ्क्ति_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_पङ्क्ति_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } अन्यथा {
                second_पङ्क्ति_height = max_button_height;
            }
            
            यदि (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    यदि (controls->messageboxdata->numbuttons) {
        यदि (rtl) {
            second_पङ्क्ति_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } अन्यथा {
            second_पङ्क्ति_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    यदि (second_पङ्क्ति_width > first_पङ्क्ति_width) {
        पूर्णाङ्क pad;
        
        pad = (second_पङ्क्ति_width - first_पङ्क्ति_width)/2;
        यदि (controls->message) {
            controls->message->rect.x += pad;
        }
        यदि (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } अन्यथा {
        पूर्णाङ्क pad;
        
        pad = (first_पङ्क्ति_width - second_पङ्क्ति_width)/2;
        लागि (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_पङ्क्ति_width, second_पङ्क्ति_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_पङ्क्ति_height + second_पङ्क्ति_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    यदि (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    यदि (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    लागि (i = 0; i < controls->messageboxdata->numbuttons; i++) {
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

स्थिर bool X11_ShowMessageBoxImpl(अचर SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = रिक्त;
    SDL_MessageBoxX11 controls;
    अचर SDL_MessageBoxColor *colorhints;
    पूर्णाङ्क i;
    पूर्णाङ्क w;
    पूर्णाङ्क h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    यदि (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } अन्यथा {
        colorhints = रिक्त;
    }

    /* Create window */
    यदि (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#यदि SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, रिक्त, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#अन्यथा 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, रिक्त, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#endif
    यदि (!controls.window) {
        फर्काऊ false;
    }
    controls.window->cb_data = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, परिमाण(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (वर्ण *)messageboxdata->message);
    लागि (i = 0; i < messageboxdata->numbuttons; i++) {
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
    फर्काऊ true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(अचर SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID)
{
    यदि (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        फर्काऊ true;
    }

#यदि SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    पूर्णाङ्क fds[2];
    पूर्णाङ्क status = 0;
    bool result = true;

    यदि (pipe(fds) == -1) {
        फर्काऊ X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = विभाजन();
    यदि (pid == -1) { // failed
        बंद(fds[0]);
        बंद(fds[1]);
        फर्काऊ X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } अन्यथा यदि (pid == 0) {                                       // we're the child
        पूर्णाङ्क exitcode = 0;
        बंद(fds[0]);
        result = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        यदि (लिख(fds[1], &result, परिमाण(result)) != परिमाण(result)) {
            exitcode = 1;
        } अन्यथा यदि (लिख(fds[1], buttonID, परिमाण(*buttonID)) != परिमाण(*buttonID)) {
            exitcode = 1;
        }
        बंद(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } अन्यथा {             // we're the parent
        pid_t rc;
        बंद(fds[1]);
        गर {
            rc = waitpid(pid, &status, 0);
        } जबसम्म ((rc == -1) && (त्रुटि_सं == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        यदि ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            result = SDL_SetError("msgbox child process failed");
        } अन्यथा यदि ((पठ(fds[0], &result, परिमाण(result)) != परिमाण(result)) ||
                   (पठ(fds[0], buttonID, परिमाण(*buttonID)) != परिमाण(*buttonID))) {
            result = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        बंद(fds[0]);

        फर्काऊ result;
    }
#अन्यथा
    फर्काऊ X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#endif
}
#endif // SDL_VIDEO_DRIVER_X11
