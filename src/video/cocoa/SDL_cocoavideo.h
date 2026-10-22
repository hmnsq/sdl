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
#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_cocoavideo_h_
#define SDL_cocoavideo_h_

#অন্তর্ভাব <SDL3/SDL_opengl.h>

#অন্তর্ভাব <ApplicationServices/ApplicationServices.h>
#অন্তর্ভাব <IOKit/pwr_mgt/IOPMLib.h>
#অন্তর্ভাব <Cocoa/Cocoa.h>

#অন্তর্ভাব "../SDL_sysvideo.h"

#অন্তর্ভাব "SDL_cocoaclipboard.h"
#অন্তর্ভাব "SDL_cocoaevents.h"
#অন্তর্ভাব "SDL_cocoakeyboard.h"
#অন্তর্ভাব "SDL_cocoamodes.h"
#অন্তর্ভাব "SDL_cocoamouse.h"
#অন্তর্ভাব "SDL_cocoaopengl.h"
#অন্তর্ভাব "SDL_cocoawindow.h"
#অন্তর্ভাব "SDL_cocoapen.h"

// Private display data

@class SDL3TranslatorResponder;

প্রকারলেখ গণনা
{
    OptionAsAltNone,
    Option_As_Alt_Only_বাম,
    Option_As_Alt_Only_ডান,
    OptionAsAltBoth,
} OptionAsAlt;

@interface SDL_Cocoa_Video_তথ্য : NSObject
@property(nonatomic) পূর্ণসংখ্যা allow_spaces;
@property(nonatomic) পূর্ণসংখ্যা trackpad_is_touch_only;
@property(nonatomic) unsigned পূর্ণসংখ্যা modifierFlags;
@property(nonatomic) শূন্য *চাবি_layout;
@property(nonatomic) SDL3TranslatorResponder *fieldEdit;
@property(nonatomic) NSInteger clipboard_গুনতি;
@property(nonatomic) IOPMAssertionID screensaver_assertion;
@property(nonatomic) SDL_Mutex *swaplock;
@property(nonatomic) OptionAsAlt option_as_alt;
@property(nonatomic) CGFloat mainDisplayHeight;
@end

// Utility functions
বাহ্যিক SDL_SystemTheme Cocoa_GetSystemTheme(শূন্য);
বাহ্যিক NSImage *Cocoa_CreateImage(SDL_Surface *surface);

#endif // SDL_cocoavideo_h_
