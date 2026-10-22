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

#અન્તર્ભાવ "SDL_internal.h"
#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "../SDL_egl_c.h"
#અન્તર્ભાવ "../../events/SDL_keyboard_c.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"
#અન્તર્ભાવ "../../events/SDL_windowevents_c.h"
#અન્તર્ભાવ "SDL_qnx.h"

#અન્તર્ભાવ <errno.h>

સ્થિર screen_context_t context;
સ્થિર screen_event_t   event;
સ્થિર bool video_initialized = false;

screen_context_t * getContext()
{
    પાછા &context;
}

screen_event_t * getEvent()
{
    પાછા &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
સ્થિર bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_DisplayData      *display_data;
    SDL_DisplayMode      display_mode;
    SDL_DisplayModeData  *display_mode_data;

    પૂર્ણાંક size[2];
    પૂર્ણાંક index;
    પૂર્ણાંક display_ગણતરી;
    પૂર્ણાંક active;

    screen_display_t *screen_display;

    જો (video_initialized) {
        પાછા true;
    }

    જો (screen_create_context(&context, 0) < 0) {
        પાછા false;
    }

    જો (screen_create_event(&event) < 0) {
        પાછા false;
    }

    /* start with no displays and increment as attached displays are found */
    જો (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_ગણતરી, &display_ગણતરી) < 0) {
        પાછા false;
    }

    screen_display = SDL_calloc(display_ગણતરી, કદ(screen_display_t));
    જો (screen_display == ખાલી) {
        પાછા false;
    }

    જો (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (શૂન્ય **)screen_display) < 0) {
        પાછા false;
    }

    /* create SDL displays based on display info from the screen API */
    માટે (index = 0; index < display_ગણતરી; index++) {
        active = 0;
        જો (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_ATTACHED, &active) < 0) {
            SDL_free(screen_display);
            પાછા false;
        }

        જો (active) {
            display_data = (SDL_DisplayData *)SDL_calloc(1, કદ(SDL_DisplayData));
            જો (display_data == ખાલી) {
                SDL_free(screen_display);
                પાછા false;
            }
            SDL_zerop(display_data);

            જો (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_SIZE, size) < 0) {
                SDL_free(screen_display);
                SDL_free(display_data);
                પાછા false;
            }

            display_mode_data = (SDL_DisplayModeData *)SDL_calloc(1, કદ(SDL_DisplayModeData));
            જો (display_mode_data == ખાલી) {
                SDL_free(screen_display);
                SDL_free(display_data);
                પાછા false;
            }
            SDL_zerop(display_mode_data);

            SDL_zero(display);
            SDL_zero(display_mode);

            display_data->screen_display = screen_display[index];
            display.internal = (શૂન્ય *)display_data;

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

            જો (!SDL_AddVideoDisplay(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_mode_data);
                SDL_free(display_data);
                પાછા false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ખાલી);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ખાલી);

    video_initialized = true;

    SDL_free(screen_display);

    પાછા true;
}

સ્થિર શૂન્ય QNX_VideoQuit(SDL_VideoDevice *_this)
{
    જો (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
સ્થિર bool QNX_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData       *impl;
    SDL_VideoDisplay     *display = ખાલી;
    SDL_DisplayData      *display_data = ખાલી;
    SDL_DisplayModeData  *display_mode_data = ખાલી;

    પૂર્ણાંક             size[2];
    પૂર્ણાંક             position[2];
    પૂર્ણાંક             numbufs;
    પૂર્ણાંક             format;
    પૂર્ણાંક             usage;
    પૂર્ણાંક             has_focus_i;

    impl = SDL_calloc(1, કદ(*impl));
    જો (!impl) {
        પાછા false;
    }
    window->internal = impl;

    // Create a native window.
    જો (screen_create_window(&impl->window, context) < 0) {
        જાઓ fail;
    }

    // Set the native window's size to match the SDL window.
    size[0] = window->w;
    size[1] = window->h;
    position[0] = window->x;
    position[1] = window->y;

    જો (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        જાઓ fail;
    }

    જો (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        જાઓ fail;
    }

    જો (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        જાઓ fail;
    }

    display = SDL_GetVideoDisplayForWindow(window);
    SDL_assert(display != ખાલી);
    SDL_assert(display->desktop_mode.internal != ખાલી);
    display_mode_data = display->desktop_mode.internal;

    // Create window buffer(s).
    જો (window->flags & SDL_WINDOW_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        જો (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            જાઓ fail;
        }
    } નહીંતર {
        numbufs = 1;
    }

    // Create buffer(s).
    જો (screen_create_window_buffers(impl->window, numbufs>0?numbufs:1) < 0) {
        જાઓ fail;
    }

    // Initialize EGL surface.
    જો (window->flags & SDL_WINDOW_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
        જો (impl->egl_surface == EGL_NO_SURFACE) {
            જાઓ fail;
        }
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    જો (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_mode_data->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_mode.format = screenToPixelFormat(format);
    display_mode_data->screen_format = format;

    display_data = display->internal;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_data != ખાલી);

    // Get initial focus state. Fallback to true.
    જો(screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } નહીંતર {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_WINDOW_POINTER, impl->window);

    પાછા true;

fail:
    જો (impl->window) {
        screen_destroy_window(impl->window);
    }
    જો (display_data) {
        SDL_free(display_data);
        display->internal = ખાલી;
    }

    SDL_free(impl);
    window->internal = ખાલી;
    પાછા false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
સ્થિર bool QNX_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format,
                        શૂન્ય ** pixels, પૂર્ણાંક *pitch)
{
    પૂર્ણાંક              buffer_ગણતરી_2;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t  *buffer;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);

    જો (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_ગણતરી, &buffer_ગણતરી_2) < 0) {
        પાછા false;
    }
    buffer = SDL_calloc(buffer_ગણતરી_2, કદ(screen_buffer_t));

    // Get a pointer to the buffer's memory.
    જો (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (શૂન્ય **)buffer) < 0) {
        પાછા false;
    }

    જો (screen_get_buffer_property_pv(*buffer, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        પાછા false;
    }

    // Set format and pitch.
    જો (screen_get_buffer_property_iv(*buffer, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        પાછા false;
    }

    *format = display->desktop_mode.format;
    પાછા true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
સ્થિર bool QNX_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, અચલ SDL_Rect *rects,
                        પૂર્ણાંક numrects)
{
    પૂર્ણાંક buffer_ગણતરી_2, *rects_int;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t *buffer;

    જો (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_ગણતરી, &buffer_ગણતરી_2) < 0) {
        પાછા false;
    }
    buffer = SDL_calloc(buffer_ગણતરી_2, કદ(screen_buffer_t));

    જો (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (શૂન્ય **)buffer) < 0) {
        પાછા false;
    }

    જો(numrects>0){
        rects_int = SDL_calloc(4*numrects, કદ(પૂર્ણાંક));

        માટે(પૂર્ણાંક i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        જો(screen_post_window(impl->window, buffer[0], numrects, rects_int, 0)) {
            પાછા false;
        }
        જો(screen_flush_context(context, 0)) {
            પાછા false;
        }
    }
    પાછા true;
}

સ્થિર SDL_FullscreenResult QNX_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *window_data = window->internal;
    પૂર્ણાંક size[2] = { 0, 0 };
    પૂર્ણાંક position[2] = { 0, 0 };

    જો (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        પાછા SDL_FULLSCREEN_SUCCEEDED;
    }

    જો (fullscreen) {
        SDL_Rect bounds;

        જો (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            પાછા SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        size[0] = bounds.w;
        size[1] = bounds.h;
    } નહીંતર {
        position[0] = window->x;
        position[1] = window->y;
        size[0] = window->w;
        size[1] = window->h;
    }

    જો (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        પાછા SDL_FULLSCREEN_FAILED;
    }

    જો (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        પાછા SDL_FULLSCREEN_FAILED;
    }

    જો (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        પાછા SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);

    પાછા SDL_FULLSCREEN_SUCCEEDED;
}

સ્થિર SDL_DisplayID QNX_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_WindowData  *impl = (SDL_WindowData *)window->internal;
    SDL_DisplayData *display_data;

    screen_display_t screen_display;

    જો (impl == ખાલી) {
        પાછા 0;
    }

    જો (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_DISPLAY, (શૂન્ય **)&screen_display) < 0) {
        પાછા 0;
    }

    માટે (પૂર્ણાંક i = 0; i < _this->અંક_displays; i++) {
        display_data = _this->displays[i]->internal;
        જો (display_data && (display_data->screen_display == screen_display)) {
            પાછા _this->displays[i]->id;
        }
    }

    પાછા 0;
}

/**
 * Runs the main event loop.
 */
સ્થિર શૂન્ય QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Window      *window;
    SDL_WindowData   *impl;
    પૂર્ણાંક             type;
    પૂર્ણાંક             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    માટે (window = _this->windows; window; window = window->next) {
        impl = (SDL_WindowData *)window->internal;
        જો (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            ચાલુ;
        }
        has_focus = (bool)has_focus_i;

        જો (impl->has_focus != has_focus) {
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST), 0, 0);
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_MOUSE_ENTER : SDL_EVENT_WINDOW_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_SetMouseFocus(window);
            SDL_SetKeyboardFocus(window);
        }
    }

    માટે (;;) {
        જો (screen_get_event(context, event, 0) < 0) {
            તોડો;
        }

        જો (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            તોડો;
        }

        જો (type == SCREEN_EVENT_NONE) {
            તોડો;
        }

        પસંદગી (type) {
        સ્થિતિ SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            તોડો;

        સ્થિતિ SCREEN_EVENT_POINTER:
            handlePointerEvent(event);
            તોડો;

        મૂળભૂત:
            તોડો;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
સ્થિર શૂન્ય QNX_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    પૂર્ણાંક             size[2];

    size[0] = window->pending.w;
    size[1] = window->pending.h;

    જો (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        જો (screen_destroy_window_buffers(impl->window) < 0) {
            પાછા;
        }
        impl->resize = true;

        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size);
        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size);

        screen_create_window_buffers(impl->window, (window->flags & SDL_WINDOW_OPENGL) ? 2 : 1);
    } નહીંતર {
        window->last_size_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
સ્થિર શૂન્ય QNX_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    અચલ પૂર્ણાંક       visible = 1;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
સ્થિર શૂન્ય QNX_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    અચલ પૂર્ણાંક       visible = 0;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
સ્થિર શૂન્ય QNX_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;

    જો (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_window(impl->window);
        window->internal = ખાલી;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
સ્થિર શૂન્ય QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
સ્થિર SDL_VideoDevice *createDevice(શૂન્ય)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, કદ(SDL_VideoDevice));
    જો (!device) {
        પાછા ખાલી;
    }

    device->internal = ખાલી;
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
#જો 0
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

    device->મુક્ત = QNX_DeleteDevice;

    પાછા device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    ખાલી, // no ShowMessageBox implementation
    false
};
