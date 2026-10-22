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

#جے_بنا_تعریف SDL_sysvideo_h_
#تعریف_کرو SDL_sysvideo_h_

#ضمن <SDL3/SDL_vulkan.h>

#ضمن "SDL_surface_c.h"

// The SDL video driver

تعريفنوع بنية SDL_VideoDisplay SDL_VideoDisplay;
تعريفنوع بنية SDL_VideoDevice SDL_VideoDevice;
تعريفنوع بنية SDL_Video_انکڑے SDL_Video_انکڑے;
تعريفنوع بنية SDL_Display_انکڑے SDL_Display_انکڑے;
تعريفنوع بنية SDL_کھڑکی_انکڑے SDL_کھڑکی_انکڑے;

تعريفنوع بنية
{
    عائم SDR_white_level;
    عائم HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
بنية SDL_کھڑکی
{
    SDL_کھڑکی_ID id;
    حرف *title;
    SDL_Surface *icon;
    صحيح x, y;
    صحيح w, h;
    صحيح min_w, min_h;
    صحيح max_w, max_h;
    عائم min_aspect;
    عائم max_aspect;
    صحيح آخری_pixel_w, آخری_pixel_h;
    SDL_کھڑکی_Flags flags;
    SDL_کھڑکی_Flags pending_flags;
    عائم display_scale;
    bool external_graphics_context;
    bool fullscreen_exclusive;  // The window is currently fullscreen exclusive
    SDL_DisplayID آخری_fullscreen_exclusive_display;  // The last fullscreen_exclusive display
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

    SDL_Display_منوال requested_fullscreen_منوال;
    SDL_Display_منوال current_fullscreen_منوال;
    SDL_HDROutputProperties HDR;

    عائم opacity;

    SDL_Surface *surface;
    bool surface_valid;

    bool is_hiding;
    bool restore_on_show; // Child was hidden recursively by the parent, restore when shown.
    bool آخری_position_pending; // This should NOT be cleared by the backend, as it is used for fullscreen positioning.
    bool آخری_ناپ_pending; // This should be cleared by the backend if the new size cannot be applied.
    bool update_fullscreen_on_display_بدلیا;
    bool constrain_popup;
    bool is_destroying;
    bool is_dropping; // drag/drop in progress, expecting SDL_SendDropComplete().

    صحيح محفوظ_inset_بایاں;
    صحيح محفوظ_inset_دایاں;
    صحيح محفوظ_inset_چوٹی;
    صحيح محفوظ_inset_bottom;
    SDL_Rect محفوظ_rect;

    SDL_PropertiesID متن_داخلہ_props;
    bool متن_داخلہ_سرگرم;
    SDL_Rect متن_داخلہ_rect;
    صحيح متن_داخلہ_cursor;

    SDL_Rect mouse_rect;

    SDL_کامیابی_Test کامیابی_test;
    فراغ *کامیابی_test_انکڑے;

    SDL_ترقی_State ترقی_state;
    عائم ترقی_قدر;

    SDL_PropertiesID props;

    صحيح عدد_renderers;
    SDL_Renderer **renderers;

    SDL_کھڑکی_انکڑے *اندرونی;

    // If a toplevel window, holds the current keyboard focus for grabbing popups.
    SDL_کھڑکی *keyboard_focus;

    SDL_کھڑکی *prev;
    SDL_کھڑکی *اگلا;

    SDL_کھڑکی *ماپا;
    SDL_کھڑکی *پہلا_بچہ;
    SDL_کھڑکی *prev_sibling;
    SDL_کھڑکی *اگلا_sibling;
};
#تعریف_کرو SDL_کھڑکی_FULLSCREEN_VISIBLE(W)        \
    ((((W)->flags & SDL_کھڑکی_FULLSCREEN) != 0) &&   \
     (((W)->flags & SDL_کھڑکی_HIDDEN) == 0) && \
     (((W)->flags & SDL_کھڑکی_MINIMIZED) == 0))

#تعریف_کرو SDL_کھڑکی_IS_POPUP(W) \
    (((W)->flags & (SDL_کھڑکی_TOOLTIP | SDL_کھڑکی_POPUP_MENU)) != 0)

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
    SDL_Display_منوال *fullscreen_modes;
    SDL_Display_منوال desktop_منوال;
    ثابت SDL_Display_منوال *current_منوال;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    عائم content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_سرگرم;
    SDL_کھڑکی *fullscreen_کھڑکی;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_Display_انکڑے *اندرونی;
};

// Video device flags
تعريفنوع تعداد
{
    VIDEO_DEVICE_CAPS_منوال_SWITCHING_EMULATED = 0x01,
    VIDEO_DEVICE_CAPS_HAS_POPUP_کھڑکی_SUPPORT = 0x02,
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
} SDL_Fullscreen_نتیجہ;

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
    bool (*سیٹ_Display_منوال)(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);

    /* * * */
    /*
     * Window functions
     */
    bool (*CreateSDLWindow)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
    فراغ (*سیٹ_کھڑکی_Title)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*سیٹ_کھڑکی_Icon)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon);
    bool (*سیٹ_کھڑکی_Position)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*سیٹ_کھڑکی_ناپ)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*سیٹ_کھڑکی_Minimum_ناپ)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*سیٹ_کھڑکی_Aspect_تناسب)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*Get_کھڑکی_Borders_ناپ)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *چوٹی, صحيح *بایاں, صحيح *bottom, صحيح *دایاں);
    عائم (*Get_کھڑکی_Content_Scale)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*Get_کھڑکی_ناپ_وچ_Pixels)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *w, صحيح *h);
    bool (*سیٹ_کھڑکی_Opacity)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, عائم opacity);
    bool (*سیٹ_کھڑکی_ماپا)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *ماپا);
    bool (*سیٹ_کھڑکی_Modal)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal);
    فراغ (*Show_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*Hide_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*Raise_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*Maximize_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*Minimize_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*Restore_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*سیٹ_کھڑکی_Bordered)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered);
    فراغ (*سیٹ_کھڑکی_Resizable)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable);
    فراغ (*سیٹ_کھڑکی_Always_On_چوٹی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool on_چوٹی);
    SDL_Fullscreen_نتیجہ (*سیٹ_کھڑکی_Fullscreen)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    فراغ *(*Get_کھڑکی_ICCProfile)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *ناپ);
    SDL_DisplayID (*Get_Display_For_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*سیٹ_کھڑکی_Mouse_Rect)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*سیٹ_کھڑکی_Mouse_Grab)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
    bool (*سیٹ_کھڑکی_Keyboard_Grab)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
    فراغ (*Destroy_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*Create_کھڑکی_Framebuffer)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch);
    bool (*سیٹ_کھڑکی_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح vsync);
    bool (*Get_کھڑکی_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *vsync);
    bool (*Update_کھڑکی_Framebuffer)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحيح numrects);
    فراغ (*Destroy_کھڑکی_Framebuffer)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*On_کھڑکی_Enter)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*Update_کھڑکی_Shape)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *shape);
    bool (*Flash_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation);
    bool (*Apply_کھڑکی_ترقی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*سیٹ_کھڑکی_Focusable)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable);
    bool (*سیٹ_کھڑکی_Fill_Document)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool fill);
    bool (*Sync_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*Reconfigure_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags);

    /* * * */
    /*
     * OpenGL support
     */
    bool (*GL_لدو_Library)(SDL_VideoDevice *_this, ثابت حرف *رستہ);
    SDL_Function_اشارہ_گر (*GL_Get_Proc_پتہ)(SDL_VideoDevice *_this, ثابت حرف *proc);
    فراغ (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*GL_سیٹ_وٹاندرا_Interval)(SDL_VideoDevice *_this, صحيح interval);
    bool (*GL_Get_وٹاندرا_Interval)(SDL_VideoDevice *_this, صحيح *interval);
    bool (*GL_وٹاندرا_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    فراغ (*GL_سیٹ_Default_Profile_Config)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_لدو_Library)(SDL_VideoDevice *_this, ثابت حرف *رستہ);
    فراغ (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    حرف ثابت * ثابت *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *گنتی);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, VkInstance instance, ثابت بنية Vk_ونڈ_Callbacks *allocator, VkSurfaceKHR *surface);
    فراغ (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ثابت بنية Vk_ونڈ_Callbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 قطار_Family_اشاریہ);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    فراغ *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    صحيح (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    فراغ (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*شروع_متن_داخلہ)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);
    bool (*Stop_متن_داخلہ)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*Update_متن_داخلہ_Area)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    فراغ (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);
    فراغ (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    فراغ (*سیٹ_متن_داخلہ_Properties)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);

    // Clipboard
    ثابت حرف *ثابت *(*Get_متن_Mime_Types)(SDL_VideoDevice *_this, size_t *عدد_mime_types);
    bool (*سیٹ_Clipboard_انکڑے)(SDL_VideoDevice *_this);
    فراغ *(*Get_Clipboard_انکڑے)(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *ناپ);
    bool (*Has_Clipboard_انکڑے)(SDL_VideoDevice *_this, ثابت حرف *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*سیٹ_Clipboard_متن)(SDL_VideoDevice *_this, ثابت حرف *متن);
    حرف *(*Get_Clipboard_متن)(SDL_VideoDevice *_this);
    bool (*Has_Clipboard_متن)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*سیٹ_Primary_Selection_متن)(SDL_VideoDevice *_this, ثابت حرف *متن);
    حرف *(*Get_Primary_Selection_متن)(SDL_VideoDevice *_this);
    bool (*Has_Primary_Selection_متن)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*Show_سنیہا_Box)(SDL_VideoDevice *_this, ثابت SDL_سنیہا_Box_انکڑے *messageboxdata, صحيح *buttonID);

    // Hit-testing
    bool (*سیٹ_کھڑکی_کامیابی_Test)(SDL_کھڑکی *کھڑکی, bool enabled);

    // Tell window that app enabled drag'n'drop events
    فراغ (*AcceptDragAndDrop)(SDL_کھڑکی *کھڑکی, bool accept);

    // Display the system-level window menu
    فراغ (*Show_کھڑکی_System_Menu)(SDL_کھڑکی *کھڑکی, صحيح x, صحيح y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    فراغ *wakeup_کھڑکی;
    صحيح عدد_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_کھڑکی *windows;
    SDL_کھڑکی *grabbed_کھڑکی;
    Uint32 clipboard_sequence;
    SDL_Clipboard_انکڑے_Callback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    فراغ *clipboard_userdata;
    حرف **clipboard_mime_types;
    size_t عدد_clipboard_mime_types;
    حرف *primary_selection_متن;
    bool setting_display_منوال;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    بنية
    {
        صحيح red_ناپ;
        صحيح green_ناپ;
        صحيح blue_ناپ;
        صحيح alpha_ناپ;
        صحيح ڈونگھائی_ناپ;
        صحيح بفر_ناپ;
        صحيح stencil_ناپ;
        صحيح double_بفر;
        صحيح accum_red_ناپ;
        صحيح accum_green_ناپ;
        صحيح accum_blue_ناپ;
        صحيح accum_alpha_ناپ;
        صحيح stereo;
        صحيح multisamplebuffers;
        صحيح multisamplesamples;
        صحيح floatbuffers;
        صحيح accelerated;
        صحيح major_نسخہ;
        صحيح minor_نسخہ;
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
        حرف driver_رستہ[256];
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
    SDL_کھڑکی *current_glwin;
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
        SDL_Function_اشارہ_گر vkGetInstanceProcAddr;
        SDL_Function_اشارہ_گر vkEnumerateInstanceExtensionProperties;
        صحيح loader_loaded;
        حرف loader_رستہ[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_Video_انکڑے *اندرونی;
    بنية SDL_GLDriver_انکڑے *gl_انکڑے;

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    بنية SDL_EGL_Video_انکڑے *egl_انکڑے;
#جے_انت

#إذا defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    بنية SDL_نجی_GLESData *gles_انکڑے;
#جے_انت

    /* * * */
    // The function used to dispose of this structure
    فراغ (*حرر)(SDL_VideoDevice *_this);
};

تعريفنوع بنية VideoBootStrap
{
    ثابت حرف *name;
    ثابت حرف *desc;
    SDL_VideoDevice *(*create)(فراغ);
    bool (*Show_سنیہا_Box)(ثابت SDL_سنیہا_Box_انکڑے *messageboxdata, صحيح *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
خارجي VideoBootStrap نجی_bootstrap;
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
خارجي فراغ SDL_سیٹ_System_Theme(SDL_SystemTheme theme);
خارجي SDL_DisplayID SDL_جوڑو_Basic_Video_Display(ثابت SDL_Display_منوال *desktop_منوال);
خارجي SDL_DisplayID SDL_جوڑو_Video_Display(ثابت SDL_VideoDisplay *display, bool send_event);
خارجي فراغ SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
خارجي bool SDL_جوڑو_Fullscreen_Display_منوال(SDL_VideoDisplay *display, ثابت SDL_Display_منوال *منوال);
خارجي فراغ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
خارجي فراغ SDL_سیٹ_Desktop_Display_منوال(SDL_VideoDisplay *display, ثابت SDL_Display_منوال *منوال);
خارجي فراغ SDL_سیٹ_Current_Display_منوال(SDL_VideoDisplay *display, ثابت SDL_Display_منوال *منوال);
خارجي فراغ SDL_سیٹ_Display_Content_Scale(SDL_VideoDisplay *display, عائم scale);
خارجي فراغ SDL_سیٹ_Display_HDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR);
خارجي bool SDL_سیٹ_Display_منوال_For_Display(SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
خارجي SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
خارجي SDL_DisplayID SDL_Get_Display_For_کھڑکی_Position(SDL_کھڑکی *کھڑکی);
خارجي SDL_VideoDisplay *SDL_Get_Video_Display_For_کھڑکی(SDL_کھڑکی *کھڑکی);
خارجي SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_کھڑکی(SDL_کھڑکی *کھڑکی);
خارجي صحيح SDL_Get_Display_اشاریہ(SDL_DisplayID displayID);
خارجي SDL_Display_انکڑے *SDL_Get_Display_Driver_انکڑے(SDL_DisplayID display);
خارجي SDL_Display_انکڑے *SDL_Get_Display_Driver_انکڑے_For_کھڑکی(SDL_کھڑکی *کھڑکی);
خارجي صحيح SDL_Get_سنیہا_Box_گنتی(فراغ);
خارجي فراغ SDL_سیٹ_کھڑکی_HDRProperties(SDL_کھڑکی *کھڑکی, ثابت SDL_HDROutputProperties *HDR, bool send_event);
خارجي فراغ SDL_سیٹ_کھڑکی_محفوظ_Area_Insets(SDL_کھڑکی *کھڑکی, صحيح بایاں, صحيح دایاں, صحيح چوٹی, صحيح bottom);

خارجي فراغ SDL_GL_DeduceMaxSupportedESProfile(صحيح *major, صحيح *minor);

خارجي bool SDL_Recreate_کھڑکی(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags);
خارجي bool SDL_Reconfigure_کھڑکی(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags);
خارجي bool SDL_HasWindows(فراغ);
خارجي فراغ SDL_Relative_منزل_Global_For_کھڑکی(SDL_کھڑکی *کھڑکی, صحيح rel_x, صحيح rel_y, صحيح *abs_x, صحيح *abs_y);
خارجي فراغ SDL_Global_منزل_Relative_For_کھڑکی(SDL_کھڑکی *کھڑکی, صحيح abs_x, صحيح abs_y, صحيح *rel_x, صحيح *rel_y);
خارجي bool SDL_ShouldFocusPopup(SDL_کھڑکی *کھڑکی);
خارجي bool SDL_ShouldRelinquishPopupFocus(SDL_کھڑکی *کھڑکی, SDL_کھڑکی **new_focus);

خارجي فراغ SDL_OnDisplayAdded(SDL_VideoDisplay *display);
خارجي فراغ SDL_OnDisplayMoved(SDL_VideoDisplay *display);
خارجي فراغ SDL_On_کھڑکی_Shown(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_Hidden(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_Moved(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_Resized(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_Check_کھڑکی_Pixel_ناپ_بدلیا(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_Pixel_ناپ_بدلیا(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_جیوندا_Resize_Update(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_Minimized(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_Maximized(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_Restored(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_Enter(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_Leave(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_Focus_Gained(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_Focus_گواچا(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_On_کھڑکی_Display_بدلیا(SDL_کھڑکی *کھڑکی);
خارجي فراغ SDL_Update_کھڑکی_Grab(SDL_کھڑکی *کھڑکی);
خارجي bool SDL_Update_Fullscreen_منوال(SDL_کھڑکی *کھڑکی, SDL_FullscreenOp fullscreen, bool commit);
خارجي SDL_کھڑکی *SDL_GetToplevelForKeyboardFocus(فراغ);

خارجي bool SDL_ShouldAllowTopmost(فراغ);

خارجي فراغ SDL_ToggleDragAndDropSupport(فراغ);

خارجي فراغ SDL_UpdateDesktopBounds(فراغ);

خارجي SDL_متن_داخلہ_Type SDL_Get_متن_داخلہ_Type(SDL_PropertiesID props);
خارجي SDL_Capitalization SDL_Get_متن_داخلہ_Capitalization(SDL_PropertiesID props);
خارجي bool SDL_Get_متن_داخلہ_Autocorrect(SDL_PropertiesID props);
خارجي bool SDL_Get_متن_داخلہ_Multiline(SDL_PropertiesID props);

خارجي فراغ SDL_SendScreenKeyboardShown(فراغ);
خارجي فراغ SDL_SendScreenKeyboardHidden(فراغ);

#جے_انت // SDL_sysvideo_h_
