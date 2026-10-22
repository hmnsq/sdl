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

#جيڪڏهن_وصف_نه_ٿيل SDL_cocoawindow_h_
#وصف_ڪريو SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
#ضمن "../SDL_egl_c.h"
#جيڪڏهن_پورو

#وصف_ڪريو SDL_METALVIEW_ٽيگ 255

@class SDL_Cocoa_دري_معلومات;

تعريفنوع تعداد
{
    PENDING_OPERATION_NONE = 0x00,
    PENDING_OPERATION_ENTER_FULLSCREEN = 0x01,
    PENDING_OPERATION_LEAVE_FULLSCREEN = 0x02,
    PENDING_OPERATION_MINIMIZE = 0x04,
    PENDING_OPERATION_ZOOM = 0x08
} Pending_دري_Operation;

@interface SDL3_Cocoa_دري_Listener : NSResponder <NSWindowDelegate>
{
    /* SDL_CocoaWindowData owns this Listener and has a strong reference to it.
     * To avoid reference cycles, we could have either a weak or an
     * unretained ref to the WindowData. */
    __weak SDL_Cocoa_دري_معلومات *معلومات_2;
    BOOL observingVisible;
    BOOL was_Ctrl_کاٻو;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL اندريون_Fullscreen_Transition;
    Pending_دري_Operation pending_دري_Operation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    عائم pending_دري_Warp_X, pending_دري_Warp_Y;
    BOOL isDragAreaRunning;
    NSTimer *جيئرو_Resize_Timer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (فراغ)listen:(SDL_Cocoa_دري_معلومات *)معلومات;
- (فراغ)pauseVisibleObservation;
- (فراغ)resumeVisibleObservation;
- (BOOL)سيٽ_Fullscreen_Space:(BOOL)state;
- (BOOL)is_اندريون_Fullscreen_Space;
- (BOOL)is_اندريون_Fullscreen_Space_Transition;
- (فراغ)جوڙيو_Pending_دري_Operation:(Pending_دري_Operation)operation;
- (فراغ)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (فراغ)سيٽ_Focus_Click_Pending:(NSInteger)button;
- (فراغ)clearFocusClickPending:(NSInteger)button;
- (فراغ)updateIgnoreMouseState:(NSEvent *)theEvent;
- (فراغ)سيٽ_Pending_Move_X:(عائم)x Y:(عائم)y;
- (فراغ)دري_Did_پڄاڻي_Moving;
- (فراغ)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)دري_Should_Close:(id)sender;
- (فراغ)دري_Did_Expose:(NSNotification *)aNotification;
- (فراغ)دري_Did_Change_Occlusion_State:(NSNotification *)aNotification;
- (فراغ)دري_Will_شروعات_جيئرو_Resize:(NSNotification *)aNotification;
- (فراغ)دري_Did_پڇاڙي_جيئرو_Resize:(NSNotification *)aNotification;
- (فراغ)دري_Did_Move:(NSNotification *)aNotification;
- (فراغ)دري_Did_Resize:(NSNotification *)aNotification;
- (فراغ)دري_Did_Miniaturize:(NSNotification *)aNotification;
- (فراغ)دري_Did_Deminiaturize:(NSNotification *)aNotification;
- (فراغ)دري_Did_Become_ڪنجي:(NSNotification *)aNotification;
- (فراغ)دري_Did_Resign_ڪنجي:(NSNotification *)aNotification;
- (فراغ)دري_Did_Change_Backing_Properties:(NSNotification *)aNotification;
- (فراغ)دري_Did_Change_Screen_Profile:(NSNotification *)aNotification;
- (فراغ)دري_Did_Change_Screen:(NSNotification *)aNotification;
- (فراغ)دري_Will_Enter_ڀريل_Screen:(NSNotification *)aNotification;
- (فراغ)دري_Did_Enter_ڀريل_Screen:(NSNotification *)aNotification;
- (فراغ)دري_Will_Exit_ڀريل_Screen:(NSNotification *)aNotification;
- (فراغ)دري_Did_Exit_ڀريل_Screen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)دري:(NSWindow *)دري will_Use_ڀريل_Screen_Presentation_Options:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (فراغ)update_ڪاميابي_Test;
- (BOOL)process_ڪاميابي_Test:(NSEvent *)theEvent;

// Window event handling
- (فراغ)mouse_هيٺ_ڏانهن:(NSEvent *)theEvent;
- (فراغ)ساڄو_Mouse_هيٺ_ڏانهن:(NSEvent *)theEvent;
- (فراغ)other_Mouse_هيٺ_ڏانهن:(NSEvent *)theEvent;
- (فراغ)mouse_مٿي:(NSEvent *)theEvent;
- (فراغ)ساڄو_Mouse_مٿي:(NSEvent *)theEvent;
- (فراغ)other_Mouse_مٿي:(NSEvent *)theEvent;
- (فراغ)mouseMoved:(NSEvent *)theEvent;
- (فراغ)mouseDragged:(NSEvent *)theEvent;
- (فراغ)ساڄو_Mouse_Dragged:(NSEvent *)theEvent;
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
- (فراغ)tablet_نقطو:(NSEvent *)theEvent;

@پڇاڙي
/* *INDENT-ON* */

@class SDL3OpenGLContext;
@class SDL_Cocoa_Video_معلومات;

@interface SDL_Cocoa_دري_معلومات : NSObject
@property(nonatomic) SDL_دري *دري;
@property(nonatomic) NSWindow *nswindow;
@property(nonatomic) NSView *sdlContentView;
@property(nonatomic) NSRect viewport;
@property(nonatomic) NSMutableArray *nscontexts;
@property(nonatomic) BOOL اندريون_blocking_transition;
@property(nonatomic) BOOL fullscreen_space_requested;
@property(nonatomic) BOOL was_zoomed;
@property(nonatomic) NSInteger دري_عدد;
@property(nonatomic) NSInteger flash_request;
@property(nonatomic) SDL3_Cocoa_دري_Listener *listener;
@property(nonatomic) NSModalSession modal_session;
@property(nonatomic) SDL_Cocoa_Video_معلومات *videodata;
@property(nonatomic) bool pending_سائيز;
@property(nonatomic) bool pending_position;
@property(nonatomic) bool border_toggled;
@property(nonatomic) bool has_modal_dialog;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
@property(nonatomic) EGLSurface egl_surface;
#جيڪڏهن_پورو
@پڇاڙي

خارجي bool b_اندريون_گهڻائي_Transition;

خارجي bool Cocoa_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props);
خارجي فراغ Cocoa_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Cocoa_سيٽ_دري_Icon(SDL_VideoDevice *_this, SDL_دري *دري, SDL_Surface *icon);
خارجي bool Cocoa_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Cocoa_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Cocoa_سيٽ_دري_Minimum_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Cocoa_سيٽ_دري_وڌ_کان_وڌ_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Cocoa_سيٽ_دري_Aspect_تناسب(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Cocoa_Get_دري_سائيز_اندريون_Pixels(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *w, صحيح *h);
خارجي bool Cocoa_سيٽ_دري_Opacity(SDL_VideoDevice *_this, SDL_دري *دري, عائم opacity);
خارجي فراغ Cocoa_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Cocoa_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Cocoa_Raise_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Cocoa_Maximize_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Cocoa_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Cocoa_Restore_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Cocoa_سيٽ_دري_Bordered(SDL_VideoDevice *_this, SDL_دري *دري, bool bordered);
خارجي فراغ Cocoa_سيٽ_دري_Resizable(SDL_VideoDevice *_this, SDL_دري *دري, bool resizable);
خارجي فراغ Cocoa_سيٽ_دري_Always_On_چوٽي(SDL_VideoDevice *_this, SDL_دري *دري, bool on_چوٽي);
خارجي SDL_Fullscreen_نتيجو Cocoa_سيٽ_دري_Fullscreen(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ *Cocoa_Get_دري_ICCProfile(SDL_VideoDevice *_this, SDL_دري *دري, size_t *سائيز);
خارجي SDL_DisplayID Cocoa_Get_Display_For_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Cocoa_سيٽ_دري_Mouse_Rect(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Cocoa_سيٽ_دري_Mouse_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed);
خارجي فراغ Cocoa_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Cocoa_سيٽ_دري_ڪاميابي_Test(SDL_دري *دري, bool enabled);
خارجي فراغ Cocoa_AcceptDragAndDrop(SDL_دري *دري, bool accept);
خارجي bool Cocoa_Flash_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_FlashOperation operation);
خارجي bool Cocoa_سيٽ_دري_Focusable(SDL_VideoDevice *_this, SDL_دري *دري, bool focusable);
خارجي bool Cocoa_سيٽ_دري_Modal(SDL_VideoDevice *_this, SDL_دري *دري, bool modal);
خارجي bool Cocoa_سيٽ_دري_والد(SDL_VideoDevice *_this, SDL_دري *دري, SDL_دري *والد);
خارجي bool Cocoa_Sync_دري(SDL_VideoDevice *_this, SDL_دري *دري);

خارجي فراغ Cocoa_MenuVisibilityCallback(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر);

#جيڪڏهن_پورو // SDL_cocoawindow_h_
