/**
  ******************************************************************************  
  * @author  EDT Embedded Team  
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ETEM070006XDH6_H
#define __ETEM070006XDH6_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "etem070006xdh6_msp.h"
   
typedef enum 
{
LED1 = 0,
LED_GREEN = LED1,
}LED_TypeDef;

typedef enum 
{
  COM1 = 0,
  RS232 = 1,
  RS485 = 2
}COM_TypeDef;

/** 
  * @brief  Define for STM32746G_EDT EV board
  */ 
#if !defined (STM32746G_EDT)
 #define STM32746G_EDT
#endif

/** @addtogroup STM32746G_DISCOVERY_LOW_LEVEL_LED
  * @{
  */

#define LEDn                             ((uint8_t)1)

#define LED1_GPIO_PORT                   GPIOI
#define LED1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOI_CLK_ENABLE()
#define LED1_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOI_CLK_DISABLE()
#define LED1_PIN                         GPIO_PIN_1

/**
  * @brief Touch screen interrupt signal
  */
#define TS_INT_PIN                           GPIO_PIN_13
#define TS_INT_GPIO_PORT                     GPIOI
#define TS_INT_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOI_CLK_ENABLE()
#define TS_INT_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOI_CLK_DISABLE()
#define TS_INT_EXTI_IRQn                     EXTI15_10_IRQn

/** @addtogroup STM32746G_DISCOVERY_LOW_LEVEL_COM
  * @{
  */
#define COMn                             ((uint8_t)1)

/**
 * @brief Definition for COM port1, connected to USART1
 */ 
#define RS232                          USART6
#define RS232_CLK_ENABLE()             __HAL_RCC_USART6_CLK_ENABLE()
#define RS232_CLK_DISABLE()            __HAL_RCC_USART6_CLK_DISABLE()

#define RS232_TX_PIN                   GPIO_PIN_9
#define RS232_TX_GPIO_PORT             GPIOA
#define RS232_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define RS232_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#define RS232_TX_AF                    GPIO_AF7_USART1

#define RS232_RX_PIN                   GPIO_PIN_7
#define RS232_RX_GPIO_PORT             GPIOB
#define RS232_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define RS232_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#define RS232_RX_AF                    GPIO_AF7_USART1

#define RS232_IRQn                     USART6_IRQn

#define RS485                          USART2
#define RS485_CLK_ENABLE()             __HAL_RCC_USART1_CLK_ENABLE()
#define RS485_CLK_DISABLE()            __HAL_RCC_USART1_CLK_DISABLE()

#define RS485_TX_PIN                   GPIO_PIN_9
#define RS485_TX_GPIO_PORT             GPIOA
#define RS485_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define RS485_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#define RS485_TX_AF                    GPIO_AF7_USART1

#define RS485_RX_PIN                   GPIO_PIN_7
#define RS485_RX_GPIO_PORT             GPIOB
#define RS485_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define RS485_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#define RS485_RX_AF                    GPIO_AF7_USART1

#define RS485_IRQn                     USART2_IRQn

#define USARTx_CLK_ENABLE(__INDEX__)            do { if((__INDEX__) == COM1) RS232_CLK_ENABLE(); } while(0)
#define USARTx_CLK_DISABLE(__INDEX__)           (((__INDEX__) == 0) ? RS232_CLK_DISABLE() : 0)

#define USARTx_TX_GPIO_CLK_ENABLE(__INDEX__)    do { if((__INDEX__) == COM1) RS232_TX_GPIO_CLK_ENABLE(); } while(0)
#define USARTx_TX_GPIO_CLK_DISABLE(__INDEX__)   (((__INDEX__) == 0) ? RS232_TX_GPIO_CLK_DISABLE() : 0)

#define USARTx_RX_GPIO_CLK_ENABLE(__INDEX__)    do { if((__INDEX__) == COM1) RS232_RX_GPIO_CLK_ENABLE(); } while(0)
#define USARTx_RX_GPIO_CLK_DISABLE(__INDEX__)   (((__INDEX__) == 0) ? RS232_RX_GPIO_CLK_DISABLE() : 0)

/* Exported constant IO ------------------------------------------------------*/

#define TS_I2C_ADDRESS                   ((uint16_t)0x70)

/* I2C clock speed configuration (in Hz) 
   WARNING: 
   Make sure that this define is not already declared in other files (ie. 
   stm32746g_discovery.h file). It can be used in parallel by other modules. */
#ifndef I2C_SPEED
 #define I2C_SPEED                       ((uint32_t)100000)
#endif /* I2C_SPEED */

/* User can use this section to tailor I2Cx/I2Cx instance used and associated 
   resources */
/* Definition for EXTERNAL I2C and CTP I2Cx resources */
#define CTP_I2Cx                             I2C1
#define CTP_I2Cx_CLK_ENABLE()                __HAL_RCC_I2C1_CLK_ENABLE()
#define CTP_DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define CTP_I2Cx_SCL_SDA_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()

#define CTP_I2Cx_FORCE_RESET()               __HAL_RCC_I2C1_FORCE_RESET()
#define CTP_I2Cx_RELEASE_RESET()             __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define CTP_I2Cx_SCL_PIN                     GPIO_PIN_8
#define CTP_I2Cx_SCL_SDA_GPIO_PORT           GPIOB
#define CTP_I2Cx_SCL_SDA_AF                  GPIO_AF4_I2C1
#define CTP_I2Cx_SDA_PIN                     GPIO_PIN_9

/* I2C interrupt requests */
#define CTP_I2Cx_EV_IRQn                     I2C1_EV_IRQn
#define CTP_I2Cx_ER_IRQn                     I2C1_ER_IRQn

/* Definition for external, camera and Arduino connector I2Cx resources */
#define EXT_I2Cx                               I2C3
#define EXT_I2Cx_CLK_ENABLE()                  __HAL_RCC_I2C3_CLK_ENABLE()
#define EXT_DMAx_CLK_ENABLE()                  __HAL_RCC_DMA1_CLK_ENABLE()
//#define EXT_I2Cx_SCL_SDA_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define EXT_I2Cx_SCL_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define EXT_I2Cx_SDA_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOC_CLK_ENABLE()
#define EXT_I2Cx_FORCE_RESET()                 __HAL_RCC_I2C3_FORCE_RESET()
#define EXT_I2Cx_RELEASE_RESET()               __HAL_RCC_I2C3_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define EXT_I2Cx_SCL_PIN                       GPIO_PIN_8
//#define EXT_I2Cx_SCL_SDA_GPIO_PORT             GPIOB
#define EXT_I2Cx_SCL_GPIO_PORT                  GPIOA
#define EXT_I2Cx_SDA_GPIO_PORT                  GPIOC
#define EXT_I2Cx_SCL_SDA_AF                    GPIO_AF4_I2C3
#define EXT_I2Cx_SDA_PIN                       GPIO_PIN_9

/* I2C interrupt requests */
#define EXT_I2Cx_EV_IRQn                       I2C3_EV_IRQn
#define EXT_I2Cx_ER_IRQn                       I2C3_ER_IRQn

/* I2C TIMING Register define when I2C clock source is SYSCLK */
/* I2C TIMING is calculated from APB1 source clock = 50 MHz */
/* Due to the big MOFSET capacity for adapting the camera level the rising time is very large (>1us) */
/* 0x40912732 takes in account the big rising and aims a clock of 100khz */
#ifndef I2Cx_TIMING  
#define I2Cx_TIMING                      ((uint32_t)0x40912732)  
#endif /* DISCOVERY_I2Cx_TIMING */

/** @addtogroup STM32746G_DISCOVERY_LOW_LEVEL_Exported_Functions
  * @{
  */
uint32_t  BSP_GetVersion(void);
void      BSP_LED_Init(LED_TypeDef Led);
void      BSP_LED_DeInit(LED_TypeDef Led);
void      BSP_LED_On(LED_TypeDef Led);
void      BSP_LED_Off(LED_TypeDef Led);
void      BSP_LED_Toggle(LED_TypeDef Led);
void      BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef *husart);
void      BSP_COM_DeInit(COM_TypeDef COM, UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif

#endif /* __ETEM070006XDH6_H */
