# LPUART1
## Interupt driven

### ADDRESS
| Port | Address |
| --- | ----------- |
| LPUART1 | 0x40008000 |


## Clock enables
```
  RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
  RCC->CCIPR |= RCC_CCIPR_LPUART1SEL_0;
```

## PA2     ------> LPUART1_TX
```
  pin = 2;
  GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN_2 MASK
  GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN_2 OUTPUT
  GPIOA->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN_2 MASK
  GPIOA->AFR[0] |= (GPIO_AF12_LPUART1<<(4*pin));  // GPIO_PIN_2 4*(2)
  GPIOA->PUPDR &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN_2 NOPULLUP
  GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN_2 MASK
  GPIOA->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN_2 PUSHPULL
  GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN_2 MASK
  GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));  
```
## PA3     ------> LPUART1_RX
```
  pin = 3;
  GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN_2 MASK
  GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN_3 INPUT
  GPIOA->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN_3 MASK
  GPIOA->AFR[0] |= (GPIO_AF12_LPUART1<<(4*pin));  // GPIO_PIN_3 4*(3)
  GPIOA->PUPDR &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN_3 MASK
  GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));         // GPIO_PIN_3 PULLDOWN
```
## Init
```
  LPUART1->CR1 = USART_CR1_RE;        // enable receive
  LPUART1->CR1 |=  USART_CR1_TE;       // enable  transmit
  LPUART1->CR1 |= USART_CR1_TXEIE_TXFNFIE;    // enable transmit IRQ
  LPUART1->CR1 |= USART_CR1_RXNEIE_RXFNEIE;   // enable receive IRQ
  LPUART1->CR1 |= USART_CR1_FIFOEN;
  LPUART1->CR3 |= USART_CR3_EIE;      // FE, NE and ORE enable
  LPUART1->PRESC = 9;                 // prescale = 64;
  LPUART1->BRR = uartdiv;
  LPUART1->CR1 |= USART_CR1_UE;       // enable;
  NVIC_EnableIRQ(LPUART1_IRQn);       // Enable NVIC Interrupt
```

## Starting output
```
void MX_LPUART1_Tx(char *lpuart1_txData, uint32_t lpuart1_txCNT)
  {
  extern char * lpuart1_txPtr;
  lpuart1_txPtr = lpuart1_txData;
  while(((LPUART1->ISR & USART_ISR_TXE) == USART_ISR_TXE) && (lpuart1_txCNT > 0))
    {
    LPUART1->TDR = *lpuart1_txPtr++;
    lpuart1_txCNT--;
    }
  if(lpuart1_txCNT > 0)
    LPUART1->CR1 |= USART_CR1_TXEIE_TXFNFIE;
  }
```

## Interupt
```
void LPUART1_IRQHandler(void)
  {
  extern uint32_t lpuart1_txCNT, lpuart1_rxPtr;
  extern char *lpuart1_txPtr, lpuart1_rxData[32];
  extern uint32_t menu_cntr_1, menu_cntr_2;

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
```
