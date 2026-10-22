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
#ضمن "SDL_internal.h"

#که_نه_تعریف_شوی SDL_cocoawindow_h_
#تعریف_کړه SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
#ضمن "../SDL_egl_c.h"
#د_که_پای

#تعریف_کړه SDL_METALVIEW_نښان 255

@class SDL_Cocoa_کړکۍ_معلومات;

تعريفنوع تعداد
{
    PENDING_OPERATION_NONE = 0x00,
    PENDING_OPERATION_ENTER_FULLSCREEN = 0x01,
    PENDING_OPERATION_LEAVE_FULLSCREEN = 0x02,
    PENDING_OPERATION_MINIMIZE = 0x04,
    PENDING_OPERATION_ZOOM = 0x08
} Pending_کړکۍ_Operation;

@interface SDL3_Cocoa_کړکۍ_Listener : NSResponder <NSWindowDelegate>
{
    /* SDL_CocoaWindowData owns this Listener and has a strong reference to it.
     * To avoid reference cycles, we could have either a weak or an
     * unretained ref to the WindowData. */
    __weak SDL_Cocoa_کړکۍ_معلومات *معلومات_2;
    BOOL observingVisible;
    BOOL was_Ctrl_کیڼ;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL دننه_Fullscreen_Transition;
    Pending_کړکۍ_Operation pending_کړکۍ_Operation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    عائم pending_کړکۍ_Warp_X, pending_کړکۍ_Warp_Y;
    BOOL isDragAreaRunning;
    NSTimer *ژوندی_Resize_Timer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (فراغ)listen:(SDL_Cocoa_کړکۍ_معلومات *)معلومات;
- (فراغ)pauseVisibleObservation;
- (فراغ)resumeVisibleObservation;
- (BOOL)سېټ_Fullscreen_Space:(BOOL)state;
- (BOOL)is_دننه_Fullscreen_Space;
- (BOOL)is_دننه_Fullscreen_Space_Transition;
- (فراغ)جمع_کړه_Pending_کړکۍ_Operation:(Pending_کړکۍ_Operation)operation;
- (فراغ)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (فراغ)سېټ_Focus_Click_Pending:(NSInteger)button;
- (فراغ)clearFocusClickPending:(NSInteger)button;
- (فراغ)updateIgnoreMouseState:(NSEvent *)theEvent;
- (فراغ)سېټ_Pending_Move_X:(عائم)x Y:(عائم)y;
- (فراغ)کړکۍ_Did_پای_Moving;
- (فراغ)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)کړکۍ_Should_Close:(id)sender;
- (فراغ)کړکۍ_Did_Expose:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_Change_Occlusion_State:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Will_پیل_ژوندی_Resize:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_پای_ټکی_ژوندی_Resize:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_Move:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_Resize:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_Miniaturize:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_Deminiaturize:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_Become_کلی:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_Resign_کلی:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_Change_Backing_Properties:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_Change_Screen_Profile:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_Change_Screen:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Will_Enter_ډک_Screen:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_Enter_ډک_Screen:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Will_Exit_ډک_Screen:(NSNotification *)aNotification;
- (فراغ)کړکۍ_Did_Exit_ډک_Screen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)کړکۍ:(NSWindow *)کړکۍ will_Use_ډک_Screen_Presentation_Options:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (فراغ)update_موندنه_Test;
- (BOOL)process_موندنه_Test:(NSEvent *)theEvent;

// Window event handling
- (فراغ)mouse_ښکته:(NSEvent *)theEvent;
- (فراغ)ښی_Mouse_ښکته:(NSEvent *)theEvent;
- (فراغ)other_Mouse_ښکته:(NSEvent *)theEvent;
- (فراغ)mouse_پورته:(NSEvent *)theEvent;
- (فراغ)ښی_Mouse_پورته:(NSEvent *)theEvent;
- (فراغ)other_Mouse_پورته:(NSEvent *)theEvent;
- (فراغ)mouseMoved:(NSEvent *)theEvent;
- (فراغ)mouseDragged:(NSEvent *)theEvent;
- (فراغ)ښی_Mouse_Dragged:(NSEvent *)theEvent;
- (فراغ)otherMouseDragged:(NSEvent *)theEvent;
- (فراغ)scrollWheel:(NSEvent *)theEvent;
- (فراغ)touchesBeganWithEvent:(NSEvent *)theEvent;
- (فراغ)touchesMovedWithEvent:(NSEvent *)theEvent;
- (فراغ)touchesEndedWithEvent:(NSEvent *)theEvent;
- (فراغ)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (فراغ)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (فراغ)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (فراغ)tabletProximity:(NSEvent *)theEvent;
- (فراغ)tablet_ټکی:(NSEvent *)theEvent;

@پای_ټکی
/* *INDENT-ON* */

@class SDL3OpenGLContext;
@class SDL_Cocoa_Video_معلومات;

@interface SDL_Cocoa_کړکۍ_معلومات : NSObject
@property(nonatomic) SDL_کړکۍ *کړکۍ;
@property(nonatomic) NSWindow *nswindow;
@property(nonatomic) NSView *sdlContentView;
@property(nonatomic) NSRect viewport;
@property(nonatomic) NSMutableArray *nscontexts;
@property(nonatomic) BOOL دننه_blocking_transition;
@property(nonatomic) BOOL fullscreen_space_requested;
@property(nonatomic) BOOL was_zoomed;
@property(nonatomic) NSInteger کړکۍ_شمېره;
@property(nonatomic) NSInteger flash_request;
@property(nonatomic) SDL3_Cocoa_کړکۍ_Listener *listener;
@property(nonatomic) NSModalSession modal_session;
@property(nonatomic) SDL_Cocoa_Video_معلومات *videodata;
@property(nonatomic) bool pending_اندازه;
@property(nonatomic) bool pending_position;
@property(nonatomic) bool border_toggled;
@property(nonatomic) bool has_modal_dialog;

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
@property(nonatomic) EGLSurface egl_surface;
#د_که_پای
@پای_ټکی

خارجي bool b_دننه_ډېرپېښ_Transition;

خارجي bool Cocoa_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props);
خارجي فراغ Cocoa_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool Cocoa_سېټ_کړکۍ_Icon(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_Surface *icon);
خارجي bool Cocoa_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Cocoa_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Cocoa_سېټ_کړکۍ_Minimum_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Cocoa_سېټ_کړکۍ_اعظمي_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Cocoa_سېټ_کړکۍ_Aspect_نسبت(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Cocoa_Get_کړکۍ_اندازه_دننه_Pixels(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *w, صحيح *h);
خارجي bool Cocoa_سېټ_کړکۍ_Opacity(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, عائم opacity);
خارجي فراغ Cocoa_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Cocoa_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Cocoa_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Cocoa_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Cocoa_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Cocoa_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Cocoa_سېټ_کړکۍ_Bordered(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool bordered);
خارجي فراغ Cocoa_سېټ_کړکۍ_Resizable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool resizable);
خارجي فراغ Cocoa_سېټ_کړکۍ_Always_On_سر(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool on_سر);
خارجي SDL_Fullscreen_پایله Cocoa_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ *Cocoa_Get_کړکۍ_ICCProfile(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, size_t *اندازه);
خارجي SDL_DisplayID Cocoa_Get_Display_For_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool Cocoa_سېټ_کړکۍ_Mouse_Rect(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool Cocoa_سېټ_کړکۍ_Mouse_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed);
خارجي فراغ Cocoa_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool Cocoa_سېټ_کړکۍ_موندنه_Test(SDL_کړکۍ *کړکۍ, bool enabled);
خارجي فراغ Cocoa_AcceptDragAndDrop(SDL_کړکۍ *کړکۍ, bool accept);
خارجي bool Cocoa_Flash_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_FlashOperation operation);
خارجي bool Cocoa_سېټ_کړکۍ_Focusable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool focusable);
خارجي bool Cocoa_سېټ_کړکۍ_Modal(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool modal);
خارجي bool Cocoa_سېټ_کړکۍ_پلار(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_کړکۍ *پلار);
خارجي bool Cocoa_Sync_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

خارجي فراغ Cocoa_MenuVisibilityCallback(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_ارزښت, ثابت حرف *new_ارزښت);

#د_که_پای // SDL_cocoawindow_h_
