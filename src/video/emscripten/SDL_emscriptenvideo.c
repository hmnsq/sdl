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

#که_تعریف_شوی SDL_VIDEO_DRIVER_EMSCRIPTEN

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../SDL_hints_c.h"

#ضمن "SDL_emscriptenvideo.h"
#ضمن "SDL_emscriptenopengles.h"
#ضمن "SDL_emscriptenframebuffer.h"
#ضمن "SDL_emscriptenevents.h"
#ضمن "SDL_emscriptenmouse.h"

#تعریف_کړه EMSCRIPTENVID_DRIVER_NAME "emscripten"

// Initialization/Query functions
ساكن bool Emscripten_VideoInit(SDL_VideoDevice *_this);
ساكن bool Emscripten_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ);
ساكن فراغ Emscripten_VideoQuit(SDL_VideoDevice *_this);
ساكن bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

ساكن bool Emscripten_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props);
ساكن فراغ Emscripten_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
ساكن فراغ Emscripten_سېټ_کړکۍ_Resizable(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ, bool resizable);
ساكن فراغ Emscripten_Get_کړکۍ_اندازه_دننه_Pixels(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *w, صحيح *h);
ساكن فراغ Emscripten_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
ساكن SDL_Fullscreen_پایله Emscripten_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ساكن فراغ Emscripten_PumpEvents(SDL_VideoDevice *_this);
ساكن فراغ Emscripten_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
ساكن bool Emscripten_سېټ_کړکۍ_Icon(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_Surface *icon);
ساكن bool Emscripten_سېټ_کړکۍ_Fill_Document(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool fill);

SDL_کړکۍ *Emscripten_fill_document_کړکۍ = عدم;

ساكن bool pumpevents_has_پرلپسې = false;
ساكن صحيح pending_بدلون_interval = -1;

// Emscripten driver bootstrap functions

ساكن فراغ Emscripten_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ساكن SDL_SystemTheme Emscripten_GetSystemTheme(فراغ)
{
    /* Technically, light theme can mean explicit light theme or no preference.
       https://developer.mozilla.org/en-US/docs/Web/CSS/@media/prefers-color-scheme#syntax */

    صحيح theme_کوډ = MAIN_THREAD_EM_ASM_INT({
        إذا (!کړکۍ.سمون_Media) {
            أرجع -1;
        }

        إذا (کړکۍ.سمون_Media('(prefers-color-scheme: light)').matches) {
            أرجع 0;
        }

        إذا (کړکۍ.سمون_Media('(prefers-color-scheme: dark)').matches) {
            أرجع 1;
        }

        أرجع -1;
    });

    بدل (theme_کوډ) {
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
        إذا (کړکۍ.سمون_Media) {
            var SDL3 = Module['SDL3'];

            SDL3.event_Handler_Theme_بدل_شوی = function(event) {
                Emscripten_Send_System_Theme_بدل_شوی_Event();
            };

            SDL3.theme_بدل_شوی_سمون_Media = کړکۍ.سمون_Media('(prefers-color-scheme: dark)');
            SDL3.theme_بدل_شوی_سمون_Media.جمع_کړه_Event_Listener('change', SDL3.event_Handler_Theme_بدل_شوی);
        }
    });
}

ساكن فراغ Emscripten_UnlistenSystemTheme(فراغ)
{
    MAIN_THREAD_EM_ASM({
        إذا (typeof(Module['SDL3']) !== 'undefined') {
            var SDL3 = Module['SDL3'];

            SDL3.theme_بدل_شوی_سمون_Media.removeEventListener('change', SDL3.event_Handler_Theme_بدل_شوی);
            SDL3.theme_بدل_شوی_سمون_Media = undefined;
            SDL3.event_Handler_Theme_بدل_شوی = undefined;
        }
    });
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Send_System_Theme_بدل_شوی_Event_2(فراغ)
{
    SDL_سېټ_System_Theme(Emscripten_GetSystemTheme());
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
    SDL_سېټ_Hint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

    // Set the function pointers
    device->VideoInit = Emscripten_VideoInit;
    device->VideoQuit = Emscripten_VideoQuit;
    device->GetDisplayUsableBounds = Emscripten_GetDisplayUsableBounds;
    device->سېټ_Display_ډېرپېښ = Emscripten_سېټ_Display_ډېرپېښ;

    device->PumpEvents = Emscripten_PumpEvents;

    device->CreateSDLWindow = Emscripten_Create_کړکۍ;
    device->سېټ_کړکۍ_Title = Emscripten_سېټ_کړکۍ_Title;
    device->سېټ_کړکۍ_Icon = Emscripten_سېټ_کړکۍ_Icon;
    /*device->SetWindowPosition = Emscripten_SetWindowPosition;*/
    device->سېټ_کړکۍ_اندازه = Emscripten_سېټ_کړکۍ_اندازه;
    device->سېټ_کړکۍ_Resizable = Emscripten_سېټ_کړکۍ_Resizable;
    /*device->ShowWindow = Emscripten_ShowWindow;
    device->HideWindow = Emscripten_HideWindow;
    device->RaiseWindow = Emscripten_RaiseWindow;
    device->MaximizeWindow = Emscripten_MaximizeWindow;
    device->MinimizeWindow = Emscripten_MinimizeWindow;
    device->RestoreWindow = Emscripten_RestoreWindow;
    device->SetWindowMouseGrab = Emscripten_SetWindowMouseGrab;*/
    device->Get_کړکۍ_اندازه_دننه_Pixels = Emscripten_Get_کړکۍ_اندازه_دننه_Pixels;
    device->Destroy_کړکۍ = Emscripten_Destroy_کړکۍ;
    device->سېټ_کړکۍ_Fullscreen = Emscripten_سېټ_کړکۍ_Fullscreen;
    device->سېټ_کړکۍ_Fill_Document = Emscripten_سېټ_کړکۍ_Fill_Document;

    device->Create_کړکۍ_Framebuffer = Emscripten_Create_کړکۍ_Framebuffer;
    device->Update_کړکۍ_Framebuffer = Emscripten_Update_کړکۍ_Framebuffer;
    device->Destroy_کړکۍ_Framebuffer = Emscripten_Destroy_کړکۍ_Framebuffer;

    device->GL_بارول_Library = Emscripten_GLES_بارول_Library;
    device->GL_Get_Proc_پته = Emscripten_GLES_Get_Proc_پته;
    device->GL_UnloadLibrary = Emscripten_GLES_UnloadLibrary;
    device->GL_CreateContext = Emscripten_GLES_CreateContext;
    device->GL_MakeCurrent = Emscripten_GLES_MakeCurrent;
    device->GL_سېټ_بدلون_Interval = Emscripten_GLES_سېټ_بدلون_Interval;
    device->GL_Get_بدلون_Interval = Emscripten_GLES_Get_بدلون_Interval;
    device->GL_بدلون_کړکۍ = Emscripten_GLES_بدلون_کړکۍ;
    device->GL_DestroyContext = Emscripten_GLES_DestroyContext;

    device->حرر = Emscripten_DeleteDevice;

    Emscripten_ListenSystemTheme();
    device->system_theme = Emscripten_GetSystemTheme();

    أرجع device;
}

ساكن bool Emscripten_ShowMessagebox(ثابت SDL_پیغام_Box_معلومات *messageboxdata, صحيح *buttonID) {
    إذا (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        حرف dialog_background[32];
        حرف dialog_color[32];
        حرف button_border[32];
        حرف button_background[32];
        حرف button_hovered[32];

        إذا (messageboxdata->colorScheme) {
            SDL_پیغام_Box_Color color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND];
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
        SDL_snprintf(dialog_id, حجم(dialog_id), "SDL3_messagebox_%u", SDL_rand_بټونه());
        EM_ASM({
            var title = UTF8_منزل_String($0);
            var پیغام = UTF8_منزل_String($1);
            var background = UTF8_منزل_String($2);
            var color = UTF8_منزل_String($3);
            var id = UTF8_منزل_String($4);

            // Dialogs are always put in the front of the DOM
            var dialog = document.createElement("dialog");
            // Set class to allow for CSS selectors
            dialog.classList.جمع_کړه("SDL3_messagebox");
            dialog.id = id;
            dialog.style.color = color;
            dialog.style.backgroundColor = background;
            document.body.append(dialog);

            var h1 = document.createElement("h1");
            h1.inner_متن = title;
            dialog.append(h1);

            var p = document.createElement("p");
            p.inner_متن = پیغام;
            dialog.append(p);

            dialog.showModal();
        }, messageboxdata->title, messageboxdata->پیغام, dialog_background, dialog_color, dialog_id);

        صحيح i;
        لكل (i = 0; i < messageboxdata->numbuttons; ++i) {
            SDL_پیغام_Box_Button_معلومات button = messageboxdata->buttons[i];

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

                    dialog.جمع_کړه_Event_Listener('keydown', function(e) {
                        إذا (clickOnReturn && e.کلی === "Enter") {
                            e.preventDefault();
                            button.click();
                        } وإلا إذا (clickOnEscape && e.کلی === "Escape") {
                            e.preventDefault();
                            button.click();
                        }
                    });
                    dialog.جمع_کړه_Event_Listener('cancel', function(e){
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
                    أرجع parseInt(dialog.return_ارزښت);
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
        }, messageboxdata->title, messageboxdata->پیغام);
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
    SDL_Display_ډېرپېښ ډېرپېښ;

    // Use a fake 32-bpp desktop mode
    SDL_zero(ډېرپېښ);
    ډېرپېښ.format = SDL_PIXELFORMAT_RGBA32;
    emscripten_get_screen_اندازه(&ډېرپېښ.w, &ډېرپېښ.h);
    ډېرپېښ.pixel_density = emscripten_get_device_pixel_نسبت();

    إذا (SDL_جمع_کړه_Basic_Video_Display(&ډېرپېښ) == 0) {
        أرجع false;
    }

    Emscripten_InitMouse();

    // Assume we have a mouse and keyboard
    SDL_جمع_کړه_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_جمع_کړه_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);

    Emscripten_ثبتوونکی_Global_Event_Handlers(_this);

    // We're done!
    أرجع true;
}

ساكن bool Emscripten_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    // can't do this
    أرجع true;
}

ساكن فراغ Emscripten_VideoQuit(SDL_VideoDevice *_this)
{
    Emscripten_UnregisterGlobalEventHandlers(_this);
    Emscripten_QuitMouse();
    Emscripten_UnlistenSystemTheme();
    pumpevents_has_پرلپسې = false;
    pending_بدلون_interval = -1;
}

ساكن bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    إذا (rect) {
        rect->x = 0;
        rect->y = 0;
        rect->w = MAIN_THREAD_EM_ASM_INT({
            أرجع کړکۍ.inner_پلنوالی;
        });
        rect->h = MAIN_THREAD_EM_ASM_INT({
            أرجع کړکۍ.inner_لوړوالی;
        });
    }
    أرجع true;
}

bool Emscripten_Should_سېټ_بدلون_Interval(صحيح interval)
{
    إذا (!pumpevents_has_پرلپسې) {
        pending_بدلون_interval = interval;
        أرجع false;
    }
    أرجع true;
}

صحيح Emscripten_Get_Pending_بدلون_Interval(فراغ)
{
    أرجع pending_بدلون_interval;
}

ساكن فراغ Emscripten_PumpEvents(SDL_VideoDevice *_this)
{
    إذا (!pumpevents_has_پرلپسې) {
        // we assume you've set a mainloop by the time you've called pumpevents, so we delay initial SetInterval changes until then.
        // otherwise you'll get a warning on the javascript console.
        pumpevents_has_پرلپسې = true;
        إذا (pending_بدلون_interval >= 0) {
            Emscripten_GLES_سېټ_بدلون_Interval(_this, pending_بدلون_interval);
            pending_بدلون_interval = -1;
        }
    }
}

EMSCRIPTEN_KEEPALIVE فراغ requestFullscreenThroughSDL(SDL_کړکۍ *کړکۍ)
{
    SDL_سېټ_کړکۍ_Fullscreen(کړکۍ, true);
}

ساكن bool Emscripten_سېټ_کړکۍ_Fill_Document(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool fill)
{
    SDL_کړکۍ_معلومات *wdata = کړکۍ->دننی;

    إذا (fill && Emscripten_fill_document_کړکۍ && (Emscripten_fill_document_کړکۍ != کړکۍ)) {
        أرجع SDL_سېټ_Error("Only one fill-document window allowed at a time.");
    }

    // fill_document takes up the entire page and resizes as the browser window resizes.
    إذا (fill) {
        Emscripten_fill_document_کړکۍ = کړکۍ;

        ثابت صحيح w = MAIN_THREAD_EM_ASM_INT({ أرجع کړکۍ.inner_پلنوالی; });
        ثابت صحيح h = MAIN_THREAD_EM_ASM_INT({ أرجع کړکۍ.inner_لوړوالی; });
        ثابت مزدوج scaled_w = w * wdata->pixel_نسبت;
        ثابت مزدوج scaled_h = h * wdata->pixel_نسبت;

        wdata->non_fill_document_پلنوالی = کړکۍ->w;
        wdata->non_fill_document_لوړوالی = کړکۍ->h;

        MAIN_THREAD_EM_ASM({
            var canvas = document.querySelector(UTF8_منزل_String($0));
            canvas.SDL3_original_position = canvas.style.position;
            canvas.SDL3_original_سر = canvas.style.سر;
            canvas.SDL3_original_کیڼ = canvas.style.کیڼ;

            // hide everything on the page that isn't the canvas.
            var div = document.createElement('div');
            div.id = 'SDL3_fill_document_background_elements';

            div.SDL3_canvas = canvas;
            div.SDL3_canvas_پلار = canvas.پلار_غوټه;
            div.SDL3_canvas_nextsib = canvas.بل_Sibling;

            var children = Array.from(document.body.children);
            لكل (var ماشوم د children) {
                div.append_ماشوم(ماشوم);
            }
            document.body.append_ماشوم(div);
            div.style.display = 'none';
            document.body.append_ماشوم(canvas);
            canvas.style.position = 'fixed';
            canvas.style.سر = '0';
            canvas.style.کیڼ = '0';
        }, wdata->canvas_id);

        emscripten_سېټ_canvas_element_اندازه(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // set_canvas_size unsets this
        إذا (wdata->pixel_نسبت != 1.0f) {
            emscripten_سېټ_element_css_اندازه(wdata->canvas_id, w, h);
        }

        // force the event to trigger, so pixel ratio changes can be handled
        کړکۍ->w = کړکۍ->h = 0;
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    } وإلا {
        ثابت bool transitioning = (Emscripten_fill_document_کړکۍ == کړکۍ);
        إذا (transitioning) {
            MAIN_THREAD_EM_ASM({
                // if we had previously hidden everything behind a fill_document window, put it back.
                var div = document.getElementById('SDL3_fill_document_background_elements');
                إذا (div) {
                    إذا (div.SDL3_canvas_nextsib) {
                        div.SDL3_canvas_پلار.ورننباسه_Before(div.SDL3_canvas, div.SDL3_canvas_nextsib);
                    } وإلا {
                        div.SDL3_canvas_پلار.append_ماشوم(div.SDL3_canvas);
                    }
                    طالما (div.لومړی_ماشوم_2) {
                        document.body.ورننباسه_Before(div.لومړی_ماشوم_2, div);
                    }
                    div.SDL3_canvas.style.position = div.SDL3_canvas.SDL3_original_position;
                    div.SDL3_canvas.style.سر = div.SDL3_canvas.SDL3_original_سر;
                    div.SDL3_canvas.style.کیڼ = div.SDL3_canvas.SDL3_original_کیڼ;
                    div.remove();
                }
            });
            Emscripten_fill_document_کړکۍ = عدم;
        }

        کړکۍ->w = wdata->non_fill_document_پلنوالی;
        کړکۍ->h = wdata->non_fill_document_لوړوالی;
        ثابت مزدوج scaled_w = SDL_floor(کړکۍ->w * wdata->pixel_نسبت);
        ثابت مزدوج scaled_h = SDL_floor(کړکۍ->h * wdata->pixel_نسبت);
        emscripten_سېټ_canvas_element_اندازه(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // if the size is not being controlled by css, we need to scale down for hidpi
        إذا (!wdata->external_اندازه && (wdata->pixel_نسبت != 1.0f)) {
            // scale canvas down
            emscripten_سېټ_element_css_اندازه(wdata->canvas_id, کړکۍ->w, کړکۍ->h);
        }

        إذا (transitioning) {
            کړکۍ->w = کړکۍ->h = 0;
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, wdata->non_fill_document_پلنوالی, wdata->non_fill_document_لوړوالی);
        }
    }

    أرجع true;
}

ساكن bool Emscripten_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props)
{
    SDL_کړکۍ_معلومات *wdata;
    مزدوج css_w, css_h;
    ثابت حرف *selector;

    bool fill_document = ((کړکۍ->flags & SDL_کړکۍ_FILL_DOCUMENT) != 0);
    إذا (fill_document && Emscripten_fill_document_کړکۍ) {
        fill_document = false;  // only one allowed at a time.
        کړکۍ->flags &= ~SDL_کړکۍ_FILL_DOCUMENT;   // !!! FIXME: should this fail instead?
    }

    // Allocate window internal data
    wdata = (SDL_کړکۍ_معلومات *)SDL_calloc(1, حجم(SDL_کړکۍ_معلومات));
    إذا (!wdata) {
        أرجع false;
    }

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR);
    إذا (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_کړکۍ_CREATE_EMSCRIPTEN_CANVAS_ID_STRING, "#canvas");
    }
    wdata->canvas_id = SDL_strdup(selector);

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
    إذا (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_کړکۍ_CREATE_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, "#window");
    }
    wdata->keyboard_element = SDL_strdup(selector);

    إذا (کړکۍ->flags & SDL_کړکۍ_لوړ_PIXEL_DENSITY) {
        wdata->pixel_نسبت = emscripten_get_device_pixel_نسبت();
    } وإلا {
        wdata->pixel_نسبت = 1.0f;
    }

    // set a fake size to check if there is any CSS sizing the canvas
    emscripten_سېټ_canvas_element_اندازه(wdata->canvas_id, 1, 1);
    emscripten_get_element_css_اندازه(wdata->canvas_id, &css_w, &css_h);

    wdata->external_اندازه = SDL_floor(css_w) != 1 || SDL_floor(css_h) != 1;
    إذا (wdata->external_اندازه) {
        fill_document = false;  // can't be resizable if something else is controlling it.
        کړکۍ->w = (صحيح) css_w;
        کړکۍ->h = (صحيح) css_h;
    }

    wdata->کړکۍ = کړکۍ;

    // Setup driver data for this window
    کړکۍ->دننی = wdata;

    wdata->non_fill_document_پلنوالی = کړکۍ->w;
    wdata->non_fill_document_لوړوالی = کړکۍ->h;
    Emscripten_سېټ_کړکۍ_Fill_Document(_this, کړکۍ, fill_document);

    // One window, it always has focus
    SDL_سېټ_Mouse_Focus(کړکۍ);
    SDL_سېټ_Keyboard_Focus(کړکۍ);

    Emscripten_ثبتوونکی_Event_Handlers(wdata);

    // Make the emscripten "fullscreen" button go through SDL.
    MAIN_THREAD_EM_ASM({
        Module['requestFullscreen'] = function(قلف_اشاره_ګر, resizeCanvas) {
            _requestFullscreenThroughSDL($0);
        };
    }, کړکۍ);

    // Ensure various things are added to the window's properties
    SDL_سېټ_String_Property(کړکۍ->props, SDL_PROP_کړکۍ_EMSCRIPTEN_CANVAS_ID_STRING, wdata->canvas_id);
    SDL_سېټ_String_Property(کړکۍ->props, SDL_PROP_کړکۍ_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, wdata->keyboard_element);

    // Window has been successfully created
    أرجع true;
}

ساكن فراغ Emscripten_سېټ_کړکۍ_Resizable(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ, bool resizable)
{
    // this function just has to exist or the higher level won't let the window change its SDL_WINDOW_RESIZABLE flag.
}

ساكن فراغ Emscripten_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    إذا (کړکۍ->دننی) {
        SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
        إذا (کړکۍ == Emscripten_fill_document_کړکۍ) {
            أرجع;  // canvas size is being dictated by the browser window size, refuse request.
        }

        // update pixel ratio
        إذا (کړکۍ->flags & SDL_کړکۍ_لوړ_PIXEL_DENSITY) {
            معلومات->pixel_نسبت = emscripten_get_device_pixel_نسبت();
        }
        emscripten_سېټ_canvas_element_اندازه(معلومات->canvas_id, SDL_lroundf(کړکۍ->pending.w * معلومات->pixel_نسبت), SDL_lroundf(کړکۍ->pending.h * معلومات->pixel_نسبت));

        // scale canvas down
        إذا (!معلومات->external_اندازه && معلومات->pixel_نسبت != 1.0f) {
            emscripten_سېټ_element_css_اندازه(معلومات->canvas_id, کړکۍ->pending.w, کړکۍ->pending.h);
        }

        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, کړکۍ->pending.w, کړکۍ->pending.h);
    }
}

ساكن فراغ Emscripten_Get_کړکۍ_اندازه_دننه_Pixels(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *w, صحيح *h)
{
    SDL_کړکۍ_معلومات *معلومات;
    إذا (کړکۍ->دننی) {
        معلومات = کړکۍ->دننی;
        *w = SDL_lroundf(کړکۍ->w * معلومات->pixel_نسبت);
        *h = SDL_lroundf(کړکۍ->h * معلومات->pixel_نسبت);
    }
}

ساكن فراغ Emscripten_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات;

    Emscripten_سېټ_کړکۍ_Fill_Document(_this, کړکۍ, false);

    إذا (کړکۍ->دننی) {
        معلومات = کړکۍ->دننی;

        Emscripten_UnregisterEventHandlers(معلومات);

        // We can't destroy the canvas, so resize it to zero instead
        emscripten_سېټ_canvas_element_اندازه(معلومات->canvas_id, 0, 0);
        إذا (معلومات->pixel_نسبت != 1.0f) {
            emscripten_سېټ_element_css_اندازه(معلومات->canvas_id, 1, 1);
        }
        SDL_free(معلومات->canvas_id);

        SDL_free(معلومات->keyboard_element);

        SDL_free(کړکۍ->دننی);
        کړکۍ->دننی = عدم;
    }

    MAIN_THREAD_EM_ASM({
        // just ignore clicks on the fullscreen button while there's no SDL window.
        Module['requestFullscreen'] = function(قلف_اشاره_ګر, resizeCanvas) {};
    });
}

ساكن SDL_Fullscreen_پایله Emscripten_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_کړکۍ_معلومات *معلومات;
    صحيح res = -1;

    إذا (کړکۍ->دننی) {
        معلومات = کړکۍ->دننی;

        إذا (معلومات->fullscreen_change_دننه_پرمختګ) {
            أرجع SDL_FULLSCREEN_FAILED;;
        }

        EmscriptenFullscreenChangeEvent fsevent;
        إذا (emscripten_get_fullscreen_حالت(&fsevent) == EMSCRIPTEN_پایله_SUCCESS) {
            إذا ((fullscreen == SDL_FULLSCREEN_OP_ENTER) == fsevent.isFullscreen) {
                أرجع SDL_FULLSCREEN_SUCCEEDED;  // already there.
            }
        }

        إذا (fullscreen) {
            EmscriptenFullscreenStrategy strategy;
            bool is_fullscreen_desktop = !کړکۍ->fullscreen_exclusive;

            SDL_zero(strategy);
            strategy.scale_ډېرپېښ = is_fullscreen_desktop ? EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH : EMSCRIPTEN_FULLSCREEN_SCALE_ASPECT;

            إذا (!is_fullscreen_desktop) {
                strategy.canvas_Resolution_Scale_ډېرپېښ = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
            } وإلا إذا (کړکۍ->flags & SDL_کړکۍ_لوړ_PIXEL_DENSITY) {
                strategy.canvas_Resolution_Scale_ډېرپېښ = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF;
            } وإلا {
                strategy.canvas_Resolution_Scale_ډېرپېښ = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
            }

            strategy.filtering_ډېرپېښ = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;

            strategy.canvasResizedCallback = Emscripten_HandleCanvasResize;
            strategy.canvas_Resized_Callback_User_معلومات = معلومات;

            معلومات->fullscreen_ډېرپېښ_flags = (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN);
            معلومات->fullscreen_resize = is_fullscreen_desktop;

            res = emscripten_request_fullscreen_strategy(معلومات->canvas_id, 1, &strategy);
        } وإلا {
            res = emscripten_exit_fullscreen();
        }
    }

    إذا (res == EMSCRIPTEN_پایله_SUCCESS) {
        معلومات->fullscreen_change_دننه_پرمختګ = true;   // even on success, this might animate to the new state.
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    } وإلا إذا (res == EMSCRIPTEN_پایله_DEFERRED) {
        معلومات->fullscreen_change_دننه_پرمختګ = true;
        أرجع SDL_FULLSCREEN_PENDING;
    } وإلا {
        أرجع SDL_FULLSCREEN_FAILED;
    }
}

ساكن فراغ Emscripten_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    emscripten_سېټ_کړکۍ_title(کړکۍ->title);
}

ساكن bool Emscripten_سېټ_کړکۍ_Icon(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_Surface *icon)
{
    // Create dynamic memory stream for PNG encoding
    SDL_IOStream *بهیر = SDL_IOFromDynamicMem();
    إذا (!بهیر) {
        أرجع false;
    }

    // Encode icon to PNG using SDL's native PNG encoder
    إذا (!SDL_SavePNG_IO(icon, بهیر, false)) {
        SDL_CloseIO(بهیر);
        أرجع false;
    }

    // Get the PNG data from the stream
    فراغ *png_معلومات = SDL_Get_اشاره_ګر_Property(
        SDL_GetIOProperties(بهیر),
        SDL_PROP_IOSTREAM_DYNAMIC_حافظه_اشاره_ګر,
        عدم
    );
    size_t png_اندازه = (size_t)SDL_GetIOSize(بهیر);

    // Pass PNG data to JavaScript
    MAIN_THREAD_EM_ASM({
        // Use `.slice` to make a copy of the data if we are dealing with a SharedArrayBuffer, or `.subarray` to create a
        // view into the existing buffer if its non-shared.
        var png_معلومات_2 = HEAPU8.بفر_2 instanceof Array_بفر ? HEAPU8.subarray($0, $0 + $1) : HEAPU8.ټوټه($0, $0 + $1);

        var blob = new Blob([png_معلومات_2], {type: 'image/png'});
        var url = URL.createObjectURL(blob);

        // Set as favicon (create link element if it doesn't exist)
        var link = document.querySelector("link[rel~='icon']");
        إذا (!link) {
            link = document.createElement('link');
            link.rel = 'icon';
            link.type = 'image/png';
            document.سر_2.append_ماشوم(link);
        }

        // Revoke old URL if it exists to prevent memory leaks
        إذا (link.href && link.href.startsWith('blob:')) {
            URL.revokeObjectURL(link.href);
        }

        link.href = url;
    }, png_معلومات, png_اندازه);

    SDL_CloseIO(بهیر);
    أرجع true;
}

#د_که_پای // SDL_VIDEO_DRIVER_EMSCRIPTEN
