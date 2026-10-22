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
#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_sysvideo_h_
#define SDL_sysvideo_h_

#অন্তর্ভাব <SDL3/SDL_vulkan.h>

#অন্তর্ভাব "SDL_surface_c.h"

// The SDL video driver

প্রকারলেখ কাঠামো SDL_VideoDisplay SDL_VideoDisplay;
প্রকারলেখ কাঠামো SDL_VideoDevice SDL_VideoDevice;
প্রকারলেখ কাঠামো SDL_Video_তথ্য SDL_Video_তথ্য;
প্রকারলেখ কাঠামো SDL_Display_তথ্য SDL_Display_তথ্য;
প্রকারলেখ কাঠামো SDL_Window_তথ্য SDL_Window_তথ্য;

প্রকারলেখ কাঠামো
{
    দশমিক SDR_white_level;
    দশমিক HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
কাঠামো SDL_Window
{
    SDL_WindowID id;
    অক্ষর *title;
    SDL_Surface *icon;
    পূর্ণসংখ্যা x, y;
    পূর্ণসংখ্যা w, h;
    পূর্ণসংখ্যা min_w, min_h;
    পূর্ণসংখ্যা max_w, max_h;
    দশমিক min_aspect;
    দশমিক max_aspect;
    পূর্ণসংখ্যা last_pixel_w, last_pixel_h;
    SDL_WindowFlags flags;
    SDL_WindowFlags pending_flags;
    দশমিক display_scale;
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

    দশমিক opacity;

    SDL_Surface *surface;
    bool surface_valid;

    bool is_hiding;
    bool restore_on_show; // Child was hidden recursively by the parent, restore when shown.
    bool last_position_pending; // This should NOT be cleared by the backend, as it is used for fullscreen positioning.
    bool last_আকার_pending; // This should be cleared by the backend if the new size cannot be applied.
    bool update_fullscreen_on_display_changed;
    bool constrain_popup;
    bool is_destroying;
    bool is_dropping; // drag/drop in progress, expecting SDL_SendDropComplete().

    পূর্ণসংখ্যা safe_inset_বাম;
    পূর্ণসংখ্যা safe_inset_ডান;
    পূর্ণসংখ্যা safe_inset_শীর্ষ;
    পূর্ণসংখ্যা safe_inset_bottom;
    SDL_Rect safe_rect;

    SDL_PropertiesID text_প্রবেশ_props;
    bool text_প্রবেশ_active;
    SDL_Rect text_প্রবেশ_rect;
    পূর্ণসংখ্যা text_প্রবেশ_cursor;

    SDL_Rect mouse_rect;

    SDL_HitTest hit_test;
    শূন্য *hit_test_তথ্য;

    SDL_ProgressState progress_state;
    দশমিক progress_মান;

    SDL_PropertiesID props;

    পূর্ণসংখ্যা অঙ্ক_renderers;
    SDL_Renderer **renderers;

    SDL_Window_তথ্য *internal;

    // If a toplevel window, holds the current keyboard focus for grabbing popups.
    SDL_Window *keyboard_focus;

    SDL_Window *পূর্ব;
    SDL_Window *পরবর্তী;

    SDL_Window *parent;
    SDL_Window *first_child;
    SDL_Window *পূর্ব_sibling;
    SDL_Window *পরবর্তী_sibling;
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
কাঠামো SDL_VideoDisplay
{
    SDL_DisplayID id;
    অক্ষর *name;
    পূর্ণসংখ্যা max_fullscreen_modes;
    পূর্ণসংখ্যা অঙ্ক_fullscreen_modes;
    SDL_DisplayMode *fullscreen_modes;
    SDL_DisplayMode desktop_mode;
    ধ্রুবক SDL_DisplayMode *current_mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    দশমিক content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_active;
    SDL_Window *fullscreen_window;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_Display_তথ্য *internal;
};

// Video device flags
প্রকারলেখ গণনা
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
প্রকারলেখ গণনা
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

প্রকারলেখ গণনা
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_Fullscreen_ফলাফল;

কাঠামো SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    ধ্রুবক অক্ষর *name;

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
    শূন্য (*Set_Window_আকার)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*Set_Window_Minimum_আকার)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*Set_Window_Maximum_আকার)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*SetWindowAspectRatio)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Get_Window_Borders_আকার)(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণসংখ্যা *শীর্ষ, পূর্ণসংখ্যা *বাম, পূর্ণসংখ্যা *bottom, পূর্ণসংখ্যা *ডান);
    দশমিক (*GetWindowContentScale)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*Get_Window_আকার_In_Pixels)(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণসংখ্যা *w, পূর্ণসংখ্যা *h);
    bool (*SetWindowOpacity)(SDL_VideoDevice *_this, SDL_Window *window, দশমিক opacity);
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
    শূন্য (*Set_Window_Always_On_শীর্ষ)(SDL_VideoDevice *_this, SDL_Window *window, bool on_শীর্ষ);
    SDL_Fullscreen_ফলাফল (*SetWindowFullscreen)(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    শূন্য *(*GetWindowICCProfile)(SDL_VideoDevice *_this, SDL_Window *window, size_t *আকার_2);
    SDL_DisplayID (*GetDisplayForWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseRect)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    bool (*SetWindowKeyboardGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    শূন্য (*DestroyWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*CreateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, শূন্য **pixels, পূর্ণসংখ্যা *pitch);
    bool (*SetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণসংখ্যা vsync);
    bool (*GetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণসংখ্যা *vsync);
    bool (*UpdateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুবক SDL_Rect *rects, পূর্ণসংখ্যা numrects);
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
    bool (*GL_LoadLibrary)(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path);
    SDL_FunctionPointer (*GL_GetProcAddress)(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *proc);
    শূন্য (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_SetSwapInterval)(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval);
    bool (*GL_GetSwapInterval)(SDL_VideoDevice *_this, পূর্ণসংখ্যা *interval);
    bool (*GL_SwapWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    শূন্য (*GL_SetDefaultProfileConfig)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_LoadLibrary)(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path);
    শূন্য (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    অক্ষর ধ্রুবক * ধ্রুবক *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *গুনতি);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_Window *window, VkInstance instance, ধ্রুবক কাঠামো VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
    শূন্য (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ধ্রুবক কাঠামো VkAllocationCallbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 queue_Family_সূচক);

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
    পূর্ণসংখ্যা (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    শূন্য (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*Start_Text_প্রবেশ)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    bool (*Stop_Text_প্রবেশ)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Update_Text_প্রবেশ_Area)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_Window *window);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    শূন্য (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    শূন্য (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window);
    শূন্য (*Set_Text_প্রবেশ_Properties)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);

    // Clipboard
    ধ্রুবক অক্ষর *ধ্রুবক *(*GetTextMimeTypes)(SDL_VideoDevice *_this, size_t *অঙ্ক_mime_types);
    bool (*Set_Clipboard_তথ্য)(SDL_VideoDevice *_this);
    শূন্য *(*Get_Clipboard_তথ্য)(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *mime_type, size_t *আকার_2);
    bool (*Has_Clipboard_তথ্য)(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*SetClipboardText)(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *text);
    অক্ষর *(*GetClipboardText)(SDL_VideoDevice *_this);
    bool (*HasClipboardText)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*SetPrimarySelectionText)(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *text);
    অক্ষর *(*GetPrimarySelectionText)(SDL_VideoDevice *_this);
    bool (*HasPrimarySelectionText)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*ShowMessageBox)(SDL_VideoDevice *_this, ধ্রুবক SDL_Message_Box_তথ্য *messageboxdata, পূর্ণসংখ্যা *buttonID);

    // Hit-testing
    bool (*SetWindowHitTest)(SDL_Window *window, bool enabled);

    // Tell window that app enabled drag'n'drop events
    শূন্য (*AcceptDragAndDrop)(SDL_Window *window, bool accept);

    // Display the system-level window menu
    শূন্য (*ShowWindowSystemMenu)(SDL_Window *window, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    শূন্য *wakeup_window;
    পূর্ণসংখ্যা অঙ্ক_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_Window *windows;
    SDL_Window *grabbed_window;
    Uint32 clipboard_sequence;
    SDL_Clipboard_তথ্য_Callback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    শূন্য *clipboard_userdata;
    অক্ষর **clipboard_mime_types;
    size_t অঙ্ক_clipboard_mime_types;
    অক্ষর *primary_selection_text;
    bool setting_display_mode;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    কাঠামো
    {
        পূর্ণসংখ্যা red_আকার;
        পূর্ণসংখ্যা green_আকার;
        পূর্ণসংখ্যা blue_আকার;
        পূর্ণসংখ্যা alpha_আকার;
        পূর্ণসংখ্যা depth_আকার;
        পূর্ণসংখ্যা বাফার_আকার;
        পূর্ণসংখ্যা stencil_আকার;
        পূর্ণসংখ্যা double_বাফার;
        পূর্ণসংখ্যা accum_red_আকার;
        পূর্ণসংখ্যা accum_green_আকার;
        পূর্ণসংখ্যা accum_blue_আকার;
        পূর্ণসংখ্যা accum_alpha_আকার;
        পূর্ণসংখ্যা stereo;
        পূর্ণসংখ্যা multisamplebuffers;
        পূর্ণসংখ্যা multisamplesamples;
        পূর্ণসংখ্যা floatbuffers;
        পূর্ণসংখ্যা accelerated;
        পূর্ণসংখ্যা major_version;
        পূর্ণসংখ্যা minor_version;
        পূর্ণসংখ্যা flags;
        পূর্ণসংখ্যা profile_mask;
        পূর্ণসংখ্যা share_with_current_context;
        পূর্ণসংখ্যা release_behavior;
        পূর্ণসংখ্যা reset_notification;
        পূর্ণসংখ্যা framebuffer_srgb_capable;
        পূর্ণসংখ্যা no_error;
        পূর্ণসংখ্যা retained_backing;
        পূর্ণসংখ্যা egl_platform;
        পূর্ণসংখ্যা driver_loaded;
        পূর্ণসংখ্যা HAS_GL_ARB_color_বাফার_float;
        অক্ষর driver_path[256];
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
    কাঠামো
    {
        SDL_FunctionPointer vkGetInstanceProcAddr;
        SDL_FunctionPointer vkEnumerateInstanceExtensionProperties;
        পূর্ণসংখ্যা loader_loaded;
        অক্ষর loader_path[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_Video_তথ্য *internal;
    কাঠামো SDL_GLDriver_তথ্য *gl_তথ্য;

#ifdef SDL_VIDEO_OPENGL_EGL
    কাঠামো SDL_EGL_Video_তথ্য *egl_তথ্য;
#endif

#যদি defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    কাঠামো SDL_PrivateGLESData *gles_তথ্য;
#endif

    /* * * */
    // The function used to dispose of this structure
    শূন্য (*মুক্ত)(SDL_VideoDevice *_this);
};

প্রকারলেখ কাঠামো VideoBootStrap
{
    ধ্রুবক অক্ষর *name;
    ধ্রুবক অক্ষর *desc;
    SDL_VideoDevice *(*create)(শূন্য);
    bool (*ShowMessageBox)(ধ্রুবক SDL_Message_Box_তথ্য *messageboxdata, পূর্ণসংখ্যা *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
বাহ্যিক VideoBootStrap PRIVATE_bootstrap;
বাহ্যিক VideoBootStrap COCOA_bootstrap;
বাহ্যিক VideoBootStrap X11_bootstrap;
বাহ্যিক VideoBootStrap WINDOWS_bootstrap;
বাহ্যিক VideoBootStrap HAIKU_bootstrap;
বাহ্যিক VideoBootStrap UIKIT_bootstrap;
বাহ্যিক VideoBootStrap Android_bootstrap;
বাহ্যিক VideoBootStrap OPENHARMONY_bootstrap;
বাহ্যিক VideoBootStrap PS2_bootstrap;
বাহ্যিক VideoBootStrap PSP_bootstrap;
বাহ্যিক VideoBootStrap VITA_bootstrap;
বাহ্যিক VideoBootStrap RISCOS_bootstrap;
বাহ্যিক VideoBootStrap N3DS_bootstrap;
বাহ্যিক VideoBootStrap NGAGE_bootstrap;
বাহ্যিক VideoBootStrap RPI_bootstrap;
বাহ্যিক VideoBootStrap KMSDRM_bootstrap;
বাহ্যিক VideoBootStrap DUMMY_bootstrap;
বাহ্যিক VideoBootStrap DUMMY_evdev_bootstrap;
বাহ্যিক VideoBootStrap Wayland_preferred_bootstrap;
বাহ্যিক VideoBootStrap Wayland_bootstrap;
বাহ্যিক VideoBootStrap VIVANTE_bootstrap;
বাহ্যিক VideoBootStrap Emscripten_bootstrap;
বাহ্যিক VideoBootStrap OFFSCREEN_bootstrap;
বাহ্যিক VideoBootStrap QNX_bootstrap;
বাহ্যিক VideoBootStrap OPENVR_bootstrap;
বাহ্যিক VideoBootStrap DOSVESA_bootstrap;

বাহ্যিক bool SDL_UninitializedVideo(শূন্য);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
বাহ্যিক bool SDL_OnVideoThread(শূন্য);
বাহ্যিক SDL_VideoDevice *SDL_GetVideoDevice(শূন্য);
বাহ্যিক শূন্য SDL_SetSystemTheme(SDL_SystemTheme theme);
বাহ্যিক SDL_DisplayID SDL_AddBasicVideoDisplay(ধ্রুবক SDL_DisplayMode *desktop_mode);
বাহ্যিক SDL_DisplayID SDL_AddVideoDisplay(ধ্রুবক SDL_VideoDisplay *display, bool send_event);
বাহ্যিক শূন্য SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
বাহ্যিক bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ধ্রুবক SDL_DisplayMode *mode);
বাহ্যিক শূন্য SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
বাহ্যিক শূন্য SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ধ্রুবক SDL_DisplayMode *mode);
বাহ্যিক শূন্য SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ধ্রুবক SDL_DisplayMode *mode);
বাহ্যিক শূন্য SDL_SetDisplayContentScale(SDL_VideoDisplay *display, দশমিক scale);
বাহ্যিক শূন্য SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ধ্রুবক SDL_HDROutputProperties *HDR);
বাহ্যিক bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode);
বাহ্যিক SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
বাহ্যিক SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window);
বাহ্যিক SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window);
বাহ্যিক SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window);
বাহ্যিক পূর্ণসংখ্যা SDL_Get_Display_সূচক(SDL_DisplayID displayID);
বাহ্যিক SDL_Display_তথ্য *SDL_Get_Display_Driver_তথ্য(SDL_DisplayID display);
বাহ্যিক SDL_Display_তথ্য *SDL_Get_Display_Driver_তথ্য_For_Window(SDL_Window *window);
বাহ্যিক পূর্ণসংখ্যা SDL_Get_Message_Box_গুনতি(শূন্য);
বাহ্যিক শূন্য SDL_SetWindowHDRProperties(SDL_Window *window, ধ্রুবক SDL_HDROutputProperties *HDR, bool send_event);
বাহ্যিক শূন্য SDL_SetWindowSafeAreaInsets(SDL_Window *window, পূর্ণসংখ্যা বাম, পূর্ণসংখ্যা ডান, পূর্ণসংখ্যা শীর্ষ, পূর্ণসংখ্যা bottom);

বাহ্যিক শূন্য SDL_GL_DeduceMaxSupportedESProfile(পূর্ণসংখ্যা *major, পূর্ণসংখ্যা *minor);

বাহ্যিক bool SDL_RecreateWindow(SDL_Window *window, SDL_WindowFlags flags);
বাহ্যিক bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags);
বাহ্যিক bool SDL_HasWindows(শূন্য);
বাহ্যিক শূন্য SDL_RelativeToGlobalForWindow(SDL_Window *window, পূর্ণসংখ্যা rel_x, পূর্ণসংখ্যা rel_y, পূর্ণসংখ্যা *abs_x, পূর্ণসংখ্যা *abs_y);
বাহ্যিক শূন্য SDL_GlobalToRelativeForWindow(SDL_Window *window, পূর্ণসংখ্যা abs_x, পূর্ণসংখ্যা abs_y, পূর্ণসংখ্যা *rel_x, পূর্ণসংখ্যা *rel_y);
বাহ্যিক bool SDL_ShouldFocusPopup(SDL_Window *window);
বাহ্যিক bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus);

বাহ্যিক শূন্য SDL_OnDisplayAdded(SDL_VideoDisplay *display);
বাহ্যিক শূন্য SDL_OnDisplayMoved(SDL_VideoDisplay *display);
বাহ্যিক শূন্য SDL_OnWindowShown(SDL_Window *window);
বাহ্যিক শূন্য SDL_OnWindowHidden(SDL_Window *window);
বাহ্যিক শূন্য SDL_OnWindowMoved(SDL_Window *window);
বাহ্যিক শূন্য SDL_OnWindowResized(SDL_Window *window);
বাহ্যিক শূন্য SDL_Check_Window_Pixel_আকার_Changed(SDL_Window *window);
বাহ্যিক শূন্য SDL_On_Window_Pixel_আকার_Changed(SDL_Window *window);
বাহ্যিক শূন্য SDL_OnWindowLiveResizeUpdate(SDL_Window *window);
বাহ্যিক শূন্য SDL_OnWindowMinimized(SDL_Window *window);
বাহ্যিক শূন্য SDL_OnWindowMaximized(SDL_Window *window);
বাহ্যিক শূন্য SDL_OnWindowRestored(SDL_Window *window);
বাহ্যিক শূন্য SDL_OnWindowEnter(SDL_Window *window);
বাহ্যিক শূন্য SDL_OnWindowLeave(SDL_Window *window);
বাহ্যিক শূন্য SDL_OnWindowFocusGained(SDL_Window *window);
বাহ্যিক শূন্য SDL_OnWindowFocusLost(SDL_Window *window);
বাহ্যিক শূন্য SDL_OnWindowDisplayChanged(SDL_Window *window);
বাহ্যিক শূন্য SDL_UpdateWindowGrab(SDL_Window *window);
বাহ্যিক bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit);
বাহ্যিক SDL_Window *SDL_GetToplevelForKeyboardFocus(শূন্য);

বাহ্যিক bool SDL_ShouldAllowTopmost(শূন্য);

বাহ্যিক শূন্য SDL_ToggleDragAndDropSupport(শূন্য);

বাহ্যিক শূন্য SDL_UpdateDesktopBounds(শূন্য);

বাহ্যিক SDL_Text_প্রবেশ_Type SDL_Get_Text_প্রবেশ_Type(SDL_PropertiesID props);
বাহ্যিক SDL_Capitalization SDL_Get_Text_প্রবেশ_Capitalization(SDL_PropertiesID props);
বাহ্যিক bool SDL_Get_Text_প্রবেশ_Autocorrect(SDL_PropertiesID props);
বাহ্যিক bool SDL_Get_Text_প্রবেশ_Multiline(SDL_PropertiesID props);

বাহ্যিক শূন্য SDL_SendScreenKeyboardShown(শূন্য);
বাহ্যিক শূন্য SDL_SendScreenKeyboardHidden(শূন্য);

#endif // SDL_sysvideo_h_
