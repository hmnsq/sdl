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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_cocoavideo_h_
#నిర్వచించు SDL_cocoavideo_h_

#అన్తర్భావ <SDL3/SDL_opengl.h>

#అన్తర్భావ <ApplicationServices/ApplicationServices.h>
#అన్తర్భావ <IOKit/pwr_mgt/IOPMLib.h>
#అన్తర్భావ <Cocoa/Cocoa.h>

#అన్తర్భావ "../SDL_sysvideo.h"

#అన్తర్భావ "SDL_cocoaclipboard.h"
#అన్తర్భావ "SDL_cocoaevents.h"
#అన్తర్భావ "SDL_cocoakeyboard.h"
#అన్తర్భావ "SDL_cocoamodes.h"
#అన్తర్భావ "SDL_cocoamouse.h"
#అన్తర్భావ "SDL_cocoaopengl.h"
#అన్తర్భావ "SDL_cocoawindow.h"
#అన్తర్భావ "SDL_cocoapen.h"

// Private display data

@class SDL3TranslatorResponder;

రకనిర్వచనం గణన
{
    OptionAsAltNone,
    Option_As_Alt_Only_ఎడమ,
    Option_As_Alt_Only_కుడి,
    OptionAsAltBoth,
} OptionAsAlt;

@interface SDL_Cocoa_Video_దత్తాంశం : NSObject
@property(nonatomic) పూర్ణాంకం allow_spaces;
@property(nonatomic) పూర్ణాంకం trackpad_is_touch_only;
@property(nonatomic) గుర్తులేని పూర్ణాంకం modifierFlags;
@property(nonatomic) శూన్య *కీలకం_layout;
@property(nonatomic) SDL3TranslatorResponder *క్షేత్రం_Edit;
@property(nonatomic) NSInteger clipboard_లెక్క;
@property(nonatomic) IOPMAssertionID screensaver_assertion;
@property(nonatomic) SDL_Mutex *swaplock;
@property(nonatomic) OptionAsAlt option_as_alt;
@property(nonatomic) CGFloat main_Display_ఎత్తు;
@చివర

// Utility functions
బాహ్య SDL_SystemTheme Cocoa_GetSystemTheme(శూన్య);
బాహ్య NSImage *Cocoa_CreateImage(SDL_Surface *surface);

#అయితే_ముగింపు // SDL_cocoavideo_h_
