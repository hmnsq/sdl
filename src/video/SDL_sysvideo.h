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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_sysvideo_h_
#నిర్వచించు SDL_sysvideo_h_

#అన్తర్భావ <SDL3/SDL_vulkan.h>

#అన్తర్భావ "SDL_surface_c.h"

// The SDL video driver

రకనిర్వచనం నిర్మాణం SDL_VideoDisplay SDL_VideoDisplay;
రకనిర్వచనం నిర్మాణం SDL_VideoDevice SDL_VideoDevice;
రకనిర్వచనం నిర్మాణం SDL_Video_దత్తాంశం SDL_Video_దత్తాంశం;
రకనిర్వచనం నిర్మాణం SDL_Display_దత్తాంశం SDL_Display_దత్తాంశం;
రకనిర్వచనం నిర్మాణం SDL_కిటికీ_దత్తాంశం SDL_కిటికీ_దత్తాంశం;

రకనిర్వచనం నిర్మాణం
{
    దశాంశం SDR_white_level;
    దశాంశం HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
నిర్మాణం SDL_కిటికీ
{
    SDL_కిటికీ_ID id;
    అక్షరం *title;
    SDL_Surface *icon;
    పూర్ణాంకం x, y;
    పూర్ణాంకం w, h;
    పూర్ణాంకం min_w, min_h;
    పూర్ణాంకం max_w, max_h;
    దశాంశం min_aspect;
    దశాంశం max_aspect;
    పూర్ణాంకం చివరి_pixel_w, చివరి_pixel_h;
    SDL_కిటికీ_Flags flags;
    SDL_కిటికీ_Flags pending_flags;
    దశాంశం display_scale;
    bool external_graphics_context;
    bool fullscreen_exclusive;  // The window is currently fullscreen exclusive
    SDL_DisplayID చివరి_fullscreen_exclusive_display;  // The last fullscreen_exclusive display
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

    SDL_Display_బహుళకం requested_fullscreen_బహుళకం;
    SDL_Display_బహుళకం current_fullscreen_బహుళకం;
    SDL_HDROutputProperties HDR;

    దశాంశం opacity;

    SDL_Surface *surface;
    bool surface_valid;

    bool is_hiding;
    bool restore_on_show; // Child was hidden recursively by the parent, restore when shown.
    bool చివరి_position_pending; // This should NOT be cleared by the backend, as it is used for fullscreen positioning.
    bool చివరి_కొలత_pending; // This should be cleared by the backend if the new size cannot be applied.
    bool update_fullscreen_on_display_మారింది;
    bool constrain_popup;
    bool is_destroying;
    bool is_dropping; // drag/drop in progress, expecting SDL_SendDropComplete().

    పూర్ణాంకం సురక్షిత_inset_ఎడమ;
    పూర్ణాంకం సురక్షిత_inset_కుడి;
    పూర్ణాంకం సురక్షిత_inset_శిఖరం;
    పూర్ణాంకం సురక్షిత_inset_bottom;
    SDL_Rect సురక్షిత_rect;

    SDL_PropertiesID పాఠ్యం_ఆదానం_props;
    bool పాఠ్యం_ఆదానం_చురుకైన;
    SDL_Rect పాఠ్యం_ఆదానం_rect;
    పూర్ణాంకం పాఠ్యం_ఆదానం_cursor;

    SDL_Rect mouse_rect;

    SDL_తగిలింది_Test తగిలింది_test;
    శూన్య *తగిలింది_test_దత్తాంశం;

    SDL_పురోగతి_State పురోగతి_state;
    దశాంశం పురోగతి_విలువ;

    SDL_PropertiesID props;

    పూర్ణాంకం అంకె_renderers;
    SDL_Renderer **renderers;

    SDL_కిటికీ_దత్తాంశం *అంతర్గత;

    // If a toplevel window, holds the current keyboard focus for grabbing popups.
    SDL_కిటికీ *keyboard_focus;

    SDL_కిటికీ *prev;
    SDL_కిటికీ *తదుపరి;

    SDL_కిటికీ *మాతృ;
    SDL_కిటికీ *మొదటి_బిడ్డ;
    SDL_కిటికీ *prev_sibling;
    SDL_కిటికీ *తదుపరి_sibling;
};
#నిర్వచించు SDL_కిటికీ_FULLSCREEN_VISIBLE(W)        \
    ((((W)->flags & SDL_కిటికీ_FULLSCREEN) != 0) &&   \
     (((W)->flags & SDL_కిటికీ_HIDDEN) == 0) && \
     (((W)->flags & SDL_కిటికీ_MINIMIZED) == 0))

#నిర్వచించు SDL_కిటికీ_IS_POPUP(W) \
    (((W)->flags & (SDL_కిటికీ_TOOLTIP | SDL_కిటికీ_POPUP_MENU)) != 0)

/*
 * Define the SDL display structure.
 * This corresponds to physical monitors attached to the system.
 */
నిర్మాణం SDL_VideoDisplay
{
    SDL_DisplayID id;
    అక్షరం *name;
    పూర్ణాంకం max_fullscreen_modes;
    పూర్ణాంకం అంకె_fullscreen_modes;
    SDL_Display_బహుళకం *fullscreen_modes;
    SDL_Display_బహుళకం desktop_బహుళకం;
    స్థిరరాశి SDL_Display_బహుళకం *current_బహుళకం;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    దశాంశం content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_చురుకైన;
    SDL_కిటికీ *fullscreen_కిటికీ;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_Display_దత్తాంశం *అంతర్గత;
};

// Video device flags
రకనిర్వచనం గణన
{
    VIDEO_DEVICE_CAPS_బహుళకం_SWITCHING_EMULATED = 0x01,
    VIDEO_DEVICE_CAPS_HAS_POPUP_కిటికీ_SUPPORT = 0x02,
    VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS = 0x04,
    VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY = 0x08,
    VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES = 0x10,
    VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES = 0x20,
    VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER = 0x40
} DeviceCaps;

// Fullscreen operations
రకనిర్వచనం గణన
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

రకనిర్వచనం గణన
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_Fullscreen_ఫలితం;

నిర్మాణం SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    స్థిరరాశి అక్షరం *name;

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
    శూన్య (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    శూన్య (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    శూన్య (*RefreshDisplays)(SDL_VideoDevice *_this);

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
    bool (*సమితి_Display_బహుళకం)(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);

    /* * * */
    /*
     * Window functions
     */
    bool (*CreateSDLWindow)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
    శూన్య (*సమితి_కిటికీ_Title)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*సమితి_కిటికీ_Icon)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *icon);
    bool (*సమితి_కిటికీ_Position)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*సమితి_కిటికీ_కొలత)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*సమితి_కిటికీ_Minimum_కొలత)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*సమితి_కిటికీ_గరిష్ఠ_కొలత)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*సమితి_కిటికీ_Aspect_నిష్పత్తి)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*Get_కిటికీ_Borders_కొలత)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *శిఖరం, పూర్ణాంకం *ఎడమ, పూర్ణాంకం *bottom, పూర్ణాంకం *కుడి);
    దశాంశం (*Get_కిటికీ_Content_Scale)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*Get_కిటికీ_కొలత_లోపల_Pixels)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *w, పూర్ణాంకం *h);
    bool (*సమితి_కిటికీ_Opacity)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, దశాంశం opacity);
    bool (*సమితి_కిటికీ_మాతృ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_కిటికీ *మాతృ);
    bool (*సమితి_కిటికీ_Modal)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool modal);
    శూన్య (*Show_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*Hide_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*Raise_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*Maximize_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*Minimize_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*Restore_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*సమితి_కిటికీ_Bordered)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool bordered);
    శూన్య (*సమితి_కిటికీ_Resizable)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool resizable);
    శూన్య (*సమితి_కిటికీ_Always_On_శిఖరం)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool on_శిఖరం);
    SDL_Fullscreen_ఫలితం (*సమితి_కిటికీ_Fullscreen)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    శూన్య *(*Get_కిటికీ_ICCProfile)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, size_t *కొలత);
    SDL_DisplayID (*Get_Display_For_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*సమితి_కిటికీ_Mouse_Rect)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*సమితి_కిటికీ_Mouse_Grab)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed);
    bool (*సమితి_కిటికీ_Keyboard_Grab)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed);
    శూన్య (*Destroy_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*Create_కిటికీ_Framebuffer)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PixelFormat *format, శూన్య **pixels, పూర్ణాంకం *pitch);
    bool (*సమితి_కిటికీ_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం vsync);
    bool (*Get_కిటికీ_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *vsync);
    bool (*Update_కిటికీ_Framebuffer)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rects, పూర్ణాంకం numrects);
    శూన్య (*Destroy_కిటికీ_Framebuffer)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*On_కిటికీ_Enter)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*Update_కిటికీ_Shape)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *shape);
    bool (*Flash_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_FlashOperation operation);
    bool (*Apply_కిటికీ_పురోగతి)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*సమితి_కిటికీ_Focusable)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool focusable);
    bool (*సమితి_కిటికీ_Fill_Document)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool fill);
    bool (*Sync_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*Reconfigure_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_కిటికీ_Flags flags);

    /* * * */
    /*
     * OpenGL support
     */
    bool (*GL_ఎక్కించు_Library)(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
    SDL_Function_సూచిక (*GL_Get_Proc_చిరునామా)(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc);
    శూన్య (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*GL_సమితి_మార్పిడి_Interval)(SDL_VideoDevice *_this, పూర్ణాంకం interval);
    bool (*GL_Get_మార్పిడి_Interval)(SDL_VideoDevice *_this, పూర్ణాంకం *interval);
    bool (*GL_మార్పిడి_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    శూన్య (*GL_సమితి_Default_Profile_Config)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_ఎక్కించు_Library)(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
    శూన్య (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    అక్షరం స్థిరరాశి * స్థిరరాశి *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *లెక్క);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, VkInstance instance, స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator, VkSurfaceKHR *surface);
    శూన్య (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 వరుస_Family_సూచీ);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    శూన్య *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    పూర్ణాంకం (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    శూన్య (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*ప్రారంభం_పాఠ్యం_ఆదానం)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props);
    bool (*Stop_పాఠ్యం_ఆదానం)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*Update_పాఠ్యం_ఆదానం_Area)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    శూన్య (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props);
    శూన్య (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
    శూన్య (*సమితి_పాఠ్యం_ఆదానం_Properties)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props);

    // Clipboard
    స్థిరరాశి అక్షరం *స్థిరరాశి *(*Get_పాఠ్యం_Mime_Types)(SDL_VideoDevice *_this, size_t *అంకె_mime_types);
    bool (*సమితి_Clipboard_దత్తాంశం)(SDL_VideoDevice *_this);
    శూన్య *(*Get_Clipboard_దత్తాంశం)(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type, size_t *కొలత);
    bool (*Has_Clipboard_దత్తాంశం)(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*సమితి_Clipboard_పాఠ్యం)(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *పాఠ్యం);
    అక్షరం *(*Get_Clipboard_పాఠ్యం)(SDL_VideoDevice *_this);
    bool (*Has_Clipboard_పాఠ్యం)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*సమితి_Primary_Selection_పాఠ్యం)(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *పాఠ్యం);
    అక్షరం *(*Get_Primary_Selection_పాఠ్యం)(SDL_VideoDevice *_this);
    bool (*Has_Primary_Selection_పాఠ్యం)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*Show_సందేశం_Box)(SDL_VideoDevice *_this, స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonID);

    // Hit-testing
    bool (*సమితి_కిటికీ_తగిలింది_Test)(SDL_కిటికీ *కిటికీ, bool enabled);

    // Tell window that app enabled drag'n'drop events
    శూన్య (*AcceptDragAndDrop)(SDL_కిటికీ *కిటికీ, bool accept);

    // Display the system-level window menu
    శూన్య (*Show_కిటికీ_System_Menu)(SDL_కిటికీ *కిటికీ, పూర్ణాంకం x, పూర్ణాంకం y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    శూన్య *wakeup_కిటికీ;
    పూర్ణాంకం అంకె_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_కిటికీ *windows;
    SDL_కిటికీ *grabbed_కిటికీ;
    Uint32 clipboard_sequence;
    SDL_Clipboard_దత్తాంశం_Callback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    శూన్య *clipboard_userdata;
    అక్షరం **clipboard_mime_types;
    size_t అంకె_clipboard_mime_types;
    అక్షరం *primary_selection_పాఠ్యం;
    bool setting_display_బహుళకం;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    నిర్మాణం
    {
        పూర్ణాంకం red_కొలత;
        పూర్ణాంకం green_కొలత;
        పూర్ణాంకం blue_కొలత;
        పూర్ణాంకం alpha_కొలత;
        పూర్ణాంకం లోతు_కొలత;
        పూర్ణాంకం బఫరు_కొలత;
        పూర్ణాంకం stencil_కొలత;
        పూర్ణాంకం double_బఫరు;
        పూర్ణాంకం accum_red_కొలత;
        పూర్ణాంకం accum_green_కొలత;
        పూర్ణాంకం accum_blue_కొలత;
        పూర్ణాంకం accum_alpha_కొలత;
        పూర్ణాంకం stereo;
        పూర్ణాంకం multisamplebuffers;
        పూర్ణాంకం multisamplesamples;
        పూర్ణాంకం floatbuffers;
        పూర్ణాంకం accelerated;
        పూర్ణాంకం major_సంస్కరణ;
        పూర్ణాంకం minor_సంస్కరణ;
        పూర్ణాంకం flags;
        పూర్ణాంకం profile_ముసుగు;
        పూర్ణాంకం share_with_current_context;
        పూర్ణాంకం release_behavior;
        పూర్ణాంకం reset_notification;
        పూర్ణాంకం framebuffer_srgb_capable;
        పూర్ణాంకం no_error;
        పూర్ణాంకం retained_backing;
        పూర్ణాంకం egl_platform;
        పూర్ణాంకం driver_loaded;
        పూర్ణాంకం HAS_GL_ARB_color_బఫరు_float;
        అక్షరం driver_మార్గం[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    శూన్య *egl_attrib_callback_userdata;

    /* * * */
    // Cache current GL context; don't call the OS when it hasn't changed.
    /* We have the global pointers here so Cocoa continues to work the way
       it always has, and the thread-local storage for the general case.
     */
    SDL_కిటికీ *current_glwin;
    SDL_GLContext current_glctx;
    SDL_TLSID current_glwin_tls;
    SDL_TLSID current_glctx_tls;

    /* Flag that stores whether it's allowed to call SDL_GL_MakeCurrent()
     * with a NULL window, but a non-NULL context. (Not allowed in most cases,
     * except on EGL under some circumstances.) */
    bool gl_allow_no_surface;

    /* * * */
    // Data used by the Vulkan drivers
    నిర్మాణం
    {
        SDL_Function_సూచిక vkGetInstanceProcAddr;
        SDL_Function_సూచిక vkEnumerateInstanceExtensionProperties;
        పూర్ణాంకం loader_loaded;
        అక్షరం loader_మార్గం[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_Video_దత్తాంశం *అంతర్గత;
    నిర్మాణం SDL_GLDriver_దత్తాంశం *gl_దత్తాంశం;

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    నిర్మాణం SDL_EGL_Video_దత్తాంశం *egl_దత్తాంశం;
#అయితే_ముగింపు

#ఒకవేళ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    నిర్మాణం SDL_వ్యక్తిగత_GLESData *gles_దత్తాంశం;
#అయితే_ముగింపు

    /* * * */
    // The function used to dispose of this structure
    శూన్య (*విడుదల)(SDL_VideoDevice *_this);
};

రకనిర్వచనం నిర్మాణం VideoBootStrap
{
    స్థిరరాశి అక్షరం *name;
    స్థిరరాశి అక్షరం *desc;
    SDL_VideoDevice *(*create)(శూన్య);
    bool (*Show_సందేశం_Box)(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
బాహ్య VideoBootStrap వ్యక్తిగత_bootstrap;
బాహ్య VideoBootStrap COCOA_bootstrap;
బాహ్య VideoBootStrap X11_bootstrap;
బాహ్య VideoBootStrap WINDOWS_bootstrap;
బాహ్య VideoBootStrap HAIKU_bootstrap;
బాహ్య VideoBootStrap UIKIT_bootstrap;
బాహ్య VideoBootStrap Android_bootstrap;
బాహ్య VideoBootStrap OPENHARMONY_bootstrap;
బాహ్య VideoBootStrap PS2_bootstrap;
బాహ్య VideoBootStrap PSP_bootstrap;
బాహ్య VideoBootStrap VITA_bootstrap;
బాహ్య VideoBootStrap RISCOS_bootstrap;
బాహ్య VideoBootStrap N3DS_bootstrap;
బాహ్య VideoBootStrap NGAGE_bootstrap;
బాహ్య VideoBootStrap RPI_bootstrap;
బాహ్య VideoBootStrap KMSDRM_bootstrap;
బాహ్య VideoBootStrap DUMMY_bootstrap;
బాహ్య VideoBootStrap DUMMY_evdev_bootstrap;
బాహ్య VideoBootStrap Wayland_preferred_bootstrap;
బాహ్య VideoBootStrap Wayland_bootstrap;
బాహ్య VideoBootStrap VIVANTE_bootstrap;
బాహ్య VideoBootStrap Emscripten_bootstrap;
బాహ్య VideoBootStrap OFFSCREEN_bootstrap;
బాహ్య VideoBootStrap QNX_bootstrap;
బాహ్య VideoBootStrap OPENVR_bootstrap;
బాహ్య VideoBootStrap DOSVESA_bootstrap;

బాహ్య bool SDL_UninitializedVideo(శూన్య);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
బాహ్య bool SDL_OnVideoThread(శూన్య);
బాహ్య SDL_VideoDevice *SDL_GetVideoDevice(శూన్య);
బాహ్య శూన్య SDL_సమితి_System_Theme(SDL_SystemTheme theme);
బాహ్య SDL_DisplayID SDL_కూడు_Basic_Video_Display(స్థిరరాశి SDL_Display_బహుళకం *desktop_బహుళకం);
బాహ్య SDL_DisplayID SDL_కూడు_Video_Display(స్థిరరాశి SDL_VideoDisplay *display, bool send_event);
బాహ్య శూన్య SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
బాహ్య bool SDL_కూడు_Fullscreen_Display_బహుళకం(SDL_VideoDisplay *display, స్థిరరాశి SDL_Display_బహుళకం *బహుళకం);
బాహ్య శూన్య SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
బాహ్య శూన్య SDL_సమితి_Desktop_Display_బహుళకం(SDL_VideoDisplay *display, స్థిరరాశి SDL_Display_బహుళకం *బహుళకం);
బాహ్య శూన్య SDL_సమితి_Current_Display_బహుళకం(SDL_VideoDisplay *display, స్థిరరాశి SDL_Display_బహుళకం *బహుళకం);
బాహ్య శూన్య SDL_సమితి_Display_Content_Scale(SDL_VideoDisplay *display, దశాంశం scale);
బాహ్య శూన్య SDL_సమితి_Display_HDRProperties(SDL_VideoDisplay *display, స్థిరరాశి SDL_HDROutputProperties *HDR);
బాహ్య bool SDL_సమితి_Display_బహుళకం_For_Display(SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);
బాహ్య SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
బాహ్య SDL_DisplayID SDL_Get_Display_For_కిటికీ_Position(SDL_కిటికీ *కిటికీ);
బాహ్య SDL_VideoDisplay *SDL_Get_Video_Display_For_కిటికీ(SDL_కిటికీ *కిటికీ);
బాహ్య SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_కిటికీ(SDL_కిటికీ *కిటికీ);
బాహ్య పూర్ణాంకం SDL_Get_Display_సూచీ(SDL_DisplayID displayID);
బాహ్య SDL_Display_దత్తాంశం *SDL_Get_Display_Driver_దత్తాంశం(SDL_DisplayID display);
బాహ్య SDL_Display_దత్తాంశం *SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(SDL_కిటికీ *కిటికీ);
బాహ్య పూర్ణాంకం SDL_Get_సందేశం_Box_లెక్క(శూన్య);
బాహ్య శూన్య SDL_సమితి_కిటికీ_HDRProperties(SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_HDROutputProperties *HDR, bool send_event);
బాహ్య శూన్య SDL_సమితి_కిటికీ_సురక్షిత_Area_Insets(SDL_కిటికీ *కిటికీ, పూర్ణాంకం ఎడమ, పూర్ణాంకం కుడి, పూర్ణాంకం శిఖరం, పూర్ణాంకం bottom);

బాహ్య శూన్య SDL_GL_DeduceMaxSupportedESProfile(పూర్ణాంకం *major, పూర్ణాంకం *minor);

బాహ్య bool SDL_Recreate_కిటికీ(SDL_కిటికీ *కిటికీ, SDL_కిటికీ_Flags flags);
బాహ్య bool SDL_Reconfigure_కిటికీ(SDL_కిటికీ *కిటికీ, SDL_కిటికీ_Flags flags);
బాహ్య bool SDL_HasWindows(శూన్య);
బాహ్య శూన్య SDL_Relative_గమ్యం_Global_For_కిటికీ(SDL_కిటికీ *కిటికీ, పూర్ణాంకం rel_x, పూర్ణాంకం rel_y, పూర్ణాంకం *abs_x, పూర్ణాంకం *abs_y);
బాహ్య శూన్య SDL_Global_గమ్యం_Relative_For_కిటికీ(SDL_కిటికీ *కిటికీ, పూర్ణాంకం abs_x, పూర్ణాంకం abs_y, పూర్ణాంకం *rel_x, పూర్ణాంకం *rel_y);
బాహ్య bool SDL_ShouldFocusPopup(SDL_కిటికీ *కిటికీ);
బాహ్య bool SDL_ShouldRelinquishPopupFocus(SDL_కిటికీ *కిటికీ, SDL_కిటికీ **new_focus);

బాహ్య శూన్య SDL_OnDisplayAdded(SDL_VideoDisplay *display);
బాహ్య శూన్య SDL_OnDisplayMoved(SDL_VideoDisplay *display);
బాహ్య శూన్య SDL_On_కిటికీ_Shown(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_Hidden(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_Moved(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_Resized(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_Check_కిటికీ_Pixel_కొలత_మారింది(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_Pixel_కొలత_మారింది(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_సజీవ_Resize_Update(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_Minimized(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_Maximized(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_Restored(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_Enter(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_Leave(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_Focus_Gained(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_Focus_కోల్పోయిన(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_On_కిటికీ_Display_మారింది(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య SDL_Update_కిటికీ_Grab(SDL_కిటికీ *కిటికీ);
బాహ్య bool SDL_Update_Fullscreen_బహుళకం(SDL_కిటికీ *కిటికీ, SDL_FullscreenOp fullscreen, bool commit);
బాహ్య SDL_కిటికీ *SDL_GetToplevelForKeyboardFocus(శూన్య);

బాహ్య bool SDL_ShouldAllowTopmost(శూన్య);

బాహ్య శూన్య SDL_ToggleDragAndDropSupport(శూన్య);

బాహ్య శూన్య SDL_UpdateDesktopBounds(శూన్య);

బాహ్య SDL_పాఠ్యం_ఆదానం_Type SDL_Get_పాఠ్యం_ఆదానం_Type(SDL_PropertiesID props);
బాహ్య SDL_Capitalization SDL_Get_పాఠ్యం_ఆదానం_Capitalization(SDL_PropertiesID props);
బాహ్య bool SDL_Get_పాఠ్యం_ఆదానం_Autocorrect(SDL_PropertiesID props);
బాహ్య bool SDL_Get_పాఠ్యం_ఆదానం_Multiline(SDL_PropertiesID props);

బాహ్య శూన్య SDL_SendScreenKeyboardShown(శూన్య);
బాహ్య శూన్య SDL_SendScreenKeyboardHidden(శూన్య);

#అయితే_ముగింపు // SDL_sysvideo_h_
