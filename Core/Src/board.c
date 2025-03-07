#include "board.h"

void board_gpio_init(void)
    {
    int pin;
    // PA 0x48000000
    // PA0
    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOFEN |
                   RCC_AHB2ENR_GPIOCEN |
                   RCC_AHB2ENR_GPIOBEN |
                   RCC_AHB2ENR_GPIOAEN);

    pin = 0;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));     // GPIO_PIN MASK
    GPIOA->MODER |= (MODE_INPUT<<(2*pin));     // GPIO_PIN INPUT
    GPIOA->PUPDR &= ~(GPIO_MODE<<(2*pin));     // GPIO_PIN MASK
    GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));    // GPIO_PIN PULLUP
    SYSCFG->EXTICR[pin/4] &= ~(0xf << (4*(pin%4))); 
    SYSCFG->EXTICR[pin/4] |= (1<<(4*(pin%4)));  // PA0 A=0, B=1, C=2
    EXTI->RTSR1 &= ~(EXTI_IMR1_IM0);            // rising edge
    EXTI->FTSR1 |= (EXTI_IMR1_IM0);             // falling edge
    EXTI->IMR1 |= (EXTI_IMR1_IM0);
    NVIC_SetPriority(EXTI0_IRQn, 0x03);
    NVIC_EnableIRQ(EXTI0_IRQn);

    // PA1

    // PA2     ------> LPUART1_TX
    pin = 2;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOA->AFR[0] |= (GPIO_AF12_LPUART1<<(4*pin));  // GPIO_PIN 4*(2)
    GPIOA->PUPDR &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN NOPULLUP
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));  

    // PA3     ------> LPUART1_RX
    pin = 3;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN INPUT
    GPIOA->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOA->AFR[0] |= (GPIO_AF12_LPUART1<<(4*pin));  // GPIO_PIN 4*(3)
    GPIOA->PUPDR &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));         // GPIO_PIN PULLDOWN

    // PA4     ------> DAC1_OUT1 dac.c
    // PA5     ------> DAC1_OUT2
    pin = 5;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));    // GPIO_PIN MASK
    GPIOA->MODER |= (MODE_ANALOG<<(2*pin));   // GPIO_PIN OUTPUT
    GPIOA->PUPDR &= ~(GPIO_MODE<<(2*pin));    // GPIO_PIN NOPULLUP

    // PA6     ------> DAC2_OUT1 dac.c

    // PA8     ------> TIM1_CH1
    pin = 8;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[1] &= ~(15<<(4*(pin-8)));            // GPIO_PIN MASK
    GPIOA->AFR[1] |= (GPIO_AF6_TIM1<<(4*(pin-8)));  // GPIO_PIN 4*(1)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOA->OSPEEDR &= (3<<(2*pin));                 // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));

    // PA9     ------> TIM1_CH2
    pin = 9;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[1] &= ~(15<<(4*(pin-8)));            // GPIO_PIN MASK
    GPIOA->AFR[1] |= (GPIO_AF6_TIM1<<(4*(pin-8)));  // GPIO_PIN 4*(1)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOA->PUPDR &= ~(3<<(2*pin));                  // GPIO_PIN MASK
    GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));
    GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));

    // PA10    ------> TIM1_CH3
    pin = 10;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[1] &= ~(15<<(4*(pin-8)));            // GPIO_PIN MASK
    GPIOA->AFR[1] |= (GPIO_AF6_TIM1<<(4*(pin-8)));  // GPIO_PIN 4*(2)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));

    // PA11    ======> USB_DN
    // PA12    ======> USB_DP

    // PA13    ======> SWDIO
    // IN I2C.c

    // PA14    ======> SWCLK
    // IN I2C.c

    // PA15    ------> SPI1_NSS spi.c
    pin = 15;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[1] &= ~(15<<(4*(pin-8)));            // GPIO_PIN MASK
    GPIOA->AFR[1] |= (GPIO_AF5_SPI1<<(4*(pin-8)));  // GPIO_PIN 4*(2)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));
  
    // PB 0x48000400
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    // PB1     ------> ADC1_IN12 adc.c 
    // PB2     ------> ADC2_IN12 adc.c

    // PB3     ------> SPI1_SCK spi.c
    pin = 3;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOB->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOB->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOB->AFR[0] |= (GPIO_AF5_SPI1<<(4*pin));      // GPIO_PIN 4*(6)
    GPIOB->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOB->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOB->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOB->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));

    // PB4     ------> SPI1_MISO spi.c
    pin = 4;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOB->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOB->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOB->AFR[0] |= (GPIO_AF5_SPI1<<(4*pin));      // GPIO_PIN 4*(6)
    GPIOB->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOB->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOB->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOB->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));

    // PB5     ------> SPI1_MOSI spi.c
    pin = 5;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOB->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOB->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOB->AFR[0] |= (GPIO_AF5_SPI1<<(4*pin));      // GPIO_PIN 4*(6)
    GPIOB->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOB->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOB->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOB->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));

    \
    // PB6     ------> TIM4_CH1
    pin = 6;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOB->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOB->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOB->AFR[0] |= (GPIO_AF2_TIM4<<(4*pin));      // GPIO_PIN 4*(6)
    GPIOB->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOB->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOB->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOB->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));

    // PB7     ------> USART1_RX
    pin = 7;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));        // GPIO_PIN MASK
    GPIOB->MODER |= (GPIO_MODE_AF_PP<<(2*pin));   // GPIO_PIN INPUT
    GPIOB->AFR[0] &= ~(15<<(4*pin));              // GPIO_PIN MASK
    GPIOB->AFR[0] |= (GPIO_AF7_USART1<<(4*pin));  // GPIO_PIN 4*(7)
    GPIOB->PUPDR &= ~(GPIO_MODE<<(2*pin));        // GPIO_PIN MASK
    GPIOB->PUPDR |= (GPIO_PULLUP<<(2*pin));       // GPIO_PIN PULLDOWN

    // PB8     ------> BOOT0
    pin = 8;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));     // GPIO_PIN MASK
    GPIOB->MODER |= (MODE_INPUT<<(2*pin));     // GPIO_PIN INPUT
    GPIOB->PUPDR &= ~(GPIO_MODE<<(2*pin));     // GPIO_PIN MASK
    GPIOB->PUPDR |= (GPIO_PULLDOWN<<(2*pin));  // GPIO_PIN PULLDOWN
    SYSCFG->EXTICR[pin/4] &= ~(0xf << (4*(pin%4))); 
    SYSCFG->EXTICR[pin/4] |= (1<<(4*(pin%4)));  // PC13 A=0, B=1, C=2
    EXTI->RTSR1 &= ~(EXTI_IMR1_IM8);            // rising edge
    EXTI->FTSR1 |= (EXTI_IMR1_IM8);             // falling edge
    EXTI->IMR1 |= (EXTI_IMR1_IM8);
    NVIC_SetPriority(EXTI9_5_IRQn, 0x03);
    NVIC_EnableIRQ(EXTI9_5_IRQn);

    // PB9     ------> TEST_Out
    pin = 9;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));      // GPIO_PIN MASK
    GPIOB->MODER |= (MODE_OUTPUT<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOB->PUPDR &= ~(GPIO_MODE<<(2*pin));      // GPIO_PIN NOPULLUP
    GPIOB->OTYPER &= ~(OUTPUT_TYPE<<(pin));     // GPIO_PIN MASK
    GPIOB->OTYPER |= (OUTPUT_PP<<(pin));        // GPIO_PIN PUSHPULL
    GPIOB->OSPEEDR &= (3<<(2*pin));             // GPIO_PIN MASK
    GPIOB->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));

    // PB10     ------> USART3_RX
    pin = 10;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));            // GPIO_PIN MASK
    GPIOB->MODER |= (GPIO_MODE_AF_PP<<(2*pin));       // GPIO_PIN INPUT
    GPIOB->AFR[1] &= ~(15<<(4*pin));                  // GPIO_PIN MASK
    GPIOB->AFR[1] |= (GPIO_AF7_USART1<<(4*(pin-8)));  // GPIO_PIN 4*(3)
    GPIOB->PUPDR &= ~(GPIO_MODE<<(2*pin));            // GPIO_PIN MASK
    GPIOB->PUPDR |= (GPIO_PULLUP<<(2*pin));           // GPIO_PIN PULLUP

    // PB11     ------> USART3_TX
    pin = 11;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOB->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOB->AFR[1] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOB->AFR[1] |= (GPIO_AF7_USART3<<(4*pin-8));  // GPIO_PIN 4*(2)
    GPIOB->PUPDR &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN NOPULLUP
    GPIOB->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOB->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOB->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOB->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));  

    // PB12    ------>
    pin = 12;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));    // GPIO_PINMASK
    GPIOB->MODER |= (MODE_OUTPUT<<(2*pin));   // GPIO_PINOUTPUT
    GPIOB->PUPDR &= ~(GPIO_MODE<<(2*pin));    // GPIO_PINNOPULLUP
    GPIOB->OTYPER &= ~(OUTPUT_TYPE<<(pin));   // GPIO_PINMASK
    GPIOB->OTYPER |= (OUTPUT_PP<<(pin));      // GPIO_PINPUSHPULL
    GPIOB->OSPEEDR &= ~(3<<(2*pin));          // GPIO_PINMASK
    GPIOB->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));  

    // PB13    ------> COMP5 / ADC3_IN5
    pin = 13; 
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));    // GPIO_PIN MASK
    GPIOB->MODER |= (MODE_ANALOG<<(2*pin));   // GPIO_PIN OUTPUT
    GPIOB->PUPDR &= ~(GPIO_MODE<<(2*pin));    // GPIO_PIN NOPULLUP
    COMP5->CSR |= COMP_CSR_EN;                // enabble

    // PB14    ------> ADC4_IN4
    pin = 14; 
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));    // GPIO_PIN MASK
    GPIOB->MODER |= (MODE_ANALOG<<(2*pin));   // GPIO_PIN OUTPUT
    GPIOB->PUPDR &= ~(GPIO_MODE<<(2*pin));    // GPIO_PIN NOPULLUP

    // PB15    ------> C_RESET
    pin = 15;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));    // GPIO_PINMASK
    GPIOB->MODER |= (MODE_OUTPUT<<(2*pin));   // GPIO_PINOUTPUT
    GPIOB->PUPDR &= ~(GPIO_MODE<<(2*pin));    // GPIO_PINNOPULLUP
    GPIOB->OTYPER &= ~(OUTPUT_TYPE<<(pin));   // GPIO_PINMASK
    GPIOB->OTYPER |= (OUTPUT_PP<<(pin));      // GPIO_PINPUSHPULL
    GPIOB->OSPEEDR &= ~(3<<(2*pin));          // GPIO_PINMASK
    GPIOB->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));  

  // PC 0x48000800
    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOFEN |
                   RCC_AHB2ENR_GPIOCEN |
                   RCC_AHB2ENR_GPIOBEN |
                   RCC_AHB2ENR_GPIOAEN);
    // PC4     ------> UART1_TX
    pin = 4;
    GPIOC->MODER &= ~(GPIO_MODE<<(2*pin));        // GPIO_PIN MASK
    GPIOC->MODER |= (GPIO_MODE_AF_PP<<(2*pin));   // GPIO_PIN OUTPUT
    GPIOC->AFR[0] &= ~(15<<(4*pin));              // GPIO_PIN MASK
    GPIOC->AFR[0] |= (GPIO_AF7_USART1<<(4*pin));  // GPIO_PIN 4*(4)
    GPIOC->PUPDR &= ~(GPIO_MODE<<(2*pin));        // GPIO_PIN NOPULLUP
    GPIOC->OTYPER &= ~(OUTPUT_TYPE<<(pin));       // GPIO_PIN MASK
    GPIOC->OTYPER |= (OUTPUT_PP<<(pin));          // GPIO_PIN PUSHPULL
    GPIOC->OSPEEDR &= ~(3<<(2*pin));              // GPIO_PIN MASK
    GPIOC->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));  

    // PC6     ------> LED_Pin
    pin = 6;
    GPIOC->MODER &= ~(GPIO_MODE<<(2*pin));     // GPIO_PIN MASK
    GPIOC->MODER |= (MODE_OUTPUT<<(2*pin));    // GPIO_PIN OUTPUT
    GPIOC->PUPDR &= ~(GPIO_MODE<<(2*pin));     // GPIO_PIN NOPULLUP
    GPIOC->OTYPER &= ~(OUTPUT_TYPE<<(pin));    // GPIO_PIN MASK
    GPIOC->OTYPER |= (OUTPUT_PP<<(pin));       // GPIO_PIN PUSHPULL
    GPIOC->OSPEEDR &= ~(3<<(2*pin));           // GPIO_PIN MASK
    GPIOC->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));  

    // PC11    ------> I2C3_SDA

    // PC13    ------> KEY_Pin
    pin = 13;
    GPIOC->MODER &= ~(GPIO_MODE<<(2*pin));    // GPIO_PIN MASK
    GPIOC->MODER |= (MODE_INPUT<<(2*pin));    // GPIO_PIN INPUT
    GPIOC->PUPDR &= ~(GPIO_MODE<<(2*pin));    // GPIO_PIN MASK
    GPIOC->PUPDR |= (GPIO_PULLDOWN<<(2*pin)); // GPIO_PIN PULLDOWN
    SYSCFG->EXTICR[pin/4] |= (2<<(4*(pin%4)));  // PC13 A=0, B=1, C=2
    EXTI->RTSR1 &= ~(EXTI_IMR1_IM13);           // rising edge
    EXTI->FTSR1 |= (EXTI_IMR1_IM13);            // falling edge
    EXTI->IMR1 |= (EXTI_IMR1_IM13);
    NVIC_SetPriority(EXTI15_10_IRQn, 0x03);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOFEN;
    }

uint8_t KEY_Pin_getstate(void)
  {
  return ((GPIOC->IDR & KEY_Pin) == KEY_Pin) ? 1 : 0;
  }

void LED_Pin_toggle(void)
  {
  if((GPIOC->IDR & LED_Pin) == LED_Pin)
    GPIOC->BRR = LED_Pin;
  else
    GPIOC->BSRR = LED_Pin;
  }

void LED_Pin_set(uint8_t set)
  { 
  if (set)
    GPIOC->BSRR = LED_Pin;
  else
    GPIOC->BRR = LED_Pin;
  }

// IWD
    // KR [0x00]
        // KEY[15:0]: Key value (write only, read 0x0000)
            // 0xAAAA Tickle
            // 0x5555 Unlock
    // PR prescaler register [0x04]
        // PR[2:0]: Prescaler divider
            // 000: divider /4
            // 001: divider /8
            // 010: divider /16
            // 011: divider /32
            // 100: divider /64
            // 101: divider /128
            // 110: divider /256
            // 111: divider /256
    // RLR reload register [0x08]
        // RL[11:0]: Watchdog counter reload value
    // SR status register ro [0x0C]
        // WVU: Watchdog counter window value update
        // RVU: Watchdog counter reload value update
        // PVU: Watchdog prescaler value update
    // WINR window register [0x10]
        // WIN[11:0]: Watchdog counter window value
// 0x40003000
void IWD_Init(void)
    {
    IWDG->KR = 0x0000CCCC;
    IWDG->KR = 0x00005555;
    IWDG->PR = 2;
    IWDG->RLR = 512;
    while(IWDG->SR != 00)
        ;
//    IWDG->WINR = 512;
    IWDG->KR = 0x0000AAAA;
    }

void IWD_Tickle(void)
    {
    IWDG->KR = 0x0000AAAA;
    }

// WWDG
    // CR control register [0x00]
        // WDGA: Activation bit
        // T[6:0]: 7-bit counter (MSB to LSB)
    // CFR configuration register [0x04]
        // WDGTB[2:0]: Timer base
            // 000: CK counter clock (PCLK div 4096) div 1
            // 001: CK counter clock (PCLK div 4096) div 2
            // 010: CK counter clock (PCLK div 4096) div 4
            // 011: CK counter clock (PCLK div 4096) div 8
            // 100: CK counter clock (PCLK div 4096) div 16
            // 101: CK counter clock (PCLK div 4096) div 32
            // 110: CK counter clock (PCLK div 4096) div 64
            // 111: CK counter clock (PCLK div 4096) div 128
        // EWI: Early wakeup interrupt
        // W[6:0]: 7-bit window value
    // SR [0x08]
        // EWIF: Early wakeup interrupt flag
// 0x40002C00
void WWDG_Init(void)
    {
    RCC->APB1ENR1 &= ~RCC_APB1ENR1_WWDGEN;
    WWDG->CR = WWDG_CR_WDGA |               // Activate
               (0x7E << WWDG_CR_T_Pos);     // Counter value
    WWDG->CFR |= (7 << WWDG_CFR_WDGTB_Pos) | // div 128
                (0x7F << WWDG_CFR_W_Pos);   //  
    RCC->APB1ENR1 |= RCC_APB1ENR1_WWDGEN;
    }

void WWDG_Tickle(void)
    {
    RCC->APB1ENR1 &= ~RCC_APB1ENR1_WWDGEN;
//    if((WWDG->CR & WWDG_CR_W_Msk) >  (WWDG->CFR & WWDG_CFR_T_Msk))
    WWDG->CR |= (0x7E << WWDG_CR_T_Pos);    // Counter value
//    WWDG->CR |= WWDG_CR_WDGA;               // enable
    RCC->APB1ENR1 |= RCC_APB1ENR1_WWDGEN;
    }
    
void HAL_MspInit(void)
  {
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWREx_DisableUCPDDeadBattery();
  }

// RND 0x50060800
void RND_Init(void)
    {
    RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;    // enable random clock
    RNG->CR|=RNG_CR_RNGEN;                // enable random
    }

// RCC
    // CR Clock control register [0x00] 0x03030500
        // PLLRDY: Main PLL clock ready flag
        // PLLON: Main PLL enable = 1
        // CSSON: Clock security system enable
        // HSEBYP: HSE crystal oscillator bypass
        // HSERDY: HSE clock ready flag
        // HSEON: HSE clock enable = 1
        // HSIRDY: HSI16 clock ready flag
        // HSIKERON: HSI16 always enable for peripheral kernels
        // HSION: HSI16 clock enable = 1
    // ICSCR Internal clock sources calibration register [0x04] 0x409F0000
        // HSITRIM[6:0]: HSI16 clock trimming = 0x40
        // HSICAL[7:0]: HSI16 clock calibration = 0x9F
    // CFGR Clock configuration register [0x08] ox0000000F
        // MCOPRE[2:0]: Microcontroller clock output prescaler
        // MCOSEL[3:0]: Microcontroller clock output
        // PPRE2[2:0]: APB2 prescaler
        // PPRE1[2:0]:APB1 prescaler
        // HPRE[3:0]: AHB prescaler
        // SWS[1:0]: System clock switch status
        // SW[1:0]: System clock switch = 0x11
    // PLLCFGR PLL configuration register [0x0C] 0x11005513
        // PLLPDIV[4:0]: Main PLLP division factor = 2
        // PLLR[1:0]: Main PLL division factor for PLL “R” clock
        // PLLREN: PLL “R” clock output enable = 1
        // PLLQ[1:0]: Main PLL division factor for PLL “Q” clock
        // PLLQEN: Main PLL “Q” clock output enable
        // PLLP: Main PLL division factor for PLL “P” clock
        // PLLPEN: Main PLL PLL “P” clock output enable
        // PLLN[6:0]: Main PLL multiplication factor for VCO =0x55
        // PLLM[3:0]: Division factor for the main PLL input clock =0x1
        // PLLSRC[1:0]: Main PLL entry clock source = 0x3
    // CIER Clock interrupt enable register [0x18] 0x00000000
        // HSI48RDYIE: HSI48 ready interrupt enable
        // LSECSSIE: LSE clock security system interrupt enable
        // PLLRDYIE: PLL ready interrupt enable
        // HSERDYIE: HSE ready interrupt enable
        // HSIRDYIE: HSI16 ready interrupt enable
        // LSERDYIE: LSE ready interrupt enable
        // LSIRDYIE: LSI ready interrupt enable
    // CIFR Clock interrupt flag register [0x1C] 0x00000000
        // HSI48RDYF: HSI48 ready interrupt flag
        // LSECSSF: LSE Clock security system interrupt flag
        // CSSF: Clock security system interrupt flag
        // PLLRDYF: PLL ready interrupt flag
        // HSERDYF: HSE ready interrupt flag
        // HSIRDYF: HSI16 ready interrupt flag
        // LSERDYF: LSE ready interrupt flag
        // LSIRDYF: LSI ready interrupt flag
    // CICR Clock interrupt clear register [0x20]  0x00000000
        // HSI48RDYC: HSI48 oscillator ready interrupt clear
        // LSECSSC: LSE Clock security system interrupt clear
        // CSSC: Clock security system interrupt clear
        // PLLRDYC: PLL ready interrupt clear
        // HSERDYC: HSE ready interrupt clear
        // HSIRDYC: HSI16 ready interrupt clear
        // LSERDYC: LSE ready interrupt clear
        // LSIRDYC: LSI ready interrupt clear
// RCC 0x40021000
// PWR 0x40007000
void SystemClock_Config(void)
  {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 |  RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
    Error_Handler();
    }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
    Error_Handler();
    }
  }

