# TIM1 PWMs
Timer 1 with 3 pwms. Default set to 1/2, 3/8 and 1/4 duty cycle.
## STM32G474
### TIM1 0x40012C00
## Clock enables
```
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
```
## Enable
```
  TIM1->CR1 = 0x0;
  TIM1->CR2 = 0x0;
  TIM1->SMCR = 0x0;
  TIM1->DIER |= TIM_DIER_UIE;    // Enable the Interrupt
  TIM1->SR &= ~TIM_SR_UIF;       // Clear the Interrupt Status
  TIM1->EGR = 0x0;
  TIM1->CCMR1 =  0x6868;
  TIM1->CCMR2 = 0x68;
  TIM1->CCER = 0x111;
  TIM1->PSC = 3;
  TIM1->ARR = 999;
  TIM1->RCR = 0x0;
  TIM1->CCR1 = 500;
  TIM1->CCR2 = 375;
  TIM1->CCR3 = 250;
  TIM1->CCR4 = 0x0;
  TIM1->BDTR = 0x200A000; // TIM_BDTR_BK2P | TIM_BDTR_MOE | TIM_BDTR_BKP
  TIM1->CCR5 = 0x0;
  TIM1->CCR6 = 0x0; 
  TIM1->CCMR3 = 0x0;
  TIM1->DTR2 = 0x0;
  TIM1->ECR = 0x0;
  TIM1->TISEL = 0x0;
  TIM1->AF1 = TIM_BDTR_BK2P; // 0x1
  TIM1->AF2 = TIM_BDTR_BK2P; // 0x1
  TIM1->DCR = 0x0;
  TIM1->DMAR = 0x1;
  TIM1->CR1 |= TIM_CR1_CEN;       // enable TIM1
```
## PA8     ------> TIM1_CH1
```
  pin = 8;
  GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN_8 MASK
  GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN_8 OUTPUT
  GPIOA->AFR[1] &= ~(15<<(4*(pin-8)));            // GPIO_PIN_8 MASK
  GPIOA->AFR[1] |= (GPIO_AF6_TIM1<<(4*(pin-8)));  // GPIO_PIN_8 4*(1)
  GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN_8 MASK
  GPIOA->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN_8 PUSHPULL
  GPIOA->OSPEEDR &= (3<<(2*pin));                 // GPIO_PIN_8 MASK
  GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));
```
## PA9     ------> TIM1_CH2
```
  pin = 9;
  GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN_9 MASK
  GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN_9 OUTPUT
  GPIOA->AFR[1] &= ~(15<<(4*(pin-8)));            // GPIO_PIN_9 MASK
  GPIOA->AFR[1] |= (GPIO_AF6_TIM1<<(4*(pin-8)));  // GPIO_PIN_9 4*(1)
  GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN_9 MASK
  GPIOA->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN_9 PUSHPULL
  GPIOA->PUPDR &= ~(3<<(2*pin));                  // GPIO_PIN_9 MASK
  GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));
  GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN_9 MASK
  GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));
```

## PA10    ------> TIM1_CH3
```
  pin = 10;
  GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN_10 MASK
  GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN_10 OUTPUT
  GPIOA->AFR[1] &= ~(15<<(4*(pin-8)));            // GPIO_PIN_10 MASK
  GPIOA->AFR[1] |= (GPIO_AF6_TIM1<<(4*(pin-8)));  // GPIO_PIN_10 4*(2)
  GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN_10 MASK
  GPIOA->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN_10 PUSHPULL
  GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN_10 MASK
  GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));
```
## Update width
```
  TIM1->CCR1 = 100; // 10%
  TIM1->CCR2 = 50;``// 5%
  TIM1->CCR3 = 25;``// 2.5%
```