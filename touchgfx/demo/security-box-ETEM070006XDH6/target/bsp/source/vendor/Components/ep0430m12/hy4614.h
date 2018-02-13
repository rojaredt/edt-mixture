/**
  ******************************************************************************
  * @file    hy4614.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    25-June-2015
  * @brief   This file contains all the functions prototypes for the
  *          hy4614.c Touch screen driver.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HY4614_H
#define __HY4614_H

#ifdef __cplusplus
extern "C" {
#endif

/* Set Multi-touch as supported */
#if !defined(TS_MONO_TOUCH_SUPPORTED)
#define TS_MULTI_TOUCH_SUPPORTED        1
#endif /* TS_MONO_TOUCH_SUPPORTED */

/* Includes ------------------------------------------------------------------*/
#include "Common/ts.h"

/* Macros --------------------------------------------------------------------*/

#if defined(HY4614_ENABLE_ASSERT)
/* Assert activated */
#define HY4614_ASSERT(__condition__)      do { if(__condition__) \
                                               {  \
                                                 while(1);  \
                                               } \
                                          }while(0)
#else
/* Assert not activated : macro has no effect */
#define HY4614_ASSERT(__condition__)    do { if(__condition__) \
                                             {  \
                                                ;  \
                                             } \
                                            }while(0)
#endif /* HY4614_ENABLE_ASSERT == 1 */

/** @typedef hy4614_handle_TypeDef
 *  hy4614 Handle definition.
 */
typedef struct
{
  uint8_t i2cInitialized;

  /* field holding the current number of simultaneous active touches */
  uint8_t currActiveTouchNb;

  /* field holding the touch index currently managed */
  uint8_t currActiveTouchIdx;

} hy4614_handle_TypeDef;

  /** @addtogroup BSP
   * @{
   */

  /** @addtogroup Component
   * @{
   */

  /** @defgroup HY4614
   * @{
   */

  /* Exported types ------------------------------------------------------------*/

  /** @defgroup HY4614_Exported_Types
   * @{
   */

  /* Exported constants --------------------------------------------------------*/

  /** @defgroup HY4614_Exported_Constants
   * @{
   */

  /* I2C Slave address of touchscreen FocalTech HY4614 */
#define HY4614_I2C_SLAVE_ADDRESS            ((uint8_t)0x70)

  /* Maximum border values of the touchscreen pad */
#define HY4614_MAX_WIDTH                    ((uint16_t)1280)    /* Touchscreen pad max width   */
#define HY4614_MAX_HEIGHT                   ((uint16_t)768)     /* Touchscreen pad max height  */

  /* Calibration touchscreen coordinate to LCD resoulation, Conversion ratio*/
#define SUM_WIDTH_TEMP                      ((uint16_t)HY4614_MAX_WIDTH-1)
#define SUM_HEIGHT_TEMP                     ((uint16_t)HY4614_MAX_HEIGHT-1)
#define TARGET_WIDTH                        ((uint16_t)480) // LCD resolution width
#define TARGET_HEIGHT                       ((uint16_t)272) // LCD resolution height

  /* Possible values of driver functions return status */
#define HY4614_STATUS_OK                    ((uint8_t)0x00)
#define HY4614_STATUS_NOT_OK                ((uint8_t)0x01)

  /* Possible values of global variable 'TS_I2C_Initialized' */
#define HY4614_I2C_NOT_INITIALIZED          ((uint8_t)0x00)
#define HY4614_I2C_INITIALIZED              ((uint8_t)0x01)

  /* Max detectable simultaneous touches */
#define HY4614_MAX_DETECTABLE_TOUCH         ((uint8_t)0x05)

  /**
   * @brief : Definitions for HY4614 I2C register addresses on 8 bit
   **/

  /* Current mode register of the HY4614 (R/W) */
#define HY4614_DEV_MODE_REG                 ((uint8_t)0x00)

  /* Possible values of HY4614_DEV_MODE_REG */
#define HY4614_DEV_MODE_WORKING             ((uint8_t)0x00)
#define HY4614_DEV_MODE_FACTORY             ((uint8_t)0x04)

#define HY4614_DEV_MODE_MASK                ((uint8_t)0x07)
#define HY4614_DEV_MODE_SHIFT               ((uint8_t)0x04)

  /* Gesture ID register */
#define HY4614_GEST_ID_REG                  ((uint8_t)0x01)

  /* Possible values of HY4614_GEST_ID_REG */
#define HY4614_GEST_ID_NO_GESTURE           ((uint8_t)0x00)
#define HY4614_GEST_ID_MOVE_UP              ((uint8_t)0x10)
#define HY4614_GEST_ID_MOVE_RIGHT           ((uint8_t)0x14)
#define HY4614_GEST_ID_MOVE_DOWN            ((uint8_t)0x18)
#define HY4614_GEST_ID_MOVE_LEFT            ((uint8_t)0x1C)
#define HY4614_GEST_ID_SINGLE_CLICK         ((uint8_t)0x20)
#define HY4614_GEST_ID_DOUBLE_CLICK         ((uint8_t)0x22)
#define HY4614_GEST_ID_ROTATE_CLOCKWISE     ((uint8_t)0x28)
#define HY4614_GEST_ID_ROTATE_C_CLOCKWISE   ((uint8_t)0x29)
#define HY4614_GEST_ID_ZOOM_IN              ((uint8_t)0x40)
#define HY4614_GEST_ID_ZOOM_OUT             ((uint8_t)0x49)

  /* Touch Data Status register : gives number of active touch points (0..5) */
#define HY4614_TD_STAT_REG                  ((uint8_t)0x02)

  /* Values related to HY4614_TD_STAT_REG */
#define HY4614_TD_STAT_MASK                 ((uint8_t)0x0F)
#define HY4614_TD_STAT_SHIFT                ((uint8_t)0x00)

  /* Values Pn_XH and Pn_YH related */
#define HY4614_TOUCH_EVT_FLAG_PRESS_DOWN    ((uint8_t)0x00)
#define HY4614_TOUCH_EVT_FLAG_LIFT_UP       ((uint8_t)0x01)
#define HY4614_TOUCH_EVT_FLAG_CONTACT       ((uint8_t)0x02)
#define HY4614_TOUCH_EVT_FLAG_NO_EVENT      ((uint8_t)0x03)

#define HY4614_TOUCH_EVT_FLAG_SHIFT         ((uint8_t)0x06)
#define HY4614_TOUCH_EVT_FLAG_MASK          ((uint8_t)(3 << HY4614_TOUCH_EVT_FLAG_SHIFT))

#define HY4614_TOUCH_POS_MSB_MASK           ((uint8_t)0x0F)
#define HY4614_TOUCH_POS_MSB_SHIFT          ((uint8_t)0x00)

  /* Values Pn_XL and Pn_YL related */
#define HY4614_TOUCH_POS_LSB_MASK           ((uint8_t)0xFF)
#define HY4614_TOUCH_POS_LSB_SHIFT          ((uint8_t)0x00)

#define HY4614_P1_XH_REG                    ((uint8_t)0x03)
#define HY4614_P1_XL_REG                    ((uint8_t)0x04)
#define HY4614_P1_YH_REG                    ((uint8_t)0x05)
#define HY4614_P1_YL_REG                    ((uint8_t)0x06)

/* Touch Pressure register value (R) */
#define HY4614_P1_WEIGHT_REG                ((uint8_t)0x07)

/* Values Pn_WEIGHT related  */
#define HY4614_TOUCH_WEIGHT_MASK            ((uint8_t)0xFF)
#define HY4614_TOUCH_WEIGHT_SHIFT           ((uint8_t)0x00)

/* Touch area register */
#define HY4614_P1_MISC_REG                  ((uint8_t)0x08)

/* Values related to HY4614_Pn_MISC_REG */
#define HY4614_TOUCH_AREA_MASK              ((uint8_t)(0x04 << 4))
#define HY4614_TOUCH_AREA_SHIFT             ((uint8_t)0x04)

#define HY4614_P2_XH_REG                    ((uint8_t)0x09)
#define HY4614_P2_XL_REG                    ((uint8_t)0x0A)
#define HY4614_P2_YH_REG                    ((uint8_t)0x0B)
#define HY4614_P2_YL_REG                    ((uint8_t)0x0C)
#define HY4614_P2_WEIGHT_REG                ((uint8_t)0x0D)
#define HY4614_P2_MISC_REG                  ((uint8_t)0x0E)

#define HY4614_P3_XH_REG                    ((uint8_t)0x0F)
#define HY4614_P3_XL_REG                    ((uint8_t)0x10)
#define HY4614_P3_YH_REG                    ((uint8_t)0x11)
#define HY4614_P3_YL_REG                    ((uint8_t)0x12)
#define HY4614_P3_WEIGHT_REG                ((uint8_t)0x13)
#define HY4614_P3_MISC_REG                  ((uint8_t)0x14)

#define HY4614_P4_XH_REG                    ((uint8_t)0x15)
#define HY4614_P4_XL_REG                    ((uint8_t)0x16)
#define HY4614_P4_YH_REG                    ((uint8_t)0x17)
#define HY4614_P4_YL_REG                    ((uint8_t)0x18)
#define HY4614_P4_WEIGHT_REG                ((uint8_t)0x19)
#define HY4614_P4_MISC_REG                  ((uint8_t)0x1A)

#define HY4614_P5_XH_REG                    ((uint8_t)0x1B)
#define HY4614_P5_XL_REG                    ((uint8_t)0x1C)
#define HY4614_P5_YH_REG                    ((uint8_t)0x1D)
#define HY4614_P5_YL_REG                    ((uint8_t)0x1E)
#define HY4614_P5_WEIGHT_REG                ((uint8_t)0x1F)
#define HY4614_P5_MISC_REG                  ((uint8_t)0x20)

#define HY4614_P6_XH_REG                    ((uint8_t)0x21)
#define HY4614_P6_XL_REG                    ((uint8_t)0x22)
#define HY4614_P6_YH_REG                    ((uint8_t)0x23)
#define HY4614_P6_YL_REG                    ((uint8_t)0x24)
#define HY4614_P6_WEIGHT_REG                ((uint8_t)0x25)
#define HY4614_P6_MISC_REG                  ((uint8_t)0x26)

#define HY4614_P7_XH_REG                    ((uint8_t)0x27)
#define HY4614_P7_XL_REG                    ((uint8_t)0x28)
#define HY4614_P7_YH_REG                    ((uint8_t)0x29)
#define HY4614_P7_YL_REG                    ((uint8_t)0x2A)
#define HY4614_P7_WEIGHT_REG                ((uint8_t)0x2B)
#define HY4614_P7_MISC_REG                  ((uint8_t)0x2C)

#define HY4614_P8_XH_REG                    ((uint8_t)0x2D)
#define HY4614_P8_XL_REG                    ((uint8_t)0x2E)
#define HY4614_P8_YH_REG                    ((uint8_t)0x2F)
#define HY4614_P8_YL_REG                    ((uint8_t)0x30)
#define HY4614_P8_WEIGHT_REG                ((uint8_t)0x31)
#define HY4614_P8_MISC_REG                  ((uint8_t)0x32)

#define HY4614_P9_XH_REG                    ((uint8_t)0x33)
#define HY4614_P9_XL_REG                    ((uint8_t)0x34)
#define HY4614_P9_YH_REG                    ((uint8_t)0x35)
#define HY4614_P9_YL_REG                    ((uint8_t)0x36)
#define HY4614_P9_WEIGHT_REG                ((uint8_t)0x37)
#define HY4614_P9_MISC_REG                  ((uint8_t)0x38)

#define HY4614_P10_XH_REG                   ((uint8_t)0x39)
#define HY4614_P10_XL_REG                   ((uint8_t)0x3A)
#define HY4614_P10_YH_REG                   ((uint8_t)0x3B)
#define HY4614_P10_YL_REG                   ((uint8_t)0x3C)
#define HY4614_P10_WEIGHT_REG               ((uint8_t)0x3D)
#define HY4614_P10_MISC_REG                 ((uint8_t)0x3E)

  /* Threshold for touch detection */
#define HY4614_TH_GROUP_REG                 ((uint8_t)0x80)

  /* Values HY4614_TH_GROUP_REG : threshold related  */
#define HY4614_THRESHOLD_MASK               ((uint8_t)0xFF)
#define HY4614_THRESHOLD_SHIFT              ((uint8_t)0x00)

  /* Filter function coefficients */
#define HY4614_TH_DIFF_REG                  ((uint8_t)0x85)

  /* Control register */
#define HY4614_CTRL_REG                     ((uint8_t)0x86)

  /* Values related to HY4614_CTRL_REG */

  /* Will keep the Active mode when there is no touching */
#define HY4614_CTRL_KEEP_ACTIVE_MODE        ((uint8_t)0x00)

  /* Switching from Active mode to Monitor mode automatically when there is no touching */
#define HY4614_CTRL_KEEP_AUTO_SWITCH_MONITOR_MODE  ((uint8_t)0x01

  /* The time period of switching from Active mode to Monitor mode when there is no touching */
#define HY4614_TIMEENTERMONITOR_REG         ((uint8_t)0x87)

  /* Report rate in Active mode */
#define HY4614_PERIODACTIVE_REG             ((uint8_t)0x88)

  /* Report rate in Monitor mode */
#define HY4614_PERIODMONITOR_REG            ((uint8_t)0x89)

  /* The value of the minimum allowed angle while Rotating gesture mode */
#define HY4614_RADIAN_VALUE_REG             ((uint8_t)0x91)

  /* Maximum offset while Moving Left and Moving Right gesture */
#define HY4614_OFFSET_LEFT_RIGHT_REG        ((uint8_t)0x92)

  /* Maximum offset while Moving Up and Moving Down gesture */
#define HY4614_OFFSET_UP_DOWN_REG           ((uint8_t)0x93)

  /* Minimum distance while Moving Left and Moving Right gesture */
#define HY4614_DISTANCE_LEFT_RIGHT_REG      ((uint8_t)0x94)

  /* Minimum distance while Moving Up and Moving Down gesture */
#define HY4614_DISTANCE_UP_DOWN_REG         ((uint8_t)0x95)

  /* Maximum distance while Zoom In and Zoom Out gesture */
#define HY4614_DISTANCE_ZOOM_REG            ((uint8_t)0x96)

  /* High 8-bit of LIB Version info */
#define HY4614_LIB_VER_H_REG                ((uint8_t)0xA1)

  /* Low 8-bit of LIB Version info */
#define HY4614_LIB_VER_L_REG                ((uint8_t)0xA2)

  /* Chip Selecting */
#define HY4614_CIPHER_REG                   ((uint8_t)0xA3)

  /* Interrupt mode register (used when in interrupt mode) */
#define HY4614_GMODE_REG                    ((uint8_t)0xA4)

#define HY4614_G_MODE_INTERRUPT_MASK        ((uint8_t)0x03)
#define HY4614_G_MODE_INTERRUPT_SHIFT       ((uint8_t)0x00)

  /* Possible values of HY4614_GMODE_REG */
#define HY4614_G_MODE_INTERRUPT_POLLING     ((uint8_t)0x00)
#define HY4614_G_MODE_INTERRUPT_TRIGGER     ((uint8_t)0x01)

  /* Current power mode the HY4614 system is in (R) */
#define HY4614_PWR_MODE_REG                 ((uint8_t)0xA5)

  /* HY4614 firmware version */
#define HY4614_FIRMID_REG                   ((uint8_t)0xA6)

  /* HY4614 Chip identification register */
#define HY4614_CHIP_ID_REG                  ((uint8_t)0xA8)

  /*  Possible values of HY4614_CHIP_ID_REG */
#define HY4614_ID_VALUE                     ((uint8_t)0x43)

  /* Release code version */
#define HY4614_RELEASE_CODE_ID_REG          ((uint8_t)0xAF)

  /* Current operating mode the HY4614 system is in (R) */
#define HY4614_STATE_REG                    ((uint8_t)0xBC)

  /**
   * @}
   */

  /* Exported macro ------------------------------------------------------------*/

  /** @defgroup hy4614_Exported_Macros
   * @{
   */

  /* Exported functions --------------------------------------------------------*/

  /** @defgroup hy4614_Exported_Functions
   * @{
   */

  /**
   * @brief hy4614 Control functions
   */

/**
 * @brief  Calculate the conversion ratio 
 *         from touchscreen to LCD.
 * @param  conversion ratio width, conversion ratio height
 * @retval None
 */
void conversion_ratio_Cal(void);

/**
 * @brief  Initialize the hy4614 communication bus
 *         from MCU to HY4614 : ie I2C channel initialization (if required).
 * @param  DeviceAddr: Device address on communication Bus (I2C slave address of HY4614).
 * @retval None
 */
void hy4614_Init(uint16_t DeviceAddr);

/**
 * @brief  Software Reset the hy4614.
 * @param  DeviceAddr: Device address on communication Bus (I2C slave address of HY4614).
 * @retval None
 */
void hy4614_Reset(uint16_t DeviceAddr);

/**
 * @brief  Read the hy4614 device ID, pre initialize I2C in case of need to be
 *         able to read the HY4614 device ID, and verify this is a HY4614.
 * @param  DeviceAddr: I2C HY4614 Slave address.
 * @retval The Device ID (two bytes).
 */
uint16_t hy4614_ReadID(uint16_t DeviceAddr);

/**
 * @brief  Configures the touch Screen IC device to start detecting touches
 * @param  DeviceAddr: Device address on communication Bus (I2C slave address).
 * @retval None.
 */
void hy4614_TS_Start(uint16_t DeviceAddr);

/**
 * @brief  Return if there is touches detected or not.
 *         Try to detect new touches and forget the old ones (reset internal global
 *         variables).
 * @param  DeviceAddr: Device address on communication Bus.
 * @retval : Number of active touches detected (can be 0, 1 or 2).
 */
uint8_t hy4614_TS_DetectTouch(uint16_t DeviceAddr);

/**
 * @brief  Get the touch screen X and Y positions values
 *         Manage multi touch thanks to touch Index global
 *         variable 'hy4614_handle.currActiveTouchIdx'.
 * @param  DeviceAddr: Device address on communication Bus.
 * @param  X: Pointer to X position value
 * @param  Y: Pointer to Y position value
 * @retval None.
 */
void hy4614_TS_GetXY(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y);

/**
 * @brief  Configure the HY4614 device to generate IT on given INT pin
 *         connected to MCU as EXTI.
 * @param  DeviceAddr: Device address on communication Bus (Slave I2C address of HY4614).
 * @retval None
 */
void hy4614_TS_EnableIT(uint16_t DeviceAddr);

/**
 * @brief  Configure the HY4614 device to stop generating IT on the given INT pin
 *         connected to MCU as EXTI.
 * @param  DeviceAddr: Device address on communication Bus (Slave I2C address of HY4614).
 * @retval None
 */
void hy4614_TS_DisableIT(uint16_t DeviceAddr);

/**
 * @brief  Get IT status from HY4614 interrupt status registers
 *         Should be called Following an EXTI coming to the MCU to know the detailed
 *         reason of the interrupt.
 * @param  DeviceAddr: Device address on communication Bus (I2C slave address of HY4614).
 * @retval TS interrupts status
 */
uint8_t hy4614_TS_ITStatus (uint16_t DeviceAddr);

/**
 * @brief  Clear IT status in HY4614 interrupt status clear registers
 *         Should be called Following an EXTI coming to the MCU.
 * @param  DeviceAddr: Device address on communication Bus (I2C slave address of HY4614).
 * @retval TS interrupts status
 */
void hy4614_TS_ClearIT (uint16_t DeviceAddr);

/**** NEW FEATURES enabled when Multi-touch support is enabled ****/

#if (TS_MULTI_TOUCH_SUPPORTED == 1)

/**
 * @brief  Get the last touch gesture identification (zoom, move up/down...).
 * @param  DeviceAddr: Device address on communication Bus (I2C slave address of HY4614).
 * @param  pGestureId : Pointer to get last touch gesture Identification.
 * @retval None.
 */
void hy4614_TS_GetGestureID(uint16_t DeviceAddr, uint32_t * pGestureId);

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
                            uint32_t * pEvent);

#endif /* TS_MULTI_TOUCH_SUPPORTED == 1 */

/* Imported TS IO functions --------------------------------------------------------*/

/** @defgroup hy4614_Imported_Functions
 * @{
 */

/* TouchScreen (TS) external IO functions */
extern void    TS_IO_Init(void);
extern void    TS_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
extern uint8_t TS_IO_Read(uint8_t Addr, uint8_t Reg);
extern void    TS_IO_Delay(uint32_t Delay);

  /**
   * @}
   */

  /* Imported global variables --------------------------------------------------------*/

  /** @defgroup hy4614_Imported_Globals
   * @{
   */


/* Touch screen driver structure */
extern TS_DrvTypeDef hy4614_ts_drv;

  /**
   * @}
   */

#ifdef __cplusplus
}
#endif
#endif /* __HY4614_H */


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
