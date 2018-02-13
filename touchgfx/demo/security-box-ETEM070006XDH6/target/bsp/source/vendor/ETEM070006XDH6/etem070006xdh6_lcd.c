/**
  ******************************************************************************  
  * @author  EDT Embedded Team  
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "etem070006xdh6_lcd.h"
//#include "etem070006xdh6_msp.h"

LTDC_HandleTypeDef  hLtdcHandler;
static DMA2D_HandleTypeDef hDma2dHandler;

/* Default LCD configuration with LCD Layer 1 */
static uint32_t            ActiveLayer = 0;

/**
  * @brief  Initializes the LCD.
  * @retval LCD state
  */
uint8_t BSP_LCD_Init(void)
{    
  /* Select the used LCD */
  /* Timing Configuration */
  hLtdcHandler.Init.HorizontalSync = (TFT_HSYNC - 1);
  hLtdcHandler.Init.VerticalSync = (TFT_VSYNC - 1);
  hLtdcHandler.Init.AccumulatedHBP = (TFT_HSYNC + TFT_HBP - 1);
  hLtdcHandler.Init.AccumulatedVBP = (TFT_VSYNC + TFT_VBP - 1);
  hLtdcHandler.Init.AccumulatedActiveH = (TFT_HEIGHT + TFT_VSYNC + TFT_VBP - 1);
  hLtdcHandler.Init.AccumulatedActiveW = (TFT_WIDTH + TFT_HSYNC + TFT_HBP - 1);
  hLtdcHandler.Init.TotalHeigh = (TFT_HEIGHT + TFT_VSYNC + TFT_VBP + TFT_VFP - 1);
  hLtdcHandler.Init.TotalWidth = (TFT_WIDTH + TFT_HSYNC + TFT_HBP + TFT_HFP - 1);
  
  /* LCD clock configuration */
  BSP_LCD_ClockConfig(&hLtdcHandler, NULL);

  /* Initialize the LCD pixel width and pixel height */
  hLtdcHandler.LayerCfg->ImageWidth  = TFT_WIDTH;
  hLtdcHandler.LayerCfg->ImageHeight = TFT_HEIGHT;

  /* Background value */
  hLtdcHandler.Init.Backcolor.Blue = 0;
  hLtdcHandler.Init.Backcolor.Green = 0;
  hLtdcHandler.Init.Backcolor.Red = 0;
  
  /* Polarity */
  hLtdcHandler.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hLtdcHandler.Init.VSPolarity = LTDC_VSPOLARITY_AL; 
  hLtdcHandler.Init.DEPolarity = LTDC_DEPOLARITY_AL;  
  //hLtdcHandler.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hLtdcHandler.Init.PCPolarity = LTDC_PCPOLARITY_IIPC; // for EDT layout 7" board
  hLtdcHandler.Instance = LTDC;

  if(HAL_LTDC_GetState(&hLtdcHandler) == HAL_LTDC_STATE_RESET)
  {
    /* Initialize the LCD Msp: this __weak function can be rewritten by the application */
    BSP_LCD_MspInit(&hLtdcHandler, NULL);
  }
  HAL_LTDC_Init(&hLtdcHandler);
  /* Disable display DE-Mode */
 // HAL_GPIO_WritePin(GPIOK, LCD_DE_Pin, GPIO_PIN_RESET);

  /* Assert backlight LCD_BL_CTRL pin */
  HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_Port, LCD_BL_CTRL_Pin, GPIO_PIN_SET);

#if !defined(DATA_IN_ExtSDRAM)
  /* Initialize the SDRAM */
  BSP_SDRAM_Init();
#endif
     
  return LCD_OK;
}

/**
  * @brief  DeInitializes the LCD.
  * @retval LCD state
  */
uint8_t BSP_LCD_DeInit(void)
{ 
  /* Initialize the hLtdcHandler Instance parameter */
  hLtdcHandler.Instance = LTDC;

 /* Disable LTDC block */
  __HAL_LTDC_DISABLE(&hLtdcHandler);

  /* DeInit the LTDC */
  HAL_LTDC_DeInit(&hLtdcHandler);

  /* DeInit the LTDC MSP : this __weak function can be rewritten by the application */
  BSP_LCD_MspDeInit(&hLtdcHandler, NULL);

  return LCD_OK;
}

/**
  * @brief  Gets the LCD X size.
  * @retval Used LCD X size
  */
uint32_t BSP_LCD_GetXSize(void)
{
  return hLtdcHandler.LayerCfg[ActiveLayer].ImageWidth;
}

/**
  * @brief  Gets the LCD Y size.
  * @retval Used LCD Y size
  */
uint32_t BSP_LCD_GetYSize(void)
{
  return hLtdcHandler.LayerCfg[ActiveLayer].ImageHeight;
}

/**
  * @brief  Enables the display.
  * @retval None
  */
void BSP_LCD_DisplayOn(void)
{
  /* Display On */
  __HAL_LTDC_ENABLE(&hLtdcHandler);
  HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_Port, LCD_BL_CTRL_Pin, GPIO_PIN_SET);  /* Assert LCD_BL_CTRL pin */
}

/**
  * @brief  Disables the display.
  * @retval None
  */
void BSP_LCD_DisplayOff(void)
{
  /* Display Off */
  __HAL_LTDC_DISABLE(&hLtdcHandler);
  HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_Port, LCD_BL_CTRL_Pin, GPIO_PIN_RESET);/* De-assert LCD_BL_CTRL pin */
}

/**
  * @brief  Initializes the LTDC MSP.
  * @param  hltdc: LTDC handle
  * @param  Params
  * @retval None
  */
void BSP_LCD_MspInit(LTDC_HandleTypeDef *hltdc, void *Params)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the LTDC and DMA2D clocks */
  __HAL_RCC_LTDC_CLK_ENABLE();
  __HAL_RCC_DMA2D_CLK_ENABLE();
  
  /* Enable GPIOs clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
 
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  
    GPIO_InitStruct.Pin = LCD_B0_Pin;
    HAL_GPIO_Init(LCD_B0_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_B1_Pin|LCD_B2_Pin|LCD_B3_Pin|LCD_G4_Pin 
                          |LCD_G1_Pin|LCD_G3_Pin|LCD_G0_Pin|LCD_G2_Pin 
                          |LCD_R7_Pin|LCD_R5_Pin|LCD_R6_Pin|LCD_R4_Pin 
                          |LCD_R3_Pin|LCD_R1_Pin|LCD_R2_Pin;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_DE_Pin|LCD_B7_Pin|LCD_B6_Pin|LCD_B5_Pin 
                          |LCD_B4_Pin|LCD_G6_Pin|LCD_G7_Pin|LCD_G5_Pin;
    HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_HSYNC_Pin|LCD_R0_Pin|LCD_CLK_Pin;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_VSYNC_Pin;
    HAL_GPIO_Init(LCD_VSYNC_GPIO_Port, &GPIO_InitStruct);
    
    /* LCD_BL_CTRL GPIO configuration */
    GPIO_InitStruct.Pin   = LCD_BL_CTRL_Pin;  /* LCD_BL_CTRL pin has to be manually controlled */
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_BL_CTRL_GPIO_Port, &GPIO_InitStruct);
}


/**
  * @brief  Clock Config.
  * @param  hltdc: LTDC handle
  * @param  Params
  * @note   This API is called by BSP_LCD_Init()
  *         Being __weak it can be overwritten by the application
  * @retval None
  */
void BSP_LCD_ClockConfig(LTDC_HandleTypeDef *hltdc, void *Params)
{
  static RCC_PeriphCLKInitTypeDef  periph_clk_init_struct;

  /* TFT LCD clock configuration */
  periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  periph_clk_init_struct.PLLSAI.PLLSAIN = 208; //OG=180
  periph_clk_init_struct.PLLSAI.PLLSAIR = 4;
  periph_clk_init_struct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  HAL_RCCEx_PeriphCLKConfig(&periph_clk_init_struct);
  
}   

void BSP_LCD_Reset(void)          
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure LCD_RESET_Pin(E5) Output Level */
  HAL_GPIO_WritePin(LCD_RESET_GPIO_Port,LCD_RESET_Pin, GPIO_PIN_RESET);

  /*Configure LCD_RESET_Pin(E5)*/
  GPIO_InitStruct.Pin = LCD_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_RESET_GPIO_Port, &GPIO_InitStruct);
  
  HAL_GPIO_WritePin(LCD_RESET_GPIO_Port,LCD_RESET_Pin, GPIO_PIN_RESET); 

  HAL_Delay(20);                       //delay 20ms  
  HAL_GPIO_WritePin(LCD_RESET_GPIO_Port,LCD_RESET_Pin, GPIO_PIN_SET);
// Wait for 10ms after releasing XRES before sending commands
  HAL_Delay(10);                       //delay 10ms	
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
