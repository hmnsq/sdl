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

#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#include "../../dialog/unix/SDL_zenitymessagebox.h"
#include "SDL_x11messagebox.h"
#include "SDL_x11toolkit.h"

#ifndef SDL_FORK_MESSAGEBOX
#define SDL_FORK_MESSAGEBOX 0
#endif

#ຖ້າ SDL_FORK_MESSAGEBOX
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#endif

typedef sa_nracanaa SDL_MessageBoxX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *message;
    SDL_ToolkitControlX11 **buttons;
    const SDL_MessageBoxData *messageboxdata;
    ຈຳນວນເຕັມ *buttonID;
} SDL_MessageBoxX11;

static void X11_MessageBoxButtonCallback(SDL_ToolkitControlX11 *control, void *data)
{
    SDL_MessageBoxX11 *cbdata;

    cbdata = data;
    *cbdata->buttonID = X11Toolkit_GetButtonControlData(control)->buttonID;
    X11Toolkit_SignalWindowClose(cbdata->window);
}

static void X11_PositionMessageBox(SDL_MessageBoxX11 *controls, ຈຳນວນເຕັມ *wp, ຈຳນວນເຕັມ *hp) {
    ຈຳນວນເຕັມ first_line_width;
    ຈຳນວນເຕັມ first_line_height;
    ຈຳນວນເຕັມ second_line_width;
    ຈຳນວນເຕັມ second_line_height;
    ຈຳນວນເຕັມ max_button_width;
    ຈຳນວນເຕັມ max_button_height;
    ຈຳນວນເຕັມ window_width;
    ຈຳນວນເຕັມ window_height;
    ຈຳນວນເຕັມ i;
    bool rtl;
    
    /* window size */
    window_width = 1;
    window_height = 1;
    
    /* rtl */
    ຖ້າ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT) {
        rtl = true;
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT) {
        rtl = false;
    } ບໍ່ດັ່ງນັ້ນ {
        rtl = controls->window->flip_interface;
    }
    
    /* first line */
    first_line_width = first_line_height = 0;
    ຖ້າ (controls->icon && controls->message) {
        controls->icon->rect.y = 0;
        
        first_line_width = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale + controls->message->rect.w;  
        
        ຖ້າ (!controls->window->flip_interface) {
            controls->message->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
            controls->icon->rect.x = 0;
        } ບໍ່ດັ່ງນັ້ນ {
            controls->message->rect.x = 0;    
            controls->icon->rect.x = controls->message->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->window->iscale;
        }
        
        ຖ້າ (controls->message->rect.h > controls->icon->rect.h) {
            controls->message->rect.y = (controls->icon->rect.h - X11Toolkit_GetLabelControlFirstLineHeight(controls->message))/2;
            first_line_height = controls->message->rect.y + controls->message->rect.h;
        } ບໍ່ດັ່ງນັ້ນ {
            controls->message->rect.y = (controls->icon->rect.h - controls->message->rect.h)/2;
            first_line_height = controls->icon->rect.h;
        }        
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (!controls->icon && controls->message) {
        first_line_width = controls->message->rect.w;  
        first_line_height = controls->message->rect.h;
        controls->message->rect.x = 0;
        controls->message->rect.y = 0;
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (controls->icon && !controls->message) {
        first_line_width = controls->icon->rect.w;  
        first_line_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_width = 50;
    max_button_height = 0;
    second_line_width = second_line_height = 0;
    
    ສຳລັບ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_width = SDL_max(max_button_width, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    ຖ້າ (rtl) {
        ສຳລັບ (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            ຖ້າ (first_line_height) {
                controls->buttons[i]->rect.y = first_line_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_line_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } ບໍ່ດັ່ງນັ້ນ {
                second_line_height = max_button_height;
            }
            
            ຖ້າ ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }    
    } ບໍ່ດັ່ງນັ້ນ {
        ສຳລັບ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_width;
            controls->buttons[i]->rect.h = max_button_height;
            X11Toolkit_NotifyControlOfSizeChange(controls->buttons[i]);

            ຖ້າ (first_line_height) {
                controls->buttons[i]->rect.y = first_line_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
                second_line_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->window->iscale;
            } ບໍ່ດັ່ງນັ້ນ {
                second_line_height = max_button_height;
            }
            
            ຖ້າ (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->window->iscale);
            }
        }
    }
    
    ຖ້າ (controls->messageboxdata->numbuttons) {
        ຖ້າ (rtl) {
            second_line_width = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } ບໍ່ດັ່ງນັ້ນ {
            second_line_width = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    ຖ້າ (second_line_width > first_line_width) {
        ຈຳນວນເຕັມ pad;
        
        pad = (second_line_width - first_line_width)/2;
        ຖ້າ (controls->message) {
            controls->message->rect.x += pad;
        }
        ຖ້າ (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } ບໍ່ດັ່ງນັ້ນ {
        ຈຳນວນເຕັມ pad;
        
        pad = (first_line_width - second_line_width)/2;
        ສຳລັບ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    window_width = SDL_max(first_line_width, second_line_width) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    window_height = first_line_height + second_line_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->window->iscale;
    *wp = window_width;
    *hp = window_height;
    ຖ້າ (controls->message) {
        controls->message->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->message->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    ຖ້າ (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
    ສຳລັບ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->window->iscale;
    }
}

static void X11_OnMessageBoxScaleChange(SDL_ToolkitWindowX11 *window, void *data) {
    SDL_MessageBoxX11 *controls;
    ຈຳນວນເຕັມ w;
    ຈຳນວນເຕັມ h;

    controls = data;
    X11_PositionMessageBox(controls, &w, &h);
    X11Toolkit_ResizeWindow(window, w, h);
}

static bool X11_ShowMessageBoxImpl(const SDL_MessageBoxData *messageboxdata, ຈຳນວນເຕັມ *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_Window *parent_window = NULL;
    SDL_MessageBoxX11 controls;
    const SDL_MessageBoxColor *colorhints;
    ຈຳນວນເຕັມ i;
    ຈຳນວນເຕັມ w;
    ຈຳນວນເຕັມ h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    ຖ້າ (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } ບໍ່ດັ່ງນັ້ນ {
        colorhints = NULL;
    }

    /* Create window */
    ຖ້າ (messageboxdata->window && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_window = messageboxdata->window;
    }
#ຖ້າ SDL_FORK_MESSAGEBOX
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, NULL, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, true);
#ບໍ່ດັ່ງນັ້ນ 
    controls.window = X11Toolkit_CreateWindowStruct(parent_window, NULL, SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG, colorhints, false);
#endif
    ຖ້າ (!controls.window) {
        ສົ່ງຄືນ false;
    }
    controls.window->cb_data = &controls;
    controls.window->cb_on_scale_change = X11_OnMessageBoxScaleChange;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, parimaa_na(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.window, messageboxdata->flags);
    controls.message = X11Toolkit_CreateLabelControl(controls.window, (var_na *)messageboxdata->message);
    ສຳລັບ (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.window, &messageboxdata->buttons[i]);
        X11Toolkit_RegisterCallbackForButtonControl(controls.buttons[i], &controls, X11_MessageBoxButtonCallback);
    }

    /* Positioning */
    X11_PositionMessageBox(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11Toolkit_CreateWindowRes(controls.window, w, h, 0, 0, (var_na *)messageboxdata->title);
    X11Toolkit_DoWindowEventLoop(controls.window);
    X11Toolkit_DestroyWindow(controls.window);
    SDL_free(controls.buttons);
    ສົ່ງຄືນ true;
}

// Display an x11 message box.
bool X11_ShowMessageBox(const SDL_MessageBoxData *messageboxdata, ຈຳນວນເຕັມ *buttonID)
{
    ຖ້າ (SDL_Zenity_ShowMessageBox(messageboxdata, buttonID)) {
        ສົ່ງຄືນ true;
    }

#ຖ້າ SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    ຈຳນວນເຕັມ fds[2];
    ຈຳນວນເຕັມ status = 0;
    bool result = true;

    ຖ້າ (pipe(fds) == -1) {
        ສົ່ງຄືນ X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    ຖ້າ (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        ສົ່ງຄືນ X11_ShowMessageBoxImpl(messageboxdata, buttonID); // oh well.
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (pid == 0) {                                       // we're the child
        ຈຳນວນເຕັມ exitcode = 0;
        close(fds[0]);
        result = X11_ShowMessageBoxImpl(messageboxdata, buttonID);
        ຖ້າ (write(fds[1], &result, parimaa_na(result)) != parimaa_na(result)) {
            exitcode = 1;
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ (write(fds[1], buttonID, parimaa_na(*buttonID)) != parimaa_na(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } ບໍ່ດັ່ງນັ້ນ {             // we're the parent
        pid_t rc;
        close(fds[1]);
        do {
            rc = waitpid(pid, &status, 0);
        } ໃນຂະນະທີ່ ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        ຖ້າ ((rc == -1) || (!WIFEXITED(status)) || (WEXITSTATUS(status) != 0)) {
            result = SDL_SetError("msgbox child process failed");
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ ((read(fds[0], &result, parimaa_na(result)) != parimaa_na(result)) ||
                   (read(fds[0], buttonID, parimaa_na(*buttonID)) != parimaa_na(*buttonID))) {
            result = SDL_SetError("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        ສົ່ງຄືນ result;
    }
#ບໍ່ດັ່ງນັ້ນ
    ສົ່ງຄືນ X11_ShowMessageBoxImpl(messageboxdata, buttonID);
#endif
}
#endif // SDL_VIDEO_DRIVER_X11
