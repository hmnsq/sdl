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

#ifndef SDL_cocoavideo_h_
#define SDL_cocoavideo_h_

#अन्तर्भाव <SDL3/SDL_opengl.h>

#अन्तर्भाव <ApplicationServices/ApplicationServices.h>
#अन्तर्भाव <IOKit/pwr_mgt/IOPMLib.h>
#अन्तर्भाव <Cocoa/Cocoa.h>

#अन्तर्भाव "../SDL_sysvideo.h"

#अन्तर्भाव "SDL_cocoaclipboard.h"
#अन्तर्भाव "SDL_cocoaevents.h"
#अन्तर्भाव "SDL_cocoakeyboard.h"
#अन्तर्भाव "SDL_cocoamodes.h"
#अन्तर्भाव "SDL_cocoamouse.h"
#अन्तर्भाव "SDL_cocoaopengl.h"
#अन्तर्भाव "SDL_cocoawindow.h"
#अन्तर्भाव "SDL_cocoapen.h"

// Private display data

@class SDL3TranslatorResponder;

प्रकारनिर्देश गणना
{
    OptionAsAltNone,
    Option_As_Alt_Only_बायाँ,
    Option_As_Alt_Only_दायाँ,
    OptionAsAltBoth,
} OptionAsAlt;

@interface SDL_CocoaVideoData : NSObject
@property(nonatomic) पूर्णाङ्क allow_spaces;
@property(nonatomic) पूर्णाङ्क trackpad_is_touch_only;
@property(nonatomic) unsigned पूर्णाङ्क modifierFlags;
@property(nonatomic) शून्य *कुंजी_layout;
@property(nonatomic) SDL3TranslatorResponder *fieldEdit;
@property(nonatomic) NSInteger clipboard_गिनती;
@property(nonatomic) IOPMAssertionID screensaver_assertion;
@property(nonatomic) SDL_Mutex *swaplock;
@property(nonatomic) OptionAsAlt option_as_alt;
@property(nonatomic) CGFloat mainDisplayHeight;
@end

// Utility functions
बाह्य SDL_SystemTheme Cocoa_GetSystemTheme(शून्य);
बाह्य NSImage *Cocoa_CreateImage(SDL_Surface *surface);

#endif // SDL_cocoavideo_h_
