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

#جے_بنا_تعریف SDL_cocoawindow_h_
#تعریف_کرو SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#ضمن "../SDL_egl_c.h"
#جے_انت

#تعریف_کرو SDL_METALVIEW_ٹیگ 255

@class SDL_Cocoa_کھڑکی_انکڑے;

تعريفنوع تعداد
{
    PENDING_OPERATION_NONE = 0x00,
    PENDING_OPERATION_ENTER_FULLSCREEN = 0x01,
    PENDING_OPERATION_LEAVE_FULLSCREEN = 0x02,
    PENDING_OPERATION_MINIMIZE = 0x04,
    PENDING_OPERATION_ZOOM = 0x08
} Pending_کھڑکی_Operation;

@interface SDL3_Cocoa_کھڑکی_Listener : NSResponder <NSWindowDelegate>
{
    /* SDL_CocoaWindowData owns this Listener and has a strong reference to it.
     * To avoid reference cycles, we could have either a weak or an
     * unretained ref to the WindowData. */
    __weak SDL_Cocoa_کھڑکی_انکڑے *انکڑے_2;
    BOOL observingVisible;
    BOOL was_Ctrl_بایاں;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL وچ_Fullscreen_Transition;
    Pending_کھڑکی_Operation pending_کھڑکی_Operation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    عائم pending_کھڑکی_Warp_X, pending_کھڑکی_Warp_Y;
    BOOL isDragAreaRunning;
    NSTimer *جیوندا_Resize_Timer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (فراغ)listen:(SDL_Cocoa_کھڑکی_انکڑے *)انکڑے;
- (فراغ)pauseVisibleObservation;
- (فراغ)resumeVisibleObservation;
- (BOOL)سیٹ_Fullscreen_Space:(BOOL)state;
- (BOOL)is_وچ_Fullscreen_Space;
- (BOOL)is_وچ_Fullscreen_Space_Transition;
- (فراغ)جوڑو_Pending_کھڑکی_Operation:(Pending_کھڑکی_Operation)operation;
- (فراغ)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (فراغ)سیٹ_Focus_Click_Pending:(NSInteger)button;
- (فراغ)clearFocusClickPending:(NSInteger)button;
- (فراغ)updateIgnoreMouseState:(NSEvent *)theEvent;
- (فراغ)سیٹ_Pending_Move_X:(عائم)x Y:(عائم)y;
- (فراغ)کھڑکی_Did_انت_Moving;
- (فراغ)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)کھڑکی_Should_Close:(id)sender;
- (فراغ)کھڑکی_Did_Expose:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_Change_Occlusion_State:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Will_شروع_جیوندا_Resize:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_سرا_جیوندا_Resize:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_Move:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_Resize:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_Miniaturize:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_Deminiaturize:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_Become_کلید:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_Resign_کلید:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_Change_Backing_Properties:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_Change_Screen_Profile:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_Change_Screen:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Will_Enter_بھریا_Screen:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_Enter_بھریا_Screen:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Will_Exit_بھریا_Screen:(NSNotification *)aNotification;
- (فراغ)کھڑکی_Did_Exit_بھریا_Screen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)کھڑکی:(NSWindow *)کھڑکی will_Use_بھریا_Screen_Presentation_Options:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (فراغ)update_کامیابی_Test;
- (BOOL)process_کامیابی_Test:(NSEvent *)theEvent;

// Window event handling
- (فراغ)mouse_تھلے:(NSEvent *)theEvent;
- (فراغ)دایاں_Mouse_تھلے:(NSEvent *)theEvent;
- (فراغ)other_Mouse_تھلے:(NSEvent *)theEvent;
- (فراغ)mouse_اتے:(NSEvent *)theEvent;
- (فراغ)دایاں_Mouse_اتے:(NSEvent *)theEvent;
- (فراغ)other_Mouse_اتے:(NSEvent *)theEvent;
- (فراغ)mouseMoved:(NSEvent *)theEvent;
- (فراغ)mouseDragged:(NSEvent *)theEvent;
- (فراغ)دایاں_Mouse_Dragged:(NSEvent *)theEvent;
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
- (فراغ)tablet_نقطہ:(NSEvent *)theEvent;

@سرا
/* *INDENT-ON* */

@class SDL3OpenGLContext;
@class SDL_Cocoa_Video_انکڑے;

@interface SDL_Cocoa_کھڑکی_انکڑے : NSObject
@property(nonatomic) SDL_کھڑکی *کھڑکی;
@property(nonatomic) NSWindow *nswindow;
@property(nonatomic) NSView *sdlContentView;
@property(nonatomic) NSRect viewport;
@property(nonatomic) NSMutableArray *nscontexts;
@property(nonatomic) BOOL وچ_blocking_transition;
@property(nonatomic) BOOL fullscreen_space_requested;
@property(nonatomic) BOOL was_zoomed;
@property(nonatomic) NSInteger کھڑکی_نمبر;
@property(nonatomic) NSInteger flash_request;
@property(nonatomic) SDL3_Cocoa_کھڑکی_Listener *listener;
@property(nonatomic) NSModalSession modal_session;
@property(nonatomic) SDL_Cocoa_Video_انکڑے *videodata;
@property(nonatomic) bool pending_ناپ;
@property(nonatomic) bool pending_position;
@property(nonatomic) bool border_toggled;
@property(nonatomic) bool has_modal_dialog;

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
@property(nonatomic) EGLSurface egl_surface;
#جے_انت
@سرا

خارجي bool b_وچ_منوال_Transition;

خارجي bool Cocoa_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجي فراغ Cocoa_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Cocoa_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon);
خارجي bool Cocoa_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Cocoa_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Cocoa_سیٹ_کھڑکی_Minimum_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Cocoa_سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Cocoa_سیٹ_کھڑکی_Aspect_تناسب(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Cocoa_Get_کھڑکی_ناپ_وچ_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *w, صحيح *h);
خارجي bool Cocoa_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, عائم opacity);
خارجي فراغ Cocoa_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Cocoa_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Cocoa_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Cocoa_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Cocoa_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Cocoa_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Cocoa_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered);
خارجي فراغ Cocoa_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable);
خارجي فراغ Cocoa_سیٹ_کھڑکی_Always_On_چوٹی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool on_چوٹی);
خارجي SDL_Fullscreen_نتیجہ Cocoa_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ *Cocoa_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *ناپ);
خارجي SDL_DisplayID Cocoa_Get_Display_For_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Cocoa_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Cocoa_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجي فراغ Cocoa_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Cocoa_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled);
خارجي فراغ Cocoa_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept);
خارجي bool Cocoa_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation);
خارجي bool Cocoa_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable);
خارجي bool Cocoa_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal);
خارجي bool Cocoa_سیٹ_کھڑکی_ماپا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *ماپا);
خارجي bool Cocoa_Sync_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

خارجي فراغ Cocoa_MenuVisibilityCallback(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر);

#جے_انت // SDL_cocoawindow_h_
