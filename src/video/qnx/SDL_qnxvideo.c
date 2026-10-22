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
    SDL_Display_انکڑے      *display_انکڑے;
    SDL_Display_منوال      display_منوال_2;
    SDL_Display_منوال_انکڑے  *display_منوال_انکڑے;

    صحيح ناپ[2];
    صحيح اشاریہ;
    صحيح display_گنتی;
    صحيح سرگرم;

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
    إذا (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_گنتی, &display_گنتی) < 0) {
        أرجع false;
    }

    screen_display = SDL_calloc(display_گنتی, حجم(screen_display_t));
    إذا (screen_display == عدم) {
        أرجع false;
    }

    إذا (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (فراغ **)screen_display) < 0) {
        أرجع false;
    }

    /* create SDL displays based on display info from the screen API */
    لكل (اشاریہ = 0; اشاریہ < display_گنتی; اشاریہ++) {
        سرگرم = 0;
        إذا (screen_get_display_property_iv(screen_display[اشاریہ], SCREEN_PROPERTY_ATTACHED, &سرگرم) < 0) {
            SDL_free(screen_display);
            أرجع false;
        }

        إذا (سرگرم) {
            display_انکڑے = (SDL_Display_انکڑے *)SDL_calloc(1, حجم(SDL_Display_انکڑے));
            إذا (display_انکڑے == عدم) {
                SDL_free(screen_display);
                أرجع false;
            }
            SDL_zerop(display_انکڑے);

            إذا (screen_get_display_property_iv(screen_display[اشاریہ], SCREEN_PROPERTY_ناپ, ناپ) < 0) {
                SDL_free(screen_display);
                SDL_free(display_انکڑے);
                أرجع false;
            }

            display_منوال_انکڑے = (SDL_Display_منوال_انکڑے *)SDL_calloc(1, حجم(SDL_Display_منوال_انکڑے));
            إذا (display_منوال_انکڑے == عدم) {
                SDL_free(screen_display);
                SDL_free(display_انکڑے);
                أرجع false;
            }
            SDL_zerop(display_منوال_انکڑے);

            SDL_zero(display);
            SDL_zero(display_منوال_2);

            display_انکڑے->screen_display = screen_display[اشاریہ];
            display.اندرونی = (فراغ *)display_انکڑے;

            display_منوال_2.w = ناپ[0];
            display_منوال_2.h = ناپ[1];
            display_منوال_2.refresh_شرح = 60;
            display_منوال_2.pixel_density = 1.0;
            display_منوال_2.اندرونی = display_منوال_انکڑے;
            // This is assigned later when the window is created. For now, use a
            // safe guess.
            display_منوال_2.format = SDL_PIXELFORMAT_RGBX8888;
            display_منوال_انکڑے->screen_format = SCREEN_FORMAT_RGBX8888;
            // Be able to revert to the default display mode despite not having
            // the actual object to refer to.
            display_منوال_انکڑے->screen_display_منوال.اشاریہ = SCREEN_DISPLAY_منوال_PREFERRED_اشاریہ;

            // Added to current_mode when the display is added.
            display.desktop_منوال = display_منوال_2;

            إذا (!SDL_جوڑو_Video_Display(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_منوال_انکڑے);
                SDL_free(display_انکڑے);
                أرجع false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_جوڑو_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_جوڑو_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);

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
ساكن bool QNX_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_انکڑے       *impl;
    SDL_VideoDisplay     *display = عدم;
    SDL_Display_انکڑے      *display_انکڑے = عدم;
    SDL_Display_منوال_انکڑے  *display_منوال_انکڑے = عدم;

    صحيح             ناپ[2];
    صحيح             position[2];
    صحيح             numbufs;
    صحيح             format;
    صحيح             usage;
    صحيح             has_focus_i;

    impl = SDL_calloc(1, حجم(*impl));
    إذا (!impl) {
        أرجع false;
    }
    کھڑکی->اندرونی = impl;

    // Create a native window.
    إذا (screen_create_کھڑکی(&impl->کھڑکی, context) < 0) {
        اذهب fail;
    }

    // Set the native window's size to match the SDL window.
    ناپ[0] = کھڑکی->w;
    ناپ[1] = کھڑکی->h;
    position[0] = کھڑکی->x;
    position[1] = کھڑکی->y;

    إذا (screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_ناپ, ناپ) < 0) {
        اذهب fail;
    }

    إذا (screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_سروت_ناپ, ناپ) < 0) {
        اذهب fail;
    }

    إذا (screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_POSITION, position) < 0) {
        اذهب fail;
    }

    display = SDL_Get_Video_Display_For_کھڑکی(کھڑکی);
    SDL_assert(display != عدم);
    SDL_assert(display->desktop_منوال.اندرونی != عدم);
    display_منوال_انکڑے = display->desktop_منوال.اندرونی;

    // Create window buffer(s).
    إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        إذا (screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            اذهب fail;
        }
    } وإلا {
        numbufs = 1;
    }

    // Create buffer(s).
    إذا (screen_create_کھڑکی_buffers(impl->کھڑکی, numbufs>0?numbufs:1) < 0) {
        اذهب fail;
    }

    // Initialize EGL surface.
    إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)impl->کھڑکی);
        إذا (impl->egl_surface == EGL_NO_SURFACE) {
            اذهب fail;
        }
        SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_QNX_SURFACE_اشارہ_گر, impl->egl_surface);
    }

    إذا (screen_get_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_منوال_انکڑے->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_منوال.format = screen_منزل_Pixel_Format(format);
    display_منوال_انکڑے->screen_format = format;

    display_انکڑے = display->اندرونی;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_انکڑے != عدم);

    // Get initial focus state. Fallback to true.
    إذا(screen_get_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } وإلا {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_QNX_کھڑکی_اشارہ_گر, impl->کھڑکی);

    أرجع true;

fail:
    إذا (impl->کھڑکی) {
        screen_destroy_کھڑکی(impl->کھڑکی);
    }
    إذا (display_انکڑے) {
        SDL_free(display_انکڑے);
        display->اندرونی = عدم;
    }

    SDL_free(impl);
    کھڑکی->اندرونی = عدم;
    أرجع false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
ساكن bool QNX_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, SDL_PixelFormat * format,
                        فراغ ** pixels, صحيح *pitch)
{
    صحيح              بفر_گنتی_2;
    SDL_کھڑکی_انکڑے   *impl = (SDL_کھڑکی_انکڑے *)کھڑکی->اندرونی;
    screen_بفر_t  *بفر_2;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کھڑکی(کھڑکی);

    إذا (screen_get_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_بفر_گنتی, &بفر_گنتی_2) < 0) {
        أرجع false;
    }
    بفر_2 = SDL_calloc(بفر_گنتی_2, حجم(screen_بفر_t));

    // Get a pointer to the buffer's memory.
    إذا (screen_get_کھڑکی_property_pv(impl->کھڑکی, SCREEN_PROPERTY_BUFFERS, (فراغ **)بفر_2) < 0) {
        أرجع false;
    }

    إذا (screen_get_بفر_property_pv(*بفر_2, SCREEN_PROPERTY_اشارہ_گر, pixels) < 0) {
        أرجع false;
    }

    // Set format and pitch.
    إذا (screen_get_بفر_property_iv(*بفر_2, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        أرجع false;
    }

    *format = display->desktop_منوال.format;
    أرجع true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
ساكن bool QNX_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects,
                        صحيح numrects)
{
    صحيح بفر_گنتی_2, *rects_int;
    SDL_کھڑکی_انکڑے   *impl = (SDL_کھڑکی_انکڑے *)کھڑکی->اندرونی;
    screen_بفر_t *بفر_2;

    إذا (screen_get_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_بفر_گنتی, &بفر_گنتی_2) < 0) {
        أرجع false;
    }
    بفر_2 = SDL_calloc(بفر_گنتی_2, حجم(screen_بفر_t));

    إذا (screen_get_کھڑکی_property_pv(impl->کھڑکی, SCREEN_PROPERTY_BUFFERS, (فراغ **)بفر_2) < 0) {
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

        إذا(screen_post_کھڑکی(impl->کھڑکی, بفر_2[0], numrects, rects_int, 0)) {
            أرجع false;
        }
        إذا(screen_flush_context(context, 0)) {
            أرجع false;
        }
    }
    أرجع true;
}

ساكن SDL_Fullscreen_نتیجہ QNX_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = کھڑکی->اندرونی;
    صحيح ناپ[2] = { 0, 0 };
    صحيح position[2] = { 0, 0 };

    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && !fullscreen) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (fullscreen) {
        SDL_Rect bounds;

        إذا (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            أرجع SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        ناپ[0] = bounds.w;
        ناپ[1] = bounds.h;
    } وإلا {
        position[0] = کھڑکی->x;
        position[1] = کھڑکی->y;
        ناپ[0] = کھڑکی->w;
        ناپ[1] = کھڑکی->h;
    }

    إذا (screen_سیٹ_کھڑکی_property_iv(کھڑکی_انکڑے_2->کھڑکی, SCREEN_PROPERTY_ناپ, ناپ) < 0) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    إذا (screen_سیٹ_کھڑکی_property_iv(کھڑکی_انکڑے_2->کھڑکی, SCREEN_PROPERTY_سروت_ناپ, ناپ) < 0) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    إذا (screen_سیٹ_کھڑکی_property_iv(کھڑکی_انکڑے_2->کھڑکی, SCREEN_PROPERTY_POSITION, position) < 0) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_کھڑکی_Event(کھڑکی, fullscreen ? SDL_EVENT_کھڑکی_ENTER_FULLSCREEN : SDL_EVENT_کھڑکی_LEAVE_FULLSCREEN, 0, 0);

    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

ساكن SDL_DisplayID QNX_Get_Display_For_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_کھڑکی_انکڑے  *impl = (SDL_کھڑکی_انکڑے *)کھڑکی->اندرونی;
    SDL_Display_انکڑے *display_انکڑے;

    screen_display_t screen_display;

    إذا (impl == عدم) {
        أرجع 0;
    }

    إذا (screen_get_کھڑکی_property_pv(impl->کھڑکی, SCREEN_PROPERTY_DISPLAY, (فراغ **)&screen_display) < 0) {
        أرجع 0;
    }

    لكل (صحيح i = 0; i < _this->عدد_displays; i++) {
        display_انکڑے = _this->displays[i]->اندرونی;
        إذا (display_انکڑے && (display_انکڑے->screen_display == screen_display)) {
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
    SDL_کھڑکی      *کھڑکی;
    SDL_کھڑکی_انکڑے   *impl;
    صحيح             type;
    صحيح             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    لكل (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        impl = (SDL_کھڑکی_انکڑے *)کھڑکی->اندرونی;
        إذا (screen_get_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            استمر;
        }
        has_focus = (bool)has_focus_i;

        إذا (impl->has_focus != has_focus) {
            SDL_Send_کھڑکی_Event(کھڑکی, (has_focus ? SDL_EVENT_کھڑکی_FOCUS_GAINED : SDL_EVENT_کھڑکی_FOCUS_گواچا), 0, 0);
            SDL_Send_کھڑکی_Event(کھڑکی, (has_focus ? SDL_EVENT_کھڑکی_MOUSE_ENTER : SDL_EVENT_کھڑکی_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_سیٹ_Mouse_Focus(کھڑکی);
            SDL_سیٹ_Keyboard_Focus(کھڑکی);
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

        حالة SCREEN_EVENT_اشارہ_گر:
            handle_اشارہ_گر_Event(event);
            اكسر;

        افتراضي:
            اكسر;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
ساكن فراغ QNX_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے   *impl = (SDL_کھڑکی_انکڑے *)کھڑکی->اندرونی;
    صحيح             ناپ[2];

    ناپ[0] = کھڑکی->pending.w;
    ناپ[1] = کھڑکی->pending.h;

    إذا (!(کھڑکی->flags & (SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_MAXIMIZED))) {
        إذا (screen_destroy_کھڑکی_buffers(impl->کھڑکی) < 0) {
            أرجع;
        }
        impl->resize = true;

        screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_ناپ, ناپ);
        screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_سروت_ناپ, ناپ);

        screen_create_کھڑکی_buffers(impl->کھڑکی, (کھڑکی->flags & SDL_کھڑکی_OPENGL) ? 2 : 1);
    } وإلا {
        کھڑکی->آخری_ناپ_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
ساكن فراغ QNX_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے   *impl = (SDL_کھڑکی_انکڑے *)کھڑکی->اندرونی;
    ثابت صحيح       visible = 1;

    screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
ساكن فراغ QNX_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے   *impl = (SDL_کھڑکی_انکڑے *)کھڑکی->اندرونی;
    ثابت صحيح       visible = 0;

    screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
ساكن فراغ QNX_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے   *impl = (SDL_کھڑکی_انکڑے *)کھڑکی->اندرونی;

    إذا (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_کھڑکی(impl->کھڑکی);
        کھڑکی->اندرونی = عدم;
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

    device->اندرونی = عدم;
    device->VideoInit = QNX_VideoInit;
    device->VideoQuit = QNX_VideoQuit;
    device->CreateSDLWindow = QNX_Create_کھڑکی;
    device->Create_کھڑکی_Framebuffer = QNX_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = QNX_Update_کھڑکی_Framebuffer;
    device->سیٹ_کھڑکی_ناپ = QNX_سیٹ_کھڑکی_ناپ;
    device->سیٹ_کھڑکی_Fullscreen = QNX_سیٹ_کھڑکی_Fullscreen;
    device->Show_کھڑکی = QNX_Show_کھڑکی;
    device->Hide_کھڑکی = QNX_Hide_کھڑکی;
    device->Get_Display_For_کھڑکی = QNX_Get_Display_For_کھڑکی;
    device->GetDisplayBounds = QNX_GetDisplayBounds;
    device->GetDisplayModes = QNX_GetDisplayModes;
#إذا 0
    device->سیٹ_Display_منوال = QNX_سیٹ_Display_منوال;
#جے_انت
    device->PumpEvents = QNX_PumpEvents;
    device->Destroy_کھڑکی = QNX_Destroy_کھڑکی;

    device->GL_لدو_Library = QNX_GLES_لدو_Library;
    device->GL_Get_Proc_پتہ = QNX_GLES_Get_Proc_پتہ;
    device->GL_CreateContext = QNX_GLES_CreateContext;
    device->GL_سیٹ_وٹاندرا_Interval = QNX_GLES_سیٹ_وٹاندرا_Interval;
    device->GL_Get_وٹاندرا_Interval = QNX_GLES_Get_وٹاندرا_Interval;
    device->GL_وٹاندرا_کھڑکی = QNX_GLES_وٹاندرا_کھڑکی;
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
