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

#अन्तर्भाव "SDL_internal.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_egl_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_windowevents_c.h"
#अन्तर्भाव "SDL_qnx.h"

#अन्तर्भाव <errno.h>

स्थिर screen_context_t context;
स्थिर screen_event_t   event;
स्थिर bool video_initialized = false;

screen_context_t * getContext()
{
    प्रत्यागम &context;
}

screen_event_t * getEvent()
{
    प्रत्यागम &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
स्थिर bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_DisplayData      *display_data;
    SDL_DisplayMode      display_mode;
    SDL_DisplayModeData  *display_mode_data;

    पूर्णाङ्क size[2];
    पूर्णाङ्क index;
    पूर्णाङ्क display_गिनती;
    पूर्णाङ्क active;

    screen_display_t *screen_display;

    यदि (video_initialized) {
        प्रत्यागम true;
    }

    यदि (screen_create_context(&context, 0) < 0) {
        प्रत्यागम false;
    }

    यदि (screen_create_event(&event) < 0) {
        प्रत्यागम false;
    }

    /* start with no displays and increment as attached displays are found */
    यदि (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_गिनती, &display_गिनती) < 0) {
        प्रत्यागम false;
    }

    screen_display = SDL_calloc(display_गिनती, परिमाण(screen_display_t));
    यदि (screen_display == रिक्त) {
        प्रत्यागम false;
    }

    यदि (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (शून्य **)screen_display) < 0) {
        प्रत्यागम false;
    }

    /* create SDL displays based on display info from the screen API */
    प्रति (index = 0; index < display_गिनती; index++) {
        active = 0;
        यदि (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_ATTACHED, &active) < 0) {
            SDL_free(screen_display);
            प्रत्यागम false;
        }

        यदि (active) {
            display_data = (SDL_DisplayData *)SDL_calloc(1, परिमाण(SDL_DisplayData));
            यदि (display_data == रिक्त) {
                SDL_free(screen_display);
                प्रत्यागम false;
            }
            SDL_zerop(display_data);

            यदि (screen_get_display_property_iv(screen_display[index], SCREEN_PROPERTY_SIZE, size) < 0) {
                SDL_free(screen_display);
                SDL_free(display_data);
                प्रत्यागम false;
            }

            display_mode_data = (SDL_DisplayModeData *)SDL_calloc(1, परिमाण(SDL_DisplayModeData));
            यदि (display_mode_data == रिक्त) {
                SDL_free(screen_display);
                SDL_free(display_data);
                प्रत्यागम false;
            }
            SDL_zerop(display_mode_data);

            SDL_zero(display);
            SDL_zero(display_mode);

            display_data->screen_display = screen_display[index];
            display.internal = (शून्य *)display_data;

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

            यदि (!SDL_AddVideoDisplay(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_mode_data);
                SDL_free(display_data);
                प्रत्यागम false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, रिक्त);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, रिक्त);

    video_initialized = true;

    SDL_free(screen_display);

    प्रत्यागम true;
}

स्थिर शून्य QNX_VideoQuit(SDL_VideoDevice *_this)
{
    यदि (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
स्थिर bool QNX_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData       *impl;
    SDL_VideoDisplay     *display = रिक्त;
    SDL_DisplayData      *display_data = रिक्त;
    SDL_DisplayModeData  *display_mode_data = रिक्त;

    पूर्णाङ्क             size[2];
    पूर्णाङ्क             position[2];
    पूर्णाङ्क             numbufs;
    पूर्णाङ्क             format;
    पूर्णाङ्क             usage;
    पूर्णाङ्क             has_focus_i;

    impl = SDL_calloc(1, परिमाण(*impl));
    यदि (!impl) {
        प्रत्यागम false;
    }
    window->internal = impl;

    // Create a native window.
    यदि (screen_create_window(&impl->window, context) < 0) {
        गच्छ fail;
    }

    // Set the native window's size to match the SDL window.
    size[0] = window->w;
    size[1] = window->h;
    position[0] = window->x;
    position[1] = window->y;

    यदि (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        गच्छ fail;
    }

    यदि (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        गच्छ fail;
    }

    यदि (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        गच्छ fail;
    }

    display = SDL_GetVideoDisplayForWindow(window);
    SDL_assert(display != रिक्त);
    SDL_assert(display->desktop_mode.internal != रिक्त);
    display_mode_data = display->desktop_mode.internal;

    // Create window buffer(s).
    यदि (window->flags & SDL_WINDOW_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        यदि (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            गच्छ fail;
        }
    } अन्यथा {
        numbufs = 1;
    }

    // Create buffer(s).
    यदि (screen_create_window_buffers(impl->window, numbufs>0?numbufs:1) < 0) {
        गच्छ fail;
    }

    // Initialize EGL surface.
    यदि (window->flags & SDL_WINDOW_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
        यदि (impl->egl_surface == EGL_NO_SURFACE) {
            गच्छ fail;
        }
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    यदि (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_mode_data->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_mode.format = screenToPixelFormat(format);
    display_mode_data->screen_format = format;

    display_data = display->internal;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_data != रिक्त);

    // Get initial focus state. Fallback to true.
    यदि(screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } अन्यथा {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_WINDOW_POINTER, impl->window);

    प्रत्यागम true;

fail:
    यदि (impl->window) {
        screen_destroy_window(impl->window);
    }
    यदि (display_data) {
        SDL_free(display_data);
        display->internal = रिक्त;
    }

    SDL_free(impl);
    window->internal = रिक्त;
    प्रत्यागम false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
स्थिर bool QNX_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format,
                        शून्य ** pixels, पूर्णाङ्क *pitch)
{
    पूर्णाङ्क              buffer_गिनती_2;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t  *buffer;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);

    यदि (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_गिनती, &buffer_गिनती_2) < 0) {
        प्रत्यागम false;
    }
    buffer = SDL_calloc(buffer_गिनती_2, परिमाण(screen_buffer_t));

    // Get a pointer to the buffer's memory.
    यदि (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (शून्य **)buffer) < 0) {
        प्रत्यागम false;
    }

    यदि (screen_get_buffer_property_pv(*buffer, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        प्रत्यागम false;
    }

    // Set format and pitch.
    यदि (screen_get_buffer_property_iv(*buffer, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        प्रत्यागम false;
    }

    *format = display->desktop_mode.format;
    प्रत्यागम true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
स्थिर bool QNX_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ध्रुव SDL_Rect *rects,
                        पूर्णाङ्क numrects)
{
    पूर्णाङ्क buffer_गिनती_2, *rects_int;
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    screen_buffer_t *buffer;

    यदि (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_BUFFER_गिनती, &buffer_गिनती_2) < 0) {
        प्रत्यागम false;
    }
    buffer = SDL_calloc(buffer_गिनती_2, परिमाण(screen_buffer_t));

    यदि (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (शून्य **)buffer) < 0) {
        प्रत्यागम false;
    }

    यदि(numrects>0){
        rects_int = SDL_calloc(4*numrects, परिमाण(पूर्णाङ्क));

        प्रति(पूर्णाङ्क i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        यदि(screen_post_window(impl->window, buffer[0], numrects, rects_int, 0)) {
            प्रत्यागम false;
        }
        यदि(screen_flush_context(context, 0)) {
            प्रत्यागम false;
        }
    }
    प्रत्यागम true;
}

स्थिर SDL_FullscreenResult QNX_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *window_data = window->internal;
    पूर्णाङ्क size[2] = { 0, 0 };
    पूर्णाङ्क position[2] = { 0, 0 };

    यदि (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
    }

    यदि (fullscreen) {
        SDL_Rect bounds;

        यदि (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            प्रत्यागम SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        size[0] = bounds.w;
        size[1] = bounds.h;
    } अन्यथा {
        position[0] = window->x;
        position[1] = window->y;
        size[0] = window->w;
        size[1] = window->h;
    }

    यदि (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SIZE, size) < 0) {
        प्रत्यागम SDL_FULLSCREEN_FAILED;
    }

    यदि (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_SOURCE_SIZE, size) < 0) {
        प्रत्यागम SDL_FULLSCREEN_FAILED;
    }

    यदि (screen_set_window_property_iv(window_data->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        प्रत्यागम SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);

    प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
}

स्थिर SDL_DisplayID QNX_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_WindowData  *impl = (SDL_WindowData *)window->internal;
    SDL_DisplayData *display_data;

    screen_display_t screen_display;

    यदि (impl == रिक्त) {
        प्रत्यागम 0;
    }

    यदि (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_DISPLAY, (शून्य **)&screen_display) < 0) {
        प्रत्यागम 0;
    }

    प्रति (पूर्णाङ्क i = 0; i < _this->अंक_displays; i++) {
        display_data = _this->displays[i]->internal;
        यदि (display_data && (display_data->screen_display == screen_display)) {
            प्रत्यागम _this->displays[i]->id;
        }
    }

    प्रत्यागम 0;
}

/**
 * Runs the main event loop.
 */
स्थिर शून्य QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Window      *window;
    SDL_WindowData   *impl;
    पूर्णाङ्क             type;
    पूर्णाङ्क             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    प्रति (window = _this->windows; window; window = window->next) {
        impl = (SDL_WindowData *)window->internal;
        यदि (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            अनुवर्त;
        }
        has_focus = (bool)has_focus_i;

        यदि (impl->has_focus != has_focus) {
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST), 0, 0);
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_MOUSE_ENTER : SDL_EVENT_WINDOW_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_SetMouseFocus(window);
            SDL_SetKeyboardFocus(window);
        }
    }

    प्रति (;;) {
        यदि (screen_get_event(context, event, 0) < 0) {
            भङ्ग;
        }

        यदि (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            भङ्ग;
        }

        यदि (type == SCREEN_EVENT_NONE) {
            भङ्ग;
        }

        विकल्प (type) {
        पक्ष SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            भङ्ग;

        पक्ष SCREEN_EVENT_POINTER:
            handlePointerEvent(event);
            भङ्ग;

        स्वभाव:
            भङ्ग;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
स्थिर शून्य QNX_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    पूर्णाङ्क             size[2];

    size[0] = window->pending.w;
    size[1] = window->pending.h;

    यदि (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        यदि (screen_destroy_window_buffers(impl->window) < 0) {
            प्रत्यागम;
        }
        impl->resize = true;

        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size);
        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE, size);

        screen_create_window_buffers(impl->window, (window->flags & SDL_WINDOW_OPENGL) ? 2 : 1);
    } अन्यथा {
        window->last_size_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
स्थिर शून्य QNX_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ध्रुव पूर्णाङ्क       visible = 1;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
स्थिर शून्य QNX_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;
    ध्रुव पूर्णाङ्क       visible = 0;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
स्थिर शून्य QNX_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData   *impl = (SDL_WindowData *)window->internal;

    यदि (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_window(impl->window);
        window->internal = रिक्त;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
स्थिर शून्य QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
स्थिर SDL_VideoDevice *createDevice(शून्य)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    device->internal = रिक्त;
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
#यदि 0
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

    device->मुक्त = QNX_DeleteDevice;

    प्रत्यागम device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    रिक्त, // no ShowMessageBox implementation
    false
};
