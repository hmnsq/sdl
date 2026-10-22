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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_egl_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keyboard_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_windowevents_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_qnx.h"

#ଅନ୍ତର୍ଭାଵ <errno.h>

ସ୍ଥିର screen_context_t context;
ସ୍ଥିର screen_event_t   event;
ସ୍ଥିର bool video_initialized = false;

screen_context_t * getContext()
{
    ଫେରନ୍ତୁ &context;
}

screen_event_t * getEvent()
{
    ଫେରନ୍ତୁ &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
ସ୍ଥିର bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_DisplayData      *display_data;
    SDL_DisplayMode      display_mode;
    SDL_DisplayModeData  *display_mode_data;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା size[2];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା index;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା display_ଗଣନା;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା active;

    screen_display_t *screen_display;

    ଯଦି (video_initialized) {
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (screen_create_context(&context, 0) < 0) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (screen_create_event(&event) < 0) {
        ଫେରନ୍ତୁ false;
    }

    /* start with no displays and increment as attached displays are found */
    ଯଦି (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_ଗଣନା, &display_ଗଣନା) < 0) {
        ଫେରନ୍ତୁ false;
    }

    screen_display = SDL_calloc(display_ଗଣନା, ଆକାର(screen_display_t));
    ଯଦି (screen_display == ଖାଲି) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (ଶୂନ୍ୟ **)screen_display) < 0) {
        ଫେରନ୍ତୁ false;
    }

    /* create SDL displays based on display info from the screen API */
    ପାଇଁ (index = 0; index < display_ଗଣନା; index++) {
        active = 0;
        ଯଦି (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_ATTACHED, &active) < 0) {
            SDL_free(screen_display);
            ଫେରନ୍ତୁ false;
        }

        ଯଦି (active) {
            display_data = (SDL_DisplayData *)SDL_calloc(1, ଆକାର(SDL_DisplayData));
            ଯଦି (display_data == ଖାଲି) {
                SDL_free(screen_display);
                ଫେରନ୍ତୁ false;
            }
            SDL_zerop(display_data);

            ଯଦି (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_SIZE, size) < 0) {
                SDL_free(screen_display);
                SDL_free(display_data);
                ଫେରନ୍ତୁ false;
            }

            display_mode_data = (SDL_DisplayModeData *)SDL_calloc(1, ଆକାର(SDL_DisplayModeData));
            ଯଦି (display_mode_data == ଖାଲି) {
                SDL_free(screen_display);
                SDL_free(display_data);
                ଫେରନ୍ତୁ false;
            }
            SDL_zerop(display_mode_data);

            SDL_zero(display);
            SDL_zero(display_mode);

            display_data->screen_display = screen_display[index];
            display.internal = (ଶୂନ୍ୟ *)display_data;

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

            ଯଦି (!SDL_AddVideoDisplay(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_mode_data);
                SDL_free(display_data);
                ଫେରନ୍ତୁ false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ଖାଲି);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ଖାଲି);

    video_initialized = true;

    SDL_free(screen_display);

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ QNX_VideoQuit(SDL_VideoDevice *_this)
{
    ଯଦି (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
ସ୍ଥିର bool QNX_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData       *impl;
    SDL_VideoDisplay     *display = ଖାଲି;
    SDL_DisplayData      *display_data = ଖାଲି;
    SDL_DisplayModeData  *display_mode_data = ଖାଲି;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             size[2];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             position[2];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             numbufs;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             format;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             usage;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             has_focus_i;

    impl = SDL_calloc(1, ଆକାର(*impl));
    ଯଦି (!impl) {
        ଫେରନ୍ତୁ false;
    }
    window->internal = impl;

    // Create a native window.
    ଯଦି (screen_create_window(&impl->window, context) < 0) {
        ଯାଅ fail;
    }

    // Set the native window's size to match the SDL window.
    size[0] = window->w;
    size[1] = window->h;
    position[0] = window->x;
    position[1] = window->y;

    ଯଦି (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        ଯାଅ fail;
    }

    ଯଦି (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        ଯାଅ fail;
    }

    ଯଦି (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        ଯାଅ fail;
    }

    display = SDL_GetVideoDisplayForWindow(window);
    SDL_assert(display != ଖାଲି);
    SDL_assert(display->desktop_mode.internal != ଖାଲି);
    display_mode_data = display->desktop_mode.internal;

    // Create window buffer(s).
    ଯଦି (window->flags & SDL_WINDOW_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        ଯଦି (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            ଯାଅ fail;
        }
    } ଅନ୍ୟଥା {
        numbufs = 1;
    }

    // Create buffer(s).
    ଯଦି (screen_create_window_buffers(impl->window, numbufs>0?numbufs:1) < 0) {
        ଯାଅ fail;
    }

    // Initialize EGL surface.
    ଯଦି (window->flags & SDL_WINDOW_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
        ଯଦି (impl->egl_surface == EGL_NO_SURFACE) {
            ଯାଅ fail;
        }
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    ଯଦି (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_mode_data->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_mode.format = screenToPixelFormat(format);
    display_mode_data->screen_format = format;

    display_data = display->internal;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_data != ଖାଲି);

    // Get initial focus state. Fallback to true.
    ଯଦି(screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } ଅନ୍ୟଥା {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_WINDOW_POINTER, impl->window);

    ଫେରନ୍ତୁ true;

fail:
    ଯଦି (impl->window) {
        screen_destroy_window(impl->window);
    }
    ଯଦି (display_data) {
        SDL_free(display_data);
        display->internal = ଖାଲି;
    }

    SDL_free(impl);
    window->internal = ଖାଲି;
    ଫେରନ୍ତୁ false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
ସ୍ଥିର bool QNX_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format,
                        ଶୂନ୍ୟ ** pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pitch)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              buffer_ଗଣନା_2;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t  *buffer;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);

    ଯଦି (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_ଗଣନା, &buffer_ଗଣନା_2) < 0) {
        ଫେରନ୍ତୁ false;
    }
    buffer = SDL_calloc(buffer_ଗଣନା_2, ଆକାର(screen_buffer_t));

    // Get a pointer to the buffer's memory.
    ଯଦି (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (ଶୂନ୍ୟ **)buffer) < 0) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (screen_get_buffer_property_pv(*buffer, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        ଫେରନ୍ତୁ false;
    }

    // Set format and pitch.
    ଯଦି (screen_get_buffer_property_iv(*buffer, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        ଫେରନ୍ତୁ false;
    }

    *format = display->desktop_mode.format;
    ଫେରନ୍ତୁ true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
ସ୍ଥିର bool QNX_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ଅଚଳ SDL_Rect *rects,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା numrects)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା buffer_ଗଣନା_2, *rects_int;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t *buffer;

    ଯଦି (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_ଗଣନା, &buffer_ଗଣନା_2) < 0) {
        ଫେରନ୍ତୁ false;
    }
    buffer = SDL_calloc(buffer_ଗଣନା_2, ଆକାର(screen_buffer_t));

    ଯଦି (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (ଶୂନ୍ୟ **)buffer) < 0) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି(numrects>0){
        rects_int = SDL_calloc(4*numrects, ଆକାର(ପୂର୍ଣ୍ଣସଂଖ୍ୟା));

        ପାଇଁ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        ଯଦି(screen_post_window(impl->window, buffer[0], numrects, rects_int, 0)) {
            ଫେରନ୍ତୁ false;
        }
        ଯଦି(screen_flush_context(context, 0)) {
            ଫେରନ୍ତୁ false;
        }
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର SDL_FullscreenResult QNX_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *window_data = window->internal;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା size[2] = { 0, 0 };
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା position[2] = { 0, 0 };

    ଯଦି (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        ଫେରନ୍ତୁ SDL_FULLSCREEN_SUCCEEDED;
    }

    ଯଦି (fullscreen) {
        SDL_Rect bounds;

        ଯଦି (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            ଫେରନ୍ତୁ SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        size[0] = bounds.w;
        size[1] = bounds.h;
    } ଅନ୍ୟଥା {
        position[0] = window->x;
        position[1] = window->y;
        size[0] = window->w;
        size[1] = window->h;
    }

    ଯଦି (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        ଫେରନ୍ତୁ SDL_FULLSCREEN_FAILED;
    }

    ଯଦି (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        ଫେରନ୍ତୁ SDL_FULLSCREEN_FAILED;
    }

    ଯଦି (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        ଫେରନ୍ତୁ SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);

    ଫେରନ୍ତୁ SDL_FULLSCREEN_SUCCEEDED;
}

ସ୍ଥିର SDL_DisplayID QNX_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_WindowData  *impl = (SDL_WindowData *)window->internal;
    SDL_DisplayData *display_data;

    screen_display_t screen_display;

    ଯଦି (impl == ଖାଲି) {
        ଫେରନ୍ତୁ 0;
    }

    ଯଦି (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_DISPLAY, (ଶୂନ୍ୟ **)&screen_display) < 0) {
        ଫେରନ୍ତୁ 0;
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < _this->ଅଙ୍କ_displays; i++) {
        display_data = _this->displays[i]->internal;
        ଯଦି (display_data && (display_data->screen_display == screen_display)) {
            ଫେରନ୍ତୁ _this->displays[i]->id;
        }
    }

    ଫେରନ୍ତୁ 0;
}

/**
 * Runs the main event loop.
 */
ସ୍ଥିର ଶୂନ୍ୟ QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Window      *window;
    SDL_WindowData   *impl;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             type;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    ପାଇଁ (window = _this->windows; window; window = window->next) {
        impl = (SDL_WindowData *)window->internal;
        ଯଦି (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            ଜାରି;
        }
        has_focus = (bool)has_focus_i;

        ଯଦି (impl->has_focus != has_focus) {
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST), 0, 0);
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_MOUSE_ENTER : SDL_EVENT_WINDOW_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_SetMouseFocus(window);
            SDL_SetKeyboardFocus(window);
        }
    }

    ପାଇଁ (;;) {
        ଯଦି (screen_get_event(context, event, 0) < 0) {
            ଭାଙ୍ଗ;
        }

        ଯଦି (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            ଭାଙ୍ଗ;
        }

        ଯଦି (type == SCREEN_EVENT_NONE) {
            ଭାଙ୍ଗ;
        }

        ବାଛ (type) {
        ସ୍ଥିତି SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            ଭାଙ୍ଗ;

        ସ୍ଥିତି SCREEN_EVENT_POINTER:
            handlePointerEvent(event);
            ଭାଙ୍ଗ;

        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
ସ୍ଥିର ଶୂନ୍ୟ QNX_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             size[2];

    size[0] = window->pending.w;
    size[1] = window->pending.h;

    ଯଦି (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        ଯଦି (screen_destroy_window_buffers(impl->window) < 0) {
            ଫେରନ୍ତୁ;
        }
        impl->resize = true;

        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size);
        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size);

        screen_create_window_buffers(impl->window, (window->flags & SDL_WINDOW_OPENGL) ? 2 : 1);
    } ଅନ୍ୟଥା {
        window->last_size_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
ସ୍ଥିର ଶୂନ୍ୟ QNX_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା       visible = 1;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
ସ୍ଥିର ଶୂନ୍ୟ QNX_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା       visible = 0;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
ସ୍ଥିର ଶୂନ୍ୟ QNX_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;

    ଯଦି (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_window(impl->window);
        window->internal = ଖାଲି;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
ସ୍ଥିର ଶୂନ୍ୟ QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
ସ୍ଥିର SDL_VideoDevice *createDevice(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, ଆକାର(SDL_VideoDevice));
    ଯଦି (!device) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    device->internal = ଖାଲି;
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
#ଯଦି 0
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

    device->ମୁକ୍ତ = QNX_DeleteDevice;

    ଫେରନ୍ତୁ device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    ଖାଲି, // no ShowMessageBox implementation
    false
};
