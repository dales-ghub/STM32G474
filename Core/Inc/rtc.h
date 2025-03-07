#include <stdio.h>
#include "main.h"
#include "stm32g4xx_hal.h"

typedef struct
    {
    int error;
    int yd;
    int yu;
    int md;
    int mu; 
    int dd; 
    int du;
    int dow;
    }  DATE_VAL;
  
typedef struct
    {
    int error;
    int hd;
    int hu;
    int md;
    int mu; 
    int sd; 
    int su;
    }  TIME_VAL;
  
void dateVal(char*s, DATE_VAL * date_val);
void RTC_Init(void);
void setAlarmA(TIME_VAL * time_val);
void setAlarmB(TIME_VAL * time_val);
void SetRTCdate(DATE_VAL * date_val);
void SetRTCtime(TIME_VAL * time_val);
void timeVal(char*s, TIME_VAL * time_val);

// RTC_TR time register [0x00]
    // PM: AM/PM notation
    // HT[1:0]: Hour tens in BCD format
    // HU[3:0]: Hour units in BCD format
    // MNT[2:0]: Minute tens in BCD format
    // MNU[3:0]: Minute units in BCD format
    // ST[2:0]: Second tens in BCD format
    // SU[3:0]: Second units in BCD format
// RTC_DR date register [0x04]
    // YT[3:0]: Year tens in BCD format
    // YU[3:0]: Year units in BCD format
    // WDU[2:0]: Week day units
        // 001: Monday
        // 111: Sunday
    // MT: Month tens in BCD format
    // MU[3:0]: Month units in BCD format
    // DT[1:0]: Date tens in BCD format
    // DU[3:0]: Date units in BCD format
// RTC_SSR sub second register [0x08]
    // SS[15:0]: Sub second value
// RTC_ICSR initialization control and status register [0x0C]
    // RECALPF: Recalibration pending Flag
    // INIT: Initialization mode
    // INITF: Initialization flag
    // RSF: Registers synchronization flag
    // INITS: Initialization status flag
    // SHPF: Shift operation pending
    // WUTWF: Wakeup timer write flag
    // ALRBWF: Alarm B write flag
    // ALRAWF: Alarm A write flag
// RTC_PRER prescaler register [0x10]
    // PREDIV_A[6:0]: Asynchronous prescaler factor
    // PREDIV_S[14:0]: Synchronous prescaler factor
// RTC_WUTR wakeup timer register [0x14]
    // WUT[15:0]: Wakeup auto-reload value bits
// RTC_CR control register [0x18]
    // OUT2EN: RTC_OUT2 output enable
    // TAMPALRM_TYPE: TAMPALRM output type
    // TAMPALRM_PU: TAMPALRM pull-up enable
    // TAMPOE: Tamper detection output enable on TAMPALRM
    // TAMPTS: Activate timestamp on tamper detection event
    // ITSE: timestamp on internal event enable
    // COE: Calibration output enable
    // OSEL[1:0]: Output selection
    // POL: Output polarity
    // COSEL: Calibration output selection
    // BKP: Backup
    // SUB1H: Subtract 1 hour (winter time change)
    // ADD1H: Add 1 hour (summer time change)
    // TSIE: Timestamp interrupt enable
    // WUTIE: Wakeup timer interrupt enable
    // ALRBIE: Alarm B interrupt enable
    // ALRAIE: Alarm A interrupt enable
    // TSE: timestamp enable
    // WUTE: Wakeup timer enable
    // ALRBE: Alarm B enable
    // ALRAE: Alarm A enable
    // FMT: Hour format
    // REFCKON: RTC_REFIN reference clock detection enable (50 or 60 Hz)
    // TSEDGE: Timestamp event active edge
    // WUCKSEL[2:0]: ck_wut wakeup clock selection
// RTC_WPR write protection register [0x24]
    // KEY[7:0]: Write protection key
// RTC_CALR calibration register [0x28]
    // CALP: Increase frequency of RTC by 488.5 ppm
    // CALW8: Use an 8-second calibration cycle period
    // CALW16: Use a 16-second calibration cycle period
    // CALM[8:0]: Calibration minus
// RTC_SHIFTR shift control register [0x2C]
    // ADD1S: Add one second
    // SUBFS[14:0]: Subtract a fraction of a second
// RTC_TSTR timestamp time register [0x30]
    // PM: AM/PM notation
    // HT[1:0]: Hour tens in BCD format.
    // HU[3:0]: Hour units in BCD format.
    // MNT[2:0]: Minute tens in BCD format.
    // MNU[3:0]: Minute units in BCD format.
    // ST[2:0]: Second tens in BCD format.
    // SU[3:0]: Second units in BCD format.
// RTC_TSDR timestamp date register [0x34]
    // WDU[2:0]: Week day units
    // MT: Month tens in BCD format
    // MU[3:0]: Month units in BCD format
    // DT[1:0]: Date tens in BCD format
    // DU[3:0]: Date units in BCD format
// RTC_TSSSR timestamp sub second register [0x38]
    // SS[15:0]: Sub second value
// RTC_ALRMAR alarm A register [0x40]
    // MSK4: Alarm A date mask
    // WDSEL: Week day selection
    // DT[1:0]: Date tens in BCD format
    // DU[3:0]: Date units or day in BCD format
    // MSK3: Alarm A hours mask
    // PM: AM/PM notation
    // HT[1:0]: Hour tens in BCD format
    // HU[3:0]: Hour units in BCD format
    // MNT[2:0]: Minute tens in BCD format
    // MNU[3:0]: Minute units in BCD format
    // MSK1: Alarm A seconds mask
    // ST[2:0]: Second tens in BCD format.
    // SU[3:0]: Second units in BCD format
// RTC_ALRMASSR alarm A sub second register [0x44]
    // MASKSS[3:0]: Mask the most-significant bits starting at this bit
    // SS[14:0]: Sub seconds value
// RTC_ALRMBR alarm B register [0x48]
    // MSK4: Alarm B date mask
    // WDSEL: Week day selection
    // DT[1:0]: Date tens in BCD format
    // DU[3:0]: Date units or day in BCD format
    // MSK3: Alarm B hours mask
    // PM: AM/PM notation
    // HT[1:0]: Hour tens in BCD format
    // HU[3:0]: Hour units in BCD format
    // MNT[2:0]: Minute tens in BCD format
    // MNU[3:0]: Minute units in BCD format
    // MSK1: Alarm B seconds mask
    // ST[2:0]: Second tens in BCD format.
    // SU[3:0]: Second units in BCD format
// RTC_ALRMBSSR alarm B sub second register [0x4C]
    // MASKSS[3:0]: Mask the most-significant bits starting at this bit
    // SS[14:0]: Sub seconds value
// RTC_SR status register [0x50]
    // ITSF: Internal timestamp flag
    // TSOVF: Timestamp overflow flag
    // TSF: Timestamp flag
    // WUTF: Wakeup timer flag
    // ALRBF: Alarm B flag
    // ALRAF: Alarm A flag
// RTC_MISR masked interrupt status register [0x54]
    // ITSMF: Internal timestamp masked flag
    // TSOVMF: Timestamp overflow masked flag
    // TSMF: Timestamp masked flag
    // WUTMF: Wakeup timer masked flag
    // ALRBMF: Alarm B masked flag
    // ALRAMF: Alarm A masked flag
// RTC_SCR status clear register [0x5C]
    // CITSF: Clear internal timestamp flag
    // CTSOVF: Clear timestamp overflow flag
    // CTSF: Clear timestamp flag
    // CWUTF: Clear wakeup timer flag
    // CALRBF: Clear alarm B flag
    // CALRAF: Clear alarm A flag

