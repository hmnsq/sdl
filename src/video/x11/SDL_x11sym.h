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

/* *INDENT-OFF* */ // clang-format off

#ifndef SDL_X11_MODULE
#define SDL_X11_MODULE(modname)
#endif

#ifndef SDL_X11_SYM
#define SDL_X11_SYM(rc, fn, params)
#endif

SDL_X11_MODULE(BASEXLIB)
SDL_X11_SYM(XSizeHints*,XAllocSizeHints,(ଶୂନ୍ୟ))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(ଶୂନ୍ୟ))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(ଶୂନ୍ୟ))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XChangePointerControl,(Display* a,Bool b,Bool c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,ପୂର୍ଣ୍ଣସଂଖ୍ୟା f))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XChangeProperty,(Display* a,Window b,Atom c,Atom d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,_Xconst unsigned ଅକ୍ଷର* g,ପୂର୍ଣ୍ଣସଂଖ୍ୟା h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XCloseDisplay,(Display* a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst ଅକ୍ଷର *data,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା width,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst ଅକ୍ଷର* b, ଅକ୍ଷର*** c, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* d, ଅକ୍ଷର** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(ଶୂନ୍ୟ,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,ଅକ୍ଷର* f,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା g,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା h,ପୂର୍ଣ୍ଣସଂଖ୍ୟା i,ପୂର୍ଣ୍ଣସଂଖ୍ୟା j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା g,ପୂର୍ଣ୍ଣସଂଖ୍ୟା h,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(ଶୂନ୍ୟ,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, ପୂର୍ଣ୍ଣସଂଖ୍ୟା e, ପୂର୍ଣ୍ଣସଂଖ୍ୟା f, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା g, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ପୂର୍ଣ୍ଣସଂଖ୍ୟା j))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XDisplayKeycodes,(Display* a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* c))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XDrawRectangle,(Display* a,Drawable b,GC c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା g))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,ଅକ୍ଷର ***c))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XFillArc,(Display* a,Drawable b,GC c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା g, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, ପୂର୍ଣ୍ଣସଂଖ୍ୟା i))
SDL_X11_SYM(ଅକ୍ଷର*,XDisplayName,(_Xconst ଅକ୍ଷର* a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XDrawString,(Display* a,Drawable b,GC c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,_Xconst ଅକ୍ଷର* f,ପୂର୍ଣ୍ଣସଂଖ୍ୟା g))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XEventsQueued,(Display* a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XFillRectangle,(Display* a,Drawable b,GC c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XFlush,(Display* a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XFree,(ଶୂନ୍ୟ*a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(ଶୂନ୍ୟ,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(ଶୂନ୍ୟ,XFreeStringList,(ଅକ୍ଷର** a))
SDL_X11_SYM(ଅକ୍ଷର*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XGet_ନିବେଶ_Focus,(Display *a,Window *b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *c))
SDL_X11_SYM(ଚାବି_Sym*,XGetKeyboardMapping,(Display *a, ଚାବି_Code_2 b, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *d))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XGetErrorDatabaseText,(Display* a,_Xconst ଅକ୍ଷର* b,_Xconst ଅକ୍ଷର* c,_Xconst ଅକ୍ଷର* d,ଅକ୍ଷର* e,ପୂର୍ଣ୍ଣସଂଖ୍ୟା f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XGetPointerControl,(Display* a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* i,unsigned long* j,unsigned long *k,unsigned ଅକ୍ଷର **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XGrabKeyboard,(Display* a,Window b,Bool c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,Time f))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XGrabPointer,(Display* a,Window b,Bool c,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,Window g,Cursor h,Time i))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c))
SDL_X11_SYM(ଚାବି_Code_2,XKeysymToKeycode,(Display* a,ଚାବି_Sym b))
SDL_X11_SYM(ଅକ୍ଷର*,XKeysymToString,(ଚାବି_Sym a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst ଅକ୍ଷର* b,Bool c))
SDL_X11_SYM(XPixmap_Format_ମୂଲ୍ୟଗୁଡ଼ିକ*,XListPixmapFormats,(Display* a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst ଅକ୍ଷର* b))
SDL_X11_SYM(ଚାବି_Sym,XLookupKeysym,(XKeyEvent* a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XLookupString,(XKeyEvent* a,ଅକ୍ଷର* b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,ଚାବି_Sym* d,XComposeStatus* e))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,XVisualInfo* e))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XMissingExtension,(Display* a,_Xconst ଅକ୍ଷର* b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XMoveWindow,(Display* a,Window b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst ଅକ୍ଷର* a))
SDL_X11_SYM(Status,XInitThreads,(ଶୂନ୍ୟ))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,unsigned long g,ପୂର୍ଣ୍ଣସଂଖ୍ୟା h))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XPutImage,(Display* a,Drawable b,GC c,XImage* d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,ପୂର୍ଣ୍ଣସଂଖ୍ୟା g,ପୂର୍ଣ୍ଣସଂଖ୍ୟା h,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XQueryKeymap,(Display* a,ଅକ୍ଷର b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* e,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* f,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* g,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* h,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା* i))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XReparentWindow,(Display* a,Window b,Window c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XResetScreenSaver,(Display* a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XResizeWindow,(Display* a,Window b,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା d))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XScreen_ସଂଖ୍ୟା_Of_Screen,(Screen* a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XSelect_ନିବେଶ,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XSet_ନିବେଶ_Focus,(Display *a,Window b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,Time d))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(ଶୂନ୍ୟ,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(ଶୂନ୍ୟ,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(ଶୂନ୍ୟ,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(ଶୂନ୍ୟ,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,ଅକ୍ଷର** e,ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XStoreColors,(Display* a,Colormap b,XColor* c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XStoreName,(Display* a,Window b,_Xconst ଅକ୍ଷର* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(ଅକ୍ଷର** a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,XTextProperty* c))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XSync,(Display* a,Bool b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XTextExtents,(XFontStruct* a,_Xconst ଅକ୍ଷର* b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* e,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* f,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* g,Window* h))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XUngrabServer,(Display* a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XWarpPointer,(Display* a,Window b,Window c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା g,ପୂର୍ଣ୍ଣସଂଖ୍ୟା h,ପୂର୍ଣ୍ଣସଂଖ୍ୟା i))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(ଅକ୍ଷର*,XGetDefault,(Display* a,_Xconst ଅକ୍ଷର* b, _Xconst ଅକ୍ଷର* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst ଅକ୍ଷର* b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା* e))
SDL_X11_SYM(ଅକ୍ଷର *,XDisplayString,(Display* a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XGetErrorText,(Display* a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,ଅକ୍ଷର* c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d))
SDL_X11_SYM(ଶୂନ୍ୟ,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(ଶୂନ୍ୟ,_XFlush,(Display* a))
SDL_X11_SYM(ଶୂନ୍ୟ,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,_XRead,(Display* a,ଅକ୍ଷର* b,long c))
SDL_X11_SYM(ଶୂନ୍ୟ,_XReadPad,(Display* a,ଅକ୍ଷର* b,long c))
SDL_X11_SYM(ଶୂନ୍ୟ,_XSend,(Display* a,_Xconst ଅକ୍ଷର* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(ଶୂନ୍ୟ,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XQuery_ବୃକ୍ଷ,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା* f))
SDL_X11_SYM(Bool,XSupportsLocale,(ଶୂନ୍ୟ))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,ଅକ୍ଷର** b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(ଶୂନ୍ୟ))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(ଶୂନ୍ୟ,XDestroyRegion,(Region))
SDL_X11_SYM(ଶୂନ୍ୟ,XrmInitialize,(ଶୂନ୍ୟ))
SDL_X11_SYM(ଅକ୍ଷର*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(ଅକ୍ଷର *data))
SDL_X11_SYM(ଶୂନ୍ୟ,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, ଅକ୍ଷର* str_name, ଅକ୍ଷର* str_class, ଅକ୍ଷର **str_type_return, Xrm_ମୂଲ୍ୟ *))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XGetPointerMapping,(Display *a, unsigned ଅକ୍ଷର *b, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ପୂର୍ଣ୍ଣସଂଖ୍ୟା d, ପୂର୍ଣ୍ଣସଂଖ୍ୟା e, ପୂର୍ଣ୍ଣସଂଖ୍ୟା f, ପୂର୍ଣ୍ଣସଂଖ୍ୟା g, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *i))
SDL_X11_SYM(ଶୂନ୍ୟ, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, XIBarrierReleasePointer,(Display* a,  ପୂର୍ଣ୍ଣସଂଖ୍ୟା b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* b, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* c))
SDL_X11_SYM(Status, XFixes_Select_Selection_ନିବେଶ, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* b, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* b, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_ମୂଲ୍ୟ b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSync_ମୂଲ୍ୟ c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* b, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* c))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, XTestFakeMotionEvent, (Display* a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା b, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ପୂର୍ଣ୍ଣସଂଖ୍ୟା d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(ଶୂନ୍ୟ,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା * b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା * c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା * d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା * e, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *f))
SDL_X11_SYM(ଚାବି_Sym,XkbKeycodeToKeysym,(Display* a, ଚାବି_Code_2 b, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା b, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା b, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା c))
SDL_X11_SYM(ଶୂନ୍ୟ,XkbFreeClientMap,(XkbDescPtr a,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା b, Bool c))
SDL_X11_SYM(ଶୂନ୍ୟ,XkbFreeKeyboard,(XkbDescPtr a,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,Xutf8TextListToTextProperty,(Display* a,ଅକ୍ଷର** b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,ଅକ୍ଷର* c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ଚାବି_Sym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(ଶୂନ୍ୟ,XDestroyIC,(XIC a))
SDL_X11_SYM(ଅକ୍ଷର*,XGetICValues,(XIC,...))
SDL_X11_SYM(ଅକ୍ଷର*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ...))
SDL_X11_SYM(ଶୂନ୍ୟ,XSetICFocus,(XIC a))
SDL_X11_SYM(ଶୂନ୍ୟ,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,ସଂରଚନା _XrmHashBucketRec* b,ଅକ୍ଷର* c,ଅକ୍ଷର* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(ଅକ୍ଷର*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,ସଂରଚନା _XrmHashBucketRec*,ଅକ୍ଷର*,ଅକ୍ଷର*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,ସଂରଚନା _XrmHashBucketRec*,ଅକ୍ଷର*,ଅକ୍ଷର*,XIDProc,XPointer))
SDL_X11_SYM(ଶୂନ୍ୟ,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, ପୂର୍ଣ୍ଣସଂଖ୍ୟା e, ପୂର୍ଣ୍ଣସଂଖ୍ୟା f, _Xconst ଅକ୍ଷର *g, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,Xutf8TextExtents,(XFontSet a, _Xconst ଅକ୍ଷର* b, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(ଅକ୍ଷର*,XSetLocaleModifiers,(ଅଚଳ ଅକ୍ଷର *a))
SDL_X11_SYM(ଅକ୍ଷର*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,ପୂର୍ଣ୍ଣସଂଖ୍ୟା g,ପୂର୍ଣ୍ଣସଂଖ୍ୟା h,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d, ପୂର୍ଣ୍ଣସଂଖ୍ୟା e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ଅକ୍ଷର* e,XShmSegmentInfo* f,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା g,unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,ଅକ୍ଷର* c,XShmSegmentInfo* d, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା e, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା f, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *b, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *c, Bool *d))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,_XData32,(Display *dpy,ପଞ୍ଜିକରଣ _Xconst long *data,unsigned len))
SDL_X11_SYM(ଶୂନ୍ୟ,_XRead32,(Display *dpy,ପଞ୍ଜିକରଣ long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(ଶୂନ୍ୟ,_SmtBufferOverflow,(Display *dpy,ପଞ୍ଜିକରଣ smtDisplayPtr p))
SDL_X11_SYM(ଶୂନ୍ୟ,_SmtIpError,(Display *dpy,ପଞ୍ଜିକରଣ smtDisplayPtr p,ପୂର୍ଣ୍ଣସଂଖ୍ୟା i))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା a))
SDL_X11_SYM(ଶୂନ୍ୟ,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(ଶୂନ୍ୟ,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,ଅଚଳ XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,ଅଚଳ XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, ଅଚଳ ଅକ୍ଷର *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *major_version_return,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଅଙ୍କ_screens))
SDL_X11_SYM(ଶୂନ୍ୟ,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *c))
SDL_X11_SYM(ଶୂନ୍ୟ,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XISelectEvents,(Display *a,Window b,XIEventMask *c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XIGrabTouchBegin,(Display *a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,Window c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,XIEventMask *e,ପୂର୍ଣ୍ଣସଂଖ୍ୟା f,XIGrabModifiers *g))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XIUngrabTouchBegin, (Display *a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,Window c, ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,Window c,Window d,ଦ୍ୱିଗୁଣ e,ଦ୍ୱିଗୁଣ f,ପୂର୍ଣ୍ଣସଂଖ୍ୟା g,ପୂର୍ଣ୍ଣସଂଖ୍ୟା h,ଦ୍ୱିଗୁଣ i,ଦ୍ୱିଗୁଣ j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,ପୂର୍ଣ୍ଣସଂଖ୍ୟା b,Atom c,long d,long e,Bool f, Atom g, Atom *h, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *i, unsigned long *j, unsigned long *k, unsigned ଅକ୍ଷର **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *major_versionp,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *event_base_return,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,ପୂର୍ଣ୍ଣସଂଖ୍ୟା sizeID,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,ପୂର୍ଣ୍ଣସଂଖ୍ୟା size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(ଶୂନ୍ୟ,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(ଶୂନ୍ୟ,XRRSetScreenSize,(Display *dpy, Window window,ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height,ପୂର୍ଣ୍ଣସଂଖ୍ୟା mmWidth, ପୂର୍ଣ୍ଣସଂଖ୍ୟା mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *minWidth, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *minHeight, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *maxWidth, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(ଶୂନ୍ୟ,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(ଶୂନ୍ୟ,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(ଶୂନ୍ୟ,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y, RRMode mode, Rotation rotation, RROutput *outputs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned ଅକ୍ଷର **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(ଶୂନ୍ୟ,XRRSelect_ନିବେଶ,(Display *dpy, Window window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *event_base,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *major_versionp,ପୂର୍ଣ୍ଣସଂଖ୍ୟା *minor_versionp))
SDL_X11_SYM(ଶୂନ୍ୟ,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(ଶୂନ୍ୟ,XShapeCombineMask,(Display *dpy,Window dest,ପୂର୍ଣ୍ଣସଂଖ୍ୟା dest_kind,ପୂର୍ଣ୍ଣସଂଖ୍ୟା x_off,ପୂର୍ଣ୍ଣସଂଖ୍ୟା y_off,Pixmap src,ପୂର୍ଣ୍ଣସଂଖ୍ୟା op))
SDL_X11_SYM(ଶୂନ୍ୟ,XShapeCombineRegion,(Display *a,Window b,ପୂର୍ଣ୍ଣସଂଖ୍ୟା c,ପୂର୍ଣ୍ଣସଂଖ୍ୟା d,ପୂର୍ଣ୍ଣସଂଖ୍ୟା e,Region f,ପୂର୍ଣ୍ଣସଂଖ୍ୟା g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
