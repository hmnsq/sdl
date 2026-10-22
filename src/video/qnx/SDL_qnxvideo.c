/*
  Simple DirectMedia Layer
  Copyright (C) 2026 BlackBerry Limited

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
#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../SDL_egl_c.h"
#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../events/SDL_windowevents_c.h"
#അന്തര്ഭാവ "SDL_qnx.h"

#അന്തര്ഭാവ <errno.h>

സ്ഥിതം screen_context_t context;
സ്ഥിതം screen_event_t   event;
സ്ഥിതം bool video_initialized = false;

screen_context_t * getContext()
{
    തിരികെ &context;
}

screen_event_t * getEvent()
{
    തിരികെ &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
സ്ഥിതം bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_DisplayData      *display_data;
    SDL_DisplayMode      display_mode;
    SDL_DisplayModeData  *display_mode_data;

    പൂർണ്ണസംഖ്യ size[2];
    പൂർണ്ണസംഖ്യ index;
    പൂർണ്ണസംഖ്യ display_എണ്ണം;
    പൂർണ്ണസംഖ്യ active;

    screen_display_t *screen_display;

    എങ്കിൽ (video_initialized) {
        തിരികെ true;
    }

    എങ്കിൽ (screen_create_context(&context, 0) < 0) {
        തിരികെ false;
    }

    എങ്കിൽ (screen_create_event(&event) < 0) {
        തിരികെ false;
    }

    /* start with no displays and increment as attached displays are found */
    എങ്കിൽ (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_എണ്ണം, &display_എണ്ണം) < 0) {
        തിരികെ false;
    }

    screen_display = SDL_calloc(display_എണ്ണം, വലുപ്പം(screen_display_t));
    എങ്കിൽ (screen_display == ശൂന്യ) {
        തിരികെ false;
    }

    എങ്കിൽ (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (ശൂന്യം **)screen_display) < 0) {
        തിരികെ false;
    }

    /* create SDL displays based on display info from the screen API */
    വേണ്ടി (index = 0; index < display_എണ്ണം; index++) {
        active = 0;
        എങ്കിൽ (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_ATTACHED, &active) < 0) {
            SDL_free(screen_display);
            തിരികെ false;
        }

        എങ്കിൽ (active) {
            display_data = (SDL_DisplayData *)SDL_calloc(1, വലുപ്പം(SDL_DisplayData));
            എങ്കിൽ (display_data == ശൂന്യ) {
                SDL_free(screen_display);
                തിരികെ false;
            }
            SDL_zerop(display_data);

            എങ്കിൽ (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_SIZE, size) < 0) {
                SDL_free(screen_display);
                SDL_free(display_data);
                തിരികെ false;
            }

            display_mode_data = (SDL_DisplayModeData *)SDL_calloc(1, വലുപ്പം(SDL_DisplayModeData));
            എങ്കിൽ (display_mode_data == ശൂന്യ) {
                SDL_free(screen_display);
                SDL_free(display_data);
                തിരികെ false;
            }
            SDL_zerop(display_mode_data);

            SDL_zero(display);
            SDL_zero(display_mode);

            display_data->screen_display = screen_display[index];
            display.internal = (ശൂന്യം *)display_data;

            display_mode.w = size[0];
            display_mode.h = size[1];
            display_mode.refresh_rate = 60;
            display_mode.pixel_density = 1.0;
            display_mode.internal = display_mode_data;
            // This is assigned later when the window is created. For now, use a
            // safe guess.
            display_mode.format = SDL_PIXELFORMAT_RGBX8888;
            display_mode_data->screen_format = SCREEN_FORMAT_RGBX8888;
            // Be able to revert to the default display mode despite not having
            // the actual object to refer to.
            display_mode_data->screen_display_mode.index = SCREEN_DISPLAY_MODE_PREFERRED_INDEX;

            // Added to current_mode when the display is added.
            display.desktop_mode = display_mode;

            എങ്കിൽ (!SDL_AddVideoDisplay(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_mode_data);
                SDL_free(display_data);
                തിരികെ false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ശൂന്യ);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ശൂന്യ);

    video_initialized = true;

    SDL_free(screen_display);

    തിരികെ true;
}

സ്ഥിതം ശൂന്യം QNX_VideoQuit(SDL_VideoDevice *_this)
{
    എങ്കിൽ (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
സ്ഥിതം bool QNX_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData       *impl;
    SDL_VideoDisplay     *display = ശൂന്യ;
    SDL_DisplayData      *display_data = ശൂന്യ;
    SDL_DisplayModeData  *display_mode_data = ശൂന്യ;

    പൂർണ്ണസംഖ്യ             size[2];
    പൂർണ്ണസംഖ്യ             position[2];
    പൂർണ്ണസംഖ്യ             numbufs;
    പൂർണ്ണസംഖ്യ             format;
    പൂർണ്ണസംഖ്യ             usage;
    പൂർണ്ണസംഖ്യ             has_focus_i;

    impl = SDL_calloc(1, വലുപ്പം(*impl));
    എങ്കിൽ (!impl) {
        തിരികെ false;
    }
    window->internal = impl;

    // Create a native window.
    എങ്കിൽ (screen_create_window(&impl->window, context) < 0) {
        പോകുക fail;
    }

    // Set the native window's size to match the SDL window.
    size[0] = window->w;
    size[1] = window->h;
    position[0] = window->x;
    position[1] = window->y;

    എങ്കിൽ (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        പോകുക fail;
    }

    എങ്കിൽ (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        പോകുക fail;
    }

    എങ്കിൽ (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        പോകുക fail;
    }

    display = SDL_GetVideoDisplayForWindow(window);
    SDL_assert(display != ശൂന്യ);
    SDL_assert(display->desktop_mode.internal != ശൂന്യ);
    display_mode_data = display->desktop_mode.internal;

    // Create window buffer(s).
    എങ്കിൽ (window->flags & SDL_WINDOW_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        എങ്കിൽ (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            പോകുക fail;
        }
    } അല്ലെങ്കിൽ {
        numbufs = 1;
    }

    // Create buffer(s).
    എങ്കിൽ (screen_create_window_buffers(impl->window, numbufs>0?numbufs:1) < 0) {
        പോകുക fail;
    }

    // Initialize EGL surface.
    എങ്കിൽ (window->flags & SDL_WINDOW_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
        എങ്കിൽ (impl->egl_surface == EGL_NO_SURFACE) {
            പോകുക fail;
        }
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    എങ്കിൽ (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_mode_data->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_mode.format = screenToPixelFormat(format);
    display_mode_data->screen_format = format;

    display_data = display->internal;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_data != ശൂന്യ);

    // Get initial focus state. Fallback to true.
    എങ്കിൽ(screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } അല്ലെങ്കിൽ {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_WINDOW_POINTER, impl->window);

    തിരികെ true;

fail:
    എങ്കിൽ (impl->window) {
        screen_destroy_window(impl->window);
    }
    എങ്കിൽ (display_data) {
        SDL_free(display_data);
        display->internal = ശൂന്യ;
    }

    SDL_free(impl);
    window->internal = ശൂന്യ;
    തിരികെ false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
സ്ഥിതം bool QNX_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format,
                        ശൂന്യം ** pixels, പൂർണ്ണസംഖ്യ *pitch)
{
    പൂർണ്ണസംഖ്യ              buffer_എണ്ണം_2;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t  *buffer;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);

    എങ്കിൽ (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_എണ്ണം, &buffer_എണ്ണം_2) < 0) {
        തിരികെ false;
    }
    buffer = SDL_calloc(buffer_എണ്ണം_2, വലുപ്പം(screen_buffer_t));

    // Get a pointer to the buffer's memory.
    എങ്കിൽ (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (ശൂന്യം **)buffer) < 0) {
        തിരികെ false;
    }

    എങ്കിൽ (screen_get_buffer_property_pv(*buffer, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        തിരികെ false;
    }

    // Set format and pitch.
    എങ്കിൽ (screen_get_buffer_property_iv(*buffer, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        തിരികെ false;
    }

    *format = display->desktop_mode.format;
    തിരികെ true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
സ്ഥിതം bool QNX_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, സ്ഥിരം SDL_Rect *rects,
                        പൂർണ്ണസംഖ്യ numrects)
{
    പൂർണ്ണസംഖ്യ buffer_എണ്ണം_2, *rects_int;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t *buffer;

    എങ്കിൽ (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_എണ്ണം, &buffer_എണ്ണം_2) < 0) {
        തിരികെ false;
    }
    buffer = SDL_calloc(buffer_എണ്ണം_2, വലുപ്പം(screen_buffer_t));

    എങ്കിൽ (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (ശൂന്യം **)buffer) < 0) {
        തിരികെ false;
    }

    എങ്കിൽ(numrects>0){
        rects_int = SDL_calloc(4*numrects, വലുപ്പം(പൂർണ്ണസംഖ്യ));

        വേണ്ടി(പൂർണ്ണസംഖ്യ i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        എങ്കിൽ(screen_post_window(impl->window, buffer[0], numrects, rects_int, 0)) {
            തിരികെ false;
        }
        എങ്കിൽ(screen_flush_context(context, 0)) {
            തിരികെ false;
        }
    }
    തിരികെ true;
}

സ്ഥിതം SDL_FullscreenResult QNX_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *window_data = window->internal;
    പൂർണ്ണസംഖ്യ size[2] = { 0, 0 };
    പൂർണ്ണസംഖ്യ position[2] = { 0, 0 };

    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        തിരികെ SDL_FULLSCREEN_SUCCEEDED;
    }

    എങ്കിൽ (fullscreen) {
        SDL_Rect bounds;

        എങ്കിൽ (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            തിരികെ SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        size[0] = bounds.w;
        size[1] = bounds.h;
    } അല്ലെങ്കിൽ {
        position[0] = window->x;
        position[1] = window->y;
        size[0] = window->w;
        size[1] = window->h;
    }

    എങ്കിൽ (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        തിരികെ SDL_FULLSCREEN_FAILED;
    }

    എങ്കിൽ (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        തിരികെ SDL_FULLSCREEN_FAILED;
    }

    എങ്കിൽ (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        തിരികെ SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);

    തിരികെ SDL_FULLSCREEN_SUCCEEDED;
}

സ്ഥിതം SDL_DisplayID QNX_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_WindowData  *impl = (SDL_WindowData *)window->internal;
    SDL_DisplayData *display_data;

    screen_display_t screen_display;

    എങ്കിൽ (impl == ശൂന്യ) {
        തിരികെ 0;
    }

    എങ്കിൽ (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_DISPLAY, (ശൂന്യം **)&screen_display) < 0) {
        തിരികെ 0;
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < _this->അക്കം_displays; i++) {
        display_data = _this->displays[i]->internal;
        എങ്കിൽ (display_data && (display_data->screen_display == screen_display)) {
            തിരികെ _this->displays[i]->id;
        }
    }

    തിരികെ 0;
}

/**
 * Runs the main event loop.
 */
സ്ഥിതം ശൂന്യം QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Window      *window;
    SDL_WindowData   *impl;
    പൂർണ്ണസംഖ്യ             type;
    പൂർണ്ണസംഖ്യ             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    വേണ്ടി (window = _this->windows; window; window = window->next) {
        impl = (SDL_WindowData *)window->internal;
        എങ്കിൽ (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            തുടരുക;
        }
        has_focus = (bool)has_focus_i;

        എങ്കിൽ (impl->has_focus != has_focus) {
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST), 0, 0);
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_MOUSE_ENTER : SDL_EVENT_WINDOW_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_SetMouseFocus(window);
            SDL_SetKeyboardFocus(window);
        }
    }

    വേണ്ടി (;;) {
        എങ്കിൽ (screen_get_event(context, event, 0) < 0) {
            നിർത്തുക;
        }

        എങ്കിൽ (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            നിർത്തുക;
        }

        എങ്കിൽ (type == SCREEN_EVENT_NONE) {
            നിർത്തുക;
        }

        തിരഞ്ഞെടുപ്പ് (type) {
        അവസ്ഥ SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            നിർത്തുക;

        അവസ്ഥ SCREEN_EVENT_POINTER:
            handlePointerEvent(event);
            നിർത്തുക;

        സ്ഥിരസ്ഥിതി:
            നിർത്തുക;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
സ്ഥിതം ശൂന്യം QNX_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    പൂർണ്ണസംഖ്യ             size[2];

    size[0] = window->pending.w;
    size[1] = window->pending.h;

    എങ്കിൽ (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        എങ്കിൽ (screen_destroy_window_buffers(impl->window) < 0) {
            തിരികെ;
        }
        impl->resize = true;

        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size);
        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size);

        screen_create_window_buffers(impl->window, (window->flags & SDL_WINDOW_OPENGL) ? 2 : 1);
    } അല്ലെങ്കിൽ {
        window->last_size_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
സ്ഥിതം ശൂന്യം QNX_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    സ്ഥിരം പൂർണ്ണസംഖ്യ       visible = 1;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
സ്ഥിതം ശൂന്യം QNX_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    സ്ഥിരം പൂർണ്ണസംഖ്യ       visible = 0;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
സ്ഥിതം ശൂന്യം QNX_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;

    എങ്കിൽ (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_window(impl->window);
        window->internal = ശൂന്യ;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
സ്ഥിതം ശൂന്യം QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
സ്ഥിതം SDL_VideoDevice *createDevice(ശൂന്യം)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, വലുപ്പം(SDL_VideoDevice));
    എങ്കിൽ (!device) {
        തിരികെ ശൂന്യ;
    }

    device->internal = ശൂന്യ;
    device->VideoInit = QNX_VideoInit;
    device->VideoQuit = QNX_VideoQuit;
    device->CreateSDLWindow = QNX_CreateWindow;
    device->CreateWindowFramebuffer = QNX_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = QNX_UpdateWindowFramebuffer;
    device->SetWindowSize = QNX_SetWindowSize;
    device->SetWindowFullscreen = QNX_SetWindowFullscreen;
    device->ShowWindow = QNX_ShowWindow;
    device->HideWindow = QNX_HideWindow;
    device->GetDisplayForWindow = QNX_GetDisplayForWindow;
    device->GetDisplayBounds = QNX_GetDisplayBounds;
    device->GetDisplayModes = QNX_GetDisplayModes;
#എങ്കിൽ 0
    device->SetDisplayMode = QNX_SetDisplayMode;
#endif
    device->PumpEvents = QNX_PumpEvents;
    device->DestroyWindow = QNX_DestroyWindow;

    device->GL_LoadLibrary = QNX_GLES_LoadLibrary;
    device->GL_GetProcAddress = QNX_GLES_GetProcAddress;
    device->GL_CreateContext = QNX_GLES_CreateContext;
    device->GL_SetSwapInterval = QNX_GLES_SetSwapInterval;
    device->GL_GetSwapInterval = QNX_GLES_GetSwapInterval;
    device->GL_SwapWindow = QNX_GLES_SwapWindow;
    device->GL_MakeCurrent = QNX_GLES_MakeCurrent;
    device->GL_DestroyContext = QNX_GLES_DeleteContext;
    device->GL_UnloadLibrary = QNX_GLES_UnloadLibrary;

    device->സ്വതന്ത്രം = QNX_DeleteDevice;

    തിരികെ device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    ശൂന്യ, // no ShowMessageBox implementation
    false
};
