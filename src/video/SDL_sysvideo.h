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

#यदि_अपरिभाषितम् SDL_sysvideo_h_
#परिभाषय SDL_sysvideo_h_

#अन्तर्भाव <SDL3/SDL_vulkan.h>

#अन्तर्भाव "SDL_surface_c.h"

// The SDL video driver

प्रकारनिर्देश संरचना SDL_VideoDisplay SDL_VideoDisplay;
प्रकारनिर्देश संरचना SDL_VideoDevice SDL_VideoDevice;
प्रकारनिर्देश संरचना SDL_Video_दत्त SDL_Video_दत्त;
प्रकारनिर्देश संरचना SDL_Display_दत्त SDL_Display_दत्त;
प्रकारनिर्देश संरचना SDL_गवाक्षः_दत्त SDL_गवाक्षः_दत्त;

प्रकारनिर्देश संरचना
{
    भिन्न SDR_white_level;
    भिन्न HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
संरचना SDL_गवाक्षः
{
    SDL_गवाक्षः_ID id;
    वर्ण *title;
    SDL_Surface *icon;
    पूर्णाङ्क x, y;
    पूर्णाङ्क w, h;
    पूर्णाङ्क min_w, min_h;
    पूर्णाङ्क max_w, max_h;
    भिन्न min_aspect;
    भिन्न max_aspect;
    पूर्णाङ्क चरमः_pixel_w, चरमः_pixel_h;
    SDL_गवाक्षः_Flags flags;
    SDL_गवाक्षः_Flags pending_flags;
    भिन्न display_scale;
    bool external_graphics_context;
    bool fullscreen_exclusive;  // The window is currently fullscreen exclusive
    SDL_DisplayID चरमः_fullscreen_exclusive_display;  // The last fullscreen_exclusive display
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

    SDL_Display_बहुलकम् requested_fullscreen_बहुलकम्;
    SDL_Display_बहुलकम् current_fullscreen_बहुलकम्;
    SDL_HDROutputProperties HDR;

    भिन्न opacity;

    SDL_Surface *surface;
    bool surface_valid;

    bool is_hiding;
    bool restore_on_show; // Child was hidden recursively by the parent, restore when shown.
    bool चरमः_position_pending; // This should NOT be cleared by the backend, as it is used for fullscreen positioning.
    bool चरमः_आकार_pending; // This should be cleared by the backend if the new size cannot be applied.
    bool update_fullscreen_on_display_परिवर्तितम्;
    bool constrain_popup;
    bool is_destroying;
    bool is_dropping; // drag/drop in progress, expecting SDL_SendDropComplete().

    पूर्णाङ्क safe_inset_वामः;
    पूर्णाङ्क safe_inset_दक्षिणः;
    पूर्णाङ्क safe_inset_शिखरम्;
    पूर्णाङ्क safe_inset_bottom;
    SDL_Rect safe_rect;

    SDL_PropertiesID text_निवेशः_props;
    bool text_निवेशः_सक्रिय;
    SDL_Rect text_निवेशः_rect;
    पूर्णाङ्क text_निवेशः_cursor;

    SDL_Rect mouse_rect;

    SDL_लब्धम्_Test लब्धम्_test;
    शून्य *लब्धम्_test_दत्त;

    SDL_प्रगतिः_State प्रगतिः_state;
    भिन्न प्रगतिः_मानम्;

    SDL_PropertiesID props;

    पूर्णाङ्क अङ्कः_renderers;
    SDL_Renderer **renderers;

    SDL_गवाक्षः_दत्त *आन्तरिकम्;

    // If a toplevel window, holds the current keyboard focus for grabbing popups.
    SDL_गवाक्षः *keyboard_focus;

    SDL_गवाक्षः *पूर्व;
    SDL_गवाक्षः *अग्र;

    SDL_गवाक्षः *parent;
    SDL_गवाक्षः *first_child;
    SDL_गवाक्षः *पूर्व_sibling;
    SDL_गवाक्षः *अग्र_sibling;
};
#परिभाषय SDL_गवाक्षः_FULLSCREEN_VISIBLE(W)        \
    ((((W)->flags & SDL_गवाक्षः_FULLSCREEN) != 0) &&   \
     (((W)->flags & SDL_गवाक्षः_HIDDEN) == 0) && \
     (((W)->flags & SDL_गवाक्षः_MINIMIZED) == 0))

#परिभाषय SDL_गवाक्षः_IS_POPUP(W) \
    (((W)->flags & (SDL_गवाक्षः_TOOLTIP | SDL_गवाक्षः_POPUP_MENU)) != 0)

/*
 * Define the SDL display structure.
 * This corresponds to physical monitors attached to the system.
 */
संरचना SDL_VideoDisplay
{
    SDL_DisplayID id;
    वर्ण *name;
    पूर्णाङ्क max_fullscreen_modes;
    पूर्णाङ्क अङ्कः_fullscreen_modes;
    SDL_Display_बहुलकम् *fullscreen_modes;
    SDL_Display_बहुलकम् desktop_बहुलकम्;
    ध्रुव SDL_Display_बहुलकम् *current_बहुलकम्;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    भिन्न content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_सक्रिय;
    SDL_गवाक्षः *fullscreen_गवाक्षः;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_Display_दत्त *आन्तरिकम्;
};

// Video device flags
प्रकारनिर्देश गणना
{
    VIDEO_DEVICE_CAPS_बहुलकम्_SWITCHING_EMULATED = 0x01,
    VIDEO_DEVICE_CAPS_HAS_POPUP_गवाक्षः_SUPPORT = 0x02,
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
} SDL_Fullscreen_परिणाम;

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
    bool (*समुच्चयः_Display_बहुलकम्)(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्);

    /* * * */
    /*
     * Window functions
     */
    bool (*CreateSDLWindow)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
    शून्य (*समुच्चयः_गवाक्षः_Title)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*समुच्चयः_गवाक्षः_Icon)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *icon);
    bool (*समुच्चयः_गवाक्षः_Position)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*समुच्चयः_गवाक्षः_आकार)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*समुच्चयः_गवाक्षः_Minimum_आकार)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*समुच्चयः_गवाक्षः_अधिकतमम्_आकार)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*समुच्चयः_गवाक्षः_Aspect_अनुपातः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*Get_गवाक्षः_Borders_आकार)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *शिखरम्, पूर्णाङ्क *वामः, पूर्णाङ्क *bottom, पूर्णाङ्क *दक्षिणः);
    भिन्न (*Get_गवाक्षः_Content_Scale)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*Get_गवाक्षः_आकार_अन्तर्_Pixels)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *w, पूर्णाङ्क *h);
    bool (*समुच्चयः_गवाक्षः_Opacity)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, भिन्न opacity);
    bool (*समुच्चयः_गवाक्षः_Parent)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः *parent);
    bool (*समुच्चयः_गवाक्षः_Modal)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool modal);
    शून्य (*Show_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*Hide_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*Raise_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*Maximize_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*Minimize_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*Restore_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*समुच्चयः_गवाक्षः_Bordered)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool bordered);
    शून्य (*समुच्चयः_गवाक्षः_Resizable)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool resizable);
    शून्य (*समुच्चयः_गवाक्षः_Always_On_शिखरम्)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool on_शिखरम्);
    SDL_Fullscreen_परिणाम (*समुच्चयः_गवाक्षः_Fullscreen)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    शून्य *(*Get_गवाक्षः_ICCProfile)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, size_t *आकार);
    SDL_DisplayID (*Get_Display_For_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*समुच्चयः_गवाक्षः_Mouse_Rect)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*समुच्चयः_गवाक्षः_Mouse_Grab)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed);
    bool (*समुच्चयः_गवाक्षः_Keyboard_Grab)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed);
    शून्य (*Destroy_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*Create_गवाक्षः_Framebuffer)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PixelFormat *format, शून्य **pixels, पूर्णाङ्क *pitch);
    bool (*समुच्चयः_गवाक्षः_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क vsync);
    bool (*Get_गवाक्षः_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *vsync);
    bool (*Update_गवाक्षः_Framebuffer)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rects, पूर्णाङ्क numrects);
    शून्य (*Destroy_गवाक्षः_Framebuffer)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*On_गवाक्षः_Enter)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*Update_गवाक्षः_Shape)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *shape);
    bool (*Flash_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_FlashOperation operation);
    bool (*Apply_गवाक्षः_प्रगतिः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*समुच्चयः_गवाक्षः_Focusable)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool focusable);
    bool (*समुच्चयः_गवाक्षः_Fill_Document)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool fill);
    bool (*Sync_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*Reconfigure_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः_Flags flags);

    /* * * */
    /*
     * OpenGL support
     */
    bool (*GL_आरोपय_Library)(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);
    SDL_FunctionPointer (*GL_Get_Proc_स्थानाङ्कः)(SDL_VideoDevice *_this, ध्रुव वर्ण *proc);
    शून्य (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*GL_समुच्चयः_Swap_Interval)(SDL_VideoDevice *_this, पूर्णाङ्क interval);
    bool (*GL_GetSwapInterval)(SDL_VideoDevice *_this, पूर्णाङ्क *interval);
    bool (*GL_Swap_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    शून्य (*GL_समुच्चयः_Default_Profile_Config)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_आरोपय_Library)(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);
    शून्य (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    वर्ण ध्रुव * ध्रुव *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *गणनम्);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, VkInstance instance, ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator, VkSurfaceKHR *surface);
    शून्य (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 queue_Family_सूचकांक);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    शून्य *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    पूर्णाङ्क (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    शून्य (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*Start_Text_निवेशः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props);
    bool (*Stop_Text_निवेशः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*Update_Text_निवेशः_Area)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    शून्य (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props);
    शून्य (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
    शून्य (*समुच्चयः_Text_निवेशः_Properties)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props);

    // Clipboard
    ध्रुव वर्ण *ध्रुव *(*GetTextMimeTypes)(SDL_VideoDevice *_this, size_t *अङ्कः_mime_types);
    bool (*समुच्चयः_Clipboard_दत्त)(SDL_VideoDevice *_this);
    शून्य *(*Get_Clipboard_दत्त)(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type, size_t *आकार);
    bool (*Has_Clipboard_दत्त)(SDL_VideoDevice *_this, ध्रुव वर्ण *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*समुच्चयः_Clipboard_Text)(SDL_VideoDevice *_this, ध्रुव वर्ण *text);
    वर्ण *(*GetClipboardText)(SDL_VideoDevice *_this);
    bool (*HasClipboardText)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*समुच्चयः_Primary_Selection_Text)(SDL_VideoDevice *_this, ध्रुव वर्ण *text);
    वर्ण *(*GetPrimarySelectionText)(SDL_VideoDevice *_this);
    bool (*HasPrimarySelectionText)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*Show_सन्देशः_Box)(SDL_VideoDevice *_this, ध्रुव SDL_सन्देशः_Box_दत्त *messageboxdata, पूर्णाङ्क *buttonID);

    // Hit-testing
    bool (*समुच्चयः_गवाक्षः_लब्धम्_Test)(SDL_गवाक्षः *गवाक्षः, bool enabled);

    // Tell window that app enabled drag'n'drop events
    शून्य (*AcceptDragAndDrop)(SDL_गवाक्षः *गवाक्षः, bool accept);

    // Display the system-level window menu
    शून्य (*Show_गवाक्षः_System_Menu)(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क x, पूर्णाङ्क y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    शून्य *wakeup_गवाक्षः;
    पूर्णाङ्क अङ्कः_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_गवाक्षः *windows;
    SDL_गवाक्षः *grabbed_गवाक्षः;
    Uint32 clipboard_sequence;
    SDL_Clipboard_दत्त_Callback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    शून्य *clipboard_userdata;
    वर्ण **clipboard_mime_types;
    size_t अङ्कः_clipboard_mime_types;
    वर्ण *primary_selection_text;
    bool setting_display_बहुलकम्;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    संरचना
    {
        पूर्णाङ्क red_आकार;
        पूर्णाङ्क green_आकार;
        पूर्णाङ्क blue_आकार;
        पूर्णाङ्क alpha_आकार;
        पूर्णाङ्क गभीरता_आकार;
        पूर्णाङ्क बफर_आकार;
        पूर्णाङ्क stencil_आकार;
        पूर्णाङ्क double_बफर;
        पूर्णाङ्क accum_red_आकार;
        पूर्णाङ्क accum_green_आकार;
        पूर्णाङ्क accum_blue_आकार;
        पूर्णाङ्क accum_alpha_आकार;
        पूर्णाङ्क stereo;
        पूर्णाङ्क multisamplebuffers;
        पूर्णाङ्क multisamplesamples;
        पूर्णाङ्क floatbuffers;
        पूर्णाङ्क accelerated;
        पूर्णाङ्क major_संस्करणम्;
        पूर्णाङ्क minor_संस्करणम्;
        पूर्णाङ्क flags;
        पूर्णाङ्क profile_आवरणम्;
        पूर्णाङ्क share_with_current_context;
        पूर्णाङ्क release_behavior;
        पूर्णाङ्क reset_notification;
        पूर्णाङ्क framebuffer_srgb_capable;
        पूर्णाङ्क no_error;
        पूर्णाङ्क retained_backing;
        पूर्णाङ्क egl_platform;
        पूर्णाङ्क driver_loaded;
        पूर्णाङ्क HAS_GL_ARB_color_बफर_float;
        वर्ण driver_मार्गः[256];
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
    SDL_गवाक्षः *current_glwin;
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
        वर्ण loader_मार्गः[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_Video_दत्त *आन्तरिकम्;
    संरचना SDL_GLDriver_दत्त *gl_दत्त;

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    संरचना SDL_EGL_Video_दत्त *egl_दत्त;
#यदि_अन्तः

#यदि defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    संरचना SDL_वैयक्तिकम्_GLESData *gles_दत्त;
#यदि_अन्तः

    /* * * */
    // The function used to dispose of this structure
    शून्य (*मुक्त)(SDL_VideoDevice *_this);
};

प्रकारनिर्देश संरचना VideoBootStrap
{
    ध्रुव वर्ण *name;
    ध्रुव वर्ण *desc;
    SDL_VideoDevice *(*create)(शून्य);
    bool (*Show_सन्देशः_Box)(ध्रुव SDL_सन्देशः_Box_दत्त *messageboxdata, पूर्णाङ्क *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
बाह्य VideoBootStrap वैयक्तिकम्_bootstrap;
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
बाह्य शून्य SDL_समुच्चयः_System_Theme(SDL_SystemTheme theme);
बाह्य SDL_DisplayID SDL_सङ्कलय_Basic_Video_Display(ध्रुव SDL_Display_बहुलकम् *desktop_बहुलकम्);
बाह्य SDL_DisplayID SDL_सङ्कलय_Video_Display(ध्रुव SDL_VideoDisplay *display, bool send_event);
बाह्य शून्य SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
बाह्य bool SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(SDL_VideoDisplay *display, ध्रुव SDL_Display_बहुलकम् *बहुलकम्);
बाह्य शून्य SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
बाह्य शून्य SDL_समुच्चयः_Desktop_Display_बहुलकम्(SDL_VideoDisplay *display, ध्रुव SDL_Display_बहुलकम् *बहुलकम्);
बाह्य शून्य SDL_समुच्चयः_Current_Display_बहुलकम्(SDL_VideoDisplay *display, ध्रुव SDL_Display_बहुलकम् *बहुलकम्);
बाह्य शून्य SDL_समुच्चयः_Display_Content_Scale(SDL_VideoDisplay *display, भिन्न scale);
बाह्य शून्य SDL_समुच्चयः_Display_HDRProperties(SDL_VideoDisplay *display, ध्रुव SDL_HDROutputProperties *HDR);
बाह्य bool SDL_समुच्चयः_Display_बहुलकम्_For_Display(SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्);
बाह्य SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
बाह्य SDL_DisplayID SDL_Get_Display_For_गवाक्षः_Position(SDL_गवाक्षः *गवाक्षः);
बाह्य SDL_VideoDisplay *SDL_Get_Video_Display_For_गवाक्षः(SDL_गवाक्षः *गवाक्षः);
बाह्य SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_गवाक्षः(SDL_गवाक्षः *गवाक्षः);
बाह्य पूर्णाङ्क SDL_Get_Display_सूचकांक(SDL_DisplayID displayID);
बाह्य SDL_Display_दत्त *SDL_Get_Display_Driver_दत्त(SDL_DisplayID display);
बाह्य SDL_Display_दत्त *SDL_Get_Display_Driver_दत्त_For_गवाक्षः(SDL_गवाक्षः *गवाक्षः);
बाह्य पूर्णाङ्क SDL_Get_सन्देशः_Box_गणनम्(शून्य);
बाह्य शून्य SDL_समुच्चयः_गवाक्षः_HDRProperties(SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_HDROutputProperties *HDR, bool send_event);
बाह्य शून्य SDL_समुच्चयः_गवाक्षः_Safe_Area_Insets(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क वामः, पूर्णाङ्क दक्षिणः, पूर्णाङ्क शिखरम्, पूर्णाङ्क bottom);

बाह्य शून्य SDL_GL_DeduceMaxSupportedESProfile(पूर्णाङ्क *major, पूर्णाङ्क *minor);

बाह्य bool SDL_Recreate_गवाक्षः(SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः_Flags flags);
बाह्य bool SDL_Reconfigure_गवाक्षः(SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः_Flags flags);
बाह्य bool SDL_HasWindows(शून्य);
बाह्य शून्य SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क rel_x, पूर्णाङ्क rel_y, पूर्णाङ्क *abs_x, पूर्णाङ्क *abs_y);
बाह्य शून्य SDL_Global_गन्तव्यम्_Relative_For_गवाक्षः(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क abs_x, पूर्णाङ्क abs_y, पूर्णाङ्क *rel_x, पूर्णाङ्क *rel_y);
बाह्य bool SDL_ShouldFocusPopup(SDL_गवाक्षः *गवाक्षः);
बाह्य bool SDL_ShouldRelinquishPopupFocus(SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः **new_focus);

बाह्य शून्य SDL_OnDisplayAdded(SDL_VideoDisplay *display);
बाह्य शून्य SDL_OnDisplayMoved(SDL_VideoDisplay *display);
बाह्य शून्य SDL_On_गवाक्षः_Shown(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_Hidden(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_Moved(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_Resized(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_Check_गवाक्षः_Pixel_आकार_परिवर्तितम्(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_Pixel_आकार_परिवर्तितम्(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_जीवितम्_Resize_Update(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_Minimized(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_Maximized(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_Restored(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_Enter(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_Leave(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_Focus_Gained(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_Focus_नष्टम्(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_On_गवाक्षः_Display_परिवर्तितम्(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य SDL_Update_गवाक्षः_Grab(SDL_गवाक्षः *गवाक्षः);
बाह्य bool SDL_Update_Fullscreen_बहुलकम्(SDL_गवाक्षः *गवाक्षः, SDL_FullscreenOp fullscreen, bool commit);
बाह्य SDL_गवाक्षः *SDL_GetToplevelForKeyboardFocus(शून्य);

बाह्य bool SDL_ShouldAllowTopmost(शून्य);

बाह्य शून्य SDL_ToggleDragAndDropSupport(शून्य);

बाह्य शून्य SDL_UpdateDesktopBounds(शून्य);

बाह्य SDL_Text_निवेशः_Type SDL_Get_Text_निवेशः_Type(SDL_PropertiesID props);
बाह्य SDL_Capitalization SDL_Get_Text_निवेशः_Capitalization(SDL_PropertiesID props);
बाह्य bool SDL_Get_Text_निवेशः_Autocorrect(SDL_PropertiesID props);
बाह्य bool SDL_Get_Text_निवेशः_Multiline(SDL_PropertiesID props);

बाह्य शून्य SDL_SendScreenKeyboardShown(शून्य);
बाह्य शून्य SDL_SendScreenKeyboardHidden(शून्य);

#यदि_अन्तः // SDL_sysvideo_h_
