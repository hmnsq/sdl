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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_sysvideo_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_sysvideo_h_

#ಅನ್ತರ್ಭಾವ <SDL3/SDL_vulkan.h>

#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"

// The SDL video driver

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_VideoDisplay SDL_VideoDisplay;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_VideoDevice SDL_VideoDevice;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_Video_ದತ್ತಾಂಶ SDL_Video_ದತ್ತಾಂಶ;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_Display_ದತ್ತಾಂಶ SDL_Display_ದತ್ತಾಂಶ;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ದಶಮಾಂಶ SDR_white_level;
    ದಶಮಾಂಶ HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
ರಚನೆ SDL_ಕಿಟಕಿ
{
    SDL_ಕಿಟಕಿ_ID id;
    ಅಕ್ಷರ *title;
    SDL_Surface *icon;
    ಪೂರ್ಣಾಂಕ x, y;
    ಪೂರ್ಣಾಂಕ w, h;
    ಪೂರ್ಣಾಂಕ min_w, min_h;
    ಪೂರ್ಣಾಂಕ max_w, max_h;
    ದಶಮಾಂಶ min_aspect;
    ದಶಮಾಂಶ max_aspect;
    ಪೂರ್ಣಾಂಕ ಕೊನೆಯ_pixel_w, ಕೊನೆಯ_pixel_h;
    SDL_ಕಿಟಕಿ_Flags flags;
    SDL_ಕಿಟಕಿ_Flags pending_flags;
    ದಶಮಾಂಶ display_scale;
    bool external_graphics_context;
    bool fullscreen_exclusive;  // The window is currently fullscreen exclusive
    SDL_DisplayID ಕೊನೆಯ_fullscreen_exclusive_display;  // The last fullscreen_exclusive display
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

    SDL_Display_ಬಹುಲಕ requested_fullscreen_ಬಹುಲಕ;
    SDL_Display_ಬಹುಲಕ current_fullscreen_ಬಹುಲಕ;
    SDL_HDROutputProperties HDR;

    ದಶಮಾಂಶ opacity;

    SDL_Surface *surface;
    bool surface_valid;

    bool is_hiding;
    bool restore_on_show; // Child was hidden recursively by the parent, restore when shown.
    bool ಕೊನೆಯ_position_pending; // This should NOT be cleared by the backend, as it is used for fullscreen positioning.
    bool ಕೊನೆಯ_ಗಾತ್ರ_pending; // This should be cleared by the backend if the new size cannot be applied.
    bool update_fullscreen_on_display_ಬದಲಾಯಿತು;
    bool constrain_popup;
    bool is_destroying;
    bool is_dropping; // drag/drop in progress, expecting SDL_SendDropComplete().

    ಪೂರ್ಣಾಂಕ ಸುರಕ್ಷಿತ_inset_ಎಡ;
    ಪೂರ್ಣಾಂಕ ಸುರಕ್ಷಿತ_inset_ಬಲ;
    ಪೂರ್ಣಾಂಕ ಸುರಕ್ಷಿತ_inset_ತುದಿ;
    ಪೂರ್ಣಾಂಕ ಸುರಕ್ಷಿತ_inset_bottom;
    SDL_Rect ಸುರಕ್ಷಿತ_rect;

    SDL_PropertiesID ಪಠ್ಯ_ಒಳಹರಿವು_props;
    bool ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ;
    SDL_Rect ಪಠ್ಯ_ಒಳಹರಿವು_rect;
    ಪೂರ್ಣಾಂಕ ಪಠ್ಯ_ಒಳಹರಿವು_cursor;

    SDL_Rect mouse_rect;

    SDL_ದೊರಕಿತು_Test ದೊರಕಿತು_test;
    ಶೂನ್ಯ *ದೊರಕಿತು_test_ದತ್ತಾಂಶ;

    SDL_ಪ್ರಗತಿ_State ಪ್ರಗತಿ_state;
    ದಶಮಾಂಶ ಪ್ರಗತಿ_ಮೌಲ್ಯ;

    SDL_PropertiesID props;

    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_renderers;
    SDL_Renderer **renderers;

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಆಂತರಿಕ;

    // If a toplevel window, holds the current keyboard focus for grabbing popups.
    SDL_ಕಿಟಕಿ *keyboard_focus;

    SDL_ಕಿಟಕಿ *prev;
    SDL_ಕಿಟಕಿ *ಮುಂದಿನ;

    SDL_ಕಿಟಕಿ *ಪೋಷಕ;
    SDL_ಕಿಟಕಿ *ಮೊದಲ_ಮಗು;
    SDL_ಕಿಟಕಿ *prev_sibling;
    SDL_ಕಿಟಕಿ *ಮುಂದಿನ_sibling;
};
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_ಕಿಟಕಿ_FULLSCREEN_VISIBLE(W)        \
    ((((W)->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) != 0) &&   \
     (((W)->flags & SDL_ಕಿಟಕಿ_HIDDEN) == 0) && \
     (((W)->flags & SDL_ಕಿಟಕಿ_MINIMIZED) == 0))

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_ಕಿಟಕಿ_IS_POPUP(W) \
    (((W)->flags & (SDL_ಕಿಟಕಿ_TOOLTIP | SDL_ಕಿಟಕಿ_POPUP_MENU)) != 0)

/*
 * Define the SDL display structure.
 * This corresponds to physical monitors attached to the system.
 */
ರಚನೆ SDL_VideoDisplay
{
    SDL_DisplayID id;
    ಅಕ್ಷರ *name;
    ಪೂರ್ಣಾಂಕ max_fullscreen_modes;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_fullscreen_modes;
    SDL_Display_ಬಹುಲಕ *fullscreen_modes;
    SDL_Display_ಬಹುಲಕ desktop_ಬಹುಲಕ;
    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *current_ಬಹುಲಕ;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    ದಶಮಾಂಶ content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_ಸಕ್ರಿಯ;
    SDL_ಕಿಟಕಿ *fullscreen_ಕಿಟಕಿ;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ;
};

// Video device flags
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    VIDEO_DEVICE_CAPS_ಬಹುಲಕ_SWITCHING_EMULATED = 0x01,
    VIDEO_DEVICE_CAPS_HAS_POPUP_ಕಿಟಕಿ_SUPPORT = 0x02,
    VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS = 0x04,
    VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY = 0x08,
    VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES = 0x10,
    VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES = 0x20,
    VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER = 0x40
} DeviceCaps;

// Fullscreen operations
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_Fullscreen_ಫಲಿತಾಂಶ;

ರಚನೆ SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;

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
    bool (*ಗಣ_Display_ಬಹುಲಕ)(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);

    /* * * */
    /*
     * Window functions
     */
    bool (*CreateSDLWindow)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
    ಶೂನ್ಯ (*ಗಣ_ಕಿಟಕಿ_Title)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*ಗಣ_ಕಿಟಕಿ_Icon)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *icon);
    bool (*ಗಣ_ಕಿಟಕಿ_Position)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*Get_ಕಿಟಕಿ_Borders_ಗಾತ್ರ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *ತುದಿ, ಪೂರ್ಣಾಂಕ *ಎಡ, ಪೂರ್ಣಾಂಕ *bottom, ಪೂರ್ಣಾಂಕ *ಬಲ);
    ದಶಮಾಂಶ (*Get_ಕಿಟಕಿ_Content_Scale)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *w, ಪೂರ್ಣಾಂಕ *h);
    bool (*ಗಣ_ಕಿಟಕಿ_Opacity)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ opacity);
    bool (*ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ *ಪೋಷಕ);
    bool (*ಗಣ_ಕಿಟಕಿ_Modal)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool modal);
    ಶೂನ್ಯ (*Show_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*Hide_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*Raise_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*Maximize_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*Minimize_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*Restore_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*ಗಣ_ಕಿಟಕಿ_Bordered)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool bordered);
    ಶೂನ್ಯ (*ಗಣ_ಕಿಟಕಿ_Resizable)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable);
    ಶೂನ್ಯ (*ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool on_ತುದಿ);
    SDL_Fullscreen_ಫಲಿತಾಂಶ (*ಗಣ_ಕಿಟಕಿ_Fullscreen)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    ಶೂನ್ಯ *(*Get_ಕಿಟಕಿ_ICCProfile)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, size_t *ಗಾತ್ರ_2);
    SDL_DisplayID (*Get_Display_For_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*ಗಣ_ಕಿಟಕಿ_Mouse_Rect)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*ಗಣ_ಕಿಟಕಿ_Mouse_Grab)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed);
    bool (*ಗಣ_ಕಿಟಕಿ_Keyboard_Grab)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed);
    ಶೂನ್ಯ (*Destroy_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*Create_ಕಿಟಕಿ_Framebuffer)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಂಕ *pitch);
    bool (*ಗಣ_ಕಿಟಕಿ_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ vsync);
    bool (*Get_ಕಿಟಕಿ_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *vsync);
    bool (*Update_ಕಿಟಕಿ_Framebuffer)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects, ಪೂರ್ಣಾಂಕ numrects);
    ಶೂನ್ಯ (*Destroy_ಕಿಟಕಿ_Framebuffer)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*On_ಕಿಟಕಿ_Enter)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*Update_ಕಿಟಕಿ_Shape)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *shape);
    bool (*Flash_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_FlashOperation operation);
    bool (*Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*ಗಣ_ಕಿಟಕಿ_Focusable)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool focusable);
    bool (*ಗಣ_ಕಿಟಕಿ_Fill_Document)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool fill);
    bool (*Sync_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*Reconfigure_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ_Flags flags);

    /* * * */
    /*
     * OpenGL support
     */
    bool (*GL_ತುಂಬು_Library)(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ);
    SDL_Function_ಸೂಚಕ (*GL_Get_Proc_ವಿಳಾಸ)(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc);
    ಶೂನ್ಯ (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*GL_ಗಣ_ಅದಲುಬದಲು_Interval)(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval);
    bool (*GL_Get_ಅದಲುಬದಲು_Interval)(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval);
    bool (*GL_ಅದಲುಬದಲು_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    ಶೂನ್ಯ (*GL_ಗಣ_Default_Profile_Config)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_ತುಂಬು_Library)(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ);
    ಶೂನ್ಯ (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    ಅಕ್ಷರ ಸ್ಥಿರಾಂಕ * ಸ್ಥಿರಾಂಕ *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *ಎಣಿಕೆ_2);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, VkInstance instance, ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator, VkSurfaceKHR *surface);
    ಶೂನ್ಯ (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 ಸರತಿ_Family_ಸೂಚ್ಯಂಕ);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    ಶೂನ್ಯ *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    ಪೂರ್ಣಾಂಕ (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    ಶೂನ್ಯ (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props);
    bool (*Stop_ಪಠ್ಯ_ಒಳಹರಿವು)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    ಶೂನ್ಯ (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props);
    ಶೂನ್ಯ (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
    ಶೂನ್ಯ (*ಗಣ_ಪಠ್ಯ_ಒಳಹರಿವು_Properties)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props);

    // Clipboard
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *(*Get_ಪಠ್ಯ_Mime_Types)(SDL_VideoDevice *_this, size_t *ಅಂಕೆ_mime_types);
    bool (*ಗಣ_Clipboard_ದತ್ತಾಂಶ)(SDL_VideoDevice *_this);
    ಶೂನ್ಯ *(*Get_Clipboard_ದತ್ತಾಂಶ)(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಗಾತ್ರ_2);
    bool (*Has_Clipboard_ದತ್ತಾಂಶ)(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*ಗಣ_Clipboard_ಪಠ್ಯ)(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ);
    ಅಕ್ಷರ *(*Get_Clipboard_ಪಠ್ಯ)(SDL_VideoDevice *_this);
    bool (*Has_Clipboard_ಪಠ್ಯ)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*ಗಣ_Primary_Selection_ಪಠ್ಯ)(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ);
    ಅಕ್ಷರ *(*Get_Primary_Selection_ಪಠ್ಯ)(SDL_VideoDevice *_this);
    bool (*Has_Primary_Selection_ಪಠ್ಯ)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*Show_ಸಂದೇಶ_Box)(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonID);

    // Hit-testing
    bool (*ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test)(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool enabled);

    // Tell window that app enabled drag'n'drop events
    ಶೂನ್ಯ (*AcceptDragAndDrop)(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool accept);

    // Display the system-level window menu
    ಶೂನ್ಯ (*Show_ಕಿಟಕಿ_System_Menu)(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    ಶೂನ್ಯ *wakeup_ಕಿಟಕಿ;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_ಕಿಟಕಿ *windows;
    SDL_ಕಿಟಕಿ *grabbed_ಕಿಟಕಿ;
    Uint32 clipboard_sequence;
    SDL_Clipboard_ದತ್ತಾಂಶ_Callback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    ಶೂನ್ಯ *clipboard_userdata;
    ಅಕ್ಷರ **clipboard_mime_types;
    size_t ಅಂಕೆ_clipboard_mime_types;
    ಅಕ್ಷರ *primary_selection_ಪಠ್ಯ;
    bool setting_display_ಬಹುಲಕ;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    ರಚನೆ
    {
        ಪೂರ್ಣಾಂಕ red_ಗಾತ್ರ;
        ಪೂರ್ಣಾಂಕ green_ಗಾತ್ರ;
        ಪೂರ್ಣಾಂಕ blue_ಗಾತ್ರ;
        ಪೂರ್ಣಾಂಕ alpha_ಗಾತ್ರ;
        ಪೂರ್ಣಾಂಕ ಆಳ_ಗಾತ್ರ;
        ಪೂರ್ಣಾಂಕ ಬಫರ್_ಗಾತ್ರ;
        ಪೂರ್ಣಾಂಕ stencil_ಗಾತ್ರ;
        ಪೂರ್ಣಾಂಕ double_ಬಫರ್;
        ಪೂರ್ಣಾಂಕ accum_red_ಗಾತ್ರ;
        ಪೂರ್ಣಾಂಕ accum_green_ಗಾತ್ರ;
        ಪೂರ್ಣಾಂಕ accum_blue_ಗಾತ್ರ;
        ಪೂರ್ಣಾಂಕ accum_alpha_ಗಾತ್ರ;
        ಪೂರ್ಣಾಂಕ stereo;
        ಪೂರ್ಣಾಂಕ multisamplebuffers;
        ಪೂರ್ಣಾಂಕ multisamplesamples;
        ಪೂರ್ಣಾಂಕ floatbuffers;
        ಪೂರ್ಣಾಂಕ accelerated;
        ಪೂರ್ಣಾಂಕ major_ಆವೃತ್ತಿ;
        ಪೂರ್ಣಾಂಕ minor_ಆವೃತ್ತಿ;
        ಪೂರ್ಣಾಂಕ flags;
        ಪೂರ್ಣಾಂಕ profile_ಮುಖವಾಡ;
        ಪೂರ್ಣಾಂಕ share_with_current_context;
        ಪೂರ್ಣಾಂಕ release_behavior;
        ಪೂರ್ಣಾಂಕ reset_notification;
        ಪೂರ್ಣಾಂಕ framebuffer_srgb_capable;
        ಪೂರ್ಣಾಂಕ no_error;
        ಪೂರ್ಣಾಂಕ retained_backing;
        ಪೂರ್ಣಾಂಕ egl_platform;
        ಪೂರ್ಣಾಂಕ driver_loaded;
        ಪೂರ್ಣಾಂಕ HAS_GL_ARB_color_ಬಫರ್_float;
        ಅಕ್ಷರ driver_ಮಾರ್ಗ[256];
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
    SDL_ಕಿಟಕಿ *current_glwin;
    SDL_GLContext current_glctx;
    SDL_TLSID current_glwin_tls;
    SDL_TLSID current_glctx_tls;

    /* Flag that stores whether it's allowed to call SDL_GL_MakeCurrent()
     * with a NULL window, but a non-NULL context. (Not allowed in most cases,
     * except on EGL under some circumstances.) */
    bool gl_allow_no_surface;

    /* * * */
    // Data used by the Vulkan drivers
    ರಚನೆ
    {
        SDL_Function_ಸೂಚಕ vkGetInstanceProcAddr;
        SDL_Function_ಸೂಚಕ vkEnumerateInstanceExtensionProperties;
        ಪೂರ್ಣಾಂಕ loader_loaded;
        ಅಕ್ಷರ loader_ಮಾರ್ಗ[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_Video_ದತ್ತಾಂಶ *ಆಂತರಿಕ;
    ರಚನೆ SDL_GLDriver_ದತ್ತಾಂಶ *gl_ದತ್ತಾಂಶ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    ರಚನೆ SDL_EGL_Video_ದತ್ತಾಂಶ *egl_ದತ್ತಾಂಶ;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    ರಚನೆ SDL_ಖಾಸಗಿ_GLESData *gles_ದತ್ತಾಂಶ;
#ಆದರೆ_ಅಂತ್ಯ

    /* * * */
    // The function used to dispose of this structure
    ಶೂನ್ಯ (*ಬಿಡುಗಡೆ)(SDL_VideoDevice *_this);
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VideoBootStrap
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *desc;
    SDL_VideoDevice *(*create)(ಶೂನ್ಯ);
    bool (*Show_ಸಂದೇಶ_Box)(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
ಬಾಹ್ಯ VideoBootStrap ಖಾಸಗಿ_bootstrap;
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
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ಗಣ_System_Theme(SDL_SystemTheme theme);
ಬಾಹ್ಯ SDL_DisplayID SDL_ಕೂಡಿಸು_Basic_Video_Display(ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *desktop_ಬಹುಲಕ);
ಬಾಹ್ಯ SDL_DisplayID SDL_ಕೂಡಿಸು_Video_Display(ಸ್ಥಿರಾಂಕ SDL_VideoDisplay *display, bool send_event);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
ಬಾಹ್ಯ bool SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(SDL_VideoDisplay *display, ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ಗಣ_Desktop_Display_ಬಹುಲಕ(SDL_VideoDisplay *display, ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ಗಣ_Current_Display_ಬಹುಲಕ(SDL_VideoDisplay *display, ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ಗಣ_Display_Content_Scale(SDL_VideoDisplay *display, ದಶಮಾಂಶ scale);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ಗಣ_Display_HDRProperties(SDL_VideoDisplay *display, ಸ್ಥಿರಾಂಕ SDL_HDROutputProperties *HDR);
ಬಾಹ್ಯ bool SDL_ಗಣ_Display_ಬಹುಲಕ_For_Display(SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
ಬಾಹ್ಯ SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
ಬಾಹ್ಯ SDL_DisplayID SDL_Get_Display_For_ಕಿಟಕಿ_Position(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ SDL_VideoDisplay *SDL_Get_Video_Display_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ SDL_Get_Display_ಸೂಚ್ಯಂಕ(SDL_DisplayID displayID);
ಬಾಹ್ಯ SDL_Display_ದತ್ತಾಂಶ *SDL_Get_Display_Driver_ದತ್ತಾಂಶ(SDL_DisplayID display);
ಬಾಹ್ಯ SDL_Display_ದತ್ತಾಂಶ *SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ SDL_Get_ಸಂದೇಶ_Box_ಎಣಿಕೆ(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ಗಣ_ಕಿಟಕಿ_HDRProperties(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_HDROutputProperties *HDR, bool send_event);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ಗಣ_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_Area_Insets(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ ಎಡ, ಪೂರ್ಣಾಂಕ ಬಲ, ಪೂರ್ಣಾಂಕ ತುದಿ, ಪೂರ್ಣಾಂಕ bottom);

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_GL_DeduceMaxSupportedESProfile(ಪೂರ್ಣಾಂಕ *major, ಪೂರ್ಣಾಂಕ *minor);

ಬಾಹ್ಯ bool SDL_Recreate_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ_Flags flags);
ಬಾಹ್ಯ bool SDL_Reconfigure_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ_Flags flags);
ಬಾಹ್ಯ bool SDL_HasWindows(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ rel_x, ಪೂರ್ಣಾಂಕ rel_y, ಪೂರ್ಣಾಂಕ *abs_x, ಪೂರ್ಣಾಂಕ *abs_y);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_Global_ಗಮ್ಯ_Relative_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ abs_x, ಪೂರ್ಣಾಂಕ abs_y, ಪೂರ್ಣಾಂಕ *rel_x, ಪೂರ್ಣಾಂಕ *rel_y);
ಬಾಹ್ಯ bool SDL_ShouldFocusPopup(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool SDL_ShouldRelinquishPopupFocus(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ **new_focus);

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnDisplayAdded(SDL_VideoDisplay *display);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_OnDisplayMoved(SDL_VideoDisplay *display);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Shown(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Hidden(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Moved(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Resized(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_Check_ಕಿಟಕಿ_Pixel_ಗಾತ್ರ_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Pixel_ಗಾತ್ರ_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_ಜೀವಂತ_Resize_Update(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Minimized(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Maximized(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Restored(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Enter(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Leave(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Focus_Gained(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Focus_ಕಳೆದುಹೋದ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Display_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_Update_ಕಿಟಕಿ_Grab(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool SDL_Update_Fullscreen_ಬಹುಲಕ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_FullscreenOp fullscreen, bool commit);
ಬಾಹ್ಯ SDL_ಕಿಟಕಿ *SDL_GetToplevelForKeyboardFocus(ಶೂನ್ಯ);

ಬಾಹ್ಯ bool SDL_ShouldAllowTopmost(ಶೂನ್ಯ);

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ToggleDragAndDropSupport(ಶೂನ್ಯ);

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_UpdateDesktopBounds(ಶೂನ್ಯ);

ಬಾಹ್ಯ SDL_ಪಠ್ಯ_ಒಳಹರಿವು_Type SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Type(SDL_PropertiesID props);
ಬಾಹ್ಯ SDL_Capitalization SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Capitalization(SDL_PropertiesID props);
ಬಾಹ್ಯ bool SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Autocorrect(SDL_PropertiesID props);
ಬಾಹ್ಯ bool SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Multiline(SDL_PropertiesID props);

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_SendScreenKeyboardShown(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_SendScreenKeyboardHidden(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_sysvideo_h_
