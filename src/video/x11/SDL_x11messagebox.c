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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#समावेश "../../dialog/unix/SDL_zenitymessagebox.h"
#समावेश "SDL_x11messagebox.h"
#समावेश "SDL_x11toolkit.h"

#अगर_अघोषित SDL_FORK_MESSAGEBOX
#घोषणा SDL_FORK_MESSAGEBOX 0
#पूर्ण_अगर

#अगर SDL_FORK_MESSAGEBOX
#समावेश <sys/types.h>
#समावेश <sys/wait.h>
#समावेश <unistd.h>
#समावेश <errno.h>
#पूर्ण_अगर

प्रकार काष्ठा SDL_MessageBoxX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *message;
    SDL_ToolkitControlX11 **buttons;
    स्थिर SDL_Message_Box_तथ्य *messageboxdata;
    पूर्णांक *buttonID;
} SDL_MessageBoxX11;

अटल व्योम X11_MessageBoxButtonCallback(SDL_ToolkitControlX11 *control, व्योम *तथ्य)
{
    SDL_MessageBoxX11 *cbdata;

    cbdata = तथ्य;
    *cbdata->buttonID = X11_Toolkit_Get_Button_Control_तथ्य(control)->buttonID;
    X11Toolkit_SignalWindowClose(cbdata->window);
}

अटल व्योम X11_PositionMessageBox(SDL_MessageBoxX11 *controls, पूर्णांक *wp, पूर्णांक *hp) {
    पूर्णांक first_पंक्ति_width;
    पूर्णांक first_पंक्ति_height;
    पूर्णांक second_पंक्ति_width;
    पूर्णांक second_पंक्ति_height;
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
    अगर (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_दायाँ_TO_बायाँ) {
        rtl = true;
    } अन्यथा अगर (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_बायाँ_TO_दायाँ) {
        rtl = false;
    } अन्यथा {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_पंक्ति_width = first_पंक्ति_height = 0;
    अगर (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_पंक्ति_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        अगर (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } अन्यथा {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        अगर (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_पंक्ति_Height(controls->message))/2;
            first_पंक्ति_height = controls->message->rect.y + controls->message->rect.h;
        } अन्यथा {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_पंक्ति_height = controls->icon->rect.h;
        }        
    } अन्यथा अगर (!controls->icon && controls->message) {
        first_पंक्ति_width = controls->message->rect.w;  
        first_पंक्ति_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } अन्यथा अगर (controls->icon && !controls->message) {
        first_पंक्ति_width = controls->icon->rect.w;  
        first_पंक्ति_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_पंक्ति_width = second_पंक्ति_height = 0;
    
    क्रम (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    अगर (rtl) {
        क्रम (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11_Toolkit_Notify_Control_Of_आकार_Change(controls->buttons[i]);

            अगर (first_पंक्ति_height) {
                controls->buttons[i]->rect.y = first_पंक्ति_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_पंक्ति_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } अन्यथा {
                second_पंक्ति_height = max_button_height;
            }
            
            अगर ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } अन्यथा {
        क्रम (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11_Toolkit_Notify_Control_Of_आकार_Change(controls->buttons[i]);

            अगर (first_पंक्ति_height) {
                controls->buttons[i]->rect.y = first_पंक्ति_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_पंक्ति_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } अन्यथा {
                second_पंक्ति_height = max_button_height;
            }
            
            अगर (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    अगर (controls->messageboxdata->numbuttons) {
        अगर (rtl) {
            second_पंक्ति_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } अन्यथा {
            second_पंक्ति_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    अगर (second_पंक्ति_width > first_पंक्ति_width) {
        पूर्णांक pad;
        
        pad = (second_पंक्ति_width - first_पंक्ति_width)/2;
        अगर (controls->message) {
            controls->message->rect.x += pad;
        }
        अगर (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } अन्यथा {
        पूर्णांक pad;
        
        pad = (first_पंक्ति_width - second_पंक्ति_width)/2;
        क्रम (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_पंक्ति_width, second_पंक्ति_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_पंक्ति_height + second_पंक्ति_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    अगर (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    अगर (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    क्रम (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
}

अटल व्योम X11_OnMessageBoxScaleChange(SDL_ToolkitWindowX11 *window, व्योम *तथ्य) {
    SDL_MessageBoxX11 *controls;
    पूर्णांक w;
    पूर्णांक h;

    controls = तथ्य;
    X11_PositionMessageBox(controls, &w, &h);
    X11Toolkit_ResizeWindow(window, w, h);
}

अटल bool X11_ShowMessageBoxImpl(स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = शून्य;
    SDL_MessageBoxX11 controls;
    स्थिर SDL_MessageBoxColor *colorhints;
    पूर्णांक i;
    पूर्णांक w;
    पूर्णांक h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    अगर (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } अन्यथा {
        colorhints = शून्य;
    }

    /* Create window */
    अगर (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#अगर SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, शून्य, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#अन्यथा 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, शून्य, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#पूर्ण_अगर
    अगर (!controls.window) {
        वापस false;
    }
    controls.window->cb_तथ्य = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, माप(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (अक्षर *)messageboxdata->message);
    क्रम (i = 0; i < messageboxdata->numbuttons; i++) {
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
    वापस true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonID)
{
    अगर (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        वापस true;
    }

#अगर SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    पूर्णांक fds[2];
    पूर्णांक status = 0;
    bool परिणाम = true;

    अगर (pipe(fds) == -1) {
        वापस X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = विभाजन();
    अगर (pid == -1) { // failed
        बंद(fds[0]);
        बंद(fds[1]);
        वापस X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } अन्यथा अगर (pid == 0) {                                       // we're the child
        पूर्णांक exitcode = 0;
        बंद(fds[0]);
        परिणाम = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        अगर (ग_लिखो(fds[1], &परिणाम, माप(परिणाम)) != माप(परिणाम)) {
            exitcode = 1;
        } अन्यथा अगर (ग_लिखो(fds[1], buttonID, माप(*buttonID)) != माप(*buttonID)) {
            exitcode = 1;
        }
        बंद(fds[1]);
        _निकास(exitcode); // don't run atexit() stuff, static destructors, etc.
    } अन्यथा {             // we're the parent
        pid_t rc;
        बंद(fds[1]);
        करो {
            rc = waitpid(pid, &status, 0);
        } जबतक ((rc == -1) && (त्रुटि_सं == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        अगर ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            परिणाम = SDL_SetError("msgbox child process failed");
        } अन्यथा अगर ((पढ़ो(fds[0], &परिणाम, माप(परिणाम)) != माप(परिणाम)) ||
                   (पढ़ो(fds[0], buttonID, माप(*buttonID)) != माप(*buttonID))) {
            परिणाम = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        बंद(fds[0]);

        वापस परिणाम;
    }
#अन्यथा
    वापस X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#पूर्ण_अगर
}
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11
