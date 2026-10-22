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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../SDL_pixels_c.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../../SDL_hints_c.h"

#അന്തര്ഭാവ "SDL_emscriptenvideo.h"
#അന്തര്ഭാവ "SDL_emscriptenopengles.h"
#അന്തര്ഭാവ "SDL_emscriptenframebuffer.h"
#അന്തര്ഭാവ "SDL_emscriptenevents.h"
#അന്തര്ഭാവ "SDL_emscriptenmouse.h"

#define EMSCRIPTENVID_DRIVER_NAME "emscripten"

// Initialization/Query functions
സ്ഥിതം bool Emscripten_VideoInit(SDL_VideoDevice *_this);
സ്ഥിതം bool Emscripten_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
സ്ഥിതം ശൂന്യം Emscripten_VideoQuit(SDL_VideoDevice *_this);
സ്ഥിതം bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

സ്ഥിതം bool Emscripten_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
സ്ഥിതം ശൂന്യം Emscripten_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
സ്ഥിതം ശൂന്യം Emscripten_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, bool resizable);
സ്ഥിതം ശൂന്യം Emscripten_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ *w, പൂർണ്ണസംഖ്യ *h);
സ്ഥിതം ശൂന്യം Emscripten_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
സ്ഥിതം SDL_FullscreenResult Emscripten_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
സ്ഥിതം ശൂന്യം Emscripten_PumpEvents(SDL_VideoDevice *_this);
സ്ഥിതം ശൂന്യം Emscripten_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
സ്ഥിതം bool Emscripten_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
സ്ഥിതം bool Emscripten_SetWindowFillDocument(SDL_VideoDevice *_this, SDL_Window *window, bool fill);

SDL_Window *Emscripten_fill_document_window = ശൂന്യ;

സ്ഥിതം bool pumpevents_has_run = false;
സ്ഥിതം പൂർണ്ണസംഖ്യ pending_swap_interval = -1;

// Emscripten driver bootstrap functions

സ്ഥിതം ശൂന്യം Emscripten_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

സ്ഥിതം SDL_SystemTheme Emscripten_GetSystemTheme(ശൂന്യം)
{
    /* Technically, light theme can mean explicit light theme or no preference.
       https://developer.mozilla.org/en-US/docs/Web/CSS/@media/prefers-color-scheme#syntax */

    പൂർണ്ണസംഖ്യ theme_code = MAIN_THREAD_EM_ASM_INT({
        എങ്കിൽ (!window.matchMedia) {
            തിരികെ -1;
        }

        എങ്കിൽ (window.matchMedia('(prefers-color-scheme: light)').matches) {
            തിരികെ 0;
        }

        എങ്കിൽ (window.matchMedia('(prefers-color-scheme: dark)').matches) {
            തിരികെ 1;
        }

        തിരികെ -1;
    });

    തിരഞ്ഞെടുപ്പ് (theme_code) {
    അവസ്ഥ 0:
        തിരികെ SDL_SYSTEM_THEME_LIGHT;

    അവസ്ഥ 1:
        തിരികെ SDL_SYSTEM_THEME_DARK;

    സ്ഥിരസ്ഥിതി:
        തിരികെ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

സ്ഥിതം ശൂന്യം Emscripten_ListenSystemTheme(ശൂന്യം)
{
    MAIN_THREAD_EM_ASM({
        എങ്കിൽ (window.matchMedia) {
            var SDL3 = Module['SDL3'];

            SDL3.eventHandlerThemeChanged = function(event) {
                _Emscripten_SendSystemThemeChangedEvent();
            };

            SDL3.themeChangedMatchMedia = window.matchMedia('(prefers-color-scheme: dark)');
            SDL3.themeChangedMatchMedia.addEventListener('change', SDL3.eventHandlerThemeChanged);
        }
    });
}

സ്ഥിതം ശൂന്യം Emscripten_UnlistenSystemTheme(ശൂന്യം)
{
    MAIN_THREAD_EM_ASM({
        എങ്കിൽ (typeof(Module['SDL3']) !== 'undefined') {
            var SDL3 = Module['SDL3'];

            SDL3.themeChangedMatchMedia.removeEventListener('change', SDL3.eventHandlerThemeChanged);
            SDL3.themeChangedMatchMedia = undefined;
            SDL3.eventHandlerThemeChanged = undefined;
        }
    });
}

EMSCRIPTEN_KEEPALIVE ശൂന്യം Emscripten_SendSystemThemeChangedEvent(ശൂന്യം)
{
    SDL_SetSystemTheme(Emscripten_GetSystemTheme());
}

സ്ഥിതം SDL_VideoDevice *Emscripten_CreateDevice(ശൂന്യം)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, വലുപ്പം(SDL_VideoDevice));
    എങ്കിൽ (!device) {
        തിരികെ ശൂന്യ;
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

    device->സ്വതന്ത്രം = Emscripten_DeleteDevice;

    Emscripten_ListenSystemTheme();
    device->system_theme = Emscripten_GetSystemTheme();

    തിരികെ device;
}

സ്ഥിതം bool Emscripten_ShowMessagebox(സ്ഥിരം SDL_MessageBoxData *messageboxdata, പൂർണ്ണസംഖ്യ *buttonID) {
    എങ്കിൽ (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        അക്ഷരം dialog_background[32];
        അക്ഷരം dialog_color[32];
        അക്ഷരം button_border[32];
        അക്ഷരം button_background[32];
        അക്ഷരം button_hovered[32];

        എങ്കിൽ (messageboxdata->colorScheme) {
            SDL_MessageBoxColor color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND];
            SDL_snprintf(dialog_background, വലുപ്പം(dialog_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT];
            SDL_snprintf(dialog_color, വലുപ്പം(dialog_color), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER];
            SDL_snprintf(button_border, വലുപ്പം(button_border), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND];
            SDL_snprintf(button_background, വലുപ്പം(button_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED];
            SDL_snprintf(button_hovered, വലുപ്പം(button_hovered), "rgb(%u, %u, %u)", color.r, color.g, color.b);
        } അല്ലെങ്കിൽ {
            SDL_zero(dialog_background);
            SDL_zero(dialog_color);
            SDL_zero(button_border);
            SDL_zero(button_background);
            SDL_zero(button_hovered);
        }

        // TODO: Handle parent window when multiple windows can be added in Emscripten builds
        അക്ഷരം dialog_id[64];
        SDL_snprintf(dialog_id, വലുപ്പം(dialog_id), "SDL3_messagebox_%u", SDL_rand_bits());
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

        പൂർണ്ണസംഖ്യ i;
        വേണ്ടി (i = 0; i < messageboxdata->numbuttons; ++i) {
            SDL_MessageBoxButtonData button = messageboxdata->buttons[i];

            സ്ഥിരം പൂർണ്ണസംഖ്യ created = EM_ASM_INT({
                    var dialog_id = UTF8ToString($0);
                    var text = UTF8ToString($1);
                    var responseId = $2;
                    var clickOnReturn = $3;
                    var clickOnEscape = $4;
                    var border = UTF8ToString($5);
                    var background = UTF8ToString($6);
                    var hovered = UTF8ToString($7);

                    var dialog = document.getElementById(dialog_id);
                    എങ്കിൽ (!dialog) {
                        തിരികെ false;
                    }

                    var button = document.createElement("button");
                    button.innerText = text;
                    button.style.borderColor = border;
                    button.style.backgroundColor = background;

                    dialog.addEventListener('keydown', function(e) {
                        എങ്കിൽ (clickOnReturn && e.താക്കോൽ === "Enter") {
                            e.preventDefault();
                            button.click();
                        } അല്ലെങ്കിൽ എങ്കിൽ (clickOnEscape && e.താക്കോൽ === "Escape") {
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
                    തിരികെ true;
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

            എങ്കിൽ (!created) {
                തിരികെ false;
            }
        }

        ആകുമ്പോൾ (true) {
            // give back control to browser for screen refresh
            emscripten_sleep(0);

            സ്ഥിരം പൂർണ്ണസംഖ്യ dialog_open = EM_ASM_INT({
                var dialog_id = UTF8ToString($0);

                var dialog = document.getElementById(dialog_id);
                എങ്കിൽ (!dialog) {
                    തിരികെ false;
                }
                തിരികെ dialog.open;
            }, dialog_id);

            എങ്കിൽ (dialog_open) {
                തുടരുക;
            }

            *buttonID = EM_ASM_INT({
                var dialog_id = UTF8ToString($0);
                var dialog = document.getElementById(dialog_id);
                എങ്കിൽ (!dialog) {
                    തിരികെ 0;
                }
                try
                {
                    തിരികെ parseInt(dialog.return_മൂല്യം);
                }
                catch(e)
                {
                    തിരികെ 0;
                }
            }, dialog_id);
            നിർത്തുക;
        }

    } അല്ലെങ്കിൽ {
        // Cannot add elements to DOM and block without Asyncify. So, fall back to the alert function.
        EM_ASM({
            alert(UTF8ToString($0) + "\n\n" + UTF8ToString($1));
        }, messageboxdata->title, messageboxdata->message);
    }
    തിരികെ true;
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

    എങ്കിൽ (SDL_AddBasicVideoDisplay(&mode) == 0) {
        തിരികെ false;
    }

    Emscripten_InitMouse();

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ശൂന്യ);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ശൂന്യ);

    Emscripten_RegisterGlobalEventHandlers(_this);

    // We're done!
    തിരികെ true;
}

സ്ഥിതം bool Emscripten_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    // can't do this
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം Emscripten_VideoQuit(SDL_VideoDevice *_this)
{
    Emscripten_UnregisterGlobalEventHandlers(_this);
    Emscripten_QuitMouse();
    Emscripten_UnlistenSystemTheme();
    pumpevents_has_run = false;
    pending_swap_interval = -1;
}

സ്ഥിതം bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    എങ്കിൽ (rect) {
        rect->x = 0;
        rect->y = 0;
        rect->w = MAIN_THREAD_EM_ASM_INT({
            തിരികെ window.innerWidth;
        });
        rect->h = MAIN_THREAD_EM_ASM_INT({
            തിരികെ window.innerHeight;
        });
    }
    തിരികെ true;
}

bool Emscripten_ShouldSetSwapInterval(പൂർണ്ണസംഖ്യ interval)
{
    എങ്കിൽ (!pumpevents_has_run) {
        pending_swap_interval = interval;
        തിരികെ false;
    }
    തിരികെ true;
}

പൂർണ്ണസംഖ്യ Emscripten_GetPendingSwapInterval(ശൂന്യം)
{
    തിരികെ pending_swap_interval;
}

സ്ഥിതം ശൂന്യം Emscripten_PumpEvents(SDL_VideoDevice *_this)
{
    എങ്കിൽ (!pumpevents_has_run) {
        // we assume you've set a mainloop by the time you've called pumpevents, so we delay initial SetInterval changes until then.
        // otherwise you'll get a warning on the javascript console.
        pumpevents_has_run = true;
        എങ്കിൽ (pending_swap_interval >= 0) {
            Emscripten_GLES_SetSwapInterval(_this, pending_swap_interval);
            pending_swap_interval = -1;
        }
    }
}

EMSCRIPTEN_KEEPALIVE ശൂന്യം requestFullscreenThroughSDL(SDL_Window *window)
{
    SDL_SetWindowFullscreen(window, true);
}

സ്ഥിതം bool Emscripten_SetWindowFillDocument(SDL_VideoDevice *_this, SDL_Window *window, bool fill)
{
    SDL_WindowData *wdata = window->internal;

    എങ്കിൽ (fill && Emscripten_fill_document_window && (Emscripten_fill_document_window != window)) {
        തിരികെ SDL_SetError("Only one fill-document window allowed at a time.");
    }

    // fill_document takes up the entire page and resizes as the browser window resizes.
    എങ്കിൽ (fill) {
        Emscripten_fill_document_window = window;

        സ്ഥിരം പൂർണ്ണസംഖ്യ w = MAIN_THREAD_EM_ASM_INT({ തിരികെ window.innerWidth; });
        സ്ഥിരം പൂർണ്ണസംഖ്യ h = MAIN_THREAD_EM_ASM_INT({ തിരികെ window.innerHeight; });
        സ്ഥിരം ഇരട്ട scaled_w = w * wdata->pixel_ratio;
        സ്ഥിരം ഇരട്ട scaled_h = h * wdata->pixel_ratio;

        wdata->non_fill_document_width = window->w;
        wdata->non_fill_document_height = window->h;

        MAIN_THREAD_EM_ASM({
            var canvas = document.querySelector(UTF8ToString($0));
            canvas.SDL3_original_position = canvas.style.position;
            canvas.SDL3_original_മുകൾ = canvas.style.മുകൾ;
            canvas.SDL3_original_ഇടത് = canvas.style.ഇടത്;

            // hide everything on the page that isn't the canvas.
            var div = document.createElement('div');
            div.id = 'SDL3_fill_document_background_elements';

            div.SDL3_canvas = canvas;
            div.SDL3_canvas_parent = canvas.parent_കണ്ണി;
            div.SDL3_canvas_nextsib = canvas.nextSibling;

            var children = Array.from(document.body.children);
            വേണ്ടി (var child of children) {
                div.appendChild(child);
            }
            document.body.appendChild(div);
            div.style.display = 'none';
            document.body.appendChild(canvas);
            canvas.style.position = 'fixed';
            canvas.style.മുകൾ = '0';
            canvas.style.ഇടത് = '0';
        }, wdata->canvas_id);

        emscripten_set_canvas_element_size(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // set_canvas_size unsets this
        എങ്കിൽ (wdata->pixel_ratio != 1.0f) {
            emscripten_set_element_css_size(wdata->canvas_id, w, h);
        }

        // force the event to trigger, so pixel ratio changes can be handled
        window->w = window->h = 0;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    } അല്ലെങ്കിൽ {
        സ്ഥിരം bool transitioning = (Emscripten_fill_document_window == window);
        എങ്കിൽ (transitioning) {
            MAIN_THREAD_EM_ASM({
                // if we had previously hidden everything behind a fill_document window, put it back.
                var div = document.getElementById('SDL3_fill_document_background_elements');
                എങ്കിൽ (div) {
                    എങ്കിൽ (div.SDL3_canvas_nextsib) {
                        div.SDL3_canvas_parent.തിരുകുക_Before(div.SDL3_canvas, div.SDL3_canvas_nextsib);
                    } അല്ലെങ്കിൽ {
                        div.SDL3_canvas_parent.appendChild(div.SDL3_canvas);
                    }
                    ആകുമ്പോൾ (div.firstChild) {
                        document.body.തിരുകുക_Before(div.firstChild, div);
                    }
                    div.SDL3_canvas.style.position = div.SDL3_canvas.SDL3_original_position;
                    div.SDL3_canvas.style.മുകൾ = div.SDL3_canvas.SDL3_original_മുകൾ;
                    div.SDL3_canvas.style.ഇടത് = div.SDL3_canvas.SDL3_original_ഇടത്;
                    div.remove();
                }
            });
            Emscripten_fill_document_window = ശൂന്യ;
        }

        window->w = wdata->non_fill_document_width;
        window->h = wdata->non_fill_document_height;
        സ്ഥിരം ഇരട്ട scaled_w = SDL_floor(window->w * wdata->pixel_ratio);
        സ്ഥിരം ഇരട്ട scaled_h = SDL_floor(window->h * wdata->pixel_ratio);
        emscripten_set_canvas_element_size(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // if the size is not being controlled by css, we need to scale down for hidpi
        എങ്കിൽ (!wdata->external_size && (wdata->pixel_ratio != 1.0f)) {
            // scale canvas down
            emscripten_set_element_css_size(wdata->canvas_id, window->w, window->h);
        }

        എങ്കിൽ (transitioning) {
            window->w = window->h = 0;
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, wdata->non_fill_document_width, wdata->non_fill_document_height);
        }
    }

    തിരികെ true;
}

സ്ഥിതം bool Emscripten_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_WindowData *wdata;
    ഇരട്ട css_w, css_h;
    സ്ഥിരം അക്ഷരം *selector;

    bool fill_document = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    എങ്കിൽ (fill_document && Emscripten_fill_document_window) {
        fill_document = false;  // only one allowed at a time.
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;   // !!! FIXME: should this fail instead?
    }

    // Allocate window internal data
    wdata = (SDL_WindowData *)SDL_calloc(1, വലുപ്പം(SDL_WindowData));
    എങ്കിൽ (!wdata) {
        തിരികെ false;
    }

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR);
    എങ്കിൽ (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_EMSCRIPTEN_CANVAS_ID_STRING, "#canvas");
    }
    wdata->canvas_id = SDL_strdup(selector);

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
    എങ്കിൽ (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, "#window");
    }
    wdata->keyboard_element = SDL_strdup(selector);

    എങ്കിൽ (window->flags & SDL_WINDOW_മുകളിലെ_PIXEL_DENSITY) {
        wdata->pixel_ratio = emscripten_get_device_pixel_ratio();
    } അല്ലെങ്കിൽ {
        wdata->pixel_ratio = 1.0f;
    }

    // set a fake size to check if there is any CSS sizing the canvas
    emscripten_set_canvas_element_size(wdata->canvas_id, 1, 1);
    emscripten_get_element_css_size(wdata->canvas_id, &css_w, &css_h);

    wdata->external_size = SDL_floor(css_w) != 1 || SDL_floor(css_h) != 1;
    എങ്കിൽ (wdata->external_size) {
        fill_document = false;  // can't be resizable if something else is controlling it.
        window->w = (പൂർണ്ണസംഖ്യ) css_w;
        window->h = (പൂർണ്ണസംഖ്യ) css_h;
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
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം Emscripten_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, bool resizable)
{
    // this function just has to exist or the higher level won't let the window change its SDL_WINDOW_RESIZABLE flag.
}

സ്ഥിതം ശൂന്യം Emscripten_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    എങ്കിൽ (window->internal) {
        SDL_WindowData *data = window->internal;
        എങ്കിൽ (window == Emscripten_fill_document_window) {
            തിരികെ;  // canvas size is being dictated by the browser window size, refuse request.
        }

        // update pixel ratio
        എങ്കിൽ (window->flags & SDL_WINDOW_മുകളിലെ_PIXEL_DENSITY) {
            data->pixel_ratio = emscripten_get_device_pixel_ratio();
        }
        emscripten_set_canvas_element_size(data->canvas_id, SDL_lroundf(window->pending.w * data->pixel_ratio), SDL_lroundf(window->pending.h * data->pixel_ratio));

        // scale canvas down
        എങ്കിൽ (!data->external_size && data->pixel_ratio != 1.0f) {
            emscripten_set_element_css_size(data->canvas_id, window->pending.w, window->pending.h);
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
    }
}

സ്ഥിതം ശൂന്യം Emscripten_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ *w, പൂർണ്ണസംഖ്യ *h)
{
    SDL_WindowData *data;
    എങ്കിൽ (window->internal) {
        data = window->internal;
        *w = SDL_lroundf(window->w * data->pixel_ratio);
        *h = SDL_lroundf(window->h * data->pixel_ratio);
    }
}

സ്ഥിതം ശൂന്യം Emscripten_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data;

    Emscripten_SetWindowFillDocument(_this, window, false);

    എങ്കിൽ (window->internal) {
        data = window->internal;

        Emscripten_UnregisterEventHandlers(data);

        // We can't destroy the canvas, so resize it to zero instead
        emscripten_set_canvas_element_size(data->canvas_id, 0, 0);
        എങ്കിൽ (data->pixel_ratio != 1.0f) {
            emscripten_set_element_css_size(data->canvas_id, 1, 1);
        }
        SDL_free(data->canvas_id);

        SDL_free(data->keyboard_element);

        SDL_free(window->internal);
        window->internal = ശൂന്യ;
    }

    MAIN_THREAD_EM_ASM({
        // just ignore clicks on the fullscreen button while there's no SDL window.
        Module['requestFullscreen'] = function(lockPointer, resizeCanvas) {};
    });
}

സ്ഥിതം SDL_FullscreenResult Emscripten_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *data;
    പൂർണ്ണസംഖ്യ res = -1;

    എങ്കിൽ (window->internal) {
        data = window->internal;

        എങ്കിൽ (data->fullscreen_change_in_progress) {
            തിരികെ SDL_FULLSCREEN_FAILED;;
        }

        EmscriptenFullscreenChangeEvent fsevent;
        എങ്കിൽ (emscripten_get_fullscreen_status(&fsevent) == EMSCRIPTEN_RESULT_SUCCESS) {
            എങ്കിൽ ((fullscreen == SDL_FULLSCREEN_OP_ENTER) == fsevent.isFullscreen) {
                തിരികെ SDL_FULLSCREEN_SUCCEEDED;  // already there.
            }
        }

        എങ്കിൽ (fullscreen) {
            EmscriptenFullscreenStrategy strategy;
            bool is_fullscreen_desktop = !window->fullscreen_exclusive;

            SDL_zero(strategy);
            strategy.scaleMode = is_fullscreen_desktop ? EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH : EMSCRIPTEN_FULLSCREEN_SCALE_ASPECT;

            എങ്കിൽ (!is_fullscreen_desktop) {
                strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
            } അല്ലെങ്കിൽ എങ്കിൽ (window->flags & SDL_WINDOW_മുകളിലെ_PIXEL_DENSITY) {
                strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF;
            } അല്ലെങ്കിൽ {
                strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
            }

            strategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;

            strategy.canvasResizedCallback = Emscripten_HandleCanvasResize;
            strategy.canvasResizedCallbackUserData = data;

            data->fullscreen_mode_flags = (window->flags & SDL_WINDOW_FULLSCREEN);
            data->fullscreen_resize = is_fullscreen_desktop;

            res = emscripten_request_fullscreen_strategy(data->canvas_id, 1, &strategy);
        } അല്ലെങ്കിൽ {
            res = emscripten_exit_fullscreen();
        }
    }

    എങ്കിൽ (res == EMSCRIPTEN_RESULT_SUCCESS) {
        data->fullscreen_change_in_progress = true;   // even on success, this might animate to the new state.
        തിരികെ SDL_FULLSCREEN_SUCCEEDED;
    } അല്ലെങ്കിൽ എങ്കിൽ (res == EMSCRIPTEN_RESULT_DEFERRED) {
        data->fullscreen_change_in_progress = true;
        തിരികെ SDL_FULLSCREEN_PENDING;
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_FULLSCREEN_FAILED;
    }
}

സ്ഥിതം ശൂന്യം Emscripten_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    emscripten_set_window_title(window->title);
}

സ്ഥിതം bool Emscripten_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
    // Create dynamic memory stream for PNG encoding
    SDL_IOStream *stream = SDL_IOFromDynamicMem();
    എങ്കിൽ (!stream) {
        തിരികെ false;
    }

    // Encode icon to PNG using SDL's native PNG encoder
    എങ്കിൽ (!SDL_SavePNG_IO(icon, stream, false)) {
        SDL_CloseIO(stream);
        തിരികെ false;
    }

    // Get the PNG data from the stream
    ശൂന്യം *png_data = SDL_GetPointerProperty(
        SDL_GetIOProperties(stream),
        SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER,
        ശൂന്യ
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
        എങ്കിൽ (!link) {
            link = document.createElement('link');
            link.rel = 'icon';
            link.type = 'image/png';
            document.head.appendChild(link);
        }

        // Revoke old URL if it exists to prevent memory leaks
        എങ്കിൽ (link.href && link.href.startsWith('blob:')) {
            URL.revokeObjectURL(link.href);
        }

        link.href = url;
    }, png_data, png_size);

    SDL_CloseIO(stream);
    തിരികെ true;
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
