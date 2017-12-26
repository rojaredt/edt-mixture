#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/BoardConfiguration.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

using namespace touchgfx;

//#include "comm.h"
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stm32f7xx_hal.h"

#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x080C0000) /* Base address of Sector 7, 256 Kbytes */

//#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_7   /* Start @ of user Flash area */
//#define FLASH_USER_END_ADDR     (ADDR_FLASH_SECTOR_7_END-1)   /* End @ of user Flash area */

//volatile uint32_t ulAddress = 0; //, data32 = 0; //, MemoryProgramStatus = 0;
volatile uint32_t ulLogData[4 + 20 * 10] = {0};

uint32_t SECTORError = 0;
static FLASH_EraseInitTypeDef EraseInitStruct;

/**
 * Define the FreeRTOS task priorities and stack sizes
 */
#define configGUI_TASK_PRIORITY                 ( tskIDLE_PRIORITY + 3 )

#define configGUI_TASK_STK_SIZE                 ( 2048 )

#define configBACKEND_TASK_STK_SIZE             ( 2048 )

//#define CANVAS_BUFFER_SIZE (3600)

extern "C"
{
  typedef struct
  {
    uint16_t id;  
    uint16_t data[50];
  } QueueMessage_t;
  
    typedef struct
  {
    uint16_t id;  
    uint16_t data[200];
  } QueueMessageR_t;
}

QueueHandle_t xQueueRX;
QueueHandle_t xQueueTX;

static void GUITask(void* params)
{
    touchgfx::HAL::getInstance()->taskEntry();
}

static void BackendTask(void* pvParameters)
{  
  QueueMessage_t xMessageRX;
  QueueMessageR_t xMessageTX;
  
  for (;;)
  {         
    taskENTER_CRITICAL();
    
    if (xQueueRX != 0)
    {      
      //taskENTER_CRITICAL();
      
      if (xQueueReceive(xQueueRX, &xMessageRX, (TickType_t)0) == pdTRUE)
      {         
        //taskENTER_CRITICAL();
        
        if(xMessageRX.id == 2)
        {
          volatile uint32_t ulData = 0;
          volatile uint32_t ulAddress = 0;
          volatile uint32_t ulAddressBase = ADDR_FLASH_SECTOR_7;
          uint32_t ulLength = 4 + (20 * 8);
          
          HAL_FLASH_Unlock();
          
          // Save data.
          ulAddress = ulAddressBase;  
          
          for(int i = 0;i < ulLength; i++)
          {
            ulData = *(volatile uint32_t *)(ulAddress);
            
            if(i < 4)
            {
              ulLogData[i] = ulData;
            }
            else
            {
              ulLogData[i + 20] = ulData;
            }
            
            ulAddress += 4;
          }
          
          for(int i = 0;i < 18;i++)
          {
            ulLogData[i + 4] = xMessageRX.data[i];
          }
          
          // Erase.
          EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
          EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
          EraseInitStruct.Sector        = FLASH_SECTOR_7;
          EraseInitStruct.NbSectors     = 1;          
          
          if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
          {    
            /*
            Error occurred while sector erase.
            User can add here some code to deal with this error.
            SECTORError will contain the faulty sector and then to know the code error on this sector,
            user can call function 'HAL_FLASH_GetError()'
            */
          }
          
          // Restore.
          ulAddress = ulAddressBase;
          
          for(int i = 0;i < ulLength; i++)
          {            
            ulData = ulLogData[i];
            
            if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, ulAddress, ulData) == HAL_OK)
            {
              ulAddress = ulAddress + 4;
            }
            else
            {
              /* Error occurred while writing data in Flash memory.
              User can add here some code to deal with this error */
            }
          }      
          
          HAL_FLASH_Lock();
        } 
        else if(xMessageRX.id == 210)
        {
          if (xQueueTX != 0)
          { 
            volatile uint32_t ulData = 0;
            volatile uint32_t ulAddress = 0;
            volatile uint32_t ulAddressBase = ADDR_FLASH_SECTOR_7;          
            uint32_t ulLength = 4 + (20 * 8);
            
            HAL_FLASH_Unlock();          
            
            // Read data.
            ulAddress = ulAddressBase;  
            
            xMessageTX.id = (uint16_t)211;
            
            for(int i = 0;i < ulLength; i++)
            {
              ulData = *(volatile uint32_t *)(ulAddress);            
              xMessageTX.data[i] = ulData;
              
              ulAddress += 4;
            }
            
            HAL_FLASH_Lock();
            
            xQueueSend(xQueueTX, ( void * )&xMessageTX, 0); 
          }
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
    
    xQueueRX = xQueueCreate(1, sizeof(QueueMessage_t));
    xQueueTX = xQueueCreate(1, sizeof(QueueMessageR_t));
    
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