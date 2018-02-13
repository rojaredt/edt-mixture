/**
  ******************************************************************************
  * @file    et070001dma.h
  * @author  Embedded Display Team
  * @version V1.0.0
  * @date    2017.08.1
  * @brief   This file contains all the constants parameters for the ET070001DMA
  *          LCD component.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TFT_H
#define __TFT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/  

/** 
  * @brief  ET070001DMA Size  
  */     
#define  TFT_WIDTH    ((uint16_t)800)          /* LCD PIXEL WIDTH            */
#define  TFT_HEIGHT   ((uint16_t)480)          /* LCD PIXEL HEIGHT           */

/** 
  * @brief  ET070001DMA Timing  
  */     

    #define  TFT_HSYNC            ((uint16_t)40)  /* Horizontal synchronization */
    #define  TFT_HBP              ((uint16_t)6)   /* Horizontal back porch      */
    #define  TFT_HFP              ((uint16_t)210)   /* Horizontal front porch     */
    #define  TFT_VSYNC            ((uint16_t)1)    /* Vertical synchronization   */
    #define  TFT_VBP              ((uint16_t)22)   /* Vertical back porch        */
    #define  TFT_VFP              ((uint16_t)22)   /* Vertical front porch       */   
    #define  TFT_FREQUENCY_DIVIDER    2            /* LCD Frequency divider      */

   
   
//    #define  TFT_HSYNC            ((uint16_t)128)  /* Horizontal synchronization */
//    #define  TFT_HBP              ((uint16_t)88)   /* Horizontal back porch      */
//    #define  TFT_HFP              ((uint16_t)40)   /* Horizontal front porch     */
//    #define  TFT_VSYNC            ((uint16_t)2)    /* Vertical synchronization   */
//    #define  TFT_VBP              ((uint16_t)35)   /* Vertical back porch        */
//    #define  TFT_VFP              ((uint16_t)10)   /* Vertical front porch       */   
//    #define  TFT_FREQUENCY_DIVIDER    5            /* LCD Frequency divider      */ 
#ifdef __cplusplus
}
#endif

#endif /* __TFT_H */

/************************ (C) COPYRIGHT EDT *****END OF FILE****/
