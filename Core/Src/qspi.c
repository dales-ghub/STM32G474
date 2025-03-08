#include "qspi.h"

// W25Q128 16 Mbyte
// DATA 0x90000000-0x9FFFFFFF
void QSPI_Init(void)
    {
    RCC->AHB3ENR |= RCC_AHB3ENR_QSPIEN;

    // PA6     ------> QSPI_IO3
    int pin = 6;
#if(0)
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOA->AFR[0] |= (GPIO_AF10_QUADSPI<<(4*pin));  // GPIO_PIN 4*(3)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOA->OSPEEDR &= (3<<(2*pin));                 // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_HIGH<<(2*pin));
#else
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));      // GPIO_PIN MASK
    GPIOA->MODER |= (MODE_OUTPUT<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->PUPDR &= ~(3<<(2*pin));              // GPIO_PIN NOPULLUP
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));     // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_PP<<(pin));        // GPIO_PIN PUSHPULL
    GPIOA->OSPEEDR &= (3<<(2*pin));             // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));
    GPIOA->BSRR = GPIO_PIN_6;
#endif 
    // PA7     ------> QSPI_IO2
    pin = 7;
#if(0)
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOA->AFR[0] |= (GPIO_AF10_QUADSPI<<(4*pin));  // GPIO_PIN 4*(3)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOA->OSPEEDR &= (3<<(2*pin));                 // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_HIGH<<(2*pin));
#else
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));      // GPIO_PIN MASK
    GPIOA->MODER |= (MODE_OUTPUT<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->PUPDR &= ~(3<<(2*pin));              // GPIO_PIN NOPULLUP
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));     // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_PP<<(pin));        // GPIO_PIN PUSHPULL
    GPIOA->OSPEEDR &= (3<<(2*pin));             // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_LOW<<(2*pin));
    GPIOA->BSRR = GPIO_PIN_7;
#endif 

    // PB 0x48000400
    // PB0     ------> QSPI_IO0
    pin = 0;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOB->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOB->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOB->AFR[0] |= (GPIO_AF10_QUADSPI<<(4*pin));  // GPIO_PIN 4*(3)
    GPIOB->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOB->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOB->OSPEEDR &= (3<<(2*pin));                 // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_HIGH<<(2*pin));

    // PB1     ------> QSPI_IO1
    pin = 1;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOB->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOB->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOB->AFR[0] |= (GPIO_AF10_QUADSPI<<(4*pin));  // GPIO_PIN 4*(3)
    GPIOB->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOB->OTYPER |= (OUTPUT_PP<<(pin));            // GPIO_PIN PUSHPULL
    GPIOB->OSPEEDR &= (3<<(2*pin));                 // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_HIGH<<(2*pin));
  
    // PB10     ------> QSPI_CLK
    pin = 10;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));              // GPIO_PIN MASK
    GPIOB->MODER |= (GPIO_MODE_AF_PP<<(2*pin));         // GPIO_PIN OUTPUT
    GPIOB->AFR[1] &= ~(15<<(4*(pin&7)));                // GPIO_PIN MASK
    GPIOB->AFR[1] |= (GPIO_AF10_QUADSPI<<(4*(pin&7)));  // GPIO_PIN 4*(3)
    GPIOB->OTYPER &= ~(OUTPUT_TYPE<<(pin));             // GPIO_PIN MASK
    GPIOB->OTYPER |= (OUTPUT_PP<<(pin));                // GPIO_PIN PUSHPULL
    GPIOB->OSPEEDR &= (3<<(2*pin));                     // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_HIGH<<(2*pin));
  
    // PB11     ------> QSPI_NCS
    pin = 11;
    GPIOB->MODER &= ~(GPIO_MODE<<(2*pin));              // GPIO_PIN MASK
    GPIOB->MODER |= (GPIO_MODE_AF_PP<<(2*pin));         // GPIO_PIN OUTPUT
    GPIOB->AFR[1] &= ~(15<<(4*(pin&7)));                // GPIO_PIN MASK
    GPIOB->AFR[1] |= (GPIO_AF10_QUADSPI<<(4*(pin&7)));  // GPIO_PIN 4*(3)
    GPIOB->OTYPER &= ~(OUTPUT_TYPE<<(pin));             // GPIO_PIN MASK
    GPIOB->OTYPER |= (OUTPUT_PP<<(pin));                // GPIO_PIN PUSHPULL
    GPIOB->OSPEEDR &= (3<<(2*pin));                     // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_FREQ_HIGH<<(2*pin));

//    QUADSPI->CR = (7 << QUADSPI_CR_PRESCALER_Pos);
//    QUADSPI->CR = ((22 << QUADSPI_CR_PRESCALER_Pos) | QUADSPI_CR_TCEN);
    QUADSPI->CR = (22 << QUADSPI_CR_PRESCALER_Pos);
  
    QUADSPI->DCR = (23 << QUADSPI_DCR_FSIZE_Pos);  // 16 Mbyte
//    QUADSPI->DCR |= QUADSPI_DCR_CKMODE;
  
    QUADSPI->DLR = 0;
             // Read Data
    QUADSPI->CCR = ((3 << QUADSPI_CCR_FMODE_Pos) |  // Memory-mapped mode
                    (1 << QUADSPI_CCR_DMODE_Pos) |  // Singe data
                    (0 << QUADSPI_CCR_DCYC_Pos ) |  // no delay
                    (2 << QUADSPI_CCR_ADSIZE_Pos) | // 24 bit address
                    (1 << QUADSPI_CCR_ADMODE_Pos) | // single address
                    (1 << QUADSPI_CCR_IMODE_Pos)|   // single instruction
                    (CCR_READ_DATA << QUADSPI_CCR_INSTRUCTION_Pos));
    QUADSPI->AR = 0;
  
    QUADSPI->CR |= QUADSPI_CR_EN;
    }

void QUADSPI_IRQHandler(void)
    {
    QUADSPI->FCR = QUADSPI_FCR_CTOF |   // cClear timeout flag
                   QUADSPI_FCR_CSMF |   // Clear status match flag
                   QUADSPI_FCR_CTCF |   // Clear transfer complete flag
                   QUADSPI_FCR_CTEF;    // Clear transfer error flag
    }

// Erase all 16M bytes
void qspi_erase_all(void)
    {
        // Send 'enable writes' command.
    qspi_indirect_write(CCR_WRITE_ENABLE);
    qspi_indirect_write(CCR_CHIP_ERASE);
    while ( QUADSPI->SR & QUADSPI_SR_BUSY )
        ;
        // Disable the peripheral once the transaction is complete.
    QUADSPI->CR  &= ~( QUADSPI_CR_EN );
    qspi_memory_mode(2);
    }
    
// Erase a 64KB block. Block address = (bnum * 0x10000) 0..255
void qspi_erase_block( uint32_t bnum )
    {
    QUADSPI->CR  &= ~( QUADSPI_CR_EN );
        // Send 'enable writes' command.
    qspi_indirect_write(CCR_WRITE_ENABLE);
        // Erase the sector, and wait for the operation to complete.
    QUADSPI->CCR = ((0 << QUADSPI_CCR_FMODE_Pos) |  // Indirect write
                    (0 << QUADSPI_CCR_DMODE_Pos) |  // No data
                    (0 << QUADSPI_CCR_DCYC_Pos ) |  // No dummy
                    (2 << QUADSPI_CCR_ADSIZE_Pos) | // 24 bit address
                    (1 << QUADSPI_CCR_ADMODE_Pos) | // Single line
                    (1 << QUADSPI_CCR_IMODE_Pos));  // Single line
    QUADSPI->CR  |=  ( QUADSPI_CR_EN );
        // Block Erase (64KB)
    QUADSPI->CCR |=  ( CCR_BLOCK_ERASE << QUADSPI_CCR_INSTRUCTION_Pos );
        // The address is equal to the sector number * 4KB.
    QUADSPI->AR   =  ( bnum * 0x10000 );
    while ( QUADSPI->SR & QUADSPI_SR_BUSY )
        ;
        // Disable the peripheral once the transaction is complete.
    QUADSPI->CR  &= ~( QUADSPI_CR_EN );
    qspi_memory_mode(2);
    }

// Erase a 4KB sector. Sector address = ( snum * 0x1000 ) 0..4095
void qspi_erase_sector( uint32_t snum )
    {
        // Send 'enable writes' command.
    qspi_indirect_write(CCR_WRITE_ENABLE);
        // Erase the sector, and wait for the operation to complete.
    QUADSPI->CCR = ((0 << QUADSPI_CCR_FMODE_Pos) |  // Indirect write
                    (0 << QUADSPI_CCR_DMODE_Pos) |  // No data
                    (0 << QUADSPI_CCR_DCYC_Pos ) |  // No dummy
                    (2 << QUADSPI_CCR_ADSIZE_Pos) | // 24 bit address
                    (1 << QUADSPI_CCR_ADMODE_Pos) | // Single line
                    (1 << QUADSPI_CCR_IMODE_Pos));  // Single line
    QUADSPI->CR  |=  ( QUADSPI_CR_EN );
        // Sector Erase (4KB)
    QUADSPI->CCR |=  ( CCR_SECTOR_ERASE << QUADSPI_CCR_INSTRUCTION_Pos );
        // The address is equal to the sector number * 4KB.
    QUADSPI->AR   =  ( snum * 0x1000 );
    while ( QUADSPI->SR & QUADSPI_SR_BUSY )
        ;
        // Disable the peripheral once the transaction is complete.
    QUADSPI->CR  &= ~( QUADSPI_CR_EN );
    qspi_memory_mode(2);
    }

void qspi_memory_mode(uint8_t w)
    {
    // Enable memory-mapped mode. W25Q128JV Flash chips use
    // 3 "dummy cycles" with Quad I/O "fast read" instructions by
    // default, which allows up to 84MHz communication speed.
    // Maps to 0x90000000
    
        // if busy, clear busy first
    while (QUADSPI->SR & QUADSPI_SR_BUSY)
        QUADSPI->CR |= QUADSPI_CR_ABORT;        

    QUADSPI->CR  &= ~( QUADSPI_CR_EN );
    QUADSPI->DLR = 0;
    switch(w)
        {
        case 4:     // 0x0F0C_2DEB write Status Regoister 2 0x02
                    // Fast Read Quad I/O
            QUADSPI->CCR = ((3 << QUADSPI_CCR_FMODE_Pos) |  // Memory-mapped mode
                            (3 << QUADSPI_CCR_DMODE_Pos) |  // Quad data
                            (3 << QUADSPI_CCR_DCYC_Pos) |   // 3 delays
                            (2 << QUADSPI_CCR_ADSIZE_Pos) | // 24 bit address
                            (3 << QUADSPI_CCR_ADMODE_Pos) | // Quad address
                            (1 << QUADSPI_CCR_IMODE_Pos) |  // 1 line instruction
                            (CCR_FAST_READ_QUAD << QUADSPI_CCR_INSTRUCTION_Pos));
            break;
        case 2:     // 0x0E10_29BB
                    // Fast read dual I/O
            QUADSPI->CCR = ((3 << QUADSPI_CCR_FMODE_Pos) |  // Memory-mapped mode
                            (2 << QUADSPI_CCR_DMODE_Pos) |  // Dual data
                            (4 << QUADSPI_CCR_DCYC_Pos) |   // 4 delays
                            (2 << QUADSPI_CCR_ADSIZE_Pos) | // 24 bit address
                            (2 << QUADSPI_CCR_ADMODE_Pos) | // Dual address
                            (1 << QUADSPI_CCR_IMODE_Pos) |  // single instruction
                            (FAST_READ_DUAL << QUADSPI_CCR_INSTRUCTION_Pos)); 
            break;
        default:    // 0x0D00_2503
                    // Read Data single I/O
            QUADSPI->CCR = ((3 << QUADSPI_CCR_FMODE_Pos) |  // Memory-mapped mode
                            (1 << QUADSPI_CCR_DMODE_Pos) |  // Singe data
                            (0 << QUADSPI_CCR_DCYC_Pos ) |  // no delay
                            (2 << QUADSPI_CCR_ADSIZE_Pos) | // 24 bit address
                            (1 << QUADSPI_CCR_ADMODE_Pos) | // single address
                            (1 << QUADSPI_CCR_IMODE_Pos)|   // single instruction
                            (CCR_READ_DATA << QUADSPI_CCR_INSTRUCTION_Pos)); 
            break;
        }
    QUADSPI->CR  |=  ( QUADSPI_CR_EN );
    }
  
void qspi_indirect_read(uint8_t command, uint8_t receiveBuffer[], uint32_t length) 
    {
    uint32_t counter = 0x00;
    GPIOA->BSRR = GPIO_PIN_4;       // set high
        // if busy, clear busy first
    while (QUADSPI->SR & QUADSPI_SR_BUSY)
        QUADSPI->CR |= QUADSPI_CR_ABORT;        

        // Disable qspi to configure
    QUADSPI->CR &= ~(QUADSPI_CR_EN);
        // Clear all flags
    QUADSPI->FCR = QUADSPI_FCR_CTOF |
                   QUADSPI_FCR_CSMF | 
                   QUADSPI_FCR_CTCF | 
                   QUADSPI_FCR_CTEF;
        // Number of byte to write
    QUADSPI->DLR = length;
        // Clear instruction field
    QUADSPI->CCR = ((1 << QUADSPI_CCR_FMODE_Pos) |  // read mode
                    (1 << QUADSPI_CCR_DMODE_Pos) |  // single data line
                    (0 << QUADSPI_CCR_DCYC_Pos) |   // No delay
                    (0 << QUADSPI_CCR_ADSIZE_Pos) | // 8 bit address
                    (0 << QUADSPI_CCR_ADMODE_Pos) | // No address
                    (1 << QUADSPI_CCR_IMODE_Pos));  // single instruction line
    QUADSPI->CR |= (QUADSPI_CR_EN);
    
        //writing instruction starts communication
    QUADSPI->CCR |= (command << QUADSPI_CCR_INSTRUCTION_Pos); 
    
    GPIOA->BRR = GPIO_PIN_4;       // set low
        //wait while data arrives to FIFO
    while (counter < length) 
        {
        while (!(QUADSPI->SR & QUADSPI_SR_TCF))
            ; 
        receiveBuffer[counter++] = *(uint8_t*)(&QUADSPI->DR);
        }
    qspi_memory_mode(2);
    }
    
void qspi_indirect_write(uint8_t command) 
    {
        // if busy, clear busy first
    while (QUADSPI->SR & QUADSPI_SR_BUSY)
        QUADSPI->CR |= QUADSPI_CR_ABORT;        

    QUADSPI->CR &= ~(QUADSPI_CR_EN); // Disable qspi to configure

    QUADSPI->FCR = QUADSPI_FCR_CTOF |
                   QUADSPI_FCR_CSMF |
                   QUADSPI_FCR_CTCF | 
                   QUADSPI_FCR_CTEF; // Clear all flags
                       // Set indirect write, only instruction on 1 line, everything else off
                       // fmode imode admode abmode dcyc  dmode
    QUADSPI->CCR = ((0 << QUADSPI_CCR_FMODE_Pos) |  // write
                    (0 << QUADSPI_CCR_DMODE_Pos) |  // No data
                    (0 << QUADSPI_CCR_DCYC_Pos ) |  // No delay
                    (0 << QUADSPI_CCR_ADSIZE_Pos) | // 8 bit address
                    (0 << QUADSPI_CCR_ADMODE_Pos) | // No address
                    (1 << QUADSPI_CCR_IMODE_Pos));  // single instruction line

    QUADSPI->CR |= (QUADSPI_CR_EN);
        // Writing instruction starts communication
    QUADSPI->CCR |= (command << QUADSPI_CCR_INSTRUCTION_Pos); 
        // Wait for the transaction to complete
    while (QUADSPI->SR & QUADSPI_SR_BUSY)   
        ;
    qspi_memory_mode(2);
    }
    
    // QSPI 0xA0001000
void qspi_read(uint32_t addr, uint8_t receiveBuffer[], uint32_t length) 
    {
    uint32_t counter = 0;
        // if busy, clear busy first
    while (QUADSPI->SR & QUADSPI_SR_BUSY)
        QUADSPI->CR |= QUADSPI_CR_ABORT;        

        // Disable qspi to configure
    QUADSPI->CR &= ~(QUADSPI_CR_EN);
        // Clear all flags
    QUADSPI->DLR = length;  // bytes to read
    QUADSPI->FCR = QUADSPI_FCR_CTOF | 
                   QUADSPI_FCR_CSMF | 
                   QUADSPI_FCR_CTCF | 
                   QUADSPI_FCR_CTEF; // Clear all flags
    QUADSPI->CCR = ((1 << QUADSPI_CCR_FMODE_Pos) |  // read mode
                    (1 << QUADSPI_CCR_DMODE_Pos) |  // single data line
                    (0 << QUADSPI_CCR_DCYC_Pos ) |  // no dumby cycles
                    (2 << QUADSPI_CCR_ADSIZE_Pos) | // 24 bit address
                    (1 << QUADSPI_CCR_ADMODE_Pos) | // single address line
                    (1 << QUADSPI_CCR_IMODE_Pos));  // single instruction line
        // 4 bytes to read
    QUADSPI->CR |= (QUADSPI_CR_EN);
        //writing instruction starts communication
    QUADSPI->CCR |= (CCR_READ_DATA << QUADSPI_CCR_INSTRUCTION_Pos); 
    QUADSPI->AR = addr;     // address to start

    while (counter < length) 
        {
        while (!(QUADSPI->SR & QUADSPI_SR_TCF))
        ;        // wait while data arrives to FIFO
        receiveBuffer[counter++] = *(uint8_t*)(&QUADSPI->DR);
        }
    qspi_memory_mode(2);
    }
    
  void qspi_write_page(uint32_t address, uint8_t Buffer[], uint32_t length) 
    {
    uint32_t count = 0;
        // if busy, clear busy first
    while (QUADSPI->SR & QUADSPI_SR_BUSY)
        QUADSPI->CR |= QUADSPI_CR_ABORT;        

    QUADSPI->CR &= ~(QUADSPI_CR_EN); // Disable qspi to configure

    QUADSPI->FCR = QUADSPI_FCR_CTOF |
                   QUADSPI_FCR_CSMF | 
                   QUADSPI_FCR_CTCF | 
                   QUADSPI_FCR_CTEF; // Clear all flags
                         // Page Program
    QUADSPI->CCR = ((0 << QUADSPI_CCR_FMODE_Pos) |  // Indirect write
                    (1 << QUADSPI_CCR_DMODE_Pos) |  // Single line
                    (0 << QUADSPI_CCR_DCYC_Pos ) |  // No dummy
                    (2 << QUADSPI_CCR_ADSIZE_Pos) | // 24 bit address
                    (1 << QUADSPI_CCR_ADMODE_Pos) | // Single line
                    (1 << QUADSPI_CCR_IMODE_Pos) |  // Single line
                    (CCR_PAGE_PROGRAM << QUADSPI_CCR_INSTRUCTION_Pos));
    QUADSPI->CR |= (8 << QUADSPI_CR_FTHRES_Pos);
    QUADSPI->DLR = length - 1;
    QUADSPI->AR = address;
    QUADSPI->CR |= (QUADSPI_CR_EN);
    while (count < length)
        {
        *(uint8_t*)(&QUADSPI->DR) = Buffer[count++];
        while ((QUADSPI->SR & QUADSPI_SR_FTF) == 0);
        }
            // Wait for the transaction to complete
    while (QUADSPI->SR & QUADSPI_SR_BUSY)
        ;
    QUADSPI->CR &= ~(QUADSPI_CR_EN);
    
    qspi_memory_mode(2);
    }
