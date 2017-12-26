#include <gui/log_screen/LogView.hpp>

LogView::LogView(): firstTime(0)
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
  
  textAreaMainName1.setWildcard(name_01);
  textAreaMainTime1.setWildcard(time_01);
  
  //  presenter->readLoginRecord();
}

void LogView::tearDownScreen()
{
  
}

void LogView::handleTickEvent()
{
  if(firstTime == 0) 
  {
    presenter->readLoginRecord();
    
    firstTime = 1;
  }
}

void LogView::showLogList(uint16_t *data)
{
  int bidx = 4;
  int idx = 0;  
  int idx2 = 0;
  //int len = 4 + (20 * 8);
  Unicode::UnicodeChar name[13] = {0};
  Unicode::UnicodeChar time[20] = {0};
  
  //1
  idx = 0;
  memset(name, 0, 12);
  memset(time, 0, 19);
  while(idx < 12)
  {
    name[idx] = *(data + bidx + idx);
    idx++;
  }  
  while(idx < 18)
  {
    if(idx == 12)
    {
      int16_t year = *(data + bidx + idx);
      time[0] = convertPosToHex(year ,4) + 48;
      time[1] = convertPosToHex(year ,3) + 48;
      time[2] = convertPosToHex(year ,2) + 48;
      time[3] = convertPosToHex(year ,1) + 48;
    }
    else if(idx == 13)
    {
      time[4] = 0x2D;
      int16_t month = *(data + bidx + idx);
      time[5] = convertPosToHex(month ,2) + 48;
      time[6] = convertPosToHex(month ,1) + 48;
    }
    else if(idx == 14)
    {
      time[7] = 0x2D;
      int16_t day = *(data + bidx + idx);
      time[8] = convertPosToHex(day ,2) + 48;
      time[9] = convertPosToHex(day ,1) + 48;    
    }
    else if(idx == 15)
    {
      time[10] = 0x20;
      int16_t hour = *(data + bidx + idx);
      time[11] = convertPosToHex(hour ,2) + 48;
      time[12] = convertPosToHex(hour ,1) + 48;     
    }
    else if(idx == 16)
    {
      time[13] = 0x3A;
      int16_t min = *(data + bidx + idx);
      time[14] = convertPosToHex(min ,2) + 48;
      time[15] = convertPosToHex(min ,1) + 48;     
    }
    else if(idx == 17)
    {
      time[16] = 0x3A;
      int16_t sec = *(data + bidx + idx);
      time[17] = convertPosToHex(sec ,2) + 48;
      time[18] = convertPosToHex(sec ,1) + 48;     
    }
    
    idx++;
  }    
  
  textAreaMainName1.setVisible(true);
  textAreaMainTime1.setVisible(true);
  Unicode::snprintf(name_01, 13, "%s", name);
  Unicode::snprintf(time_01, 20, "%s", time);  
  textAreaMainName1.resizeToCurrentText();
  textAreaMainTime1.resizeToCurrentText();
  //textAreaMainTime1.setWidth(textAreaMainTime1.getWidth()+50);
  textAreaMainName1.invalidate();
  textAreaMainTime1.invalidate();
}

uint16_t LogView::convertPosToHex(uint16_t num, uint16_t pos)
{
  uint16_t r = 0;
  
  pos--;
  
  for(int i = 0; i < pos; i++)
  {
    num /= 10;
  }
  
  r = num % 10;
  
  return r;
}