#include "main.h"

void ADC_Cal(uint8_t chan);
int ADC_rd(uint8_t chan);
float ADC_temp(uint16_t adc, uint16_t vref);
void ADC1_Init(void);
void ADC2_Init(void);
void ADC3_Init(void);
void ADC4_Init(void);
void ADC5_Init(void);

    /* 
    Internal temperature sensor, temperature at which temperature sensor
    has been calibrated in production for data into TEMPSENSOR_CAL2_ADDR
    (tolerance: +-5 DegC) (unit: DegC). 
    */
#define TEMPSENSOR_CAL1_ADDR               ((uint16_t*) (0x1FFF75A8UL))
#define TEMPSENSOR_CAL1_TEMP               (30L)
#define TEMPSENSOR_CAL2_TEMP               (130L)
#define TEMPSENSOR_CAL2_ADDR               ((uint16_t*) (0x1FFF75CAUL))
#define TEMPSENSOR_CAL_VREFANALOG          (3000UL)
/*
temp = (TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP) /
       (*TEMPSENSOR_CAL2_ADDR - *TEMPSENSOR_CAL1_ADDR) *
       (TS_DATA - TEMPSENSOR_CAL1_ADDR) + 
*/
