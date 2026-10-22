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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_cocoaopengl_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_cocoaopengl_h_

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_CGL

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

// We still support OpenGL as long as Apple offers it, deprecated or not, so disable deprecation warnings about it.
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __clang__
#ಸೂಚನೆ clang diagnostic ತಳ್ಳು
#ಸೂಚನೆ clang diagnostic ignored "-Wdeprecated-declarations"
#ಆದರೆ_ಅಂತ್ಯ

ರಚನೆ SDL_GLDriver_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ initialized;
};

@interface SDL3OpenGLContext : NSOpenGLContext
{
    SDL_AtomicInt dirty;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    CVDisplayLinkRef displayLink;
  @ಸಾರ್ವಜನಿಕ
    SDL_Mutex *ಅದಲುಬದಲು_Interval_Mutex;
  @ಸಾರ್ವಜನಿಕ
    SDL_Condition *ಅದಲುಬದಲು_Interval_Cond;
  @ಸಾರ್ವಜನಿಕ
    SDL_AtomicInt ಅದಲುಬದಲು_Interval_Setting;
  @ಸಾರ್ವಜನಿಕ
    SDL_AtomicInt ಅದಲುಬದಲು_Intervals_Passed;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (ಶೂನ್ಯ)ವೇಳಾಪಟ್ಟಿ_Update;
- (ಶೂನ್ಯ)updateIfNeeded;
- (ಶೂನ್ಯ)moved_ಗಮ್ಯ_New_Screen;
- (ಶೂನ್ಯ)ಗಣ_ಕಿಟಕಿ:(SDL_ಕಿಟಕಿ *)ಕಿಟಕಿ;
- (SDL_ಕಿಟಕಿ *)ಕಿಟಕಿ;
- (ಶೂನ್ಯ)explicitUpdate;
- (ಶೂನ್ಯ)cleanup;

@property(retain, nonatomic) NSOpenGLPixelFormat *openglPixelFormat; // macOS 10.10 has -[NSOpenGLContext pixelFormat] but this handles older OS releases.

@ಕೊನೆ

// OpenGL functions
ಬಾಹ್ಯ bool Cocoa_GL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ);
ಬಾಹ್ಯ SDL_Function_ಸೂಚಕ Cocoa_GL_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_GL_UnloadLibrary(SDL_VideoDevice *_this);
ಬಾಹ್ಯ SDL_GLContext Cocoa_GL_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Cocoa_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context);
ಬಾಹ್ಯ bool Cocoa_GL_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval);
ಬಾಹ್ಯ bool Cocoa_GL_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval);
ಬಾಹ್ಯ bool Cocoa_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Cocoa_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __clang__
#ಸೂಚನೆ clang diagnostic ತೆಗೆ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_CGL

#ಆದರೆ_ಅಂತ್ಯ // SDL_cocoaopengl_h_
