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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_EMSCRIPTEN

#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_pixels_c.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../../SDL_hints_c.h"

#समावेश "SDL_emscriptenvideo.h"
#समावेश "SDL_emscriptenopengles.h"
#समावेश "SDL_emscriptenframebuffer.h"
#समावेश "SDL_emscriptenevents.h"
#समावेश "SDL_emscriptenmouse.h"

#घोषणा EMSCRIPTENVID_DRIVER_NAME "emscripten"

// Initialization/Query functions
अटल bool Emscripten_VideoInit(SDL_VideoDevice *_this);
अटल bool Emscripten_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
अटल व्योम Emscripten_VideoQuit(SDL_VideoDevice *_this);
अटल bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

अटल bool Emscripten_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
अटल व्योम Emscripten_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window);
अटल व्योम Emscripten_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, bool resizable);
अटल व्योम Emscripten_Get_Window_आकार_In_Pixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *w, पूर्णांक *h);
अटल व्योम Emscripten_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
अटल SDL_Fullscreen_परिणाम Emscripten_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
अटल व्योम Emscripten_PumpEvents(SDL_VideoDevice *_this);
अटल व्योम Emscripten_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
अटल bool Emscripten_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
अटल bool Emscripten_SetWindowFillDocument(SDL_VideoDevice *_this, SDL_Window *window, bool fill);

SDL_Window *Emscripten_fill_document_window = शून्य;

अटल bool pumpevents_has_run = false;
अटल पूर्णांक pending_swap_interval = -1;

// Emscripten driver bootstrap functions

अटल व्योम Emscripten_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

अटल SDL_SystemTheme Emscripten_GetSystemTheme(व्योम)
{
    /* Technically, light theme can mean explicit light theme or no preference.
       https://developer.mozilla.org/en-US/docs/Web/CSS/@media/prefers-color-scheme#syntax */

    पूर्णांक theme_code = MAIN_THREAD_EM_ASM_INT({
        अगर (!window.matchMedia) {
            वापस -1;
        }

        अगर (window.matchMedia('(prefers-color-scheme: light)').matches) {
            वापस 0;
        }

        अगर (window.matchMedia('(prefers-color-scheme: dark)').matches) {
            वापस 1;
        }

        वापस -1;
    });

    चयन (theme_code) {
    हाल 0:
        वापस SDL_SYSTEM_THEME_LIGHT;

    हाल 1:
        वापस SDL_SYSTEM_THEME_DARK;

    शेष:
        वापस SDL_SYSTEM_THEME_UNKNOWN;
    }
}

अटल व्योम Emscripten_ListenSystemTheme(व्योम)
{
    MAIN_THREAD_EM_ASM({
        अगर (window.matchMedia) {
            var SDL3 = Module['SDL3'];

            SDL3.eventHandlerThemeChanged = function(event) {
                _Emscripten_SendSystemThemeChangedEvent();
            };

            SDL3.themeChangedMatchMedia = window.matchMedia('(prefers-color-scheme: dark)');
            SDL3.themeChangedMatchMedia.addEventListener('change', SDL3.eventHandlerThemeChanged);
        }
    });
}

अटल व्योम Emscripten_UnlistenSystemTheme(व्योम)
{
    MAIN_THREAD_EM_ASM({
        अगर (typeof(Module['SDL3']) !== 'undefined') {
            var SDL3 = Module['SDL3'];

            SDL3.themeChangedMatchMedia.removeEventListener('change', SDL3.eventHandlerThemeChanged);
            SDL3.themeChangedMatchMedia = undefined;
            SDL3.eventHandlerThemeChanged = undefined;
        }
    });
}

EMSCRIPTEN_KEEPALIVE व्योम Emscripten_SendSystemThemeChangedEvent(व्योम)
{
    SDL_SetSystemTheme(Emscripten_GetSystemTheme());
}

अटल SDL_VideoDevice *Emscripten_CreateDevice(व्योम)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (!device) {
        वापस शून्य;
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
    device->Set_Window_आकार = Emscripten_Set_Window_आकार;
    device->SetWindowResizable = Emscripten_SetWindowResizable;
    /*device->ShowWindow = Emscripten_ShowWindow;
    device->HideWindow = Emscripten_HideWindow;
    device->RaiseWindow = Emscripten_RaiseWindow;
    device->MaximizeWindow = Emscripten_MaximizeWindow;
    device->MinimizeWindow = Emscripten_MinimizeWindow;
    device->RestoreWindow = Emscripten_RestoreWindow;
    device->SetWindowMouseGrab = Emscripten_SetWindowMouseGrab;*/
    device->Get_Window_आकार_In_Pixels = Emscripten_Get_Window_आकार_In_Pixels;
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

    device->मुक्त = Emscripten_DeleteDevice;

    Emscripten_ListenSystemTheme();
    device->system_theme = Emscripten_GetSystemTheme();

    वापस device;
}

अटल bool Emscripten_ShowMessagebox(स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonID) {
    अगर (emscripten_has_asyncify() && SDL_GetHintBoolean(SDL_HINT_EMSCRIPTEN_ASYNCIFY, true)) {
        अक्षर dialog_background[32];
        अक्षर dialog_color[32];
        अक्षर button_border[32];
        अक्षर button_background[32];
        अक्षर button_hovered[32];

        अगर (messageboxdata->colorScheme) {
            SDL_MessageBoxColor color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND];
            SDL_snprintf(dialog_background, माप(dialog_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT];
            SDL_snprintf(dialog_color, माप(dialog_color), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER];
            SDL_snprintf(button_border, माप(button_border), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND];
            SDL_snprintf(button_background, माप(button_background), "rgb(%u, %u, %u)", color.r, color.g, color.b);

            color = messageboxdata->colorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED];
            SDL_snprintf(button_hovered, माप(button_hovered), "rgb(%u, %u, %u)", color.r, color.g, color.b);
        } अन्यथा {
            SDL_zero(dialog_background);
            SDL_zero(dialog_color);
            SDL_zero(button_border);
            SDL_zero(button_background);
            SDL_zero(button_hovered);
        }

        // TODO: Handle parent window when multiple windows can be added in Emscripten builds
        अक्षर dialog_id[64];
        SDL_snprintf(dialog_id, माप(dialog_id), "SDL3_messagebox_%u", SDL_rand_bits());
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

        पूर्णांक i;
        क्रम (i = 0; i < messageboxdata->numbuttons; ++i) {
            SDL_Message_Box_Button_तथ्य button = messageboxdata->buttons[i];

            स्थिर पूर्णांक created = EM_ASM_INT({
                    var dialog_id = UTF8ToString($0);
                    var text = UTF8ToString($1);
                    var responseId = $2;
                    var clickOnReturn = $3;
                    var clickOnEscape = $4;
                    var border = UTF8ToString($5);
                    var background = UTF8ToString($6);
                    var hovered = UTF8ToString($7);

                    var dialog = document.getElementById(dialog_id);
                    अगर (!dialog) {
                        वापस false;
                    }

                    var button = document.createElement("button");
                    button.innerText = text;
                    button.style.borderColor = border;
                    button.style.backgroundColor = background;

                    dialog.addEventListener('keydown', function(e) {
                        अगर (clickOnReturn && e.कुंजी === "Enter") {
                            e.preventDefault();
                            button.click();
                        } अन्यथा अगर (clickOnEscape && e.कुंजी === "Escape") {
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
                        dialog.बंद(responseId);
                    };

                    dialog.append(button);
                    वापस true;
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

            अगर (!created) {
                वापस false;
            }
        }

        जबतक (true) {
            // give back control to browser for screen refresh
            emscripten_sleep(0);

            स्थिर पूर्णांक dialog_open = EM_ASM_INT({
                var dialog_id = UTF8ToString($0);

                var dialog = document.getElementById(dialog_id);
                अगर (!dialog) {
                    वापस false;
                }
                वापस dialog.खोलो;
            }, dialog_id);

            अगर (dialog_open) {
                जारी;
            }

            *buttonID = EM_ASM_INT({
                var dialog_id = UTF8ToString($0);
                var dialog = document.getElementById(dialog_id);
                अगर (!dialog) {
                    वापस 0;
                }
                try
                {
                    वापस parseInt(dialog.return_मूल्य);
                }
                catch(e)
                {
                    वापस 0;
                }
            }, dialog_id);
            अवरोध;
        }

    } अन्यथा {
        // Cannot add elements to DOM and block without Asyncify. So, fall back to the alert function.
        EM_ASM({
            alert(UTF8ToString($0) + "\n\n" + UTF8ToString($1));
        }, messageboxdata->title, messageboxdata->message);
    }
    वापस true;
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
    emscripten_get_screen_आकार(&mode.w, &mode.h);
    mode.pixel_density = emscripten_get_device_pixel_ratio();

    अगर (SDL_AddBasicVideoDisplay(&mode) == 0) {
        वापस false;
    }

    Emscripten_InitMouse();

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, शून्य);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, शून्य);

    Emscripten_RegisterGlobalEventHandlers(_this);

    // We're done!
    वापस true;
}

अटल bool Emscripten_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    // can't do this
    वापस true;
}

अटल व्योम Emscripten_VideoQuit(SDL_VideoDevice *_this)
{
    Emscripten_UnregisterGlobalEventHandlers(_this);
    Emscripten_QuitMouse();
    Emscripten_UnlistenSystemTheme();
    pumpevents_has_run = false;
    pending_swap_interval = -1;
}

अटल bool Emscripten_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    अगर (rect) {
        rect->x = 0;
        rect->y = 0;
        rect->w = MAIN_THREAD_EM_ASM_INT({
            वापस window.innerWidth;
        });
        rect->h = MAIN_THREAD_EM_ASM_INT({
            वापस window.innerHeight;
        });
    }
    वापस true;
}

bool Emscripten_ShouldSetSwapInterval(पूर्णांक interval)
{
    अगर (!pumpevents_has_run) {
        pending_swap_interval = interval;
        वापस false;
    }
    वापस true;
}

पूर्णांक Emscripten_GetPendingSwapInterval(व्योम)
{
    वापस pending_swap_interval;
}

अटल व्योम Emscripten_PumpEvents(SDL_VideoDevice *_this)
{
    अगर (!pumpevents_has_run) {
        // we assume you've set a mainloop by the time you've called pumpevents, so we delay initial SetInterval changes until then.
        // otherwise you'll get a warning on the javascript console.
        pumpevents_has_run = true;
        अगर (pending_swap_interval >= 0) {
            Emscripten_GLES_SetSwapInterval(_this, pending_swap_interval);
            pending_swap_interval = -1;
        }
    }
}

EMSCRIPTEN_KEEPALIVE व्योम requestFullscreenThroughSDL(SDL_Window *window)
{
    SDL_SetWindowFullscreen(window, true);
}

अटल bool Emscripten_SetWindowFillDocument(SDL_VideoDevice *_this, SDL_Window *window, bool fill)
{
    SDL_Window_तथ्य *wdata = window->internal;

    अगर (fill && Emscripten_fill_document_window && (Emscripten_fill_document_window != window)) {
        वापस SDL_SetError("Only one fill-document window allowed at a time.");
    }

    // fill_document takes up the entire page and resizes as the browser window resizes.
    अगर (fill) {
        Emscripten_fill_document_window = window;

        स्थिर पूर्णांक w = MAIN_THREAD_EM_ASM_INT({ वापस window.innerWidth; });
        स्थिर पूर्णांक h = MAIN_THREAD_EM_ASM_INT({ वापस window.innerHeight; });
        स्थिर द्विगुन scaled_w = w * wdata->pixel_ratio;
        स्थिर द्विगुन scaled_h = h * wdata->pixel_ratio;

        wdata->non_fill_document_width = window->w;
        wdata->non_fill_document_height = window->h;

        MAIN_THREAD_EM_ASM({
            var canvas = document.querySelector(UTF8ToString($0));
            canvas.SDL3_original_position = canvas.style.position;
            canvas.SDL3_original_शीर्ष = canvas.style.शीर्ष;
            canvas.SDL3_original_बायाँ = canvas.style.बायाँ;

            // hide everything on the page that isn't the canvas.
            var भाग = document.createElement('div');
            भाग.id = 'SDL3_fill_document_background_elements';

            भाग.SDL3_canvas = canvas;
            भाग.SDL3_canvas_parent = canvas.parent_गाँठ;
            भाग.SDL3_canvas_nextsib = canvas.अग्र_Sibling;

            var children = Array.from(document.body.children);
            क्रम (var child of children) {
                भाग.appendChild(child);
            }
            document.body.appendChild(भाग);
            भाग.style.display = 'none';
            document.body.appendChild(canvas);
            canvas.style.position = 'fixed';
            canvas.style.शीर्ष = '0';
            canvas.style.बायाँ = '0';
        }, wdata->canvas_id);

        emscripten_set_canvas_element_आकार(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // set_canvas_size unsets this
        अगर (wdata->pixel_ratio != 1.0f) {
            emscripten_set_element_css_आकार(wdata->canvas_id, w, h);
        }

        // force the event to trigger, so pixel ratio changes can be handled
        window->w = window->h = 0;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    } अन्यथा {
        स्थिर bool transitioning = (Emscripten_fill_document_window == window);
        अगर (transitioning) {
            MAIN_THREAD_EM_ASM({
                // if we had previously hidden everything behind a fill_document window, put it back.
                var भाग = document.getElementById('SDL3_fill_document_background_elements');
                अगर (भाग) {
                    अगर (भाग.SDL3_canvas_nextsib) {
                        भाग.SDL3_canvas_parent.जोड़ो_Before(भाग.SDL3_canvas, भाग.SDL3_canvas_nextsib);
                    } अन्यथा {
                        भाग.SDL3_canvas_parent.appendChild(भाग.SDL3_canvas);
                    }
                    जबतक (भाग.firstChild) {
                        document.body.जोड़ो_Before(भाग.firstChild, भाग);
                    }
                    भाग.SDL3_canvas.style.position = भाग.SDL3_canvas.SDL3_original_position;
                    भाग.SDL3_canvas.style.शीर्ष = भाग.SDL3_canvas.SDL3_original_शीर्ष;
                    भाग.SDL3_canvas.style.बायाँ = भाग.SDL3_canvas.SDL3_original_बायाँ;
                    भाग.हटाओ();
                }
            });
            Emscripten_fill_document_window = शून्य;
        }

        window->w = wdata->non_fill_document_width;
        window->h = wdata->non_fill_document_height;
        स्थिर द्विगुन scaled_w = SDL_floor(window->w * wdata->pixel_ratio);
        स्थिर द्विगुन scaled_h = SDL_floor(window->h * wdata->pixel_ratio);
        emscripten_set_canvas_element_आकार(wdata->canvas_id, SDL_lroundf(scaled_w), SDL_lroundf(scaled_h));

        // if the size is not being controlled by css, we need to scale down for hidpi
        अगर (!wdata->external_आकार && (wdata->pixel_ratio != 1.0f)) {
            // scale canvas down
            emscripten_set_element_css_आकार(wdata->canvas_id, window->w, window->h);
        }

        अगर (transitioning) {
            window->w = window->h = 0;
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, wdata->non_fill_document_width, wdata->non_fill_document_height);
        }
    }

    वापस true;
}

अटल bool Emscripten_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_Window_तथ्य *wdata;
    द्विगुन css_w, css_h;
    स्थिर अक्षर *selector;

    bool fill_document = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    अगर (fill_document && Emscripten_fill_document_window) {
        fill_document = false;  // only one allowed at a time.
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;   // !!! FIXME: should this fail instead?
    }

    // Allocate window internal data
    wdata = (SDL_Window_तथ्य *)SDL_calloc(1, माप(SDL_Window_तथ्य));
    अगर (!wdata) {
        वापस false;
    }

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR);
    अगर (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_EMSCRIPTEN_CANVAS_ID_STRING, "#canvas");
    }
    wdata->canvas_id = SDL_strdup(selector);

    selector = SDL_GetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
    अगर (!selector || !*selector) {
        selector = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_EMSCRIPTEN_KEYBOARD_ELEMENT_STRING, "#window");
    }
    wdata->keyboard_element = SDL_strdup(selector);

    अगर (window->flags & SDL_WINDOW_ऊपरी_PIXEL_DENSITY) {
        wdata->pixel_ratio = emscripten_get_device_pixel_ratio();
    } अन्यथा {
        wdata->pixel_ratio = 1.0f;
    }

    // set a fake size to check if there is any CSS sizing the canvas
    emscripten_set_canvas_element_आकार(wdata->canvas_id, 1, 1);
    emscripten_get_element_css_आकार(wdata->canvas_id, &css_w, &css_h);

    wdata->external_आकार = SDL_floor(css_w) != 1 || SDL_floor(css_h) != 1;
    अगर (wdata->external_आकार) {
        fill_document = false;  // can't be resizable if something else is controlling it.
        window->w = (पूर्णांक) css_w;
        window->h = (पूर्णांक) css_h;
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
    वापस true;
}

अटल व्योम Emscripten_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, bool resizable)
{
    // this function just has to exist or the higher level won't let the window change its SDL_WINDOW_RESIZABLE flag.
}

अटल व्योम Emscripten_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    अगर (window->internal) {
        SDL_Window_तथ्य *तथ्य = window->internal;
        अगर (window == Emscripten_fill_document_window) {
            वापस;  // canvas size is being dictated by the browser window size, refuse request.
        }

        // update pixel ratio
        अगर (window->flags & SDL_WINDOW_ऊपरी_PIXEL_DENSITY) {
            तथ्य->pixel_ratio = emscripten_get_device_pixel_ratio();
        }
        emscripten_set_canvas_element_आकार(तथ्य->canvas_id, SDL_lroundf(window->pending.w * तथ्य->pixel_ratio), SDL_lroundf(window->pending.h * तथ्य->pixel_ratio));

        // scale canvas down
        अगर (!तथ्य->external_आकार && तथ्य->pixel_ratio != 1.0f) {
            emscripten_set_element_css_आकार(तथ्य->canvas_id, window->pending.w, window->pending.h);
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
    }
}

अटल व्योम Emscripten_Get_Window_आकार_In_Pixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *w, पूर्णांक *h)
{
    SDL_Window_तथ्य *तथ्य;
    अगर (window->internal) {
        तथ्य = window->internal;
        *w = SDL_lroundf(window->w * तथ्य->pixel_ratio);
        *h = SDL_lroundf(window->h * तथ्य->pixel_ratio);
    }
}

अटल व्योम Emscripten_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य;

    Emscripten_SetWindowFillDocument(_this, window, false);

    अगर (window->internal) {
        तथ्य = window->internal;

        Emscripten_UnregisterEventHandlers(तथ्य);

        // We can't destroy the canvas, so resize it to zero instead
        emscripten_set_canvas_element_आकार(तथ्य->canvas_id, 0, 0);
        अगर (तथ्य->pixel_ratio != 1.0f) {
            emscripten_set_element_css_आकार(तथ्य->canvas_id, 1, 1);
        }
        SDL_free(तथ्य->canvas_id);

        SDL_free(तथ्य->keyboard_element);

        SDL_free(window->internal);
        window->internal = शून्य;
    }

    MAIN_THREAD_EM_ASM({
        // just ignore clicks on the fullscreen button while there's no SDL window.
        Module['requestFullscreen'] = function(lockPointer, resizeCanvas) {};
    });
}

अटल SDL_Fullscreen_परिणाम Emscripten_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_Window_तथ्य *तथ्य;
    पूर्णांक res = -1;

    अगर (window->internal) {
        तथ्य = window->internal;

        अगर (तथ्य->fullscreen_change_in_progress) {
            वापस SDL_FULLSCREEN_FAILED;;
        }

        EmscriptenFullscreenChangeEvent fsevent;
        अगर (emscripten_get_fullscreen_status(&fsevent) == EMSCRIPTEN_परिणाम_SUCCESS) {
            अगर ((fullscreen == SDL_FULLSCREEN_OP_ENTER) == fsevent.isFullscreen) {
                वापस SDL_FULLSCREEN_SUCCEEDED;  // already there.
            }
        }

        अगर (fullscreen) {
            EmscriptenFullscreenStrategy strategy;
            bool is_fullscreen_desktop = !window->fullscreen_exclusive;

            SDL_zero(strategy);
            strategy.scaleMode = is_fullscreen_desktop ? EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH : EMSCRIPTEN_FULLSCREEN_SCALE_ASPECT;

            अगर (!is_fullscreen_desktop) {
                strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE;
            } अन्यथा अगर (window->flags & SDL_WINDOW_ऊपरी_PIXEL_DENSITY) {
                strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF;
            } अन्यथा {
                strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
            }

            strategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;

            strategy.canvasResizedCallback = Emscripten_HandleCanvasResize;
            strategy.canvas_Resized_Callback_User_तथ्य = तथ्य;

            तथ्य->fullscreen_mode_flags = (window->flags & SDL_WINDOW_FULLSCREEN);
            तथ्य->fullscreen_resize = is_fullscreen_desktop;

            res = emscripten_request_fullscreen_strategy(तथ्य->canvas_id, 1, &strategy);
        } अन्यथा {
            res = emscripten_exit_fullscreen();
        }
    }

    अगर (res == EMSCRIPTEN_परिणाम_SUCCESS) {
        तथ्य->fullscreen_change_in_progress = true;   // even on success, this might animate to the new state.
        वापस SDL_FULLSCREEN_SUCCEEDED;
    } अन्यथा अगर (res == EMSCRIPTEN_परिणाम_DEFERRED) {
        तथ्य->fullscreen_change_in_progress = true;
        वापस SDL_FULLSCREEN_PENDING;
    } अन्यथा {
        वापस SDL_FULLSCREEN_FAILED;
    }
}

अटल व्योम Emscripten_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    emscripten_set_window_title(window->title);
}

अटल bool Emscripten_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
    // Create dynamic memory stream for PNG encoding
    SDL_IOStream *stream = SDL_IOFromDynamicMem();
    अगर (!stream) {
        वापस false;
    }

    // Encode icon to PNG using SDL's native PNG encoder
    अगर (!SDL_SavePNG_IO(icon, stream, false)) {
        SDL_CloseIO(stream);
        वापस false;
    }

    // Get the PNG data from the stream
    व्योम *png_तथ्य = SDL_GetPointerProperty(
        SDL_GetIOProperties(stream),
        SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER,
        शून्य
    );
    माप_प्रकार png_आकार = (माप_प्रकार)SDL_GetIOSize(stream);

    // Pass PNG data to JavaScript
    MAIN_THREAD_EM_ASM({
        // Use `.slice` to make a copy of the data if we are dealing with a SharedArrayBuffer, or `.subarray` to create a
        // view into the existing buffer if its non-shared.
        var png_तथ्य_2 = HEAPU8.बफर_2 instanceof Array_बफर ? HEAPU8.subarray($0, $0 + $1) : HEAPU8.slice($0, $0 + $1);

        var blob = new Blob([png_तथ्य_2], {type: 'image/png'});
        var url = URL.createObjectURL(blob);

        // Set as favicon (create link element if it doesn't exist)
        var link = document.querySelector("link[rel~='icon']");
        अगर (!link) {
            link = document.createElement('link');
            link.rel = 'icon';
            link.type = 'image/png';
            document.शीर्ष_2.appendChild(link);
        }

        // Revoke old URL if it exists to prevent memory leaks
        अगर (link.href && link.href.startsWith('blob:')) {
            URL.revokeObjectURL(link.href);
        }

        link.href = url;
    }, png_तथ्य, png_आकार);

    SDL_CloseIO(stream);
    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_EMSCRIPTEN
