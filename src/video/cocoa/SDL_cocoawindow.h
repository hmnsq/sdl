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
#شامل "SDL_internal.h"

#ifndef SDL_cocoawindow_h_
#define SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#ifdef SDL_VIDEO_OPENGL_EGL
#شامل "../SDL_egl_c.h"
#endif

#define SDL_METALVIEW_TAG 255

@class SDL_CocoaWindowData;

تعریفنوع شمارش
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
    BOOL was_Ctrl_چپ;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL inFullscreenTransition;
    PendingWindowOperation pendingWindowOperation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    اعشاری pendingWindowWarpX, pendingWindowWarpY;
    BOOL isDragAreaRunning;
    NSTimer *liveResizeTimer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (تهی)listen:(SDL_CocoaWindowData *)data;
- (تهی)pauseVisibleObservation;
- (تهی)resumeVisibleObservation;
- (BOOL)setFullscreenSpace:(BOOL)state;
- (BOOL)isInFullscreenSpace;
- (BOOL)isInFullscreenSpaceTransition;
- (تهی)addPendingWindowOperation:(PendingWindowOperation)operation;
- (تهی)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (تهی)setFocusClickPending:(NSInteger)button;
- (تهی)clearFocusClickPending:(NSInteger)button;
- (تهی)updateIgnoreMouseState:(NSEvent *)theEvent;
- (تهی)setPendingMoveX:(اعشاری)x Y:(اعشاری)y;
- (تهی)windowDidFinishMoving;
- (تهی)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)windowShouldClose:(id)sender;
- (تهی)windowDidExpose:(NSNotification *)aNotification;
- (تهی)windowDidChangeOcclusionState:(NSNotification *)aNotification;
- (تهی)windowWillStartLiveResize:(NSNotification *)aNotification;
- (تهی)windowDidEndLiveResize:(NSNotification *)aNotification;
- (تهی)windowDidMove:(NSNotification *)aNotification;
- (تهی)windowDidResize:(NSNotification *)aNotification;
- (تهی)windowDidMiniaturize:(NSNotification *)aNotification;
- (تهی)windowDidDeminiaturize:(NSNotification *)aNotification;
- (تهی)window_Did_Become_کلید:(NSNotification *)aNotification;
- (تهی)window_Did_Resign_کلید:(NSNotification *)aNotification;
- (تهی)windowDidChangeBackingProperties:(NSNotification *)aNotification;
- (تهی)windowDidChangeScreenProfile:(NSNotification *)aNotification;
- (تهی)windowDidChangeScreen:(NSNotification *)aNotification;
- (تهی)windowWillEnterFullScreen:(NSNotification *)aNotification;
- (تهی)windowDidEnterFullScreen:(NSNotification *)aNotification;
- (تهی)windowWillExitFullScreen:(NSNotification *)aNotification;
- (تهی)windowDidExitFullScreen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (تهی)updateHitTest;
- (BOOL)processHitTest:(NSEvent *)theEvent;

// Window event handling
- (تهی)mouseDown:(NSEvent *)theEvent;
- (تهی)راست_Mouse_Down:(NSEvent *)theEvent;
- (تهی)otherMouseDown:(NSEvent *)theEvent;
- (تهی)mouseUp:(NSEvent *)theEvent;
- (تهی)راست_Mouse_Up:(NSEvent *)theEvent;
- (تهی)otherMouseUp:(NSEvent *)theEvent;
- (تهی)mouseMoved:(NSEvent *)theEvent;
- (تهی)mouseDragged:(NSEvent *)theEvent;
- (تهی)راست_Mouse_Dragged:(NSEvent *)theEvent;
- (تهی)otherMouseDragged:(NSEvent *)theEvent;
- (تهی)scrollWheel:(NSEvent *)theEvent;
- (تهی)touchesBeganWithEvent:(NSEvent *)theEvent;
- (تهی)touchesMovedWithEvent:(NSEvent *)theEvent;
- (تهی)touchesEndedWithEvent:(NSEvent *)theEvent;
- (تهی)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (تهی)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (تهی)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (تهی)tabletProximity:(NSEvent *)theEvent;
- (تهی)tabletPoint:(NSEvent *)theEvent;

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
@property(nonatomic) NSInteger window_عدد;
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

بیرونی bool b_inModeTransition;

بیرونی bool Cocoa_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
بیرونی تهی Cocoa_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool Cocoa_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
بیرونی bool Cocoa_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Cocoa_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Cocoa_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Cocoa_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Cocoa_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Cocoa_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, صحیح *w, صحیح *h);
بیرونی bool Cocoa_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, اعشاری opacity);
بیرونی تهی Cocoa_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Cocoa_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Cocoa_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Cocoa_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Cocoa_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Cocoa_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Cocoa_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
بیرونی تهی Cocoa_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
بیرونی تهی Cocoa_Set_Window_Always_On_بالاترین(SDL_VideoDevice *_this, SDL_Window *window, bool on_بالاترین);
بیرونی SDL_FullscreenResult Cocoa_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
بیرونی تهی *Cocoa_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
بیرونی SDL_DisplayID Cocoa_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool Cocoa_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool Cocoa_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
بیرونی تهی Cocoa_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool Cocoa_SetWindowHitTest(SDL_Window *window, bool enabled);
بیرونی تهی Cocoa_AcceptDragAndDrop(SDL_Window *window, bool accept);
بیرونی bool Cocoa_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
بیرونی bool Cocoa_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
بیرونی bool Cocoa_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
بیرونی bool Cocoa_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
بیرونی bool Cocoa_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);

بیرونی تهی Cocoa_MenuVisibilityCallback(تهی *userdata, ثابت نویسه *name, ثابت نویسه *old_مقدار, ثابت نویسه *new_مقدار);

#endif // SDL_cocoawindow_h_
