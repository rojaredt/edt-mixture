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

#define configGUI_TASK_STK_SIZE                 ( 950 )

#define configBACKEND_TASK_STK_SIZE             ( 400 )

//#define CANVAS_BUFFER_SIZE (3600)

extern "C"
{
  typedef struct
  {
    uint16_t id;  
    uint16_t data[50];
  } QueueMessage_t;
}

//typedef struct
//{
//  uint16_t id;  
//  uint16_t data[50];
//} QueueMessage_t;

QueueMessage_t xMessageRX;

QueueHandle_t xQueueRX;

static void GUITask(void* params)
{
    touchgfx::HAL::getInstance()->taskEntry();
}

static void BackendTask( void* pvParameters )
{
  configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
  
  vTaskDelay(1000);
  
  while(1)
  {        
    taskENTER_CRITICAL();
    
    if (xQueueRX != 0)
    {
      if (xQueueReceive(xQueueRX, &xMessageRX, 0) == pdPASS)
      {         
        if(xMessageRX.id == 1 && xMessageRX.data[0] == 0)
        {          
        }
        else if(xMessageRX.id == 1 && xMessageRX.data[0] == 100)
        {
        }
        
        xQueueReset(xQueueRX);
      }
    }    
    
    taskEXIT_CRITICAL();    
  }
}

int main(void)
{
    hw_init();
    touchgfx_init();

    xQueueRX = xQueueCreate(2, sizeof(QueueMessage_t));
    
    xTaskCreate(GUITask,
                (TASKCREATE_NAME_TYPE)"GUITask",
                configGUI_TASK_STK_SIZE,
                NULL,
                configGUI_TASK_PRIORITY,
                NULL);

    xTaskCreate(BackendTask, 
                (TASKCREATE_NAME_TYPE)"BackendTask",
                configBACKEND_TASK_STK_SIZE,
                ( void * ) 1,
                configGUI_TASK_PRIORITY - 1,
                NULL);
    
    vTaskStartScheduler();

    for (;;);
}