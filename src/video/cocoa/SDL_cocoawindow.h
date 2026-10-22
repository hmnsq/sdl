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

#ifndef SDL_cocoawindow_h_
#define SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#ifdef SDL_VIDEO_OPENGL_EGL
#ଅନ୍ତର୍ଭାଵ "../SDL_egl_c.h"
#endif

#define SDL_METALVIEW_TAG 255

@class SDL_CocoaWindowData;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
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
    BOOL was_Ctrl_ବାମ;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL inFullscreenTransition;
    PendingWindowOperation pendingWindowOperation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    ଦଶମିକ pendingWindowWarpX, pendingWindowWarpY;
    BOOL isDragAreaRunning;
    NSTimer *liveResizeTimer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)listen:(SDL_CocoaWindowData *)data;
- (ଶୂନ୍ୟ)pauseVisibleObservation;
- (ଶୂନ୍ୟ)resumeVisibleObservation;
- (BOOL)setFullscreenSpace:(BOOL)state;
- (BOOL)isInFullscreenSpace;
- (BOOL)isInFullscreenSpaceTransition;
- (ଶୂନ୍ୟ)addPendingWindowOperation:(PendingWindowOperation)operation;
- (ଶୂନ୍ୟ)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (ଶୂନ୍ୟ)setFocusClickPending:(NSInteger)button;
- (ଶୂନ୍ୟ)clearFocusClickPending:(NSInteger)button;
- (ଶୂନ୍ୟ)updateIgnoreMouseState:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)setPendingMoveX:(ଦଶମିକ)x Y:(ଦଶମିକ)y;
- (ଶୂନ୍ୟ)windowDidFinishMoving;
- (ଶୂନ୍ୟ)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)windowShouldClose:(id)sender;
- (ଶୂନ୍ୟ)windowDidExpose:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowDidChangeOcclusionState:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowWillStartLiveResize:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowDidEndLiveResize:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowDidMove:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowDidResize:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowDidMiniaturize:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowDidDeminiaturize:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)window_Did_Become_ଚାବି:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)window_Did_Resign_ଚାବି:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowDidChangeBackingProperties:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowDidChangeScreenProfile:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowDidChangeScreen:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowWillEnterFullScreen:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowDidEnterFullScreen:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowWillExitFullScreen:(NSNotification *)aNotification;
- (ଶୂନ୍ୟ)windowDidExitFullScreen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (ଶୂନ୍ୟ)updateHitTest;
- (BOOL)processHitTest:(NSEvent *)theEvent;

// Window event handling
- (ଶୂନ୍ୟ)mouseDown:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)ଡାହାଣ_Mouse_Down:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)otherMouseDown:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)mouseUp:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)ଡାହାଣ_Mouse_Up:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)otherMouseUp:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)mouseMoved:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)mouseDragged:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)ଡାହାଣ_Mouse_Dragged:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)otherMouseDragged:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)scrollWheel:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)touchesBeganWithEvent:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)touchesMovedWithEvent:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)touchesEndedWithEvent:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (ଶୂନ୍ୟ)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (ଶୂନ୍ୟ)tabletProximity:(NSEvent *)theEvent;
- (ଶୂନ୍ୟ)tabletPoint:(NSEvent *)theEvent;

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
@property(nonatomic) NSInteger window_ସଂଖ୍ୟା;
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

ବାହ୍ୟ bool b_inModeTransition;

ବାହ୍ୟ bool Cocoa_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool Cocoa_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
ବାହ୍ୟ bool Cocoa_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *h);
ବାହ୍ୟ bool Cocoa_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ଦଶମିକ opacity);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_Set_Window_Always_On_ଶୀର୍ଷ(SDL_VideoDevice *_this, SDL_Window *window, bool on_ଶୀର୍ଷ);
ବାହ୍ୟ SDL_FullscreenResult Cocoa_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ବାହ୍ୟ ଶୂନ୍ୟ *Cocoa_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
ବାହ୍ୟ SDL_DisplayID Cocoa_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool Cocoa_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool Cocoa_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool Cocoa_SetWindowHitTest(SDL_Window *window, bool enabled);
ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_AcceptDragAndDrop(SDL_Window *window, bool accept);
ବାହ୍ୟ bool Cocoa_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
ବାହ୍ୟ bool Cocoa_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
ବାହ୍ୟ bool Cocoa_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
ବାହ୍ୟ bool Cocoa_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
ବାହ୍ୟ bool Cocoa_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);

ବାହ୍ୟ ଶୂନ୍ୟ Cocoa_MenuVisibilityCallback(ଶୂନ୍ୟ *userdata, ଅଚଳ ଅକ୍ଷର *name, ଅଚଳ ଅକ୍ଷର *old_ମୂଲ୍ୟ, ଅଚଳ ଅକ୍ଷର *new_ମୂଲ୍ୟ);

#endif // SDL_cocoawindow_h_
