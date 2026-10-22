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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#ضمن "../../dialog/unix/SDL_zenitymessagebox.h"
#ضمن "SDL_x11messagebox.h"
#ضمن "SDL_x11toolkit.h"

#جے_بنا_تعریف SDL_FORK_MESSAGEBOX
#تعریف_کرو SDL_FORK_MESSAGEBOX 0
#جے_انت

#إذا SDL_FORK_MESSAGEBOX
#ضمن <sys/types.h>
#ضمن <sys/wait.h>
#ضمن <unistd.h>
#ضمن <errno.h>
#جے_انت

تعريفنوع بنية SDL_سنیہا_Box_X11
{
    SDL_Toolkit_کھڑکی_X11 *کھڑکی;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *سنیہا;
    SDL_ToolkitControlX11 **buttons;
    ثابت SDL_سنیہا_Box_انکڑے *messageboxdata;
    صحيح *buttonID;
} SDL_سنیہا_Box_X11;

ساكن فراغ X11_سنیہا_Box_Button_Callback(SDL_ToolkitControlX11 *control, فراغ *انکڑے)
{
    SDL_سنیہا_Box_X11 *cbdata;

    cbdata = انکڑے;
    *cbdata->buttonID = X11_Toolkit_Get_Button_Control_انکڑے(control)->buttonID;
    X11_Toolkit_Signal_کھڑکی_Close(cbdata->کھڑکی);
}

ساكن فراغ X11_Position_سنیہا_Box(SDL_سنیہا_Box_X11 *controls, صحيح *wp, صحيح *hp) {
    صحيح پہلا_سطر_چوڑائی;
    صحيح پہلا_سطر_اچائی;
    صحيح دوجا_سطر_چوڑائی;
    صحيح دوجا_سطر_اچائی;
    صحيح max_button_چوڑائی;
    صحيح max_button_اچائی;
    صحيح کھڑکی_چوڑائی;
    صحيح کھڑکی_اچائی;
    صحيح i;
    bool rtl;
    
    /* window size */
    کھڑکی_چوڑائی = 1;
    کھڑکی_اچائی = 1;
    
    /* rtl */
    إذا (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_دایاں_منزل_بایاں) {
        rtl = true;
    } وإلا إذا (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_بایاں_منزل_دایاں) {
        rtl = false;
    } وإلا {
        rtl = controls->کھڑکی->flip_interface;
    }
    
    /* first line */
    پہلا_سطر_چوڑائی = پہلا_سطر_اچائی = 0;
    إذا (controls->icon && controls->سنیہا) {
        controls->icon->rect.y = 0;
        
        پہلا_سطر_چوڑائی = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale + controls->سنیہا->rect.w;  
        
        إذا (!controls->کھڑکی->flip_interface) {
            controls->سنیہا->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->کھڑکی->iscale;
            controls->icon->rect.x = 0;
        } وإلا {
            controls->سنیہا->rect.x = 0;    
            controls->icon->rect.x = controls->سنیہا->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->کھڑکی->iscale;
        }
        
        إذا (controls->سنیہا->rect.h > controls->icon->rect.h) {
            controls->سنیہا->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_پہلا_سطر_اچائی(controls->سنیہا))/2;
            پہلا_سطر_اچائی = controls->سنیہا->rect.y + controls->سنیہا->rect.h;
        } وإلا {
            controls->سنیہا->rect.y = (controls->icon->rect.h - controls->سنیہا->rect.h)/2;
            پہلا_سطر_اچائی = controls->icon->rect.h;
        }        
    } وإلا إذا (!controls->icon && controls->سنیہا) {
        پہلا_سطر_چوڑائی = controls->سنیہا->rect.w;  
        پہلا_سطر_اچائی = controls->سنیہا->rect.h;
        controls->سنیہا->rect.x = 0;
        controls->سنیہا->rect.y = 0;
    } وإلا إذا (controls->icon && !controls->سنیہا) {
        پہلا_سطر_چوڑائی = controls->icon->rect.w;  
        پہلا_سطر_اچائی = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_چوڑائی = 50;
    max_button_اچائی = 0;
    دوجا_سطر_چوڑائی = دوجا_سطر_اچائی = 0;
    
    لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_چوڑائی = SDL_max(max_button_چوڑائی, controls->buttons[i]->rect.w);
        max_button_اچائی = SDL_max(max_button_اچائی, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    إذا (rtl) {
        لكل (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_چوڑائی;
            controls->buttons[i]->rect.h = max_button_اچائی;
            X11_Toolkit_Notify_Control_دا_ناپ_Change(controls->buttons[i]);

            إذا (پہلا_سطر_اچائی) {
                controls->buttons[i]->rect.y = پہلا_سطر_اچائی + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->کھڑکی->iscale;
                دوجا_سطر_اچائی = max_button_اچائی + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->کھڑکی->iscale;
            } وإلا {
                دوجا_سطر_اچائی = max_button_اچائی;
            }
            
            إذا ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->کھڑکی->iscale);
            }
        }    
    } وإلا {
        لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_چوڑائی;
            controls->buttons[i]->rect.h = max_button_اچائی;
            X11_Toolkit_Notify_Control_دا_ناپ_Change(controls->buttons[i]);

            إذا (پہلا_سطر_اچائی) {
                controls->buttons[i]->rect.y = پہلا_سطر_اچائی + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->کھڑکی->iscale;
                دوجا_سطر_اچائی = max_button_اچائی + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->کھڑکی->iscale;
            } وإلا {
                دوجا_سطر_اچائی = max_button_اچائی;
            }
            
            إذا (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->کھڑکی->iscale);
            }
        }
    }
    
    إذا (controls->messageboxdata->numbuttons) {
        إذا (rtl) {
            دوجا_سطر_چوڑائی = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } وإلا {
            دوجا_سطر_چوڑائی = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    إذا (دوجا_سطر_چوڑائی > پہلا_سطر_چوڑائی) {
        صحيح pad;
        
        pad = (دوجا_سطر_چوڑائی - پہلا_سطر_چوڑائی)/2;
        إذا (controls->سنیہا) {
            controls->سنیہا->rect.x += pad;
        }
        إذا (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } وإلا {
        صحيح pad;
        
        pad = (پہلا_سطر_چوڑائی - دوجا_سطر_چوڑائی)/2;
        لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    کھڑکی_چوڑائی = SDL_max(پہلا_سطر_چوڑائی, دوجا_سطر_چوڑائی) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->کھڑکی->iscale;
    کھڑکی_اچائی = پہلا_سطر_اچائی + دوجا_سطر_اچائی + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->کھڑکی->iscale;
    *wp = کھڑکی_چوڑائی;
    *hp = کھڑکی_اچائی;
    إذا (controls->سنیہا) {
        controls->سنیہا->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale;
        controls->سنیہا->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale;
    }
    إذا (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale;
    }
    لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale;
    }
}

ساكن فراغ X11_On_سنیہا_Box_Scale_Change(SDL_Toolkit_کھڑکی_X11 *کھڑکی, فراغ *انکڑے) {
    SDL_سنیہا_Box_X11 *controls;
    صحيح w;
    صحيح h;

    controls = انکڑے;
    X11_Position_سنیہا_Box(controls, &w, &h);
    X11_Toolkit_Resize_کھڑکی(کھڑکی, w, h);
}

ساكن bool X11_Show_سنیہا_Box_Impl(ثابت SDL_سنیہا_Box_انکڑے *messageboxdata, صحيح *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_کھڑکی *ماپا_کھڑکی = عدم;
    SDL_سنیہا_Box_X11 controls;
    ثابت SDL_سنیہا_Box_Color *colorhints;
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
    إذا (messageboxdata->کھڑکی && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        ماپا_کھڑکی = messageboxdata->کھڑکی;
    }
#إذا SDL_FORK_MESSAGEBOX
    controls.کھڑکی = X11_Toolkit_Create_کھڑکی_Struct(ماپا_کھڑکی, عدم, SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG, colorhints, true);
#وإلا 
    controls.کھڑکی = X11_Toolkit_Create_کھڑکی_Struct(ماپا_کھڑکی, عدم, SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG, colorhints, false);
#جے_انت
    إذا (!controls.کھڑکی) {
        أرجع false;
    }
    controls.کھڑکی->cb_انکڑے = &controls;
    controls.کھڑکی->cb_on_scale_change = X11_On_سنیہا_Box_Scale_Change;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, حجم(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.کھڑکی, messageboxdata->flags);
    controls.سنیہا = X11Toolkit_CreateLabelControl(controls.کھڑکی, (حرف *)messageboxdata->سنیہا);
    لكل (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.کھڑکی, &messageboxdata->buttons[i]);
        X11_Toolkit_رجسٹر_Callback_For_Button_Control(controls.buttons[i], &controls, X11_سنیہا_Box_Button_Callback);
    }

    /* Positioning */
    X11_Position_سنیہا_Box(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11_Toolkit_Create_کھڑکی_Res(controls.کھڑکی, w, h, 0, 0, (حرف *)messageboxdata->title);
    X11_Toolkit_Do_کھڑکی_Event_Loop(controls.کھڑکی);
    X11_Toolkit_Destroy_کھڑکی(controls.کھڑکی);
    SDL_free(controls.buttons);
    أرجع true;
}

// Display an x11 message box.
bool X11_Show_سنیہا_Box(ثابت SDL_سنیہا_Box_انکڑے *messageboxdata, صحيح *buttonID)
{
    إذا (SDL_Zenity_Show_سنیہا_Box(messageboxdata, buttonID)) {
        أرجع true;
    }

#إذا SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    صحيح fds[2];
    صحيح حالت = 0;
    bool نتیجہ = true;

    إذا (pipe(fds) == -1) {
        أرجع X11_Show_سنیہا_Box_Impl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    إذا (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        أرجع X11_Show_سنیہا_Box_Impl(messageboxdata, buttonID); // oh well.
    } وإلا إذا (pid == 0) {                                       // we're the child
        صحيح exitcode = 0;
        close(fds[0]);
        نتیجہ = X11_Show_سنیہا_Box_Impl(messageboxdata, buttonID);
        إذا (اكتب(fds[1], &نتیجہ, حجم(نتیجہ)) != حجم(نتیجہ)) {
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
            نتیجہ = SDL_سیٹ_Error("msgbox child process failed");
        } وإلا إذا ((اقرأ(fds[0], &نتیجہ, حجم(نتیجہ)) != حجم(نتیجہ)) ||
                   (اقرأ(fds[0], buttonID, حجم(*buttonID)) != حجم(*buttonID))) {
            نتیجہ = SDL_سیٹ_Error("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        أرجع نتیجہ;
    }
#وإلا
    أرجع X11_Show_سنیہا_Box_Impl(messageboxdata, buttonID);
#جے_انت
}
#جے_انت // SDL_VIDEO_DRIVER_X11
