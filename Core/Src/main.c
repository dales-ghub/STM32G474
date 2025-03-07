//*******************************************************************************
// file           : main.c
//*******************************************************************************

/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "adc.h"
#include "adc.h"
#include "analog.h"
#include "board.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "timer.h"
#include "uart.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include <string.h>
#define TEST1
#define TEST2
#define TEST3

void rtc(char*s);

uint32_t resetFlags;
uint16_t tim4_ccr = 1;
uint16_t dacVal = 0;
uint8_t I2C_data[20];
int ADC1_Val = 0;
int ADC2_Val = 0;

int main(void)
  {
  uint32_t count, tick, tick_now;
  extern char lpuart1_txData[LPUART1_TX_SIZE];
  extern uint32_t lpuart1_txCNT;
  extern char usart1_txData[USRART1_TX_SIZE];
  extern uint32_t usart1_txCNT;
  I2C_struct * I2C1_PTR;
  
  resetFlags = RCC->CSR;
  HAL_Init();
  SystemClock_Config();
  /* Initialize all configured peripherals */
    // GPIO Port A, B, C, F Clock Enable */
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOFEN |
                   RCC_AHB2ENR_GPIOCEN |
                   RCC_AHB2ENR_GPIOBEN |
                   RCC_AHB2ENR_GPIOAEN);

  COMP5_Init();
  ADC1_Init();
  ADC2_Init();
  ADC3_Init();
  ADC4_Init();
  ADC5_Init();
  DAC1_Init();
  DAC2_Init();
//  IWD_Init();
#ifdef TEST1
  LPUART1d_Init(9600);
#else
  LPUART1_Init(19200);
#endif
  RND_Init();
  SPI1d_Init();
  RTC_Init();
  TIM1_Init();
  TIM3_Init();
  TIM4_Init();
  TIM5_Init();
  TIM20_Init();
  USART1d_Init(4800);
  USART3d_Init(4800);
  
  MX_USB_Device_Init();
  
  /* USER CODE BEGIN 2 */
  board_gpio_init(); 
  
  tick = HAL_GetTick() + 200;
  tick_now = HAL_GetTick();
 
  GPIOB->BSRR = (uint32_t)C_RESET_Pin; // set pin
  GPIOB->BSRR = GPIO_PIN_12;   // I2C_Test
 
  uint8_t text[60];
  int text_lenth;
  char usart3_txData[20];
  for(count = 2; count < 18; count++)
    I2C_data[count] = count;
  RCC->CSR |= RCC_CSR_RMVF; // Clear reset flags
  
  count = 0;
  WWDG_Init();    // ToFix
  I2C1_PTR = I2C1_Init(I2C_data);

  /* Infinite loop */
  while (1)
    {
    tick_now = HAL_GetTick();
    WWDG_Tickle();      // ToFix
//    GPIOB->BSRR = GPIO_PIN_12;   // I2C_Test
    if((RTC->MISR & RTC_MISR_ALRAMF) == RTC_MISR_ALRAMF)
        {
        RTC->SCR |= RTC_SCR_CALRAF;
        rtc((char *)text);
        }
    if(tick_now >= tick)
      {
      LED_Pin_toggle();
      if((GPIOB->IDR & BOOT0_Pin) == BOOT0_Pin) // BOOT0
        {
        tick = tick_now + 200;
        GPIOB->BRR = (uint32_t)C_RESET_Pin; // clear pin
        GPIOB->BSRR = GPIO_PIN_12;   // I2C_Test
        TIM1->CCR1 = 200;
        ADC2_Val = ADC_rd(4);
        ADC1_Val = ADC_rd(5);
        text_lenth = sprintf((char *) &text,"adc [%ld] %dmV %dmV\r\n",
            count++, 
            (ADC1_Val*3300) >> 16, 
            (ADC2_Val*3300) >> 16);
        CDC_Transmit_FS(text,text_lenth);
        }
      else if (KEY_Pin_getstate())
        {
        ADC_Cal(5);
        DS3231_set(I2C1_PTR);
        tick = tick_now + 100;
        GPIOB->BSRR = (uint32_t)C_RESET_Pin; // set pin
        TIM1->CCR1 = 100;
        ADC1_Val = ADC_rd(1);
        ADC2_Val = ADC_rd(2);
        text_lenth = sprintf((char *) &text,"adc [%lx] %dmV %dmV\r\n",
            RNG->DR, 
            (ADC1_Val*3300) >> 16, 
            (ADC2_Val*3300) >> 16);
        CDC_Transmit_FS(text,text_lenth);
        }
      else
        {
        tick = tick_now + 50;
        ADC1_Val = ADC_rd(4);
        ADC2_Val = ADC_rd(5);
        lpuart1_txCNT = sprintf((char *) &lpuart1_txData[0],
            "adc (%ld) %dmV %dmV\r\n",
            count++, 
            (ADC1_Val*3300) >> 16, 
            (ADC2_Val*3300) >> 16);
#ifdef TEST1
        LPUART1d_Tx(&lpuart1_txData[0],lpuart1_txCNT);
#else
        LPUART1_Tx(&lpuart1_txData[0],--lpuart1_txCNT);
#endif
        usart1_txCNT = sprintf((char *) &usart1_txData[0],"%ld\n", tick);
        USART1d_Tx(&usart1_txData[0], usart1_txCNT);
        
        text_lenth = sprintf((char *) &text,"SPI1 \n"); 
        SPI1d_Start((char *) &text, (char *) &text, text_lenth);
        text_lenth = sprintf((char *) &usart3_txData,"Count %ld\n", count); 
        USART3d_Tx(&usart3_txData[0], text_lenth);
//        IWD_Tickle();
        GPIOA->OTYPER |= (1<<(14));            // GPIO_PIN OPEN DRAIN
        I2C_data[0] = 0;
        I2C1_PTR->Addr = 0x68 << 1;
        I2C1_PTR->Ptr = I2C_data;
        I2C1_PTR->readBytes = 13;
        I2C1_PTR->writeBytes = 1;
        I2C_Start(I2C1_PTR);
        GPIOB->BSRR = GPIO_PIN_12;   // I2C_Test
        }
      }
    }
  }


void Error_Handler(void)
  {
  __disable_irq();
  while (1)
    {
    }
  }

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

