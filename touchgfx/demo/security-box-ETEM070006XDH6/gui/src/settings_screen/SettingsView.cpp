#include <gui/settings_screen/SettingsView.hpp>

SettingsView::SettingsView()
{

}

void SettingsView::setupScreen()
{
	textAreaConfigIntro.setWideTextAction(WIDE_TEXT_CHARWRAP);
	textAreaConfigIntro.resizeHeightToCurrentText();
}

void SettingsView::tearDownScreen()
{

}

void SettingsView::clearUnlockLog()
{
	presenter->clearUnlockLog();
}