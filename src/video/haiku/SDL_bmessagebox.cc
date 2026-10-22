/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>
  Copyright (C) 2018-2019 EXL <exlmotodev@gmail.com>

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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#ضمن "../../core/haiku/SDL_BeApp.h"

#ضمن <Alert.h>
#ضمن <Application.h>
#ضمن <Button.h>
#ضمن <Font.h>
#ضمن <Layout.h>
#ضمن <String.h>
#ضمن <TextView.h>
#ضمن <View.h>
#ضمن <Window.h>

#ضمن <InterfaceDefs.h>
#ضمن <SupportDefs.h>
#ضمن <GraphicsDefs.h>

#ضمن <new>
#ضمن <vector>
#ضمن <algorithm>
#ضمن <memory>

تعداد
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_درازی_بایتها = 120
};

صنف HAIKU_SDL_پیام_Box : عام BAlert
{
	عائم f_Computed_پیام_Box_عرض;

	BTextView *f_پیام_Box_متن_View;

	صحيح fCloseButton;
	صحيح fDefaultButton;

	منطقي fCustomColorScheme;
	منطقي f_There_Is_Long_سطر;
	rgb_color f_متن_Color;

	ثابت حرف *fTitle;
	ثابت حرف *HAIKU_SDL_DefTitle;
	ثابت حرف *HAIKU_SDL_Def_پیام;
	ثابت حرف *HAIKU_SDL_DefButton;

	std::وکتور<ثابت SDL_پیام_Box_Button_داده *> fButtons;

	ساكن منطقي
	مرتب_سازی_Buttons_Predicate(ثابت SDL_پیام_Box_Button_داده *a_Button_چپ,
	                                 ثابت SDL_پیام_Box_Button_داده *a_Button_راست)
	{
		أرجع a_Button_چپ->buttonID < a_Button_راست->buttonID;
	}

	alert_type
	Convert_پیام_Box_Type(ثابت SDL_پیام_Box_Flags a_پنجره_Type) ثابت
	{
		بدل (a_پنجره_Type)
		{
			افتراضي:
			حالة SDL_MESSAGEBOX_WARNING:
			{
				أرجع B_WARNING_ALERT;
			}
			حالة SDL_MESSAGEBOX_ERROR:
			{
				أرجع B_STOP_ALERT;
			}
			حالة SDL_MESSAGEBOX_INFORMATION:
			{
				أرجع B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(ثابت SDL_پیام_Box_Color *aColor) ثابت
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		أرجع color;
	}

	int32
	Get_چپ_Panel_عرض(فراغ) ثابت
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->اندازه_2() + 15) / 16);
		أرجع (30 * scale) + (32 * scale);
	}

	فراغ
	Update_متن_View_عرض(فراغ)
	{
		f_Computed_پیام_Box_عرض = f_پیام_Box_متن_View->Preferred_اندازه().عرض_2() + Get_چپ_Panel_عرض();
	}

	فراغ
	Parse_Sdl_پیام_Box_داده(ثابت SDL_پیام_Box_داده *a_پیام_Box_داده)
	{
		إذا (a_پیام_Box_داده == عدم) {
			مجموعه_Title_2(HAIKU_SDL_DefTitle);
			مجموعه_پیام_متن(HAIKU_SDL_Def_پیام);
			جمع_کن_Button(HAIKU_SDL_DefButton);
			أرجع;
		}

		إذا (a_پیام_Box_داده->numbuttons <= 0) {
			جمع_کن_Button(HAIKU_SDL_DefButton);
		} وإلا {
			جمع_کن_Sdl_Buttons(a_پیام_Box_داده->buttons, a_پیام_Box_داده->numbuttons);
		}

		إذا (a_پیام_Box_داده->colorScheme != عدم) {
			fCustomColorScheme = درست;
			ApplyAndParseColorScheme(a_پیام_Box_داده->colorScheme);
		}

		(a_پیام_Box_داده->title[0]) ?
			مجموعه_Title_2(a_پیام_Box_داده->title) : مجموعه_Title_2(HAIKU_SDL_DefTitle);
		(a_پیام_Box_داده->پیام[0]) ?
			مجموعه_پیام_متن(a_پیام_Box_داده->پیام) : مجموعه_پیام_متن(HAIKU_SDL_Def_پیام);

		مجموعه_Type(Convert_پیام_Box_Type(a_پیام_Box_داده->flags));
	}

	فراغ
	ApplyAndParseColorScheme(ثابت SDL_پیام_Box_Color_Scheme *aColorScheme)
	{
		مجموعه_Background_Color(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		f_متن_Color = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_متن]);
		مجموعه_Button_Colors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_متن],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	فراغ
	مجموعه_Button_Colors(ثابت SDL_پیام_Box_Color *aBorderColor,
	                ثابت SDL_پیام_Box_Color *aBackgroundColor,
	                ثابت SDL_پیام_Box_Color *a_متن_Color,
	                ثابت SDL_پیام_Box_Color *aSelectedColor)
	{
		إذا (fCustomColorScheme) {
			int32 شمار_Buttons = شمار_Buttons_2();
			لكل (صحيح i = 0; i < شمار_Buttons; ++i) {
				ButtonAt(i)->مجموعه_View_Color(ConvertColorType(aBorderColor));
				ButtonAt(i)->مجموعه_کم_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->مجموعه_بالا_Color(ConvertColorType(a_متن_Color));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(فراغ)aSelectedColor;
	}

	فراغ
	مجموعه_Background_Color(ثابت SDL_پیام_Box_Color *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->مجموعه_View_Color(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		پیدا_کن_View("TAlertView")->مجموعه_View_Color(background);
		f_پیام_Box_متن_View->مجموعه_View_Color(background);
	}

	منطقي
	Check_Long_سطرها(ثابت حرف *a_پیام)
	{
		صحيح final = 0;

		// This UTF-8 friendly.
		BString پیام = a_پیام;
		int32 درازی = پیام.شمار_Chars();

		لكل (صحيح i = 0, c = 0; i < درازی; ++i) {
			c++;
			إذا (*(پیام.CharAt(i)) == '\n') {
				c = 0;
			}
			إذا (c > final) {
				final = c;
			}
		}

		أرجع (final > G_MAX_STRING_درازی_بایتها);
	}

	فراغ
	مجموعه_پیام_متن(ثابت حرف *a_پیام)
	{
		f_There_Is_Long_سطر = Check_Long_سطرها(a_پیام);
		إذا (f_There_Is_Long_سطر) {
			f_پیام_Box_متن_View->مجموعه_کلمه_Wrap(درست);
		}

		rgb_color متن_Color = ui_color(B_PANEL_متن_COLOR);
		إذا (fCustomColorScheme) {
			متن_Color = f_متن_Color;
		}

		/*
		if (fNoTitledWindow) {
			fMessageBoxTextView->SetFontAndColor(be_bold_font);
			fMessageBoxTextView->Insert(fTitle);
			fMessageBoxTextView->Insert("\n\n");
			fMessageBoxTextView->SetFontAndColor(be_plain_font);
		}
		*/

		f_پیام_Box_متن_View->مجموعه_Font_And_Color(be_plain_font, B_FONT_ALL, &متن_Color);
		f_پیام_Box_متن_View->درج(a_پیام);

		// Be sure to call update width method.
		Update_متن_View_عرض();
	}

	فراغ
	جمع_کن_Sdl_Buttons(ثابت SDL_پیام_Box_Button_داده *aButtons, صحيح a_رقم_Buttons)
	{
		لكل (صحيح i = 0; i < a_رقم_Buttons; ++i) {
			fButtons.افزودن_پشت(&aButtons[i]);
		}

		std::مرتب_سازی(fButtons.begin(), fButtons.انتها(), &HAIKU_SDL_پیام_Box::مرتب_سازی_Buttons_Predicate);

		size_t شمار_Buttons = fButtons.اندازه();
		لكل (size_t i = 0; i < شمار_Buttons; ++i) {
			إذا (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<صحيح>(i);
            }
			إذا (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<صحيح>(i);
            }
			جمع_کن_Button(fButtons[i]->متن);
		}

		مجموعه_Default_Button(ButtonAt(fDefaultButton));
	}

عام:
	صریح
	HAIKU_SDL_پیام_Box(ثابت SDL_پیام_Box_داده *a_پیام_Box_داده)
		: BAlert(عدم, عدم, عدم, عدم, عدم, B_عرض_FROM_LABEL, B_WARNING_ALERT),
		  f_Computed_پیام_Box_عرض(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(خطأ), f_There_Is_Long_سطر(خطأ),
		  HAIKU_SDL_DefTitle("SDL MessageBox"),
		  HAIKU_SDL_Def_پیام("Some information has been lost."),
		  HAIKU_SDL_DefButton("OK")
	{
		// MessageBox settings.
		// We need a title to display it.
		مجموعه_Look(B_TITLED_پنجره_LOOK);
		مجموعه_Flags(Flags() | B_CLOSE_ON_ESCAPE);

		// MessageBox TextView settings.
		f_پیام_Box_متن_View = متن_View();
		f_پیام_Box_متن_View->مجموعه_کلمه_Wrap(خطأ);
		f_پیام_Box_متن_View->مجموعه_Stylable(درست);

		Parse_Sdl_پیام_Box_داده(a_پیام_Box_داده);
	}

	صحيح
	GetCloseButtonId(فراغ) ثابت
	{
		أرجع fCloseButton;
	}

	مجازی
	~HAIKU_SDL_پیام_Box(فراغ)
	{
		fButtons.clear();
	}

محمي:
	مجازی فراغ
	قاب_Resized(عائم a_New_عرض, عائم a_New_ارتفاع)
	{
		إذا (f_Computed_پیام_Box_عرض > a_New_عرض) {
			Resize_مقصد(f_Computed_پیام_Box_عرض, a_New_ارتفاع);
		} وإلا {
			BAlert::قاب_Resized(a_New_عرض, a_New_ارتفاع);
		}
	}

	مجازی فراغ
	مجموعه_Title_2(ثابت حرف *aTitle)
	{
		fTitle = aTitle;
		BAlert::مجموعه_Title_2(aTitle);
	}
};

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

منطقي HAIKU_Show_پیام_Box(ثابت SDL_پیام_Box_داده *messageboxdata, صحيح *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	إذا (!be_app) {
		application = std::unique_ptr<BApplication>(جديد(std::nothrow) BApplication(SDL_signature));
		إذا (!application) {
			أرجع SDL_مجموعه_Error("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_پیام_Box *SDL_پیام_Box = جديد(std::nothrow) HAIKU_SDL_پیام_Box(messageboxdata);
	إذا (!SDL_پیام_Box) {
		أرجع SDL_مجموعه_Error("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ثابت صحيح closeButton = SDL_پیام_Box->GetCloseButtonId();
	صحيح pushedButton = SDL_پیام_Box->Go();

	// The close button is equivalent to pressing Escape.
	إذا (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
		pushedButton = closeButton;
	}

	// It's deleted by itself after the "Go()" method was executed.
	/*
	if (messageBox != NULL) {
		delete messageBox;
	}
	*/
	// Initialize button by real pushed value then.
	*buttonID = pushedButton;

	أرجع درست;
}

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر // SDL_VIDEO_DRIVER_HAIKU
