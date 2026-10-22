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

#ifndef SDL_cocoawindow_h_
#define SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#ifdef SDL_VIDEO_OPENGL_EGL
#அந்தர்பாவ "../SDL_egl_c.h"
#endif

#define SDL_METALVIEW_TAG 255

@class SDL_CocoaWindowData;

வகைவரை எண்ணிக்கை
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
    BOOL was_Ctrl_இடது;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL inFullscreenTransition;
    PendingWindowOperation pendingWindowOperation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    தசம pendingWindowWarpX, pendingWindowWarpY;
    BOOL isDragAreaRunning;
    NSTimer *liveResizeTimer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (வெறுமை)listen:(SDL_CocoaWindowData *)data;
- (வெறுமை)pauseVisibleObservation;
- (வெறுமை)resumeVisibleObservation;
- (BOOL)setFullscreenSpace:(BOOL)state;
- (BOOL)isInFullscreenSpace;
- (BOOL)isInFullscreenSpaceTransition;
- (வெறுமை)addPendingWindowOperation:(PendingWindowOperation)operation;
- (வெறுமை)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (வெறுமை)setFocusClickPending:(NSInteger)button;
- (வெறுமை)clearFocusClickPending:(NSInteger)button;
- (வெறுமை)updateIgnoreMouseState:(NSEvent *)theEvent;
- (வெறுமை)setPendingMoveX:(தசம)x Y:(தசம)y;
- (வெறுமை)windowDidFinishMoving;
- (வெறுமை)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)windowShouldClose:(id)sender;
- (வெறுமை)windowDidExpose:(NSNotification *)aNotification;
- (வெறுமை)windowDidChangeOcclusionState:(NSNotification *)aNotification;
- (வெறுமை)windowWillStartLiveResize:(NSNotification *)aNotification;
- (வெறுமை)windowDidEndLiveResize:(NSNotification *)aNotification;
- (வெறுமை)windowDidMove:(NSNotification *)aNotification;
- (வெறுமை)windowDidResize:(NSNotification *)aNotification;
- (வெறுமை)windowDidMiniaturize:(NSNotification *)aNotification;
- (வெறுமை)windowDidDeminiaturize:(NSNotification *)aNotification;
- (வெறுமை)window_Did_Become_சாவி:(NSNotification *)aNotification;
- (வெறுமை)window_Did_Resign_சாவி:(NSNotification *)aNotification;
- (வெறுமை)windowDidChangeBackingProperties:(NSNotification *)aNotification;
- (வெறுமை)windowDidChangeScreenProfile:(NSNotification *)aNotification;
- (வெறுமை)windowDidChangeScreen:(NSNotification *)aNotification;
- (வெறுமை)windowWillEnterFullScreen:(NSNotification *)aNotification;
- (வெறுமை)windowDidEnterFullScreen:(NSNotification *)aNotification;
- (வெறுமை)windowWillExitFullScreen:(NSNotification *)aNotification;
- (வெறுமை)windowDidExitFullScreen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (வெறுமை)updateHitTest;
- (BOOL)processHitTest:(NSEvent *)theEvent;

// Window event handling
- (வெறுமை)mouseDown:(NSEvent *)theEvent;
- (வெறுமை)வலது_Mouse_Down:(NSEvent *)theEvent;
- (வெறுமை)otherMouseDown:(NSEvent *)theEvent;
- (வெறுமை)mouseUp:(NSEvent *)theEvent;
- (வெறுமை)வலது_Mouse_Up:(NSEvent *)theEvent;
- (வெறுமை)otherMouseUp:(NSEvent *)theEvent;
- (வெறுமை)mouseMoved:(NSEvent *)theEvent;
- (வெறுமை)mouseDragged:(NSEvent *)theEvent;
- (வெறுமை)வலது_Mouse_Dragged:(NSEvent *)theEvent;
- (வெறுமை)otherMouseDragged:(NSEvent *)theEvent;
- (வெறுமை)scrollWheel:(NSEvent *)theEvent;
- (வெறுமை)touchesBeganWithEvent:(NSEvent *)theEvent;
- (வெறுமை)touchesMovedWithEvent:(NSEvent *)theEvent;
- (வெறுமை)touchesEndedWithEvent:(NSEvent *)theEvent;
- (வெறுமை)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (வெறுமை)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (வெறுமை)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (வெறுமை)tabletProximity:(NSEvent *)theEvent;
- (வெறுமை)tabletPoint:(NSEvent *)theEvent;

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
@property(nonatomic) NSInteger window_எண்;
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

வெளி bool b_inModeTransition;

வெளி bool Cocoa_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
வெளி வெறுமை Cocoa_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool Cocoa_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
வெளி bool Cocoa_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Cocoa_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Cocoa_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Cocoa_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Cocoa_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Cocoa_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, முழு *w, முழு *h);
வெளி bool Cocoa_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, தசம opacity);
வெளி வெறுமை Cocoa_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Cocoa_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Cocoa_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Cocoa_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Cocoa_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Cocoa_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Cocoa_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
வெளி வெறுமை Cocoa_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
வெளி வெறுமை Cocoa_Set_Window_Always_On_உச்சி(SDL_VideoDevice *_this, SDL_Window *window, bool on_உச்சி);
வெளி SDL_FullscreenResult Cocoa_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
வெளி வெறுமை *Cocoa_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
வெளி SDL_DisplayID Cocoa_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool Cocoa_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool Cocoa_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
வெளி வெறுமை Cocoa_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool Cocoa_SetWindowHitTest(SDL_Window *window, bool enabled);
வெளி வெறுமை Cocoa_AcceptDragAndDrop(SDL_Window *window, bool accept);
வெளி bool Cocoa_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
வெளி bool Cocoa_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
வெளி bool Cocoa_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
வெளி bool Cocoa_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
வெளி bool Cocoa_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);

வெளி வெறுமை Cocoa_MenuVisibilityCallback(வெறுமை *userdata, மாறிலி எழுத்து *name, மாறிலி எழுத்து *old_மதிப்பு, மாறிலி எழுத்து *new_மதிப்பு);

#endif // SDL_cocoawindow_h_
