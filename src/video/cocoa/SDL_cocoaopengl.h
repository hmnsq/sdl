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
#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_نه_ٿيل SDL_cocoaopengl_h_
#وصف_ڪريو SDL_cocoaopengl_h_

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_CGL

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

// We still support OpenGL as long as Apple offers it, deprecated or not, so disable deprecation warnings about it.
#جيڪڏهن_وصف_ٿيل __clang__
#هدايت clang diagnostic ڌڪو
#هدايت clang diagnostic ignored "-Wdeprecated-declarations"
#جيڪڏهن_پورو

بنية SDL_GLDriver_معلومات
{
    صحيح initialized;
};

@interface SDL3OpenGLContext : NSOpenGLContext
{
    SDL_AtomicInt dirty;
    SDL_دري *دري;
    CVDisplayLinkRef displayLink;
  @عام
    SDL_Mutex *مٽا_سٽا_Interval_Mutex;
  @عام
    SDL_Condition *مٽا_سٽا_Interval_Cond;
  @عام
    SDL_AtomicInt مٽا_سٽا_Interval_Setting;
  @عام
    SDL_AtomicInt مٽا_سٽا_Intervals_Passed;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (فراغ)وقت_جدول_Update;
- (فراغ)updateIfNeeded;
- (فراغ)moved_منزل_New_Screen;
- (فراغ)سيٽ_دري:(SDL_دري *)دري;
- (SDL_دري *)دري;
- (فراغ)explicitUpdate;
- (فراغ)cleanup;

@property(retain, nonatomic) NSOpenGLPixelFormat *openglPixelFormat; // macOS 10.10 has -[NSOpenGLContext pixelFormat] but this handles older OS releases.

@پڇاڙي

// OpenGL functions
خارجي bool Cocoa_GL_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو);
خارجي SDL_Function_اشارو Cocoa_GL_Get_Proc_پتو(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ Cocoa_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext Cocoa_GL_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Cocoa_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_دري *دري, SDL_GLContext context);
خارجي bool Cocoa_GL_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool Cocoa_GL_Get_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool Cocoa_GL_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Cocoa_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#جيڪڏهن_وصف_ٿيل __clang__
#هدايت clang diagnostic ڪڍو
#جيڪڏهن_پورو

#جيڪڏهن_پورو // SDL_VIDEO_OPENGL_CGL

#جيڪڏهن_پورو // SDL_cocoaopengl_h_
