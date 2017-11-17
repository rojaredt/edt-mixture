#include <gui/log_screen/LogView.hpp>

LogView::LogView()
{

}

void LogView::setupScreen()
{
	textAreaMainNo1.setVisible(false);
	textAreaMainNo2.setVisible(false);
	textAreaMainNo3.setVisible(false);
	textAreaMainNo4.setVisible(false);
	textAreaMainNo5.setVisible(false);
	textAreaMainNo6.setVisible(false);
	textAreaMainNo7.setVisible(false);
	textAreaMainNo8.setVisible(false);
	
	textAreaMainName1.setVisible(false);
	textAreaMainName2.setVisible(false);
	textAreaMainName3.setVisible(false);
	textAreaMainName4.setVisible(false);
	textAreaMainName5.setVisible(false);
	textAreaMainName6.setVisible(false);
	textAreaMainName7.setVisible(false);
	textAreaMainName8.setVisible(false);

	textAreaMainTime1.setVisible(false);
	textAreaMainTime2.setVisible(false);
	textAreaMainTime3.setVisible(false);
	textAreaMainTime4.setVisible(false);
	textAreaMainTime5.setVisible(false);
	textAreaMainTime6.setVisible(false);
	textAreaMainTime7.setVisible(false);
	textAreaMainTime8.setVisible(false);
}

void LogView::tearDownScreen()
{

}
