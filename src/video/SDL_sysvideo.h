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
#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_sysvideo_h_
#define SDL_sysvideo_h_

#அந்தர்பாவ <SDL3/SDL_vulkan.h>

#அந்தர்பாவ "SDL_surface_c.h"

// The SDL video driver

வகைவரை கட்டமைப்பு SDL_VideoDisplay SDL_VideoDisplay;
வகைவரை கட்டமைப்பு SDL_VideoDevice SDL_VideoDevice;
வகைவரை கட்டமைப்பு SDL_VideoData SDL_VideoData;
வகைவரை கட்டமைப்பு SDL_DisplayData SDL_DisplayData;
வகைவரை கட்டமைப்பு SDL_WindowData SDL_WindowData;

வகைவரை கட்டமைப்பு
{
    தசம SDR_white_level;
    தசம HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
கட்டமைப்பு SDL_Window
{
    SDL_WindowID id;
    எழுத்து *title;
    SDL_Surface *icon;
    முழு x, y;
    முழு w, h;
    முழு min_w, min_h;
    முழு max_w, max_h;
    தசம min_aspect;
    தசம max_aspect;
    முழு last_pixel_w, last_pixel_h;
    SDL_WindowFlags flags;
    SDL_WindowFlags pending_flags;
    தசம display_scale;
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

    தசம opacity;

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

    முழு safe_inset_இடது;
    முழு safe_inset_வலது;
    முழு safe_inset_உச்சி;
    முழு safe_inset_bottom;
    SDL_Rect safe_rect;

    SDL_PropertiesID text_உள்ளீடு_props;
    bool text_உள்ளீடு_active;
    SDL_Rect text_உள்ளீடு_rect;
    முழு text_உள்ளீடு_cursor;

    SDL_Rect mouse_rect;

    SDL_HitTest hit_test;
    வெறுமை *hit_test_data;

    SDL_ProgressState progress_state;
    தசம progress_மதிப்பு;

    SDL_PropertiesID props;

    முழு இலக்கம்_renderers;
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
கட்டமைப்பு SDL_VideoDisplay
{
    SDL_DisplayID id;
    எழுத்து *name;
    முழு max_fullscreen_modes;
    முழு இலக்கம்_fullscreen_modes;
    SDL_DisplayMode *fullscreen_modes;
    SDL_DisplayMode desktop_mode;
    மாறிலி SDL_DisplayMode *current_mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    தசம content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_active;
    SDL_Window *fullscreen_window;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_DisplayData *internal;
};

// Video device flags
வகைவரை எண்ணிக்கை
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
வகைவரை எண்ணிக்கை
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

வகைவரை எண்ணிக்கை
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_FullscreenResult;

கட்டமைப்பு SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    மாறிலி எழுத்து *name;

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
    வெறுமை (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    வெறுமை (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    வெறுமை (*RefreshDisplays)(SDL_VideoDevice *_this);

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
    வெறுமை (*SetWindowTitle)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowIcon)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
    bool (*SetWindowPosition)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*SetWindowSize)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*SetWindowMinimumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*SetWindowMaximumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*SetWindowAspectRatio)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GetWindowBordersSize)(SDL_VideoDevice *_this, SDL_Window *window, முழு *உச்சி, முழு *இடது, முழு *bottom, முழு *வலது);
    தசம (*GetWindowContentScale)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*GetWindowSizeInPixels)(SDL_VideoDevice *_this, SDL_Window *window, முழு *w, முழு *h);
    bool (*SetWindowOpacity)(SDL_VideoDevice *_this, SDL_Window *window, தசம opacity);
    bool (*SetWindowParent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
    bool (*SetWindowModal)(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
    வெறுமை (*ShowWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*HideWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*RaiseWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*MaximizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*MinimizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*RestoreWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*SetWindowBordered)(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
    வெறுமை (*SetWindowResizable)(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
    வெறுமை (*Set_Window_Always_On_உச்சி)(SDL_VideoDevice *_this, SDL_Window *window, bool on_உச்சி);
    SDL_FullscreenResult (*SetWindowFullscreen)(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    வெறுமை *(*GetWindowICCProfile)(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
    SDL_DisplayID (*GetDisplayForWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseRect)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    bool (*SetWindowKeyboardGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    வெறுமை (*DestroyWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*CreateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, வெறுமை **pixels, முழு *pitch);
    bool (*SetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, முழு vsync);
    bool (*GetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, முழு *vsync);
    bool (*UpdateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, மாறிலி SDL_Rect *rects, முழு numrects);
    வெறுமை (*DestroyWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*OnWindowEnter)(SDL_VideoDevice *_this, SDL_Window *window);
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
    bool (*GL_LoadLibrary)(SDL_VideoDevice *_this, மாறிலி எழுத்து *path);
    SDL_FunctionPointer (*GL_GetProcAddress)(SDL_VideoDevice *_this, மாறிலி எழுத்து *proc);
    வெறுமை (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_SetSwapInterval)(SDL_VideoDevice *_this, முழு interval);
    bool (*GL_GetSwapInterval)(SDL_VideoDevice *_this, முழு *interval);
    bool (*GL_SwapWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    வெறுமை (*GL_SetDefaultProfileConfig)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_LoadLibrary)(SDL_VideoDevice *_this, மாறிலி எழுத்து *path);
    வெறுமை (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    எழுத்து மாறிலி * மாறிலி *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *மொத்தம்);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_Window *window, VkInstance instance, மாறிலி கட்டமைப்பு VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
    வெறுமை (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, மாறிலி கட்டமைப்பு VkAllocationCallbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 queueFamilyIndex);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    வெறுமை *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    முழு (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    வெறுமை (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*Start_Text_உள்ளீடு)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    bool (*Stop_Text_உள்ளீடு)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Update_Text_உள்ளீடு_Area)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_Window *window);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    வெறுமை (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    வெறுமை (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window);
    வெறுமை (*Set_Text_உள்ளீடு_Properties)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);

    // Clipboard
    மாறிலி எழுத்து *மாறிலி *(*GetTextMimeTypes)(SDL_VideoDevice *_this, size_t *இலக்கம்_mime_types);
    bool (*SetClipboardData)(SDL_VideoDevice *_this);
    வெறுமை *(*GetClipboardData)(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type, size_t *size);
    bool (*HasClipboardData)(SDL_VideoDevice *_this, மாறிலி எழுத்து *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*SetClipboardText)(SDL_VideoDevice *_this, மாறிலி எழுத்து *text);
    எழுத்து *(*GetClipboardText)(SDL_VideoDevice *_this);
    bool (*HasClipboardText)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*SetPrimarySelectionText)(SDL_VideoDevice *_this, மாறிலி எழுத்து *text);
    எழுத்து *(*GetPrimarySelectionText)(SDL_VideoDevice *_this);
    bool (*HasPrimarySelectionText)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*ShowMessageBox)(SDL_VideoDevice *_this, மாறிலி SDL_MessageBoxData *messageboxdata, முழு *buttonID);

    // Hit-testing
    bool (*SetWindowHitTest)(SDL_Window *window, bool enabled);

    // Tell window that app enabled drag'n'drop events
    வெறுமை (*AcceptDragAndDrop)(SDL_Window *window, bool accept);

    // Display the system-level window menu
    வெறுமை (*ShowWindowSystemMenu)(SDL_Window *window, முழு x, முழு y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    வெறுமை *wakeup_window;
    முழு இலக்கம்_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_Window *windows;
    SDL_Window *grabbed_window;
    Uint32 clipboard_sequence;
    SDL_ClipboardDataCallback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    வெறுமை *clipboard_userdata;
    எழுத்து **clipboard_mime_types;
    size_t இலக்கம்_clipboard_mime_types;
    எழுத்து *primary_selection_text;
    bool setting_display_mode;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    கட்டமைப்பு
    {
        முழு red_size;
        முழு green_size;
        முழு blue_size;
        முழு alpha_size;
        முழு depth_size;
        முழு buffer_size;
        முழு stencil_size;
        முழு double_buffer;
        முழு accum_red_size;
        முழு accum_green_size;
        முழு accum_blue_size;
        முழு accum_alpha_size;
        முழு stereo;
        முழு multisamplebuffers;
        முழு multisamplesamples;
        முழு floatbuffers;
        முழு accelerated;
        முழு major_version;
        முழு minor_version;
        முழு flags;
        முழு profile_mask;
        முழு share_with_current_context;
        முழு release_behavior;
        முழு reset_notification;
        முழு framebuffer_srgb_capable;
        முழு no_error;
        முழு retained_backing;
        முழு egl_platform;
        முழு driver_loaded;
        முழு HAS_GL_ARB_color_buffer_float;
        எழுத்து driver_path[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    வெறுமை *egl_attrib_callback_userdata;

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
    கட்டமைப்பு
    {
        SDL_FunctionPointer vkGetInstanceProcAddr;
        SDL_FunctionPointer vkEnumerateInstanceExtensionProperties;
        முழு loader_loaded;
        எழுத்து loader_path[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_VideoData *internal;
    கட்டமைப்பு SDL_GLDriverData *gl_data;

#ifdef SDL_VIDEO_OPENGL_EGL
    கட்டமைப்பு SDL_EGL_VideoData *egl_data;
#endif

#எனில் defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    கட்டமைப்பு SDL_PrivateGLESData *gles_data;
#endif

    /* * * */
    // The function used to dispose of this structure
    வெறுமை (*விடுவி)(SDL_VideoDevice *_this);
};

வகைவரை கட்டமைப்பு VideoBootStrap
{
    மாறிலி எழுத்து *name;
    மாறிலி எழுத்து *desc;
    SDL_VideoDevice *(*create)(வெறுமை);
    bool (*ShowMessageBox)(மாறிலி SDL_MessageBoxData *messageboxdata, முழு *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
வெளி VideoBootStrap PRIVATE_bootstrap;
வெளி VideoBootStrap COCOA_bootstrap;
வெளி VideoBootStrap X11_bootstrap;
வெளி VideoBootStrap WINDOWS_bootstrap;
வெளி VideoBootStrap HAIKU_bootstrap;
வெளி VideoBootStrap UIKIT_bootstrap;
வெளி VideoBootStrap Android_bootstrap;
வெளி VideoBootStrap OPENHARMONY_bootstrap;
வெளி VideoBootStrap PS2_bootstrap;
வெளி VideoBootStrap PSP_bootstrap;
வெளி VideoBootStrap VITA_bootstrap;
வெளி VideoBootStrap RISCOS_bootstrap;
வெளி VideoBootStrap N3DS_bootstrap;
வெளி VideoBootStrap NGAGE_bootstrap;
வெளி VideoBootStrap RPI_bootstrap;
வெளி VideoBootStrap KMSDRM_bootstrap;
வெளி VideoBootStrap DUMMY_bootstrap;
வெளி VideoBootStrap DUMMY_evdev_bootstrap;
வெளி VideoBootStrap Wayland_preferred_bootstrap;
வெளி VideoBootStrap Wayland_bootstrap;
வெளி VideoBootStrap VIVANTE_bootstrap;
வெளி VideoBootStrap Emscripten_bootstrap;
வெளி VideoBootStrap OFFSCREEN_bootstrap;
வெளி VideoBootStrap QNX_bootstrap;
வெளி VideoBootStrap OPENVR_bootstrap;
வெளி VideoBootStrap DOSVESA_bootstrap;

வெளி bool SDL_UninitializedVideo(வெறுமை);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
வெளி bool SDL_OnVideoThread(வெறுமை);
வெளி SDL_VideoDevice *SDL_GetVideoDevice(வெறுமை);
வெளி வெறுமை SDL_SetSystemTheme(SDL_SystemTheme theme);
வெளி SDL_DisplayID SDL_AddBasicVideoDisplay(மாறிலி SDL_DisplayMode *desktop_mode);
வெளி SDL_DisplayID SDL_AddVideoDisplay(மாறிலி SDL_VideoDisplay *display, bool send_event);
வெளி வெறுமை SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
வெளி bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, மாறிலி SDL_DisplayMode *mode);
வெளி வெறுமை SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
வெளி வெறுமை SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, மாறிலி SDL_DisplayMode *mode);
வெளி வெறுமை SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, மாறிலி SDL_DisplayMode *mode);
வெளி வெறுமை SDL_SetDisplayContentScale(SDL_VideoDisplay *display, தசம scale);
வெளி வெறுமை SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, மாறிலி SDL_HDROutputProperties *HDR);
வெளி bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode);
வெளி SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
வெளி SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window);
வெளி SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window);
வெளி SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window);
வெளி முழு SDL_GetDisplayIndex(SDL_DisplayID displayID);
வெளி SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID display);
வெளி SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window);
வெளி முழு SDL_Get_Message_Box_மொத்தம்(வெறுமை);
வெளி வெறுமை SDL_SetWindowHDRProperties(SDL_Window *window, மாறிலி SDL_HDROutputProperties *HDR, bool send_event);
வெளி வெறுமை SDL_SetWindowSafeAreaInsets(SDL_Window *window, முழு இடது, முழு வலது, முழு உச்சி, முழு bottom);

வெளி வெறுமை SDL_GL_DeduceMaxSupportedESProfile(முழு *major, முழு *minor);

வெளி bool SDL_RecreateWindow(SDL_Window *window, SDL_WindowFlags flags);
வெளி bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags);
வெளி bool SDL_HasWindows(வெறுமை);
வெளி வெறுமை SDL_RelativeToGlobalForWindow(SDL_Window *window, முழு rel_x, முழு rel_y, முழு *abs_x, முழு *abs_y);
வெளி வெறுமை SDL_GlobalToRelativeForWindow(SDL_Window *window, முழு abs_x, முழு abs_y, முழு *rel_x, முழு *rel_y);
வெளி bool SDL_ShouldFocusPopup(SDL_Window *window);
வெளி bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus);

வெளி வெறுமை SDL_OnDisplayAdded(SDL_VideoDisplay *display);
வெளி வெறுமை SDL_OnDisplayMoved(SDL_VideoDisplay *display);
வெளி வெறுமை SDL_OnWindowShown(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowHidden(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowMoved(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowResized(SDL_Window *window);
வெளி வெறுமை SDL_CheckWindowPixelSizeChanged(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowPixelSizeChanged(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowLiveResizeUpdate(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowMinimized(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowMaximized(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowRestored(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowEnter(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowLeave(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowFocusGained(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowFocusLost(SDL_Window *window);
வெளி வெறுமை SDL_OnWindowDisplayChanged(SDL_Window *window);
வெளி வெறுமை SDL_UpdateWindowGrab(SDL_Window *window);
வெளி bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit);
வெளி SDL_Window *SDL_GetToplevelForKeyboardFocus(வெறுமை);

வெளி bool SDL_ShouldAllowTopmost(வெறுமை);

வெளி வெறுமை SDL_ToggleDragAndDropSupport(வெறுமை);

வெளி வெறுமை SDL_UpdateDesktopBounds(வெறுமை);

வெளி SDL_Text_உள்ளீடு_Type SDL_Get_Text_உள்ளீடு_Type(SDL_PropertiesID props);
வெளி SDL_Capitalization SDL_Get_Text_உள்ளீடு_Capitalization(SDL_PropertiesID props);
வெளி bool SDL_Get_Text_உள்ளீடு_Autocorrect(SDL_PropertiesID props);
வெளி bool SDL_Get_Text_உள்ளீடு_Multiline(SDL_PropertiesID props);

வெளி வெறுமை SDL_SendScreenKeyboardShown(வெறுமை);
வெளி வெறுமை SDL_SendScreenKeyboardHidden(வெறுமை);

#endif // SDL_sysvideo_h_
