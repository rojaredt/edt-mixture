/******************************************************************************
 *
 * @author    EDT <http://www.edtc.com>
 *
 *****************************************************************************/
#include <touchgfx/hal/GPIO.hpp>

#include "etem070006xdh6.h"
using namespace touchgfx;

static bool ledState;

// This GPIO utility links that LED to GPIO::RENDER_TIME.

static bool isRenderTime(GPIO::GPIO_ID id)
{
    return id == GPIO::RENDER_TIME;
}

void GPIO::init()
{
    BSP_LED_Init(LED_GREEN);
    clear(GPIO::RENDER_TIME);
}

void GPIO::set(GPIO::GPIO_ID id)
{
    if (isRenderTime(id))
    {
        ledState = 1;
        BSP_LED_On(LED_GREEN);
    }
}

void GPIO::clear(GPIO::GPIO_ID id)
{
    if (isRenderTime(id))
    {
        ledState = 0;
        BSP_LED_Off(LED_GREEN);
    }
}

void GPIO::toggle(GPIO::GPIO_ID id)
{
    if (isRenderTime(id))
    {
        BSP_LED_Toggle(LED_GREEN);
    }
}

bool GPIO::get(GPIO::GPIO_ID id)
{
    if (isRenderTime(id))
    {
        return ledState;
    }
    return 0;
}
