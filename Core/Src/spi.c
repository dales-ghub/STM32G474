#include "spi.h"

// SPI1 0x40013000
void SPI1a_Init(void)
  {
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;   // enable SPI1 clock
  SPI1->CR1 = (SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0); // fPCLK/256
  SPI1->CR1 |= SPI_CR1_MSTR;            // Master configuration (13C)
  SPI1->CR1 |= SPI_CR1_SSI;             // Master configuration
  SPI1->CR2 = SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;  // 8-bit
  SPI1->CR2 |= SPI_CR2_SSOE;    // SS output enable
  SPI1->CR2 |= SPI_CR2_FRXTH;   // FIFO reception threshold (170C)
  SPI1->CR2 |= SPI_CR2_NSSP;    // NSS pulse generated
  NVIC_EnableIRQ(SPI1_IRQn);
  }

char * SPI1_ptrIn;
char * SPI1_ptrOut;
uint32_t SPI1_bytes;
uint16_t temp;
void SPI1a_Start(char * buff, uint32_t len)
  {
  SPI1->CR1 &= ~SPI_CR1_SPE;     // SPI disable
  SPI1_ptrIn = buff;
  SPI1_ptrOut = buff;
  SPI1_bytes = len;
  while(SPI1->SR & SPI_SR_RXNE)
    temp = SPI1->DR;
  while((SPI1->SR & SPI_SR_TXE) && (SPI1_bytes > 0))
    {
    temp = *SPI1_ptrOut++;
    SPI1_bytes--;
    temp |= (*SPI1_ptrOut++)<<8;
    if(SPI1_bytes > 0)
      SPI1_bytes--;
    SPI1->DR = temp;
    }
  SPI1->CR2 |= SPI_CR2_TXEIE;   // Tx buffer empty interrupt enable
  SPI1->CR2 |= SPI_CR2_RXNEIE;  // RX buffer not empty interrupt enable
  SPI1->CR1 |= SPI_CR1_SPE;     // SPI enable
  }

// SPI1 0x40013000
void SPI1d_Init(void)
  {
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;   // enable SPI1 clock
  SPI1->CR1 = (SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0); // fPCLK/256
  SPI1->CR1 |= SPI_CR1_MSTR;             // Master configuration (13C)
  SPI1->CR2 = SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;  // 8-bit
  SPI1->CR2 |= SPI_CR2_SSOE;  // SS output enable
  SPI1->CR2 |= SPI_CR2_NSSP;  // NSS pulse generated
  SPI1->CR2 |= SPI_CR2_TXDMAEN; // 
  SPI1->CR2 |= SPI_CR2_RXDMAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_DMAMUX1EN | RCC_AHB1ENR_DMA2EN;
  }

// DMA2_Channel1 40020400
// DMA2_Channel2 40020414
// DMAMUX1_Channel8 40020820
// DMAMUX1_Channel9 40020824
// DMAMUX channels 8 to 15 are connected to DMA2 channels 1 to 8
void SPI1d_Start(char * wrBuff, char * rdBuff, uint32_t len)
  {
  DMA2_Channel1->CCR = 0;   // clear write DMA
  DMA2_Channel2->CCR = 0;   // clear read DMA
  DMAMUX1_Channel8->CCR = 0x0;
  DMAMUX1_Channel9->CCR = 0x0;
  DMA2_Channel1->CNDTR = 0;
  DMA2_Channel2->CNDTR = 0;
  DMA2_Channel1->CCR |= DMA_CCR_TCIE;
  DMA2_Channel2->CCR |= DMA_CCR_TCIE;
  DMA2->IFCR = (DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TCIF1 | DMA_ISR_GIF1);
  DMA2->IFCR = (DMA_ISR_TCIF2 | DMA_ISR_HTIF2 | DMA_ISR_TCIF2 | DMA_ISR_GIF2);
  SPI1->CR1 |= SPI_CR1_SPE;     // SPI enable

  // DMAMUX 
    // SYNC_ID Synchronization identification = 
    // NBREQ Number of DMA requests = 
    // SPOL Synchronization polarity = 
    // SE Synchronization enable = Synchronization disabled
    // EGE Event generation enable = generation disabled
    // SOIE Synchronization overrun = Interrupt disabled
    // DMAREQ_ID Request identification = LPUART1_TX 35
  DMAMUX1_Channel8->CCR |=  (DMA_REQUEST_SPI1_TX << DMAMUX_CxCR_DMAREQ_ID_Pos);
  DMAMUX1_Channel9->CCR |=  (DMA_REQUEST_SPI1_RX << DMAMUX_CxCR_DMAREQ_ID_Pos);
  DMAMUX1_Channel8->CCR |= DMAMUX_CxCR_SPOL_1;
  DMAMUX1_Channel9->CCR |= DMAMUX_CxCR_SPOL_1;
  // DMA
    // CMAR peripheral address
    // CPAR peripheral address
    // CNDTR byte count
  DMA2_Channel1->CMAR  = ( uint32_t )wrBuff;
  DMA2_Channel2->CMAR  = ( uint32_t )rdBuff;
  DMA2_Channel1->CPAR  = ( uint32_t )&( SPI1->DR );
  DMA2_Channel2->CPAR  = ( uint32_t )&( SPI1->DR );
  len /= 2;
  DMA2_Channel1->CNDTR = len--;
  DMA2_Channel2->CNDTR = len--;
  // DMA_CCR
    // memory-to-memory mode = off
    // PL priority = medium
    // MSIZE memory size = 8
    // PSIZE peripheral size = 16
    // MINC memory increment mode = enabled
    // PINC peripheral increment mode = disabled
    // CIRC circular mode = 0ff
    // DIR data transfer direction = read from memory
    // TEIE transfer error interrupt enable = disabled
    // HTIE half transfer interrupt enable = disabled
    // TCIE transfer complete interrupt enable = enabled
    // EN channel enable = disabled
  DMA2_Channel1->CCR |= (( 0x1 << DMA_CCR_PL_Pos ) |
                          DMA_CCR_MSIZE_0 |
                          DMA_CCR_PSIZE_0 |
                          DMA_CCR_MINC |
                          DMA_CCR_DIR |
                          DMA_CCR_TCIE); 
  DMA2_Channel2->CCR |= (( 0x1 << DMA_CCR_PL_Pos ) |
                          DMA_CCR_MSIZE_0 |
                          DMA_CCR_PSIZE_0 |
//                          DMA_CCR_MINC |
                          DMA_CCR_TCIE); 
  DMA2_Channel1->CCR |= DMA_CCR_EN;
  DMA2_Channel2->CCR |= DMA_CCR_EN;
  }

// SPI2 0x40003800
void SPI2_Init(void)
  {
  SPI2->CR1 = 0x0;
  RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;    // enable SPI2 clock
  }
  
// SPI3 0x40003C00
void SPI3_Init(void)
  {
  SPI3->CR1 = 0x0;
  RCC->APB1ENR1 |= RCC_APB1ENR1_SPI3EN;    // enable SPI1 clock
  }
  
// SPI4 0x40013C00
void SPI4_Init(void)
  {
  SPI4->CR1 = 0x0;
  RCC->APB2ENR |= RCC_APB2ENR_SPI4EN;    // enable SPI1 clock
  }


