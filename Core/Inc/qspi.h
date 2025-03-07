#include "main.h"
#include "stm32g4xx_hal.h"

void QSPI_Init(void);
void qspi_erase_all(void);
void qspi_erase_block(uint32_t bnum);
void qspi_erase_sector(uint32_t snum);
void qspi_memory_mode(uint8_t w);
void qspi_indirect_read(uint8_t command, uint8_t receiveBuffer[], uint32_t length);
void qspi_indirect_write(uint8_t command);
void qspi_read(uint32_t addr, uint8_t receiveBuffer[], uint32_t length);
void qspi_write_page(uint32_t address, uint8_t Buffer[], uint32_t length);

// QSPI
  // QUADSPI_CR 0x00
    // PRESCALER[7:0]
    // PMM: Polling match mode
    // APMS: Automatic poll mode stop
    // TOIE: Timeout interrupt enable
    // SMIE: Status match interrupt enable
    // FTIE: FIFO threshold interrupt enable
    // TCIE: Transfer complete interrupt enable
    // TEIE: Transfer error interrupt enable
    // FTHRES[3:0]: FIFO threshold level
    // FSEL: Flash memory selection
    // TCEN: Timeout counter enable
    // DMAEN: DMA enable
    // ABORT: Abort request
    // EN: Enable

  // DCR 0x04
    // FSIZE[4:0]: Flash memory size
    // CSHT[2:0]: Chip select high time
    // CKMODE: Mode 0/mode 3

  // SR (Status register) 0x08
    // FLEVEL[4:0]: FIFO level
    // BUSY: Busy
    // TOF: Timeout flag
    // SMF: Status match flag
    // FTF: FIFO threshold flag
    // TCF: Transfer complete flag
    // TEF: Transfer error flag
    
  // FCR 0x0C
    // CTOF: Clear timeout flag
    // CSMF: Clear status match flag
    // CTCF: Clear transfer complete flag
    // CTEF: Clear transfer error flag
    
  // DLR (data length register) 0x10

  // CCR 0x14
    // DDRM: Double data rate mode
        // 0: DDR mode disabled
        // 1: DDR mode enabled
    // DHHC: DDR hold
        // 0: Data output delayed using analog delay
        // 1: Data output delayed by 1/4 of a QUADSPI output clock cycle
    // SIOO: Send instruction only once mode
        // 0: Instruction sent on every transaction
        // 1: Instruction sent only for the first command
    // FMODE[1:0]: Functional mode
        // 00: Indirect write mode
        // 01: Indirect read mode
        // 10: Automatic polling mode
        // 11: Memory-mapped mode
    // DMODE[1:0]: Data mode
        // 00: No data
        // 01: Data on a single line
        // 10: Data on two lines
        // 11: Data on four lines
    // DCYC[4:0]: Number of dummy cycles
    // ABSIZE[1:0]: Alternate bytes size
        // 00: 8-bit alternate byte
        // 01: 16-bit alternate bytes
        // 10: 24-bit alternate bytes
        // 11: 32-bit alternate bytes
    // ABMODE[1:0]: Alternate bytes mode
        // 00: No alternate bytes
        // 01: Alternate bytes on a single line
        // 10: Alternate bytes on two lines
        // 11: Alternate bytes on four lines
    // ADSIZE[1:0]: Address size 
        // 00: 8-bit address
        // 01: 16-bit address
        // 10: 24-bit address
        // 11: 32-bit address
    // ADMODE[1:0]: Address mode
        // 00: No address
        // 01: Address on a single line
        // 10: Address on two lines
        // 11: Address on four lines
    // IMODE[1:0]: Instruction mode
        // 00: No instruction
        // 01: Instruction on a single line
        // 10: Instruction on two lines
        // 11: Instruction on four lines
    // INSTRUCTION[7:0]: Instruction

  // AR (Address) 0x18

  // ABR (alternate bytes)
  // DR (Data register)
  // PSMKR (polling status mask)
  // PSMAR (polling status match)
  // PIR (polling interval)
  // LPTR (low power timeout)

