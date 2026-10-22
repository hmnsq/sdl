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

#جے_بنا_تعریف SDL_cocoaopengl_h_
#تعریف_کرو SDL_cocoaopengl_h_

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_CGL

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

// We still support OpenGL as long as Apple offers it, deprecated or not, so disable deprecation warnings about it.
#جے_تعریف_شدہ __clang__
#ہدایت clang diagnostic ڈالو
#ہدایت clang diagnostic ignored "-Wdeprecated-declarations"
#جے_انت

بنية SDL_GLDriver_انکڑے
{
    صحيح initialized;
};

@interface SDL3OpenGLContext : NSOpenGLContext
{
    SDL_AtomicInt dirty;
    SDL_کھڑکی *کھڑکی;
    CVDisplayLinkRef displayLink;
  @عام
    SDL_Mutex *وٹاندرا_Interval_Mutex;
  @عام
    SDL_Condition *وٹاندرا_Interval_Cond;
  @عام
    SDL_AtomicInt وٹاندرا_Interval_Setting;
  @عام
    SDL_AtomicInt وٹاندرا_Intervals_Passed;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (فراغ)ویلا_سارنی_Update;
- (فراغ)updateIfNeeded;
- (فراغ)moved_منزل_New_Screen;
- (فراغ)سیٹ_کھڑکی:(SDL_کھڑکی *)کھڑکی;
- (SDL_کھڑکی *)کھڑکی;
- (فراغ)explicitUpdate;
- (فراغ)cleanup;

@property(retain, nonatomic) NSOpenGLPixelFormat *openglPixelFormat; // macOS 10.10 has -[NSOpenGLContext pixelFormat] but this handles older OS releases.

@سرا

// OpenGL functions
خارجي bool Cocoa_GL_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ);
خارجي SDL_Function_اشارہ_گر Cocoa_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ Cocoa_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext Cocoa_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Cocoa_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context);
خارجي bool Cocoa_GL_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool Cocoa_GL_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool Cocoa_GL_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Cocoa_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#جے_تعریف_شدہ __clang__
#ہدایت clang diagnostic نکالو
#جے_انت

#جے_انت // SDL_VIDEO_OPENGL_CGL

#جے_انت // SDL_cocoaopengl_h_
