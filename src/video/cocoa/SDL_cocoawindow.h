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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_cocoawindow_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_METALVIEW_ಟ್ಯಾಗ್ 255

@class SDL_Cocoa_ಕಿಟಕಿ_ದತ್ತಾಂಶ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    PENDING_OPERATION_NONE = 0x00,
    PENDING_OPERATION_ENTER_FULLSCREEN = 0x01,
    PENDING_OPERATION_LEAVE_FULLSCREEN = 0x02,
    PENDING_OPERATION_MINIMIZE = 0x04,
    PENDING_OPERATION_ZOOM = 0x08
} Pending_ಕಿಟಕಿ_Operation;

@interface SDL3_Cocoa_ಕಿಟಕಿ_Listener : NSResponder <NSWindowDelegate>
{
    /* SDL_CocoaWindowData owns this Listener and has a strong reference to it.
     * To avoid reference cycles, we could have either a weak or an
     * unretained ref to the WindowData. */
    __weak SDL_Cocoa_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ_2;
    BOOL observingVisible;
    BOOL was_Ctrl_ಎಡ;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL ಒಳ_Fullscreen_Transition;
    Pending_ಕಿಟಕಿ_Operation pending_ಕಿಟಕಿ_Operation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    ದಶಮಾಂಶ pending_ಕಿಟಕಿ_Warp_X, pending_ಕಿಟಕಿ_Warp_Y;
    BOOL isDragAreaRunning;
    NSTimer *ಜೀವಂತ_Resize_Timer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)listen:(SDL_Cocoa_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
- (ಶೂನ್ಯ)pauseVisibleObservation;
- (ಶೂನ್ಯ)resumeVisibleObservation;
- (BOOL)ಗಣ_Fullscreen_Space:(BOOL)state;
- (BOOL)is_ಒಳ_Fullscreen_Space;
- (BOOL)is_ಒಳ_Fullscreen_Space_Transition;
- (ಶೂನ್ಯ)ಕೂಡಿಸು_Pending_ಕಿಟಕಿ_Operation:(Pending_ಕಿಟಕಿ_Operation)operation;
- (ಶೂನ್ಯ)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (ಶೂನ್ಯ)ಗಣ_Focus_Click_Pending:(NSInteger)button;
- (ಶೂನ್ಯ)clearFocusClickPending:(NSInteger)button;
- (ಶೂನ್ಯ)updateIgnoreMouseState:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)ಗಣ_Pending_Move_X:(ದಶಮಾಂಶ)x Y:(ದಶಮಾಂಶ)y;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_ಮುಕ್ತಾಯ_Moving;
- (ಶೂನ್ಯ)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)ಕಿಟಕಿ_Should_Close:(id)sender;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Expose:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Change_Occlusion_State:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Will_ಆರಂಭ_ಜೀವಂತ_Resize:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_ಕೊನೆ_ಜೀವಂತ_Resize:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Move:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Resize:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Miniaturize:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Deminiaturize:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Become_ಕೀಲಿ:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Resign_ಕೀಲಿ:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Change_Backing_Properties:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Change_Screen_Profile:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Change_Screen:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Will_Enter_ತುಂಬಿದ_Screen:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Enter_ತುಂಬಿದ_Screen:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Will_Exit_ತುಂಬಿದ_Screen:(NSNotification *)aNotification;
- (ಶೂನ್ಯ)ಕಿಟಕಿ_Did_Exit_ತುಂಬಿದ_Screen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)ಕಿಟಕಿ:(NSWindow *)ಕಿಟಕಿ will_Use_ತುಂಬಿದ_Screen_Presentation_Options:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (ಶೂನ್ಯ)update_ದೊರಕಿತು_Test;
- (BOOL)process_ದೊರಕಿತು_Test:(NSEvent *)theEvent;

// Window event handling
- (ಶೂನ್ಯ)mouse_ಕೆಳಕ್ಕೆ:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)ಬಲ_Mouse_ಕೆಳಕ್ಕೆ:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)other_Mouse_ಕೆಳಕ್ಕೆ:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)mouse_ಮೇಲೆ:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)ಬಲ_Mouse_ಮೇಲೆ:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)other_Mouse_ಮೇಲೆ:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)mouseMoved:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)mouseDragged:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)ಬಲ_Mouse_Dragged:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)otherMouseDragged:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)scrollWheel:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)touchesBeganWithEvent:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)touchesMovedWithEvent:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)touchesEndedWithEvent:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (ಶೂನ್ಯ)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (ಶೂನ್ಯ)tabletProximity:(NSEvent *)theEvent;
- (ಶೂನ್ಯ)tablet_ಬಿಂದು:(NSEvent *)theEvent;

@ಕೊನೆ
/* *INDENT-ON* */

@class SDL3OpenGLContext;
@class SDL_Cocoa_Video_ದತ್ತಾಂಶ;

@interface SDL_Cocoa_ಕಿಟಕಿ_ದತ್ತಾಂಶ : NSObject
@property(nonatomic) SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
@property(nonatomic) NSWindow *nswindow;
@property(nonatomic) NSView *sdlContentView;
@property(nonatomic) NSRect viewport;
@property(nonatomic) NSMutableArray *nscontexts;
@property(nonatomic) BOOL ಒಳ_blocking_transition;
@property(nonatomic) BOOL fullscreen_space_requested;
@property(nonatomic) BOOL was_zoomed;
@property(nonatomic) NSInteger ಕಿಟಕಿ_ಸಂಖ್ಯೆ;
@property(nonatomic) NSInteger flash_request;
@property(nonatomic) SDL3_Cocoa_ಕಿಟಕಿ_Listener *listener;
@property(nonatomic) NSModalSession modal_session;
@property(nonatomic) SDL_Cocoa_Video_ದತ್ತಾಂಶ *videodata;
@property(nonatomic) bool pending_ಗಾತ್ರ;
@property(nonatomic) bool pending_position;
@property(nonatomic) bool border_toggled;
@property(nonatomic) bool has_modal_dialog;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
@property(nonatomic) EGLSurface egl_surface;
#ಆದರೆ_ಅಂತ್ಯ
@ಕೊನೆ

ಬಾಹ್ಯ bool b_ಒಳ_ಬಹುಲಕ_Transition;

ಬಾಹ್ಯ bool Cocoa_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Cocoa_ಗಣ_ಕಿಟಕಿ_Icon(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *icon);
ಬಾಹ್ಯ bool Cocoa_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *w, ಪೂರ್ಣಾಂಕ *h);
ಬಾಹ್ಯ bool Cocoa_ಗಣ_ಕಿಟಕಿ_Opacity(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ opacity);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_ಗಣ_ಕಿಟಕಿ_Bordered(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool bordered);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool on_ತುದಿ);
ಬಾಹ್ಯ SDL_Fullscreen_ಫಲಿತಾಂಶ Cocoa_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ಬಾಹ್ಯ ಶೂನ್ಯ *Cocoa_Get_ಕಿಟಕಿ_ICCProfile(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, size_t *ಗಾತ್ರ_2);
ಬಾಹ್ಯ SDL_DisplayID Cocoa_Get_Display_For_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Cocoa_ಗಣ_ಕಿಟಕಿ_Mouse_Rect(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Cocoa_ಗಣ_ಕಿಟಕಿ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Cocoa_ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool enabled);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_AcceptDragAndDrop(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool accept);
ಬಾಹ್ಯ bool Cocoa_Flash_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_FlashOperation operation);
ಬಾಹ್ಯ bool Cocoa_ಗಣ_ಕಿಟಕಿ_Focusable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool focusable);
ಬಾಹ್ಯ bool Cocoa_ಗಣ_ಕಿಟಕಿ_Modal(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool modal);
ಬಾಹ್ಯ bool Cocoa_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ *ಪೋಷಕ);
ಬಾಹ್ಯ bool Cocoa_Sync_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_MenuVisibilityCallback(ಶೂನ್ಯ *userdata, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *old_ಮೌಲ್ಯ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *new_ಮೌಲ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_cocoawindow_h_
