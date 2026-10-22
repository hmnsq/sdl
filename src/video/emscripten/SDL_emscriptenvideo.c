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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_EMSCRIPTEN

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_pixels_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../SDL_hints_c.h"

#अन्तर्भाव "SDL_emscriptenvideo.h"
#अन्तर्भाव "SDL_emscriptenopengles.h"
#अन्तर्भाव "SDL_emscriptenframebuffer.h"
#अन्तर्भाव "SDL_emscriptenevents.h"
#अन्तर्भाव "SDL_emscriptenmouse.h"

#परिभाषय EMSCRIPTENVID_DRIVER_NAME "emscripten"

// Initialization/Query functions
स्थिर bool Emscripten_VideoInit(SDL_VideoDevice *_this);
स्थिर bool Emscripten_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्);
स्थिर शून्य Emscripten_VideoQuit(SDL_VideoDevice *_this);
स्थिर bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

स्थिर bool Emscripten_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
स्थिर शून्य Emscripten_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
स्थिर शून्य Emscripten_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः, bool resizable);
स्थिर शून्य Emscripten_Get_गवाक्षः_आकार_अन्तर्_Pixels(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *w, पूर्णाङ्क *h);
स्थिर शून्य Emscripten_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
स्थिर SDL_Fullscreen_परिणाम Emscripten_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
स्थिर शून्य Emscripten_PumpEvents(SDL_VideoDevice *_this);
स्थिर शून्य Emscripten_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
स्थिर bool Emscripten_समुच्चयः_गवाक्षः_Icon(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *icon);
स्थिर bool Emscripten_समुच्चयः_गवाक्षः_Fill_Document(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool fill);

SDL_गवाक्षः *Emscripten_fill_document_गवाक्षः = रिक्त;

स्थिर bool pumpevents_has_सततम् = false;
स्थिर पूर्णाङ्क pending_swap_interval = -1;

// Emscripten driver bootstrap functions

स्थिर शून्य Emscripten_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

स्थिर SDL_SystemTheme Emscripten_GetSystemTheme(शून्य)
{
    /* Technically, light theme can mean explicit light theme or no preference.
       https://developer.mozilla.org/en-US/docs/Web/CSS/@media/prefers-color-scheme#syntax */

    पूर्णाङ्क theme_संहिता = MAIN_THREAD_EM_ASM_INT({
        यदि (!गवाक्षः.मेलनम्_Media) {
            प्रत्यागम -1;
        }

        यदि (गवाक्षः.मेलनम्_Media('(prefers-color-scheme: light)').matches) {
            प्रत्यागम 0;
        }

        यदि (गवाक्षः.मेलनम्_Media('(prefers-color-scheme: dark)').matches) {
            प्रत्यागम 1;
        }

        प्रत्यागम -1;
    });

    विकल्प (theme_संहिता) {
    पक्ष 0:
        प्रत्यागम SDL_SYSTEM_THEME_LIGHT;

    पक्ष 1:
        प्रत्यागम SDL_SYSTEM_THEME_DARK;

    स्वभाव:
        प्रत्यागम SDL_SYSTEM_THEME_UNKNOWN;
    }
}

स्थिर शून्य Emscripten_ListenSystemTheme(शून्य)
{
    MAIN_THREAD_EM_ASM({
        यदि (गवाक्षः.मेलनम्_Media) {
            var SDL3 = Module['SDL3'];

            SDL3.event_Handler_Theme_परिवर्तितम् = function(event) {
                Emscripten_Send_System_Theme_परिवर्तितम्_Event();
            };

            SDL3.theme_परिवर्तितम्_मेलनम्_Media = गवाक्षः.मेलनम्_Media('(prefers-color-scheme: dark)');
            SDL3.theme_परिवर्तितम्_मेलनम्_Media.सङ्कलय_Event_Listener('change', SDL3.event_Handler_Theme_परिवर्तितम्);
        }
    });
}

स्थिर शून्य Emscripten_UnlistenSystemTheme(शून्य)
{
    MAIN_THREAD_EM_ASM({
        यदि (typeof(Module['SDL3']) !== 'undefined') {
            var SDL3 = Module['SDL3'];

            SDL3.theme_परिवर्तितम्_मेलनम्_Media.removeEventListener('change', SDL3.event_Handler_Theme_परिवर्तितम्);
            SDL3.theme_परिवर्तितम्_मेलनम्_Media = undefined;
            SDL3.event_Handler_Theme_परिवर्तितम् = undefined;
        }
    });
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_Send_System_Theme_परिवर्तितम्_Event_2(शून्य)
{
    SDL_समुच्चयः_System_Theme(Emscripten_GetSystemTheme());
}

स्थिर SDL_VideoDevice *Emscripten_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    /* Firefox sends blur event which would otherwise prevent full screen
     * when the user clicks to allow full screen.
     * See https://bugzilla.mozilla.org/show_bug.cgi?id=1144964
     */
    SDL_समुच्चयः_Hint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

    // Set the function pointers
    device->VideoInit = Emscripten_VideoInit;
    device->VideoQuit = Emscripten_VideoQuit;
    device->GetDisplayUsableBounds = Emscripten_GetDisplayUsableBounds;
    device->समुच्चयः_Display_बहुलकम् = Emscripten_समुच्चयः_Display_बहुलकम्;

    device->PumpEvents = Emscripten_PumpEvents;

    device->CreateSDLWindow = Emscripten_Create_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Title = Emscripten_समुच्चयः_गवाक्षः_Title;
    device->समुच्चयः_गवाक्षः_Icon = Emscripten_समुच्चयः_गवाक्षः_Icon;
    /*device->SetWindowPosition = Emscripten_SetWindowPosition;*/
    device->समुच्चयः_गवाक्षः_आकार = Emscripten_समुच्चयः_गवाक्षः_आकार;
    device->समुच्चयः_गवाक्षः_Resizable = Emscripten_समुच्चयः_गवाक्षः_Resizable;
    /*device->ShowWindow = Emscripten_ShowWindow;
    device->HideWindow = Emscripten_HideWindow;
    device->RaiseWindow = Emscripten_RaiseWindow;
    device->MaximizeWindow = Emscripten_MaximizeWindow;
    device->MinimizeWindow = Emscripten_MinimizeWindow;
    device->RestoreWindow = Emscripten_RestoreWindow;
    device->SetWindowMouseGrab = Emscripten_SetWindowMouseGrab;*/
    device->Get_गवाक्षः_आकार_अन्तर्_Pixels = Emscripten_Get_गवाक्षः_आकार_अन्तर्_Pixels;
    device->Destroy_गवाक्षः = Emscripten_Destroy_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Fullscreen = Emscripten_समुच्चयः_गवाक्षः_Fullscreen;
    device->समुच्चयः_गवाक्षः_Fill_Document = Emscripten_समुच्चयः_गवाक्षः_Fill_Document;

    device->Create_गवाक्षः_Framebuffer = Emscripten_Create_गवाक्षः_Framebuffer;
    device->Update_गवाक्षः_Framebuffer = Emscripten_Update_गवाक्षः_Framebuffer;
    device->Destroy_गवाक्षः_Framebuffer = Emscripten_Destroy_गवाक्षः_Framebuffer;

    device->GL_आरोपय_Library = Emscripten_GLES_आरोपय_Library;
    device->GL_Get_Proc_स्थानाङ्कः = Emscripten_GLES_Get_Proc_स्थानाङ्कः;
    device->GL_UnloadLibrary = Emscripten_GLES_UnloadLibrary;
    device->GL_CreateContext = Emscripten_GLES_CreateContext;
    device->GL_MakeCurrent = Emscripten_GLES_MakeCurrent;
    device->GL_समुच्चयः_Swap_Interval = Emscripten_GLES_समुच्चयः_Swap_Interval;
    device->GL_GetSwapInterval = Emscripten_GLES_GetSwapInterval;
    device->GL_Swap_गवाक्षः = Emscripten_GLES_Swap_गवाक्षः;
    device->GL_DestroyContext = Emscripten_GLES_DestroyContext;

    device->मुक्त = Emscripten_DeleteDevice;

    Emscripten_ListenSystemTheme();
    device->system_theme = Emscripten_GetSystemTheme();

    प्रत्यागम device;
}

स्थिर bool Emscripten_ShowMessagebox(ध्रुव SDL_सन्देशः_Box_दत्त *messageboxdata, पूर्णाङ्क *buttonID) {
    यदि (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        वर्ण dialog_background[32];
        वर्ण dialog_color[32];
        वर्ण button_border[32];
        वर्ण button_background[32];
        वर्ण button_hovered[32];

        यदि (messageboxdata->colorScheme) {
            SDL_सन्देशः_Box_Color color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND];
            SDL_snprintf(dialog_background, परिमाण(dialog_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT];
            SDL_snprintf(dialog_color, परिमाण(dialog_color), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER];
            SDL_snprintf(button_border, परिमाण(button_border), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND];
            SDL_snprintf(button_background, परिमाण(button_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED];
            SDL_snprintf(button_hovered, परिमाण(button_hovered), "rgb(%u, %u, %u)", color.r, color.g, color.b);
        } अन्यथा {
            SDL_zero(dialog_background);
            SDL_zero(dialog_color);
            SDL_zero(button_border);
            SDL_zero(button_background);
            SDL_zero(button_hovered);
        }

        // TODO: Handle parent window when multiple windows can be added in Emscripten builds
        वर्ण dialog_id[64];
        SDL_snprintf(dialog_id, परिमाण(dialog_id), "SDL3_messagebox_%u", SDL_rand_द्वयङ्काः());
        EM_ASM({
            var title = UTF8_गन्तव्यम्_String($0);
            var सन्देशः = UTF8_गन्तव्यम्_String($1);
            var background = UTF8_गन्तव्यम्_String($2);
            var color = UTF8_गन्तव्यम्_String($3);
            var id = UTF8_गन्तव्यम्_String($4);

            // Dialogs are always put in the front of the DOM
            var dialog = document.createElement("dialog");
            // Set class to allow for CSS selectors
            dialog.classList.सङ्कलय("SDL3_messagebox");
            dialog.id = id;
            dialog.style.color = color;
            dialog.style.backgroundColor = background;
            document.body.append(dialog);

            var h1 = document.createElement("h1");
            h1.innerText = title;
            dialog.append(h1);

            var p = document.createElement("p");
            p.innerText = सन्देशः;
            dialog.append(p);

            dialog.showModal();
        }, messageboxdata->title, messageboxdata->सन्देशः, dialog_background, dialog_color, dialog_id);

        पूर्णाङ्क i;
        प्रति (i = 0; i < messageboxdata->numbuttons; ++i) {
            SDL_सन्देशः_Box_Button_दत्त button = messageboxdata->buttons[i];

            ध्रुव पूर्णाङ्क created = EM_ASM_INT({
                    var dialog_id = UTF8_गन्तव्यम्_String($0);
                    var text = UTF8_गन्तव्यम्_String($1);
                    var responseId = $2;
                    var clickOnReturn = $3;
                    var clickOnEscape = $4;
                    var border = UTF8_गन्तव्यम्_String($5);
                    var background = UTF8_गन्तव्यम्_String($6);
                    var hovered = UTF8_गन्तव्यम्_String($7);

                    var dialog = document.getElementById(dialog_id);
                    यदि (!dialog) {
                        प्रत्यागम false;
                    }

                    var button = document.createElement("button");
                    button.innerText = text;
                    button.style.borderColor = border;
                    button.style.backgroundColor = background;

                    dialog.सङ्कलय_Event_Listener('keydown', function(e) {
                        यदि (clickOnReturn && e.कुञ्चिका === "Enter") {
                            e.preventDefault();
                            button.click();
                        } अन्यथा यदि (clickOnEscape && e.कुञ्चिका === "Escape") {
                            e.preventDefault();
                            button.click();
                        }
                    });
                    dialog.सङ्कलय_Event_Listener('cancel', function(e){
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
                    प्रत्यागम true;
                },
                dialog_id,
                button.text,
                button.buttonID,
                button.flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
                button.flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
                button_border,
                button_background,
                button_hovered
            );

            यदि (!created) {
                प्रत्यागम false;
            }
        }

        यावत् (true) {
            // give back control to browser for screen refresh
            emscripten_sleep(0);

            ध्रुव पूर्णाङ्क dialog_open = EM_ASM_INT({
                var dialog_id = UTF8_गन्तव्यम्_String($0);

                var dialog = document.getElementById(dialog_id);
                यदि (!dialog) {
                    प्रत्यागम false;
                }
                प्रत्यागम dialog.उद्घाटय;
            }, dialog_id);

            यदि (dialog_open) {
                अनुवर्त;
            }

            *buttonID = EM_ASM_INT({
                var dialog_id = UTF8_गन्तव्यम्_String($0);
                var dialog = document.getElementById(dialog_id);
                यदि (!dialog) {
                    प्रत्यागम 0;
                }
                try
                {
                    प्रत्यागम parseInt(dialog.return_मानम्);
                }
                catch(e)
                {
                    प्रत्यागम 0;
                }
            }, dialog_id);
            भङ्ग;
        }

    } अन्यथा {
        // Cannot add elements to DOM and block without Asyncify. So, fall back to the alert function.
        EM_ASM({
            alert(UTF8_गन्तव्यम्_String($0) + "\n\n" + UTF8_गन्तव्यम्_String($1));
        }, messageboxdata->title, messageboxdata->सन्देशः);
    }
    प्रत्यागम true;
}

VideoBootStrap Emscripten_bootstrap = {
    EMSCRIPTENVID_DRIVER_NAME, "SDL emscripten video driver",
    Emscripten_CreateDevice,
    Emscripten_ShowMessagebox,
    false
};

bool Emscripten_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_बहुलकम् बहुलकम्;

    // Use a fake 32-bpp desktop mode
    SDL_zero(बहुलकम्);
    बहुलकम्.format = SDL_PIXELFORMAT_RGBA32;
    emscripten_get_screen_आकार(&बहुलकम्.w, &बहुलकम्.h);
    बहुलकम्.pixel_density = emscripten_get_device_pixel_अनुपातः();

    यदि (SDL_सङ्कलय_Basic_Video_Display(&बहुलकम्) == 0) {
        प्रत्यागम false;
    }

    Emscripten_InitMouse();

    // Assume we have a mouse and keyboard
    SDL_सङ्कलय_Keyboard(SDL_DEFAULT_KEYBOARD_ID, रिक्त);
    SDL_सङ्कलय_Mouse(SDL_DEFAULT_MOUSE_ID, रिक्त);

    Emscripten_पञ्जिकाकोशः_Global_Event_Handlers(_this);

    // We're done!
    प्रत्यागम true;
}

स्थिर bool Emscripten_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्)
{
    // can't do this
    प्रत्यागम true;
}

स्थिर शून्य Emscripten_VideoQuit(SDL_VideoDevice *_this)
{
    Emscripten_UnregisterGlobalEventHandlers(_this);
    Emscripten_QuitMouse();
    Emscripten_UnlistenSystemTheme();
    pumpevents_has_सततम् = false;
    pending_swap_interval = -1;
}

स्थिर bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    यदि (rect) {
        rect->x = 0;
        rect->y = 0;
        rect->w = MAIN_THREAD_EM_ASM_INT({
            प्रत्यागम गवाक्षः.inner_विस्तारः;
        });
        rect->h = MAIN_THREAD_EM_ASM_INT({
            प्रत्यागम गवाक्षः.innerHeight;
        });
    }
    प्रत्यागम true;
}

bool Emscripten_Should_समुच्चयः_Swap_Interval(पूर्णाङ्क interval)
{
    यदि (!pumpevents_has_सततम्) {
        pending_swap_interval = interval;
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

पूर्णाङ्क Emscripten_GetPendingSwapInterval(शून्य)
{
    प्रत्यागम pending_swap_interval;
}

स्थिर शून्य Emscripten_PumpEvents(SDL_VideoDevice *_this)
{
    यदि (!pumpevents_has_सततम्) {
        // we assume you've set a mainloop by the time you've called pumpevents, so we delay initial SetInterval changes until then.
        // otherwise you'll get a warning on the javascript console.
        pumpevents_has_सततम् = true;
        यदि (pending_swap_interval >= 0) {
            Emscripten_GLES_समुच्चयः_Swap_Interval(_this, pending_swap_interval);
            pending_swap_interval = -1;
        }
    }
}

EMSCRIPTEN_KEEPALIVE शून्य requestFullscreenThroughSDL(SDL_गवाक्षः *गवाक्षः)
{
    SDL_समुच्चयः_गवाक्षः_Fullscreen(गवाक्षः, true);
}

स्थिर bool Emscripten_समुच्चयः_गवाक्षः_Fill_Document(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool fill)
{
    SDL_गवाक्षः_दत्त *wdata = गवाक्षः->आन्तरिकम्;

    यदि (fill && Emscripten_fill_document_गवाक्षः && (Emscripten_fill_document_गवाक्षः != गवाक्षः)) {
        प्रत्यागम SDL_समुच्चयः_Error("Only one fill-document window allowed at a time.");
    }

    // fill_document takes up the entire page and resizes as the browser window resizes.
    यदि (fill) {
        Emscripten_fill_document_गवाक्षः = गवाक्षः;

        ध्रुव पूर्णाङ्क w = MAIN_THREAD_EM_ASM_INT({ प्रत्यागम गवाक्षः.inner_विस्तारः; });
        ध्रुव पूर्णाङ्क h = MAIN_THREAD_EM_ASM_INT({ प्रत्यागम गवाक्षः.innerHeight; });
        ध्रुव द्विगुण scaled_w = w * wdata->pixel_अनुपातः;
        ध्रुव द्विगुण scaled_h = h * wdata->pixel_अनुपातः;

        wdata->non_fill_document_विस्तारः = गवाक्षः->w;
        wdata->non_fill_document_height = गवाक्षः->h;

        MAIN_THREAD_EM_ASM({
            var canvas = document.querySelector(UTF8_गन्तव्यम्_String($0));
            canvas.SDL3_original_position = canvas.style.position;
            canvas.SDL3_original_शिखरम् = canvas.style.शिखरम्;
            canvas.SDL3_original_वामः = canvas.style.वामः;

            // hide everything on the page that isn't the canvas.
            var भाजय = document.createElement('div');
            भाजय.id = 'SDL3_fill_document_background_elements';

            भाजय.SDL3_canvas = canvas;
            भाजय.SDL3_canvas_parent = canvas.parent_ग्रन्थिः;
            भाजय.SDL3_canvas_nextsib = canvas.अग्र_Sibling;

            var children = Array.from(document.body.children);
            प्रति (var child सम्बन्धि children) {
                भाजय.appendChild(child);
            }
            document.body.appendChild(भाजय);
            भाजय.style.display = 'none';
            document.body.appendChild(canvas);
            canvas.style.position = 'fixed';
            canvas.style.शिखरम् = '0';
            canvas.style.वामः = '0';
        }, wdata->canvas_id);

        emscripten_समुच्चयः_canvas_element_आकार(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // set_canvas_size unsets this
        यदि (wdata->pixel_अनुपातः != 1.0f) {
            emscripten_समुच्चयः_element_css_आकार(wdata->canvas_id, w, h);
        }

        // force the event to trigger, so pixel ratio changes can be handled
        गवाक्षः->w = गवाक्षः->h = 0;
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    } अन्यथा {
        ध्रुव bool transitioning = (Emscripten_fill_document_गवाक्षः == गवाक्षः);
        यदि (transitioning) {
            MAIN_THREAD_EM_ASM({
                // if we had previously hidden everything behind a fill_document window, put it back.
                var भाजय = document.getElementById('SDL3_fill_document_background_elements');
                यदि (भाजय) {
                    यदि (भाजय.SDL3_canvas_nextsib) {
                        भाजय.SDL3_canvas_parent.निवेशय_Before(भाजय.SDL3_canvas, भाजय.SDL3_canvas_nextsib);
                    } अन्यथा {
                        भाजय.SDL3_canvas_parent.appendChild(भाजय.SDL3_canvas);
                    }
                    यावत् (भाजय.firstChild) {
                        document.body.निवेशय_Before(भाजय.firstChild, भाजय);
                    }
                    भाजय.SDL3_canvas.style.position = भाजय.SDL3_canvas.SDL3_original_position;
                    भाजय.SDL3_canvas.style.शिखरम् = भाजय.SDL3_canvas.SDL3_original_शिखरम्;
                    भाजय.SDL3_canvas.style.वामः = भाजय.SDL3_canvas.SDL3_original_वामः;
                    भाजय.remove();
                }
            });
            Emscripten_fill_document_गवाक्षः = रिक्त;
        }

        गवाक्षः->w = wdata->non_fill_document_विस्तारः;
        गवाक्षः->h = wdata->non_fill_document_height;
        ध्रुव द्विगुण scaled_w = SDL_floor(गवाक्षः->w * wdata->pixel_अनुपातः);
        ध्रुव द्विगुण scaled_h = SDL_floor(गवाक्षः->h * wdata->pixel_अनुपातः);
        emscripten_समुच्चयः_canvas_element_आकार(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // if the size is not being controlled by css, we need to scale down for hidpi
        यदि (!wdata->external_आकार && (wdata->pixel_अनुपातः != 1.0f)) {
            // scale canvas down
            emscripten_समुच्चयः_element_css_आकार(wdata->canvas_id, गवाक्षः->w, गवाक्षः->h);
        }

        यदि (transitioning) {
            गवाक्षः->w = गवाक्षः->h = 0;
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, wdata->non_fill_document_विस्तारः, wdata->non_fill_document_height);
        }
    }

    प्रत्यागम true;
}

स्थिर bool Emscripten_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props)
{
    SDL_गवाक्षः_दत्त *wdata;
    द्विगुण css_w, css_h;
    ध्रुव वर्ण *selector;

    bool fill_document = ((गवाक्षः->flags & SDL_गवाक्षः_FILL_DOCUMENT) != 0);
    यदि (fill_document && Emscripten_fill_document_गवाक्षः) {
        fill_document = false;  // only one allowed at a time.
        गवाक्षः->flags &= ~SDL_गवाक्षः_FILL_DOCUMENT;   // !!! FIXME: should this fail instead?
    }

    // Allocate window internal data
    wdata = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(SDL_गवाक्षः_दत्त));
    यदि (!wdata) {
        प्रत्यागम false;
    }

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR);
    यदि (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_गवाक्षः_CREATE_EMSCRIPTEN_CANVAS_ID_STRING, "#canvas");
    }
    wdata->canvas_id = SDL_strdup(selector);

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
    यदि (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_गवाक्षः_CREATE_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, "#window");
    }
    wdata->keyboard_element = SDL_strdup(selector);

    यदि (गवाक्षः->flags & SDL_गवाक्षः_उच्चः_PIXEL_DENSITY) {
        wdata->pixel_अनुपातः = emscripten_get_device_pixel_अनुपातः();
    } अन्यथा {
        wdata->pixel_अनुपातः = 1.0f;
    }

    // set a fake size to check if there is any CSS sizing the canvas
    emscripten_समुच्चयः_canvas_element_आकार(wdata->canvas_id, 1, 1);
    emscripten_get_element_css_आकार(wdata->canvas_id, &css_w, &css_h);

    wdata->external_आकार = SDL_floor(css_w) != 1 || SDL_floor(css_h) != 1;
    यदि (wdata->external_आकार) {
        fill_document = false;  // can't be resizable if something else is controlling it.
        गवाक्षः->w = (पूर्णाङ्क) css_w;
        गवाक्षः->h = (पूर्णाङ्क) css_h;
    }

    wdata->गवाक्षः = गवाक्षः;

    // Setup driver data for this window
    गवाक्षः->आन्तरिकम् = wdata;

    wdata->non_fill_document_विस्तारः = गवाक्षः->w;
    wdata->non_fill_document_height = गवाक्षः->h;
    Emscripten_समुच्चयः_गवाक्षः_Fill_Document(_this, गवाक्षः, fill_document);

    // One window, it always has focus
    SDL_समुच्चयः_Mouse_Focus(गवाक्षः);
    SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);

    Emscripten_पञ्जिकाकोशः_Event_Handlers(wdata);

    // Make the emscripten "fullscreen" button go through SDL.
    MAIN_THREAD_EM_ASM({
        Module['requestFullscreen'] = function(तालकम्_Pointer, resizeCanvas) {
            _requestFullscreenThroughSDL($0);
        };
    }, गवाक्षः);

    // Ensure various things are added to the window's properties
    SDL_समुच्चयः_String_Property(गवाक्षः->props, SDL_PROP_गवाक्षः_EMSCRIPTEN_CANVAS_ID_STRING, wdata->canvas_id);
    SDL_समुच्चयः_String_Property(गवाक्षः->props, SDL_PROP_गवाक्षः_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, wdata->keyboard_element);

    // Window has been successfully created
    प्रत्यागम true;
}

स्थिर शून्य Emscripten_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः, bool resizable)
{
    // this function just has to exist or the higher level won't let the window change its SDL_WINDOW_RESIZABLE flag.
}

स्थिर शून्य Emscripten_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (गवाक्षः->आन्तरिकम्) {
        SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
        यदि (गवाक्षः == Emscripten_fill_document_गवाक्षः) {
            प्रत्यागम;  // canvas size is being dictated by the browser window size, refuse request.
        }

        // update pixel ratio
        यदि (गवाक्षः->flags & SDL_गवाक्षः_उच्चः_PIXEL_DENSITY) {
            दत्त->pixel_अनुपातः = emscripten_get_device_pixel_अनुपातः();
        }
        emscripten_समुच्चयः_canvas_element_आकार(दत्त->canvas_id, SDL_lroundf(गवाक्षः->pending.w * दत्त->pixel_अनुपातः), SDL_lroundf(गवाक्षः->pending.h * दत्त->pixel_अनुपातः));

        // scale canvas down
        यदि (!दत्त->external_आकार && दत्त->pixel_अनुपातः != 1.0f) {
            emscripten_समुच्चयः_element_css_आकार(दत्त->canvas_id, गवाक्षः->pending.w, गवाक्षः->pending.h);
        }

        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, गवाक्षः->pending.w, गवाक्षः->pending.h);
    }
}

स्थिर शून्य Emscripten_Get_गवाक्षः_आकार_अन्तर्_Pixels(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *w, पूर्णाङ्क *h)
{
    SDL_गवाक्षः_दत्त *दत्त;
    यदि (गवाक्षः->आन्तरिकम्) {
        दत्त = गवाक्षः->आन्तरिकम्;
        *w = SDL_lroundf(गवाक्षः->w * दत्त->pixel_अनुपातः);
        *h = SDL_lroundf(गवाक्षः->h * दत्त->pixel_अनुपातः);
    }
}

स्थिर शून्य Emscripten_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त;

    Emscripten_समुच्चयः_गवाक्षः_Fill_Document(_this, गवाक्षः, false);

    यदि (गवाक्षः->आन्तरिकम्) {
        दत्त = गवाक्षः->आन्तरिकम्;

        Emscripten_UnregisterEventHandlers(दत्त);

        // We can't destroy the canvas, so resize it to zero instead
        emscripten_समुच्चयः_canvas_element_आकार(दत्त->canvas_id, 0, 0);
        यदि (दत्त->pixel_अनुपातः != 1.0f) {
            emscripten_समुच्चयः_element_css_आकार(दत्त->canvas_id, 1, 1);
        }
        SDL_free(दत्त->canvas_id);

        SDL_free(दत्त->keyboard_element);

        SDL_free(गवाक्षः->आन्तरिकम्);
        गवाक्षः->आन्तरिकम् = रिक्त;
    }

    MAIN_THREAD_EM_ASM({
        // just ignore clicks on the fullscreen button while there's no SDL window.
        Module['requestFullscreen'] = function(तालकम्_Pointer, resizeCanvas) {};
    });
}

स्थिर SDL_Fullscreen_परिणाम Emscripten_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_गवाक्षः_दत्त *दत्त;
    पूर्णाङ्क res = -1;

    यदि (गवाक्षः->आन्तरिकम्) {
        दत्त = गवाक्षः->आन्तरिकम्;

        यदि (दत्त->fullscreen_change_अन्तर्_प्रगतिः) {
            प्रत्यागम SDL_FULLSCREEN_FAILED;;
        }

        EmscriptenFullscreenChangeEvent fsevent;
        यदि (emscripten_get_fullscreen_स्थितिः(&fsevent) == EMSCRIPTEN_परिणाम_SUCCESS) {
            यदि ((fullscreen == SDL_FULLSCREEN_OP_ENTER) == fsevent.isFullscreen) {
                प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;  // already there.
            }
        }

        यदि (fullscreen) {
            EmscriptenFullscreenStrategy strategy;
            bool is_fullscreen_desktop = !गवाक्षः->fullscreen_exclusive;

            SDL_zero(strategy);
            strategy.scale_बहुलकम् = is_fullscreen_desktop ? EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH : EMSCRIPTEN_FULLSCREEN_SCALE_ASPECT;

            यदि (!is_fullscreen_desktop) {
                strategy.canvas_Resolution_Scale_बहुलकम् = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
            } अन्यथा यदि (गवाक्षः->flags & SDL_गवाक्षः_उच्चः_PIXEL_DENSITY) {
                strategy.canvas_Resolution_Scale_बहुलकम् = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF;
            } अन्यथा {
                strategy.canvas_Resolution_Scale_बहुलकम् = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
            }

            strategy.filtering_बहुलकम् = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;

            strategy.canvasResizedCallback = Emscripten_HandleCanvasResize;
            strategy.canvas_Resized_Callback_User_दत्त = दत्त;

            दत्त->fullscreen_बहुलकम्_flags = (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN);
            दत्त->fullscreen_resize = is_fullscreen_desktop;

            res = emscripten_request_fullscreen_strategy(दत्त->canvas_id, 1, &strategy);
        } अन्यथा {
            res = emscripten_exit_fullscreen();
        }
    }

    यदि (res == EMSCRIPTEN_परिणाम_SUCCESS) {
        दत्त->fullscreen_change_अन्तर्_प्रगतिः = true;   // even on success, this might animate to the new state.
        प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
    } अन्यथा यदि (res == EMSCRIPTEN_परिणाम_DEFERRED) {
        दत्त->fullscreen_change_अन्तर्_प्रगतिः = true;
        प्रत्यागम SDL_FULLSCREEN_PENDING;
    } अन्यथा {
        प्रत्यागम SDL_FULLSCREEN_FAILED;
    }
}

स्थिर शून्य Emscripten_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    emscripten_समुच्चयः_गवाक्षः_title(गवाक्षः->title);
}

स्थिर bool Emscripten_समुच्चयः_गवाक्षः_Icon(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *icon)
{
    // Create dynamic memory stream for PNG encoding
    SDL_IOStream *प्रवाहः = SDL_IOFromDynamicMem();
    यदि (!प्रवाहः) {
        प्रत्यागम false;
    }

    // Encode icon to PNG using SDL's native PNG encoder
    यदि (!SDL_SavePNG_IO(icon, प्रवाहः, false)) {
        SDL_CloseIO(प्रवाहः);
        प्रत्यागम false;
    }

    // Get the PNG data from the stream
    शून्य *png_दत्त = SDL_GetPointerProperty(
        SDL_GetIOProperties(प्रवाहः),
        SDL_PROP_IOSTREAM_DYNAMIC_स्मृतिः_POINTER,
        रिक्त
    );
    size_t png_आकार = (size_t)SDL_GetIOSize(प्रवाहः);

    // Pass PNG data to JavaScript
    MAIN_THREAD_EM_ASM({
        // Use `.slice` to make a copy of the data if we are dealing with a SharedArrayBuffer, or `.subarray` to create a
        // view into the existing buffer if its non-shared.
        var png_दत्त_2 = HEAPU8.बफर_2 instanceof Array_बफर ? HEAPU8.subarray($0, $0 + $1) : HEAPU8.खण्डिका($0, $0 + $1);

        var blob = new Blob([png_दत्त_2], {type: 'image/png'});
        var url = URL.createObjectURL(blob);

        // Set as favicon (create link element if it doesn't exist)
        var link = document.querySelector("link[rel~='icon']");
        यदि (!link) {
            link = document.createElement('link');
            link.rel = 'icon';
            link.type = 'image/png';
            document.शीर्ष.appendChild(link);
        }

        // Revoke old URL if it exists to prevent memory leaks
        यदि (link.href && link.href.startsWith('blob:')) {
            URL.revokeObjectURL(link.href);
        }

        link.href = url;
    }, png_दत्त, png_आकार);

    SDL_CloseIO(प्रवाहः);
    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_EMSCRIPTEN
