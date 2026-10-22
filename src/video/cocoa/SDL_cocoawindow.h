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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_cocoawindow_h_
#घोषणा SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
#समावेश "../SDL_egl_c.h"
#पूर्ण_अगर

#घोषणा SDL_METALVIEW_TAG 255

@class SDL_Cocoa_Window_तथ्य;

प्रकार क्रमागत
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
    __weak SDL_Cocoa_Window_तथ्य *तथ्य_2;
    BOOL observingVisible;
    BOOL was_Ctrl_बायाँ;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL inFullscreenTransition;
    PendingWindowOperation pendingWindowOperation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    भग्न pendingWindowWarpX, pendingWindowWarpY;
    BOOL isDragAreaRunning;
    NSTimer *liveResizeTimer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (व्योम)listen:(SDL_Cocoa_Window_तथ्य *)तथ्य;
- (व्योम)pauseVisibleObservation;
- (व्योम)resumeVisibleObservation;
- (BOOL)setFullscreenSpace:(BOOL)state;
- (BOOL)isInFullscreenSpace;
- (BOOL)isInFullscreenSpaceTransition;
- (व्योम)addPendingWindowOperation:(PendingWindowOperation)operation;
- (व्योम)बंद;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (व्योम)setFocusClickPending:(NSInteger)button;
- (व्योम)clearFocusClickPending:(NSInteger)button;
- (व्योम)updateIgnoreMouseState:(NSEvent *)theEvent;
- (व्योम)setPendingMoveX:(भग्न)x Y:(भग्न)y;
- (व्योम)windowDidFinishMoving;
- (व्योम)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)windowShouldClose:(id)sender;
- (व्योम)windowDidExpose:(NSNotification *)aNotification;
- (व्योम)windowDidChangeOcclusionState:(NSNotification *)aNotification;
- (व्योम)windowWillStartLiveResize:(NSNotification *)aNotification;
- (व्योम)windowDidEndLiveResize:(NSNotification *)aNotification;
- (व्योम)windowDidMove:(NSNotification *)aNotification;
- (व्योम)windowDidResize:(NSNotification *)aNotification;
- (व्योम)windowDidMiniaturize:(NSNotification *)aNotification;
- (व्योम)windowDidDeminiaturize:(NSNotification *)aNotification;
- (व्योम)window_Did_Become_कुंजी:(NSNotification *)aNotification;
- (व्योम)window_Did_Resign_कुंजी:(NSNotification *)aNotification;
- (व्योम)windowDidChangeBackingProperties:(NSNotification *)aNotification;
- (व्योम)windowDidChangeScreenProfile:(NSNotification *)aNotification;
- (व्योम)windowDidChangeScreen:(NSNotification *)aNotification;
- (व्योम)windowWillEnterFullScreen:(NSNotification *)aNotification;
- (व्योम)windowDidEnterFullScreen:(NSNotification *)aNotification;
- (व्योम)windowWillExitFullScreen:(NSNotification *)aNotification;
- (व्योम)windowDidExitFullScreen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)window:(NSWindow *)window willUseFullScreenPresentationOptions:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (व्योम)updateHitTest;
- (BOOL)processHitTest:(NSEvent *)theEvent;

// Window event handling
- (व्योम)mouseDown:(NSEvent *)theEvent;
- (व्योम)दायाँ_Mouse_Down:(NSEvent *)theEvent;
- (व्योम)otherMouseDown:(NSEvent *)theEvent;
- (व्योम)mouseUp:(NSEvent *)theEvent;
- (व्योम)दायाँ_Mouse_Up:(NSEvent *)theEvent;
- (व्योम)otherMouseUp:(NSEvent *)theEvent;
- (व्योम)mouseMoved:(NSEvent *)theEvent;
- (व्योम)mouseDragged:(NSEvent *)theEvent;
- (व्योम)दायाँ_Mouse_Dragged:(NSEvent *)theEvent;
- (व्योम)otherMouseDragged:(NSEvent *)theEvent;
- (व्योम)scrollWheel:(NSEvent *)theEvent;
- (व्योम)touchesBeganWithEvent:(NSEvent *)theEvent;
- (व्योम)touchesMovedWithEvent:(NSEvent *)theEvent;
- (व्योम)touchesEndedWithEvent:(NSEvent *)theEvent;
- (व्योम)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (व्योम)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (व्योम)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (व्योम)tabletProximity:(NSEvent *)theEvent;
- (व्योम)tabletPoint:(NSEvent *)theEvent;

@end
/* *INDENT-ON* */

@class SDL3OpenGLContext;
@class SDL_Cocoa_Video_तथ्य;

@interface SDL_Cocoa_Window_तथ्य : NSObject
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
@property(nonatomic) SDL_Cocoa_Video_तथ्य *videodata;
@property(nonatomic) bool pending_आकार;
@property(nonatomic) bool pending_position;
@property(nonatomic) bool border_toggled;
@property(nonatomic) bool has_modal_dialog;

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
@property(nonatomic) EGLSurface egl_surface;
#पूर्ण_अगर
@end

बाह्य bool b_inModeTransition;

बाह्य bool Cocoa_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य व्योम Cocoa_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Cocoa_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
बाह्य bool Cocoa_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Cocoa_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Cocoa_Set_Window_Minimum_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Cocoa_Set_Window_Maximum_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Cocoa_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Cocoa_Get_Window_आकार_In_Pixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *w, पूर्णांक *h);
बाह्य bool Cocoa_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, भग्न opacity);
बाह्य व्योम Cocoa_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Cocoa_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Cocoa_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Cocoa_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Cocoa_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Cocoa_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Cocoa_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
बाह्य व्योम Cocoa_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
बाह्य व्योम Cocoa_Set_Window_Always_On_शीर्ष(SDL_VideoDevice *_this, SDL_Window *window, bool on_शीर्ष);
बाह्य SDL_Fullscreen_परिणाम Cocoa_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
बाह्य व्योम *Cocoa_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, माप_प्रकार *आकार);
बाह्य SDL_DisplayID Cocoa_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Cocoa_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Cocoa_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य व्योम Cocoa_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Cocoa_SetWindowHitTest(SDL_Window *window, bool enabled);
बाह्य व्योम Cocoa_AcceptDragAndDrop(SDL_Window *window, bool accept);
बाह्य bool Cocoa_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
बाह्य bool Cocoa_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
बाह्य bool Cocoa_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
बाह्य bool Cocoa_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
बाह्य bool Cocoa_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);

बाह्य व्योम Cocoa_MenuVisibilityCallback(व्योम *userdata, स्थिर अक्षर *name, स्थिर अक्षर *old_मूल्य, स्थिर अक्षर *new_मूल्य);

#पूर्ण_अगर // SDL_cocoawindow_h_
