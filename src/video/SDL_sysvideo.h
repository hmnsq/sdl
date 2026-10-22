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

#ifndef SDL_sysvideo_h_
#define SDL_sysvideo_h_

#شامل <SDL3/SDL_vulkan.h>

#شامل "SDL_surface_c.h"

// The SDL video driver

تعریفنوع ساختار SDL_VideoDisplay SDL_VideoDisplay;
تعریفنوع ساختار SDL_VideoDevice SDL_VideoDevice;
تعریفنوع ساختار SDL_VideoData SDL_VideoData;
تعریفنوع ساختار SDL_DisplayData SDL_DisplayData;
تعریفنوع ساختار SDL_WindowData SDL_WindowData;

تعریفنوع ساختار
{
    اعشاری SDR_white_level;
    اعشاری HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
ساختار SDL_Window
{
    SDL_WindowID id;
    نویسه *title;
    SDL_Surface *icon;
    صحیح x, y;
    صحیح w, h;
    صحیح min_w, min_h;
    صحیح max_w, max_h;
    اعشاری min_aspect;
    اعشاری max_aspect;
    صحیح last_pixel_w, last_pixel_h;
    SDL_WindowFlags flags;
    SDL_WindowFlags pending_flags;
    اعشاری display_scale;
    bool external_graphics_context;
    bool fullscreen_exclusive;  // The window is currently fullscreen exclusive
    SDL_DisplayID last_fullscreen_exclusive_display;  // The last fullscreen_exclusive display
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

    SDL_DisplayMode requested_fullscreen_mode;
    SDL_DisplayMode current_fullscreen_mode;
    SDL_HDROutputProperties HDR;

    اعشاری opacity;

    SDL_Surface *surface;
    bool surface_valid;

    bool is_hiding;
    bool restore_on_show; // Child was hidden recursively by the parent, restore when shown.
    bool last_position_pending; // This should NOT be cleared by the backend, as it is used for fullscreen positioning.
    bool last_size_pending; // This should be cleared by the backend if the new size cannot be applied.
    bool update_fullscreen_on_display_changed;
    bool constrain_popup;
    bool is_destroying;
    bool is_dropping; // drag/drop in progress, expecting SDL_SendDropComplete().

    صحیح safe_inset_چپ;
    صحیح safe_inset_راست;
    صحیح safe_inset_بالاترین;
    صحیح safe_inset_bottom;
    SDL_Rect safe_rect;

    SDL_PropertiesID text_درون_داد_props;
    bool text_درون_داد_active;
    SDL_Rect text_درون_داد_rect;
    صحیح text_درون_داد_cursor;

    SDL_Rect mouse_rect;

    SDL_HitTest hit_test;
    تهی *hit_test_data;

    SDL_ProgressState progress_state;
    اعشاری progress_مقدار;

    SDL_PropertiesID props;

    صحیح رقم_renderers;
    SDL_Renderer **renderers;

    SDL_WindowData *internal;

    // If a toplevel window, holds the current keyboard focus for grabbing popups.
    SDL_Window *keyboard_focus;

    SDL_Window *prev;
    SDL_Window *next;

    SDL_Window *parent;
    SDL_Window *first_child;
    SDL_Window *prev_sibling;
    SDL_Window *next_sibling;
};
#define SDL_WINDOW_FULLSCREEN_VISIBLE(W)        \
    ((((W)->flags & SDL_WINDOW_FULLSCREEN) != 0) &&   \
     (((W)->flags & SDL_WINDOW_HIDDEN) == 0) && \
     (((W)->flags & SDL_WINDOW_MINIMIZED) == 0))

#define SDL_WINDOW_IS_POPUP(W) \
    (((W)->flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0)

/*
 * Define the SDL display structure.
 * This corresponds to physical monitors attached to the system.
 */
ساختار SDL_VideoDisplay
{
    SDL_DisplayID id;
    نویسه *name;
    صحیح max_fullscreen_modes;
    صحیح رقم_fullscreen_modes;
    SDL_DisplayMode *fullscreen_modes;
    SDL_DisplayMode desktop_mode;
    ثابت SDL_DisplayMode *current_mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    اعشاری content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_active;
    SDL_Window *fullscreen_window;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_DisplayData *internal;
};

// Video device flags
تعریفنوع شمارش
{
    VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED = 0x01,
    VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT = 0x02,
    VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS = 0x04,
    VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY = 0x08,
    VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES = 0x10,
    VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES = 0x20,
    VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER = 0x40
} DeviceCaps;

// Fullscreen operations
تعریفنوع شمارش
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

تعریفنوع شمارش
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_FullscreenResult;

ساختار SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    ثابت نویسه *name;

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
    تهی (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    تهی (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    تهی (*RefreshDisplays)(SDL_VideoDevice *_this);

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
    bool (*SetDisplayMode)(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);

    /* * * */
    /*
     * Window functions
     */
    bool (*CreateSDLWindow)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
    تهی (*SetWindowTitle)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowIcon)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
    bool (*SetWindowPosition)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*SetWindowSize)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*SetWindowMinimumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*SetWindowMaximumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*SetWindowAspectRatio)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GetWindowBordersSize)(SDL_VideoDevice *_this, SDL_Window *window, صحیح *بالاترین, صحیح *چپ, صحیح *bottom, صحیح *راست);
    اعشاری (*GetWindowContentScale)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*GetWindowSizeInPixels)(SDL_VideoDevice *_this, SDL_Window *window, صحیح *w, صحیح *h);
    bool (*SetWindowOpacity)(SDL_VideoDevice *_this, SDL_Window *window, اعشاری opacity);
    bool (*SetWindowParent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
    bool (*SetWindowModal)(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
    تهی (*ShowWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*HideWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*RaiseWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*MaximizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*MinimizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*RestoreWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*SetWindowBordered)(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
    تهی (*SetWindowResizable)(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
    تهی (*Set_Window_Always_On_بالاترین)(SDL_VideoDevice *_this, SDL_Window *window, bool on_بالاترین);
    SDL_FullscreenResult (*SetWindowFullscreen)(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    تهی *(*GetWindowICCProfile)(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
    SDL_DisplayID (*GetDisplayForWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseRect)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    bool (*SetWindowKeyboardGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    تهی (*DestroyWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*CreateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, تهی **pixels, صحیح *pitch);
    bool (*SetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, صحیح vsync);
    bool (*GetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, صحیح *vsync);
    bool (*UpdateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, ثابت SDL_Rect *rects, صحیح numrects);
    تهی (*DestroyWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*OnWindowEnter)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*UpdateWindowShape)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape);
    bool (*FlashWindow)(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
    bool (*ApplyWindowProgress)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowFocusable)(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
    bool (*SetWindowFillDocument)(SDL_VideoDevice *_this, SDL_Window *window, bool fill);
    bool (*SyncWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*ReconfigureWindow)(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

    /* * * */
    /*
     * OpenGL support
     */
    bool (*GL_LoadLibrary)(SDL_VideoDevice *_this, ثابت نویسه *path);
    SDL_FunctionPointer (*GL_GetProcAddress)(SDL_VideoDevice *_this, ثابت نویسه *proc);
    تهی (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_SetSwapInterval)(SDL_VideoDevice *_this, صحیح interval);
    bool (*GL_GetSwapInterval)(SDL_VideoDevice *_this, صحیح *interval);
    bool (*GL_SwapWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    تهی (*GL_SetDefaultProfileConfig)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_LoadLibrary)(SDL_VideoDevice *_this, ثابت نویسه *path);
    تهی (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    نویسه ثابت * ثابت *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *شمار);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_Window *window, VkInstance instance, ثابت ساختار VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
    تهی (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ثابت ساختار VkAllocationCallbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 queueFamilyIndex);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    تهی *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    صحیح (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    تهی (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*Start_Text_درون_داد)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    bool (*Stop_Text_درون_داد)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Update_Text_درون_داد_Area)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_Window *window);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    تهی (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    تهی (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window);
    تهی (*Set_Text_درون_داد_Properties)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);

    // Clipboard
    ثابت نویسه *ثابت *(*GetTextMimeTypes)(SDL_VideoDevice *_this, size_t *رقم_mime_types);
    bool (*SetClipboardData)(SDL_VideoDevice *_this);
    تهی *(*GetClipboardData)(SDL_VideoDevice *_this, ثابت نویسه *mime_type, size_t *size);
    bool (*HasClipboardData)(SDL_VideoDevice *_this, ثابت نویسه *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*SetClipboardText)(SDL_VideoDevice *_this, ثابت نویسه *text);
    نویسه *(*GetClipboardText)(SDL_VideoDevice *_this);
    bool (*HasClipboardText)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*SetPrimarySelectionText)(SDL_VideoDevice *_this, ثابت نویسه *text);
    نویسه *(*GetPrimarySelectionText)(SDL_VideoDevice *_this);
    bool (*HasPrimarySelectionText)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*ShowMessageBox)(SDL_VideoDevice *_this, ثابت SDL_MessageBoxData *messageboxdata, صحیح *buttonID);

    // Hit-testing
    bool (*SetWindowHitTest)(SDL_Window *window, bool enabled);

    // Tell window that app enabled drag'n'drop events
    تهی (*AcceptDragAndDrop)(SDL_Window *window, bool accept);

    // Display the system-level window menu
    تهی (*ShowWindowSystemMenu)(SDL_Window *window, صحیح x, صحیح y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    تهی *wakeup_window;
    صحیح رقم_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_Window *windows;
    SDL_Window *grabbed_window;
    Uint32 clipboard_sequence;
    SDL_ClipboardDataCallback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    تهی *clipboard_userdata;
    نویسه **clipboard_mime_types;
    size_t رقم_clipboard_mime_types;
    نویسه *primary_selection_text;
    bool setting_display_mode;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    ساختار
    {
        صحیح red_size;
        صحیح green_size;
        صحیح blue_size;
        صحیح alpha_size;
        صحیح depth_size;
        صحیح buffer_size;
        صحیح stencil_size;
        صحیح double_buffer;
        صحیح accum_red_size;
        صحیح accum_green_size;
        صحیح accum_blue_size;
        صحیح accum_alpha_size;
        صحیح stereo;
        صحیح multisamplebuffers;
        صحیح multisamplesamples;
        صحیح floatbuffers;
        صحیح accelerated;
        صحیح major_version;
        صحیح minor_version;
        صحیح flags;
        صحیح profile_mask;
        صحیح share_with_current_context;
        صحیح release_behavior;
        صحیح reset_notification;
        صحیح framebuffer_srgb_capable;
        صحیح no_error;
        صحیح retained_backing;
        صحیح egl_platform;
        صحیح driver_loaded;
        صحیح HAS_GL_ARB_color_buffer_float;
        نویسه driver_path[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    تهی *egl_attrib_callback_userdata;

    /* * * */
    // Cache current GL context; don't call the OS when it hasn't changed.
    /* We have the global pointers here so Cocoa continues to work the way
       it always has, and the thread-local storage for the general case.
     */
    SDL_Window *current_glwin;
    SDL_GLContext current_glctx;
    SDL_TLSID current_glwin_tls;
    SDL_TLSID current_glctx_tls;

    /* Flag that stores whether it's allowed to call SDL_GL_MakeCurrent()
     * with a NULL window, but a non-NULL context. (Not allowed in most cases,
     * except on EGL under some circumstances.) */
    bool gl_allow_no_surface;

    /* * * */
    // Data used by the Vulkan drivers
    ساختار
    {
        SDL_FunctionPointer vkGetInstanceProcAddr;
        SDL_FunctionPointer vkEnumerateInstanceExtensionProperties;
        صحیح loader_loaded;
        نویسه loader_path[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_VideoData *internal;
    ساختار SDL_GLDriverData *gl_data;

#ifdef SDL_VIDEO_OPENGL_EGL
    ساختار SDL_EGL_VideoData *egl_data;
#endif

#اگر defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    ساختار SDL_PrivateGLESData *gles_data;
#endif

    /* * * */
    // The function used to dispose of this structure
    تهی (*آزاد)(SDL_VideoDevice *_this);
};

تعریفنوع ساختار VideoBootStrap
{
    ثابت نویسه *name;
    ثابت نویسه *desc;
    SDL_VideoDevice *(*create)(تهی);
    bool (*ShowMessageBox)(ثابت SDL_MessageBoxData *messageboxdata, صحیح *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
بیرونی VideoBootStrap PRIVATE_bootstrap;
بیرونی VideoBootStrap COCOA_bootstrap;
بیرونی VideoBootStrap X11_bootstrap;
بیرونی VideoBootStrap WINDOWS_bootstrap;
بیرونی VideoBootStrap HAIKU_bootstrap;
بیرونی VideoBootStrap UIKIT_bootstrap;
بیرونی VideoBootStrap Android_bootstrap;
بیرونی VideoBootStrap OPENHARMONY_bootstrap;
بیرونی VideoBootStrap PS2_bootstrap;
بیرونی VideoBootStrap PSP_bootstrap;
بیرونی VideoBootStrap VITA_bootstrap;
بیرونی VideoBootStrap RISCOS_bootstrap;
بیرونی VideoBootStrap N3DS_bootstrap;
بیرونی VideoBootStrap NGAGE_bootstrap;
بیرونی VideoBootStrap RPI_bootstrap;
بیرونی VideoBootStrap KMSDRM_bootstrap;
بیرونی VideoBootStrap DUMMY_bootstrap;
بیرونی VideoBootStrap DUMMY_evdev_bootstrap;
بیرونی VideoBootStrap Wayland_preferred_bootstrap;
بیرونی VideoBootStrap Wayland_bootstrap;
بیرونی VideoBootStrap VIVANTE_bootstrap;
بیرونی VideoBootStrap Emscripten_bootstrap;
بیرونی VideoBootStrap OFFSCREEN_bootstrap;
بیرونی VideoBootStrap QNX_bootstrap;
بیرونی VideoBootStrap OPENVR_bootstrap;
بیرونی VideoBootStrap DOSVESA_bootstrap;

بیرونی bool SDL_UninitializedVideo(تهی);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
بیرونی bool SDL_OnVideoThread(تهی);
بیرونی SDL_VideoDevice *SDL_GetVideoDevice(تهی);
بیرونی تهی SDL_SetSystemTheme(SDL_SystemTheme theme);
بیرونی SDL_DisplayID SDL_AddBasicVideoDisplay(ثابت SDL_DisplayMode *desktop_mode);
بیرونی SDL_DisplayID SDL_AddVideoDisplay(ثابت SDL_VideoDisplay *display, bool send_event);
بیرونی تهی SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
بیرونی bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode);
بیرونی تهی SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
بیرونی تهی SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode);
بیرونی تهی SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode);
بیرونی تهی SDL_SetDisplayContentScale(SDL_VideoDisplay *display, اعشاری scale);
بیرونی تهی SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR);
بیرونی bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode);
بیرونی SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
بیرونی SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window);
بیرونی SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window);
بیرونی SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window);
بیرونی صحیح SDL_GetDisplayIndex(SDL_DisplayID displayID);
بیرونی SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID display);
بیرونی SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window);
بیرونی صحیح SDL_Get_Message_Box_شمار(تهی);
بیرونی تهی SDL_SetWindowHDRProperties(SDL_Window *window, ثابت SDL_HDROutputProperties *HDR, bool send_event);
بیرونی تهی SDL_SetWindowSafeAreaInsets(SDL_Window *window, صحیح چپ, صحیح راست, صحیح بالاترین, صحیح bottom);

بیرونی تهی SDL_GL_DeduceMaxSupportedESProfile(صحیح *major, صحیح *minor);

بیرونی bool SDL_RecreateWindow(SDL_Window *window, SDL_WindowFlags flags);
بیرونی bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags);
بیرونی bool SDL_HasWindows(تهی);
بیرونی تهی SDL_RelativeToGlobalForWindow(SDL_Window *window, صحیح rel_x, صحیح rel_y, صحیح *abs_x, صحیح *abs_y);
بیرونی تهی SDL_GlobalToRelativeForWindow(SDL_Window *window, صحیح abs_x, صحیح abs_y, صحیح *rel_x, صحیح *rel_y);
بیرونی bool SDL_ShouldFocusPopup(SDL_Window *window);
بیرونی bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus);

بیرونی تهی SDL_OnDisplayAdded(SDL_VideoDisplay *display);
بیرونی تهی SDL_OnDisplayMoved(SDL_VideoDisplay *display);
بیرونی تهی SDL_OnWindowShown(SDL_Window *window);
بیرونی تهی SDL_OnWindowHidden(SDL_Window *window);
بیرونی تهی SDL_OnWindowMoved(SDL_Window *window);
بیرونی تهی SDL_OnWindowResized(SDL_Window *window);
بیرونی تهی SDL_CheckWindowPixelSizeChanged(SDL_Window *window);
بیرونی تهی SDL_OnWindowPixelSizeChanged(SDL_Window *window);
بیرونی تهی SDL_OnWindowLiveResizeUpdate(SDL_Window *window);
بیرونی تهی SDL_OnWindowMinimized(SDL_Window *window);
بیرونی تهی SDL_OnWindowMaximized(SDL_Window *window);
بیرونی تهی SDL_OnWindowRestored(SDL_Window *window);
بیرونی تهی SDL_OnWindowEnter(SDL_Window *window);
بیرونی تهی SDL_OnWindowLeave(SDL_Window *window);
بیرونی تهی SDL_OnWindowFocusGained(SDL_Window *window);
بیرونی تهی SDL_OnWindowFocusLost(SDL_Window *window);
بیرونی تهی SDL_OnWindowDisplayChanged(SDL_Window *window);
بیرونی تهی SDL_UpdateWindowGrab(SDL_Window *window);
بیرونی bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit);
بیرونی SDL_Window *SDL_GetToplevelForKeyboardFocus(تهی);

بیرونی bool SDL_ShouldAllowTopmost(تهی);

بیرونی تهی SDL_ToggleDragAndDropSupport(تهی);

بیرونی تهی SDL_UpdateDesktopBounds(تهی);

بیرونی SDL_Text_درون_داد_Type SDL_Get_Text_درون_داد_Type(SDL_PropertiesID props);
بیرونی SDL_Capitalization SDL_Get_Text_درون_داد_Capitalization(SDL_PropertiesID props);
بیرونی bool SDL_Get_Text_درون_داد_Autocorrect(SDL_PropertiesID props);
بیرونی bool SDL_Get_Text_درون_داد_Multiline(SDL_PropertiesID props);

بیرونی تهی SDL_SendScreenKeyboardShown(تهی);
بیرونی تهی SDL_SendScreenKeyboardHidden(تهی);

#endif // SDL_sysvideo_h_
