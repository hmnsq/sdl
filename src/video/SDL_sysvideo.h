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

#ifndef SDL_sysvideo_h_
#define SDL_sysvideo_h_

#ضمن <SDL3/SDL_vulkan.h>

#ضمن "SDL_surface_c.h"

// The SDL video driver

تعريفنوع بنية SDL_VideoDisplay SDL_VideoDisplay;
تعريفنوع بنية SDL_VideoDevice SDL_VideoDevice;
تعريفنوع بنية SDL_VideoData SDL_VideoData;
تعريفنوع بنية SDL_DisplayData SDL_DisplayData;
تعريفنوع بنية SDL_WindowData SDL_WindowData;

تعريفنوع بنية
{
    عائم SDR_white_level;
    عائم HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
بنية SDL_Window
{
    SDL_WindowID id;
    حرف *title;
    SDL_Surface *icon;
    صحيح x, y;
    صحيح w, h;
    صحيح min_w, min_h;
    صحيح max_w, max_h;
    عائم min_aspect;
    عائم max_aspect;
    صحيح last_pixel_w, last_pixel_h;
    SDL_WindowFlags flags;
    SDL_WindowFlags pending_flags;
    عائم display_scale;
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

    عائم opacity;

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

    صحيح safe_inset_کيري;
    صحيح safe_inset_کانن;
    صحيح safe_inset_اتس;
    صحيح safe_inset_bottom;
    SDL_Rect safe_rect;

    SDL_PropertiesID text_ماسوقن_props;
    bool text_ماسوقن_active;
    SDL_Rect text_ماسوقن_rect;
    صحيح text_ماسوقن_cursor;

    SDL_Rect mouse_rect;

    SDL_HitTest hit_test;
    فراغ *hit_test_data;

    SDL_ProgressState progress_state;
    عائم progress_نيلاي;

    SDL_PropertiesID props;

    صحيح اڠک_renderers;
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
بنية SDL_VideoDisplay
{
    SDL_DisplayID id;
    حرف *name;
    صحيح max_fullscreen_modes;
    صحيح اڠک_fullscreen_modes;
    SDL_DisplayMode *fullscreen_modes;
    SDL_DisplayMode desktop_mode;
    ثابت SDL_DisplayMode *current_mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    عائم content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_active;
    SDL_Window *fullscreen_window;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_DisplayData *internal;
};

// Video device flags
تعريفنوع تعداد
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
} SDL_FullscreenResult;

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
    bool (*SetDisplayMode)(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);

    /* * * */
    /*
     * Window functions
     */
    bool (*CreateSDLWindow)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
    فراغ (*SetWindowTitle)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowIcon)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
    bool (*SetWindowPosition)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*SetWindowSize)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*SetWindowMinimumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*SetWindowMaximumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*SetWindowAspectRatio)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GetWindowBordersSize)(SDL_VideoDevice *_this, SDL_Window *window, صحيح *اتس, صحيح *کيري, صحيح *bottom, صحيح *کانن);
    عائم (*GetWindowContentScale)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*GetWindowSizeInPixels)(SDL_VideoDevice *_this, SDL_Window *window, صحيح *w, صحيح *h);
    bool (*SetWindowOpacity)(SDL_VideoDevice *_this, SDL_Window *window, عائم opacity);
    bool (*SetWindowParent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
    bool (*SetWindowModal)(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
    فراغ (*ShowWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*HideWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*RaiseWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*MaximizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*MinimizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*RestoreWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*SetWindowBordered)(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
    فراغ (*SetWindowResizable)(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
    فراغ (*Set_Window_Always_On_اتس)(SDL_VideoDevice *_this, SDL_Window *window, bool on_اتس);
    SDL_FullscreenResult (*SetWindowFullscreen)(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    فراغ *(*GetWindowICCProfile)(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
    SDL_DisplayID (*GetDisplayForWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseRect)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    bool (*SetWindowKeyboardGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    فراغ (*DestroyWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*CreateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch);
    bool (*SetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, صحيح vsync);
    bool (*GetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, صحيح *vsync);
    bool (*UpdateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, ثابت SDL_Rect *rects, صحيح numrects);
    فراغ (*DestroyWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*OnWindowEnter)(SDL_VideoDevice *_this, SDL_Window *window);
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
    bool (*GL_LoadLibrary)(SDL_VideoDevice *_this, ثابت حرف *path);
    SDL_FunctionPointer (*GL_GetProcAddress)(SDL_VideoDevice *_this, ثابت حرف *proc);
    فراغ (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_SetSwapInterval)(SDL_VideoDevice *_this, صحيح interval);
    bool (*GL_GetSwapInterval)(SDL_VideoDevice *_this, صحيح *interval);
    bool (*GL_SwapWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    فراغ (*GL_SetDefaultProfileConfig)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_LoadLibrary)(SDL_VideoDevice *_this, ثابت حرف *path);
    فراغ (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    حرف ثابت * ثابت *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *کيراءن);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_Window *window, VkInstance instance, ثابت بنية VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
    فراغ (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ثابت بنية VkAllocationCallbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 queueFamilyIndex);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    فراغ *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    صحيح (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    فراغ (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*Start_Text_ماسوقن)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    bool (*Stop_Text_ماسوقن)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Update_Text_ماسوقن_Area)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_Window *window);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    فراغ (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    فراغ (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window);
    فراغ (*Set_Text_ماسوقن_Properties)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);

    // Clipboard
    ثابت حرف *ثابت *(*GetTextMimeTypes)(SDL_VideoDevice *_this, size_t *اڠک_mime_types);
    bool (*SetClipboardData)(SDL_VideoDevice *_this);
    فراغ *(*GetClipboardData)(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *size);
    bool (*HasClipboardData)(SDL_VideoDevice *_this, ثابت حرف *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*SetClipboardText)(SDL_VideoDevice *_this, ثابت حرف *text);
    حرف *(*GetClipboardText)(SDL_VideoDevice *_this);
    bool (*HasClipboardText)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*SetPrimarySelectionText)(SDL_VideoDevice *_this, ثابت حرف *text);
    حرف *(*GetPrimarySelectionText)(SDL_VideoDevice *_this);
    bool (*HasPrimarySelectionText)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*ShowMessageBox)(SDL_VideoDevice *_this, ثابت SDL_MessageBoxData *messageboxdata, صحيح *buttonID);

    // Hit-testing
    bool (*SetWindowHitTest)(SDL_Window *window, bool enabled);

    // Tell window that app enabled drag'n'drop events
    فراغ (*AcceptDragAndDrop)(SDL_Window *window, bool accept);

    // Display the system-level window menu
    فراغ (*ShowWindowSystemMenu)(SDL_Window *window, صحيح x, صحيح y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    فراغ *wakeup_window;
    صحيح اڠک_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_Window *windows;
    SDL_Window *grabbed_window;
    Uint32 clipboard_sequence;
    SDL_ClipboardDataCallback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    فراغ *clipboard_userdata;
    حرف **clipboard_mime_types;
    size_t اڠک_clipboard_mime_types;
    حرف *primary_selection_text;
    bool setting_display_mode;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    بنية
    {
        صحيح red_size;
        صحيح green_size;
        صحيح blue_size;
        صحيح alpha_size;
        صحيح depth_size;
        صحيح buffer_size;
        صحيح stencil_size;
        صحيح double_buffer;
        صحيح accum_red_size;
        صحيح accum_green_size;
        صحيح accum_blue_size;
        صحيح accum_alpha_size;
        صحيح stereo;
        صحيح multisamplebuffers;
        صحيح multisamplesamples;
        صحيح floatbuffers;
        صحيح accelerated;
        صحيح major_version;
        صحيح minor_version;
        صحيح flags;
        صحيح profile_mask;
        صحيح share_with_current_context;
        صحيح release_behavior;
        صحيح reset_notification;
        صحيح framebuffer_srgb_capable;
        صحيح no_error;
        صحيح retained_backing;
        صحيح egl_platform;
        صحيح driver_loaded;
        صحيح HAS_GL_ARB_color_buffer_float;
        حرف driver_path[256];
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
    بنية
    {
        SDL_FunctionPointer vkGetInstanceProcAddr;
        SDL_FunctionPointer vkEnumerateInstanceExtensionProperties;
        صحيح loader_loaded;
        حرف loader_path[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_VideoData *internal;
    بنية SDL_GLDriverData *gl_data;

#ifdef SDL_VIDEO_OPENGL_EGL
    بنية SDL_EGL_VideoData *egl_data;
#endif

#إذا defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    بنية SDL_PrivateGLESData *gles_data;
#endif

    /* * * */
    // The function used to dispose of this structure
    فراغ (*حرر)(SDL_VideoDevice *_this);
};

تعريفنوع بنية VideoBootStrap
{
    ثابت حرف *name;
    ثابت حرف *desc;
    SDL_VideoDevice *(*create)(فراغ);
    bool (*ShowMessageBox)(ثابت SDL_MessageBoxData *messageboxdata, صحيح *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
خارجي VideoBootStrap PRIVATE_bootstrap;
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
خارجي فراغ SDL_SetSystemTheme(SDL_SystemTheme theme);
خارجي SDL_DisplayID SDL_AddBasicVideoDisplay(ثابت SDL_DisplayMode *desktop_mode);
خارجي SDL_DisplayID SDL_AddVideoDisplay(ثابت SDL_VideoDisplay *display, bool send_event);
خارجي فراغ SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
خارجي bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode);
خارجي فراغ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
خارجي فراغ SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode);
خارجي فراغ SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode);
خارجي فراغ SDL_SetDisplayContentScale(SDL_VideoDisplay *display, عائم scale);
خارجي فراغ SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR);
خارجي bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode);
خارجي SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
خارجي SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window);
خارجي SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window);
خارجي SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window);
خارجي صحيح SDL_GetDisplayIndex(SDL_DisplayID displayID);
خارجي SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID display);
خارجي SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window);
خارجي صحيح SDL_Get_Message_Box_کيراءن(فراغ);
خارجي فراغ SDL_SetWindowHDRProperties(SDL_Window *window, ثابت SDL_HDROutputProperties *HDR, bool send_event);
خارجي فراغ SDL_SetWindowSafeAreaInsets(SDL_Window *window, صحيح کيري, صحيح کانن, صحيح اتس, صحيح bottom);

خارجي فراغ SDL_GL_DeduceMaxSupportedESProfile(صحيح *major, صحيح *minor);

خارجي bool SDL_RecreateWindow(SDL_Window *window, SDL_WindowFlags flags);
خارجي bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags);
خارجي bool SDL_HasWindows(فراغ);
خارجي فراغ SDL_RelativeToGlobalForWindow(SDL_Window *window, صحيح rel_x, صحيح rel_y, صحيح *abs_x, صحيح *abs_y);
خارجي فراغ SDL_GlobalToRelativeForWindow(SDL_Window *window, صحيح abs_x, صحيح abs_y, صحيح *rel_x, صحيح *rel_y);
خارجي bool SDL_ShouldFocusPopup(SDL_Window *window);
خارجي bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus);

خارجي فراغ SDL_OnDisplayAdded(SDL_VideoDisplay *display);
خارجي فراغ SDL_OnDisplayMoved(SDL_VideoDisplay *display);
خارجي فراغ SDL_OnWindowShown(SDL_Window *window);
خارجي فراغ SDL_OnWindowHidden(SDL_Window *window);
خارجي فراغ SDL_OnWindowMoved(SDL_Window *window);
خارجي فراغ SDL_OnWindowResized(SDL_Window *window);
خارجي فراغ SDL_CheckWindowPixelSizeChanged(SDL_Window *window);
خارجي فراغ SDL_OnWindowPixelSizeChanged(SDL_Window *window);
خارجي فراغ SDL_OnWindowLiveResizeUpdate(SDL_Window *window);
خارجي فراغ SDL_OnWindowMinimized(SDL_Window *window);
خارجي فراغ SDL_OnWindowMaximized(SDL_Window *window);
خارجي فراغ SDL_OnWindowRestored(SDL_Window *window);
خارجي فراغ SDL_OnWindowEnter(SDL_Window *window);
خارجي فراغ SDL_OnWindowLeave(SDL_Window *window);
خارجي فراغ SDL_OnWindowFocusGained(SDL_Window *window);
خارجي فراغ SDL_OnWindowFocusLost(SDL_Window *window);
خارجي فراغ SDL_OnWindowDisplayChanged(SDL_Window *window);
خارجي فراغ SDL_UpdateWindowGrab(SDL_Window *window);
خارجي bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit);
خارجي SDL_Window *SDL_GetToplevelForKeyboardFocus(فراغ);

خارجي bool SDL_ShouldAllowTopmost(فراغ);

خارجي فراغ SDL_ToggleDragAndDropSupport(فراغ);

خارجي فراغ SDL_UpdateDesktopBounds(فراغ);

خارجي SDL_Text_ماسوقن_Type SDL_Get_Text_ماسوقن_Type(SDL_PropertiesID props);
خارجي SDL_Capitalization SDL_Get_Text_ماسوقن_Capitalization(SDL_PropertiesID props);
خارجي bool SDL_Get_Text_ماسوقن_Autocorrect(SDL_PropertiesID props);
خارجي bool SDL_Get_Text_ماسوقن_Multiline(SDL_PropertiesID props);

خارجي فراغ SDL_SendScreenKeyboardShown(فراغ);
خارجي فراغ SDL_SendScreenKeyboardHidden(فراغ);

#endif // SDL_sysvideo_h_
