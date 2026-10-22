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
#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_cocoavideo_h_
#define SDL_cocoavideo_h_

#அந்தர்பாவ <SDL3/SDL_opengl.h>

#அந்தர்பாவ <ApplicationServices/ApplicationServices.h>
#அந்தர்பாவ <IOKit/pwr_mgt/IOPMLib.h>
#அந்தர்பாவ <Cocoa/Cocoa.h>

#அந்தர்பாவ "../SDL_sysvideo.h"

#அந்தர்பாவ "SDL_cocoaclipboard.h"
#அந்தர்பாவ "SDL_cocoaevents.h"
#அந்தர்பாவ "SDL_cocoakeyboard.h"
#அந்தர்பாவ "SDL_cocoamodes.h"
#அந்தர்பாவ "SDL_cocoamouse.h"
#அந்தர்பாவ "SDL_cocoaopengl.h"
#அந்தர்பாவ "SDL_cocoawindow.h"
#அந்தர்பாவ "SDL_cocoapen.h"

// Private display data

@class SDL3TranslatorResponder;

வகைவரை எண்ணிக்கை
{
    OptionAsAltNone,
    Option_As_Alt_Only_இடது,
    Option_As_Alt_Only_வலது,
    OptionAsAltBoth,
} OptionAsAlt;

@interface SDL_CocoaVideoData : NSObject
@property(nonatomic) முழு allow_spaces;
@property(nonatomic) முழு trackpad_is_touch_only;
@property(nonatomic) unsigned முழு modifierFlags;
@property(nonatomic) வெறுமை *சாவி_layout;
@property(nonatomic) SDL3TranslatorResponder *fieldEdit;
@property(nonatomic) NSInteger clipboard_மொத்தம்;
@property(nonatomic) IOPMAssertionID screensaver_assertion;
@property(nonatomic) SDL_Mutex *swaplock;
@property(nonatomic) OptionAsAlt option_as_alt;
@property(nonatomic) CGFloat mainDisplayHeight;
@end

// Utility functions
வெளி SDL_SystemTheme Cocoa_GetSystemTheme(வெறுமை);
வெளி NSImage *Cocoa_CreateImage(SDL_Surface *surface);

#endif // SDL_cocoavideo_h_
