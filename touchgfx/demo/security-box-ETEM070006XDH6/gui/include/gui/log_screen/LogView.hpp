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
  
  Unicode::UnicodeChar name_02[13] = {0};
  Unicode::UnicodeChar time_02[20] = {0};
  
  Unicode::UnicodeChar name_03[13] = {0};
  Unicode::UnicodeChar time_03[20] = {0};
  
  Unicode::UnicodeChar name_04[13] = {0};
  Unicode::UnicodeChar time_04[20] = {0};
  
  Unicode::UnicodeChar name_05[13] = {0};
  Unicode::UnicodeChar time_05[20] = {0};
  
  Unicode::UnicodeChar name_06[13] = {0};
  Unicode::UnicodeChar time_06[20] = {0};
  
  Unicode::UnicodeChar name_07[13] = {0};
  Unicode::UnicodeChar time_07[20] = {0};
  
  Unicode::UnicodeChar name_08[13] = {0};
  Unicode::UnicodeChar time_08[20] = {0};
  
  uint16_t convertPosToHex(uint16_t num, uint16_t pos);
};

#endif // LOG_VIEW_HPP
