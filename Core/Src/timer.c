#include "timer.h"

// High-resolution timer (HRTIM)
// Advanced-control timers (TIM1/TIM8/TIM20)
// General-purpose timers (TIM2/TIM3/TIM4/TIM5)
// General purpose timers (TIM15/TIM16/TIM17)
// Low-power timer (LPTIM)

// CHA1  PA8
// CHA2  PA9
// CHB1  PA10
// CHB2  PA11
// CHC1  PB12
// CHC2  PB13
// CHD1  PB14
// CHD2  PB15
// CHE1  PC8
// CHE2  PC9
// CHF1  PC6
// CHF2  PC7
// EEV1  PC12
// EEV2  PC11
// EEV3  PB7
// EEV4  PB6
// EEV6  PB5
// EEV7  PB4
// EEV8  PB8
// EEV9  PB3
// EEV10 PC6  PC5
// FLT1  PA12
// FLT2  PA15
// FLT3  PB10
// FLT4  PB11
// FLT5  PB0  PC7
// FLT6  PC10
// OUT   PA14 PB2
// SCOUT PB3  PB1
// SCIN  PB6
// HRTIM 0x40016800
void HRTIM_Init(void)
    {
    RCC->APB1ENR1 |= RCC_APB2ENR_HRTIM1EN;

        // MCR master timer control register
            // BRSTDMA[1:0]: Burst DMA update
            // MREPU: Master timer repetition update
            // PREEN: Preload enable
            // DACSYNC[1:0] DAC synchronization
            // TFCEN: Timer F counter enable
            // TECEN: Timer E counter enable
            // TDCEN: Timer D counter enable
            // TCCEN: Timer C counter enable
            // TBCEN: Timer B counter enable
            // TADEN: Timer A counter enable
            // MCEN: Master timer counter enable
            // SYNCSRC[1:0]: Synchronization source
            // SYNCOUT[1:0]: Synchronization output
            // SYNCSTRTM: Synchronization starts master
            // SYNCRSTM: Synchronization resets master
            // SYNCIN[1:0] Synchronization input
            // INTLVD[1:0]: Interleaved mode
            // HALF: Half mode
            // RETRIG: Re-triggerable mode
            // CONT: Continuous mode
        // CKPSC[2:0]: Clock prescaler
    HRTIM1->sMasterRegs.MCR = 0;

        // MISR master timer interrupt status register
            // MUPD: Master update interrupt flag
            // SYNC: Sync input interrupt flag
            // MREP: Master repetition interrupt flag
            // MCMP4: Master compare 4 interrupt flag
            // MCMP3: Master compare 3 interrupt flag
            // MCMP2: Master compare 2 interrupt flag
            // MCMP1: Master compare 1 interrupt flag
    HRTIM1->sMasterRegs.MISR = 0;

        // MICR master timer interrupt clear register
            // MUPDC: Master update interrupt flag clear
            // SYNCC: Sync input interrupt flag clear
            // MREPC: Repetition interrupt flag clear
            // MCMP4C: Master compare 4 interrupt flag clear
            // MCMP3C: Master compare 3 interrupt flag clear
            // MCMP2C: Master compare 2 interrupt flag clear
            // MCMP1C: Master compare 1 interrupt flag clear
    HRTIM1->sMasterRegs.MICR = 0;

        // HRTIM_MDIER master timer DMA interrupt enable register
            // MUPDDE: Master update DMA request enable
            // SYNCDE: Sync input DMA request enable
            // MREPDE: Master repetition DMA request enable
            // MCMP4DE: Master compare 4 DMA request enable
            // MCMP3DE: Master compare 3 DMA request enable
            // MCMP2DE: Master compare 2 DMA request enable
            // MCMP1DE: Master compare 1 DMA request enable
            // MUPDIE: Master update interrupt enable
            // SYNCIE: Sync input interrupt enable
            // MREPIE: Master repetition interrupt enable
            // MCMP4IE: Master compare 4 interrupt enable
            // MCMP3IE: Master compare 3 interrupt enable
            // MCMP2IE: Master compare 2 interrupt enable
            // MCMP1IE: Master compare 1 interrupt enable
    HRTIM1->sMasterRegs.MDIER = 0;

        // HRTIM_MCNTR master timer counter register
            // MCNT[15:0]: Counter value
    HRTIM1->sMasterRegs.MCNTR = 0;

        // HRTIM_MPER master timer period register
            // MPER[15:0]: Master timer period value
    HRTIM1->sMasterRegs.MPER = 0;

        // HRTIM_MREP master timer repetition register
            // MREP[7:0]: Master timer repetition period value
    HRTIM1->sMasterRegs.MREP = 0;

        // HRTIM_MCMP1R master timer compare 1 register
            // MCMP1[15:0]: Master timer compare 1 value
    HRTIM1->sMasterRegs.MCMP1R = 0;

        // HRTIM_MCMP2R master timer compare 2 register
            // MCMP2[15:0]: Master timer compare 2 value
    HRTIM1->sMasterRegs.MCMP2R = 0;

        // HRTIM_MCMP3R master timer compare 3 register
            // MCMP3[15:0]: Master timer compare 3 value
    HRTIM1->sMasterRegs.MCMP3R = 0;

        // HRTIM_MCMP4R master timer compare 4 register
            // MCMP4[15:0]: Master timer compare 4 value
    HRTIM1->sMasterRegs.MCMP4R = 0;

        // HRTIM_TIMxCR timer [0:5] control register
            // UPDGAT[3:0]: Update gating
                // 0000: independently from the DMA burst transfer
                // 0001: when the DMA burst transfer is completed
                // 0010: update event following the DMA burst
                // 0011: on a rising edge on hrtim_upd_en1
                // 0100: on a rising edge on hrtim_upd_en2
                // 0101: on a rising edge on hrtim_upd_en3
                // 0110: following a rising edge on hrtim_upd_en1
                // 0111: following a rising edge on hrtim_upd_en2
                // 1000: following a rising edge on hrtim_upd_en3
            // PREEN: Preload enable
            // DACSYNC[1:0] DAC synchronization
            // MSTU: Master timer update
            // TEU: Timer E update
            // TDU: Timer D update
            // TCU: Timer C update
            // TBU: Timer B update
            // TAU: Timer A update
            // TxRSTU: Timer x reset update
            // TxREPU: Timer x repetition update
            // TFU: Timer F update
            // DELCMP4[1:0]: CMP4 auto-delayed mode
            // DELCMP2[1:0]: CMP2 auto-delayed mode
            // SYNCSTRTx: Synchronization starts timer x
            // SYNCRSTx: Synchronization resets timer x
            // RSYNCU: Re-synchronized update
            // INTLVD[1:0]: Interleaved mode
            // PSHPLL: Push-pull mode enable
            // HALF: Half mode enable
            // RETRIG: Re-triggerable mode
            // CONT: Continuous mode
            // CKPSCx[2:0]: HRTIM timer x clock prescaler
    HRTIM1->sTimerxRegs[0].TIMxCR = 0;

        // HRTIM timer x interrupt status register
            // O2CPY: Output 2 copy
            // O1CPY: Output 1 copy
            // O2STAT: Output 2 status
            // O1STAT: Output 1 status
            // IPPSTAT: Idle push-pull Status
            // CPPSTAT: Current push-pull status
            // DLYPRT: Delayed protection flag
            // RST: Reset and/or roll-over interrupt flag
            // RSTx2: Output 2 reset interrupt flag
            // SETx2: Output 2 set interrupt flag
            // RSTx1: Output 1 reset interrupt flag
            // SETx1: Output 1 set interrupt flag
            // CPT2: Capture 2 interrupt flag
            // CPT1: Capture 1 interrupt flag
            // UPD: Update interrupt flag
            // REP: Repetition interrupt flag
            // CMP4: Compare 4 interrupt flag
            // CMP3: Compare 3 interrupt flag
            // CMP2: Compare 2 interrupt flag
            // CMP1: Compare 1 interrupt flag
    HRTIM1->sTimerxRegs[0].TIMxISR = 0;

        // TIMxICR timer x interrupt clear register
            // DLYPRTC: Delayed protection flag clear
            // RSTC: Reset interrupt flag clear
            // RSTx2C: Output 2 reset flag clear
            // SETx2C: Output 2 set flag clear
            // RSTx1C: Output 1 reset flag clear
            // SETx1C: Output 1 set flag clear
            // CPT2C: Capture 2 interrupt flag clear
            // CPT1C: Capture 1 interrupt flag clear
            // UPDC: Update interrupt flag clear
            // REPC: Repetition interrupt flag clear
            // CMP4C: Compare 4 interrupt flag clear
            // CMP3C: Compare 3 interrupt flag clear
            // CMP2C: Compare 2 interrupt flag clear
            // CMP1C: Compare 1 interrupt flag clear
    HRTIM1->sTimerxRegs[0].TIMxICR = 0;

        // TIMxDIER DMA interrupt enable register
            // DLYPRTDE: Delayed protection DMA request enable
            // RSTDE: Reset/roll-over DMA request enable
            // RSTx2DE: Output 2 reset DMA request enable
            // SETx2DE: Output 2 set DMA request enable
            // RSTx1DE: Output 1 reset DMA request enable
            // SETx1DE: Output 1 set DMA request enable
            // CPT2DE: Capture 2 DMA request enable
            // CPT1DE: Capture 1 DMA request enable
            // UPDDE: Update DMA request enable
            // REPDE: Repetition DMA request enable
            // CMP4DE: Compare 4 DMA request enable
            // CMP3DE: Compare 3 DMA request enable
            // CMP2DE: Compare 2 DMA request enable
            // CMP1DE: Compare 1 DMA request enable
            // DLYPRTIE: Delayed protection interrupt enable
            // RSTIE: Reset/roll-over interrupt enable
            // RSTx2IE: Output 2 reset interrupt enable
            // SETx2IE: Output 2 set interrupt enable
            // RSTx1IE: Output 1 reset interrupt enable
            // SETx1IE: Output 1 set interrupt enable
            // CPT2IE: Capture interrupt enable
            // CPT1IE: Capture interrupt enable
            // UPDIE: Update interrupt enable
            // REPIE: Repetition interrupt enable
            // CMP4IE: Compare 4 interrupt enable
            // CMP3IE: Compare 3 interrupt enable
            // CMP2IE: Compare 2 interrupt enable
            // CMP1IE: Compare 1 interrupt enable
    HRTIM1->sTimerxRegs[0].TIMxDIER = 0;

        // CNTxR counter register
            // CNTx[15:0]: Timer x counter value
    HRTIM1->sTimerxRegs[0].CNTxR = 0;

        // PERxR timer x period register
            // PERx[15:0]: Timer x period value
    HRTIM1->sTimerxRegs[0].CNTxR = 0;

        // REPxR timer x repetition register
            // REPx[7:0]: Timer x repetition period value
    HRTIM1->sTimerxRegs[0].REPxR = 0;

        // REPxR timer x repetition register
            // REPx[7:0]: Timer x repetition period value
    HRTIM1->sTimerxRegs[0].REPxR = 0;
    
        // CMP1xR timer x compare 1 register
            // CMP1x[15:0]: Timer x compare 1 value
            
    HRTIM1->sTimerxRegs[0].CMP1xR = 0;
            
        // CMP1CxR timer x compare 1 compound register
            // CREPx[7:0]: Timer x repetition value
            // CMP1x[15:0]: Timer x compare 1 value
    HRTIM1->sTimerxRegs[0].CMP1CxR = 0;
            
        // CMP2xR timer x compare 2 compound register
            // CMP2x[15:0]: Timer x compare 2 value
    HRTIM1->sTimerxRegs[0].CMP2xR = 0;
            
        // CMP3xR timer x compare 3 compound register
            // CMP3x[15:0]: Timer x compare 3 value
    HRTIM1->sTimerxRegs[0].CMP3xR = 0;
            
        // CPT1xR timer x capture 1 register
            // DIR: Timer x capture 1 direction status
            // CPT1x[15:0]: Timer x capture 1 value
    HRTIM1->sTimerxRegs[0].CPT1xR = 0;
            
        // CPT2xR timer x capture 2 register
            // DIR: Timer x capture 2 direction status
            // CPT1x[15:0]: Timer x capture 2 value
    HRTIM1->sTimerxRegs[0].CPT2xR = 0;
            
        // DTxR timer x deadtime register
            // DTFLKx: Deadtime falling lock
            // DTFSLKx: Deadtime falling sign lock
            // SDTFx: Sign deadtime falling value
            // DTFx[8:0]: Deadtime falling value
            // DTRLKx: Deadtime rising lock
            // DTRSLKx: Deadtime rising sign lock
            // DTPRSC[2:0]: Deadtime prescaler
            // SDTRx: Sign deadtime rising value
            // DTRx[8:0]: Deadtime rising value
    HRTIM1->sTimerxRegs[0].DTxR = 0;

        // SETx1R timer x output 1 set register
            // UPDATE: Registers update
            // EXTEVNT[11:1]: External events
            // TIMEVNT[9:1]: Timer events
            // MSTCMP[4:1]: Master compares
            // MSTPER: Master period
            // CMP[4:1]: Timer x compares
            // PER: Timer x period
            // RESYNC: Timer A resynchronization
            // SST: Software set trigger
    HRTIM1->sTimerxRegs[0].SETx1R = 0;

        // RSTx1R timer x output 1 reset register
            // UPDATE: Registers update
            // EXTEVNT[11:1]: External events
            // TIMEVNT[9:1]: Timer events
            // MSTCMP[4:1]: Master compares
            // MSTPER: Master period
            // CMP[4:1]: Timer x compares
            // PER: Timer x period
            // RESYNC: Timer A resynchronization
            // SST: Software set trigger
    HRTIM1->sTimerxRegs[0].RSTx1R = 0;

        // SETx2R timer x output 2 set register
            // UPDATE: Registers update
            // EXTEVNT[11:1]: External events
            // TIMEVNT[9:1]: Timer events
            // MSTCMP[4:1]: Master compares
            // MSTPER: Master period
            // CMP[4:1]: Timer x compares
            // PER: Timer x period
            // RESYNC: Timer A resynchronization
            // SST: Software set trigger            
    HRTIM1->sTimerxRegs[0].SETx2R = 0;
    
        // RSTx2R timer x output 2 reset register
            // UPDATE: Registers update
            // EXTEVNT[11:1]: External events
            // TIMEVNT[9:1]: Timer events
            // MSTCMP[4:1]: Master compares
            // MSTPER: Master period
            // CMP[4:1]: Timer x compares
            // PER: Timer x period
            // RESYNC: Timer A resynchronization
            // SST: Software set trigger
    HRTIM1->sTimerxRegs[0].RSTx2R = 0;

        // EEFxR1 timer x external event filtering register 1
            // EE5FLTR[3:0]: External event 5 filter
            // EE5LTCH: External event 5 latch
            // EE4FLTR[3:0]: External event 4 filter
            // EE4LTCH: External event 4 latch
            // EE3FLTR[3:0]: External event 3 filter
            // EE3LTCH: External event 3 latch
            // EE2FLTR[3:0]: External event 2 filter
            // EE2LTCH: External event 2 latch
            // EE1FLTR[3:0]: External event 1 filter
            // EE1LTCH: External event 1 latch
    HRTIM1->sTimerxRegs[0].EEFxR1 = 0;

        // EEFxR2 timer x external event filtering register 2
            // EE10FLTR[3:0]: External event 10 filter
            // EE10LTCH: External event 10 latch
            // EE9FLTR[3:0]: External event 9 filter
            // EE9LTCH: External event 9 latch
            // EE8FLTR[3:0]: External event 8 filter
            // EE8LTCH: External event 8 latch
            // EE7FLTR[3:0]: External event 7 filter
            // EE7LTCH: External event 7 latch
            // EE6FLTR[3:0]: External event 6 filter
            // EE16LTCH: External event 6 latch
    HRTIM1->sTimerxRegs[0].EEFxR2 = 0;

        // RSTxR timer x reset register
            // TIMFCPM2: Timer F compare 2
            // TIMECPM4: Timer E compare 4
            // TIMECMP2: Timer E compare 2
            // TIMECMP1: Timer E compare 1
            // TIMDCMP4: Timer D compare 4
            // TIMDCMP2: Timer D compare 2
            // TIMDCMP1: Timer D compare 1
            // TIMCCMP4: Timer C compare 4
            // TIMCCMP2: Timer C compare 2
            // TIMCCMP1: Timer C compare 1
            // TIMBCMP4: Timer B compare 4
            // TIMBCMP2: Timer B compare 2
            // TIMBCMP1: Timer B compare 1
            // EXTEVNT10: External event
            // EXTEVNT9: External event 9
            // EXTEVNT8: External event 8
            // EXTEVNT7: External event 7
            // EXTEVNT6: External event 6
            // EXTEVNT5: External event 5
            // EXTEVNT4: External event 4
            // EXTEVNT3: External event 3
            // EXTEVNT2: External event 2
            // EXTEVNT1: External event 1
            // MSTCMP4: Master compare 4
            // MSTCMP3: Master compare 3
            // MSTCMP2: Master compare 2
            // MSTCMP1: Master compare 1
            // MSTPER Master timer period
            // CMP4: Timer x compare 4 reset
            // CMP2: Timer x compare 2 reset
            // UPDT: Timer x update reset
            // TIMFCMP1: Timer F compare 1
    HRTIM1->sTimerxRegs[0].RSTxR = 0;

        // CHPxR timer x chopper register
            // STRPW[3:0]: Timer x start pulsewidth
            // CARDTY[2:0]: Timer x chopper duty cycle value
            // CARFRQ[3:0]: Timer x carrier frequency value
    HRTIM1->sTimerxRegs[0].CHPxR = 0;

        // CPT1xCR timer x capture 1 control register
            // 
    HRTIM1->sTimerxRegs[0].CPT1xCR = 0;

        // CPT2xCR timer x capture 2 control register
            //
    HRTIM1->sTimerxRegs[0].CPT2xCR = 0;

        // OUTxR timer x output register
            // DIDL2: Output 2 deadtime upon burst mode Idle entry
            // CHP2: Output 2 chopper enable
            // FAULT2[1:0]: Output 2 fault state
            // IDLES2: Output 2 idle state
            // IDLEM2: Output 2 idle mode
            // POL2: Output 2 polarity
            // BIAR: Balanced Idle Automatic Resume
            // DLYPRT[2:0]: Delayed protection
            // DLYPRTEN: Delayed protection enable
            // DTEN: Deadtime enable
            // DIDL1: Output 1 deadtime upon burst mode idle entry
            // CHP1: Output 1 chopper enable
            // FAULT1[1:0]: Output 1 fault state
            // IDLES1: Output 1 Idle State
            // IDLEM1: Output 1 Idle mode
            // POL1: Output 1 polarity
    HRTIM1->sTimerxRegs[0].OUTxR = 0;
    
        // FLTxR timer x fault register
            // FLTLCK: Fault sources lock
            // FLT6EN: Fault 6 enable
            // FLT5EN: Fault 5 enable
            // FLT4EN: Fault 4 enable
            // FLT3EN: Fault 3 enable
            // FLT2EN: Fault 2 enable
            // FLT1EN: Fault 1 enable
    HRTIM1->sTimerxRegs[0].FLTxR = 0;
            
        // TIMxCR2 timer x control register 2
            // TRGHLF: Triggered-half mode
            // GTCMP3: Greater than compare 3 PWM mode
            // GTCMP1: Greater than compare 1 PWM mode
            // FEROM[1:0]: Fault and event roll-over mode
            // BMROM[1:0]: Burst mode roll-over mode
            // ADROM[1:0]: ADC roll-over mode
            // OUTROM[1:0]: Output roll-over mode
            // ROM[1:0]: Roll-over mode
            // UDM: Up-Down mode
            // DCDR: Dual channel DAC reset trigger
            // DCDS Dual channel DAC Step trigger
            // DCDE: Dual channel DAC trigger enable
    HRTIM1->sTimerxRegs[0].TIMxCR2 = 0;
            
        // TIMxEEFR3 timer x external event filtering register 3
            // EEVACNT[5:0] External event A counter
            // EEVASEL[3:0]: External event A Selection
            // EEVARSTM: External event A reset mode
            // EEVACRES: External event A counter reset
            // EEVACE: External event A counter enable
    HRTIM1->sTimerxRegs[0].EEFxR3 = 0;

        // CR1 control register 1
            // AD4USRC[2:0]: ADC trigger 4 update source
            // AD3USRC[2:0]: ADC trigger 3 update source
            // AD2USRC[2:0]: ADC trigger 2 update source
            // AD1USRC[2:0]: ADC trigger 1 update source
                // 000: Master timer
                // 001: Timer A
                // 010: Timer B
                // 011: Timer C
                // 100: Timer D
                // 101: Timer E
                // 110: Timer F
                // 111: Reserved
            // TFUDIS: Timer F update disable
            // TEUDIS: Timer E update disable
            // TDUDIS: Timer D update disable
            // TCUDIS: Timer C update disable
            // TBUDIS: Timer B update disable
            // TAUDIS: Timer A update disable
            // MUDIS: Master update disable
    HRTIM1->sCommonRegs.CR1 = 0;
            
        // CR2 control register 2
            // SWPF: Swap timer F outputs
            // SWPE: Swap timer E outputs
            // SWPD: Swap timer D outputs
            // SWPC: Swap timer C outputs
            // SWPB: Swap timer B outputs
            // SWPA: Swap timer A outputs
            // TFRST: Timer F counter software reset
            // TERST: Timer E counter software reset
            // TDRST: Timer D counter software reset
            // TCRST: Timer C counter software reset
            // TBRST: Timer B counter software reset
            // TARST: Timer A counter software reset
            // MRST: Master counter software reset
            // TFSWU: Timer F software update
            // TESWU: Timer E software update
            // TDSWU: Timer D software update
            // TCSWU: Timer C software update
            // TBSWU: Timer B software update
            // TASWU: Timer A software update
            // MSWU: Master timer software update
    HRTIM1->sCommonRegs.CR2 = 0;
      
      // ISR interrupt status register
        // BMPER: Burst mode period interrupt flag
        // DLLRDY: DLL Ready Interrupt Flag
        // FLT6: Fault 6 interrupt flag
        // SYSFLT: System fault interrupt flag
        // FLT5: Fault 5 interrupt flag
        // FLT4: Fault 4 interrupt flag
        // FLT3: Fault 3 interrupt flag
        // FLT2: Fault 2 interrupt flag
        // FLT1: Fault 1 interrupt flag
    HRTIM1->sCommonRegs.ISR = 0;

      // ICR interrupt clear register
        // BMPERC: Burst mode period flag clear
        // DLLRDYC: DLL Ready Interrupt flag Clear
        // FLT6C: Fault 6 interrupt flag clear
        // SYSFLTC: System fault interrupt flag clear
        // FLT5C: Fault 5 interrupt flag clear
        // FLT4C: Fault 4 interrupt flag clear
        // FLT3C: Fault 3 interrupt flag clear
        // FLT2C: Fault 2 interrupt flag clear
        // FLT1C: Fault 1 interrupt flag clear
    HRTIM1->sCommonRegs.ICR = 0;

      // IER interrupt enable register
        // BMPERIE: Burst mode period interrupt enable
        // DLLRDYC: DLLRDYIE: DLL Ready Interrupt Enable
        // FLT6IE: Fault 6 interrupt enable
        // SYSFLTIE: System fault interrupt enable
        // FLT5IE: Fault 5 interrupt enable
        // FLT4IE: Fault 4 interrupt enable
        // FLT3IE: Fault 3 interrupt enable
        // FLT2IE: Fault 2 interrupt enable
        // FLT1IE: Fault 1 interrupt enable
    HRTIM1->sCommonRegs.IER = 0;
    
        // OENR output enable register
            // TF2OEN: Timer F output 2 enable
            // TF1OEN: Timer F output 1 enable
            // TE2OEN: Timer E output 2 enable
            // TE1OEN: Timer E output 1 enable
            // TD2OEN: Timer D output 2 enable
            // TD1OEN: Timer D output 1 enable
            // TC2OEN: Timer C output 2 enable
            // TC1OEN: Timer C output 1 enable
            // TB2OEN: Timer B output 2 enable
            // TB1OEN: Timer B output 1 enable
            // TA2OEN: Timer A output 2 enable
            // TA1OEN: Timer A output 1 enable
    HRTIM1->sCommonRegs.OENR = 0;
    
        // ODSR output disable status register r/o
            // TF2ODS: Timer F output 2 disable status
            // TF1ODS: Timer F output 1 disable status
            // TE2ODS: Timer E output 2 disable status
            // TE1ODS: Timer E output 1 disable status
            // TD2ODS: Timer D output 2 disable status
            // TD1ODS: Timer D output 1 disable status
            // TC2ODS: Timer C output 2 disable status
            // TC1ODS: Timer C output 1 disable status
            // TB2ODS: Timer B output 2 disable status
            // TB1ODS: Timer B output 1 disable status
            // TA2ODS: Timer A output 2 disable status
            // TA1ODS: Timer A output 1 disable status

        // BMCR burst mode control register
            // BMSTAT: Burst mode status
            // TFBM: Timer F burst mode
            // TEBM: Timer E burst mode
            // TDBM: Timer D burst mode
            // TCBM: Timer C burst mode
            // TBBM: Timer B burst mode
            // TABM: Timer A burst mode
            // MTBM: Master timer burst mode
            // BMPREN: Burst mode preload enable
            // BMPRSC[3:0]: Burst mode prescaler
            // BMCLK[3:0]: Burst mode clock source
            // BMOM: Burst mode operating mode
            // BME: Burst mode enable
    HRTIM1->sCommonRegs.BMCR = 0;

        // BMTRGR burst mode trigger register
            // OCHPEV: On-chip event
            // EEV8: External event 8
            // EEV7: External event 7
            // TDEEV8: Timer D period following external event 8
            // TAEEV7: Timer A period following external event 7
            // TECMP2: Timer E compare 2 event
            // TECMP1: Timer E compare 1 event
            // TEREP: Timer E repetition
            // TFCMP1: Timer F compare 1 event
            // TDCMP2: Timer D compare 2 event
            // TFREP: Timer F repetition
            // TDREP: Timer D repetition
            // TDRST: Timer D reset or roll-over
            // TFRST: Timer F reset
            // TCCMP1: Timer C compare 1 event
            // TCREP: Timer C repetition
            // TCRST: Timer C reset or roll-over
            // TBCMP2: Timer B compare 2 event
            // TBCMP1: Timer B compare 1 event
            // TBREP: Timer B repetition
            // TBRST: Timer B reset or roll-over
            // TACMP2: Timer A compare 2 event
            // TACMP1: Timer A compare 1 event
            // TAREP: Timer A repetition
            // TARST: Timer A reset or roll-over
            // MSTCMP4: Master compare 4
            // MSTCMP3: Master compare 3
            // MSTCMP2: Master compare 2
            // MSTCMP1: Master compare 1
            // MSTREP: Master repetition
            // MSTRST: Master reset or roll-over
            // SW: Software start
    HRTIM1->sCommonRegs.BMTRGR = 0;

        // BMCMPR burst mode compare register
            // BMCMP[15:0]: Burst mode compare value
    HRTIM1->sCommonRegs.BMCMPR = 0;

        // BMPER burst mode period register
            // BMPER[15:0]: Burst mode period
    HRTIM1->sCommonRegs.BMPER = 0;

        // EECR1 timer external event control register 1
            // EE5FAST: External event 5 fast mode
            // EE5SNS[1:0]: External event 5 sensitivity
            // EE5POL: External event 5 polarity
            // EE5SRC[1:0]: External event 5 source
            // EE4FAST: External event 4 fast mode
            // EE4SNS[1:0]: External event 4 sensitivity
            // EE4POL: External event 4 polarity
            // EE4SRC[1:0]: External event 4 source
            // EE3FAST: External event 3 fast mode
            // EE3SNS[1:0]: External event 3 sensitivity
            // EE3POL: External event 3 polarity
            // EE3SRC[1:0]: External event 3 source
            // EE2FAST: External event 2 fast mode
            // EE2SNS[1:0]: External event 2 sensitivity
            // EE2POL: External event 2 polarity
            // EE2SRC[1:0]: External event 2 source
            // EE1FAST: External event 1 fast mode
            // EE1SNS[1:0]: External event 1 sensitivity
            // EE1POL: External event 1 polarity
            // EE1SRC[1:0]: External event 1 source
    HRTIM1->sCommonRegs.EECR1 = 0;

        // EECR2 timer external event control register 2
            // EE10SNS[1:0]: External event 10 sensitivity
            // EE10POL: External event 10 polarity
            // EE10SRC[1:0]: External event 10 source
            // EE9SNS[1:0]: External event 9 sensitivity
            // EE9POL: External event 9 polarity
            // EE9SRC[1:0]: External event 9 source
            // EE8SNS[1:0]: External event 8 sensitivity
            // EE8POL: External event 8 polarity
            // EE8SRC[1:0]: External event 8 source
            // EE7SNS[1:0]: External event 7 sensitivity
            // EE7POL: External event 7 polarity
            // EE7SRC[1:0]: External event 7 source
            // EE6SNS[1:0]: External event 6 sensitivity
            // EE6POL: External event 6 polarity
            // EE6SRC[1:0]: External event 6 source
    HRTIM1->sCommonRegs.EECR2 = 0;

        // EECR3 timer external event control register 3
            // EEVSD[1:0]: External event sampling clock division
            // EE10F[3:0]: External event 10 filter
            // EE9F[3:0]: External event 9 filter
            // EE8F[3:0]: External event 8 filter
            // EE7F[3:0]: External event 7 filter
            // EE6F[3:0]: External event 6 filter
    HRTIM1->sCommonRegs.EECR3 = 0;

        // ADC1R ADC trigger 1 register
            // See ADC3R
    HRTIM1->sCommonRegs.ADC1R = 0;
    
        // ADC2R ADC trigger 2 register
            // ADC4R
    HRTIM1->sCommonRegs.ADC2R = 0;
    
        // ADC3R ADC trigger 3 register
            // ADC3TEPER: ADC trigger 3 on timer E period
            // ADC3TEC4: ADC trigger 3 on timer E compare 4
            // ADC3TEC3: ADC trigger 3 on timer E compare 3
            // ADC3TFRST: ADC trigger 3 on timer F reset and counter roll-over
            // ADC3TDPER: ADC trigger 3 on timer D period
            // ADC3TDC4: ADC trigger 3 on timer D compare 4
            // ADC3TDC3: ADC trigger 3 on timer D compare 3
            // ADC3TFPER: ADC trigger 3 on timer F period
            // ADC3TCPER: ADC trigger 3 on timer C period
            // ADC3TCC4: ADC trigger 3 on timer C compare 4
            // ADC3TCC3: ADC trigger 3 on timer C compare 3
            // ADC3TFC4: ADC trigger 3 on timer F compare 4
            // ADC3TBRST: ADC trigger 3 on timer B reset and counter roll-over
            // ADC3TBPER: ADC trigger 3 on timer B period
            // ADC3TBC4: ADC trigger 3 on timer B compare 4
            // ADC3TBC3: ADC trigger 3 on timer B compare 3
            // ADC3TFC3: ADC trigger 3 on timer F compare 3
            // ADC3TARST: ADC trigger 3 on timer A reset and counter roll-over
            // ADC3TAPER: ADC trigger 3 on timer A period
            // ADC3TAC4: ADC trigger 3 on timer A compare 4
            // ADC3TAC3: ADC trigger 3 on timer A compare 3
            // ADC3TFC2: ADC trigger 3 on timer F compare 2
            // ADC3EEV5: ADC trigger 3 on external event 5(1)
            // ADC3EEV4: ADC trigger 3 on external event 4(1)
            // ADC3EEV3: ADC trigger 3 on external event 3(1)
            // ADC3EEV2: ADC trigger 3 on external event 2(1)
            // ADC3EEV1: ADC trigger 3 on external event 1(1)
            // ADC3MPER: ADC trigger 3 on master period
            // ADC3MC4: ADC trigger 3 on master compare 4
            // ADC3MC3: ADC trigger 3 on master compare 3
            // ADC3MC2: ADC trigger 3 on master compare 2
            // ADC3MC1: ADC trigger 3 on master compare 1
    HRTIM1->sCommonRegs.ADC3R = 0;
    
        // ADC4R ADC trigger 4 register
            // ADC4TERST: ADC trigger 4 on timer E reset and counter roll-over
            // ADC4TEC4: ADC trigger 4 on timer E compare 4
            // ADC4TEC3: ADC trigger 4 on timer E compare 3
            // ADC4TEC2: ADC trigger 4 on timer E compare 2
            // ADC4TDRST: ADC trigger 4 on timer D reset and counter roll-over
            // ADC4TDPER: ADC trigger 4 on timer D period
            // ADC4TDC4: ADC trigger 4 on timer D compare 4
            // ADC4TFPER: ADC trigger 4 on timer F period
            // ADC4TDC2: ADC trigger 2 on timer D compare 2
            // ADC4TCRST: ADC trigger 4 on timer C reset and counter roll-over
            // ADC4TCPER: ADC trigger 4 on timer C period
            // ADC4TCC4: ADC trigger 4 on timer C compare 4
            // ADC4TFC4: ADC trigger 4 on timer F compare 4
            // ADC4TCC2: ADC trigger 4 on timer C compare 2
            // ADC4TBPER: ADC trigger 4 on timer B period
            // ADC4TBC4: ADC trigger 4 on timer B compare 4
            // ADC4TFC3: ADC trigger 4 on timer F compare 3
            // ADC4TBC2: ADC trigger 4 on timer B compare 2
            // ADC4TAPER: ADC trigger 4 on timer A period
            // ADC4TAC4: ADC trigger 4 on timer A compare 4
            // ADC4TFC2: ADC trigger 4 on timer F compare 2
            // ADC4TAC2: ADC trigger 4 on timer A compare 2
            // ADC4EEV10: ADC trigger 4 on external event 10(1)
            // ADC4EEV9: ADC trigger 4 on external event 9(1)
            // ADC4EEV8: ADC trigger 4 on external event 8(1)
            // ADC4EEV7: ADC trigger 4 on external event 7(1)
            // ADC4EEV6: ADC trigger 4 on external event 6(1)
            // ADC4MPER: ADC trigger 4 on master period
            // ADC4MC4: ADC trigger 4 on master compare 4
            // ADC4MC3: ADC trigger 4 on master compare 3
            // ADC4MC2: ADC trigger 4 on master compare 2
            // ADC4MC1: ADC trigger 4 on master compare 1
    HRTIM1->sCommonRegs.ADC4R = 0;

        // DLLCR DLL control register
            // CALRTE[1:0]: DLL Calibration rate
            // CALEN: DLL Calibration Enable
            // CAL: DLL Calibration Start
    HRTIM1->sCommonRegs.ADC4R = 0;

        // FLTINR1 fault input register 1
            // FLT4LCK: Fault 4 lock
            // FLT4F[3:0]: Fault 4 filter
            // FLT4SRC[0]: Fault 4 source bit 0
            // FLT4P: Fault 4 polarity
            // FLT4E: Fault 4 enable
            // FLT3LCK: Fault 3 lock
            // FLT3F[3:0]: Fault 3 filter
            // FLT3SRC[0]: Fault 3 source bit 0
            // FLT3P: Fault 3 polarity
            // FLT3E: Fault 3 enable
            // FLT2LCK: Fault 2 lock
            // FLT2F[3:0]: Fault 2 filter
            // FLT2SRC[0]: Fault 2 source bit 0
            // FLT2P: Fault 2 polarity
            // FLT2E: Fault 2 enable
            // FLT1LCK: Fault 1 lock
            // FLT1F[3:0]: Fault 1 filter
            // FLT1SRC[0]: Fault 1 source bit 0
            // FLT1P: Fault 1 polarity
            // FLT1E: Fault 1 enable
    HRTIM1->sCommonRegs.FLTINR1 = 0;

        // FLTINR2 fault input register 2
            // FLTSD[1:0]: Fault sampling clock division
            // FLT6SRC[1]: Fault 6 source bit 1
            // FLT5SRC[1]: Fault 5 source bit 1
            // FLT4SRC[1]: Fault 4 source bit 1
            // FLT3SRC[1]: Fault 3 source bit 1
            // FLT2SRC[1]: Fault 2 source bit 1
            // FLT1SRC[1]: Fault 1 source bit 1
            // FLT6LCK: Fault 6 lock
            // FLT6F[3:0]: Fault 6 filter
            // FLT6SRC[0]: Fault 6 source bit 0
            // FLT6P: Fault 6 polarity
            // FLT6E: Fault 6 enable
            // FLT5F[3:0]: Fault 5 filter
            // FLT5SRC[0]: Fault 5 source bit 0
            // FLT5P: Fault 5 polarity
            // FLT5E: Fault 5 enable
    HRTIM1->sCommonRegs.FLTINR2 = 0;

        // BDMUPR burst DMA master timer update register
            // MCMP4: MCMP4R register update enable
            // MCMP3: MCMP3R register update enable
            // MCMP2: MCMP2R register update enable
            // MCMP1: MCMP1R register update enable
            // MREP: MREP register update enable
            // MPER: MPER register update enable
            // MCNT: MCNTR register update enable
            // MDIER: MDIER register update enable
            // MICR: MICR register update enable
            // MCR: MCR register update enable
    HRTIM1->sCommonRegs.BDMUPR = 0;
    
        // BDTxUPR burst DMA timer x update register
            // TIMxEEFR3: HRTIM_EEFxR3 register update enable
            // TIMxCR2: HRTIM_TIMxCR2 register update enable
            // TIMxFLTR: HRTIM_FLTxR register update enable
            // TIMxOUTR: HRTIM_OUTxR register update enable
            // TIMxCHPR: HRTIM_CHPxR register update enable
            // TIMxRSTR: HRTIM_RSTxR register update enable
            // TIMxEEFR2: HRTIM_EEFxR2 register update enable
            // TIMxEEFR1: HRTIM_EEFxR1 register update enable
            // TIMxRST2R: HRTIM_RST2xR register update enable
            // TIMxSET2R: HRTIM_SET2xR register update enable
            // TIMxRST1R: HRTIM_RST1xR register update enable
            // TIMxSET1R: HRTIM_SET1xR register update enable
            // TIMxDTR: HRTIM_DTxR register update enable
            // TIMxCMP4: HRTIM_CMP4xR register update enable
            // TIMxCMP3: HRTIM_CMP3xR register update enable
            // TIMxCMP2: HRTIM_CMP2xR register update enable
            // TIMxCMP1: HRTIM_CMP1xR register update enable
            // TIMxREP: HRTIM_REPxR register update enable
            // TIMxPER: HRTIM_PERxR register update enable
            // TIMxCNT: HRTIM_CNTxR register update enable
            // TIMxDIER: HRTIM_TIMxDIER register update enable
            // TIMxICR: HRTIM_TIMxICR register update enable
            // TIMxCR: HRTIM_TIMxCR register update enable
    HRTIM1->sCommonRegs.BDTAUPR = 0;
    HRTIM1->sCommonRegs.BDTBUPR = 0;
    HRTIM1->sCommonRegs.BDTCUPR = 0;
    HRTIM1->sCommonRegs.BDTDUPR = 0;
    HRTIM1->sCommonRegs.BDTEUPR = 0;
    HRTIM1->sCommonRegs.BDTFUPR = 0;
    
        // BDMADR burst DMA data register
            // BDMADR[31:0]: Burst DMA data register
    HRTIM1->sCommonRegs.BDMADR = 0;
    
        // ADCER ADC extended trigger register
            // ADC10TRG[4:0]: ADC trigger 10 selection
            // ADC9TRG[4:0]: ADC trigger 9 selection
            // ADC8TRG[4:0]: ADC trigger 8 selection
            // ADC7TRG[4:0]: ADC trigger 7 selection
            // ADC6TRG[4:0]: ADC trigger 6 selection
            // ADC5TRG[4:0]: ADC trigger 5 selection
    HRTIM1->sCommonRegs.ADCER = 0;
    
        // ADCUR ADC trigger update register
            // AD10USRC[2:0]: ADC trigger 10 update source
            // AD9USRC[2:0]: ADC trigger 9 update source
            // AD8USRC[2:0]: ADC trigger 8 update source
            // AD7USRC[2:0]: ADC trigger 7 update source
            // AD6USRC[2:0]: ADC trigger 6 update source
            // AD5USRC[2:0]: ADC trigger 5 update source
    HRTIM1->sCommonRegs.ADCUR = 0;
    
        // ADCPS1 ADC post scaler register 1
            // ADC5PSC[4:0]: ADC 5 post scaler
            // ADC4PSC[4:0]: ADC 4 post scaler
            // ADC3PSC[4:0]: ADC 3 post scaler
            // ADC2PSC[4:0]: ADC 2 post scaler
            // ADC1PSC[4:0]: ADC 1 post scaler
    HRTIM1->sCommonRegs.ADCPS1 = 0;
    
        // ADCPS2 ADC post scaler register 2
            // ADC10PSC[4:0]: ADC 10 post scaler
            // ADC9PSC[4:0]: ADC 9 post scaler
            // ADC8PSC[4:0]: ADC 8 post scaler
            // ADC7PSC[4:0]: ADC 7 post scaler
            // ADC6PSC[4:0]: ADC 6 post scaler
    HRTIM1->sCommonRegs.ADCPS2 = 0;
    
        // FLTINR3 fault input register 3
            // FLT4RSTM: Fault 4 reset mode
            // FLT4CRES: Fault 4 counter reset
            // FLT4CNT[3:0]: Fault 4 counter
            // FLT4BLKS: Fault 4 blanking source
            // FLT4BLKE: Fault 4 blanking enable
            // FLT3RSTM: Fault 3 reset mode
            // FLT3CRES: Fault 3 counter reset
            // FLT3CNT[3:0]: Fault 3 counter
            // FLT3BLKS: Fault 3 blanking source
            // FLT3BLKE: Fault 3 blanking enable
            // FLT2RSTM: Fault 2 reset mode
            // FLT2CRES: Fault 2 counter reset
            // FLT2CNT[3:0]: Fault 2 counter
            // FLT2BLKS: Fault 2 blanking source
            // FLT2BLKE: Fault 2 blanking enable
            // FLT1RSTM: Fault 1 reset mode
            // FLT1CRES: Fault 1 counter reset
            // FLT1CNT[3:0]: Fault 1 counter
            // FLT1BLKS: Fault 1 blanking source
            // FLT1BLKE: Fault 1 blanking enable
    HRTIM1->sCommonRegs.FLTINR3 = 0;
    
        // FLTINR4 fault input register 4
            // FLT6RSTM: Fault 6 reset mode
            // FLT6CRES: Fault 6 counter reset
            // FLT6CNT[3:0]: Fault 6 counter
            // FLT6BLKS: Fault 6 blanking source
            // FLT6BLKE: Fault 6 blanking enable
            // FLT5RSTM: Fault 5 reset mode
            // FLT5CRES: Fault 5 counter reset
            // FLT5CNT[3:0]: Fault 5 counter
            // FLT5BLKS: Fault 5 blanking source
            // FLT5BLKE: Fault 5 blanking enable
    HRTIM1->sCommonRegs.FLTINR4 = 0;
    }

// ETR  PB6 PC3
// IN1  PB5 PC0
// IN2  PB7 PC2
// OUT  PB1 PC1
// LPTIM 
void LPTIM1_Init(void)
    {
    RCC->APB1ENR1 |= RCC_APB1ENR1_LPTIM1EN;
    
        // ISR interrupt and status register
            // DOWN: Counter direction change up to down
            // UP: Counter direction change down to up
            // ARROK: Autoreload register update OK
            // CMPOK: Compare register update OK
            // EXTTRIG: External trigger edge event
            // ARRM: Autoreload match
            // CMPM: Compare match
    LPTIM1->ISR = 0;
    
        // ICR interrupt clear register
            // DOWNCF: Direction change to down clear flag
            // UPCF: Direction change to UP clear flag
            // ARROKCF: Autoreload register update OK clear flag
            // CMPOKCF: Compare register update OK clear flag
            // EXTTRIGCF: External trigger valid edge clear flag
            // ARRMCF: Autoreload match clear flag
            // CMPMCF: Compare match clear flag
    LPTIM1->ICR = 0;
    
        // IER interrupt enable register
            // DOWNIE: Direction change to down Interrupt Enable
            // UPIE: Direction change to UP Interrupt Enable
            // ARROKIE: Autoreload register update OK Interrupt Enable
            // CMPOKIE: Compare register update OK Interrupt Enable
            // EXTTRIGIE: External trigger valid edge Interrupt Enable
            // ARRMIE: Autoreload match Interrupt Enable
            // CMPMIE: Compare match Interrupt Enable
    LPTIM1->ICR = 0;
    
        // CFGR configuration register
            // ENC: Encoder mode enable
            // COUNTMODE: counter mode enabled
            // PRELOAD: Registers update mode
            // WAVPOL: Waveform shape polarity
            // 20 WAVE: Waveform shape
            // TIMOUT: Timeout enable
            // TRIGEN[1:0]: Trigger enable and polarity
            // TRIGSEL[3:0]: Trigger selector
            // PRESC[2:0]: Clock prescaler
            // Reserved, must be kept at reset value.
            // TRGFLT[1:0]: Configurable digital filter for trigger
            // CKFLT[1:0]: Configurable digital filter for external clock
            // CKPOL[1:0]: Clock Polarity
            // CKSEL: Clock selector
    LPTIM1->CFGR = 0;
    
        // CR control register
            // RSTARE: Reset after read enable
            // COUNTRST: Counter reset
            // CNTSTRT: Timer start in Continuous mode
            // SNGSTRT: LPTIM start in Single mode
            // ENABLE: LPTIM enable
    LPTIM1->CR = 0;
    
        // CMP compare register
            // CMP[15:0]: Compare value
    LPTIM1->CMP = 0;
    
        // ARR autoreload register
            // ARR[15:0]: Auto reload value
    LPTIM1->ARR = 0;
    
        // CNT counter register
            // CNT[15:0]: Counter value
    LPTIM1->CNT = 0;
    
        // OR option register
            // IN2[2:1]: LPTimer input 2 remap extension
            // IN1[2:1]: LPTimer input 1 remap extension
            // IN2[0]: LPTimer input 2 remap
            // IN1[0]: LPTimer input 1 remap
    LPTIM1->OR = 0;
    }

// BKIN  PA6  PA14 PA15 PB8 PB10 PB12 PC13 PE15
// BKIN2 PA11 PC3  PE14
// CH1   PA8  PB9  PC0  PE9
// CH1N  PA7  PA11 PB13 PC13 PE8
// CH2   PA9  PC1  PE11
// CH2N  PA12 PB0  PB14 PE10
// CH3   PA10 PC2  PE13
// CH3N  PB15 PB1  PE12
// CH4   PA11 PC4  PE14
// CH4N  PC5  PE15
// ETR   PA12 PE7
// TIM1 0x40012C00
void TIM1_Init(void)
  {
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  TIM1->CR1 = 0x0;
  TIM1->CR2 = 0x0;
  TIM1->SMCR = 0x0;
  TIM1->DIER |= TIM_DIER_UIE;    // Enable the Interrupt
  TIM1->SR &= ~TIM_SR_UIF;       // Clear the Interrupt Status
  TIM1->EGR = 0x0;
  TIM1->CCMR1 =  0x6868; // 0x6868
  TIM1->CCMR2 = 0x68;
  TIM1->CCER = 0x111;
  TIM1->PSC = 3;
  TIM1->ARR = 999;
  TIM1->RCR = 0x0;
  TIM1->CCR1 = 500;
  TIM1->CCR2 = 375;
  TIM1->CCR3 = 250;
  TIM1->CCR4 = 0x0;
  TIM1->BDTR = 0x200A000; // TIM_BDTR_BK2P | TIM_BDTR_MOE | TIM_BDTR_BKP
  TIM1->CCR5 = 0x0;
  TIM1->CCR6 = 0x0; 
  TIM1->CCMR3 = 0x0;
  TIM1->DTR2 = 0x0;
  TIM1->ECR = 0x0;
  TIM1->TISEL = 0x0;
  TIM1->AF1 = TIM_BDTR_BK2P; // 0x1
  TIM1->AF2 = TIM_BDTR_BK2P; // 0x1
  TIM1->DCR = 0x0;
  TIM1->DMAR = 0x1;
  TIM1->CR1 |= TIM_CR1_CEN;       // enable TIM1
  }
 
// CH1 PA0  PA5  PA15 PD3
// CH2 PA1  PB3  PD4
// CH3 PA2  PB10 PD7
// CH4 PA3  PA9  PB11 PD6
// ETR PA5  PA10 PA0  PA15 PD3
// TIM2 0x40000000
void TIM2_Init(void)
  {
  RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN; // Enable the APB clock FOR TIM2
  TIM2->PSC = 8499;
  TIM2->ARR = 498;
  TIM2->DIER |= TIM_DIER_UIE; // Enable the Interrupt
  TIM2->SR &= ~TIM_SR_UIF;    // Clear the Interrupt Status
  NVIC_EnableIRQ(TIM2_IRQn);  // Enable NVIC Interrupt
  TIM2->CR1 = TIM_CR1_CEN;    // enable TIM2
  }
 
// CH1  PA6  PB4  PC6  PE2
// CH2  PA4  PA7  PB5  PC7  PE3
// CH3  PB0  PC8  PE4
// CH4  PB1  PB7  PC9  PE5
// ETR  PB3  PD2
// TIM3 0x40000400
void TIM3_Init(void)
  {
  RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN; // Enable the APB clock FOR TIM3
  TIM3->PSC = 8499;
  TIM3->ARR = 499;
  TIM3->DIER |= TIM_DIER_UIE; // Enable the Interrupt
  TIM3->SR &= ~TIM_SR_UIF;    // Clear the Interrupt Status
  NVIC_EnableIRQ(TIM3_IRQn);  // Enable NVIC Interrupt
  TIM3->CR1 = TIM_CR1_CEN;    // enable TIM3
  }

// CH1  PA11 PB6  PD12
// CH2  PA12 PB7  PD13
// CH3  PA13 PB8  PD14
// CH4  PB9  PD15 PF6
// ETR  PA8  PB3
// TIM4 0x40000800
void TIM4_Init(void)
  {
  RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN; // Enable the APB clock FOR TIM4
  TIM4->CR1 = 0x0; // 
  TIM4->CR2 = 0;
  TIM4->SMCR = 0;
  TIM4->DIER = TIM_DIER_CC1IE;
  TIM4->EGR = 0;
  TIM4->CCMR1 = 0x68; 
  TIM4->CCMR2 = 0x0; 
  TIM4->CCER = TIM_CCER_CC1E;
  TIM4->PSC = 169; 
  TIM4->ARR = 0x3E7; 
  TIM4->CCR1 = 0x237;
  TIM4->CCR2 = 0x0;
  TIM4->CCR3 = 0x0;
  TIM4->CCR4 = 0x0;
  TIM4->ECR = 0x0;
  TIM4->TISEL = 0x0;
  TIM4->AF1 = 0x0;
  TIM4->AF2 = 0x0;
  TIM4->DCR = 0x0;
  TIM4->DMAR = 0x0;
  NVIC_EnableIRQ(TIM4_IRQn); // Enable NVIC Interrupt
  TIM4->CR1 = TIM_CR1_CEN;
  }

// CH1  PA0  PB2  PF6
// CH2  PA1  PC12 PF7
// CH3  PA2  PE8  PF8
// CH4  PA3  PE9  PF9
// ETR  PB12 PD11 PF6
// TIM5 0x40000C00
void TIM5_Init(void)
  {
  RCC->APB1ENR1 |= RCC_APB1ENR1_TIM5EN;
  TIM5->PSC = 31;             // pre-scale value
  TIM5->ARR = 15989;          // timer reload
  TIM5->DIER |= TIM_DIER_UIE; // Enable the Interrupt
  TIM5->SR &= ~TIM_SR_UIF;    // Clear the Interrupt Status
  NVIC_EnableIRQ(TIM5_IRQn);  // Enable NVIC Interrupt
  TIM5->CR1 |= TIM_CR1_CEN;   // enable TIM5
  }

// BKIN  PA0  PA6  PA10 PB7 PD2
// BKIN2 PB6  PC9  PD1
// CH1   PA15 PB6  PC6
// CH1N  PA7  PB3  PC10 PC12
// CH2   PA14 PB8  PC7
// CH2N  PA0  PB0  PB4  PC11
// CH3   PB9  PC8
// CH3N  PA1  PB1  PB5  PC12
// CH4   PC9  PD1
// CH4N  PD0
// ETR   PA0  PB6
// TIM8 0x40013400
void TIM8_Init(void)
    {
    RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
    }

// BKIN PA9  PC5
// CH1  PA2  PB14 PF9
// CH1N PA1  PB15 PG9
// CH2  PA3  PB15 PF10
// TIM15 0x40014000
void TIM15_Init(void)
    {
    RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
    }

// BKIN PB5
// CH1  PA6  PA12 PB4 PB8
// CH1N PA13 PB6
// TIM16 0x40014400
void TIM16_Init(void)
    {
    RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
    }

// BKIN PA10 PB4
// CH1  PA7  PB5  PB9  PE1
// CH1N PB7
// TIM17 0x40014800
void TIM17_Init(void)
    {
    RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
    }

// BKIN  PF7  PF9  PG3  PG6
// BKIN2 PF8  PF10
// CH1   PB2  PE2  PF12
// CH1N  PE4  PF4  PG0
// CH2   PC2  PE3  PF13
// CH2N  PE5  PF5  PG1
// CH3   PC8  PF2  PF14
// CH3N  PE6  PG2
// CH4   PE1  PF3  PF15
// CH4N  PE0  PG4
// ETR   PE0  PF11 PG5
// TIM20 0x40015000
void TIM20_Init(void)
  {
  RCC->APB2ENR |= RCC_APB2ENR_TIM20EN;
  TIM20->PSC = 31;
  TIM20->ARR = 15999;
  TIM20->DIER |= TIM_DIER_UIE;    // Enable the Interrupt
  TIM20->SR &= ~TIM_SR_UIF;       // Clear the Interrupt Status
  NVIC_EnableIRQ(TIM20_UP_IRQn);  // Enable NVIC Interrupt
  TIM20->CR1 |= TIM_CR1_CEN;      // enable TIM3
  }
  
