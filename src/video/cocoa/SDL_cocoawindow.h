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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_cocoawindow_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_METALVIEW_ਟੈਗ 255

@class SDL_Cocoa_ਖਿੜਕੀ_ਅੰਕੜੇ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    PENDING_OPERATION_NONE = 0x00,
    PENDING_OPERATION_ENTER_FULLSCREEN = 0x01,
    PENDING_OPERATION_LEAVE_FULLSCREEN = 0x02,
    PENDING_OPERATION_MINIMIZE = 0x04,
    PENDING_OPERATION_ZOOM = 0x08
} Pending_ਖਿੜਕੀ_Operation;

@interface SDL3_Cocoa_ਖਿੜਕੀ_Listener : NSResponder <NSWindowDelegate>
{
    /* SDL_CocoaWindowData owns this Listener and has a strong reference to it.
     * To avoid reference cycles, we could have either a weak or an
     * unretained ref to the WindowData. */
    __weak SDL_Cocoa_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ_2;
    BOOL observingVisible;
    BOOL was_Ctrl_ਖੱਬਾ;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL ਵਿੱਚ_Fullscreen_Transition;
    Pending_ਖਿੜਕੀ_Operation pending_ਖਿੜਕੀ_Operation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    ਦਸ਼ਮਲਵ pending_ਖਿੜਕੀ_Warp_X, pending_ਖਿੜਕੀ_Warp_Y;
    BOOL isDragAreaRunning;
    NSTimer *ਜੀਵਤ_Resize_Timer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (ਖਾਲੀ)listen:(SDL_Cocoa_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;
- (ਖਾਲੀ)pauseVisibleObservation;
- (ਖਾਲੀ)resumeVisibleObservation;
- (BOOL)ਸੈੱਟ_Fullscreen_Space:(BOOL)state;
- (BOOL)is_ਵਿੱਚ_Fullscreen_Space;
- (BOOL)is_ਵਿੱਚ_Fullscreen_Space_Transition;
- (ਖਾਲੀ)ਜੋੜੋ_Pending_ਖਿੜਕੀ_Operation:(Pending_ਖਿੜਕੀ_Operation)operation;
- (ਖਾਲੀ)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (ਖਾਲੀ)ਸੈੱਟ_Focus_Click_Pending:(NSInteger)button;
- (ਖਾਲੀ)clearFocusClickPending:(NSInteger)button;
- (ਖਾਲੀ)updateIgnoreMouseState:(NSEvent *)theEvent;
- (ਖਾਲੀ)ਸੈੱਟ_Pending_Move_X:(ਦਸ਼ਮਲਵ)x Y:(ਦਸ਼ਮਲਵ)y;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_ਅੰਤ_Moving;
- (ਖਾਲੀ)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)ਖਿੜਕੀ_Should_Close:(id)sender;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Expose:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Change_Occlusion_State:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Will_ਸ਼ੁਰੂ_ਜੀਵਤ_Resize:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_ਸਿਰਾ_ਜੀਵਤ_Resize:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Move:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Resize:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Miniaturize:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Deminiaturize:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Become_ਕੁੰਜੀ:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Resign_ਕੁੰਜੀ:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Change_Backing_Properties:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Change_Screen_Profile:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Change_Screen:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Will_Enter_ਭਰਿਆ_Screen:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Enter_ਭਰਿਆ_Screen:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Will_Exit_ਭਰਿਆ_Screen:(NSNotification *)aNotification;
- (ਖਾਲੀ)ਖਿੜਕੀ_Did_Exit_ਭਰਿਆ_Screen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)ਖਿੜਕੀ:(NSWindow *)ਖਿੜਕੀ will_Use_ਭਰਿਆ_Screen_Presentation_Options:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (ਖਾਲੀ)update_ਪ੍ਰਾਪਤੀ_Test;
- (BOOL)process_ਪ੍ਰਾਪਤੀ_Test:(NSEvent *)theEvent;

// Window event handling
- (ਖਾਲੀ)mouse_ਥੱਲੇ:(NSEvent *)theEvent;
- (ਖਾਲੀ)ਸੱਜਾ_Mouse_ਥੱਲੇ:(NSEvent *)theEvent;
- (ਖਾਲੀ)other_Mouse_ਥੱਲੇ:(NSEvent *)theEvent;
- (ਖਾਲੀ)mouse_ਉੱਪਰ:(NSEvent *)theEvent;
- (ਖਾਲੀ)ਸੱਜਾ_Mouse_ਉੱਪਰ:(NSEvent *)theEvent;
- (ਖਾਲੀ)other_Mouse_ਉੱਪਰ:(NSEvent *)theEvent;
- (ਖਾਲੀ)mouseMoved:(NSEvent *)theEvent;
- (ਖਾਲੀ)mouseDragged:(NSEvent *)theEvent;
- (ਖਾਲੀ)ਸੱਜਾ_Mouse_Dragged:(NSEvent *)theEvent;
- (ਖਾਲੀ)otherMouseDragged:(NSEvent *)theEvent;
- (ਖਾਲੀ)scrollWheel:(NSEvent *)theEvent;
- (ਖਾਲੀ)touchesBeganWithEvent:(NSEvent *)theEvent;
- (ਖਾਲੀ)touchesMovedWithEvent:(NSEvent *)theEvent;
- (ਖਾਲੀ)touchesEndedWithEvent:(NSEvent *)theEvent;
- (ਖਾਲੀ)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (ਖਾਲੀ)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (ਖਾਲੀ)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (ਖਾਲੀ)tabletProximity:(NSEvent *)theEvent;
- (ਖਾਲੀ)tablet_ਬਿੰਦੂ:(NSEvent *)theEvent;

@ਸਿਰਾ
/* *INDENT-ON* */

@class SDL3OpenGLContext;
@class SDL_Cocoa_Video_ਅੰਕੜੇ;

@interface SDL_Cocoa_ਖਿੜਕੀ_ਅੰਕੜੇ : NSObject
@property(nonatomic) SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
@property(nonatomic) NSWindow *nswindow;
@property(nonatomic) NSView *sdlContentView;
@property(nonatomic) NSRect viewport;
@property(nonatomic) NSMutableArray *nscontexts;
@property(nonatomic) BOOL ਵਿੱਚ_blocking_transition;
@property(nonatomic) BOOL fullscreen_space_requested;
@property(nonatomic) BOOL was_zoomed;
@property(nonatomic) NSInteger ਖਿੜਕੀ_ਸੰਖਿਆ;
@property(nonatomic) NSInteger flash_request;
@property(nonatomic) SDL3_Cocoa_ਖਿੜਕੀ_Listener *listener;
@property(nonatomic) NSModalSession modal_session;
@property(nonatomic) SDL_Cocoa_Video_ਅੰਕੜੇ *videodata;
@property(nonatomic) bool pending_ਮਾਪ;
@property(nonatomic) bool pending_position;
@property(nonatomic) bool border_toggled;
@property(nonatomic) bool has_modal_dialog;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
@property(nonatomic) EGLSurface egl_surface;
#ਜੇ_ਅੰਤ
@ਸਿਰਾ

ਬਾਹਰੀ bool b_ਵਿੱਚ_ਬਹੁਲਕ_Transition;

ਬਾਹਰੀ bool Cocoa_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Icon(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *icon);
ਬਾਹਰੀ bool Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *w, ਪੂਰਨ *h);
ਬਾਹਰੀ bool Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Opacity(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ opacity);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Bordered(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool bordered);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool resizable);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool on_ਸਿਖਰ);
ਬਾਹਰੀ SDL_Fullscreen_ਨਤੀਜਾ Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ਬਾਹਰੀ ਖਾਲੀ *Cocoa_Get_ਖਿੜਕੀ_ICCProfile(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, size_t *ਮਾਪ);
ਬਾਹਰੀ SDL_DisplayID Cocoa_Get_Display_For_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool enabled);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_AcceptDragAndDrop(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool accept);
ਬਾਹਰੀ bool Cocoa_Flash_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_FlashOperation operation);
ਬਾਹਰੀ bool Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Focusable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool focusable);
ਬਾਹਰੀ bool Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Modal(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool modal);
ਬਾਹਰੀ bool Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ *ਮਾਪਾ);
ਬਾਹਰੀ bool Cocoa_Sync_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

ਬਾਹਰੀ ਖਾਲੀ Cocoa_MenuVisibilityCallback(ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *old_ਮੁੱਲ, ਅਚਲ ਅੱਖਰ *new_ਮੁੱਲ);

#ਜੇ_ਅੰਤ // SDL_cocoawindow_h_
