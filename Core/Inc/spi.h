#include "stm32g4xx_hal.h"

void SPI1a_Init(void);
void SPI1a_Start(char * buff, uint32_t len);
void SPI1d_Init(void);
void SPI1d_Start(char * wrBuff, char * rdBuff, uint32_t len);
void SPI2_Init(void);
void SPI3_Init(void);
void SPI4_Init(void);

// SPIx_CR1
    // BIDIMODE: Bidirectional data mode enable.
    // BIDIOE: Output enable in bidirectional mode
    // CRCEN: Hardware CRC calculation enable
    // CRCNEXT: Transmit CRC next
    // CRCL: CRC length
    // RXONLY: Receive only mode enabled.
    // SSI: Internal slave select
    // BR[2:0]: Baud rate control
        // 000: fPCLK/2
        // 001: fPCLK/4
        // 010: fPCLK/8
        // 011: fPCLK/16
        // 100: fPCLK/32
        // 101: fPCLK/64
        // 110: fPCLK/128
        // 111: fPCLK/256
    // MSTR: Master selection
    // CPOL: Clock polarity
    // CPHA: Clock phase
    
// SPIx_CR2
    // LDMA_TX: Last DMA transfer for transmission
    // LDMA_RX: Last DMA transfer for reception
    // FRXTH: FIFO reception threshold
    // DS[3:0]: Data size
        // 0011: 4-bit
        // 0100: 5-bit
        // 0101: 6-bit
        // 0110: 7-bit
        // 0111: 8-bit
        // 1000: 9-bit
        // 1001: 10-bit
        // 1010: 11-bit
        // 1011: 12-bit
        // 1100: 13-bit
        // 1101: 14-bit
        // 1110: 15-bit
        // 1111: 16-bit
    // TXEIE: Tx buffer empty interrupt enable
    // RXNEIE: RX buffer not empty interrupt enable
    // ERRIE: Error interrupt enable
    // FRF: Frame format
    // NSSP: NSS pulse management
    // SSOE: SS output enable
    // TXDMAEN: Tx buffer DMA enable
    // RXDMAEN: Rx buffer DMA enable

// SPIx_SR status register
    // FTLVL[1:0]: FIFO transmission level
    // FRLVL[1:0]: FIFO reception level
    // FRE: Frame format error
    // BSY: Busy flag
    // OVR: Overrun flag
    // MODF: Mode fault
    // CRCERR: CRC error flag
    // UDR: Underrun flag
    // CHSIDE: Channel side
    // TXE: Transmit buffer empty
    // RXNE: Receive buffer not empty
    
// SPIx_DR data register
    // DR[15:0]: Data register
    
// SPIx_CRCPR polynomial register
    // CRCPOLY[15:0]: CRC polynomial register
    
// SPIx_RXCRCR Rx CRC register
    // RXCRC[15:0]: Rx CRC register
    
// SPIx_TXCRCR Tx CRC register
    // TXCRC[15:0]: Tx CRC register
    
// SPIx_I2SCFGR configuration register
    // ASTRTEN: Asynchronous start enable.
    // I2SMOD: I2S mode selection
    // I2SE: I2S enable
    // I2SCFG[1:0]: I2S configuration mode
    // PCMSYNC: PCM frame synchronization
    // I2SSTD[1:0]: I2S standard selection
    // CKPOL: Inactive state clock polarity
    // DATLEN[1:0]: Data length to be transferred
    // CHLEN: Channel length
    
// SPIx_I2SPR prescaler register
    // MCKOE: Master clock output enable
    // ODD: Odd factor for the prescaler
    // I2SDIV[7:0]: I2S linear prescaler

