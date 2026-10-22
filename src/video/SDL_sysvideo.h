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

#اگر_تعریف_نشده SDL_sysvideo_h_
#تعریف_کن SDL_sysvideo_h_

#ضمن <SDL3/SDL_vulkan.h>

#ضمن "SDL_surface_c.h"

// The SDL video driver

تعريفنوع بنية SDL_VideoDisplay SDL_VideoDisplay;
تعريفنوع بنية SDL_VideoDevice SDL_VideoDevice;
تعريفنوع بنية SDL_Video_داده SDL_Video_داده;
تعريفنوع بنية SDL_Display_داده SDL_Display_داده;
تعريفنوع بنية SDL_پنجره_داده SDL_پنجره_داده;

تعريفنوع بنية
{
    عائم SDR_white_level;
    عائم HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
بنية SDL_پنجره
{
    SDL_پنجره_ID id;
    حرف *title;
    SDL_Surface *icon;
    صحيح x, y;
    صحيح w, h;
    صحيح min_w, min_h;
    صحيح max_w, max_h;
    عائم min_aspect;
    عائم max_aspect;
    صحيح آخرین_pixel_w, آخرین_pixel_h;
    SDL_پنجره_Flags flags;
    SDL_پنجره_Flags pending_flags;
    عائم display_scale;
    bool external_graphics_context;
    bool fullscreen_exclusive;  // The window is currently fullscreen exclusive
    SDL_DisplayID آخرین_fullscreen_exclusive_display;  // The last fullscreen_exclusive display
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

    SDL_Display_نما requested_fullscreen_نما;
    SDL_Display_نما current_fullscreen_نما;
    SDL_HDROutputProperties HDR;

    عائم opacity;

    SDL_Surface *surface;
    bool surface_valid;

    bool is_hiding;
    bool restore_on_show; // Child was hidden recursively by the parent, restore when shown.
    bool آخرین_position_pending; // This should NOT be cleared by the backend, as it is used for fullscreen positioning.
    bool آخرین_اندازه_pending; // This should be cleared by the backend if the new size cannot be applied.
    bool update_fullscreen_on_display_تغییریافته;
    bool constrain_popup;
    bool is_destroying;
    bool is_dropping; // drag/drop in progress, expecting SDL_SendDropComplete().

    صحيح امن_inset_چپ;
    صحيح امن_inset_راست;
    صحيح امن_inset_بالاترین;
    صحيح امن_inset_bottom;
    SDL_Rect امن_rect;

    SDL_PropertiesID متن_درون_داد_props;
    bool متن_درون_داد_فعال;
    SDL_Rect متن_درون_داد_rect;
    صحيح متن_درون_داد_cursor;

    SDL_Rect mouse_rect;

    SDL_اصابت_Test اصابت_test;
    فراغ *اصابت_test_داده;

    SDL_پیشرفت_State پیشرفت_state;
    عائم پیشرفت_مقدار;

    SDL_PropertiesID props;

    صحيح رقم_renderers;
    SDL_Renderer **renderers;

    SDL_پنجره_داده *داخلی;

    // If a toplevel window, holds the current keyboard focus for grabbing popups.
    SDL_پنجره *keyboard_focus;

    SDL_پنجره *prev;
    SDL_پنجره *بعدی;

    SDL_پنجره *والد;
    SDL_پنجره *اولی_فرزند;
    SDL_پنجره *prev_sibling;
    SDL_پنجره *بعدی_sibling;
};
#تعریف_کن SDL_پنجره_FULLSCREEN_VISIBLE(W)        \
    ((((W)->flags & SDL_پنجره_FULLSCREEN) != 0) &&   \
     (((W)->flags & SDL_پنجره_HIDDEN) == 0) && \
     (((W)->flags & SDL_پنجره_MINIMIZED) == 0))

#تعریف_کن SDL_پنجره_IS_POPUP(W) \
    (((W)->flags & (SDL_پنجره_TOOLTIP | SDL_پنجره_POPUP_MENU)) != 0)

/*
 * Define the SDL display structure.
 * This corresponds to physical monitors attached to the system.
 */
بنية SDL_VideoDisplay
{
    SDL_DisplayID id;
    حرف *name;
    صحيح max_fullscreen_modes;
    صحيح رقم_fullscreen_modes;
    SDL_Display_نما *fullscreen_modes;
    SDL_Display_نما desktop_نما;
    ثابت SDL_Display_نما *current_نما;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    عائم content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_فعال;
    SDL_پنجره *fullscreen_پنجره;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_Display_داده *داخلی;
};

// Video device flags
تعريفنوع تعداد
{
    VIDEO_DEVICE_CAPS_نما_SWITCHING_EMULATED = 0x01,
    VIDEO_DEVICE_CAPS_HAS_POPUP_پنجره_SUPPORT = 0x02,
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
} SDL_Fullscreen_نتیجه;

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
    bool (*مجموعه_Display_نما)(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما);

    /* * * */
    /*
     * Window functions
     */
    bool (*CreateSDLWindow)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props);
    فراغ (*مجموعه_پنجره_Title)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*مجموعه_پنجره_Icon)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_Surface *icon);
    bool (*مجموعه_پنجره_Position)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*مجموعه_پنجره_اندازه)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*مجموعه_پنجره_Minimum_اندازه)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*مجموعه_پنجره_بیشینه_اندازه)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*مجموعه_پنجره_Aspect_نسبت)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*Get_پنجره_Borders_اندازه)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *بالاترین, صحيح *چپ, صحيح *bottom, صحيح *راست);
    عائم (*Get_پنجره_Content_Scale)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*Get_پنجره_اندازه_درون_Pixels)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *w, صحيح *h);
    bool (*مجموعه_پنجره_Opacity)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, عائم opacity);
    bool (*مجموعه_پنجره_والد)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_پنجره *والد);
    bool (*مجموعه_پنجره_Modal)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool modal);
    فراغ (*Show_پنجره)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*Hide_پنجره)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*Raise_پنجره)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*Maximize_پنجره)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*Minimize_پنجره)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*Restore_پنجره)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*مجموعه_پنجره_Bordered)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool bordered);
    فراغ (*مجموعه_پنجره_Resizable)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool resizable);
    فراغ (*مجموعه_پنجره_Always_On_بالاترین)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool on_بالاترین);
    SDL_Fullscreen_نتیجه (*مجموعه_پنجره_Fullscreen)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    فراغ *(*Get_پنجره_ICCProfile)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, size_t *اندازه);
    SDL_DisplayID (*Get_Display_For_پنجره)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*مجموعه_پنجره_Mouse_Rect)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*مجموعه_پنجره_Mouse_Grab)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed);
    bool (*مجموعه_پنجره_Keyboard_Grab)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed);
    فراغ (*Destroy_پنجره)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*Create_پنجره_Framebuffer)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch);
    bool (*مجموعه_پنجره_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح vsync);
    bool (*Get_پنجره_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *vsync);
    bool (*Update_پنجره_Framebuffer)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, ثابت SDL_Rect *rects, صحيح numrects);
    فراغ (*Destroy_پنجره_Framebuffer)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*On_پنجره_Enter)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*Update_پنجره_Shape)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_Surface *shape);
    bool (*Flash_پنجره)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_FlashOperation operation);
    bool (*Apply_پنجره_پیشرفت)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*مجموعه_پنجره_Focusable)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool focusable);
    bool (*مجموعه_پنجره_Fill_Document)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool fill);
    bool (*Sync_پنجره)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*Reconfigure_پنجره)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_پنجره_Flags flags);

    /* * * */
    /*
     * OpenGL support
     */
    bool (*GL_بارگیری_Library)(SDL_VideoDevice *_this, ثابت حرف *مسیر);
    SDL_Function_اشاره_گر (*GL_Get_Proc_آدرس)(SDL_VideoDevice *_this, ثابت حرف *proc);
    فراغ (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*GL_مجموعه_جابجا_Interval)(SDL_VideoDevice *_this, صحيح interval);
    bool (*GL_Get_جابجا_Interval)(SDL_VideoDevice *_this, صحيح *interval);
    bool (*GL_جابجا_پنجره)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    فراغ (*GL_مجموعه_Default_Profile_Config)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_بارگیری_Library)(SDL_VideoDevice *_this, ثابت حرف *مسیر);
    فراغ (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    حرف ثابت * ثابت *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *شمار);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, VkInstance instance, ثابت بنية Vk_تخصیص_Callbacks *allocator, VkSurfaceKHR *surface);
    فراغ (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ثابت بنية Vk_تخصیص_Callbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 صف_Family_شاخص);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    فراغ *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    صحيح (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    فراغ (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*شروع_متن_درون_داد)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props);
    bool (*Stop_متن_درون_داد)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*Update_متن_درون_داد_Area)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    فراغ (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props);
    فراغ (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
    فراغ (*مجموعه_متن_درون_داد_Properties)(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props);

    // Clipboard
    ثابت حرف *ثابت *(*Get_متن_Mime_Types)(SDL_VideoDevice *_this, size_t *رقم_mime_types);
    bool (*مجموعه_Clipboard_داده)(SDL_VideoDevice *_this);
    فراغ *(*Get_Clipboard_داده)(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *اندازه);
    bool (*Has_Clipboard_داده)(SDL_VideoDevice *_this, ثابت حرف *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*مجموعه_Clipboard_متن)(SDL_VideoDevice *_this, ثابت حرف *متن);
    حرف *(*Get_Clipboard_متن)(SDL_VideoDevice *_this);
    bool (*Has_Clipboard_متن)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*مجموعه_Primary_Selection_متن)(SDL_VideoDevice *_this, ثابت حرف *متن);
    حرف *(*Get_Primary_Selection_متن)(SDL_VideoDevice *_this);
    bool (*Has_Primary_Selection_متن)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*Show_پیام_Box)(SDL_VideoDevice *_this, ثابت SDL_پیام_Box_داده *messageboxdata, صحيح *buttonID);

    // Hit-testing
    bool (*مجموعه_پنجره_اصابت_Test)(SDL_پنجره *پنجره, bool enabled);

    // Tell window that app enabled drag'n'drop events
    فراغ (*AcceptDragAndDrop)(SDL_پنجره *پنجره, bool accept);

    // Display the system-level window menu
    فراغ (*Show_پنجره_System_Menu)(SDL_پنجره *پنجره, صحيح x, صحيح y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    فراغ *wakeup_پنجره;
    صحيح رقم_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_پنجره *windows;
    SDL_پنجره *grabbed_پنجره;
    Uint32 clipboard_sequence;
    SDL_Clipboard_داده_Callback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    فراغ *clipboard_userdata;
    حرف **clipboard_mime_types;
    size_t رقم_clipboard_mime_types;
    حرف *primary_selection_متن;
    bool setting_display_نما;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    بنية
    {
        صحيح red_اندازه;
        صحيح green_اندازه;
        صحيح blue_اندازه;
        صحيح alpha_اندازه;
        صحيح عمق_اندازه;
        صحيح میانگیر_اندازه;
        صحيح stencil_اندازه;
        صحيح double_میانگیر;
        صحيح accum_red_اندازه;
        صحيح accum_green_اندازه;
        صحيح accum_blue_اندازه;
        صحيح accum_alpha_اندازه;
        صحيح stereo;
        صحيح multisamplebuffers;
        صحيح multisamplesamples;
        صحيح floatbuffers;
        صحيح accelerated;
        صحيح major_نسخه;
        صحيح minor_نسخه;
        صحيح flags;
        صحيح profile_ماسک;
        صحيح share_with_current_context;
        صحيح release_behavior;
        صحيح reset_notification;
        صحيح framebuffer_srgb_capable;
        صحيح no_error;
        صحيح retained_backing;
        صحيح egl_platform;
        صحيح driver_loaded;
        صحيح HAS_GL_ARB_color_میانگیر_float;
        حرف driver_مسیر[256];
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
    SDL_پنجره *current_glwin;
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
        SDL_Function_اشاره_گر vkGetInstanceProcAddr;
        SDL_Function_اشاره_گر vkEnumerateInstanceExtensionProperties;
        صحيح loader_loaded;
        حرف loader_مسیر[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_Video_داده *داخلی;
    بنية SDL_GLDriver_داده *gl_داده;

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    بنية SDL_EGL_Video_داده *egl_داده;
#پایان_اگر

#إذا defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    بنية SDL_خصوصی_GLESData *gles_داده;
#پایان_اگر

    /* * * */
    // The function used to dispose of this structure
    فراغ (*حرر)(SDL_VideoDevice *_this);
};

تعريفنوع بنية VideoBootStrap
{
    ثابت حرف *name;
    ثابت حرف *desc;
    SDL_VideoDevice *(*create)(فراغ);
    bool (*Show_پیام_Box)(ثابت SDL_پیام_Box_داده *messageboxdata, صحيح *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
خارجي VideoBootStrap خصوصی_bootstrap;
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
خارجي فراغ SDL_مجموعه_System_Theme(SDL_SystemTheme theme);
خارجي SDL_DisplayID SDL_جمع_کن_Basic_Video_Display(ثابت SDL_Display_نما *desktop_نما);
خارجي SDL_DisplayID SDL_جمع_کن_Video_Display(ثابت SDL_VideoDisplay *display, bool send_event);
خارجي فراغ SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
خارجي bool SDL_جمع_کن_Fullscreen_Display_نما(SDL_VideoDisplay *display, ثابت SDL_Display_نما *نما);
خارجي فراغ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
خارجي فراغ SDL_مجموعه_Desktop_Display_نما(SDL_VideoDisplay *display, ثابت SDL_Display_نما *نما);
خارجي فراغ SDL_مجموعه_Current_Display_نما(SDL_VideoDisplay *display, ثابت SDL_Display_نما *نما);
خارجي فراغ SDL_مجموعه_Display_Content_Scale(SDL_VideoDisplay *display, عائم scale);
خارجي فراغ SDL_مجموعه_Display_HDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR);
خارجي bool SDL_مجموعه_Display_نما_For_Display(SDL_VideoDisplay *display, SDL_Display_نما *نما);
خارجي SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
خارجي SDL_DisplayID SDL_Get_Display_For_پنجره_Position(SDL_پنجره *پنجره);
خارجي SDL_VideoDisplay *SDL_Get_Video_Display_For_پنجره(SDL_پنجره *پنجره);
خارجي SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_پنجره(SDL_پنجره *پنجره);
خارجي صحيح SDL_Get_Display_شاخص(SDL_DisplayID displayID);
خارجي SDL_Display_داده *SDL_Get_Display_Driver_داده(SDL_DisplayID display);
خارجي SDL_Display_داده *SDL_Get_Display_Driver_داده_For_پنجره(SDL_پنجره *پنجره);
خارجي صحيح SDL_Get_پیام_Box_شمار(فراغ);
خارجي فراغ SDL_مجموعه_پنجره_HDRProperties(SDL_پنجره *پنجره, ثابت SDL_HDROutputProperties *HDR, bool send_event);
خارجي فراغ SDL_مجموعه_پنجره_امن_Area_Insets(SDL_پنجره *پنجره, صحيح چپ, صحيح راست, صحيح بالاترین, صحيح bottom);

خارجي فراغ SDL_GL_DeduceMaxSupportedESProfile(صحيح *major, صحيح *minor);

خارجي bool SDL_Recreate_پنجره(SDL_پنجره *پنجره, SDL_پنجره_Flags flags);
خارجي bool SDL_Reconfigure_پنجره(SDL_پنجره *پنجره, SDL_پنجره_Flags flags);
خارجي bool SDL_HasWindows(فراغ);
خارجي فراغ SDL_Relative_مقصد_Global_For_پنجره(SDL_پنجره *پنجره, صحيح rel_x, صحيح rel_y, صحيح *abs_x, صحيح *abs_y);
خارجي فراغ SDL_Global_مقصد_Relative_For_پنجره(SDL_پنجره *پنجره, صحيح abs_x, صحيح abs_y, صحيح *rel_x, صحيح *rel_y);
خارجي bool SDL_ShouldFocusPopup(SDL_پنجره *پنجره);
خارجي bool SDL_ShouldRelinquishPopupFocus(SDL_پنجره *پنجره, SDL_پنجره **new_focus);

خارجي فراغ SDL_OnDisplayAdded(SDL_VideoDisplay *display);
خارجي فراغ SDL_OnDisplayMoved(SDL_VideoDisplay *display);
خارجي فراغ SDL_On_پنجره_Shown(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_Hidden(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_Moved(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_Resized(SDL_پنجره *پنجره);
خارجي فراغ SDL_Check_پنجره_Pixel_اندازه_تغییریافته(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_Pixel_اندازه_تغییریافته(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_زنده_Resize_Update(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_Minimized(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_Maximized(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_Restored(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_Enter(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_Leave(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_Focus_Gained(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_Focus_گمشده(SDL_پنجره *پنجره);
خارجي فراغ SDL_On_پنجره_Display_تغییریافته(SDL_پنجره *پنجره);
خارجي فراغ SDL_Update_پنجره_Grab(SDL_پنجره *پنجره);
خارجي bool SDL_Update_Fullscreen_نما(SDL_پنجره *پنجره, SDL_FullscreenOp fullscreen, bool commit);
خارجي SDL_پنجره *SDL_GetToplevelForKeyboardFocus(فراغ);

خارجي bool SDL_ShouldAllowTopmost(فراغ);

خارجي فراغ SDL_ToggleDragAndDropSupport(فراغ);

خارجي فراغ SDL_UpdateDesktopBounds(فراغ);

خارجي SDL_متن_درون_داد_Type SDL_Get_متن_درون_داد_Type(SDL_PropertiesID props);
خارجي SDL_Capitalization SDL_Get_متن_درون_داد_Capitalization(SDL_PropertiesID props);
خارجي bool SDL_Get_متن_درون_داد_Autocorrect(SDL_PropertiesID props);
خارجي bool SDL_Get_متن_درون_داد_Multiline(SDL_PropertiesID props);

خارجي فراغ SDL_SendScreenKeyboardShown(فراغ);
خارجي فراغ SDL_SendScreenKeyboardHidden(فراغ);

#پایان_اگر // SDL_sysvideo_h_
