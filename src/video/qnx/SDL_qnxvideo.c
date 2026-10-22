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

#include "SDL_internal.h"
#include "../SDL_sysvideo.h"
#include "../SDL_egl_c.h"
#include "../../events/SDL_keyboard_c.h"
#include "../../events/SDL_mouse_c.h"
#include "../../events/SDL_windowevents_c.h"
#include "SDL_qnx.h"

#include <errno.h>

static screen_context_t context;
static screen_event_t   event;
static bool video_initialized = false;

screen_context_t * getContext()
{
    ត្រឡប់ &context;
}

screen_event_t * getEvent()
{
    ត្រឡប់ &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
static bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_DisplayData      *display_data;
    SDL_DisplayMode      display_mode;
    SDL_DisplayModeData  *display_mode_data;

    ចំនួនគត់ size[2];
    ចំនួនគត់ index;
    ចំនួនគត់ display_count;
    ចំនួនគត់ active;

    screen_display_t *screen_display;

    ប្រសិនបើ (video_initialized) {
        ត្រឡប់ true;
    }

    ប្រសិនបើ (screen_create_context(&context, 0) < 0) {
        ត្រឡប់ false;
    }

    ប្រសិនបើ (screen_create_event(&event) < 0) {
        ត្រឡប់ false;
    }

    /* start with no displays and increment as attached displays are found */
    ប្រសិនបើ (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_COUNT, &display_count) < 0) {
        ត្រឡប់ false;
    }

    screen_display = SDL_calloc(display_count, parimaa_na(screen_display_t));
    ប្រសិនបើ (screen_display == NULL) {
        ត្រឡប់ false;
    }

    ប្រសិនបើ (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (void **)screen_display) < 0) {
        ត្រឡប់ false;
    }

    /* create SDL displays based on display info from the screen API */
    សម្រាប់ (index = 0; index < display_count; index++) {
        active = 0;
        ប្រសិនបើ (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_ATTACHED, &active) < 0) {
            SDL_free(screen_display);
            ត្រឡប់ false;
        }

        ប្រសិនបើ (active) {
            display_data = (SDL_DisplayData *)SDL_calloc(1, parimaa_na(SDL_DisplayData));
            ប្រសិនបើ (display_data == NULL) {
                SDL_free(screen_display);
                ត្រឡប់ false;
            }
            SDL_zerop(display_data);

            ប្រសិនបើ (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_SIZE, size) < 0) {
                SDL_free(screen_display);
                SDL_free(display_data);
                ត្រឡប់ false;
            }

            display_mode_data = (SDL_DisplayModeData *)SDL_calloc(1, parimaa_na(SDL_DisplayModeData));
            ប្រសិនបើ (display_mode_data == NULL) {
                SDL_free(screen_display);
                SDL_free(display_data);
                ត្រឡប់ false;
            }
            SDL_zerop(display_mode_data);

            SDL_zero(display);
            SDL_zero(display_mode);

            display_data->screen_display = screen_display[index];
            display.internal = (void *)display_data;

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

            ប្រសិនបើ (!SDL_AddVideoDisplay(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_mode_data);
                SDL_free(display_data);
                ត្រឡប់ false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, NULL);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, NULL);

    video_initialized = true;

    SDL_free(screen_display);

    ត្រឡប់ true;
}

static void QNX_VideoQuit(SDL_VideoDevice *_this)
{
    ប្រសិនបើ (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
static bool QNX_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData       *impl;
    SDL_VideoDisplay     *display = NULL;
    SDL_DisplayData      *display_data = NULL;
    SDL_DisplayModeData  *display_mode_data = NULL;

    ចំនួនគត់             size[2];
    ចំនួនគត់             position[2];
    ចំនួនគត់             numbufs;
    ចំនួនគត់             format;
    ចំនួនគត់             usage;
    ចំនួនគត់             has_focus_i;

    impl = SDL_calloc(1, parimaa_na(*impl));
    ប្រសិនបើ (!impl) {
        ត្រឡប់ false;
    }
    window->internal = impl;

    // Create a native window.
    ប្រសិនបើ (screen_create_window(&impl->window, context) < 0) {
        goto fail;
    }

    // Set the native window's size to match the SDL window.
    size[0] = window->w;
    size[1] = window->h;
    position[0] = window->x;
    position[1] = window->y;

    ប្រសិនបើ (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        goto fail;
    }

    ប្រសិនបើ (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        goto fail;
    }

    ប្រសិនបើ (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        goto fail;
    }

    display = SDL_GetVideoDisplayForWindow(window);
    SDL_assert(display != NULL);
    SDL_assert(display->desktop_mode.internal != NULL);
    display_mode_data = display->desktop_mode.internal;

    // Create window buffer(s).
    ប្រសិនបើ (window->flags & SDL_WINDOW_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        ប្រសិនបើ (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            goto fail;
        }
    } បើមិនដូច្នេះ {
        numbufs = 1;
    }

    // Create buffer(s).
    ប្រសិនបើ (screen_create_window_buffers(impl->window, numbufs>0?numbufs:1) < 0) {
        goto fail;
    }

    // Initialize EGL surface.
    ប្រសិនបើ (window->flags & SDL_WINDOW_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
        ប្រសិនបើ (impl->egl_surface == EGL_NO_SURFACE) {
            goto fail;
        }
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    ប្រសិនបើ (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_mode_data->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_mode.format = screenToPixelFormat(format);
    display_mode_data->screen_format = format;

    display_data = display->internal;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_data != NULL);

    // Get initial focus state. Fallback to true.
    ប្រសិនបើ(screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } បើមិនដូច្នេះ {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_WINDOW_POINTER, impl->window);

    ត្រឡប់ true;

fail:
    ប្រសិនបើ (impl->window) {
        screen_destroy_window(impl->window);
    }
    ប្រសិនបើ (display_data) {
        SDL_free(display_data);
        display->internal = NULL;
    }

    SDL_free(impl);
    window->internal = NULL;
    ត្រឡប់ false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
static bool QNX_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format,
                        void ** pixels, ចំនួនគត់ *pitch)
{
    ចំនួនគត់              buffer_count;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t  *buffer;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);

    ប្រសិនបើ (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_COUNT, &buffer_count) < 0) {
        ត្រឡប់ false;
    }
    buffer = SDL_calloc(buffer_count, parimaa_na(screen_buffer_t));

    // Get a pointer to the buffer's memory.
    ប្រសិនបើ (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (void **)buffer) < 0) {
        ត្រឡប់ false;
    }

    ប្រសិនបើ (screen_get_buffer_property_pv(*buffer, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        ត្រឡប់ false;
    }

    // Set format and pitch.
    ប្រសិនបើ (screen_get_buffer_property_iv(*buffer, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        ត្រឡប់ false;
    }

    *format = display->desktop_mode.format;
    ត្រឡប់ true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
static bool QNX_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, const SDL_Rect *rects,
                        ចំនួនគត់ numrects)
{
    ចំនួនគត់ buffer_count, *rects_int;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t *buffer;

    ប្រសិនបើ (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_COUNT, &buffer_count) < 0) {
        ត្រឡប់ false;
    }
    buffer = SDL_calloc(buffer_count, parimaa_na(screen_buffer_t));

    ប្រសិនបើ (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (void **)buffer) < 0) {
        ត្រឡប់ false;
    }

    ប្រសិនបើ(numrects>0){
        rects_int = SDL_calloc(4*numrects, parimaa_na(ចំនួនគត់));

        សម្រាប់(ចំនួនគត់ i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        ប្រសិនបើ(screen_post_window(impl->window, buffer[0], numrects, rects_int, 0)) {
            ត្រឡប់ false;
        }
        ប្រសិនបើ(screen_flush_context(context, 0)) {
            ត្រឡប់ false;
        }
    }
    ត្រឡប់ true;
}

static SDL_FullscreenResult QNX_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *window_data = window->internal;
    ចំនួនគត់ size[2] = { 0, 0 };
    ចំនួនគត់ position[2] = { 0, 0 };

    ប្រសិនបើ (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        ត្រឡប់ SDL_FULLSCREEN_SUCCEEDED;
    }

    ប្រសិនបើ (fullscreen) {
        SDL_Rect bounds;

        ប្រសិនបើ (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            ត្រឡប់ SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        size[0] = bounds.w;
        size[1] = bounds.h;
    } បើមិនដូច្នេះ {
        position[0] = window->x;
        position[1] = window->y;
        size[0] = window->w;
        size[1] = window->h;
    }

    ប្រសិនបើ (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        ត្រឡប់ SDL_FULLSCREEN_FAILED;
    }

    ប្រសិនបើ (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        ត្រឡប់ SDL_FULLSCREEN_FAILED;
    }

    ប្រសិនបើ (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        ត្រឡប់ SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);

    ត្រឡប់ SDL_FULLSCREEN_SUCCEEDED;
}

static SDL_DisplayID QNX_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_WindowData  *impl = (SDL_WindowData *)window->internal;
    SDL_DisplayData *display_data;

    screen_display_t screen_display;

    ប្រសិនបើ (impl == NULL) {
        ត្រឡប់ 0;
    }

    ប្រសិនបើ (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_DISPLAY, (void **)&screen_display) < 0) {
        ត្រឡប់ 0;
    }

    សម្រាប់ (ចំនួនគត់ i = 0; i < _this->num_displays; i++) {
        display_data = _this->displays[i]->internal;
        ប្រសិនបើ (display_data && (display_data->screen_display == screen_display)) {
            ត្រឡប់ _this->displays[i]->id;
        }
    }

    ត្រឡប់ 0;
}

/**
 * Runs the main event loop.
 */
static void QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Window      *window;
    SDL_WindowData   *impl;
    ចំនួនគត់             type;
    ចំនួនគត់             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    សម្រាប់ (window = _this->windows; window; window = window->next) {
        impl = (SDL_WindowData *)window->internal;
        ប្រសិនបើ (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            continue;
        }
        has_focus = (bool)has_focus_i;

        ប្រសិនបើ (impl->has_focus != has_focus) {
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST), 0, 0);
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_MOUSE_ENTER : SDL_EVENT_WINDOW_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_SetMouseFocus(window);
            SDL_SetKeyboardFocus(window);
        }
    }

    សម្រាប់ (;;) {
        ប្រសិនបើ (screen_get_event(context, event, 0) < 0) {
            bha_nga;
        }

        ប្រសិនបើ (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            bha_nga;
        }

        ប្រសិនបើ (type == SCREEN_EVENT_NONE) {
            bha_nga;
        }

        switch (type) {
        pak_sa SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            bha_nga;

        pak_sa SCREEN_EVENT_POINTER:
            handlePointerEvent(event);
            bha_nga;

        default:
            bha_nga;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
static void QNX_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ចំនួនគត់             size[2];

    size[0] = window->pending.w;
    size[1] = window->pending.h;

    ប្រសិនបើ (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        ប្រសិនបើ (screen_destroy_window_buffers(impl->window) < 0) {
            ត្រឡប់;
        }
        impl->resize = true;

        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size);
        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size);

        screen_create_window_buffers(impl->window, (window->flags & SDL_WINDOW_OPENGL) ? 2 : 1);
    } បើមិនដូច្នេះ {
        window->last_size_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
static void QNX_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    const ចំនួនគត់       visible = 1;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
static void QNX_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    const ចំនួនគត់       visible = 0;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
static void QNX_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;

    ប្រសិនបើ (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_window(impl->window);
        window->internal = NULL;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
static void QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
static SDL_VideoDevice *createDevice(void)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, parimaa_na(SDL_VideoDevice));
    ប្រសិនបើ (!device) {
        ត្រឡប់ NULL;
    }

    device->internal = NULL;
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
#ប្រសិនបើ 0
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

    device->free = QNX_DeleteDevice;

    ត្រឡប់ device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    NULL, // no ShowMessageBox implementation
    false
};
