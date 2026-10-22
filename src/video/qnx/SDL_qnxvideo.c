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
    SDL_Display_داده      *display_داده;
    SDL_Display_نما      display_نما_2;
    SDL_Display_نما_داده  *display_نما_داده;

    صحيح اندازه[2];
    صحيح شاخص;
    صحيح display_شمار;
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
    إذا (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_شمار, &display_شمار) < 0) {
        أرجع false;
    }

    screen_display = SDL_calloc(display_شمار, حجم(screen_display_t));
    إذا (screen_display == عدم) {
        أرجع false;
    }

    إذا (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (فراغ **)screen_display) < 0) {
        أرجع false;
    }

    /* create SDL displays based on display info from the screen API */
    لكل (شاخص = 0; شاخص < display_شمار; شاخص++) {
        فعال = 0;
        إذا (screen_get_display_property_iv(screen_display[شاخص], SCREEN_PROPERTY_ATTACHED, &فعال) < 0) {
            SDL_free(screen_display);
            أرجع false;
        }

        إذا (فعال) {
            display_داده = (SDL_Display_داده *)SDL_calloc(1, حجم(SDL_Display_داده));
            إذا (display_داده == عدم) {
                SDL_free(screen_display);
                أرجع false;
            }
            SDL_zerop(display_داده);

            إذا (screen_get_display_property_iv(screen_display[شاخص], SCREEN_PROPERTY_اندازه, اندازه) < 0) {
                SDL_free(screen_display);
                SDL_free(display_داده);
                أرجع false;
            }

            display_نما_داده = (SDL_Display_نما_داده *)SDL_calloc(1, حجم(SDL_Display_نما_داده));
            إذا (display_نما_داده == عدم) {
                SDL_free(screen_display);
                SDL_free(display_داده);
                أرجع false;
            }
            SDL_zerop(display_نما_داده);

            SDL_zero(display);
            SDL_zero(display_نما_2);

            display_داده->screen_display = screen_display[شاخص];
            display.داخلی = (فراغ *)display_داده;

            display_نما_2.w = اندازه[0];
            display_نما_2.h = اندازه[1];
            display_نما_2.refresh_نرخ = 60;
            display_نما_2.pixel_density = 1.0;
            display_نما_2.داخلی = display_نما_داده;
            // This is assigned later when the window is created. For now, use a
            // safe guess.
            display_نما_2.format = SDL_PIXELFORMAT_RGBX8888;
            display_نما_داده->screen_format = SCREEN_FORMAT_RGBX8888;
            // Be able to revert to the default display mode despite not having
            // the actual object to refer to.
            display_نما_داده->screen_display_نما.شاخص = SCREEN_DISPLAY_نما_PREFERRED_شاخص;

            // Added to current_mode when the display is added.
            display.desktop_نما = display_نما_2;

            إذا (!SDL_جمع_کن_Video_Display(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_نما_داده);
                SDL_free(display_داده);
                أرجع false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_جمع_کن_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_جمع_کن_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);

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
ساكن bool QNX_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    SDL_پنجره_داده       *impl;
    SDL_VideoDisplay     *display = عدم;
    SDL_Display_داده      *display_داده = عدم;
    SDL_Display_نما_داده  *display_نما_داده = عدم;

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
    پنجره->داخلی = impl;

    // Create a native window.
    إذا (screen_create_پنجره(&impl->پنجره, context) < 0) {
        اذهب fail;
    }

    // Set the native window's size to match the SDL window.
    اندازه[0] = پنجره->w;
    اندازه[1] = پنجره->h;
    position[0] = پنجره->x;
    position[1] = پنجره->y;

    إذا (screen_مجموعه_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_اندازه, اندازه) < 0) {
        اذهب fail;
    }

    إذا (screen_مجموعه_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_منبع_اندازه, اندازه) < 0) {
        اذهب fail;
    }

    إذا (screen_مجموعه_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_POSITION, position) < 0) {
        اذهب fail;
    }

    display = SDL_Get_Video_Display_For_پنجره(پنجره);
    SDL_assert(display != عدم);
    SDL_assert(display->desktop_نما.داخلی != عدم);
    display_نما_داده = display->desktop_نما.داخلی;

    // Create window buffer(s).
    إذا (پنجره->flags & SDL_پنجره_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        إذا (screen_مجموعه_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            اذهب fail;
        }
    } وإلا {
        numbufs = 1;
    }

    // Create buffer(s).
    إذا (screen_create_پنجره_buffers(impl->پنجره, numbufs>0?numbufs:1) < 0) {
        اذهب fail;
    }

    // Initialize EGL surface.
    إذا (پنجره->flags & SDL_پنجره_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, پنجره, (Native_پنجره_Type)impl->پنجره);
        إذا (impl->egl_surface == EGL_NO_SURFACE) {
            اذهب fail;
        }
        SDL_مجموعه_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), SDL_PROP_پنجره_QNX_SURFACE_اشاره_گر, impl->egl_surface);
    }

    إذا (screen_get_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_نما_داده->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_نما.format = screen_مقصد_Pixel_Format(format);
    display_نما_داده->screen_format = format;

    display_داده = display->داخلی;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_داده != عدم);

    // Get initial focus state. Fallback to true.
    إذا(screen_get_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } وإلا {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_مجموعه_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), SDL_PROP_پنجره_QNX_پنجره_اشاره_گر, impl->پنجره);

    أرجع true;

fail:
    إذا (impl->پنجره) {
        screen_destroy_پنجره(impl->پنجره);
    }
    إذا (display_داده) {
        SDL_free(display_داده);
        display->داخلی = عدم;
    }

    SDL_free(impl);
    پنجره->داخلی = عدم;
    أرجع false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
ساكن bool QNX_Create_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره * پنجره, SDL_PixelFormat * format,
                        فراغ ** pixels, صحيح *pitch)
{
    صحيح              میانگیر_شمار_2;
    SDL_پنجره_داده   *impl = (SDL_پنجره_داده *)پنجره->داخلی;
    screen_میانگیر_t  *میانگیر_2;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_پنجره(پنجره);

    إذا (screen_get_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_میانگیر_شمار, &میانگیر_شمار_2) < 0) {
        أرجع false;
    }
    میانگیر_2 = SDL_calloc(میانگیر_شمار_2, حجم(screen_میانگیر_t));

    // Get a pointer to the buffer's memory.
    إذا (screen_get_پنجره_property_pv(impl->پنجره, SCREEN_PROPERTY_BUFFERS, (فراغ **)میانگیر_2) < 0) {
        أرجع false;
    }

    إذا (screen_get_میانگیر_property_pv(*میانگیر_2, SCREEN_PROPERTY_اشاره_گر, pixels) < 0) {
        أرجع false;
    }

    // Set format and pitch.
    إذا (screen_get_میانگیر_property_iv(*میانگیر_2, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        أرجع false;
    }

    *format = display->desktop_نما.format;
    أرجع true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
ساكن bool QNX_Update_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره, ثابت SDL_Rect *rects,
                        صحيح numrects)
{
    صحيح میانگیر_شمار_2, *rects_int;
    SDL_پنجره_داده   *impl = (SDL_پنجره_داده *)پنجره->داخلی;
    screen_میانگیر_t *میانگیر_2;

    إذا (screen_get_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_میانگیر_شمار, &میانگیر_شمار_2) < 0) {
        أرجع false;
    }
    میانگیر_2 = SDL_calloc(میانگیر_شمار_2, حجم(screen_میانگیر_t));

    إذا (screen_get_پنجره_property_pv(impl->پنجره, SCREEN_PROPERTY_BUFFERS, (فراغ **)میانگیر_2) < 0) {
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

        إذا(screen_post_پنجره(impl->پنجره, میانگیر_2[0], numrects, rects_int, 0)) {
            أرجع false;
        }
        إذا(screen_flush_context(context, 0)) {
            أرجع false;
        }
    }
    أرجع true;
}

ساكن SDL_Fullscreen_نتیجه QNX_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_پنجره_داده *پنجره_داده_2 = پنجره->داخلی;
    صحيح اندازه[2] = { 0, 0 };
    صحيح position[2] = { 0, 0 };

    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN) && !fullscreen) {
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
        position[0] = پنجره->x;
        position[1] = پنجره->y;
        اندازه[0] = پنجره->w;
        اندازه[1] = پنجره->h;
    }

    إذا (screen_مجموعه_پنجره_property_iv(پنجره_داده_2->پنجره, SCREEN_PROPERTY_اندازه, اندازه) < 0) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    إذا (screen_مجموعه_پنجره_property_iv(پنجره_داده_2->پنجره, SCREEN_PROPERTY_منبع_اندازه, اندازه) < 0) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    إذا (screen_مجموعه_پنجره_property_iv(پنجره_داده_2->پنجره, SCREEN_PROPERTY_POSITION, position) < 0) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_پنجره_Event(پنجره, fullscreen ? SDL_EVENT_پنجره_ENTER_FULLSCREEN : SDL_EVENT_پنجره_LEAVE_FULLSCREEN, 0, 0);

    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

ساكن SDL_DisplayID QNX_Get_Display_For_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_پنجره_داده  *impl = (SDL_پنجره_داده *)پنجره->داخلی;
    SDL_Display_داده *display_داده;

    screen_display_t screen_display;

    إذا (impl == عدم) {
        أرجع 0;
    }

    إذا (screen_get_پنجره_property_pv(impl->پنجره, SCREEN_PROPERTY_DISPLAY, (فراغ **)&screen_display) < 0) {
        أرجع 0;
    }

    لكل (صحيح i = 0; i < _this->رقم_displays; i++) {
        display_داده = _this->displays[i]->داخلی;
        إذا (display_داده && (display_داده->screen_display == screen_display)) {
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
    SDL_پنجره      *پنجره;
    SDL_پنجره_داده   *impl;
    صحيح             type;
    صحيح             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    لكل (پنجره = _this->windows; پنجره; پنجره = پنجره->بعدی) {
        impl = (SDL_پنجره_داده *)پنجره->داخلی;
        إذا (screen_get_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            استمر;
        }
        has_focus = (bool)has_focus_i;

        إذا (impl->has_focus != has_focus) {
            SDL_Send_پنجره_Event(پنجره, (has_focus ? SDL_EVENT_پنجره_FOCUS_GAINED : SDL_EVENT_پنجره_FOCUS_گمشده), 0, 0);
            SDL_Send_پنجره_Event(پنجره, (has_focus ? SDL_EVENT_پنجره_MOUSE_ENTER : SDL_EVENT_پنجره_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_مجموعه_Mouse_Focus(پنجره);
            SDL_مجموعه_Keyboard_Focus(پنجره);
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

        حالة SCREEN_EVENT_اشاره_گر:
            handle_اشاره_گر_Event(event);
            اكسر;

        افتراضي:
            اكسر;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
ساكن فراغ QNX_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده   *impl = (SDL_پنجره_داده *)پنجره->داخلی;
    صحيح             اندازه[2];

    اندازه[0] = پنجره->pending.w;
    اندازه[1] = پنجره->pending.h;

    إذا (!(پنجره->flags & (SDL_پنجره_FULLSCREEN | SDL_پنجره_MAXIMIZED))) {
        إذا (screen_destroy_پنجره_buffers(impl->پنجره) < 0) {
            أرجع;
        }
        impl->resize = true;

        screen_مجموعه_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_اندازه, اندازه);
        screen_مجموعه_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_منبع_اندازه, اندازه);

        screen_create_پنجره_buffers(impl->پنجره, (پنجره->flags & SDL_پنجره_OPENGL) ? 2 : 1);
    } وإلا {
        پنجره->آخرین_اندازه_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
ساكن فراغ QNX_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده   *impl = (SDL_پنجره_داده *)پنجره->داخلی;
    ثابت صحيح       visible = 1;

    screen_مجموعه_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
ساكن فراغ QNX_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده   *impl = (SDL_پنجره_داده *)پنجره->داخلی;
    ثابت صحيح       visible = 0;

    screen_مجموعه_پنجره_property_iv(impl->پنجره, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
ساكن فراغ QNX_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده   *impl = (SDL_پنجره_داده *)پنجره->داخلی;

    إذا (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_پنجره(impl->پنجره);
        پنجره->داخلی = عدم;
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

    device->داخلی = عدم;
    device->VideoInit = QNX_VideoInit;
    device->VideoQuit = QNX_VideoQuit;
    device->CreateSDLWindow = QNX_Create_پنجره;
    device->Create_پنجره_Framebuffer = QNX_Create_پنجره_Framebuffer;
    device->Update_پنجره_Framebuffer = QNX_Update_پنجره_Framebuffer;
    device->مجموعه_پنجره_اندازه = QNX_مجموعه_پنجره_اندازه;
    device->مجموعه_پنجره_Fullscreen = QNX_مجموعه_پنجره_Fullscreen;
    device->Show_پنجره = QNX_Show_پنجره;
    device->Hide_پنجره = QNX_Hide_پنجره;
    device->Get_Display_For_پنجره = QNX_Get_Display_For_پنجره;
    device->GetDisplayBounds = QNX_GetDisplayBounds;
    device->GetDisplayModes = QNX_GetDisplayModes;
#إذا 0
    device->مجموعه_Display_نما = QNX_مجموعه_Display_نما;
#پایان_اگر
    device->PumpEvents = QNX_PumpEvents;
    device->Destroy_پنجره = QNX_Destroy_پنجره;

    device->GL_بارگیری_Library = QNX_GLES_بارگیری_Library;
    device->GL_Get_Proc_آدرس = QNX_GLES_Get_Proc_آدرس;
    device->GL_CreateContext = QNX_GLES_CreateContext;
    device->GL_مجموعه_جابجا_Interval = QNX_GLES_مجموعه_جابجا_Interval;
    device->GL_Get_جابجا_Interval = QNX_GLES_Get_جابجا_Interval;
    device->GL_جابجا_پنجره = QNX_GLES_جابجا_پنجره;
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
