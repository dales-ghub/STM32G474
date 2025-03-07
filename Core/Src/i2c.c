#include "i2c.h"

// I2C
  // CR1
    // PECEN: PEC enable
    // LERTEN: SMBus alert enable
    // LERTEN: SMBus alert enable
    // SMBHEN: SMBus host
    // GCEN: General call
    // WUPEN: Wakeup from Stop
    // NOSTRETCH: Clock stretching
    // SBC: Slave byte
    // RXDMAEN: DMA reception
    // TXDMAEN: DMA transmission
    // ANFOFF: Analog noise filter
    // DNF[3:0]: Digital noise filter
    // ERRIE: Error
    // TCIE: Transfer Complete
    // STOPIE: Stop detection
    // NACKIE: Not acknowledge received
    // ADDRIE: Address match
    // RXIE: RX
    // TXIE: TX
    // PE: Peripheral enable
  // CR2
    // PECBYTE: Packet error checking
    // AUTOEND: Automatic end
    // RELOAD: NBYTES reload
    // NBYTES[7:0]: Number of bytes
    // NACK: NACK generation
    // STOP: Stop generation
    // START: Start generation
    // HEAD10R: 10-bit address
    // ADD10: 10-bit addressing
    // RD_WRN: Transfer direction = Write transfer
    // SADD[9:0]: Slave address
  // OAR1
    // OA1EN: Own Address
    // OA1MODE: Own Address 1 10-bit
    // OA1[9:0]: Interface own slave address
  // I2C_OAR2
    // OA2EN: Own Address 2
    // OA2MSK[2:0]: Own Address 2 masks
    // OA2[7:1]: Interface address
  // TIMINGR
    // PRESC[3:0]: Timing prescaler
    // SCLDEL[3:0]: Data setup time
    // SDADEL[3:0]: Data hold time
    // SCLH[7:0]: SCL high period
    // SCLL[7:0]: SCL low period  
  // TIMEOUTR
    // TEXTEN: Extended clock timeout
    // TIMEOUTB[11:0]: Bus timeout B
    // TIMOUTEN: Clock timeout
    // TIDLE: Idle clock timeout detection
    // TIMEOUTA[11:0]: Bus Timeout A
  // ISR
    // ADDCODE[6:0]: Address match code
    // DIR: Transfer direction
    // BUSY: Bus busy
    // ALERT: SMBus alert
    // TIMEOUT: Timeout
    // PECERR: PEC Error in reception
    // OVR: Overrun/Underrun
    // ARLO: Arbitration lost
    // BERR: Bus error
    // TCR: Transfer Complete Reload
    // STOPF: Stop detection flag
    // NACKF: Not Acknowledge received
    // ADDR: Address matched
    // RXNE: Receive data register not empty
    // TXIS: Transmit interrupt status
    // TXE: Transmit data register empty
  // ICR
    // ALERTCF: Alert flag clear
    // TIMOUTCF: Timeout detection flag clear
    // PECCF: PEC Error flag clear
    // OVRCF: Overrun/Underrun flag clear
    // ARLOCF: Arbitration lost flag clear
    // BERRCF: Bus error flag clear
    // STOPCF: STOP detection flag clear
    // NACKCF: Not Acknowledge flag clear
    // ADDRCF: Address matched flag clear
  // PECR
    // PEC[7:0]: Packet error checking
  // RXDR
    // RXDATA[7:0]: 8-bit receive data
  // TXDR
    // TXDATA[7:0]: 8-bit transmit data

I2C_struct I2C1data = {
        I2C1,   // i2c port
        0,      // device address
        0,      // data pointer
        0,      // Status flags
        0,      // number of read bytes
        0};     // number of write bytes
        
// I2C1_SCL PA13 PA15 PB8
// I2C1_SDA PA14 PB7
// I2C1 0x40005400
I2C_struct * I2C1_Init(uint8_t * data)
    {
    I2C1data.Ptr = data;
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;
    
    I2C1->CR1 = 0;
    I2C1->CR2 = 0;
    I2C1->CR2 &=  ~( 0x3FF << I2C_CR2_SADD_Pos | 0xFF << I2C_CR2_NBYTES_Pos );
    I2C1->TIMINGR = (10 << I2C_TIMINGR_PRESC_Pos);
    I2C1->TIMINGR |= (6 << I2C_TIMINGR_SCLDEL_Pos);
    I2C1->TIMINGR |= (6 << I2C_TIMINGR_SDADEL_Pos);
    I2C1->TIMINGR |= (17 << I2C_TIMINGR_SCLH_Pos);
    I2C1->TIMINGR |= (17 << I2C_TIMINGR_SCLL_Pos);
    NVIC_EnableIRQ(I2C1_ER_IRQn);
    NVIC_EnableIRQ(I2C1_EV_IRQn);

    // PA 0x48000000
    // PA13    ------> I2C1_SCL
    int pin = 13;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[1] &= ~(15<<(4*(pin-8)));            // GPIO_PIN MASK
    GPIOA->AFR[1] |= (GPIO_AF4_I2C1<<(4*(pin-8)));  // GPIO_PIN 4*(2)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_OD<<(pin));            // GPIO_PIN OPEN DRAIN
    GPIOA->PUPDR &= ~(3<<(2*pin));                  // GPIO_PIN MASK
    GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));         // GPIO_PIN PULLUP
    GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_HIGH<<(2*pin));

    // PA14    ------> I2C1_SDA
    pin = 14;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[1] &= ~(15<<(4*(pin-8)));            // GPIO_PIN MASK
    GPIOA->AFR[1] |= (GPIO_AF4_I2C1<<(4*(pin-8)));  // GPIO_PIN 4*(2)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_OD<<(pin));            // GPIO_PIN OPEN DRAIN
    GPIOA->PUPDR &= ~(3<<(2*pin));                  // GPIO_PIN MASK
    GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));         // GPIO_PIN PULLUP
    GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_HIGH<<(2*pin));
    
    return &I2C1data;
    }

I2C_struct I2C2data = {
        I2C2,   // i2c port
        0,      // device address
        0,      // data pointer
        0,      // Status flags
        0,      // number of read bytes
        0};     // number of write bytes
        
// I2C2_SCL PA9 PC4 PF6
// I2C2_SDA PA8 PF0
// I2C2 0x40005800
I2C_struct * I2C2_Init(uint8_t * data)
    {
    I2C2data.Ptr = data;
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C2EN;

    I2C2->CR1 = 0;
    I2C2->CR2 = 0;
    I2C2->CR2 &=  ~( 0x3FF << I2C_CR2_SADD_Pos | 0xFF << I2C_CR2_NBYTES_Pos );
    I2C2->TIMINGR = (10 << I2C_TIMINGR_PRESC_Pos);
    I2C2->TIMINGR |= (6 << I2C_TIMINGR_SCLDEL_Pos);
    I2C2->TIMINGR |= (6 << I2C_TIMINGR_SDADEL_Pos);
    I2C2->TIMINGR |= (17 << I2C_TIMINGR_SCLH_Pos);
    I2C2->TIMINGR |= (17 << I2C_TIMINGR_SCLL_Pos);
    NVIC_EnableIRQ(I2C2_ER_IRQn);
    NVIC_EnableIRQ(I2C2_EV_IRQn);

    // PA 0x48000000
    // PA8    ------> I2C2_SDA
    int pin = 8;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOA->AFR[0] |= (GPIO_AF4_I2C2<<(4*pin));      // GPIO_PIN 4*(2)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_OD<<(pin));            // GPIO_PIN OPEN DRAIN
    GPIOA->PUPDR &= ~(3<<(2*pin));                  // GPIO_PIN MASK
    GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));         // GPIO_PIN PULLUP
    GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_HIGH<<(2*pin));

    // PA9    ------> I2C2_SCl
    pin = 14;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[1] &= ~(15<<(4*(pin-8)));            // GPIO_PIN MASK
    GPIOA->AFR[1] |= (GPIO_AF4_I2C2<<(4*(pin-8)));  // GPIO_PIN 4*(2)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_OD<<(pin));            // GPIO_PIN OPEN DRAIN
    GPIOA->PUPDR &= ~(3<<(2*pin));                  // GPIO_PIN MASK
    GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));         // GPIO_PIN PULLUP
    GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_HIGH<<(2*pin));
    
    return &I2C2data;
    }

I2C_struct I2C3data = {
        I2C3,   // i2c port
        0,      // device address
        0,      // data pointer
        0,      // Status flags
        0,      // number of read bytes
        0};     // number of write bytes
        
// I2C3_SCL PA8 PC8 PF3 PG7
// I2C3_SDA PA9 PB7 PC9 PC11 PF4 PG8
// I2C3 0x40007800
I2C_struct * I2C3_Init(uint8_t * data)
    {
    int pin;
    I2C3data.Ptr = data;
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C3EN;

    I2C3->CR1 = 0;
    I2C3->CR2 = 0;
    I2C3->CR2 &=  ~( 0x3FF << I2C_CR2_SADD_Pos | 0xFF << I2C_CR2_NBYTES_Pos );
    I2C3->TIMINGR = (10 << I2C_TIMINGR_PRESC_Pos);
    I2C3->TIMINGR |= (6 << I2C_TIMINGR_SCLDEL_Pos);
    I2C3->TIMINGR |= (6 << I2C_TIMINGR_SDADEL_Pos);
    I2C3->TIMINGR |= (17 << I2C_TIMINGR_SCLH_Pos);
    I2C3->TIMINGR |= (17 << I2C_TIMINGR_SCLL_Pos);
    NVIC_EnableIRQ(I2C3_ER_IRQn);
    NVIC_EnableIRQ(I2C3_EV_IRQn);
    
    // PA 0x48000000
    // PA8    ------> I2C3_SCL
    pin = 8;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[0] &= ~(15<<4*(pin));                // GPIO_PIN MASK
    GPIOA->AFR[0] |= (GPIO_AF2_I2C3<<(4*pin));      // GPIO_PIN 4*(2)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_OD<<(pin));            // GPIO_PIN OPEN DRAIN
    GPIOA->PUPDR &= ~(3<<(2*pin));                  // GPIO_PIN MASK
    GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));         // GPIO_PIN PULLUP
    GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_HIGH<<(2*pin));

    // PA9    ------> I2C3_SDA
    pin = 9;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[1] &= ~(15<<(4*(pin-8)));            // GPIO_PIN MASK
    GPIOA->AFR[1] |= (GPIO_AF2_I2C3<<(4*(pin-8)));  // GPIO_PIN 4*(2)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_OD<<(pin));            // GPIO_PIN OPEN DRAIN
    GPIOA->PUPDR &= ~(3<<(2*pin));                  // GPIO_PIN MASK
    GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));         // GPIO_PIN PULLUP
    GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_HIGH<<(2*pin));
    
    return &I2C3data;
    }
  
I2C_struct I2C4data = {
        I2C4,   // i2c port
        0,      // device address
        0,      // data pointer
        0,      // Status flags
        0,      // number of read bytes
        0};     // number of write bytes
        
// I2C4_SCL PA13    PC6 PF14    PG3
// I2C4_SDA PB7     PC7 PF15    PG4
// I2C4 0x40008400  
I2C_struct * I2C4_Init(uint8_t * data)
    {
    I2C4data.Ptr = data;
    RCC->APB1ENR2 |= RCC_APB1ENR2_I2C4EN;

    I2C4->CR1 = 0;
    I2C4->CR2 = 0;
    I2C4->CR2 &=  ~( 0x3FF << I2C_CR2_SADD_Pos | 0xFF << I2C_CR2_NBYTES_Pos );
    I2C4->TIMINGR = (10 << I2C_TIMINGR_PRESC_Pos);
    I2C4->TIMINGR |= (6 << I2C_TIMINGR_SCLDEL_Pos);
    I2C4->TIMINGR |= (6 << I2C_TIMINGR_SDADEL_Pos);
    I2C4->TIMINGR |= (17 << I2C_TIMINGR_SCLH_Pos);
    I2C4->TIMINGR |= (17 << I2C_TIMINGR_SCLL_Pos);
    NVIC_EnableIRQ(I2C4_ER_IRQn);
    NVIC_EnableIRQ(I2C4_EV_IRQn);
    
    // PA 0x48000000
    // PA13    ------> I2C4_SCL
    int pin = 13;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[1] &= ~(15<<(4*(pin-8)));            // GPIO_PIN MASK
    GPIOA->AFR[1] |= (GPIO_AF3_I2C4<<(4*(pin-8)));  // GPIO_PIN 4*(2)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_OD<<(pin));            // GPIO_PIN OPEN DRAIN
    GPIOA->PUPDR &= ~(3<<(2*pin));                  // GPIO_PIN MASK
    GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));         // GPIO_PIN PULLUP
    GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_HIGH<<(2*pin));

    // PB7    ------> I2C2_SDA
    pin = 7;
    GPIOA->MODER &= ~(GPIO_MODE<<(2*pin));          // GPIO_PIN MASK
    GPIOA->MODER |= (GPIO_MODE_AF_PP<<(2*pin));     // GPIO_PIN OUTPUT
    GPIOA->AFR[0] &= ~(15<<(4*pin));                // GPIO_PIN MASK
    GPIOA->AFR[0] |= (GPIO_AF3_I2C4<<(4*pin));      // GPIO_PIN 4*(2)
    GPIOA->OTYPER &= ~(OUTPUT_TYPE<<(pin));         // GPIO_PIN MASK
    GPIOA->OTYPER |= (OUTPUT_OD<<(pin));            // GPIO_PIN OPEN DRAIN
    GPIOA->PUPDR &= ~(3<<(2*pin));                  // GPIO_PIN MASK
    GPIOA->PUPDR |= (GPIO_PULLUP<<(2*pin));         // GPIO_PIN PULLUP
    GPIOA->OSPEEDR &= ~(3<<(2*pin));                // GPIO_PIN MASK
    GPIOA->OSPEEDR |= (GPIO_SPEED_HIGH<<(2*pin));
    
    return &I2C1data;
    }

// BERR     Bus error
// ARLO     Arbitration loss
// OVR      Overrun/Underrun
// PECERR   PEC error
// TIMEOUT  Timeout
// ALERT    SMBus alert
void I2C1_ER_IRQHandler(void)
    {
    if(I2C1->ISR & I2C_ISR_BERR)
        {
        I2C1->ICR |= I2C_ICR_BERRCF;
        I2C1data.Status |= 0x100;
        }
    if(I2C1->ISR & I2C_ISR_ARLO)
        {
        I2C1->ICR |= I2C_ICR_ARLOCF;
        I2C1data.Status |= 0x200;
        }
    if(I2C1->ISR & I2C_ISR_OVR)
        {
        I2C1->ICR |= I2C_ICR_OVRCF;
        I2C1data.Status |= 0x400;
        }
    if(I2C1->ISR & I2C_ISR_PECERR)
        {
        I2C1->ICR |= I2C_ICR_PECCF;
        I2C1data.Status |= 0x800;
        }
    if(I2C1->ISR & I2C_ISR_ALERT)
        {
        I2C1->ICR |= I2C_ICR_ALERTCF;
        I2C1data.Status |= 0x2000;
        }
    }
    
// RXNE     Receive buffer not empty
// TXIS     Transmit buffer interrupt status
// STOPF    Stop detection interrupt flag
// TCR      Transfer complete reload
// TC       Transfer complete
// ADDR     Address matched
// NACKF    NACK reception
void I2C1_EV_IRQHandler(void)
    {
    if(I2C1->ISR & I2C_ISR_TXE)
        {
        I2C1->TXDR = *I2C1data.Ptr++;
        I2C1data.Status |= 0x1;
        }
    if(I2C1->ISR & I2C_ISR_TXIS)
        {
        I2C1->TXDR = *I2C1data.Ptr++;
        I2C1data.Status |= 0x2;
        }
    if(I2C1->ISR & I2C_ISR_RXNE) 
        {
        I2C1data.Status |= 0x4;
        *(I2C1data.Ptr++)  = (uint8_t)I2C1->RXDR;
        }
    if(I2C1->ISR & I2C_ISR_ADDR)
        {
        I2C1->ICR |= I2C_ICR_ADDRCF;
        I2C1data.Status |= 0x8;
        }
    if(I2C1->ISR & I2C_ISR_NACKF)
        {
        I2C1->ICR |= I2C_ICR_NACKCF;
        I2C1data.Status |= 0x10;
        }
     if(I2C1->ISR & I2C_ISR_STOPF)
        {
        I2C1->ICR |= I2C_ICR_STOPCF;
        I2C1data.Status |= 0x20;
        if(I2C1data.readBytes > 0)
            {
            I2C1->CR2 |= I2C_CR2_RD_WRN;  // Read enable
            I2C1->CR2 &= ~(0xFF << I2C_CR2_NBYTES_Pos);
            I2C1->CR2 |= (I2C1data.readBytes << I2C_CR2_NBYTES_Pos);
            I2C1->CR2 |= I2C_CR2_AUTOEND;  //  
            I2C1->CR2 |= I2C_CR2_START;  //
            I2C1data.readBytes = 0;
            }
        else
            I2C1data.Status |= 0x8000;
        }
    if(I2C1->ISR & I2C_ISR_TC)
        {
        I2C1data.Status |= 0x40;
        }
    if(I2C1->ISR & I2C_ISR_TCR)
        {
        I2C1->CR2 &= ~(0xFF << I2C_CR2_NBYTES_Pos);
        I2C1data.Status |= 0x80;
       }
    }
    
// AT2AA01 eeProm
// 128 x 8
// address = 1010xxx
// write device + addrL + data

// AT24C32 eeProm
// 4096 x 8
// address = 101111
// write device + addrH + addrL
// read data ...

// AT24C32 eeProm
// 4096 x 8
// address = 1010111
// write device + addrH + addrL + data ...

// DS3231 read
// address = 0x68

void I2C_Start(I2C_struct * data)
    {
    GPIOB->BRR = GPIO_PIN_12;
//    GPIOA->OTYPER |= (1<<(14));            // GPIO_PIN OPEN DRAIN
    
    data->I2Cx->CR1 |= I2C_CR1_PE;     // start transfer
    data->I2Cx->CR2 &= ~I2C_CR2_START;     // Clear start
    data->I2Cx->CR2 &= ~I2C_CR2_ADD10;     // ADDR 7 bits
    data->I2Cx->CR2 &= ~(0x3FF << I2C_CR2_SADD_Pos);
    data->I2Cx->CR2 |= data->Addr << I2C_CR2_SADD_Pos;
    data->I2Cx->CR2 &= ~(I2C_CR2_RD_WRN);  // Write enable
    data->I2Cx->CR2 &= ~(0xFF << I2C_CR2_NBYTES_Pos);
    data->I2Cx->CR2 |= (data->writeBytes << I2C_CR2_NBYTES_Pos);
    data->I2Cx->CR1 |= (I2C_CR1_ERRIE |    // Error interrupts enable
                 I2C_CR1_TCIE |     //Transfer Complete interrupt enable
                 I2C_CR1_TXIE |     // transmit irq enable
                 I2C_CR1_STOPIE |   // Stop detection Interrupt enable
                 I2C_CR1_NACKIE |   // Not acknowledge received
                 I2C_CR1_RXIE |     // RX Interrupt enable
                 I2C_CR1_TXIE);     // TX Interrupt enable
    data->I2Cx->CR2 |= I2C_CR2_AUTOEND;  //  
    data->I2Cx->CR2 |= I2C_CR2_START;  //  

    }

// DS3231 get
void DS3231_get(I2C_struct * data)
    {
    data->Ptr[0] = 0;
    data->readBytes = 7;
    data->writeBytes = 1;
    data->Addr = 0x68 << 1;
    RTC->TR = (data->Ptr[3] << 16) |
              (data->Ptr[2] << 8) |
              (data->Ptr[2] << 0);
    RTC->DR = (data->Ptr[7] << 16) |
              (data->Ptr[6] << 8) |
              (data->Ptr[5] << 0) |
              (data->Ptr[4] << 13);
    
    }
    
    // DS3231 set
void DS3231_set(I2C_struct * data)
    {
    data->Ptr[0] = 0;
    data->Ptr[1] = (RTC->TR >> 0) & 0xff;   // get seconds
    data->Ptr[2] = (RTC->TR >> 8) & 0xff;   // get minutes
    data->Ptr[3] = (RTC->TR >> 16) & 0x7f;  // get hours
    data->Ptr[4] = (RTC->DR >> 13) & 0x3;   // get dow
    data->Ptr[5] = (RTC->DR >> 0) & 0x3f;   // get day
    data->Ptr[6] = (RTC->DR >> 8) & 0x1f;   // get month
    data->Ptr[7] = (RTC->DR >> 16) & 0xff;  // get year
    data->readBytes = 0;
    data->writeBytes = 8;
    data->Addr = 0x68 << 1;
    I2C_Start(data);
    }
    
void I2C_wr8(I2C_struct * data, uint16_t Addr, uint8_t val)
    {
    data->Ptr[0] = Addr >> 8;
    data->Ptr[1] = Addr & 0xff;
    data->Ptr[2] = val;
    data->readBytes = 0;
    data->writeBytes = 3;
    I2C_Start(data);
    }    
    
void I2C_wr16(I2C_struct * data, uint16_t Addr, uint16_t val)
    {
    data->Ptr[0] = Addr >> 8;
    data->Ptr[1] = Addr & 0xff;
    data->Ptr[2] = val >> 8;
    data->Ptr[3] = val & 0xff;
    data->readBytes = 0;
    data->writeBytes = 4;
    I2C_Start(data);
    }    

void I2C_wr32(I2C_struct * data, uint16_t Addr, uint32_t val)
    {
    data->Ptr[0] = Addr >> 8;
    data->Ptr[1] = Addr & 0xff;
    data->Ptr[2] = (val >> 24) & 0xff;
    data->Ptr[3] = (val >> 16) & 0xff;
    data->Ptr[4] = (val >> 8) & 0xff;
    data->Ptr[5] = val & 0xff;
    data->readBytes = 0;
    data->writeBytes = 6;
    I2C_Start(data);
    }    

