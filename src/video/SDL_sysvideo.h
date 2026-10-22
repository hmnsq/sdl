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
#अन्तर्भाव "SDL_internal.h"

#ifndef SDL_sysvideo_h_
#define SDL_sysvideo_h_

#अन्तर्भाव <SDL3/SDL_vulkan.h>

#अन्तर्भाव "SDL_surface_c.h"

// The SDL video driver

प्रकारनिर्देश संरचना SDL_VideoDisplay SDL_VideoDisplay;
प्रकारनिर्देश संरचना SDL_VideoDevice SDL_VideoDevice;
प्रकारनिर्देश संरचना SDL_VideoData SDL_VideoData;
प्रकारनिर्देश संरचना SDL_DisplayData SDL_DisplayData;
प्रकारनिर्देश संरचना SDL_WindowData SDL_WindowData;

प्रकारनिर्देश संरचना
{
    भिन्न SDR_white_level;
    भिन्न HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
संरचना SDL_Window
{
    SDL_WindowID id;
    वर्ण *title;
    SDL_Surface *icon;
    पूर्णाङ्क x, y;
    पूर्णाङ्क w, h;
    पूर्णाङ्क min_w, min_h;
    पूर्णाङ्क max_w, max_h;
    भिन्न min_aspect;
    भिन्न max_aspect;
    पूर्णाङ्क last_pixel_w, last_pixel_h;
    SDL_WindowFlags flags;
    SDL_WindowFlags pending_flags;
    भिन्न display_scale;
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

    भिन्न opacity;

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

    पूर्णाङ्क safe_inset_बायाँ;
    पूर्णाङ्क safe_inset_दायाँ;
    पूर्णाङ्क safe_inset_शीर्ष;
    पूर्णाङ्क safe_inset_bottom;
    SDL_Rect safe_rect;

    SDL_PropertiesID text_निवेश_props;
    bool text_निवेश_active;
    SDL_Rect text_निवेश_rect;
    पूर्णाङ्क text_निवेश_cursor;

    SDL_Rect mouse_rect;

    SDL_HitTest hit_test;
    शून्य *hit_test_data;

    SDL_ProgressState progress_state;
    भिन्न progress_मूल्य;

    SDL_PropertiesID props;

    पूर्णाङ्क अंक_renderers;
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
संरचना SDL_VideoDisplay
{
    SDL_DisplayID id;
    वर्ण *name;
    पूर्णाङ्क max_fullscreen_modes;
    पूर्णाङ्क अंक_fullscreen_modes;
    SDL_DisplayMode *fullscreen_modes;
    SDL_DisplayMode desktop_mode;
    ध्रुव SDL_DisplayMode *current_mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    भिन्न content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_active;
    SDL_Window *fullscreen_window;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_DisplayData *internal;
};

// Video device flags
प्रकारनिर्देश गणना
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
प्रकारनिर्देश गणना
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

प्रकारनिर्देश गणना
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_FullscreenResult;

संरचना SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    ध्रुव वर्ण *name;

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
    शून्य (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    शून्य (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    शून्य (*RefreshDisplays)(SDL_VideoDevice *_this);

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
    शून्य (*SetWindowTitle)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowIcon)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
    bool (*SetWindowPosition)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*SetWindowSize)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*SetWindowMinimumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*SetWindowMaximumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*SetWindowAspectRatio)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GetWindowBordersSize)(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *शीर्ष, पूर्णाङ्क *बायाँ, पूर्णाङ्क *bottom, पूर्णाङ्क *दायाँ);
    भिन्न (*GetWindowContentScale)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*GetWindowSizeInPixels)(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *w, पूर्णाङ्क *h);
    bool (*SetWindowOpacity)(SDL_VideoDevice *_this, SDL_Window *window, भिन्न opacity);
    bool (*SetWindowParent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
    bool (*SetWindowModal)(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
    शून्य (*ShowWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*HideWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*RaiseWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*MaximizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*MinimizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*RestoreWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*SetWindowBordered)(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
    शून्य (*SetWindowResizable)(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
    शून्य (*Set_Window_Always_On_शीर्ष)(SDL_VideoDevice *_this, SDL_Window *window, bool on_शीर्ष);
    SDL_FullscreenResult (*SetWindowFullscreen)(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    शून्य *(*GetWindowICCProfile)(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
    SDL_DisplayID (*GetDisplayForWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseRect)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    bool (*SetWindowKeyboardGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    शून्य (*DestroyWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*CreateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, शून्य **pixels, पूर्णाङ्क *pitch);
    bool (*SetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क vsync);
    bool (*GetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *vsync);
    bool (*UpdateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, ध्रुव SDL_Rect *rects, पूर्णाङ्क numrects);
    शून्य (*DestroyWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*OnWindowEnter)(SDL_VideoDevice *_this, SDL_Window *window);
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
    bool (*GL_LoadLibrary)(SDL_VideoDevice *_this, ध्रुव वर्ण *path);
    SDL_FunctionPointer (*GL_GetProcAddress)(SDL_VideoDevice *_this, ध्रुव वर्ण *proc);
    शून्य (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_SetSwapInterval)(SDL_VideoDevice *_this, पूर्णाङ्क interval);
    bool (*GL_GetSwapInterval)(SDL_VideoDevice *_this, पूर्णाङ्क *interval);
    bool (*GL_SwapWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    शून्य (*GL_SetDefaultProfileConfig)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_LoadLibrary)(SDL_VideoDevice *_this, ध्रुव वर्ण *path);
    शून्य (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    वर्ण ध्रुव * ध्रुव *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *गिनती);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_Window *window, VkInstance instance, ध्रुव संरचना VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
    शून्य (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ध्रुव संरचना VkAllocationCallbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 queueFamilyIndex);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    शून्य *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    पूर्णाङ्क (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    शून्य (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*Start_Text_निवेश)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    bool (*Stop_Text_निवेश)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Update_Text_निवेश_Area)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_Window *window);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    शून्य (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    शून्य (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window);
    शून्य (*Set_Text_निवेश_Properties)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);

    // Clipboard
    ध्रुव वर्ण *ध्रुव *(*GetTextMimeTypes)(SDL_VideoDevice *_this, size_t *अंक_mime_types);
    bool (*SetClipboardData)(SDL_VideoDevice *_this);
    शून्य *(*GetClipboardData)(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type, size_t *size);
    bool (*HasClipboardData)(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*SetClipboardText)(SDL_VideoDevice *_this, ध्रुव वर्ण *text);
    वर्ण *(*GetClipboardText)(SDL_VideoDevice *_this);
    bool (*HasClipboardText)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*SetPrimarySelectionText)(SDL_VideoDevice *_this, ध्रुव वर्ण *text);
    वर्ण *(*GetPrimarySelectionText)(SDL_VideoDevice *_this);
    bool (*HasPrimarySelectionText)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*ShowMessageBox)(SDL_VideoDevice *_this, ध्रुव SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID);

    // Hit-testing
    bool (*SetWindowHitTest)(SDL_Window *window, bool enabled);

    // Tell window that app enabled drag'n'drop events
    शून्य (*AcceptDragAndDrop)(SDL_Window *window, bool accept);

    // Display the system-level window menu
    शून्य (*ShowWindowSystemMenu)(SDL_Window *window, पूर्णाङ्क x, पूर्णाङ्क y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    शून्य *wakeup_window;
    पूर्णाङ्क अंक_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_Window *windows;
    SDL_Window *grabbed_window;
    Uint32 clipboard_sequence;
    SDL_ClipboardDataCallback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    शून्य *clipboard_userdata;
    वर्ण **clipboard_mime_types;
    size_t अंक_clipboard_mime_types;
    वर्ण *primary_selection_text;
    bool setting_display_mode;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    संरचना
    {
        पूर्णाङ्क red_size;
        पूर्णाङ्क green_size;
        पूर्णाङ्क blue_size;
        पूर्णाङ्क alpha_size;
        पूर्णाङ्क depth_size;
        पूर्णाङ्क buffer_size;
        पूर्णाङ्क stencil_size;
        पूर्णाङ्क double_buffer;
        पूर्णाङ्क accum_red_size;
        पूर्णाङ्क accum_green_size;
        पूर्णाङ्क accum_blue_size;
        पूर्णाङ्क accum_alpha_size;
        पूर्णाङ्क stereo;
        पूर्णाङ्क multisamplebuffers;
        पूर्णाङ्क multisamplesamples;
        पूर्णाङ्क floatbuffers;
        पूर्णाङ्क accelerated;
        पूर्णाङ्क major_version;
        पूर्णाङ्क minor_version;
        पूर्णाङ्क flags;
        पूर्णाङ्क profile_mask;
        पूर्णाङ्क share_with_current_context;
        पूर्णाङ्क release_behavior;
        पूर्णाङ्क reset_notification;
        पूर्णाङ्क framebuffer_srgb_capable;
        पूर्णाङ्क no_error;
        पूर्णाङ्क retained_backing;
        पूर्णाङ्क egl_platform;
        पूर्णाङ्क driver_loaded;
        पूर्णाङ्क HAS_GL_ARB_color_buffer_float;
        वर्ण driver_path[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    शून्य *egl_attrib_callback_userdata;

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
    संरचना
    {
        SDL_FunctionPointer vkGetInstanceProcAddr;
        SDL_FunctionPointer vkEnumerateInstanceExtensionProperties;
        पूर्णाङ्क loader_loaded;
        वर्ण loader_path[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_VideoData *internal;
    संरचना SDL_GLDriverData *gl_data;

#ifdef SDL_VIDEO_OPENGL_EGL
    संरचना SDL_EGL_VideoData *egl_data;
#endif

#यदि defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    संरचना SDL_PrivateGLESData *gles_data;
#endif

    /* * * */
    // The function used to dispose of this structure
    शून्य (*मुक्त)(SDL_VideoDevice *_this);
};

प्रकारनिर्देश संरचना VideoBootStrap
{
    ध्रुव वर्ण *name;
    ध्रुव वर्ण *desc;
    SDL_VideoDevice *(*create)(शून्य);
    bool (*ShowMessageBox)(ध्रुव SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
बाह्य VideoBootStrap PRIVATE_bootstrap;
बाह्य VideoBootStrap COCOA_bootstrap;
बाह्य VideoBootStrap X11_bootstrap;
बाह्य VideoBootStrap WINDOWS_bootstrap;
बाह्य VideoBootStrap HAIKU_bootstrap;
बाह्य VideoBootStrap UIKIT_bootstrap;
बाह्य VideoBootStrap Android_bootstrap;
बाह्य VideoBootStrap OPENHARMONY_bootstrap;
बाह्य VideoBootStrap PS2_bootstrap;
बाह्य VideoBootStrap PSP_bootstrap;
बाह्य VideoBootStrap VITA_bootstrap;
बाह्य VideoBootStrap RISCOS_bootstrap;
बाह्य VideoBootStrap N3DS_bootstrap;
बाह्य VideoBootStrap NGAGE_bootstrap;
बाह्य VideoBootStrap RPI_bootstrap;
बाह्य VideoBootStrap KMSDRM_bootstrap;
बाह्य VideoBootStrap DUMMY_bootstrap;
बाह्य VideoBootStrap DUMMY_evdev_bootstrap;
बाह्य VideoBootStrap Wayland_preferred_bootstrap;
बाह्य VideoBootStrap Wayland_bootstrap;
बाह्य VideoBootStrap VIVANTE_bootstrap;
बाह्य VideoBootStrap Emscripten_bootstrap;
बाह्य VideoBootStrap OFFSCREEN_bootstrap;
बाह्य VideoBootStrap QNX_bootstrap;
बाह्य VideoBootStrap OPENVR_bootstrap;
बाह्य VideoBootStrap DOSVESA_bootstrap;

बाह्य bool SDL_UninitializedVideo(शून्य);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
बाह्य bool SDL_OnVideoThread(शून्य);
बाह्य SDL_VideoDevice *SDL_GetVideoDevice(शून्य);
बाह्य शून्य SDL_SetSystemTheme(SDL_SystemTheme theme);
बाह्य SDL_DisplayID SDL_AddBasicVideoDisplay(ध्रुव SDL_DisplayMode *desktop_mode);
बाह्य SDL_DisplayID SDL_AddVideoDisplay(ध्रुव SDL_VideoDisplay *display, bool send_event);
बाह्य शून्य SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
बाह्य bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ध्रुव SDL_DisplayMode *mode);
बाह्य शून्य SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
बाह्य शून्य SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ध्रुव SDL_DisplayMode *mode);
बाह्य शून्य SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ध्रुव SDL_DisplayMode *mode);
बाह्य शून्य SDL_SetDisplayContentScale(SDL_VideoDisplay *display, भिन्न scale);
बाह्य शून्य SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ध्रुव SDL_HDROutputProperties *HDR);
बाह्य bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode);
बाह्य SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
बाह्य SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window);
बाह्य SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window);
बाह्य SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window);
बाह्य पूर्णाङ्क SDL_GetDisplayIndex(SDL_DisplayID displayID);
बाह्य SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID display);
बाह्य SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window);
बाह्य पूर्णाङ्क SDL_Get_Message_Box_गिनती(शून्य);
बाह्य शून्य SDL_SetWindowHDRProperties(SDL_Window *window, ध्रुव SDL_HDROutputProperties *HDR, bool send_event);
बाह्य शून्य SDL_SetWindowSafeAreaInsets(SDL_Window *window, पूर्णाङ्क बायाँ, पूर्णाङ्क दायाँ, पूर्णाङ्क शीर्ष, पूर्णाङ्क bottom);

बाह्य शून्य SDL_GL_DeduceMaxSupportedESProfile(पूर्णाङ्क *major, पूर्णाङ्क *minor);

बाह्य bool SDL_RecreateWindow(SDL_Window *window, SDL_WindowFlags flags);
बाह्य bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags);
बाह्य bool SDL_HasWindows(शून्य);
बाह्य शून्य SDL_RelativeToGlobalForWindow(SDL_Window *window, पूर्णाङ्क rel_x, पूर्णाङ्क rel_y, पूर्णाङ्क *abs_x, पूर्णाङ्क *abs_y);
बाह्य शून्य SDL_GlobalToRelativeForWindow(SDL_Window *window, पूर्णाङ्क abs_x, पूर्णाङ्क abs_y, पूर्णाङ्क *rel_x, पूर्णाङ्क *rel_y);
बाह्य bool SDL_ShouldFocusPopup(SDL_Window *window);
बाह्य bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus);

बाह्य शून्य SDL_OnDisplayAdded(SDL_VideoDisplay *display);
बाह्य शून्य SDL_OnDisplayMoved(SDL_VideoDisplay *display);
बाह्य शून्य SDL_OnWindowShown(SDL_Window *window);
बाह्य शून्य SDL_OnWindowHidden(SDL_Window *window);
बाह्य शून्य SDL_OnWindowMoved(SDL_Window *window);
बाह्य शून्य SDL_OnWindowResized(SDL_Window *window);
बाह्य शून्य SDL_CheckWindowPixelSizeChanged(SDL_Window *window);
बाह्य शून्य SDL_OnWindowPixelSizeChanged(SDL_Window *window);
बाह्य शून्य SDL_OnWindowLiveResizeUpdate(SDL_Window *window);
बाह्य शून्य SDL_OnWindowMinimized(SDL_Window *window);
बाह्य शून्य SDL_OnWindowMaximized(SDL_Window *window);
बाह्य शून्य SDL_OnWindowRestored(SDL_Window *window);
बाह्य शून्य SDL_OnWindowEnter(SDL_Window *window);
बाह्य शून्य SDL_OnWindowLeave(SDL_Window *window);
बाह्य शून्य SDL_OnWindowFocusGained(SDL_Window *window);
बाह्य शून्य SDL_OnWindowFocusLost(SDL_Window *window);
बाह्य शून्य SDL_OnWindowDisplayChanged(SDL_Window *window);
बाह्य शून्य SDL_UpdateWindowGrab(SDL_Window *window);
बाह्य bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit);
बाह्य SDL_Window *SDL_GetToplevelForKeyboardFocus(शून्य);

बाह्य bool SDL_ShouldAllowTopmost(शून्य);

बाह्य शून्य SDL_ToggleDragAndDropSupport(शून्य);

बाह्य शून्य SDL_UpdateDesktopBounds(शून्य);

बाह्य SDL_Text_निवेश_Type SDL_Get_Text_निवेश_Type(SDL_PropertiesID props);
बाह्य SDL_Capitalization SDL_Get_Text_निवेश_Capitalization(SDL_PropertiesID props);
बाह्य bool SDL_Get_Text_निवेश_Autocorrect(SDL_PropertiesID props);
बाह्य bool SDL_Get_Text_निवेश_Multiline(SDL_PropertiesID props);

बाह्य शून्य SDL_SendScreenKeyboardShown(शून्य);
बाह्य शून्य SDL_SendScreenKeyboardHidden(शून्य);

#endif // SDL_sysvideo_h_
