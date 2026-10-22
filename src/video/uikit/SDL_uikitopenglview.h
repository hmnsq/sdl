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

#જો defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES3/gl.h>

#import "SDL_uikitview.h"
#અન્તર્ભાવ "SDL_uikitvideo.h"

@interface SDL_uikitopenglview : SDL_uikitview

- (instancetype)initWithFrame:(CGRect)frame
                        scale:(CGFloat)scale
                retainBacking:(BOOL)retained
                        rBits:(પૂર્ણાંક)rBits
                        gBits:(પૂર્ણાંક)gBits
                        bBits:(પૂર્ણાંક)bBits
                        aBits:(પૂર્ણાંક)aBits
                    depthBits:(પૂર્ણાંક)depthBits
                  stencilBits:(પૂર્ણાંક)stencilBits
                         sRGB:(પૂર્ણાંક)sRGB
                 multisamples:(પૂર્ણાંક)multisamples
                      context:(EAGLContext *)glcontext;

@property(nonatomic, readonly, weak) EAGLContext *context;

// The width and height of the drawable in pixels (as opposed to points.)
@property(nonatomic, readonly) પૂર્ણાંક backingWidth;
@property(nonatomic, readonly) પૂર્ણાંક backingHeight;

@property(nonatomic, readonly) GLuint drawableRenderbuffer;
@property(nonatomic, readonly) GLuint drawableFramebuffer;
@property(nonatomic, readonly) GLuint msaaResolveFramebuffer;

- (શૂન્ય)swapBuffers;

- (શૂન્ય)updateFrame;

@end

#endif // SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2
