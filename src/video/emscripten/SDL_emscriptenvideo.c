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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_pixels_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"
#ଅନ୍ତର୍ଭାଵ "../../SDL_hints_c.h"

#ଅନ୍ତର୍ଭାଵ "SDL_emscriptenvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_emscriptenopengles.h"
#ଅନ୍ତର୍ଭାଵ "SDL_emscriptenframebuffer.h"
#ଅନ୍ତର୍ଭାଵ "SDL_emscriptenevents.h"
#ଅନ୍ତର୍ଭାଵ "SDL_emscriptenmouse.h"

#define EMSCRIPTENVID_DRIVER_NAME "emscripten"

// Initialization/Query functions
ସ୍ଥିର bool Emscripten_VideoInit(SDL_VideoDevice *_this);
ସ୍ଥିର bool Emscripten_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
ସ୍ଥିର ଶୂନ୍ୟ Emscripten_VideoQuit(SDL_VideoDevice *_this);
ସ୍ଥିର bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

ସ୍ଥିର bool Emscripten_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ସ୍ଥିର ଶୂନ୍ୟ Emscripten_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ସ୍ଥିର ଶୂନ୍ୟ Emscripten_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, bool resizable);
ସ୍ଥିର ଶୂନ୍ୟ Emscripten_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *h);
ସ୍ଥିର ଶୂନ୍ୟ Emscripten_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
ସ୍ଥିର SDL_FullscreenResult Emscripten_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ସ୍ଥିର ଶୂନ୍ୟ Emscripten_PumpEvents(SDL_VideoDevice *_this);
ସ୍ଥିର ଶୂନ୍ୟ Emscripten_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
ସ୍ଥିର bool Emscripten_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
ସ୍ଥିର bool Emscripten_SetWindowFillDocument(SDL_VideoDevice *_this, SDL_Window *window, bool fill);

SDL_Window *Emscripten_fill_document_window = ଖାଲି;

ସ୍ଥିର bool pumpevents_has_run = false;
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା pending_swap_interval = -1;

// Emscripten driver bootstrap functions

ସ୍ଥିର ଶୂନ୍ୟ Emscripten_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ସ୍ଥିର SDL_SystemTheme Emscripten_GetSystemTheme(ଶୂନ୍ୟ)
{
    /* Technically, light theme can mean explicit light theme or no preference.
       https://developer.mozilla.org/en-US/docs/Web/CSS/@media/prefers-color-scheme#syntax */

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା theme_code = MAIN_THREAD_EM_ASM_INT({
        ଯଦି (!window.matchMedia) {
            ଫେରନ୍ତୁ -1;
        }

        ଯଦି (window.matchMedia('(prefers-color-scheme: light)').matches) {
            ଫେରନ୍ତୁ 0;
        }

        ଯଦି (window.matchMedia('(prefers-color-scheme: dark)').matches) {
            ଫେରନ୍ତୁ 1;
        }

        ଫେରନ୍ତୁ -1;
    });

    ବାଛ (theme_code) {
    ସ୍ଥିତି 0:
        ଫେରନ୍ତୁ SDL_SYSTEM_THEME_LIGHT;

    ସ୍ଥିତି 1:
        ଫେରନ୍ତୁ SDL_SYSTEM_THEME_DARK;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Emscripten_ListenSystemTheme(ଶୂନ୍ୟ)
{
    MAIN_THREAD_EM_ASM({
        ଯଦି (window.matchMedia) {
            var SDL3 = Module['SDL3'];

            SDL3.eventHandlerThemeChanged = function(event) {
                _Emscripten_SendSystemThemeChangedEvent();
            };

            SDL3.themeChangedMatchMedia = window.matchMedia('(prefers-color-scheme: dark)');
            SDL3.themeChangedMatchMedia.addEventListener('change', SDL3.eventHandlerThemeChanged);
        }
    });
}

ସ୍ଥିର ଶୂନ୍ୟ Emscripten_UnlistenSystemTheme(ଶୂନ୍ୟ)
{
    MAIN_THREAD_EM_ASM({
        ଯଦି (typeof(Module['SDL3']) !== 'undefined') {
            var SDL3 = Module['SDL3'];

            SDL3.themeChangedMatchMedia.removeEventListener('change', SDL3.eventHandlerThemeChanged);
            SDL3.themeChangedMatchMedia = undefined;
            SDL3.eventHandlerThemeChanged = undefined;
        }
    });
}

EMSCRIPTEN_KEEPALIVE ଶୂନ୍ୟ Emscripten_SendSystemThemeChangedEvent(ଶୂନ୍ୟ)
{
    SDL_SetSystemTheme(Emscripten_GetSystemTheme());
}

ସ୍ଥିର SDL_VideoDevice *Emscripten_CreateDevice(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ଆକାର(SDL_VideoDevice));
    ଯଦି (!device) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    /* Firefox sends blur event which would otherwise prevent full screen
     * when the user clicks to allow full screen.
     * See https://bugzilla.mozilla.org/show_bug.cgi?id=1144964
     */
    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

    // Set the function pointers
    device->VideoInit = Emscripten_VideoInit;
    device->VideoQuit = Emscripten_VideoQuit;
    device->GetDisplayUsableBounds = Emscripten_GetDisplayUsableBounds;
    device->SetDisplayMode = Emscripten_SetDisplayMode;

    device->PumpEvents = Emscripten_PumpEvents;

    device->CreateSDLWindow = Emscripten_CreateWindow;
    device->SetWindowTitle = Emscripten_SetWindowTitle;
    device->SetWindowIcon = Emscripten_SetWindowIcon;
    /*device->SetWindowPosition = Emscripten_SetWindowPosition;*/
    device->SetWindowSize = Emscripten_SetWindowSize;
    device->SetWindowResizable = Emscripten_SetWindowResizable;
    /*device->ShowWindow = Emscripten_ShowWindow;
    device->HideWindow = Emscripten_HideWindow;
    device->RaiseWindow = Emscripten_RaiseWindow;
    device->MaximizeWindow = Emscripten_MaximizeWindow;
    device->MinimizeWindow = Emscripten_MinimizeWindow;
    device->RestoreWindow = Emscripten_RestoreWindow;
    device->SetWindowMouseGrab = Emscripten_SetWindowMouseGrab;*/
    device->GetWindowSizeInPixels = Emscripten_GetWindowSizeInPixels;
    device->DestroyWindow = Emscripten_DestroyWindow;
    device->SetWindowFullscreen = Emscripten_SetWindowFullscreen;
    device->SetWindowFillDocument = Emscripten_SetWindowFillDocument;

    device->CreateWindowFramebuffer = Emscripten_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = Emscripten_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = Emscripten_DestroyWindowFramebuffer;

    device->GL_LoadLibrary = Emscripten_GLES_LoadLibrary;
    device->GL_GetProcAddress = Emscripten_GLES_GetProcAddress;
    device->GL_UnloadLibrary = Emscripten_GLES_UnloadLibrary;
    device->GL_CreateContext = Emscripten_GLES_CreateContext;
    device->GL_MakeCurrent = Emscripten_GLES_MakeCurrent;
    device->GL_SetSwapInterval = Emscripten_GLES_SetSwapInterval;
    device->GL_GetSwapInterval = Emscripten_GLES_GetSwapInterval;
    device->GL_SwapWindow = Emscripten_GLES_SwapWindow;
    device->GL_DestroyContext = Emscripten_GLES_DestroyContext;

    device->ମୁକ୍ତ = Emscripten_DeleteDevice;

    Emscripten_ListenSystemTheme();
    device->system_theme = Emscripten_GetSystemTheme();

    ଫେରନ୍ତୁ device;
}

ସ୍ଥିର bool Emscripten_ShowMessagebox(ଅଚଳ SDL_MessageBoxData *messageboxdata, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *buttonID) {
    ଯଦି (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        ଅକ୍ଷର dialog_background[32];
        ଅକ୍ଷର dialog_color[32];
        ଅକ୍ଷର button_border[32];
        ଅକ୍ଷର button_background[32];
        ଅକ୍ଷର button_hovered[32];

        ଯଦି (messageboxdata->colorScheme) {
            SDL_MessageBoxColor color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND];
            SDL_snprintf(dialog_background, ଆକାର(dialog_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT];
            SDL_snprintf(dialog_color, ଆକାର(dialog_color), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER];
            SDL_snprintf(button_border, ଆକାର(button_border), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND];
            SDL_snprintf(button_background, ଆକାର(button_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED];
            SDL_snprintf(button_hovered, ଆକାର(button_hovered), "rgb(%u, %u, %u)", color.r, color.g, color.b);
        } ଅନ୍ୟଥା {
            SDL_zero(dialog_background);
            SDL_zero(dialog_color);
            SDL_zero(button_border);
            SDL_zero(button_background);
            SDL_zero(button_hovered);
        }

        // TODO: Handle parent window when multiple windows can be added in Emscripten builds
        ଅକ୍ଷର dialog_id[64];
        SDL_snprintf(dialog_id, ଆକାର(dialog_id), "SDL3_messagebox_%u", SDL_rand_bits());
        EM_ASM({
            var title = UTF8ToString($0);
            var message = UTF8ToString($1);
            var background = UTF8ToString($2);
            var color = UTF8ToString($3);
            var id = UTF8ToString($4);

            // Dialogs are always put in the front of the DOM
            var dialog = document.createElement("dialog");
            // Set class to allow for CSS selectors
            dialog.classList.add("SDL3_messagebox");
            dialog.id = id;
            dialog.style.color = color;
            dialog.style.backgroundColor = background;
            document.body.append(dialog);

            var h1 = document.createElement("h1");
            h1.innerText = title;
            dialog.append(h1);

            var p = document.createElement("p");
            p.innerText = message;
            dialog.append(p);

            dialog.showModal();
        }, messageboxdata->title, messageboxdata->message, dialog_background, dialog_color, dialog_id);

        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
        ପାଇଁ (i = 0; i < messageboxdata->numbuttons; ++i) {
            SDL_MessageBoxButtonData button = messageboxdata->buttons[i];

            ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା created = EM_ASM_INT({
                    var dialog_id = UTF8ToString($0);
                    var text = UTF8ToString($1);
                    var responseId = $2;
                    var clickOnReturn = $3;
                    var clickOnEscape = $4;
                    var border = UTF8ToString($5);
                    var background = UTF8ToString($6);
                    var hovered = UTF8ToString($7);

                    var dialog = document.getElementById(dialog_id);
                    ଯଦି (!dialog) {
                        ଫେରନ୍ତୁ false;
                    }

                    var button = document.createElement("button");
                    button.innerText = text;
                    button.style.borderColor = border;
                    button.style.backgroundColor = background;

                    dialog.addEventListener('keydown', function(e) {
                        ଯଦି (clickOnReturn && e.ଚାବି === "Enter") {
                            e.preventDefault();
                            button.click();
                        } ଅନ୍ୟଥା ଯଦି (clickOnEscape && e.ଚାବି === "Escape") {
                            e.preventDefault();
                            button.click();
                        }
                    });
                    dialog.addEventListener('cancel', function(e){
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
                    ଫେରନ୍ତୁ true;
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

            ଯଦି (!created) {
                ଫେରନ୍ତୁ false;
            }
        }

        ଯେତେବେଳେ (true) {
            // give back control to browser for screen refresh
            emscripten_sleep(0);

            ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dialog_open = EM_ASM_INT({
                var dialog_id = UTF8ToString($0);

                var dialog = document.getElementById(dialog_id);
                ଯଦି (!dialog) {
                    ଫେରନ୍ତୁ false;
                }
                ଫେରନ୍ତୁ dialog.open;
            }, dialog_id);

            ଯଦି (dialog_open) {
                ଜାରି;
            }

            *buttonID = EM_ASM_INT({
                var dialog_id = UTF8ToString($0);
                var dialog = document.getElementById(dialog_id);
                ଯଦି (!dialog) {
                    ଫେରନ୍ତୁ 0;
                }
                try
                {
                    ଫେରନ୍ତୁ parseInt(dialog.return_ମୂଲ୍ୟ);
                }
                catch(e)
                {
                    ଫେରନ୍ତୁ 0;
                }
            }, dialog_id);
            ଭାଙ୍ଗ;
        }

    } ଅନ୍ୟଥା {
        // Cannot add elements to DOM and block without Asyncify. So, fall back to the alert function.
        EM_ASM({
            alert(UTF8ToString($0) + "\n\n" + UTF8ToString($1));
        }, messageboxdata->title, messageboxdata->message);
    }
    ଫେରନ୍ତୁ true;
}

VideoBootStrap Emscripten_bootstrap = {
    EMSCRIPTENVID_DRIVER_NAME, "SDL emscripten video driver",
    Emscripten_CreateDevice,
    Emscripten_ShowMessagebox,
    false
};

bool Emscripten_VideoInit(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;

    // Use a fake 32-bpp desktop mode
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_RGBA32;
    emscripten_get_screen_size(&mode.w, &mode.h);
    mode.pixel_density = emscripten_get_device_pixel_ratio();

    ଯଦି (SDL_AddBasicVideoDisplay(&mode) == 0) {
        ଫେରନ୍ତୁ false;
    }

    Emscripten_InitMouse();

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ଖାଲି);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ଖାଲି);

    Emscripten_RegisterGlobalEventHandlers(_this);

    // We're done!
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool Emscripten_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    // can't do this
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ Emscripten_VideoQuit(SDL_VideoDevice *_this)
{
    Emscripten_UnregisterGlobalEventHandlers(_this);
    Emscripten_QuitMouse();
    Emscripten_UnlistenSystemTheme();
    pumpevents_has_run = false;
    pending_swap_interval = -1;
}

ସ୍ଥିର bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ଯଦି (rect) {
        rect->x = 0;
        rect->y = 0;
        rect->w = MAIN_THREAD_EM_ASM_INT({
            ଫେରନ୍ତୁ window.innerWidth;
        });
        rect->h = MAIN_THREAD_EM_ASM_INT({
            ଫେରନ୍ତୁ window.innerHeight;
        });
    }
    ଫେରନ୍ତୁ true;
}

bool Emscripten_ShouldSetSwapInterval(ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval)
{
    ଯଦି (!pumpevents_has_run) {
        pending_swap_interval = interval;
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ true;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା Emscripten_GetPendingSwapInterval(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ pending_swap_interval;
}

ସ୍ଥିର ଶୂନ୍ୟ Emscripten_PumpEvents(SDL_VideoDevice *_this)
{
    ଯଦି (!pumpevents_has_run) {
        // we assume you've set a mainloop by the time you've called pumpevents, so we delay initial SetInterval changes until then.
        // otherwise you'll get a warning on the javascript console.
        pumpevents_has_run = true;
        ଯଦି (pending_swap_interval >= 0) {
            Emscripten_GLES_SetSwapInterval(_this, pending_swap_interval);
            pending_swap_interval = -1;
        }
    }
}

EMSCRIPTEN_KEEPALIVE ଶୂନ୍ୟ requestFullscreenThroughSDL(SDL_Window *window)
{
    SDL_SetWindowFullscreen(window, true);
}

ସ୍ଥିର bool Emscripten_SetWindowFillDocument(SDL_VideoDevice *_this, SDL_Window *window, bool fill)
{
    SDL_WindowData *wdata = window->internal;

    ଯଦି (fill && Emscripten_fill_document_window && (Emscripten_fill_document_window != window)) {
        ଫେରନ୍ତୁ SDL_SetError("Only one fill-document window allowed at a time.");
    }

    // fill_document takes up the entire page and resizes as the browser window resizes.
    ଯଦି (fill) {
        Emscripten_fill_document_window = window;

        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = MAIN_THREAD_EM_ASM_INT({ ଫେରନ୍ତୁ window.innerWidth; });
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = MAIN_THREAD_EM_ASM_INT({ ଫେରନ୍ତୁ window.innerHeight; });
        ଅଚଳ ଦ୍ୱିଗୁଣ scaled_w = w * wdata->pixel_ratio;
        ଅଚଳ ଦ୍ୱିଗୁଣ scaled_h = h * wdata->pixel_ratio;

        wdata->non_fill_document_width = window->w;
        wdata->non_fill_document_height = window->h;

        MAIN_THREAD_EM_ASM({
            var canvas = document.querySelector(UTF8ToString($0));
            canvas.SDL3_original_position = canvas.style.position;
            canvas.SDL3_original_ଶୀର୍ଷ = canvas.style.ଶୀର୍ଷ;
            canvas.SDL3_original_ବାମ = canvas.style.ବାମ;

            // hide everything on the page that isn't the canvas.
            var div = document.createElement('div');
            div.id = 'SDL3_fill_document_background_elements';

            div.SDL3_canvas = canvas;
            div.SDL3_canvas_parent = canvas.parent_ଗଣ୍ଠି;
            div.SDL3_canvas_nextsib = canvas.nextSibling;

            var children = Array.from(document.body.children);
            ପାଇଁ (var child of children) {
                div.appendChild(child);
            }
            document.body.appendChild(div);
            div.style.display = 'none';
            document.body.appendChild(canvas);
            canvas.style.position = 'fixed';
            canvas.style.ଶୀର୍ଷ = '0';
            canvas.style.ବାମ = '0';
        }, wdata->canvas_id);

        emscripten_set_canvas_element_size(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // set_canvas_size unsets this
        ଯଦି (wdata->pixel_ratio != 1.0f) {
            emscripten_set_element_css_size(wdata->canvas_id, w, h);
        }

        // force the event to trigger, so pixel ratio changes can be handled
        window->w = window->h = 0;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    } ଅନ୍ୟଥା {
        ଅଚଳ bool transitioning = (Emscripten_fill_document_window == window);
        ଯଦି (transitioning) {
            MAIN_THREAD_EM_ASM({
                // if we had previously hidden everything behind a fill_document window, put it back.
                var div = document.getElementById('SDL3_fill_document_background_elements');
                ଯଦି (div) {
                    ଯଦି (div.SDL3_canvas_nextsib) {
                        div.SDL3_canvas_parent.ଭର୍ତ୍ତି_Before(div.SDL3_canvas, div.SDL3_canvas_nextsib);
                    } ଅନ୍ୟଥା {
                        div.SDL3_canvas_parent.appendChild(div.SDL3_canvas);
                    }
                    ଯେତେବେଳେ (div.firstChild) {
                        document.body.ଭର୍ତ୍ତି_Before(div.firstChild, div);
                    }
                    div.SDL3_canvas.style.position = div.SDL3_canvas.SDL3_original_position;
                    div.SDL3_canvas.style.ଶୀର୍ଷ = div.SDL3_canvas.SDL3_original_ଶୀର୍ଷ;
                    div.SDL3_canvas.style.ବାମ = div.SDL3_canvas.SDL3_original_ବାମ;
                    div.remove();
                }
            });
            Emscripten_fill_document_window = ଖାଲି;
        }

        window->w = wdata->non_fill_document_width;
        window->h = wdata->non_fill_document_height;
        ଅଚଳ ଦ୍ୱିଗୁଣ scaled_w = SDL_floor(window->w * wdata->pixel_ratio);
        ଅଚଳ ଦ୍ୱିଗୁଣ scaled_h = SDL_floor(window->h * wdata->pixel_ratio);
        emscripten_set_canvas_element_size(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // if the size is not being controlled by css, we need to scale down for hidpi
        ଯଦି (!wdata->external_size && (wdata->pixel_ratio != 1.0f)) {
            // scale canvas down
            emscripten_set_element_css_size(wdata->canvas_id, window->w, window->h);
        }

        ଯଦି (transitioning) {
            window->w = window->h = 0;
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, wdata->non_fill_document_width, wdata->non_fill_document_height);
        }
    }

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool Emscripten_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_WindowData *wdata;
    ଦ୍ୱିଗୁଣ css_w, css_h;
    ଅଚଳ ଅକ୍ଷର *selector;

    bool fill_document = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    ଯଦି (fill_document && Emscripten_fill_document_window) {
        fill_document = false;  // only one allowed at a time.
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;   // !!! FIXME: should this fail instead?
    }

    // Allocate window internal data
    wdata = (SDL_WindowData *)SDL_calloc(1, ଆକାର(SDL_WindowData));
    ଯଦି (!wdata) {
        ଫେରନ୍ତୁ false;
    }

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR);
    ଯଦି (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_EMSCRIPTEN_CANVAS_ID_STRING, "#canvas");
    }
    wdata->canvas_id = SDL_strdup(selector);

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
    ଯଦି (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, "#window");
    }
    wdata->keyboard_element = SDL_strdup(selector);

    ଯଦି (window->flags & SDL_WINDOW_ଉପର_PIXEL_DENSITY) {
        wdata->pixel_ratio = emscripten_get_device_pixel_ratio();
    } ଅନ୍ୟଥା {
        wdata->pixel_ratio = 1.0f;
    }

    // set a fake size to check if there is any CSS sizing the canvas
    emscripten_set_canvas_element_size(wdata->canvas_id, 1, 1);
    emscripten_get_element_css_size(wdata->canvas_id, &css_w, &css_h);

    wdata->external_size = SDL_floor(css_w) != 1 || SDL_floor(css_h) != 1;
    ଯଦି (wdata->external_size) {
        fill_document = false;  // can't be resizable if something else is controlling it.
        window->w = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) css_w;
        window->h = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) css_h;
    }

    wdata->window = window;

    // Setup driver data for this window
    window->internal = wdata;

    wdata->non_fill_document_width = window->w;
    wdata->non_fill_document_height = window->h;
    Emscripten_SetWindowFillDocument(_this, window, fill_document);

    // One window, it always has focus
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);

    Emscripten_RegisterEventHandlers(wdata);

    // Make the emscripten "fullscreen" button go through SDL.
    MAIN_THREAD_EM_ASM({
        Module['requestFullscreen'] = function(lockPointer, resizeCanvas) {
            _requestFullscreenThroughSDL($0);
        };
    }, window);

    // Ensure various things are added to the window's properties
    SDL_SetStringProperty(window->props, SDL_PROP_WINDOW_EMSCRIPTEN_CANVAS_ID_STRING, wdata->canvas_id);
    SDL_SetStringProperty(window->props, SDL_PROP_WINDOW_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, wdata->keyboard_element);

    // Window has been successfully created
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ Emscripten_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, bool resizable)
{
    // this function just has to exist or the higher level won't let the window change its SDL_WINDOW_RESIZABLE flag.
}

ସ୍ଥିର ଶୂନ୍ୟ Emscripten_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    ଯଦି (window->internal) {
        SDL_WindowData *data = window->internal;
        ଯଦି (window == Emscripten_fill_document_window) {
            ଫେରନ୍ତୁ;  // canvas size is being dictated by the browser window size, refuse request.
        }

        // update pixel ratio
        ଯଦି (window->flags & SDL_WINDOW_ଉପର_PIXEL_DENSITY) {
            data->pixel_ratio = emscripten_get_device_pixel_ratio();
        }
        emscripten_set_canvas_element_size(data->canvas_id, SDL_lroundf(window->pending.w * data->pixel_ratio), SDL_lroundf(window->pending.h * data->pixel_ratio));

        // scale canvas down
        ଯଦି (!data->external_size && data->pixel_ratio != 1.0f) {
            emscripten_set_element_css_size(data->canvas_id, window->pending.w, window->pending.h);
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Emscripten_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *h)
{
    SDL_WindowData *data;
    ଯଦି (window->internal) {
        data = window->internal;
        *w = SDL_lroundf(window->w * data->pixel_ratio);
        *h = SDL_lroundf(window->h * data->pixel_ratio);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Emscripten_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data;

    Emscripten_SetWindowFillDocument(_this, window, false);

    ଯଦି (window->internal) {
        data = window->internal;

        Emscripten_UnregisterEventHandlers(data);

        // We can't destroy the canvas, so resize it to zero instead
        emscripten_set_canvas_element_size(data->canvas_id, 0, 0);
        ଯଦି (data->pixel_ratio != 1.0f) {
            emscripten_set_element_css_size(data->canvas_id, 1, 1);
        }
        SDL_free(data->canvas_id);

        SDL_free(data->keyboard_element);

        SDL_free(window->internal);
        window->internal = ଖାଲି;
    }

    MAIN_THREAD_EM_ASM({
        // just ignore clicks on the fullscreen button while there's no SDL window.
        Module['requestFullscreen'] = function(lockPointer, resizeCanvas) {};
    });
}

ସ୍ଥିର SDL_FullscreenResult Emscripten_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *data;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା res = -1;

    ଯଦି (window->internal) {
        data = window->internal;

        ଯଦି (data->fullscreen_change_in_progress) {
            ଫେରନ୍ତୁ SDL_FULLSCREEN_FAILED;;
        }

        EmscriptenFullscreenChangeEvent fsevent;
        ଯଦି (emscripten_get_fullscreen_status(&fsevent) == EMSCRIPTEN_RESULT_SUCCESS) {
            ଯଦି ((fullscreen == SDL_FULLSCREEN_OP_ENTER) == fsevent.isFullscreen) {
                ଫେରନ୍ତୁ SDL_FULLSCREEN_SUCCEEDED;  // already there.
            }
        }

        ଯଦି (fullscreen) {
            EmscriptenFullscreenStrategy strategy;
            bool is_fullscreen_desktop = !window->fullscreen_exclusive;

            SDL_zero(strategy);
            strategy.scaleMode = is_fullscreen_desktop ? EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH : EMSCRIPTEN_FULLSCREEN_SCALE_ASPECT;

            ଯଦି (!is_fullscreen_desktop) {
                strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
            } ଅନ୍ୟଥା ଯଦି (window->flags & SDL_WINDOW_ଉପର_PIXEL_DENSITY) {
                strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF;
            } ଅନ୍ୟଥା {
                strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
            }

            strategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;

            strategy.canvasResizedCallback = Emscripten_HandleCanvasResize;
            strategy.canvasResizedCallbackUserData = data;

            data->fullscreen_mode_flags = (window->flags & SDL_WINDOW_FULLSCREEN);
            data->fullscreen_resize = is_fullscreen_desktop;

            res = emscripten_request_fullscreen_strategy(data->canvas_id, 1, &strategy);
        } ଅନ୍ୟଥା {
            res = emscripten_exit_fullscreen();
        }
    }

    ଯଦି (res == EMSCRIPTEN_RESULT_SUCCESS) {
        data->fullscreen_change_in_progress = true;   // even on success, this might animate to the new state.
        ଫେରନ୍ତୁ SDL_FULLSCREEN_SUCCEEDED;
    } ଅନ୍ୟଥା ଯଦି (res == EMSCRIPTEN_RESULT_DEFERRED) {
        data->fullscreen_change_in_progress = true;
        ଫେରନ୍ତୁ SDL_FULLSCREEN_PENDING;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_FULLSCREEN_FAILED;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Emscripten_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    emscripten_set_window_title(window->title);
}

ସ୍ଥିର bool Emscripten_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
    // Create dynamic memory stream for PNG encoding
    SDL_IOStream *stream = SDL_IOFromDynamicMem();
    ଯଦି (!stream) {
        ଫେରନ୍ତୁ false;
    }

    // Encode icon to PNG using SDL's native PNG encoder
    ଯଦି (!SDL_SavePNG_IO(icon, stream, false)) {
        SDL_CloseIO(stream);
        ଫେରନ୍ତୁ false;
    }

    // Get the PNG data from the stream
    ଶୂନ୍ୟ *png_data = SDL_GetPointerProperty(
        SDL_GetIOProperties(stream),
        SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER,
        ଖାଲି
    );
    size_t png_size = (size_t)SDL_GetIOSize(stream);

    // Pass PNG data to JavaScript
    MAIN_THREAD_EM_ASM({
        // Use `.slice` to make a copy of the data if we are dealing with a SharedArrayBuffer, or `.subarray` to create a
        // view into the existing buffer if its non-shared.
        var pngData = HEAPU8.buffer instanceof ArrayBuffer ? HEAPU8.subarray($0, $0 + $1) : HEAPU8.slice($0, $0 + $1);

        var blob = new Blob([pngData], {type: 'image/png'});
        var url = URL.createObjectURL(blob);

        // Set as favicon (create link element if it doesn't exist)
        var link = document.querySelector("link[rel~='icon']");
        ଯଦି (!link) {
            link = document.createElement('link');
            link.rel = 'icon';
            link.type = 'image/png';
            document.head.appendChild(link);
        }

        // Revoke old URL if it exists to prevent memory leaks
        ଯଦି (link.href && link.href.startsWith('blob:')) {
            URL.revokeObjectURL(link.href);
        }

        link.href = url;
    }, png_data, png_size);

    SDL_CloseIO(stream);
    ଫେରନ୍ତୁ true;
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
