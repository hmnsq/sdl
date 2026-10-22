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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_EMSCRIPTEN

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_pixels_c.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../SDL_hints_c.h"

#అన్తర్భావ "SDL_emscriptenvideo.h"
#అన్తర్భావ "SDL_emscriptenopengles.h"
#అన్తర్భావ "SDL_emscriptenframebuffer.h"
#అన్తర్భావ "SDL_emscriptenevents.h"
#అన్తర్భావ "SDL_emscriptenmouse.h"

#నిర్వచించు EMSCRIPTENVID_DRIVER_NAME "emscripten"

// Initialization/Query functions
స్థిర bool Emscripten_VideoInit(SDL_VideoDevice *_this);
స్థిర bool Emscripten_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);
స్థిర శూన్య Emscripten_VideoQuit(SDL_VideoDevice *_this);
స్థిర bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

స్థిర bool Emscripten_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
స్థిర శూన్య Emscripten_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
స్థిర శూన్య Emscripten_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ, bool resizable);
స్థిర శూన్య Emscripten_Get_కిటికీ_కొలత_లోపల_Pixels(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *w, పూర్ణాంకం *h);
స్థిర శూన్య Emscripten_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
స్థిర SDL_Fullscreen_ఫలితం Emscripten_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
స్థిర శూన్య Emscripten_PumpEvents(SDL_VideoDevice *_this);
స్థిర శూన్య Emscripten_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
స్థిర bool Emscripten_సమితి_కిటికీ_Icon(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *icon);
స్థిర bool Emscripten_సమితి_కిటికీ_Fill_Document(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool fill);

SDL_కిటికీ *Emscripten_fill_document_కిటికీ = ఖాళీ;

స్థిర bool pumpevents_has_నిరంతరం = false;
స్థిర పూర్ణాంకం pending_మార్పిడి_interval = -1;

// Emscripten driver bootstrap functions

స్థిర శూన్య Emscripten_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

స్థిర SDL_SystemTheme Emscripten_GetSystemTheme(శూన్య)
{
    /* Technically, light theme can mean explicit light theme or no preference.
       https://developer.mozilla.org/en-US/docs/Web/CSS/@media/prefers-color-scheme#syntax */

    పూర్ణాంకం theme_సంకేతం = MAIN_THREAD_EM_ASM_INT({
        ఒకవేళ (!కిటికీ.సరిపోలిక_Media) {
            తిరిగి -1;
        }

        ఒకవేళ (కిటికీ.సరిపోలిక_Media('(prefers-color-scheme: light)').matches) {
            తిరిగి 0;
        }

        ఒకవేళ (కిటికీ.సరిపోలిక_Media('(prefers-color-scheme: dark)').matches) {
            తిరిగి 1;
        }

        తిరిగి -1;
    });

    ఎంపిక (theme_సంకేతం) {
    స్థితి 0:
        తిరిగి SDL_SYSTEM_THEME_LIGHT;

    స్థితి 1:
        తిరిగి SDL_SYSTEM_THEME_DARK;

    అప్రమేయ:
        తిరిగి SDL_SYSTEM_THEME_UNKNOWN;
    }
}

స్థిర శూన్య Emscripten_ListenSystemTheme(శూన్య)
{
    MAIN_THREAD_EM_ASM({
        ఒకవేళ (కిటికీ.సరిపోలిక_Media) {
            var SDL3 = Module['SDL3'];

            SDL3.event_Handler_Theme_మారింది = function(event) {
                Emscripten_Send_System_Theme_మారింది_Event();
            };

            SDL3.theme_మారింది_సరిపోలిక_Media = కిటికీ.సరిపోలిక_Media('(prefers-color-scheme: dark)');
            SDL3.theme_మారింది_సరిపోలిక_Media.కూడు_Event_Listener('change', SDL3.event_Handler_Theme_మారింది);
        }
    });
}

స్థిర శూన్య Emscripten_UnlistenSystemTheme(శూన్య)
{
    MAIN_THREAD_EM_ASM({
        ఒకవేళ (typeof(Module['SDL3']) !== 'undefined') {
            var SDL3 = Module['SDL3'];

            SDL3.theme_మారింది_సరిపోలిక_Media.removeEventListener('change', SDL3.event_Handler_Theme_మారింది);
            SDL3.theme_మారింది_సరిపోలిక_Media = undefined;
            SDL3.event_Handler_Theme_మారింది = undefined;
        }
    });
}

EMSCRIPTEN_KEEPALIVE శూన్య Emscripten_Send_System_Theme_మారింది_Event_2(శూన్య)
{
    SDL_సమితి_System_Theme(Emscripten_GetSystemTheme());
}

స్థిర SDL_VideoDevice *Emscripten_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    /* Firefox sends blur event which would otherwise prevent full screen
     * when the user clicks to allow full screen.
     * See https://bugzilla.mozilla.org/show_bug.cgi?id=1144964
     */
    SDL_సమితి_Hint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

    // Set the function pointers
    device->VideoInit = Emscripten_VideoInit;
    device->VideoQuit = Emscripten_VideoQuit;
    device->GetDisplayUsableBounds = Emscripten_GetDisplayUsableBounds;
    device->సమితి_Display_బహుళకం = Emscripten_సమితి_Display_బహుళకం;

    device->PumpEvents = Emscripten_PumpEvents;

    device->CreateSDLWindow = Emscripten_Create_కిటికీ;
    device->సమితి_కిటికీ_Title = Emscripten_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_Icon = Emscripten_సమితి_కిటికీ_Icon;
    /*device->SetWindowPosition = Emscripten_SetWindowPosition;*/
    device->సమితి_కిటికీ_కొలత = Emscripten_సమితి_కిటికీ_కొలత;
    device->సమితి_కిటికీ_Resizable = Emscripten_సమితి_కిటికీ_Resizable;
    /*device->ShowWindow = Emscripten_ShowWindow;
    device->HideWindow = Emscripten_HideWindow;
    device->RaiseWindow = Emscripten_RaiseWindow;
    device->MaximizeWindow = Emscripten_MaximizeWindow;
    device->MinimizeWindow = Emscripten_MinimizeWindow;
    device->RestoreWindow = Emscripten_RestoreWindow;
    device->SetWindowMouseGrab = Emscripten_SetWindowMouseGrab;*/
    device->Get_కిటికీ_కొలత_లోపల_Pixels = Emscripten_Get_కిటికీ_కొలత_లోపల_Pixels;
    device->Destroy_కిటికీ = Emscripten_Destroy_కిటికీ;
    device->సమితి_కిటికీ_Fullscreen = Emscripten_సమితి_కిటికీ_Fullscreen;
    device->సమితి_కిటికీ_Fill_Document = Emscripten_సమితి_కిటికీ_Fill_Document;

    device->Create_కిటికీ_Framebuffer = Emscripten_Create_కిటికీ_Framebuffer;
    device->Update_కిటికీ_Framebuffer = Emscripten_Update_కిటికీ_Framebuffer;
    device->Destroy_కిటికీ_Framebuffer = Emscripten_Destroy_కిటికీ_Framebuffer;

    device->GL_ఎక్కించు_Library = Emscripten_GLES_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = Emscripten_GLES_Get_Proc_చిరునామా;
    device->GL_UnloadLibrary = Emscripten_GLES_UnloadLibrary;
    device->GL_CreateContext = Emscripten_GLES_CreateContext;
    device->GL_MakeCurrent = Emscripten_GLES_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = Emscripten_GLES_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = Emscripten_GLES_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = Emscripten_GLES_మార్పిడి_కిటికీ;
    device->GL_DestroyContext = Emscripten_GLES_DestroyContext;

    device->విడుదల = Emscripten_DeleteDevice;

    Emscripten_ListenSystemTheme();
    device->system_theme = Emscripten_GetSystemTheme();

    తిరిగి device;
}

స్థిర bool Emscripten_ShowMessagebox(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonID) {
    ఒకవేళ (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        అక్షరం dialog_background[32];
        అక్షరం dialog_color[32];
        అక్షరం button_border[32];
        అక్షరం button_background[32];
        అక్షరం button_hovered[32];

        ఒకవేళ (messageboxdata->colorScheme) {
            SDL_సందేశం_Box_Color color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND];
            SDL_snprintf(dialog_background, పరిమాణం(dialog_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_పాఠ్యం];
            SDL_snprintf(dialog_color, పరిమాణం(dialog_color), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER];
            SDL_snprintf(button_border, పరిమాణం(button_border), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND];
            SDL_snprintf(button_background, పరిమాణం(button_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED];
            SDL_snprintf(button_hovered, పరిమాణం(button_hovered), "rgb(%u, %u, %u)", color.r, color.g, color.b);
        } లేకపోతే {
            SDL_zero(dialog_background);
            SDL_zero(dialog_color);
            SDL_zero(button_border);
            SDL_zero(button_background);
            SDL_zero(button_hovered);
        }

        // TODO: Handle parent window when multiple windows can be added in Emscripten builds
        అక్షరం dialog_id[64];
        SDL_snprintf(dialog_id, పరిమాణం(dialog_id), "SDL3_messagebox_%u", SDL_rand_బిట్లు());
        EM_ASM({
            var title = UTF8_గమ్యం_String($0);
            var సందేశం = UTF8_గమ్యం_String($1);
            var background = UTF8_గమ్యం_String($2);
            var color = UTF8_గమ్యం_String($3);
            var id = UTF8_గమ్యం_String($4);

            // Dialogs are always put in the front of the DOM
            var dialog = document.createElement("dialog");
            // Set class to allow for CSS selectors
            dialog.classList.కూడు("SDL3_messagebox");
            dialog.id = id;
            dialog.style.color = color;
            dialog.style.backgroundColor = background;
            document.body.append(dialog);

            var h1 = document.createElement("h1");
            h1.inner_పాఠ్యం = title;
            dialog.append(h1);

            var p = document.createElement("p");
            p.inner_పాఠ్యం = సందేశం;
            dialog.append(p);

            dialog.showModal();
        }, messageboxdata->title, messageboxdata->సందేశం, dialog_background, dialog_color, dialog_id);

        పూర్ణాంకం i;
        కొరకు (i = 0; i < messageboxdata->numbuttons; ++i) {
            SDL_సందేశం_Box_Button_దత్తాంశం button = messageboxdata->buttons[i];

            స్థిరరాశి పూర్ణాంకం created = EM_ASM_INT({
                    var dialog_id = UTF8_గమ్యం_String($0);
                    var పాఠ్యం = UTF8_గమ్యం_String($1);
                    var responseId = $2;
                    var clickOnReturn = $3;
                    var clickOnEscape = $4;
                    var border = UTF8_గమ్యం_String($5);
                    var background = UTF8_గమ్యం_String($6);
                    var hovered = UTF8_గమ్యం_String($7);

                    var dialog = document.getElementById(dialog_id);
                    ఒకవేళ (!dialog) {
                        తిరిగి false;
                    }

                    var button = document.createElement("button");
                    button.inner_పాఠ్యం = పాఠ్యం;
                    button.style.borderColor = border;
                    button.style.backgroundColor = background;

                    dialog.కూడు_Event_Listener('keydown', function(e) {
                        ఒకవేళ (clickOnReturn && e.కీలకం === "Enter") {
                            e.preventDefault();
                            button.click();
                        } లేకపోతే ఒకవేళ (clickOnEscape && e.కీలకం === "Escape") {
                            e.preventDefault();
                            button.click();
                        }
                    });
                    dialog.కూడు_Event_Listener('cancel', function(e){
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
                    తిరిగి true;
                },
                dialog_id,
                button.పాఠ్యం,
                button.buttonID,
                button.flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
                button.flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
                button_border,
                button_background,
                button_hovered
            );

            ఒకవేళ (!created) {
                తిరిగి false;
            }
        }

        అయితే (true) {
            // give back control to browser for screen refresh
            emscripten_sleep(0);

            స్థిరరాశి పూర్ణాంకం dialog_open = EM_ASM_INT({
                var dialog_id = UTF8_గమ్యం_String($0);

                var dialog = document.getElementById(dialog_id);
                ఒకవేళ (!dialog) {
                    తిరిగి false;
                }
                తిరిగి dialog.open;
            }, dialog_id);

            ఒకవేళ (dialog_open) {
                కొనసాగు;
            }

            *buttonID = EM_ASM_INT({
                var dialog_id = UTF8_గమ్యం_String($0);
                var dialog = document.getElementById(dialog_id);
                ఒకవేళ (!dialog) {
                    తిరిగి 0;
                }
                try
                {
                    తిరిగి parseInt(dialog.return_విలువ);
                }
                catch(e)
                {
                    తిరిగి 0;
                }
            }, dialog_id);
            ఆపు;
        }

    } లేకపోతే {
        // Cannot add elements to DOM and block without Asyncify. So, fall back to the alert function.
        EM_ASM({
            alert(UTF8_గమ్యం_String($0) + "\n\n" + UTF8_గమ్యం_String($1));
        }, messageboxdata->title, messageboxdata->సందేశం);
    }
    తిరిగి true;
}

VideoBootStrap Emscripten_bootstrap = {
    EMSCRIPTENVID_DRIVER_NAME, "SDL emscripten video driver",
    Emscripten_CreateDevice,
    Emscripten_ShowMessagebox,
    false
};

bool Emscripten_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_బహుళకం బహుళకం;

    // Use a fake 32-bpp desktop mode
    SDL_zero(బహుళకం);
    బహుళకం.format = SDL_PIXELFORMAT_RGBA32;
    emscripten_get_screen_కొలత(&బహుళకం.w, &బహుళకం.h);
    బహుళకం.pixel_density = emscripten_get_device_pixel_నిష్పత్తి();

    ఒకవేళ (SDL_కూడు_Basic_Video_Display(&బహుళకం) == 0) {
        తిరిగి false;
    }

    Emscripten_InitMouse();

    // Assume we have a mouse and keyboard
    SDL_కూడు_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ఖాళీ);
    SDL_కూడు_Mouse(SDL_DEFAULT_MOUSE_ID, ఖాళీ);

    Emscripten_రిజిస్టరు_Global_Event_Handlers(_this);

    // We're done!
    తిరిగి true;
}

స్థిర bool Emscripten_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం)
{
    // can't do this
    తిరిగి true;
}

స్థిర శూన్య Emscripten_VideoQuit(SDL_VideoDevice *_this)
{
    Emscripten_UnregisterGlobalEventHandlers(_this);
    Emscripten_QuitMouse();
    Emscripten_UnlistenSystemTheme();
    pumpevents_has_నిరంతరం = false;
    pending_మార్పిడి_interval = -1;
}

స్థిర bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ఒకవేళ (rect) {
        rect->x = 0;
        rect->y = 0;
        rect->w = MAIN_THREAD_EM_ASM_INT({
            తిరిగి కిటికీ.inner_వెడల్పు;
        });
        rect->h = MAIN_THREAD_EM_ASM_INT({
            తిరిగి కిటికీ.inner_ఎత్తు;
        });
    }
    తిరిగి true;
}

bool Emscripten_Should_సమితి_మార్పిడి_Interval(పూర్ణాంకం interval)
{
    ఒకవేళ (!pumpevents_has_నిరంతరం) {
        pending_మార్పిడి_interval = interval;
        తిరిగి false;
    }
    తిరిగి true;
}

పూర్ణాంకం Emscripten_Get_Pending_మార్పిడి_Interval(శూన్య)
{
    తిరిగి pending_మార్పిడి_interval;
}

స్థిర శూన్య Emscripten_PumpEvents(SDL_VideoDevice *_this)
{
    ఒకవేళ (!pumpevents_has_నిరంతరం) {
        // we assume you've set a mainloop by the time you've called pumpevents, so we delay initial SetInterval changes until then.
        // otherwise you'll get a warning on the javascript console.
        pumpevents_has_నిరంతరం = true;
        ఒకవేళ (pending_మార్పిడి_interval >= 0) {
            Emscripten_GLES_సమితి_మార్పిడి_Interval(_this, pending_మార్పిడి_interval);
            pending_మార్పిడి_interval = -1;
        }
    }
}

EMSCRIPTEN_KEEPALIVE శూన్య requestFullscreenThroughSDL(SDL_కిటికీ *కిటికీ)
{
    SDL_సమితి_కిటికీ_Fullscreen(కిటికీ, true);
}

స్థిర bool Emscripten_సమితి_కిటికీ_Fill_Document(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool fill)
{
    SDL_కిటికీ_దత్తాంశం *wdata = కిటికీ->అంతర్గత;

    ఒకవేళ (fill && Emscripten_fill_document_కిటికీ && (Emscripten_fill_document_కిటికీ != కిటికీ)) {
        తిరిగి SDL_సమితి_Error("Only one fill-document window allowed at a time.");
    }

    // fill_document takes up the entire page and resizes as the browser window resizes.
    ఒకవేళ (fill) {
        Emscripten_fill_document_కిటికీ = కిటికీ;

        స్థిరరాశి పూర్ణాంకం w = MAIN_THREAD_EM_ASM_INT({ తిరిగి కిటికీ.inner_వెడల్పు; });
        స్థిరరాశి పూర్ణాంకం h = MAIN_THREAD_EM_ASM_INT({ తిరిగి కిటికీ.inner_ఎత్తు; });
        స్థిరరాశి ద్విగుణ scaled_w = w * wdata->pixel_నిష్పత్తి;
        స్థిరరాశి ద్విగుణ scaled_h = h * wdata->pixel_నిష్పత్తి;

        wdata->non_fill_document_వెడల్పు = కిటికీ->w;
        wdata->non_fill_document_ఎత్తు = కిటికీ->h;

        MAIN_THREAD_EM_ASM({
            var canvas = document.querySelector(UTF8_గమ్యం_String($0));
            canvas.SDL3_original_position = canvas.style.position;
            canvas.SDL3_original_శిఖరం = canvas.style.శిఖరం;
            canvas.SDL3_original_ఎడమ = canvas.style.ఎడమ;

            // hide everything on the page that isn't the canvas.
            var div = document.createElement('div');
            div.id = 'SDL3_fill_document_background_elements';

            div.SDL3_canvas = canvas;
            div.SDL3_canvas_మాతృ = canvas.మాతృ_కణుపు;
            div.SDL3_canvas_nextsib = canvas.తదుపరి_Sibling;

            var children = Array.from(document.body.children);
            కొరకు (var బిడ్డ యొక్క children) {
                div.append_బిడ్డ(బిడ్డ);
            }
            document.body.append_బిడ్డ(div);
            div.style.display = 'none';
            document.body.append_బిడ్డ(canvas);
            canvas.style.position = 'fixed';
            canvas.style.శిఖరం = '0';
            canvas.style.ఎడమ = '0';
        }, wdata->canvas_id);

        emscripten_సమితి_canvas_element_కొలత(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // set_canvas_size unsets this
        ఒకవేళ (wdata->pixel_నిష్పత్తి != 1.0f) {
            emscripten_సమితి_element_css_కొలత(wdata->canvas_id, w, h);
        }

        // force the event to trigger, so pixel ratio changes can be handled
        కిటికీ->w = కిటికీ->h = 0;
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    } లేకపోతే {
        స్థిరరాశి bool transitioning = (Emscripten_fill_document_కిటికీ == కిటికీ);
        ఒకవేళ (transitioning) {
            MAIN_THREAD_EM_ASM({
                // if we had previously hidden everything behind a fill_document window, put it back.
                var div = document.getElementById('SDL3_fill_document_background_elements');
                ఒకవేళ (div) {
                    ఒకవేళ (div.SDL3_canvas_nextsib) {
                        div.SDL3_canvas_మాతృ.చొప్పించు_Before(div.SDL3_canvas, div.SDL3_canvas_nextsib);
                    } లేకపోతే {
                        div.SDL3_canvas_మాతృ.append_బిడ్డ(div.SDL3_canvas);
                    }
                    అయితే (div.మొదటి_బిడ్డ_2) {
                        document.body.చొప్పించు_Before(div.మొదటి_బిడ్డ_2, div);
                    }
                    div.SDL3_canvas.style.position = div.SDL3_canvas.SDL3_original_position;
                    div.SDL3_canvas.style.శిఖరం = div.SDL3_canvas.SDL3_original_శిఖరం;
                    div.SDL3_canvas.style.ఎడమ = div.SDL3_canvas.SDL3_original_ఎడమ;
                    div.remove();
                }
            });
            Emscripten_fill_document_కిటికీ = ఖాళీ;
        }

        కిటికీ->w = wdata->non_fill_document_వెడల్పు;
        కిటికీ->h = wdata->non_fill_document_ఎత్తు;
        స్థిరరాశి ద్విగుణ scaled_w = SDL_floor(కిటికీ->w * wdata->pixel_నిష్పత్తి);
        స్థిరరాశి ద్విగుణ scaled_h = SDL_floor(కిటికీ->h * wdata->pixel_నిష్పత్తి);
        emscripten_సమితి_canvas_element_కొలత(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // if the size is not being controlled by css, we need to scale down for hidpi
        ఒకవేళ (!wdata->external_కొలత && (wdata->pixel_నిష్పత్తి != 1.0f)) {
            // scale canvas down
            emscripten_సమితి_element_css_కొలత(wdata->canvas_id, కిటికీ->w, కిటికీ->h);
        }

        ఒకవేళ (transitioning) {
            కిటికీ->w = కిటికీ->h = 0;
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, wdata->non_fill_document_వెడల్పు, wdata->non_fill_document_ఎత్తు);
        }
    }

    తిరిగి true;
}

స్థిర bool Emscripten_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
{
    SDL_కిటికీ_దత్తాంశం *wdata;
    ద్విగుణ css_w, css_h;
    స్థిరరాశి అక్షరం *selector;

    bool fill_document = ((కిటికీ->flags & SDL_కిటికీ_FILL_DOCUMENT) != 0);
    ఒకవేళ (fill_document && Emscripten_fill_document_కిటికీ) {
        fill_document = false;  // only one allowed at a time.
        కిటికీ->flags &= ~SDL_కిటికీ_FILL_DOCUMENT;   // !!! FIXME: should this fail instead?
    }

    // Allocate window internal data
    wdata = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_కిటికీ_దత్తాంశం));
    ఒకవేళ (!wdata) {
        తిరిగి false;
    }

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR);
    ఒకవేళ (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_కిటికీ_CREATE_EMSCRIPTEN_CANVAS_ID_STRING, "#canvas");
    }
    wdata->canvas_id = SDL_strdup(selector);

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
    ఒకవేళ (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_కిటికీ_CREATE_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, "#window");
    }
    wdata->keyboard_element = SDL_strdup(selector);

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_ఎగువ_PIXEL_DENSITY) {
        wdata->pixel_నిష్పత్తి = emscripten_get_device_pixel_నిష్పత్తి();
    } లేకపోతే {
        wdata->pixel_నిష్పత్తి = 1.0f;
    }

    // set a fake size to check if there is any CSS sizing the canvas
    emscripten_సమితి_canvas_element_కొలత(wdata->canvas_id, 1, 1);
    emscripten_get_element_css_కొలత(wdata->canvas_id, &css_w, &css_h);

    wdata->external_కొలత = SDL_floor(css_w) != 1 || SDL_floor(css_h) != 1;
    ఒకవేళ (wdata->external_కొలత) {
        fill_document = false;  // can't be resizable if something else is controlling it.
        కిటికీ->w = (పూర్ణాంకం) css_w;
        కిటికీ->h = (పూర్ణాంకం) css_h;
    }

    wdata->కిటికీ = కిటికీ;

    // Setup driver data for this window
    కిటికీ->అంతర్గత = wdata;

    wdata->non_fill_document_వెడల్పు = కిటికీ->w;
    wdata->non_fill_document_ఎత్తు = కిటికీ->h;
    Emscripten_సమితి_కిటికీ_Fill_Document(_this, కిటికీ, fill_document);

    // One window, it always has focus
    SDL_సమితి_Mouse_Focus(కిటికీ);
    SDL_సమితి_Keyboard_Focus(కిటికీ);

    Emscripten_రిజిస్టరు_Event_Handlers(wdata);

    // Make the emscripten "fullscreen" button go through SDL.
    MAIN_THREAD_EM_ASM({
        Module['requestFullscreen'] = function(తాళం_సూచిక, resizeCanvas) {
            _requestFullscreenThroughSDL($0);
        };
    }, కిటికీ);

    // Ensure various things are added to the window's properties
    SDL_సమితి_String_Property(కిటికీ->props, SDL_PROP_కిటికీ_EMSCRIPTEN_CANVAS_ID_STRING, wdata->canvas_id);
    SDL_సమితి_String_Property(కిటికీ->props, SDL_PROP_కిటికీ_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, wdata->keyboard_element);

    // Window has been successfully created
    తిరిగి true;
}

స్థిర శూన్య Emscripten_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ, bool resizable)
{
    // this function just has to exist or the higher level won't let the window change its SDL_WINDOW_RESIZABLE flag.
}

స్థిర శూన్య Emscripten_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (కిటికీ->అంతర్గత) {
        SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
        ఒకవేళ (కిటికీ == Emscripten_fill_document_కిటికీ) {
            తిరిగి;  // canvas size is being dictated by the browser window size, refuse request.
        }

        // update pixel ratio
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_ఎగువ_PIXEL_DENSITY) {
            దత్తాంశం->pixel_నిష్పత్తి = emscripten_get_device_pixel_నిష్పత్తి();
        }
        emscripten_సమితి_canvas_element_కొలత(దత్తాంశం->canvas_id, SDL_lroundf(కిటికీ->pending.w * దత్తాంశం->pixel_నిష్పత్తి), SDL_lroundf(కిటికీ->pending.h * దత్తాంశం->pixel_నిష్పత్తి));

        // scale canvas down
        ఒకవేళ (!దత్తాంశం->external_కొలత && దత్తాంశం->pixel_నిష్పత్తి != 1.0f) {
            emscripten_సమితి_element_css_కొలత(దత్తాంశం->canvas_id, కిటికీ->pending.w, కిటికీ->pending.h);
        }

        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, కిటికీ->pending.w, కిటికీ->pending.h);
    }
}

స్థిర శూన్య Emscripten_Get_కిటికీ_కొలత_లోపల_Pixels(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *w, పూర్ణాంకం *h)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;
    ఒకవేళ (కిటికీ->అంతర్గత) {
        దత్తాంశం = కిటికీ->అంతర్గత;
        *w = SDL_lroundf(కిటికీ->w * దత్తాంశం->pixel_నిష్పత్తి);
        *h = SDL_lroundf(కిటికీ->h * దత్తాంశం->pixel_నిష్పత్తి);
    }
}

స్థిర శూన్య Emscripten_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;

    Emscripten_సమితి_కిటికీ_Fill_Document(_this, కిటికీ, false);

    ఒకవేళ (కిటికీ->అంతర్గత) {
        దత్తాంశం = కిటికీ->అంతర్గత;

        Emscripten_UnregisterEventHandlers(దత్తాంశం);

        // We can't destroy the canvas, so resize it to zero instead
        emscripten_సమితి_canvas_element_కొలత(దత్తాంశం->canvas_id, 0, 0);
        ఒకవేళ (దత్తాంశం->pixel_నిష్పత్తి != 1.0f) {
            emscripten_సమితి_element_css_కొలత(దత్తాంశం->canvas_id, 1, 1);
        }
        SDL_free(దత్తాంశం->canvas_id);

        SDL_free(దత్తాంశం->keyboard_element);

        SDL_free(కిటికీ->అంతర్గత);
        కిటికీ->అంతర్గత = ఖాళీ;
    }

    MAIN_THREAD_EM_ASM({
        // just ignore clicks on the fullscreen button while there's no SDL window.
        Module['requestFullscreen'] = function(తాళం_సూచిక, resizeCanvas) {};
    });
}

స్థిర SDL_Fullscreen_ఫలితం Emscripten_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;
    పూర్ణాంకం res = -1;

    ఒకవేళ (కిటికీ->అంతర్గత) {
        దత్తాంశం = కిటికీ->అంతర్గత;

        ఒకవేళ (దత్తాంశం->fullscreen_change_లోపల_పురోగతి) {
            తిరిగి SDL_FULLSCREEN_FAILED;;
        }

        EmscriptenFullscreenChangeEvent fsevent;
        ఒకవేళ (emscripten_get_fullscreen_స్థితి(&fsevent) == EMSCRIPTEN_ఫలితం_SUCCESS) {
            ఒకవేళ ((fullscreen == SDL_FULLSCREEN_OP_ENTER) == fsevent.isFullscreen) {
                తిరిగి SDL_FULLSCREEN_SUCCEEDED;  // already there.
            }
        }

        ఒకవేళ (fullscreen) {
            EmscriptenFullscreenStrategy strategy;
            bool is_fullscreen_desktop = !కిటికీ->fullscreen_exclusive;

            SDL_zero(strategy);
            strategy.scale_బహుళకం = is_fullscreen_desktop ? EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH : EMSCRIPTEN_FULLSCREEN_SCALE_ASPECT;

            ఒకవేళ (!is_fullscreen_desktop) {
                strategy.canvas_Resolution_Scale_బహుళకం = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
            } లేకపోతే ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_ఎగువ_PIXEL_DENSITY) {
                strategy.canvas_Resolution_Scale_బహుళకం = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF;
            } లేకపోతే {
                strategy.canvas_Resolution_Scale_బహుళకం = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
            }

            strategy.filtering_బహుళకం = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;

            strategy.canvasResizedCallback = Emscripten_HandleCanvasResize;
            strategy.canvas_Resized_Callback_User_దత్తాంశం = దత్తాంశం;

            దత్తాంశం->fullscreen_బహుళకం_flags = (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN);
            దత్తాంశం->fullscreen_resize = is_fullscreen_desktop;

            res = emscripten_request_fullscreen_strategy(దత్తాంశం->canvas_id, 1, &strategy);
        } లేకపోతే {
            res = emscripten_exit_fullscreen();
        }
    }

    ఒకవేళ (res == EMSCRIPTEN_ఫలితం_SUCCESS) {
        దత్తాంశం->fullscreen_change_లోపల_పురోగతి = true;   // even on success, this might animate to the new state.
        తిరిగి SDL_FULLSCREEN_SUCCEEDED;
    } లేకపోతే ఒకవేళ (res == EMSCRIPTEN_ఫలితం_DEFERRED) {
        దత్తాంశం->fullscreen_change_లోపల_పురోగతి = true;
        తిరిగి SDL_FULLSCREEN_PENDING;
    } లేకపోతే {
        తిరిగి SDL_FULLSCREEN_FAILED;
    }
}

స్థిర శూన్య Emscripten_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    emscripten_సమితి_కిటికీ_title(కిటికీ->title);
}

స్థిర bool Emscripten_సమితి_కిటికీ_Icon(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *icon)
{
    // Create dynamic memory stream for PNG encoding
    SDL_IOStream *ప్రవాహం = SDL_IOFromDynamicMem();
    ఒకవేళ (!ప్రవాహం) {
        తిరిగి false;
    }

    // Encode icon to PNG using SDL's native PNG encoder
    ఒకవేళ (!SDL_SavePNG_IO(icon, ప్రవాహం, false)) {
        SDL_CloseIO(ప్రవాహం);
        తిరిగి false;
    }

    // Get the PNG data from the stream
    శూన్య *png_దత్తాంశం = SDL_Get_సూచిక_Property(
        SDL_GetIOProperties(ప్రవాహం),
        SDL_PROP_IOSTREAM_DYNAMIC_జ్ఞాపకం_సూచిక,
        ఖాళీ
    );
    size_t png_కొలత = (size_t)SDL_GetIOSize(ప్రవాహం);

    // Pass PNG data to JavaScript
    MAIN_THREAD_EM_ASM({
        // Use `.slice` to make a copy of the data if we are dealing with a SharedArrayBuffer, or `.subarray` to create a
        // view into the existing buffer if its non-shared.
        var png_దత్తాంశం_2 = HEAPU8.బఫరు_2 instanceof Array_బఫరు ? HEAPU8.subarray($0, $0 + $1) : HEAPU8.ముక్క($0, $0 + $1);

        var blob = new Blob([png_దత్తాంశం_2], {type: 'image/png'});
        var url = URL.createObjectURL(blob);

        // Set as favicon (create link element if it doesn't exist)
        var link = document.querySelector("link[rel~='icon']");
        ఒకవేళ (!link) {
            link = document.createElement('link');
            link.rel = 'icon';
            link.type = 'image/png';
            document.తల.append_బిడ్డ(link);
        }

        // Revoke old URL if it exists to prevent memory leaks
        ఒకవేళ (link.href && link.href.startsWith('blob:')) {
            URL.revokeObjectURL(link.href);
        }

        link.href = url;
    }, png_దత్తాంశం, png_కొలత);

    SDL_CloseIO(ప్రవాహం);
    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_EMSCRIPTEN
