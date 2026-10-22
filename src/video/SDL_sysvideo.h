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
#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_sysvideo_h_
#define SDL_sysvideo_h_

#അന്തര്ഭാവ <SDL3/SDL_vulkan.h>

#അന്തര്ഭാവ "SDL_surface_c.h"

// The SDL video driver

തരനിർവചനം ഘടന SDL_VideoDisplay SDL_VideoDisplay;
തരനിർവചനം ഘടന SDL_VideoDevice SDL_VideoDevice;
തരനിർവചനം ഘടന SDL_VideoData SDL_VideoData;
തരനിർവചനം ഘടന SDL_DisplayData SDL_DisplayData;
തരനിർവചനം ഘടന SDL_WindowData SDL_WindowData;

തരനിർവചനം ഘടന
{
    ദശാംശം SDR_white_level;
    ദശാംശം HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
ഘടന SDL_Window
{
    SDL_WindowID id;
    അക്ഷരം *title;
    SDL_Surface *icon;
    പൂർണ്ണസംഖ്യ x, y;
    പൂർണ്ണസംഖ്യ w, h;
    പൂർണ്ണസംഖ്യ min_w, min_h;
    പൂർണ്ണസംഖ്യ max_w, max_h;
    ദശാംശം min_aspect;
    ദശാംശം max_aspect;
    പൂർണ്ണസംഖ്യ last_pixel_w, last_pixel_h;
    SDL_WindowFlags flags;
    SDL_WindowFlags pending_flags;
    ദശാംശം display_scale;
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

    ദശാംശം opacity;

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

    പൂർണ്ണസംഖ്യ safe_inset_ഇടത്;
    പൂർണ്ണസംഖ്യ safe_inset_വലത്;
    പൂർണ്ണസംഖ്യ safe_inset_മുകൾ;
    പൂർണ്ണസംഖ്യ safe_inset_bottom;
    SDL_Rect safe_rect;

    SDL_PropertiesID text_നിവേശം_props;
    bool text_നിവേശം_active;
    SDL_Rect text_നിവേശം_rect;
    പൂർണ്ണസംഖ്യ text_നിവേശം_cursor;

    SDL_Rect mouse_rect;

    SDL_HitTest hit_test;
    ശൂന്യം *hit_test_data;

    SDL_ProgressState progress_state;
    ദശാംശം progress_മൂല്യം;

    SDL_PropertiesID props;

    പൂർണ്ണസംഖ്യ അക്കം_renderers;
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
ഘടന SDL_VideoDisplay
{
    SDL_DisplayID id;
    അക്ഷരം *name;
    പൂർണ്ണസംഖ്യ max_fullscreen_modes;
    പൂർണ്ണസംഖ്യ അക്കം_fullscreen_modes;
    SDL_DisplayMode *fullscreen_modes;
    SDL_DisplayMode desktop_mode;
    സ്ഥിരം SDL_DisplayMode *current_mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    ദശാംശം content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_active;
    SDL_Window *fullscreen_window;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_DisplayData *internal;
};

// Video device flags
തരനിർവചനം എണ്ണൽ
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
തരനിർവചനം എണ്ണൽ
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

തരനിർവചനം എണ്ണൽ
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_FullscreenResult;

ഘടന SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    സ്ഥിരം അക്ഷരം *name;

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
    ശൂന്യം (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    ശൂന്യം (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    ശൂന്യം (*RefreshDisplays)(SDL_VideoDevice *_this);

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
    ശൂന്യം (*SetWindowTitle)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowIcon)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
    bool (*SetWindowPosition)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*SetWindowSize)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*SetWindowMinimumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*SetWindowMaximumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*SetWindowAspectRatio)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GetWindowBordersSize)(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ *മുകൾ, പൂർണ്ണസംഖ്യ *ഇടത്, പൂർണ്ണസംഖ്യ *bottom, പൂർണ്ണസംഖ്യ *വലത്);
    ദശാംശം (*GetWindowContentScale)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*GetWindowSizeInPixels)(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ *w, പൂർണ്ണസംഖ്യ *h);
    bool (*SetWindowOpacity)(SDL_VideoDevice *_this, SDL_Window *window, ദശാംശം opacity);
    bool (*SetWindowParent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
    bool (*SetWindowModal)(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
    ശൂന്യം (*ShowWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*HideWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*RaiseWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*MaximizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*MinimizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*RestoreWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*SetWindowBordered)(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
    ശൂന്യം (*SetWindowResizable)(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
    ശൂന്യം (*Set_Window_Always_On_മുകൾ)(SDL_VideoDevice *_this, SDL_Window *window, bool on_മുകൾ);
    SDL_FullscreenResult (*SetWindowFullscreen)(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    ശൂന്യം *(*GetWindowICCProfile)(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
    SDL_DisplayID (*GetDisplayForWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseRect)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    bool (*SetWindowKeyboardGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    ശൂന്യം (*DestroyWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*CreateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ശൂന്യം **pixels, പൂർണ്ണസംഖ്യ *pitch);
    bool (*SetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ vsync);
    bool (*GetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ *vsync);
    bool (*UpdateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, സ്ഥിരം SDL_Rect *rects, പൂർണ്ണസംഖ്യ numrects);
    ശൂന്യം (*DestroyWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*OnWindowEnter)(SDL_VideoDevice *_this, SDL_Window *window);
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
    bool (*GL_LoadLibrary)(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path);
    SDL_FunctionPointer (*GL_GetProcAddress)(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc);
    ശൂന്യം (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_SetSwapInterval)(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval);
    bool (*GL_GetSwapInterval)(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ *interval);
    bool (*GL_SwapWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    ശൂന്യം (*GL_SetDefaultProfileConfig)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_LoadLibrary)(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path);
    ശൂന്യം (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    അക്ഷരം സ്ഥിരം * സ്ഥിരം *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *എണ്ണം);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_Window *window, VkInstance instance, സ്ഥിരം ഘടന VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
    ശൂന്യം (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, സ്ഥിരം ഘടന VkAllocationCallbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 queueFamilyIndex);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    ശൂന്യം *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    പൂർണ്ണസംഖ്യ (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    ശൂന്യം (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*Start_Text_നിവേശം)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    bool (*Stop_Text_നിവേശം)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Update_Text_നിവേശം_Area)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_Window *window);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    ശൂന്യം (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    ശൂന്യം (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window);
    ശൂന്യം (*Set_Text_നിവേശം_Properties)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);

    // Clipboard
    സ്ഥിരം അക്ഷരം *സ്ഥിരം *(*GetTextMimeTypes)(SDL_VideoDevice *_this, size_t *അക്കം_mime_types);
    bool (*SetClipboardData)(SDL_VideoDevice *_this);
    ശൂന്യം *(*GetClipboardData)(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *mime_type, size_t *size);
    bool (*HasClipboardData)(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*SetClipboardText)(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *text);
    അക്ഷരം *(*GetClipboardText)(SDL_VideoDevice *_this);
    bool (*HasClipboardText)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*SetPrimarySelectionText)(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *text);
    അക്ഷരം *(*GetPrimarySelectionText)(SDL_VideoDevice *_this);
    bool (*HasPrimarySelectionText)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*ShowMessageBox)(SDL_VideoDevice *_this, സ്ഥിരം SDL_MessageBoxData *messageboxdata, പൂർണ്ണസംഖ്യ *buttonID);

    // Hit-testing
    bool (*SetWindowHitTest)(SDL_Window *window, bool enabled);

    // Tell window that app enabled drag'n'drop events
    ശൂന്യം (*AcceptDragAndDrop)(SDL_Window *window, bool accept);

    // Display the system-level window menu
    ശൂന്യം (*ShowWindowSystemMenu)(SDL_Window *window, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    ശൂന്യം *wakeup_window;
    പൂർണ്ണസംഖ്യ അക്കം_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_Window *windows;
    SDL_Window *grabbed_window;
    Uint32 clipboard_sequence;
    SDL_ClipboardDataCallback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    ശൂന്യം *clipboard_userdata;
    അക്ഷരം **clipboard_mime_types;
    size_t അക്കം_clipboard_mime_types;
    അക്ഷരം *primary_selection_text;
    bool setting_display_mode;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    ഘടന
    {
        പൂർണ്ണസംഖ്യ red_size;
        പൂർണ്ണസംഖ്യ green_size;
        പൂർണ്ണസംഖ്യ blue_size;
        പൂർണ്ണസംഖ്യ alpha_size;
        പൂർണ്ണസംഖ്യ depth_size;
        പൂർണ്ണസംഖ്യ buffer_size;
        പൂർണ്ണസംഖ്യ stencil_size;
        പൂർണ്ണസംഖ്യ double_buffer;
        പൂർണ്ണസംഖ്യ accum_red_size;
        പൂർണ്ണസംഖ്യ accum_green_size;
        പൂർണ്ണസംഖ്യ accum_blue_size;
        പൂർണ്ണസംഖ്യ accum_alpha_size;
        പൂർണ്ണസംഖ്യ stereo;
        പൂർണ്ണസംഖ്യ multisamplebuffers;
        പൂർണ്ണസംഖ്യ multisamplesamples;
        പൂർണ്ണസംഖ്യ floatbuffers;
        പൂർണ്ണസംഖ്യ accelerated;
        പൂർണ്ണസംഖ്യ major_version;
        പൂർണ്ണസംഖ്യ minor_version;
        പൂർണ്ണസംഖ്യ flags;
        പൂർണ്ണസംഖ്യ profile_mask;
        പൂർണ്ണസംഖ്യ share_with_current_context;
        പൂർണ്ണസംഖ്യ release_behavior;
        പൂർണ്ണസംഖ്യ reset_notification;
        പൂർണ്ണസംഖ്യ framebuffer_srgb_capable;
        പൂർണ്ണസംഖ്യ no_error;
        പൂർണ്ണസംഖ്യ retained_backing;
        പൂർണ്ണസംഖ്യ egl_platform;
        പൂർണ്ണസംഖ്യ driver_loaded;
        പൂർണ്ണസംഖ്യ HAS_GL_ARB_color_buffer_float;
        അക്ഷരം driver_path[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    ശൂന്യം *egl_attrib_callback_userdata;

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
    ഘടന
    {
        SDL_FunctionPointer vkGetInstanceProcAddr;
        SDL_FunctionPointer vkEnumerateInstanceExtensionProperties;
        പൂർണ്ണസംഖ്യ loader_loaded;
        അക്ഷരം loader_path[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_VideoData *internal;
    ഘടന SDL_GLDriverData *gl_data;

#ifdef SDL_VIDEO_OPENGL_EGL
    ഘടന SDL_EGL_VideoData *egl_data;
#endif

#എങ്കിൽ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    ഘടന SDL_PrivateGLESData *gles_data;
#endif

    /* * * */
    // The function used to dispose of this structure
    ശൂന്യം (*സ്വതന്ത്രം)(SDL_VideoDevice *_this);
};

തരനിർവചനം ഘടന VideoBootStrap
{
    സ്ഥിരം അക്ഷരം *name;
    സ്ഥിരം അക്ഷരം *desc;
    SDL_VideoDevice *(*create)(ശൂന്യം);
    bool (*ShowMessageBox)(സ്ഥിരം SDL_MessageBoxData *messageboxdata, പൂർണ്ണസംഖ്യ *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
ബാഹ്യ VideoBootStrap PRIVATE_bootstrap;
ബാഹ്യ VideoBootStrap COCOA_bootstrap;
ബാഹ്യ VideoBootStrap X11_bootstrap;
ബാഹ്യ VideoBootStrap WINDOWS_bootstrap;
ബാഹ്യ VideoBootStrap HAIKU_bootstrap;
ബാഹ്യ VideoBootStrap UIKIT_bootstrap;
ബാഹ്യ VideoBootStrap Android_bootstrap;
ബാഹ്യ VideoBootStrap OPENHARMONY_bootstrap;
ബാഹ്യ VideoBootStrap PS2_bootstrap;
ബാഹ്യ VideoBootStrap PSP_bootstrap;
ബാഹ്യ VideoBootStrap VITA_bootstrap;
ബാഹ്യ VideoBootStrap RISCOS_bootstrap;
ബാഹ്യ VideoBootStrap N3DS_bootstrap;
ബാഹ്യ VideoBootStrap NGAGE_bootstrap;
ബാഹ്യ VideoBootStrap RPI_bootstrap;
ബാഹ്യ VideoBootStrap KMSDRM_bootstrap;
ബാഹ്യ VideoBootStrap DUMMY_bootstrap;
ബാഹ്യ VideoBootStrap DUMMY_evdev_bootstrap;
ബാഹ്യ VideoBootStrap Wayland_preferred_bootstrap;
ബാഹ്യ VideoBootStrap Wayland_bootstrap;
ബാഹ്യ VideoBootStrap VIVANTE_bootstrap;
ബാഹ്യ VideoBootStrap Emscripten_bootstrap;
ബാഹ്യ VideoBootStrap OFFSCREEN_bootstrap;
ബാഹ്യ VideoBootStrap QNX_bootstrap;
ബാഹ്യ VideoBootStrap OPENVR_bootstrap;
ബാഹ്യ VideoBootStrap DOSVESA_bootstrap;

ബാഹ്യ bool SDL_UninitializedVideo(ശൂന്യം);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
ബാഹ്യ bool SDL_OnVideoThread(ശൂന്യം);
ബാഹ്യ SDL_VideoDevice *SDL_GetVideoDevice(ശൂന്യം);
ബാഹ്യ ശൂന്യം SDL_SetSystemTheme(SDL_SystemTheme theme);
ബാഹ്യ SDL_DisplayID SDL_AddBasicVideoDisplay(സ്ഥിരം SDL_DisplayMode *desktop_mode);
ബാഹ്യ SDL_DisplayID SDL_AddVideoDisplay(സ്ഥിരം SDL_VideoDisplay *display, bool send_event);
ബാഹ്യ ശൂന്യം SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
ബാഹ്യ bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, സ്ഥിരം SDL_DisplayMode *mode);
ബാഹ്യ ശൂന്യം SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
ബാഹ്യ ശൂന്യം SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, സ്ഥിരം SDL_DisplayMode *mode);
ബാഹ്യ ശൂന്യം SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, സ്ഥിരം SDL_DisplayMode *mode);
ബാഹ്യ ശൂന്യം SDL_SetDisplayContentScale(SDL_VideoDisplay *display, ദശാംശം scale);
ബാഹ്യ ശൂന്യം SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, സ്ഥിരം SDL_HDROutputProperties *HDR);
ബാഹ്യ bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode);
ബാഹ്യ SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
ബാഹ്യ SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window);
ബാഹ്യ SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window);
ബാഹ്യ SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window);
ബാഹ്യ പൂർണ്ണസംഖ്യ SDL_GetDisplayIndex(SDL_DisplayID displayID);
ബാഹ്യ SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID display);
ബാഹ്യ SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window);
ബാഹ്യ പൂർണ്ണസംഖ്യ SDL_Get_Message_Box_എണ്ണം(ശൂന്യം);
ബാഹ്യ ശൂന്യം SDL_SetWindowHDRProperties(SDL_Window *window, സ്ഥിരം SDL_HDROutputProperties *HDR, bool send_event);
ബാഹ്യ ശൂന്യം SDL_SetWindowSafeAreaInsets(SDL_Window *window, പൂർണ്ണസംഖ്യ ഇടത്, പൂർണ്ണസംഖ്യ വലത്, പൂർണ്ണസംഖ്യ മുകൾ, പൂർണ്ണസംഖ്യ bottom);

ബാഹ്യ ശൂന്യം SDL_GL_DeduceMaxSupportedESProfile(പൂർണ്ണസംഖ്യ *major, പൂർണ്ണസംഖ്യ *minor);

ബാഹ്യ bool SDL_RecreateWindow(SDL_Window *window, SDL_WindowFlags flags);
ബാഹ്യ bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags);
ബാഹ്യ bool SDL_HasWindows(ശൂന്യം);
ബാഹ്യ ശൂന്യം SDL_RelativeToGlobalForWindow(SDL_Window *window, പൂർണ്ണസംഖ്യ rel_x, പൂർണ്ണസംഖ്യ rel_y, പൂർണ്ണസംഖ്യ *abs_x, പൂർണ്ണസംഖ്യ *abs_y);
ബാഹ്യ ശൂന്യം SDL_GlobalToRelativeForWindow(SDL_Window *window, പൂർണ്ണസംഖ്യ abs_x, പൂർണ്ണസംഖ്യ abs_y, പൂർണ്ണസംഖ്യ *rel_x, പൂർണ്ണസംഖ്യ *rel_y);
ബാഹ്യ bool SDL_ShouldFocusPopup(SDL_Window *window);
ബാഹ്യ bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus);

ബാഹ്യ ശൂന്യം SDL_OnDisplayAdded(SDL_VideoDisplay *display);
ബാഹ്യ ശൂന്യം SDL_OnDisplayMoved(SDL_VideoDisplay *display);
ബാഹ്യ ശൂന്യം SDL_OnWindowShown(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowHidden(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowMoved(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowResized(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_CheckWindowPixelSizeChanged(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowPixelSizeChanged(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowLiveResizeUpdate(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowMinimized(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowMaximized(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowRestored(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowEnter(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowLeave(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowFocusGained(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowFocusLost(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_OnWindowDisplayChanged(SDL_Window *window);
ബാഹ്യ ശൂന്യം SDL_UpdateWindowGrab(SDL_Window *window);
ബാഹ്യ bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit);
ബാഹ്യ SDL_Window *SDL_GetToplevelForKeyboardFocus(ശൂന്യം);

ബാഹ്യ bool SDL_ShouldAllowTopmost(ശൂന്യം);

ബാഹ്യ ശൂന്യം SDL_ToggleDragAndDropSupport(ശൂന്യം);

ബാഹ്യ ശൂന്യം SDL_UpdateDesktopBounds(ശൂന്യം);

ബാഹ്യ SDL_Text_നിവേശം_Type SDL_Get_Text_നിവേശം_Type(SDL_PropertiesID props);
ബാഹ്യ SDL_Capitalization SDL_Get_Text_നിവേശം_Capitalization(SDL_PropertiesID props);
ബാഹ്യ bool SDL_Get_Text_നിവേശം_Autocorrect(SDL_PropertiesID props);
ബാഹ്യ bool SDL_Get_Text_നിവേശം_Multiline(SDL_PropertiesID props);

ബാഹ്യ ശൂന്യം SDL_SendScreenKeyboardShown(ശൂന്യം);
ബാഹ്യ ശൂന്യം SDL_SendScreenKeyboardHidden(ശൂന്യം);

#endif // SDL_sysvideo_h_
