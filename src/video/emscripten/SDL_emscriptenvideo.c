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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_EMSCRIPTEN

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../SDL_hints_c.h"

#ضمن "SDL_emscriptenvideo.h"
#ضمن "SDL_emscriptenopengles.h"
#ضمن "SDL_emscriptenframebuffer.h"
#ضمن "SDL_emscriptenevents.h"
#ضمن "SDL_emscriptenmouse.h"

#تعریف_کرو EMSCRIPTENVID_DRIVER_NAME "emscripten"

// Initialization/Query functions
ساكن bool Emscripten_VideoInit(SDL_VideoDevice *_this);
ساكن bool Emscripten_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
ساكن فراغ Emscripten_VideoQuit(SDL_VideoDevice *_this);
ساكن bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

ساكن bool Emscripten_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
ساكن فراغ Emscripten_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
ساكن فراغ Emscripten_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, bool resizable);
ساكن فراغ Emscripten_Get_کھڑکی_ناپ_وچ_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *w, صحيح *h);
ساكن فراغ Emscripten_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
ساكن SDL_Fullscreen_نتیجہ Emscripten_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ساكن فراغ Emscripten_PumpEvents(SDL_VideoDevice *_this);
ساكن فراغ Emscripten_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
ساكن bool Emscripten_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon);
ساكن bool Emscripten_سیٹ_کھڑکی_Fill_Document(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool fill);

SDL_کھڑکی *Emscripten_fill_document_کھڑکی = عدم;

ساكن bool pumpevents_has_لگاتار = false;
ساكن صحيح pending_وٹاندرا_interval = -1;

// Emscripten driver bootstrap functions

ساكن فراغ Emscripten_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ساكن SDL_SystemTheme Emscripten_GetSystemTheme(فراغ)
{
    /* Technically, light theme can mean explicit light theme or no preference.
       https://developer.mozilla.org/en-US/docs/Web/CSS/@media/prefers-color-scheme#syntax */

    صحيح theme_کوڈ = MAIN_THREAD_EM_ASM_INT({
        إذا (!کھڑکی.میل_Media) {
            أرجع -1;
        }

        إذا (کھڑکی.میل_Media('(prefers-color-scheme: light)').matches) {
            أرجع 0;
        }

        إذا (کھڑکی.میل_Media('(prefers-color-scheme: dark)').matches) {
            أرجع 1;
        }

        أرجع -1;
    });

    بدل (theme_کوڈ) {
    حالة 0:
        أرجع SDL_SYSTEM_THEME_LIGHT;

    حالة 1:
        أرجع SDL_SYSTEM_THEME_DARK;

    افتراضي:
        أرجع SDL_SYSTEM_THEME_UNKNOWN;
    }
}

ساكن فراغ Emscripten_ListenSystemTheme(فراغ)
{
    MAIN_THREAD_EM_ASM({
        إذا (کھڑکی.میل_Media) {
            var SDL3 = Module['SDL3'];

            SDL3.event_Handler_Theme_بدلیا = function(event) {
                Emscripten_Send_System_Theme_بدلیا_Event();
            };

            SDL3.theme_بدلیا_میل_Media = کھڑکی.میل_Media('(prefers-color-scheme: dark)');
            SDL3.theme_بدلیا_میل_Media.جوڑو_Event_Listener('change', SDL3.event_Handler_Theme_بدلیا);
        }
    });
}

ساكن فراغ Emscripten_UnlistenSystemTheme(فراغ)
{
    MAIN_THREAD_EM_ASM({
        إذا (typeof(Module['SDL3']) !== 'undefined') {
            var SDL3 = Module['SDL3'];

            SDL3.theme_بدلیا_میل_Media.removeEventListener('change', SDL3.event_Handler_Theme_بدلیا);
            SDL3.theme_بدلیا_میل_Media = undefined;
            SDL3.event_Handler_Theme_بدلیا = undefined;
        }
    });
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Send_System_Theme_بدلیا_Event_2(فراغ)
{
    SDL_سیٹ_System_Theme(Emscripten_GetSystemTheme());
}

ساكن SDL_VideoDevice *Emscripten_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    /* Firefox sends blur event which would otherwise prevent full screen
     * when the user clicks to allow full screen.
     * See https://bugzilla.mozilla.org/show_bug.cgi?id=1144964
     */
    SDL_سیٹ_Hint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

    // Set the function pointers
    device->VideoInit = Emscripten_VideoInit;
    device->VideoQuit = Emscripten_VideoQuit;
    device->GetDisplayUsableBounds = Emscripten_GetDisplayUsableBounds;
    device->سیٹ_Display_منوال = Emscripten_سیٹ_Display_منوال;

    device->PumpEvents = Emscripten_PumpEvents;

    device->CreateSDLWindow = Emscripten_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = Emscripten_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Icon = Emscripten_سیٹ_کھڑکی_Icon;
    /*device->SetWindowPosition = Emscripten_SetWindowPosition;*/
    device->سیٹ_کھڑکی_ناپ = Emscripten_سیٹ_کھڑکی_ناپ;
    device->سیٹ_کھڑکی_Resizable = Emscripten_سیٹ_کھڑکی_Resizable;
    /*device->ShowWindow = Emscripten_ShowWindow;
    device->HideWindow = Emscripten_HideWindow;
    device->RaiseWindow = Emscripten_RaiseWindow;
    device->MaximizeWindow = Emscripten_MaximizeWindow;
    device->MinimizeWindow = Emscripten_MinimizeWindow;
    device->RestoreWindow = Emscripten_RestoreWindow;
    device->SetWindowMouseGrab = Emscripten_SetWindowMouseGrab;*/
    device->Get_کھڑکی_ناپ_وچ_Pixels = Emscripten_Get_کھڑکی_ناپ_وچ_Pixels;
    device->Destroy_کھڑکی = Emscripten_Destroy_کھڑکی;
    device->سیٹ_کھڑکی_Fullscreen = Emscripten_سیٹ_کھڑکی_Fullscreen;
    device->سیٹ_کھڑکی_Fill_Document = Emscripten_سیٹ_کھڑکی_Fill_Document;

    device->Create_کھڑکی_Framebuffer = Emscripten_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = Emscripten_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = Emscripten_Destroy_کھڑکی_Framebuffer;

    device->GL_لدو_Library = Emscripten_GLES_لدو_Library;
    device->GL_Get_Proc_پتہ = Emscripten_GLES_Get_Proc_پتہ;
    device->GL_UnloadLibrary = Emscripten_GLES_UnloadLibrary;
    device->GL_CreateContext = Emscripten_GLES_CreateContext;
    device->GL_MakeCurrent = Emscripten_GLES_MakeCurrent;
    device->GL_سیٹ_وٹاندرا_Interval = Emscripten_GLES_سیٹ_وٹاندرا_Interval;
    device->GL_Get_وٹاندرا_Interval = Emscripten_GLES_Get_وٹاندرا_Interval;
    device->GL_وٹاندرا_کھڑکی = Emscripten_GLES_وٹاندرا_کھڑکی;
    device->GL_DestroyContext = Emscripten_GLES_DestroyContext;

    device->حرر = Emscripten_DeleteDevice;

    Emscripten_ListenSystemTheme();
    device->system_theme = Emscripten_GetSystemTheme();

    أرجع device;
}

ساكن bool Emscripten_ShowMessagebox(ثابت SDL_سنیہا_Box_انکڑے *messageboxdata, صحيح *buttonID) {
    إذا (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        حرف dialog_background[32];
        حرف dialog_color[32];
        حرف button_border[32];
        حرف button_background[32];
        حرف button_hovered[32];

        إذا (messageboxdata->colorScheme) {
            SDL_سنیہا_Box_Color color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND];
            SDL_snprintf(dialog_background, حجم(dialog_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_متن];
            SDL_snprintf(dialog_color, حجم(dialog_color), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER];
            SDL_snprintf(button_border, حجم(button_border), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND];
            SDL_snprintf(button_background, حجم(button_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED];
            SDL_snprintf(button_hovered, حجم(button_hovered), "rgb(%u, %u, %u)", color.r, color.g, color.b);
        } وإلا {
            SDL_zero(dialog_background);
            SDL_zero(dialog_color);
            SDL_zero(button_border);
            SDL_zero(button_background);
            SDL_zero(button_hovered);
        }

        // TODO: Handle parent window when multiple windows can be added in Emscripten builds
        حرف dialog_id[64];
        SDL_snprintf(dialog_id, حجم(dialog_id), "SDL3_messagebox_%u", SDL_rand_بٹ());
        EM_ASM({
            var title = UTF8_منزل_String($0);
            var سنیہا = UTF8_منزل_String($1);
            var background = UTF8_منزل_String($2);
            var color = UTF8_منزل_String($3);
            var id = UTF8_منزل_String($4);

            // Dialogs are always put in the front of the DOM
            var dialog = document.createElement("dialog");
            // Set class to allow for CSS selectors
            dialog.classList.جوڑو("SDL3_messagebox");
            dialog.id = id;
            dialog.style.color = color;
            dialog.style.backgroundColor = background;
            document.body.append(dialog);

            var h1 = document.createElement("h1");
            h1.inner_متن = title;
            dialog.append(h1);

            var p = document.createElement("p");
            p.inner_متن = سنیہا;
            dialog.append(p);

            dialog.showModal();
        }, messageboxdata->title, messageboxdata->سنیہا, dialog_background, dialog_color, dialog_id);

        صحيح i;
        لكل (i = 0; i < messageboxdata->numbuttons; ++i) {
            SDL_سنیہا_Box_Button_انکڑے button = messageboxdata->buttons[i];

            ثابت صحيح created = EM_ASM_INT({
                    var dialog_id = UTF8_منزل_String($0);
                    var متن = UTF8_منزل_String($1);
                    var responseId = $2;
                    var clickOnReturn = $3;
                    var clickOnEscape = $4;
                    var border = UTF8_منزل_String($5);
                    var background = UTF8_منزل_String($6);
                    var hovered = UTF8_منزل_String($7);

                    var dialog = document.getElementById(dialog_id);
                    إذا (!dialog) {
                        أرجع false;
                    }

                    var button = document.createElement("button");
                    button.inner_متن = متن;
                    button.style.borderColor = border;
                    button.style.backgroundColor = background;

                    dialog.جوڑو_Event_Listener('keydown', function(e) {
                        إذا (clickOnReturn && e.کلید === "Enter") {
                            e.preventDefault();
                            button.click();
                        } وإلا إذا (clickOnEscape && e.کلید === "Escape") {
                            e.preventDefault();
                            button.click();
                        }
                    });
                    dialog.جوڑو_Event_Listener('cancel', function(e){
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
                    أرجع true;
                },
                dialog_id,
                button.متن,
                button.buttonID,
                button.flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
                button.flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
                button_border,
                button_background,
                button_hovered
            );

            إذا (!created) {
                أرجع false;
            }
        }

        طالما (true) {
            // give back control to browser for screen refresh
            emscripten_sleep(0);

            ثابت صحيح dialog_open = EM_ASM_INT({
                var dialog_id = UTF8_منزل_String($0);

                var dialog = document.getElementById(dialog_id);
                إذا (!dialog) {
                    أرجع false;
                }
                أرجع dialog.open;
            }, dialog_id);

            إذا (dialog_open) {
                استمر;
            }

            *buttonID = EM_ASM_INT({
                var dialog_id = UTF8_منزل_String($0);
                var dialog = document.getElementById(dialog_id);
                إذا (!dialog) {
                    أرجع 0;
                }
                try
                {
                    أرجع parseInt(dialog.return_قدر);
                }
                catch(e)
                {
                    أرجع 0;
                }
            }, dialog_id);
            اكسر;
        }

    } وإلا {
        // Cannot add elements to DOM and block without Asyncify. So, fall back to the alert function.
        EM_ASM({
            alert(UTF8_منزل_String($0) + "\n\n" + UTF8_منزل_String($1));
        }, messageboxdata->title, messageboxdata->سنیہا);
    }
    أرجع true;
}

VideoBootStrap Emscripten_bootstrap = {
    EMSCRIPTENVID_DRIVER_NAME, "SDL emscripten video driver",
    Emscripten_CreateDevice,
    Emscripten_ShowMessagebox,
    false
};

bool Emscripten_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_منوال منوال;

    // Use a fake 32-bpp desktop mode
    SDL_zero(منوال);
    منوال.format = SDL_PIXELFORMAT_RGBA32;
    emscripten_get_screen_ناپ(&منوال.w, &منوال.h);
    منوال.pixel_density = emscripten_get_device_pixel_تناسب();

    إذا (SDL_جوڑو_Basic_Video_Display(&منوال) == 0) {
        أرجع false;
    }

    Emscripten_InitMouse();

    // Assume we have a mouse and keyboard
    SDL_جوڑو_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_جوڑو_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);

    Emscripten_رجسٹر_Global_Event_Handlers(_this);

    // We're done!
    أرجع true;
}

ساكن bool Emscripten_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    // can't do this
    أرجع true;
}

ساكن فراغ Emscripten_VideoQuit(SDL_VideoDevice *_this)
{
    Emscripten_UnregisterGlobalEventHandlers(_this);
    Emscripten_QuitMouse();
    Emscripten_UnlistenSystemTheme();
    pumpevents_has_لگاتار = false;
    pending_وٹاندرا_interval = -1;
}

ساكن bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    إذا (rect) {
        rect->x = 0;
        rect->y = 0;
        rect->w = MAIN_THREAD_EM_ASM_INT({
            أرجع کھڑکی.inner_چوڑائی;
        });
        rect->h = MAIN_THREAD_EM_ASM_INT({
            أرجع کھڑکی.inner_اچائی;
        });
    }
    أرجع true;
}

bool Emscripten_Should_سیٹ_وٹاندرا_Interval(صحيح interval)
{
    إذا (!pumpevents_has_لگاتار) {
        pending_وٹاندرا_interval = interval;
        أرجع false;
    }
    أرجع true;
}

صحيح Emscripten_Get_Pending_وٹاندرا_Interval(فراغ)
{
    أرجع pending_وٹاندرا_interval;
}

ساكن فراغ Emscripten_PumpEvents(SDL_VideoDevice *_this)
{
    إذا (!pumpevents_has_لگاتار) {
        // we assume you've set a mainloop by the time you've called pumpevents, so we delay initial SetInterval changes until then.
        // otherwise you'll get a warning on the javascript console.
        pumpevents_has_لگاتار = true;
        إذا (pending_وٹاندرا_interval >= 0) {
            Emscripten_GLES_سیٹ_وٹاندرا_Interval(_this, pending_وٹاندرا_interval);
            pending_وٹاندرا_interval = -1;
        }
    }
}

EMSCRIPTEN_KEEPALIVE فراغ requestFullscreenThroughSDL(SDL_کھڑکی *کھڑکی)
{
    SDL_سیٹ_کھڑکی_Fullscreen(کھڑکی, true);
}

ساكن bool Emscripten_سیٹ_کھڑکی_Fill_Document(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool fill)
{
    SDL_کھڑکی_انکڑے *wdata = کھڑکی->اندرونی;

    إذا (fill && Emscripten_fill_document_کھڑکی && (Emscripten_fill_document_کھڑکی != کھڑکی)) {
        أرجع SDL_سیٹ_Error("Only one fill-document window allowed at a time.");
    }

    // fill_document takes up the entire page and resizes as the browser window resizes.
    إذا (fill) {
        Emscripten_fill_document_کھڑکی = کھڑکی;

        ثابت صحيح w = MAIN_THREAD_EM_ASM_INT({ أرجع کھڑکی.inner_چوڑائی; });
        ثابت صحيح h = MAIN_THREAD_EM_ASM_INT({ أرجع کھڑکی.inner_اچائی; });
        ثابت مزدوج scaled_w = w * wdata->pixel_تناسب;
        ثابت مزدوج scaled_h = h * wdata->pixel_تناسب;

        wdata->non_fill_document_چوڑائی = کھڑکی->w;
        wdata->non_fill_document_اچائی = کھڑکی->h;

        MAIN_THREAD_EM_ASM({
            var canvas = document.querySelector(UTF8_منزل_String($0));
            canvas.SDL3_original_position = canvas.style.position;
            canvas.SDL3_original_چوٹی = canvas.style.چوٹی;
            canvas.SDL3_original_بایاں = canvas.style.بایاں;

            // hide everything on the page that isn't the canvas.
            var div = document.createElement('div');
            div.id = 'SDL3_fill_document_background_elements';

            div.SDL3_canvas = canvas;
            div.SDL3_canvas_ماپا = canvas.ماپا_گرہ;
            div.SDL3_canvas_nextsib = canvas.اگلا_Sibling;

            var children = Array.from(document.body.children);
            لكل (var بچہ دا children) {
                div.append_بچہ(بچہ);
            }
            document.body.append_بچہ(div);
            div.style.display = 'none';
            document.body.append_بچہ(canvas);
            canvas.style.position = 'fixed';
            canvas.style.چوٹی = '0';
            canvas.style.بایاں = '0';
        }, wdata->canvas_id);

        emscripten_سیٹ_canvas_element_ناپ(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // set_canvas_size unsets this
        إذا (wdata->pixel_تناسب != 1.0f) {
            emscripten_سیٹ_element_css_ناپ(wdata->canvas_id, w, h);
        }

        // force the event to trigger, so pixel ratio changes can be handled
        کھڑکی->w = کھڑکی->h = 0;
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    } وإلا {
        ثابت bool transitioning = (Emscripten_fill_document_کھڑکی == کھڑکی);
        إذا (transitioning) {
            MAIN_THREAD_EM_ASM({
                // if we had previously hidden everything behind a fill_document window, put it back.
                var div = document.getElementById('SDL3_fill_document_background_elements');
                إذا (div) {
                    إذا (div.SDL3_canvas_nextsib) {
                        div.SDL3_canvas_ماپا.داخل_کرو_Before(div.SDL3_canvas, div.SDL3_canvas_nextsib);
                    } وإلا {
                        div.SDL3_canvas_ماپا.append_بچہ(div.SDL3_canvas);
                    }
                    طالما (div.پہلا_بچہ_2) {
                        document.body.داخل_کرو_Before(div.پہلا_بچہ_2, div);
                    }
                    div.SDL3_canvas.style.position = div.SDL3_canvas.SDL3_original_position;
                    div.SDL3_canvas.style.چوٹی = div.SDL3_canvas.SDL3_original_چوٹی;
                    div.SDL3_canvas.style.بایاں = div.SDL3_canvas.SDL3_original_بایاں;
                    div.remove();
                }
            });
            Emscripten_fill_document_کھڑکی = عدم;
        }

        کھڑکی->w = wdata->non_fill_document_چوڑائی;
        کھڑکی->h = wdata->non_fill_document_اچائی;
        ثابت مزدوج scaled_w = SDL_floor(کھڑکی->w * wdata->pixel_تناسب);
        ثابت مزدوج scaled_h = SDL_floor(کھڑکی->h * wdata->pixel_تناسب);
        emscripten_سیٹ_canvas_element_ناپ(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // if the size is not being controlled by css, we need to scale down for hidpi
        إذا (!wdata->external_ناپ && (wdata->pixel_تناسب != 1.0f)) {
            // scale canvas down
            emscripten_سیٹ_element_css_ناپ(wdata->canvas_id, کھڑکی->w, کھڑکی->h);
        }

        إذا (transitioning) {
            کھڑکی->w = کھڑکی->h = 0;
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, wdata->non_fill_document_چوڑائی, wdata->non_fill_document_اچائی);
        }
    }

    أرجع true;
}

ساكن bool Emscripten_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    SDL_کھڑکی_انکڑے *wdata;
    مزدوج css_w, css_h;
    ثابت حرف *selector;

    bool fill_document = ((کھڑکی->flags & SDL_کھڑکی_FILL_DOCUMENT) != 0);
    إذا (fill_document && Emscripten_fill_document_کھڑکی) {
        fill_document = false;  // only one allowed at a time.
        کھڑکی->flags &= ~SDL_کھڑکی_FILL_DOCUMENT;   // !!! FIXME: should this fail instead?
    }

    // Allocate window internal data
    wdata = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(SDL_کھڑکی_انکڑے));
    إذا (!wdata) {
        أرجع false;
    }

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR);
    إذا (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_کھڑکی_CREATE_EMSCRIPTEN_CANVAS_ID_STRING, "#canvas");
    }
    wdata->canvas_id = SDL_strdup(selector);

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
    إذا (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_کھڑکی_CREATE_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, "#window");
    }
    wdata->keyboard_element = SDL_strdup(selector);

    إذا (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY) {
        wdata->pixel_تناسب = emscripten_get_device_pixel_تناسب();
    } وإلا {
        wdata->pixel_تناسب = 1.0f;
    }

    // set a fake size to check if there is any CSS sizing the canvas
    emscripten_سیٹ_canvas_element_ناپ(wdata->canvas_id, 1, 1);
    emscripten_get_element_css_ناپ(wdata->canvas_id, &css_w, &css_h);

    wdata->external_ناپ = SDL_floor(css_w) != 1 || SDL_floor(css_h) != 1;
    إذا (wdata->external_ناپ) {
        fill_document = false;  // can't be resizable if something else is controlling it.
        کھڑکی->w = (صحيح) css_w;
        کھڑکی->h = (صحيح) css_h;
    }

    wdata->کھڑکی = کھڑکی;

    // Setup driver data for this window
    کھڑکی->اندرونی = wdata;

    wdata->non_fill_document_چوڑائی = کھڑکی->w;
    wdata->non_fill_document_اچائی = کھڑکی->h;
    Emscripten_سیٹ_کھڑکی_Fill_Document(_this, کھڑکی, fill_document);

    // One window, it always has focus
    SDL_سیٹ_Mouse_Focus(کھڑکی);
    SDL_سیٹ_Keyboard_Focus(کھڑکی);

    Emscripten_رجسٹر_Event_Handlers(wdata);

    // Make the emscripten "fullscreen" button go through SDL.
    MAIN_THREAD_EM_ASM({
        Module['requestFullscreen'] = function(جندرا_اشارہ_گر, resizeCanvas) {
            _requestFullscreenThroughSDL($0);
        };
    }, کھڑکی);

    // Ensure various things are added to the window's properties
    SDL_سیٹ_String_Property(کھڑکی->props, SDL_PROP_کھڑکی_EMSCRIPTEN_CANVAS_ID_STRING, wdata->canvas_id);
    SDL_سیٹ_String_Property(کھڑکی->props, SDL_PROP_کھڑکی_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, wdata->keyboard_element);

    // Window has been successfully created
    أرجع true;
}

ساكن فراغ Emscripten_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, bool resizable)
{
    // this function just has to exist or the higher level won't let the window change its SDL_WINDOW_RESIZABLE flag.
}

ساكن فراغ Emscripten_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (کھڑکی->اندرونی) {
        SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
        إذا (کھڑکی == Emscripten_fill_document_کھڑکی) {
            أرجع;  // canvas size is being dictated by the browser window size, refuse request.
        }

        // update pixel ratio
        إذا (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY) {
            انکڑے->pixel_تناسب = emscripten_get_device_pixel_تناسب();
        }
        emscripten_سیٹ_canvas_element_ناپ(انکڑے->canvas_id, SDL_lroundf(کھڑکی->pending.w * انکڑے->pixel_تناسب), SDL_lroundf(کھڑکی->pending.h * انکڑے->pixel_تناسب));

        // scale canvas down
        إذا (!انکڑے->external_ناپ && انکڑے->pixel_تناسب != 1.0f) {
            emscripten_سیٹ_element_css_ناپ(انکڑے->canvas_id, کھڑکی->pending.w, کھڑکی->pending.h);
        }

        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی->pending.w, کھڑکی->pending.h);
    }
}

ساكن فراغ Emscripten_Get_کھڑکی_ناپ_وچ_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *w, صحيح *h)
{
    SDL_کھڑکی_انکڑے *انکڑے;
    إذا (کھڑکی->اندرونی) {
        انکڑے = کھڑکی->اندرونی;
        *w = SDL_lroundf(کھڑکی->w * انکڑے->pixel_تناسب);
        *h = SDL_lroundf(کھڑکی->h * انکڑے->pixel_تناسب);
    }
}

ساكن فراغ Emscripten_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے;

    Emscripten_سیٹ_کھڑکی_Fill_Document(_this, کھڑکی, false);

    إذا (کھڑکی->اندرونی) {
        انکڑے = کھڑکی->اندرونی;

        Emscripten_UnregisterEventHandlers(انکڑے);

        // We can't destroy the canvas, so resize it to zero instead
        emscripten_سیٹ_canvas_element_ناپ(انکڑے->canvas_id, 0, 0);
        إذا (انکڑے->pixel_تناسب != 1.0f) {
            emscripten_سیٹ_element_css_ناپ(انکڑے->canvas_id, 1, 1);
        }
        SDL_free(انکڑے->canvas_id);

        SDL_free(انکڑے->keyboard_element);

        SDL_free(کھڑکی->اندرونی);
        کھڑکی->اندرونی = عدم;
    }

    MAIN_THREAD_EM_ASM({
        // just ignore clicks on the fullscreen button while there's no SDL window.
        Module['requestFullscreen'] = function(جندرا_اشارہ_گر, resizeCanvas) {};
    });
}

ساكن SDL_Fullscreen_نتیجہ Emscripten_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_کھڑکی_انکڑے *انکڑے;
    صحيح res = -1;

    إذا (کھڑکی->اندرونی) {
        انکڑے = کھڑکی->اندرونی;

        إذا (انکڑے->fullscreen_change_وچ_ترقی) {
            أرجع SDL_FULLSCREEN_FAILED;;
        }

        EmscriptenFullscreenChangeEvent fsevent;
        إذا (emscripten_get_fullscreen_حالت(&fsevent) == EMSCRIPTEN_نتیجہ_SUCCESS) {
            إذا ((fullscreen == SDL_FULLSCREEN_OP_ENTER) == fsevent.isFullscreen) {
                أرجع SDL_FULLSCREEN_SUCCEEDED;  // already there.
            }
        }

        إذا (fullscreen) {
            EmscriptenFullscreenStrategy strategy;
            bool is_fullscreen_desktop = !کھڑکی->fullscreen_exclusive;

            SDL_zero(strategy);
            strategy.scale_منوال = is_fullscreen_desktop ? EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH : EMSCRIPTEN_FULLSCREEN_SCALE_ASPECT;

            إذا (!is_fullscreen_desktop) {
                strategy.canvas_Resolution_Scale_منوال = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
            } وإلا إذا (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY) {
                strategy.canvas_Resolution_Scale_منوال = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF;
            } وإلا {
                strategy.canvas_Resolution_Scale_منوال = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
            }

            strategy.filtering_منوال = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;

            strategy.canvasResizedCallback = Emscripten_HandleCanvasResize;
            strategy.canvas_Resized_Callback_User_انکڑے = انکڑے;

            انکڑے->fullscreen_منوال_flags = (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN);
            انکڑے->fullscreen_resize = is_fullscreen_desktop;

            res = emscripten_request_fullscreen_strategy(انکڑے->canvas_id, 1, &strategy);
        } وإلا {
            res = emscripten_exit_fullscreen();
        }
    }

    إذا (res == EMSCRIPTEN_نتیجہ_SUCCESS) {
        انکڑے->fullscreen_change_وچ_ترقی = true;   // even on success, this might animate to the new state.
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    } وإلا إذا (res == EMSCRIPTEN_نتیجہ_DEFERRED) {
        انکڑے->fullscreen_change_وچ_ترقی = true;
        أرجع SDL_FULLSCREEN_PENDING;
    } وإلا {
        أرجع SDL_FULLSCREEN_FAILED;
    }
}

ساكن فراغ Emscripten_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    emscripten_سیٹ_کھڑکی_title(کھڑکی->title);
}

ساكن bool Emscripten_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon)
{
    // Create dynamic memory stream for PNG encoding
    SDL_IOStream *دھارا = SDL_IOFromDynamicMem();
    إذا (!دھارا) {
        أرجع false;
    }

    // Encode icon to PNG using SDL's native PNG encoder
    إذا (!SDL_SavePNG_IO(icon, دھارا, false)) {
        SDL_CloseIO(دھارا);
        أرجع false;
    }

    // Get the PNG data from the stream
    فراغ *png_انکڑے = SDL_Get_اشارہ_گر_Property(
        SDL_GetIOProperties(دھارا),
        SDL_PROP_IOSTREAM_DYNAMIC_حافظہ_اشارہ_گر,
        عدم
    );
    size_t png_ناپ = (size_t)SDL_GetIOSize(دھارا);

    // Pass PNG data to JavaScript
    MAIN_THREAD_EM_ASM({
        // Use `.slice` to make a copy of the data if we are dealing with a SharedArrayBuffer, or `.subarray` to create a
        // view into the existing buffer if its non-shared.
        var png_انکڑے_2 = HEAPU8.بفر_2 instanceof Array_بفر ? HEAPU8.subarray($0, $0 + $1) : HEAPU8.ٹکڑا($0, $0 + $1);

        var blob = new Blob([png_انکڑے_2], {type: 'image/png'});
        var url = URL.createObjectURL(blob);

        // Set as favicon (create link element if it doesn't exist)
        var link = document.querySelector("link[rel~='icon']");
        إذا (!link) {
            link = document.createElement('link');
            link.rel = 'icon';
            link.type = 'image/png';
            document.سر.append_بچہ(link);
        }

        // Revoke old URL if it exists to prevent memory leaks
        إذا (link.href && link.href.startsWith('blob:')) {
            URL.revokeObjectURL(link.href);
        }

        link.href = url;
    }, png_انکڑے, png_ناپ);

    SDL_CloseIO(دھارا);
    أرجع true;
}

#جے_انت // SDL_VIDEO_DRIVER_EMSCRIPTEN
