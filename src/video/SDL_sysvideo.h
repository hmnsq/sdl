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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_sysvideo_h_
#घोषणा SDL_sysvideo_h_

#समावेश <SDL3/SDL_vulkan.h>

#समावेश "SDL_surface_c.h"

// The SDL video driver

प्रकार काष्ठा SDL_VideoDisplay SDL_VideoDisplay;
प्रकार काष्ठा SDL_VideoDevice SDL_VideoDevice;
प्रकार काष्ठा SDL_Video_तथ्य SDL_Video_तथ्य;
प्रकार काष्ठा SDL_Display_तथ्य SDL_Display_तथ्य;
प्रकार काष्ठा SDL_Window_तथ्य SDL_Window_तथ्य;

प्रकार काष्ठा
{
    भग्न SDR_white_level;
    भग्न HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
काष्ठा SDL_Window
{
    SDL_WindowID id;
    अक्षर *title;
    SDL_Surface *icon;
    पूर्णांक x, y;
    पूर्णांक w, h;
    पूर्णांक min_w, min_h;
    पूर्णांक max_w, max_h;
    भग्न min_aspect;
    भग्न max_aspect;
    पूर्णांक last_pixel_w, last_pixel_h;
    SDL_WindowFlags flags;
    SDL_WindowFlags pending_flags;
    भग्न display_scale;
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

    भग्न opacity;

    SDL_Surface *surface;
    bool surface_valid;

    bool is_hiding;
    bool restore_on_show; // Child was hidden recursively by the parent, restore when shown.
    bool last_position_pending; // This should NOT be cleared by the backend, as it is used for fullscreen positioning.
    bool last_आकार_pending; // This should be cleared by the backend if the new size cannot be applied.
    bool update_fullscreen_on_display_changed;
    bool constrain_popup;
    bool is_destroying;
    bool is_dropping; // drag/drop in progress, expecting SDL_SendDropComplete().

    पूर्णांक safe_inset_बायाँ;
    पूर्णांक safe_inset_दायाँ;
    पूर्णांक safe_inset_शीर्ष;
    पूर्णांक safe_inset_bottom;
    SDL_Rect safe_rect;

    SDL_PropertiesID text_निवेश_props;
    bool text_निवेश_active;
    SDL_Rect text_निवेश_rect;
    पूर्णांक text_निवेश_cursor;

    SDL_Rect mouse_rect;

    SDL_HitTest hit_test;
    व्योम *hit_test_तथ्य;

    SDL_ProgressState progress_state;
    भग्न progress_मूल्य;

    SDL_PropertiesID props;

    पूर्णांक अंक_renderers;
    SDL_Renderer **renderers;

    SDL_Window_तथ्य *internal;

    // If a toplevel window, holds the current keyboard focus for grabbing popups.
    SDL_Window *keyboard_focus;

    SDL_Window *पूर्व;
    SDL_Window *अग्र;

    SDL_Window *parent;
    SDL_Window *first_child;
    SDL_Window *पूर्व_sibling;
    SDL_Window *अग्र_sibling;
};
#घोषणा SDL_WINDOW_FULLSCREEN_VISIBLE(W)        \
    ((((W)->flags & SDL_WINDOW_FULLSCREEN) != 0) &&   \
     (((W)->flags & SDL_WINDOW_HIDDEN) == 0) && \
     (((W)->flags & SDL_WINDOW_MINIMIZED) == 0))

#घोषणा SDL_WINDOW_IS_POPUP(W) \
    (((W)->flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0)

/*
 * Define the SDL display structure.
 * This corresponds to physical monitors attached to the system.
 */
काष्ठा SDL_VideoDisplay
{
    SDL_DisplayID id;
    अक्षर *name;
    पूर्णांक max_fullscreen_modes;
    पूर्णांक अंक_fullscreen_modes;
    SDL_DisplayMode *fullscreen_modes;
    SDL_DisplayMode desktop_mode;
    स्थिर SDL_DisplayMode *current_mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    भग्न content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_active;
    SDL_Window *fullscreen_window;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_Display_तथ्य *internal;
};

// Video device flags
प्रकार क्रमागत
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
प्रकार क्रमागत
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

प्रकार क्रमागत
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_Fullscreen_परिणाम;

काष्ठा SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    स्थिर अक्षर *name;

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
    व्योम (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    व्योम (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    व्योम (*RefreshDisplays)(SDL_VideoDevice *_this);

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
    व्योम (*SetWindowTitle)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowIcon)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
    bool (*SetWindowPosition)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*Set_Window_आकार)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*Set_Window_Minimum_आकार)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*Set_Window_Maximum_आकार)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*SetWindowAspectRatio)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Get_Window_Borders_आकार)(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *शीर्ष, पूर्णांक *बायाँ, पूर्णांक *bottom, पूर्णांक *दायाँ);
    भग्न (*GetWindowContentScale)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*Get_Window_आकार_In_Pixels)(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *w, पूर्णांक *h);
    bool (*SetWindowOpacity)(SDL_VideoDevice *_this, SDL_Window *window, भग्न opacity);
    bool (*SetWindowParent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
    bool (*SetWindowModal)(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
    व्योम (*ShowWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*HideWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*RaiseWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*MaximizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*MinimizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*RestoreWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*SetWindowBordered)(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
    व्योम (*SetWindowResizable)(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
    व्योम (*Set_Window_Always_On_शीर्ष)(SDL_VideoDevice *_this, SDL_Window *window, bool on_शीर्ष);
    SDL_Fullscreen_परिणाम (*SetWindowFullscreen)(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    व्योम *(*GetWindowICCProfile)(SDL_VideoDevice *_this, SDL_Window *window, माप_प्रकार *आकार);
    SDL_DisplayID (*GetDisplayForWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseRect)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    bool (*SetWindowKeyboardGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    व्योम (*DestroyWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*CreateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, व्योम **pixels, पूर्णांक *pitch);
    bool (*SetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक vsync);
    bool (*GetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *vsync);
    bool (*UpdateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, स्थिर SDL_Rect *rects, पूर्णांक numrects);
    व्योम (*DestroyWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*OnWindowEnter)(SDL_VideoDevice *_this, SDL_Window *window);
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
    bool (*GL_LoadLibrary)(SDL_VideoDevice *_this, स्थिर अक्षर *path);
    SDL_FunctionPointer (*GL_GetProcAddress)(SDL_VideoDevice *_this, स्थिर अक्षर *proc);
    व्योम (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_SetSwapInterval)(SDL_VideoDevice *_this, पूर्णांक interval);
    bool (*GL_GetSwapInterval)(SDL_VideoDevice *_this, पूर्णांक *interval);
    bool (*GL_SwapWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    व्योम (*GL_SetDefaultProfileConfig)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_LoadLibrary)(SDL_VideoDevice *_this, स्थिर अक्षर *path);
    व्योम (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    अक्षर स्थिर * स्थिर *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *गिनती);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_Window *window, VkInstance instance, स्थिर काष्ठा VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
    व्योम (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, स्थिर काष्ठा VkAllocationCallbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 queue_Family_सूचकांक);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    व्योम *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    पूर्णांक (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    व्योम (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*Start_Text_निवेश)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    bool (*Stop_Text_निवेश)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Update_Text_निवेश_Area)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_Window *window);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    व्योम (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    व्योम (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window);
    व्योम (*Set_Text_निवेश_Properties)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);

    // Clipboard
    स्थिर अक्षर *स्थिर *(*GetTextMimeTypes)(SDL_VideoDevice *_this, माप_प्रकार *अंक_mime_types);
    bool (*Set_Clipboard_तथ्य)(SDL_VideoDevice *_this);
    व्योम *(*Get_Clipboard_तथ्य)(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type, माप_प्रकार *आकार);
    bool (*Has_Clipboard_तथ्य)(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*SetClipboardText)(SDL_VideoDevice *_this, स्थिर अक्षर *text);
    अक्षर *(*GetClipboardText)(SDL_VideoDevice *_this);
    bool (*HasClipboardText)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*SetPrimarySelectionText)(SDL_VideoDevice *_this, स्थिर अक्षर *text);
    अक्षर *(*GetPrimarySelectionText)(SDL_VideoDevice *_this);
    bool (*HasPrimarySelectionText)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*ShowMessageBox)(SDL_VideoDevice *_this, स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonID);

    // Hit-testing
    bool (*SetWindowHitTest)(SDL_Window *window, bool enabled);

    // Tell window that app enabled drag'n'drop events
    व्योम (*AcceptDragAndDrop)(SDL_Window *window, bool accept);

    // Display the system-level window menu
    व्योम (*ShowWindowSystemMenu)(SDL_Window *window, पूर्णांक x, पूर्णांक y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    व्योम *wakeup_window;
    पूर्णांक अंक_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_Window *windows;
    SDL_Window *grabbed_window;
    Uint32 clipboard_sequence;
    SDL_Clipboard_तथ्य_Callback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    व्योम *clipboard_userdata;
    अक्षर **clipboard_mime_types;
    माप_प्रकार अंक_clipboard_mime_types;
    अक्षर *primary_selection_text;
    bool setting_display_mode;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    काष्ठा
    {
        पूर्णांक red_आकार;
        पूर्णांक green_आकार;
        पूर्णांक blue_आकार;
        पूर्णांक alpha_आकार;
        पूर्णांक depth_आकार;
        पूर्णांक बफर_आकार;
        पूर्णांक stencil_आकार;
        पूर्णांक double_बफर;
        पूर्णांक accum_red_आकार;
        पूर्णांक accum_green_आकार;
        पूर्णांक accum_blue_आकार;
        पूर्णांक accum_alpha_आकार;
        पूर्णांक stereo;
        पूर्णांक multisamplebuffers;
        पूर्णांक multisamplesamples;
        पूर्णांक floatbuffers;
        पूर्णांक accelerated;
        पूर्णांक major_version;
        पूर्णांक minor_version;
        पूर्णांक flags;
        पूर्णांक profile_mask;
        पूर्णांक share_with_current_context;
        पूर्णांक release_behavior;
        पूर्णांक reset_notification;
        पूर्णांक framebuffer_srgb_capable;
        पूर्णांक no_error;
        पूर्णांक retained_backing;
        पूर्णांक egl_platform;
        पूर्णांक driver_loaded;
        पूर्णांक HAS_GL_ARB_color_बफर_float;
        अक्षर driver_path[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    व्योम *egl_attrib_callback_userdata;

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
    काष्ठा
    {
        SDL_FunctionPointer vkGetInstanceProcAddr;
        SDL_FunctionPointer vkEnumerateInstanceExtensionProperties;
        पूर्णांक loader_loaded;
        अक्षर loader_path[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_Video_तथ्य *internal;
    काष्ठा SDL_GLDriver_तथ्य *gl_तथ्य;

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    काष्ठा SDL_EGL_Video_तथ्य *egl_तथ्य;
#पूर्ण_अगर

#अगर defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    काष्ठा SDL_PrivateGLESData *gles_तथ्य;
#पूर्ण_अगर

    /* * * */
    // The function used to dispose of this structure
    व्योम (*मुक्त)(SDL_VideoDevice *_this);
};

प्रकार काष्ठा VideoBootStrap
{
    स्थिर अक्षर *name;
    स्थिर अक्षर *desc;
    SDL_VideoDevice *(*create)(व्योम);
    bool (*ShowMessageBox)(स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonID);  // can be done without initializing backend!
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

बाह्य bool SDL_UninitializedVideo(व्योम);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
बाह्य bool SDL_OnVideoThread(व्योम);
बाह्य SDL_VideoDevice *SDL_GetVideoDevice(व्योम);
बाह्य व्योम SDL_SetSystemTheme(SDL_SystemTheme theme);
बाह्य SDL_DisplayID SDL_AddBasicVideoDisplay(स्थिर SDL_DisplayMode *desktop_mode);
बाह्य SDL_DisplayID SDL_AddVideoDisplay(स्थिर SDL_VideoDisplay *display, bool send_event);
बाह्य व्योम SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
बाह्य bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, स्थिर SDL_DisplayMode *mode);
बाह्य व्योम SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
बाह्य व्योम SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, स्थिर SDL_DisplayMode *mode);
बाह्य व्योम SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, स्थिर SDL_DisplayMode *mode);
बाह्य व्योम SDL_SetDisplayContentScale(SDL_VideoDisplay *display, भग्न scale);
बाह्य व्योम SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, स्थिर SDL_HDROutputProperties *HDR);
बाह्य bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode);
बाह्य SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
बाह्य SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window);
बाह्य SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window);
बाह्य SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window);
बाह्य पूर्णांक SDL_Get_Display_सूचकांक(SDL_DisplayID displayID);
बाह्य SDL_Display_तथ्य *SDL_Get_Display_Driver_तथ्य(SDL_DisplayID display);
बाह्य SDL_Display_तथ्य *SDL_Get_Display_Driver_तथ्य_For_Window(SDL_Window *window);
बाह्य पूर्णांक SDL_Get_Message_Box_गिनती(व्योम);
बाह्य व्योम SDL_SetWindowHDRProperties(SDL_Window *window, स्थिर SDL_HDROutputProperties *HDR, bool send_event);
बाह्य व्योम SDL_SetWindowSafeAreaInsets(SDL_Window *window, पूर्णांक बायाँ, पूर्णांक दायाँ, पूर्णांक शीर्ष, पूर्णांक bottom);

बाह्य व्योम SDL_GL_DeduceMaxSupportedESProfile(पूर्णांक *major, पूर्णांक *minor);

बाह्य bool SDL_RecreateWindow(SDL_Window *window, SDL_WindowFlags flags);
बाह्य bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags);
बाह्य bool SDL_HasWindows(व्योम);
बाह्य व्योम SDL_RelativeToGlobalForWindow(SDL_Window *window, पूर्णांक rel_x, पूर्णांक rel_y, पूर्णांक *abs_x, पूर्णांक *abs_y);
बाह्य व्योम SDL_GlobalToRelativeForWindow(SDL_Window *window, पूर्णांक abs_x, पूर्णांक abs_y, पूर्णांक *rel_x, पूर्णांक *rel_y);
बाह्य bool SDL_ShouldFocusPopup(SDL_Window *window);
बाह्य bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus);

बाह्य व्योम SDL_OnDisplayAdded(SDL_VideoDisplay *display);
बाह्य व्योम SDL_OnDisplayMoved(SDL_VideoDisplay *display);
बाह्य व्योम SDL_OnWindowShown(SDL_Window *window);
बाह्य व्योम SDL_OnWindowHidden(SDL_Window *window);
बाह्य व्योम SDL_OnWindowMoved(SDL_Window *window);
बाह्य व्योम SDL_OnWindowResized(SDL_Window *window);
बाह्य व्योम SDL_Check_Window_Pixel_आकार_Changed(SDL_Window *window);
बाह्य व्योम SDL_On_Window_Pixel_आकार_Changed(SDL_Window *window);
बाह्य व्योम SDL_OnWindowLiveResizeUpdate(SDL_Window *window);
बाह्य व्योम SDL_OnWindowMinimized(SDL_Window *window);
बाह्य व्योम SDL_OnWindowMaximized(SDL_Window *window);
बाह्य व्योम SDL_OnWindowRestored(SDL_Window *window);
बाह्य व्योम SDL_OnWindowEnter(SDL_Window *window);
बाह्य व्योम SDL_OnWindowLeave(SDL_Window *window);
बाह्य व्योम SDL_OnWindowFocusGained(SDL_Window *window);
बाह्य व्योम SDL_OnWindowFocusLost(SDL_Window *window);
बाह्य व्योम SDL_OnWindowDisplayChanged(SDL_Window *window);
बाह्य व्योम SDL_UpdateWindowGrab(SDL_Window *window);
बाह्य bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit);
बाह्य SDL_Window *SDL_GetToplevelForKeyboardFocus(व्योम);

बाह्य bool SDL_ShouldAllowTopmost(व्योम);

बाह्य व्योम SDL_ToggleDragAndDropSupport(व्योम);

बाह्य व्योम SDL_UpdateDesktopBounds(व्योम);

बाह्य SDL_Text_निवेश_Type SDL_Get_Text_निवेश_Type(SDL_PropertiesID props);
बाह्य SDL_Capitalization SDL_Get_Text_निवेश_Capitalization(SDL_PropertiesID props);
बाह्य bool SDL_Get_Text_निवेश_Autocorrect(SDL_PropertiesID props);
बाह्य bool SDL_Get_Text_निवेश_Multiline(SDL_PropertiesID props);

बाह्य व्योम SDL_SendScreenKeyboardShown(व्योम);
बाह्य व्योम SDL_SendScreenKeyboardHidden(व्योम);

#पूर्ण_अगर // SDL_sysvideo_h_
