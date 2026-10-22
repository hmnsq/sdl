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

#ضمن "SDL_internal.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_egl_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "SDL_qnx.h"

#ضمن <errno.h>

ساكن screen_context_t context;
ساكن screen_event_t   event;
ساكن bool video_initialized = false;

screen_context_t * getContext()
{
    أرجع &context;
}

screen_event_t * getEvent()
{
    أرجع &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
ساكن bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_DisplayData      *display_data;
    SDL_DisplayMode      display_mode;
    SDL_DisplayModeData  *display_mode_data;

    صحيح size[2];
    صحيح index;
    صحيح display_كدي;
    صحيح active;

    screen_display_t *screen_display;

    إذا (video_initialized) {
        أرجع true;
    }

    إذا (screen_create_context(&context, 0) < 0) {
        أرجع false;
    }

    إذا (screen_create_event(&event) < 0) {
        أرجع false;
    }

    /* start with no displays and increment as attached displays are found */
    إذا (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_كدي, &display_كدي) < 0) {
        أرجع false;
    }

    screen_display = SDL_calloc(display_كدي, حجم(screen_display_t));
    إذا (screen_display == عدم) {
        أرجع false;
    }

    إذا (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (فراغ **)screen_display) < 0) {
        أرجع false;
    }

    /* create SDL displays based on display info from the screen API */
    لكل (index = 0; index < display_كدي; index++) {
        active = 0;
        إذا (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_ATTACHED, &active) < 0) {
            SDL_free(screen_display);
            أرجع false;
        }

        إذا (active) {
            display_data = (SDL_DisplayData *)SDL_calloc(1, حجم(SDL_DisplayData));
            إذا (display_data == عدم) {
                SDL_free(screen_display);
                أرجع false;
            }
            SDL_zerop(display_data);

            إذا (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_SIZE, size) < 0) {
                SDL_free(screen_display);
                SDL_free(display_data);
                أرجع false;
            }

            display_mode_data = (SDL_DisplayModeData *)SDL_calloc(1, حجم(SDL_DisplayModeData));
            إذا (display_mode_data == عدم) {
                SDL_free(screen_display);
                SDL_free(display_data);
                أرجع false;
            }
            SDL_zerop(display_mode_data);

            SDL_zero(display);
            SDL_zero(display_mode);

            display_data->screen_display = screen_display[index];
            display.internal = (فراغ *)display_data;

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

            إذا (!SDL_AddVideoDisplay(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_mode_data);
                SDL_free(display_data);
                أرجع false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, عدم);

    video_initialized = true;

    SDL_free(screen_display);

    أرجع true;
}

ساكن فراغ QNX_VideoQuit(SDL_VideoDevice *_this)
{
    إذا (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
ساكن bool QNX_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData       *impl;
    SDL_VideoDisplay     *display = عدم;
    SDL_DisplayData      *display_data = عدم;
    SDL_DisplayModeData  *display_mode_data = عدم;

    صحيح             size[2];
    صحيح             position[2];
    صحيح             numbufs;
    صحيح             format;
    صحيح             usage;
    صحيح             has_focus_i;

    impl = SDL_calloc(1, حجم(*impl));
    إذا (!impl) {
        أرجع false;
    }
    window->internal = impl;

    // Create a native window.
    إذا (screen_create_window(&impl->window, context) < 0) {
        اذهب fail;
    }

    // Set the native window's size to match the SDL window.
    size[0] = window->w;
    size[1] = window->h;
    position[0] = window->x;
    position[1] = window->y;

    إذا (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        اذهب fail;
    }

    إذا (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        اذهب fail;
    }

    إذا (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        اذهب fail;
    }

    display = SDL_GetVideoDisplayForWindow(window);
    SDL_assert(display != عدم);
    SDL_assert(display->desktop_mode.internal != عدم);
    display_mode_data = display->desktop_mode.internal;

    // Create window buffer(s).
    إذا (window->flags & SDL_WINDOW_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        إذا (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            اذهب fail;
        }
    } وإلا {
        numbufs = 1;
    }

    // Create buffer(s).
    إذا (screen_create_window_buffers(impl->window, numbufs>0?numbufs:1) < 0) {
        اذهب fail;
    }

    // Initialize EGL surface.
    إذا (window->flags & SDL_WINDOW_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
        إذا (impl->egl_surface == EGL_NO_SURFACE) {
            اذهب fail;
        }
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    إذا (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_mode_data->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_mode.format = screenToPixelFormat(format);
    display_mode_data->screen_format = format;

    display_data = display->internal;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_data != عدم);

    // Get initial focus state. Fallback to true.
    إذا(screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } وإلا {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_WINDOW_POINTER, impl->window);

    أرجع true;

fail:
    إذا (impl->window) {
        screen_destroy_window(impl->window);
    }
    إذا (display_data) {
        SDL_free(display_data);
        display->internal = عدم;
    }

    SDL_free(impl);
    window->internal = عدم;
    أرجع false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
ساكن bool QNX_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format,
                        فراغ ** pixels, صحيح *pitch)
{
    صحيح              buffer_كدي_2;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t  *buffer;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);

    إذا (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_كدي, &buffer_كدي_2) < 0) {
        أرجع false;
    }
    buffer = SDL_calloc(buffer_كدي_2, حجم(screen_buffer_t));

    // Get a pointer to the buffer's memory.
    إذا (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (فراغ **)buffer) < 0) {
        أرجع false;
    }

    إذا (screen_get_buffer_property_pv(*buffer, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        أرجع false;
    }

    // Set format and pitch.
    إذا (screen_get_buffer_property_iv(*buffer, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        أرجع false;
    }

    *format = display->desktop_mode.format;
    أرجع true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
ساكن bool QNX_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ثابت SDL_Rect *rects,
                        صحيح numrects)
{
    صحيح buffer_كدي_2, *rects_int;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t *buffer;

    إذا (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_كدي, &buffer_كدي_2) < 0) {
        أرجع false;
    }
    buffer = SDL_calloc(buffer_كدي_2, حجم(screen_buffer_t));

    إذا (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (فراغ **)buffer) < 0) {
        أرجع false;
    }

    إذا(numrects>0){
        rects_int = SDL_calloc(4*numrects, حجم(صحيح));

        لكل(صحيح i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        إذا(screen_post_window(impl->window, buffer[0], numrects, rects_int, 0)) {
            أرجع false;
        }
        إذا(screen_flush_context(context, 0)) {
            أرجع false;
        }
    }
    أرجع true;
}

ساكن SDL_FullscreenResult QNX_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *window_data = window->internal;
    صحيح size[2] = { 0, 0 };
    صحيح position[2] = { 0, 0 };

    إذا (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (fullscreen) {
        SDL_Rect bounds;

        إذا (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            أرجع SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        size[0] = bounds.w;
        size[1] = bounds.h;
    } وإلا {
        position[0] = window->x;
        position[1] = window->y;
        size[0] = window->w;
        size[1] = window->h;
    }

    إذا (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    إذا (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    إذا (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);

    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

ساكن SDL_DisplayID QNX_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_WindowData  *impl = (SDL_WindowData *)window->internal;
    SDL_DisplayData *display_data;

    screen_display_t screen_display;

    إذا (impl == عدم) {
        أرجع 0;
    }

    إذا (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_DISPLAY, (فراغ **)&screen_display) < 0) {
        أرجع 0;
    }

    لكل (صحيح i = 0; i < _this->لمب_displays; i++) {
        display_data = _this->displays[i]->internal;
        إذا (display_data && (display_data->screen_display == screen_display)) {
            أرجع _this->displays[i]->id;
        }
    }

    أرجع 0;
}

/**
 * Runs the main event loop.
 */
ساكن فراغ QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Window      *window;
    SDL_WindowData   *impl;
    صحيح             type;
    صحيح             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    لكل (window = _this->windows; window; window = window->next) {
        impl = (SDL_WindowData *)window->internal;
        إذا (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            استمر;
        }
        has_focus = (bool)has_focus_i;

        إذا (impl->has_focus != has_focus) {
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST), 0, 0);
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_MOUSE_ENTER : SDL_EVENT_WINDOW_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_SetMouseFocus(window);
            SDL_SetKeyboardFocus(window);
        }
    }

    لكل (;;) {
        إذا (screen_get_event(context, event, 0) < 0) {
            اكسر;
        }

        إذا (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            اكسر;
        }

        إذا (type == SCREEN_EVENT_NONE) {
            اكسر;
        }

        بدل (type) {
        حالة SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            اكسر;

        حالة SCREEN_EVENT_POINTER:
            handlePointerEvent(event);
            اكسر;

        افتراضي:
            اكسر;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
ساكن فراغ QNX_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    صحيح             size[2];

    size[0] = window->pending.w;
    size[1] = window->pending.h;

    إذا (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        إذا (screen_destroy_window_buffers(impl->window) < 0) {
            أرجع;
        }
        impl->resize = true;

        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size);
        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size);

        screen_create_window_buffers(impl->window, (window->flags & SDL_WINDOW_OPENGL) ? 2 : 1);
    } وإلا {
        window->last_size_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
ساكن فراغ QNX_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ثابت صحيح       visible = 1;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
ساكن فراغ QNX_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ثابت صحيح       visible = 0;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
ساكن فراغ QNX_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;

    إذا (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_window(impl->window);
        window->internal = عدم;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
ساكن فراغ QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
ساكن SDL_VideoDevice *createDevice(فراغ)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    device->internal = عدم;
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
#إذا 0
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

    device->حرر = QNX_DeleteDevice;

    أرجع device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    عدم, // no ShowMessageBox implementation
    false
};
