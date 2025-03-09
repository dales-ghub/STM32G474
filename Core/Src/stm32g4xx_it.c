#include "main.h"
#include "board.h"
#include "stm32g4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */


/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_FS;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g4xx.s).                    */
/******************************************************************************/
void ADC5_IRQHandler(void)
  {
  ADC5->ISR &= ~(0xF);
  }
  
void DMA1_Channel1_IRQHandler(void)
  {
  DMA1->IFCR = (DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TCIF1 | DMA_ISR_GIF1);
  DMA1_Channel1->CCR = 0;
  }
  
void DMA1_Channel2_IRQHandler(void)
  {
  DMA1->IFCR = (DMA_ISR_TCIF2 | DMA_ISR_HTIF2 | DMA_ISR_TCIF2 | DMA_ISR_GIF2);
  DMA1_Channel2->CCR = 0;
  }
  
void DMA1_Channel3_IRQHandler(void)
  {
  DMA1->IFCR = (DMA_ISR_TCIF3 | DMA_ISR_HTIF3 | DMA_ISR_TCIF3 | DMA_ISR_GIF3);
  DMA1_Channel3->CCR = 0;
  }
  
void DMA1_Channel4_IRQHandler(void)
  {
  DMA1->IFCR = (DMA_ISR_TCIF4 | DMA_ISR_HTIF4 | DMA_ISR_TCIF4 | DMA_ISR_GIF4);
  DMA1_Channel4->CCR = 0;
  }
  
void DMA1_Channel5_IRQHandler(void)
  {
  DMA1->IFCR = (DMA_ISR_TCIF5 | DMA_ISR_HTIF5 | DMA_ISR_TCIF5 | DMA_ISR_GIF5);
  DMA1_Channel1->CCR = 0;
  }
  
void DMA1_Channel6_IRQHandler(void)
  {
  DMA1->IFCR = (DMA_ISR_TCIF6 | DMA_ISR_HTIF6 | DMA_ISR_TCIF6 | DMA_ISR_GIF6);
  DMA1_Channel2->CCR = 0;
  }
  
void DMA1_Channel7_IRQHandler(void)
  {
  DMA1->IFCR = (DMA_ISR_TCIF7 | DMA_ISR_HTIF7 | DMA_ISR_TCIF7 | DMA_ISR_GIF7);
  DMA1_Channel3->CCR = 0;
  }
  
void DMA1_Channel8_IRQHandler(void)
  {
  DMA1->IFCR = (DMA_ISR_TCIF8 | DMA_ISR_HTIF8 | DMA_ISR_TCIF8 | DMA_ISR_GIF8);
  DMA1_Channel4->CCR = 0;
  }
  
void DMA2_Channel1_IRQHandler(void)
  {
  DMA2->IFCR = (DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TCIF1 | DMA_ISR_GIF1);
  DMA2_Channel1->CCR = 0;
  }
  
void DMA2_Channel2_IRQHandler(void)
  {
  DMA2->IFCR = (DMA_ISR_TCIF2 | DMA_ISR_HTIF2 | DMA_ISR_TCIF2 | DMA_ISR_GIF2);
  DMA2_Channel2->CCR = 0;
  }

uint8_t SPI2_DMAx = 0;
  
void DMA2_Channel3_IRQHandler(void)
  {
  DMA2->IFCR = (DMA_ISR_TCIF3 | DMA_ISR_HTIF3 | DMA_ISR_TCIF3 | DMA_ISR_GIF3);
  DMA2_Channel3->CCR = 0;
  SPI2_DMAx = 1;
  }
  
void DMA2_Channel4_IRQHandler(void)
  {
  DMA2->IFCR = (DMA_ISR_TCIF4 | DMA_ISR_HTIF4 | DMA_ISR_TCIF4 | DMA_ISR_GIF4);
  DMA2_Channel4->CCR = 0;
  }
  
// Port[A:G] bit 0
void EXTI0_IRQHandler(void)
  {
  EXTI->PR1 |=  EXTI_PR1_PIF0;
  }
  
// Port[A:G] bit 1
void EXTI1_IRQHandler(void)
  {
  EXTI->PR1 |=  EXTI_PR1_PIF1;
  }
  
// Port[A:G] bit 2
void EXTI2_IRQHandler(void)
  {
  EXTI->PR1 |=  EXTI_PR1_PIF2;
  }
  
// Port[A:G] bit 3
void EXTI3_IRQHandler(void)
  {
  EXTI->PR1 |=  EXTI_PR1_PIF3;
  }
  
// Port[A:G] bit 4
void EXTI4_IRQHandler(void)
  {
  EXTI->PR1 |=  EXTI_PR1_PIF4;
  }

// Port[A:G] bit 5:9
void EXTI9_5_IRQHandler(void)
  {
  extern uint32_t menu_cntr_1;
  if ((EXTI->PR1 & EXTI_PR1_PIF5) == EXTI_PR1_PIF5)
    EXTI->PR1 |=  EXTI_PR1_PIF5;
  if ((EXTI->PR1 & EXTI_PR1_PIF6) == EXTI_PR1_PIF6)
    EXTI->PR1 |=  EXTI_PR1_PIF6;
  if ((EXTI->PR1 & EXTI_PR1_PIF7) == EXTI_PR1_PIF7)
    EXTI->PR1 |=  EXTI_PR1_PIF7;
  if ((EXTI->PR1 & EXTI_PR1_PIF8) == EXTI_PR1_PIF8)
    {
    EXTI->PR1 |=  EXTI_PR1_PIF8;
    menu_cntr_1++;
    }
  if ((EXTI->PR1 & EXTI_PR1_PIF9) == EXTI_PR1_PIF9)
    {
    EXTI->PR1 |=  EXTI_PR1_PIF9;
    }
  }

// Port[A:G] bit 10:15
void EXTI15_10_IRQHandler(void)
  {
  extern uint32_t menu_cntr_2;
  if ((EXTI->PR1 & EXTI_PR1_PIF10) == EXTI_PR1_PIF10)
    EXTI->PR1 |=  EXTI_PR1_PIF10;
  if ((EXTI->PR1 & EXTI_PR1_PIF11) == EXTI_PR1_PIF11)
    EXTI->PR1 |=  EXTI_PR1_PIF11;
  if ((EXTI->PR1 & EXTI_PR1_PIF12) == EXTI_PR1_PIF12)
    EXTI->PR1 |=  EXTI_PR1_PIF12;
  if ((EXTI->PR1 & EXTI_PR1_PIF13) == EXTI_PR1_PIF13)
    {
    EXTI->PR1 |=  EXTI_PR1_PIF13;
    menu_cntr_2++;
    }
  if ((EXTI->PR1 & EXTI_PR1_PIF14) == EXTI_PR1_PIF14)
    EXTI->PR1 |=  EXTI_PR1_PIF14;
  if ((EXTI->PR1 & EXTI_PR1_PIF15) == EXTI_PR1_PIF15)
    EXTI->PR1 |=  EXTI_PR1_PIF15;
  }
  
void LPUART1_IRQHandler(void)
  {
  extern uint32_t lpuart1_txCNT, lpuart1_rxPtr;
  extern char *lpuart1_txPtr, lpuart1_rxData[32];
  extern uint32_t menu_cntr_1, menu_cntr_2;
//  extern unsigned char _binary_blob_bin_start;

    // Frame error, noise, over run
  if (LPUART1->ISR & (USART_ISR_FE | USART_ISR_NE | USART_ISR_ORE))
    {
    LPUART1->ICR |= (USART_ISR_FE | USART_ISR_NE | USART_ISR_ORE);
    menu_cntr_2++;
    }

    // Character match flag
  if ((LPUART1->ISR & USART_ISR_CMF) == USART_ISR_CMF)
    {
    LPUART1->ICR |= USART_ISR_CMF;
    menu_cntr_1++;
//    MX_USART1_Tx((char *)&(lpuart1_rxData[0]), 15);
//    MX_USART1_Tx((char *)&_binary_blob_bin_start,8);
    }

    // Receive character
  if ((LPUART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
    {
    LPUART1->ICR |= USART_ISR_RXNE;
    lpuart1_rxData[lpuart1_rxPtr++] = LPUART1->RDR;
    if(lpuart1_rxPtr > 31)
      lpuart1_rxPtr = 0;
    menu_cntr_1++;
    }

    // Transmit character
  if ((LPUART1->ISR & USART_ISR_TXE) == USART_ISR_TXE)
    {
    LPUART1->ICR |= USART_ISR_TXE;
    if(lpuart1_txCNT > 0)
      {
      lpuart1_txCNT--;
      LPUART1->TDR = *lpuart1_txPtr++;
      }
    else
      LPUART1->CR1 &= ~(USART_CR1_TXEIE_TXFNFIE);
    }
  }

void RTC_Alarm_IRQHandler(void)
  {
  extern uint32_t menu_cntr_1;
  extern uint32_t menu_cntr_2;
//  EXTI->PR1 |= EXTI_PR1_PIF17;
  if((RTC->MISR & RTC_MISR_ALRAMF) == RTC_MISR_ALRAMF)
    {
    RTC->SCR |= RTC_SCR_CALRAF;
    menu_cntr_1 = 0;
    }
  if((RTC->MISR & RTC_MISR_ALRBMF) == RTC_MISR_ALRBMF)
    {
    EXTI->PR1 |= EXTI_PR1_PIF17;
    RTC->SCR |= RTC_SCR_CALRBF;
    menu_cntr_2 = 0;
    }
  }
  
void SPI1_IRQHandler(void)
  {
  extern char * SPI1_ptrIn;
  extern char * SPI1_ptrOut;
  extern uint32_t SPI1_bytes;
  uint16_t temp;
  if ((SPI1->SR & SPI_SR_TXE) == SPI_SR_TXE)
    {
    while(((SPI1->SR & SPI_SR_TXE) == SPI_SR_TXE) && (SPI1_bytes > 0))
      {
      temp = *SPI1_ptrOut++;
      SPI1_bytes--;
      temp |= (*SPI1_ptrOut++)<<8;
      if(SPI1_bytes > 0)
        SPI1_bytes--;
      SPI1->DR = temp;
      }

    if(SPI1_bytes == 0)
      SPI1->CR2 &= ~SPI_CR2_TXEIE;
    } 
  if ((SPI1->SR & SPI_SR_RXNE) == SPI_SR_RXNE)
    *SPI1_ptrIn++ = SPI1->DR;
  }

void TIM2_IRQHandler(void)
  {
  TIM2->SR &= ~TIM_SR_UIF;
  }
  
void TIM3_IRQHandler(void)
  {
  TIM3->SR &= ~TIM_SR_UIF;  // clear irqs
  }
  
void TIM4_IRQHandler(void)
  {
  extern uint16_t tim4_ccr;
  extern uint16_t dacVal;
  TIM4->SR &= ~TIM_DIER_CC1IE; // clear irq
  if(++tim4_ccr > 999)
    tim4_ccr = 1;
  TIM4->CCR1 = tim4_ccr;
  if(++dacVal > 4095)
    dacVal = 0;
  DAC1->DHR12R1 = dacVal;
  DAC2->DHR12R1 = 4095 - dacVal;
  }

void TIM5_IRQHandler(void)
  {
  TIM5->SR &= ~TIM_SR_UIF;  // clear irqs
  GPIOC->BSRR = (uint32_t)GPIO_PIN_11;
  }
  
//void TIM20_BRK_IRQHandler(void)
//void TIM20_CC_IRQHandler(void)
//void TIM20_TRG_COM_IRQHandler(void)

void TIM20_UP_IRQHandler(void)
  {
  TIM20->SR = 0; // clear irq
  GPIOC->BRR = (uint32_t)GPIO_PIN_11;
  }
  
void USART1_IRQHandler(void)
  {
  extern uint32_t usart1_txCNT, usart1_rxPtr;
  extern char *usart1_txPtr, *usart1_rxData;
  extern uint32_t menu_cntr_2;

    // Frame error, noise, over run
  if (USART1->ISR & (USART_ISR_FE | USART_ISR_NE | USART_ISR_ORE))
    {
    USART1->ICR |= (USART_ISR_FE | USART_ISR_NE | USART_ISR_ORE);
    menu_cntr_2++;
    }

    // receive character
  if ((USART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
    {
    USART1->ICR |= USART_ISR_RXNE;
    usart1_rxData[usart1_rxPtr++] = USART1->RDR;
    if(usart1_rxPtr > 15)
      usart1_rxPtr = 0;
    }

    // Transmit character
  if ((USART1->ISR & USART_ISR_TXE) == USART_ISR_TXE)
    {
    USART1->ICR |= USART_ISR_TXE;
    if(usart1_txCNT > 0)
      {
      usart1_txCNT--;
      USART1->TDR = *usart1_txPtr++;
      }
    else
      USART1->CR1 &= ~(USART_CR1_TXEIE_TXFNFIE);
    }
  }

void USART2_IRQHandler(void)
  {
  USART2->ICR |= 0x7f;
  }
  
void USART3_IRQHandler(void)
  {
//  extern uint32_t usart3_txCNT, usart3_rxPtr;
//  extern char *usart3_txPtr, *usart3_rxData;
  extern uint32_t menu_cntr_2;

// Frame error, noise, over run
  if (USART3->ISR & (USART_ISR_FE | USART_ISR_NE | USART_ISR_ORE))
    {
    USART3->ICR |= (USART_ISR_FE | USART_ISR_NE | USART_ISR_ORE);
    menu_cntr_2++;
    }

    // receive character
  if ((USART3->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
    {
    USART3->ICR |= USART_ISR_RXNE;
//    usart3_rxData[usart3_rxPtr++] = USART3->RDR;
//    if(usart3_rxPtr > 15)
//      usart3_rxPtr = 0;
    }

    // Transmit character
  if ((USART3->ISR & USART_ISR_TXE) == USART_ISR_TXE)
    {
    USART3->ICR |= USART_ISR_TXE;
//    if(usart3_txCNT > 0)
//      {
//      usart3_txCNT--;
//      USART3->TDR = *usart3_txPtr++;
//      }
//    else
//      USART3->CR1 &= ~(USART_CR1_TXEIE_TXFNFIE);
    }
  }

void USB_LP_IRQHandler(void)
  {
  HAL_PCD_IRQHandler(&hpcd_USB_FS);
  }
