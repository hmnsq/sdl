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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#شامل "../../dialog/unix/SDL_zenitymessagebox.h"
#شامل "SDL_x11messagebox.h"
#شامل "SDL_x11toolkit.h"

#اگر_غیر_تعریف_شدہ SDL_FORK_MESSAGEBOX
#تعریف_کرو SDL_FORK_MESSAGEBOX 0
#اگر_ختم

#اگر SDL_FORK_MESSAGEBOX
#شامل <sys/types.h>
#شامل <sys/wait.h>
#شامل <unistd.h>
#شامل <errno.h>
#اگر_ختم

قسمتعریف ساخت SDL_پیغام_Box_X11
{
    SDL_Toolkit_کھڑکی_X11 *کھڑکی;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *پیغام;
    SDL_ToolkitControlX11 **buttons;
    ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata;
    صحیح *buttonID;
} SDL_پیغام_Box_X11;

ساکن خالی X11_پیغام_Box_Button_Callback(SDL_ToolkitControlX11 *control, خالی *ڈیٹا)
{
    SDL_پیغام_Box_X11 *cbdata;

    cbdata = ڈیٹا;
    *cbdata->buttonID = X11_Toolkit_Get_Button_Control_ڈیٹا(control)->buttonID;
    X11_Toolkit_Signal_کھڑکی_Close(cbdata->کھڑکی);
}

ساکن خالی X11_Position_پیغام_Box(SDL_پیغام_Box_X11 *controls, صحیح *wp, صحیح *hp) {
    صحیح پہلا_سطر_چوڑائی;
    صحیح پہلا_سطر_اونچائی;
    صحیح دوسرا_سطر_چوڑائی;
    صحیح دوسرا_سطر_اونچائی;
    صحیح max_button_چوڑائی;
    صحیح max_button_اونچائی;
    صحیح کھڑکی_چوڑائی;
    صحیح کھڑکی_اونچائی;
    صحیح i;
    bool rtl;
    
    /* window size */
    کھڑکی_چوڑائی = 1;
    کھڑکی_اونچائی = 1;
    
    /* rtl */
    اگر (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_دایاں_مقصد_بایاں) {
        rtl = true;
    } ورنہ اگر (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_بایاں_مقصد_دایاں) {
        rtl = false;
    } ورنہ {
        rtl = controls->کھڑکی->flip_interface;
    }
    
    /* first line */
    پہلا_سطر_چوڑائی = پہلا_سطر_اونچائی = 0;
    اگر (controls->icon && controls->پیغام) {
        controls->icon->rect.y = 0;
        
        پہلا_سطر_چوڑائی = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale + controls->پیغام->rect.w;  
        
        اگر (!controls->کھڑکی->flip_interface) {
            controls->پیغام->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->کھڑکی->iscale;
            controls->icon->rect.x = 0;
        } ورنہ {
            controls->پیغام->rect.x = 0;    
            controls->icon->rect.x = controls->پیغام->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->کھڑکی->iscale;
        }
        
        اگر (controls->پیغام->rect.h > controls->icon->rect.h) {
            controls->پیغام->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_پہلا_سطر_اونچائی(controls->پیغام))/2;
            پہلا_سطر_اونچائی = controls->پیغام->rect.y + controls->پیغام->rect.h;
        } ورنہ {
            controls->پیغام->rect.y = (controls->icon->rect.h - controls->پیغام->rect.h)/2;
            پہلا_سطر_اونچائی = controls->icon->rect.h;
        }        
    } ورنہ اگر (!controls->icon && controls->پیغام) {
        پہلا_سطر_چوڑائی = controls->پیغام->rect.w;  
        پہلا_سطر_اونچائی = controls->پیغام->rect.h;
        controls->پیغام->rect.x = 0;
        controls->پیغام->rect.y = 0;
    } ورنہ اگر (controls->icon && !controls->پیغام) {
        پہلا_سطر_چوڑائی = controls->icon->rect.w;  
        پہلا_سطر_اونچائی = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_چوڑائی = 50;
    max_button_اونچائی = 0;
    دوسرا_سطر_چوڑائی = دوسرا_سطر_اونچائی = 0;
    
    برائے (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_چوڑائی = SDL_max(max_button_چوڑائی, controls->buttons[i]->rect.w);
        max_button_اونچائی = SDL_max(max_button_اونچائی, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    اگر (rtl) {
        برائے (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_چوڑائی;
            controls->buttons[i]->rect.h = max_button_اونچائی;
            X11_Toolkit_Notify_Control_کا_سائز_Change(controls->buttons[i]);

            اگر (پہلا_سطر_اونچائی) {
                controls->buttons[i]->rect.y = پہلا_سطر_اونچائی + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->کھڑکی->iscale;
                دوسرا_سطر_اونچائی = max_button_اونچائی + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->کھڑکی->iscale;
            } ورنہ {
                دوسرا_سطر_اونچائی = max_button_اونچائی;
            }
            
            اگر ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->کھڑکی->iscale);
            }
        }    
    } ورنہ {
        برائے (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_چوڑائی;
            controls->buttons[i]->rect.h = max_button_اونچائی;
            X11_Toolkit_Notify_Control_کا_سائز_Change(controls->buttons[i]);

            اگر (پہلا_سطر_اونچائی) {
                controls->buttons[i]->rect.y = پہلا_سطر_اونچائی + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->کھڑکی->iscale;
                دوسرا_سطر_اونچائی = max_button_اونچائی + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->کھڑکی->iscale;
            } ورنہ {
                دوسرا_سطر_اونچائی = max_button_اونچائی;
            }
            
            اگر (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->کھڑکی->iscale);
            }
        }
    }
    
    اگر (controls->messageboxdata->numbuttons) {
        اگر (rtl) {
            دوسرا_سطر_چوڑائی = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } ورنہ {
            دوسرا_سطر_چوڑائی = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    اگر (دوسرا_سطر_چوڑائی > پہلا_سطر_چوڑائی) {
        صحیح pad;
        
        pad = (دوسرا_سطر_چوڑائی - پہلا_سطر_چوڑائی)/2;
        اگر (controls->پیغام) {
            controls->پیغام->rect.x += pad;
        }
        اگر (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } ورنہ {
        صحیح pad;
        
        pad = (پہلا_سطر_چوڑائی - دوسرا_سطر_چوڑائی)/2;
        برائے (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    کھڑکی_چوڑائی = SDL_max(پہلا_سطر_چوڑائی, دوسرا_سطر_چوڑائی) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->کھڑکی->iscale;
    کھڑکی_اونچائی = پہلا_سطر_اونچائی + دوسرا_سطر_اونچائی + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->کھڑکی->iscale;
    *wp = کھڑکی_چوڑائی;
    *hp = کھڑکی_اونچائی;
    اگر (controls->پیغام) {
        controls->پیغام->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale;
        controls->پیغام->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale;
    }
    اگر (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale;
    }
    برائے (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->کھڑکی->iscale;
    }
}

ساکن خالی X11_On_پیغام_Box_Scale_Change(SDL_Toolkit_کھڑکی_X11 *کھڑکی, خالی *ڈیٹا) {
    SDL_پیغام_Box_X11 *controls;
    صحیح w;
    صحیح h;

    controls = ڈیٹا;
    X11_Position_پیغام_Box(controls, &w, &h);
    X11_Toolkit_Resize_کھڑکی(کھڑکی, w, h);
}

ساکن bool X11_Show_پیغام_Box_Impl(ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_کھڑکی *والد_کھڑکی = تہی;
    SDL_پیغام_Box_X11 controls;
    ثابت SDL_پیغام_Box_Color *colorhints;
    صحیح i;
    صحیح w;
    صحیح h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    اگر (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } ورنہ {
        colorhints = تہی;
    }

    /* Create window */
    اگر (messageboxdata->کھڑکی && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        والد_کھڑکی = messageboxdata->کھڑکی;
    }
#اگر SDL_FORK_MESSAGEBOX
    controls.کھڑکی = X11_Toolkit_Create_کھڑکی_Struct(والد_کھڑکی, تہی, SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG, colorhints, true);
#ورنہ 
    controls.کھڑکی = X11_Toolkit_Create_کھڑکی_Struct(والد_کھڑکی, تہی, SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG, colorhints, false);
#اگر_ختم
    اگر (!controls.کھڑکی) {
        واپس false;
    }
    controls.کھڑکی->cb_ڈیٹا = &controls;
    controls.کھڑکی->cb_on_scale_change = X11_On_پیغام_Box_Scale_Change;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, حجم(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.کھڑکی, messageboxdata->flags);
    controls.پیغام = X11Toolkit_CreateLabelControl(controls.کھڑکی, (حرف *)messageboxdata->پیغام);
    برائے (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.کھڑکی, &messageboxdata->buttons[i]);
        X11_Toolkit_رجسٹر_Callback_For_Button_Control(controls.buttons[i], &controls, X11_پیغام_Box_Button_Callback);
    }

    /* Positioning */
    X11_Position_پیغام_Box(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11_Toolkit_Create_کھڑکی_Res(controls.کھڑکی, w, h, 0, 0, (حرف *)messageboxdata->title);
    X11_Toolkit_Do_کھڑکی_Event_Loop(controls.کھڑکی);
    X11_Toolkit_Destroy_کھڑکی(controls.کھڑکی);
    SDL_free(controls.buttons);
    واپس true;
}

// Display an x11 message box.
bool X11_Show_پیغام_Box(ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonID)
{
    اگر (SDL_Zenity_Show_پیغام_Box(messageboxdata, buttonID)) {
        واپس true;
    }

#اگر SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    صحیح fds[2];
    صحیح حالت_2 = 0;
    bool نتیجہ = true;

    اگر (pipe(fds) == -1) {
        واپس X11_Show_پیغام_Box_Impl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    اگر (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        واپس X11_Show_پیغام_Box_Impl(messageboxdata, buttonID); // oh well.
    } ورنہ اگر (pid == 0) {                                       // we're the child
        صحیح exitcode = 0;
        close(fds[0]);
        نتیجہ = X11_Show_پیغام_Box_Impl(messageboxdata, buttonID);
        اگر (اكتب(fds[1], &نتیجہ, حجم(نتیجہ)) != حجم(نتیجہ)) {
            exitcode = 1;
        } ورنہ اگر (اكتب(fds[1], buttonID, حجم(*buttonID)) != حجم(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } ورنہ {             // we're the parent
        pid_t rc;
        close(fds[1]);
        کرو {
            rc = waitpid(pid, &حالت_2, 0);
        } جب ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        اگر ((rc == -1) || (!WIFEXITED(حالت_2)) || (WEXITSTATUS(حالت_2) != 0)) {
            نتیجہ = SDL_سیٹ_Error("msgbox child process failed");
        } ورنہ اگر ((اقرأ(fds[0], &نتیجہ, حجم(نتیجہ)) != حجم(نتیجہ)) ||
                   (اقرأ(fds[0], buttonID, حجم(*buttonID)) != حجم(*buttonID))) {
            نتیجہ = SDL_سیٹ_Error("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        واپس نتیجہ;
    }
#ورنہ
    واپس X11_Show_پیغام_Box_Impl(messageboxdata, buttonID);
#اگر_ختم
}
#اگر_ختم // SDL_VIDEO_DRIVER_X11
