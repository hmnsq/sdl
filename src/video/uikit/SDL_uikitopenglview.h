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

#ਜੇ defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES3/gl.h>

#import "SDL_uikitview.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_uikitvideo.h"

@interface SDL_uikitopenglview : SDL_uikitview

- (instancetype)init_With_ਚੌਖਟਾ:(CGRect)ਚੌਖਟਾ
                        scale:(CGFloat)scale
                retainBacking:(BOOL)retained
                        r_ਬਿੱਟ:(ਪੂਰਨ)r_ਬਿੱਟ
                        g_ਬਿੱਟ:(ਪੂਰਨ)g_ਬਿੱਟ
                        b_ਬਿੱਟ:(ਪੂਰਨ)b_ਬਿੱਟ
                        a_ਬਿੱਟ:(ਪੂਰਨ)a_ਬਿੱਟ
                    ਡੂੰਘਾਈ_ਬਿੱਟ:(ਪੂਰਨ)ਡੂੰਘਾਈ_ਬਿੱਟ
                  stencil_ਬਿੱਟ:(ਪੂਰਨ)stencil_ਬਿੱਟ
                         sRGB:(ਪੂਰਨ)sRGB
                 multisamples:(ਪੂਰਨ)multisamples
                      context:(EAGLContext *)glcontext;

@property(nonatomic, readonly, weak) EAGLContext *context;

// The width and height of the drawable in pixels (as opposed to points.)
@property(nonatomic, readonly) ਪੂਰਨ backing_ਚੌੜਾਈ;
@property(nonatomic, readonly) ਪੂਰਨ backing_ਉਚਾਈ;

@property(nonatomic, readonly) GLuint drawableRenderbuffer;
@property(nonatomic, readonly) GLuint drawableFramebuffer;
@property(nonatomic, readonly) GLuint msaaResolveFramebuffer;

- (ਖਾਲੀ)ਅਦਲਾ_ਬਦਲੀ_Buffers_2;

- (ਖਾਲੀ)update_ਚੌਖਟਾ;

@ਸਿਰਾ

#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2
