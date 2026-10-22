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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_X11_MODULE
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_MODULE(modname)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_X11_SYM
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_X11_SYM(rc, fn, params)
#ಆದರೆ_ಅಂತ್ಯ

SDL_X11_MODULE(BASEXLIB)
SDL_X11_SYM(XSizeHints*,XAlloc_ಗಾತ್ರ_Hints,(ಶೂನ್ಯ))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(ಶೂನ್ಯ))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(ಶೂನ್ಯ))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XChange_ಸೂಚಕ_Control,(Display* a,Bool b,Bool c,ಪೂರ್ಣಾಂಕ d,ಪೂರ್ಣಾಂಕ e,ಪೂರ್ಣಾಂಕ f))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XChangeProperty,(Display* a,ಕಿಟಕಿ_2 b,Atom c,Atom d,ಪೂರ್ಣಾಂಕ e,ಪೂರ್ಣಾಂಕ f,_Xconst ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ* g,ಪೂರ್ಣಾಂಕ h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XClear_ಕಿಟಕಿ,(Display* a,ಕಿಟಕಿ_2 b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XCloseDisplay,(Display* a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,ಕಿಟಕಿ_2 e,ಸಮಯ_2 f))
SDL_X11_SYM(Pixmap,XCreate_Bitmap_From_ದತ್ತಾಂಶ,(Display *dpy,Drawable d,_Xconst ಅಕ್ಷರ *ದತ್ತಾಂಶ,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಅಗಲ,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಎತ್ತರ))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,ಕಿಟಕಿ_2 b,Visual* c,ಪೂರ್ಣಾಂಕ d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ f,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ d,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ e,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ b))
SDL_X11_SYM(XFont_ಗಣ,XCreate_Font_ಗಣ,(Display* a, _Xconst ಅಕ್ಷರ* b, ಅಕ್ಷರ*** c, ಪೂರ್ಣಾಂಕ* d, ಅಕ್ಷರ** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ c,XGCValues* d))
SDL_X11_SYM(ಶೂನ್ಯ,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ c,ಪೂರ್ಣಾಂಕ d,ಪೂರ್ಣಾಂಕ e,ಅಕ್ಷರ* f,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ g,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ h,ಪೂರ್ಣಾಂಕ i,ಪೂರ್ಣಾಂಕ j))
SDL_X11_SYM(ಕಿಟಕಿ_2,XCreate_ಕಿಟಕಿ,(Display* a,ಕಿಟಕಿ_2 b,ಪೂರ್ಣಾಂಕ c,ಪೂರ್ಣಾಂಕ d,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ e,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ f,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ g,ಪೂರ್ಣಾಂಕ h,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i,Visual* j,ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ k,XSet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು* l))
SDL_X11_SYM(ಶೂನ್ಯ,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, ಪೂರ್ಣಾಂಕ e, ಪೂರ್ಣಾಂಕ f, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ g, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ i, ಪೂರ್ಣಾಂಕ j))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XDefineCursor,(Display* a,ಕಿಟಕಿ_2 b,Cursor c))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XDeleteProperty,(Display* a,ಕಿಟಕಿ_2 b,Atom c))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XDestroy_ಕಿಟಕಿ,(Display* a,ಕಿಟಕಿ_2 b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XDisplayKeycodes,(Display* a,ಪೂರ್ಣಾಂಕ* b,ಪೂರ್ಣಾಂಕ* c))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XDrawRectangle,(Display* a,Drawable b,GC c,ಪೂರ್ಣಾಂಕ d,ಪೂರ್ಣಾಂಕ e,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ f,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ g))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XFonts_ದ_Font_ಗಣ,(XFont_ಗಣ a,XFontStruct ***b,ಅಕ್ಷರ ***c))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XFillArc,(Display* a,Drawable b,GC c,ಪೂರ್ಣಾಂಕ d,ಪೂರ್ಣಾಂಕ e,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ f,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ g, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ i))
SDL_X11_SYM(ಅಕ್ಷರ*,XDisplayName,(_Xconst ಅಕ್ಷರ* a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XDrawString,(Display* a,Drawable b,GC c,ಪೂರ್ಣಾಂಕ d,ಪೂರ್ಣಾಂಕ e,_Xconst ಅಕ್ಷರ* f,ಪೂರ್ಣಾಂಕ g))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XEventsQueued,(Display* a,ಪೂರ್ಣಾಂಕ b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XFillRectangle,(Display* a,Drawable b,GC c,ಪೂರ್ಣಾಂಕ d,ಪೂರ್ಣಾಂಕ e,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ f,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,ಕಿಟಕಿ_2 w))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XFlush,(Display* a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XFree,(ಶೂನ್ಯ*a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(ಶೂನ್ಯ,XFree_Font_ಗಣ,(Display* a, XFont_ಗಣ b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(ಶೂನ್ಯ,XFreeStringList,(ಅಕ್ಷರ** a))
SDL_X11_SYM(ಅಕ್ಷರ*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XGet_ಒಳಹರಿವು_Focus,(Display *a,ಕಿಟಕಿ_2 *b,ಪೂರ್ಣಾಂಕ *c))
SDL_X11_SYM(ಕೀಲಿ_Sym*,XGetKeyboardMapping,(Display *a, ಕೀಲಿ_ಸಂಕೇತ_2 b, ಪೂರ್ಣಾಂಕ c, ಪೂರ್ಣಾಂಕ *d))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XGet_Error_Database_ಪಠ್ಯ,(Display* a,_Xconst ಅಕ್ಷರ* b,_Xconst ಅಕ್ಷರ* c,_Xconst ಅಕ್ಷರ* d,ಅಕ್ಷರ* e,ಪೂರ್ಣಾಂಕ f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XGet_ಸೂಚಕ_Control,(Display* a,ಪೂರ್ಣಾಂಕ* b,ಪೂರ್ಣಾಂಕ* c,ಪೂರ್ಣಾಂಕ* d))
SDL_X11_SYM(ಕಿಟಕಿ_2,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,ದೀರ್ಘ b,XVisualInfo* c,ಪೂರ್ಣಾಂಕ* d))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು,(Display* a,ಕಿಟಕಿ_2 b,XWindow_ಗುಣಲಕ್ಷಣಗಳು* c))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XGet_ಕಿಟಕಿ_Property,(Display* a,ಕಿಟಕಿ_2 b,Atom c,ದೀರ್ಘ d,ದೀರ್ಘ e,Bool f,Atom g,Atom* h,ಪೂರ್ಣಾಂಕ* i,ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ* j,ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ *k,ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,ಕಿಟಕಿ_2 b))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XGetWMNormalHints,(Display *a,ಕಿಟಕಿ_2 b, XSizeHints *c, ದೀರ್ಘ *d))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XGrabKeyboard,(Display* a,ಕಿಟಕಿ_2 b,Bool c,ಪೂರ್ಣಾಂಕ d,ಪೂರ್ಣಾಂಕ e,ಸಮಯ_2 f))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XGrab_ಸೂಚಕ,(Display* a,ಕಿಟಕಿ_2 b,Bool c,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ d,ಪೂರ್ಣಾಂಕ e,ಪೂರ್ಣಾಂಕ f,ಕಿಟಕಿ_2 g,Cursor h,ಸಮಯ_2 i))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XGrabServer,(Display* a))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XIconify_ಕಿಟಕಿ,(Display* a,ಕಿಟಕಿ_2 b,ಪೂರ್ಣಾಂಕ c))
SDL_X11_SYM(ಕೀಲಿ_ಸಂಕೇತ_2,XKeysym_ಗಮ್ಯ_Keycode,(Display* a,ಕೀಲಿ_Sym b))
SDL_X11_SYM(ಅಕ್ಷರ*,XKeysym_ಗಮ್ಯ_String,(ಕೀಲಿ_Sym a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst ಅಕ್ಷರ* b,Bool c))
SDL_X11_SYM(XPixmap_Format_ಮೌಲ್ಯಗಳು*,XListPixmapFormats,(Display* a,ಪೂರ್ಣಾಂಕ* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst ಅಕ್ಷರ* b))
SDL_X11_SYM(ಕೀಲಿ_Sym,XLookupKeysym,(XKeyEvent* a,ಪೂರ್ಣಾಂಕ b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XLookupString,(XKeyEvent* a,ಅಕ್ಷರ* b,ಪೂರ್ಣಾಂಕ c,ಕೀಲಿ_Sym* d,XCompose_ಸ್ಥಿತಿ* e))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XMapRaised,(Display* a,ಕಿಟಕಿ_2 b))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XMatchVisualInfo,(Display* a,ಪೂರ್ಣಾಂಕ b,ಪೂರ್ಣಾಂಕ c,ಪೂರ್ಣಾಂಕ d,XVisualInfo* e))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XMissingExtension,(Display* a,_Xconst ಅಕ್ಷರ* b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XMove_ಕಿಟಕಿ,(Display* a,ಕಿಟಕಿ_2 b,ಪೂರ್ಣಾಂಕ c,ಪೂರ್ಣಾಂಕ d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst ಅಕ್ಷರ* a))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XInit_ಎಳೆಗಳು,(ಶೂನ್ಯ))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,ಪೂರ್ಣಾಂಕ c, ಪೂರ್ಣಾಂಕ d,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ e,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ f,ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ g,ಪೂರ್ಣಾಂಕ h))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XPutImage,(Display* a,Drawable b,GC c,XImage* d,ಪೂರ್ಣಾಂಕ e,ಪೂರ್ಣಾಂಕ f,ಪೂರ್ಣಾಂಕ g,ಪೂರ್ಣಾಂಕ h,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ j))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XQueryKeymap,(Display* a,ಅಕ್ಷರ b[32]))
SDL_X11_SYM(Bool,XQuery_ಸೂಚಕ,(Display* a,ಕಿಟಕಿ_2 b,ಕಿಟಕಿ_2* c,ಕಿಟಕಿ_2* d,ಪೂರ್ಣಾಂಕ* e,ಪೂರ್ಣಾಂಕ* f,ಪೂರ್ಣಾಂಕ* g,ಪೂರ್ಣಾಂಕ* h,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ* i))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XRaise_ಕಿಟಕಿ,(Display* a,ಕಿಟಕಿ_2 b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XReparent_ಕಿಟಕಿ,(Display* a,ಕಿಟಕಿ_2 b,ಕಿಟಕಿ_2 c,ಪೂರ್ಣಾಂಕ d,ಪೂರ್ಣಾಂಕ e))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XResetScreenSaver,(Display* a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XResize_ಕಿಟಕಿ,(Display* a,ಕಿಟಕಿ_2 b,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ c,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ d))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XScreen_ಸಂಖ್ಯೆ_ದ_Screen,(Screen* a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XSelect_ಒಳಹರಿವು,(Display* a,ಕಿಟಕಿ_2 b,ದೀರ್ಘ c))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XSendEvent,(Display* a,ಕಿಟಕಿ_2 b,Bool c,ದೀರ್ಘ d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XSetForeground,(Display* a,GC b,ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XSet_ಒಳಹರಿವು_Focus,(Display *a,ಕಿಟಕಿ_2 b,ಪೂರ್ಣಾಂಕ c,ಸಮಯ_2 d))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XSetSelectionOwner,(Display* a,Atom b,ಕಿಟಕಿ_2 c,ಸಮಯ_2 d))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XSetTransientForHint,(Display* a,ಕಿಟಕಿ_2 b,ಕಿಟಕಿ_2 c))
SDL_X11_SYM(ಶೂನ್ಯ,XSet_ಪಠ್ಯ_Property,(Display* a,ಕಿಟಕಿ_2 b,XTextProperty* c,Atom d))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XSet_ಕಿಟಕಿ_Background,(Display* a,ಕಿಟಕಿ_2 b,ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ c))
SDL_X11_SYM(ಶೂನ್ಯ,XSetWMHints,(Display* a,ಕಿಟಕಿ_2 b,XWMHints* c))
SDL_X11_SYM(ಶೂನ್ಯ,XSetWMNormalHints,(Display* a,ಕಿಟಕಿ_2 b,XSizeHints* c))
SDL_X11_SYM(ಶೂನ್ಯ,XSetWMProperties,(Display* a,ಕಿಟಕಿ_2 b,XTextProperty* c,XTextProperty* d,ಅಕ್ಷರ** e,ಪೂರ್ಣಾಂಕ f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XSetWMProtocols,(Display* a,ಕಿಟಕಿ_2 b,Atom* c,ಪೂರ್ಣಾಂಕ d))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XStoreColors,(Display* a,Colormap b,XColor* c,ಪೂರ್ಣಾಂಕ d))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XStoreName,(Display* a,ಕಿಟಕಿ_2 b,_Xconst ಅಕ್ಷರ* c))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XString_List_ಗಮ್ಯ_ಪಠ್ಯ_Property,(ಅಕ್ಷರ** a,ಪೂರ್ಣಾಂಕ b,XTextProperty* c))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XSync,(Display* a,Bool b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XTextExtents,(XFontStruct* a,_Xconst ಅಕ್ಷರ* b,ಪೂರ್ಣಾಂಕ c,ಪೂರ್ಣಾಂಕ* d,ಪೂರ್ಣಾಂಕ* e,ಪೂರ್ಣಾಂಕ* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,ಕಿಟಕಿ_2 b,ಕಿಟಕಿ_2 c,ಪೂರ್ಣಾಂಕ d,ಪೂರ್ಣಾಂಕ e,ಪೂರ್ಣಾಂಕ* f,ಪೂರ್ಣಾಂಕ* g,ಕಿಟಕಿ_2* h))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XUndefineCursor,(Display* a,ಕಿಟಕಿ_2 b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XUngrabKeyboard,(Display* a,ಸಮಯ_2 b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XUngrab_ಸೂಚಕ,(Display* a,ಸಮಯ_2 b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XUngrabServer,(Display* a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XWarp_ಸೂಚಕ,(Display* a,ಕಿಟಕಿ_2 b,ಕಿಟಕಿ_2 c,ಪೂರ್ಣಾಂಕ d,ಪೂರ್ಣಾಂಕ e,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ f,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ g,ಪೂರ್ಣಾಂಕ h,ಪೂರ್ಣಾಂಕ i))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XWindowEvent,(Display* a,ಕಿಟಕಿ_2 b,ದೀರ್ಘ c,XEvent* d))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XWithdraw_ಕಿಟಕಿ,(Display* a,ಕಿಟಕಿ_2 b,ಪೂರ್ಣಾಂಕ c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(ಅಕ್ಷರ*,XGetDefault,(Display* a,_Xconst ಅಕ್ಷರ* b, _Xconst ಅಕ್ಷರ* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst ಅಕ್ಷರ* b,ಪೂರ್ಣಾಂಕ* c,ಪೂರ್ಣಾಂಕ* d,ಪೂರ್ಣಾಂಕ* e))
SDL_X11_SYM(ಅಕ್ಷರ *,XDisplayString,(Display* a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XGet_Error_ಪಠ್ಯ,(Display* a,ಪೂರ್ಣಾಂಕ b,ಅಕ್ಷರ* c,ಪೂರ್ಣಾಂಕ d))
SDL_X11_SYM(ಶೂನ್ಯ,XEat_ದತ್ತಾಂಶ,(Display* a,ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ b))
SDL_X11_SYM(ಶೂನ್ಯ,_XFlush,(Display* a))
SDL_X11_SYM(ಶೂನ್ಯ,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,_XRead,(Display* a,ಅಕ್ಷರ* b,ದೀರ್ಘ c))
SDL_X11_SYM(ಶೂನ್ಯ,_XReadPad,(Display* a,ಅಕ್ಷರ* b,ದೀರ್ಘ c))
SDL_X11_SYM(ಶೂನ್ಯ,_XSend,(Display* a,_Xconst ಅಕ್ಷರ* b,ದೀರ್ಘ c))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,_XReply,(Display* a,x_ಉತ್ತರ* b,ಪೂರ್ಣಾಂಕ c,Bool d))
SDL_X11_SYM(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ,XSet_ಕೊನೆಯ_Request_Read,(Display* a,x_Generic_ಉತ್ತರ* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESet_Wire_ಗಮ್ಯ_Event_Ret_Type,XESet_Wire_ಗಮ್ಯ_Event,(Display* a,ಪೂರ್ಣಾಂಕ b,SDL_X11_XESet_Wire_ಗಮ್ಯ_Event_Ret_Type c))
SDL_X11_SYM(SDL_X11_XESet_Event_ಗಮ್ಯ_Wire_Ret_Type,XESet_Event_ಗಮ್ಯ_Wire,(Display* a,ಪೂರ್ಣಾಂಕ b,SDL_X11_XESet_Event_ಗಮ್ಯ_Wire_Ret_Type c))
SDL_X11_SYM(ಶೂನ್ಯ,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XQuery_ವೃಕ್ಷ,(Display* a,ಕಿಟಕಿ_2 b,ಕಿಟಕಿ_2* c,ಕಿಟಕಿ_2* d,ಕಿಟಕಿ_2** e,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ* f))
SDL_X11_SYM(Bool,XSupportsLocale,(ಶೂನ್ಯ))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,Xmb_ಪಠ್ಯ_List_ಗಮ್ಯ_ಪಠ್ಯ_Property,(Display* a,ಅಕ್ಷರ** b,ಪೂರ್ಣಾಂಕ c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(ಶೂನ್ಯ))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(ಶೂನ್ಯ,XDestroyRegion,(Region))
SDL_X11_SYM(ಶೂನ್ಯ,XrmInitialize,(ಶೂನ್ಯ))
SDL_X11_SYM(ಅಕ್ಷರ*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(ಅಕ್ಷರ *ದತ್ತಾಂಶ))
SDL_X11_SYM(ಶೂನ್ಯ,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, ಅಕ್ಷರ* str_name, ಅಕ್ಷರ* str_class, ಅಕ್ಷರ **str_type_return, Xrm_ಮೌಲ್ಯ *))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XGet_ಸೂಚಕ_Mapping,(Display *a, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *b, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ c))

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(ಸೂಚಕ_Barrier, XFixes_Create_ಸೂಚಕ_Barrier, (Display* a, ಕಿಟಕಿ_2 b, ಪೂರ್ಣಾಂಕ c, ಪೂರ್ಣಾಂಕ d, ಪೂರ್ಣಾಂಕ e, ಪೂರ್ಣಾಂಕ f, ಪೂರ್ಣಾಂಕ g, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ *i))
SDL_X11_SYM(ಶೂನ್ಯ, XFixes_Destroy_ಸೂಚಕ_Barrier, (Display* a, ಸೂಚಕ_Barrier b))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ, XIBarrier_Release_ಸೂಚಕ,(Display* a,  ಪೂರ್ಣಾಂಕ b, ಸೂಚಕ_Barrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(ಸ್ಥಿತಿ_3, XFixes_Query_ಆವೃತ್ತಿ,(Display* a, ಪೂರ್ಣಾಂಕ* b, ಪೂರ್ಣಾಂಕ* c))
SDL_X11_SYM(ಸ್ಥಿತಿ_3, XFixes_Select_Selection_ಒಳಹರಿವು, (Display* a, ಕಿಟಕಿ_2 b, Atom c, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ d))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(ಸ್ಥಿತಿ_3, XSyncQueryExtension, (Display* a, ಪೂರ್ಣಾಂಕ* b, ಪೂರ್ಣಾಂಕ* c))
SDL_X11_SYM(ಸ್ಥಿತಿ_3, XSyncInitialize, (Display* a, ಪೂರ್ಣಾಂಕ* b, ಪೂರ್ಣಾಂಕ* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_ಮೌಲ್ಯ b))
SDL_X11_SYM(ಸ್ಥಿತಿ_3, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(ಸ್ಥಿತಿ_3, XSync_ಗಣ_Counter, (Display* a, XSyncCounter b, XSync_ಮೌಲ್ಯ c))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(ಸ್ಥಿತಿ_3, XTestQueryExtension, (Display* a, ಪೂರ್ಣಾಂಕ* b, ಪೂರ್ಣಾಂಕ* c))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ, XTestFakeMotionEvent, (Display* a, ಪೂರ್ಣಾಂಕ b, ಪೂರ್ಣಾಂಕ c, ಪೂರ್ಣಾಂಕ d, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ e))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGet_Event_ದತ್ತಾಂಶ,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(ಶೂನ್ಯ,XFree_Event_ದತ್ತಾಂಶ,(Display* a,XGenericEventCookie* b))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,ಪೂರ್ಣಾಂಕ * b,ಪೂರ್ಣಾಂಕ * c,ಪೂರ್ಣಾಂಕ * d,ಪೂರ್ಣಾಂಕ * e, ಪೂರ್ಣಾಂಕ *f))
SDL_X11_SYM(ಕೀಲಿ_Sym,Xkb_Keycode_ಗಮ್ಯ_Keysym,(Display* a, ಕೀಲಿ_ಸಂಕೇತ_2 b, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ c, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ b, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ c, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ b, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ c, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ d, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ e))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,Xkb_Get_ಹೆಸರುಗಳು,(Display *a, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ b, XkbDescPtr c))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XkbGetState,(Display* a,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ b,XkbStatePtr c))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XkbGetUpdatedMap,(Display* a,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ b,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ c))
SDL_X11_SYM(ಶೂನ್ಯ,XkbFreeClientMap,(XkbDescPtr a,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ b, Bool c))
SDL_X11_SYM(ಶೂನ್ಯ,XkbFreeKeyboard,(XkbDescPtr a,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ b, Bool c))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,Xkb_ಗಣ_Detectable_Auto_Repeat,(Display* a, Bool b, Bool* c))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,Xutf8_ಪಠ್ಯ_List_ಗಮ್ಯ_ಪಠ್ಯ_Property,(Display* a,ಅಕ್ಷರ** b,ಪೂರ್ಣಾಂಕ c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,ಅಕ್ಷರ* c,ಪೂರ್ಣಾಂಕ d,ಕೀಲಿ_Sym* e,ಸ್ಥಿತಿ_3* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(ಶೂನ್ಯ,XDestroyIC,(XIC a))
SDL_X11_SYM(ಅಕ್ಷರ*,XGetICValues,(XIC,...))
SDL_X11_SYM(ಅಕ್ಷರ*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(ಪೂರ್ಣಾಂಕ, ...))
SDL_X11_SYM(ಶೂನ್ಯ,XSetICFocus,(XIC a))
SDL_X11_SYM(ಶೂನ್ಯ,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,ರಚನೆ Xrm_Hash_ಪಾತ್ರೆ_Rec* b,ಅಕ್ಷರ* c,ಅಕ್ಷರ* d))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XCloseIM,(XIM a))
SDL_X11_SYM(ಅಕ್ಷರ*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,ರಚನೆ Xrm_Hash_ಪಾತ್ರೆ_Rec*,ಅಕ್ಷರ*,ಅಕ್ಷರ*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,ರಚನೆ Xrm_Hash_ಪಾತ್ರೆ_Rec*,ಅಕ್ಷರ*,ಅಕ್ಷರ*,XIDProc,XPointer))
SDL_X11_SYM(ಶೂನ್ಯ,Xutf8DrawString,(Display *a, Drawable b, XFont_ಗಣ c, GC d, ಪೂರ್ಣಾಂಕ e, ಪೂರ್ಣಾಂಕ f, _Xconst ಅಕ್ಷರ *g, ಪೂರ್ಣಾಂಕ h))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,Xutf8_ಪಠ್ಯ_Extents,(XFont_ಗಣ a, _Xconst ಅಕ್ಷರ* b, ಪೂರ್ಣಾಂಕ c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(ಅಕ್ಷರ*,XSetLocaleModifiers,(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *a))
SDL_X11_SYM(ಅಕ್ಷರ*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFont_ಗಣ_Extents*,XExtents_ದ_Font_ಗಣ,(XFont_ಗಣ a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFont_ಗಣ a))
#ಆದರೆ_ಅಂತ್ಯ


#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
SDL_X11_MODULE(SHM)
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,ಪೂರ್ಣಾಂಕ e,ಪೂರ್ಣಾಂಕ f,ಪೂರ್ಣಾಂಕ g,ಪೂರ್ಣಾಂಕ h,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ j,Bool k))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XShmGetImage,(Display* a,Drawable b,XImage *c,ಪೂರ್ಣಾಂಕ d, ಪೂರ್ಣಾಂಕ e, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ c,ಪೂರ್ಣಾಂಕ d,ಅಕ್ಷರ* e,XShmSegmentInfo* f,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ g,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,ಅಕ್ಷರ* c,XShmSegmentInfo* d, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ e, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ f, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XShm_Query_ಆವೃತ್ತಿ,(Display* a, ಪೂರ್ಣಾಂಕ *b, ಪೂರ್ಣಾಂಕ *c, Bool *d))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XShmPixmapFormat,(Display* a))
#ಆದರೆ_ಅಂತ್ಯ

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ LONG64
SDL_X11_MODULE(IO_32_ಬಿಟ್)
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,_XData32,(Display *dpy,ನೋಂದಣಿ _Xconst ದೀರ್ಘ *ದತ್ತಾಂಶ,ಚಿಹ್ನೆರಹಿತ len))
SDL_X11_SYM(ಶೂನ್ಯ,_XRead32,(Display *dpy,ನೋಂದಣಿ ದೀರ್ಘ *ದತ್ತಾಂಶ,ದೀರ್ಘ len))
#ಆದರೆ_ಅಂತ್ಯ

/*
 * These only show up on some variants of Unix.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ನಮೂದು_POINTS)
SDL_X11_SYM(ಶೂನ್ಯ,Smt_ಬಫರ್_ಅತಿಪ್ರವಾಹ,(Display *dpy,ನೋಂದಣಿ smtDisplayPtr p))
SDL_X11_SYM(ಶೂನ್ಯ,_SmtIpError,(Display *dpy,ನೋಂದಣಿ smtDisplayPtr p,ಪೂರ್ಣಾಂಕ i))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,ip_Allocate_ದತ್ತಾಂಶ,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,ip_Unallocate_And_Send_ದತ್ತಾಂಶ,(ChannelPtr a,IPCard b))
#ಆದರೆ_ಅಂತ್ಯ

// XCursor support
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(ಪೂರ್ಣಾಂಕ a,ಪೂರ್ಣಾಂಕ b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(ಪೂರ್ಣಾಂಕ a))
SDL_X11_SYM(ಶೂನ್ಯ,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(ಶೂನ್ಯ,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,Xcursor_Image_ತುಂಬು_Cursor,(Display *a,ಸ್ಥಿರಾಂಕ XcursorImage *b))
SDL_X11_SYM(Cursor,Xcursor_Images_ತುಂಬು_Cursor,(Display *a,ಸ್ಥಿರಾಂಕ XcursorImages *b))
SDL_X11_SYM(Cursor,Xcursor_Library_ತುಂಬು_Cursor,(Display *a, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *b))
#ಆದರೆ_ಅಂತ್ಯ

// Xdbe support
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XdbeQueryExtension,(Display *dpy,ಪೂರ್ಣಾಂಕ *major_ಆವೃತ್ತಿ_return,ಪೂರ್ಣಾಂಕ *minor_ಆವೃತ್ತಿ_return))
SDL_X11_SYM(Xdbe_ಹಿಂಭಾಗ_ಬಫರ್,Xdbe_Allocate_ಹಿಂಭಾಗ_ಬಫರ್_Name,(Display *dpy,ಕಿಟಕಿ_2 ಕಿಟಕಿ,Xdbe_ಅದಲುಬದಲು_Action ಅದಲುಬದಲು_action))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,Xdbe_Deallocate_ಹಿಂಭಾಗ_ಬಫರ್_Name,(Display *dpy,Xdbe_ಹಿಂಭಾಗ_ಬಫರ್ ಬಫರ್_2))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,Xdbe_ಅದಲುಬದಲು_Buffers,(Display *dpy,Xdbe_ಅದಲುಬದಲು_Info *ಅದಲುಬದಲು_info,ಪೂರ್ಣಾಂಕ ಅಂಕೆ_windows))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,Xdbe_ಕೊನೆ_Idiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,ಪೂರ್ಣಾಂಕ *ಅಂಕೆ_screens))
SDL_X11_SYM(ಶೂನ್ಯ,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(Xdbe_ಹಿಂಭಾಗ_ಬಫರ್_ಗುಣಲಕ್ಷಣಗಳು*,Xdbe_Get_ಹಿಂಭಾಗ_ಬಫರ್_ಗುಣಲಕ್ಷಣಗಳು,(Display *dpy,Xdbe_ಹಿಂಭಾಗ_ಬಫರ್ ಬಫರ್_2))
#ಆದರೆ_ಅಂತ್ಯ

// XInput2 support for multiple mice, tablets, etc.
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,ಪೂರ್ಣಾಂಕ b,ಪೂರ್ಣಾಂಕ *c))
SDL_X11_SYM(ಶೂನ್ಯ,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XISelectEvents,(Display *a,ಕಿಟಕಿ_2 b,XIEvent_ಮುಖವಾಡ *c,ಪೂರ್ಣಾಂಕ d))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XIGrabTouchBegin,(Display *a,ಪೂರ್ಣಾಂಕ b,ಕಿಟಕಿ_2 c,ಪೂರ್ಣಾಂಕ d,XIEvent_ಮುಖವಾಡ *e,ಪೂರ್ಣಾಂಕ f,XIGrabModifiers *g))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XIUngrabTouchBegin, (Display *a,ಪೂರ್ಣಾಂಕ b,ಕಿಟಕಿ_2 c, ಪೂರ್ಣಾಂಕ d,XIGrabModifiers *e))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XIQuery_ಆವೃತ್ತಿ,(Display *a,ಪೂರ್ಣಾಂಕ *b,ಪೂರ್ಣಾಂಕ *c))
SDL_X11_SYM(XIEvent_ಮುಖವಾಡ*,XIGetSelectedEvents,(Display *a,ಕಿಟಕಿ_2 b,ಪೂರ್ಣಾಂಕ *c))
SDL_X11_SYM(Bool,XIGet_Client_ಸೂಚಕ,(Display *a,ಕಿಟಕಿ_2 b,ಪೂರ್ಣಾಂಕ *c))
SDL_X11_SYM(Bool,XIWarp_ಸೂಚಕ,(Display *a,ಪೂರ್ಣಾಂಕ b,ಕಿಟಕಿ_2 c,ಕಿಟಕಿ_2 d,ದ್ವಿಗುಣ e,ದ್ವಿಗುಣ f,ಪೂರ್ಣಾಂಕ g,ಪೂರ್ಣಾಂಕ h,ದ್ವಿಗುಣ i,ದ್ವಿಗುಣ j))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XIGetProperty,(Display *a,ಪೂರ್ಣಾಂಕ b,Atom c,ದೀರ್ಘ d,ದೀರ್ಘ e,Bool f, Atom g, Atom *h, ಪೂರ್ಣಾಂಕ *i, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ *j, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ *k, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ **l))
#ಆದರೆ_ಅಂತ್ಯ

// XRandR support
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XRRQuery_ಆವೃತ್ತಿ,(Display *dpy,ಪೂರ್ಣಾಂಕ *major_versionp,ಪೂರ್ಣಾಂಕ *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,ಪೂರ್ಣಾಂಕ *event_ತಳ_return,ಪೂರ್ಣಾಂಕ *error_ತಳ_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(ಗಾತ್ರ_ID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(ಗಿಡ್ಡ,XRRConfig_Current_ದರ,(XRRScreenConfiguration *config))
SDL_X11_SYM(ಗಿಡ್ಡ *,XRRConfigRates,(XRRScreenConfiguration *config,ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_ID_2,ಪೂರ್ಣಾಂಕ *nrates))
SDL_X11_SYM(XRRScreen_ಗಾತ್ರ *,XRRConfigSizes,(XRRScreenConfiguration *config,ಪೂರ್ಣಾಂಕ *nsizes))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XRRSet_Screen_Config_And_ದರ,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_ಸೂಚ್ಯಂಕ,Rotation rotation,ಗಿಡ್ಡ ದರ,ಸಮಯ_2 timestamp))
SDL_X11_SYM(ಶೂನ್ಯ,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(ಶೂನ್ಯ,XRRSet_Screen_ಗಾತ್ರ,(Display *dpy, ಕಿಟಕಿ_2 ಕಿಟಕಿ,ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,ಪೂರ್ಣಾಂಕ mm_ಅಗಲ_2, ಪೂರ್ಣಾಂಕ mm_ಎತ್ತರ_2))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XRRGet_Screen_ಗಾತ್ರ_Range,(Display *dpy, ಕಿಟಕಿ_2 ಕಿಟಕಿ,ಪೂರ್ಣಾಂಕ *min_ಅಗಲ, ಪೂರ್ಣಾಂಕ *min_ಎತ್ತರ, ಪೂರ್ಣಾಂಕ *max_ಅಗಲ, ಪೂರ್ಣಾಂಕ *max_ಎತ್ತರ))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, ಕಿಟಕಿ_2 ಕಿಟಕಿ))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, ಕಿಟಕಿ_2 ಕಿಟಕಿ))
SDL_X11_SYM(ಶೂನ್ಯ,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(ಶೂನ್ಯ,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(ಶೂನ್ಯ,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, ಸಮಯ_2 timestamp, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, RRMode ಬಹುಲಕ, Rotation rotation, RROutput *outputs, ಪೂರ್ಣಾಂಕ noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, ಪೂರ್ಣಾಂಕ *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(ಪೂರ್ಣಾಂಕ,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, ದೀರ್ಘ ಸ್ಥಾನಾಂತರ_2, ದೀರ್ಘ ಉದ್ದಳತೆ, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, ಪೂರ್ಣಾಂಕ *actual_format, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ *nitems, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ *ಬೈಟುಗಳು_after, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,ಕಿಟಕಿ_2 ಕಿಟಕಿ))
SDL_X11_SYM(ಶೂನ್ಯ,XRRSelect_ಒಳಹರಿವು,(Display *dpy, ಕಿಟಕಿ_2 ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtc_Transform_ಗುಣಲಕ್ಷಣಗಳು **ಗುಣಲಕ್ಷಣಗಳು))
#ಆದರೆ_ಅಂತ್ಯ

// MIT-SCREEN-SAVER support
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,ಪೂರ್ಣಾಂಕ *event_ತಳ_2,ಪೂರ್ಣಾಂಕ *error_ತಳ_2))
SDL_X11_SYM(ಸ್ಥಿತಿ_3,XScreen_Saver_Query_ಆವೃತ್ತಿ,(Display *dpy,ಪೂರ್ಣಾಂಕ *major_versionp,ಪೂರ್ಣಾಂಕ *minor_versionp))
SDL_X11_SYM(ಶೂನ್ಯ,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(ಶೂನ್ಯ,XShape_Combine_ಮುಖವಾಡ,(Display *dpy,ಕಿಟಕಿ_2 dest,ಪೂರ್ಣಾಂಕ dest_ಬಗೆ,ಪೂರ್ಣಾಂಕ x_off,ಪೂರ್ಣಾಂಕ y_off,Pixmap src,ಪೂರ್ಣಾಂಕ op))
SDL_X11_SYM(ಶೂನ್ಯ,XShapeCombineRegion,(Display *a,ಕಿಟಕಿ_2 b,ಪೂರ್ಣಾಂಕ c,ಪೂರ್ಣಾಂಕ d,ಪೂರ್ಣಾಂಕ e,Region f,ಪೂರ್ಣಾಂಕ g))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_X11_MODULE
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on
