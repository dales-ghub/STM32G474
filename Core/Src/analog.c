#include "analog.h"

//COMP1234567
// COMP_CxCSR
    // LOCK: COMP_CxCSR register lock
    // VALUE: Comparator x output status
    // SCALEN: VREFINT scaler enable
    // BRGEN: VREFINT scaler resistor bridge enable
    // BLANKSEL[2:0]: Comparator x blanking signal select
    // HYST[2:0]: Comparator x hysteresis
    // POL: Comparator x polarity
    // INPSEL: Comparator x signal select for non-inverting input
        // INPSEL   1   2   3   4    5    6    7
        // 0      PA1 PA7 PA0 PB0 PB13 PB11 PB14
        // 1      PB1 PA3 PC1 PE7 PD12 PD11 PD14
    // INMSEL[2:0]: Comparator x signal select for inverting input
        // INMSEL       1        2        3        4        5        6        7
        // 000     1/4Ref   1/4Ref   1/4Ref   1/4Ref   1/4Ref   1/4Ref   1/4Ref
        // 001     1/2Ref   1/2Ref   1/2Ref   1/2Ref   1/2Ref   1/2Ref   1/2Ref
        // 010     3/4Ref   3/4Ref   3/4Ref   3/4Ref   3/4Ref   3/4Ref   3/4Ref
        // 011        Ref      Ref      Ref      Ref      Ref      Ref      Ref
        // 100   DAC3_CH1 DAC3_CH2 DAC3_CH1 DAC3_CH2 DAC4_CH1 DAC4_CH2 DAC4_CH1
        // 101   DAC1_CH1 DAC1_CH2 DAC1_CH1 DAC1_CH1 DAC1_CH2 DAC2_CH1 DAC2_CH1
        // 110        PA4      PA5      PF1      PE8     PB10     PD10     PD15
        // 111        PA0      PA2      PC0      PB2     PD13     PB15     PB12
    // EN: Comparator x enable

// COMP 0x40010200
void COMP1_Init(void) // PA1 / PB1
  {
  COMP1->CSR = COMP_CSR_SCALEN | COMP_CSR_BRGEN | COMP_CSR_EN;
  COMP1->CSR |= 1 << COMP_CSR_HYST_Pos; // 10mV hysteresis
  COMP1->CSR |= 1 << COMP_CSR_INMSEL_Pos; // 1/2 VREFINT
  }

void COMP2_Init(void) // PA7 / PA3
  {
  COMP2->CSR = COMP_CSR_SCALEN | COMP_CSR_BRGEN | COMP_CSR_EN;
  COMP2->CSR |= 1 << COMP_CSR_HYST_Pos; // 10mV hysteresis
  COMP2->CSR |= 1 << COMP_CSR_INMSEL_Pos; // 1/2 VREFINT
  }

void COMP3_Init(void) // PA0 / PC1
  {
  COMP3->CSR = COMP_CSR_SCALEN | COMP_CSR_BRGEN | COMP_CSR_EN;
  COMP3->CSR |= 1 << COMP_CSR_HYST_Pos; // 10mV hysteresis
  COMP3->CSR |= 1 << COMP_CSR_INMSEL_Pos; // 1/2 VREFINT
  }

void COMP4_Init(void) // PB0 / PE7
  {
  COMP4->CSR = COMP_CSR_SCALEN | COMP_CSR_BRGEN | COMP_CSR_EN;
  COMP4->CSR |= 1 << COMP_CSR_HYST_Pos; // 10mV hysteresis
  COMP4->CSR |= 1 << COMP_CSR_INMSEL_Pos; // 1/2 VREFINT
  }

void COMP5_Init(void) // PB13 / PD12
  {
  COMP5->CSR = COMP_CSR_SCALEN | COMP_CSR_BRGEN | COMP_CSR_EN;
  COMP5->CSR |= 1 << COMP_CSR_HYST_Pos; // 10mV hysteresis
  COMP5->CSR |= 1 << COMP_CSR_INMSEL_Pos; // 1/2 VREFINT
  }

void COMP6_Init(void) // PB11 / PD11
  {
  COMP6->CSR = COMP_CSR_SCALEN | COMP_CSR_BRGEN | COMP_CSR_EN;
  COMP6->CSR |= 1 << COMP_CSR_HYST_Pos; // 10mV hysteresis
  COMP6->CSR |= 1 << COMP_CSR_INMSEL_Pos; // 1/2 VREFINT
  }

void COMP7_Init(void) // PB14 / PD14
  {
  COMP7->CSR = COMP_CSR_SCALEN | COMP_CSR_BRGEN | COMP_CSR_EN;
  COMP7->CSR |= 1 << COMP_CSR_HYST_Pos; // 10mV hysteresis
  COMP7->CSR |= 1 << COMP_CSR_INMSEL_Pos; // 1/2 VREFINT
  }

// DAC1234
    // CR control register
        // CEN2: DAC channel2 calibration enable
        // DMAUDRIE2: DAC channel2 DMA underrun interrupt enable
        // DMAEN2: DAC channel2 DMA enable
        // MAMP2[3:0]: DAC channel2 mask/amplitude selector
        // WAVE2[1:0]: DAC channel2 noise/triangle wave generation enable
        // TSEL2[3:0]: DAC channel2 trigger selection
        // TEN2: DAC channel2 trigger enable
        // EN2: DAC channel2 enable
        // CEN1: DAC channel1 calibration enable
        // DMAUDRIE1: DAC channel1 DMA Underrun Interrupt enable
        // DMAEN1: DAC channel1 DMA enable
        // MAMP1[3:0]: DAC channel1 mask/amplitude selector
        // WAVE1[1:0]: DAC channel1 noise/triangle wave generation enable
        // TSEL1[3:0]: DAC channel1 trigger selection
        // TEN1: DAC channel1 trigger enable
        // EN1: DAC channel1 enable

    // SWTRGR software trigger register
        // SWTRIGB2: DAC channel2 software trigger B
        // SWTRIGB1: DAC channel1 software trigger B
        // SWTRIG2: DAC channel2 software trigger
        // SWTRIG1: DAC channel1 software trigger

    // DHR12R1 hannel1 12-bit right-aligned data
        // DACC1DHRB[11:0]: DAC channel1 12-bit right-aligned data B
        // DACC1DHR[11:0]: DAC channel1 12-bit right-aligned data

    // DHR12L1
        // channel1 12-bit left aligned data
            // DACC1DHRB[11:0]: DAC channel1 12-bit left-aligned data B
            // DACC1DHR[11:0]: DAC channel1 12-bit left-aligned data
            
    // DHR8R1 channel1 8-bit right aligned data
        // DACC1DHRB[7:0]: DAC channel1 8-bit right-aligned data
        // DACC1DHR[7:0]: DAC channel1 8-bit right-aligned data
        
    // DHR12R2 channel2 12-bit right aligned data
        // DACC2DHRB[11:0]: DAC channel2 12-bit right-aligned data
        // DACC2DHR[11:0]: DAC channel2 12-bit right-aligned data
        
    // DHR12L2 channel2 12-bit left aligned data
        // DACC2DHRB[11:0]: DAC channel2 12-bit left-aligned data B
        // DACC2DHR[11:0]: DAC channel2 12-bit left-aligned data
        
    // DHR8R2 channel2 8-bit right-aligned data
        // DACC2DHRB[7:0]: DAC channel2 8-bit right-aligned data
        // DACC2DHR[7:0]: DAC channel2 8-bit right-aligned data
        
    // DHR12RD Dual 12-bit right-aligned data
        // DACC2DHR[11:0]: DAC channel2 12-bit right-aligned data
        // DACC1DHR[11:0]: DAC channel1 12-bit right-aligned data
        
    // DHR12LD Dual 12-bit left aligned data
        // DACC2DHR[11:0]: DAC channel2 12-bit left-aligned data
        // DACC1DHR[11:0]: DAC channel1 12-bit left-aligned data
    
    // DHR8RD Dual DAC 8-bit right aligned data
        // DACC2DHR[7:0]: DAC channel2 8-bit right-aligned data
        // DACC1DHR[7:0]: DAC channel1 8-bit right-aligned data
        
    // DOR1 channel1 data output register
        // DACC1DORB[11:0]: DAC channel1 data output
        // DACC1DOR[11:0]: DAC channel1 data output
        
    // DOR2 channel2 data output register
        // DACC2DORB[11:0]: DAC channel2 data output
        // DACC2DOR[11:0]: DAC channel2 data output
        
    // SR status register
        // BWST2: DAC channel2 busy writing sample time flag
        // CAL_FLAG2: DAC channel2 calibration offset status
        // DMAUDR2: DAC channel2 DMA underrun flag
        // DORSTAT2: DAC channel2 output register status bit
        // DAC2RDY: DAC channel2 ready status bit
        // BWST1: DAC channel1 busy writing sample time flag
        // CAL_FLAG1: DAC channel1 calibration offset status
        // DMAUDR1: DAC channel1 DMA underrun flag
        // DORSTAT1: DAC channel1 output register status bit
        // DAC1RDY: DAC channel1 ready status bit

    // CCR calibration control register
        // OTRIM2[4:0]: DAC channel2 offset trimming value
        // OTRIM1[4:0]: DAC channel1 offset trimming value

    // MCR mode control register
        // SINFORMAT2: Enable signed format for DAC channel2
        // DMADOUBLE2: DAC channel2 DMA double data mode
        // MODE2[2:0]: DAC channel2 mode
        // HFSEL[1:0]: High frequency interface mode selection
        // SINFORMAT1: Enable signed format for DAC channel1
        // DMADOUBLE1: DAC channel1 DMA double data mode
        // MODE1[2:0]: DAC channel1 mode
// DAC1 0x50000800
void DAC1_Init(void) // PA4, PA5
    { // dual channel
    RCC->AHB2ENR |= RCC_AHB2ENR_DAC1EN;
    RCC->AHB2SMENR |= RCC_AHB2SMENR_DAC1SMEN; // Enable the APB clock FOR DAC1

    DAC1->CR = 0x0;
    DAC1->SWTRIGR = 0x0;
    DAC1->DHR12R1 = 0x01000100;
    DAC1->CCR = ((0xC<<DAC_CCR_OTRIM2_Pos) | (0x14 << DAC_CCR_OTRIM1_Pos));
    DAC1->MCR = DAC_MCR_HFSEL_1;
    DAC1->CR = DAC_CR_EN1;
  }

// DAC2 50000C00
void DAC2_Init(void) // PA6
  { // single cahnnel
  RCC->AHB2ENR |= RCC_AHB2ENR_DAC2EN;
  RCC->AHB2SMENR |= RCC_AHB2SMENR_DAC2SMEN; // Enable the APB clock FOR DAC1
  DAC2->CR = 0x0;
  DAC2->SWTRIGR = 0x0;
  DAC2->DHR12R1 = 0x00000100;
  DAC2->CCR =  0x14;
  DAC2->MCR = DAC_MCR_HFSEL_1;
  DAC2->CR |= DAC_CR_EN1;
  }

// DAC3 0x50001000
void DAC3_Init(void) // Internal
  { // dual channel
  RCC->AHB2ENR |= RCC_AHB2ENR_DAC3EN;
  RCC->AHB2SMENR |= RCC_AHB2SMENR_DAC3SMEN; // Enable the APB clock FOR DAC3
  DAC3->CR = 0x0;
  DAC3->SWTRIGR = 0x0;
  DAC3->DHR12R1 = 0x01000100;
  DAC3->CCR = 0x14;
  DAC3->MCR = DAC_MCR_HFSEL_1;
  DAC3->CR |= DAC_CR_EN1;
  }

// DAC4 0x50001400
void DAC4_Init(void) // Internal
  { // dual channel
  RCC->AHB2ENR |= RCC_AHB2ENR_DAC4EN;
  RCC->AHB2SMENR |= RCC_AHB2SMENR_DAC4SMEN; // Enable the APB clock FOR DAC4
  DAC4->CR = 0x0;
  DAC4->SWTRIGR = 0x0;
  DAC4->DHR12R1 = 0x01000100;
  DAC4->CCR = (0xC<<16 | 0x14);
  DAC4->MCR = DAC_MCR_HFSEL_1;
  DAC4->CR = DAC_CR_EN1;
  }
// OPAMP123456
    // CSR control/status register
        // LOCK: OPAMP1_CSR lock
        // CALOUT: Operational amplifier calibration output
        // TRIMOFFSETN[4:0]: Trim for NMOS differential pairs
        // TRIMOFFSETP[4:0]: Trim for PMOS differential pairs
        // PGA_GAIN[4:0]: Operational amplifier gain value
        // CALSEL[1:0]: Calibration selection
        // CALON: Calibration mode enabled
        // OPAINTOEN: Operational amplifier internal output enable
        // OPAHSM: Operational amplifier high-speed mode
        // VM_SEL[1:0]: Inverting input selection
        // USERTRIM: User trimming enable
        // VP_SEL[1:0]: Non inverted input selection
        // FORCE_VP: Force internal reference on OPAMP VINP
        // OPAEN: Operational amplifier Enable
    // TCMR 
        // LOCK: OPAMP1_TCMR lock
        // T20CM_EN: TIM20 controlled mux mode enable
        // T8CM_EN: TIM8 controlled mux mode enable
        // T1CM_EN: TIM1 controlled mux mode enable
        // VPS_SEL[1:0]: OPAMP1 Non inverting input secondary selection.
        // VMS_SEL: OPAMP1 inverting input secondary selection
        
// OPAMP1 0x40010300
    // VM_SEL[1:0]: Inverting input selection
        // 00: connected to PA3
        // 01: connected to PC5
        // 10: PGA mode, Inverting input
        // 11: Follower mode
    // VP_SEL[1:0]: Non inverted input selection
        // 00: connected to PA1
        // 01: connected to PA3
        // 10: connected to PA7
        // 11: connected to DAC3_CH1
    // OPAMP1_VOUT
        // PA2
        // ADC1_IN3
        // ADC1_IN13
void OPAMP1_Init(void)
    {
    OPAMP1->CSR = 0x0;   
    OPAMP1->TCMR = 0x0;    
    OPAMP1->CSR = OPAMP_CSR_OPAMPxEN;
    }

// OPAMP2 0x40010304
    // VM_SEL[1:0]: Inverting input selection
        // 00: connected to PA5
        // 01: connected to PC5
        // 10: PGA mode, Inverting input
        // 11: Follower mode
    // VP_SEL[1:0]: Non inverted input selection
        // 00: connected to PA7
        // 01: connected to PB14
        // 10: connected to PB0
        // 11: connected to PD14
    // OPAMP2_VOUT
        // PA6
        // ADC2_IN3
        // ADC2_IN16
void OPAMP2_Init(void)
    {
    OPAMP2->CSR = 0x0;
    OPAMP2->TCMR = 0x0;
    OPAMP2->CSR = OPAMP_CSR_OPAMPxEN;
    }
     
// OPAMP3 0x40010308
    // VM_SEL[1:0]: Inverting input selection
        // 00: connected to PB2
        // 01: connected to PB10
        // 10: PGA mode, Inverting input
        // 11: Follower mode
    // VP_SEL[1:0]: Non inverted input selection
        // 00: connected to PB0
        // 01: connected to PB13
        // 10: connected to PA1
        // 11: connected to DAC3_CH2
    // OPAMP3_VOUT
        // PB1
        // ADC3_IN1
        // ADC1_IN12
        // ADC2_IN18
        // ADC3_IN13
void OPAMP3_Init(void)
    {
    OPAMP3->CSR = 0x0;
    OPAMP3->TCMR = 0x0;
    OPAMP3->CSR = OPAMP_CSR_OPAMPxEN;
    }
     
// OPAMP4 0x4001030C
    // VM_SEL[1:0]: Inverting input selection
        // 00: connected to PB10
        // 01: connected to PD8
        // 10: PGA mode, Inverting input
        // 11: Follower mode
    // VP_SEL[1:0]: Non inverted input selection
        // 00: connected to PB13
        // 01: connected to PD11
        // 10: connected to PB11
        // 11: connected to DAC4_CH1
    // OPAMP4_VOUT
        // PB12
        // ADC4_IN3
        // ADC1_IN11
        // ADC5_IN5
void OPAMP4_Init(void)
    {
    OPAMP4->CSR = 0x0;
    OPAMP4->TCMR = 0x0;
    OPAMP4->CSR = OPAMP_CSR_OPAMPxEN;
    }
     
// OPAMP5 0x40010310
    // VM_SEL[1:0]: Inverting input selection
        // 00: connected to PB15
        // 01: connected to PA3
        // 10: PGA mode, Inverting input
        // 11: Follower mode
    // VP_SEL[1:0]: Non inverted input selection
        // 00: connected to PB14
        // 01: connected to PD12
        // 10: connected to PC3
        // 11: connected to DAC4_CH2
    // OPAMP5_VOUT
        // PA8
        // ADC5_IN1
        // ADC5_IN3
void OPAMP5_Init(void)
    {
    OPAMP5->CSR = 0x0;
    OPAMP5->TCMR = 0x0;
    OPAMP5->CSR = OPAMP_CSR_OPAMPxEN;
    }
     
// OPAMP6 0x40010314
    // VM_SEL[1:0]: Inverting input selection
        // 00: connected to PA1
        // 01: connected to PB1
        // 10: PGA mode, Inverting input
        // 11: Follower mode
    // VP_SEL[1:0]: Non inverted input selection
        // 00: connected to PB12
        // 01: connected to PD9
        // 10: connected to PB13
        // 11: connected to DAC3_CH1
    // OPAMP6_VOUT
        // PB11
        // ADC12_IN14
        // ADC4_IN17
        // ADC3_IN17
void OPAMP6_Init(void)
    {
    OPAMP6->CSR = 0x0;
    OPAMP6->TCMR = 0x0;
    OPAMP6->CSR = OPAMP_CSR_OPAMPxEN;
    }

// VREFBUF
    // CR control and status register
        // VRS[1:0]: Voltage reference scale
            // 00: Voltage reference set to 2.048 V
            // 01: Voltage reference set to 2.5 V
            // 10: Voltage reference set to 2.90 V
        // VRR: Voltage reference buffer ready
        // HIZ: High impedance mode
        // ENVR: Voltage reference buffer mode enable
    // CCR calibration control register
        // TRIM[5:0]: Trimming code
// 0x40010030
void VREF_Init(void)
    {
    
    }
    
