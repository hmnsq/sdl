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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_cocoawindow_h_
#నిర్వచించు SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
#అన్తర్భావ "../SDL_egl_c.h"
#అయితే_ముగింపు

#నిర్వచించు SDL_METALVIEW_ట్యాగ్ 255

@class SDL_Cocoa_కిటికీ_దత్తాంశం;

రకనిర్వచనం గణన
{
    PENDING_OPERATION_NONE = 0x00,
    PENDING_OPERATION_ENTER_FULLSCREEN = 0x01,
    PENDING_OPERATION_LEAVE_FULLSCREEN = 0x02,
    PENDING_OPERATION_MINIMIZE = 0x04,
    PENDING_OPERATION_ZOOM = 0x08
} Pending_కిటికీ_Operation;

@interface SDL3_Cocoa_కిటికీ_Listener : NSResponder <NSWindowDelegate>
{
    /* SDL_CocoaWindowData owns this Listener and has a strong reference to it.
     * To avoid reference cycles, we could have either a weak or an
     * unretained ref to the WindowData. */
    __weak SDL_Cocoa_కిటికీ_దత్తాంశం *దత్తాంశం_2;
    BOOL observingVisible;
    BOOL was_Ctrl_ఎడమ;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL లోపల_Fullscreen_Transition;
    Pending_కిటికీ_Operation pending_కిటికీ_Operation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    దశాంశం pending_కిటికీ_Warp_X, pending_కిటికీ_Warp_Y;
    BOOL isDragAreaRunning;
    NSTimer *సజీవ_Resize_Timer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (శూన్య)listen:(SDL_Cocoa_కిటికీ_దత్తాంశం *)దత్తాంశం;
- (శూన్య)pauseVisibleObservation;
- (శూన్య)resumeVisibleObservation;
- (BOOL)సమితి_Fullscreen_Space:(BOOL)state;
- (BOOL)is_లోపల_Fullscreen_Space;
- (BOOL)is_లోపల_Fullscreen_Space_Transition;
- (శూన్య)కూడు_Pending_కిటికీ_Operation:(Pending_కిటికీ_Operation)operation;
- (శూన్య)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (శూన్య)సమితి_Focus_Click_Pending:(NSInteger)button;
- (శూన్య)clearFocusClickPending:(NSInteger)button;
- (శూన్య)updateIgnoreMouseState:(NSEvent *)theEvent;
- (శూన్య)సమితి_Pending_Move_X:(దశాంశం)x Y:(దశాంశం)y;
- (శూన్య)కిటికీ_Did_ముగింపు_Moving;
- (శూన్య)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)కిటికీ_Should_Close:(id)sender;
- (శూన్య)కిటికీ_Did_Expose:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_Change_Occlusion_State:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Will_ప్రారంభం_సజీవ_Resize:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_చివర_సజీవ_Resize:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_Move:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_Resize:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_Miniaturize:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_Deminiaturize:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_Become_కీలకం:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_Resign_కీలకం:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_Change_Backing_Properties:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_Change_Screen_Profile:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_Change_Screen:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Will_Enter_నిండిన_Screen:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_Enter_నిండిన_Screen:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Will_Exit_నిండిన_Screen:(NSNotification *)aNotification;
- (శూన్య)కిటికీ_Did_Exit_నిండిన_Screen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)కిటికీ:(NSWindow *)కిటికీ will_Use_నిండిన_Screen_Presentation_Options:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (శూన్య)update_తగిలింది_Test;
- (BOOL)process_తగిలింది_Test:(NSEvent *)theEvent;

// Window event handling
- (శూన్య)mouse_కిందికి:(NSEvent *)theEvent;
- (శూన్య)కుడి_Mouse_కిందికి:(NSEvent *)theEvent;
- (శూన్య)other_Mouse_కిందికి:(NSEvent *)theEvent;
- (శూన్య)mouse_పైకి:(NSEvent *)theEvent;
- (శూన్య)కుడి_Mouse_పైకి:(NSEvent *)theEvent;
- (శూన్య)other_Mouse_పైకి:(NSEvent *)theEvent;
- (శూన్య)mouseMoved:(NSEvent *)theEvent;
- (శూన్య)mouseDragged:(NSEvent *)theEvent;
- (శూన్య)కుడి_Mouse_Dragged:(NSEvent *)theEvent;
- (శూన్య)otherMouseDragged:(NSEvent *)theEvent;
- (శూన్య)scrollWheel:(NSEvent *)theEvent;
- (శూన్య)touchesBeganWithEvent:(NSEvent *)theEvent;
- (శూన్య)touchesMovedWithEvent:(NSEvent *)theEvent;
- (శూన్య)touchesEndedWithEvent:(NSEvent *)theEvent;
- (శూన్య)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (శూన్య)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (శూన్య)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (శూన్య)tabletProximity:(NSEvent *)theEvent;
- (శూన్య)tablet_బిందువు:(NSEvent *)theEvent;

@చివర
/* *INDENT-ON* */

@class SDL3OpenGLContext;
@class SDL_Cocoa_Video_దత్తాంశం;

@interface SDL_Cocoa_కిటికీ_దత్తాంశం : NSObject
@property(nonatomic) SDL_కిటికీ *కిటికీ;
@property(nonatomic) NSWindow *nswindow;
@property(nonatomic) NSView *sdlContentView;
@property(nonatomic) NSRect viewport;
@property(nonatomic) NSMutableArray *nscontexts;
@property(nonatomic) BOOL లోపల_blocking_transition;
@property(nonatomic) BOOL fullscreen_space_requested;
@property(nonatomic) BOOL was_zoomed;
@property(nonatomic) NSInteger కిటికీ_సంఖ్య;
@property(nonatomic) NSInteger flash_request;
@property(nonatomic) SDL3_Cocoa_కిటికీ_Listener *listener;
@property(nonatomic) NSModalSession modal_session;
@property(nonatomic) SDL_Cocoa_Video_దత్తాంశం *videodata;
@property(nonatomic) bool pending_కొలత;
@property(nonatomic) bool pending_position;
@property(nonatomic) bool border_toggled;
@property(nonatomic) bool has_modal_dialog;

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
@property(nonatomic) EGLSurface egl_surface;
#అయితే_ముగింపు
@చివర

బాహ్య bool b_లోపల_బహుళకం_Transition;

బాహ్య bool Cocoa_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
బాహ్య శూన్య Cocoa_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool Cocoa_సమితి_కిటికీ_Icon(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *icon);
బాహ్య bool Cocoa_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Cocoa_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Cocoa_సమితి_కిటికీ_Minimum_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Cocoa_సమితి_కిటికీ_గరిష్ఠ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Cocoa_సమితి_కిటికీ_Aspect_నిష్పత్తి(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Cocoa_Get_కిటికీ_కొలత_లోపల_Pixels(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *w, పూర్ణాంకం *h);
బాహ్య bool Cocoa_సమితి_కిటికీ_Opacity(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, దశాంశం opacity);
బాహ్య శూన్య Cocoa_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Cocoa_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Cocoa_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Cocoa_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Cocoa_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Cocoa_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Cocoa_సమితి_కిటికీ_Bordered(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool bordered);
బాహ్య శూన్య Cocoa_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool resizable);
బాహ్య శూన్య Cocoa_సమితి_కిటికీ_Always_On_శిఖరం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool on_శిఖరం);
బాహ్య SDL_Fullscreen_ఫలితం Cocoa_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
బాహ్య శూన్య *Cocoa_Get_కిటికీ_ICCProfile(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, size_t *కొలత);
బాహ్య SDL_DisplayID Cocoa_Get_Display_For_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool Cocoa_సమితి_కిటికీ_Mouse_Rect(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool Cocoa_సమితి_కిటికీ_Mouse_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed);
బాహ్య శూన్య Cocoa_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool Cocoa_సమితి_కిటికీ_తగిలింది_Test(SDL_కిటికీ *కిటికీ, bool enabled);
బాహ్య శూన్య Cocoa_AcceptDragAndDrop(SDL_కిటికీ *కిటికీ, bool accept);
బాహ్య bool Cocoa_Flash_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_FlashOperation operation);
బాహ్య bool Cocoa_సమితి_కిటికీ_Focusable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool focusable);
బాహ్య bool Cocoa_సమితి_కిటికీ_Modal(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool modal);
బాహ్య bool Cocoa_సమితి_కిటికీ_మాతృ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_కిటికీ *మాతృ);
బాహ్య bool Cocoa_Sync_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

బాహ్య శూన్య Cocoa_MenuVisibilityCallback(శూన్య *userdata, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *old_విలువ, స్థిరరాశి అక్షరం *new_విలువ);

#అయితే_ముగింపు // SDL_cocoawindow_h_
