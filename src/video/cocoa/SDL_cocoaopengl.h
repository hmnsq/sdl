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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_cocoaopengl_h_
#تعریف_کرو SDL_cocoaopengl_h_

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_CGL

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

// We still support OpenGL as long as Apple offers it, deprecated or not, so disable deprecation warnings about it.
#اگر_تعریف_شدہ __clang__
#ہدایت clang diagnostic ڈالو
#ہدایت clang diagnostic ignored "-Wdeprecated-declarations"
#اگر_ختم

ساخت SDL_GLDriver_ڈیٹا
{
    صحیح initialized;
};

@interface SDL3OpenGLContext : NSOpenGLContext
{
    SDL_AtomicInt dirty;
    SDL_کھڑکی *کھڑکی;
    CVDisplayLinkRef displayLink;
  @عوامی
    SDL_Mutex *تبادلہ_Interval_Mutex;
  @عوامی
    SDL_Condition *تبادلہ_Interval_Cond;
  @عوامی
    SDL_AtomicInt تبادلہ_Interval_Setting;
  @عوامی
    SDL_AtomicInt تبادلہ_Intervals_Passed;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (خالی)جدول_وقت_Update;
- (خالی)updateIfNeeded;
- (خالی)moved_مقصد_New_Screen;
- (خالی)سیٹ_کھڑکی:(SDL_کھڑکی *)کھڑکی;
- (SDL_کھڑکی *)کھڑکی;
- (خالی)explicitUpdate;
- (خالی)cleanup;

@property(retain, nonatomic) NSOpenGLPixelFormat *openglPixelFormat; // macOS 10.10 has -[NSOpenGLContext pixelFormat] but this handles older OS releases.

@انتہا

// OpenGL functions
خارجی bool Cocoa_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ);
خارجی SDL_Function_اشارہ_گر Cocoa_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجی خالی Cocoa_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجی SDL_GLContext Cocoa_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool Cocoa_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context);
خارجی bool Cocoa_GL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval);
خارجی bool Cocoa_GL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval);
خارجی bool Cocoa_GL_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool Cocoa_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#اگر_تعریف_شدہ __clang__
#ہدایت clang diagnostic نکالو
#اگر_ختم

#اگر_ختم // SDL_VIDEO_OPENGL_CGL

#اگر_ختم // SDL_cocoaopengl_h_
