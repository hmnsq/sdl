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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11

#ضمن "../../dialog/unix/SDL_zenitymessagebox.h"
#ضمن "SDL_x11messagebox.h"
#ضمن "SDL_x11toolkit.h"

#جيڪڏهن_وصف_نه_ٿيل SDL_FORK_MESSAGEBOX
#وصف_ڪريو SDL_FORK_MESSAGEBOX 0
#جيڪڏهن_پورو

#إذا SDL_FORK_MESSAGEBOX
#ضمن <sys/types.h>
#ضمن <sys/wait.h>
#ضمن <unistd.h>
#ضمن <errno.h>
#جيڪڏهن_پورو

تعريفنوع بنية SDL_پيغام_Box_X11
{
    SDL_Toolkit_دري_X11 *دري;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *پيغام;
    SDL_ToolkitControlX11 **buttons;
    ثابت SDL_پيغام_Box_معلومات *messageboxdata;
    صحيح *buttonID;
} SDL_پيغام_Box_X11;

ساكن فراغ X11_پيغام_Box_Button_Callback(SDL_ToolkitControlX11 *control, فراغ *معلومات)
{
    SDL_پيغام_Box_X11 *cbdata;

    cbdata = معلومات;
    *cbdata->buttonID = X11_Toolkit_Get_Button_Control_معلومات(control)->buttonID;
    X11_Toolkit_Signal_دري_Close(cbdata->دري);
}

ساكن فراغ X11_Position_پيغام_Box(SDL_پيغام_Box_X11 *controls, صحيح *wp, صحيح *hp) {
    صحيح پهريون_سٽ_ويڪر;
    صحيح پهريون_سٽ_اوچائي;
    صحيح ٻيو_سٽ_ويڪر;
    صحيح ٻيو_سٽ_اوچائي;
    صحيح max_button_ويڪر;
    صحيح max_button_اوچائي;
    صحيح دري_ويڪر;
    صحيح دري_اوچائي;
    صحيح i;
    bool rtl;
    
    /* window size */
    دري_ويڪر = 1;
    دري_اوچائي = 1;
    
    /* rtl */
    إذا (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ساڄو_منزل_کاٻو) {
        rtl = true;
    } وإلا إذا (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_کاٻو_منزل_ساڄو) {
        rtl = false;
    } وإلا {
        rtl = controls->دري->flip_interface;
    }
    
    /* first line */
    پهريون_سٽ_ويڪر = پهريون_سٽ_اوچائي = 0;
    إذا (controls->icon && controls->پيغام) {
        controls->icon->rect.y = 0;
        
        پهريون_سٽ_ويڪر = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->دري->iscale + controls->پيغام->rect.w;  
        
        إذا (!controls->دري->flip_interface) {
            controls->پيغام->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->دري->iscale;
            controls->icon->rect.x = 0;
        } وإلا {
            controls->پيغام->rect.x = 0;    
            controls->icon->rect.x = controls->پيغام->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->دري->iscale;
        }
        
        إذا (controls->پيغام->rect.h > controls->icon->rect.h) {
            controls->پيغام->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_پهريون_سٽ_اوچائي(controls->پيغام))/2;
            پهريون_سٽ_اوچائي = controls->پيغام->rect.y + controls->پيغام->rect.h;
        } وإلا {
            controls->پيغام->rect.y = (controls->icon->rect.h - controls->پيغام->rect.h)/2;
            پهريون_سٽ_اوچائي = controls->icon->rect.h;
        }        
    } وإلا إذا (!controls->icon && controls->پيغام) {
        پهريون_سٽ_ويڪر = controls->پيغام->rect.w;  
        پهريون_سٽ_اوچائي = controls->پيغام->rect.h;
        controls->پيغام->rect.x = 0;
        controls->پيغام->rect.y = 0;
    } وإلا إذا (controls->icon && !controls->پيغام) {
        پهريون_سٽ_ويڪر = controls->icon->rect.w;  
        پهريون_سٽ_اوچائي = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_ويڪر = 50;
    max_button_اوچائي = 0;
    ٻيو_سٽ_ويڪر = ٻيو_سٽ_اوچائي = 0;
    
    لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_ويڪر = SDL_max(max_button_ويڪر, controls->buttons[i]->rect.w);
        max_button_اوچائي = SDL_max(max_button_اوچائي, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    إذا (rtl) {
        لكل (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_ويڪر;
            controls->buttons[i]->rect.h = max_button_اوچائي;
            X11_Toolkit_Notify_Control_جو_سائيز_Change(controls->buttons[i]);

            إذا (پهريون_سٽ_اوچائي) {
                controls->buttons[i]->rect.y = پهريون_سٽ_اوچائي + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->دري->iscale;
                ٻيو_سٽ_اوچائي = max_button_اوچائي + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->دري->iscale;
            } وإلا {
                ٻيو_سٽ_اوچائي = max_button_اوچائي;
            }
            
            إذا ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->دري->iscale);
            }
        }    
    } وإلا {
        لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_ويڪر;
            controls->buttons[i]->rect.h = max_button_اوچائي;
            X11_Toolkit_Notify_Control_جو_سائيز_Change(controls->buttons[i]);

            إذا (پهريون_سٽ_اوچائي) {
                controls->buttons[i]->rect.y = پهريون_سٽ_اوچائي + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->دري->iscale;
                ٻيو_سٽ_اوچائي = max_button_اوچائي + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->دري->iscale;
            } وإلا {
                ٻيو_سٽ_اوچائي = max_button_اوچائي;
            }
            
            إذا (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->دري->iscale);
            }
        }
    }
    
    إذا (controls->messageboxdata->numbuttons) {
        إذا (rtl) {
            ٻيو_سٽ_ويڪر = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } وإلا {
            ٻيو_سٽ_ويڪر = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    إذا (ٻيو_سٽ_ويڪر > پهريون_سٽ_ويڪر) {
        صحيح pad;
        
        pad = (ٻيو_سٽ_ويڪر - پهريون_سٽ_ويڪر)/2;
        إذا (controls->پيغام) {
            controls->پيغام->rect.x += pad;
        }
        إذا (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } وإلا {
        صحيح pad;
        
        pad = (پهريون_سٽ_ويڪر - ٻيو_سٽ_ويڪر)/2;
        لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    دري_ويڪر = SDL_max(پهريون_سٽ_ويڪر, ٻيو_سٽ_ويڪر) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->دري->iscale;
    دري_اوچائي = پهريون_سٽ_اوچائي + ٻيو_سٽ_اوچائي + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->دري->iscale;
    *wp = دري_ويڪر;
    *hp = دري_اوچائي;
    إذا (controls->پيغام) {
        controls->پيغام->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->دري->iscale;
        controls->پيغام->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->دري->iscale;
    }
    إذا (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->دري->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->دري->iscale;
    }
    لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->دري->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->دري->iscale;
    }
}

ساكن فراغ X11_On_پيغام_Box_Scale_Change(SDL_Toolkit_دري_X11 *دري, فراغ *معلومات) {
    SDL_پيغام_Box_X11 *controls;
    صحيح w;
    صحيح h;

    controls = معلومات;
    X11_Position_پيغام_Box(controls, &w, &h);
    X11_Toolkit_Resize_دري(دري, w, h);
}

ساكن bool X11_Show_پيغام_Box_Impl(ثابت SDL_پيغام_Box_معلومات *messageboxdata, صحيح *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_دري *والد_دري = عدم;
    SDL_پيغام_Box_X11 controls;
    ثابت SDL_پيغام_Box_Color *colorhints;
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
    إذا (messageboxdata->دري && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        والد_دري = messageboxdata->دري;
    }
#إذا SDL_FORK_MESSAGEBOX
    controls.دري = X11_Toolkit_Create_دري_Struct(والد_دري, عدم, SDL_TOOLKIT_دري_گهڻائي_X11_DIALOG, colorhints, true);
#وإلا 
    controls.دري = X11_Toolkit_Create_دري_Struct(والد_دري, عدم, SDL_TOOLKIT_دري_گهڻائي_X11_DIALOG, colorhints, false);
#جيڪڏهن_پورو
    إذا (!controls.دري) {
        أرجع false;
    }
    controls.دري->cb_معلومات = &controls;
    controls.دري->cb_on_scale_change = X11_On_پيغام_Box_Scale_Change;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, حجم(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.دري, messageboxdata->flags);
    controls.پيغام = X11Toolkit_CreateLabelControl(controls.دري, (حرف *)messageboxdata->پيغام);
    لكل (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.دري, &messageboxdata->buttons[i]);
        X11_Toolkit_رجسٽر_Callback_For_Button_Control(controls.buttons[i], &controls, X11_پيغام_Box_Button_Callback);
    }

    /* Positioning */
    X11_Position_پيغام_Box(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11_Toolkit_Create_دري_Res(controls.دري, w, h, 0, 0, (حرف *)messageboxdata->title);
    X11_Toolkit_Do_دري_Event_Loop(controls.دري);
    X11_Toolkit_Destroy_دري(controls.دري);
    SDL_free(controls.buttons);
    أرجع true;
}

// Display an x11 message box.
bool X11_Show_پيغام_Box(ثابت SDL_پيغام_Box_معلومات *messageboxdata, صحيح *buttonID)
{
    إذا (SDL_Zenity_Show_پيغام_Box(messageboxdata, buttonID)) {
        أرجع true;
    }

#إذا SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    صحيح fds[2];
    صحيح حالت = 0;
    bool نتيجو = true;

    إذا (pipe(fds) == -1) {
        أرجع X11_Show_پيغام_Box_Impl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    إذا (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        أرجع X11_Show_پيغام_Box_Impl(messageboxdata, buttonID); // oh well.
    } وإلا إذا (pid == 0) {                                       // we're the child
        صحيح exitcode = 0;
        close(fds[0]);
        نتيجو = X11_Show_پيغام_Box_Impl(messageboxdata, buttonID);
        إذا (اكتب(fds[1], &نتيجو, حجم(نتيجو)) != حجم(نتيجو)) {
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
            نتيجو = SDL_سيٽ_Error("msgbox child process failed");
        } وإلا إذا ((اقرأ(fds[0], &نتيجو, حجم(نتيجو)) != حجم(نتيجو)) ||
                   (اقرأ(fds[0], buttonID, حجم(*buttonID)) != حجم(*buttonID))) {
            نتيجو = SDL_سيٽ_Error("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        أرجع نتيجو;
    }
#وإلا
    أرجع X11_Show_پيغام_Box_Impl(messageboxdata, buttonID);
#جيڪڏهن_پورو
}
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11
