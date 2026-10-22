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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_cocoavideo_h_
#घोषणा SDL_cocoavideo_h_

#समावेश <SDL3/SDL_opengl.h>

#समावेश <ApplicationServices/ApplicationServices.h>
#समावेश <IOKit/pwr_mgt/IOPMLib.h>
#समावेश <Cocoa/Cocoa.h>

#समावेश "../SDL_sysvideo.h"

#समावेश "SDL_cocoaclipboard.h"
#समावेश "SDL_cocoaevents.h"
#समावेश "SDL_cocoakeyboard.h"
#समावेश "SDL_cocoamodes.h"
#समावेश "SDL_cocoamouse.h"
#समावेश "SDL_cocoaopengl.h"
#समावेश "SDL_cocoawindow.h"
#समावेश "SDL_cocoapen.h"

// Private display data

@class SDL3TranslatorResponder;

प्रकार क्रमागत
{
    OptionAsAltNone,
    Option_As_Alt_Only_बायाँ,
    Option_As_Alt_Only_दायाँ,
    OptionAsAltBoth,
} OptionAsAlt;

@interface SDL_Cocoa_Video_तथ्य : NSObject
@property(nonatomic) पूर्णांक allow_spaces;
@property(nonatomic) पूर्णांक trackpad_is_touch_only;
@property(nonatomic) अचिन्हित पूर्णांक modifierFlags;
@property(nonatomic) व्योम *कुंजी_layout;
@property(nonatomic) SDL3TranslatorResponder *fieldEdit;
@property(nonatomic) NSInteger clipboard_गिनती;
@property(nonatomic) IOPMAssertionID screensaver_assertion;
@property(nonatomic) SDL_Mutex *swaplock;
@property(nonatomic) OptionAsAlt option_as_alt;
@property(nonatomic) CGFloat mainDisplayHeight;
@end

// Utility functions
बाह्य SDL_SystemTheme Cocoa_GetSystemTheme(व्योम);
बाह्य NSImage *Cocoa_CreateImage(SDL_Surface *surface);

#पूर्ण_अगर // SDL_cocoavideo_h_
