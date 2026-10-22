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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_cocoavideo_h_
#define SDL_cocoavideo_h_

#અન્તર્ભાવ <SDL3/SDL_opengl.h>

#અન્તર્ભાવ <ApplicationServices/ApplicationServices.h>
#અન્તર્ભાવ <IOKit/pwr_mgt/IOPMLib.h>
#અન્તર્ભાવ <Cocoa/Cocoa.h>

#અન્તર્ભાવ "../SDL_sysvideo.h"

#અન્તર્ભાવ "SDL_cocoaclipboard.h"
#અન્તર્ભાવ "SDL_cocoaevents.h"
#અન્તર્ભાવ "SDL_cocoakeyboard.h"
#અન્તર્ભાવ "SDL_cocoamodes.h"
#અન્તર્ભાવ "SDL_cocoamouse.h"
#અન્તર્ભાવ "SDL_cocoaopengl.h"
#અન્તર્ભાવ "SDL_cocoawindow.h"
#અન્તર્ભાવ "SDL_cocoapen.h"

// Private display data

@class SDL3TranslatorResponder;

પ્રકારવ્યાખ્યા ગણના
{
    OptionAsAltNone,
    Option_As_Alt_Only_ડાબું,
    Option_As_Alt_Only_જમણું,
    OptionAsAltBoth,
} OptionAsAlt;

@interface SDL_CocoaVideoData : NSObject
@property(nonatomic) પૂર્ણાંક allow_spaces;
@property(nonatomic) પૂર્ણાંક trackpad_is_touch_only;
@property(nonatomic) unsigned પૂર્ણાંક modifierFlags;
@property(nonatomic) શૂન્ય *ચાવી_layout;
@property(nonatomic) SDL3TranslatorResponder *fieldEdit;
@property(nonatomic) NSInteger clipboard_ગણતરી;
@property(nonatomic) IOPMAssertionID screensaver_assertion;
@property(nonatomic) SDL_Mutex *swaplock;
@property(nonatomic) OptionAsAlt option_as_alt;
@property(nonatomic) CGFloat mainDisplayHeight;
@end

// Utility functions
બાહ્ય SDL_SystemTheme Cocoa_GetSystemTheme(શૂન્ય);
બાહ્ય NSImage *Cocoa_CreateImage(SDL_Surface *surface);

#endif // SDL_cocoavideo_h_
