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

#اگر_تعریف_نشده SDL_cocoawindow_h_
#تعریف_کن SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
#ضمن "../SDL_egl_c.h"
#پایان_اگر

#تعریف_کن SDL_METALVIEW_برچسب 255

@class SDL_Cocoa_پنجره_داده;

تعريفنوع تعداد
{
    PENDING_OPERATION_NONE = 0x00,
    PENDING_OPERATION_ENTER_FULLSCREEN = 0x01,
    PENDING_OPERATION_LEAVE_FULLSCREEN = 0x02,
    PENDING_OPERATION_MINIMIZE = 0x04,
    PENDING_OPERATION_ZOOM = 0x08
} Pending_پنجره_Operation;

@interface SDL3_Cocoa_پنجره_Listener : NSResponder <NSWindowDelegate>
{
    /* SDL_CocoaWindowData owns this Listener and has a strong reference to it.
     * To avoid reference cycles, we could have either a weak or an
     * unretained ref to the WindowData. */
    __weak SDL_Cocoa_پنجره_داده *داده_2;
    BOOL observingVisible;
    BOOL was_Ctrl_چپ;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL درون_Fullscreen_Transition;
    Pending_پنجره_Operation pending_پنجره_Operation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    عائم pending_پنجره_Warp_X, pending_پنجره_Warp_Y;
    BOOL isDragAreaRunning;
    NSTimer *زنده_Resize_Timer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (فراغ)listen:(SDL_Cocoa_پنجره_داده *)داده;
- (فراغ)pauseVisibleObservation;
- (فراغ)resumeVisibleObservation;
- (BOOL)مجموعه_Fullscreen_Space:(BOOL)state;
- (BOOL)is_درون_Fullscreen_Space;
- (BOOL)is_درون_Fullscreen_Space_Transition;
- (فراغ)جمع_کن_Pending_پنجره_Operation:(Pending_پنجره_Operation)operation;
- (فراغ)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (فراغ)مجموعه_Focus_Click_Pending:(NSInteger)button;
- (فراغ)clearFocusClickPending:(NSInteger)button;
- (فراغ)updateIgnoreMouseState:(NSEvent *)theEvent;
- (فراغ)مجموعه_Pending_Move_X:(عائم)x Y:(عائم)y;
- (فراغ)پنجره_Did_پایان_Moving;
- (فراغ)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)پنجره_Should_Close:(id)sender;
- (فراغ)پنجره_Did_Expose:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_Change_Occlusion_State:(NSNotification *)aNotification;
- (فراغ)پنجره_Will_شروع_زنده_Resize:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_انتها_زنده_Resize:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_Move:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_Resize:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_Miniaturize:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_Deminiaturize:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_Become_کلید:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_Resign_کلید:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_Change_Backing_Properties:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_Change_Screen_Profile:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_Change_Screen:(NSNotification *)aNotification;
- (فراغ)پنجره_Will_Enter_پر_Screen:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_Enter_پر_Screen:(NSNotification *)aNotification;
- (فراغ)پنجره_Will_Exit_پر_Screen:(NSNotification *)aNotification;
- (فراغ)پنجره_Did_Exit_پر_Screen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)پنجره:(NSWindow *)پنجره will_Use_پر_Screen_Presentation_Options:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (فراغ)update_اصابت_Test;
- (BOOL)process_اصابت_Test:(NSEvent *)theEvent;

// Window event handling
- (فراغ)mouse_پایین:(NSEvent *)theEvent;
- (فراغ)راست_Mouse_پایین:(NSEvent *)theEvent;
- (فراغ)other_Mouse_پایین:(NSEvent *)theEvent;
- (فراغ)mouse_به_بالا:(NSEvent *)theEvent;
- (فراغ)راست_Mouse_به_بالا:(NSEvent *)theEvent;
- (فراغ)other_Mouse_به_بالا:(NSEvent *)theEvent;
- (فراغ)mouseMoved:(NSEvent *)theEvent;
- (فراغ)mouseDragged:(NSEvent *)theEvent;
- (فراغ)راست_Mouse_Dragged:(NSEvent *)theEvent;
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
- (فراغ)tablet_نقطه:(NSEvent *)theEvent;

@انتها
/* *INDENT-ON* */

@class SDL3OpenGLContext;
@class SDL_Cocoa_Video_داده;

@interface SDL_Cocoa_پنجره_داده : NSObject
@property(nonatomic) SDL_پنجره *پنجره;
@property(nonatomic) NSWindow *nswindow;
@property(nonatomic) NSView *sdlContentView;
@property(nonatomic) NSRect viewport;
@property(nonatomic) NSMutableArray *nscontexts;
@property(nonatomic) BOOL درون_blocking_transition;
@property(nonatomic) BOOL fullscreen_space_requested;
@property(nonatomic) BOOL was_zoomed;
@property(nonatomic) NSInteger پنجره_عدد;
@property(nonatomic) NSInteger flash_request;
@property(nonatomic) SDL3_Cocoa_پنجره_Listener *listener;
@property(nonatomic) NSModalSession modal_session;
@property(nonatomic) SDL_Cocoa_Video_داده *videodata;
@property(nonatomic) bool pending_اندازه;
@property(nonatomic) bool pending_position;
@property(nonatomic) bool border_toggled;
@property(nonatomic) bool has_modal_dialog;

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
@property(nonatomic) EGLSurface egl_surface;
#پایان_اگر
@انتها

خارجي bool b_درون_نما_Transition;

خارجي bool Cocoa_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props);
خارجي فراغ Cocoa_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Cocoa_مجموعه_پنجره_Icon(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_Surface *icon);
خارجي bool Cocoa_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Cocoa_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Cocoa_مجموعه_پنجره_Minimum_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Cocoa_مجموعه_پنجره_بیشینه_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Cocoa_مجموعه_پنجره_Aspect_نسبت(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Cocoa_Get_پنجره_اندازه_درون_Pixels(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *w, صحيح *h);
خارجي bool Cocoa_مجموعه_پنجره_Opacity(SDL_VideoDevice *_this, SDL_پنجره *پنجره, عائم opacity);
خارجي فراغ Cocoa_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Cocoa_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Cocoa_Raise_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Cocoa_Maximize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Cocoa_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Cocoa_Restore_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Cocoa_مجموعه_پنجره_Bordered(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool bordered);
خارجي فراغ Cocoa_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool resizable);
خارجي فراغ Cocoa_مجموعه_پنجره_Always_On_بالاترین(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool on_بالاترین);
خارجي SDL_Fullscreen_نتیجه Cocoa_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ *Cocoa_Get_پنجره_ICCProfile(SDL_VideoDevice *_this, SDL_پنجره *پنجره, size_t *اندازه);
خارجي SDL_DisplayID Cocoa_Get_Display_For_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Cocoa_مجموعه_پنجره_Mouse_Rect(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Cocoa_مجموعه_پنجره_Mouse_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed);
خارجي فراغ Cocoa_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Cocoa_مجموعه_پنجره_اصابت_Test(SDL_پنجره *پنجره, bool enabled);
خارجي فراغ Cocoa_AcceptDragAndDrop(SDL_پنجره *پنجره, bool accept);
خارجي bool Cocoa_Flash_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_FlashOperation operation);
خارجي bool Cocoa_مجموعه_پنجره_Focusable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool focusable);
خارجي bool Cocoa_مجموعه_پنجره_Modal(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool modal);
خارجي bool Cocoa_مجموعه_پنجره_والد(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_پنجره *والد);
خارجي bool Cocoa_Sync_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);

خارجي فراغ Cocoa_MenuVisibilityCallback(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_مقدار, ثابت حرف *new_مقدار);

#پایان_اگر // SDL_cocoawindow_h_
