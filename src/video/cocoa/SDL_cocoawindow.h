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
#अन्तर्भाव "SDL_internal.h"

#ifndef SDL_cocoawindow_h_
#define SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#ifdef SDL_VIDEO_OPENGL_EGL
#अन्तर्भाव "../SDL_egl_c.h"
#endif

#define SDL_METALVIEW_TAG 255

@class SDL_CocoaWindowData;

प्रकारनिर्देश गणना
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
    BOOL was_Ctrl_बायाँ;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL inFullscreenTransition;
    PendingWindowOperation pendingWindowOperation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    भिन्न pendingWindowWarpX, pendingWindowWarpY;
    BOOL isDragAreaRunning;
    NSTimer *liveResizeTimer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (शून्य)listen:(SDL_CocoaWindowData *)data;
- (शून्य)pauseVisibleObservation;
- (शून्य)resumeVisibleObservation;
- (BOOL)setFullscreenSpace:(BOOL)state;
- (BOOL)isInFullscreenSpace;
- (BOOL)isInFullscreenSpaceTransition;
- (शून्य)addPendingWindowOperation:(PendingWindowOperation)operation;
- (शून्य)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (शून्य)setFocusClickPending:(NSInteger)button;
- (शून्य)clearFocusClickPending:(NSInteger)button;
- (शून्य)updateIgnoreMouseState:(NSEvent *)theEvent;
- (शून्य)setPendingMoveX:(भिन्न)x Y:(भिन्न)y;
- (शून्य)windowDidFinishMoving;
- (शून्य)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)windowShouldClose:(id)sender;
- (शून्य)windowDidExpose:(NSNotification *)aNotification;
- (शून्य)windowDidChangeOcclusionState:(NSNotification *)aNotification;
- (शून्य)windowWillStartLiveResize:(NSNotification *)aNotification;
- (शून्य)windowDidEndLiveResize:(NSNotification *)aNotification;
- (शून्य)windowDidMove:(NSNotification *)aNotification;
- (शून्य)windowDidResize:(NSNotification *)aNotification;
- (शून्य)windowDidMiniaturize:(NSNotification *)aNotification;
- (शून्य)windowDidDeminiaturize:(NSNotification *)aNotification;
- (शून्य)window_Did_Become_कुंजी:(NSNotification *)aNotification;
- (शून्य)window_Did_Resign_कुंजी:(NSNotification *)aNotification;
- (शून्य)windowDidChangeBackingProperties:(NSNotification *)aNotification;
- (शून्य)windowDidChangeScreenProfile:(NSNotification *)aNotification;
- (शून्य)windowDidChangeScreen:(NSNotification *)aNotification;
- (शून्य)windowWillEnterFullScreen:(NSNotification *)aNotification;
- (शून्य)windowDidEnterFullScreen:(NSNotification *)aNotification;
- (शून्य)windowWillExitFullScreen:(NSNotification *)aNotification;
- (शून्य)windowDidExitFullScreen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (शून्य)updateHitTest;
- (BOOL)processHitTest:(NSEvent *)theEvent;

// Window event handling
- (शून्य)mouseDown:(NSEvent *)theEvent;
- (शून्य)दायाँ_Mouse_Down:(NSEvent *)theEvent;
- (शून्य)otherMouseDown:(NSEvent *)theEvent;
- (शून्य)mouseUp:(NSEvent *)theEvent;
- (शून्य)दायाँ_Mouse_Up:(NSEvent *)theEvent;
- (शून्य)otherMouseUp:(NSEvent *)theEvent;
- (शून्य)mouseMoved:(NSEvent *)theEvent;
- (शून्य)mouseDragged:(NSEvent *)theEvent;
- (शून्य)दायाँ_Mouse_Dragged:(NSEvent *)theEvent;
- (शून्य)otherMouseDragged:(NSEvent *)theEvent;
- (शून्य)scrollWheel:(NSEvent *)theEvent;
- (शून्य)touchesBeganWithEvent:(NSEvent *)theEvent;
- (शून्य)touchesMovedWithEvent:(NSEvent *)theEvent;
- (शून्य)touchesEndedWithEvent:(NSEvent *)theEvent;
- (शून्य)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (शून्य)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (शून्य)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (शून्य)tabletProximity:(NSEvent *)theEvent;
- (शून्य)tabletPoint:(NSEvent *)theEvent;

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
@property(nonatomic) NSInteger window_संख्या;
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

बाह्य bool b_inModeTransition;

बाह्य bool Cocoa_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य शून्य Cocoa_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Cocoa_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
बाह्य bool Cocoa_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Cocoa_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Cocoa_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Cocoa_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Cocoa_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Cocoa_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *w, पूर्णाङ्क *h);
बाह्य bool Cocoa_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, भिन्न opacity);
बाह्य शून्य Cocoa_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Cocoa_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Cocoa_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Cocoa_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Cocoa_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Cocoa_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Cocoa_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
बाह्य शून्य Cocoa_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
बाह्य शून्य Cocoa_Set_Window_Always_On_शीर्ष(SDL_VideoDevice *_this, SDL_Window *window, bool on_शीर्ष);
बाह्य SDL_FullscreenResult Cocoa_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
बाह्य शून्य *Cocoa_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
बाह्य SDL_DisplayID Cocoa_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Cocoa_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Cocoa_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य शून्य Cocoa_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Cocoa_SetWindowHitTest(SDL_Window *window, bool enabled);
बाह्य शून्य Cocoa_AcceptDragAndDrop(SDL_Window *window, bool accept);
बाह्य bool Cocoa_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
बाह्य bool Cocoa_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
बाह्य bool Cocoa_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
बाह्य bool Cocoa_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
बाह्य bool Cocoa_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);

बाह्य शून्य Cocoa_MenuVisibilityCallback(शून्य *userdata, ध्रुव वर्ण *name, ध्रुव वर्ण *old_मूल्य, ध्रुव वर्ण *new_मूल्य);

#endif // SDL_cocoawindow_h_
