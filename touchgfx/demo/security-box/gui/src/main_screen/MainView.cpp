#include <gui/main_screen/MainView.hpp>

MainView::MainView()
	: checkAccountCallback(this, &MainView::checkAccountCallbackHandler)
{
	keyboard.setPosition(32, 44, 640, 392);
	keyboard.setCheckAccountAction(checkAccountCallback);
    add(keyboard);
}

void MainView::setupScreen()
{

}

void MainView::tearDownScreen()
{

}

void MainView::checkAccountCallbackHandler(bool valid)
{

}