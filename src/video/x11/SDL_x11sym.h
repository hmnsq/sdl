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

#جے_بنا_تعریف SDL_X11_MODULE
#تعریف_کرو SDL_X11_MODULE(modname)
#جے_انت

#جے_بنا_تعریف SDL_X11_SYM
#تعریف_کرو SDL_X11_SYM(rc, fn, params)
#جے_انت

SDL_X11_MODULE(BASEXLIB)
SDL_X11_SYM(XSizeHints*,XAlloc_ناپ_Hints,(فراغ))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(فراغ))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(فراغ))
SDL_X11_SYM(صحيح,XChange_اشارہ_گر_Control,(Display* a,Bool b,Bool c,صحيح d,صحيح e,صحيح f))
SDL_X11_SYM(صحيح,XChangeProperty,(Display* a,کھڑکی_2 b,Atom c,Atom d,صحيح e,صحيح f,_Xconst بنانشانی حرف* g,صحيح h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(صحيح,XClear_کھڑکی,(Display* a,کھڑکی_2 b))
SDL_X11_SYM(صحيح,XCloseDisplay,(Display* a))
SDL_X11_SYM(صحيح,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,کھڑکی_2 e,ویلا_2 f))
SDL_X11_SYM(Pixmap,XCreate_Bitmap_From_انکڑے,(Display *dpy,Drawable d,_Xconst حرف *انکڑے,بنانشانی صحيح چوڑائی,بنانشانی صحيح اچائی))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,کھڑکی_2 b,Visual* c,صحيح d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,بنانشانی صحيح f,بنانشانی صحيح g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,بنانشانی صحيح d,بنانشانی صحيح e,بنانشانی صحيح f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,بنانشانی صحيح b))
SDL_X11_SYM(XFont_سیٹ,XCreate_Font_سیٹ,(Display* a, _Xconst حرف* b, حرف*** c, صحيح* d, حرف** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,بنانشانی لما c,XGCValues* d))
SDL_X11_SYM(فراغ,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(حالت_2,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,بنانشانی صحيح c,صحيح d,صحيح e,حرف* f,بنانشانی صحيح g,بنانشانی صحيح h,صحيح i,صحيح j))
SDL_X11_SYM(کھڑکی_2,XCreate_کھڑکی,(Display* a,کھڑکی_2 b,صحيح c,صحيح d,بنانشانی صحيح e,بنانشانی صحيح f,بنانشانی صحيح g,صحيح h,بنانشانی صحيح i,Visual* j,بنانشانی لما k,XSet_کھڑکی_گن* l))
SDL_X11_SYM(فراغ,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, صحيح e, صحيح f, بنانشانی صحيح g, بنانشانی صحيح h, صحيح i, صحيح j))
SDL_X11_SYM(صحيح,XDefineCursor,(Display* a,کھڑکی_2 b,Cursor c))
SDL_X11_SYM(صحيح,XDeleteProperty,(Display* a,کھڑکی_2 b,Atom c))
SDL_X11_SYM(صحيح,XDestroy_کھڑکی,(Display* a,کھڑکی_2 b))
SDL_X11_SYM(صحيح,XDisplayKeycodes,(Display* a,صحيح* b,صحيح* c))
SDL_X11_SYM(صحيح,XDrawRectangle,(Display* a,Drawable b,GC c,صحيح d,صحيح e,بنانشانی صحيح f,بنانشانی صحيح g))
SDL_X11_SYM(صحيح,XFonts_دا_Font_سیٹ,(XFont_سیٹ a,XFontStruct ***b,حرف ***c))
SDL_X11_SYM(صحيح,XFillArc,(Display* a,Drawable b,GC c,صحيح d,صحيح e,بنانشانی صحيح f,بنانشانی صحيح g, صحيح h, صحيح i))
SDL_X11_SYM(حرف*,XDisplayName,(_Xconst حرف* a))
SDL_X11_SYM(صحيح,XDrawString,(Display* a,Drawable b,GC c,صحيح d,صحيح e,_Xconst حرف* f,صحيح g))
SDL_X11_SYM(صحيح,XEventsQueued,(Display* a,صحيح b))
SDL_X11_SYM(صحيح,XFillRectangle,(Display* a,Drawable b,GC c,صحيح d,صحيح e,بنانشانی صحيح f,بنانشانی صحيح g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,کھڑکی_2 w))
SDL_X11_SYM(صحيح,XFlush,(Display* a))
SDL_X11_SYM(صحيح,XFree,(فراغ*a))
SDL_X11_SYM(صحيح,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(فراغ,XFree_Font_سیٹ,(Display* a, XFont_سیٹ b))
SDL_X11_SYM(صحيح,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(صحيح,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(صحيح,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(صحيح,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(صحيح,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(فراغ,XFreeStringList,(حرف** a))
SDL_X11_SYM(حرف*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(صحيح,XGet_داخلہ_Focus,(Display *a,کھڑکی_2 *b,صحيح *c))
SDL_X11_SYM(کلید_Sym*,XGetKeyboardMapping,(Display *a, کلید_کوڈ_2 b, صحيح c, صحيح *d))
SDL_X11_SYM(صحيح,XGet_Error_Database_متن,(Display* a,_Xconst حرف* b,_Xconst حرف* c,_Xconst حرف* d,حرف* e,صحيح f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(صحيح,XGet_اشارہ_گر_Control,(Display* a,صحيح* b,صحيح* c,صحيح* d))
SDL_X11_SYM(کھڑکی_2,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,لما b,XVisualInfo* c,صحيح* d))
SDL_X11_SYM(حالت_2,XGet_کھڑکی_گن,(Display* a,کھڑکی_2 b,XWindow_گن* c))
SDL_X11_SYM(صحيح,XGet_کھڑکی_Property,(Display* a,کھڑکی_2 b,Atom c,لما d,لما e,Bool f,Atom g,Atom* h,صحيح* i,بنانشانی لما* j,بنانشانی لما *k,بنانشانی حرف **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,کھڑکی_2 b))
SDL_X11_SYM(حالت_2,XGetWMNormalHints,(Display *a,کھڑکی_2 b, XSizeHints *c, لما *d))
SDL_X11_SYM(صحيح,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(صحيح,XGrabKeyboard,(Display* a,کھڑکی_2 b,Bool c,صحيح d,صحيح e,ویلا_2 f))
SDL_X11_SYM(صحيح,XGrab_اشارہ_گر,(Display* a,کھڑکی_2 b,Bool c,بنانشانی صحيح d,صحيح e,صحيح f,کھڑکی_2 g,Cursor h,ویلا_2 i))
SDL_X11_SYM(صحيح,XGrabServer,(Display* a))
SDL_X11_SYM(حالت_2,XIconify_کھڑکی,(Display* a,کھڑکی_2 b,صحيح c))
SDL_X11_SYM(کلید_کوڈ_2,XKeysym_منزل_Keycode,(Display* a,کلید_Sym b))
SDL_X11_SYM(حرف*,XKeysym_منزل_String,(کلید_Sym a))
SDL_X11_SYM(صحيح,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst حرف* b,Bool c))
SDL_X11_SYM(XPixmap_Format_اقدار*,XListPixmapFormats,(Display* a,صحيح* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst حرف* b))
SDL_X11_SYM(کلید_Sym,XLookupKeysym,(XKeyEvent* a,صحيح b))
SDL_X11_SYM(صحيح,XLookupString,(XKeyEvent* a,حرف* b,صحيح c,کلید_Sym* d,XCompose_حالت* e))
SDL_X11_SYM(صحيح,XMapRaised,(Display* a,کھڑکی_2 b))
SDL_X11_SYM(حالت_2,XMatchVisualInfo,(Display* a,صحيح b,صحيح c,صحيح d,XVisualInfo* e))
SDL_X11_SYM(صحيح,XMissingExtension,(Display* a,_Xconst حرف* b))
SDL_X11_SYM(صحيح,XMove_کھڑکی,(Display* a,کھڑکی_2 b,صحيح c,صحيح d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst حرف* a))
SDL_X11_SYM(حالت_2,XInit_دھاگے,(فراغ))
SDL_X11_SYM(صحيح,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(صحيح,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,صحيح c, صحيح d,بنانشانی صحيح e,بنانشانی صحيح f,بنانشانی لما g,صحيح h))
SDL_X11_SYM(صحيح,XPutImage,(Display* a,Drawable b,GC c,XImage* d,صحيح e,صحيح f,صحيح g,صحيح h,بنانشانی صحيح i,بنانشانی صحيح j))
SDL_X11_SYM(صحيح,XQueryKeymap,(Display* a,حرف b[32]))
SDL_X11_SYM(Bool,XQuery_اشارہ_گر,(Display* a,کھڑکی_2 b,کھڑکی_2* c,کھڑکی_2* d,صحيح* e,صحيح* f,صحيح* g,صحيح* h,بنانشانی صحيح* i))
SDL_X11_SYM(صحيح,XRaise_کھڑکی,(Display* a,کھڑکی_2 b))
SDL_X11_SYM(صحيح,XReparent_کھڑکی,(Display* a,کھڑکی_2 b,کھڑکی_2 c,صحيح d,صحيح e))
SDL_X11_SYM(صحيح,XResetScreenSaver,(Display* a))
SDL_X11_SYM(صحيح,XResize_کھڑکی,(Display* a,کھڑکی_2 b,بنانشانی صحيح c,بنانشانی صحيح d))
SDL_X11_SYM(صحيح,XScreen_نمبر_دا_Screen,(Screen* a))
SDL_X11_SYM(صحيح,XSelect_داخلہ,(Display* a,کھڑکی_2 b,لما c))
SDL_X11_SYM(حالت_2,XSendEvent,(Display* a,کھڑکی_2 b,Bool c,لما d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(صحيح,XSetForeground,(Display* a,GC b,بنانشانی لما c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(صحيح,XSet_داخلہ_Focus,(Display *a,کھڑکی_2 b,صحيح c,ویلا_2 d))
SDL_X11_SYM(صحيح,XSetSelectionOwner,(Display* a,Atom b,کھڑکی_2 c,ویلا_2 d))
SDL_X11_SYM(صحيح,XSetTransientForHint,(Display* a,کھڑکی_2 b,کھڑکی_2 c))
SDL_X11_SYM(فراغ,XSet_متن_Property,(Display* a,کھڑکی_2 b,XTextProperty* c,Atom d))
SDL_X11_SYM(صحيح,XSet_کھڑکی_Background,(Display* a,کھڑکی_2 b,بنانشانی لما c))
SDL_X11_SYM(فراغ,XSetWMHints,(Display* a,کھڑکی_2 b,XWMHints* c))
SDL_X11_SYM(فراغ,XSetWMNormalHints,(Display* a,کھڑکی_2 b,XSizeHints* c))
SDL_X11_SYM(فراغ,XSetWMProperties,(Display* a,کھڑکی_2 b,XTextProperty* c,XTextProperty* d,حرف** e,صحيح f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(حالت_2,XSetWMProtocols,(Display* a,کھڑکی_2 b,Atom* c,صحيح d))
SDL_X11_SYM(صحيح,XStoreColors,(Display* a,Colormap b,XColor* c,صحيح d))
SDL_X11_SYM(صحيح,XStoreName,(Display* a,کھڑکی_2 b,_Xconst حرف* c))
SDL_X11_SYM(حالت_2,XString_List_منزل_متن_Property,(حرف** a,صحيح b,XTextProperty* c))
SDL_X11_SYM(صحيح,XSync,(Display* a,Bool b))
SDL_X11_SYM(صحيح,XTextExtents,(XFontStruct* a,_Xconst حرف* b,صحيح c,صحيح* d,صحيح* e,صحيح* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,کھڑکی_2 b,کھڑکی_2 c,صحيح d,صحيح e,صحيح* f,صحيح* g,کھڑکی_2* h))
SDL_X11_SYM(صحيح,XUndefineCursor,(Display* a,کھڑکی_2 b))
SDL_X11_SYM(صحيح,XUngrabKeyboard,(Display* a,ویلا_2 b))
SDL_X11_SYM(صحيح,XUngrab_اشارہ_گر,(Display* a,ویلا_2 b))
SDL_X11_SYM(صحيح,XUngrabServer,(Display* a))
SDL_X11_SYM(صحيح,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(صحيح,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(صحيح,XWarp_اشارہ_گر,(Display* a,کھڑکی_2 b,کھڑکی_2 c,صحيح d,صحيح e,بنانشانی صحيح f,بنانشانی صحيح g,صحيح h,صحيح i))
SDL_X11_SYM(صحيح,XWindowEvent,(Display* a,کھڑکی_2 b,لما c,XEvent* d))
SDL_X11_SYM(حالت_2,XWithdraw_کھڑکی,(Display* a,کھڑکی_2 b,صحيح c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(حرف*,XGetDefault,(Display* a,_Xconst حرف* b, _Xconst حرف* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst حرف* b,صحيح* c,صحيح* d,صحيح* e))
SDL_X11_SYM(حرف *,XDisplayString,(Display* a))
SDL_X11_SYM(صحيح,XGet_Error_متن,(Display* a,صحيح b,حرف* c,صحيح d))
SDL_X11_SYM(فراغ,XEat_انکڑے,(Display* a,بنانشانی لما b))
SDL_X11_SYM(فراغ,_XFlush,(Display* a))
SDL_X11_SYM(فراغ,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(صحيح,_XRead,(Display* a,حرف* b,لما c))
SDL_X11_SYM(فراغ,_XReadPad,(Display* a,حرف* b,لما c))
SDL_X11_SYM(فراغ,_XSend,(Display* a,_Xconst حرف* b,لما c))
SDL_X11_SYM(حالت_2,_XReply,(Display* a,x_جواب* b,صحيح c,Bool d))
SDL_X11_SYM(بنانشانی لما,XSet_آخری_Request_Read,(Display* a,x_Generic_جواب* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESet_Wire_منزل_Event_Ret_Type,XESet_Wire_منزل_Event,(Display* a,صحيح b,SDL_X11_XESet_Wire_منزل_Event_Ret_Type c))
SDL_X11_SYM(SDL_X11_XESet_Event_منزل_Wire_Ret_Type,XESet_Event_منزل_Wire,(Display* a,صحيح b,SDL_X11_XESet_Event_منزل_Wire_Ret_Type c))
SDL_X11_SYM(فراغ,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(صحيح,XQuery_درخت,(Display* a,کھڑکی_2 b,کھڑکی_2* c,کھڑکی_2* d,کھڑکی_2** e,بنانشانی صحيح* f))
SDL_X11_SYM(Bool,XSupportsLocale,(فراغ))
SDL_X11_SYM(حالت_2,Xmb_متن_List_منزل_متن_Property,(Display* a,حرف** b,صحيح c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(فراغ))
SDL_X11_SYM(صحيح,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(فراغ,XDestroyRegion,(Region))
SDL_X11_SYM(فراغ,XrmInitialize,(فراغ))
SDL_X11_SYM(حرف*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(حرف *انکڑے))
SDL_X11_SYM(فراغ,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, حرف* str_name, حرف* str_class, حرف **str_type_return, Xrm_قدر *))
SDL_X11_SYM(صحيح,XGet_اشارہ_گر_Mapping,(Display *a, بنانشانی حرف *b, بنانشانی صحيح c))

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(اشارہ_گر_Barrier, XFixes_Create_اشارہ_گر_Barrier, (Display* a, کھڑکی_2 b, صحيح c, صحيح d, صحيح e, صحيح f, صحيح g, صحيح h, صحيح *i))
SDL_X11_SYM(فراغ, XFixes_Destroy_اشارہ_گر_Barrier, (Display* a, اشارہ_گر_Barrier b))
SDL_X11_SYM(صحيح, XIBarrier_Release_اشارہ_گر,(Display* a,  صحيح b, اشارہ_گر_Barrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(حالت_2, XFixes_Query_نسخہ,(Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(حالت_2, XFixes_Select_Selection_داخلہ, (Display* a, کھڑکی_2 b, Atom c, بنانشانی لما d))
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(حالت_2, XSyncQueryExtension, (Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(حالت_2, XSyncInitialize, (Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_قدر b))
SDL_X11_SYM(حالت_2, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(حالت_2, XSync_سیٹ_Counter, (Display* a, XSyncCounter b, XSync_قدر c))
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(حالت_2, XTestQueryExtension, (Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(صحيح, XTestFakeMotionEvent, (Display* a, صحيح b, صحيح c, صحيح d, بنانشانی لما e))
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGet_Event_انکڑے,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(فراغ,XFree_Event_انکڑے,(Display* a,XGenericEventCookie* b))
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,صحيح * b,صحيح * c,صحيح * d,صحيح * e, صحيح *f))
SDL_X11_SYM(کلید_Sym,Xkb_Keycode_منزل_Keysym,(Display* a, کلید_کوڈ_2 b, بنانشانی صحيح c, بنانشانی صحيح d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, بنانشانی صحيح b, بنانشانی صحيح c, بنانشانی لما d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, بنانشانی صحيح b, بنانشانی صحيح c, بنانشانی لما d, بنانشانی لما e))
SDL_X11_SYM(حالت_2,Xkb_Get_ناں,(Display *a, بنانشانی صحيح b, XkbDescPtr c))
SDL_X11_SYM(حالت_2,XkbGetState,(Display* a,بنانشانی صحيح b,XkbStatePtr c))
SDL_X11_SYM(حالت_2,XkbGetUpdatedMap,(Display* a,بنانشانی صحيح b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,بنانشانی صحيح b,بنانشانی صحيح c))
SDL_X11_SYM(فراغ,XkbFreeClientMap,(XkbDescPtr a,بنانشانی صحيح b, Bool c))
SDL_X11_SYM(فراغ,XkbFreeKeyboard,(XkbDescPtr a,بنانشانی صحيح b, Bool c))
SDL_X11_SYM(حالت_2,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,Xkb_سیٹ_Detectable_Auto_Repeat,(Display* a, Bool b, Bool* c))
#جے_انت

#جے_تعریف_شدہ X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(صحيح,Xutf8_متن_List_منزل_متن_Property,(Display* a,حرف** b,صحيح c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(صحيح,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,حرف* c,صحيح d,کلید_Sym* e,حالت_2* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(فراغ,XDestroyIC,(XIC a))
SDL_X11_SYM(حرف*,XGetICValues,(XIC,...))
SDL_X11_SYM(حرف*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(صحيح, ...))
SDL_X11_SYM(فراغ,XSetICFocus,(XIC a))
SDL_X11_SYM(فراغ,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,بنية Xrm_Hash_بالٹی_Rec* b,حرف* c,حرف* d))
SDL_X11_SYM(حالت_2,XCloseIM,(XIM a))
SDL_X11_SYM(حرف*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,بنية Xrm_Hash_بالٹی_Rec*,حرف*,حرف*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,بنية Xrm_Hash_بالٹی_Rec*,حرف*,حرف*,XIDProc,XPointer))
SDL_X11_SYM(فراغ,Xutf8DrawString,(Display *a, Drawable b, XFont_سیٹ c, GC d, صحيح e, صحيح f, _Xconst حرف *g, صحيح h))
SDL_X11_SYM(صحيح,Xutf8_متن_Extents,(XFont_سیٹ a, _Xconst حرف* b, صحيح c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(حرف*,XSetLocaleModifiers,(ثابت حرف *a))
SDL_X11_SYM(حرف*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFont_سیٹ_Extents*,XExtents_دا_Font_سیٹ,(XFont_سیٹ a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFont_سیٹ a))
#جے_انت


#جے_بنا_تعریف NO_SHARED_حافظہ
SDL_X11_MODULE(SHM)
SDL_X11_SYM(حالت_2,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(حالت_2,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(حالت_2,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,صحيح e,صحيح f,صحيح g,صحيح h,بنانشانی صحيح i,بنانشانی صحيح j,Bool k))
SDL_X11_SYM(حالت_2,XShmGetImage,(Display* a,Drawable b,XImage *c,صحيح d, صحيح e, بنانشانی لما f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,بنانشانی صحيح c,صحيح d,حرف* e,XShmSegmentInfo* f,بنانشانی صحيح g,بنانشانی صحيح h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,حرف* c,XShmSegmentInfo* d, بنانشانی صحيح e, بنانشانی صحيح f, بنانشانی صحيح g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(حالت_2,XShm_Query_نسخہ,(Display* a, صحيح *b, صحيح *c, Bool *d))
SDL_X11_SYM(صحيح,XShmPixmapFormat,(Display* a))
#جے_انت

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#جے_تعریف_شدہ LONG64
SDL_X11_MODULE(IO_32_ثنائی_ہندسہ)
SDL_X11_SYM(صحيح,_XData32,(Display *dpy,سجل _Xconst لما *انکڑے,بنانشانی len))
SDL_X11_SYM(فراغ,_XRead32,(Display *dpy,سجل لما *انکڑے,لما len))
#جے_انت

/*
 * These only show up on some variants of Unix.
 */
#جے_تعریف_شدہ SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_اندراج_POINTS)
SDL_X11_SYM(فراغ,Smt_بفر_حد_توں_ودھ,(Display *dpy,سجل smtDisplayPtr p))
SDL_X11_SYM(فراغ,_SmtIpError,(Display *dpy,سجل smtDisplayPtr p,صحيح i))
SDL_X11_SYM(صحيح,ip_Allocate_انکڑے,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(صحيح,ip_Unallocate_And_Send_انکڑے,(ChannelPtr a,IPCard b))
#جے_انت

// XCursor support
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(صحيح a,صحيح b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(صحيح a))
SDL_X11_SYM(فراغ,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(فراغ,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,Xcursor_Image_لدو_Cursor,(Display *a,ثابت XcursorImage *b))
SDL_X11_SYM(Cursor,Xcursor_Images_لدو_Cursor,(Display *a,ثابت XcursorImages *b))
SDL_X11_SYM(Cursor,Xcursor_Library_لدو_Cursor,(Display *a, ثابت حرف *b))
#جے_انت

// Xdbe support
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(حالت_2,XdbeQueryExtension,(Display *dpy,صحيح *major_نسخہ_return,صحيح *minor_نسخہ_return))
SDL_X11_SYM(Xdbe_پٹھ_بفر,Xdbe_Allocate_پٹھ_بفر_Name,(Display *dpy,کھڑکی_2 کھڑکی,Xdbe_وٹاندرا_Action وٹاندرا_action))
SDL_X11_SYM(حالت_2,Xdbe_Deallocate_پٹھ_بفر_Name,(Display *dpy,Xdbe_پٹھ_بفر بفر_2))
SDL_X11_SYM(حالت_2,Xdbe_وٹاندرا_Buffers,(Display *dpy,Xdbe_وٹاندرا_Info *وٹاندرا_info,صحيح عدد_windows))
SDL_X11_SYM(حالت_2,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(حالت_2,Xdbe_سرا_Idiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,صحيح *عدد_screens))
SDL_X11_SYM(فراغ,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(Xdbe_پٹھ_بفر_گن*,Xdbe_Get_پٹھ_بفر_گن,(Display *dpy,Xdbe_پٹھ_بفر بفر_2))
#جے_انت

// XInput2 support for multiple mice, tablets, etc.
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,صحيح b,صحيح *c))
SDL_X11_SYM(فراغ,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(صحيح,XISelectEvents,(Display *a,کھڑکی_2 b,XIEvent_نقاب *c,صحيح d))
SDL_X11_SYM(صحيح,XIGrabTouchBegin,(Display *a,صحيح b,کھڑکی_2 c,صحيح d,XIEvent_نقاب *e,صحيح f,XIGrabModifiers *g))
SDL_X11_SYM(صحيح,XIUngrabTouchBegin, (Display *a,صحيح b,کھڑکی_2 c, صحيح d,XIGrabModifiers *e))
SDL_X11_SYM(حالت_2,XIQuery_نسخہ,(Display *a,صحيح *b,صحيح *c))
SDL_X11_SYM(XIEvent_نقاب*,XIGetSelectedEvents,(Display *a,کھڑکی_2 b,صحيح *c))
SDL_X11_SYM(Bool,XIGet_Client_اشارہ_گر,(Display *a,کھڑکی_2 b,صحيح *c))
SDL_X11_SYM(Bool,XIWarp_اشارہ_گر,(Display *a,صحيح b,کھڑکی_2 c,کھڑکی_2 d,مزدوج e,مزدوج f,صحيح g,صحيح h,مزدوج i,مزدوج j))
SDL_X11_SYM(حالت_2,XIGetProperty,(Display *a,صحيح b,Atom c,لما d,لما e,Bool f, Atom g, Atom *h, صحيح *i, بنانشانی لما *j, بنانشانی لما *k, بنانشانی حرف **l))
#جے_انت

// XRandR support
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(حالت_2,XRRQuery_نسخہ,(Display *dpy,صحيح *major_versionp,صحيح *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,صحيح *event_ادھار_return,صحيح *error_ادھار_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(ناپ_ID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(چھوٹا,XRRConfig_Current_شرح,(XRRScreenConfiguration *config))
SDL_X11_SYM(چھوٹا *,XRRConfigRates,(XRRScreenConfiguration *config,صحيح ناپ_ID_2,صحيح *nrates))
SDL_X11_SYM(XRRScreen_ناپ *,XRRConfigSizes,(XRRScreenConfiguration *config,صحيح *nsizes))
SDL_X11_SYM(حالت_2,XRRSet_Screen_Config_And_شرح,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,صحيح ناپ_اشاریہ,Rotation rotation,چھوٹا شرح,ویلا_2 timestamp))
SDL_X11_SYM(فراغ,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(فراغ,XRRSet_Screen_ناپ,(Display *dpy, کھڑکی_2 کھڑکی,صحيح چوڑائی, صحيح اچائی,صحيح mm_چوڑائی_2, صحيح mm_اچائی_2))
SDL_X11_SYM(حالت_2,XRRGet_Screen_ناپ_Range,(Display *dpy, کھڑکی_2 کھڑکی,صحيح *min_چوڑائی, صحيح *min_اچائی, صحيح *max_چوڑائی, صحيح *max_اچائی))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, کھڑکی_2 کھڑکی))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, کھڑکی_2 کھڑکی))
SDL_X11_SYM(فراغ,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(فراغ,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(فراغ,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(حالت_2,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, ویلا_2 timestamp, صحيح x, صحيح y, RRMode منوال, Rotation rotation, RROutput *outputs, صحيح noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, صحيح *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(صحيح,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, لما وتھ_2, لما لمائی, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, صحيح *actual_format, بنانشانی لما *nitems, بنانشانی لما *بائٹاں_after, بنانشانی حرف **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,کھڑکی_2 کھڑکی))
SDL_X11_SYM(فراغ,XRRSelect_داخلہ,(Display *dpy, کھڑکی_2 کھڑکی, صحيح نقاب))
SDL_X11_SYM(حالت_2,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtc_Transform_گن **گن))
#جے_انت

// MIT-SCREEN-SAVER support
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,صحيح *event_ادھار_2,صحيح *error_ادھار_2))
SDL_X11_SYM(حالت_2,XScreen_Saver_Query_نسخہ,(Display *dpy,صحيح *major_versionp,صحيح *minor_versionp))
SDL_X11_SYM(فراغ,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(فراغ,XShape_Combine_نقاب,(Display *dpy,کھڑکی_2 dest,صحيح dest_قسم,صحيح x_off,صحيح y_off,Pixmap src,صحيح op))
SDL_X11_SYM(فراغ,XShapeCombineRegion,(Display *a,کھڑکی_2 b,صحيح c,صحيح d,صحيح e,Region f,صحيح g))
#جے_انت

#تعریف_رد SDL_X11_MODULE
#تعریف_رد SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
