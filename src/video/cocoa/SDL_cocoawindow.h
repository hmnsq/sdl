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

#यदि_अपरिभाषितम् SDL_cocoawindow_h_
#परिभाषय SDL_cocoawindow_h_

#import <Cocoa/Cocoa.h>

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
#अन्तर्भाव "../SDL_egl_c.h"
#यदि_अन्तः

#परिभाषय SDL_METALVIEW_चिह्नकम् 255

@class SDL_Cocoa_गवाक्षः_दत्त;

प्रकारनिर्देश गणना
{
    PENDING_OPERATION_NONE = 0x00,
    PENDING_OPERATION_ENTER_FULLSCREEN = 0x01,
    PENDING_OPERATION_LEAVE_FULLSCREEN = 0x02,
    PENDING_OPERATION_MINIMIZE = 0x04,
    PENDING_OPERATION_ZOOM = 0x08
} Pending_गवाक्षः_Operation;

@interface SDL3_Cocoa_गवाक्षः_Listener : NSResponder <NSWindowDelegate>
{
    /* SDL_CocoaWindowData owns this Listener and has a strong reference to it.
     * To avoid reference cycles, we could have either a weak or an
     * unretained ref to the WindowData. */
    __weak SDL_Cocoa_गवाक्षः_दत्त *दत्त_2;
    BOOL observingVisible;
    BOOL was_Ctrl_वामः;
    BOOL wasVisible;
    BOOL isFullscreenSpace;
    BOOL अन्तर्_Fullscreen_Transition;
    Pending_गवाक्षः_Operation pending_गवाक्षः_Operation;
    BOOL isMoving;
    BOOL isMiniaturizing;
    NSInteger focusClickPending;
    भिन्न pending_गवाक्षः_Warp_X, pending_गवाक्षः_Warp_Y;
    BOOL isDragAreaRunning;
    NSTimer *जीवितम्_Resize_Timer;
}

- (BOOL)isTouchFromTrackpad:(NSEvent *)theEvent;
- (शून्य)listen:(SDL_Cocoa_गवाक्षः_दत्त *)दत्त;
- (शून्य)pauseVisibleObservation;
- (शून्य)resumeVisibleObservation;
- (BOOL)समुच्चयः_Fullscreen_Space:(BOOL)state;
- (BOOL)is_अन्तर्_Fullscreen_Space;
- (BOOL)is_अन्तर्_Fullscreen_Space_Transition;
- (शून्य)सङ्कलय_Pending_गवाक्षः_Operation:(Pending_गवाक्षः_Operation)operation;
- (शून्य)close;

- (BOOL)isMoving;
- (BOOL)isMovingOrFocusClickPending;
- (शून्य)समुच्चयः_Focus_Click_Pending:(NSInteger)button;
- (शून्य)clearFocusClickPending:(NSInteger)button;
- (शून्य)updateIgnoreMouseState:(NSEvent *)theEvent;
- (शून्य)समुच्चयः_Pending_Move_X:(भिन्न)x Y:(भिन्न)y;
- (शून्य)गवाक्षः_Did_Finish_Moving;
- (शून्य)onMovingOrFocusClickPendingStateCleared;

// Window delegate functionality
- (BOOL)गवाक्षः_Should_Close:(id)sender;
- (शून्य)गवाक्षः_Did_Expose:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_Change_Occlusion_State:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Will_Start_जीवितम्_Resize:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_अन्तः_जीवितम्_Resize:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_Move:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_Resize:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_Miniaturize:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_Deminiaturize:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_Become_कुञ्चिका:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_Resign_कुञ्चिका:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_Change_Backing_Properties:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_Change_Screen_Profile:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_Change_Screen:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Will_Enter_पूर्णम्_Screen:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_Enter_पूर्णम्_Screen:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Will_Exit_पूर्णम्_Screen:(NSNotification *)aNotification;
- (शून्य)गवाक्षः_Did_Exit_पूर्णम्_Screen:(NSNotification *)aNotification;
- (NSApplicationPresentationOptions)गवाक्षः:(NSWindow *)गवाक्षः will_Use_पूर्णम्_Screen_Presentation_Options:(NSApplicationPresentationOptions)proposedOptions;

// See if event is in a drag area, toggle on window dragging.
- (शून्य)update_लब्धम्_Test;
- (BOOL)process_लब्धम्_Test:(NSEvent *)theEvent;

// Window event handling
- (शून्य)mouse_अधस्तात्:(NSEvent *)theEvent;
- (शून्य)दक्षिणः_Mouse_अधस्तात्:(NSEvent *)theEvent;
- (शून्य)other_Mouse_अधस्तात्:(NSEvent *)theEvent;
- (शून्य)mouse_ऊर्ध्वम्:(NSEvent *)theEvent;
- (शून्य)दक्षिणः_Mouse_ऊर्ध्वम्:(NSEvent *)theEvent;
- (शून्य)other_Mouse_ऊर्ध्वम्:(NSEvent *)theEvent;
- (शून्य)mouseMoved:(NSEvent *)theEvent;
- (शून्य)mouseDragged:(NSEvent *)theEvent;
- (शून्य)दक्षिणः_Mouse_Dragged:(NSEvent *)theEvent;
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

@अन्तः
/* *INDENT-ON* */

@class SDL3OpenGLContext;
@class SDL_Cocoa_Video_दत्त;

@interface SDL_Cocoa_गवाक्षः_दत्त : NSObject
@property(nonatomic) SDL_गवाक्षः *गवाक्षः;
@property(nonatomic) NSWindow *nswindow;
@property(nonatomic) NSView *sdlContentView;
@property(nonatomic) NSRect viewport;
@property(nonatomic) NSMutableArray *nscontexts;
@property(nonatomic) BOOL अन्तर्_blocking_transition;
@property(nonatomic) BOOL fullscreen_space_requested;
@property(nonatomic) BOOL was_zoomed;
@property(nonatomic) NSInteger गवाक्षः_सङ्ख्या;
@property(nonatomic) NSInteger flash_request;
@property(nonatomic) SDL3_Cocoa_गवाक्षः_Listener *listener;
@property(nonatomic) NSModalSession modal_session;
@property(nonatomic) SDL_Cocoa_Video_दत्त *videodata;
@property(nonatomic) bool pending_आकार;
@property(nonatomic) bool pending_position;
@property(nonatomic) bool border_toggled;
@property(nonatomic) bool has_modal_dialog;

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
@property(nonatomic) EGLSurface egl_surface;
#यदि_अन्तः
@अन्तः

बाह्य bool b_अन्तर्_बहुलकम्_Transition;

बाह्य bool Cocoa_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
बाह्य शून्य Cocoa_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Cocoa_समुच्चयः_गवाक्षः_Icon(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *icon);
बाह्य bool Cocoa_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Cocoa_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Cocoa_समुच्चयः_गवाक्षः_Minimum_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Cocoa_समुच्चयः_गवाक्षः_अधिकतमम्_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Cocoa_समुच्चयः_गवाक्षः_Aspect_अनुपातः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Cocoa_Get_गवाक्षः_आकार_अन्तर्_Pixels(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *w, पूर्णाङ्क *h);
बाह्य bool Cocoa_समुच्चयः_गवाक्षः_Opacity(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, भिन्न opacity);
बाह्य शून्य Cocoa_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Cocoa_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Cocoa_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Cocoa_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Cocoa_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Cocoa_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Cocoa_समुच्चयः_गवाक्षः_Bordered(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool bordered);
बाह्य शून्य Cocoa_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool resizable);
बाह्य शून्य Cocoa_समुच्चयः_गवाक्षः_Always_On_शिखरम्(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool on_शिखरम्);
बाह्य SDL_Fullscreen_परिणाम Cocoa_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
बाह्य शून्य *Cocoa_Get_गवाक्षः_ICCProfile(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, size_t *आकार);
बाह्य SDL_DisplayID Cocoa_Get_Display_For_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Cocoa_समुच्चयः_गवाक्षः_Mouse_Rect(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Cocoa_समुच्चयः_गवाक्षः_Mouse_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed);
बाह्य शून्य Cocoa_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Cocoa_समुच्चयः_गवाक्षः_लब्धम्_Test(SDL_गवाक्षः *गवाक्षः, bool enabled);
बाह्य शून्य Cocoa_AcceptDragAndDrop(SDL_गवाक्षः *गवाक्षः, bool accept);
बाह्य bool Cocoa_Flash_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_FlashOperation operation);
बाह्य bool Cocoa_समुच्चयः_गवाक्षः_Focusable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool focusable);
बाह्य bool Cocoa_समुच्चयः_गवाक्षः_Modal(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool modal);
बाह्य bool Cocoa_समुच्चयः_गवाक्षः_Parent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः *parent);
बाह्य bool Cocoa_Sync_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);

बाह्य शून्य Cocoa_MenuVisibilityCallback(शून्य *userdata, ध्रुव वर्ण *name, ध्रुव वर्ण *old_मानम्, ध्रुव वर्ण *new_मानम्);

#यदि_अन्तः // SDL_cocoawindow_h_
