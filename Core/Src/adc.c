#include "adc.h"

void ADC_Cal(uint8_t chan)
    {
    switch(chan)
        {
        case 1:
            ADC5->CR |= ADC_CR_ADDIS;
            ADC1->CR &= ~ADC_CR_ADCALDIF;
            ADC1->CR |= ADC_CR_ADDIS;
            ADC1->CR |= ADC_CR_ADCAL;
            while((ADC1->CR & ADC_CR_ADCAL) == ADC_CR_ADCAL)
                ;
            ADC1->CR |= ADC_CR_ADEN;
            break;
        case 2:
            ADC2->CR |= ADC_CR_ADDIS;
            ADC2->CR &= ~ADC_CR_ADCALDIF;
            ADC2->CR |= ADC_CR_ADDIS;
            ADC2->CR |= ADC_CR_ADCAL;
            while((ADC2->CR & ADC_CR_ADCAL) == ADC_CR_ADCAL)
                ;
            ADC2->CR |= ADC_CR_ADEN;
            break;
        case 3:
            ADC3->CR |= ADC_CR_ADDIS;
            ADC3->CR &= ~ADC_CR_ADCALDIF;
            ADC3->CR |= ADC_CR_ADDIS;
            ADC3->CR |= ADC_CR_ADCAL;
            while((ADC3->CR & ADC_CR_ADCAL) == ADC_CR_ADCAL)
                ;
            ADC3->CR |= ADC_CR_ADEN;
            break;
        case 4:
            ADC4->CR |= ADC_CR_ADDIS;
            ADC4->CR &= ~ADC_CR_ADCALDIF;
            ADC4->CR |= ADC_CR_ADDIS;
            ADC4->CR |= ADC_CR_ADCAL;
            while((ADC4->CR & ADC_CR_ADCAL) == ADC_CR_ADCAL)
                ;
            ADC4->CR |= ADC_CR_ADEN;
            break;
        case 5:
            ADC5->CR |= ADC_CR_ADDIS;
            ADC5->CR &= ~ADC_CR_ADCALDIF;
            ADC5->CR |= ADC_CR_ADCAL;
            while((ADC5->CR & ADC_CR_ADCAL) == ADC_CR_ADCAL)
                ;
            ADC5->CR |= ADC_CR_ADEN;
            break;
        }
    }

// ADC read
int ADC_rd(uint8_t chan)
    {
    ADC_TypeDef * ADC;
    switch(chan)
        {
        case 1:
            ADC = ADC1;
            break;
        case 2:
            ADC = ADC2;
            break;
        case 3:
            ADC = ADC3;
            break;
        case 4:
            ADC = ADC4;
            break;
        case 5:
            ADC = ADC5;
            break;
        default:
            return(0);
        }
    
    ADC->CFGR &= ~ADC_CFGR_EXTEN;
    ADC->CR |= ADC_CR_ADEN;
    ADC->CR |= ADC_CR_ADSTART;
//    return((int)ADC->DR);
    while((ADC->ISR & ADC_ISR_EOC) == 0)
        ;
    return((int)ADC->DR);
    }

float ADC_temp(uint16_t adc, uint16_t vref)
    {
    float a = (float)(TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP) /
       (float)(*TEMPSENSOR_CAL2_ADDR - *TEMPSENSOR_CAL1_ADDR);
    float b = (float)adc * (float)vref/(float)TEMPSENSOR_CAL_VREFANALOG;
    return (float)(a * (b - (float)*TEMPSENSOR_CAL1_ADDR) +
           (float)TEMPSENSOR_CAL1_TEMP);
    }
        
// ADC
    // ISR interrupt and status register [0x00]
        // JQOVF: Injected context queue overflow
        // AWD3: Analog watchdog 3 flag
        // AWD2: Analog watchdog 2 flag
        // AWD1: Analog watchdog 1 flag
        // JEOS: Injected channel end of sequence flag
        // JEOC: Injected channel end of conversion flag
        // OVR: ADC overrun
        // EOS: End of regular sequence flag
        // EOC: End of conversion flag
        // EOSMP: End of sampling flag
        // ADRDY: ADC ready
    // IER interrupt enable register [0x04]
        // JQOVFIE: Injected context queue overflow interrupt enable
        // AWD3IE: Analog watchdog 3 interrupt enable
        // AWD2IE: Analog watchdog 2 interrupt enable
        // AWD1IE: Analog watchdog 1 interrupt enable
        // JEOSIE: End of injected sequence of conversions interrupt enable
        // JEOCIE: End of injected conversion interrupt enable
        // OVRIE: Overrun interrupt enable
        // EOSIE: End of regular sequence of conversions interrupt enable
        // EOCIE: End of regular conversion interrupt enable
        // EOSMPIE: End of sampling flag interrupt for regular conversions
        // ADRDYIE: ADC ready interrupt enable
    // CR control register [0x08]
        // ADCAL: ADC calibration
        // ADCALDIF: Differential mode for calibration
        // DEEPPWD: Deep-power-down enable
        // ADVREGEN: ADC voltage regulator enable
        // JADSTP: ADC stop of injected conversion command
        // ADSTP: ADC stop of regular conversion command
        // JADSTART: ADC start of injected conversion
        // ADSTART: ADC start of regular conversion
        // ADDIS: ADC disable command
        // ADEN: ADC enable control
    // CFGR configuration register [0x0C]
        // JQDIS: Injected Queue disable
        // AWD1CH[4:0]: Analog watchdog 1 channel selection
        // JAUTO: Automatic injected group conversion
        // JAWD1EN: Analog watchdog 1 enable on injected channels
        // AWD1EN: Analog watchdog 1 enable on regular channels
        // AWD1SGL: Enable the watchdog 1 on a single channel or on all channels
        // JQM: JSQR queue mode
        // JDISCEN: Discontinuous mode on injected channels
        // DISCNUM[2:0]: Discontinuous mode channel count
        // DISCEN: Discontinuous mode for regular channels
        // ALIGN: Data alignment
        // AUTDLY: Delayed conversion mode
        // CONT: Single / continuous conversion mode for regular
        // OVRMOD: Overrun mode
        // EXTEN[1:0]: External trigger enable and polarity selection for regular
        // EXTSEL[4:0]: External trigger selection for regular group
        // RES[1:0]: Data resolution
        // DMACFG: Direct memory access configuration
        // DMAEN: Direct memory access enable
    // CFGR2 configuration register 2 [0x10]
        // SMPTRIG: Sampling time control trigger mode
        // BULB: Bulb sampling mode
        // SWTRIG: Software trigger bit for sampling time control trigger mode
        // GCOMP: Gain compensation mode
        // ROVSM: Regular Oversampling mode
        // TROVS: Triggered Regular Oversampling
        // OVSS[3:0]: Oversampling shift
        // OVSR[2:0]: Oversampling ratio
        // JOVSE: Injected Oversampling Enable
        // ROVSE: Regular Oversampling Enable
    // SMPR1 sample time register 1 [0x14]
        // SMPPLUS: Addition of one clock cycle to the sampling time
        // SMPx[2:0]: Channel x sampling time selection (x = 9 to 0)
    // SMPR2 sample time register 2 [0x18]
        // SMPx[2:0]: Channel x sampling time selection (x = 18 to 10)
    // TR1 watchdog threshold register 1 [0x20]
        // HT1[11:0]: Analog watchdog 1 higher threshold
        // AWDFILT: Analog watchdog filtering parameter
        // LT1[11:0]: Analog watchdog 1 lower threshold
    // TR2 watchdog threshold register 2 [0x24]
        // HT2[7:0]: Analog watchdog 2 higher threshold
        // LT2[7:0]: Analog watchdog 2 lower threshold
    // TR3 watchdog threshold register 3 [0x28]
        // HT3[7:0]: Analog watchdog 3 higher threshold
        // LT3[7:0]: Analog watchdog 3 lower threshold
    // SQR1 regular sequence register 1 [0x30]
        // SQ4[4:0]: 4th conversion in regular sequence
        // SQ3[4:0]: 3rd conversion in regular sequence
        // SQ2[4:0]: 2nd conversion in regular sequence
        // SQ1[4:0]: 1st conversion in regular sequence
        // L[3:0]: Regular channel sequence length
    // SQR2 regular sequence register 1 [0x34]
        // SQ9[4:0]: 9th conversion in regular sequence
        // SQ8[4:0]: 8th conversion in regular sequence
        // SQ7[4:0]: 7th conversion in regular sequence
        // SQ6[4:0]: 6th conversion in regular sequence
        // SQ5[4:0]: 5th conversion in regular sequence
    // SQR3 regular sequence register 1 [0x38]
        // SQ14[4:0]: 14th conversion in regular sequence
        // SQ13[4:0]: 13th conversion in regular sequence
        // SQ12[4:0]: 12th conversion in regular sequence
        // SQ11[4:0]: 11th conversion in regular sequence
        // SQ10[4:0]: 10th conversion in regular sequence
    // SQR4 regular sequence register 1 [0x3C]
        // SQ16[4:0]: 16th conversion in regular sequence
        // SQ15[4:0]: 15th conversion in regular sequence
    // DR regular data register [0x40]
        // RDATA[15:0]: Regular data converted
    // JSQR injected sequence register [0x4C]
        // JSQ4[4:0]: 4th conversion in the injected sequence
        // JSQ3[4:0]: 3rd conversion in the injected sequence
        // JSQ2[4:0]: 2nd conversion in the injected sequence
        // JSQ1[4:0]: 1st conversion in the injected sequence
        // JEXTEN[1:0]: External Trigger Enable and Polarity Selection for injected channels
        // JEXTSEL[4:0]: External Trigger Selection for injected group
        // JL[1:0]: Injected channel sequence length
    // OFRy offset y register [0x60 + 0x04 * (y -1)]
        // OFFSET_EN: Offset y enable
        // OFFSET_CH[4:0]: Channel selection for the data offset y
        // SATEN: Saturation enable
        // OFFSETPOS: Positive offset
        // OFFSET[11:0]: Data offset y for the channel
    // JDRy injected channel y data register [0x80 + 0x04 * (y - 1)]
        // JDATA[15:0]: Injected data
    // AWD2CR analog watchdog 2 configuration register [0xA0]
        // AWD2CH[18:0]: Analog watchdog 2 channel selection
    // AWD3CR analog watchdog 3 configuration register [0xA4]
        // AWD3CH[18:0]: Analog watchdog 3 channel selection
    // DIFSEL differential mode selection register [0xB0]
        // DIFSEL[18:0]: Differential mode for channels 18 to 0
    // CALFACT calibration factors [0xB4]
        // CALFACT_D[6:0]: Calibration Factors in differential mode
        // CALFACT_S[6:0]: Calibration Factors In single-ended mode
    // GCOMP Gain compensation Register [0xC0]
        // GCOMPCOEFF[13:0]: Gain compensation coefficient
    // CSR common status register [0x300]
        // JQOVF_SLV: Injected Context Queue Overflow flag of the slave ADC
        // AWD3_SLV: Analog watchdog 3 flag of the slave ADC
        // AWD2_SLV: Analog watchdog 2 flag of the slave ADC
        // AWD1_SLV: Analog watchdog 1 flag of the slave ADC
        // JEOS_SLV: End of injected sequence flag of the slave ADC
        // JEOC_SLV: End of injected conversion flag of the slave ADC
        // OVR_SLV: Overrun flag of the slave ADC
        // EOS_SLV: End of regular sequence flag of the slave ADC
        // EOC_SLV: End of regular conversion of the slave ADC
        // EOSMP_SLV: End of Sampling phase flag of the slave ADC
        // ADRDY_SLV: Slave ADC ready
        // JQOVF_MST: Injected Context Queue Overflow flag of the master ADC
        // AWD3_MST: Analog watchdog 3 flag of the master ADC
        // AWD2_MST: Analog watchdog 2 flag of the master ADC
        // AWD1_MST: Analog watchdog 1 flag of the master ADC
        // JEOS_MST: End of injected sequence flag of the master ADC
        // JEOC_MST: End of injected conversion flag of the master ADC
        // OVR_MST: Overrun flag of the master ADC
        // EOS_MST: End of regular sequence flag of the master ADC
        // EOC_MST: End of regular conversion of the master ADC
        // EOSMP_MST: End of Sampling phase flag of the master ADC
        // ADRDY_MST: Master ADC ready
    // CCR common control register [0x308]
        // VBATSEL: VBAT selection
        // VSENSESEL: VTS selection
        // VREFEN: VREFINT enable
        // PRESC[3:0]: ADC prescaler
        // CKMODE[1:0]: ADC clock mode
        // MDMA[1:0]: Direct memory access mode for dual ADC mode
        // DMACFG: DMA configuration
        // DELAY: Delay between 2 sampling phases
        // DUAL[4:0]: Dual ADC mode selection
    // CDR common regular data register for dual [0x30C]
        // RDATA_SLV[15:0]: Regular data of the slave ADC
        // RDATA_MST[15:0]: Regular data of the master ADC
    //

// ADC1_IN12
// ADC1 0x50000000
void ADC1_Init(void)
    {
    RCC->AHB2ENR |= RCC_AHB2ENR_ADC12EN;
    RCC->CCIPR |= (2 << RCC_CCIPR_ADC12SEL_Pos);
    ADC1->CR = ADC_CR_ADVREGEN; // 10 00 00 01
    ADC1->CFGR = ADC_CFGR_JQDIS; // 80 00 00 00
    ADC1->CFGR2 = ADC_CFGR2_ROVSE; // 79
    ADC1->CFGR2 |= (ADC_CFGR2_OVSR_2 | ADC_CFGR2_OVSR_1); // 128x
    ADC1->CFGR2 |= (ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0); // Shift 3-bits
    ADC1->SMPR1 = 0x0; // 0        
    ADC1->SMPR2 = (ADC_SMPR2_SMP12_2 | ADC_SMPR2_SMP12_1); // 1 80
    ADC1->TR1 |= (7 << ADC_TR1_AWDFILT_Pos);  // F FF 00 00
    ADC1->TR1 |= (255 << ADC_TR1_HT1_Pos);       // F FF 00 00
    ADC1->TR2 |= (255 << ADC_TR2_HT2_Pos);    // FF 00 00
    ADC1->TR3 |= (255 << ADC_TR3_HT3_Pos);    // FF 00 00
    ADC1->SQR1 |= (0xC << ADC_SQR1_SQ1_Pos);  // 3 00
    ADC1->CR |= ADC_CR_ADEN;
    }
    
void ADC2_Init(void)
    {
    RCC->AHB2ENR |= RCC_AHB2ENR_ADC12EN;
    RCC->CCIPR |= (2 << RCC_CCIPR_ADC12SEL_Pos);
    ADC2->CR = ADC_CR_ADVREGEN; // 10 00 00 01
    ADC2->CFGR = ADC_CFGR_JQDIS; // 80 00 00 00
    ADC2->CFGR2 = ADC_CFGR2_ROVSE; // 79
    ADC2->CFGR2 |= (ADC_CFGR2_OVSR_2 | ADC_CFGR2_OVSR_1); // 128x
    ADC2->CFGR2 |= (ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0); // Shift 3-bits
    ADC2->SMPR1 = 0x0; // 0        
    ADC2->SMPR2 = (ADC_SMPR2_SMP12_2 | ADC_SMPR2_SMP12_1); // 1 80
    ADC2->TR1 |= (7 << ADC_TR1_AWDFILT_Pos);  // F FF 00 00
    ADC2->TR1 |= (255 << ADC_TR1_HT1_Pos);       // F FF 00 00
    ADC2->TR2 |= (255 << ADC_TR2_HT2_Pos);    // FF 00 00
    ADC2->TR3 |= (255 << ADC_TR3_HT3_Pos);    // FF 00 00
    ADC2->SQR1 |= (0xC << ADC_SQR1_SQ1_Pos);  // 3 00
    ADC2->SQR1 |= 1 << ADC_SQR1_L_Pos;
    ADC2->CR |= ADC_CR_ADEN;
    }
    
// ADC3_IN5
// ADC3 0x50000400
void ADC3_Init(void)
  {
  RCC->AHB2ENR |= RCC_AHB2ENR_ADC345EN;
  RCC->CCIPR |= (2 << RCC_CCIPR_ADC345SEL_Pos);
  ADC3->CR = ADC_CR_ADVREGEN;     // Enable ADC
  ADC3->CFGR = ADC_CFGR_JQDIS;    // Disable injection
  ADC3->CFGR2 = ADC_CFGR2_ROVSE;  // Regular Oversampling Enable
  ADC3->CFGR2 |= (ADC_CFGR2_OVSR_2 | ADC_CFGR2_OVSR_1); // 128x
  ADC3->CFGR2 |= (ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0); // Shift 3-bits
  ADC3->SMPR1 = (ADC_SMPR1_SMP4_2 | ADC_SMPR1_SMP4_1);  // 0        
  ADC3->SMPR2 = (ADC_SMPR2_SMP11_2 | ADC_SMPR2_SMP11_1); // 1 80
  ADC3->TR1 |= (0xFFF << ADC_TR1_HT1_Pos);    // F FF 00 00
  ADC3->TR2 |= (0xFF << ADC_TR2_HT2_Pos);     // FF 00 00
  ADC3->TR3 |= (0xFF << ADC_TR3_HT3_Pos);     // FF 00 00
  ADC3->SQR1 |= (13 << ADC_SQR1_SQ1_Pos);   // 3 00
  ADC3->SQR1 |= 1 << ADC_SQR1_L_Pos;
  ADC3->CR |= ADC_CR_ADEN;
  }

// ADC4_IN4
// ADC4 0X50000500
void ADC4_Init(void)
  {
  RCC->AHB2ENR |= RCC_AHB2ENR_ADC345EN;
  RCC->CCIPR |= (2 << RCC_CCIPR_ADC345SEL_Pos);
  ADC4->CR = ADC_CR_ADVREGEN;     // Enable ADC
  ADC4->CFGR = ADC_CFGR_JQDIS;    // Disable injection
  ADC4->CFGR2 = ADC_CFGR2_ROVSE;  // Regular Oversampling Enable
  ADC4->CFGR2 |= (ADC_CFGR2_OVSR_2 | ADC_CFGR2_OVSR_1); // 128x
  ADC4->CFGR2 |= (ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0); // Shift 3-bits
  ADC4->SMPR1 = (ADC_SMPR1_SMP4_2 | ADC_SMPR1_SMP4_1);  // 0        
  ADC4->SMPR2 = (ADC_SMPR2_SMP11_2 | ADC_SMPR2_SMP11_1); // 1 80
  ADC4->TR1 = 0xF;
  ADC4->TR1 |= (0xFFF << ADC_TR1_HT1_Pos);    // F FF 00 00
  ADC4->TR2 |= (0xFF << ADC_TR2_HT2_Pos);     // FF 00 00
  ADC4->TR3 |= (0xFF << ADC_TR3_HT3_Pos);     // FF 00 00
  ADC4->SQR1 |= (0x4 << ADC_SQR1_SQ1_Pos);    // 3 00
  ADC4->CR |= ADC_CR_ADEN;
  }

// ADC5_IN4
// ADC5 0x50000600
void ADC5_Init(void)
  {
  RCC->AHB2ENR |= RCC_AHB2ENR_ADC345EN;
  RCC->CCIPR |= (2 << RCC_CCIPR_ADC345SEL_Pos);
  ADC5->CR = ADC_CR_ADVREGEN; // 10 00 00 01
//  ADC5->CFGR = ADC_CFGR_JQDIS | ADC_CFGR_JAUTO; // 80 00 00 00
  ADC5->CFGR = ADC_CFGR_JQDIS; // 80 00 00 00
  ADC5->CFGR2 = ADC_CFGR2_ROVSE; // 79
  ADC5->CFGR2 |= (ADC_CFGR2_OVSR_2 | ADC_CFGR2_OVSR_1); // 128x
  ADC5->CFGR2 |= (ADC_CFGR2_OVSS_2 | ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0); // Shift 3-bits
  ADC5->SMPR1 = (ADC_SMPR1_SMP4_2 | ADC_SMPR1_SMP4_1); // 0        
  ADC5->SMPR2 = (ADC_SMPR2_SMP11_2 | ADC_SMPR2_SMP11_1); // 1 80
  ADC5->TR1 |= 0xF;    // F FF 00 00
  ADC5->TR1 |= (0xFFF << ADC_TR1_AWDFILT_Pos);    // F FF 00 00
  ADC5->TR2 |= (0xFF << ADC_TR2_HT2_Pos);         // FF 00 00
  ADC5->TR3 |= (0xFF << ADC_TR3_HT3_Pos);         // FF 00 00
  ADC5->SQR1 |= (0x4 << ADC_SQR1_SQ1_Pos);        // 3 00
  ADC345_COMMON->CCR |= (ADC_CCR_VSENSESEL);      // Temperature
  ADC5->CR |= ADC_CR_ADEN;
//  ADC5->IER |= ADC_IER_EOSIE;
//  NVIC_EnableIRQ(ADC5_IRQn);
  }

