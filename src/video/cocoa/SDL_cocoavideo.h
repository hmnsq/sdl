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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_cocoavideo_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_cocoavideo_h_

#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_opengl.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <ApplicationServices/ApplicationServices.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <IOKit/pwr_mgt/IOPMLib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <Cocoa/Cocoa.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_cocoaclipboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_cocoaevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_cocoakeyboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_cocoamodes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_cocoamouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_cocoaopengl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_cocoawindow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_cocoapen.h"

// Private display data

@class SDL3TranslatorResponder;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    OptionAsAltNone,
    Option_As_Alt_Only_ਖੱਬਾ,
    Option_As_Alt_Only_ਸੱਜਾ,
    OptionAsAltBoth,
} OptionAsAlt;

@interface SDL_Cocoa_Video_ਅੰਕੜੇ : NSObject
@property(nonatomic) ਪੂਰਨ allow_spaces;
@property(nonatomic) ਪੂਰਨ trackpad_is_touch_only;
@property(nonatomic) ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ modifierFlags;
@property(nonatomic) ਖਾਲੀ *ਕੁੰਜੀ_layout;
@property(nonatomic) SDL3TranslatorResponder *ਖੇਤਰ_Edit;
@property(nonatomic) NSInteger clipboard_ਗਿਣਤੀ;
@property(nonatomic) IOPMAssertionID screensaver_assertion;
@property(nonatomic) SDL_Mutex *swaplock;
@property(nonatomic) OptionAsAlt option_as_alt;
@property(nonatomic) CGFloat main_Display_ਉਚਾਈ;
@ਸਿਰਾ

// Utility functions
ਬਾਹਰੀ SDL_SystemTheme Cocoa_GetSystemTheme(ਖਾਲੀ);
ਬਾਹਰੀ NSImage *Cocoa_CreateImage(SDL_Surface *surface);

#ਜੇ_ਅੰਤ // SDL_cocoavideo_h_
