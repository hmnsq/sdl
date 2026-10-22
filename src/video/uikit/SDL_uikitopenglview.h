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

#ಆದರೆ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES3/gl.h>

#import "SDL_uikitview.h"
#ಅನ್ತರ್ಭಾವ "SDL_uikitvideo.h"

@interface SDL_uikitopenglview : SDL_uikitview

- (instancetype)init_With_ಚೌಕಟ್ಟು:(CGRect)ಚೌಕಟ್ಟು
                        scale:(CGFloat)scale
                retainBacking:(BOOL)retained
                        r_ಬಿಟ್ಟುಗಳು:(ಪೂರ್ಣಾಂಕ)r_ಬಿಟ್ಟುಗಳು
                        g_ಬಿಟ್ಟುಗಳು:(ಪೂರ್ಣಾಂಕ)g_ಬಿಟ್ಟುಗಳು
                        b_ಬಿಟ್ಟುಗಳು:(ಪೂರ್ಣಾಂಕ)b_ಬಿಟ್ಟುಗಳು
                        a_ಬಿಟ್ಟುಗಳು:(ಪೂರ್ಣಾಂಕ)a_ಬಿಟ್ಟುಗಳು
                    ಆಳ_ಬಿಟ್ಟುಗಳು:(ಪೂರ್ಣಾಂಕ)ಆಳ_ಬಿಟ್ಟುಗಳು
                  stencil_ಬಿಟ್ಟುಗಳು:(ಪೂರ್ಣಾಂಕ)stencil_ಬಿಟ್ಟುಗಳು
                         sRGB:(ಪೂರ್ಣಾಂಕ)sRGB
                 multisamples:(ಪೂರ್ಣಾಂಕ)multisamples
                      context:(EAGLContext *)glcontext;

@property(nonatomic, readonly, weak) EAGLContext *context;

// The width and height of the drawable in pixels (as opposed to points.)
@property(nonatomic, readonly) ಪೂರ್ಣಾಂಕ backing_ಅಗಲ;
@property(nonatomic, readonly) ಪೂರ್ಣಾಂಕ backing_ಎತ್ತರ;

@property(nonatomic, readonly) GLuint drawableRenderbuffer;
@property(nonatomic, readonly) GLuint drawableFramebuffer;
@property(nonatomic, readonly) GLuint msaaResolveFramebuffer;

- (ಶೂನ್ಯ)ಅದಲುಬದಲು_Buffers_2;

- (ಶೂನ್ಯ)update_ಚೌಕಟ್ಟು;

@ಕೊನೆ

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2
