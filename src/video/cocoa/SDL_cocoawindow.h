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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_cocoawindow_h_
#تعریف_کرو SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#شامل "../SDL_egl_c.h"
#اگر_ختم

#تعریف_کرو SDL_METALVIEW_لیبل 255

@class SDL_Cocoa_کھڑکی_ڈیٹا;

قسمتعریف شمار
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
    __weak SDL_Cocoa_کھڑکی_ڈیٹا *ڈیٹا_2;
    BOOL observingVisible;
    BOOL was_Ctrl_بایاں;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL اندر_Fullscreen_Transition;
    Pending_کھڑکی_Operation pending_کھڑکی_Operation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    اعشاری pending_کھڑکی_Warp_X, pending_کھڑکی_Warp_Y;
    BOOL isDragAreaRunning;
    NSTimer *زندہ_Resize_Timer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (خالی)listen:(SDL_Cocoa_کھڑکی_ڈیٹا *)ڈیٹا;
- (خالی)pauseVisibleObservation;
- (خالی)resumeVisibleObservation;
- (BOOL)سیٹ_Fullscreen_Space:(BOOL)state;
- (BOOL)is_اندر_Fullscreen_Space;
- (BOOL)is_اندر_Fullscreen_Space_Transition;
- (خالی)جوڑو_Pending_کھڑکی_Operation:(Pending_کھڑکی_Operation)operation;
- (خالی)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (خالی)سیٹ_Focus_Click_Pending:(NSInteger)button;
- (خالی)clearFocusClickPending:(NSInteger)button;
- (خالی)updateIgnoreMouseState:(NSEvent *)theEvent;
- (خالی)سیٹ_Pending_Move_X:(اعشاری)x Y:(اعشاری)y;
- (خالی)کھڑکی_Did_اختتام_Moving;
- (خالی)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)کھڑکی_Should_Close:(id)sender;
- (خالی)کھڑکی_Did_Expose:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_Change_Occlusion_State:(NSNotification *)aNotification;
- (خالی)کھڑکی_Will_آغاز_زندہ_Resize:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_انتہا_زندہ_Resize:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_Move:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_Resize:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_Miniaturize:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_Deminiaturize:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_Become_کلید:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_Resign_کلید:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_Change_Backing_Properties:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_Change_Screen_Profile:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_Change_Screen:(NSNotification *)aNotification;
- (خالی)کھڑکی_Will_Enter_بھرا_Screen:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_Enter_بھرا_Screen:(NSNotification *)aNotification;
- (خالی)کھڑکی_Will_Exit_بھرا_Screen:(NSNotification *)aNotification;
- (خالی)کھڑکی_Did_Exit_بھرا_Screen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)کھڑکی:(NSWindow *)کھڑکی will_Use_بھرا_Screen_Presentation_Options:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (خالی)update_کامیابی_Test;
- (BOOL)process_کامیابی_Test:(NSEvent *)theEvent;

// Window event handling
- (خالی)mouse_نیچے_کو:(NSEvent *)theEvent;
- (خالی)دایاں_Mouse_نیچے_کو:(NSEvent *)theEvent;
- (خالی)other_Mouse_نیچے_کو:(NSEvent *)theEvent;
- (خالی)mouse_اوپر:(NSEvent *)theEvent;
- (خالی)دایاں_Mouse_اوپر:(NSEvent *)theEvent;
- (خالی)other_Mouse_اوپر:(NSEvent *)theEvent;
- (خالی)mouseMoved:(NSEvent *)theEvent;
- (خالی)mouseDragged:(NSEvent *)theEvent;
- (خالی)دایاں_Mouse_Dragged:(NSEvent *)theEvent;
- (خالی)otherMouseDragged:(NSEvent *)theEvent;
- (خالی)scrollWheel:(NSEvent *)theEvent;
- (خالی)touchesBeganWithEvent:(NSEvent *)theEvent;
- (خالی)touchesMovedWithEvent:(NSEvent *)theEvent;
- (خالی)touchesEndedWithEvent:(NSEvent *)theEvent;
- (خالی)touchesCancelledWithEvent:(NSEvent *)theEvent;
- (خالی)magnifyWithEvent:(NSEvent *) theEvent;

// Touch event handling
- (خالی)handleTouches:(NSTouchPhase)phase withEvent:(NSEvent *)theEvent;

// Tablet event handling (but these also come through on mouse events sometimes!)
- (خالی)tabletProximity:(NSEvent *)theEvent;
- (خالی)tablet_نقطہ:(NSEvent *)theEvent;

@انتہا
/* *INDENT-ON* */

@class SDL3OpenGLContext;
@class SDL_Cocoa_Video_ڈیٹا;

@interface SDL_Cocoa_کھڑکی_ڈیٹا : NSObject
@property(nonatomic) SDL_کھڑکی *کھڑکی;
@property(nonatomic) NSWindow *nswindow;
@property(nonatomic) NSView *sdlContentView;
@property(nonatomic) NSRect viewport;
@property(nonatomic) NSMutableArray *nscontexts;
@property(nonatomic) BOOL اندر_blocking_transition;
@property(nonatomic) BOOL fullscreen_space_requested;
@property(nonatomic) BOOL was_zoomed;
@property(nonatomic) NSInteger کھڑکی_نمبر;
@property(nonatomic) NSInteger flash_request;
@property(nonatomic) SDL3_Cocoa_کھڑکی_Listener *listener;
@property(nonatomic) NSModalSession modal_session;
@property(nonatomic) SDL_Cocoa_Video_ڈیٹا *videodata;
@property(nonatomic) bool pending_سائز;
@property(nonatomic) bool pending_position;
@property(nonatomic) bool border_toggled;
@property(nonatomic) bool has_modal_dialog;

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
@property(nonatomic) EGLSurface egl_surface;
#اگر_ختم
@انتہا

خارجی bool b_اندر_منوال_Transition;

خارجی bool Cocoa_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجی خالی Cocoa_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool Cocoa_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon);
خارجی bool Cocoa_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Cocoa_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Cocoa_سیٹ_کھڑکی_Minimum_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Cocoa_سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Cocoa_سیٹ_کھڑکی_Aspect_تناسب(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Cocoa_Get_کھڑکی_سائز_اندر_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *w, صحیح *h);
خارجی bool Cocoa_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, اعشاری opacity);
خارجی خالی Cocoa_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Cocoa_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Cocoa_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Cocoa_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Cocoa_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Cocoa_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Cocoa_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered);
خارجی خالی Cocoa_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable);
خارجی خالی Cocoa_سیٹ_کھڑکی_Always_On_چوٹی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool on_چوٹی);
خارجی SDL_Fullscreen_نتیجہ Cocoa_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجی خالی *Cocoa_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *سائز);
خارجی SDL_DisplayID Cocoa_Get_Display_For_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool Cocoa_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool Cocoa_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجی خالی Cocoa_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool Cocoa_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled);
خارجی خالی Cocoa_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept);
خارجی bool Cocoa_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation);
خارجی bool Cocoa_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable);
خارجی bool Cocoa_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal);
خارجی bool Cocoa_سیٹ_کھڑکی_والد(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *والد);
خارجی bool Cocoa_Sync_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

خارجی خالی Cocoa_MenuVisibilityCallback(خالی *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر);

#اگر_ختم // SDL_cocoawindow_h_
