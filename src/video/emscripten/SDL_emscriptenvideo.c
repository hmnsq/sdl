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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_EMSCRIPTEN

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../SDL_hints_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_emscriptenvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_emscriptenopengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_emscriptenframebuffer.h"
#ಅನ್ತರ್ಭಾವ "SDL_emscriptenevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_emscriptenmouse.h"

#ವ್ಯಾಖ್ಯಾನಿಸು EMSCRIPTENVID_DRIVER_NAME "emscripten"

// Initialization/Query functions
ಸ್ಥಿರ bool Emscripten_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ bool Emscripten_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_VideoQuit(SDL_VideoDevice *_this);
ಸ್ಥಿರ bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

ಸ್ಥಿರ bool Emscripten_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ, bool resizable);
ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *w, ಪೂರ್ಣಾಂಕ *h);
ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಸ್ಥಿರ SDL_Fullscreen_ಫಲಿತಾಂಶ Emscripten_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_PumpEvents(SDL_VideoDevice *_this);
ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಸ್ಥಿರ bool Emscripten_ಗಣ_ಕಿಟಕಿ_Icon(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *icon);
ಸ್ಥಿರ bool Emscripten_ಗಣ_ಕಿಟಕಿ_Fill_Document(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool fill);

SDL_ಕಿಟಕಿ *Emscripten_fill_document_ಕಿಟಕಿ = ಖಾಲಿ;

ಸ್ಥಿರ bool pumpevents_has_ಸತತ = false;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ pending_ಅದಲುಬದಲು_interval = -1;

// Emscripten driver bootstrap functions

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ಸ್ಥಿರ SDL_SystemTheme Emscripten_GetSystemTheme(ಶೂನ್ಯ)
{
    /* Technically, light theme can mean explicit light theme or no preference.
       https://developer.mozilla.org/en-US/docs/Web/CSS/@media/prefers-color-scheme#syntax */

    ಪೂರ್ಣಾಂಕ theme_ಸಂಕೇತ = MAIN_THREAD_EM_ASM_INT({
        ಆದರೆ (!ಕಿಟಕಿ.ಹೊಂದಿಕೆ_Media) {
            ಹಿಂತಿರುಗಿ -1;
        }

        ಆದರೆ (ಕಿಟಕಿ.ಹೊಂದಿಕೆ_Media('(prefers-color-scheme: light)').matches) {
            ಹಿಂತಿರುಗಿ 0;
        }

        ಆದರೆ (ಕಿಟಕಿ.ಹೊಂದಿಕೆ_Media('(prefers-color-scheme: dark)').matches) {
            ಹಿಂತಿರುಗಿ 1;
        }

        ಹಿಂತಿರುಗಿ -1;
    });

    ಆಯ್ಕೆ (theme_ಸಂಕೇತ) {
    ಸ್ಥಿತಿ 0:
        ಹಿಂತಿರುಗಿ SDL_SYSTEM_THEME_LIGHT;

    ಸ್ಥಿತಿ 1:
        ಹಿಂತಿರುಗಿ SDL_SYSTEM_THEME_DARK;

    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_ListenSystemTheme(ಶೂನ್ಯ)
{
    MAIN_THREAD_EM_ASM({
        ಆದರೆ (ಕಿಟಕಿ.ಹೊಂದಿಕೆ_Media) {
            var SDL3 = Module['SDL3'];

            SDL3.event_Handler_Theme_ಬದಲಾಯಿತು = function(event) {
                Emscripten_Send_System_Theme_ಬದಲಾಯಿತು_Event();
            };

            SDL3.theme_ಬದಲಾಯಿತು_ಹೊಂದಿಕೆ_Media = ಕಿಟಕಿ.ಹೊಂದಿಕೆ_Media('(prefers-color-scheme: dark)');
            SDL3.theme_ಬದಲಾಯಿತು_ಹೊಂದಿಕೆ_Media.ಕೂಡಿಸು_Event_Listener('change', SDL3.event_Handler_Theme_ಬದಲಾಯಿತು);
        }
    });
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_UnlistenSystemTheme(ಶೂನ್ಯ)
{
    MAIN_THREAD_EM_ASM({
        ಆದರೆ (typeof(Module['SDL3']) !== 'undefined') {
            var SDL3 = Module['SDL3'];

            SDL3.theme_ಬದಲಾಯಿತು_ಹೊಂದಿಕೆ_Media.removeEventListener('change', SDL3.event_Handler_Theme_ಬದಲಾಯಿತು);
            SDL3.theme_ಬದಲಾಯಿತು_ಹೊಂದಿಕೆ_Media = undefined;
            SDL3.event_Handler_Theme_ಬದಲಾಯಿತು = undefined;
        }
    });
}

EMSCRIPTEN_KEEPALIVE ಶೂನ್ಯ Emscripten_Send_System_Theme_ಬದಲಾಯಿತು_Event_2(ಶೂನ್ಯ)
{
    SDL_ಗಣ_System_Theme(Emscripten_GetSystemTheme());
}

ಸ್ಥಿರ SDL_VideoDevice *Emscripten_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    /* Firefox sends blur event which would otherwise prevent full screen
     * when the user clicks to allow full screen.
     * See https://bugzilla.mozilla.org/show_bug.cgi?id=1144964
     */
    SDL_ಗಣ_Hint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

    // Set the function pointers
    device->VideoInit = Emscripten_VideoInit;
    device->VideoQuit = Emscripten_VideoQuit;
    device->GetDisplayUsableBounds = Emscripten_GetDisplayUsableBounds;
    device->ಗಣ_Display_ಬಹುಲಕ = Emscripten_ಗಣ_Display_ಬಹುಲಕ;

    device->PumpEvents = Emscripten_PumpEvents;

    device->CreateSDLWindow = Emscripten_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Title = Emscripten_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_Icon = Emscripten_ಗಣ_ಕಿಟಕಿ_Icon;
    /*device->SetWindowPosition = Emscripten_SetWindowPosition;*/
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = Emscripten_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->ಗಣ_ಕಿಟಕಿ_Resizable = Emscripten_ಗಣ_ಕಿಟಕಿ_Resizable;
    /*device->ShowWindow = Emscripten_ShowWindow;
    device->HideWindow = Emscripten_HideWindow;
    device->RaiseWindow = Emscripten_RaiseWindow;
    device->MaximizeWindow = Emscripten_MaximizeWindow;
    device->MinimizeWindow = Emscripten_MinimizeWindow;
    device->RestoreWindow = Emscripten_RestoreWindow;
    device->SetWindowMouseGrab = Emscripten_SetWindowMouseGrab;*/
    device->Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels = Emscripten_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels;
    device->Destroy_ಕಿಟಕಿ = Emscripten_Destroy_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Fullscreen = Emscripten_ಗಣ_ಕಿಟಕಿ_Fullscreen;
    device->ಗಣ_ಕಿಟಕಿ_Fill_Document = Emscripten_ಗಣ_ಕಿಟಕಿ_Fill_Document;

    device->Create_ಕಿಟಕಿ_Framebuffer = Emscripten_Create_ಕಿಟಕಿ_Framebuffer;
    device->Update_ಕಿಟಕಿ_Framebuffer = Emscripten_Update_ಕಿಟಕಿ_Framebuffer;
    device->Destroy_ಕಿಟಕಿ_Framebuffer = Emscripten_Destroy_ಕಿಟಕಿ_Framebuffer;

    device->GL_ತುಂಬು_Library = Emscripten_GLES_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = Emscripten_GLES_Get_Proc_ವಿಳಾಸ;
    device->GL_UnloadLibrary = Emscripten_GLES_UnloadLibrary;
    device->GL_CreateContext = Emscripten_GLES_CreateContext;
    device->GL_MakeCurrent = Emscripten_GLES_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = Emscripten_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = Emscripten_GLES_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = Emscripten_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_DestroyContext = Emscripten_GLES_DestroyContext;

    device->ಬಿಡುಗಡೆ = Emscripten_DeleteDevice;

    Emscripten_ListenSystemTheme();
    device->system_theme = Emscripten_GetSystemTheme();

    ಹಿಂತಿರುಗಿ device;
}

ಸ್ಥಿರ bool Emscripten_ShowMessagebox(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonID) {
    ಆದರೆ (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        ಅಕ್ಷರ dialog_background[32];
        ಅಕ್ಷರ dialog_color[32];
        ಅಕ್ಷರ button_border[32];
        ಅಕ್ಷರ button_background[32];
        ಅಕ್ಷರ button_hovered[32];

        ಆದರೆ (messageboxdata->colorScheme) {
            SDL_ಸಂದೇಶ_Box_Color color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND];
            SDL_snprintf(dialog_background, ಗಾತ್ರ(dialog_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_ಪಠ್ಯ];
            SDL_snprintf(dialog_color, ಗಾತ್ರ(dialog_color), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER];
            SDL_snprintf(button_border, ಗಾತ್ರ(button_border), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND];
            SDL_snprintf(button_background, ಗಾತ್ರ(button_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED];
            SDL_snprintf(button_hovered, ಗಾತ್ರ(button_hovered), "rgb(%u, %u, %u)", color.r, color.g, color.b);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_zero(dialog_background);
            SDL_zero(dialog_color);
            SDL_zero(button_border);
            SDL_zero(button_background);
            SDL_zero(button_hovered);
        }

        // TODO: Handle parent window when multiple windows can be added in Emscripten builds
        ಅಕ್ಷರ dialog_id[64];
        SDL_snprintf(dialog_id, ಗಾತ್ರ(dialog_id), "SDL3_messagebox_%u", SDL_rand_ಬಿಟ್ಟುಗಳು());
        EM_ASM({
            var title = UTF8_ಗಮ್ಯ_String($0);
            var ಸಂದೇಶ = UTF8_ಗಮ್ಯ_String($1);
            var background = UTF8_ಗಮ್ಯ_String($2);
            var color = UTF8_ಗಮ್ಯ_String($3);
            var id = UTF8_ಗಮ್ಯ_String($4);

            // Dialogs are always put in the front of the DOM
            var dialog = document.createElement("dialog");
            // Set class to allow for CSS selectors
            dialog.classList.ಕೂಡಿಸು("SDL3_messagebox");
            dialog.id = id;
            dialog.style.color = color;
            dialog.style.backgroundColor = background;
            document.body.append(dialog);

            var h1 = document.createElement("h1");
            h1.inner_ಪಠ್ಯ = title;
            dialog.append(h1);

            var p = document.createElement("p");
            p.inner_ಪಠ್ಯ = ಸಂದೇಶ;
            dialog.append(p);

            dialog.showModal();
        }, messageboxdata->title, messageboxdata->ಸಂದೇಶ, dialog_background, dialog_color, dialog_id);

        ಪೂರ್ಣಾಂಕ i;
        ಗಾಗಿ (i = 0; i < messageboxdata->numbuttons; ++i) {
            SDL_ಸಂದೇಶ_Box_Button_ದತ್ತಾಂಶ button = messageboxdata->buttons[i];

            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ created = EM_ASM_INT({
                    var dialog_id = UTF8_ಗಮ್ಯ_String($0);
                    var ಪಠ್ಯ = UTF8_ಗಮ್ಯ_String($1);
                    var responseId = $2;
                    var clickOnReturn = $3;
                    var clickOnEscape = $4;
                    var border = UTF8_ಗಮ್ಯ_String($5);
                    var background = UTF8_ಗಮ್ಯ_String($6);
                    var hovered = UTF8_ಗಮ್ಯ_String($7);

                    var dialog = document.getElementById(dialog_id);
                    ಆದರೆ (!dialog) {
                        ಹಿಂತಿರುಗಿ false;
                    }

                    var button = document.createElement("button");
                    button.inner_ಪಠ್ಯ = ಪಠ್ಯ;
                    button.style.borderColor = border;
                    button.style.backgroundColor = background;

                    dialog.ಕೂಡಿಸು_Event_Listener('keydown', function(e) {
                        ಆದರೆ (clickOnReturn && e.ಕೀಲಿ === "Enter") {
                            e.preventDefault();
                            button.click();
                        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (clickOnEscape && e.ಕೀಲಿ === "Escape") {
                            e.preventDefault();
                            button.click();
                        }
                    });
                    dialog.ಕೂಡಿಸು_Event_Listener('cancel', function(e){
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
                    ಹಿಂತಿರುಗಿ true;
                },
                dialog_id,
                button.ಪಠ್ಯ,
                button.buttonID,
                button.flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
                button.flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
                button_border,
                button_background,
                button_hovered
            );

            ಆದರೆ (!created) {
                ಹಿಂತಿರುಗಿ false;
            }
        }

        ಆಗ (true) {
            // give back control to browser for screen refresh
            emscripten_sleep(0);

            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dialog_open = EM_ASM_INT({
                var dialog_id = UTF8_ಗಮ್ಯ_String($0);

                var dialog = document.getElementById(dialog_id);
                ಆದರೆ (!dialog) {
                    ಹಿಂತಿರುಗಿ false;
                }
                ಹಿಂತಿರುಗಿ dialog.open;
            }, dialog_id);

            ಆದರೆ (dialog_open) {
                ಮುಂದುವರಿ;
            }

            *buttonID = EM_ASM_INT({
                var dialog_id = UTF8_ಗಮ್ಯ_String($0);
                var dialog = document.getElementById(dialog_id);
                ಆದರೆ (!dialog) {
                    ಹಿಂತಿರುಗಿ 0;
                }
                try
                {
                    ಹಿಂತಿರುಗಿ parseInt(dialog.return_ಮೌಲ್ಯ);
                }
                catch(e)
                {
                    ಹಿಂತಿರುಗಿ 0;
                }
            }, dialog_id);
            ನಿಲ್ಲಿಸು;
        }

    } ಇಲ್ಲದಿದ್ದರೆ {
        // Cannot add elements to DOM and block without Asyncify. So, fall back to the alert function.
        EM_ASM({
            alert(UTF8_ಗಮ್ಯ_String($0) + "\n\n" + UTF8_ಗಮ್ಯ_String($1));
        }, messageboxdata->title, messageboxdata->ಸಂದೇಶ);
    }
    ಹಿಂತಿರುಗಿ true;
}

VideoBootStrap Emscripten_bootstrap = {
    EMSCRIPTENVID_DRIVER_NAME, "SDL emscripten video driver",
    Emscripten_CreateDevice,
    Emscripten_ShowMessagebox,
    false
};

bool Emscripten_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;

    // Use a fake 32-bpp desktop mode
    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ.format = SDL_PIXELFORMAT_RGBA32;
    emscripten_get_screen_ಗಾತ್ರ(&ಬಹುಲಕ.w, &ಬಹುಲಕ.h);
    ಬಹುಲಕ.pixel_density = emscripten_get_device_pixel_ಅನುಪಾತ();

    ಆದರೆ (SDL_ಕೂಡಿಸು_Basic_Video_Display(&ಬಹುಲಕ) == 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    Emscripten_InitMouse();

    // Assume we have a mouse and keyboard
    SDL_ಕೂಡಿಸು_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ಖಾಲಿ);
    SDL_ಕೂಡಿಸು_Mouse(SDL_DEFAULT_MOUSE_ID, ಖಾಲಿ);

    Emscripten_ರಿಜಿಸ್ಟರ್_Global_Event_Handlers(_this);

    // We're done!
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool Emscripten_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    // can't do this
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_VideoQuit(SDL_VideoDevice *_this)
{
    Emscripten_UnregisterGlobalEventHandlers(_this);
    Emscripten_QuitMouse();
    Emscripten_UnlistenSystemTheme();
    pumpevents_has_ಸತತ = false;
    pending_ಅದಲುಬದಲು_interval = -1;
}

ಸ್ಥಿರ bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ಆದರೆ (rect) {
        rect->x = 0;
        rect->y = 0;
        rect->w = MAIN_THREAD_EM_ASM_INT({
            ಹಿಂತಿರುಗಿ ಕಿಟಕಿ.inner_ಅಗಲ;
        });
        rect->h = MAIN_THREAD_EM_ASM_INT({
            ಹಿಂತಿರುಗಿ ಕಿಟಕಿ.inner_ಎತ್ತರ;
        });
    }
    ಹಿಂತಿರುಗಿ true;
}

bool Emscripten_Should_ಗಣ_ಅದಲುಬದಲು_Interval(ಪೂರ್ಣಾಂಕ interval)
{
    ಆದರೆ (!pumpevents_has_ಸತತ) {
        pending_ಅದಲುಬದಲು_interval = interval;
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

ಪೂರ್ಣಾಂಕ Emscripten_Get_Pending_ಅದಲುಬದಲು_Interval(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ pending_ಅದಲುಬದಲು_interval;
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_PumpEvents(SDL_VideoDevice *_this)
{
    ಆದರೆ (!pumpevents_has_ಸತತ) {
        // we assume you've set a mainloop by the time you've called pumpevents, so we delay initial SetInterval changes until then.
        // otherwise you'll get a warning on the javascript console.
        pumpevents_has_ಸತತ = true;
        ಆದರೆ (pending_ಅದಲುಬದಲು_interval >= 0) {
            Emscripten_GLES_ಗಣ_ಅದಲುಬದಲು_Interval(_this, pending_ಅದಲುಬದಲು_interval);
            pending_ಅದಲುಬದಲು_interval = -1;
        }
    }
}

EMSCRIPTEN_KEEPALIVE ಶೂನ್ಯ requestFullscreenThroughSDL(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಗಣ_ಕಿಟಕಿ_Fullscreen(ಕಿಟಕಿ, true);
}

ಸ್ಥಿರ bool Emscripten_ಗಣ_ಕಿಟಕಿ_Fill_Document(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool fill)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (fill && Emscripten_fill_document_ಕಿಟಕಿ && (Emscripten_fill_document_ಕಿಟಕಿ != ಕಿಟಕಿ)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Only one fill-document window allowed at a time.");
    }

    // fill_document takes up the entire page and resizes as the browser window resizes.
    ಆದರೆ (fill) {
        Emscripten_fill_document_ಕಿಟಕಿ = ಕಿಟಕಿ;

        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ w = MAIN_THREAD_EM_ASM_INT({ ಹಿಂತಿರುಗಿ ಕಿಟಕಿ.inner_ಅಗಲ; });
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ h = MAIN_THREAD_EM_ASM_INT({ ಹಿಂತಿರುಗಿ ಕಿಟಕಿ.inner_ಎತ್ತರ; });
        ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ scaled_w = w * wdata->pixel_ಅನುಪಾತ;
        ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ scaled_h = h * wdata->pixel_ಅನುಪಾತ;

        wdata->non_fill_document_ಅಗಲ = ಕಿಟಕಿ->w;
        wdata->non_fill_document_ಎತ್ತರ = ಕಿಟಕಿ->h;

        MAIN_THREAD_EM_ASM({
            var canvas = document.querySelector(UTF8_ಗಮ್ಯ_String($0));
            canvas.SDL3_original_position = canvas.style.position;
            canvas.SDL3_original_ತುದಿ = canvas.style.ತುದಿ;
            canvas.SDL3_original_ಎಡ = canvas.style.ಎಡ;

            // hide everything on the page that isn't the canvas.
            var div = document.createElement('div');
            div.id = 'SDL3_fill_document_background_elements';

            div.SDL3_canvas = canvas;
            div.SDL3_canvas_ಪೋಷಕ = canvas.ಪೋಷಕ_ಗಂಟು;
            div.SDL3_canvas_nextsib = canvas.ಮುಂದಿನ_Sibling;

            var children = Array.from(document.body.children);
            ಗಾಗಿ (var ಮಗು ದ children) {
                div.append_ಮಗು(ಮಗು);
            }
            document.body.append_ಮಗು(div);
            div.style.display = 'none';
            document.body.append_ಮಗು(canvas);
            canvas.style.position = 'fixed';
            canvas.style.ತುದಿ = '0';
            canvas.style.ಎಡ = '0';
        }, wdata->canvas_id);

        emscripten_ಗಣ_canvas_element_ಗಾತ್ರ(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // set_canvas_size unsets this
        ಆದರೆ (wdata->pixel_ಅನುಪಾತ != 1.0f) {
            emscripten_ಗಣ_element_css_ಗಾತ್ರ(wdata->canvas_id, w, h);
        }

        // force the event to trigger, so pixel ratio changes can be handled
        ಕಿಟಕಿ->w = ಕಿಟಕಿ->h = 0;
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ bool transitioning = (Emscripten_fill_document_ಕಿಟಕಿ == ಕಿಟಕಿ);
        ಆದರೆ (transitioning) {
            MAIN_THREAD_EM_ASM({
                // if we had previously hidden everything behind a fill_document window, put it back.
                var div = document.getElementById('SDL3_fill_document_background_elements');
                ಆದರೆ (div) {
                    ಆದರೆ (div.SDL3_canvas_nextsib) {
                        div.SDL3_canvas_ಪೋಷಕ.ಸೇರಿಸು_Before(div.SDL3_canvas, div.SDL3_canvas_nextsib);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        div.SDL3_canvas_ಪೋಷಕ.append_ಮಗು(div.SDL3_canvas);
                    }
                    ಆಗ (div.ಮೊದಲ_ಮಗು_2) {
                        document.body.ಸೇರಿಸು_Before(div.ಮೊದಲ_ಮಗು_2, div);
                    }
                    div.SDL3_canvas.style.position = div.SDL3_canvas.SDL3_original_position;
                    div.SDL3_canvas.style.ತುದಿ = div.SDL3_canvas.SDL3_original_ತುದಿ;
                    div.SDL3_canvas.style.ಎಡ = div.SDL3_canvas.SDL3_original_ಎಡ;
                    div.remove();
                }
            });
            Emscripten_fill_document_ಕಿಟಕಿ = ಖಾಲಿ;
        }

        ಕಿಟಕಿ->w = wdata->non_fill_document_ಅಗಲ;
        ಕಿಟಕಿ->h = wdata->non_fill_document_ಎತ್ತರ;
        ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ scaled_w = SDL_floor(ಕಿಟಕಿ->w * wdata->pixel_ಅನುಪಾತ);
        ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ scaled_h = SDL_floor(ಕಿಟಕಿ->h * wdata->pixel_ಅನುಪಾತ);
        emscripten_ಗಣ_canvas_element_ಗಾತ್ರ(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // if the size is not being controlled by css, we need to scale down for hidpi
        ಆದರೆ (!wdata->external_ಗಾತ್ರ && (wdata->pixel_ಅನುಪಾತ != 1.0f)) {
            // scale canvas down
            emscripten_ಗಣ_element_css_ಗಾತ್ರ(wdata->canvas_id, ಕಿಟಕಿ->w, ಕಿಟಕಿ->h);
        }

        ಆದರೆ (transitioning) {
            ಕಿಟಕಿ->w = ಕಿಟಕಿ->h = 0;
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, wdata->non_fill_document_ಅಗಲ, wdata->non_fill_document_ಎತ್ತರ);
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool Emscripten_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata;
    ದ್ವಿಗುಣ css_w, css_h;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *selector;

    bool fill_document = ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FILL_DOCUMENT) != 0);
    ಆದರೆ (fill_document && Emscripten_fill_document_ಕಿಟಕಿ) {
        fill_document = false;  // only one allowed at a time.
        ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_FILL_DOCUMENT;   // !!! FIXME: should this fail instead?
    }

    // Allocate window internal data
    wdata = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ));
    ಆದರೆ (!wdata) {
        ಹಿಂತಿರುಗಿ false;
    }

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR);
    ಆದರೆ (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_ಕಿಟಕಿ_CREATE_EMSCRIPTEN_CANVAS_ID_STRING, "#canvas");
    }
    wdata->canvas_id = SDL_strdup(selector);

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
    ಆದರೆ (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_ಕಿಟಕಿ_CREATE_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, "#window");
    }
    wdata->keyboard_element = SDL_strdup(selector);

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಮೇಲಿನ_PIXEL_DENSITY) {
        wdata->pixel_ಅನುಪಾತ = emscripten_get_device_pixel_ಅನುಪಾತ();
    } ಇಲ್ಲದಿದ್ದರೆ {
        wdata->pixel_ಅನುಪಾತ = 1.0f;
    }

    // set a fake size to check if there is any CSS sizing the canvas
    emscripten_ಗಣ_canvas_element_ಗಾತ್ರ(wdata->canvas_id, 1, 1);
    emscripten_get_element_css_ಗಾತ್ರ(wdata->canvas_id, &css_w, &css_h);

    wdata->external_ಗಾತ್ರ = SDL_floor(css_w) != 1 || SDL_floor(css_h) != 1;
    ಆದರೆ (wdata->external_ಗಾತ್ರ) {
        fill_document = false;  // can't be resizable if something else is controlling it.
        ಕಿಟಕಿ->w = (ಪೂರ್ಣಾಂಕ) css_w;
        ಕಿಟಕಿ->h = (ಪೂರ್ಣಾಂಕ) css_h;
    }

    wdata->ಕಿಟಕಿ = ಕಿಟಕಿ;

    // Setup driver data for this window
    ಕಿಟಕಿ->ಆಂತರಿಕ = wdata;

    wdata->non_fill_document_ಅಗಲ = ಕಿಟಕಿ->w;
    wdata->non_fill_document_ಎತ್ತರ = ಕಿಟಕಿ->h;
    Emscripten_ಗಣ_ಕಿಟಕಿ_Fill_Document(_this, ಕಿಟಕಿ, fill_document);

    // One window, it always has focus
    SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ);
    SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);

    Emscripten_ರಿಜಿಸ್ಟರ್_Event_Handlers(wdata);

    // Make the emscripten "fullscreen" button go through SDL.
    MAIN_THREAD_EM_ASM({
        Module['requestFullscreen'] = function(ಬೀಗ_ಸೂಚಕ, resizeCanvas) {
            _requestFullscreenThroughSDL($0);
        };
    }, ಕಿಟಕಿ);

    // Ensure various things are added to the window's properties
    SDL_ಗಣ_String_Property(ಕಿಟಕಿ->props, SDL_PROP_ಕಿಟಕಿ_EMSCRIPTEN_CANVAS_ID_STRING, wdata->canvas_id);
    SDL_ಗಣ_String_Property(ಕಿಟಕಿ->props, SDL_PROP_ಕಿಟಕಿ_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, wdata->keyboard_element);

    // Window has been successfully created
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ, bool resizable)
{
    // this function just has to exist or the higher level won't let the window change its SDL_WINDOW_RESIZABLE flag.
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
        ಆದರೆ (ಕಿಟಕಿ == Emscripten_fill_document_ಕಿಟಕಿ) {
            ಹಿಂತಿರುಗಿ;  // canvas size is being dictated by the browser window size, refuse request.
        }

        // update pixel ratio
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಮೇಲಿನ_PIXEL_DENSITY) {
            ದತ್ತಾಂಶ->pixel_ಅನುಪಾತ = emscripten_get_device_pixel_ಅನುಪಾತ();
        }
        emscripten_ಗಣ_canvas_element_ಗಾತ್ರ(ದತ್ತಾಂಶ->canvas_id, SDL_lroundf(ಕಿಟಕಿ->pending.w * ದತ್ತಾಂಶ->pixel_ಅನುಪಾತ), SDL_lroundf(ಕಿಟಕಿ->pending.h * ದತ್ತಾಂಶ->pixel_ಅನುಪಾತ));

        // scale canvas down
        ಆದರೆ (!ದತ್ತಾಂಶ->external_ಗಾತ್ರ && ದತ್ತಾಂಶ->pixel_ಅನುಪಾತ != 1.0f) {
            emscripten_ಗಣ_element_css_ಗಾತ್ರ(ದತ್ತಾಂಶ->canvas_id, ಕಿಟಕಿ->pending.w, ಕಿಟಕಿ->pending.h);
        }

        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, ಕಿಟಕಿ->pending.w, ಕಿಟಕಿ->pending.h);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *w, ಪೂರ್ಣಾಂಕ *h)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ) {
        ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
        *w = SDL_lroundf(ಕಿಟಕಿ->w * ದತ್ತಾಂಶ->pixel_ಅನುಪಾತ);
        *h = SDL_lroundf(ಕಿಟಕಿ->h * ದತ್ತಾಂಶ->pixel_ಅನುಪಾತ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    Emscripten_ಗಣ_ಕಿಟಕಿ_Fill_Document(_this, ಕಿಟಕಿ, false);

    ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ) {
        ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

        Emscripten_UnregisterEventHandlers(ದತ್ತಾಂಶ);

        // We can't destroy the canvas, so resize it to zero instead
        emscripten_ಗಣ_canvas_element_ಗಾತ್ರ(ದತ್ತಾಂಶ->canvas_id, 0, 0);
        ಆದರೆ (ದತ್ತಾಂಶ->pixel_ಅನುಪಾತ != 1.0f) {
            emscripten_ಗಣ_element_css_ಗಾತ್ರ(ದತ್ತಾಂಶ->canvas_id, 1, 1);
        }
        SDL_free(ದತ್ತಾಂಶ->canvas_id);

        SDL_free(ದತ್ತಾಂಶ->keyboard_element);

        SDL_free(ಕಿಟಕಿ->ಆಂತರಿಕ);
        ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
    }

    MAIN_THREAD_EM_ASM({
        // just ignore clicks on the fullscreen button while there's no SDL window.
        Module['requestFullscreen'] = function(ಬೀಗ_ಸೂಚಕ, resizeCanvas) {};
    });
}

ಸ್ಥಿರ SDL_Fullscreen_ಫಲಿತಾಂಶ Emscripten_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ res = -1;

    ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ) {
        ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

        ಆದರೆ (ದತ್ತಾಂಶ->fullscreen_change_ಒಳ_ಪ್ರಗತಿ) {
            ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_FAILED;;
        }

        EmscriptenFullscreenChangeEvent fsevent;
        ಆದರೆ (emscripten_get_fullscreen_ಸ್ಥಿತಿ(&fsevent) == EMSCRIPTEN_ಫಲಿತಾಂಶ_SUCCESS) {
            ಆದರೆ ((fullscreen == SDL_FULLSCREEN_OP_ENTER) == fsevent.isFullscreen) {
                ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;  // already there.
            }
        }

        ಆದರೆ (fullscreen) {
            EmscriptenFullscreenStrategy strategy;
            bool is_fullscreen_desktop = !ಕಿಟಕಿ->fullscreen_exclusive;

            SDL_zero(strategy);
            strategy.scale_ಬಹುಲಕ = is_fullscreen_desktop ? EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH : EMSCRIPTEN_FULLSCREEN_SCALE_ASPECT;

            ಆದರೆ (!is_fullscreen_desktop) {
                strategy.canvas_Resolution_Scale_ಬಹುಲಕ = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಮೇಲಿನ_PIXEL_DENSITY) {
                strategy.canvas_Resolution_Scale_ಬಹುಲಕ = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF;
            } ಇಲ್ಲದಿದ್ದರೆ {
                strategy.canvas_Resolution_Scale_ಬಹುಲಕ = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
            }

            strategy.filtering_ಬಹುಲಕ = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;

            strategy.canvasResizedCallback = Emscripten_HandleCanvasResize;
            strategy.canvas_Resized_Callback_User_ದತ್ತಾಂಶ = ದತ್ತಾಂಶ;

            ದತ್ತಾಂಶ->fullscreen_ಬಹುಲಕ_flags = (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN);
            ದತ್ತಾಂಶ->fullscreen_resize = is_fullscreen_desktop;

            res = emscripten_request_fullscreen_strategy(ದತ್ತಾಂಶ->canvas_id, 1, &strategy);
        } ಇಲ್ಲದಿದ್ದರೆ {
            res = emscripten_exit_fullscreen();
        }
    }

    ಆದರೆ (res == EMSCRIPTEN_ಫಲಿತಾಂಶ_SUCCESS) {
        ದತ್ತಾಂಶ->fullscreen_change_ಒಳ_ಪ್ರಗತಿ = true;   // even on success, this might animate to the new state.
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (res == EMSCRIPTEN_ಫಲಿತಾಂಶ_DEFERRED) {
        ದತ್ತಾಂಶ->fullscreen_change_ಒಳ_ಪ್ರಗತಿ = true;
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_PENDING;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_FAILED;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    emscripten_ಗಣ_ಕಿಟಕಿ_title(ಕಿಟಕಿ->title);
}

ಸ್ಥಿರ bool Emscripten_ಗಣ_ಕಿಟಕಿ_Icon(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *icon)
{
    // Create dynamic memory stream for PNG encoding
    SDL_IOStream *ಹರಿವು = SDL_IOFromDynamicMem();
    ಆದರೆ (!ಹರಿವು) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Encode icon to PNG using SDL's native PNG encoder
    ಆದರೆ (!SDL_SavePNG_IO(icon, ಹರಿವು, false)) {
        SDL_CloseIO(ಹರಿವು);
        ಹಿಂತಿರುಗಿ false;
    }

    // Get the PNG data from the stream
    ಶೂನ್ಯ *png_ದತ್ತಾಂಶ = SDL_Get_ಸೂಚಕ_Property(
        SDL_GetIOProperties(ಹರಿವು),
        SDL_PROP_IOSTREAM_DYNAMIC_ಸ್ಮರಣೆ_ಸೂಚಕ,
        ಖಾಲಿ
    );
    size_t png_ಗಾತ್ರ = (size_t)SDL_GetIOSize(ಹರಿವು);

    // Pass PNG data to JavaScript
    MAIN_THREAD_EM_ASM({
        // Use `.slice` to make a copy of the data if we are dealing with a SharedArrayBuffer, or `.subarray` to create a
        // view into the existing buffer if its non-shared.
        var png_ದತ್ತಾಂಶ_2 = HEAPU8.ಬಫರ್_2 instanceof Array_ಬಫರ್ ? HEAPU8.subarray($0, $0 + $1) : HEAPU8.ತುಂಡು($0, $0 + $1);

        var blob = new Blob([png_ದತ್ತಾಂಶ_2], {type: 'image/png'});
        var url = URL.createObjectURL(blob);

        // Set as favicon (create link element if it doesn't exist)
        var link = document.querySelector("link[rel~='icon']");
        ಆದರೆ (!link) {
            link = document.createElement('link');
            link.rel = 'icon';
            link.type = 'image/png';
            document.ತಲೆ.append_ಮಗು(link);
        }

        // Revoke old URL if it exists to prevent memory leaks
        ಆದರೆ (link.href && link.href.startsWith('blob:')) {
            URL.revokeObjectURL(link.href);
        }

        link.href = url;
    }, png_ದತ್ತಾಂಶ, png_ಗಾತ್ರ);

    SDL_CloseIO(ಹರಿವು);
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_EMSCRIPTEN
