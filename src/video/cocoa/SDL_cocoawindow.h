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
#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_cocoawindow_h_
#define SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#ifdef SDL_VIDEO_OPENGL_EGL
#অন্তর্ভাব "../SDL_egl_c.h"
#endif

#define SDL_METALVIEW_TAG 255

@class SDL_CocoaWindowData;

প্রকারনির্দেশ গণনা
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
    BOOL was_Ctrl_বাম;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL inFullscreenTransition;
    PendingWindowOperation pendingWindowOperation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    ভিন্ন pendingWindowWarpX, pendingWindowWarpY;
    BOOL isDragAreaRunning;
    NSTimer *liveResizeTimer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (শূন্য)listen:(SDL_CocoaWindowData *)data;
- (শূন্য)pauseVisibleObservation;
- (শূন্য)resumeVisibleObservation;
- (BOOL)setFullscreenSpace:(BOOL)state;
- (BOOL)isInFullscreenSpace;
- (BOOL)isInFullscreenSpaceTransition;
- (শূন্য)addPendingWindowOperation:(PendingWindowOperation)operation;
- (শূন্য)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (শূন্য)setFocusClickPending:(NSInteger)button;
- (শূন্য)clearFocusClickPending:(NSInteger)button;
- (শূন্য)updateIgnoreMouseState:(NSEvent *)theEvent;
- (শূন্য)setPendingMoveX:(ভিন্ন)x Y:(ভিন্ন)y;
- (শূন্য)windowDidFinishMoving;
- (শূন্য)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)windowShouldClose:(id)sender;
- (শূন্য)windowDidExpose:(NSNotification *)aNotification;
- (শূন্য)windowDidChangeOcclusionState:(NSNotification *)aNotification;
- (শূন্য)windowWillStartLiveResize:(NSNotification *)aNotification;
- (শূন্য)windowDidEndLiveResize:(NSNotification *)aNotification;
- (শূন্য)windowDidMove:(NSNotification *)aNotification;
- (শূন্য)windowDidResize:(NSNotification *)aNotification;
- (শূন্য)windowDidMiniaturize:(NSNotification *)aNotification;
- (শূন্য)windowDidDeminiaturize:(NSNotification *)aNotification;
- (শূন্য)window_Did_Become_চাবি:(NSNotification *)aNotification;
- (শূন্য)window_Did_Resign_চাবি:(NSNotification *)aNotification;
- (শূন্য)windowDidChangeBackingProperties:(NSNotification *)aNotification;
- (শূন্য)windowDidChangeScreenProfile:(NSNotification *)aNotification;
- (শূন্য)windowDidChangeScreen:(NSNotification *)aNotification;
- (শূন্য)windowWillEnterFullScreen:(NSNotification *)aNotification;
- (শূন্য)windowDidEnterFullScreen:(NSNotification *)aNotification;
- (শূন্য)windowWillExitFullScreen:(NSNotification *)aNotification;
- (শূন্য)windowDidExitFullScreen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (শূন্য)updateHitTest;
- (BOOL)processHitTest:(NSEvent *)theEvent;

// Window event handling
- (শূন্য)mouseDown:(NSEvent *)theEvent;
- (শূন্য)ডান_Mouse_Down:(NSEvent *)theEvent;
- (শূন্য)otherMouseDown:(NSEvent *)theEvent;
- (শূন্য)mouseUp:(NSEvent *)theEvent;
- (শূন্য)ডান_Mouse_Up:(NSEvent *)theEvent;
- (শূন্য)otherMouseUp:(NSEvent *)theEvent;
- (শূন্য)mouseMoved:(NSEvent *)theEvent;
- (শূন্য)mouseDragged:(NSEvent *)theEvent;
- (শূন্য)ডান_Mouse_Dragged:(NSEvent *)theEvent;
- (শূন্য)otherMouseDragged:(NSEvent *)theEvent;
- (শূন্য)scrollWheel:(NSEvent *)theEvent;
- (শূন্য)touchesBeganWithEvent:(NSEvent *)theEvent;
- (শূন্য)touchesMovedWithEvent:(NSEvent *)theEvent;
- (শূন্য)touchesEndedWithEvent:(NSEvent *)theEvent;
- (শূন্য)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (শূন্য)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (শূন্য)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (শূন্য)tabletProximity:(NSEvent *)theEvent;
- (শূন্য)tabletPoint:(NSEvent *)theEvent;

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
@property(nonatomic) NSInteger window_সংখ্যা;
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

বাহ্য bool b_inModeTransition;

বাহ্য bool Cocoa_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
বাহ্য শূন্য Cocoa_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool Cocoa_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
বাহ্য bool Cocoa_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Cocoa_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Cocoa_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Cocoa_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Cocoa_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Cocoa_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক *w, পূর্ণাঙ্ক *h);
বাহ্য bool Cocoa_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ভিন্ন opacity);
বাহ্য শূন্য Cocoa_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Cocoa_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Cocoa_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Cocoa_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Cocoa_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Cocoa_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Cocoa_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
বাহ্য শূন্য Cocoa_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
বাহ্য শূন্য Cocoa_Set_Window_Always_On_শীর্ষ(SDL_VideoDevice *_this, SDL_Window *window, bool on_শীর্ষ);
বাহ্য SDL_FullscreenResult Cocoa_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
বাহ্য শূন্য *Cocoa_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
বাহ্য SDL_DisplayID Cocoa_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool Cocoa_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool Cocoa_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
বাহ্য শূন্য Cocoa_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool Cocoa_SetWindowHitTest(SDL_Window *window, bool enabled);
বাহ্য শূন্য Cocoa_AcceptDragAndDrop(SDL_Window *window, bool accept);
বাহ্য bool Cocoa_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
বাহ্য bool Cocoa_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
বাহ্য bool Cocoa_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
বাহ্য bool Cocoa_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
বাহ্য bool Cocoa_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);

বাহ্য শূন্য Cocoa_MenuVisibilityCallback(শূন্য *userdata, ধ্রুব বর্ণ *name, ধ্রুব বর্ণ *old_মান, ধ্রুব বর্ণ *new_মান);

#endif // SDL_cocoawindow_h_
