/**
  ******************************************************************************  
  * @author  EDT Embedded Team  
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ETEM070006XDH6_LCD_H
#define __ETEM070006XDH6_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif 

   /* Includes ------------------------------------------------------------------*/
/* Include LCD component Driver */
#include "et070001dma/et070001dma.h"

/* Include SDRAM Driver */
#include "etem070006xdh6_sdram.h"
 
#include "etem070006xdh6.h"

#define LCD_LayerCfgTypeDef    LTDC_LayerCfgTypeDef
    
#define LCD_OK                 ((uint8_t)0x00)
#define LCD_ERROR              ((uint8_t)0x01)
#define LCD_TIMEOUT            ((uint8_t)0x02)

uint8_t  BSP_LCD_Init(void);
uint8_t  BSP_LCD_DeInit(void);
uint32_t BSP_LCD_GetXSize(void);
uint32_t BSP_LCD_GetYSize(void);

void    BSP_LCD_DisplayOff(void);
void    BSP_LCD_DisplayOn(void);
void    BSP_LCD_Reset(void);
/* These functions can be modified in case the current settings
   need to be changed for specific application needs */
void    BSP_LCD_MspInit(LTDC_HandleTypeDef *hltdc, void *Params);
void    BSP_LCD_MspDeInit(LTDC_HandleTypeDef *hltdc, void *Params);
void    BSP_LCD_ClockConfig(LTDC_HandleTypeDef *hltdc, void *Params);

#ifdef __cplusplus
}
#endif
#endif /* __ETEM070006XDH6_LCD_H */
