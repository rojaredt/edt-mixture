/**
  ******************************************************************************
  * @file    hy4614.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    25-June-2015
  * @brief   This file provides a set of functions needed to manage the HY4614
  *          touch screen devices.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hy4614.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Component
  * @{
  */

/** @defgroup HY4614
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/** @defgroup HY4614_Private_Types_Definitions
  * @{
  */

/* Private define ------------------------------------------------------------*/

/** @defgroup HY4614_Private_Defines
  * @{
  */

/* Private macro -------------------------------------------------------------*/

/** @defgroup HY4614_Private_Macros
  * @{
  */

/* Private variables ---------------------------------------------------------*/

/** @defgroup HY4614_Private_Variables
  * @{
  */

/* Touch screen driver structure initialization */
TS_DrvTypeDef hy4614_ts_drv =
{
  hy4614_Init,
  hy4614_ReadID,
  hy4614_Reset,

  hy4614_TS_Start,
  hy4614_TS_DetectTouch,
  hy4614_TS_GetXY,

  hy4614_TS_EnableIT,
  hy4614_TS_ClearIT,
  hy4614_TS_ITStatus,
  hy4614_TS_DisableIT

};

/* Global hy4614 handle */
static hy4614_handle_TypeDef hy4614_handle = { HY4614_I2C_NOT_INITIALIZED, 0, 0};

/**
  * @}
  */

/** @defgroup hy4614_Private_Function_Prototypes
  * @{
  */

/* Private functions prototypes-----------------------------------------------*/

/**
  * @brief  Return the status of I2C was initialized or not.
  * @param  None.
  * @retval : I2C initialization status.
  */
static uint8_t hy4614_Get_I2C_InitializedStatus(void);

/**
  * @brief  I2C initialize if needed.
  * @param  None.
  * @retval : None.
  */
static void hy4614_I2C_InitializeIfRequired(void);

/**
  * @brief  Basic static configuration of TouchScreen
  * @param  DeviceAddr: HY4614 Device address for communication on I2C Bus.
  * @retval Status HY4614_STATUS_OK or HY4614_STATUS_NOT_OK.
  */
static uint32_t hy4614_TS_Configure(uint16_t DeviceAddr);

/** @defgroup hy4614_Private_Functions
  * @{
  */

/** @defgroup hy4614_Public_Function_Body
  * @{
  */

/* Public functions bodies-----------------------------------------------*/


/**
  * @brief  Initialize the hy4614 communication bus
  *         from MCU to HY4614 : ie I2C channel initialization (if required).
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of HY4614).
  * @retval None
  */
void hy4614_Init(uint16_t DeviceAddr)
{
  /* Wait at least 200ms after power up before accessing registers
   * Trsi timing (Time of starting to report point after resetting) from HY4614GQQ datasheet */
  TS_IO_Delay(200);

  /* Initialize I2C link if needed */
  hy4614_I2C_InitializeIfRequired();
}

/**
  * @brief  Software Reset the hy4614.
  *         @note : Not applicable to HY4614.
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of HY4614).
  * @retval None
  */
void hy4614_Reset(uint16_t DeviceAddr)
{
  /* Do nothing */
  /* No software reset sequence available in HY4614 IC */
}

/**
  * @brief  Read the hy4614 device ID, pre initialize I2C in case of need to be
  *         able to read the HY4614 device ID, and verify this is a HY4614.
  * @param  DeviceAddr: I2C HY4614 Slave address.
  * @retval The Device ID (two bytes).
  */
uint16_t hy4614_ReadID(uint16_t DeviceAddr)
{
  volatile uint8_t ucReadId = 0;
  uint8_t nbReadAttempts = 0;
  uint8_t bFoundDevice = 0; /* Device not found by default */

  /* Initialize I2C link if needed */
  hy4614_I2C_InitializeIfRequired();

  /* At maximum 4 attempts to read ID : exit at first finding of the searched device ID */
  for(nbReadAttempts = 0; ((nbReadAttempts < 3) && !(bFoundDevice)); nbReadAttempts++)
  {
    /* Read register HY4614_CHIP_ID_REG as DeviceID detection */
    ucReadId = TS_IO_Read(DeviceAddr, HY4614_CHIP_ID_REG);

    /* Found the searched device ID ? */
    if(ucReadId == HY4614_ID_VALUE)
    {
      /* Set device as found */
      bFoundDevice = 1;
    }
  }

  /* Return the device ID value */
  return (ucReadId);
}

/**
  * @brief  Configures the touch Screen IC device to start detecting touches
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address).
  * @retval None.
  */
void hy4614_TS_Start(uint16_t DeviceAddr)
{
  /* Minimum static configuration of HY4614 */
  HY4614_ASSERT(hy4614_TS_Configure(DeviceAddr));

  /* By default set HY4614 IC in Polling mode : no INT generation on HY4614 for new touch available */
  /* Note TS_INT is active low                                                                      */
  hy4614_TS_DisableIT(DeviceAddr);
}

/**
  * @brief  Return if there is touches detected or not.
  *         Try to detect new touches and forget the old ones (reset internal global
  *         variables).
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval : Number of active touches detected (can be 0, 1 or 2).
  */
uint8_t hy4614_TS_DetectTouch(uint16_t DeviceAddr)
{
  volatile uint8_t nbTouch = 0;

  /* Read register HY4614_TD_STAT_REG to check number of touches detection */
  nbTouch = TS_IO_Read(DeviceAddr, HY4614_TD_STAT_REG);
  nbTouch &= HY4614_TD_STAT_MASK;

  if(nbTouch > HY4614_MAX_DETECTABLE_TOUCH)
  {
    /* If invalid number of touch detected, set it to zero */
    nbTouch = 0;
  }

  /* Update hy4614 driver internal global : current number of active touches */
  hy4614_handle.currActiveTouchNb = nbTouch;

  /* Reset current active touch index on which to work on */
  hy4614_handle.currActiveTouchIdx = 0;

  return(nbTouch);
}

/**
  * @brief  Get the touch screen X and Y positions values
  *         Manage multi touch thanks to touch Index global
  *         variable 'hy4614_handle.currActiveTouchIdx'.
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  X: Pointer to X position value
  * @param  Y: Pointer to Y position value
  * @retval None.
  */
void hy4614_TS_GetXY(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y)
{
  volatile uint8_t ucReadData = 0;
  static uint16_t coord;
  uint8_t regAddressXLow = 0;
  uint8_t regAddressXHigh = 0;
  uint8_t regAddressYLow = 0;
  uint8_t regAddressYHigh = 0;

  if(hy4614_handle.currActiveTouchIdx < hy4614_handle.currActiveTouchNb)
  {
    switch(hy4614_handle.currActiveTouchIdx)
    {
    case 0 :
      regAddressXLow  = HY4614_P1_XL_REG;
      regAddressXHigh = HY4614_P1_XH_REG;
      regAddressYLow  = HY4614_P1_YL_REG;
      regAddressYHigh = HY4614_P1_YH_REG;
      break;

    case 1 :
      regAddressXLow  = HY4614_P2_XL_REG;
      regAddressXHigh = HY4614_P2_XH_REG;
      regAddressYLow  = HY4614_P2_YL_REG;
      regAddressYHigh = HY4614_P2_YH_REG;
      break;

    case 2 :
      regAddressXLow  = HY4614_P3_XL_REG;
      regAddressXHigh = HY4614_P3_XH_REG;
      regAddressYLow  = HY4614_P3_YL_REG;
      regAddressYHigh = HY4614_P3_YH_REG;
      break;

    case 3 :
      regAddressXLow  = HY4614_P4_XL_REG;
      regAddressXHigh = HY4614_P4_XH_REG;
      regAddressYLow  = HY4614_P4_YL_REG;
      regAddressYHigh = HY4614_P4_YH_REG;
      break;

    case 4 :
      regAddressXLow  = HY4614_P5_XL_REG;
      regAddressXHigh = HY4614_P5_XH_REG;
      regAddressYLow  = HY4614_P5_YL_REG;
      regAddressYHigh = HY4614_P5_YH_REG;
      break;

    case 5 :
      regAddressXLow  = HY4614_P6_XL_REG;
      regAddressXHigh = HY4614_P6_XH_REG;
      regAddressYLow  = HY4614_P6_YL_REG;
      regAddressYHigh = HY4614_P6_YH_REG;
      break;

    case 6 :
      regAddressXLow  = HY4614_P7_XL_REG;
      regAddressXHigh = HY4614_P7_XH_REG;
      regAddressYLow  = HY4614_P7_YL_REG;
      regAddressYHigh = HY4614_P7_YH_REG;
      break;

    case 7 :
      regAddressXLow  = HY4614_P8_XL_REG;
      regAddressXHigh = HY4614_P8_XH_REG;
      regAddressYLow  = HY4614_P8_YL_REG;
      regAddressYHigh = HY4614_P8_YH_REG;
      break;

    case 8 :
      regAddressXLow  = HY4614_P9_XL_REG;
      regAddressXHigh = HY4614_P9_XH_REG;
      regAddressYLow  = HY4614_P9_YL_REG;
      regAddressYHigh = HY4614_P9_YH_REG;
      break;

    case 9 :
      regAddressXLow  = HY4614_P10_XL_REG;
      regAddressXHigh = HY4614_P10_XH_REG;
      regAddressYLow  = HY4614_P10_YL_REG;
      regAddressYHigh = HY4614_P10_YH_REG;
      break;

    default :
      break;

    } /* end switch(hy4614_handle.currActiveTouchIdx) */

    /* Read low part of X position */
    ucReadData = TS_IO_Read(DeviceAddr, regAddressXLow);
    coord = (ucReadData & HY4614_TOUCH_POS_LSB_MASK) >> HY4614_TOUCH_POS_LSB_SHIFT;

    /* Read high part of X position */
    ucReadData = TS_IO_Read(DeviceAddr, regAddressXHigh);
    coord |= ((ucReadData & HY4614_TOUCH_POS_MSB_MASK) >> HY4614_TOUCH_POS_MSB_SHIFT) << 8;

    /* Send back ready X position to caller */
    *X = coord;

    /* Read low part of Y position */
    ucReadData = TS_IO_Read(DeviceAddr, regAddressYLow);
    coord = (ucReadData & HY4614_TOUCH_POS_LSB_MASK) >> HY4614_TOUCH_POS_LSB_SHIFT;

    /* Read high part of Y position */
    ucReadData = TS_IO_Read(DeviceAddr, regAddressYHigh);
    coord |= ((ucReadData & HY4614_TOUCH_POS_MSB_MASK) >> HY4614_TOUCH_POS_MSB_SHIFT) << 8;

    /* Send back ready Y position to caller */
    *Y = coord;

    hy4614_handle.currActiveTouchIdx++; /* next call will work on next touch */

  } /* of if(hy4614_handle.currActiveTouchIdx < hy4614_handle.currActiveTouchNb) */
}

/**
  * @brief  Configure the HY4614 device to generate IT on given INT pin
  *         connected to MCU as EXTI.
  * @param  DeviceAddr: Device address on communication Bus (Slave I2C address of HY4614).
  * @retval None
  */
void hy4614_TS_EnableIT(uint16_t DeviceAddr)
{
   uint8_t regValue = 0;
   regValue = (HY4614_G_MODE_INTERRUPT_TRIGGER & (HY4614_G_MODE_INTERRUPT_MASK >> HY4614_G_MODE_INTERRUPT_SHIFT)) << HY4614_G_MODE_INTERRUPT_SHIFT;

   /* Set interrupt trigger mode in HY4614_GMODE_REG */
   TS_IO_Write(DeviceAddr, HY4614_GMODE_REG, regValue);
}

/**
  * @brief  Configure the HY4614 device to stop generating IT on the given INT pin
  *         connected to MCU as EXTI.
  * @param  DeviceAddr: Device address on communication Bus (Slave I2C address of HY4614).
  * @retval None
  */
void hy4614_TS_DisableIT(uint16_t DeviceAddr)
{
  uint8_t regValue = 0;
  regValue = (HY4614_G_MODE_INTERRUPT_POLLING & (HY4614_G_MODE_INTERRUPT_MASK >> HY4614_G_MODE_INTERRUPT_SHIFT)) << HY4614_G_MODE_INTERRUPT_SHIFT;

  /* Set interrupt polling mode in HY4614_GMODE_REG */
  TS_IO_Write(DeviceAddr, HY4614_GMODE_REG, regValue);
}

/**
  * @brief  Get IT status from HY4614 interrupt status registers
  *         Should be called Following an EXTI coming to the MCU to know the detailed
  *         reason of the interrupt.
  *         @note : This feature is not applicable to HY4614.
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of HY4614).
  * @retval TS interrupts status : always return 0 here
  */
uint8_t hy4614_TS_ITStatus(uint16_t DeviceAddr)
{
  /* Always return 0 as feature not applicable to HY4614 */
  return 0;
}

/**
  * @brief  Clear IT status in HY4614 interrupt status clear registers
  *         Should be called Following an EXTI coming to the MCU.
  *         @note : This feature is not applicable to HY4614.
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of HY4614).
  * @retval None
  */
void hy4614_TS_ClearIT(uint16_t DeviceAddr)
{
  /* Nothing to be done here for HY4614 */
}

/**** NEW FEATURES enabled when Multi-touch support is enabled ****/

#if (TS_MULTI_TOUCH_SUPPORTED == 1)

/**
  * @brief  Get the last touch gesture identification (zoom, move up/down...).
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of HY4614).
  * @param  pGestureId : Pointer to get last touch gesture Identification.
  * @retval None.
  */
void hy4614_TS_GetGestureID(uint16_t DeviceAddr, uint32_t * pGestureId)
{
  volatile uint8_t ucReadData = 0;

  ucReadData = TS_IO_Read(DeviceAddr, HY4614_GEST_ID_REG);

  * pGestureId = ucReadData;
}

/**
  * @brief  Get the touch detailed informations on touch number 'touchIdx' (0..1)
  *         This touch detailed information contains :
  *         - weight that was applied to this touch
  *         - sub-area of the touch in the touch panel
  *         - event of linked to the touch (press down, lift up, ...)
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of HY4614).
  * @param  touchIdx : Passed index of the touch (0..1) on which we want to get the
  *                    detailed information.
  * @param  pWeight : Pointer to to get the weight information of 'touchIdx'.
  * @param  pArea   : Pointer to to get the sub-area information of 'touchIdx'.
  * @param  pEvent  : Pointer to to get the event information of 'touchIdx'.

  * @retval None.
  */
void hy4614_TS_GetTouchInfo(uint16_t   DeviceAddr,
                            uint32_t   touchIdx,
                            uint32_t * pWeight,
                            uint32_t * pArea,
                            uint32_t * pEvent)
{
  volatile uint8_t ucReadData = 0;
  uint8_t regAddressXHigh = 0;
  uint8_t regAddressPWeight = 0;
  uint8_t regAddressPMisc = 0;

  if(touchIdx < hy4614_handle.currActiveTouchNb)
  {
    switch(touchIdx)
    {
    case 0 :
      regAddressXHigh   = HY4614_P1_XH_REG;
      regAddressPWeight = HY4614_P1_WEIGHT_REG;
      regAddressPMisc   = HY4614_P1_MISC_REG;
      break;

    case 1 :
      regAddressXHigh   = HY4614_P2_XH_REG;
      regAddressPWeight = HY4614_P2_WEIGHT_REG;
      regAddressPMisc   = HY4614_P2_MISC_REG;
      break;

    case 2 :
      regAddressXHigh   = HY4614_P3_XH_REG;
      regAddressPWeight = HY4614_P3_WEIGHT_REG;
      regAddressPMisc   = HY4614_P3_MISC_REG;
      break;

    case 3 :
      regAddressXHigh   = HY4614_P4_XH_REG;
      regAddressPWeight = HY4614_P4_WEIGHT_REG;
      regAddressPMisc   = HY4614_P4_MISC_REG;
      break;

    case 4 :
      regAddressXHigh   = HY4614_P5_XH_REG;
      regAddressPWeight = HY4614_P5_WEIGHT_REG;
      regAddressPMisc   = HY4614_P5_MISC_REG;
      break;

    case 5 :
      regAddressXHigh   = HY4614_P6_XH_REG;
      regAddressPWeight = HY4614_P6_WEIGHT_REG;
      regAddressPMisc   = HY4614_P6_MISC_REG;
      break;

    case 6 :
      regAddressXHigh   = HY4614_P7_XH_REG;
      regAddressPWeight = HY4614_P7_WEIGHT_REG;
      regAddressPMisc   = HY4614_P7_MISC_REG;
      break;

    case 7 :
      regAddressXHigh   = HY4614_P8_XH_REG;
      regAddressPWeight = HY4614_P8_WEIGHT_REG;
      regAddressPMisc   = HY4614_P8_MISC_REG;
      break;

    case 8 :
      regAddressXHigh   = HY4614_P9_XH_REG;
      regAddressPWeight = HY4614_P9_WEIGHT_REG;
      regAddressPMisc   = HY4614_P9_MISC_REG;
      break;

    case 9 :
      regAddressXHigh   = HY4614_P10_XH_REG;
      regAddressPWeight = HY4614_P10_WEIGHT_REG;
      regAddressPMisc   = HY4614_P10_MISC_REG;
      break;

    default :
      break;

    } /* end switch(touchIdx) */

    /* Read Event Id of touch index */
    ucReadData = TS_IO_Read(DeviceAddr, regAddressXHigh);
    * pEvent = (ucReadData & HY4614_TOUCH_EVT_FLAG_MASK) >> HY4614_TOUCH_EVT_FLAG_SHIFT;

    /* Read weight of touch index */
    ucReadData = TS_IO_Read(DeviceAddr, regAddressPWeight);
    * pWeight = (ucReadData & HY4614_TOUCH_WEIGHT_MASK) >> HY4614_TOUCH_WEIGHT_SHIFT;

    /* Read area of touch index */
    ucReadData = TS_IO_Read(DeviceAddr, regAddressPMisc);
    * pArea = (ucReadData & HY4614_TOUCH_AREA_MASK) >> HY4614_TOUCH_AREA_SHIFT;

  } /* of if(touchIdx < hy4614_handle.currActiveTouchNb) */
}

#endif /* TS_MULTI_TOUCH_SUPPORTED == 1 */

/** @defgroup hy4614_Static_Function_Body
  * @{
  */

/* Static functions bodies-----------------------------------------------*/


/**
  * @brief  Return the status of I2C was initialized or not.
  * @param  None.
  * @retval : I2C initialization status.
  */
static uint8_t hy4614_Get_I2C_InitializedStatus(void)
{
  return(hy4614_handle.i2cInitialized);
}

/**
  * @brief  I2C initialize if needed.
  * @param  None.
  * @retval : None.
  */
static void hy4614_I2C_InitializeIfRequired(void)
{
  if(hy4614_Get_I2C_InitializedStatus() == HY4614_I2C_NOT_INITIALIZED)
  {
    /* Initialize TS IO BUS layer (I2C) */
    TS_IO_Init();

    /* Set state to initialized */
    hy4614_handle.i2cInitialized = HY4614_I2C_INITIALIZED;
  }
}

/**
  * @brief  Basic static configuration of TouchScreen
  * @param  DeviceAddr: HY4614 Device address for communication on I2C Bus.
  * @retval Status HY4614_STATUS_OK or HY4614_STATUS_NOT_OK.
  */
static uint32_t hy4614_TS_Configure(uint16_t DeviceAddr)
{
  uint32_t status = HY4614_STATUS_OK;

  /* Nothing special to be done for HY4614 */

  return(status);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
