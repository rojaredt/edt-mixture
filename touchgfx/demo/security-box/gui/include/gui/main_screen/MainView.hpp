#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/common/CustomKeyboard.hpp>
#include <gui/common/Mask.hpp>
#include <touchgfx/containers/clock/DigitalClock.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

	virtual void handleTickEvent();
protected:
	DigitalClock digitalClock_;
	CustomKeyboard keyboard;
	Mask mask_;

	virtual void clickButtonLock();

	Callback<MainView, const bool> checkAccountCallback;
	void checkAccountCallbackHandler(bool valid);

private:
	int tickCounter_;
	int hours_;
	int minutes_;
	int seconds_;
};

#endif // MAIN_VIEW_HPP
