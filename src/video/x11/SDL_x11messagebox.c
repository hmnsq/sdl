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

#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#অন্তর্ভাৱ "../../dialog/unix/SDL_zenitymessagebox.h"
#অন্তর্ভাৱ "SDL_x11messagebox.h"
#অন্তর্ভাৱ "SDL_x11toolkit.h"

#ifndef SDL_FORK_MESSAGEBOX
#define SDL_FORK_MESSAGEBOX 0
#endif

#যদি SDL_FORK_MESSAGEBOX
#অন্তর্ভাৱ <sys/types.h>
#অন্তর্ভাৱ <sys/wait.h>
#অন্তর্ভাৱ <unistd.h>
#অন্তর্ভাৱ <errno.h>
#endif

প্রকারনির্দেশ সংরচনা SDL_MessageBoxX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *message;
    SDL_ToolkitControlX11 **buttons;
    ধ্রুৱ SDL_MessageBoxData *messageboxdata;
    পূর্ণাঙ্ক *buttonID;
} SDL_MessageBoxX11;

স্থির শূন্য X11_MessageBoxButtonCallback(SDL_ToolkitControlX11 *control, শূন্য *data)
{
    SDL_MessageBoxX11 *cbdata;

    cbdata = data;
    *cbdata->buttonID = X11Toolkit_GetButtonControlData(control)->buttonID;
    X11Toolkit_SignalWindowClose(cbdata->window);
}

স্থির শূন্য X11_PositionMessageBox(SDL_MessageBoxX11 *controls, পূর্ণাঙ্ক *wp, পূর্ণাঙ্ক *hp) {
    পূর্ণাঙ্ক first_সাৰি_width;
    পূর্ণাঙ্ক first_সাৰি_height;
    পূর্ণাঙ্ক second_সাৰি_width;
    পূর্ণাঙ্ক second_সাৰি_height;
    পূর্ণাঙ্ক max_button_width;
    পূর্ণাঙ্ক max_button_height;
    পূর্ণাঙ্ক window_width;
    পূর্ণাঙ্ক window_height;
    পূর্ণাঙ্ক i;
    bool rtl;
    
    /* window size */
    window_width = 1;
    window_height = 1;
    
    /* rtl */
    যদি (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ডান_TO_বাম) {
        rtl = true;
    } অন্যথা যদি (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_বাম_TO_ডান) {
        rtl = false;
    } অন্যথা {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_সাৰি_width = first_সাৰি_height = 0;
    যদি (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_সাৰি_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        যদি (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } অন্যথা {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        যদি (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_সাৰি_Height(controls->message))/2;
            first_সাৰি_height = controls->message->rect.y + controls->message->rect.h;
        } অন্যথা {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_সাৰি_height = controls->icon->rect.h;
        }        
    } অন্যথা যদি (!controls->icon && controls->message) {
        first_সাৰি_width = controls->message->rect.w;  
        first_সাৰি_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } অন্যথা যদি (controls->icon && !controls->message) {
        first_সাৰি_width = controls->icon->rect.w;  
        first_সাৰি_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_সাৰি_width = second_সাৰি_height = 0;
    
    বাবে (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    যদি (rtl) {
        বাবে (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            যদি (first_সাৰি_height) {
                controls->buttons[i]->rect.y = first_সাৰি_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_সাৰি_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } অন্যথা {
                second_সাৰি_height = max_button_height;
            }
            
            যদি ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } অন্যথা {
        বাবে (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            যদি (first_সাৰি_height) {
                controls->buttons[i]->rect.y = first_সাৰি_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_সাৰি_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } অন্যথা {
                second_সাৰি_height = max_button_height;
            }
            
            যদি (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    যদি (controls->messageboxdata->numbuttons) {
        যদি (rtl) {
            second_সাৰি_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } অন্যথা {
            second_সাৰি_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    যদি (second_সাৰি_width > first_সাৰি_width) {
        পূর্ণাঙ্ক pad;
        
        pad = (second_সাৰি_width - first_সাৰি_width)/2;
        যদি (controls->message) {
            controls->message->rect.x += pad;
        }
        যদি (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } অন্যথা {
        পূর্ণাঙ্ক pad;
        
        pad = (first_সাৰি_width - second_সাৰি_width)/2;
        বাবে (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_সাৰি_width, second_সাৰি_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_সাৰি_height + second_সাৰি_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    যদি (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    যদি (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    বাবে (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
}

স্থির শূন্য X11_OnMessageBoxScaleChange(SDL_ToolkitWindowX11 *window, শূন্য *data) {
    SDL_MessageBoxX11 *controls;
    পূর্ণাঙ্ক w;
    পূর্ণাঙ্ক h;

    controls = data;
    X11_PositionMessageBox(controls, &w, &h);
    X11Toolkit_ResizeWindow(window, w, h);
}

স্থির bool X11_ShowMessageBoxImpl(ধ্রুৱ SDL_MessageBoxData *messageboxdata, পূর্ণাঙ্ক *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = রিক্ত;
    SDL_MessageBoxX11 controls;
    ধ্রুৱ SDL_MessageBoxColor *colorhints;
    পূর্ণাঙ্ক i;
    পূর্ণাঙ্ক w;
    পূর্ণাঙ্ক h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    যদি (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } অন্যথা {
        colorhints = রিক্ত;
    }

    /* Create window */
    যদি (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#যদি SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, রিক্ত, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#অন্যথা 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, রিক্ত, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#endif
    যদি (!controls.window) {
        ঘূৰাই false;
    }
    controls.window->cb_data = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, পরিমাণ(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (ৱর্ণ *)messageboxdata->message);
    বাবে (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.window, &messageboxdata->buttons[i]);
        X11Toolkit_RegisterCallbackForButtonControl(controls.buttons[i], &controls, X11_MessageBoxButtonCallback);
    }

    /* Positioning */
    X11_PositionMessageBox(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11Toolkit_CreateWindowRes(controls.window, w, h, 0, 0, (ৱর্ণ *)messageboxdata->title);
    X11Toolkit_DoWindowEventLoop(controls.window);
    X11Toolkit_DestroyWindow(controls.window);
    SDL_free(controls.buttons);
    ঘূৰাই true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(ধ্রুৱ SDL_MessageBoxData *messageboxdata, পূর্ণাঙ্ক *buttonID)
{
    যদি (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        ঘূৰাই true;
    }

#যদি SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    পূর্ণাঙ্ক fds[2];
    পূর্ণাঙ্ক status = 0;
    bool result = true;

    যদি (pipe(fds) == -1) {
        ঘূৰাই X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    যদি (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        ঘূৰাই X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } অন্যথা যদি (pid == 0) {                                       // we're the child
        পূর্ণাঙ্ক exitcode = 0;
        close(fds[0]);
        result = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        যদি (লিখ(fds[1], &result, পরিমাণ(result)) != পরিমাণ(result)) {
            exitcode = 1;
        } অন্যথা যদি (লিখ(fds[1], buttonID, পরিমাণ(*buttonID)) != পরিমাণ(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } অন্যথা {             // we're the parent
        pid_t rc;
        close(fds[1]);
        কৰা {
            rc = waitpid(pid, &status, 0);
        } যেতিয়ালৈ ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        যদি ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            result = SDL_SetError("msgbox child process failed");
        } অন্যথা যদি ((পঠ(fds[0], &result, পরিমাণ(result)) != পরিমাণ(result)) ||
                   (পঠ(fds[0], buttonID, পরিমাণ(*buttonID)) != পরিমাণ(*buttonID))) {
            result = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        ঘূৰাই result;
    }
#অন্যথা
    ঘূৰাই X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#endif
}
#endif // SDL_VIDEO_DRIVER_X11
