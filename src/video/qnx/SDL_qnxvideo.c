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

#অন্তর্ভাৱ "SDL_internal.h"
#অন্তর্ভাৱ "../SDL_sysvideo.h"
#অন্তর্ভাৱ "../SDL_egl_c.h"
#অন্তর্ভাৱ "../../events/SDL_keyboard_c.h"
#অন্তর্ভাৱ "../../events/SDL_mouse_c.h"
#অন্তর্ভাৱ "../../events/SDL_windowevents_c.h"
#অন্তর্ভাৱ "SDL_qnx.h"

#অন্তর্ভাৱ <errno.h>

স্থির screen_context_t context;
স্থির screen_event_t   event;
স্থির bool video_initialized = false;

screen_context_t * getContext()
{
    ঘূৰাই &context;
}

screen_event_t * getEvent()
{
    ঘূৰাই &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
স্থির bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_DisplayData      *display_data;
    SDL_DisplayMode      display_mode;
    SDL_DisplayModeData  *display_mode_data;

    পূর্ণাঙ্ক size[2];
    পূর্ণাঙ্ক index;
    পূর্ণাঙ্ক display_গুনতি;
    পূর্ণাঙ্ক active;

    screen_display_t *screen_display;

    যদি (video_initialized) {
        ঘূৰাই true;
    }

    যদি (screen_create_context(&context, 0) < 0) {
        ঘূৰাই false;
    }

    যদি (screen_create_event(&event) < 0) {
        ঘূৰাই false;
    }

    /* start with no displays and increment as attached displays are found */
    যদি (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_গুনতি, &display_গুনতি) < 0) {
        ঘূৰাই false;
    }

    screen_display = SDL_calloc(display_গুনতি, পরিমাণ(screen_display_t));
    যদি (screen_display == রিক্ত) {
        ঘূৰাই false;
    }

    যদি (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (শূন্য **)screen_display) < 0) {
        ঘূৰাই false;
    }

    /* create SDL displays based on display info from the screen API */
    বাবে (index = 0; index < display_গুনতি; index++) {
        active = 0;
        যদি (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_ATTACHED, &active) < 0) {
            SDL_free(screen_display);
            ঘূৰাই false;
        }

        যদি (active) {
            display_data = (SDL_DisplayData *)SDL_calloc(1, পরিমাণ(SDL_DisplayData));
            যদি (display_data == রিক্ত) {
                SDL_free(screen_display);
                ঘূৰাই false;
            }
            SDL_zerop(display_data);

            যদি (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_SIZE, size) < 0) {
                SDL_free(screen_display);
                SDL_free(display_data);
                ঘূৰাই false;
            }

            display_mode_data = (SDL_DisplayModeData *)SDL_calloc(1, পরিমাণ(SDL_DisplayModeData));
            যদি (display_mode_data == রিক্ত) {
                SDL_free(screen_display);
                SDL_free(display_data);
                ঘূৰাই false;
            }
            SDL_zerop(display_mode_data);

            SDL_zero(display);
            SDL_zero(display_mode);

            display_data->screen_display = screen_display[index];
            display.internal = (শূন্য *)display_data;

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

            যদি (!SDL_AddVideoDisplay(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_mode_data);
                SDL_free(display_data);
                ঘূৰাই false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, রিক্ত);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, রিক্ত);

    video_initialized = true;

    SDL_free(screen_display);

    ঘূৰাই true;
}

স্থির শূন্য QNX_VideoQuit(SDL_VideoDevice *_this)
{
    যদি (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
স্থির bool QNX_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData       *impl;
    SDL_VideoDisplay     *display = রিক্ত;
    SDL_DisplayData      *display_data = রিক্ত;
    SDL_DisplayModeData  *display_mode_data = রিক্ত;

    পূর্ণাঙ্ক             size[2];
    পূর্ণাঙ্ক             position[2];
    পূর্ণাঙ্ক             numbufs;
    পূর্ণাঙ্ক             format;
    পূর্ণাঙ্ক             usage;
    পূর্ণাঙ্ক             has_focus_i;

    impl = SDL_calloc(1, পরিমাণ(*impl));
    যদি (!impl) {
        ঘূৰাই false;
    }
    window->internal = impl;

    // Create a native window.
    যদি (screen_create_window(&impl->window, context) < 0) {
        গচ্ছ fail;
    }

    // Set the native window's size to match the SDL window.
    size[0] = window->w;
    size[1] = window->h;
    position[0] = window->x;
    position[1] = window->y;

    যদি (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        গচ্ছ fail;
    }

    যদি (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        গচ্ছ fail;
    }

    যদি (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        গচ্ছ fail;
    }

    display = SDL_GetVideoDisplayForWindow(window);
    SDL_assert(display != রিক্ত);
    SDL_assert(display->desktop_mode.internal != রিক্ত);
    display_mode_data = display->desktop_mode.internal;

    // Create window buffer(s).
    যদি (window->flags & SDL_WINDOW_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        যদি (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            গচ্ছ fail;
        }
    } অন্যথা {
        numbufs = 1;
    }

    // Create buffer(s).
    যদি (screen_create_window_buffers(impl->window, numbufs>0?numbufs:1) < 0) {
        গচ্ছ fail;
    }

    // Initialize EGL surface.
    যদি (window->flags & SDL_WINDOW_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
        যদি (impl->egl_surface == EGL_NO_SURFACE) {
            গচ্ছ fail;
        }
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    যদি (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_mode_data->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_mode.format = screenToPixelFormat(format);
    display_mode_data->screen_format = format;

    display_data = display->internal;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_data != রিক্ত);

    // Get initial focus state. Fallback to true.
    যদি(screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } অন্যথা {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_WINDOW_POINTER, impl->window);

    ঘূৰাই true;

fail:
    যদি (impl->window) {
        screen_destroy_window(impl->window);
    }
    যদি (display_data) {
        SDL_free(display_data);
        display->internal = রিক্ত;
    }

    SDL_free(impl);
    window->internal = রিক্ত;
    ঘূৰাই false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
স্থির bool QNX_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format,
                        শূন্য ** pixels, পূর্ণাঙ্ক *pitch)
{
    পূর্ণাঙ্ক              buffer_গুনতি_2;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t  *buffer;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);

    যদি (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_গুনতি, &buffer_গুনতি_2) < 0) {
        ঘূৰাই false;
    }
    buffer = SDL_calloc(buffer_গুনতি_2, পরিমাণ(screen_buffer_t));

    // Get a pointer to the buffer's memory.
    যদি (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (শূন্য **)buffer) < 0) {
        ঘূৰাই false;
    }

    যদি (screen_get_buffer_property_pv(*buffer, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        ঘূৰাই false;
    }

    // Set format and pitch.
    যদি (screen_get_buffer_property_iv(*buffer, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        ঘূৰাই false;
    }

    *format = display->desktop_mode.format;
    ঘূৰাই true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
স্থির bool QNX_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুৱ SDL_Rect *rects,
                        পূর্ণাঙ্ক numrects)
{
    পূর্ণাঙ্ক buffer_গুনতি_2, *rects_int;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t *buffer;

    যদি (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_গুনতি, &buffer_গুনতি_2) < 0) {
        ঘূৰাই false;
    }
    buffer = SDL_calloc(buffer_গুনতি_2, পরিমাণ(screen_buffer_t));

    যদি (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (শূন্য **)buffer) < 0) {
        ঘূৰাই false;
    }

    যদি(numrects>0){
        rects_int = SDL_calloc(4*numrects, পরিমাণ(পূর্ণাঙ্ক));

        বাবে(পূর্ণাঙ্ক i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        যদি(screen_post_window(impl->window, buffer[0], numrects, rects_int, 0)) {
            ঘূৰাই false;
        }
        যদি(screen_flush_context(context, 0)) {
            ঘূৰাই false;
        }
    }
    ঘূৰাই true;
}

স্থির SDL_FullscreenResult QNX_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *window_data = window->internal;
    পূর্ণাঙ্ক size[2] = { 0, 0 };
    পূর্ণাঙ্ক position[2] = { 0, 0 };

    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        ঘূৰাই SDL_FULLSCREEN_SUCCEEDED;
    }

    যদি (fullscreen) {
        SDL_Rect bounds;

        যদি (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            ঘূৰাই SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        size[0] = bounds.w;
        size[1] = bounds.h;
    } অন্যথা {
        position[0] = window->x;
        position[1] = window->y;
        size[0] = window->w;
        size[1] = window->h;
    }

    যদি (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        ঘূৰাই SDL_FULLSCREEN_FAILED;
    }

    যদি (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        ঘূৰাই SDL_FULLSCREEN_FAILED;
    }

    যদি (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        ঘূৰাই SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);

    ঘূৰাই SDL_FULLSCREEN_SUCCEEDED;
}

স্থির SDL_DisplayID QNX_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_WindowData  *impl = (SDL_WindowData *)window->internal;
    SDL_DisplayData *display_data;

    screen_display_t screen_display;

    যদি (impl == রিক্ত) {
        ঘূৰাই 0;
    }

    যদি (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_DISPLAY, (শূন্য **)&screen_display) < 0) {
        ঘূৰাই 0;
    }

    বাবে (পূর্ণাঙ্ক i = 0; i < _this->অঙ্ক_displays; i++) {
        display_data = _this->displays[i]->internal;
        যদি (display_data && (display_data->screen_display == screen_display)) {
            ঘূৰাই _this->displays[i]->id;
        }
    }

    ঘূৰাই 0;
}

/**
 * Runs the main event loop.
 */
স্থির শূন্য QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Window      *window;
    SDL_WindowData   *impl;
    পূর্ণাঙ্ক             type;
    পূর্ণাঙ্ক             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    বাবে (window = _this->windows; window; window = window->next) {
        impl = (SDL_WindowData *)window->internal;
        যদি (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            অনুৱর্ত;
        }
        has_focus = (bool)has_focus_i;

        যদি (impl->has_focus != has_focus) {
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST), 0, 0);
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_MOUSE_ENTER : SDL_EVENT_WINDOW_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_SetMouseFocus(window);
            SDL_SetKeyboardFocus(window);
        }
    }

    বাবে (;;) {
        যদি (screen_get_event(context, event, 0) < 0) {
            ভঙ্গ;
        }

        যদি (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            ভঙ্গ;
        }

        যদি (type == SCREEN_EVENT_NONE) {
            ভঙ্গ;
        }

        ৱিকল্প (type) {
        পক্ষ SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            ভঙ্গ;

        পক্ষ SCREEN_EVENT_POINTER:
            handlePointerEvent(event);
            ভঙ্গ;

        স্ৱভাৱ:
            ভঙ্গ;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
স্থির শূন্য QNX_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    পূর্ণাঙ্ক             size[2];

    size[0] = window->pending.w;
    size[1] = window->pending.h;

    যদি (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        যদি (screen_destroy_window_buffers(impl->window) < 0) {
            ঘূৰাই;
        }
        impl->resize = true;

        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size);
        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size);

        screen_create_window_buffers(impl->window, (window->flags & SDL_WINDOW_OPENGL) ? 2 : 1);
    } অন্যথা {
        window->last_size_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
স্থির শূন্য QNX_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ধ্রুৱ পূর্ণাঙ্ক       visible = 1;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
স্থির শূন্য QNX_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ধ্রুৱ পূর্ণাঙ্ক       visible = 0;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
স্থির শূন্য QNX_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;

    যদি (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_window(impl->window);
        window->internal = রিক্ত;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
স্থির শূন্য QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
স্থির SDL_VideoDevice *createDevice(শূন্য)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, পরিমাণ(SDL_VideoDevice));
    যদি (!device) {
        ঘূৰাই রিক্ত;
    }

    device->internal = রিক্ত;
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
#যদি 0
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

    device->মুক্ত = QNX_DeleteDevice;

    ঘূৰাই device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    রিক্ত, // no ShowMessageBox implementation
    false
};
