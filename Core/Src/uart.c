#include "uart.h"

uint32_t lpuart1_rxPtr = 0;
uint32_t lpuart1_txCNT = 0;
uint32_t usart1_rxPtr = 0;

char lpuart1_rxData[LPUART1_RX_SIZE];
char lpuart1_txData[LPUART1_TX_SIZE];
char *lpuart1_txPtr;
char usart1_rxData[USART1_RX_SIZE];
char usart1_txData[USRART1_TX_SIZE];
uint32_t usart1_txCNT = 0;
char *usart1_txPtr;

// LPUART1_TX
// LPUART1 40008000
void LPUART1_Init(uint32_t baud)
  {
  uint32_t uartdiv = 4 * SystemCoreClock / baud;
  
  RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
  RCC->CCIPR |= RCC_CCIPR_LPUART1SEL_0;
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
  }
  
void LPUART1_Tx(char *lpuart1_txData, uint32_t lpuart1_txCNT)
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

// LPUART1 40008000
void LPUART1d_Init(uint32_t baud)
  {
  uint32_t uartdiv = 4 * SystemCoreClock / baud;
  
  RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
  RCC->CCIPR |= RCC_CCIPR_LPUART1SEL_0;
  LPUART1->CR1 = ( USART_CR1_RE | USART_CR1_TE );   // enable receive and transmit
//  LPUART1->CR1 |= USART_CR1_CMIE;         // enable charater match
  LPUART1->CR1 |= USART_CR1_RXNEIE_RXFNEIE;         // enable receive IRQ
  LPUART1->CR2 =  (10 << USART_CR2_ADD_Pos);
  LPUART1->PRESC = 9;             // prescale = 64;
  LPUART1->BRR = uartdiv;
  LPUART1->CR1 |= USART_CR1_UE;   // enable;
  NVIC_EnableIRQ(LPUART1_IRQn);   // Enable NVIC Interrupt
  RCC->AHB1ENR |= RCC_AHB1ENR_DMAMUX1EN | RCC_AHB1ENR_DMA1EN;
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);   // Enable NVIC Interrupt
  }

// DMA1_Channel1 40020000
// DMAMUX1_Channel0 40020800
// DMAMUX channels 0 to 7 are connected to DMA1 channels 1 to 8
void LPUART1d_Tx(char *lpuart1_txData, uint32_t lpuart1_txCNT)
  {
  DMA1_Channel1->CCR = 0;
  DMAMUX1_Channel0->CCR = 0x0;
  DMA1_Channel1->CNDTR = 0;
  DMA1->IFCR = (DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TCIF1 | DMA_ISR_GIF1);
  LPUART1->CR3 |= USART_CR3_DMAT;                   // enable transmit DMA

  // DMAMUX 
    // SYNC_ID Synchronization identification = 
    // NBREQ Number of DMA requests = 
    // SPOL Synchronization polarity = 
    // SE Synchronization enable = Synchronization disabled
    // EGE Event generation enable = generation disabled
    // SOIE Synchronization overrun = Interrupt disabled
    // DMAREQ_ID Request identification = LPUART1_TX 35
  DMAMUX1_Channel0->CCR |=  (DMA_REQUEST_LPUART1_TX << DMAMUX_CxCR_DMAREQ_ID_Pos);
  DMAMUX1_Channel0->CCR |= DMAMUX_CxCR_SPOL_1;
  // DMA
    // CMAR peripheral address
    // CPAR peripheral address
    // CNDTR byte count
  DMA1_Channel1->CMAR  = ( uint32_t )lpuart1_txData;
  DMA1_Channel1->CPAR  = ( uint32_t )&( LPUART1->TDR );
  DMA1_Channel1->CNDTR = lpuart1_txCNT--;
  // DMA_CCR
    // memory-to-memory mode = off
    // PL priority = medium
    // MSIZE memory size = 8
    // PSIZE peripheral size = 8
    // MINC memory increment mode = enabled
    // PINC peripheral increment mode = disabled
    // CIRC circular mode = 0ff
    // DIR data transfer direction = read from memory
    // TEIE transfer error interrupt enable = disabled
    // HTIE half transfer interrupt enable = disabled
    // TCIE transfer complete interrupt enable = enabled
    // EN channel enable = disabled
  DMA1_Channel1->CCR |= (( 0x1 << DMA_CCR_PL_Pos ) |
                          DMA_CCR_MINC |
                          DMA_CCR_DIR |
                          DMA_CCR_TCIE); 
  DMA1_Channel1->CCR |= DMA_CCR_EN;
  }
 
// USART1 0x40013800
void USART1_Init(uint32_t baud)
  {
  uint16_t uartdiv = SystemCoreClock / baud;
  
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  USART1->CR1 = USART_CR1_RE;     // enable receive
  USART1->CR1 |= USART_CR1_TE;    // enable transmit
  USART1->CR1 |= USART_CR1_TXEIE_TXFNFIE;  // enable transmit IRQ
  USART1->CR1 |= USART_CR1_RXNEIE_RXFNEIE; // enable receive IRQ
  USART1->CR1 |= USART_CR1_FIFOEN;
  USART1->CR3 |= USART_CR3_EIE;     // FE, NE and ORE enable
  USART1->PRESC = 0;                // prescale = 1;
  USART1->BRR = uartdiv;
  USART1->CR1 |= USART_CR1_UE;      // enable;
  NVIC_EnableIRQ(USART1_IRQn);      // Enable NVIC Interrupt
  }
  
void USART1_Tx(char *s, uint32_t CNT)
  {
  extern char * usart1_txPtr;
  extern uint32_t usart1_txCNT;
  usart1_txCNT = CNT;
  usart1_txPtr = s;
  while(((USART1->ISR & USART_ISR_TXE) == USART_ISR_TXE) && (usart1_txCNT > 0))
    {
    USART1->TDR = *usart1_txPtr++;
    usart1_txCNT--;
    }
  if(usart1_txCNT > 0)
    {
    USART1->CR1 |= USART_CR1_TXEIE_TXFNFIE;
    }
  }
  
void USART1d_Init(uint32_t baud)
  {
  uint16_t uartdiv = SystemCoreClock / baud;
  
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  USART1->CR1 = USART_CR1_RE;     // enable receive
  USART1->CR1 |= USART_CR1_TE;    // enable transmit
//  USART1->CR1 |= USART_CR1_CMIE;                  // enable charater match
  USART1->CR1 |= USART_CR1_RXNEIE_RXFNEIE; // enable receive IRQ
//  USART1->CR2 =  (10 << USART_CR2_ADD_Pos);
  USART1->PRESC = 0;                    // prescale = 1;
  USART1->BRR = uartdiv;                // Baud rate
  USART1->CR1 |= USART_CR1_UE;          // enable;
  NVIC_EnableIRQ(USART1_IRQn);          // Enable NVIC Interrupt
  RCC->AHB1ENR |= RCC_AHB1ENR_DMAMUX1EN | RCC_AHB1ENR_DMA1EN;
  NVIC_EnableIRQ(DMA1_Channel2_IRQn);   // Enable NVIC Interrupt
  }

// DMA1_Channel2 40020014
// DMAMUX1_Channel1 40020800
// DMAMUX channels 0 to 7 are connected to DMA1 channels 1 to 8
void USART1d_Tx(char *usart1_txData, uint32_t usart1_txCNT)
  {
  DMA1_Channel2->CCR = 0;
  DMAMUX1_Channel1->CCR = 0x0;
  DMA1_Channel2->CNDTR = 0;
  DMA1->IFCR = (DMA_ISR_TCIF2 | DMA_ISR_HTIF2 | DMA_ISR_TCIF2 | DMA_ISR_GIF2);
  USART1->CR3 |= USART_CR3_DMAT;                   // enable transmit DMA

  // DMAMUX 
    // SYNC_ID Synchronization identification = 
    // NBREQ Number of DMA requests = 
    // SPOL Synchronization polarity = 
    // SE Synchronization enable = Synchronization disabled
    // EGE Event generation enable = generation disabled
    // SOIE Synchronization overrun = Interrupt disabled
    // DMAREQ_ID Request identification = LPUART1_TX 35
  DMAMUX1_Channel1->CCR |=  (DMA_REQUEST_USART1_TX << DMAMUX_CxCR_DMAREQ_ID_Pos);
  DMAMUX1_Channel1->CCR |= DMAMUX_CxCR_SPOL_1;
  // DMA
    // CMAR peripheral address
    // CPAR peripheral address
    // CNDTR byte count
  DMA1_Channel2->CMAR  = ( uint32_t )usart1_txData;
  DMA1_Channel2->CPAR  = ( uint32_t )&( USART1->TDR );
  DMA1_Channel2->CNDTR = usart1_txCNT--;
  // DMA_CCR
    // memory-to-memory mode = off
    // PL priority = medium
    // MSIZE memory size = 8
    // PSIZE peripheral size = 8
    // MINC memory increment mode = enabled
    // PINC peripheral increment mode = disabled
    // CIRC circular mode = 0ff
    // DIR data transfer direction = read from memory
    // TEIE transfer error interrupt enable = disabled
    // HTIE half transfer interrupt enable = disabled
    // TCIE transfer complete interrupt enable = enabled
    // EN channel enable = disabled
  DMA1_Channel2->CCR |= (( 0x1 << DMA_CCR_PL_Pos ) |
                          DMA_CCR_MINC |
                          DMA_CCR_DIR |
                          DMA_CCR_TCIE); 
  DMA1_Channel2->CCR |= DMA_CCR_EN;
  }
  
// USART3 40004800
void USART3d_Init(uint32_t baud)
  {
  uint16_t uartdiv = SystemCoreClock / baud;
  
  RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN;
  USART3->CR1 = USART_CR1_RE;     // enable receive
  USART3->CR1 |= USART_CR1_TE;    // enable transmit
//  USART3->CR1 |= USART_CR1_CMIE;                  // enable charater match
//  USART3->CR1 |= USART_CR1_RXNEIE_RXFNEIE; // enable receive IRQ
  USART3->CR2 =  (10 << USART_CR2_ADD_Pos);
  USART3->PRESC = 0;                    // prescale = 1;
  USART3->BRR = uartdiv;                // Baud rate
  USART3->CR1 |= USART_CR1_UE;          // enable;
  NVIC_EnableIRQ(USART3_IRQn);          // Enable NVIC Interrupt
  RCC->AHB1ENR |= RCC_AHB1ENR_DMAMUX1EN | RCC_AHB1ENR_DMA1EN;
  NVIC_EnableIRQ(DMA1_Channel3_IRQn);   // Enable NVIC Interrupt
  }

// DMA1_Channel3 40020028
// DMAMUX1_Channel2 40020800
// DMAMUX channels 0 to 7 are connected to DMA1 channels 1 to 8
void USART3d_Tx(char *usart3_txData, uint32_t txCNT)
  {
  DMA1_Channel3->CCR = 0;
  DMAMUX1_Channel2->CCR = 0x0;
  DMA1_Channel3->CNDTR = 0;
  DMA1->IFCR = (DMA_ISR_TCIF3 | DMA_ISR_HTIF3 | DMA_ISR_TCIF3 | DMA_ISR_GIF3);
  USART3->CR3 |= USART_CR3_DMAT;                   // enable transmit DMA

  // DMAMUX 
    // SYNC_ID Synchronization identification = 
    // NBREQ Number of DMA requests = 
    // SPOL Synchronization polarity = 
    // SE Synchronization enable = Synchronization disabled
    // EGE Event generation enable = generation disabled
    // SOIE Synchronization overrun = Interrupt disabled
    // DMAREQ_ID Request identification = LPUART1_TX 35
  DMAMUX1_Channel2->CCR |= (DMA_REQUEST_USART3_TX << DMAMUX_CxCR_DMAREQ_ID_Pos);
  DMAMUX1_Channel2->CCR |= DMAMUX_CxCR_SPOL_1;
  // DMA
    // CMAR peripheral address
    // CPAR peripheral address
    // CNDTR byte count
  DMA1_Channel3->CMAR  = ( uint32_t )usart3_txData;
  DMA1_Channel3->CPAR  = ( uint32_t )&( USART3->TDR );
  DMA1_Channel3->CNDTR = txCNT--;
  // DMA_CCR
    // memory-to-memory mode = off
    // PL priority = medium
    // MSIZE memory size = 8
    // PSIZE peripheral size = 8
    // MINC memory increment mode = enabled
    // PINC peripheral increment mode = disabled
    // CIRC circular mode = 0ff
    // DIR data transfer direction = read from memory
    // TEIE transfer error interrupt enable = disabled
    // HTIE half transfer interrupt enable = disabled
    // TCIE transfer complete interrupt enable = enabled
    // EN channel enable = disabled
  DMA1_Channel3->CCR |= (( 0x1 << DMA_CCR_PL_Pos ) |
                          DMA_CCR_MINC |
                          DMA_CCR_DIR |
                          DMA_CCR_TCIE); 
  DMA1_Channel3->CCR |= DMA_CCR_EN;
  }
  

