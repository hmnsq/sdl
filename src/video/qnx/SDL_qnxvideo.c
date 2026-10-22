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

#অন্তর্ভাব "SDL_internal.h"
#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../SDL_egl_c.h"
#অন্তর্ভাব "../../events/SDL_keyboard_c.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"
#অন্তর্ভাব "../../events/SDL_windowevents_c.h"
#অন্তর্ভাব "SDL_qnx.h"

#অন্তর্ভাব <errno.h>

স্থির screen_context_t context;
স্থির screen_event_t   event;
স্থির bool video_initialized = false;

screen_context_t * getContext()
{
    ফেরত &context;
}

screen_event_t * getEvent()
{
    ফেরত &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
স্থির bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_Display_তথ্য      *display_তথ্য;
    SDL_DisplayMode      display_mode;
    SDL_Display_Mode_তথ্য  *display_mode_তথ্য;

    পূর্ণসংখ্যা আকার_2[2];
    পূর্ণসংখ্যা সূচক;
    পূর্ণসংখ্যা display_গুনতি;
    পূর্ণসংখ্যা active;

    screen_display_t *screen_display;

    যদি (video_initialized) {
        ফেরত true;
    }

    যদি (screen_create_context(&context, 0) < 0) {
        ফেরত false;
    }

    যদি (screen_create_event(&event) < 0) {
        ফেরত false;
    }

    /* start with no displays and increment as attached displays are found */
    যদি (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_গুনতি, &display_গুনতি) < 0) {
        ফেরত false;
    }

    screen_display = SDL_calloc(display_গুনতি, আকার(screen_display_t));
    যদি (screen_display == ফাঁকা) {
        ফেরত false;
    }

    যদি (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (শূন্য **)screen_display) < 0) {
        ফেরত false;
    }

    /* create SDL displays based on display info from the screen API */
    জন্য (সূচক = 0; সূচক < display_গুনতি; সূচক++) {
        active = 0;
        যদি (screen_get_display_property_iv(screen_display[সূচক], SCREEN_PROPERTY_ATTACHED, &active) < 0) {
            SDL_free(screen_display);
            ফেরত false;
        }

        যদি (active) {
            display_তথ্য = (SDL_Display_তথ্য *)SDL_calloc(1, আকার(SDL_Display_তথ্য));
            যদি (display_তথ্য == ফাঁকা) {
                SDL_free(screen_display);
                ফেরত false;
            }
            SDL_zerop(display_তথ্য);

            যদি (screen_get_display_property_iv(screen_display[সূচক], SCREEN_PROPERTY_আকার, আকার_2) < 0) {
                SDL_free(screen_display);
                SDL_free(display_তথ্য);
                ফেরত false;
            }

            display_mode_তথ্য = (SDL_Display_Mode_তথ্য *)SDL_calloc(1, আকার(SDL_Display_Mode_তথ্য));
            যদি (display_mode_তথ্য == ফাঁকা) {
                SDL_free(screen_display);
                SDL_free(display_তথ্য);
                ফেরত false;
            }
            SDL_zerop(display_mode_তথ্য);

            SDL_zero(display);
            SDL_zero(display_mode);

            display_তথ্য->screen_display = screen_display[সূচক];
            display.internal = (শূন্য *)display_তথ্য;

            display_mode.w = আকার_2[0];
            display_mode.h = আকার_2[1];
            display_mode.refresh_rate = 60;
            display_mode.pixel_density = 1.0;
            display_mode.internal = display_mode_তথ্য;
            // This is assigned later when the window is created. For now, use a
            // safe guess.
            display_mode.format = SDL_PIXELFORMAT_RGBX8888;
            display_mode_তথ্য->screen_format = SCREEN_FORMAT_RGBX8888;
            // Be able to revert to the default display mode despite not having
            // the actual object to refer to.
            display_mode_তথ্য->screen_display_mode.সূচক = SCREEN_DISPLAY_MODE_PREFERRED_সূচক;

            // Added to current_mode when the display is added.
            display.desktop_mode = display_mode;

            যদি (!SDL_AddVideoDisplay(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_mode_তথ্য);
                SDL_free(display_তথ্য);
                ফেরত false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ফাঁকা);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ফাঁকা);

    video_initialized = true;

    SDL_free(screen_display);

    ফেরত true;
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
    SDL_Window_তথ্য       *impl;
    SDL_VideoDisplay     *display = ফাঁকা;
    SDL_Display_তথ্য      *display_তথ্য = ফাঁকা;
    SDL_Display_Mode_তথ্য  *display_mode_তথ্য = ফাঁকা;

    পূর্ণসংখ্যা             আকার_2[2];
    পূর্ণসংখ্যা             position[2];
    পূর্ণসংখ্যা             numbufs;
    পূর্ণসংখ্যা             format;
    পূর্ণসংখ্যা             usage;
    পূর্ণসংখ্যা             has_focus_i;

    impl = SDL_calloc(1, আকার(*impl));
    যদি (!impl) {
        ফেরত false;
    }
    window->internal = impl;

    // Create a native window.
    যদি (screen_create_window(&impl->window, context) < 0) {
        যাও fail;
    }

    // Set the native window's size to match the SDL window.
    আকার_2[0] = window->w;
    আকার_2[1] = window->h;
    position[0] = window->x;
    position[1] = window->y;

    যদি (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_আকার, আকার_2) < 0) {
        যাও fail;
    }

    যদি (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_আকার, আকার_2) < 0) {
        যাও fail;
    }

    যদি (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        যাও fail;
    }

    display = SDL_GetVideoDisplayForWindow(window);
    SDL_assert(display != ফাঁকা);
    SDL_assert(display->desktop_mode.internal != ফাঁকা);
    display_mode_তথ্য = display->desktop_mode.internal;

    // Create window buffer(s).
    যদি (window->flags & SDL_WINDOW_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        যদি (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            যাও fail;
        }
    } অন্যথা {
        numbufs = 1;
    }

    // Create buffer(s).
    যদি (screen_create_window_buffers(impl->window, numbufs>0?numbufs:1) < 0) {
        যাও fail;
    }

    // Initialize EGL surface.
    যদি (window->flags & SDL_WINDOW_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
        যদি (impl->egl_surface == EGL_NO_SURFACE) {
            যাও fail;
        }
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    যদি (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_mode_তথ্য->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_mode.format = screenToPixelFormat(format);
    display_mode_তথ্য->screen_format = format;

    display_তথ্য = display->internal;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_তথ্য != ফাঁকা);

    // Get initial focus state. Fallback to true.
    যদি(screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } অন্যথা {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_WINDOW_POINTER, impl->window);

    ফেরত true;

fail:
    যদি (impl->window) {
        screen_destroy_window(impl->window);
    }
    যদি (display_তথ্য) {
        SDL_free(display_তথ্য);
        display->internal = ফাঁকা;
    }

    SDL_free(impl);
    window->internal = ফাঁকা;
    ফেরত false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
স্থির bool QNX_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format,
                        শূন্য ** pixels, পূর্ণসংখ্যা *pitch)
{
    পূর্ণসংখ্যা              বাফার_গুনতি_2;
    SDL_Window_তথ্য   *impl = (SDL_Window_তথ্য *)window->internal;
    screen_বাফার_t  *বাফার_2;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);

    যদি (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_বাফার_গুনতি, &বাফার_গুনতি_2) < 0) {
        ফেরত false;
    }
    বাফার_2 = SDL_calloc(বাফার_গুনতি_2, আকার(screen_বাফার_t));

    // Get a pointer to the buffer's memory.
    যদি (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (শূন্য **)বাফার_2) < 0) {
        ফেরত false;
    }

    যদি (screen_get_বাফার_property_pv(*বাফার_2, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        ফেরত false;
    }

    // Set format and pitch.
    যদি (screen_get_বাফার_property_iv(*বাফার_2, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        ফেরত false;
    }

    *format = display->desktop_mode.format;
    ফেরত true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
স্থির bool QNX_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুবক SDL_Rect *rects,
                        পূর্ণসংখ্যা numrects)
{
    পূর্ণসংখ্যা বাফার_গুনতি_2, *rects_int;
    SDL_Window_তথ্য   *impl = (SDL_Window_তথ্য *)window->internal;
    screen_বাফার_t *বাফার_2;

    যদি (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_বাফার_গুনতি, &বাফার_গুনতি_2) < 0) {
        ফেরত false;
    }
    বাফার_2 = SDL_calloc(বাফার_গুনতি_2, আকার(screen_বাফার_t));

    যদি (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (শূন্য **)বাফার_2) < 0) {
        ফেরত false;
    }

    যদি(numrects>0){
        rects_int = SDL_calloc(4*numrects, আকার(পূর্ণসংখ্যা));

        জন্য(পূর্ণসংখ্যা i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        যদি(screen_post_window(impl->window, বাফার_2[0], numrects, rects_int, 0)) {
            ফেরত false;
        }
        যদি(screen_flush_context(context, 0)) {
            ফেরত false;
        }
    }
    ফেরত true;
}

স্থির SDL_Fullscreen_ফলাফল QNX_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_Window_তথ্য *window_তথ্য_2 = window->internal;
    পূর্ণসংখ্যা আকার_2[2] = { 0, 0 };
    পূর্ণসংখ্যা position[2] = { 0, 0 };

    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        ফেরত SDL_FULLSCREEN_SUCCEEDED;
    }

    যদি (fullscreen) {
        SDL_Rect bounds;

        যদি (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            ফেরত SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        আকার_2[0] = bounds.w;
        আকার_2[1] = bounds.h;
    } অন্যথা {
        position[0] = window->x;
        position[1] = window->y;
        আকার_2[0] = window->w;
        আকার_2[1] = window->h;
    }

    যদি (screen_set_window_property_iv(window_তথ্য_2->window, SCREEN_PROPERTY_আকার, আকার_2) < 0) {
        ফেরত SDL_FULLSCREEN_FAILED;
    }

    যদি (screen_set_window_property_iv(window_তথ্য_2->window, SCREEN_PROPERTY_SOURCE_আকার, আকার_2) < 0) {
        ফেরত SDL_FULLSCREEN_FAILED;
    }

    যদি (screen_set_window_property_iv(window_তথ্য_2->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        ফেরত SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);

    ফেরত SDL_FULLSCREEN_SUCCEEDED;
}

স্থির SDL_DisplayID QNX_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_Window_তথ্য  *impl = (SDL_Window_তথ্য *)window->internal;
    SDL_Display_তথ্য *display_তথ্য;

    screen_display_t screen_display;

    যদি (impl == ফাঁকা) {
        ফেরত 0;
    }

    যদি (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_DISPLAY, (শূন্য **)&screen_display) < 0) {
        ফেরত 0;
    }

    জন্য (পূর্ণসংখ্যা i = 0; i < _this->অঙ্ক_displays; i++) {
        display_তথ্য = _this->displays[i]->internal;
        যদি (display_তথ্য && (display_তথ্য->screen_display == screen_display)) {
            ফেরত _this->displays[i]->id;
        }
    }

    ফেরত 0;
}

/**
 * Runs the main event loop.
 */
স্থির শূন্য QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Window      *window;
    SDL_Window_তথ্য   *impl;
    পূর্ণসংখ্যা             type;
    পূর্ণসংখ্যা             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    জন্য (window = _this->windows; window; window = window->পরবর্তী) {
        impl = (SDL_Window_তথ্য *)window->internal;
        যদি (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            চালু;
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

    জন্য (;;) {
        যদি (screen_get_event(context, event, 0) < 0) {
            বিরতি;
        }

        যদি (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            বিরতি;
        }

        যদি (type == SCREEN_EVENT_NONE) {
            বিরতি;
        }

        নির্বাচন (type) {
        ক্ষেত্র SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            বিরতি;

        ক্ষেত্র SCREEN_EVENT_POINTER:
            handlePointerEvent(event);
            বিরতি;

        পূর্বনির্ধারিত:
            বিরতি;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
স্থির শূন্য QNX_Set_Window_আকার(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য   *impl = (SDL_Window_তথ্য *)window->internal;
    পূর্ণসংখ্যা             আকার_2[2];

    আকার_2[0] = window->pending.w;
    আকার_2[1] = window->pending.h;

    যদি (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        যদি (screen_destroy_window_buffers(impl->window) < 0) {
            ফেরত;
        }
        impl->resize = true;

        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_আকার, আকার_2);
        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_আকার, আকার_2);

        screen_create_window_buffers(impl->window, (window->flags & SDL_WINDOW_OPENGL) ? 2 : 1);
    } অন্যথা {
        window->last_আকার_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
স্থির শূন্য QNX_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য   *impl = (SDL_Window_তথ্য *)window->internal;
    ধ্রুবক পূর্ণসংখ্যা       visible = 1;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
স্থির শূন্য QNX_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য   *impl = (SDL_Window_তথ্য *)window->internal;
    ধ্রুবক পূর্ণসংখ্যা       visible = 0;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
স্থির শূন্য QNX_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য   *impl = (SDL_Window_তথ্য *)window->internal;

    যদি (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_window(impl->window);
        window->internal = ফাঁকা;
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

    device = (SDL_VideoDevice *)SDL_calloc(1, আকার(SDL_VideoDevice));
    যদি (!device) {
        ফেরত ফাঁকা;
    }

    device->internal = ফাঁকা;
    device->VideoInit = QNX_VideoInit;
    device->VideoQuit = QNX_VideoQuit;
    device->CreateSDLWindow = QNX_CreateWindow;
    device->CreateWindowFramebuffer = QNX_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = QNX_UpdateWindowFramebuffer;
    device->Set_Window_আকার = QNX_Set_Window_আকার;
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

    ফেরত device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    ফাঁকা, // no ShowMessageBox implementation
    false
};
