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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/haiku/SDL_BeApp.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <Alert.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <Application.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <Button.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <Font.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <Layout.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <String.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <TextView.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <View.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <Window.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <InterfaceDefs.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <SupportDefs.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <GraphicsDefs.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <new>
#ਅਨ੍ਤਰ੍ਭਾਵ <vector>
#ਅਨ੍ਤਰ੍ਭਾਵ <algorithm>
#ਅਨ੍ਤਰ੍ਭਾਵ <memory>

ਗਿਣਤੀ
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_ਲੰਮਾਈ_ਬਾਈਟਾਂ = 120
};

ਵਰਗ HAIKU_SDL_ਸੁਨੇਹਾ_Box : ਜਨਤਕ BAlert
{
	ਦਸ਼ਮਲਵ f_Computed_ਸੁਨੇਹਾ_Box_ਚੌੜਾਈ;

	BTextView *f_ਸੁਨੇਹਾ_Box_ਪਾਠ_View;

	ਪੂਰਨ fCloseButton;
	ਪੂਰਨ fDefaultButton;

	ਤਾਰਕਿਕ fCustomColorScheme;
	ਤਾਰਕਿਕ f_There_Is_Long_ਸਤਰ;
	rgb_color f_ਪਾਠ_Color;

	ਅਚਲ ਅੱਖਰ *fTitle;
	ਅਚਲ ਅੱਖਰ *HAIKU_SDL_DefTitle;
	ਅਚਲ ਅੱਖਰ *HAIKU_SDL_Def_ਸੁਨੇਹਾ;
	ਅਚਲ ਅੱਖਰ *HAIKU_SDL_DefButton;

	std::ਸਦਿਸ਼<ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Button_ਅੰਕੜੇ *> fButtons;

	ਸਥਿਰ ਤਾਰਕਿਕ
	ਛਾਂਟੋ_Buttons_Predicate(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Button_ਅੰਕੜੇ *a_Button_ਖੱਬਾ,
	                                 ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Button_ਅੰਕੜੇ *a_Button_ਸੱਜਾ)
	{
		ਵਾਪਸ a_Button_ਖੱਬਾ->buttonID < a_Button_ਸੱਜਾ->buttonID;
	}

	alert_type
	Convert_ਸੁਨੇਹਾ_Box_Type(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Flags a_ਖਿੜਕੀ_Type) ਅਚਲ
	{
		ਚੋਣ (a_ਖਿੜਕੀ_Type)
		{
			ਮੂਲ:
			ਹਾਲਤ SDL_MESSAGEBOX_WARNING:
			{
				ਵਾਪਸ B_WARNING_ALERT;
			}
			ਹਾਲਤ SDL_MESSAGEBOX_ERROR:
			{
				ਵਾਪਸ B_STOP_ALERT;
			}
			ਹਾਲਤ SDL_MESSAGEBOX_INFORMATION:
			{
				ਵਾਪਸ B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color *aColor) ਅਚਲ
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		ਵਾਪਸ color;
	}

	int32
	Get_ਖੱਬਾ_Panel_ਚੌੜਾਈ(ਖਾਲੀ) ਅਚਲ
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->ਮਾਪ_2() + 15) / 16);
		ਵਾਪਸ (30 * scale) + (32 * scale);
	}

	ਖਾਲੀ
	Update_ਪਾਠ_View_ਚੌੜਾਈ(ਖਾਲੀ)
	{
		f_Computed_ਸੁਨੇਹਾ_Box_ਚੌੜਾਈ = f_ਸੁਨੇਹਾ_Box_ਪਾਠ_View->Preferred_ਮਾਪ().ਚੌੜਾਈ_2() + Get_ਖੱਬਾ_Panel_ਚੌੜਾਈ();
	}

	ਖਾਲੀ
	Parse_Sdl_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ)
	{
		ਜੇ (a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ == ਨਿਰਾ) {
			ਸੈੱਟ_Title_2(HAIKU_SDL_DefTitle);
			ਸੈੱਟ_ਸੁਨੇਹਾ_ਪਾਠ(HAIKU_SDL_Def_ਸੁਨੇਹਾ);
			ਜੋੜੋ_Button(HAIKU_SDL_DefButton);
			ਵਾਪਸ;
		}

		ਜੇ (a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ->numbuttons <= 0) {
			ਜੋੜੋ_Button(HAIKU_SDL_DefButton);
		} ਨਹੀਂਤਾਂ {
			ਜੋੜੋ_Sdl_Buttons(a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ->buttons, a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ->numbuttons);
		}

		ਜੇ (a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ->colorScheme != ਨਿਰਾ) {
			fCustomColorScheme = ਸੱਚ;
			ApplyAndParseColorScheme(a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ->colorScheme);
		}

		(a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ->title[0]) ?
			ਸੈੱਟ_Title_2(a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ->title) : ਸੈੱਟ_Title_2(HAIKU_SDL_DefTitle);
		(a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ->ਸੁਨੇਹਾ[0]) ?
			ਸੈੱਟ_ਸੁਨੇਹਾ_ਪਾਠ(a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ->ਸੁਨੇਹਾ) : ਸੈੱਟ_ਸੁਨੇਹਾ_ਪਾਠ(HAIKU_SDL_Def_ਸੁਨੇਹਾ);

		ਸੈੱਟ_Type(Convert_ਸੁਨੇਹਾ_Box_Type(a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ->flags));
	}

	ਖਾਲੀ
	ApplyAndParseColorScheme(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color_Scheme *aColorScheme)
	{
		ਸੈੱਟ_Background_Color(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		f_ਪਾਠ_Color = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_ਪਾਠ]);
		ਸੈੱਟ_Button_Colors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_ਪਾਠ],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	ਖਾਲੀ
	ਸੈੱਟ_Button_Colors(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color *aBorderColor,
	                ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color *aBackgroundColor,
	                ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color *a_ਪਾਠ_Color,
	                ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color *aSelectedColor)
	{
		ਜੇ (fCustomColorScheme) {
			int32 ਗਿਣਤੀ_Buttons = ਗਿਣਤੀ_Buttons_2();
			ਲਈ (ਪੂਰਨ i = 0; i < ਗਿਣਤੀ_Buttons; ++i) {
				ButtonAt(i)->ਸੈੱਟ_View_Color(ConvertColorType(aBorderColor));
				ButtonAt(i)->ਸੈੱਟ_ਨੀਵਾਂ_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->ਸੈੱਟ_ਉੱਚਾ_Color(ConvertColorType(a_ਪਾਠ_Color));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(ਖਾਲੀ)aSelectedColor;
	}

	ਖਾਲੀ
	ਸੈੱਟ_Background_Color(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->ਸੈੱਟ_View_Color(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		ਲੱਭੋ_View("TAlertView")->ਸੈੱਟ_View_Color(background);
		f_ਸੁਨੇਹਾ_Box_ਪਾਠ_View->ਸੈੱਟ_View_Color(background);
	}

	ਤਾਰਕਿਕ
	Check_Long_ਸਤਰਾਂ(ਅਚਲ ਅੱਖਰ *a_ਸੁਨੇਹਾ)
	{
		ਪੂਰਨ final = 0;

		// This UTF-8 friendly.
		BString ਸੁਨੇਹਾ = a_ਸੁਨੇਹਾ;
		int32 ਲੰਮਾਈ = ਸੁਨੇਹਾ.ਗਿਣਤੀ_Chars();

		ਲਈ (ਪੂਰਨ i = 0, c = 0; i < ਲੰਮਾਈ; ++i) {
			c++;
			ਜੇ (*(ਸੁਨੇਹਾ.CharAt(i)) == '\n') {
				c = 0;
			}
			ਜੇ (c > final) {
				final = c;
			}
		}

		ਵਾਪਸ (final > G_MAX_STRING_ਲੰਮਾਈ_ਬਾਈਟਾਂ);
	}

	ਖਾਲੀ
	ਸੈੱਟ_ਸੁਨੇਹਾ_ਪਾਠ(ਅਚਲ ਅੱਖਰ *a_ਸੁਨੇਹਾ)
	{
		f_There_Is_Long_ਸਤਰ = Check_Long_ਸਤਰਾਂ(a_ਸੁਨੇਹਾ);
		ਜੇ (f_There_Is_Long_ਸਤਰ) {
			f_ਸੁਨੇਹਾ_Box_ਪਾਠ_View->ਸੈੱਟ_ਸ਼ਬਦ_Wrap(ਸੱਚ);
		}

		rgb_color ਪਾਠ_Color = ui_color(B_PANEL_ਪਾਠ_COLOR);
		ਜੇ (fCustomColorScheme) {
			ਪਾਠ_Color = f_ਪਾਠ_Color;
		}

		/*
		if (fNoTitledWindow) {
			fMessageBoxTextView->SetFontAndColor(be_bold_font);
			fMessageBoxTextView->Insert(fTitle);
			fMessageBoxTextView->Insert("\n\n");
			fMessageBoxTextView->SetFontAndColor(be_plain_font);
		}
		*/

		f_ਸੁਨੇਹਾ_Box_ਪਾਠ_View->ਸੈੱਟ_Font_And_Color(be_plain_font, B_FONT_ALL, &ਪਾਠ_Color);
		f_ਸੁਨੇਹਾ_Box_ਪਾਠ_View->ਪਾਓ(a_ਸੁਨੇਹਾ);

		// Be sure to call update width method.
		Update_ਪਾਠ_View_ਚੌੜਾਈ();
	}

	ਖਾਲੀ
	ਜੋੜੋ_Sdl_Buttons(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Button_ਅੰਕੜੇ *aButtons, ਪੂਰਨ a_ਅੰਕ_Buttons)
	{
		ਲਈ (ਪੂਰਨ i = 0; i < a_ਅੰਕ_Buttons; ++i) {
			fButtons.ਧੱਕੋ_ਪਿੱਠ(&aButtons[i]);
		}

		std::ਛਾਂਟੋ(fButtons.begin(), fButtons.ਸਿਰਾ(), &HAIKU_SDL_ਸੁਨੇਹਾ_Box::ਛਾਂਟੋ_Buttons_Predicate);

		size_t ਗਿਣਤੀ_Buttons = fButtons.ਮਾਪ();
		ਲਈ (size_t i = 0; i < ਗਿਣਤੀ_Buttons; ++i) {
			ਜੇ (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<ਪੂਰਨ>(i);
            }
			ਜੇ (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<ਪੂਰਨ>(i);
            }
			ਜੋੜੋ_Button(fButtons[i]->ਪਾਠ);
		}

		ਸੈੱਟ_Default_Button(ButtonAt(fDefaultButton));
	}

ਜਨਤਕ:
	ਸਪਸ਼ਟ
	HAIKU_SDL_ਸੁਨੇਹਾ_Box(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ)
		: BAlert(ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, B_ਚੌੜਾਈ_FROM_LABEL, B_WARNING_ALERT),
		  f_Computed_ਸੁਨੇਹਾ_Box_ਚੌੜਾਈ(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(ਝੂਠ), f_There_Is_Long_ਸਤਰ(ਝੂਠ),
		  HAIKU_SDL_DefTitle("SDL MessageBox"),
		  HAIKU_SDL_Def_ਸੁਨੇਹਾ("Some information has been lost."),
		  HAIKU_SDL_DefButton("OK")
	{
		// MessageBox settings.
		// We need a title to display it.
		ਸੈੱਟ_Look(B_TITLED_ਖਿੜਕੀ_LOOK);
		ਸੈੱਟ_Flags(Flags() | B_CLOSE_ON_ESCAPE);

		// MessageBox TextView settings.
		f_ਸੁਨੇਹਾ_Box_ਪਾਠ_View = ਪਾਠ_View();
		f_ਸੁਨੇਹਾ_Box_ਪਾਠ_View->ਸੈੱਟ_ਸ਼ਬਦ_Wrap(ਝੂਠ);
		f_ਸੁਨੇਹਾ_Box_ਪਾਠ_View->ਸੈੱਟ_Stylable(ਸੱਚ);

		Parse_Sdl_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ(a_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ);
	}

	ਪੂਰਨ
	GetCloseButtonId(ਖਾਲੀ) ਅਚਲ
	{
		ਵਾਪਸ fCloseButton;
	}

	ਆਭਾਸੀ
	~HAIKU_SDL_ਸੁਨੇਹਾ_Box(ਖਾਲੀ)
	{
		fButtons.clear();
	}

ਸੁਰੱਖਿਅਤ:
	ਆਭਾਸੀ ਖਾਲੀ
	ਚੌਖਟਾ_Resized(ਦਸ਼ਮਲਵ a_New_ਚੌੜਾਈ, ਦਸ਼ਮਲਵ a_New_ਉਚਾਈ)
	{
		ਜੇ (f_Computed_ਸੁਨੇਹਾ_Box_ਚੌੜਾਈ > a_New_ਚੌੜਾਈ) {
			Resize_ਮੰਜ਼ਿਲ(f_Computed_ਸੁਨੇਹਾ_Box_ਚੌੜਾਈ, a_New_ਉਚਾਈ);
		} ਨਹੀਂਤਾਂ {
			BAlert::ਚੌਖਟਾ_Resized(a_New_ਚੌੜਾਈ, a_New_ਉਚਾਈ);
		}
	}

	ਆਭਾਸੀ ਖਾਲੀ
	ਸੈੱਟ_Title_2(ਅਚਲ ਅੱਖਰ *aTitle)
	{
		fTitle = aTitle;
		BAlert::ਸੈੱਟ_Title_2(aTitle);
	}
};

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

ਤਾਰਕਿਕ HAIKU_Show_ਸੁਨੇਹਾ_Box(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	ਜੇ (!be_app) {
		application = std::unique_ptr<BApplication>(ਨਵਾਂ(std::nothrow) BApplication(SDL_signature));
		ਜੇ (!application) {
			ਵਾਪਸ SDL_ਸੈੱਟ_Error("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_ਸੁਨੇਹਾ_Box *SDL_ਸੁਨੇਹਾ_Box = ਨਵਾਂ(std::nothrow) HAIKU_SDL_ਸੁਨੇਹਾ_Box(messageboxdata);
	ਜੇ (!SDL_ਸੁਨੇਹਾ_Box) {
		ਵਾਪਸ SDL_ਸੈੱਟ_Error("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ਅਚਲ ਪੂਰਨ closeButton = SDL_ਸੁਨੇਹਾ_Box->GetCloseButtonId();
	ਪੂਰਨ pushedButton = SDL_ਸੁਨੇਹਾ_Box->Go();

	// The close button is equivalent to pressing Escape.
	ਜੇ (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	ਵਾਪਸ ਸੱਚ;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_HAIKU
