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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_sysvideo_h_
#define SDL_sysvideo_h_

#અન્તર્ભાવ <SDL3/SDL_vulkan.h>

#અન્તર્ભાવ "SDL_surface_c.h"

// The SDL video driver

પ્રકારવ્યાખ્યા સંરચના SDL_VideoDisplay SDL_VideoDisplay;
પ્રકારવ્યાખ્યા સંરચના SDL_VideoDevice SDL_VideoDevice;
પ્રકારવ્યાખ્યા સંરચના SDL_VideoData SDL_VideoData;
પ્રકારવ્યાખ્યા સંરચના SDL_DisplayData SDL_DisplayData;
પ્રકારવ્યાખ્યા સંરચના SDL_WindowData SDL_WindowData;

પ્રકારવ્યાખ્યા સંરચના
{
    દશાંશ SDR_white_level;
    દશાંશ HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
સંરચના SDL_Window
{
    SDL_WindowID id;
    અક્ષર *title;
    SDL_Surface *icon;
    પૂર્ણાંક x, y;
    પૂર્ણાંક w, h;
    પૂર્ણાંક min_w, min_h;
    પૂર્ણાંક max_w, max_h;
    દશાંશ min_aspect;
    દશાંશ max_aspect;
    પૂર્ણાંક last_pixel_w, last_pixel_h;
    SDL_WindowFlags flags;
    SDL_WindowFlags pending_flags;
    દશાંશ display_scale;
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

    દશાંશ opacity;

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

    પૂર્ણાંક safe_inset_ડાબું;
    પૂર્ણાંક safe_inset_જમણું;
    પૂર્ણાંક safe_inset_ટોચ;
    પૂર્ણાંક safe_inset_bottom;
    SDL_Rect safe_rect;

    SDL_PropertiesID text_આગત_props;
    bool text_આગત_active;
    SDL_Rect text_આગત_rect;
    પૂર્ણાંક text_આગત_cursor;

    SDL_Rect mouse_rect;

    SDL_HitTest hit_test;
    શૂન્ય *hit_test_data;

    SDL_ProgressState progress_state;
    દશાંશ progress_કિંમત;

    SDL_PropertiesID props;

    પૂર્ણાંક અંક_renderers;
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
સંરચના SDL_VideoDisplay
{
    SDL_DisplayID id;
    અક્ષર *name;
    પૂર્ણાંક max_fullscreen_modes;
    પૂર્ણાંક અંક_fullscreen_modes;
    SDL_DisplayMode *fullscreen_modes;
    SDL_DisplayMode desktop_mode;
    અચલ SDL_DisplayMode *current_mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    દશાંશ content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_active;
    SDL_Window *fullscreen_window;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_DisplayData *internal;
};

// Video device flags
પ્રકારવ્યાખ્યા ગણના
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
પ્રકારવ્યાખ્યા ગણના
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

પ્રકારવ્યાખ્યા ગણના
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_FullscreenResult;

સંરચના SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    અચલ અક્ષર *name;

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
    શૂન્ય (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    શૂન્ય (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    શૂન્ય (*RefreshDisplays)(SDL_VideoDevice *_this);

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
    શૂન્ય (*SetWindowTitle)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowIcon)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
    bool (*SetWindowPosition)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*SetWindowSize)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*SetWindowMinimumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*SetWindowMaximumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*SetWindowAspectRatio)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GetWindowBordersSize)(SDL_VideoDevice *_this, SDL_Window *window, પૂર્ણાંક *ટોચ, પૂર્ણાંક *ડાબું, પૂર્ણાંક *bottom, પૂર્ણાંક *જમણું);
    દશાંશ (*GetWindowContentScale)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*GetWindowSizeInPixels)(SDL_VideoDevice *_this, SDL_Window *window, પૂર્ણાંક *w, પૂર્ણાંક *h);
    bool (*SetWindowOpacity)(SDL_VideoDevice *_this, SDL_Window *window, દશાંશ opacity);
    bool (*SetWindowParent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
    bool (*SetWindowModal)(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
    શૂન્ય (*ShowWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*HideWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*RaiseWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*MaximizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*MinimizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*RestoreWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*SetWindowBordered)(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
    શૂન્ય (*SetWindowResizable)(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
    શૂન્ય (*Set_Window_Always_On_ટોચ)(SDL_VideoDevice *_this, SDL_Window *window, bool on_ટોચ);
    SDL_FullscreenResult (*SetWindowFullscreen)(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    શૂન્ય *(*GetWindowICCProfile)(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
    SDL_DisplayID (*GetDisplayForWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseRect)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    bool (*SetWindowKeyboardGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    શૂન્ય (*DestroyWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*CreateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, શૂન્ય **pixels, પૂર્ણાંક *pitch);
    bool (*SetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, પૂર્ણાંક vsync);
    bool (*GetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, પૂર્ણાંક *vsync);
    bool (*UpdateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, અચલ SDL_Rect *rects, પૂર્ણાંક numrects);
    શૂન્ય (*DestroyWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*OnWindowEnter)(SDL_VideoDevice *_this, SDL_Window *window);
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
    bool (*GL_LoadLibrary)(SDL_VideoDevice *_this, અચલ અક્ષર *path);
    SDL_FunctionPointer (*GL_GetProcAddress)(SDL_VideoDevice *_this, અચલ અક્ષર *proc);
    શૂન્ય (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_SetSwapInterval)(SDL_VideoDevice *_this, પૂર્ણાંક interval);
    bool (*GL_GetSwapInterval)(SDL_VideoDevice *_this, પૂર્ણાંક *interval);
    bool (*GL_SwapWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    શૂન્ય (*GL_SetDefaultProfileConfig)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_LoadLibrary)(SDL_VideoDevice *_this, અચલ અક્ષર *path);
    શૂન્ય (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    અક્ષર અચલ * અચલ *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *ગણતરી);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_Window *window, VkInstance instance, અચલ સંરચના VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
    શૂન્ય (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, અચલ સંરચના VkAllocationCallbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 queueFamilyIndex);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    શૂન્ય *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    પૂર્ણાંક (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    શૂન્ય (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*Start_Text_આગત)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    bool (*Stop_Text_આગત)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Update_Text_આગત_Area)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_Window *window);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    શૂન્ય (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    શૂન્ય (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window);
    શૂન્ય (*Set_Text_આગત_Properties)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);

    // Clipboard
    અચલ અક્ષર *અચલ *(*GetTextMimeTypes)(SDL_VideoDevice *_this, size_t *અંક_mime_types);
    bool (*SetClipboardData)(SDL_VideoDevice *_this);
    શૂન્ય *(*GetClipboardData)(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type, size_t *size);
    bool (*HasClipboardData)(SDL_VideoDevice *_this, અચલ અક્ષર *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*SetClipboardText)(SDL_VideoDevice *_this, અચલ અક્ષર *text);
    અક્ષર *(*GetClipboardText)(SDL_VideoDevice *_this);
    bool (*HasClipboardText)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*SetPrimarySelectionText)(SDL_VideoDevice *_this, અચલ અક્ષર *text);
    અક્ષર *(*GetPrimarySelectionText)(SDL_VideoDevice *_this);
    bool (*HasPrimarySelectionText)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*ShowMessageBox)(SDL_VideoDevice *_this, અચલ SDL_MessageBoxData *messageboxdata, પૂર્ણાંક *buttonID);

    // Hit-testing
    bool (*SetWindowHitTest)(SDL_Window *window, bool enabled);

    // Tell window that app enabled drag'n'drop events
    શૂન્ય (*AcceptDragAndDrop)(SDL_Window *window, bool accept);

    // Display the system-level window menu
    શૂન્ય (*ShowWindowSystemMenu)(SDL_Window *window, પૂર્ણાંક x, પૂર્ણાંક y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    શૂન્ય *wakeup_window;
    પૂર્ણાંક અંક_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_Window *windows;
    SDL_Window *grabbed_window;
    Uint32 clipboard_sequence;
    SDL_ClipboardDataCallback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    શૂન્ય *clipboard_userdata;
    અક્ષર **clipboard_mime_types;
    size_t અંક_clipboard_mime_types;
    અક્ષર *primary_selection_text;
    bool setting_display_mode;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    સંરચના
    {
        પૂર્ણાંક red_size;
        પૂર્ણાંક green_size;
        પૂર્ણાંક blue_size;
        પૂર્ણાંક alpha_size;
        પૂર્ણાંક depth_size;
        પૂર્ણાંક buffer_size;
        પૂર્ણાંક stencil_size;
        પૂર્ણાંક double_buffer;
        પૂર્ણાંક accum_red_size;
        પૂર્ણાંક accum_green_size;
        પૂર્ણાંક accum_blue_size;
        પૂર્ણાંક accum_alpha_size;
        પૂર્ણાંક stereo;
        પૂર્ણાંક multisamplebuffers;
        પૂર્ણાંક multisamplesamples;
        પૂર્ણાંક floatbuffers;
        પૂર્ણાંક accelerated;
        પૂર્ણાંક major_version;
        પૂર્ણાંક minor_version;
        પૂર્ણાંક flags;
        પૂર્ણાંક profile_mask;
        પૂર્ણાંક share_with_current_context;
        પૂર્ણાંક release_behavior;
        પૂર્ણાંક reset_notification;
        પૂર્ણાંક framebuffer_srgb_capable;
        પૂર્ણાંક no_error;
        પૂર્ણાંક retained_backing;
        પૂર્ણાંક egl_platform;
        પૂર્ણાંક driver_loaded;
        પૂર્ણાંક HAS_GL_ARB_color_buffer_float;
        અક્ષર driver_path[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    શૂન્ય *egl_attrib_callback_userdata;

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
    સંરચના
    {
        SDL_FunctionPointer vkGetInstanceProcAddr;
        SDL_FunctionPointer vkEnumerateInstanceExtensionProperties;
        પૂર્ણાંક loader_loaded;
        અક્ષર loader_path[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_VideoData *internal;
    સંરચના SDL_GLDriverData *gl_data;

#ifdef SDL_VIDEO_OPENGL_EGL
    સંરચના SDL_EGL_VideoData *egl_data;
#endif

#જો defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    સંરચના SDL_PrivateGLESData *gles_data;
#endif

    /* * * */
    // The function used to dispose of this structure
    શૂન્ય (*મુક્ત)(SDL_VideoDevice *_this);
};

પ્રકારવ્યાખ્યા સંરચના VideoBootStrap
{
    અચલ અક્ષર *name;
    અચલ અક્ષર *desc;
    SDL_VideoDevice *(*create)(શૂન્ય);
    bool (*ShowMessageBox)(અચલ SDL_MessageBoxData *messageboxdata, પૂર્ણાંક *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
બાહ્ય VideoBootStrap PRIVATE_bootstrap;
બાહ્ય VideoBootStrap COCOA_bootstrap;
બાહ્ય VideoBootStrap X11_bootstrap;
બાહ્ય VideoBootStrap WINDOWS_bootstrap;
બાહ્ય VideoBootStrap HAIKU_bootstrap;
બાહ્ય VideoBootStrap UIKIT_bootstrap;
બાહ્ય VideoBootStrap Android_bootstrap;
બાહ્ય VideoBootStrap OPENHARMONY_bootstrap;
બાહ્ય VideoBootStrap PS2_bootstrap;
બાહ્ય VideoBootStrap PSP_bootstrap;
બાહ્ય VideoBootStrap VITA_bootstrap;
બાહ્ય VideoBootStrap RISCOS_bootstrap;
બાહ્ય VideoBootStrap N3DS_bootstrap;
બાહ્ય VideoBootStrap NGAGE_bootstrap;
બાહ્ય VideoBootStrap RPI_bootstrap;
બાહ્ય VideoBootStrap KMSDRM_bootstrap;
બાહ્ય VideoBootStrap DUMMY_bootstrap;
બાહ્ય VideoBootStrap DUMMY_evdev_bootstrap;
બાહ્ય VideoBootStrap Wayland_preferred_bootstrap;
બાહ્ય VideoBootStrap Wayland_bootstrap;
બાહ્ય VideoBootStrap VIVANTE_bootstrap;
બાહ્ય VideoBootStrap Emscripten_bootstrap;
બાહ્ય VideoBootStrap OFFSCREEN_bootstrap;
બાહ્ય VideoBootStrap QNX_bootstrap;
બાહ્ય VideoBootStrap OPENVR_bootstrap;
બાહ્ય VideoBootStrap DOSVESA_bootstrap;

બાહ્ય bool SDL_UninitializedVideo(શૂન્ય);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
બાહ્ય bool SDL_OnVideoThread(શૂન્ય);
બાહ્ય SDL_VideoDevice *SDL_GetVideoDevice(શૂન્ય);
બાહ્ય શૂન્ય SDL_SetSystemTheme(SDL_SystemTheme theme);
બાહ્ય SDL_DisplayID SDL_AddBasicVideoDisplay(અચલ SDL_DisplayMode *desktop_mode);
બાહ્ય SDL_DisplayID SDL_AddVideoDisplay(અચલ SDL_VideoDisplay *display, bool send_event);
બાહ્ય શૂન્ય SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
બાહ્ય bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, અચલ SDL_DisplayMode *mode);
બાહ્ય શૂન્ય SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
બાહ્ય શૂન્ય SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, અચલ SDL_DisplayMode *mode);
બાહ્ય શૂન્ય SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, અચલ SDL_DisplayMode *mode);
બાહ્ય શૂન્ય SDL_SetDisplayContentScale(SDL_VideoDisplay *display, દશાંશ scale);
બાહ્ય શૂન્ય SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, અચલ SDL_HDROutputProperties *HDR);
બાહ્ય bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode);
બાહ્ય SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
બાહ્ય SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window);
બાહ્ય SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window);
બાહ્ય SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window);
બાહ્ય પૂર્ણાંક SDL_GetDisplayIndex(SDL_DisplayID displayID);
બાહ્ય SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID display);
બાહ્ય SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window);
બાહ્ય પૂર્ણાંક SDL_Get_Message_Box_ગણતરી(શૂન્ય);
બાહ્ય શૂન્ય SDL_SetWindowHDRProperties(SDL_Window *window, અચલ SDL_HDROutputProperties *HDR, bool send_event);
બાહ્ય શૂન્ય SDL_SetWindowSafeAreaInsets(SDL_Window *window, પૂર્ણાંક ડાબું, પૂર્ણાંક જમણું, પૂર્ણાંક ટોચ, પૂર્ણાંક bottom);

બાહ્ય શૂન્ય SDL_GL_DeduceMaxSupportedESProfile(પૂર્ણાંક *major, પૂર્ણાંક *minor);

બાહ્ય bool SDL_RecreateWindow(SDL_Window *window, SDL_WindowFlags flags);
બાહ્ય bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags);
બાહ્ય bool SDL_HasWindows(શૂન્ય);
બાહ્ય શૂન્ય SDL_RelativeToGlobalForWindow(SDL_Window *window, પૂર્ણાંક rel_x, પૂર્ણાંક rel_y, પૂર્ણાંક *abs_x, પૂર્ણાંક *abs_y);
બાહ્ય શૂન્ય SDL_GlobalToRelativeForWindow(SDL_Window *window, પૂર્ણાંક abs_x, પૂર્ણાંક abs_y, પૂર્ણાંક *rel_x, પૂર્ણાંક *rel_y);
બાહ્ય bool SDL_ShouldFocusPopup(SDL_Window *window);
બાહ્ય bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus);

બાહ્ય શૂન્ય SDL_OnDisplayAdded(SDL_VideoDisplay *display);
બાહ્ય શૂન્ય SDL_OnDisplayMoved(SDL_VideoDisplay *display);
બાહ્ય શૂન્ય SDL_OnWindowShown(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowHidden(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowMoved(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowResized(SDL_Window *window);
બાહ્ય શૂન્ય SDL_CheckWindowPixelSizeChanged(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowPixelSizeChanged(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowLiveResizeUpdate(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowMinimized(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowMaximized(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowRestored(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowEnter(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowLeave(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowFocusGained(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowFocusLost(SDL_Window *window);
બાહ્ય શૂન્ય SDL_OnWindowDisplayChanged(SDL_Window *window);
બાહ્ય શૂન્ય SDL_UpdateWindowGrab(SDL_Window *window);
બાહ્ય bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit);
બાહ્ય SDL_Window *SDL_GetToplevelForKeyboardFocus(શૂન્ય);

બાહ્ય bool SDL_ShouldAllowTopmost(શૂન્ય);

બાહ્ય શૂન્ય SDL_ToggleDragAndDropSupport(શૂન્ય);

બાહ્ય શૂન્ય SDL_UpdateDesktopBounds(શૂન્ય);

બાહ્ય SDL_Text_આગત_Type SDL_Get_Text_આગત_Type(SDL_PropertiesID props);
બાહ્ય SDL_Capitalization SDL_Get_Text_આગત_Capitalization(SDL_PropertiesID props);
બાહ્ય bool SDL_Get_Text_આગત_Autocorrect(SDL_PropertiesID props);
બાહ્ય bool SDL_Get_Text_આગત_Multiline(SDL_PropertiesID props);

બાહ્ય શૂન્ય SDL_SendScreenKeyboardShown(શૂન્ય);
બાહ્ય શૂન્ય SDL_SendScreenKeyboardHidden(શૂન્ય);

#endif // SDL_sysvideo_h_
