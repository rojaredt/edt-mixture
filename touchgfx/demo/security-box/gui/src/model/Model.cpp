#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR
extern "C"
{
	extern QueueHandle_t xQueueRX;
        extern QueueHandle_t xQueueTX;
}
#endif

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
#if !defined(_MSC_VER) && !defined(SIMULATOR)
  
  //taskENTER_CRITICAL();
  
  if (xQueueTX != 0)
  {
    if (xQueueReceive(xQueueTX, &xMessageTX, 0) == pdPASS)
    {    
      if (xMessageTX.id == 211)
      {
        if (xMessageTX.data[0] == 3)
        {
          //modelListener->mp3_status(xMessageTX.data[1], xMessageTX.data[2], xMessageTX.data[3], xMessageTX.data[4]);
        }
        if (xMessageTX.data[0] == 4)
        {
          //modelListener->printer_status(mrx.data[1]);
        }                    
      }
    }
  }
  
  //taskEXIT_CRITICAL();
#endif
}

void Model::pushData(uint16_t id)
{
	xMessageRX.id = id;
	xMessageRX.data[0] = 0;	

#ifndef SIMULATOR
	xQueueSend(xQueueRX, &xMessageRX, 0);
#endif
}

void Model::pushData(uint16_t id, uint16_t data[], uint16_t dataLength)
{
	xMessageRX.id = id;
	for (int i = 0; i < dataLength; i++)
	{
		xMessageRX.data[i] = data[i];
	}

#ifndef SIMULATOR
	xQueueSend(xQueueRX, &xMessageRX, 0);
#endif
}