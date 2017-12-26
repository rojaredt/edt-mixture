#ifndef LOG_VIEW_HPP
#define LOG_VIEW_HPP

#include <gui_generated/log_screen/LogViewBase.hpp>
#include <gui/log_screen/LogPresenter.hpp>

class LogView : public LogViewBase
{
public:
  LogView();
  virtual ~LogView() {}
  
  virtual void setupScreen();
  virtual void tearDownScreen();    
  virtual void handleTickEvent();
  
  void showLogList(uint16_t *data);
protected:
private:
  uint8_t firstTime;
  
  Unicode::UnicodeChar name_01[13] = {0};
  Unicode::UnicodeChar time_01[20] = {0};
  
  uint16_t convertPosToHex(uint16_t num, uint16_t pos);
};

#endif // LOG_VIEW_HPP
