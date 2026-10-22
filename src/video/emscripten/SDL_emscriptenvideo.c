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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_EMSCRIPTEN

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_hints_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_emscriptenvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_emscriptenopengles.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_emscriptenframebuffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_emscriptenevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_emscriptenmouse.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EMSCRIPTENVID_DRIVER_NAME "emscripten"

// Initialization/Query functions
ਸਥਿਰ bool Emscripten_VideoInit(SDL_VideoDevice *_this);
ਸਥਿਰ bool Emscripten_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਸਥਿਰ ਖਾਲੀ Emscripten_VideoQuit(SDL_VideoDevice *_this);
ਸਥਿਰ bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

ਸਥਿਰ bool Emscripten_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
ਸਥਿਰ ਖਾਲੀ Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਸਥਿਰ ਖਾਲੀ Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ, bool resizable);
ਸਥਿਰ ਖਾਲੀ Emscripten_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *w, ਪੂਰਨ *h);
ਸਥਿਰ ਖਾਲੀ Emscripten_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਸਥਿਰ SDL_Fullscreen_ਨਤੀਜਾ Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ਸਥਿਰ ਖਾਲੀ Emscripten_PumpEvents(SDL_VideoDevice *_this);
ਸਥਿਰ ਖਾਲੀ Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਸਥਿਰ bool Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Icon(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *icon);
ਸਥਿਰ bool Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Fill_Document(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool fill);

SDL_ਖਿੜਕੀ *Emscripten_fill_document_ਖਿੜਕੀ = ਨਿਰਾ;

ਸਥਿਰ bool pumpevents_has_ਲੜੀਵਾਰ = false;
ਸਥਿਰ ਪੂਰਨ pending_ਅਦਲਾ_ਬਦਲੀ_interval = -1;

// Emscripten driver bootstrap functions

ਸਥਿਰ ਖਾਲੀ Emscripten_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ਸਥਿਰ SDL_SystemTheme Emscripten_GetSystemTheme(ਖਾਲੀ)
{
    /* Technically, light theme can mean explicit light theme or no preference.
       https://developer.mozilla.org/en-US/docs/Web/CSS/@media/prefers-color-scheme#syntax */

    ਪੂਰਨ theme_ਕੋਡ = MAIN_THREAD_EM_ASM_INT({
        ਜੇ (!ਖਿੜਕੀ.ਮੇਲ_Media) {
            ਵਾਪਸ -1;
        }

        ਜੇ (ਖਿੜਕੀ.ਮੇਲ_Media('(prefers-color-scheme: light)').matches) {
            ਵਾਪਸ 0;
        }

        ਜੇ (ਖਿੜਕੀ.ਮੇਲ_Media('(prefers-color-scheme: dark)').matches) {
            ਵਾਪਸ 1;
        }

        ਵਾਪਸ -1;
    });

    ਚੋਣ (theme_ਕੋਡ) {
    ਹਾਲਤ 0:
        ਵਾਪਸ SDL_SYSTEM_THEME_LIGHT;

    ਹਾਲਤ 1:
        ਵਾਪਸ SDL_SYSTEM_THEME_DARK;

    ਮੂਲ:
        ਵਾਪਸ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

ਸਥਿਰ ਖਾਲੀ Emscripten_ListenSystemTheme(ਖਾਲੀ)
{
    MAIN_THREAD_EM_ASM({
        ਜੇ (ਖਿੜਕੀ.ਮੇਲ_Media) {
            var SDL3 = Module['SDL3'];

            SDL3.event_Handler_Theme_ਬਦਲਿਆ = function(event) {
                Emscripten_Send_System_Theme_ਬਦਲਿਆ_Event();
            };

            SDL3.theme_ਬਦਲਿਆ_ਮੇਲ_Media = ਖਿੜਕੀ.ਮੇਲ_Media('(prefers-color-scheme: dark)');
            SDL3.theme_ਬਦਲਿਆ_ਮੇਲ_Media.ਜੋੜੋ_Event_Listener('change', SDL3.event_Handler_Theme_ਬਦਲਿਆ);
        }
    });
}

ਸਥਿਰ ਖਾਲੀ Emscripten_UnlistenSystemTheme(ਖਾਲੀ)
{
    MAIN_THREAD_EM_ASM({
        ਜੇ (typeof(Module['SDL3']) !== 'undefined') {
            var SDL3 = Module['SDL3'];

            SDL3.theme_ਬਦਲਿਆ_ਮੇਲ_Media.removeEventListener('change', SDL3.event_Handler_Theme_ਬਦਲਿਆ);
            SDL3.theme_ਬਦਲਿਆ_ਮੇਲ_Media = undefined;
            SDL3.event_Handler_Theme_ਬਦਲਿਆ = undefined;
        }
    });
}

EMSCRIPTEN_KEEPALIVE ਖਾਲੀ Emscripten_Send_System_Theme_ਬਦਲਿਆ_Event_2(ਖਾਲੀ)
{
    SDL_ਸੈੱਟ_System_Theme(Emscripten_GetSystemTheme());
}

ਸਥਿਰ SDL_VideoDevice *Emscripten_CreateDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    /* Firefox sends blur event which would otherwise prevent full screen
     * when the user clicks to allow full screen.
     * See https://bugzilla.mozilla.org/show_bug.cgi?id=1144964
     */
    SDL_ਸੈੱਟ_Hint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

    // Set the function pointers
    device->VideoInit = Emscripten_VideoInit;
    device->VideoQuit = Emscripten_VideoQuit;
    device->GetDisplayUsableBounds = Emscripten_GetDisplayUsableBounds;
    device->ਸੈੱਟ_Display_ਬਹੁਲਕ = Emscripten_ਸੈੱਟ_Display_ਬਹੁਲਕ;

    device->PumpEvents = Emscripten_PumpEvents;

    device->CreateSDLWindow = Emscripten_Create_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Title = Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Title;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Icon = Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Icon;
    /*device->SetWindowPosition = Emscripten_SetWindowPosition;*/
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Resizable = Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Resizable;
    /*device->ShowWindow = Emscripten_ShowWindow;
    device->HideWindow = Emscripten_HideWindow;
    device->RaiseWindow = Emscripten_RaiseWindow;
    device->MaximizeWindow = Emscripten_MaximizeWindow;
    device->MinimizeWindow = Emscripten_MinimizeWindow;
    device->RestoreWindow = Emscripten_RestoreWindow;
    device->SetWindowMouseGrab = Emscripten_SetWindowMouseGrab;*/
    device->Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels = Emscripten_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels;
    device->Destroy_ਖਿੜਕੀ = Emscripten_Destroy_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen = Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Fill_Document = Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Fill_Document;

    device->Create_ਖਿੜਕੀ_Framebuffer = Emscripten_Create_ਖਿੜਕੀ_Framebuffer;
    device->Update_ਖਿੜਕੀ_Framebuffer = Emscripten_Update_ਖਿੜਕੀ_Framebuffer;
    device->Destroy_ਖਿੜਕੀ_Framebuffer = Emscripten_Destroy_ਖਿੜਕੀ_Framebuffer;

    device->GL_ਲੱਦੋ_Library = Emscripten_GLES_ਲੱਦੋ_Library;
    device->GL_Get_Proc_ਪਤਾ = Emscripten_GLES_Get_Proc_ਪਤਾ;
    device->GL_UnloadLibrary = Emscripten_GLES_UnloadLibrary;
    device->GL_CreateContext = Emscripten_GLES_CreateContext;
    device->GL_MakeCurrent = Emscripten_GLES_MakeCurrent;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = Emscripten_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = Emscripten_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = Emscripten_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_DestroyContext = Emscripten_GLES_DestroyContext;

    device->ਮੁਕਤ = Emscripten_DeleteDevice;

    Emscripten_ListenSystemTheme();
    device->system_theme = Emscripten_GetSystemTheme();

    ਵਾਪਸ device;
}

ਸਥਿਰ bool Emscripten_ShowMessagebox(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID) {
    ਜੇ (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        ਅੱਖਰ dialog_background[32];
        ਅੱਖਰ dialog_color[32];
        ਅੱਖਰ button_border[32];
        ਅੱਖਰ button_background[32];
        ਅੱਖਰ button_hovered[32];

        ਜੇ (messageboxdata->colorScheme) {
            SDL_ਸੁਨੇਹਾ_Box_Color color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND];
            SDL_snprintf(dialog_background, ਆਕਾਰ(dialog_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_ਪਾਠ];
            SDL_snprintf(dialog_color, ਆਕਾਰ(dialog_color), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER];
            SDL_snprintf(button_border, ਆਕਾਰ(button_border), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND];
            SDL_snprintf(button_background, ਆਕਾਰ(button_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED];
            SDL_snprintf(button_hovered, ਆਕਾਰ(button_hovered), "rgb(%u, %u, %u)", color.r, color.g, color.b);
        } ਨਹੀਂਤਾਂ {
            SDL_zero(dialog_background);
            SDL_zero(dialog_color);
            SDL_zero(button_border);
            SDL_zero(button_background);
            SDL_zero(button_hovered);
        }

        // TODO: Handle parent window when multiple windows can be added in Emscripten builds
        ਅੱਖਰ dialog_id[64];
        SDL_snprintf(dialog_id, ਆਕਾਰ(dialog_id), "SDL3_messagebox_%u", SDL_rand_ਬਿੱਟ());
        EM_ASM({
            var title = UTF8_ਮੰਜ਼ਿਲ_String($0);
            var ਸੁਨੇਹਾ = UTF8_ਮੰਜ਼ਿਲ_String($1);
            var background = UTF8_ਮੰਜ਼ਿਲ_String($2);
            var color = UTF8_ਮੰਜ਼ਿਲ_String($3);
            var id = UTF8_ਮੰਜ਼ਿਲ_String($4);

            // Dialogs are always put in the front of the DOM
            var dialog = document.createElement("dialog");
            // Set class to allow for CSS selectors
            dialog.classList.ਜੋੜੋ("SDL3_messagebox");
            dialog.id = id;
            dialog.style.color = color;
            dialog.style.backgroundColor = background;
            document.body.append(dialog);

            var h1 = document.createElement("h1");
            h1.inner_ਪਾਠ = title;
            dialog.append(h1);

            var p = document.createElement("p");
            p.inner_ਪਾਠ = ਸੁਨੇਹਾ;
            dialog.append(p);

            dialog.showModal();
        }, messageboxdata->title, messageboxdata->ਸੁਨੇਹਾ, dialog_background, dialog_color, dialog_id);

        ਪੂਰਨ i;
        ਲਈ (i = 0; i < messageboxdata->numbuttons; ++i) {
            SDL_ਸੁਨੇਹਾ_Box_Button_ਅੰਕੜੇ button = messageboxdata->buttons[i];

            ਅਚਲ ਪੂਰਨ created = EM_ASM_INT({
                    var dialog_id = UTF8_ਮੰਜ਼ਿਲ_String($0);
                    var ਪਾਠ = UTF8_ਮੰਜ਼ਿਲ_String($1);
                    var responseId = $2;
                    var clickOnReturn = $3;
                    var clickOnEscape = $4;
                    var border = UTF8_ਮੰਜ਼ਿਲ_String($5);
                    var background = UTF8_ਮੰਜ਼ਿਲ_String($6);
                    var hovered = UTF8_ਮੰਜ਼ਿਲ_String($7);

                    var dialog = document.getElementById(dialog_id);
                    ਜੇ (!dialog) {
                        ਵਾਪਸ false;
                    }

                    var button = document.createElement("button");
                    button.inner_ਪਾਠ = ਪਾਠ;
                    button.style.borderColor = border;
                    button.style.backgroundColor = background;

                    dialog.ਜੋੜੋ_Event_Listener('keydown', function(e) {
                        ਜੇ (clickOnReturn && e.ਕੁੰਜੀ === "Enter") {
                            e.preventDefault();
                            button.click();
                        } ਨਹੀਂਤਾਂ ਜੇ (clickOnEscape && e.ਕੁੰਜੀ === "Escape") {
                            e.preventDefault();
                            button.click();
                        }
                    });
                    dialog.ਜੋੜੋ_Event_Listener('cancel', function(e){
                        e.preventDefault();
                    });

                    button.onmouseenter = function(e){
                        button.style.backgroundColor = hovered;
                    };
                    button.onmouseleave = function(e){
                        button.style.backgroundColor = background;
                    };
                    button.onclick = function(e) {
                        dialog.close(responseId);
                    };

                    dialog.append(button);
                    ਵਾਪਸ true;
                },
                dialog_id,
                button.ਪਾਠ,
                button.buttonID,
                button.flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
                button.flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
                button_border,
                button_background,
                button_hovered
            );

            ਜੇ (!created) {
                ਵਾਪਸ false;
            }
        }

        ਜਦੋਂ (true) {
            // give back control to browser for screen refresh
            emscripten_sleep(0);

            ਅਚਲ ਪੂਰਨ dialog_open = EM_ASM_INT({
                var dialog_id = UTF8_ਮੰਜ਼ਿਲ_String($0);

                var dialog = document.getElementById(dialog_id);
                ਜੇ (!dialog) {
                    ਵਾਪਸ false;
                }
                ਵਾਪਸ dialog.open;
            }, dialog_id);

            ਜੇ (dialog_open) {
                ਜਾਰੀ;
            }

            *buttonID = EM_ASM_INT({
                var dialog_id = UTF8_ਮੰਜ਼ਿਲ_String($0);
                var dialog = document.getElementById(dialog_id);
                ਜੇ (!dialog) {
                    ਵਾਪਸ 0;
                }
                try
                {
                    ਵਾਪਸ parseInt(dialog.return_ਮੁੱਲ);
                }
                catch(e)
                {
                    ਵਾਪਸ 0;
                }
            }, dialog_id);
            ਰੋਕੋ;
        }

    } ਨਹੀਂਤਾਂ {
        // Cannot add elements to DOM and block without Asyncify. So, fall back to the alert function.
        EM_ASM({
            alert(UTF8_ਮੰਜ਼ਿਲ_String($0) + "\n\n" + UTF8_ਮੰਜ਼ਿਲ_String($1));
        }, messageboxdata->title, messageboxdata->ਸੁਨੇਹਾ);
    }
    ਵਾਪਸ true;
}

VideoBootStrap Emscripten_bootstrap = {
    EMSCRIPTENVID_DRIVER_NAME, "SDL emscripten video driver",
    Emscripten_CreateDevice,
    Emscripten_ShowMessagebox,
    false
};

bool Emscripten_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;

    // Use a fake 32-bpp desktop mode
    SDL_zero(ਬਹੁਲਕ);
    ਬਹੁਲਕ.format = SDL_PIXELFORMAT_RGBA32;
    emscripten_get_screen_ਮਾਪ(&ਬਹੁਲਕ.w, &ਬਹੁਲਕ.h);
    ਬਹੁਲਕ.pixel_density = emscripten_get_device_pixel_ਅਨੁਪਾਤ();

    ਜੇ (SDL_ਜੋੜੋ_Basic_Video_Display(&ਬਹੁਲਕ) == 0) {
        ਵਾਪਸ false;
    }

    Emscripten_InitMouse();

    // Assume we have a mouse and keyboard
    SDL_ਜੋੜੋ_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ਨਿਰਾ);
    SDL_ਜੋੜੋ_Mouse(SDL_DEFAULT_MOUSE_ID, ਨਿਰਾ);

    Emscripten_ਰਜਿਸਟਰ_Global_Event_Handlers(_this);

    // We're done!
    ਵਾਪਸ true;
}

ਸਥਿਰ bool Emscripten_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    // can't do this
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ Emscripten_VideoQuit(SDL_VideoDevice *_this)
{
    Emscripten_UnregisterGlobalEventHandlers(_this);
    Emscripten_QuitMouse();
    Emscripten_UnlistenSystemTheme();
    pumpevents_has_ਲੜੀਵਾਰ = false;
    pending_ਅਦਲਾ_ਬਦਲੀ_interval = -1;
}

ਸਥਿਰ bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ਜੇ (rect) {
        rect->x = 0;
        rect->y = 0;
        rect->w = MAIN_THREAD_EM_ASM_INT({
            ਵਾਪਸ ਖਿੜਕੀ.inner_ਚੌੜਾਈ;
        });
        rect->h = MAIN_THREAD_EM_ASM_INT({
            ਵਾਪਸ ਖਿੜਕੀ.inner_ਉਚਾਈ;
        });
    }
    ਵਾਪਸ true;
}

bool Emscripten_Should_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(ਪੂਰਨ interval)
{
    ਜੇ (!pumpevents_has_ਲੜੀਵਾਰ) {
        pending_ਅਦਲਾ_ਬਦਲੀ_interval = interval;
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

ਪੂਰਨ Emscripten_Get_Pending_ਅਦਲਾ_ਬਦਲੀ_Interval(ਖਾਲੀ)
{
    ਵਾਪਸ pending_ਅਦਲਾ_ਬਦਲੀ_interval;
}

ਸਥਿਰ ਖਾਲੀ Emscripten_PumpEvents(SDL_VideoDevice *_this)
{
    ਜੇ (!pumpevents_has_ਲੜੀਵਾਰ) {
        // we assume you've set a mainloop by the time you've called pumpevents, so we delay initial SetInterval changes until then.
        // otherwise you'll get a warning on the javascript console.
        pumpevents_has_ਲੜੀਵਾਰ = true;
        ਜੇ (pending_ਅਦਲਾ_ਬਦਲੀ_interval >= 0) {
            Emscripten_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(_this, pending_ਅਦਲਾ_ਬਦਲੀ_interval);
            pending_ਅਦਲਾ_ਬਦਲੀ_interval = -1;
        }
    }
}

EMSCRIPTEN_KEEPALIVE ਖਾਲੀ requestFullscreenThroughSDL(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(ਖਿੜਕੀ, true);
}

ਸਥਿਰ bool Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Fill_Document(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool fill)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (fill && Emscripten_fill_document_ਖਿੜਕੀ && (Emscripten_fill_document_ਖਿੜਕੀ != ਖਿੜਕੀ)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Only one fill-document window allowed at a time.");
    }

    // fill_document takes up the entire page and resizes as the browser window resizes.
    ਜੇ (fill) {
        Emscripten_fill_document_ਖਿੜਕੀ = ਖਿੜਕੀ;

        ਅਚਲ ਪੂਰਨ w = MAIN_THREAD_EM_ASM_INT({ ਵਾਪਸ ਖਿੜਕੀ.inner_ਚੌੜਾਈ; });
        ਅਚਲ ਪੂਰਨ h = MAIN_THREAD_EM_ASM_INT({ ਵਾਪਸ ਖਿੜਕੀ.inner_ਉਚਾਈ; });
        ਅਚਲ ਦੁੱਗਣਾ scaled_w = w * wdata->pixel_ਅਨੁਪਾਤ;
        ਅਚਲ ਦੁੱਗਣਾ scaled_h = h * wdata->pixel_ਅਨੁਪਾਤ;

        wdata->non_fill_document_ਚੌੜਾਈ = ਖਿੜਕੀ->w;
        wdata->non_fill_document_ਉਚਾਈ = ਖਿੜਕੀ->h;

        MAIN_THREAD_EM_ASM({
            var canvas = document.querySelector(UTF8_ਮੰਜ਼ਿਲ_String($0));
            canvas.SDL3_original_position = canvas.style.position;
            canvas.SDL3_original_ਸਿਖਰ = canvas.style.ਸਿਖਰ;
            canvas.SDL3_original_ਖੱਬਾ = canvas.style.ਖੱਬਾ;

            // hide everything on the page that isn't the canvas.
            var div = document.createElement('div');
            div.id = 'SDL3_fill_document_background_elements';

            div.SDL3_canvas = canvas;
            div.SDL3_canvas_ਮਾਪਾ = canvas.ਮਾਪਾ_ਗੰਢ;
            div.SDL3_canvas_nextsib = canvas.ਅਗਲਾ_Sibling;

            var children = Array.from(document.body.children);
            ਲਈ (var ਬੱਚਾ ਦਾ children) {
                div.append_ਬੱਚਾ(ਬੱਚਾ);
            }
            document.body.append_ਬੱਚਾ(div);
            div.style.display = 'none';
            document.body.append_ਬੱਚਾ(canvas);
            canvas.style.position = 'fixed';
            canvas.style.ਸਿਖਰ = '0';
            canvas.style.ਖੱਬਾ = '0';
        }, wdata->canvas_id);

        emscripten_ਸੈੱਟ_canvas_element_ਮਾਪ(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // set_canvas_size unsets this
        ਜੇ (wdata->pixel_ਅਨੁਪਾਤ != 1.0f) {
            emscripten_ਸੈੱਟ_element_css_ਮਾਪ(wdata->canvas_id, w, h);
        }

        // force the event to trigger, so pixel ratio changes can be handled
        ਖਿੜਕੀ->w = ਖਿੜਕੀ->h = 0;
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ bool transitioning = (Emscripten_fill_document_ਖਿੜਕੀ == ਖਿੜਕੀ);
        ਜੇ (transitioning) {
            MAIN_THREAD_EM_ASM({
                // if we had previously hidden everything behind a fill_document window, put it back.
                var div = document.getElementById('SDL3_fill_document_background_elements');
                ਜੇ (div) {
                    ਜੇ (div.SDL3_canvas_nextsib) {
                        div.SDL3_canvas_ਮਾਪਾ.ਪਾਓ_Before(div.SDL3_canvas, div.SDL3_canvas_nextsib);
                    } ਨਹੀਂਤਾਂ {
                        div.SDL3_canvas_ਮਾਪਾ.append_ਬੱਚਾ(div.SDL3_canvas);
                    }
                    ਜਦੋਂ (div.ਪਹਿਲਾ_ਬੱਚਾ_2) {
                        document.body.ਪਾਓ_Before(div.ਪਹਿਲਾ_ਬੱਚਾ_2, div);
                    }
                    div.SDL3_canvas.style.position = div.SDL3_canvas.SDL3_original_position;
                    div.SDL3_canvas.style.ਸਿਖਰ = div.SDL3_canvas.SDL3_original_ਸਿਖਰ;
                    div.SDL3_canvas.style.ਖੱਬਾ = div.SDL3_canvas.SDL3_original_ਖੱਬਾ;
                    div.remove();
                }
            });
            Emscripten_fill_document_ਖਿੜਕੀ = ਨਿਰਾ;
        }

        ਖਿੜਕੀ->w = wdata->non_fill_document_ਚੌੜਾਈ;
        ਖਿੜਕੀ->h = wdata->non_fill_document_ਉਚਾਈ;
        ਅਚਲ ਦੁੱਗਣਾ scaled_w = SDL_floor(ਖਿੜਕੀ->w * wdata->pixel_ਅਨੁਪਾਤ);
        ਅਚਲ ਦੁੱਗਣਾ scaled_h = SDL_floor(ਖਿੜਕੀ->h * wdata->pixel_ਅਨੁਪਾਤ);
        emscripten_ਸੈੱਟ_canvas_element_ਮਾਪ(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // if the size is not being controlled by css, we need to scale down for hidpi
        ਜੇ (!wdata->external_ਮਾਪ && (wdata->pixel_ਅਨੁਪਾਤ != 1.0f)) {
            // scale canvas down
            emscripten_ਸੈੱਟ_element_css_ਮਾਪ(wdata->canvas_id, ਖਿੜਕੀ->w, ਖਿੜਕੀ->h);
        }

        ਜੇ (transitioning) {
            ਖਿੜਕੀ->w = ਖਿੜਕੀ->h = 0;
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, wdata->non_fill_document_ਚੌੜਾਈ, wdata->non_fill_document_ਉਚਾਈ);
        }
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ bool Emscripten_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wdata;
    ਦੁੱਗਣਾ css_w, css_h;
    ਅਚਲ ਅੱਖਰ *selector;

    bool fill_document = ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FILL_DOCUMENT) != 0);
    ਜੇ (fill_document && Emscripten_fill_document_ਖਿੜਕੀ) {
        fill_document = false;  // only one allowed at a time.
        ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_FILL_DOCUMENT;   // !!! FIXME: should this fail instead?
    }

    // Allocate window internal data
    wdata = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ));
    ਜੇ (!wdata) {
        ਵਾਪਸ false;
    }

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR);
    ਜੇ (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_ਖਿੜਕੀ_CREATE_EMSCRIPTEN_CANVAS_ID_STRING, "#canvas");
    }
    wdata->canvas_id = SDL_strdup(selector);

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
    ਜੇ (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_ਖਿੜਕੀ_CREATE_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, "#window");
    }
    wdata->keyboard_element = SDL_strdup(selector);

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਉੱਚਾ_PIXEL_DENSITY) {
        wdata->pixel_ਅਨੁਪਾਤ = emscripten_get_device_pixel_ਅਨੁਪਾਤ();
    } ਨਹੀਂਤਾਂ {
        wdata->pixel_ਅਨੁਪਾਤ = 1.0f;
    }

    // set a fake size to check if there is any CSS sizing the canvas
    emscripten_ਸੈੱਟ_canvas_element_ਮਾਪ(wdata->canvas_id, 1, 1);
    emscripten_get_element_css_ਮਾਪ(wdata->canvas_id, &css_w, &css_h);

    wdata->external_ਮਾਪ = SDL_floor(css_w) != 1 || SDL_floor(css_h) != 1;
    ਜੇ (wdata->external_ਮਾਪ) {
        fill_document = false;  // can't be resizable if something else is controlling it.
        ਖਿੜਕੀ->w = (ਪੂਰਨ) css_w;
        ਖਿੜਕੀ->h = (ਪੂਰਨ) css_h;
    }

    wdata->ਖਿੜਕੀ = ਖਿੜਕੀ;

    // Setup driver data for this window
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = wdata;

    wdata->non_fill_document_ਚੌੜਾਈ = ਖਿੜਕੀ->w;
    wdata->non_fill_document_ਉਚਾਈ = ਖਿੜਕੀ->h;
    Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Fill_Document(_this, ਖਿੜਕੀ, fill_document);

    // One window, it always has focus
    SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ);
    SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);

    Emscripten_ਰਜਿਸਟਰ_Event_Handlers(wdata);

    // Make the emscripten "fullscreen" button go through SDL.
    MAIN_THREAD_EM_ASM({
        Module['requestFullscreen'] = function(ਤਾਲਾ_ਸੂਚਕ, resizeCanvas) {
            _requestFullscreenThroughSDL($0);
        };
    }, ਖਿੜਕੀ);

    // Ensure various things are added to the window's properties
    SDL_ਸੈੱਟ_String_Property(ਖਿੜਕੀ->props, SDL_PROP_ਖਿੜਕੀ_EMSCRIPTEN_CANVAS_ID_STRING, wdata->canvas_id);
    SDL_ਸੈੱਟ_String_Property(ਖਿੜਕੀ->props, SDL_PROP_ਖਿੜਕੀ_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, wdata->keyboard_element);

    // Window has been successfully created
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ, bool resizable)
{
    // this function just has to exist or the higher level won't let the window change its SDL_WINDOW_RESIZABLE flag.
}

ਸਥਿਰ ਖਾਲੀ Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        ਜੇ (ਖਿੜਕੀ == Emscripten_fill_document_ਖਿੜਕੀ) {
            ਵਾਪਸ;  // canvas size is being dictated by the browser window size, refuse request.
        }

        // update pixel ratio
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਉੱਚਾ_PIXEL_DENSITY) {
            ਅੰਕੜੇ->pixel_ਅਨੁਪਾਤ = emscripten_get_device_pixel_ਅਨੁਪਾਤ();
        }
        emscripten_ਸੈੱਟ_canvas_element_ਮਾਪ(ਅੰਕੜੇ->canvas_id, SDL_lroundf(ਖਿੜਕੀ->pending.w * ਅੰਕੜੇ->pixel_ਅਨੁਪਾਤ), SDL_lroundf(ਖਿੜਕੀ->pending.h * ਅੰਕੜੇ->pixel_ਅਨੁਪਾਤ));

        // scale canvas down
        ਜੇ (!ਅੰਕੜੇ->external_ਮਾਪ && ਅੰਕੜੇ->pixel_ਅਨੁਪਾਤ != 1.0f) {
            emscripten_ਸੈੱਟ_element_css_ਮਾਪ(ਅੰਕੜੇ->canvas_id, ਖਿੜਕੀ->pending.w, ਖਿੜਕੀ->pending.h);
        }

        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, ਖਿੜਕੀ->pending.w, ਖਿੜਕੀ->pending.h);
    }
}

ਸਥਿਰ ਖਾਲੀ Emscripten_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *w, ਪੂਰਨ *h)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;
    ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ) {
        ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        *w = SDL_lroundf(ਖਿੜਕੀ->w * ਅੰਕੜੇ->pixel_ਅਨੁਪਾਤ);
        *h = SDL_lroundf(ਖਿੜਕੀ->h * ਅੰਕੜੇ->pixel_ਅਨੁਪਾਤ);
    }
}

ਸਥਿਰ ਖਾਲੀ Emscripten_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;

    Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Fill_Document(_this, ਖਿੜਕੀ, false);

    ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ) {
        ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

        Emscripten_UnregisterEventHandlers(ਅੰਕੜੇ);

        // We can't destroy the canvas, so resize it to zero instead
        emscripten_ਸੈੱਟ_canvas_element_ਮਾਪ(ਅੰਕੜੇ->canvas_id, 0, 0);
        ਜੇ (ਅੰਕੜੇ->pixel_ਅਨੁਪਾਤ != 1.0f) {
            emscripten_ਸੈੱਟ_element_css_ਮਾਪ(ਅੰਕੜੇ->canvas_id, 1, 1);
        }
        SDL_free(ਅੰਕੜੇ->canvas_id);

        SDL_free(ਅੰਕੜੇ->keyboard_element);

        SDL_free(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
        ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    }

    MAIN_THREAD_EM_ASM({
        // just ignore clicks on the fullscreen button while there's no SDL window.
        Module['requestFullscreen'] = function(ਤਾਲਾ_ਸੂਚਕ, resizeCanvas) {};
    });
}

ਸਥਿਰ SDL_Fullscreen_ਨਤੀਜਾ Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;
    ਪੂਰਨ res = -1;

    ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ) {
        ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

        ਜੇ (ਅੰਕੜੇ->fullscreen_change_ਵਿੱਚ_ਤਰੱਕੀ) {
            ਵਾਪਸ SDL_FULLSCREEN_FAILED;;
        }

        EmscriptenFullscreenChangeEvent fsevent;
        ਜੇ (emscripten_get_fullscreen_ਸਥਿਤੀ(&fsevent) == EMSCRIPTEN_ਨਤੀਜਾ_SUCCESS) {
            ਜੇ ((fullscreen == SDL_FULLSCREEN_OP_ENTER) == fsevent.isFullscreen) {
                ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;  // already there.
            }
        }

        ਜੇ (fullscreen) {
            EmscriptenFullscreenStrategy strategy;
            bool is_fullscreen_desktop = !ਖਿੜਕੀ->fullscreen_exclusive;

            SDL_zero(strategy);
            strategy.scale_ਬਹੁਲਕ = is_fullscreen_desktop ? EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH : EMSCRIPTEN_FULLSCREEN_SCALE_ASPECT;

            ਜੇ (!is_fullscreen_desktop) {
                strategy.canvas_Resolution_Scale_ਬਹੁਲਕ = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
            } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਉੱਚਾ_PIXEL_DENSITY) {
                strategy.canvas_Resolution_Scale_ਬਹੁਲਕ = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF;
            } ਨਹੀਂਤਾਂ {
                strategy.canvas_Resolution_Scale_ਬਹੁਲਕ = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
            }

            strategy.filtering_ਬਹੁਲਕ = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;

            strategy.canvasResizedCallback = Emscripten_HandleCanvasResize;
            strategy.canvas_Resized_Callback_User_ਅੰਕੜੇ = ਅੰਕੜੇ;

            ਅੰਕੜੇ->fullscreen_ਬਹੁਲਕ_flags = (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN);
            ਅੰਕੜੇ->fullscreen_resize = is_fullscreen_desktop;

            res = emscripten_request_fullscreen_strategy(ਅੰਕੜੇ->canvas_id, 1, &strategy);
        } ਨਹੀਂਤਾਂ {
            res = emscripten_exit_fullscreen();
        }
    }

    ਜੇ (res == EMSCRIPTEN_ਨਤੀਜਾ_SUCCESS) {
        ਅੰਕੜੇ->fullscreen_change_ਵਿੱਚ_ਤਰੱਕੀ = true;   // even on success, this might animate to the new state.
        ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
    } ਨਹੀਂਤਾਂ ਜੇ (res == EMSCRIPTEN_ਨਤੀਜਾ_DEFERRED) {
        ਅੰਕੜੇ->fullscreen_change_ਵਿੱਚ_ਤਰੱਕੀ = true;
        ਵਾਪਸ SDL_FULLSCREEN_PENDING;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_FULLSCREEN_FAILED;
    }
}

ਸਥਿਰ ਖਾਲੀ Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    emscripten_ਸੈੱਟ_ਖਿੜਕੀ_title(ਖਿੜਕੀ->title);
}

ਸਥਿਰ bool Emscripten_ਸੈੱਟ_ਖਿੜਕੀ_Icon(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *icon)
{
    // Create dynamic memory stream for PNG encoding
    SDL_IOStream *ਧਾਰਾ = SDL_IOFromDynamicMem();
    ਜੇ (!ਧਾਰਾ) {
        ਵਾਪਸ false;
    }

    // Encode icon to PNG using SDL's native PNG encoder
    ਜੇ (!SDL_SavePNG_IO(icon, ਧਾਰਾ, false)) {
        SDL_CloseIO(ਧਾਰਾ);
        ਵਾਪਸ false;
    }

    // Get the PNG data from the stream
    ਖਾਲੀ *png_ਅੰਕੜੇ = SDL_Get_ਸੂਚਕ_Property(
        SDL_GetIOProperties(ਧਾਰਾ),
        SDL_PROP_IOSTREAM_DYNAMIC_ਸਮ੍ਰਿਤੀ_ਸੂਚਕ,
        ਨਿਰਾ
    );
    size_t png_ਮਾਪ = (size_t)SDL_GetIOSize(ਧਾਰਾ);

    // Pass PNG data to JavaScript
    MAIN_THREAD_EM_ASM({
        // Use `.slice` to make a copy of the data if we are dealing with a SharedArrayBuffer, or `.subarray` to create a
        // view into the existing buffer if its non-shared.
        var png_ਅੰਕੜੇ_2 = HEAPU8.ਬਫਰ_2 instanceof Array_ਬਫਰ ? HEAPU8.subarray($0, $0 + $1) : HEAPU8.ਟੁਕੜਾ($0, $0 + $1);

        var blob = new Blob([png_ਅੰਕੜੇ_2], {type: 'image/png'});
        var url = URL.createObjectURL(blob);

        // Set as favicon (create link element if it doesn't exist)
        var link = document.querySelector("link[rel~='icon']");
        ਜੇ (!link) {
            link = document.createElement('link');
            link.rel = 'icon';
            link.type = 'image/png';
            document.ਸਿਰ.append_ਬੱਚਾ(link);
        }

        // Revoke old URL if it exists to prevent memory leaks
        ਜੇ (link.href && link.href.startsWith('blob:')) {
            URL.revokeObjectURL(link.href);
        }

        link.href = url;
    }, png_ਅੰਕੜੇ, png_ਮਾਪ);

    SDL_CloseIO(ਧਾਰਾ);
    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_EMSCRIPTEN
