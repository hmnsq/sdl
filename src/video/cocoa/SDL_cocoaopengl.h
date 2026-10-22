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

#که_نه_تعریف_شوی SDL_cocoaopengl_h_
#تعریف_کړه SDL_cocoaopengl_h_

#که_تعریف_شوی SDL_VIDEO_OPENGL_CGL

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

// We still support OpenGL as long as Apple offers it, deprecated or not, so disable deprecation warnings about it.
#که_تعریف_شوی __clang__
#لارښوونه clang diagnostic ټېل
#لارښوونه clang diagnostic ignored "-Wdeprecated-declarations"
#د_که_پای

بنية SDL_GLDriver_معلومات
{
    صحيح initialized;
};

@interface SDL3OpenGLContext : NSOpenGLContext
{
    SDL_AtomicInt dirty;
    SDL_کړکۍ *کړکۍ;
    CVDisplayLinkRef displayLink;
  @عام
    SDL_Mutex *بدلون_Interval_Mutex;
  @عام
    SDL_Condition *بدلون_Interval_Cond;
  @عام
    SDL_AtomicInt بدلون_Interval_Setting;
  @عام
    SDL_AtomicInt بدلون_Intervals_Passed;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (فراغ)مهالوېش_Update;
- (فراغ)updateIfNeeded;
- (فراغ)moved_منزل_New_Screen;
- (فراغ)سېټ_کړکۍ:(SDL_کړکۍ *)کړکۍ;
- (SDL_کړکۍ *)کړکۍ;
- (فراغ)explicitUpdate;
- (فراغ)cleanup;

@property(retain, nonatomic) NSOpenGLPixelFormat *openglPixelFormat; // macOS 10.10 has -[NSOpenGLContext pixelFormat] but this handles older OS releases.

@پای_ټکی

// OpenGL functions
خارجي bool Cocoa_GL_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار);
خارجي SDL_Function_اشاره_ګر Cocoa_GL_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ Cocoa_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext Cocoa_GL_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool Cocoa_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_GLContext context);
خارجي bool Cocoa_GL_سېټ_بدلون_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool Cocoa_GL_Get_بدلون_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool Cocoa_GL_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool Cocoa_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#که_تعریف_شوی __clang__
#لارښوونه clang diagnostic راوباسه
#د_که_پای

#د_که_پای // SDL_VIDEO_OPENGL_CGL

#د_که_پای // SDL_cocoaopengl_h_
