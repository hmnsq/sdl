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

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11

#ضمن "../../dialog/unix/SDL_zenitymessagebox.h"
#ضمن "SDL_x11messagebox.h"
#ضمن "SDL_x11toolkit.h"

#که_نه_تعریف_شوی SDL_FORK_MESSAGEBOX
#تعریف_کړه SDL_FORK_MESSAGEBOX 0
#د_که_پای

#إذا SDL_FORK_MESSAGEBOX
#ضمن <sys/types.h>
#ضمن <sys/wait.h>
#ضمن <unistd.h>
#ضمن <errno.h>
#د_که_پای

تعريفنوع بنية SDL_پیغام_Box_X11
{
    SDL_Toolkit_کړکۍ_X11 *کړکۍ;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *پیغام;
    SDL_ToolkitControlX11 **buttons;
    ثابت SDL_پیغام_Box_معلومات *messageboxdata;
    صحيح *buttonID;
} SDL_پیغام_Box_X11;

ساكن فراغ X11_پیغام_Box_Button_Callback(SDL_ToolkitControlX11 *control, فراغ *معلومات)
{
    SDL_پیغام_Box_X11 *cbdata;

    cbdata = معلومات;
    *cbdata->buttonID = X11_Toolkit_Get_Button_Control_معلومات(control)->buttonID;
    X11_Toolkit_Signal_کړکۍ_Close(cbdata->کړکۍ);
}

ساكن فراغ X11_Position_پیغام_Box(SDL_پیغام_Box_X11 *controls, صحيح *wp, صحيح *hp) {
    صحيح لومړی_کرښه_پلنوالی;
    صحيح لومړی_کرښه_لوړوالی;
    صحيح دوهم_کرښه_پلنوالی;
    صحيح دوهم_کرښه_لوړوالی;
    صحيح max_button_پلنوالی;
    صحيح max_button_لوړوالی;
    صحيح کړکۍ_پلنوالی;
    صحيح کړکۍ_لوړوالی;
    صحيح i;
    bool rtl;
    
    /* window size */
    کړکۍ_پلنوالی = 1;
    کړکۍ_لوړوالی = 1;
    
    /* rtl */
    إذا (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ښی_منزل_کیڼ) {
        rtl = true;
    } وإلا إذا (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_کیڼ_منزل_ښی) {
        rtl = false;
    } وإلا {
        rtl = controls->کړکۍ->flip_interface;
    }
    
    /* first line */
    لومړی_کرښه_پلنوالی = لومړی_کرښه_لوړوالی = 0;
    إذا (controls->icon && controls->پیغام) {
        controls->icon->rect.y = 0;
        
        لومړی_کرښه_پلنوالی = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کړکۍ->iscale + controls->پیغام->rect.w;  
        
        إذا (!controls->کړکۍ->flip_interface) {
            controls->پیغام->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->کړکۍ->iscale;
            controls->icon->rect.x = 0;
        } وإلا {
            controls->پیغام->rect.x = 0;    
            controls->icon->rect.x = controls->پیغام->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->کړکۍ->iscale;
        }
        
        إذا (controls->پیغام->rect.h > controls->icon->rect.h) {
            controls->پیغام->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_لومړی_کرښه_لوړوالی(controls->پیغام))/2;
            لومړی_کرښه_لوړوالی = controls->پیغام->rect.y + controls->پیغام->rect.h;
        } وإلا {
            controls->پیغام->rect.y = (controls->icon->rect.h - controls->پیغام->rect.h)/2;
            لومړی_کرښه_لوړوالی = controls->icon->rect.h;
        }        
    } وإلا إذا (!controls->icon && controls->پیغام) {
        لومړی_کرښه_پلنوالی = controls->پیغام->rect.w;  
        لومړی_کرښه_لوړوالی = controls->پیغام->rect.h;
        controls->پیغام->rect.x = 0;
        controls->پیغام->rect.y = 0;
    } وإلا إذا (controls->icon && !controls->پیغام) {
        لومړی_کرښه_پلنوالی = controls->icon->rect.w;  
        لومړی_کرښه_لوړوالی = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_پلنوالی = 50;
    max_button_لوړوالی = 0;
    دوهم_کرښه_پلنوالی = دوهم_کرښه_لوړوالی = 0;
    
    لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_پلنوالی = SDL_max(max_button_پلنوالی, controls->buttons[i]->rect.w);
        max_button_لوړوالی = SDL_max(max_button_لوړوالی, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    إذا (rtl) {
        لكل (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_پلنوالی;
            controls->buttons[i]->rect.h = max_button_لوړوالی;
            X11_Toolkit_Notify_Control_د_اندازه_Change(controls->buttons[i]);

            إذا (لومړی_کرښه_لوړوالی) {
                controls->buttons[i]->rect.y = لومړی_کرښه_لوړوالی + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->کړکۍ->iscale;
                دوهم_کرښه_لوړوالی = max_button_لوړوالی + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->کړکۍ->iscale;
            } وإلا {
                دوهم_کرښه_لوړوالی = max_button_لوړوالی;
            }
            
            إذا ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->کړکۍ->iscale);
            }
        }    
    } وإلا {
        لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_پلنوالی;
            controls->buttons[i]->rect.h = max_button_لوړوالی;
            X11_Toolkit_Notify_Control_د_اندازه_Change(controls->buttons[i]);

            إذا (لومړی_کرښه_لوړوالی) {
                controls->buttons[i]->rect.y = لومړی_کرښه_لوړوالی + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->کړکۍ->iscale;
                دوهم_کرښه_لوړوالی = max_button_لوړوالی + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->کړکۍ->iscale;
            } وإلا {
                دوهم_کرښه_لوړوالی = max_button_لوړوالی;
            }
            
            إذا (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->کړکۍ->iscale);
            }
        }
    }
    
    إذا (controls->messageboxdata->numbuttons) {
        إذا (rtl) {
            دوهم_کرښه_پلنوالی = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } وإلا {
            دوهم_کرښه_پلنوالی = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    إذا (دوهم_کرښه_پلنوالی > لومړی_کرښه_پلنوالی) {
        صحيح pad;
        
        pad = (دوهم_کرښه_پلنوالی - لومړی_کرښه_پلنوالی)/2;
        إذا (controls->پیغام) {
            controls->پیغام->rect.x += pad;
        }
        إذا (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } وإلا {
        صحيح pad;
        
        pad = (لومړی_کرښه_پلنوالی - دوهم_کرښه_پلنوالی)/2;
        لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    کړکۍ_پلنوالی = SDL_max(لومړی_کرښه_پلنوالی, دوهم_کرښه_پلنوالی) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->کړکۍ->iscale;
    کړکۍ_لوړوالی = لومړی_کرښه_لوړوالی + دوهم_کرښه_لوړوالی + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->کړکۍ->iscale;
    *wp = کړکۍ_پلنوالی;
    *hp = کړکۍ_لوړوالی;
    إذا (controls->پیغام) {
        controls->پیغام->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کړکۍ->iscale;
        controls->پیغام->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کړکۍ->iscale;
    }
    إذا (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کړکۍ->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کړکۍ->iscale;
    }
    لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کړکۍ->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کړکۍ->iscale;
    }
}

ساكن فراغ X11_On_پیغام_Box_Scale_Change(SDL_Toolkit_کړکۍ_X11 *کړکۍ, فراغ *معلومات) {
    SDL_پیغام_Box_X11 *controls;
    صحيح w;
    صحيح h;

    controls = معلومات;
    X11_Position_پیغام_Box(controls, &w, &h);
    X11_Toolkit_Resize_کړکۍ(کړکۍ, w, h);
}

ساكن bool X11_Show_پیغام_Box_Impl(ثابت SDL_پیغام_Box_معلومات *messageboxdata, صحيح *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_کړکۍ *پلار_کړکۍ = عدم;
    SDL_پیغام_Box_X11 controls;
    ثابت SDL_پیغام_Box_Color *colorhints;
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
    إذا (messageboxdata->کړکۍ && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        پلار_کړکۍ = messageboxdata->کړکۍ;
    }
#إذا SDL_FORK_MESSAGEBOX
    controls.کړکۍ = X11_Toolkit_Create_کړکۍ_Struct(پلار_کړکۍ, عدم, SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_DIALOG, colorhints, true);
#وإلا 
    controls.کړکۍ = X11_Toolkit_Create_کړکۍ_Struct(پلار_کړکۍ, عدم, SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_DIALOG, colorhints, false);
#د_که_پای
    إذا (!controls.کړکۍ) {
        أرجع false;
    }
    controls.کړکۍ->cb_معلومات = &controls;
    controls.کړکۍ->cb_on_scale_change = X11_On_پیغام_Box_Scale_Change;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, حجم(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.کړکۍ, messageboxdata->flags);
    controls.پیغام = X11Toolkit_CreateLabelControl(controls.کړکۍ, (حرف *)messageboxdata->پیغام);
    لكل (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.کړکۍ, &messageboxdata->buttons[i]);
        X11_Toolkit_ثبتوونکی_Callback_For_Button_Control(controls.buttons[i], &controls, X11_پیغام_Box_Button_Callback);
    }

    /* Positioning */
    X11_Position_پیغام_Box(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11_Toolkit_Create_کړکۍ_Res(controls.کړکۍ, w, h, 0, 0, (حرف *)messageboxdata->title);
    X11_Toolkit_Do_کړکۍ_Event_Loop(controls.کړکۍ);
    X11_Toolkit_Destroy_کړکۍ(controls.کړکۍ);
    SDL_free(controls.buttons);
    أرجع true;
}

// Display an x11 message box.
bool X11_Show_پیغام_Box(ثابت SDL_پیغام_Box_معلومات *messageboxdata, صحيح *buttonID)
{
    إذا (SDL_Zenity_Show_پیغام_Box(messageboxdata, buttonID)) {
        أرجع true;
    }

#إذا SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    صحيح fds[2];
    صحيح حالت = 0;
    bool پایله = true;

    إذا (pipe(fds) == -1) {
        أرجع X11_Show_پیغام_Box_Impl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    إذا (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        أرجع X11_Show_پیغام_Box_Impl(messageboxdata, buttonID); // oh well.
    } وإلا إذا (pid == 0) {                                       // we're the child
        صحيح exitcode = 0;
        close(fds[0]);
        پایله = X11_Show_پیغام_Box_Impl(messageboxdata, buttonID);
        إذا (اكتب(fds[1], &پایله, حجم(پایله)) != حجم(پایله)) {
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
            rc = waitpid(pid, &حالت, 0);
        } طالما ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        إذا ((rc == -1) || (!WIFEXITED(حالت)) || (WEXITSTATUS(حالت) != 0)) {
            پایله = SDL_سېټ_Error("msgbox child process failed");
        } وإلا إذا ((اقرأ(fds[0], &پایله, حجم(پایله)) != حجم(پایله)) ||
                   (اقرأ(fds[0], buttonID, حجم(*buttonID)) != حجم(*buttonID))) {
            پایله = SDL_سېټ_Error("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        أرجع پایله;
    }
#وإلا
    أرجع X11_Show_پیغام_Box_Impl(messageboxdata, buttonID);
#د_که_پای
}
#د_که_پای // SDL_VIDEO_DRIVER_X11
