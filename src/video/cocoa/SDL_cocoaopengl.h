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

#اگر_تعریف_نشده SDL_cocoaopengl_h_
#تعریف_کن SDL_cocoaopengl_h_

#اگر_تعریف_شده SDL_VIDEO_OPENGL_CGL

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

// We still support OpenGL as long as Apple offers it, deprecated or not, so disable deprecation warnings about it.
#اگر_تعریف_شده __clang__
#رهنمود clang diagnostic افزودن
#رهنمود clang diagnostic ignored "-Wdeprecated-declarations"
#پایان_اگر

بنية SDL_GLDriver_داده
{
    صحيح initialized;
};

@interface SDL3OpenGLContext : NSOpenGLContext
{
    SDL_AtomicInt dirty;
    SDL_پنجره *پنجره;
    CVDisplayLinkRef displayLink;
  @عام
    SDL_Mutex *جابجا_Interval_Mutex;
  @عام
    SDL_Condition *جابجا_Interval_Cond;
  @عام
    SDL_AtomicInt جابجا_Interval_Setting;
  @عام
    SDL_AtomicInt جابجا_Intervals_Passed;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (فراغ)زمانبندی_Update;
- (فراغ)updateIfNeeded;
- (فراغ)moved_مقصد_New_Screen;
- (فراغ)مجموعه_پنجره:(SDL_پنجره *)پنجره;
- (SDL_پنجره *)پنجره;
- (فراغ)explicitUpdate;
- (فراغ)cleanup;

@property(retain, nonatomic) NSOpenGLPixelFormat *openglPixelFormat; // macOS 10.10 has -[NSOpenGLContext pixelFormat] but this handles older OS releases.

@انتها

// OpenGL functions
خارجي bool Cocoa_GL_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر);
خارجي SDL_Function_اشاره_گر Cocoa_GL_Get_Proc_آدرس(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ Cocoa_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext Cocoa_GL_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Cocoa_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_GLContext context);
خارجي bool Cocoa_GL_مجموعه_جابجا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool Cocoa_GL_Get_جابجا_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool Cocoa_GL_جابجا_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Cocoa_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#اگر_تعریف_شده __clang__
#رهنمود clang diagnostic برداشت
#پایان_اگر

#پایان_اگر // SDL_VIDEO_OPENGL_CGL

#پایان_اگر // SDL_cocoaopengl_h_
