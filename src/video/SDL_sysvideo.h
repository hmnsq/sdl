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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_sysvideo_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_sysvideo_h_

#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_vulkan.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"

// The SDL video driver

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_VideoDisplay SDL_VideoDisplay;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_VideoDevice SDL_VideoDevice;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_Video_ਅੰਕੜੇ SDL_Video_ਅੰਕੜੇ;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_Display_ਅੰਕੜੇ SDL_Display_ਅੰਕੜੇ;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਦਸ਼ਮਲਵ SDR_white_level;
    ਦਸ਼ਮਲਵ HDR_headroom;
} SDL_HDROutputProperties;

// Define the SDL window structure, corresponding to toplevel windows
ਬਣਤਰ SDL_ਖਿੜਕੀ
{
    SDL_ਖਿੜਕੀ_ID id;
    ਅੱਖਰ *title;
    SDL_Surface *icon;
    ਪੂਰਨ x, y;
    ਪੂਰਨ w, h;
    ਪੂਰਨ min_w, min_h;
    ਪੂਰਨ max_w, max_h;
    ਦਸ਼ਮਲਵ min_aspect;
    ਦਸ਼ਮਲਵ max_aspect;
    ਪੂਰਨ ਆਖਰੀ_pixel_w, ਆਖਰੀ_pixel_h;
    SDL_ਖਿੜਕੀ_Flags flags;
    SDL_ਖਿੜਕੀ_Flags pending_flags;
    ਦਸ਼ਮਲਵ display_scale;
    bool external_graphics_context;
    bool fullscreen_exclusive;  // The window is currently fullscreen exclusive
    SDL_DisplayID ਆਖਰੀ_fullscreen_exclusive_display;  // The last fullscreen_exclusive display
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

    SDL_Display_ਬਹੁਲਕ requested_fullscreen_ਬਹੁਲਕ;
    SDL_Display_ਬਹੁਲਕ current_fullscreen_ਬਹੁਲਕ;
    SDL_HDROutputProperties HDR;

    ਦਸ਼ਮਲਵ opacity;

    SDL_Surface *surface;
    bool surface_valid;

    bool is_hiding;
    bool restore_on_show; // Child was hidden recursively by the parent, restore when shown.
    bool ਆਖਰੀ_position_pending; // This should NOT be cleared by the backend, as it is used for fullscreen positioning.
    bool ਆਖਰੀ_ਮਾਪ_pending; // This should be cleared by the backend if the new size cannot be applied.
    bool update_fullscreen_on_display_ਬਦਲਿਆ;
    bool constrain_popup;
    bool is_destroying;
    bool is_dropping; // drag/drop in progress, expecting SDL_SendDropComplete().

    ਪੂਰਨ ਸੁਰੱਖਿਅਤ_inset_ਖੱਬਾ;
    ਪੂਰਨ ਸੁਰੱਖਿਅਤ_inset_ਸੱਜਾ;
    ਪੂਰਨ ਸੁਰੱਖਿਅਤ_inset_ਸਿਖਰ;
    ਪੂਰਨ ਸੁਰੱਖਿਅਤ_inset_bottom;
    SDL_Rect ਸੁਰੱਖਿਅਤ_rect;

    SDL_PropertiesID ਪਾਠ_ਨਿਵੇਸ਼_props;
    bool ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ;
    SDL_Rect ਪਾਠ_ਨਿਵੇਸ਼_rect;
    ਪੂਰਨ ਪਾਠ_ਨਿਵੇਸ਼_cursor;

    SDL_Rect mouse_rect;

    SDL_ਪ੍ਰਾਪਤੀ_Test ਪ੍ਰਾਪਤੀ_test;
    ਖਾਲੀ *ਪ੍ਰਾਪਤੀ_test_ਅੰਕੜੇ;

    SDL_ਤਰੱਕੀ_State ਤਰੱਕੀ_state;
    ਦਸ਼ਮਲਵ ਤਰੱਕੀ_ਮੁੱਲ;

    SDL_PropertiesID props;

    ਪੂਰਨ ਅੰਕ_renderers;
    SDL_Renderer **renderers;

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ;

    // If a toplevel window, holds the current keyboard focus for grabbing popups.
    SDL_ਖਿੜਕੀ *keyboard_focus;

    SDL_ਖਿੜਕੀ *prev;
    SDL_ਖਿੜਕੀ *ਅਗਲਾ;

    SDL_ਖਿੜਕੀ *ਮਾਪਾ;
    SDL_ਖਿੜਕੀ *ਪਹਿਲਾ_ਬੱਚਾ;
    SDL_ਖਿੜਕੀ *prev_sibling;
    SDL_ਖਿੜਕੀ *ਅਗਲਾ_sibling;
};
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_ਖਿੜਕੀ_FULLSCREEN_VISIBLE(W)        \
    ((((W)->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) != 0) &&   \
     (((W)->flags & SDL_ਖਿੜਕੀ_HIDDEN) == 0) && \
     (((W)->flags & SDL_ਖਿੜਕੀ_MINIMIZED) == 0))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_ਖਿੜਕੀ_IS_POPUP(W) \
    (((W)->flags & (SDL_ਖਿੜਕੀ_TOOLTIP | SDL_ਖਿੜਕੀ_POPUP_MENU)) != 0)

/*
 * Define the SDL display structure.
 * This corresponds to physical monitors attached to the system.
 */
ਬਣਤਰ SDL_VideoDisplay
{
    SDL_DisplayID id;
    ਅੱਖਰ *name;
    ਪੂਰਨ max_fullscreen_modes;
    ਪੂਰਨ ਅੰਕ_fullscreen_modes;
    SDL_Display_ਬਹੁਲਕ *fullscreen_modes;
    SDL_Display_ਬਹੁਲਕ desktop_ਬਹੁਲਕ;
    ਅਚਲ SDL_Display_ਬਹੁਲਕ *current_ਬਹੁਲਕ;
    SDL_DisplayOrientation natural_orientation;
    SDL_DisplayOrientation current_orientation;
    ਦਸ਼ਮਲਵ content_scale;
    SDL_HDROutputProperties HDR;

    // This is true if we are fullscreen or fullscreen is pending
    bool fullscreen_ਸਰਗਰਮ;
    SDL_ਖਿੜਕੀ *fullscreen_ਖਿੜਕੀ;

    SDL_VideoDevice *device;

    SDL_PropertiesID props;

    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ;
};

// Video device flags
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    VIDEO_DEVICE_CAPS_ਬਹੁਲਕ_SWITCHING_EMULATED = 0x01,
    VIDEO_DEVICE_CAPS_HAS_POPUP_ਖਿੜਕੀ_SUPPORT = 0x02,
    VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS = 0x04,
    VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY = 0x08,
    VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES = 0x10,
    VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES = 0x20,
    VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER = 0x40
} DeviceCaps;

// Fullscreen operations
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    SDL_FULLSCREEN_OP_LEAVE = 0,
    SDL_FULLSCREEN_OP_ENTER,
    SDL_FULLSCREEN_OP_UPDATE
} SDL_FullscreenOp;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    SDL_FULLSCREEN_FAILED,
    SDL_FULLSCREEN_SUCCEEDED,
    SDL_FULLSCREEN_PENDING
} SDL_Fullscreen_ਨਤੀਜਾ;

ਬਣਤਰ SDL_VideoDevice
{
    /* * * */
    // The name of this video driver
    ਅਚਲ ਅੱਖਰ *name;

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
    ਖਾਲੀ (*VideoQuit)(SDL_VideoDevice *_this);

    /*
     * Reinitialize the touch devices -- called if an unknown touch ID occurs.
     */
    ਖਾਲੀ (*ResetTouch)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Display functions
     */

    /*
     * Refresh the display list
     */
    ਖਾਲੀ (*RefreshDisplays)(SDL_VideoDevice *_this);

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
    bool (*ਸੈੱਟ_Display_ਬਹੁਲਕ)(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);

    /* * * */
    /*
     * Window functions
     */
    bool (*CreateSDLWindow)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
    ਖਾਲੀ (*ਸੈੱਟ_ਖਿੜਕੀ_Title)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*ਸੈੱਟ_ਖਿੜਕੀ_Icon)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *icon);
    bool (*ਸੈੱਟ_ਖਿੜਕੀ_Position)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*Get_ਖਿੜਕੀ_Borders_ਮਾਪ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *ਸਿਖਰ, ਪੂਰਨ *ਖੱਬਾ, ਪੂਰਨ *bottom, ਪੂਰਨ *ਸੱਜਾ);
    ਦਸ਼ਮਲਵ (*Get_ਖਿੜਕੀ_Content_Scale)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *w, ਪੂਰਨ *h);
    bool (*ਸੈੱਟ_ਖਿੜਕੀ_Opacity)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ opacity);
    bool (*ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ *ਮਾਪਾ);
    bool (*ਸੈੱਟ_ਖਿੜਕੀ_Modal)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool modal);
    ਖਾਲੀ (*Show_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*Hide_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*Raise_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*Maximize_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*Minimize_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*Restore_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*ਸੈੱਟ_ਖਿੜਕੀ_Bordered)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool bordered);
    ਖਾਲੀ (*ਸੈੱਟ_ਖਿੜਕੀ_Resizable)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool resizable);
    ਖਾਲੀ (*ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool on_ਸਿਖਰ);
    SDL_Fullscreen_ਨਤੀਜਾ (*ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
    ਖਾਲੀ *(*Get_ਖਿੜਕੀ_ICCProfile)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, size_t *ਮਾਪ);
    SDL_DisplayID (*Get_Display_For_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed);
    bool (*ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed);
    ਖਾਲੀ (*Destroy_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*Create_ਖਿੜਕੀ_Framebuffer)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PixelFormat *format, ਖਾਲੀ **pixels, ਪੂਰਨ *pitch);
    bool (*ਸੈੱਟ_ਖਿੜਕੀ_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ vsync);
    bool (*Get_ਖਿੜਕੀ_Framebuffer_VSync)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *vsync);
    bool (*Update_ਖਿੜਕੀ_Framebuffer)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rects, ਪੂਰਨ numrects);
    ਖਾਲੀ (*Destroy_ਖਿੜਕੀ_Framebuffer)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*On_ਖਿੜਕੀ_Enter)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*Update_ਖਿੜਕੀ_Shape)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *shape);
    bool (*Flash_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_FlashOperation operation);
    bool (*Apply_ਖਿੜਕੀ_ਤਰੱਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*ਸੈੱਟ_ਖਿੜਕੀ_Focusable)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool focusable);
    bool (*ਸੈੱਟ_ਖਿੜਕੀ_Fill_Document)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool fill);
    bool (*Sync_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*Reconfigure_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ_Flags flags);

    /* * * */
    /*
     * OpenGL support
     */
    bool (*GL_ਲੱਦੋ_Library)(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
    SDL_Function_ਸੂਚਕ (*GL_Get_Proc_ਪਤਾ)(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc);
    ਖਾਲੀ (*GL_UnloadLibrary)(SDL_VideoDevice *_this);
    SDL_GLContext (*GL_CreateContext)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*GL_MakeCurrent)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context);
    SDL_EGLSurface (*GL_GetEGLSurface)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval)(SDL_VideoDevice *_this, ਪੂਰਨ interval);
    bool (*GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval)(SDL_VideoDevice *_this, ਪੂਰਨ *interval);
    bool (*GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*GL_DestroyContext)(SDL_VideoDevice *_this, SDL_GLContext context);
    ਖਾਲੀ (*GL_ਸੈੱਟ_Default_Profile_Config)(SDL_VideoDevice *_this);

    /* * * */
    /*
     * Vulkan support
     */
    bool (*Vulkan_ਲੱਦੋ_Library)(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
    ਖਾਲੀ (*Vulkan_UnloadLibrary)(SDL_VideoDevice *_this);
    ਅੱਖਰ ਅਚਲ * ਅਚਲ *(*Vulkan_GetInstanceExtensions)(SDL_VideoDevice *_this, Uint32 *ਗਿਣਤੀ_2);
    bool (*Vulkan_CreateSurface)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, VkInstance instance, ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator, VkSurfaceKHR *surface);
    ਖਾਲੀ (*Vulkan_DestroySurface)(SDL_VideoDevice *_this, VkInstance instance, VkSurfaceKHR surface, ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator);
    bool (*Vulkan_GetPresentationSupport)(SDL_VideoDevice *_this, VkInstance instance, VkPhysicalDevice physicalDevice, Uint32 ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ);

    /* * * */
    /*
     * Metal support
     */
    SDL_MetalView (*Metal_CreateView)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*Metal_DestroyView)(SDL_VideoDevice *_this, SDL_MetalView view);
    ਖਾਲੀ *(*Metal_GetLayer)(SDL_VideoDevice *_this, SDL_MetalView view);

    /* * * */
    /*
     * Event manager functions
     */
    ਪੂਰਨ (*WaitEventTimeout)(SDL_VideoDevice *_this, Sint64 timeoutNS);
    ਖਾਲੀ (*SendWakeupEvent)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*PumpEvents)(SDL_VideoDevice *_this);

    // Suspend/resume the screensaver
    bool (*SuspendScreenSaver)(SDL_VideoDevice *_this);

    // Text input
    bool (*ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props);
    bool (*Stop_ਪਾਠ_ਨਿਵੇਸ਼)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*Update_ਪਾਠ_ਨਿਵੇਸ਼_Area)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    bool (*ClearComposition)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

    // Screen keyboard
    bool (*HasScreenKeyboardSupport)(SDL_VideoDevice *_this);
    ਖਾਲੀ (*ShowScreenKeyboard)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props);
    ਖਾਲੀ (*HideScreenKeyboard)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
    ਖਾਲੀ (*ਸੈੱਟ_ਪਾਠ_ਨਿਵੇਸ਼_Properties)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props);

    // Clipboard
    ਅਚਲ ਅੱਖਰ *ਅਚਲ *(*Get_ਪਾਠ_Mime_Types)(SDL_VideoDevice *_this, size_t *ਅੰਕ_mime_types);
    bool (*ਸੈੱਟ_Clipboard_ਅੰਕੜੇ)(SDL_VideoDevice *_this);
    ਖਾਲੀ *(*Get_Clipboard_ਅੰਕੜੇ)(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਮਾਪ);
    bool (*Has_Clipboard_ਅੰਕੜੇ)(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *mime_type);
    /* If you implement *ClipboardData, you don't need to implement *ClipboardText */
    bool (*ਸੈੱਟ_Clipboard_ਪਾਠ)(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਪਾਠ);
    ਅੱਖਰ *(*Get_Clipboard_ਪਾਠ)(SDL_VideoDevice *_this);
    bool (*Has_Clipboard_ਪਾਠ)(SDL_VideoDevice *_this);
    // These functions are only needed if the platform has a separate primary selection buffer
    bool (*ਸੈੱਟ_Primary_Selection_ਪਾਠ)(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਪਾਠ);
    ਅੱਖਰ *(*Get_Primary_Selection_ਪਾਠ)(SDL_VideoDevice *_this);
    bool (*Has_Primary_Selection_ਪਾਠ)(SDL_VideoDevice *_this);

    // MessageBox
    bool (*Show_ਸੁਨੇਹਾ_Box)(SDL_VideoDevice *_this, ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID);

    // Hit-testing
    bool (*ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test)(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool enabled);

    // Tell window that app enabled drag'n'drop events
    ਖਾਲੀ (*AcceptDragAndDrop)(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool accept);

    // Display the system-level window menu
    ਖਾਲੀ (*Show_ਖਿੜਕੀ_System_Menu)(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ x, ਪੂਰਨ y);

    /* * * */
    // Data common to all drivers
    SDL_ThreadID thread;
    bool checked_texture_framebuffer;
    bool suspend_screensaver;
    ਖਾਲੀ *wakeup_ਖਿੜਕੀ;
    ਪੂਰਨ ਅੰਕ_displays;
    SDL_VideoDisplay **displays;
    SDL_Rect desktop_bounds;
    SDL_ਖਿੜਕੀ *windows;
    SDL_ਖਿੜਕੀ *grabbed_ਖਿੜਕੀ;
    Uint32 clipboard_sequence;
    SDL_Clipboard_ਅੰਕੜੇ_Callback clipboard_callback;
    SDL_ClipboardCleanupCallback clipboard_cleanup;
    ਖਾਲੀ *clipboard_userdata;
    ਅੱਖਰ **clipboard_mime_types;
    size_t ਅੰਕ_clipboard_mime_types;
    ਅੱਖਰ *primary_selection_ਪਾਠ;
    bool setting_display_ਬਹੁਲਕ;
    Uint32 device_caps;
    SDL_SystemTheme system_theme;
    bool screen_keyboard_shown;
    bool is_quitting;

    /* * * */
    // Data used by the GL drivers
    ਬਣਤਰ
    {
        ਪੂਰਨ red_ਮਾਪ;
        ਪੂਰਨ green_ਮਾਪ;
        ਪੂਰਨ blue_ਮਾਪ;
        ਪੂਰਨ alpha_ਮਾਪ;
        ਪੂਰਨ ਡੂੰਘਾਈ_ਮਾਪ;
        ਪੂਰਨ ਬਫਰ_ਮਾਪ;
        ਪੂਰਨ stencil_ਮਾਪ;
        ਪੂਰਨ double_ਬਫਰ;
        ਪੂਰਨ accum_red_ਮਾਪ;
        ਪੂਰਨ accum_green_ਮਾਪ;
        ਪੂਰਨ accum_blue_ਮਾਪ;
        ਪੂਰਨ accum_alpha_ਮਾਪ;
        ਪੂਰਨ stereo;
        ਪੂਰਨ multisamplebuffers;
        ਪੂਰਨ multisamplesamples;
        ਪੂਰਨ floatbuffers;
        ਪੂਰਨ accelerated;
        ਪੂਰਨ major_ਸੰਸਕਰਣ;
        ਪੂਰਨ minor_ਸੰਸਕਰਣ;
        ਪੂਰਨ flags;
        ਪੂਰਨ profile_ਨਕਾਬ;
        ਪੂਰਨ share_with_current_context;
        ਪੂਰਨ release_behavior;
        ਪੂਰਨ reset_notification;
        ਪੂਰਨ framebuffer_srgb_capable;
        ਪੂਰਨ no_error;
        ਪੂਰਨ retained_backing;
        ਪੂਰਨ egl_platform;
        ਪੂਰਨ driver_loaded;
        ਪੂਰਨ HAS_GL_ARB_color_ਬਫਰ_float;
        ਅੱਖਰ driver_ਰਸਤਾ[256];
        SDL_SharedObject *dll_handle;
    } gl_config;

    SDL_EGLAttribArrayCallback egl_platformattrib_callback;
    SDL_EGLIntArrayCallback egl_surfaceattrib_callback;
    SDL_EGLIntArrayCallback egl_contextattrib_callback;
    ਖਾਲੀ *egl_attrib_callback_userdata;

    /* * * */
    // Cache current GL context; don't call the OS when it hasn't changed.
    /* We have the global pointers here so Cocoa continues to work the way
       it always has, and the thread-local storage for the general case.
     */
    SDL_ਖਿੜਕੀ *current_glwin;
    SDL_GLContext current_glctx;
    SDL_TLSID current_glwin_tls;
    SDL_TLSID current_glctx_tls;

    /* Flag that stores whether it's allowed to call SDL_GL_MakeCurrent()
     * with a NULL window, but a non-NULL context. (Not allowed in most cases,
     * except on EGL under some circumstances.) */
    bool gl_allow_no_surface;

    /* * * */
    // Data used by the Vulkan drivers
    ਬਣਤਰ
    {
        SDL_Function_ਸੂਚਕ vkGetInstanceProcAddr;
        SDL_Function_ਸੂਚਕ vkEnumerateInstanceExtensionProperties;
        ਪੂਰਨ loader_loaded;
        ਅੱਖਰ loader_ਰਸਤਾ[256];
        SDL_SharedObject *loader_handle;
    } vulkan_config;

    /* * * */
    // Data private to this driver
    SDL_Video_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ;
    ਬਣਤਰ SDL_GLDriver_ਅੰਕੜੇ *gl_ਅੰਕੜੇ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    ਬਣਤਰ SDL_EGL_Video_ਅੰਕੜੇ *egl_ਅੰਕੜੇ;
#ਜੇ_ਅੰਤ

#ਜੇ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    ਬਣਤਰ SDL_ਨਿੱਜੀ_GLESData *gles_ਅੰਕੜੇ;
#ਜੇ_ਅੰਤ

    /* * * */
    // The function used to dispose of this structure
    ਖਾਲੀ (*ਮੁਕਤ)(SDL_VideoDevice *_this);
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VideoBootStrap
{
    ਅਚਲ ਅੱਖਰ *name;
    ਅਚਲ ਅੱਖਰ *desc;
    SDL_VideoDevice *(*create)(ਖਾਲੀ);
    bool (*Show_ਸੁਨੇਹਾ_Box)(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID);  // can be done without initializing backend!
    bool is_preferred;
} VideoBootStrap;

// Not all of these are available in a given build. Use #ifdefs, etc.
ਬਾਹਰੀ VideoBootStrap ਨਿੱਜੀ_bootstrap;
ਬਾਹਰੀ VideoBootStrap COCOA_bootstrap;
ਬਾਹਰੀ VideoBootStrap X11_bootstrap;
ਬਾਹਰੀ VideoBootStrap WINDOWS_bootstrap;
ਬਾਹਰੀ VideoBootStrap HAIKU_bootstrap;
ਬਾਹਰੀ VideoBootStrap UIKIT_bootstrap;
ਬਾਹਰੀ VideoBootStrap Android_bootstrap;
ਬਾਹਰੀ VideoBootStrap OPENHARMONY_bootstrap;
ਬਾਹਰੀ VideoBootStrap PS2_bootstrap;
ਬਾਹਰੀ VideoBootStrap PSP_bootstrap;
ਬਾਹਰੀ VideoBootStrap VITA_bootstrap;
ਬਾਹਰੀ VideoBootStrap RISCOS_bootstrap;
ਬਾਹਰੀ VideoBootStrap N3DS_bootstrap;
ਬਾਹਰੀ VideoBootStrap NGAGE_bootstrap;
ਬਾਹਰੀ VideoBootStrap RPI_bootstrap;
ਬਾਹਰੀ VideoBootStrap KMSDRM_bootstrap;
ਬਾਹਰੀ VideoBootStrap DUMMY_bootstrap;
ਬਾਹਰੀ VideoBootStrap DUMMY_evdev_bootstrap;
ਬਾਹਰੀ VideoBootStrap Wayland_preferred_bootstrap;
ਬਾਹਰੀ VideoBootStrap Wayland_bootstrap;
ਬਾਹਰੀ VideoBootStrap VIVANTE_bootstrap;
ਬਾਹਰੀ VideoBootStrap Emscripten_bootstrap;
ਬਾਹਰੀ VideoBootStrap OFFSCREEN_bootstrap;
ਬਾਹਰੀ VideoBootStrap QNX_bootstrap;
ਬਾਹਰੀ VideoBootStrap OPENVR_bootstrap;
ਬਾਹਰੀ VideoBootStrap DOSVESA_bootstrap;

ਬਾਹਰੀ bool SDL_UninitializedVideo(ਖਾਲੀ);
// Use SDL_OnVideoThread() sparingly, to avoid regressions in use cases that currently happen to work
ਬਾਹਰੀ bool SDL_OnVideoThread(ਖਾਲੀ);
ਬਾਹਰੀ SDL_VideoDevice *SDL_GetVideoDevice(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_ਸੈੱਟ_System_Theme(SDL_SystemTheme theme);
ਬਾਹਰੀ SDL_DisplayID SDL_ਜੋੜੋ_Basic_Video_Display(ਅਚਲ SDL_Display_ਬਹੁਲਕ *desktop_ਬਹੁਲਕ);
ਬਾਹਰੀ SDL_DisplayID SDL_ਜੋੜੋ_Video_Display(ਅਚਲ SDL_VideoDisplay *display, bool send_event);
ਬਾਹਰੀ ਖਾਲੀ SDL_DelVideoDisplay(SDL_DisplayID display, bool send_event);
ਬਾਹਰੀ bool SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(SDL_VideoDisplay *display, ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਬਾਹਰੀ ਖਾਲੀ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display);
ਬਾਹਰੀ ਖਾਲੀ SDL_ਸੈੱਟ_Desktop_Display_ਬਹੁਲਕ(SDL_VideoDisplay *display, ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਬਾਹਰੀ ਖਾਲੀ SDL_ਸੈੱਟ_Current_Display_ਬਹੁਲਕ(SDL_VideoDisplay *display, ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਬਾਹਰੀ ਖਾਲੀ SDL_ਸੈੱਟ_Display_Content_Scale(SDL_VideoDisplay *display, ਦਸ਼ਮਲਵ scale);
ਬਾਹਰੀ ਖਾਲੀ SDL_ਸੈੱਟ_Display_HDRProperties(SDL_VideoDisplay *display, ਅਚਲ SDL_HDROutputProperties *HDR);
ਬਾਹਰੀ bool SDL_ਸੈੱਟ_Display_ਬਹੁਲਕ_For_Display(SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਬਾਹਰੀ SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID display);
ਬਾਹਰੀ SDL_DisplayID SDL_Get_Display_For_ਖਿੜਕੀ_Position(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ SDL_VideoDisplay *SDL_Get_Video_Display_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਪੂਰਨ SDL_Get_Display_ਸੂਚਕਾਂਕ(SDL_DisplayID displayID);
ਬਾਹਰੀ SDL_Display_ਅੰਕੜੇ *SDL_Get_Display_Driver_ਅੰਕੜੇ(SDL_DisplayID display);
ਬਾਹਰੀ SDL_Display_ਅੰਕੜੇ *SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਪੂਰਨ SDL_Get_ਸੁਨੇਹਾ_Box_ਗਿਣਤੀ(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_ਸੈੱਟ_ਖਿੜਕੀ_HDRProperties(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_HDROutputProperties *HDR, bool send_event);
ਬਾਹਰੀ ਖਾਲੀ SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_Area_Insets(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ ਖੱਬਾ, ਪੂਰਨ ਸੱਜਾ, ਪੂਰਨ ਸਿਖਰ, ਪੂਰਨ bottom);

ਬਾਹਰੀ ਖਾਲੀ SDL_GL_DeduceMaxSupportedESProfile(ਪੂਰਨ *major, ਪੂਰਨ *minor);

ਬਾਹਰੀ bool SDL_Recreate_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ_Flags flags);
ਬਾਹਰੀ bool SDL_Reconfigure_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ_Flags flags);
ਬਾਹਰੀ bool SDL_HasWindows(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ rel_x, ਪੂਰਨ rel_y, ਪੂਰਨ *abs_x, ਪੂਰਨ *abs_y);
ਬਾਹਰੀ ਖਾਲੀ SDL_Global_ਮੰਜ਼ਿਲ_Relative_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ abs_x, ਪੂਰਨ abs_y, ਪੂਰਨ *rel_x, ਪੂਰਨ *rel_y);
ਬਾਹਰੀ bool SDL_ShouldFocusPopup(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool SDL_ShouldRelinquishPopupFocus(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ **new_focus);

ਬਾਹਰੀ ਖਾਲੀ SDL_OnDisplayAdded(SDL_VideoDisplay *display);
ਬਾਹਰੀ ਖਾਲੀ SDL_OnDisplayMoved(SDL_VideoDisplay *display);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Shown(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Hidden(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Moved(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Resized(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_Check_ਖਿੜਕੀ_Pixel_ਮਾਪ_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Pixel_ਮਾਪ_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_ਜੀਵਤ_Resize_Update(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Minimized(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Maximized(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Restored(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Enter(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Leave(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Focus_Gained(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Focus_ਗੁਆਚਾ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Display_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_Update_ਖਿੜਕੀ_Grab(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool SDL_Update_Fullscreen_ਬਹੁਲਕ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_FullscreenOp fullscreen, bool commit);
ਬਾਹਰੀ SDL_ਖਿੜਕੀ *SDL_GetToplevelForKeyboardFocus(ਖਾਲੀ);

ਬਾਹਰੀ bool SDL_ShouldAllowTopmost(ਖਾਲੀ);

ਬਾਹਰੀ ਖਾਲੀ SDL_ToggleDragAndDropSupport(ਖਾਲੀ);

ਬਾਹਰੀ ਖਾਲੀ SDL_UpdateDesktopBounds(ਖਾਲੀ);

ਬਾਹਰੀ SDL_ਪਾਠ_ਨਿਵੇਸ਼_Type SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Type(SDL_PropertiesID props);
ਬਾਹਰੀ SDL_Capitalization SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Capitalization(SDL_PropertiesID props);
ਬਾਹਰੀ bool SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Autocorrect(SDL_PropertiesID props);
ਬਾਹਰੀ bool SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Multiline(SDL_PropertiesID props);

ਬਾਹਰੀ ਖਾਲੀ SDL_SendScreenKeyboardShown(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_SendScreenKeyboardHidden(ਖਾਲੀ);

#ਜੇ_ਅੰਤ // SDL_sysvideo_h_
