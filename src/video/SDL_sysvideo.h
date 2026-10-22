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

#که_نه_تعریف_شوی SDL_sysvideo_h_
#تعریف_کړه SDL_sysvideo_h_

#ضمن <SDL3/SDL_vulkan.h>

#ضمن "SDL_surface_c.h"

// The SDL video driver

تعريفنوع بنية SDL_VideoDisplay SDL_VideoDisplay;
تعريفنوع بنية SDL_VideoDevice SDL_VideoDevice;
تعريفنوع بنية SDL_Video_معلومات SDL_Video_معلومات;
تعريفنوع بنية SDL_Display_معلومات SDL_Display_معلومات;
تعريفنوع بنية SDL_کړکۍ_معلومات SDL_کړکۍ_معلومات;

تعريفنوع بنية
{
    عائم SDR_white_level;
    عائم HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
بنية SDL_کړکۍ
{
    SDL_کړکۍ_ID id;
    حرف *title;
    SDL_Surface *icon;
    صحيح x, y;
    صحيح w, h;
    صحيح min_w, min_h;
    صحيح max_w, max_h;
    عائم min_aspect;
    عائم max_aspect;
    صحيح وروستی_pixel_w, وروستی_pixel_h;
    SDL_کړکۍ_Flags flags;
    SDL_کړکۍ_Flags pending_flags;
    عائم display_scale;
    bool external_graphics_context;
    bool fullscreen_exclusive;  // The window is currently fullscreen exclusive
    SDL_DisplayID وروستی_fullscreen_exclusive_display;  // The last fullscreen_exclusive display
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

    SDL_Display_ډېرپېښ requested_fullscreen_ډېرپېښ;
    SDL_Display_ډېرپېښ current_fullscreen_ډېرپېښ;
    SDL_HDROutputProperties HDR;

    عائم opacity;

    SDL_Surface *surface;
    bool surface_valid;

    bool is_hiding;
    bool restore_on_show; // Child was hidden recursively by the parent, restore when shown.
    bool وروستی_position_pending; // This should NOT be cleared by the backend, as it is used for fullscreen positioning.
    bool وروستی_اندازه_pending; // This should be cleared by the backend if the new size cannot be applied.
    bool update_fullscreen_on_display_بدل_شوی;
    bool constrain_popup;
    bool is_destroying;
    bool is_dropping; // drag/drop in progress, expecting SDL_SendDropComplete().

    صحيح خوندي_inset_کیڼ;
    صحيح خوندي_inset_ښی;
    صحيح خوندي_inset_سر;
    صحيح خوندي_inset_bottom;
    SDL_Rect خوندي_rect;

    SDL_PropertiesID متن_ننوت_props;
    bool متن_ننوت_فعال;
    SDL_Rect متن_ننوت_rect;
    صحيح متن_ننوت_cursor;

    SDL_Rect mouse_rect;

    SDL_موندنه_Test موندنه_test;
    فراغ *موندنه_test_معلومات;

    SDL_پرمختګ_State پرمختګ_state;
    عائم پرمختګ_ارزښت;

    SDL_PropertiesID props;

    صحيح عدد_renderers;
    SDL_Renderer **renderers;

    SDL_کړکۍ_معلومات *دننی;

    // If a toplevel window, holds the current keyboard focus for grabbing popups.
    SDL_کړکۍ *keyboard_focus;

    SDL_کړکۍ *prev;
    SDL_کړکۍ *بل;

    SDL_کړکۍ *پلار;
    SDL_کړکۍ *لومړی_ماشوم;
    SDL_کړکۍ *prev_sibling;
    SDL_کړکۍ *بل_sibling;
};
#تعریف_کړه SDL_کړکۍ_FULLSCREEN_VISIBLE(W)        \
    ((((W)->flags & SDL_کړکۍ_FULLSCREEN) != 0) &&   \
     (((W)->flags & SDL_کړکۍ_HIDDEN) == 0) && \
     (((W)->flags & SDL_کړکۍ_MINIMIZED) == 0))

#تعریف_کړه SDL_کړکۍ_IS_POPUP(W) \
    (((W)->flags & (SDL_کړکۍ_TOOLTIP | SDL_کړکۍ_POPUP_MENU)) != 0)

/*
 * Define the SDL display structure.
 * This corresponds to physical monitors attached to the system.
 */
بنية SDL_VideoDisplay
{
    SDL_DisplayID id;
    حرف *name;
    صحيح max_fullscreen_modes;
    صحيح عدد_fullscreen_modes;
    SDL_Display_ډېرپېښ *fullscreen_modes;
    SDL_Display_ډېرپېښ desktop_ډېرپېښ;
    ثابت SDL_Display_ډېرپېښ *current_ډېرپېښ;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    عائم content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_فعال;
    SDL_کړکۍ *fullscreen_کړکۍ;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_Display_معلومات *دننی;
};

// Video device flags
تعريفنوع تعداد
{
    VIDEO_DEVICE_CAPS_ډېرپېښ_SWITCHING_EMULATED = 0x01,
    VIDEO_DEVICE_CAPS_HAS_POPUP_کړکۍ_SUPPORT = 0x02,
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
} SDL_Fullscreen_پایله;

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
    bool (*سېټ_Display_ډېرپېښ)(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ);

    /* * * */
    /*
     * Window functions
     */
    bool (*CreateSDLWindow)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props);
    فراغ (*سېټ_کړکۍ_Title)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*سېټ_کړکۍ_Icon)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_Surface *icon);
    bool (*سېټ_کړکۍ_Position)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*سېټ_کړکۍ_اندازه)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*سېټ_کړکۍ_Minimum_اندازه)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*سېټ_کړکۍ_اعظمي_اندازه)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*سېټ_کړکۍ_Aspect_نسبت)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*Get_کړکۍ_Borders_اندازه)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *سر, صحيح *کیڼ, صحيح *bottom, صحيح *ښی);
    عائم (*Get_کړکۍ_Content_Scale)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*Get_کړکۍ_اندازه_دننه_Pixels)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *w, صحيح *h);
    bool (*سېټ_کړکۍ_Opacity)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, عائم opacity);
    bool (*سېټ_کړکۍ_پلار)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_کړکۍ *پلار);
    bool (*سېټ_کړکۍ_Modal)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool modal);
    فراغ (*Show_کړکۍ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*Hide_کړکۍ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*Raise_کړکۍ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*Maximize_کړکۍ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*Minimize_کړکۍ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*Restore_کړکۍ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*سېټ_کړکۍ_Bordered)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool bordered);
    فراغ (*سېټ_کړکۍ_Resizable)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool resizable);
    فراغ (*سېټ_کړکۍ_Always_On_سر)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool on_سر);
    SDL_Fullscreen_پایله (*سېټ_کړکۍ_Fullscreen)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    فراغ *(*Get_کړکۍ_ICCProfile)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, size_t *اندازه);
    SDL_DisplayID (*Get_Display_For_کړکۍ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*سېټ_کړکۍ_Mouse_Rect)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*سېټ_کړکۍ_Mouse_Grab)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed);
    bool (*سېټ_کړکۍ_Keyboard_Grab)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed);
    فراغ (*Destroy_کړکۍ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*Create_کړکۍ_Framebuffer)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch);
    bool (*سېټ_کړکۍ_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح vsync);
    bool (*Get_کړکۍ_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *vsync);
    bool (*Update_کړکۍ_Framebuffer)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, ثابت SDL_Rect *rects, صحيح numrects);
    فراغ (*Destroy_کړکۍ_Framebuffer)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*On_کړکۍ_Enter)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*Update_کړکۍ_Shape)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_Surface *shape);
    bool (*Flash_کړکۍ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_FlashOperation operation);
    bool (*Apply_کړکۍ_پرمختګ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*سېټ_کړکۍ_Focusable)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool focusable);
    bool (*سېټ_کړکۍ_Fill_Document)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool fill);
    bool (*Sync_کړکۍ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*Reconfigure_کړکۍ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_کړکۍ_Flags flags);

    /* * * */
    /*
     * OpenGL support
     */
    bool (*GL_بارول_Library)(SDL_VideoDevice *_this, ثابت حرف *لار);
    SDL_Function_اشاره_ګر (*GL_Get_Proc_پته)(SDL_VideoDevice *_this, ثابت حرف *proc);
    فراغ (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*GL_سېټ_بدلون_Interval)(SDL_VideoDevice *_this, صحيح interval);
    bool (*GL_Get_بدلون_Interval)(SDL_VideoDevice *_this, صحيح *interval);
    bool (*GL_بدلون_کړکۍ)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    فراغ (*GL_سېټ_Default_Profile_Config)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_بارول_Library)(SDL_VideoDevice *_this, ثابت حرف *لار);
    فراغ (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    حرف ثابت * ثابت *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *شمېر);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, VkInstance instance, ثابت بنية Vk_ویش_Callbacks *allocator, VkSurfaceKHR *surface);
    فراغ (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ثابت بنية Vk_ویش_Callbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 کتار_Family_شاخص);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    فراغ *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    صحيح (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    فراغ (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*پیل_متن_ننوت)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props);
    bool (*Stop_متن_ننوت)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*Update_متن_ننوت_Area)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    فراغ (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props);
    فراغ (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
    فراغ (*سېټ_متن_ننوت_Properties)(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props);

    // Clipboard
    ثابت حرف *ثابت *(*Get_متن_Mime_Types)(SDL_VideoDevice *_this, size_t *عدد_mime_types);
    bool (*سېټ_Clipboard_معلومات)(SDL_VideoDevice *_this);
    فراغ *(*Get_Clipboard_معلومات)(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *اندازه);
    bool (*Has_Clipboard_معلومات)(SDL_VideoDevice *_this, ثابت حرف *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*سېټ_Clipboard_متن)(SDL_VideoDevice *_this, ثابت حرف *متن);
    حرف *(*Get_Clipboard_متن)(SDL_VideoDevice *_this);
    bool (*Has_Clipboard_متن)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*سېټ_Primary_Selection_متن)(SDL_VideoDevice *_this, ثابت حرف *متن);
    حرف *(*Get_Primary_Selection_متن)(SDL_VideoDevice *_this);
    bool (*Has_Primary_Selection_متن)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*Show_پیغام_Box)(SDL_VideoDevice *_this, ثابت SDL_پیغام_Box_معلومات *messageboxdata, صحيح *buttonID);

    // Hit-testing
    bool (*سېټ_کړکۍ_موندنه_Test)(SDL_کړکۍ *کړکۍ, bool enabled);

    // Tell window that app enabled drag'n'drop events
    فراغ (*AcceptDragAndDrop)(SDL_کړکۍ *کړکۍ, bool accept);

    // Display the system-level window menu
    فراغ (*Show_کړکۍ_System_Menu)(SDL_کړکۍ *کړکۍ, صحيح x, صحيح y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    فراغ *wakeup_کړکۍ;
    صحيح عدد_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_کړکۍ *windows;
    SDL_کړکۍ *grabbed_کړکۍ;
    Uint32 clipboard_sequence;
    SDL_Clipboard_معلومات_Callback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    فراغ *clipboard_userdata;
    حرف **clipboard_mime_types;
    size_t عدد_clipboard_mime_types;
    حرف *primary_selection_متن;
    bool setting_display_ډېرپېښ;
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
        صحيح ژوروالی_اندازه;
        صحيح بفر_اندازه;
        صحيح stencil_اندازه;
        صحيح double_بفر;
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
        صحيح HAS_GL_ARB_color_بفر_float;
        حرف driver_لار[256];
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
    SDL_کړکۍ *current_glwin;
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
        SDL_Function_اشاره_ګر vkGetInstanceProcAddr;
        SDL_Function_اشاره_ګر vkEnumerateInstanceExtensionProperties;
        صحيح loader_loaded;
        حرف loader_لار[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_Video_معلومات *دننی;
    بنية SDL_GLDriver_معلومات *gl_معلومات;

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    بنية SDL_EGL_Video_معلومات *egl_معلومات;
#د_که_پای

#إذا defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    بنية SDL_شخصي_GLESData *gles_معلومات;
#د_که_پای

    /* * * */
    // The function used to dispose of this structure
    فراغ (*حرر)(SDL_VideoDevice *_this);
};

تعريفنوع بنية VideoBootStrap
{
    ثابت حرف *name;
    ثابت حرف *desc;
    SDL_VideoDevice *(*create)(فراغ);
    bool (*Show_پیغام_Box)(ثابت SDL_پیغام_Box_معلومات *messageboxdata, صحيح *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
خارجي VideoBootStrap شخصي_bootstrap;
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
خارجي فراغ SDL_سېټ_System_Theme(SDL_SystemTheme theme);
خارجي SDL_DisplayID SDL_جمع_کړه_Basic_Video_Display(ثابت SDL_Display_ډېرپېښ *desktop_ډېرپېښ);
خارجي SDL_DisplayID SDL_جمع_کړه_Video_Display(ثابت SDL_VideoDisplay *display, bool send_event);
خارجي فراغ SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
خارجي bool SDL_جمع_کړه_Fullscreen_Display_ډېرپېښ(SDL_VideoDisplay *display, ثابت SDL_Display_ډېرپېښ *ډېرپېښ);
خارجي فراغ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
خارجي فراغ SDL_سېټ_Desktop_Display_ډېرپېښ(SDL_VideoDisplay *display, ثابت SDL_Display_ډېرپېښ *ډېرپېښ);
خارجي فراغ SDL_سېټ_Current_Display_ډېرپېښ(SDL_VideoDisplay *display, ثابت SDL_Display_ډېرپېښ *ډېرپېښ);
خارجي فراغ SDL_سېټ_Display_Content_Scale(SDL_VideoDisplay *display, عائم scale);
خارجي فراغ SDL_سېټ_Display_HDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR);
خارجي bool SDL_سېټ_Display_ډېرپېښ_For_Display(SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ);
خارجي SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
خارجي SDL_DisplayID SDL_Get_Display_For_کړکۍ_Position(SDL_کړکۍ *کړکۍ);
خارجي SDL_VideoDisplay *SDL_Get_Video_Display_For_کړکۍ(SDL_کړکۍ *کړکۍ);
خارجي SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_کړکۍ(SDL_کړکۍ *کړکۍ);
خارجي صحيح SDL_Get_Display_شاخص(SDL_DisplayID displayID);
خارجي SDL_Display_معلومات *SDL_Get_Display_Driver_معلومات(SDL_DisplayID display);
خارجي SDL_Display_معلومات *SDL_Get_Display_Driver_معلومات_For_کړکۍ(SDL_کړکۍ *کړکۍ);
خارجي صحيح SDL_Get_پیغام_Box_شمېر(فراغ);
خارجي فراغ SDL_سېټ_کړکۍ_HDRProperties(SDL_کړکۍ *کړکۍ, ثابت SDL_HDROutputProperties *HDR, bool send_event);
خارجي فراغ SDL_سېټ_کړکۍ_خوندي_Area_Insets(SDL_کړکۍ *کړکۍ, صحيح کیڼ, صحيح ښی, صحيح سر, صحيح bottom);

خارجي فراغ SDL_GL_DeduceMaxSupportedESProfile(صحيح *major, صحيح *minor);

خارجي bool SDL_Recreate_کړکۍ(SDL_کړکۍ *کړکۍ, SDL_کړکۍ_Flags flags);
خارجي bool SDL_Reconfigure_کړکۍ(SDL_کړکۍ *کړکۍ, SDL_کړکۍ_Flags flags);
خارجي bool SDL_HasWindows(فراغ);
خارجي فراغ SDL_Relative_منزل_Global_For_کړکۍ(SDL_کړکۍ *کړکۍ, صحيح rel_x, صحيح rel_y, صحيح *abs_x, صحيح *abs_y);
خارجي فراغ SDL_Global_منزل_Relative_For_کړکۍ(SDL_کړکۍ *کړکۍ, صحيح abs_x, صحيح abs_y, صحيح *rel_x, صحيح *rel_y);
خارجي bool SDL_ShouldFocusPopup(SDL_کړکۍ *کړکۍ);
خارجي bool SDL_ShouldRelinquishPopupFocus(SDL_کړکۍ *کړکۍ, SDL_کړکۍ **new_focus);

خارجي فراغ SDL_OnDisplayAdded(SDL_VideoDisplay *display);
خارجي فراغ SDL_OnDisplayMoved(SDL_VideoDisplay *display);
خارجي فراغ SDL_On_کړکۍ_Shown(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_Hidden(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_Moved(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_Resized(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_Check_کړکۍ_Pixel_اندازه_بدل_شوی(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_Pixel_اندازه_بدل_شوی(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_ژوندی_Resize_Update(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_Minimized(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_Maximized(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_Restored(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_Enter(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_Leave(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_Focus_Gained(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_Focus_ورک(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_On_کړکۍ_Display_بدل_شوی(SDL_کړکۍ *کړکۍ);
خارجي فراغ SDL_Update_کړکۍ_Grab(SDL_کړکۍ *کړکۍ);
خارجي bool SDL_Update_Fullscreen_ډېرپېښ(SDL_کړکۍ *کړکۍ, SDL_FullscreenOp fullscreen, bool commit);
خارجي SDL_کړکۍ *SDL_GetToplevelForKeyboardFocus(فراغ);

خارجي bool SDL_ShouldAllowTopmost(فراغ);

خارجي فراغ SDL_ToggleDragAndDropSupport(فراغ);

خارجي فراغ SDL_UpdateDesktopBounds(فراغ);

خارجي SDL_متن_ننوت_Type SDL_Get_متن_ننوت_Type(SDL_PropertiesID props);
خارجي SDL_Capitalization SDL_Get_متن_ننوت_Capitalization(SDL_PropertiesID props);
خارجي bool SDL_Get_متن_ننوت_Autocorrect(SDL_PropertiesID props);
خارجي bool SDL_Get_متن_ننوت_Multiline(SDL_PropertiesID props);

خارجي فراغ SDL_SendScreenKeyboardShown(فراغ);
خارجي فراغ SDL_SendScreenKeyboardHidden(فراغ);

#د_که_پای // SDL_sysvideo_h_
