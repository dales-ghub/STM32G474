#include "stm32g4xx_hal.h"

typedef struct 
    {
    I2C_TypeDef * I2Cx;     // i/o port address
    uint8_t Addr;           // device address
    uint8_t * Ptr;          // data pointer
    uint8_t Status;         // Status flags
    uint8_t readBytes;      // number of read bytes
    uint8_t writeBytes;     // number of write bytes
    } I2C_struct;

I2C_struct * I2C1_Init(uint8_t * data);
I2C_struct * I2C2_Init(uint8_t * data);
I2C_struct * I2C3_Init(uint8_t * data);
I2C_struct * I2C4_Init(uint8_t * data);

void I2C_Start(I2C_struct * data);
void DS3231_set(I2C_struct * data);

