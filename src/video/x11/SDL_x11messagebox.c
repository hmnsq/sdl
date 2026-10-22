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

#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ضمن "../../dialog/unix/SDL_zenitymessagebox.h"
#ضمن "SDL_x11messagebox.h"
#ضمن "SDL_x11toolkit.h"

#ifndef SDL_FORK_MESSAGEBOX
#define SDL_FORK_MESSAGEBOX 0
#endif

#إذا SDL_FORK_MESSAGEBOX
#ضمن <sys/types.h>
#ضمن <sys/wait.h>
#ضمن <unistd.h>
#ضمن <errno.h>
#endif

تعريفنوع بنية SDL_MessageBoxX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *message;
    SDL_ToolkitControlX11 **buttons;
    ثابت SDL_MessageBoxData *messageboxdata;
    صحيح *buttonID;
} SDL_MessageBoxX11;

ساكن فراغ X11_MessageBoxButtonCallback(SDL_ToolkitControlX11 *control, فراغ *data)
{
    SDL_MessageBoxX11 *cbdata;

    cbdata = data;
    *cbdata->buttonID = X11Toolkit_GetButtonControlData(control)->buttonID;
    X11Toolkit_SignalWindowClose(cbdata->window);
}

ساكن فراغ X11_PositionMessageBox(SDL_MessageBoxX11 *controls, صحيح *wp, صحيح *hp) {
    صحيح first_قۇر_width;
    صحيح first_قۇر_height;
    صحيح second_قۇر_width;
    صحيح second_قۇر_height;
    صحيح max_button_width;
    صحيح max_button_height;
    صحيح window_width;
    صحيح window_height;
    صحيح i;
    bool rtl;
    
    /* window size */
    window_width = 1;
    window_height = 1;
    
    /* rtl */
    إذا (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ئوڭ_TO_سول) {
        rtl = true;
    } وإلا إذا (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_سول_TO_ئوڭ) {
        rtl = false;
    } وإلا {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_قۇر_width = first_قۇر_height = 0;
    إذا (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_قۇر_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        إذا (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } وإلا {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        إذا (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_قۇر_Height(controls->message))/2;
            first_قۇر_height = controls->message->rect.y + controls->message->rect.h;
        } وإلا {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_قۇر_height = controls->icon->rect.h;
        }        
    } وإلا إذا (!controls->icon && controls->message) {
        first_قۇر_width = controls->message->rect.w;  
        first_قۇر_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } وإلا إذا (controls->icon && !controls->message) {
        first_قۇر_width = controls->icon->rect.w;  
        first_قۇر_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_قۇر_width = second_قۇر_height = 0;
    
    لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    إذا (rtl) {
        لكل (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            إذا (first_قۇر_height) {
                controls->buttons[i]->rect.y = first_قۇر_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_قۇر_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } وإلا {
                second_قۇر_height = max_button_height;
            }
            
            إذا ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } وإلا {
        لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            إذا (first_قۇر_height) {
                controls->buttons[i]->rect.y = first_قۇر_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_قۇر_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } وإلا {
                second_قۇر_height = max_button_height;
            }
            
            إذا (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    إذا (controls->messageboxdata->numbuttons) {
        إذا (rtl) {
            second_قۇر_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } وإلا {
            second_قۇر_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    إذا (second_قۇر_width > first_قۇر_width) {
        صحيح pad;
        
        pad = (second_قۇر_width - first_قۇر_width)/2;
        إذا (controls->message) {
            controls->message->rect.x += pad;
        }
        إذا (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } وإلا {
        صحيح pad;
        
        pad = (first_قۇر_width - second_قۇر_width)/2;
        لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_قۇر_width, second_قۇر_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_قۇر_height + second_قۇر_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    إذا (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    إذا (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
}

ساكن فراغ X11_OnMessageBoxScaleChange(SDL_ToolkitWindowX11 *window, فراغ *data) {
    SDL_MessageBoxX11 *controls;
    صحيح w;
    صحيح h;

    controls = data;
    X11_PositionMessageBox(controls, &w, &h);
    X11Toolkit_ResizeWindow(window, w, h);
}

ساكن bool X11_ShowMessageBoxImpl(ثابت SDL_MessageBoxData *messageboxdata, صحيح *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = عدم;
    SDL_MessageBoxX11 controls;
    ثابت SDL_MessageBoxColor *colorhints;
    صحيح i;
    صحيح w;
    صحيح h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    إذا (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } وإلا {
        colorhints = عدم;
    }

    /* Create window */
    إذا (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#إذا SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, عدم, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#وإلا 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, عدم, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#endif
    إذا (!controls.window) {
        أرجع false;
    }
    controls.window->cb_data = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, حجم(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (حرف *)messageboxdata->message);
    لكل (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.window, &messageboxdata->buttons[i]);
        X11Toolkit_RegisterCallbackForButtonControl(controls.buttons[i], &controls, X11_MessageBoxButtonCallback);
    }

    /* Positioning */
    X11_PositionMessageBox(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11Toolkit_CreateWindowRes(controls.window, w, h, 0, 0, (حرف *)messageboxdata->title);
    X11Toolkit_DoWindowEventLoop(controls.window);
    X11Toolkit_DestroyWindow(controls.window);
    SDL_free(controls.buttons);
    أرجع true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(ثابت SDL_MessageBoxData *messageboxdata, صحيح *buttonID)
{
    إذا (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        أرجع true;
    }

#إذا SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    صحيح fds[2];
    صحيح status = 0;
    bool result = true;

    إذا (pipe(fds) == -1) {
        أرجع X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    إذا (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        أرجع X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } وإلا إذا (pid == 0) {                                       // we're the child
        صحيح exitcode = 0;
        close(fds[0]);
        result = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        إذا (اكتب(fds[1], &result, حجم(result)) != حجم(result)) {
            exitcode = 1;
        } وإلا إذا (اكتب(fds[1], buttonID, حجم(*buttonID)) != حجم(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } وإلا {             // we're the parent
        pid_t rc;
        close(fds[1]);
        افعل {
            rc = waitpid(pid, &status, 0);
        } طالما ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        إذا ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            result = SDL_SetError("msgbox child process failed");
        } وإلا إذا ((اقرأ(fds[0], &result, حجم(result)) != حجم(result)) ||
                   (اقرأ(fds[0], buttonID, حجم(*buttonID)) != حجم(*buttonID))) {
            result = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        أرجع result;
    }
#وإلا
    أرجع X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#endif
}
#endif // SDL_VIDEO_DRIVER_X11
