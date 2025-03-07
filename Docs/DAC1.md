# DAC1
DAC1 simple setup.
### ADDRESS
| Port | Address | Pin |
| --- | ----------- | --- |
| DAC1 | 0x50000800 | PA4, PA5 |
| DAC2 | 0x50000C00 | PA6 |
| DAC3 | 0x50001000 | N/A |
| DAC4 | 0x50001400 | N/A |

## Clock enables
```
  RCC->AHB2ENR |= RCC_AHB2ENR_DAC1EN;
  RCC->AHB2ENR |= RCC_AHB2ENR_DAC2EN;
  RCC->AHB2ENR |= RCC_AHB2ENR_DAC3EN;
  RCC->AHB2ENR |= RCC_AHB2ENR_DAC4EN;
```
## Enable
```
  DAC1->CR = 0x0;
  DAC1->SWTRIGR = 0x0;
  DAC1->DHR12R1 = 0x01000100;
  DAC1->CCR = (0xC<<16 | 0x14);
  DAC1->MCR = DAC_MCR_HFSEL_1;
  DAC1->CR = DAC_CR_EN1;
```
## PA4     ------> DAC1_OUT1
```
  pin = 5;
  GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));    // GPIO_PIN_5 MASK
  GPIOA->MODER |= (MODE_ANALOG<<(2*pin));   // GPIO_PIN_5 OUTPUT
  GPIOA->PUPDR &= ~(GPIO_MODE<<(2*pin));    // GPIO_PIN_5 NOPULLU
```
## Set Value
```
  DAC1->DHR12R1 = 2;
```