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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_sysvideo_h_
#تعریف_کرو SDL_sysvideo_h_

#شامل <SDL3/SDL_vulkan.h>

#شامل "SDL_surface_c.h"

// The SDL video driver

قسمتعریف ساخت SDL_VideoDisplay SDL_VideoDisplay;
قسمتعریف ساخت SDL_VideoDevice SDL_VideoDevice;
قسمتعریف ساخت SDL_Video_ڈیٹا SDL_Video_ڈیٹا;
قسمتعریف ساخت SDL_Display_ڈیٹا SDL_Display_ڈیٹا;
قسمتعریف ساخت SDL_کھڑکی_ڈیٹا SDL_کھڑکی_ڈیٹا;

قسمتعریف ساخت
{
    اعشاری SDR_white_level;
    اعشاری HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
ساخت SDL_کھڑکی
{
    SDL_کھڑکی_ID id;
    حرف *title;
    SDL_Surface *icon;
    صحیح x, y;
    صحیح w, h;
    صحیح min_w, min_h;
    صحیح max_w, max_h;
    اعشاری min_aspect;
    اعشاری max_aspect;
    صحیح آخری_pixel_w, آخری_pixel_h;
    SDL_کھڑکی_Flags flags;
    SDL_کھڑکی_Flags pending_flags;
    اعشاری display_scale;
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

    اعشاری opacity;

    SDL_Surface *surface;
    bool surface_valid;

    bool is_hiding;
    bool restore_on_show; // Child was hidden recursively by the parent, restore when shown.
    bool آخری_position_pending; // This should NOT be cleared by the backend, as it is used for fullscreen positioning.
    bool آخری_سائز_pending; // This should be cleared by the backend if the new size cannot be applied.
    bool update_fullscreen_on_display_بدلا;
    bool constrain_popup;
    bool is_destroying;
    bool is_dropping; // drag/drop in progress, expecting SDL_SendDropComplete().

    صحیح محفوظ_inset_بایاں;
    صحیح محفوظ_inset_دایاں;
    صحیح محفوظ_inset_چوٹی;
    صحیح محفوظ_inset_bottom;
    SDL_Rect محفوظ_rect;

    SDL_PropertiesID متن_داخلہ_props;
    bool متن_داخلہ_فعال;
    SDL_Rect متن_داخلہ_rect;
    صحیح متن_داخلہ_cursor;

    SDL_Rect mouse_rect;

    SDL_کامیابی_Test کامیابی_test;
    خالی *کامیابی_test_ڈیٹا;

    SDL_پیش_رفت_State پیش_رفت_state;
    اعشاری پیش_رفت_قدر;

    SDL_PropertiesID props;

    صحیح عدد_renderers;
    SDL_Renderer **renderers;

    SDL_کھڑکی_ڈیٹا *اندرونی_2;

    // If a toplevel window, holds the current keyboard focus for grabbing popups.
    SDL_کھڑکی *keyboard_focus;

    SDL_کھڑکی *پچھلا;
    SDL_کھڑکی *اگلا;

    SDL_کھڑکی *والد;
    SDL_کھڑکی *پہلا_بچہ;
    SDL_کھڑکی *پچھلا_sibling;
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
ساخت SDL_VideoDisplay
{
    SDL_DisplayID id;
    حرف *name;
    صحیح max_fullscreen_modes;
    صحیح عدد_fullscreen_modes;
    SDL_Display_منوال *fullscreen_modes;
    SDL_Display_منوال desktop_منوال;
    ثابت SDL_Display_منوال *current_منوال;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    اعشاری content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_فعال;
    SDL_کھڑکی *fullscreen_کھڑکی;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_Display_ڈیٹا *اندرونی_2;
};

// Video device flags
قسمتعریف شمار
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
قسمتعریف شمار
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

قسمتعریف شمار
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_Fullscreen_نتیجہ;

ساخت SDL_VideoDevice
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
    خالی (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    خالی (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    خالی (*RefreshDisplays)(SDL_VideoDevice *_this);

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
    خالی (*سیٹ_کھڑکی_Title)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*سیٹ_کھڑکی_Icon)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon);
    bool (*سیٹ_کھڑکی_Position)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*سیٹ_کھڑکی_سائز)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*سیٹ_کھڑکی_Minimum_سائز)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*سیٹ_کھڑکی_Aspect_تناسب)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*Get_کھڑکی_Borders_سائز)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *چوٹی, صحیح *بایاں, صحیح *bottom, صحیح *دایاں);
    اعشاری (*Get_کھڑکی_Content_Scale)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*Get_کھڑکی_سائز_اندر_Pixels)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *w, صحیح *h);
    bool (*سیٹ_کھڑکی_Opacity)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, اعشاری opacity);
    bool (*سیٹ_کھڑکی_والد)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *والد);
    bool (*سیٹ_کھڑکی_Modal)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal);
    خالی (*Show_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*Hide_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*Raise_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*Maximize_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*Minimize_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*Restore_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*سیٹ_کھڑکی_Bordered)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered);
    خالی (*سیٹ_کھڑکی_Resizable)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable);
    خالی (*سیٹ_کھڑکی_Always_On_چوٹی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool on_چوٹی);
    SDL_Fullscreen_نتیجہ (*سیٹ_کھڑکی_Fullscreen)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    خالی *(*Get_کھڑکی_ICCProfile)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *سائز);
    SDL_DisplayID (*Get_Display_For_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*سیٹ_کھڑکی_Mouse_Rect)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*سیٹ_کھڑکی_Mouse_Grab)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
    bool (*سیٹ_کھڑکی_Keyboard_Grab)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
    خالی (*Destroy_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*Create_کھڑکی_Framebuffer)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, خالی **pixels, صحیح *pitch);
    bool (*سیٹ_کھڑکی_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح vsync);
    bool (*Get_کھڑکی_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *vsync);
    bool (*Update_کھڑکی_Framebuffer)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحیح numrects);
    خالی (*Destroy_کھڑکی_Framebuffer)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*On_کھڑکی_Enter)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*Update_کھڑکی_Shape)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *shape);
    bool (*Flash_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation);
    bool (*Apply_کھڑکی_پیش_رفت)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*سیٹ_کھڑکی_Focusable)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable);
    bool (*سیٹ_کھڑکی_Fill_Document)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool fill);
    bool (*Sync_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*Reconfigure_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags);

    /* * * */
    /*
     * OpenGL support
     */
    bool (*GL_بھرو_Library)(SDL_VideoDevice *_this, ثابت حرف *راستہ);
    SDL_Function_اشارہ_گر (*GL_Get_Proc_پتہ)(SDL_VideoDevice *_this, ثابت حرف *proc);
    خالی (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*GL_سیٹ_تبادلہ_Interval)(SDL_VideoDevice *_this, صحیح interval);
    bool (*GL_Get_تبادلہ_Interval)(SDL_VideoDevice *_this, صحیح *interval);
    bool (*GL_تبادلہ_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    خالی (*GL_سیٹ_Default_Profile_Config)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_بھرو_Library)(SDL_VideoDevice *_this, ثابت حرف *راستہ);
    خالی (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    حرف ثابت * ثابت *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *گنتی);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, VkInstance instance, ثابت ساخت Vk_تخصیص_Callbacks *allocator, VkSurfaceKHR *surface);
    خالی (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ثابت ساخت Vk_تخصیص_Callbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 قطار_Family_اشاریہ);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    خالی *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    صحیح (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    خالی (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*آغاز_متن_داخلہ)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);
    bool (*Stop_متن_داخلہ)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*Update_متن_داخلہ_Area)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    خالی (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);
    خالی (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
    خالی (*سیٹ_متن_داخلہ_Properties)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props);

    // Clipboard
    ثابت حرف *ثابت *(*Get_متن_Mime_Types)(SDL_VideoDevice *_this, size_t *عدد_mime_types);
    bool (*سیٹ_Clipboard_ڈیٹا)(SDL_VideoDevice *_this);
    خالی *(*Get_Clipboard_ڈیٹا)(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *سائز);
    bool (*Has_Clipboard_ڈیٹا)(SDL_VideoDevice *_this, ثابت حرف *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*سیٹ_Clipboard_متن)(SDL_VideoDevice *_this, ثابت حرف *متن);
    حرف *(*Get_Clipboard_متن)(SDL_VideoDevice *_this);
    bool (*Has_Clipboard_متن)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*سیٹ_Primary_Selection_متن)(SDL_VideoDevice *_this, ثابت حرف *متن);
    حرف *(*Get_Primary_Selection_متن)(SDL_VideoDevice *_this);
    bool (*Has_Primary_Selection_متن)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*Show_پیغام_Box)(SDL_VideoDevice *_this, ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonID);

    // Hit-testing
    bool (*سیٹ_کھڑکی_کامیابی_Test)(SDL_کھڑکی *کھڑکی, bool enabled);

    // Tell window that app enabled drag'n'drop events
    خالی (*AcceptDragAndDrop)(SDL_کھڑکی *کھڑکی, bool accept);

    // Display the system-level window menu
    خالی (*Show_کھڑکی_System_Menu)(SDL_کھڑکی *کھڑکی, صحیح x, صحیح y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    خالی *wakeup_کھڑکی;
    صحیح عدد_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_کھڑکی *windows;
    SDL_کھڑکی *grabbed_کھڑکی;
    Uint32 clipboard_sequence;
    SDL_Clipboard_ڈیٹا_Callback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    خالی *clipboard_userdata;
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
    ساخت
    {
        صحیح red_سائز;
        صحیح green_سائز;
        صحیح blue_سائز;
        صحیح alpha_سائز;
        صحیح گہرائی_سائز;
        صحیح بفر_سائز;
        صحیح stencil_سائز;
        صحیح double_بفر;
        صحیح accum_red_سائز;
        صحیح accum_green_سائز;
        صحیح accum_blue_سائز;
        صحیح accum_alpha_سائز;
        صحیح stereo;
        صحیح multisamplebuffers;
        صحیح multisamplesamples;
        صحیح floatbuffers;
        صحیح accelerated;
        صحیح major_نسخہ;
        صحیح minor_نسخہ;
        صحیح flags;
        صحیح profile_نقاب;
        صحیح share_with_current_context;
        صحیح release_behavior;
        صحیح reset_notification;
        صحیح framebuffer_srgb_capable;
        صحیح no_error;
        صحیح retained_backing;
        صحیح egl_platform;
        صحیح driver_loaded;
        صحیح HAS_GL_ARB_color_بفر_float;
        حرف driver_راستہ[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    خالی *egl_attrib_callback_userdata;

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
    ساخت
    {
        SDL_Function_اشارہ_گر vkGetInstanceProcAddr;
        SDL_Function_اشارہ_گر vkEnumerateInstanceExtensionProperties;
        صحیح loader_loaded;
        حرف loader_راستہ[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_Video_ڈیٹا *اندرونی_2;
    ساخت SDL_GLDriver_ڈیٹا *gl_ڈیٹا;

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    ساخت SDL_EGL_Video_ڈیٹا *egl_ڈیٹا;
#اگر_ختم

#اگر defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    ساخت SDL_نجی_GLESData *gles_ڈیٹا;
#اگر_ختم

    /* * * */
    // The function used to dispose of this structure
    خالی (*آزاد)(SDL_VideoDevice *_this);
};

قسمتعریف ساخت VideoBootStrap
{
    ثابت حرف *name;
    ثابت حرف *desc;
    SDL_VideoDevice *(*create)(خالی);
    bool (*Show_پیغام_Box)(ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
خارجی VideoBootStrap نجی_bootstrap;
خارجی VideoBootStrap COCOA_bootstrap;
خارجی VideoBootStrap X11_bootstrap;
خارجی VideoBootStrap WINDOWS_bootstrap;
خارجی VideoBootStrap HAIKU_bootstrap;
خارجی VideoBootStrap UIKIT_bootstrap;
خارجی VideoBootStrap Android_bootstrap;
خارجی VideoBootStrap OPENHARMONY_bootstrap;
خارجی VideoBootStrap PS2_bootstrap;
خارجی VideoBootStrap PSP_bootstrap;
خارجی VideoBootStrap VITA_bootstrap;
خارجی VideoBootStrap RISCOS_bootstrap;
خارجی VideoBootStrap N3DS_bootstrap;
خارجی VideoBootStrap NGAGE_bootstrap;
خارجی VideoBootStrap RPI_bootstrap;
خارجی VideoBootStrap KMSDRM_bootstrap;
خارجی VideoBootStrap DUMMY_bootstrap;
خارجی VideoBootStrap DUMMY_evdev_bootstrap;
خارجی VideoBootStrap Wayland_preferred_bootstrap;
خارجی VideoBootStrap Wayland_bootstrap;
خارجی VideoBootStrap VIVANTE_bootstrap;
خارجی VideoBootStrap Emscripten_bootstrap;
خارجی VideoBootStrap OFFSCREEN_bootstrap;
خارجی VideoBootStrap QNX_bootstrap;
خارجی VideoBootStrap OPENVR_bootstrap;
خارجی VideoBootStrap DOSVESA_bootstrap;

خارجی bool SDL_UninitializedVideo(خالی);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
خارجی bool SDL_OnVideoThread(خالی);
خارجی SDL_VideoDevice *SDL_GetVideoDevice(خالی);
خارجی خالی SDL_سیٹ_System_Theme(SDL_SystemTheme theme);
خارجی SDL_DisplayID SDL_جوڑو_Basic_Video_Display(ثابت SDL_Display_منوال *desktop_منوال);
خارجی SDL_DisplayID SDL_جوڑو_Video_Display(ثابت SDL_VideoDisplay *display, bool send_event);
خارجی خالی SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
خارجی bool SDL_جوڑو_Fullscreen_Display_منوال(SDL_VideoDisplay *display, ثابت SDL_Display_منوال *منوال);
خارجی خالی SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
خارجی خالی SDL_سیٹ_Desktop_Display_منوال(SDL_VideoDisplay *display, ثابت SDL_Display_منوال *منوال);
خارجی خالی SDL_سیٹ_Current_Display_منوال(SDL_VideoDisplay *display, ثابت SDL_Display_منوال *منوال);
خارجی خالی SDL_سیٹ_Display_Content_Scale(SDL_VideoDisplay *display, اعشاری scale);
خارجی خالی SDL_سیٹ_Display_HDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR);
خارجی bool SDL_سیٹ_Display_منوال_For_Display(SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
خارجی SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
خارجی SDL_DisplayID SDL_Get_Display_For_کھڑکی_Position(SDL_کھڑکی *کھڑکی);
خارجی SDL_VideoDisplay *SDL_Get_Video_Display_For_کھڑکی(SDL_کھڑکی *کھڑکی);
خارجی SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_کھڑکی(SDL_کھڑکی *کھڑکی);
خارجی صحیح SDL_Get_Display_اشاریہ(SDL_DisplayID displayID);
خارجی SDL_Display_ڈیٹا *SDL_Get_Display_Driver_ڈیٹا(SDL_DisplayID display);
خارجی SDL_Display_ڈیٹا *SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(SDL_کھڑکی *کھڑکی);
خارجی صحیح SDL_Get_پیغام_Box_گنتی(خالی);
خارجی خالی SDL_سیٹ_کھڑکی_HDRProperties(SDL_کھڑکی *کھڑکی, ثابت SDL_HDROutputProperties *HDR, bool send_event);
خارجی خالی SDL_سیٹ_کھڑکی_محفوظ_Area_Insets(SDL_کھڑکی *کھڑکی, صحیح بایاں, صحیح دایاں, صحیح چوٹی, صحیح bottom);

خارجی خالی SDL_GL_DeduceMaxSupportedESProfile(صحیح *major, صحیح *minor);

خارجی bool SDL_Recreate_کھڑکی(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags);
خارجی bool SDL_Reconfigure_کھڑکی(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags);
خارجی bool SDL_HasWindows(خالی);
خارجی خالی SDL_Relative_مقصد_Global_For_کھڑکی(SDL_کھڑکی *کھڑکی, صحیح rel_x, صحیح rel_y, صحیح *abs_x, صحیح *abs_y);
خارجی خالی SDL_Global_مقصد_Relative_For_کھڑکی(SDL_کھڑکی *کھڑکی, صحیح abs_x, صحیح abs_y, صحیح *rel_x, صحیح *rel_y);
خارجی bool SDL_ShouldFocusPopup(SDL_کھڑکی *کھڑکی);
خارجی bool SDL_ShouldRelinquishPopupFocus(SDL_کھڑکی *کھڑکی, SDL_کھڑکی **new_focus);

خارجی خالی SDL_OnDisplayAdded(SDL_VideoDisplay *display);
خارجی خالی SDL_OnDisplayMoved(SDL_VideoDisplay *display);
خارجی خالی SDL_On_کھڑکی_Shown(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_Hidden(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_Moved(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_Resized(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_Check_کھڑکی_Pixel_سائز_بدلا(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_Pixel_سائز_بدلا(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_زندہ_Resize_Update(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_Minimized(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_Maximized(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_Restored(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_Enter(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_Leave(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_Focus_Gained(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_Focus_گمشدہ(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_On_کھڑکی_Display_بدلا(SDL_کھڑکی *کھڑکی);
خارجی خالی SDL_Update_کھڑکی_Grab(SDL_کھڑکی *کھڑکی);
خارجی bool SDL_Update_Fullscreen_منوال(SDL_کھڑکی *کھڑکی, SDL_FullscreenOp fullscreen, bool commit);
خارجی SDL_کھڑکی *SDL_GetToplevelForKeyboardFocus(خالی);

خارجی bool SDL_ShouldAllowTopmost(خالی);

خارجی خالی SDL_ToggleDragAndDropSupport(خالی);

خارجی خالی SDL_UpdateDesktopBounds(خالی);

خارجی SDL_متن_داخلہ_Type SDL_Get_متن_داخلہ_Type(SDL_PropertiesID props);
خارجی SDL_Capitalization SDL_Get_متن_داخلہ_Capitalization(SDL_PropertiesID props);
خارجی bool SDL_Get_متن_داخلہ_Autocorrect(SDL_PropertiesID props);
خارجی bool SDL_Get_متن_داخلہ_Multiline(SDL_PropertiesID props);

خارجی خالی SDL_SendScreenKeyboardShown(خالی);
خارجی خالی SDL_SendScreenKeyboardHidden(خالی);

#اگر_ختم // SDL_sysvideo_h_
