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
#ضمن "SDL_internal.h"

#ifndef SDL_cocoawindow_h_
#define SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#ifdef SDL_VIDEO_OPENGL_EGL
#ضمن "../SDL_egl_c.h"
#endif

#define SDL_METALVIEW_TAG 255

@class SDL_CocoaWindowData;

تعريفنوع تعداد
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
    BOOL was_Ctrl_سول;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL inFullscreenTransition;
    PendingWindowOperation pendingWindowOperation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    عائم pendingWindowWarpX, pendingWindowWarpY;
    BOOL isDragAreaRunning;
    NSTimer *liveResizeTimer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (فراغ)listen:(SDL_CocoaWindowData *)data;
- (فراغ)pauseVisibleObservation;
- (فراغ)resumeVisibleObservation;
- (BOOL)setFullscreenSpace:(BOOL)state;
- (BOOL)isInFullscreenSpace;
- (BOOL)isInFullscreenSpaceTransition;
- (فراغ)addPendingWindowOperation:(PendingWindowOperation)operation;
- (فراغ)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (فراغ)setFocusClickPending:(NSInteger)button;
- (فراغ)clearFocusClickPending:(NSInteger)button;
- (فراغ)updateIgnoreMouseState:(NSEvent *)theEvent;
- (فراغ)setPendingMoveX:(عائم)x Y:(عائم)y;
- (فراغ)windowDidFinishMoving;
- (فراغ)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)windowShouldClose:(id)sender;
- (فراغ)windowDidExpose:(NSNotification *)aNotification;
- (فراغ)windowDidChangeOcclusionState:(NSNotification *)aNotification;
- (فراغ)windowWillStartLiveResize:(NSNotification *)aNotification;
- (فراغ)windowDidEndLiveResize:(NSNotification *)aNotification;
- (فراغ)windowDidMove:(NSNotification *)aNotification;
- (فراغ)windowDidResize:(NSNotification *)aNotification;
- (فراغ)windowDidMiniaturize:(NSNotification *)aNotification;
- (فراغ)windowDidDeminiaturize:(NSNotification *)aNotification;
- (فراغ)window_Did_Become_ئاچقۇچ:(NSNotification *)aNotification;
- (فراغ)window_Did_Resign_ئاچقۇچ:(NSNotification *)aNotification;
- (فراغ)windowDidChangeBackingProperties:(NSNotification *)aNotification;
- (فراغ)windowDidChangeScreenProfile:(NSNotification *)aNotification;
- (فراغ)windowDidChangeScreen:(NSNotification *)aNotification;
- (فراغ)windowWillEnterFullScreen:(NSNotification *)aNotification;
- (فراغ)windowDidEnterFullScreen:(NSNotification *)aNotification;
- (فراغ)windowWillExitFullScreen:(NSNotification *)aNotification;
- (فراغ)windowDidExitFullScreen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (فراغ)updateHitTest;
- (BOOL)processHitTest:(NSEvent *)theEvent;

// Window event handling
- (فراغ)mouseDown:(NSEvent *)theEvent;
- (فراغ)ئوڭ_Mouse_Down:(NSEvent *)theEvent;
- (فراغ)otherMouseDown:(NSEvent *)theEvent;
- (فراغ)mouseUp:(NSEvent *)theEvent;
- (فراغ)ئوڭ_Mouse_Up:(NSEvent *)theEvent;
- (فراغ)otherMouseUp:(NSEvent *)theEvent;
- (فراغ)mouseMoved:(NSEvent *)theEvent;
- (فراغ)mouseDragged:(NSEvent *)theEvent;
- (فراغ)ئوڭ_Mouse_Dragged:(NSEvent *)theEvent;
- (فراغ)otherMouseDragged:(NSEvent *)theEvent;
- (فراغ)scrollWheel:(NSEvent *)theEvent;
- (فراغ)touchesBeganWithEvent:(NSEvent *)theEvent;
- (فراغ)touchesMovedWithEvent:(NSEvent *)theEvent;
- (فراغ)touchesEndedWithEvent:(NSEvent *)theEvent;
- (فراغ)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (فراغ)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (فراغ)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (فراغ)tabletProximity:(NSEvent *)theEvent;
- (فراغ)tabletPoint:(NSEvent *)theEvent;

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
@property(nonatomic) NSInteger window_سان;
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

خارجي bool b_inModeTransition;

خارجي bool Cocoa_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
خارجي فراغ Cocoa_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool Cocoa_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
خارجي bool Cocoa_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Cocoa_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Cocoa_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Cocoa_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Cocoa_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Cocoa_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, صحيح *w, صحيح *h);
خارجي bool Cocoa_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, عائم opacity);
خارجي فراغ Cocoa_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Cocoa_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Cocoa_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Cocoa_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Cocoa_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Cocoa_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Cocoa_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
خارجي فراغ Cocoa_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
خارجي فراغ Cocoa_Set_Window_Always_On_چوققا(SDL_VideoDevice *_this, SDL_Window *window, bool on_چوققا);
خارجي SDL_FullscreenResult Cocoa_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ *Cocoa_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
خارجي SDL_DisplayID Cocoa_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool Cocoa_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool Cocoa_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
خارجي فراغ Cocoa_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool Cocoa_SetWindowHitTest(SDL_Window *window, bool enabled);
خارجي فراغ Cocoa_AcceptDragAndDrop(SDL_Window *window, bool accept);
خارجي bool Cocoa_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
خارجي bool Cocoa_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
خارجي bool Cocoa_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
خارجي bool Cocoa_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
خارجي bool Cocoa_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);

خارجي فراغ Cocoa_MenuVisibilityCallback(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قىممەت, ثابت حرف *new_قىممەت);

#endif // SDL_cocoawindow_h_
