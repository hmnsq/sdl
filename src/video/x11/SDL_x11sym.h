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

#اگر_تعریف_نشده SDL_X11_MODULE
#تعریف_کن SDL_X11_MODULE(modname)
#پایان_اگر

#اگر_تعریف_نشده SDL_X11_SYM
#تعریف_کن SDL_X11_SYM(rc, fn, params)
#پایان_اگر

SDL_X11_MODULE(BASEXLIB)
SDL_X11_SYM(XSizeHints*,XAlloc_اندازه_Hints,(فراغ))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(فراغ))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(فراغ))
SDL_X11_SYM(صحيح,XChange_اشاره_گر_Control,(Display* a,Bool b,Bool c,صحيح d,صحيح e,صحيح f))
SDL_X11_SYM(صحيح,XChangeProperty,(Display* a,پنجره_2 b,Atom c,Atom d,صحيح e,صحيح f,_Xconst بیعلامت حرف* g,صحيح h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(صحيح,XClear_پنجره,(Display* a,پنجره_2 b))
SDL_X11_SYM(صحيح,XCloseDisplay,(Display* a))
SDL_X11_SYM(صحيح,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,پنجره_2 e,زمان_2 f))
SDL_X11_SYM(Pixmap,XCreate_Bitmap_From_داده,(Display *dpy,Drawable d,_Xconst حرف *داده,بیعلامت صحيح عرض,بیعلامت صحيح ارتفاع))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,پنجره_2 b,Visual* c,صحيح d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,بیعلامت صحيح f,بیعلامت صحيح g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,بیعلامت صحيح d,بیعلامت صحيح e,بیعلامت صحيح f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,بیعلامت صحيح b))
SDL_X11_SYM(XFont_مجموعه,XCreate_Font_مجموعه,(Display* a, _Xconst حرف* b, حرف*** c, صحيح* d, حرف** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,بیعلامت دراز c,XGCValues* d))
SDL_X11_SYM(فراغ,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(وضعیت_2,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,بیعلامت صحيح c,صحيح d,صحيح e,حرف* f,بیعلامت صحيح g,بیعلامت صحيح h,صحيح i,صحيح j))
SDL_X11_SYM(پنجره_2,XCreate_پنجره,(Display* a,پنجره_2 b,صحيح c,صحيح d,بیعلامت صحيح e,بیعلامت صحيح f,بیعلامت صحيح g,صحيح h,بیعلامت صحيح i,Visual* j,بیعلامت دراز k,XSet_پنجره_صفات* l))
SDL_X11_SYM(فراغ,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, صحيح e, صحيح f, بیعلامت صحيح g, بیعلامت صحيح h, صحيح i, صحيح j))
SDL_X11_SYM(صحيح,XDefineCursor,(Display* a,پنجره_2 b,Cursor c))
SDL_X11_SYM(صحيح,XDeleteProperty,(Display* a,پنجره_2 b,Atom c))
SDL_X11_SYM(صحيح,XDestroy_پنجره,(Display* a,پنجره_2 b))
SDL_X11_SYM(صحيح,XDisplayKeycodes,(Display* a,صحيح* b,صحيح* c))
SDL_X11_SYM(صحيح,XDrawRectangle,(Display* a,Drawable b,GC c,صحيح d,صحيح e,بیعلامت صحيح f,بیعلامت صحيح g))
SDL_X11_SYM(صحيح,XFonts_از_Font_مجموعه,(XFont_مجموعه a,XFontStruct ***b,حرف ***c))
SDL_X11_SYM(صحيح,XFillArc,(Display* a,Drawable b,GC c,صحيح d,صحيح e,بیعلامت صحيح f,بیعلامت صحيح g, صحيح h, صحيح i))
SDL_X11_SYM(حرف*,XDisplayName,(_Xconst حرف* a))
SDL_X11_SYM(صحيح,XDrawString,(Display* a,Drawable b,GC c,صحيح d,صحيح e,_Xconst حرف* f,صحيح g))
SDL_X11_SYM(صحيح,XEventsQueued,(Display* a,صحيح b))
SDL_X11_SYM(صحيح,XFillRectangle,(Display* a,Drawable b,GC c,صحيح d,صحيح e,بیعلامت صحيح f,بیعلامت صحيح g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,پنجره_2 w))
SDL_X11_SYM(صحيح,XFlush,(Display* a))
SDL_X11_SYM(صحيح,XFree,(فراغ*a))
SDL_X11_SYM(صحيح,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(فراغ,XFree_Font_مجموعه,(Display* a, XFont_مجموعه b))
SDL_X11_SYM(صحيح,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(صحيح,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(صحيح,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(صحيح,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(صحيح,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(فراغ,XFreeStringList,(حرف** a))
SDL_X11_SYM(حرف*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(صحيح,XGet_درون_داد_Focus,(Display *a,پنجره_2 *b,صحيح *c))
SDL_X11_SYM(کلید_Sym*,XGetKeyboardMapping,(Display *a, کلید_کد_2 b, صحيح c, صحيح *d))
SDL_X11_SYM(صحيح,XGet_Error_Database_متن,(Display* a,_Xconst حرف* b,_Xconst حرف* c,_Xconst حرف* d,حرف* e,صحيح f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(صحيح,XGet_اشاره_گر_Control,(Display* a,صحيح* b,صحيح* c,صحيح* d))
SDL_X11_SYM(پنجره_2,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,دراز b,XVisualInfo* c,صحيح* d))
SDL_X11_SYM(وضعیت_2,XGet_پنجره_صفات,(Display* a,پنجره_2 b,XWindow_صفات* c))
SDL_X11_SYM(صحيح,XGet_پنجره_Property,(Display* a,پنجره_2 b,Atom c,دراز d,دراز e,Bool f,Atom g,Atom* h,صحيح* i,بیعلامت دراز* j,بیعلامت دراز *k,بیعلامت حرف **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,پنجره_2 b))
SDL_X11_SYM(وضعیت_2,XGetWMNormalHints,(Display *a,پنجره_2 b, XSizeHints *c, دراز *d))
SDL_X11_SYM(صحيح,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(صحيح,XGrabKeyboard,(Display* a,پنجره_2 b,Bool c,صحيح d,صحيح e,زمان_2 f))
SDL_X11_SYM(صحيح,XGrab_اشاره_گر,(Display* a,پنجره_2 b,Bool c,بیعلامت صحيح d,صحيح e,صحيح f,پنجره_2 g,Cursor h,زمان_2 i))
SDL_X11_SYM(صحيح,XGrabServer,(Display* a))
SDL_X11_SYM(وضعیت_2,XIconify_پنجره,(Display* a,پنجره_2 b,صحيح c))
SDL_X11_SYM(کلید_کد_2,XKeysym_مقصد_Keycode,(Display* a,کلید_Sym b))
SDL_X11_SYM(حرف*,XKeysym_مقصد_String,(کلید_Sym a))
SDL_X11_SYM(صحيح,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst حرف* b,Bool c))
SDL_X11_SYM(XPixmap_Format_مقادیر*,XListPixmapFormats,(Display* a,صحيح* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst حرف* b))
SDL_X11_SYM(کلید_Sym,XLookupKeysym,(XKeyEvent* a,صحيح b))
SDL_X11_SYM(صحيح,XLookupString,(XKeyEvent* a,حرف* b,صحيح c,کلید_Sym* d,XCompose_وضعیت* e))
SDL_X11_SYM(صحيح,XMapRaised,(Display* a,پنجره_2 b))
SDL_X11_SYM(وضعیت_2,XMatchVisualInfo,(Display* a,صحيح b,صحيح c,صحيح d,XVisualInfo* e))
SDL_X11_SYM(صحيح,XMissingExtension,(Display* a,_Xconst حرف* b))
SDL_X11_SYM(صحيح,XMove_پنجره,(Display* a,پنجره_2 b,صحيح c,صحيح d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst حرف* a))
SDL_X11_SYM(وضعیت_2,XInit_نخها,(فراغ))
SDL_X11_SYM(صحيح,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(صحيح,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,صحيح c, صحيح d,بیعلامت صحيح e,بیعلامت صحيح f,بیعلامت دراز g,صحيح h))
SDL_X11_SYM(صحيح,XPutImage,(Display* a,Drawable b,GC c,XImage* d,صحيح e,صحيح f,صحيح g,صحيح h,بیعلامت صحيح i,بیعلامت صحيح j))
SDL_X11_SYM(صحيح,XQueryKeymap,(Display* a,حرف b[32]))
SDL_X11_SYM(Bool,XQuery_اشاره_گر,(Display* a,پنجره_2 b,پنجره_2* c,پنجره_2* d,صحيح* e,صحيح* f,صحيح* g,صحيح* h,بیعلامت صحيح* i))
SDL_X11_SYM(صحيح,XRaise_پنجره,(Display* a,پنجره_2 b))
SDL_X11_SYM(صحيح,XReparent_پنجره,(Display* a,پنجره_2 b,پنجره_2 c,صحيح d,صحيح e))
SDL_X11_SYM(صحيح,XResetScreenSaver,(Display* a))
SDL_X11_SYM(صحيح,XResize_پنجره,(Display* a,پنجره_2 b,بیعلامت صحيح c,بیعلامت صحيح d))
SDL_X11_SYM(صحيح,XScreen_عدد_از_Screen,(Screen* a))
SDL_X11_SYM(صحيح,XSelect_درون_داد,(Display* a,پنجره_2 b,دراز c))
SDL_X11_SYM(وضعیت_2,XSendEvent,(Display* a,پنجره_2 b,Bool c,دراز d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(صحيح,XSetForeground,(Display* a,GC b,بیعلامت دراز c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(صحيح,XSet_درون_داد_Focus,(Display *a,پنجره_2 b,صحيح c,زمان_2 d))
SDL_X11_SYM(صحيح,XSetSelectionOwner,(Display* a,Atom b,پنجره_2 c,زمان_2 d))
SDL_X11_SYM(صحيح,XSetTransientForHint,(Display* a,پنجره_2 b,پنجره_2 c))
SDL_X11_SYM(فراغ,XSet_متن_Property,(Display* a,پنجره_2 b,XTextProperty* c,Atom d))
SDL_X11_SYM(صحيح,XSet_پنجره_Background,(Display* a,پنجره_2 b,بیعلامت دراز c))
SDL_X11_SYM(فراغ,XSetWMHints,(Display* a,پنجره_2 b,XWMHints* c))
SDL_X11_SYM(فراغ,XSetWMNormalHints,(Display* a,پنجره_2 b,XSizeHints* c))
SDL_X11_SYM(فراغ,XSetWMProperties,(Display* a,پنجره_2 b,XTextProperty* c,XTextProperty* d,حرف** e,صحيح f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(وضعیت_2,XSetWMProtocols,(Display* a,پنجره_2 b,Atom* c,صحيح d))
SDL_X11_SYM(صحيح,XStoreColors,(Display* a,Colormap b,XColor* c,صحيح d))
SDL_X11_SYM(صحيح,XStoreName,(Display* a,پنجره_2 b,_Xconst حرف* c))
SDL_X11_SYM(وضعیت_2,XString_List_مقصد_متن_Property,(حرف** a,صحيح b,XTextProperty* c))
SDL_X11_SYM(صحيح,XSync,(Display* a,Bool b))
SDL_X11_SYM(صحيح,XTextExtents,(XFontStruct* a,_Xconst حرف* b,صحيح c,صحيح* d,صحيح* e,صحيح* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,پنجره_2 b,پنجره_2 c,صحيح d,صحيح e,صحيح* f,صحيح* g,پنجره_2* h))
SDL_X11_SYM(صحيح,XUndefineCursor,(Display* a,پنجره_2 b))
SDL_X11_SYM(صحيح,XUngrabKeyboard,(Display* a,زمان_2 b))
SDL_X11_SYM(صحيح,XUngrab_اشاره_گر,(Display* a,زمان_2 b))
SDL_X11_SYM(صحيح,XUngrabServer,(Display* a))
SDL_X11_SYM(صحيح,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(صحيح,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(صحيح,XWarp_اشاره_گر,(Display* a,پنجره_2 b,پنجره_2 c,صحيح d,صحيح e,بیعلامت صحيح f,بیعلامت صحيح g,صحيح h,صحيح i))
SDL_X11_SYM(صحيح,XWindowEvent,(Display* a,پنجره_2 b,دراز c,XEvent* d))
SDL_X11_SYM(وضعیت_2,XWithdraw_پنجره,(Display* a,پنجره_2 b,صحيح c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(حرف*,XGetDefault,(Display* a,_Xconst حرف* b, _Xconst حرف* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst حرف* b,صحيح* c,صحيح* d,صحيح* e))
SDL_X11_SYM(حرف *,XDisplayString,(Display* a))
SDL_X11_SYM(صحيح,XGet_Error_متن,(Display* a,صحيح b,حرف* c,صحيح d))
SDL_X11_SYM(فراغ,XEat_داده,(Display* a,بیعلامت دراز b))
SDL_X11_SYM(فراغ,_XFlush,(Display* a))
SDL_X11_SYM(فراغ,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(صحيح,_XRead,(Display* a,حرف* b,دراز c))
SDL_X11_SYM(فراغ,_XReadPad,(Display* a,حرف* b,دراز c))
SDL_X11_SYM(فراغ,_XSend,(Display* a,_Xconst حرف* b,دراز c))
SDL_X11_SYM(وضعیت_2,_XReply,(Display* a,x_پاسخ* b,صحيح c,Bool d))
SDL_X11_SYM(بیعلامت دراز,XSet_آخرین_Request_Read,(Display* a,x_Generic_پاسخ* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESet_Wire_مقصد_Event_Ret_Type,XESet_Wire_مقصد_Event,(Display* a,صحيح b,SDL_X11_XESet_Wire_مقصد_Event_Ret_Type c))
SDL_X11_SYM(SDL_X11_XESet_Event_مقصد_Wire_Ret_Type,XESet_Event_مقصد_Wire,(Display* a,صحيح b,SDL_X11_XESet_Event_مقصد_Wire_Ret_Type c))
SDL_X11_SYM(فراغ,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(صحيح,XQuery_درخت,(Display* a,پنجره_2 b,پنجره_2* c,پنجره_2* d,پنجره_2** e,بیعلامت صحيح* f))
SDL_X11_SYM(Bool,XSupportsLocale,(فراغ))
SDL_X11_SYM(وضعیت_2,Xmb_متن_List_مقصد_متن_Property,(Display* a,حرف** b,صحيح c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(فراغ))
SDL_X11_SYM(صحيح,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(فراغ,XDestroyRegion,(Region))
SDL_X11_SYM(فراغ,XrmInitialize,(فراغ))
SDL_X11_SYM(حرف*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(حرف *داده))
SDL_X11_SYM(فراغ,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, حرف* str_name, حرف* str_class, حرف **str_type_return, Xrm_مقدار *))
SDL_X11_SYM(صحيح,XGet_اشاره_گر_Mapping,(Display *a, بیعلامت حرف *b, بیعلامت صحيح c))

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(اشاره_گر_Barrier, XFixes_Create_اشاره_گر_Barrier, (Display* a, پنجره_2 b, صحيح c, صحيح d, صحيح e, صحيح f, صحيح g, صحيح h, صحيح *i))
SDL_X11_SYM(فراغ, XFixes_Destroy_اشاره_گر_Barrier, (Display* a, اشاره_گر_Barrier b))
SDL_X11_SYM(صحيح, XIBarrier_Release_اشاره_گر,(Display* a,  صحيح b, اشاره_گر_Barrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(وضعیت_2, XFixes_Query_نسخه,(Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(وضعیت_2, XFixes_Select_Selection_درون_داد, (Display* a, پنجره_2 b, Atom c, بیعلامت دراز d))
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(وضعیت_2, XSyncQueryExtension, (Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(وضعیت_2, XSyncInitialize, (Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_مقدار b))
SDL_X11_SYM(وضعیت_2, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(وضعیت_2, XSync_مجموعه_Counter, (Display* a, XSyncCounter b, XSync_مقدار c))
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(وضعیت_2, XTestQueryExtension, (Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(صحيح, XTestFakeMotionEvent, (Display* a, صحيح b, صحيح c, صحيح d, بیعلامت دراز e))
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGet_Event_داده,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(فراغ,XFree_Event_داده,(Display* a,XGenericEventCookie* b))
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,صحيح * b,صحيح * c,صحيح * d,صحيح * e, صحيح *f))
SDL_X11_SYM(کلید_Sym,Xkb_Keycode_مقصد_Keysym,(Display* a, کلید_کد_2 b, بیعلامت صحيح c, بیعلامت صحيح d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, بیعلامت صحيح b, بیعلامت صحيح c, بیعلامت دراز d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, بیعلامت صحيح b, بیعلامت صحيح c, بیعلامت دراز d, بیعلامت دراز e))
SDL_X11_SYM(وضعیت_2,Xkb_Get_نامها,(Display *a, بیعلامت صحيح b, XkbDescPtr c))
SDL_X11_SYM(وضعیت_2,XkbGetState,(Display* a,بیعلامت صحيح b,XkbStatePtr c))
SDL_X11_SYM(وضعیت_2,XkbGetUpdatedMap,(Display* a,بیعلامت صحيح b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,بیعلامت صحيح b,بیعلامت صحيح c))
SDL_X11_SYM(فراغ,XkbFreeClientMap,(XkbDescPtr a,بیعلامت صحيح b, Bool c))
SDL_X11_SYM(فراغ,XkbFreeKeyboard,(XkbDescPtr a,بیعلامت صحيح b, Bool c))
SDL_X11_SYM(وضعیت_2,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,Xkb_مجموعه_Detectable_Auto_Repeat,(Display* a, Bool b, Bool* c))
#پایان_اگر

#اگر_تعریف_شده X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(صحيح,Xutf8_متن_List_مقصد_متن_Property,(Display* a,حرف** b,صحيح c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(صحيح,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,حرف* c,صحيح d,کلید_Sym* e,وضعیت_2* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(فراغ,XDestroyIC,(XIC a))
SDL_X11_SYM(حرف*,XGetICValues,(XIC,...))
SDL_X11_SYM(حرف*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(صحيح, ...))
SDL_X11_SYM(فراغ,XSetICFocus,(XIC a))
SDL_X11_SYM(فراغ,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,بنية Xrm_Hash_سطل_Rec* b,حرف* c,حرف* d))
SDL_X11_SYM(وضعیت_2,XCloseIM,(XIM a))
SDL_X11_SYM(حرف*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,بنية Xrm_Hash_سطل_Rec*,حرف*,حرف*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,بنية Xrm_Hash_سطل_Rec*,حرف*,حرف*,XIDProc,XPointer))
SDL_X11_SYM(فراغ,Xutf8DrawString,(Display *a, Drawable b, XFont_مجموعه c, GC d, صحيح e, صحيح f, _Xconst حرف *g, صحيح h))
SDL_X11_SYM(صحيح,Xutf8_متن_Extents,(XFont_مجموعه a, _Xconst حرف* b, صحيح c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(حرف*,XSetLocaleModifiers,(ثابت حرف *a))
SDL_X11_SYM(حرف*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFont_مجموعه_Extents*,XExtents_از_Font_مجموعه,(XFont_مجموعه a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFont_مجموعه a))
#پایان_اگر


#اگر_تعریف_نشده NO_SHARED_حافظه
SDL_X11_MODULE(SHM)
SDL_X11_SYM(وضعیت_2,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(وضعیت_2,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(وضعیت_2,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,صحيح e,صحيح f,صحيح g,صحيح h,بیعلامت صحيح i,بیعلامت صحيح j,Bool k))
SDL_X11_SYM(وضعیت_2,XShmGetImage,(Display* a,Drawable b,XImage *c,صحيح d, صحيح e, بیعلامت دراز f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,بیعلامت صحيح c,صحيح d,حرف* e,XShmSegmentInfo* f,بیعلامت صحيح g,بیعلامت صحيح h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,حرف* c,XShmSegmentInfo* d, بیعلامت صحيح e, بیعلامت صحيح f, بیعلامت صحيح g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(وضعیت_2,XShm_Query_نسخه,(Display* a, صحيح *b, صحيح *c, Bool *d))
SDL_X11_SYM(صحيح,XShmPixmapFormat,(Display* a))
#پایان_اگر

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#اگر_تعریف_شده LONG64
SDL_X11_MODULE(IO_32_بیت)
SDL_X11_SYM(صحيح,_XData32,(Display *dpy,سجل _Xconst دراز *داده,بیعلامت len))
SDL_X11_SYM(فراغ,_XRead32,(Display *dpy,سجل دراز *داده,دراز len))
#پایان_اگر

/*
 * These only show up on some variants of Unix.
 */
#اگر_تعریف_شده SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_مدخل_POINTS)
SDL_X11_SYM(فراغ,Smt_میانگیر_سرریز,(Display *dpy,سجل smtDisplayPtr p))
SDL_X11_SYM(فراغ,_SmtIpError,(Display *dpy,سجل smtDisplayPtr p,صحيح i))
SDL_X11_SYM(صحيح,ip_Allocate_داده,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(صحيح,ip_Unallocate_And_Send_داده,(ChannelPtr a,IPCard b))
#پایان_اگر

// XCursor support
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(صحيح a,صحيح b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(صحيح a))
SDL_X11_SYM(فراغ,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(فراغ,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,Xcursor_Image_بارگیری_Cursor,(Display *a,ثابت XcursorImage *b))
SDL_X11_SYM(Cursor,Xcursor_Images_بارگیری_Cursor,(Display *a,ثابت XcursorImages *b))
SDL_X11_SYM(Cursor,Xcursor_Library_بارگیری_Cursor,(Display *a, ثابت حرف *b))
#پایان_اگر

// Xdbe support
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(وضعیت_2,XdbeQueryExtension,(Display *dpy,صحيح *major_نسخه_return,صحيح *minor_نسخه_return))
SDL_X11_SYM(Xdbe_پشت_میانگیر,Xdbe_Allocate_پشت_میانگیر_Name,(Display *dpy,پنجره_2 پنجره,Xdbe_جابجا_Action جابجا_action))
SDL_X11_SYM(وضعیت_2,Xdbe_Deallocate_پشت_میانگیر_Name,(Display *dpy,Xdbe_پشت_میانگیر میانگیر_2))
SDL_X11_SYM(وضعیت_2,Xdbe_جابجا_Buffers,(Display *dpy,Xdbe_جابجا_Info *جابجا_info,صحيح رقم_windows))
SDL_X11_SYM(وضعیت_2,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(وضعیت_2,Xdbe_انتها_Idiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,صحيح *رقم_screens))
SDL_X11_SYM(فراغ,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(Xdbe_پشت_میانگیر_صفات*,Xdbe_Get_پشت_میانگیر_صفات,(Display *dpy,Xdbe_پشت_میانگیر میانگیر_2))
#پایان_اگر

// XInput2 support for multiple mice, tablets, etc.
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,صحيح b,صحيح *c))
SDL_X11_SYM(فراغ,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(صحيح,XISelectEvents,(Display *a,پنجره_2 b,XIEvent_ماسک *c,صحيح d))
SDL_X11_SYM(صحيح,XIGrabTouchBegin,(Display *a,صحيح b,پنجره_2 c,صحيح d,XIEvent_ماسک *e,صحيح f,XIGrabModifiers *g))
SDL_X11_SYM(صحيح,XIUngrabTouchBegin, (Display *a,صحيح b,پنجره_2 c, صحيح d,XIGrabModifiers *e))
SDL_X11_SYM(وضعیت_2,XIQuery_نسخه,(Display *a,صحيح *b,صحيح *c))
SDL_X11_SYM(XIEvent_ماسک*,XIGetSelectedEvents,(Display *a,پنجره_2 b,صحيح *c))
SDL_X11_SYM(Bool,XIGet_Client_اشاره_گر,(Display *a,پنجره_2 b,صحيح *c))
SDL_X11_SYM(Bool,XIWarp_اشاره_گر,(Display *a,صحيح b,پنجره_2 c,پنجره_2 d,مزدوج e,مزدوج f,صحيح g,صحيح h,مزدوج i,مزدوج j))
SDL_X11_SYM(وضعیت_2,XIGetProperty,(Display *a,صحيح b,Atom c,دراز d,دراز e,Bool f, Atom g, Atom *h, صحيح *i, بیعلامت دراز *j, بیعلامت دراز *k, بیعلامت حرف **l))
#پایان_اگر

// XRandR support
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(وضعیت_2,XRRQuery_نسخه,(Display *dpy,صحيح *major_versionp,صحيح *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,صحيح *event_پایه_return,صحيح *error_پایه_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(اندازه_ID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(کوتاه,XRRConfig_Current_نرخ,(XRRScreenConfiguration *config))
SDL_X11_SYM(کوتاه *,XRRConfigRates,(XRRScreenConfiguration *config,صحيح اندازه_ID_2,صحيح *nrates))
SDL_X11_SYM(XRRScreen_اندازه *,XRRConfigSizes,(XRRScreenConfiguration *config,صحيح *nsizes))
SDL_X11_SYM(وضعیت_2,XRRSet_Screen_Config_And_نرخ,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,صحيح اندازه_شاخص,Rotation rotation,کوتاه نرخ,زمان_2 timestamp))
SDL_X11_SYM(فراغ,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(فراغ,XRRSet_Screen_اندازه,(Display *dpy, پنجره_2 پنجره,صحيح عرض, صحيح ارتفاع,صحيح mm_عرض_2, صحيح mm_ارتفاع_2))
SDL_X11_SYM(وضعیت_2,XRRGet_Screen_اندازه_Range,(Display *dpy, پنجره_2 پنجره,صحيح *min_عرض, صحيح *min_ارتفاع, صحيح *max_عرض, صحيح *max_ارتفاع))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, پنجره_2 پنجره))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, پنجره_2 پنجره))
SDL_X11_SYM(فراغ,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(فراغ,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(فراغ,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(وضعیت_2,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, زمان_2 timestamp, صحيح x, صحيح y, RRMode نما, Rotation rotation, RROutput *outputs, صحيح noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, صحيح *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(صحيح,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, دراز جابه_جایی_2, دراز درازی, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, صحيح *actual_format, بیعلامت دراز *nitems, بیعلامت دراز *بایتها_after, بیعلامت حرف **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,پنجره_2 پنجره))
SDL_X11_SYM(فراغ,XRRSelect_درون_داد,(Display *dpy, پنجره_2 پنجره, صحيح ماسک))
SDL_X11_SYM(وضعیت_2,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtc_Transform_صفات **صفات))
#پایان_اگر

// MIT-SCREEN-SAVER support
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,صحيح *event_پایه_2,صحيح *error_پایه_2))
SDL_X11_SYM(وضعیت_2,XScreen_Saver_Query_نسخه,(Display *dpy,صحيح *major_versionp,صحيح *minor_versionp))
SDL_X11_SYM(فراغ,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(فراغ,XShape_Combine_ماسک,(Display *dpy,پنجره_2 dest,صحيح dest_نوع,صحيح x_off,صحيح y_off,Pixmap src,صحيح op))
SDL_X11_SYM(فراغ,XShapeCombineRegion,(Display *a,پنجره_2 b,صحيح c,صحيح d,صحيح e,Region f,صحيح g))
#پایان_اگر

#لغو_تعریف SDL_X11_MODULE
#لغو_تعریف SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
