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
SDL_X11_SYM(XSizeHints*,XAllocSizeHints,(void))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(void))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(void))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XChangePointerControl,(Display* a,Bool b,Bool c,පූර්ණ_සංඛ්‍යා d,පූර්ණ_සංඛ්‍යා e,පූර්ණ_සංඛ්‍යා f))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XChangeProperty,(Display* a,Window b,Atom c,Atom d,පූර්ණ_සංඛ්‍යා e,පූර්ණ_සංඛ්‍යා f,_Xconst unsigned var_na* g,පූර්ණ_සංඛ්‍යා h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XCloseDisplay,(Display* a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst var_na *data,unsigned පූර්ණ_සංඛ්‍යා width,unsigned පූර්ණ_සංඛ්‍යා height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,පූර්ණ_සංඛ්‍යා d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned පූර්ණ_සංඛ්‍යා f,unsigned පූර්ණ_සංඛ්‍යා g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned පූර්ණ_සංඛ්‍යා d,unsigned පූර්ණ_සංඛ්‍යා e,unsigned පූර්ණ_සංඛ්‍යා f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned පූර්ණ_සංඛ්‍යා b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst var_na* b, var_na*** c, පූර්ණ_සංඛ්‍යා* d, var_na** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(void,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned පූර්ණ_සංඛ්‍යා c,පූර්ණ_සංඛ්‍යා d,පූර්ණ_සංඛ්‍යා e,var_na* f,unsigned පූර්ණ_සංඛ්‍යා g,unsigned පූර්ණ_සංඛ්‍යා h,පූර්ණ_සංඛ්‍යා i,පූර්ණ_සංඛ්‍යා j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,පූර්ණ_සංඛ්‍යා c,පූර්ණ_සංඛ්‍යා d,unsigned පූර්ණ_සංඛ්‍යා e,unsigned පූර්ණ_සංඛ්‍යා f,unsigned පූර්ණ_සංඛ්‍යා g,පූර්ණ_සංඛ්‍යා h,unsigned පූර්ණ_සංඛ්‍යා i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(void,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, පූර්ණ_සංඛ්‍යා e, පූර්ණ_සංඛ්‍යා f, unsigned පූර්ණ_සංඛ්‍යා g, unsigned පූර්ණ_සංඛ්‍යා h, පූර්ණ_සංඛ්‍යා i, පූර්ණ_සංඛ්‍යා j))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XDisplayKeycodes,(Display* a,පූර්ණ_සංඛ්‍යා* b,පූර්ණ_සංඛ්‍යා* c))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XDrawRectangle,(Display* a,Drawable b,GC c,පූර්ණ_සංඛ්‍යා d,පූර්ණ_සංඛ්‍යා e,unsigned පූර්ණ_සංඛ්‍යා f,unsigned පූර්ණ_සංඛ්‍යා g))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,var_na ***c))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XFillArc,(Display* a,Drawable b,GC c,පූර්ණ_සංඛ්‍යා d,පූර්ණ_සංඛ්‍යා e,unsigned පූර්ණ_සංඛ්‍යා f,unsigned පූර්ණ_සංඛ්‍යා g, පූර්ණ_සංඛ්‍යා h, පූර්ණ_සංඛ්‍යා i))
SDL_X11_SYM(var_na*,XDisplayName,(_Xconst var_na* a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XDrawString,(Display* a,Drawable b,GC c,පූර්ණ_සංඛ්‍යා d,පූර්ණ_සංඛ්‍යා e,_Xconst var_na* f,පූර්ණ_සංඛ්‍යා g))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XEventsQueued,(Display* a,පූර්ණ_සංඛ්‍යා b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XFillRectangle,(Display* a,Drawable b,GC c,පූර්ණ_සංඛ්‍යා d,පූර්ණ_සංඛ්‍යා e,unsigned පූර්ණ_සංඛ්‍යා f,unsigned පූර්ණ_සංඛ්‍යා g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XFlush,(Display* a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XFree,(void*a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(void,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(void,XFreeStringList,(var_na** a))
SDL_X11_SYM(var_na*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XGetInputFocus,(Display *a,Window *b,පූර්ණ_සංඛ්‍යා *c))
SDL_X11_SYM(KeySym*,XGetKeyboardMapping,(Display *a, KeyCode b, පූර්ණ_සංඛ්‍යා c, පූර්ණ_සංඛ්‍යා *d))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XGetErrorDatabaseText,(Display* a,_Xconst var_na* b,_Xconst var_na* c,_Xconst var_na* d,var_na* e,පූර්ණ_සංඛ්‍යා f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XGetPointerControl,(Display* a,පූර්ණ_සංඛ්‍යා* b,පූර්ණ_සංඛ්‍යා* c,පූර්ණ_සංඛ්‍යා* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,පූර්ණ_සංඛ්‍යා* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,පූර්ණ_සංඛ්‍යා* i,unsigned long* j,unsigned long *k,unsigned var_na **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XGrabKeyboard,(Display* a,Window b,Bool c,පූර්ණ_සංඛ්‍යා d,පූර්ණ_සංඛ්‍යා e,Time f))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XGrabPointer,(Display* a,Window b,Bool c,unsigned පූර්ණ_සංඛ්‍යා d,පූර්ණ_සංඛ්‍යා e,පූර්ණ_සංඛ්‍යා f,Window g,Cursor h,Time i))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,පූර්ණ_සංඛ්‍යා c))
SDL_X11_SYM(KeyCode,XKeysymToKeycode,(Display* a,KeySym b))
SDL_X11_SYM(var_na*,XKeysymToString,(KeySym a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst var_na* b,Bool c))
SDL_X11_SYM(XPixmapFormatValues*,XListPixmapFormats,(Display* a,පූර්ණ_සංඛ්‍යා* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst var_na* b))
SDL_X11_SYM(KeySym,XLookupKeysym,(XKeyEvent* a,පූර්ණ_සංඛ්‍යා b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XLookupString,(XKeyEvent* a,var_na* b,පූර්ණ_සංඛ්‍යා c,KeySym* d,XComposeStatus* e))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,පූර්ණ_සංඛ්‍යා b,පූර්ණ_සංඛ්‍යා c,පූර්ණ_සංඛ්‍යා d,XVisualInfo* e))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XMissingExtension,(Display* a,_Xconst var_na* b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XMoveWindow,(Display* a,Window b,පූර්ණ_සංඛ්‍යා c,පූර්ණ_සංඛ්‍යා d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst var_na* a))
SDL_X11_SYM(Status,XInitThreads,(void))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,පූර්ණ_සංඛ්‍යා c, පූර්ණ_සංඛ්‍යා d,unsigned පූර්ණ_සංඛ්‍යා e,unsigned පූර්ණ_සංඛ්‍යා f,unsigned long g,පූර්ණ_සංඛ්‍යා h))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XPutImage,(Display* a,Drawable b,GC c,XImage* d,පූර්ණ_සංඛ්‍යා e,පූර්ණ_සංඛ්‍යා f,පූර්ණ_සංඛ්‍යා g,පූර්ණ_සංඛ්‍යා h,unsigned පූර්ණ_සංඛ්‍යා i,unsigned පූර්ණ_සංඛ්‍යා j))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XQueryKeymap,(Display* a,var_na b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,පූර්ණ_සංඛ්‍යා* e,පූර්ණ_සංඛ්‍යා* f,පූර්ණ_සංඛ්‍යා* g,පූර්ණ_සංඛ්‍යා* h,unsigned පූර්ණ_සංඛ්‍යා* i))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XReparentWindow,(Display* a,Window b,Window c,පූර්ණ_සංඛ්‍යා d,පූර්ණ_සංඛ්‍යා e))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XResetScreenSaver,(Display* a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XResizeWindow,(Display* a,Window b,unsigned පූර්ණ_සංඛ්‍යා c,unsigned පූර්ණ_සංඛ්‍යා d))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XScreenNumberOfScreen,(Screen* a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XSelectInput,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XSetInputFocus,(Display *a,Window b,පූර්ණ_සංඛ්‍යා c,Time d))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(void,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(void,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(void,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(void,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,var_na** e,පූර්ණ_සංඛ්‍යා f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,පූර්ණ_සංඛ්‍යා d))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XStoreColors,(Display* a,Colormap b,XColor* c,පූර්ණ_සංඛ්‍යා d))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XStoreName,(Display* a,Window b,_Xconst var_na* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(var_na** a,පූර්ණ_සංඛ්‍යා b,XTextProperty* c))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XSync,(Display* a,Bool b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XTextExtents,(XFontStruct* a,_Xconst var_na* b,පූර්ණ_සංඛ්‍යා c,පූර්ණ_සංඛ්‍යා* d,පූර්ණ_සංඛ්‍යා* e,පූර්ණ_සංඛ්‍යා* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,පූර්ණ_සංඛ්‍යා d,පූර්ණ_සංඛ්‍යා e,පූර්ණ_සංඛ්‍යා* f,පූර්ණ_සංඛ්‍යා* g,Window* h))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XUngrabServer,(Display* a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XWarpPointer,(Display* a,Window b,Window c,පූර්ණ_සංඛ්‍යා d,පූර්ණ_සංඛ්‍යා e,unsigned පූර්ණ_සංඛ්‍යා f,unsigned පූර්ණ_සංඛ්‍යා g,පූර්ණ_සංඛ්‍යා h,පූර්ණ_සංඛ්‍යා i))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,පූර්ණ_සංඛ්‍යා c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(var_na*,XGetDefault,(Display* a,_Xconst var_na* b, _Xconst var_na* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst var_na* b,පූර්ණ_සංඛ්‍යා* c,පූර්ණ_සංඛ්‍යා* d,පූර්ණ_සංඛ්‍යා* e))
SDL_X11_SYM(var_na *,XDisplayString,(Display* a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XGetErrorText,(Display* a,පූර්ණ_සංඛ්‍යා b,var_na* c,පූර්ණ_සංඛ්‍යා d))
SDL_X11_SYM(void,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(void,_XFlush,(Display* a))
SDL_X11_SYM(void,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,_XRead,(Display* a,var_na* b,long c))
SDL_X11_SYM(void,_XReadPad,(Display* a,var_na* b,long c))
SDL_X11_SYM(void,_XSend,(Display* a,_Xconst var_na* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,පූර්ණ_සංඛ්‍යා c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,පූර්ණ_සංඛ්‍යා b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,පූර්ණ_සංඛ්‍යා b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(void,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XQueryTree,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned පූර්ණ_සංඛ්‍යා* f))
SDL_X11_SYM(Bool,XSupportsLocale,(void))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,var_na** b,පූර්ණ_සංඛ්‍යා c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(void))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(void,XDestroyRegion,(Region))
SDL_X11_SYM(void,XrmInitialize,(void))
SDL_X11_SYM(var_na*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(var_na *data))
SDL_X11_SYM(void,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, var_na* str_name, var_na* str_class, var_na **str_type_return, XrmValue *))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XGetPointerMapping,(Display *a, unsigned var_na *b, unsigned පූර්ණ_සංඛ්‍යා c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, පූර්ණ_සංඛ්‍යා c, පූර්ණ_සංඛ්‍යා d, පූර්ණ_සංඛ්‍යා e, පූර්ණ_සංඛ්‍යා f, පූර්ණ_සංඛ්‍යා g, පූර්ණ_සංඛ්‍යා h, පූර්ණ_සංඛ්‍යා *i))
SDL_X11_SYM(void, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා, XIBarrierReleasePointer,(Display* a,  පූර්ණ_සංඛ්‍යා b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, පූර්ණ_සංඛ්‍යා* b, පූර්ණ_සංඛ්‍යා* c))
SDL_X11_SYM(Status, XFixesSelectSelectionInput, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, පූර්ණ_සංඛ්‍යා* b, පූර්ණ_සංඛ්‍යා* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, පූර්ණ_සංඛ්‍යා* b, පූර්ණ_සංඛ්‍යා* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSyncValue b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSyncValue c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, පූර්ණ_සංඛ්‍යා* b, පූර්ණ_සංඛ්‍යා* c))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා, XTestFakeMotionEvent, (Display* a, පූර්ණ_සංඛ්‍යා b, පූර්ණ_සංඛ්‍යා c, පූර්ණ_සංඛ්‍යා d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(void,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,පූර්ණ_සංඛ්‍යා * b,පූර්ණ_සංඛ්‍යා * c,පූර්ණ_සංඛ්‍යා * d,පූර්ණ_සංඛ්‍යා * e, පූර්ණ_සංඛ්‍යා *f))
SDL_X11_SYM(KeySym,XkbKeycodeToKeysym,(Display* a, KeyCode b, unsigned පූර්ණ_සංඛ්‍යා c, unsigned පූර්ණ_සංඛ්‍යා d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned පූර්ණ_සංඛ්‍යා b, unsigned පූර්ණ_සංඛ්‍යා c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned පූර්ණ_සංඛ්‍යා b, unsigned පූර්ණ_සංඛ්‍යා c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned පූර්ණ_සංඛ්‍යා b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned පූර්ණ_සංඛ්‍යා b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned පූර්ණ_සංඛ්‍යා b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned පූර්ණ_සංඛ්‍යා b,unsigned පූර්ණ_සංඛ්‍යා c))
SDL_X11_SYM(void,XkbFreeClientMap,(XkbDescPtr a,unsigned පූර්ණ_සංඛ්‍යා b, Bool c))
SDL_X11_SYM(void,XkbFreeKeyboard,(XkbDescPtr a,unsigned පූර්ණ_සංඛ්‍යා b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,Xutf8TextListToTextProperty,(Display* a,var_na** b,පූර්ණ_සංඛ්‍යා c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,var_na* c,පූර්ණ_සංඛ්‍යා d,KeySym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(void,XDestroyIC,(XIC a))
SDL_X11_SYM(var_na*,XGetICValues,(XIC,...))
SDL_X11_SYM(var_na*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(පූර්ණ_සංඛ්‍යා, ...))
SDL_X11_SYM(void,XSetICFocus,(XIC a))
SDL_X11_SYM(void,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,sa_nracanaa _XrmHashBucketRec* b,var_na* c,var_na* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(var_na*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,sa_nracanaa _XrmHashBucketRec*,var_na*,var_na*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,sa_nracanaa _XrmHashBucketRec*,var_na*,var_na*,XIDProc,XPointer))
SDL_X11_SYM(void,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, පූර්ණ_සංඛ්‍යා e, පූර්ණ_සංඛ්‍යා f, _Xconst var_na *g, පූර්ණ_සංඛ්‍යා h))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,Xutf8TextExtents,(XFontSet a, _Xconst var_na* b, පූර්ණ_සංඛ්‍යා c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(var_na*,XSetLocaleModifiers,(const var_na *a))
SDL_X11_SYM(var_na*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,පූර්ණ_සංඛ්‍යා e,පූර්ණ_සංඛ්‍යා f,පූර්ණ_සංඛ්‍යා g,පූර්ණ_සංඛ්‍යා h,unsigned පූර්ණ_සංඛ්‍යා i,unsigned පූර්ණ_සංඛ්‍යා j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,පූර්ණ_සංඛ්‍යා d, පූර්ණ_සංඛ්‍යා e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned පූර්ණ_සංඛ්‍යා c,පූර්ණ_සංඛ්‍යා d,var_na* e,XShmSegmentInfo* f,unsigned පූර්ණ_සංඛ්‍යා g,unsigned පූර්ණ_සංඛ්‍යා h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,var_na* c,XShmSegmentInfo* d, unsigned පූර්ණ_සංඛ්‍යා e, unsigned පූර්ණ_සංඛ්‍යා f, unsigned පූර්ණ_සංඛ්‍යා g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, පූර්ණ_සංඛ්‍යා *b, පූර්ණ_සංඛ්‍යා *c, Bool *d))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,_XData32,(Display *dpy,pa_njikaa _Xconst long *data,unsigned len))
SDL_X11_SYM(void,_XRead32,(Display *dpy,pa_njikaa long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(void,_SmtBufferOverflow,(Display *dpy,pa_njikaa smtDisplayPtr p))
SDL_X11_SYM(void,_SmtIpError,(Display *dpy,pa_njikaa smtDisplayPtr p,පූර්ණ_සංඛ්‍යා i))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(පූර්ණ_සංඛ්‍යා a,පූර්ණ_සංඛ්‍යා b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(පූර්ණ_සංඛ්‍යා a))
SDL_X11_SYM(void,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(void,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,const XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,const XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, const var_na *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,පූර්ණ_සංඛ්‍යා *major_version_return,පූර්ණ_සංඛ්‍යා *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,පූර්ණ_සංඛ්‍යා num_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,පූර්ණ_සංඛ්‍යා *num_screens))
SDL_X11_SYM(void,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,පූර්ණ_සංඛ්‍යා b,පූර්ණ_සංඛ්‍යා *c))
SDL_X11_SYM(void,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XISelectEvents,(Display *a,Window b,XIEventMask *c,පූර්ණ_සංඛ්‍යා d))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XIGrabTouchBegin,(Display *a,පූර්ණ_සංඛ්‍යා b,Window c,පූර්ණ_සංඛ්‍යා d,XIEventMask *e,පූර්ණ_සංඛ්‍යා f,XIGrabModifiers *g))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XIUngrabTouchBegin, (Display *a,පූර්ණ_සංඛ්‍යා b,Window c, පූර්ණ_සංඛ්‍යා d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,පූර්ණ_සංඛ්‍යා *b,පූර්ණ_සංඛ්‍යා *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,පූර්ණ_සංඛ්‍යා *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,පූර්ණ_සංඛ්‍යා *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,පූර්ණ_සංඛ්‍යා b,Window c,Window d,dviguu_na e,dviguu_na f,පූර්ණ_සංඛ්‍යා g,පූර්ණ_සංඛ්‍යා h,dviguu_na i,dviguu_na j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,පූර්ණ_සංඛ්‍යා b,Atom c,long d,long e,Bool f, Atom g, Atom *h, පූර්ණ_සංඛ්‍යා *i, unsigned long *j, unsigned long *k, unsigned var_na **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,පූර්ණ_සංඛ්‍යා *major_versionp,පූර්ණ_සංඛ්‍යා *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,පූර්ණ_සංඛ්‍යා *event_base_return,පූර්ණ_සංඛ්‍යා *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,පූර්ණ_සංඛ්‍යා sizeID,පූර්ණ_සංඛ්‍යා *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,පූර්ණ_සංඛ්‍යා *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,පූර්ණ_සංඛ්‍යා size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(void,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(void,XRRSetScreenSize,(Display *dpy, Window window,පූර්ණ_සංඛ්‍යා width, පූර්ණ_සංඛ්‍යා height,පූර්ණ_සංඛ්‍යා mmWidth, පූර්ණ_සංඛ්‍යා mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,පූර්ණ_සංඛ්‍යා *minWidth, පූර්ණ_සංඛ්‍යා *minHeight, පූර්ණ_සංඛ්‍යා *maxWidth, පූර්ණ_සංඛ්‍යා *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(void,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(void,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(void,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, පූර්ණ_සංඛ්‍යා x, පූර්ණ_සංඛ්‍යා y, RRMode mode, Rotation rotation, RROutput *outputs, පූර්ණ_සංඛ්‍යා noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, පූර්ණ_සංඛ්‍යා *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(පූර්ණ_සංඛ්‍යා,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, පූර්ණ_සංඛ්‍යා *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned var_na **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(void,XRRSelectInput,(Display *dpy, Window window, පූර්ණ_සංඛ්‍යා mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,පූර්ණ_සංඛ්‍යා *event_base,පූර්ණ_සංඛ්‍යා *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,පූර්ණ_සංඛ්‍යා *major_versionp,පූර්ණ_සංඛ්‍යා *minor_versionp))
SDL_X11_SYM(void,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(void,XShapeCombineMask,(Display *dpy,Window dest,පූර්ණ_සංඛ්‍යා dest_kind,පූර්ණ_සංඛ්‍යා x_off,පූර්ණ_සංඛ්‍යා y_off,Pixmap src,පූර්ණ_සංඛ්‍යා op))
SDL_X11_SYM(void,XShapeCombineRegion,(Display *a,Window b,පූර්ණ_සංඛ්‍යා c,පූර්ණ_සංඛ්‍යා d,පූර්ණ_සංඛ්‍යා e,Region f,පූර්ණ_සංඛ්‍යා g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
