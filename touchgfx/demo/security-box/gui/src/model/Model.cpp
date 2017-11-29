#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR
extern "C"
{
	extern QueueHandle_t xQueueRX;
}
#endif

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
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