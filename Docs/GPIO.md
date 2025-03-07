# GPIO
PC13 simple input pin example with interupt. PC6 output pin.
## STM32G474
### ADDRESS
| Port | Address |
| --- | ----------- |
| PORTA | 0x48000000 |
| PORTB | 0x48000400 |
| PORTC | 0x48000800 |
| PORTF | 0x48001400 |
| PORTG | 0x48001800 |

## Clock enables
```
    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOFEN | RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOAEN);
```
## PC13    ------> KEY_Pin
```
  pin = 13;
  GPIOC->MODER &= ~(GPIO_MODE<<(2*pin));    // GPIO_PIN_8 MASK
  GPIOC->MODER |= (MODE_INPUT<<(2*pin));    // GPIO_PIN_8 INPUT
  GPIOC->PUPDR &= ~(GPIO_MODE<<(2*pin));    // GPIO_PIN_8 MASK
  GPIOC->PUPDR |= (GPIO_PULLDOWN<<(2*pin)); // GPIO_PIN_8 PULLDOWN
```
### IRQ enable
```
  SYSCFG->EXTICR[pin/4] |= (2<<(4*(pin%4)));  // PC13 A=0, B=1, C=2
  EXTI->RTSR1 &= ~(EXTI_IMR1_IM13);           // rising edge
  EXTI->FTSR1 |= (EXTI_IMR1_IM13);            // falling edge
  EXTI->IMR1 |= (EXTI_IMR1_IM13);
  NVIC_SetPriority(EXTI15_10_IRQn, 0x03);
  NVIC_EnableIRQ(EXTI15_10_IRQn);
```
### IRQ
```
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
```
### Get state
```
uint8_t KEY_Pin_getstate(void)
  {
  return ((GPIOC->IDR & KEY_Pin) == KEY_Pin) ? 1 : 0;
  }
```
## PC6     ------> LED_Pin
```
  pin = 6;
  GPIOC->MODER &= ~(GPIO_MODE<<(2*pin));     // GPIO_PIN_6 MASK
  GPIOC->MODER |= (MODE_OUTPUT<<(2*pin));    // GPIO_PIN_6 OUTPUT
  GPIOC->PUPDR &= ~(GPIO_MODE<<(2*pin));     // GPIO_PIN_6 NOPULLUP
  GPIOC->OTYPER &= ~(OUTPUT_TYPE<<(pin));    // GPIO_PIN_6 MASK
  GPIOC->OTYPER |= (OUTPUT_PP<<(pin));       // GPIO_PIN_6 PUSHPULL
  GPIOC->OSPEEDR &= ~(3<<(2*pin));           // GPIO_PIN_6 MASK
  GPIOC->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));  
```
### Set pin
```
void LED_Pin_set(uint8_t set)
  { 
  if (set)
    GPIOC->BSRR = LED_Pin;
  else
    GPIOC->BRR = LED_Pin;
  }
```
### Toggle pin
```void LED_Pin_toggle(void)
  {
  if((GPIOC->IDR & LED_Pin) == LED_Pin)
    GPIOC->BRR = LED_Pin;
  else
    GPIOC->BSRR = LED_Pin;
  }

```