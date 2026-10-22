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
SDL_X11_SYM(số_nguyên,XChangePointerControl,(Display* a,Bool b,Bool c,số_nguyên d,số_nguyên e,số_nguyên f))
SDL_X11_SYM(số_nguyên,XChangeProperty,(Display* a,Window b,Atom c,Atom d,số_nguyên e,số_nguyên f,_Xconst unsigned char* g,số_nguyên h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(số_nguyên,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(số_nguyên,XCloseDisplay,(Display* a))
SDL_X11_SYM(số_nguyên,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst char *data,unsigned số_nguyên width,unsigned số_nguyên height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,số_nguyên d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned số_nguyên f,unsigned số_nguyên g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned số_nguyên d,unsigned số_nguyên e,unsigned số_nguyên f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned số_nguyên b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst char* b, char*** c, số_nguyên* d, char** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(void,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned số_nguyên c,số_nguyên d,số_nguyên e,char* f,unsigned số_nguyên g,unsigned số_nguyên h,số_nguyên i,số_nguyên j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,số_nguyên c,số_nguyên d,unsigned số_nguyên e,unsigned số_nguyên f,unsigned số_nguyên g,số_nguyên h,unsigned số_nguyên i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(void,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, số_nguyên e, số_nguyên f, unsigned số_nguyên g, unsigned số_nguyên h, số_nguyên i, số_nguyên j))
SDL_X11_SYM(số_nguyên,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(số_nguyên,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(số_nguyên,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(số_nguyên,XDisplayKeycodes,(Display* a,số_nguyên* b,số_nguyên* c))
SDL_X11_SYM(số_nguyên,XDrawRectangle,(Display* a,Drawable b,GC c,số_nguyên d,số_nguyên e,unsigned số_nguyên f,unsigned số_nguyên g))
SDL_X11_SYM(số_nguyên,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,char ***c))
SDL_X11_SYM(số_nguyên,XFillArc,(Display* a,Drawable b,GC c,số_nguyên d,số_nguyên e,unsigned số_nguyên f,unsigned số_nguyên g, số_nguyên h, số_nguyên i))
SDL_X11_SYM(char*,XDisplayName,(_Xconst char* a))
SDL_X11_SYM(số_nguyên,XDrawString,(Display* a,Drawable b,GC c,số_nguyên d,số_nguyên e,_Xconst char* f,số_nguyên g))
SDL_X11_SYM(số_nguyên,XEventsQueued,(Display* a,số_nguyên b))
SDL_X11_SYM(số_nguyên,XFillRectangle,(Display* a,Drawable b,GC c,số_nguyên d,số_nguyên e,unsigned số_nguyên f,unsigned số_nguyên g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(số_nguyên,XFlush,(Display* a))
SDL_X11_SYM(số_nguyên,XFree,(void*a))
SDL_X11_SYM(số_nguyên,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(void,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(số_nguyên,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(số_nguyên,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(số_nguyên,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(số_nguyên,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(số_nguyên,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(void,XFreeStringList,(char** a))
SDL_X11_SYM(char*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(số_nguyên,XGetInputFocus,(Display *a,Window *b,số_nguyên *c))
SDL_X11_SYM(KeySym*,XGetKeyboardMapping,(Display *a, KeyCode b, số_nguyên c, số_nguyên *d))
SDL_X11_SYM(số_nguyên,XGetErrorDatabaseText,(Display* a,_Xconst char* b,_Xconst char* c,_Xconst char* d,char* e,số_nguyên f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(số_nguyên,XGetPointerControl,(Display* a,số_nguyên* b,số_nguyên* c,số_nguyên* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,số_nguyên* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(số_nguyên,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,số_nguyên* i,unsigned long* j,unsigned long *k,unsigned char **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(số_nguyên,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(số_nguyên,XGrabKeyboard,(Display* a,Window b,Bool c,số_nguyên d,số_nguyên e,Time f))
SDL_X11_SYM(số_nguyên,XGrabPointer,(Display* a,Window b,Bool c,unsigned số_nguyên d,số_nguyên e,số_nguyên f,Window g,Cursor h,Time i))
SDL_X11_SYM(số_nguyên,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,số_nguyên c))
SDL_X11_SYM(KeyCode,XKeysymToKeycode,(Display* a,KeySym b))
SDL_X11_SYM(char*,XKeysymToString,(KeySym a))
SDL_X11_SYM(số_nguyên,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst char* b,Bool c))
SDL_X11_SYM(XPixmapFormatValues*,XListPixmapFormats,(Display* a,số_nguyên* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst char* b))
SDL_X11_SYM(KeySym,XLookupKeysym,(XKeyEvent* a,số_nguyên b))
SDL_X11_SYM(số_nguyên,XLookupString,(XKeyEvent* a,char* b,số_nguyên c,KeySym* d,XComposeStatus* e))
SDL_X11_SYM(số_nguyên,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,số_nguyên b,số_nguyên c,số_nguyên d,XVisualInfo* e))
SDL_X11_SYM(số_nguyên,XMissingExtension,(Display* a,_Xconst char* b))
SDL_X11_SYM(số_nguyên,XMoveWindow,(Display* a,Window b,số_nguyên c,số_nguyên d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst char* a))
SDL_X11_SYM(Status,XInitThreads,(void))
SDL_X11_SYM(số_nguyên,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(số_nguyên,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,số_nguyên c, số_nguyên d,unsigned số_nguyên e,unsigned số_nguyên f,unsigned long g,số_nguyên h))
SDL_X11_SYM(số_nguyên,XPutImage,(Display* a,Drawable b,GC c,XImage* d,số_nguyên e,số_nguyên f,số_nguyên g,số_nguyên h,unsigned số_nguyên i,unsigned số_nguyên j))
SDL_X11_SYM(số_nguyên,XQueryKeymap,(Display* a,char b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,số_nguyên* e,số_nguyên* f,số_nguyên* g,số_nguyên* h,unsigned số_nguyên* i))
SDL_X11_SYM(số_nguyên,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(số_nguyên,XReparentWindow,(Display* a,Window b,Window c,số_nguyên d,số_nguyên e))
SDL_X11_SYM(số_nguyên,XResetScreenSaver,(Display* a))
SDL_X11_SYM(số_nguyên,XResizeWindow,(Display* a,Window b,unsigned số_nguyên c,unsigned số_nguyên d))
SDL_X11_SYM(số_nguyên,XScreenNumberOfScreen,(Screen* a))
SDL_X11_SYM(số_nguyên,XSelectInput,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(số_nguyên,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(số_nguyên,XSetInputFocus,(Display *a,Window b,số_nguyên c,Time d))
SDL_X11_SYM(số_nguyên,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(số_nguyên,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(void,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(số_nguyên,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(void,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(void,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(void,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,char** e,số_nguyên f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,số_nguyên d))
SDL_X11_SYM(số_nguyên,XStoreColors,(Display* a,Colormap b,XColor* c,số_nguyên d))
SDL_X11_SYM(số_nguyên,XStoreName,(Display* a,Window b,_Xconst char* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(char** a,số_nguyên b,XTextProperty* c))
SDL_X11_SYM(số_nguyên,XSync,(Display* a,Bool b))
SDL_X11_SYM(số_nguyên,XTextExtents,(XFontStruct* a,_Xconst char* b,số_nguyên c,số_nguyên* d,số_nguyên* e,số_nguyên* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,số_nguyên d,số_nguyên e,số_nguyên* f,số_nguyên* g,Window* h))
SDL_X11_SYM(số_nguyên,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(số_nguyên,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(số_nguyên,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(số_nguyên,XUngrabServer,(Display* a))
SDL_X11_SYM(số_nguyên,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(số_nguyên,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(số_nguyên,XWarpPointer,(Display* a,Window b,Window c,số_nguyên d,số_nguyên e,unsigned số_nguyên f,unsigned số_nguyên g,số_nguyên h,số_nguyên i))
SDL_X11_SYM(số_nguyên,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,số_nguyên c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(char*,XGetDefault,(Display* a,_Xconst char* b, _Xconst char* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst char* b,số_nguyên* c,số_nguyên* d,số_nguyên* e))
SDL_X11_SYM(char *,XDisplayString,(Display* a))
SDL_X11_SYM(số_nguyên,XGetErrorText,(Display* a,số_nguyên b,char* c,số_nguyên d))
SDL_X11_SYM(void,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(void,_XFlush,(Display* a))
SDL_X11_SYM(void,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(số_nguyên,_XRead,(Display* a,char* b,long c))
SDL_X11_SYM(void,_XReadPad,(Display* a,char* b,long c))
SDL_X11_SYM(void,_XSend,(Display* a,_Xconst char* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,số_nguyên c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,số_nguyên b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,số_nguyên b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(void,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(số_nguyên,XQueryTree,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned số_nguyên* f))
SDL_X11_SYM(Bool,XSupportsLocale,(void))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,char** b,số_nguyên c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(void))
SDL_X11_SYM(số_nguyên,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(void,XDestroyRegion,(Region))
SDL_X11_SYM(void,XrmInitialize,(void))
SDL_X11_SYM(char*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(char *data))
SDL_X11_SYM(void,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, char* str_name, char* str_class, char **str_type_return, XrmValue *))
SDL_X11_SYM(số_nguyên,XGetPointerMapping,(Display *a, unsigned char *b, unsigned số_nguyên c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, số_nguyên c, số_nguyên d, số_nguyên e, số_nguyên f, số_nguyên g, số_nguyên h, số_nguyên *i))
SDL_X11_SYM(void, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(số_nguyên, XIBarrierReleasePointer,(Display* a,  số_nguyên b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, số_nguyên* b, số_nguyên* c))
SDL_X11_SYM(Status, XFixesSelectSelectionInput, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, số_nguyên* b, số_nguyên* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, số_nguyên* b, số_nguyên* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSyncValue b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSyncValue c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, số_nguyên* b, số_nguyên* c))
SDL_X11_SYM(số_nguyên, XTestFakeMotionEvent, (Display* a, số_nguyên b, số_nguyên c, số_nguyên d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(void,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,số_nguyên * b,số_nguyên * c,số_nguyên * d,số_nguyên * e, số_nguyên *f))
SDL_X11_SYM(KeySym,XkbKeycodeToKeysym,(Display* a, KeyCode b, unsigned số_nguyên c, unsigned số_nguyên d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned số_nguyên b, unsigned số_nguyên c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned số_nguyên b, unsigned số_nguyên c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned số_nguyên b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned số_nguyên b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned số_nguyên b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned số_nguyên b,unsigned số_nguyên c))
SDL_X11_SYM(void,XkbFreeClientMap,(XkbDescPtr a,unsigned số_nguyên b, Bool c))
SDL_X11_SYM(void,XkbFreeKeyboard,(XkbDescPtr a,unsigned số_nguyên b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(số_nguyên,Xutf8TextListToTextProperty,(Display* a,char** b,số_nguyên c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(số_nguyên,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,char* c,số_nguyên d,KeySym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(void,XDestroyIC,(XIC a))
SDL_X11_SYM(char*,XGetICValues,(XIC,...))
SDL_X11_SYM(char*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(số_nguyên, ...))
SDL_X11_SYM(void,XSetICFocus,(XIC a))
SDL_X11_SYM(void,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,struct _XrmHashBucketRec* b,char* c,char* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(char*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,struct _XrmHashBucketRec*,char*,char*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,struct _XrmHashBucketRec*,char*,char*,XIDProc,XPointer))
SDL_X11_SYM(void,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, số_nguyên e, số_nguyên f, _Xconst char *g, số_nguyên h))
SDL_X11_SYM(số_nguyên,Xutf8TextExtents,(XFontSet a, _Xconst char* b, số_nguyên c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(char*,XSetLocaleModifiers,(const char *a))
SDL_X11_SYM(char*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,số_nguyên e,số_nguyên f,số_nguyên g,số_nguyên h,unsigned số_nguyên i,unsigned số_nguyên j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,số_nguyên d, số_nguyên e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned số_nguyên c,số_nguyên d,char* e,XShmSegmentInfo* f,unsigned số_nguyên g,unsigned số_nguyên h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,char* c,XShmSegmentInfo* d, unsigned số_nguyên e, unsigned số_nguyên f, unsigned số_nguyên g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, số_nguyên *b, số_nguyên *c, Bool *d))
SDL_X11_SYM(số_nguyên,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(số_nguyên,_XData32,(Display *dpy,register _Xconst long *data,unsigned len))
SDL_X11_SYM(void,_XRead32,(Display *dpy,register long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(void,_SmtBufferOverflow,(Display *dpy,register smtDisplayPtr p))
SDL_X11_SYM(void,_SmtIpError,(Display *dpy,register smtDisplayPtr p,số_nguyên i))
SDL_X11_SYM(số_nguyên,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(số_nguyên,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(số_nguyên a,số_nguyên b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(số_nguyên a))
SDL_X11_SYM(void,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(void,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,const XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,const XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, const char *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,số_nguyên *major_version_return,số_nguyên *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,số_nguyên num_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,số_nguyên *num_screens))
SDL_X11_SYM(void,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,số_nguyên b,số_nguyên *c))
SDL_X11_SYM(void,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(số_nguyên,XISelectEvents,(Display *a,Window b,XIEventMask *c,số_nguyên d))
SDL_X11_SYM(số_nguyên,XIGrabTouchBegin,(Display *a,số_nguyên b,Window c,số_nguyên d,XIEventMask *e,số_nguyên f,XIGrabModifiers *g))
SDL_X11_SYM(số_nguyên,XIUngrabTouchBegin, (Display *a,số_nguyên b,Window c, số_nguyên d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,số_nguyên *b,số_nguyên *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,số_nguyên *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,số_nguyên *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,số_nguyên b,Window c,Window d,double e,double f,số_nguyên g,số_nguyên h,double i,double j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,số_nguyên b,Atom c,long d,long e,Bool f, Atom g, Atom *h, số_nguyên *i, unsigned long *j, unsigned long *k, unsigned char **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,số_nguyên *major_versionp,số_nguyên *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,số_nguyên *event_base_return,số_nguyên *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,số_nguyên sizeID,số_nguyên *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,số_nguyên *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,số_nguyên size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(void,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(void,XRRSetScreenSize,(Display *dpy, Window window,số_nguyên width, số_nguyên height,số_nguyên mmWidth, số_nguyên mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,số_nguyên *minWidth, số_nguyên *minHeight, số_nguyên *maxWidth, số_nguyên *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(void,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(void,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(void,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, số_nguyên x, số_nguyên y, RRMode mode, Rotation rotation, RROutput *outputs, số_nguyên noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, số_nguyên *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(số_nguyên,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, số_nguyên *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned char **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(void,XRRSelectInput,(Display *dpy, Window window, số_nguyên mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,số_nguyên *event_base,số_nguyên *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,số_nguyên *major_versionp,số_nguyên *minor_versionp))
SDL_X11_SYM(void,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(void,XShapeCombineMask,(Display *dpy,Window dest,số_nguyên dest_kind,số_nguyên x_off,số_nguyên y_off,Pixmap src,số_nguyên op))
SDL_X11_SYM(void,XShapeCombineRegion,(Display *a,Window b,số_nguyên c,số_nguyên d,số_nguyên e,Region f,số_nguyên g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
