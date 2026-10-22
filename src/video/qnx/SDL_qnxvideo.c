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

#समावेश "SDL_internal.h"
#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_egl_c.h"
#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../events/SDL_windowevents_c.h"
#समावेश "SDL_qnx.h"

#समावेश <errno.h>

अटल screen_context_t context;
अटल screen_event_t   event;
अटल bool video_initialized = false;

screen_context_t * getContext()
{
    वापस &context;
}

screen_event_t * getEvent()
{
    वापस &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
अटल bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_Display_तथ्य      *display_तथ्य;
    SDL_DisplayMode      display_mode;
    SDL_Display_Mode_तथ्य  *display_mode_तथ्य;

    पूर्णांक आकार[2];
    पूर्णांक सूचकांक;
    पूर्णांक display_गिनती;
    पूर्णांक active;

    screen_display_t *screen_display;

    अगर (video_initialized) {
        वापस true;
    }

    अगर (screen_create_context(&context, 0) < 0) {
        वापस false;
    }

    अगर (screen_create_event(&event) < 0) {
        वापस false;
    }

    /* start with no displays and increment as attached displays are found */
    अगर (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_गिनती, &display_गिनती) < 0) {
        वापस false;
    }

    screen_display = SDL_calloc(display_गिनती, माप(screen_display_t));
    अगर (screen_display == शून्य) {
        वापस false;
    }

    अगर (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (व्योम **)screen_display) < 0) {
        वापस false;
    }

    /* create SDL displays based on display info from the screen API */
    क्रम (सूचकांक = 0; सूचकांक < display_गिनती; सूचकांक++) {
        active = 0;
        अगर (screen_get_display_property_iv(screen_display[सूचकांक], SCREEN_PROPERTY_ATTACHED, &active) < 0) {
            SDL_free(screen_display);
            वापस false;
        }

        अगर (active) {
            display_तथ्य = (SDL_Display_तथ्य *)SDL_calloc(1, माप(SDL_Display_तथ्य));
            अगर (display_तथ्य == शून्य) {
                SDL_free(screen_display);
                वापस false;
            }
            SDL_zerop(display_तथ्य);

            अगर (screen_get_display_property_iv(screen_display[सूचकांक], SCREEN_PROPERTY_आकार, आकार) < 0) {
                SDL_free(screen_display);
                SDL_free(display_तथ्य);
                वापस false;
            }

            display_mode_तथ्य = (SDL_Display_Mode_तथ्य *)SDL_calloc(1, माप(SDL_Display_Mode_तथ्य));
            अगर (display_mode_तथ्य == शून्य) {
                SDL_free(screen_display);
                SDL_free(display_तथ्य);
                वापस false;
            }
            SDL_zerop(display_mode_तथ्य);

            SDL_zero(display);
            SDL_zero(display_mode);

            display_तथ्य->screen_display = screen_display[सूचकांक];
            display.internal = (व्योम *)display_तथ्य;

            display_mode.w = आकार[0];
            display_mode.h = आकार[1];
            display_mode.refresh_rate = 60;
            display_mode.pixel_density = 1.0;
            display_mode.internal = display_mode_तथ्य;
            // This is assigned later when the window is created. For now, use a
            // safe guess.
            display_mode.format = SDL_PIXELFORMAT_RGBX8888;
            display_mode_तथ्य->screen_format = SCREEN_FORMAT_RGBX8888;
            // Be able to revert to the default display mode despite not having
            // the actual object to refer to.
            display_mode_तथ्य->screen_display_mode.सूचकांक = SCREEN_DISPLAY_MODE_PREFERRED_सूचकांक;

            // Added to current_mode when the display is added.
            display.desktop_mode = display_mode;

            अगर (!SDL_AddVideoDisplay(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_mode_तथ्य);
                SDL_free(display_तथ्य);
                वापस false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, शून्य);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, शून्य);

    video_initialized = true;

    SDL_free(screen_display);

    वापस true;
}

अटल व्योम QNX_VideoQuit(SDL_VideoDevice *_this)
{
    अगर (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
अटल bool QNX_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Window_तथ्य       *impl;
    SDL_VideoDisplay     *display = शून्य;
    SDL_Display_तथ्य      *display_तथ्य = शून्य;
    SDL_Display_Mode_तथ्य  *display_mode_तथ्य = शून्य;

    पूर्णांक             आकार[2];
    पूर्णांक             position[2];
    पूर्णांक             numbufs;
    पूर्णांक             format;
    पूर्णांक             usage;
    पूर्णांक             has_focus_i;

    impl = SDL_calloc(1, माप(*impl));
    अगर (!impl) {
        वापस false;
    }
    window->internal = impl;

    // Create a native window.
    अगर (screen_create_window(&impl->window, context) < 0) {
        जाओ fail;
    }

    // Set the native window's size to match the SDL window.
    आकार[0] = window->w;
    आकार[1] = window->h;
    position[0] = window->x;
    position[1] = window->y;

    अगर (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_आकार, आकार) < 0) {
        जाओ fail;
    }

    अगर (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_आकार, आकार) < 0) {
        जाओ fail;
    }

    अगर (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        जाओ fail;
    }

    display = SDL_GetVideoDisplayForWindow(window);
    SDL_assert(display != शून्य);
    SDL_assert(display->desktop_mode.internal != शून्य);
    display_mode_तथ्य = display->desktop_mode.internal;

    // Create window buffer(s).
    अगर (window->flags & SDL_WINDOW_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        अगर (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            जाओ fail;
        }
    } अन्यथा {
        numbufs = 1;
    }

    // Create buffer(s).
    अगर (screen_create_window_buffers(impl->window, numbufs>0?numbufs:1) < 0) {
        जाओ fail;
    }

    // Initialize EGL surface.
    अगर (window->flags & SDL_WINDOW_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)impl->window);
        अगर (impl->egl_surface == EGL_NO_SURFACE) {
            जाओ fail;
        }
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    अगर (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_mode_तथ्य->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_mode.format = screenToPixelFormat(format);
    display_mode_तथ्य->screen_format = format;

    display_तथ्य = display->internal;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_तथ्य != शून्य);

    // Get initial focus state. Fallback to true.
    अगर(screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } अन्यथा {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_QNX_WINDOW_POINTER, impl->window);

    वापस true;

fail:
    अगर (impl->window) {
        screen_destroy_window(impl->window);
    }
    अगर (display_तथ्य) {
        SDL_free(display_तथ्य);
        display->internal = शून्य;
    }

    SDL_free(impl);
    window->internal = शून्य;
    वापस false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
अटल bool QNX_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format,
                        व्योम ** pixels, पूर्णांक *pitch)
{
    पूर्णांक              बफर_गिनती_2;
    SDL_Window_तथ्य   *impl = (SDL_Window_तथ्य *)window->internal;
    screen_बफर_t  *बफर_2;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);

    अगर (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_बफर_गिनती, &बफर_गिनती_2) < 0) {
        वापस false;
    }
    बफर_2 = SDL_calloc(बफर_गिनती_2, माप(screen_बफर_t));

    // Get a pointer to the buffer's memory.
    अगर (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (व्योम **)बफर_2) < 0) {
        वापस false;
    }

    अगर (screen_get_बफर_property_pv(*बफर_2, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        वापस false;
    }

    // Set format and pitch.
    अगर (screen_get_बफर_property_iv(*बफर_2, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        वापस false;
    }

    *format = display->desktop_mode.format;
    वापस true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
अटल bool QNX_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, स्थिर SDL_Rect *rects,
                        पूर्णांक numrects)
{
    पूर्णांक बफर_गिनती_2, *rects_int;
    SDL_Window_तथ्य   *impl = (SDL_Window_तथ्य *)window->internal;
    screen_बफर_t *बफर_2;

    अगर (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_बफर_गिनती, &बफर_गिनती_2) < 0) {
        वापस false;
    }
    बफर_2 = SDL_calloc(बफर_गिनती_2, माप(screen_बफर_t));

    अगर (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS, (व्योम **)बफर_2) < 0) {
        वापस false;
    }

    अगर(numrects>0){
        rects_int = SDL_calloc(4*numrects, माप(पूर्णांक));

        क्रम(पूर्णांक i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        अगर(screen_post_window(impl->window, बफर_2[0], numrects, rects_int, 0)) {
            वापस false;
        }
        अगर(screen_flush_context(context, 0)) {
            वापस false;
        }
    }
    वापस true;
}

अटल SDL_Fullscreen_परिणाम QNX_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_Window_तथ्य *window_तथ्य_2 = window->internal;
    पूर्णांक आकार[2] = { 0, 0 };
    पूर्णांक position[2] = { 0, 0 };

    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN) && !fullscreen) {
        वापस SDL_FULLSCREEN_SUCCEEDED;
    }

    अगर (fullscreen) {
        SDL_Rect bounds;

        अगर (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            वापस SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        आकार[0] = bounds.w;
        आकार[1] = bounds.h;
    } अन्यथा {
        position[0] = window->x;
        position[1] = window->y;
        आकार[0] = window->w;
        आकार[1] = window->h;
    }

    अगर (screen_set_window_property_iv(window_तथ्य_2->window, SCREEN_PROPERTY_आकार, आकार) < 0) {
        वापस SDL_FULLSCREEN_FAILED;
    }

    अगर (screen_set_window_property_iv(window_तथ्य_2->window, SCREEN_PROPERTY_SOURCE_आकार, आकार) < 0) {
        वापस SDL_FULLSCREEN_FAILED;
    }

    अगर (screen_set_window_property_iv(window_तथ्य_2->window, SCREEN_PROPERTY_POSITION, position) < 0) {
        वापस SDL_FULLSCREEN_FAILED;
    }

    SDL_SendWindowEvent(window, fullscreen ? SDL_EVENT_WINDOW_ENTER_FULLSCREEN : SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);

    वापस SDL_FULLSCREEN_SUCCEEDED;
}

अटल SDL_DisplayID QNX_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_Window_तथ्य  *impl = (SDL_Window_तथ्य *)window->internal;
    SDL_Display_तथ्य *display_तथ्य;

    screen_display_t screen_display;

    अगर (impl == शून्य) {
        वापस 0;
    }

    अगर (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_DISPLAY, (व्योम **)&screen_display) < 0) {
        वापस 0;
    }

    क्रम (पूर्णांक i = 0; i < _this->अंक_displays; i++) {
        display_तथ्य = _this->displays[i]->internal;
        अगर (display_तथ्य && (display_तथ्य->screen_display == screen_display)) {
            वापस _this->displays[i]->id;
        }
    }

    वापस 0;
}

/**
 * Runs the main event loop.
 */
अटल व्योम QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Window      *window;
    SDL_Window_तथ्य   *impl;
    पूर्णांक             type;
    पूर्णांक             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    क्रम (window = _this->windows; window; window = window->अग्र) {
        impl = (SDL_Window_तथ्य *)window->internal;
        अगर (screen_get_window_property_iv(impl->window, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            जारी;
        }
        has_focus = (bool)has_focus_i;

        अगर (impl->has_focus != has_focus) {
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST), 0, 0);
            SDL_SendWindowEvent(window, (has_focus ? SDL_EVENT_WINDOW_MOUSE_ENTER : SDL_EVENT_WINDOW_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_SetMouseFocus(window);
            SDL_SetKeyboardFocus(window);
        }
    }

    क्रम (;;) {
        अगर (screen_get_event(context, event, 0) < 0) {
            अवरोध;
        }

        अगर (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            अवरोध;
        }

        अगर (type == SCREEN_EVENT_NONE) {
            अवरोध;
        }

        चयन (type) {
        हाल SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            अवरोध;

        हाल SCREEN_EVENT_POINTER:
            handlePointerEvent(event);
            अवरोध;

        शेष:
            अवरोध;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
अटल व्योम QNX_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य   *impl = (SDL_Window_तथ्य *)window->internal;
    पूर्णांक             आकार[2];

    आकार[0] = window->pending.w;
    आकार[1] = window->pending.h;

    अगर (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED))) {
        अगर (screen_destroy_window_buffers(impl->window) < 0) {
            वापस;
        }
        impl->resize = true;

        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_आकार, आकार);
        screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_आकार, आकार);

        screen_create_window_buffers(impl->window, (window->flags & SDL_WINDOW_OPENGL) ? 2 : 1);
    } अन्यथा {
        window->last_आकार_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
अटल व्योम QNX_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य   *impl = (SDL_Window_तथ्य *)window->internal;
    स्थिर पूर्णांक       visible = 1;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
अटल व्योम QNX_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य   *impl = (SDL_Window_तथ्य *)window->internal;
    स्थिर पूर्णांक       visible = 0;

    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
अटल व्योम QNX_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य   *impl = (SDL_Window_तथ्य *)window->internal;

    अगर (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_window(impl->window);
        window->internal = शून्य;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
अटल व्योम QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
अटल SDL_VideoDevice *createDevice(व्योम)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (!device) {
        वापस शून्य;
    }

    device->internal = शून्य;
    device->VideoInit = QNX_VideoInit;
    device->VideoQuit = QNX_VideoQuit;
    device->CreateSDLWindow = QNX_CreateWindow;
    device->CreateWindowFramebuffer = QNX_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = QNX_UpdateWindowFramebuffer;
    device->Set_Window_आकार = QNX_Set_Window_आकार;
    device->SetWindowFullscreen = QNX_SetWindowFullscreen;
    device->ShowWindow = QNX_ShowWindow;
    device->HideWindow = QNX_HideWindow;
    device->GetDisplayForWindow = QNX_GetDisplayForWindow;
    device->GetDisplayBounds = QNX_GetDisplayBounds;
    device->GetDisplayModes = QNX_GetDisplayModes;
#अगर 0
    device->SetDisplayMode = QNX_SetDisplayMode;
#पूर्ण_अगर
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

    वापस device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    शून्य, // no ShowMessageBox implementation
    false
};
