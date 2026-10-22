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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#ಅನ್ತರ್ಭಾವ "../../core/haiku/SDL_BeApp.h"

#ಅನ್ತರ್ಭಾವ <Alert.h>
#ಅನ್ತರ್ಭಾವ <Application.h>
#ಅನ್ತರ್ಭಾವ <Button.h>
#ಅನ್ತರ್ಭಾವ <Font.h>
#ಅನ್ತರ್ಭಾವ <Layout.h>
#ಅನ್ತರ್ಭಾವ <String.h>
#ಅನ್ತರ್ಭಾವ <TextView.h>
#ಅನ್ತರ್ಭಾವ <View.h>
#ಅನ್ತರ್ಭಾವ <Window.h>

#ಅನ್ತರ್ಭಾವ <InterfaceDefs.h>
#ಅನ್ತರ್ಭಾವ <SupportDefs.h>
#ಅನ್ತರ್ಭಾವ <GraphicsDefs.h>

#ಅನ್ತರ್ಭಾವ <new>
#ಅನ್ತರ್ಭಾವ <vector>
#ಅನ್ತರ್ಭಾವ <algorithm>
#ಅನ್ತರ್ಭಾವ <memory>

ಎಣಿಕೆ
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_ಉದ್ದಳತೆ_ಬೈಟುಗಳು = 120
};

ವರ್ಗ HAIKU_SDL_ಸಂದೇಶ_Box : ಸಾರ್ವಜನಿಕ BAlert
{
	ದಶಮಾಂಶ f_Computed_ಸಂದೇಶ_Box_ಅಗಲ;

	BTextView *f_ಸಂದೇಶ_Box_ಪಠ್ಯ_View;

	ಪೂರ್ಣಾಂಕ fCloseButton;
	ಪೂರ್ಣಾಂಕ fDefaultButton;

	ತಾರ್ಕಿಕ fCustomColorScheme;
	ತಾರ್ಕಿಕ f_There_Is_Long_ಸಾಲು;
	rgb_color f_ಪಠ್ಯ_Color;

	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fTitle;
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *HAIKU_SDL_DefTitle;
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *HAIKU_SDL_Def_ಸಂದೇಶ;
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *HAIKU_SDL_DefButton;

	std::ಸದಿಶ<ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Button_ದತ್ತಾಂಶ *> fButtons;

	ಸ್ಥಿರ ತಾರ್ಕಿಕ
	ವಿಂಗಡಿಸು_Buttons_Predicate(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Button_ದತ್ತಾಂಶ *a_Button_ಎಡ,
	                                 ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Button_ದತ್ತಾಂಶ *a_Button_ಬಲ)
	{
		ಹಿಂತಿರುಗಿ a_Button_ಎಡ->buttonID < a_Button_ಬಲ->buttonID;
	}

	alert_type
	Convert_ಸಂದೇಶ_Box_Type(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Flags a_ಕಿಟಕಿ_Type) ಸ್ಥಿರಾಂಕ
	{
		ಆಯ್ಕೆ (a_ಕಿಟಕಿ_Type)
		{
			ಪೂರ್ವನಿಯೋಜಿತ:
			ಸ್ಥಿತಿ SDL_MESSAGEBOX_WARNING:
			{
				ಹಿಂತಿರುಗಿ B_WARNING_ALERT;
			}
			ಸ್ಥಿತಿ SDL_MESSAGEBOX_ERROR:
			{
				ಹಿಂತಿರುಗಿ B_STOP_ALERT;
			}
			ಸ್ಥಿತಿ SDL_MESSAGEBOX_INFORMATION:
			{
				ಹಿಂತಿರುಗಿ B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color *aColor) ಸ್ಥಿರಾಂಕ
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		ಹಿಂತಿರುಗಿ color;
	}

	int32
	Get_ಎಡ_Panel_ಅಗಲ(ಶೂನ್ಯ) ಸ್ಥಿರಾಂಕ
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->ಗಾತ್ರ_3() + 15) / 16);
		ಹಿಂತಿರುಗಿ (30 * scale) + (32 * scale);
	}

	ಶೂನ್ಯ
	Update_ಪಠ್ಯ_View_ಅಗಲ(ಶೂನ್ಯ)
	{
		f_Computed_ಸಂದೇಶ_Box_ಅಗಲ = f_ಸಂದೇಶ_Box_ಪಠ್ಯ_View->Preferred_ಗಾತ್ರ().ಅಗಲ_2() + Get_ಎಡ_Panel_ಅಗಲ();
	}

	ಶೂನ್ಯ
	Parse_Sdl_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ)
	{
		ಆದರೆ (a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ == ಖಾಲಿ) {
			ಗಣ_Title_2(HAIKU_SDL_DefTitle);
			ಗಣ_ಸಂದೇಶ_ಪಠ್ಯ(HAIKU_SDL_Def_ಸಂದೇಶ);
			ಕೂಡಿಸು_Button(HAIKU_SDL_DefButton);
			ಹಿಂತಿರುಗಿ;
		}

		ಆದರೆ (a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ->numbuttons <= 0) {
			ಕೂಡಿಸು_Button(HAIKU_SDL_DefButton);
		} ಇಲ್ಲದಿದ್ದರೆ {
			ಕೂಡಿಸು_Sdl_Buttons(a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ->buttons, a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ->numbuttons);
		}

		ಆದರೆ (a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ->colorScheme != ಖಾಲಿ) {
			fCustomColorScheme = ನಿಜ;
			ApplyAndParseColorScheme(a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ->colorScheme);
		}

		(a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ->title[0]) ?
			ಗಣ_Title_2(a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ->title) : ಗಣ_Title_2(HAIKU_SDL_DefTitle);
		(a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ->ಸಂದೇಶ[0]) ?
			ಗಣ_ಸಂದೇಶ_ಪಠ್ಯ(a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ->ಸಂದೇಶ) : ಗಣ_ಸಂದೇಶ_ಪಠ್ಯ(HAIKU_SDL_Def_ಸಂದೇಶ);

		ಗಣ_Type(Convert_ಸಂದೇಶ_Box_Type(a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ->flags));
	}

	ಶೂನ್ಯ
	ApplyAndParseColorScheme(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color_Scheme *aColorScheme)
	{
		ಗಣ_Background_Color(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		f_ಪಠ್ಯ_Color = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_ಪಠ್ಯ]);
		ಗಣ_Button_Colors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_ಪಠ್ಯ],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	ಶೂನ್ಯ
	ಗಣ_Button_Colors(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color *aBorderColor,
	                ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color *aBackgroundColor,
	                ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color *a_ಪಠ್ಯ_Color,
	                ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color *aSelectedColor)
	{
		ಆದರೆ (fCustomColorScheme) {
			int32 ಎಣಿಕೆ_Buttons = ಎಣಿಕೆ_Buttons_2();
			ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಎಣಿಕೆ_Buttons; ++i) {
				ButtonAt(i)->ಗಣ_View_Color(ConvertColorType(aBorderColor));
				ButtonAt(i)->ಗಣ_ಕೆಳಗಿನ_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->ಗಣ_ಮೇಲಿನ_Color(ConvertColorType(a_ಪಠ್ಯ_Color));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(ಶೂನ್ಯ)aSelectedColor;
	}

	ಶೂನ್ಯ
	ಗಣ_Background_Color(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->ಗಣ_View_Color(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		ಕಂಡುಹಿಡಿ_View("TAlertView")->ಗಣ_View_Color(background);
		f_ಸಂದೇಶ_Box_ಪಠ್ಯ_View->ಗಣ_View_Color(background);
	}

	ತಾರ್ಕಿಕ
	Check_Long_ಸಾಲುಗಳು(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *a_ಸಂದೇಶ)
	{
		ಪೂರ್ಣಾಂಕ final = 0;

		// This UTF-8 friendly.
		BString ಸಂದೇಶ = a_ಸಂದೇಶ;
		int32 ಉದ್ದಳತೆ = ಸಂದೇಶ.ಎಣಿಕೆ_Chars();

		ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0, c = 0; i < ಉದ್ದಳತೆ; ++i) {
			c++;
			ಆದರೆ (*(ಸಂದೇಶ.CharAt(i)) == '\n') {
				c = 0;
			}
			ಆದರೆ (c > final) {
				final = c;
			}
		}

		ಹಿಂತಿರುಗಿ (final > G_MAX_STRING_ಉದ್ದಳತೆ_ಬೈಟುಗಳು);
	}

	ಶೂನ್ಯ
	ಗಣ_ಸಂದೇಶ_ಪಠ್ಯ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *a_ಸಂದೇಶ)
	{
		f_There_Is_Long_ಸಾಲು = Check_Long_ಸಾಲುಗಳು(a_ಸಂದೇಶ);
		ಆದರೆ (f_There_Is_Long_ಸಾಲು) {
			f_ಸಂದೇಶ_Box_ಪಠ್ಯ_View->ಗಣ_ಶಬ್ದ_Wrap(ನಿಜ);
		}

		rgb_color ಪಠ್ಯ_Color = ui_color(B_PANEL_ಪಠ್ಯ_COLOR);
		ಆದರೆ (fCustomColorScheme) {
			ಪಠ್ಯ_Color = f_ಪಠ್ಯ_Color;
		}

		/*
		if (fNoTitledWindow) {
			fMessageBoxTextView->SetFontAndColor(be_bold_font);
			fMessageBoxTextView->Insert(fTitle);
			fMessageBoxTextView->Insert("\n\n");
			fMessageBoxTextView->SetFontAndColor(be_plain_font);
		}
		*/

		f_ಸಂದೇಶ_Box_ಪಠ್ಯ_View->ಗಣ_Font_And_Color(be_plain_font, B_FONT_ALL, &ಪಠ್ಯ_Color);
		f_ಸಂದೇಶ_Box_ಪಠ್ಯ_View->ಸೇರಿಸು(a_ಸಂದೇಶ);

		// Be sure to call update width method.
		Update_ಪಠ್ಯ_View_ಅಗಲ();
	}

	ಶೂನ್ಯ
	ಕೂಡಿಸು_Sdl_Buttons(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Button_ದತ್ತಾಂಶ *aButtons, ಪೂರ್ಣಾಂಕ a_ಅಂಕೆ_Buttons)
	{
		ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < a_ಅಂಕೆ_Buttons; ++i) {
			fButtons.ತಳ್ಳು_ಹಿಂಭಾಗ(&aButtons[i]);
		}

		std::ವಿಂಗಡಿಸು(fButtons.begin(), fButtons.ಕೊನೆ(), &HAIKU_SDL_ಸಂದೇಶ_Box::ವಿಂಗಡಿಸು_Buttons_Predicate);

		size_t ಎಣಿಕೆ_Buttons = fButtons.ಗಾತ್ರ_2();
		ಗಾಗಿ (size_t i = 0; i < ಎಣಿಕೆ_Buttons; ++i) {
			ಆದರೆ (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<ಪೂರ್ಣಾಂಕ>(i);
            }
			ಆದರೆ (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<ಪೂರ್ಣಾಂಕ>(i);
            }
			ಕೂಡಿಸು_Button(fButtons[i]->ಪಠ್ಯ);
		}

		ಗಣ_Default_Button(ButtonAt(fDefaultButton));
	}

ಸಾರ್ವಜನಿಕ:
	ಸ್ಪಷ್ಟ
	HAIKU_SDL_ಸಂದೇಶ_Box(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ)
		: BAlert(ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, B_ಅಗಲ_FROM_LABEL, B_WARNING_ALERT),
		  f_Computed_ಸಂದೇಶ_Box_ಅಗಲ(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(ಸುಳ್ಳು), f_There_Is_Long_ಸಾಲು(ಸುಳ್ಳು),
		  HAIKU_SDL_DefTitle("SDL MessageBox"),
		  HAIKU_SDL_Def_ಸಂದೇಶ("Some information has been lost."),
		  HAIKU_SDL_DefButton("OK")
	{
		// MessageBox settings.
		// We need a title to display it.
		ಗಣ_Look(B_TITLED_ಕಿಟಕಿ_LOOK);
		ಗಣ_Flags(Flags() | B_CLOSE_ON_ESCAPE);

		// MessageBox TextView settings.
		f_ಸಂದೇಶ_Box_ಪಠ್ಯ_View = ಪಠ್ಯ_View();
		f_ಸಂದೇಶ_Box_ಪಠ್ಯ_View->ಗಣ_ಶಬ್ದ_Wrap(ಸುಳ್ಳು);
		f_ಸಂದೇಶ_Box_ಪಠ್ಯ_View->ಗಣ_Stylable(ನಿಜ);

		Parse_Sdl_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ(a_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ);
	}

	ಪೂರ್ಣಾಂಕ
	GetCloseButtonId(ಶೂನ್ಯ) ಸ್ಥಿರಾಂಕ
	{
		ಹಿಂತಿರುಗಿ fCloseButton;
	}

	ವಾಸ್ತವಿಕ
	~HAIKU_SDL_ಸಂದೇಶ_Box(ಶೂನ್ಯ)
	{
		fButtons.clear();
	}

ಸಂರಕ್ಷಿತ:
	ವಾಸ್ತವಿಕ ಶೂನ್ಯ
	ಚೌಕಟ್ಟು_Resized(ದಶಮಾಂಶ a_New_ಅಗಲ, ದಶಮಾಂಶ a_New_ಎತ್ತರ)
	{
		ಆದರೆ (f_Computed_ಸಂದೇಶ_Box_ಅಗಲ > a_New_ಅಗಲ) {
			Resize_ಗಮ್ಯ(f_Computed_ಸಂದೇಶ_Box_ಅಗಲ, a_New_ಎತ್ತರ);
		} ಇಲ್ಲದಿದ್ದರೆ {
			BAlert::ಚೌಕಟ್ಟು_Resized(a_New_ಅಗಲ, a_New_ಎತ್ತರ);
		}
	}

	ವಾಸ್ತವಿಕ ಶೂನ್ಯ
	ಗಣ_Title_2(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *aTitle)
	{
		fTitle = aTitle;
		BAlert::ಗಣ_Title_2(aTitle);
	}
};

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

ತಾರ್ಕಿಕ HAIKU_Show_ಸಂದೇಶ_Box(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	ಆದರೆ (!be_app) {
		application = std::unique_ptr<BApplication>(ಹೊಸ(std::nothrow) BApplication(SDL_signature));
		ಆದರೆ (!application) {
			ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_ಸಂದೇಶ_Box *SDL_ಸಂದೇಶ_Box = ಹೊಸ(std::nothrow) HAIKU_SDL_ಸಂದೇಶ_Box(messageboxdata);
	ಆದರೆ (!SDL_ಸಂದೇಶ_Box) {
		ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ closeButton = SDL_ಸಂದೇಶ_Box->GetCloseButtonId();
	ಪೂರ್ಣಾಂಕ pushedButton = SDL_ಸಂದೇಶ_Box->Go();

	// The close button is equivalent to pressing Escape.
	ಆದರೆ (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	ಹಿಂತಿರುಗಿ ನಿಜ;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_HAIKU
