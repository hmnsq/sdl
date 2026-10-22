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
    SDL_Display_दत्त      *display_दत्त;
    SDL_Display_बहुलकम्      display_बहुलकम्_2;
    SDL_Display_बहुलकम्_दत्त  *display_बहुलकम्_दत्त;

    पूर्णाङ्क आकार[2];
    पूर्णाङ्क सूचकांक;
    पूर्णाङ्क display_गणनम्;
    पूर्णाङ्क सक्रिय;

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
    यदि (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_गणनम्, &display_गणनम्) < 0) {
        प्रत्यागम false;
    }

    screen_display = SDL_calloc(display_गणनम्, परिमाण(screen_display_t));
    यदि (screen_display == रिक्त) {
        प्रत्यागम false;
    }

    यदि (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (शून्य **)screen_display) < 0) {
        प्रत्यागम false;
    }

    /* create SDL displays based on display info from the screen API */
    प्रति (सूचकांक = 0; सूचकांक < display_गणनम्; सूचकांक++) {
        सक्रिय = 0;
        यदि (screen_get_display_property_iv(screen_display[सूचकांक], SCREEN_PROPERTY_ATTACHED, &सक्रिय) < 0) {
            SDL_free(screen_display);
            प्रत्यागम false;
        }

        यदि (सक्रिय) {
            display_दत्त = (SDL_Display_दत्त *)SDL_calloc(1, परिमाण(SDL_Display_दत्त));
            यदि (display_दत्त == रिक्त) {
                SDL_free(screen_display);
                प्रत्यागम false;
            }
            SDL_zerop(display_दत्त);

            यदि (screen_get_display_property_iv(screen_display[सूचकांक], SCREEN_PROPERTY_आकार, आकार) < 0) {
                SDL_free(screen_display);
                SDL_free(display_दत्त);
                प्रत्यागम false;
            }

            display_बहुलकम्_दत्त = (SDL_Display_बहुलकम्_दत्त *)SDL_calloc(1, परिमाण(SDL_Display_बहुलकम्_दत्त));
            यदि (display_बहुलकम्_दत्त == रिक्त) {
                SDL_free(screen_display);
                SDL_free(display_दत्त);
                प्रत्यागम false;
            }
            SDL_zerop(display_बहुलकम्_दत्त);

            SDL_zero(display);
            SDL_zero(display_बहुलकम्_2);

            display_दत्त->screen_display = screen_display[सूचकांक];
            display.आन्तरिकम् = (शून्य *)display_दत्त;

            display_बहुलकम्_2.w = आकार[0];
            display_बहुलकम्_2.h = आकार[1];
            display_बहुलकम्_2.refresh_दरः = 60;
            display_बहुलकम्_2.pixel_density = 1.0;
            display_बहुलकम्_2.आन्तरिकम् = display_बहुलकम्_दत्त;
            // This is assigned later when the window is created. For now, use a
            // safe guess.
            display_बहुलकम्_2.format = SDL_PIXELFORMAT_RGBX8888;
            display_बहुलकम्_दत्त->screen_format = SCREEN_FORMAT_RGBX8888;
            // Be able to revert to the default display mode despite not having
            // the actual object to refer to.
            display_बहुलकम्_दत्त->screen_display_बहुलकम्.सूचकांक = SCREEN_DISPLAY_बहुलकम्_PREFERRED_सूचकांक;

            // Added to current_mode when the display is added.
            display.desktop_बहुलकम् = display_बहुलकम्_2;

            यदि (!SDL_सङ्कलय_Video_Display(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_बहुलकम्_दत्त);
                SDL_free(display_दत्त);
                प्रत्यागम false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_सङ्कलय_Keyboard(SDL_DEFAULT_KEYBOARD_ID, रिक्त);
    SDL_सङ्कलय_Mouse(SDL_DEFAULT_MOUSE_ID, रिक्त);

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
स्थिर bool QNX_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_गवाक्षः_दत्त       *impl;
    SDL_VideoDisplay     *display = रिक्त;
    SDL_Display_दत्त      *display_दत्त = रिक्त;
    SDL_Display_बहुलकम्_दत्त  *display_बहुलकम्_दत्त = रिक्त;

    पूर्णाङ्क             आकार[2];
    पूर्णाङ्क             position[2];
    पूर्णाङ्क             numbufs;
    पूर्णाङ्क             format;
    पूर्णाङ्क             usage;
    पूर्णाङ्क             has_focus_i;

    impl = SDL_calloc(1, परिमाण(*impl));
    यदि (!impl) {
        प्रत्यागम false;
    }
    गवाक्षः->आन्तरिकम् = impl;

    // Create a native window.
    यदि (screen_create_गवाक्षः(&impl->गवाक्षः, context) < 0) {
        गच्छ fail;
    }

    // Set the native window's size to match the SDL window.
    आकार[0] = गवाक्षः->w;
    आकार[1] = गवाक्षः->h;
    position[0] = गवाक्षः->x;
    position[1] = गवाक्षः->y;

    यदि (screen_समुच्चयः_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_आकार, आकार) < 0) {
        गच्छ fail;
    }

    यदि (screen_समुच्चयः_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_SOURCE_आकार, आकार) < 0) {
        गच्छ fail;
    }

    यदि (screen_समुच्चयः_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_POSITION, position) < 0) {
        गच्छ fail;
    }

    display = SDL_Get_Video_Display_For_गवाक्षः(गवाक्षः);
    SDL_assert(display != रिक्त);
    SDL_assert(display->desktop_बहुलकम्.आन्तरिकम् != रिक्त);
    display_बहुलकम्_दत्त = display->desktop_बहुलकम्.आन्तरिकम्;

    // Create window buffer(s).
    यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        यदि (screen_समुच्चयः_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            गच्छ fail;
        }
    } अन्यथा {
        numbufs = 1;
    }

    // Create buffer(s).
    यदि (screen_create_गवाक्षः_buffers(impl->गवाक्षः, numbufs>0?numbufs:1) < 0) {
        गच्छ fail;
    }

    // Initialize EGL surface.
    यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, गवाक्षः, (Native_गवाक्षः_Type)impl->गवाक्षः);
        यदि (impl->egl_surface == EGL_NO_SURFACE) {
            गच्छ fail;
        }
        SDL_समुच्चयः_Pointer_Property(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_QNX_SURFACE_POINTER, impl->egl_surface);
    }

    यदि (screen_get_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_बहुलकम्_दत्त->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_बहुलकम्.format = screen_गन्तव्यम्_Pixel_Format(format);
    display_बहुलकम्_दत्त->screen_format = format;

    display_दत्त = display->आन्तरिकम्;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_दत्त != रिक्त);

    // Get initial focus state. Fallback to true.
    यदि(screen_get_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } अन्यथा {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_समुच्चयः_Pointer_Property(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_QNX_गवाक्षः_POINTER, impl->गवाक्षः);

    प्रत्यागम true;

fail:
    यदि (impl->गवाक्षः) {
        screen_destroy_गवाक्षः(impl->गवाक्षः);
    }
    यदि (display_दत्त) {
        SDL_free(display_दत्त);
        display->आन्तरिकम् = रिक्त;
    }

    SDL_free(impl);
    गवाक्षः->आन्तरिकम् = रिक्त;
    प्रत्यागम false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
स्थिर bool QNX_Create_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः, SDL_PixelFormat * format,
                        शून्य ** pixels, पूर्णाङ्क *pitch)
{
    पूर्णाङ्क              बफर_गणनम्_2;
    SDL_गवाक्षः_दत्त   *impl = (SDL_गवाक्षः_दत्त *)गवाक्षः->आन्तरिकम्;
    screen_बफर_t  *बफर_2;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_गवाक्षः(गवाक्षः);

    यदि (screen_get_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_बफर_गणनम्, &बफर_गणनम्_2) < 0) {
        प्रत्यागम false;
    }
    बफर_2 = SDL_calloc(बफर_गणनम्_2, परिमाण(screen_बफर_t));

    // Get a pointer to the buffer's memory.
    यदि (screen_get_गवाक्षः_property_pv(impl->गवाक्षः, SCREEN_PROPERTY_BUFFERS, (शून्य **)बफर_2) < 0) {
        प्रत्यागम false;
    }

    यदि (screen_get_बफर_property_pv(*बफर_2, SCREEN_PROPERTY_POINTER, pixels) < 0) {
        प्रत्यागम false;
    }

    // Set format and pitch.
    यदि (screen_get_बफर_property_iv(*बफर_2, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        प्रत्यागम false;
    }

    *format = display->desktop_बहुलकम्.format;
    प्रत्यागम true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
स्थिर bool QNX_Update_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rects,
                        पूर्णाङ्क numrects)
{
    पूर्णाङ्क बफर_गणनम्_2, *rects_int;
    SDL_गवाक्षः_दत्त   *impl = (SDL_गवाक्षः_दत्त *)गवाक्षः->आन्तरिकम्;
    screen_बफर_t *बफर_2;

    यदि (screen_get_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_बफर_गणनम्, &बफर_गणनम्_2) < 0) {
        प्रत्यागम false;
    }
    बफर_2 = SDL_calloc(बफर_गणनम्_2, परिमाण(screen_बफर_t));

    यदि (screen_get_गवाक्षः_property_pv(impl->गवाक्षः, SCREEN_PROPERTY_BUFFERS, (शून्य **)बफर_2) < 0) {
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

        यदि(screen_post_गवाक्षः(impl->गवाक्षः, बफर_2[0], numrects, rects_int, 0)) {
            प्रत्यागम false;
        }
        यदि(screen_flush_context(context, 0)) {
            प्रत्यागम false;
        }
    }
    प्रत्यागम true;
}

स्थिर SDL_Fullscreen_परिणाम QNX_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = गवाक्षः->आन्तरिकम्;
    पूर्णाङ्क आकार[2] = { 0, 0 };
    पूर्णाङ्क position[2] = { 0, 0 };

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) && !fullscreen) {
        प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
    }

    यदि (fullscreen) {
        SDL_Rect bounds;

        यदि (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            प्रत्यागम SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        आकार[0] = bounds.w;
        आकार[1] = bounds.h;
    } अन्यथा {
        position[0] = गवाक्षः->x;
        position[1] = गवाक्षः->y;
        आकार[0] = गवाक्षः->w;
        आकार[1] = गवाक्षः->h;
    }

    यदि (screen_समुच्चयः_गवाक्षः_property_iv(गवाक्षः_दत्त_2->गवाक्षः, SCREEN_PROPERTY_आकार, आकार) < 0) {
        प्रत्यागम SDL_FULLSCREEN_FAILED;
    }

    यदि (screen_समुच्चयः_गवाक्षः_property_iv(गवाक्षः_दत्त_2->गवाक्षः, SCREEN_PROPERTY_SOURCE_आकार, आकार) < 0) {
        प्रत्यागम SDL_FULLSCREEN_FAILED;
    }

    यदि (screen_समुच्चयः_गवाक्षः_property_iv(गवाक्षः_दत्त_2->गवाक्षः, SCREEN_PROPERTY_POSITION, position) < 0) {
        प्रत्यागम SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_गवाक्षः_Event(गवाक्षः, fullscreen ? SDL_EVENT_गवाक्षः_ENTER_FULLSCREEN : SDL_EVENT_गवाक्षः_LEAVE_FULLSCREEN, 0, 0);

    प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
}

स्थिर SDL_DisplayID QNX_Get_Display_For_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_गवाक्षः_दत्त  *impl = (SDL_गवाक्षः_दत्त *)गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *display_दत्त;

    screen_display_t screen_display;

    यदि (impl == रिक्त) {
        प्रत्यागम 0;
    }

    यदि (screen_get_गवाक्षः_property_pv(impl->गवाक्षः, SCREEN_PROPERTY_DISPLAY, (शून्य **)&screen_display) < 0) {
        प्रत्यागम 0;
    }

    प्रति (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; i++) {
        display_दत्त = _this->displays[i]->आन्तरिकम्;
        यदि (display_दत्त && (display_दत्त->screen_display == screen_display)) {
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
    SDL_गवाक्षः      *गवाक्षः;
    SDL_गवाक्षः_दत्त   *impl;
    पूर्णाङ्क             type;
    पूर्णाङ्क             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    प्रति (गवाक्षः = _this->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
        impl = (SDL_गवाक्षः_दत्त *)गवाक्षः->आन्तरिकम्;
        यदि (screen_get_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            अनुवर्त;
        }
        has_focus = (bool)has_focus_i;

        यदि (impl->has_focus != has_focus) {
            SDL_Send_गवाक्षः_Event(गवाक्षः, (has_focus ? SDL_EVENT_गवाक्षः_FOCUS_GAINED : SDL_EVENT_गवाक्षः_FOCUS_नष्टम्), 0, 0);
            SDL_Send_गवाक्षः_Event(गवाक्षः, (has_focus ? SDL_EVENT_गवाक्षः_MOUSE_ENTER : SDL_EVENT_गवाक्षः_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_समुच्चयः_Mouse_Focus(गवाक्षः);
            SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);
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
स्थिर शून्य QNX_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त   *impl = (SDL_गवाक्षः_दत्त *)गवाक्षः->आन्तरिकम्;
    पूर्णाङ्क             आकार[2];

    आकार[0] = गवाक्षः->pending.w;
    आकार[1] = गवाक्षः->pending.h;

    यदि (!(गवाक्षः->flags & (SDL_गवाक्षः_FULLSCREEN | SDL_गवाक्षः_MAXIMIZED))) {
        यदि (screen_destroy_गवाक्षः_buffers(impl->गवाक्षः) < 0) {
            प्रत्यागम;
        }
        impl->resize = true;

        screen_समुच्चयः_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_आकार, आकार);
        screen_समुच्चयः_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_SOURCE_आकार, आकार);

        screen_create_गवाक्षः_buffers(impl->गवाक्षः, (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) ? 2 : 1);
    } अन्यथा {
        गवाक्षः->चरमः_आकार_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
स्थिर शून्य QNX_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त   *impl = (SDL_गवाक्षः_दत्त *)गवाक्षः->आन्तरिकम्;
    ध्रुव पूर्णाङ्क       visible = 1;

    screen_समुच्चयः_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
स्थिर शून्य QNX_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त   *impl = (SDL_गवाक्षः_दत्त *)गवाक्षः->आन्तरिकम्;
    ध्रुव पूर्णाङ्क       visible = 0;

    screen_समुच्चयः_गवाक्षः_property_iv(impl->गवाक्षः, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
स्थिर शून्य QNX_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त   *impl = (SDL_गवाक्षः_दत्त *)गवाक्षः->आन्तरिकम्;

    यदि (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_गवाक्षः(impl->गवाक्षः);
        गवाक्षः->आन्तरिकम् = रिक्त;
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

    device->आन्तरिकम् = रिक्त;
    device->VideoInit = QNX_VideoInit;
    device->VideoQuit = QNX_VideoQuit;
    device->CreateSDLWindow = QNX_Create_गवाक्षः;
    device->Create_गवाक्षः_Framebuffer = QNX_Create_गवाक्षः_Framebuffer;
    device->Update_गवाक्षः_Framebuffer = QNX_Update_गवाक्षः_Framebuffer;
    device->समुच्चयः_गवाक्षः_आकार = QNX_समुच्चयः_गवाक्षः_आकार;
    device->समुच्चयः_गवाक्षः_Fullscreen = QNX_समुच्चयः_गवाक्षः_Fullscreen;
    device->Show_गवाक्षः = QNX_Show_गवाक्षः;
    device->Hide_गवाक्षः = QNX_Hide_गवाक्षः;
    device->Get_Display_For_गवाक्षः = QNX_Get_Display_For_गवाक्षः;
    device->GetDisplayBounds = QNX_GetDisplayBounds;
    device->GetDisplayModes = QNX_GetDisplayModes;
#यदि 0
    device->समुच्चयः_Display_बहुलकम् = QNX_समुच्चयः_Display_बहुलकम्;
#यदि_अन्तः
    device->PumpEvents = QNX_PumpEvents;
    device->Destroy_गवाक्षः = QNX_Destroy_गवाक्षः;

    device->GL_आरोपय_Library = QNX_GLES_आरोपय_Library;
    device->GL_Get_Proc_स्थानाङ्कः = QNX_GLES_Get_Proc_स्थानाङ्कः;
    device->GL_CreateContext = QNX_GLES_CreateContext;
    device->GL_समुच्चयः_Swap_Interval = QNX_GLES_समुच्चयः_Swap_Interval;
    device->GL_GetSwapInterval = QNX_GLES_GetSwapInterval;
    device->GL_Swap_गवाक्षः = QNX_GLES_Swap_गवाक्षः;
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
