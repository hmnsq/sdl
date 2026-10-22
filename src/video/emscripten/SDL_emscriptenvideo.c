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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_EMSCRIPTEN

#شامل "../SDL_sysvideo.h"
#شامل "../SDL_pixels_c.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../SDL_hints_c.h"

#شامل "SDL_emscriptenvideo.h"
#شامل "SDL_emscriptenopengles.h"
#شامل "SDL_emscriptenframebuffer.h"
#شامل "SDL_emscriptenevents.h"
#شامل "SDL_emscriptenmouse.h"

#تعریف_کرو EMSCRIPTENVID_DRIVER_NAME "emscripten"

// Initialization/Query functions
ساکن bool Emscripten_VideoInit(SDL_VideoDevice *_this);
ساکن bool Emscripten_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
ساکن خالی Emscripten_VideoQuit(SDL_VideoDevice *_this);
ساکن bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

ساکن bool Emscripten_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
ساکن خالی Emscripten_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
ساکن خالی Emscripten_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, bool resizable);
ساکن خالی Emscripten_Get_کھڑکی_سائز_اندر_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *w, صحیح *h);
ساکن خالی Emscripten_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
ساکن SDL_Fullscreen_نتیجہ Emscripten_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ساکن خالی Emscripten_PumpEvents(SDL_VideoDevice *_this);
ساکن خالی Emscripten_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
ساکن bool Emscripten_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon);
ساکن bool Emscripten_سیٹ_کھڑکی_Fill_Document(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool fill);

SDL_کھڑکی *Emscripten_fill_document_کھڑکی = تہی;

ساکن bool pumpevents_has_تسلسل = false;
ساکن صحیح pending_تبادلہ_interval = -1;

// Emscripten driver bootstrap functions

ساکن خالی Emscripten_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ساکن SDL_SystemTheme Emscripten_GetSystemTheme(خالی)
{
    /* Technically, light theme can mean explicit light theme or no preference.
       https://developer.mozilla.org/en-US/docs/Web/CSS/@media/prefers-color-scheme#syntax */

    صحیح theme_رمز = MAIN_THREAD_EM_ASM_INT({
        اگر (!کھڑکی.مطابقت_Media) {
            واپس -1;
        }

        اگر (کھڑکی.مطابقت_Media('(prefers-color-scheme: light)').matches) {
            واپس 0;
        }

        اگر (کھڑکی.مطابقت_Media('(prefers-color-scheme: dark)').matches) {
            واپس 1;
        }

        واپس -1;
    });

    انتخاب (theme_رمز) {
    حالت 0:
        واپس SDL_SYSTEM_THEME_LIGHT;

    حالت 1:
        واپس SDL_SYSTEM_THEME_DARK;

    طےشدہ:
        واپس SDL_SYSTEM_THEME_UNKNOWN;
    }
}

ساکن خالی Emscripten_ListenSystemTheme(خالی)
{
    MAIN_THREAD_EM_ASM({
        اگر (کھڑکی.مطابقت_Media) {
            var SDL3 = Module['SDL3'];

            SDL3.event_Handler_Theme_بدلا = function(event) {
                Emscripten_Send_System_Theme_بدلا_Event();
            };

            SDL3.theme_بدلا_مطابقت_Media = کھڑکی.مطابقت_Media('(prefers-color-scheme: dark)');
            SDL3.theme_بدلا_مطابقت_Media.جوڑو_Event_Listener('change', SDL3.event_Handler_Theme_بدلا);
        }
    });
}

ساکن خالی Emscripten_UnlistenSystemTheme(خالی)
{
    MAIN_THREAD_EM_ASM({
        اگر (typeof(Module['SDL3']) !== 'undefined') {
            var SDL3 = Module['SDL3'];

            SDL3.theme_بدلا_مطابقت_Media.removeEventListener('change', SDL3.event_Handler_Theme_بدلا);
            SDL3.theme_بدلا_مطابقت_Media = undefined;
            SDL3.event_Handler_Theme_بدلا = undefined;
        }
    });
}

EMSCRIPTEN_KEEPALIVE خالی Emscripten_Send_System_Theme_بدلا_Event_2(خالی)
{
    SDL_سیٹ_System_Theme(Emscripten_GetSystemTheme());
}

ساکن SDL_VideoDevice *Emscripten_CreateDevice(خالی)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
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
    device->سیٹ_کھڑکی_سائز = Emscripten_سیٹ_کھڑکی_سائز;
    device->سیٹ_کھڑکی_Resizable = Emscripten_سیٹ_کھڑکی_Resizable;
    /*device->ShowWindow = Emscripten_ShowWindow;
    device->HideWindow = Emscripten_HideWindow;
    device->RaiseWindow = Emscripten_RaiseWindow;
    device->MaximizeWindow = Emscripten_MaximizeWindow;
    device->MinimizeWindow = Emscripten_MinimizeWindow;
    device->RestoreWindow = Emscripten_RestoreWindow;
    device->SetWindowMouseGrab = Emscripten_SetWindowMouseGrab;*/
    device->Get_کھڑکی_سائز_اندر_Pixels = Emscripten_Get_کھڑکی_سائز_اندر_Pixels;
    device->Destroy_کھڑکی = Emscripten_Destroy_کھڑکی;
    device->سیٹ_کھڑکی_Fullscreen = Emscripten_سیٹ_کھڑکی_Fullscreen;
    device->سیٹ_کھڑکی_Fill_Document = Emscripten_سیٹ_کھڑکی_Fill_Document;

    device->Create_کھڑکی_Framebuffer = Emscripten_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = Emscripten_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = Emscripten_Destroy_کھڑکی_Framebuffer;

    device->GL_بھرو_Library = Emscripten_GLES_بھرو_Library;
    device->GL_Get_Proc_پتہ = Emscripten_GLES_Get_Proc_پتہ;
    device->GL_UnloadLibrary = Emscripten_GLES_UnloadLibrary;
    device->GL_CreateContext = Emscripten_GLES_CreateContext;
    device->GL_MakeCurrent = Emscripten_GLES_MakeCurrent;
    device->GL_سیٹ_تبادلہ_Interval = Emscripten_GLES_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = Emscripten_GLES_Get_تبادلہ_Interval;
    device->GL_تبادلہ_کھڑکی = Emscripten_GLES_تبادلہ_کھڑکی;
    device->GL_DestroyContext = Emscripten_GLES_DestroyContext;

    device->آزاد = Emscripten_DeleteDevice;

    Emscripten_ListenSystemTheme();
    device->system_theme = Emscripten_GetSystemTheme();

    واپس device;
}

ساکن bool Emscripten_ShowMessagebox(ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonID) {
    اگر (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        حرف dialog_background[32];
        حرف dialog_color[32];
        حرف button_border[32];
        حرف button_background[32];
        حرف button_hovered[32];

        اگر (messageboxdata->colorScheme) {
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
        } ورنہ {
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
            var title = UTF8_مقصد_String($0);
            var پیغام = UTF8_مقصد_String($1);
            var background = UTF8_مقصد_String($2);
            var color = UTF8_مقصد_String($3);
            var id = UTF8_مقصد_String($4);

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
            p.inner_متن = پیغام;
            dialog.append(p);

            dialog.showModal();
        }, messageboxdata->title, messageboxdata->پیغام, dialog_background, dialog_color, dialog_id);

        صحیح i;
        برائے (i = 0; i < messageboxdata->numbuttons; ++i) {
            SDL_پیغام_Box_Button_ڈیٹا button = messageboxdata->buttons[i];

            ثابت صحیح created = EM_ASM_INT({
                    var dialog_id = UTF8_مقصد_String($0);
                    var متن = UTF8_مقصد_String($1);
                    var responseId = $2;
                    var clickOnReturn = $3;
                    var clickOnEscape = $4;
                    var border = UTF8_مقصد_String($5);
                    var background = UTF8_مقصد_String($6);
                    var hovered = UTF8_مقصد_String($7);

                    var dialog = document.getElementById(dialog_id);
                    اگر (!dialog) {
                        واپس false;
                    }

                    var button = document.createElement("button");
                    button.inner_متن = متن;
                    button.style.borderColor = border;
                    button.style.backgroundColor = background;

                    dialog.جوڑو_Event_Listener('keydown', function(e) {
                        اگر (clickOnReturn && e.کلید === "Enter") {
                            e.preventDefault();
                            button.click();
                        } ورنہ اگر (clickOnEscape && e.کلید === "Escape") {
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
                    واپس true;
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

            اگر (!created) {
                واپس false;
            }
        }

        جب (true) {
            // give back control to browser for screen refresh
            emscripten_sleep(0);

            ثابت صحیح dialog_open = EM_ASM_INT({
                var dialog_id = UTF8_مقصد_String($0);

                var dialog = document.getElementById(dialog_id);
                اگر (!dialog) {
                    واپس false;
                }
                واپس dialog.open;
            }, dialog_id);

            اگر (dialog_open) {
                جاری;
            }

            *buttonID = EM_ASM_INT({
                var dialog_id = UTF8_مقصد_String($0);
                var dialog = document.getElementById(dialog_id);
                اگر (!dialog) {
                    واپس 0;
                }
                try
                {
                    واپس parseInt(dialog.return_قدر);
                }
                catch(e)
                {
                    واپس 0;
                }
            }, dialog_id);
            توڑو;
        }

    } ورنہ {
        // Cannot add elements to DOM and block without Asyncify. So, fall back to the alert function.
        EM_ASM({
            alert(UTF8_مقصد_String($0) + "\n\n" + UTF8_مقصد_String($1));
        }, messageboxdata->title, messageboxdata->پیغام);
    }
    واپس true;
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
    emscripten_get_screen_سائز(&منوال.w, &منوال.h);
    منوال.pixel_density = emscripten_get_device_pixel_تناسب();

    اگر (SDL_جوڑو_Basic_Video_Display(&منوال) == 0) {
        واپس false;
    }

    Emscripten_InitMouse();

    // Assume we have a mouse and keyboard
    SDL_جوڑو_Keyboard(SDL_DEFAULT_KEYBOARD_ID, تہی);
    SDL_جوڑو_Mouse(SDL_DEFAULT_MOUSE_ID, تہی);

    Emscripten_رجسٹر_Global_Event_Handlers(_this);

    // We're done!
    واپس true;
}

ساکن bool Emscripten_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    // can't do this
    واپس true;
}

ساکن خالی Emscripten_VideoQuit(SDL_VideoDevice *_this)
{
    Emscripten_UnregisterGlobalEventHandlers(_this);
    Emscripten_QuitMouse();
    Emscripten_UnlistenSystemTheme();
    pumpevents_has_تسلسل = false;
    pending_تبادلہ_interval = -1;
}

ساکن bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    اگر (rect) {
        rect->x = 0;
        rect->y = 0;
        rect->w = MAIN_THREAD_EM_ASM_INT({
            واپس کھڑکی.inner_چوڑائی;
        });
        rect->h = MAIN_THREAD_EM_ASM_INT({
            واپس کھڑکی.inner_اونچائی;
        });
    }
    واپس true;
}

bool Emscripten_Should_سیٹ_تبادلہ_Interval(صحیح interval)
{
    اگر (!pumpevents_has_تسلسل) {
        pending_تبادلہ_interval = interval;
        واپس false;
    }
    واپس true;
}

صحیح Emscripten_Get_Pending_تبادلہ_Interval(خالی)
{
    واپس pending_تبادلہ_interval;
}

ساکن خالی Emscripten_PumpEvents(SDL_VideoDevice *_this)
{
    اگر (!pumpevents_has_تسلسل) {
        // we assume you've set a mainloop by the time you've called pumpevents, so we delay initial SetInterval changes until then.
        // otherwise you'll get a warning on the javascript console.
        pumpevents_has_تسلسل = true;
        اگر (pending_تبادلہ_interval >= 0) {
            Emscripten_GLES_سیٹ_تبادلہ_Interval(_this, pending_تبادلہ_interval);
            pending_تبادلہ_interval = -1;
        }
    }
}

EMSCRIPTEN_KEEPALIVE خالی requestFullscreenThroughSDL(SDL_کھڑکی *کھڑکی)
{
    SDL_سیٹ_کھڑکی_Fullscreen(کھڑکی, true);
}

ساکن bool Emscripten_سیٹ_کھڑکی_Fill_Document(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool fill)
{
    SDL_کھڑکی_ڈیٹا *wdata = کھڑکی->اندرونی_2;

    اگر (fill && Emscripten_fill_document_کھڑکی && (Emscripten_fill_document_کھڑکی != کھڑکی)) {
        واپس SDL_سیٹ_Error("Only one fill-document window allowed at a time.");
    }

    // fill_document takes up the entire page and resizes as the browser window resizes.
    اگر (fill) {
        Emscripten_fill_document_کھڑکی = کھڑکی;

        ثابت صحیح w = MAIN_THREAD_EM_ASM_INT({ واپس کھڑکی.inner_چوڑائی; });
        ثابت صحیح h = MAIN_THREAD_EM_ASM_INT({ واپس کھڑکی.inner_اونچائی; });
        ثابت دوہرا scaled_w = w * wdata->pixel_تناسب;
        ثابت دوہرا scaled_h = h * wdata->pixel_تناسب;

        wdata->non_fill_document_چوڑائی = کھڑکی->w;
        wdata->non_fill_document_اونچائی = کھڑکی->h;

        MAIN_THREAD_EM_ASM({
            var canvas = document.querySelector(UTF8_مقصد_String($0));
            canvas.SDL3_original_position = canvas.style.position;
            canvas.SDL3_original_چوٹی = canvas.style.چوٹی;
            canvas.SDL3_original_بایاں = canvas.style.بایاں;

            // hide everything on the page that isn't the canvas.
            var div = document.createElement('div');
            div.id = 'SDL3_fill_document_background_elements';

            div.SDL3_canvas = canvas;
            div.SDL3_canvas_والد = canvas.والد_گرہ;
            div.SDL3_canvas_nextsib = canvas.اگلا_Sibling;

            var children = Array.from(document.body.children);
            برائے (var بچہ کا children) {
                div.append_بچہ(بچہ);
            }
            document.body.append_بچہ(div);
            div.style.display = 'none';
            document.body.append_بچہ(canvas);
            canvas.style.position = 'fixed';
            canvas.style.چوٹی = '0';
            canvas.style.بایاں = '0';
        }, wdata->canvas_id);

        emscripten_سیٹ_canvas_element_سائز(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // set_canvas_size unsets this
        اگر (wdata->pixel_تناسب != 1.0f) {
            emscripten_سیٹ_element_css_سائز(wdata->canvas_id, w, h);
        }

        // force the event to trigger, so pixel ratio changes can be handled
        کھڑکی->w = کھڑکی->h = 0;
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    } ورنہ {
        ثابت bool transitioning = (Emscripten_fill_document_کھڑکی == کھڑکی);
        اگر (transitioning) {
            MAIN_THREAD_EM_ASM({
                // if we had previously hidden everything behind a fill_document window, put it back.
                var div = document.getElementById('SDL3_fill_document_background_elements');
                اگر (div) {
                    اگر (div.SDL3_canvas_nextsib) {
                        div.SDL3_canvas_والد.داخل_کرو_Before(div.SDL3_canvas, div.SDL3_canvas_nextsib);
                    } ورنہ {
                        div.SDL3_canvas_والد.append_بچہ(div.SDL3_canvas);
                    }
                    جب (div.پہلا_بچہ_2) {
                        document.body.داخل_کرو_Before(div.پہلا_بچہ_2, div);
                    }
                    div.SDL3_canvas.style.position = div.SDL3_canvas.SDL3_original_position;
                    div.SDL3_canvas.style.چوٹی = div.SDL3_canvas.SDL3_original_چوٹی;
                    div.SDL3_canvas.style.بایاں = div.SDL3_canvas.SDL3_original_بایاں;
                    div.remove();
                }
            });
            Emscripten_fill_document_کھڑکی = تہی;
        }

        کھڑکی->w = wdata->non_fill_document_چوڑائی;
        کھڑکی->h = wdata->non_fill_document_اونچائی;
        ثابت دوہرا scaled_w = SDL_floor(کھڑکی->w * wdata->pixel_تناسب);
        ثابت دوہرا scaled_h = SDL_floor(کھڑکی->h * wdata->pixel_تناسب);
        emscripten_سیٹ_canvas_element_سائز(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // if the size is not being controlled by css, we need to scale down for hidpi
        اگر (!wdata->external_سائز && (wdata->pixel_تناسب != 1.0f)) {
            // scale canvas down
            emscripten_سیٹ_element_css_سائز(wdata->canvas_id, کھڑکی->w, کھڑکی->h);
        }

        اگر (transitioning) {
            کھڑکی->w = کھڑکی->h = 0;
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, wdata->non_fill_document_چوڑائی, wdata->non_fill_document_اونچائی);
        }
    }

    واپس true;
}

ساکن bool Emscripten_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    SDL_کھڑکی_ڈیٹا *wdata;
    دوہرا css_w, css_h;
    ثابت حرف *selector;

    bool fill_document = ((کھڑکی->flags & SDL_کھڑکی_FILL_DOCUMENT) != 0);
    اگر (fill_document && Emscripten_fill_document_کھڑکی) {
        fill_document = false;  // only one allowed at a time.
        کھڑکی->flags &= ~SDL_کھڑکی_FILL_DOCUMENT;   // !!! FIXME: should this fail instead?
    }

    // Allocate window internal data
    wdata = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(SDL_کھڑکی_ڈیٹا));
    اگر (!wdata) {
        واپس false;
    }

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR);
    اگر (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_کھڑکی_CREATE_EMSCRIPTEN_CANVAS_ID_STRING, "#canvas");
    }
    wdata->canvas_id = SDL_strdup(selector);

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
    اگر (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_کھڑکی_CREATE_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, "#window");
    }
    wdata->keyboard_element = SDL_strdup(selector);

    اگر (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY) {
        wdata->pixel_تناسب = emscripten_get_device_pixel_تناسب();
    } ورنہ {
        wdata->pixel_تناسب = 1.0f;
    }

    // set a fake size to check if there is any CSS sizing the canvas
    emscripten_سیٹ_canvas_element_سائز(wdata->canvas_id, 1, 1);
    emscripten_get_element_css_سائز(wdata->canvas_id, &css_w, &css_h);

    wdata->external_سائز = SDL_floor(css_w) != 1 || SDL_floor(css_h) != 1;
    اگر (wdata->external_سائز) {
        fill_document = false;  // can't be resizable if something else is controlling it.
        کھڑکی->w = (صحیح) css_w;
        کھڑکی->h = (صحیح) css_h;
    }

    wdata->کھڑکی = کھڑکی;

    // Setup driver data for this window
    کھڑکی->اندرونی_2 = wdata;

    wdata->non_fill_document_چوڑائی = کھڑکی->w;
    wdata->non_fill_document_اونچائی = کھڑکی->h;
    Emscripten_سیٹ_کھڑکی_Fill_Document(_this, کھڑکی, fill_document);

    // One window, it always has focus
    SDL_سیٹ_Mouse_Focus(کھڑکی);
    SDL_سیٹ_Keyboard_Focus(کھڑکی);

    Emscripten_رجسٹر_Event_Handlers(wdata);

    // Make the emscripten "fullscreen" button go through SDL.
    MAIN_THREAD_EM_ASM({
        Module['requestFullscreen'] = function(تالا_اشارہ_گر, resizeCanvas) {
            _requestFullscreenThroughSDL($0);
        };
    }, کھڑکی);

    // Ensure various things are added to the window's properties
    SDL_سیٹ_String_Property(کھڑکی->props, SDL_PROP_کھڑکی_EMSCRIPTEN_CANVAS_ID_STRING, wdata->canvas_id);
    SDL_سیٹ_String_Property(کھڑکی->props, SDL_PROP_کھڑکی_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, wdata->keyboard_element);

    // Window has been successfully created
    واپس true;
}

ساکن خالی Emscripten_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, bool resizable)
{
    // this function just has to exist or the higher level won't let the window change its SDL_WINDOW_RESIZABLE flag.
}

ساکن خالی Emscripten_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (کھڑکی->اندرونی_2) {
        SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
        اگر (کھڑکی == Emscripten_fill_document_کھڑکی) {
            واپس;  // canvas size is being dictated by the browser window size, refuse request.
        }

        // update pixel ratio
        اگر (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY) {
            ڈیٹا->pixel_تناسب = emscripten_get_device_pixel_تناسب();
        }
        emscripten_سیٹ_canvas_element_سائز(ڈیٹا->canvas_id, SDL_lroundf(کھڑکی->pending.w * ڈیٹا->pixel_تناسب), SDL_lroundf(کھڑکی->pending.h * ڈیٹا->pixel_تناسب));

        // scale canvas down
        اگر (!ڈیٹا->external_سائز && ڈیٹا->pixel_تناسب != 1.0f) {
            emscripten_سیٹ_element_css_سائز(ڈیٹا->canvas_id, کھڑکی->pending.w, کھڑکی->pending.h);
        }

        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی->pending.w, کھڑکی->pending.h);
    }
}

ساکن خالی Emscripten_Get_کھڑکی_سائز_اندر_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *w, صحیح *h)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا;
    اگر (کھڑکی->اندرونی_2) {
        ڈیٹا = کھڑکی->اندرونی_2;
        *w = SDL_lroundf(کھڑکی->w * ڈیٹا->pixel_تناسب);
        *h = SDL_lroundf(کھڑکی->h * ڈیٹا->pixel_تناسب);
    }
}

ساکن خالی Emscripten_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا;

    Emscripten_سیٹ_کھڑکی_Fill_Document(_this, کھڑکی, false);

    اگر (کھڑکی->اندرونی_2) {
        ڈیٹا = کھڑکی->اندرونی_2;

        Emscripten_UnregisterEventHandlers(ڈیٹا);

        // We can't destroy the canvas, so resize it to zero instead
        emscripten_سیٹ_canvas_element_سائز(ڈیٹا->canvas_id, 0, 0);
        اگر (ڈیٹا->pixel_تناسب != 1.0f) {
            emscripten_سیٹ_element_css_سائز(ڈیٹا->canvas_id, 1, 1);
        }
        SDL_free(ڈیٹا->canvas_id);

        SDL_free(ڈیٹا->keyboard_element);

        SDL_free(کھڑکی->اندرونی_2);
        کھڑکی->اندرونی_2 = تہی;
    }

    MAIN_THREAD_EM_ASM({
        // just ignore clicks on the fullscreen button while there's no SDL window.
        Module['requestFullscreen'] = function(تالا_اشارہ_گر, resizeCanvas) {};
    });
}

ساکن SDL_Fullscreen_نتیجہ Emscripten_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا;
    صحیح res = -1;

    اگر (کھڑکی->اندرونی_2) {
        ڈیٹا = کھڑکی->اندرونی_2;

        اگر (ڈیٹا->fullscreen_change_اندر_پیش_رفت) {
            واپس SDL_FULLSCREEN_FAILED;;
        }

        EmscriptenFullscreenChangeEvent fsevent;
        اگر (emscripten_get_fullscreen_حالت(&fsevent) == EMSCRIPTEN_نتیجہ_SUCCESS) {
            اگر ((fullscreen == SDL_FULLSCREEN_OP_ENTER) == fsevent.isFullscreen) {
                واپس SDL_FULLSCREEN_SUCCEEDED;  // already there.
            }
        }

        اگر (fullscreen) {
            EmscriptenFullscreenStrategy strategy;
            bool is_fullscreen_desktop = !کھڑکی->fullscreen_exclusive;

            SDL_zero(strategy);
            strategy.scale_منوال = is_fullscreen_desktop ? EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH : EMSCRIPTEN_FULLSCREEN_SCALE_ASPECT;

            اگر (!is_fullscreen_desktop) {
                strategy.canvas_Resolution_Scale_منوال = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
            } ورنہ اگر (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY) {
                strategy.canvas_Resolution_Scale_منوال = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF;
            } ورنہ {
                strategy.canvas_Resolution_Scale_منوال = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
            }

            strategy.filtering_منوال = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;

            strategy.canvasResizedCallback = Emscripten_HandleCanvasResize;
            strategy.canvas_Resized_Callback_User_ڈیٹا = ڈیٹا;

            ڈیٹا->fullscreen_منوال_flags = (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN);
            ڈیٹا->fullscreen_resize = is_fullscreen_desktop;

            res = emscripten_request_fullscreen_strategy(ڈیٹا->canvas_id, 1, &strategy);
        } ورنہ {
            res = emscripten_exit_fullscreen();
        }
    }

    اگر (res == EMSCRIPTEN_نتیجہ_SUCCESS) {
        ڈیٹا->fullscreen_change_اندر_پیش_رفت = true;   // even on success, this might animate to the new state.
        واپس SDL_FULLSCREEN_SUCCEEDED;
    } ورنہ اگر (res == EMSCRIPTEN_نتیجہ_DEFERRED) {
        ڈیٹا->fullscreen_change_اندر_پیش_رفت = true;
        واپس SDL_FULLSCREEN_PENDING;
    } ورنہ {
        واپس SDL_FULLSCREEN_FAILED;
    }
}

ساکن خالی Emscripten_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    emscripten_سیٹ_کھڑکی_title(کھڑکی->title);
}

ساکن bool Emscripten_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon)
{
    // Create dynamic memory stream for PNG encoding
    SDL_IOStream *دھارا = SDL_IOFromDynamicMem();
    اگر (!دھارا) {
        واپس false;
    }

    // Encode icon to PNG using SDL's native PNG encoder
    اگر (!SDL_SavePNG_IO(icon, دھارا, false)) {
        SDL_CloseIO(دھارا);
        واپس false;
    }

    // Get the PNG data from the stream
    خالی *png_ڈیٹا = SDL_Get_اشارہ_گر_Property(
        SDL_GetIOProperties(دھارا),
        SDL_PROP_IOSTREAM_DYNAMIC_حافظہ_اشارہ_گر,
        تہی
    );
    size_t png_سائز = (size_t)SDL_GetIOSize(دھارا);

    // Pass PNG data to JavaScript
    MAIN_THREAD_EM_ASM({
        // Use `.slice` to make a copy of the data if we are dealing with a SharedArrayBuffer, or `.subarray` to create a
        // view into the existing buffer if its non-shared.
        var png_ڈیٹا_2 = HEAPU8.بفر_2 instanceof Array_بفر ? HEAPU8.subarray($0, $0 + $1) : HEAPU8.قاش($0, $0 + $1);

        var blob = new Blob([png_ڈیٹا_2], {type: 'image/png'});
        var url = URL.createObjectURL(blob);

        // Set as favicon (create link element if it doesn't exist)
        var link = document.querySelector("link[rel~='icon']");
        اگر (!link) {
            link = document.createElement('link');
            link.rel = 'icon';
            link.type = 'image/png';
            document.سر.append_بچہ(link);
        }

        // Revoke old URL if it exists to prevent memory leaks
        اگر (link.href && link.href.startsWith('blob:')) {
            URL.revokeObjectURL(link.href);
        }

        link.href = url;
    }, png_ڈیٹا, png_سائز);

    SDL_CloseIO(دھارا);
    واپس true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_EMSCRIPTEN
