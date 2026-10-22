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

#అన్తర్భావ "SDL_internal.h"
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_egl_c.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_windowevents_c.h"
#అన్తర్భావ "SDL_qnx.h"

#అన్తర్భావ <errno.h>

స్థిర screen_context_t context;
స్థిర screen_event_t   event;
స్థిర bool video_initialized = false;

screen_context_t * getContext()
{
    తిరిగి &context;
}

screen_event_t * getEvent()
{
    తిరిగి &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
స్థిర bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_Display_దత్తాంశం      *display_దత్తాంశం;
    SDL_Display_బహుళకం      display_బహుళకం_2;
    SDL_Display_బహుళకం_దత్తాంశం  *display_బహుళకం_దత్తాంశం;

    పూర్ణాంకం కొలత[2];
    పూర్ణాంకం సూచీ;
    పూర్ణాంకం display_లెక్క;
    పూర్ణాంకం చురుకైన;

    screen_display_t *screen_display;

    ఒకవేళ (video_initialized) {
        తిరిగి true;
    }

    ఒకవేళ (screen_create_context(&context, 0) < 0) {
        తిరిగి false;
    }

    ఒకవేళ (screen_create_event(&event) < 0) {
        తిరిగి false;
    }

    /* start with no displays and increment as attached displays are found */
    ఒకవేళ (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_లెక్క, &display_లెక్క) < 0) {
        తిరిగి false;
    }

    screen_display = SDL_calloc(display_లెక్క, పరిమాణం(screen_display_t));
    ఒకవేళ (screen_display == ఖాళీ) {
        తిరిగి false;
    }

    ఒకవేళ (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (శూన్య **)screen_display) < 0) {
        తిరిగి false;
    }

    /* create SDL displays based on display info from the screen API */
    కొరకు (సూచీ = 0; సూచీ < display_లెక్క; సూచీ++) {
        చురుకైన = 0;
        ఒకవేళ (screen_get_display_property_iv(screen_display[సూచీ], SCREEN_PROPERTY_ATTACHED, &చురుకైన) < 0) {
            SDL_free(screen_display);
            తిరిగి false;
        }

        ఒకవేళ (చురుకైన) {
            display_దత్తాంశం = (SDL_Display_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Display_దత్తాంశం));
            ఒకవేళ (display_దత్తాంశం == ఖాళీ) {
                SDL_free(screen_display);
                తిరిగి false;
            }
            SDL_zerop(display_దత్తాంశం);

            ఒకవేళ (screen_get_display_property_iv(screen_display[సూచీ], SCREEN_PROPERTY_కొలత, కొలత) < 0) {
                SDL_free(screen_display);
                SDL_free(display_దత్తాంశం);
                తిరిగి false;
            }

            display_బహుళకం_దత్తాంశం = (SDL_Display_బహుళకం_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Display_బహుళకం_దత్తాంశం));
            ఒకవేళ (display_బహుళకం_దత్తాంశం == ఖాళీ) {
                SDL_free(screen_display);
                SDL_free(display_దత్తాంశం);
                తిరిగి false;
            }
            SDL_zerop(display_బహుళకం_దత్తాంశం);

            SDL_zero(display);
            SDL_zero(display_బహుళకం_2);

            display_దత్తాంశం->screen_display = screen_display[సూచీ];
            display.అంతర్గత = (శూన్య *)display_దత్తాంశం;

            display_బహుళకం_2.w = కొలత[0];
            display_బహుళకం_2.h = కొలత[1];
            display_బహుళకం_2.refresh_రేటు = 60;
            display_బహుళకం_2.pixel_density = 1.0;
            display_బహుళకం_2.అంతర్గత = display_బహుళకం_దత్తాంశం;
            // This is assigned later when the window is created. For now, use a
            // safe guess.
            display_బహుళకం_2.format = SDL_PIXELFORMAT_RGBX8888;
            display_బహుళకం_దత్తాంశం->screen_format = SCREEN_FORMAT_RGBX8888;
            // Be able to revert to the default display mode despite not having
            // the actual object to refer to.
            display_బహుళకం_దత్తాంశం->screen_display_బహుళకం.సూచీ = SCREEN_DISPLAY_బహుళకం_PREFERRED_సూచీ;

            // Added to current_mode when the display is added.
            display.desktop_బహుళకం = display_బహుళకం_2;

            ఒకవేళ (!SDL_కూడు_Video_Display(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_బహుళకం_దత్తాంశం);
                SDL_free(display_దత్తాంశం);
                తిరిగి false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_కూడు_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ఖాళీ);
    SDL_కూడు_Mouse(SDL_DEFAULT_MOUSE_ID, ఖాళీ);

    video_initialized = true;

    SDL_free(screen_display);

    తిరిగి true;
}

స్థిర శూన్య QNX_VideoQuit(SDL_VideoDevice *_this)
{
    ఒకవేళ (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
స్థిర bool QNX_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_కిటికీ_దత్తాంశం       *impl;
    SDL_VideoDisplay     *display = ఖాళీ;
    SDL_Display_దత్తాంశం      *display_దత్తాంశం = ఖాళీ;
    SDL_Display_బహుళకం_దత్తాంశం  *display_బహుళకం_దత్తాంశం = ఖాళీ;

    పూర్ణాంకం             కొలత[2];
    పూర్ణాంకం             position[2];
    పూర్ణాంకం             numbufs;
    పూర్ణాంకం             format;
    పూర్ణాంకం             usage;
    పూర్ణాంకం             has_focus_i;

    impl = SDL_calloc(1, పరిమాణం(*impl));
    ఒకవేళ (!impl) {
        తిరిగి false;
    }
    కిటికీ->అంతర్గత = impl;

    // Create a native window.
    ఒకవేళ (screen_create_కిటికీ(&impl->కిటికీ, context) < 0) {
        వెళ్ళు fail;
    }

    // Set the native window's size to match the SDL window.
    కొలత[0] = కిటికీ->w;
    కొలత[1] = కిటికీ->h;
    position[0] = కిటికీ->x;
    position[1] = కిటికీ->y;

    ఒకవేళ (screen_సమితి_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_కొలత, కొలత) < 0) {
        వెళ్ళు fail;
    }

    ఒకవేళ (screen_సమితి_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_ఆధారం_కొలత, కొలత) < 0) {
        వెళ్ళు fail;
    }

    ఒకవేళ (screen_సమితి_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_POSITION, position) < 0) {
        వెళ్ళు fail;
    }

    display = SDL_Get_Video_Display_For_కిటికీ(కిటికీ);
    SDL_assert(display != ఖాళీ);
    SDL_assert(display->desktop_బహుళకం.అంతర్గత != ఖాళీ);
    display_బహుళకం_దత్తాంశం = display->desktop_బహుళకం.అంతర్గత;

    // Create window buffer(s).
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        ఒకవేళ (screen_సమితి_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            వెళ్ళు fail;
        }
    } లేకపోతే {
        numbufs = 1;
    }

    // Create buffer(s).
    ఒకవేళ (screen_create_కిటికీ_buffers(impl->కిటికీ, numbufs>0?numbufs:1) < 0) {
        వెళ్ళు fail;
    }

    // Initialize EGL surface.
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, కిటికీ, (Native_కిటికీ_Type)impl->కిటికీ);
        ఒకవేళ (impl->egl_surface == EGL_NO_SURFACE) {
            వెళ్ళు fail;
        }
        SDL_సమితి_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_QNX_SURFACE_సూచిక, impl->egl_surface);
    }

    ఒకవేళ (screen_get_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_బహుళకం_దత్తాంశం->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_బహుళకం.format = screen_గమ్యం_Pixel_Format(format);
    display_బహుళకం_దత్తాంశం->screen_format = format;

    display_దత్తాంశం = display->అంతర్గత;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_దత్తాంశం != ఖాళీ);

    // Get initial focus state. Fallback to true.
    ఒకవేళ(screen_get_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } లేకపోతే {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_సమితి_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_QNX_కిటికీ_సూచిక, impl->కిటికీ);

    తిరిగి true;

fail:
    ఒకవేళ (impl->కిటికీ) {
        screen_destroy_కిటికీ(impl->కిటికీ);
    }
    ఒకవేళ (display_దత్తాంశం) {
        SDL_free(display_దత్తాంశం);
        display->అంతర్గత = ఖాళీ;
    }

    SDL_free(impl);
    కిటికీ->అంతర్గత = ఖాళీ;
    తిరిగి false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
స్థిర bool QNX_Create_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ, SDL_PixelFormat * format,
                        శూన్య ** pixels, పూర్ణాంకం *pitch)
{
    పూర్ణాంకం              బఫరు_లెక్క_2;
    SDL_కిటికీ_దత్తాంశం   *impl = (SDL_కిటికీ_దత్తాంశం *)కిటికీ->అంతర్గత;
    screen_బఫరు_t  *బఫరు_2;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_కిటికీ(కిటికీ);

    ఒకవేళ (screen_get_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_బఫరు_లెక్క, &బఫరు_లెక్క_2) < 0) {
        తిరిగి false;
    }
    బఫరు_2 = SDL_calloc(బఫరు_లెక్క_2, పరిమాణం(screen_బఫరు_t));

    // Get a pointer to the buffer's memory.
    ఒకవేళ (screen_get_కిటికీ_property_pv(impl->కిటికీ, SCREEN_PROPERTY_BUFFERS, (శూన్య **)బఫరు_2) < 0) {
        తిరిగి false;
    }

    ఒకవేళ (screen_get_బఫరు_property_pv(*బఫరు_2, SCREEN_PROPERTY_సూచిక, pixels) < 0) {
        తిరిగి false;
    }

    // Set format and pitch.
    ఒకవేళ (screen_get_బఫరు_property_iv(*బఫరు_2, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        తిరిగి false;
    }

    *format = display->desktop_బహుళకం.format;
    తిరిగి true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
స్థిర bool QNX_Update_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rects,
                        పూర్ణాంకం numrects)
{
    పూర్ణాంకం బఫరు_లెక్క_2, *rects_int;
    SDL_కిటికీ_దత్తాంశం   *impl = (SDL_కిటికీ_దత్తాంశం *)కిటికీ->అంతర్గత;
    screen_బఫరు_t *బఫరు_2;

    ఒకవేళ (screen_get_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_బఫరు_లెక్క, &బఫరు_లెక్క_2) < 0) {
        తిరిగి false;
    }
    బఫరు_2 = SDL_calloc(బఫరు_లెక్క_2, పరిమాణం(screen_బఫరు_t));

    ఒకవేళ (screen_get_కిటికీ_property_pv(impl->కిటికీ, SCREEN_PROPERTY_BUFFERS, (శూన్య **)బఫరు_2) < 0) {
        తిరిగి false;
    }

    ఒకవేళ(numrects>0){
        rects_int = SDL_calloc(4*numrects, పరిమాణం(పూర్ణాంకం));

        కొరకు(పూర్ణాంకం i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        ఒకవేళ(screen_post_కిటికీ(impl->కిటికీ, బఫరు_2[0], numrects, rects_int, 0)) {
            తిరిగి false;
        }
        ఒకవేళ(screen_flush_context(context, 0)) {
            తిరిగి false;
        }
    }
    తిరిగి true;
}

స్థిర SDL_Fullscreen_ఫలితం QNX_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = కిటికీ->అంతర్గత;
    పూర్ణాంకం కొలత[2] = { 0, 0 };
    పూర్ణాంకం position[2] = { 0, 0 };

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) && !fullscreen) {
        తిరిగి SDL_FULLSCREEN_SUCCEEDED;
    }

    ఒకవేళ (fullscreen) {
        SDL_Rect bounds;

        ఒకవేళ (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            తిరిగి SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        కొలత[0] = bounds.w;
        కొలత[1] = bounds.h;
    } లేకపోతే {
        position[0] = కిటికీ->x;
        position[1] = కిటికీ->y;
        కొలత[0] = కిటికీ->w;
        కొలత[1] = కిటికీ->h;
    }

    ఒకవేళ (screen_సమితి_కిటికీ_property_iv(కిటికీ_దత్తాంశం_2->కిటికీ, SCREEN_PROPERTY_కొలత, కొలత) < 0) {
        తిరిగి SDL_FULLSCREEN_FAILED;
    }

    ఒకవేళ (screen_సమితి_కిటికీ_property_iv(కిటికీ_దత్తాంశం_2->కిటికీ, SCREEN_PROPERTY_ఆధారం_కొలత, కొలత) < 0) {
        తిరిగి SDL_FULLSCREEN_FAILED;
    }

    ఒకవేళ (screen_సమితి_కిటికీ_property_iv(కిటికీ_దత్తాంశం_2->కిటికీ, SCREEN_PROPERTY_POSITION, position) < 0) {
        తిరిగి SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_కిటికీ_Event(కిటికీ, fullscreen ? SDL_EVENT_కిటికీ_ENTER_FULLSCREEN : SDL_EVENT_కిటికీ_LEAVE_FULLSCREEN, 0, 0);

    తిరిగి SDL_FULLSCREEN_SUCCEEDED;
}

స్థిర SDL_DisplayID QNX_Get_Display_For_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_కిటికీ_దత్తాంశం  *impl = (SDL_కిటికీ_దత్తాంశం *)కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *display_దత్తాంశం;

    screen_display_t screen_display;

    ఒకవేళ (impl == ఖాళీ) {
        తిరిగి 0;
    }

    ఒకవేళ (screen_get_కిటికీ_property_pv(impl->కిటికీ, SCREEN_PROPERTY_DISPLAY, (శూన్య **)&screen_display) < 0) {
        తిరిగి 0;
    }

    కొరకు (పూర్ణాంకం i = 0; i < _this->అంకె_displays; i++) {
        display_దత్తాంశం = _this->displays[i]->అంతర్గత;
        ఒకవేళ (display_దత్తాంశం && (display_దత్తాంశం->screen_display == screen_display)) {
            తిరిగి _this->displays[i]->id;
        }
    }

    తిరిగి 0;
}

/**
 * Runs the main event loop.
 */
స్థిర శూన్య QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_కిటికీ      *కిటికీ;
    SDL_కిటికీ_దత్తాంశం   *impl;
    పూర్ణాంకం             type;
    పూర్ణాంకం             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    కొరకు (కిటికీ = _this->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
        impl = (SDL_కిటికీ_దత్తాంశం *)కిటికీ->అంతర్గత;
        ఒకవేళ (screen_get_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            కొనసాగు;
        }
        has_focus = (bool)has_focus_i;

        ఒకవేళ (impl->has_focus != has_focus) {
            SDL_Send_కిటికీ_Event(కిటికీ, (has_focus ? SDL_EVENT_కిటికీ_FOCUS_GAINED : SDL_EVENT_కిటికీ_FOCUS_కోల్పోయిన), 0, 0);
            SDL_Send_కిటికీ_Event(కిటికీ, (has_focus ? SDL_EVENT_కిటికీ_MOUSE_ENTER : SDL_EVENT_కిటికీ_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_సమితి_Mouse_Focus(కిటికీ);
            SDL_సమితి_Keyboard_Focus(కిటికీ);
        }
    }

    కొరకు (;;) {
        ఒకవేళ (screen_get_event(context, event, 0) < 0) {
            ఆపు;
        }

        ఒకవేళ (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            ఆపు;
        }

        ఒకవేళ (type == SCREEN_EVENT_NONE) {
            ఆపు;
        }

        ఎంపిక (type) {
        స్థితి SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            ఆపు;

        స్థితి SCREEN_EVENT_సూచిక:
            handle_సూచిక_Event(event);
            ఆపు;

        అప్రమేయ:
            ఆపు;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
స్థిర శూన్య QNX_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం   *impl = (SDL_కిటికీ_దత్తాంశం *)కిటికీ->అంతర్గత;
    పూర్ణాంకం             కొలత[2];

    కొలత[0] = కిటికీ->pending.w;
    కొలత[1] = కిటికీ->pending.h;

    ఒకవేళ (!(కిటికీ->flags & (SDL_కిటికీ_FULLSCREEN | SDL_కిటికీ_MAXIMIZED))) {
        ఒకవేళ (screen_destroy_కిటికీ_buffers(impl->కిటికీ) < 0) {
            తిరిగి;
        }
        impl->resize = true;

        screen_సమితి_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_కొలత, కొలత);
        screen_సమితి_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_ఆధారం_కొలత, కొలత);

        screen_create_కిటికీ_buffers(impl->కిటికీ, (కిటికీ->flags & SDL_కిటికీ_OPENGL) ? 2 : 1);
    } లేకపోతే {
        కిటికీ->చివరి_కొలత_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
స్థిర శూన్య QNX_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం   *impl = (SDL_కిటికీ_దత్తాంశం *)కిటికీ->అంతర్గత;
    స్థిరరాశి పూర్ణాంకం       visible = 1;

    screen_సమితి_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
స్థిర శూన్య QNX_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం   *impl = (SDL_కిటికీ_దత్తాంశం *)కిటికీ->అంతర్గత;
    స్థిరరాశి పూర్ణాంకం       visible = 0;

    screen_సమితి_కిటికీ_property_iv(impl->కిటికీ, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
స్థిర శూన్య QNX_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం   *impl = (SDL_కిటికీ_దత్తాంశం *)కిటికీ->అంతర్గత;

    ఒకవేళ (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_కిటికీ(impl->కిటికీ);
        కిటికీ->అంతర్గత = ఖాళీ;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
స్థిర శూన్య QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
స్థిర SDL_VideoDevice *createDevice(శూన్య)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    device->అంతర్గత = ఖాళీ;
    device->VideoInit = QNX_VideoInit;
    device->VideoQuit = QNX_VideoQuit;
    device->CreateSDLWindow = QNX_Create_కిటికీ;
    device->Create_కిటికీ_Framebuffer = QNX_Create_కిటికీ_Framebuffer;
    device->Update_కిటికీ_Framebuffer = QNX_Update_కిటికీ_Framebuffer;
    device->సమితి_కిటికీ_కొలత = QNX_సమితి_కిటికీ_కొలత;
    device->సమితి_కిటికీ_Fullscreen = QNX_సమితి_కిటికీ_Fullscreen;
    device->Show_కిటికీ = QNX_Show_కిటికీ;
    device->Hide_కిటికీ = QNX_Hide_కిటికీ;
    device->Get_Display_For_కిటికీ = QNX_Get_Display_For_కిటికీ;
    device->GetDisplayBounds = QNX_GetDisplayBounds;
    device->GetDisplayModes = QNX_GetDisplayModes;
#ఒకవేళ 0
    device->సమితి_Display_బహుళకం = QNX_సమితి_Display_బహుళకం;
#అయితే_ముగింపు
    device->PumpEvents = QNX_PumpEvents;
    device->Destroy_కిటికీ = QNX_Destroy_కిటికీ;

    device->GL_ఎక్కించు_Library = QNX_GLES_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = QNX_GLES_Get_Proc_చిరునామా;
    device->GL_CreateContext = QNX_GLES_CreateContext;
    device->GL_సమితి_మార్పిడి_Interval = QNX_GLES_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = QNX_GLES_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = QNX_GLES_మార్పిడి_కిటికీ;
    device->GL_MakeCurrent = QNX_GLES_MakeCurrent;
    device->GL_DestroyContext = QNX_GLES_DeleteContext;
    device->GL_UnloadLibrary = QNX_GLES_UnloadLibrary;

    device->విడుదల = QNX_DeleteDevice;

    తిరిగి device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    ఖాళీ, // no ShowMessageBox implementation
    false
};
