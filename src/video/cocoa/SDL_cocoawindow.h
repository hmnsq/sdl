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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_cocoawindow_h_
#define SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#ifdef SDL_VIDEO_OPENGL_EGL
#અન્તર્ભાવ "../SDL_egl_c.h"
#endif

#define SDL_METALVIEW_TAG 255

@class SDL_CocoaWindowData;

પ્રકારવ્યાખ્યા ગણના
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
    BOOL was_Ctrl_ડાબું;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL inFullscreenTransition;
    PendingWindowOperation pendingWindowOperation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    દશાંશ pendingWindowWarpX, pendingWindowWarpY;
    BOOL isDragAreaRunning;
    NSTimer *liveResizeTimer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (શૂન્ય)listen:(SDL_CocoaWindowData *)data;
- (શૂન્ય)pauseVisibleObservation;
- (શૂન્ય)resumeVisibleObservation;
- (BOOL)setFullscreenSpace:(BOOL)state;
- (BOOL)isInFullscreenSpace;
- (BOOL)isInFullscreenSpaceTransition;
- (શૂન્ય)addPendingWindowOperation:(PendingWindowOperation)operation;
- (શૂન્ય)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (શૂન્ય)setFocusClickPending:(NSInteger)button;
- (શૂન્ય)clearFocusClickPending:(NSInteger)button;
- (શૂન્ય)updateIgnoreMouseState:(NSEvent *)theEvent;
- (શૂન્ય)setPendingMoveX:(દશાંશ)x Y:(દશાંશ)y;
- (શૂન્ય)windowDidFinishMoving;
- (શૂન્ય)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)windowShouldClose:(id)sender;
- (શૂન્ય)windowDidExpose:(NSNotification *)aNotification;
- (શૂન્ય)windowDidChangeOcclusionState:(NSNotification *)aNotification;
- (શૂન્ય)windowWillStartLiveResize:(NSNotification *)aNotification;
- (શૂન્ય)windowDidEndLiveResize:(NSNotification *)aNotification;
- (શૂન્ય)windowDidMove:(NSNotification *)aNotification;
- (શૂન્ય)windowDidResize:(NSNotification *)aNotification;
- (શૂન્ય)windowDidMiniaturize:(NSNotification *)aNotification;
- (શૂન્ય)windowDidDeminiaturize:(NSNotification *)aNotification;
- (શૂન્ય)window_Did_Become_ચાવી:(NSNotification *)aNotification;
- (શૂન્ય)window_Did_Resign_ચાવી:(NSNotification *)aNotification;
- (શૂન્ય)windowDidChangeBackingProperties:(NSNotification *)aNotification;
- (શૂન્ય)windowDidChangeScreenProfile:(NSNotification *)aNotification;
- (શૂન્ય)windowDidChangeScreen:(NSNotification *)aNotification;
- (શૂન્ય)windowWillEnterFullScreen:(NSNotification *)aNotification;
- (શૂન્ય)windowDidEnterFullScreen:(NSNotification *)aNotification;
- (શૂન્ય)windowWillExitFullScreen:(NSNotification *)aNotification;
- (શૂન્ય)windowDidExitFullScreen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (શૂન્ય)updateHitTest;
- (BOOL)processHitTest:(NSEvent *)theEvent;

// Window event handling
- (શૂન્ય)mouseDown:(NSEvent *)theEvent;
- (શૂન્ય)જમણું_Mouse_Down:(NSEvent *)theEvent;
- (શૂન્ય)otherMouseDown:(NSEvent *)theEvent;
- (શૂન્ય)mouseUp:(NSEvent *)theEvent;
- (શૂન્ય)જમણું_Mouse_Up:(NSEvent *)theEvent;
- (શૂન્ય)otherMouseUp:(NSEvent *)theEvent;
- (શૂન્ય)mouseMoved:(NSEvent *)theEvent;
- (શૂન્ય)mouseDragged:(NSEvent *)theEvent;
- (શૂન્ય)જમણું_Mouse_Dragged:(NSEvent *)theEvent;
- (શૂન્ય)otherMouseDragged:(NSEvent *)theEvent;
- (શૂન્ય)scrollWheel:(NSEvent *)theEvent;
- (શૂન્ય)touchesBeganWithEvent:(NSEvent *)theEvent;
- (શૂન્ય)touchesMovedWithEvent:(NSEvent *)theEvent;
- (શૂન્ય)touchesEndedWithEvent:(NSEvent *)theEvent;
- (શૂન્ય)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (શૂન્ય)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (શૂન્ય)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (શૂન્ય)tabletProximity:(NSEvent *)theEvent;
- (શૂન્ય)tabletPoint:(NSEvent *)theEvent;

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
@property(nonatomic) NSInteger window_સંખ્યા;
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

બાહ્ય bool b_inModeTransition;

બાહ્ય bool Cocoa_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
બાહ્ય શૂન્ય Cocoa_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool Cocoa_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
બાહ્ય bool Cocoa_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Cocoa_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Cocoa_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Cocoa_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Cocoa_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Cocoa_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, પૂર્ણાંક *w, પૂર્ણાંક *h);
બાહ્ય bool Cocoa_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, દશાંશ opacity);
બાહ્ય શૂન્ય Cocoa_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Cocoa_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Cocoa_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Cocoa_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Cocoa_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Cocoa_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Cocoa_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
બાહ્ય શૂન્ય Cocoa_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
બાહ્ય શૂન્ય Cocoa_Set_Window_Always_On_ટોચ(SDL_VideoDevice *_this, SDL_Window *window, bool on_ટોચ);
બાહ્ય SDL_FullscreenResult Cocoa_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
બાહ્ય શૂન્ય *Cocoa_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
બાહ્ય SDL_DisplayID Cocoa_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool Cocoa_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool Cocoa_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
બાહ્ય શૂન્ય Cocoa_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool Cocoa_SetWindowHitTest(SDL_Window *window, bool enabled);
બાહ્ય શૂન્ય Cocoa_AcceptDragAndDrop(SDL_Window *window, bool accept);
બાહ્ય bool Cocoa_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
બાહ્ય bool Cocoa_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
બાહ્ય bool Cocoa_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
બાહ્ય bool Cocoa_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
બાહ્ય bool Cocoa_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);

બાહ્ય શૂન્ય Cocoa_MenuVisibilityCallback(શૂન્ય *userdata, અચલ અક્ષર *name, અચલ અક્ષર *old_કિંમત, અચલ અક્ષર *new_કિંમત);

#endif // SDL_cocoawindow_h_
