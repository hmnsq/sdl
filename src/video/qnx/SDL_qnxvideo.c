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
    SDL_Display_معلومات      *display_معلومات;
    SDL_Display_ډېرپېښ      display_ډېرپېښ_2;
    SDL_Display_ډېرپېښ_معلومات  *display_ډېرپېښ_معلومات;

    صحيح اندازه[2];
    صحيح شاخص;
    صحيح display_شمېر;
    صحيح فعال;

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
    إذا (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_شمېر, &display_شمېر) < 0) {
        أرجع false;
    }

    screen_display = SDL_calloc(display_شمېر, حجم(screen_display_t));
    إذا (screen_display == عدم) {
        أرجع false;
    }

    إذا (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (فراغ **)screen_display) < 0) {
        أرجع false;
    }

    /* create SDL displays based on display info from the screen API */
    لكل (شاخص = 0; شاخص < display_شمېر; شاخص++) {
        فعال = 0;
        إذا (screen_get_display_property_iv(screen_display[شاخص], SCREEN_PROPERTY_ATTACHED, &فعال) < 0) {
            SDL_free(screen_display);
            أرجع false;
        }

        إذا (فعال) {
            display_معلومات = (SDL_Display_معلومات *)SDL_calloc(1, حجم(SDL_Display_معلومات));
            إذا (display_معلومات == عدم) {
                SDL_free(screen_display);
                أرجع false;
            }
            SDL_zerop(display_معلومات);

            إذا (screen_get_display_property_iv(screen_display[شاخص], SCREEN_PROPERTY_اندازه, اندازه) < 0) {
                SDL_free(screen_display);
                SDL_free(display_معلومات);
                أرجع false;
            }

            display_ډېرپېښ_معلومات = (SDL_Display_ډېرپېښ_معلومات *)SDL_calloc(1, حجم(SDL_Display_ډېرپېښ_معلومات));
            إذا (display_ډېرپېښ_معلومات == عدم) {
                SDL_free(screen_display);
                SDL_free(display_معلومات);
                أرجع false;
            }
            SDL_zerop(display_ډېرپېښ_معلومات);

            SDL_zero(display);
            SDL_zero(display_ډېرپېښ_2);

            display_معلومات->screen_display = screen_display[شاخص];
            display.دننی = (فراغ *)display_معلومات;

            display_ډېرپېښ_2.w = اندازه[0];
            display_ډېرپېښ_2.h = اندازه[1];
            display_ډېرپېښ_2.refresh_شرح = 60;
            display_ډېرپېښ_2.pixel_density = 1.0;
            display_ډېرپېښ_2.دننی = display_ډېرپېښ_معلومات;
            // This is assigned later when the window is created. For now, use a
            // safe guess.
            display_ډېرپېښ_2.format = SDL_PIXELFORMAT_RGBX8888;
            display_ډېرپېښ_معلومات->screen_format = SCREEN_FORMAT_RGBX8888;
            // Be able to revert to the default display mode despite not having
            // the actual object to refer to.
            display_ډېرپېښ_معلومات->screen_display_ډېرپېښ.شاخص = SCREEN_DISPLAY_ډېرپېښ_PREFERRED_شاخص;

            // Added to current_mode when the display is added.
            display.desktop_ډېرپېښ = display_ډېرپېښ_2;

            إذا (!SDL_جمع_کړه_Video_Display(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_ډېرپېښ_معلومات);
                SDL_free(display_معلومات);
                أرجع false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_جمع_کړه_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_جمع_کړه_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);

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
ساكن bool QNX_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    SDL_کړکۍ_معلومات       *impl;
    SDL_VideoDisplay     *display = عدم;
    SDL_Display_معلومات      *display_معلومات = عدم;
    SDL_Display_ډېرپېښ_معلومات  *display_ډېرپېښ_معلومات = عدم;

    صحيح             اندازه[2];
    صحيح             position[2];
    صحيح             numbufs;
    صحيح             format;
    صحيح             usage;
    صحيح             has_focus_i;

    impl = SDL_calloc(1, حجم(*impl));
    إذا (!impl) {
        أرجع false;
    }
    کړکۍ->دننی = impl;

    // Create a native window.
    إذا (screen_create_کړکۍ(&impl->کړکۍ, context) < 0) {
        اذهب fail;
    }

    // Set the native window's size to match the SDL window.
    اندازه[0] = کړکۍ->w;
    اندازه[1] = کړکۍ->h;
    position[0] = کړکۍ->x;
    position[1] = کړکۍ->y;

    إذا (screen_سېټ_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_اندازه, اندازه) < 0) {
        اذهب fail;
    }

    إذا (screen_سېټ_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_سرچینه_اندازه, اندازه) < 0) {
        اذهب fail;
    }

    إذا (screen_سېټ_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_POSITION, position) < 0) {
        اذهب fail;
    }

    display = SDL_Get_Video_Display_For_کړکۍ(کړکۍ);
    SDL_assert(display != عدم);
    SDL_assert(display->desktop_ډېرپېښ.دننی != عدم);
    display_ډېرپېښ_معلومات = display->desktop_ډېرپېښ.دننی;

    // Create window buffer(s).
    إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        إذا (screen_سېټ_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            اذهب fail;
        }
    } وإلا {
        numbufs = 1;
    }

    // Create buffer(s).
    إذا (screen_create_کړکۍ_buffers(impl->کړکۍ, numbufs>0?numbufs:1) < 0) {
        اذهب fail;
    }

    // Initialize EGL surface.
    إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, کړکۍ, (Native_کړکۍ_Type)impl->کړکۍ);
        إذا (impl->egl_surface == EGL_NO_SURFACE) {
            اذهب fail;
        }
        SDL_سېټ_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_QNX_SURFACE_اشاره_ګر, impl->egl_surface);
    }

    إذا (screen_get_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_ډېرپېښ_معلومات->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_ډېرپېښ.format = screen_منزل_Pixel_Format(format);
    display_ډېرپېښ_معلومات->screen_format = format;

    display_معلومات = display->دننی;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_معلومات != عدم);

    // Get initial focus state. Fallback to true.
    إذا(screen_get_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } وإلا {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_سېټ_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_QNX_کړکۍ_اشاره_ګر, impl->کړکۍ);

    أرجع true;

fail:
    إذا (impl->کړکۍ) {
        screen_destroy_کړکۍ(impl->کړکۍ);
    }
    إذا (display_معلومات) {
        SDL_free(display_معلومات);
        display->دننی = عدم;
    }

    SDL_free(impl);
    کړکۍ->دننی = عدم;
    أرجع false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
ساكن bool QNX_Create_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ, SDL_PixelFormat * format,
                        فراغ ** pixels, صحيح *pitch)
{
    صحيح              بفر_شمېر_2;
    SDL_کړکۍ_معلومات   *impl = (SDL_کړکۍ_معلومات *)کړکۍ->دننی;
    screen_بفر_t  *بفر_2;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کړکۍ(کړکۍ);

    إذا (screen_get_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_بفر_شمېر, &بفر_شمېر_2) < 0) {
        أرجع false;
    }
    بفر_2 = SDL_calloc(بفر_شمېر_2, حجم(screen_بفر_t));

    // Get a pointer to the buffer's memory.
    إذا (screen_get_کړکۍ_property_pv(impl->کړکۍ, SCREEN_PROPERTY_BUFFERS, (فراغ **)بفر_2) < 0) {
        أرجع false;
    }

    إذا (screen_get_بفر_property_pv(*بفر_2, SCREEN_PROPERTY_اشاره_ګر, pixels) < 0) {
        أرجع false;
    }

    // Set format and pitch.
    إذا (screen_get_بفر_property_iv(*بفر_2, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        أرجع false;
    }

    *format = display->desktop_ډېرپېښ.format;
    أرجع true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
ساكن bool QNX_Update_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, ثابت SDL_Rect *rects,
                        صحيح numrects)
{
    صحيح بفر_شمېر_2, *rects_int;
    SDL_کړکۍ_معلومات   *impl = (SDL_کړکۍ_معلومات *)کړکۍ->دننی;
    screen_بفر_t *بفر_2;

    إذا (screen_get_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_بفر_شمېر, &بفر_شمېر_2) < 0) {
        أرجع false;
    }
    بفر_2 = SDL_calloc(بفر_شمېر_2, حجم(screen_بفر_t));

    إذا (screen_get_کړکۍ_property_pv(impl->کړکۍ, SCREEN_PROPERTY_BUFFERS, (فراغ **)بفر_2) < 0) {
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

        إذا(screen_post_کړکۍ(impl->کړکۍ, بفر_2[0], numrects, rects_int, 0)) {
            أرجع false;
        }
        إذا(screen_flush_context(context, 0)) {
            أرجع false;
        }
    }
    أرجع true;
}

ساكن SDL_Fullscreen_پایله QNX_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = کړکۍ->دننی;
    صحيح اندازه[2] = { 0, 0 };
    صحيح position[2] = { 0, 0 };

    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) && !fullscreen) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (fullscreen) {
        SDL_Rect bounds;

        إذا (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            أرجع SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        اندازه[0] = bounds.w;
        اندازه[1] = bounds.h;
    } وإلا {
        position[0] = کړکۍ->x;
        position[1] = کړکۍ->y;
        اندازه[0] = کړکۍ->w;
        اندازه[1] = کړکۍ->h;
    }

    إذا (screen_سېټ_کړکۍ_property_iv(کړکۍ_معلومات_2->کړکۍ, SCREEN_PROPERTY_اندازه, اندازه) < 0) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    إذا (screen_سېټ_کړکۍ_property_iv(کړکۍ_معلومات_2->کړکۍ, SCREEN_PROPERTY_سرچینه_اندازه, اندازه) < 0) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    إذا (screen_سېټ_کړکۍ_property_iv(کړکۍ_معلومات_2->کړکۍ, SCREEN_PROPERTY_POSITION, position) < 0) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_کړکۍ_Event(کړکۍ, fullscreen ? SDL_EVENT_کړکۍ_ENTER_FULLSCREEN : SDL_EVENT_کړکۍ_LEAVE_FULLSCREEN, 0, 0);

    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

ساكن SDL_DisplayID QNX_Get_Display_For_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_کړکۍ_معلومات  *impl = (SDL_کړکۍ_معلومات *)کړکۍ->دننی;
    SDL_Display_معلومات *display_معلومات;

    screen_display_t screen_display;

    إذا (impl == عدم) {
        أرجع 0;
    }

    إذا (screen_get_کړکۍ_property_pv(impl->کړکۍ, SCREEN_PROPERTY_DISPLAY, (فراغ **)&screen_display) < 0) {
        أرجع 0;
    }

    لكل (صحيح i = 0; i < _this->عدد_displays; i++) {
        display_معلومات = _this->displays[i]->دننی;
        إذا (display_معلومات && (display_معلومات->screen_display == screen_display)) {
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
    SDL_کړکۍ      *کړکۍ;
    SDL_کړکۍ_معلومات   *impl;
    صحيح             type;
    صحيح             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    لكل (کړکۍ = _this->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
        impl = (SDL_کړکۍ_معلومات *)کړکۍ->دننی;
        إذا (screen_get_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            استمر;
        }
        has_focus = (bool)has_focus_i;

        إذا (impl->has_focus != has_focus) {
            SDL_Send_کړکۍ_Event(کړکۍ, (has_focus ? SDL_EVENT_کړکۍ_FOCUS_GAINED : SDL_EVENT_کړکۍ_FOCUS_ورک), 0, 0);
            SDL_Send_کړکۍ_Event(کړکۍ, (has_focus ? SDL_EVENT_کړکۍ_MOUSE_ENTER : SDL_EVENT_کړکۍ_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_سېټ_Mouse_Focus(کړکۍ);
            SDL_سېټ_Keyboard_Focus(کړکۍ);
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

        حالة SCREEN_EVENT_اشاره_ګر:
            handle_اشاره_ګر_Event(event);
            اكسر;

        افتراضي:
            اكسر;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
ساكن فراغ QNX_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات   *impl = (SDL_کړکۍ_معلومات *)کړکۍ->دننی;
    صحيح             اندازه[2];

    اندازه[0] = کړکۍ->pending.w;
    اندازه[1] = کړکۍ->pending.h;

    إذا (!(کړکۍ->flags & (SDL_کړکۍ_FULLSCREEN | SDL_کړکۍ_MAXIMIZED))) {
        إذا (screen_destroy_کړکۍ_buffers(impl->کړکۍ) < 0) {
            أرجع;
        }
        impl->resize = true;

        screen_سېټ_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_اندازه, اندازه);
        screen_سېټ_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_سرچینه_اندازه, اندازه);

        screen_create_کړکۍ_buffers(impl->کړکۍ, (کړکۍ->flags & SDL_کړکۍ_OPENGL) ? 2 : 1);
    } وإلا {
        کړکۍ->وروستی_اندازه_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
ساكن فراغ QNX_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات   *impl = (SDL_کړکۍ_معلومات *)کړکۍ->دننی;
    ثابت صحيح       visible = 1;

    screen_سېټ_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
ساكن فراغ QNX_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات   *impl = (SDL_کړکۍ_معلومات *)کړکۍ->دننی;
    ثابت صحيح       visible = 0;

    screen_سېټ_کړکۍ_property_iv(impl->کړکۍ, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
ساكن فراغ QNX_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات   *impl = (SDL_کړکۍ_معلومات *)کړکۍ->دننی;

    إذا (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_کړکۍ(impl->کړکۍ);
        کړکۍ->دننی = عدم;
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

    device->دننی = عدم;
    device->VideoInit = QNX_VideoInit;
    device->VideoQuit = QNX_VideoQuit;
    device->CreateSDLWindow = QNX_Create_کړکۍ;
    device->Create_کړکۍ_Framebuffer = QNX_Create_کړکۍ_Framebuffer;
    device->Update_کړکۍ_Framebuffer = QNX_Update_کړکۍ_Framebuffer;
    device->سېټ_کړکۍ_اندازه = QNX_سېټ_کړکۍ_اندازه;
    device->سېټ_کړکۍ_Fullscreen = QNX_سېټ_کړکۍ_Fullscreen;
    device->Show_کړکۍ = QNX_Show_کړکۍ;
    device->Hide_کړکۍ = QNX_Hide_کړکۍ;
    device->Get_Display_For_کړکۍ = QNX_Get_Display_For_کړکۍ;
    device->GetDisplayBounds = QNX_GetDisplayBounds;
    device->GetDisplayModes = QNX_GetDisplayModes;
#إذا 0
    device->سېټ_Display_ډېرپېښ = QNX_سېټ_Display_ډېرپېښ;
#د_که_پای
    device->PumpEvents = QNX_PumpEvents;
    device->Destroy_کړکۍ = QNX_Destroy_کړکۍ;

    device->GL_بارول_Library = QNX_GLES_بارول_Library;
    device->GL_Get_Proc_پته = QNX_GLES_Get_Proc_پته;
    device->GL_CreateContext = QNX_GLES_CreateContext;
    device->GL_سېټ_بدلون_Interval = QNX_GLES_سېټ_بدلون_Interval;
    device->GL_Get_بدلون_Interval = QNX_GLES_Get_بدلون_Interval;
    device->GL_بدلون_کړکۍ = QNX_GLES_بدلون_کړکۍ;
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
