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

#அந்தர்பாவ "SDL_internal.h"
#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../SDL_egl_c.h"
#அந்தர்பாவ "../../events/SDL_keyboard_c.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"
#அந்தர்பாவ "../../events/SDL_windowevents_c.h"
#அந்தர்பாவ "SDL_qnx.h"

#அந்தர்பாவ <errno.h>

நிலையான screen_context_t context;
நிலையான screen_event_t   event;
நிலையான bool video_initialized = false;

screen_context_t * getContext()
{
    திரும்பு &context;
}

screen_event_t * getEvent()
{
    திரும்பு &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
நிலையான bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_DisplayData      *display_data;
    SDL_DisplayMode      display_mode;
    SDL_DisplayModeData  *display_mode_data;

    முழு size[2];
    முழு index;
    முழு display_மொத்தம்;
    முழு active;

    screen_display_t *screen_display;

    எனில் (video_initialized) {
        திரும்பு true;
    }

    எனில் (screen_create_context(&context, 0) < 0) {
        திரும்பு false;
    }

    எனில் (screen_create_event(&event) < 0) {
        திரும்பு false;
    }

    /* start with no displays and increment as attached displays are found */
    எனில் (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_மொத்தம், &display_மொத்தம்) < 0) {
        திரும்பு false;
    }

    screen_display = SDL_calloc(display_மொத்தம், அளவு(screen_display_t));
    எனில் (screen_display == வெற்று) {
        திரும்பு false;
    }

    எனில் (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (வெறுமை **)screen_display) < 0) {
        திரும்பு false;
    }

    /* create SDL displays based on display info from the screen API */
    க்கு (index = 0; index < display_மொத்தம்; index++) {
        active = 0;
        எனில் (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_ATTACHED, &active) < 0) {
            SDL_free(screen_display);
            திரும்பு false;
        }

        எனில் (active) {
            display_data = (SDL_DisplayData *)SDL_calloc(1, அளவு(SDL_DisplayData));
            எனில் (display_data == வெற்று) {
                SDL_free(screen_display);
                திரும்பு false;
            }
            SDL_zerop(display_data);

            எனில் (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_SIZE, size) < 0) {
                SDL_free(screen_display);
                SDL_free(display_data);
                திரும்பு false;
            }

            display_mode_data = (SDL_DisplayModeData *)SDL_calloc(1, அளவு(SDL_DisplayModeData));
            எனில் (display_mode_data == வெற்று) {
                SDL_free(screen_display);
                SDL_free(display_data);
                திரும்பு false;
            }
            SDL_zerop(display_mode_data);

            SDL_zero(display);
            SDL_zero(display_mode);

            display_data->screen_display = screen_display[index];
            display.internal = (வெறுமை *)display_data;

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

            எனில் (!SDL_AddVideoDisplay(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_mode_data);
                SDL_free(display_data);
                திரும்பு false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, வெற்று);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, வெற்று);

    video_initialized = true;

    SDL_free(screen_display);

    திரும்பு true;
}

நிலையான வெறுமை QNX_VideoQuit(SDL_VideoDevice *_this)
{
    எனில் (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
நிலையான bool QNX_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData       *impl;
    SDL_VideoDisplay     *display = வெற்று;
    SDL_DisplayData      *display_data = வெற்று;
    SDL_DisplayModeData  *display_mode_data = வெற்று;

    முழு             size[2];
    முழு             position[2];
    முழு             numbufs;
    முழு             format;
    முழு             usage;
    முழு             has_focus_i;

    impl = SDL_calloc(1, அளவு(*impl));
    எனில் (!impl) {
        திரும்பு false;
    }
    window->internal = impl;

    // Create a native window.
    எனில் (screen_create_window(&impl->window, context) < 0) {
        செல் fail;
    }

    // Set the native window's size to match the SDL window.
    size[0] = window->w;
    size[1] = window->h;
    position[0] = window->x;
    position[1] = window->y;

    எனில் (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        செல் fail;
    }

    எனில் (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        செல் fail;
    }

    எனில் (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        செல் fail;
    }

    display = SDL_GetVideoDisplayForWindow(window);
    SDL_assert(display != வெற்று);
    SDL_assert(display->desktop_mode.internal != வெற்று);
    display_mode_data = display->desktop_mode.internal;

    // Create window buffer(s).
    எனில் (window->flags & SDL_WINDOW_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        எனில் (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            செல் fail;
        }
    } இல்லையெனில் {
        numbufs = 1;
    }

    // Create buffer(s).
    எனில் (screen_create_window_buffers(impl->window, numbufs>0?numbufs:1) < 0) {
        செல் fail;
    }

    // Initialize EGL surface.
    எனில் (window->flags & SDL_WINDOW_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
        எனில் (impl->egl_surface == EGL_NO_SURFACE) {
            செல் fail;
        }
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    எனில் (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_mode_data->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_mode.format = screenToPixelFormat(format);
    display_mode_data->screen_format = format;

    display_data = display->internal;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_data != வெற்று);

    // Get initial focus state. Fallback to true.
    எனில்(screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } இல்லையெனில் {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_WINDOW_POINTER, impl->window);

    திரும்பு true;

fail:
    எனில் (impl->window) {
        screen_destroy_window(impl->window);
    }
    எனில் (display_data) {
        SDL_free(display_data);
        display->internal = வெற்று;
    }

    SDL_free(impl);
    window->internal = வெற்று;
    திரும்பு false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
நிலையான bool QNX_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format,
                        வெறுமை ** pixels, முழு *pitch)
{
    முழு              buffer_மொத்தம்_2;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t  *buffer;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);

    எனில் (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_மொத்தம், &buffer_மொத்தம்_2) < 0) {
        திரும்பு false;
    }
    buffer = SDL_calloc(buffer_மொத்தம்_2, அளவு(screen_buffer_t));

    // Get a pointer to the buffer's memory.
    எனில் (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (வெறுமை **)buffer) < 0) {
        திரும்பு false;
    }

    எனில் (screen_get_buffer_property_pv(*buffer, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        திரும்பு false;
    }

    // Set format and pitch.
    எனில் (screen_get_buffer_property_iv(*buffer, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        திரும்பு false;
    }

    *format = display->desktop_mode.format;
    திரும்பு true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
நிலையான bool QNX_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, மாறிலி SDL_Rect *rects,
                        முழு numrects)
{
    முழு buffer_மொத்தம்_2, *rects_int;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t *buffer;

    எனில் (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_மொத்தம், &buffer_மொத்தம்_2) < 0) {
        திரும்பு false;
    }
    buffer = SDL_calloc(buffer_மொத்தம்_2, அளவு(screen_buffer_t));

    எனில் (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (வெறுமை **)buffer) < 0) {
        திரும்பு false;
    }

    எனில்(numrects>0){
        rects_int = SDL_calloc(4*numrects, அளவு(முழு));

        க்கு(முழு i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        எனில்(screen_post_window(impl->window, buffer[0], numrects, rects_int, 0)) {
            திரும்பு false;
        }
        எனில்(screen_flush_context(context, 0)) {
            திரும்பு false;
        }
    }
    திரும்பு true;
}

நிலையான SDL_FullscreenResult QNX_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *window_data = window->internal;
    முழு size[2] = { 0, 0 };
    முழு position[2] = { 0, 0 };

    எனில் (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        திரும்பு SDL_FULLSCREEN_SUCCEEDED;
    }

    எனில் (fullscreen) {
        SDL_Rect bounds;

        எனில் (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            திரும்பு SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        size[0] = bounds.w;
        size[1] = bounds.h;
    } இல்லையெனில் {
        position[0] = window->x;
        position[1] = window->y;
        size[0] = window->w;
        size[1] = window->h;
    }

    எனில் (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        திரும்பு SDL_FULLSCREEN_FAILED;
    }

    எனில் (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        திரும்பு SDL_FULLSCREEN_FAILED;
    }

    எனில் (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        திரும்பு SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);

    திரும்பு SDL_FULLSCREEN_SUCCEEDED;
}

நிலையான SDL_DisplayID QNX_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_WindowData  *impl = (SDL_WindowData *)window->internal;
    SDL_DisplayData *display_data;

    screen_display_t screen_display;

    எனில் (impl == வெற்று) {
        திரும்பு 0;
    }

    எனில் (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_DISPLAY, (வெறுமை **)&screen_display) < 0) {
        திரும்பு 0;
    }

    க்கு (முழு i = 0; i < _this->இலக்கம்_displays; i++) {
        display_data = _this->displays[i]->internal;
        எனில் (display_data && (display_data->screen_display == screen_display)) {
            திரும்பு _this->displays[i]->id;
        }
    }

    திரும்பு 0;
}

/**
 * Runs the main event loop.
 */
நிலையான வெறுமை QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Window      *window;
    SDL_WindowData   *impl;
    முழு             type;
    முழு             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    க்கு (window = _this->windows; window; window = window->next) {
        impl = (SDL_WindowData *)window->internal;
        எனில் (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            தொடர்;
        }
        has_focus = (bool)has_focus_i;

        எனில் (impl->has_focus != has_focus) {
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST), 0, 0);
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_MOUSE_ENTER : SDL_EVENT_WINDOW_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_SetMouseFocus(window);
            SDL_SetKeyboardFocus(window);
        }
    }

    க்கு (;;) {
        எனில் (screen_get_event(context, event, 0) < 0) {
            நிறுத்து;
        }

        எனில் (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            நிறுத்து;
        }

        எனில் (type == SCREEN_EVENT_NONE) {
            நிறுத்து;
        }

        தேர்வு (type) {
        நிலை SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            நிறுத்து;

        நிலை SCREEN_EVENT_POINTER:
            handlePointerEvent(event);
            நிறுத்து;

        இயல்பு:
            நிறுத்து;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
நிலையான வெறுமை QNX_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    முழு             size[2];

    size[0] = window->pending.w;
    size[1] = window->pending.h;

    எனில் (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        எனில் (screen_destroy_window_buffers(impl->window) < 0) {
            திரும்பு;
        }
        impl->resize = true;

        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size);
        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size);

        screen_create_window_buffers(impl->window, (window->flags & SDL_WINDOW_OPENGL) ? 2 : 1);
    } இல்லையெனில் {
        window->last_size_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
நிலையான வெறுமை QNX_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    மாறிலி முழு       visible = 1;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
நிலையான வெறுமை QNX_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    மாறிலி முழு       visible = 0;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
நிலையான வெறுமை QNX_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;

    எனில் (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_window(impl->window);
        window->internal = வெற்று;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
நிலையான வெறுமை QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
நிலையான SDL_VideoDevice *createDevice(வெறுமை)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, அளவு(SDL_VideoDevice));
    எனில் (!device) {
        திரும்பு வெற்று;
    }

    device->internal = வெற்று;
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
#எனில் 0
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

    device->விடுவி = QNX_DeleteDevice;

    திரும்பு device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    வெற்று, // no ShowMessageBox implementation
    false
};
