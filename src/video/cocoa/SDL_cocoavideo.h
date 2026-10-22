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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_cocoavideo_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_cocoavideo_h_

#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengl.h>

#ಅನ್ತರ್ಭಾವ <ApplicationServices/ApplicationServices.h>
#ಅನ್ತರ್ಭಾವ <IOKit/pwr_mgt/IOPMLib.h>
#ಅನ್ತರ್ಭಾವ <Cocoa/Cocoa.h>

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ಅನ್ತರ್ಭಾವ "SDL_cocoaclipboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_cocoaevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_cocoakeyboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_cocoamodes.h"
#ಅನ್ತರ್ಭಾವ "SDL_cocoamouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_cocoaopengl.h"
#ಅನ್ತರ್ಭಾವ "SDL_cocoawindow.h"
#ಅನ್ತರ್ಭಾವ "SDL_cocoapen.h"

// Private display data

@class SDL3TranslatorResponder;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    OptionAsAltNone,
    Option_As_Alt_Only_ಎಡ,
    Option_As_Alt_Only_ಬಲ,
    OptionAsAltBoth,
} OptionAsAlt;

@interface SDL_Cocoa_Video_ದತ್ತಾಂಶ : NSObject
@property(nonatomic) ಪೂರ್ಣಾಂಕ allow_spaces;
@property(nonatomic) ಪೂರ್ಣಾಂಕ trackpad_is_touch_only;
@property(nonatomic) ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ modifierFlags;
@property(nonatomic) ಶೂನ್ಯ *ಕೀಲಿ_layout;
@property(nonatomic) SDL3TranslatorResponder *ಕ್ಷೇತ್ರ_Edit;
@property(nonatomic) NSInteger clipboard_ಎಣಿಕೆ;
@property(nonatomic) IOPMAssertionID screensaver_assertion;
@property(nonatomic) SDL_Mutex *swaplock;
@property(nonatomic) OptionAsAlt option_as_alt;
@property(nonatomic) CGFloat main_Display_ಎತ್ತರ;
@ಕೊನೆ

// Utility functions
ಬಾಹ್ಯ SDL_SystemTheme Cocoa_GetSystemTheme(ಶೂನ್ಯ);
ಬಾಹ್ಯ NSImage *Cocoa_CreateImage(SDL_Surface *surface);

#ಆದರೆ_ಅಂತ್ಯ // SDL_cocoavideo_h_
