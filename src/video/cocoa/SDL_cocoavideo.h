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
#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_cocoavideo_h_
#define SDL_cocoavideo_h_

#അന്തര്ഭാവ <SDL3/SDL_opengl.h>

#അന്തര്ഭാവ <ApplicationServices/ApplicationServices.h>
#അന്തര്ഭാവ <IOKit/pwr_mgt/IOPMLib.h>
#അന്തര്ഭാവ <Cocoa/Cocoa.h>

#അന്തര്ഭാവ "../SDL_sysvideo.h"

#അന്തര്ഭാവ "SDL_cocoaclipboard.h"
#അന്തര്ഭാവ "SDL_cocoaevents.h"
#അന്തര്ഭാവ "SDL_cocoakeyboard.h"
#അന്തര്ഭാവ "SDL_cocoamodes.h"
#അന്തര്ഭാവ "SDL_cocoamouse.h"
#അന്തര്ഭാവ "SDL_cocoaopengl.h"
#അന്തര്ഭാവ "SDL_cocoawindow.h"
#അന്തര്ഭാവ "SDL_cocoapen.h"

// Private display data

@class SDL3TranslatorResponder;

തരനിർവചനം എണ്ണൽ
{
    OptionAsAltNone,
    Option_As_Alt_Only_ഇടത്,
    Option_As_Alt_Only_വലത്,
    OptionAsAltBoth,
} OptionAsAlt;

@interface SDL_CocoaVideoData : NSObject
@property(nonatomic) പൂർണ്ണസംഖ്യ allow_spaces;
@property(nonatomic) പൂർണ്ണസംഖ്യ trackpad_is_touch_only;
@property(nonatomic) unsigned പൂർണ്ണസംഖ്യ modifierFlags;
@property(nonatomic) ശൂന്യം *താക്കോൽ_layout;
@property(nonatomic) SDL3TranslatorResponder *fieldEdit;
@property(nonatomic) NSInteger clipboard_എണ്ണം;
@property(nonatomic) IOPMAssertionID screensaver_assertion;
@property(nonatomic) SDL_Mutex *swaplock;
@property(nonatomic) OptionAsAlt option_as_alt;
@property(nonatomic) CGFloat mainDisplayHeight;
@end

// Utility functions
ബാഹ്യ SDL_SystemTheme Cocoa_GetSystemTheme(ശൂന്യം);
ബാഹ്യ NSImage *Cocoa_CreateImage(SDL_Surface *surface);

#endif // SDL_cocoavideo_h_
