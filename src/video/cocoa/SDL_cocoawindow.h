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
#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_cocoawindow_h_
#define SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#ifdef SDL_VIDEO_OPENGL_EGL
#അന്തര്ഭാവ "../SDL_egl_c.h"
#endif

#define SDL_METALVIEW_TAG 255

@class SDL_CocoaWindowData;

തരനിർവചനം എണ്ണൽ
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
    BOOL was_Ctrl_ഇടത്;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL inFullscreenTransition;
    PendingWindowOperation pendingWindowOperation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    ദശാംശം pendingWindowWarpX, pendingWindowWarpY;
    BOOL isDragAreaRunning;
    NSTimer *liveResizeTimer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (ശൂന്യം)listen:(SDL_CocoaWindowData *)data;
- (ശൂന്യം)pauseVisibleObservation;
- (ശൂന്യം)resumeVisibleObservation;
- (BOOL)setFullscreenSpace:(BOOL)state;
- (BOOL)isInFullscreenSpace;
- (BOOL)isInFullscreenSpaceTransition;
- (ശൂന്യം)addPendingWindowOperation:(PendingWindowOperation)operation;
- (ശൂന്യം)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (ശൂന്യം)setFocusClickPending:(NSInteger)button;
- (ശൂന്യം)clearFocusClickPending:(NSInteger)button;
- (ശൂന്യം)updateIgnoreMouseState:(NSEvent *)theEvent;
- (ശൂന്യം)setPendingMoveX:(ദശാംശം)x Y:(ദശാംശം)y;
- (ശൂന്യം)windowDidFinishMoving;
- (ശൂന്യം)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)windowShouldClose:(id)sender;
- (ശൂന്യം)windowDidExpose:(NSNotification *)aNotification;
- (ശൂന്യം)windowDidChangeOcclusionState:(NSNotification *)aNotification;
- (ശൂന്യം)windowWillStartLiveResize:(NSNotification *)aNotification;
- (ശൂന്യം)windowDidEndLiveResize:(NSNotification *)aNotification;
- (ശൂന്യം)windowDidMove:(NSNotification *)aNotification;
- (ശൂന്യം)windowDidResize:(NSNotification *)aNotification;
- (ശൂന്യം)windowDidMiniaturize:(NSNotification *)aNotification;
- (ശൂന്യം)windowDidDeminiaturize:(NSNotification *)aNotification;
- (ശൂന്യം)window_Did_Become_താക്കോൽ:(NSNotification *)aNotification;
- (ശൂന്യം)window_Did_Resign_താക്കോൽ:(NSNotification *)aNotification;
- (ശൂന്യം)windowDidChangeBackingProperties:(NSNotification *)aNotification;
- (ശൂന്യം)windowDidChangeScreenProfile:(NSNotification *)aNotification;
- (ശൂന്യം)windowDidChangeScreen:(NSNotification *)aNotification;
- (ശൂന്യം)windowWillEnterFullScreen:(NSNotification *)aNotification;
- (ശൂന്യം)windowDidEnterFullScreen:(NSNotification *)aNotification;
- (ശൂന്യം)windowWillExitFullScreen:(NSNotification *)aNotification;
- (ശൂന്യം)windowDidExitFullScreen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (ശൂന്യം)updateHitTest;
- (BOOL)processHitTest:(NSEvent *)theEvent;

// Window event handling
- (ശൂന്യം)mouseDown:(NSEvent *)theEvent;
- (ശൂന്യം)വലത്_Mouse_Down:(NSEvent *)theEvent;
- (ശൂന്യം)otherMouseDown:(NSEvent *)theEvent;
- (ശൂന്യം)mouseUp:(NSEvent *)theEvent;
- (ശൂന്യം)വലത്_Mouse_Up:(NSEvent *)theEvent;
- (ശൂന്യം)otherMouseUp:(NSEvent *)theEvent;
- (ശൂന്യം)mouseMoved:(NSEvent *)theEvent;
- (ശൂന്യം)mouseDragged:(NSEvent *)theEvent;
- (ശൂന്യം)വലത്_Mouse_Dragged:(NSEvent *)theEvent;
- (ശൂന്യം)otherMouseDragged:(NSEvent *)theEvent;
- (ശൂന്യം)scrollWheel:(NSEvent *)theEvent;
- (ശൂന്യം)touchesBeganWithEvent:(NSEvent *)theEvent;
- (ശൂന്യം)touchesMovedWithEvent:(NSEvent *)theEvent;
- (ശൂന്യം)touchesEndedWithEvent:(NSEvent *)theEvent;
- (ശൂന്യം)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (ശൂന്യം)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (ശൂന്യം)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (ശൂന്യം)tabletProximity:(NSEvent *)theEvent;
- (ശൂന്യം)tabletPoint:(NSEvent *)theEvent;

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
@property(nonatomic) NSInteger window_സംഖ്യ;
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

ബാഹ്യ bool b_inModeTransition;

ബാഹ്യ bool Cocoa_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ബാഹ്യ ശൂന്യം Cocoa_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool Cocoa_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
ബാഹ്യ bool Cocoa_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Cocoa_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Cocoa_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Cocoa_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Cocoa_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Cocoa_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ *w, പൂർണ്ണസംഖ്യ *h);
ബാഹ്യ bool Cocoa_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ദശാംശം opacity);
ബാഹ്യ ശൂന്യം Cocoa_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Cocoa_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Cocoa_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Cocoa_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Cocoa_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Cocoa_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Cocoa_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
ബാഹ്യ ശൂന്യം Cocoa_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
ബാഹ്യ ശൂന്യം Cocoa_Set_Window_Always_On_മുകൾ(SDL_VideoDevice *_this, SDL_Window *window, bool on_മുകൾ);
ബാഹ്യ SDL_FullscreenResult Cocoa_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ബാഹ്യ ശൂന്യം *Cocoa_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
ബാഹ്യ SDL_DisplayID Cocoa_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool Cocoa_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool Cocoa_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
ബാഹ്യ ശൂന്യം Cocoa_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool Cocoa_SetWindowHitTest(SDL_Window *window, bool enabled);
ബാഹ്യ ശൂന്യം Cocoa_AcceptDragAndDrop(SDL_Window *window, bool accept);
ബാഹ്യ bool Cocoa_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
ബാഹ്യ bool Cocoa_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
ബാഹ്യ bool Cocoa_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
ബാഹ്യ bool Cocoa_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
ബാഹ്യ bool Cocoa_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);

ബാഹ്യ ശൂന്യം Cocoa_MenuVisibilityCallback(ശൂന്യം *userdata, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *old_മൂല്യം, സ്ഥിരം അക്ഷരം *new_മൂല്യം);

#endif // SDL_cocoawindow_h_
