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

#شامل "SDL_internal.h"
#شامل "../SDL_sysvideo.h"
#شامل "../SDL_egl_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_windowevents_c.h"
#شامل "SDL_qnx.h"

#شامل <errno.h>

ساکن screen_context_t context;
ساکن screen_event_t   event;
ساکن bool video_initialized = false;

screen_context_t * getContext()
{
    واپس &context;
}

screen_event_t * getEvent()
{
    واپس &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
ساکن bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_Display_ڈیٹا      *display_ڈیٹا;
    SDL_Display_منوال      display_منوال_2;
    SDL_Display_منوال_ڈیٹا  *display_منوال_ڈیٹا;

    صحیح سائز[2];
    صحیح اشاریہ;
    صحیح display_گنتی;
    صحیح فعال;

    screen_display_t *screen_display;

    اگر (video_initialized) {
        واپس true;
    }

    اگر (screen_create_context(&context, 0) < 0) {
        واپس false;
    }

    اگر (screen_create_event(&event) < 0) {
        واپس false;
    }

    /* start with no displays and increment as attached displays are found */
    اگر (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_گنتی, &display_گنتی) < 0) {
        واپس false;
    }

    screen_display = SDL_calloc(display_گنتی, حجم(screen_display_t));
    اگر (screen_display == تہی) {
        واپس false;
    }

    اگر (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (خالی **)screen_display) < 0) {
        واپس false;
    }

    /* create SDL displays based on display info from the screen API */
    برائے (اشاریہ = 0; اشاریہ < display_گنتی; اشاریہ++) {
        فعال = 0;
        اگر (screen_get_display_property_iv(screen_display[اشاریہ], SCREEN_PROPERTY_ATTACHED, &فعال) < 0) {
            SDL_free(screen_display);
            واپس false;
        }

        اگر (فعال) {
            display_ڈیٹا = (SDL_Display_ڈیٹا *)SDL_calloc(1, حجم(SDL_Display_ڈیٹا));
            اگر (display_ڈیٹا == تہی) {
                SDL_free(screen_display);
                واپس false;
            }
            SDL_zerop(display_ڈیٹا);

            اگر (screen_get_display_property_iv(screen_display[اشاریہ], SCREEN_PROPERTY_سائز, سائز) < 0) {
                SDL_free(screen_display);
                SDL_free(display_ڈیٹا);
                واپس false;
            }

            display_منوال_ڈیٹا = (SDL_Display_منوال_ڈیٹا *)SDL_calloc(1, حجم(SDL_Display_منوال_ڈیٹا));
            اگر (display_منوال_ڈیٹا == تہی) {
                SDL_free(screen_display);
                SDL_free(display_ڈیٹا);
                واپس false;
            }
            SDL_zerop(display_منوال_ڈیٹا);

            SDL_zero(display);
            SDL_zero(display_منوال_2);

            display_ڈیٹا->screen_display = screen_display[اشاریہ];
            display.اندرونی_2 = (خالی *)display_ڈیٹا;

            display_منوال_2.w = سائز[0];
            display_منوال_2.h = سائز[1];
            display_منوال_2.refresh_شرح = 60;
            display_منوال_2.pixel_density = 1.0;
            display_منوال_2.اندرونی_2 = display_منوال_ڈیٹا;
            // This is assigned later when the window is created. For now, use a
            // safe guess.
            display_منوال_2.format = SDL_PIXELFORMAT_RGBX8888;
            display_منوال_ڈیٹا->screen_format = SCREEN_FORMAT_RGBX8888;
            // Be able to revert to the default display mode despite not having
            // the actual object to refer to.
            display_منوال_ڈیٹا->screen_display_منوال.اشاریہ = SCREEN_DISPLAY_منوال_PREFERRED_اشاریہ;

            // Added to current_mode when the display is added.
            display.desktop_منوال = display_منوال_2;

            اگر (!SDL_جوڑو_Video_Display(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_منوال_ڈیٹا);
                SDL_free(display_ڈیٹا);
                واپس false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_جوڑو_Keyboard(SDL_DEFAULT_KEYBOARD_ID, تہی);
    SDL_جوڑو_Mouse(SDL_DEFAULT_MOUSE_ID, تہی);

    video_initialized = true;

    SDL_free(screen_display);

    واپس true;
}

ساکن خالی QNX_VideoQuit(SDL_VideoDevice *_this)
{
    اگر (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
ساکن bool QNX_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_ڈیٹا       *impl;
    SDL_VideoDisplay     *display = تہی;
    SDL_Display_ڈیٹا      *display_ڈیٹا = تہی;
    SDL_Display_منوال_ڈیٹا  *display_منوال_ڈیٹا = تہی;

    صحیح             سائز[2];
    صحیح             position[2];
    صحیح             numbufs;
    صحیح             format;
    صحیح             usage;
    صحیح             has_focus_i;

    impl = SDL_calloc(1, حجم(*impl));
    اگر (!impl) {
        واپس false;
    }
    کھڑکی->اندرونی_2 = impl;

    // Create a native window.
    اگر (screen_create_کھڑکی(&impl->کھڑکی, context) < 0) {
        جاؤ fail;
    }

    // Set the native window's size to match the SDL window.
    سائز[0] = کھڑکی->w;
    سائز[1] = کھڑکی->h;
    position[0] = کھڑکی->x;
    position[1] = کھڑکی->y;

    اگر (screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_سائز, سائز) < 0) {
        جاؤ fail;
    }

    اگر (screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_ماخذ_سائز, سائز) < 0) {
        جاؤ fail;
    }

    اگر (screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_POSITION, position) < 0) {
        جاؤ fail;
    }

    display = SDL_Get_Video_Display_For_کھڑکی(کھڑکی);
    SDL_assert(display != تہی);
    SDL_assert(display->desktop_منوال.اندرونی_2 != تہی);
    display_منوال_ڈیٹا = display->desktop_منوال.اندرونی_2;

    // Create window buffer(s).
    اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        اگر (screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            جاؤ fail;
        }
    } ورنہ {
        numbufs = 1;
    }

    // Create buffer(s).
    اگر (screen_create_کھڑکی_buffers(impl->کھڑکی, numbufs>0?numbufs:1) < 0) {
        جاؤ fail;
    }

    // Initialize EGL surface.
    اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)impl->کھڑکی);
        اگر (impl->egl_surface == EGL_NO_SURFACE) {
            جاؤ fail;
        }
        SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_QNX_SURFACE_اشارہ_گر, impl->egl_surface);
    }

    اگر (screen_get_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_منوال_ڈیٹا->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_منوال.format = screen_مقصد_Pixel_Format(format);
    display_منوال_ڈیٹا->screen_format = format;

    display_ڈیٹا = display->اندرونی_2;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_ڈیٹا != تہی);

    // Get initial focus state. Fallback to true.
    اگر(screen_get_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } ورنہ {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_QNX_کھڑکی_اشارہ_گر, impl->کھڑکی);

    واپس true;

fail:
    اگر (impl->کھڑکی) {
        screen_destroy_کھڑکی(impl->کھڑکی);
    }
    اگر (display_ڈیٹا) {
        SDL_free(display_ڈیٹا);
        display->اندرونی_2 = تہی;
    }

    SDL_free(impl);
    کھڑکی->اندرونی_2 = تہی;
    واپس false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
ساکن bool QNX_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, SDL_PixelFormat * format,
                        خالی ** pixels, صحیح *pitch)
{
    صحیح              بفر_گنتی_2;
    SDL_کھڑکی_ڈیٹا   *impl = (SDL_کھڑکی_ڈیٹا *)کھڑکی->اندرونی_2;
    screen_بفر_t  *بفر_2;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کھڑکی(کھڑکی);

    اگر (screen_get_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_بفر_گنتی, &بفر_گنتی_2) < 0) {
        واپس false;
    }
    بفر_2 = SDL_calloc(بفر_گنتی_2, حجم(screen_بفر_t));

    // Get a pointer to the buffer's memory.
    اگر (screen_get_کھڑکی_property_pv(impl->کھڑکی, SCREEN_PROPERTY_BUFFERS, (خالی **)بفر_2) < 0) {
        واپس false;
    }

    اگر (screen_get_بفر_property_pv(*بفر_2, SCREEN_PROPERTY_اشارہ_گر, pixels) < 0) {
        واپس false;
    }

    // Set format and pitch.
    اگر (screen_get_بفر_property_iv(*بفر_2, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        واپس false;
    }

    *format = display->desktop_منوال.format;
    واپس true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
ساکن bool QNX_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects,
                        صحیح numrects)
{
    صحیح بفر_گنتی_2, *rects_int;
    SDL_کھڑکی_ڈیٹا   *impl = (SDL_کھڑکی_ڈیٹا *)کھڑکی->اندرونی_2;
    screen_بفر_t *بفر_2;

    اگر (screen_get_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_بفر_گنتی, &بفر_گنتی_2) < 0) {
        واپس false;
    }
    بفر_2 = SDL_calloc(بفر_گنتی_2, حجم(screen_بفر_t));

    اگر (screen_get_کھڑکی_property_pv(impl->کھڑکی, SCREEN_PROPERTY_BUFFERS, (خالی **)بفر_2) < 0) {
        واپس false;
    }

    اگر(numrects>0){
        rects_int = SDL_calloc(4*numrects, حجم(صحیح));

        برائے(صحیح i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        اگر(screen_post_کھڑکی(impl->کھڑکی, بفر_2[0], numrects, rects_int, 0)) {
            واپس false;
        }
        اگر(screen_flush_context(context, 0)) {
            واپس false;
        }
    }
    واپس true;
}

ساکن SDL_Fullscreen_نتیجہ QNX_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = کھڑکی->اندرونی_2;
    صحیح سائز[2] = { 0, 0 };
    صحیح position[2] = { 0, 0 };

    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && !fullscreen) {
        واپس SDL_FULLSCREEN_SUCCEEDED;
    }

    اگر (fullscreen) {
        SDL_Rect bounds;

        اگر (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            واپس SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        سائز[0] = bounds.w;
        سائز[1] = bounds.h;
    } ورنہ {
        position[0] = کھڑکی->x;
        position[1] = کھڑکی->y;
        سائز[0] = کھڑکی->w;
        سائز[1] = کھڑکی->h;
    }

    اگر (screen_سیٹ_کھڑکی_property_iv(کھڑکی_ڈیٹا_2->کھڑکی, SCREEN_PROPERTY_سائز, سائز) < 0) {
        واپس SDL_FULLSCREEN_FAILED;
    }

    اگر (screen_سیٹ_کھڑکی_property_iv(کھڑکی_ڈیٹا_2->کھڑکی, SCREEN_PROPERTY_ماخذ_سائز, سائز) < 0) {
        واپس SDL_FULLSCREEN_FAILED;
    }

    اگر (screen_سیٹ_کھڑکی_property_iv(کھڑکی_ڈیٹا_2->کھڑکی, SCREEN_PROPERTY_POSITION, position) < 0) {
        واپس SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_کھڑکی_Event(کھڑکی, fullscreen ? SDL_EVENT_کھڑکی_ENTER_FULLSCREEN : SDL_EVENT_کھڑکی_LEAVE_FULLSCREEN, 0, 0);

    واپس SDL_FULLSCREEN_SUCCEEDED;
}

ساکن SDL_DisplayID QNX_Get_Display_For_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_کھڑکی_ڈیٹا  *impl = (SDL_کھڑکی_ڈیٹا *)کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *display_ڈیٹا;

    screen_display_t screen_display;

    اگر (impl == تہی) {
        واپس 0;
    }

    اگر (screen_get_کھڑکی_property_pv(impl->کھڑکی, SCREEN_PROPERTY_DISPLAY, (خالی **)&screen_display) < 0) {
        واپس 0;
    }

    برائے (صحیح i = 0; i < _this->عدد_displays; i++) {
        display_ڈیٹا = _this->displays[i]->اندرونی_2;
        اگر (display_ڈیٹا && (display_ڈیٹا->screen_display == screen_display)) {
            واپس _this->displays[i]->id;
        }
    }

    واپس 0;
}

/**
 * Runs the main event loop.
 */
ساکن خالی QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_کھڑکی      *کھڑکی;
    SDL_کھڑکی_ڈیٹا   *impl;
    صحیح             type;
    صحیح             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    برائے (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        impl = (SDL_کھڑکی_ڈیٹا *)کھڑکی->اندرونی_2;
        اگر (screen_get_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            جاری;
        }
        has_focus = (bool)has_focus_i;

        اگر (impl->has_focus != has_focus) {
            SDL_Send_کھڑکی_Event(کھڑکی, (has_focus ? SDL_EVENT_کھڑکی_FOCUS_GAINED : SDL_EVENT_کھڑکی_FOCUS_گمشدہ), 0, 0);
            SDL_Send_کھڑکی_Event(کھڑکی, (has_focus ? SDL_EVENT_کھڑکی_MOUSE_ENTER : SDL_EVENT_کھڑکی_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_سیٹ_Mouse_Focus(کھڑکی);
            SDL_سیٹ_Keyboard_Focus(کھڑکی);
        }
    }

    برائے (;;) {
        اگر (screen_get_event(context, event, 0) < 0) {
            توڑو;
        }

        اگر (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            توڑو;
        }

        اگر (type == SCREEN_EVENT_NONE) {
            توڑو;
        }

        انتخاب (type) {
        حالت SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            توڑو;

        حالت SCREEN_EVENT_اشارہ_گر:
            handle_اشارہ_گر_Event(event);
            توڑو;

        طےشدہ:
            توڑو;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
ساکن خالی QNX_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا   *impl = (SDL_کھڑکی_ڈیٹا *)کھڑکی->اندرونی_2;
    صحیح             سائز[2];

    سائز[0] = کھڑکی->pending.w;
    سائز[1] = کھڑکی->pending.h;

    اگر (!(کھڑکی->flags & (SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_MAXIMIZED))) {
        اگر (screen_destroy_کھڑکی_buffers(impl->کھڑکی) < 0) {
            واپس;
        }
        impl->resize = true;

        screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_سائز, سائز);
        screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_ماخذ_سائز, سائز);

        screen_create_کھڑکی_buffers(impl->کھڑکی, (کھڑکی->flags & SDL_کھڑکی_OPENGL) ? 2 : 1);
    } ورنہ {
        کھڑکی->آخری_سائز_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
ساکن خالی QNX_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا   *impl = (SDL_کھڑکی_ڈیٹا *)کھڑکی->اندرونی_2;
    ثابت صحیح       visible = 1;

    screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
ساکن خالی QNX_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا   *impl = (SDL_کھڑکی_ڈیٹا *)کھڑکی->اندرونی_2;
    ثابت صحیح       visible = 0;

    screen_سیٹ_کھڑکی_property_iv(impl->کھڑکی, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
ساکن خالی QNX_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا   *impl = (SDL_کھڑکی_ڈیٹا *)کھڑکی->اندرونی_2;

    اگر (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_کھڑکی(impl->کھڑکی);
        کھڑکی->اندرونی_2 = تہی;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
ساکن خالی QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
ساکن SDL_VideoDevice *createDevice(خالی)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
    }

    device->اندرونی_2 = تہی;
    device->VideoInit = QNX_VideoInit;
    device->VideoQuit = QNX_VideoQuit;
    device->CreateSDLWindow = QNX_Create_کھڑکی;
    device->Create_کھڑکی_Framebuffer = QNX_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = QNX_Update_کھڑکی_Framebuffer;
    device->سیٹ_کھڑکی_سائز = QNX_سیٹ_کھڑکی_سائز;
    device->سیٹ_کھڑکی_Fullscreen = QNX_سیٹ_کھڑکی_Fullscreen;
    device->Show_کھڑکی = QNX_Show_کھڑکی;
    device->Hide_کھڑکی = QNX_Hide_کھڑکی;
    device->Get_Display_For_کھڑکی = QNX_Get_Display_For_کھڑکی;
    device->GetDisplayBounds = QNX_GetDisplayBounds;
    device->GetDisplayModes = QNX_GetDisplayModes;
#اگر 0
    device->سیٹ_Display_منوال = QNX_سیٹ_Display_منوال;
#اگر_ختم
    device->PumpEvents = QNX_PumpEvents;
    device->Destroy_کھڑکی = QNX_Destroy_کھڑکی;

    device->GL_بھرو_Library = QNX_GLES_بھرو_Library;
    device->GL_Get_Proc_پتہ = QNX_GLES_Get_Proc_پتہ;
    device->GL_CreateContext = QNX_GLES_CreateContext;
    device->GL_سیٹ_تبادلہ_Interval = QNX_GLES_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = QNX_GLES_Get_تبادلہ_Interval;
    device->GL_تبادلہ_کھڑکی = QNX_GLES_تبادلہ_کھڑکی;
    device->GL_MakeCurrent = QNX_GLES_MakeCurrent;
    device->GL_DestroyContext = QNX_GLES_DeleteContext;
    device->GL_UnloadLibrary = QNX_GLES_UnloadLibrary;

    device->آزاد = QNX_DeleteDevice;

    واپس device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    تہی, // no ShowMessageBox implementation
    false
};
