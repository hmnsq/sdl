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

#ifndef SDL_cocoavideo_h_
#define SDL_cocoavideo_h_

#ضمن <SDL3/SDL_opengl.h>

#ضمن <ApplicationServices/ApplicationServices.h>
#ضمن <IOKit/pwr_mgt/IOPMLib.h>
#ضمن <Cocoa/Cocoa.h>

#ضمن "../SDL_sysvideo.h"

#ضمن "SDL_cocoaclipboard.h"
#ضمن "SDL_cocoaevents.h"
#ضمن "SDL_cocoakeyboard.h"
#ضمن "SDL_cocoamodes.h"
#ضمن "SDL_cocoamouse.h"
#ضمن "SDL_cocoaopengl.h"
#ضمن "SDL_cocoawindow.h"
#ضمن "SDL_cocoapen.h"

// Private display data

@class SDL3TranslatorResponder;

تعريفنوع تعداد
{
    OptionAsAltNone,
    OptionAsAltOnlyLeft,
    OptionAsAltOnlyRight,
    OptionAsAltBoth,
} OptionAsAlt;

@interface SDL_CocoaVideoData : NSObject
@property(nonatomic) صحيح allow_spaces;
@property(nonatomic) صحيح trackpad_is_touch_only;
@property(nonatomic) unsigned صحيح modifierFlags;
@property(nonatomic) فراغ *key_layout;
@property(nonatomic) SDL3TranslatorResponder *fieldEdit;
@property(nonatomic) NSInteger clipboard_count;
@property(nonatomic) IOPMAssertionID screensaver_assertion;
@property(nonatomic) SDL_Mutex *swaplock;
@property(nonatomic) OptionAsAlt option_as_alt;
@property(nonatomic) CGFloat mainDisplayHeight;
@end

// Utility functions
خارجي SDL_SystemTheme Cocoa_GetSystemTheme(فراغ);
خارجي NSImage *Cocoa_CreateImage(SDL_Surface *surface);

#endif // SDL_cocoavideo_h_
