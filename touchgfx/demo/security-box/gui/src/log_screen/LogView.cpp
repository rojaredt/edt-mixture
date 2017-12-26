#include <gui/log_screen/LogView.hpp>

LogView::LogView(): firstTime(0)
{
  
}

void LogView::setupScreen()
{
  //textAreaMainNo1.setVisible(false);
  //textAreaMainNo2.setVisible(false);
  //textAreaMainNo3.setVisible(false);
  //textAreaMainNo4.setVisible(false);
  //textAreaMainNo5.setVisible(false);
  //textAreaMainNo6.setVisible(false);
  //textAreaMainNo7.setVisible(false);
  //textAreaMainNo8.setVisible(false);
  
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
  textAreaMainName2.setWildcard(name_02);
  textAreaMainTime2.setWildcard(time_02);
  textAreaMainName3.setWildcard(name_03);
  textAreaMainTime3.setWildcard(time_03);
  textAreaMainName4.setWildcard(name_04);
  textAreaMainTime4.setWildcard(time_04);
  textAreaMainName5.setWildcard(name_05);
  textAreaMainTime5.setWildcard(time_05);
  textAreaMainName6.setWildcard(name_06);
  textAreaMainTime6.setWildcard(time_06);
  textAreaMainName7.setWildcard(name_07);
  textAreaMainTime7.setWildcard(time_07);
  textAreaMainName8.setWildcard(name_08);
  textAreaMainTime8.setWildcard(time_08);  
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
  Unicode::UnicodeChar name[13] = {0};
  Unicode::UnicodeChar time[20] = {0};
  
  //1
  if (*(data + bidx) != 0 && *(data + bidx) != 0xFFFF)
  {
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
    textAreaMainName1.invalidate();
    textAreaMainTime1.invalidate();    
  }
  
  bidx += 20;
  
  //2
  if (*(data + bidx) != 0 && *(data + bidx) != 0xFFFF)
  {
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
    
    textAreaMainName2.setVisible(true);
    textAreaMainTime2.setVisible(true);
    Unicode::snprintf(name_02, 13, "%s", name);
    Unicode::snprintf(time_02, 20, "%s", time);  
    textAreaMainName2.resizeToCurrentText();
    textAreaMainTime2.resizeToCurrentText();  
    textAreaMainName2.invalidate();
    textAreaMainTime2.invalidate();
  }
  
  bidx += 20;
  
  //3
  if (*(data + bidx) != 0 && *(data + bidx) != 0xFFFF)
  {
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
    textAreaMainName3.setVisible(true);
    textAreaMainTime3.setVisible(true);
    Unicode::snprintf(name_03, 13, "%s", name);
    Unicode::snprintf(time_03, 20, "%s", time);  
    textAreaMainName3.resizeToCurrentText();
    textAreaMainTime3.resizeToCurrentText();  
    textAreaMainName3.invalidate();
    textAreaMainTime3.invalidate();
  }
  
  bidx += 20;
  
  //4
  if (*(data + bidx) != 0 && *(data + bidx) != 0xFFFF)
  {
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
    textAreaMainName4.setVisible(true);
    textAreaMainTime4.setVisible(true);
    Unicode::snprintf(name_04, 13, "%s", name);
    Unicode::snprintf(time_04, 20, "%s", time);  
    textAreaMainName4.resizeToCurrentText();
    textAreaMainTime4.resizeToCurrentText();  
    textAreaMainName4.invalidate();
    textAreaMainTime4.invalidate();
  }
  
  bidx += 20;
  
  //5
  if (*(data + bidx) != 0 && *(data + bidx) != 0xFFFF)
  {
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
    textAreaMainName5.setVisible(true);
    textAreaMainTime5.setVisible(true);
    Unicode::snprintf(name_05, 13, "%s", name);
    Unicode::snprintf(time_05, 20, "%s", time);  
    textAreaMainName5.resizeToCurrentText();
    textAreaMainTime5.resizeToCurrentText();  
    textAreaMainName5.invalidate();
    textAreaMainTime5.invalidate();
  }
  
  bidx += 20;
  
  //6
  if (*(data + bidx) != 0 && *(data + bidx) != 0xFFFF)
  {
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
    textAreaMainName6.setVisible(true);
    textAreaMainTime6.setVisible(true);
    Unicode::snprintf(name_06, 13, "%s", name);
    Unicode::snprintf(time_06, 20, "%s", time);  
    textAreaMainName6.resizeToCurrentText();
    textAreaMainTime6.resizeToCurrentText();  
    textAreaMainName6.invalidate();
    textAreaMainTime6.invalidate();
  }
  
  bidx += 20;
  
  //7
  if (*(data + bidx) != 0 && *(data + bidx) != 0xFFFF)
  {
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
    textAreaMainName7.setVisible(true);
    textAreaMainTime7.setVisible(true);
    Unicode::snprintf(name_07, 13, "%s", name);
    Unicode::snprintf(time_07, 20, "%s", time);  
    textAreaMainName7.resizeToCurrentText();
    textAreaMainTime7.resizeToCurrentText();  
    textAreaMainName7.invalidate();
    textAreaMainTime7.invalidate();
  }
  
  bidx += 20;
  
  //8
  if (*(data + bidx) != 0 && *(data + bidx) != 0xFFFF)
  {
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
    
    textAreaMainName8.setVisible(true);
    textAreaMainTime8.setVisible(true);
    Unicode::snprintf(name_08, 13, "%s", name);
    Unicode::snprintf(time_08, 20, "%s", time);  
    textAreaMainName8.resizeToCurrentText();
    textAreaMainTime8.resizeToCurrentText();  
    textAreaMainName8.invalidate();
    textAreaMainTime8.invalidate();
  }
  
  bidx += 20;
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