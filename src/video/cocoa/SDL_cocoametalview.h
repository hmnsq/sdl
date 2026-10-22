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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_cocoametalview_h_
#परिभाषय SDL_cocoametalview_h_

#यदि defined(SDL_VIDEO_DRIVER_COCOA) && (defined(SDL_VIDEO_VULKAN) || defined(SDL_VIDEO_METAL))

#import "../SDL_sysvideo.h"

#import "SDL_cocoawindow.h"

#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

@interface SDL3_cocoametalview : NSView

- (instancetype)initWithFrame:(NSRect)frame
                      उच्चः_DPI:(BOOL)उच्चः_DPI
                     गवाक्षः_ID:(Uint32)गवाक्षः_ID
                       opaque:(BOOL)opaque;

- (शून्य)update_Drawable_आकार;
- (NSView *)लब्धम्_Test:(NSPoint)point;

// Override superclass tag so this class can set it.
@property(नियोजय, readonly) NSInteger चिह्नकम्;

@property(nonatomic) BOOL उच्चः_DPI;
@property(nonatomic) Uint32 sdl_गवाक्षः_ID;

@अन्तः

SDL_MetalView Cocoa_Metal_CreateView(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
शून्य Cocoa_Metal_DestroyView(SDL_VideoDevice *_this, SDL_MetalView view);
शून्य *Cocoa_Metal_GetLayer(SDL_VideoDevice *_this, SDL_MetalView view);

#यदि_अन्तः // SDL_VIDEO_DRIVER_COCOA && (SDL_VIDEO_VULKAN || SDL_VIDEO_METAL)

#यदि_अन्तः // SDL_cocoametalview_h_
