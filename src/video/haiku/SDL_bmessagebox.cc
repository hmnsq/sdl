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

#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#include "../../core/haiku/SDL_BeApp.h"

#include <Alert.h>
#include <Application.h>
#include <Button.h>
#include <Font.h>
#include <Layout.h>
#include <String.h>
#include <TextView.h>
#include <View.h>
#include <Window.h>

#include <InterfaceDefs.h>
#include <SupportDefs.h>
#include <GraphicsDefs.h>

#include <new>
#include <vector>
#include <algorithm>
#include <memory>

ga_nanaa
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_LENGTH_BYTES = 120
};

class HAIKU_SDL_MessageBox : public BAlert
{
	float fComputedMessageBoxWidth;

	BTextView *fMessageBoxTextView;

	පූර්ණ_සංඛ්‍යා fCloseButton;
	පූර්ණ_සංඛ්‍යා fDefaultButton;

	bool fCustomColorScheme;
	bool fThereIsLongLine;
	rgb_color fTextColor;

	const var_na *fTitle;
	const var_na *HAIKU_SDL_DefTitle;
	const var_na *HAIKU_SDL_DefMessage;
	const var_na *HAIKU_SDL_DefButton;

	std::vector<const SDL_MessageBoxButtonData *> fButtons;

	static bool
	SortButtonsPredicate(const SDL_MessageBoxButtonData *aButtonLeft,
	                                 const SDL_MessageBoxButtonData *aButtonRight)
	{
		ආපසු aButtonLeft->buttonID < aButtonRight->buttonID;
	}

	alert_type
	ConvertMessageBoxType(const SDL_MessageBoxFlags aWindowType) const
	{
		switch (aWindowType)
		{
			default:
			pak_sa SDL_MESSAGEBOX_WARNING:
			{
				ආපසු B_WARNING_ALERT;
			}
			pak_sa SDL_MESSAGEBOX_ERROR:
			{
				ආපසු B_STOP_ALERT;
			}
			pak_sa SDL_MESSAGEBOX_INFORMATION:
			{
				ආපසු B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(const SDL_MessageBoxColor *aColor) const
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		ආපසු color;
	}

	int32
	GetLeftPanelWidth(void) const
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16);
		ආපසු (30 * scale) + (32 * scale);
	}

	void
	UpdateTextViewWidth(void)
	{
		fComputedMessageBoxWidth = fMessageBoxTextView->PreferredSize().Width() + GetLeftPanelWidth();
	}

	void
	ParseSdlMessageBoxData(const SDL_MessageBoxData *aMessageBoxData)
	{
		නම් (aMessageBoxData == NULL) {
			SetTitle(HAIKU_SDL_DefTitle);
			SetMessageText(HAIKU_SDL_DefMessage);
			AddButton(HAIKU_SDL_DefButton);
			ආපසු;
		}

		නම් (aMessageBoxData->numbuttons <= 0) {
			AddButton(HAIKU_SDL_DefButton);
		} නැතහොත් {
			AddSdlButtons(aMessageBoxData->buttons, aMessageBoxData->numbuttons);
		}

		නම් (aMessageBoxData->colorScheme != NULL) {
			fCustomColorScheme = true;
			ApplyAndParseColorScheme(aMessageBoxData->colorScheme);
		}

		(aMessageBoxData->title[0]) ?
			SetTitle(aMessageBoxData->title) : SetTitle(HAIKU_SDL_DefTitle);
		(aMessageBoxData->message[0]) ?
			SetMessageText(aMessageBoxData->message) : SetMessageText(HAIKU_SDL_DefMessage);

		SetType(ConvertMessageBoxType(aMessageBoxData->flags));
	}

	void
	ApplyAndParseColorScheme(const SDL_MessageBoxColorScheme *aColorScheme)
	{
		SetBackgroundColor(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		SetButtonColors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	void
	SetButtonColors(const SDL_MessageBoxColor *aBorderColor,
	                const SDL_MessageBoxColor *aBackgroundColor,
	                const SDL_MessageBoxColor *aTextColor,
	                const SDL_MessageBoxColor *aSelectedColor)
	{
		නම් (fCustomColorScheme) {
			int32 countButtons = CountButtons();
			සඳහා (පූර්ණ_සංඛ්‍යා i = 0; i < countButtons; ++i) {
				ButtonAt(i)->SetViewColor(ConvertColorType(aBorderColor));
				ButtonAt(i)->SetLowColor(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->SetHighColor(ConvertColorType(aTextColor));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(void)aSelectedColor;
	}

	void
	SetBackgroundColor(const SDL_MessageBoxColor *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->SetViewColor(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->SetViewColor(background);
		fMessageBoxTextView->SetViewColor(background);
	}

	bool
	CheckLongLines(const var_na *aMessage)
	{
		පූර්ණ_සංඛ්‍යා final = 0;

		// This UTF-8 friendly.
		BString message = aMessage;
		int32 length = message.CountChars();

		සඳහා (පූර්ණ_සංඛ්‍යා i = 0, c = 0; i < length; ++i) {
			c++;
			නම් (*(message.CharAt(i)) == '\n') {
				c = 0;
			}
			නම් (c > final) {
				final = c;
			}
		}

		ආපසු (final > G_MAX_STRING_LENGTH_BYTES);
	}

	void
	SetMessageText(const var_na *aMessage)
	{
		fThereIsLongLine = CheckLongLines(aMessage);
		නම් (fThereIsLongLine) {
			fMessageBoxTextView->SetWordWrap(true);
		}

		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		නම් (fCustomColorScheme) {
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
		fMessageBoxTextView->Insert(aMessage);

		// Be sure to call update width method.
		UpdateTextViewWidth();
	}

	void
	AddSdlButtons(const SDL_MessageBoxButtonData *aButtons, පූර්ණ_සංඛ්‍යා aNumButtons)
	{
		සඳහා (පූර්ණ_සංඛ්‍යා i = 0; i < aNumButtons; ++i) {
			fButtons.push_back(&aButtons[i]);
		}

		std::sort(fButtons.begin(), fButtons.end(), &HAIKU_SDL_MessageBox::SortButtonsPredicate);

		size_t countButtons = fButtons.size();
		සඳහා (size_t i = 0; i < countButtons; ++i) {
			නම් (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<පූර්ණ_සංඛ්‍යා>(i);
            }
			නම් (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<පූර්ණ_සංඛ්‍යා>(i);
            }
			AddButton(fButtons[i]->text);
		}

		SetDefaultButton(ButtonAt(fDefaultButton));
	}

public:
	explicit
	HAIKU_SDL_MessageBox(const SDL_MessageBoxData *aMessageBoxData)
		: BAlert(NULL, NULL, NULL, NULL, NULL, B_WIDTH_FROM_LABEL, B_WARNING_ALERT),
		  fComputedMessageBoxWidth(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(false), fThereIsLongLine(false),
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
		fMessageBoxTextView->SetWordWrap(false);
		fMessageBoxTextView->SetStylable(true);

		ParseSdlMessageBoxData(aMessageBoxData);
	}

	පූර්ණ_සංඛ්‍යා
	GetCloseButtonId(void) const
	{
		ආපසු fCloseButton;
	}

	virtual
	~HAIKU_SDL_MessageBox(void)
	{
		fButtons.clear();
	}

rak_sita:
	virtual void
	FrameResized(float aNewWidth, float aNewHeight)
	{
		නම් (fComputedMessageBoxWidth > aNewWidth) {
			ResizeTo(fComputedMessageBoxWidth, aNewHeight);
		} නැතහොත් {
			BAlert::FrameResized(aNewWidth, aNewHeight);
		}
	}

	virtual void
	SetTitle(const var_na *aTitle)
	{
		fTitle = aTitle;
		BAlert::SetTitle(aTitle);
	}
};

#ifdef __cplusplus
extern "C" {
#endif

bool HAIKU_ShowMessageBox(const SDL_MessageBoxData *messageboxdata, පූර්ණ_සංඛ්‍යා *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	නම් (!be_app) {
		application = std::unique_ptr<BApplication>(new(std::nothrow) BApplication(SDL_signature));
		නම් (!application) {
			ආපසු SDL_SetError("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_MessageBox *SDL_MessageBox = new(std::nothrow) HAIKU_SDL_MessageBox(messageboxdata);
	නම් (!SDL_MessageBox) {
		ආපසු SDL_SetError("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	const පූර්ණ_සංඛ්‍යා closeButton = SDL_MessageBox->GetCloseButtonId();
	පූර්ණ_සංඛ්‍යා pushedButton = SDL_MessageBox->Go();

	// The close button is equivalent to pressing Escape.
	නම් (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	ආපසු true;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
