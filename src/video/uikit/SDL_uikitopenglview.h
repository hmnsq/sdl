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

#ఒకవేళ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES3/gl.h>

#import "SDL_uikitview.h"
#అన్తర్భావ "SDL_uikitvideo.h"

@interface SDL_uikitopenglview : SDL_uikitview

- (instancetype)init_With_చట్రం:(CGRect)చట్రం
                        scale:(CGFloat)scale
                retainBacking:(BOOL)retained
                        r_బిట్లు:(పూర్ణాంకం)r_బిట్లు
                        g_బిట్లు:(పూర్ణాంకం)g_బిట్లు
                        b_బిట్లు:(పూర్ణాంకం)b_బిట్లు
                        a_బిట్లు:(పూర్ణాంకం)a_బిట్లు
                    లోతు_బిట్లు:(పూర్ణాంకం)లోతు_బిట్లు
                  stencil_బిట్లు:(పూర్ణాంకం)stencil_బిట్లు
                         sRGB:(పూర్ణాంకం)sRGB
                 multisamples:(పూర్ణాంకం)multisamples
                      context:(EAGLContext *)glcontext;

@property(nonatomic, readonly, weak) EAGLContext *context;

// The width and height of the drawable in pixels (as opposed to points.)
@property(nonatomic, readonly) పూర్ణాంకం backing_వెడల్పు;
@property(nonatomic, readonly) పూర్ణాంకం backing_ఎత్తు;

@property(nonatomic, readonly) GLuint drawableRenderbuffer;
@property(nonatomic, readonly) GLuint drawableFramebuffer;
@property(nonatomic, readonly) GLuint msaaResolveFramebuffer;

- (శూన్య)మార్పిడి_Buffers_2;

- (శూన్య)update_చట్రం;

@చివర

#అయితే_ముగింపు // SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2
