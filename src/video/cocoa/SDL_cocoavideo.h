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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_cocoavideo_h_
#define SDL_cocoavideo_h_

#ଅନ୍ତର୍ଭାଵ <SDL3/SDL_opengl.h>

#ଅନ୍ତର୍ଭାଵ <ApplicationServices/ApplicationServices.h>
#ଅନ୍ତର୍ଭାଵ <IOKit/pwr_mgt/IOPMLib.h>
#ଅନ୍ତର୍ଭାଵ <Cocoa/Cocoa.h>

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"

#ଅନ୍ତର୍ଭାଵ "SDL_cocoaclipboard.h"
#ଅନ୍ତର୍ଭାଵ "SDL_cocoaevents.h"
#ଅନ୍ତର୍ଭାଵ "SDL_cocoakeyboard.h"
#ଅନ୍ତର୍ଭାଵ "SDL_cocoamodes.h"
#ଅନ୍ତର୍ଭାଵ "SDL_cocoamouse.h"
#ଅନ୍ତର୍ଭାଵ "SDL_cocoaopengl.h"
#ଅନ୍ତର୍ଭାଵ "SDL_cocoawindow.h"
#ଅନ୍ତର୍ଭାଵ "SDL_cocoapen.h"

// Private display data

@class SDL3TranslatorResponder;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
{
    OptionAsAltNone,
    Option_As_Alt_Only_ବାମ,
    Option_As_Alt_Only_ଡାହାଣ,
    OptionAsAltBoth,
} OptionAsAlt;

@interface SDL_CocoaVideoData : NSObject
@property(nonatomic) ପୂର୍ଣ୍ଣସଂଖ୍ୟା allow_spaces;
@property(nonatomic) ପୂର୍ଣ୍ଣସଂଖ୍ୟା trackpad_is_touch_only;
@property(nonatomic) unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା modifierFlags;
@property(nonatomic) ଶୂନ୍ୟ *ଚାବି_layout;
@property(nonatomic) SDL3TranslatorResponder *fieldEdit;
@property(nonatomic) NSInteger clipboard_ଗଣନା;
@property(nonatomic) IOPMAssertionID screensaver_assertion;
@property(nonatomic) SDL_Mutex *swaplock;
@property(nonatomic) OptionAsAlt option_as_alt;
@property(nonatomic) CGFloat mainDisplayHeight;
@end

// Utility functions
ବାହ୍ୟ SDL_SystemTheme Cocoa_GetSystemTheme(ଶୂନ୍ୟ);
ବାହ୍ୟ NSImage *Cocoa_CreateImage(SDL_Surface *surface);

#endif // SDL_cocoavideo_h_
