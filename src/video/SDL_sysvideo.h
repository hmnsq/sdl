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
#অন্তর্ভাৱ "SDL_internal.h"

#ifndef SDL_sysvideo_h_
#define SDL_sysvideo_h_

#অন্তর্ভাৱ <SDL3/SDL_vulkan.h>

#অন্তর্ভাৱ "SDL_surface_c.h"

// The SDL video driver

প্রকারনির্দেশ সংরচনা SDL_VideoDisplay SDL_VideoDisplay;
প্রকারনির্দেশ সংরচনা SDL_VideoDevice SDL_VideoDevice;
প্রকারনির্দেশ সংরচনা SDL_VideoData SDL_VideoData;
প্রকারনির্দেশ সংরচনা SDL_DisplayData SDL_DisplayData;
প্রকারনির্দেশ সংরচনা SDL_WindowData SDL_WindowData;

প্রকারনির্দেশ সংরচনা
{
    ভিন্ন SDR_white_level;
    ভিন্ন HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
সংরচনা SDL_Window
{
    SDL_WindowID id;
    ৱর্ণ *title;
    SDL_Surface *icon;
    পূর্ণাঙ্ক x, y;
    পূর্ণাঙ্ক w, h;
    পূর্ণাঙ্ক min_w, min_h;
    পূর্ণাঙ্ক max_w, max_h;
    ভিন্ন min_aspect;
    ভিন্ন max_aspect;
    পূর্ণাঙ্ক last_pixel_w, last_pixel_h;
    SDL_WindowFlags flags;
    SDL_WindowFlags pending_flags;
    ভিন্ন display_scale;
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

    ভিন্ন opacity;

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

    পূর্ণাঙ্ক safe_inset_বাম;
    পূর্ণাঙ্ক safe_inset_ডান;
    পূর্ণাঙ্ক safe_inset_শীৰ্ষ;
    পূর্ণাঙ্ক safe_inset_bottom;
    SDL_Rect safe_rect;

    SDL_PropertiesID text_প্ৰবেশ_props;
    bool text_প্ৰবেশ_active;
    SDL_Rect text_প্ৰবেশ_rect;
    পূর্ণাঙ্ক text_প্ৰবেশ_cursor;

    SDL_Rect mouse_rect;

    SDL_HitTest hit_test;
    শূন্য *hit_test_data;

    SDL_ProgressState progress_state;
    ভিন্ন progress_মান;

    SDL_PropertiesID props;

    পূর্ণাঙ্ক অঙ্ক_renderers;
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
সংরচনা SDL_VideoDisplay
{
    SDL_DisplayID id;
    ৱর্ণ *name;
    পূর্ণাঙ্ক max_fullscreen_modes;
    পূর্ণাঙ্ক অঙ্ক_fullscreen_modes;
    SDL_DisplayMode *fullscreen_modes;
    SDL_DisplayMode desktop_mode;
    ধ্রুৱ SDL_DisplayMode *current_mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    ভিন্ন content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_active;
    SDL_Window *fullscreen_window;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_DisplayData *internal;
};

// Video device flags
প্রকারনির্দেশ গণনা
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
প্রকারনির্দেশ গণনা
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

প্রকারনির্দেশ গণনা
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_FullscreenResult;

সংরচনা SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    ধ্রুৱ ৱর্ণ *name;

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
    শূন্য (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    শূন্য (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    শূন্য (*RefreshDisplays)(SDL_VideoDevice *_this);

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
    শূন্য (*SetWindowTitle)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowIcon)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
    bool (*SetWindowPosition)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*SetWindowSize)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*SetWindowMinimumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*SetWindowMaximumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*SetWindowAspectRatio)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GetWindowBordersSize)(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক *শীৰ্ষ, পূর্ণাঙ্ক *বাম, পূর্ণাঙ্ক *bottom, পূর্ণাঙ্ক *ডান);
    ভিন্ন (*GetWindowContentScale)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*GetWindowSizeInPixels)(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক *w, পূর্ণাঙ্ক *h);
    bool (*SetWindowOpacity)(SDL_VideoDevice *_this, SDL_Window *window, ভিন্ন opacity);
    bool (*SetWindowParent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
    bool (*SetWindowModal)(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
    শূন্য (*ShowWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*HideWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*RaiseWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*MaximizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*MinimizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*RestoreWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*SetWindowBordered)(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
    শূন্য (*SetWindowResizable)(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
    শূন্য (*Set_Window_Always_On_শীৰ্ষ)(SDL_VideoDevice *_this, SDL_Window *window, bool on_শীৰ্ষ);
    SDL_FullscreenResult (*SetWindowFullscreen)(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    শূন্য *(*GetWindowICCProfile)(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
    SDL_DisplayID (*GetDisplayForWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseRect)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    bool (*SetWindowKeyboardGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    শূন্য (*DestroyWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*CreateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, শূন্য **pixels, পূর্ণাঙ্ক *pitch);
    bool (*SetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক vsync);
    bool (*GetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক *vsync);
    bool (*UpdateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুৱ SDL_Rect *rects, পূর্ণাঙ্ক numrects);
    শূন্য (*DestroyWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*OnWindowEnter)(SDL_VideoDevice *_this, SDL_Window *window);
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
    bool (*GL_LoadLibrary)(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *path);
    SDL_FunctionPointer (*GL_GetProcAddress)(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *proc);
    শূন্য (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_SetSwapInterval)(SDL_VideoDevice *_this, পূর্ণাঙ্ক interval);
    bool (*GL_GetSwapInterval)(SDL_VideoDevice *_this, পূর্ণাঙ্ক *interval);
    bool (*GL_SwapWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    শূন্য (*GL_SetDefaultProfileConfig)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_LoadLibrary)(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *path);
    শূন্য (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    ৱর্ণ ধ্রুৱ * ধ্রুৱ *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *গুনতি);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_Window *window, VkInstance instance, ধ্রুৱ সংরচনা VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
    শূন্য (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ধ্রুৱ সংরচনা VkAllocationCallbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 queueFamilyIndex);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    শূন্য *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    পূর্ণাঙ্ক (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    শূন্য (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*Start_Text_প্ৰবেশ)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    bool (*Stop_Text_প্ৰবেশ)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Update_Text_প্ৰবেশ_Area)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_Window *window);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    শূন্য (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    শূন্য (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*Set_Text_প্ৰবেশ_Properties)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);

    // Clipboard
    ধ্রুৱ ৱর্ণ *ধ্রুৱ *(*GetTextMimeTypes)(SDL_VideoDevice *_this, size_t *অঙ্ক_mime_types);
    bool (*SetClipboardData)(SDL_VideoDevice *_this);
    শূন্য *(*GetClipboardData)(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *mime_type, size_t *size);
    bool (*HasClipboardData)(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*SetClipboardText)(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *text);
    ৱর্ণ *(*GetClipboardText)(SDL_VideoDevice *_this);
    bool (*HasClipboardText)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*SetPrimarySelectionText)(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *text);
    ৱর্ণ *(*GetPrimarySelectionText)(SDL_VideoDevice *_this);
    bool (*HasPrimarySelectionText)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*ShowMessageBox)(SDL_VideoDevice *_this, ধ্রুৱ SDL_MessageBoxData *messageboxdata, পূর্ণাঙ্ক *buttonID);

    // Hit-testing
    bool (*SetWindowHitTest)(SDL_Window *window, bool enabled);

    // Tell window that app enabled drag'n'drop events
    শূন্য (*AcceptDragAndDrop)(SDL_Window *window, bool accept);

    // Display the system-level window menu
    শূন্য (*ShowWindowSystemMenu)(SDL_Window *window, পূর্ণাঙ্ক x, পূর্ণাঙ্ক y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    শূন্য *wakeup_window;
    পূর্ণাঙ্ক অঙ্ক_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_Window *windows;
    SDL_Window *grabbed_window;
    Uint32 clipboard_sequence;
    SDL_ClipboardDataCallback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    শূন্য *clipboard_userdata;
    ৱর্ণ **clipboard_mime_types;
    size_t অঙ্ক_clipboard_mime_types;
    ৱর্ণ *primary_selection_text;
    bool setting_display_mode;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    সংরচনা
    {
        পূর্ণাঙ্ক red_size;
        পূর্ণাঙ্ক green_size;
        পূর্ণাঙ্ক blue_size;
        পূর্ণাঙ্ক alpha_size;
        পূর্ণাঙ্ক depth_size;
        পূর্ণাঙ্ক buffer_size;
        পূর্ণাঙ্ক stencil_size;
        পূর্ণাঙ্ক double_buffer;
        পূর্ণাঙ্ক accum_red_size;
        পূর্ণাঙ্ক accum_green_size;
        পূর্ণাঙ্ক accum_blue_size;
        পূর্ণাঙ্ক accum_alpha_size;
        পূর্ণাঙ্ক stereo;
        পূর্ণাঙ্ক multisamplebuffers;
        পূর্ণাঙ্ক multisamplesamples;
        পূর্ণাঙ্ক floatbuffers;
        পূর্ণাঙ্ক accelerated;
        পূর্ণাঙ্ক major_version;
        পূর্ণাঙ্ক minor_version;
        পূর্ণাঙ্ক flags;
        পূর্ণাঙ্ক profile_mask;
        পূর্ণাঙ্ক share_with_current_context;
        পূর্ণাঙ্ক release_behavior;
        পূর্ণাঙ্ক reset_notification;
        পূর্ণাঙ্ক framebuffer_srgb_capable;
        পূর্ণাঙ্ক no_error;
        পূর্ণাঙ্ক retained_backing;
        পূর্ণাঙ্ক egl_platform;
        পূর্ণাঙ্ক driver_loaded;
        পূর্ণাঙ্ক HAS_GL_ARB_color_buffer_float;
        ৱর্ণ driver_path[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    শূন্য *egl_attrib_callback_userdata;

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
    সংরচনা
    {
        SDL_FunctionPointer vkGetInstanceProcAddr;
        SDL_FunctionPointer vkEnumerateInstanceExtensionProperties;
        পূর্ণাঙ্ক loader_loaded;
        ৱর্ণ loader_path[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_VideoData *internal;
    সংরচনা SDL_GLDriverData *gl_data;

#ifdef SDL_VIDEO_OPENGL_EGL
    সংরচনা SDL_EGL_VideoData *egl_data;
#endif

#যদি defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    সংরচনা SDL_PrivateGLESData *gles_data;
#endif

    /* * * */
    // The function used to dispose of this structure
    শূন্য (*মুক্ত)(SDL_VideoDevice *_this);
};

প্রকারনির্দেশ সংরচনা VideoBootStrap
{
    ধ্রুৱ ৱর্ণ *name;
    ধ্রুৱ ৱর্ণ *desc;
    SDL_VideoDevice *(*create)(শূন্য);
    bool (*ShowMessageBox)(ধ্রুৱ SDL_MessageBoxData *messageboxdata, পূর্ণাঙ্ক *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
বাহ্য VideoBootStrap PRIVATE_bootstrap;
বাহ্য VideoBootStrap COCOA_bootstrap;
বাহ্য VideoBootStrap X11_bootstrap;
বাহ্য VideoBootStrap WINDOWS_bootstrap;
বাহ্য VideoBootStrap HAIKU_bootstrap;
বাহ্য VideoBootStrap UIKIT_bootstrap;
বাহ্য VideoBootStrap Android_bootstrap;
বাহ্য VideoBootStrap OPENHARMONY_bootstrap;
বাহ্য VideoBootStrap PS2_bootstrap;
বাহ্য VideoBootStrap PSP_bootstrap;
বাহ্য VideoBootStrap VITA_bootstrap;
বাহ্য VideoBootStrap RISCOS_bootstrap;
বাহ্য VideoBootStrap N3DS_bootstrap;
বাহ্য VideoBootStrap NGAGE_bootstrap;
বাহ্য VideoBootStrap RPI_bootstrap;
বাহ্য VideoBootStrap KMSDRM_bootstrap;
বাহ্য VideoBootStrap DUMMY_bootstrap;
বাহ্য VideoBootStrap DUMMY_evdev_bootstrap;
বাহ্য VideoBootStrap Wayland_preferred_bootstrap;
বাহ্য VideoBootStrap Wayland_bootstrap;
বাহ্য VideoBootStrap VIVANTE_bootstrap;
বাহ্য VideoBootStrap Emscripten_bootstrap;
বাহ্য VideoBootStrap OFFSCREEN_bootstrap;
বাহ্য VideoBootStrap QNX_bootstrap;
বাহ্য VideoBootStrap OPENVR_bootstrap;
বাহ্য VideoBootStrap DOSVESA_bootstrap;

বাহ্য bool SDL_UninitializedVideo(শূন্য);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
বাহ্য bool SDL_OnVideoThread(শূন্য);
বাহ্য SDL_VideoDevice *SDL_GetVideoDevice(শূন্য);
বাহ্য শূন্য SDL_SetSystemTheme(SDL_SystemTheme theme);
বাহ্য SDL_DisplayID SDL_AddBasicVideoDisplay(ধ্রুৱ SDL_DisplayMode *desktop_mode);
বাহ্য SDL_DisplayID SDL_AddVideoDisplay(ধ্রুৱ SDL_VideoDisplay *display, bool send_event);
বাহ্য শূন্য SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
বাহ্য bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ধ্রুৱ SDL_DisplayMode *mode);
বাহ্য শূন্য SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
বাহ্য শূন্য SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ধ্রুৱ SDL_DisplayMode *mode);
বাহ্য শূন্য SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ধ্রুৱ SDL_DisplayMode *mode);
বাহ্য শূন্য SDL_SetDisplayContentScale(SDL_VideoDisplay *display, ভিন্ন scale);
বাহ্য শূন্য SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ধ্রুৱ SDL_HDROutputProperties *HDR);
বাহ্য bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode);
বাহ্য SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
বাহ্য SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window);
বাহ্য SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window);
বাহ্য SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window);
বাহ্য পূর্ণাঙ্ক SDL_GetDisplayIndex(SDL_DisplayID displayID);
বাহ্য SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID display);
বাহ্য SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window);
বাহ্য পূর্ণাঙ্ক SDL_Get_Message_Box_গুনতি(শূন্য);
বাহ্য শূন্য SDL_SetWindowHDRProperties(SDL_Window *window, ধ্রুৱ SDL_HDROutputProperties *HDR, bool send_event);
বাহ্য শূন্য SDL_SetWindowSafeAreaInsets(SDL_Window *window, পূর্ণাঙ্ক বাম, পূর্ণাঙ্ক ডান, পূর্ণাঙ্ক শীৰ্ষ, পূর্ণাঙ্ক bottom);

বাহ্য শূন্য SDL_GL_DeduceMaxSupportedESProfile(পূর্ণাঙ্ক *major, পূর্ণাঙ্ক *minor);

বাহ্য bool SDL_RecreateWindow(SDL_Window *window, SDL_WindowFlags flags);
বাহ্য bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags);
বাহ্য bool SDL_HasWindows(শূন্য);
বাহ্য শূন্য SDL_RelativeToGlobalForWindow(SDL_Window *window, পূর্ণাঙ্ক rel_x, পূর্ণাঙ্ক rel_y, পূর্ণাঙ্ক *abs_x, পূর্ণাঙ্ক *abs_y);
বাহ্য শূন্য SDL_GlobalToRelativeForWindow(SDL_Window *window, পূর্ণাঙ্ক abs_x, পূর্ণাঙ্ক abs_y, পূর্ণাঙ্ক *rel_x, পূর্ণাঙ্ক *rel_y);
বাহ্য bool SDL_ShouldFocusPopup(SDL_Window *window);
বাহ্য bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus);

বাহ্য শূন্য SDL_OnDisplayAdded(SDL_VideoDisplay *display);
বাহ্য শূন্য SDL_OnDisplayMoved(SDL_VideoDisplay *display);
বাহ্য শূন্য SDL_OnWindowShown(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowHidden(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowMoved(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowResized(SDL_Window *window);
বাহ্য শূন্য SDL_CheckWindowPixelSizeChanged(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowPixelSizeChanged(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowLiveResizeUpdate(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowMinimized(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowMaximized(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowRestored(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowEnter(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowLeave(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowFocusGained(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowFocusLost(SDL_Window *window);
বাহ্য শূন্য SDL_OnWindowDisplayChanged(SDL_Window *window);
বাহ্য শূন্য SDL_UpdateWindowGrab(SDL_Window *window);
বাহ্য bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit);
বাহ্য SDL_Window *SDL_GetToplevelForKeyboardFocus(শূন্য);

বাহ্য bool SDL_ShouldAllowTopmost(শূন্য);

বাহ্য শূন্য SDL_ToggleDragAndDropSupport(শূন্য);

বাহ্য শূন্য SDL_UpdateDesktopBounds(শূন্য);

বাহ্য SDL_Text_প্ৰবেশ_Type SDL_Get_Text_প্ৰবেশ_Type(SDL_PropertiesID props);
বাহ্য SDL_Capitalization SDL_Get_Text_প্ৰবেশ_Capitalization(SDL_PropertiesID props);
বাহ্য bool SDL_Get_Text_প্ৰবেশ_Autocorrect(SDL_PropertiesID props);
বাহ্য bool SDL_Get_Text_প্ৰবেশ_Multiline(SDL_PropertiesID props);

বাহ্য শূন্য SDL_SendScreenKeyboardShown(শূন্য);
বাহ্য শূন্য SDL_SendScreenKeyboardHidden(শূন্য);

#endif // SDL_sysvideo_h_
