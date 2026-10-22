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

#ifndef SDL_cocoawindow_h_
#define SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#ifdef SDL_VIDEO_OPENGL_EGL
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"
#endif

#define SDL_METALVIEW_TAG 255

@class SDL_CocoaWindowData;

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
{
    PENDING_OPERATION_NONE = 0x00,
    PENDING_OPERATION_ENTER_FULLSCREEN = 0x01,
    PENDING_OPERATION_LEAVE_FULLSCREEN = 0x02,
    PENDING_OPERATION_MINIMIZE = 0x04,
    PENDING_OPERATION_ZOOM = 0x08
} PendingWindowOperation;

@interface SDL3Cocoa_WindowListener : NSResponder <NSWindowDelegate>
{
    /* SDL_CocoaWindowData owns this Listener and has a strong reference to it.
     * To avoid reference cycles, we could have either a weak or an
     * unretained ref to the WindowData. */
    __weak SDL_CocoaWindowData *_data;
    BOOL observingVisible;
    BOOL was_Ctrl_ಎಡ;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL inFullscreenTransition;
    PendingWindowOperation pendingWindowOperation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    ಭಿನ್ನ pendingWindowWarpX, pendingWindowWarpY;
    BOOL isDragAreaRunning;
    NSTimer *liveResizeTimer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)listen:(SDL_CocoaWindowData *)data;
- (ಶೂನ್ಯ)pauseVisibleObservation;
- (ಶೂನ್ಯ)resumeVisibleObservation;
- (BOOL)setFullscreenSpace:(BOOL)state;
- (BOOL)isInFullscreenSpace;
- (BOOL)isInFullscreenSpaceTransition;
- (ಶೂನ್ಯ)addPendingWindowOperation:(PendingWindowOperation)operation;
- (ಶೂನ್ಯ)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (ಶೂನ್ಯ)setFocusClickPending:(NSInteger)button;
- (ಶೂನ್ಯ)clearFocusClickPending:(NSInteger)button;
- (ಶೂನ್ಯ)updateIgnoreMouseState:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)setPendingMoveX:(ಭಿನ್ನ)x Y:(ಭಿನ್ನ)y;
- (ಶೂನ್ಯ)windowDidFinishMoving;
- (ಶೂನ್ಯ)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)windowShouldClose:(id)sender;
- (ಶೂನ್ಯ)windowDidExpose:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowDidChangeOcclusionState:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowWillStartLiveResize:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowDidEndLiveResize:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowDidMove:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowDidResize:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowDidMiniaturize:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowDidDeminiaturize:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)window_Did_Become_ಕೀಲಿ:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)window_Did_Resign_ಕೀಲಿ:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowDidChangeBackingProperties:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowDidChangeScreenProfile:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowDidChangeScreen:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowWillEnterFullScreen:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowDidEnterFullScreen:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowWillExitFullScreen:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)windowDidExitFullScreen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (ಶೂನ್ಯ)updateHitTest;
- (BOOL)processHitTest:(NSEvent *)theEvent;

// Window event handling
- (ಶೂನ್ಯ)mouseDown:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)ಬಲ_Mouse_Down:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)otherMouseDown:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)mouseUp:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)ಬಲ_Mouse_Up:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)otherMouseUp:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)mouseMoved:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)mouseDragged:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)ಬಲ_Mouse_Dragged:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)otherMouseDragged:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)scrollWheel:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)touchesBeganWithEvent:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)touchesMovedWithEvent:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)touchesEndedWithEvent:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (ಶೂನ್ಯ)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (ಶೂನ್ಯ)tabletProximity:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)tabletPoint:(NSEvent *)theEvent;

@end
/* *INDENT-ON* */

@class SDL3OpenGLContext;
@class SDL_CocoaVideoData;

@interface SDL_CocoaWindowData : NSObject
@property(nonatomic) SDL_Window *window;
@property(nonatomic) NSWindow *nswindow;
@property(nonatomic) NSView *sdlContentView;
@property(nonatomic) NSRect viewport;
@property(nonatomic) NSMutableArray *nscontexts;
@property(nonatomic) BOOL in_blocking_transition;
@property(nonatomic) BOOL fullscreen_space_requested;
@property(nonatomic) BOOL was_zoomed;
@property(nonatomic) NSInteger window_ಸಂಖ್ಯೆ;
@property(nonatomic) NSInteger flash_request;
@property(nonatomic) SDL3Cocoa_WindowListener *listener;
@property(nonatomic) NSModalSession modal_session;
@property(nonatomic) SDL_CocoaVideoData *videodata;
@property(nonatomic) bool pending_size;
@property(nonatomic) bool pending_position;
@property(nonatomic) bool border_toggled;
@property(nonatomic) bool has_modal_dialog;

#ifdef SDL_VIDEO_OPENGL_EGL
@property(nonatomic) EGLSurface egl_surface;
#endif
@end

ಬಾಹ್ಯ bool b_inModeTransition;

ಬಾಹ್ಯ bool Cocoa_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool Cocoa_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
ಬಾಹ್ಯ bool Cocoa_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *w, ಪೂರ್ಣಾಙ್ಕ *h);
ಬಾಹ್ಯ bool Cocoa_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ಭಿನ್ನ opacity);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_Set_Window_Always_On_ತುದಿ(SDL_VideoDevice *_this, SDL_Window *window, bool on_ತುದಿ);
ಬಾಹ್ಯ SDL_FullscreenResult Cocoa_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ಬಾಹ್ಯ ಶೂನ್ಯ *Cocoa_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
ಬಾಹ್ಯ SDL_DisplayID Cocoa_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool Cocoa_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool Cocoa_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool Cocoa_SetWindowHitTest(SDL_Window *window, bool enabled);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_AcceptDragAndDrop(SDL_Window *window, bool accept);
ಬಾಹ್ಯ bool Cocoa_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
ಬಾಹ್ಯ bool Cocoa_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
ಬಾಹ್ಯ bool Cocoa_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
ಬಾಹ್ಯ bool Cocoa_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
ಬಾಹ್ಯ bool Cocoa_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);

ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_MenuVisibilityCallback(ಶೂನ್ಯ *userdata, ಧ್ರುವ ವರ್ಣ *name, ಧ್ರುವ ವರ್ಣ *old_ಮೌಲ್ಯ, ಧ್ರುವ ವರ್ಣ *new_ಮೌಲ್ಯ);

#endif // SDL_cocoawindow_h_
