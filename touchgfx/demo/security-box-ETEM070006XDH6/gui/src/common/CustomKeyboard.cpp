#include <gui/common/CustomKeyboard.hpp>
#include <touchgfx/hal/HAL.hpp>

CustomKeyboard::CustomKeyboard() : 
  tick(0),
  keyboardNumberpad_(false),
  keyboard_(),
  capslockPressed_(this, &CustomKeyboard::capslockPressedHandler),
  backspacePressed_(this, &CustomKeyboard::backspacePressedHandler),
  modePressed_(this, &CustomKeyboard::modePressedHandler),
  enterUserPressed_(this, &CustomKeyboard::enterUserPressedHandler),
  enterPasswordPressed_(this, &CustomKeyboard::enterPasswordPressedHandler),
  keyPressed_(this, &CustomKeyboard::keyPressedhandler),
  alphaKeys_(true),
  uppercaseKeys_(false),
  firstCharacterEntry_(false)
  {
    //Set the callbacks for the callback areas of the keyboard and set its layout.
    layoutEnglish.callbackAreaArray[0].callback = &backspacePressed_;
    layoutEnglish.callbackAreaArray[1].callback = &enterUserPressed_;
    layoutNumberpad.callbackAreaArray[0].callback = &backspacePressed_;
    layoutNumberpad.callbackAreaArray[1].callback = &enterPasswordPressed_;
    
    keyboard_.setLayout(&layoutEnglish);
    keyboard_.setKeyListener(keyPressed_);
    keyboard_.setPosition(0, 0, backgraound_width_, backgraound_height_);
    keyboard_.setTextIndentation();
    //Allocate the buffer associated with keyboard.
    memset(buffer_, 0, sizeof(buffer_));
    keyboard_.setBuffer(buffer_, BUFFER_SIZE);
    
    uppercaseKeys_ = true;
    firstCharacterEntry_ = true;
       
    setKeyMappingList();
    
    cursor_.setPosition(cursor_begin_x_, cursor_begin_y_, cursor_width_x_, cursor_height_y_);
    cursor_.setColor(touchgfx::Color::getColorFrom24BitRGB(211, 145, 45));
    cursor_.setAlpha(255);
    
    message_.setPosition(cursor_begin_x_ + 20, cursor_begin_y_, 410, 60);
    message_.setWildcard(message_buffer_);
    message_.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    message_.setAlpha(100);
    message_.setLinespacing(0);
    message_.setTypedText(TypedText(T_ENTEREDTEXT));
    
    add(keyboard_);
    add(cursor_);
    add(message_);
    
    Unicode::UnicodeChar list[] = { 0x0055, 0x0053, 0x0045, 0x0052 };
    Unicode::snprintf(message_buffer_, 5, "%s", list);
    message_.invalidate();
    
    Application::getInstance()->registerTimerWidget(this);
  }
  
  void CustomKeyboard::setKeyMappingList()
  {
    if (alphaKeys_)
    {
      if (uppercaseKeys_)
      {
        keyboard_.setKeymappingList(&keyMappingListAlphaUpper);
      }
      else
      {
        keyboard_.setKeymappingList(&keyMappingListAlphaLower);
      }
    }
    else
    {
      if (uppercaseKeys_)
      {
        keyboard_.setKeymappingList(&keyMappingListNumUpper);
      }
      else
      {
        keyboard_.setKeymappingList(&keyMappingListNumLower);
      }
    }
  }
  
  void CustomKeyboard::backspacePressedHandler()
  {
    uint16_t pos = keyboard_.getBufferPosition();
    if (pos > 0)
    {
      //Delete the previous entry in the buffer and decrement the position.
      buffer_[pos - 1] = 0;
      keyboard_.setBufferPosition(pos - 1);
      
      //Change keymappings if we have reached the first position.
      if (1 == pos)
      {
        message_.setVisible(true);
        firstCharacterEntry_ = true;
      }
    }
    
    moveCursor();
  }
  
  void CustomKeyboard::capslockPressedHandler()
  {
    uppercaseKeys_ = !uppercaseKeys_;
    setKeyMappingList();
  }
  
  void CustomKeyboard::modePressedHandler()
  {
    alphaKeys_ = !alphaKeys_;
    
    // if we have changed back to alpha and still has no chars in the buffer,
    // we show upper case letters.
    if (firstCharacterEntry_ && alphaKeys_)
    {
      uppercaseKeys_ = true;
    }
    else
    {
      uppercaseKeys_ = false;
    }
    setKeyMappingList();
  }
  
  void CustomKeyboard::keyPressedhandler(Unicode::UnicodeChar keyChar)
  {
    // After the first keypress, the keyboard will shift to lowercase.
    if (firstCharacterEntry_ && keyChar != 0)
    {
      message_.setVisible(false);
      firstCharacterEntry_ = false;
      //uppercaseKeys = false;
      setKeyMappingList();
    }
    
    moveCursor();
  }
  
  void CustomKeyboard::enterUserPressedHandler()
  {
    HAL::getInstance()->blockCopy(bufferUser_, buffer_, 15 * sizeof(buffer_) / BUFFER_SIZE);
    
    keyboard_.setLayout(&layoutNumberpad);
    keyboard_.setKeyListener(keyPressed_);
    keyboard_.setPosition(0, 0, backgraound_width_, backgraound_height_);
    keyboard_.setTextIndentation();
    //Allocate the buffer associated with keyboard.
    memset(buffer_, 0, sizeof(buffer_));
    keyboard_.setBuffer(buffer_, BUFFER_SIZE);
    
    modePressedHandler();
    
    message_.setVisible(true);
    Unicode::UnicodeChar msg[] = { 0x0050, 0x0041, 0x0053, 0x0053, 0x0057, 0x004F, 0x0052, 0x0044 };
    Unicode::snprintf(message_buffer_, 9, "%s", msg);
    message_.invalidate();
    
    firstCharacterEntry_ = true;
  }
  
  void CustomKeyboard::enterPasswordPressedHandler()
  {	
    HAL::getInstance()->blockCopy(bufferPassword_, buffer_, 15 * sizeof(buffer_) / BUFFER_SIZE);
    
    if (checkAccount()) {
      if (checkAccountCallback_ && checkAccountCallback_->isValid())
      {
        checkAccountCallback_->execute(true);
      }
    }
    else
    {
      if (checkAccountCallback_ && checkAccountCallback_->isValid())
      {
        checkAccountCallback_->execute(false);
      }
    }
    
    firstCharacterEntry_ = true;
    uppercaseKeys_ = true;
    
    modePressedHandler();
    
    keyboard_.setLayout(&layoutEnglish);
    keyboard_.setKeyListener(keyPressed_);	
    keyboard_.setPosition(0, 0, backgraound_width_, backgraound_height_);
    keyboard_.setTextIndentation();
    
    memset(buffer_, 0, 15 * sizeof(buffer_) / BUFFER_SIZE);
    keyboard_.setBuffer(buffer_, BUFFER_SIZE);
    
    Unicode::UnicodeChar list[] = { 0x0055, 0x0053, 0x0045, 0x0052 };
    Unicode::snprintf(message_buffer_, 5, "%s", list);
    message_.setVisible(true);
    message_.invalidate();
  }
  
  void CustomKeyboard::setTouchable(bool touch)
  {
    Container::setTouchable(touch);
    keyboard_.setTouchable(touch);
  }
  
  void CustomKeyboard::moveCursor() 
  {
    uint16_t pos = keyboard_.getBufferPosition();
    uint16_t cursorPosition = cursor_begin_x_;
    
    for (int i = 0; i < pos; i++)
    {
      cursorPosition += shiftCursor[buffer_[i]];
    }
    
    cursor_.setPosition(cursorPosition, cursor_begin_y_, cursor_width_x_, cursor_height_y_);
  }
  
  bool CustomKeyboard::checkAccount()
  {
    //EDT, 3038
    if (bufferUser_[0] == 69 &&
        bufferUser_[1] == 68 &&
          bufferUser_[2] == 84 &&
            bufferUser_[3] == 00 &&
              bufferPassword_[0] == 51 &&
		bufferPassword_[1] == 48 &&
                  bufferPassword_[2] == 51 &&
                    bufferPassword_[3] == 56 && 
                      bufferPassword_[4] == 00 )
    {
      return true;
    }
    
    //ROJAR, 3683
    if (bufferUser_[0] == 82 &&
        bufferUser_[1] == 79 &&
          bufferUser_[2] == 74 &&
            bufferUser_[3] == 65 &&
              bufferUser_[4] == 82 &&
		bufferUser_[5] == 00 &&
                  bufferPassword_[0] == 51 &&
                    bufferPassword_[1] == 54 &&
                      bufferPassword_[2] == 56 &&
                        bufferPassword_[3] == 51 &&
                          bufferPassword_[4] == 00)
    {
      return true;
    }
    
    return false;
  }
  
  void CustomKeyboard::handleTickEvent()
  {
    if ((tick % 30) == 0)
    {
      if (cursor_.getAlpha() == 50) 
      {
        cursor_.setAlpha(10);
      }
      else
      {
        cursor_.setAlpha(50);
      }
      
      cursor_.invalidate();
    }
    
    tick++;
  }
  
  
  void CustomKeyboard::getBufferUser(uint16_t* user, uint16_t length)
  {
    for (int i = 0; i < length; i++)
    {
      user[i] = bufferUser_[i];
    }
  }