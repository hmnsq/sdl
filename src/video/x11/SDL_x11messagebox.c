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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11

#ضمن "../../dialog/unix/SDL_zenitymessagebox.h"
#ضمن "SDL_x11messagebox.h"
#ضمن "SDL_x11toolkit.h"

#اگر_تعریف_نشده SDL_FORK_MESSAGEBOX
#تعریف_کن SDL_FORK_MESSAGEBOX 0
#پایان_اگر

#إذا SDL_FORK_MESSAGEBOX
#ضمن <sys/types.h>
#ضمن <sys/wait.h>
#ضمن <unistd.h>
#ضمن <errno.h>
#پایان_اگر

تعريفنوع بنية SDL_پیام_Box_X11
{
    SDL_Toolkit_پنجره_X11 *پنجره;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *پیام;
    SDL_ToolkitControlX11 **buttons;
    ثابت SDL_پیام_Box_داده *messageboxdata;
    صحيح *buttonID;
} SDL_پیام_Box_X11;

ساكن فراغ X11_پیام_Box_Button_Callback(SDL_ToolkitControlX11 *control, فراغ *داده)
{
    SDL_پیام_Box_X11 *cbdata;

    cbdata = داده;
    *cbdata->buttonID = X11_Toolkit_Get_Button_Control_داده(control)->buttonID;
    X11_Toolkit_Signal_پنجره_Close(cbdata->پنجره);
}

ساكن فراغ X11_Position_پیام_Box(SDL_پیام_Box_X11 *controls, صحيح *wp, صحيح *hp) {
    صحيح اولی_سطر_عرض;
    صحيح اولی_سطر_ارتفاع;
    صحيح دومی_سطر_عرض;
    صحيح دومی_سطر_ارتفاع;
    صحيح max_button_عرض;
    صحيح max_button_ارتفاع;
    صحيح پنجره_عرض;
    صحيح پنجره_ارتفاع;
    صحيح i;
    bool rtl;
    
    /* window size */
    پنجره_عرض = 1;
    پنجره_ارتفاع = 1;
    
    /* rtl */
    إذا (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_راست_مقصد_چپ) {
        rtl = true;
    } وإلا إذا (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_چپ_مقصد_راست) {
        rtl = false;
    } وإلا {
        rtl = controls->پنجره->flip_interface;
    }
    
    /* first line */
    اولی_سطر_عرض = اولی_سطر_ارتفاع = 0;
    إذا (controls->icon && controls->پیام) {
        controls->icon->rect.y = 0;
        
        اولی_سطر_عرض = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->پنجره->iscale + controls->پیام->rect.w;  
        
        إذا (!controls->پنجره->flip_interface) {
            controls->پیام->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->پنجره->iscale;
            controls->icon->rect.x = 0;
        } وإلا {
            controls->پیام->rect.x = 0;    
            controls->icon->rect.x = controls->پیام->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->پنجره->iscale;
        }
        
        إذا (controls->پیام->rect.h > controls->icon->rect.h) {
            controls->پیام->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_اولی_سطر_ارتفاع(controls->پیام))/2;
            اولی_سطر_ارتفاع = controls->پیام->rect.y + controls->پیام->rect.h;
        } وإلا {
            controls->پیام->rect.y = (controls->icon->rect.h - controls->پیام->rect.h)/2;
            اولی_سطر_ارتفاع = controls->icon->rect.h;
        }        
    } وإلا إذا (!controls->icon && controls->پیام) {
        اولی_سطر_عرض = controls->پیام->rect.w;  
        اولی_سطر_ارتفاع = controls->پیام->rect.h;
        controls->پیام->rect.x = 0;
        controls->پیام->rect.y = 0;
    } وإلا إذا (controls->icon && !controls->پیام) {
        اولی_سطر_عرض = controls->icon->rect.w;  
        اولی_سطر_ارتفاع = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_عرض = 50;
    max_button_ارتفاع = 0;
    دومی_سطر_عرض = دومی_سطر_ارتفاع = 0;
    
    لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_عرض = SDL_max(max_button_عرض, controls->buttons[i]->rect.w);
        max_button_ارتفاع = SDL_max(max_button_ارتفاع, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    إذا (rtl) {
        لكل (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_عرض;
            controls->buttons[i]->rect.h = max_button_ارتفاع;
            X11_Toolkit_Notify_Control_از_اندازه_Change(controls->buttons[i]);

            إذا (اولی_سطر_ارتفاع) {
                controls->buttons[i]->rect.y = اولی_سطر_ارتفاع + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->پنجره->iscale;
                دومی_سطر_ارتفاع = max_button_ارتفاع + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->پنجره->iscale;
            } وإلا {
                دومی_سطر_ارتفاع = max_button_ارتفاع;
            }
            
            إذا ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->پنجره->iscale);
            }
        }    
    } وإلا {
        لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_عرض;
            controls->buttons[i]->rect.h = max_button_ارتفاع;
            X11_Toolkit_Notify_Control_از_اندازه_Change(controls->buttons[i]);

            إذا (اولی_سطر_ارتفاع) {
                controls->buttons[i]->rect.y = اولی_سطر_ارتفاع + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->پنجره->iscale;
                دومی_سطر_ارتفاع = max_button_ارتفاع + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->پنجره->iscale;
            } وإلا {
                دومی_سطر_ارتفاع = max_button_ارتفاع;
            }
            
            إذا (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->پنجره->iscale);
            }
        }
    }
    
    إذا (controls->messageboxdata->numbuttons) {
        إذا (rtl) {
            دومی_سطر_عرض = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } وإلا {
            دومی_سطر_عرض = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    إذا (دومی_سطر_عرض > اولی_سطر_عرض) {
        صحيح pad;
        
        pad = (دومی_سطر_عرض - اولی_سطر_عرض)/2;
        إذا (controls->پیام) {
            controls->پیام->rect.x += pad;
        }
        إذا (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } وإلا {
        صحيح pad;
        
        pad = (اولی_سطر_عرض - دومی_سطر_عرض)/2;
        لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    پنجره_عرض = SDL_max(اولی_سطر_عرض, دومی_سطر_عرض) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->پنجره->iscale;
    پنجره_ارتفاع = اولی_سطر_ارتفاع + دومی_سطر_ارتفاع + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->پنجره->iscale;
    *wp = پنجره_عرض;
    *hp = پنجره_ارتفاع;
    إذا (controls->پیام) {
        controls->پیام->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->پنجره->iscale;
        controls->پیام->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->پنجره->iscale;
    }
    إذا (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->پنجره->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->پنجره->iscale;
    }
    لكل (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->پنجره->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->پنجره->iscale;
    }
}

ساكن فراغ X11_On_پیام_Box_Scale_Change(SDL_Toolkit_پنجره_X11 *پنجره, فراغ *داده) {
    SDL_پیام_Box_X11 *controls;
    صحيح w;
    صحيح h;

    controls = داده;
    X11_Position_پیام_Box(controls, &w, &h);
    X11_Toolkit_Resize_پنجره(پنجره, w, h);
}

ساكن bool X11_Show_پیام_Box_Impl(ثابت SDL_پیام_Box_داده *messageboxdata, صحيح *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_پنجره *والد_پنجره = عدم;
    SDL_پیام_Box_X11 controls;
    ثابت SDL_پیام_Box_Color *colorhints;
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
    إذا (messageboxdata->پنجره && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        والد_پنجره = messageboxdata->پنجره;
    }
#إذا SDL_FORK_MESSAGEBOX
    controls.پنجره = X11_Toolkit_Create_پنجره_Struct(والد_پنجره, عدم, SDL_TOOLKIT_پنجره_نما_X11_DIALOG, colorhints, true);
#وإلا 
    controls.پنجره = X11_Toolkit_Create_پنجره_Struct(والد_پنجره, عدم, SDL_TOOLKIT_پنجره_نما_X11_DIALOG, colorhints, false);
#پایان_اگر
    إذا (!controls.پنجره) {
        أرجع false;
    }
    controls.پنجره->cb_داده = &controls;
    controls.پنجره->cb_on_scale_change = X11_On_پیام_Box_Scale_Change;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, حجم(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.پنجره, messageboxdata->flags);
    controls.پیام = X11Toolkit_CreateLabelControl(controls.پنجره, (حرف *)messageboxdata->پیام);
    لكل (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.پنجره, &messageboxdata->buttons[i]);
        X11_Toolkit_ثبات_Callback_For_Button_Control(controls.buttons[i], &controls, X11_پیام_Box_Button_Callback);
    }

    /* Positioning */
    X11_Position_پیام_Box(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11_Toolkit_Create_پنجره_Res(controls.پنجره, w, h, 0, 0, (حرف *)messageboxdata->title);
    X11_Toolkit_Do_پنجره_Event_Loop(controls.پنجره);
    X11_Toolkit_Destroy_پنجره(controls.پنجره);
    SDL_free(controls.buttons);
    أرجع true;
}

// Display an x11 message box.
bool X11_Show_پیام_Box(ثابت SDL_پیام_Box_داده *messageboxdata, صحيح *buttonID)
{
    إذا (SDL_Zenity_Show_پیام_Box(messageboxdata, buttonID)) {
        أرجع true;
    }

#إذا SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    صحيح fds[2];
    صحيح وضعیت = 0;
    bool نتیجه = true;

    إذا (pipe(fds) == -1) {
        أرجع X11_Show_پیام_Box_Impl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    إذا (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        أرجع X11_Show_پیام_Box_Impl(messageboxdata, buttonID); // oh well.
    } وإلا إذا (pid == 0) {                                       // we're the child
        صحيح exitcode = 0;
        close(fds[0]);
        نتیجه = X11_Show_پیام_Box_Impl(messageboxdata, buttonID);
        إذا (اكتب(fds[1], &نتیجه, حجم(نتیجه)) != حجم(نتیجه)) {
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
            rc = waitpid(pid, &وضعیت, 0);
        } طالما ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        إذا ((rc == -1) || (!WIFEXITED(وضعیت)) || (WEXITSTATUS(وضعیت) != 0)) {
            نتیجه = SDL_مجموعه_Error("msgbox child process failed");
        } وإلا إذا ((اقرأ(fds[0], &نتیجه, حجم(نتیجه)) != حجم(نتیجه)) ||
                   (اقرأ(fds[0], buttonID, حجم(*buttonID)) != حجم(*buttonID))) {
            نتیجه = SDL_مجموعه_Error("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        أرجع نتیجه;
    }
#وإلا
    أرجع X11_Show_پیام_Box_Impl(messageboxdata, buttonID);
#پایان_اگر
}
#پایان_اگر // SDL_VIDEO_DRIVER_X11
