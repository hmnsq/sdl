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
/*
 * @author Mark Callow, www.edgewise-consulting.com.
 *
 * Thanks to @slime73 on GitHub for their gist showing how to add a CAMetalLayer
 * backed view.
 */
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_cocoametalview_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_cocoametalview_h_

#ಆದರೆ defined(SDL_VIDEO_DRIVER_COCOA) && (defined(SDL_VIDEO_VULKAN) || defined(SDL_VIDEO_METAL))

#import "../SDL_sysvideo.h"

#import "SDL_cocoawindow.h"

#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

@interface SDL3_cocoametalview : NSView

- (instancetype)init_With_ಚೌಕಟ್ಟು:(NSRect)ಚೌಕಟ್ಟು
                      ಮೇಲಿನ_DPI:(BOOL)ಮೇಲಿನ_DPI
                     ಕಿಟಕಿ_ID:(Uint32)ಕಿಟಕಿ_ID
                       opaque:(BOOL)opaque;

- (ಶೂನ್ಯ)update_Drawable_ಗಾತ್ರ;
- (NSView *)ದೊರಕಿತು_Test:(NSPoint)ಬಿಂದು;

// Override superclass tag so this class can set it.
@property(ನಿಯೋಜಿಸು, readonly) NSInteger ಟ್ಯಾಗ್;

@property(nonatomic) BOOL ಮೇಲಿನ_DPI;
@property(nonatomic) Uint32 sdl_ಕಿಟಕಿ_ID;

@ಕೊನೆ

SDL_MetalView Cocoa_Metal_CreateView(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಶೂನ್ಯ Cocoa_Metal_DestroyView(SDL_VideoDevice *_this, SDL_MetalView view);
ಶೂನ್ಯ *Cocoa_Metal_GetLayer(SDL_VideoDevice *_this, SDL_MetalView view);

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_COCOA && (SDL_VIDEO_VULKAN || SDL_VIDEO_METAL)

#ಆದರೆ_ಅಂತ್ಯ // SDL_cocoametalview_h_
