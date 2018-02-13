/******************************************************************************
 *
 * @author    EDT <http://www.edtc.com>
 *
 *****************************************************************************/
#ifndef ETEM070006XDH6TOUCHCONTROLLER_HPP
#define ETEM070006XDH6TOUCHCONTROLLER_HPP

#include <platform/driver/touch/TouchController.hpp>

namespace touchgfx
{
class ETEM070006XDH6TouchController: public TouchController
{
public:
    ETEM070006XDH6TouchController() : isInitialized(false) {}
    virtual void init();
    virtual bool sampleTouch(int32_t& x, int32_t& y);
protected:
    bool isInitialized;
};

}

#endif // ETEM070006XDH6TOUCHCONTROLLER_HPP
