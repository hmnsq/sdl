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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_sysvideo_h_
#define SDL_sysvideo_h_

#ಅನ್ತರ್ಭಾವ <SDL3/SDL_vulkan.h>

#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"

// The SDL video driver

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_VideoDisplay SDL_VideoDisplay;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_VideoDevice SDL_VideoDevice;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_VideoData SDL_VideoData;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_DisplayData SDL_DisplayData;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_WindowData SDL_WindowData;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಭಿನ್ನ SDR_white_level;
    ಭಿನ್ನ HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
ಸಂರಚನಾ SDL_Window
{
    SDL_WindowID id;
    ವರ್ಣ *title;
    SDL_Surface *icon;
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಪೂರ್ಣಾಙ್ಕ w, h;
    ಪೂರ್ಣಾಙ್ಕ min_w, min_h;
    ಪೂರ್ಣಾಙ್ಕ max_w, max_h;
    ಭಿನ್ನ min_aspect;
    ಭಿನ್ನ max_aspect;
    ಪೂರ್ಣಾಙ್ಕ last_pixel_w, last_pixel_h;
    SDL_WindowFlags flags;
    SDL_WindowFlags pending_flags;
    ಭಿನ್ನ display_scale;
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

    ಭಿನ್ನ opacity;

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

    ಪೂರ್ಣಾಙ್ಕ safe_inset_ಎಡ;
    ಪೂರ್ಣಾಙ್ಕ safe_inset_ಬಲ;
    ಪೂರ್ಣಾಙ್ಕ safe_inset_ತುದಿ;
    ಪೂರ್ಣಾಙ್ಕ safe_inset_bottom;
    SDL_Rect safe_rect;

    SDL_PropertiesID text_ಒಳಹರಿವು_props;
    bool text_ಒಳಹರಿವು_active;
    SDL_Rect text_ಒಳಹರಿವು_rect;
    ಪೂರ್ಣಾಙ್ಕ text_ಒಳಹರಿವು_cursor;

    SDL_Rect mouse_rect;

    SDL_HitTest hit_test;
    ಶೂನ್ಯ *hit_test_data;

    SDL_ProgressState progress_state;
    ಭಿನ್ನ progress_ಮೌಲ್ಯ;

    SDL_PropertiesID props;

    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_renderers;
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
ಸಂರಚನಾ SDL_VideoDisplay
{
    SDL_DisplayID id;
    ವರ್ಣ *name;
    ಪೂರ್ಣಾಙ್ಕ max_fullscreen_modes;
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_fullscreen_modes;
    SDL_DisplayMode *fullscreen_modes;
    SDL_DisplayMode desktop_mode;
    ಧ್ರುವ SDL_DisplayMode *current_mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    ಭಿನ್ನ content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_active;
    SDL_Window *fullscreen_window;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_DisplayData *internal;
};

// Video device flags
ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
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
ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_FullscreenResult;

ಸಂರಚನಾ SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    ಧ್ರುವ ವರ್ಣ *name;

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
    ಶೂನ್ಯ (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    ಶೂನ್ಯ (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    ಶೂನ್ಯ (*RefreshDisplays)(SDL_VideoDevice *_this);

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
    ಶೂನ್ಯ (*SetWindowTitle)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowIcon)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
    bool (*SetWindowPosition)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*SetWindowSize)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*SetWindowMinimumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*SetWindowMaximumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*SetWindowAspectRatio)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GetWindowBordersSize)(SDL_VideoDevice *_this, SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *ತುದಿ, ಪೂರ್ಣಾಙ್ಕ *ಎಡ, ಪೂರ್ಣಾಙ್ಕ *bottom, ಪೂರ್ಣಾಙ್ಕ *ಬಲ);
    ಭಿನ್ನ (*GetWindowContentScale)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*GetWindowSizeInPixels)(SDL_VideoDevice *_this, SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *w, ಪೂರ್ಣಾಙ್ಕ *h);
    bool (*SetWindowOpacity)(SDL_VideoDevice *_this, SDL_Window *window, ಭಿನ್ನ opacity);
    bool (*SetWindowParent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
    bool (*SetWindowModal)(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
    ಶೂನ್ಯ (*ShowWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*HideWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*RaiseWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*MaximizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*MinimizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*RestoreWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*SetWindowBordered)(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
    ಶೂನ್ಯ (*SetWindowResizable)(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
    ಶೂನ್ಯ (*Set_Window_Always_On_ತುದಿ)(SDL_VideoDevice *_this, SDL_Window *window, bool on_ತುದಿ);
    SDL_FullscreenResult (*SetWindowFullscreen)(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    ಶೂನ್ಯ *(*GetWindowICCProfile)(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
    SDL_DisplayID (*GetDisplayForWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseRect)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    bool (*SetWindowKeyboardGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    ಶೂನ್ಯ (*DestroyWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*CreateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಙ್ಕ *pitch);
    bool (*SetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ vsync);
    bool (*GetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *vsync);
    bool (*UpdateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, ಧ್ರುವ SDL_Rect *rects, ಪೂರ್ಣಾಙ್ಕ numrects);
    ಶೂನ್ಯ (*DestroyWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*OnWindowEnter)(SDL_VideoDevice *_this, SDL_Window *window);
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
    bool (*GL_LoadLibrary)(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path);
    SDL_FunctionPointer (*GL_GetProcAddress)(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *proc);
    ಶೂನ್ಯ (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_SetSwapInterval)(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ interval);
    bool (*GL_GetSwapInterval)(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ *interval);
    bool (*GL_SwapWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    ಶೂನ್ಯ (*GL_SetDefaultProfileConfig)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_LoadLibrary)(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path);
    ಶೂನ್ಯ (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    ವರ್ಣ ಧ್ರುವ * ಧ್ರುವ *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *ಎಣಿಕೆ);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_Window *window, VkInstance instance, ಧ್ರುವ ಸಂರಚನಾ VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
    ಶೂನ್ಯ (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ಧ್ರುವ ಸಂರಚನಾ VkAllocationCallbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 queueFamilyIndex);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    ಶೂನ್ಯ *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    ಪೂರ್ಣಾಙ್ಕ (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    ಶೂನ್ಯ (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*Start_Text_ಒಳಹರಿವು)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    bool (*Stop_Text_ಒಳಹರಿವು)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Update_Text_ಒಳಹರಿವು_Area)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_Window *window);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    ಶೂನ್ಯ (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    ಶೂನ್ಯ (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window);
    ಶೂನ್ಯ (*Set_Text_ಒಳಹರಿವು_Properties)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);

    // Clipboard
    ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *(*GetTextMimeTypes)(SDL_VideoDevice *_this, size_t *ಅಂಕೆ_mime_types);
    bool (*SetClipboardData)(SDL_VideoDevice *_this);
    ಶೂನ್ಯ *(*GetClipboardData)(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *size);
    bool (*HasClipboardData)(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*SetClipboardText)(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *text);
    ವರ್ಣ *(*GetClipboardText)(SDL_VideoDevice *_this);
    bool (*HasClipboardText)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*SetPrimarySelectionText)(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *text);
    ವರ್ಣ *(*GetPrimarySelectionText)(SDL_VideoDevice *_this);
    bool (*HasPrimarySelectionText)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*ShowMessageBox)(SDL_VideoDevice *_this, ಧ್ರುವ SDL_MessageBoxData *messageboxdata, ಪೂರ್ಣಾಙ್ಕ *buttonID);

    // Hit-testing
    bool (*SetWindowHitTest)(SDL_Window *window, bool enabled);

    // Tell window that app enabled drag'n'drop events
    ಶೂನ್ಯ (*AcceptDragAndDrop)(SDL_Window *window, bool accept);

    // Display the system-level window menu
    ಶೂನ್ಯ (*ShowWindowSystemMenu)(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    ಶೂನ್ಯ *wakeup_window;
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_Window *windows;
    SDL_Window *grabbed_window;
    Uint32 clipboard_sequence;
    SDL_ClipboardDataCallback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    ಶೂನ್ಯ *clipboard_userdata;
    ವರ್ಣ **clipboard_mime_types;
    size_t ಅಂಕೆ_clipboard_mime_types;
    ವರ್ಣ *primary_selection_text;
    bool setting_display_mode;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    ಸಂರಚನಾ
    {
        ಪೂರ್ಣಾಙ್ಕ red_size;
        ಪೂರ್ಣಾಙ್ಕ green_size;
        ಪೂರ್ಣಾಙ್ಕ blue_size;
        ಪೂರ್ಣಾಙ್ಕ alpha_size;
        ಪೂರ್ಣಾಙ್ಕ depth_size;
        ಪೂರ್ಣಾಙ್ಕ buffer_size;
        ಪೂರ್ಣಾಙ್ಕ stencil_size;
        ಪೂರ್ಣಾಙ್ಕ double_buffer;
        ಪೂರ್ಣಾಙ್ಕ accum_red_size;
        ಪೂರ್ಣಾಙ್ಕ accum_green_size;
        ಪೂರ್ಣಾಙ್ಕ accum_blue_size;
        ಪೂರ್ಣಾಙ್ಕ accum_alpha_size;
        ಪೂರ್ಣಾಙ್ಕ stereo;
        ಪೂರ್ಣಾಙ್ಕ multisamplebuffers;
        ಪೂರ್ಣಾಙ್ಕ multisamplesamples;
        ಪೂರ್ಣಾಙ್ಕ floatbuffers;
        ಪೂರ್ಣಾಙ್ಕ accelerated;
        ಪೂರ್ಣಾಙ್ಕ major_version;
        ಪೂರ್ಣಾಙ್ಕ minor_version;
        ಪೂರ್ಣಾಙ್ಕ flags;
        ಪೂರ್ಣಾಙ್ಕ profile_mask;
        ಪೂರ್ಣಾಙ್ಕ share_with_current_context;
        ಪೂರ್ಣಾಙ್ಕ release_behavior;
        ಪೂರ್ಣಾಙ್ಕ reset_notification;
        ಪೂರ್ಣಾಙ್ಕ framebuffer_srgb_capable;
        ಪೂರ್ಣಾಙ್ಕ no_error;
        ಪೂರ್ಣಾಙ್ಕ retained_backing;
        ಪೂರ್ಣಾಙ್ಕ egl_platform;
        ಪೂರ್ಣಾಙ್ಕ driver_loaded;
        ಪೂರ್ಣಾಙ್ಕ HAS_GL_ARB_color_buffer_float;
        ವರ್ಣ driver_path[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    ಶೂನ್ಯ *egl_attrib_callback_userdata;

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
    ಸಂರಚನಾ
    {
        SDL_FunctionPointer vkGetInstanceProcAddr;
        SDL_FunctionPointer vkEnumerateInstanceExtensionProperties;
        ಪೂರ್ಣಾಙ್ಕ loader_loaded;
        ವರ್ಣ loader_path[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_VideoData *internal;
    ಸಂರಚನಾ SDL_GLDriverData *gl_data;

#ifdef SDL_VIDEO_OPENGL_EGL
    ಸಂರಚನಾ SDL_EGL_VideoData *egl_data;
#endif

#ಯದಿ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    ಸಂರಚನಾ SDL_PrivateGLESData *gles_data;
#endif

    /* * * */
    // The function used to dispose of this structure
    ಶೂನ್ಯ (*ಮುಕ್ತ)(SDL_VideoDevice *_this);
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VideoBootStrap
{
    ಧ್ರುವ ವರ್ಣ *name;
    ಧ್ರುವ ವರ್ಣ *desc;
    SDL_VideoDevice *(*create)(ಶೂನ್ಯ);
    bool (*ShowMessageBox)(ಧ್ರುವ SDL_MessageBoxData *messageboxdata, ಪೂರ್ಣಾಙ್ಕ *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
ಬಾಹ್ಯ VideoBootStrap PRIVATE_bootstrap;
ಬಾಹ್ಯ VideoBootStrap COCOA_bootstrap;
ಬಾಹ್ಯ VideoBootStrap X11_bootstrap;
ಬಾಹ್ಯ VideoBootStrap WINDOWS_bootstrap;
ಬಾಹ್ಯ VideoBootStrap HAIKU_bootstrap;
ಬಾಹ್ಯ VideoBootStrap UIKIT_bootstrap;
ಬಾಹ್ಯ VideoBootStrap Android_bootstrap;
ಬಾಹ್ಯ VideoBootStrap OPENHARMONY_bootstrap;
ಬಾಹ್ಯ VideoBootStrap PS2_bootstrap;
ಬಾಹ್ಯ VideoBootStrap PSP_bootstrap;
ಬಾಹ್ಯ VideoBootStrap VITA_bootstrap;
ಬಾಹ್ಯ VideoBootStrap RISCOS_bootstrap;
ಬಾಹ್ಯ VideoBootStrap N3DS_bootstrap;
ಬಾಹ್ಯ VideoBootStrap NGAGE_bootstrap;
ಬಾಹ್ಯ VideoBootStrap RPI_bootstrap;
ಬಾಹ್ಯ VideoBootStrap KMSDRM_bootstrap;
ಬಾಹ್ಯ VideoBootStrap DUMMY_bootstrap;
ಬಾಹ್ಯ VideoBootStrap DUMMY_evdev_bootstrap;
ಬಾಹ್ಯ VideoBootStrap Wayland_preferred_bootstrap;
ಬಾಹ್ಯ VideoBootStrap Wayland_bootstrap;
ಬಾಹ್ಯ VideoBootStrap VIVANTE_bootstrap;
ಬಾಹ್ಯ VideoBootStrap Emscripten_bootstrap;
ಬಾಹ್ಯ VideoBootStrap OFFSCREEN_bootstrap;
ಬಾಹ್ಯ VideoBootStrap QNX_bootstrap;
ಬಾಹ್ಯ VideoBootStrap OPENVR_bootstrap;
ಬಾಹ್ಯ VideoBootStrap DOSVESA_bootstrap;

ಬಾಹ್ಯ bool SDL_UninitializedVideo(ಶೂನ್ಯ);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
ಬಾಹ್ಯ bool SDL_OnVideoThread(ಶೂನ್ಯ);
ಬಾಹ್ಯ SDL_VideoDevice *SDL_GetVideoDevice(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_SetSystemTheme(SDL_SystemTheme theme);
ಬಾಹ್ಯ SDL_DisplayID SDL_AddBasicVideoDisplay(ಧ್ರುವ SDL_DisplayMode *desktop_mode);
ಬಾಹ್ಯ SDL_DisplayID SDL_AddVideoDisplay(ಧ್ರುವ SDL_VideoDisplay *display, bool send_event);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
ಬಾಹ್ಯ bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ಧ್ರುವ SDL_DisplayMode *mode);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ಧ್ರುವ SDL_DisplayMode *mode);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ಧ್ರುವ SDL_DisplayMode *mode);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_SetDisplayContentScale(SDL_VideoDisplay *display, ಭಿನ್ನ scale);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ಧ್ರುವ SDL_HDROutputProperties *HDR);
ಬಾಹ್ಯ bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode);
ಬಾಹ್ಯ SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
ಬಾಹ್ಯ SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window);
ಬಾಹ್ಯ SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window);
ಬಾಹ್ಯ SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window);
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ SDL_GetDisplayIndex(SDL_DisplayID displayID);
ಬಾಹ್ಯ SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID display);
ಬಾಹ್ಯ SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window);
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ SDL_Get_Message_Box_ಎಣಿಕೆ(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_SetWindowHDRProperties(SDL_Window *window, ಧ್ರುವ SDL_HDROutputProperties *HDR, bool send_event);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_SetWindowSafeAreaInsets(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ ಎಡ, ಪೂರ್ಣಾಙ್ಕ ಬಲ, ಪೂರ್ಣಾಙ್ಕ ತುದಿ, ಪೂರ್ಣಾಙ್ಕ bottom);

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_GL_DeduceMaxSupportedESProfile(ಪೂರ್ಣಾಙ್ಕ *major, ಪೂರ್ಣಾಙ್ಕ *minor);

ಬಾಹ್ಯ bool SDL_RecreateWindow(SDL_Window *window, SDL_WindowFlags flags);
ಬಾಹ್ಯ bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags);
ಬಾಹ್ಯ bool SDL_HasWindows(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_RelativeToGlobalForWindow(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ rel_x, ಪೂರ್ಣಾಙ್ಕ rel_y, ಪೂರ್ಣಾಙ್ಕ *abs_x, ಪೂರ್ಣಾಙ್ಕ *abs_y);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_GlobalToRelativeForWindow(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ abs_x, ಪೂರ್ಣಾಙ್ಕ abs_y, ಪೂರ್ಣಾಙ್ಕ *rel_x, ಪೂರ್ಣಾಙ್ಕ *rel_y);
ಬಾಹ್ಯ bool SDL_ShouldFocusPopup(SDL_Window *window);
ಬಾಹ್ಯ bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus);

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnDisplayAdded(SDL_VideoDisplay *display);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnDisplayMoved(SDL_VideoDisplay *display);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowShown(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowHidden(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowMoved(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowResized(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_CheckWindowPixelSizeChanged(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowPixelSizeChanged(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowLiveResizeUpdate(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowMinimized(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowMaximized(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowRestored(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowEnter(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowLeave(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowFocusGained(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowFocusLost(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnWindowDisplayChanged(SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_UpdateWindowGrab(SDL_Window *window);
ಬಾಹ್ಯ bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit);
ಬಾಹ್ಯ SDL_Window *SDL_GetToplevelForKeyboardFocus(ಶೂನ್ಯ);

ಬಾಹ್ಯ bool SDL_ShouldAllowTopmost(ಶೂನ್ಯ);

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ToggleDragAndDropSupport(ಶೂನ್ಯ);

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_UpdateDesktopBounds(ಶೂನ್ಯ);

ಬಾಹ್ಯ SDL_Text_ಒಳಹರಿವು_Type SDL_Get_Text_ಒಳಹರಿವು_Type(SDL_PropertiesID props);
ಬಾಹ್ಯ SDL_Capitalization SDL_Get_Text_ಒಳಹರಿವು_Capitalization(SDL_PropertiesID props);
ಬಾಹ್ಯ bool SDL_Get_Text_ಒಳಹರಿವು_Autocorrect(SDL_PropertiesID props);
ಬಾಹ್ಯ bool SDL_Get_Text_ಒಳಹರಿವು_Multiline(SDL_PropertiesID props);

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_SendScreenKeyboardShown(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_SendScreenKeyboardHidden(ಶೂನ್ಯ);

#endif // SDL_sysvideo_h_
