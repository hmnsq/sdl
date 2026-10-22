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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_cocoavideo_h_
#تعریف_کرو SDL_cocoavideo_h_

#شامل <SDL3/SDL_opengl.h>

#شامل <ApplicationServices/ApplicationServices.h>
#شامل <IOKit/pwr_mgt/IOPMLib.h>
#شامل <Cocoa/Cocoa.h>

#شامل "../SDL_sysvideo.h"

#شامل "SDL_cocoaclipboard.h"
#شامل "SDL_cocoaevents.h"
#شامل "SDL_cocoakeyboard.h"
#شامل "SDL_cocoamodes.h"
#شامل "SDL_cocoamouse.h"
#شامل "SDL_cocoaopengl.h"
#شامل "SDL_cocoawindow.h"
#شامل "SDL_cocoapen.h"

// Private display data

@class SDL3TranslatorResponder;

قسمتعریف شمار
{
    OptionAsAltNone,
    Option_As_Alt_Only_بایاں,
    Option_As_Alt_Only_دایاں,
    OptionAsAltBoth,
} OptionAsAlt;

@interface SDL_Cocoa_Video_ڈیٹا : NSObject
@property(nonatomic) صحیح allow_spaces;
@property(nonatomic) صحیح trackpad_is_touch_only;
@property(nonatomic) غیرعلامتی صحیح modifierFlags;
@property(nonatomic) خالی *کلید_layout;
@property(nonatomic) SDL3TranslatorResponder *میدان_Edit;
@property(nonatomic) NSInteger clipboard_گنتی;
@property(nonatomic) IOPMAssertionID screensaver_assertion;
@property(nonatomic) SDL_Mutex *swaplock;
@property(nonatomic) OptionAsAlt option_as_alt;
@property(nonatomic) CGFloat main_Display_اونچائی;
@انتہا

// Utility functions
خارجی SDL_SystemTheme Cocoa_GetSystemTheme(خالی);
خارجی NSImage *Cocoa_CreateImage(SDL_Surface *surface);

#اگر_ختم // SDL_cocoavideo_h_
