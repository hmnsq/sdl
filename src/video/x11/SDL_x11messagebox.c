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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ "../../dialog/unix/SDL_zenitymessagebox.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11messagebox.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11toolkit.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_FORK_MESSAGEBOX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_FORK_MESSAGEBOX 0
#ਜੇ_ਅੰਤ

#ਜੇ SDL_FORK_MESSAGEBOX
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/types.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/wait.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_ਸੁਨੇਹਾ_Box_X11
{
    SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ;
    SDL_ToolkitControlX11 *icon;
    SDL_ToolkitControlX11 *ਸੁਨੇਹਾ;
    SDL_ToolkitControlX11 **buttons;
    ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata;
    ਪੂਰਨ *buttonID;
} SDL_ਸੁਨੇਹਾ_Box_X11;

ਸਥਿਰ ਖਾਲੀ X11_ਸੁਨੇਹਾ_Box_Button_Callback(SDL_ToolkitControlX11 *control, ਖਾਲੀ *ਅੰਕੜੇ)
{
    SDL_ਸੁਨੇਹਾ_Box_X11 *cbdata;

    cbdata = ਅੰਕੜੇ;
    *cbdata->buttonID = X11_Toolkit_Get_Button_Control_ਅੰਕੜੇ(control)->buttonID;
    X11_Toolkit_Signal_ਖਿੜਕੀ_Close(cbdata->ਖਿੜਕੀ);
}

ਸਥਿਰ ਖਾਲੀ X11_Position_ਸੁਨੇਹਾ_Box(SDL_ਸੁਨੇਹਾ_Box_X11 *controls, ਪੂਰਨ *wp, ਪੂਰਨ *hp) {
    ਪੂਰਨ ਪਹਿਲਾ_ਸਤਰ_ਚੌੜਾਈ;
    ਪੂਰਨ ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ;
    ਪੂਰਨ ਦੂਜਾ_ਸਤਰ_ਚੌੜਾਈ;
    ਪੂਰਨ ਦੂਜਾ_ਸਤਰ_ਉਚਾਈ;
    ਪੂਰਨ max_button_ਚੌੜਾਈ;
    ਪੂਰਨ max_button_ਉਚਾਈ;
    ਪੂਰਨ ਖਿੜਕੀ_ਚੌੜਾਈ;
    ਪੂਰਨ ਖਿੜਕੀ_ਉਚਾਈ;
    ਪੂਰਨ i;
    bool rtl;
    
    /* window size */
    ਖਿੜਕੀ_ਚੌੜਾਈ = 1;
    ਖਿੜਕੀ_ਉਚਾਈ = 1;
    
    /* rtl */
    ਜੇ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ਸੱਜਾ_ਮੰਜ਼ਿਲ_ਖੱਬਾ) {
        rtl = true;
    } ਨਹੀਂਤਾਂ ਜੇ (controls->messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ਖੱਬਾ_ਮੰਜ਼ਿਲ_ਸੱਜਾ) {
        rtl = false;
    } ਨਹੀਂਤਾਂ {
        rtl = controls->ਖਿੜਕੀ->flip_interface;
    }
    
    /* first line */
    ਪਹਿਲਾ_ਸਤਰ_ਚੌੜਾਈ = ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ = 0;
    ਜੇ (controls->icon && controls->ਸੁਨੇਹਾ) {
        controls->icon->rect.y = 0;
        
        ਪਹਿਲਾ_ਸਤਰ_ਚੌੜਾਈ = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ਖਿੜਕੀ->iscale + controls->ਸੁਨੇਹਾ->rect.w;  
        
        ਜੇ (!controls->ਖਿੜਕੀ->flip_interface) {
            controls->ਸੁਨੇਹਾ->rect.x = controls->icon->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->ਖਿੜਕੀ->iscale;
            controls->icon->rect.x = 0;
        } ਨਹੀਂਤਾਂ {
            controls->ਸੁਨੇਹਾ->rect.x = 0;    
            controls->icon->rect.x = controls->ਸੁਨੇਹਾ->rect.w + SDL_TOOLKIT_X11_ELEMENT_PADDING_2  * controls->ਖਿੜਕੀ->iscale;
        }
        
        ਜੇ (controls->ਸੁਨੇਹਾ->rect.h > controls->icon->rect.h) {
            controls->ਸੁਨੇਹਾ->rect.y = (controls->icon->rect.h - X11_Toolkit_Get_Label_Control_ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ(controls->ਸੁਨੇਹਾ))/2;
            ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ = controls->ਸੁਨੇਹਾ->rect.y + controls->ਸੁਨੇਹਾ->rect.h;
        } ਨਹੀਂਤਾਂ {
            controls->ਸੁਨੇਹਾ->rect.y = (controls->icon->rect.h - controls->ਸੁਨੇਹਾ->rect.h)/2;
            ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ = controls->icon->rect.h;
        }        
    } ਨਹੀਂਤਾਂ ਜੇ (!controls->icon && controls->ਸੁਨੇਹਾ) {
        ਪਹਿਲਾ_ਸਤਰ_ਚੌੜਾਈ = controls->ਸੁਨੇਹਾ->rect.w;  
        ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ = controls->ਸੁਨੇਹਾ->rect.h;
        controls->ਸੁਨੇਹਾ->rect.x = 0;
        controls->ਸੁਨੇਹਾ->rect.y = 0;
    } ਨਹੀਂਤਾਂ ਜੇ (controls->icon && !controls->ਸੁਨੇਹਾ) {
        ਪਹਿਲਾ_ਸਤਰ_ਚੌੜਾਈ = controls->icon->rect.w;  
        ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ = controls->icon->rect.h;
        controls->icon->rect.x = 0;
        controls->icon->rect.y = 0;        
    }
    
    /* second line */
    max_button_ਚੌੜਾਈ = 50;
    max_button_ਉਚਾਈ = 0;
    ਦੂਜਾ_ਸਤਰ_ਚੌੜਾਈ = ਦੂਜਾ_ਸਤਰ_ਉਚਾਈ = 0;
    
    ਲਈ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        max_button_ਚੌੜਾਈ = SDL_max(max_button_ਚੌੜਾਈ, controls->buttons[i]->rect.w);
        max_button_ਉਚਾਈ = SDL_max(max_button_ਉਚਾਈ, controls->buttons[i]->rect.h);
        controls->buttons[i]->rect.x = 0;
        controls->buttons[i]->rect.y = 0;
    }

    ਜੇ (rtl) {
        ਲਈ (i = (controls->messageboxdata->numbuttons - 1); i != -1; i--) {
            controls->buttons[i]->rect.w = max_button_ਚੌੜਾਈ;
            controls->buttons[i]->rect.h = max_button_ਉਚਾਈ;
            X11_Toolkit_Notify_Control_ਦਾ_ਮਾਪ_Change(controls->buttons[i]);

            ਜੇ (ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ) {
                controls->buttons[i]->rect.y = ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->ਖਿੜਕੀ->iscale;
                ਦੂਜਾ_ਸਤਰ_ਉਚਾਈ = max_button_ਉਚਾਈ + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->ਖਿੜਕੀ->iscale;
            } ਨਹੀਂਤਾਂ {
                ਦੂਜਾ_ਸਤਰ_ਉਚਾਈ = max_button_ਉਚਾਈ;
            }
            
            ਜੇ ((i + 1) < controls->messageboxdata->numbuttons) {
                controls->buttons[i]->rect.x = controls->buttons[i + 1]->rect.x + controls->buttons[i + 1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->ਖਿੜਕੀ->iscale);
            }
        }    
    } ਨਹੀਂਤਾਂ {
        ਲਈ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.w = max_button_ਚੌੜਾਈ;
            controls->buttons[i]->rect.h = max_button_ਉਚਾਈ;
            X11_Toolkit_Notify_Control_ਦਾ_ਮਾਪ_Change(controls->buttons[i]);

            ਜੇ (ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ) {
                controls->buttons[i]->rect.y = ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->ਖਿੜਕੀ->iscale;
                ਦੂਜਾ_ਸਤਰ_ਉਚਾਈ = max_button_ਉਚਾਈ + SDL_TOOLKIT_X11_ELEMENT_PADDING_4 * controls->ਖਿੜਕੀ->iscale;
            } ਨਹੀਂਤਾਂ {
                ਦੂਜਾ_ਸਤਰ_ਉਚਾਈ = max_button_ਉਚਾਈ;
            }
            
            ਜੇ (i) {
                controls->buttons[i]->rect.x = controls->buttons[i-1]->rect.x + controls->buttons[i-1]->rect.w + (SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * controls->ਖਿੜਕੀ->iscale);
            }
        }
    }
    
    ਜੇ (controls->messageboxdata->numbuttons) {
        ਜੇ (rtl) {
            ਦੂਜਾ_ਸਤਰ_ਚੌੜਾਈ = controls->buttons[0]->rect.x + controls->buttons[0]->rect.w;
        } ਨਹੀਂਤਾਂ {
            ਦੂਜਾ_ਸਤਰ_ਚੌੜਾਈ = controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.x + controls->buttons[controls->messageboxdata->numbuttons - 1]->rect.w;            
        }
    }

    /* center lines */
    ਜੇ (ਦੂਜਾ_ਸਤਰ_ਚੌੜਾਈ > ਪਹਿਲਾ_ਸਤਰ_ਚੌੜਾਈ) {
        ਪੂਰਨ pad;
        
        pad = (ਦੂਜਾ_ਸਤਰ_ਚੌੜਾਈ - ਪਹਿਲਾ_ਸਤਰ_ਚੌੜਾਈ)/2;
        ਜੇ (controls->ਸੁਨੇਹਾ) {
            controls->ਸੁਨੇਹਾ->rect.x += pad;
        }
        ਜੇ (controls->icon) {
            controls->icon->rect.x += pad;
        }
    } ਨਹੀਂਤਾਂ {
        ਪੂਰਨ pad;
        
        pad = (ਪਹਿਲਾ_ਸਤਰ_ਚੌੜਾਈ - ਦੂਜਾ_ਸਤਰ_ਚੌੜਾਈ)/2;
        ਲਈ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
            controls->buttons[i]->rect.x += pad;
        }
    }
     
    /* window size and final padding */
    ਖਿੜਕੀ_ਚੌੜਾਈ = SDL_max(ਪਹਿਲਾ_ਸਤਰ_ਚੌੜਾਈ, ਦੂਜਾ_ਸਤਰ_ਚੌੜਾਈ) + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->ਖਿੜਕੀ->iscale;
    ਖਿੜਕੀ_ਉਚਾਈ = ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ + ਦੂਜਾ_ਸਤਰ_ਉਚਾਈ + SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * 2 * controls->ਖਿੜਕੀ->iscale;
    *wp = ਖਿੜਕੀ_ਚੌੜਾਈ;
    *hp = ਖਿੜਕੀ_ਉਚਾਈ;
    ਜੇ (controls->ਸੁਨੇਹਾ) {
        controls->ਸੁਨੇਹਾ->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ਖਿੜਕੀ->iscale;
        controls->ਸੁਨੇਹਾ->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ਖਿੜਕੀ->iscale;
    }
    ਜੇ (controls->icon) {
        controls->icon->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ਖਿੜਕੀ->iscale;
        controls->icon->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ਖਿੜਕੀ->iscale;
    }
    ਲਈ (i = 0; i < controls->messageboxdata->numbuttons; i++) {
        controls->buttons[i]->rect.x += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ਖਿੜਕੀ->iscale;
        controls->buttons[i]->rect.y += SDL_TOOLKIT_X11_ELEMENT_PADDING_2 * controls->ਖਿੜਕੀ->iscale;
    }
}

ਸਥਿਰ ਖਾਲੀ X11_On_ਸੁਨੇਹਾ_Box_Scale_Change(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ, ਖਾਲੀ *ਅੰਕੜੇ) {
    SDL_ਸੁਨੇਹਾ_Box_X11 *controls;
    ਪੂਰਨ w;
    ਪੂਰਨ h;

    controls = ਅੰਕੜੇ;
    X11_Position_ਸੁਨੇਹਾ_Box(controls, &w, &h);
    X11_Toolkit_Resize_ਖਿੜਕੀ(ਖਿੜਕੀ, w, h);
}

ਸਥਿਰ bool X11_Show_ਸੁਨੇਹਾ_Box_Impl(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID)
{
    SDL_VideoDevice *video = SDL_GetVideoDevice();
    SDL_ਖਿੜਕੀ *ਮਾਪਾ_ਖਿੜਕੀ = ਨਿਰਾ;
    SDL_ਸੁਨੇਹਾ_Box_X11 controls;
    ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color *colorhints;
    ਪੂਰਨ i;
    ਪੂਰਨ w;
    ਪੂਰਨ h;

    controls.messageboxdata = messageboxdata;

    /* Color scheme */
    ਜੇ (messageboxdata->colorScheme) {
        colorhints = messageboxdata->colorScheme->colors;
    } ਨਹੀਂਤਾਂ {
        colorhints = ਨਿਰਾ;
    }

    /* Create window */
    ਜੇ (messageboxdata->ਖਿੜਕੀ && video && SDL_strcmp(video->name, "x11") == 0) {
        // Only use the window as a parent if it is from the X11 driver.
        ਮਾਪਾ_ਖਿੜਕੀ = messageboxdata->ਖਿੜਕੀ;
    }
#ਜੇ SDL_FORK_MESSAGEBOX
    controls.ਖਿੜਕੀ = X11_Toolkit_Create_ਖਿੜਕੀ_Struct(ਮਾਪਾ_ਖਿੜਕੀ, ਨਿਰਾ, SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_DIALOG, colorhints, true);
#ਨਹੀਂਤਾਂ 
    controls.ਖਿੜਕੀ = X11_Toolkit_Create_ਖਿੜਕੀ_Struct(ਮਾਪਾ_ਖਿੜਕੀ, ਨਿਰਾ, SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_DIALOG, colorhints, false);
#ਜੇ_ਅੰਤ
    ਜੇ (!controls.ਖਿੜਕੀ) {
        ਵਾਪਸ false;
    }
    controls.ਖਿੜਕੀ->cb_ਅੰਕੜੇ = &controls;
    controls.ਖਿੜਕੀ->cb_on_scale_change = X11_On_ਸੁਨੇਹਾ_Box_Scale_Change;

    /* Create controls */
    controls.buttonID = buttonID;
    controls.buttons = SDL_calloc(messageboxdata->numbuttons, ਆਕਾਰ(SDL_ToolkitControlX11 *));
    controls.icon = X11Toolkit_CreateIconControl(controls.ਖਿੜਕੀ, messageboxdata->flags);
    controls.ਸੁਨੇਹਾ = X11Toolkit_CreateLabelControl(controls.ਖਿੜਕੀ, (ਅੱਖਰ *)messageboxdata->ਸੁਨੇਹਾ);
    ਲਈ (i = 0; i < messageboxdata->numbuttons; i++) {
        controls.buttons[i] = X11Toolkit_CreateButtonControl(controls.ਖਿੜਕੀ, &messageboxdata->buttons[i]);
        X11_Toolkit_ਰਜਿਸਟਰ_Callback_For_Button_Control(controls.buttons[i], &controls, X11_ਸੁਨੇਹਾ_Box_Button_Callback);
    }

    /* Positioning */
    X11_Position_ਸੁਨੇਹਾ_Box(&controls, &w, &h);

    /* Actually create window, do event loop, cleanup */
    X11_Toolkit_Create_ਖਿੜਕੀ_Res(controls.ਖਿੜਕੀ, w, h, 0, 0, (ਅੱਖਰ *)messageboxdata->title);
    X11_Toolkit_Do_ਖਿੜਕੀ_Event_Loop(controls.ਖਿੜਕੀ);
    X11_Toolkit_Destroy_ਖਿੜਕੀ(controls.ਖਿੜਕੀ);
    SDL_free(controls.buttons);
    ਵਾਪਸ true;
}

// Display an x11 message box.
bool X11_Show_ਸੁਨੇਹਾ_Box(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID)
{
    ਜੇ (SDL_Zenity_Show_ਸੁਨੇਹਾ_Box(messageboxdata, buttonID)) {
        ਵਾਪਸ true;
    }

#ਜੇ SDL_FORK_MESSAGEBOX
    // Use a child process to protect against setlocale(). Annoying.
    pid_t pid;
    ਪੂਰਨ fds[2];
    ਪੂਰਨ ਸਥਿਤੀ = 0;
    bool ਨਤੀਜਾ = true;

    ਜੇ (pipe(fds) == -1) {
        ਵਾਪਸ X11_Show_ਸੁਨੇਹਾ_Box_Impl(messageboxdata, buttonID); // oh well.
    }

    pid = fork();
    ਜੇ (pid == -1) { // failed
        close(fds[0]);
        close(fds[1]);
        ਵਾਪਸ X11_Show_ਸੁਨੇਹਾ_Box_Impl(messageboxdata, buttonID); // oh well.
    } ਨਹੀਂਤਾਂ ਜੇ (pid == 0) {                                       // we're the child
        ਪੂਰਨ exitcode = 0;
        close(fds[0]);
        ਨਤੀਜਾ = X11_Show_ਸੁਨੇਹਾ_Box_Impl(messageboxdata, buttonID);
        ਜੇ (ਲਿਖ(fds[1], &ਨਤੀਜਾ, ਆਕਾਰ(ਨਤੀਜਾ)) != ਆਕਾਰ(ਨਤੀਜਾ)) {
            exitcode = 1;
        } ਨਹੀਂਤਾਂ ਜੇ (ਲਿਖ(fds[1], buttonID, ਆਕਾਰ(*buttonID)) != ਆਕਾਰ(*buttonID)) {
            exitcode = 1;
        }
        close(fds[1]);
        _exit(exitcode); // don't run atexit() stuff, static destructors, etc.
    } ਨਹੀਂਤਾਂ {             // we're the parent
        pid_t rc;
        close(fds[1]);
        ਕਰੋ {
            rc = waitpid(pid, &ਸਥਿਤੀ, 0);
        } ਜਦੋਂ ((rc == -1) && (errno == EINTR));

        SDL_assert(rc == pid); // not sure what to do if this fails.

        ਜੇ ((rc == -1) || (!WIFEXITED(ਸਥਿਤੀ)) || (WEXITSTATUS(ਸਥਿਤੀ) != 0)) {
            ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("msgbox child process failed");
        } ਨਹੀਂਤਾਂ ਜੇ ((ਪਠ(fds[0], &ਨਤੀਜਾ, ਆਕਾਰ(ਨਤੀਜਾ)) != ਆਕਾਰ(ਨਤੀਜਾ)) ||
                   (ਪਠ(fds[0], buttonID, ਆਕਾਰ(*buttonID)) != ਆਕਾਰ(*buttonID))) {
            ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("read from msgbox child process failed");
            *buttonID = 0;
        }
        close(fds[0]);

        ਵਾਪਸ ਨਤੀਜਾ;
    }
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ X11_Show_ਸੁਨੇਹਾ_Box_Impl(messageboxdata, buttonID);
#ਜੇ_ਅੰਤ
}
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
