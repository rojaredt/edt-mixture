#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/BoardConfiguration.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

using namespace touchgfx;

//#include "comm.h"
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/**
 * Define the FreeRTOS task priorities and stack sizes
 */
#define configGUI_TASK_PRIORITY                 ( tskIDLE_PRIORITY + 3 )

#define configGUI_TASK_STK_SIZE                 ( 1000 )

#define configBACKEND_TASK_STK_SIZE             ( 1000 )

//#define CANVAS_BUFFER_SIZE (3600)

extern "C"
{
  typedef struct
  {
    uint16_t id;  
    uint16_t data[50];
  } QueueMessage_t;
}

QueueHandle_t xQueueRX;

static void GUITask(void* params)
{
    touchgfx::HAL::getInstance()->taskEntry();
}

static void BackendTask(void* pvParameters)
{  
  QueueMessage_t xMessageRX;
  
  for (;;)
  {      
    taskENTER_CRITICAL();
    
    if (xQueueRX != 0)
    {      
      if (xQueueReceive(xQueueRX, &xMessageRX, ( TickType_t )0) == pdTRUE)
      {         
        if(xMessageRX.id == 1 && xMessageRX.data[0] == 0)
        {          
        }
        else if(xMessageRX.id == 1 && xMessageRX.data[0] == 100)
        {
        }
      }
    }
    
    taskEXIT_CRITICAL();
  }
}

int main(void)
{
    hw_init();
    touchgfx_init();
    
    xQueueRX = xQueueCreate(8, sizeof(QueueMessage_t));
    
    xTaskCreate(GUITask,
                (TASKCREATE_NAME_TYPE)"GUITask",
                configGUI_TASK_STK_SIZE,
                NULL,
                configGUI_TASK_PRIORITY,
                NULL);

    xTaskCreate(BackendTask, 
                (TASKCREATE_NAME_TYPE)"BackendTask",
                configBACKEND_TASK_STK_SIZE,
                NULL,
                configGUI_TASK_PRIORITY - 1,
                NULL);
    
    vTaskStartScheduler();

    for (;;);
}