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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_qnx.h"

#ಅನ್ತರ್ಭಾವ <errno.h>

ಸ್ಥಿರ screen_context_t context;
ಸ್ಥಿರ screen_event_t   event;
ಸ್ಥಿರ bool video_initialized = false;

screen_context_t * getContext()
{
    ಪ್ರತ್ಯಾಗಮ &context;
}

screen_event_t * getEvent()
{
    ಪ್ರತ್ಯಾಗಮ &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
ಸ್ಥಿರ bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_DisplayData      *display_data;
    SDL_DisplayMode      display_mode;
    SDL_DisplayModeData  *display_mode_data;

    ಪೂರ್ಣಾಙ್ಕ size[2];
    ಪೂರ್ಣಾಙ್ಕ index;
    ಪೂರ್ಣಾಙ್ಕ display_ಎಣಿಕೆ;
    ಪೂರ್ಣಾಙ್ಕ active;

    screen_display_t *screen_display;

    ಯದಿ (video_initialized) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (screen_create_context(&context, 0) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (screen_create_event(&event) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    /* start with no displays and increment as attached displays are found */
    ಯದಿ (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_ಎಣಿಕೆ, &display_ಎಣಿಕೆ) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    screen_display = SDL_calloc(display_ಎಣಿಕೆ, ಪರಿಮಾಣ(screen_display_t));
    ಯದಿ (screen_display == ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (ಶೂನ್ಯ **)screen_display) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    /* create SDL displays based on display info from the screen API */
    ಪ್ರತಿ (index = 0; index < display_ಎಣಿಕೆ; index++) {
        active = 0;
        ಯದಿ (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_ATTACHED, &active) < 0) {
            SDL_free(screen_display);
            ಪ್ರತ್ಯಾಗಮ false;
        }

        ಯದಿ (active) {
            display_data = (SDL_DisplayData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_DisplayData));
            ಯದಿ (display_data == ರಿಕ್ತ) {
                SDL_free(screen_display);
                ಪ್ರತ್ಯಾಗಮ false;
            }
            SDL_zerop(display_data);

            ಯದಿ (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_SIZE, size) < 0) {
                SDL_free(screen_display);
                SDL_free(display_data);
                ಪ್ರತ್ಯಾಗಮ false;
            }

            display_mode_data = (SDL_DisplayModeData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_DisplayModeData));
            ಯದಿ (display_mode_data == ರಿಕ್ತ) {
                SDL_free(screen_display);
                SDL_free(display_data);
                ಪ್ರತ್ಯಾಗಮ false;
            }
            SDL_zerop(display_mode_data);

            SDL_zero(display);
            SDL_zero(display_mode);

            display_data->screen_display = screen_display[index];
            display.internal = (ಶೂನ್ಯ *)display_data;

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

            ಯದಿ (!SDL_AddVideoDisplay(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_mode_data);
                SDL_free(display_data);
                ಪ್ರತ್ಯಾಗಮ false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ರಿಕ್ತ);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ರಿಕ್ತ);

    video_initialized = true;

    SDL_free(screen_display);

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ QNX_VideoQuit(SDL_VideoDevice *_this)
{
    ಯದಿ (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
ಸ್ಥಿರ bool QNX_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData       *impl;
    SDL_VideoDisplay     *display = ರಿಕ್ತ;
    SDL_DisplayData      *display_data = ರಿಕ್ತ;
    SDL_DisplayModeData  *display_mode_data = ರಿಕ್ತ;

    ಪೂರ್ಣಾಙ್ಕ             size[2];
    ಪೂರ್ಣಾಙ್ಕ             position[2];
    ಪೂರ್ಣಾಙ್ಕ             numbufs;
    ಪೂರ್ಣಾಙ್ಕ             format;
    ಪೂರ್ಣಾಙ್ಕ             usage;
    ಪೂರ್ಣಾಙ್ಕ             has_focus_i;

    impl = SDL_calloc(1, ಪರಿಮಾಣ(*impl));
    ಯದಿ (!impl) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    window->internal = impl;

    // Create a native window.
    ಯದಿ (screen_create_window(&impl->window, context) < 0) {
        ಗಚ್ಛ fail;
    }

    // Set the native window's size to match the SDL window.
    size[0] = window->w;
    size[1] = window->h;
    position[0] = window->x;
    position[1] = window->y;

    ಯದಿ (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        ಗಚ್ಛ fail;
    }

    ಯದಿ (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        ಗಚ್ಛ fail;
    }

    ಯದಿ (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        ಗಚ್ಛ fail;
    }

    display = SDL_GetVideoDisplayForWindow(window);
    SDL_assert(display != ರಿಕ್ತ);
    SDL_assert(display->desktop_mode.internal != ರಿಕ್ತ);
    display_mode_data = display->desktop_mode.internal;

    // Create window buffer(s).
    ಯದಿ (window->flags & SDL_WINDOW_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        ಯದಿ (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            ಗಚ್ಛ fail;
        }
    } ಅನ್ಯಥಾ {
        numbufs = 1;
    }

    // Create buffer(s).
    ಯದಿ (screen_create_window_buffers(impl->window, numbufs>0?numbufs:1) < 0) {
        ಗಚ್ಛ fail;
    }

    // Initialize EGL surface.
    ಯದಿ (window->flags & SDL_WINDOW_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
        ಯದಿ (impl->egl_surface == EGL_NO_SURFACE) {
            ಗಚ್ಛ fail;
        }
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    ಯದಿ (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_mode_data->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_mode.format = screenToPixelFormat(format);
    display_mode_data->screen_format = format;

    display_data = display->internal;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_data != ರಿಕ್ತ);

    // Get initial focus state. Fallback to true.
    ಯದಿ(screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } ಅನ್ಯಥಾ {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_WINDOW_POINTER, impl->window);

    ಪ್ರತ್ಯಾಗಮ true;

fail:
    ಯದಿ (impl->window) {
        screen_destroy_window(impl->window);
    }
    ಯದಿ (display_data) {
        SDL_free(display_data);
        display->internal = ರಿಕ್ತ;
    }

    SDL_free(impl);
    window->internal = ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
ಸ್ಥಿರ bool QNX_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format,
                        ಶೂನ್ಯ ** pixels, ಪೂರ್ಣಾಙ್ಕ *pitch)
{
    ಪೂರ್ಣಾಙ್ಕ              buffer_ಎಣಿಕೆ_2;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t  *buffer;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);

    ಯದಿ (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_ಎಣಿಕೆ, &buffer_ಎಣಿಕೆ_2) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    buffer = SDL_calloc(buffer_ಎಣಿಕೆ_2, ಪರಿಮಾಣ(screen_buffer_t));

    // Get a pointer to the buffer's memory.
    ಯದಿ (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (ಶೂನ್ಯ **)buffer) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (screen_get_buffer_property_pv(*buffer, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Set format and pitch.
    ಯದಿ (screen_get_buffer_property_iv(*buffer, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    *format = display->desktop_mode.format;
    ಪ್ರತ್ಯಾಗಮ true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
ಸ್ಥಿರ bool QNX_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ಧ್ರುವ SDL_Rect *rects,
                        ಪೂರ್ಣಾಙ್ಕ numrects)
{
    ಪೂರ್ಣಾಙ್ಕ buffer_ಎಣಿಕೆ_2, *rects_int;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t *buffer;

    ಯದಿ (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_ಎಣಿಕೆ, &buffer_ಎಣಿಕೆ_2) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    buffer = SDL_calloc(buffer_ಎಣಿಕೆ_2, ಪರಿಮಾಣ(screen_buffer_t));

    ಯದಿ (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (ಶೂನ್ಯ **)buffer) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ(numrects>0){
        rects_int = SDL_calloc(4*numrects, ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ));

        ಪ್ರತಿ(ಪೂರ್ಣಾಙ್ಕ i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        ಯದಿ(screen_post_window(impl->window, buffer[0], numrects, rects_int, 0)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        ಯದಿ(screen_flush_context(context, 0)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ SDL_FullscreenResult QNX_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *window_data = window->internal;
    ಪೂರ್ಣಾಙ್ಕ size[2] = { 0, 0 };
    ಪೂರ್ಣಾಙ್ಕ position[2] = { 0, 0 };

    ಯದಿ (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        ಪ್ರತ್ಯಾಗಮ SDL_FULLSCREEN_SUCCEEDED;
    }

    ಯದಿ (fullscreen) {
        SDL_Rect bounds;

        ಯದಿ (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            ಪ್ರತ್ಯಾಗಮ SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        size[0] = bounds.w;
        size[1] = bounds.h;
    } ಅನ್ಯಥಾ {
        position[0] = window->x;
        position[1] = window->y;
        size[0] = window->w;
        size[1] = window->h;
    }

    ಯದಿ (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_FULLSCREEN_FAILED;
    }

    ಯದಿ (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_FULLSCREEN_FAILED;
    }

    ಯದಿ (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);

    ಪ್ರತ್ಯಾಗಮ SDL_FULLSCREEN_SUCCEEDED;
}

ಸ್ಥಿರ SDL_DisplayID QNX_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_WindowData  *impl = (SDL_WindowData *)window->internal;
    SDL_DisplayData *display_data;

    screen_display_t screen_display;

    ಯದಿ (impl == ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಯದಿ (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_DISPLAY, (ಶೂನ್ಯ **)&screen_display) < 0) {
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < _this->ಅಂಕೆ_displays; i++) {
        display_data = _this->displays[i]->internal;
        ಯದಿ (display_data && (display_data->screen_display == screen_display)) {
            ಪ್ರತ್ಯಾಗಮ _this->displays[i]->id;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

/**
 * Runs the main event loop.
 */
ಸ್ಥಿರ ಶೂನ್ಯ QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Window      *window;
    SDL_WindowData   *impl;
    ಪೂರ್ಣಾಙ್ಕ             type;
    ಪೂರ್ಣಾಙ್ಕ             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    ಪ್ರತಿ (window = _this->windows; window; window = window->next) {
        impl = (SDL_WindowData *)window->internal;
        ಯದಿ (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            ಅನುವರ್ತ;
        }
        has_focus = (bool)has_focus_i;

        ಯದಿ (impl->has_focus != has_focus) {
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST), 0, 0);
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_MOUSE_ENTER : SDL_EVENT_WINDOW_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_SetMouseFocus(window);
            SDL_SetKeyboardFocus(window);
        }
    }

    ಪ್ರತಿ (;;) {
        ಯದಿ (screen_get_event(context, event, 0) < 0) {
            ಭಙ್ಗ;
        }

        ಯದಿ (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            ಭಙ್ಗ;
        }

        ಯದಿ (type == SCREEN_EVENT_NONE) {
            ಭಙ್ಗ;
        }

        ವಿಕಲ್ಪ (type) {
        ಪಕ್ಷ SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            ಭಙ್ಗ;

        ಪಕ್ಷ SCREEN_EVENT_POINTER:
            handlePointerEvent(event);
            ಭಙ್ಗ;

        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
ಸ್ಥಿರ ಶೂನ್ಯ QNX_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ಪೂರ್ಣಾಙ್ಕ             size[2];

    size[0] = window->pending.w;
    size[1] = window->pending.h;

    ಯದಿ (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        ಯದಿ (screen_destroy_window_buffers(impl->window) < 0) {
            ಪ್ರತ್ಯಾಗಮ;
        }
        impl->resize = true;

        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size);
        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size);

        screen_create_window_buffers(impl->window, (window->flags & SDL_WINDOW_OPENGL) ? 2 : 1);
    } ಅನ್ಯಥಾ {
        window->last_size_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
ಸ್ಥಿರ ಶೂನ್ಯ QNX_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ       visible = 1;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
ಸ್ಥಿರ ಶೂನ್ಯ QNX_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ       visible = 0;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
ಸ್ಥಿರ ಶೂನ್ಯ QNX_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;

    ಯದಿ (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_window(impl->window);
        window->internal = ರಿಕ್ತ;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
ಸ್ಥಿರ ಶೂನ್ಯ QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
ಸ್ಥಿರ SDL_VideoDevice *createDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoDevice));
    ಯದಿ (!device) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    device->internal = ರಿಕ್ತ;
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
#ಯದಿ 0
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

    device->ಮುಕ್ತ = QNX_DeleteDevice;

    ಪ್ರತ್ಯಾಗಮ device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    ರಿಕ್ತ, // no ShowMessageBox implementation
    false
};
