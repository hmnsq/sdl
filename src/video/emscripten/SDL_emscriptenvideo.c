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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_EMSCRIPTEN

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../SDL_hints_c.h"

#ضمن "SDL_emscriptenvideo.h"
#ضمن "SDL_emscriptenopengles.h"
#ضمن "SDL_emscriptenframebuffer.h"
#ضمن "SDL_emscriptenevents.h"
#ضمن "SDL_emscriptenmouse.h"

#تعریف_کن EMSCRIPTENVID_DRIVER_NAME "emscripten"

// Initialization/Query functions
ساكن bool Emscripten_VideoInit(SDL_VideoDevice *_this);
ساكن bool Emscripten_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما);
ساكن فراغ Emscripten_VideoQuit(SDL_VideoDevice *_this);
ساكن bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

ساكن bool Emscripten_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props);
ساكن فراغ Emscripten_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
ساكن فراغ Emscripten_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره * پنجره, bool resizable);
ساكن فراغ Emscripten_Get_پنجره_اندازه_درون_Pixels(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *w, صحيح *h);
ساكن فراغ Emscripten_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
ساكن SDL_Fullscreen_نتیجه Emscripten_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ساكن فراغ Emscripten_PumpEvents(SDL_VideoDevice *_this);
ساكن فراغ Emscripten_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
ساكن bool Emscripten_مجموعه_پنجره_Icon(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_Surface *icon);
ساكن bool Emscripten_مجموعه_پنجره_Fill_Document(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool fill);

SDL_پنجره *Emscripten_fill_document_پنجره = عدم;

ساكن bool pumpevents_has_پیاپی = false;
ساكن صحيح pending_جابجا_interval = -1;

// Emscripten driver bootstrap functions

ساكن فراغ Emscripten_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ساكن SDL_SystemTheme Emscripten_GetSystemTheme(فراغ)
{
    /* Technically, light theme can mean explicit light theme or no preference.
       https://developer.mozilla.org/en-US/docs/Web/CSS/@media/prefers-color-scheme#syntax */

    صحيح theme_کد = MAIN_THREAD_EM_ASM_INT({
        إذا (!پنجره.تطابق_Media) {
            أرجع -1;
        }

        إذا (پنجره.تطابق_Media('(prefers-color-scheme: light)').matches) {
            أرجع 0;
        }

        إذا (پنجره.تطابق_Media('(prefers-color-scheme: dark)').matches) {
            أرجع 1;
        }

        أرجع -1;
    });

    بدل (theme_کد) {
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
        إذا (پنجره.تطابق_Media) {
            var SDL3 = Module['SDL3'];

            SDL3.event_Handler_Theme_تغییریافته = function(event) {
                Emscripten_Send_System_Theme_تغییریافته_Event();
            };

            SDL3.theme_تغییریافته_تطابق_Media = پنجره.تطابق_Media('(prefers-color-scheme: dark)');
            SDL3.theme_تغییریافته_تطابق_Media.جمع_کن_Event_Listener('change', SDL3.event_Handler_Theme_تغییریافته);
        }
    });
}

ساكن فراغ Emscripten_UnlistenSystemTheme(فراغ)
{
    MAIN_THREAD_EM_ASM({
        إذا (typeof(Module['SDL3']) !== 'undefined') {
            var SDL3 = Module['SDL3'];

            SDL3.theme_تغییریافته_تطابق_Media.removeEventListener('change', SDL3.event_Handler_Theme_تغییریافته);
            SDL3.theme_تغییریافته_تطابق_Media = undefined;
            SDL3.event_Handler_Theme_تغییریافته = undefined;
        }
    });
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Send_System_Theme_تغییریافته_Event_2(فراغ)
{
    SDL_مجموعه_System_Theme(Emscripten_GetSystemTheme());
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
    SDL_مجموعه_Hint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

    // Set the function pointers
    device->VideoInit = Emscripten_VideoInit;
    device->VideoQuit = Emscripten_VideoQuit;
    device->GetDisplayUsableBounds = Emscripten_GetDisplayUsableBounds;
    device->مجموعه_Display_نما = Emscripten_مجموعه_Display_نما;

    device->PumpEvents = Emscripten_PumpEvents;

    device->CreateSDLWindow = Emscripten_Create_پنجره;
    device->مجموعه_پنجره_Title = Emscripten_مجموعه_پنجره_Title;
    device->مجموعه_پنجره_Icon = Emscripten_مجموعه_پنجره_Icon;
    /*device->SetWindowPosition = Emscripten_SetWindowPosition;*/
    device->مجموعه_پنجره_اندازه = Emscripten_مجموعه_پنجره_اندازه;
    device->مجموعه_پنجره_Resizable = Emscripten_مجموعه_پنجره_Resizable;
    /*device->ShowWindow = Emscripten_ShowWindow;
    device->HideWindow = Emscripten_HideWindow;
    device->RaiseWindow = Emscripten_RaiseWindow;
    device->MaximizeWindow = Emscripten_MaximizeWindow;
    device->MinimizeWindow = Emscripten_MinimizeWindow;
    device->RestoreWindow = Emscripten_RestoreWindow;
    device->SetWindowMouseGrab = Emscripten_SetWindowMouseGrab;*/
    device->Get_پنجره_اندازه_درون_Pixels = Emscripten_Get_پنجره_اندازه_درون_Pixels;
    device->Destroy_پنجره = Emscripten_Destroy_پنجره;
    device->مجموعه_پنجره_Fullscreen = Emscripten_مجموعه_پنجره_Fullscreen;
    device->مجموعه_پنجره_Fill_Document = Emscripten_مجموعه_پنجره_Fill_Document;

    device->Create_پنجره_Framebuffer = Emscripten_Create_پنجره_Framebuffer;
    device->Update_پنجره_Framebuffer = Emscripten_Update_پنجره_Framebuffer;
    device->Destroy_پنجره_Framebuffer = Emscripten_Destroy_پنجره_Framebuffer;

    device->GL_بارگیری_Library = Emscripten_GLES_بارگیری_Library;
    device->GL_Get_Proc_آدرس = Emscripten_GLES_Get_Proc_آدرس;
    device->GL_UnloadLibrary = Emscripten_GLES_UnloadLibrary;
    device->GL_CreateContext = Emscripten_GLES_CreateContext;
    device->GL_MakeCurrent = Emscripten_GLES_MakeCurrent;
    device->GL_مجموعه_جابجا_Interval = Emscripten_GLES_مجموعه_جابجا_Interval;
    device->GL_Get_جابجا_Interval = Emscripten_GLES_Get_جابجا_Interval;
    device->GL_جابجا_پنجره = Emscripten_GLES_جابجا_پنجره;
    device->GL_DestroyContext = Emscripten_GLES_DestroyContext;

    device->حرر = Emscripten_DeleteDevice;

    Emscripten_ListenSystemTheme();
    device->system_theme = Emscripten_GetSystemTheme();

    أرجع device;
}

ساكن bool Emscripten_ShowMessagebox(ثابت SDL_پیام_Box_داده *messageboxdata, صحيح *buttonID) {
    إذا (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        حرف dialog_background[32];
        حرف dialog_color[32];
        حرف button_border[32];
        حرف button_background[32];
        حرف button_hovered[32];

        إذا (messageboxdata->colorScheme) {
            SDL_پیام_Box_Color color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND];
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
        SDL_snprintf(dialog_id, حجم(dialog_id), "SDL3_messagebox_%u", SDL_rand_بیتها());
        EM_ASM({
            var title = UTF8_مقصد_String($0);
            var پیام = UTF8_مقصد_String($1);
            var background = UTF8_مقصد_String($2);
            var color = UTF8_مقصد_String($3);
            var id = UTF8_مقصد_String($4);

            // Dialogs are always put in the front of the DOM
            var dialog = document.createElement("dialog");
            // Set class to allow for CSS selectors
            dialog.classList.جمع_کن("SDL3_messagebox");
            dialog.id = id;
            dialog.style.color = color;
            dialog.style.backgroundColor = background;
            document.body.append(dialog);

            var h1 = document.createElement("h1");
            h1.inner_متن = title;
            dialog.append(h1);

            var p = document.createElement("p");
            p.inner_متن = پیام;
            dialog.append(p);

            dialog.showModal();
        }, messageboxdata->title, messageboxdata->پیام, dialog_background, dialog_color, dialog_id);

        صحيح i;
        لكل (i = 0; i < messageboxdata->numbuttons; ++i) {
            SDL_پیام_Box_Button_داده button = messageboxdata->buttons[i];

            ثابت صحيح created = EM_ASM_INT({
                    var dialog_id = UTF8_مقصد_String($0);
                    var متن = UTF8_مقصد_String($1);
                    var responseId = $2;
                    var clickOnReturn = $3;
                    var clickOnEscape = $4;
                    var border = UTF8_مقصد_String($5);
                    var background = UTF8_مقصد_String($6);
                    var hovered = UTF8_مقصد_String($7);

                    var dialog = document.getElementById(dialog_id);
                    إذا (!dialog) {
                        أرجع false;
                    }

                    var button = document.createElement("button");
                    button.inner_متن = متن;
                    button.style.borderColor = border;
                    button.style.backgroundColor = background;

                    dialog.جمع_کن_Event_Listener('keydown', function(e) {
                        إذا (clickOnReturn && e.کلید === "Enter") {
                            e.preventDefault();
                            button.click();
                        } وإلا إذا (clickOnEscape && e.کلید === "Escape") {
                            e.preventDefault();
                            button.click();
                        }
                    });
                    dialog.جمع_کن_Event_Listener('cancel', function(e){
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
                var dialog_id = UTF8_مقصد_String($0);

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
                var dialog_id = UTF8_مقصد_String($0);
                var dialog = document.getElementById(dialog_id);
                إذا (!dialog) {
                    أرجع 0;
                }
                try
                {
                    أرجع parseInt(dialog.return_مقدار);
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
            alert(UTF8_مقصد_String($0) + "\n\n" + UTF8_مقصد_String($1));
        }, messageboxdata->title, messageboxdata->پیام);
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
    SDL_Display_نما نما;

    // Use a fake 32-bpp desktop mode
    SDL_zero(نما);
    نما.format = SDL_PIXELFORMAT_RGBA32;
    emscripten_get_screen_اندازه(&نما.w, &نما.h);
    نما.pixel_density = emscripten_get_device_pixel_نسبت();

    إذا (SDL_جمع_کن_Basic_Video_Display(&نما) == 0) {
        أرجع false;
    }

    Emscripten_InitMouse();

    // Assume we have a mouse and keyboard
    SDL_جمع_کن_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_جمع_کن_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);

    Emscripten_ثبات_Global_Event_Handlers(_this);

    // We're done!
    أرجع true;
}

ساكن bool Emscripten_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما)
{
    // can't do this
    أرجع true;
}

ساكن فراغ Emscripten_VideoQuit(SDL_VideoDevice *_this)
{
    Emscripten_UnregisterGlobalEventHandlers(_this);
    Emscripten_QuitMouse();
    Emscripten_UnlistenSystemTheme();
    pumpevents_has_پیاپی = false;
    pending_جابجا_interval = -1;
}

ساكن bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    إذا (rect) {
        rect->x = 0;
        rect->y = 0;
        rect->w = MAIN_THREAD_EM_ASM_INT({
            أرجع پنجره.inner_عرض;
        });
        rect->h = MAIN_THREAD_EM_ASM_INT({
            أرجع پنجره.inner_ارتفاع;
        });
    }
    أرجع true;
}

bool Emscripten_Should_مجموعه_جابجا_Interval(صحيح interval)
{
    إذا (!pumpevents_has_پیاپی) {
        pending_جابجا_interval = interval;
        أرجع false;
    }
    أرجع true;
}

صحيح Emscripten_Get_Pending_جابجا_Interval(فراغ)
{
    أرجع pending_جابجا_interval;
}

ساكن فراغ Emscripten_PumpEvents(SDL_VideoDevice *_this)
{
    إذا (!pumpevents_has_پیاپی) {
        // we assume you've set a mainloop by the time you've called pumpevents, so we delay initial SetInterval changes until then.
        // otherwise you'll get a warning on the javascript console.
        pumpevents_has_پیاپی = true;
        إذا (pending_جابجا_interval >= 0) {
            Emscripten_GLES_مجموعه_جابجا_Interval(_this, pending_جابجا_interval);
            pending_جابجا_interval = -1;
        }
    }
}

EMSCRIPTEN_KEEPALIVE فراغ requestFullscreenThroughSDL(SDL_پنجره *پنجره)
{
    SDL_مجموعه_پنجره_Fullscreen(پنجره, true);
}

ساكن bool Emscripten_مجموعه_پنجره_Fill_Document(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool fill)
{
    SDL_پنجره_داده *wdata = پنجره->داخلی;

    إذا (fill && Emscripten_fill_document_پنجره && (Emscripten_fill_document_پنجره != پنجره)) {
        أرجع SDL_مجموعه_Error("Only one fill-document window allowed at a time.");
    }

    // fill_document takes up the entire page and resizes as the browser window resizes.
    إذا (fill) {
        Emscripten_fill_document_پنجره = پنجره;

        ثابت صحيح w = MAIN_THREAD_EM_ASM_INT({ أرجع پنجره.inner_عرض; });
        ثابت صحيح h = MAIN_THREAD_EM_ASM_INT({ أرجع پنجره.inner_ارتفاع; });
        ثابت مزدوج scaled_w = w * wdata->pixel_نسبت;
        ثابت مزدوج scaled_h = h * wdata->pixel_نسبت;

        wdata->non_fill_document_عرض = پنجره->w;
        wdata->non_fill_document_ارتفاع = پنجره->h;

        MAIN_THREAD_EM_ASM({
            var canvas = document.querySelector(UTF8_مقصد_String($0));
            canvas.SDL3_original_position = canvas.style.position;
            canvas.SDL3_original_بالاترین = canvas.style.بالاترین;
            canvas.SDL3_original_چپ = canvas.style.چپ;

            // hide everything on the page that isn't the canvas.
            var div = document.createElement('div');
            div.id = 'SDL3_fill_document_background_elements';

            div.SDL3_canvas = canvas;
            div.SDL3_canvas_والد = canvas.والد_گره;
            div.SDL3_canvas_nextsib = canvas.بعدی_Sibling;

            var children = Array.from(document.body.children);
            لكل (var فرزند از children) {
                div.append_فرزند(فرزند);
            }
            document.body.append_فرزند(div);
            div.style.display = 'none';
            document.body.append_فرزند(canvas);
            canvas.style.position = 'fixed';
            canvas.style.بالاترین = '0';
            canvas.style.چپ = '0';
        }, wdata->canvas_id);

        emscripten_مجموعه_canvas_element_اندازه(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // set_canvas_size unsets this
        إذا (wdata->pixel_نسبت != 1.0f) {
            emscripten_مجموعه_element_css_اندازه(wdata->canvas_id, w, h);
        }

        // force the event to trigger, so pixel ratio changes can be handled
        پنجره->w = پنجره->h = 0;
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    } وإلا {
        ثابت bool transitioning = (Emscripten_fill_document_پنجره == پنجره);
        إذا (transitioning) {
            MAIN_THREAD_EM_ASM({
                // if we had previously hidden everything behind a fill_document window, put it back.
                var div = document.getElementById('SDL3_fill_document_background_elements');
                إذا (div) {
                    إذا (div.SDL3_canvas_nextsib) {
                        div.SDL3_canvas_والد.درج_Before(div.SDL3_canvas, div.SDL3_canvas_nextsib);
                    } وإلا {
                        div.SDL3_canvas_والد.append_فرزند(div.SDL3_canvas);
                    }
                    طالما (div.اولی_فرزند_2) {
                        document.body.درج_Before(div.اولی_فرزند_2, div);
                    }
                    div.SDL3_canvas.style.position = div.SDL3_canvas.SDL3_original_position;
                    div.SDL3_canvas.style.بالاترین = div.SDL3_canvas.SDL3_original_بالاترین;
                    div.SDL3_canvas.style.چپ = div.SDL3_canvas.SDL3_original_چپ;
                    div.remove();
                }
            });
            Emscripten_fill_document_پنجره = عدم;
        }

        پنجره->w = wdata->non_fill_document_عرض;
        پنجره->h = wdata->non_fill_document_ارتفاع;
        ثابت مزدوج scaled_w = SDL_floor(پنجره->w * wdata->pixel_نسبت);
        ثابت مزدوج scaled_h = SDL_floor(پنجره->h * wdata->pixel_نسبت);
        emscripten_مجموعه_canvas_element_اندازه(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // if the size is not being controlled by css, we need to scale down for hidpi
        إذا (!wdata->external_اندازه && (wdata->pixel_نسبت != 1.0f)) {
            // scale canvas down
            emscripten_مجموعه_element_css_اندازه(wdata->canvas_id, پنجره->w, پنجره->h);
        }

        إذا (transitioning) {
            پنجره->w = پنجره->h = 0;
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, wdata->non_fill_document_عرض, wdata->non_fill_document_ارتفاع);
        }
    }

    أرجع true;
}

ساكن bool Emscripten_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props)
{
    SDL_پنجره_داده *wdata;
    مزدوج css_w, css_h;
    ثابت حرف *selector;

    bool fill_document = ((پنجره->flags & SDL_پنجره_FILL_DOCUMENT) != 0);
    إذا (fill_document && Emscripten_fill_document_پنجره) {
        fill_document = false;  // only one allowed at a time.
        پنجره->flags &= ~SDL_پنجره_FILL_DOCUMENT;   // !!! FIXME: should this fail instead?
    }

    // Allocate window internal data
    wdata = (SDL_پنجره_داده *)SDL_calloc(1, حجم(SDL_پنجره_داده));
    إذا (!wdata) {
        أرجع false;
    }

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR);
    إذا (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_پنجره_CREATE_EMSCRIPTEN_CANVAS_ID_STRING, "#canvas");
    }
    wdata->canvas_id = SDL_strdup(selector);

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
    إذا (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_پنجره_CREATE_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, "#window");
    }
    wdata->keyboard_element = SDL_strdup(selector);

    إذا (پنجره->flags & SDL_پنجره_بالا_PIXEL_DENSITY) {
        wdata->pixel_نسبت = emscripten_get_device_pixel_نسبت();
    } وإلا {
        wdata->pixel_نسبت = 1.0f;
    }

    // set a fake size to check if there is any CSS sizing the canvas
    emscripten_مجموعه_canvas_element_اندازه(wdata->canvas_id, 1, 1);
    emscripten_get_element_css_اندازه(wdata->canvas_id, &css_w, &css_h);

    wdata->external_اندازه = SDL_floor(css_w) != 1 || SDL_floor(css_h) != 1;
    إذا (wdata->external_اندازه) {
        fill_document = false;  // can't be resizable if something else is controlling it.
        پنجره->w = (صحيح) css_w;
        پنجره->h = (صحيح) css_h;
    }

    wdata->پنجره = پنجره;

    // Setup driver data for this window
    پنجره->داخلی = wdata;

    wdata->non_fill_document_عرض = پنجره->w;
    wdata->non_fill_document_ارتفاع = پنجره->h;
    Emscripten_مجموعه_پنجره_Fill_Document(_this, پنجره, fill_document);

    // One window, it always has focus
    SDL_مجموعه_Mouse_Focus(پنجره);
    SDL_مجموعه_Keyboard_Focus(پنجره);

    Emscripten_ثبات_Event_Handlers(wdata);

    // Make the emscripten "fullscreen" button go through SDL.
    MAIN_THREAD_EM_ASM({
        Module['requestFullscreen'] = function(قفل_اشاره_گر, resizeCanvas) {
            _requestFullscreenThroughSDL($0);
        };
    }, پنجره);

    // Ensure various things are added to the window's properties
    SDL_مجموعه_String_Property(پنجره->props, SDL_PROP_پنجره_EMSCRIPTEN_CANVAS_ID_STRING, wdata->canvas_id);
    SDL_مجموعه_String_Property(پنجره->props, SDL_PROP_پنجره_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, wdata->keyboard_element);

    // Window has been successfully created
    أرجع true;
}

ساكن فراغ Emscripten_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره * پنجره, bool resizable)
{
    // this function just has to exist or the higher level won't let the window change its SDL_WINDOW_RESIZABLE flag.
}

ساكن فراغ Emscripten_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    إذا (پنجره->داخلی) {
        SDL_پنجره_داده *داده = پنجره->داخلی;
        إذا (پنجره == Emscripten_fill_document_پنجره) {
            أرجع;  // canvas size is being dictated by the browser window size, refuse request.
        }

        // update pixel ratio
        إذا (پنجره->flags & SDL_پنجره_بالا_PIXEL_DENSITY) {
            داده->pixel_نسبت = emscripten_get_device_pixel_نسبت();
        }
        emscripten_مجموعه_canvas_element_اندازه(داده->canvas_id, SDL_lroundf(پنجره->pending.w * داده->pixel_نسبت), SDL_lroundf(پنجره->pending.h * داده->pixel_نسبت));

        // scale canvas down
        إذا (!داده->external_اندازه && داده->pixel_نسبت != 1.0f) {
            emscripten_مجموعه_element_css_اندازه(داده->canvas_id, پنجره->pending.w, پنجره->pending.h);
        }

        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, پنجره->pending.w, پنجره->pending.h);
    }
}

ساكن فراغ Emscripten_Get_پنجره_اندازه_درون_Pixels(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *w, صحيح *h)
{
    SDL_پنجره_داده *داده;
    إذا (پنجره->داخلی) {
        داده = پنجره->داخلی;
        *w = SDL_lroundf(پنجره->w * داده->pixel_نسبت);
        *h = SDL_lroundf(پنجره->h * داده->pixel_نسبت);
    }
}

ساكن فراغ Emscripten_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده;

    Emscripten_مجموعه_پنجره_Fill_Document(_this, پنجره, false);

    إذا (پنجره->داخلی) {
        داده = پنجره->داخلی;

        Emscripten_UnregisterEventHandlers(داده);

        // We can't destroy the canvas, so resize it to zero instead
        emscripten_مجموعه_canvas_element_اندازه(داده->canvas_id, 0, 0);
        إذا (داده->pixel_نسبت != 1.0f) {
            emscripten_مجموعه_element_css_اندازه(داده->canvas_id, 1, 1);
        }
        SDL_free(داده->canvas_id);

        SDL_free(داده->keyboard_element);

        SDL_free(پنجره->داخلی);
        پنجره->داخلی = عدم;
    }

    MAIN_THREAD_EM_ASM({
        // just ignore clicks on the fullscreen button while there's no SDL window.
        Module['requestFullscreen'] = function(قفل_اشاره_گر, resizeCanvas) {};
    });
}

ساكن SDL_Fullscreen_نتیجه Emscripten_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_پنجره_داده *داده;
    صحيح res = -1;

    إذا (پنجره->داخلی) {
        داده = پنجره->داخلی;

        إذا (داده->fullscreen_change_درون_پیشرفت) {
            أرجع SDL_FULLSCREEN_FAILED;;
        }

        EmscriptenFullscreenChangeEvent fsevent;
        إذا (emscripten_get_fullscreen_وضعیت(&fsevent) == EMSCRIPTEN_نتیجه_SUCCESS) {
            إذا ((fullscreen == SDL_FULLSCREEN_OP_ENTER) == fsevent.isFullscreen) {
                أرجع SDL_FULLSCREEN_SUCCEEDED;  // already there.
            }
        }

        إذا (fullscreen) {
            EmscriptenFullscreenStrategy strategy;
            bool is_fullscreen_desktop = !پنجره->fullscreen_exclusive;

            SDL_zero(strategy);
            strategy.scale_نما = is_fullscreen_desktop ? EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH : EMSCRIPTEN_FULLSCREEN_SCALE_ASPECT;

            إذا (!is_fullscreen_desktop) {
                strategy.canvas_Resolution_Scale_نما = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
            } وإلا إذا (پنجره->flags & SDL_پنجره_بالا_PIXEL_DENSITY) {
                strategy.canvas_Resolution_Scale_نما = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF;
            } وإلا {
                strategy.canvas_Resolution_Scale_نما = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
            }

            strategy.filtering_نما = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;

            strategy.canvasResizedCallback = Emscripten_HandleCanvasResize;
            strategy.canvas_Resized_Callback_User_داده = داده;

            داده->fullscreen_نما_flags = (پنجره->flags & SDL_پنجره_FULLSCREEN);
            داده->fullscreen_resize = is_fullscreen_desktop;

            res = emscripten_request_fullscreen_strategy(داده->canvas_id, 1, &strategy);
        } وإلا {
            res = emscripten_exit_fullscreen();
        }
    }

    إذا (res == EMSCRIPTEN_نتیجه_SUCCESS) {
        داده->fullscreen_change_درون_پیشرفت = true;   // even on success, this might animate to the new state.
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    } وإلا إذا (res == EMSCRIPTEN_نتیجه_DEFERRED) {
        داده->fullscreen_change_درون_پیشرفت = true;
        أرجع SDL_FULLSCREEN_PENDING;
    } وإلا {
        أرجع SDL_FULLSCREEN_FAILED;
    }
}

ساكن فراغ Emscripten_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    emscripten_مجموعه_پنجره_title(پنجره->title);
}

ساكن bool Emscripten_مجموعه_پنجره_Icon(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_Surface *icon)
{
    // Create dynamic memory stream for PNG encoding
    SDL_IOStream *جریان = SDL_IOFromDynamicMem();
    إذا (!جریان) {
        أرجع false;
    }

    // Encode icon to PNG using SDL's native PNG encoder
    إذا (!SDL_SavePNG_IO(icon, جریان, false)) {
        SDL_CloseIO(جریان);
        أرجع false;
    }

    // Get the PNG data from the stream
    فراغ *png_داده = SDL_Get_اشاره_گر_Property(
        SDL_GetIOProperties(جریان),
        SDL_PROP_IOSTREAM_DYNAMIC_حافظه_اشاره_گر,
        عدم
    );
    size_t png_اندازه = (size_t)SDL_GetIOSize(جریان);

    // Pass PNG data to JavaScript
    MAIN_THREAD_EM_ASM({
        // Use `.slice` to make a copy of the data if we are dealing with a SharedArrayBuffer, or `.subarray` to create a
        // view into the existing buffer if its non-shared.
        var png_داده_2 = HEAPU8.میانگیر_2 instanceof Array_میانگیر ? HEAPU8.subarray($0, $0 + $1) : HEAPU8.برش($0, $0 + $1);

        var blob = new Blob([png_داده_2], {type: 'image/png'});
        var url = URL.createObjectURL(blob);

        // Set as favicon (create link element if it doesn't exist)
        var link = document.querySelector("link[rel~='icon']");
        إذا (!link) {
            link = document.createElement('link');
            link.rel = 'icon';
            link.type = 'image/png';
            document.سر.append_فرزند(link);
        }

        // Revoke old URL if it exists to prevent memory leaks
        إذا (link.href && link.href.startsWith('blob:')) {
            URL.revokeObjectURL(link.href);
        }

        link.href = url;
    }, png_داده, png_اندازه);

    SDL_CloseIO(جریان);
    أرجع true;
}

#پایان_اگر // SDL_VIDEO_DRIVER_EMSCRIPTEN
