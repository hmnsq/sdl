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

#ifdef SDL_VIDEO_DRIVER_HAIKU


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

ಗಣನಾ
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_LENGTH_BYTES = 120
};

ವರ್ಗ HAIKU_SDL_MessageBox : ಸಾರ್ವಜನಿಕ BAlert
{
	ಭಿನ್ನ fComputedMessageBoxWidth;

	BTextView *fMessageBoxTextView;

	ಪೂರ್ಣಾಙ್ಕ fCloseButton;
	ಪೂರ್ಣಾಙ್ಕ fDefaultButton;

	ತಾರ್ಕಿಕ fCustomColorScheme;
	ತಾರ್ಕಿಕ f_There_Is_Long_ಸಾಲು;
	rgb_color fTextColor;

	ಧ್ರುವ ವರ್ಣ *fTitle;
	ಧ್ರುವ ವರ್ಣ *HAIKU_SDL_DefTitle;
	ಧ್ರುವ ವರ್ಣ *HAIKU_SDL_DefMessage;
	ಧ್ರುವ ವರ್ಣ *HAIKU_SDL_DefButton;

	std::vector<ಧ್ರುವ SDL_MessageBoxButtonData *> fButtons;

	ಸ್ಥಿರ ತಾರ್ಕಿಕ
	SortButtonsPredicate(ಧ್ರುವ SDL_MessageBoxButtonData *a_Button_ಎಡ,
	                                 ಧ್ರುವ SDL_MessageBoxButtonData *a_Button_ಬಲ)
	{
		ಪ್ರತ್ಯಾಗಮ a_Button_ಎಡ->buttonID < a_Button_ಬಲ->buttonID;
	}

	alert_type
	ConvertMessageBoxType(ಧ್ರುವ SDL_MessageBoxFlags aWindowType) ಧ್ರುವ
	{
		ವಿಕಲ್ಪ (aWindowType)
		{
			ಸ್ವಭಾವ:
			ಪಕ್ಷ SDL_MESSAGEBOX_WARNING:
			{
				ಪ್ರತ್ಯಾಗಮ B_WARNING_ALERT;
			}
			ಪಕ್ಷ SDL_MESSAGEBOX_ERROR:
			{
				ಪ್ರತ್ಯಾಗಮ B_STOP_ALERT;
			}
			ಪಕ್ಷ SDL_MESSAGEBOX_INFORMATION:
			{
				ಪ್ರತ್ಯಾಗಮ B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(ಧ್ರುವ SDL_MessageBoxColor *aColor) ಧ್ರುವ
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		ಪ್ರತ್ಯಾಗಮ color;
	}

	int32
	Get_ಎಡ_Panel_Width(ಶೂನ್ಯ) ಧ್ರುವ
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16);
		ಪ್ರತ್ಯಾಗಮ (30 * scale) + (32 * scale);
	}

	ಶೂನ್ಯ
	UpdateTextViewWidth(ಶೂನ್ಯ)
	{
		fComputedMessageBoxWidth = fMessageBoxTextView->PreferredSize().Width() + Get_ಎಡ_Panel_Width();
	}

	ಶೂನ್ಯ
	ParseSdlMessageBoxData(ಧ್ರುವ SDL_MessageBoxData *aMessageBoxData)
	{
		ಯದಿ (aMessageBoxData == ರಿಕ್ತ) {
			SetTitle(HAIKU_SDL_DefTitle);
			SetMessageText(HAIKU_SDL_DefMessage);
			AddButton(HAIKU_SDL_DefButton);
			ಪ್ರತ್ಯಾಗಮ;
		}

		ಯದಿ (aMessageBoxData->numbuttons <= 0) {
			AddButton(HAIKU_SDL_DefButton);
		} ಅನ್ಯಥಾ {
			AddSdlButtons(aMessageBoxData->buttons, aMessageBoxData->numbuttons);
		}

		ಯದಿ (aMessageBoxData->colorScheme != ರಿಕ್ತ) {
			fCustomColorScheme = ಸತ್ಯ;
			ApplyAndParseColorScheme(aMessageBoxData->colorScheme);
		}

		(aMessageBoxData->title[0]) ?
			SetTitle(aMessageBoxData->title) : SetTitle(HAIKU_SDL_DefTitle);
		(aMessageBoxData->message[0]) ?
			SetMessageText(aMessageBoxData->message) : SetMessageText(HAIKU_SDL_DefMessage);

		SetType(ConvertMessageBoxType(aMessageBoxData->flags));
	}

	ಶೂನ್ಯ
	ApplyAndParseColorScheme(ಧ್ರುವ SDL_MessageBoxColorScheme *aColorScheme)
	{
		SetBackgroundColor(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		SetButtonColors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	ಶೂನ್ಯ
	SetButtonColors(ಧ್ರುವ SDL_MessageBoxColor *aBorderColor,
	                ಧ್ರುವ SDL_MessageBoxColor *aBackgroundColor,
	                ಧ್ರುವ SDL_MessageBoxColor *aTextColor,
	                ಧ್ರುವ SDL_MessageBoxColor *aSelectedColor)
	{
		ಯದಿ (fCustomColorScheme) {
			int32 ಎಣಿಕೆ_Buttons = ಎಣಿಕೆ_Buttons_2();
			ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಎಣಿಕೆ_Buttons; ++i) {
				ButtonAt(i)->SetViewColor(ConvertColorType(aBorderColor));
				ButtonAt(i)->Set_ಕೆಳಗಿನ_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->Set_ಮೇಲಿನ_Color(ConvertColorType(aTextColor));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(ಶೂನ್ಯ)aSelectedColor;
	}

	ಶೂನ್ಯ
	SetBackgroundColor(ಧ್ರುವ SDL_MessageBoxColor *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->SetViewColor(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->SetViewColor(background);
		fMessageBoxTextView->SetViewColor(background);
	}

	ತಾರ್ಕಿಕ
	Check_Long_ಸಾಲುಗಳು(ಧ್ರುವ ವರ್ಣ *aMessage)
	{
		ಪೂರ್ಣಾಙ್ಕ final = 0;

		// This UTF-8 friendly.
		BString message = aMessage;
		int32 length = message.ಎಣಿಕೆ_Chars();

		ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0, c = 0; i < length; ++i) {
			c++;
			ಯದಿ (*(message.CharAt(i)) == '\n') {
				c = 0;
			}
			ಯದಿ (c > final) {
				final = c;
			}
		}

		ಪ್ರತ್ಯಾಗಮ (final > G_MAX_STRING_LENGTH_BYTES);
	}

	ಶೂನ್ಯ
	SetMessageText(ಧ್ರುವ ವರ್ಣ *aMessage)
	{
		f_There_Is_Long_ಸಾಲು = Check_Long_ಸಾಲುಗಳು(aMessage);
		ಯದಿ (f_There_Is_Long_ಸಾಲು) {
			fMessageBoxTextView->SetWordWrap(ಸತ್ಯ);
		}

		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		ಯದಿ (fCustomColorScheme) {
			textColor = fTextColor;
		}

		/*
		if (fNoTitledWindow) {
			fMessageBoxTextView->SetFontAndColor(be_bold_font);
			fMessageBoxTextView->Insert(fTitle);
			fMessageBoxTextView->Insert("\n\n");
			fMessageBoxTextView->SetFontAndColor(be_plain_font);
		}
		*/

		fMessageBoxTextView->SetFontAndColor(be_plain_font, B_FONT_ALL, &textColor);
		fMessageBoxTextView->ಸೇರಿಸು(aMessage);

		// Be sure to call update width method.
		UpdateTextViewWidth();
	}

	ಶೂನ್ಯ
	AddSdlButtons(ಧ್ರುವ SDL_MessageBoxButtonData *aButtons, ಪೂರ್ಣಾಙ್ಕ a_ಅಂಕೆ_Buttons)
	{
		ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < a_ಅಂಕೆ_Buttons; ++i) {
			fButtons.ತಳ್ಳು_back(&aButtons[i]);
		}

		std::sort(fButtons.begin(), fButtons.end(), &HAIKU_SDL_MessageBox::SortButtonsPredicate);

		size_t ಎಣಿಕೆ_Buttons = fButtons.size();
		ಪ್ರತಿ (size_t i = 0; i < ಎಣಿಕೆ_Buttons; ++i) {
			ಯದಿ (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<ಪೂರ್ಣಾಙ್ಕ>(i);
            }
			ಯದಿ (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<ಪೂರ್ಣಾಙ್ಕ>(i);
            }
			AddButton(fButtons[i]->text);
		}

		SetDefaultButton(ButtonAt(fDefaultButton));
	}

ಸಾರ್ವಜನಿಕ:
	explicit
	HAIKU_SDL_MessageBox(ಧ್ರುವ SDL_MessageBoxData *aMessageBoxData)
		: BAlert(ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, B_WIDTH_FROM_LABEL, B_WARNING_ALERT),
		  fComputedMessageBoxWidth(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(ಅಸತ್ಯ), f_There_Is_Long_ಸಾಲು(ಅಸತ್ಯ),
		  HAIKU_SDL_DefTitle("SDL MessageBox"),
		  HAIKU_SDL_DefMessage("Some information has been lost."),
		  HAIKU_SDL_DefButton("OK")
	{
		// MessageBox settings.
		// We need a title to display it.
		SetLook(B_TITLED_WINDOW_LOOK);
		SetFlags(Flags() | B_CLOSE_ON_ESCAPE);

		// MessageBox TextView settings.
		fMessageBoxTextView = TextView();
		fMessageBoxTextView->SetWordWrap(ಅಸತ್ಯ);
		fMessageBoxTextView->SetStylable(ಸತ್ಯ);

		ParseSdlMessageBoxData(aMessageBoxData);
	}

	ಪೂರ್ಣಾಙ್ಕ
	GetCloseButtonId(ಶೂನ್ಯ) ಧ್ರುವ
	{
		ಪ್ರತ್ಯಾಗಮ fCloseButton;
	}

	ಆಭಾಸ
	~HAIKU_SDL_MessageBox(ಶೂನ್ಯ)
	{
		fButtons.clear();
	}

ರಕ್ಷಿತ:
	ಆಭಾಸ ಶೂನ್ಯ
	FrameResized(ಭಿನ್ನ aNewWidth, ಭಿನ್ನ aNewHeight)
	{
		ಯದಿ (fComputedMessageBoxWidth > aNewWidth) {
			ResizeTo(fComputedMessageBoxWidth, aNewHeight);
		} ಅನ್ಯಥಾ {
			BAlert::FrameResized(aNewWidth, aNewHeight);
		}
	}

	ಆಭಾಸ ಶೂನ್ಯ
	SetTitle(ಧ್ರುವ ವರ್ಣ *aTitle)
	{
		fTitle = aTitle;
		BAlert::SetTitle(aTitle);
	}
};

#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
#endif

ತಾರ್ಕಿಕ HAIKU_ShowMessageBox(ಧ್ರುವ SDL_MessageBoxData *messageboxdata, ಪೂರ್ಣಾಙ್ಕ *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	ಯದಿ (!be_app) {
		application = std::unique_ptr<BApplication>(ನೂತನ(std::nothrow) BApplication(SDL_signature));
		ಯದಿ (!application) {
			ಪ್ರತ್ಯಾಗಮ SDL_SetError("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_MessageBox *SDL_MessageBox = ನೂತನ(std::nothrow) HAIKU_SDL_MessageBox(messageboxdata);
	ಯದಿ (!SDL_MessageBox) {
		ಪ್ರತ್ಯಾಗಮ SDL_SetError("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ closeButton = SDL_MessageBox->GetCloseButtonId();
	ಪೂರ್ಣಾಙ್ಕ pushedButton = SDL_MessageBox->Go();

	// The close button is equivalent to pressing Escape.
	ಯದಿ (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
