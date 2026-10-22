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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ "../../dialog/unix/SDL_zenitymessagebox.h"
#అన్తర్భావ "SDL_x11messagebox.h"
#అన్తర్భావ "SDL_x11toolkit.h"

#నిర్వచితం_కాకపోతే SDL_FORK_MESSAGEBOX
#నిర్వచించు SDL_FORK_MESSAGEBOX 0
#అయితే_ముగింపు

#ఒకవేళ SDL_FORK_MESSAGEBOX
#అన్తర్భావ <sys/types.h>
#అన్తర్భావ <sys/wait.h>
#అన్తర్భావ <unistd.h>
#అన్తర్భావ <errno.h>
#అయితే_ముగింపు

రకనిర్వచనం నిర్మాణం SDL_సందేశం_Box_X11
{
    SDL_Toolkit_కిటికీ_X11 *కిటికీ;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *సందేశం;
    SDL_ToolkitControlX11 **buttons;
    స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata;
    పూర్ణాంకం *buttonID;
} SDL_సందేశం_Box_X11;

స్థిర శూన్య X11_సందేశం_Box_Button_Callback(SDL_ToolkitControlX11 *control, శూన్య *దత్తాంశం)
{
    SDL_సందేశం_Box_X11 *cbdata;

    cbdata = దత్తాంశం;
    *cbdata->buttonID = X11_Toolkit_Get_Button_Control_దత్తాంశం(control)->buttonID;
    X11_Toolkit_Signal_కిటికీ_Close(cbdata->కిటికీ);
}

స్థిర శూన్య X11_Position_సందేశం_Box(SDL_సందేశం_Box_X11 *controls, పూర్ణాంకం *wp, పూర్ణాంకం *hp) {
    పూర్ణాంకం మొదటి_పంక్తి_వెడల్పు;
    పూర్ణాంకం మొదటి_పంక్తి_ఎత్తు;
    పూర్ణాంకం రెండవ_పంక్తి_వెడల్పు;
    పూర్ణాంకం రెండవ_పంక్తి_ఎత్తు;
    పూర్ణాంకం max_button_వెడల్పు;
    పూర్ణాంకం max_button_ఎత్తు;
    పూర్ణాంకం కిటికీ_వెడల్పు;
    పూర్ణాంకం కిటికీ_ఎత్తు;
    పూర్ణాంకం i;
    bool rtl;
    
    /* window size */
    కిటికీ_వెడల్పు = 1;
    కిటికీ_ఎత్తు = 1;
    
    /* rtl */
    ఒకవేళ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_కుడి_గమ్యం_ఎడమ) {
        rtl = true;
    } లేకపోతే ఒకవేళ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ఎడమ_గమ్యం_కుడి) {
        rtl = false;
    } లేకపోతే {
        rtl = controls->కిటికీ->flip_interface;
    }
    
    /* first line */
    మొదటి_పంక్తి_వెడల్పు = మొదటి_పంక్తి_ఎత్తు = 0;
    ఒకవేళ (controls->icon && controls->సందేశం) {
        controls->icon->rect.y = 0;
        
        మొదటి_పంక్తి_వెడల్పు = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->కిటికీ->iscale + controls->సందేశం->rect.w;  
        
        ఒకవేళ (!controls->కిటికీ->flip_interface) {
            controls->సందేశం->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->కిటికీ->iscale;
            controls->icon->rect.x = 0;
        } లేకపోతే {
            controls->సందేశం->rect.x = 0;    
            controls->icon->rect.x = controls->సందేశం->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->కిటికీ->iscale;
        }
        
        ఒకవేళ (controls->సందేశం->rect.h > controls->icon->rect.h) {
            controls->సందేశం->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_మొదటి_పంక్తి_ఎత్తు(controls->సందేశం))/2;
            మొదటి_పంక్తి_ఎత్తు = controls->సందేశం->rect.y + controls->సందేశం->rect.h;
        } లేకపోతే {
            controls->సందేశం->rect.y = (controls->icon->rect.h - controls->సందేశం->rect.h)/2;
            మొదటి_పంక్తి_ఎత్తు = controls->icon->rect.h;
        }        
    } లేకపోతే ఒకవేళ (!controls->icon && controls->సందేశం) {
        మొదటి_పంక్తి_వెడల్పు = controls->సందేశం->rect.w;  
        మొదటి_పంక్తి_ఎత్తు = controls->సందేశం->rect.h;
        controls->సందేశం->rect.x = 0;
        controls->సందేశం->rect.y = 0;
    } లేకపోతే ఒకవేళ (controls->icon && !controls->సందేశం) {
        మొదటి_పంక్తి_వెడల్పు = controls->icon->rect.w;  
        మొదటి_పంక్తి_ఎత్తు = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_వెడల్పు = 50;
    max_button_ఎత్తు = 0;
    రెండవ_పంక్తి_వెడల్పు = రెండవ_పంక్తి_ఎత్తు = 0;
    
    కొరకు (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_వెడల్పు = SDL_max(max_button_వెడల్పు, controls->buttons[i]->rect.w);
        max_button_ఎత్తు = SDL_max(max_button_ఎత్తు, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    ఒకవేళ (rtl) {
        కొరకు (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_వెడల్పు;
            controls->buttons[i]->rect.h = max_button_ఎత్తు;
            X11_Toolkit_Notify_Control_యొక్క_కొలత_Change(controls->buttons[i]);

            ఒకవేళ (మొదటి_పంక్తి_ఎత్తు) {
                controls->buttons[i]->rect.y = మొదటి_పంక్తి_ఎత్తు + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->కిటికీ->iscale;
                రెండవ_పంక్తి_ఎత్తు = max_button_ఎత్తు + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->కిటికీ->iscale;
            } లేకపోతే {
                రెండవ_పంక్తి_ఎత్తు = max_button_ఎత్తు;
            }
            
            ఒకవేళ ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->కిటికీ->iscale);
            }
        }    
    } లేకపోతే {
        కొరకు (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_వెడల్పు;
            controls->buttons[i]->rect.h = max_button_ఎత్తు;
            X11_Toolkit_Notify_Control_యొక్క_కొలత_Change(controls->buttons[i]);

            ఒకవేళ (మొదటి_పంక్తి_ఎత్తు) {
                controls->buttons[i]->rect.y = మొదటి_పంక్తి_ఎత్తు + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->కిటికీ->iscale;
                రెండవ_పంక్తి_ఎత్తు = max_button_ఎత్తు + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->కిటికీ->iscale;
            } లేకపోతే {
                రెండవ_పంక్తి_ఎత్తు = max_button_ఎత్తు;
            }
            
            ఒకవేళ (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->కిటికీ->iscale);
            }
        }
    }
    
    ఒకవేళ (controls->messageboxdata->numbuttons) {
        ఒకవేళ (rtl) {
            రెండవ_పంక్తి_వెడల్పు = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } లేకపోతే {
            రెండవ_పంక్తి_వెడల్పు = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    ఒకవేళ (రెండవ_పంక్తి_వెడల్పు > మొదటి_పంక్తి_వెడల్పు) {
        పూర్ణాంకం pad;
        
        pad = (రెండవ_పంక్తి_వెడల్పు - మొదటి_పంక్తి_వెడల్పు)/2;
        ఒకవేళ (controls->సందేశం) {
            controls->సందేశం->rect.x += pad;
        }
        ఒకవేళ (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } లేకపోతే {
        పూర్ణాంకం pad;
        
        pad = (మొదటి_పంక్తి_వెడల్పు - రెండవ_పంక్తి_వెడల్పు)/2;
        కొరకు (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    కిటికీ_వెడల్పు = SDL_max(మొదటి_పంక్తి_వెడల్పు, రెండవ_పంక్తి_వెడల్పు) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->కిటికీ->iscale;
    కిటికీ_ఎత్తు = మొదటి_పంక్తి_ఎత్తు + రెండవ_పంక్తి_ఎత్తు + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->కిటికీ->iscale;
    *wp = కిటికీ_వెడల్పు;
    *hp = కిటికీ_ఎత్తు;
    ఒకవేళ (controls->సందేశం) {
        controls->సందేశం->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->కిటికీ->iscale;
        controls->సందేశం->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->కిటికీ->iscale;
    }
    ఒకవేళ (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->కిటికీ->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->కిటికీ->iscale;
    }
    కొరకు (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->కిటికీ->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->కిటికీ->iscale;
    }
}

స్థిర శూన్య X11_On_సందేశం_Box_Scale_Change(SDL_Toolkit_కిటికీ_X11 *కిటికీ, శూన్య *దత్తాంశం) {
    SDL_సందేశం_Box_X11 *controls;
    పూర్ణాంకం w;
    పూర్ణాంకం h;

    controls = దత్తాంశం;
    X11_Position_సందేశం_Box(controls, &w, &h);
    X11_Toolkit_Resize_కిటికీ(కిటికీ, w, h);
}

స్థిర bool X11_Show_సందేశం_Box_Impl(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_కిటికీ *మాతృ_కిటికీ = ఖాళీ;
    SDL_సందేశం_Box_X11 controls;
    స్థిరరాశి SDL_సందేశం_Box_Color *colorhints;
    పూర్ణాంకం i;
    పూర్ణాంకం w;
    పూర్ణాంకం h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    ఒకవేళ (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } లేకపోతే {
        colorhints = ఖాళీ;
    }

    /* Create window */
    ఒకవేళ (messageboxdata->కిటికీ && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        మాతృ_కిటికీ = messageboxdata->కిటికీ;
    }
#ఒకవేళ SDL_FORK_MESSAGEBOX
    controls.కిటికీ = X11_Toolkit_Create_కిటికీ_Struct(మాతృ_కిటికీ, ఖాళీ, SDL_TOOLKIT_కిటికీ_బహుళకం_X11_DIALOG, colorhints, true);
#లేకపోతే 
    controls.కిటికీ = X11_Toolkit_Create_కిటికీ_Struct(మాతృ_కిటికీ, ఖాళీ, SDL_TOOLKIT_కిటికీ_బహుళకం_X11_DIALOG, colorhints, false);
#అయితే_ముగింపు
    ఒకవేళ (!controls.కిటికీ) {
        తిరిగి false;
    }
    controls.కిటికీ->cb_దత్తాంశం = &controls;
    controls.కిటికీ->cb_on_scale_change = X11_On_సందేశం_Box_Scale_Change;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, పరిమాణం(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.కిటికీ, messageboxdata->flags);
    controls.సందేశం = X11Toolkit_CreateLabelControl(controls.కిటికీ, (అక్షరం *)messageboxdata->సందేశం);
    కొరకు (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.కిటికీ, &messageboxdata->buttons[i]);
        X11_Toolkit_రిజిస్టరు_Callback_For_Button_Control(controls.buttons[i], &controls, X11_సందేశం_Box_Button_Callback);
    }

    /* Positioning */
    X11_Position_సందేశం_Box(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11_Toolkit_Create_కిటికీ_Res(controls.కిటికీ, w, h, 0, 0, (అక్షరం *)messageboxdata->title);
    X11_Toolkit_Do_కిటికీ_Event_Loop(controls.కిటికీ);
    X11_Toolkit_Destroy_కిటికీ(controls.కిటికీ);
    SDL_free(controls.buttons);
    తిరిగి true;
}

// Display an x11 message box.
bool X11_Show_సందేశం_Box(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonID)
{
    ఒకవేళ (SDL_Zenity_Show_సందేశం_Box(messageboxdata, buttonID)) {
        తిరిగి true;
    }

#ఒకవేళ SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    పూర్ణాంకం fds[2];
    పూర్ణాంకం స్థితి_2 = 0;
    bool ఫలితం = true;

    ఒకవేళ (pipe(fds) == -1) {
        తిరిగి X11_Show_సందేశం_Box_Impl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    ఒకవేళ (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        తిరిగి X11_Show_సందేశం_Box_Impl(messageboxdata, buttonID); // oh well.
    } లేకపోతే ఒకవేళ (pid == 0) {                                       // we're the child
        పూర్ణాంకం exitcode = 0;
        close(fds[0]);
        ఫలితం = X11_Show_సందేశం_Box_Impl(messageboxdata, buttonID);
        ఒకవేళ (లిఖ(fds[1], &ఫలితం, పరిమాణం(ఫలితం)) != పరిమాణం(ఫలితం)) {
            exitcode = 1;
        } లేకపోతే ఒకవేళ (లిఖ(fds[1], buttonID, పరిమాణం(*buttonID)) != పరిమాణం(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } లేకపోతే {             // we're the parent
        pid_t rc;
        close(fds[1]);
        చేయి {
            rc = waitpid(pid, &స్థితి_2, 0);
        } అయితే ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        ఒకవేళ ((rc == -1) || (!WIFEXITED(స్థితి_2)) || (WEXITSTATUS(స్థితి_2) != 0)) {
            ఫలితం = SDL_సమితి_Error("msgbox child process failed");
        } లేకపోతే ఒకవేళ ((పఠ(fds[0], &ఫలితం, పరిమాణం(ఫలితం)) != పరిమాణం(ఫలితం)) ||
                   (పఠ(fds[0], buttonID, పరిమాణం(*buttonID)) != పరిమాణం(*buttonID))) {
            ఫలితం = SDL_సమితి_Error("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        తిరిగి ఫలితం;
    }
#లేకపోతే
    తిరిగి X11_Show_సందేశం_Box_Impl(messageboxdata, buttonID);
#అయితే_ముగింపు
}
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
