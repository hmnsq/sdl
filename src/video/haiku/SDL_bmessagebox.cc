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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#شامل "../../core/haiku/SDL_BeApp.h"

#شامل <Alert.h>
#شامل <Application.h>
#شامل <Button.h>
#شامل <Font.h>
#شامل <Layout.h>
#شامل <String.h>
#شامل <TextView.h>
#شامل <View.h>
#شامل <Window.h>

#شامل <InterfaceDefs.h>
#شامل <SupportDefs.h>
#شامل <GraphicsDefs.h>

#شامل <new>
#شامل <vector>
#شامل <algorithm>
#شامل <memory>

شمار
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_لمبائی_بائٹیں = 120
};

جماعت HAIKU_SDL_پیغام_Box : عوامی BAlert
{
	اعشاری f_Computed_پیغام_Box_چوڑائی;

	BTextView *f_پیغام_Box_متن_View;

	صحیح fCloseButton;
	صحیح fDefaultButton;

	منطقی fCustomColorScheme;
	منطقی f_There_Is_Long_سطر;
	rgb_color f_متن_Color;

	ثابت حرف *fTitle;
	ثابت حرف *HAIKU_SDL_DefTitle;
	ثابت حرف *HAIKU_SDL_Def_پیغام;
	ثابت حرف *HAIKU_SDL_DefButton;

	std::سمتیہ<ثابت SDL_پیغام_Box_Button_ڈیٹا *> fButtons;

	ساکن منطقی
	ترتیب_دو_Buttons_Predicate(ثابت SDL_پیغام_Box_Button_ڈیٹا *a_Button_بایاں,
	                                 ثابت SDL_پیغام_Box_Button_ڈیٹا *a_Button_دایاں)
	{
		واپس a_Button_بایاں->buttonID < a_Button_دایاں->buttonID;
	}

	alert_type
	Convert_پیغام_Box_Type(ثابت SDL_پیغام_Box_Flags a_کھڑکی_Type) ثابت
	{
		انتخاب (a_کھڑکی_Type)
		{
			طےشدہ:
			حالت SDL_MESSAGEBOX_WARNING:
			{
				واپس B_WARNING_ALERT;
			}
			حالت SDL_MESSAGEBOX_ERROR:
			{
				واپس B_STOP_ALERT;
			}
			حالت SDL_MESSAGEBOX_INFORMATION:
			{
				واپس B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(ثابت SDL_پیغام_Box_Color *aColor) ثابت
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		واپس color;
	}

	int32
	Get_بایاں_Panel_چوڑائی(خالی) ثابت
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->سائز_2() + 15) / 16);
		واپس (30 * scale) + (32 * scale);
	}

	خالی
	Update_متن_View_چوڑائی(خالی)
	{
		f_Computed_پیغام_Box_چوڑائی = f_پیغام_Box_متن_View->Preferred_سائز().چوڑائی_2() + Get_بایاں_Panel_چوڑائی();
	}

	خالی
	Parse_Sdl_پیغام_Box_ڈیٹا(ثابت SDL_پیغام_Box_ڈیٹا *a_پیغام_Box_ڈیٹا)
	{
		اگر (a_پیغام_Box_ڈیٹا == تہی) {
			سیٹ_Title_2(HAIKU_SDL_DefTitle);
			سیٹ_پیغام_متن(HAIKU_SDL_Def_پیغام);
			جوڑو_Button(HAIKU_SDL_DefButton);
			واپس;
		}

		اگر (a_پیغام_Box_ڈیٹا->numbuttons <= 0) {
			جوڑو_Button(HAIKU_SDL_DefButton);
		} ورنہ {
			جوڑو_Sdl_Buttons(a_پیغام_Box_ڈیٹا->buttons, a_پیغام_Box_ڈیٹا->numbuttons);
		}

		اگر (a_پیغام_Box_ڈیٹا->colorScheme != تہی) {
			fCustomColorScheme = سچ;
			ApplyAndParseColorScheme(a_پیغام_Box_ڈیٹا->colorScheme);
		}

		(a_پیغام_Box_ڈیٹا->title[0]) ?
			سیٹ_Title_2(a_پیغام_Box_ڈیٹا->title) : سیٹ_Title_2(HAIKU_SDL_DefTitle);
		(a_پیغام_Box_ڈیٹا->پیغام[0]) ?
			سیٹ_پیغام_متن(a_پیغام_Box_ڈیٹا->پیغام) : سیٹ_پیغام_متن(HAIKU_SDL_Def_پیغام);

		سیٹ_Type(Convert_پیغام_Box_Type(a_پیغام_Box_ڈیٹا->flags));
	}

	خالی
	ApplyAndParseColorScheme(ثابت SDL_پیغام_Box_Color_Scheme *aColorScheme)
	{
		سیٹ_Background_Color(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		f_متن_Color = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_متن]);
		سیٹ_Button_Colors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_متن],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	خالی
	سیٹ_Button_Colors(ثابت SDL_پیغام_Box_Color *aBorderColor,
	                ثابت SDL_پیغام_Box_Color *aBackgroundColor,
	                ثابت SDL_پیغام_Box_Color *a_متن_Color,
	                ثابت SDL_پیغام_Box_Color *aSelectedColor)
	{
		اگر (fCustomColorScheme) {
			int32 گنتی_Buttons = گنتی_Buttons_2();
			برائے (صحیح i = 0; i < گنتی_Buttons; ++i) {
				ButtonAt(i)->سیٹ_View_Color(ConvertColorType(aBorderColor));
				ButtonAt(i)->سیٹ_کم_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->سیٹ_بلند_Color(ConvertColorType(a_متن_Color));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(خالی)aSelectedColor;
	}

	خالی
	سیٹ_Background_Color(ثابت SDL_پیغام_Box_Color *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->سیٹ_View_Color(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		ڈھونڈو_View("TAlertView")->سیٹ_View_Color(background);
		f_پیغام_Box_متن_View->سیٹ_View_Color(background);
	}

	منطقی
	Check_Long_سطریں(ثابت حرف *a_پیغام)
	{
		صحیح final = 0;

		// This UTF-8 friendly.
		BString پیغام = a_پیغام;
		int32 لمبائی = پیغام.گنتی_Chars();

		برائے (صحیح i = 0, c = 0; i < لمبائی; ++i) {
			c++;
			اگر (*(پیغام.CharAt(i)) == '\n') {
				c = 0;
			}
			اگر (c > final) {
				final = c;
			}
		}

		واپس (final > G_MAX_STRING_لمبائی_بائٹیں);
	}

	خالی
	سیٹ_پیغام_متن(ثابت حرف *a_پیغام)
	{
		f_There_Is_Long_سطر = Check_Long_سطریں(a_پیغام);
		اگر (f_There_Is_Long_سطر) {
			f_پیغام_Box_متن_View->سیٹ_لفظ_Wrap(سچ);
		}

		rgb_color متن_Color = ui_color(B_PANEL_متن_COLOR);
		اگر (fCustomColorScheme) {
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

		f_پیغام_Box_متن_View->سیٹ_Font_And_Color(be_plain_font, B_FONT_ALL, &متن_Color);
		f_پیغام_Box_متن_View->داخل_کرو(a_پیغام);

		// Be sure to call update width method.
		Update_متن_View_چوڑائی();
	}

	خالی
	جوڑو_Sdl_Buttons(ثابت SDL_پیغام_Box_Button_ڈیٹا *aButtons, صحیح a_عدد_Buttons)
	{
		برائے (صحیح i = 0; i < a_عدد_Buttons; ++i) {
			fButtons.ڈالو_عقب(&aButtons[i]);
		}

		std::ترتیب_دو(fButtons.begin(), fButtons.انتہا(), &HAIKU_SDL_پیغام_Box::ترتیب_دو_Buttons_Predicate);

		size_t گنتی_Buttons = fButtons.سائز();
		برائے (size_t i = 0; i < گنتی_Buttons; ++i) {
			اگر (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<صحیح>(i);
            }
			اگر (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<صحیح>(i);
            }
			جوڑو_Button(fButtons[i]->متن);
		}

		سیٹ_Default_Button(ButtonAt(fDefaultButton));
	}

عوامی:
	صریح
	HAIKU_SDL_پیغام_Box(ثابت SDL_پیغام_Box_ڈیٹا *a_پیغام_Box_ڈیٹا)
		: BAlert(تہی, تہی, تہی, تہی, تہی, B_چوڑائی_FROM_LABEL, B_WARNING_ALERT),
		  f_Computed_پیغام_Box_چوڑائی(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(جھوٹ), f_There_Is_Long_سطر(جھوٹ),
		  HAIKU_SDL_DefTitle("SDL MessageBox"),
		  HAIKU_SDL_Def_پیغام("Some information has been lost."),
		  HAIKU_SDL_DefButton("OK")
	{
		// MessageBox settings.
		// We need a title to display it.
		سیٹ_Look(B_TITLED_کھڑکی_LOOK);
		سیٹ_Flags(Flags() | B_CLOSE_ON_ESCAPE);

		// MessageBox TextView settings.
		f_پیغام_Box_متن_View = متن_View();
		f_پیغام_Box_متن_View->سیٹ_لفظ_Wrap(جھوٹ);
		f_پیغام_Box_متن_View->سیٹ_Stylable(سچ);

		Parse_Sdl_پیغام_Box_ڈیٹا(a_پیغام_Box_ڈیٹا);
	}

	صحیح
	GetCloseButtonId(خالی) ثابت
	{
		واپس fCloseButton;
	}

	مجازی
	~HAIKU_SDL_پیغام_Box(خالی)
	{
		fButtons.clear();
	}

محفوظ:
	مجازی خالی
	چوکھٹا_Resized(اعشاری a_New_چوڑائی, اعشاری a_New_اونچائی)
	{
		اگر (f_Computed_پیغام_Box_چوڑائی > a_New_چوڑائی) {
			Resize_مقصد(f_Computed_پیغام_Box_چوڑائی, a_New_اونچائی);
		} ورنہ {
			BAlert::چوکھٹا_Resized(a_New_چوڑائی, a_New_اونچائی);
		}
	}

	مجازی خالی
	سیٹ_Title_2(ثابت حرف *aTitle)
	{
		fTitle = aTitle;
		BAlert::سیٹ_Title_2(aTitle);
	}
};

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

منطقی HAIKU_Show_پیغام_Box(ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	اگر (!be_app) {
		application = std::unique_ptr<BApplication>(نیا(std::nothrow) BApplication(SDL_signature));
		اگر (!application) {
			واپس SDL_سیٹ_Error("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_پیغام_Box *SDL_پیغام_Box = نیا(std::nothrow) HAIKU_SDL_پیغام_Box(messageboxdata);
	اگر (!SDL_پیغام_Box) {
		واپس SDL_سیٹ_Error("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ثابت صحیح closeButton = SDL_پیغام_Box->GetCloseButtonId();
	صحیح pushedButton = SDL_پیغام_Box->Go();

	// The close button is equivalent to pressing Escape.
	اگر (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	واپس سچ;
}

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم // SDL_VIDEO_DRIVER_HAIKU
