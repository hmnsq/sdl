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

#شامل "SDL_internal.h"
#شامل "../SDL_sysvideo.h"
#شامل "../SDL_egl_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_windowevents_c.h"
#شامل "SDL_qnx.h"

#شامل <errno.h>

ایستا screen_context_t context;
ایستا screen_event_t   event;
ایستا bool video_initialized = false;

screen_context_t * getContext()
{
    بازگشت &context;
}

screen_event_t * getEvent()
{
    بازگشت &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
ایستا bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_DisplayData      *display_data;
    SDL_DisplayMode      display_mode;
    SDL_DisplayModeData  *display_mode_data;

    صحیح size[2];
    صحیح index;
    صحیح display_شمار;
    صحیح active;

    screen_display_t *screen_display;

    اگر (video_initialized) {
        بازگشت true;
    }

    اگر (screen_create_context(&context, 0) < 0) {
        بازگشت false;
    }

    اگر (screen_create_event(&event) < 0) {
        بازگشت false;
    }

    /* start with no displays and increment as attached displays are found */
    اگر (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_شمار, &display_شمار) < 0) {
        بازگشت false;
    }

    screen_display = SDL_calloc(display_شمار, اندازه(screen_display_t));
    اگر (screen_display == پوچ) {
        بازگشت false;
    }

    اگر (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (تهی **)screen_display) < 0) {
        بازگشت false;
    }

    /* create SDL displays based on display info from the screen API */
    برای (index = 0; index < display_شمار; index++) {
        active = 0;
        اگر (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_ATTACHED, &active) < 0) {
            SDL_free(screen_display);
            بازگشت false;
        }

        اگر (active) {
            display_data = (SDL_DisplayData *)SDL_calloc(1, اندازه(SDL_DisplayData));
            اگر (display_data == پوچ) {
                SDL_free(screen_display);
                بازگشت false;
            }
            SDL_zerop(display_data);

            اگر (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_SIZE, size) < 0) {
                SDL_free(screen_display);
                SDL_free(display_data);
                بازگشت false;
            }

            display_mode_data = (SDL_DisplayModeData *)SDL_calloc(1, اندازه(SDL_DisplayModeData));
            اگر (display_mode_data == پوچ) {
                SDL_free(screen_display);
                SDL_free(display_data);
                بازگشت false;
            }
            SDL_zerop(display_mode_data);

            SDL_zero(display);
            SDL_zero(display_mode);

            display_data->screen_display = screen_display[index];
            display.internal = (تهی *)display_data;

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

            اگر (!SDL_AddVideoDisplay(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_mode_data);
                SDL_free(display_data);
                بازگشت false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, پوچ);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, پوچ);

    video_initialized = true;

    SDL_free(screen_display);

    بازگشت true;
}

ایستا تهی QNX_VideoQuit(SDL_VideoDevice *_this)
{
    اگر (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
ایستا bool QNX_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData       *impl;
    SDL_VideoDisplay     *display = پوچ;
    SDL_DisplayData      *display_data = پوچ;
    SDL_DisplayModeData  *display_mode_data = پوچ;

    صحیح             size[2];
    صحیح             position[2];
    صحیح             numbufs;
    صحیح             format;
    صحیح             usage;
    صحیح             has_focus_i;

    impl = SDL_calloc(1, اندازه(*impl));
    اگر (!impl) {
        بازگشت false;
    }
    window->internal = impl;

    // Create a native window.
    اگر (screen_create_window(&impl->window, context) < 0) {
        برو fail;
    }

    // Set the native window's size to match the SDL window.
    size[0] = window->w;
    size[1] = window->h;
    position[0] = window->x;
    position[1] = window->y;

    اگر (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        برو fail;
    }

    اگر (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        برو fail;
    }

    اگر (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        برو fail;
    }

    display = SDL_GetVideoDisplayForWindow(window);
    SDL_assert(display != پوچ);
    SDL_assert(display->desktop_mode.internal != پوچ);
    display_mode_data = display->desktop_mode.internal;

    // Create window buffer(s).
    اگر (window->flags & SDL_WINDOW_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        اگر (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            برو fail;
        }
    } وگرنه {
        numbufs = 1;
    }

    // Create buffer(s).
    اگر (screen_create_window_buffers(impl->window, numbufs>0?numbufs:1) < 0) {
        برو fail;
    }

    // Initialize EGL surface.
    اگر (window->flags & SDL_WINDOW_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
        اگر (impl->egl_surface == EGL_NO_SURFACE) {
            برو fail;
        }
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    اگر (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_mode_data->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_mode.format = screenToPixelFormat(format);
    display_mode_data->screen_format = format;

    display_data = display->internal;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_data != پوچ);

    // Get initial focus state. Fallback to true.
    اگر(screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } وگرنه {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_WINDOW_POINTER, impl->window);

    بازگشت true;

fail:
    اگر (impl->window) {
        screen_destroy_window(impl->window);
    }
    اگر (display_data) {
        SDL_free(display_data);
        display->internal = پوچ;
    }

    SDL_free(impl);
    window->internal = پوچ;
    بازگشت false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
ایستا bool QNX_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format,
                        تهی ** pixels, صحیح *pitch)
{
    صحیح              buffer_شمار_2;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t  *buffer;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);

    اگر (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_شمار, &buffer_شمار_2) < 0) {
        بازگشت false;
    }
    buffer = SDL_calloc(buffer_شمار_2, اندازه(screen_buffer_t));

    // Get a pointer to the buffer's memory.
    اگر (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (تهی **)buffer) < 0) {
        بازگشت false;
    }

    اگر (screen_get_buffer_property_pv(*buffer, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        بازگشت false;
    }

    // Set format and pitch.
    اگر (screen_get_buffer_property_iv(*buffer, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        بازگشت false;
    }

    *format = display->desktop_mode.format;
    بازگشت true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
ایستا bool QNX_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ثابت SDL_Rect *rects,
                        صحیح numrects)
{
    صحیح buffer_شمار_2, *rects_int;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t *buffer;

    اگر (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_شمار, &buffer_شمار_2) < 0) {
        بازگشت false;
    }
    buffer = SDL_calloc(buffer_شمار_2, اندازه(screen_buffer_t));

    اگر (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (تهی **)buffer) < 0) {
        بازگشت false;
    }

    اگر(numrects>0){
        rects_int = SDL_calloc(4*numrects, اندازه(صحیح));

        برای(صحیح i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        اگر(screen_post_window(impl->window, buffer[0], numrects, rects_int, 0)) {
            بازگشت false;
        }
        اگر(screen_flush_context(context, 0)) {
            بازگشت false;
        }
    }
    بازگشت true;
}

ایستا SDL_FullscreenResult QNX_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *window_data = window->internal;
    صحیح size[2] = { 0, 0 };
    صحیح position[2] = { 0, 0 };

    اگر (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        بازگشت SDL_FULLSCREEN_SUCCEEDED;
    }

    اگر (fullscreen) {
        SDL_Rect bounds;

        اگر (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            بازگشت SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        size[0] = bounds.w;
        size[1] = bounds.h;
    } وگرنه {
        position[0] = window->x;
        position[1] = window->y;
        size[0] = window->w;
        size[1] = window->h;
    }

    اگر (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        بازگشت SDL_FULLSCREEN_FAILED;
    }

    اگر (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        بازگشت SDL_FULLSCREEN_FAILED;
    }

    اگر (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        بازگشت SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);

    بازگشت SDL_FULLSCREEN_SUCCEEDED;
}

ایستا SDL_DisplayID QNX_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_WindowData  *impl = (SDL_WindowData *)window->internal;
    SDL_DisplayData *display_data;

    screen_display_t screen_display;

    اگر (impl == پوچ) {
        بازگشت 0;
    }

    اگر (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_DISPLAY, (تهی **)&screen_display) < 0) {
        بازگشت 0;
    }

    برای (صحیح i = 0; i < _this->رقم_displays; i++) {
        display_data = _this->displays[i]->internal;
        اگر (display_data && (display_data->screen_display == screen_display)) {
            بازگشت _this->displays[i]->id;
        }
    }

    بازگشت 0;
}

/**
 * Runs the main event loop.
 */
ایستا تهی QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Window      *window;
    SDL_WindowData   *impl;
    صحیح             type;
    صحیح             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    برای (window = _this->windows; window; window = window->next) {
        impl = (SDL_WindowData *)window->internal;
        اگر (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            ادامه;
        }
        has_focus = (bool)has_focus_i;

        اگر (impl->has_focus != has_focus) {
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST), 0, 0);
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_MOUSE_ENTER : SDL_EVENT_WINDOW_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_SetMouseFocus(window);
            SDL_SetKeyboardFocus(window);
        }
    }

    برای (;;) {
        اگر (screen_get_event(context, event, 0) < 0) {
            بشکن;
        }

        اگر (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            بشکن;
        }

        اگر (type == SCREEN_EVENT_NONE) {
            بشکن;
        }

        انتخاب (type) {
        حالت SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            بشکن;

        حالت SCREEN_EVENT_POINTER:
            handlePointerEvent(event);
            بشکن;

        پیشفرض:
            بشکن;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
ایستا تهی QNX_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    صحیح             size[2];

    size[0] = window->pending.w;
    size[1] = window->pending.h;

    اگر (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        اگر (screen_destroy_window_buffers(impl->window) < 0) {
            بازگشت;
        }
        impl->resize = true;

        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size);
        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size);

        screen_create_window_buffers(impl->window, (window->flags & SDL_WINDOW_OPENGL) ? 2 : 1);
    } وگرنه {
        window->last_size_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
ایستا تهی QNX_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ثابت صحیح       visible = 1;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
ایستا تهی QNX_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ثابت صحیح       visible = 0;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
ایستا تهی QNX_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;

    اگر (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_window(impl->window);
        window->internal = پوچ;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
ایستا تهی QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
ایستا SDL_VideoDevice *createDevice(تهی)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, اندازه(SDL_VideoDevice));
    اگر (!device) {
        بازگشت پوچ;
    }

    device->internal = پوچ;
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
#اگر 0
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

    device->آزاد = QNX_DeleteDevice;

    بازگشت device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    پوچ, // no ShowMessageBox implementation
    false
};
