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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#അന്തര്ഭാവ "../../core/haiku/SDL_BeApp.h"

#അന്തര്ഭാവ <Alert.h>
#അന്തര്ഭാവ <Application.h>
#അന്തര്ഭാവ <Button.h>
#അന്തര്ഭാവ <Font.h>
#അന്തര്ഭാവ <Layout.h>
#അന്തര്ഭാവ <String.h>
#അന്തര്ഭാവ <TextView.h>
#അന്തര്ഭാവ <View.h>
#അന്തര്ഭാവ <Window.h>

#അന്തര്ഭാവ <InterfaceDefs.h>
#അന്തര്ഭാവ <SupportDefs.h>
#അന്തര്ഭാവ <GraphicsDefs.h>

#അന്തര്ഭാവ <new>
#അന്തര്ഭാവ <vector>
#അന്തര്ഭാവ <algorithm>
#അന്തര്ഭാവ <memory>

എണ്ണൽ
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_LENGTH_BYTES = 120
};

വർഗ്ഗം HAIKU_SDL_MessageBox : പൊതു BAlert
{
	ദശാംശം fComputedMessageBoxWidth;

	BTextView *fMessageBoxTextView;

	പൂർണ്ണസംഖ്യ fCloseButton;
	പൂർണ്ണസംഖ്യ fDefaultButton;

	തർക്കം fCustomColorScheme;
	തർക്കം f_There_Is_Long_വരി;
	rgb_color fTextColor;

	സ്ഥിരം അക്ഷരം *fTitle;
	സ്ഥിരം അക്ഷരം *HAIKU_SDL_DefTitle;
	സ്ഥിരം അക്ഷരം *HAIKU_SDL_DefMessage;
	സ്ഥിരം അക്ഷരം *HAIKU_SDL_DefButton;

	std::vector<സ്ഥിരം SDL_MessageBoxButtonData *> fButtons;

	സ്ഥിതം തർക്കം
	SortButtonsPredicate(സ്ഥിരം SDL_MessageBoxButtonData *a_Button_ഇടത്,
	                                 സ്ഥിരം SDL_MessageBoxButtonData *a_Button_വലത്)
	{
		തിരികെ a_Button_ഇടത്->buttonID < a_Button_വലത്->buttonID;
	}

	alert_type
	ConvertMessageBoxType(സ്ഥിരം SDL_MessageBoxFlags aWindowType) സ്ഥിരം
	{
		തിരഞ്ഞെടുപ്പ് (aWindowType)
		{
			സ്ഥിരസ്ഥിതി:
			അവസ്ഥ SDL_MESSAGEBOX_WARNING:
			{
				തിരികെ B_WARNING_ALERT;
			}
			അവസ്ഥ SDL_MESSAGEBOX_ERROR:
			{
				തിരികെ B_STOP_ALERT;
			}
			അവസ്ഥ SDL_MESSAGEBOX_INFORMATION:
			{
				തിരികെ B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(സ്ഥിരം SDL_MessageBoxColor *aColor) സ്ഥിരം
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		തിരികെ color;
	}

	int32
	Get_ഇടത്_Panel_Width(ശൂന്യം) സ്ഥിരം
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16);
		തിരികെ (30 * scale) + (32 * scale);
	}

	ശൂന്യം
	UpdateTextViewWidth(ശൂന്യം)
	{
		fComputedMessageBoxWidth = fMessageBoxTextView->PreferredSize().Width() + Get_ഇടത്_Panel_Width();
	}

	ശൂന്യം
	ParseSdlMessageBoxData(സ്ഥിരം SDL_MessageBoxData *aMessageBoxData)
	{
		എങ്കിൽ (aMessageBoxData == ശൂന്യ) {
			SetTitle(HAIKU_SDL_DefTitle);
			SetMessageText(HAIKU_SDL_DefMessage);
			AddButton(HAIKU_SDL_DefButton);
			തിരികെ;
		}

		എങ്കിൽ (aMessageBoxData->numbuttons <= 0) {
			AddButton(HAIKU_SDL_DefButton);
		} അല്ലെങ്കിൽ {
			AddSdlButtons(aMessageBoxData->buttons, aMessageBoxData->numbuttons);
		}

		എങ്കിൽ (aMessageBoxData->colorScheme != ശൂന്യ) {
			fCustomColorScheme = സത്യം;
			ApplyAndParseColorScheme(aMessageBoxData->colorScheme);
		}

		(aMessageBoxData->title[0]) ?
			SetTitle(aMessageBoxData->title) : SetTitle(HAIKU_SDL_DefTitle);
		(aMessageBoxData->message[0]) ?
			SetMessageText(aMessageBoxData->message) : SetMessageText(HAIKU_SDL_DefMessage);

		SetType(ConvertMessageBoxType(aMessageBoxData->flags));
	}

	ശൂന്യം
	ApplyAndParseColorScheme(സ്ഥിരം SDL_MessageBoxColorScheme *aColorScheme)
	{
		SetBackgroundColor(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		SetButtonColors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	ശൂന്യം
	SetButtonColors(സ്ഥിരം SDL_MessageBoxColor *aBorderColor,
	                സ്ഥിരം SDL_MessageBoxColor *aBackgroundColor,
	                സ്ഥിരം SDL_MessageBoxColor *aTextColor,
	                സ്ഥിരം SDL_MessageBoxColor *aSelectedColor)
	{
		എങ്കിൽ (fCustomColorScheme) {
			int32 എണ്ണം_Buttons = എണ്ണം_Buttons_2();
			വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < എണ്ണം_Buttons; ++i) {
				ButtonAt(i)->SetViewColor(ConvertColorType(aBorderColor));
				ButtonAt(i)->Set_താഴെയുള്ള_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->Set_മുകളിലെ_Color(ConvertColorType(aTextColor));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(ശൂന്യം)aSelectedColor;
	}

	ശൂന്യം
	SetBackgroundColor(സ്ഥിരം SDL_MessageBoxColor *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->SetViewColor(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->SetViewColor(background);
		fMessageBoxTextView->SetViewColor(background);
	}

	തർക്കം
	Check_Long_വരികൾ(സ്ഥിരം അക്ഷരം *aMessage)
	{
		പൂർണ്ണസംഖ്യ final = 0;

		// This UTF-8 friendly.
		BString message = aMessage;
		int32 length = message.എണ്ണം_Chars();

		വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0, c = 0; i < length; ++i) {
			c++;
			എങ്കിൽ (*(message.CharAt(i)) == '\n') {
				c = 0;
			}
			എങ്കിൽ (c > final) {
				final = c;
			}
		}

		തിരികെ (final > G_MAX_STRING_LENGTH_BYTES);
	}

	ശൂന്യം
	SetMessageText(സ്ഥിരം അക്ഷരം *aMessage)
	{
		f_There_Is_Long_വരി = Check_Long_വരികൾ(aMessage);
		എങ്കിൽ (f_There_Is_Long_വരി) {
			fMessageBoxTextView->SetWordWrap(സത്യം);
		}

		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		എങ്കിൽ (fCustomColorScheme) {
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
		fMessageBoxTextView->തിരുകുക(aMessage);

		// Be sure to call update width method.
		UpdateTextViewWidth();
	}

	ശൂന്യം
	AddSdlButtons(സ്ഥിരം SDL_MessageBoxButtonData *aButtons, പൂർണ്ണസംഖ്യ a_അക്കം_Buttons)
	{
		വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < a_അക്കം_Buttons; ++i) {
			fButtons.തള്ളുക_back(&aButtons[i]);
		}

		std::sort(fButtons.begin(), fButtons.end(), &HAIKU_SDL_MessageBox::SortButtonsPredicate);

		size_t എണ്ണം_Buttons = fButtons.size();
		വേണ്ടി (size_t i = 0; i < എണ്ണം_Buttons; ++i) {
			എങ്കിൽ (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<പൂർണ്ണസംഖ്യ>(i);
            }
			എങ്കിൽ (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<പൂർണ്ണസംഖ്യ>(i);
            }
			AddButton(fButtons[i]->text);
		}

		SetDefaultButton(ButtonAt(fDefaultButton));
	}

പൊതു:
	explicit
	HAIKU_SDL_MessageBox(സ്ഥിരം SDL_MessageBoxData *aMessageBoxData)
		: BAlert(ശൂന്യ, ശൂന്യ, ശൂന്യ, ശൂന്യ, ശൂന്യ, B_WIDTH_FROM_LABEL, B_WARNING_ALERT),
		  fComputedMessageBoxWidth(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(അസത്യം), f_There_Is_Long_വരി(അസത്യം),
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
		fMessageBoxTextView->SetWordWrap(അസത്യം);
		fMessageBoxTextView->SetStylable(സത്യം);

		ParseSdlMessageBoxData(aMessageBoxData);
	}

	പൂർണ്ണസംഖ്യ
	GetCloseButtonId(ശൂന്യം) സ്ഥിരം
	{
		തിരികെ fCloseButton;
	}

	മായാ
	~HAIKU_SDL_MessageBox(ശൂന്യം)
	{
		fButtons.clear();
	}

സംരക്ഷിത:
	മായാ ശൂന്യം
	FrameResized(ദശാംശം aNewWidth, ദശാംശം aNewHeight)
	{
		എങ്കിൽ (fComputedMessageBoxWidth > aNewWidth) {
			ResizeTo(fComputedMessageBoxWidth, aNewHeight);
		} അല്ലെങ്കിൽ {
			BAlert::FrameResized(aNewWidth, aNewHeight);
		}
	}

	മായാ ശൂന്യം
	SetTitle(സ്ഥിരം അക്ഷരം *aTitle)
	{
		fTitle = aTitle;
		BAlert::SetTitle(aTitle);
	}
};

#ifdef __cplusplus
ബാഹ്യ "C" {
#endif

തർക്കം HAIKU_ShowMessageBox(സ്ഥിരം SDL_MessageBoxData *messageboxdata, പൂർണ്ണസംഖ്യ *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	എങ്കിൽ (!be_app) {
		application = std::unique_ptr<BApplication>(പുതിയ(std::nothrow) BApplication(SDL_signature));
		എങ്കിൽ (!application) {
			തിരികെ SDL_SetError("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_MessageBox *SDL_MessageBox = പുതിയ(std::nothrow) HAIKU_SDL_MessageBox(messageboxdata);
	എങ്കിൽ (!SDL_MessageBox) {
		തിരികെ SDL_SetError("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	സ്ഥിരം പൂർണ്ണസംഖ്യ closeButton = SDL_MessageBox->GetCloseButtonId();
	പൂർണ്ണസംഖ്യ pushedButton = SDL_MessageBox->Go();

	// The close button is equivalent to pressing Escape.
	എങ്കിൽ (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	തിരികെ സത്യം;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
