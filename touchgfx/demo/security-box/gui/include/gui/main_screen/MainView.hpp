#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/common/CustomKeyboard.hpp>
#include <gui/common/Mask.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
	CustomKeyboard keyboard;
	Mask mask_;

	virtual void clickButtonLock();

	Callback<MainView, const bool> checkAccountCallback;
	void checkAccountCallbackHandler(bool valid);
};

#endif // MAIN_VIEW_HPP
