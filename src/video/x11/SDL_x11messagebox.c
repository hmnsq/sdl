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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "../../dialog/unix/SDL_zenitymessagebox.h"
#अन्तर्भाव "SDL_x11messagebox.h"
#अन्तर्भाव "SDL_x11toolkit.h"

#यदि_अपरिभाषितम् SDL_FORK_MESSAGEBOX
#परिभाषय SDL_FORK_MESSAGEBOX 0
#यदि_अन्तः

#यदि SDL_FORK_MESSAGEBOX
#अन्तर्भाव <sys/types.h>
#अन्तर्भाव <sys/wait.h>
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <errno.h>
#यदि_अन्तः

प्रकारनिर्देश संरचना SDL_सन्देशः_Box_X11
{
    SDL_Toolkit_गवाक्षः_X11 *गवाक्षः;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *सन्देशः;
    SDL_ToolkitControlX11 **buttons;
    ध्रुव SDL_सन्देशः_Box_दत्त *messageboxdata;
    पूर्णाङ्क *buttonID;
} SDL_सन्देशः_Box_X11;

स्थिर शून्य X11_सन्देशः_Box_Button_Callback(SDL_ToolkitControlX11 *control, शून्य *दत्त)
{
    SDL_सन्देशः_Box_X11 *cbdata;

    cbdata = दत्त;
    *cbdata->buttonID = X11_Toolkit_Get_Button_Control_दत्त(control)->buttonID;
    X11_Toolkit_Signal_गवाक्षः_Close(cbdata->गवाक्षः);
}

स्थिर शून्य X11_Position_सन्देशः_Box(SDL_सन्देशः_Box_X11 *controls, पूर्णाङ्क *wp, पूर्णाङ्क *hp) {
    पूर्णाङ्क first_पङ्क्तिः_विस्तारः;
    पूर्णाङ्क first_पङ्क्तिः_height;
    पूर्णाङ्क second_पङ्क्तिः_विस्तारः;
    पूर्णाङ्क second_पङ्क्तिः_height;
    पूर्णाङ्क max_button_विस्तारः;
    पूर्णाङ्क max_button_height;
    पूर्णाङ्क गवाक्षः_विस्तारः;
    पूर्णाङ्क गवाक्षः_height;
    पूर्णाङ्क i;
    bool rtl;
    
    /* window size */
    गवाक्षः_विस्तारः = 1;
    गवाक्षः_height = 1;
    
    /* rtl */
    यदि (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_दक्षिणः_गन्तव्यम्_वामः) {
        rtl = true;
    } अन्यथा यदि (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_वामः_गन्तव्यम्_दक्षिणः) {
        rtl = false;
    } अन्यथा {
        rtl = controls->गवाक्षः->flip_interface;
    }
    
    /* first line */
    first_पङ्क्तिः_विस्तारः = first_पङ्क्तिः_height = 0;
    यदि (controls->icon && controls->सन्देशः) {
        controls->icon->rect.y = 0;
        
        first_पङ्क्तिः_विस्तारः = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->गवाक्षः->iscale + controls->सन्देशः->rect.w;  
        
        यदि (!controls->गवाक्षः->flip_interface) {
            controls->सन्देशः->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->गवाक्षः->iscale;
            controls->icon->rect.x = 0;
        } अन्यथा {
            controls->सन्देशः->rect.x = 0;    
            controls->icon->rect.x = controls->सन्देशः->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->गवाक्षः->iscale;
        }
        
        यदि (controls->सन्देशः->rect.h > controls->icon->rect.h) {
            controls->सन्देशः->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_First_पङ्क्तिः_Height(controls->सन्देशः))/2;
            first_पङ्क्तिः_height = controls->सन्देशः->rect.y + controls->सन्देशः->rect.h;
        } अन्यथा {
            controls->सन्देशः->rect.y = (controls->icon->rect.h - controls->सन्देशः->rect.h)/2;
            first_पङ्क्तिः_height = controls->icon->rect.h;
        }        
    } अन्यथा यदि (!controls->icon && controls->सन्देशः) {
        first_पङ्क्तिः_विस्तारः = controls->सन्देशः->rect.w;  
        first_पङ्क्तिः_height = controls->सन्देशः->rect.h;
        controls->सन्देशः->rect.x = 0;
        controls->सन्देशः->rect.y = 0;
    } अन्यथा यदि (controls->icon && !controls->सन्देशः) {
        first_पङ्क्तिः_विस्तारः = controls->icon->rect.w;  
        first_पङ्क्तिः_height = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_विस्तारः = 50;
    max_button_height = 0;
    second_पङ्क्तिः_विस्तारः = second_पङ्क्तिः_height = 0;
    
    प्रति (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_विस्तारः = SDL_max(max_button_विस्तारः, controls->buttons[i]->rect.w);
        max_button_height = SDL_max(max_button_height, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    यदि (rtl) {
        प्रति (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_विस्तारः;
            controls->buttons[i]->rect.h = max_button_height;
            X11_Toolkit_Notify_Control_सम्बन्धि_आकार_Change(controls->buttons[i]);

            यदि (first_पङ्क्तिः_height) {
                controls->buttons[i]->rect.y = first_पङ्क्तिः_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->गवाक्षः->iscale;
                second_पङ्क्तिः_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->गवाक्षः->iscale;
            } अन्यथा {
                second_पङ्क्तिः_height = max_button_height;
            }
            
            यदि ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->गवाक्षः->iscale);
            }
        }    
    } अन्यथा {
        प्रति (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_विस्तारः;
            controls->buttons[i]->rect.h = max_button_height;
            X11_Toolkit_Notify_Control_सम्बन्धि_आकार_Change(controls->buttons[i]);

            यदि (first_पङ्क्तिः_height) {
                controls->buttons[i]->rect.y = first_पङ्क्तिः_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->गवाक्षः->iscale;
                second_पङ्क्तिः_height = max_button_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->गवाक्षः->iscale;
            } अन्यथा {
                second_पङ्क्तिः_height = max_button_height;
            }
            
            यदि (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->गवाक्षः->iscale);
            }
        }
    }
    
    यदि (controls->messageboxdata->numbuttons) {
        यदि (rtl) {
            second_पङ्क्तिः_विस्तारः = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } अन्यथा {
            second_पङ्क्तिः_विस्तारः = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    यदि (second_पङ्क्तिः_विस्तारः > first_पङ्क्तिः_विस्तारः) {
        पूर्णाङ्क pad;
        
        pad = (second_पङ्क्तिः_विस्तारः - first_पङ्क्तिः_विस्तारः)/2;
        यदि (controls->सन्देशः) {
            controls->सन्देशः->rect.x += pad;
        }
        यदि (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } अन्यथा {
        पूर्णाङ्क pad;
        
        pad = (first_पङ्क्तिः_विस्तारः - second_पङ्क्तिः_विस्तारः)/2;
        प्रति (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    गवाक्षः_विस्तारः = SDL_max(first_पङ्क्तिः_विस्तारः, second_पङ्क्तिः_विस्तारः) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->गवाक्षः->iscale;
    गवाक्षः_height = first_पङ्क्तिः_height + second_पङ्क्तिः_height + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->गवाक्षः->iscale;
    *wp = गवाक्षः_विस्तारः;
    *hp = गवाक्षः_height;
    यदि (controls->सन्देशः) {
        controls->सन्देशः->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->गवाक्षः->iscale;
        controls->सन्देशः->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->गवाक्षः->iscale;
    }
    यदि (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->गवाक्षः->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->गवाक्षः->iscale;
    }
    प्रति (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->गवाक्षः->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->गवाक्षः->iscale;
    }
}

स्थिर शून्य X11_On_सन्देशः_Box_Scale_Change(SDL_Toolkit_गवाक्षः_X11 *गवाक्षः, शून्य *दत्त) {
    SDL_सन्देशः_Box_X11 *controls;
    पूर्णाङ्क w;
    पूर्णाङ्क h;

    controls = दत्त;
    X11_Position_सन्देशः_Box(controls, &w, &h);
    X11_Toolkit_Resize_गवाक्षः(गवाक्षः, w, h);
}

स्थिर bool X11_Show_सन्देशः_Box_Impl(ध्रुव SDL_सन्देशः_Box_दत्त *messageboxdata, पूर्णाङ्क *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_गवाक्षः *parent_गवाक्षः = रिक्त;
    SDL_सन्देशः_Box_X11 controls;
    ध्रुव SDL_सन्देशः_Box_Color *colorhints;
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
    यदि (messageboxdata->गवाक्षः && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        parent_गवाक्षः = messageboxdata->गवाक्षः;
    }
#यदि SDL_FORK_MESSAGEBOX
    controls.गवाक्षः = X11_Toolkit_Create_गवाक्षः_Struct(parent_गवाक्षः, रिक्त, SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_DIALOG, colorhints, true);
#अन्यथा 
    controls.गवाक्षः = X11_Toolkit_Create_गवाक्षः_Struct(parent_गवाक्षः, रिक्त, SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_DIALOG, colorhints, false);
#यदि_अन्तः
    यदि (!controls.गवाक्षः) {
        प्रत्यागम false;
    }
    controls.गवाक्षः->cb_दत्त = &controls;
    controls.गवाक्षः->cb_on_scale_change = X11_On_सन्देशः_Box_Scale_Change;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, परिमाण(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.गवाक्षः, messageboxdata->flags);
    controls.सन्देशः = X11Toolkit_CreateLabelControl(controls.गवाक्षः, (वर्ण *)messageboxdata->सन्देशः);
    प्रति (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.गवाक्षः, &messageboxdata->buttons[i]);
        X11_Toolkit_पञ्जिकाकोशः_Callback_For_Button_Control(controls.buttons[i], &controls, X11_सन्देशः_Box_Button_Callback);
    }

    /* Positioning */
    X11_Position_सन्देशः_Box(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11_Toolkit_Create_गवाक्षः_Res(controls.गवाक्षः, w, h, 0, 0, (वर्ण *)messageboxdata->title);
    X11_Toolkit_Do_गवाक्षः_Event_Loop(controls.गवाक्षः);
    X11_Toolkit_Destroy_गवाक्षः(controls.गवाक्षः);
    SDL_free(controls.buttons);
    प्रत्यागम true;
}

// Display an x11 message box.
bool X11_Show_सन्देशः_Box(ध्रुव SDL_सन्देशः_Box_दत्त *messageboxdata, पूर्णाङ्क *buttonID)
{
    यदि (SDL_Zenity_Show_सन्देशः_Box(messageboxdata, buttonID)) {
        प्रत्यागम true;
    }

#यदि SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    पूर्णाङ्क fds[2];
    पूर्णाङ्क स्थितिः = 0;
    bool परिणाम = true;

    यदि (pipe(fds) == -1) {
        प्रत्यागम X11_Show_सन्देशः_Box_Impl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    यदि (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        प्रत्यागम X11_Show_सन्देशः_Box_Impl(messageboxdata, buttonID); // oh well.
    } अन्यथा यदि (pid == 0) {                                       // we're the child
        पूर्णाङ्क exitcode = 0;
        close(fds[0]);
        परिणाम = X11_Show_सन्देशः_Box_Impl(messageboxdata, buttonID);
        यदि (लिख(fds[1], &परिणाम, परिमाण(परिणाम)) != परिमाण(परिणाम)) {
            exitcode = 1;
        } अन्यथा यदि (लिख(fds[1], buttonID, परिमाण(*buttonID)) != परिमाण(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } अन्यथा {             // we're the parent
        pid_t rc;
        close(fds[1]);
        कुरु {
            rc = waitpid(pid, &स्थितिः, 0);
        } यावत् ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        यदि ((rc == -1) || (!WIFEXITED(स्थितिः)) || (WEXITSTATUS(स्थितिः) != 0)) {
            परिणाम = SDL_समुच्चयः_Error("msgbox child process failed");
        } अन्यथा यदि ((पठ(fds[0], &परिणाम, परिमाण(परिणाम)) != परिमाण(परिणाम)) ||
                   (पठ(fds[0], buttonID, परिमाण(*buttonID)) != परिमाण(*buttonID))) {
            परिणाम = SDL_समुच्चयः_Error("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        प्रत्यागम परिणाम;
    }
#अन्यथा
    प्रत्यागम X11_Show_सन्देशः_Box_Impl(messageboxdata, buttonID);
#यदि_अन्तः
}
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
