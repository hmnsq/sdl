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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_sysvideo_h_
#define SDL_sysvideo_h_

#ଅନ୍ତର୍ଭାଵ <SDL3/SDL_vulkan.h>

#ଅନ୍ତର୍ଭାଵ "SDL_surface_c.h"

// The SDL video driver

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_VideoDisplay SDL_VideoDisplay;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_VideoDevice SDL_VideoDevice;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_VideoData SDL_VideoData;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_DisplayData SDL_DisplayData;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_WindowData SDL_WindowData;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ଦଶମିକ SDR_white_level;
    ଦଶମିକ HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
ସଂରଚନା SDL_Window
{
    SDL_WindowID id;
    ଅକ୍ଷର *title;
    SDL_Surface *icon;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା min_w, min_h;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_w, max_h;
    ଦଶମିକ min_aspect;
    ଦଶମିକ max_aspect;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା last_pixel_w, last_pixel_h;
    SDL_WindowFlags flags;
    SDL_WindowFlags pending_flags;
    ଦଶମିକ display_scale;
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

    ଦଶମିକ opacity;

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

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା safe_inset_ବାମ;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା safe_inset_ଡାହାଣ;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା safe_inset_ଶୀର୍ଷ;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା safe_inset_bottom;
    SDL_Rect safe_rect;

    SDL_PropertiesID text_ନିବେଶ_props;
    bool text_ନିବେଶ_active;
    SDL_Rect text_ନିବେଶ_rect;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା text_ନିବେଶ_cursor;

    SDL_Rect mouse_rect;

    SDL_HitTest hit_test;
    ଶୂନ୍ୟ *hit_test_data;

    SDL_ProgressState progress_state;
    ଦଶମିକ progress_ମୂଲ୍ୟ;

    SDL_PropertiesID props;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_renderers;
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
ସଂରଚନା SDL_VideoDisplay
{
    SDL_DisplayID id;
    ଅକ୍ଷର *name;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_fullscreen_modes;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_fullscreen_modes;
    SDL_DisplayMode *fullscreen_modes;
    SDL_DisplayMode desktop_mode;
    ଅଚଳ SDL_DisplayMode *current_mode;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    ଦଶମିକ content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_active;
    SDL_Window *fullscreen_window;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_DisplayData *internal;
};

// Video device flags
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
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
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_FullscreenResult;

ସଂରଚନା SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    ଅଚଳ ଅକ୍ଷର *name;

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
    ଶୂନ୍ୟ (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    ଶୂନ୍ୟ (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    ଶୂନ୍ୟ (*RefreshDisplays)(SDL_VideoDevice *_this);

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
    ଶୂନ୍ୟ (*SetWindowTitle)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowIcon)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
    bool (*SetWindowPosition)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*SetWindowSize)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*SetWindowMinimumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*SetWindowMaximumSize)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*SetWindowAspectRatio)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GetWindowBordersSize)(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଶୀର୍ଷ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ବାମ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *bottom, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଡାହାଣ);
    ଦଶମିକ (*GetWindowContentScale)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*GetWindowSizeInPixels)(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *h);
    bool (*SetWindowOpacity)(SDL_VideoDevice *_this, SDL_Window *window, ଦଶମିକ opacity);
    bool (*SetWindowParent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
    bool (*SetWindowModal)(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
    ଶୂନ୍ୟ (*ShowWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*HideWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*RaiseWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*MaximizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*MinimizeWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*RestoreWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*SetWindowBordered)(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
    ଶୂନ୍ୟ (*SetWindowResizable)(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
    ଶୂନ୍ୟ (*Set_Window_Always_On_ଶୀର୍ଷ)(SDL_VideoDevice *_this, SDL_Window *window, bool on_ଶୀର୍ଷ);
    SDL_FullscreenResult (*SetWindowFullscreen)(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    ଶୂନ୍ୟ *(*GetWindowICCProfile)(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
    SDL_DisplayID (*GetDisplayForWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseRect)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*SetWindowMouseGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    bool (*SetWindowKeyboardGrab)(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
    ଶୂନ୍ୟ (*DestroyWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*CreateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ଶୂନ୍ୟ **pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pitch);
    bool (*SetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା vsync);
    bool (*GetWindowFramebufferVSync)(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *vsync);
    bool (*UpdateWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window, ଅଚଳ SDL_Rect *rects, ପୂର୍ଣ୍ଣସଂଖ୍ୟା numrects);
    ଶୂନ୍ୟ (*DestroyWindowFramebuffer)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*OnWindowEnter)(SDL_VideoDevice *_this, SDL_Window *window);
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
    bool (*GL_LoadLibrary)(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path);
    SDL_FunctionPointer (*GL_GetProcAddress)(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *proc);
    ଶୂନ୍ୟ (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_SetSwapInterval)(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval);
    bool (*GL_GetSwapInterval)(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *interval);
    bool (*GL_SwapWindow)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    ଶୂନ୍ୟ (*GL_SetDefaultProfileConfig)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_LoadLibrary)(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path);
    ଶୂନ୍ୟ (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    ଅକ୍ଷର ଅଚଳ * ଅଚଳ *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *ଗଣନା_2);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_Window *window, VkInstance instance, ଅଚଳ ସଂରଚନା VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
    ଶୂନ୍ୟ (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ଅଚଳ ସଂରଚନା VkAllocationCallbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 queueFamilyIndex);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    ଶୂନ୍ୟ *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    ଶୂନ୍ୟ (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*Start_Text_ନିବେଶ)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    bool (*Stop_Text_ନିବେଶ)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*Update_Text_ନିବେଶ_Area)(SDL_VideoDevice *_this, SDL_Window *window);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_Window *window);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    ଶୂନ୍ୟ (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);
    ଶୂନ୍ୟ (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_Window *window);
    ଶୂନ୍ୟ (*Set_Text_ନିବେଶ_Properties)(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props);

    // Clipboard
    ଅଚଳ ଅକ୍ଷର *ଅଚଳ *(*GetTextMimeTypes)(SDL_VideoDevice *_this, size_t *ଅଙ୍କ_mime_types);
    bool (*SetClipboardData)(SDL_VideoDevice *_this);
    ଶୂନ୍ୟ *(*GetClipboardData)(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *size);
    bool (*HasClipboardData)(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*SetClipboardText)(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *text);
    ଅକ୍ଷର *(*GetClipboardText)(SDL_VideoDevice *_this);
    bool (*HasClipboardText)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*SetPrimarySelectionText)(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *text);
    ଅକ୍ଷର *(*GetPrimarySelectionText)(SDL_VideoDevice *_this);
    bool (*HasPrimarySelectionText)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*ShowMessageBox)(SDL_VideoDevice *_this, ଅଚଳ SDL_MessageBoxData *messageboxdata, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *buttonID);

    // Hit-testing
    bool (*SetWindowHitTest)(SDL_Window *window, bool enabled);

    // Tell window that app enabled drag'n'drop events
    ଶୂନ୍ୟ (*AcceptDragAndDrop)(SDL_Window *window, bool accept);

    // Display the system-level window menu
    ଶୂନ୍ୟ (*ShowWindowSystemMenu)(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    ଶୂନ୍ୟ *wakeup_window;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_Window *windows;
    SDL_Window *grabbed_window;
    Uint32 clipboard_sequence;
    SDL_ClipboardDataCallback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    ଶୂନ୍ୟ *clipboard_userdata;
    ଅକ୍ଷର **clipboard_mime_types;
    size_t ଅଙ୍କ_clipboard_mime_types;
    ଅକ୍ଷର *primary_selection_text;
    bool setting_display_mode;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    ସଂରଚନା
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା red_size;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା green_size;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା blue_size;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା alpha_size;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth_size;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା buffer_size;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା stencil_size;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା double_buffer;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା accum_red_size;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା accum_green_size;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା accum_blue_size;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା accum_alpha_size;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା stereo;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା multisamplebuffers;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା multisamplesamples;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା floatbuffers;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା accelerated;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା major_version;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା minor_version;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା profile_mask;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା share_with_current_context;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା release_behavior;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା reset_notification;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା framebuffer_srgb_capable;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା no_error;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା retained_backing;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା egl_platform;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା driver_loaded;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା HAS_GL_ARB_color_buffer_float;
        ଅକ୍ଷର driver_path[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    ଶୂନ୍ୟ *egl_attrib_callback_userdata;

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
    ସଂରଚନା
    {
        SDL_FunctionPointer vkGetInstanceProcAddr;
        SDL_FunctionPointer vkEnumerateInstanceExtensionProperties;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା loader_loaded;
        ଅକ୍ଷର loader_path[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_VideoData *internal;
    ସଂରଚନା SDL_GLDriverData *gl_data;

#ifdef SDL_VIDEO_OPENGL_EGL
    ସଂରଚନା SDL_EGL_VideoData *egl_data;
#endif

#ଯଦି defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    ସଂରଚନା SDL_PrivateGLESData *gles_data;
#endif

    /* * * */
    // The function used to dispose of this structure
    ଶୂନ୍ୟ (*ମୁକ୍ତ)(SDL_VideoDevice *_this);
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VideoBootStrap
{
    ଅଚଳ ଅକ୍ଷର *name;
    ଅଚଳ ଅକ୍ଷର *desc;
    SDL_VideoDevice *(*create)(ଶୂନ୍ୟ);
    bool (*ShowMessageBox)(ଅଚଳ SDL_MessageBoxData *messageboxdata, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
ବାହ୍ୟ VideoBootStrap PRIVATE_bootstrap;
ବାହ୍ୟ VideoBootStrap COCOA_bootstrap;
ବାହ୍ୟ VideoBootStrap X11_bootstrap;
ବାହ୍ୟ VideoBootStrap WINDOWS_bootstrap;
ବାହ୍ୟ VideoBootStrap HAIKU_bootstrap;
ବାହ୍ୟ VideoBootStrap UIKIT_bootstrap;
ବାହ୍ୟ VideoBootStrap Android_bootstrap;
ବାହ୍ୟ VideoBootStrap OPENHARMONY_bootstrap;
ବାହ୍ୟ VideoBootStrap PS2_bootstrap;
ବାହ୍ୟ VideoBootStrap PSP_bootstrap;
ବାହ୍ୟ VideoBootStrap VITA_bootstrap;
ବାହ୍ୟ VideoBootStrap RISCOS_bootstrap;
ବାହ୍ୟ VideoBootStrap N3DS_bootstrap;
ବାହ୍ୟ VideoBootStrap NGAGE_bootstrap;
ବାହ୍ୟ VideoBootStrap RPI_bootstrap;
ବାହ୍ୟ VideoBootStrap KMSDRM_bootstrap;
ବାହ୍ୟ VideoBootStrap DUMMY_bootstrap;
ବାହ୍ୟ VideoBootStrap DUMMY_evdev_bootstrap;
ବାହ୍ୟ VideoBootStrap Wayland_preferred_bootstrap;
ବାହ୍ୟ VideoBootStrap Wayland_bootstrap;
ବାହ୍ୟ VideoBootStrap VIVANTE_bootstrap;
ବାହ୍ୟ VideoBootStrap Emscripten_bootstrap;
ବାହ୍ୟ VideoBootStrap OFFSCREEN_bootstrap;
ବାହ୍ୟ VideoBootStrap QNX_bootstrap;
ବାହ୍ୟ VideoBootStrap OPENVR_bootstrap;
ବାହ୍ୟ VideoBootStrap DOSVESA_bootstrap;

ବାହ୍ୟ bool SDL_UninitializedVideo(ଶୂନ୍ୟ);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
ବାହ୍ୟ bool SDL_OnVideoThread(ଶୂନ୍ୟ);
ବାହ୍ୟ SDL_VideoDevice *SDL_GetVideoDevice(ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_SetSystemTheme(SDL_SystemTheme theme);
ବାହ୍ୟ SDL_DisplayID SDL_AddBasicVideoDisplay(ଅଚଳ SDL_DisplayMode *desktop_mode);
ବାହ୍ୟ SDL_DisplayID SDL_AddVideoDisplay(ଅଚଳ SDL_VideoDisplay *display, bool send_event);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
ବାହ୍ୟ bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ଅଚଳ SDL_DisplayMode *mode);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ଅଚଳ SDL_DisplayMode *mode);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ଅଚଳ SDL_DisplayMode *mode);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_SetDisplayContentScale(SDL_VideoDisplay *display, ଦଶମିକ scale);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ଅଚଳ SDL_HDROutputProperties *HDR);
ବାହ୍ୟ bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode);
ବାହ୍ୟ SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
ବାହ୍ୟ SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window);
ବାହ୍ୟ SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window);
ବାହ୍ୟ SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window);
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDL_GetDisplayIndex(SDL_DisplayID displayID);
ବାହ୍ୟ SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID display);
ବାହ୍ୟ SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window);
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDL_Get_Message_Box_ଗଣନା(ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_SetWindowHDRProperties(SDL_Window *window, ଅଚଳ SDL_HDROutputProperties *HDR, bool send_event);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_SetWindowSafeAreaInsets(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଶୀର୍ଷ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା bottom);

ବାହ୍ୟ ଶୂନ୍ୟ SDL_GL_DeduceMaxSupportedESProfile(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *major, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *minor);

ବାହ୍ୟ bool SDL_RecreateWindow(SDL_Window *window, SDL_WindowFlags flags);
ବାହ୍ୟ bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags);
ବାହ୍ୟ bool SDL_HasWindows(ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_RelativeToGlobalForWindow(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rel_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rel_y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *abs_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *abs_y);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_GlobalToRelativeForWindow(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା abs_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା abs_y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *rel_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *rel_y);
ବାହ୍ୟ bool SDL_ShouldFocusPopup(SDL_Window *window);
ବାହ୍ୟ bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus);

ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnDisplayAdded(SDL_VideoDisplay *display);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnDisplayMoved(SDL_VideoDisplay *display);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowShown(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowHidden(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowMoved(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowResized(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_CheckWindowPixelSizeChanged(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowPixelSizeChanged(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowLiveResizeUpdate(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowMinimized(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowMaximized(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowRestored(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowEnter(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowLeave(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowFocusGained(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowFocusLost(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_OnWindowDisplayChanged(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_UpdateWindowGrab(SDL_Window *window);
ବାହ୍ୟ bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit);
ବାହ୍ୟ SDL_Window *SDL_GetToplevelForKeyboardFocus(ଶୂନ୍ୟ);

ବାହ୍ୟ bool SDL_ShouldAllowTopmost(ଶୂନ୍ୟ);

ବାହ୍ୟ ଶୂନ୍ୟ SDL_ToggleDragAndDropSupport(ଶୂନ୍ୟ);

ବାହ୍ୟ ଶୂନ୍ୟ SDL_UpdateDesktopBounds(ଶୂନ୍ୟ);

ବାହ୍ୟ SDL_Text_ନିବେଶ_Type SDL_Get_Text_ନିବେଶ_Type(SDL_PropertiesID props);
ବାହ୍ୟ SDL_Capitalization SDL_Get_Text_ନିବେଶ_Capitalization(SDL_PropertiesID props);
ବାହ୍ୟ bool SDL_Get_Text_ନିବେଶ_Autocorrect(SDL_PropertiesID props);
ବାହ୍ୟ bool SDL_Get_Text_ନିବେଶ_Multiline(SDL_PropertiesID props);

ବାହ୍ୟ ଶୂନ୍ୟ SDL_SendScreenKeyboardShown(ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_SendScreenKeyboardHidden(ଶୂନ୍ୟ);

#endif // SDL_sysvideo_h_
