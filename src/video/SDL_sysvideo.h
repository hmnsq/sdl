/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

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

#جيڪڏهن_وصف_نه_ٿيل SDL_sysvideo_h_
#وصف_ڪريو SDL_sysvideo_h_

#ضمن <SDL3/SDL_vulkan.h>

#ضمن "SDL_surface_c.h"

// The SDL video driver

تعريفنوع بنية SDL_VideoDisplay SDL_VideoDisplay;
تعريفنوع بنية SDL_VideoDevice SDL_VideoDevice;
تعريفنوع بنية SDL_Video_معلومات SDL_Video_معلومات;
تعريفنوع بنية SDL_Display_معلومات SDL_Display_معلومات;
تعريفنوع بنية SDL_دري_معلومات SDL_دري_معلومات;

تعريفنوع بنية
{
    عائم SDR_white_level;
    عائم HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
بنية SDL_دري
{
    SDL_دري_ID id;
    حرف *title;
    SDL_Surface *icon;
    صحيح x, y;
    صحيح w, h;
    صحيح min_w, min_h;
    صحيح max_w, max_h;
    عائم min_aspect;
    عائم max_aspect;
    صحيح آخري_pixel_w, آخري_pixel_h;
    SDL_دري_Flags flags;
    SDL_دري_Flags pending_flags;
    عائم display_scale;
    bool external_graphics_context;
    bool fullscreen_exclusive;  // The window is currently fullscreen exclusive
    SDL_DisplayID آخري_fullscreen_exclusive_display;  // The last fullscreen_exclusive display
    SDL_DisplayID displayID;
    SDL_DisplayID pending_displayID;

    /* Stored position and size for the window in the non-fullscreen state,
     * including when the window is maximized or tiled.
     *
     * This is the size and position to which the window should return when
     * leaving the fullscreen state.
     */
    SDL_Rect windowed;

    /* Stored position and size for the window in the base 'floating' state;
     * when not fullscreen, nor in a state such as maximized or tiled.
     *
     * This is the size and position to which the window should return when
     * it's maximized and SDL_RestoreWindow() is called.
     */
    SDL_Rect floating;

    // The last client requested size and position for the window.
    SDL_Rect pending;

    /* Toggle for drivers to indicate that the current window state is tiled,
     * and sizes set non-programmatically shouldn't be cached.
     */
    bool tiled;

    // Whether or not the initial position was defined
    bool undefined_x;
    bool undefined_y;

    SDL_Display_گهڻائي requested_fullscreen_گهڻائي;
    SDL_Display_گهڻائي current_fullscreen_گهڻائي;
    SDL_HDROutputProperties HDR;

    عائم opacity;

    SDL_Surface *surface;
    bool surface_valid;

    bool is_hiding;
    bool restore_on_show; // Child was hidden recursively by the parent, restore when shown.
    bool آخري_position_pending; // This should NOT be cleared by the backend, as it is used for fullscreen positioning.
    bool آخري_سائيز_pending; // This should be cleared by the backend if the new size cannot be applied.
    bool update_fullscreen_on_display_بدليو;
    bool constrain_popup;
    bool is_destroying;
    bool is_dropping; // drag/drop in progress, expecting SDL_SendDropComplete().

    صحيح محفوظ_inset_کاٻو;
    صحيح محفوظ_inset_ساڄو;
    صحيح محفوظ_inset_چوٽي;
    صحيح محفوظ_inset_bottom;
    SDL_Rect محفوظ_rect;

    SDL_PropertiesID متن_داخلا_props;
    bool متن_داخلا_سرگرم;
    SDL_Rect متن_داخلا_rect;
    صحيح متن_داخلا_cursor;

    SDL_Rect mouse_rect;

    SDL_ڪاميابي_Test ڪاميابي_test;
    فراغ *ڪاميابي_test_معلومات;

    SDL_ترقي_State ترقي_state;
    عائم ترقي_قدر;

    SDL_PropertiesID props;

    صحيح انگ_renderers;
    SDL_Renderer **renderers;

    SDL_دري_معلومات *اندروني;

    // If a toplevel window, holds the current keyboard focus for grabbing popups.
    SDL_دري *keyboard_focus;

    SDL_دري *prev;
    SDL_دري *ايندڙ;

    SDL_دري *والد;
    SDL_دري *پهريون_ٻار;
    SDL_دري *prev_sibling;
    SDL_دري *ايندڙ_sibling;
};
#وصف_ڪريو SDL_دري_FULLSCREEN_VISIBLE(W)        \
    ((((W)->flags & SDL_دري_FULLSCREEN) != 0) &&   \
     (((W)->flags & SDL_دري_HIDDEN) == 0) && \
     (((W)->flags & SDL_دري_MINIMIZED) == 0))

#وصف_ڪريو SDL_دري_IS_POPUP(W) \
    (((W)->flags & (SDL_دري_TOOLTIP | SDL_دري_POPUP_MENU)) != 0)

/*
 * Define the SDL display structure.
 * This corresponds to physical monitors attached to the system.
 */
بنية SDL_VideoDisplay
{
    SDL_DisplayID id;
    حرف *name;
    صحيح max_fullscreen_modes;
    صحيح انگ_fullscreen_modes;
    SDL_Display_گهڻائي *fullscreen_modes;
    SDL_Display_گهڻائي desktop_گهڻائي;
    ثابت SDL_Display_گهڻائي *current_گهڻائي;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    عائم content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_سرگرم;
    SDL_دري *fullscreen_دري;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_Display_معلومات *اندروني;
};

// Video device flags
تعريفنوع تعداد
{
    VIDEO_DEVICE_CAPS_گهڻائي_SWITCHING_EMULATED = 0x01,
    VIDEO_DEVICE_CAPS_HAS_POPUP_دري_SUPPORT = 0x02,
    VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS = 0x04,
    VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY = 0x08,
    VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES = 0x10,
    VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES = 0x20,
    VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER = 0x40
} DeviceCaps;

// Fullscreen operations
تعريفنوع تعداد
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

تعريفنوع تعداد
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_Fullscreen_نتيجو;

بنية SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    ثابت حرف *name;

    /* * * */
    // Initialization/Query functions

    /*
     * Initialize the native video subsystem, filling in the list of
     * displays for this driver, returning true (success) or false (error).
     */
    bool (*VideoInit)(SDL_VideoDevice *_this);

    /*
     * Reverse the effects VideoInit() -- called if VideoInit() fails or
     * if the application is shutting down the video subsystem.
     */
    فراغ (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    فراغ (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    فراغ (*RefreshDisplays)(SDL_VideoDevice *_this);

    /*
     * Get the bounds of a display
     */
    bool (*GetDisplayBounds)(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

    /*
     * Get the usable bounds of a display (bounds minus menubar or whatever)
     */
    bool (*GetDisplayUsableBounds)(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);

    /*
     * Get a list of the available display modes for a display.
     */
    bool (*GetDisplayModes)(SDL_VideoDevice *_this, SDL_VideoDisplay *display);

    /*
     * Setting the display mode is independent of creating windows, so
     * when the display mode is changed, all existing windows should have
     * their data updated accordingly, including the display surfaces
     * associated with them.
     */
    bool (*سيٽ_Display_گهڻائي)(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي);

    /* * * */
    /*
     * Window functions
     */
    bool (*CreateSDLWindow)(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props);
    فراغ (*سيٽ_دري_Title)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*سيٽ_دري_Icon)(SDL_VideoDevice *_this, SDL_دري *دري, SDL_Surface *icon);
    bool (*سيٽ_دري_Position)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*سيٽ_دري_سائيز)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*سيٽ_دري_Minimum_سائيز)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*سيٽ_دري_وڌ_کان_وڌ_سائيز)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*سيٽ_دري_Aspect_تناسب)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*Get_دري_Borders_سائيز)(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *چوٽي, صحيح *کاٻو, صحيح *bottom, صحيح *ساڄو);
    عائم (*Get_دري_Content_Scale)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*Get_دري_سائيز_اندريون_Pixels)(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *w, صحيح *h);
    bool (*سيٽ_دري_Opacity)(SDL_VideoDevice *_this, SDL_دري *دري, عائم opacity);
    bool (*سيٽ_دري_والد)(SDL_VideoDevice *_this, SDL_دري *دري, SDL_دري *والد);
    bool (*سيٽ_دري_Modal)(SDL_VideoDevice *_this, SDL_دري *دري, bool modal);
    فراغ (*Show_دري)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*Hide_دري)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*Raise_دري)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*Maximize_دري)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*Minimize_دري)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*Restore_دري)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*سيٽ_دري_Bordered)(SDL_VideoDevice *_this, SDL_دري *دري, bool bordered);
    فراغ (*سيٽ_دري_Resizable)(SDL_VideoDevice *_this, SDL_دري *دري, bool resizable);
    فراغ (*سيٽ_دري_Always_On_چوٽي)(SDL_VideoDevice *_this, SDL_دري *دري, bool on_چوٽي);
    SDL_Fullscreen_نتيجو (*سيٽ_دري_Fullscreen)(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    فراغ *(*Get_دري_ICCProfile)(SDL_VideoDevice *_this, SDL_دري *دري, size_t *سائيز);
    SDL_DisplayID (*Get_Display_For_دري)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*سيٽ_دري_Mouse_Rect)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*سيٽ_دري_Mouse_Grab)(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed);
    bool (*سيٽ_دري_Keyboard_Grab)(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed);
    فراغ (*Destroy_دري)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*Create_دري_Framebuffer)(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch);
    bool (*سيٽ_دري_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_دري *دري, صحيح vsync);
    bool (*Get_دري_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *vsync);
    bool (*Update_دري_Framebuffer)(SDL_VideoDevice *_this, SDL_دري *دري, ثابت SDL_Rect *rects, صحيح numrects);
    فراغ (*Destroy_دري_Framebuffer)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*On_دري_Enter)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*Update_دري_Shape)(SDL_VideoDevice *_this, SDL_دري *دري, SDL_Surface *shape);
    bool (*Flash_دري)(SDL_VideoDevice *_this, SDL_دري *دري, SDL_FlashOperation operation);
    bool (*Apply_دري_ترقي)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*سيٽ_دري_Focusable)(SDL_VideoDevice *_this, SDL_دري *دري, bool focusable);
    bool (*سيٽ_دري_Fill_Document)(SDL_VideoDevice *_this, SDL_دري *دري, bool fill);
    bool (*Sync_دري)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*Reconfigure_دري)(SDL_VideoDevice *_this, SDL_دري *دري, SDL_دري_Flags flags);

    /* * * */
    /*
     * OpenGL support
     */
    bool (*GL_ڀريو_Library)(SDL_VideoDevice *_this, ثابت حرف *رستو);
    SDL_Function_اشارو (*GL_Get_Proc_پتو)(SDL_VideoDevice *_this, ثابت حرف *proc);
    فراغ (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_دري *دري, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*GL_سيٽ_مٽا_سٽا_Interval)(SDL_VideoDevice *_this, صحيح interval);
    bool (*GL_Get_مٽا_سٽا_Interval)(SDL_VideoDevice *_this, صحيح *interval);
    bool (*GL_مٽا_سٽا_دري)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    فراغ (*GL_سيٽ_Default_Profile_Config)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_ڀريو_Library)(SDL_VideoDevice *_this, ثابت حرف *رستو);
    فراغ (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    حرف ثابت * ثابت *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *ڳڻپ);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_دري *دري, VkInstance instance, ثابت بنية Vk_ورهاست_Callbacks *allocator, VkSurfaceKHR *surface);
    فراغ (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ثابت بنية Vk_ورهاست_Callbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 قطار_Family_اشاريو);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    فراغ *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    صحيح (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    فراغ (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*شروعات_متن_داخلا)(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props);
    bool (*Stop_متن_داخلا)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*Update_متن_داخلا_Area)(SDL_VideoDevice *_this, SDL_دري *دري);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_دري *دري);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    فراغ (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props);
    فراغ (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_دري *دري);
    فراغ (*سيٽ_متن_داخلا_Properties)(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props);

    // Clipboard
    ثابت حرف *ثابت *(*Get_متن_Mime_Types)(SDL_VideoDevice *_this, size_t *انگ_mime_types);
    bool (*سيٽ_Clipboard_معلومات)(SDL_VideoDevice *_this);
    فراغ *(*Get_Clipboard_معلومات)(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *سائيز);
    bool (*Has_Clipboard_معلومات)(SDL_VideoDevice *_this, ثابت حرف *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*سيٽ_Clipboard_متن)(SDL_VideoDevice *_this, ثابت حرف *متن);
    حرف *(*Get_Clipboard_متن)(SDL_VideoDevice *_this);
    bool (*Has_Clipboard_متن)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*سيٽ_Primary_Selection_متن)(SDL_VideoDevice *_this, ثابت حرف *متن);
    حرف *(*Get_Primary_Selection_متن)(SDL_VideoDevice *_this);
    bool (*Has_Primary_Selection_متن)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*Show_پيغام_Box)(SDL_VideoDevice *_this, ثابت SDL_پيغام_Box_معلومات *messageboxdata, صحيح *buttonID);

    // Hit-testing
    bool (*سيٽ_دري_ڪاميابي_Test)(SDL_دري *دري, bool enabled);

    // Tell window that app enabled drag'n'drop events
    فراغ (*AcceptDragAndDrop)(SDL_دري *دري, bool accept);

    // Display the system-level window menu
    فراغ (*Show_دري_System_Menu)(SDL_دري *دري, صحيح x, صحيح y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    فراغ *wakeup_دري;
    صحيح انگ_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_دري *windows;
    SDL_دري *grabbed_دري;
    Uint32 clipboard_sequence;
    SDL_Clipboard_معلومات_Callback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    فراغ *clipboard_userdata;
    حرف **clipboard_mime_types;
    size_t انگ_clipboard_mime_types;
    حرف *primary_selection_متن;
    bool setting_display_گهڻائي;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    بنية
    {
        صحيح red_سائيز;
        صحيح green_سائيز;
        صحيح blue_سائيز;
        صحيح alpha_سائيز;
        صحيح اونهائي_سائيز;
        صحيح بفر_سائيز;
        صحيح stencil_سائيز;
        صحيح double_بفر;
        صحيح accum_red_سائيز;
        صحيح accum_green_سائيز;
        صحيح accum_blue_سائيز;
        صحيح accum_alpha_سائيز;
        صحيح stereo;
        صحيح multisamplebuffers;
        صحيح multisamplesamples;
        صحيح floatbuffers;
        صحيح accelerated;
        صحيح major_نسخو;
        صحيح minor_نسخو;
        صحيح flags;
        صحيح profile_نقاب;
        صحيح share_with_current_context;
        صحيح release_behavior;
        صحيح reset_notification;
        صحيح framebuffer_srgb_capable;
        صحيح no_error;
        صحيح retained_backing;
        صحيح egl_platform;
        صحيح driver_loaded;
        صحيح HAS_GL_ARB_color_بفر_float;
        حرف driver_رستو[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    فراغ *egl_attrib_callback_userdata;

    /* * * */
    // Cache current GL context; don't call the OS when it hasn't changed.
    /* We have the global pointers here so Cocoa continues to work the way
       it always has, and the thread-local storage for the general case.
     */
    SDL_دري *current_glwin;
    SDL_GLContext current_glctx;
    SDL_TLSID current_glwin_tls;
    SDL_TLSID current_glctx_tls;

    /* Flag that stores whether it's allowed to call SDL_GL_MakeCurrent()
     * with a NULL window, but a non-NULL context. (Not allowed in most cases,
     * except on EGL under some circumstances.) */
    bool gl_allow_no_surface;

    /* * * */
    // Data used by the Vulkan drivers
    بنية
    {
        SDL_Function_اشارو vkGetInstanceProcAddr;
        SDL_Function_اشارو vkEnumerateInstanceExtensionProperties;
        صحيح loader_loaded;
        حرف loader_رستو[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_Video_معلومات *اندروني;
    بنية SDL_GLDriver_معلومات *gl_معلومات;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    بنية SDL_EGL_Video_معلومات *egl_معلومات;
#جيڪڏهن_پورو

#إذا defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    بنية SDL_ذاتي_GLESData *gles_معلومات;
#جيڪڏهن_پورو

    /* * * */
    // The function used to dispose of this structure
    فراغ (*حرر)(SDL_VideoDevice *_this);
};

تعريفنوع بنية VideoBootStrap
{
    ثابت حرف *name;
    ثابت حرف *desc;
    SDL_VideoDevice *(*create)(فراغ);
    bool (*Show_پيغام_Box)(ثابت SDL_پيغام_Box_معلومات *messageboxdata, صحيح *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
خارجي VideoBootStrap ذاتي_bootstrap;
خارجي VideoBootStrap COCOA_bootstrap;
خارجي VideoBootStrap X11_bootstrap;
خارجي VideoBootStrap WINDOWS_bootstrap;
خارجي VideoBootStrap HAIKU_bootstrap;
خارجي VideoBootStrap UIKIT_bootstrap;
خارجي VideoBootStrap Android_bootstrap;
خارجي VideoBootStrap OPENHARMONY_bootstrap;
خارجي VideoBootStrap PS2_bootstrap;
خارجي VideoBootStrap PSP_bootstrap;
خارجي VideoBootStrap VITA_bootstrap;
خارجي VideoBootStrap RISCOS_bootstrap;
خارجي VideoBootStrap N3DS_bootstrap;
خارجي VideoBootStrap NGAGE_bootstrap;
خارجي VideoBootStrap RPI_bootstrap;
خارجي VideoBootStrap KMSDRM_bootstrap;
خارجي VideoBootStrap DUMMY_bootstrap;
خارجي VideoBootStrap DUMMY_evdev_bootstrap;
خارجي VideoBootStrap Wayland_preferred_bootstrap;
خارجي VideoBootStrap Wayland_bootstrap;
خارجي VideoBootStrap VIVANTE_bootstrap;
خارجي VideoBootStrap Emscripten_bootstrap;
خارجي VideoBootStrap OFFSCREEN_bootstrap;
خارجي VideoBootStrap QNX_bootstrap;
خارجي VideoBootStrap OPENVR_bootstrap;
خارجي VideoBootStrap DOSVESA_bootstrap;

خارجي bool SDL_UninitializedVideo(فراغ);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
خارجي bool SDL_OnVideoThread(فراغ);
خارجي SDL_VideoDevice *SDL_GetVideoDevice(فراغ);
خارجي فراغ SDL_سيٽ_System_Theme(SDL_SystemTheme theme);
خارجي SDL_DisplayID SDL_جوڙيو_Basic_Video_Display(ثابت SDL_Display_گهڻائي *desktop_گهڻائي);
خارجي SDL_DisplayID SDL_جوڙيو_Video_Display(ثابت SDL_VideoDisplay *display, bool send_event);
خارجي فراغ SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
خارجي bool SDL_جوڙيو_Fullscreen_Display_گهڻائي(SDL_VideoDisplay *display, ثابت SDL_Display_گهڻائي *گهڻائي);
خارجي فراغ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
خارجي فراغ SDL_سيٽ_Desktop_Display_گهڻائي(SDL_VideoDisplay *display, ثابت SDL_Display_گهڻائي *گهڻائي);
خارجي فراغ SDL_سيٽ_Current_Display_گهڻائي(SDL_VideoDisplay *display, ثابت SDL_Display_گهڻائي *گهڻائي);
خارجي فراغ SDL_سيٽ_Display_Content_Scale(SDL_VideoDisplay *display, عائم scale);
خارجي فراغ SDL_سيٽ_Display_HDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR);
خارجي bool SDL_سيٽ_Display_گهڻائي_For_Display(SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي);
خارجي SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
خارجي SDL_DisplayID SDL_Get_Display_For_دري_Position(SDL_دري *دري);
خارجي SDL_VideoDisplay *SDL_Get_Video_Display_For_دري(SDL_دري *دري);
خارجي SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_دري(SDL_دري *دري);
خارجي صحيح SDL_Get_Display_اشاريو(SDL_DisplayID displayID);
خارجي SDL_Display_معلومات *SDL_Get_Display_Driver_معلومات(SDL_DisplayID display);
خارجي SDL_Display_معلومات *SDL_Get_Display_Driver_معلومات_For_دري(SDL_دري *دري);
خارجي صحيح SDL_Get_پيغام_Box_ڳڻپ(فراغ);
خارجي فراغ SDL_سيٽ_دري_HDRProperties(SDL_دري *دري, ثابت SDL_HDROutputProperties *HDR, bool send_event);
خارجي فراغ SDL_سيٽ_دري_محفوظ_Area_Insets(SDL_دري *دري, صحيح کاٻو, صحيح ساڄو, صحيح چوٽي, صحيح bottom);

خارجي فراغ SDL_GL_DeduceMaxSupportedESProfile(صحيح *major, صحيح *minor);

خارجي bool SDL_Recreate_دري(SDL_دري *دري, SDL_دري_Flags flags);
خارجي bool SDL_Reconfigure_دري(SDL_دري *دري, SDL_دري_Flags flags);
خارجي bool SDL_HasWindows(فراغ);
خارجي فراغ SDL_Relative_منزل_Global_For_دري(SDL_دري *دري, صحيح rel_x, صحيح rel_y, صحيح *abs_x, صحيح *abs_y);
خارجي فراغ SDL_Global_منزل_Relative_For_دري(SDL_دري *دري, صحيح abs_x, صحيح abs_y, صحيح *rel_x, صحيح *rel_y);
خارجي bool SDL_ShouldFocusPopup(SDL_دري *دري);
خارجي bool SDL_ShouldRelinquishPopupFocus(SDL_دري *دري, SDL_دري **new_focus);

خارجي فراغ SDL_OnDisplayAdded(SDL_VideoDisplay *display);
خارجي فراغ SDL_OnDisplayMoved(SDL_VideoDisplay *display);
خارجي فراغ SDL_On_دري_Shown(SDL_دري *دري);
خارجي فراغ SDL_On_دري_Hidden(SDL_دري *دري);
خارجي فراغ SDL_On_دري_Moved(SDL_دري *دري);
خارجي فراغ SDL_On_دري_Resized(SDL_دري *دري);
خارجي فراغ SDL_Check_دري_Pixel_سائيز_بدليو(SDL_دري *دري);
خارجي فراغ SDL_On_دري_Pixel_سائيز_بدليو(SDL_دري *دري);
خارجي فراغ SDL_On_دري_جيئرو_Resize_Update(SDL_دري *دري);
خارجي فراغ SDL_On_دري_Minimized(SDL_دري *دري);
خارجي فراغ SDL_On_دري_Maximized(SDL_دري *دري);
خارجي فراغ SDL_On_دري_Restored(SDL_دري *دري);
خارجي فراغ SDL_On_دري_Enter(SDL_دري *دري);
خارجي فراغ SDL_On_دري_Leave(SDL_دري *دري);
خارجي فراغ SDL_On_دري_Focus_Gained(SDL_دري *دري);
خارجي فراغ SDL_On_دري_Focus_گم(SDL_دري *دري);
خارجي فراغ SDL_On_دري_Display_بدليو(SDL_دري *دري);
خارجي فراغ SDL_Update_دري_Grab(SDL_دري *دري);
خارجي bool SDL_Update_Fullscreen_گهڻائي(SDL_دري *دري, SDL_FullscreenOp fullscreen, bool commit);
خارجي SDL_دري *SDL_GetToplevelForKeyboardFocus(فراغ);

خارجي bool SDL_ShouldAllowTopmost(فراغ);

خارجي فراغ SDL_ToggleDragAndDropSupport(فراغ);

خارجي فراغ SDL_UpdateDesktopBounds(فراغ);

خارجي SDL_متن_داخلا_Type SDL_Get_متن_داخلا_Type(SDL_PropertiesID props);
خارجي SDL_Capitalization SDL_Get_متن_داخلا_Capitalization(SDL_PropertiesID props);
خارجي bool SDL_Get_متن_داخلا_Autocorrect(SDL_PropertiesID props);
خارجي bool SDL_Get_متن_داخلا_Multiline(SDL_PropertiesID props);

خارجي فراغ SDL_SendScreenKeyboardShown(فراغ);
خارجي فراغ SDL_SendScreenKeyboardHidden(فراغ);

#جيڪڏهن_پورو // SDL_sysvideo_h_
